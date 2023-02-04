#pragma once

#include <boost/signals2/signal.hpp>
#include <QMainWindow>
#include <MinerWorkerIF.h>
#include <interfaces_types.h>
#include "GuiActionsMgr.h"

class QAction;
class QActionGroup;
class QLabel;
class QMenu;
class QToolBar;
class CreatorMainWidgetUi;
class UrlInputUi;
class QDockWidget;
class QLabel;
class QProgressBar;

class QTextEdit;
class QListWidget;

class OutputViewUi;
class QResizeEvent;

class PhpQuickUi;
class MinerCtrl;
class ScriptCtrl;
class MainToolBarUI;
class DebugToolBarUI;
class BrowserToolBarUI;
class CreatorDomTableView;
class CreatorLinearDomTableModel;
class DomSequencesTreeView;
class UrlQueueTableModel;
class DomSequencesTreeModel;
class DomTreeModel;
class DomTreeView;


namespace crawl {
class NetscavatorFactoryIF;
}

class CreatorMainWindowUi : public QMainWindow
{
    Q_OBJECT

public:
    CreatorMainWindowUi             (crawl::NetscavatorFactoryIF* netscavatorFactory);
    ~CreatorMainWindowUi            () override;
    void    init                    ();
    void    loadPhpScript           ( const QString& scriptAbsPath );
    void    runCrawlerRobot         ( crawl::RunModeE rm );

signals:
    void    loadMinerScriptSignal(const QString& phpMinerScript, const QString& scriptAbsPath);
    void    runSetupFunctionsSignal();
    void    beginMiningEventSignal();
    void    endMiningEventSignal();

    void    matchStepSignal();
    void    mineStepSignal();
    void    navigateStepSignal();

    void    runPhpSnippetSignal (const QString& phpCode);
    void    findText            (const QString& text);
    void    findTextNext        (const QString& text);
    void    findTextAll         (const QString& text);
    void    nodeClick           ();

public slots:
    void    viewWelcomeSlot     ();
    void    viewBrowserSlot     ();
    void    viewEditorSlot      ();
    void    viewDesignSlot      ();
    void    viewHtmlSourceSlot  ();
    void    viewHelpSlot        ();
    void    browserLoadUrlSlot  ();
    void    exitSlot            ();
    void    workDoneSlot        (crawl::MinerWorkerIF::TaskDone done);

    void    netscavatorFactorySet(crawl::NetscavatorFactoryIF* netscavatorFactory);

protected:
    void resizeEvent                ( QResizeEvent* event ) override;
    void contextMenuEvent           ( QContextMenuEvent *event ) override;
    void closeEvent                 ( QCloseEvent *event ) override;


private slots:
    void    setViewSlot             ( int view );
    void    openCrawlerSlot         ();
    void    openCrawlerPathSlot     ( const QString& path ) ;
    void    runCrawlerSlot          ();
    void    executePhpQuickSlot     ();
    void    domFindSlot             (const QString& domSeq);
    void    domFindNextSlot         (const QString& domSeq);
    void    domFindAllSlot          (const QString& domSeq);
    void    nodeClickSlot           ();
    void    debugScriptSlot         ();
    void    reloadScriptSlot        ();
    void    matchPageSlot           ();
    void    refreshUrlQueueModelSlot();


    void newFile();
    void open();
    void saveLayoutSlot();
    void about();
    void aboutQt();

private:

    void    createActions           ();
    void    createDockWindows       ();
    void    createMenus             ();
    void    connectSignalsSlots     ();
    void    updateWindowTitle       (const QString& status);
    void    updateDomSequencesView  ();

    crawl::NetscavatorFactoryIF*    m_netscavatorFactory;   // Owned by the "parent" main function
    int                             m_iCurrentView;
    CreatorMainWidgetUi*            m_mainWidget;
    OutputViewUi*                   m_pDataOutView;
    PhpQuickUi*                     m_phpQuick;
    DomTreeModel*                   m_domTreeModel;
    DomTreeView*                    m_domTreeView;
    CreatorDomTableView*            m_domTableView;
    CreatorLinearDomTableModel*     m_linearDomTableModel;
    MinerCtrl*                      m_minerCtrl;
    ScriptCtrl*                     m_pScriptCtrl;
    boost::signals2::connection     m_connectionPageLoaded;
    QString                         m_baseTitle;

    QMenu*          m_pFileMenu;
    QMenu*          m_pEditMenu;
    MainToolBarUI*  m_pMainToolBar;
    DebugToolBarUI* m_pDebugToolBar;
    QToolBar*       m_pBrowserToolBar;
    UrlInputUi*     m_pUrlInput;

    QDockWidget*    m_pOutputViewDock;
    QDockWidget*    m_domTableViewDock;
    QDockWidget*    m_domTreeViewDock;
    QDockWidget*    m_domSequencesViewDock;
    QDockWidget*    m_pPhpQuickDock;

    DomSequencesTreeView*   m_domSequencesCompactView;
    UrlQueueTableModel*     m_urlQueueTableModel;
    DomSequencesTreeModel*  m_domSequencesTreeModel;

    QMenu *formatMenu;
    QMenu *helpMenu;

    QTextEdit *textEdit;
    QListWidget *customerList;
    QListWidget *paragraphsList;

    QActionGroup *alignmentGroup;
    QAction *newAct;
    QAction *openAct;
    QAction *saveLayoutAct;
    QAction *exitAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
    QLabel *infoLabel;
};

