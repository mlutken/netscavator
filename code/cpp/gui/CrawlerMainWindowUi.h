#pragma once

#include <boost/signals2/signal.hpp>
#include <QMainWindow>
#include <MinerWorkerIF.h>
#include <interfaces_types.h>

class QResizeEvent;
class MinerCtrl;

namespace crawl {
    class NetscavatorFactoryIF;
    class BrowserViewIF;
}

class CrawlerMainWindowUi : public QMainWindow
{
    Q_OBJECT
public:
    CrawlerMainWindowUi     (crawl::NetscavatorFactoryIF* netscavatorFactory);
    ~CrawlerMainWindowUi    () override;
    void    run             (const QString& scriptAbsPath, crawl::RunModeE rm);
protected:
    void resizeEvent        (QResizeEvent* event) override;
    void closeEvent         ( QCloseEvent *event ) override;

private:
    void updateWindowTitle  (const QString& status);

    crawl::NetscavatorFactoryIF*    m_netscavatorFactory;   // Owned by the "parent" main function
    crawl::BrowserViewIF*           m_browserView = nullptr;
    MinerCtrl*                      m_minerCtrl;
    boost::signals2::connection     m_connectionPageLoaded;
    QString                         m_baseTitle;
};
