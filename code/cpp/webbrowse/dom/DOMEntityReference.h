#ifndef _WEBBROWSE_DOM_ENTITY_REFERENCE_H_
#define _WEBBROWSE_DOM_ENTITY_REFERENCE_H_


////#include <dom/nsIDOMEntityReference.h>
#include <nsIDOMEntityReference.h>

#include <dom/DOMNode.h>

class DOMEntityReference : public DOMNode {
	MOZ_CONSTRUCT(DOMEntityReference,DOMNode);
public: 
};

#endif /* _WEBBROWSE_DOM_ENTITY_REFERENCE_H_ */

