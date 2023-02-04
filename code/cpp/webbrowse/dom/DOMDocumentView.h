#ifndef _WEBBROWSE_DOM_DOCUMENT_VIEW_H_
#define _WEBBROWSE_DOM_DOCUMENT_VIEW_H_

////#include <nsIDOMDocumentView.h>
#include <utils/mozilla_if_macros.h>
#include <utils/mozilla_utils.h>

class DOMAbstractView;

/**
The nsIDOMDocumentView interface is a datatype for a document that
supports views in the Document Object Model.

For more information on this interface please see
http://www.w3.org/TR/DOM-Level-2-Views
@status FROZEN */
class DOMDocumentView : public Supports
{
////	MOZ_CONSTRUCT(DOMDocumentView,Supports);
public:
////	/// Get defaultView
////	boost::shared_ptr<DOMAbstractView>
////	defaultView();
};


#endif // _WEBBROWSE_DOM_DOCUMENT_VIEW_H_
