#ifndef _WEBBROWSE_DOM_TEXT_H_
#define _WEBBROWSE_DOM_TEXT_H_


#include <nsIDOMText.h>
#include <dom/DOMCharacterData.h>

/**
The nsIDOMText interface inherits from nsIDOMCharacterData and represents 
the textual content (termed character data in XML) of an Element or Attr.

For more information on this interface please see 
http://www.w3.org/TR/DOM-Level-2-Core/
@status FROZEN */
class DOMText : public DOMCharacterData {
	MOZ_CONSTRUCT(DOMText,DOMCharacterData);
public: 
	/// Split text at offset. \todo raises DOMException.
	boost::shared_ptr<DOMText>		
	item( boost::uint32_t iIndex ) const
												{	MOZ_IF_RETURN_MOZ_UINT32(SplitText,DOMText,iIndex);	}
};
#endif // _WEBBROWSE_DOM_TEXT_H_ 
