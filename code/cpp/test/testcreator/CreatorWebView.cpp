#include "CreatorWebView.h"
#include <stdio.h>
#include <QMouseEvent>
#include <QWebFrame>
#include <QWebElement>
#include <WebKitDomNodeQt.h>
#include <map>
#include <boost/algorithm/string.hpp>
#include <boost/assign/list_of.hpp>
#include <cpaf_stl_utils.h>

using namespace crawl;
using namespace std;
using namespace boost;
using namespace boost::assign; // bring 'list_of()' into scope


CreatorWebView::CreatorWebView(QWidget *parent)
  : QWebView(parent)
  , m_pLinearDom()
  , m_pSelectedNode()
  , m_itSelectedDomPos()
  , m_selectedElement()
  , m_iSelectedDomPos(0)
{


}


void CreatorWebView::mousePressEvent(QMouseEvent* event)
{
    static const map<QString, size_t> adjustPos = map_list_of
            ("A", 3)
            ("LI", 1)
            ("TITLE", 1)
            ;


    if ( Qt::ControlModifier & event->modifiers() )    {
        //printf("CreatorWebView::mousePressEvent (x,y): (%d,%d)\n", event->x(), event->y() );

        QWebHitTestResult hit = page()->mainFrame()->hitTestContent( event->pos() );
        if ( !hit.isNull() ) {
//            printf("hit.element.tagname: '%s'\n", hit.element().tagName().toUtf8().data() );
//            printf("hit.enclosingBlockElement.tagname: '%s'\n", hit.enclosingBlockElement().tagName().toUtf8().data() );
//            printf("hit.linkElement.tagname: '%s'\n", hit.linkElement().tagName().toUtf8().data() );
//            printf("hit.isContentSelected: '%d'\n", hit.isContentSelected() );
//            printf("hit.isContentEditable: '%d'\n", hit.isContentEditable() );
//            printf("hit.linkText: '%s'\n", hit.linkText().toUtf8().data() );
//            printf("hit.alternateText: '%s'\n", hit.alternateText().toUtf8().data() );
//            printf("hit.linkTitle: '%s'\n", hit.linkTitle().toString().toUtf8().data() );
//            printf("hit.linkUrl: '%s'\n", hit.linkUrl().toString().toUtf8().data() );
//            printf("hit.linkText: '%s'\n", hit.linkText().toUtf8().data() );
//            printf("hit.title: '%s'\n", hit.title().toUtf8().data() );
            m_selectedElement = hit.enclosingBlockElement();
            if ( hit.element().tagName() != "" ) {
                m_selectedElement = hit.element();
                //printf("Using actual element and not enclosing\n" );
            }
            else if ( hit.linkElement().tagName() != "" ) {
                m_selectedElement = hit.linkElement();
                //printf("Using link element and not enclosing\n" );
            }

            bool bOk = false;
            if ( m_pLinearDom ) {
                m_pSelectedNode = mkWebKitDomNodeQt(
                            DomNodeTypes::ELEMENT, "", m_selectedElement, m_pLinearDom->browser(), -1
                            );
                LinearDomIF::const_iterator it = m_pLinearDom->findFromRawPointer( m_pSelectedNode );
                if ( it != m_pLinearDom->end() ) {
                    bOk = true;
                    m_iSelectedDomPos = m_pLinearDom->iteratorToPos(it);
                    m_pSelectedNode = it->node;
                    m_itSelectedDomPos = it;
                    //printf("XPos: %d\n", (int)m_iSelectedDomPos );
                    emit elementSelected();
                }
            }
            if (!bOk) {
                m_pSelectedNode = boost::shared_ptr<crawl::DomNodeIF>();
                m_itSelectedDomPos = m_pLinearDom->end();
                m_selectedElement = QWebElement();
                m_iSelectedDomPos = 0;
            }
        }
    }
    else {
        //printf("QWebView::mousePressEvent\n" );
        QWebView::mousePressEvent(event);

    }
}




void CreatorWebView::setLinearDom ( boost::shared_ptr<crawl::LinearDomIF> pLinearDom )
{
    m_pLinearDom = pLinearDom;
}

