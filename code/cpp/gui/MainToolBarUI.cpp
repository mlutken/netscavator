#include "MainToolBarUI.h"
#include <iostream>
#include <QLabel>
#include <QWheelEvent>

#include <math/base/utils.hpp>

#include <GuiActionsMgr.h>
#include <Globals.h>
#include <GuiGlobals.h>

using namespace std;
using namespace crawl;

MainToolBarUI::MainToolBarUI(const QString& title, GuiActionsMgr* pAMgr, QWidget* parent)
    : QToolBar(title, parent)
{
    m_guiGlobals = g()->gui();
    createStructure(pAMgr);
}

void MainToolBarUI::wheelEvent(QWheelEvent* event)
{
    if (event->modifiers() && Qt::ControlModifier ) {
        const int zoomDelta = cpaf::math::clamp_copy(event->angleDelta().y(), -2, 2);
        int iconSize = m_guiGlobals->mainToolBarIconSize();
        iconSize = iconSize + zoomDelta;
        m_guiGlobals->mainToolBarIconSizeSet(iconSize);
        setIconSize(QSize(iconSize, iconSize));
        event->accept();
        return;
    }
    else {
        QToolBar::wheelEvent(event);
        return;
    }
    event->ignore();
}




MainToolBarUI::~MainToolBarUI()
{

}

void MainToolBarUI::createStructure(GuiActionsMgr* pAMgr)
{
    const int iconSize = m_guiGlobals->mainToolBarIconSize();
    setIconSize(QSize(iconSize, iconSize));
    //setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    addAction(pAMgr->byName("welcome") );
    addSeparator();
    addAction(pAMgr->byName("browser") );
    addAction(pAMgr->byName("crawler_editor") );
    addAction(pAMgr->byName("design") );
    addAction(pAMgr->byName("htmlsource") );
    addSeparator();
    addAction(pAMgr->byName("help") );

    QLabel* pStretchWidget = new QLabel("", this );
    pStretchWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    addWidget( pStretchWidget );
    addAction(pAMgr->byName("run") );
    addAction(pAMgr->byName("stop") );
    addAction(pAMgr->byName("debug") );
    addAction(pAMgr->byName("reload_script") );

}
