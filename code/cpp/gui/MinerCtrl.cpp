#include "MinerCtrl.h"

#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <utils/cpaf_string_utils.hpp>
#include <filesystem/cpaf_file_directory_functions.h>
#include <QThread>
#include <QApplication>
#include <QCoreApplication>

#include <MinerWorker.h>
#include <Configuration.h>
#include <Globals.h>
#include <php_embedding/php_embedding_utils.h>
#include <php_embedding/php_embedding_callbacks.h>
#include <scriptcrawl_private_php.h>
#include <url/Url.h>
#include <parser/DataWriterXml.h>
#include <parser/DataWriterJson.h>
#include <utils/utils.h>
#include <scripting/ScriptExecutor.h>
#include <NetscavatorFactoryIF.h>
#include <SignalsManager.h>
#include <ScriptMiner.h>

#include <OutputViewUi.h>
//#include <creatorutils/DomTreeTextHtmlGen.h>
#include <CreatorTextDomTreeView.h>
#include <CreatorLinearDomTableModel.h>
#include <CreatorDomTableView.h>
#include <DomTreeModel.h>
#include <DomTreeView.h>
#include <OutputViewCtrl.h>
#include <EditorViewUi.h>
#include <htmlparser/html/XPath.h>

using namespace boost::algorithm;
using namespace crawl;
using namespace std;


MinerCtrl::MinerCtrl (crawl::NetscavatorFactoryIF* netscavatorFactory, QObject *parent)
    : QObject(parent)
    , m_netscavatorFactory  (netscavatorFactory)
    , m_pBrowser            ()
{
    g_phpEmbedCallbacks::Instance().startUpFun = boost::bind(&MinerCtrl::phpStartupCallback, this, _1);
}

boost::shared_ptr<ScriptMinerIF> MinerCtrl::miner()
{
    return m_pMiner;
}

void MinerCtrl::setWebView (crawl::BrowserViewIF* pWebViewBrowser)
{
    // TODO: This only seems to work if we also reload
    m_pWebViewBrowser   = pWebViewBrowser;
    m_pBrowser->setWebView( pWebViewBrowser);
    updateDomTreeViews();
}

crawl::MinerWorker* MinerCtrl::minerWorker () const
{
    return m_pMiner->minerWorker();
}

EditorViewUi* MinerCtrl::editorView() const
{
    return m_editorView;
}

void MinerCtrl::netscavatorFactorySet(NetscavatorFactoryIF* netscavatorFactory)
{
    m_netscavatorFactory = netscavatorFactory;
}

