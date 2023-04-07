#pragma once

#include <string>
#include <string_view>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/function.hpp>
#include <boost/signals2/signal.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <QObject>
#include <QString>
#include <QUrl>
#include <interfaces_types.h>

class SignalsManager;
class wxWindow;
class QWebView;

namespace crawl {
    class WebkitNetworkAccessManagerQt;
    class LinearDomIF;
    class DomNodeIF;
    class WordMonitor;
    class BrowserViewIF;
    class Configuration;

    /** Base browser class. */
    class WebBrowserIF : public QObject, public boost::enable_shared_from_this<WebBrowserIF>
    {
        Q_OBJECT
    public:
        // ---------------------
        // --- PUBLIC: Types ---
        // ---------------------
        typedef boost::function< bool ( std::string const&, std::string const& ) >		StringCompareFunT;

        // ---------------------------------------------
        // --- PUBLIC: Constructors / Init functions ---
        // ---------------------------------------------
        explicit WebBrowserIF (boost::shared_ptr<crawl::Configuration> c);
        virtual 	~WebBrowserIF() {}

        void    setWebView              (BrowserViewIF* browserView)    { do_setWebView(browserView);   }
        void    initDerived             ()                              { do_initDerived();             }
        void	clearForReloadScript    ();

    signals:
        void    pageLoadProgressSignal (int pct);
        void    domPosSelectedSig      (const QString& xpath, const QString& innerText);

        // -----------------------------
        // --- Public slot functions ---
        // -----------------------------
    public slots:
        void        markPositions       (const std::string& xpathStrList, bool clearCurrentlyMarked)       { return do_markPositions(xpathStrList, clearCurrentlyMarked); }
        void        markPositions       (const std::vector<int>& domPositions, bool clearCurrentlyMarked);
        void        markPositionsClear  (const std::vector<int>& domPositions);
        void        markPosition        (int domPos, bool clearCurrentlyMarked);
        void        markPositionClear   (int domPos);
        void        hoverPositions      (const std::string& xpath)                                      { return do_hoverPosition(xpath); }
        void        triggerPageLoaded   ()                                                              { do_triggerPageLoaded(); }

    public:

        // --------------------------------
        // --- Get interfaces functions ---
        // --------------------------------
        boost::shared_ptr<LinearDomIF>      createLinearDom     (WordMonitor* wordMonitor);
        boost::shared_ptr<LinearDomIF>      currentLinearDom    ()	const;
        boost::shared_ptr<SignalsManager>   signalsManager      ()	const	{ return do_signalsManager();   }
        QString                             pageHash            () const    { return do_pageHash(); }
        crawl::BrowserViewIF*               browserView         () const    { return do_browserView(); }

        // ---------------------
        // --- Url functions ---
        // ---------------------
        QUrl            currentUrl              () const;
        std::string 	currentUri              () const                    { return do_currentUriGet(); }
        std::string 	requestedUri            () const                    { return do_requestedUriGet(); }
        bool 			loadUri                 (const std::string& sUri);
        bool 			loadUrl                 (const QUrl& url);
        void 			cancelPageLoad          ()                          { do_cancelPageLoad();  }

//        std::string     currentLoadingUri     () const                    { return do_currentLoadingUriGet(); }
        bool            goBack                  () const                    { return do_goBack();               }
        bool            cancelUriLoadRequest    (void* requestID, const std::string& sUri) { return do_cancelUriLoadRequest(requestID, sUri ); }

        // ---------------------
        // --- Dom functions ---
        // ---------------------
        std::string_view                    html            () const { return do_html(); }
        QString                             htmlQString     () const;
        boost::shared_ptr<DomNodeIF>        getElementById  (const std::string& sID) const      { return do_getElementById(sID); }
        bool                                nodeClick       (const std::string& xpath)          { return do_nodeClick(xpath); }
        bool                                inputSet        (const std::string& xpath, const std::string& input)  {return do_inputSet(xpath, input); }
        boost::shared_ptr<crawl::DomNodeIF> makeDomNode     (void *nativeDomNodePtr) { return do_makeDomNode(nativeDomNodePtr);}

        // -------------------------------------
        // --- Pagestatus/Progress functions ---
        // -------------------------------------
        const std::string	currentLoadingUri               () const 	{ return m_sCurrentLoadingUri; 	}
        bool				pageLoading                     () const 	{ return m_bPageLoading; 		}
        bool				domValid                        () const 	{ return !pageLoading(); 		}
        void                activityCounterSet              (unsigned int iCount) { m_iCount_ACTIVITY_ANY = iCount;   }
        unsigned int        activityCounter                 () const                { return m_iCount_ACTIVITY_ANY;     }

