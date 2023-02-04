#include "dom_node_convenience.h"

#include <iostream>
#include <nsIDOMHTMLOptionElement.h>
#include <nsIDOMHTMLSelectElement.h>
#include <nsIDOMHTMLOptionsCollection.h>

#include <dom/DOMHTMLInputElement.h>
#include <dom/DOMHTMLFormElement.h>
#include <dom/DOMHTMLAnchorElement.h>
#include <dom/DOMHTMLSelectElement.h>
#include <dom/DOMHTMLOptionElement.h>
#include <utils/mozilla_utils.h>

#include <boost/thread/thread.hpp>
#include <cpaf_string_utils.hpp>

namespace crawl {

/** 
Find parent of dom node. You specify the number of levels up (ancestors) 
you want from the input node. Like e.g:
\code
parentNode ( 1, pNode );	// Get immediate parent
parentNode ( 2, pNode );	// Get parent node of parent node (grandparent so to speak)
\return The \a iLevelsUp parent of the specified dom node.
\endcode */
boost::shared_ptr<DOMNode>
parentNode ( 
	 int iLevelsUp							///< [in] (Must be positive greater than 1 ) Number of levels up from input node. 1: Immediate parent, 2: Grandparent, so on
	,boost::shared_ptr<DOMNode> pNode		///< Starting node.
)
{
	if ( !pNode )	return boost::shared_ptr<DOMNode>();
	if ( iLevelsUp < 1 ) iLevelsUp = 1;
	
	int i = iLevelsUp;
	while ( (i > 0) && (pNode && pNode->parentNode()) )	{ 
		pNode = pNode->parentNode();
		i--;
	}
	////for ( ; i > 0; --i ) {
	////	if ( pNode && pNode->parentNode() ) pNode = pNode->parentNode();
	////	else								break;
	////}
	if ( i == 0 )	return pNode;
	else			return boost::shared_ptr<DOMNode>();
}


/** Find a parent node matching the pattern using the specified compare function. 
The \a iCount parameter (must 1 or greater - positive only) specifies the number 
of parent (ancester nodes) that must match the pattern before the node is returned. 
For example:
If ...
\todo Implement this function
\return The node parent/ancestor node matching the pattern and count or empty pointer if not found. */
boost::shared_ptr<DOMNode>
parentNodeFind ( int iCount, boost::shared_ptr<DOMNode> pNode, const StringCompareFunT& strComp, const std::string& sPattern )
{
	boost::shared_ptr<DOMNode> pParentNode;
	
	return pParentNode;
}


/** Tries to call element's focus methoh if applicable.
\return True if node points to an element that have a 'focus' method. */
bool tryFocus (	boost::shared_ptr<DOMNode>	pTargetNode	)	///< [in] Target node 
{
	if ( pTargetNode ) {
		boost::shared_ptr<DOMHTMLAnchorElement> pDOMHTMLAnchorElement( doQueryInterface<DOMHTMLAnchorElement>(pTargetNode) );
		if ( pDOMHTMLAnchorElement && pDOMHTMLAnchorElement->ifMoz() ) {
			printf("DOMHTMLAnchorElement focus\n");
			pDOMHTMLAnchorElement->focus();
			return true;
		}
		boost::shared_ptr<DOMHTMLInputElement> pDOMHTMLInputElement( doQueryInterface<DOMHTMLInputElement>(pTargetNode) );
		if ( pDOMHTMLInputElement && pDOMHTMLInputElement->ifMoz() ) {
			printf("DOMHTMLInputElement focus\n");
			pDOMHTMLInputElement->focus();
			return true;
		}
		boost::shared_ptr<DOMHTMLSelectElement> pDOMHTMLSelectElement( doQueryInterface<DOMHTMLSelectElement>(pTargetNode) );
		if ( pDOMHTMLSelectElement && pDOMHTMLSelectElement->ifMoz() ) {
			printf("DOMHTMLSelectElement focus\n");
			pDOMHTMLSelectElement->focus();
			return true;
		}
	}
	return false;
}


/** Tries to call element's blur methoh if applicable.
\return True if node points to an element that have a 'blur' method. */
bool tryBlur(	boost::shared_ptr<DOMNode>	pTargetNode	)	///< [in] Target node 
{
	if ( pTargetNode ) {
		boost::shared_ptr<DOMHTMLAnchorElement> pDOMHTMLAnchorElement( doQueryInterface<DOMHTMLAnchorElement>(pTargetNode) );
		if ( pDOMHTMLAnchorElement && pDOMHTMLAnchorElement->ifMoz() ) {
			printf("DOMHTMLAnchorElement blur\n");
			pDOMHTMLAnchorElement->blur();
			return true;
		}
		boost::shared_ptr<DOMHTMLInputElement> pDOMHTMLInputElement( doQueryInterface<DOMHTMLInputElement>(pTargetNode) );
		if ( pDOMHTMLInputElement && pDOMHTMLInputElement->ifMoz() ) {
			printf("DOMHTMLInputElement blur\n");
			pDOMHTMLInputElement->blur();
			return true;
		}
		boost::shared_ptr<DOMHTMLSelectElement> pDOMHTMLSelectElement( doQueryInterface<DOMHTMLSelectElement>(pTargetNode) );
		if ( pDOMHTMLSelectElement && pDOMHTMLSelectElement->ifMoz() ) {
			printf("DOMHTMLSelectElement blur\n");
			pDOMHTMLSelectElement->blur();
			return true;
		}
	}
	return false;
}


/** Call HTML input element's 'click()' metod. 
	\return True if node pointer could be safely converted to a DOMHTMLInputElement pointer.*/
bool
inputClick ( 
	boost::shared_ptr<DOMNode> pNode 	///< Node pointer that can be "query interfaced" to a DOMHTMLInputElement pointer
)
{
	if ( !pNode	)	return false;
	DOMHTMLInputElement::Ptr pInput ( doQueryInterface<DOMHTMLInputElement>( pNode ) );
	if ( pInput && pInput->valid() ) {
		pInput->click();
		return true;
	}
	return false;
} 



/** Set HTML input element's value ('value()' metod.) 
	\return True if node pointer could be safely converted to a DOMHTMLInputElement pointer.*/
bool
inputValue ( 
	boost::shared_ptr<DOMNode> pNode, 	///< Node pointer that can be "query interfaced" to a DOMHTMLInputElement pointer
	std::string const& sVal				///< New value
)
{
	if ( !pNode	)	return false;
	DOMHTMLInputElement::Ptr pInput ( doQueryInterface<DOMHTMLInputElement>( pNode ) );
	if ( pInput->valid() ) {
		pInput->value( sVal );
		return true;
	}
	return false;
} 


/** Call HTML form element's 'submit()' metod. 
	\return True if node pointer could be safely converted to a DOMHTMLFormElement pointer.*/
bool
formSubmit ( 
	boost::shared_ptr<DOMNode> pNode 	///< Node pointer that can be "query interfaced" to a DOMHTMLFormElement pointer
)
{
	if ( !pNode	)	return false;
	DOMHTMLFormElement::Ptr pElem ( doQueryInterface<DOMHTMLFormElement>( pNode ) );
	if ( pElem->valid() ) {
		pElem->submit();
		return true;
	}
	return false;
} 


/** Call HTML form element's 'reset()' metod. 
	\return True if node pointer could be safely converted to a DOMHTMLFormElement pointer.*/
bool
formReset ( 
	boost::shared_ptr<DOMNode> pNode 	///< Node pointer that can be "query interfaced" to a DOMHTMLFormElement pointer
)
{
	if ( !pNode	)	return false;
	DOMHTMLFormElement::Ptr pElem ( doQueryInterface<DOMHTMLFormElement>( pNode ) );
	if ( pElem->valid() ) {
		pElem->reset();
		return true;
	}
	return false;
} 


// --------------
// --- Events ---
// --------------
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
dispatchMouseEvent ( 
	boost::shared_ptr<DOMNode>	pTargetNode, 	///< [in] Node/element to dispatch event to
	std::string const& 			sEventNames,	///< [in] Event names ( comma separated ) to dispatch
	boost::int32_t 				iDetail,		///< [in] Detail argument from W3C DOM spec.
	boost::uint32_t 			iButton			///< [in] Button ( left=0, middle/wheel=1, right=2 )
)
{
	using namespace cpaf;
	if ( !pTargetNode ) return false;
//  	printf("C++: dispatchMouseEvent: '%s'\n", sEventNames.c_str() );
// 	tryFocus( pTargetNode );
	
	StringVecT events;
	cpaf::split	( events, sEventNames, "," );
	
	for ( StringVecT::const_iterator it = events.begin(); it != events.end(); ++it ){
		boost::shared_ptr<DOMMouseEvent> 	pMouseEvent = createMouseEvent ( pTargetNode );
// 		pMouseEvent->initMouseEvent ( *it, true, false, iDetail, iButton );
		pMouseEvent->initMouseEvent ( *it, true, true, iDetail, iButton );
		dispatchEvent( pTargetNode, pMouseEvent );
	}
// 	tryBlur ( pTargetNode );
	return true;
} 

/**
Select option element. If pTargetNode is an OPTION element a selection of this element is simulated. 
 - The parent SELECT element is clicked
 - The OPTION element is clicked
 - The SELECT element is set to the OPTION element
 - The SELECT element gets sent a 'change' event (onchange).
\return true if operation was successfull .*/
bool selectOption (	boost::shared_ptr<DOMNode>	pTargetNode	)	///< [in] Target node that should be an OPTION element
{
	if ( pTargetNode  && pTargetNode->ifMoz() ) {
		nsCOMPtr<nsIDOMHTMLOptionElement> piOptionElement;
		piOptionElement = do_QueryInterface( pTargetNode->ifMoz() );
		if ( piOptionElement ) {
			nsCOMPtr<nsIDOMHTMLSelectElement> piSelectElement;
			piSelectElement = do_QueryInterface( pTargetNode->parentNode()->ifMoz() );
			// Click on parent SELECT element 
			if ( piSelectElement && pTargetNode->parentNode() ) {
 				crawl::userClickSimple( pTargetNode->parentNode() );
			}
			// Click on OPTION node, set it as selected and dispatch a 'change' event 
			crawl::userClickNoMouseDown( pTargetNode );
			piOptionElement->SetSelected( PR_TRUE );
			return crawl::dispatchMouseEvent( pTargetNode->parentNode(), "change", 0, 0 );
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
bool	selectSelect (
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
                return selectOption( pOption );
            }
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
bool	selectSelect (
    boost::shared_ptr<DOMNode>	pTargetNode, 	///< [in] Target node that should be a SELECT element
    boost::int32_t iIndex	)					///< [in] Index of OPTION to select.
{
    boost::shared_ptr<DOMHTMLOptionElement> pOptionNode;
    return selectSelect( pOptionNode, pTargetNode, iIndex );
//	if ( pTargetNode && pTargetNode->ifMoz() ) {
//		nsCOMPtr<nsIDOMHTMLSelectElement> piSelectElement;
//		piSelectElement = do_QueryInterface( pTargetNode->ifMoz() );
//		if ( piSelectElement ) {
//			nsCOMPtr<nsIDOMHTMLOptionsCollection> pIOptionsCollection;
//			piSelectElement->GetOptions( getter_AddRefs(pIOptionsCollection) );
//			if ( pIOptionsCollection ) {
//				nsCOMPtr<nsIDOMNode> pIDOMNode;
//				pIOptionsCollection->Item ( iIndex, getter_AddRefs(pIDOMNode) ) ;
//				boost::shared_ptr<DOMNode> pOption(new DOMNode(pIDOMNode));
//				return selectOption( pOption );
//			}
//		}
//	}
//	return false;
}


/** 
Send event to element. 
\return true if operation was successfull .*/
bool
dispatchEventTgt ( 
	boost::shared_ptr<DOMEventTarget> 	pEventTgt,	///< Event target to dispatch event to
	boost::shared_ptr<DOMEvent>			pEvent		///< Event to dispatch
)
{
//  	printf("ML: dispatchEventTgt 1: pEvent:\n");
	if ( !pEventTgt && !pEvent ) return false;
	pEventTgt->dispatchEvent( pEvent );
	return true;
} 



/** 
Send event to element. 
\return true if operation was successfull .*/
bool
dispatchEvent ( 
	boost::shared_ptr<DOMNode>		pTargetNode, 	///< Node/element to dispatch event to
	boost::shared_ptr<DOMEvent>		pEvent			///< Event to dispatch
)
{
	if ( !pTargetNode ) return false;
	boost::shared_ptr<DOMEventTarget> 	pEventTgt( doQueryInterface<DOMEventTarget>(pTargetNode) );
	pEventTgt->dispatchEvent( pEvent );
	return true;
} 



/** Simulates a real user left-clicking an element. 
These events are send :
 -# mouseover
 -# mousedown
 -# focus
 -# mouseup
 -# click
 -# mouseout
 -# blur

\return True if events were sent. 
\sa nodeClick, which does almost the same as this except in case of INPUT nodes,
which instead gets their member function 'click' called.  */
bool userClick (
    boost::shared_ptr<DOMNode> pNode 	)	///< Node/element pointer
{
    if ( !pNode ) return false;
//	boost::shared_ptr<DOMUIEvent> 		pUIEvent 	= createUIEvent ( pNode );
    boost::shared_ptr<DOMMouseEvent> 	pMouseEvent = createMouseEvent ( pNode );
    boost::shared_ptr<DOMEventTarget> 	pEventTgt( doQueryInterface<DOMEventTarget>(pNode) );
	
    pMouseEvent->initMouseEvent	( "mouseover", 	false, 	0 );
    dispatchEventTgt	( pEventTgt, pMouseEvent );
    pMouseEvent->initMouseEvent	( "mousedown", 	false, 	0 );
    dispatchEventTgt	( pEventTgt, pMouseEvent );
    pMouseEvent->initMouseEvent	( "focus", 		false, 	0 );	// TODO: Perhaps this should just be a simple UIEvent
    dispatchEventTgt	( pEventTgt, pMouseEvent );
    pMouseEvent->initMouseEvent	( "mouseup", 	false, 	0 );
    dispatchEventTgt	( pEventTgt, pMouseEvent );
    pMouseEvent->initMouseEvent	( "click", 		false, 	0 );
    dispatchEventTgt	( pEventTgt, pMouseEvent );
    pMouseEvent->initMouseEvent	( "mouseout", 	false, 	0 );
    dispatchEventTgt	( pEventTgt, pMouseEvent );
    pMouseEvent->initMouseEvent	( "blur", 		false,	0 );	// TODO: Perhaps this should just be a simple UIEvent
    dispatchEventTgt	( pEventTgt, pMouseEvent );
    return true;
}
/*
bool userClick (
	boost::shared_ptr<DOMNode> pNode 	)	///< Node/element pointer 
{
	if ( !pNode ) return false;
	boost::shared_ptr<DOMUIEvent> 		pUIEvent 	= createUIEvent ( pNode );
	boost::shared_ptr<DOMMouseEvent> 	pMouseEvent = createMouseEvent ( pNode );
	boost::shared_ptr<DOMEventTarget> 	pEventTgt( doQueryInterface<DOMEventTarget>(pNode) );
	
	pMouseEvent->initMouseEvent	( "mouseover", 	false, 	0 );
	dispatchEventTgt	( pEventTgt, pMouseEvent );
	pMouseEvent->initMouseEvent	( "mousedown", 	false, 	0 );
	dispatchEventTgt	( pEventTgt, pMouseEvent );
	pUIEvent->initUIEvent	( "focus", 		false, 	0 );	// TODO: Perhaps this should just be a simple UIEvent
	dispatchEventTgt	( pEventTgt, pUIEvent );
	pMouseEvent->initMouseEvent	( "mouseup", 	false, 	0 );
	dispatchEventTgt	( pEventTgt, pMouseEvent );
	pMouseEvent->initMouseEvent	( "click", 		false, 	0 );
	dispatchEventTgt	( pEventTgt, pMouseEvent );
	pMouseEvent->initMouseEvent	( "mouseout", 	false, 	0 );
	dispatchEventTgt	( pEventTgt, pMouseEvent );
	pUIEvent->initUIEvent	( "blur", 		false,	0 );	// TODO: Perhaps this should just be a simple UIEvent
	dispatchEventTgt	( pEventTgt, pUIEvent );
	return true;
}
*/


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
bool userClickNoMouseDown (
	boost::shared_ptr<DOMNode> pNode 	)	///< Node/element pointer 
{
	if ( !pNode ) return false;
//	boost::shared_ptr<DOMUIEvent> 		pUIEvent 	= createUIEvent ( pNode );
	boost::shared_ptr<DOMMouseEvent> 	pMouseEvent = createMouseEvent ( pNode );
	boost::shared_ptr<DOMEventTarget> 	pEventTgt( doQueryInterface<DOMEventTarget>(pNode) );
	
	pMouseEvent->initMouseEvent	( "mouseover", 	false, 	0 );
	dispatchEventTgt	( pEventTgt, pMouseEvent );
	
// 	printf("ML: userClick BEFORE mousedown\n ");
	pMouseEvent->initMouseEvent	( "mousedown", 	false, 	0 );
// 	dispatchEventTgt	( pEventTgt, pMouseEvent );
// 	printf("ML: userClick AFTER mousedown\n ");
	
	
	pMouseEvent->initMouseEvent	( "focus", 		false, 	0 );	// TODO: Perhaps this should just be a simple UIEvent
	dispatchEventTgt	( pEventTgt, pMouseEvent );
	pMouseEvent->initMouseEvent	( "mouseup", 	false, 	0 );
	dispatchEventTgt	( pEventTgt, pMouseEvent );
	pMouseEvent->initMouseEvent	( "click", 		false, 	0 );
	dispatchEventTgt	( pEventTgt, pMouseEvent );
	pMouseEvent->initMouseEvent	( "mouseout", 	false, 	0 );
	dispatchEventTgt	( pEventTgt, pMouseEvent );
	pMouseEvent->initMouseEvent	( "blur", 		false,	0 );	// TODO: Perhaps this should just be a simple UIEvent
	dispatchEventTgt	( pEventTgt, pMouseEvent );
	return true;
}


/** Simulates a real user left-clicking an element. 
These events are send :
 -# mouseover
 -# focus
 -# mousedown
 -# mouseup
 -# click
 -# mouseout
 -# blur
 

\return True if events were sent. 
\sa nodeClick, which does almost the same as this except in case of INPUT nodes,
which instead gets their member function 'click' called.  */
bool userClickSimple (
	boost::shared_ptr<DOMNode> pNode 	)	///< Node/element pointer 
{
	if ( !pNode ) return false;
	boost::shared_ptr<DOMUIEvent> 		pUIEvent 	= createUIEvent ( pNode );
	boost::shared_ptr<DOMMouseEvent> 	pMouseEvent = createMouseEvent ( pNode );
	boost::shared_ptr<DOMEventTarget> 	pEventTgt( doQueryInterface<DOMEventTarget>(pNode) );
	
// 	printf("userClickSimple 1 \n");
	pMouseEvent->initMouseEvent	( "click", 		false, 	0 );
	dispatchEvent	( pEventTgt, pMouseEvent );
// 	printf("userClickSimple 2 \n");
// 	pMouseEvent->initMouseEvent	( "mousedown", 	false, 	0 );
// 	dispatchEventTgt	( pEventTgt, pMouseEvent );
// 	pMouseEvent->initMouseEvent	( "mouseup", 	false, 	0 );
// 	dispatchEventTgt	( pEventTgt, pMouseEvent );
	return true;
}

	
// 	boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
//sleep(2);

/** Clicks on a node in the DOM tree. 
In case of INPUT nodes the member function 'click' is called and for 
other nodes we simulate the click like in userClick().
\return True if events were sent. 
\sa userClick, which allways simulates the click using events.  */
bool nodeClick (
	boost::shared_ptr<DOMNode> pNode 	)	///< Node/element pointer 
{
 	return userClick( pNode );
// 	if ( !pNode	)	return false;
// 	DOMHTMLInputElement::Ptr pInput ( doQueryInterface<DOMHTMLInputElement>( pNode ) );
// 	if ( pInput && pInput->valid() ) {
// 		printf("C++: nodeClick! type: '%s'\n", pInput->type().c_str() );
// 		if	( pInput->type() == "text" || pInput->type() == "password" || 
// 			  pInput->type() == "file" || pInput->type() == "hidden" )	
// 		{
// 			return userClick (pNode);
// 		}
// 		printf("C++: pInput->click()\n" );
// 		pInput->click();
// 		return true;
// 	}
// 	else return userClick( pNode );
}


} // END namespace crawl
