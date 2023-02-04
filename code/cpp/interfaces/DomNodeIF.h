#pragma once

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/cstdint.hpp>
#include <QString>
#include <interfaces_types.h>
#include <htmlparser/html/XPath.h>
#include <htmlparser/html/ParserDom.h>

namespace crawl {

    class LinearDomIF;
    class WebBrowserIF;
    class BoxObjectIF;


    struct DomNodeTypes {
        using node_type_type = int32_t; // TODO: use this type in below constants!
        // --------------------------------
        // --- PUBLIC: Types, Constants ---
        // --------------------------------
        //TODO: This is a signess mess !!! Also look at operator precedence
        static const uint32_t NODE_TYPES_OFFSET     = 16U;
        static const int32_t ELEMENT                = 1 << (0U + NODE_TYPES_OFFSET);
        static const int32_t ATTRIBUTE              = 1 << (1U + NODE_TYPES_OFFSET);
        static const int32_t TEXT                   = 1 << (2U + NODE_TYPES_OFFSET);
        static const int32_t CDATA_SECTION          = 1 << (3U + NODE_TYPES_OFFSET);
        static const int32_t ENTITY_REFERENCE       = 1 << (4U + NODE_TYPES_OFFSET);
        static const int32_t ENTITY                 = 1 << (5U + NODE_TYPES_OFFSET);
        static const int32_t PROCESSING_INSTRUCTION = 1 << (6U + NODE_TYPES_OFFSET);
        static const int32_t COMMENT                = 1 << (7U + NODE_TYPES_OFFSET);
        static const int32_t DOCUMENT               = 1 << (8U + NODE_TYPES_OFFSET);
        static const int32_t DOCUMENT_TYPE          = 1 << (9U + NODE_TYPES_OFFSET);
        static const int32_t DOCUMENT_FRAGMENT 		= 1 << (10U + NODE_TYPES_OFFSET);
        static const int32_t NOTATION               = 1 << (11U + NODE_TYPES_OFFSET);
        // Not in Mozilla/W3C original
        static const int32_t ATTRIBUTE_VALUE        = 1 << (12U + NODE_TYPES_OFFSET);
        static const int32_t ELEMENT_END_TAG        = 1 << (13U + NODE_TYPES_OFFSET);
        static const int32_t ATTRIBUTE_NODES        = ATTRIBUTE | ATTRIBUTE_VALUE;    // We reserve the two lowest bytes for post steps
        static const int32_t ELEMENT_TEXT           = ELEMENT | TEXT;    // We reserve the two lowest bytes for post steps
        static const int32_t ELEMENT_NODES          = ELEMENT | ELEMENT_END_TAG;    // We reserve the two lowest bytes for post steps
        static const int32_t ALL_NODE_TYPES         = static_cast<int32_t>(0xFFFF0000);    // We reserve the two lowest bytes for post steps
        static const int32_t REMOVE_NODE_TYPES      = 0x0000FFFF;    // We reserve the two lowest bytes for post steps
    };

