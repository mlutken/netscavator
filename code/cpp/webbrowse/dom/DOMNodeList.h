#ifndef _WEBBROWSE_DOM_NODE_LIST_H_
#define _WEBBROWSE_DOM_NODE_LIST_H_

////#include <dom/nsIDOMNodeList.h>
#include <nsIDOMNodeList.h>

#include <dom/DOMNode.h>
#include <utils/mozilla_utils.h>
#include <utils/mozilla_if_macros.h>

class DOMNode;
class DOMNodeList;
typedef boost::shared_ptr<DOMNodeList>		DOMNodeListPtr;			///< Pointer to a DOMNodeList

/**
* The nsIDOMNodeList interface provides the abstraction of an ordered 
* collection of nodes, without defining or constraining how this collection 
* is implemented.
* The items in the list are accessible via an integral index, starting from 0.
*
* For more information on this interface please see 
* http://www.w3.org/TR/DOM-Level-2-Core/
*
* @status FROZEN
*/
class DOMNodeList : public Supports {
	MOZ_CONSTRUCT(DOMNodeList,Supports);
public: 
	/// Get item by index 
	boost::shared_ptr<DOMNode>		
	item( boost::uint32_t iIndex ) const
												{	MOZ_IF_RETURN_MOZ_UINT32(Item,DOMNode,iIndex);	}
	/// Get length of list
	boost::uint32_t 				
	length() const
												{	MOZ_IF_RETURN_UINT32(GetLength);	}
	
	// ------------------------------------------------
	// --- Methods beyond W3C/Mozilla specification ---	
	// ------------------------------------------------
	typedef boost::shared_ptr<DOMNode>		value_type;
	typedef value_type &					reference;
	typedef value_type *					pointer;
	typedef boost::int32_t					difference_type;
	
	typedef IteratorItemIndex<DOMNodeList,DOMNode> iterator;			///< Nested iterator class.
	MOZ_IF_ITERATOR_ITEM_INDEX_CONTAINER_CLASS_FUNCS(DOMNode,length);	///< Create iterator stuff: begin(), end(), front(), back(), size(), at() ..

	/// Acces nodes by index using operator []
	boost::shared_ptr<DOMNode>	operator[]( boost::uint32_t iIndex ) const
	{	return item(iIndex);}
};


#endif /* _WEBBROWSE_DOM_NODE_LIST_H_*/

