#include "CreatorMainWindowUi.h"

#include <iostream>
#include <QtGui>
#include <QMenu>
#include <QApplication>
#include <QDockWidget>
#include <QLabel>
#include <QMessageBox>
#include <QMenuBar>
#include <QToolBar>
#include <QProgressBar>

#include <version_info.h>
#include <utils/utils.h>
#include <Globals.h>
#include <Configuration.h>
#include <php_embedding/php_embedding_utils.h>
#include <WelcomeWidgetUi.h>
#include <BrowserWidgetUi.h>
#include <EditorWidgetUi.h>
#include <EditorViewUi.h>
#include <ProjectsViewUi.h>
#include <GuiGlobals.h>
#include <OutputViewUi.h>
#include <PhpQuickUi.h>
#include <CreatorLinearDomTableModel.h>
#include <CreatorDomTableView.h>
#include <CreatorTextDomTreeView.h>
#include <MinerCtrl.h>
#include <ScriptCtrl.h>
#include <ScriptMiner.h>
#include <MinerWorker.h>
#include <ScriptMinerIF.h>
#include <SignalsManager.h>

#include "EditorViewUi.h"
#include "CreatorMainWidgetUi.h"
#include "MainToolBarUI.h"
#include "DebugToolBarUI.h"
#include "HtmlSourceWidgetUi.h"
#include "DesignWidgetUi.h"
#include "DomSequencesTreeViewUi.h"
#include "DomSequencesTreeModel.h"
#include "DomTreeModel.h"
#include "DomTreeView.h"
#include "UrlQueueTableModel.h"

#include "UrlInputUi.h"

using namespace std;
using namespace crawl;

CreatorMainWindowUi::CreatorMainWindowUi(NetscavatorFactoryIF* netscavatorFactory)
    : m_netscavatorFactory  (netscavatorFactory),
      m_iCurrentView        (0)
{
    boost::shared_ptr<crawl::Configuration> c= crawl::g()->configuration();
    GuiGlobals* guiGlobals = new GuiGlobals;
    crawl::g()->guiSet( guiGlobals );

    GuiActionsMgr* guiActionsMgr = new GuiActionsMgr(this) ;
    crawl::g()->guiActionsMgrSet( guiActionsMgr );

    createActions();

    m_urlQueueTableModel        = new UrlQueueTableModel(this);
    m_domSequencesTreeModel     = new DomSequencesTreeModel(this);
    m_domTreeModel = new DomTreeModel(this);
    m_mainWidget = new CreatorMainWidgetUi(m_netscavatorFactory, m_urlQueueTableModel, m_domSequencesTreeModel, this);
    setCentralWidget(m_mainWidget);

    setMinimumSize(160, 160);

    m_pDataOutView          = new OutputViewUi(this);
    m_domTableView          = new CreatorDomTableView(this);

    m_linearDomTableModel   = new CreatorLinearDomTableModel(this);
    m_domTableView->setLinearDomTableModel(m_linearDomTableModel);


    m_domTreeView           = new DomTreeView(this);
    m_domTreeModel          = new DomTreeModel(this);
    m_domTreeView->setDomTreeModel(m_domTreeModel);

    m_phpQuick              = new PhpQuickUi(this);
    m_minerCtrl             = new MinerCtrl(m_netscavatorFactory, this);

    resize(crawl::g()->gui()->mainWindowWidth(), crawl::g()->gui()->mainWindowHeight());
}

CreatorMainWindowUi::~CreatorMainWindowUi    ()
{
    m_connectionPageLoaded.disconnect();

    GuiActionsMgr* pGuiActionsMgr = crawl::g()->guiActionsMgr();
    crawl::g()->guiActionsMgrSet( nullptr );
    delete pGuiActionsMgr;

    GuiGlobals* pGuiGlobals = crawl::g()->gui();
    crawl::g()->guiSet( nullptr );
    delete pGuiGlobals;
}

