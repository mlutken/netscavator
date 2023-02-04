#ifndef _TEST_CREATOR_BROWSER_FRAME_H_
#define _TEST_CREATOR_BROWSER_FRAME_H_

#include <hacks/wx_h_include_hack.h>
#include <nsIWebBrowserChrome.h>
#include <nsIEmbeddingSiteWindow.h>
#include <nsIWebBrowser.h>

#include <nsIBaseWindow.h>
#include <utils/webbrowse_embedding_utils.h>
#include <webbrwsr/DefaultChromeEmbed.h>

class TestCreatorBrowserFrame : public wxFrame
{
public:
	TestCreatorBrowserFrame ( const wxString& title	);

	void	initWebBrowser( nsCOMPtr<nsIWebBrowser> pIWebBrowser );	


	// Event handlers (these functions should _not_ be virtual)
	void	OnActivate	( wxActivateEvent &event 	);
	void 	OnSize		( wxSizeEvent &event		);
    void	OnQuit		( wxCommandEvent& event		);
    void	OnAbout		( wxCommandEvent& event		);

private:
	nsCOMPtr<nsIWebBrowser>		m_pIWebBrowser;
	nsCOMPtr<nsIBaseWindow> 	m_pIBaseWindow;

	// any class wishing to process wxWidgets events must use this macro
	DECLARE_EVENT_TABLE()
};


// IDs for the controls and the menu commands
enum
{
    Action_Quit = wxID_EXIT,
    Action_About = wxID_ABOUT
};


#endif // _TEST_CREATOR_BROWSER_FRAME_H_

