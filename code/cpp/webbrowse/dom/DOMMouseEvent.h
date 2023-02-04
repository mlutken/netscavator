#ifndef _WEBBROWSE_DOM_MOUSE_EVENT_H_
#define _WEBBROWSE_DOM_MOUSE_EVENT_H_


#include <nsIDOMMouseEvent.h>
#include <dom/DOMUIEvent.h>
#include <dom/DOMEventTarget.h>

/**
The nsIDOMMouseEvent interface is the datatype for all mouse events
in the Document Object Model.

For more information on this interface please see
http://www.w3.org/TR/DOM-Level-2-Events/
@status FROZEN  */
class DOMMouseEvent : public DOMUIEvent
{
	MOZ_CONSTRUCT(DOMMouseEvent,DOMUIEvent);
public:
	boost::int32_t 
	screenX () const
										{	MOZ_IF_RETURN_INT32(GetScreenX); 				}
	boost::int32_t 
	screenY () const
										{	MOZ_IF_RETURN_INT32(GetScreenY); 				}
	boost::int32_t 
	clientX () const
										{	MOZ_IF_RETURN_INT32(GetClientX); 				}
	boost::int32_t 
	clientY () const
										{	MOZ_IF_RETURN_INT32(GetClientY); 				}
	bool 				
	altKey () const 
										{	MOZ_IF_RETURN_BOOL(GetAltKey); 					}
	bool 				
	ctrlKey () const 
										{	MOZ_IF_RETURN_BOOL(GetCtrlKey); 				}
	bool 				
	shiftKey () const 
										{	MOZ_IF_RETURN_BOOL(GetShiftKey); 				}
	bool 				
	metaKey () const 
										{	MOZ_IF_RETURN_BOOL(GetMetaKey); 				}
 
 
	boost::uint16_t 
	button () const
										{	MOZ_IF_RETURN_UINT16(GetButton); 				}
	
	
	boost::shared_ptr<DOMEventTarget>			
	relatedTarget () const
										{	MOZ_IF_RETURN_MOZ(GetRelatedTarget,DOMEventTarget);	}


	void initMouseEvent ( std::string sTypeArg, bool bCanBubbleArg, bool bCancelableArg, 
                        boost::shared_ptr<DOMWindow> pViewArg,  boost::int32_t iDetailArg,
						boost::int32_t iScreenXArg, boost::int32_t iScreenYArg, 
						boost::int32_t iClientXArg, boost::int32_t iClientYArg,
						bool bCtrlKeyArg, bool bAltKeyArg, 
						bool bShiftKeyArg, bool bMetaKeyArg, 
						boost::uint32_t iButtonArg, boost::shared_ptr<DOMEventTarget>  pRelatedTargetArg )
	{																																	
		ifMoz()->InitMouseEvent( toAStringUTF16(sTypeArg), static_cast<PRBool>(bCanBubbleArg), static_cast<PRBool>(bCancelableArg), 
								pViewArg->ifMoz(), static_cast<PRInt32>(iDetailArg),
								static_cast<PRInt32>(iScreenXArg), static_cast<PRInt32>(iScreenYArg),
								static_cast<PRInt32>(iClientXArg), static_cast<PRInt32>(iClientYArg),
								static_cast<PRBool>(bCtrlKeyArg), static_cast<PRBool>(bAltKeyArg),
								static_cast<PRBool>(bShiftKeyArg), static_cast<PRBool>(bMetaKeyArg),
								static_cast<PRUint32>(iButtonArg), pRelatedTargetArg->ifMoz() );	
	}
	
	// ------------------------------------------------
	// --- Methods beyond W3C/Mozilla specification ---	
	// ------------------------------------------------
	void initMouseEvent ( 	std::string sTypeArg, bool bCanBubbleArg, bool bCancelableArg, 
							boost::int32_t iDetailArg, 
							boost::int32_t iScreenXArg, boost::int32_t iScreenYArg, 
							boost::int32_t iClientXArg, boost::int32_t iClientYArg,
							bool bCtrlKeyArg, bool bAltKeyArg, 
							bool bShiftKeyArg, bool bMetaKeyArg, 
							boost::uint32_t iButtonArg )
	{																																	
		ifMoz()->InitMouseEvent( toAStringUTF16(sTypeArg), static_cast<PRBool>(bCanBubbleArg), static_cast<PRBool>(bCancelableArg), 
								0, static_cast<PRInt32>(iDetailArg),
								static_cast<PRInt32>(iScreenXArg), static_cast<PRInt32>(iScreenYArg),
								static_cast<PRInt32>(iClientXArg), static_cast<PRInt32>(iClientYArg),
								static_cast<PRBool>(bCtrlKeyArg), static_cast<PRBool>(bAltKeyArg),
								static_cast<PRBool>(bShiftKeyArg), static_cast<PRBool>(bMetaKeyArg),
								static_cast<PRUint32>(iButtonArg), 0 );	
	}

	void initMouseEvent ( 	std::string sTypeArg, bool bCanBubbleArg, bool bCancelableArg, 
							boost::int32_t iDetailArg, 
							bool bCtrlKeyArg, bool bAltKeyArg, 
							bool bShiftKeyArg, bool bMetaKeyArg, 
							boost::uint32_t iButtonArg )
	{																																	
		ifMoz()->InitMouseEvent( toAStringUTF16(sTypeArg), static_cast<PRBool>(bCanBubbleArg), static_cast<PRBool>(bCancelableArg), 
								0, static_cast<PRInt32>(iDetailArg),
								0, 0, 0, 0,
								static_cast<PRBool>(bCtrlKeyArg), static_cast<PRBool>(bAltKeyArg),
								static_cast<PRBool>(bShiftKeyArg), static_cast<PRBool>(bMetaKeyArg),
								static_cast<PRUint32>(iButtonArg), 0 );	
	}

	void initMouseEvent ( 	std::string sTypeArg, bool bCanBubbleArg, bool bCancelableArg, 
							boost::int32_t iDetailArg, 
							boost::uint32_t iButtonArg )
	{																																	
		ifMoz()->InitMouseEvent( toAStringUTF16(sTypeArg), static_cast<PRBool>(bCanBubbleArg), static_cast<PRBool>(bCancelableArg), 
								0, static_cast<PRInt32>(iDetailArg),
								0, 0, 0, 0,
								PR_FALSE, PR_FALSE,	PR_FALSE, PR_FALSE,
								static_cast<PRUint32>(iButtonArg), 0 );	
	}

	void initMouseEvent ( 	std::string sTypeArg, bool bCancelableArg, 
							boost::uint32_t iButtonArg )
	{																																	
		ifMoz()->InitMouseEvent( toAStringUTF16(sTypeArg), PR_TRUE, static_cast<PRBool>(bCancelableArg), 
								0, 1,
								0, 0, 0, 0,
								PR_FALSE, PR_FALSE,	PR_FALSE, PR_FALSE,
								static_cast<PRUint32>(iButtonArg), 0 );	
	}
};

#endif // _WEBBROWSE_DOM_MOUSE_EVENT_H_

