#include "Crawler.h"

#include <iostream>
#include <fstream>

////#include <MozBrowserWx.h>
#include <containers/UrlQueue.h>
#include <containers/DomActionMgr.h>
#include <containers/DomSearchMgr.h>
#include <containers/ModifierMgr.h>
#include <containers/SettingsMgr.h>
#include <SignalsManager.h>
#include <ScriptingClassIF.h>
#include <DomMouseEventIF.h>
#include <DomKeyEventIF.h>
#include <Configuration.h>
#include <containers/NetworkActivityLogger.h>


using namespace boost::placeholders;
namespace b = boost;


namespace crawl {

    using namespace std;
    typedef boost::shared_ptr<std::ostream>		OstreamPtrT;
/*

*/
    Crawler::Crawler( boost::shared_ptr<crawl::WebBrowserIF> pMozBrowser
             , Url const& siteUrl
             , const DataWriterIF::DataWriterVecT& dataWriters
             , boost::shared_ptr<crawl::ScriptingClassIF> pScriptClass
             , boost::shared_ptr<Configuration> pConfig
            )	:
        ScriptMinerIF(pScriptClass, pConfig )
          , m_pMozBrowser(nullptr)
          , m_stringSearch(dataWriters, this->config())
          , m_siteUrl(siteUrl)
          , m_urlQueue(false, this)
          //, m_wordMonitor()
          //, m_networkActivityLogger()
          , m_bProgressOutput(false)
          , m_bDebugOutput(false)
          //, m_currentUrl()
          //, m_pLinearDom()
          //, m_pLinearDomSearch()
          //, m_pLinksGetter()
          , m_pDomActionMgr(new DomActionMgr)
          , m_pDomSearchMgr(new DomSearchMgr)
          , m_pModifierMgr(new ModifierMgr)
          , m_pSettingsMgr(new SettingsMgr)
          //, m_OnScanningDone()
          //, m_includeUrlFunctors()
          //, m_excludeUrlFunctors()
          //, m_connectionNetProgress()
          //, m_connectionPageLoaded()
          //, m_connectionLoadUri()
          //, m_connectionMouseDown()
          , m_iCountActivityAny(0)
    {
        assignWebBrowser(pMozBrowser);
        reset();
    }

    void Crawler::assignWebBrowser  ( boost::shared_ptr<crawl::WebBrowserIF> pMozBrowser )
    {
        m_pMozBrowser = pMozBrowser;
        disconnectSignals();
        connectSignals();
    }


    Crawler::~Crawler()
    {
        disconnectSignals();
    }

    void Crawler::reset  ()
    {
        m_bProgressOutput   = false;
        m_bDebugOutput      = false;
        m_currentUrl        = Url();
    }

    void Crawler::init()
    {

    }

    void Crawler::clearForReloadScript()
    {
        m_includeUrlFunctors.clear();
        m_excludeUrlFunctors.clear();
        m_pSettingsMgr->clear();
        if (webBrowser()) {
            webBrowser()->clearForReloadScript();
        }

        m_pDomSearchMgr->clear();

        // TODO: Seems to mess up handler selection sometimes.
//        m_pDomActionMgr->clear();
//        m_pDomSearchMgr->clear();
//        m_pModifierMgr->clear();
//        m_pSettingsMgr->clear();
    }

    void Crawler::outputNameSet ( const std::string sBaseOutputName )
    {
        m_stringSearch.outputNameSet(sBaseOutputName);
    }

    void Crawler::restart( const std::string sBaseOutputName )
    {
        m_stringSearch.restart(sBaseOutputName);
        reset();
    }

    void Crawler::dataBaseOutputStreamClose ()
    {
        m_stringSearch.dataWriterOutputClose();
    }

    /** Set value of current domNode as the actual current value. */
    void Crawler::domNodeToCurrentValue()
    {
        if ( m_pLinearDomSearch && m_pLinearDomSearch->curElemPtr() ) {
            m_stringSearch.newSearchString( m_pLinearDomSearch->curElemPtr()->stringDataUTF8(), "" );
        }
        else {
            m_stringSearch.newSearchString( "", "" );
        }
    }

