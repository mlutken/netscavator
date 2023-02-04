#ifndef CRAWLER_SIMPLE_H
#define CRAWLER_SIMPLE_H

#include <QObject>
#include <MinerWorkerIF.h>
#include <interfaces_types.h>

class MinerCtrl;

namespace crawl {
    class NetscavatorFactoryIF;
    class BrowserViewIF;
}

class CrawlerSimple : public QObject
{
    Q_OBJECT
public:
    CrawlerSimple     (crawl::NetscavatorFactoryIF* netscavatorFactory);
    void    run       (const QString& scriptAbsPath, crawl::RunModeE rm);

private:
    crawl::NetscavatorFactoryIF*    m_netscavatorFactory;   // Owned by the "parent" main function
    crawl::BrowserViewIF*           m_browserView = nullptr;
    MinerCtrl*                      m_minerCtrl;
};

#endif //CRAWLER_SIMPLE_H
