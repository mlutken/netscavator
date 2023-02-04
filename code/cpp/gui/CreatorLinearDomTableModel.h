#pragma once

#include <boost/shared_ptr.hpp>
#include <QAbstractTableModel>
#include <QFont>

namespace crawl {
    class LinearDomIF;
    class DomNodeIF;
}

class CreatorLinearDomTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    CreatorLinearDomTableModel(QObject *parent = 0);
    int         rowCount            (const QModelIndex & parent) const override;
    int         columnCount         (const QModelIndex & parent) const override;
    QVariant    data                (const QModelIndex &index, int role) const override;
    QVariant    headerData          (int section, Qt::Orientation orientation, int role) const;
    void        setLinearDom        (boost::shared_ptr<crawl::LinearDomIF> linearDom);

    QFont       font                () const;
    void        fontSet             (const QFont& font);
    void        fontPointSizeSet    (int pointSize);
    int         fontPointSize       () const;
signals:

public slots:
private:
    QString getNodeColor ( boost::shared_ptr<crawl::DomNodeIF> pNode ) const;
    boost::shared_ptr<crawl::LinearDomIF> m_linearDom;
    QFont m_font;
};
