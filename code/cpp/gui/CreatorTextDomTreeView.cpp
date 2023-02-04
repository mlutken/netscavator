#include "CreatorTextDomTreeView.h"
#include <stdio.h>
#include <QMouseEvent>
//FIXME OLD QWebView #include <QWebFrame>
//FIXME OLD QWebView #include <QWebElement>
#include <QTextBlock>
#include <QTextCursor>
//#include <qDebug>

#include <set>
#include <boost/algorithm/string.hpp>
#include <boost/assign/list_of.hpp>
#include <cpaf_libs/utils/cpaf_string_utils.hpp>

using namespace std;
using namespace boost::assign; // bring 'list_of()' into scope
using namespace crawl;



CreatorTextDomTreeView::CreatorTextDomTreeView(QWidget *parent)
  : QPlainTextEdit(parent)
  , m_pLinearDom()
  , m_bShowPos(false)
{
    setReadOnly(true);
    setWordWrapMode( QTextOption::NoWrap);


}


void CreatorTextDomTreeView::setFromLinearDom ( boost::shared_ptr<crawl::LinearDomIF> pLinearDom )
{
    m_pLinearDom = pLinearDom;
    clear();
    QTextCursor c (document() );

    size_t iPos = 0;
    LinearDomIF::const_iterator it      = pLinearDom->begin();
    LinearDomIF::const_iterator itEND   = pLinearDom->end();
    size_t i = 0;
    for ( ; it != itEND; ++it ) {
        i++;
        appendNode( c, it->node(), ++iPos );
//        printf("%d/%d\n", (int)i, (int)pLinearDom->size() );
    }
}


void CreatorTextDomTreeView::mousePressEvent(QMouseEvent* event)
{
    if ( Qt::ControlModifier & event->modifiers() )    {
        printf("CreatorTextDomTreeEdit::mousePressEvent (x,y): (%d,%d)\n", event->x(), event->y() );

//        QWebHitTestResult hit = page()->mainFrame()->hitTestContent( event->pos() );
//        if ( !hit.isNull() ) {
//            printf("hit.element.tagname: '%s'\n", hit.element().tagName().toUtf8().data() );
//            printf("hit.enclosingBlockElement.tagname: '%s'\n", hit.enclosingBlockElement().tagName().toUtf8().data() );
//            printf("hit.isContentSelected: '%d'\n", hit.isContentSelected() );
//            printf("hit.isContentEditable: '%d'\n", hit.isContentEditable() );
////            qDebug() << hit.element().geometry();
////            qDebug() << hit.enclosingBlockElement().geometry();

////            qDebug() << hit.boundingRect();
//        }
        QTextBlock b = document()->findBlockByNumber(1);
        QTextCursor c(b);
        QTextCharFormat f;
        f.setBackground( QBrush(QColor("red")));
        c.movePosition( QTextCursor::EndOfLine, QTextCursor::KeepAnchor );
        c.select(QTextCursor::LineUnderCursor);

        //c.mergeBlockCharFormat(f);
        //c.insertText("ddd", f);
        setTextCursor(c);
        ensureCursorVisible();

//        ////////////
//        QList<QTextEdit::ExtraSelection> extraSelections;
//        QTextEdit::ExtraSelection selection;
//        QColor lineColor = QColor(Qt::cyan).darker(200);
//        selection.format.setBackground(lineColor);
//        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
//        selection.s = cursor;

//        selection.cursor.clearSelection();
//        extraSelections.append(selection);
//        setExtraSelections(extraSelections);

//        //////////////


    }
    else {
        printf("QWebView::mousePressEvent\n" );
        QPlainTextEdit::mousePressEvent(event);
    }
}


void CreatorTextDomTreeView::selectDomPos( size_t iPos )
{
//    QTextBlock b = document()->findBlockByNumber(iPos -1);
    QTextBlock b = document()->findBlockByLineNumber(iPos - 1);
    QTextCursor c(b);
    QTextCharFormat f;
    f.setBackground( QBrush(QColor("red")));
    c.movePosition( QTextCursor::EndOfLine, QTextCursor::KeepAnchor );
    c.select(QTextCursor::LineUnderCursor);
    setTextCursor(c);
    ensureCursorVisible();
}


// --------------------------
// --- PRIVATE: Functions ---
// --------------------------

bool CreatorTextDomTreeView::breakAfter ( boost::shared_ptr<crawl::DomNodeIF> pNode ) const
{
    static const set<std::string> exceptELEM = list_of("A")
            ("B")("I")("U")
            ("LI")
            ("TITLE")
            ;

    static const set<std::string> exceptEND_TAG = list_of("/A")
            ("/B")("/I")("/U")
            ;

    const std::string sNodeVal = pNode->stringDataUTF8();
    bool insertBreak = false;
    if ( DomNodeTypes::ELEMENT == pNode->nodeType() ) {
        insertBreak = true;
        if ( exceptELEM.find( sNodeVal ) != exceptELEM.end() ) {
            insertBreak = false;
        }
    }
    else if ( DomNodeTypes::ELEMENT_END_TAG == pNode->nodeType() ) {
        insertBreak = true;
        if ( exceptEND_TAG.find( sNodeVal ) != exceptEND_TAG.end() ) {
            insertBreak = false;
        }
    }
    return insertBreak;
}


