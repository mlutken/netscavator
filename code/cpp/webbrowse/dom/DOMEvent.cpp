
#include <dom/DOMEventTarget.h>
#include "DOMEvent.h"

/// Used to indicate the EventTarget to which the event was originally
/// dispatched.
boost::shared_ptr<DOMEventTarget>			
DOMEvent::target ()
{	
	MOZ_IF_RETURN_MOZ(GetTarget,DOMEventTarget);		
}

/**
Used to indicate the EventTarget whose EventListeners are currently
being processed. This is particularly useful during capturing and
bubbling. */
boost::shared_ptr<DOMEventTarget>			
DOMEvent::currentTarget ()
{	
	MOZ_IF_RETURN_MOZ(GetCurrentTarget,DOMEventTarget);	
}


