#include <iostream>

#include <boost/format.hpp>
#include <boost/system/error_code.hpp>
#include <boost/thread/thread.hpp>
#include <QThread>

#include <cpaf_libs/time/cpaf_time.h>
#include <utils/cpaf_string_utils.hpp>
#include <compression/cpaf_compression_functions.h>
#include <net/cpaf_http_convenience.h>
#include <interfaces_utils.h>
#include <BoxObjectIF.h>
#include <parser/DomActionAbstraction.h>
#include <containers/DomActionMgr.h>
#include <containers/DomSearchMgr.h>
#include <containers/ModifierMgr.h>
#include <containers/SettingsMgr.h>
#include <containers/LookForWordMgr.h>
#include <navigator/StateMachineMgr.h>
#include <navigator/DomNavigator.h>
#include <utils/string_algorithms.h>
#include <utils/utils.h>
#include <ScriptingClassIF.h>
#include <DomMouseEventIF.h>
#include <DomKeyEventIF.h>
#include <SignalsManager.h>
#include <Configuration.h>
#include <Globals.h>
#include <html/ParserDom.h>

#include "ScriptMiner.h"
#include <utils/string_manipulation.h>
#include <utils/StatusFile.h>
#include <interfaces/BrowserViewIF.h>
#include <navigator/NavigateStateBase.h>
#include <navigator/NavigatorActionsExecutor.h>
#include <navigator/NavigatorActionsClickAllExecutor.h>
#include <WebkitNetworkAccessManagerQt.h>
#include <applicationutils/CrawlerCommandQueue.h>
#include <scripting/ScriptExecutor.h>
#include <locale/default_locales.h>
#include <MinerWorker.h>

// FIXMENM: Simulate mouse events test !!!
#include <QWidget>
#include <gui/gui_utils.h>

namespace b = boost;
namespace fs = boost::filesystem;
using crawl::string_compare::G_StringCompareLookUp;
using namespace crawl;
using namespace cpaf;
using namespace std::string_literals;
using namespace boost::placeholders;


// Husk: XML Qt
// http://doc.qt.io/qt-5/qxmlstreamreader.html

// ----------------------------------
// --- PUBLIC: Static member vars ---
// ----------------------------------
const std::string ScriptMiner::DefaultCompareFun("contains");
const std::string ScriptMiner::DefaultModifierFun("trimDefault");

ScriptMiner::ScriptMiner(
                 boost::shared_ptr<crawl::WebBrowserIF> pBrowser
               , const::std::string& sBaseOutputName
               , crawl::Url const& siteUrl
               , const crawl::DataWriterIF::DataWriterVecT& dataWriters
               , boost::shared_ptr<crawl::ScriptingClassIF> pScriptClass
               , boost::shared_ptr<crawl::Configuration> pConfig
)	: QObject(nullptr),
    Crawler					( pBrowser, siteUrl, dataWriters, pScriptClass, pConfig ),
    m_pStateMachineMgr		( new StateMachineMgr(this)),
    m_lookForWordDomFinder  (new crawl::LookForWordDomFinder(this)),
    m_outputName            (sBaseOutputName),
    m_iMiningDoneStatus		(0),
    m_sHandlerContextName   (""),
    m_sBeginMiningHandlerContextName(""),
    m_bUploadData           (false),
    m_urlStart				( siteUrl ),
    m_sCurrentLoadingUrl	(""),
    m_bPageLoadInProgress	(false),
    m_bNewPageLoadInitiated	(false),
    m_sLatestFullyLoadedUrl (""),
    m_iPreviousActivityCount(-1),
    m_iTimeSinceLastNetActivityInSeconds(0),
    m_iConfigTimeReloadIfNoActivityInSeconds( pConfig->valueIntGet("no-net-activity-timeout") ),
    m_iReloadIfNoActivityLevel(0),
    m_iMiningRunTimeInSeconds(0),
    m_iPageLoadsTotal       (0),
    m_configAjaxPageLoadDeltaTime ( boost::posix_time::milliseconds(500) ),
    m_sConfigUrlUploadData	("http://veriquin.com/webservice/upload.php"),
    m_sDecimalPoint 		("."),
    m_sThousandsSep 		(",")

{
    m_showNetworkActivity = config()->valueBoolGet("show-network-activity");

    runModeSet( config()->runMode() );
    createProgressOut(sBaseOutputName);
    connectSignals();

    m_timeLastPageLoadStarted   = boost::posix_time::second_clock::universal_time();
    m_timeLastPageLoadFinished  = boost::posix_time::second_clock::universal_time();

    //if ( scriptingClass() ) addScriptFunctions(); // FIXME, TODO. Seems ok to not have this cacall here!
    webBrowser()->sizeSet(config()->valueIntGet("win-width"), config()->valueIntGet("win-height"));

    webBrowser()->continuousTimerStart(1000);
    webBrowser()->continuousTimer2Start(250);


}

ScriptMiner::~ScriptMiner()
{
    disconnectSignals();
}

void ScriptMiner::assignWebBrowser    ( boost::shared_ptr<crawl::WebBrowserIF> pMozBrowser )
{
    Crawler::assignWebBrowser( pMozBrowser );
    webBrowser()->continuousTimerStart(1000);
    disconnectSignals();
    connectSignals();
}

void ScriptMiner::init ()
{
    using namespace std;
    // --- Miner worker thread setup ---
    m_minerWorkerThread = new QThread;
    m_minerWorker = new MinerWorker();
    m_minerWorker->moveToThread(m_minerWorkerThread);
    scriptingClassSet(m_minerWorker->scriptExecutor()->scriptingClass());
    auto self = shared_from_this();
    m_minerWorker->minerSet(boost::static_pointer_cast<ScriptMiner>(self));

    connect(this, SIGNAL( startUpPhpSignal() ), m_minerWorker, SLOT(startUpPhpSlot()));
    connect(this, SIGNAL( loadMinerScriptSignal(const QString&, const QString&) ), m_minerWorker, SLOT( loadMinerScriptSlot(const QString&, const QString&) ));
    connect(this, SIGNAL( runSetupFunctionsSignal() ), m_minerWorker, SLOT( runSetupFunctionsSlot() ));
    connect(this, SIGNAL( beginMiningSignal(bool) ), m_minerWorker, SLOT( beginMiningSlot(bool) ));
    connect(this, SIGNAL( endMiningSignal() ), m_minerWorker, SLOT( endMiningSlot() ));
    connect(this, SIGNAL( matchStepSignal() ), m_minerWorker, SLOT( matchStepSlot() ));
    connect(this, SIGNAL( mineStepSignal() ), m_minerWorker, SLOT( mineStepSlot() ));
    connect(this, SIGNAL( navigateStepSignal() ), m_minerWorker, SLOT( navigateStepSlot() ));
    connect(this, SIGNAL( doOnPageLoadedSignal() ), m_minerWorker, SLOT( doOnPageLoadedSlot() ));

    connect(this, SIGNAL( runPhpSnippetSignal(const QString&) ), m_minerWorker, SLOT( runPhpSnippetSlot(const QString&) ));

    //
    connect(m_minerWorker, SIGNAL( workDoneSignal(crawl::MinerWorkerIF::TaskDone) ), this, SLOT( workDoneSlot(crawl::MinerWorkerIF::TaskDone) ) );
    connect(this, SIGNAL( emptyCrawlerCommandQueueSignal() ), this, SLOT( emptyCrawlerCommandQueueSlot() ) );

    m_minerWorkerThread->start();
    startUpPhpWorker();
}

void ScriptMiner::clearForReloadScript()
{
    Crawler::clearForReloadScript();
    m_outputName = "";
    m_bUploadData = false;
    m_urlStart    = Url("");
}


void ScriptMiner::connectSignals   ()
{
    m_connectionPageLoaded      = webBrowser()->signalsManager()->connectPageLoaded			( boost::bind(&ScriptMiner::slotPageLoaded,			this, _1            ) );
    m_connectionLoadUri			= webBrowser()->signalsManager()->connectOnLoadUri			( boost::bind(&ScriptMiner::slotLoadUri, 			this, _1, _2        ) );
    m_connectionOnClose			= webBrowser()->signalsManager()->connectOnClose			( boost::bind(&ScriptMiner::onClose, 				this                ) );
    m_connectionContinuousTimer	= webBrowser()->signalsManager()->connectContinuousTimer	( boost::bind(&ScriptMiner::slotContinuousTimer,	this                ) );
    m_connectionContinuousTimer2= webBrowser()->signalsManager()->connectContinuousTimer2	( boost::bind(&ScriptMiner::slotContinuousTimer2,	this                ) );
}

void ScriptMiner::disconnectSignals   ()
{
    m_connectionNetProgress.disconnect();
    m_connectionPageLoaded.disconnect();
    m_connectionLoadUri.disconnect();
    m_connectionOnClose.disconnect();
    m_connectionContinuousTimer.disconnect();
    m_connectionContinuousTimer2.disconnect();
}



void ScriptMiner::assignScriptingClass ( boost::shared_ptr<crawl::ScriptingClassIF> pScriptClass )
{
    scriptingClassSet(pScriptClass);
    addScriptFunctions();
}


bool ScriptMiner::scriptFunctionExists ( const std::string&  sFunName ) const
{
    return scriptingClass()->scriptFunctionExists( sFunName );
}

void ScriptMiner::startUpPhpWorker()
{
    emit startUpPhpSignal();
}

void ScriptMiner::loadMinerScriptWorker(const QString& phpMinerScript, const QString& scriptAbsPath)
{
    emit loadMinerScriptSignal(phpMinerScript, scriptAbsPath);
}

void ScriptMiner::runSetupFunctionsWorker()
{
    emit runSetupFunctionsSignal();
}

void ScriptMiner::beginMiningWorker(bool restart)
{
    emit beginMiningSignal(restart);
}

void ScriptMiner::endMiningWorker()
{
    emit endMiningSignal();
}

void ScriptMiner::matchStepWorker()
{
    emit matchStepSignal();
}

void ScriptMiner::mineStepWorker()
{
    emit mineStepSignal();
}

void ScriptMiner::navigateStepWorker()
{
    emit navigateStepSignal();
}

void ScriptMiner::doOnPageLoadedWorker()
{
    emit doOnPageLoadedSignal();
}

void ScriptMiner::runPhpSnippetWorker(const QString& phpCode)
{
    emit runPhpSnippetSignal(phpCode);
}

void ScriptMiner::emptyCrawlerCommandQueueSlot()
{
    using namespace std;
    if (m_crawlerCommandQueue.empty()) {
        waitingForDomReadySet(false); // Signal any script in waiting for dom ready that it can continue.
        return;
    }
    while (!m_crawlerCommandQueue.empty()) {
        auto&& fn = std::move(m_crawlerCommandQueue.front());
        fn();
        m_crawlerCommandQueue.front() = CrawlerCommandQueue::Cmd();
        m_crawlerCommandQueue.pop();
    }
}

void ScriptMiner::workDoneSlot(crawl::MinerWorkerIF::TaskDone done)
{
    using namespace std;

    switch (done) {
    case MinerWorkerIF::TaskDone::runPhpSnippet:
    case MinerWorkerIF::TaskDone::navigateStep:
        emptyCrawlerCommandQueueSlot();
        break;
    default:
        break;
    }
}

// -------------------------------------
// --- Start mining helper functions ---
// -------------------------------------
void ScriptMiner::setUrlStartAndUrlSite()
{
    // Get urlSite from setting
    std::string urlSite = settingGet("urlSite");

    // Get urlSite from function (backwards compatible)
    const std::string funName1 =  "Crawler__urlSite";
    if ( scriptFunctionExists(funName1) ) {
        urlSite = scriptingClass()->callScriptFunction_String (funName1);
    }
    siteUrlSet(urlSite);


    std::string urlStart = settingGet("urlStart");
    const std::string funName2 = "Crawler__urlStart" ;
    if ( scriptFunctionExists(funName2) )  {
        urlStart = scriptingClass()->callScriptFunction_String (funName2);
    }

    if ( urlStart == "" ) {
        urlStart = siteUrl();
    }
    // Override if urlStart found in config/command line
    const auto urlStartFromConfig = config()->urlStartGet();
    if ( urlStartFromConfig != "" ) {
        urlStart = urlStartFromConfig;
    }

    m_urlStart = Url(urlStart);
}


void ScriptMiner::readConfig( )
{
    std::string sFunName;
    // --------------------------------------
    // --- Runmode specific configuration ---
    // --------------------------------------
    // I.e. configuration determined by the runmode:
    // dbg_runminer, rel_runminer, runminer, robot_runminer, web_runminer
    // This configuration comes from the webminer.php, which all scripts
    // must include. Depending on runmode a different webminer.php will be
    // controlled from the actual used php.ini file used.

    const auto delayPageLoadedSignalTimeInMs = cpaf::to_int(settingGet("delay_page_loaded_signal_time_in_ms", "50"));
    webBrowser()->delayPageLoadedSignalTimeInMsSet(delayPageLoadedSignalTimeInMs);

    // Set image loading default mode
    std::string sLoadImages	= config()->valueStrGet("load-images");
    if ( sLoadImages == "" ) {
        sLoadImages = settingGet("load_images");
    }
    if ( sLoadImages == "" ) {
        sLoadImages = crawl::rmCrawlerE == runMode() ? "no" : "yes";
    }


    loadImages	( crawl::stringToBool(sLoadImages) );

    // Set upload data default mode
    //upload-result
    std::string sUploadResult	= config()->valueStrGet("upload-result");
    if ( sUploadResult == "" ) {
        sUploadResult = crawl::rmCrawlerE == runMode() ? "yes" : "no";
    }

    m_bUploadData = crawl::stringToBool(sUploadResult);

//	std::cout << boost::format("Runmode: %s") % config()->valueStrGet("run-mode") << std::endl;
//	std::cout << boost::format("Default image: %1%") % m_bDefaultLoadImages << std::endl;

    // ---------------------------------------
    // --- TEMPLATE specific configuration ---
    // ---------------------------------------
    // I.e. configuration set by the (TEMPLATE) script .
    sFunName = "TEMPLATE__setRunConfig";
    if ( scriptFunctionExists ( sFunName ) )	scriptingClass()->callScriptFunction_Void(sFunName) ;

    // -------------------------------------
    // --- Script specific configuration ---
    // -------------------------------------
    // I.e. configuration set by the script by the creator.
    sFunName = "Crawler__setRunConfig";
    if ( scriptFunctionExists ( sFunName ) )	scriptingClass()->callScriptFunction_Void(sFunName) ;
}

void ScriptMiner::setOutputName()
{
    m_outputName = "";
    std::string sFunName;

    // Get from setting
    const auto outputNameFromSetting = settingGet("outputName");
    if ( outputNameFromSetting != "" ) {
        m_outputName = outputNameFromSetting;
    }

    if (m_outputName == "") {
        m_outputName = settingGet("site_id") != "" ? settingGet("site_id") : settingGet("shop_id");
    }

    // Get from PHP function (backwards compatible)
    sFunName = "Crawler__outputName" ;
    if ( scriptingClass()->scriptFunctionExists(sFunName) ) {
        m_outputName = scriptingClass()->callScriptFunction_String ( sFunName ) ;
    }

    // Get from command line.
    const auto outputNameFromCommandLine = config()->valueStrGet("output-name");
    if ( outputNameFromCommandLine != "" )  {
        m_outputName = outputNameFromCommandLine;
    }

    if (m_outputName.empty()) {
        m_outputName = "Crawler";
    }

    std::cerr << "Writing to output name '" << m_outputName << "(.json.gz)'\n";
}


void ScriptMiner::startMiningInitVars ()
{
    // TODO: Probably most of these should be set to initial default values here!
 //   m_pStateMachineMgr		( new StateMachineMgr(this)),
    m_iMiningDoneStatus = 0;
    m_sHandlerContextName               = "";
    m_sBeginMiningHandlerContextName    = "";
 //   m_sCurrentLoadingUrl	(""),
    m_bPageLoadInProgress	= false;
    m_bNewPageLoadInitiated	= false;
    m_waitingForDomReady    = false;
    m_workerIsExecutingPhp  = false;
}

void ScriptMiner::outputBeginMiningRecord()
{
    using namespace cpaf::time;
    stringSearch().pushContext("beginMining", true);
    stringSearch().outputValueDirectUnit( "TIME_SCANNING_START_UTC",  	format_utc(m_tStartUTC, iso_pretty));
    stringSearch().outputValueDirectUnit( "TIME_SCANNING_START_LOCAL", 	format_local(m_tStartUTC, iso_pretty));
    stringSearch().popContext();
}

void ScriptMiner::resetVarsBeforeFirstPageLoad()
{
    m_timeLastPageLoadStarted               = boost::posix_time::second_clock::universal_time();
    m_timeLastPageLoadFinished              = boost::posix_time::second_clock::universal_time();
    m_iTimeSinceLastNetActivityInSeconds    = 0;
    m_iMiningRunTimeInSeconds               = 0;
    m_iReloadIfNoActivityLevel              = 0;
    m_iPageLoadsTotal                       = 0;
    m_iItemsWritten                         = 0;
    m_sLatestFullyLoadedUrl                 = m_urlStart.string();
}

void ScriptMiner::doDownloadSitemaps()
{
    m_sitemapGetter.clearLocationUrls();

    m_sitemapGetter.siteSet(siteUrl());
    m_sitemapGetter.doneCallbackSet(boost::bind(&ScriptMiner::sitemapsDownloaded, this, _1));
    m_sitemapGetter.downloadSiteMap();
}

void ScriptMiner::downloadSitemapsWait(int timeoutInMs)
{
    std::cout << "INFO: downloadSitemaps start, siteUrl(): " << siteUrl() << std::endl;
    auto&& fn =
            [this]() -> bool
    {
        this->doDownloadSitemaps();
        return true;
    };
    m_crawlerCommandQueue.push(std::move(fn));
    waitForFilesDownloaded(timeoutInMs);
    std::cerr << "INFO: downloadSitemaps completed. Found "
              << m_sitemapGetter.locationUrls().size() << " urls ...";

    if (settingBoolGet("dbg_sitemaps")) {
        std::cout << "DBG: Print all location URLS from sitemap " << std::endl;
        int i = 0;
        for (const auto& s : m_sitemapGetter.locationUrls()) {
            ++i;
            std::cout << "[" << i << "] " << s << "\n";
        }
        std::cout << std::endl;
    }

    // Either add all sitemap URLs as is or call use PHP function to filter/modify them
    const auto fname = "Crawler__filterSitemapUrl"s;
    if ( scriptFunctionExists(fname) ) {
        constexpr bool forceUnique = false;
        constexpr bool updateQueueFile = false;
        for (const auto& url: siteMapLocationUrls()) {
            const auto ret_url = scriptingClass()->callScriptFunction_String ( fname, url ) ;
            if (!ret_url.empty()) {
                urlQueue().pushBackUrl(ret_url, forceUnique, updateQueueFile);
            }
        }
        urlQueue().writeQueueToFile();
    }
    else {
        urlQueue().append(siteMapLocationUrls());
    }
    std::cerr << "\n      Added "
              << urlQueue().size()
              << " page URLs to the URL queue. " << std::endl;
}

void ScriptMiner::sitemapsDownloaded(SiteMapGetter* /*smg*/)
{
    waitingForDomReadySet(false);
}

void ScriptMiner::callSetupBeginMiningPhpFunctions()
{
    std::string sFunName = "TEMPLATE__doSetup" ;
    if ( scriptFunctionExists(sFunName) ) scriptingClass()->callScriptFunction_Void ( sFunName ) ;
    sFunName =  "Crawler__doSetup" ;
    if ( scriptFunctionExists(sFunName) ) scriptingClass()->callScriptFunction_Void ( sFunName ) ;

    // Call TEMPLATE__handler-name__beginMining PHP functions
    for( const std::string& sFunName: m_templateBeginMiningFunctions ) {
        scriptingClass()->callScriptFunction_Void ( sFunName ) ;
    }

    // Call Crawler__handler-name__beginMining PHP functions
    for( const std::string& sFunName : m_crawlerBeginMiningFunctions ) {
        scriptingClass()->callScriptFunction_Void ( sFunName ) ;
    }
}

// -----------------------------------------
// --- Start/end mining helper functions ---
// -----------------------------------------

void ScriptMiner::runSetupFunctions()
{
    // Call _doSetup PHP function
    std::string sFunName = "TEMPLATE__doSetup" ;
    if ( scriptFunctionExists(sFunName) ) scriptingClass()->callScriptFunction_Void ( sFunName ) ;
    sFunName =  "Crawler__doSetup" ;
    if ( scriptFunctionExists(sFunName) ) scriptingClass()->callScriptFunction_Void ( sFunName ) ;
}

void ScriptMiner::startMining(bool restart)
{
    m_curMiningStepE = crawl::MiningStepE::stepStartMiningE;
    using namespace boost::posix_time;
    using namespace boost::gregorian;
    m_tStartUTC 	= second_clock::universal_time();


    //m_sitemapGetter.clear();    //TODO: Should we do this ?

    // Reset URL queue
    urlQueue().reset(false);
    urlQueue().assign( config()->urlQueue() );
    m_pStateMachineMgr->reset();

    if ( !scriptingClass() ) { printf("ERROR: ScriptMiner::beginMiningAuto() no scripting class assigned\n"); }
    scriptingClass()->readScriptFunctions();

    setOutputName();
    dataBaseOutputStreamClose();
    g()->minerAdd( this->shared_from_this(), "Crawler" );  // TODO: Change minerAdd() to minerSet()

    addScriptFunctions();
    startMiningInitVars ();
    if ( restart ) Crawler::restart();
    stringSearch().beginMining(outputName());

    outputBeginMiningRecord();
    setUrlStartAndUrlSite();
    readConfig();

    const auto continue_counter = crawl::g()->configuration()->continueCounterGet();
    if ( settingBoolGet("use_sitemap") && continue_counter == 0) {
        std::cout << "INFO: Sitemap download allowed! Trying to fetch ... " << std::endl;
        downloadSitemapsWait();
    }

    // Call __doSetup PHP function
    callSetupBeginMiningPhpFunctions();

    // Make sure these timestamps are set to a recent time before starting the crawl.
    resetVarsBeforeFirstPageLoad();

    writeMiningStatusFile();


    m_nextMiningStepE = crawl::MiningStepE::stepMatchE;
    const std::string startState = config()->startStateGet();
    if ( startState != "" ) navCurrentStateSet( startState );

    const std::string endState = config()->valueStrGet("end-state");
    if ( endState != "" ) navEndStateSet( endState );

    domSearchMgr()->prepareForRun();

    m_showDomFindCalls = settingBoolGet("show_dom_find_calls", false);
    std::cerr << "ScriptMiner::startMining Url: " << m_urlStart << "\n";
    m_curMiningStepE = crawl::MiningStepE::stepLoadPageE;
    urlLoad( m_urlStart.string() );  // Load initial page.
    emit emptyCrawlerCommandQueueSignal(); // And actually start loading!!!
}

bool ScriptMiner::onClose()
{
    endMining( crawl::miningDoneUserExitE );
    return true;
}

std::string ScriptMiner::creationHandlerContextName() const
{
    if ( m_sBeginMiningHandlerContextName != "" ) return m_sBeginMiningHandlerContextName;
    return handlerContextName();
}

void ScriptMiner::signalMiningDone()
{
    webBrowser()->signalsManager()->signalOnMiningDone();
}

void ScriptMiner::endMining(  int iMiningDoneStatus )
{
    m_curMiningStepE = crawl::MiningStepE::stepEndMiningE;
    using namespace boost::posix_time;
    using namespace cpaf::time;

    std::cerr << "FIXMENM ScriptMiner::endMining, status: " << iMiningDoneStatus << "\n";
    if ( m_iMiningDoneStatus )	return ;
    m_iMiningDoneStatus = iMiningDoneStatus;
//	m_connectionPageLoaded.disconnect();
//	m_connectionLoadUri.disconnect();


    // Call _endMining PHP function
    std::string sFunName = "TEMPLATE__endMining" ;
    if ( scriptFunctionExists(sFunName) ) scriptingClass()->callScriptFunction_Void ( sFunName ) ;
    sFunName = "Crawler__endMining";
    if ( scriptFunctionExists(sFunName) ) scriptingClass()->callScriptFunction_Void ( sFunName ) ;

    ptime tEndUTC 		= second_clock::universal_time();
    stringSearch().pushContext("endMining", true);


    stringSearch().outputValueDirectUnit( "TIME_SCANNING_END_UTC",  	format_utc(tEndUTC, iso_pretty));
    stringSearch().outputValueDirectUnit( "TIME_SCANNING_END_LOCAL", 	format_local(tEndUTC, iso_pretty));
    stringSearch().outputValueDirectUnit( "TIME_SCANNING_ELAPSED_ISO", 		to_iso_string(tEndUTC-m_tStartUTC)      );
    stringSearch().outputValueDirectUnit( "TIME_SCANNING_ELAPSED_SIMPLE", 	to_simple_string(tEndUTC-m_tStartUTC)   );
    stringSearch().popContext();
    stringSearch().endMining();

    // --- Send data json file to server if requested ---
//    if ( m_bUploadData || ( crawl::rmCrawlerE == runMode() ) ) {
    if ( m_bUploadData ) {
        boost::shared_ptr<crawl::Configuration> c= crawl::g()->configuration();
        std::string sUploadFun = c->valueStrGet("upload-handler");
        if (sUploadFun == "")
            sUploadFun = settingGet("upload-handler");
        scriptingClass()->callScriptFunction_Void ( sUploadFun ) ;
    }
    writeMiningStatusFile();
    signalMiningDone();
    runModeSet( crawl::rmDesignE );
}



void ScriptMiner::match()
{
    m_curMiningStepE = crawl::MiningStepE::stepMatchE;
    m_sHandlerContextName = "";

    // First try Crawler match functions in order
    for (const std::string& function_name: m_matchFunctionsCrawler) {
        if ( scriptingClass()->callScriptFunction_Bool ( function_name ) ) {
            m_sHandlerContextName = boost::algorithm::erase_first_copy( function_name, "Crawler__" ) ;
            boost::algorithm::erase_last( m_sHandlerContextName, "__match" ) ;
            break;
        }
    }
    // Then try Template match functions in order if the crawler functions did not "want" to handle the page
    if (m_sHandlerContextName.empty()) {
        for (const std::string& function_name: m_matchFunctionsTemplate) {
            const auto crawler_fun_name = boost::algorithm::replace_first_copy(function_name, "TEMPLATE__", "Crawler__");
            if (scriptingClass()->scriptFunctionExists(crawler_fun_name)) {
                continue;   // Skip if a corresponding "Crawler__" function exists - already tried that.
            }
            if ( scriptingClass()->callScriptFunction_Bool ( function_name ) ) {
                m_sHandlerContextName = boost::algorithm::erase_first_copy( function_name, "TEMPLATE__" ) ;
                boost::algorithm::erase_last( m_sHandlerContextName, "__match" ) ;
                break;
            }
        }
    }

    webBrowser()->signalsManager()->signalOnMatch();
    m_nextMiningStepE = crawl::MiningStepE::stepMineE;
}

void ScriptMiner::mine()
{
    m_curMiningStepE = crawl::MiningStepE::stepMineE;
    const std::string& sHandlerContextName = handlerContextName();
    m_lookForWordDomFinder->lfwInitPageLoaded(lookForWordMgr(sHandlerContextName));
    // Call regular '_mine' function, if present
    std::string sFunName ( std::string("Crawler__") + sHandlerContextName + "__mine" );
    if ( scriptFunctionExists(sFunName) ) {
        scriptingClass()->callScriptFunction_Void ( sFunName );
    }
    else {
        // Call TEMPLATE '_mine' function, if present
        sFunName = std::string("TEMPLATE__") + sHandlerContextName + "__mine";
        if ( scriptFunctionExists(sFunName) ) {
            scriptingClass()->callScriptFunction_Void ( sFunName );
        }
    }
    m_nextMiningStepE = crawl::MiningStepE::stepNavigateE;
    updateScriptStatusString(); // Possibly update the script's status string for writing to the Crawler.status file!
}

/**
Call the script navigate function.
\return true if scriptfunction returns true or a new page load is
        auto detected (i.e. the navigation results in a pageload. */
bool
ScriptMiner::navigate()
{
    m_curMiningStepE = crawl::MiningStepE::stepNavigateE;
    m_nextMiningStepE = crawl::MiningStepE::stepMatchE;
    const std::string& sHandlerContextName = handlerContextName();

    if ( sHandlerContextName == "" ) {
        printf("ML: Warning: ScriptMiner::navigate no page name\n"); return false;
    }
    bool newPageLoadInitiated = false;

    // Call regular '_navigate' function, if present
    std::string sFunName ( std::string("Crawler__") + sHandlerContextName + "__navigate" );
    if ( scriptFunctionExists(sFunName) ) {
        newPageLoadInitiated = scriptingClass()->callScriptFunction_Bool ( sFunName ) ;
        // NOTE: Script MUST decide alone, no auto-detect
    }
    // ELSE Call TEMPLATE '_navigate' function, if present
    else {
        sFunName = std::string("TEMPLATE__") + sHandlerContextName + "__navigate";
        if ( scriptFunctionExists(sFunName) ) {
            newPageLoadInitiated = scriptingClass()->callScriptFunction_Bool ( sFunName ) ;
            // NOTE: Script MUST decide alone, no auto-detect "page loading"
        }
    }

    m_handlerContinuePositions[m_sHandlerContextName] = domPos(); // Save dom position to use in domGetContinuePos(), domContinueSearch().
    return newPageLoadInitiated;
}


/**
Load next page/url. In case navigate() returns false we try the front of the
UrlQueue.
\return true if a new page will be loaded, and false if scanning is done. */
bool
ScriptMiner::nextPage()
{
    using namespace std;
    bool newPageLoadInitiated = false;
    if ( navigate() ) {
        newPageLoadInitiated = true;
    }
    else {

        // --- UrlQueue ---
        // Pop URLs from front until we get one that's OK to load. See also Crawler::configAddIncludeUrl() and friends.
        while ( !urlQueue().empty() && !okToLoadUrl(urlQueue().front().string()) )	{
            urlQueue().popFront();
        }

        // Found an URL it's ok to load, so load it
        if ( !urlQueue().empty() ) {

            const auto& url = urlQueue().front().string();
            if (settingBoolGet("dbg_url_queue")) {
                std::cerr << "DBG: Load from URL queue '" << url << "'" << std::endl;
            }
            urlLoad( url );
            urlQueue().popFront();	// Pop just loaded URL too
            newPageLoadInitiated = true;
        }
        else {
            std::cerr << "DBG: ScriptMiner::nextPage() URL queue empty\n";
            newPageLoadInitiated = false; // Queue empty !
        }
    }
    m_bNewPageLoadInitiated = newPageLoadInitiated;
    return m_bNewPageLoadInitiated;
}


std::string	ScriptMiner::minerName () const
{
    return "Crawler";
}

std::string ScriptMiner::outputName() const
{
    return m_outputName;
}


std::string ScriptMiner::dataFileName	() const
{
    return m_outputName + ".json";
}

