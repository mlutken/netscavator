#ifndef _CREATOR_TEXT_DOM_TREE_EDIT_H_
#define _CREATOR_TEXT_DOM_TREE_EDIT_H_

#include <QTextEdit>
#include <QPlainTextEdit>
#include <LinearDomIF.h>
#include <DomNodeIF.h>


class CreatorTextDomTreeView : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit CreatorTextDomTreeView(QWidget *parent = 0);
    void    setFromLinearDom    ( boost::shared_ptr<crawl::LinearDomIF> pLinearDom );
    void    selectDomPos        ( size_t iPos );

signals:
    
public slots:

protected:
    void mousePressEvent(QMouseEvent *event);

private:
    bool 			breakAfter          ( boost::shared_ptr<crawl::DomNodeIF> pNode ) const;
    bool 			breakBefore         ( boost::shared_ptr<crawl::DomNodeIF> pNode ) const;

    void            getNodeStyle 		( QTextCharFormat& f, boost::shared_ptr<crawl::DomNodeIF> pNode ) const ;
    QString         getNodeColor        ( boost::shared_ptr<crawl::DomNodeIF> pNode ) const;
    void 			appendNode  		( QTextCursor& c ,boost::shared_ptr<crawl::DomNodeIF> pNode, size_t iLinearDomPos );

    // --- PRIVATE: Data ---
    boost::shared_ptr<crawl::LinearDomIF>   m_pLinearDom;
    bool                                    m_bPreviousIsBreak;
    bool                                    m_bShowPos;

};

#endif // _CREATOR_TEXT_DOM_TREE_EDIT_H_
