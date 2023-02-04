#ifndef _WEBBROWSE_DOM_HTML_FORM_ELEMENT_H_
#define _WEBBROWSE_DOM_HTML_FORM_ELEMENT_H_

#include <boost/shared_ptr.hpp>	

////#include <dom/nsIDOMHTMLFormElement.h>
#include <nsIDOMHTMLFormElement.h>

#include <dom/DOMHTMLCollection.h>
#include <dom/DOMHTMLElement.h>
#include <utils/mozilla_if_macros.h>

/**
* The nsIDOMHTMLFormElement interface is the interface to a [X]HTML
* form element.
*
* For more information on this interface please see
* http://www.w3.org/TR/DOM-Level-2-HTML/
*
* @status FROZEN
*/
class DOMHTMLFormElement : public DOMHTMLElement {
	MOZ_CONSTRUCT(DOMHTMLFormElement,DOMHTMLElement);
public: 
	/// Get (readonly attribute) nsIDOMHTMLCollection elements
	boost::shared_ptr<DOMHTMLCollection>	
	elements() const;
  	
  	///  Get length
	boost::int32_t 				
	length() const 
												{	MOZ_IF_RETURN_INT32(GetLength); }
  	///  Get name
	std::string 				
	name() const 
												{	MOZ_IF_RETURN_STRING(GetName); }
  	///  Set name
    void
	name( const std::string& sName )				///< String name 
												{	MOZ_IF_SET_VOID_STRING(SetName,sName);	}
  	///  Get acceptCharset
	std::string 				
	acceptCharset() const 
												{	MOZ_IF_RETURN_STRING(GetAcceptCharset); }
  	///  Set acceptCharset
    void
	acceptCharset( const std::string& sCharset )	///< String acceptCharset 
												{	MOZ_IF_SET_VOID_STRING(SetAcceptCharset,sCharset);	}
  	///  Get action
	std::string 				
	action() const 
												{	MOZ_IF_RETURN_STRING(GetAction); }
  	///  Set action
    void
	action( const std::string& sAction )			///< String action 
												{	MOZ_IF_SET_VOID_STRING(SetAction,sAction);	}
  	///  Get enctype
	std::string 				
	enctype() const 
												{	MOZ_IF_RETURN_STRING(GetEnctype); }
  	///  Set enctype
    void
	enctype( const std::string& sEnctype )			///< String enctype 
												{	MOZ_IF_SET_VOID_STRING(SetEnctype,sEnctype);	}
  	///  Get method
	std::string 				
	method() const 
												{	MOZ_IF_RETURN_STRING(GetMethod); }
  	///  Set method
    void
	method( const std::string& sMethod )			///< String method 
												{	MOZ_IF_SET_VOID_STRING(SetMethod,sMethod);	}
  	///  Get target
	std::string 				
	target() const 
												{	MOZ_IF_RETURN_STRING(GetTarget); }
  	///  Set target
    void
	target( const std::string& sTarget )			///< String target 
												{	MOZ_IF_SET_VOID_STRING(SetTarget,sTarget);	}
	/// Submit form data
	void
	submit()						
												{	ifMoz()->Submit();	}
	/// Submit form data
	void
	reset()						
												{	ifMoz()->Reset();	}
};

#endif /* _WEBBROWSE_DOM_HTML_FORM_ELEMENT_H_ */

