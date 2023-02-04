#ifndef _WEBBROWSE_DEFAULT_WX_BROWSER_FRAME_H_
#define _WEBBROWSE_DEFAULT_WX_BROWSER_FRAME_H_

#include <hacks/wx_h_include_hack.h>
#include <boost/weak_ptr.hpp>
#include <nsIWebBrowserChrome.h>
#include <nsIEmbeddingSiteWindow.h>
#include <nsIWebBrowser.h>

#include <nsIBaseWindow.h>
#include <utils/webbrowse_embedding_utils.h>
#include <webbrwsr/DefaultChromeEmbed.h>

namespace crawl {
    class WebBrowserIF;
}

class DefaultWxBrowserFrame : public wxFrame
{
public:
	DefaultWxBrowserFrame ( const wxString& title, nsCOMPtr<nsIWebBrowser>  pIWebBrowser, crawl::WebBrowserIF* pMozBrowser );

	// Event handlers (these functions should _not_ be virtual)
	void 	sendTestEvent();
	void	OnActivate		( wxActivateEvent &event 		);
	void 	OnSize			( wxSizeEvent &event			);
    void 	OnPaint			( wxPaintEvent& WXUNUSED(evt)	);
	void 	OnCloseHandler	( wxCloseEvent& event			);
	void	mozBrowserSet	( crawl::WebBrowserIF* pMozBrowser		);

private:
	nsCOMPtr<nsIWebBrowser>		m_pIWebBrowser;
	nsCOMPtr<nsIBaseWindow> 	m_pIBaseWindow;
	crawl::WebBrowserIF*					m_pMozBrowser;

	// any class wishing to process wxWidgets events must use this macro
	DECLARE_EVENT_TABLE()
};


#endif // _WEBBROWSE_DEFAULT_WX_BROWSER_FRAME_H_ 
