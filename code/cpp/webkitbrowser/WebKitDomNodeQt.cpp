#include "WebKitDomNodeQt.h"

#include <iostream>
#include <boost/algorithm/string.hpp>
#include <cpaf_libs/utils/cpaf_string_utils.hpp>
#include <LinearDomIF.h>
#include <BoxObjectIF.h>
#include <WebBrowserIF.h>
#include <url/Url.h>
//FIXME OLD QWebView #include <QtWebKit>
#include <QThread>

//FIXME OLD QWebView #include <qwebelement.h>
using namespace std;

// DOM geometry: http://www.quirksmode.org/dom/tests/elementdimensions.html



namespace crawl {

    // ------------------
    // --- WebKitDomNodeQt ---
    // ------------------


    WebKitDomNodeQt::WebKitDomNodeQt(int32_t iNodeType
             , const QString& value
             , const QString& sElem
//             , const QWebElement& nativeElem
             , boost::shared_ptr<crawl::WebBrowserIF> pOwnerBrowser
             , int iDepthLevel
            )
                : DomNodeIF     ( pOwnerBrowser, iDepthLevel )
                , m_iNodeType   ( iNodeType     )
                , m_value       ( value         )
                , m_sElem       ( sElem         )
//                , m_nativeElem  ( nativeElem    )
    {
//FIXME OLD QWebView         if ( 3 == nativeElem.nodeTypeCrawler() ) m_iNodeType = DomNodeTypes::TEXT;
    }

    WebKitDomNodeQt::~WebKitDomNodeQt()
    {
    }



    // -------------------------------------
    // --- PRIVATE: Structural functions ---
    // -------------------------------------

