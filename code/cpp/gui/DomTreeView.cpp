#include "DomTreeView.h"

#include <iostream>
#include <QHeaderView>

#include <interfaces/Globals.h>
#include <GuiGlobals.h>
#include "DomTreeModel.h"

// https://doc.qt.io/qt-6/qtreeview-members.html
// https://stackoverflow.com/questions/6625188/qtreeview-horizontal-scrollbar-problems#6648906

using namespace std;
using namespace crawl;

DomTreeView::DomTreeView(QWidget* parent)
    : QTreeView(parent)
{
    // https://stackoverflow.com/questions/6625188/qtreeview-horizontal-scrollbar-problems#6648906
    setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
//    setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    header()->setSectionsClickable(true);
    connect(this, &DomTreeView::clicked, this, &DomTreeView::cellClickedSlot);
    connect(this, &QTreeView::expanded, this, &DomTreeView::itemExpandededSlot);
    connect(header(), &QHeaderView::sectionClicked, this, &DomTreeView::headerSectionClickedSlot);
}

void DomTreeView::setDomTreeModel(DomTreeModel* model)
{
    m_domTreeModel = model;
    fontPointSizeSet(g()->gui()->linearDomTableViewFontPointSize());
    setModel(model);
    resizeColumnToContents(0);
}

void DomTreeView::fontPointSizeSet(int pointSize)
{
//    if (!m_domTreeModel) return;
//    m_domTreeModel->fontPointSizeSet(pointSize);
//    QFontMetrics fm(m_domTreeModel->font());

//    verticalHeader()->setDefaultSectionSize(fm.height());
//    g()->gui()->linearDomTableViewFontPointSizeSet(fontPointSize());
}

int DomTreeView::fontPointSize() const
{
//    if (!m_domTreeModel) return 0;
//    return m_domTreeModel->fontPointSize();
    return 12;
}

void DomTreeView::fontPointSizeChange(int deltaPointSize)
{
    if (!m_domTreeModel) return;
    fontPointSizeSet(fontPointSize() + deltaPointSize);
}

void DomTreeView::selectDomPosSlot(int pos)
{
//    cerr << "FIXMENM DomTreeView::selectDomPosSlot(" << pos << ")\n";
    QModelIndex index = m_domTreeModel->indexFromDomPos(pos);
//    cerr << "index.row, col: (" << index.row() << ", " << index.column() << ")\n";
    auto indices = m_domTreeModel->pathToRootIndex(index);
//    cerr << "pathToRootIndex.size:" << indices.size()
//         << " rootNodePtr: " << m_domTreeModel->rootNode()
//         << "\n";
    for (auto it = indices.rbegin(); it != indices.rend(); ++it) {
        auto idx = *it;
//        auto* ptr = static_cast<crawl::TreeNode*>(idx.internalPointer());
//        cerr << "EXPAND idx.row, col: (" << idx.row() << ", " << idx.column() << ")"
//             << " pos: " << m_domTreeModel->domPosFromNode(ptr)
//             << " ptr: " << ptr
//             << "\n";
        expand(idx);
    }
    setCurrentIndex(index);
}

void DomTreeView::setExpanded(bool doExpand)
{
   if (doExpand) {
       expandToDepth(4);
   }
   else {
       collapseAll();
   }
   m_treeExpanded = doExpand;
   resizeColumnToContents(0);
}

void DomTreeView::toggleExpanded()
{
    setExpanded(!m_treeExpanded);
}

void DomTreeView::cellClickedSlot(const QModelIndex& index)
{
    auto* ptr = static_cast<crawl::TreeNode*>(index.internalPointer());
//    std::cerr << "FIXMENM DomTreeView::cellClickedSlot"
//              << " (" << index.row() << ", " << index.column() << ")"
//              << " pos: " << m_domTreeModel->domPosFromNode(ptr)
//              << " nodePtr: " << ptr
//              << "\n";
    emit domPosClickedSig(domPos(index));
}

void DomTreeView::headerSectionClickedSlot(int logicalIndex)
{
    if (logicalIndex == 0) {
        toggleExpanded();
    }
}

void DomTreeView::itemExpandededSlot(const QModelIndex& /*index*/)
{
    resizeColumnToContents(0);
}

int DomTreeView::domPos(const QModelIndex& index) const
{
    if (!m_domTreeModel)    { return 0; }
    if (!index.isValid())   { return 0; }
    return m_domTreeModel->domPosFromNode(static_cast<const crawl::TreeNode*>(index.internalPointer()));
}
