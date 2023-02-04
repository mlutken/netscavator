#include "CrawlerMainWindowUi.h"

#include <QResizeEvent>

#include <version_info.h>
#include <utils/utils.h>
#include <Globals.h>
#include <Configuration.h>
#include <BrowserWidgetUi.h>
#include <GuiGlobals.h>
#include <MinerCtrl.h>
#include <NetscavatorFactoryIF.h>
#include <BrowserViewIF.h>
#include <ScriptMinerIF.h>
#include <SignalsManager.h>

using namespace std;
using namespace crawl;

CrawlerMainWindowUi::CrawlerMainWindowUi(NetscavatorFactoryIF* netscavatorFactory)
    : m_netscavatorFactory  (netscavatorFactory)
{
    // TODO: Use Configuration from netscavatorFactory
    boost::shared_ptr<crawl::Configuration> c= crawl::g()->configuration();
    GuiGlobals* guiGlobals = new GuiGlobals;
    crawl::g()->guiSet( guiGlobals );
    m_baseTitle = ("Netscavator (" + versionString() + ") Webkit Crawler [" + c->valueStrGet("script-name") + "] : " + c->phpArgsStr()).c_str();
    updateWindowTitle("");
    setMinimumSize(0, 0);

    m_browserView = m_netscavatorFactory->createBrowserView(this);
    m_browserView->setUrl(QUrl(""));
    setCentralWidget(m_browserView->widgetPtr());
    m_minerCtrl = new MinerCtrl(m_netscavatorFactory, this);

    resize(crawl::g()->gui()->mainWindowWidth(), crawl::g()->gui()->mainWindowHeight());
}

CrawlerMainWindowUi::~CrawlerMainWindowUi()
{
    m_connectionPageLoaded.disconnect();
}

void CrawlerMainWindowUi::run(const QString& scriptAbsPath, RunModeE rm)
{
    m_minerCtrl->init(m_browserView, nullptr, nullptr, nullptr, nullptr, nullptr);

    auto pageLoadedCb = [this] (crawl::WebBrowserIF& /*browser*/) {
        auto status = crawl::toQString(this->m_minerCtrl->miner()->settingGet("items_mined"));
        status += QString(" / ") + QString::number( this->m_minerCtrl->miner()->urlQueueSize());
        this->updateWindowTitle(status);
    };

    m_connectionPageLoaded = m_minerCtrl->miner()->webBrowser()->signalsManager()->connectPageLoaded(pageLoadedCb);
    m_minerCtrl->loadPhpScript(scriptAbsPath);
    m_minerCtrl->runCrawlerRobot(rm);
    show();
}

void CrawlerMainWindowUi::resizeEvent(QResizeEvent* event)
{
    crawl::g()->gui()->mainWindowWidthSet(event->size().width());
    crawl::g()->gui()->mainWindowHeightSet(event->size().height());
    crawl::g()->gui()->writeToSettings();
}

void CrawlerMainWindowUi::closeEvent(QCloseEvent* event)
{
    m_minerCtrl->miner()->webBrowser()->signalsManager()->signalOnClose();
    event->accept();
}

void CrawlerMainWindowUi::updateWindowTitle(const QString& status)
{
    setWindowTitle(m_baseTitle + " " + status);
}
