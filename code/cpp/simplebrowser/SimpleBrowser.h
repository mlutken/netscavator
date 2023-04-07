#ifndef SIMPLE_BROWSER_H
#define SIMPLE_BROWSER_H

#include <chrono>
#include <WebBrowserIF.h>
#include <BrowserViewIF.h>
#include <applicationutils/QtHttpDownloader.h>


namespace crawl {
class SimpleWebView;

/** Toplevel (QT WebKit) browser class. */
class SimpleBrowser : public crawl::WebBrowserIF
{
    Q_OBJECT
public:
    typedef boost::shared_ptr<SimpleBrowser> 	Ptr;		///< Pointer to a SimpleBrowser

    explicit SimpleBrowser ( crawl::BrowserViewIF* browserView, boost::shared_ptr<crawl::Configuration> c);
    ~SimpleBrowser() override;

signals:
    void    loadUriSignal(const QString& uri);

private:

    // -------------------------------
    // --- PRIVATE: Init functions ---
    // -------------------------------
    virtual void            do_initDerived          () override;
    virtual void            do_setWebView           (BrowserViewIF* browserView) override;
    void                    do_clearForReloadScript () override {}

    // --------------------------------
    // --- PRIVATE: Get interfaces functions ---
    // --------------------------------
    virtual boost::shared_ptr<crawl::LinearDomIF>   do_createLinearDom  () override;
    virtual QString                                 do_pageHash         () const override;
    crawl::BrowserViewIF*                           do_browserView      () const override { return m_browserView; }

    // ------------------------------
    // --- PRIVATE: Url functions ---
    // ------------------------------
    virtual std::string 	do_currentUriGet        () const ;
    std::string             do_requestedUriGet      () const override;
    virtual bool            do_loadUri              ( const std::string& sUri );
    virtual void 			do_cancelPageLoad       () override;
    //        virtual std::string     do_currentLoadingUrl() const = 0;
    virtual bool            do_goBack() const;
    virtual bool            do_cancelUriLoadRequest  ( void* requestID, const std::string& sUri );

    // ------------------------------
    // --- PRIVATE: Dom functions ---
    // ------------------------------
    std::string_view                                do_html             () const override;
    bool                                            do_nodeClick        (const std::string& xpath) override;
    bool                                            do_inputSet         (const std::string& xpath, const std::string& input) override;
    virtual boost::shared_ptr<crawl::DomNodeIF>     do_getElementById   ( const std::string& sID ) const override;
    virtual boost::shared_ptr<crawl::DomNodeIF>     do_makeDomNode      (void *nativeDomNodePtr) override;

    // -------------------------------------
    // --- PRIVATE: Pagestatus functions ---
    // -------------------------------------
    void                    do_triggerPageLoaded                () override;
    virtual bool			do_checkPotentialAjaxLoadCompleted	( const boost::posix_time::time_duration& deltaTime ) const;
    virtual void			do_resetPageRequestCounters			() ;
    virtual int             do_infoLastNetworkError             () const override;
    int                     do_activityRequestStartCount        () const override { return 0; }
    int                     do_activityRequestFinishedCount     () const override { return 0; }

    // -------------------------------------
    // --- PRIVATE: Javascript functions ---
    // -------------------------------------
    bool        do_javaScriptExecuteRetVal          (   const std::string& sScript, std::string& sScriptReturnValue ) override;
    void        do_javaScriptExecuteCallback        (const std::string& sScript, const std::function<void(const QVariant &)>& resultCallback) override;


    // -------------------------------
    // --- Configuration functions ---
    // -------------------------------
    virtual void		do_loadImages				( bool bLoadImages      );
    virtual void        do_loadStyleSheets			( bool bLoadStyleSheets );

