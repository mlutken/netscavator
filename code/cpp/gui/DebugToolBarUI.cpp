#include "DebugToolBarUI.h"
#include <iostream>
#include <QLabel>
#include <QWheelEvent>
#include <QComboBox>

#include <math/base/utils.hpp>
#include <utils/utils.h>
#include <GuiActionsMgr.h>
#include <Globals.h>
#include <GuiGlobals.h>

using namespace std;
using namespace crawl;

DebugToolBarUI::DebugToolBarUI(const QString& title, GuiActionsMgr* pAMgr, QWidget* parent)
    : QToolBar(title, parent)
{
    m_guiGlobals = g()->gui();
    createStructure(pAMgr);
}

QString DebugToolBarUI::textToFind() const
{
    return m_findCombo->currentText();
}

void DebugToolBarUI::matchLabelTextSet(const QString& text)
{
    m_matchLbl->setText(text);
}

void DebugToolBarUI::wheelEvent(QWheelEvent* event)
{
    if (event->modifiers() && Qt::ControlModifier ) {
        int zoomDelta = cpaf::math::clamp_copy(event->pixelDelta().manhattanLength(), -2, 2);
        int iconSize = m_guiGlobals->debugToolBarIconSize();
        iconSize = iconSize + zoomDelta;
        m_guiGlobals->debugToolBarIconSizeSet(iconSize);
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




DebugToolBarUI::~DebugToolBarUI()
{

}

void DebugToolBarUI::createStructure(GuiActionsMgr* pAMgr)
{
    const int iconSize = m_guiGlobals->debugToolBarIconSize();
    setIconSize(QSize(iconSize, iconSize));
    setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ////  m_pDebugToolBar->addAction(pAMgr->byName("blank") );
    //m_pDebugToolBar->addAction(pAMgr->byName("next_step") );
    addAction(pAMgr->byName("force_page_loaded") );
    addAction(pAMgr->byName("match_step") );
    addAction(pAMgr->byName("mine_step") );
    addAction(pAMgr->byName("navigate_step") );

    QLabel* matchLabelPrefix = new QLabel(tr("Match: "), this );
    matchLabelPrefix->setToolTip( tr("Handler last matched.\nI.e. the handler matched when match button was pressed last.") );
    //pW->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //pW->setScaledContents(true);
    matchLabelPrefix->setFont( QFont("verdana", 12));
    m_matchLbl = new QLabel("           ", this);
    m_matchLbl->setFont( QFont("verdana", 12, QFont::Bold) );
    m_matchLbl->setMinimumWidth(200);
    addWidget( matchLabelPrefix );
    addWidget( m_matchLbl );

    // Find / find next
    m_findCombo = new QComboBox(this);
    m_findCombo->setEditable(true);
    m_findCombo->setInsertPolicy(QComboBox::InsertAlphabetically);
    m_findCombo->setFont( QFont("verdana", 12));
    m_findCombo->setMinimumHeight(20);
    m_findCombo->setMaximumHeight(35);
    m_findCombo->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    addWidget(m_findCombo);

    addAction(pAMgr->byName("find"));
    addAction(pAMgr->byName("findnext"));
    addAction(pAMgr->byName("findall"));
    addAction(pAMgr->byName("nodeclick"));

    // --- Local signal handlers ---
    QObject::connect(pAMgr->byName("find"), &QAction::triggered, [this]()
        {
            const QString toFind = this->textToFind();
            const auto index = m_findCombo->findText(toFind);
            if (index == -1) {
                m_findCombo->addItem(toFind);
            }
        }
    );

    QObject::connect(pAMgr->byName("findnext"), &QAction::triggered, [this]()
        {
            const QString toFind = this->textToFind();
            const auto index = m_findCombo->findText(toFind);
            if (index == -1) {
                m_findCombo->addItem(toFind);
            }
        }
    );

    QObject::connect(pAMgr->byName("findall"), &QAction::triggered, [this]()
        {
            const QString toFind = this->textToFind();
            const auto index = m_findCombo->findText(toFind);
            if (index == -1) {
                m_findCombo->addItem(toFind);
            }
        }
    );

}
