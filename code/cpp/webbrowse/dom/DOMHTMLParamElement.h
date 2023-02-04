#ifndef _WEBBROWSE_DOM_HTML_PARAM_ELEMENT_H_
#define _WEBBROWSE_DOM_HTML_PARAM_ELEMENT_H_

////#include <dom/nsIDOMHTMLParamElement.h>
#include <nsIDOMHTMLParamElement.h>

#include <dom/DOMHTMLElement.h>

/**
* The nsIDOMHTMLParamElement interface is the interface to a [X]HTML
* param element.
*
* For more information on this interface please see
* http://www.w3.org/TR/DOM-Level-2-HTML/
*
* @status FROZEN
*/
class DOMHTMLParamElement : public DOMHTMLElement {
	MOZ_CONSTRUCT(DOMHTMLParamElement,DOMHTMLElement);
public: 
  	///  Get name
	std::string 				
	name() const 
												{	MOZ_IF_RETURN_STRING(GetName); }
  	///  Set name
	void 				
	name( const std::string& sName )				///< String name 
												{	MOZ_IF_SET_VOID_STRING(SetName,sName);	}
  	///  Get type
	std::string 				
	type() const 
												{	MOZ_IF_RETURN_STRING(GetType); }
  	///  Set type
	void 				
	type( const std::string& sType )				///< String type 
												{	MOZ_IF_SET_VOID_STRING(SetType,sType);	}
  	///  Get value
	std::string 				
	value() const 
												{	MOZ_IF_RETURN_STRING(GetValue); }
  	///  Set value
	void 				
	value( const std::string& sValue )				///< String value 
												{	MOZ_IF_SET_VOID_STRING(SetValue,sValue);	}
  	///  Get valueType
	std::string 				
	valueType() const 
												{	MOZ_IF_RETURN_STRING(GetValueType); }
  	///  Set valueType
	void 				
	valueType( const std::string& sValueType )		///< String valueType 
												{	MOZ_IF_SET_VOID_STRING(SetValueType,sValueType);	}
};
#endif /* _WEBBROWSE_DOM_HTML_PARAM_ELEMENT_H_ */

