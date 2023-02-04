#ifndef _WEBBROWSE_DEFAULT_CONTENT_LISTENER_H_ 
#define _WEBBROWSE_DEFAULT_CONTENT_LISTENER_H_

//#include <boost/shared_ptr.hpp>
#include <nsIURIContentListener.h>
#include <nsWeakReference.h>
#include <nsIWebBrowser.h>
#include <nsIWebNavigation.h>

namespace crawl {
    class WebBrowserIF;
}
class WebNavigation;

class DefaultURIContentListener : public nsIURIContentListener,
			public nsSupportsWeakReference
{
public:

	DefaultURIContentListener( crawl::WebBrowserIF& mozBrowser, nsCOMPtr<nsIWebBrowser> pIWebBrowser );
	virtual ~DefaultURIContentListener();

	NS_DECL_ISUPPORTS
	NS_DECL_NSIURICONTENTLISTENER

private:
	crawl::WebBrowserIF& 						m_mozBrowser; 
	nsCOMPtr<nsIWebNavigation>    		m_pNavigation;
	
};

#endif // _WEBBROWSE_DEFAULT_CONTENT_LISTENER_H_
