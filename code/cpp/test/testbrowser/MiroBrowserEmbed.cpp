
//#include <stdio.h>
//#include "windows.h"
#include "nsCOMPtr.h"
#include "nsComponentManagerUtils.h"
#include "nsEmbedCID.h"
#include "nsEmbedString.h"
#include "nsIDOMWindow.h"
#include "nsIInterfaceRequestorUtils.h"
#include "nsISupportsImpl.h"
#include "nsIWebBrowser.h"
#include "nsIWebBrowserFocus.h"
#include "nsIDocShellTreeItem.h"
#include "nsIWebNavigation.h"
#include "nsIWidget.h"

#include "MiroBrowserEmbed.h"
//#include "FixFocus.h"

#include <utils/webbrowse_embedding_utils.h>

MiroBrowserEmbed::MiroBrowserEmbed()
{
	this->AddRef();
	mWindow = nsnull;
	mFocusCallback = nsnull;
}

MiroBrowserEmbed::~MiroBrowserEmbed()
{
	fprintf ( stderr, "destroying MiroBrowserEmbed\n" );
}

nsresult MiroBrowserEmbed::init ( GtkWidget* parentWindow, int x,
                                  int y, int width, int height )
{
	printf("INIT Gtk\n");
	nsresult rv;
	mWebBrowser = do_CreateInstance ( NS_WEBBROWSER_CONTRACTID, &rv );
	NS_ENSURE_SUCCESS ( rv, rv );
	mBrowserBaseWindow = do_QueryInterface ( mWebBrowser ) ;
	return initNativeWindow ( mWebBrowser, this, parentWindow, x, y, width, height );
}


nsresult MiroBrowserEmbed::init ( wxWindow* parentWindow, int x,
                                  int y, int width, int height )
{
	printf("INIT wxWidgets\n");
	nsresult rv;
	mWebBrowser = do_CreateInstance ( NS_WEBBROWSER_CONTRACTID, &rv );
	NS_ENSURE_SUCCESS ( rv, rv );
	mBrowserBaseWindow = do_QueryInterface ( mWebBrowser ) ;
	return initNativeWindow ( mWebBrowser, this, parentWindow, x, y, width, height );
}


void MiroBrowserEmbed::destroy()
{
	nsCOMPtr<nsIBaseWindow> browserBaseWindow ( do_QueryInterface ( mWebBrowser ) );
	browserBaseWindow->Destroy();
}

// Load a URI into the browser
nsresult MiroBrowserEmbed::loadURI ( const char* uri )
{
	nsCOMPtr<nsIWebNavigation> webNavigation (
	    do_QueryInterface ( mWebBrowser ) );
	if ( !webNavigation ) return NS_ERROR_FAILURE;
	webNavigation->LoadURI ( NS_ConvertASCIItoUTF16 ( uri ).get(),
	                         nsIWebNavigation::LOAD_FLAGS_NONE, 0, 0, 0 );
	return NS_OK;
}

// Called when the parent window changes size
nsresult MiroBrowserEmbed::resize ( int x, int y, int width, int height )
{
	nsCOMPtr<nsIBaseWindow>browserBaseWindow (
	    do_QueryInterface ( mWebBrowser ) );
	if ( !browserBaseWindow ) return NS_ERROR_FAILURE;
	return browserBaseWindow->SetPositionAndSize ( x, y, width, height,
	        PR_TRUE );
}

// Give the browser keyboard focus
nsresult MiroBrowserEmbed::focus()
{
	nsCOMPtr<nsIWebBrowserFocus> browserFocus (
	    do_GetInterface ( mWebBrowser ) );
	if ( !browserFocus ) return NS_ERROR_FAILURE;
	return browserFocus->Activate();
}

// Set the focus callback.  This will be called when the user tabs through all
// the elements in the browser and the next Widget should be given focus.
void MiroBrowserEmbed::SetFocusCallback ( focusCallback callback, void* data )
{
	mFocusCallback = callback;
	mFocusCallbackData = data;
}

//*****************************************************************************
// MiroBrowserEmbed::nsISupports
//*****************************************************************************

NS_IMPL_ADDREF ( MiroBrowserEmbed )
NS_IMPL_RELEASE ( MiroBrowserEmbed )

NS_INTERFACE_MAP_BEGIN ( MiroBrowserEmbed )
NS_INTERFACE_MAP_ENTRY_AMBIGUOUS ( nsISupports, nsIWebBrowserChrome )
NS_INTERFACE_MAP_ENTRY ( nsIWebBrowserChrome )
NS_INTERFACE_MAP_ENTRY ( nsIEmbeddingSiteWindow )
NS_INTERFACE_MAP_ENTRY ( nsIInterfaceRequestor )
NS_INTERFACE_MAP_ENTRY ( nsIWebBrowserChromeFocus )
NS_INTERFACE_MAP_END


//*****************************************************************************
// MiroBrowserEmbed::nsIWebBrowserChrome
//*****************************************************************************

NS_IMETHODIMP MiroBrowserEmbed::SetStatus ( PRUint32 aType, const PRUnichar* aStatus )
{

	return NS_OK;
}

