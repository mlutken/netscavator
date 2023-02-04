#include "MozDomNode.h"
#include <nsIDOMHTMLOptionElement.h>
#include <nsIDOMHTMLSelectElement.h>
#include <nsIDOMHTMLOptionsCollection.h>
#include <nsIBoxObject.h>
#include <nsIDocument.h>

#include <dom/DOMNode.h>
#include <dom/DOMElement.h>
#include <dom/DOMDocument.h>
#include <dom/DOMEvent.h>
#include <dom/DOMMouseEvent.h>
#include <dom/DOMKeyEvent.h>
#include <dom/DOMEventTarget.h>
#include <dom/DOMDocumentEvent.h>
#include <dom/DOMHTMLInputElement.h>
#include <dom/DOMHTMLFormElement.h>
#include <dom/DOMHTMLAnchorElement.h>
#include <dom/DOMHTMLSelectElement.h>
#include <dom/DOMHTMLOptionElement.h>
#include <utils/mozilla_utils.h>
#include <cpaf_string_utils.hpp>
#include <LinearDomIF.h>
#include <BoxObjectIF.h>
#include <MozBrowserWx.h>
//#include <url/Url.h>

namespace crawl {

    // ------------------------
    // --- Helper functions ---
    // ------------------------

//    /** Create event.
//    \include dom_events.inc */
//    template <typename EVENT_TYPE>
//            boost::shared_ptr<EVENT_TYPE>
//            createEvent2 (
//                    boost::shared_ptr<DOMDocumentEvent> pDOMDocEvent, 	///< DOM doc event creator
//                    std::string const& sEventCreateName					///< Event create names ( see first listing )
//                    )
//    {
//        if ( !pDOMDocEvent ) return boost::shared_ptr<EVENT_TYPE>();
//        boost::shared_ptr<DOMEvent> 	pEvent 				= pDOMDocEvent->createEvent( sEventCreateName );
//        boost::shared_ptr<EVENT_TYPE> 	pActualTypeEvent 	= doQueryInterface<EVENT_TYPE>(pEvent) ;
//        return pActualTypeEvent;
//    }


    /**
    Create event.
    \include dom_events.inc */
    template <typename EVENT_TYPE>
            boost::shared_ptr<EVENT_TYPE>
            createEvent2 (
                    boost::shared_ptr<DOMNode> pNode, 		///< Node/element pointer
                    std::string const& sEventCreateName		///< Event create names ( see first listing )
                    )
    {
        if ( !pNode ) return boost::shared_ptr<EVENT_TYPE>();
//        boost::shared_ptr<DOMDocumentEvent> pDOMDocEvent ( doQueryInterface<DOMDocumentEvent>( pNode->ownerDocument() ) );
//        boost::shared_ptr<DOMEvent> 	pEvent 				= pDOMDocEvent->createEvent( sEventCreateName );
        boost::shared_ptr<DOMEvent> 	pEvent 				= pNode->ownerDocument()->createEvent( sEventCreateName );
        boost::shared_ptr<EVENT_TYPE> 	pActualTypeEvent 	= doQueryInterface<EVENT_TYPE>(pEvent) ;
        return pActualTypeEvent;
    }

//    /** Create mouse event. */
//    inline boost::shared_ptr<DOMMouseEvent>
//            createMouseEvent (
//                    boost::shared_ptr<DOMDocumentEvent> pDOMDocEvent 	///< DOM doc event creator
//                    )
//    {
//        return createEvent2<DOMMouseEvent>( pDOMDocEvent, "mouseevent" );
//    }



    /**  Create mouse event. */
    inline boost::shared_ptr<DOMMouseEvent>
            createMouseEvent (
                    boost::shared_ptr<DOMNode> pNode 	///< Node/element pointer
                    )
    {
        return createEvent2<DOMMouseEvent>( pNode, "mouseevent" );
    }


//    /** Create key event. */
//    inline boost::shared_ptr<DOMKeyEvent>
//            createKeyEvent (
//                    boost::shared_ptr<DOMDocumentEvent> pDOMDocEvent 	///< DOM doc event creator
//                    )
//    {
//        return createEvent2<DOMKeyEvent>( pDOMDocEvent, "keyboardevent" );
//    }


