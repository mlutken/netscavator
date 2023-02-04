
#include "DOMWindowCollection.h"
#include "DOMWindow.h"
	
/// Method for accessing an item in this collection by index  
boost::shared_ptr<DOMWindow>		
DOMWindowCollection::item( boost::uint32_t iIndex ) const
{
	MOZ_IF_RETURN_MOZ_UINT32(Item,DOMWindow,iIndex);
}
	

/// Get named item
boost::shared_ptr<DOMWindow>		
DOMWindowCollection::namedItem( const std::string& sName )
{	
	MOZ_IF_RETURN_MOZ_STRING(NamedItem,DOMWindow,sName);	
}
