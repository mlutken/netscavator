#ifndef __WX_MOZILLA_EVENTS_H__
#define __WX_MOZILLA_EVENTS_H__
/*
 * wxWindows Mozilla Component
 * Copyright 2002 (c) Myers Carpenter. All Rights Reserved.
 * 
 * Author: Kevin Ollivier
 * Created: June 5, 2003
 * Licence: wxWindows License
 */

/* wxwindow includes */
#include "wx/defs.h"
#include "wx/window.h"

//wxMozilla states - for EVT_MOZILLA_STATE_CHANGE
enum {
	wxMOZILLA_STATE_START = 1,
	wxMOZILLA_STATE_NEGOTIATING = 2,
	wxMOZILLA_STATE_REDIRECTING = 4,
	wxMOZILLA_STATE_TRANSFERRING = 8,
	wxMOZILLA_STATE_STOP = 16,
	wxMOZILLA_STATE_IS_REQUEST = 32,
	wxMOZILLA_STATE_IS_DOCUMENT = 64,
	wxMOZILLA_STATE_IS_NETWORK = 128,
	wxMOZILLA_STATE_IS_WINDOW = 256
};

//wxMozilla security modes - for EVT_MOZILLA_SECURITY_CHANGE
enum {
	wxMOZILLA_IS_INSECURE = 1,
	wxMOZILLA_IS_BROKEN = 2,
	wxMOZILLA_IS_SECURE = 4,
	wxMOZILLA_SECURE_HIGH = 8,
	wxMOZILLA_SECURE_MED = 16,
	wxMOZILLA_SECURE_LOW = 32
};

//wxMozilla right-click event contexts
enum {
	wxMOZILLA_CONTEXT_DOCUMENT = 1,
	wxMOZILLA_CONTEXT_LINK = 2,
	wxMOZILLA_CONTEXT_TEXT = 4,
	wxMOZILLA_CONTEXT_BACKGROUND_IMAGE = 8,
	wxMOZILLA_CONTEXT_IMAGE = 16
};

class wxMozillaBeforeLoadEvent : public wxCommandEvent
{
    DECLARE_DYNAMIC_CLASS( wxMozillaBeforeLoadEvent )

public:
	wxString GetURL() { return m_url; }
	void SetURL(const wxString& newURL) { m_url = newURL; }
	void Cancel() { m_cancelled = TRUE; }
	bool IsCancelled() { return m_cancelled; }

    wxMozillaBeforeLoadEvent( wxWindow* win = (wxWindow*) NULL );
	wxEvent *Clone(void) const { return new wxMozillaBeforeLoadEvent(*this); }

protected:
	wxString m_url;
	bool m_cancelled;
};

/*event class definitions*/
class wxMozillaLinkChangedEvent : public wxCommandEvent
{
    DECLARE_DYNAMIC_CLASS( wxMozillaLinkChangedEvent )

public:
	wxString GetNewURL() { return m_newURL; }
	bool CanGoBack() { return m_canGoBack; }
	bool CanGoForward() { return m_canGoForward; }

	void SetNewURL(const wxString& newurl) { m_newURL = newurl; }
	void SetCanGoBack(bool goback) { m_canGoBack = goback; }
	void SetCanGoForward(bool goforward) { m_canGoForward = goforward; }

    wxMozillaLinkChangedEvent( wxWindow* win = (wxWindow*) NULL );
	wxEvent *Clone(void) const { return new wxMozillaLinkChangedEvent(*this); }
protected:
	wxString m_newURL;
	bool m_canGoBack;
	bool m_canGoForward;
};

class wxMozillaStateChangedEvent : public wxCommandEvent
{
    DECLARE_DYNAMIC_CLASS( wxMozillaStateChangedEvent )

public:
	int GetState() { return m_state; }
	void SetState(const int state) { m_state = state; }
	wxString GetURL() { return m_url; }
	void SetURL(const wxString& url) { m_url = url; }

    wxMozillaStateChangedEvent( wxWindow* win = (wxWindow*) NULL );
	wxEvent *Clone(void) const { return new wxMozillaStateChangedEvent(*this); }

protected:
	int m_state;
	wxString m_url;
};

