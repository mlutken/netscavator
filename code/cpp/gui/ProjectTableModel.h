#ifndef PROJECTTABLEMODEL_H
#define PROJECTTABLEMODEL_H

#include <QAbstractTableModel>

class ProjectTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ProjectTableModel(QObject *parent = 0);

    virtual int rowCount        ( const QModelIndex &parent = QModelIndex() ) const;
    virtual int columnCount     ( const QModelIndex &parent = QModelIndex() ) const;
    virtual QVariant data       ( const QModelIndex &index, int role = Qt::DisplayRole ) const;
    virtual QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    
signals:
    
public slots:
    
};

#endif // PROJECTTABLEMODEL_H
