#ifndef _WEBBROWSE_DOM_HTML_MAP_ELEMENT_H_
#define _WEBBROWSE_DOM_HTML_MAP_ELEMENT_H_

////#include <dom/nsIDOMHTMLMapElement.h>
#include <nsIDOMHTMLMapElement.h>

#include <dom/DOMHTMLElement.h>
#include <dom/DOMHTMLCollection.h>


/**
 * The nsIDOMHTMLMapElement interface is the interface to a [X]HTML
 * map element.
 *
 * For more information on this interface please see
 * http://www.w3.org/TR/DOM-Level-2-HTML/
 *
 * @status FROZEN
 */
class DOMHTMLMapElement : public DOMHTMLElement {
	MOZ_CONSTRUCT(DOMHTMLMapElement,DOMHTMLElement);
public: 
	/// Get areas (readonly)
	boost::shared_ptr<DOMHTMLCollection>		
	areas()
												{	MOZ_IF_RETURN_MOZ(GetAreas,DOMHTMLCollection);	}
  	///  Get name
	std::string 				
	name() const 
												{	MOZ_IF_RETURN_STRING(GetName); }
  	///  Set name
	void 				
	name( const std::string& sName )				///< String name 
												{	MOZ_IF_SET_VOID_STRING(SetName,sName);	}
};
#endif /* _WEBBROWSE_DOM_HTML_MAP_ELEMENT_H_ */

