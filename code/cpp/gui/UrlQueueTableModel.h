#pragma once

#include <QAbstractTableModel>

namespace crawl {
    class UrlQueue;
}

class UrlQueueTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit UrlQueueTableModel(QObject *parent = nullptr);
    virtual int rowCount        ( const QModelIndex &parent = QModelIndex() ) const;
    virtual int columnCount     ( const QModelIndex &parent = QModelIndex() ) const;
    virtual QVariant data       ( const QModelIndex &index, int role = Qt::DisplayRole ) const;
    virtual QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    void    urlQueueSet         (crawl::UrlQueue* urlQueue);

private:
    crawl::UrlQueue*    m_urlQueue = nullptr;
};