NS_IMETHODIMP MiroBrowserEmbed::GetWebBrowser ( nsIWebBrowser** aWebBrowser )
{
	NS_ENSURE_ARG_POINTER ( aWebBrowser );
	*aWebBrowser = mWebBrowser;
	NS_IF_ADDREF ( *aWebBrowser );
	return NS_OK;
}

NS_IMETHODIMP MiroBrowserEmbed::SetWebBrowser ( nsIWebBrowser* aWebBrowser )
{
	mWebBrowser = aWebBrowser;
	return NS_OK;
}

NS_IMETHODIMP MiroBrowserEmbed::GetChromeFlags ( PRUint32* aChromeMask )
{
	*aChromeMask = mChromeFlags;
	return NS_OK;
}

NS_IMETHODIMP MiroBrowserEmbed::SetChromeFlags ( PRUint32 aChromeMask )
{
	mChromeFlags = aChromeMask;
	return NS_OK;
}

NS_IMETHODIMP MiroBrowserEmbed::DestroyBrowserWindow ( void )
{
	fprintf ( stderr, "DestroyBrowserWindow() not implemented\n" );
	return NS_OK;
}


// IN: The desired browser client area dimensions.
NS_IMETHODIMP MiroBrowserEmbed::SizeBrowserTo ( PRInt32 aWidth, PRInt32 aHeight )
{
	return NS_OK;
}


NS_IMETHODIMP MiroBrowserEmbed::ShowAsModal ( void )
{
	mContinueModalLoop = PR_TRUE;
	//AppCallbacks::RunEventLoop(mContinueModalLoop);

	return NS_OK;
}

NS_IMETHODIMP MiroBrowserEmbed::IsWindowModal ( PRBool *_retval )
{
	*_retval = PR_FALSE;
	return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP MiroBrowserEmbed::ExitModalEventLoop ( nsresult aStatus )
{
	mContinueModalLoop = PR_FALSE;
	return NS_OK;
}


//*****************************************************************************
// MiroBrowserEmbed::nsIWebBrowserChromeFocus
//*****************************************************************************
NS_IMETHODIMP MiroBrowserEmbed::FocusNextElement()
{
	if ( mFocusCallback ) mFocusCallback ( PR_TRUE, mFocusCallbackData );
	return NS_OK;
}

NS_IMETHODIMP MiroBrowserEmbed::FocusPrevElement()
{
	if ( mFocusCallback ) mFocusCallback ( PR_FALSE, mFocusCallbackData );
	return NS_OK;
}


//*****************************************************************************
// MiroBrowserEmbed::nsIEmbeddingSiteWindow
//*****************************************************************************

NS_IMETHODIMP MiroBrowserEmbed::SetDimensions ( PRUint32 aFlags, PRInt32 x, PRInt32 y, PRInt32 cx, PRInt32 cy )
{
	return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP MiroBrowserEmbed::GetDimensions ( PRUint32 aFlags, PRInt32 *x, PRInt32 *y, PRInt32 *cx, PRInt32 *cy )
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
NS_IMETHODIMP MiroBrowserEmbed::SetFocus()
{
	return NS_OK;
}

/* attribute wstring title; */
NS_IMETHODIMP MiroBrowserEmbed::GetTitle ( PRUnichar * *aTitle )
{
	NS_ENSURE_ARG_POINTER ( aTitle );

	*aTitle = nsnull;

	return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP MiroBrowserEmbed::SetTitle ( const PRUnichar * aTitle )
{
	return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute boolean visibility; */
NS_IMETHODIMP MiroBrowserEmbed::GetVisibility ( PRBool * aVisibility )
{
	NS_ENSURE_ARG_POINTER ( aVisibility );
	*aVisibility = PR_TRUE;
	return NS_OK;
}
NS_IMETHODIMP MiroBrowserEmbed::SetVisibility ( PRBool aVisibility )
{
	return NS_OK;
}

/* attribute nativeSiteWindow siteWindow */
NS_IMETHODIMP MiroBrowserEmbed::GetSiteWindow ( void * *aSiteWindow )
{
	NS_ENSURE_ARG_POINTER ( aSiteWindow );

	*aSiteWindow = mWindow;
	return NS_OK;
}


//*****************************************************************************
// MiroBrowserEmbed::nsIInterfaceRequestor
//*****************************************************************************

NS_IMETHODIMP MiroBrowserEmbed::GetInterface ( const nsIID &aIID, void** aInstancePtr )
{
	NS_ENSURE_ARG_POINTER ( aInstancePtr );

	*aInstancePtr = 0;
	if ( aIID.Equals ( NS_GET_IID ( nsIDOMWindow ) ) )
	{
		if ( mWebBrowser )
		{
			return mWebBrowser->GetContentDOMWindow ( ( nsIDOMWindow ** ) aInstancePtr );
		}
		return NS_ERROR_NOT_INITIALIZED;
	}
	return QueryInterface ( aIID, aInstancePtr );
}

void addref ( MiroBrowserEmbed* browser )
{
	NS_ADDREF ( browser );
}
void release ( MiroBrowserEmbed* browser )
{
	NS_RELEASE ( browser );
}
