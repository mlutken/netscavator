#ifndef _WEBBROWSE_DOM_ABSTRACT_VIEW_H_
#define _WEBBROWSE_DOM_ABSTRACT_VIEW_H_

////#include <nsIDOMAbstractView.h>
#include <utils/mozilla_if_macros.h>
#include <utils/mozilla_utils.h>

class DOMDocumentView;

/**
The nsIDOMAbstractView interface is a datatype for a view in the
Document Object Model.

For more information on this interface please see
http://www.w3.org/TR/DOM-Level-2-Views
@status FROZEN */
class DOMAbstractView : public Supports
{
////	MOZ_CONSTRUCT(DOMAbstractView,Supports);
public:
////	/// Get document(view)
////	boost::shared_ptr<DOMDocumentView>
////	document();
};


#endif // _WEBBROWSE_DOM_ABSTRACT_VIEW_H_
