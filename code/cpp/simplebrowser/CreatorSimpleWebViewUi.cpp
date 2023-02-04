#include "CreatorSimpleWebViewUi.h"
#include <stdio.h>
#include <iostream>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QProgressBar>

#include <map>
#include <boost/algorithm/string.hpp>
#include <boost/assign/list_of.hpp>
#include <cpaf_libs/utils/cpaf_stl_utils.h>
#include <math/base/utils.hpp>
#include <WebBrowserIF.h>
//#include <Globals.h>
#include "SimpleWebView.h"

using namespace std;
using namespace boost;
using namespace boost::assign; // bring 'list_of()' into scope

namespace crawl {

CreatorSimpleWebViewUi::CreatorSimpleWebViewUi(const boost::shared_ptr<Configuration>& configuration,
                                               QObject* parent)
    : BrowserViewIF(configuration, parent)
{
    m_simpleWebView = new SimpleWebView(configuration, this);
    connect(m_simpleWebView, &SimpleWebView::elementSelectedSig, this, &CreatorSimpleWebViewUi::elementSelectedSlot);
}

CreatorSimpleWebViewUi::~CreatorSimpleWebViewUi()
{
///    delete m_webkitWebView; // TODO: If we add this to a layout we we should not delete here!
}

// ----------------------------
// --- PROTECTED: overrides ---
// ----------------------------
// ----------------------
// --- private slots: ---
// ----------------------

void CreatorSimpleWebViewUi::elementSelectedSlot(SimpleWebView* /*pWebView*/)
{
    emit elementSelected(this);
}

void* CreatorSimpleWebViewUi::do_nativeViewPtr()
{
    return m_simpleWebView;
}

QWidget* CreatorSimpleWebViewUi::do_widgetPtr()
{
    return m_simpleWebView;
}

QString CreatorSimpleWebViewUi::do_title()
{
    return m_simpleWebView->title();
}

void CreatorSimpleWebViewUi::do_forward()
{
    m_simpleWebView->forward();
}

void CreatorSimpleWebViewUi::do_back()
{
    m_simpleWebView->back();
}

QUrl CreatorSimpleWebViewUi::do_url() const
{
    if (owningBrowser()) {
        return owningBrowser()->currentUrl();
    }
    return QUrl();
}

void CreatorSimpleWebViewUi::do_setUrl(const QUrl& url)
{
    if (owningBrowser()) {
        owningBrowser()->loadUrl(url);
    }
}

XPath CreatorSimpleWebViewUi::do_selectedElementXPath()
{
    return XPath(); // FIXME XPath
}

boost::shared_ptr<DomNodeIF> CreatorSimpleWebViewUi::do_selectedElement() const
{
    std::cout << "ERROR: CreatorWebViewUi::do_selectedElement() not implemented!" << std::endl;
    return boost::shared_ptr<DomNodeIF>();
}

} // END namespace crawl
