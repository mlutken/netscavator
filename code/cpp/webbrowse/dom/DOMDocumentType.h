#ifndef _WEBBROWSE_DOM_DOCUMENT_TYPE_H_
#define _WEBBROWSE_DOM_DOCUMENT_TYPE_H_


////#include <dom/nsIDOMDocumentType.h>
#include <nsIDOMDocumentType.h>

#include <dom/DOMNode.h>
#include <dom/DOMNamedNodeMap.h>

/**
Each Document has a doctype attribute whose value is either null 
or a DocumentType object. 
The nsIDOMDocumentType interface in the DOM Core provides an 
interface to the list of entities that are defined for the document.

For more information on this interface please see 
http://www.w3.org/TR/DOM-Level-2-Core/

@status FROZEN */
class DOMDocumentType : public DOMNode {
	MOZ_CONSTRUCT(DOMDocumentType,DOMNode);
public: 
  	///  Get name (readonly)
	std::string 				
	name() const 
												{	MOZ_IF_RETURN_STRING(GetName); }
//	/// Get entities (readonly)
//	boost::shared_ptr<DOMNamedNodeMap>
//	entities()
//												{	MOZ_IF_RETURN_MOZ(GetEntities,DOMNamedNodeMap);	}
//	/// Get notations (readonly)
//	boost::shared_ptr<DOMNamedNodeMap>
//	notations()
//												{	MOZ_IF_RETURN_MOZ(GetNotations,DOMNamedNodeMap);	}
  	///  Get publicId (readonly)
	std::string 				
	publicId() const 
												{	MOZ_IF_RETURN_STRING(GetPublicId); }
  	///  Get systemId (readonly)
	std::string 				
	systemId() const 
												{	MOZ_IF_RETURN_STRING(GetSystemId); }
  	///  Get internalSubset (readonly)
	std::string 				
	internalSubset() const 
												{	MOZ_IF_RETURN_STRING(GetInternalSubset); }
};


#endif /* _WEBBROWSE_DOM_DOCUMENT_TYPE_H_ */

