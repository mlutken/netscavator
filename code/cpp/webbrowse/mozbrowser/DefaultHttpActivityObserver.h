#ifndef _WEBBROWSE_DEFAULT_HTTP_ACTIVITY_OBSERVER_H_
#define _WEBBROWSE_DEFAULT_HTTP_ACTIVITY_OBSERVER_H_

#include <nsIHttpActivityObserver.h>
#include <nsWeakReference.h>

namespace crawl {
    class WebBrowserIF;
}

class DefaultHttpActivityObserver : public nsIHttpActivityObserver
                                    //,public nsISupportsWeakReference
                                    ,public nsSupportsWeakReference
{
public:
    DefaultHttpActivityObserver( crawl::WebBrowserIF* pMozBrowser );
    virtual ~DefaultHttpActivityObserver();
    void     ResetCounters();

    NS_DECL_ISUPPORTS
    NS_DECL_NSIHTTPACTIVITYOBSERVER

private:
	
	// --- Data ---
    crawl::WebBrowserIF* 	m_pMozBrowser;
    int             m_iCount_REQUEST_HEADER;
    int             m_iCount_REQUEST_BODY_SENT;
    int             m_iCount_RESPONSE_START;
    int             m_iCount_RESPONSE_HEADER;
    int             m_iCount_RESPONSE_COMPLETE;
    int             m_iCount_TRANSACTION_CLOSE;

    int             m_iCount_RESOLVING;
    int             m_iCount_CONNECTING_TO;
    int             m_iCount_CONNECTED_TO;
    int             m_iCount_SENDING_TO;
    int             m_iCount_WAITING_FOR;
    int             m_iCount_RECEIVING_FROM;
    unsigned int    m_iCount_ACTIVITY_ANY;


};

#endif // _WEBBROWSE_DEFAULT_HTTP_ACTIVITY_OBSERVER_H_
