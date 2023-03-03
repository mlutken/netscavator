#include "GuiActionsMgr.h"
#include <QAction>
#include <QtGui>
#include <QMainWindow>

#include <Globals.h>
#include <Configuration.h>
#include <cpaf_libs/utils/cpaf_stl_utils.h>

GuiActionsMgr::GuiActionsMgr(QMainWindow* pMainWindow)
    : m_pMainWindow(pMainWindow)
{
    boost::shared_ptr<crawl::Configuration> c= crawl::g()->configuration();
    QAction* pAction;

    // --- Main toolbar actions ---
    pAction = new QAction(QIcon(":/data/icons/128x128/welcome.png"), QObject::tr("&Welcome"), pMainWindow);
    pAction->setIconText(QObject::tr("Welcome"));
    pAction->setToolTip(QObject::tr("New project, examples ..."));
    m_actionsMap["welcome"] = pAction;

    pAction = new QAction(QIcon(":/data/icons/128x128/browser.png"), QObject::tr("&Browser"), pMainWindow);
    pAction->setIconText(QObject::tr("Browser"));
    pAction->setToolTip(QObject::tr("Browser view"));
    m_actionsMap["browser"] = pAction;

    pAction = new QAction(QIcon(":/data/icons/128x128/crawler_editor.png"), QObject::tr("&Crawler editor"), pMainWindow);
    pAction->setIconText(QObject::tr("Script"));
    pAction->setToolTip(QObject::tr("Script editor"));
    m_actionsMap["crawler_editor"] = pAction;

    pAction = new QAction(QIcon(":/data/icons/128x128/design.png"), QObject::tr("&Design"), pMainWindow);
    pAction->setIconText(QObject::tr("Design"));
    pAction->setToolTip(QObject::tr("Design"));
    m_actionsMap["design"] = pAction;

    pAction = new QAction(QIcon(":/data/icons/128x128/htmlsource.png"), QObject::tr("&Html source"), pMainWindow);
    pAction->setIconText(QObject::tr("Html source"));
    pAction->setToolTip(QObject::tr("Html source"));
    m_actionsMap["htmlsource"] = pAction;

    pAction = new QAction(QIcon(":/data/icons/128x128/help.png"), QObject::tr("&Help"), pMainWindow);
    pAction->setIconText(QObject::tr("Help"));
    pAction->setToolTip(QObject::tr("Help"));
    m_actionsMap["help"] = pAction;

    // --- Run actions ---
    pAction = new QAction(QIcon(":/data/icons/128x128/blank.png"), QObject::tr(""), pMainWindow);
    m_actionsMap["blank"] = pAction;

    pAction = new QAction(QIcon(":/data/icons/128x128/reload_script.png"), QObject::tr("&Reload script"), pMainWindow);
    pAction->setIconText(QObject::tr("Reload script"));
    pAction->setToolTip(QObject::tr("Reload script"));
    m_actionsMap["reload_script"] = pAction;

    pAction = new QAction(QIcon(":/data/icons/128x128/run.png"), QObject::tr("&Run"), pMainWindow);
    pAction->setIconText(QObject::tr("Run"));
    pAction->setToolTip(QObject::tr("Run"));
    m_actionsMap["run"] = pAction;

    pAction = new QAction(QIcon(":/data/icons/128x128/stop.png"), QObject::tr("&Stop"), pMainWindow);
    pAction->setIconText(QObject::tr("Stop"));
    pAction->setToolTip(QObject::tr("Stop"));
    m_actionsMap["stop"] = pAction;

    pAction = new QAction(QIcon(":/data/icons/128x128/pause.png"), QObject::tr("&Pause"), pMainWindow);
    pAction->setIconText(QObject::tr("Pause"));
    pAction->setToolTip(QObject::tr("Pause"));
    m_actionsMap["pause"] = pAction;

    // --- Debug actions ---
    pAction = new QAction(QIcon(":/data/icons/128x128/debug.png"), QObject::tr("&Debug"), pMainWindow);
    pAction->setIconText(QObject::tr("Debug"));
    pAction->setToolTip(QObject::tr("Start debugging session"));
    m_actionsMap["debug"] = pAction;

    pAction = new QAction(QIcon(":/data/icons/128x128/force_page_loaded.png"), QObject::tr("&Force page loaded"), pMainWindow);
    pAction->setIconText(QObject::tr("Force loaded"));
    pAction->setToolTip(QObject::tr("Force page loaded"));
    m_actionsMap["force_page_loaded"] = pAction;

    pAction = new QAction(QIcon(":/data/icons/128x128/next_step.png"), QObject::tr("&Next step"), pMainWindow);
    pAction->setIconText(QObject::tr("Next"));
    pAction->setToolTip(QObject::tr("Next step"));
    m_actionsMap["next_step"] = pAction;

    pAction = new QAction(QIcon(":/data/icons/128x128/match_step.png"), QObject::tr("&Match step"), pMainWindow);
    pAction->setIconText(QObject::tr("Match"));
    pAction->setToolTip(QObject::tr("Match step"));
    m_actionsMap["match_step"] = pAction;

    pAction = new QAction(QIcon( ":/data/icons/128x128/mine_step.png"), QObject::tr("&Mine step"), pMainWindow);
    pAction->setIconText(QObject::tr("Mine"));
    pAction->setToolTip(QObject::tr("Mine step"));
    m_actionsMap["mine_step"] = pAction;

    pAction = new QAction(QIcon( ":/data/icons/128x128/navigate_step.png"), QObject::tr("&Navigate step"), pMainWindow);
    pAction->setIconText(QObject::tr("Navigate"));
    pAction->setToolTip(QObject::tr("Navigate step"));
    m_actionsMap["navigate_step"] = pAction;

    pAction = new QAction(QIcon(":/data/icons/128x128/find.png"), QObject::tr("&Find"), pMainWindow);
    pAction->setIconText(QObject::tr("Find"));
    pAction->setToolTip(QObject::tr("Find"));
    m_actionsMap["find"] = pAction;

    pAction = new QAction( QIcon(":/data/icons/128x128/findnext.png"), QObject::tr("&Find next"), pMainWindow);
    pAction->setIconText(QObject::tr("Find next"));
    pAction->setToolTip(QObject::tr("Find next"));
    m_actionsMap["findnext"] = pAction;

    pAction = new QAction(QIcon( ":/data/icons/128x128/findall.png"), QObject::tr("&Find all"), pMainWindow);
    pAction->setIconText(QObject::tr("Find all"));
    pAction->setToolTip(QObject::tr("Find all"));
    m_actionsMap["findall"] = pAction;

    pAction = new QAction(QIcon( ":/data/icons/128x128/nodeclick.png" ), QObject::tr("Click"), pMainWindow);
    pAction->setIconText(QObject::tr("nodeClick"));
    pAction->setToolTip(QObject::tr("Click on current node"));
    m_actionsMap["nodeclick"] = pAction;

    // --- Browser actions ---
    pAction = new QAction(QIcon( ":/data/icons/128x128/load_url.png"), QObject::tr("&Load url"), pMainWindow);
    pAction->setIconText(QObject::tr("Load"));
    pAction->setToolTip(QObject::tr("Load url"));
    m_actionsMap["load_url"] = pAction;

    pAction = new QAction(QIcon( ":/data/icons/128x128/new_browser.png"), QObject::tr("New browser &tab"), pMainWindow);
    pAction->setIconText(QObject::tr("New"));
    pAction->setToolTip(QObject::tr("New browser tab"));
    m_actionsMap["new_browser"] = pAction;

    pAction = new QAction(QIcon( ":/data/icons/128x128/browser_back.png" ), QObject::tr("Browser &back"), pMainWindow);
    pAction->setIconText(QObject::tr("Back"));
    pAction->setToolTip(QObject::tr("Browser back"));
    m_actionsMap["browser_back"] = pAction;

    pAction = new QAction(QIcon( ":/data/icons/128x128/browser_forward.png"), QObject::tr("Browser &forward"), pMainWindow);
    pAction->setIconText(QObject::tr("Forward"));
    pAction->setToolTip(QObject::tr("Browser forward"));
    m_actionsMap["browser_forward"] = pAction;


    // --- File menu actions ---
    pAction = new QAction(QIcon(":/data/icons/48x48/new.png"), QObject::tr("New crawler"), pMainWindow);
    pAction->setIconText(QObject::tr("New crawler project"));
    pAction->setToolTip(QObject::tr("New crawler project"));
    m_actionsMap["new_crawler"] = pAction;

    pAction = new QAction(QIcon(":/data/icons/48x48/new_file.png"), QObject::tr("New file"), pMainWindow);
    pAction->setIconText(QObject::tr("New file"));
    pAction->setToolTip(QObject::tr("New file"));
    m_actionsMap["new_file"] = pAction;

    pAction = new QAction(QIcon(":/data/icons/48x48/new_php_file.png"), QObject::tr("New php file"), pMainWindow);
    pAction->setIconText(QObject::tr("New php file"));
    pAction->setToolTip(QObject::tr("New php file"));
    m_actionsMap["new_php_file"] = pAction;

    pAction = new QAction(QIcon(":/data/icons/48x48/open_crawler.png"), QObject::tr("Open crawler"), pMainWindow);
    pAction->setIconText(QObject::tr("Open crawler project"));
    pAction->setToolTip(QObject::tr("Open crawler project"));
    m_actionsMap["open_crawler"] = pAction;

    pAction = new QAction(QIcon(":/data/icons/48x48/save.png"), QObject::tr("Save"), pMainWindow);
    pAction->setShortcuts(QKeySequence::Save);
    pAction->setIconText(QObject::tr("Save crawler/file"));
    pAction->setToolTip(QObject::tr("Save current active crawler or file tab"));
    m_actionsMap["save"] = pAction;

    pAction = new QAction(QIcon(), QObject::tr("Save crawler as"), pMainWindow);
    pAction->setIconText(QObject::tr("Save crawler as ..."));
    pAction->setToolTip(QObject::tr("Save crawler project as another name"));
    m_actionsMap["save_crawler_as"] = pAction;

    pAction = new QAction(QIcon(), QObject::tr("Close crawler"), pMainWindow);
    pAction->setIconText(QObject::tr("Close crawler project"));
    pAction->setToolTip(QObject::tr("Close crawler project"));
    m_actionsMap["close_crawler"] = pAction;


    pAction = new QAction(QIcon(":/data/icons/48x48/open_file.png"), QObject::tr("Open file"), pMainWindow);
    pAction->setIconText(QObject::tr("Open file"));
    pAction->setToolTip(QObject::tr("Open file"));
    m_actionsMap["open_file"] = pAction;

    pAction = new QAction(QIcon(), QObject::tr("Save file as"), pMainWindow);
    pAction->setIconText(QObject::tr("Save file as ..."));
    pAction->setToolTip(QObject::tr("Save file to another name"));
    m_actionsMap["save_file_as"] = pAction;

    pAction = new QAction(QIcon(), QObject::tr("Close file"), pMainWindow);
    pAction->setIconText(QObject::tr("Close file"));
    pAction->setToolTip(QObject::tr("Close file"));
    m_actionsMap["close_file"] = pAction;

    pAction = new QAction(QIcon(":/data/icons/48x48/print.png"), QObject::tr("Print"), pMainWindow);
    pAction->setIconText(QObject::tr("Print"));
    pAction->setToolTip(QObject::tr("Print"));
    m_actionsMap["print"] = pAction;

    pAction = new QAction(QIcon(":/data/icons/48x48/exit.png"), QObject::tr("Exit"), pMainWindow);
    pAction->setIconText(QObject::tr("Exit"));
    pAction->setToolTip(QObject::tr("Exit"));
    m_actionsMap["exit"] = pAction;
}


GuiActionsMgr::~GuiActionsMgr()
{
////    printf("~GuiActionsMgr()\n");
}


QAction* GuiActionsMgr::byName  ( const QString& actionName ) const
{
    GuiActionsMapT::const_iterator it = m_actionsMap.find ( actionName );
    if ( it != m_actionsMap.end() )     return it->second;
    else                                return 0;

////    return cpaf::map_find( m_actionsMap, 0, actionName );
}
