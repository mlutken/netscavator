#ifndef BROWSERWIDGETUI_H
#define BROWSERWIDGETUI_H

#include <QWidget>
#include <QUrl>
#include <BrowserViewIF.h>

class QTabWidget;

namespace crawl {
class NetscavatorFactoryIF;
}

class BrowserWidgetUi : public QWidget
{
    Q_OBJECT
public:
    explicit    BrowserWidgetUi         (crawl::NetscavatorFactoryIF* netscavatorFactory, QWidget *parent = nullptr);
    void        netscavatorFactorySet   (crawl::NetscavatorFactoryIF* netscavatorFactory);

    void                    addBrowserTab           (const QUrl& url);
    crawl::BrowserViewIF*   currentBrowserView      () const;
    crawl::BrowserViewIF*   browserView             (int index) const;
    crawl::BrowserViewIF*   curBrowserView          () const;
    crawl::BrowserViewIF*   curBrowserViewAquire    ();
    void                    curBrowserViewRelease   ();
    void                    urlSet                  (const QUrl& url);
    QUrl                    url                     () const;

signals:
    void                    domPosSelectedSig       (const QString& xpath, const QString& innerText);
    void                    elementSelected         (crawl::BrowserViewIF* pWebView);
    void                    urlChangedSignal        (const QString& url);
    void                    currentTabChanged       (int index);
    void                    currentBrowserChanged   (crawl::BrowserViewIF* pWebView);
    void                    pageLoadedSignal        ();

public slots:
    void                    newBrowserTabSlot       ();
    void                    urlSetSlot              (const QString& url);
    void                    backSlot                () const;
    void                    forwardSlot             () const;

private slots:
    void                    domPosSelectedSlot      (const QString& xpath, const QString& innerText);
    void                    webElementSelectedSlot  (crawl::BrowserViewIF* pWebView);
    void                    browserWidgetPageLoadedSlot          (crawl::BrowserViewIF* pWebView, bool ok);
    void                    tabChangedSlot          (int index);
    void                    tabCloseRequestedSlot   (int index);

private:
    QWidget*                browserViewToWidget     (crawl::BrowserViewIF* browserView);

    crawl::NetscavatorFactoryIF*                m_netscavatorFactory;   // Owned by the "parent" main function
    QTabWidget*                                 m_pTabs;
    crawl::BrowserViewIF*                       m_pCurrentCrawlerBrowser;
    std::map<QWidget*, crawl::BrowserViewIF*>   m_widgetToViewMap;
};

#endif // BROWSERWIDGETUI_H
