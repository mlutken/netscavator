#ifndef _WEBBROWSE_DOM_DOCUMENT_H_
#define _WEBBROWSE_DOM_DOCUMENT_H_

#include <boost/shared_ptr.hpp>	

#include <nsCOMPtr.h>
#include <nsIDOMDocument.h>

#include <utils/string_conversion.h>

#include <dom/DOMEvent.h>
#include "DOMNode.h"
#include "DOMText.h"
#include "DOMComment.h"
#include "DOMAttr.h"
#include "DOMElement.h"
#include "DOMNodeList.h"
#include "DOMCDATASection.h"
#include "DOMProcessingInstruction.h"
#include "DOMDocumentType.h"
#include "DOMDOMImplementation.h"


class DOMDocument;
typedef boost::shared_ptr<DOMDocument>		DOMDocumentPtr;			///< Pointer to a DOMDocument

class nsIDocument;

/**
* The nsIDOMDocument interface represents the entire HTML or XML document.
* Conceptually, it is the root of the document tree, and provides the 
* primary access to the document's data.
* Since elements, text nodes, comments, processing instructions, etc. 
* cannot exist outside the context of a Document, the nsIDOMDocument 
* interface also contains the factory methods needed to create these 
* objects.
*
* For more information on this interface please see 
* http://www.w3.org/TR/DOM-Level-2-Core/
*
* @status FROZEN
*/
class DOMDocument : public DOMNode {
	MOZ_CONSTRUCT(DOMDocument,DOMNode);
public: 
	boost::shared_ptr<DOMDocumentType>		
	doctype()
														{	MOZ_IF_RETURN_MOZ(GetDoctype,DOMDocumentType);	}
	boost::shared_ptr<DOMDOMImplementation>		
	implementation()
														{	MOZ_IF_RETURN_MOZ(GetImplementation,DOMDOMImplementation);	}

	boost::shared_ptr<DOMElement>		
	documentElement()
														{	MOZ_IF_RETURN_MOZ(GetDocumentElement,DOMElement);	}
	/// Create element by tag name  \todo Raises (DOMException)
	boost::shared_ptr<DOMElement>		
	createElement( const std::string& sTagName )			///< Tagname to 'lookup'
														{	MOZ_IF_RETURN_MOZ_STRING(CreateElement,DOMElement,sTagName);	}
  /* nsIDOMDocumentFragment createDocumentFragment (); */
//     CreateDocumentFragment(nsIDOMDocumentFragment **_retval) = 0;
	/// Create text node 
	boost::shared_ptr<DOMText>		
	createTextNode( const std::string& sData )				///< String data
														{	MOZ_IF_RETURN_MOZ_STRING(CreateTextNode,DOMText,sData);	}
	/// Create comment node 
	boost::shared_ptr<DOMComment>		
	createComment( const std::string& sData )				///< String data
														{	MOZ_IF_RETURN_MOZ_STRING(CreateComment,DOMComment,sData);	}
	/// Create CDATA section.  \todo raises (DOMException)
	boost::shared_ptr<DOMCDATASection>		
	createCDATASection( const std::string& sData )				///< String data
														{	MOZ_IF_RETURN_MOZ_STRING(CreateCDATASection,DOMCDATASection,sData);	}
	boost::shared_ptr<DOMProcessingInstruction>		
	createProcessingInstruction( const std::string& sTarget,	///< Target  
								const std::string& sData	)	///< String data
														{	MOZ_IF_RETURN_MOZ_STRING_STRING(CreateProcessingInstruction,DOMProcessingInstruction,sTarget,sData);	}

	/// Create attribute  
	boost::shared_ptr<DOMAttr>		
	createAttribute( const std::string& sName )				///< Attribute name
														{	MOZ_IF_RETURN_MOZ_STRING(CreateAttribute,DOMAttr,sName);	}

  /* nsIDOMEntityReference createEntityReference (in DOMString name)  raises (DOMException); */
//     CreateEntityReference(const nsAString & name, nsIDOMEntityReference **_retval) = 0;


	/// Get elements by tag name 
	boost::shared_ptr<DOMNodeList>		
	getElementsByTagName( const std::string& sTagName )		///< Tagname to 'lookup'
														{	MOZ_IF_RETURN_MOZ_STRING(GetElementsByTagName,DOMNodeList,sTagName);	}
	/// Import node  \todo Raises (DOMException)
	boost::shared_ptr<DOMNode>		
	importNode(	const boost::shared_ptr<DOMNode> pDOMNode,		///<  Node to import
				bool bDeep									)	///< Deep import if true
	{	
		nsCOMPtr<nsIDOMNode> pIMozReturn;												
		ifMoz()->ImportNode( pDOMNode->ifMoz(), static_cast<PRBool>(bDeep), getter_AddRefs(pIMozReturn) );
		return boost::shared_ptr<DOMNode>(new DOMNode(pIMozReturn) );		
	}
	/// Create element namespace \todo Raises (DOMException)
	boost::shared_ptr<DOMElement>		
	createElementNS(	const std::string& sNamespaceURI,		///<  Namespace
						const std::string& sQualifiedName	)	///< Name
														{	MOZ_IF_RETURN_MOZ_STRING_STRING(CreateElementNS,DOMElement,sNamespaceURI,sQualifiedName);	}
	/// Create attribute namespace \todo Raises (DOMException)
	boost::shared_ptr<DOMAttr>		
	createAttributeNS(	const std::string& sNamespaceURI,		///<  Namespace
						const std::string& sQualifiedName	)	///< Name
														{	MOZ_IF_RETURN_MOZ_STRING_STRING(CreateAttributeNS,DOMAttr,sNamespaceURI,sQualifiedName);	}
	/// Get elements by tag name namespace
	boost::shared_ptr<DOMNodeList>		
	getElementsByTagNameNS( const std::string& sNamespaceURI,		///<  Namespace
							const std::string& sLocalName	)		///< Local name  to 'lookup'
														{	MOZ_IF_RETURN_MOZ_STRING_STRING(GetElementsByTagNameNS,DOMNodeList,sNamespaceURI,sLocalName);	}
	/// Get elements by id
	boost::shared_ptr<DOMElement>		
	getElementById( const std::string& sElementId )		///< String ID to 'lookup'
														{	MOZ_IF_RETURN_MOZ_STRING(GetElementById,DOMElement,sElementId);	}

    boost::shared_ptr<DOMEvent>
    createEvent( const std::string& sEventType )			///< String title
                                                {	MOZ_IF_RETURN_MOZ_STRING(CreateEvent,DOMEvent,sEventType);	}

	// ------------------------------------------------
	// --- Methods beyond W3C/Mozilla specification ---	
	// ------------------------------------------------

	DOMNodeVec	getElementsByTagNameCopy(  const std::string& sTagName )
	{
		DOMNodeVec nodeVec;
		nsCOMPtr<nsIDOMNodeList> nodelist;
		ifMoz()->GetElementsByTagName( toAStringUTF16(sTagName), getter_AddRefs(nodelist) );	
		
		PRUint32 index;
		PRUint32 length;
		nodelist->GetLength(&length);
		for(index=0;index<length;index++)
		{
			nsCOMPtr<nsIDOMNode> pIDOMNode;
			nodelist->Item(index,getter_AddRefs(pIDOMNode));
			nodeVec.push_back( DOMNode(pIDOMNode) );
		}						
		return nodeVec;
	}
	
	nsCOMPtr<nsIDocument>
	getDocument() const;
	
};



#endif /* _WEBBROWSE_DOM_DOCUMENT_H_ */
