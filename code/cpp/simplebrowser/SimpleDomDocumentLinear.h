#pragma once

#include <string_view>
#include <html/ParserDom.h>

#include <LinearDomIF.h>
#include <WebBrowserIF.h>

class DOMDocument;
class DOMNode;

namespace crawl {
class DomNodeIF;
class WebBrowserIF;
class WordMonitor;

/** Linear representation of a DOM document
@author Martin Lütken */
class SimpleDomDocumentLinear : public LinearDomIF {
public:
    // -------------------------------------------------
    // --- CONSTRUCTOR / INIT and DESTRUCTOR methods ---
    // -------------------------------------------------
    SimpleDomDocumentLinear(boost::shared_ptr<crawl::WebBrowserIF> pBrowser,
                            std::string_view html);
    virtual ~SimpleDomDocumentLinear();

    void createSimpleLinearDom(std::string_view html);

    void wordMonitorSet(WordMonitor *wordMonitor);

private:

    // ---------------------------------
    // --- PRIVATE: Helper functions ---
    // ---------------------------------
    TreeNode*           do_rootNode             ()       override           { return m_domTree->begin().node; }
    const TreeNode*     do_rootNode             () const override           { return m_domTree->begin().node; }
    DomTree*            do_domTree              () const override           { return m_domTree.get(); }

    // ----------------------------
    // --- PRIVATE: Member data ---
    // ----------------------------
    int                                 m_iFrameCounter;
    WordMonitor*                        m_wordMonitor = nullptr;
    std::unique_ptr<DomTree>            m_domTree;
    bool                                m_sortAttributes = false;

};

} // END namespace crawl

