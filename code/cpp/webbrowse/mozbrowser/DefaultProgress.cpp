#include <stdio.h>
#include <boost/thread.hpp>
#include <boost/algorithm/string.hpp>

#include <nsIChannel.h>
#include <nsIWebProgress.h>
#include <nsIDOMWindow.h>
#include <nsNetError.h>

#include <nsIURI.h>
#include <MozBrowserWx.h>
#include <SignalsManager.h>
#include "DefaultProgress.h"




namespace b = boost;

DefaultProgress::DefaultProgress (  
    MozBrowserWx* pMozBrowser
)	:
    m_pMozBrowser( pMozBrowser )
{
}

DefaultProgress::~DefaultProgress()
{
}

NS_IMPL_ISUPPORTS2 ( DefaultProgress,
                     nsIWebProgressListener,
                     nsISupportsWeakReference )



/** 
\see http://hg.mozilla.org/incubator/embedding/rev/c335c76103d5#l1.37 */
NS_IMETHODIMP
DefaultProgress::OnStateChange ( nsIWebProgress *aWebProgress,
                               nsIRequest     *aRequest,
                               PRUint32        aStateFlags,
                               nsresult        aStatus )
{
	using namespace std;
    static int iCount = 0;
    iCount++;

	// if we've got the start flag, emit the signal
	if ( ( aStateFlags & STATE_IS_NETWORK ) && ( aStateFlags & STATE_START ) )
	{
		// get the uri for this request
		nsCAutoString uriString;
		requestToURIString ( aRequest, uriString );
        if (m_pMozBrowser) m_pMozBrowser->signalsManager()->signalOnNetStart( *m_pMozBrowser, uriString.get() )	;
	}

    // Signal 'On Net Progress' event
	nsCAutoString uriString;
	requestToURIString ( aRequest, uriString );
    if (m_pMozBrowser) m_pMozBrowser->signalsManager()->signalOnNetProgress( aRequest, aStateFlags, uriString.get() )	;


	// is it the same as the current URI?
//	if ( mOwner->mURI.Equals ( uriString ) )
//	{
//		// for people who know what they are doing
//		g_signal_emit ( G_OBJECT ( mOwner->mOwningWidget ),  moz_embed_signals[NET_STATE], 0, aStateFlags, aStatus );
//	}
//	g_signal_emit ( G_OBJECT ( mOwner->mOwningWidget ), moz_embed_signals[NET_STATE_ALL], 0, uriString.get(),( gint ) aStateFlags, ( gint )aStatus );
	// and for stop, too
 	if ( ( aStateFlags & STATE_IS_NETWORK ) && ( aStateFlags & STATE_STOP ) ) {
        //printf("OLD(%d): PAGE LOADED %X : %s", iCount, aStateFlags, uriString.get() );
        //cout << endl;

///        nsIWebBrowser* mWebBrowser =  m_pMozBrowser->webBrowser()->ifMoz();
///        nsCOMPtr<nsIDOMWindow> contentWin;
///        mWebBrowser->GetContentDOMWindow(getter_AddRefs(contentWin));
        nsCOMPtr<nsIDOMWindow> contentWin ( m_pMozBrowser->getIContentDOMWindow() );


        nsCOMPtr<nsIDOMWindow> progressWindow;
        aWebProgress->GetDOMWindow(getter_AddRefs(progressWindow));
        if ( SameCOMIdentity(progressWindow, contentWin) ) {
            //printf("NNN (%d): page loaded : %X  '%s'", iCount, aStateFlags, uriString.get() );
            //cout << endl;
        }
    }


//    // --- NEW ---
//    boost::uint32_t pageLoadedFlags = STATE_STOP | STATE_IS_NETWORK | STATE_IS_WINDOW;
//    if ( aStateFlags == pageLoadedFlags ) {
//        printf("TST(%d):  page loaded: %X == %X   '%s'", iCount, aStateFlags, pageLoadedFlags, uriString.get() );
//        cout << endl;


//    }

     if ( (aStateFlags & STATE_STOP) && (aStateFlags & STATE_IS_DOCUMENT) ) 
// 	if ( ( aStateFlags & STATE_IS_NETWORK ) && ( aStateFlags & STATE_STOP ) )
	{
        //printf("AAA(%d): page loaded 1: %X  '%s'", iCount, aStateFlags, uriString.get() );
        //cout << endl;

///        nsIWebBrowser* mWebBrowser =  m_pMozBrowser->webBrowser()->ifMoz();
///		nsCOMPtr<nsIDOMWindow> contentWin;
///		mWebBrowser->GetContentDOMWindow(getter_AddRefs(contentWin));
        nsCOMPtr<nsIDOMWindow> contentWin ( m_pMozBrowser->getIContentDOMWindow() );
		
  		// The fact that nsWebBrowser won't hand out its root web progress is ridiculous.
		nsCOMPtr<nsIDOMWindow> progressWindow;
		aWebProgress->GetDOMWindow(getter_AddRefs(progressWindow));
				
		// Make sure the current window is the main content window
		if ( SameCOMIdentity(progressWindow, contentWin) ) {
            ////printf("ML: CUR (%d): page loaded 2: %X  '%s'\n", iCount, aStateFlags, uriString.get() );
            //cout << endl;
            m_pMozBrowser->signalsManager()->signalPageLoaded( *m_pMozBrowser );
		}
	}
    //printf("ML ... %d ... %X : %s",  iCount, aStateFlags, uriString.get());
    //cout << endl;
	return NS_OK;
}