    /** Create key event. */
    inline boost::shared_ptr<DOMKeyEvent>
            createKeyEvent (
                    boost::shared_ptr<DOMNode> pNode 	///< Node/element pointer
                    )
    {
        return createEvent2<DOMKeyEvent>( pNode, "keyboardevent" );
    }


//    /** Create UI event. */
//    inline boost::shared_ptr<DOMUIEvent>
//            createUIEvent (
//                    boost::shared_ptr<DOMDocumentEvent> pDOMDocEvent 	///< DOM doc event creator
//                    )
//    {
//        return createEvent2<DOMUIEvent>( pDOMDocEvent, "keyboardevent" );
//    }


    /** Create UI event. */
    inline boost::shared_ptr<DOMUIEvent>
            createUIEvent (
                    boost::shared_ptr<DOMNode> pNode 	///< Node/element pointer
                    )
    {
        return createEvent2<DOMUIEvent>( pNode, "keyboardevent" );
    }


    /** Send event to element.
    \return true if operation was successfull .*/
    inline bool
            sendEvent (
                    boost::shared_ptr<DOMEventTarget>	pEventTgt, 	///< Event tarrget to dispatch event to.
                    boost::shared_ptr<DOMEvent>			pEvent		///< Event to dispatch.
                    )
    {
        if ( !pEventTgt ) return false;
        pEventTgt->dispatchEvent( pEvent );
        return true;
    }

    /** Send event to element.
    \return true if operation was successfull .*/
    bool
            sendEventTgt (
                    boost::shared_ptr<DOMEventTarget> 	pEventTgt,	///< Event target to dispatch event to
                    boost::shared_ptr<DOMEvent>			pEvent		///< Event to dispatch
                    )
    {
        //  	printf("ML: sendEventTgt 1: pEvent:\n");
        if ( !pEventTgt && !pEvent ) return false;
        pEventTgt->dispatchEvent( pEvent );
        return true;
    }



    /** Send event to element.
    \return true if operation was successfull .*/
    bool
            sendEvent (
                    boost::shared_ptr<DOMNode>		pTargetNode, 	///< Node/element to dispatch event to
                    boost::shared_ptr<DOMEvent>		pEvent			///< Event to dispatch
                    )
    {
        if ( !pTargetNode ) return false;
        boost::shared_ptr<DOMEventTarget> 	pEventTgt( doQueryInterface<DOMEventTarget>(pTargetNode) );
        pEventTgt->dispatchEvent( pEvent );
        return true;
    }

    /**
    Send mouse event(s) to element.

    \see http://www.howtocreate.co.uk/tutorials/javascript/domevents

    Note that manually firing an event does not generate the default action associated with that
    event. For example, manually firing a focus event does not cause the element to receive focus
    (you must use its focus method for that), manually firing a submit event does not submit a
    form (use the submit method), manually firing a key event does not cause that letter to appear
    in a focused text input, and manually firing a click event on a link does not cause the link
    to be activated, etc. In the case of UI events, this is important for security reasons, as it
    prevents scripts from simulating user actions that interact with the browser itself.

    There are five DOM 2 event modules, and they map directly to the names of the DOM features;
    Events
        Covers all event types.
    HTMLEvents
        Covers 'abort', 'blur', 'change', 'error', 'focus', 'load', 'reset', 'resize',
        'scroll', 'select', 'submit', and 'unload'.
    UIEvents
        Covers 'DOMActivate', 'DOMFocusIn', 'DOMFocusOut',
        and (since they do not have their own key events module in DOM 2) it also covers 'keydown',
        'keypress', and 'keyup'.
        Also indirectly covers MouseEvents.
    MouseEvents
        Covers 'click', 'mousedown', 'mousemove', 'mouseout', 'mouseover', and 'mouseup'.
    MutationEvents
        Covers 'DOMAttrModified', 'DOMNodeInserted', 'DOMNodeRemoved', 'DOMCharacterDataModified',
        'DOMNodeInsertedIntoDocument', 'DOMNodeRemovedFromDocument', and 'DOMSubtreeModified'.


    \include dom_events.inc
    \return true if operation was successfull .*/
    bool
            sendMouseEvent (
                    boost::shared_ptr<DOMNode>	pTargetNode, 	///< [in] Node/element to dispatch event to
                    const std::string& 			sEventNames,	///< [in] Event names ( comma separated ) to dispatch
                    boost::int32_t 				iDetail,		///< [in] Detail argument from W3C DOM spec.
                    boost::uint32_t 			iButton			///< [in] Button ( left=0, middle/wheel=1, right=2 )
                    )
    {
        using namespace cpaf;
        if ( !pTargetNode ) return false;

        StringVecT events;
        cpaf::split	( events, sEventNames, "," );

        for ( StringVecT::const_iterator it = events.begin(); it != events.end(); ++it ){
            boost::shared_ptr<DOMMouseEvent> 	pMouseEvent = createMouseEvent ( pTargetNode );
            pMouseEvent->initMouseEvent ( *it, true, true, iDetail, iButton );
            sendEvent( pTargetNode, pMouseEvent );
        }
        return true;
    }


