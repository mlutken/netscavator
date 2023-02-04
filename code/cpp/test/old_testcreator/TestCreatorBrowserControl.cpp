#include "TestCreatorBrowserControl.h"

BEGIN_EVENT_TABLE ( TestCreatorBrowserControl, wxControl )
	EVT_ACTIVATE	( TestCreatorBrowserControl::OnActivate 	)
	EVT_SIZE 		( TestCreatorBrowserControl::OnSize 		)
    EVT_PAINT		( TestCreatorBrowserControl::OnPaint		)
END_EVENT_TABLE()

TestCreatorBrowserControl::TestCreatorBrowserControl ( 
	wxWindow* parent, 
	wxWindowID id,
	const wxPoint& pos,
    const wxSize& size )
 : 	wxControl(parent, id, pos, size, wxNO_BORDER),
	m_pIWebBrowser( 0 )
{
}



void TestCreatorBrowserControl::initWebBrowser( 
	nsCOMPtr<nsIWebBrowser> pIWebBrowser )
{
	printf("ML: TestCreatorBrowserControl::initWebBrowser 1\n");
	m_pIWebBrowser = pIWebBrowser;
	if ( ! m_pIWebBrowser )	return;
	m_pIBaseWindow = do_QueryInterface ( m_pIWebBrowser ) ;
	printf("ML: TestCreatorBrowserControl::initWebBrowser 2\n");
}



void TestCreatorBrowserControl::OnActivate( wxActivateEvent &event )
{
	printf("ML: TestCreatorBrowserControl::OnActivate\n");
	if ( m_pIBaseWindow ) {
		wxRect newRect = this->GetClientRect();
		m_pIBaseWindow->SetPositionAndSize ( 
				newRect.GetLeft(), newRect.GetTop(),
		        newRect.GetWidth(), newRect.GetHeight(), 
				PR_FALSE );
	}
}


void TestCreatorBrowserControl::OnSize ( wxSizeEvent &event )
{
// 	printf("TestCreatorBrowserControl::OnSize\n");
	if ( m_pIBaseWindow ) {
		wxRect newRect = this->GetClientRect();
// 		printf ("wxRect: %d, %d ; %d, %d\n", newRect.GetLeft(), newRect.GetTop(), newRect.GetWidth(), newRect.GetHeight() );
		m_pIBaseWindow->SetPositionAndSize ( 
				newRect.GetLeft(), newRect.GetTop(),
		        newRect.GetWidth(), newRect.GetHeight(), 
				PR_FALSE );
	}
}

// 	if ( m_pChrome && m_pChrome->mBrowserBaseWindow ) {
// 		wxRect newRect = this->GetClientRect();
// 		m_pChrome->mBrowserBaseWindow->SetPositionAndSize ( 
// 				newRect.GetLeft(), newRect.GetTop(),
// 		        newRect.GetWidth(), newRect.GetHeight(), 
// 				PR_FALSE );
// 	}


void TestCreatorBrowserControl::OnPaint(wxPaintEvent& WXUNUSED(evt))
{
// 	printf("TestCreatorBrowserControl::OnPaint\n");
	if ( m_pIBaseWindow ) {
		wxRect newRect = this->GetClientRect();
// 		printf ("wxRect: %d, %d ; %d, %d\n", newRect.GetLeft(), newRect.GetTop(), newRect.GetWidth(), newRect.GetHeight() );
		m_pIBaseWindow->SetPositionAndSize ( 
				newRect.GetLeft(), newRect.GetTop(),
		        newRect.GetWidth(), newRect.GetHeight(), 
				PR_FALSE );
	}

}