void CreatorMainWindowUi::netscavatorFactorySet(crawl::NetscavatorFactoryIF* netscavatorFactory)
{
    m_netscavatorFactory = netscavatorFactory;
    if (m_mainWidget)   m_mainWidget->netscavatorFactorySet(netscavatorFactory);
    if (m_minerCtrl)    m_minerCtrl->netscavatorFactorySet(netscavatorFactory);
}


void CreatorMainWindowUi::init()
{
    createMenus();
    createDockWindows();
    connectSignalsSlots();

    // Connect minerWorker signal/slots after m_minerCtrl->init();
    m_minerCtrl->init( m_mainWidget->browserWidgetUi()->curBrowserViewAquire(), m_pDataOutView,
                       /*m_textDomTreeView,*/ m_domTableView, m_linearDomTableModel,
                       m_domTreeModel, m_domTreeView);

    connect(m_minerCtrl->minerWorker(), SIGNAL( workDoneSignal(crawl::MinerWorkerIF::TaskDone) ), this, SLOT( workDoneSlot(crawl::MinerWorkerIF::TaskDone) ));

    m_baseTitle = ("Netscavator (" + versionString() + ") Creator ").c_str();
    updateWindowTitle("");

    auto pageLoadedCb = [this] (crawl::WebBrowserIF& /*browser*/) {
        auto status = crawl::toQString(this->m_minerCtrl->miner()->settingGet("items_mined"));
        status += QString(" / ") + QString::number( this->m_minerCtrl->miner()->urlQueueSize());
        this->updateWindowTitle(status);
        m_mainWidget->htmlSource()->setText(this->m_minerCtrl->miner()->webBrowser()->htmlQString());
    };

    m_connectionPageLoaded = m_minerCtrl->miner()->webBrowser()->signalsManager()->connectPageLoaded(pageLoadedCb);
    updateDomSequencesView();
    refreshUrlQueueModelSlot();
}

void CreatorMainWindowUi::loadPhpScript(const QString &scriptAbsPath)
{
    m_minerCtrl->loadPhpScript(scriptAbsPath);
}

void CreatorMainWindowUi::runCrawlerRobot(crawl::RunModeE rm)
{
    m_minerCtrl->runCrawlerRobot(rm);
}


// PUBLIC: slots
void CreatorMainWindowUi::viewWelcomeSlot ()
{
    setViewSlot(1);
}

void CreatorMainWindowUi::viewBrowserSlot ()
{
    setViewSlot(2);
}



void CreatorMainWindowUi::viewEditorSlot()
{
    QDockWidget* dock1 = findChild<QDockWidget*> ("Customers");
    if (dock1) {
        std::cout << "DEBIG: FOUND dock1" << std::endl;
//        addDockWidget(Qt::RightDockWidgetArea, dock1);
//        restoreDockWidget(dock1);
        //dock1->setVisible(true);
//        QSettings settings("Nitram", "Sleipner Creator");
        QSettings settings;
//        settings.setValue("geometry", saveGeometry());
//        settings.setValue("windowState", saveState(1));
        bool b;
//        b = restoreGeometry(settings.value("geometry").toByteArray());
//        printf("restored 1: %d\n", b);
        b = restoreState(settings.value("windowState").toByteArray(), 1);
        printf("restored 2: %d\n", b);
    }
    setViewSlot(3);
}

void CreatorMainWindowUi::viewDesignSlot()
{
    refreshUrlQueueModelSlot();
    setViewSlot(4);
}

void CreatorMainWindowUi::viewHtmlSourceSlot()
{
    setViewSlot(5);
}

void CreatorMainWindowUi::viewHelpSlot ()
{
    setViewSlot(6);
}

void CreatorMainWindowUi::browserLoadUrlSlot ()
{
    m_mainWidget->browserWidgetUi()->urlSet( QUrl(m_pUrlInput->urlString() ) );
}

