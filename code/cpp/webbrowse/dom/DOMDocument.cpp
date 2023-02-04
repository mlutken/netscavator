#include "DOMDocument.h"	

#include <nsIDocument.h>

nsCOMPtr<nsIDocument>
DOMDocument::getDocument() const
{
	nsCOMPtr<nsIDocument> pIDocument = do_QueryInterface( ifMoz() );
	return pIDocument;
}
	



