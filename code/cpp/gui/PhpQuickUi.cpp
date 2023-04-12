#include "PhpQuickUi.h"
#include <iostream>
#include <boost/algorithm/string.hpp>

#include <QPushButton>
#include <QVBoxLayout>
#include <QWheelEvent>
#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexerhtml.h>
#include <Qsci/qscilexerperl.h>
#include <Configuration.h>
#include <math/base/utils.hpp>
#include <Globals.h>
#include <GuiGlobals.h>

using namespace std;
using namespace crawl;
using namespace boost::algorithm;

PhpQuickUi::PhpQuickUi(QWidget *parent) :
    QWidget(parent)
{
    m_guiGlobals = g()->gui();
    boost::shared_ptr<crawl::Configuration> c= crawl::g()->configuration();
    QAction* pAction;

    m_pMainLayout = new QVBoxLayout;
    m_pExecutePhpBtn = new QPushButton(QIcon(":/data/icons/128x128/php.png"), tr("Execute PHP"), this);
    m_pPhpEdit = new QsciScintilla(this);

    m_pPhpEdit->setFolding(QsciScintilla::NoFoldStyle);
    m_pPhpEdit->setTabWidth(4);
    m_pPhpEdit->setAutoCompletionThreshold(3);
    m_pPhpEdit->setAutoCompletionCaseSensitivity(false);
    m_pPhpEdit->setUtf8(true);
    m_pPhpEdit->zoomTo(m_guiGlobals->phpQuickZoomLevel());
    m_pPhpEdit->setText(m_guiGlobals->phpQuickCode());

    QsciLexerHTML* pQsciLexerHTML = new QsciLexerHTML(m_pPhpEdit) ;
////	QsciLexerPerl* pQsciLexerHTML = new QsciLexerPerl(m_pPhpEdit) ;
    m_pPhpEdit->setLexer( pQsciLexerHTML );
    m_pPhpEdit->setMarginWidth(1,0);

    m_pMainLayout->addWidget( m_pExecutePhpBtn);
    m_pMainLayout->addWidget(m_pPhpEdit);
    setLayout(m_pMainLayout);
    connect( m_pExecutePhpBtn, SIGNAL( clicked()), this, SLOT (onExecutePhpBtnClicked()) );
}

PhpQuickUi::~PhpQuickUi()
{
}

std::string PhpQuickUi::phpStringOld() const
{
    std::string s = m_pPhpEdit->text().toUtf8().data();
    erase_first( s, "<?php" );
    erase_last( s, "?>" );
    return s;
}

QString PhpQuickUi::phpString() const
{
    std::string s = m_pPhpEdit->text().toUtf8().data();
    erase_first( s, "<?php" );
    erase_last( s, "?>" );
    return QString::fromUtf8(s.c_str());
}

// ----------------------------
// --- PROTECTED: overrides ---
// ----------------------------

void PhpQuickUi::wheelEvent(QWheelEvent* event)
{
    if (event->modifiers() && Qt::ControlModifier ) {
        const int zoomDelta = cpaf::math::clamp_copy(event->angleDelta().y(), -1, 1);
        event->accept();
        m_guiGlobals->phpQuickZoomLevelSet(m_guiGlobals->phpQuickZoomLevel() + zoomDelta);
        m_pPhpEdit->zoomTo(m_guiGlobals->phpQuickZoomLevel());
        return;
    }
    else {
        QWidget::wheelEvent(event);
        return;
    }
    event->ignore();
}


// ---------------------
// --- private slots:---
// ---------------------

void PhpQuickUi::onExecutePhpBtnClicked()
{
    saveSettings();
    emit executePhpQuick();
}

void PhpQuickUi::saveSettings()
{
    g()->gui()->phpQuickCodeSet(m_pPhpEdit->text());
}
