
#include "DOMNode.h"

#include <boost/format.hpp> 
#include <dom/DOMNamedNodeMap.h>
#include <dom/DOMNodeList.h>
#include <dom/DOMDocument.h>

#include <cpaf_string_utils.hpp>
#include <utils/webbrowse_string_utils.h>

boost::shared_ptr<DOMNamedNodeMap>			
DOMNode::attributes( )
{	MOZ_IF_RETURN_MOZ(GetAttributes,DOMNamedNodeMap);	}


boost::shared_ptr<DOMNodeList>		
DOMNode::childNodes()
{	MOZ_IF_RETURN_MOZ(GetChildNodes,DOMNodeList);	}


boost::shared_ptr<DOMDocument>		
DOMNode::ownerDocument()
{	MOZ_IF_RETURN_MOZ(GetOwnerDocument,DOMDocument);	}


// ------------------------------------------------
// --- Methods beyond W3C/Mozilla specification ---	
// ------------------------------------------------
std::string const&	
DOMNode::stringData ( bool bTrimBlanks, NodeStringDataFunT const& nodeStringDataFun ) const
{	
	if ( !m_bStringDataCalculated )	{
		m_sStringData = nodeStringDataFun( this );
		//if ( bTrimBlanks ) 
		m_sStringData = trimBlanksCopy(m_sStringData);
		m_bStringDataCalculated = true;
	}
	return m_sStringData; 
}




std::string	
defaultStringDataFun ( DOMNode const* pNode )
{
//	return pNode->nodeName() + "=" + pNode->nodeValue() 	; 
	
	std::string sType = cpaf::to_string( pNode->nodeType() );
	
	switch ( static_cast<boost::uint32_t>(pNode->nodeType()) ) {
//		case DOMNode::ELEMENT	 					: return "ELEMENT"					; break; 
		case DOMNode::ATTRIBUTE 					: return pNode->nodeName() 								; break; 
//		case DOMNode::ATTRIBUTE 					: return pNode->nodeName() + "=" + pNode->nodeValue() 	; break; 
		case DOMNode::TEXT 							: return pNode->nodeValue() 							; break; 
//		case DOMNode::CDATA_SECTION		 			: return "CDATA_SECTION"			; break; 
//		case DOMNode::ENTITY_REFERENCE		 		: return "ENTITY_REFERENCE"			; break; 
//		case DOMNode::ENTITY			 			: return "ENTITY"					; break; 
//		case DOMNode::PROCESSING_INSTRUCTION	 	: return "PROCESSING_INSTRUCTION"	; break; 
		case DOMNode::COMMENT	 					: return pNode->nodeValue() 							; break; 
//		case DOMNode::DOCUMENT		 				: return "DOCUMENT"					; break; 
//		case DOMNode::DOCUMENT_TYPE		 			: return "DOCUMENT_TYPE"			; break; 
//		case DOMNode::DOCUMENT_FRAGMENT		 		: return "DOCUMENT_FRAGMENT"		; break; 
//		case DOMNode::NOTATION		 				: return "NOTATION"					; break; 
		case DOMNode::ATTRIBUTE_VALUE				: return pNode->nodeValue() 							; break; 
		default 									: return pNode->nodeName()								; break;
	}
}


void DOMNode::forceStringData ( std::string sStringData )
{
	m_bStringDataCalculated = true;
	m_sStringData = sStringData;
}
