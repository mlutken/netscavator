
#include <iostream>
#include <nsComponentManagerUtils.h>
#include <nsEmbedCID.h>
#include <nsIDOMWindow.h>
#include <nsIInterfaceRequestorUtils.h>
#include <nsISupportsImpl.h>
#include <nsIWebBrowser.h>
#include <nsIWebBrowserFocus.h>
#include <nsIDocShellTreeItem.h>
#include <nsIWebNavigation.h>
#include <nsIWidget.h>

#include "DefaultChromeEmbed.h"

#include <utils/webbrowse_embedding_utils.h>
#include <utils/mozilla_strings.h>
#include <dom/DOMNode.h>
#include <dom/DOMEvent.h>
#include <SignalsManager.h>
#include <DomEventIF.h>


// DefaultChromeEmbed::DefaultChromeEmbed() :
// 	m_NativeWindow(nsnull),
// 	mFocusCallback(nsnull),
// 	mFocusCallbackData(nsnull)
// {
// 	this->AddRef();
// 
// 	nsresult rv;
// 	m_pIWebBrowser = do_CreateInstance ( NS_WEBBROWSER_CONTRACTID, &rv );
// 	m_pIBaseWindow = do_QueryInterface ( m_pIWebBrowser ) ;
// }

DefaultChromeEmbed::DefaultChromeEmbed(
        crawl::WebBrowserIF*  pWebBrowser
        , nsCOMPtr<nsIWebBrowser> pIWebBrowser
        , boost::shared_ptr<SignalsManager> pSignalsManager ) :
        m_pWebBrowserRawPtr(pWebBrowser)
        , m_pIWebBrowser(pIWebBrowser)
        , m_NativeWindow(nsnull)
        , m_pSignalsManager(pSignalsManager)
        , mFocusCallback(nsnull)
        , mFocusCallbackData(nsnull)
{
	this->AddRef();

    //	nsresult rv;
	m_pIBaseWindow = do_QueryInterface ( m_pIWebBrowser ) ;
}

DefaultChromeEmbed::~DefaultChromeEmbed()
{
	printf ( "destroying DefaultChromeEmbed\n" );
}


/// Destroy the broswer
void DefaultChromeEmbed::destroy()
{
	nsCOMPtr<nsIBaseWindow> browserBaseWindow ( do_QueryInterface ( m_pIWebBrowser ) );
	browserBaseWindow->Destroy();
}

/// Load a URI into the browser
nsresult DefaultChromeEmbed::loadURI ( const char* uri )
{
	nsCOMPtr<nsIWebNavigation> webNavigation (  do_QueryInterface ( m_pIWebBrowser ) );
	if ( !webNavigation ) return NS_ERROR_FAILURE;
	webNavigation->LoadURI ( NS_ConvertASCIItoUTF16 ( uri ).get(), nsIWebNavigation::LOAD_FLAGS_NONE, 0, 0, 0 );
	return NS_OK;
}

/// Call when the parent window changes size
nsresult DefaultChromeEmbed::resize ( int x, int y, int width, int height )
{
	printf("DefaultChromeEmbed::resize\n");
	nsCOMPtr<nsIBaseWindow>browserBaseWindow ( do_QueryInterface ( m_pIWebBrowser ) );
	if ( !browserBaseWindow ) return NS_ERROR_FAILURE;
	return browserBaseWindow->SetPositionAndSize ( x, y, width, height, PR_TRUE );
}

/// Give the browser keyboard focus
nsresult DefaultChromeEmbed::focus()
{
	nsCOMPtr<nsIWebBrowserFocus> browserFocus ( do_GetInterface ( m_pIWebBrowser ) );
	if ( !browserFocus ) return NS_ERROR_FAILURE;
	return browserFocus->Activate();
}

/// Set the focus callback.  This will be called when the user tabs through
/// all the elements in the browser and the next Widget should be given
/// focus.
void DefaultChromeEmbed::setFocusCallback ( focusCallback callback, void* data )
{
	mFocusCallback 		= callback;
	mFocusCallbackData 	= data;
}

//*****************************************************************************
// DefaultChromeEmbed::nsISupports
//*****************************************************************************