    /** Simulates a real user left-clicking an element.
    These events are send :
     -# mouseover
     -# focus
     -# mouseup
     -# click
     -# mouseout
     -# blur


    \return True if events were sent.
    \sa nodeClick, which does almost the same as this except in case of INPUT nodes,
    which instead gets their member function 'click' called.  */
    bool userClickNoMouseDown2 (
            boost::shared_ptr<DOMNode> pNode 	)	///< Node/element pointer
    {
        if ( !pNode ) return false;
        //	boost::shared_ptr<DOMUIEvent> 		pUIEvent 	= createUIEvent ( pNode );
        boost::shared_ptr<DOMMouseEvent> 	pMouseEvent = createMouseEvent ( pNode );
        boost::shared_ptr<DOMEventTarget> 	pEventTgt( doQueryInterface<DOMEventTarget>(pNode) );

        pMouseEvent->initMouseEvent	( "mouseover", 	false, 	0 );
        sendEventTgt	( pEventTgt, pMouseEvent );

        // 	printf("ML: userClick BEFORE mousedown\n ");
        pMouseEvent->initMouseEvent	( "mousedown", 	false, 	0 );
        // 	sendEventTgt	( pEventTgt, pMouseEvent );
        // 	printf("ML: userClick AFTER mousedown\n ");


        pMouseEvent->initMouseEvent	( "focus", 		false, 	0 );	// TODO: Perhaps this should just be a simple UIEvent
        sendEventTgt	( pEventTgt, pMouseEvent );
        pMouseEvent->initMouseEvent	( "mouseup", 	false, 	0 );
        sendEventTgt	( pEventTgt, pMouseEvent );
        pMouseEvent->initMouseEvent	( "click", 		false, 	0 );
        sendEventTgt	( pEventTgt, pMouseEvent );
        pMouseEvent->initMouseEvent	( "mouseout", 	false, 	0 );
        sendEventTgt	( pEventTgt, pMouseEvent );
        pMouseEvent->initMouseEvent	( "blur", 		false,	0 );	// TODO: Perhaps this should just be a simple UIEvent
        sendEventTgt	( pEventTgt, pMouseEvent );
        return true;
    }

    /** Simulates a real user left-clicking an element.
    These events are send :
     -# click
    \return True if events were sent.
    \sa nodeClick, which does almost the same as this except in case of INPUT nodes,
    which instead gets their member function 'click' called.  */
    bool userClickSimple2 (
            boost::shared_ptr<DOMNode> pNode 	)	///< Node/element pointer
    {
        if ( !pNode ) return false;
        boost::shared_ptr<DOMUIEvent> 		pUIEvent 	= createUIEvent ( pNode );
        boost::shared_ptr<DOMMouseEvent> 	pMouseEvent = createMouseEvent ( pNode );
        boost::shared_ptr<DOMEventTarget> 	pEventTgt( doQueryInterface<DOMEventTarget>(pNode) );

        // 	printf("userClickSimple2 1 \n");
        pMouseEvent->initMouseEvent	( "click", 		false, 	0 );
        sendEvent	( pEventTgt, pMouseEvent );
        // 	printf("userClickSimple2 2 \n");
        // 	pMouseEvent->initMouseEvent	( "mousedown", 	false, 	0 );
        // 	sendEventTgt	( pEventTgt, pMouseEvent );
        // 	pMouseEvent->initMouseEvent	( "mouseup", 	false, 	0 );
        // 	sendEventTgt	( pEventTgt, pMouseEvent );
        return true;
    }

