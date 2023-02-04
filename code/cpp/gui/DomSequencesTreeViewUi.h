#pragma once

#include <QWidget>
#include <QTableView>
#include <QTreeView>

class QModelIndex;
class DomSequencesTableModel;
class DomSequencesTreeModel;

class DomSequencesTreeView : public QTreeView
{
    Q_OBJECT
public:
    enum class mode_t { normal, compact };

    DomSequencesTreeView(DomSequencesTreeModel* model, mode_t mode, QWidget* parent = nullptr);

    void        domSequencesTreeModelSet(DomSequencesTreeModel* model);

signals:
    void        domFind            (const QString& domSeq);
    void        domFindNext        (const QString& domSeq);
    void        domFindAll         (const QString& domSeq);

private slots:
    void        cellClickedSlot    (const QModelIndex& index);
private:
    DomSequencesTreeModel*      m_domSequencesTreeModel = nullptr;
    mode_t                      mode_                   = mode_t::normal;
};
