#ifndef _DOM_BAR_PROP_H_
#define _DOM_BAR_PROP_H_

#include <nsIDOMBarProp.h>

#include <utils/mozilla_if_macros.h>
#include <utils/mozilla_utils.h>

class DOMBarProp;
typedef boost::shared_ptr<DOMBarProp>		DOMBarPropPtr;			///< Pointer to a DOMBarProp

/**
* The nsIDOMBarProp interface is the interface for controlling and
* accessing the visibility of certain UI items (scrollbars, menubars,
* toolbars, ...) through the DOM.
*
* @status FROZEN
*/
class DOMBarProp : public Supports {
	MOZ_CONSTRUCT(DOMBarProp,Supports);
public: 
	///  Get visible
	bool  				
	visible() const 
												{	MOZ_IF_RETURN_BOOL(GetVisible); }
  	///  Set visible
	void 				
	visible( bool bVisible )			///< Set visible to true or false
												{	MOZ_IF_SET_VOID_BOOL(SetVisible,bVisible);	}

  /* attribute boolean visible; */
// // 	NS_SCRIPTABLE NS_IMETHOD GetVisible(PRBool *aVisible) = 0;
// // 	NS_SCRIPTABLE NS_IMETHOD SetVisible(PRBool aVisible) = 0;
	
};



#endif /* _DOM_BAR_PROP_H_ */
