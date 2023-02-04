#ifndef _WEBBROWSE_DOM_HTML_LINK_ELEMENT_H_
#define _WEBBROWSE_DOM_HTML_LINK_ELEMENT_H_


////#include <dom/nsIDOMHTMLLinkElement.h>
#include <nsIDOMHTMLLinkElement.h>

#include <dom/DOMHTMLElement.h>

/**
 * The nsIDOMHTMLLinkElement interface is the interface to a [X]HTML
 * link element.
 *
 * For more information on this interface please see
 * http://www.w3.org/TR/DOM-Level-2-HTML/
 *
 * @status FROZEN
 */
class DOMHTMLLinkElement : public DOMHTMLElement {
	MOZ_CONSTRUCT(DOMHTMLLinkElement,DOMHTMLElement);
public: 
  	///  Get disabled 
	bool 				
	disabled() const 
												{	MOZ_IF_RETURN_BOOL(GetDisabled); }
  	///  Set disabled
	void 				
	disabled( bool bDisabled )						///< Disabled true/false 
												{	MOZ_IF_SET_VOID_BOOL(SetDisabled,bDisabled);	}
  	///  Get charset
	std::string 				
	charset() const 
												{	MOZ_IF_RETURN_STRING(GetCharset); }
  	///  Set charset
	void 				
	charset( const std::string& sCharset )			///< String charset 
												{	MOZ_IF_SET_VOID_STRING(SetCharset,sCharset);	}
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
  	///  Get media
	std::string 				
	media() const 
												{	MOZ_IF_RETURN_STRING(GetMedia); }
  	///  Set media
	void 				
	media( const std::string& sMedia )					///< String media 
												{	MOZ_IF_SET_VOID_STRING(SetMedia,sMedia);	}
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
  	///  Get target
	std::string 				
	target() const 
												{	MOZ_IF_RETURN_STRING(GetTarget); }
  	///  Set target
	std::string 				
	target( const std::string& sTarget )			///< String target 
												{	MOZ_IF_SET_VOID_STRING(SetTarget,sTarget);	}
  	///  Get type
	std::string 				
	type() const 
												{	MOZ_IF_RETURN_STRING(GetType); }
  	///  Set type
	void 				
	type( const std::string& sType )				///< String type 
												{	MOZ_IF_SET_VOID_STRING(SetType,sType);	}
};

#endif /* _WEBBROWSE_DOM_HTML_LINK_ELEMENT_H_ */