    /** Rebuilds LinearDom and current URI. Usually needed if (crawler script) actions causes new dom elements to be created.. */
    void Crawler::buildLinearDom()
    {
        m_currentUrl 		= Url( webBrowser()->currentUri() );
        m_pLinearDom        = webBrowser()->createLinearDom(&m_wordMonitor);
        m_pLinearDomSearch	= LinearDomSearch::Ptr 	( new LinearDomSearch(*m_pLinearDom, runMode()) );
        m_pLinksGetter		= LinksGetter::Ptr		( new LinksGetter(m_pLinearDom, m_siteUrl) );

        // Clear look-for-word stop and start positions
        lfwDomStartPosSet(0);
        lfwDomStopPosSet(0);
        webBrowser()->signalsManager()->signalDomChanged(*webBrowser());

    }

    string Crawler::siteUrl() const
    {
        return m_siteUrl.string();
    }


    void Crawler::createProgressOut( const std::string& /*sName*/ )
    {
        ////m_pProgressOutStream = boost::shared_ptr<std::ofstream>(new std::ofstream((sName+".progress").c_str()) );
    }

    void Crawler::writeProgress( const std::string& /*sMsg*/, bool /*bAppendEndl*/ )
    {
     //   printf( "XX: Crawler::writeProgress: %s", sMsg.c_str() );
        //	if ( !progressOutput() ) return;
        //	if (m_pProgressOutStream) 		*m_pProgressOutStream << sMsg;
        //	if ( bAppendEndl ) {
        //		printf( "\n" );
        //		if (m_pProgressOutStream) 	*m_pProgressOutStream << std::endl;
        //	}
    }

    void  Crawler::writeProgress( const boost::format& /*msg*/, bool /*bAppendEndl*/ )
    {
     //   writeProgress( boost::str(msg), bAppendEndl );
    }

    // --------------------
    // --- PUBLIC: Info ---
    // --------------------


    // -------------------------------
    // --- Configuration functions ---
    // -------------------------------

    /** Enable/disable loading of images in the crawler/browser. */
    void Crawler::loadImages (
            bool bLoadImages )		///< [in]
    {
        webBrowser()->loadImagesSet(bLoadImages);
    }

    /** Add pattern that all URLs }must} match in order to be loaded.
    \note If you want to utilize this you must subscribe to the pageLoaded signal
    and implement something similar to ScriptMiner::slotLoadUri()
    \sa configAddExcludeUrl(), checkUrlInclude() */
    void Crawler::configAddIncludeUrl (
            const std::string sPattern, 				///< [in] Pattern to compare against URL about to be loaded.
            StringCompareFunT fnCompare					///< [in] Funtion to use when comparing.
            )
    {
        // Create and add a functor which compares the designated pattern with some string
        // using the two argument compare function given. Note the functor is a new
        // compare function with the pattern bound so only one parameter is left in the
        // functor - namely the incoming URL we wish to compare against the pattern.
        m_includeUrlFunctors.push_back( boost::bind(fnCompare, _1, sPattern) );
    }


    void Crawler::configAddExcludeUrl (
            const std::string sPattern, 				///< [in] Pattern to compare against URL about to be loaded.
            StringCompareFunT fnCompare					///< [in] Funtion to use when comparing.
            )
    {
        // Create and add a functor which compares the designated pattern with some string
        // using the two argument compare function given. Note the functor is a new
        // compare function with the pattern bound so only one parameter is left in the
        // functor - namely the incoming URL we wish to compare against the pattern.
        m_excludeUrlFunctors.push_back( boost::bind(fnCompare, _1, sPattern) );
    }

    //{	return  boost::algorithm::contains ( sInput, sTest ); 		}

    // ------------------------
    // --- Helper functions ---
    // ------------------------

    /** See if given URL is ok to load according to the include list.
    The URL is considered ok, if it matches any of the (pattern,function) pairs.
    \sa configAddIncludeUrl(), checkUrlExclude()
    \return true if URL is found in a least one of the (pattern,function) pairs, meaning it }should} be loaded. */
    bool Crawler::checkUrlInclude (
            std::string const& sUrl 		///< [in] In URL to check.
            )	const
    {
        if ( m_includeUrlFunctors.empty() )
            return true;	// If no patterns all Urls are considered OK.
        UrlCompareVecT::const_iterator it;
        for ( it = m_includeUrlFunctors.begin(); it != m_includeUrlFunctors.end(); ++it ) {
            if ( (*it)(sUrl) )
                return true;
        }
        return false;										// No matches - URL is NOT ok to load.
    }

