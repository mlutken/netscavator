#ifndef _WEBBROWSE_DOM_DOM_IMPLEMENTATION_H_
#define _WEBBROWSE_DOM_DOM_IMPLEMENTATION_H_


////#include <dom/nsIDOMDOMImplementation.h>
#include <nsIDOMDOMImplementation.h>

#include <dom/DOMDocumentType.h>
#include <utils/mozilla_if_macros.h>
#include <utils/mozilla_utils.h>

class DOMDocument;

/**
The nsIDOMDOMImplementation interface provides a number of methods for 
performing operations that are independent of any particular instance 
of the document object model.

For more information on this interface please see 
http://www.w3.org/TR/DOM-Level-2-Core/

@status FROZEN */
class DOMDOMImplementation : public Supports {
	MOZ_CONSTRUCT(DOMDOMImplementation,Supports);
public: 
	/// Check for feature 
	bool 				
	hasFeature( const std::string& sFeature,		///<  
				const std::string& sVersion ) const ///< 
										{	MOZ_IF_RETURN_BOOL_STRING_STRING(HasFeature,sFeature,sVersion);	}
	/** Create document type.	
	\todo DOMDOMImplementation::createDocumentType should raise DOMException */
	boost::shared_ptr<DOMDocumentType>	
	createDocumentType(	const std::string& sQualifiedName, 	///< 
						const std::string& sPublicId,		///< 
						const std::string& sSystemId	)	///< 
										{	MOZ_IF_RETURN_MOZ_STRING_STRING_STRING(CreateDocumentType,DOMDocumentType,sQualifiedName,sPublicId,sSystemId);	}
	/** Create document.	
	\todo DOMDOMImplementation::createDocument should raise DOMException */
	boost::shared_ptr<DOMDocument>	
	createDocument(	const std::string& sNamespaceURI, 						///< 
					const std::string& sQualifiedName,						///< 
					const boost::shared_ptr<DOMDocumentType> pDocumentType	///< 
					);	
};

#endif /* _WEBBROWSE_DOM_DOM_IMPLEMENTATION_H_ */


