#include "CreatorWebkitWebViewUi.h"
#include <stdio.h>
#include <iostream>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QWebEngineView>

//FIXME OLD QWebView #include <QWebFrame>
//FIXME OLD QWebView #include <QWebElement>
#include <QProgressBar>

#include <map>
#include <boost/algorithm/string.hpp>
#include <boost/assign/list_of.hpp>
#include <cpaf_libs/utils/cpaf_stl_utils.h>
#include <math/base/utils.hpp>
#include <interfaces/Globals.h>
#include <GuiGlobals.h>
#include "WebkitWebView.h"

using namespace crawl;
using namespace std;
using namespace boost;
using namespace boost::assign; // bring 'list_of()' into scope

CreatorWebkitWebViewUi::CreatorWebkitWebViewUi(
        const boost::shared_ptr<crawl::Configuration>& configuration, QObject* parent)
    : crawl::BrowserViewIF(configuration, parent)
//FIXME OLD QWebView   , m_selectedElement()
{
    m_webkitWebView = new WebkitWebView;

    m_guiGlobals = g()->gui();
//FIXME OLD QWebView
    connect(m_webkitWebView, SIGNAL(loadFinished(bool)), this, SLOT(loadFinishedSlot(bool) ) );
    connect(m_webkitWebView, SIGNAL(elementSelectedSig (WebkitWebView*)), this, SLOT(elementSelectedSlot(WebkitWebView*) ) );

//    connect(m_webkitWebView, SIGNAL(elementSelectedSig (WebkitWebView*)), this, SLOT(elementSelectedSlot(WebkitWebView*) ) );
}

CreatorWebkitWebViewUi::~CreatorWebkitWebViewUi()
{
///    delete m_webkitWebView; // TODO: If we add this to a layout we we should not delete here!
}

// ----------------------------
// --- PROTECTED: overrides ---
// ----------------------------
// ----------------------
// --- private slots: ---
// ----------------------
void CreatorWebkitWebViewUi::loadFinishedSlot ( bool ok )
{
    m_webkitWebView->setZoomFactor(static_cast<qreal>(m_guiGlobals->browserZoomLevel()));
    emitBrowserViewPageLoaded(ok);
}

void CreatorWebkitWebViewUi::elementSelectedSlot(WebkitWebView* /*pWebView*/)
{
    emit elementSelected(this);
}

void CreatorWebkitWebViewUi::domPosSelectedSlot(const QString& xpath, const QString& innerText)
{
    std::cerr << "FIXMENM CreatorWebkitWebViewUi::domPosSelectedSlot\n";
}

void* CreatorWebkitWebViewUi::do_nativeViewPtr()
{
    return m_webkitWebView;
}

QWidget* CreatorWebkitWebViewUi::do_widgetPtr()
{
    return m_webkitWebView;
}

QString CreatorWebkitWebViewUi::do_title()
{
    return m_webkitWebView->title();
}

void CreatorWebkitWebViewUi::do_forward()
{
    m_webkitWebView->forward();
}

void CreatorWebkitWebViewUi::do_back()
{
    m_webkitWebView->back();
}

QUrl CreatorWebkitWebViewUi::do_url() const
{
    return m_webkitWebView->url();
}

void CreatorWebkitWebViewUi::do_setUrl(const QUrl& url)
{
    m_webkitWebView->setUrl(url);
}

crawl::XPath CreatorWebkitWebViewUi::do_selectedElementXPath()
{
    return XPath(); // FIXME XPath
}

boost::shared_ptr<DomNodeIF> CreatorWebkitWebViewUi::do_selectedElement() const
{
    std::cout << "ERROR: CreatorWebViewUi::do_selectedElement() not implemented!" << std::endl;
    return boost::shared_ptr<DomNodeIF>();
}

