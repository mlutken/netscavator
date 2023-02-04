#ifndef _WEBBROWSE_DOM_ATTR_H_
#define _WEBBROWSE_DOM_ATTR_H_

////#include <dom/nsIDOMAttr.h>
#include <nsIDOMAttr.h>

#include <dom/DOMNode.h>

class DOMElement;

/**
* The nsIDOMAttr interface represents an attribute in an "Element" object. 
* Typically the allowable values for the attribute are defined in a document 
* type definition.
* 
* For more information on this interface please see 
* http://www.w3.org/TR/DOM-Level-2-Core/
*
* @status FROZEN
*/
class DOMAttr : public DOMNode {
	MOZ_CONSTRUCT(DOMAttr,DOMNode);
public: 
  	///  Get name (readonly attribute)
	std::string 				
	name() const 
											{	MOZ_IF_RETURN_STRING(GetName); }
  	///  Get specified (readonly attribute)
	bool 				
	specified() const 
											{	MOZ_IF_RETURN_BOOL(GetSpecified); }
  	///  Get value
	std::string 				
	value() const 
											{	MOZ_IF_RETURN_STRING(GetValue); }
  	///  Set value
	void 				
	value( const std::string& sValue )		///< String value 
											{	MOZ_IF_SET_VOID_STRING(SetValue,sValue);	}
	/// Get owner element
	boost::shared_ptr<DOMElement>		
	ownerElement();
};
#endif /* _WEBBROWSE_DOM_ATTR_H_ */