class wxMozillaSecurityChangedEvent : public wxCommandEvent
{
    DECLARE_DYNAMIC_CLASS( wxMozillaSecurityChangedEvent )

public:
	int GetSecurity() { return m_security; }
	void SetSecurity(const int security) { m_security = security; }

    wxMozillaSecurityChangedEvent( wxWindow* win = (wxWindow*) NULL );
	wxEvent *Clone(void) const { return new wxMozillaSecurityChangedEvent(*this); }

protected:
	int m_security;
};

class wxMozillaLoadCompleteEvent : public wxCommandEvent
{
    DECLARE_DYNAMIC_CLASS( wxMozillaLoadCompleteEvent )

public:

    wxMozillaLoadCompleteEvent( wxWindow* win = (wxWindow*) NULL );
	wxEvent *Clone(void) const { return new wxMozillaLoadCompleteEvent(*this); }
};


class wxMozillaStatusChangedEvent : public wxCommandEvent
{
    DECLARE_DYNAMIC_CLASS( wxMozillaStatusChangedEvent )

public:
	wxString GetStatusText() { return m_statusText; }
	bool IsBusy() { return m_isBusy; }
	void SetStatusText(const wxString& status) { m_statusText = status; }
	void SetBusy(bool isbusy) { m_isBusy = isbusy; }

    wxMozillaStatusChangedEvent( wxWindow* win = (wxWindow*) NULL );
	wxEvent *Clone(void) const { return new wxMozillaStatusChangedEvent(*this); }

protected:
	wxString m_statusText;
	bool m_isBusy;
};

class wxMozillaTitleChangedEvent : public wxCommandEvent
{
    DECLARE_DYNAMIC_CLASS( wxMozillaTitleChangedEvent )

public:
	wxString GetTitle() { return m_title; }
	void SetTitle(const wxString& title) { m_title = title; }

    wxMozillaTitleChangedEvent( wxWindow* win = (wxWindow*) NULL );
	wxEvent *Clone(void) const { return new wxMozillaTitleChangedEvent(*this); }

protected:
	wxString m_title;
};

class wxMozillaProgressEvent : public wxCommandEvent
{
    DECLARE_DYNAMIC_CLASS( wxMozillaProgressEvent )

public:
	int GetSelfCurrentProgress() { return m_curSelfProgress; }
	void SetSelfCurrentProgress(int progress) { m_curSelfProgress = progress; }
	
	int GetSelfMaxProgress() { return m_maxSelfProgress; }
	void SetSelfMaxProgress(int progress) { m_maxSelfProgress = progress; }
	
	int GetTotalCurrentProgress() { return m_curTotalProgress; }
	void SetTotalCurrentProgress(int progress) { m_curTotalProgress = progress; }
	
	int GetTotalMaxProgress() { return m_maxTotalProgress; }
	void SetTotalMaxProgress(int progress) { m_maxTotalProgress = progress; }

    wxMozillaProgressEvent( wxWindow* win = (wxWindow*) NULL );
	wxEvent *Clone(void) const { return new wxMozillaProgressEvent(*this); }

protected: 
	    /// Progress of current request. maxSelfProgress is -1 if unknown 
    int m_curSelfProgress, m_maxSelfProgress;
    /// Progress of all monitored requests. maxSelfProgress is -1 if unknown 
    int m_curTotalProgress, m_maxTotalProgress;
};

class wxMozillaRightClickEvent : public wxMouseEvent
{
    DECLARE_DYNAMIC_CLASS( wxMozillaRightClickEvent )

public:
	//wxString statusText;
	bool IsBusy() { return m_isBusy; }
	void SetBusy(bool isbusy) { m_isBusy = isbusy; }

	wxString GetBackgroundImageSrc() { return m_backgroundImage; }
	void SetBackgroundImageSrc(const wxString& name) { m_backgroundImage = name; }

	wxString GetText() { return m_text; }
	void SetText(const wxString& text) { m_text = text; }

	wxString GetImageSrc() { return m_imageSrc; }
	void SetImageSrc(const wxString& src) { m_imageSrc = src; }

	wxString GetLink() { return m_link; }
	void SetLink(const wxString& link) { m_link = link; }

