#ifndef _WEBBROWSE_WEB_NAVIGATION_H_
#define _WEBBROWSE_WEB_NAVIGATION_H_


#include <boost/shared_ptr.hpp>	
#include <iostream> 
#include <boost/format.hpp> 

#include <nsIWebNavigation.h>
#include <dom/DOMDocument.h>
#include <necko/URI.h>
#include <xpcom/InputStream.h>

#include <utils/mozilla_if_macros.h>


class DOMDocument;
// class InputStream;
// class SHistory; 

/**
 * The nsIWebNavigation interface defines an interface for navigating the web.
 * It provides methods and attributes to direct an object to navigate to a new
 * location, stop or restart an in process load, or determine where the object
 * has previously gone.
 *
 * @status UNDER_REVIEW  */
class WebNavigation : public Supports {
	MOZ_CONSTRUCT(WebNavigation,Supports);
public: 
	
	/**
	* Indicates if the object can go back.  If true this indicates that
	* there is back session history available for navigation. */
	bool 				
	canGoBack () const 
										{	MOZ_IF_RETURN_BOOL(GetCanGoBack); 			}
	/**
	* Indicates if the object can go forward.  If true this indicates that
	* there is forward session history available for navigation */
	bool 				
	canGoForward () const 
										{	MOZ_IF_RETURN_BOOL(GetCanGoForward); 		}
	
	/**
	* Tells the object to navigate to the previous session history item.  When a
	* page is loaded from session history, all content is loaded from the cache
	* (if available) and page state (such as form values and scroll position) is
	* restored.
	*
	* @throw NS_ERROR_UNEXPECTED
	*        Indicates that the call was unexpected at this time, which implies
	*        that canGoBack is false.
	*/
	void goBack ()	
										{	ifMoz()->GoBack();							}
	
	/**
	* Tells the object to navigate to the next session history item.  When a
	* page is loaded from session history, all content is loaded from the cache
	* (if available) and page state (such as form values and scroll position) is
	* restored.
	*
	* @throw NS_ERROR_UNEXPECTED
	*        Indicates that the call was unexpected at this time, which implies
	*        that canGoForward is false.
	*/
	void goForward ()	
										{	ifMoz()->GoForward();						}
	
	/**
	* Tells the object to navigate to the session history item at a given index.
	*
	* @throw NS_ERROR_UNEXPECTED
	*        Indicates that the call was unexpected at this time, which implies
	*        that session history entry at the given index does not exist.
	*/
	void gotoIndex ( boost::int32_t iIndex )
										{	MOZ_IF_SET_VOID_INT32(GotoIndex,iIndex);	}

	/****************************************************************************
	* The following flags may be bitwise combined to form the load flags
	* parameter passed to either the loadURI or reload method.  Some of these
	* flags are only applicable to loadURI.
	*/
	/// This flags defines the range of bits that may be specified. */
	enum { LOAD_FLAGS_MASK = nsIWebNavigation::LOAD_FLAGS_MASK };

	/// This is the default value for the load flags parameter.
	enum { LOAD_FLAGS_NONE = nsIWebNavigation::LOAD_FLAGS_NONE };
	
	/**
	* This flag specifies that the load should have the semantics of an HTML
	* Meta-refresh tag (i.e., that the cache should be bypassed).  This flag
	* is only applicable to loadURI.
	* XXX the meaning of this flag is poorly defined.
	* XXX no one uses this, so we should probably deprecate and remove it. */
	enum { LOAD_FLAGS_IS_REFRESH = nsIWebNavigation::LOAD_FLAGS_IS_REFRESH };
	
	/**
	* This flag specifies that the load should have the semantics of a link
	* click.  This flag is only applicable to loadURI.
	* XXX the meaning of this flag is poorly defined. */
	enum { LOAD_FLAGS_IS_LINK = nsIWebNavigation::LOAD_FLAGS_IS_LINK };
	
	/**
	* This flag specifies that history should not be updated.  This flag is only
	* applicable to loadURI. */
	enum { LOAD_FLAGS_BYPASS_HISTORY = nsIWebNavigation::LOAD_FLAGS_BYPASS_HISTORY };
	
	/**
	* This flag specifies that any existing history entry should be replaced.
	* This flag is only applicable to loadURI. */
	enum { LOAD_FLAGS_REPLACE_HISTORY = nsIWebNavigation::LOAD_FLAGS_REPLACE_HISTORY };
	
