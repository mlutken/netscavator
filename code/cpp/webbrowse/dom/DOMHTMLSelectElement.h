#ifndef _WEBBROWSE_DOM_HTML_SELECT_ELEMENT_H_
#define _WEBBROWSE_DOM_HTML_SELECT_ELEMENT_H_

//// #include <dom/nsIDOMHTMLSelectElement.h>
#include <nsIDOMHTMLSelectElement.h>

#include <dom/DOMHTMLElement.h>
#include <dom/DOMHTMLFormElement.h>

class DOMHTMLOptionsCollection;


/**
 * The nsIDOMHTMLSelectElement interface is the interface to a [X]HTML
 * select element.
 *
 * For more information on this interface please see
 * http://www.w3.org/TR/DOM-Level-2-HTML/
 *
 * @status FROZEN
 */
class DOMHTMLSelectElement : public DOMHTMLElement {
	MOZ_CONSTRUCT(DOMHTMLSelectElement,DOMHTMLElement);
public: 
  	///  Get type (readonly)
	std::string 				
	type() const 
												{	MOZ_IF_RETURN_STRING(GetType); }
  	///  Get selectedIndex 
	boost::int32_t 				
	selectedIndex() const 
												{	MOZ_IF_RETURN_INT32(GetSelectedIndex); }
  	///  Set selectedIndex
	void 				
	selectedIndex( const boost::int32_t iSelectedIndex )			///< Integer selectedIndex 
												{	MOZ_IF_SET_VOID_INT32(SetSelectedIndex,iSelectedIndex);	}
  	///  Get value
	std::string 				
	value() const 
												{	MOZ_IF_RETURN_STRING(GetValue); }
  	///  Set value
	void 				
	value( const std::string& sValue )				///< String value 
												{	MOZ_IF_SET_VOID_STRING(SetValue,sValue);	}
  	///  Get length 
	boost::uint32_t 				
	length() const 
												{	MOZ_IF_RETURN_UINT32(GetLength); }
  	///  Set length
	void 				
	length( const boost::uint32_t iLength )			///< Integer length 
												{	MOZ_IF_SET_VOID_UINT32(SetLength,iLength);	}
	/// Get form element (readonly)
	boost::shared_ptr<DOMHTMLFormElement>		
	form()
												{	MOZ_IF_RETURN_MOZ(GetForm,DOMHTMLFormElement);	}
	/// Get options (readonly)
	boost::shared_ptr<DOMHTMLOptionsCollection>		
	options();
  	
  	///  Get disabled 
	bool 				
	disabled() const 
												{	MOZ_IF_RETURN_BOOL(GetDisabled); }
  	///  Set disabled
	void 				
	disabled( bool bDisabled )						///< Disabled true/false 
												{	MOZ_IF_SET_VOID_BOOL(SetDisabled,bDisabled);	}
  	///  Get multiple 
	bool 				
	multiple() const 
												{	MOZ_IF_RETURN_BOOL(GetMultiple); }
  	///  Set multiple
	void 				
	multiple( bool bMultiple )						///< Multiple true/false 
												{	MOZ_IF_SET_VOID_BOOL(SetMultiple,bMultiple);	}
  	///  Get name
	std::string 				
	name() const 
												{	MOZ_IF_RETURN_STRING(GetName); }
  	///  Set name
	void 				
	name( const std::string& sName )				///< String name 
												{	MOZ_IF_SET_VOID_STRING(SetName,sName);	}
  	///  Get size 
	boost::int32_t 				
	size() const 
												{	MOZ_IF_RETURN_INT32(GetSize); }
  	///  Set size
	void 				
	size( const boost::int32_t iSize )				///< Integer size 
												{	MOZ_IF_SET_VOID_INT32(SetSize,iSize);	}
  	///  Get tabIndex 
	boost::int32_t 				
	tabIndex() const 
												{	MOZ_IF_RETURN_INT32(GetTabIndex); }
  	///  Set tabIndex
	void 				
	tabIndex( const boost::int32_t iTabIndex )		///< Integer tabIndex 
												{	MOZ_IF_SET_VOID_INT32(SetTabIndex,iTabIndex);	}
//	void
//	add( 	const boost::shared_ptr<DOMHTMLElement> pElement, 		///< Element to add
//			const boost::shared_ptr<DOMHTMLElement> pBefore		)	///< Insert before this element
//												{	MOZ_IF_SET_VOID_MOZ_MOZ(Add,pElement,pBefore);	}
  	///  Remove element
	void 				
	remove( const boost::int32_t iIndex )			///< Integer index 
												{	MOZ_IF_SET_VOID_INT32(Remove,iIndex);	}
	///  Blur
	void 				
	blur()			
												{	ifMoz()->Blur();	}
	///  Focus
	void 				
	focus()			
												{	ifMoz()->Focus();	}
};

#endif /* _WEBBROWSE_DOM_HTML_SELECT_ELEMENT_H_ */

