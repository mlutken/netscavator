#pragma once

#include <vector>
#include <boost/shared_ptr.hpp>

#include <QAbstractItemModel>
#include <QFont>

#include <interfaces/LinearDomIF.h>

namespace crawl {
    class LinearDomIF;
//    class DomNodeIF;
}

class DomTreeModel : public QAbstractItemModel
{
public:
    explicit DomTreeModel(QObject *parent = nullptr);
    void            setLinearDom(boost::shared_ptr<crawl::LinearDomIF> linearDom);


    QVariant            data                (const QModelIndex& index, int role) const override;
    Qt::ItemFlags       flags               (const QModelIndex& index) const override;
    QVariant            headerData          (int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QModelIndex         index               (int row, int column, const QModelIndex& parent = QModelIndex()) const override;
    QModelIndex         parent              (const QModelIndex& index) const override;
    int                 rowCount            (const QModelIndex& parentIndex = QModelIndex()) const override;
    int                 columnCount         (const QModelIndex& index = QModelIndex()) const override;

    int                 domPosFromNode      (const crawl::TreeNode* treeNode) const;
    QModelIndex         indexFromNode       (const crawl::TreeNode* treeNode) const;
    QModelIndex         indexFromDomPos     (int domPos) const;
    crawl::TreeNode*    treeNodeFromDomPos  (int domPos) const;
    std::vector<QModelIndex> pathToRootIndex(const QModelIndex& index) const;
private:
public: // FIXMENM
    crawl::TreeNode*    rootNode            () const { return m_linearDom ? m_linearDom->rootNode() : nullptr; }
    crawl::DomTree*     domTree             () const { return m_linearDom ? m_linearDom->domTree()  : nullptr; }

    const int           attributesCount     (const crawl::TreeNode* treeNode) const;
    const int           columnCount         (const crawl::TreeNode* treeNode) const;
    const int           rowCount            (const crawl::TreeNode* treeNode) const;
    QString             displayData         (const crawl::TreeNode* treeNode) const;
    std::string         attributesData      (const crawl::TreeNode* treeNode) const;

    boost::shared_ptr<crawl::LinearDomIF>   m_linearDom;
    QFont                                   m_font;
    const std::string                       m_emptyString;
};

