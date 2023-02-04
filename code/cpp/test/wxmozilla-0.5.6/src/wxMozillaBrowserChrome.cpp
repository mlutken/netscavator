/*
 * wxMozillaBrowserChrome
 * Copyright 2001 (c) Jeremiah Cornelius McCarthy. All Rights Reserved.
 * Modifications: Kevin Ollivier, Vaclav Slavik, Kun Fang
 */

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wxMozilla.h"
#include "wxMozillaEvents.h"
#include "wxMozillaBrowserChrome.h"
#include "wxMozillaWindow.h"
#include "nsIWidget.h"
#include "nsWidgetsCID.h"
#include "nsRect.h"
#include "nsIURI.h"
#include "nsIChannel.h"
#include "nsIRequest.h"
#include "nsIDOMWindow.h"
#include "nsIDOMMouseEvent.h"
#include "nsIDOMKeyEvent.h"
//#include <Carbon/Carbon.h>
#include "wxMozillaBrowserInterface.h"
#include "helpers.h"

static wxMouseEvent
convertMouseEvent ( wxMozillaBrowser* moz,
                    nsIDOMMouseEvent* mouseEvent,
                    const WXTYPE*     eventTypes )
{
	wxMouseEvent thisEvent;

	PRUint16 button;
	mouseEvent->GetButton ( &button );
	switch ( button )
	{
		case 0:
			thisEvent.m_leftDown   = true;
			thisEvent.m_eventType  = eventTypes[0];
			break;

		case 1:
			thisEvent.m_middleDown = true;
			thisEvent.m_eventType  = eventTypes[1];
			break;

		default:
			thisEvent.m_rightDown  = true;
			thisEvent.m_eventType  = eventTypes[2];
	}

	PRBool result;
	mouseEvent->GetAltKey ( &result );
	if ( result )
		thisEvent.m_altDown = true;

	mouseEvent->GetCtrlKey ( &result );
	if ( result )
		thisEvent.m_controlDown = true;

	mouseEvent->GetShiftKey ( &result );
	if ( result )
		thisEvent.m_shiftDown = true;

	mouseEvent->GetMetaKey ( &result );
	if ( result )
		thisEvent.m_metaDown = true;

	PRInt32 x, y;
	mouseEvent->GetScreenX ( &x );
	mouseEvent->GetScreenY ( &y );
	thisEvent.m_x = x;
	thisEvent.m_y = y;
	moz->ScreenToClient ( &thisEvent.m_x, &thisEvent.m_y );

	wxPoint pos = moz->GetPosition();
	thisEvent.m_x += pos.x;
	thisEvent.m_y += pos.y;

	return thisEvent;
}


static wxMouseEvent
convertMouseEvent ( wxMozillaBrowser* moz,
                    nsIDOMMouseEvent* mouseEvent,
                    WXTYPE            eventType )
{
	WXTYPE eventTypes[] = { eventType, eventType, eventType };
	return convertMouseEvent ( moz, mouseEvent, eventTypes );
}