// ---------------------------------
// --- PRIVATE: Helper functions ---
// ---------------------------------
void ScriptMiner::addScriptFunctions ( )
{
    m_allFunctions.clear();
    m_matchFunctionsCrawler.clear();
    m_matchFunctionsCrawler.clear();
    m_templateBeginMiningFunctions.clear();
    m_crawlerBeginMiningFunctions.clear();
    boost::shared_ptr<crawl::ScriptingClassIF> pScriptClass  =  scriptingClass();
    pScriptClass->readScriptFunctions();
    ScriptingClassIF::FunctionsVecT::const_iterator it      = pScriptClass->allFunctionsVec().begin();
    ScriptingClassIF::FunctionsVecT::const_iterator itEND   = pScriptClass->allFunctionsVec().end();
    for ( ; it != itEND; ++it ) {
        addFunction(*it);
    }
}


void ScriptMiner::addFunction (
    std::string const& sFunctionName
)
{
    if ( boost::algorithm::starts_with( sFunctionName, "Crawler__") ) {
        m_allFunctions.insert( sFunctionName );
        if ( boost::algorithm::ends_with( sFunctionName, "__match" ) ) {
            m_matchFunctionsCrawler.push_back( sFunctionName );
        }
        else if ( boost::algorithm::ends_with( sFunctionName, "__beginMining" ) ) {
            m_crawlerBeginMiningFunctions.push_back( sFunctionName );
        }
    }
    else if ( boost::algorithm::starts_with( sFunctionName, "TEMPLATE__") ) {
        m_allFunctions.insert( sFunctionName );
        if ( boost::algorithm::ends_with( sFunctionName, "__match" ) ) {
            m_matchFunctionsTemplate.push_back( sFunctionName );
        }
        else if ( boost::algorithm::ends_with( sFunctionName, "__beginMining" ) ) {
            m_templateBeginMiningFunctions.push_back( sFunctionName );
        }
    }
}

std::string ScriptMiner::pageSource() const
{
    return std::string(webBrowser()->html());
}


// ----------------------
// --- Misc functions ---
// ----------------------


std::string	ScriptMiner::currentMiner() const
{
    return minerName();
}

std::string	ScriptMiner::currentDataFile() const
{
    return dataFileName();
}

void ScriptMiner::triggerPageLoaded()
{
    auto&& fn = [=,this]() -> bool { webBrowser()->triggerPageLoaded(); return true;};
    m_crawlerCommandQueue.push(std::move(fn));
}

void ScriptMiner::triggerPageLoadedWait (int timeoutInMs)
{
    triggerPageLoaded();
    waitForDomReady(timeoutInMs);
}


void ScriptMiner::waitSleep(int timeInMs)
{
    emit emptyCrawlerCommandQueueSignal();
    QThread::msleep(static_cast<unsigned long>(timeInMs));
}

bool ScriptMiner::waitForDomReady(int timeoutInMs)
{
    using namespace std;
    if (!webBrowser()->supportsDynamicDom()) {
        cout << "WARNING: Called wait function on browser that does not support it" << endl;
        return false;
    }


    if (!m_crawlerCommandQueue.empty()) {
        waitingForDomReadySet(true);
    }
    emit emptyCrawlerCommandQueueSignal();

    cerr << "FIXMENM: waitForDomReady( " << timeoutInMs << " ), "
         << " m_crawlerCommandQueue.empty(): " << m_crawlerCommandQueue.empty()
         << ", m_waitingForDomReady: " << m_waitingForDomReady
         << "\n";

    const int sleepStepInMs = 10;
    while (m_waitingForDomReady && (timeoutInMs > 0)) {
//        cerr << "FIXMENM: sleep while waiting for dom ready: "  << timeoutInMs << "ms left\n";
        QThread::msleep(sleepStepInMs);
        timeoutInMs -= sleepStepInMs;
    }
    m_curMiningStepE = crawl::MiningStepE::stepNoneE;

    if (m_waitingForDomReady) {
       cout << "Warning: waitForDomReady( " << timeoutInMs << " ), miliseconds timeout reached!" << endl;
       return false;
    }
    cerr << "FIXMENM: waitForDomReady DONE ( " << timeoutInMs << " ), "
         << " m_crawlerCommandQueue.empty(): " << m_crawlerCommandQueue.empty()
         << ", m_waitingForDomReady: " << m_waitingForDomReady
         << "\n";
    return true; // All ok! no timeout!
}

void ScriptMiner::waitForFilesDownloaded(int timeoutInMs)
{
    using namespace std;

    if (!m_crawlerCommandQueue.empty()) {
        waitingForDomReadySet(true);
    }
    emit emptyCrawlerCommandQueueSignal();

    const int sleepStepInMs = 10;
    while (m_waitingForDomReady && (timeoutInMs > 0)) {
        QThread::msleep(sleepStepInMs);
        timeoutInMs -= sleepStepInMs;
    }
    if (m_waitingForDomReady) {
       cout << "Warning: waitForFilesDownloaded( " << timeoutInMs << " ), seconds timeout reached!" << endl;
    }
}

void ScriptMiner::waitForJavascriptDone()
{

}

void ScriptMiner::clearCookies()
{
    webBrowser()->clearCookies();
}

int ScriptMiner::networkActivityCounter() const
{
    return static_cast<int>(m_iCountActivityAny);
}

void ScriptMiner::browserScroll(int x, int y)
{
    auto&& fn = [=,this]() -> bool { webBrowser()->scroll(x,y); return true;};
    m_crawlerCommandQueue.push(std::move(fn));
}

int ScriptMiner::browserScrollPosXGet() const
{
    return webBrowser()->scrollPosXGet();
}

int ScriptMiner::browserScrollPosYGet() const
{
    return webBrowser()->scrollPosYGet();
}


/*
-------------------------
--- Browser functions ---
------------------------- */

void ScriptMiner::browserHide ()
{
    auto&& fn = [this]() -> bool { webBrowser()->hide(); return true;};
    m_crawlerCommandQueue.push(std::move(fn));
}

void ScriptMiner::browserShow ()
{
    auto&& fn = [this]() -> bool { webBrowser()->show(); return true;};
    m_crawlerCommandQueue.push(std::move(fn));
}

void ScriptMiner::browserSetSize	(int x, int y)
{
    auto&& fn = [=,this]() -> bool { webBrowser()->sizeSet(x,y); return true;};
    m_crawlerCommandQueue.push(std::move(fn));
}

int ScriptMiner::browserGetSizeX () const
{
    int x, y;
    webBrowser()->sizeGet( x, y );
    return x;
}

int ScriptMiner::browserGetSizeY () const
{
    int x, y;
    webBrowser()->sizeGet( x, y );
    return y;
}

/**
Trigger "go back" in browser.

@todo We might not want a return value here at all. Anyway currently it's always true.
*/
bool ScriptMiner::browserGoBack ()
{
    auto&& fn = [this]() -> bool {
        webBrowser()->goBack(); return true;
    };
    m_crawlerCommandQueue.push(std::move(fn));
    return true; // TODO:
}

void ScriptMiner::browserKeyEvent(int eventType, int key, int modifiers)
{
    auto&& fn = [=,this]() -> bool { webBrowser()->userKeyEvent(eventType, key, modifiers); return true;};
    m_crawlerCommandQueue.push(std::move(fn));
}

void ScriptMiner::browserMouseEvent(int eventType, float xpos, float ypos, int button, int buttons, int modifiers)
{
    auto&& fn = [=,this]() -> bool { webBrowser()->userMouseEvent(eventType, xpos, ypos, button, buttons, modifiers); return true;};
    m_crawlerCommandQueue.push(std::move(fn));
}

void ScriptMiner::browserFocusActivate()
{
    auto&& fn = [this]() -> bool { webBrowser()->focusActivate(); return true;};
    m_crawlerCommandQueue.push(std::move(fn));
}

void ScriptMiner::browserFocusDeactivate()
{
    auto&& fn = [this]() -> bool { webBrowser()->focusDeactivate(); return true;};
    m_crawlerCommandQueue.push(std::move(fn));
}

/*------------------------------------------
--- String operators/compare functions ---
------------------------------------------*/
bool ScriptMiner::valuesCompare	(
      const std::string& sInput
    , const std::string& sTest
    , const std::string& sCompareFun
    )
{
    using namespace crawl;
    StringCompareFunT strCmp = G_StringCompareLookUp::fromAlias(sCompareFun) ;
    return strCmp( sInput, sTest ) ;
}

/*
-------------------------
--- Sitemap functions ---
-------------------------*/

std::vector<std::string> ScriptMiner::siteMapUrls() const
{
    return m_sitemapGetter.siteMapUrls();
}

void ScriptMiner::siteMapUrlsSet(const std::vector<std::string>& siteMapUrls)
{
    m_sitemapGetter.siteMapUrlsSet(siteMapUrls);
}

void ScriptMiner::siteMapUrlAppend(const std::string& siteMapUrl)
{
    m_sitemapGetter.siteMapUrlAppend(siteMapUrl);
}

std::vector<std::string> ScriptMiner::siteMapLocationUrls() const
{
    return m_sitemapGetter.locationUrls();
}

void ScriptMiner::siteMapLocationsInclude(const std::string& urlPattern, const std::string& compareFun)
{
    m_sitemapGetter.addIncludeUrl(urlPattern, compareFun);
}

void ScriptMiner::siteMapLocationsExclude(const std::string& urlPattern, const std::string& compareFun)
{
    m_sitemapGetter.addExcludeUrl(urlPattern, compareFun);
}

/*
----------------------------------
--- Navigation (nav) functions ---
---------------------------------- */
void ScriptMiner::navActiveNavigatorSet ( const std::string& sNavigatorName  )
{
    stateMachineMgr()->smSetCurrent( sNavigatorName );
}


std::string ScriptMiner::navActiveNavigatorGet ()
{
    return stateMachineMgr()->smCurrentName();
}


void ScriptMiner::navJavascriptExecuteCreate ( const std::string& sNavActionName )
{
    stateMachineMgr()->smCurrent()->javascriptExecuteCreate ( sNavActionName );
}


void ScriptMiner::navUrlLoadCreate ( const std::string& sNavActionName, const std::string& sBaseUrl )
{
    stateMachineMgr()->smCurrent()->urlLoadCreate( sNavActionName, sBaseUrl );
}


void ScriptMiner::navInputOptionsCreate (
      const std::string& sNavActionName
        )
{
    stateMachineMgr()->smCurrent()->inputOptionsCreate(sNavActionName );
}


void ScriptMiner::navDropDownSelectCreate ( const std::string& sNavActionName )
{
    stateMachineMgr()->smCurrent()->dropDownSelectCreate(sNavActionName );
}


void ScriptMiner::navDomPosClickCreate ( const std::string& sNavActionName, const std::string& sFindNextDomPosSequence )
{
    stateMachineMgr()->smCurrent()->domPosClickCreate ( sNavActionName, sFindNextDomPosSequence );
}

void ScriptMiner::navDomClickNextCreate(const std::string& sNavActionName, const std::string& sFindNextDomPosSequence)
{
    stateMachineMgr()->smCurrent()->domClickNextCreate ( sNavActionName, sFindNextDomPosSequence );
    std::cout << "ERROR Not implemented: 'navDomClickNextCreate' " << std::endl;
    exit(1);
}


void ScriptMiner::navAutoInputCreate ( const std::string& sNavActionName, const std::string& sCharsList, int iMinLength, int iMaxLength )
{
    stateMachineMgr()->smCurrent()->autoInputCreate ( sNavActionName, sCharsList, iMinLength, iMaxLength );
}



void ScriptMiner::navAttributeNamesCreate (
    const std::string& sAttrNames
  , const std::string& sDelimiter
  )
{
    stateMachineMgr()->smCurrent()->attributeNamesCreate ( sAttrNames, sDelimiter );
}


// --- PUBLIC: Runtime settings functions ---
void ScriptMiner::navCurrentStateIndicesSet ( const std::string& sState )
{
    stateMachineMgr()->smCurrent()->currentStateIndicesStringSet( sState );
}

std::string ScriptMiner::navCurrentStateIndicesGet () const
{
    return stateMachineMgr()->smCurrent()->currentStateIndicesStringGet();
}


void ScriptMiner::navCurrentStateSet (
      const std::string& sState
    , const std::string& sDelimiter
    )
{
    stateMachineMgr()->smCurrent()->currentStateSet( sState, sDelimiter );
}


void ScriptMiner::navCurrentStateSet (
    const std::string& sState
    )
{
    stateMachineMgr()->smCurrent()->currentStateSet( sState );
}


void ScriptMiner::navEndStateSet (
      const std::string& sState
    , const std::string& sDelimiter
    )
{
    stateMachineMgr()->smCurrent()->endStateSet( sState, sDelimiter );
}


void ScriptMiner::navEndStateSet(
    const std::string& sState
    )
{
    stateMachineMgr()->smCurrent()->endStateSet( sState );
}



// --- PUBLIC: Add Options functions ---

void ScriptMiner::navOptionResourceAdd    (
      const std::string& sResourcePath
    , const std::string& sScriptFilterFunction
    ,  bool bForceDownload
    )

{
    stateMachineMgr()->smCurrent()->optionResourceAdd( sResourcePath, sScriptFilterFunction, bForceDownload );
}

void ScriptMiner::navOptionAdd(
      int iCount
    , const std::string& sValue
    , const std::string& sSearchFor
    )
{
    stateMachineMgr()->smCurrent()->optionAdd( iCount, sValue, sSearchFor );
}


void ScriptMiner::navOptionAdd (
      int iCount
    , const std::string& sValue
    )
{
    stateMachineMgr()->smCurrent()->optionAdd( iCount, sValue );
}


void ScriptMiner::navOptionAdd (
      const std::string& sValue
    , const std::string& sSearchFor
    )
{
    stateMachineMgr()->smCurrent()->optionAdd( sValue, sSearchFor );
}


void ScriptMiner::navOptionAdd (
    const std::string& sValue
    )
{
    stateMachineMgr()->smCurrent()->optionAdd( sValue );
}


void ScriptMiner::navOptionAdd (
    int iCount
    )
{
    stateMachineMgr()->smCurrent()->optionAdd( iCount );
}

void ScriptMiner::navOptionAdd(
      int iCount
    , const std::string& sValue
    , const std::string& sSearchFor
    , int attrStart
    , const std::string& sAttributes
    , const std::string& sDelimiter
    )
{
    stateMachineMgr()->smCurrent()->optionAdd( iCount, sValue, sSearchFor, attrStart, sAttributes, sDelimiter );
}


void ScriptMiner::navOptionAdd (
      int iCount
    , const std::string& sValue
    , int attrStart
    , const std::string& sAttributes
    , const std::string& sDelimiter
    )
{
    stateMachineMgr()->smCurrent()->optionAdd( iCount, sValue, attrStart, sAttributes, sDelimiter  );
}


void ScriptMiner::navOptionAdd (
      const std::string& sValue
    , const std::string& sSearchFor
    , int attrStart
    , const std::string& sAttributes
    , const std::string& sDelimiter
    )
{
    stateMachineMgr()->smCurrent()->optionAdd( sValue, sSearchFor, attrStart, sAttributes, sDelimiter  );
}


void ScriptMiner::navOptionAdd (
      const std::string& sValue
    , int attrStart
    , const std::string& sAttributes
    , const std::string& sDelimiter
    )
{
    stateMachineMgr()->smCurrent()->optionAdd( sValue, attrStart, sAttributes, sDelimiter  );
}


void ScriptMiner::navOptionAdd (
      int iCount
    , int attrStart
    , const std::string& sAttributes
    , const std::string& sDelimiter
    )
{
    stateMachineMgr()->smCurrent()->optionAdd( iCount, attrStart, sAttributes, sDelimiter  );
}

std::string ScriptMiner::navDomTextValueGet( const std::string& sNavActionName ) const
{
    return stateMachineMgr()->smCurrent()->domTextValueGet( sNavActionName );
}

std::string ScriptMiner::navDomValueGet( const std::string& sNavActionName ) const
{
    return stateMachineMgr()->smCurrent()->domValueGet( sNavActionName );
}


std::string ScriptMiner::navValueGet( const std::string& sNavActionName )
{
    return stateMachineMgr()->smCurrent()->valueGet( sNavActionName );
}


std::string ScriptMiner::navSearchForGet( const std::string& sNavActionName )
{
    return stateMachineMgr()->smCurrent()->searchForGet( sNavActionName );
}

int ScriptMiner::navCountGet( const std::string& sNavActionName )
{
    return stateMachineMgr()->smCurrent()->countGet( sNavActionName );
}

int ScriptMiner::navOptionIndexGet( const std::string& sNavActionName )
{
    return static_cast<int>(stateMachineMgr()->smCurrent()->optionIndexGet(sNavActionName ));
}

int ScriptMiner::navStateIndexGet()
{
    return static_cast<int>(stateMachineMgr()->smCurrent()->stateIndexGet());
}

int ScriptMiner::navNumStatesGet () const
{
    return static_cast<int>( stateMachineMgr()->smCurrent()->numStatesGet() );
}

int ScriptMiner::navLastStateIndexGet () const
{
    return static_cast<int>( stateMachineMgr()->smCurrent()->lastStateIndexGet() );
}


std::string ScriptMiner::navAttributeGet ( const std::string& sNavActionName, const std::string& sAttrName )
{
    return stateMachineMgr()->smCurrent()->attributeGet ( sNavActionName, sAttrName );
}

std::string ScriptMiner::navAttributeGet ( const std::string& sAttrName ) const
{
    return stateMachineMgr()->smCurrent()->attributeGet ( sAttrName );
}

bool ScriptMiner::navDoAction (
    const std::string& sNavActionName
    )
{
    using namespace boost;
    shared_ptr<NavigateStateBase> pNSB = stateMachineMgr()->smCurrent()->actionPtrGet ( sNavActionName );
    if ( !pNSB ) return false;
//    boost::shared_ptr<DomNodeIF> pNode = helperGetNearestElement( crawl::NEAREST_AUTO );
    NavigatorActionsExecutor navExe;
    return navExe.doAction( this, pNSB/*, pNode*/ );
}

bool ScriptMiner::navDoActionClickAll (
    const std::string& sNavActionName
    )
{
    using namespace boost;
    shared_ptr<NavigateStateBase> pNSB = stateMachineMgr()->smCurrent()->actionPtrGet ( sNavActionName );
    if ( !pNSB ) return false;
//    boost::shared_ptr<DomNodeIF> pNode = helperGetNearestElement( crawl::NEAREST_AUTO );
    NavigatorActionsClickAllExecutor navClickAllExe;
    return navClickAllExe.doAction( this, pNSB/*, pNode*/ );
}

bool ScriptMiner::navNextState()
{
    return stateMachineMgr()->smCurrent()->nextState();
}

std::string ScriptMiner::navStateString () const
{
    return stateMachineMgr()->smCurrent()->stateString();
}

void ScriptMiner::navStart ()
{
    stateMachineMgr()->smCurrent()->start();
}

void ScriptMiner::navReset ()
{
    stateMachineMgr()->smCurrent()->reset();
}

bool ScriptMiner::navNavigationDone () const
{
    return stateMachineMgr()->smCurrent()->navigationDone();
}

void ScriptMiner::navAutoInputIncreaseLength (
    bool bDoIncreaseLength
    )
{
    stateMachineMgr()->smCurrent()->autoInputIncreaseLength( bDoIncreaseLength );
}


/*
----------------------------------------------
--- String modifier/manipulation functions ---
---------------------------------------------- */
std::string ScriptMiner::trimDefault_fn 		( const std::string& sInput 	) const
{
    return crawl::trimDefault_fnc(config(), sInput);
}

std::string ScriptMiner::raw_fn				( const std::string& sInput		) const
{
    return crawl::raw_fnc(config(), sInput);
}

std::string ScriptMiner::toUpper_fn			( const std::string& sInput		) const
{
    return crawl::toUpper_fnc(config(), sInput);
}

std::string ScriptMiner::toLower_fn			( const std::string& sInput		) const
{
    return crawl::toLower_fnc(config(), sInput);
}

std::string ScriptMiner::trimEnds_fn			( const std::string& sInput		) const
{
    return crawl::trimEnds_fnc(config(), sInput);
}

std::string ScriptMiner::trimLeft_fn			( const std::string& sInput		) const
{
    return crawl::trimLeft_fnc(config(), sInput);
}

std::string ScriptMiner::trimRight_fn		( const std::string& sInput		) const
{
    return crawl::trimRight_fnc(config(), sInput);
}

std::string ScriptMiner::trimYear_fn			( const std::string& sInput 	) const
{
    return crawl::trimYear_fnc(config(), sInput);
}


std::string ScriptMiner::trimInteger_fn		( const std::string& sInput		) const
{
    return crawl::trimInteger_fnc(config(), sInput);
}

std::string ScriptMiner::trimNumber_fn		( const std::string& sInput		) const
{
    return crawl::trimNumber_fnc(config(), sInput);
}

std::string ScriptMiner::trimCharsEnds_fn	( const std::string& sInput, const std::string& sCharsToTrim ) const
{
    return crawl::trimCharsEnds_fnc(config(), sInput, sCharsToTrim);
}

std::string ScriptMiner::trimCharsLeft_fn	( const std::string& sInput, const std::string& sCharsToTrim ) const
{
    return crawl::trimCharsLeft_fnc(config(), sInput, sCharsToTrim);
}

std::string ScriptMiner::trimCharsRight_fn	( const std::string& sInput, const std::string& sCharsToTrim ) const
{
    return crawl::trimCharsRight_fnc(config(), sInput, sCharsToTrim);
}

std::string ScriptMiner::trimRegex_fn		( const std::string& sInput, const std::string& sRegex ) const
{
    return crawl::trimRegex_fnc(config(), sInput, sRegex);
}

std::string ScriptMiner::itrimRegex_fn		( const std::string& sInput, const std::string& sRegex ) const
{
    return crawl::itrimRegex_fnc(config(), sInput, sRegex);
}

std::string ScriptMiner::append_fn			( const std::string& sInput, const std::string& sString	) const
{
    return crawl::append_fnc(config(), sInput, sString);
}

std::string ScriptMiner::prepend_fn			( const std::string& sInput, const std::string& sString	) const
{
    return crawl::prepend_fnc(config(), sInput, sString);
}

std::string ScriptMiner::eraseFirst_fn		( const std::string& sInput, const std::string& sSearchFor	) const
{
    return crawl::eraseFirst_fnc(config(), sInput, sSearchFor);
}

std::string ScriptMiner::ieraseFirst_fn		( const std::string& sInput, const std::string& sSearchFor	) const
{
    return crawl::ieraseFirst_fnc(config(), sInput, sSearchFor);
}

std::string ScriptMiner::eraseLast_fn		( const std::string& sInput, const std::string& sSearchFor	) const
{
    return crawl::eraseLast_fnc(config(), sInput, sSearchFor);
}

std::string ScriptMiner::ieraseLast_fn		( const std::string& sInput, const std::string& sSearchFor	) const
{
    return crawl::ieraseLast_fnc(config(), sInput, sSearchFor);
}

std::string ScriptMiner::eraseAll_fn			( const std::string& sInput, const std::string& sSearchFor	) const
{
    return crawl::eraseAll_fnc(config(), sInput, sSearchFor);
}

std::string ScriptMiner::ieraseAll_fn		( const std::string& sInput, const std::string& sSearchFor	) const
{
    return crawl::ieraseAll_fnc(config(), sInput, sSearchFor);
}

std::string ScriptMiner::eraseRegex_fn		( const std::string& sInput, const std::string& sSearchFor	) const
{
    return crawl::eraseRegex_fnc(config(), sInput, sSearchFor);
}

std::string ScriptMiner::eraseAllRegex_fn	( const std::string& sInput, const std::string& sSearchFor	) const
{
    return crawl::eraseAllRegex_fnc(config(), sInput, sSearchFor);
}

std::string ScriptMiner::trimBetween_fn      ( const std::string& sInput, const std::string& sBegin, const std::string& sEnd ) const
{
    return crawl::trimBetween_fnc(config(), sInput, sBegin, sEnd );
}

std::string ScriptMiner::trimBetweenCount_fn  (const std::string& sInput, const std::string& sBegin, const std::string& sEnd, const std::string& sCount ) const
{
    return crawl::trimBetweenCount_fnc(config(), sInput, sBegin, sEnd, sCount );
}

std::string ScriptMiner::trimBetweenCount_fn  (const std::string& sInput, const std::string& sBegin, const std::string& sEnd, int iCount ) const
{
    return crawl::trimBetweenCountInt_fnc(config(), sInput, sBegin, sEnd, iCount );
}

std::string ScriptMiner::trimIntegerCustom_fn( const std::string& sInput, const std::string& iBase, const std::string& sThousandsSep) const
{
    return crawl::trimIntegerCustom_fnc(config(), sInput, iBase, sThousandsSep);
}

std::string ScriptMiner::trimNumberCustom_fn	( const std::string& sInput, const std::string& sDecimalPoint, 	const std::string& sThousandsSep) const
{
    return crawl::trimNumberCustom_fnc(config(), sInput, sDecimalPoint, sThousandsSep);
}

std::string ScriptMiner::replaceFirst_fn		( const std::string& sInput, const std::string& sSearchFor,		const std::string& sReplaceWith	) const
{
    return crawl::replaceFirst_fnc(config(), sInput, sSearchFor, sReplaceWith);
}

std::string ScriptMiner::ireplaceFirst_fn	( const std::string& sInput, const std::string& sSearchFor,		const std::string& sReplaceWith	) const
{
    return crawl::ireplaceFirst_fnc(config(), sInput, sSearchFor, sReplaceWith);
}

std::string ScriptMiner::replaceLast_fn		( const std::string& sInput, const std::string& sSearchFor,		const std::string& sReplaceWith	) const
{
    return crawl::replaceLast_fnc(config(), sInput, sSearchFor, sReplaceWith);
}

std::string ScriptMiner::ireplaceLast_fn		( const std::string& sInput, const std::string& sSearchFor,		const std::string& sReplaceWith	) const
{
    return crawl::ireplaceLast_fnc(config(), sInput, sSearchFor, sReplaceWith);
}

std::string ScriptMiner::replaceAll_fn		( const std::string& sInput, const std::string& sSearchFor,		const std::string& sReplaceWith	) const
{
    return crawl::replaceAll_fnc(config(), sInput, sSearchFor, sReplaceWith);
}

std::string ScriptMiner::ireplaceAll_fn		( const std::string& sInput, const std::string& sSearchFor,		const std::string& sReplaceWith	) const
{
    return crawl::ireplaceAll_fnc(config(), sInput, sSearchFor, sReplaceWith);
}

std::string ScriptMiner::replaceRegex_fn		( const std::string& sInput, const std::string& sSearchFor,		const std::string& sReplaceWith	) const
{
    return crawl::replaceRegex_fnc(config(), sInput, sSearchFor, sReplaceWith);
}

std::string ScriptMiner::replaceAllRegex_fn	( const std::string& sInput, const std::string& sSearchFor,		const std::string& sReplaceWith	) const
{
    return crawl::replaceAllRegex_fnc(config(), sInput, sSearchFor, sReplaceWith);
}

std::string ScriptMiner::eraseNth_fn	( const std::string& sInput, const std::string& sSearchFor,	int iNth 	) const
{
    return crawl::eraseNth_fnc(config(), sInput, sSearchFor, iNth);
}

std::string ScriptMiner::ieraseNth_fn		( const std::string& sInput, const std::string& sSearchFor,	int iNth 	) const
{
    return crawl::ieraseNth_fnc(config(), sInput, sSearchFor, iNth);
}


std::string ScriptMiner::replaceNth_fn	( const std::string& sInput, const std::string& sSearchFor,	const std::string& sReplaceWith, int iNth	) const
{
    return crawl::replaceNth_fnc(config(), sInput, sSearchFor, sReplaceWith, iNth);
}

std::string ScriptMiner::ireplaceNth_fn		( const std::string& sInput, const std::string& sSearchFor,	const std::string& sReplaceWith, int iNth	) const
{
    return crawl::ireplaceNth_fnc(config(), sInput, sSearchFor, sReplaceWith, iNth);
}

std::string ScriptMiner::eraseNth_fn	( const std::string& sInput, const std::string& sSearchFor, const std::string& sNth 	) const
{
    return crawl::eraseNthStrIndex_fnc(config(), sInput, sSearchFor, sNth);
}

std::string ScriptMiner::ieraseNth_fn( const std::string& sInput, const std::string& sSearchFor,     const std::string& sNth 	) const
{
    return crawl::ieraseNthStrIndex_fnc(config(), sInput, sSearchFor, sNth);
}

std::string ScriptMiner::replaceNth_fn	( const std::string& sInput, const std::string& sSearchFor,	const std::string& sReplaceWith ,const std::string& sNth	) const
{
    return crawl::replaceNthStrIndex_fnc(config(), sInput, sSearchFor, sReplaceWith, sNth);
}

std::string ScriptMiner::ireplaceNth_fn	( const std::string& sInput, const std::string& sSearchFor,	const std::string& sReplaceWith, const std::string& sNth	) const
{
    return crawl::ireplaceNthStrIndex_fnc(config(), sInput, sSearchFor, sReplaceWith, sNth);
}




/*
---------------------
--- URL functions ---
--------------------- */
std::string
ScriptMiner::urlSite()
{
    return siteUrl();
}

std::string
ScriptMiner::urlCurrent()
{
    return webBrowser()->currentUri();
}

/** Load new URL directly into browser.*/
bool
ScriptMiner::urlLoad (
    const std::string sUrl		///< [in] URL (as string) to load .
    )
{
    using namespace std;
    m_curMiningStepE = crawl::MiningStepE::stepLoadPageE;
    const auto urlProto = ensureProtocol(sUrl);
    auto&& fn =
            [=,this]() -> bool
    {
        return this->loadURI(urlProto);
    };
    m_crawlerCommandQueue.push(std::move(fn));
    return true;
}

bool
ScriptMiner::urlLoadWait (const std::string sUrl		///< [in] URL (as string) to load .
    , int timeoutInMs)
{
    const bool retval = urlLoad(sUrl);
    waitForDomReady(timeoutInMs);
    return retval;
}

void ScriptMiner::domRebuildWait( int timeoutInMs)
{
    waitingForDomReadySet(true);
    auto&& fn = [=,this]() -> bool {
        this->buildLinearDom ();
        this->waitingForDomReadySet(false); // Signal any script in waiting for dom ready that it can continue.
        return true;
////        signals_manager->signalDomChanged(*webBrowser());
    };
    m_crawlerCommandQueue.push(std::move(fn));
    waitForDomReady(timeoutInMs);
}

/*
---------------------
--- DOM functions ---
--------------------- */
void ScriptMiner::domNewSearch()
{
    boost::shared_ptr<LinearDomSearch> pLinearDomSearch = linearDomSearch();
    if (!pLinearDomSearch) return;
    pLinearDomSearch->newSearch();
    domNodeToCurrentValue();

    // TODO: If below is enabled we get program exit witout crash at all.. Bad!
//    if (pLinearDomSearch) {
//        pLinearDomSearch->newSearch();
//        domNodeToCurrentValue();
//    }
//    else {
//        printf("ML: Debug error ScriptMiner::domNewSearch linearDomSearch() null ptr\n");
    //    }
}

std::vector<int> ScriptMiner::domFindAll(const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps)
{
    int posSave = domPos();
    std::vector<int> positions;
    domNewSearch();
    while ( domFindNext( 1, sSequence, sCompareFun, iPostMatchSteps) ) {
        positions.push_back(domPos());
    }
    domPosSet(posSave);
    return positions;
}

