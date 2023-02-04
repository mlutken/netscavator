#include "WebKitDomDocumentLinearQt.h"

#include <stdio.h>
#include <iostream>
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>
#include <utils/cpaf_json_utils.h>
#include <interfaces_utils.h>
#include <WebKitDomNodeQt.h>

namespace crawl {

//FIXME NEW QWebView
void parseJsonRecursive(const nlohmann::json& object, WebKitDomDocumentLinearQt* webkit_dom,
                        boost::shared_ptr<WebBrowserIF> browser, int depth, int parentPos)
{
}


//FIXME OLD QWebView
//    void parseJsonRecursive(const nlohmann::json& object, WebKitDomDocumentLinearQt* webkit_dom,
//                            boost::shared_ptr<WebBrowserIF> browser,
//                            QWebElement webElement, int depth, int parentPos)
//    {
//        if (object.is_object()){
//            for (auto& item : object.items()) {
//                constexpr auto nodetype = DomNodeTypes::ATTRIBUTE;
//                const QString key = QString::fromUtf8(item.key().c_str());
//                auto n = mkWebKitDomNodeQt(nodetype,  key, "", webElement, browser, depth);
//                webkit_dom->pushBackNode ( LinearDomNode(n, item.key(), parentPos, depth, nodetype) );
//                parseJsonRecursive(item.value(), webkit_dom, browser, webElement, depth +1, parentPos);
//            }
//        }
//        else if (object.is_array()){
//            for (auto& item : object.items()) {
//                parseJsonRecursive(item.value(), webkit_dom, browser, webElement, depth +1, parentPos);
//            }
//        }
//        else {
//            constexpr auto nodetype = DomNodeTypes::ATTRIBUTE_VALUE;
//            const std::string val_str = cpaf::simple_json_to_string(object);
//            const QString value = QString::fromUtf8(val_str.c_str());
//            auto n = mkWebKitDomNodeQt(nodetype, value, "", webElement, browser, depth);
//            webkit_dom->pushBackNode ( LinearDomNode(n, val_str, parentPos, depth, nodetype) );
//        }
//    }

    // -------------------------------------------------
    // --- CONSTRUCTOR / INIT and DESTRUCTOR methods ---
    // -------------------------------------------------

    WebKitDomDocumentLinearQt::WebKitDomDocumentLinearQt (
            boost::shared_ptr<crawl::WebBrowserIF> pBrowser
            )
        : LinearDomIF(pBrowser)
    {
    }



    WebKitDomDocumentLinearQt::~WebKitDomDocumentLinearQt()
    {
    }


    // -----------------------------------------
    // --- PRIVATE: Implementation functions ---
    // -----------------------------------------
    // http://sleipnerexamples.com.localhost/sites/TestDomTree/index.html

//    LinearDomIF::const_iterator WebKitDomDocumentLinearQt::do_findFromRawPointer ( boost::shared_ptr<DomNodeIF> pDomNode ) const
//    {
//        //FIXME NEW QWebView
//        WebKitDomDocumentLinearQt::const_iterator itEND = end();
//        //FIXME OLD QWebView
////        if ( !pDomNode ) return itEND;
////        QWebElement* pNativeElemLookFor = static_cast<QWebElement*>( pDomNode->nativeNodePtr() );
////        boost::shared_ptr<WebKitDomNodeQt> pNodeLookFor = boost::static_pointer_cast<WebKitDomNodeQt>( pDomNode );


////        for ( WebKitDomDocumentLinearQt::const_iterator it = begin(); it != itEND; ++it	) {
////            QWebElement* pNativeElemCompare = static_cast<QWebElement*>( it->node()->nativeNodePtr() );
////            boost::shared_ptr<WebKitDomNodeQt> pNodeCompare = boost::static_pointer_cast<WebKitDomNodeQt>( it->node() );
////            if ( *pNativeElemLookFor        == *pNativeElemCompare  &&
////                 pDomNode->nodeType()       == it->node()->nodeType() &&
////                 pNodeLookFor->elemString() == pNodeCompare->elemString()
////                 )	{
////                return it;
////            }
////        }
//        return itEND;
//    }

//    LinearDomIF::const_iterator WebKitDomDocumentLinearQt::do_findFromNodeTreePointer (const void* pNativeNode ) const
//    {
//        WebKitDomDocumentLinearQt::const_iterator itEND = end();
//        if ( !pNativeNode ) return itEND;

//        //FIXME NEW QWebView
//        //FIXME OLD QWebView
////        QWebElement* pNativeElemLookFor = static_cast<QWebElement*>(pNativeNode);
////        for ( WebKitDomDocumentLinearQt::const_iterator it = begin(); it != itEND; ++it	) {
////            QWebElement* pNativeElemCompare = static_cast<QWebElement*>( it->node()->nativeNodePtr() );
////            if ( *pNativeElemLookFor == *pNativeElemCompare  )	{
////                return it;
////            }
////        }
//        return itEND;

//    }


