#ifndef _WEBBROWSE_DOM_PROCESSING_INSTRUCTION_H_
#define _WEBBROWSE_DOM_PROCESSING_INSTRUCTION_H_


////#include <dom/nsIDOMProcessingInstruction.h>
#include <nsIDOMProcessingInstruction.h>

#include <dom/DOMNode.h>

/**
The nsIDOMProcessingInstruction interface represents a 
"processing instruction", used in XML as a way to keep processor-specific 
information in the text of the document.

For more information on this interface please see 
http://www.w3.org/TR/DOM-Level-2-Core/

@status FROZEN */
class DOMProcessingInstruction : public DOMNode {
	MOZ_CONSTRUCT(DOMProcessingInstruction,DOMNode);
public: 
	///  Get target (readonly).
	std::string 				
	target() const 
											{	MOZ_IF_RETURN_STRING(GetTarget); }
	///  Get data
	std::string 				
	data() const 
											{	MOZ_IF_RETURN_STRING(GetData); }
	///  Set data
	void 				
	data( const std::string& sData )		///< String data 
											{	MOZ_IF_SET_VOID_STRING(SetData,sData);	}
};
#endif /* _WEBBROWSE_DOM_PROCESSING_INSTRUCTION_H_ */