std::vector<int> ScriptMiner::domFindAll(const std::string& sSequence, int iPostMatchSteps)
{
    return domFindAll(sSequence, DefaultCompareFun, iPostMatchSteps);
}

std::vector<int> ScriptMiner::domFindAll(const std::string& sSequence)
{
    return domFindAll(sSequence, DefaultCompareFun, postMatchStepsZero );
}

int ScriptMiner::domFindParentPos (
    int iLevelsUp 			///< [in] Stop at parent number iLevelsUp (ONLY positive numbers).
)
{
    return domParentPos(iLevelsUp);
}


int ScriptMiner::domFindParent(
    int iLevelsUp 			///< [in] Stop at parent number iLevelsUp (ONLY positive numbers).
)
{
    return domPosToParent(iLevelsUp);
}


// -----------------------------
// --- domFindNext functions ---
// -----------------------------
int ScriptMiner::domFindCallPhpFunHelper( const std::string& sSequence, std::string& sPhpFunRetValOut )
{
    int pos = 0;
    sPhpFunRetValOut = "";
    boost::any ret = scriptingClass()->callScriptFunction_Any( sSequence );
    if ( ret.type() == typeid(long) ) {
        int int_val = static_cast<int>(boost::any_cast<long>(ret));
        sPhpFunRetValOut = "";  // If return value is an integer(long) we assume it to be the new dom position
        pos = int_val;
    }
    else {
        try                             { sPhpFunRetValOut = boost::any_cast<std::string>(ret); }
        catch (const boost::bad_any_cast&)    { sPhpFunRetValOut = ""; }
    }
    if (pos) {
        domNodeToCurrentValue();
    }
    return pos;
}


int	ScriptMiner::domSeqFindNextParams(
        int iCount					///< [in] Stop at match number iCount (ONLY positive numbers, i.e forward search ).
      , const crawl::DomSeq& seq	///< [in] Dom sequence to search for
      , const std::string& sArgs	///< [in] Dom sequence arguments - as comma separated string.
      , int iNodeTypes 				///< [in] Restrict to node types. Default is all node types.
    )
{
    auto lds = linearDomSearch();
    if (!lds) return 0;
    using namespace crawl;
    using namespace std;
    int iPos = 0;
    if ( !seq.empty() ) {
        PtrStrVecT pArgs;
        if ( sArgs != "" ) {
            pArgs = PtrStrVecT( new vector<string> );
            vector<string> args;
            cpaf::splitv(args, sArgs, ",");
            for ( vector<string>::const_iterator it = args.begin(); it != args.end(); ++it ) {
                pArgs->push_back( boost::trim_copy( *it ) );
            }
        }
        iPos 	= lds->next( seq, iCount, iNodeTypes, true, pArgs );
    }
    if ( iPos ) domNodeToCurrentValue();
    return iPos;
}

int ScriptMiner::domFindNextHelper(
        int iCount, std::string& sPhpFunRetVal,
        const std::string& sSequence,
        const std::string& sArgs,
        const std::string& sCompareFun,
        int iPostMatchSteps,
        int iNodeTypes)
{
    using namespace crawl;
    using namespace string_compare;

    sPhpFunRetVal = "";
    // First check if a PHP function exists with the given (sSequence) name
    if ( scriptFunctionExists(sSequence) ) {
        boost::any ret = scriptingClass()->callScriptFunction_Any( sSequence );
        if ( ret.type() == typeid(long) )   return static_cast<int>(boost::any_cast<long>(ret));
        else {
            try                                 { sPhpFunRetVal = boost::any_cast<std::string>(ret); }
            catch (const boost::bad_any_cast&)  { sPhpFunRetVal = ""; }
        }
        return domPos();
    }

    // Take care of special case with choices between more dom sequences typically named like:
    // 'MyDomSeq#1', 'MyDomSeq#2', ... And used like outputValueFindNext	( 1, "MyDomSeq", "MyFieldName", .... )
    // Here we must call each of the 'MyDomSeq#n' in turn and the first one to actually return a valid dom position
    // is the one used.
    if ( domSearchMgr()->domSeqChoicesExists( sSequence ) ) {
        DomSearchMgr::DomSeqVecRangeT range = domSearchMgr()->domSeqChoicesGet( sSequence );
        DomSearchMgr::DomSeqVecRangeT::const_iterator it = range.begin();
        int domPosStart = domPos();
        int new_dom_pos = 0;
        for ( ; it != range.end(); ++it ) {
            domPosSet(domPosStart); // Restore start domPos for each choice we try!
            const crawl::DomSeq& seq = *(*it);
            const auto& seq_name = seq.sequenceGet();
            new_dom_pos = 0;
            if ( scriptFunctionExists(seq_name) ) {
                new_dom_pos = domFindCallPhpFunHelper(seq_name, sPhpFunRetVal);
            }
            else {
                new_dom_pos = domSeqFindNextParams( iCount, seq, sArgs, iNodeTypes );
            }
            if ( new_dom_pos != 0 ) {
                break;
            }
        }
        return new_dom_pos;
    }

    // Normal case
    boost::shared_ptr<DomSeq> pDomSeq = domSearchMgr()->domSeqGet( sSequence );
    if ( pDomSeq ) {
        const auto& seq_name = pDomSeq->sequenceGet();
        if ( scriptFunctionExists( seq_name ) ) {
            boost::any ret = scriptingClass()->callScriptFunction_Any( seq_name );
            if ( ret.type() == typeid(long) )   return static_cast<int>(boost::any_cast<long>(ret));
            else {
                try                                 { sPhpFunRetVal = boost::any_cast<std::string>(ret); }
                catch (const boost::bad_any_cast&)  { sPhpFunRetVal = ""; }
            }
            return domPos();
        }
        else {
            return domSeqFindNextParams( iCount, *pDomSeq, sArgs, iNodeTypes );
        }
    }
    else {
        // Create a dom sequece directly from the sequence string, unless it ends with __FIND, which
        // we assume then to be a "real" named" sequence which was accidentially not (yet) defined
        if (endsWith(sSequence, "__FIND")) {
            return 0;
        }
        pDomSeq = boost::shared_ptr<DomSeq>( new DomSeq( 1, sSequence, sCompareFun, iPostMatchSteps, crawl::DomNodeTypes::ALL_NODE_TYPES, "," ) );
        return domSeqFindNextParams( iCount, *pDomSeq, sArgs, iNodeTypes );
    }
}


int ScriptMiner::domFindNextImpl (
      int iCount							///< Stop at iCount occurrence of sequence. Negative values searches backwards. Not applicaple \a sSequence refers to a user defined PHP function
    , std::string& sPhpFunRetVal            ///< Return value from user defined PHP function in case it was a PHP function that was called, and not a normal dom sequence.
    , const std::string& sSequence          ///< Named dom sequence, or string to use as dom sequence. Can also be the name of a user defined PHP function to call to do the actual dom search.
    , const std::string& sArgs              ///< Arguments to dom sequence. Only applicable to sequences with parameters.
    , const std::string& sCompareFun		///< Default compare function to use in case \a sSequence is used to create a dom sequence in place.
    , int iPostMatchSteps                   ///< Dom positions to move after we have matched the sequence. Only used when sequence is not a named sequence but rather a "direct" expression like domFind("class, MyClass", "constains", 3);
    , int iNodeTypes						///< Restrict search to certain node types. Typically ALL_NODE_TYPES.
    )
{

    const int domPosStart = domPos();
    const int domPosFound = domFindNextHelper(iCount, sPhpFunRetVal, sSequence, sArgs, sCompareFun, iPostMatchSteps, iNodeTypes);
    if (m_showDomFindCalls) {
        std::cerr << "DBG: domFindNext('" << sSequence << "', '" << sCompareFun << "')"
                  << "; Pos (start, found) => [" <<  domPosStart << ", " << domPosFound << "]"
                  << "\n";
    }
    if ( (iCount >= 0 && (domPosFound <= domPosStart)) ||
         (iCount < 0 && (domPosFound >= domPosStart))
         ) {
        linearDomSearch()->setCurrentPosToEnd();    // If not found set current postion to last element in linear dom
        return 0;
    }
    else {
        domPosSet(domPosFound); // Ensure we get the current dom pos updated. Also in case a useed defined function "forgets"
    }
    return domPosFound;
}

int ScriptMiner::domFindNext(
        int iCount,
        const std::string& sSequence,
        const std::string &sCompareFun,
        int iPostMatchSteps,
        int iNodeTypes)
{
    std::string sPhpFunRetVal;
    return domFindNextImpl( iCount, sPhpFunRetVal, sSequence, "", sCompareFun, iPostMatchSteps, iNodeTypes );
}


int ScriptMiner::domFindNext (
      int iCount                            ///< Stop at iCount occurrence of sequence. Negative values searches backwards. Not applicaple \a sSequence refers to a user defined PHP function
    , const std::string& sSequence          ///< Named dom sequence, or string to use as dom sequence. Can also be the name of a user defined PHP function to call to do the actual dom search.
    , const std::string& sCompareFun		///< Default compare function to use in case \a sSequence is used to create a dom sequence in place.
    , int iPostMatchSteps					///< Restrict search to certain node types. Typically ALL_NODE_TYPES.
    )
{
    std::string sPhpFunRetVal;
    return domFindNextImpl( iCount, sPhpFunRetVal, sSequence, "", sCompareFun, iPostMatchSteps, crawl::DomNodeTypes::ALL_NODE_TYPES );
}


int ScriptMiner::domFindNext (
     int iCount							///< Stop at iCount occurrence of sequence. Negative values searches backwards. Not applicaple \a sSequence refers to a user defined PHP function
    ,const std::string& sSequence		///< Named dom sequence, or string to use as dom sequence. Can also be the name of a user defined PHP function to call to do the actual dom search.
    ,const std::string& sCompareFun		///< Default compare function to use in case \a sSequence is used to create a dom sequence in place.
    )
{
    return domFindNext ( iCount, sSequence, sCompareFun, postMatchStepsZero );
}


int ScriptMiner::domFindNext (int iCount	///< Stop at iCount occurrence of sequence. Negative values searches backwards. Not applicaple \a sSequence refers to a user defined PHP function
    , const std::string& sSequence          ///< Named dom sequence, or string to use as dom sequence. Can also be the name of a user defined PHP function to call to do the actual dom search.
    , int iPostMatchSteps                   ///< Restrict search to certain node types. Typically ALL_NODE_TYPES.
    )
{
    return domFindNext ( iCount, sSequence, DefaultCompareFun, iPostMatchSteps );
}

int ScriptMiner::domFindNext (
     int iCount							///< Stop at iCount occurrence of sequence. Negative values searches backwards. Not applicaple \a sSequence refers to a user defined PHP function
    ,const std::string& sSequence		///< Named dom sequence, or string to use as dom sequence. Can also be the name of a user defined PHP function to call to do the actual dom search.
    )
{
    return domFindNext ( iCount, sSequence, DefaultCompareFun, postMatchStepsZero );
}

int ScriptMiner::domFindNext(const std::string &sSequence, const std::string &sCompareFun, int iPostMatchSteps, int iNodeTypes)
{
    return domFindNext ( 1, sSequence, sCompareFun, iPostMatchSteps, iNodeTypes );
}

int ScriptMiner::domFindNext(const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps)
{
    return domFindNext ( 1, sSequence, sCompareFun, iPostMatchSteps );
}

int ScriptMiner::domFindNext (
     const std::string& sSequence		///< Named dom sequence, or string to use as dom sequence. Can also be the name of a user defined PHP function to call to do the actual dom search.
    ,const std::string& sCompareFun		///< Default compare function to use in case \a sSequence is used to create a dom sequence in place.
    )
{
    return domFindNext ( 1, sSequence, sCompareFun, postMatchStepsZero );
}

int ScriptMiner::domFindNext(const std::string& sSequence, int iPostMatchSteps)
{
    return domFindNext ( 1, sSequence, ScriptMiner::DefaultCompareFun, iPostMatchSteps );
}

int ScriptMiner::domFindNext (
     const std::string& sSequence		///< Named dom sequence, or string to use as dom sequence. Can also be the name of a user defined PHP function to call to do the actual dom search.
    )
{
    return domFindNext ( 1, sSequence, ScriptMiner::DefaultCompareFun, postMatchStepsZero );
}

int ScriptMiner::domFindPrev (
     const std::string& sSequence		///< Named dom sequence, or string to use as dom sequence. Can also be the name of a user defined PHP function to call to do the actual dom search.
    ,const std::string& sCompareFun		///< Default compare function to use in case \a sSequence is used to create a dom sequence in place.
    )
{
    return domFindNext ( -1, sSequence, sCompareFun, postMatchStepsZero );
}

int ScriptMiner::domSeqFindNextParams (
      int iCount
    , const std::string& sSequence
    , const std::string& sArgs
    )
{
    std::string sPhpFunRetVal;
    return domFindNextImpl( iCount, sPhpFunRetVal, sSequence, sArgs, DefaultCompareFun, postMatchStepsZero, crawl::DomNodeTypes::ALL_NODE_TYPES );
}



// -------------------------
// --- domFind functions ---
// -------------------------
int ScriptMiner::domFind(int iCount, const std::string &sSequence, const std::string &sCompareFun, int iPostMatchSteps, int iNodeTypes)
{
    domNewSearch();
    return domFindNext ( iCount, sSequence, sCompareFun , iPostMatchSteps, iNodeTypes );
}

int ScriptMiner::domFind (
      int iCount						///< Stop at iCount occurrence of sequence. Negative values searches backwards. Not applicaple \a sSequence refers to a user defined PHP function
    , const std::string& sSequence		///< Named dom sequence, or string to use as dom sequence. Can also be the name of a user defined PHP function to call to do the actual dom search.
    , const std::string& sCompareFun	///< Default compare function to use in case \a sSequence is used to create a dom sequence in place.
    , int iPostMatchSteps				///< [in] Steps to move forward or backwards (negative) in dom after a match.
    )
{
    domNewSearch();
    return domFindNext ( iCount, sSequence, sCompareFun , iPostMatchSteps );
}

int ScriptMiner::domFind (
     int iCount							///< Stop at iCount occurrence of sequence. Negative values searches backwards. Not applicaple \a sSequence refers to a user defined PHP function
    ,const std::string& sSequence		///< Named dom sequence, or string to use as dom sequence. Can also be the name of a user defined PHP function to call to do the actual dom search.
    ,const std::string& sCompareFun		///< Default compare function to use in case \a sSequence is used to create a dom sequence in place.
    )
{
    return domFind ( iCount, sSequence, sCompareFun, postMatchStepsZero );
}


int ScriptMiner::domFind (int iCount							///< Stop at iCount occurrence of sequence. Negative values searches backwards. Not applicaple \a sSequence refers to a user defined PHP function
    , const std::string& sSequence		///< Named dom sequence, or string to use as dom sequence. Can also be the name of a user defined PHP function to call to do the actual dom search.
    , int iPostMatchSteps						///< Restrict search to certain node types. Typically ALL_NODE_TYPES.
    )
{
    return domFind ( iCount, sSequence, DefaultCompareFun, iPostMatchSteps );
}

int ScriptMiner::domFind (
     int iCount							///< Stop at iCount occurrence of sequence. Negative values searches backwards. Not applicaple \a sSequence refers to a user defined PHP function
    ,const std::string& sSequence		///< Named dom sequence, or string to use as dom sequence. Can also be the name of a user defined PHP function to call to do the actual dom search.
    )
{
    return domFind ( iCount, sSequence, DefaultCompareFun, postMatchStepsZero );
}

int ScriptMiner::domFind(const std::string &sSequence, const std::string &sCompareFun, int iPostMatchSteps, int iNodeTypes)
{
    return domFind ( 1, sSequence, sCompareFun, iPostMatchSteps, iNodeTypes );
}

int ScriptMiner::domFind(const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps)
{
    return domFind ( 1, sSequence, sCompareFun, iPostMatchSteps );
}

int ScriptMiner::domFind (
     const std::string& sSequence		///< Named dom sequence, or string to use as dom sequence. Can also be the name of a user defined PHP function to call to do the actual dom search.
    ,const std::string& sCompareFun		///< Default compare function to use in case \a sSequence is used to create a dom sequence in place.
        )
{
    return domFind ( 1, sSequence, sCompareFun, postMatchStepsZero );
}

int ScriptMiner::domFind(const std::string& sSequence, int iPostMatchSteps)
{
    return domFind ( 1, sSequence, DefaultCompareFun, iPostMatchSteps );
}

int ScriptMiner::domFind (
     const std::string& sSequence		///< Named dom sequence, or string to use as dom sequence. Can also be the name of a user defined PHP function to call to do the actual dom search.
        )
{
    return domFind ( 1, sSequence, DefaultCompareFun, postMatchStepsZero );
}

int ScriptMiner::domFindPos(int iCount, const std::string &sSequence, const std::string &sCompareFun, int iPostMatchSteps, int iNodeTypes)
{
    int iPosSave = domPos();
    int iPos = domFind( iCount, sSequence, sCompareFun, iPostMatchSteps, iNodeTypes );
    domPosSet(iPosSave);
    return iPos;
}


int ScriptMiner::domFindPos (
      int iCount                            ///< Stop at iCount occurrence of sequence. Negative values searches backwards. Not applicaple \a sSequence refers to a user defined PHP function
    , const std::string& sSequence          ///< Named dom sequence, or string to use as dom sequence. Can also be the name of a user defined PHP function to call to do the actual dom search.
    , const std::string& sCompareFun		///< Default compare function to use in case \a sSequence is used to create a dom sequence in place.
    , int iPostMatchSteps					///< [in] Steps to move forward or backwards (negative) in dom after a match.
                )
{
    int iPosSave = domPos();
    int iPos = domFind( iCount, sSequence, sCompareFun, iPostMatchSteps );
    domPosSet(iPosSave);
    return iPos;
}

int ScriptMiner::domFindPos (
     int iCount							///< Stop at iCount occurrence of sequence. Negative values searches backwards. Not applicaple \a sSequence refers to a user defined PHP function
    ,const std::string& sSequence		///< Named dom sequence, or string to use as dom sequence. Can also be the name of a user defined PHP function to call to do the actual dom search.
    ,const std::string& sCompareFun		///< Default compare function to use in case \a sSequence is used to create a dom sequence in place.
    )
{
    return domFindPos ( iCount, sSequence, sCompareFun, postMatchStepsZero );
}


int ScriptMiner::domFindPos (
      int iCount                        ///< Stop at iCount occurrence of sequence. Negative values searches backwards. Not applicaple \a sSequence refers to a user defined PHP function
    , const std::string& sSequence		///< Named dom sequence, or string to use as dom sequence. Can also be the name of a user defined PHP function to call to do the actual dom search.
    , int iPostMatchSteps				///< [in] Steps to move forward or backwards (negative) in dom after a match.
    )
{
    return domFindPos ( iCount, sSequence, DefaultCompareFun, iPostMatchSteps );
}

int ScriptMiner::domFindPos (
     int iCount							///< Stop at iCount occurrence of sequence. Negative values searches backwards. Not applicaple \a sSequence refers to a user defined PHP function
    ,const std::string& sSequence		///< Named dom sequence, or string to use as dom sequence. Can also be the name of a user defined PHP function to call to do the actual dom search.
    )
{
    return domFindPos ( iCount, sSequence, DefaultCompareFun, postMatchStepsZero );
}

int ScriptMiner::domFindPos(const std::string &sSequence, const std::string &sCompareFun, int iPostMatchSteps, int iNodeTypes)
{
    return domFindPos ( 1, sSequence, sCompareFun, iPostMatchSteps, iNodeTypes );
}

int ScriptMiner::domFindPos(
          const std::string& sSequence
        , const std::string& sCompareFun
        , int iPostMatchSteps               ///< [in] Steps to move forward or backwards (negative) in dom after a match.
        )
{
    return domFindPos ( 1, sSequence, sCompareFun, iPostMatchSteps );
}

int ScriptMiner::domFindPos (
     const std::string& sSequence		///< Named dom sequence, or string to use as dom sequence. Can also be the name of a user defined PHP function to call to do the actual dom search.
    ,const std::string& sCompareFun		///< Default compare function to use in case \a sSequence is used to create a dom sequence in place.
    )
{
    return domFindPos ( 1, sSequence, sCompareFun, postMatchStepsZero );
}

int ScriptMiner::domFindPos(const std::string& sSequence, int iPostMatchSteps)
{
    return domFindPos ( 1, sSequence, DefaultCompareFun, iPostMatchSteps );
}


int ScriptMiner::domFindPos (
     const std::string& sSequence		///< Named dom sequence, or string to use as dom sequence. Can also be the name of a user defined PHP function to call to do the actual dom search.
    )
{
    return domFindPos ( 1, sSequence, DefaultCompareFun, postMatchStepsZero );
}

int ScriptMiner::domFindNextPos(int iCount, const std::string &sSequence, const std::string &sCompareFun, int iPostMatchSteps, int iNodeTypes)
{
    int iPosSave = domPos();
    int iPos = domFindNext( iCount, sSequence, sCompareFun, iPostMatchSteps, iNodeTypes );
    domPosSet(iPosSave);
    return iPos;
}


int ScriptMiner::domFindNextPos (
      int iCount							///< Stop at iCount occurrence of sequence. Negative values searches backwards. Not applicaple \a sSequence refers to a user defined PHP function
    , const std::string& sSequence          ///< Named dom sequence, or string to use as dom sequence. Can also be the name of a user defined PHP function to call to do the actual dom search.
    , const std::string& sCompareFun		///< Default compare function to use in case \a sSequence is used to create a dom sequence in place.
    , int iPostMatchSteps					///< [in] Steps to move forward or backwards (negative) in dom after a match.
    )
{
    int iPosSave = domPos();
    int iPos = domFindNext( iCount, sSequence, sCompareFun, iPostMatchSteps );
    domPosSet(iPosSave);
    return iPos;
}

int ScriptMiner::domFindNextPos (
     int iCount							///< Stop at iCount occurrence of sequence. Negative values searches backwards. Not applicaple \a sSequence refers to a user defined PHP function
    ,const std::string& sSequence		///< Named dom sequence, or string to use as dom sequence. Can also be the name of a user defined PHP function to call to do the actual dom search.
    ,const std::string& sCompareFun		///< Default compare function to use in case \a sSequence is used to create a dom sequence in place.
    )
{
    return domFindNextPos ( iCount, sSequence, sCompareFun, postMatchStepsZero );
}


int ScriptMiner::domFindNextPos (
      int iCount						///< Stop at iCount occurrence of sequence. Negative values searches backwards. Not applicaple \a sSequence refers to a user defined PHP function
    , const std::string& sSequence		///< Named dom sequence, or string to use as dom sequence. Can also be the name of a user defined PHP function to call to do the actual dom search.
    , int iPostMatchSteps				///< [in] Steps to move forward or backwards (negative) in dom after a match.
    )
{
    return domFindNextPos ( iCount, sSequence, DefaultCompareFun, iPostMatchSteps );
}

int ScriptMiner::domFindNextPos (
     int iCount							///< Stop at iCount occurrence of sequence. Negative values searches backwards. Not applicaple \a sSequence refers to a user defined PHP function
    , const std::string& sSequence		///< Named dom sequence, or string to use as dom sequence. Can also be the name of a user defined PHP function to call to do the actual dom search.
    )
{
    return domFindNextPos ( iCount, sSequence, DefaultCompareFun, postMatchStepsZero );
}

int ScriptMiner::domFindNextPos(const std::string &sSequence, const std::string &sCompareFun, int iPostMatchSteps, int iNodeTypes)
{
    return domFindNextPos ( 1, sSequence, sCompareFun, iPostMatchSteps, iNodeTypes);
}

int ScriptMiner::domFindNextPos(
          const std::string& sSequence
        , const std::string& sCompareFun
        , int iPostMatchSteps               ///< [in] Steps to move forward or backwards (negative) in dom after a match.
        )
{
    return domFindNextPos ( 1, sSequence, sCompareFun, iPostMatchSteps);
}

int ScriptMiner::domFindNextPos (
     const std::string& sSequence		///< Named dom sequence, or string to use as dom sequence. Can also be the name of a user defined PHP function to call to do the actual dom search.
    ,const std::string& sCompareFun		///< Default compare function to use in case \a sSequence is used to create a dom sequence in place.
    )
{
    return domFindNextPos ( 1, sSequence, sCompareFun, postMatchStepsZero );
}

int ScriptMiner::domFindNextPos(const std::string& sSequence, int iPostMatchSteps)
{
    return domFindNextPos ( 1, sSequence, DefaultCompareFun, iPostMatchSteps );
}


int ScriptMiner::domFindNextPos (
     const std::string& sSequence		///< Named dom sequence, or string to use as dom sequence. Can also be the name of a user defined PHP function to call to do the actual dom search.
    )
{
    return domFindNextPos ( 1, sSequence, DefaultCompareFun, postMatchStepsZero );
}

int ScriptMiner::domFindPrevPos (
     const std::string& sSequence		///< Named dom sequence, or string to use as dom sequence. Can also be the name of a user defined PHP function to call to do the actual dom search.
    ,const std::string& sCompareFun		///< Default compare function to use in case \a sSequence is used to create a dom sequence in place.
    )
{
    return domFindNextPos ( -1, sSequence, sCompareFun, postMatchStepsZero );
}

// -------------------

int	ScriptMiner::domClickInput( int iCount ) 	///< [in] Stop at match number iCount (ONLY positive numbers, i.e forward search ).
{
    linearDomSearch()->newSearch();
    int iPos = linearDomSearch()->next( "INPUT", crawl::string_compare::equals, iCount, DomNodeTypes::ELEMENT, true );
    if ( iPos && linearDomSearch()->curElemPtr() ) {
        linearDomSearch()->curElemPtr()->click();
        domNodeToCurrentValue();
    }
    return iPos;
}

int	ScriptMiner::domClickInputNext( int iCount ) 		///< [in] Stop at match number iCount ( use negative numbers for backwards search ).
{
    int iPos = linearDomSearch()->next( "INPUT", crawl::string_compare::equals, iCount, DomNodeTypes::ELEMENT, true );
    if ( iPos && linearDomSearch()->curElemPtr() ) {
        linearDomSearch()->curElemPtr()->click();
        domNodeToCurrentValue();
    }
    return iPos;
}

int	ScriptMiner::domSetInput	(
    int iCount,							///< [in] Stop at match number iCount ( use negative numbers for backwards search ).
    const std::string& /*sValue*/ 	)
{
    linearDomSearch()->newSearch();
    int iPos = linearDomSearch()->next( "INPUT", crawl::string_compare::equals, iCount, DomNodeTypes::ELEMENT, true );
    if ( iPos && linearDomSearch()->curElemPtr() ) {
        std::cerr << "TODO NOT IMPLEMENTED: domSetInput()\n";
        //linearDomSearch()->curElemPtr()->inputSet( sValue );
        domNodeToCurrentValue();
    }
    return iPos;
}

int	ScriptMiner::domSetInputNext	(
    int iCount,							///< [in] Stop at match number iCount ( use negative numbers for backwards search ).
    const std::string& /*sValue*/ 	)
{
    int iPos = linearDomSearch()->next( "INPUT", crawl::string_compare::equals, iCount, DomNodeTypes::ELEMENT, true );
    if ( iPos && linearDomSearch()->curElemPtr() ) {
        std::cerr << "TODO NOT IMPLEMENTED: domSetInput()\n";
//        linearDomSearch()->curElemPtr()->inputSet( sValue );
        domNodeToCurrentValue();
    }
    return iPos;
}

int	ScriptMiner::domSetInput	(
    int iCount,					///< [in] Stop at match number iCount ( use negative numbers for backwards search ).
    int iValue 	)
{
    return domSetInput( iCount, std::to_string( iValue ) );
}


int	ScriptMiner::domSetInputNext	(
    int iCount,					///< [in] Stop at match number iCount ( use negative numbers for backwards search ).
    int iValue 	)
{
    return domSetInputNext( iCount, std::to_string( iValue ) );
}


int	ScriptMiner::domStep	(
    int iCount, 		///< [in] Stop at match number iCount ( use negative numbers for backwards search ).
    int iNodeTypes )	///< [in] Restrict to node types. Default is all node types.
{
    int iPos  = linearDomSearch()->step( iCount, iNodeTypes);
    if ( iPos ) domNodeToCurrentValue();
    return iPos;
}

bool ScriptMiner::domAtEnd()
{
    return linearDomSearch()->atDomEnd();
}

void ScriptMiner::domRangePushElement(int iElementPos)
{
    domRangePush(iElementPos, posEndElementPos(iElementPos));
}

void ScriptMiner::domRangePush(int iStartPos, int iStopPos)
{
    linearDomSearch()->rangePush(iStartPos, iStopPos);
}

void ScriptMiner::domRangePop()
{
    linearDomSearch()->rangePop();
}


void ScriptMiner::domPointerPush()
{
    linearDomSearch()->iteratorPush();
}

int	ScriptMiner::domPointerPop()
{
    int iPos = linearDomSearch()->iteratorPop();
    if ( iPos ) domNodeToCurrentValue();
    return iPos;
}

int ScriptMiner::domSize()
{
    if ( ! linearDomSearch() )  return 0;
    return static_cast<int>( linearDomSearch()->domSize() );
}

int ScriptMiner::domEndPos()
{
    if ( ! linearDomSearch() )  return 0;
    return static_cast<int>( linearDomSearch()->domEndPos() );
}

int ScriptMiner::domPos()
{
    if ( ! linearDomSearch() )  return 0;
    return static_cast<int>( linearDomSearch()->iteratorPos() );
}

int
ScriptMiner::domPosSet( int iNewPos )
{
    if ( ! linearDomSearch() )  return 0;
    auto pos = static_cast<int>(linearDomSearch()->iteratorPos(iNewPos));
    if (pos) {
        domNodeToCurrentValue();
    }
    return pos;
}

int ScriptMiner::domStartPosSet( int iStartPos )
{
    if ( ! linearDomSearch() )  return 0;
    return linearDomSearch()->setStartPos(iStartPos);
}

int ScriptMiner::domStartPos()
{
    if ( ! linearDomSearch() )  return 0;
    return linearDomSearch()->getStartPos();
}


void ScriptMiner::domStartPosClear ()
{
    if ( ! linearDomSearch() )  return;
    linearDomSearch()->clearStartPos();
}

int ScriptMiner::domStopPosSet( int iStopPos )
{
    if ( ! linearDomSearch() )  return 0;
    return linearDomSearch()->setStopPos(iStopPos);
}

int ScriptMiner::domStopPos()
{
    if ( ! linearDomSearch() )  return 0;
    return linearDomSearch()->getStopPos();
}


void ScriptMiner::domStopPosClear ()
{
    if ( ! linearDomSearch() )  return;
    linearDomSearch()->clearStopPos();
}

void ScriptMiner::domSetAtEnd ()
{
    if ( ! linearDomSearch() )  return;
    linearDomSearch()->setCurrentPosToEnd();
}

int ScriptMiner::domContinuePos()
{
    auto it = m_handlerContinuePositions.find(m_sHandlerContextName);
    if (it != m_handlerContinuePositions.end()) return it->second;
    return 0;
}

int ScriptMiner::domThisElementPos()
{
    return linearDomSearch()->linearDom().thisElementPos(domPos());
}

