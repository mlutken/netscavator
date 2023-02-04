#include "wxBrowserControl.h"

BEGIN_EVENT_TABLE ( wxBrowserControl, wxControl )
	EVT_ACTIVATE	( wxBrowserControl::OnActivate 	)
	EVT_SIZE 		( wxBrowserControl::OnSize 		)
    EVT_PAINT		( wxBrowserControl::OnPaint		)
END_EVENT_TABLE()

wxBrowserControl::wxBrowserControl ( 
	wxWindow* parent, 
	wxWindowID id,
	const wxPoint& pos,
    const wxSize& size )
 : 	wxControl(parent, id, pos, size, wxNO_BORDER),
	m_pIWebBrowser( 0 )
{
}



void wxBrowserControl::initWebBrowser( 
	nsCOMPtr<nsIWebBrowser> pIWebBrowser )
{
	m_pIWebBrowser = pIWebBrowser;
	if ( ! m_pIWebBrowser )	return;
	m_pIBaseWindow = do_QueryInterface ( m_pIWebBrowser ) ;
}



void wxBrowserControl::OnActivate( wxActivateEvent &event )
{
	if ( m_pIBaseWindow ) {
		wxRect newRect = this->GetClientRect();
		m_pIBaseWindow->SetPositionAndSize ( 
				newRect.GetLeft(), newRect.GetTop(),
		        newRect.GetWidth(), newRect.GetHeight(), 
				PR_FALSE );
	}
}


void wxBrowserControl::OnSize ( wxSizeEvent &event )
{
//	printf("wxBrowserControl::OnSize\n");
	if ( m_pIBaseWindow ) {
		wxRect newRect = this->GetClientRect();
		m_pIBaseWindow->SetPositionAndSize ( 
				newRect.GetLeft(), newRect.GetTop(),
		        newRect.GetWidth(), newRect.GetHeight(), 
				PR_FALSE );
	}
}

void wxBrowserControl::OnPaint(wxPaintEvent& WXUNUSED(evt))
{
	printf("wxBrowserControl::OnPaint\n");

}