	/**
	* This flag specifies that the local web cache should be bypassed, but an
	* intermediate proxy cache could still be used to satisfy the load. */
	enum { LOAD_FLAGS_BYPASS_CACHE = nsIWebNavigation::LOAD_FLAGS_BYPASS_CACHE };
	
	/**
	* This flag specifies that any intermediate proxy caches should be bypassed
	* (i.e., that the content should be loaded from the origin server). */
	enum { LOAD_FLAGS_BYPASS_PROXY = nsIWebNavigation::LOAD_FLAGS_BYPASS_PROXY };
	
	/**
	* This flag specifies that a reload was triggered as a result of detecting
	* an incorrect character encoding while parsing a previously loaded
	* document. */
	enum { LOAD_FLAGS_CHARSET_CHANGE = nsIWebNavigation::LOAD_FLAGS_CHARSET_CHANGE };
	
	/**
	* If this flag is set, Stop() will be called before the load starts
	* and will stop both content and network activity (the default is to
	* only stop network activity).  Effectively, this passes the
	* STOP_CONTENT flag to Stop(), in addition to the STOP_NETWORK flag. */
	enum { LOAD_FLAGS_STOP_CONTENT = nsIWebNavigation::LOAD_FLAGS_STOP_CONTENT };
	
	/// A hint this load was prompted by an external program: take care!
	enum { LOAD_FLAGS_FROM_EXTERNAL = nsIWebNavigation::LOAD_FLAGS_FROM_EXTERNAL };
	
	/**
	* This flag specifies that the URI may be submitted to a third-party
	* server for correction. This should only be applied to non-sensitive
	* URIs entered by users. */
	enum { LOAD_FLAGS_ALLOW_THIRD_PARTY_FIXUP = nsIWebNavigation::LOAD_FLAGS_ALLOW_THIRD_PARTY_FIXUP };
	
	/**
	* This flag specifies that this is the first load in this object.
	* Set with care, since setting incorrectly can cause us to assume that
	* nothing was actually loaded in this object if the load ends up being
	* handled by an external application. */
	enum { LOAD_FLAGS_FIRST_LOAD = nsIWebNavigation::LOAD_FLAGS_FIRST_LOAD };
	
	/**
	* This flag specifies that the load should not be subject to popup
	* blocking checks.*/
	enum { LOAD_FLAGS_ALLOW_POPUPS = nsIWebNavigation::LOAD_FLAGS_ALLOW_POPUPS };
	
	/**
	* This flag specifies that the URI classifier should not be checked for
	* this load. */
	enum { LOAD_FLAGS_BYPASS_CLASSIFIER = nsIWebNavigation::LOAD_FLAGS_BYPASS_CLASSIFIER };

	/**
	* Loads a given URI.  This will give priority to loading the requested URI
	* in the object implementing	this interface.  If it can't be loaded here
	* however, the URI dispatcher will go through its normal process of content
	* loading.
	*
	* @param aURI
	*        The URI string to load.  For HTTP and FTP URLs and possibly others,
	*        characters above U+007F will be converted to UTF-8 and then URL-
	*        escaped per the rules of RFC 2396.
	* @param aLoadFlags
	*        Flags modifying load behaviour.  This parameter is a bitwise
	*        combination of the load flags defined above.  (Undefined bits are
	*        reserved for future use.)  Generally you will pass LOAD_FLAGS_NONE
	*        for this parameter.
	* @param aReferrer
	*        The referring URI.  If this argument is null, then the referring
	*        URI will be inferred internally.
	* @param aPostData
	*        If the URI corresponds to a HTTP request, then this stream is
	*        appended directly to the HTTP request headers.  It may be prefixed
	*        with additional HTTP headers.  This stream must contain a "\r\n"
	*        sequence separating any HTTP headers from the HTTP request body.
	*        This parameter is optional and may be null.
	* @param aHeaders
	*        If the URI corresponds to a HTTP request, then any HTTP headers
	*        contained in this stream are set on the HTTP request.  The HTTP
	*        header stream is formatted as:
	*            ( HEADER "\r\n" )*
	*        This parameter is optional and may be null.
	*/
	/* void loadURI (in wstring aURI, in unsigned long aLoadFlags, in nsIURI aReferrer, in nsIInputStream aPostData, in nsIInputStream aHeaders); */
//	LoadURI(const PRUnichar *aURI, PRUint32 aLoadFlags, nsIURI *aReferrer, nsIInputStream *aPostData, nsIInputStream *aHeaders) = 0;

