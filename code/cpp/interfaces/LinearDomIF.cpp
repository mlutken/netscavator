#include "LinearDomIF.h"

#include <ostream>
#include <iostream>
#include <ranges>
#include <QThread>

#include "DomNodeIF.h"
#include "interfaces_utils.h"
#include <htmlparser/html/Node.h>

using namespace std;


namespace crawl {

// -------------------------------------------------
// --- CONSTRUCTOR / INIT and DESTRUCTOR methods ---
// -------------------------------------------------
boost::shared_ptr<DomNodeIF> LinearDomNode::node() const
{
    return m_node;
}

std::vector<int> LinearDomNode::childPositions() const
{
    std::vector<int> child_positions;
    std::cerr << "LinearDomNode::children() not implemented yet!" << std::endl;

    return child_positions;
}

XPath LinearDomNode::xpath() const
{
    return treeNodeToXPath(m_treeNode);
}


LinearDomNode::LinearDomNode(
        boost::shared_ptr<DomNodeIF> pNode )
    : m_node              ( pNode )
    , m_string_data    ( pNode->stringDataUTF8() )
{
}

LinearDomNode::LinearDomNode(TreeNode* treeNode, boost::shared_ptr<DomNodeIF> node, const std::string& string_data,
                             int parent_pos, int depth_level, int32_t node_type)
    : m_treeNode(treeNode),
      m_node(node),
      m_string_data(string_data),
      m_parent_pos(parent_pos),
      m_depth_level(depth_level),
      m_node_type(node_type)
{
    // NOTE: Make sure cached string is set!
    if (node->getStringDataUTF8Cached().empty()) {
        node->setStringDataUTF8Cached(m_string_data);
    }
}


LinearDomNode::LinearDomNode(TreeNode* treeNode, boost::shared_ptr<DomNodeIF> node, const QString& string_data,
                             int parent_pos, int depth_level, int32_t node_type)
    : m_treeNode(treeNode),
      m_node(node),
      m_string_data(string_data.toUtf8().data()),
      m_parent_pos(parent_pos),
      m_depth_level(depth_level),
      m_node_type(node_type)
{
    // NOTE: Make sure cached string is set!
    if (node->getStringDataUTF8Cached().empty()) {
        node->setStringDataUTF8Cached(m_string_data);
    }
}


LinearDomIF::LinearDomIF(
        boost::shared_ptr<WebBrowserIF> pBrowser
        )
    : m_pBrowser            ( pBrowser )
    , m_PrintNodeFun 		( LinearDomIF::printNode )
    , m_bPrintNodeTypes		( false )
{
}


/** Get position of this postion's ELEMENT node.
     * Ie. Givent a position we want to locate the ELEMENT node associated
     * with it.
     * Works like this:
     * 1) In case it is already and ELEMENT the current positions is returned.
     * 2) In case it is an ATTRIBUE or ATTRIBUTE_VALUE we return the parent (ELEMENT)
     *    pos.
     * 3) In case it is a TEXT node we return the parent ELEMENT node.
     *
     * Basically we return the parent ELEMENT unless the position happens to
     * be an ELEMENT already, in which case we return "ourselves"
    */
LinearDomIF::size_type LinearDomIF::thisElementPos(LinearDomIF::size_type pos) const
{
    if (!posValid(pos)) {
        return 0;
    }
    const auto& node = (*this)[pos];
    if (node.nodeType() & DomNodeTypes::ELEMENT) {
        return pos;
    }
    return node.parentPos();
}

TreeNode* LinearDomIF::treeNode(size_type pos) const
{
    const const_iterator it = posToIterator(pos);
    return (it != end()) ? it->treeNode() : nullptr;
}

TreeNode* LinearDomIF::treeNode(const_iterator it) const
{
    return (it != end()) ? it->treeNode() : nullptr;
}

int LinearDomIF::parentPos(size_type pos, int levels_up) const
{
    if (!posValid(pos)) {
        return 0;
    }

    if ( levels_up < 1 ) levels_up = 1;
    auto parent_pos = pos;

    while ((levels_up > 0) && parent_pos != LinearDomNode::no_owner_pos)	{
        parent_pos = (*this)[parent_pos].parentPos();
        --levels_up;
    }
    if ( levels_up == 0 && parent_pos != LinearDomNode::no_owner_pos) {
        return static_cast<int>(parent_pos);
    }
    return 0;
}

int LinearDomIF::ownerPos(size_type pos, int levels_up) const
{
    if( (*this)[pos].nodeType() & DomNodeTypes::ATTRIBUTE_NODES ) {
        ++levels_up;
    }
    return parentPos(pos, levels_up);
}

LinearDomIF::size_type LinearDomIF::endTagPos(size_type parentPos) const
{
    if (!posValid(parentPos)) { return 0; }
    const TreeNode* node = (*this)[parentPos].treeNode();
    if (!node) { return 0; }
    return treeNodeToPos(endTagNode(node));
}

std::vector<LinearDomIF::size_type> LinearDomIF::childPositions(
        const size_type pos, const std::string& tagName ) const
{
    if (!posValid(pos)) {
        return std::vector<size_type>{};
    }

    const TreeNode* node = (*this)[pos].treeNode();
    if (!node) {
        return std::vector<size_type>{};
    }

    return treeNodesToPositions(children(node, tagName));
}

std::vector<LinearDomIF::size_type> LinearDomIF::childPositionsAll(const size_type pos) const
{
    const TreeNode* node = (*this)[pos].treeNode();
    return treeNodesToPositions(node->children());
}


std::string LinearDomIF::attribute(const LinearDomIF::size_type pos,
                                   const string& key, const string& default_val) const
{
    const auto elem_pos = thisElementPos(pos);
    if (!posValid(elem_pos)) {
        return default_val;
    }
    const TreeNode* node = (*this)[pos].treeNode();

    const auto& attribs = node->data.attributes();
    auto finder = [key](const Node::Attribute& attribute) { return attribute.name == key; };
    const auto it = std::ranges::find_if(attribs, finder);

    if (it != attribs.end()) {
        return it->value;
    }

    return default_val;
}

string LinearDomIF::toXPathStringList(const std::vector<int>& domPositions) const
{
    string xpathList;
    auto count = 0;
    for (size_type pos : domPositions) {
        auto xp = toXPath(pos);
        if (!xp.empty()) {
            if (count > 0) { xpathList.append(1, ','); }
            xpathList.append(xp.toString());
            ++count;
        }
    }
    return xpathList;
}

XPath LinearDomIF::toXPath(const size_type pos) const
{
    const auto* tn = treeNode(pos);
    return tn ? treeNodeToXPath(tn) : XPath{};
}

XPath LinearDomIF::toXPath(const_iterator it) const
{
    const auto* tn = treeNode(it);
    return tn ? treeNodeToXPath(tn) : XPath{};
}

// --------------------
// --- Misc methods ---
// --------------------

void LinearDomIF::pushBackNode ( const LinearDomNode& node )
{
    m_LinearNodes.push_back (node);
    m_LinearNodes.back().thisPosSet(lastDomPos());
}

void LinearDomIF::clearNodes ()
{
    m_LinearNodes.clear();
}


LinearDomIF::const_iterator LinearDomIF::posToIterator( size_type iDomPos ) const
{
    if (!posValid(iDomPos)){
        return end();
    }
    return begin() -1 + static_cast<ptrdiff_t>(iDomPos);
}

LinearDomIF::size_type LinearDomIF::iteratorToPos    ( const_iterator it ) const
{
    if ( it >= end() || it < begin() ) return 0;
    return static_cast<size_type>(it - begin()) +1;
}

LinearDomIF::size_type LinearDomIF::treeNodeToPos(const TreeNode* treeNode) const
{
    return iteratorToPos(findFromTreeNode(treeNode));
}

std::vector<LinearDomIF::size_type> LinearDomIF::treeNodesToPositions(std::vector<TreeNode*> treeNodes) const
{
    std::vector<LinearDomIF::size_type> positions;
    for (auto* treeNode: treeNodes) {
        positions.push_back(treeNodeToPos(treeNode));
    }
    return positions;
}

std::vector<LinearDomIF::size_type> LinearDomIF::treeNodesToPositions(std::vector<const TreeNode*> treeNodes) const
{
    std::vector<LinearDomIF::size_type> positions;
    for (const auto* treeNode: treeNodes) {
        positions.push_back(treeNodeToPos(treeNode));
    }
    return positions;
}

void LinearDomIF::print(
        std::ostream& os,  			///< output stream to print to
        bool bPrintNodeTypes		///< [in] Print nodes types as well.
        ) const
{
    using namespace std ;
    for ( auto it = cbegin() ; it != cend(); ++it ) {
        m_PrintNodeFun ( it->node(), os, true, bPrintNodeTypes );
    }
}

const LinearDomNode &LinearDomIF::operator[](size_type domPos) const
{
    return m_LinearNodes[static_cast<internal_size_type>(domPos-1)];
}

LinearDomNode &LinearDomIF::operator[](size_type domPos)
{
    return m_LinearNodes[static_cast<internal_size_type>(domPos-1)];
}



// ----------------------
// --- Static methods ---
// ----------------------

/** String representation of node. */
std::string
LinearDomIF::nodeToString	(
        boost::shared_ptr<DomNodeIF> pNode,     ///< DomNodeIF (pointer) to convert to string representation.
        bool /*bTrimBlanks*/,
        bool bPrintNodeType )                   ///< Print node type as well .
{
    using namespace std;
    std::string s;
    string sNodeType("");
    if ( bPrintNodeType )	sNodeType = "[" + nodeTypeToString ( pNode ) + "]" ;

    if ( 		pNode->nodeType() 	== DomNodeTypes::ATTRIBUTE ) {
        s.append ( sNodeType + pNode->stringDataUTF8() +  "=" );
    }
    else if ( 	pNode->nodeType() 	== DomNodeTypes::TEXT ) {
        s.append ( ">" + sNodeType + pNode->stringDataUTF8() + "< " );
    }
    else if ( 	pNode->nodeType() 	== DomNodeTypes::ATTRIBUTE_VALUE ) {
        s.append ( "\"" + sNodeType + pNode->stringDataUTF8() + "\" " ) ;
    }
    else if ( 	pNode->nodeType() 	== DomNodeTypes::COMMENT ) {
        s.append ( "<!-- " + sNodeType + pNode->stringDataUTF8() + " --> " );
    }
    else if ( 	pNode->nodeType() 	== DomNodeTypes::DOCUMENT ) {
        s.append ( sNodeType + pNode->stringDataUTF8() + " " );
    }
    else {
        s.append ( "<" + sNodeType + pNode->stringDataUTF8() + " " ) ;
    }
    return s;
}

/** Print a node linear dom mode mode. Very similar to the linear dom view
     * in minercreator just with the type appended each line in square brackets.
     * Sample output here:
     *
     * A [ELEMENT]
     * class [ATTRIBUTE]
     * amshopby-attr [ATTRIBUTE_VALUE]
     * href [ATTRIBUTE]
     * https://www.hellorider.dk/cykler/-/racercykler/lightweight [ATTRIBUTE_VALUE]
     * Lightweight [TEXT]
     * /A [ELEMENT_END_TAG]
       */
void LinearDomIF::printNode		(
        boost::shared_ptr<DomNodeIF> pNode, ///< DDomNodeIFOMNode (pointer) to print.
        std::ostream& os,                   ///< Stream to print to
        bool /*bTrimBlanks*/,
        bool bPrintNodeType )               ///< Print node type as well .
{
    using namespace std;
    os << pNode->stringDataUTF8();
    if ( bPrintNodeType ) os << " [" + nodeTypeToString ( pNode ) + "]" ;
    os << "\n";
}

void LinearDomIF::dbgPrintLinearDom() const
{
    cout << "this: " << this << " DBG, LinearDomIF::dbgPrint() called from thread: "<< QThread::currentThreadId() << endl;
    const auto& linearDom = *this;
    for ( int pos = 1 ; pos <= linearDom.size(); pos++) {
        const auto& nodeValCached = linearDom[pos].stringData();
        const auto& nodeValDirect = linearDom[pos].node()->stringDataUTF8();
        cout << "nodeType: '" << linearDom[pos].node()->nodeType() << "' (" << pos << "): '" << nodeValCached << "' == '" << nodeValDirect << "'" << endl;
        if (nodeValDirect == "") {
            cout << "ERROR! nodeType: '" << linearDom[pos].node()->nodeType() << "' (" << pos << "): '" << nodeValCached << "' == '" << nodeValDirect << "'" << endl;
            return;
            //                cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXX" << endl;
        }
    }

}

/** Set data for the last added linear dom node.
        called from pushBackNode()
        TODO: Not implemented !*/
void LinearDomIF::setDataForLastAddedLinearDomNode()
{
    //        LinearDomNode& ldn = m_LinearNodes.back();
    //ldn.ownerIndexSet();
}

LinearDomIF::const_iterator LinearDomIF::do_findFromTreeNode(const TreeNode* pNativeNode) const
{
    return std::find_if(begin(), end(), [pNativeNode](const LinearDomNode& domNode) {
        return domNode.treeNode() == pNativeNode;
    });
}

LinearDomIF::const_iterator LinearDomIF::do_findFromXPath(const XPath& xpath) const
{
    const auto* treeNode = xPathToTreeNode(rootNode(), xpath);
    if (treeNode) {
        auto it = findFromTreeNode(treeNode);
        return it;
    }
    return end();

}


} // END namespace crawl

