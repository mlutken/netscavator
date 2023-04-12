#include "WebkitWebView.h"
#include <stdio.h>
#include <iostream>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QKeyEvent>
//FIXME OLD QWebView #include <QtWebKitWidgets/QWebFrame>
//FIXME OLD QWebView #include <QtWebKit/QWebElement>
#include <QProgressBar>
#include <QLabel>

#include <map>
#include <boost/algorithm/string.hpp>
#include <boost/assign/list_of.hpp>
#include <cpaf_libs/utils/cpaf_stl_utils.h>
#include <math/base/utils.hpp>
#include <interfaces/Globals.h>
#include <GuiGlobals.h>

// https://doc.qt.io/qt-6/qml-qtwebengine-webengineview.html
// https://github.com/therecipe/qt/issues/730


using namespace crawl;
using namespace std;
using namespace boost;
using namespace boost::assign; // bring 'list_of()' into scope


WebkitWebView::WebkitWebView(QWidget *parent)
    : QWebEngineView(parent)
{
    m_guiGlobals = g()->gui();
    connect(this, SIGNAL(loadFinished(bool)), this, SLOT(loadFinishedSlot(bool) ) );
}

WebkitWebView::~WebkitWebView()
{
}


// ----------------------------
// --- PROTECTED: overrides ---
// ----------------------------

void WebkitWebView::mousePressEvent(QMouseEvent* event)
{
    std::cerr << "FIXMENM WebkitWebView::mousePressEvent()\n";
    QWebEngineView::mousePressEvent(event);
    //FIXME OLD QWebView
//    static const map<QString, size_t> adjustPos = map_list_of
//            ("A", 3)
//            ("LI", 1)
//            ("TITLE", 1)
//            ;


//    if ( Qt::ControlModifier & event->modifiers() )    {
//        //printf("WebkitWebView::mousePressEvent (x,y): (%d,%d)\n", event->x(), event->y() );

//        QWebHitTestResult hit = page()->mainFrame()->hitTestContent( event->pos() );
//        m_selectedElement = QWebElement();
//        if ( !hit.isNull() ) {

//            std::cout << "\nhit.element.tagname: '" << hit.element().tagName().toUtf8().constData() << "'" << std::endl;
//            //printf("hit.nodeType: '%d'\n", hit.element().nodeTypeCrawler() );
//            //printf("hit.element.nodeValueCrawler: '%s'\n", hit.element().nodeValueCrawler().toUtf8().data() );
////            printf("hit.enclosingBlockElement.tagname: '%s'\n", hit.enclosingBlockElement().tagName().toUtf8().data() );
////            printf("hit.linkElement.tagname: '%s'\n", hit.linkElement().tagName().toUtf8().data() );
////            printf("hit.isContentSelected: '%d'\n", hit.isContentSelected() );
////            printf("hit.isContentEditable: '%d'\n", hit.isContentEditable() );
////            printf("hit.linkText: '%s'\n", hit.linkText().toUtf8().data() );
////            printf("hit.alternateText: '%s'\n", hit.alternateText().toUtf8().data() );
////            printf("hit.linkTitle: '%s'\n", hit.linkTitle().toString().toUtf8().data() );
////            printf("hit.linkUrl: '%s'\n", hit.linkUrl().toString().toUtf8().data() );
////            printf("hit.linkText: '%s'\n", hit.linkText().toUtf8().data() );
////            printf("hit.title: '%s'\n", hit.title().toUtf8().data() );
//            m_selectedElement = hit.enclosingBlockElement();
//            if ( hit.element().tagName() != "" ) {
//                m_selectedElement = hit.element();
////                printf("Using actual element and not enclosing\n" );
//            }
//            else if ( hit.linkElement().tagName() != "" ) {
//                m_selectedElement = hit.linkElement();
////                printf("Using link element and not enclosing\n" );
//            }
////            else {
////                m_selectedElement = hit.element();
////                printf("Fallback to default hit element\n" );
////            }
//            emit elementSelectedSig(this);
//        }
//    }
//    else {
//        //printf("QWebView::mousePressEvent\n" );
//        QWebView::mousePressEvent(event);

//    }
}

void WebkitWebView::wheelEvent(QWheelEvent* event)
{
    std::cerr << "FIXMENM WebkitWebView::wheelEvent() Seems to not be called :(!\n";
    if (event->modifiers() & Qt::ControlModifier ) {
        const int zoomDelta = cpaf::math::clamp_copy(event->angleDelta().y(), -1, 1);
        const auto zoomFac = zoomFactor() + zoomDelta;
        setZoomFactor(zoomFac);
        m_guiGlobals->browserZoomLevelSet(zoomFactor());
        event->accept();
        return;
    }
    QWebEngineView::wheelEvent(event);
}

void WebkitWebView::keyPressEvent(QKeyEvent* event)
{
//FIXME OLD QWebView
    const auto &k = event->key();
    if ( event->modifiers() & Qt::ControlModifier) {
        cout << "DBG WebkitWebView::keyPressEvent, CTRL key: " << event->key() << endl;
        if (k == Qt::Key_Plus) {
            setZoomFactor(zoomFactor() + 0.1f );
            m_guiGlobals->browserZoomLevelSet(zoomFactor());
            event->accept();
            return;
        }
        else if (k == Qt::Key_Minus) {
            setZoomFactor(zoomFactor() - 0.1f );
            m_guiGlobals->browserZoomLevelSet(zoomFactor());
            event->accept();
            return;
        }
    }
    QWebEngineView::keyPressEvent(event);
}

// ----------------------
// --- private slots: ---
// ----------------------
void WebkitWebView::loadFinishedSlot ( bool ok )
{
    // TODO: This is not needed!
    setZoomFactor(m_guiGlobals->browserZoomLevel());
    emit pageLoadedSig(this, ok);
}

