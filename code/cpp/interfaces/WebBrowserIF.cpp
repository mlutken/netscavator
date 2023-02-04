#include "WebBrowserIF.h"
#include <iostream>
#include <QThread>
#include <SignalsManager.h>
#include <LinearDomIF.h>
#include <DomNodeIF.h>
#include <utils/utils.h>
#include <Configuration.h>

using namespace std;

namespace crawl {

    WebBrowserIF::WebBrowserIF (boost::shared_ptr<Configuration> c)
        : QObject(nullptr)      // Make sure Qt does not do any memory management on this object!
        , m_config(c)
        , m_pSignalsManager     ( new SignalsManager )
        , m_iCount_ACTIVITY_ANY (0)
        , m_eRunMode            (c->runMode())
        , m_pCurrentLinearDom   ()
        , m_sCurrentLoadingUri 	("")
        , m_delayPageLoadedSignalInMilliseconds(50)
        , m_bPageLoading        (false)
        , m_bDoLoadImages       (true)
        , m_bDoLoadStyleSheets  (true)
    {
        // TODO: If possible make signalsManager() a real member of this class
        if ( signalsManager() ) {
            m_connectionPageLoaded 	= signalsManager()->connectPageLoaded		( boost::bind(&WebBrowserIF::slotPageLoaded, 	this, _1		) );
            m_connectionLoadUri		= signalsManager()->connectOnLoadUri		( boost::bind(&WebBrowserIF::slotLoadUri,       this, _1, _2	) );
        }
    }

    void WebBrowserIF::clearForReloadScript()
    {
        scriptHtmlEntitiesReplaceClear();
        do_clearForReloadScript();
    }

    // -----------------------------
    // --- Public slot functions ---
    // -----------------------------
    void WebBrowserIF::markPositions(const std::vector<int>& domPositions, bool clearCurrentlyMarked)
    {
        if (!currentLinearDom()) { return; }
        const auto xpathStrList = currentLinearDom()->toXPathStringList(domPositions);
        markPositions(xpathStrList, clearCurrentlyMarked);
    }

    void WebBrowserIF::markPositionsClear(const std::vector<int>& domPositions)
    {
        const bool clearCurrentlyMarked = true;
        markPositions(domPositions, clearCurrentlyMarked);
    }


    void WebBrowserIF::markPosition(int domPos, bool clearCurrentlyMarked)
    {
        if (!currentLinearDom()) { return; }
        const auto xpathStr = currentLinearDom()->toXPath(domPos).toString();
        markPositions(xpathStr, clearCurrentlyMarked);
    }

    void WebBrowserIF::markPositionClear(int domPos)
    {
        const bool clearCurrentlyMarked = true;
        markPosition(domPos, clearCurrentlyMarked);
    }

    // --------------------------------
    // --- Get interfaces functions ---
    // --------------------------------
    boost::shared_ptr<LinearDomIF> WebBrowserIF::createLinearDom (WordMonitor* wordMonitor)
    {
        m_wordMonitor = wordMonitor;
        m_pCurrentLinearDom = do_createLinearDom();
        return m_pCurrentLinearDom;
    }


    boost::shared_ptr<LinearDomIF> WebBrowserIF::currentLinearDom ()	const
    {
        return m_pCurrentLinearDom;
    }

    QUrl WebBrowserIF::currentUrl() const
    {
        return QUrl(currentUri().c_str());
    }

    bool crawl::WebBrowserIF::loadUri(const std::string& sUri)
    {
        return do_loadUri(sUri);
    }

    bool WebBrowserIF::loadUrl(const QUrl& url)
    {
        return loadUri(toString(url.toString()));
    }

    QString WebBrowserIF::htmlQString() const
    {
        return toQString(std::string(html()));
    }

    // ----------------------------
    // --- Javascript functions ---
    // ----------------------------

    bool WebBrowserIF::javaScriptExecuteRetVal (
            const std::string& sScript
            , std::string& sScriptReturnValue )
    {
        return do_javaScriptExecuteRetVal(sScript, sScriptReturnValue );
    }