    /** See if given URL should }not} be loaded according to include list.
    If the URL matches any of the (pattern,function) pairs then it should }not}
    be loaded and this function returns true.
    \sa configAddExcludeUrl(), checkUrlInclude()
    \return true if URL is found in a least one of the (pattern,function) pairs, meaning it should }not} be loaded. */
    bool Crawler::checkUrlExclude (
            std::string const& sUrl 		///< [in] In URL to check.
            )	const
    {
        UrlCompareVecT::const_iterator it;
        for ( it = m_excludeUrlFunctors.begin(); it != m_excludeUrlFunctors.end(); ++it ) {
            if ( (*it)(sUrl) )
                return true;
        }
        return false;					// No matches - URL should NOT be excluded, i.e. it's ok to load.
    }


    /** Test if URL in question should actually be loaded. */
    bool Crawler::okToLoadUrl (
            std::string const& sUrl
            ) const
    {
        using namespace std;
        bool okToLoad = true;
        if ( !checkUrlInclude 	( sUrl ) )	okToLoad = false;
        if ( checkUrlExclude 	( sUrl ) )	okToLoad = false;
        return okToLoad;
    }


    // --------------------------
    // --- PRIVATE: Functions ---
    // --------------------------
    /** Slot called  net progress.*/
    bool Crawler::slotNetProgress(
            void* aRequest
            , boost::uint32_t networkOpType
            , const std::string& sUri
            )
    {
        const NetworkOperationType netOpType = static_cast<NetworkOperationType>(networkOpType);
        ++m_iCountActivityAny;
        m_pMozBrowser->activityCounterSet(m_iCountActivityAny);
        if (netOpType == NetworkOperationType::NetworkRequestStart) {

            bool doLoad = true;
            if ( !okToLoadUrl( sUri) ) {
    //          printf("CANCEL LOAD OF: '%s'\n", sUri.c_str());
                doLoad = false;
                webBrowser()->cancelUriLoadRequest( aRequest, sUri );
            }
            return doLoad;
        }
        if (m_networkActivityLogger) {
            const QString&& url = QString::fromUtf8(sUri.c_str());
            if (netOpType == NetworkOperationType::NetworkRequestStart)
                m_networkActivityLogger->pushFront(url, NetworkOperationType::NetworkRequestStart);
            else
                m_networkActivityLogger->updateEntry(url, netOpType);
        }
        return true; // Unless we are in NetworkRequestStart this value will be ignored
    }



    bool Crawler::slotLoadUri(
            crawl::WebBrowserIF& /*mozBrowser*/ 		///< Pointer to MozBrowser
            , const std::string&	/*sUri*/        ///< Uri about to be loaded
            )
    {
        return false;
    }




    void Crawler::slotPageLoaded(
            crawl::WebBrowserIF&  	///< Pointer to MozBrowser
            )
    {
    }


    void Crawler::slotMouseDown   (
            crawl::WebBrowserIF& browser
            , boost::shared_ptr<crawl::DomMouseEventIF> pMouseEvent )
    {
        if ( 2 == pMouseEvent->button() ) {
            printf("ML XX: slotMouseDown btn: %d cur URI: %s\n", pMouseEvent->button(), browser.currentUri().c_str() );
            //mozBrowser()->loadUri( mozBrowser()->currentUri() );
        }
    }

    void Crawler::connectSignals   ()
    {
        m_connectionNetProgress = webBrowser()->signalsManager()->connectOnNetProgress  ( boost::bind(&Crawler::slotNetProgress,this, _1, _2, _3    ) );
        m_connectionPageLoaded 	= webBrowser()->signalsManager()->connectPageLoaded     ( boost::bind(&Crawler::slotPageLoaded, this, _1            ) );
        m_connectionLoadUri		= webBrowser()->signalsManager()->connectOnLoadUri      ( boost::bind(&Crawler::slotLoadUri, 	this, _1, _2        ) );
        m_connectionMouseDown   = webBrowser()->signalsManager()->connectMouseDown      ( boost::bind(&Crawler::slotMouseDown, 	this, _1, _2        ) );
    }

    void Crawler::disconnectSignals   ()
    {
        m_connectionNetProgress.disconnect();
        m_connectionPageLoaded.disconnect();
        m_connectionLoadUri.disconnect();
        m_connectionMouseDown.disconnect();
    }

    boost::shared_ptr<NetworkActivityLogger> Crawler::networkActivityLogger() const
    {
        return m_networkActivityLogger;
    }

    void Crawler::networkActivityLoggerSet(const boost::shared_ptr<NetworkActivityLogger>& networkActivityLogger)
    {
        m_networkActivityLogger = networkActivityLogger;
    }


} // END namespace crawl



