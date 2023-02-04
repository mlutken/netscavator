#include "DomSequencesTreeModel.h"

#include <iostream>
#include <QDebug>
#include <QBrush>
#include <Globals.h>
#include <containers/DomSearchMgr.h>
#include <utils/utils.h>
#include <parser/DomSeq.h>

using namespace std;
using namespace crawl;

// https://doc.qt.io/qt-6/qabstractitemmodel.html
// https://doc.qt.io/qt-6/qt.html#ItemDataRole-enum

class DomSeqTreeNode
{
public:
    using PtrT = std::unique_ptr<DomSeqTreeNode>;
    using ChildVecT = std::vector<PtrT>;

    bool                isRootNode      () const    { return parent_ == nullptr; }
    bool                isLeafNode      () const    { return childNodes_.empty(); }

    std::string         name            () const
    {
        if (name_.empty())  { return parent_->name_;}
        else                { return name_;         }
    }

    std::string         sequence        () const
    {
        if (domSeq_) {
            return domSeq_->sequenceGet();
        }
        return "";
    }

    uint32_t            choicesSortOrder() const
    {
        if (domSeq_) {
            return domSeq_->choicesSortOrder();
        }
        return 0;
    }

    DomSeqTreeNode*     childAt         (int row) const
    {
        if (row < 0 || row >= childCount()) {
            return nullptr;
        }
        return childNodes_[static_cast<size_t>(row)].get();
    }

    int                 indexOfChild    (const DomSeqTreeNode* childNode) const
    {
        if (childNodes_.empty()) { return -1; }

        int row = -1;
        for (const auto& uniquePtrChild: childNodes_) {
            ++row;
            if (uniquePtrChild.get() == childNode) {
                return row;
            }
        }
        return -1;
    }

    int                 childCount() const { return static_cast<int>(childNodes_.size()); }

    boost::shared_ptr<DomSeq>   domSeq_;
    ChildVecT                   childNodes_;
    std::string                 name_ = "";
    DomSeqTreeNode*             parent_ = nullptr;
};


std::unique_ptr<DomSeqTreeNode> DomSequencesTreeModel::createDomSeqTree(const crawl::DomSearchMgr& domSearchMgr)
{
    auto rootNode = std::make_unique<DomSeqTreeNode>();
    rootNode->name_ = "root";
    for (const auto& pair : domSearchMgr.domSeqChoicesMap()) {
        auto level1Node = std::make_unique<DomSeqTreeNode>();
        level1Node->parent_ = rootNode.get();
        level1Node->name_ = pair.first;
        //        cerr << "FIXMENM level1: " << level1Node->name_ << "\n";

        // Level 2: Actual dom sequences/choices
        for (const boost::shared_ptr<DomSeq>& domSeq: pair.second) {
            auto level2Node = std::make_unique<DomSeqTreeNode>();
            level2Node->parent_ = level1Node.get();
            level2Node->domSeq_ = domSeq;
            //            cerr << "       FIXMENM level2: " << level2Node->choicesSortOrder() << "\n";
            level1Node->childNodes_.push_back(std::move(level2Node));
        }
        rootNode->childNodes_.push_back(std::move(level1Node));
    }

    return rootNode;
}


DomSequencesTreeModel::DomSequencesTreeModel(QObject* parent) :
    QAbstractItemModel(parent)
{

}

// NOTE: Destructor MUST be here! Empty or default is fine, but since we
//      have a unique_ptr<DomSeqTreeNode> which is only forward
//      declared in the header, the destructor MUST be here in the
//      cpp file where the complete definition of DomSeqTreeNode
//      is visible!
//  See: https://stackoverflow.com/questions/6012157/is-stdunique-ptrt-required-to-know-the-full-definition-of-t
DomSequencesTreeModel::~DomSequencesTreeModel() = default;

