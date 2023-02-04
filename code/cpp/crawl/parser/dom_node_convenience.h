#ifndef _CRAWL_DOM_NODE_CONVENIENCE_H_
#define _CRAWL_DOM_NODE_CONVENIENCE_H_

#include <string>	
#include <boost/shared_ptr.hpp>	

#include <dom/DOMNode.h>
#include <dom/DOMDocument.h>
#include <dom/DOMEvent.h>
#include <dom/DOMMouseEvent.h>
#include <dom/DOMKeyEvent.h>
#include <dom/DOMEventTarget.h>
#include <dom/DOMDocumentEvent.h>

#include <utils/string_compare_functions.h>
#include <utils/string_algorithms.h>

class DOMNode;
class DOMHTMLOptionElement;

namespace crawl {


boost::shared_ptr<DOMNode>
parentNode ( int iLevelsUp, boost::shared_ptr<DOMNode> pNode ); 

boost::shared_ptr<DOMNode>
parentNodeFind ( int iCount, boost::shared_ptr<DOMNode> pNode, const StringCompareFunT& strComp, const std::string& sPattern ); 

bool tryFocus 	( boost::shared_ptr<DOMNode>	pTargetNode	);
bool tryBlur	( boost::shared_ptr<DOMNode>	pTargetNode	);

bool
inputClick ( boost::shared_ptr<DOMNode> pNode ); 


bool
inputClick ( boost::shared_ptr<DOMNode> pNode ); 

bool
inputValue ( boost::shared_ptr<DOMNode> pNode, std::string const& sVal ); 

bool
formSubmit ( boost::shared_ptr<DOMNode> pNode ); 

bool
formReset ( boost::shared_ptr<DOMNode> pNode ); 


// --------------
// --- Events ---
// --------------

bool 	userClick 			( boost::shared_ptr<DOMNode> pNode 	)	;
bool 	userClickNoMouseDown( boost::shared_ptr<DOMNode> pNode 	)	;
bool 	userClickSimple 	( boost::shared_ptr<DOMNode> pNode 	)	;
bool 	nodeClick 			( boost::shared_ptr<DOMNode> pNode 	)	;
bool	dispatchMouseEvent 	( 	boost::shared_ptr<DOMNode>	pTargetNode, std::string const& sEventNames,	
								boost::int32_t iDetail,	boost::uint32_t iButton	);

bool	selectOption 		( 	boost::shared_ptr<DOMNode>	pTargetNode	);
bool	selectSelect 		( 	boost::shared_ptr<DOMHTMLOptionElement>& pOptionNode, boost::shared_ptr<DOMNode>	pTargetNode, boost::int32_t iIndex	);
bool	selectSelect 		( 	boost::shared_ptr<DOMNode>	pTargetNode, boost::int32_t iIndex	);

bool	dispatchEventTgt	( boost::shared_ptr<DOMEventTarget> pEventTgt	, boost::shared_ptr<DOMEvent> pEvent );
bool	dispatchEvent 		( boost::shared_ptr<DOMNode> pTargetNode		, boost::shared_ptr<DOMEvent> pEvent );


/** 
Create event. 
\include dom_events.inc */
//template <typename EVENT_TYPE>
//boost::shared_ptr<EVENT_TYPE>
//createEvent (
//	boost::shared_ptr<DOMDocumentEvent> pDOMDocEvent, 	///< DOM doc event creator
//	std::string const& sEventCreateName					///< Event create names ( see first listing )
//)
//{
//	if ( !pDOMDocEvent ) return boost::shared_ptr<EVENT_TYPE>();
//	boost::shared_ptr<DOMEvent> 	pEvent 				= pDOMDocEvent->createEvent( sEventCreateName );
//	boost::shared_ptr<EVENT_TYPE> 	pActualTypeEvent 	= doQueryInterface<EVENT_TYPE>(pEvent) ;
//	return pActualTypeEvent;
//}


/** 
Create event. 
\include dom_events.inc */
template <typename EVENT_TYPE>
boost::shared_ptr<EVENT_TYPE>
createEvent ( 
	boost::shared_ptr<DOMNode> pNode, 		///< Node/element pointer 
	std::string const& sEventCreateName		///< Event create names ( see first listing )
)
{
	if ( !pNode ) return boost::shared_ptr<EVENT_TYPE>();
//	boost::shared_ptr<DOMDocumentEvent> pDOMDocEvent ( doQueryInterface<DOMDocumentEvent>( pNode->ownerDocument() ) );
//	boost::shared_ptr<DOMEvent> 	pEvent 				= pDOMDocEvent->createEvent( sEventCreateName );
    boost::shared_ptr<DOMEvent> 	pEvent 				= pNode->ownerDocument()->createEvent( sEventCreateName );
	boost::shared_ptr<EVENT_TYPE> 	pActualTypeEvent 	= doQueryInterface<EVENT_TYPE>(pEvent) ;
	return pActualTypeEvent;
} 

/** 
Create mouse event. */
//inline boost::shared_ptr<DOMMouseEvent>
//createMouseEvent (
//	boost::shared_ptr<DOMDocumentEvent> pDOMDocEvent 	///< DOM doc event creator
//)
//{	return createEvent<DOMMouseEvent>( pDOMDocEvent, "mouseevent" ); }



/** 
Create mouse event. */
inline boost::shared_ptr<DOMMouseEvent>
createMouseEvent ( 
	boost::shared_ptr<DOMNode> pNode 	///< Node/element pointer 
)
{	return createEvent<DOMMouseEvent>( pNode, "mouseevent" ); } 


/** 
Create key event. */
//inline boost::shared_ptr<DOMKeyEvent>
//createKeyEvent (
//	boost::shared_ptr<DOMDocumentEvent> pDOMDocEvent 	///< DOM doc event creator
//)
//{	return createEvent<DOMKeyEvent>( pDOMDocEvent, "keyboardevent" ); }


/** 
Create key event. */
inline boost::shared_ptr<DOMKeyEvent>
createKeyEvent ( 
	boost::shared_ptr<DOMNode> pNode 	///< Node/element pointer 
)
{	return createEvent<DOMKeyEvent>( pNode, "keyboardevent" ); } 


/** 
Create UI event. */
//inline boost::shared_ptr<DOMUIEvent>
//createUIEvent (
//	boost::shared_ptr<DOMDocumentEvent> pDOMDocEvent 	///< DOM doc event creator
//)
//{	return createEvent<DOMUIEvent>( pDOMDocEvent, "keyboardevent" ); }


/** 
Create UI event. */
inline boost::shared_ptr<DOMUIEvent>
createUIEvent ( 
	boost::shared_ptr<DOMNode> pNode 	///< Node/element pointer 
)
{	return createEvent<DOMUIEvent>( pNode, "keyboardevent" ); } 


/** 
Send event to element. 
\return true if operation was successfull .*/
inline bool
dispatchEvent ( 
	boost::shared_ptr<DOMEventTarget>	pEventTgt, 	///< Event tarrget to dispatch event to.
	boost::shared_ptr<DOMEvent>			pEvent		///< Event to dispatch.
)
{
	if ( !pEventTgt ) return false;
	pEventTgt->dispatchEvent( pEvent );
	return true;
} 





} // END namespace crawl

#endif //_CRAWL_DOM_NODE_CONVENIENCE_H_

