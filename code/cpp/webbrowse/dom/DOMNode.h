#ifndef _WEBBROWSE_DOM_NODE_H_
#define _WEBBROWSE_DOM_NODE_H_

#include <vector>	
#include <boost/shared_ptr.hpp>	
#include <boost/function.hpp>

#include <nsIDOMNode.h>
#include <nsIDOMNodeList.h>
#include <nsCOMPtr.h>


#include <utils/mozilla_if_macros.h>
#include <utils/mozilla_utils.h>

class DOMDocument;
class DOMNodeList;
class DOMNamedNodeMap;
class DOMNode;
typedef boost::shared_ptr<DOMNode>		DOMNodePtr;			///< Pointer to a DOMNode
typedef std::vector<DOMNode>			DOMNodeVec;			///< std::vector of DOMNodes


std::string	
defaultStringDataFun ( DOMNode const* pNode );

/**
* The nsIDOMNode interface is the primary datatype for the entire 
* Document Object Model.
* It represents a single node in the document tree.
*
* For more information on this interface please see 
* http://www.w3.org/TR/DOM-Level-2-Core/
*
* @status FROZEN
*/
class DOMNode : public Supports {
//	MOZ_CONSTRUCT(DOMNode,Supports);
	public:															
		DOMNode ( nsISupports* pIMozImpl ) 							
			:	Supports(pIMozImpl), m_bStringDataCalculated ( false ), m_sStringData(""), m_iNodeType(0) {}							
	typedef nsIDOMNode		nsInterfaceT;						
	typedef boost::shared_ptr<DOMNode>	Ptr;						
																			
	nsInterfaceT*	ifMoz()  												
	{ 	return static_cast<nsInterfaceT*>( ifISupportsNAR() );	} 			
																			
	nsInterfaceT*	ifMoz() const											
	{ 	return static_cast<nsInterfaceT*>( ifISupportsNAR() );	} 			

private:					
	
public: 
	enum Type 
		{ 	ELEMENT 				= 1 << nsIDOMNode::ELEMENT_NODE 				,
			ATTRIBUTE 				= 1 << nsIDOMNode::ATTRIBUTE_NODE 				,
			TEXT 					= 1 << nsIDOMNode::TEXT_NODE 					,
			CDATA_SECTION 			= 1 << nsIDOMNode::CDATA_SECTION_NODE 			,
			ENTITY_REFERENCE 		= 1 << nsIDOMNode::ENTITY_REFERENCE_NODE 		,
			ENTITY 					= 1 << nsIDOMNode::ENTITY_NODE 					,
			PROCESSING_INSTRUCTION 	= 1 << nsIDOMNode::PROCESSING_INSTRUCTION_NODE 	,
			COMMENT 				= 1 << nsIDOMNode::COMMENT_NODE 				,
			DOCUMENT 				= 1 << nsIDOMNode::DOCUMENT_NODE 				,
			DOCUMENT_TYPE 			= 1 << nsIDOMNode::DOCUMENT_TYPE_NODE 			,
			DOCUMENT_FRAGMENT 		= 1 << nsIDOMNode::DOCUMENT_FRAGMENT_NODE 		,
			NOTATION 				= 1 << nsIDOMNode::NOTATION_NODE 				,
			
			// Not in Mozilla/W3C original
			ATTRIBUTE_VALUE 		= 1 << (nsIDOMNode::NOTATION_NODE +1) 			,
			NODE_END_TAG 			= 1 << (nsIDOMNode::NOTATION_NODE +2) 			,
			ALL_NODE_TYPES 			= 0xFFFFFFFF 									};

  	///  Get nodeName (readonly attribute)
	std::string 		
	nodeName()	const 
											{	MOZ_IF_RETURN_STRING(GetNodeName); 			}
  	/// Get nodeValue 
	std::string 		
	nodeValue()	const 
											{	MOZ_IF_RETURN_STRING(GetNodeValue); 		}
	/// Set nodeValue 
	void 				
	nodeValue( const std::string& sValue )
											{	MOZ_IF_SET_VOID_STRING(SetNodeValue,sValue);}
											
	/// Get nodeType 
	boost::uint32_t 	
	nodeType()	const 
											{	
												if ( m_iNodeType == 0 ) {												
													PRUint16 result;								
													ifMoz()->GetNodeType(&result);					
													m_iNodeType = static_cast<boost::uint32_t>( 1 << result ) ;
												}
												return m_iNodeType;	
											}
	/// Get parent node
	boost::shared_ptr<DOMNode>		
	parentNode()
											{	MOZ_IF_RETURN_MOZ(GetParentNode,DOMNode);	}
	/// Get child nodes 
	boost::shared_ptr<DOMNodeList>	
	childNodes();