QVariant DomSequencesTreeModel::data(const QModelIndex& index, int role) const
{
    if ( !index.isValid() ) { return QVariant(); }
    if (!m_domSeqTreeRoot)  { return QVariant(); }

    const auto* itemPtr = static_cast<DomSeqTreeNode*>(index.internalPointer());
    if ( !itemPtr )       { return QVariant(); }

    const auto sortOrder = itemPtr->choicesSortOrder();
    auto seqName = crawl::toQString(itemPtr->name().c_str());
    if (sortOrder > 0) {
        seqName = seqName + QString("#") + QString::number(sortOrder);
    }

    const auto childCount = itemPtr->childCount();
    QString choicesStr = childCount > 0 ? QString::number(childCount) : "";
    //        if      ( 0 == col  )   return seqName;
    //        else if ( 1 == col  )   return QString("Find");
    //        else if ( 2 == col  )   return QString("Find Next");
    //        else if ( 3 == col  )   return QString("Find All");
    //        else if ( 4 == col  )   return choicesStr;
    //        else if ( 5 == col  )   return QString::fromUtf8(itemPtr->sequence().c_str());

    const int col = index.column();
    if ( Qt::DisplayRole == role ) {
        switch (col) {
        case 0: return seqName;
        case 1: return QString("Find");
        case 2: return QString("Find Next");
        case 3: return QString("Find All");
        case 4: return choicesStr;
        case 5: return QString::fromUtf8(itemPtr->sequence().c_str());
        }
    }
    else if (role == Qt::BackgroundRole)
    {
        switch (col) {
        case 0: return QBrush(QColorConstants::Svg::linen);
        case 1: return QBrush(QColorConstants::Svg::lightblue); // aliceblue;
        case 2: return QBrush(QColorConstants::Svg::aliceblue);
        case 3: return QBrush(QColorConstants::Svg::lightblue);
        case 4: return QBrush(QColorConstants::Svg::linen);
        case 5: return QBrush(QColorConstants::Svg::linen); // inactive
        }
    }
    return QVariant();
}

Qt::ItemFlags DomSequencesTreeModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index);
}

QVariant DomSequencesTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (!m_domSearchMgr) { return QVariant(); }
    if ( Qt::DisplayRole == role  && Qt::Horizontal == orientation ) {

        if ( 0 == section ) {
            const auto primarySeqsCount = m_domSearchMgr->domSeqChoicesMap().size();
            const auto totalVariantsCount = m_domSearchMgr->size();
            QString stats = QString::number(primarySeqsCount) + "/" + QString::number(totalVariantsCount);
            return tr("Name") + " (" + stats + ")";
        }
        else if ( 1 == section )    return tr("Find");
        else if ( 2 == section )    return tr("Find next");
        else if ( 3 == section )    return tr("Find All");
        else if ( 4 == section )    return tr("Choices");
        else if ( 5 == section )    return tr("Sequence");
    }
    return QVariant();
}

QModelIndex DomSequencesTreeModel::index(int row, int column, const QModelIndex& parent) const
{
    if (!hasIndex(row, column, parent)) {
        return QModelIndex();
    }

    const DomSeqTreeNode* parentItemPtr;

    if (!parent.isValid()) {
        parentItemPtr = m_domSeqTreeRoot.get();
    }
    else {
        parentItemPtr = static_cast<const DomSeqTreeNode*>(parent.internalPointer());
    }

    const DomSeqTreeNode* childItemPtr = parentItemPtr->childAt(row);
    if (childItemPtr) {
        QModelIndex newIndex = createIndex(row, column, childItemPtr);
        return newIndex;
    }

    return QModelIndex();
}

QModelIndex DomSequencesTreeModel::parent(const QModelIndex& index) const
{
    if (!index.isValid()) {
        return QModelIndex();
    }

    const auto* itemPtr = static_cast<const DomSeqTreeNode*>(index.internalPointer());
    if (itemPtr->isRootNode()) {
        return QModelIndex();
    }

    const auto* parentItemPtr = itemPtr->parent_;
    if (parentItemPtr == nullptr ) {
        return QModelIndex(); // If we end here something is wrong with the check above for this item.isRootNode()!
    }

    return indexFromNode(parentItemPtr, index.column());
}

