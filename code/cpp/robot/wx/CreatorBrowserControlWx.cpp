#include "CreatorBrowserControlWx.h"
#include <nsIWebBrowserFocus.h>

BEGIN_EVENT_TABLE ( CreatorBrowserControlWx, wxControl )
//	EVT_KEY_DOWN	( CreatorBrowserControlWx::OnKeyDown	)
	EVT_ACTIVATE	( CreatorBrowserControlWx::OnActivate 	)
	EVT_SIZE 		( CreatorBrowserControlWx::OnSize 		)
    EVT_PAINT		( CreatorBrowserControlWx::OnPaint		)
END_EVENT_TABLE()

CreatorBrowserControlWx::CreatorBrowserControlWx ( 
	wxWindow* parent, 
	wxWindowID id,
	const wxPoint& pos,
    const wxSize& size )
 : 	wxControl(parent, id, pos, size, wxNO_BORDER),
	m_pIWebBrowser( 0 )
{
}



void CreatorBrowserControlWx::initWebBrowser( 
	nsCOMPtr<nsIWebBrowser> pIWebBrowser )
{
	m_pIWebBrowser = pIWebBrowser;
	if ( ! m_pIWebBrowser )	return;
	m_pIBaseWindow = do_QueryInterface ( m_pIWebBrowser ) ;
}

// void CreatorBrowserControlWx::OnKeyDown( wxKeyEvent &event )
// {
// 	printf("ML: CreatorBrowserControlWx::OnKeyDown\n");
// }


void CreatorBrowserControlWx::OnActivate( wxActivateEvent &event )
{
// 	printf("ML: CreatorBrowserControlWx::OnActivate\n");
	if ( m_pIBaseWindow ) {
		wxRect newRect = this->GetClientRect();
		m_pIBaseWindow->SetPositionAndSize ( 
				newRect.GetLeft(), newRect.GetTop(),
		        newRect.GetWidth(), newRect.GetHeight(), 
				PR_FALSE );
	}
}


void CreatorBrowserControlWx::OnSize ( wxSizeEvent &event )
{
    //printf("CreatorBrowserControlWx::OnSize: %p\n", m_pIWebBrowser.get());
	
	if ( m_pIBaseWindow ) {
		wxRect newRect = this->GetClientRect();
        //printf ("wxRect: %d, %d ; %d, %d\n", newRect.GetLeft(), newRect.GetTop(), newRect.GetWidth(), newRect.GetHeight() );
		m_pIBaseWindow->SetPositionAndSize ( 
				newRect.GetLeft(), newRect.GetTop(),
		        newRect.GetWidth(), newRect.GetHeight(), 
				PR_FALSE );
	}
	
	nsCOMPtr<nsIWebBrowserFocus> pIWebBrowserFocus = do_QueryInterface ( m_pIWebBrowser );
	if ( pIWebBrowserFocus ) {
		pIWebBrowserFocus->Activate(); 
	}
	
}

// 	if ( m_pChrome && m_pChrome->mBrowserBaseWindow ) {
// 		wxRect newRect = this->GetClientRect();
// 		m_pChrome->mBrowserBaseWindow->SetPositionAndSize ( 
// 				newRect.GetLeft(), newRect.GetTop(),
// 		        newRect.GetWidth(), newRect.GetHeight(), 
// 				PR_FALSE );
// 	}


void CreatorBrowserControlWx::OnPaint(wxPaintEvent& WXUNUSED(evt))
{
	wxPaintDC dc(this);
// 	printf("CreatorBrowserControlWx::OnPaint: %p\n", m_pIWebBrowser.get() );
	
	if ( m_pIBaseWindow ) {
		wxRect newRect = this->GetClientRect();
// 		printf ("wxRect: %d, %d ; %d, %d\n", newRect.GetLeft(), newRect.GetTop(), newRect.GetWidth(), newRect.GetHeight() );
		m_pIBaseWindow->SetPositionAndSize ( 
				newRect.GetLeft(), newRect.GetTop(),
		        newRect.GetWidth(), newRect.GetHeight(), 
				PR_FALSE );
	}

}