	/// Get first child node
	boost::shared_ptr<DOMNode>		
	firstChild()
											{	MOZ_IF_RETURN_MOZ(GetFirstChild,DOMNode);	}
	/// Get last child node
	boost::shared_ptr<DOMNode>		
	lastChild()
											{	MOZ_IF_RETURN_MOZ(GetLastChild,DOMNode);	}
	/// Get previous sibling node
	boost::shared_ptr<DOMNode>		
	previousSibling()
											{	MOZ_IF_RETURN_MOZ(GetPreviousSibling,DOMNode);	}
	/// Get next sibling node
	boost::shared_ptr<DOMNode>		
	nextSibling()
											{	MOZ_IF_RETURN_MOZ(GetNextSibling,DOMNode);	}
	/// Get attributes map
	boost::shared_ptr<DOMNamedNodeMap>	
	attributes();

	/// Get owner document of this node
	boost::shared_ptr<DOMDocument>		
	ownerDocument();
	
	/// Insert child node before. \todo Raises (DOMException); 
	boost::shared_ptr<DOMNode>	
	insertBefore( 	const boost::shared_ptr<DOMNode> pNewChild, 	///< New child node to insert
					const boost::shared_ptr<DOMNode> pOldChild )	///< Old child node to replace 
														{	MOZ_IF_RETURN_MOZ_MOZ_MOZ(InsertBefore,DOMNode,pNewChild,pOldChild);	}																	
	/// Replace child node. \todo Raises (DOMException); 
	boost::shared_ptr<DOMNode>	
	replaceChild( 	const boost::shared_ptr<DOMNode> pNewChild, 	///< New child node to insert
					const boost::shared_ptr<DOMNode> pOldChild )	///< Old child node to replace 
														{	MOZ_IF_RETURN_MOZ_MOZ_MOZ(ReplaceChild,DOMNode,pNewChild,pOldChild);	}																	
	 /// Remove child node. \todo Raises (DOMException); 
	boost::shared_ptr<DOMNode>	
	removeChild( const boost::shared_ptr<DOMNode> pOldChild )
														{	MOZ_IF_RETURN_MOZ_MOZ(RemoveChild,DOMNode,pOldChild);	}																	
	/// Append child node. \todo Raises (DOMException); 
	boost::shared_ptr<DOMNode>	
	appendChild( const boost::shared_ptr<DOMNode> pNewChild )
														{	MOZ_IF_RETURN_MOZ_MOZ(AppendChild,DOMNode,pNewChild);	}																	
	/// Get hasChildNodes
	bool 				
	hasChildNodes() const 
														{	MOZ_IF_RETURN_BOOL(HasChildNodes);	}
	///  Clone this node. 
	boost::shared_ptr<DOMNode>			
	cloneNode( bool bDeep )
	{																		
		nsCOMPtr<nsIDOMNode> pIDOMNode;										
		ifMoz()->CloneNode( static_cast<PRBool>(bDeep), getter_AddRefs(pIDOMNode) );		
		return DOMNodePtr(new DOMNode(pIDOMNode) );							
	}

	/** void normalize (); */
	void				
	normalize ()
														{	ifMoz()->Normalize();	}
	/// Find out if feature is supported
	bool 				
	isSupported ( 	const std::string& sFeature, 		///< 
					const std::string& sVersion )		///< 
														{	MOZ_IF_RETURN_BOOL_STRING_STRING(IsSupported,sFeature,sVersion);	}
	/// Get namespace URI
	std::string 		
	namespaceURI() const 
														{	MOZ_IF_RETURN_STRING(GetNamespaceURI); }
    /// Get  DOMString prefix
	std::string 		
	prefix() const 
														{	MOZ_IF_RETURN_STRING(GetPrefix); }
//	/// Set  DOMString prefix
//    void
//	prefix( const std::string& sValue )
//														{	MOZ_IF_SET_VOID_STRING(SetPrefix,sValue); }
	/// Get localName 
	std::string 		
	localName() const 
														{	MOZ_IF_RETURN_STRING(GetLocalName); }
	/// Get hasAttributes
	bool 			
	hasAttributes () const 
														{	MOZ_IF_RETURN_BOOL(HasAttributes); }
	
	// ------------------------------------------------
	// --- Methods beyond W3C/Mozilla specification ---	
	// ------------------------------------------------
	typedef boost::function< std::string ( DOMNode const* ) >		NodeStringDataFunT;		///< Prototype for node string data function
	
	void		
	resetStringData()	
	{	m_bStringDataCalculated = false;	}
	
	void		
	forceNodeType ( boost::uint32_t iNodeType )	
														{	m_iNodeType = iNodeType;	}
	
	void		
	forceStringData ( std::string sStringData )	;
	
 	std::string const&	
 	stringData ( bool bTrimBlanks, NodeStringDataFunT const& nodeStringDataFun = defaultStringDataFun ) const;
	

private:
	mutable bool				m_bStringDataCalculated;
	mutable std::string			m_sStringData;
	mutable boost::uint32_t		m_iNodeType;
	
};



#endif /* _WEBBROWSE_DOM_NODE_H_ */
