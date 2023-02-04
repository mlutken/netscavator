
// #include <QWidget>
// #include <stdio.h>
// #include <boost/thread/thread.hpp>
// #include <webbrwsr/DefaultQtBrowserFrame.h>
// #include <utils/webbrowse_embedding_utils.h>
// #include "MozBrowserQt.h"
// #include <QWidget>



#include <utils/webbrowse_embedding_utils.h>
#include <MozBrowserQt.h>
#include <QWidget>
#include <QApplication>
#include <QFont>
#include <QPushButton>
#include <webbrwsr/DefaultQtBrowserFrame.h>
#include <webbrwsr/lcdrange.h>


int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

// 	QPushButton quit("Quit");
// 	QWidget quit;
// 	quit.resize(75, 30);
// 	quit.setFont(QFont("Times", 18, QFont::Bold));
// 	QObject::connect(&quit, SIGNAL(clicked()), &app, SLOT(quit()));
// 	quit.show();
	
	LCDRange* pWidget = new LCDRange(0);
	
	initXulrunner();
// 	QWidget* pWidget = new DefaultQtBrowserFrame(0);
// 	QWidget* pWidget = new DefaultQtBrowserFrame(0);
	printf( "a widget windId: %d\n", pWidget->winId() );
	printf( "1 widget handle: %d\n", pWidget->x11PictureHandle() );
	printf( "2 widget handle: %d\n", pWidget->x11PictureHandle() );
	printf( "b widget windId: %d\n", pWidget->winId() );

// 	TestCreatorBrowserControl* pBrowserControl = new TestCreatorBrowserControl( m_pFrame );
	MozBrowserQt* pMozBrowserQt = new MozBrowserQt(pWidget );
	
// 	pBrowserControl->initWebBrowser( m_pMozBrowserWx-> webBrowser()->ifMoz() );
// 	testEvents_connectSlots ( m_pMozBrowserWx->signalsManager() );
// 	pMozBrowserQt->loadURI("http://www.boost.org");
	printf( "3 widget handle: %d\n", pWidget->x11PictureHandle() );
// 	pWidget->show();
// 	pWidget->resize(400, 300);
	printf( "4 widget handle: %d\n", pWidget->x11PictureHandle() );
	printf( "5 widget handle: %d\n", pWidget->x11PictureHandle() );


	return app.exec();
}
    