int ScriptMiner::domThisElementPos(int pos)
{
    return linearDomSearch()->linearDom().thisElementPos(pos);
}

int ScriptMiner::domOwnerPos(int iLevelsUp)
{
    auto pos = linearDomSearch()->iteratorPos();
    return static_cast<int>(linearDomSearch()->linearDom().ownerPos(pos, iLevelsUp));
}

int ScriptMiner::domPosToOwner(int iLevelsUp)
{
    int pos = domOwnerPos(iLevelsUp);
    if ( pos ) {
        domPosSet(pos);
    }
    return pos;
}

int ScriptMiner::domParentPos(int iLevelsUp)
{
    auto pos = linearDomSearch()->iteratorPos();
    return static_cast<int>(linearDomSearch()->linearDom().parentPos(pos, iLevelsUp));
}

int ScriptMiner::domPosToParent(int iLevelsUp)
{
    int pos = domOwnerPos(iLevelsUp);
    if ( pos ) {
        domPosSet(pos);
    }
    return pos;
}


// -------------------------------------
// --- DOM Sequence create functions ---
// -------------------------------------
void ScriptMiner::domSeqCreate (
      int iCount                        ///< [in] Stop at match number iCount (use negative numbers for backwards search).
    , const std::string& sName 			///< [in] Unique name to assign the dom sequence.
    , const std::string& sSequence		///< [in] The actual sequence (by default comma separated).
    , const std::string& sCompareFun	///< [in] Name of default compare function to use.
    , int iPostMatchSteps				///< [in] Steps to move forward or backwards (negative) in dom after a match.
    , int iNodeTypes
    , const std::string& sCommaChar		///< [in] Separation char to use (default is comma ',')
    )
{
    using namespace crawl;
    using namespace crawl::string_compare;

    std::string sSepChar(sCommaChar);
    if ( sSepChar.empty() )	sSepChar = ",";

    boost::shared_ptr<DomSeq>  pDomSeq = boost::shared_ptr<DomSeq>( new DomSeq( iCount, sSequence, sCompareFun, iPostMatchSteps, iNodeTypes, sSepChar ) );
    domSearchMgr()->domSeqAdd( sName, pDomSeq );
}

void ScriptMiner::domSeqCreate(
        int iCount
        , const std::string &sName
        , const std::string &sSequence
        , const std::string &sCompareFun
        , int iPostMatchSteps
        , int iNodeTypes)
{
    domSeqCreate ( iCount, sName, sSequence, sCompareFun, iPostMatchSteps, iNodeTypes, "," );
}

void ScriptMiner::domSeqCreate (
      int iCount                        ///< [in] Stop at match number iCount (use negative numbers for backwards search).
    , const std::string& sName 			///< [in] Unique name to assign the dom sequence.
    , const std::string& sSequence
    , const std::string& sCompareFun
    , int iPostMatchSteps
                  )
{
    domSeqCreate ( iCount, sName, sSequence, sCompareFun, iPostMatchSteps, crawl::DomNodeTypes::ALL_NODE_TYPES, "," );
}

void ScriptMiner::domSeqCreate (
      int iCount                        ///< [in] Stop at match number iCount (use negative numbers for backwards search).
    , const std::string& sName 			///< [in] Unique name to assign the dom sequence.
    , const std::string& sSequence
    , const std::string& sCompareFun
    )
{
    domSeqCreate ( iCount, sName, sSequence, sCompareFun, 0, crawl::DomNodeTypes::ALL_NODE_TYPES, ","  );
}


void ScriptMiner::domSeqCreate (
      int iCount                        ///< [in] Stop at match number iCount (use negative numbers for backwards search).
    , const std::string& sName 			///< [in] Unique name to assign the dom sequence.
    , const std::string& sSequence
    , int iPostMatchSteps
                  )
{
    domSeqCreate ( iCount, sName, sSequence, DefaultCompareFun, iPostMatchSteps, crawl::DomNodeTypes::ALL_NODE_TYPES, ","  );
}

void ScriptMiner::domSeqCreate (
      int iCount                        ///< [in] Stop at match number iCount (use negative numbers for backwards search).
    , const std::string& sName 			///< [in] Unique name to assign the dom sequence.
    , const std::string& sSequence
                  )
{
    domSeqCreate ( iCount, sName, sSequence, DefaultCompareFun, 0, crawl::DomNodeTypes::ALL_NODE_TYPES, ","  );
}

void ScriptMiner::domSeqCreate (
     const std::string& sName 			///< [in] Unique name to assign the dom sequence.
    ,const std::string& sSequence		///< [in] The actual sequence (by default comma separated).
    ,const std::string& sCompareFun		///< [in] Name of default compare function to use.
    ,int iPostMatchSteps				///< [in] Steps to move forward or backwards (negative) in dom after a match.
    ,int iNodeTypes
    ,const std::string& sCommaChar		///< [in] Separation char to use (default is comma ',')
    )
{
    domSeqCreate ( 0, sName, sSequence, sCompareFun, iPostMatchSteps, iNodeTypes, sCommaChar );
}

void ScriptMiner::domSeqCreate(
        const std::string &sName
        , const std::string &sSequence
        , const std::string &sCompareFun
        , int iPostMatchSteps
        , int iNodeTypes)
{
    domSeqCreate ( 0, sName, sSequence, sCompareFun, iPostMatchSteps, iNodeTypes, "," );
}


void ScriptMiner::domSeqCreate (
     const std::string& sName
    ,const std::string& sSequence
    ,const std::string& sCompareFun
    ,int iPostMatchSteps
                  )
{
    domSeqCreate ( 0, sName, sSequence, sCompareFun, iPostMatchSteps, crawl::DomNodeTypes::ALL_NODE_TYPES, "," );
}

void ScriptMiner::domSeqCreate (
     const std::string& sName
    ,const std::string& sSequence
    ,const std::string& sCompareFun
    )
{
    domSeqCreate ( 0, sName, sSequence, sCompareFun, 0, crawl::DomNodeTypes::ALL_NODE_TYPES, ","  );
}


void ScriptMiner::domSeqCreate (
     const std::string& sName
    ,const std::string& sSequence
    ,int iPostMatchSteps
                  )
{
    domSeqCreate ( 0, sName, sSequence, DefaultCompareFun, iPostMatchSteps, crawl::DomNodeTypes::ALL_NODE_TYPES, ","  );
}

void ScriptMiner::domSeqCreate (
     const std::string& sName
    ,const std::string& sSequence
                  )
{
    domSeqCreate ( 0, sName, sSequence, DefaultCompareFun, 0, crawl::DomNodeTypes::ALL_NODE_TYPES, ","  );
}

bool ScriptMiner::domSeqExists ( const std::string& sName ) const
{
    return  domSearchMgr()->domSequenceExists(sName) ||
            scriptFunctionExists(sName);
}

void ScriptMiner::lfwMatchWholeWordsOnlySet(bool matchWholeWordsOnly)
{
    m_lookForWordDomFinder->matchWholeWordsOnlySet(matchWholeWordsOnly);
}

void ScriptMiner::lfwClear()
{
    for (auto& pair : m_lookForWordMgrs) {
        if (pair.second)
            pair.second->clear();
    }
}

void ScriptMiner::lfwClear(const std::string& contextName)
{
    lookForWordMgr(contextName)->clear();
}

void ScriptMiner::lfwClear(const std::string& contextName, const std::string& referenceName)
{
    lookForWordMgr(contextName)->clear(toQString(referenceName));
}

void ScriptMiner::lfwAddWord(const std::string& contextName, const std::string& referenceName,
                             const std::string& word, const std::string& compareFun, int nodeTypes)
{
    lookForWordMgr(contextName)->addLookForWord(toQString(referenceName), toQString(word), toQString(compareFun), nodeTypes);
}

void ScriptMiner::lfwRemoveWord(const std::string& contextName, const std::string& referenceName, const std::string& word)
{
    lookForWordMgr(contextName)->removeLookForWord(toQString(referenceName), toQString(word));
}

void ScriptMiner::lfwGetDataFunctionSet(const std::string& contextName, const std::string& getDataFunction)
{
    lookForWordMgr(contextName)->getDataFunctionSet(getDataFunction);
}

void ScriptMiner::lfwGetDataFallbackFunctionSet(const std::string& contextName, const std::string& getDataFallbackFunction)
{
    lookForWordMgr(contextName)->getDataFallbackFunctionSet(getDataFallbackFunction);
}

int ScriptMiner::lfwDomFindNext(const std::string& referenceName)
{
    return m_lookForWordDomFinder->domFindNext(currentLookForWordMgr(), toQString(referenceName));
}

std::string ScriptMiner::lfwOutputValueFindNext(const std::string& referenceName)
{
    std::string outputValue;
    m_lookForWordDomFinder->outputValueFindNext(outputValue, currentLookForWordMgr(), toQString(referenceName));
    return outputValue;
}

std::string ScriptMiner::lfwPreSequence(const std::string& contextName)
{
    return lookForWordMgr(contextName)->lfwPreSequence();
}

void ScriptMiner::lfwPreSequenceSet(const std::string& contextName, const std::string& lfwPreSequence)
{
    lookForWordMgr(contextName)->lfwPreSequenceSet(lfwPreSequence);
}

std::string ScriptMiner::lfwPostSequence(const std::string& contextName)
{
    return lookForWordMgr(contextName)->lfwPostSequence();
}

void ScriptMiner::lfwPostSequenceSet(const std::string& contextName, const std::string& lfwPostSequence)
{
    lookForWordMgr(contextName)->lfwPostSequenceSet(lfwPostSequence);
}

std::string ScriptMiner::lfwStartPosDomSeq(const std::string& contextName) const
{
    return lookForWordMgr(contextName)->lfwStartPosDomSeq();
}

void ScriptMiner::lfwStartPosDomSeqSet(const std::string& contextName, const std::string& lfwStartPosDomSeq)
{
    lookForWordMgr(contextName)->lfwStartPosDomSeqSet(lfwStartPosDomSeq);
}

std::string ScriptMiner::lfwStopPosDomSeq(const std::string& contextName) const
{
    return lookForWordMgr(contextName)->lfwStopPosDomSeq();
}

void ScriptMiner::lfwStopPosDomSeqSet(const std::string& contextName, const std::string& lfwStopPosDomSeq)
{
    lookForWordMgr(contextName)->lfwStopPosDomSeqSet(lfwStopPosDomSeq);
}

/*
----------------------------------
--- Element children functions ---
---------------------------------  */
std::vector<int> ScriptMiner::nodeChildren(int iSearchDir)
{
    return nodeChildren("", iSearchDir);
}

std::vector<int> ScriptMiner::nodeChildren(const std::string& tagName, int iSearchDir)
{
    const auto it = helperGetNearestLinearIter(iSearchDir);
    if (it == linearDom()->end()) return std::vector<int>();

    const auto pos = it->thisPos();
    return linearDomSearch()->childPositions(pos, tagName);
}

std::vector<int> ScriptMiner::nodeChildrenRecur(const std::string& tagName, int iSearchDir)
{
    std::cerr << "ERROR TODO: Not implemented correctly - yet: ScriptMiner::nodeChildrenRecur()\n";
    const auto it = helperGetNearestLinearIter(iSearchDir);
    if (it == linearDom()->end()) return std::vector<int>();

    const auto pos = it->thisPos();
    return linearDomSearch()->childPositions(pos, tagName);
}

int ScriptMiner::nodeEndElementPos(int iSearchDir)
{
    const auto it = helperGetNearestLinearIter(iSearchDir);
    if (it == linearDom()->end()) return 0;

    return linearDomSearch()->linearDom().endTagPos(it->thisPos());
}

std::vector<int> ScriptMiner::posChildren(int iDomPos)
{
    return posChildren("", iDomPos);
}

std::vector<int> ScriptMiner::posChildren(const std::string& tagName, int iDomPos)
{
    return linearDomSearch()->childPositions(iDomPos, tagName);
}

std::vector<int> ScriptMiner::posChildrenRecur(const std::string& tagName, int iDomPos)
{
    std::cerr << "ERROR TODO: Not implemented correctly - yet: ScriptMiner::nodeChildrenRecur()\n";
    return linearDomSearch()->childPositions(iDomPos, tagName);
}

int ScriptMiner::posEndElementPos(int iDomPos)
{
    return linearDomSearch()->linearDom().endTagPos(iDomPos);
}


// ----------------------
// --- Node functions ---
// ----------------------
//boost::shared_ptr<crawl::DomNodeIF>  ScriptMiner::helperGetNearestElement( int iSearchDir, std::string sElemType  )
//{
//    auto lds = linearDomSearch();
//    if (!lds) return boost::shared_ptr<crawl::DomNodeIF>();
//    boost::shared_ptr<crawl::DomNodeIF> pNode = lds->curElemPtr();
//    if ( !pNode )	return boost::shared_ptr<crawl::DomNodeIF>();
//    const auto iNodeType = pNode->nodeType();
//    if ( sElemType.empty() ) {
//        if ( iNodeType == DomNodeTypes::ELEMENT )	{
//            return pNode ;
//        }
//    }
//    else {
//        if ( iNodeType == DomNodeTypes::ELEMENT && pNode->stringDataUTF8() == sElemType ) {
//            return pNode ;
//        }
//    }

//    if ( iSearchDir >= NEAREST_PARENT ) {
//        if ( iNodeType & ( DomNodeTypes::ATTRIBUTE | DomNodeTypes::ATTRIBUTE_VALUE ) ) {
//            iSearchDir = NEAREST_BACKWARD;
//        }
//        else iSearchDir = NEAREST_BOTH;
//    }
//    crawl::LinearDomIF::const_iterator it1;
//    it1 = lds->seekNearestElement(sElemType, static_cast<crawl::ENearestDir>(iSearchDir) , 1 );
//    if ( it1 != linearDom()->end() ) {
//        return it1->node();
//    }
//    return boost::shared_ptr<crawl::DomNodeIF>();
//}

crawl::LinearDomIF::const_iterator ScriptMiner::helperGetNearestLinearIter(int iSearchDir, std::string sElemType)
{
    auto lds = linearDomSearch();
    if (!lds) return crawl::LinearDomIF::const_iterator();

    auto it = lds->itCurElem();
    if ( it == lds->end())	return it;
    const auto iNodeType = it->nodeType();
    if ( sElemType.empty() ) {
        if ( iNodeType == DomNodeTypes::ELEMENT )	{
            return it;
        }
    }
    else {
        if ( iNodeType == DomNodeTypes::ELEMENT && it->stringData() == sElemType ) {
            return it;
        }
    }

    if ( iSearchDir >= NEAREST_PARENT ) {
        if ( iNodeType & ( DomNodeTypes::ATTRIBUTE | DomNodeTypes::ATTRIBUTE_VALUE ) ) {
            iSearchDir = NEAREST_BACKWARD;
        }
        else iSearchDir = NEAREST_BOTH;
    }
    crawl::LinearDomIF::const_iterator it1;
    it1 = lds->seekNearestElement(sElemType, static_cast<crawl::ENearestDir>(iSearchDir) , 1 );
    if ( it1 != linearDom()->end() ) {
        return it1;
    }
    return lds->end();
}

int	ScriptMiner::nodeType ()
{
    if ( linearDomSearch()->curElemPtr() ) {
        return static_cast<int>(linearDomSearch()->curElemPtr()->nodeType()); // TODO: We should use uint32_t, but eventually we need to cast to a signed type since we want in PHP
    }
    else return 0;
}

bool ScriptMiner::nodeClickLoadHref	( int /*iSearchDir*/ )
{
    std::cerr << "TODO NOT IMPLEMENTED: nodeClickLoadHref()\n";
//    boost::shared_ptr<DomNodeIF> pNode = helperGetNearestElement( iSearchDir );
//    if ( !pNode ) return false;
//    const std::string sNodeName = pNode->nodeName();
//    bool bRetVal = pNode->click();
//    // For anchor elements we want to actually load the href URL!
//    if ( sNodeName == "A" ) {
//        if ( pNode->href() != "" ) {
//            bRetVal = urlLoad (pNode->hrefComplete());
//        }
//    }
//    else if ( sNodeName == "INPUT" || sNodeName == "BUTTON" ) {
//        const std::string sAttr = pNode->attributeGet("type");

//        // Is this a submit INPUT,BUTTON element ?, See: http://www.w3schools.com/tags/att_input_type.asp
//        if ( sAttr == "submit" || sAttr == "image" ) {
//            boost::shared_ptr<DomNodeIF> pNodeForm = helperGetNearestElement( crawl::NEAREST_PARENT, "FORM" );
//            if ( pNodeForm ) bRetVal = pNodeForm->formSubmit();
//        }
//        else if ( sAttr == "reset" ) {
//            boost::shared_ptr<DomNodeIF> pNodeForm = helperGetNearestElement( crawl::NEAREST_PARENT, "FORM" );
//            if ( pNodeForm ) bRetVal = pNodeForm->formReset();
//        }
//    }
//    else if ( sNodeName == "FORM" ) {
//        bRetVal = pNode->formSubmit();
//    }
//    return bRetVal;
    return false; // TODO
}

#if 0
bool ScriptMiner::nodeClick	(
    int iSearchDir
    )
{
    boost::shared_ptr<DomNodeIF> pNode = helperGetNearestElement( iSearchDir );
    if ( !pNode ) return false;
    auto&& fn =
            [=]() -> bool
    {
        const bool retval = pNode->click();
        return retval;
    };
    m_crawlerCommandQueue.push(std::move(fn));
    return true;
}
#else

bool ScriptMiner::nodeClick	(
    int iSearchDir
    )
{
    const auto it = helperGetNearestLinearIter(iSearchDir);
    if (it == linearDom()->end()) return false;
    auto&& fn =
            [=, this]() -> bool
    {
        const bool retval = this->webBrowser()->nodeClick(it->xpath().toString());
        return retval;
    };
    m_crawlerCommandQueue.push(std::move(fn));
    return true;
}

#endif

bool ScriptMiner::userClick	(
    int /*iSearchDir*/ )
{
    std::cerr << "TODO NOT IMPLEMENTED: userClick()\n";
//    boost::shared_ptr<DomNodeIF> pNode = helperGetNearestElement(iSearchDir);
//    if ( !pNode ) return false;
//    auto bo = pNode->getBoxObject();
//    if (!bo) return false;
//    const float x = bo->x() + bo->w() / 2.0f;
//    const float y = bo->y() + bo->h() / 2.0f;

//    browserMouseEvent(crawl::MOUSE_CLICK_EVENT, x, y, Qt::LeftButton, Qt::NoButton, Qt::NoModifier);
////    browserMouseEvent(QEvent::MouseButtonPress, x, y, Qt::LeftButton, Qt::NoButton, Qt::NoModifier);
////    browserMouseEvent(QEvent::MouseButtonRelease, x, y, Qt::LeftButton, Qt::NoButton, Qt::NoModifier);
//    return true;
    return false; // TODO
}

bool ScriptMiner::userMouseEvent(int /*eventType*/, int /*button*/, int /*buttons*/, int /*modifiers*/, int /*iSearchDir*/)
{
    std::cerr << "TODO NOT IMPLEMENTED: userMouseEvent()\n";
//    boost::shared_ptr<DomNodeIF> pNode = helperGetNearestElement(iSearchDir);
//    if ( !pNode ) return false;
//    auto bo = pNode->getBoxObject();
//    if (!bo) return false;
//    const float x = bo->x() + bo->w() / 2.0f;
//    const float y = bo->y() + bo->h() / 2.0f;
//    browserMouseEvent(eventType, x, y, button, buttons, modifiers);
//    return true;
    return false; // TODO
}


bool ScriptMiner::nodeClickWait	(int timeoutInMs ,
    int iSearchDir)
{
    bool bRetVal = nodeClick(iSearchDir);
    waitForDomReady(timeoutInMs);

//    // For anchor elements we want to actually load the href URL!
//    if ( bLoadHref && pNode->nodeName() == "A" ) {
//        if ( pNode->href() != "" ) {
//            bRetVal = urlLoad (pNode->href());
//        }
//    }
    return bRetVal;
}

bool ScriptMiner::nodeMouseEvent (
    const std::string& sEvent
    )
{
    return this->nodeMouseEvent(sEvent, crawl::NEAREST_AUTO );
}


bool ScriptMiner::nodeMouseEvent	(
    const std::string& sEvent,
    int iSearchDir )
{
    const boost::uint32_t 			iButton	= 0;	// Button ( left=0, middle/wheel=1, right=2 )
    return this->nodeMouseEvent(sEvent, iButton, iSearchDir );
}

bool ScriptMiner::nodeMouseEvent	(
     const std::string& /*sEvent*/
   , int /*iButton*/
   , int /*iSearchDir*/ )
{
    std::cerr << "TODO NOT IMPLEMENTED: nodeMouseEvent()\n";
//    const boost::int32_t 			iDetail = 0;	// Detail argument from W3C DOM spec.
//    boost::shared_ptr<DomNodeIF> pNode = helperGetNearestElement(iSearchDir);
//    if ( !pNode ) return false;
//    auto&& fn = [=]() -> bool {
//        return pNode->mouseEvent(sEvent, iDetail, static_cast<uint32_t>(iButton) );
//    };
//    m_crawlerCommandQueue.push(std::move(fn));
//    return true;
    return false; // TODO
}

bool ScriptMiner::nodeJavaScriptEvaluate ( const std::string& /*sJavaScript*/, int /*iSearchDir*/ )
{
    std::cerr << "TODO NOT IMPLEMENTED: nodeJavaScriptEvaluate()\n";
//    boost::shared_ptr<DomNodeIF> pNode = helperGetNearestElement(iSearchDir);
//    if ( !pNode ) return false;
//    auto&& fn = [=]() -> bool { return pNode->javaScriptEvaluate( sJavaScript );};
//    m_crawlerCommandQueue.push(std::move(fn));
    return false; // TODO
}


bool ScriptMiner::inputSet (
    const std::string& sValue,
    int iSearchDir )
{
    const auto it = helperGetNearestLinearIter(iSearchDir);
    if (it == linearDom()->end()) return false;
    auto&& fn =
            [=, this]() -> bool
    {
        const bool retval = this->webBrowser()->inputSet(it->xpath().toString(), sValue);
        return retval;
    };
    m_crawlerCommandQueue.push(std::move(fn));
    return true;
}

bool ScriptMiner::inputSet (
    int iValue,
    int iSearchDir )
{
    return inputSet( std::to_string( iValue ), iSearchDir);
    return false; // TODO
}

std::string ScriptMiner::innerHtml(int /*iSearchDir*/)
{
    std::cerr << "TODO NOT IMPLEMENTED: nodeJavaScriptEvaluate()\n";
//    boost::shared_ptr<DomNodeIF> pNode = helperGetNearestElement(iSearchDir);
//    if ( !pNode ) return "";
//    return pNode->innerHtml();
    return ""; // TODO
}

bool ScriptMiner::innerHtmlSet(const std::string& /*sValue*/, int /*iSearchDir*/)
{
    std::cerr << "TODO NOT IMPLEMENTED: innerHtmlSet()\n";
//    boost::shared_ptr<DomNodeIF> pNode = helperGetNearestElement(iSearchDir);
//    if ( !pNode ) return false;
//    auto&& fn = [=]() -> bool { return pNode->innerHtmlSet(sValue);};
//    m_crawlerCommandQueue.push(std::move(fn));
    return false; // TODO
}

std::string ScriptMiner::innerText(int /*iSearchDir*/)
{
    std::cerr << "TODO NOT IMPLEMENTED: nodeJavaScriptEvaluate()\n";
//    boost::shared_ptr<DomNodeIF> pNode = helperGetNearestElement(iSearchDir);
//    if ( !pNode ) return "";
//    return pNode->innerText();
    return ""; // TODO
}

bool ScriptMiner::innerTextSet(const std::string& /*sValue*/, int /*iSearchDir*/)
{
    std::cerr << "TODO NOT IMPLEMENTED: nodeJavaScriptEvaluate()\n";
//    boost::shared_ptr<DomNodeIF> pNode = helperGetNearestElement(iSearchDir);
//    if ( !pNode ) return false;
//    auto&& fn = [=]() -> bool { return pNode->innerTextSet(sValue);};
//    m_crawlerCommandQueue.push(std::move(fn));
    return false; // TODO
}

bool ScriptMiner::formSubmit (
    int /*iSearchDir*/ )
{
    std::cerr << "TODO NOT IMPLEMENTED: nodeJavaScriptEvaluate()\n";
//    boost::shared_ptr<DomNodeIF> pNode = helperGetNearestElement(iSearchDir, "FORM");
//    if ( !pNode ) return false;
//    auto&& fn = [=]() -> bool { return pNode->formSubmit();};
//    m_crawlerCommandQueue.push(std::move(fn));
    return false; // TODO
}


bool ScriptMiner::formReset (
    int /*iSearchDir*/ )
{
    std::cerr << "TODO NOT IMPLEMENTED: formReset()\n";
//    boost::shared_ptr<DomNodeIF> pNode = helperGetNearestElement(iSearchDir, "FORM");
//    if ( !pNode ) return false;
//    auto&& fn = [=]() -> bool { return pNode->formReset();};
//    m_crawlerCommandQueue.push(std::move(fn));
    return false; // TODO
}


int ScriptMiner::selectLength (
    int /*iSearchDir*/ )
{
    std::cerr << "TODO NOT IMPLEMENTED: selectLength()\n";
//    boost::shared_ptr<DomNodeIF> pNode = helperGetNearestElement(iSearchDir, "SELECT" );
//    if ( !pNode ) return 0;
//    return pNode->selectLengthGet();
    return 0; // TODO
}

int ScriptMiner::selectSelectedIndex (
    int /*iSearchDir*/
 )
{
    std::cerr << "TODO NOT IMPLEMENTED: selectSelectedIndex()\n";
//    boost::shared_ptr<DomNodeIF> pNode = helperGetNearestElement(iSearchDir, "SELECT" );
//    if ( !pNode ) return 0;
//    return pNode->selectedIndexGet();
    return 0; // TODO
}

std::string ScriptMiner::selectSelectedText (
    int /*iSearchDir*/
 )
{
    std::cerr << "TODO NOT IMPLEMENTED: selectSelectedText()\n";
//    boost::shared_ptr<DomNodeIF> pNode = helperGetNearestElement(iSearchDir, "SELECT" );
//    if ( !pNode ) return 0;
//    return pNode->selectTextGet();
    return ""; // TODO
}

std::string ScriptMiner::selectSelectedValue (
    int /*iSearchDir*/
 )
{
    std::cerr << "TODO NOT IMPLEMENTED: selectSelectedValue()\n";
//    boost::shared_ptr<DomNodeIF> pNode = helperGetNearestElement(iSearchDir, "SELECT" );
//    if ( !pNode ) return 0;
//    return pNode->selectValueGet();
    return ""; // TODO
}

int ScriptMiner::selectSelectedDomPos (
    int /*iSearchDir*/ )
{
    std::cerr << "TODO NOT IMPLEMENTED: nodeJavaScriptEvaluate()\n";
//    boost::shared_ptr<DomNodeIF> pNode = helperGetNearestElement(iSearchDir, "SELECT" );
//    if ( !pNode ) return 0;
//    return pNode->selectedDomPosGet();
    return 0; // TODO
}

/** Obsolete name for selectIndex. */
bool ScriptMiner::selectSelect (
    int iIndex,
    int iSearchDir )
{
    return this->selectIndex( iIndex, iSearchDir );
}

bool ScriptMiner::selectIndex (
    int /*iIndex*/,
    int /*iSearchDir*/ )
{
    std::cerr << "TODO NOT IMPLEMENTED: selectIndex()\n";
//    waitingForDomReadySet(true);
    bool res = true;
//    auto&& fn = [this, iIndex, iSearchDir, &res]() -> bool {
//        boost::shared_ptr<DomNodeIF> pNode = helperGetNearestElement(iSearchDir, "SELECT" );
//        if ( !pNode )
//            res = false;
//        else
//            res = pNode->selectIndex(iIndex);
//        waitingForDomReadySet(false);   // No new page load expected, so just mark DOM ready
//        return res; // TODO: Hmm a little weird this returning the same as res!
//    };
//    m_crawlerCommandQueue.push(std::move(fn));
//    waitForDomReady();

    return res;
}

bool ScriptMiner::selectIndexWait (int /*iIndex*/, int /*timeoutInMs*/, int /*iSearchDir*/)
{
    std::cerr << "TODO NOT IMPLEMENTED: selectIndexWait()\n";
//    waitingForDomReadySet(true);
    bool res = true;
//    auto&& fn = [this, iIndex, iSearchDir, &res]() -> bool {
//        boost::shared_ptr<DomNodeIF> pNode = helperGetNearestElement(iSearchDir, "SELECT" );
//        if ( !pNode )
//            res = false;
//        else
//            res = pNode->selectIndex(iIndex);
//        return res; // TODO: Hmm a little weird this returning the same as res!
//    };
//    m_crawlerCommandQueue.push(std::move(fn));
//    waitForDomReady(timeoutInMs); // Here we expect a page loaded or ajax completed
    return res;
}

bool ScriptMiner::selectOption (
    int /*iSearchDir*/
    )
{
    std::cerr << "TODO NOT IMPLEMENTED: selectOption()\n";
//    waitingForDomReadySet(true);
    bool res = true;
//    auto&& fn = [this, iSearchDir, &res]() -> bool {
//        boost::shared_ptr<DomNodeIF> pNode = helperGetNearestElement(iSearchDir, "OPTION" );
//        if (!pNode)
//            res = false;
//        else {
//            const int index = selectIndexOfOption(iSearchDir);
//            if (index > -1) {
//                auto parentSelect = pNode->optionOwnerSelectNodeGet();
//                if (parentSelect) {
//                    res = parentSelect->selectIndex(index);
//                }
//            }
//            else
//                res = false;
//        }
//        waitingForDomReadySet(false);   // No new page load expected, so just mark DOM ready
//        return res; // TODO: Hmm a little weird this returning the same as res!
//    };
//    m_crawlerCommandQueue.push(std::move(fn));
//    waitForDomReady();

    return res;
}


// TODO: Copy strategy from selectIndexWait
bool ScriptMiner::selectOptionWait (int /*timeoutInMs*/, int /*iSearchDir*/)
{
    std::cerr << "TODO NOT IMPLEMENTED: selectOptionWait()\n";
//    waitingForDomReadySet(true);
    bool res = true;
//    auto&& fn = [this, iSearchDir, &res]() -> bool {
//        boost::shared_ptr<DomNodeIF> pNode = helperGetNearestElement(iSearchDir, "OPTION" );
//        if (!pNode)
//            res = false;
//        else {
//            const int index = selectIndexOfOption(iSearchDir);
//            if (index > -1) {
//                auto parentSelect = pNode->optionOwnerSelectNodeGet();
//                if (parentSelect) {
//                    res = parentSelect->selectIndex(index);
//                }
//            }
//            else
//                res = false;
//        }
//        return res; // TODO: Hmm a little weird this returning the same as res!
//    };
//    m_crawlerCommandQueue.push(std::move(fn));
//    waitForDomReady(timeoutInMs); // Here we expect a page loaded or ajax completed

    return res;
}

