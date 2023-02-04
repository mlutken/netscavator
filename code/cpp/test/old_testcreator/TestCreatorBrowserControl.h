#ifndef _TEST_CREATOR_BROWSER_CONTROL_H_
#define _TEST_CREATOR_BROWSER_CONTROL_H_

#include <hacks/wx_h_include_hack.h>
#include <nsIWebBrowserChrome.h>
#include <nsIEmbeddingSiteWindow.h>
#include <nsIWebBrowser.h>

#include <nsIBaseWindow.h>
#include <utils/webbrowse_embedding_utils.h>
#include <webbrwsr/DefaultChromeEmbed.h>

class TestCreatorBrowserControl : public wxControl
{
public:
	TestCreatorBrowserControl ( wxWindow* parent, wxWindowID id = wxID_ANY,
                     const wxPoint& pos = wxDefaultPosition,
                     const wxSize& size = wxDefaultSize );

	void	initWebBrowser( nsCOMPtr<nsIWebBrowser> pIWebBrowser );	

	// Event handlers (these functions should _not_ be virtual)
	void	OnActivate	( wxActivateEvent &event 		);
	void 	OnSize		( wxSizeEvent &event			);
    void 	OnPaint		( wxPaintEvent& WXUNUSED(evt)	);

private:
	nsCOMPtr<nsIWebBrowser>		m_pIWebBrowser;
	nsCOMPtr<nsIBaseWindow> 	m_pIBaseWindow;

	// any class wishing to process wxWidgets events must use this macro
	DECLARE_EVENT_TABLE()
};



#endif // _TEST_CREATOR_BROWSER_CONTROL_H_

