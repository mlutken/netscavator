#ifndef _WEBBROWSE_DOM_HTML_ANCHOR_ELEMENT_H_
#define _WEBBROWSE_DOM_HTML_ANCHOR_ELEMENT_H_

////#include <dom/nsIDOMHTMLAnchorElement.h>
#include <nsIDOMHTMLAnchorElement.h>

#include <dom/DOMHTMLElement.h>


/**
 * The nsIDOMHTMLAnchorElement interface is the interface to a [X]HTML
 * a element.
 *
 * For more information on this interface please see
 * http://www.w3.org/TR/DOM-Level-2-HTML/
 *
 * @status FROZEN
 */
class DOMHTMLAnchorElement : public DOMHTMLElement {
	MOZ_CONSTRUCT(DOMHTMLAnchorElement,DOMHTMLElement);
public: 
  	///  Get accessKey
	std::string 				
	accessKey() const 
												{	MOZ_IF_RETURN_STRING(GetAccessKey); }
  	///  Set accessKey
	void 				
	accessKey( const std::string& sAccessKey )			///< String accessKey 
												{	MOZ_IF_SET_VOID_STRING(SetAccessKey,sAccessKey);	}
  	///  Get charset
	std::string 				
	charset() const 
												{	MOZ_IF_RETURN_STRING(GetCharset); }
  	///  Set charset
	void 				
	charset( const std::string& sCharset )			///< String charset 
												{	MOZ_IF_SET_VOID_STRING(SetCharset,sCharset);	}
  	///  Get coords
	std::string 				
	coords() const 
												{	MOZ_IF_RETURN_STRING(GetCoords); }
  	///  Set coords
	void 				
	coords( const std::string& sCoords )			///< String coords 
												{	MOZ_IF_SET_VOID_STRING(SetCoords,sCoords);	}
  	///  Get href
	std::string 				
	href() const 
												{	MOZ_IF_RETURN_STRING(GetHref); }
  	///  Set href
	void 				
	href( const std::string& sHref )				///< String href 
												{	MOZ_IF_SET_VOID_STRING(SetHref,sHref);	}
  	///  Get hreflang
	std::string 				
	hreflang() const 
												{	MOZ_IF_RETURN_STRING(GetHreflang); }
  	///  Set hreflang
	void 				
	hreflang( const std::string& sHreflang )		///< String hreflang 
												{	MOZ_IF_SET_VOID_STRING(SetHreflang,sHreflang);	}
  	///  Get name
	std::string 				
	name() const 
												{	MOZ_IF_RETURN_STRING(GetName); }
  	///  Set name
	void 				
	name( const std::string& sName )				///< String name 
												{	MOZ_IF_SET_VOID_STRING(SetName,sName);	}
  	///  Get rel
	std::string 				
	rel() const 
												{	MOZ_IF_RETURN_STRING(GetRel); }
  	///  Set rel
	void 				
	rel( const std::string& sRel )					///< String rel 
												{	MOZ_IF_SET_VOID_STRING(SetRel,sRel);	}
  	///  Get rev
	std::string 				
	rev() const 
												{	MOZ_IF_RETURN_STRING(GetRev); }
  	///  Set rev
	void 				
	rev( const std::string& sRev )					///< String rev 
												{	MOZ_IF_SET_VOID_STRING(SetRev,sRev);	}
  	///  Get shape
	std::string 				
	shape() const 
												{	MOZ_IF_RETURN_STRING(GetShape); }
  	///  Set shape
	void 				
	shape( const std::string& sShape )				///< String shape 
												{	MOZ_IF_SET_VOID_STRING(SetShape,sShape);	}
  	///  Get tabIndex 
	boost::int32_t 				
	tabIndex() const 
												{	MOZ_IF_RETURN_INT32(GetTabIndex); }
  	///  Set tabIndex
	void 				
	tabIndex( const boost::int32_t iTabIndex )		///< Integer tabIndex 
												{	MOZ_IF_SET_VOID_INT32(SetTabIndex,iTabIndex);	}
  	///  Get target
	std::string 				
	target() const 
												{	MOZ_IF_RETURN_STRING(GetTarget); }
  	///  Set target
	void 				
	target( const std::string& sTarget )			///< String target 
												{	MOZ_IF_SET_VOID_STRING(SetTarget,sTarget);	}
  	///  Get type
	std::string 				
	type() const 
												{	MOZ_IF_RETURN_STRING(GetTitle); }
  	///  Set type
	void 				
	type( const std::string& sTitle )				///< String type 
												{	MOZ_IF_SET_VOID_STRING(SetTitle,sTitle);	}
	///  Blur
	void 				
	blur()			
												{	ifMoz()->Blur();	}
	///  Focus
	void 				
	focus()			
												{	ifMoz()->Focus();	}
};

#endif /* _WEBBROWSE_DOM_HTML_ANCHOR_ELEMENT_H_ */

