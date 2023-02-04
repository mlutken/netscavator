#include "TestCreatorBrowserFrame.h"

BEGIN_EVENT_TABLE ( TestCreatorBrowserFrame, wxFrame )
	EVT_ACTIVATE ( TestCreatorBrowserFrame::OnActivate )
	EVT_SIZE ( TestCreatorBrowserFrame::OnSize )
    EVT_MENU(Action_Quit,  TestCreatorBrowserFrame::OnQuit)
    EVT_MENU(Action_About, TestCreatorBrowserFrame::OnAbout)
END_EVENT_TABLE()

TestCreatorBrowserFrame::TestCreatorBrowserFrame ( const wxString& title ) 
: 	wxFrame ( NULL, wxID_ANY, title ),
	m_pIWebBrowser( 0 )
{
	printf("SSSSSSSSSSSSSSSSSSSS\n");
    // create a menu bar
    wxMenu *fileMenu = new wxMenu;

    // the "About" item should be in the help menu
    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(Action_About, _T("&About...\tF1"), _T("Show about dialog"));

    fileMenu->Append(Action_Quit, _T("E&xit\tAlt-X"), _T("Quit this program"));

    // now append the freshly created menu to the menu bar...
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, _T("&File"));
    menuBar->Append(helpMenu, _T("&Help"));

    // ... and attach this menu bar to the frame
    SetMenuBar(menuBar);
    // create a status bar just for fun (by default with 1 pane only)
    CreateStatusBar(2);
    SetStatusText(_T("Test creator statusbar!"), 0);
    SetStatusText(_T("Felt 2!"), 1);
}



void TestCreatorBrowserFrame::initWebBrowser( 
	nsCOMPtr<nsIWebBrowser> pIWebBrowser )
{
	m_pIWebBrowser = pIWebBrowser;
	if ( ! m_pIWebBrowser )	return;
	m_pIBaseWindow = do_QueryInterface ( m_pIWebBrowser ) ;
}



void TestCreatorBrowserFrame::OnActivate( wxActivateEvent &event )
{
	printf("TestCreatorBrowserFrame::OnActivate\n");
	if ( m_pIBaseWindow ) {
		wxRect newRect = this->GetClientRect();
		m_pIBaseWindow->SetPositionAndSize ( 
				newRect.GetLeft(), newRect.GetTop(),
		        newRect.GetWidth(), newRect.GetHeight(), 
				PR_FALSE );
	}
}


void TestCreatorBrowserFrame::OnSize ( wxSizeEvent &event )
{
	printf("TestCreatorBrowserFrame::OnSize\n");
	if ( m_pIBaseWindow ) {
		wxRect newRect = this->GetClientRect();
		m_pIBaseWindow->SetPositionAndSize ( 
				newRect.GetLeft(), newRect.GetTop(),
		        newRect.GetWidth(), newRect.GetHeight(), 
				PR_FALSE );
	}
}


void TestCreatorBrowserFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    // true is to force the frame to close
    Close(true);
}

void TestCreatorBrowserFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox(wxString::Format(
                    _T("Welcome to %s!\n")
                    _T("\n")
                    _T("This is the test miner creator\n")
                    _T("running under %s."),
                    wxVERSION_STRING,
                    wxGetOsDescription().c_str()
                 ),
                 _T("About Test creator"),
                 wxOK | wxICON_INFORMATION,
                 this);
}
