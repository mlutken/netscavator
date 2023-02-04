/////////////////////////////////////////////////////////////////////////////
// Name:        mozilla.i
// Purpose:     Mozilla in a wxWindow
//
// Author:      Robin Dunn / Kevin Ollivier
//
// Created:     28-Feb-2003
// RCS-ID:      $Id: mozilla.i,v 1.22 2005/05/17 21:19:33 vaclavslavik Exp $
// Copyright:   (c) 2001 by Total Control Software
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////


%module mozilla

%{
#include "wxPython.h"
#include "wxMozillaBrowser.h"
#include "wxMozillaWindow.h"
#include "wxMozilla.h"
#include "pyistream.h"
%}

//---------------------------------------------------------------------------

%include typemaps.i
%include my_typemaps.i

%extern wx.i
%extern windows.i
%extern _defs.i
%extern misc.i
%extern events.i
%extern streams.i

%pragma(python) code = "import wx"

//---------------------------------------------------------------------------

%{
    // Put some wx default wxChar* values into wxStrings.
    DECLARE_DEF_STRING(PanelNameStr);
%}

const int wxMOZ_MAJOR_VERSION, wxMOZ_MINOR_VERSION, wxMOZ_RELEASE_NUMBER;

class wxMozillaBrowser : public wxWindow 
{
public:
	wxMozillaBrowser(wxWindow *parent, wxWindowID id,
		const wxPoint &pos = wxDefaultPosition,
		const wxSize &size = wxDefaultSize,
		long style = 0,
        	const wxString &name = wxPyPanelNameStr);
	//virtual ~wxMozillaBrowser();

	bool Create(wxWindow *parent, wxWindowID id,
		const wxPoint &pos = wxDefaultPosition,
		const wxSize &size = wxDefaultSize,
		long style = 0,
	       	const wxString &name = wxPyPanelNameStr);

	virtual bool LoadURL(const wxString &location);
	wxString GetURL();

	bool SavePage(const wxString &filename, bool saveFiles=TRUE);
	bool IsBusy();
	bool GoBack();
	bool CanGoBack();
	bool GoForward();
	bool CanGoForward();
	bool Stop();
	bool Reload();
	bool Find(const wxString &searchString, bool matchCase = FALSE, bool matchWholeWord = FALSE, bool wrapAround = TRUE, bool searchBackwards = FALSE);
	bool FindNext();
	wxString GetStatus();
	wxString GetSelection();
	void Copy();
	void SelectAll();
	void SelectNone();
	
	void UpdateBaseURI();
	void MakeEditable(bool enable=TRUE);
	void InsertHTML(wxString &html);
	bool IsEditable();
	void EditCommand(const wxString &cmdId, const wxString& value = "");
    bool GetCommandState(const wxString &command, const wxString &state);
    wxString GetStateAttribute(wxString &command);
    bool IsElementInSelection(wxString &element);
    bool SelectElement(wxString &element);
    wxString GetElementAttribute(wxString& tagName, wxString &attrName);
    void SetElementAttribute(wxString &attrName, wxString &attrValue);
    bool SetPage(const wxString &data);
    wxString GetPage();
    bool SetZoom(float level);
};

class wxMozillaWindow: public wxFrame
{
public:
	wxMozillaWindow(bool showMenu = TRUE, bool showToolbar = TRUE, bool showStatusbar = TRUE);
	wxMozillaBrowser *Mozilla;
};

class wxMozillaSettings
{
public:
    static bool SetProfilePath(const wxString &path);
    static wxString GetProfilePath() { return ms_profilePath; }
    
	static void SetMozillaPath(const wxString &path);
    static wxString GetMozillaPath() { return ms_mozillaPath; }

    static void SetBoolPref(const wxString& name, bool value);
    static bool GetBoolPref(const wxString& name);
    static void SetStrPref(const wxString& name, const wxString& value);
    static wxString GetStrPref(const wxString& name);
    static void SetIntPref(const wxString& name, int value);
    static int GetIntPref(const wxString& name);

    static void SavePrefs();
};



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
public:
	wxString GetURL();
	void SetURL(const wxString& newURL);
	void Cancel();
	bool IsCancelled();

    wxMozillaBeforeLoadEvent( wxWindow* win = NULL );
};

/*event class definitions*/
class wxMozillaLinkChangedEvent : public wxCommandEvent
{
public:
	wxString GetNewURL();
	bool CanGoBack();
	bool CanGoForward();
	void SetNewURL(const wxString& newurl);
	void SetCanGoBack(bool goback);
	void SetCanGoForward(bool goforward);

    wxMozillaLinkChangedEvent( wxWindow* win = NULL );
};