void CreatorMainWindowUi::exitSlot ()
{
    close();
}

void CreatorMainWindowUi::workDoneSlot(crawl::MinerWorkerIF::TaskDone done)
{
    switch (done) {
    case MinerWorkerIF::TaskDone::loadMinerScript:
    {
        updateDomSequencesView();
        refreshUrlQueueModelSlot();
        break;
    }
    case MinerWorkerIF::TaskDone::runPhpSnippet:
    {
        const auto domPos = m_minerCtrl->miner()->domPos();
        m_domTableView->selectDomPosSlot(domPos);
        m_domTreeView->selectDomPosSlot(domPos);
        const bool clearCurrentlyMarked = true;
        const auto locatedPositions = m_minerCtrl->miner()->linearDomSearch()->locatedPositions();
        m_minerCtrl->browser()->markPositions(locatedPositions, clearCurrentlyMarked);
//        m_minerCtrl->browser()->markPosition(domPos, clearCurrentlyMarked);

        QApplication::clipboard()->setText( QString::fromUtf8(m_minerCtrl->miner()->valueGet().c_str()) );
        break;
    }
    default:
        break;
    }
}

void CreatorMainWindowUi::resizeEvent(QResizeEvent* event)
{
    crawl::g()->gui()->mainWindowWidthSet(event->size().width());
    crawl::g()->gui()->mainWindowHeightSet(event->size().height());
}


void CreatorMainWindowUi::contextMenuEvent(QContextMenuEvent *event)
{
//    QMenu menu(this);
//    menu.addAction(cutAct);
//    menu.addAction(copyAct);
//    menu.addAction(pasteAct);
//    menu.exec(event->globalPos());
}

void CreatorMainWindowUi::closeEvent(QCloseEvent *event)
 {
     if ( m_mainWidget->editor()->closeCrawlerProjectSlot() ) {
         ///writeSettings();
         event->accept();
     } else {
         event->ignore();
     }
 }

// -------------
// --- SLOTS ---
// -------------
void CreatorMainWindowUi::setViewSlot ( int view )
{
    refreshUrlQueueModelSlot();
    m_mainWidget->setMainViewSlot( view );
}


void CreatorMainWindowUi::openCrawlerSlot()
{
    if ( m_mainWidget->editor()->openCrawlerSlot() ) {
        setViewSlot(3);
        debugScriptSlot();
    }
}

void CreatorMainWindowUi::openCrawlerPathSlot( const QString& path )
{
    if ( m_mainWidget->editor()->openCrawlerPathSlot (path ) ) {
        setViewSlot(3);
        debugScriptSlot();
    }
}

void CreatorMainWindowUi::runCrawlerSlot ()
{
    m_minerCtrl->runCrawler( m_mainWidget->editor()->crawlerEditor(), 0, crawl::rmNormalE );
}


void CreatorMainWindowUi::executePhpQuickSlot ()
{
    m_minerCtrl->runSetupFunctions();
    m_minerCtrl->runPhpSnippet(m_phpQuick->phpString());
    m_minerCtrl->browser()->repaint();
//    m_minerCtrl->runSetupFunctions( m_mainWidget->editor()->crawlerEditor() );
//    executePhpString( m_phpQuick->phpString().c_str() );
//    m_textDomTreeView->selectDomPos( m_minerCtrl->miner()->domGetPos() );
//    QApplication::clipboard()->setText( QString::fromUtf8(m_minerCtrl->miner()->valueGet().c_str()) );

    //m_pMinerCtrl->browser()->webView()->setFocus();
}

void CreatorMainWindowUi::domFindSlot(const QString& domSeq)
{
    m_minerCtrl->runSetupFunctions();
    const QString phpCode = "domFind(\"" + domSeq + "\");";
    m_minerCtrl->runPhpSnippet(phpCode);
    m_minerCtrl->browser()->repaint();
}

