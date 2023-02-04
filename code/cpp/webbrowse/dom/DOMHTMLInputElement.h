#ifndef _WEBBROWSE_DOM_HTML_INPUT_ELEMENT_H_
#define _WEBBROWSE_DOM_HTML_INPUT_ELEMENT_H_

////#include <dom/nsIDOMHTMLInputElement.h>
#include <nsIDOMHTMLInputElement.h>

#include <dom/DOMHTMLElement.h>
#include <dom/DOMHTMLFormElement.h>

/**
 * The nsIDOMHTMLInputElement interface is the interface to a [X]HTML
 * input element.
 *
 * For more information on this interface please see
 * http://www.w3.org/TR/DOM-Level-2-HTML/
 *
 * @status FROZEN
 */
class DOMHTMLInputElement : public DOMHTMLElement {
	MOZ_CONSTRUCT(DOMHTMLInputElement,DOMHTMLElement);
public: 
  	///  Get defaultValue
	std::string 				
	defaultValue() const 
												{	MOZ_IF_RETURN_STRING(GetDefaultValue); }
  	///  Set defaultValue
	void 				
	defaultValue( const std::string& sDefaultValue )	///< String defaultValue 
												{	MOZ_IF_SET_VOID_STRING(SetDefaultValue,sDefaultValue);	}
  	///  Get defaultChecked 
	bool 				
	defaultChecked() const 
												{	MOZ_IF_RETURN_BOOL(GetDefaultChecked); }
  	///  Set defaultChecked
	void 				
	defaultChecked( bool bDefaultChecked )			///< DefaultChecked true/false 
												{	MOZ_IF_SET_VOID_BOOL(SetDefaultChecked,bDefaultChecked);	}
	/// Get form element (readonly)
	boost::shared_ptr<DOMHTMLFormElement>		
	form()
												{	MOZ_IF_RETURN_MOZ(GetForm,DOMHTMLFormElement);	}
  	///  Get accept
	std::string 				
	accept() const 
												{	MOZ_IF_RETURN_STRING(GetAccept); }
  	///  Set accept
	void 				
	accept( const std::string& sAccept )			///< String accept 
												{	MOZ_IF_SET_VOID_STRING(SetAccept,sAccept);	}
  	///  Get accessKey
	std::string 				
	accessKey() const 
												{	MOZ_IF_RETURN_STRING(GetAccessKey); }
  	///  Set accessKey
	void 				
	accessKey( const std::string& sAccessKey )			///< String accessKey 
												{	MOZ_IF_SET_VOID_STRING(SetAccessKey,sAccessKey);	}
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
  	///  Get checked 
	bool 				
	checked() const 
												{	MOZ_IF_RETURN_BOOL(GetChecked); }
  	///  Set checked
	void 				
	checked( bool bChecked )						///< Checked true/false 
												{	MOZ_IF_SET_VOID_BOOL(SetChecked,bChecked);	}
  	///  Get disabled 
	bool 				
	disabled() const 
												{	MOZ_IF_RETURN_BOOL(GetDisabled); }
  	///  Set disabled
	void 				
	disabled( bool bDisabled )						///< Disabled true/false 
												{	MOZ_IF_SET_VOID_BOOL(SetDisabled,bDisabled);	}
  	///  Get maxLength 
	boost::int32_t 				
	maxLength() const 
												{	MOZ_IF_RETURN_INT32(GetMaxLength); }
  	///  Set maxLength
	void 				
	maxLength( const boost::int32_t iMaxLength )	///< Integer maxLength 
												{	MOZ_IF_SET_VOID_INT32(SetMaxLength,iMaxLength);	}
  	///  Get name
	std::string 				
	name() const 
												{	MOZ_IF_RETURN_STRING(GetName); }
  	///  Set name
	void 				
	name( const std::string& sName )				///< String name 
												{	MOZ_IF_SET_VOID_STRING(SetName,sName);	}
  	///  Get readOnly 
	bool 				
	readOnly() const 
												{	MOZ_IF_RETURN_BOOL(GetReadOnly); }
  	///  Set readOnly
	void 				
	readOnly( bool bReadOnly )					///< ReadOnly true/false 
												{	MOZ_IF_SET_VOID_BOOL(SetReadOnly,bReadOnly);	}
  	///  Get size 
	boost::uint32_t 				
	size() const 
												{	MOZ_IF_RETURN_UINT32(GetSize); }
  	///  Set size
	void 				
	size( const boost::uint32_t iSize )				///< Integer size 
												{	MOZ_IF_SET_VOID_UINT32(SetSize,iSize);	}
  	///  Get src
	std::string 				
	src() const 
												{	MOZ_IF_RETURN_STRING(GetSrc); }
  	///  Set src
	void 				
	src( const std::string& sSrc )					///< String src 
												{	MOZ_IF_SET_VOID_STRING(SetSrc,sSrc);	}
  	///  Get tabIndex 
	boost::int32_t 				
	tabIndex() const 
												{	MOZ_IF_RETURN_INT32(GetTabIndex); }
  	///  Set tabIndex
	void 				
	tabIndex( const boost::int32_t iTabIndex )		///< Integer tabIndex 
												{	MOZ_IF_SET_VOID_INT32(SetTabIndex,iTabIndex);	}
  	///  Get type
	std::string 				
	type() const 
												{	MOZ_IF_RETURN_STRING(GetType); }
  	///  Set type
	void 				
	type( const std::string& sType )				///< String type 
												{	MOZ_IF_SET_VOID_STRING(SetType,sType);	}
  	///  Get useMap
	std::string 				
	useMap() const 
												{	MOZ_IF_RETURN_STRING(GetUseMap); }
  	///  Set useMap
	void 				
	useMap( const std::string& sUseMap )			///< String useMap 
												{	MOZ_IF_SET_VOID_STRING(SetUseMap,sUseMap);	}
  	///  Get value
	std::string 				
	value() const 
												{	MOZ_IF_RETURN_STRING(GetValue); }
  	///  Set value
	void 				
	value( const std::string& sValue )				///< String value 
												{	MOZ_IF_SET_VOID_STRING(SetValue,sValue);	}
	///  Blur
	void 				
	blur()			
												{	ifMoz()->Blur();	}
	///  Focus
	void 				
	focus()			
												{	ifMoz()->Focus();	}
	///  Select
	void 				
	select()			
												{	ifMoz()->Select();	}
	///  Click
	void 				
	click()			
												{	ifMoz()->Click();	}
};

#endif /* _WEBBROWSE_DOM_HTML_INPUT_ELEMENT_H_ */

