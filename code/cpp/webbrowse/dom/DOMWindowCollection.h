#ifndef _DOM_WINDOW_COLLECTION_H_
#define _DOM_WINDOW_COLLECTION_H_

#include <nsIDOMWindowCollection.h>

#include <utils/mozilla_if_macros.h>
#include <utils/mozilla_utils.h>

class DOMWindowCollection;
typedef boost::shared_ptr<DOMWindowCollection>		DOMWindowCollectionPtr;			///< Pointer to a DOMWindowCollection

class DOMWindow;

/**
* The nsIDOMWindowCollection interface is an interface for a
* collection of DOM window objects.
*
* @status FROZEN
*/
class DOMWindowCollection : public Supports {
	MOZ_CONSTRUCT(DOMWindowCollection,Supports);
public: 
	
	/// Get length of list. Accessor for the number of windows in this collection.
	boost::uint32_t 				
	length() const
										{	MOZ_IF_RETURN_UINT32(GetLength);	}
	
	boost::shared_ptr<DOMWindow>		
	item( boost::uint32_t iIndex ) const;
	
	boost::shared_ptr<DOMWindow>		
	namedItem( const std::string& sName );
	
};


#endif /* _DOM_WINDOW_COLLECTION_H_ */

