#ifndef _WEBBROWSE_DOM_EVENT_LISTENER_H_
#define _WEBBROWSE_DOM_EVENT_LISTENER_H_

#include <nsIDOMEventListener.h>
#include <DOMEvent.h>


/**
The nsIDOMEventListener interface is a callback interface for
listening to events in the Document Object Model.

For more information on this interface please see
http://www.w3.org/TR/DOM-Level-2-Events/

@status FROZEN */
class DOMEventListener : public Supports
{
	MOZ_CONSTRUCT(DOMEventListener,Supports);
public:

	/**
	   * This method is called whenever an event occurs of the type for which
	   * the EventListener interface was registered.
	   *
	   * @param   evt The Event contains contextual information about the
	   *              event. It also contains the stopPropagation and
	   *              preventDefault methods which are used in determining the
	   *              event's flow and default action.
	   */
	void	handleEvent ( boost::shared_ptr<DOMEvent> pEvent )
																{	MOZ_IF_SET_VOID_MOZ(HandleEvent,pEvent);	}
};


#endif //_WEBBROWSE_DOM_EVENT_LISTENER_H_

