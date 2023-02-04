#pragma once

#include <QWidget>

class QTableView;
class QModelIndex;

class ProjectsViewUi : public QWidget
{
    Q_OBJECT
public:
    explicit ProjectsViewUi(QWidget *parent = 0);
    
signals:
    void    openCrawlerSignal ( const QString& path );

private slots:
    void    cellClickedSlot         (const QModelIndex& index);

    
private:
    // --- PRIVATE: Data ---
    QTableView*     m_pTableView;
};