/*
--------------------------
--- OLD implementation ---
--------------------------
- which did give multiple 'pageloaded' events when fx. IFRAMES on the page.
--------------------------
NS_IMETHODIMP
DefaultProgress::OnStateChange ( nsIWebProgress *aWebProgress,
                               nsIRequest     *aRequest,
                               PRUint32        aStateFlags,
                               nsresult        aStatus )
{
//	printf("DefaultProgress::OnStateChange\n");
	// give the widget a chance to attach any listeners
//	mOwner->ContentStateChange();
	// if we've got the start flag, emit the signal
	if ( ( aStateFlags & STATE_IS_NETWORK ) && ( aStateFlags & STATE_START ) )
	{
//		printf("DefaultProgress::STATE_START\n");
// 		g_signal_emit ( G_OBJECT ( mOwner->mOwningWidget ),  moz_embed_signals[NET_START], 0 );
	}

	// get the uri for this request
	nsCAutoString uriString;
	requestToURIString ( aRequest, uriString );

	// is it the same as the current URI?
//	if ( mOwner->mURI.Equals ( uriString ) )
//	{
//		// for people who know what they are doing
//		g_signal_emit ( G_OBJECT ( mOwner->mOwningWidget ),  moz_embed_signals[NET_STATE], 0, aStateFlags, aStatus );
//	}
//	g_signal_emit ( G_OBJECT ( mOwner->mOwningWidget ), moz_embed_signals[NET_STATE_ALL], 0, uriString.get(),( gint ) aStateFlags, ( gint )aStatus );
	// and for stop, too
 	if ( ( aStateFlags & STATE_IS_NETWORK ) && ( aStateFlags & STATE_STOP ) )
	{
 		m_mozBrowser.signalsManager()->signalPageLoaded( m_mozBrowser );
// 		printf("\n\nDefaultProgress::STATE_STOP\n");
	}

	return NS_OK;
}
*/


// 		if (!mSizeSet && (mChromeFlags & nsIWebBrowserChrome::CHROME_OPENAS_CHROME)) {
// 			if (contentWin)	contentWin->SizeToContent();
// 			SetVisibility(PR_TRUE);
// 		}






NS_IMETHODIMP
DefaultProgress::OnProgressChange ( nsIWebProgress *aWebProgress,
                                  nsIRequest     *aRequest,
                                  PRInt32         aCurSelfProgress,
                                  PRInt32         aMaxSelfProgress,
                                  PRInt32         aCurTotalProgress,
                                  PRInt32         aMaxTotalProgress )
{
	nsCAutoString uriString;
	requestToURIString ( aRequest, uriString );
	return NS_OK;
}

