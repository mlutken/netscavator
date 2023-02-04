#ifndef CREATORWEBVIEW_H
#define CREATORWEBVIEW_H

#include <QWebView>
#include <QWebElement>
#include <LinearDomIF.h>

class CreatorWebView : public QWebView
{
    Q_OBJECT
public:
    explicit CreatorWebView(QWidget *parent = 0);
    void    setLinearDom ( boost::shared_ptr<crawl::LinearDomIF> pLinearDom );

    boost::shared_ptr<crawl::DomNodeIF>     selectedNode    () const { return m_pSelectedNode;      }
    crawl::LinearDomIF::const_iterator      itSelectedDomPos() const { return m_itSelectedDomPos;   }
    QWebElement     selectedElement ()   const { return m_selectedElement; }
    size_t          selectedDomPos  ()   const { return m_iSelectedDomPos; }


Q_SIGNALS:
    void    elementSelected();

public slots:

protected:
    void mousePressEvent(QMouseEvent *event);

private:
    boost::shared_ptr<crawl::LinearDomIF>   m_pLinearDom;
    boost::shared_ptr<crawl::DomNodeIF>     m_pSelectedNode;
    crawl::LinearDomIF::const_iterator      m_itSelectedDomPos;
    QWebElement                             m_selectedElement;
    size_t                                  m_iSelectedDomPos;
};

#endif // CREATORWEBVIEW_H
