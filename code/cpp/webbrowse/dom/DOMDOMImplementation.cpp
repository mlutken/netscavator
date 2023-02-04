#include "DOMDOMImplementation.h"

#include <dom/DOMDocument.h>

// 	
// 	/* nsIDOMDocument createDocument (in DOMString namespaceURI, in DOMString qualifiedName, in nsIDOMDocumentType doctype)  raises (DOMException); */
// 	CreateDocument(const nsAString & namespaceURI, const nsAString & qualifiedName, nsIDOMDocumentType *doctype, nsIDOMDocument **_retval) = 0;
	/** Create document.	
	\todo DOMDOMImplementation::createDocument should raise DOMException */
boost::shared_ptr<DOMDocument>	
DOMDOMImplementation::createDocument(	
	const std::string& sNamespaceURI, 		
	const std::string& sQualifiedName,		
	const boost::shared_ptr<DOMDocumentType> pDocumentType )
{
	nsCOMPtr<nsIDOMDocument> pIMozReturn;														
	ifMoz()->CreateDocument( toAStringUTF16(sNamespaceURI), toAStringUTF16(sQualifiedName), pDocumentType->ifMoz(), getter_AddRefs(pIMozReturn) );
	return boost::shared_ptr<DOMDocument>(new DOMDocument(pIMozReturn) );									

}	

