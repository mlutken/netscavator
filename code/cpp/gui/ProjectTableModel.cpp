#include "ProjectTableModel.h"
#include <QDebug>

#include <Globals.h>
#include <GuiGlobals.h>
#include <gui_utils.h>

ProjectTableModel::ProjectTableModel(QObject *parent) :
    QAbstractTableModel(parent)
{

}


int ProjectTableModel::rowCount        ( const QModelIndex& /*parent*/ ) const
{
    return crawl::g()->gui()->recentCrawlers().count();
    ////return 6;
}

int ProjectTableModel::columnCount     ( const QModelIndex& /*parent*/ ) const
{
    return 2;
}

QVariant ProjectTableModel::data       ( const QModelIndex& index, int role ) const
{
    if ( !index.isValid() ) return QVariant();
    if ( Qt::DisplayRole == role ) {
        const auto& recentCrawlers = crawl::g()->gui()->recentCrawlers();
        const int row = index.row();
        const int col = index.column();
        if ( row < recentCrawlers.count() ) {
            QString path = recentCrawlers.at(row);
            if      ( 0 == col  )   return leafFileName( path );
            else if ( 1 == col  )   return path;
        }
    }
    return QVariant();
}


QVariant ProjectTableModel::headerData ( int section, Qt::Orientation orientation, int role ) const
{
    if ( Qt::DisplayRole == role  && Qt::Horizontal == orientation ) {
        if ( 0 == section )         return tr("Recent crawlers");
        else if ( 1 == section )    return tr("Crawler project location");
    }
    return QVariant();
}