NS_IMETHODIMP
DefaultProgress::OnLocationChange ( nsIWebProgress *aWebProgress,
                                  nsIRequest     *aRequest,
                                  nsIURI         *aLocation )
{
// 	printf("DefaultProgress::OnLocationChange\n");
	nsCAutoString newURI;
	NS_ENSURE_ARG_POINTER ( aLocation );
	aLocation->GetSpec ( newURI );

	// Make sure that this is the primary frame change and not
	// just a subframe.
	PRBool isSubFrameLoad = PR_FALSE;
	if ( aWebProgress )
	{
		nsCOMPtr<nsIDOMWindow> domWindow;
		nsCOMPtr<nsIDOMWindow> topDomWindow;

		aWebProgress->GetDOMWindow ( getter_AddRefs ( domWindow ) );

		// get the root dom window
		if ( domWindow )	domWindow->GetTop ( getter_AddRefs ( topDomWindow ) );

		if ( domWindow != topDomWindow )	isSubFrameLoad = PR_TRUE;
	}

	if ( !isSubFrameLoad )
	{
// 		printf("DefaultProgress::OnLocationChange FULL PAGE LOAD\n");
	}

	return NS_OK;
}

NS_IMETHODIMP
DefaultProgress::OnStatusChange ( nsIWebProgress  *aWebProgress,
                                nsIRequest      *aRequest,
                                nsresult         aStatus,
                                const PRUnichar *aMessage )
{
	return NS_OK;
}

NS_IMETHODIMP
DefaultProgress::OnSecurityChange ( nsIWebProgress *aWebProgress,
                                  nsIRequest     *aRequest,
                                  PRUint32         aState )
{
	return NS_OK;
}

void
DefaultProgress::requestToURIString ( nsIRequest *aRequest, nsACString &aString )
{
	// is it a channel
	nsCOMPtr<nsIChannel> channel;
	channel = do_QueryInterface ( aRequest );
	if ( !channel )	return;

	nsCOMPtr<nsIURI> uri;
	channel->GetURI ( getter_AddRefs ( uri ) );
	if ( !uri )		return;

	uri->GetSpec ( aString );
}





/*

NS_IMETHODIMP
DefaultProgress::OnStateChange ( nsIWebProgress *aWebProgress,
                               nsIRequest     *aRequest,
                               PRUint32        aStateFlags,
                               nsresult        aStatus )
{
    using namespace std;
    static int iCount = 0;
    iCount++;

    // if we've got the start flag, emit the signal
    if ( ( aStateFlags & STATE_IS_NETWORK ) && ( aStateFlags & STATE_START ) )
    {
        // get the uri for this request
        nsCAutoString uriString;
        requestToURIString ( aRequest, uriString );
        m_mozBrowser.signalsManager()->signalOnNetStart( m_mozBrowser, uriString.get() )	;
    }

    // Signal 'On Net Progress' event
    nsCAutoString uriString;
    requestToURIString ( aRequest, uriString );
    m_mozBrowser.signalsManager()->signalOnNetProgress( aRequest, aStateFlags, uriString.get() )	;


    // is it the same as the current URI?
//	if ( mOwner->mURI.Equals ( uriString ) )
//	{
//		// for people who know what they are doing
//		g_signal_emit ( G_OBJECT ( mOwner->mOwningWidget ),  moz_embed_signals[NET_STATE], 0, aStateFlags, aStatus );
//	}
//	g_signal_emit ( G_OBJECT ( mOwner->mOwningWidget ), moz_embed_signals[NET_STATE_ALL], 0, uriString.get(),( gint ) aStateFlags, ( gint )aStatus );
    // and for stop, too
    if ( ( aStateFlags & STATE_IS_NETWORK ) && ( aStateFlags & STATE_STOP ) ) {
        //printf("OLD(%d): PAGE LOADED %X : %s", iCount, aStateFlags, uriString.get() );
        //cout << endl;

        nsIWebBrowser* mWebBrowser =  m_mozBrowser.webBrowser()->ifMoz();
        nsCOMPtr<nsIDOMWindow> contentWin;
        mWebBrowser->GetContentDOMWindow(getter_AddRefs(contentWin));
        nsCOMPtr<nsIDOMWindow> progressWindow;
        aWebProgress->GetDOMWindow(getter_AddRefs(progressWindow));
        if ( SameCOMIdentity(progressWindow, contentWin) ) {
            //printf("NNN (%d): page loaded : %X  '%s'", iCount, aStateFlags, uriString.get() );
            //cout << endl;
        }
    }


//    // --- NEW ---
//    boost::uint32_t pageLoadedFlags = STATE_STOP | STATE_IS_NETWORK | STATE_IS_WINDOW;
//    if ( aStateFlags == pageLoadedFlags ) {
//        printf("TST(%d):  page loaded: %X == %X   '%s'", iCount, aStateFlags, pageLoadedFlags, uriString.get() );
//        cout << endl;


//    }

     if ( (aStateFlags & STATE_STOP) && (aStateFlags & STATE_IS_DOCUMENT) )
// 	if ( ( aStateFlags & STATE_IS_NETWORK ) && ( aStateFlags & STATE_STOP ) )
    {
        //printf("AAA(%d): page loaded 1: %X  '%s'", iCount, aStateFlags, uriString.get() );
        //cout << endl;

        nsIWebBrowser* mWebBrowser =  m_mozBrowser.webBrowser()->ifMoz();
        nsCOMPtr<nsIDOMWindow> contentWin;
        mWebBrowser->GetContentDOMWindow(getter_AddRefs(contentWin));

        // The fact that nsWebBrowser won't hand out its root web progress is ridiculous.
        nsCOMPtr<nsIDOMWindow> progressWindow;
        aWebProgress->GetDOMWindow(getter_AddRefs(progressWindow));

        // Make sure the current window is the main content window
        if ( SameCOMIdentity(progressWindow, contentWin) ) {
            //printf("CUR (%d): page loaded 2: %X  '%s'", iCount, aStateFlags, uriString.get() );
            //cout << endl;
            m_mozBrowser.signalsManager()->signalPageLoaded( m_mozBrowser );
        }
    }
    //printf("ML ... %d ... %X : %s",  iCount, aStateFlags, uriString.get());
    //cout << endl;
    return NS_OK;
}


 */


