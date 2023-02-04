
#include <nsComponentManagerUtils.h>
#include <nsEmbedCID.h>
#include "WebBrowser.h"
	

boost::shared_ptr<WebBrowser>
createWebBrowser()
{
	nsresult rv;
	nsCOMPtr<nsIWebBrowser> pIWebBrowser ( do_CreateInstance ( NS_WEBBROWSER_CONTRACTID, &rv ) );
	return  WebBrowser::Ptr ( new WebBrowser( pIWebBrowser  ) ); 
}

