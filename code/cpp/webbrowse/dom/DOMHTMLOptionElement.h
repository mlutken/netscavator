#ifndef _WEBBROWSE_DOM_HTML_OPTION_ELEMENT_H_
#define _WEBBROWSE_DOM_HTML_OPTION_ELEMENT_H_

////#include <dom/nsIDOMHTMLOptionElement.h>
#include <nsIDOMHTMLOptionElement.h>

#include <dom/DOMHTMLElement.h>
#include <dom/DOMHTMLFormElement.h>

/**
 * The nsIDOMHTMLOptionElement interface is the interface to a [X]HTML
 * option element.
 *
 * For more information on this interface please see
 * http://www.w3.org/TR/DOM-Level-2-HTML/
 *
 * @status FROZEN
 */
class DOMHTMLOptionElement : public DOMHTMLElement {
	MOZ_CONSTRUCT(DOMHTMLOptionElement,DOMHTMLElement);
public: 
	/// Get form element (readonly)
	boost::shared_ptr<DOMHTMLFormElement>		
	form()
												{	MOZ_IF_RETURN_MOZ(GetForm,DOMHTMLFormElement);	}
  	///  Get defaultSelected 
	bool 				
	defaultSelected() const 
												{	MOZ_IF_RETURN_BOOL(GetDefaultSelected); }
  	///  Set defaultSelected
	void 				
	defaultSelected( bool bDefaultSelected )					///< DefaultSelected true/false 
												{	MOZ_IF_SET_VOID_BOOL(SetDefaultSelected,bDefaultSelected);	}
  	///  Get text (readonly)
	std::string 				
	text() const 
												{	MOZ_IF_RETURN_STRING(GetText); }
  	///  Get index (readonly)
	boost::int32_t 				
	index() const 
												{	MOZ_IF_RETURN_INT32(GetIndex); }
  	///  Get disabled 
	bool 				
	disabled() const 
												{	MOZ_IF_RETURN_BOOL(GetDisabled); }
  	///  Set disabled
	void 				
	disabled( bool bDisabled )					///< Disabled true/false 
												{	MOZ_IF_SET_VOID_BOOL(SetDisabled,bDisabled);	}
  	///  Get label
	std::string 				
	label() const 
												{	MOZ_IF_RETURN_STRING(GetLabel); }
  	///  Set label
	void 				
	label( const std::string& sLabel )			///< String label 
												{	MOZ_IF_SET_VOID_STRING(SetLabel,sLabel);	}
  	///  Get selected 
	bool 				
	selected() const 
												{	MOZ_IF_RETURN_BOOL(GetSelected); }
  	///  Set selected
	void 				
	selected( bool bSelected )					///< Selected true/false 
												{	MOZ_IF_SET_VOID_BOOL(SetSelected,bSelected);	}
  	///  Get value
	std::string 				
	value() const 
												{	MOZ_IF_RETURN_STRING(GetValue); }
  	///  Set value
	void 				
	value( const std::string& sValue )			///< String value 
												{	MOZ_IF_SET_VOID_STRING(SetValue,sValue);	}
};

#endif /* _WEBBROWSE_DOM_HTML_OPTION_ELEMENT_H_ */

