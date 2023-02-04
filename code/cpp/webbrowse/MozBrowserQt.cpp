#if WEBBROWSE_ENABLE_QT

#include <stdio.h>
#include <boost/thread/thread.hpp>
// #include <webbrwsr/DefaultQtBrowserFrame.h>
#include <utils/webbrowse_embedding_utils.h>
#include "MozBrowserQt.h"
#include <QWidget>

//    m_panel = new qtPanel(this, qtID_ANY);

MozBrowserQt::MozBrowserQt ()	:	
	MozBrowser (),
	m_iKeepAxtiveX(0),
	m_iKeepAxtiveY(0)
{
	printf("MozBrowserQt::CONSTRUCTOR this: %p\n", this );
// 	m_pGuiQt = new DefaultQtBrowserFrame ( _T ( "Minimal qtWidgets App" ), webBrowser()->ifMoz(), this );
// 	::initNativeWindow ( webBrowser()->ifMoz(), chrome(), m_pGuiQt, 0, 0, 1024, 800 );
	initCommonDefaults(); // Important to call this after initNativeWindow
}

MozBrowserQt::MozBrowserQt (
	boost::shared_ptr<WebBrowser> pWebBrowser 
)	:	
	MozBrowser( pWebBrowser ),
	m_iKeepAxtiveX(0),
	m_iKeepAxtiveY(0)
{
	printf("MozBrowserQt::CONSTRUCTOR this: %p\n", this );
// 	m_pGuiQt = new DefaultQtBrowserFrame ( _T ( "Minimal qtWidgets App" ), webBrowser()->ifMoz(), this  );
// 	::initNativeWindow ( webBrowser()->ifMoz(), chrome(), m_pGuiQt, 0, 0, 1024, 800 );
	initCommonDefaults(); // Important to call this after initNativeWindow
}

MozBrowserQt::MozBrowserQt ( 
	QWidget* pGuiQt 
)	:	
	MozBrowser(),
	m_pGuiQt( pGuiQt ),
	m_iKeepAxtiveX(0),
	m_iKeepAxtiveY(0)
{
	printf("MozBrowserQt::CONSTRUCTOR this: %p\n", this );
	::initNativeWindow ( webBrowser()->ifMoz(), chrome(), m_pGuiQt, 0, 0, 1024, 800 );
	initCommonDefaults(); // Important to call this after initNativeWindow
}


MozBrowserQt::MozBrowserQt (
	boost::shared_ptr<WebBrowser> pWebBrowser,
	QWidget* pGuiQt	
)	:	
	MozBrowser( pWebBrowser ),
	m_pGuiQt( pGuiQt ),
	m_iKeepAxtiveX(0),
	m_iKeepAxtiveY(0)
{
	printf("MozBrowserQt::CONSTRUCTOR this: %p\n", this );
	::initNativeWindow ( webBrowser()->ifMoz(), chrome(), m_pGuiQt, 0, 0, 1024, 800 );
	initCommonDefaults(); // Important to call this after initNativeWindow
}

MozBrowserQt::~MozBrowserQt ( )
{
	printf("MozBrowserQt::DESTRUCTOR this: %p\n", this );
}


void MozBrowserQt::refresh	()
{
}

void MozBrowserQt::show()
{
// 	m_pGuiQt->Show( true );
}

void MozBrowserQt::hide()
{
// 	m_pGuiQt->Show( false );
}

void MozBrowserQt::sizeGet ( int& x, int& y	) const
{
// 	m_pGuiQt->GetSize(&x, &y); 
}
	 
void MozBrowserQt::sizeSet ( int x, int y )
{
// 	m_pGuiQt->SetSize(x, y);
}

void MozBrowserQt::sendKeepActive ()	
{
}

void MozBrowserQt::close (bool bForce)	
{
// 	m_pGuiQt->Close(bForce); 
}

void MozBrowserQt::continuousTimerStart	( int iMilisecs )
{
}

void MozBrowserQt::oneShotTimerStart		( int iMilisecs )
{
}

void MozBrowserQt::continuousTimerStop	( )	
{
}

void MozBrowserQt::oneShotTimerStop	( )	
{
}


#endif //#if WEBBROWSE_ENABLE_QT


