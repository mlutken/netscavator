#include "DomSequencesTreeViewUi.h"

#include <iostream>
#include <QLabel>
#include <QVBoxLayout>
#include <QTableView>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QModelIndex>

#include "DomSequencesTreeModel.h"

// https://doc.qt.io/qt-6/qtreeview.html

DomSequencesTreeView::DomSequencesTreeView(DomSequencesTreeModel* model, mode_t mode, QWidget* parent) :
    QTreeView(parent),
    m_domSequencesTreeModel(model),
    mode_(mode)
{
//    setShowGrid(true);
    setSelectionMode( QAbstractItemView::NoSelection );
    if (model) {
        setModel(model);
        if (mode_ == mode_t::compact) {
            hideColumn(5);
        }
    }

    connect(this, &DomSequencesTreeView::clicked, this, &DomSequencesTreeView::cellClickedSlot);
}

void DomSequencesTreeView::domSequencesTreeModelSet(DomSequencesTreeModel* model)
{
    if (!model) { return; }
    m_domSequencesTreeModel = model;
    setModel(model);
    if (mode_ == mode_t::compact) {
        hideColumn(5);
    }
    const auto colCount = model->columnCount();
    for (int col = 0; col < colCount; ++col) {
        resizeColumnToContents(col);
    }
}

void DomSequencesTreeView::cellClickedSlot(const QModelIndex& index)
{
    QModelIndex parentIndex = m_domSequencesTreeModel->parent(index);
    QModelIndex seqIndex = m_domSequencesTreeModel->index(index.row(), 0, parentIndex);
//    auto domSeqStr = model()->data(index, Qt::DisplayRole).toString();
    auto domSeqStr = model()->data(seqIndex, Qt::DisplayRole).toString();
    std::cerr << "FIXMENM DomSequencesTreeView::cellClickedSlot"
              << " (" << index.row() << ", " << index.column() << ")"
              << "  seq: '" << domSeqStr.toUtf8().constData() << "'"
              << "\n";
    switch (index.column()) {
    case 1:
        emit domFind(domSeqStr); break;
    case 2:
        emit domFindNext(domSeqStr); break;
    case 3:
        emit domFindAll(domSeqStr); break;
    }
}
