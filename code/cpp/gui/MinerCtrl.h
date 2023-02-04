#pragma once

#include <QObject>
#include <boost/shared_ptr.hpp>
#include <interfaces_types.h>

class OutputViewUi;
class CreatorLinearDomTableModel;
class CreatorDomTableView;
class DomTreeModel;
class DomTreeView;
class ScriptMiner;
class EditorViewUi;
class QThread;
class QTimer;

namespace crawl {
    class WebBrowserIF;
    class BrowserViewIF;
    class DataWriterXml;
    class OutputViewCtrl;
    class LinearDomIF;
    class MinerWorker;
    class ScriptExecutor;
    class NetscavatorFactoryIF;
    class ScriptMinerIF;
}

class MinerCtrl : public QObject
{
    Q_OBJECT
public:
    explicit MinerCtrl(crawl::NetscavatorFactoryIF* netscavatorFactory, QObject *parent = nullptr);
    boost::shared_ptr<crawl::WebBrowserIF>      browser     ()   { return m_pBrowser; }
    boost::shared_ptr<crawl::ScriptMinerIF>     miner       ();
    void                                        setWebView  (crawl::BrowserViewIF* pWebViewBrowser);
    crawl::MinerWorker*                         minerWorker () const;
    EditorViewUi*                               editorView () const;
    void    netscavatorFactorySet       (crawl::NetscavatorFactoryIF* netscavatorFactory);

    void    init                        (crawl::BrowserViewIF* pWebViewBrowser, OutputViewUi* pDataOutView,
                                        CreatorDomTableView* domTableView, CreatorLinearDomTableModel* linearDomTableModel,
                                         DomTreeModel* domTreeModel, DomTreeView* domTreeView);
    void    loadPhpScript               (const QString& scriptAbsPath);
    void    reloadEditorPhpScript       (EditorViewUi* editorView);
    void    runCrawler                  (EditorViewUi* editorView, crawl::BrowserViewIF* pWebViewBrowser, crawl::RunModeE rm);
    void    runCrawlerRobot             (crawl::RunModeE rm);
    void    runSetupFunctions           ();
    void    runPhpSnippet               (const QString& phpCode);

signals:
    void    startUpPhpSignal            ();

    void    loadMinerScriptSignal       (const QString& phpMinerScript, const QString& scriptAbsPath);
    void    runSetupFunctionsSignal     ();
    void    beginMiningSignal           (bool restart);
    void    endMiningSignal             ();

    void    matchStepSignal             ();
    void    mineStepSignal              ();
    void    navigateStepSignal          ();

    void    runPhpSnippetSignal         (const QString& phpCode);

    void    onMatchPage();

public slots:
    void        stopMiningSlot          ();
    void        nextStepSlot            ();
    void        forcePageLoadedSlot     ();
    void        matchStepSlot           ();
    void        mineStepSlot            ();
    void        navigateStepSlot        ();
    void        webElementSelectedSlot  (crawl::BrowserViewIF* pWebView);
    void        domPosSelectedSlot      (const QString& xpath, const QString& innerText);
    void        browserChangedSlot      (crawl::BrowserViewIF* pWebView);
private:
    // ---------------------------------
    // --- PRIVATE: Helper functions ---
    // ---------------------------------
    void        updateDomTreeViews      ();
    void        pageLoadedSlot          (crawl::WebBrowserIF& browser);
    void        domChangedSlot          (crawl::WebBrowserIF& browser);
    void        onMatchPageSlot         ();
    int         phpStartupCallback      (struct _sapi_module_struct *sapi_module);
    void        miningDoneSlot          ();

    // ---------------------
    // --- PRIVATE: Data ---
    // ---------------------
    crawl::NetscavatorFactoryIF*                m_netscavatorFactory;   // Owned by the "parent" main function
    boost::shared_ptr<crawl::WebBrowserIF>      m_pBrowser;
    boost::shared_ptr<ScriptMiner>              m_pMiner;
    boost::shared_ptr<crawl::OutputViewCtrl>    m_pOutputViewCtrl;

    EditorViewUi*                               m_editorView            = nullptr;
    crawl::BrowserViewIF*                       m_pWebViewBrowser       = nullptr;
    CreatorDomTableView*                        m_domTableView          = nullptr;
    CreatorLinearDomTableModel*                 m_linearDomTableModel   = nullptr;
    DomTreeModel*                               m_domTreeModel          = nullptr;
    DomTreeView*                                m_domTreeView           = nullptr;
    OutputViewUi*                               m_pDataOutView          = nullptr;
};