        bool                checkPotentialAjaxLoadCompleted	( const boost::posix_time::time_duration& deltaTime ) const { return do_checkPotentialAjaxLoadCompleted(deltaTime); }
        void                resetPageRequestCounters		() { do_resetPageRequestCounters(); }
        int                 infoLastNetworkError            () const { return do_infoLastNetworkError(); }
        int                 activityRequestStartCount       () const { return do_activityRequestStartCount(); }
        int                 activityRequestFinishedCount    () const { return do_activityRequestFinishedCount(); }



        // ----------------------------
        // --- Javascript functions ---
        // ----------------------------
        bool    javaScriptExecuteRetVal     (const std::string& sScript, std::string& sScriptReturnValue);
        bool    javaScriptExecute           (const std::string& sScript);
        void    javaScriptExecuteCallback   (const std::string& sScript, const std::function<void(const QVariant &)> &resultCallback);


        // -------------------------------
        // --- Configuration functions ---
        // -------------------------------
        void            loadImagesSet		(bool bLoadImages)          { do_loadImages(bLoadImages); m_bDoLoadImages = bLoadImages; }
        bool            loadImages          () const                    { return m_bDoLoadImages; }

        void            loadStyleSheetsSet	(bool bLoadStyleSheets)     { do_loadStyleSheets(bLoadStyleSheets); m_bDoLoadStyleSheets = bLoadStyleSheets; }
        bool            loadStyleSheets     () const                    { return m_bDoLoadStyleSheets; }

        void            runModeSet          (crawl::RunModeE eRunMode);
        crawl::RunModeE	runMode             () const;

        // ------------------------
        // --- Window functions ---
        // ------------------------
        void        refresh				() 							{ do_refresh();     }
        void        show				() 							{ do_show();        }
        void        hide				() 							{ do_hide();        }
        void        sizeGet				(int& x, int& y) const      { do_sizeGet(x,y);  }
        void        sizeSet				(int x, int y)              { do_sizeSet(x,y);  }
        void        close 				(bool bForce)				{ do_close(bForce); }
        void        repaint 			()                          { do_repaint();     }
        void        focusActivate       ()                          { do_focusActivate();   }
        void        focusDeactivate     ()                          { do_focusDeactivate(); }
        void		sendKeepActive 		()                          { do_sendKeepActive();  }
        void        scroll              (int32_t x, int32_t y)      { do_scroll(x,y);}
        void        scrollByLines       (int32_t iNumLines)         { do_scrollByLines(iNumLines); }
        int         scrollPosXGet       () const                    { return do_scrollPosXGet(); }
        int         scrollPosYGet       () const                    { return do_scrollPosYGet(); }
        void        zoomSet             (float pct)                 { do_zoomSet(pct); }
        float       zoom                () const                    { return do_zoomGet(); }
        void        userKeyEvent        (int eventType, int key, int modifiers)
                                            { do_userKeyEvent     (eventType, key, modifiers);}
        void        userMouseEvent      (int eventType, float xpos, float ypos, int button, int buttons, int modifiers)
                                            { do_userMouseEvent   (eventType, xpos, ypos, button, buttons, modifiers); }

        // ----------------------
        // --- Edit functions ---
        // ----------------------
        std::string	selectionGet		() const                            { return do_selectionGet(); }
        void        searchStringSet     (const std::string& sSearchFor)     { return do_searchStringSet(sSearchFor); }
        bool        findNext            ()                                  { return do_findNext();}
        void        findEntireWord      (bool val)                          { return do_findEntireWord(val);   }
        void        findMatchCase       (bool val)                          { return do_findMatchCase(val);    }

        // -----------------------
        // --- Timer functions ---
        // -----------------------
        void		continuousTimerStart                (int iMilisecs)         { do_continuousTimerStart   (iMilisecs);    }
        void		continuousTimer2Start               (int iMilisecs)         { do_continuousTimer2Start  (iMilisecs);    }
        void		oneShotTimerStart                   (int iMilisecs)         { do_oneShotTimerStart      (iMilisecs);    }
        void		continuousTimerStop                 ()						{ do_continuousTimerStop    ();             }
        void		continuousTimer2Stop                ()						{ do_continuousTimer2Stop   ();             }
        void		oneShotTimerStop                    ()						{ do_oneShotTimerStop       ();             }
        int         delayPageLoadedSignalTimeInMs       () const;
        void        delayPageLoadedSignalTimeInMsSet    (int milliseconds);

