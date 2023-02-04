#include "DOMAttr.h"
#include <dom/DOMElement.h>

boost::shared_ptr<DOMElement>		
DOMAttr::ownerElement()
{	MOZ_IF_RETURN_MOZ(GetOwnerElement,DOMElement);	}
	