    /**
    Select option element. If pTargetNode is an OPTION element a selection of this element is simulated.
     - The parent SELECT element is clicked
     - The OPTION element is clicked
     - The SELECT element is set to the OPTION element
     - The SELECT element gets sent a 'change' event (onchange).
    \return true if operation was successfull .*/
    bool selectOption2 (	boost::shared_ptr<DOMNode>	pTargetNode	)	///< [in] Target node that should be an OPTION element
    {
        if ( pTargetNode  && pTargetNode->ifMoz() ) {
            nsCOMPtr<nsIDOMHTMLOptionElement> piOptionElement;
            piOptionElement = do_QueryInterface( pTargetNode->ifMoz() );
            if ( piOptionElement ) {
                nsCOMPtr<nsIDOMHTMLSelectElement> piSelectElement;
                piSelectElement = do_QueryInterface( pTargetNode->parentNode()->ifMoz() );
                // Click on parent SELECT element
                boost::shared_ptr<DOMNode> pParentNode = pTargetNode->parentNode();
                if ( piSelectElement && pTargetNode->parentNode() ) {
                    crawl::userClickSimple2( pTargetNode->parentNode() );
                }
                // Click on OPTION node, set it as selected and dispatch a 'change' event
                crawl::userClickNoMouseDown2( pTargetNode );
                piOptionElement->SetSelected( PR_TRUE );
                return sendMouseEvent( pTargetNode->parentNode(), "change", 0, 0 );
            }
        }
        return false;
    }



    /**
    Select indexed element in SELECT. If pTargetNode is an SELECT element a selection of the index requestedsimulated:
     - The SELECT element is clicked
     - The OPTION element corresponding to the index is clicked
     - The SELECT element is set to the OPTION element
     - The SELECT element gets send a 'change' event (onchange).
    \return true if operation was successfull .*/
    bool	selectSelect2 (
            boost::shared_ptr<DOMHTMLOptionElement>&	pOptionNode 	///< [out] Selected option node (an OPTION element)
            , boost::shared_ptr<DOMNode>                pTargetNode 	///< [in] Target node that should be a SELECT element
            , boost::int32_t iIndex	)                                   ///< [in] Index of OPTION to select.
    {
        pOptionNode = boost::shared_ptr<DOMHTMLOptionElement>();
        if ( pTargetNode && pTargetNode->ifMoz() ) {
            nsCOMPtr<nsIDOMHTMLSelectElement> piSelectElement;
            piSelectElement = do_QueryInterface( pTargetNode->ifMoz() );
            if ( piSelectElement ) {
                nsCOMPtr<nsIDOMHTMLOptionsCollection> pIOptionsCollection;
                piSelectElement->GetOptions( getter_AddRefs(pIOptionsCollection) );
                if ( pIOptionsCollection ) {
                    nsCOMPtr<nsIDOMNode> pIDOMNode;
                    pIOptionsCollection->Item ( iIndex, getter_AddRefs(pIDOMNode) ) ;
                    boost::shared_ptr<DOMNode> pOption(new DOMNode(pIDOMNode));
                    pOptionNode = doQueryInterface<DOMHTMLOptionElement>(pOption);
                    return selectOption2( pOption );
                }
            }
        }
        return false;
    }

    // ------------------
    // --- MozDomNode ---
    // ------------------


    MozDomNode::MozDomNode(
            boost::shared_ptr<DOMNode> pNativeNode
            , boost::shared_ptr<crawl::WebBrowserIF> pOwnerBrowser
            )
                : DomNodeIF     ( pOwnerBrowser )
                , m_pNativeNode ( pNativeNode   )
                , m_iNodeType   ( 0             )
    {
    }

