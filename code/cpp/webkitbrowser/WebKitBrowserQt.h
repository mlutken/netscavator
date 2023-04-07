#ifndef WEBKIT_BROWSER_QT_H
#define WEBKIT_BROWSER_QT_H

#include <chrono>
#include <WebBrowserIF.h>
#include <BrowserViewIF.h>
#include <QWidget>
#include <QWebChannel>
#include <WebChannelBridge.h>

//https://cefview.github.io/QCefView/docs/guide/FirstProject

class QWebEngineView;

namespace crawl {

class WebkitNetworkAccessManagerQt;

/** Toplevel (QT WebKit) browser class. */
class WebKitBrowserQt : public crawl::WebBrowserIF
{
    Q_OBJECT
public:
    typedef boost::shared_ptr<WebKitBrowserQt> 	Ptr;		///< Pointer to a WebKitBrowserQt

    explicit WebKitBrowserQt    (BrowserViewIF* browserView, boost::shared_ptr<crawl::Configuration> c);
    ~WebKitBrowserQt            () override;

signals:
    void    loadUriSignal       (const QString& uri);

private slots:
    void    rotateImages        (bool invert);
    void    addOnClickToAllElements ();
    void    domPosSelectedSlot  (const QString& xpath, const QString& innerText);

private:
    // -------------------------------
    // --- PRIVATE: Init functions ---
    // -------------------------------
    void            do_initDerived  () override;
///    void            do_setWebView   (QWebEngineView* webView) override;
    void            do_setWebView   (BrowserViewIF* browserView) override;
    void            do_clearForReloadScript () override {}

    // -----------------------------------------
    // --- PRIVATE: Get interfaces functions ---
    // -----------------------------------------
    boost::shared_ptr<crawl::LinearDomIF>   do_createLinearDom  () override;
    QString                                 do_pageHash         () const override;
    crawl::BrowserViewIF*                   do_browserView      () const override { return m_browserView; }

    // ------------------------------
    // --- PRIVATE: Url functions ---
    // ------------------------------
    std::string 	do_currentUriGet        () const override;
    std::string 	do_requestedUriGet      () const override;
    bool            do_loadUri              ( const std::string& sUri ) override;
    void 			do_cancelPageLoad       () override;
    //        std::string     do_currentLoadingUrl() const override;
    bool            do_goBack() const override;
    bool            do_cancelUriLoadRequest  (void* requestID, const std::string& sUri) override;

    // ------------------------------
    // --- PRIVATE: Dom functions ---
    // ------------------------------
    std::string_view                        do_html             () const override;
    bool                                    do_nodeClick        (const std::string& xpath) override;
    bool                                    do_inputSet         (const std::string& xpath, const std::string& input) override;
    boost::shared_ptr<crawl::DomNodeIF>     do_getElementById   (const std::string& sID) const override;
    boost::shared_ptr<crawl::DomNodeIF>     do_makeDomNode      (void *nativeDomNodePtr) override;

    // -------------------------------------
    // --- PRIVATE: Pagestatus functions ---
    // -------------------------------------
    void		do_triggerPageLoaded                () override;
    bool		do_checkPotentialAjaxLoadCompleted	(const boost::posix_time::time_duration& deltaTime) const override;
    void		do_resetPageRequestCounters			() override;
    int         do_infoLastNetworkError             () const override;
    int         do_activityRequestStartCount        () const override;
    int         do_activityRequestFinishedCount     () const override;

    // -------------------------------------
    // --- PRIVATE: Javascript functions ---
    // -------------------------------------
    bool        do_javaScriptExecuteRetVal          (const std::string& sScript, std::string& sScriptReturnValue) override;
    void        do_javaScriptExecuteCallback        (const std::string& sScript, const std::function<void(const QVariant &)>& resultCallback) override;

    // -------------------------------
    // --- Configuration functions ---
    // -------------------------------
    void		do_loadImages        (bool bLoadImages) override;
    void        do_loadStyleSheets   (bool bLoadStyleSheets) override;

    // ---------------------------------
    // --- PRIVATE: Window functions ---
    // ---------------------------------
    void        do_refresh			() override;
    void        do_show				() override;
    void        do_hide				() override;
    void        do_sizeGet			(int& x, int& y) const override;
    void        do_sizeSet			(int x, int y) override;
    void        do_close 			(bool bForce) override;
    void        do_repaint          () override;
    void        do_focusActivate    () override;
    void        do_focusDeactivate  () override;
    void		do_sendKeepActive   () override;
    void        do_scroll           (int32_t xScroll, int32_t yScroll) override;
    void        do_scrollByLines    (int32_t iNumLines) override;
    int         do_scrollPosXGet    () const override;
    int         do_scrollPosYGet    () const override;
    void        do_zoomSet          ( float pct ) override;
    float       do_zoomGet          () const override;
    void        do_userKeyEvent     (int eventType, int key, int modifiers) override;
    void        do_userMouseEvent   (int eventType, float xpos, float ypos, int button, int buttons, int modifiers) override;

    // -------------------------------
    // --- PRIVATE: Edit functions ---
    // -------------------------------
    std::string	do_selectionGet		() const override;
    void        do_searchStringSet  (const std::string& sSearchFor) override;
    bool        do_findNext         () override;
    void        do_findEntireWord   (bool val) override;
    void        do_findMatchCase    (bool val) override;
    void        do_markPositions    (const std::string& xpathStrList, bool clearCurrentlyMarked) override;
    void        do_hoverPosition    (const std::string& xpath) override;

    // --------------------------------
    // --- PRIVATE: Timer functions ---
    // --------------------------------
    void		do_continuousTimerStart     (int iMilisecs) override;
    void		do_continuousTimer2Start    (int iMilisecs) override;
    void		do_oneShotTimerStart        (int iMilisecs) override;
    void		do_continuousTimerStop      () override;
    void		do_continuousTimer2Stop     () override;
    void		do_oneShotTimerStop         () override;

    // -------------------------------
    // --- PRIVATE: Misc functions ---
    // -------------------------------
    bool        do_supportsDynamicDom	() const override;
    void        do_clearCookies         () override;
    std::string	do_typeNameGet          () const override;
    wxWindow*	do_guiWx                () const override;

    // ----------------------------------------
    // --- PRVATE: QtWebKit event functions ---
    // ----------------------------------------

private slots:
    void    slotLoadStarted     ();
    void    slotLoadProgress    (int iProgress);
    void    slotLoadFinished    (bool bOk);
    void    delayPageLoadedSlot ();
    void    slotContinuousTimer ();
    void    slotContinuousTimer2();

    // -------------------------------------
    // --- PRVATE: Mozilla specific data ---
    // -------------------------------------
private:
    std::chrono::high_resolution_clock::time_point   m_lastPageLoadTime;
    QWebEngineView*                 m_pWebView = nullptr;
    crawl::BrowserViewIF*           m_browserView = nullptr;
    QWebChannel                     m_webChannel;
    WebChannelBridge                m_webChannelBridge;
    long long                       m_iPageLoadsTotal;
    QString                         m_javascriptInject;

    //FIXME OLD QWebEngineView  WebkitNetworkAccessManagerQt*   m_networkAccessMgr;
    QTimer*                         m_continuousTimer;
    QTimer*                         m_continuousTimer2;
    QTimer*                         m_delayPageLoadedSignalTimer;
    int                             m_delayPageLoadedSignalInMilliseconds;
    mutable std::string             m_pageHtml;
};

} // END namespace crawl

#endif // WEBKIT_BROWSER_QT_H



