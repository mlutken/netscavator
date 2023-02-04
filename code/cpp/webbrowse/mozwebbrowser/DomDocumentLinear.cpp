#include "DomDocumentLinear.h"

#include <iostream>
#include <boost/format.hpp> 
#include <boost/algorithm/string.hpp>
#include <interfaces_utils.h>
#include <mozwebbrowser/MozDomNode.h>
#include <dom/DOMDocument.h>

// TODO: Moxzilla cleanup not completed here!

#include <nsCoord.h>
#include <nsIDOMDocument.h>
//#include <nsIFrameSetElement.h>
#include <nsIDOMWindow.h>
#include <nsIDOMHTMLFrameElement.h>
#include <nsIDOMHTMLIFrameElement.h>

#include <dom/DOMNodeEndTag.h>


namespace crawl {


    // -------------------------------------------------
    // --- CONSTRUCTOR / INIT and DESTRUCTOR methods ---
    // -------------------------------------------------

    DomDocumentLinear::DomDocumentLinear (
            boost::shared_ptr<crawl::WebBrowserIF> pBrowser
            , boost::shared_ptr<DOMDocument> pDOMDoc
            )
                : LinearDomIF(pBrowser)
                , m_pDOMDoc				( pDOMDoc )
    {
    }



    DomDocumentLinear::~DomDocumentLinear()
    {
    }



    // ---------------------------------
    // --- PRIVATE: Helper functions ---
    // ---------------------------------

    LinearDomIF::const_iterator DomDocumentLinear::do_findFromRawPointer ( boost::shared_ptr<DomNodeIF> pDomNode ) const
    {
        return do_findFromRawPointer(pDomNode->nativeNodePtr());
    }

    LinearDomIF::const_iterator DomDocumentLinear::do_findFromRawPointer (const void* pNativeNode ) const
    {
        DomDocumentLinear::const_iterator itEND = end();
        for ( DomDocumentLinear::const_iterator it = begin(); it != itEND; ++it	) {
            if ( pNativeNode == it->node->DOMNodePtr()->ifMoz() )	{
                return it;
            }
        }
        return itEND;

    }




    // ----------------------
    // --- Free functions ---
    // ----------------------


    /** Continue recursing the DOM tree from this node ? We do not want to
    recurse "all the way to the bottom" for all nodes. For example for
    attribute nodes we stop at the attribute node and do not continue to split
    up these nodes into two additional nodes.
    \return True if recursing should continue from this node. */
    bool
            recurseThisNode	(
                    boost::shared_ptr<DOMNode>     pNode              ///<	DOMNode (pointer) to test.
                    )
    {
        return 	!( 	pNode->nodeType() 	== DOMNode::ATTRIBUTE ||
                    pNode->nodeType() 	== DOMNode::TEXT 			);
    }