int ScriptMiner::selectIndexOfOption (
    int /*iSearchDir*/
    )
{
    std::cerr << "TODO NOT IMPLEMENTED: selectIndexOfOption()\n";
//    boost::shared_ptr<DomNodeIF> pNode = helperGetNearestElement(iSearchDir, "OPTION" );
//    if ( !pNode ) return -1;
//    int iPosSave = domPos();

//    int optionIndex = -1;
//    auto val = nodeValue();
//    while (domPos() > 0 && val != "SELECT") {
//        if (val == "OPTION")
//            optionIndex++;
//        domStep(-1);
//        val = nodeValue();
//    }
//    val = nodeValue();
//    domPosSet(iPosSave);
//    if (val == "SELECT" && optionIndex > -1)
//        return optionIndex;
    return -1;
}

bool ScriptMiner::doActionSimple (
     const std::string& sAction		///< [in] name of named action to lookup, ID of action to perform or the name of a PHP function to execute
    ,const std::string& sParam1		///< [in] Parameter 1 to action, if applicable, can be set to empty string if not needed.
    ,const std::string& sParam2		///< [in] Parameter 2 to action, if applicable, can be set to empty string if not needed.
    ,int /*iSearchDir*/					///< [in] "Direction" to search for the node: NEAREST_FORWARD, NEAREST_BACKWARD, NEAREST_BOTH, NEAREST_PARENT , NEAREST_AUTO, NEAREST_THIS_NODE
    )
{
    using namespace crawl;
    ////boost::shared_ptr<DomNodeIF> pNode = helperGetNearestElement( iSearchDir, "" );  // TODO: Shold probably go away since done by abtion abstraction call
    boost::shared_ptr<DomActionAbstraction>	pDomAction = G_DomActionAbstractionLookUp::fromAlias ( sAction );
    if ( !pDomAction )	return false;

    return pDomAction->doActionBool( this, sParam1, sParam2 );
}

bool ScriptMiner::doAction (
      const std::string& sAction		///< [in] name of named action to lookup, ID of action to perform or the name of a PHP function to execute
    , const std::string& sParam1		///< [in] Parameter 1 to action, if applicable, can be set to empty string if not needed.
    , const std::string& sParam2		///< [in] Parameter 2 to action, if applicable, can be set to empty string if not needed.
    , int iSearchDir					///< [in] "Direction" to search for the node: NEAREST_FORWARD, NEAREST_BACKWARD, NEAREST_BOTH, NEAREST_PARENT , NEAREST_AUTO, NEAREST_THIS_NODE
    )
{
    using namespace crawl;
    bool bExecutedOk = true;
    // First try to se if there is a user defined PHP action function, and if so: call it
    if ( scriptFunctionExists(sAction) ) {
        bExecutedOk = scriptingClass()->callScriptFunction_Bool( sAction, sParam1, sParam2, std::to_string(iSearchDir) );
    }
    else if ( stateMachineMgr()->smCurrent()->hasNavAction(sAction) ) {
        bExecutedOk = navDoAction( sAction );
    }
    else {
        boost::shared_ptr<DomActionMgr::Action>	pAction = domActionMgr()->domActionGet( sAction );
        if ( pAction ) {
            if ( scriptFunctionExists( pAction->sAction ) ) {
                std::string retval = scriptingClass()->callScriptFunction_String( pAction->sAction, pAction->sParam1, pAction->sParam2, std::to_string(pAction->iSearchDir) );
                if ( retval == "false" ) bExecutedOk = false;
            }
            else {
                bExecutedOk = doActionSimple( pAction->sAction, pAction->sParam1, pAction->sParam2, pAction->iSearchDir );
            }
        }
        else {
            bExecutedOk = doActionSimple( sAction, sParam1, sParam2, iSearchDir );
        }
    }
    return bExecutedOk;
}

bool ScriptMiner::doAction (
     const std::string& sAction		///< [in] name of named action to lookup, ID of action to perform or the name of a PHP function to execute
    ,const std::string& sParam1		///< [in] Parameter 1 to action, if applicable, can be set to empty string if not needed.
    ,const std::string& sParam2		///< [in] Parameter 2 to action, if applicable, can be set to empty string if not needed.
    )
{
    return doAction ( sAction, sParam1, sParam2, NEAREST_AUTO );
}


bool ScriptMiner::doAction (
     const std::string& sAction		///< [in] name of named action to lookup, ID of action to perform or the name of a PHP function to execute
    ,const std::string& sParam1		///< [in] Parameter 1 to action, if applicable, can be set to empty string if not needed.
    ,int iSearchDir					///< [in] "Direction" to search for the node: NEAREST_FORWARD, NEAREST_BACKWARD, NEAREST_BOTH, NEAREST_PARENT , NEAREST_AUTO, NEAREST_THIS_NODE
    )
{
    return doAction ( sAction, sParam1, "", iSearchDir );
}


bool ScriptMiner::doAction (
     const std::string& sAction		///< [in] name of named action to lookup, ID of action to perform or the name of a PHP function to execute
    ,int iSearchDir					///< [in] "Direction" to search for the node: NEAREST_FORWARD, NEAREST_BACKWARD, NEAREST_BOTH, NEAREST_PARENT , NEAREST_AUTO, NEAREST_THIS_NODE
    )
{
    return doAction ( sAction, "", "", iSearchDir );
}

float ScriptMiner::nodeGeomPosX(int /*iSearchDir*/)
{
    std::cerr << "TODO NOT IMPLEMENTED: nodeGeomPosX()\n";
//    boost::shared_ptr<DomNodeIF> pNode = helperGetNearestElement(iSearchDir, "SELECT" );
//    if ( !pNode ) return -1;
//    return pNode->getBoxObject()->x();
    return 0; // TODO
}

float ScriptMiner::nodeGeomPosY(int /*iSearchDir*/)
{
    std::cerr << "TODO NOT IMPLEMENTED: nodeGeomPosY()\n";
//    boost::shared_ptr<DomNodeIF> pNode = helperGetNearestElement(iSearchDir, "SELECT" );
//    if ( !pNode ) return -1;
//    return pNode->getBoxObject()->y();
    return 0; // TODO
}

float ScriptMiner::nodeGeomWidth(int /*iSearchDir*/)
{
    std::cerr << "TODO NOT IMPLEMENTED: nodeGeomWidth()\n";
//    boost::shared_ptr<DomNodeIF> pNode = helperGetNearestElement(iSearchDir, "SELECT" );
//    if ( !pNode ) return -1;
//    return pNode->getBoxObject()->w();
    return 0; // TODO
}

float ScriptMiner::nodeGeomHeight(int /*iSearchDir*/)
{
    std::cerr << "TODO NOT IMPLEMENTED: nodeGeomHeight()\n";
//    boost::shared_ptr<DomNodeIF> pNode = helperGetNearestElement(iSearchDir, "SELECT" );
//    if ( !pNode ) return -1;
//    return pNode->getBoxObject()->h();
    return 0; // TODO
}


/*
----------------------------------------
--- DOM doActionFind(Next) functions ---
---------------------------------------- */
int	ScriptMiner::doActionFindNextImpl(
     int iCount 								///< [in] Stop at match number iCount (use negative numbers for backwards search).
    ,const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sAction					///< [in] name of named action to lookup, ID of action to perform or the name of a PHP function to execute
    ,const std::string& sParam1					///< [in] Parameter 1 to action, if applicable, can be set to empty string if not needed.
    ,const std::string& sParam2					///< [in] Parameter 2 to action, if applicable, can be set to empty string if not needed.
    ,int iSearchDir								///< [in] "Direction" to search for the node: NEAREST_FORWARD, NEAREST_BACKWARD, NEAREST_BOTH, NEAREST_PARENT , NEAREST_AUTO, NEAREST_THIS_NODE
    ,bool bUpdateDomPos							///< [in] Do update dom position to found position.
    )
{
    int iPosSave = 0;
    if ( !bUpdateDomPos )
        iPosSave = domPos();
    int iDomPos = domFindNext( iCount, sSequence );

    // Fire action only if dompos was found or if navigator has an action of this name that does not need a dom position
    boost::shared_ptr<NavigateStateBase> action = stateMachineMgr()->smCurrent()->actionPtrGet(sAction);
    if ( iDomPos || (action && !action->needValidDomPosToExecute())) {
        if ( !doAction ( sAction, sParam1, sParam2, iSearchDir ) )
            iDomPos = 0;
    }
    if ( !bUpdateDomPos )
        domPosSet(iPosSave);
    return iDomPos;
}

/*
--------------------------------------
--- DOM doActionFindNext functions ---
-------------------------------------- */

int		ScriptMiner::doActionFindNext(
     int iCount 								///< [in] Stop at match number iCount (use negative numbers for backwards search).
    ,const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sAction					///< [in] name of named action to lookup, ID of action to perform or the name of a PHP function to execute
    ,const std::string& sParam1					///< [in] Parameter 1 to action, if applicable, can be set to empty string if not needed.
    ,const std::string& sParam2					///< [in] Parameter 2 to action, if applicable, can be set to empty string if not needed.
    ,int iSearchDir								///< [in] "Direction" to search for the node: NEAREST_FORWARD, NEAREST_BACKWARD, NEAREST_BOTH, NEAREST_PARENT , NEAREST_AUTO, NEAREST_THIS_NODE
    )
{
    return doActionFindNextImpl ( iCount, sSequence, sAction, sParam1, sParam2, iSearchDir, false );
}

int		ScriptMiner::doActionFindNext (
     int iCount 								///< [in] Stop at match number iCount (use negative numbers for backwards search).
    ,const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sAction					///< [in] name of named action to lookup, ID of action to perform or the name of a PHP function to execute
    ,const std::string& sParam1					///< [in] Parameter 1 to action, if applicable, can be set to empty string if not needed.
    ,const std::string& sParam2					///< [in] Parameter 2 to action, if applicable, can be set to empty string if not needed.
    )
{
    return doActionFindNext ( iCount, sSequence, sAction, sParam1, sParam2, NEAREST_AUTO );
}

int		ScriptMiner::doActionFindNext (
     int iCount 								///< [in] Stop at match number iCount (use negative numbers for backwards search).
    ,const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sAction					///< [in] name of named action to lookup, ID of action to perform or the name of a PHP function to execute
    ,const std::string& sParam1					///< [in] Parameter 1 to action, if applicable, can be set to empty string if not needed.
    ,int iSearchDir								///< [in] "Direction" to search for the node: NEAREST_FORWARD, NEAREST_BACKWARD, NEAREST_BOTH, NEAREST_PARENT , NEAREST_AUTO, NEAREST_THIS_NODE
    )
{
    return doActionFindNext ( iCount, sSequence, sAction, sParam1, "", iSearchDir );
}

int		ScriptMiner::doActionFindNext (
     int iCount 								///< [in] Stop at match number iCount (use negative numbers for backwards search).
    ,const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sAction					///< [in] name of named action to lookup, ID of action to perform or the name of a PHP function to execute
    ,int iSearchDir								///< [in] "Direction" to search for the node: NEAREST_FORWARD, NEAREST_BACKWARD, NEAREST_BOTH, NEAREST_PARENT , NEAREST_AUTO, NEAREST_THIS_NODE
    )
{
    return doActionFindNext ( iCount, sSequence, sAction, "", "", iSearchDir );
}

int		ScriptMiner::doActionFindNext(
     const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sAction					///< [in] name of named action to lookup, ID of action to perform or the name of a PHP function to execute
    ,const std::string& sParam1					///< [in] Parameter 1 to action, if applicable, can be set to empty string if not needed.
    ,const std::string& sParam2					///< [in] Parameter 2 to action, if applicable, can be set to empty string if not needed.
    ,int iSearchDir								///< [in] "Direction" to search for the node: NEAREST_FORWARD, NEAREST_BACKWARD, NEAREST_BOTH, NEAREST_PARENT , NEAREST_AUTO, NEAREST_THIS_NODE
    )
{
    return doActionFindNext ( 1, sSequence, sAction, sParam1, sParam2, iSearchDir );
}

int		ScriptMiner::doActionFindNext (
     const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sAction					///< [in] name of named action to lookup, ID of action to perform or the name of a PHP function to execute
    ,const std::string& sParam1					///< [in] Parameter 1 to action, if applicable, can be set to empty string if not needed.
    ,const std::string& sParam2					///< [in] Parameter 2 to action, if applicable, can be set to empty string if not needed.
    )
{
    return doActionFindNext ( sSequence, sAction, sParam1, sParam2, NEAREST_AUTO );
}

int		ScriptMiner::doActionFindNext (
     const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sAction					///< [in] name of named action to lookup, ID of action to perform or the name of a PHP function to execute
    ,const std::string& sParam1					///< [in] Parameter 1 to action, if applicable, can be set to empty string if not needed.
    ,int iSearchDir								///< [in] "Direction" to search for the node: NEAREST_FORWARD, NEAREST_BACKWARD, NEAREST_BOTH, NEAREST_PARENT , NEAREST_AUTO, NEAREST_THIS_NODE
    )
{
    return doActionFindNext ( sSequence, sAction, sParam1, "", iSearchDir );
}

int		ScriptMiner::doActionFindNext (
     const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sAction					///< [in] name of named action to lookup, ID of action to perform or the name of a PHP function to execute
    ,int iSearchDir								///< [in] "Direction" to search for the node: NEAREST_FORWARD, NEAREST_BACKWARD, NEAREST_BOTH, NEAREST_PARENT , NEAREST_AUTO, NEAREST_THIS_NODE
    )
{
    return doActionFindNext ( sSequence, sAction, "", "", iSearchDir );
}


/*
----------------------------------
--- DOM doActionFind functions ---
---------------------------------- */
int		ScriptMiner::doActionFind(
     int iCount 								///< [in] Stop at match number iCount (use negative numbers for backwards search).
    ,const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sAction					///< [in] name of named action to lookup, ID of action to perform or the name of a PHP function to execute
    ,const std::string& sParam1					///< [in] Parameter 1 to action, if applicable, can be set to empty string if not needed.
    ,const std::string& sParam2					///< [in] Parameter 2 to action, if applicable, can be set to empty string if not needed.
    ,int iSearchDir								///< [in] "Direction" to search for the node: NEAREST_FORWARD, NEAREST_BACKWARD, NEAREST_BOTH, NEAREST_PARENT , NEAREST_AUTO, NEAREST_THIS_NODE
    )
{
    domNewSearch();
    return doActionFindNext ( iCount, sSequence, sAction, sParam1, sParam2, iSearchDir );
}

int		ScriptMiner::doActionFind(
     int iCount 								///< [in] Stop at match number iCount (use negative numbers for backwards search).
    ,const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sAction					///< [in] name of named action to lookup, ID of action to perform or the name of a PHP function to execute
    ,const std::string& sParam1					///< [in] Parameter 1 to action, if applicable, can be set to empty string if not needed.
    ,const std::string& sParam2					///< [in] Parameter 2 to action, if applicable, can be set to empty string if not needed.
    )
{
    return doActionFind ( iCount, sSequence, sAction, sParam1, sParam2, NEAREST_AUTO );
}

int		ScriptMiner::doActionFind(
     int iCount 								///< [in] Stop at match number iCount (use negative numbers for backwards search).
    ,const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sAction					///< [in] name of named action to lookup, ID of action to perform or the name of a PHP function to execute
    ,const std::string& sParam1					///< [in] Parameter 1 to action, if applicable, can be set to empty string if not needed.
    ,int iSearchDir								///< [in] "Direction" to search for the node: NEAREST_FORWARD, NEAREST_BACKWARD, NEAREST_BOTH, NEAREST_PARENT , NEAREST_AUTO, NEAREST_THIS_NODE
    )
{
    return doActionFind ( iCount, sSequence, sAction, sParam1, "", iSearchDir );
}

int		ScriptMiner::doActionFind(
     int iCount 								///< [in] Stop at match number iCount (use negative numbers for backwards search).
    ,const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sAction					///< [in] name of named action to lookup, ID of action to perform or the name of a PHP function to execute
    ,int iSearchDir								///< [in] "Direction" to search for the node: NEAREST_FORWARD, NEAREST_BACKWARD, NEAREST_BOTH, NEAREST_PARENT , NEAREST_AUTO, NEAREST_THIS_NODE
    )
{
    return doActionFind ( iCount, sSequence, sAction, "", "", iSearchDir );
}

int		ScriptMiner::doActionFind(
     const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sAction					///< [in] name of named action to lookup, ID of action to perform or the name of a PHP function to execute
    ,const std::string& sParam1					///< [in] Parameter 1 to action, if applicable, can be set to empty string if not needed.
    ,const std::string& sParam2					///< [in] Parameter 2 to action, if applicable, can be set to empty string if not needed.
    ,int iSearchDir								///< [in] "Direction" to search for the node: NEAREST_FORWARD, NEAREST_BACKWARD, NEAREST_BOTH, NEAREST_PARENT , NEAREST_AUTO, NEAREST_THIS_NODE
    )
{
    return doActionFind ( 1, sSequence, sAction, sParam1, sParam2, iSearchDir );
}

int		ScriptMiner::doActionFind(
     const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sAction					///< [in] name of named action to lookup, ID of action to perform or the name of a PHP function to execute
    ,const std::string& sParam1					///< [in] Parameter 1 to action, if applicable, can be set to empty string if not needed.
    ,const std::string& sParam2					///< [in] Parameter 2 to action, if applicable, can be set to empty string if not needed.
    )
{
    return doActionFind ( sSequence, sAction, sParam1, sParam2, NEAREST_AUTO );
}

int		ScriptMiner::doActionFind(
     const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sAction					///< [in] name of named action to lookup, ID of action to perform or the name of a PHP function to execute
    ,const std::string& sParam1					///< [in] Parameter 1 to action, if applicable, can be set to empty string if not needed.
    ,int iSearchDir								///< [in] "Direction" to search for the node: NEAREST_FORWARD, NEAREST_BACKWARD, NEAREST_BOTH, NEAREST_PARENT , NEAREST_AUTO, NEAREST_THIS_NODE
    )
{
    return doActionFind ( sSequence, sAction, sParam1, "", iSearchDir );
}

int		ScriptMiner::doActionFind(
     const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sAction					///< [in] name of named action to lookup, ID of action to perform or the name of a PHP function to execute
    ,int iSearchDir								///< [in] "Direction" to search for the node: NEAREST_FORWARD, NEAREST_BACKWARD, NEAREST_BOTH, NEAREST_PARENT , NEAREST_AUTO, NEAREST_THIS_NODE
    )
{
    return doActionFind ( sSequence, sAction, "", "", iSearchDir );
}

/*
-----------------------------------
--- DOM Action create functions ---
----------------------------------- */

void ScriptMiner::domActionCreate (
      const std::string& sName          ///< [in] Name of the named action we are creating (e.g. 'MyClickNextBtnAction' )
    , const std::string& sAction		///< [in] (String) ID of action to perform
    , const std::string& sParam1		///< [in] Parameter 1 to action, if applicable, can be set to empty string if not needed.
    , const std::string& sParam2		///< [in] Parameter 2 to action, if applicable, can be set to empty string if not needed.
    , int iSearchDir					///< [in] "Direction" to search for the node: NEAREST_FORWARD, NEAREST_BACKWARD, NEAREST_BOTH, NEAREST_PARENT , NEAREST_AUTO, NEAREST_THIS_NODE
    )
{
    domActionMgr()->domActionAdd( sName, sAction, sParam1, sParam2, iSearchDir );
}

void ScriptMiner::domActionCreate (
      const std::string& sName          ///< [in] Name of the named action we are creating (e.g. 'MyClickNextBtnAction' )
    , const std::string& sAction		///< [in] (String) ID of action to perform
    , const std::string& sParam1		///< [in] Parameter 1 to action, if applicable, can be set to empty string if not needed.
    , const std::string& sParam2		///< [in] Parameter 2 to action, if applicable, can be set to empty string if not needed.
    )
{
    domActionMgr()->domActionAdd( sName, sAction, sParam1, sParam2, NEAREST_AUTO );
}

void ScriptMiner::domActionCreate (
      const std::string& sName          ///< [in] Name of the named action we are creating (e.g. 'MyClickNextBtnAction' )
    , const std::string& sAction		///< [in] (String) ID of action to perform
    , const std::string& sParam1		///< [in] Parameter 1 to action, if applicable, can be set to empty string if not needed.
    , int iSearchDir					///< [in] "Direction" to search for the node: NEAREST_FORWARD, NEAREST_BACKWARD, NEAREST_BOTH, NEAREST_PARENT , NEAREST_AUTO, NEAREST_THIS_NODE
    )
{
    domActionMgr()->domActionAdd( sName, sAction, sParam1, "", iSearchDir );
}

void ScriptMiner::domActionCreate (
      const std::string& sName          ///< [in] Name of the named action we are creating (e.g. 'MyClickNextBtnAction' )
    , const std::string& sAction		///< [in] (String) ID of action to perform
    , int iSearchDir					///< [in] "Direction" to search for the node: NEAREST_FORWARD, NEAREST_BACKWARD, NEAREST_BOTH, NEAREST_PARENT , NEAREST_AUTO, NEAREST_THIS_NODE
    )
{
    domActionMgr()->domActionAdd( sName, sAction, "", "", iSearchDir );
}

/*
--------------------------------------------------------------------
--- Modifier create functions (OutputModifier create functions)  ---
-------------------------------------------------------------------- */
void ScriptMiner::modifierCreate	(
      const std::string& sModifierID						///< [in] Name to use for new modifier.
    , const std::string& sManipFunID						///< [in] ID of built-in string modifier/manipulation function. E.g. 'append', 'replaceAll', ...
    , const std::string& sManipParam1						///< [in] Parameter 1 to modifier function.
    , const std::string& sManipParam2 						///< [in] Parameter 2 to modifier function.
    , const std::string& sManipParam3						///< [in] Parameter 3 to modifier function.
    , const std::string& /* sManipParam4 reserved */		///< [in] Parameter 4 to modifier function.
)
{
    modifierMgr()->modifierAdd( sModifierID, sManipFunID, sManipParam1, sManipParam2, sManipParam3, "" );
}

void ScriptMiner::modifierCreate	(
      const std::string& sModifierID						///< [in] Name to use for new modifier.
    , const std::string& sManipFunID						///< [in] ID of built-in string modifier/manipulation function. E.g. 'append', 'replaceAll', ...
    , const std::string& sManipParam1						///< [in] Parameter 1 to modifier function.
    , const std::string& sManipParam2 						///< [in] Parameter 2 to modifier function.
    , const std::string& sManipParam3						///< [in] Parameter 3 to modifier function.
)
{
    modifierMgr()->modifierAdd( sModifierID, sManipFunID, sManipParam1, sManipParam2, sManipParam3, "" );
}

void ScriptMiner::modifierCreate	(
      const std::string& sModifierID						///< [in] Name to use for new modifier.
    , const std::string& sManipFunID						///< [in] ID of built-in string modifier/manipulation function. E.g. 'append', 'replaceAll', ...
    , const std::string& sManipParam1						///< [in] Parameter 1 to modifier function.
    , const std::string& sManipParam2 						///< [in] Parameter 2 to modifier function.
)
{
    modifierMgr()->modifierAdd( sModifierID, sManipFunID, sManipParam1, sManipParam2, "", "" );
}

void ScriptMiner::modifierCreate	(
      const std::string& sModifierID						///< [in] Name to use for new modifier.
    , const std::string& sManipFunID						///< [in] ID of built-in string modifier/manipulation function. E.g. 'append', 'replaceAll', ...
    , const std::string& sManipParam1						///< [in] Parameter 1 to modifier function.
)
{
    modifierMgr()->modifierAdd( sModifierID, sManipFunID, sManipParam1, "", "", "" );
}

void ScriptMiner::modifierCreate	(
      const std::string& sModifierID						///< [in] Name to use for new modifier.
    , const std::string& sManipFunID						///< [in] ID of built-in string modifier/manipulation function. E.g. 'append', 'replaceAll', ...
)
{
    modifierMgr()->modifierAdd( sModifierID, sManipFunID, "", "", "", "" );
}

/*
-----------------------------
--- nodeXX misc functions ---
----------------------------- */

int ScriptMiner::nodeLevel()
{
    if ( !linearDomSearch()->curElemPtr() ) return -1;
    return linearDomSearch()->curElemPtr()->depthLevelGet();
}

std::string ScriptMiner::nodeXPath()
{
    auto xp = linearDomSearch()->curElem().xpath();
    return xp.toString();
}

/*
------------------------------
--- nodeValuePos functions ---
------------------------------ */
std::string	ScriptMiner::nodeValuePos (
      int iDomPos
    , const std::string& sModifierID							///< [in] String manipulation function/ to apply to value before writing out.
    , const std::string& sManipParam1							///< [in] Parameter 1 to modifier function.
    , const std::string& sManipParam2 							///< [in] Parameter 2 to modifier function.
    , const std::string& sManipParam3							///< [in] Parameter 3 to modifier function.
    , const std::string& /* sManipParam4 reserved */			///< [in] Parameter 4 to modifier function.
)
{
    std::string sVal("");

    // Get value from requested dom position
    const auto& linearDom = linearDomSearch()->linearDom();
    if ( 0 < iDomPos && iDomPos <= linearDom.size()) {
        sVal = linearDom[iDomPos].stringData();
    }
    return manipulateValueHelper( sVal, true, sModifierID, sManipParam1, sManipParam2, sManipParam3, "" );
}

std::string	ScriptMiner::nodeValuePos (
      int iDomPos
    , const std::string& sModifierID								///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    , const std::string& sManipParam1								///< [in] Parameter 1 to modifier function.
    , const std::string& sManipParam2 								///< [in] Parameter 2 to modifier function.
    , const std::string& sManipParam3								///< [in] Parameter 3 to modifier function.
)
{
    return nodeValuePos( iDomPos, sModifierID, sManipParam1, sManipParam2, sManipParam3, "" );
}

std::string	ScriptMiner::nodeValuePos (
      int iDomPos
    , const std::string& sModifierID								///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    , const std::string& sManipParam1								///< [in] Parameter 1 to modifier function.
    , const std::string& sManipParam2 								///< [in] Parameter 2 to modifier function.
)
{
    return nodeValuePos( iDomPos, sModifierID, sManipParam1, sManipParam2, "", "" );
}

std::string	ScriptMiner::nodeValuePos (
      int iDomPos
    , const std::string& sModifierID								///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    , const std::string& sManipParam1								///< [in] Parameter 1 to modifier function.
)
{
    return nodeValuePos( iDomPos, sModifierID, sManipParam1, "", "", "" );
}

std::string	ScriptMiner::nodeValuePos (
      int iDomPos
    , const std::string& sModifierID									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
)
{
    return nodeValuePos( iDomPos, sModifierID, "", "", "", "" );
}

std::string	ScriptMiner::nodeValuePos (
     int iDomPos
)
{
    return nodeValuePos( iDomPos, "", "", "", "", "" );
}


/*
---------------------------
--- nodeValue functions ---
--------------------------- */
std::string	ScriptMiner::nodeValue (
      const std::string& sModifierID									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    , const std::string& sManipParam1								///< [in] Parameter 1 to modifier function.
    , const std::string& sManipParam2 								///< [in] Parameter 2 to modifier function.
    , const std::string& sManipParam3								///< [in] Parameter 3 to modifier function.
    , const std::string& /* sManipParam4 reserved */					///< [in] Parameter 4 to modifier function.
)
{
    const auto& val = linearDomSearch()->curElem().stringData();
    return manipulateValueHelper( val, true, sModifierID, sManipParam1, sManipParam2, sManipParam3, "" );
}

std::string	ScriptMiner::nodeValue (
      const std::string& sModifierID									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    , const std::string& sManipParam1								///< [in] Parameter 1 to modifier function.
    , const std::string& sManipParam2 								///< [in] Parameter 2 to modifier function.
    , const std::string& sManipParam3								///< [in] Parameter 3 to modifier function.
)
{
    return nodeValue( sModifierID, sManipParam1, sManipParam2, sManipParam3, "" );
}


/** Get the value of the node at current dom position.
The value extracted from current node position can optionally be filtered through \a sModifierID + parameters.
\return Value of current node possibly filtered through \a sModifierID + parameters. */
std::string	ScriptMiner::nodeValue (
      const std::string& sModifierID									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    , const std::string& sManipParam1								///< [in] Parameter 1 to modifier function.
    , const std::string& sManipParam2 								///< [in] Parameter 2 to modifier function.
)
{
    return nodeValue( sModifierID, sManipParam1, sManipParam2, "", "" );
}

/** Get the value of the node at current dom position.
The value extracted from current node position can optionally be filtered through \a sModifierID + parameter.
\return Value of current node possibly filtered through \a sModifierID + parameter. */
std::string	ScriptMiner::nodeValue (
      const std::string& sModifierID									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    , const std::string& sManipParam1								///< [in] Parameter 1 to modifier function.
)
{
    return nodeValue( sModifierID, sManipParam1, "", "", "" );
}

/** Get the value of the node at current dom position.
The value extracted from current node position can optionally be filtered through \a sModifierID.
\return Value of current node possibly filtered through \a sModifierID. */
std::string	ScriptMiner::nodeValue (
     const std::string& sModifierID									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
)
{
    return nodeValue( sModifierID, "", "", "", "" );
}

/** Get the value of the node at current dom position.
The value extracted from current node position filtered through trimDefault.
\return Value of current node filtered through trimDefault. */
std::string	ScriptMiner::nodeValue (
)
{
    return nodeValue( "", "", "", "", "" );
}

std::string ScriptMiner::posValue(int iDomPos, const std::string& sModifierID, const std::string& sManipParam1,
                                  const std::string& sManipParam2, const std::string& sManipParam3,
                                  const std::string& sManipParam4)
{
    std::string sVal("");

    // Get value from requested dom position
    const auto& linearDom = linearDomSearch()->linearDom();
    if ( 0 < iDomPos && iDomPos <= linearDom.size()) {
        sVal = linearDom[iDomPos].stringData();
    }
    return manipulateValueHelper( sVal, true, sModifierID, sManipParam1, sManipParam2, sManipParam3, sManipParam4 );

}

std::string ScriptMiner::posValue(int iDomPos, const std::string& sModifierID, const std::string& sManipParam1,
                                  const std::string& sManipParam2, const std::string& sManipParam3)
{
    return posValue( iDomPos, sModifierID, sManipParam1, sManipParam2, sManipParam3, "" );
}

std::string ScriptMiner::posValue(int iDomPos, const std::string& sModifierID, const std::string& sManipParam1,
                                  const std::string& sManipParam2)
{
    return posValue( iDomPos, sModifierID, sManipParam1, sManipParam2, "", "" );
}

std::string ScriptMiner::posValue(int iDomPos, const std::string& sModifierID, const std::string& sManipParam1)
{
    return posValue( iDomPos, sModifierID, sManipParam1, "", "", "" );
}

std::string ScriptMiner::posValue(int iDomPos, const std::string& sModifierID)
{
    return posValue( iDomPos, sModifierID, "", "", "", "" );
}

std::string ScriptMiner::posValue(int iDomPos)
{
    return posValue( iDomPos, "", "", "", "", ""  );
}


/*
---------------------------------
--- nodeValueParent functions ---
--------------------------------- */
std::string	ScriptMiner::nodeValueParent (
      int iLevelsUp 									///< [in] Stop at parent number iLevelsUp (ONLY positive numbers).
    , const std::string& sModifierID					///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    , const std::string& sManipParam1					///< [in] Parameter 1 to modifier function.
    , const std::string& sManipParam2 					///< [in] Parameter 2 to modifier function.
    , const std::string& sManipParam3					///< [in] Parameter 3 to modifier function.
    , const std::string& /* sManipParam4 reserved */	///< [in] Parameter 4 to modifier function.
)
{
    std::string val("");
    auto pos = domParentPos(iLevelsUp);
    if (pos) {
        val = nodeValuePos(pos);
    }
    return manipulateValueHelper( val, true, sModifierID, sManipParam1, sManipParam2, sManipParam3, "" );
}