    class DomNodeIF : public boost::enable_shared_from_this<DomNodeIF>  {
    public:

//        using node_type_type = int32_t; // TODO: use this type in below constants!
//        // --------------------------------
//        // --- PUBLIC: Types, Constants ---
//        // --------------------------------
//        //TODO: This is a signess mess !!! Also look at operator precedence
//        static const uint32_t NODE_TYPES_OFFSET     = 16U;
//        static const int32_t ELEMENT                = 1 << (0U + NODE_TYPES_OFFSET);
//        static const int32_t ATTRIBUTE              = 1 << (1U + NODE_TYPES_OFFSET);
//        static const int32_t TEXT                   = 1 << (2U + NODE_TYPES_OFFSET);
//        static const int32_t CDATA_SECTION          = 1 << (3U + NODE_TYPES_OFFSET);
//        static const int32_t ENTITY_REFERENCE       = 1 << (4U + NODE_TYPES_OFFSET);
//        static const int32_t ENTITY                 = 1 << (5U + NODE_TYPES_OFFSET);
//        static const int32_t PROCESSING_INSTRUCTION = 1 << (6U + NODE_TYPES_OFFSET);
//        static const int32_t COMMENT                = 1 << (7U + NODE_TYPES_OFFSET);
//        static const int32_t DOCUMENT               = 1 << (8U + NODE_TYPES_OFFSET);
//        static const int32_t DOCUMENT_TYPE          = 1 << (9U + NODE_TYPES_OFFSET);
//        static const int32_t DOCUMENT_FRAGMENT 		= 1 << (10U + NODE_TYPES_OFFSET);
//        static const int32_t NOTATION               = 1 << (11U + NODE_TYPES_OFFSET);
//        // Not in Mozilla/W3C original
//        static const int32_t ATTRIBUTE_VALUE        = 1 << (12U + NODE_TYPES_OFFSET);
//        static const int32_t ELEMENT_END_TAG        = 1 << (13U + NODE_TYPES_OFFSET);
//        static const int32_t ATTRIBUTE_NODES        = ATTRIBUTE | ATTRIBUTE_VALUE;    // We reserve the two lowest bytes for post steps
//        static const int32_t ELEMENT_TEXT           = ELEMENT | TEXT;    // We reserve the two lowest bytes for post steps
//        static const int32_t ELEMENT_NODES          = ELEMENT | ELEMENT_END_TAG;    // We reserve the two lowest bytes for post steps
//        static const int32_t ALL_NODE_TYPES         = static_cast<int32_t>(0xFFFF0000);    // We reserve the two lowest bytes for post steps
//        static const int32_t REMOVE_NODE_TYPES      = 0x0000FFFF;    // We reserve the two lowest bytes for post steps

        // -----------------------------------------------
        // --- PUBLIC: Constructors, Init, Destructors ---
        // -----------------------------------------------
        explicit DomNodeIF( boost::shared_ptr<WebBrowserIF> pOwnerBrowser )
            : m_pOwnerBrowser(pOwnerBrowser)
            , m_iDepthLevel(-1)
        {}

        DomNodeIF( boost::shared_ptr<WebBrowserIF> pOwnerBrowser, int iDepthLevel )
            : m_pOwnerBrowser(pOwnerBrowser)
            , m_iDepthLevel(iDepthLevel)
        {}
        virtual ~DomNodeIF() {}


        // ------------------------------------
        // --- PUBLIC: Structural functions ---
        // ------------------------------------
        boost::shared_ptr<LinearDomIF>      ownerLinearDom      () const;
//        void                                ownerLinearDomSet   ( boost::shared_ptr<LinearDomIF> pOwner ) { m_pOwnerLinearDom = pOwner; }

        boost::shared_ptr<WebBrowserIF>     ownerBrowser        () const { return m_pOwnerBrowser; }

        boost::shared_ptr<DomNodeIF>        parentNode          ( int iLevelsUp ) const;
//        bool                                hasChildNodes       () const { return do_hasChildNodes(); }
//        boost::shared_ptr<BoxObjectIF>      getBoxObject        () const { return do_getBoxObject(); }

//        std::vector<boost::shared_ptr<DomNodeIF>> childNodes    () const { return do_childNodesGet();}
//        boost::shared_ptr<DomNodeIF>        firstChild          () const { return do_firstChild(); }
//        boost::shared_ptr<DomNodeIF>        lastChild           () const { return do_lastChild(); }
//        boost::shared_ptr<DomNodeIF>        previousSibling     () const { return do_previousSibling(); }
//        boost::shared_ptr<DomNodeIF>        nextSibling         () const { return do_nextSibling(); }
//        void                                attributesGet       ( AttributesMap& attributes ) const { do_attributesGet(attributes);}



////        virtual boost::shared_ptr<DOMNode>  DOMNodePtr() const { return boost::shared_ptr<DOMNode>(); } // TODO: Temporary hack until we have completed the refactoring project
        // -----------------------------------
        // --- PUBLIC: Attribute functions ---
        // -----------------------------------
//        std::string 	attributeGet        ( const std::string& sName ) const { return do_attributeGet(sName); }
//        void            attributeSet        ( const std::string& sName, const std::string& sValue ) { return do_attributeSet(sName, sValue); }
//        std::string     classGet            () const;
//        void            classSet            ( const std::string& sClassName );
//        void            classAdd            ( const std::string& sClassName );
//        void            classRemove         ( const std::string& sClassName );
        int             depthLevelGet       () const { return m_iDepthLevel; }

