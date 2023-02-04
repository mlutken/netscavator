#pragma once

#include <boost/shared_ptr.hpp>
#include <QWidget>

namespace crawl {
class DomSearchMgr;
}

class QTabWidget;
class QTableView;
class UrlQueueTableModel;
class DomSequencesTreeView;
class DomSequencesTreeModel;

class DesignWidgetUi : public QWidget
{
    Q_OBJECT
public:
    explicit DesignWidgetUi(UrlQueueTableModel* urlQueueTableModel,
                            DomSequencesTreeModel* domSequencesTreeModel,
                            QWidget *parent = nullptr);

    QTableView*             urlQueueTableView       ()                              { return m_urlQueueTableView; }
    DomSequencesTreeView*   domSeqTreeView          ()                              { return m_domSequencesTreeView; }
    void                    urlQueueTableModelSet   (UrlQueueTableModel* model);
    void                    domSequencesTreeModelSet(DomSequencesTreeModel* model);

private:
    // --- PRIVATE: Data ---
    QTabWidget*             m_pTabs;
    QTableView*             m_urlQueueTableView = nullptr;
    DomSequencesTreeView*   m_domSequencesTreeView = nullptr;
};