std::string	ScriptMiner::nodeValueParent (
      int iLevelsUp 												///< [in] Stop at parent number iLevelsUp (ONLY positive numbers).
    , const std::string& sModifierID								///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    , const std::string& sManipParam1								///< [in] Parameter 1 to modifier function.
    , const std::string& sManipParam2 								///< [in] Parameter 2 to modifier function.
    , const std::string& sManipParam3								///< [in] Parameter 3 to modifier function.
)
{
    return nodeValueParent( iLevelsUp, sModifierID, sManipParam1, sManipParam2, sManipParam3, "" );
}

std::string	ScriptMiner::nodeValueParent (
      int iLevelsUp 												///< [in] Stop at parent number iLevelsUp (ONLY positive numbers).
    , const std::string& sModifierID								///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    , const std::string& sManipParam1								///< [in] Parameter 1 to modifier function.
    , const std::string& sManipParam2 								///< [in] Parameter 2 to modifier function.
)
{
    return nodeValueParent( iLevelsUp, sModifierID, sManipParam1, sManipParam2, "", "" );
}

std::string	ScriptMiner::nodeValueParent (
      int iLevelsUp 												///< [in] Stop at parent number iLevelsUp (ONLY positive numbers).
    , const std::string& sModifierID								///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    , const std::string& sManipParam1								///< [in] Parameter 1 to modifier function.
)
{
    return nodeValueParent( iLevelsUp, sModifierID, sManipParam1, "", "", "" );
}

std::string	ScriptMiner::nodeValueParent (
      int iLevelsUp 													///< [in] Stop at parent number iLevelsUp (ONLY positive numbers).
    , const std::string& sModifierID									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
)
{
    return nodeValueParent( iLevelsUp, sModifierID, "", "", "", "" );
}

std::string	ScriptMiner::nodeValueParent (
     int iLevelsUp 													///< [in] Stop at parent number iLevelsUp (ONLY positive numbers).
)
{
    return nodeValueParent( iLevelsUp, "", "", "", "", "" );
}

/*
---------------------------------
--- nodeAttribute functions ---
--------------------------------- */
std::string	ScriptMiner::nodeAttribute (
      const std::string& sAttribute 					///< [in] Attribute name to get the value for.
    , const std::string& sModifierID					///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    , const std::string& sManipParam1					///< [in] Parameter 1 to modifier function.
    , const std::string& sManipParam2 					///< [in] Parameter 2 to modifier function.
    , const std::string& sManipParam3					///< [in] Parameter 3 to modifier function.
    , const std::string& /* sManipParam4 reserved */	///< [in] Parameter 4 to modifier function.
)
{
    std::string sVal = linearDomSearch()->linearDom().attribute(domPos(), sAttribute, "");
    return manipulateValueHelper( sVal, true, sModifierID, sManipParam1, sManipParam2, sManipParam3, "" );
}

std::string	ScriptMiner::nodeAttribute (
      const std::string& sAttribute 								///< [in] Attribute name to get the value for.
    , const std::string& sModifierID								///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    , const std::string& sManipParam1								///< [in] Parameter 1 to modifier function.
    , const std::string& sManipParam2 								///< [in] Parameter 2 to modifier function.
    , const std::string& sManipParam3								///< [in] Parameter 3 to modifier function.
)
{
    return nodeAttribute( sAttribute, sModifierID, sManipParam1, sManipParam2, sManipParam3, "" );
}

std::string	ScriptMiner::nodeAttribute (
      const std::string& sAttribute 								///< [in] Attribute name to get the value for.
    , const std::string& sModifierID								///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    , const std::string& sManipParam1								///< [in] Parameter 1 to modifier function.
    , const std::string& sManipParam2 								///< [in] Parameter 2 to modifier function.
)
{
    return nodeAttribute( sAttribute, sModifierID, sManipParam1, sManipParam2, "", "" );
}

std::string	ScriptMiner::nodeAttribute (
      const std::string& sAttribute 								///< [in] Attribute name to get the value for.
    , const std::string& sModifierID								///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    , const std::string& sManipParam1								///< [in] Parameter 1 to modifier function.
)
{
    return nodeAttribute( sAttribute, sModifierID, sManipParam1, "", "", "" );
}

std::string	ScriptMiner::nodeAttribute (
      const std::string& sAttribute 								///< [in] Attribute name to get the value for.
    , const std::string& sModifierID								///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
)
{
    return nodeAttribute( sAttribute, sModifierID, "", "", "", "" );
}

std::string	ScriptMiner::nodeAttribute (
     const std::string& sAttribute 									///< [in] Attribute name to get the value for.
)
{
    return nodeAttribute( sAttribute, "", "", "", "", "" );
}

std::string ScriptMiner::posAttribute(int iDomPos, const std::string& sAttribute, const std::string& sModifierID,
                                      const std::string& sManipParam1, const std::string& sManipParam2,
                                      const std::string& sManipParam3, const std::string& sManipParam4)
{
    std::string sVal = linearDomSearch()->linearDom().attribute(iDomPos, sAttribute, "");
    return manipulateValueHelper( sVal, true, sModifierID, sManipParam1, sManipParam2, sManipParam3, sManipParam4 );
}

std::string ScriptMiner::posAttribute(int iDomPos, const std::string& sAttribute, const std::string& sModifierID,
                                      const std::string& sManipParam1, const std::string& sManipParam2,
                                      const std::string& sManipParam3)
{
    return posAttribute( iDomPos, sAttribute, sModifierID, sManipParam1, sManipParam2, sManipParam3, "" );
}

std::string ScriptMiner::posAttribute(int iDomPos, const std::string& sAttribute, const std::string& sModifierID,
                                      const std::string& sManipParam1, const std::string& sManipParam2)
{
    return posAttribute( iDomPos, sAttribute, sModifierID, sManipParam1, sManipParam2, "", "" );
}

std::string ScriptMiner::posAttribute(int iDomPos, const std::string& sAttribute, const std::string& sModifierID,
                                      const std::string& sManipParam1)
{
    return posAttribute( iDomPos, sAttribute, sModifierID, sManipParam1, "", "", "" );
}

std::string ScriptMiner::posAttribute(int iDomPos, const std::string& sAttribute, const std::string& sModifierID)
{
    return posAttribute( iDomPos, sAttribute, sModifierID, "", "", "", "" );
}

std::string ScriptMiner::posAttribute(int iDomPos, const std::string& sAttribute)
{
    return posAttribute( iDomPos, sAttribute, "", "", "", "", "" );
}


/*
---------------------------------
--- nodeText functions ---
--------------------------------- */
std::string	ScriptMiner::nodeText (
      const std::string& /*sModifierID*/								///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    , const std::string& /*sManipParam1*/								///< [in] Parameter 1 to modifier function.
    , const std::string& /*sManipParam2*/ 								///< [in] Parameter 2 to modifier function.
    , const std::string& /*sManipParam3*/								///< [in] Parameter 3 to modifier function.
    , const std::string& /* sManipParam4 reserved */					///< [in] Parameter 4 to modifier function.
)
{
    std::cerr << "TODO NOT IMPLEMENTED: nodeText()\n";
//    if ( !linearDomSearch()->curElemPtr() ) return "";
//    std::string sVal = linearDomSearch()->curElemPtr()->nodeText();
//    return manipulateValueHelper( sVal, true, sModifierID, sManipParam1, sManipParam2, sManipParam3, "" );
    return ""; // TODO
}

std::string	ScriptMiner::nodeText (
      const std::string& sModifierID								///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    , const std::string& sManipParam1								///< [in] Parameter 1 to modifier function.
    , const std::string& sManipParam2 								///< [in] Parameter 2 to modifier function.
    , const std::string& sManipParam3								///< [in] Parameter 3 to modifier function.
)
{
    return nodeText( sModifierID, sManipParam1, sManipParam2, sManipParam3, "" );
}


/** Get the text of the node at current dom position.
The text extracted from current node position can optionally be filtered through \a sModifierID + parameters.
\return Text of current node possibly filtered through \a sModifierID + parameters. */
std::string	ScriptMiner::nodeText (
      const std::string& sModifierID								///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    , const std::string& sManipParam1								///< [in] Parameter 1 to modifier function.
    , const std::string& sManipParam2 								///< [in] Parameter 2 to modifier function.
)
{
    return nodeText( sModifierID, sManipParam1, sManipParam2, "", "" );
}

/** Get the text of the node at current dom position.
The text extracted from current node position can optionally be filtered through \a sModifierID + parameter.
\return Text of current node possibly filtered through \a sModifierID + parameter. */
std::string	ScriptMiner::nodeText (
      const std::string& sModifierID								///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    , const std::string& sManipParam1								///< [in] Parameter 1 to modifier function.
)
{
    return nodeText( sModifierID, sManipParam1, "", "", "" );
}

/** Get the text of the node at current dom position.
The text extracted from current node position can optionally be filtered through \a sModifierID.
\return Text of current node possibly filtered through \a sModifierID. */
std::string	ScriptMiner::nodeText (
     const std::string& sModifierID									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
)
{
    return nodeText( sModifierID, "", "", "", "" );
}

/** Get the text of the node at current dom position.
The text extracted from current node position filtered through trimDefault.
\return Text of current node filtered through trimDefault. */
std::string	ScriptMiner::nodeText (
)
{
    return nodeText( "", "", "", "", "" );
}



/*
--------------------------------
--- nodeCompare functions ---
-------------------------------- */
bool ScriptMiner::nodeCompare	(
     const std::string& sPattern 			///< [in] String pattern to compare against current value
    ,const std::string& sCompareFun			///< [in] Compare function to use.
    ,const std::string& sModifierID			///< [in] String manipulation function used to manipulate current value. Only built-ins supported.
    ,const std::string& sManipParam1		///< [in] Parameter 1 to modifier function.
    ,const std::string& sManipParam2 		///< [in] Parameter 2 to modifier function.
    ,const std::string& sManipParam3		///< [in] Parameter 3 to modifier function.
    ,const std::string& /* sManipParam4 reserved */					///< [in] Parameter 4 to modifier function.
    )
{
    using namespace crawl;
    using namespace crawl::string_compare;
    std::string	sVal = nodeValue( sModifierID, sManipParam1, sManipParam2, sManipParam3, "" );
    StringCompareFunT strCmp = G_StringCompareLookUp::fromAlias(sCompareFun) ;
    return strCmp( sVal, sPattern ) ;
}


bool ScriptMiner::nodeCompare	(
     const std::string& sPattern 			///< [in] String pattern to compare against current value
    ,const std::string& sCompareFun			///< [in] Compare function to use.
    ,const std::string& sModifierID			///< [in] String manipulation function used to manipulate current value. Only built-ins supported.
    ,const std::string& sManipParam1		///< [in] Parameter 1 to modifier function.
    ,const std::string& sManipParam2 		///< [in] Parameter 2 to modifier function.
    ,const std::string& sManipParam3		///< [in] Parameter 3 to modifier function.
    )
{
    return nodeCompare( sPattern, sCompareFun, sModifierID, sManipParam1, sManipParam2, sManipParam3, "" );
}

bool ScriptMiner::nodeCompare	(
     const std::string& sPattern 			///< [in] String pattern to compare against current value
    ,const std::string& sCompareFun			///< [in] Compare function to use.
    ,const std::string& sModifierID			///< [in] String manipulation function used to manipulate current value. Only built-ins supported.
    ,const std::string& sManipParam1		///< [in] Parameter 1 to modifier function.
    ,const std::string& sManipParam2 		///< [in] Parameter 2 to modifier function.
    )
{
    return nodeCompare( sPattern, sCompareFun, sModifierID, sManipParam1, sManipParam2, "", "" );
}

bool ScriptMiner::nodeCompare	(
     const std::string& sPattern 			///< [in] String pattern to compare against current value
    ,const std::string& sCompareFun			///< [in] Compare function to use.
    ,const std::string& sModifierID			///< [in] String manipulation function used to manipulate current value. Only built-ins supported.
    ,const std::string& sManipParam1		///< [in] Parameter 1 to modifier function.
    )
{
    return nodeCompare( sPattern, sCompareFun, sModifierID, sManipParam1, "", "", "" );
}

bool ScriptMiner::nodeCompare	(
     const std::string& sPattern 			///< [in] String pattern to compare against current value
    ,const std::string& sCompareFun			///< [in] Compare function to use.
    ,const std::string& sModifierID			///< [in] String manipulation function used to manipulate current value. Only built-ins supported.
    )
{
    return nodeCompare( sPattern, sCompareFun, sModifierID, "", "", "", "" );
}

bool ScriptMiner::nodeCompare	(
     const std::string& sPattern 			///< [in] String pattern to compare against current value
    ,const std::string& sCompareFun			///< [in] Compare function to use.
    )
{
    return nodeCompare( sPattern, sCompareFun, "", "", "", "", "" );
}


/*
-----------------------
--- Parse functions ---
----------------------- */

bool ScriptMiner::parseRegex (
    int iCount,
    const std::string& sRegex,
    int postMarkerPos )
{
    return stringSearch().parseRegex( iCount, sRegex, static_cast<crawl::StringSearch::EMatchPos>(postMarkerPos), false, false );
}

bool ScriptMiner::iparseRegex (
    int iCount,
    const std::string& sRegex,
    int postMarkerPos )
{
    return stringSearch().parseRegex( iCount, sRegex, static_cast<crawl::StringSearch::EMatchPos>(postMarkerPos), true, false );
}

bool ScriptMiner::parseToRegex (
    int iCount,
    const std::string& sRegex,
    int postMarkerPos )
{
    return stringSearch().parseRegex( iCount, sRegex, static_cast<crawl::StringSearch::EMatchPos>(postMarkerPos), false, true );
}

bool ScriptMiner::iparseToRegex (
    int iCount,
    const std::string& sRegex,
    int postMarkerPos )
{
    return stringSearch().parseRegex( iCount, sRegex, static_cast<crawl::StringSearch::EMatchPos>(postMarkerPos), true, true );
}

bool ScriptMiner::parseToString (
    int iCount,
    const std::string& sSubstring,
    int postMarkerPos )
{
    return stringSearch().parseToString( iCount, sSubstring, static_cast<crawl::StringSearch::EMatchPos>(postMarkerPos), false );
}

bool ScriptMiner::iparseToString (
    int iCount,
    const std::string& sSubstring,
    int postMarkerPos )
{
    return stringSearch().parseToString( iCount, sSubstring, static_cast<crawl::StringSearch::EMatchPos>(postMarkerPos), true );
}

bool ScriptMiner::parseToEnd ()
{
    return stringSearch().parseToEnd();
}

std::string	ScriptMiner::getParseMatch (
    int iMatchNumber
)
{
    return stringSearch().getParseMatch(iMatchNumber);
}

std::string	ScriptMiner::getParseRest ()
{
    return stringSearch().getParseRest();
}

int	ScriptMiner::getParseMatchCount ( )
{
    return stringSearch().getParseMatchCount();
}


/*
----------------------
--- Text functions ---
---------------------- */
void ScriptMiner::textNewSearch	()
{
   stringSearch().resetMarkersBeginEnd();
}

bool ScriptMiner::findBegin(
    int iCount, 					///< [in] Stop at match number.
    const std::string& sSearchFor,	///< [in] Substring to search for.
    int setBeginToPos 			)	///< [in] Update 'Begin' marker to first or last position in match.
{
    stringSearch().resetMarkersBeginEnd();
    return stringSearch().findBeginNext( iCount, sSearchFor, static_cast<crawl::StringSearch::EMatchPos>(setBeginToPos) );
}

bool ScriptMiner::findEnd		(
    int iCount, 					///< [in] Stop at match number.
    const std::string& sSearchFor,	///< [in] Substring to search for.
    int setEndToPos 			)	///< [in] Update 'End' marker to first or last position in match.
{
    stringSearch().resetMarkersBeginEnd();
    return stringSearch().findEndNext( iCount, sSearchFor, static_cast<crawl::StringSearch::EMatchPos>(setEndToPos)  );
}

bool ScriptMiner::findBeginNext	(
    int iCount, 					///< [in] Stop at match number.
    const std::string& sSearchFor,	///< [in] Substring to search for.
    int setBeginToPos 			)	///< [in] Update 'Begin' marker to first or last position in match.
{
    return stringSearch().findBeginNext( iCount, sSearchFor, static_cast<crawl::StringSearch::EMatchPos>(setBeginToPos) );
}

bool ScriptMiner::findEndNext		(
    int iCount, 					///< [in] Stop at match number.
    const std::string& sSearchFor,	///< [in] Substring to search for.
    int setEndToPos 			)	///< [in] Update 'End' marker to first or last position in match.
{
    return stringSearch().findEndNext( iCount, sSearchFor, static_cast<crawl::StringSearch::EMatchPos>(setEndToPos)  );
}

bool ScriptMiner::ifindBegin	(
    int iCount, 					///< [in] Stop at match number.
    const std::string& sSearchFor,	///< [in] Substring to search for.
    int setBeginToPos 			)	///< [in] Update 'Begin' marker to first or last position in match.
{
    stringSearch().resetMarkersBeginEnd();
    return stringSearch().ifindBeginNext( iCount, sSearchFor, static_cast<crawl::StringSearch::EMatchPos>(setBeginToPos) );
}

bool ScriptMiner::ifindEnd		(
    int iCount, 					///< [in] Stop at match number.
    const std::string& sSearchFor,	///< [in] Substring to search for.
    int setEndToPos 			)	///< [in] Update 'End' marker to first or last position in match.
{
    stringSearch().resetMarkersBeginEnd();
    return stringSearch().ifindEndNext( iCount, sSearchFor, static_cast<crawl::StringSearch::EMatchPos>(setEndToPos)  );
}

bool ScriptMiner::ifindBeginNext	(
    int iCount, 					///< [in] Stop at match number.
    const std::string& sSearchFor,	///< [in] Substring to search for.
    int setBeginToPos 			)	///< [in] Update 'Begin' marker to first or last position in match.
{
    return stringSearch().ifindBeginNext( iCount, sSearchFor, static_cast<crawl::StringSearch::EMatchPos>(setBeginToPos) );
}

bool ScriptMiner::ifindEndNext		(
    int iCount, 					///< [in] Stop at match number.
    const std::string& sSearchFor,	///< [in] Substring to search for.
    int setEndToPos 			)	///< [in] Update 'End' marker to first or last position in match.
{
    return stringSearch().ifindEndNext( iCount, sSearchFor, static_cast<crawl::StringSearch::EMatchPos>(setEndToPos)  );
}


bool ScriptMiner::findRegexBegin	(
    int iCount, 					///< [in] Stop at match number.
    const std::string& sRegex,		///< [in] Regular expression to use.
    int setBeginToPos 			)	///< [in] Update 'Begin' marker to first or last position in match.
{
    stringSearch().resetMarkersBeginEnd();
    return stringSearch().findRegexBeginNext( iCount, sRegex, static_cast<crawl::StringSearch::EMatchPos>(setBeginToPos) );
}

bool ScriptMiner::findRegexEnd		(
    int iCount, 					///< [in] Stop at match number.
    const std::string& sRegex,		///< [in] Regular expression to use.
    int setEndToPos 			)	///< [in] Update 'End' marker to first or last position in match.
{
    stringSearch().resetMarkersBeginEnd();
    return stringSearch().findRegexEndNext( iCount, sRegex, static_cast<crawl::StringSearch::EMatchPos>(setEndToPos)  );
}

bool ScriptMiner::findRegexBeginNext	(
    int iCount, 					///< [in] Stop at match number.
    const std::string& sRegex,		///< [in] Regular expression to use.
    int setBeginToPos 			)	///< [in] Update 'Begin' marker to first or last position in match.
{
    return stringSearch().findRegexBeginNext( iCount, sRegex, static_cast<crawl::StringSearch::EMatchPos>(setBeginToPos) );
}

bool ScriptMiner::findRegexEndNext	(
    int iCount, 					///< [in] Stop at match number.
    const std::string& sRegex,		///< [in] Regular expression to use.
    int setEndToPos 		)		///< [in] Update 'End' marker to first or last position in match.
{
    return stringSearch().findRegexEndNext( iCount, sRegex, static_cast<crawl::StringSearch::EMatchPos>(setEndToPos) );
}


bool ScriptMiner::stepBegin		(
    int iCount 	)				///< [in] Number of chars to step.
{
    return stringSearch().moveBegin( iCount );
}


bool ScriptMiner::stepEnd		(
    int iCount 	)				///< [in] Number of chars to step.
{
    return stringSearch().moveEnd( iCount );
}

/*
-----------------------------
--- (URL) queue functions ---
----------------------------- */
int ScriptMiner::urlQueueSize () const
{
    return urlQueue().size();
}

int ScriptMiner::urlQueueSizeProcessed () const
{
    return urlQueue().sizeProcessed();
}

bool ScriptMiner::urlQueueAlreadyProcessed( const std::string& sUrl ) const
{
    return urlQueue().alreadyProcessed( sUrl );
}


void ScriptMiner::urlQueueClear	()
{
    urlQueue().clearQueue();
}

std::string ScriptMiner::urlQueueFront	()
{
    return urlQueue().front().string();
}

void ScriptMiner::urlQueueAppend (
     int iLinkType 						///< [in] Link type, one of: LINK_TYPE_LOCAL, LINK_TYPE_EXTERNAL, LINK_TYPE_ALL
    ,const std::string& sUrlsMatch 		///< [in] String to match each url against using the compare operator
    ,const std::string& sCompareFun		///< [in] Compare function to use.
)
{
    using crawl::string_compare::G_StringCompareLookUp;
    crawl::StringCompareFunT op = G_StringCompareLookUp::fromAlias(sCompareFun);
    if ( sUrlsMatch.empty()	)	linksGetter()->calculateLinks	( true );
    else						linksGetter()->calculateLinks 	( true, sUrlsMatch, op );
    if ( iLinkType & LINK_TYPE_LOCAL ) {
        urlQueue().append( linksGetter()->linksLocal(), false) ;
    }
    if ( iLinkType & LINK_TYPE_EXTERNAL ) {
        urlQueue().append( linksGetter()->linksExternal(), false) ;
    }
}


void ScriptMiner::urlQueueAppendUnique (
     int iLinkType 						///< [in] Link type, one of: LINK_TYPE_LOCAL, LINK_TYPE_EXTERNAL, LINK_TYPE_ALL
    ,const std::string& sUrlsMatch 		///< [in] String to match each url against using the compare operator
    ,const std::string& sCompareFun		///< [in] Compare function to use.
)
{
    using crawl::string_compare::G_StringCompareLookUp;
    crawl::StringCompareFunT op = G_StringCompareLookUp::fromAlias(sCompareFun);
    if ( sUrlsMatch.empty()	)	linksGetter()->calculateLinks	( true );
    else						linksGetter()->calculateLinks 	( true, sUrlsMatch, op );
    if ( iLinkType & LINK_TYPE_LOCAL ) {
        urlQueue().append( linksGetter()->linksLocal(), true) ;
    }
    if ( iLinkType & LINK_TYPE_EXTERNAL ) {
        urlQueue().append( linksGetter()->linksExternal(), true) ;
    }
}

void ScriptMiner::urlQueueAppend (
    const std::string& sUrl 		///< [in] Urls to append.
)
{
    const bool forceUnique = false;
    const bool updateQueueFile = true;
    urlQueue().pushBack (sUrl, forceUnique, updateQueueFile);
}

void ScriptMiner::urlQueueAppendUnique (
    const std::string& sUrl 		///< [in] Urls to append.
)
{
    const bool forceUnique = true;
    const bool updateQueueFile = true;
    urlQueue().pushBack (sUrl, forceUnique, updateQueueFile);
}

void ScriptMiner::urlQueuePrepend (
    const std::string& sUrl 		///< [in] Urls to prepend.
)
{
    urlQueue().pushFront ( sUrl, false );
}

void ScriptMiner::urlQueuePrependUnique (
    const std::string& sUrl 		///< [in] Urls to prepend.
)
{
    urlQueue().pushFront ( sUrl, true );
}

/*
-----------------------------
--- linksGetter functions ---
----------------------------- */
void ScriptMiner::linksGetterDebugPrint	()
{
    linksGetter()->printLinks();
}


/*
--------------------------
--- valueSet functions ---
-------------------------- */
void ScriptMiner::valueSet (
    const std::string& sValue
    )
{
    stringSearch().setValue ( sValue )	;
}

/*
--------------------------
--- valueGet functions ---
-------------------------- */

std::string	ScriptMiner::valueGet (
     const std::string& sModifierID									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    ,const std::string& sManipParam1								///< [in] Parameter 1 to modifier function.
    ,const std::string& sManipParam2 								///< [in] Parameter 2 to modifier function.
    ,const std::string& sManipParam3								///< [in] Parameter 3 to modifier function.
    ,const std::string& /* sManipParam4 reserved */					///< [in] Parameter 4 to modifier function.
)
{
    // Initalize the value to output to the actual current value (ie. before doing any modifications to it)
    std::string sVal = stringSearch().currentValue();
    return manipulateValueHelper( sVal, true, sModifierID, sManipParam1, sManipParam2, sManipParam3, "" );
}

std::string	ScriptMiner::valueGet (
     const std::string& sModifierID									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    ,const std::string& sManipParam1								///< [in] Parameter 1 to modifier function.
    ,const std::string& sManipParam2 								///< [in] Parameter 2 to modifier function.
    ,const std::string& sManipParam3								///< [in] Parameter 3 to modifier function.
)
{
    return valueGet ( sModifierID, sManipParam1, sManipParam2, sManipParam3, "" );
}

std::string	ScriptMiner::valueGet (
     const std::string& sModifierID									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    ,const std::string& sManipParam1								///< [in] Parameter 1 to modifier function.
    ,const std::string& sManipParam2 								///< [in] Parameter 2 to modifier function.
)
{
    return valueGet ( sModifierID, sManipParam1, sManipParam2, "", "" );
}

std::string	ScriptMiner::valueGet (
     const std::string& sModifierID									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    ,const std::string& sManipParam1								///< [in] Parameter 1 to modifier function.
)
{
    return valueGet ( sModifierID, sManipParam1, "", "", "" );
}

std::string	ScriptMiner::valueGet (
     const std::string& sModifierID									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
)
{
    return valueGet ( sModifierID, "", "", "", "" );
}

std::string	ScriptMiner::valueGet ()
{
    return valueGet ( "", "", "", "", "" );
}


/*
------------------------------
--- valueCompare functions ---
------------------------------ */

/** Compare current value with a pattern. */
bool	ScriptMiner::valueCompare	(
     const std::string& sPattern 			///< [in] String pattern to compare against current value
    ,const std::string& sCompareFun			///< [in] Compare function to use.
    ,const std::string& sModifierID			///< [in] String manipulation function used to manipulate current value. Only built-ins supported.
    ,const std::string& sManipParam1		///< [in] Parameter 1 to modifier function.
    ,const std::string& sManipParam2 		///< [in] Parameter 2 to modifier function.
    ,const std::string& sManipParam3		///< [in] Parameter 3 to modifier function.
    ,const std::string& /* sManipParam4 reserved */					///< [in] Parameter 4 to modifier function.
    )
{
    using namespace crawl;
    using namespace crawl::string_compare;
    std::string	sVal = valueGet( sModifierID, sManipParam1, sManipParam2, sManipParam3, "" );
    StringCompareFunT strCmp = G_StringCompareLookUp::fromAlias(sCompareFun) ;
    return strCmp( sVal, sPattern ) ;
}

bool	ScriptMiner::valueCompare	(
     const std::string& sPattern 			///< [in] String pattern to compare against current value
    ,const std::string& sCompareFun			///< [in] Compare function to use.
    ,const std::string& sModifierID			///< [in] String manipulation function used to manipulate current value. Only built-ins supported.
    ,const std::string& sManipParam1		///< [in] Parameter 1 to modifier function.
    ,const std::string& sManipParam2 		///< [in] Parameter 2 to modifier function.
    ,const std::string& sManipParam3		///< [in] Parameter 3 to modifier function.
    )
{
    return valueCompare( sPattern, sCompareFun, sModifierID, sManipParam1, sManipParam2, sManipParam3, "" );
}

bool	ScriptMiner::valueCompare	(
     const std::string& sPattern 			///< [in] String pattern to compare against current value
    ,const std::string& sCompareFun			///< [in] Compare function to use.
    ,const std::string& sModifierID			///< [in] String manipulation function used to manipulate current value. Only built-ins supported.
    ,const std::string& sManipParam1		///< [in] Parameter 1 to modifier function.
    ,const std::string& sManipParam2 		///< [in] Parameter 2 to modifier function.
    )
{
    return valueCompare( sPattern, sCompareFun, sModifierID, sManipParam1, sManipParam2, "", "" );
}

bool	ScriptMiner::valueCompare	(
     const std::string& sPattern 			///< [in] String pattern to compare against current value
    ,const std::string& sCompareFun			///< [in] Compare function to use.
    ,const std::string& sModifierID			///< [in] String manipulation function used to manipulate current value. Only built-ins supported.
    ,const std::string& sManipParam1		///< [in] Parameter 1 to modifier function.
    )
{
    return valueCompare( sPattern, sCompareFun, sModifierID, sManipParam1, "", "", "" );
}

bool	ScriptMiner::valueCompare	(
     const std::string& sPattern 			///< [in] String pattern to compare against current value
    ,const std::string& sCompareFun			///< [in] Compare function to use.
    ,const std::string& sModifierID			///< [in] String manipulation function used to manipulate current value. Only built-ins supported.
    )
{
    return valueCompare( sPattern, sCompareFun, sModifierID, "", "", "", "" );
}

bool	ScriptMiner::valueCompare	(
     const std::string& sPattern 			///< [in] String pattern to compare against current value
    ,const std::string& sCompareFun			///< [in] Compare function to use.
    )
{
    return valueCompare( sPattern, sCompareFun, "", "", "", "", "" );
}


/*
--------------------------------
--- outputValueGet functions ---
-------------------------------- */

/** Get value of previously written output name/field. */
std::string	ScriptMiner::outputValueContextGet	(
     const std::string& sFieldName			///< [in] Name/fieldname of previously written value to retrieve.
    ,const std::string& sContextName		///< [in] XML level context (default is current context)
)
{
    return stringSearch().outputValueGet(sFieldName, sContextName) ;
}

std::string ScriptMiner::outputValueGet(const std::string& sFieldName, const std::string& sModifierID, const std::string& sManipParam1,
                                        const std::string& sManipParam2, const std::string& sManipParam3, const std::string& /* sManipParam4 reserved */)
{
    auto val = stringSearch().outputValueGet(sFieldName, "");
    val = manipulateValueHelper( val, false, sModifierID, sManipParam1, sManipParam2, sManipParam3, "" ) ;
    stringSearch().currentValueSetDirect( val );
    return val;
}

std::string ScriptMiner::outputValueGet(const std::string& sFieldName, const std::string& sModifierID, const std::string& sManipParam1,
                                        const std::string& sManipParam2, const std::string& sManipParam3)
{
    return outputValueGet(sFieldName, sModifierID, sManipParam1, sManipParam2, sManipParam3, "");
}

