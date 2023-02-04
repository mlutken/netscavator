#ifndef _WEBBROWSE_DOM_HTML_DOCUMENT_H_
#define _WEBBROWSE_DOM_HTML_DOCUMENT_H_

////#include <dom/nsIDOMHTMLDocument.h>
#include <nsIDOMHTMLDocument.h>

#include <dom/DOMDocument.h>
#include <dom/DOMHTMLElement.h>
#include <dom/DOMHTMLCollection.h>
#include <dom/DOMNodeList.h>

/**
 * The nsIDOMHTMLDocument interface is the interface to a [X]HTML
 * document object.
 *
 * For more information on this interface please see
 * http://www.w3.org/TR/DOM-Level-2-HTML/
 *
 * @status FROZEN
 */
class DOMHTMLDocument : public DOMDocument {
	MOZ_CONSTRUCT(DOMHTMLDocument,DOMDocument);
public: 
  	///  Get title
	std::string 				
	title() const 
												{	MOZ_IF_RETURN_STRING(GetTitle); }
  	///  Set title
	void 				
	title( const std::string& sTitle )				///< String title 
												{	MOZ_IF_SET_VOID_STRING(SetTitle,sTitle);	}
  	///  Get referrer
	std::string 				
	referrer() const 
												{	MOZ_IF_RETURN_STRING(GetReferrer); }
  	///  Get domain
	std::string 				
	domain() const 
												{	MOZ_IF_RETURN_STRING(GetDomain); }
  	///  Get url
	std::string 				
	url() const 
												{	MOZ_IF_RETURN_STRING(GetURL); }
	/// Get body
	boost::shared_ptr<DOMHTMLElement>		
	body()
												{	MOZ_IF_RETURN_MOZ(GetBody,DOMHTMLElement);	}
  	///  Set body
	void 				
	title( const boost::shared_ptr<DOMHTMLElement>  pBody	)	///< Body element
												{	MOZ_IF_SET_VOID_MOZ(SetBody,pBody);	}
	/// Get images
	boost::shared_ptr<DOMHTMLCollection>		
	images()
												{	MOZ_IF_RETURN_MOZ(GetImages,DOMHTMLCollection);	}
	/// Get applets
	boost::shared_ptr<DOMHTMLCollection>		
	applets()
												{	MOZ_IF_RETURN_MOZ(GetApplets,DOMHTMLCollection);	}
	/// Get links
	boost::shared_ptr<DOMHTMLCollection>		
	links()
												{	MOZ_IF_RETURN_MOZ(GetLinks,DOMHTMLCollection);	}
	/// Get forms
	boost::shared_ptr<DOMHTMLCollection>		
	forms()
												{	MOZ_IF_RETURN_MOZ(GetForms,DOMHTMLCollection);	}
	/// Get anchors
	boost::shared_ptr<DOMHTMLCollection>		
	anchors()
												{	MOZ_IF_RETURN_MOZ(GetAnchors,DOMHTMLCollection);	}
  	///  Get cookie
	std::string 				
	cookie() const 
												{	MOZ_IF_RETURN_STRING(GetCookie); }
  	///  Set cookie
	void 				
	cookie( const std::string& sCookie )			///< String cookie 
												{	MOZ_IF_SET_VOID_STRING(SetCookie,sCookie);	}
	/// Open 
	void				
	open()
												{	ifMoz()->Open();	}
	/// Close 
	void				
	close()
												{	ifMoz()->Close();	}
  	///  Write string
	void 				
	write( const std::string& sText )				///< String to write 
												{	MOZ_IF_SET_VOID_STRING(Write,sText);	}
  	///  Write line
	void 				
	writeln( const std::string& sText )				///< Line to write 
												{	MOZ_IF_SET_VOID_STRING(Writeln,sText);	}
	/// Get attribute node 
	boost::shared_ptr<DOMNodeList>	
	getElementsByName( const std::string& sElementName )	///< Element name
												{	MOZ_IF_RETURN_MOZ_STRING(GetElementsByName,DOMNodeList,sElementName);	}
};


#endif /* _WEBBROWSE_DOM_HTML_DOCUMENT_H_ */
