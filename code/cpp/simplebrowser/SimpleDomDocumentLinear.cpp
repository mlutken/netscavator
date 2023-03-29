#include "SimpleDomDocumentLinear.h"

#include <cstdio>
#include <iostream>
#include <utility>
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>
#include <utils/cpaf_json_utils.h>

#include <utils/utils.h>
#include <utils/string_algorithms.h>
#include <interfaces_utils.h>
#include <SimpleDomNode.h>
#include <containers/WordMonitor.h>
#include <htmlparser/html/ParserDom.h>
#include <interfaces/Configuration.h>

// -----------------------
// --- HTML char codes ---
// -----------------------
// https://www.ascii.cl/htmlcodes.htm
// https://www.freeformatter.com/html-entities.html
// https://www.w3.org/wiki/Common_HTML_entities_used_for_typography
// :		&#58; (&#3A;)	Colon
// /		&#47; (&#2F;)	Slash
// ?		&#63; (&#3F;)	Question mark
using namespace std;

namespace crawl {

    void parseJsonRecursive(TreeNode* parentTreeNode, const nlohmann::json& object, SimpleDomDocumentLinear* simple_dom,
                            boost::shared_ptr<WebBrowserIF> browser,
                            int depth, int parentPos)
    {
        if (object.is_object()){
            for (auto& item : object.items()) {
                constexpr auto nodetype = DomNodeTypes::ATTRIBUTE;
                auto domNode = makeSimpleDomNode(nodetype, item.key(), AttributesMap{}, browser, depth, parentTreeNode);
                simple_dom->pushBackNode (LinearDomNode(parentTreeNode, domNode, domNode->stringDataUTF8(), parentPos, depth, nodetype));
                parseJsonRecursive(parentTreeNode, item.value(), simple_dom, browser, depth +1, parentPos);
            }
        }
        else if (object.is_array()){
            for (auto& item : object.items()) {
                parseJsonRecursive(parentTreeNode, item.value(), simple_dom, browser, depth +1, parentPos);
            }
        }
        else {
            constexpr auto nodetype = DomNodeTypes::ATTRIBUTE_VALUE;
            const std::string val = cpaf::simple_json_to_string(object);
            auto domNode = makeSimpleDomNode(nodetype, val, AttributesMap{}, browser, depth, parentTreeNode);
            simple_dom->pushBackNode (LinearDomNode(parentTreeNode, domNode, domNode->stringDataUTF8(), parentPos, depth, nodetype));
        }
    }

    // -------------------------------------------------
    // --- CONSTRUCTOR / INIT and DESTRUCTOR methods ---
    // -------------------------------------------------

    SimpleDomDocumentLinear::SimpleDomDocumentLinear (boost::shared_ptr<crawl::WebBrowserIF> pBrowser
            , string_view html)
        : LinearDomIF(pBrowser)
    {
        m_sortAttributes = pBrowser->configuration()->valueBoolGet("sort_attributes");
        createSimpleLinearDom(html);
    }

    SimpleDomDocumentLinear::~SimpleDomDocumentLinear() = default;

