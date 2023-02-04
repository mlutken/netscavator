#pragma once

#include <DomNodeIF.h>
//FIXME OLD QWebView #include <QWebElement>

class DOMNode;

namespace crawl {

class LinearDomIF;
class WebBrowserIF;


class WebKitDomNodeQt: public DomNodeIF  {
public:

    WebKitDomNodeQt  (
            int32_t iNodeType
            , const QString& value
            , const QString& sElem
            //FIXME OLD QWebView , const QWebElement& nativeElem
            , boost::shared_ptr<WebBrowserIF> pOwnerBrowser
            , int iDepthLevel );
    virtual ~WebKitDomNodeQt() ;

    ////        virtual boost::shared_ptr<DOMNode>          DOMNodePtr() const { return m_pNativeNode; } // TODO: Temporary hack until we have completed the refactoring project

    // -------------------------
    // --- PUBLIC: Functions ---
    // -------------------------
    //        boost::shared_ptr<DOMNode>        nativeNode      () const { return m_pNativeNode; }
    //        void                              nativeNodeSet   ( boost::shared_ptr<DOMNode> pNativeNode ) { m_pNativeNode = pNativeNode; }

    const QString&  elemString() const { return m_sElem; }

private:
    // -------------------------------------
    // --- PRIVATE: Structural functions ---
    // -------------------------------------
    virtual boost::shared_ptr<DomNodeIF>    do_immediateParentNodeNative () const override;
/////    virtual boost::shared_ptr<DomNodeIF>    do_parentNode       ( int iLevelsUp ) const ;
//    virtual bool                            do_hasChildNodes    () const;
//    virtual boost::shared_ptr<BoxObjectIF>  do_getBoxObject     () const;
//    virtual std::vector<boost::shared_ptr<DomNodeIF>> do_childNodesGet() const;
//    virtual boost::shared_ptr<DomNodeIF>    do_firstChild       () const;
//    virtual boost::shared_ptr<DomNodeIF>    do_lastChild        () const;
//    virtual boost::shared_ptr<DomNodeIF>    do_previousSibling  () const;
//    virtual boost::shared_ptr<DomNodeIF>    do_nextSibling      () const;


    // ------------------------------------
    // --- PRIVATE: Attribute functions ---
    // ------------------------------------
//    virtual std::string 	do_attributeGet     ( const std::string& sName ) const;
//    virtual void            do_attributeSet     ( const std::string& sName, const std::string& sValue );
//    virtual void            do_attributesGet    ( AttributesMap& attributes ) const;

    // -------------------------------
    // --- PRIVATE: Info functions ---
    // -------------------------------
//    virtual QString         do_qstringDataGet       () const override;
//    virtual std::string     do_stringDataUTF8Get    () const;
//    virtual std::string     do_nodeNameGet          () const;
//    virtual std::string     do_nodeValueGet         () const;
//    virtual std::string     do_nodeTextGet          () const;
//    virtual std::string     do_nodeTextAllRecurGet  () const;
//    virtual std::string     do_hrefGet              () const;
//    virtual std::string     do_hrefCompleteGet      () const;
    virtual void*           do_nativeNodePtrGet     () const override;
    virtual boost::uint32_t do_nodeTypeGet          () const override;
    crawl::XPath          do_xpathGet             () const override;



    // -----------------------------
    // --- PRIVATE: Node actions ---
    // -----------------------------
    virtual bool            do_click                () const override;
//    virtual bool            do_mouseClick           () const   ;
//    virtual bool            do_mouseEvent           ( const std::string& sEventNames, boost::int32_t iDetail, boost::uint32_t iButton ) const   ;
//    virtual bool            do_inputSet             ( const std::string& sValue ) const;
//    virtual std::string     do_innerHtml            () const;
//    virtual bool            do_innerHtmlSet         ( const std::string& sValue ) const;
//    virtual std::string     do_innerText            () const;
//    virtual bool            do_innerTextSet         ( const std::string& sValue ) const;
//    virtual bool            do_formSubmit           () const        ;
//    virtual bool            do_formReset            () const        ;
//    virtual bool            do_javaScriptEvaluate   ( const std::string& sJavaScript ) const;

    // ------------------------------------
    // --- PRIVATE: Node select actions ---
    // ------------------------------------
//    virtual int                             do_selectLengthGet          () const;
//    virtual int                             do_selectedIndexGet         () const;
//    virtual int                             do_selectedDomPosGet        () const;
//    virtual bool                            do_selectIndex              ( int iIndex ) const;
//    virtual bool                            do_selectOption             () const;
//    virtual std::string                     do_selectValueGet           () const;
//    virtual std::string                     do_selectTextGet            () const;
//    virtual std::string                     do_optionTextGet            () const;
//    virtual boost::shared_ptr<DomNodeIF>    do_selectOptionNodeGet      ( int iIndex ) const;
//    virtual boost::shared_ptr<DomNodeIF>    do_optionOwnerSelectNodeGet () const;

    // ----------------------------------------
    // --- PRIVATE: Action helper functions ---
    // ----------------------------------------
    bool sendMouseEvent (
            std::string const& 			sEventName
            , boost::int32_t 			iDetail
            , boost::uint32_t 			iButton
            ) const;

    // ----------------------------
    // --- PRIVATE: Member data ---
    // ----------------------------
    // TODO: Test if we really need these to be mutable
    mutable boost::uint32_t         m_iNodeType;
    QString                         m_value;
    mutable QString                 m_sElem;        // Helper string. Typically an attribute name, used for ATTRIBUTE and ATTRIBUTE_VALUE
//FIXME OLD QWebView     mutable QWebElement             m_nativeElem;
};

boost::shared_ptr<WebKitDomNodeQt> mkWebKitDomNodeQt(
        int32_t iNodeType
        , const QString& value
        , const QString& sElem
//FIXME OLD QWebView         , const QWebElement& nativeElem
        , boost::shared_ptr<crawl::WebBrowserIF> pOwnerBrowser
        , int iDepthLevel
        );


} // END namespace crawl