/*

        16U = 00 00 10 = 0000 0000.0000 0001.0000 = 00000000000000010000 = STATE_STOP
    262144U = 04 00 00 = 0100 0000.0000 0000.0000 = 01000000000000000000 = STATE_IS_NETWORK
    524288U = 08 00 00 = 1000 0000.0000 0000.0000 = 10000000000000000000 = STATE_IS_WINDOW
    786432U = 0C 00 00 = 1100 0000.0000 0000.0000 = 11000000000000000000
    786448U = 0C 00 10 = 1100 0000.0000 0001.0000 = 11000000000000010000
  enum { STATE_START = 1U }; 00 00 00 01

  enum { STATE_REDIRECTING = 2U }; 00 00 00 02

  enum { STATE_TRANSFERRING = 4U }; 00 00 00 04

  enum { STATE_NEGOTIATING = 8U }; 00 00 00 08

  enum { STATE_STOP = 16U }; 00 00 00 10
  enum { STATE_IS_REQUEST = 65536U }; 00 01 00 00

  enum { STATE_IS_DOCUMENT = 131072U }; 00 02 00 00

  enum { STATE_IS_NETWORK = 262144U }; 00 04 00 00 = 0000.0100 0000.0000 0000.0000

  enum { STATE_IS_WINDOW = 524288U };  00 08 00 00 = 0000.1000 0000.0000 0000.0000

  enum { STATE_RESTORING = 16777216U }; 01 00 00 00

  enum { STATE_IS_INSECURE = 4U };

  enum { STATE_IS_BROKEN = 1U };

  enum { STATE_IS_SECURE = 2U };

  enum { STATE_SECURE_HIGH = 262144U };

  enum { STATE_SECURE_MED = 65536U };

  enum { STATE_SECURE_LOW = 131072U }; 02 00 00

  enum { STATE_IDENTITY_EV_TOPLEVEL = 1048576U }; 00 10 00 00 = 0001.0000 0000.0000 0000.0000

 2097152U = 20 00 00 = 0010.0000 0000.0000 0000.0000

  STATE_STOP | STATE_IS_NETWORK | STATE_IS_WINDOW

 */

