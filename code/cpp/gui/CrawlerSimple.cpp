#include "CrawlerSimple.h"

#include <MinerCtrl.h>
#include <NetscavatorFactoryIF.h>
#include <BrowserViewIF.h>

using namespace crawl;

CrawlerSimple::CrawlerSimple(NetscavatorFactoryIF* netscavatorFactory)
    : QObject (),
      m_netscavatorFactory  (netscavatorFactory)
{
    m_browserView = m_netscavatorFactory->createBrowserView(this);
    m_minerCtrl = new MinerCtrl(m_netscavatorFactory, this);
}

void CrawlerSimple::run(const QString& scriptAbsPath, RunModeE rm)
{
    m_minerCtrl->init(m_browserView, nullptr, nullptr, nullptr, nullptr, nullptr);
    m_minerCtrl->loadPhpScript(scriptAbsPath);
    m_minerCtrl->runCrawlerRobot(rm);
}