class wxMozillaStateChangedEvent : public wxCommandEvent
{
public:
	int GetState();
	void SetState(const int state);
	wxString GetURL();
	void SetURL(const wxString& url);

    wxMozillaStateChangedEvent( wxWindow* win = NULL );
};

class wxMozillaSecurityChangedEvent : public wxCommandEvent
{
public:
	int GetSecurity();
	void SetSecurity(const int security);

    wxMozillaSecurityChangedEvent( wxWindow* win = NULL );
};

class wxMozillaLoadCompleteEvent : public wxCommandEvent
{
public:
    wxMozillaLoadCompleteEvent( wxWindow* win = NULL );
};


class wxMozillaStatusChangedEvent : public wxCommandEvent
{
public:
	wxString GetStatusText();
	bool IsBusy();
	void SetStatusText(const wxString& status);
	void SetBusy(bool isbusy);

    wxMozillaStatusChangedEvent( wxWindow* win = NULL );
};

class wxMozillaTitleChangedEvent : public wxCommandEvent
{
public:
	wxString GetTitle();
	void SetTitle(const wxString& title);

    wxMozillaTitleChangedEvent( wxWindow* win = NULL );
};

class wxMozillaProgressEvent : public wxCommandEvent
{
public:
	int GetSelfCurrentProgress();
	void SetSelfCurrentProgress(int progress);
	
	int GetSelfMaxProgress();
	void SetSelfMaxProgress(int progress);
	
	int GetTotalCurrentProgress();
	void SetTotalCurrentProgress(int progress);
	
	int GetTotalMaxProgress();
	void SetTotalMaxProgress(int progress);

    wxMozillaProgressEvent( wxWindow* win = NULL );
};

class wxMozillaRightClickEvent : public wxMouseEvent
{
public:
	//wxString statusText;
	bool IsBusy();
	void SetBusy(bool isbusy);

	wxString GetBackgroundImageSrc();
	void SetBackgroundImageSrc(const wxString& name);
	wxString GetText();
	void SetText(const wxString& text);

	wxString GetImageSrc();
	void SetImageSrc(const wxString& src);

	wxString GetLink();
	void SetLink(const wxString& link);

	int GetContext();
	void SetContext(int context);

    wxMozillaRightClickEvent( wxWindow* win = NULL );
};


enum {
    wxEVT_MOZILLA_BEFORE_LOAD,
    wxEVT_MOZILLA_URL_CHANGED,
    wxEVT_MOZILLA_STATE_CHANGED,
    wxEVT_MOZILLA_SECURITY_CHANGED,
    wxEVT_MOZILLA_STATUS_CHANGED,
    wxEVT_MOZILLA_TITLE_CHANGED,
    wxEVT_MOZILLA_LOAD_COMPLETE,
    wxEVT_MOZILLA_PROGRESS,
    wxEVT_MOZILLA_RIGHT_CLICK
};

%pragma(python) code = "
def EVT_MOZILLA_BEFORE_LOAD(win, id, func):
    win.Connect(id, -1, wxEVT_MOZILLA_BEFORE_LOAD, func)

def EVT_MOZILLA_URL_CHANGED(win, id, func):
    win.Connect(id, -1, wxEVT_MOZILLA_URL_CHANGED, func)

def EVT_MOZILLA_STATE_CHANGED(win, id, func):
    win.Connect(id, -1, wxEVT_MOZILLA_STATE_CHANGED, func)

def EVT_MOZILLA_SECURITY_CHANGED(win, id, func):
    win.Connect(id, -1, wxEVT_MOZILLA_SECURITY_CHANGED, func)

def EVT_MOZILLA_STATUS_CHANGED(win, id, func):
    win.Connect(id, -1, wxEVT_MOZILLA_STATUS_CHANGED, func)

def EVT_MOZILLA_TITLE_CHANGED(win, id, func):
    win.Connect(id, -1, wxEVT_MOZILLA_TITLE_CHANGED, func)

def EVT_MOZILLA_LOAD_COMPLETE(win, id, func):
    win.Connect(id, -1, wxEVT_MOZILLA_LOAD_COMPLETE, func)

def EVT_MOZILLA_PROGRESS(win, id, func):
    win.Connect(id, -1, wxEVT_MOZILLA_PROGRESS, func)

def EVT_MOZILLA_RIGHT_CLICK(win, id, func):
    win.Connect(id, -1, wxEVT_MOZILLA_RIGHT_CLICK, func)
"

;//---------------------------------------------------------------------------

%init %{

    wxClassInfo::CleanUpClasses();
    wxClassInfo::InitializeClasses();

%}

%pragma(python) include="mozilla_extras.py"
