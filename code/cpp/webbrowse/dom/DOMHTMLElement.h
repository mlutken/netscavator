#ifndef _WEBBROWSE_DOM_HTML_ELEMENT_H_
#define _WEBBROWSE_DOM_HTML_ELEMENT_H_

#include <boost/shared_ptr.hpp>	

////#include <dom/nsIDOMHTMLElement.h>
#include <nsIDOMHTMLElement.h>

#include <dom/DOMElement.h>
#include <utils/mozilla_if_macros.h>

/**
* The nsIDOMHTMLElement interface is the primary [X]HTML element
* interface. It represents a single [X]HTML element in the document
* tree.
*
* For more information on this interface please see
* http://www.w3.org/TR/DOM-Level-2-HTML/
*
* @status FROZEN
*/
class DOMHTMLElement : public DOMElement {
	MOZ_CONSTRUCT(DOMHTMLElement,DOMElement);
public: 
  	///  Get id
	std::string 				
	id() const 
												{	MOZ_IF_RETURN_STRING(GetId); }
  	///  Set id
	void 				
	id( const std::string& sID )				///< String id 
												{	MOZ_IF_SET_VOID_STRING(SetId,sID);	}
  	///  Get title
	std::string 				
	title() const 
												{	MOZ_IF_RETURN_STRING(GetTitle); }
  	///  Set title
	void 				
	title( const std::string& sTitle )			///< String title 
												{	MOZ_IF_SET_VOID_STRING(SetTitle,sTitle);	}
  	///  Get lang
	std::string 				
	lang() const 
												{	MOZ_IF_RETURN_STRING(GetLang); }
  	///  Set lang
	void 				
	lang( const std::string& sLang )			///< String lang 
												{	MOZ_IF_SET_VOID_STRING(SetLang,sLang);	}
  	///  Get dir
	std::string 				
	dir() const 
												{	MOZ_IF_RETURN_STRING(GetDir); }
  	///  Set dir
	void 				
	dir( const std::string& sDir )				///< String dir 
												{	MOZ_IF_SET_VOID_STRING(SetDir,sDir);	}
  	///  Get className
	std::string 				
	className() const 
												{	MOZ_IF_RETURN_STRING(GetClassName); }
  	///  Set className
	void 				
	className( const std::string& sClassName )	///< String className 
												{	MOZ_IF_SET_VOID_STRING(SetClassName,sClassName);	}
};

#endif /* _WEBBROWSE_DOM_HTML_ELEMENT_H_ */