    MozDomNode::~MozDomNode()
    {
    }


    // -------------------------------------
    // --- PRIVATE: Structural functions ---
    // -------------------------------------
    boost::shared_ptr<DomNodeIF> MozDomNode::do_parentNode       (
            int iLevelsUp
            ) const
    {
        if ( !m_pNativeNode ) return boost::shared_ptr<DomNodeIF>();
        if ( iLevelsUp < 1 ) iLevelsUp = 1;

        int i = iLevelsUp;
        boost::shared_ptr<DOMNode> pNode = m_pNativeNode;
        while ( (i > 0) && (pNode && pNode->parentNode()) )	{
            pNode = pNode->parentNode();
            i--;
        }
        if ( i == 0 )	return boost::shared_ptr<DomNodeIF>(new MozDomNode(pNode, ownerBrowser()) );
        else			return boost::shared_ptr<DomNodeIF>();
    }



    bool MozDomNode::do_hasChildNodes    () const
    {
		// TODO: Implement this
		return false;
    }

    boost::shared_ptr<BoxObjectIF> MozDomNode::do_getBoxObject () const
    {
        boost::shared_ptr<crawl::WebBrowserIF> pWebBrowserIF = ownerBrowser();

        boost::shared_ptr<MozBrowserWx> pBrowser = boost::static_pointer_cast<MozBrowserWx>( pWebBrowserIF );
        boost::shared_ptr<BoxObjectIF> pBox;

        nsCOMPtr<nsIDocument>	pIDocument = pBrowser->getContentDOMWindow()->document()->getDocument();
        if ( pIDocument ) {
            nsCOMPtr<nsIBoxObject> pIBoxObject;

            boost::shared_ptr<DOMElement> pElem = boost::static_pointer_cast<DOMElement>(m_pNativeNode);

            pIDocument->GetBoxObjectFor( pElem->ifMoz(), getter_AddRefs(pIBoxObject));
            if ( pIBoxObject ) {
                boost::int32_t xWin, yWin, xScr, yScr, w, h;
                pIBoxObject->GetX		( reinterpret_cast<PRInt32*>(&xWin) );
                pIBoxObject->GetY		( reinterpret_cast<PRInt32*>(&yWin) );
                pIBoxObject->GetScreenX	( reinterpret_cast<PRInt32*>(&xScr) );
                pIBoxObject->GetScreenY	( reinterpret_cast<PRInt32*>(&yScr) );
                pIBoxObject->GetWidth	( reinterpret_cast<PRInt32*>(&w) );
                pIBoxObject->GetHeight  ( reinterpret_cast<PRInt32*>(&h) );

                boost::shared_ptr<DomNodeIF> pOwningNode = boost::const_pointer_cast<DomNodeIF>(shared_from_this());
                pBox = boost::shared_ptr<BoxObjectIF>( new crawl::BoxObjectIF(pOwningNode, xWin, yWin, w, h, xScr, yScr) );
            }
        }
        return pBox;
    }

    void MozDomNode::do_childNodesGet    ( std::vector<boost::shared_ptr<DomNodeIF> >& nodes ) const
    {

    }

    boost::shared_ptr<DomNodeIF> MozDomNode::do_firstChild () const
    {
        boost::shared_ptr<DOMNode> pNative = m_pNativeNode->firstChild();
        return mkMozDomNode( pNative, ownerBrowser() );
    }

    boost::shared_ptr<DomNodeIF> MozDomNode::do_lastChild () const
    {
        boost::shared_ptr<DOMNode> pNative = m_pNativeNode->lastChild();
        return mkMozDomNode( pNative, ownerBrowser() );
    }

    boost::shared_ptr<DomNodeIF> MozDomNode::do_previousSibling () const
    {
        boost::shared_ptr<DOMNode> pNative = m_pNativeNode->previousSibling();
        return mkMozDomNode( pNative, ownerBrowser() );

    }

    boost::shared_ptr<DomNodeIF> MozDomNode::do_nextSibling () const
    {
        boost::shared_ptr<DOMNode> pNative = m_pNativeNode->nextSibling();
        return mkMozDomNode( pNative, ownerBrowser() );

    }


