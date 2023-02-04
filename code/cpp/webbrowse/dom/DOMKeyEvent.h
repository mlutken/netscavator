#ifndef _WEBBROWSE_DOM_KEY_EVENT_H_
#define _WEBBROWSE_DOM_KEY_EVENT_H_


#include <nsIDOMKeyEvent.h>
#include <dom/DOMUIEvent.h>

class DOMKeyEvent : public DOMUIEvent
{
	MOZ_CONSTRUCT(DOMKeyEvent,DOMUIEvent);
public:
	enum { DOM_VK_CANCEL = nsIDOMKeyEvent::DOM_VK_CANCEL };

	enum { DOM_VK_HELP = nsIDOMKeyEvent::DOM_VK_HELP };

	enum { DOM_VK_BACK_SPACE = nsIDOMKeyEvent::DOM_VK_BACK_SPACE };

	enum { DOM_VK_TAB = nsIDOMKeyEvent::DOM_VK_TAB };

	enum { DOM_VK_CLEAR = nsIDOMKeyEvent::DOM_VK_CLEAR };

	enum { DOM_VK_RETURN = nsIDOMKeyEvent::DOM_VK_RETURN };

	enum { DOM_VK_ENTER = nsIDOMKeyEvent::DOM_VK_ENTER };

	enum { DOM_VK_SHIFT = nsIDOMKeyEvent::DOM_VK_SHIFT };

	enum { DOM_VK_CONTROL = nsIDOMKeyEvent::DOM_VK_CONTROL };

	enum { DOM_VK_ALT = nsIDOMKeyEvent::DOM_VK_ALT };

	enum { DOM_VK_PAUSE = nsIDOMKeyEvent::DOM_VK_PAUSE };

	enum { DOM_VK_CAPS_LOCK = nsIDOMKeyEvent::DOM_VK_CAPS_LOCK };

	enum { DOM_VK_ESCAPE = nsIDOMKeyEvent::DOM_VK_ESCAPE };

	enum { DOM_VK_SPACE = nsIDOMKeyEvent::DOM_VK_SPACE };

	enum { DOM_VK_PAGE_UP = nsIDOMKeyEvent::DOM_VK_PAGE_UP };

	enum { DOM_VK_PAGE_DOWN = nsIDOMKeyEvent::DOM_VK_PAGE_DOWN };

	enum { DOM_VK_END = nsIDOMKeyEvent::DOM_VK_END };

	enum { DOM_VK_HOME = nsIDOMKeyEvent::DOM_VK_HOME };

	enum { DOM_VK_LEFT = nsIDOMKeyEvent::DOM_VK_LEFT };

	enum { DOM_VK_UP = nsIDOMKeyEvent::DOM_VK_UP };

	enum { DOM_VK_RIGHT = nsIDOMKeyEvent::DOM_VK_RIGHT };

	enum { DOM_VK_DOWN = nsIDOMKeyEvent::DOM_VK_DOWN };

	enum { DOM_VK_PRINTSCREEN = nsIDOMKeyEvent::DOM_VK_PRINTSCREEN };

	enum { DOM_VK_INSERT = nsIDOMKeyEvent::DOM_VK_INSERT };

	enum { DOM_VK_DELETE = nsIDOMKeyEvent::DOM_VK_DELETE };

	enum { DOM_VK_0 = nsIDOMKeyEvent::DOM_VK_0 };

	enum { DOM_VK_1 = nsIDOMKeyEvent::DOM_VK_1 };

	enum { DOM_VK_2 = nsIDOMKeyEvent::DOM_VK_2 };

	enum { DOM_VK_3 = nsIDOMKeyEvent::DOM_VK_3 };

	enum { DOM_VK_4 = nsIDOMKeyEvent::DOM_VK_4 };

	enum { DOM_VK_5 = nsIDOMKeyEvent::DOM_VK_5 };

	enum { DOM_VK_6 = nsIDOMKeyEvent::DOM_VK_6 };

	enum { DOM_VK_7 = nsIDOMKeyEvent::DOM_VK_7 };

	enum { DOM_VK_8 = nsIDOMKeyEvent::DOM_VK_8 };

	enum { DOM_VK_9 = nsIDOMKeyEvent::DOM_VK_9 };

	enum { DOM_VK_SEMICOLON = nsIDOMKeyEvent::DOM_VK_SEMICOLON };

	enum { DOM_VK_EQUALS = nsIDOMKeyEvent::DOM_VK_EQUALS };

	enum { DOM_VK_A = nsIDOMKeyEvent::DOM_VK_A };

	enum { DOM_VK_B = nsIDOMKeyEvent::DOM_VK_B };

