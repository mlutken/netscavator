/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

//wxMozilla
#include "wxMozillaProtocolHandler.h"
#include "helpers.h"
#include "wxMozillaComponents.h"

//Mozilla

// // #include "nsIServiceManagerUtils.h"
// // #include "nsIEventQueue.h"
// // #include "nsIEventQueueService.h"
#include "nsServiceManagerUtils.h"
#include "nsEventQueue.h"
#include "prthread.h"
#include "nsIThreadManager.h"

#include "netCore.h"
#include "nsNetUtil.h"
////#include "nsReadableUtils.h"
#include "nsIURI.h"
#include "nsIChannel.h"
#include "nsIFactory.h"
#include "nsNetCID.h"
#include "nsIStandardURL.h"
#include "nsIFileURL.h"
#include "nsStringAPI.h"
#include "nsIFileStreams.h"
#include "nsWidgetsCID.h"
#include "nsXPCOM.h"
#include "nsIComponentRegistrar.h"
#include "nsIProgressEventSink.h"

//wxWindows
#include "wx/filesys.h"

//
//--------------------- Prototypes and classes
//

class wxMozillaProtocolHandler : public nsIProtocolHandler
{
	public:
		wxMozillaProtocolHandler ( wxProtocolHandler* wrapped );
		virtual ~wxMozillaProtocolHandler();
	public:
		NS_DECL_ISUPPORTS
		NS_DECL_NSIPROTOCOLHANDLER
	private:
		wxProtocolHandler* mProtocolHandler;
		nsCString mScheme;
		PRUint32  mProtocolFlags;
};


/**
 * Exposing a wxInputStream to Mozilla
 */
class wxMozillaStream : public nsIInputStream
{
	public:
		/**
		 * Build a MozillaStream
		 *
		 * @param channel a non-null channel which will be used as source for the stream
		 */
		wxMozillaStream ( wxProtocolChannel* channel );
		virtual ~wxMozillaStream();
	public:
		NS_DECL_ISUPPORTS
		NS_DECL_NSIINPUTSTREAM
	private:
		/**
		 * The wrapped protocol channel.
		 */
		wxProtocolChannel const* mProtocolChannel;
		/**
		 * The wrapped input stream (obtained from mProtocolChannel)
		 */
		wxInputStream*    mInputStream;
		/**
		 * A guess on the number of bytes initially available on this channel.
		 *
		 * If we do not have any idea, we have mSize=-1
		 */
		const int mSize;
};


/**
 * A Mozilla channel based on a wxInputStream.
 *
 * At this level, we have a Mozilla channel wrapping a wxInputStream
 * wrapping a platform-dependent stream. This may seem like overkill
 * but we DO want to be able to write custom protocol handlers without
 * depending on Mozilla.
 *
 * And anyway, it's easier like this.
 */
class wxMozillaChannel : public nsIChannel,
			nsIStreamListener
{
	public:
		NS_DECL_ISUPPORTS
		NS_DECL_NSICHANNEL
		NS_DECL_NSIREQUEST
		NS_DECL_NSISTREAMLISTENER
		NS_DECL_NSIREQUESTOBSERVER

	public:
		wxMozillaChannel ( nsIURI* uri, wxProtocolHandler* aProtocolHandler );
		virtual ~wxMozillaChannel();
	protected:
		nsresult EnsureTransport();
	private:
		wxProtocolHandler* mProtocolHandler;

		PRInt32        mPort;
		PRInt32        mContentLength;

		nsCOMPtr<nsIInterfaceRequestor>  mCallbacks;
		nsCOMPtr<nsIURI>                 mOriginalURI;
		nsCOMPtr<nsIURI>                 mURI;
		nsCOMPtr<nsIStreamListener>      mListener;
		nsCOMPtr<nsILoadGroup>           mLoadGroup;
		nsCOMPtr<nsITransport>           mTransport;
		nsCOMPtr<nsISupports>            mOwner;
		nsCOMPtr<nsISupports>            mListenerContext;
		nsCOMPtr<nsIRequest>             mCurrentRequest;
		nsCOMPtr<nsIProgressEventSink>      mProgress;
		nsLoadFlags    mLoadFlags;

		nsCString      mContentType;
		nsCString      mContentCharset;

		nsresult       mStatus;
};



#if wxUSE_FILESYSTEM
/**
 * Class wxFSProtocolHandler
 */
class wxFSProtocolChannel : public wxProtocolChannel
{
	public:
		/**
		 * Build a FSProtocolChannel for a given file.
		 *
		 * @param file the possibly NULL wrapped file - it now belongs to <b>this</b>
		 */
		wxFSProtocolChannel ( wxFSFile* file ) : mFile ( file )
		{
		}
		~wxFSProtocolChannel()
		{
			delete mFile;
		}
		wxInputStream* GetStream()
		{
			if ( mFile==NULL )
				return NULL;
			return mFile->GetStream();
		}
		wxString GetCharset()
		{
			return UNKNOWN_CHARSET;
		}
		wxString GetContentType()
		{
			if ( mFile==NULL )
				return UNKNOWN_CONTENT_TYPE;
			return mFile->GetMimeType();
		}
	protected:
		wxFSFile* mFile;
};
#endif