    /** Get immediate/direct (first level) parent node, by using the underlying "native"
        browser "framework". This is only OK to do from main thread */
    boost::shared_ptr<DomNodeIF> WebKitDomNodeQt::do_immediateParentNodeNative() const
    {
        return nullptr;
//FIXME OLD QWebView
//        if ( m_nativeElem.isNull() )
//            return boost::shared_ptr<DomNodeIF>();
//        QWebElement e = m_nativeElem;
//        if ( nodeType() == DomNodeTypes::ELEMENT || nodeType() == DomNodeTypes::ELEMENT_END_TAG  ) {
//            e = e.parent();
//        }
//        if (e.isNull())
//            return boost::shared_ptr<DomNodeIF>();

//        boost::shared_ptr<WebKitDomNodeQt> node( new WebKitDomNodeQt(DomNodeTypes::ELEMENT, "", "", e, ownerBrowser(), depthLevelGet() - 1 ) );
//        return node;
    }

////    boost::shared_ptr<DomNodeIF> WebKitDomNodeQt::do_parentNode       (
////            int iLevelsUp
////            ) const
////    {
////        if ( m_nativeElem.isNull() ) return boost::shared_ptr<DomNodeIF>();
////        if ( iLevelsUp < 1 ) iLevelsUp = 1;
////
////        int i = iLevelsUp;
////        QWebElement e = m_nativeElem;
////        if ( DomNodeTypes::ELEMENT != nodeType() && DomNodeTypes::ELEMENT_END_TAG != nodeType()  ) {
////            --i;
////        }
////        while ( (i > 0) && ( !e.isNull() && !e.parent().isNull() ) )	{
////            e = e.parent();
////            i--;
////        }
////        if ( i == 0 ) {
////            return mkWebKitDomNodeQt( DomNodeTypes::ELEMENT, "", e, ownerBrowser(), depthLevelGet() - iLevelsUp );
////        }
////        else return boost::shared_ptr<DomNodeIF>();
////    }



//    bool WebKitDomNodeQt::do_hasChildNodes () const
//    {
//        return false;     //FIXME NEW QWebView
////FIXME OLD QWebView         if ( m_nativeElem.isNull() ) return false;
////FIXME OLD QWebView        return !m_nativeElem.firstChild().isNull();
//    }

//    boost::shared_ptr<BoxObjectIF> WebKitDomNodeQt::do_getBoxObject () const
//    {
////FIXME OLD QWebView         if ( m_nativeElem.isNull() ) return boost::shared_ptr<BoxObjectIF>();
//        boost::shared_ptr<BoxObjectIF> pBox;
////FIXME OLD QWebView         QRect r = m_nativeElem.geometry();
////FIXME OLD QWebView         boost::int32_t iUnInitialized = std::numeric_limits<boost::int32_t>::min();
////FIXME OLD QWebView         boost::shared_ptr<DomNodeIF> pOwningNode = boost::const_pointer_cast<DomNodeIF>(shared_from_this());
////FIXME OLD QWebView         pBox = boost::shared_ptr<BoxObjectIF>( new crawl::BoxObjectIF(pOwningNode, r.x(), r.y(), r.width(), r.height(), iUnInitialized, iUnInitialized) );
//        return pBox;
//    }

//    std::vector<boost::shared_ptr<DomNodeIF>> WebKitDomNodeQt::do_childNodesGet () const
//    {
//        std::vector<boost::shared_ptr<DomNodeIF>> nodes;
////FIXME OLD QWebView         if ( m_nativeElem.isNull() ) return std::vector<boost::shared_ptr<DomNodeIF>>();
////FIXME OLD QWebView         QWebElement child = m_nativeElem.firstChild();
////FIXME OLD QWebView         while ( !child.isNull() ) {
////FIXME OLD QWebView             boost::shared_ptr<DomNodeIF> pDomNode = mkWebKitDomNodeQt( DomNodeTypes::ELEMENT,"", "", child, ownerBrowser(), depthLevelGet() +1 );
////FIXME OLD QWebView             nodes.push_back( pDomNode );
////FIXME OLD QWebView             child = child.nextSibling();
////FIXME OLD QWebView         }
//        return nodes;
//    }

//    boost::shared_ptr<DomNodeIF> WebKitDomNodeQt::do_firstChild () const
//    {
//        return boost::shared_ptr<DomNodeIF>();
//        //FIXME OLD QWebView
////FIXME OLD QWebView         if ( m_nativeElem.isNull() ) return boost::shared_ptr<DomNodeIF>();
////FIXME OLD QWebView         QWebElement e = m_nativeElem.firstChild();
////FIXME OLD QWebView         if ( e.isNull() ) return boost::shared_ptr<DomNodeIF>();
////FIXME OLD QWebView         return mkWebKitDomNodeQt( DomNodeTypes::ELEMENT, "", "", e, ownerBrowser(), depthLevelGet() +1 );
//    }

//    boost::shared_ptr<DomNodeIF> WebKitDomNodeQt::do_lastChild () const
//    {
//        return boost::shared_ptr<DomNodeIF>();
//        //FIXME OLD QWebView
////        if ( m_nativeElem.isNull() ) return boost::shared_ptr<DomNodeIF>();
////        QWebElement e = m_nativeElem.lastChild();
////        if ( e.isNull() ) return boost::shared_ptr<DomNodeIF>();
////        return mkWebKitDomNodeQt( DomNodeTypes::ELEMENT, "", "", e, ownerBrowser(), depthLevelGet() +1 );
//    }

//    boost::shared_ptr<DomNodeIF> WebKitDomNodeQt::do_previousSibling () const
//    {
//        return boost::shared_ptr<DomNodeIF>();
//        //FIXME OLD QWebView
////        if ( m_nativeElem.isNull() ) return boost::shared_ptr<DomNodeIF>();
////        QWebElement e = m_nativeElem.previousSibling();
////        if ( e.isNull() ) return boost::shared_ptr<DomNodeIF>();
////        return mkWebKitDomNodeQt( DomNodeTypes::ELEMENT, "", "", e, ownerBrowser(), depthLevelGet() );
//    }

//    boost::shared_ptr<DomNodeIF> WebKitDomNodeQt::do_nextSibling () const
//    {
//        return boost::shared_ptr<DomNodeIF>();
//        //FIXME OLD QWebView
////        if ( m_nativeElem.isNull() ) return boost::shared_ptr<DomNodeIF>();
////        QWebElement e = m_nativeElem.nextSibling();
////        if ( e.isNull() ) return boost::shared_ptr<DomNodeIF>();
////        return mkWebKitDomNodeQt( DomNodeTypes::ELEMENT, "", "", e, ownerBrowser(), depthLevelGet() );
//    }


