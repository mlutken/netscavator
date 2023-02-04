#pragma once

#include <DomNodeIF.h>


namespace crawl {

class LinearDomIF;
class WebBrowserIF;


class SimpleDomNode: public DomNodeIF  {
public:

    SimpleDomNode  (int32_t iNodeType,
            const std::string& value,
            const AttributesMap& attributes,
            boost::shared_ptr<crawl::WebBrowserIF> pOwnerBrowser,
            int iDepthLevel,
            crawl::TreeNode* treeNode);
    ~SimpleDomNode() override;

    // -------------------------
    // --- PUBLIC: Functions ---
    // -------------------------
private:
    // -------------------------------------
    // --- PRIVATE: Structural functions ---
    // -------------------------------------
    boost::shared_ptr<DomNodeIF>    do_immediateParentNodeNative () const override;
//    bool                            do_hasChildNodes    () const override;
//    boost::shared_ptr<BoxObjectIF>  do_getBoxObject     () const override;
//    std::vector<boost::shared_ptr<DomNodeIF>> do_childNodesGet() const override;
//    boost::shared_ptr<DomNodeIF>    do_firstChild       () const override;
//    boost::shared_ptr<DomNodeIF>    do_lastChild        () const override;
//    boost::shared_ptr<DomNodeIF>    do_previousSibling  () const override;
//    boost::shared_ptr<DomNodeIF>    do_nextSibling      () const override;


    // ------------------------------------
    // --- PRIVATE: Attribute functions ---
    // ------------------------------------
//    std::string 	do_attributeGet     ( const std::string& sName ) const override;
//    void            do_attributeSet     ( const std::string& sName, const std::string& sValue ) override;
//    void            do_attributesGet    ( AttributesMap& attributes ) const override;

    // -------------------------------
    // --- PRIVATE: Info functions ---
    // -------------------------------
    QString         do_qstringDataGet       () const override;
    std::string     do_stringDataUTF8Get    () const override;
//    std::string     do_nodeNameGet          () const override;
//    std::string     do_nodeValueGet         () const override;
//    std::string     do_nodeTextGet          () const override;
//    std::string     do_nodeTextAllRecurGet  () const override;
//    std::string     do_hrefGet              () const override;
//    std::string     do_hrefCompleteGet      () const override;
    void*           do_nativeNodePtrGet     () const override;
    boost::uint32_t do_nodeTypeGet          () const override;
    crawl::XPath    do_xpathGet             () const override;

    // -----------------------------
    // --- PRIVATE: Node actions ---
    // -----------------------------
    bool            do_click                () const override;
//    bool            do_mouseEvent           ( const std::string& sEventNames, boost::int32_t iDetail, boost::uint32_t iButton ) const override;
//    bool            do_inputSet             ( const std::string& sValue ) const override;
//    std::string     do_innerHtml            () const override;
//    bool            do_innerHtmlSet         ( const std::string& sValue ) const override;
//    std::string     do_innerText            () const override;
//    bool            do_innerTextSet         ( const std::string& sValue ) const override;
//    bool            do_formSubmit           () const override;
//    bool            do_formReset            () const override;
//    bool            do_javaScriptEvaluate   ( const std::string& sJavaScript ) const override;

    // ------------------------------------
    // --- PRIVATE: Node select actions ---
    // ------------------------------------
//    int                             do_selectLengthGet          () const override;
//    int                             do_selectedIndexGet         () const override;
//    int                             do_selectedDomPosGet        () const override;
//    bool                            do_selectIndex              (int index) const override;
//    bool                            do_selectOption             () const override;
//    std::string                     do_selectValueGet           () const override;
//    std::string                     do_selectTextGet            () const override;
//    std::string                     do_optionTextGet            () const override;
//    boost::shared_ptr<DomNodeIF>    do_selectOptionNodeGet      (int iIndex) const override;
//    boost::shared_ptr<DomNodeIF>    do_optionOwnerSelectNodeGet () const override;

    // ----------------------------------------
    // --- PRIVATE: Action helper functions ---
    // ----------------------------------------

    // ----------------------------
    // --- PRIVATE: Member data ---
    // ----------------------------
    // TODO: Test if we really need these to be mutable
    mutable int32_t                 m_iNodeType;
    std::string                     m_value;
    AttributesMap                   m_attributes;
    crawl::TreeNode*                m_treeNode;
};

boost::shared_ptr<SimpleDomNode> makeSimpleDomNode(int32_t nodeType,
            const std::string& value,
            const AttributesMap& attributes,
            boost::shared_ptr<crawl::WebBrowserIF> ownerBrowser,
            int depthLevel,
            crawl::TreeNode* treeNode
        );


} // END namespace crawl