static int
convertKeyCode ( PRUint32 rawCode )
{
	int id;
	switch ( rawCode )
	{
		case nsIDOMKeyEvent::DOM_VK_CANCEL:
			id = WXK_CANCEL;
			break;

		case nsIDOMKeyEvent::DOM_VK_HELP:
			id = WXK_HELP;
			break;

		case nsIDOMKeyEvent::DOM_VK_BACK_SPACE:
			id = WXK_BACK;
			break;

		case nsIDOMKeyEvent::DOM_VK_TAB:
			id = WXK_TAB;
			break;

		case nsIDOMKeyEvent::DOM_VK_CLEAR:
			id = WXK_CLEAR;
			break;

		case nsIDOMKeyEvent::DOM_VK_RETURN:
			// NS tells no difference between WXK_RETURN and WXK_NUMPAD_ENTER
			id = WXK_RETURN;
			break;

		case nsIDOMKeyEvent::DOM_VK_ENTER:
			// WX tells no difference between DOM_VK_ENTER and DOM_VK_RETURN
			id = WXK_RETURN;
			break;

		case nsIDOMKeyEvent::DOM_VK_SHIFT:
			id = WXK_SHIFT;
			break;

		case nsIDOMKeyEvent::DOM_VK_CONTROL:
			id = WXK_CONTROL;
			break;

		case nsIDOMKeyEvent::DOM_VK_ALT:
			id = WXK_ALT;
			break;

		case nsIDOMKeyEvent::DOM_VK_PAUSE:
			id = WXK_PAUSE;
			break;

		case nsIDOMKeyEvent::DOM_VK_CAPS_LOCK:
			id = WXK_CAPITAL;
			break;

		case nsIDOMKeyEvent::DOM_VK_ESCAPE:
			id = WXK_ESCAPE;
			break;

		case nsIDOMKeyEvent::DOM_VK_SPACE:
			id = WXK_SPACE;
			break;

		case nsIDOMKeyEvent::DOM_VK_PAGE_UP:
			id = WXK_PAGEUP;
			break;

		case nsIDOMKeyEvent::DOM_VK_PAGE_DOWN:
			id = WXK_PAGEDOWN;
			break;

		case nsIDOMKeyEvent::DOM_VK_END:
			id = WXK_END;
			break;

		case nsIDOMKeyEvent::DOM_VK_HOME:
			id = WXK_HOME;
			break;

		case nsIDOMKeyEvent::DOM_VK_LEFT:
			id = WXK_LEFT;
			break;

		case nsIDOMKeyEvent::DOM_VK_UP:
			id = WXK_UP;
			break;

		case nsIDOMKeyEvent::DOM_VK_RIGHT:
			id = WXK_RIGHT;
			break;

		case nsIDOMKeyEvent::DOM_VK_DOWN:
			id = WXK_DOWN;
			break;

		case nsIDOMKeyEvent::DOM_VK_PRINTSCREEN:
			id = WXK_PRINT;
			break;

		case nsIDOMKeyEvent::DOM_VK_INSERT:
			id = WXK_INSERT;
			break;

		case nsIDOMKeyEvent::DOM_VK_DELETE:
			id = WXK_DELETE;
			break;

		case nsIDOMKeyEvent::DOM_VK_0:
			id = '0';
			break;

		case nsIDOMKeyEvent::DOM_VK_1:
			id = '1';
			break;

		case nsIDOMKeyEvent::DOM_VK_2:
			id = '2';
			break;

		case nsIDOMKeyEvent::DOM_VK_3:
			id = '3';
			break;

		case nsIDOMKeyEvent::DOM_VK_4:
			id = '4';
			break;

		case nsIDOMKeyEvent::DOM_VK_5:
			id = '5';
			break;

		case nsIDOMKeyEvent::DOM_VK_6:
			id = '6';
			break;

		case nsIDOMKeyEvent::DOM_VK_7:
			id = '7';
			break;

		case nsIDOMKeyEvent::DOM_VK_8:
			id = '8';
			break;

		case nsIDOMKeyEvent::DOM_VK_9:
			id = '9';
			break;

		case nsIDOMKeyEvent::DOM_VK_SEMICOLON:
			id = ';';
			break;

		case nsIDOMKeyEvent::DOM_VK_EQUALS:
			id = '+';   // instead of '='
			break;

		case nsIDOMKeyEvent::DOM_VK_A:
			id = 'A';
			break;

		case nsIDOMKeyEvent::DOM_VK_B:
			id = 'B';
			break;

		case nsIDOMKeyEvent::DOM_VK_C:
			id = 'C';
			break;

		case nsIDOMKeyEvent::DOM_VK_D:
			id = 'D';
			break;

		case nsIDOMKeyEvent::DOM_VK_E:
			id = 'E';
			break;

		case nsIDOMKeyEvent::DOM_VK_F:
			id = 'F';
			break;

		case nsIDOMKeyEvent::DOM_VK_G:
			id = 'G';
			break;

		case nsIDOMKeyEvent::DOM_VK_H:
			id = 'H';
			break;

		case nsIDOMKeyEvent::DOM_VK_I:
			id = 'I';
			break;

		case nsIDOMKeyEvent::DOM_VK_J:
			id = 'J';
			break;

		case nsIDOMKeyEvent::DOM_VK_K:
			id = 'K';
			break;

		case nsIDOMKeyEvent::DOM_VK_L:
			id = 'L';
			break;

		case nsIDOMKeyEvent::DOM_VK_M:
			id = 'M';
			break;

		case nsIDOMKeyEvent::DOM_VK_N:
			id = 'N';
			break;

		case nsIDOMKeyEvent::DOM_VK_O:
			id = 'O';
			break;

		case nsIDOMKeyEvent::DOM_VK_P:
			id = 'P';
			break;

		case nsIDOMKeyEvent::DOM_VK_Q:
			id = 'Q';
			break;

		case nsIDOMKeyEvent::DOM_VK_R:
			id = 'R';
			break;

		case nsIDOMKeyEvent::DOM_VK_S:
			id = 'S';
			break;

		case nsIDOMKeyEvent::DOM_VK_T:
			id = 'T';
			break;

		case nsIDOMKeyEvent::DOM_VK_U:
			id = 'U';
			break;

		case nsIDOMKeyEvent::DOM_VK_V:
			id = 'V';
			break;

		case nsIDOMKeyEvent::DOM_VK_W:
			id = 'W';
			break;

		case nsIDOMKeyEvent::DOM_VK_X:
			id = 'X';
			break;

		case nsIDOMKeyEvent::DOM_VK_Y:
			id = 'Y';
			break;

		case nsIDOMKeyEvent::DOM_VK_Z:
			id = 'Z';
			break;

		case nsIDOMKeyEvent::DOM_VK_NUMPAD0:
			id = WXK_NUMPAD0;
			break;

		case nsIDOMKeyEvent::DOM_VK_NUMPAD1:
			id = WXK_NUMPAD1;
			break;

		case nsIDOMKeyEvent::DOM_VK_NUMPAD2:
			id = WXK_NUMPAD2;
			break;

		case nsIDOMKeyEvent::DOM_VK_NUMPAD3:
			id = WXK_NUMPAD3;
			break;

		case nsIDOMKeyEvent::DOM_VK_NUMPAD4:
			id = WXK_NUMPAD4;
			break;

		case nsIDOMKeyEvent::DOM_VK_NUMPAD5:
			id = WXK_NUMPAD5;
			break;

		case nsIDOMKeyEvent::DOM_VK_NUMPAD6:
			id = WXK_NUMPAD6;
			break;

		case nsIDOMKeyEvent::DOM_VK_NUMPAD7:
			id = WXK_NUMPAD7;
			break;

		case nsIDOMKeyEvent::DOM_VK_NUMPAD8:
			id = WXK_NUMPAD8;
			break;

		case nsIDOMKeyEvent::DOM_VK_NUMPAD9:
			id = WXK_NUMPAD9;
			break;

		case nsIDOMKeyEvent::DOM_VK_MULTIPLY:
			id = WXK_NUMPAD_MULTIPLY;
			break;

		case nsIDOMKeyEvent::DOM_VK_ADD:
			id = WXK_NUMPAD_ADD;
			break;

		case nsIDOMKeyEvent::DOM_VK_SEPARATOR:
			id = WXK_NUMPAD_SEPARATOR;
			break;

		case nsIDOMKeyEvent::DOM_VK_SUBTRACT:
			// NS tells no difference between '-' and WXK_NUMPAD_SUBTRACT
			id = '-';
			break;

		case nsIDOMKeyEvent::DOM_VK_DECIMAL:
			id = WXK_NUMPAD_DECIMAL;
			break;

		case nsIDOMKeyEvent::DOM_VK_DIVIDE:
			id = WXK_NUMPAD_DIVIDE;
			break;

		case nsIDOMKeyEvent::DOM_VK_F1:
			id = WXK_F1;
			break;

		case nsIDOMKeyEvent::DOM_VK_F2:
			id = WXK_F2;
			break;

		case nsIDOMKeyEvent::DOM_VK_F3:
			id = WXK_F3;
			break;

		case nsIDOMKeyEvent::DOM_VK_F4:
			id = WXK_F4;
			break;

		case nsIDOMKeyEvent::DOM_VK_F5:
			id = WXK_F5;
			break;

		case nsIDOMKeyEvent::DOM_VK_F6:
			id = WXK_F6;
			break;

		case nsIDOMKeyEvent::DOM_VK_F7:
			id = WXK_F7;
			break;

		case nsIDOMKeyEvent::DOM_VK_F8:
			id = WXK_F8;
			break;

		case nsIDOMKeyEvent::DOM_VK_F9:
			id = WXK_F9;
			break;

		case nsIDOMKeyEvent::DOM_VK_F10:
			id = WXK_F10;
			break;

		case nsIDOMKeyEvent::DOM_VK_F11:
			id = WXK_F11;
			break;

		case nsIDOMKeyEvent::DOM_VK_F12:
			id = WXK_F12;
			break;

		case nsIDOMKeyEvent::DOM_VK_F13:
			id = WXK_F13;
			break;

		case nsIDOMKeyEvent::DOM_VK_F14:
			id = WXK_F14;
			break;

		case nsIDOMKeyEvent::DOM_VK_F15:
			id = WXK_F15;
			break;

		case nsIDOMKeyEvent::DOM_VK_F16:
			id = WXK_F16;
			break;

		case nsIDOMKeyEvent::DOM_VK_F17:
			id = WXK_F17;
			break;

		case nsIDOMKeyEvent::DOM_VK_F18:
			id = WXK_F18;
			break;

		case nsIDOMKeyEvent::DOM_VK_F19:
			id = WXK_F19;
			break;

		case nsIDOMKeyEvent::DOM_VK_F20:
			id = WXK_F20;
			break;

		case nsIDOMKeyEvent::DOM_VK_F21:
			id = WXK_F21;
			break;

		case nsIDOMKeyEvent::DOM_VK_F22:
			id = WXK_F22;
			break;

		case nsIDOMKeyEvent::DOM_VK_F23:
			id = WXK_F23;
			break;

		case nsIDOMKeyEvent::DOM_VK_F24:
			id = WXK_F24;
			break;

		case nsIDOMKeyEvent::DOM_VK_NUM_LOCK:
			id = WXK_NUMLOCK;
			break;

		case nsIDOMKeyEvent::DOM_VK_SCROLL_LOCK:
			id = WXK_SCROLL;
			break;

		case nsIDOMKeyEvent::DOM_VK_COMMA:
			id = ',';
			break;

		case nsIDOMKeyEvent::DOM_VK_PERIOD:
			id = '.';
			break;

		case nsIDOMKeyEvent::DOM_VK_SLASH:
			id = '/';
			break;

		case nsIDOMKeyEvent::DOM_VK_BACK_QUOTE:
			id = '~';   // instead of '`'
			break;

		case nsIDOMKeyEvent::DOM_VK_OPEN_BRACKET:
			id = '[';
			break;

		case nsIDOMKeyEvent::DOM_VK_BACK_SLASH:
			id = '\\';
			break;

		case nsIDOMKeyEvent::DOM_VK_CLOSE_BRACKET:
			id = ']';
			break;

		case nsIDOMKeyEvent::DOM_VK_QUOTE:
			id = '\'';
			break;

		case nsIDOMKeyEvent::DOM_VK_META:
			//TODO
			id = 'A';
			break;

		default:
			id = 0;
	}

	return id;
}


