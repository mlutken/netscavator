#ifndef _WEBBROWSE_DOM_HTML_BUTTON_ELEMENT_H_
#define _WEBBROWSE_DOM_HTML_BUTTON_ELEMENT_H_

////#include <dom/nsIDOMHTMLButtonElement.h>
#include <nsIDOMHTMLButtonElement.h>

#include <dom/DOMHTMLElement.h>
#include <dom/DOMHTMLFormElement.h>

/**
 * The nsIDOMHTMLButtonElement interface is the interface to a [X]HTML
 * button element.
 *
 * For more information on this interface please see
 * http://www.w3.org/TR/DOM-Level-2-HTML/
 *
 * @status FROZEN
 */
class DOMHTMLButtonElement : public DOMHTMLElement {
	MOZ_CONSTRUCT(DOMHTMLButtonElement,DOMHTMLElement);
public: 
	/// Get form element (readonly)
	boost::shared_ptr<DOMHTMLFormElement>		
	form()
												{	MOZ_IF_RETURN_MOZ(GetForm,DOMHTMLFormElement);	}
  	///  Get accessKey
	std::string 				
	accessKey() const 
												{	MOZ_IF_RETURN_STRING(GetAccessKey); }
  	///  Set accessKey
	void 				
	accessKey( const std::string& sAccessKey )			///< String accessKey 
												{	MOZ_IF_SET_VOID_STRING(SetAccessKey,sAccessKey);	}
  	///  Get disabled 
	bool 				
	disabled() const 
												{	MOZ_IF_RETURN_BOOL(GetDisabled); }
  	///  Set disabled
	void 				
	disabled( bool bDisabled )					///< Disabled true/false 
												{	MOZ_IF_SET_VOID_BOOL(SetDisabled,bDisabled);	}
  	///  Get name
	std::string 				
	name() const 
												{	MOZ_IF_RETURN_STRING(GetName); }
  	///  Set name
	void 				
	name( const std::string& sName )				///< String name 
												{	MOZ_IF_SET_VOID_STRING(SetName,sName);	}
  	///  Get tabIndex 
	boost::int32_t 				
	tabIndex() const 
												{	MOZ_IF_RETURN_INT32(GetTabIndex); }
  	///  Set tabIndex
	void 				
	tabIndex( const boost::int32_t iTabIndex )		///< Integer tabIndex 
												{	MOZ_IF_SET_VOID_INT32(SetTabIndex,iTabIndex);	}
  	///  Get type (readonly)
	std::string 				
	type() const 
												{	MOZ_IF_RETURN_STRING(GetType); }
  	///  Get value
	std::string 				
	value() const 
												{	MOZ_IF_RETURN_STRING(GetValue); }
  	///  Set value
	void 				
	value( const std::string& sValue )			///< String value 
												{	MOZ_IF_SET_VOID_STRING(SetValue,sValue);	}
};
#endif /* _WEBBROWSE_DOM_HTML_BUTTON_ELEMENT_H_ */

