#ifndef _CRAWL_DOM_DOCUMENT_LINEAR_H_
#define _CRAWL_DOM_DOCUMENT_LINEAR_H_


#include <LinearDomIF.h>
#include <WebBrowserIF.h>

class DOMDocument;
class DOMNode;

namespace crawl {
    class DomNodeIF;
    class WebBrowserIF;

    /** Linear representation of a DOM document
@author Martin Lütken */
    class DomDocumentLinear : public LinearDomIF {
    public:

        // -------------------------------------------------
        // --- CONSTRUCTOR / INIT and DESTRUCTOR methods ---
        // -------------------------------------------------
        DomDocumentLinear( boost::shared_ptr<crawl::WebBrowserIF> pBrowser, boost::shared_ptr<DOMDocument> pDOMDoc );
        virtual ~DomDocumentLinear();


    private:
        // ---------------------------------
        // --- PRIVATE: Helper functions ---
        // ---------------------------------
        virtual const_iterator       do_findFromRawPointer ( boost::shared_ptr<DomNodeIF> pDomNode ) const;
        virtual const_iterator       do_findFromRawPointer ( const void* pNativeNode ) const;

        // ----------------------------
        // --- PRIVATE: Member data ---
        // ----------------------------
        boost::shared_ptr<DOMDocument>	m_pDOMDoc;
    };


    // ----------------------
    // --- Free functions ---
    // ----------------------
    void createLinearDomFromNode(
            boost::shared_ptr<WebBrowserIF>     pBrowser
            , boost::shared_ptr<LinearDomIF>    pLinearDom
            , boost::shared_ptr<DOMNode>        pNode
            , bool                              bInsertEndTagNodes
            , bool                              bSkipEmptyNodes
            );


} // END namespace crawl

#endif //_CRAWL_DOM_DOCUMENT_LINEAR_H_