	/**
	* Tells the Object to reload the current page.  There may be cases where the
	* user will be asked to confirm the reload (for example, when it is
	* determined that the request is non-idempotent).
	*
	* @param aReloadFlags
	*        Flags modifying load behaviour.  This parameter is a bitwise
	*        combination of the Load Flags defined above.  (Undefined bits are
	*        reserved for future use.)  Generally you will pass LOAD_FLAGS_NONE
	*        for this parameter.
	*
	* @throw NS_BINDING_ABORTED
	*        Indicating that the user canceled the reload.
	*/
	void reload ( boost::uint32_t iReloadFlags )
										{	MOZ_IF_SET_VOID_UINT32(Reload,iReloadFlags);	}

	/****************************************************************************
	* The following flags may be passed as the stop flags parameter to the stop
	* method defined on this interface.
	*/
	
	/// This flag specifies that all network activity should be stopped.  This
	/// includes both active network loads and pending META-refreshes.
	enum { STOP_NETWORK = nsIWebNavigation::STOP_NETWORK };
	
	/// This flag specifies that all content activity should be stopped.  This
	/// includes animated images, plugins and pending Javascript timeouts.
	enum { STOP_CONTENT = nsIWebNavigation::STOP_CONTENT };
	
	/// This flag specifies that all activity should be stopped. 
	enum { STOP_ALL = nsIWebNavigation::STOP_ALL };
	
	/**
	* Stops a load of a URI.
	*
	* @param aStopFlags
	*        This parameter is one of the stop flags defined above.
	*/
	void			
	stop ( boost::uint32_t iStopFlags )
										{	MOZ_IF_SET_VOID_UINT32(Stop,iStopFlags);	}
	
	/**
	* Retrieves the current DOM document for the frame, or lazily creates a
	* blank document if there is none.  This attribute never returns null except
	* for unexpected error situations. */
	boost::shared_ptr<DOMDocument>			
	document ()
										{	MOZ_IF_RETURN_MOZ(GetDocument,DOMDocument);	}
	
	/// The currently loaded URI or null.
	boost::shared_ptr<URI>			
	currentURI ()
										{	MOZ_IF_RETURN_MOZ(GetCurrentURI,URI);	}
	
	/// The referring URI for the currently loaded URI or null.
	boost::shared_ptr<URI>			
	referringURI ()
										{	MOZ_IF_RETURN_MOZ(GetReferringURI,URI);	}
	
	/**
	* The session history object used by this web navigation instance.
	*/
	/* attribute nsISHistory sessionHistory; */
// 	GetSessionHistory(nsISHistory * *aSessionHistory) = 0;
// 	SetSessionHistory(nsISHistory * aSessionHistory) = 0;

	// ------------------------------------------------
	// --- Methods beyond W3C/Mozilla specification ---	
	// ------------------------------------------------
	
	bool loadURI( const std::string& sURI, boost::uint32_t aLoadFlags = LOAD_FLAGS_NONE ) ;
	std::string 	currentURIAsString() const;
	
/*	
	/// Simple loadURI overload.
	/// \return True if call succeded.
	bool loadURI( const std::string& sURI, boost::uint32_t aLoadFlags = LOAD_FLAGS_NONE ) 
	{
////		std::cout << boost::format ( "WebNavigation::loadURI URL: %1%\n") % sURI;
//		nsresult rv = ifMoz()->LoadURI( NS_ConvertASCIItoUTF16( sURI.c_str() ).get(), aLoadFlags, 0, 0, 0);
		nsresult rv = ifMoz()->LoadURI( NS_ConvertUTF8toUTF16( sURI.c_str() ).get(), aLoadFlags, 0, 0, 0);
		if ( NS_FAILED(rv) ) 	return false;
		else					return true;
	}

	std::string 	currentURIAsString() const
	{
		nsCString		uriAsciiString;
		nsCOMPtr<nsIURI> 	pIURI;
		ifMoz()->GetCurrentURI( getter_AddRefs(pIURI) );
		
		pIURI->GetAsciiSpec( uriAsciiString );
		return std::string ( uriAsciiString.get() );
	}
	*/

//	std::string 	currentURIPageSource() const;
// 	std::string 	currentURIPageSourceWget() const;


};

#endif /* _WEBBROWSE_WEB_NAVIGATION_H_ */


