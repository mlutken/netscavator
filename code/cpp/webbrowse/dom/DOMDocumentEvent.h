#ifndef _WEBBROWSE_DOM_DOCUMENT_EVENT_H_
#define _WEBBROWSE_DOM_DOCUMENT_EVENT_H_

// /*#include <utils/mozilla_if_macros.h>
// #include <utils/mozilla_utils.h>*/
//#include <nsIDOMDocumentEvent.h>
#include <dom/DOMEvent.h>

/**
The nsIDOMDocumentEvent interface is the interface to the event
factory method on a DOM document object.
For more information on this interface please see 
http://www.w3.org/TR/DOM-Level-2-Events
@status FROZEN */
class DOMDocumentEvent : public Supports {
//	MOZ_CONSTRUCT(DOMDocumentEvent,Supports);
public:
	/// nsIDOMEvent createEvent (in DOMString eventType)  raises (DOMException); 
//	CreateEvent(const nsAString & eventType, nsIDOMEvent **_retval) = 0;
//	boost::shared_ptr<DOMEvent>
//	createEvent( const std::string& sEventType )			///< String title
//												{	MOZ_IF_RETURN_MOZ_STRING(CreateEvent,DOMEvent,sEventType);	}

};


#endif /* _WEBBROWSE_DOM_DOCUMENT_EVENT_H_ */