        // ------------------------------
        // --- PUBLIC: Info functions ---
        // ------------------------------
        QString         qstringDataGet      () const    { return do_qstringDataGet();       }
        std::string     stringDataUTF8      () const;
//        std::string     nodeName            () const    { return do_nodeNameGet();          }
//        std::string     nodeValue           () const    { return do_nodeValueGet();         }
//        std::string     nodeText            () const    { return do_nodeTextGet();          }
//        std::string     nodeTextAllRecur    () const    { return do_nodeTextAllRecurGet();  }
//        std::string     href                () const    { return do_hrefGet();              }
//        std::string     hrefComplete        () const    { return do_hrefCompleteGet();      }
        void*           nativeNodePtr       () const    { return do_nativeNodePtrGet();     }
        boost::uint32_t nodeType            () const    { return do_nodeTypeGet();          }
        crawl::XPath    xpath               () const    { return do_xpathGet();             }


        // -----------------------------
        // --- PUBLIC: Node actions ---
        // -----------------------------
        bool            click               () const                            { return do_click(); }
//        bool            mouseEvent          ( const std::string& sEventNames, boost::int32_t iDetail, boost::uint32_t iButton ) const;
//        bool            inputSet            ( const std::string& sValue ) const;
//        std::string     innerHtml           () const;
//        bool            innerHtmlSet 		( const std::string& sValue ) const;
//        std::string     innerText           () const;
//        bool            innerTextSet 		( const std::string& sValue ) const;
//        bool            formSubmit          () const                            { return do_formSubmit(); }
//        bool            formReset           () const                            { return do_formReset(); }
//        bool            javaScriptEvaluate  ( const std::string& sJavaScript ) const  { return do_javaScriptEvaluate(sJavaScript); }

        // -----------------------------------
        // --- PUBLIC: Node select actions ---
        // -----------------------------------
//        int                                 selectLengthGet         () const                { return do_selectLengthGet();  }
//        int                                 selectedIndexGet        () const                { return do_selectedIndexGet(); }
//        int                                 selectedDomPosGet       () const                { return do_selectedDomPosGet();}
//        bool                                selectIndex             ( int iIndex ) const    { return do_selectIndex(iIndex);}
//        bool                                selectOption            () const                { return do_selectOption();     }
//        std::string                         selectValueGet          () const                { return do_selectValueGet();   }
//        std::string                         selectTextGet           () const                { return do_selectTextGet();    }
//        std::string                         optionTextGet           () const                { return do_optionTextGet();    }
//        boost::shared_ptr<DomNodeIF>        selectOptionNodeGet     ( int iIndex ) const    { return do_selectOptionNodeGet( iIndex );    }
//        boost::shared_ptr<DomNodeIF>        optionOwnerSelectNodeGet() const                { return do_optionOwnerSelectNodeGet(); }

        // --- Immediate parent node helper functions ---
        void immediateParentNodeSet(const boost::shared_ptr<DomNodeIF> &parentNode) { m_immediateParentNode = parentNode; }
        boost::shared_ptr<DomNodeIF> immediateParentNode() const;

        void setStringDataUTF8Cached(const std::string& stringDataUTF8Cached);

        const std::string& getStringDataUTF8Cached() const { return m_stringDataUTF8Cached; }

    private:


    private:
        // -------------------------------------
        // --- PRIVATE: Structural functions ---
        // -------------------------------------
        virtual boost::shared_ptr<DomNodeIF>    do_immediateParentNodeNative () const = 0;
////        virtual boost::shared_ptr<DomNodeIF>    do_parentNode       ( int /*iLevelsUp*/ ) const { return boost::shared_ptr<DomNodeIF>(); }
//        virtual bool                            do_hasChildNodes    () const = 0;
//        virtual boost::shared_ptr<BoxObjectIF>  do_getBoxObject     () const = 0;
//        virtual std::vector<boost::shared_ptr<DomNodeIF>>   do_childNodesGet () const = 0;
//        virtual boost::shared_ptr<DomNodeIF>    do_firstChild       () const = 0;
//        virtual boost::shared_ptr<DomNodeIF>    do_lastChild        () const = 0;
//        virtual boost::shared_ptr<DomNodeIF>    do_previousSibling  () const = 0;
//        virtual boost::shared_ptr<DomNodeIF>    do_nextSibling      () const = 0;

        // ------------------------------------
        // --- PRIVATE: Attribute functions ---
        // ------------------------------------
//        virtual std::string 	do_attributeGet     ( const std::string& sName ) const = 0;
//        virtual void            do_attributeSet     ( const std::string& sName, const std::string& sValue ) = 0;
//        virtual void            do_attributesGet    ( AttributesMap& attributes ) const = 0;


        // -------------------------------
        // --- PRIVATE: Info functions ---
        // -------------------------------
        virtual QString         do_qstringDataGet       () const   = 0;
        virtual std::string     do_stringDataUTF8Get    () const   = 0;
//        virtual std::string     do_nodeNameGet          () const   = 0;
//        virtual std::string     do_nodeValueGet         () const   = 0;
//        virtual std::string     do_nodeTextGet          () const   = 0;
//        virtual std::string     do_nodeTextAllRecurGet  () const   = 0;
//        virtual std::string     do_hrefGet              () const   = 0;
//        virtual std::string     do_hrefCompleteGet      () const   = 0;

        virtual void*           do_nativeNodePtrGet     () const   = 0;
        virtual boost::uint32_t do_nodeTypeGet          () const   = 0;
        virtual crawl::XPath    do_xpathGet             () const   = 0;


        // -----------------------------
        // --- PRIVATE: Node actions ---
        // -----------------------------
        virtual bool            do_click                () const = 0;
//        virtual bool            do_mouseEvent           ( const std::string& sEventNames, boost::int32_t iDetail, boost::uint32_t iButton ) const = 0;
//        virtual bool            do_inputSet             ( const std::string& sValue ) const = 0;
//        virtual std::string     do_innerHtml            () const = 0;
//        virtual bool            do_innerHtmlSet         ( const std::string& sValue ) const = 0;
//        virtual std::string     do_innerText            () const = 0;
//        virtual bool            do_innerTextSet         ( const std::string& sValue ) const = 0;
//        virtual bool            do_formSubmit           () const = 0;
//        virtual bool            do_formReset            () const = 0;
//        virtual bool            do_javaScriptEvaluate   ( const std::string& sJavaScript ) const = 0;

        // ------------------------------------
        // --- PRIVATE: Node select actions ---
        // ------------------------------------
//        virtual int                             do_selectLengthGet          () const = 0;
//        virtual int                             do_selectedIndexGet         () const = 0;
//        virtual int                             do_selectedDomPosGet        () const = 0;
//        virtual bool                            do_selectIndex              ( int iIndex ) const = 0;
//        virtual bool                            do_selectOption             () const = 0;
//        virtual std::string                     do_selectValueGet           () const = 0;
//        virtual std::string                     do_selectTextGet            () const = 0;
//        virtual std::string                     do_optionTextGet            () const = 0;
//        virtual boost::shared_ptr<DomNodeIF>    do_selectOptionNodeGet      ( int iIndex ) const = 0;
//        virtual boost::shared_ptr<DomNodeIF>    do_optionOwnerSelectNodeGet () const = 0;


        // ----------------------------
        // --- PRIVATE: Member data ---
        // ----------------------------
        boost::shared_ptr<WebBrowserIF>         m_pOwnerBrowser;
        boost::shared_ptr<LinearDomIF>          m_pOwnerLinearDom;
        int                                     m_iDepthLevel;
        mutable std::string                     m_stringDataUTF8Cached;
        mutable boost::shared_ptr<DomNodeIF>    m_immediateParentNode;
    };

} // END namespace crawl
