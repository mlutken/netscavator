#include "CreatorLinearDomTableModel.h"
#include <QColor>
#include <QFont>
#include <LinearDomIF.h>
#include <DomNodeIF.h>


CreatorLinearDomTableModel::CreatorLinearDomTableModel(QObject *parent)
    : QAbstractTableModel(parent),
      m_font("Arial", 9)
{
}

int CreatorLinearDomTableModel::rowCount(const QModelIndex & /*parent*/) const
{
   if (m_linearDom)
       return m_linearDom->size() +1; // NOTE: LinearDom starts from postion 1!!!
   return 0;
}

int CreatorLinearDomTableModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 1;
}

QVariant CreatorLinearDomTableModel::data(const QModelIndex &index, int role) const
{
    if (!m_linearDom)
        return QVariant();
    const int row = index.row();
    if (row <= 0 || row > m_linearDom->size())
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        return (*m_linearDom)[row].qstringData();
    }
    else if (role == Qt::ForegroundRole )   {  // notice that Qt::TextColorRole is deprecated
        const QString&& color = getNodeColor((*m_linearDom)[row].node());
        return QVariant::fromValue(QColor(color));
    }
    else if (role == Qt::FontRole )   {
        return QVariant::fromValue(m_font);
    }

    return QVariant();
}

QVariant CreatorLinearDomTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (!m_linearDom)
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Vertical) {
            return section;
        }
    }
    else if (role == Qt::FontRole )   {
        QFont font(m_font.family(), m_font.pointSize() -1);
        return QVariant::fromValue(font);
    }
    return QVariant();
}


void CreatorLinearDomTableModel::setLinearDom(boost::shared_ptr<crawl::LinearDomIF> linearDom)
{
    beginResetModel();
    m_linearDom = linearDom;
    endResetModel();
}

QString CreatorLinearDomTableModel::getNodeColor(boost::shared_ptr<crawl::DomNodeIF> pNode) const
{
    QString sClass;
    switch ( pNode->nodeType() ) {
    case crawl::DomNodeTypes::ELEMENT :
    case crawl::DomNodeTypes::ELEMENT_END_TAG:
    case crawl::DomNodeTypes::DOCUMENT :
        sClass = "darkblue";
        break;
    case crawl::DomNodeTypes::TEXT :
        sClass = "black";
        break;
    case crawl::DomNodeTypes::ATTRIBUTE :
        sClass = "darkgreen";
        break;
    case crawl::DomNodeTypes::ATTRIBUTE_VALUE :
        sClass = "limegreen";
        break;
    default:
        sClass = "darkorange";
    }
    return sClass;
}

QFont CreatorLinearDomTableModel::font() const
{
    return m_font;
}

void CreatorLinearDomTableModel::fontSet(const QFont& font)
{
    m_font = font;
    emit layoutAboutToBeChanged();
    emit layoutChanged();
}

void CreatorLinearDomTableModel::fontPointSizeSet(int pointSize)
{
    if (pointSize < 3) pointSize = 3;
    fontSet(QFont(m_font.family(), pointSize));
}

int CreatorLinearDomTableModel::fontPointSize() const
{
    return m_font.pointSize();

}


