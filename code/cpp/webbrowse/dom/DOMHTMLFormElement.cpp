#include "DOMHTMLFormElement.h"

#include <dom/DOMHTMLCollection.h>	


boost::shared_ptr<DOMHTMLCollection>	
DOMHTMLFormElement::elements() const
{	MOZ_IF_RETURN_MOZ(GetElements,DOMHTMLCollection);	}