    bool WebBrowserIF::javaScriptExecute (
            const std::string& sScript
            )
    {
        std::string sIgnoreRetval;
        return javaScriptExecuteRetVal( sScript, sIgnoreRetval );
    }

    void WebBrowserIF::javaScriptExecuteCallback(const std::string& sScript,
                                                 const std::function<void (const QVariant&)>& resultCallback)
    {
        do_javaScriptExecuteCallback(sScript, resultCallback);
    }


    // -------------------------------
    // --- Configuration functions ---
    // -------------------------------
    void  WebBrowserIF::runModeSet ( crawl::RunModeE eRunMode )
    {
        m_eRunMode = eRunMode;
    }

    crawl::RunModeE	WebBrowserIF::runMode () const
    {
        return m_eRunMode;
    }


    // -----------------------------------
    // --- PROTECTED: helper functions ---
    // -----------------------------------
    /** Call this from derived class as }last} thing before returning from constructor(s). */
    void WebBrowserIF::initCommonDefaults ()
    {
        m_sCurrentLoadingUri 	= "";
        m_bPageLoading 			= false;

        initDerived();

        m_connectionPageLoaded 	= signalsManager()->connectPageLoaded		( boost::bind(&WebBrowserIF::slotPageLoaded, 	this, _1		) );
        m_connectionLoadUri		= signalsManager()->connectOnLoadUri		( boost::bind(&WebBrowserIF::slotLoadUri,       this, _1, _2	) );
    }

    // ---------------------------------
    // --- PRIVATE: helper functions ---
    // ---------------------------------

    boost::shared_ptr<SignalsManager> WebBrowserIF::do_signalsManager   ()	const
    {
        return m_pSignalsManager;
    }


    /** Called just before pageload is initiated.
    If you want to prevent the pageload return true from this function. */
    bool WebBrowserIF::slotLoadUri(
            WebBrowserIF& /*browser*/,              ///< Reference to browser
            const std::string&			sUri	///< Uri about to be loaded
            )
    {
        m_sCurrentLoadingUri 	= sUri;
        m_bPageLoading 			= true;
        return false;
    }

    /** Slot called when whole page is loaded.*/
    void WebBrowserIF::slotPageLoaded(
            WebBrowserIF& /*browser*/ 	///< Reference to browser
            )
    {
        resetPageRequestCounters();
        m_sCurrentLoadingUri	= "";
        m_bPageLoading 			= false;
//        cout <<"WebBrowserIF::slotPageLoaded: "<< QThread::currentThreadId() << endl;
    }
    
    const std::map<std::string, std::string>& WebBrowserIF::scriptHtmlEntitiesReplace() const
    {
        return m_scriptHtmlEntitiesReplace;
    }

    void WebBrowserIF::scriptHtmlEntitiesReplaceAdd(const string& lookFor, const string& replaceWith)
    {
        m_scriptHtmlEntitiesReplace[lookFor] = replaceWith;
    }
    
    void WebBrowserIF::scriptHtmlEntitiesReplaceSet(const std::map<std::string, std::string>& scriptHtmlEntitiesReplace)
    {
        m_scriptHtmlEntitiesReplace = scriptHtmlEntitiesReplace;
    }

    void WebBrowserIF::scriptHtmlEntitiesReplaceClear()
    {
        m_scriptHtmlEntitiesReplace.clear();
    }
    
    void WebBrowserIF::configurationSet(const boost::shared_ptr<Configuration>& config)
    {
        m_config = config;
    }
    
    int WebBrowserIF::delayPageLoadedSignalTimeInMs() const
    {
        return m_delayPageLoadedSignalInMilliseconds;
    }
    
    void WebBrowserIF::delayPageLoadedSignalTimeInMsSet(int milliseconds)
    {
        m_delayPageLoadedSignalInMilliseconds = milliseconds;
    }
    
    WordMonitor *WebBrowserIF::wordMonitor() const
    {
        return m_wordMonitor;
    }
    
    void WebBrowserIF::wordMonitorSet(WordMonitor *wordMonitor)
    {
        m_wordMonitor = wordMonitor;
    }
    
    
    
} // END namespace crawl

