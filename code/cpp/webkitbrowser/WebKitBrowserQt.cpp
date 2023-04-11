#include <QApplication>
#include <QKeyEvent>
#include <QAction>
#include <QUrl>
#include <QCryptographicHash>
#include <QWebEngineView>
#include <QtWebChannel/QtWebChannel>
#include <QStringLiteral>

#include <QtTest/QtTest>
#include <QtTest/QTestEventList>
#include <cpaf_libs/utils/cpaf_stl_utils.h>
#include <cpaf_libs/crypto/crypto_hash.h>

#include "WebKitBrowserQt.h"
//#include "WebKitDomNodeQt.h"
#include "WebKitDomDocumentLinearQt.h"

#include <SimpleDomDocumentLinear.h>
#include <SignalsManager.h>
#include <utils/utils.h>
#include <dom_constants.h>
#include <htmlparser/html/XPath.h>
#include <htmlparser/html/ParserDom.h>

#include "WebkitNetworkAccessManagerQt.h"

//    /home/ml/code/miners/scripts/simple-test.php
//    /home/ml/code/miners/scripts/cycling/dk/bikester.dk.php

using namespace std;
using namespace std::chrono;

namespace crawl {



// ------------------------
// --- helper functions ---
// ------------------------
static Qt::Key keyStringToKey(const std::string& key)
{
    static const std::map<std::string, Qt::Key> m = {
        {"$", Qt::Key_Dollar},
        {"%", Qt::Key_Percent},
        {"&", Qt::Key_Ampersand},
        {"'", Qt::Key_Apostrophe},
        {"(", Qt::Key_ParenLeft},
        {")", Qt::Key_ParenRight},
        {"*", Qt::Key_Asterisk},
        {"+", Qt::Key_Plus},
        {",", Qt::Key_Comma},
        {"-", Qt::Key_Minus},
        {".", Qt::Key_Period},
        {"/", Qt::Key_Slash},
        {"0", Qt::Key_0},
        {"1", Qt::Key_1},
        {"2", Qt::Key_2},
        {"3", Qt::Key_3},
        {"4", Qt::Key_4},
        {"5", Qt::Key_5},
        {"6", Qt::Key_6},
        {"7", Qt::Key_7},
        {"8", Qt::Key_8},
        {"9", Qt::Key_9},
        {":", Qt::Key_Colon},
        {";", Qt::Key_Semicolon},
        {"<", Qt::Key_Less},
        {"=", Qt::Key_Equal},
        {">", Qt::Key_Greater},
        {"?", Qt::Key_Question},
        {"@", Qt::Key_At},
        {"A", Qt::Key_A},
        {"B", Qt::Key_B},
        {"C", Qt::Key_C},
        {"D", Qt::Key_D},
        {"E", Qt::Key_E},
        {"F", Qt::Key_F},
        {"G", Qt::Key_G},
        {"H", Qt::Key_H},
        {"I", Qt::Key_I},
        {"J", Qt::Key_J},
        {"K", Qt::Key_K},
        {"L", Qt::Key_L},
        {"M", Qt::Key_M},
        {"N", Qt::Key_N},
        {"O", Qt::Key_O},
        {"P", Qt::Key_P},
        {"Q", Qt::Key_Q},
        {"R", Qt::Key_R},
        {"S", Qt::Key_S},
        {"T", Qt::Key_T},
        {"U", Qt::Key_U},
        {"V", Qt::Key_V},
        {"W", Qt::Key_W},
        {"X", Qt::Key_X},
        {"Y", Qt::Key_Y},
        {"Z", Qt::Key_Z},
        {"[", Qt::Key_BracketLeft},
        {"\\", Qt::Key_Backslash},
        {"]", Qt::Key_BracketRight},
        {"FIXME1", Qt::Key_AsciiCircum},
        {"_", Qt::Key_Underscore},
        {"FIXME2", Qt::Key_QuoteLeft},
        {"{", Qt::Key_BraceLeft},
        {"FIXME2", Qt::Key_Bar},
        {"}", Qt::Key_BraceRight},
        {"~", Qt::Key_AsciiTilde},
    };
    return cpaf::map_find(m, Qt::Key_unknown, key);
}

// See: https://doc.qt.io/qt-6/qtwebchannel-javascript.html
// https://stackoverflow.com/questions/6157929/how-to-simulate-a-mouse-click-using-javascript
static const auto webChannelInitialize = QStringLiteral (R"<<<(

function netscavatorNodeClick(xpath)
{
    let elem1 = netscavatorElementFromXPath(xpath);
    netscavatorSimulateMouseEvent(elem1, "mouseover");
    netscavatorSimulateMouseEvent(elem1, "click");
}

function netscavatorInputSet(xpath, input)
{
    let elem1 = netscavatorElementFromXPath(xpath);
    elem1.value = input;
}


function netscavatorSimulateMouseEvent(element, eventName)
{
    var options = netscavatorExtendObject(netscavatorDefaultOptions, arguments[2] || {});
    var oEvent, eventType = null;

    for (var name in netscavatorEventMatchers)
    {
        if (netscavatorEventMatchers[name].test(eventName)) { eventType = name; break; }
    }

    if (!eventType)
        throw new SyntaxError('Only HTMLEvents and MouseEvents interfaces are supported');

    if (document.createEvent)
    {
        oEvent = document.createEvent(eventType);
        if (eventType == 'HTMLEvents')
        {
            oEvent.initEvent(eventName, options.bubbles, options.cancelable);
        }
        else
        {
            oEvent.initMouseEvent(eventName, options.bubbles, options.cancelable, document.defaultView,
            options.button, options.pointerX, options.pointerY, options.pointerX, options.pointerY,
            options.ctrlKey, options.altKey, options.shiftKey, options.metaKey, options.button, element);
        }
        element.dispatchEvent(oEvent);
    }
    else
    {
        options.clientX = options.pointerX;
        options.clientY = options.pointerY;
        var evt = document.createEventObject();
        oEvent = netscavatorExtendObject(evt, options);
        element.fireEvent('on' + eventName, oEvent);
    }
    return element;
}

function netscavatorExtendObject(destination, source) {
    for (var property in source)
      destination[property] = source[property];
    return destination;
}

var netscavatorEventMatchers = {
    'HTMLEvents': /^(?:load|unload|abort|error|select|change|submit|reset|focus|blur|resize|scroll)$/,
    'MouseEvents': /^(?:click|dblclick|mouse(?:down|up|over|move|out))$/
}
var netscavatorDefaultOptions = {
    pointerX: 0,
    pointerY: 0,
    button: 0,
    ctrlKey: false,
    altKey: false,
    shiftKey: false,
    metaKey: false,
    bubbles: true,
    cancelable: true
}

function netscavatorNodeClickSimple(xpath)
{
    let elem1 = netscavatorElementFromXPath(xpath);
    elem1.click();
}

function netscavatorElementFromXPath(xpath) {
    let elem = document.evaluate(
      xpath,
      document,
      null,
      XPathResult.FIRST_ORDERED_NODE_TYPE,
      null,
    ).singleNodeValue;
    return elem;
}

var netscavator = {};
new QWebChannel(qt.webChannelTransport, function(channel)
{
    channel.objects.webChannelBridge.inputSet.connect(function() {
        let xpath = arguments[0];
        let input = arguments[1];
        netscavatorInputSet(xpath, input);
        ///channel.objects.webChannelBridge.browserToCpp(input, 34);
    });

    channel.objects.webChannelBridge.nodeClick.connect(function() {
        let xpath = arguments[0];
        netscavatorNodeClick(xpath);
        ///channel.objects.webChannelBridge.browserToCpp(xpath, 33);
    });

    channel.objects.webChannelBridge.markPositions.connect(function() {
        // This callback will be invoked whenever the signal is emitted on the C++/QML side.
        let xpathList = arguments[0];
        let clearCurrentlyMarked = arguments[1];
        netscavatorMarkElements(xpathList, clearCurrentlyMarked);
        ///channel.objects.webChannelBridge.browserToCpp(xpathList, 33);
    });

    channel.objects.webChannelBridge.hoverPosition.connect(function() {
        let xpath = arguments[0];
        netscavatorHoverElement(xpath);
    });

    channel.objects.webChannelBridge.cppToBrowser.connect(function() {
        // This callback will be invoked whenever the signal is emitted on the C++/QML side.
        let msg = arguments[0];
        let counter = arguments[1];
        counter = counter + 9;
        channel.objects.webChannelBridge.browserToCpp(msg, counter);
    });


    window.webChannelBridge = channel.objects.webChannelBridge;
    // webChannelBridge.browserToCpp('Hello from web page', 10);
});
)<<<");


static const auto creatorJavascript = QStringLiteral (R"<<<(


function netscavatorIndexOfChildNode(parentNode, childNode)
{
    if (parentNode === undefined || parentNode === null) {
        return -1;
    }
    let tagNameToFind = childNode.localName;
    let n = parentNode.firstChild;
    let index = -1;
    let indexCounter = 0;
    while (n != null) {
        var tagName = n.localName;
        if (n.nodeType != 1) {
            n = n.nextSibling;
            continue;
        }

        if (tagName && tagName == tagNameToFind) {
            indexCounter++;
        }
        if (n == childNode) {
            index = indexCounter;
        }
        n = n.nextSibling;
    }

    if (indexCounter < 2 && (index > -1)) {
        index = 0;  // If we only have one og the tagName we use index 0 to indicate this. Actually it's index = 1
    }

    return index;
}

function netscavatorXPathFromElement(treeNode)
{
    let xp = [];
    let n = treeNode;
    while (n) {
        if (n.nodeType == 1) { // is tag
            var tagName = n.localName;
            var index = netscavatorIndexOfChildNode(n.parentNode, n);
            if (index == 0) {
                xp.unshift(tagName);
            }
            else if (index > 0) {
                xp.unshift(tagName + '[' + index + ']');
            }
        }

        n = n.parentNode;
    }
    return xp.length ? '/' + xp.join('/') : null;
}

// https://www.w3schools.com/jsreF/obj_event.asp
function netcreatorMouseClick(event, element) {
    if (!element) { return; }

    if (event.ctrlKey) {
        let xpath = netscavatorXPathFromElement(element);
        event.cancelBubble = true;
        let clearCurrentlyMarked = false;
        netscavatorMarkElements(xpath, clearCurrentlyMarked);
        window.webChannelBridge.jsDomPosSelectedSlot(xpath, element.innerText);
    }
    else if (event.altKey) {
        let xpath = netscavatorXPathFromElement(element);
        event.cancelBubble = true;
        let clearCurrentlyMarked = true;
        netscavatorMarkElements(xpath, clearCurrentlyMarked);
        window.webChannelBridge.jsDomPosSelectedSlot(xpath, element.innerText);
    }
};

function netcreatorMouseHover(event, element) {
    if (!element) { return; }
    let xpath = netscavatorXPathFromElement(element);
    event.cancelBubble = true;
    netscavatorHoverElement(element);
    window.webChannelBridge.jsDomPosHoverSlot(xpath, element.innerText);
};


function netcreatorAppendMouseClick(element) {
    if (!element) { return; }
    let currentOnClick = element.onclick;
    element.onclick = function() {
        if (currentOnClick) {
            currentOnClick();
        }
        netcreatorMouseClick(event, this);
    }
}

function netcreatorAppendMouseHover(element) {
    if (!element) { return; }
    let currentOnHover = element.onmouseover;
    element.onmouseover = function() {
        if (currentOnHover) {
            currentOnHover();
        }
        netcreatorMouseHover(event, this);
    }
}

function netcreatorAddOnClickToAllElements() {
    let elements = document.getElementsByTagName("*");
    for (var i=0; i < elements.length; i++)
    {
        let element = elements[i];
        netcreatorAppendMouseClick(element);
        netcreatorAppendMouseHover(element);
    }
}

function netscavatorClearMarkedElements() {
    for (let i = 0; i < netscavator.markedElements.length; i++) {
        let elem = netscavator.markedElements[i][0];
        let color = netscavator.markedElements[i][1];
        elem.style.backgroundColor = color; // Restore original background color
    }
    netscavator.markedElements = [];
}

function netscavatorClearHoverElements() {
    for (let i = 0; i < netscavator.hoverElements.length; i++) {
        let elem = netscavator.hoverElements[i][0];
        let border = netscavator.hoverElements[i][1];
        elem.style.border = border; // Restore original border
    }
    netscavator.hoverElements = [];
}


function netscavatorMarkElements(xpathList, clearCurrentlyMarked) {
    if (!xpathList) { return; }
    if (clearCurrentlyMarked) {
        netscavatorClearMarkedElements();
    }
    let xpaths = xpathList.split(',');
    for (let i = 0; i < xpaths.length; i++) {
        netscavatorMarkElement(xpaths[i]);
    }
}

function netscavatorMarkElement(xpath) {
    let elem = netscavatorElementFromXPath(xpath);
    if (elem == undefined) { return; }
    netscavator.markedElements.push([elem, elem.style.backgroundColor]);
    elem.style.backgroundColor = 'yellow';
}

function netscavatorHoverElement(elem) {
    netscavatorClearHoverElements();
    if (elem == undefined) { return; }
    netscavator.hoverElements.push([elem, elem.style.border]);
    elem.style.border = '1px solid red';
}


netscavator.markedElements = [];
netscavator.hoverElements = [];

netcreatorAddOnClickToAllElements();
)<<<");

static const auto jQueryNamespaceJavascript = QStringLiteral (R"<<<(
netscavator.jQuery = jQuery.noConflict( true );
)<<<");


// -----------------------
// --- WebKitBrowserQt ---
// -----------------------


WebKitBrowserQt::WebKitBrowserQt(BrowserViewIF* browserView, boost::shared_ptr<Configuration> c)
    : crawl::WebBrowserIF(c)
    , m_browserView(browserView)
    , m_iPageLoadsTotal(0)
    , m_continuousTimer()
    , m_continuousTimer2()
    , m_delayPageLoadedSignalTimer(new QTimer(this))
{
    m_javascriptInject = "";
    m_javascriptInject.append(crawl::readResourceFile(":/qtwebchannel/qwebchannel.js"));
    m_javascriptInject.append(webChannelInitialize);
    const auto rm = runMode();
    if (runModeCreator(rm)) {
        m_javascriptInject.append(creatorJavascript);
        // m_javascriptInject.append(crawl::readResourceFile(":/jquery.min.js"));
        // m_javascriptInject.append(jQueryNamespaceJavascript);
    }


    m_delayPageLoadedSignalTimer->setSingleShot(true);
    connect(m_delayPageLoadedSignalTimer, SIGNAL(timeout()), this, SLOT(delayPageLoadedSlot()));

    setWebView(browserView);
    m_webChannel.registerObject(QStringLiteral("webChannelBridge"), &m_webChannelBridge);
    connect(&m_webChannelBridge, &WebChannelBridge::domPosSelectedSig, this, &WebKitBrowserQt::domPosSelectedSlot);
}

WebKitBrowserQt::~WebKitBrowserQt ( )
{
}

void WebKitBrowserQt::rotateImages(bool invert)
{
    QString code;

    if (invert)
        code = QStringLiteral("netscavator.jQuery('img').each( function () { netscavator.jQuery(this).css('transition', 'transform 2s'); netscavator.jQuery(this).css('transform', 'rotate(180deg)') } )");
    else
        code = QStringLiteral("netscavator.jQuery('img').each( function () { netscavator.jQuery(this).css('transition', 'transform 2s'); netscavator.jQuery(this).css('transform', 'rotate(0deg)') } )");
    m_pWebView->page()->runJavaScript(code);
}

void WebKitBrowserQt::addOnClickToAllElements()
{
    m_pWebView->page()->runJavaScript(QStringLiteral("netcreatorAddOnClickToAllElements();"));
}

void WebKitBrowserQt::domPosSelectedSlot(const QString& xpath, const QString& innerText)
{
    const string path = toString(xpath);
    crawl::XPath xp(path);

////    TreeNode*  treeNode = xPathToTreeNode (const TreeNode* rootNode,xpath);
//    cerr << "FIXMENM WebChannelBridge::domPosSelectedSlot; "
//         << "\nxpath: " << xpath.toUtf8().constData()
//         << "\nconv : " << xp.toString()
//         << "\ninnerText: " << innerText.toUtf8().constData()
//         << "\n";
    emit domPosSelectedSig(xpath, innerText);
    browserView()->emitDomPosSelectedSig(xpath, innerText);
}

// -------------------------------
// --- PRIVATE: Init functions ---
// -------------------------------
/** Call this from derived class as }last} thing before returning from constructor(s). */
void WebKitBrowserQt::do_initDerived()
{
}

void WebKitBrowserQt::do_setWebView(BrowserViewIF* browserView)
{
    // TODO: FIXME: Assigning twice connect ??

    bool firstAssign = true;
    if ( m_pWebView ) {
        firstAssign = false;
        disconnect(m_pWebView, SIGNAL(loadStarted()), this, SLOT(slotLoadStarted()));
        disconnect(m_pWebView, SIGNAL(loadProgress(int)), this, SLOT(slotLoadProgress(int)));
        disconnect(m_pWebView, SIGNAL(loadFinished(bool)), this, SLOT(slotLoadFinished(bool)));
    }

    m_pWebView = static_cast<QWebEngineView*>(browserView->nativeViewPtr());    // TODO: Get rid of this webview function again!

    connect(m_pWebView, SIGNAL(loadStarted()), this, SLOT(slotLoadStarted()));
    connect(m_pWebView, SIGNAL(loadProgress(int)), this, SLOT(slotLoadProgress(int)));
    connect(m_pWebView, SIGNAL(loadFinished(bool)), this, SLOT(slotLoadFinished(bool)));


    //FIXME OLD QWebEngineView
//    bool doLoadImages       = this->loadImages();
//    bool doLoadStyleSheets  = this->loadStyleSheets();
//    if ( m_networkAccessMgr ) {
//        delete m_networkAccessMgr;
//    }
//    m_networkAccessMgr = new WebkitNetworkAccessManagerQt(
//                m_pWebView->page()->networkAccessManager(), signalsManager(), doLoadImages, doLoadStyleSheets, this );
//    m_pWebView->page()->setNetworkAccessManager( m_networkAccessMgr );

    if ( !firstAssign ) {
        signalsManager()->signalPageLoaded( *this );
    }
    m_browserView = browserView;
}

// --------------------------------
// --- PRIVATE: Get interfaces functions ---
// --------------------------------
boost::shared_ptr<crawl::LinearDomIF>  WebKitBrowserQt::do_createLinearDom  ()
{
    using namespace crawl;
    boost::shared_ptr<crawl::WebBrowserIF> pBrowser = shared_from_this();

    boost::shared_ptr<SimpleDomDocumentLinear> linearDom;

    linearDom = boost::shared_ptr<SimpleDomDocumentLinear>(
                new SimpleDomDocumentLinear(pBrowser, html()) );
    return linearDom;
}

QString WebKitBrowserQt::do_pageHash() const
{
    return QCryptographicHash::hash(html().data(), QCryptographicHash::Md5).toHex();
//    return QString::fromUtf8(cpaf::crypto::md5(html()));
}


// ------------------------------
// --- PRIVATE: Url functions ---
// ------------------------------
std::string WebKitBrowserQt::do_currentUriGet () const
{
    if (!m_pWebView) {
        return "";
    }
    return m_pWebView->url().toEncoded().data();
}

string WebKitBrowserQt::do_requestedUriGet() const
{
    if (!m_pWebView) { return ""; }
    return toString(m_pWebView->page()->requestedUrl().toString());
}

bool WebKitBrowserQt::do_loadUri ( const std::string& sUri)
{
    if (!m_pWebView) {
        return false;
    }

    cancelPageLoad();
    QUrl url( sUri.c_str(), QUrl::StrictMode );
    if ( !url.isValid() ) {
        url = QUrl( sUri.c_str(), QUrl::TolerantMode );
    }
    if ( !url.isValid() ) {
        url.setUrl( QString::fromUtf8(sUri.c_str()) );
    }
    if ( url.scheme().isEmpty() ) {
        url.setScheme("http");
    }
    m_pWebView->load( url );
    return true;
}

void WebKitBrowserQt::do_cancelPageLoad()
{
    m_pWebView->stop();
}

bool WebKitBrowserQt::do_goBack() const
{
    bool bRetval = m_pWebView->pageAction( QWebEnginePage::Back )->isEnabled();
    m_pWebView->triggerPageAction( QWebEnginePage::Back );
    return bRetval;
}

bool WebKitBrowserQt::do_cancelUriLoadRequest  ( void* requestID, const std::string& /*sUri*/ )
{
    // TODO: Implement do_cancelUriLoadRequest
    return false;
}

string_view WebKitBrowserQt::do_html() const
{
    return m_pageHtml;
}

// https://stackoverflow.com/questions/6157929/how-to-simulate-a-mouse-click-using-javascript
bool WebKitBrowserQt::do_nodeClick(const std::string& xpath)
{
    m_webChannelBridge.nodeClick(toQString(xpath));
    return true;
}

bool WebKitBrowserQt::do_inputSet(const std::string& xpath, const std::string& input)
{
    m_webChannelBridge.inputSet(toQString(xpath), toQString(input));
    return true;
}

// ------------------------------
// --- PRIVATE: Dom functions ---
// ------------------------------
boost::shared_ptr<crawl::DomNodeIF> WebKitBrowserQt::do_getElementById ( const std::string& sID ) const
{
    return boost::shared_ptr<crawl::DomNodeIF>();
    //FIXME OLD QWebEngineView
//    QWebElement e = m_pWebView->page()->mainFrame()->documentElement().findFirst( QString::fromUtf8( (std::string("E#") + sID).c_str() ) );
//    boost::shared_ptr<crawl::WebBrowserIF> pBrowser;
//    pBrowser = boost::const_pointer_cast<crawl::WebBrowserIF>(shared_from_this());

//    return crawl::mkWebKitDomNodeQt(DomNodeTypes::ELEMENT, "", "", e, pBrowser, -1);
}

// TODO: Make this function const
boost::shared_ptr<DomNodeIF> WebKitBrowserQt::do_makeDomNode(void* nativeDomElementPtr)
{
    return boost::shared_ptr<crawl::DomNodeIF>();

    //FIXME OLD QWebEngineView
//    boost::shared_ptr<WebBrowserIF> browser = shared_from_this();
//    QWebElement* webElement = static_cast<QWebElement*>(nativeDomElementPtr);
    //    return crawl::mkWebKitDomNodeQt(DomNodeTypes::ELEMENT, "", "", *webElement, browser, -1);
}

void WebKitBrowserQt::do_triggerPageLoaded()
{
    const bool ok = true;
    slotLoadFinished(ok);
}



// -------------------------------------
// --- PRIVATE: Pagestatus functions ---
// -------------------------------------
bool WebKitBrowserQt::do_checkPotentialAjaxLoadCompleted	( const boost::posix_time::time_duration& deltaTime ) const
{
    return false;
//FIXME OLD QWebEngineView      return m_networkAccessMgr->checkPotentialAjaxLoadCompleted(deltaTime);
}

void WebKitBrowserQt::do_resetPageRequestCounters ()
{
//FIXME OLD QWebEngineView      m_networkAccessMgr->resetPageRequestCounters();
}

int WebKitBrowserQt::do_infoLastNetworkError() const
{
    return -1;
    //FIXME OLD QWebEngineView
//    QNetworkReply* reply = m_networkAccessMgr->lastNetworkReply();
//    return reply ? reply->error() : -1;
}

int WebKitBrowserQt::do_activityRequestStartCount() const
{
    return -1;
//FIXME OLD QWebEngineView      return m_networkAccessMgr->requestStartCount();
}

int WebKitBrowserQt::do_activityRequestFinishedCount() const
{
    return -1;
//FIXME OLD QWebEngineView      return m_networkAccessMgr->requestFinishedCount();
}

// ----------------------------------------------
// --- PRIVATE: Pagestatus/Progress functions ---
// ----------------------------------------------


// -------------------------------------
// --- PRIVATE: Javascript functions ---
// -------------------------------------
bool WebKitBrowserQt::do_javaScriptExecuteRetVal     (
        const std::string& sScript
        , std::string& sScriptReturnValue )
{
    m_pWebView->page()->runJavaScript(QString::fromUtf8(sScript.c_str()));

    return true; // TODO: See if we can detect eventual errors and return false
}

void WebKitBrowserQt::do_javaScriptExecuteCallback(const std::string& sScript,
                                                   const std::function<void (const QVariant&)>& resultCallback)
{
    m_pWebView->page()->runJavaScript(QString::fromUtf8(sScript.c_str()), resultCallback);
}


// -------------------------------
// --- Configuration functions ---
// -------------------------------
void WebKitBrowserQt::do_loadImages ( bool bLoadImages )
{
//FIXME OLD QWebEngineView      m_networkAccessMgr->doLoadImages( bLoadImages );
}

void WebKitBrowserQt::do_loadStyleSheets ( bool bLoadStyleSheets )
{
//FIXME OLD QWebEngineView      m_networkAccessMgr->doLoadStyleSheets( bLoadStyleSheets );
}


void WebKitBrowserQt::do_refresh ()
{
}

void WebKitBrowserQt::do_show ()
{
}

void WebKitBrowserQt::do_hide ()
{
}

void WebKitBrowserQt::do_sizeGet ( int& /*x*/, int& /*y*/ ) const
{
}

void WebKitBrowserQt::do_sizeSet( int /*x*/, int /*y*/ 	)
{
}

void WebKitBrowserQt::do_close ( bool /*bForce*/ )
{
}

void WebKitBrowserQt::do_repaint()
{
    m_pWebView->repaint();
}

void WebKitBrowserQt::do_focusActivate ()
{
//FIXME OLD QWebEngineView
//    QFocusEvent* ev = new QFocusEvent(QEvent::FocusIn, Qt::MouseFocusReason);
//    QApplication::sendEvent(m_pWebView, ev);
}

void WebKitBrowserQt::do_focusDeactivate ()
{
//FIXME OLD QWebEngineView
//    QFocusEvent* ev = new QFocusEvent(QEvent::FocusOut, Qt::MouseFocusReason);
//    QApplication::sendEvent(m_pWebView, ev);
}

void WebKitBrowserQt::do_sendKeepActive ()
{
}

void WebKitBrowserQt::do_scroll (int32_t xScroll, int32_t yScroll)
{
//FIXME OLD QWebEngineView      m_pWebView->page()->currentFrame()->scroll(xScroll, yScroll);
}

int WebKitBrowserQt::do_scrollPosXGet () const
{
    return 0;
//FIXME OLD QWebEngineView      return m_pWebView->page()->currentFrame()->scrollPosition().x();
}

int WebKitBrowserQt::do_scrollPosYGet () const
{
    return 0;
//FIXME OLD QWebEngineView      return m_pWebView->page()->currentFrame()->scrollPosition().y();
}

void WebKitBrowserQt::do_scrollByLines ( boost::int32_t iNumLines )
{
    // TODO: Temporary 'hack'. We set a line to be 25 pixels high!
    scroll ( 0, 25*iNumLines );
}

void WebKitBrowserQt::do_zoomSet(float pct)
{
    m_pWebView->setZoomFactor(pct);
}

float WebKitBrowserQt::do_zoomGet() const
{
    return m_pWebView->zoomFactor();
}

/*
http://stackoverflow.com/questions/2034981/how-to-manipulate-pages-content-inside-webkit-window-using-qt-and-qtwebkit
http://stackoverflow.com/questions/20592466/how-to-simulate-mouse-event-with-qt
*/
void WebKitBrowserQt::do_userKeyEvent(int eventType, int key, int modifiers)
{
    QTestEventList el;

    const QTest::KeyAction qtAction = static_cast<QTest::KeyAction> (eventType);
    const Qt::Key qtKey = static_cast<Qt::Key> (key);
    const auto qtModifiers = static_cast<Qt::KeyboardModifier>(modifiers);


    el.addKeyEvent(qtAction, qtKey, qtModifiers, 500);
    el.simulate(m_pWebView);
}

/*
pWidget->mapToGlobal(widgetPos)

*/
void WebKitBrowserQt::do_userMouseEvent(int eventType, float xpos, float ypos, int button, int buttons, int modifiers)
{
    QTestEventList el;

    const auto qtEventType = static_cast<QEvent::Type> (eventType);
    QPoint qtPos(xpos, ypos);
    const auto qtButton = static_cast<Qt::MouseButton>(button);
    const auto qtButtons = static_cast<Qt::MouseButton>(buttons);

//    qtPos = m_pWebView->mapToParent(qtPos); // Hmm something to account for scrolling...
    const auto qtModifiers = static_cast<Qt::KeyboardModifier>(modifiers);

    const int delayMsecs = -1;

    if (qtEventType == QEvent::MouseButtonPress)
        el.addMousePress(qtButton, qtModifiers, qtPos, delayMsecs);
    else if (qtEventType == QEvent::MouseButtonRelease)
        el.addMouseRelease(qtButton, qtModifiers,qtPos, delayMsecs);
    else if (qtEventType == QEvent::MouseButtonDblClick)
        el.addMouseDClick(qtButton, qtModifiers, qtPos, delayMsecs);
    else if (qtEventType == QEvent::MouseMove)
        el.addMouseMove(qtPos, delayMsecs);
    else if (qtEventType == crawl::MOUSE_CLICK_EVENT)
        el.addMouseClick(qtButton, qtModifiers, qtPos, delayMsecs);

//FIXME OLD QWebEngineView      el.simulate(m_pWebView);
}


// -------------------------------
// --- PRIVATE: Edit functions ---
// -------------------------------
std::string	WebKitBrowserQt::do_selectionGet () const
{
    return "TODO: implement WebKitBrowserQt::do_selectionGet()";
}


void WebKitBrowserQt::do_searchStringSet ( const std::string& sSearchFor )
{
}

bool WebKitBrowserQt::do_findNext 	()
{
    return false;
}

void WebKitBrowserQt::do_findEntireWord   ( bool val )
{
}


void WebKitBrowserQt::do_findMatchCase    ( bool val )
{
}

void WebKitBrowserQt::do_markPositions(const std::string& xpathStrList, bool clearCurrentlyMarked)
{
    m_webChannelBridge.markPositions(toQString(xpathStrList), clearCurrentlyMarked);
}

void WebKitBrowserQt::do_hoverPosition(const std::string& xpath)
{
    m_webChannelBridge.hoverPosition(toQString(xpath));
}

// --------------------------------
// --- PRIVATE: Timer functions ---
// --------------------------------
void WebKitBrowserQt::do_continuousTimerStart ( int iMilisecs )
{
    if ( m_continuousTimer ) m_continuousTimer->deleteLater();
    m_continuousTimer = new QTimer(this);
    connect(m_continuousTimer, SIGNAL(timeout()), this, SLOT( slotContinuousTimer() ) );
    m_continuousTimer->start(iMilisecs);
}

void WebKitBrowserQt::do_continuousTimer2Start ( int iMilisecs )
{
    if ( m_continuousTimer2 ) m_continuousTimer2->deleteLater();
    m_continuousTimer2 = new QTimer(this);
    connect(m_continuousTimer2, SIGNAL(timeout()), this, SLOT( slotContinuousTimer2() ) );
    m_continuousTimer2->start(iMilisecs);
}

void WebKitBrowserQt::do_oneShotTimerStart	( int iMilisecs )
{
}

void WebKitBrowserQt::do_continuousTimerStop ()
{
    if ( m_continuousTimer ) m_continuousTimer->deleteLater();
}

void WebKitBrowserQt::do_continuousTimer2Stop ()
{
    if ( m_continuousTimer2 ) m_continuousTimer2->deleteLater();
}

void WebKitBrowserQt::do_oneShotTimerStop ()
{
}

bool WebKitBrowserQt::do_supportsDynamicDom() const
{
    return true;
}

// -------------------------------
// --- PRIVATE: Misc functions ---
// -------------------------------
// See: http://stackoverflow.com/questions/34705849/clear-cookies-in-qtwebengine
void WebKitBrowserQt::do_clearCookies()
{
//FIXME OLD QWebEngineView
//    m_networkAccessMgr->setCookieJar(new QNetworkCookieJar());
//    if (!m_pWebView)
//        return;
}

std::string	WebKitBrowserQt::do_typeNameGet		() const
{
    return "WebKitBrowserQt";
}

wxWindow* WebKitBrowserQt::do_guiWx            () const
{
    return nullptr;
}

/*
domFind("Næste", "contains" );
domStep(-4);
nodeClick();
*/
// ----------------------------------------
// --- PRVATE: QtWebKit event functions ---
// ----------------------------------------
void WebKitBrowserQt::slotLoadStarted ()
{
    const bool bAbortOpen = signalsManager()->signalOnLoadUri( *this,  requestedUri());
}

void WebKitBrowserQt::slotLoadProgress  (int iProgress)
{
    using namespace std;
    std::string sUrl = ""; // TODO: Get the Url being loaded
    emit pageLoadProgressSignal(iProgress);
    signalsManager()->signalOnNetProgress(NULL, static_cast<boost::uint32_t>(iProgress),  sUrl );
}

void WebKitBrowserQt::slotLoadFinished ( bool bOk )
{
    using namespace std;

    m_iPageLoadsTotal++;
    if ( m_iPageLoadsTotal % 100 == 0 ) {
//        m_pWebView->page()->settings()->clearMemoryCaches();
    }

   // QWebSettings
    // See https://cpp.hotexamples.com/examples/-/QWebEngineView/-/cpp-qwebengineview-class-examples.html
    if ( bOk ) {
        m_pWebView->page()->toHtml([this](const QString& html) {
            m_pageHtml = html.toUtf8().constData();
            m_delayPageLoadedSignalTimer->start(delayPageLoadedSignalTimeInMs());
        });
    }

}


void WebKitBrowserQt::delayPageLoadedSlot()
{
    if (!m_pWebView->page()->webChannel()) {
        m_pWebView->page()->setWebChannel(&m_webChannel);
    }
    m_pWebView->page()->runJavaScript(m_javascriptInject);
    if (runModeCreator(runMode())) {
        addOnClickToAllElements();
    }

//    m_pWebView->page()->runJavaScript(QStringLiteral("window.webChannelBridge.browserToCpp('Test call from web page again!');"));
//    rotateImages(true);

    signalsManager()->signalPageLoaded( *this );
}

void WebKitBrowserQt::slotContinuousTimer ()
{
    signalsManager()->signalContinuousTimer();
}

void WebKitBrowserQt::slotContinuousTimer2 ()
{
    signalsManager()->signalContinuousTimer2();
}


} // END namespace crawl








