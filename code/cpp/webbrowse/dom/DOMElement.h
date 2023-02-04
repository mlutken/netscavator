#ifndef _WEBBROWSE_DOM_ELEMENT_H_
#define _WEBBROWSE_DOM_ELEMENT_H_

#include <boost/shared_ptr.hpp>	

////#include <dom/nsIDOMElement.h>

#include <nsIDOMElement.h>

#include <dom/DOMNode.h>
#include <dom/DOMNodeList.h>
#include <dom/DOMAttr.h>
#include <utils/mozilla_if_macros.h>


  /**
 * The nsIDOMElement interface represents an element in an HTML or 
 * XML document. 
 *
 * For more information on this interface please see 
 * http://www.w3.org/TR/DOM-Level-2-Core/
 *
 * @status FROZEN
 */
class DOMElement : public DOMNode  {
	MOZ_CONSTRUCT(DOMElement,DOMNode);
public:
  	///  Get tagName (readonly attribute)
	std::string 				
	tagName() const 
											{	MOZ_IF_RETURN_STRING(GetTagName); }
	/// Get attribute 
	std::string 				
	getAttribute( const std::string& sName ) const 
											{	MOZ_IF_RETURN_STRING_STRING(GetAttribute,sName); }
	/// Set attribute 
	void 						
	setAttribute( 	const std::string& sName, 
					const std::string& sValue )
											{	MOZ_IF_SET_VOID_STRING_STRING(SetAttribute,sName,sValue);	}
	/// Remove attribute 
	void						
	removeAttribute( const std::string& sName )
											{	ifMoz()->RemoveAttribute( toAStringUTF16(sName) );	}
	/// Get attribute node 
	boost::shared_ptr<DOMAttr>	
	getAttributeNode( const std::string& sName )
											{	MOZ_IF_RETURN_MOZ_STRING(GetAttributeNode,DOMAttr,sName);	}
	
	/// Set attribute node. \todo Raises (DOMException); 
	boost::shared_ptr<DOMAttr>	
	setAttributeNode( const boost::shared_ptr<DOMAttr> pMozBase )
											{	MOZ_IF_RETURN_MOZ_MOZ(SetAttributeNode,DOMAttr,pMozBase);	}																	
	/// Remove attribute node. \todo Raises (DOMException); 
	boost::shared_ptr<DOMAttr>	
	removeAttributeNode( const boost::shared_ptr<DOMAttr> pMozBase )
											{	MOZ_IF_RETURN_MOZ_MOZ(RemoveAttributeNode,DOMAttr,pMozBase);	}																	
	/// nsIDOMNodeList getElementsByTagName (in DOMString name); 
	boost::shared_ptr<DOMNodeList>	
	getElementsByTagName( const std::string& sName )
	{	MOZ_IF_RETURN_MOZ_STRING(GetElementsByTagName,DOMNodeList,sName);	}
	
	/// Get attribute in namepace 
	std::string 		
	getAttributeNS( const std::string& sNameSpace, 
					const std::string& sName ) const 
	{	MOZ_IF_RETURN_STRING_STRING_STRING(GetAttributeNS,sNameSpace,sName);	}
	
	/// void setAttributeNS (in DOMString namespaceURI, in DOMString qualifiedName, in DOMString value)  raises (DOMException); 
	void 				
	setAttributeNS( const std::string& sNameSpace, 
					const std::string& sName, 
					const std::string& sValue ) const 
	{	MOZ_IF_SET_VOID_STRING_STRING_STRING(SetAttributeNS,sNameSpace,sName,sValue);	}
	
	/// void removeAttributeNS (in DOMString namespaceURI, in DOMString localName)  raises (DOMException); 
	void 				
	removeAttributeNS( 	const std::string& sNameSpace, 
						const std::string& sName ) const 
	{	MOZ_IF_SET_VOID_STRING_STRING(RemoveAttributeNS,sNameSpace,sName);	}	
	
	/// nsIDOMAttr getAttributeNodeNS (in DOMString namespaceURI, in DOMString localName); 
	boost::shared_ptr<DOMAttr>	
	getAttributeNodeNS( const std::string& sNameSpace, 
						const std::string& sName  )
	{	MOZ_IF_RETURN_MOZ_STRING_STRING(GetAttributeNodeNS,DOMAttr,sNameSpace,sName);	}
	
	/// Set attribute node namespace. \todo Raises (DOMException); 
	boost::shared_ptr<DOMAttr>	
	setAttributeNodeNS( const boost::shared_ptr<DOMAttr> pMozBase )
	{	MOZ_IF_RETURN_MOZ_MOZ(SetAttributeNodeNS,DOMAttr,pMozBase);	}																	
	
	/// nsIDOMNodeList getElementsByTagNameNS (in DOMString namespaceURI, in DOMString localName)
	boost::shared_ptr<DOMNodeList>	
	getElementsByTagNameNS( const std::string& sNameSpace, 
							const std::string& sName  )
										{	MOZ_IF_RETURN_MOZ_STRING_STRING(GetElementsByTagNameNS,DOMNodeList,sNameSpace,sName);	}
	
	/// boolean hasAttribute (in DOMString name); 
	bool 				
	hasAttribute( const std::string& sName ) const 
										{	MOZ_IF_RETURN_BOOL_STRING(HasAttribute,sName);	}
	
	/// boolean hasAttributeNS (in DOMString namespaceURI, in DOMString localName); 
	bool 				
	hasAttributeNS( const std::string& sNameSpace, 
					const std::string& sName ) const 
										{	MOZ_IF_RETURN_BOOL_STRING_STRING(HasAttributeNS,sNameSpace,sName);	}

	// ------------------------------------------------
	// --- Methods beyond W3C/Mozilla specification ---	
	// ------------------------------------------------
	
	// --- Convienience 'class' functions ---

	/// Get class 
	std::string 				
	getClass() const						
											{	return getAttribute("class"); }
	/// Set class 
	void 				
	setClass( const std::string& sClass ) 
											{	return setAttribute("class", sClass); }
	void 						
	addClass( const std::string& sClassName );
	
	void						
	removeClass( const std::string& sClassName );

};

#endif /* _WEBBROWSE_DOM_ELEMENT_H_ */