void MinerCtrl::init (BrowserViewIF* pWebViewBrowser, OutputViewUi* pDataOutView,
                       /*CreatorTextDomTreeView* pDomTreeText, */CreatorDomTableView* domTableView,
                       CreatorLinearDomTableModel* linearDomTableModel,
                       DomTreeModel* domTreeModel, DomTreeView* domTreeView)
{
    m_pWebViewBrowser       = pWebViewBrowser;
    m_pDataOutView          = pDataOutView;
    m_domTableView          = domTableView;
    m_linearDomTableModel   = linearDomTableModel;
    m_domTreeModel          = domTreeModel;
    m_domTreeView           = domTreeView;

    constexpr crawl::RunModeE runMode = crawl::rmDesignE;
    boost::shared_ptr<crawl::Configuration> c= crawl::g()->configuration();

    m_pBrowser = boost::shared_ptr<crawl::WebBrowserIF>(m_netscavatorFactory->createBrowser(m_pWebViewBrowser) );
    m_pBrowser->runModeSet(runMode);

    const std::string sMinerName      = "Crawler";
    const std::string sBaseOutputName = "Crawler";

    StringSearch::DataWriterVecT writers;
    boost::shared_ptr<crawl::DataWriterJson> pJsonOut(new crawl::DataWriterJson(c->outputDirGet(), ""));
    writers.push_back(pJsonOut);

    if (m_pDataOutView) {
        m_pOutputViewCtrl   = boost::shared_ptr<crawl::OutputViewCtrl>( new crawl::OutputViewCtrl(sBaseOutputName, m_pDataOutView)) ;
        writers.push_back(m_pOutputViewCtrl);
        g_phpEmbedCallbacks::Instance().writeFun = boost::bind(&OutputViewCtrl::phpStdOutputWrite, m_pOutputViewCtrl.get(), _1, _2 );
        g_phpEmbedCallbacks::Instance().logMsgFun = boost::bind(&OutputViewCtrl::phpLogMessage, m_pOutputViewCtrl.get(), _1 );
        g_phpEmbedCallbacks::Instance().flushFun = boost::bind(&OutputViewCtrl::phpFlushStdOut, m_pOutputViewCtrl.get(), _1 );
    }

    m_pMiner = boost::shared_ptr<ScriptMiner>(
            new ScriptMiner(m_pBrowser, sBaseOutputName, crawl::Url(""), writers, boost::shared_ptr<ScriptingClassIF>(), c )
    );
    m_pMiner->init();
    m_pMiner->runModeSet(runMode);
    g()->minerAdd( m_pMiner, sBaseOutputName );

    m_pBrowser->signalsManager()->connectPageLoaded     (boost::bind(&MinerCtrl::pageLoadedSlot    , this, _1 ));
    m_pBrowser->signalsManager()->connectDomChanged     (boost::bind(&MinerCtrl::domChangedSlot    , this, _1 ));
    m_pBrowser->signalsManager()->connectOnMatchHandler (boost::bind(&MinerCtrl::onMatchPageSlot   , this ));
    m_pBrowser->signalsManager()->connectOnMiningDone   (boost::bind(&MinerCtrl::miningDoneSlot    , this ));
    if (m_domTableView && m_domTreeView) {
        //connect(m_domTableView, &CreatorDomTableView::domPositionsMarkedSig, m_pBrowser.get(), &WebBrowserIF::markPositionsClear);
        connect(m_domTableView, &CreatorDomTableView::domPosClickedSig, m_pBrowser.get(), &WebBrowserIF::markPositionClear);
        connect(m_domTreeView, &DomTreeView::domPosClickedSig, m_pBrowser.get(), &WebBrowserIF::markPositionClear);

        connect(m_domTableView, &CreatorDomTableView::domPosClickedSig, m_domTreeView, &DomTreeView::selectDomPosSlot);
        connect(m_domTreeView, &DomTreeView::domPosClickedSig, m_domTableView, &CreatorDomTableView::selectDomPosSlot);
    }
}

void MinerCtrl::loadPhpScript (const QString &scriptAbsPath)
{
    const string path = scriptAbsPath.toUtf8().data();
    const QString phpMinerScript = QString::fromUtf8(cpaf::filesystem::read_file(path).c_str());
    m_pMiner->loadMinerScriptWorker(phpMinerScript, scriptAbsPath);
}

void MinerCtrl::reloadEditorPhpScript (EditorViewUi* pEditorView)
{
    if (!pEditorView) {
        return;
    }
    m_editorView = pEditorView;
    m_pMiner->loadMinerScriptWorker(pEditorView->text(), m_editorView->filePath().absoluteFilePath());
}

void MinerCtrl::runCrawler (EditorViewUi* pEditorView, BrowserViewIF* /*pWebViewBrowser*/, crawl::RunModeE rm )
{
    reloadEditorPhpScript(pEditorView);
    if ( m_pMiner ) {
        m_pMiner->runModeSet(rm);
        m_pMiner->beginMiningWorker(true);
    }
}

void MinerCtrl::runCrawlerRobot (crawl::RunModeE rm)
{
    const auto c = crawl::g()->configuration();
    const bool doContinue = c->doContinue();
    if ( m_pMiner ) {
        m_pMiner->runModeSet(rm);
        m_pMiner->stringSearch().doContinueModeSet(doContinue, c->continueCounterGet());  // Make sure that we append to output (json) in case we are trying to continue a scanning.

        bool doRestart = !doContinue;
        m_pMiner->beginMiningWorker(doRestart);
    }
}

void MinerCtrl::runSetupFunctions ()
{
    if (m_pMiner) {
        m_pMiner->runSetupFunctionsWorker();
    }
}

void MinerCtrl::runPhpSnippet (const QString& phpCode)
{
    if (m_pMiner->runModeCreator() ) {
        m_pMiner->linearDomSearch()->locatedPositionsClear();
    }
    m_pMiner->runPhpSnippetWorker(phpCode);
}

