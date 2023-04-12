#include <QApplication>
#include <QKeyEvent>
#include <QAction>
#include <QUrl>
#include <QCryptographicHash>

#include <QtTest/QtTest>
#include <QtTest/QTestEventList>
#include <cpaf_libs/utils/cpaf_stl_utils.h>
#include <compression/cpaf_compression_functions.h>
#include <streams/cpaf_streams.h>
#include <html/ParserDom.h>

#include <utils/string_algorithms.h>
#include "SimpleBrowser.h"
#include "SimpleDomNode.h"
#include "SimpleDomDocumentLinear.h"
#include <SimpleWebView.h>

#include <Configuration.h>
#include <SignalsManager.h>
#include <utils/utils.h>
#include <html/utils.h>
#include <dom_constants.h>
#include <containers/WordMonitor.h>

using namespace std;
using namespace std::chrono;
using namespace crawl;

namespace crawl {

// --------------------
// --- SimpleBrowser ---
// --------------------

SimpleBrowser::SimpleBrowser(BrowserViewIF* browserView, boost::shared_ptr<Configuration> c)
    : crawl::WebBrowserIF(c)
    , m_browserView(browserView)
    , m_iPageLoadsTotal(0)
    , m_continuousTimer()
    , m_continuousTimer2()
{
    if (m_browserView) {
        connect(m_browserView, SIGNAL(linkClicked(BrowserViewIF*, const QUrl&)), this, SLOT(linkClickedSlot(BrowserViewIF*, const QUrl&)));
    }
    setWebView(browserView);
}

SimpleBrowser::~SimpleBrowser ( )
{
    //    delete m_pContinuousTimer;
    //    delete m_pOneShotTimer;
}

// -------------------------------
// --- PRIVATE: Init functions ---
// -------------------------------
/** Call this from derived class as }last} thing before returning from constructor(s). */
void SimpleBrowser::do_initDerived()
{
}

void SimpleBrowser::do_setWebView(BrowserViewIF* browserView)
{
    m_browserView = browserView;
    if (m_browserView) {
        m_browserView->owningBrowserSet(this);
        m_simpleWebView = static_cast<SimpleWebView*>(m_browserView->widgetPtr());
    }

//    if ( m_simpleWebView ) {
//        firstAssign = false;
//        disconnect(m_pWebView, SIGNAL(loadStarted()), this, SLOT(slotLoadStarted()));
//    }

//   linkClickedSlot


//    connect(m_simpleWebView, SIGNAL(loadStarted()), this, SLOT(slotLoadStarted()));
//    connect(m_simpleWebView, SIGNAL(loadProgress(int)), this, SLOT(slotLoadProgress(int)));
//    connect(m_simpleWebView, SIGNAL(loadFinished(bool)), this, SLOT(slotLoadFinished(bool)));

//    if ( !firstAssign ) {
//        signalsManager()->signalPageLoaded( *this );
//    }
}

// --------------------------------
// --- PRIVATE: Get interfaces functions ---
// --------------------------------
boost::shared_ptr<crawl::LinearDomIF> SimpleBrowser::do_createLinearDom ()
{
    using namespace crawl;
    boost::shared_ptr<crawl::WebBrowserIF> pBrowser = shared_from_this();

    boost::shared_ptr<SimpleDomDocumentLinear> linearDom;

    linearDom = boost::shared_ptr<SimpleDomDocumentLinear>(
                new SimpleDomDocumentLinear(pBrowser, html()) );
    return std::move(linearDom); // FIXMENM TODO: std::move() ???
}

QString SimpleBrowser::do_pageHash() const
{
    return "";
//    return QCryptographicHash::hash(m_simpleWebView->page()->mainFrame()->toHtml().toUtf8(), QCryptographicHash::Md5).toHex();
}


// ------------------------------
// --- PRIVATE: Url functions ---
// ------------------------------
std::string SimpleBrowser::do_currentUriGet () const
{
    return m_currentUri;    // TODO: Decoding ??
}

string SimpleBrowser::do_requestedUriGet() const
{
    return m_currentLoadingUri;
}

bool SimpleBrowser::do_loadUri ( const std::string& sUri)
{
    m_currentLoadingUri = sUri;
    // Download html page directly
    using namespace std::placeholders;
    auto cb = [this] (QByteArray&& data, const QUrl& url, bool ok) {
        this->handleHtmlPageDownloadedCb(std::move(data), url, ok);
    };
    m_httpDownloader.downloadToByteArrayMove(toQUrl(sUri), cb);
    return true;
}

void SimpleBrowser::do_cancelPageLoad()
{
}

/// @todo Implement SimpleBrowser::do_goBack()
bool SimpleBrowser::do_goBack() const
{
    return false;
}

/// @todo Implement SimpleBrowser::do_cancelUriLoadRequest()
bool SimpleBrowser::do_cancelUriLoadRequest  ( void*  /*requestID*/, const std::string& /*sUri*/ )
{
    return false;
}

string_view SimpleBrowser::do_html() const
{
    bool replace_std_html_entities = true;
    string charset = "";

    const auto config = configuration();
    if (config) {
        replace_std_html_entities = config->valueBoolGet("replace_std_html_entities");
        const auto site_charset = config->valueStrGet("site_charset");
        if (site_charset != "") {
            charset = site_charset;
        }
        else {
            charset = crawl::detect_charset(m_currentPageHtmlData);
        }
    }
    if (charset == "utf-8") {
        if (replace_std_html_entities) {
            m_currentPageHtml = crawl::replaceAllKeyVal(crawl::stdAsciiHtmlEntitiesMap(), m_currentPageHtmlData.constData());
            // Also replace any script specific entities
            if (!scriptHtmlEntitiesReplace().empty()) {
                m_currentPageHtml = crawl::replaceAllKeyVal(scriptHtmlEntitiesReplace(), m_currentPageHtml);
            }
            return m_currentPageHtml;
        }
        else {
            return m_currentPageHtmlData.constData();
        }
    }
    else {
        if ( boost::algorithm::contains(charset, "8859") ||
             boost::algorithm::contains(charset, "1252")
           ) {
            m_currentPageHtml = toString(QString::fromLatin1(m_currentPageHtmlData));
        }
        else {
            m_currentPageHtml = toString(pageHtmlQString());
        }
    }
    // TODO: Handle conversions from other charsets... When we encounter them
    if (replace_std_html_entities) {
        m_currentPageHtml = crawl::replaceAllKeyVal(crawl::stdAsciiHtmlEntitiesMap(), m_currentPageHtml);
        // Also replace any script specific entities
        if (!scriptHtmlEntitiesReplace().empty()) {
            m_currentPageHtml = crawl::replaceAllKeyVal(scriptHtmlEntitiesReplace(), m_currentPageHtml);
        }
    }
    return m_currentPageHtml;
}

bool SimpleBrowser::do_nodeClick(const std::string& xpath)
{
    // https://doc.qt.io/qt-6/qurl.html#toString
    const auto schemeHost = toString(currentUrl().toString(QUrl::RemovePath));
    const auto* rootNode = currentLinearDom()->rootNode();
    const auto* treeNode = crawl::xPathToTreeNode(rootNode, crawl::XPath(xpath));

    std::string href = "";
    if (treeNode) {
        const auto opt = treeNode->data.attribute_value("href");
        if (opt) href = *opt;
    }
    if (href.empty()) {
        return false;
    }

    if (!boost::algorithm::starts_with(href, schemeHost)) {
        href = schemeHost + boost::algorithm::replace_all_copy("/" + href, "//", "/");
    }
    loadUri(href);
    return true;
}

bool SimpleBrowser::do_inputSet(const std::string& xpath, const std::string& input)
{
    std::cerr << " TODO SimpleBrowser::do_inputSet\n";
    return true;
}


// ------------------------------
// --- PRIVATE: Dom functions ---
// ------------------------------
boost::shared_ptr<crawl::DomNodeIF> SimpleBrowser::do_getElementById (const std::string& /*sID*/) const
{
    return boost::shared_ptr<crawl::DomNodeIF>();
    // TODO: Implement this if possible!
//    QWebElement e = m_simpleWebView->page()->mainFrame()->documentElement().findFirst( QString::fromUtf8( (std::string("E#") + sID).c_str() ) );
//    boost::shared_ptr<crawl::WebBrowserIF> pBrowser;
//    pBrowser = boost::const_pointer_cast<crawl::WebBrowserIF>(shared_from_this());

//    return crawl::mkSimpleDomNode(DomNodeTypes::ELEMENT, "", e, pBrowser, -1);
}

// TODO: Make this function const
boost::shared_ptr<DomNodeIF> SimpleBrowser::do_makeDomNode(void* /*nativeDomElementPtr*/)
{
    boost::shared_ptr<WebBrowserIF> browser = shared_from_this();
    return crawl::makeSimpleDomNode(DomNodeTypes::ELEMENT, "", AttributesMap{}, browser, -1, nullptr);
}

void SimpleBrowser::do_triggerPageLoaded()
{
    signalsManager()->signalPageLoaded(*this);
// TODO: Better implementation!
}


// -------------------------------------
// --- PRIVATE: Pagestatus functions ---
// -------------------------------------
bool SimpleBrowser::do_checkPotentialAjaxLoadCompleted	( const boost::posix_time::time_duration& /*deltaTime*/ ) const
{
    return false;
}

void SimpleBrowser::do_resetPageRequestCounters ()
{
}

int SimpleBrowser::do_infoLastNetworkError() const
{
    return -1;
}


// ----------------------------------------------
// --- PRIVATE: Pagestatus/Progress functions ---
// ----------------------------------------------


// -------------------------------------
// --- PRIVATE: Javascript functions ---
// -------------------------------------
bool SimpleBrowser::do_javaScriptExecuteRetVal     (
        const std::string& /*sScript*/
        , std::string& /*sScriptReturnValue*/ )
{
    return true; // TODO: See if we can detect eventual errors and return false
}

void SimpleBrowser::do_javaScriptExecuteCallback(const std::string& /*sScript*/,
                                                 const std::function<void (const QVariant&)>& /*resultCallback*/)
{

}


// -------------------------------
// --- Configuration functions ---
// -------------------------------
void SimpleBrowser::do_loadImages ( bool /*bLoadImages*/ )
{
}

void SimpleBrowser::do_loadStyleSheets ( bool /*bLoadStyleSheets*/ )
{
}


void SimpleBrowser::do_refresh ()
{
}

void SimpleBrowser::do_show ()
{
}

void SimpleBrowser::do_hide ()
{
}

void SimpleBrowser::do_sizeGet ( int& /*x*/, int& /*y*/ ) const
{
}

void SimpleBrowser::do_sizeSet( int /*x*/, int /*y*/ )
{
}

void SimpleBrowser::do_close ( bool /*bForce*/ )
{
}

void SimpleBrowser::do_repaint()
{
}

void SimpleBrowser::do_focusActivate ()
{
//    auto* ev = new QFocusEvent(QEvent::FocusIn, Qt::MouseFocusReason);
//    QApplication::sendEvent(m_simpleWebView, ev);
}

void SimpleBrowser::do_focusDeactivate ()
{
//    auto* ev = new QFocusEvent(QEvent::FocusOut, Qt::MouseFocusReason);
//    QApplication::sendEvent(m_simpleWebView, ev);
}

void SimpleBrowser::do_sendKeepActive ()
{
}

void SimpleBrowser::do_scroll ( boost::int32_t /*xScroll*/, boost::int32_t /*yScroll*/ )
{
}

/// @todo Implement SimpleBrowser::do_scrollPosXGet()
int SimpleBrowser::do_scrollPosXGet () const
{
    return 0;
}

/// @todo Implement SimpleBrowser::do_scrollPosYGet()
int SimpleBrowser::do_scrollPosYGet () const
{
    return 0;
}

void SimpleBrowser::do_scrollByLines ( boost::int32_t /*iNumLines*/ )
{
}

void SimpleBrowser::do_zoomSet(float /*pct*/)
{
}

float SimpleBrowser::do_zoomGet() const
{
    return 1.0f;
}

/*
http://stackoverflow.com/questions/2034981/how-to-manipulate-pages-content-inside-webkit-window-using-qt-and-qtwebkit
http://stackoverflow.com/questions/20592466/how-to-simulate-mouse-event-with-qt
*/
void SimpleBrowser::do_userKeyEvent(int /*eventType*/, int /*key*/, int /*modifiers*/)
{
}

/*
pWidget->mapToGlobal(widgetPos)

*/
void SimpleBrowser::do_userMouseEvent(int /*eventType*/, float /*xpos*/, float /*ypos*/, int /*button*/, int /*buttons*/, int /*modifiers*/)
{
}


// -------------------------------
// --- PRIVATE: Edit functions ---
// -------------------------------
std::string	SimpleBrowser::do_selectionGet () const
{
    return "TODO: implement SimpleBrowser::do_selectionGet()";
}


void SimpleBrowser::do_searchStringSet ( const std::string& /*sSearchFor*/ )
{
}

bool SimpleBrowser::do_findNext 	()
{
    return false;
}

void SimpleBrowser::do_findEntireWord   ( bool /*val*/ )
{
}


void SimpleBrowser::do_findMatchCase    ( bool /*val*/ )
{
}

void SimpleBrowser::do_markPositions(const std::string& /*xpathStrList*/, bool /*clearCurrentlyMarked*/)
{

}

void SimpleBrowser::do_hoverPosition(const std::string& /*xpath*/)
{

}

// --------------------------------
// --- PRIVATE: Timer functions ---
// --------------------------------
void SimpleBrowser::do_continuousTimerStart ( int iMilisecs )
{
    if ( m_continuousTimer ) m_continuousTimer->deleteLater();
    m_continuousTimer = new QTimer(this);
    connect(m_continuousTimer, SIGNAL(timeout()), this, SLOT( slotContinuousTimer() ) );
    m_continuousTimer->start(iMilisecs);
}

void SimpleBrowser::do_continuousTimer2Start ( int iMilisecs )
{
    if ( m_continuousTimer2 ) m_continuousTimer2->deleteLater();
    m_continuousTimer2 = new QTimer(this);
    connect(m_continuousTimer2, SIGNAL(timeout()), this, SLOT( slotContinuousTimer2() ) );
    m_continuousTimer2->start(iMilisecs);
}

void SimpleBrowser::do_oneShotTimerStart	( int /*iMilisecs*/ )
{
}

void SimpleBrowser::do_continuousTimerStop ()
{
    if ( m_continuousTimer ) m_continuousTimer->deleteLater();
}

void SimpleBrowser::do_continuousTimer2Stop ()
{
    if ( m_continuousTimer2 ) m_continuousTimer2->deleteLater();
}

void SimpleBrowser::do_oneShotTimerStop ()
{
}

bool SimpleBrowser::do_supportsDynamicDom() const
{
    return false;
}

// -------------------------------
// --- PRIVATE: Misc functions ---
// -------------------------------
// See: http://stackoverflow.com/questions/34705849/clear-cookies-in-qtwebengine
void SimpleBrowser::do_clearCookies()
{
}

std::string	SimpleBrowser::do_typeNameGet () const
{
    return "SimpleBrowser";
}

wxWindow* SimpleBrowser::do_guiWx () const
{
    return nullptr;
}

/*
*/
// ----------------------------------------
// --- PRVATE: QtWebKit event functions ---
// ----------------------------------------
void SimpleBrowser::slotLoadStarted ()
{
    std::string sUrl; // TODO: Get the Url about to be loaded
    /*bool bAbortOpen =*/ signalsManager()->signalOnLoadUri( *this,  sUrl);
}

void SimpleBrowser::slotLoadProgress  (int iProgress)
{
    using namespace std;
    std::string sUrl; // TODO: Get the Url being loaded
    emit pageLoadProgressSignal(iProgress);
    signalsManager()->signalOnNetProgress(nullptr, static_cast<boost::uint32_t>(iProgress),  sUrl );
}

void SimpleBrowser::slotContinuousTimer ()
{
    signalsManager()->signalContinuousTimer();
}

void SimpleBrowser::slotContinuousTimer2 ()
{
    signalsManager()->signalContinuousTimer2();
}

void SimpleBrowser::linkClickedSlot(BrowserViewIF* /*browserView*/, const QUrl& url)
{
    loadUrl(url);
}

void SimpleBrowser::handleHtmlPageDownloadedCb(QByteArray&& data, const QUrl& /*url*/, bool /*downloadedOk*/)
{
    m_currentUri = m_currentLoadingUri;
    m_currentLoadingUri = "";
    m_iPageLoadsTotal++;


    const auto data_type = cpaf::compression::to_compression_type(data.data(), data.size());
    const bool download_page_source_only = configuration()->valueBoolGet("download_page_source_only");
    auto page_source_file_name = configuration()->valueStrGet("page_source_file_name");
    bool save_page_source = configuration()->valueBoolGet("save_page_source");

    m_currentPageHtmlData.clear();
    if (data_type == cpaf::compression::type::gz) {
        auto dba = cpaf::compression::gz_uncompress(reinterpret_cast<const unsigned char*>(data.constData()), data.size());
        if (download_page_source_only) {
            cpaf::streams::to_file(page_source_file_name, dba);
            save_page_source = false;
        }
        else {
            m_currentPageHtmlData.append(reinterpret_cast<const char*>(dba.data()), dba.size());
        }
    }
    else {
        if (download_page_source_only) {
            cpaf::streams::to_file(page_source_file_name, data.data(), data.size());
            save_page_source = false;
        }
        else {
            m_currentPageHtmlData = std::move(data);   // TODO: Move construct this!
        }
    }

    if (save_page_source) {
        cpaf::streams::to_file(page_source_file_name, html());
    }
    if (m_simpleWebView) {
        m_simpleWebView->htmlSet(pageHtmlQString());
    }
    if (m_browserView) {
        m_browserView->emitBrowserViewPageLoaded(true);
    }
    signalsManager()->signalPageLoaded(*this);
}

QString SimpleBrowser::pageHtmlQString() const
{
    return QString::fromUtf8(m_currentPageHtmlData.constData());
}



/*
 *
 * Debugging helper commands:
  745  meld build_cbs/ninja_debug_static/netcreator/bike24.com.sitedump/htmldom/https\:/www.bike24.com/_page_webkit.html build_cbs/ninja_debug_static/netcreator/bike24.com.sitedump/htmldom/https\:/www.bike24.com/page.html
  746  curl https://www.bike24.com/ > build_cbs/ninja_debug_static/netcreator/bike24.com.sitedump/htmldom/https\:/www.bike24.com/_curl_page.html
  747  meld build_cbs/ninja_debug_static/netcreator/bike24.com.sitedump/htmldom/https\:/www.bike24.com/_page_webkit.html build_cbs/ninja_debug_static/netcreator/bike24.com.sitedump/htmldom/https\:/www.bike24.com/page.html
  748  meld build_cbs/ninja_debug_static/netcreator/bike24.com.sitedump/htmldom/https\:/www.bike24.com/_page_webkit.html build_cbs/ninja_debug_static/netcreator/bike24.com.sitedump/htmldom/https\:/www.bike24.com/_curl_page.html
  749  wget https://www.bike24.com/ -o build_cbs/ninja_debug_static/netcreator/bike24.com.sitedump/htmldom/https\:/www.bike24.com/_wget_page.html
  750  wget https://www.bike24.com/ -O build_cbs/ninja_debug_static/netcreator/bike24.com.sitedump/htmldom/https\:/www.bike24.com/_wget_page.html
  751  meld build_cbs/ninja_debug_static/netcreator/cykelexperten.dk.sitedump/htmldom/https\:/cykelexperten.dk/_page_webkit.html build_cbs/ninja_debug_static/netcreator/cykelexperten.dk.sitedump/htmldom/https\:/cykelexperten.dk/page.html
  752  wget https://cykelexperten.dk/ -O build_cbs/ninja_debug_static/netcreator/cykelexperten.dk.sitedump/htmldom/https\:/cykelexperten.dk/_wget_page.html
  753  sponge
  754  sudo apt install moreutils
  755  sponge
  756  isutf8 build_cbs/ninja_debug_static/netcreator/cykelexperten.dk.sitedump/htmldom/https\:/cykelexperten.dk/_wget_page.html
  757  isutf8 build_cbs/ninja_debug_static/netcreator/bike24.com.sitedump/htmldom/https\:/www.bike24.com/page.html
  758  isutf8 build_cbs/ninja_debug_static/netcreator/bike24.com.sitedump/htmldom/https\:/www.bike24.com/_page_webkit.html
  759  isutf8
  760  isutf8 --help
  761  isutf8 -v build_cbs/ninja_debug_static/netcreator/bike24.com.sitedump/htmldom/https\:/www.bike24.com/_page_webkit.html
  762  file -bi build_cbs/ninja_debug_static/netcreator/bike24.com.sitedump/htmldom/https\:/www.bike24.com/_page_webkit.html
  763  file -bi build_cbs/ninja_debug_static/netcreator/bike24.com.sitedump/htmldom/https\:/www.bike24.com/_curl_page.html

QWebSettings::globalSettings( )->setAttribute( QWebSettings::PrivateBrowsingEnabled, true );
QWebSettings::globalSettings( )->setAttribute( QWebSettings::LocalContentCanAccessRemoteUrls, true );
QWebSettings::setMaximumPagesInCache( 0 );
QWebSettings::setObjectCacheCapacities( 0, 0, 0 );
QWebSettings::clearMemoryCaches( );

  */


} // END namespace crawl








