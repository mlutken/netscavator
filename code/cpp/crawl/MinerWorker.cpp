#include "MinerWorker.h"
#include <QThread>
#include <QTimer>
#include <iostream>

#include <Configuration.h>
#include <Globals.h>
#include <ScriptMiner.h>
#include <scripting/ScriptExecutor.h>
#include <php_embedding/php_embedding_utils.h>
#include <php_embedding/php_embedding_callbacks.h>
#include <containers/DomSearchMgr.h>

//const int MAX_ARGS = 10;

using namespace std;
namespace crawl {


MinerWorker::MinerWorker()
    : MinerWorkerIF(),
      m_scriptExecutor(new ScriptExecutor(this))
{
//    cout <<"MinerWorker::CONSTRUCTOR called from thread: "<< QThread::currentThreadId() << endl;
    m_minerWorkerTimer = new QTimer(this);
    QObject::connect(m_minerWorkerTimer, SIGNAL(timeout()), this, SLOT(onTimeoutSlot()));
    m_minerWorkerTimer->start(1000*5);


}

MinerWorker::~MinerWorker()
{
    cout <<"MinerWorker::DESTRUCTOR called from thread: "<< QThread::currentThreadId() << endl;
    shutDownPhpSlot();
}

ScriptExecutor *MinerWorker::scriptExecutor() const
{
    return m_scriptExecutor;
}

boost::shared_ptr<ScriptMiner> MinerWorker::miner() const
{
    return m_miner;
}

void MinerWorker::minerSet(const boost::shared_ptr<ScriptMiner>& miner)
{
    m_miner = miner;
}


bool MinerWorker::event(QEvent* e)
{
    bool processed = false;

    if (e->type() == DomReadyEvent::staticType()) {
        domReadySlot();
        processed = true;
    }
    else if (e->type() == MatchStepEvent::staticType()) {
        processed = true;
    }
    else if (e->type() == MineStepEvent::staticType()) {
        processed = true;
    }
    else if (e->type() == NavigateStepEvent::staticType()) {
        processed = true;
    }
    else if (e->type() == BeginMiningEvent::staticType()) {
        processed = true;
    }
    else if (e->type() == EndMiningEvent::staticType()) {
        processed = true;
    }
    else if (e->type() == StartUpPhpEvent::staticType()) {
        startUpPhpSlot();
        processed = true;
    }
    else if (e->type() == ShutDownPhpEvent::staticType()) {
        shutDownPhpSlot();
        processed = true;
    }
    else if (e->type() == RunPhpSnippetEvent::staticType()) {
        auto ev = static_cast<RunPhpSnippetEvent*>(e);
        runPhpSnippetSlot(ev->phpCode);
        processed = true;
    }
    else if (e->type() == LoadMinerCodeEvent::staticType()) {
        auto ev = static_cast<LoadMinerCodeEvent*>(e);
        m_scriptExecutor->loadMinerCode(m_miner, ev->scriptCode, ev->scriptAbsPath);
        processed = true;
    }



    if (!processed)
        return QObject::event(e);

    return true;
}

void MinerWorker::startUpPhpSlot()
{
    m_isExecutingPhp = true;
    m_scriptExecutor->startup(m_miner);
    emit workDoneSignal(TaskDone::startUpPhp);
    m_isExecutingPhp = false;
}

void MinerWorker::shutDownPhpSlot()
{
    m_isExecutingPhp = true;
    shutdownPhp();

    emit workDoneSignal(TaskDone::shutDownPhp);
    m_isExecutingPhp = false;
}

void MinerWorker::onTimeoutSlot()
{
//    cout <<"MinerWorker::onTimeout called from: "<< QThread::currentThreadId() << endl;
}

/** This slot should be called when browser is done loading a page or ceased ajax
 * activity or done executing som javascript, that potentially changes the dom. */
void MinerWorker::domReadySlot()
{
    emit workDoneSignal(TaskDone::domReady);
}

void MinerWorker::loadMinerScriptSlot(const QString &phpMinerScript, const QString& scriptAbsPath)
{
    m_isExecutingPhp = true;
    m_scriptExecutor->loadMinerCode(m_miner, phpMinerScript, scriptAbsPath);
    m_miner->domSearchMgr()->prepareForRun();

    emit workDoneSignal(TaskDone::loadMinerScript);
    m_isExecutingPhp = false;
}

void crawl::MinerWorker::runSetupFunctionsSlot()
{
    m_isExecutingPhp = true;
    if (m_miner)
        m_miner->runSetupFunctions();
    emit workDoneSignal(TaskDone::runSetupFunctions);
    m_isExecutingPhp = false;
}

void MinerWorker::beginMiningSlot(bool restart)
{
    m_isExecutingPhp = true;
    if (m_miner)
        m_miner->startMining(restart);
    emit workDoneSignal(TaskDone::beginMining);
    m_isExecutingPhp = false;
}

void MinerWorker::endMiningSlot()
{
    m_isExecutingPhp = true;
    if (m_miner)
        m_miner->endMining( crawl::miningDoneUserStopE ); // Typically this slot will be called from GUI
    emit workDoneSignal(TaskDone::endMining);
    m_isExecutingPhp = false;
}

void MinerWorker::matchStepSlot()
{
    m_isExecutingPhp = true;
    if (m_miner)
        m_miner->match(); // Typically this slot will be called from GUI
    emit workDoneSignal(TaskDone::matchStep);
    m_isExecutingPhp = false;
}

void MinerWorker::mineStepSlot()
{
    m_isExecutingPhp = true;
    if (m_miner)
        m_miner->mine(); // Typically this slot will be called from GUI
    emit workDoneSignal(TaskDone::mineStep);
    m_isExecutingPhp = false;
}

void MinerWorker::navigateStepSlot()
{
    m_isExecutingPhp = true;
    if (m_miner)
        m_miner->nextPage(); // Typically this slot will be called from GUI (In GUI we use next page for navigate step)
    emit workDoneSignal(TaskDone::navigateStep);
    m_isExecutingPhp = false;
}

void MinerWorker::doOnPageLoadedSlot()
{
    m_isExecutingPhp = false;
    if (!m_miner)
        return;

    const auto rm = m_miner->runMode();
    if (rm == crawl::rmCrawlerE || rm == crawl::rmNormalE) {
        m_isExecutingPhp = true;
        m_miner->match(); // assigns the m_sHandlerContextName (=handlerContextName())
        emit workDoneSignal(TaskDone::matchStep);
        if ( m_miner->handlerContextName() == "" ) {
            cout << "WARNING: Web page (" << m_miner->handlerContextName()
                 << ") not matching any handler, URL: " << m_miner->currentUrl()
                 << endl;
        }

        m_miner->mine();
        emit workDoneSignal(TaskDone::mineStep);
        bool done = !m_miner->nextPage();
        emit workDoneSignal(TaskDone::navigateStep);
        if ( done ) {
//            writeProgress ( boost::format("*** DONE Scanning! Time: %1% Last URL: %2% ***\n") % to_simple_string(tNowLocal) % currentUrl(), true ) ;
            m_miner->endMining( crawl::miningDoneScriptDoneE );
            emit workDoneSignal(TaskDone::endMining);
        }
        else if ( m_miner->config()->maxPageLoads() && m_miner->infoPageLoadsTotal() >= m_miner->config()->maxPageLoads() ) {
            m_miner->endMining( crawl::miningDoneMaxPageLoadsReachedE );
            emit workDoneSignal(TaskDone::endMining);
        }
    }
    m_isExecutingPhp = false;
}


void MinerWorker::runPhpSnippetSlot(const QString& phpCode)
{
    m_isExecutingPhp = true;
    executePhpString( phpCode.toUtf8().data() );
    emit workDoneSignal(TaskDone::runPhpSnippet);
    m_isExecutingPhp = false;
}

bool MinerWorker::isExecutingPhp() const
{
    return m_isExecutingPhp;
}

} // namespace crawl

