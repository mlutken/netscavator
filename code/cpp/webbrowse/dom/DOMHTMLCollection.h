#ifndef _WEBBROWSE_DOM_HTML_COLLECTION_H_
#define _WEBBROWSE_DOM_HTML_COLLECTION_H_

////#include <dom/nsIDOMHTMLCollection.h>
#include <nsIDOMHTMLCollection.h>

#include <dom/DOMNode.h>
#include <utils/mozilla_if_macros.h>
#include <utils/mozilla_utils.h>


/**
* The nsIDOMHTMLCollection interface is an interface to a collection
* of [X]HTML elements.
*
* For more information on this interface please see
* http://www.w3.org/TR/DOM-Level-2-HTML/
*
* @status FROZEN
*/
class DOMHTMLCollection : public Supports {
	MOZ_CONSTRUCT(DOMHTMLCollection,Supports);
public: 
	/// Get item by index 
	boost::shared_ptr<DOMNode>		
	item( boost::uint32_t iIndex ) const
	{
		nsCOMPtr<nsIDOMNode> pIDOMNode;
		ifMoz()->Item( static_cast<PRUint32>(iIndex), getter_AddRefs(pIDOMNode));
		return DOMNodePtr(new DOMNode(pIDOMNode));
	}

	/// Get length of list
	boost::uint32_t 				
	length() const
										{	MOZ_IF_RETURN_UINT32(GetLength);	}
	/// Get named item
	boost::shared_ptr<DOMNode>		
	namedItem( const std::string& sName )
										{	MOZ_IF_RETURN_MOZ_STRING(NamedItem,DOMNode,sName);	}
	
	// ------------------------------------------------
	// --- Methods beyond W3C/Mozilla specification ---	
	// ------------------------------------------------
	typedef boost::shared_ptr<DOMNode>		value_type;
	typedef value_type &					reference;
	typedef value_type *					pointer;
	typedef boost::int32_t					difference_type;
	
	typedef IteratorItemIndex<DOMHTMLCollection,DOMNode> iterator;		///< Nested iterator class.
	MOZ_IF_ITERATOR_ITEM_INDEX_CONTAINER_CLASS_FUNCS(DOMNode,length);	///< Create iterator stuff: begin(), end(), front(), back(), size(), at() ..

	/// Acces nodes by name using operator []
	boost::shared_ptr<DOMNode>	
	operator[]( const std::string& sName ) 
	{	return namedItem(sName);}
};


#endif /* _WEBBROWSE_DOM_HTML_COLLECTION_H_ */
