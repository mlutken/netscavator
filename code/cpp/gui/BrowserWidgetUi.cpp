#include "BrowserWidgetUi.h"

#include <stdio.h>
#include <QLabel>
#include <QVBoxLayout>
#include <QTabWidget>
#include <url/Url.h>
#include <cpaf_libs/utils/cpaf_stl_utils.h>
#include <NetscavatorFactoryIF.h>

BrowserWidgetUi::BrowserWidgetUi (crawl::NetscavatorFactoryIF* netscavatorFactory, QWidget *parent) :
    QWidget                     (parent),
    m_netscavatorFactory        (netscavatorFactory),
    m_pCurrentCrawlerBrowser    (nullptr)
{
    m_pTabs = new QTabWidget(this);
    m_pTabs->setTabsClosable(true);
    m_pTabs->setMovable(true);
    //m_pTabs->setDocumentMode(true);
    connect(m_pTabs, SIGNAL(currentChanged(int)), this, SLOT(tabChangedSlot(int)));
    connect (m_pTabs, SIGNAL(tabCloseRequested(int)), this, SLOT(tabCloseRequestedSlot(int)));

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(m_pTabs);
    addBrowserTab(QUrl("about:blank"));
    setLayout(layout);
}

void BrowserWidgetUi::netscavatorFactorySet(crawl::NetscavatorFactoryIF* netscavatorFactory)
{
    m_netscavatorFactory = netscavatorFactory;
}

void BrowserWidgetUi::addBrowserTab (const QUrl& url)
{
    crawl::BrowserViewIF* pWebView = m_netscavatorFactory->createBrowserView(this);
    pWebView->setUrl(url);
    m_widgetToViewMap[pWebView->widgetPtr()] = pWebView;
    m_pTabs->addTab( static_cast<QWidget*>(pWebView->widgetPtr()), tr("New page"));
    connect(pWebView, SIGNAL(browserViewPageLoadedSignal(crawl::BrowserViewIF*, bool)), this, SLOT(browserWidgetPageLoadedSlot(crawl::BrowserViewIF*, bool)));
    ///connect(pWebView, SIGNAL(elementSelected(crawl::BrowserViewIF*)), this, SLOT( webElementSelectedSlot(crawl::BrowserViewIF*) ));
    connect(pWebView, &crawl::BrowserViewIF::elementSelected, this, &BrowserWidgetUi::webElementSelectedSlot);
    connect(pWebView, &crawl::BrowserViewIF::domPosSelectedSig, this, &BrowserWidgetUi::domPosSelectedSlot);
}

crawl::BrowserViewIF* BrowserWidgetUi::currentBrowserView () const
{
    return cpaf::map_find(m_widgetToViewMap, static_cast<crawl::BrowserViewIF*>(nullptr), m_pTabs->currentWidget());
}

crawl::BrowserViewIF* BrowserWidgetUi::browserView (int index) const
{
    return cpaf::map_find(m_widgetToViewMap, static_cast<crawl::BrowserViewIF*>(nullptr), m_pTabs->widget(index));
}

crawl::BrowserViewIF* BrowserWidgetUi::curBrowserView () const
{
    return m_pCurrentCrawlerBrowser;
}


crawl::BrowserViewIF* BrowserWidgetUi::curBrowserViewAquire ()
{
    m_pCurrentCrawlerBrowser = currentBrowserView();
    return m_pCurrentCrawlerBrowser;
}

void BrowserWidgetUi::curBrowserViewRelease ()
{
    m_pCurrentCrawlerBrowser = nullptr;
}


/** Set url of current browser (tab). */
void BrowserWidgetUi::urlSet (const QUrl& url)
{
    crawl::BrowserViewIF* pWebview = currentBrowserView();
    if ( pWebview ) pWebview->setUrl(url);
}

QUrl BrowserWidgetUi::url () const
{
    crawl::BrowserViewIF* pWebview = currentBrowserView();
    if ( pWebview ) return pWebview->url();
    else            return QUrl("");
}

// ---------------------
// --- public slots: ---
// ---------------------
void BrowserWidgetUi::newBrowserTabSlot ()
{
    addBrowserTab( QUrl("") );
}

void BrowserWidgetUi::urlSetSlot ( const QString& url )
{
    std::string sUrl = crawl::ensureProtocol(url.toUtf8().data() ) ;
    urlSet( QUrl( QString::fromUtf8(sUrl.c_str()) ) );
}

void BrowserWidgetUi::backSlot () const
{
    crawl::BrowserViewIF* pWebview = currentBrowserView();
    if ( pWebview ) pWebview->back();
}

void BrowserWidgetUi::forwardSlot () const
{
    crawl::BrowserViewIF* pWebview = currentBrowserView();
    if ( pWebview ) pWebview->forward();
}

// ----------------------
// --- private slots: ---
// ----------------------
void BrowserWidgetUi::domPosSelectedSlot(const QString& xpath, const QString& innerText)
{
    emit domPosSelectedSig (xpath, innerText);
}

void BrowserWidgetUi::webElementSelectedSlot (crawl::BrowserViewIF* pWebView)
{
    emit elementSelected( pWebView );
}

void BrowserWidgetUi::browserWidgetPageLoadedSlot (crawl::BrowserViewIF* pWebView, bool /*ok*/)
{
    int index = m_pTabs->indexOf ( browserViewToWidget(pWebView) );

    // --- Set tab title and tooltip to leaf filename. Truncate long names. ---
    QString title =  pWebView->title();
    const int titleFullLenght = title.length();
    m_pTabs->setTabToolTip(index, title );
    title.truncate(12);
    if ( title.length() < titleFullLenght ) title += "..";
    m_pTabs->setTabText(index, title );

    const QString url = pWebView->url().toString();
    if ( m_pTabs->currentIndex() == index ) emit urlChangedSignal(url);
    emit pageLoadedSignal();
}


void BrowserWidgetUi::tabChangedSlot (int index)
{
    emit urlChangedSignal( url().toString() );
    emit currentTabChanged(index);
    emit currentBrowserChanged( browserView(index) );
}

void BrowserWidgetUi::tabCloseRequestedSlot (int index)
{
    if ( m_pTabs->count() > 1 ) {
        crawl::BrowserViewIF* pBrowser = browserView(index);
        if ( pBrowser != m_pCurrentCrawlerBrowser ) {
            m_pTabs->removeTab(index);
            delete pBrowser;
        }
    }
}

QWidget* BrowserWidgetUi::browserViewToWidget (crawl::BrowserViewIF* browserView)
{
    for(const auto& it : m_widgetToViewMap) {
        if (it.second == browserView) {
            return it.first;
        }
    }
    return nullptr;
}