    // ------------------------------------
    // --- PRIVATE: Attribute functions ---
    // ------------------------------------
//    std::string WebKitDomNodeQt::do_attributeGet (
//            const std::string& sName
//            ) const
//    {
//        return "TODO WebKitDomNodeQt::do_attributeGet()";
//        //FIXME OLD QWebView
////        if ( m_nativeElem.isNull() ) return "";
////        return m_nativeElem.attribute( QString::fromUtf8(sName.c_str()) ).toUtf8().data();
//    }

//    void WebKitDomNodeQt::do_attributeSet (
//            const std::string& sName
//            ,const std::string& sValue
//            )
//    {
//        //FIXME OLD QWebView
////        if ( m_nativeElem.isNull() ) return;
////        m_nativeElem.setAttribute( QString::fromUtf8(sName.c_str()), QString::fromUtf8(sValue.c_str()) );
//    }

//    void WebKitDomNodeQt::do_attributesGet    ( AttributesMap& attributes ) const
//    {
//        attributes.clear();
//        //FIXME OLD QWebView
////        if ( m_nativeElem.isNull() ) return;
////        QStringList attribNames = m_nativeElem.attributeNames();
////        QStringList::const_iterator it    = attribNames.begin();
////        QStringList::const_iterator itEND = attribNames.end();

////        for ( ; it != itEND; ++it ) {
////            const std::string sName ( (*it).toUtf8().data() );
////            attributes[sName] = attributeGet(sName);
////        }
//    }

    // -------------------------------
    // --- PRIVATE: Info functions ---
    // -------------------------------
//    QString WebKitDomNodeQt::do_qstringDataGet () const
//    {
//        if (!m_value.isEmpty()) {
//            return m_value;
//        }

//        QString val = "";
//        switch ( m_iNodeType )
//        {
//            case DomNodeTypes::ELEMENT :
//            {
//                val = "TODO DomNodeTypes::ELEMENT";
//                //FIXME OLD QWebView  val = m_nativeElem.tagName();
//                break;
//            }
//            case DomNodeTypes::ATTRIBUTE :
//            {
//                val = m_sElem;
//                break;
//            }
//            case DomNodeTypes::ATTRIBUTE_VALUE :
//            {
//                val = "TODO DomNodeTypes::ATTRIBUTE_VALUE";
//                //FIXME OLD QWebView  val = m_nativeElem.attribute(m_sElem).simplified();
//                break;
//            }
//            case DomNodeTypes::TEXT :
//            {
//                val = "TODO DomNodeTypes::TEXT";
////FIXME OLD QWebView                  val = m_nativeElem.textNodeValue().simplified();
//                break;
//            }
//            case DomNodeTypes::ELEMENT_END_TAG:
//            {

//                val = "TODO DomNodeIF::END_TAG";
//                //FIXME OLD QWebView val = (QString("/") + m_nativeElem.tagName());
//                break;
//            }
//            default:
//            {
//                val = "";
//            }
//        }

//        return val;
//    }

//    std::string WebKitDomNodeQt::do_stringDataUTF8Get () const
//    {
//        return qstringDataGet().toUtf8().data();
//    }

//    std::string WebKitDomNodeQt::do_nodeNameGet() const
//    {
//        return "TODO: WebKitDomNodeQt::do_nodeNameGet()";
//       //FIXME OLD QWebView
////        if ( m_nativeElem.isNull() ) return "";
////        return  m_nativeElem.tagName().toUtf8().data();
//    }

//    std::string WebKitDomNodeQt::do_nodeValueGet() const
//    {
//        return "TODO: WebKitDomNodeQt::do_nodeValueGet()";
////FIXME OLD QWebView
////        if ( m_nativeElem.isNull() ) return "";
////        return m_nativeElem.attribute("value").toUtf8().data();
//    }

//    std::string WebKitDomNodeQt::do_nodeTextGet () const
//    {
//        return "TODO WebKitDomNodeQt::do_nodeTextGet()";
//        //FIXME OLD QWebView
////        if ( m_nativeElem.isNull() ) return "";
////        return m_nativeElem.toPlainText().simplified().toUtf8().data();
//    }

//    std::string WebKitDomNodeQt::do_nodeTextAllRecurGet () const
//    {
//        return "TODO WebKitDomNodeQt::do_nodeTextAllRecurGet()";
//        //FIXME OLD QWebView
////        if ( m_nativeElem.isNull() ) return "";
////        return m_nativeElem.toPlainText().simplified().toUtf8().data();
//    }


//    // TODO: Fix %25 problems see imusic.dk script. NOTE: Should be fixed, but check that it is
//    std::string WebKitDomNodeQt::do_hrefGet () const
//    {
//        return "TODO WebKitDomNodeQt::do_hrefGet()";
//        //FIXME OLD QWebView
////        if ( m_nativeElem.isNull() ) return "";
////        if ( DomNodeTypes::ELEMENT == m_iNodeType && m_nativeElem.tagName() == "A" ) {
////            std::string s = m_nativeElem.attribute("href").toUtf8().data();
////            return s;
////        }
////        return "";
//    }

//    std::string WebKitDomNodeQt::do_hrefCompleteGet () const
//    {
//        //FIXME OLD QWebView
////        if ( m_nativeElem.isNull() ) return "";
////        if ( DomNodeTypes::ELEMENT == m_iNodeType && m_nativeElem.tagName() == "A" ) {
////            Url u = linkComplete( Url (ownerBrowser()->currentUri() ), href() );
////            return u.string();
////        }
//        return "";
//    }