	int GetContext() { return m_context; }
	void SetContext(int context) { m_context = context; }

    wxMozillaRightClickEvent( wxWindow* win = (wxWindow*) NULL );
	wxMozillaRightClickEvent( wxEventType commandType, int id ); 
	wxEvent *Clone(void) const { return new wxMozillaRightClickEvent(*this); }
    //void CopyObject( wxObject& obj ) const { wxEvent::CopyObject( obj_d );}
protected:
	wxString m_backgroundImage;
	wxString m_text;
	wxString m_imageSrc;
	wxString m_link;
	bool m_isBusy;
	int m_context;

};

/**
 * @class wxMozillaLoadEvent
 * @author David Teller <Yoric@users.sourceforge.net>
 * 
 * Load status events
 
class wxMozillaLoadEvent : public wxCommandEvent
{
  DECLARE_DYNAMIC_CLASS( wxMozillaLoadEvent )
  public:
  bool isStart;
  bool isRedirecting;
  bool isTransferring;
  bool isNegociating;
  bool isTerminated;
 
  bool isRequest;
  bool isDocument;
  bool isNetwork;
  bool isWindow;
  
  bool isInsecure;
  bool isBroken;
  bool isSecure;
  bool isSecureHigh;
  bool isSecureMed;
  bool isSecureLow;
  wxMozillaLoadEvent(wxWindow* win = (wxWindow*) NULL);
  wxMozillaLoadEvent(wxEventType commandType, int id );
  wxEvent *Clone() const
    {
      return new wxMozillaLoadEvent(*this);
    }
};
*/

typedef void (wxEvtHandler::*wxMozillaBeforeLoadEventFunction)(wxMozillaBeforeLoadEvent&);
typedef void (wxEvtHandler::*wxMozillaLinkChangedEventFunction)(wxMozillaLinkChangedEvent&);
typedef void (wxEvtHandler::*wxMozillaStateChangedEventFunction)(wxMozillaStateChangedEvent&);
typedef void (wxEvtHandler::*wxMozillaSecurityChangedEventFunction)(wxMozillaSecurityChangedEvent&);
typedef void (wxEvtHandler::*wxMozillaStatusChangedEventFunction)(wxMozillaStatusChangedEvent&);
typedef void (wxEvtHandler::*wxMozillaTitleChangedEventFunction)(wxMozillaTitleChangedEvent&);
typedef void (wxEvtHandler::*wxMozillaLoadCompleteEventFunction)(wxMozillaLoadCompleteEvent&);
typedef void (wxEvtHandler::*wxMozillaProgressEventFunction)(wxMozillaProgressEvent&);
typedef void (wxEvtHandler::*wxMozillaRightClickEventFunction)(wxMozillaRightClickEvent&);
/**
 * @author David Teller <Yoric@users.sourceforge.net>
 * 
 * Load status events
 */
//typedef void (wxEvtHandler::*wxMozillaLoadEventFunction)(wxMozillaLoadEvent&);

BEGIN_DECLARE_EVENT_TYPES()
    DECLARE_LOCAL_EVENT_TYPE(wxEVT_MOZILLA_BEFORE_LOAD, -1)
    DECLARE_LOCAL_EVENT_TYPE(wxEVT_MOZILLA_URL_CHANGED, -1)
	DECLARE_LOCAL_EVENT_TYPE(wxEVT_MOZILLA_STATE_CHANGED, -1)
	DECLARE_LOCAL_EVENT_TYPE(wxEVT_MOZILLA_SECURITY_CHANGED, -1)
	DECLARE_LOCAL_EVENT_TYPE(wxEVT_MOZILLA_STATUS_CHANGED, -1)
	DECLARE_LOCAL_EVENT_TYPE(wxEVT_MOZILLA_TITLE_CHANGED, -1)
	DECLARE_LOCAL_EVENT_TYPE(wxEVT_MOZILLA_LOAD_COMPLETE, -1)
	DECLARE_LOCAL_EVENT_TYPE(wxEVT_MOZILLA_PROGRESS, -1)
	DECLARE_LOCAL_EVENT_TYPE(wxEVT_MOZILLA_RIGHT_CLICK, -1)
	/**
 * @author David Teller <Yoric@users.sourceforge.net>
 * 
 * Load status events
 */
  //   DECLARE_EVENT_TYPE(wxEVT_MOZILLA_LOAD_EVENT,-1)