bool CreatorTextDomTreeView::breakBefore ( boost::shared_ptr<crawl::DomNodeIF> pNode ) const
{
    static const set<std::string> exceptELEM = list_of("A")
            ("B")("I")("U")
            ("LI")
            ("TITLE")
            ;

    static const set<std::string> exceptEND_TAG = list_of("/A")
            ("/B")("/I")("/U")
            ("/TITLE")("/LI")
            ;

    const std::string sNodeVal = pNode->stringDataUTF8();
    bool insertBreak = false;
    if ( DomNodeTypes::ELEMENT == pNode->nodeType() ) {
        insertBreak = true;
        if ( exceptELEM.find( sNodeVal ) != exceptELEM.end() ) {
            insertBreak = false;
        }
    }
    else if ( DomNodeTypes::ELEMENT_END_TAG == pNode->nodeType() ) {
        insertBreak = true;
        if ( exceptEND_TAG.find( sNodeVal ) != exceptEND_TAG.end() ) {
            insertBreak = false;
        }
    }
    return insertBreak;
}

/*
    sTextHtml += "<style type='text/css'>\n.ClassELEMENT { color: DarkBlue; }\n</style>";
    sTextHtml += "<style type='text/css'>\n.ClassATTRIBUTE { color: DarkGreen ; }\n</style>";
    sTextHtml += "<style type='text/css'>\n.ClassATTRIBUTE_VALUE { color: LimeGreen; }\n</style>";
    sTextHtml += "<style type='text/css'>\n.ClassCOMMENT { color: Magenta; }\n</style>";
    sTextHtml += "<style type='text/css'>\n.ClassDEFAULT { color: Darkorange; }\n</style>";
    sTextHtml += "<style type='text/css'>\n.ClassINDENTION { }\n</style>";
    sTextHtml += "<style type='text/css'>\n.ClassALIGN_LEFT { text-align: left; float:left;}\n</style>";

  */

void CreatorTextDomTreeView::getNodeStyle ( QTextCharFormat& f, boost::shared_ptr<crawl::DomNodeIF> pNode ) const
{
    static const QBrush brush_ELEMENT           ( QColor("darkblue") );
    static const QBrush brush_TEXT              ( QColor("black") );
    static const QBrush brush_ATTRIBUTE         ( QColor("darkgreen") );
    static const QBrush brush_ATTRIBUTE_VALUE   ( QColor("limegreen") );
    static const QBrush brush_DEFAULT           ( QColor("darkorange") );

    switch ( pNode->nodeType() ) {
    case crawl::DomNodeTypes::ELEMENT :
    case crawl::DomNodeTypes::ELEMENT_END_TAG:
    case crawl::DomNodeTypes::DOCUMENT :
        f.setForeground( brush_ELEMENT );
        break;
    case crawl::DomNodeTypes::TEXT :
        f.setForeground( brush_TEXT );
        break;
    case crawl::DomNodeTypes::ATTRIBUTE :
        f.setForeground( brush_ATTRIBUTE );
        break;
    case crawl::DomNodeTypes::ATTRIBUTE_VALUE :
        f.setForeground( brush_ATTRIBUTE_VALUE );
        break;
    default:
        f.setForeground( brush_DEFAULT );
    }
}

QString CreatorTextDomTreeView::getNodeColor ( boost::shared_ptr<crawl::DomNodeIF> pNode ) const
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


void CreatorTextDomTreeView::appendNode		(
        QTextCursor& c                                  ///< Text tree document position to insert at
        , boost::shared_ptr<crawl::DomNodeIF> pNode     ///< Node (pointer) to append.
        , size_t iLinearDomPos                          ///< Position in linear dom
        )
{
    using namespace std;
    std::string sNodeVal = pNode->stringDataUTF8();


    boost::algorithm::replace_all( sNodeVal, "<", "&lt;");
    boost::algorithm::replace_all( sNodeVal, ">", "&gt;");
    boost::algorithm::replace_all( sNodeVal, std::string("\302\240"), std::string("&amp;nbsp;") );

    const bool bBreakBefore = breakBefore( pNode );
    if ( !m_bPreviousIsBreak && bBreakBefore )
    {
    }
    const bool bNewLine = m_bPreviousIsBreak || bBreakBefore;

    QString showPos = "";
    if ( m_bShowPos ) {
        showPos = QString("(") + std::to_string(iLinearDomPos).c_str()  + ")";
    }
    QString textRtf = showPos + QString::fromUtf8(sNodeVal.c_str() ) + ", ";
    QTextCharFormat f;
    getNodeStyle( f, pNode );
    this->setCurrentCharFormat(f);
    this->appendPlainText( textRtf );
    m_bPreviousIsBreak = false;
    if ( breakAfter( pNode ) )
    {
        m_bPreviousIsBreak = true;
    }

}