void CreatorMainWindowUi::domFindNextSlot(const QString& domSeq)
{
    m_minerCtrl->runSetupFunctions();
    const QString phpCode = "domFindNext(\"" + domSeq + "\");";
    m_minerCtrl->runPhpSnippet(phpCode);
    m_minerCtrl->browser()->repaint();
}

void CreatorMainWindowUi::domFindAllSlot(const QString& domSeq)
{
    m_minerCtrl->runSetupFunctions();
    const QString phpCode = "domFindAll(\"" + domSeq + "\");";
    m_minerCtrl->runPhpSnippet(phpCode);
    m_minerCtrl->browser()->repaint();
}

void CreatorMainWindowUi::nodeClickSlot()
{
    m_minerCtrl->runSetupFunctions();
    const QString phpCode = "nodeClick();";
    m_minerCtrl->runPhpSnippet(phpCode);
    m_minerCtrl->browser()->repaint();
}

void CreatorMainWindowUi::debugScriptSlot ()
{
    m_minerCtrl->runCrawler( m_mainWidget->editor()->crawlerEditor(), nullptr, crawl::rmDesignE );
}

void CreatorMainWindowUi::reloadScriptSlot ()
{
    m_minerCtrl->reloadEditorPhpScript(m_mainWidget->editor()->crawlerEditor());
    m_minerCtrl->runSetupFunctions();

    ////m_minerCtrl->runSetupFunctions( m_mainWidget->editor()->crawlerEditor() );
}

void CreatorMainWindowUi::matchPageSlot ()
{
    QString s = m_minerCtrl->miner()->handlerContextName().c_str();
    m_pDebugToolBar->matchLabelTextSet( s );
}

void CreatorMainWindowUi::refreshUrlQueueModelSlot()
{
    auto miner = m_minerCtrl->miner();
    if (miner) {
        m_urlQueueTableModel->urlQueueSet(&miner->urlQueue());
        m_mainWidget->urlQueueTableModelSet(m_urlQueueTableModel);
    }
}


void CreatorMainWindowUi::newFile()
{
    //infoLabel->setText(tr("Invoked <b>File|New</b>"));
}

void CreatorMainWindowUi::open()
{
    //infoLabel->setText(tr("Invoked <b>File|Open</b>"));
}

void CreatorMainWindowUi::saveLayoutSlot()
{
    printf("Save view\n");
    QSettings settings("Nitram", "SleipnerCreator");
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState(1));
}

void CreatorMainWindowUi::about()
{

    //infoLabel->setText(tr("Invoked <b>Help|About</b>"));
    QString sVersionInfo = "Netscavator ";
    sVersionInfo += tr("version") + " ";
    sVersionInfo += versionString().c_str();
    sVersionInfo += "<br>";
    sVersionInfo += QString("Using embedded PHP version: ") + crawler_php_version_string().c_str();
    sVersionInfo += "<br>";
    sVersionInfo += tr("Copyright");
    sVersionInfo += " 2020 (c) Progvidi.";
    QMessageBox::about(this, tr("About Menu"), sVersionInfo);
}

void CreatorMainWindowUi::aboutQt()
{
    //infoLabel->setText(tr("Invoked <b>Help|About Qt</b>"));
}