std::string ScriptMiner::outputValueGet(const std::string& sFieldName, const std::string& sModifierID, const std::string& sManipParam1,
                                        const std::string& sManipParam2)
{
    return outputValueGet(sFieldName, sModifierID, sManipParam1, sManipParam2, "", "");
}

std::string ScriptMiner::outputValueGet(const std::string& sFieldName, const std::string& sModifierID, const std::string& sManipParam1)
{
    return outputValueGet(sFieldName, sModifierID, sManipParam1, "", "", "");
}

std::string ScriptMiner::outputValueGet(const std::string& sFieldName, const std::string& sModifierID)
{
    return outputValueGet(sFieldName, sModifierID, "", "", "", "");
}

std::string ScriptMiner::outputValueGet(const std::string& sFieldName)
{
    return stringSearch().outputValueGet(sFieldName, "");
}

/*
------------------------------
--- Modify value functions ---
------------------------------ */
std::string		ScriptMiner::valueModify(
     const std::string& sModifierID									///< [in] String manipulation function used to manipulate current value.
    ,const std::string& sManipParam1								///< [in] Parameter 1 to modifier function.
    ,const std::string& sManipParam2 								///< [in] Parameter 2 to modifier function.
    ,const std::string& sManipParam3								///< [in] Parameter 3 to modifier function.
    ,const std::string& /* sManipParam4 reserved */					///< [in] Parameter 4 to modifier function.
    )
{
    std::string sVal = stringSearch().currentValue();
    sVal = manipulateValueHelper( sVal, false, sModifierID, sManipParam1, sManipParam2, sManipParam3, "" ) ;
    stringSearch().currentValueSetDirect( sVal );
    return sVal;
}

std::string		ScriptMiner::valueModify(
     const std::string& sModifierID									///< [in] String manipulation function used to manipulate current value.
    ,const std::string& sManipParam1								///< [in] Parameter 1 to modifier function.
    ,const std::string& sManipParam2 								///< [in] Parameter 2 to modifier function.
    ,const std::string& sManipParam3								///< [in] Parameter 3 to modifier function.
    )
{
    return valueModify( sModifierID, sManipParam1, sManipParam2, sManipParam3, "" );
}

std::string		ScriptMiner::valueModify(
     const std::string& sModifierID									///< [in] String manipulation function used to manipulate current value.
    ,const std::string& sManipParam1								///< [in] Parameter 1 to modifier function.
    ,const std::string& sManipParam2 								///< [in] Parameter 2 to modifier function.
    )
{
    return valueModify( sModifierID, sManipParam1, sManipParam2, "", "" );
}

std::string		ScriptMiner::valueModify(
     const std::string& sModifierID									///< [in] String manipulation function used to manipulate current value.
    ,const std::string& sManipParam1								///< [in] Parameter 1 to modifier function.
    )
{
    return valueModify( sModifierID, sManipParam1, "", "", "" );
}

std::string		ScriptMiner::valueModify(
     const std::string& sModifierID									///< [in] String manipulation function used to manipulate current value.
    )
{
    return valueModify( sModifierID, "", "", "", "" );
}


/*
-------------------------
--- Context functions ---
------------------------- */
void ScriptMiner::dataPushContext (
    std::string sContext,
    std::string const& /*sUnit*/ )
{
    stringSearch().pushContext( sContext, true );
}

void ScriptMiner::dataPushContextAlias (
    const std::string& sContext,
    const std::string& /*sContextAlias*/,
    const std::string& /*sUnit*/ )
{
    stringSearch().pushContext( sContext, true );
}

void ScriptMiner::dataPopContext	()
{
    stringSearch().popContext();
}


void ScriptMiner::contextBegin(	std::string sContextName )
{
    stringSearch().pushContext( sContextName, true );
}

void ScriptMiner::contextEnd ()
{
    stringSearch().popContext();
}

void ScriptMiner::contextOutputSaveAs ( const std::string& sContextName )
{
    stringSearch().contextOutputSaveAs(sContextName);
}

void ScriptMiner::contextFallbackOutputLoad( const std::string& sContextName )
{
    stringSearch().contextFallbackOutputLoad(sContextName);
}

void ScriptMiner::contextFallbackOutputClear()
{
    return stringSearch().contextFallbackOutputClear();
}

std::string ScriptMiner::contextFallbackValueGet( const std::string& sFieldName ) const
{
    return stringSearch().contextFallbackValueGet(sFieldName);
}

void ScriptMiner::contextFallbackValueSet( const std::string& sFieldName, const std::string& sValue )
{
    return stringSearch().contextFallbackValueSet(sFieldName, sValue);
}

bool ScriptMiner::contextFallbackValueExists( const std::string& sFieldName ) const
{
    return stringSearch().contextFallbackValueExists(sFieldName);
}

void ScriptMiner::contextFallbackValueDelete( const std::string& sFieldName )
{
    stringSearch().contextFallbackValueDelete(sFieldName);
}

bool ScriptMiner::contextSavedOutputExists( const std::string& sContextName ) const
{
    return stringSearch().contextSavedOutputExists(sContextName);
}

void ScriptMiner::contextSavedOutputDelete( const std::string& sContextName )
{
    stringSearch().contextSavedOutputDelete(sContextName);
}


/*
------------------------
--- Output functions ---
------------------------ */
// --- outputDirectUnit functions ---

void		ScriptMiner::outputDirectUnit(
     const std::string& sFieldName 									///< [in] Data field name
    ,const std::string& sValue 										///< [in] Value of field
    ,const std::string& /*sUnit*/ 										///< [in] Unit of field
    ,const std::string& sModifierID									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    ,const std::string& sManipParam1								///< [in] Parameter 1 to modifier function.
    ,const std::string& sManipParam2 								///< [in] Parameter 2 to modifier function.
    ,const std::string& sManipParam3								///< [in] Parameter 3 to modifier function.
    ,const std::string& /* sManipParam4 reserved */					///< [in] Parameter 4 to modifier function.
    )
{
    std::string sVal = manipulateValueHelper( sValue, true, sModifierID, sManipParam1, sManipParam2, sManipParam3, "" ) ;
    if ( sVal == "" && scriptFunctionExists(sModifierID) )	return;	// If user function returns emty string we assume that the user himself wrote the value to the output (XML file)
    stringSearch().outputValueDirectUnit( sFieldName, sVal );
}



void		ScriptMiner::outputDirectUnit(
    const std::string& sFieldName, 									///< [in] Data field name
    const std::string& sValue, 										///< [in] Value of field
    const std::string& sUnit, 										///< [in] Unit of field
    const std::string& sModifierID,									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    const std::string& sManipParam1,								///< [in] Parameter 1 to modifier function.
    const std::string& sManipParam2, 								///< [in] Parameter 2 to modifier function.
    const std::string& sManipParam3									///< [in] Parameter 3 to modifier function.
    )
{
    outputDirectUnit( sFieldName, sValue, sUnit, sModifierID, sManipParam1, sManipParam2, sManipParam3, "" );
}

void		ScriptMiner::outputDirectUnit(
    const std::string& sFieldName, 									///< [in] Data field name
    const std::string& sValue, 										///< [in] Value of field
    const std::string& sUnit, 										///< [in] Unit of field
    const std::string& sModifierID,									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    const std::string& sManipParam1,								///< [in] Parameter 1 to modifier function.
    const std::string& sManipParam2 								///< [in] Parameter 2 to modifier function.
    )
{
    outputDirectUnit( sFieldName, sValue, sUnit, sModifierID, sManipParam1, sManipParam2, "", "" );
}

void		ScriptMiner::outputDirectUnit(
    const std::string& sFieldName, 									///< [in] Data field name
    const std::string& sValue, 										///< [in] Value of field
    const std::string& sUnit, 										///< [in] Unit of field
    const std::string& sModifierID,									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    const std::string& sManipParam1									///< [in] Parameter 1 to modifier function.
    )
{
    outputDirectUnit( sFieldName, sValue, sUnit, sModifierID, sManipParam1, "", "", "" );
}

void		ScriptMiner::outputDirectUnit(
    const std::string& sFieldName, 									///< [in] Data field name
    const std::string& sValue, 										///< [in] Value of field
    const std::string& sUnit, 										///< [in] Unit of field
    const std::string& sModifierID									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    )
{
    outputDirectUnit( sFieldName, sValue, sUnit, sModifierID, "", "", "", "" );
}

void		ScriptMiner::outputDirectUnit(
    const std::string& sFieldName, 									///< [in] Data field name
    const std::string& sValue, 										///< [in] Value of field
    const std::string& /*sUnit*/ 										///< [in] Unit of field
    )
{
    stringSearch().outputValueDirectUnit( sFieldName, trimDefault_fnc(config(),sValue) );
}


// --- outputDirect functions ---

void		ScriptMiner::outputDirect(
    const std::string& sFieldName, 									///< [in] Data field name
    const std::string& sValue, 										///< [in] Value of field
    const std::string& sModifierID,									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    const std::string& sManipParam1,								///< [in] Parameter 1 to modifier function.
    const std::string& sManipParam2, 								///< [in] Parameter 2 to modifier function.
    const std::string& sManipParam3,								///< [in] Parameter 3 to modifier function.
    const std::string& /* sManipParam4 reserved */					///< [in] Parameter 4 to modifier function.
    )
{
    outputDirectUnit ( sFieldName, sValue, "", sModifierID, sManipParam1, sManipParam2, sManipParam3, ""  /* sManipParam4 reserved */ );
}

void		ScriptMiner::outputDirect(
    const std::string& sFieldName, 									///< [in] Data field name
    const std::string& sValue, 										///< [in] Value of field
    const std::string& sModifierID,									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    const std::string& sManipParam1,								///< [in] Parameter 1 to modifier function.
    const std::string& sManipParam2, 								///< [in] Parameter 2 to modifier function.
    const std::string& sManipParam3									///< [in] Parameter 3 to modifier function.
    )
{
    outputDirect( sFieldName, sValue, sModifierID, sManipParam1, sManipParam2, sManipParam3, "" );
}

void		ScriptMiner::outputDirect(
    const std::string& sFieldName, 									///< [in] Data field name
    const std::string& sValue, 										///< [in] Value of field
    const std::string& sModifierID,									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    const std::string& sManipParam1,								///< [in] Parameter 1 to modifier function.
    const std::string& sManipParam2 								///< [in] Parameter 2 to modifier function.
    )
{
    outputDirect( sFieldName, sValue, sModifierID, sManipParam1, sManipParam2, "", "" );
}

void		ScriptMiner::outputDirect(
    const std::string& sFieldName, 									///< [in] Data field name
    const std::string& sValue, 										///< [in] Value of field
    const std::string& sModifierID,									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    const std::string& sManipParam1									///< [in] Parameter 1 to modifier function.
    )
{
    outputDirect( sFieldName, sValue, sModifierID, sManipParam1, "", "", "" );
}

void		ScriptMiner::outputDirect(
    const std::string& sFieldName, 									///< [in] Data field name
    const std::string& sValue, 										///< [in] Value of field
    const std::string& sModifierID									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    )
{
    outputDirect( sFieldName, sValue, sModifierID, "", "", "", "" );
}

void		ScriptMiner::outputDirect(
    const std::string& sFieldName, 									///< [in] Data field name
    const std::string& sValue 										///< [in] Value of field
    )
{
    stringSearch().outputValueDirectUnit( sFieldName, trimDefault_fnc(config(),sValue));
}


// --- outputValueUnit functions ---

void		ScriptMiner::outputValueUnit(
    const std::string& sFieldName, 									///< [in] Data field name
    const std::string& sUnit, 										///< [in] Unit of field
    const std::string& sModifierID,									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    const std::string& sManipParam1,								///< [in] Parameter 1 to modifier function.
    const std::string& sManipParam2, 								///< [in] Parameter 2 to modifier function.
    const std::string& sManipParam3,								///< [in] Parameter 3 to modifier function.
    const std::string& /* sManipParam4 reserved */					///< [in] Parameter 4 to modifier function.
    )
{
    // Get the current value and then use that to call outputDirectUnit
    const std::string& sVal ( stringSearch().currentValue() );
    outputDirectUnit( sFieldName, sVal, sUnit, sModifierID, sManipParam1, sManipParam2, sManipParam3, "" /* sManipParam4 reserved */ );
}

void		ScriptMiner::outputValueUnit(
    const std::string& sFieldName, 									///< [in] Data field name
    const std::string& sUnit, 										///< [in] Unit of field
    const std::string& sModifierID,									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    const std::string& sManipParam1,								///< [in] Parameter 1 to modifier function.
    const std::string& sManipParam2, 								///< [in] Parameter 2 to modifier function.
    const std::string& sManipParam3									///< [in] Parameter 3 to modifier function.
    )
{
    outputValueUnit( sFieldName, sUnit, sModifierID, sManipParam1, sManipParam2, sManipParam3, "" );
}

void		ScriptMiner::outputValueUnit(
    const std::string& sFieldName, 									///< [in] Data field name
    const std::string& sUnit, 										///< [in] Unit of field
    const std::string& sModifierID,									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    const std::string& sManipParam1,								///< [in] Parameter 1 to modifier function.
    const std::string& sManipParam2 								///< [in] Parameter 2 to modifier function.
    )
{
    outputValueUnit( sFieldName, sUnit, sModifierID, sManipParam1, sManipParam2, "", "" );
}

void		ScriptMiner::outputValueUnit(
    const std::string& sFieldName, 									///< [in] Data field name
    const std::string& sUnit, 										///< [in] Unit of field
    const std::string& sModifierID,									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    const std::string& sManipParam1									///< [in] Parameter 1 to modifier function.
    )
{
    outputValueUnit( sFieldName, sUnit, sModifierID, sManipParam1, "", "", "" );
}

void		ScriptMiner::outputValueUnit(
    const std::string& sFieldName, 									///< [in] Data field name
    const std::string& sUnit, 										///< [in] Unit of field
    const std::string& sModifierID									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    )
{
    outputValueUnit( sFieldName, sUnit, sModifierID, "", "", "", "" );
}

void		ScriptMiner::outputValueUnit(
    const std::string& sFieldName, 									///< [in] Data field name
    const std::string& sUnit 										///< [in] Unit of field
    )
{
    // Get the current value and then use that to call outputDirectUnit
    const std::string& sVal ( stringSearch().currentValue() );
    outputDirectUnit( sFieldName, sVal, sUnit );
}


// --- outputValue functions ---

void		ScriptMiner::outputValue(
    const std::string& sFieldName, 									///< [in] Data field name
    const std::string& sModifierID,									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    const std::string& sManipParam1,								///< [in] Parameter 1 to modifier function.
    const std::string& sManipParam2, 								///< [in] Parameter 2 to modifier function.
    const std::string& sManipParam3,								///< [in] Parameter 3 to modifier function.
    const std::string& /* sManipParam4 reserved */					///< [in] Parameter 4 to modifier function.
    )
{
    outputValueUnit( sFieldName, "", sModifierID, sManipParam1, sManipParam2, sManipParam3, "" /* sManipParam4 reserved */ );
}


void		ScriptMiner::outputValue(
    const std::string& sFieldName, 									///< [in] Data field name
    const std::string& sModifierID,									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    const std::string& sManipParam1,								///< [in] Parameter 1 to modifier function.
    const std::string& sManipParam2, 								///< [in] Parameter 2 to modifier function.
    const std::string& sManipParam3									///< [in] Parameter 3 to modifier function.
    )
{
    outputValue( sFieldName, sModifierID, sManipParam1, sManipParam2, sManipParam3, "" );
}

void		ScriptMiner::outputValue(
    const std::string& sFieldName, 									///< [in] Data field name
    const std::string& sModifierID,									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    const std::string& sManipParam1,								///< [in] Parameter 1 to modifier function.
    const std::string& sManipParam2 								///< [in] Parameter 2 to modifier function.
    )
{
    outputValue( sFieldName, sModifierID, sManipParam1, sManipParam2, "", "" );
}

void		ScriptMiner::outputValue(
    const std::string& sFieldName, 									///< [in] Data field name
    const std::string& sModifierID,									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    const std::string& sManipParam1									///< [in] Parameter 1 to modifier function.
    )
{
    outputValue( sFieldName, sModifierID, sManipParam1, "", "", "" );
}

void		ScriptMiner::outputValue(
    const std::string& sFieldName, 									///< [in] Data field name
    const std::string& sModifierID									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    )
{
    outputValue( sFieldName, sModifierID, "", "", "", "" );
}

void		ScriptMiner::outputValue(
    const std::string& sFieldName 									///< [in] Data field name
    )
{
    // Call outputValueUnit with empty unit, since it's slightly faster than calling into
    // the general outputValue(), with empty manip function.
    outputValueUnit( sFieldName, "" );
}


/*
-------------------------------------
--- outputValueFindNext functions ---
------------------------------------- */
// --- outputValueFindNextImpl ---

int	ScriptMiner::outputValueFindNextImpl(
     int iCount 								///< [in] Stop at match number iCount (use negative numbers for backwards search).
    ,const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sFieldName 				///< [in] Data field name
    ,const std::string& sModifierID				///< [in] Manipulation function name. Either built-in or custom php function name
    ,const std::string& sManipParam1			///< [in] Parameter 1 to function
    ,const std::string& sManipParam2			///< [in] Parameter 2 to function
    ,const std::string& sManipParam3			///< [in] Parameter 3 to function
    ,const std::string& sManipParam4			///< [in] Parameter 4 to function
    ,bool bUpdateDomPos							///< [in] Do update dom position to found position.
    )
{
    using namespace std;

    int iPosSave = 0;
    if ( !bUpdateDomPos )	iPosSave = domPos();
//    std::cerr << "1 outputValueFindNextImpl( '" << sSequence
//              << "', '" << sFieldName
//              << "', '" << sModifierID
//              << "')\n";

    std::string sPhpFunRetVal = "";
    int iDomPos = domFindNextImpl ( iCount, sPhpFunRetVal, sSequence, "", DefaultCompareFun, postMatchStepsZero, crawl::DomNodeTypes::ALL_NODE_TYPES  );
    if ( sPhpFunRetVal != "" ) {
        outputDirect( sFieldName, sPhpFunRetVal, sModifierID, sManipParam1, sManipParam2, sManipParam3, sManipParam4 );
    }
    else if ( iDomPos ) {
        outputValue( sFieldName, sModifierID, sManipParam1, sManipParam2, sManipParam3, sManipParam4 );
    }
    // TODO: Is this (next else if) ever used, and what exactly is it ??
    else if ( stateMachineMgr()->smCurrent()->hasNavAction(sFieldName) ) {
        std::string value = boost::algorithm::trim_copy(stateMachineMgr()->smCurrent()->valueGet(sFieldName));
        if (value == "-")
            value = "";
        outputDirect( sFieldName, value, sModifierID, sManipParam1, sManipParam2, sManipParam3, sManipParam4 );
    }
    else if ( stateMachineMgr()->smCurrent()->hasNavActionAttribute(sFieldName) ) {
        std::string value = boost::algorithm::trim_copy(stateMachineMgr()->smCurrent()->attributeGet(sFieldName));
        if (value == "-")
            value = "";
        outputDirect( sFieldName, value, sModifierID, sManipParam1, sManipParam2, sManipParam3, sManipParam4 );
    }
    else {
        std::string value;

        iDomPos = m_lookForWordDomFinder->outputValueFindNext(value, currentLookForWordMgr(), toQString(sFieldName));

        if ( iDomPos ) {
            outputDirect( sFieldName, value, sModifierID, sManipParam1, sManipParam2, sManipParam3, sManipParam4 );
        }
        else if ( contextFallbackValueExists(sFieldName) ) {
            outputDirect( sFieldName, contextFallbackValueGet(sFieldName) );  // No modifiers here, since it's an earlier written value
        }
        else if ( settingsMgr()->settingExists( sFieldName ) ) {
            outputDirect( sFieldName, settingsMgr()->settingGet( sFieldName ), sModifierID, sManipParam1, sManipParam2, sManipParam3, sManipParam4 );
        }
    }
    if ( !bUpdateDomPos )	domPosSet(iPosSave);
    return iDomPos;
}


int	ScriptMiner::outputValueFindNext(
     int iCount 								///< [in] Stop at match number iCount (use negative numbers for backwards search).
    ,const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sFieldName 				///< [in] Data field name
    ,const std::string& sModifierID				///< [in] Manipulation function name. Either built-in or custom php function name
    ,const std::string& sManipParam1			///< [in] Parameter 1 to function
    ,const std::string& sManipParam2			///< [in] Parameter 2 to function
    ,const std::string& sManipParam3			///< [in] Parameter 3 to function
    ,const std::string& sManipParam4			///< [in] Parameter 4 to function
    )
{
    return outputValueFindNextImpl ( iCount, sSequence, sFieldName, sModifierID, sManipParam1, sManipParam2, sManipParam3, sManipParam4, false );
}

int		ScriptMiner::outputValueFindNext(
     int iCount 								///< [in] Stop at match number iCount (use negative numbers for backwards search).
    ,const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sFieldName 				///< [in] Data field name
    ,const std::string& sModifierID				///< [in] Manipulation function name. Either built-in or custom php function name
    ,const std::string& sManipParam1			///< [in] Parameter 1 to function
    ,const std::string& sManipParam2			///< [in] Parameter 2 to function
    ,const std::string& sManipParam3			///< [in] Parameter 3 to function
    )
{
    return outputValueFindNext ( iCount, sSequence, sFieldName, sModifierID, sManipParam1, sManipParam2, sManipParam3, "" );
}

int		ScriptMiner::outputValueFindNext(
     int iCount 								///< [in] Stop at match number iCount (use negative numbers for backwards search).
    ,const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sFieldName 				///< [in] Data field name
    ,const std::string& sModifierID				///< [in] Manipulation function name. Either built-in or custom php function name
    ,const std::string& sManipParam1			///< [in] Parameter 1 to function
    ,const std::string& sManipParam2			///< [in] Parameter 2 to function
    )
{
    return outputValueFindNext ( iCount, sSequence, sFieldName, sModifierID, sManipParam1, sManipParam2, "", "" );
}

int		ScriptMiner::outputValueFindNext(
     int iCount 								///< [in] Stop at match number iCount (use negative numbers for backwards search).
    ,const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sFieldName 				///< [in] Data field name
    ,const std::string& sModifierID				///< [in] Manipulation function name. Either built-in or custom php function name
    ,const std::string& sManipParam1			///< [in] Parameter 1 to function
    )
{
    return outputValueFindNext ( iCount, sSequence, sFieldName, sModifierID, sManipParam1, "", "", "" );
}

int	ScriptMiner::outputValueFindNext(
     int iCount 								///< [in] Stop at match number iCount (use negative numbers for backwards search).
    ,const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sFieldName 				///< [in] Data field name
    ,const std::string& sModifierID				///< [in] Manipulation function name. Either built-in or custom php function name
    )
{
    return outputValueFindNext ( iCount, sSequence, sFieldName, sModifierID, "", "", "", "" );
}

int		ScriptMiner::outputValueFindNext(
     int iCount 								///< [in] Stop at match number iCount (use negative numbers for backwards search).
    ,const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sFieldName 				///< [in] Data field name
    )
{
    return outputValueFindNext ( iCount, sSequence, sFieldName, DefaultModifierFun, "", "", "", "" );
}


int	ScriptMiner::outputValueFindNext(
     const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sFieldName 				///< [in] Data field name
    ,const std::string& sModifierID				///< [in] Manipulation function name. Either built-in or custom php function name
    ,const std::string& sManipParam1			///< [in] Parameter 1 to function
    ,const std::string& sManipParam2			///< [in] Parameter 2 to function
    ,const std::string& sManipParam3			///< [in] Parameter 3 to function
    ,const std::string& sManipParam4			///< [in] Parameter 4 to function
    )
{
    return outputValueFindNext ( 1, sSequence, sFieldName, sModifierID, sManipParam1, sManipParam2, sManipParam3, sManipParam4 );
}

int	ScriptMiner::outputValueFindNext(
     const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sFieldName 				///< [in] Data field name
    ,const std::string& sModifierID				///< [in] Manipulation function name. Either built-in or custom php function name
    ,const std::string& sManipParam1			///< [in] Parameter 1 to function
    ,const std::string& sManipParam2			///< [in] Parameter 2 to function
    ,const std::string& sManipParam3			///< [in] Parameter 3 to function
    )
{
    return outputValueFindNext ( sSequence, sFieldName, sModifierID, sManipParam1, sManipParam2, sManipParam3, "" );
}

int	ScriptMiner::outputValueFindNext(
     const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sFieldName 				///< [in] Data field name
    ,const std::string& sModifierID				///< [in] Manipulation function name. Either built-in or custom php function name
    ,const std::string& sManipParam1			///< [in] Parameter 1 to function
    ,const std::string& sManipParam2			///< [in] Parameter 2 to function
    )
{
    return outputValueFindNext ( sSequence, sFieldName, sModifierID, sManipParam1, sManipParam2, "", "" );
}

int		ScriptMiner::outputValueFindNext(
     const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sFieldName 				///< [in] Data field name
    ,const std::string& sModifierID				///< [in] Manipulation function name. Either built-in or custom php function name
    ,const std::string& sManipParam1			///< [in] Parameter 1 to function
    )
{
    return outputValueFindNext ( sSequence, sFieldName, sModifierID, sManipParam1, "", "", "" );
}

int		ScriptMiner::outputValueFindNext(
     const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sFieldName 				///< [in] Data field name
    ,const std::string& sModifierID				///< [in] Manipulation function name. Either built-in or custom php function name
    )
{
    return outputValueFindNext ( sSequence, sFieldName, sModifierID, "", "", "", "" );
}

int		ScriptMiner::outputValueFindNext(
     const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sFieldName 				///< [in] Data field name
    )
{
    return outputValueFindNext ( sSequence, sFieldName, DefaultModifierFun, "", "", "", "" );
}

/*
---------------------------------
--- outputValueFind functions ---
--------------------------------- */

int		ScriptMiner::outputValueFind (
     int iCount 								///< [in] Stop at match number iCount (use negative numbers for backwards search).
    ,const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sFieldName 				///< [in] Data field name
    ,const std::string& sModifierID				///< [in] Manipulation function name. Either built-in or custom php function name
    ,const std::string& sManipParam1			///< [in] Parameter 1 to function
    ,const std::string& sManipParam2			///< [in] Parameter 2 to function
    ,const std::string& sManipParam3			///< [in] Parameter 3 to function
    ,const std::string& sManipParam4			///< [in] Parameter 4 to function
    )
{
    domNewSearch();
    return outputValueFindNext( iCount, sSequence, sFieldName, sModifierID, sManipParam1, sManipParam2, sManipParam3, sManipParam4 );
}


int		ScriptMiner::outputValueFind (
     int iCount 								///< [in] Stop at match number iCount (use negative numbers for backwards search).
    ,const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sFieldName 				///< [in] Data field name
    ,const std::string& sModifierID				///< [in] Manipulation function name. Either built-in or custom php function name
    ,const std::string& sManipParam1			///< [in] Parameter 1 to function
    ,const std::string& sManipParam2			///< [in] Parameter 2 to function
    ,const std::string& sManipParam3			///< [in] Parameter 3 to function
    )
{
    return outputValueFind( iCount, sSequence, sFieldName, sModifierID, sManipParam1, sManipParam2, sManipParam3, "" );
}

int		ScriptMiner::outputValueFind (
     int iCount 								///< [in] Stop at match number iCount (use negative numbers for backwards search).
    ,const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sFieldName 				///< [in] Data field name
    ,const std::string& sModifierID				///< [in] Manipulation function name. Either built-in or custom php function name
    ,const std::string& sManipParam1			///< [in] Parameter 1 to function
    ,const std::string& sManipParam2			///< [in] Parameter 2 to function
    )
{
    return outputValueFind( iCount, sSequence, sFieldName, sModifierID, sManipParam1, sManipParam2, "", "" );
}

int		ScriptMiner::outputValueFind (
     int iCount 								///< [in] Stop at match number iCount (use negative numbers for backwards search).
    ,const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sFieldName 				///< [in] Data field name
    ,const std::string& sModifierID				///< [in] Manipulation function name. Either built-in or custom php function name
    ,const std::string& sManipParam1			///< [in] Parameter 1 to function
    )
{
    return outputValueFind( iCount, sSequence, sFieldName, sModifierID, sManipParam1, "", "", "" );
}

int		ScriptMiner::outputValueFind (
     int iCount 								///< [in] Stop at match number iCount (use negative numbers for backwards search).
    ,const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sFieldName 				///< [in] Data field name
    ,const std::string& sModifierID				///< [in] Manipulation function name. Either built-in or custom php function name
    )
{
    return outputValueFind( iCount, sSequence, sFieldName, sModifierID, "", "", "", "" );
}

int		ScriptMiner::outputValueFind (
     int iCount 								///< [in] Stop at match number iCount (use negative numbers for backwards search).
    ,const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sFieldName 				///< [in] Data field name
    )
{
    return outputValueFind( iCount, sSequence, sFieldName, DefaultCompareFun, "", "", "", "" );
}


int		ScriptMiner::outputValueFind (
     const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sFieldName 				///< [in] Data field name
    ,const std::string& sModifierID				///< [in] Manipulation function name. Either built-in or custom php function name
    ,const std::string& sManipParam1			///< [in] Parameter 1 to function
    ,const std::string& sManipParam2			///< [in] Parameter 2 to function
    ,const std::string& sManipParam3			///< [in] Parameter 3 to function
    ,const std::string& sManipParam4			///< [in] Parameter 4 to function
    )
{
    return outputValueFind( 1, sSequence, sFieldName, sModifierID, sManipParam1, sManipParam2, sManipParam3, sManipParam4 );
}


int		ScriptMiner::outputValueFind (
     const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sFieldName 				///< [in] Data field name
    ,const std::string& sModifierID				///< [in] Manipulation function name. Either built-in or custom php function name
    ,const std::string& sManipParam1			///< [in] Parameter 1 to function
    ,const std::string& sManipParam2			///< [in] Parameter 2 to function
    ,const std::string& sManipParam3			///< [in] Parameter 3 to function
    )
{
    return outputValueFind( sSequence, sFieldName, sModifierID, sManipParam1, sManipParam2, sManipParam3, "" );
}

int		ScriptMiner::outputValueFind (
     const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sFieldName 				///< [in] Data field name
    ,const std::string& sModifierID				///< [in] Manipulation function name. Either built-in or custom php function name
    ,const std::string& sManipParam1			///< [in] Parameter 1 to function
    ,const std::string& sManipParam2			///< [in] Parameter 2 to function
    )
{
    return outputValueFind( sSequence, sFieldName, sModifierID, sManipParam1, sManipParam2, "", "" );
}

int		ScriptMiner::outputValueFind (
     const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sFieldName 				///< [in] Data field name
    ,const std::string& sModifierID				///< [in] Manipulation function name. Either built-in or custom php function name
    ,const std::string& sManipParam1			///< [in] Parameter 1 to function
    )
{
    return outputValueFind( sSequence, sFieldName, sModifierID, sManipParam1, "", "", "" );
}

int		ScriptMiner::outputValueFind (
     const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sFieldName 				///< [in] Data field name
    ,const std::string& sModifierID				///< [in] Manipulation function name. Either built-in or custom php function name
    )
{
    return outputValueFind( sSequence, sFieldName, sModifierID, "", "", "", "" );
}

