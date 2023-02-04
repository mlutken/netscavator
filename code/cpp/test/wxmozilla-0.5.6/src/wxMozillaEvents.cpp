/*
 * wxWindows Mozilla Browser Events Component
 * 
 * Developers:
 *  Jeremiah Cornelius McCarthy <jeremiah@whoop-ass.ca>
 *  Kevin Ollivier <kevino@tulane.edu>
 *  Dave Fancella <david.fancella@attbi.com>
 */

#include "wx/wxprec.h"

#include "wxMozilla.h"

IMPLEMENT_DYNAMIC_CLASS( wxMozillaBeforeLoadEvent, wxCommandEvent )
IMPLEMENT_DYNAMIC_CLASS( wxMozillaStateChangedEvent, wxCommandEvent )
IMPLEMENT_DYNAMIC_CLASS( wxMozillaSecurityChangedEvent, wxCommandEvent )
IMPLEMENT_DYNAMIC_CLASS( wxMozillaLoadCompleteEvent, wxCommandEvent )
IMPLEMENT_DYNAMIC_CLASS( wxMozillaLinkChangedEvent, wxCommandEvent )
IMPLEMENT_DYNAMIC_CLASS( wxMozillaStatusChangedEvent, wxCommandEvent )
IMPLEMENT_DYNAMIC_CLASS( wxMozillaTitleChangedEvent, wxCommandEvent )
IMPLEMENT_DYNAMIC_CLASS( wxMozillaProgressEvent, wxCommandEvent )
IMPLEMENT_DYNAMIC_CLASS( wxMozillaRightClickEvent, wxMouseEvent )
  /**
   * @author David Teller <Yoric@users.sourceforge.net>
   * Load status events
   */
//IMPLEMENT_DYNAMIC_CLASS(  wxMozillaLoadEvent, wxCommandEvent)


DEFINE_EVENT_TYPE( wxEVT_MOZILLA_BEFORE_LOAD )
DEFINE_EVENT_TYPE( wxEVT_MOZILLA_STATE_CHANGED )
DEFINE_EVENT_TYPE( wxEVT_MOZILLA_SECURITY_CHANGED )
DEFINE_EVENT_TYPE( wxEVT_MOZILLA_LOAD_COMPLETE )
DEFINE_EVENT_TYPE( wxEVT_MOZILLA_URL_CHANGED )
DEFINE_EVENT_TYPE( wxEVT_MOZILLA_STATUS_CHANGED )
DEFINE_EVENT_TYPE( wxEVT_MOZILLA_TITLE_CHANGED )
DEFINE_EVENT_TYPE( wxEVT_MOZILLA_PROGRESS )
DEFINE_EVENT_TYPE( wxEVT_MOZILLA_RIGHT_CLICK )

  /**
   * @author David Teller <Yoric@users.sourceforge.net>
   * Load status events
   */
//DEFINE_EVENT_TYPE( wxEVT_MOZILLA_LOAD_EVENT )

wxMozillaBeforeLoadEvent::wxMozillaBeforeLoadEvent( wxWindow* win )
{
    SetEventType( wxEVT_MOZILLA_BEFORE_LOAD);
    SetEventObject( win );
	SetId(win->GetId());
}

wxMozillaStateChangedEvent::wxMozillaStateChangedEvent( wxWindow* win )
{
    SetEventType( wxEVT_MOZILLA_STATE_CHANGED);
    SetEventObject( win );
	SetId(win->GetId());
}

wxMozillaSecurityChangedEvent::wxMozillaSecurityChangedEvent( wxWindow* win )
{
    SetEventType( wxEVT_MOZILLA_SECURITY_CHANGED);
    SetEventObject( win );
	SetId(win->GetId());
}

wxMozillaLoadCompleteEvent::wxMozillaLoadCompleteEvent( wxWindow* win )
{
    SetEventType( wxEVT_MOZILLA_LOAD_COMPLETE);
    SetEventObject( win );
	SetId(win->GetId());
}

wxMozillaLinkChangedEvent::wxMozillaLinkChangedEvent( wxWindow* win )
{
    SetEventType( wxEVT_MOZILLA_URL_CHANGED);
    SetEventObject( win );
	SetId(win->GetId());
}


wxMozillaStatusChangedEvent::wxMozillaStatusChangedEvent( wxWindow* win )
{
    SetEventType( wxEVT_MOZILLA_STATUS_CHANGED);
    SetEventObject( win );
	SetId(win->GetId());
}

wxMozillaTitleChangedEvent::wxMozillaTitleChangedEvent( wxWindow* win )
{
    SetEventType(wxEVT_MOZILLA_TITLE_CHANGED);
    SetEventObject(win);
	SetId(win->GetId());
}

wxMozillaProgressEvent::wxMozillaProgressEvent( wxWindow* win )
{
    SetEventType(wxEVT_MOZILLA_PROGRESS);
    SetEventObject(win);
	SetId(win->GetId());
}

wxMozillaRightClickEvent::wxMozillaRightClickEvent( wxWindow* win )
{
    SetEventType( wxEVT_MOZILLA_RIGHT_CLICK);
    SetEventObject( win );
	SetId(win->GetId());
}

  /**
  * @author David Teller <Yoric@users.sourceforge.net>
  * Load status events
  
wxMozillaLoadEvent::wxMozillaLoadEvent( wxWindow* win )
{
  SetEventType (wxEVT_MOZILLA_LOAD_EVENT );
  SetEventObject (win);
  SetId(win->GetId());
}

  /**
   * @author David Teller <Yoric@users.sourceforge.net>
   * Load status events
   
wxMozillaLoadEvent::wxMozillaLoadEvent( wxEventType commandType, int id )
{
    //Is this normal ?
}
*/