static wxKeyEvent
convertKeyEvent ( nsIDOMKeyEvent* keyEvent,
                  WXTYPE          eventType )
{
	wxKeyEvent thisEvent = wxKeyEvent ( eventType );

	PRBool result;
	keyEvent->GetCtrlKey ( &result );
	if ( result )
		thisEvent.m_controlDown = true;

	keyEvent->GetAltKey ( &result );
	if ( result )
		thisEvent.m_altDown = true;

	keyEvent->GetShiftKey ( &result );
	if ( result )
		thisEvent.m_shiftDown = true;

	keyEvent->GetMetaKey ( &result );
	if ( result )
		thisEvent.m_metaDown = true;

	PRUint32 rawCode;
	keyEvent->GetKeyCode ( &rawCode );
	thisEvent.m_keyCode = convertKeyCode ( rawCode );

	return thisEvent;
}

NS_IMPL_ADDREF ( wxMozillaBrowserChrome )
NS_IMPL_RELEASE ( wxMozillaBrowserChrome )

static NS_DEFINE_IID ( kWindowCID, NS_WINDOW_CID );

//NS_IMPL_ISUPPORTS1(wxMozillaBrowserChrome, nsIWebBrowserChrome)

NS_INTERFACE_MAP_BEGIN ( wxMozillaBrowserChrome )
NS_INTERFACE_MAP_ENTRY_AMBIGUOUS ( nsISupports, nsIWebBrowserChrome )
NS_INTERFACE_MAP_ENTRY ( nsIInterfaceRequestor )
NS_INTERFACE_MAP_ENTRY ( nsIWebBrowserChromeFocus )
NS_INTERFACE_MAP_ENTRY ( nsIWebBrowserChrome )
NS_INTERFACE_MAP_ENTRY ( nsIURIContentListener )
NS_INTERFACE_MAP_ENTRY ( nsIEmbeddingSiteWindow )
NS_INTERFACE_MAP_ENTRY ( nsIWebProgressListener )
NS_INTERFACE_MAP_ENTRY ( nsISupportsWeakReference )
NS_INTERFACE_MAP_ENTRY ( nsIContextMenuListener2 )
NS_INTERFACE_MAP_ENTRY ( nsIWindowCreator )
NS_INTERFACE_MAP_ENTRY ( nsIDOMMouseListener )
NS_INTERFACE_MAP_ENTRY ( nsIDOMKeyListener )
NS_INTERFACE_MAP_END


////NS_IMPL_ISUPPORTS1(wxMozillaBrowserChrome, nsISupportsWeakReference)