//
//--------------------------- Implementations
//


//
//------ProtocolHandler
//
wxProtocolHandler::wxProtocolHandler ( const wxString scheme ) : mScheme ( scheme )
{
}

wxProtocolHandler::~wxProtocolHandler()
{
}

const wxString wxProtocolHandler::GetScheme()
{
	return mScheme;
}

int wxProtocolHandler::GetDefaultPort()
{
	return -1;
}

bool wxProtocolHandler::IsStd() const
{
	return true;
}

bool wxProtocolHandler::IsNoRelative() const
{
	return false;
}

bool wxProtocolHandler::IsNoAuthorityComponent() const
{
	return false;
}

bool wxProtocolHandler::IsAllowedProxy() const
{
	return false;
}

bool wxProtocolHandler::IsAllowedProxyHTTP() const
{
	return false;
}

bool wxProtocolHandler::IsAllowedPort ( int port, const wxString scheme )
{
	return false;
}


//
//------FSProtocolHandler
//


#if wxUSE_FILESYSTEM

/*static*/
wxFileSystem wxFSProtocolHandler::ms_fsys;

wxFSProtocolHandler::wxFSProtocolHandler ( const wxString scheme ) : wxProtocolHandler ( scheme )
{
}

const wxString wxFSProtocolHandler::NewURI ( const wxString spec, const wxString base )
{
	//@todo YORIC: implement uri syntax check ?
	if ( spec.StartsWith ( mScheme ) ) //Nothing to do
		return spec;
	wxString mutable_base = base;
	if ( mutable_base.IsEmpty() ) //Build from scratch
		mutable_base = mScheme+wxT ( "://" );
	return mutable_base+spec;
}

wxProtocolChannel* wxFSProtocolHandler::OpenChannel ( const wxString uri )
{
	wxString actual_url;
	const int anchor = uri.Find ( '#', TRUE );
	if ( anchor==-1 )
		actual_url = uri;
	else
		actual_url = uri.Mid ( 0, anchor );
	wxFSFile* virtual_file = ms_fsys.OpenFile ( actual_url );
	if ( virtual_file==NULL )
		return NULL;
	return new wxFSProtocolChannel ( virtual_file );
}

#endif // wxUSE_FILESYSTEM

//
// --------- MozillaStream
//
NS_IMPL_ISUPPORTS1 ( wxMozillaStream, nsIInputStream )

wxMozillaStream::wxMozillaStream ( wxProtocolChannel* channel ) :
		mProtocolChannel ( channel ),
		mInputStream ( channel->GetStream() ),
		mSize ( mInputStream->GetSize() )
{
	NS_INIT_ISUPPORTS();
}

wxMozillaStream::~wxMozillaStream()
{
	delete mProtocolChannel;
}


/* void close (); */
NS_IMETHODIMP wxMozillaStream::Close()
{
	//Nothing to do : the stream will be closed with its destruction.
	return NS_OK;
}

/* unsigned long available (); */
NS_IMETHODIMP wxMozillaStream::Available ( PRUint32 *_retval )
{
	if ( mSize>0 ) //<If we know how much is available
		*_retval= mSize-mInputStream->TellI();
	else
		*_retval = 0;
	return NS_OK;
}

/* [noscript] unsigned long read (in charPtr aBuf, in unsigned long aCount); */
NS_IMETHODIMP wxMozillaStream::Read ( char * aBuf, PRUint32 aCount, PRUint32 *_retval )
{
	mInputStream->Read ( aBuf, aCount );
	int last_read = mInputStream->LastRead();
	if ( last_read==0 )
		switch ( mInputStream->GetLastError() )
		{
			case wxSTREAM_EOF       :return NS_BASE_STREAM_CLOSED;
			case wxSTREAM_READ_ERROR:return NS_BASE_STREAM_OSERROR;
			case wxSTREAM_NO_ERROR  :
				*_retval = 0;
				return NS_OK;
			default:
				wxFAIL_MSG ( wxT ( "This kind of MozillaChannel error should not happen " ) );
				return NS_BASE_STREAM_OSERROR;
		}
	else
	{
		//YORIC: for debugging purpose -- broken by unicode, I guess wxString just_read(aBuf, last_read);
		*_retval = ( PRUint32 ) last_read;
	}
	return NS_OK;
}