    // ---------------------------------
    // --- PRIVATE: Window functions ---
    // ---------------------------------
    virtual void        do_refresh			();
    virtual void        do_show				();
    virtual void        do_hide				();
    virtual void        do_sizeGet			( int& x, int& y ) const;
    virtual void        do_sizeSet			( int x, int y 	);
    virtual void        do_close 			( bool bForce );
    virtual void        do_repaint          () override;
    virtual void        do_focusActivate    ();
    virtual void        do_focusDeactivate  ();
    virtual void		do_sendKeepActive   ();
    virtual void        do_scroll         ( boost::int32_t xScroll, boost::int32_t yScroll );
    virtual void        do_scrollByLines    ( boost::int32_t iNumLines );
    virtual int         do_scrollPosXGet    () const override;
    virtual int         do_scrollPosYGet    () const override;
    virtual void        do_zoomSet          ( float pct ) override;
    virtual float       do_zoomGet          () const override;
    virtual void        do_userKeyEvent     (int eventType, int key, int modifiers) override;
    virtual void        do_userMouseEvent   (int eventType, float xpos, float ypos, int button, int buttons, int modifiers) override;

    // -------------------------------
    // --- PRIVATE: Edit functions ---
    // -------------------------------
    std::string	do_selectionGet		() const override;
    void        do_searchStringSet  ( const std::string& sSearchFor ) override;
    bool        do_findNext         () override;
    void        do_findEntireWord   ( bool val ) override;
    void        do_findMatchCase    ( bool val ) override;
    void        do_markPositions    (const std::string& xpathStrList, bool clearCurrentlyMarked) override;
    void        do_hoverPosition    (const std::string& xpath) override;

    // --------------------------------
    // --- PRIVATE: Timer functions ---
    // --------------------------------
    virtual void		do_continuousTimerStart     ( int iMilisecs );
    virtual void		do_continuousTimer2Start    ( int iMilisecs );
    virtual void		do_oneShotTimerStart        ( int iMilisecs );
    virtual void		do_continuousTimerStop      ();
    virtual void		do_continuousTimer2Stop     ();
    virtual void		do_oneShotTimerStop         ();

    // -------------------------------
    // --- PRIVATE: Misc functions ---
    // -------------------------------
    virtual bool        do_supportsDynamicDom	() const override;
    virtual void        do_clearCookies         () override;
    virtual std::string	do_typeNameGet          () const;
    virtual	wxWindow*	do_guiWx                () const;

    // ----------------------------------------
    // --- PRVATE: QtWebKit event functions ---
    // ----------------------------------------

private slots:
    void    slotLoadStarted     ();
    void    slotLoadProgress    ( int iProgress  );
    void    slotContinuousTimer ();
    void    slotContinuousTimer2();
    void    linkClickedSlot     (BrowserViewIF* browserView, const QUrl& url);

    // -----------------------------------------
    // --- PRVATE: Helper functions and data ---
    // -----------------------------------------
private:
    // --- PRIVATE: Handler functions ---
    void            handleHtmlPageDownloadedCb  (QByteArray&& data, const QUrl& url, bool downloadedOk);
    // --- PRIVATE: Helper functions ---
    QString         pageHtmlQString() const;

    std::chrono::high_resolution_clock::time_point   m_lastPageLoadTime;
    crawl::BrowserViewIF*           m_browserView;
    SimpleWebView*                  m_simpleWebView = nullptr;
    QtHttpDownloader                m_httpDownloader;
    long long                       m_iPageLoadsTotal;
    QTimer*                         m_continuousTimer;
    QTimer*                         m_continuousTimer2;
    int                             m_delayPageLoadedSignalInMilliseconds{};
    QByteArray                      m_currentPageHtmlData;  // Original bytearry from QtHttpDownloader
    mutable std::string             m_currentPageHtml;      // used only if we need to convert m_currentPageHtmlData to utf-8
    std::string                     m_currentUri;
    std::string                     m_currentLoadingUri;
};


} // END namespace crawl

#endif // SIMPLE_BROWSER_H



