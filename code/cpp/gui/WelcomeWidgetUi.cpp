#include "WelcomeWidgetUi.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QTabWidget>
#include <QTabBar>

#include "ProjectsViewUi.h"


WelcomeWidgetUi::WelcomeWidgetUi(QWidget *parent) :
    QWidget(parent)
{
    m_pTabs = new QTabWidget(this);
    m_pTabs->setTabsClosable(false);
    m_pTabs->setMovable(false);
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(m_pTabs);

    // --- Create tab for (recent) projects ---
    m_pProjects = new ProjectsViewUi;
    m_pTabs->addTab( m_pProjects, tr("Recent projects") );
    setLayout(layout);

}
