#include "SimpleWebView.h"
#include <stdio.h>
#include <iostream>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QTextBrowser>

#include <map>
#include <boost/algorithm/string.hpp>
#include <cpaf_libs/utils/cpaf_stl_utils.h>
#include <math/base/utils.hpp>
#include <utils/utils.h>

#include <Configuration.h>

using namespace std;
using namespace boost;

namespace crawl {

SimpleWebView::SimpleWebView(const boost::shared_ptr<Configuration>& configuration,
                             crawl::BrowserViewIF* browserView,
                             QWidget *parent)
    : QWidget(parent),
    m_configuration(configuration),
    m_owningBrowserView(browserView)
{
    QHBoxLayout* layout = new QHBoxLayout;

    if (viewMode() == "textbrowser") {
        initWithTextBrowser();
    }
    else {
        initWithTextEdit();
    }

    layout->addWidget(m_webView);
    setLayout(layout);
}

SimpleWebView::~SimpleWebView()
{
}

QString SimpleWebView::viewMode() const
{
    return QString::fromUtf8(m_configuration->valueStrGet("viewmode").c_str());
}

void SimpleWebView::htmlSet(const QString& html)
{
    m_webView->setHtml(html);
}

QString SimpleWebView::title() const
{
    return "";
//    return m_webView->title();
}

void SimpleWebView::setZoomFactor(float /*fac*/)
{
//    m_webView->setZoomFactor(fac);
}

void SimpleWebView::forward()
{
//    m_webView->forward();
}

void SimpleWebView::back()
{
//    m_webView->back();
}

// ----------------------------
// --- PROTECTED: overrides ---
// ----------------------------


// ----------------------
// --- private slots: ---
// ----------------------
void SimpleWebView::linkedClickedSlot(const QUrl& url)
{
    if (m_owningBrowserView) {
        m_owningBrowserView->emitLinkClicked(url);
    }
}

void SimpleWebView::sourceChangedSlot(const QUrl& /*src*/)
{
}

void SimpleWebView::initWithTextEdit()
{
    m_webView = new QTextEdit(this);
    m_webView->setReadOnly(true);
    m_webView->setHtml("<h1>Simple browser. Viewmode: 'textedit'</h1>");
}

void SimpleWebView::initWithTextBrowser()
{
    m_textBrowser = new QTextBrowser(this);
    m_textBrowser->setOpenLinks(false); // Do not try to load from links directly. We need our simple browser to download the page.
    m_textBrowser->setOpenExternalLinks(false);

    connect(m_textBrowser, SIGNAL(anchorClicked(const QUrl&)), this, SLOT(linkedClickedSlot(const QUrl&) ) );
    connect(m_textBrowser, SIGNAL(sourceChanged(const QUrl&)), this, SLOT(sourceChangedSlot(const QUrl&) ) );
    m_webView = m_textBrowser;
    m_webView->setHtml("<h1>Simple browser. Viewmode: 'textbrowser'</h1>");
}

} // END namespace crawl
