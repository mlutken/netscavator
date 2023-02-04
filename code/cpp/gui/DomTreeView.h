#pragma once

#include <QTreeView>

class DomTreeModel;

class DomTreeView : public QTreeView
{
    Q_OBJECT
public:
    DomTreeView(QWidget* parent = nullptr);

    void        setDomTreeModel         (DomTreeModel* model);

    void        fontPointSizeSet        (int pointSize);
    int         fontPointSize           () const;
    void        fontPointSizeChange     (int deltaPointSize);
    bool        treeExpanded            () const { return m_treeExpanded; }

signals:
    void        domPosClickedSig        (int domPos);

public slots:
    void        selectDomPosSlot        (int pos);
    void        setExpanded             (bool doExpand);
    void        toggleExpanded          ();

private slots:
    void        cellClickedSlot         (const QModelIndex& index);
    void        headerSectionClickedSlot(int logicalIndex);
    void        itemExpandededSlot      (const QModelIndex &index);
private:

    int         domPos                  (const QModelIndex& index) const;

    DomTreeModel*   m_domTreeModel = nullptr;
    bool            m_treeExpanded = false;
};