    // ------------------------------------
    // --- PRIVATE: Attribute functions ---
    // ------------------------------------
    std::string MozDomNode::do_attributeGet (
            const std::string& sName
            ) const
    {
        boost::shared_ptr<DOMElement> pElem = doQueryInterface<DOMElement>(m_pNativeNode);
        if ( pElem ){
            return pElem->getAttribute(sName);
        }
        return "";
    }

    void MozDomNode::do_attributeSet (
            const std::string& sName
            ,const std::string& sValue
            )
    {
        boost::shared_ptr<DOMElement> pElem = doQueryInterface<DOMElement>(m_pNativeNode);
        if ( pElem ){
            pElem->setAttribute(sName, sValue);
        }
    }

    void MozDomNode::do_attributesGet    ( AttributesMap& attributes ) const
    {

    }

    // -------------------------------
    // --- PRIVATE: Info functions ---
    // -------------------------------
    std::string MozDomNode::do_stringDataUTF8Get () const
    {
        if ( !m_pNativeNode ) return "";
        return m_pNativeNode->stringData(true);
    }

    std::string MozDomNode::do_nodeNameGet  () const
    {
        if ( !m_pNativeNode ) return "";
        return m_pNativeNode->nodeName();
    }

    std::string MozDomNode::do_nodeValueGet () const
    {
        if ( !m_pNativeNode ) return "";
        return m_pNativeNode->nodeValue();

    }

    std::string MozDomNode::do_nodeTextGet () const
    {
        if ( !m_pNativeNode ) return "";
        return "TODO: MozDomNode::do_nodeTextGet()";

    }

    std::string MozDomNode::do_hrefGet () const
    {
        if ( !m_pNativeNode ) return "";
        DOMHTMLAnchorElement::Ptr pAnchor= doQueryInterface<DOMHTMLAnchorElement>(m_pNativeNode);
        if ( pAnchor ) {
            return pAnchor->href();
        }
        return "";
    }

    std::string MozDomNode::do_hrefCompleteGet () const
    {
        return href();
        // TODO: Move Url class to interfaces project
        //return linkComplete( Url (ownerBrowser()->currentUri() ), href() ).string();
    }


    void* MozDomNode::do_nativeNodePtrGet  () const
    {
        if ( !m_pNativeNode ) return 0;
        return m_pNativeNode->ifMoz();
    }

    boost::uint32_t MozDomNode::do_nodeTypeGet () const
    {

        if ( !m_pNativeNode ) return 0;
        return m_pNativeNode->nodeType();
    }


    // -----------------------------
    // --- PRIVATE: Node actions ---
    // -----------------------------
    bool MozDomNode::do_click  () const
    {
        if ( !m_pNativeNode ) return false;
        //	boost::shared_ptr<DOMUIEvent> 		pUIEvent 	= createUIEvent ( pNode );
        boost::shared_ptr<DOMMouseEvent> 	pMouseEvent = createMouseEvent ( m_pNativeNode );
        boost::shared_ptr<DOMEventTarget> 	pEventTgt( doQueryInterface<DOMEventTarget>(m_pNativeNode) );

        pMouseEvent->initMouseEvent	( "mouseover", 	false, 	0 );
        sendEventTgt	( pEventTgt, pMouseEvent );
        pMouseEvent->initMouseEvent	( "mousedown", 	false, 	0 );
        sendEventTgt	( pEventTgt, pMouseEvent );
        pMouseEvent->initMouseEvent	( "focus", 		false, 	0 );	// TODO: Perhaps this should just be a simple UIEvent
        sendEventTgt	( pEventTgt, pMouseEvent );
        pMouseEvent->initMouseEvent	( "mouseup", 	false, 	0 );
        sendEventTgt	( pEventTgt, pMouseEvent );
        pMouseEvent->initMouseEvent	( "click", 		false, 	0 );
        sendEventTgt	( pEventTgt, pMouseEvent );
        pMouseEvent->initMouseEvent	( "mouseout", 	false, 	0 );
        sendEventTgt	( pEventTgt, pMouseEvent );
        pMouseEvent->initMouseEvent	( "blur", 		false,	0 );	// TODO: Perhaps this should just be a simple UIEvent
        sendEventTgt	( pEventTgt, pMouseEvent );
        return true;
    }

