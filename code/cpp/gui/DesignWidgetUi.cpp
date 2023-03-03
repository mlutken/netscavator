#include "DesignWidgetUi.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QTabWidget>
#include <QTabBar>
#include <QTableView>

#include "DomSequencesTreeViewUi.h"
#include "DomSequencesTreeModel.h"
#include "UrlQueueTableModel.h"

DesignWidgetUi::DesignWidgetUi(UrlQueueTableModel* urlQueueTableModel,
                               DomSequencesTreeModel* domSequencesTreeModel,
                               QWidget *parent) :
    QWidget(parent)
{
    m_pTabs = new QTabWidget(this);
    m_pTabs->setTabsClosable(false);
    m_pTabs->setMovable(false);
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(m_pTabs);

    // --- Create tab for dom sequences ---
    m_domSequencesTreeView = new DomSequencesTreeView(domSequencesTreeModel, DomSequencesTreeView::mode_t::normal);
    m_pTabs->addTab( m_domSequencesTreeView, tr("Dom sequences") );

    m_urlQueueTableView = new QTableView(this);
    m_urlQueueTableView->setModel(urlQueueTableModel);
    m_pTabs->addTab( m_urlQueueTableView, tr("URL Queue") );
    setLayout(layout);
}

void DesignWidgetUi::urlQueueTableModelSet(UrlQueueTableModel* model)
{
    if (m_urlQueueTableView) {
        m_urlQueueTableView->setModel(model);
        m_urlQueueTableView->resizeColumnsToContents();
        m_urlQueueTableView->setSelectionMode( QAbstractItemView::NoSelection );
    }
}

void DesignWidgetUi::domSequencesTreeModelSet(DomSequencesTreeModel* model)
{
    if (m_domSequencesTreeView) {
        m_domSequencesTreeView->domSequencesTreeModelSet(model);
    }
}
