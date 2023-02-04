#include "SimpleDomNode.h"

#include <iostream>
#include <boost/algorithm/string.hpp>
#include <html/ParserDom.h>
#include <cpaf_libs/utils/cpaf_string_utils.hpp>


#include <utils/utils.h>
#include <LinearDomIF.h>
#include <BoxObjectIF.h>
#include <WebBrowserIF.h>
#include <url/Url.h>
#include <utility>

using namespace std;

// DOM geometry: http://www.quirksmode.org/dom/tests/elementdimensions.html



namespace crawl {

// ------------------
// --- SimpleDomNode ---
// ------------------


SimpleDomNode::SimpleDomNode(int32_t iNodeType,
                             const std::string& value,
                             const AttributesMap& attributes,
                             boost::shared_ptr<crawl::WebBrowserIF> pOwnerBrowser,
                             int iDepthLevel,
                             crawl::TreeNode* treeNode
                             )
    : DomNodeIF     ( pOwnerBrowser, iDepthLevel )
    , m_iNodeType   ( iNodeType     )
    , m_value       ( value         )
    , m_attributes  ( attributes    )
    , m_treeNode    ( treeNode      )
{
}

SimpleDomNode::~SimpleDomNode() = default;

// -------------------------------------
// --- PRIVATE: Structural functions ---
// -------------------------------------

/** Get immediate/direct (first level) parent node, by using the underlying "native"
        browser "framework". This is only OK to do from main thread */
boost::shared_ptr<DomNodeIF> SimpleDomNode::do_immediateParentNodeNative() const
{
    return boost::shared_ptr<DomNodeIF>(); // TODO: Fix this... Perhaps.
}

//bool SimpleDomNode::do_hasChildNodes () const
//{
//    return false; // TODO: Fix this.
//}

//boost::shared_ptr<BoxObjectIF> SimpleDomNode::do_getBoxObject () const
//{
//    return boost::shared_ptr<BoxObjectIF>();
//}

//std::vector<boost::shared_ptr<DomNodeIF>> SimpleDomNode::do_childNodesGet () const
//{
//    std::vector<boost::shared_ptr<DomNodeIF>> nodes;
//    // TODO: Fix this.
//    return nodes;
//}

//boost::shared_ptr<DomNodeIF> SimpleDomNode::do_firstChild () const
//{
//    return boost::shared_ptr<DomNodeIF>(); // TODO: Fix this.
//}

//boost::shared_ptr<DomNodeIF> SimpleDomNode::do_lastChild () const
//{
//    return boost::shared_ptr<DomNodeIF>(); // TODO: Fix this.
//}

//boost::shared_ptr<DomNodeIF> SimpleDomNode::do_previousSibling () const
//{
//    return boost::shared_ptr<DomNodeIF>(); // TODO: Fix this.
//}

//boost::shared_ptr<DomNodeIF> SimpleDomNode::do_nextSibling () const
//{
//    return boost::shared_ptr<DomNodeIF>(); // TODO: Fix this.
//}


// ------------------------------------
// --- PRIVATE: Attribute functions ---
// ------------------------------------
//std::string SimpleDomNode::do_attributeGet (
//        const std::string& sName
//        ) const
//{
//    return ""; // TODO: Fix this.
//}

//void SimpleDomNode::do_attributeSet (
//        const std::string& sName
//        ,const std::string& sValue
//        )
//{
//    // TODO: Fix this.
//}

//void SimpleDomNode::do_attributesGet    ( AttributesMap& attributes ) const
//{
//    attributes = m_attributes;
//}

// -------------------------------
// --- PRIVATE: Info functions ---
// -------------------------------
QString SimpleDomNode::do_qstringDataGet () const
{
    return crawl::toQString(m_value);
}

std::string SimpleDomNode::do_stringDataUTF8Get () const
{
    return qstringDataGet().toUtf8().data();
}

//std::string SimpleDomNode::do_nodeNameGet  () const
//{
//    return ""; // TODO: Fix this.
//}

//std::string SimpleDomNode::do_nodeValueGet () const
//{
//    return ""; // TODO: Fix this.
//}

//std::string SimpleDomNode::do_nodeTextGet () const
//{
//    return ""; // TODO: Fix this.
//}

//std::string SimpleDomNode::do_nodeTextAllRecurGet () const
//{
//    return ""; // TODO: Fix this.
//}


//// TODO: Fix %25 problems see imusic.dk script. NOTE: Should be fixed, but check that it is
//std::string SimpleDomNode::do_hrefGet () const
//{
//    return ""; // TODO: Fix this.
//    //        if ( m_nativeElem.isNull() ) return "";
//    //        if ( DomNodeTypes::ELEMENT == m_iNodeType && m_nativeElem.tagName() == "A" ) {
//    //            std::string s = m_nativeElem.attribute("href").toUtf8().data();
//    //            return s;
//    //        }
//    //        return "";
//}

//std::string SimpleDomNode::do_hrefCompleteGet () const
//{
//    return ""; // TODO: Fix this.
//}


void* SimpleDomNode::do_nativeNodePtrGet  () const
{
    return m_treeNode;
}

boost::uint32_t SimpleDomNode::do_nodeTypeGet () const
{
    return m_iNodeType;
}

crawl::XPath SimpleDomNode::do_xpathGet() const
{
    return crawl::treeNodeToXPath(m_treeNode);
}


// -----------------------------
// --- PRIVATE: Node actions ---
// -----------------------------
bool SimpleDomNode::do_click () const
{
    //        const auto xpath =
    cerr << "FIXMENM WebKitDomNodeQt::do_click xpath: '" << xpath().toString() <<  "'\n";

    std::string js;
    js.append("var elem1 = document.evaluate(\n");
    js.append("'");
    js.append(xpath().toString());
    js.append("',\n");
    js.append("document,\n");
    js.append("null,\n");
    js.append("XPathResult.FIRST_ORDERED_NODE_TYPE,\n");
    js.append("null\n");
    js.append(").singleNodeValue;\n");
    js.append("elem1.click();\n");
    cerr << "FIXMENM JS:\n" << js <<  "\n";

    string retval_unused;
    ownerBrowser()->javaScriptExecuteRetVal(js, retval_unused);
    return true; // TODO: Fix this. We can make it work for at least <A href= ... tags
}


//    bool SimpleDomNode::do_mouseClick  () const
//    {
//        if ( m_nativeElem.isNull() ) return false;
//        printf("SimpleDomNode::do_mouseClick\n");
//        QVariant r = m_nativeElem.evaluateJavaScript("var evObj = document.createEvent('MouseEvents');evObj.initEvent( 'click', true, true );this.dispatchEvent(evObj);");
//        return r.toBool();
//    }

//bool SimpleDomNode::do_mouseEvent (
//        std::string const& 			sEventNames	///< [in] Event names ( comma separated ) to dispatch
//        , boost::int32_t 			iDetail		///< [in] Detail argument from W3C DOM spec.
//        , boost::uint32_t 			iButton		///< [in] Button ( left=0, middle/wheel=1, right=2 )
//        ) const
//{
//    return false;
//}

//bool SimpleDomNode::do_inputSet (
//        const std::string& sValue
//        ) const
//{
//    return false;
//}

//std::string SimpleDomNode::do_innerHtml() const
//{
//    return ""; // TODO: Fix this.
//}

//bool SimpleDomNode::do_innerHtmlSet(const string &sValue) const
//{
//    return false; // TODO: Fix this.
//}

//std::string SimpleDomNode::do_innerText() const
//{
//    return ""; // TODO: Fix this.
//}

//bool SimpleDomNode::do_innerTextSet(const string &sValue) const
//{
//    return false; // TODO: Fix this.
//}

//bool SimpleDomNode::do_formSubmit () const
//{
//    return false; // TODO: Fix this.
//}


//bool SimpleDomNode::do_formReset () const
//{
//    return false; // TODO: Fix this.
//}

//bool SimpleDomNode::do_javaScriptEvaluate   ( const std::string& sJavaScript ) const
//{
//    return false;
//}

// ------------------------------------
// --- PRIVATE: Node select actions ---
// ------------------------------------
//int SimpleDomNode::do_selectLengthGet      () const
//{
//    // TODO: Fix this.
//    return -1;
//}

//int SimpleDomNode::do_selectedIndexGet     () const
//{
//    // TODO: Fix this.
//    return -1;
//}

//int SimpleDomNode::do_selectedDomPosGet 	() const
//{
//    // TODO: Fix this.
//    return -1;
//}

//bool SimpleDomNode::do_selectIndex (int index) const
//{
//    // TODO: Fix this.
//    return false;
//}


//// Not used currently.
//bool SimpleDomNode::do_selectOption () const
//{
//    // TODO: Fix this.
//    return false;
//}


//std::string SimpleDomNode::do_selectValueGet              () const
//{
//    return ""; // TODO: Fix this.
//}

//std::string SimpleDomNode::do_selectTextGet              () const
//{
//    return ""; // TODO: Fix this.
//}

//std::string SimpleDomNode::do_optionTextGet               () const
//{
//    return ""; // TODO: Fix this.
//}

//boost::shared_ptr<DomNodeIF> SimpleDomNode::do_selectOptionNodeGet ( int /*iIndex*/ ) const
//{
//    // TODO: Fix this.
//    return boost::shared_ptr<DomNodeIF>();
//}


//boost::shared_ptr<DomNodeIF> SimpleDomNode::do_optionOwnerSelectNodeGet () const
//{
//    // TODO: Fix this.
//    return boost::shared_ptr<DomNodeIF>();
//}


// ----------------------------------------
// --- PRIVATE: Action helper functions ---
// ----------------------------------------
// -----------------------------
// --- Free helper functions ---
// -----------------------------
boost::shared_ptr<SimpleDomNode> makeSimpleDomNode(int32_t nodeType
                                                   , const string& value
                                                   , const AttributesMap& attributes
                                                   , boost::shared_ptr<crawl::WebBrowserIF> ownerBrowser
                                                   , int depthLevel
                                                   , crawl::TreeNode* treeNode)
{
    boost::shared_ptr<SimpleDomNode> node(
                new SimpleDomNode(nodeType, value, attributes, ownerBrowser, depthLevel, treeNode ) );
    return node;
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
