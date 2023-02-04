#ifndef _WEBBROWSE_DOM_HTML_IMAGE_ELEMENT_H_
#define _WEBBROWSE_DOM_HTML_IMAGE_ELEMENT_H_

////#include <dom/nsIDOMHTMLImageElement.h>
#include <nsIDOMHTMLImageElement.h>

#include <dom/DOMHTMLElement.h>


/**
 * The nsIDOMHTMLImageElement interface is the interface to a [X]HTML
 * img element.
 *
 * For more information on this interface please see
 * http://www.w3.org/TR/DOM-Level-2-HTML/
 *
 * @status FROZEN
 */
class DOMHTMLImageElement : public DOMHTMLElement {
	MOZ_CONSTRUCT(DOMHTMLImageElement,DOMHTMLElement);
public: 
  	///  Get name
	std::string 				
	name() const 
												{	MOZ_IF_RETURN_STRING(GetName); }
  	///  Set name
	void 				
	name( const std::string& sName )				///< String name 
												{	MOZ_IF_SET_VOID_STRING(SetName,sName);	}
  	///  Get align
	std::string 				
	align() const 
												{	MOZ_IF_RETURN_STRING(GetAlign); }
  	///  Set align
	void 				
	align( const std::string& sAlign )				///< String align 
												{	MOZ_IF_SET_VOID_STRING(SetAlign,sAlign);	}
  	///  Get alt
	std::string 				
	alt() const 
												{	MOZ_IF_RETURN_STRING(GetAlt); }
  	///  Set alt
	void 				
	alt( const std::string& sAlt )					///< String alt 
												{	MOZ_IF_SET_VOID_STRING(SetAlt,sAlt);	}
  	///  Get border
	std::string 				
	border() const 
												{	MOZ_IF_RETURN_STRING(GetBorder); }
  	///  Set border
	void 				
	border( const std::string& sBorder )			///< String border 
												{	MOZ_IF_SET_VOID_STRING(SetBorder,sBorder);	}
  	///  Get height 
	boost::int32_t 				
	height() const 
												{	MOZ_IF_RETURN_INT32(GetHeight); }
  	///  Set height
	void 				
	height( const boost::int32_t iHeight )			///< Integer height 
												{	MOZ_IF_SET_VOID_INT32(SetHeight,iHeight);	}
  	///  Get hspace 
	boost::int32_t 				
	hspace() const 
												{	MOZ_IF_RETURN_INT32(GetHspace); }
  	///  Set hspace
	void 				
	hspace( const boost::int32_t iHspace )			///< Integer hspace 
												{	MOZ_IF_SET_VOID_INT32(SetHspace,iHspace);	}
  	///  Get isMap 
	bool 				
	isMap() const 
												{	MOZ_IF_RETURN_BOOL(GetIsMap); }
  	///  Set isMap
	void 				
	isMap( bool bIsMap )							///< IsMap true/false 
												{	MOZ_IF_SET_VOID_BOOL(SetIsMap,bIsMap);	}
  	///  Get longDesc
	std::string 				
	longDesc() const 
												{	MOZ_IF_RETURN_STRING(GetLongDesc); }
  	///  Set longDesc
	void 				
	longDesc( const std::string& sLongDesc )		///< String longDesc 
												{	MOZ_IF_SET_VOID_STRING(SetLongDesc,sLongDesc);	}
  	///  Get src
	std::string 				
	src() const 
												{	MOZ_IF_RETURN_STRING(GetSrc); }
  	///  Set src
	void 				
	src( const std::string& sSrc )					///< String src 
												{	MOZ_IF_SET_VOID_STRING(SetSrc,sSrc);	}
  	///  Get useMap
	std::string 				
	useMap() const 
												{	MOZ_IF_RETURN_STRING(GetUseMap); }
  	///  Set useMap
	void 				
	useMap( const std::string& sUseMap )			///< String useMap 
												{	MOZ_IF_SET_VOID_STRING(SetUseMap,sUseMap);	}
  	///  Get vspace 
	boost::int32_t 				
	vspace() const 
												{	MOZ_IF_RETURN_INT32(GetVspace); }
  	///  Set vspace
	void 				
	vspace( const boost::int32_t iVspace )			///< Integer vspace 
												{	MOZ_IF_SET_VOID_INT32(SetVspace,iVspace);	}
  	///  Get width 
	boost::int32_t 				
	width() const 
												{	MOZ_IF_RETURN_INT32(GetWidth); }
  	///  Set width
	void 				
	width( const boost::int32_t iWidth )			///< Integer width 
												{	MOZ_IF_SET_VOID_INT32(SetWidth,iWidth);	}
};


#endif /* _WEBBROWSE_DOM_HTML_IMAGE_ELEMENT_H_ */