        // ----------------------
        // --- Misc functions ---
        // ----------------------
        bool            supportsDynamicDom	() const    { return do_supportsDynamicDom(); }
        void            clearCookies		()          { do_clearCookies(); }

        std::string     typeName			() const    { return do_typeNameGet(); }
        wxWindow*       guiWx               () const    { return do_guiWx();       }

        std::string     dbgStringTest       () const    { return "dbgStringTest"; }
        WordMonitor*    wordMonitor         () const;
        void            wordMonitorSet      (WordMonitor *wordMonitor);
        void            configurationSet    (const boost::shared_ptr<Configuration>& config);

        boost::shared_ptr<Configuration> configuration() const { return m_config; }

        const std::map<std::string, std::string>& scriptHtmlEntitiesReplace() const;
        void scriptHtmlEntitiesReplaceAdd   (const std::string& lookFor,  const std::string& replaceWith);
        void scriptHtmlEntitiesReplaceSet   (const std::map<std::string, std::string>& scriptHtmlEntitiesReplace);
        void scriptHtmlEntitiesReplaceClear ();

    protected:
        // -----------------------------------
        // --- PROTECTED: helper functions ---
        // -----------------------------------
        void           initCommonDefaults  ();
    private:
        // -------------------------------
        // --- PRIVATE: Init functions ---
        // -------------------------------
        virtual void            do_initDerived          () = 0;
        virtual void            do_setWebView           (BrowserViewIF* browserView) = 0;
        virtual void			do_clearForReloadScript () = 0;

        // -----------------------------------------
        // --- PRIVATE: Get interfaces functions ---
        // -----------------------------------------
        virtual boost::shared_ptr<LinearDomIF>          do_createLinearDom  () = 0;
        virtual boost::shared_ptr<SignalsManager>       do_signalsManager   () const;
        virtual QString                                 do_pageHash         () const = 0;
        virtual crawl::BrowserViewIF*                   do_browserView      () const = 0;

        // ------------------------------
        // --- PRIVATE: Url functions ---
        // ------------------------------
        virtual std::string     do_currentUriGet            () const = 0;
        virtual std::string     do_requestedUriGet          () const = 0;
        virtual bool 			do_loadUri                  (const std::string& sUri) = 0;
        virtual void 			do_cancelPageLoad           () = 0;

//      virtual std::string     do_currentLoadingUriGet     () const = 0;
        virtual bool            do_goBack                   () const   = 0;
        virtual bool            do_cancelUriLoadRequest     (void* requestID, const std::string& sUri) = 0;

        // ------------------------------
        // --- PRIVATE: Dom functions ---
        // ------------------------------
         virtual std::string_view                       do_html             () const = 0;
         virtual boost::shared_ptr<DomNodeIF>           do_getElementById   (const std::string& sID) const = 0;
         virtual bool                                   do_nodeClick        (const std::string& xpath) = 0;
         virtual bool                                   do_inputSet         (const std::string& xpath, const std::string& input) = 0;
         virtual boost::shared_ptr<crawl::DomNodeIF>    do_makeDomNode      (void *nativeDomNodePtr) = 0; // TODO: Make const

        // -------------------------------------
        // --- PRIVATE: Pagestatus functions ---
        // -------------------------------------
        virtual void			do_triggerPageLoaded                () = 0;
        virtual bool			do_checkPotentialAjaxLoadCompleted	(const boost::posix_time::time_duration& deltaTime) const = 0;
        virtual void			do_resetPageRequestCounters			() = 0;
        virtual int             do_infoLastNetworkError             () const = 0;
        virtual int             do_activityRequestStartCount        () const = 0;
        virtual int             do_activityRequestFinishedCount     () const = 0;

        // -------------------------------------
        // --- PRIVATE: Javascript functions ---
        // -------------------------------------
        virtual bool            do_javaScriptExecuteRetVal  (const std::string& sScript, std::string& sScriptReturnValue) = 0;
        virtual void            do_javaScriptExecuteCallback(const std::string& sScript, const std::function<void(const QVariant &)>& resultCallback) = 0;