NS_IMPL_ADDREF ( DefaultChromeEmbed )
        NS_IMPL_RELEASE ( DefaultChromeEmbed )

        NS_INTERFACE_MAP_BEGIN ( DefaultChromeEmbed )
        NS_INTERFACE_MAP_ENTRY_AMBIGUOUS ( nsISupports, nsIWebBrowserChrome )
        NS_INTERFACE_MAP_ENTRY ( nsIWebBrowserChrome )
        NS_INTERFACE_MAP_ENTRY ( nsIEmbeddingSiteWindow )
        NS_INTERFACE_MAP_ENTRY ( nsIInterfaceRequestor )
        NS_INTERFACE_MAP_ENTRY ( nsIWebBrowserChromeFocus )
        NS_INTERFACE_MAP_ENTRY ( nsIContextMenuListener )
        NS_INTERFACE_MAP_END


        //*****************************************************************************
        // DefaultChromeEmbed::nsIWebBrowserChrome
        //*****************************************************************************

        NS_IMETHODIMP DefaultChromeEmbed::SetStatus ( PRUint32 aType, const PRUnichar* aStatus )
{
	return NS_OK;
}

NS_IMETHODIMP DefaultChromeEmbed::GetWebBrowser ( nsIWebBrowser** aWebBrowser )
{
	NS_ENSURE_ARG_POINTER ( aWebBrowser );
	*aWebBrowser = m_pIWebBrowser;
	NS_IF_ADDREF ( *aWebBrowser );
	return NS_OK;
}

NS_IMETHODIMP DefaultChromeEmbed::SetWebBrowser ( nsIWebBrowser* aWebBrowser )
{
	m_pIWebBrowser = aWebBrowser;
	return NS_OK;
}

NS_IMETHODIMP DefaultChromeEmbed::GetChromeFlags ( PRUint32* aChromeMask )
{
	*aChromeMask = mChromeFlags;
	return NS_OK;
}

NS_IMETHODIMP DefaultChromeEmbed::SetChromeFlags ( PRUint32 aChromeMask )
{
	mChromeFlags = aChromeMask;
	return NS_OK;
}

NS_IMETHODIMP DefaultChromeEmbed::DestroyBrowserWindow ( void )
{
    // 	fprintf ( stderr, "DestroyBrowserWindow() not implemented\n" );
	printf ( "DestroyBrowserWindow() not implemented\n" );
	return NS_OK;
}


// IN: The desired browser client area dimensions.
NS_IMETHODIMP DefaultChromeEmbed::SizeBrowserTo ( PRInt32 aWidth, PRInt32 aHeight )
{
	printf("DefaultChromeEmbed::SizeBrowserTo\n");
	return NS_OK;
}


NS_IMETHODIMP DefaultChromeEmbed::ShowAsModal ( void )
{
	mContinueModalLoop = PR_TRUE;
	//AppCallbacks::RunEventLoop(mContinueModalLoop);

	return NS_OK;
}

