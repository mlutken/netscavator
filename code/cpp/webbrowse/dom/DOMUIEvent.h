#ifndef _WEBBROWSE_DOM_UI_EVENT_H_
#define _WEBBROWSE_DOM_UI_EVENT_H_


#include <nsIDOMUIEvent.h>
#include <dom/DOMEvent.h>
#include <dom/DOMAbstractView.h>
#include <dom/DOMWindow.h>


/**
The nsIDOMUIEvent interface is the datatype for all UI events in the
Document Object Model.

For more information on this interface please see
http://www.w3.org/TR/DOM-Level-2-Events/

@status FROZEN  */
class DOMUIEvent : public DOMEvent {
	MOZ_CONSTRUCT(DOMUIEvent,DOMEvent);
public:
//	boost::shared_ptr<DOMAbstractView>
//	view ()
//										{	MOZ_IF_RETURN_MOZ(GetView,DOMAbstractView);	}
	
  	///  Get detail 
	boost::int32_t 				
	detail() const 
										{	MOZ_IF_RETURN_INT32(GetDetail); }
	
//	void initUIEvent ( 	std::string sTypeArg, bool bCanBubbleArg, bool bCancelableArg,
//						boost::shared_ptr<DOMAbstractView> pViewArg, boost::int32_t iDetailArg)
//	{
//		ifMoz()->InitUIEvent( toAStringUTF16(sTypeArg), static_cast<PRBool>(bCanBubbleArg), static_cast<PRBool>(bCancelableArg), pViewArg->ifMoz(), static_cast<PRInt32>(iDetailArg) );
//	}
    void initUIEvent ( 	std::string sTypeArg, bool bCanBubbleArg, bool bCancelableArg,
                        boost::shared_ptr<DOMWindow> pViewArg, boost::int32_t iDetailArg)
	{																																	
		ifMoz()->InitUIEvent( toAStringUTF16(sTypeArg), static_cast<PRBool>(bCanBubbleArg), static_cast<PRBool>(bCancelableArg), pViewArg->ifMoz(), static_cast<PRInt32>(iDetailArg) );	
	}
	// ------------------------------------------------
	// --- Methods beyond W3C/Mozilla specification ---	
	// ------------------------------------------------
	void initUIEvent ( 	std::string sTypeArg, bool bCancelableArg, boost::int32_t iDetailArg)
	{																																	
		ifMoz()->InitUIEvent( toAStringUTF16(sTypeArg), PR_TRUE, static_cast<PRBool>(bCancelableArg), 0, static_cast<PRInt32>(iDetailArg) );	
	}
	
};
#endif // _WEBBROWSE_DOM_UI_EVENT_H_
