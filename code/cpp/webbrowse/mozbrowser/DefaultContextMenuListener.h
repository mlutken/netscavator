#ifndef _WEBBROWSE_DEFAULT_CONTEXT_MENU_LISTENER_H_ 
#define _WEBBROWSE_DEFAULT_CONTEXT_MENU_LISTENER_H_

// #include <nsWeakReference.h>
#include <nsIWebBrowser.h>
#include <nsIContextMenuListener.h>

namespace crawl {
    class WebBrowserIF;
}

class DefaultContextMenuListener : public nsIContextMenuListener
// 			,public nsSupportsWeakReference
{

public:

	DefaultContextMenuListener( crawl::WebBrowserIF& mozBrowser);
	virtual ~DefaultContextMenuListener();

public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSICONTEXTMENULISTENER

private:
	crawl::WebBrowserIF& 						m_mozBrowser; 
// // 	nsCOMPtr<nsIWebNavigation>    		m_pNavigation;
	
};

#endif // _WEBBROWSE_DEFAULT_CONTEXT_MENU_LISTENER_H_
