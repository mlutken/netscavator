#ifndef _WEBBROWSE_DOM_DOCUMENT_FRAGMENT_H_
#define _WEBBROWSE_DOM_DOCUMENT_FRAGMENT_H_


////#include <dom/nsIDOMDocumentFragment.h>
#include <nsIDOMDocumentFragment.h>

#include <dom/DOMNode.h>

class DOMDocumentFragment : public DOMNode {
	MOZ_CONSTRUCT(DOMDocumentFragment,DOMNode);
public: 
};

#endif /* _WEBBROWSE_DOM_DOCUMENT_FRAGMENT_H_ */

