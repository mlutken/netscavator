#pragma once

#include <memory>
#include <boost/shared_ptr.hpp>
#include <QAbstractItemModel>
#include <QAbstractTableModel>

namespace crawl {
class DomSearchMgr;
}

class DomSeqTreeNode;

class DomSequencesTreeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit DomSequencesTreeModel(QObject *parent = nullptr);
    ~DomSequencesTreeModel() override;

    static std::unique_ptr<DomSeqTreeNode> createDomSeqTree(const crawl::DomSearchMgr& domSearchMgr);

    QVariant            data                (const QModelIndex& index, int role) const override;
    Qt::ItemFlags       flags               (const QModelIndex& index) const override;
    QVariant            headerData          (int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QModelIndex         index               (int row, int column, const QModelIndex& parent = QModelIndex()) const override;
    QModelIndex         parent              (const QModelIndex& index) const override;
    int                 rowCount            (const QModelIndex& parentIndex = QModelIndex()) const override;
    int                 columnCount         (const QModelIndex& index = QModelIndex()) const override;

    void domSearchMgrSet(const boost::shared_ptr<crawl::DomSearchMgr>& domSearchMgr);

signals:

public slots:


private:
    const DomSeqTreeNode*   rootNodePtr     () const;
    QModelIndex             indexFromNode   (const DomSeqTreeNode* treeNode, int column) const;

    boost::shared_ptr<crawl::DomSearchMgr>  m_domSearchMgr;
    std::unique_ptr<DomSeqTreeNode>         m_domSeqTreeRoot;
};

//class DomSequencesTableModel : public QAbstractTableModel
//{
//    Q_OBJECT
//public:
//    explicit DomSequencesTableModel(QObject *parent = nullptr);

//    virtual int rowCount        ( const QModelIndex &parent = QModelIndex() ) const;
//    virtual int columnCount     ( const QModelIndex &parent = QModelIndex() ) const;
//    virtual QVariant data       ( const QModelIndex &index, int role = Qt::DisplayRole ) const;
//    virtual QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

//    void domSearchMgrSet(const boost::shared_ptr<crawl::DomSearchMgr>& domSearchMgr);

//signals:
    
//public slots:
    

//private:
//    boost::shared_ptr<crawl::DomSearchMgr>  m_domSearchMgr;

//};

