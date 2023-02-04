
#include "nsMemory.h"
#include "nsComponentManagerUtils.h"
#include "nsCWebBrowser.h"
#include "nsIComponentManager.h"
#include "nsIDocShellTreeItem.h"
#include "nsIWidget.h"

#include "MyEmbedWindow.h"
//#include "MyEmbedPrivate.h"


EmbedWindow::EmbedWindow ( void )
{
//	mOwner       = nsnull;
}

EmbedWindow::~EmbedWindow ( void )
{
}

nsresult
EmbedWindow::Init ( )
{
	nsresult rv;

	// create our nsIWebBrowser object and set up some basic defaults.
	mWebBrowser = do_CreateInstance(NS_WEBBROWSER_CONTRACTID, &rv);
	if (NS_FAILED(rv)) printf("Error: do_CreateInstance webBrowser\n");

	mWebBrowser->SetContainerWindow ( static_cast<nsIWebBrowserChrome *> ( this ) );

	nsCOMPtr<nsIDocShellTreeItem> item = do_QueryInterface ( mWebBrowser );
	item->SetItemType ( nsIDocShellTreeItem::typeContentWrapper );

	return NS_OK;
}

nsresult
EmbedWindow::CreateWindow ( GtkWidget* pOwningWidget )
{
	nsresult rv;
//	GtkWidget *ownerAsWidget = GTK_WIDGET(pOwningWidget);
	GtkWidget *ownerAsWidget = pOwningWidget;
	
	// Get the base window interface for the web browser object and
	// create the window.
	mBaseWindow = do_QueryInterface(mWebBrowser);
	rv = mBaseWindow->InitWindow(ownerAsWidget,
					nsnull,
					0, 0, 
					ownerAsWidget->allocation.width,
					ownerAsWidget->allocation.height);
	if (NS_FAILED(rv))
	return rv;
	
	rv = mBaseWindow->Create();
	if (NS_FAILED(rv))	return rv;
	
	rv = mBaseWindow->SetVisibility(PR_TRUE);
	if (NS_FAILED(rv)) 	printf("Error: SetVisibility\n");

	
	return NS_OK;
}

void
EmbedWindow::ReleaseChildren ( void )
{
	ExitModalEventLoop ( PR_FALSE );

	mBaseWindow->Destroy();
	mBaseWindow = 0;
	mWebBrowser = 0;
}

// nsISupports

NS_IMPL_ADDREF ( EmbedWindow )
NS_IMPL_RELEASE ( EmbedWindow )

NS_INTERFACE_MAP_BEGIN ( EmbedWindow )
NS_INTERFACE_MAP_ENTRY_AMBIGUOUS ( nsISupports, nsIWebBrowserChrome )
NS_INTERFACE_MAP_ENTRY ( nsIWebBrowserChrome )
NS_INTERFACE_MAP_ENTRY ( nsIEmbeddingSiteWindow )
NS_INTERFACE_MAP_END

// nsIWebBrowserChrome

NS_IMETHODIMP
EmbedWindow::SetStatus ( PRUint32 aStatusType, const PRUnichar *aStatus )
{
	return NS_OK;
}

NS_IMETHODIMP
EmbedWindow::GetWebBrowser ( nsIWebBrowser **aWebBrowser )
{
	*aWebBrowser = mWebBrowser;
	NS_IF_ADDREF ( *aWebBrowser );
	return NS_OK;
}

NS_IMETHODIMP
EmbedWindow::SetWebBrowser ( nsIWebBrowser *aWebBrowser )
{
	mWebBrowser = aWebBrowser;
	return NS_OK;
}

NS_IMETHODIMP
EmbedWindow::GetChromeFlags ( PRUint32 *aChromeFlags )
{
//	*aChromeFlags = mOwner->mChromeMask;
	return NS_OK;
}

NS_IMETHODIMP
EmbedWindow::SetChromeFlags ( PRUint32 aChromeFlags )
{
//	mOwner->SetChromeMask ( aChromeFlags );
	return NS_OK;
}

NS_IMETHODIMP
EmbedWindow::DestroyBrowserWindow ( void )
{
/*	// mark the owner as destroyed so it won't emit events anymore.
	mOwner->mIsDestroyed = PR_TRUE;

	g_signal_emit ( G_OBJECT ( mOwner->mOwningWidget ),
					moz_embed_signals[DESTROY_BROWSER], 0 );*/
	return NS_OK;
}

NS_IMETHODIMP
EmbedWindow::SizeBrowserTo ( PRInt32 aCX, PRInt32 aCY )
{
	return NS_OK;
}