	enum { DOM_VK_C = nsIDOMKeyEvent::DOM_VK_C };

	enum { DOM_VK_D = nsIDOMKeyEvent::DOM_VK_D };

	enum { DOM_VK_E = nsIDOMKeyEvent::DOM_VK_E };

	enum { DOM_VK_F = nsIDOMKeyEvent::DOM_VK_F };

	enum { DOM_VK_G = nsIDOMKeyEvent::DOM_VK_G };

	enum { DOM_VK_H = nsIDOMKeyEvent::DOM_VK_H };

	enum { DOM_VK_I = nsIDOMKeyEvent::DOM_VK_I };

	enum { DOM_VK_J = nsIDOMKeyEvent::DOM_VK_J };

	enum { DOM_VK_K = nsIDOMKeyEvent::DOM_VK_K };

	enum { DOM_VK_L = nsIDOMKeyEvent::DOM_VK_L };

	enum { DOM_VK_M = nsIDOMKeyEvent::DOM_VK_M };

	enum { DOM_VK_N = nsIDOMKeyEvent::DOM_VK_N };

	enum { DOM_VK_O = nsIDOMKeyEvent::DOM_VK_O };

	enum { DOM_VK_P = nsIDOMKeyEvent::DOM_VK_P };

	enum { DOM_VK_Q = nsIDOMKeyEvent::DOM_VK_Q };

	enum { DOM_VK_R = nsIDOMKeyEvent::DOM_VK_R };

	enum { DOM_VK_S = nsIDOMKeyEvent::DOM_VK_S };

	enum { DOM_VK_T = nsIDOMKeyEvent::DOM_VK_T };

	enum { DOM_VK_U = nsIDOMKeyEvent::DOM_VK_U };

	enum { DOM_VK_V = nsIDOMKeyEvent::DOM_VK_V };

	enum { DOM_VK_W = nsIDOMKeyEvent::DOM_VK_W };

	enum { DOM_VK_X = nsIDOMKeyEvent::DOM_VK_X };

	enum { DOM_VK_Y = nsIDOMKeyEvent::DOM_VK_Y };

	enum { DOM_VK_Z = nsIDOMKeyEvent::DOM_VK_Z };

	enum { DOM_VK_CONTEXT_MENU = nsIDOMKeyEvent::DOM_VK_CONTEXT_MENU };

	enum { DOM_VK_NUMPAD0 = nsIDOMKeyEvent::DOM_VK_NUMPAD0 };

	enum { DOM_VK_NUMPAD1 = nsIDOMKeyEvent::DOM_VK_NUMPAD1 };

	enum { DOM_VK_NUMPAD2 = nsIDOMKeyEvent::DOM_VK_NUMPAD2 };

	enum { DOM_VK_NUMPAD3 = nsIDOMKeyEvent::DOM_VK_NUMPAD3 };

	enum { DOM_VK_NUMPAD4 = nsIDOMKeyEvent::DOM_VK_NUMPAD4 };

	enum { DOM_VK_NUMPAD5 = nsIDOMKeyEvent::DOM_VK_NUMPAD5 };

	enum { DOM_VK_NUMPAD6 = nsIDOMKeyEvent::DOM_VK_NUMPAD6 };

	enum { DOM_VK_NUMPAD7 = nsIDOMKeyEvent::DOM_VK_NUMPAD7 };

	enum { DOM_VK_NUMPAD8 = nsIDOMKeyEvent::DOM_VK_NUMPAD8 };

	enum { DOM_VK_NUMPAD9 = nsIDOMKeyEvent::DOM_VK_NUMPAD9 };

	enum { DOM_VK_MULTIPLY = nsIDOMKeyEvent::DOM_VK_MULTIPLY };

	enum { DOM_VK_ADD = nsIDOMKeyEvent::DOM_VK_ADD };

	enum { DOM_VK_SEPARATOR = nsIDOMKeyEvent::DOM_VK_SEPARATOR };

	enum { DOM_VK_SUBTRACT = nsIDOMKeyEvent::DOM_VK_SUBTRACT };

	enum { DOM_VK_DECIMAL = nsIDOMKeyEvent::DOM_VK_DECIMAL };

	enum { DOM_VK_DIVIDE = nsIDOMKeyEvent::DOM_VK_DIVIDE };

	enum { DOM_VK_F1 = nsIDOMKeyEvent::DOM_VK_F1 };

	enum { DOM_VK_F2 = nsIDOMKeyEvent::DOM_VK_F2 };

	enum { DOM_VK_F3 = nsIDOMKeyEvent::DOM_VK_F3 };

	enum { DOM_VK_F4 = nsIDOMKeyEvent::DOM_VK_F4 };

