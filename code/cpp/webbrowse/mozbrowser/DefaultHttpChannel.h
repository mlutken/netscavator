#ifndef _WEBBROWSE_DEFAULT_HTTP_CHANNEL_H_
#define _WEBBROWSE_DEFAULT_HTTP_CHANNEL_H_

#include <nsIHttpChannel.h>
#include <nsWeakReference.h>
#include <nsIWebBrowser.h>
#include <nsIWebNavigation.h>

namespace crawl {
    class WebBrowserIF;
}

class WebNavigation;

class DefaultHttpChannel : public nsIHttpChannel
        ,public nsSupportsWeakReference
{
public:
    NS_DECL_ISUPPORTS
    NS_DECL_NSIHTTPCHANNEL


    DefaultHttpChannel( crawl::WebBrowserIF& mozBrowser );
    virtual ~DefaultHttpChannel();


private:
	static void requestToURIString ( nsIRequest *aRequest, nsACString &aString );
	
	// --- Data ---
	crawl::WebBrowserIF& 						m_mozBrowser; 
};

#endif // _WEBBROWSE_DEFAULT_HTTP_CHANNEL_H_
