#include "ProjectsViewUi.h"

#include <stdio.h>
#include <QLabel>
#include <QVBoxLayout>
#include <QTableView>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QModelIndex>

#include "ProjectTableModel.h"


ProjectsViewUi::ProjectsViewUi(QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout;

    //create QTableView
    m_pTableView = new QTableView();
    m_pTableView->setSelectionBehavior(QAbstractItemView::SelectRows );
    //m_pTableView->setSelectionMode( QAbstractItemView::ExtendedSelection );
    m_pTableView->setShowGrid(false);
    m_pTableView->verticalHeader()->hide();

    //setting layout
    layout->addWidget(m_pTableView);
    setLayout(layout);

    ProjectTableModel* model = new ProjectTableModel( this );

    m_pTableView->setModel(model);
    m_pTableView->resizeColumnsToContents();
    m_pTableView->setSelectionMode( QAbstractItemView::NoSelection );

    connect(m_pTableView, &QTableView::clicked, this, &ProjectsViewUi::cellClickedSlot);
}

// ----------------------
// --- PRIVATE: Slots ---
// ----------------------

void ProjectsViewUi::cellClickedSlot(const QModelIndex& index)
{
    ProjectTableModel* model = static_cast<ProjectTableModel*>(m_pTableView->model());
    QModelIndex idx = model->index(index.row(), 1);
    QString path = model->data( idx, Qt::DisplayRole ).toString();
    emit openCrawlerSignal ( path );
}

//m_pTableView->resizeColumnsToContents();
//m_pTableView->setSelectionMode( QAbstractItemView::NoSelection );

//QItemSelectionModel* pSelModel = m_pTableView->selectionModel ();

//void ProjectsViewUi::currentRowChangedSlot ( const QModelIndex& current, const QModelIndex& previous )
//{
//    ProjectTableModel* model = static_cast<ProjectTableModel*>(m_pTableView->model());
//    QModelIndex idx = model->index(current.row(), 1);
//    QString path = model->data( idx, Qt::DisplayRole ).toString();
//    emit openCrawlerSignal ( path );
//    //m_pTableView->selectAll();
//}