int DomSequencesTreeModel::rowCount(const QModelIndex& parentIndex) const
{
    const DomSeqTreeNode* parentItemPtr;

    if (!parentIndex.isValid()) {
        parentItemPtr = m_domSeqTreeRoot.get();
    }
    else {
        parentItemPtr = static_cast<const DomSeqTreeNode*>(parentIndex.internalPointer());
    }

    if (!parentItemPtr) {
        return 0;
    }

    const auto count = parentItemPtr->childCount();
    return count;
}

int DomSequencesTreeModel::columnCount(const QModelIndex& index) const
{
    return 6;
}

void DomSequencesTreeModel::domSearchMgrSet(const boost::shared_ptr<crawl::DomSearchMgr>& domSearchMgr)
{
    if (!domSearchMgr) { return; }
    //    const bool needBuild = !m_domSeqTreeRoot || (m_domSearchMgr != domSearchMgr);
    //    if (!needBuild) {
    //        return; // No need to rebuild everything if nothing changed
    //    }
    auto newTree = DomSequencesTreeModel::createDomSeqTree(*domSearchMgr);
    beginResetModel();
    m_domSeqTreeRoot = std::move(newTree);
    m_domSearchMgr = domSearchMgr;
    endResetModel();
}

const DomSeqTreeNode* DomSequencesTreeModel::rootNodePtr() const
{
    return m_domSeqTreeRoot.get();
}

QModelIndex DomSequencesTreeModel::indexFromNode(const DomSeqTreeNode* treeNode, int column) const
{
    if (!treeNode)          { return QModelIndex(); }
    if (!treeNode->parent_) { return QModelIndex(); }

    int rowInParent = treeNode->parent_->indexOfChild(treeNode);
    if (rowInParent < 0)    { return QModelIndex(); }
    return createIndex(rowInParent, column, treeNode);
}




//DomSequencesTableModel::DomSequencesTableModel(QObject *parent) :
//    QAbstractTableModel(parent)
//{

//}


//int DomSequencesTableModel::rowCount  ( const QModelIndex& /*parent*/ ) const
//{
//    if (m_domSearchMgr) {
//        int size = static_cast<int>(m_domSearchMgr->size());
//        return size;
//    }
//    return 0;
//}

//int DomSequencesTableModel::columnCount     ( const QModelIndex& /*parent*/ ) const
//{
//    return 5;
//}

//QVariant DomSequencesTableModel::data       ( const QModelIndex& index, int role ) const
//{
//    if ( !index.isValid() ) return QVariant();

//    if (!m_domSearchMgr) {
//        return QVariant("");
//    }

//    if ( Qt::DisplayRole == role ) {
//        const size_t row = static_cast<size_t>(index.row());
//        const int col = index.column();
//        if ( row < m_domSearchMgr->size() ) {
//            auto pair = m_domSearchMgr->at(row);
//            const auto domSeqPtr = pair.second;
//            if (!domSeqPtr) {
//                return QVariant();
//            }
//            const auto name = crawl::toQString(pair.first);
//            const auto seq = crawl::toQString(domSeqPtr->sequenceGet());
//            if      ( 0 == col  )   return name;
//            else if ( 1 == col  )   return QString("Find");
//            else if ( 2 == col  )   return QString("Find Next");
//            else if ( 3 == col  )   return QString("Find All");
//            else if ( 4 == col  )   return seq;
//        }
//    }
//    return QVariant();
//}


//QVariant DomSequencesTableModel::headerData ( int section, Qt::Orientation orientation, int role ) const
//{
//    if ( Qt::DisplayRole == role  && Qt::Horizontal == orientation ) {
//        if ( 0 == section )         return tr("Name");
//        else if ( 1 == section )    return tr("Find");
//        else if ( 2 == section )    return tr("Find next");
//        else if ( 3 == section )    return tr("Sequence");
//    }
//    return QVariant();
//}

//void DomSequencesTableModel::domSearchMgrSet(const boost::shared_ptr<crawl::DomSearchMgr>& domSearchMgr)
//{
//    beginResetModel();
//    m_domSearchMgr = domSearchMgr;
//    endResetModel();
//}

