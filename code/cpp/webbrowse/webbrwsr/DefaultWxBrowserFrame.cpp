#include "DefaultWxBrowserFrame.h"
#include <WebBrowserIF.h>

#include "SignalsManager.h"

BEGIN_EVENT_TABLE ( DefaultWxBrowserFrame, wxFrame )
	EVT_ACTIVATE 	( DefaultWxBrowserFrame::OnActivate 	)
	EVT_SIZE 		( DefaultWxBrowserFrame::OnSize 		)
    EVT_PAINT		( DefaultWxBrowserFrame::OnPaint		)
	EVT_CLOSE		( DefaultWxBrowserFrame::OnCloseHandler	)
END_EVENT_TABLE()

// frame constructor
DefaultWxBrowserFrame::DefaultWxBrowserFrame ( const wxString& title, nsCOMPtr<nsIWebBrowser>  pIWebBrowser, crawl::WebBrowserIF* pMozBrowser ) 
: 	wxFrame ( NULL, wxID_ANY, title ),
	m_pIWebBrowser( pIWebBrowser ),
	m_pMozBrowser(pMozBrowser)
{
	m_pIBaseWindow = do_QueryInterface ( m_pIWebBrowser ) ;
//	SetIcon ( wxICON ( sample ) );		// set the frame icon
}

void DefaultWxBrowserFrame::mozBrowserSet( crawl::WebBrowserIF* pMozBrowser)
{
	m_pMozBrowser = pMozBrowser;
}

void DefaultWxBrowserFrame::sendTestEvent()
{
    wxPaintEvent event( this->GetId() );
    event.SetEventObject( this );
    // Send it
    this->GetEventHandler()->ProcessEvent( event );

}

void DefaultWxBrowserFrame::OnActivate( wxActivateEvent &event )
{
	if ( m_pIBaseWindow ) {
		wxRect newRect = this->GetClientRect();
		m_pIBaseWindow->SetPositionAndSize ( 
				newRect.GetLeft(), newRect.GetTop(),
		        newRect.GetWidth(), newRect.GetHeight(), 
				PR_FALSE );
	}
}



void DefaultWxBrowserFrame::OnSize ( wxSizeEvent &event )
{
	if ( m_pIBaseWindow ) {
		wxRect newRect = this->GetClientRect();
		m_pIBaseWindow->SetPositionAndSize ( 
				newRect.GetLeft(), newRect.GetTop(),
		        newRect.GetWidth(), newRect.GetHeight(), 
				PR_FALSE );
	}
}

void DefaultWxBrowserFrame::OnPaint(wxPaintEvent& WXUNUSED(evt))
{
	wxPaintDC dc(this);
    printf("ML: DefaultWxBrowserFrame::OnPaint\n");
	if ( m_pIBaseWindow ) {
		wxRect newRect = this->GetClientRect();
// 		printf ("wxRect: %d, %d ; %d, %d\n", newRect.GetLeft(), newRect.GetTop(), newRect.GetWidth(), newRect.GetHeight() );
		m_pIBaseWindow->SetPositionAndSize ( 
				newRect.GetLeft(), newRect.GetTop(),
		        newRect.GetWidth(), newRect.GetHeight(), 
				PR_FALSE );
	}

}

void DefaultWxBrowserFrame::OnCloseHandler ( wxCloseEvent& event )
{
// 	printf("\n\nXXXXXX DefaultWxBrowserFrame::OnCloseHandler\n\n");
	bool bDoClose = true;
	if ( m_pMozBrowser ) {
// 		printf("\n\nYYYYYYYY DefaultWxBrowserFrame SIGNAL \n\n");
		bDoClose = m_pMozBrowser->signalsManager()->signalOnClose();
	}
	if ( bDoClose ) Destroy();
}