NS_IMETHODIMP DefaultChromeEmbed::IsWindowModal ( PRBool *_retval )
{
	*_retval = PR_FALSE;
	return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP DefaultChromeEmbed::ExitModalEventLoop ( nsresult aStatus )
{
	mContinueModalLoop = PR_FALSE;
	return NS_OK;
}


//*****************************************************************************
// DefaultChromeEmbed::nsIWebBrowserChromeFocus
//*****************************************************************************
NS_IMETHODIMP DefaultChromeEmbed::FocusNextElement()
{
	if ( mFocusCallback ) mFocusCallback ( PR_TRUE, mFocusCallbackData );
	return NS_OK;
}

NS_IMETHODIMP DefaultChromeEmbed::FocusPrevElement()
{
	if ( mFocusCallback ) mFocusCallback ( PR_FALSE, mFocusCallbackData );
	return NS_OK;
}


//*****************************************************************************
// DefaultChromeEmbed::nsIEmbeddingSiteWindow
//*****************************************************************************

NS_IMETHODIMP DefaultChromeEmbed::SetDimensions ( PRUint32 aFlags, PRInt32 x, PRInt32 y, PRInt32 cx, PRInt32 cy )
{
	printf("DefaultChromeEmbed::SetDimensions\n");
	return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP DefaultChromeEmbed::GetDimensions ( PRUint32 aFlags, PRInt32 *x, PRInt32 *y, PRInt32 *cx, PRInt32 *cy )
{
	if ( aFlags & nsIEmbeddingSiteWindow::DIM_FLAGS_POSITION )
	{
		*x = 0;
		*y = 0;
	}
	if ( aFlags & nsIEmbeddingSiteWindow::DIM_FLAGS_SIZE_INNER ||
         aFlags & nsIEmbeddingSiteWindow::DIM_FLAGS_SIZE_OUTER )
	{
		*cx = 0;
		*cy = 0;
	}
	return NS_ERROR_NOT_IMPLEMENTED;
}

/* void setFocus (); */
NS_IMETHODIMP DefaultChromeEmbed::SetFocus()
{
	printf("DefaultChromeEmbed::SetFocus\n");
	return NS_OK;
}

/* attribute wstring title; */
NS_IMETHODIMP DefaultChromeEmbed::GetTitle ( PRUnichar * *aTitle )
{
	NS_ENSURE_ARG_POINTER ( aTitle );

	*aTitle = nsnull;

	return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP DefaultChromeEmbed::SetTitle ( const PRUnichar * aTitle )
{
	return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute boolean visibility; */
NS_IMETHODIMP DefaultChromeEmbed::GetVisibility ( PRBool * aVisibility )
{
	NS_ENSURE_ARG_POINTER ( aVisibility );
	*aVisibility = PR_TRUE;
	return NS_OK;
}
NS_IMETHODIMP DefaultChromeEmbed::SetVisibility ( PRBool aVisibility )
{
	return NS_OK;
}

/* attribute nativeSiteWindow siteWindow */
NS_IMETHODIMP DefaultChromeEmbed::GetSiteWindow ( void * *aSiteWindow )
{
	NS_ENSURE_ARG_POINTER ( aSiteWindow );

	*aSiteWindow = m_NativeWindow;
	return NS_OK;
}


//*****************************************************************************
// DefaultChromeEmbed::nsIInterfaceRequestor
//*****************************************************************************

NS_IMETHODIMP DefaultChromeEmbed::GetInterface ( const nsIID &aIID, void** aInstancePtr )
{
	NS_ENSURE_ARG_POINTER ( aInstancePtr );

	*aInstancePtr = 0;
	if ( aIID.Equals ( NS_GET_IID ( nsIDOMWindow ) ) )
	{
		if ( m_pIWebBrowser )
		{
			return m_pIWebBrowser->GetContentDOMWindow ( ( nsIDOMWindow ** ) aInstancePtr );
		}
		return NS_ERROR_NOT_INITIALIZED;
	}
	return QueryInterface ( aIID, aInstancePtr );
}

//*****************************************************************************
// DefaultChromeEmbed::nsIContextMenuListener
//*****************************************************************************

NS_IMETHODIMP DefaultChromeEmbed::OnShowContextMenu (
        PRUint32 aContextFlags,
        nsIDOMEvent *aEvent,
        nsIDOMNode *aNode)
{
	if ( m_pSignalsManager ) {
        ////		boost::shared_ptr<DOMEvent> e(new DOMEvent(aEvent));
        boost::shared_ptr<crawl::DomEventIF> pDOMEvent(new crawl::DomEventIF());
        boost::shared_ptr<DOMNode> n(new DOMNode(aNode));
        boost::shared_ptr<crawl::DomNodeIF> pDOMNode = mkMozDomNode(n, m_pWebBrowserRawPtr->shared_from_this() );

        m_pSignalsManager->signalContextMenu( aContextFlags, pDOMEvent, pDOMNode );
	}
    return NS_OK;
}


void addref ( DefaultChromeEmbed* browser )
{
	NS_ADDREF ( browser );
}
void release ( DefaultChromeEmbed* browser )
{
	NS_RELEASE ( browser );
}





#if WEBBROWSE_ENABLE_GTK
nsresult DefaultChromeEmbed::initNativeWindow ( GtkWidget* parentWindow, int x,
                                                int y, int width, int height )
{
	printf("INIT Gtk\n");
	return ::initNativeWindow ( m_pIWebBrowser, this, parentWindow, x, y, width, height );
}
#endif //#if WEBBROWSE_ENABLE_GTK

#if WEBBROWSE_ENABLE_WX
nsresult DefaultChromeEmbed::initNativeWindow ( wxWindow* parentWindow, int x,
                                                int y, int width, int height )
{
	printf("INIT wxWidgets\n");
	return ::initNativeWindow ( m_pIWebBrowser, this, parentWindow, x, y, width, height );
}
#endif //#if WEBBROWSE_ENABLE_WX