END_DECLARE_EVENT_TYPES()

#define EVT_MOZILLA_BEFORE_LOAD(func) \
            DECLARE_EVENT_TABLE_ENTRY( wxEVT_MOZILLA_BEFORE_LOAD, \
                            -1,                       \
                            -1,                       \
                            (wxObjectEventFunction)   \
                            (wxMozillaBeforeLoadEventFunction) & func, \
                            (wxObject *) NULL ),

#define EVT_MOZILLA_URL_CHANGED(func) \
            DECLARE_EVENT_TABLE_ENTRY( wxEVT_MOZILLA_URL_CHANGED, \
                            -1,                       \
                            -1,                       \
                            (wxObjectEventFunction)   \
                            (wxMozillaLinkChangedEventFunction) & func, \
                            (wxObject *) NULL ),

#define EVT_MOZILLA_STATE_CHANGED(func) \
            DECLARE_EVENT_TABLE_ENTRY( wxEVT_MOZILLA_STATE_CHANGED, \
                            -1,                       \
                            -1,                       \
                            (wxObjectEventFunction)   \
                            (wxMozillaStateChangedEventFunction) & func, \
                            (wxObject *) NULL ),

#define EVT_MOZILLA_SECURITY_CHANGED(func) \
            DECLARE_EVENT_TABLE_ENTRY( wxEVT_MOZILLA_SECURITY_CHANGED, \
                            -1,                       \
                            -1,                       \
                            (wxObjectEventFunction)   \
                            (wxMozillaSecurityChangedEventFunction) & func, \
                            (wxObject *) NULL ),

#define EVT_MOZILLA_STATUS_CHANGED(func) \
            DECLARE_EVENT_TABLE_ENTRY( wxEVT_MOZILLA_STATUS_CHANGED, \
                            -1,                       \
                            -1,                       \
                            (wxObjectEventFunction)   \
                            (wxMozillaStatusChangedEventFunction) & func, \
                            (wxObject *) NULL ),

#define EVT_MOZILLA_TITLE_CHANGED(func) \
            DECLARE_EVENT_TABLE_ENTRY( wxEVT_MOZILLA_TITLE_CHANGED, \
                            -1,                       \
                            -1,                       \
                            (wxObjectEventFunction)   \
                            (wxMozillaTitleChangedEventFunction) & func, \
                            (wxObject *) NULL ),

#define EVT_MOZILLA_LOAD_COMPLETE(func) \
            DECLARE_EVENT_TABLE_ENTRY( wxEVT_MOZILLA_LOAD_COMPLETE, \
                            -1,                       \
                            -1,                       \
                            (wxObjectEventFunction)   \
                            (wxMozillaLoadCompleteEventFunction) & func, \
                            (wxObject *) NULL ),

#define EVT_MOZILLA_PROGRESS(func) \
            DECLARE_EVENT_TABLE_ENTRY( wxEVT_MOZILLA_PROGRESS, \
                            -1,                       \
                            -1,                       \
                            (wxObjectEventFunction)   \
                            (wxMozillaProgressEventFunction) & func, \
                            (wxObject *) NULL ),

#define EVT_MOZILLA_RIGHT_CLICK(func) \
            DECLARE_EVENT_TABLE_ENTRY( wxEVT_MOZILLA_RIGHT_CLICK, \
                            -1,                       \
                            -1,                       \
                            (wxObjectEventFunction)   \
                            (wxMozillaRightClickEventFunction) & func, \
                            (wxObject *) NULL ),
							
/**
 * @author David Teller <Yoric@users.sourceforge.net>
 * 
 * Load status events
 
#define EVT_MOZILLA_LOAD_EVENT(func) \
            DECLARE_EVENT_TABLE_ENTRY( wxEVT_MOZILLA_LOAD_EVENT, \
                            -1,                       \
                            -1,                       \
                            (wxObjectEventFunction)   \
                            (wxMozillaLoadEventFunction) & func, \
                            (wxObject *) NULL ),
*/
#endif