int		ScriptMiner::outputValueFind (
     const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sFieldName 				///< [in] Data field name
    )
{
    return outputValueFind( sSequence, sFieldName, DefaultCompareFun, "", "", "", "" );
}


/*---------------------
--- State functions ---
-----------------------*/

/*
----------------------------
--- Javascript functions ---
---------------------------- */
bool ScriptMiner::javaScriptExecuteRetVal(
    const std::string& sScript,
    std::string& sScriptReturnValue )
{
    return webBrowser()->javaScriptExecuteRetVal( sScript, sScriptReturnValue );
}

bool ScriptMiner::javaScriptExecute(
    const std::string& sScript )
{
    auto&& fn = [=,this]() -> bool { return webBrowser()->javaScriptExecute( sScript );};
    m_crawlerCommandQueue.push(std::move(fn));
    return true;
}

bool ScriptMiner::javaScriptExecuteWait(const std::string &sScript, int timeoutInMs)
{
    const bool retval = javaScriptExecute(sScript);
    waitForDomReady(timeoutInMs);
    return retval;
}

/*
-------------------------
--- Utility functions ---
------------------------- */
int	ScriptMiner::curlPostUploadFileSimple(
      const std::string& sURL
    , const std::string& sFieldName
    , const std::string& sFilePath 	)
{
    boost::filesystem::path filePath(sFilePath);
    return cpaf::net::curlPostUploadFileSimple( sURL, sFieldName, filePath );
}


bool ScriptMiner::gzCompressFile	(
      const std::string& sSrcFilePath
    , const std::string& sDstFilePath
    )
{
    boost::filesystem::path srcFilePath(sSrcFilePath);
    boost::filesystem::path dstFilePath(sDstFilePath);
    return cpaf::compression::gz_compress( srcFilePath, dstFilePath );
}

bool ScriptMiner::gzUnCompressFile (
      const std::string& sSrcFilePath
    , const std::string& sDstFilePath )
{
    fs::path srcFilePath(sSrcFilePath);
    fs::path dstFilePath(sDstFilePath);
    return compression::gz_uncompress( srcFilePath, dstFilePath );
}

/*
--------------------------
--- Settings functions ---
-------------------------- */
void ScriptMiner::settingDelete (
      const std::string& sName
    )
{
    settingsMgr()->settingDelete( sName );
}

void ScriptMiner::settingSet (
      const std::string& sName
    , const std::string& sValue
    )
{
    settingsMgr()->settingSet( sName, sValue );
    if      (sName == "decimal_point")  configParseDecimalPointSet(sValue);
    else if (sName == "thousands_sep")  configParseThousandsSepSet(sValue);
}

std::string ScriptMiner::settingGet (const std::string& sName
   , const std::string& defaultValue) const
{
    return settingsMgr()->settingGet( sName, defaultValue );
}

bool ScriptMiner::settingExists (
    const std::string& sName
   ) const
{
    return settingsMgr()->settingExists( sName );
}

// Deprecated: Use settingExists instead
bool ScriptMiner::hasSetting (
    const std::string& sName
   ) const
{
    return settingsMgr()->settingExists( sName );
}

bool ScriptMiner::settingBoolGet(const std::string& sName, bool defaultValue) const
{
    const auto& val = settingGet(sName);
    if (val.empty()) return defaultValue;
    return stringToBool(val);
}

/*
------------------------
--- Config functions ---
------------------------ */
void ScriptMiner::runModeSet( crawl::RunModeE eRunMode )
{
    webBrowser()->runModeSet(eRunMode);
}

crawl::RunModeE	ScriptMiner::runMode () const
{
    return webBrowser()->runMode();
}

std::string ScriptMiner::configValueGet ( const std::string& sName )
{
    auto value = config()->valueStrGet(sName);
    if (!value.empty()) {
        return value;
    }
    return settingGet(sName);
}


void ScriptMiner::configValueSet ( const std::string& sName, const std::string& sValue )
{
    config()->valueSet(sName, sValue);
}

bool ScriptMiner::configValueBoolGet(const std::string& sName) const
{
    auto value = config()->valueStrGet(sName);
    if (value.empty()) {
        value = settingGet(sName);
    }
    return stringToBool(value);
}


void ScriptMiner::configUrlStartSet ( crawl::Url const& startingUrl )
{
    settingSet ("urlStart", startingUrl.rawString());

    const auto urlSite = startingUrl.protocolCompose() + startingUrl.domainCompose();
    const auto site_id = boost::algorithm::erase_first_copy(startingUrl.domainCompose(), "www.");
    settingSet ("urlSite", urlSite);
    settingSet ("DoSearchUrl", startingUrl.string());

    settingSet ("site_id", site_id);
    settingSet ("shop_id", site_id);
    settingSet ("outputName", site_id);
}

void ScriptMiner::configUrlStartSet (
    const std::string& sUrl			///< [in] URL to load first.
   )
{
    configUrlStartSet( crawl::Url(sUrl) );
}

void ScriptMiner::configUrlUploadDataSet      ( const std::string sUrl 		)
{
    m_sConfigUrlUploadData = sUrl;
}

std::string	ScriptMiner::configUrlUploadDataGet () const
{
    return m_sConfigUrlUploadData;
}


void ScriptMiner::configDisableLoadImages ()
{
    settingSet("load_images", "no");
}

void ScriptMiner::configForceLoadImages ()
{
    settingSet("load_images", "yes");
}

void ScriptMiner::configAddIncludeUrl (
    const std::string& sPattern,
    const std::string& sCompareFun
)
{
    Crawler::configAddIncludeUrl( sPattern, G_StringCompareLookUp::fromAlias(sCompareFun) );
}

void ScriptMiner::configAddExcludeUrl (
    const std::string& sPattern,
    const std::string& sCompareFun
)
{
    Crawler::configAddExcludeUrl( sPattern, G_StringCompareLookUp::fromAlias(sCompareFun) );
}

void ScriptMiner::configUploadData  ( bool bUploadData )
{
    m_bUploadData = bUploadData;
}

// deprecated: Use configUploadData
void ScriptMiner::configForceSendXmlData  ()
{
    m_bUploadData = true;
}


void ScriptMiner::configAjaxPageLoadDeltaTime (int iMilliSeconds )
{
    m_configAjaxPageLoadDeltaTime = boost::posix_time::milliseconds(iMilliSeconds);
}


void ScriptMiner::configProgressOutputSet	( bool bEnable )
{
    progressOutput( bEnable ) ;
}

void ScriptMiner::configDebugOutputSet( bool bEnable )
{
    debugOutput( bEnable ) ;
}

bool ScriptMiner::configDebugOutputGet()
{
    return debugOutput() ;
}

void ScriptMiner::configParseDecimalPointSet  ( const std::string& sDecimalPoint )
{
    config()->valueSet("decimal_point", sDecimalPoint );
    settingsMgr()->settingSet( "decimal_point", sDecimalPoint );
}

void ScriptMiner::configParseThousandsSepSet  ( const std::string& sThousandsSep )
{
    config()->valueSet("thousands_sep", sThousandsSep );
    settingsMgr()->settingSet( "thousands_sep", sThousandsSep );
}

std::string	ScriptMiner::configParseDecimalPointGet  () const
{
    return config()->valueStrGet("decimal_point");
}

std::string	ScriptMiner::configParseThousandsSepGet  () const
{
    return config()->valueStrGet("thousands_sep");
}

std::string ScriptMiner::configGetRunMode () const
{
    return config()->valueStrGet("run-mode");
}

void ScriptMiner::configOutputEncloseCDATA ( bool bDoEncloseInCDATA )
{
    stringSearch().configOutputEncloseCDATA( bDoEncloseInCDATA ) ;
}

void ScriptMiner::configOutputWriteToFile ( bool bDoWriteOutputToFile )
{
    stringSearch().configOutputWriteToFile ( bDoWriteOutputToFile );
}

void ScriptMiner::configLocaleSettingsSet(const std::string& country_or_currency_code)
{
    const auto json_loc = findLocale(boost::algorithm::to_lower_copy(country_or_currency_code));
    if (json_loc.empty()) {
        return;
    }

    settingSet("country_code", json_loc["country_code"]);
    settingSet("language_code", json_loc["language_code"]);
    settingSet("currency_code", json_loc["currency_code"]);
    settingSet("decimal_point", json_loc["decimal_point"]);
    settingSet("thousands_sep", json_loc["thousands_sep"]);
}

void ScriptMiner::locatedPositionsClear()
{
    linearDomSearch()->locatedPositionsClear();
}

//void ScriptMiner::configUrlStartSet(const std::string& url, const std::string& idKey)
//{

//}

/*
-----------------------
--- Debug functions ---
----------------------- */
void ScriptMiner::domDebugPrint(
    const std::string& /*sFileName*/ )		///< [in] Filename to print to. If emty stdout is used.
{
    using namespace std;
    linearDomSearch()->linearDom().dbgPrintLinearDom();
////    auto&& fn = [=]() -> bool { linearDomSearch()->linearDom(); return true;};
////    m_crawlerCommandQueue.push(std::move(fn));
}

void	ScriptMiner::nodeDebugPrint(
    int iNodesBefore, 				///< [in] Number of nodes to print before the current node (positive number always)
    int iNodesAfter, 				///< [in] Number of nodes to print after the current node (positive number always)
    bool bPrintNodeTypes )			///< [in] Print the node types also
{
    linearDomSearch()->debugPrintCurrentNode( iNodesBefore, iNodesAfter, bPrintNodeTypes);
}

void	ScriptMiner::nodeDebugPrint(
    int iNodesAround, 				///< [in] Number of nodes to print before the current node (positive number always)
    bool bPrintNodeTypes )			///< [in] Print the node types also
{
    linearDomSearch()->debugPrintCurrentNode( iNodesAround, iNodesAround, bPrintNodeTypes);
}


std::string ScriptMiner::nodeValueDebug (
    int iNodesBefore, 				///< [in] Number of nodes to print before the current node (positive number always)
    int iNodesAfter, 				///< [in] Number of nodes to print after the current node (positive number always)
    bool bPrintNodeTypes )			///< [in] Print the node types also
{
    return linearDomSearch()->debugGetCurrentNode( iNodesBefore, iNodesAfter, bPrintNodeTypes);
}

std::string ScriptMiner::nodeValueDebug (
    int iNodesAround, 				///< [in] Number of nodes to print before the current node (positive number always)
    bool bPrintNodeTypes )			///< [in] Print the node types also
{
    return linearDomSearch()->debugGetCurrentNode( iNodesAround, iNodesAround, bPrintNodeTypes);
}

int ScriptMiner::infoLastNetworkError() const
{
    return webBrowser()->infoLastNetworkError();
}


// --------------------------
// --- PRIVATE: Functions ---
// --------------------------

/** Update the script status string, that we add to the Crawler.status file in
writeMiningStatusFile() function.*/
void ScriptMiner::updateScriptStatusString()
{
    // This must be/is called from script thread and not main thread
    auto diff =  boost::posix_time::second_clock::universal_time() - m_timeLastScriptStatusUpdate;
    if (diff.seconds() < 15)
        return;

    m_timeLastScriptStatusUpdate  = boost::posix_time::second_clock::universal_time();
    std::string scriptStatusStr;
    if ( scriptFunctionExists("TEMPLATE__getStatus") ) {
        scriptStatusStr = scriptingClass()->callScriptFunction_String( "TEMPLATE__getStatus" );
    }

    const std::string funName = minerName() + "__getStatus" ;
    if ( scriptFunctionExists(funName) ) {
        if ( scriptStatusStr != "" ) scriptStatusStr += ";";
        scriptStatusStr += scriptingClass()->callScriptFunction_String ( funName ) ;
    }
    scriptStatusSet(scriptStatusStr);
}

void ScriptMiner::writeMiningStatusFile()
{
    using namespace boost::posix_time;
    crawl::StatusFile sf( config()->outputDirGet(), config()->valueStrGet("status-file"), this );
    sf.scriptStatusSet(scriptStatus());
    sf.writeFile();


//    sf.readFile ();
//    std::cout << "root.process_id: " << sf.get("root.process_id", -1) << std::endl;
//    std::cout << "root.script_name: " << sf.get("root.script_name", std::string("")) << std::endl;
//    std::cout << "root.current_url: " << sf.get("root.current_url", std::string("")) << std::endl;
//    std::cout << "root.latest_loaded_time_iso: " << sf.get("root.latest_loaded_time_iso", std::string("")) << std::endl;
//    std::cout << "root.latest_loaded_time_ext_iso: " << sf.get("root.latest_loaded_time_ext_iso", std::string("")) << std::endl;
//    std::cout << "root.tester: " << sf.get("root.tester", std::string("")) << std::endl;
//    std::cout << "root.unknown_genres: " << sf.get("root.unknown_genres", std::string("")) << std::endl;

}


/** Called just before pageload is initiated.
If you want to prevent the pageload return true from this function. */
bool ScriptMiner::slotLoadUri(
    crawl::WebBrowserIF& ,              ///< Pointer to MozBrowser
    const std::string&			sUri	///< Uri about to be loaded
)
{
    m_timeLastPageLoadStarted   = boost::posix_time::second_clock::universal_time();
    if ( !okToLoadUrl ( sUri ) )	return true;	// Returning true from here instructs browser to NOT load the Url!
    if ( sUri != "about:blank" ) m_sCurrentLoadingUrl = sUri;
    m_bPageLoadInProgress = true;

    if ( debugOutput() ) writeProgress ( boost::format("ScriptMiner::slotLoadUri: %1%=%2%  Time: %3%") % sUri % currentUrl() % to_simple_string(m_timeLastPageLoadStarted) );
    return false;
}

/** Slot called on net progress.*/
//bool ScriptMiner::slotNetProgress(
//      void* aRequest
//    , boost::uint32_t aStateFlags
//    , const std::string& sUri
//)
//{
//}


/** Function called when an ajax request is completed.*/
void ScriptMiner::doOnAjaxCompleted()
{
    using namespace std;

    cerr << "FIXMENM ScriptMiner::doOnAjaxCompleted: "
         << "  m_waitingForDomReady: " << m_waitingForDomReady
         << "\n";

    if (m_showNetworkActivity) {
        cerr << "Network: Ajax Completed Event, Waiting for DOM Ready: '"
             << m_waitingForDomReady << "'\n"
             << "  pageHash: " << webBrowser()->pageHash().toUtf8().data()
             << " linear dom size: " << webBrowser()->currentLinearDom()->size()
             << "\n";
    }

    if (m_waitingForDomReady) {
        cerr << "XXX ScriptMiner::doOnAjaxCompleted called from thread: "<< QThread::currentThreadId()
             << "  pageHash: " << webBrowser()->pageHash().toUtf8().data()
             << " linear dom size: " << webBrowser()->currentLinearDom()->size()
             << "\n";
        buildLinearDom();
        waitingForDomReadySet(false); // Signal any script in waiting for dom ready that it can continue.
    }
    using namespace std;
    webBrowser()->resetPageRequestCounters();
}

/** Slot called when whole page is loaded.*/
void ScriptMiner::doOnPageLoadedMainThread()
{
    using namespace std;
    m_timeLastPageLoadFinished  = boost::posix_time::second_clock::universal_time();
    cerr << " [" << urlQueue().sizeProcessed() << "/" << urlQueue().size() << "] "
         << "Loaded '" << m_sHandlerContextName << "' "
         << m_timeLastPageLoadFinished
         << " URL: " << currentUrl()
         << "\n";

    m_bNewPageLoadInitiated = false;

    const bool buidLinearDom = m_waitingForDomReady || !m_minerWorker->isExecutingPhp();
    if (buidLinearDom) {
        buildLinearDom();
        if (config()->valueBoolGet("dump-linear-dom")) {
            const auto dir_path = dumpDirGet() / "lineardom" / fs::path(webBrowser()->currentUri());
            const auto file_path = dir_path / "page.ldump";
            fs::create_directories(dir_path);
            std::ofstream dump_file(file_path.native());
            dump_file << webBrowser()->currentUri() << " [PAGE_URL]\n";
            linearDom()->print(dump_file, true );
        }
        if (config()->valueBoolGet("dump-html-dom")) {
            const auto dir_path = dumpDirGet() / "htmldom" / fs::path(webBrowser()->currentUri());
            const auto file_path = dir_path / "page.html";
            fs::create_directories(dir_path);
            std::ofstream dump_file(file_path.native());
            dump_file << "<!-- " << webBrowser()->currentUri() << " [PAGE_URL] -->\n";
            dump_file << webBrowser()->html();
        }
    }

    m_curMiningStepE = crawl::MiningStepE::stepNoneE;
    m_nextMiningStepE = crawl::MiningStepE::stepMatchE;
    waitingForDomReadySet(false); // Signal any script in waiting for dom ready that it can continue.

    webBrowser()->resetPageRequestCounters();
    m_sLatestFullyLoadedUrl = currentUrl();
    m_iReloadIfNoActivityLevel = 0;
    m_iPageLoadsTotal++;
    m_sCurrentLoadingUrl = "";
    m_bPageLoadInProgress = false;
}

void ScriptMiner::slotPageLoaded(
    crawl::WebBrowserIF&  	///< Pointer to MozBrowser
)
{
    if (webBrowser()->requestedUri().empty() ||  webBrowser()->currentUri() == "about:blank") {
        std::cerr << "INFO: IGNORE LOAD OF empty URL\n";
        return; // Avoid premature script end since the loading of and initial empty URL ("" / "about:blank")
                // will happen before the actual first script start URL in release build for
                // netscavator (crawler) in webkit mode
    }

    using namespace std;
    if (m_showNetworkActivity) {
        cerr << "Network: Page Loaded Event\n";
    }

    const bool scriptIsWaiting = m_waitingForDomReady;
    doOnPageLoadedMainThread();
    const bool workerExecutingPhp = m_minerWorker->isExecutingPhp();
    if (!scriptIsWaiting && !workerExecutingPhp) { //Only call on page loaded for script if it is not already running (waiting) for dom ready
        doOnPageLoadedWorker();
    }
}

void ScriptMiner::slotContinuousTimer()
{
    // TODO: Don't timeout if we are starting up... For example while
    //       we are trying to download sitemap files.


    if (m_iMiningDoneStatus || runModeCreator()) {
        return;
    }

    const auto timeNow = boost::posix_time::second_clock::universal_time();
    const auto timeLastPageLoad = timeNow - m_timeLastPageLoadFinished;
    const auto timeOutInSeconds = cpaf::to_int(settingGet("force_next_page_timeout_seconds", "30"));
    if (timeLastPageLoad > boost::posix_time::seconds(timeOutInSeconds)) {

        if (m_curMiningStepE != crawl::MiningStepE::stepLoadPageE) {
            return;
        }

        std::cerr << "ERROR Timeout page load! Force load main site URL.\n"
                  << "m_timeLastPageLoadFinished: " << m_timeLastPageLoadFinished << "\n"
                  << "timeNow                   : " << timeNow << "\n"
                  << "timeLastPageLoad          : " << timeLastPageLoad << "\n"
                  << "timeOutInSeconds          : " << timeOutInSeconds << "\n"
                  << "threadid: " << QThread::currentThreadId()
                  << std::endl;
        m_timeLastPageLoadFinished = timeNow;
        webBrowser()->cancelPageLoad();
        webBrowser()->loadUri(urlSite());
///        urlLoad(urlSite());
///        navigateStepWorker();
    }
}


//void ScriptMiner::slotContinuousTimer	()
//{
//    const std::string sNoNetActivityHandling    = config()->valueStrGet("no-net-activity-handling");
//    const std::string sNoNetHandlerMiner        = minerName() + "_NoNetActivityHandler";

//    unsigned int activityCount = webBrowser()->activityCounter();
//    if ( m_iPreviousActivityCount == activityCount )    ++m_iTimeSinceLastNetActivityInSeconds;
//    else                                                  m_iTimeSinceLastNetActivityInSeconds = 0;
//    m_iPreviousActivityCount = activityCount;

//    m_iMiningRunTimeInSeconds++;
//    if ( !m_iMiningDoneStatus && (0 == m_iMiningRunTimeInSeconds % 3) ) writeMiningStatusFile();


//    bool triggerReloadAction = false;
//    if (  m_iTimeSinceLastNetActivityInSeconds && (0 == (m_iTimeSinceLastNetActivityInSeconds % m_iConfigTimeReloadIfNoActivityInSeconds)) ) {
//        m_iReloadIfNoActivityLevel++;
//        triggerReloadAction = true;
//    }

//    const auto time_now  = boost::posix_time::second_clock::universal_time();
//    std::cout << "DEBUG: [" <<  m_iConfigTimeReloadIfNoActivityInSeconds << "] "
//              << "ScriptMiner::slotContinuousTimer, URL: " << currentUrl() << " "
//              << "time_now: " << time_now << "\n"
//              << "m_iReloadIfNoActivityLevel: " << m_iReloadIfNoActivityLevel << "\n"
//              << "triggerReloadAction: " << triggerReloadAction << "\n"
//              << std::endl;

//    if ( triggerReloadAction && !m_iMiningDoneStatus && ( crawl::rmCrawlerE == runMode() || crawl::rmNormalE == runMode() ) ) {
//        switch ( m_iReloadIfNoActivityLevel )
//        {
//        case 1 :
//        case 2 :
//        case 3 :
//            {
//                if ( sNoNetActivityHandling == "" && scriptFunctionExists( sNoNetHandlerMiner ) ) {
//                    scriptingClass()->callScriptFunction_Void( sNoNetHandlerMiner, std::to_string(m_iReloadIfNoActivityLevel) );
//                }
//                else if ( sNoNetActivityHandling == "" && scriptFunctionExists( "TEMPLATE_NoNetActivityHandler" ) ) {
//                    scriptingClass()->callScriptFunction_Void("TEMPLATE_NoNetActivityHandler", std::to_string(m_iReloadIfNoActivityLevel) );
//                }
//                else if ( sNoNetActivityHandling != "none" ) {
//                    webBrowser()->loadUri( webBrowser()->currentUri() );
//                    std::string s = str( b::format("Warning: No activity [%1%] in %2% seconds. Reload current loading URL: %3%") % m_iReloadIfNoActivityLevel % m_iTimeSinceLastNetActivityInSeconds % webBrowser()->currentUri() );
//                    g()->logWrite( crawl::logWarningE, s );
//                }
//            }
//            break;
//        case 4 :
//        case 5 :
//            {
//                webBrowser()->loadUri( m_sLatestFullyLoadedUrl );
//                std::string s = str( b::format("Warning: No activity [%1%] in %2% seconds. Reload latest fully loaded URL: %3%") % m_iReloadIfNoActivityLevel % m_iTimeSinceLastNetActivityInSeconds % m_sLatestFullyLoadedUrl );
//                g()->logWrite( crawl::logWarningE, s );
//            }
//            break;
//        default :
//            {
//                webBrowser()->loadUri( m_urlStart.string() );
//                std::string s = str( b::format("Warning: No activity [%1%] in %2% seconds. Reload starting URL: %3%") % m_iReloadIfNoActivityLevel % m_iTimeSinceLastNetActivityInSeconds % m_urlStart.string() );
//                g()->logWrite( crawl::logWarningE, s );
//            }
//        }
//    }

//}

/** 250 ms timer tasks.
Mainly handles potential ajax pageloads, which does not trigger the normal pageStartload/pageLoadFinished events.
Instead we check to see if the scripts navigate() function expected a new pageload and if none is in progress but we have seen
network activity, then we trigger an "artificial" pageloaded event when the network (ajax) activity has stopped again.
*/
void ScriptMiner::slotContinuousTimer2	()
{
//    const auto potentialAjaxPageLoad = webBrowser()->checkPotentialAjaxLoadCompleted(m_configAjaxPageLoadDeltaTime);
//    std::cerr << "FIXMENM: slotContinuousTimer2()"
//              <<  ", webBrowser()->pageLoading(): " << webBrowser()->pageLoading()
//               <<  ", m_bNewPageLoadInitiated: " << m_bNewPageLoadInitiated
//                <<  ", potentialAjaxPageLoad: " << potentialAjaxPageLoad
//                 <<  ", activityRequestStartCount(): " << webBrowser()->activityRequestStartCount()
//              << "\n";

    // --- FIXMENM: TEst mouse event sending [BEGIN] ---
    // https://www.linuxquestions.org/questions/programming-9/simulating-a-mouse-click-594576/
//    QWidget* browserWidget = webBrowser()->browserView()->widgetPtr();
//    QWidget* eventsReciverWidget = browserWidget;
//    foreach(QObject* obj, browserWidget->children())
//    {
//        QWidget* wgt = qobject_cast<QWidget*>(obj);
//        if (wgt){
//            eventsReciverWidget = wgt;
//            break;
//        }
//    }
//    QPoint clickPos(100, 100);
//    leftMouseClick(eventsReciverWidget, clickPos);
    // --- FIXMENM: Test mouse event sending [END] ---

//    if ( m_bNewPageLoadInitiated && !webBrowser()->pageLoading() ) {
//        if ( webBrowser()->checkPotentialAjaxLoadCompleted(m_configAjaxPageLoadDeltaTime) ) {
//            std::cout << "TADA! Simulate page loaded " << std::endl;
//            webBrowser()->signalsManager()->signalPageLoaded(*webBrowser());
//        }
//    }

    if ( !webBrowser()->pageLoading() ) {
        if ( webBrowser()->checkPotentialAjaxLoadCompleted(m_configAjaxPageLoadDeltaTime) ) {
            if (m_bNewPageLoadInitiated) {
                std::cerr << "Simulate (ajax) page loaded!\n";
                webBrowser()->signalsManager()->signalPageLoaded(*webBrowser());
            }
            else {
                doOnAjaxCompleted();
            }
        }
    }
}

/**
Do standard manipulation of a value and return result.
The string manipulation function can be the name of one of the built-ins like
'append', 'eraseAll' etc.
It can also be a 'named modifier' created using modifierCreate().
By default the value is filtered through the trimDefault function
which trims spaces away from both end of the output string value. If you don't want this
trimming you should use 'raw' as your manipulation function, which takes no extra parameters.

!User defined PHP manipulation function
You can also supply a user defined PHP function name as the string manipulation function, which if
found, will take precedence. The function will be called with the value you're writing as first parameter
and any manipulation parameters as the following arguments. If you don't need all the arguments you do
not need to declare them in your PHP funcion as they will just be silently ignored.
You must remeber to return the modified value from your function.

\return Current value filtered though the function specified. */
std::string	ScriptMiner::manipulateValueHelper (
     const std::string& sValue										///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    ,bool  bAllowDefaultTrimming									///< [in] If true we allow default trimming of the result. If false default trimming will never happen.
    ,const std::string& sModifierID									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    ,const std::string& sManipParam1								///< [in] Parameter 1 to modifier function.
    ,const std::string& sManipParam2 								///< [in] Parameter 2 to modifier function.
    ,const std::string& sManipParam3								///< [in] Parameter 3 to modifier function.
    ,const std::string& /* sManipParam4 reserved */					///< [in] Parameter 4 to modifier function.
)
{
    // Initalize the value to output to the actual current value (ie. before doing any modifications to it)
    std::string sVal = sValue;
    if ( boost::algorithm::icontains(sModifierID, "raw") ) bAllowDefaultTrimming = false;	// Skip default trimming if user named his function with something containing "raw"

    // First try to se if the manipulation function is a user defined PHP one, and if so: call it
    std::string sTemplateFunction = "TEMPLATE_" + sModifierID;  // Used later
    if ( scriptFunctionExists(sModifierID) ) {
        sVal = scriptingClass()->callScriptFunction_String( sModifierID, sVal, sManipParam1, sManipParam2, sManipParam3 /*, sManipParam4 reserved */ );
    }
    // Next see if sModifierID refers to a named modifier created using modifierCreate()
    else if (auto pModifier = modifierMgr()->modifierGet(sModifierID)) {
        if ( scriptFunctionExists( pModifier->sManipFunID) ) {
            //std::cerr << "FIXMENM manipulateValue call PHP function: '" << pModifier->sManipFunID << "'\n";
            sVal = scriptingClass()->callScriptFunction_String( pModifier->sManipFunID, sVal,  pModifier->sParam1, pModifier->sParam2, pModifier->sParam3  /*, pModifier->sParam4 reserved */  );
        }
        else {
            boost::shared_ptr<crawl::StrModifierAbstraction> pManip = G_StringManipLookUp::fromAliasAny( pModifier->sManipFunID );
            if ( pManip ) {
                sVal = pManip->callMeStr( config(), sVal, pModifier->sParam1, pModifier->sParam2, pModifier->sParam3  /*, pModifier->sParam4 reserved */ );
            }
        }
    }
    // Then try to se if the manipulation function is a TEMPLATE defined PHP one, and if so: call it
    else if ( scriptFunctionExists(sTemplateFunction) ) {
        sVal = scriptingClass()->callScriptFunction_String( sTemplateFunction, sVal, sManipParam1, sManipParam2, sManipParam3 /*, sManipParam4 reserved */ );
    }
    else {
        // ElSE see if sModifierID matches the name of one of our built-in ones like 'append', 'replaceAll',...
        boost::shared_ptr<crawl::StrModifierAbstraction> pManip = G_StringManipLookUp::fromAliasAny(sModifierID);
        if ( pManip ) {
            sVal = pManip->callMeStr( config(), sVal, sManipParam1, sManipParam2, sManipParam3  /*, sManipParam4 reserved */ );
        }
    }
    if ( bAllowDefaultTrimming ) sVal = trimDefault_fnc ( config(), sVal );
    return sVal;
}

LookForWordMgr* ScriptMiner::lookForWordMgr(const std::string& contextName) const
{
    auto ptr = m_lookForWordMgrs[contextName].get();
    if (!ptr) {
        m_lookForWordMgrs[contextName] = std::unique_ptr<LookForWordMgr>(new LookForWordMgr);
        ptr = m_lookForWordMgrs[contextName].get();
    }
    return ptr;
}

LookForWordMgr* ScriptMiner::currentLookForWordMgr() const
{
    return m_lookForWordMgrs[handlerContextName()].get();
}

bool ScriptMiner::workerIsExecutingPhp() const
{
    return m_workerIsExecutingPhp;
}

bool ScriptMiner::getWaitingForDomReady() const
{
    return m_waitingForDomReady;
}

crawl::MinerWorker* ScriptMiner::minerWorker() const
{
    return m_minerWorker;
}

void ScriptMiner::minerWorkerSet(crawl::MinerWorker* minerWorker)
{
    m_minerWorker = minerWorker;
}

std::string ScriptMiner::scriptStatus() const
{
    std::lock_guard<std::mutex> guard(m_scriptStatusMutex);
    return m_scriptStatus;
}

void ScriptMiner::scriptStatusSet(const std::string& scriptStatus)
{
    std::lock_guard<std::mutex> guard(m_scriptStatusMutex);
    m_scriptStatus = scriptStatus;
}

void ScriptMiner::waitingForDomReadySet(bool waitingForDomReady)
{
    m_waitingForDomReady = waitingForDomReady;
}

boost::filesystem::path ScriptMiner::dumpDirGet() const
{
    return config()->outputDirGet() / (m_outputName + ".sitedump");
}

boost::uint32_t ScriptMiner::itemsWritten() const
{
    return m_iItemsWritten;
}