/* [noscript] unsigned long readSegments (in nsWriteSegmentFun aWriter, in voidPtr aClosure, in unsigned long aCount); */
NS_IMETHODIMP wxMozillaStream::ReadSegments ( nsWriteSegmentFun aWriter, void * aClosure, PRUint32 aCount, PRUint32 *_retval )
{
	//@todo YORIC: implement readsegments ?
	return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean isNonBlocking (); */
NS_IMETHODIMP wxMozillaStream::IsNonBlocking ( PRBool *_retval )
{
	*_retval = false;
	return NS_OK;
}


//
// ------- wxMozillaProtocolHandler
//
NS_IMPL_ISUPPORTS1 ( wxMozillaProtocolHandler, nsIProtocolHandler )

wxMozillaProtocolHandler::wxMozillaProtocolHandler ( wxProtocolHandler* wrapped ) :
		mProtocolHandler ( wrapped ),
////		mScheme ( NS_ConvertUCS2toUTF8 ( wxString_to_nsString ( wrapped->GetScheme(), wxConvLocal ) ) ), //@todo YORIC: check that this is the right converter
		mScheme ( NS_ConvertUTF16toUTF8 ( wxString_to_nsString ( wrapped->GetScheme(), wxConvLocal ) ) ), //@todo YORIC: check that this is the right converter
		mProtocolFlags ( 0 )
{
	NS_INIT_ISUPPORTS();
	if ( wrapped->IsStd() )
		mProtocolFlags+=URI_STD;
	if ( wrapped->IsNoRelative() )
		mProtocolFlags+=URI_NORELATIVE;
	if ( wrapped->IsNoAuthorityComponent() )
		mProtocolFlags+=URI_NOAUTH;
	if ( wrapped->IsAllowedProxy() )
		mProtocolFlags+=ALLOWS_PROXY;
	if ( wrapped->IsAllowedProxyHTTP() )
		mProtocolFlags+=ALLOWS_PROXY_HTTP;
}

wxMozillaProtocolHandler::~wxMozillaProtocolHandler()
{
	delete mProtocolHandler;
}

/* readonly attribute ACString scheme; */
NS_IMETHODIMP wxMozillaProtocolHandler::GetScheme ( nsACString & aScheme )
{
	//wxString wx_scheme = nsString_to_wxString(NS_ConvertUTF8toUCS2(aScheme),wxConvLocal);//@todo YORIC: check that this is the right converter
	//ConvertString(mScheme, wx_scheme);
	aScheme = mScheme;
	return NS_OK;
}

/* readonly attribute long defaultPort; */
NS_IMETHODIMP wxMozillaProtocolHandler::GetDefaultPort ( PRInt32 *aDefaultPort )
{
	*aDefaultPort = mProtocolHandler->GetDefaultPort();
	return NS_OK;
}

/* readonly attribute unsigned long protocolFlags; */
NS_IMETHODIMP wxMozillaProtocolHandler::GetProtocolFlags ( PRUint32 *aProtocolFlags )
{
	*aProtocolFlags=mProtocolFlags;
	return NS_OK;
}

/* nsIURI newURI (in AUTF8String aSpec, in string aOriginCharset, in nsIURI aBaseURI); */
NS_IMETHODIMP wxMozillaProtocolHandler::NewURI ( const nsACString & aSpec, const char*, nsIURI *aBaseURI, nsIURI **_retval )
{
////	const wxString wx_spec = nsString_to_wxString ( NS_ConvertUTF8toUCS2 ( aSpec ), wxConvLocal );
	const wxString wx_spec = nsString_to_wxString ( NS_ConvertUTF8toUTF16 ( aSpec ), wxConvLocal );
	const wxString wx_base = nsURI_to_wxString ( aBaseURI );
	wxString  wx_result = mProtocolHandler->NewURI ( wx_spec, wx_base );
	*_retval= wxString_to_nsURI ( wx_result );
	return NS_OK;
}


/* nsIChannel newChannel (in nsIURI aURI); */
NS_IMETHODIMP wxMozillaProtocolHandler::NewChannel ( nsIURI *aURI, nsIChannel **_retval )
{
	nsresult rv;
	wxString wx_provided_uri = nsURI_to_wxString ( aURI );

	wxProtocolChannel*  input_channel = mProtocolHandler->OpenChannel ( wx_provided_uri );

	if ( !input_channel )
		return NS_ERROR_FILE_NOT_FOUND;

	/**
	 * YORIC: @todo This might be made more Mozilla-like (i.e. no "new"), but it seems to work, including cleanup.
	 *
	 * Is this too much implementation-dependent ? I don't think so, but could be.
	 */
	nsCOMPtr<nsIInputStream>    embedder_stream = new wxMozillaStream ( input_channel );
// // 	const nsCAutoString content_type = NS_ConvertUCS2toUTF8 ( wxString_to_nsString ( input_channel->GetContentType(), wxConvLocal ) );
// // 	const nsCAutoString charset      = NS_ConvertUCS2toUTF8 ( wxString_to_nsString ( input_channel->GetCharset(), wxConvLocal ) );
	const nsCAutoString content_type = NS_ConvertUTF16toUTF8 ( wxString_to_nsString ( input_channel->GetContentType(), wxConvLocal ) );
	const nsCAutoString charset      = NS_ConvertUTF16toUTF8 ( wxString_to_nsString ( input_channel->GetCharset(), wxConvLocal ) );


	//YORIC:Mozilla 1.0
	//rv = NS_NewInputStreamChannel(_retval, aURI, embedder_stream, content_type, charset,-1);
	//YORIC:Mozilla 1.3+
	rv = NS_NewInputStreamChannel ( _retval, aURI, embedder_stream, content_type, charset );
	return NS_OK;
}

/* boolean allowPort (in long port, in string scheme); */
NS_IMETHODIMP wxMozillaProtocolHandler::AllowPort ( PRInt32 port, const char *scheme, PRBool *_retval )
{
// // 	wxString  destination = nsString_to_wxString ( NS_ConvertUTF8toUCS2 ( scheme ), wxConvLocal );
	wxString  destination = nsString_to_wxString ( NS_ConvertUTF8toUTF16 ( scheme ), wxConvLocal );
	*_retval=mProtocolHandler->IsAllowedPort ( port, destination );
	return NS_OK;
}


static NS_DEFINE_CID ( kAppShellCID, NS_APPSHELL_CID );



class nsAProtocolFactory : public nsIFactory
{
	public:
		NS_DECL_ISUPPORTS
		nsAProtocolFactory ( const wxString scheme, wxProtocolHandlerFactory factory ) :
				mScheme ( scheme )
		{
			NS_INIT_ISUPPORTS();
			mFactory = factory;
		}
		NS_IMETHOD CreateInstance ( nsISupports *aOuter,
		                            const nsIID &aIID,
		                            void **aResult )
		{
			nsresult rv;
			if ( aResult==NULL )
				return NS_ERROR_NULL_POINTER;
			if ( aOuter!=NULL )
				return NS_ERROR_NO_AGGREGATION;
			wxProtocolHandler* wxhandler = ( *mFactory ) ( mScheme );
			if ( wxhandler==NULL )
				return NS_ERROR_NULL_POINTER;
			nsIProtocolHandler* handler = new wxMozillaProtocolHandler ( wxhandler );
			if ( handler==NULL )
				return NS_ERROR_OUT_OF_MEMORY;
			*aResult = handler;
			NS_ADDREF ( handler );
			rv = handler->QueryInterface ( aIID, aResult );
			NS_RELEASE ( handler );
			return rv;
		}

		NS_IMETHOD LockFactory ( PRBool aLock )
		{
			return NS_OK;
		}

	protected:
		virtual ~nsAProtocolFactory() {}
	protected:
		const wxString mScheme;
		wxProtocolHandlerFactory* mFactory;
};

NS_IMPL_ISUPPORTS0 ( nsAProtocolFactory )


bool wxRegisterProtocolHandler ( const wxString name, const wxString scheme, const wxUId id, wxProtocolHandlerFactory callback )
{
	nsresult rv;
	nsCOMPtr<nsIComponentRegistrar> registrar;
	nsIFactory* factory = new nsAProtocolFactory ( scheme, callback );//@todo YORIC never recovered !
	const wxString wx_contract = wxT ( NS_NETWORK_PROTOCOL_CONTRACTID_PREFIX ) +scheme;
	NS_GetComponentRegistrar ( getter_AddRefs ( registrar ) );
	const nsCID cid = wxUId_to_nsID ( id );

// // 	const char* converted_name     = ToNewCString ( ( nsCAutoString ) NS_ConvertUCS2toUTF8 ( wxString_to_nsString ( name, wxConvLocal ) ) );
// // 	const char* converted_contract = ToNewCString ( ( nsCAutoString ) NS_ConvertUCS2toUTF8 ( wxString_to_nsString ( wx_contract, wxConvLocal ) ) );
	const char* converted_name     = ToNewCString ( ( nsCAutoString ) NS_ConvertUTF16toUTF8 ( wxString_to_nsString ( name, wxConvLocal ) ) );
	const char* converted_contract = ToNewCString ( ( nsCAutoString ) NS_ConvertUTF16toUTF8 ( wxString_to_nsString ( wx_contract, wxConvLocal ) ) );

	rv = registrar->RegisterFactory ( cid,
	                                  converted_name,
	                                  converted_contract,
	                                  factory );    //Always replace
	wxASSERT_MSG ( !NS_FAILED ( rv ), wxT ( "Could not register factory" ) );
	delete converted_name;
	delete converted_contract;
	return true;
}
