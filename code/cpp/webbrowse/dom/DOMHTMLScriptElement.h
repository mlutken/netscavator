#ifndef _WEBBROWSE_DOM_HTML_SCRIPT_ELEMENT_H_
#define _WEBBROWSE_DOM_HTML_SCRIPT_ELEMENT_H_

////#include <dom/nsIDOMHTMLScriptElement.h>
#include <nsIDOMHTMLScriptElement.h>

#include <dom/DOMHTMLElement.h>


/**
 * The nsIDOMHTMLScriptElement interface is the interface to a [X]HTML
 * script element.
 *
 * For more information on this interface please see
 * http://www.w3.org/TR/DOM-Level-2-HTML/
 *
 * @status FROZEN
 */
class DOMHTMLScriptElement : public DOMHTMLElement {
	MOZ_CONSTRUCT(DOMHTMLScriptElement,DOMHTMLElement);
public: 
  	///  Get text
	std::string 				
	text() const 
												{	MOZ_IF_RETURN_STRING(GetText); }
  	///  Set text
	void 				
	text( const std::string& sText )			///< String text 
												{	MOZ_IF_SET_VOID_STRING(SetText,sText);	}
  	///  Get htmlFor
	std::string 				
	htmlFor() const 
												{	MOZ_IF_RETURN_STRING(GetHtmlFor); }
  	///  Set htmlFor
	void 				
	htmlFor( const std::string& sHtmlFor )			///< String htmlFor 
												{	MOZ_IF_SET_VOID_STRING(SetHtmlFor,sHtmlFor);	}
  	///  Get event
	std::string 				
	event() const 
												{	MOZ_IF_RETURN_STRING(GetEvent); }
  	///  Set event
	void 				
	event( const std::string& sEvent )			///< String event 
												{	MOZ_IF_SET_VOID_STRING(SetEvent,sEvent);	}
  	///  Get charset
	std::string 				
	charset() const 
												{	MOZ_IF_RETURN_STRING(GetCharset); }
  	///  Set charset
	void 				
	charset( const std::string& sCharset )		///< String charset 
												{	MOZ_IF_SET_VOID_STRING(SetCharset,sCharset);	}
  	///  Get defer 
	bool 				
	defer() const 
												{	MOZ_IF_RETURN_BOOL(GetDefer); }
  	///  Set defer
	void 				
	defer( bool bDefer )						///< Defer true/false 
												{	MOZ_IF_SET_VOID_BOOL(SetDefer,bDefer);	}
  	///  Get src
	std::string 				
	src() const 
												{	MOZ_IF_RETURN_STRING(GetSrc); }
  	///  Set src
	void 				
	src( const std::string& sSrc )					///< String src 
												{	MOZ_IF_SET_VOID_STRING(SetSrc,sSrc);	}
  	///  Get type
	std::string 				
	type() const 
												{	MOZ_IF_RETURN_STRING(GetType); }
  	///  Set type
	void 				
	type( const std::string& sType )				///< String type 
												{	MOZ_IF_SET_VOID_STRING(SetType,sType);	}
};

#endif /* _WEBBROWSE_DOM_HTML_SCRIPT_ELEMENT_H_ */

