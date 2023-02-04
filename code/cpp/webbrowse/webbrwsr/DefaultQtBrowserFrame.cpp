// #if 0
#if WEBBROWSE_ENABLE_QT
// #include <MozBrowser.h>
#include "DefaultQtBrowserFrame.h"


DefaultQtBrowserFrame::DefaultQtBrowserFrame ( QWidget* pParent ) 
: 	QWidget (pParent)
// 	,m_pIWebBrowser( 0)
// 	,m_pMozBrowser(0)
{
}

// DefaultQtBrowserFrame::DefaultQtBrowserFrame ( QWidget* pParent, nsCOMPtr<nsIWebBrowser>  pIWebBrowser, MozBrowser* pMozBrowser ) 
// : 	QWidget (pParent),
// 	m_pIWebBrowser( pIWebBrowser ),
// 	m_pMozBrowser(pMozBrowser)
// {
// 	m_pIBaseWindow = do_QueryInterface ( m_pIWebBrowser ) ;
// }

// void DefaultQtBrowserFrame::mozBrowserSet( MozBrowser* pMozBrowser)
// {
// 	m_pMozBrowser = pMozBrowser;
// }

// void DefaultQtBrowserFrame::initWebBrowser( 
// 	nsCOMPtr<nsIWebBrowser> pIWebBrowser )
// {
// 	printf("ML: DefaultQtBrowserFrame::initWebBrowser 1\n");
// 	m_pIWebBrowser = pIWebBrowser;
// 	if ( ! m_pIWebBrowser )	return;
// 	m_pIBaseWindow = do_QueryInterface ( m_pIWebBrowser ) ;
// 	printf("ML: DefaultQtBrowserFrame::initWebBrowser 2\n");
// }


// void DefaultQtBrowserFrame::OnActivate( wxActivateEvent &event )
// {
// 	if ( m_pIBaseWindow ) {
// 		wxRect newRect = this->GetClientRect();
// 		m_pIBaseWindow->SetPositionAndSize ( 
// 				newRect.GetLeft(), newRect.GetTop(),
// 		        newRect.GetWidth(), newRect.GetHeight(), 
// 				PR_FALSE );
// 	}
// }


// void DefaultQtBrowserFrame::OnSize ( wxSizeEvent &event )
// {
// 	if ( m_pIBaseWindow ) {
// 		wxRect newRect = this->GetClientRect();
// 		m_pIBaseWindow->SetPositionAndSize ( 
// 				newRect.GetLeft(), newRect.GetTop(),
// 		        newRect.GetWidth(), newRect.GetHeight(), 
// 				PR_FALSE );
// 	}
// }


// void DefaultQtBrowserFrame::OnCloseHandler ( wxCloseEvent& event )
// {
// 	bool bDoClose = true;
// 	if ( m_pMozBrowser ) {
// 		printf("\n\nYYYYYYYY DefaultQtBrowserFrame SIGNAL \n\n");
// 		bDoClose = m_pMozBrowser->signalsManager()->signalOnClose();
// 	}
// 	if ( bDoClose ) Destroy();
// }


#endif //#if WEBBROWSE_ENABLE_QT