    void* WebKitDomNodeQt::do_nativeNodePtrGet  () const
    {
        return nullptr;
        //FIXME OLD QWebView
//        if ( m_nativeElem.isNull() ) return 0;
//        return &m_nativeElem;
    }

    boost::uint32_t WebKitDomNodeQt::do_nodeTypeGet () const
    {
        return m_iNodeType;
    }

    crawl::XPath WebKitDomNodeQt::do_xpathGet() const
    {
        return crawl::XPath{};
    }


    // -----------------------------
    // --- PRIVATE: Node actions ---
    // -----------------------------
    bool WebKitDomNodeQt::do_click  () const
    {


////        const auto xpath =
//        cerr << "WebKitDomNodeQt::do_click xpath: '" << xpath().toString() <<  "'\n";

//        std::string js;
//        js.append("var elem1 = document.evaluate('\n");
//        js.append(xpath().toString());
//        js.append("',\n");
//        js.append("document,\n");
//        js.append("null,\n");
//        js.append("XPathResult.FIRST_ORDERED_NODE_TYPE,\n");
//        js.append("null\n");
//        js.append(").singleNodeValue;\n");
//        js.append("elem1.click();\n");
//        cerr << "JS:\n" << js <<  "\n";


//        var elem1 = document.evaluate(
//          '/html/body/div[1]/div[2]/div[2]/ul[1]/li[1]/a',
//          document,
//          null,
//          XPathResult.FIRST_ORDERED_NODE_TYPE,
//          null,
//        ).singleNodeValue;
//        elem1.click();

        return true;
        //FIXME OLD QWebView
//        if ( m_nativeElem.isNull() ) return false;
//        m_nativeElem.evaluateJavaScript("var evObj = document.createEvent('MouseEvents');evObj.initEvent( 'click', true, true );this.dispatchEvent(evObj); null");
//        return true;
    }


//    bool WebKitDomNodeQt::do_mouseClick  () const
//    {
//        if ( m_nativeElem.isNull() ) return false;
//        printf("WebKitDomNodeQt::do_mouseClick\n");
//        QVariant r = m_nativeElem.evaluateJavaScript("var evObj = document.createEvent('MouseEvents');evObj.initEvent( 'click', true, true );this.dispatchEvent(evObj);");
//        return r.toBool();
//    }

//    bool WebKitDomNodeQt::do_mouseEvent (
//            std::string const& 			sEventNames	///< [in] Event names ( comma separated ) to dispatch
//            , boost::int32_t 			iDetail		///< [in] Detail argument from W3C DOM spec.
//            , boost::uint32_t 			iButton		///< [in] Button ( left=0, middle/wheel=1, right=2 )
//            ) const
//    {
//        using namespace cpaf;
//        //FIXME OLD QWebView
////        if ( m_nativeElem.isNull() ) return false;

//        bool bRet = true;
//        StringVecT events;
//        cpaf::splitv	( events, sEventNames, "," );
//        for ( StringVecT::const_iterator it = events.begin(); it != events.end(); ++it ){
//            bRet = bRet && sendMouseEvent( *it, iDetail, iButton );
//        }
//        return bRet;
//    }

//    bool WebKitDomNodeQt::do_inputSet (
//            const std::string& sValue
//            ) const
//    {
//        //FIXME OLD QWebView
////        if ( m_nativeElem.isNull() ) return false;
////            // TODO: New implementation. Use when we have a new published build of QT
////            if ( DomNodeTypes::ELEMENT == m_iNodeType && m_nativeElem.tagName() == "INPUT" ) {
////                m_nativeElem.inputSet(QString::fromUtf8(sValue.c_str()));
////                return true;
////            }
//        return false;
//    }

//    std::string WebKitDomNodeQt::do_innerHtml() const
//    {
//        return "";
//        //FIXME OLD QWebView
////        if ( m_nativeElem.isNull() ) return "";
////        return m_nativeElem.innerHtml().toUtf8().data();
//    }

//    bool WebKitDomNodeQt::do_innerHtmlSet(const string &sValue) const
//    {
//        return false;
//        //FIXME OLD QWebView
////        if ( m_nativeElem.isNull() ) return "";
////        return m_nativeElem.innerHtmlSet(QString::fromUtf8(sValue.c_str()));
//    }

//    std::string WebKitDomNodeQt::do_innerText() const
//    {
//        return "";
//        //FIXME OLD QWebView
////        if ( m_nativeElem.isNull() ) return "";
////        return m_nativeElem.innerText().toUtf8().data();
//    }

//    bool WebKitDomNodeQt::do_innerTextSet(const string &sValue) const
//    {
//        return false;
//        //FIXME OLD QWebView
////        if ( m_nativeElem.isNull() ) return "";
////        return m_nativeElem.innerTextSet(QString::fromUtf8(sValue.c_str()));
//    }

//    bool WebKitDomNodeQt::do_formSubmit () const
//    {
//        //FIXME OLD QWebView
////        if ( m_nativeElem.isNull() ) return false;
////        if ( DomNodeTypes::ELEMENT == m_iNodeType && m_nativeElem.tagName() == "FORM" ) {
////            QVariant r = m_nativeElem.evaluateJavaScript("this.submit();");
////            return r.toBool();
////        }
//        return false;
//    }


//    bool WebKitDomNodeQt::do_formReset () const
//    {
//        //FIXME OLD QWebView
////        if ( m_nativeElem.isNull() ) return false;
////        if ( DomNodeTypes::ELEMENT == m_iNodeType && m_nativeElem.tagName() == "FORM" ) {
////            QVariant r = m_nativeElem.evaluateJavaScript("this.reset();");
////            return r.toBool();
////        }
//        return false;
//    }

//    bool WebKitDomNodeQt::do_javaScriptEvaluate   ( const std::string& sJavaScript ) const
//    {
//        return false;
//        //FIXME OLD QWebView
////        if ( m_nativeElem.isNull() ) return false;
////        m_nativeElem.evaluateJavaScript(sJavaScript.c_str() );
////        return true;
//    }

