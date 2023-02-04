#ifndef _WEBBROWSE_DOM_NAMED_NODE_MAP_H_
#define _WEBBROWSE_DOM_NAMED_NODE_MAP_H_

////#include <dom/nsIDOMNamedNodeMap.h>
#include <nsIDOMNamedNodeMap.h>

#include <dom/DOMNode.h>

#include <utils/mozilla_utils.h>

class DOMNamedNodeMap;
typedef boost::shared_ptr<DOMNamedNodeMap>		DOMNamedNodeMapPtr;			///< Pointer to a DOMNamedNodeMap

/**
* Objects implementing the nsIDOMNamedNodeMap interface are used to 
* represent collections of nodes that can be accessed by name.
*
* For more information on this interface please see 
* http://www.w3.org/TR/DOM-Level-2-Core/
*
* @status FROZEN */
class DOMNamedNodeMap : public Supports {
	MOZ_CONSTRUCT(DOMNamedNodeMap,Supports);
public: 

	/// Get/Lookup item by name  
	/// \return Pointer to the node or NULL if not found
	boost::shared_ptr<DOMNode>	
	getNamedItem( const std::string& sName ) const
												{	MOZ_IF_RETURN_MOZ_STRING(GetNamedItem,DOMNode,sName);	}
	/** Add/Set item by name. 
		Adds a node using its nodeName attribute. If a node with that name is 
		already present in this map, it is replaced by the new one. As the nodeName 
		attribute is used to derive the name which the node must be stored under, 
		multiple nodes of certain types (those that have a "special" string value) 
		cannot be stored as the names would clash. 
		\return If the new Node replaces an existing node the replaced Node is returned, 
				otherwise NULL is returned. 
		\todo DOMNamedNodeMap::setNamedItem should raise DOMException */
	boost::shared_ptr<DOMNode>	
	setNamedItem( boost::shared_ptr<DOMNode> pNodeIn )
												{	MOZ_IF_RETURN_MOZ_MOZ(SetNamedItem,DOMNode,pNodeIn);	}
	/** Remove item by name. 
		Removes a node specified by name. When this map contains the attributes attached 
		to an element, if the removed attribute is known to have a default value, an attribute 
		immediately appears containing the default value as well as the corresponding namespace 
		URI, local name, and prefix when applicable.
		\return The node removed from this map if a node with such a name exists.
		\todo DOMNamedNodeMap::removeNamedItem should raise DOMException */
	boost::shared_ptr<DOMNode>	
	removeNamedItem( const std::string& sName )
												{	MOZ_IF_RETURN_MOZ_STRING(RemoveNamedItem,DOMNode,sName);	}
	/// Get item by index 
	boost::shared_ptr<DOMNode>		
	item( boost::uint32_t iIndex ) const
												{	MOZ_IF_RETURN_MOZ_UINT32(Item,DOMNode,iIndex);	}
	/// Get length of map
	boost::uint32_t 			length() const
												{	MOZ_IF_RETURN_UINT32(GetLength);	}
	
	/** Retrieves a node specified by local name and namespace URI
		\return A Node (of any type) with the specified local name and namespace URI, 
		or null if they do not identify any node in this map.	*/
	boost::shared_ptr<DOMNode>	
	getNamedItemNS( const std::string& sNamespaceURI, 		///< 
					const std::string& sLocalName ) const	///< 
												{	MOZ_IF_RETURN_MOZ_STRING_STRING(GetNamedItemNS,DOMNode,sNamespaceURI,sLocalName);	}
	/** Adds a node using its namespaceURI and localName. 
		If a node with that namespace URI and that local name is already present 
		in this map, it is replaced by the new one. 
		\return If the new Node replaces an existing node the replaced Node is returned, 
				otherwise NULL is returned. 
		\todo DOMNamedNodeMap::setNamedItem should raise DOMException */
	boost::shared_ptr<DOMNode>	
	setNamedItemNS( boost::shared_ptr<DOMNode> pNodeIn )
												{	MOZ_IF_RETURN_MOZ_MOZ(SetNamedItemNS,DOMNode,pNodeIn);	}
	/** Removes a node specified by local name and namespace URI. 
		A removed attribute may be known to have a default value when this map 
		contains the attributes attached to an element, as returned by the attributes 
		attribute of the Node interface. If so, an attribute immediately appears containing 
		the default value as well as the corresponding namespace URI, local name, 
		and prefix when applicable.
		\return The node removed from this map if a node with such a local name and namespace URI exists.
		\todo DOMNamedNodeMap::removeNamedItem should raise DOMException */
	boost::shared_ptr<DOMNode>	
	removeNamedItemNS( 	const std::string& sNamespaceURI, 	///< 
						const std::string& sLocalName )		///< 
												{	MOZ_IF_RETURN_MOZ_STRING_STRING(RemoveNamedItemNS,DOMNode,sNamespaceURI,sLocalName);	}
	// ------------------------------------------------
	// --- Methods beyond W3C/Mozilla specification ---	
	// ------------------------------------------------
	typedef boost::shared_ptr<DOMNode>		value_type;
	typedef value_type &					reference;
	typedef value_type *					pointer;
	typedef boost::int32_t					difference_type;
	
	typedef IteratorItemIndex<DOMNamedNodeMap,DOMNode> iterator;		///< Nested iterator class.
	MOZ_IF_ITERATOR_ITEM_INDEX_CONTAINER_CLASS_FUNCS(DOMNode,length);	///< Create iterator stuff: begin(), end(), front(), back(), size(), at() ..

	/// Acces nodes (read only) by name using operator []
	boost::shared_ptr<DOMNode>	operator[]( const std::string& sName ) const
												{	return getNamedItem(sName);	}
};

#endif /* _WEBBROWSE_DOM_NAMED_NODE_MAP_H_ */

