#ifndef _WEBBROWSE_DEFAULT_QT_BROWSER_FRAME_H_
#define _WEBBROWSE_DEFAULT_QT_BROWSER_FRAME_H_
// #if 0
#if WEBBROWSE_ENABLE_QT


// #include <nsCOMPtr.h>
// #include <nsIWebBrowser.h>
// #include <nsIBaseWindow.h>
#include <QWidget>


// class MozBrowser;

class DefaultQtBrowserFrame : public QWidget
{
	Q_OBJECT
public:
	DefaultQtBrowserFrame ( QWidget* pParent);
// 	DefaultQtBrowserFrame ( QWidget* pParent, nsCOMPtr<nsIWebBrowser>  pIWebBrowser, MozBrowser* pMozBrowser );

// 	void	initWebBrowser( nsCOMPtr<nsIWebBrowser> pIWebBrowser );	
	// Event handlers (these functions should _not_ be virtual)
// 	void	OnActivate		( wxActivateEvent &event 	);
// 	void 	OnSize			( wxSizeEvent &event		);
// 	void 	OnCloseHandler	( wxCloseEvent& event		);
// 	void	mozBrowserSet	( MozBrowser* pMozBrowser	);

private:
// 	nsCOMPtr<nsIWebBrowser>		m_pIWebBrowser;
// 	nsCOMPtr<nsIBaseWindow> 	m_pIBaseWindow;
// 	MozBrowser*					m_pMozBrowser;

};


#endif //#if WEBBROWSE_ENABLE_QT
#endif // _WEBBROWSE_DEFAULT_QT_BROWSER_FRAME_H_ 