void CreatorMainWindowUi::createDockWindows()
{
    m_domTableViewDock = new QDockWidget(tr("Linear DOM"), this);
    m_domTableViewDock->setObjectName("DomTableViewDock");
    m_domTableViewDock->setWidget(m_domTableView);
    addDockWidget(Qt::RightDockWidgetArea, m_domTableViewDock);

    m_domTreeViewDock = new QDockWidget(tr("DOM Tree"), this);
    m_domTreeViewDock->setObjectName("DomTreeViewDock");
    m_domTreeViewDock->setWidget(m_domTreeView);
    addDockWidget(Qt::RightDockWidgetArea, m_domTreeViewDock);

    m_domSequencesCompactView = new DomSequencesTreeView(m_domSequencesTreeModel, DomSequencesTreeView::mode_t::compact, this);
    m_domSequencesViewDock = new QDockWidget(tr("Dom sequences compact"), this);
    m_domSequencesViewDock->setObjectName("DomSeuqencesCompact");
    m_domSequencesViewDock->setWidget(m_domSequencesCompactView);
    addDockWidget(Qt::RightDockWidgetArea, m_domSequencesViewDock);

//    m_pTextDomTreeViewDock = new QDockWidget(tr("Dom text tree"), this);
//    m_pTextDomTreeViewDock->setObjectName("TextDomTreeViewDock");
//    m_pTextDomTreeViewDock->setWidget(m_textDomTreeView);
//    addDockWidget(Qt::RightDockWidgetArea, m_pTextDomTreeViewDock);

    m_pOutputViewDock = new QDockWidget(tr("Output"), this);
    m_pOutputViewDock->setObjectName("DataOutViewDock");
    m_pOutputViewDock->setWidget(m_pDataOutView);
    addDockWidget(Qt::RightDockWidgetArea, m_pOutputViewDock);

    m_pPhpQuickDock   = new QDockWidget(tr("Php quick"), this);
    m_pPhpQuickDock->setObjectName("PhpQuickDock");
    m_pPhpQuickDock->setWidget(m_phpQuick);
    addDockWidget(Qt::RightDockWidgetArea, m_pPhpQuickDock);

    // Chaining docked widgets when tabifying!
    //    m_domTreeViewDock  : 1
    //    m_domTableViewDock : 2
    //    m_pOutputViewDock  : 3
    //    tabifyDockWidget(1, 2)
    //    tabifyDockWidget(2, 3)

    tabifyDockWidget ( m_domTreeViewDock, m_domTableViewDock  );
    tabifyDockWidget ( m_domTableViewDock,  m_pOutputViewDock);
    tabifyDockWidget ( m_domSequencesViewDock, m_pPhpQuickDock  );
}