    void SimpleDomDocumentLinear::createSimpleLinearDom(string_view html)
    {
        crawl::ParserDom parser;
        m_domTree = std::move(parser.parseTree(html));

        DomTree::pre_order_iterator it = m_domTree->begin();
        DomTree::pre_order_iterator end = m_domTree->end();

        int parentPos = LinearDomNode::no_owner_pos;

        unsigned int index = 0;
        while ( it != end )
        {
            crawl::Node& htmlNode = *it;
            TreeNode* treeNode = it.node;
            if (it.node && it.node->parent) {
                parentPos = it.node->parent->data.linearDomPos();
            }

            const int curDepth = m_domTree->depth(it);
            // //for(int i=0; i < curDepth - rootdepth; ++i) cerr << "  ";

            boost::shared_ptr<SimpleDomNode> domNode;
            auto nodetype = DomNodeTypes::ELEMENT;
            std::string value;
            if (htmlNode.isTag()) {
                nodetype = DomNodeTypes::ELEMENT;
                value = boost::to_upper_copy(htmlNode.tagName());
                if (htmlNode.isEndTag()) {
                    nodetype = DomNodeTypes::ELEMENT_END_TAG;
                    value = "/"s + value;
                }
            }
            else if (!htmlNode.isComment() && !htmlNode.text().empty()) {
                nodetype = DomNodeTypes::TEXT;
                value = boost::algorithm::trim_copy(htmlNode.text());
            }
            boost::algorithm::trim(value);

            if (!value.empty()) {
                bool add_single_normal_node = true;
                if ( boost::algorithm::starts_with(value, "{") || boost::algorithm::starts_with(value, "[")) {
                    add_single_normal_node = false;
                    try {
                        const auto trimmed = boost::algorithm::replace_all_copy( value, std::string("\n"), std::string(" ") );
                        auto json_object = cpaf::parse_non_strict(trimmed);
                        parseJsonRecursive(treeNode, json_object, this, browser(), curDepth, parentPos);

                    } catch (std::exception e) {
                        add_single_normal_node = true;
                    }
                }

                if (add_single_normal_node) {
                    domNode = makeSimpleDomNode(nodetype, value, AttributesMap{}, browser(), curDepth, treeNode);
                    pushBackNode (LinearDomNode(treeNode, domNode, domNode->stringDataUTF8(), parentPos, curDepth, nodetype));
                    htmlNode.linearDomPosSet(lastDomPos());
                }
            }
            htmlNode.parseAttributes();
            if (m_sortAttributes) {
                htmlNode.sortAttributes();
            }
            for (const auto& [name, value] : htmlNode.attributes()) {
                if (!name.empty()) {
                    auto attrNode = makeSimpleDomNode(DomNodeTypes::ATTRIBUTE, name, AttributesMap{}, browser(), curDepth, treeNode);
                    pushBackNode (LinearDomNode(treeNode, attrNode, attrNode->stringDataUTF8(), parentPos, curDepth, DomNodeTypes::ATTRIBUTE));
                }
                if (!value.empty()) {
                    auto attrValue = makeSimpleDomNode(DomNodeTypes::ATTRIBUTE_VALUE, value, AttributesMap{}, browser(), curDepth, treeNode);
                    pushBackNode (LinearDomNode(treeNode, attrValue, attrValue->stringDataUTF8(), parentPos, curDepth, DomNodeTypes::ATTRIBUTE_VALUE));
                }
            }

// With trimming, which is most likely not needed!!!
//            for (const auto& [name, value] : htmlNode.attributes()) {
//                auto name1 = boost::algorithm::trim_copy(name);
//                auto value1 = boost::algorithm::trim_copy(value);
//                if (!name1.empty()) {
//                    auto attrNode = makeSimpleDomNode(DomNodeTypes::ATTRIBUTE, name1, AttributesMap{}, browser(), curDepth, treeNode);
//                    pushBackNode (LinearDomNode(treeNode, attrNode, attrNode->stringDataUTF8(), parentPos, curDepth, DomNodeTypes::ATTRIBUTE));
//                }
//                if (!value1.empty()) {
//                    auto attrValue = makeSimpleDomNode(DomNodeTypes::ATTRIBUTE_VALUE, value1, AttributesMap{}, browser(), curDepth, treeNode);
//                    pushBackNode (LinearDomNode(treeNode, attrValue, attrValue->stringDataUTF8(), parentPos, curDepth, DomNodeTypes::ATTRIBUTE_VALUE));
//                }
//            }

            ++it;
            ++index;
        }

        // Insert a special last/end dom node!
        const int parentPosOfLast = LinearDomNode::no_owner_pos;
        const std::string lastNodeValue = "__END_OF_NETSCAVATOR_DOM__";
        auto specialLastDomNode = makeSimpleDomNode(DomNodeTypes::NOTATION, lastNodeValue, AttributesMap{}, browser(), 0, nullptr);
        pushBackNode (LinearDomNode(nullptr, specialLastDomNode, lastNodeValue, parentPosOfLast, 0, DomNodeTypes::NOTATION));

//        //Print whole DOM tree
//        cout << dom << endl;
//        //Dump all links in the tree
//        tree<crawl::Node>::iterator it = dom.begin();
//        tree<crawl::Node>::iterator end = dom.end();
//        for (; it != end; ++it)
//        {
//           if (strcasecmp(it->tagName().c_str(), "A") == 0)
//           {
//             it->parseAttributes();
//             cout << it->attribute("href").second << endl;
//             for (const auto& pair :  it->attributes()) {
//                 cout << pair.first << "='" << pair.second << "'";
//             }
//             cout << endl;
//           }
//        }

    }

    // -----------------------------------------
    // --- PRIVATE: Implementation functions ---
    // -----------------------------------------

    void SimpleDomDocumentLinear::wordMonitorSet(WordMonitor *wordMonitor)
    {
        m_wordMonitor = wordMonitor;
    }
} // END namespace crawl