	enum { DOM_VK_F5 = nsIDOMKeyEvent::DOM_VK_F5 };

	enum { DOM_VK_F6 = nsIDOMKeyEvent::DOM_VK_F6 };

	enum { DOM_VK_F7 = nsIDOMKeyEvent::DOM_VK_F7 };

	enum { DOM_VK_F8 = nsIDOMKeyEvent::DOM_VK_F8 };

	enum { DOM_VK_F9 = nsIDOMKeyEvent::DOM_VK_F9 };

	enum { DOM_VK_F10 = nsIDOMKeyEvent::DOM_VK_F10 };

	enum { DOM_VK_F11 = nsIDOMKeyEvent::DOM_VK_F11 };

	enum { DOM_VK_F12 = nsIDOMKeyEvent::DOM_VK_F12 };

	enum { DOM_VK_F13 = nsIDOMKeyEvent::DOM_VK_F13 };

	enum { DOM_VK_F14 = nsIDOMKeyEvent::DOM_VK_F14 };

	enum { DOM_VK_F15 = nsIDOMKeyEvent::DOM_VK_F15 };

	enum { DOM_VK_F16 = nsIDOMKeyEvent::DOM_VK_F16 };

	enum { DOM_VK_F17 = nsIDOMKeyEvent::DOM_VK_F17 };

	enum { DOM_VK_F18 = nsIDOMKeyEvent::DOM_VK_F18 };

	enum { DOM_VK_F19 = nsIDOMKeyEvent::DOM_VK_F19 };

	enum { DOM_VK_F20 = nsIDOMKeyEvent::DOM_VK_F20 };

	enum { DOM_VK_F21 = nsIDOMKeyEvent::DOM_VK_F21 };

	enum { DOM_VK_F22 = nsIDOMKeyEvent::DOM_VK_F22 };

	enum { DOM_VK_F23 = nsIDOMKeyEvent::DOM_VK_F23 };

	enum { DOM_VK_F24 = nsIDOMKeyEvent::DOM_VK_F24 };

	enum { DOM_VK_NUM_LOCK = nsIDOMKeyEvent::DOM_VK_NUM_LOCK };

	enum { DOM_VK_SCROLL_LOCK = nsIDOMKeyEvent::DOM_VK_SCROLL_LOCK };

	enum { DOM_VK_COMMA = nsIDOMKeyEvent::DOM_VK_COMMA };

	enum { DOM_VK_PERIOD = nsIDOMKeyEvent::DOM_VK_PERIOD };

	enum { DOM_VK_SLASH = nsIDOMKeyEvent::DOM_VK_SLASH };

	enum { DOM_VK_BACK_QUOTE = nsIDOMKeyEvent::DOM_VK_BACK_QUOTE };

	enum { DOM_VK_OPEN_BRACKET = nsIDOMKeyEvent::DOM_VK_OPEN_BRACKET };

	enum { DOM_VK_BACK_SLASH = nsIDOMKeyEvent::DOM_VK_BACK_SLASH };

	enum { DOM_VK_CLOSE_BRACKET = nsIDOMKeyEvent::DOM_VK_CLOSE_BRACKET };

	enum { DOM_VK_QUOTE = nsIDOMKeyEvent::DOM_VK_QUOTE };

	enum { DOM_VK_META = nsIDOMKeyEvent::DOM_VK_META };

	boost::uint32_t 
	charCode () const
										{	MOZ_IF_RETURN_UINT32(GetCharCode); 				}
	boost::uint32_t 
	keyCode () const
										{	MOZ_IF_RETURN_UINT32(GetKeyCode); 				}
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

	void initKeyEvent ( std::string sTypeArg, bool bCanBubbleArg, bool bCancelableArg, 
                        boost::shared_ptr<DOMWindow> pViewArg, bool bCtrlKeyArg, bool bAltKeyArg,
						bool bShiftKeyArg, bool bMetaKeyArg, 
						boost::uint32_t iKeyCodeArg, boost::uint32_t iCharCodeArg )
	{																																	
		ifMoz()->InitKeyEvent( 	toAStringUTF16(sTypeArg), static_cast<PRBool>(bCanBubbleArg), static_cast<PRBool>(bCancelableArg), 
								pViewArg->ifMoz(), static_cast<PRBool>(bCtrlKeyArg), static_cast<PRBool>(bAltKeyArg),
								static_cast<PRBool>(bShiftKeyArg), static_cast<PRBool>(bMetaKeyArg),
								static_cast<PRUint32>(iKeyCodeArg), static_cast<PRUint32>(iCharCodeArg) );	
	}

};

#endif //_WEBBROWSE_DOM_KEY_EVENT_H_