void CreatorMainWindowUi::createActions()
{
    boost::shared_ptr<crawl::Configuration> c= crawl::g()->configuration();
    std::string imagesDir = c->valueStrGet("resource-dir") + "/images/";

    newAct = new QAction(QIcon( (imagesDir+"new.png").c_str() ), tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    saveLayoutAct = new QAction(tr("&Layout save"), this);
    ////saveLayoutAct->setShortcuts(QKeySequence::Save);
    saveLayoutAct->setStatusTip(tr("Save layout"));
    connect(saveLayoutAct, SIGNAL(triggered()), this, SLOT(saveLayoutSlot()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(aboutQtAct, SIGNAL(triggered()), this, SLOT(aboutQt()));

}

void CreatorMainWindowUi::createMenus()
{
    GuiActionsMgr* pAMgr = crawl::g()->guiActionsMgr();


    // --- File (Editor) menu ---
    m_pFileMenu = menuBar()->addMenu(tr("&File"));
    m_pFileMenu->addAction(pAMgr->byName("new_crawler"));
    m_pFileMenu->addAction(pAMgr->byName("new_php_file"));
//    m_pFileMenu->addAction(pAMgr->byName("new_file"));
    m_pFileMenu->addAction(pAMgr->byName("open_crawler"));
    m_pFileMenu->addAction(pAMgr->byName("open_file"));
    m_pFileMenu->addSeparator();
    m_pFileMenu->addAction(pAMgr->byName("close_crawler"));
    m_pFileMenu->addAction(pAMgr->byName("close_file"));
    m_pFileMenu->addSeparator();
    m_pFileMenu->addAction(pAMgr->byName("save"));
    m_pFileMenu->addAction(pAMgr->byName("save_crawler_as"));
    m_pFileMenu->addAction(pAMgr->byName("save_file_as"));
    m_pFileMenu->addSeparator();
    m_pFileMenu->addAction(pAMgr->byName("print"));
    m_pFileMenu->addSeparator();
    m_pFileMenu->addAction(pAMgr->byName("exit"));

//    m_pFileMenu->addSeparator();
//    m_pFileMenu->addAction(saveLayoutAct);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);

    // --- Main Toolbar ---
    m_pMainToolBar = new MainToolBarUI( tr("Main"), pAMgr, this);
    m_pMainToolBar->setObjectName("MainToolbar");
    addToolBar( Qt::LeftToolBarArea, m_pMainToolBar);


    // --- Debug Toolbar ---
    m_pDebugToolBar = new DebugToolBarUI( tr("Debug"), pAMgr, this);
    m_pDebugToolBar->setObjectName("DebugToolbar");
    addToolBar( Qt::BottomToolBarArea, m_pDebugToolBar);


    // --- Browser Toolbar ---
    m_pBrowserToolBar = new QToolBar( tr("Browser"), this);
    m_pBrowserToolBar->setObjectName("BrowserToolbar");
//    m_pBrowserToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    m_pBrowserToolBar->setIconSize(QSize(24,24) );
    m_pBrowserToolBar->addAction(pAMgr->byName("browser_back") );
    m_pBrowserToolBar->addAction(pAMgr->byName("browser_forward") );
    m_pBrowserToolBar->addAction(pAMgr->byName("new_browser") );
    m_pUrlInput = new UrlInputUi(this);
    m_pBrowserToolBar->addWidget(m_pUrlInput);

//    m_pageLoadProgressBar = new QProgressBar(this);
//    m_pageLoadProgressBar->setRange(0,100);
//    m_pageLoadProgressBar->setMinimumWidth(100);
//    m_pageLoadProgressBar->setMaximumWidth(100);
//    m_pBrowserToolBar->addWidget(m_pageLoadProgressBar);

    m_pBrowserToolBar->addAction(pAMgr->byName("load_url") );
    addToolBar( Qt::TopToolBarArea, m_pBrowserToolBar);
}

void CreatorMainWindowUi::connectSignalsSlots()
{
    GuiActionsMgr* pAMgr = crawl::g()->guiActionsMgr();

    // --- Main toolbar ---
    connect(pAMgr->byName("welcome"), SIGNAL(triggered()), this, SLOT(viewWelcomeSlot()));
    connect(pAMgr->byName("browser"), SIGNAL(triggered()), this, SLOT(viewBrowserSlot()));
    connect(pAMgr->byName("crawler_editor"), SIGNAL(triggered()), this, SLOT(viewEditorSlot()));
    connect(pAMgr->byName("design"), SIGNAL(triggered()), this, SLOT(viewDesignSlot()));
    connect(pAMgr->byName("htmlsource"), SIGNAL(triggered()), this, SLOT(viewHtmlSourceSlot()));
    connect(pAMgr->byName("help"), SIGNAL(triggered()), this, SLOT(viewHelpSlot()));
    connect(pAMgr->byName("run"), SIGNAL(triggered()), this, SLOT(runCrawlerSlot()));
    connect(pAMgr->byName("debug"), SIGNAL(triggered()), this, SLOT(debugScriptSlot()));
    connect(pAMgr->byName("reload_script"), SIGNAL(triggered()), this, SLOT(reloadScriptSlot()));
    connect(pAMgr->byName("stop"), SIGNAL(triggered()), m_minerCtrl , SLOT(stopMiningSlot()));

    // --- Debug toolbar ---
    connect(pAMgr->byName("force_page_loaded"), SIGNAL(triggered()), m_minerCtrl , SLOT(forcePageLoadedSlot()));
    connect(pAMgr->byName("next_step"), SIGNAL(triggered()), m_minerCtrl , SLOT(nextStepSlot()));
    connect(pAMgr->byName("match_step"), SIGNAL(triggered()), m_minerCtrl , SLOT(matchStepSlot()));
    connect(pAMgr->byName("mine_step"), SIGNAL(triggered()), m_minerCtrl , SLOT(mineStepSlot()));
    connect(pAMgr->byName("navigate_step"), SIGNAL(triggered()), m_minerCtrl , SLOT(navigateStepSlot()));
    connect(m_minerCtrl, SIGNAL(onMatchPage()), this , SLOT(matchPageSlot()));

    QObject::connect(pAMgr->byName("find"), &QAction::triggered, [this]()
        {
            const QString textToFind = m_pDebugToolBar->textToFind();
            this->emit findText(textToFind);
        }
    );

    QObject::connect(pAMgr->byName("findnext"), &QAction::triggered, [this]()
        {
            const QString textToFind = m_pDebugToolBar->textToFind();
            this->emit findTextNext(textToFind);
        }
    );

    QObject::connect(pAMgr->byName("findall"), &QAction::triggered, [this]()
        {
            const QString textToFind = m_pDebugToolBar->textToFind();
            this->emit findTextAll(textToFind);
        }
    );

    QObject::connect(pAMgr->byName("nodeclick"), &QAction::triggered, [this]()
        {
            this->emit nodeClick();
        }
    );

////    connect(m_pUrlInput, SIGNAL(urlChanged(QString)), this, SLOT(urlChangedSlot(QString)));
    connect(m_pUrlInput, SIGNAL(urlChanged(QString)), m_mainWidget->browserWidgetUi(), SLOT(urlSetSlot(QString)));
    connect(m_mainWidget->browserWidgetUi(), SIGNAL(urlChangedSignal(QString)), m_pUrlInput, SLOT(urlSetSlot(QString)));
    connect(pAMgr->byName("browser_back"), SIGNAL(triggered()), m_mainWidget->browserWidgetUi(), SLOT(backSlot()));
    connect(pAMgr->byName("browser_forward"), SIGNAL(triggered()), m_mainWidget->browserWidgetUi(), SLOT(forwardSlot()));
    connect(pAMgr->byName("new_browser"), SIGNAL(triggered()), m_mainWidget->browserWidgetUi(), SLOT(newBrowserTabSlot()));
    connect(pAMgr->byName("load_url"), SIGNAL(triggered()), this, SLOT(browserLoadUrlSlot()));
    connect(m_phpQuick, SIGNAL(executePhpQuick()), this, SLOT(executePhpQuickSlot()) );



    // --- File menu ---
    connect(pAMgr->byName("new_crawler"), SIGNAL(triggered()), m_mainWidget->editor(), SLOT(newCrawlerSlot()));
//    connect(pAMgr->byName("new_file"), SIGNAL(triggered()), m_pMainWidget->editor(), SLOT(newFileSlot()));
    connect(pAMgr->byName("new_php_file"), SIGNAL(triggered()), m_mainWidget->editor(), SLOT(newPhpFileSlot()));
    connect(pAMgr->byName("open_crawler"), SIGNAL(triggered()), this, SLOT(openCrawlerSlot()));
    connect(pAMgr->byName("open_file"), SIGNAL(triggered()), m_mainWidget->editor(), SLOT(openFileSlot()));
    connect(pAMgr->byName("close_crawler"), SIGNAL(triggered()), m_mainWidget->editor(), SLOT(closeCrawlerProjectSlot()));
    connect(pAMgr->byName("close_file"), SIGNAL(triggered()), m_mainWidget->editor(), SLOT(closeFileSlot()));
    connect(pAMgr->byName("save"), SIGNAL(triggered()), m_mainWidget->editor(), SLOT(saveFileSlot()));
    connect(pAMgr->byName("save_crawler_as"), SIGNAL(triggered()), m_mainWidget->editor(), SLOT(saveCrawlerAsSlot()));
    connect(pAMgr->byName("save_file_as"), SIGNAL(triggered()), m_mainWidget->editor(), SLOT(saveFileAsSlot()));
    connect(pAMgr->byName("exit"), SIGNAL(triggered()), this, SLOT(exitSlot()));


    // --- Recent crawler projects ---
    connect(m_mainWidget->welcome()->projects(), SIGNAL(openCrawlerSignal (const QString&)), this, SLOT( openCrawlerPathSlot (const QString&) ));

    // --- Miner actions ---
    connect(m_mainWidget->browserWidgetUi(), &BrowserWidgetUi::domPosSelectedSig, m_minerCtrl, &MinerCtrl::domPosSelectedSlot);
    connect(m_mainWidget->browserWidgetUi(), &BrowserWidgetUi::elementSelected, m_minerCtrl, &MinerCtrl::webElementSelectedSlot);
    connect(m_mainWidget->browserWidgetUi(), &BrowserWidgetUi::currentBrowserChanged, m_minerCtrl, &MinerCtrl::browserChangedSlot);

    // --- Editor actions ---
    connect(this, SIGNAL(findText(const QString&)), m_mainWidget->editor()->crawlerEditor(), SLOT(findTextSlot(const QString&) ));
    connect(this, SIGNAL(findText(const QString&)), m_mainWidget->htmlSource(), SLOT(findTextSlot(const QString&) ));
    connect(this, SIGNAL(findText(const QString&)), this, SLOT(domFindSlot(const QString&) ));

    connect(this, SIGNAL(findTextNext(const QString&)), m_mainWidget->editor()->crawlerEditor(), SLOT(findTextNextSlot(const QString&) ));
    connect(this, SIGNAL(findTextNext(const QString&)), m_mainWidget->htmlSource(), SLOT(findTextNextSlot(const QString&) ));
    connect(this, SIGNAL(findTextNext(const QString&)), this, SLOT(domFindNextSlot(const QString&) ));

    connect(this, SIGNAL(findTextAll(const QString&)), this, SLOT(domFindAllSlot(const QString&) ));

    connect(this, SIGNAL(nodeClick()), this, SLOT(nodeClickSlot() ));

    // --- Dom sequences editor actions ---
/////    DomSequencesViewUi* domSeqViewDesign = m_mainWidget->design()->urlQueueTableView();

    DomSequencesTreeView* domSeqTreeViewDesign = m_mainWidget->design()->domSeqTreeView();
    connect(domSeqTreeViewDesign, &DomSequencesTreeView::domFind, this, &CreatorMainWindowUi::domFindSlot);
    connect(domSeqTreeViewDesign, &DomSequencesTreeView::domFindNext, this, &CreatorMainWindowUi::domFindNextSlot);
    connect(domSeqTreeViewDesign, &DomSequencesTreeView::domFindAll, this, &CreatorMainWindowUi::domFindAllSlot);

    connect(m_domSequencesCompactView, &DomSequencesTreeView::domFind, this, &CreatorMainWindowUi::domFindSlot);
    connect(m_domSequencesCompactView, &DomSequencesTreeView::domFindNext, this, &CreatorMainWindowUi::domFindNextSlot);
    connect(m_domSequencesCompactView, &DomSequencesTreeView::domFindAll, this, &CreatorMainWindowUi::domFindAllSlot);

}

void CreatorMainWindowUi::updateWindowTitle(const QString& status)
{
    QString scriptName{};
    if (m_minerCtrl && m_minerCtrl->editorView()) {
        scriptName = m_minerCtrl->editorView()->leafFileName();
    }
    setWindowTitle(m_baseTitle + "[" + scriptName + "] : " + status);
}

void CreatorMainWindowUi::updateDomSequencesView()
{
    auto miner = m_minerCtrl->miner();
    if (miner) {
        m_domSequencesTreeModel->domSearchMgrSet(miner->domSearchMgr());
        m_mainWidget->domSequencesTreeModelSet(m_domSequencesTreeModel);
        m_domSequencesCompactView->domSequencesTreeModelSet(m_domSequencesTreeModel);
    }
}