    // ------------------------------------
    // --- PRIVATE: Node select actions ---
    // ------------------------------------
//    int WebKitDomNodeQt::do_selectLengthGet      () const
//    {
//        //FIXME OLD QWebView
////        if ( m_nativeElem.isNull() ) return -1;
////        if ( DomNodeTypes::ELEMENT == m_iNodeType && m_nativeElem.tagName() == "SELECT" ) {
////            return m_nativeElem.selectLength();
////        }
//        return -1;
//    }

//    int WebKitDomNodeQt::do_selectedIndexGet     () const
//    {
//        //FIXME OLD QWebView
////        if ( m_nativeElem.isNull() ) return -1;
////        if ( DomNodeTypes::ELEMENT == m_iNodeType && m_nativeElem.tagName() == "SELECT" ) {
////            return m_nativeElem.selectSelectedIndex();
////        }
//        return -1;
//    }

//    int WebKitDomNodeQt::do_selectedDomPosGet 	() const
//    {
//        printf("TODO: WebKitDomNodeQt::do_selectedDomPosGet (). Q: We really need this ?\n" );
//        return -1;
//    }

//    bool WebKitDomNodeQt::do_selectIndex		( int iIndex ) const
//    {
//        //FIXME OLD QWebView
////        if ( m_nativeElem.isNull() ) return false;
////        if ( DomNodeTypes::ELEMENT == m_iNodeType && m_nativeElem.tagName() == "SELECT" ) {
////            return m_nativeElem.selectIndex(iIndex);
////        }
//        return false;
//    }


//    // Not used currently.
//    bool WebKitDomNodeQt::do_selectOption () const
//    {
//        using namespace std;
//        //FIXME OLD QWebView
////        if ( m_nativeElem.isNull() )            return false;
////        if ( DomNodeTypes::ELEMENT == m_iNodeType && m_nativeElem.tagName() == "OPTION" ) {
////            boost::shared_ptr<DomNodeIF> parentSelect = optionOwnerSelectNodeGet();
////            if (parentSelect) {
////                parentSelect->selectIndex(6);

////            }
////        }

//        return false;
//    }


//    std::string WebKitDomNodeQt::do_selectValueGet              () const
//    {
//        //FIXME OLD QWebView
////        if ( m_nativeElem.isNull() ) return "";
////        if ( DomNodeTypes::ELEMENT == m_iNodeType && m_nativeElem.tagName() == "SELECT" ) {
////            QString js ("this.options[this.selectedIndex].value");
////            QVariant r = m_nativeElem.evaluateJavaScript(js);
////            return r.toString().toUtf8().data();
////        }
//        return "";
//    }

//    std::string WebKitDomNodeQt::do_selectTextGet              () const
//    {
//        //FIXME OLD QWebView
////        if ( m_nativeElem.isNull() ) return "";
////        if ( DomNodeTypes::ELEMENT == m_iNodeType && m_nativeElem.tagName() == "SELECT" ) {
////            QString js ("this.options[this.selectedIndex].text");
////            QVariant r = m_nativeElem.evaluateJavaScript(js);
////            return r.toString().toUtf8().data();
////        }
//        return "";
//    }

//    std::string WebKitDomNodeQt::do_optionTextGet               () const
//    {
//        printf("TODO: WebKitDomNodeQt::do_optionTextGet ()\n" );
//        return "TODO: do_optionTextGet";
//    }

//    boost::shared_ptr<DomNodeIF> WebKitDomNodeQt::do_selectOptionNodeGet ( int /*iIndex*/ ) const
//    {
//        //printf("TODO: WebKitDomNodeQt::do_selectOptionNodeGet ( int iIndex )\n", iIndex );
//        return boost::shared_ptr<DomNodeIF>();
//    }


//    boost::shared_ptr<DomNodeIF> WebKitDomNodeQt::do_optionOwnerSelectNodeGet    () const
//    {
//        boost::shared_ptr<DomNodeIF> parentSelect = parentNode(1);
//        while ( parentSelect && parentSelect->stringDataUTF8() != "SELECT" ) {
//            parentSelect = parentSelect->parentNode(1);
//        }
//        if (parentSelect && parentSelect->stringDataUTF8() == "SELECT") {
//            return parentSelect;
//        }
//        return boost::shared_ptr<DomNodeIF>();
//    }