    void recurseCreateLinearDom(
            boost::shared_ptr<WebBrowserIF>     pBrowser
            , boost::shared_ptr<LinearDomIF>    pLinearDom          ///< LinearDom document to add nodes to/build
            , boost::shared_ptr<DOMNode>        pNode               ///< DOMNode (pointer) to recurse from.
            , bool                              bInsertEndTagNodes  ///< Should we insert endtag nodes (normally true)
            , bool                              bSkipEmptyNodes     ///< Should we skip empty nodes (normally true)
            )
    {
        if ( bSkipEmptyNodes ) {
            std::string sVal = pNode->stringData(true);
            if ( !sVal.empty() ) {
                pLinearDom->pushBackNode ( LinearDomNode( mkMozDomNode(pNode, pBrowser) ) );
            }
        }
        else {
            pLinearDom->pushBackNode ( LinearDomNode( mkMozDomNode(pNode, pBrowser) ) );
        }

        // For attribute nodes we add the value as our own special type ATTRIBUTE_VALUE
        // Also we do not continue recursing (see recurseThisNode() function )
        if ( (pNode->nodeType() == DOMNode::ATTRIBUTE) && pNode->hasChildNodes()	) {
            DOMNode::Ptr pChildNode = pNode->firstChild();
            pChildNode->forceNodeType ( DOMNode::ATTRIBUTE_VALUE ) ;
            pLinearDom->pushBackNode ( LinearDomNode( mkMozDomNode(pChildNode, pBrowser) ) );
        }

        if ( !recurseThisNode(pNode ))	return ;
        if ( pNode->hasAttributes() ) {
            DOMNamedNodeMap::Ptr 			pNodes 	= pNode->attributes();
            DOMNamedNodeMap::iterator 		pIt;

            // For some reason the DOMNamedNodeMap seems to order the attributes in reverse!
            for ( pIt = pNodes->end(); pIt > pNodes->begin();  ) {
                --pIt;
                recurseCreateLinearDom (pBrowser, pLinearDom, *pIt, bInsertEndTagNodes, bSkipEmptyNodes );
            }
        }
        if ( pNode->hasChildNodes() ) {
            DOMNodeList::Ptr 			pNodes 	= pNode->childNodes();
            DOMNodeList::iterator 		pIt;
            // 		printf("hasChildNodes: '%s'\n", pNode->stringData().c_str() );

            for ( pIt = pNodes->begin(); pIt != pNodes->end(); ++pIt ) {
                recurseCreateLinearDom (pBrowser, pLinearDom, *pIt, bInsertEndTagNodes, bSkipEmptyNodes );
            }
            if ( bInsertEndTagNodes ) {
                DOMNodeEndTag::Ptr pDOMNodeEndTag = DOMNodeEndTag::Ptr( new DOMNodeEndTag( "/" + pNode->stringData(true) ) );
                pLinearDom->pushBackNode (  LinearDomNode( mkMozDomNode(pDOMNodeEndTag, pBrowser)) );
            }
        }

        // -------------------------
        //--- Frames and iframes ---
        // -------------------------

        if ( pNode->nodeName() == "FRAME" ) {

            nsCOMPtr<nsIDOMHTMLFrameElement> piFrame;
            piFrame = do_QueryInterface( pNode->ifMoz() );
            if ( piFrame ) {
                nsCOMPtr<nsIDOMDocument> pIDOMDocument;
                piFrame->GetContentDocument( getter_AddRefs(pIDOMDocument) );
                boost::shared_ptr<DOMDocument> pDOMDocument (new DOMDocument(pIDOMDocument) );
                recurseCreateLinearDom(pBrowser, pLinearDom, pDOMDocument, bInsertEndTagNodes, bSkipEmptyNodes );
            }
            if ( bInsertEndTagNodes ) {
                DOMNodeEndTag::Ptr pDOMNodeEndTag = DOMNodeEndTag::Ptr( new DOMNodeEndTag( "/" + pNode->stringData(true) ) );
                pLinearDom->pushBackNode (  LinearDomNode( mkMozDomNode(pDOMNodeEndTag, pBrowser)) );
            }
        }
        else if ( pNode->nodeName() == "IFRAME" ) {
            nsCOMPtr<nsIDOMHTMLIFrameElement> piFrame;
            piFrame = do_QueryInterface( pNode->ifMoz() );
            if ( piFrame ) {
                nsCOMPtr<nsIDOMDocument> pIDOMDocument;
                piFrame->GetContentDocument( getter_AddRefs(pIDOMDocument) );
                boost::shared_ptr<DOMDocument> pDOMDocument (new DOMDocument(pIDOMDocument) );
                recurseCreateLinearDom(pBrowser, pLinearDom, pDOMDocument, bInsertEndTagNodes, bSkipEmptyNodes );
            }
            if ( bInsertEndTagNodes ) {
                DOMNodeEndTag::Ptr pDOMNodeEndTag = DOMNodeEndTag::Ptr( new DOMNodeEndTag( "/" + pNode->stringData(true) ) );
                pLinearDom->pushBackNode (  LinearDomNode( mkMozDomNode(pDOMNodeEndTag, pBrowser)) );
            }
        }
    }


    void createLinearDomFromNode(
            boost::shared_ptr<WebBrowserIF>     pBrowser
            , boost::shared_ptr<LinearDomIF>    pLinearDom          ///< LinearDom document to add nodes to/build
            , boost::shared_ptr<DOMNode>        pNode               ///< DOMNode (pointer) to recurse from.
            , bool                              bInsertEndTagNodes  ///< Should we insert endtag nodes (normally true)
            , bool                              bSkipEmptyNodes     ///< Should we skip empty nodes (normally true)
            )
    {
        recurseCreateLinearDom(pBrowser, pLinearDom, pNode, bInsertEndTagNodes, bSkipEmptyNodes );
    }



} // END namespace crawl
