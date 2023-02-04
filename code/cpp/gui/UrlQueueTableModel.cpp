#include "UrlQueueTableModel.h"

#include <utils/utils.h>
#include <containers/UrlQueue.h>

UrlQueueTableModel::UrlQueueTableModel(QObject *parent)
    : QAbstractTableModel{parent}
{

}

int UrlQueueTableModel::rowCount ( const QModelIndex& /*parent*/ ) const
{
    if (m_urlQueue) {
        int size = static_cast<int>(m_urlQueue->size());
        return size;
    }
    return 0;
}

int UrlQueueTableModel::columnCount ( const QModelIndex& /*parent*/ ) const
{
    return 1;
}

QVariant UrlQueueTableModel::data ( const QModelIndex& index, int role ) const
{
    if ( !index.isValid() ) return QVariant();

    if (!m_urlQueue) {
        return QVariant("");
    }

    if ( Qt::DisplayRole == role ) {
        const size_t row = static_cast<size_t>(index.row());
        const int col = index.column();
        if ( row < m_urlQueue->size() ) {
            const auto& url = m_urlQueue->at(row);
            if      ( 0 == col  )   return crawl::toQString(url.rawString());
        }
    }
    return QVariant();
}


QVariant UrlQueueTableModel::headerData ( int section, Qt::Orientation orientation, int role ) const
{
    if ( Qt::DisplayRole == role  && Qt::Horizontal == orientation ) {
        if ( 0 == section )         return tr("URL");
    }
    return QVariant();
}


void UrlQueueTableModel::urlQueueSet(crawl::UrlQueue* urlQueue)
{
    beginResetModel();
    m_urlQueue = urlQueue;
    endResetModel();
}