        // -------------------------------
        // --- Configuration functions ---
        // -------------------------------
        virtual void            do_loadImages		(bool bLoadImages)      = 0;
        virtual void            do_loadStyleSheets	(bool bLoadStyleSheets) = 0;

        // ------------------------
        // --- PRIVATE: Window functions ---
        // ------------------------
        virtual void        do_refresh              () 						= 0;
        virtual void        do_show             	() 						= 0;
        virtual void        do_hide                 () 						= 0;
        virtual void        do_sizeGet              (int& x, int& y) const  = 0;
        virtual void        do_sizeSet              (int x, int y) 			= 0;
        virtual void        do_close                (bool bForce) 			= 0;
        virtual void        do_repaint              ()                      = 0;

        virtual void        do_focusActivate        ()                      = 0;
        virtual void        do_focusDeactivate      ()                      = 0;
        virtual void		do_sendKeepActive       ()                      = 0;
        virtual void        do_scroll               (int32_t x, int32_t y)  = 0;
        virtual void        do_scrollByLines        (int32_t iNumLines)     = 0;
        virtual int         do_scrollPosXGet        () const                = 0;
        virtual int         do_scrollPosYGet        () const                = 0;
        virtual void        do_zoomSet              ( float pct)            = 0;
        virtual float       do_zoomGet              () const                = 0;
        virtual void        do_userKeyEvent         (int eventType, int key, int modifiers) = 0;
        virtual void        do_userMouseEvent       (int eventType, float xpos, float ypos, int button, int buttons, int modifiers) = 0;

        // -------------------------------
        // --- PRIVATE: Edit functions ---
        // -------------------------------
        virtual std::string	do_selectionGet		() const                            = 0;
        virtual void        do_searchStringSet  (const std::string& sSearchFor)     = 0;
        virtual bool        do_findNext         ()                                  = 0;
        virtual void        do_findEntireWord   (bool val)                          = 0;
        virtual void        do_findMatchCase    (bool val)                          = 0;
        virtual void        do_markPositions    (const std::string& xpathStrList, bool clearCurrentlyMarked) = 0;
        virtual void        do_hoverPosition    (const std::string& xpath)          = 0;

        // --------------------------------
        // --- PRIVATE: Timer functions ---
        // --------------------------------
        virtual void		do_continuousTimerStart (int iMilisecs) = 0;
        virtual void		do_continuousTimer2Start(int iMilisecs) = 0;
        virtual void		do_oneShotTimerStart	(int iMilisecs) = 0;
        virtual void		do_continuousTimerStop	()              = 0;
        virtual void		do_continuousTimer2Stop	()              = 0;
        virtual void		do_oneShotTimerStop     ()              = 0;

        // -------------------------------
        // --- PRIVATE: Misc functions ---
        // -------------------------------
        virtual bool        do_supportsDynamicDom	() const            = 0;
        virtual void        do_clearCookies         ()                  = 0;
        virtual std::string	do_typeNameGet          () const            = 0;
        virtual wxWindow*	do_guiWx                () const            = 0;

        // ---------------------------------
        // --- PRIVATE: Helper functions ---
        // ---------------------------------
        bool				slotLoadUri				(WebBrowserIF& browser, const std::string& sUri);
        void				slotPageLoaded			(WebBrowserIF& browser);

    private:
        // ----------------------------
        // --- PRIVATE: Member data ---
        // ----------------------------
        boost::shared_ptr<Configuration>        m_config;
        boost::shared_ptr<SignalsManager>       m_pSignalsManager;
        std::map<std::string, std::string>      m_scriptHtmlEntitiesReplace; // Extra html entities replace chars from script
        unsigned int                            m_iCount_ACTIVITY_ANY;
        crawl::RunModeE                         m_eRunMode;
        mutable boost::shared_ptr<LinearDomIF>  m_pCurrentLinearDom;
        std::string								m_sCurrentLoadingUri;
        boost::signals2::connection				m_connectionPageLoaded;
        boost::signals2::connection				m_connectionLoadUri;
        WordMonitor*                            m_wordMonitor = nullptr; // So it can be accessed when building the linear DOM
        int                                     m_delayPageLoadedSignalInMilliseconds;
        bool									m_bPageLoading;			///< True if page(URI) is currently loading
        bool                                    m_bDoLoadImages;
        bool                                    m_bDoLoadStyleSheets;
    };

} // END namespace crawl



