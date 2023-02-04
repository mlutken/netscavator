#include "ParserDom.h"
#include "wincstring.h"

#include <string_view>
#include <iostream>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <cpaf_libs/unicode/cpaf_u8string_utils.h>


//#define DEBUG
#include "debug.h"

#define TAG_NAME_MAX 10

namespace ba = boost::algorithm;
using namespace std;
using namespace kp; 
using namespace cpaf::unicode;

namespace crawl {

bool shouldAppendChild(const crawl::Node& node)
{
    const std::string& tag = node.tagName();
    const bool tagNameEmpty = empty_or_only_white_space(tag.begin(), tag.end());
//    std::cerr << "FIXMENM Append '" << node.tagName() << "'\n";
    return !tagNameEmpty && !node.isComment();
}

std::unique_ptr<DomTree> ParserDom::parseTree(std::string_view html)
{
    m_domTree = std::make_unique<DomTree>();
    parse(html);
    return std::move(m_domTree);
}
void ParserDom::beginParsing()
{
    m_domTree->clear();
    tree<crawl::Node>::iterator top = m_domTree->begin();
    crawl::Node lambda_node;
    lambda_node.offset(0);
    lambda_node.length(0);
    lambda_node.isTag(true);
    lambda_node.isComment(false);
    m_currentState = m_domTree->insert(top,lambda_node);
}

void ParserDom::endParsing()
{
    tree<crawl::Node>::iterator top = m_domTree->begin();
    top->length(mCurrentOffset);
}

void ParserDom::foundComment(Node node)
{
    //Add child content node, but do not update current state
    if (shouldAppendChild(node)) {
        m_domTree->append_child(m_currentState, node);
    }
}

void ParserDom::foundText(Node node)
{
    //Add child content node, but do not update current state
    if (shouldAppendChild(node)) {
        m_domTree->append_child(m_currentState, node);
    }
}

void ParserDom::foundTag(Node node, bool isEnd)
{
    if (!isEnd)
    {
        //append to current tree node
        tree<crawl::Node>::iterator next_state;
        if (shouldAppendChild(node)) {
            next_state = m_domTree->append_child(m_currentState, node);
        }
        m_currentState = next_state;
    }
    else
    {   // --- end-tag ---
        //Look if there is a pending open tag with that same name upwards
        //If mCurrentState tag isn't matching tag, maybe a some of its parents
        // matches
        vector< tree<crawl::Node>::iterator > path;
        tree<crawl::Node>::iterator i = m_currentState;
        bool found_open = false;
        while (i != m_domTree->begin())
        {
#ifdef DEBUG
            cerr << "comparing " << node.tagName() << " with " << i->tagName()<<endl<<":";
            if (!i->tagName().length()) cerr << "Tag with no name at" << i->offset()<<";"<<i->offset()+i->length();
#endif
            assert(i->isTag());
            assert(i->tagName().length());

            bool equal;
            const char *open = i->tagName().c_str();
            const char *close = node.tagName().c_str();
            equal = !(strcasecmp(open,close));


            if (equal)
            {
                DEBUGP("Found matching tag %s\n", i->tagName().c_str());
                //Closing tag closes this tag
                //Set length to full range between the opening tag and
                //closing tag
                i->length(node.offset() + node.length() - i->offset());
                i->closingText(node.text());

                m_currentState = m_domTree->parent(i);
                found_open = true;
                node.isEndTag(true);
                if (shouldAppendChild(node)) {
                    m_domTree->append_child(i, node);
                }
                break;
            }
            else
            {
                path.push_back(i);
            }

            i = m_domTree->parent(i);
        }

        if (found_open)
        {
            //If match was upper in the tree, so we need to invalidate child
            //nodes that were waiting for a close
            for (unsigned int j = 0; j < path.size(); ++j)
            {
                //				path[j]->length(node.offset() - path[j]->offset());
                m_domTree->flatten(path[j]);
            }
        }
        else
        {
            DEBUGP("Unmatched tag %s\n", node.text().c_str());

            // Treat as comment
            node.isTag(false);
            node.isComment(true);
            if (shouldAppendChild(node)) {
                m_domTree->append_child(m_currentState, node);
            }
        }
    }
}

ostream &operator<<(ostream &stream, const tree<crawl::Node> &tr)
{

    tree<crawl::Node>::pre_order_iterator it = tr.begin();
    tree<crawl::Node>::pre_order_iterator end = tr.end();

    int rootdepth = tr.depth(it);
    stream << "-----" << endl;

    unsigned int n = 0;
    while ( it != end )
    {

        int cur_depth = tr.depth(it);
        for(int i=0; i < cur_depth - rootdepth; ++i) stream << "  ";
        stream << n << "@";
        stream << "[" << it->offset() << ";";
        stream << it->offset() + it->length() << ") ";
        stream << (string)(*it) << endl;
        ++it, ++n;
    }
    stream << "-----" << endl;
    return stream;
}

// ----------------------
// --- Node functions ---
// ----------------------

TreeNode* endTagNode(const TreeNode* parentNode)
{
    if (!parentNode) { return nullptr; }
    auto* child_node = parentNode->first_child;
    if (child_node == nullptr) return nullptr;

    while(child_node) {
        if (child_node->data.isEndTag()) {
            return child_node;
            break;
        }
        child_node = child_node->next_sibling;
    }
    return nullptr;
}

std::vector<TreeNode*> children(const TreeNode* parentNode) {
    return children(parentNode, "");
}

std::vector<TreeNode*> children(const TreeNode* parentNode, const std::string& tagName) {
    if (!parentNode) { return std::vector<TreeNode*>{}; }
    auto* child_node = parentNode->first_child;
    if ( child_node == nullptr) return std::vector<TreeNode*>{};

    std::vector<TreeNode*> child_nodes;

    if (tagName.empty()) {
        while((child_node)) {
            if (!child_node->data.isEndTag()) {
                child_nodes.push_back(child_node);
            }
            child_node = child_node->next_sibling;
        }
    }
    else {
        while((child_node)) {
            if (!child_node->data.isEndTag() && ba::iequals(child_node->data.tagName(), tagName)) {
                child_nodes.push_back(child_node);
            }
            child_node = child_node->next_sibling;
        }
    }
    return child_nodes;
}



XPath treeNodeToXPath(const TreeNode* treeNode)
{
    XPath xp;
    auto* n = treeNode;
    while (n != nullptr) {
        if (n->data.isTag()) {
            const auto& tagName = n->data.tagName();
            int32_t index = indexOfChildNodeWithTagName(n->parent, n);
            if (index >= 0) {
                xp.emplace_front(tagName, static_cast<int32_t>(index));
            }
        }

        n = n->parent;
    }
    return xp;
}

/// Get index of child node
/// Helper function for treeNodeToXPath()
int32_t indexOfChildNodeWithTagName(const TreeNode* parentNode, const TreeNode* childNode)
{
    if (!parentNode) {
        return -1;
    }
    const auto& tagNameToFind = childNode->data.tagName();
    auto* n = parentNode->first_child;
    int32_t index = -1;
    int32_t indexCounter = 0;
    while (n != nullptr) {
        const auto& tagName = n->data.tagName();
        if (n->data.isEndTag() || !n->data.isTag()) {
            n = n->next_sibling;
            continue;
        }

        if (!tagName.empty() && ba::iequals(tagName,tagNameToFind)) {
            indexCounter++;
        }
        if (n == childNode) {
            index = indexCounter;
        }
        n = n->next_sibling;
    }

    if (indexCounter < 2 && (index > -1)) {
        index = 0;  // If we only have one of the tagName we use index 0 to indicate this. Actually it's index = 1
    }

    return index;
}


const TreeNode* xPathToTreeNode(const TreeNode* rootNode, const XPath& xpath)
{
    if (!rootNode) {
        return nullptr;
    }

    auto it = xpath.begin();
    const auto it_end = xpath.end();

    const auto* node = rootNode;
    while (node && (it != it_end)) {
        auto index = it->index;
        // If we only have one of the tagName we use index 0 to indicate this.
        // So an index of 0 in out XPath class is really index 1
        if (index == 0) index = 1;

        node = childNodeFromIndexWithTagName(node, it->tagName, index);
        ++it;
    }

    return node;
}

const TreeNode* childNodeFromIndexWithTagName(const TreeNode* parentNode, const std::string& tagName, int32_t index)
{
    if (!parentNode) {
        return nullptr;
    }

    auto* n = parentNode->first_child;
    int32_t indexCounter = 0;
    while (n != nullptr) {
        const auto& curTagName = n->data.tagName();
        if (n->data.isEndTag() || !n->data.isTag()) {
            n = n->next_sibling;
            continue;
        }

        if (!curTagName.empty() && ba::iequals(curTagName, tagName)) {
            indexCounter++;
        }

        if (indexCounter == index) {
            return n;
        }
        n = n->next_sibling;
    }

    return nullptr;
}

} // END namespace crawl


/// VIRKER !!
/// Get index of child node
/// Helper function for treeNodeToXPath()
//int32_t indexOfChildNode(const TreeNode* parentNode, const TreeNode* childNode)
//{
//    if (!parentNode) {
//        return -1;
//    }
//    const auto& tagNameToFind = childNode->data.tagName();
//    auto* n = parentNode->first_child;
//    int32_t index = 0;
//    int32_t indexCounter = 0;
//    while (n != nullptr) {
//        const auto& tagName = n->data.tagName();
//        if (n->data.isEndTag() || !n->data.isTag()) {
//            n = n->next_sibling;
//            continue;
//        }

//        if (!tagName.empty() && tagName == tagNameToFind) {
//            indexCounter++;
//        }
//        if (n == childNode) {
//            index = indexCounter;
//        }
//        n = n->next_sibling;
//    }

//    if (indexCounter < 2) {
//        index = 0;
//    }

//    return index;
//}

