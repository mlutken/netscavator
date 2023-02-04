#ifndef _MOZ_DOM_NODE_H_
#define _MOZ_DOM_NODE_H_

#include <DomNodeIF.h>

class DOMNode;

namespace crawl {

    class LinearDomIF;
    class WebBrowserIF;


    class MozDomNode: public DomNodeIF  {
    public:

        MozDomNode  ( boost::shared_ptr<DOMNode> pNativeNode, boost::shared_ptr<WebBrowserIF> pOwnerBrowser );
        virtual ~MozDomNode() ;

        virtual boost::shared_ptr<DOMNode>          DOMNodePtr() const { return m_pNativeNode; } // TODO: Temporary hack until we have completed the refactoring project

        // -------------------------
        // --- PUBLIC: Functions ---
        // -------------------------
        boost::shared_ptr<DOMNode>        nativeNode      () const { return m_pNativeNode; }
        void                              nativeNodeSet   ( boost::shared_ptr<DOMNode> pNativeNode ) { m_pNativeNode = pNativeNode; }

    private:
        // -------------------------------------
        // --- PRIVATE: Structural functions ---
        // -------------------------------------
        virtual boost::shared_ptr<DomNodeIF>    do_parentNode       ( int iLevelsUp ) const ;
        virtual bool                            do_hasChildNodes    () const;
        virtual boost::shared_ptr<BoxObjectIF>  do_getBoxObject     () const;
        virtual void                            do_childNodesGet    ( std::vector<boost::shared_ptr<DomNodeIF> >& nodes ) const;
        virtual boost::shared_ptr<DomNodeIF>    do_firstChild       () const;
        virtual boost::shared_ptr<DomNodeIF>    do_lastChild        () const;
        virtual boost::shared_ptr<DomNodeIF>    do_previousSibling  () const;
        virtual boost::shared_ptr<DomNodeIF>    do_nextSibling      () const;


        // ------------------------------------
        // --- PRIVATE: Attribute functions ---
        // ------------------------------------
        virtual std::string 	do_attributeGet     ( const std::string& sName ) const;
        virtual void            do_attributeSet     ( const std::string& sName, const std::string& sValue );
        virtual void            do_attributesGet    ( AttributesMap& attributes ) const;

        // -------------------------------
        // --- PRIVATE: Info functions ---
        // -------------------------------
        virtual std::string     do_stringDataUTF8Get    () const;
        virtual std::string     do_nodeNameGet          () const;
        virtual std::string     do_nodeValueGet         () const;
        virtual std::string     do_nodeTextGet          () const;
        virtual std::string     do_hrefGet              () const;
        virtual std::string     do_hrefCompleteGet      () const;
        virtual void*           do_nativeNodePtrGet     () const;
        virtual boost::uint32_t do_nodeTypeGet          () const;



        // -----------------------------
        // --- PRIVATE: Node actions ---
        // -----------------------------
        virtual bool            do_click                () const   ;
        virtual bool            do_mouseEvent           ( const std::string& sEventNames, boost::int32_t iDetail, boost::uint32_t iButton ) const   ;
        virtual bool            do_inputSet             ( const std::string& sValue ) const   ;
        virtual bool            do_formSubmit           () const        ;
        virtual bool            do_formReset            () const        ;

        // ------------------------------------
        // --- PRIVATE: Node select actions ---
        // ------------------------------------
        virtual int                             do_selectLengthGet          () const;
        virtual int                             do_selectedIndexGet         () const;
        virtual int                             do_selectedDomPosGet        () const;
        virtual bool                            do_selectIndex              ( int iIndex ) const;
        virtual bool                            do_selectOption             () const;
        virtual std::string                     do_selectValueGet           () const;
        virtual std::string                     do_selectTextGet            () const;
        virtual std::string                     do_optionTextGet            () const;
        virtual boost::shared_ptr<DomNodeIF>    do_selectOptionNodeGet      ( int iIndex ) const;
        virtual boost::shared_ptr<DomNodeIF>    do_optionOwnerSelectNodeGet () const;


        // ----------------------------
        // --- PRIVATE: Member data ---
        // ----------------------------
        mutable boost::shared_ptr<DOMNode>  m_pNativeNode;
        mutable boost::uint32_t             m_iNodeType;

    };

    boost::shared_ptr<MozDomNode> mkMozDomNode( boost::shared_ptr<DOMNode> pNativeNode, boost::shared_ptr<crawl::WebBrowserIF> pOwnerBrowser );


} // END namespace crawl


#endif /* _MOZ_DOM_NODE_H_ */