    // ---------------------------------
    // --- PRIVATE: Helper functions ---
    // ---------------------------------

    /** Gets a trimmed string containing the TEXT( toPlainText() ) of the element. If the
        text only has spaces the returned (trimmed) string will be empty. */
//FIXME OLD QWebView     QString WebKitDomDocumentLinearQt::getText( const QWebElement& e ) const
    QString WebKitDomDocumentLinearQt::getText() const
    {
        return "TODO WebKitDomDocumentLinearQt::getText()";
        //FIXME OLD QWebView return e.toPlainText().simplified();
    }

    /** Returns true if all the children of this node has empty TEXT parts. */
//FIXME OLD QWebView     int WebKitDomDocumentLinearQt::countChildrenWithText( const QWebElement& e ) const
    int WebKitDomDocumentLinearQt::countChildrenWithText() const
    {
        return 0; //FIXME NEW QWebView
        //FIXME OLD QWebView
//        int count = 0;
//        QWebElement child = e.firstChild();
//        while ( !child.isNull() ) {
//            if ( getText(child) != "" ) {
//                count++;
//            }
//            child = child.nextSibling();
//        }
//        return count;
    }

    /** Returns the (simplified) concatenation of all childrens TEXT parts. */
//FIXME OLD QWebView     QString WebKitDomDocumentLinearQt::getChildrensText( const QWebElement& e ) const
    QString WebKitDomDocumentLinearQt::getChildrensText() const
    {
        return "TODO: WebKitDomDocumentLinearQt::getChildrensText()";
        //FIXME OLD QWebView
//        QString sText;
//        QWebElement child = e.firstChild();
//        int count = 0;
//        while ( !child.isNull() ) {
//            if ( 0 != count++ ) sText += " ";
//            sText += getText(child);
//            child = child.nextSibling();
//        }
//        return sText.simplified();
    }

//FIXME OLD QWebView
//    QWebFrame* WebKitDomDocumentLinearQt::getNextSubFrame ()
//    {
//        m_iFrameCounter++;
//        if ( m_iFrameCounter >= m_frames.size() ) return NULL;
//        return m_frames.at(m_iFrameCounter);
//    }

    void WebKitDomDocumentLinearQt::indexTokenWords(const QString& /*text*/)
    {

    }

    //FIXME NEW QWebView
    void WebKitDomDocumentLinearQt::recurseCreateLinearDom(
              int iDepthLevel,
              int parent_pos
            )
    {
    }