// ---------------------
// --- PUBLIC: Slots ---
// ---------------------

void MinerCtrl::stopMiningSlot  ()
{
    m_pMiner->endMiningWorker();
}

void MinerCtrl::nextStepSlot            ()
{

}

void MinerCtrl::forcePageLoadedSlot ()
{
///	m_pBrowser->signalsManager()->signalPageLoaded(*m_pBrowser);
    m_pBrowser->triggerPageLoaded();
///    updateDomTreeViews();
}

void MinerCtrl::matchStepSlot ()
{
    m_pMiner->matchStepWorker();
}

void MinerCtrl::mineStepSlot ()
{
    m_pMiner->mineStepWorker();
}

void MinerCtrl::navigateStepSlot ()
{
    m_pMiner->navigateStepWorker();
}

// Not used currently!
void MinerCtrl::webElementSelectedSlot (BrowserViewIF* /*pWebView*/)
{
    LinearDomIF::size_type iSelectedDomPos = 0;
    boost::shared_ptr<crawl::DomNodeIF>  pSelectedNode;
    boost::shared_ptr<LinearDomIF> pLinearDom = m_pMiner->linearDom();
    bool bOk = false;
    if ( pLinearDom ) {
        XPath xpath = m_pWebViewBrowser->selectedElementXPath();
        const auto it = pLinearDom->findFromXPath(xpath);
        if ( it != pLinearDom->end() ) {
            bOk = true;
            iSelectedDomPos = pLinearDom->iteratorToPos(it);
            pSelectedNode = it->node();
            if (m_domTableView) {
                m_domTableView->selectDomPosSlot(iSelectedDomPos);
            }
            if (m_domTreeView) {
                m_domTreeView->selectDomPosSlot(iSelectedDomPos);
            }
        }
    }
}

void MinerCtrl::domPosSelectedSlot(const QString& xpath, const QString& innerText)
{
    const string path = toString(xpath);
    crawl::XPath xp(path);

//    cerr << "FIXMENM MinerCtrl::domPosSelectedSlot "
//         << "\nxpath: " << xpath.toUtf8().constData()
//         << "\nconv : " << xp.toString()
//         << "\ninnerText: " << innerText.toUtf8().constData()
//         << "\n";
    LinearDomIF::size_type iSelectedDomPos = 0;
    auto pLinearDom = m_pMiner->linearDom();
    if ( pLinearDom ) {
        const auto it = pLinearDom->findFromXPath(xp);
        if ( it != pLinearDom->end() ) {
            iSelectedDomPos = pLinearDom->iteratorToPos(it);
            if (m_domTableView) {
                m_domTableView->selectDomPosSlot(iSelectedDomPos);
            }
            if (m_domTreeView) {
                m_domTreeView->selectDomPosSlot(iSelectedDomPos);
            }
        }
    }
}

void MinerCtrl::browserChangedSlot (BrowserViewIF* pWebView)
{
    setWebView(pWebView);
}


// ---------------------------------
// --- PRIVATE: Helper functions ---
// ---------------------------------
void MinerCtrl::updateDomTreeViews ()
{
    if (!m_linearDomTableModel || !m_domTreeModel) return;
    if (m_pMiner->runModeCreator()) {
        m_linearDomTableModel->setLinearDom( browser()->currentLinearDom() );
        m_domTreeModel->setLinearDom( browser()->currentLinearDom() );
    }
}

void MinerCtrl::pageLoadedSlot (crawl::WebBrowserIF&)
{
    updateDomTreeViews();
}

void MinerCtrl::domChangedSlot (crawl::WebBrowserIF&)
{
    if (globalConfig()->runMode() != RunModeE::rmCrawlerE) {
        updateDomTreeViews();
    }
}

void MinerCtrl::onMatchPageSlot ()
{
    emit onMatchPage();
}

int MinerCtrl::phpStartupCallback (struct _sapi_module_struct* /*sapi_module*/)
{
    return 0;
}

void MinerCtrl::miningDoneSlot ()
{
    if ( g()->configuration()->valueBoolGet("exit-when-done") ) {
        qApp->quit();
    }
}


