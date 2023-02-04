
#include "DOMHTMLSelectElement.h"

#include <dom/DOMHTMLOptionsCollection.h>

boost::shared_ptr<DOMHTMLOptionsCollection>		
DOMHTMLSelectElement::options()
									{	MOZ_IF_RETURN_MOZ(GetOptions,DOMHTMLOptionsCollection);	}
