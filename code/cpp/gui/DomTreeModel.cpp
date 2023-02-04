#include "DomTreeModel.h"

#include <iostream>
#include <cpaf_libs/unicode/cpaf_u8string_utils.h>
//#include <utils/string_algorithms.h>

using namespace cpaf::unicode;
using namespace crawl;

// https://doc.qt.io/qt-6/qtwidgets-itemviews-simpletreemodel-example.html


DomTreeModel::DomTreeModel(QObject *parent)
    : QAbstractItemModel{parent}
{
}

void DomTreeModel::setLinearDom(boost::shared_ptr<crawl::LinearDomIF> linearDom)
{
    beginResetModel();
    m_linearDom = linearDom;
    endResetModel();
}

QVariant DomTreeModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }
    if (role != Qt::DisplayRole) {
        return QVariant();
    }
    return displayData(static_cast<const TreeNode*>(index.constInternalPointer()));
}

Qt::ItemFlags DomTreeModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index);
}


QVariant DomTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        return QVariant("Toggle expand/collapse");
    }

    return QVariant();
}

QModelIndex DomTreeModel::index(int row, int column, const QModelIndex& parent) const
{
    if (!hasIndex(row, column, parent)) {
        return QModelIndex();
    }

    TreeNode* parentItem;

    if (!parent.isValid()) {
        parentItem = rootNode();
    }
    else {
        parentItem = static_cast<TreeNode*>(parent.internalPointer());
    }

    TreeNode* childItem = parentItem->childAt(row);
    if (childItem) {
        QModelIndex newIndex = createIndex(row, column, childItem);
        return newIndex;
    }

    return QModelIndex();
}

QModelIndex DomTreeModel::parent(const QModelIndex& index) const
{
    if (!index.isValid()) {
        return QModelIndex();
    }

    const TreeNode* indexItem = static_cast<TreeNode*>(index.internalPointer());
    if (indexItem == nullptr) {
        return QModelIndex();
    }

    if (indexItem == rootNode()) {
        return QModelIndex();
    }

    const TreeNode* targetItem = indexItem->parent;
    return indexFromNode(targetItem);
}

int DomTreeModel::rowCount(const QModelIndex& parentIndex) const
{
    if (parentIndex.column() > 0) {
        return 0;
    }

    int row_count = 0;

    TreeNode* parentItem;
    if (!parentIndex.isValid()) {
        parentItem = rootNode();
    }
    else {
        parentItem = static_cast<TreeNode*>(parentIndex.internalPointer());
    }

    if (parentItem) {
        row_count = parentItem->calcChildCount();
    }
    return row_count;
}

int DomTreeModel::columnCount(const QModelIndex& index) const
{
    int col_count = 1;
    if (index.isValid()) {
        col_count = columnCount( static_cast<TreeNode*>(index.internalPointer()) );
    }
    return col_count;
}

int DomTreeModel::domPosFromNode(const crawl::TreeNode* treeNode) const
{
    if (!treeNode) { return 0; }
    return treeNode->data.linearDomPos();
}

QModelIndex DomTreeModel::indexFromNode(const crawl::TreeNode* treeNode) const
{
    if (!treeNode)          { return QModelIndex(); }
    if (!treeNode->parent)  { return QModelIndex(); }

    int rowInParent = treeNode->parent->indexOfChild(treeNode);
    return createIndex(rowInParent, 0, treeNode);
}

QModelIndex DomTreeModel::indexFromDomPos(int domPos) const
{
    const auto* treeNode = treeNodeFromDomPos(domPos);
    return indexFromNode(treeNode);
}

TreeNode* DomTreeModel::treeNodeFromDomPos(int domPos) const
{
    if (!m_linearDom) { return nullptr; }
    return m_linearDom->treeNode(domPos);
}

std::vector<QModelIndex> DomTreeModel::pathToRootIndex(const QModelIndex& index) const
{
    std::vector<QModelIndex> indices;
    QModelIndex parentIndex = parent(index);
    while (parentIndex.isValid()) {
        indices.push_back(parentIndex);
        parentIndex = parent(parentIndex);
    }

    return indices;
}

const int DomTreeModel::attributesCount(const crawl::TreeNode* treeNode) const
{
    if (!treeNode) {
        return 0;
    }
    const int attributes_count = static_cast<const TreeNode*>(treeNode)->data.attributes().size()*2;
    return attributes_count;
}

const int DomTreeModel::columnCount(const crawl::TreeNode* treeNode) const
{
    if (!treeNode) {
        return 0;
    }
    const int col_count = attributesCount(treeNode) + 1;
    return col_count;
}

const int DomTreeModel::rowCount(const crawl::TreeNode* treeNode) const
{
    if (treeNode == nullptr) { return 0;}
    const int row_count = treeNode->calcChildCount();
    return row_count;
}

QString DomTreeModel::displayData(const crawl::TreeNode* treeNode) const
{
    if (!treeNode) { return QString(); }
    std::string val = "[" + std::to_string(domPosFromNode(treeNode)) + "] ";
    val.append(1, '<');
    if (treeNode->data.isTag()) {
        if (treeNode->data.isEndTag()) { val.append(1, '/');}
        val.append(treeNode->data.tagName());
    }
    else {
        val.append(treeNode->data.tagName());
    }

    val = simplify_white_space_copy(val);
    return QString::fromUtf8((val + attributesData(treeNode)).c_str());
}

std::string DomTreeModel::attributesData(const crawl::TreeNode* treeNode) const
{
    if (!treeNode) {
        return std::string();
    }
    if (treeNode->data.attributes().size() == 0) {
        return std::string(">");
    }

    std::string attributes("");
    for (const auto& elem : treeNode->data.attributes()) {
        attributes.append(1, ' '); // SPACE between each attribute key,value pair
        attributes.append(elem.name);
        attributes.append("=");
        attributes.append(1, '\"');
        attributes.append(elem.value);
        attributes.append(1, '\"');
    }
    attributes.append(1, '>');

    return attributes;
}