    // ----------------------------------------
    // --- PRIVATE: Action helper functions ---
    // ----------------------------------------


    // -----------------------------
    // --- Free helper functions ---
    // -----------------------------

    // TODO: ABSTRACT OUT
    boost::shared_ptr<WebKitDomNodeQt> mkWebKitDomNodeQt(
            int32_t iNodeType
            , const QString& value
            , const QString& sElem
            //FIXME OLD QWebView , const QWebElement& nativeElem
            , boost::shared_ptr<crawl::WebBrowserIF> pOwnerBrowser
            , int iDepthLevel
            )
    {
        return boost::shared_ptr<WebKitDomNodeQt>();
        //FIXME OLD QWebView
//        if (nativeElem.isNull())
//            return boost::shared_ptr<WebKitDomNodeQt>();
//        boost::shared_ptr<WebKitDomNodeQt> node( new WebKitDomNodeQt(iNodeType, value, sElem, nativeElem, pOwnerBrowser, iDepthLevel ) );
//        node->immediateParentNodeSet(node->immediateParentNode());  // Make "direct" parent node pointer.
//        return node;
    }

} // END namespace crawl

/*
//domNewSearch();
//domSeqCreate    ( "artist_name__FIND__SL#2"         , "SPAN, class, med reg, #con:by, /SPAN", "equals", -1 );       // Required: Finds artist name
//domFind("searchStringSelect__FIND");
//domFind("INPUT");
//domStep(1);
domFind("INPUT");
inputSet("Kim");
//domFind(2, "INPUT");
//nodeClick();
//javaScriptExecute("document.getElementById('search_input').value = 'A';");

  */