    // http://sleipnerexamples.com.localhost/sites/TestDomTree/index.html
    //FIXME OLD QWebView
//    void WebKitDomDocumentLinearQt::recurseCreateLinearDom(
//               QWebElement e,           ///< DOMNode (pointer) to recurse from.
//              int iDepthLevel,
//              int parent_pos
//            )
//    {
//        using namespace std;

//        if ( 1 == e.nodeTypeCrawler()) {
//            auto n = mkWebKitDomNodeQt(DomNodeTypes::ELEMENT,"", "", e, m_pBrowser, iDepthLevel);
//            pushBackNode ( LinearDomNode(n, n->stringDataUTF8(), parent_pos, iDepthLevel, DomNodeTypes::ELEMENT) );
//        }
//        else if ( 3 == e.nodeTypeCrawler()) { // TEXT nodes
//            const QString text = e.textNodeValue().trimmed();
//            if (!text.isEmpty()) {
//                bool add_single_normal_node = true;
//                if ( text.startsWith("{") || text.startsWith("[")) {
//                    add_single_normal_node = false;
//                    try {
//                        const std::string value = text.toUtf8().constData();
//                        const auto trimmed = boost::algorithm::replace_all_copy( value, std::string("\n"), std::string(" ") );
//                        auto json_object = cpaf::parse_non_strict(trimmed);
//                        parseJsonRecursive(json_object, this, m_pBrowser, e, iDepthLevel, parent_pos);

//                    } catch (std::exception e) {
//                        add_single_normal_node = true;
//                    }
//                }

//                if (add_single_normal_node) {
//                    auto n = mkWebKitDomNodeQt(DomNodeTypes::TEXT, "", "", e, m_pBrowser, iDepthLevel);
//                    pushBackNode ( LinearDomNode(n, n->stringDataUTF8(), parent_pos, iDepthLevel, DomNodeTypes::TEXT) );
//                }
//            }

//        }
//        auto this_index = lastDomPos();

//        if  ( 1 == e.nodeTypeCrawler() ) {
//            QStringList attribNames = e.attributeNames();
//            auto it             = attribNames.begin();
//            const auto itEND    = attribNames.end();

//            for ( ; it != itEND; ++it ) {
//                auto n = mkWebKitDomNodeQt(DomNodeTypes::ATTRIBUTE, "", *it, e, m_pBrowser, iDepthLevel);
//                pushBackNode ( LinearDomNode(n, n->stringDataUTF8(), this_index, iDepthLevel, DomNodeTypes::ATTRIBUTE) );
//                if ( e.attribute(*it).simplified() != "" ) {
//                    auto n = mkWebKitDomNodeQt(DomNodeTypes::ATTRIBUTE_VALUE, "", *it, e, m_pBrowser, iDepthLevel);
//                    pushBackNode ( LinearDomNode(n, n->stringDataUTF8(), this_index, iDepthLevel, DomNodeTypes::ATTRIBUTE_VALUE) );
//                }
//            }
//            QWebElement child = e.firstChildCrawler();
//            while ( !child.isNull() ) {
//                recurseCreateLinearDom(child, iDepthLevel+1, this_index );
//                child = child.nextSiblingCrawler();
//            }
//            if ( e.tagName() != "BR" ) {
//                if ( e.tagName() == "FRAME" || e.tagName() == "IFRAME" ) {
//                    QWebFrame* pFrame = getNextSubFrame();
//                    if ( pFrame ) {
//                        QWebElement frameTopElem = pFrame->documentElement();
//                        recurseCreateLinearDom( frameTopElem, iDepthLevel+1, this_index );
//                    }
//                }

//                // Add the "END" tag as a node also
//                auto n = mkWebKitDomNodeQt(DomNodeTypes::ELEMENT_END_TAG, "", "", e, m_pBrowser, iDepthLevel);
//                pushBackNode ( LinearDomNode(n, n->stringDataUTF8(), this_index, iDepthLevel, DomNodeTypes::ELEMENT_END_TAG) );
//            }
//        }
//    }


///////////////////////////77


    void WebKitDomDocumentLinearQt::wordMonitorSet(WordMonitor *wordMonitor)
    {
        m_wordMonitor = wordMonitor;
    }


    //FIXME OLD QWebView
//    void WebKitDomDocumentLinearQt::createWebKitLinearDomFromNodeQt(
//            boost::shared_ptr<WebBrowserIF>                 pBrowser
//            , const QWebElement&                            topElem             ///< Dom/Web element to recurse from.
//            , QWebPage*                                     pWebPage            ///< Owning webpage
//            )
//    {
//        m_pBrowser = pBrowser;
//        m_topElem = topElem;
//        m_pWebPage = pWebPage;
//        m_frames = pWebPage->mainFrame()->childFrames();
//        m_iFrameCounter = -1;
//        m_wordMonitor = pBrowser->wordMonitor();
//        recurseCreateLinearDom( topElem, 0, 0 );
//        if (size() != 0) {
//            const auto& first_node = (*this)[firstDomPos()];
//            const auto& first_node_string = first_node.qstringData();
//            auto& last_node = (*this)[lastDomPos()];
//            const auto& last_node_string= last_node.qstringData();
//            const auto expected_last_node_string = QString("/") + first_node_string;
//            if (expected_last_node_string != last_node_string) {
//                auto n = mkWebKitDomNodeQt(first_node.nodeType(), "", "", topElem, m_pBrowser, 0);
//                pushBackNode ( LinearDomNode(n, expected_last_node_string, 0, 0, DomNodeTypes::ELEMENT_END_TAG) );
//            }
//        }
//        // Fix the top node(s) parent ... We have two since we insert the artificial "/HTML"
//        (*this)[firstDomPos()].parentPosSet(LinearDomNode::no_owner_pos);
//        (*this)[lastDomPos()].parentPosSet(LinearDomNode::no_owner_pos);
//    }



    void createWebKitLinearDomFromNodeQt(
            boost::shared_ptr<WebBrowserIF>                 pBrowser
            , boost::shared_ptr<WebKitDomDocumentLinearQt>  pLinearDom          ///< LinearDom document to add nodes to/build
//FIXME OLD QWebView             , const QWebElement&                            topElem             ///< Dom/Web element to recurse from.
//FIXME OLD QWebView             , QWebPage*                                     pWebPage            ///< Owning webpage
            )
    {
 //FIXME OLD QWebView        pLinearDom->createWebKitLinearDomFromNodeQt( pBrowser, topElem, pWebPage );
    }
} // END namespace crawl