NS_IMETHODIMP
EmbedWindow::ShowAsModal ( void )
{
	return NS_OK;
}

NS_IMETHODIMP
EmbedWindow::IsWindowModal ( PRBool *_retval )
{
	*_retval = false;
	return NS_OK;
}

NS_IMETHODIMP
EmbedWindow::ExitModalEventLoop ( nsresult aStatus )
{
	return NS_OK;
}


// nsIEmbeddingSiteWindow

NS_IMETHODIMP
EmbedWindow::SetDimensions ( PRUint32 aFlags, PRInt32 aX, PRInt32 aY,
							 PRInt32 aCX, PRInt32 aCY )
{
	if ( aFlags & nsIEmbeddingSiteWindow::DIM_FLAGS_POSITION &&
			( aFlags & ( nsIEmbeddingSiteWindow::DIM_FLAGS_SIZE_INNER |
						 nsIEmbeddingSiteWindow::DIM_FLAGS_SIZE_OUTER ) ) )
	{
		return mBaseWindow->SetPositionAndSize ( aX, aY, aCX, aCY, PR_TRUE );
	}
	else if ( aFlags & nsIEmbeddingSiteWindow::DIM_FLAGS_POSITION )
	{
		return mBaseWindow->SetPosition ( aX, aY );
	}
	else if ( aFlags & ( nsIEmbeddingSiteWindow::DIM_FLAGS_SIZE_INNER |
						 nsIEmbeddingSiteWindow::DIM_FLAGS_SIZE_OUTER ) )
	{
		return mBaseWindow->SetSize ( aCX, aCY, PR_TRUE );
	}
	return NS_ERROR_INVALID_ARG;
}

NS_IMETHODIMP
EmbedWindow::GetDimensions ( PRUint32 aFlags, PRInt32 *aX,
							 PRInt32 *aY, PRInt32 *aCX, PRInt32 *aCY )
{
	if ( aFlags & nsIEmbeddingSiteWindow::DIM_FLAGS_POSITION &&
			( aFlags & ( nsIEmbeddingSiteWindow::DIM_FLAGS_SIZE_INNER |
						 nsIEmbeddingSiteWindow::DIM_FLAGS_SIZE_OUTER ) ) )
	{
		return mBaseWindow->GetPositionAndSize ( aX, aY, aCX, aCY );
	}
	else if ( aFlags & nsIEmbeddingSiteWindow::DIM_FLAGS_POSITION )
	{
		return mBaseWindow->GetPosition ( aX, aY );
	}
	else if ( aFlags & ( nsIEmbeddingSiteWindow::DIM_FLAGS_SIZE_INNER |
						 nsIEmbeddingSiteWindow::DIM_FLAGS_SIZE_OUTER ) )
	{
		return mBaseWindow->GetSize ( aCX, aCY );
	}
	return NS_ERROR_INVALID_ARG;
}

NS_IMETHODIMP
EmbedWindow::SetFocus ( void )
{
	// XXX might have to do more here.
	return mBaseWindow->SetFocus();
}

NS_IMETHODIMP
EmbedWindow::GetTitle ( PRUnichar **aTitle )
{
	*aTitle = ToNewUnicode ( mTitle );
	return NS_OK;
}

NS_IMETHODIMP
EmbedWindow::SetTitle ( const PRUnichar *aTitle )
{
	return NS_OK;
}

NS_IMETHODIMP
EmbedWindow::GetSiteWindow ( void **aSiteWindow )
{
/*	GtkWidget *ownerAsWidget ( GTK_WIDGET ( mOwner->mOwningWidget ) );
	*aSiteWindow = static_cast<void *> ( ownerAsWidget );*/
	return NS_OK;
}

NS_IMETHODIMP
EmbedWindow::GetVisibility ( PRBool *aVisibility )
{
	// XXX See bug 312998
	// Work around the problem that sometimes the window
	// is already visible even though mVisibility isn't true
	// yet.
	*aVisibility = true;
	return NS_OK;
}

NS_IMETHODIMP
EmbedWindow::SetVisibility ( PRBool aVisibility )
{
/*	// We always set the visibility so that if it's chrome and we finish
	// the load we know that we have to show the window.
	mVisibility = aVisibility;

	// if this is a chrome window and the chrome hasn't finished loading
	// yet then don't show the window yet.
	if ( mOwner->mIsChrome && !mOwner->mChromeLoaded )
		return NS_OK;

	g_signal_emit ( G_OBJECT ( mOwner->mOwningWidget ),
					moz_embed_signals[VISIBILITY], 0,
					aVisibility );*/
	return NS_OK;
}