    bool MozDomNode::do_mouseEvent (
            std::string const& 			sEventNames	///< [in] Event names ( comma separated ) to dispatch
            , boost::int32_t 			iDetail		///< [in] Detail argument from W3C DOM spec.
            , boost::uint32_t 			iButton		///< [in] Button ( left=0, middle/wheel=1, right=2 )
            ) const
    {
        using namespace cpaf;
        if ( !m_pNativeNode ) return false;
        //tryFocus( pTargetNode );

        StringVecT events;
        cpaf::split	( events, sEventNames, "," );
        for ( StringVecT::const_iterator it = events.begin(); it != events.end(); ++it ){
            boost::shared_ptr<DOMMouseEvent> 	pMouseEvent = createMouseEvent ( m_pNativeNode );
            pMouseEvent->initMouseEvent ( *it, true, true, iDetail, iButton );
            sendEvent( m_pNativeNode, pMouseEvent );
        }
        //tryBlur ( pTargetNode );
        return true;
    }

    bool MozDomNode::do_inputSet (
            const std::string& sValue
            ) const
    {
        if ( !m_pNativeNode	) return false;
        DOMHTMLInputElement::Ptr pInput ( doQueryInterface<DOMHTMLInputElement>( m_pNativeNode ) );
        if ( pInput->valid() ) {
            pInput->value( sValue );
            return true;
        }
        return false;
    }

    bool MozDomNode::do_formSubmit () const
    {
        if ( !m_pNativeNode ) return false;
        DOMHTMLFormElement::Ptr pElem ( doQueryInterface<DOMHTMLFormElement>( m_pNativeNode ) );
        if ( pElem->valid() ) {
            pElem->submit();
            return true;
        }
        return false;
    }

    bool MozDomNode::do_formReset () const
    {
        if ( !m_pNativeNode ) return false;
        DOMHTMLFormElement::Ptr pElem ( doQueryInterface<DOMHTMLFormElement>( m_pNativeNode ) );
        if ( pElem->valid() ) {
            pElem->reset();
            return true;
        }
        return false;
    }

    // ------------------------------------
    // --- PRIVATE: Node select actions ---
    // ------------------------------------
    int MozDomNode::do_selectLengthGet      () const
    {
        if ( !m_pNativeNode ) return false;
        nsCOMPtr<nsIDOMHTMLSelectElement> piSelectElement;
        piSelectElement = do_QueryInterface( m_pNativeNode->ifMoz() );
        if ( piSelectElement ) {
            PRUint32 iSize;
            piSelectElement->GetLength( &iSize );
            return static_cast<int>(iSize);
        }
        return 0;
    }

    int MozDomNode::do_selectedIndexGet     () const
    {
        if ( !m_pNativeNode ) return false;
        nsCOMPtr<nsIDOMHTMLSelectElement> piSelectElement;
        piSelectElement = do_QueryInterface( m_pNativeNode->ifMoz() );
        if ( piSelectElement ) {
            PRInt32 iIndex;
            piSelectElement->GetSelectedIndex( &iIndex );
            return static_cast<boost::int32_t>(iIndex);
        }
        return 0;

    }

    int MozDomNode::do_selectedDomPosGet 	() const
    {
        if ( !m_pNativeNode ) return 0;
        nsCOMPtr<nsIDOMHTMLSelectElement> piSelectElement;
        piSelectElement = do_QueryInterface( m_pNativeNode->ifMoz() );
        if ( piSelectElement ) {
            nsCOMPtr<nsIDOMHTMLOptionsCollection> pIOptionsCollection;
            piSelectElement->GetOptions( getter_AddRefs(pIOptionsCollection) );
            PRInt32 iIndex;
            piSelectElement->GetSelectedIndex( &iIndex );

            if ( pIOptionsCollection ) {
                nsCOMPtr<nsIDOMNode> pIDOMNode;
                pIOptionsCollection->Item ( iIndex, getter_AddRefs(pIDOMNode) ) ;
                boost::shared_ptr<crawl::LinearDomIF> pOwnerLinearDom = ownerLinearDom();
                if ( pOwnerLinearDom ) {
                    //boost::shared_ptr<DomNodeIF> pDomNode (new MozDomNode(pNode, ownerBrowser()) );
                    LinearDomIF::const_iterator it = pOwnerLinearDom->findFromRawPointer( pIDOMNode.get() );
                    return ownerLinearDom()->iteratorToPos(it);
                }
            }
        }
        return 0;
    }

