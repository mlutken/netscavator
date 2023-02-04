/////////////////////////////////////////////////////////////////////////////
// Name:        mozilla.i
// Purpose:     Mozilla in a wxWindow
//
// Author:      Robin Dunn / Kevin Ollivier
//
// Created:     28-Feb-2003
// RCS-ID:      $Id: mozilla.i,v 1.4 2005/03/23 20:49:37 kollivier Exp $
// Copyright:   (c) 2001 by Total Control Software
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////


%module(package="wx") mozilla

%{
#include "wx/wxPython/wxPython.h"
#include "wx/wxPython/pyclasses.h"
#include "wx/wxPython/pyistream.h"

#ifdef __WXMAC__  // avoid a bug in Carbon headers
#define scalb scalbn
#endif

#include "wxMozillaBrowser.h"
#include "wxMozillaWindow.h"
#include "wxMozilla.h"
%}

//---------------------------------------------------------------------------

%include typemaps.i
%include my_typemaps.i

%import core.i
%import windows.i
%import misc.i

%pythoncode { wx = _core }
%pythoncode { __docfilter__ = wx.__DocFilter(globals()) }

%include _mozilla_rename.i

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
	void EditCommand(const wxString &cmdId, const wxString& value = wxEmptyString);
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
    wxEVT_MOZILLA_RIGHT_CLICK,
};

%pythoncode {
__version__ = (MOZ_MAJOR_VERSION, MOZ_MINOR_VERSION, MOZ_RELEASE_NUMBER)

EVT_MOZILLA_BEFORE_LOAD = wx.PyEventBinder(wxEVT_MOZILLA_BEFORE_LOAD, 1)
EVT_MOZILLA_URL_CHANGED = wx.PyEventBinder(wxEVT_MOZILLA_URL_CHANGED, 1)
EVT_MOZILLA_STATE_CHANGED = wx.PyEventBinder(wxEVT_MOZILLA_STATE_CHANGED, 1)
EVT_MOZILLA_SECURITY_CHANGED = wx.PyEventBinder(wxEVT_MOZILLA_SECURITY_CHANGED, 1)
EVT_MOZILLA_STATUS_CHANGED = wx.PyEventBinder(wxEVT_MOZILLA_STATUS_CHANGED, 1)
EVT_MOZILLA_TITLE_CHANGED = wx.PyEventBinder(wxEVT_MOZILLA_TITLE_CHANGED, 1)
EVT_MOZILLA_LOAD_COMPLETE = wx.PyEventBinder(wxEVT_MOZILLA_LOAD_COMPLETE, 1)
EVT_MOZILLA_PROGRESS = wx.PyEventBinder(wxEVT_MOZILLA_PROGRESS, 1)
EVT_MOZILLA_RIGHT_CLICK = wx.PyEventBinder(wxEVT_MOZILLA_RIGHT_CLICK, 1)
}

;//---------------------------------------------------------------------------

%init %{

    wxClassInfo::CleanUpClasses();
    wxClassInfo::InitializeClasses();

%}

%pragma(python) include="mozilla_extras.py"