/* nsIWeakReference GetWeakReference (); */
NS_IMETHODIMP wxMozillaBrowserChrome::GetWeakReference(nsIWeakReference **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/**
 * Creates a new instance of the mozilla browser chrome
 *
 * @param Moz
 * 	Pointer to the parent MozillaBrowser class
 *
 * @return
 * 	New class instance
 */
wxMozillaBrowserChrome::wxMozillaBrowserChrome ( wxMozillaBrowser *Moz )
{
	//NS_INIT_REFCNT(); Now NS_INIT_ISUPPORTS?
	mMoz = Moz;
	m_mouseInWindow = false;
	//mNativeWindow
}

/**
 * Class destructor
 *
 */
wxMozillaBrowserChrome::~wxMozillaBrowserChrome()
{
	mMoz = NULL;
}

/**
 * Get interface
 *
 * @param aIID
 * 	Mozilla identifier
 * @param aInstancePtr
 * 	Instance pointer
 * @return
 * 	Netscape status
 */
NS_IMETHODIMP wxMozillaBrowserChrome::GetInterface ( const nsIID &aIID, void **aInstancePtr )
{
	if ( aIID.Equals ( NS_GET_IID ( nsIDOMWindow ) ) )
	{
		if ( mMoz->m_Mozilla->mWebBrowser )
			return mMoz->m_Mozilla->mWebBrowser->GetContentDOMWindow ( ( nsIDOMWindow ** ) aInstancePtr );
		return NS_ERROR_NOT_INITIALIZED;
	}

	return QueryInterface ( aIID, aInstancePtr );
}


NS_IMETHODIMP wxMozillaBrowserChrome::CreateChromeWindow ( nsIWebBrowserChrome *parent, PRUint32 chromeFlags, nsIWebBrowserChrome **_retval )
{
	bool showMenu;
	bool showToolbar;
	bool showStatusbar;

	if ( chromeFlags & nsIWebBrowserChrome::CHROME_MENUBAR )
		showMenu = TRUE;
	else
		showMenu = FALSE;

	if ( chromeFlags & nsIWebBrowserChrome::CHROME_TOOLBAR )
		showToolbar = TRUE;
	else
		showToolbar = FALSE;

	if ( chromeFlags & nsIWebBrowserChrome::CHROME_STATUSBAR )
		showStatusbar = TRUE;
	else
		showStatusbar = FALSE;

	wxMozillaWindow *mywin;
	if ( chromeFlags & nsIWebBrowserChrome::CHROME_WINDOW_POPUP )
		mywin = new wxMozillaWindow ( showMenu, showToolbar, showStatusbar, TRUE );
	else
		mywin = new wxMozillaWindow ( showMenu, showToolbar, showStatusbar, FALSE );
	mywin->Show ( TRUE );
////	*_retval = NS_STATIC_CAST(nsIWebBrowserChrome *, mywin->Mozilla->Chrome);
	*_retval = static_cast<nsIWebBrowserChrome*> ( mywin->Mozilla->Chrome );
	NS_ADDREF ( *_retval );

	return NS_OK;
}

/**
 * Change focus to next element
 *
 * @return
 * 	Netscape status
 */

NS_IMETHODIMP wxMozillaBrowserChrome::FocusNextElement()
{
	printf ( "FocusNextElement()" );
	return NS_ERROR_NOT_IMPLEMENTED;
}

/**
 * Change focus to previous element
 *
 * @return
 * 	Netscape status
 */
NS_IMETHODIMP wxMozillaBrowserChrome::FocusPrevElement()
{
	printf ( "FocusPrevElement()" );
	return NS_ERROR_NOT_IMPLEMENTED;
}

/*
 * Callback for progress change
 *
 * @param progress
 * 	Pointer to <code>nsIWebProgress</code> class
 * @param request
 * 	Pointer to <code>nsIRequest</code> class
 * @param curSelfProgress
 * 	Current self progress
 * @param maxSelfProgress
 * 	Maximum self progress
 * @param curTotalProgress
 * 	Current total progress
 * @param maxTotalProgress
 * 	Maximum total progress
 * @return
 * 	Netscape status
 */
NS_IMETHODIMP wxMozillaBrowserChrome::OnProgressChange ( nsIWebProgress *progress, nsIRequest *request, PRInt32 curSelfProgress, PRInt32 maxSelfProgress, PRInt32 curTotalProgress, PRInt32 maxTotalProgress )
{
	wxMozillaProgressEvent event ( mMoz );
	event.SetSelfCurrentProgress ( curSelfProgress );
	event.SetSelfMaxProgress ( maxSelfProgress );
	event.SetTotalCurrentProgress ( curTotalProgress );
	event.SetTotalMaxProgress ( maxTotalProgress );
	mMoz->GetEventHandler()->ProcessEvent ( event );
	return NS_OK;
}

/**
 * On state chanage
 *
 * @param webProgress
 * 	Pointer <code>nsIWebProgress</code> class
 * @param aRequest
 * 	Pointer to <code>nsIRequest</code> class
 * @param progressStateFlags
 * 	Progress state flags
 * @param status
 * 	Status
 * @return
 * 	Netscape status
 */
NS_IMETHODIMP wxMozillaBrowserChrome::OnStateChange ( nsIWebProgress *webProgress, nsIRequest *aRequest, PRUint32 progressStateFlags, PRUint32 status )
{
	/**
	 * Add wxWindows-style events
	 * @author <Yoric@users.sourceforge.net>
	 */

	int stateFlag = 0;
	if ( progressStateFlags & STATE_START )
		stateFlag |= wxMOZILLA_STATE_START;

	if ( progressStateFlags & STATE_REDIRECTING )
		stateFlag |= wxMOZILLA_STATE_REDIRECTING;

	if ( progressStateFlags & STATE_TRANSFERRING )
		stateFlag |= wxMOZILLA_STATE_TRANSFERRING;

	if ( progressStateFlags & STATE_NEGOTIATING )
		stateFlag |= wxMOZILLA_STATE_NEGOTIATING;

	if ( progressStateFlags & STATE_STOP )
		stateFlag |= wxMOZILLA_STATE_STOP;

	wxString loadURL;
	//get the URL that the state change applies to...
	nsCOMPtr<nsIChannel> channel ( do_QueryInterface ( aRequest ) );
	if ( channel )
	{
		nsresult rv;
		nsCOMPtr<nsIURI> uri;
		rv = channel->GetURI ( getter_AddRefs ( uri ) );
		if ( NS_SUCCEEDED ( rv ) )
		{
			nsCAutoString aURI;
			uri->GetSpec ( aURI );
			loadURL = wxString::FromAscii ( aURI.get() );
			//don't ask me WHY it does this, but sometimes the URL is a 'dummy' URL...
			if ( loadURL == _T ( "about:layout-dummy-request" ) )
				loadURL = _T ( "" );
		}
	}

	if ( stateFlag > 0 )
	{
		wxMozillaStateChangedEvent stateEvent ( mMoz );
		stateEvent.SetState ( stateFlag );
		stateEvent.SetURL ( loadURL );
		mMoz->GetEventHandler()->ProcessEvent ( stateEvent );
	}

	int securityFlag = 0;
	if ( progressStateFlags & STATE_IS_INSECURE )
		securityFlag |= wxMOZILLA_IS_INSECURE;

	if ( progressStateFlags & STATE_IS_BROKEN )
		securityFlag |= wxMOZILLA_IS_BROKEN;

	if ( progressStateFlags & STATE_IS_SECURE )
		securityFlag |= wxMOZILLA_IS_SECURE;

	if ( progressStateFlags & STATE_SECURE_HIGH )
		securityFlag |= wxMOZILLA_SECURE_HIGH;

	if ( progressStateFlags & STATE_SECURE_MED )
		securityFlag |= wxMOZILLA_SECURE_MED;

	if ( progressStateFlags & STATE_SECURE_LOW )
		securityFlag |= wxMOZILLA_SECURE_LOW;

	if ( securityFlag > 0 )
	{
		wxMozillaSecurityChangedEvent securityEvent ( mMoz );
		securityEvent.SetSecurity ( securityFlag );
		mMoz->GetEventHandler()->ProcessEvent ( securityEvent );
	}

	/**
	  * End of modifications
	*/
	if ( ( progressStateFlags & STATE_START ) && ( progressStateFlags & STATE_IS_DOCUMENT ) )
	{
		//Note: this is NOT where a BeforeLoad event should go... There

		//Ideally, we should implement nsIURIContentListener to fire BeforeLoad at appropriate times.

		wxMozillaBeforeLoadEvent myEvent ( mMoz );
		myEvent.SetURL ( loadURL );
		mMoz->GetEventHandler()->ProcessEvent ( myEvent );
		mMoz->m_isBusy = TRUE;
	}

	//testing this for now - STATE_IS_NETWORK maybe more appropriate...
	//when network activity stops, we know we're finished (down)loading. =)
	if ( ( progressStateFlags & STATE_STOP ) && ( progressStateFlags & STATE_IS_DOCUMENT ) )
	{
		wxMozillaLoadCompleteEvent completeEvent ( mMoz );
		mMoz->GetEventHandler()->ProcessEvent ( completeEvent );
		mMoz->m_isBusy = FALSE;

		//mMoz->m_status = "";
		//mMoz->OnStatusChange();

	}

	return NS_OK;
}

/**
 * On the location change
 *
 * @param webProgress
 * 	Pointer to <code>nsIWebProgress</code> class.
 * @param aRequest
 * 	Pointer to <code>nsIRequest</code> class.
 * @param location
 * 	Pointer to <code>nsIURI</code> class.
 * @return
 * 	Netscape status
 */
NS_IMETHODIMP wxMozillaBrowserChrome::OnLocationChange ( nsIWebProgress *webPRogress, nsIRequest *aRequest, nsIURI *location )
{
	mMoz->OnLocationChange();
	return NS_OK;
}

/**
 * On status changed
 *
 * @param webProgress
 * 	Pointer to <code>nsIWebProgress</code> class
 * @param aRequest
 * 	Pointer to <code>nsIRequest</code> class
 * @param aStatus
 * 	Status
 * @param aMessage
 * 	String of status
 * @return
 * 	Netscape status
 */
NS_IMETHODIMP wxMozillaBrowserChrome::OnStatusChange ( nsIWebProgress *webProgress, nsIRequest *aRequest, nsresult aStatus, const PRUnichar *aMessage )
{
	//const nsAFlatString& flat = PromiseFlatString(*aMessage);
	//const wxString myString = flat.get();
	nsCString aString;
	if ( aMessage )
		mMoz->m_status =
		    nsString_to_wxString ( nsString ( aMessage ), wxConvLocal );
	else
		mMoz->m_status = wxEmptyString;
	mMoz->OnStatusChange(); //pass the event to the UI
	//printf("OnStatusChange()");
	return NS_OK;
}

/**
 * On security settings changed
 *
 * @param aWebProgress
 * 	Pointer to <code>nsIWebProgress</code> class
 * @param aRequest
 * 	Pointer to <code>nsIRequest</code> class
 * @param state
 * 	State
 * @return
 * 	Netscape status
 */
NS_IMETHODIMP wxMozillaBrowserChrome::OnSecurityChange ( nsIWebProgress *aWebProgress, nsIRequest *aRequest, PRUint32 status )
{
	return NS_ERROR_NOT_IMPLEMENTED;
}

/**
 * Set status message
 *
 * @param statusType
 * 	Type of status
 * @param status
 * 	String containing status message
 * @return
 * 	Netscape status
 */
NS_IMETHODIMP wxMozillaBrowserChrome::SetStatus ( PRUint32 statusType, const PRUnichar *status )
{
	nsCString aString;
	if ( status )
		mMoz->m_status = nsString_to_wxString ( nsString ( status ), wxConvLocal );
	else
		mMoz->m_status = wxEmptyString;
	mMoz->OnStatusChange();
	return NS_OK;
}

/**
 * Get the web browser class
 *
 * @param aWebBrowser
 * 	Object to assign class to
 * @return
 * 	Netscape status
 */
NS_IMETHODIMP wxMozillaBrowserChrome::GetWebBrowser ( nsIWebBrowser **aWebBrowser )
{
	NS_ENSURE_ARG_POINTER ( aWebBrowser );
	NS_ENSURE_TRUE ( mMoz->m_Mozilla->mWebBrowser, NS_ERROR_NOT_INITIALIZED );
	*aWebBrowser = mMoz->m_Mozilla->mWebBrowser;
	NS_IF_ADDREF ( *aWebBrowser );
	return NS_OK;
}

/**
 * Set web browser
 *
 * @param aWebBrowser
 * 	Browser to assign to chrome
 * @return
 *	Netscape status
 */
NS_IMETHODIMP wxMozillaBrowserChrome::SetWebBrowser ( nsIWebBrowser * aWebBrowser )
{
	printf ( "NI: SetWebBrowser\n" );
	NS_ENSURE_ARG ( aWebBrowser );
	NS_ENSURE_TRUE ( mMoz->m_Mozilla->mWebBrowser, NS_ERROR_NOT_INITIALIZED );
	mMoz->m_Mozilla->mWebBrowser = aWebBrowser;
	return NS_OK;
}

/**
 * Get chrome flags
 *
 * @param aChromeFlags
 * @return
 * 	Netscape status
 */
NS_IMETHODIMP wxMozillaBrowserChrome::GetChromeFlags ( PRUint32 *aChromeFlags )
{
	return NS_ERROR_FAILURE;
}

/**
 * Set chrome flags
 *
 * @param aChromeFlags
 * 	Chrome flags to assign
 * @return
 * 	Netscape status
 */
NS_IMETHODIMP wxMozillaBrowserChrome::SetChromeFlags ( PRUint32 aChromeFlags )
{

	return NS_ERROR_FAILURE;
}

/**
 * Destroy the browser window
 *
 * @return
 * 	Netscape status
 */
NS_IMETHODIMP wxMozillaBrowserChrome::DestroyBrowserWindow()
{
	mMoz->GetParent()->Destroy();
	return NS_OK;
}

/**
 * Size browser to specified width and height
 *
 * @param aCX
 * 	Width
 * @param aXY
 * 	Height
 * @return
 * 	Netscape status
 */
NS_IMETHODIMP wxMozillaBrowserChrome::SizeBrowserTo ( PRInt32 aCX, PRInt32 aCY )
{
	printf ( "In size browser to..." );
	mMoz->SetSize ( aCX, aCY );
	if ( mMoz->GetParent() )
	{
		//if (!mMoz->GetParent()->IsShown()){
		//we're in a popup window
		//mMoz->GetParent()->SetClientSize(aCX, aCY);
		//      mMoz->GetParent()->Layout();
		//  mMoz->GetParent()->Show();
		//}
	}
	return NS_OK;
}

/**
 * Show as modal window
 *
 * @return
 *	Netscape status
 */
NS_IMETHODIMP wxMozillaBrowserChrome::ShowAsModal()
{
	printf ( "In show as modal..." );
	//wxMozillaWindow *mywin = new wxMozillaWindow(FALSE, FALSE, FALSE);
	mMoz->GetParent()->SetSize ( 300,300 );
	mMoz->GetParent()->Layout();
	//mywin->Show(TRUE);
	return NS_OK;
}

/**
 * Checks to determine if window is modal
 *
 * @param _retval
 * 	Boolean return value indicating modality
 * @return
 * 	Netscape status
 */
NS_IMETHODIMP wxMozillaBrowserChrome::IsWindowModal ( PRBool *_retval )
{
	*_retval = PR_FALSE;
	return NS_OK;
}

/**
 * Exits a modal event loop
 *
 * @param aStatus
 * 	Status of action
 * @return
 * 	Netscape status
 */
NS_IMETHODIMP wxMozillaBrowserChrome::ExitModalEventLoop ( nsresult aStatus )
{
	return NS_ERROR_NOT_IMPLEMENTED;
}

/**
 * Set window dimensions
 *
 * @param flags
 * 	Window flags
 * @param x
 * 	Top left x coordinate of window
 * @param y
 * 	Top left y coordinate of window
 * @param cx
 * 	Width of window
 * @param cy
 * 	Height of window
 * @return
 * 	Netscape status
 */
NS_IMETHODIMP wxMozillaBrowserChrome::SetDimensions ( PRUint32 flags, PRInt32 x, PRInt32 y, PRInt32 cx, PRInt32 cy )
{
	if ( mMoz )
	{
		if ( ( flags & nsIEmbeddingSiteWindow::DIM_FLAGS_POSITION ) &&
		        ( flags & ( nsIEmbeddingSiteWindow::DIM_FLAGS_SIZE_INNER |
		                    nsIEmbeddingSiteWindow::DIM_FLAGS_SIZE_OUTER ) ) )
		{
			mMoz->Move ( x,y );
			mMoz->SetSize ( cx, cy );
			//mMoz->SetPositionAndSize(x, y, cx, cy, PR_TRUE);
			return NS_OK;
		}
		else if ( flags & nsIEmbeddingSiteWindow::DIM_FLAGS_POSITION )
		{
			mMoz->Move ( x, y );
			return NS_OK;
		}
		else if ( flags & ( nsIEmbeddingSiteWindow::DIM_FLAGS_SIZE_INNER |
		                    nsIEmbeddingSiteWindow::DIM_FLAGS_SIZE_OUTER ) )
		{
			printf ( "In size..." );
			mMoz->SetSize ( x, y );
			return NS_OK;
		}

		return NS_ERROR_INVALID_ARG;
	}
	else
	{
		return NS_ERROR_INVALID_ARG;
	}
}

/**
 * Get window dimensions
 *
 * @param flags
 * 	Browser flags
 * @param x
 * 	Top left x coordinate of window
 * @param y
 * 	Top left y coordinate of window
 * @param cx
 * 	Width of window
 * @param cy
 * 	Height of window
 * @return
 * 	Netscape status
 */
NS_IMETHODIMP wxMozillaBrowserChrome::GetDimensions ( PRUint32 flags, PRInt32 *x, PRInt32 *y, PRInt32 *cx, PRInt32 *cy )
{
	wxSize mysize;
	wxPoint mypoint;
	mysize = mMoz->GetSize();
	mypoint = mMoz->GetPosition();
	//caller will pass nsnull if they do not want the value
	if ( x != nsnull )
		*x = mypoint.x;
	if ( y != nsnull )
		*y = mypoint.y;
	if ( cx != nsnull )
		*cx = mysize.x;
	if ( cy != nsnull )
		*cy = mysize.y;


	return NS_OK;
}

/**
 * Set focus to window
 *
 * @return
 *	Netscape status
 */
NS_IMETHODIMP wxMozillaBrowserChrome::SetFocus()
{
	mMoz->SetFocus();
	return NS_OK;
}

/**
 * Check for visibility of window
 *
 * @param Vis
 * 	Pointer to boolean
 * @return
 * 	Netscape status
 */
NS_IMETHODIMP wxMozillaBrowserChrome::GetVisibility ( PRBool *Vis )
{
	if ( mMoz->IsShown() )
		*Vis = PR_TRUE;
	else
		*Vis = PR_FALSE;
	return NS_OK;
}

/**
 * Set visibility of window
 *
 * @param Vis
 * 	Show window if true, otherwise hide
 * @return
 * 	Netscape status
 */
NS_IMETHODIMP wxMozillaBrowserChrome::SetVisibility ( PRBool Vis )
{
	if ( Vis )
		mMoz->Show ( TRUE );
	else
		mMoz->Show ( FALSE );
	return NS_OK;
}

/**
 * Get title of browser window
 *
 * @param title
 * 	Pointer to string to contain title
 * @return
 * 	Netscape status
 */
NS_IMETHODIMP wxMozillaBrowserChrome::GetTitle ( PRUnichar **title )
{
	NS_ENSURE_ARG_POINTER ( title );
	nsString tmp = wxString_to_nsString ( mMoz->GetTitle(), wxConvLocal );

	*title = ToNewUnicode ( tmp );

	return NS_OK;
}

/**
 * Set title of browser window
 *
 * @param title
 * 	String to set window title to
 * @return
 * 	Netscape status
 */
NS_IMETHODIMP wxMozillaBrowserChrome::SetTitle ( const PRUnichar *title )
{
	NS_ENSURE_ARG_POINTER ( title );
	nsCString aString;
	wxString wxtitle;
	if ( title )
		wxtitle = nsString_to_wxString ( nsString ( title ), wxConvLocal );
	mMoz->SetTitle ( wxtitle );

	wxMozillaTitleChangedEvent event ( mMoz );
	event.SetTitle ( wxtitle );
	mMoz->GetEventHandler()->ProcessEvent ( event );

	return NS_OK;
}

/**
 * Get pointer to site window
 *
 * @param aSiteWindow
 * @return
 * 	Netscape status
 */
NS_IMETHODIMP wxMozillaBrowserChrome::GetSiteWindow ( void **aSiteWindow )
{
	NS_ENSURE_ARG_POINTER ( aSiteWindow );
	//wxMozillaBrowser is the 'native' control for wxWindows
	//GetHWND() or GetHandle() can always be used to get the platform native handles
	*aSiteWindow = mMoz;
	return NS_OK;
}

/* nsIURIContentListener */
NS_IMETHODIMP wxMozillaBrowserChrome::OnStartURIOpen ( nsIURI *aURI, PRBool *_retval )
{
	wxMozillaBeforeLoadEvent myEvent ( mMoz );
	nsCAutoString aString;
	aURI->GetSpec ( aString );
	myEvent.SetURL ( wxString::FromAscii ( aString.get() ) );

	mMoz->GetEventHandler()->ProcessEvent ( myEvent );

	if ( myEvent.IsCancelled() )
		*_retval = PR_FALSE;
	else
		*_retval = PR_TRUE;
	return NS_OK;
}

NS_IMETHODIMP wxMozillaBrowserChrome::DoContent ( const char *aContentType, PRBool aIsContentPreferred, nsIRequest *aRequest, nsIStreamListener **aContentHandler, PRBool *_retval )
{
	return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP wxMozillaBrowserChrome::IsPreferred ( const char *aContentType, char **aDesiredContentType, PRBool *_retval )
{
	return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP wxMozillaBrowserChrome::CanHandleContent ( const char *aContentType, PRBool aIsContentPreferred, char **aDesiredContentType, PRBool *_retval )
{
	return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP wxMozillaBrowserChrome::GetLoadCookie ( nsISupports * *aLoadCookie )
{
	return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP wxMozillaBrowserChrome::SetLoadCookie ( nsISupports *aLoadCookie )
{
	return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP wxMozillaBrowserChrome::GetParentContentListener ( nsIURIContentListener * *aParentContentListener )
{
	return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP wxMozillaBrowserChrome::SetParentContentListener ( nsIURIContentListener *aParentContentListener )
{
	return NS_ERROR_NOT_IMPLEMENTED;
}

/*
NS_IMETHODIMP wxMozillaBrowserChrome::OnShowContextMenu(PRUint32 aContextFlags, nsIDOMEvent *aEvent, nsIDOMNode *aNode)
*/
NS_IMETHODIMP wxMozillaBrowserChrome::OnShowContextMenu ( PRUint32 aContextFlags, nsIContextMenuInfo *aInfo )
{
	wxMozillaRightClickEvent thisEvent = wxMozillaRightClickEvent ( mMoz );
	int context;
	nsCOMPtr<nsIDOMEvent> myEvent;
	aInfo->GetMouseEvent ( getter_AddRefs ( myEvent ) );
	nsCOMPtr <nsIDOMMouseEvent> mouseEvent;
	mouseEvent = do_QueryInterface ( myEvent );
	//mouseEvent->GetClientX doesn't work in frames - so we get the screen
	//coordinates and have wxMozilla convert them to client coord.
	mouseEvent->GetScreenX ( &thisEvent.m_x );
	mouseEvent->GetScreenY ( &thisEvent.m_y );

	mMoz->ScreenToClient ( &thisEvent.m_x, &thisEvent.m_y );
	wxPoint myPos = mMoz->GetPosition();
	thisEvent.m_x += myPos.x;
	thisEvent.m_y += myPos.y;

	if ( aContextFlags & nsIContextMenuListener2::CONTEXT_DOCUMENT )
	{
		//just check for background image and pass to the handler
		context |= wxMOZILLA_CONTEXT_DOCUMENT;
		if ( aContextFlags & nsIContextMenuListener2::CONTEXT_BACKGROUND_IMAGE )
		{
			context |= wxMOZILLA_CONTEXT_BACKGROUND_IMAGE;
			nsCOMPtr<nsIURI> imgURI;
			aInfo->GetBackgroundImageSrc ( getter_AddRefs ( imgURI ) );
			nsCString aString;
			imgURI->GetSpec ( aString );
			thisEvent.SetBackgroundImageSrc ( wxString::FromAscii ( aString.get() ) );
		}
	}
	else if ( aContextFlags & nsIContextMenuListener2::CONTEXT_TEXT )
	{
		//set the context and leave - embedder can use "GetSelection" to get text
		context |= wxMOZILLA_CONTEXT_TEXT;
	}
	else if ( aContextFlags & nsIContextMenuListener2::CONTEXT_LINK )
	{
		context |= wxMOZILLA_CONTEXT_LINK;
		nsAutoString urlString;
		nsresult rv = aInfo->GetAssociatedLink ( urlString );
		if ( NS_FAILED ( rv ) )
			return NS_OK;
		thisEvent.SetLink ( nsString_to_wxString ( urlString, wxConvISO8859_1 ) );

		nsCOMPtr<nsIURI> imgURI;
		aInfo->GetImageSrc ( getter_AddRefs ( imgURI ) );
		if ( imgURI )
		{
			nsCString aString;
			imgURI->GetSpec ( aString );
			thisEvent.SetImageSrc ( wxString::FromAscii ( aString.get() ) );
		}
	}
	else if ( aContextFlags & nsIContextMenuListener2::CONTEXT_IMAGE )
	{
		context |= wxMOZILLA_CONTEXT_IMAGE;
		nsCOMPtr<nsIURI> imgURI;
		aInfo->GetImageSrc ( getter_AddRefs ( imgURI ) );
		if ( imgURI )
		{
			nsCString aString;
			imgURI->GetSpec ( aString );
			thisEvent.SetImageSrc ( wxString::FromAscii ( aString.get() ) );
		}
	}
	thisEvent.SetContext ( context );

	mMoz->GetEventHandler()->ProcessEvent ( thisEvent );
	return NS_OK;
}

NS_IMETHODIMP
wxMozillaBrowserChrome::MouseDown ( nsIDOMEvent* aDOMEvent )
{
	nsCOMPtr<nsIDOMMouseEvent> mouseEvent ( do_QueryInterface ( aDOMEvent ) );
	if ( !mouseEvent )
		return NS_OK;

	WXTYPE eventTypes[] = { wxEVT_LEFT_DOWN, wxEVT_MIDDLE_DOWN, wxEVT_RIGHT_DOWN };
	wxMouseEvent thisEvent ( convertMouseEvent ( mMoz, mouseEvent, eventTypes ) );

	mMoz->GetEventHandler()->ProcessEvent ( thisEvent );

	return NS_OK;
}

NS_IMETHODIMP
wxMozillaBrowserChrome::MouseUp ( nsIDOMEvent* aDOMEvent )
{
	nsCOMPtr<nsIDOMMouseEvent> mouseEvent ( do_QueryInterface ( aDOMEvent ) );
	if ( !mouseEvent )
		return NS_OK;

	WXTYPE eventTypes[] = { wxEVT_LEFT_UP, wxEVT_MIDDLE_UP, wxEVT_RIGHT_UP };
	wxMouseEvent thisEvent ( convertMouseEvent ( mMoz, mouseEvent, eventTypes ) );

	mMoz->GetEventHandler()->ProcessEvent ( thisEvent );

	return NS_OK;
}

NS_IMETHODIMP
wxMozillaBrowserChrome::MouseClick ( nsIDOMEvent* aDOMEvent )
{
	nsCOMPtr<nsIDOMMouseEvent> mouseEvent ( do_QueryInterface ( aDOMEvent ) );
	if ( !mouseEvent )
		return NS_OK;

	WXTYPE eventTypes[] = { wxEVT_LEFT_UP, wxEVT_MIDDLE_UP, wxEVT_RIGHT_UP };
	wxMouseEvent thisEvent ( convertMouseEvent ( mMoz, mouseEvent, eventTypes ) );

	mMoz->GetEventHandler()->ProcessEvent ( thisEvent );

	return NS_OK;
}

NS_IMETHODIMP
wxMozillaBrowserChrome::MouseDblClick ( nsIDOMEvent* aDOMEvent )
{
	nsCOMPtr<nsIDOMMouseEvent> mouseEvent ( do_QueryInterface ( aDOMEvent ) );
	if ( !mouseEvent )
		return NS_OK;

	WXTYPE eventTypes[] = { wxEVT_LEFT_DCLICK, wxEVT_MIDDLE_DCLICK, wxEVT_RIGHT_DCLICK };
	wxMouseEvent thisEvent ( convertMouseEvent ( mMoz, mouseEvent, eventTypes ) );

	mMoz->GetEventHandler()->ProcessEvent ( thisEvent );

	return NS_OK;
}

NS_IMETHODIMP
wxMozillaBrowserChrome::MouseOver ( nsIDOMEvent* aDOMEvent )
{
	nsCOMPtr<nsIDOMMouseEvent> mouseEvent ( do_QueryInterface ( aDOMEvent ) );
	if ( !mouseEvent )
		return NS_OK;

	wxMouseEvent thisEvent ( convertMouseEvent ( mMoz, mouseEvent, wxEVT_MOTION ) );

	if ( !m_mouseInWindow )
	{
		m_mouseInWindow = true;

		wxMouseEvent thatEvent ( thisEvent );
		thatEvent.m_eventType = wxEVT_ENTER_WINDOW;
		mMoz->GetEventHandler()->ProcessEvent ( thatEvent );
	}

	mMoz->GetEventHandler()->ProcessEvent ( thisEvent );

	return NS_OK;
}

NS_IMETHODIMP
wxMozillaBrowserChrome::MouseOut ( nsIDOMEvent* aDOMEvent )
{
	m_mouseInWindow = false;

	nsCOMPtr<nsIDOMMouseEvent> mouseEvent ( do_QueryInterface ( aDOMEvent ) );
	if ( !mouseEvent )
		return NS_OK;

	wxMouseEvent thisEvent ( convertMouseEvent ( mMoz, mouseEvent, wxEVT_LEAVE_WINDOW ) );

	mMoz->GetEventHandler()->ProcessEvent ( thisEvent );

	return NS_OK;
}

NS_IMETHODIMP wxMozillaBrowserChrome::KeyDown ( nsIDOMEvent* aDOMEvent )
{
	nsCOMPtr<nsIDOMKeyEvent> keyEvent ( do_QueryInterface ( aDOMEvent ) );
	if ( !keyEvent )
		return NS_OK;

	wxKeyEvent thisEvent ( convertKeyEvent ( keyEvent, wxEVT_KEY_DOWN ) );

	mMoz->GetEventHandler()->ProcessEvent ( thisEvent );

	return NS_OK;
}

NS_IMETHODIMP wxMozillaBrowserChrome::KeyUp ( nsIDOMEvent* aDOMEvent )
{
	nsCOMPtr<nsIDOMKeyEvent> keyEvent ( do_QueryInterface ( aDOMEvent ) );
	if ( !keyEvent )
		return NS_OK;

	wxKeyEvent thisEvent ( convertKeyEvent ( keyEvent, wxEVT_KEY_UP ) );

	mMoz->GetEventHandler()->ProcessEvent ( thisEvent );

	return NS_OK;
}

NS_IMETHODIMP wxMozillaBrowserChrome::KeyPress ( nsIDOMEvent* aDOMEvent )
{
	nsCOMPtr<nsIDOMKeyEvent> keyEvent ( do_QueryInterface ( aDOMEvent ) );
	if ( !keyEvent )
		return NS_OK;

	wxKeyEvent thisEvent ( convertKeyEvent ( keyEvent, wxEVT_CHAR ) );

	mMoz->GetEventHandler()->ProcessEvent ( thisEvent );

	return NS_OK;
}

NS_IMETHODIMP wxMozillaBrowserChrome::HandleEvent ( nsIDOMEvent *event )
{
	return NS_ERROR_NOT_IMPLEMENTED;
}
