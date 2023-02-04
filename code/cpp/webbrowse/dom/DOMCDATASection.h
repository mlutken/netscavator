#ifndef _WEBBROWSE_DOM_CDATA_SECTION_H_
#define _WEBBROWSE_DOM_CDATA_SECTION_H_


////#include <dom/nsIDOMCDATASection.h>
#include <nsIDOMCDATASection.h>

#include <dom/DOMText.h>

class DOMCDATASection : public DOMText {
	MOZ_CONSTRUCT(DOMCDATASection,DOMText);
public: 
};

#endif /* _WEBBROWSE_DOM_CDATA_SECTION_H_ */