    bool MozDomNode::do_selectIndex		( int iIndex ) const
    {
        if ( !m_pNativeNode ) return false;
        boost::shared_ptr<DOMHTMLOptionElement> pOptionNode;
        return selectSelect2( pOptionNode, m_pNativeNode, iIndex );
    }

    bool MozDomNode::do_selectOption	() const
    {
        if ( !m_pNativeNode ) return false;
        return selectOption2( m_pNativeNode );
    }


    std::string MozDomNode::do_selectValueGet              () const
    {
        std::string sRetVal = "";
        if ( m_pNativeNode ) {
            DOMHTMLSelectElement::Ptr pElement = doQueryInterface<DOMHTMLSelectElement>(m_pNativeNode);
            if ( pElement ) sRetVal = pElement->value();
        }
        return sRetVal;
    }

    std::string MozDomNode::do_selectTextGet              () const
    {
        printf("TODO: MozDomNode::do_selectTextGet ()\n" );
        return "TODO: MozDomNode::do_selectTextGet";
    }

    std::string MozDomNode::do_optionTextGet               () const
    {
        std::string sRetVal = "";
        if ( m_pNativeNode ) {
            DOMHTMLOptionElement::Ptr pElement = doQueryInterface<DOMHTMLOptionElement>(m_pNativeNode);
            if ( pElement ) sRetVal = pElement->text();
        }
        return sRetVal;
    }

    boost::shared_ptr<DomNodeIF> MozDomNode::do_selectOptionNodeGet ( int iIndex ) const
    {
        boost::shared_ptr<DomNodeIF> pOptionReturnNode;

        if ( m_pNativeNode && m_pNativeNode->ifMoz() ) {
            nsCOMPtr<nsIDOMHTMLSelectElement> piSelectElement;
            piSelectElement = do_QueryInterface( m_pNativeNode->ifMoz() );
            if ( piSelectElement ) {
                nsCOMPtr<nsIDOMHTMLOptionsCollection> pIOptionsCollection;
                piSelectElement->GetOptions( getter_AddRefs(pIOptionsCollection) );
                if ( pIOptionsCollection ) {
                    nsCOMPtr<nsIDOMNode> pIDOMNode;
                    pIOptionsCollection->Item ( iIndex, getter_AddRefs(pIDOMNode) ) ;
                    boost::shared_ptr<DOMNode> pOption(new DOMNode(pIDOMNode));
                    pOptionReturnNode = mkMozDomNode(pOption, ownerBrowser() );
                }
            }
        }
        return pOptionReturnNode;
    }



    boost::shared_ptr<DomNodeIF> MozDomNode::do_optionOwnerSelectNodeGet    () const
    {
        boost::shared_ptr<DomNodeIF> pSelectNode = parentNode(1);
        if ( pSelectNode && pSelectNode->nodeName() == "OPTION" ) {
            pSelectNode = parentNode(2);
        }
        if ( pSelectNode && pSelectNode->nodeName() != "SELECT" ) {
            pSelectNode = boost::shared_ptr<DomNodeIF>();
        }
        return pSelectNode;
    }



    // -----------------------------
    // --- Free helper functions ---
    // -----------------------------

    boost::shared_ptr<MozDomNode> mkMozDomNode(
            boost::shared_ptr<DOMNode> pNativeNode
            , boost::shared_ptr<crawl::WebBrowserIF> pOwnerBrowser
            )
    {
        return boost::shared_ptr<MozDomNode> ( new MozDomNode(pNativeNode, pOwnerBrowser ) );
    }

} // END namespace crawl

