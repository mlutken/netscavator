#pragma once

#include <memory>
#include "ParserSax.h"
#include "tree.h"
#include <html/XPath.h>

namespace crawl {
using DomTree   = tree<crawl::Node>;
using TreeNode  = DomTree::tree_node;

class ParserDom : public ParserSax
{
public:
    ParserDom() {}
    ~ParserDom() {}

    std::unique_ptr<DomTree>   parseTree   (std::string_view html);
protected:
    virtual void beginParsing();

    virtual void foundTag(Node node, bool isEnd);
    virtual void foundText(Node node);
    virtual void foundComment(Node node);

    virtual void endParsing();

    std::unique_ptr<DomTree>    m_domTree;
    DomTree::iterator           m_currentState;
};

std::ostream &operator<<(std::ostream &stream, const tree<crawl::Node> &tr);

// ----------------------
// --- Node functions ---
// ----------------------

TreeNode*                       endTagNode                  (const TreeNode* parentNode);
std::vector<TreeNode*>          children                    (const TreeNode* parentNode);
std::vector<TreeNode*>          children                    (const TreeNode* parentNode, const std::string& tagName);

XPath                           treeNodeToXPath             (const TreeNode* treeNode);
int32_t                         indexOfChildNodeWithTagName (const TreeNode* parentNode, const TreeNode* childNode);

const TreeNode*                 xPathToTreeNode             (const TreeNode* rootNode, const XPath& xpath);
const TreeNode*                 childNodeFromIndexWithTagName(const TreeNode* parentNode, const std::string& tagName, int32_t index);

} //namespace crawl

