#include <stdio.h>
#include <string>
#include <utils/string_conversion.h>
#include <WebBrowserIF.h>
#include "DefaultContextMenuListener.h"



DefaultContextMenuListener::DefaultContextMenuListener ( 
	crawl::WebBrowserIF& mozBrowser
// // 	,nsCOMPtr<nsIWebBrowser> pIWebBrowser
)	:
	m_mozBrowser( mozBrowser )
// // 	,m_pNavigation ( do_QueryInterface ( pIWebBrowser ) )
{
}

DefaultContextMenuListener::~DefaultContextMenuListener()
{
}

NS_IMPL_ISUPPORTS1 ( DefaultContextMenuListener,
                     nsIContextMenuListener
//                      ,nsISupportsWeakReference 
                     )


NS_IMETHODIMP DefaultContextMenuListener::OnShowContextMenu (
	PRUint32 aContextFlags, 
	nsIDOMEvent *aEvent, 
	nsIDOMNode *aNode)
{
	printf("DefaultContextMenuListener::OnShowContextMenu\n");
    return NS_ERROR_NOT_IMPLEMENTED;
}
