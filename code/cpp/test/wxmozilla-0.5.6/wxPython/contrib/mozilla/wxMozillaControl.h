#ifndef __WX_MOZILLA_CONTROL_H__
#define __WX_MOZILLA_CONTROL_H__
/*
 * wxWindows Mozilla Component
 * Copyright 2001 (c) Jeremiah Cornelius McCarthy. All Rights Reserved.
 * 
 * Author: Jeremiah Cornelius McCarthy
 * Created: January 24th, 2001
 * Licence: wxWindows License
 */

/* wxwindow includes */

// forward declarations



// wxWindows headers

#include "wx/defs.h"
#include "wx/window.h"

#include "wxMozillaEvents.h"

extern const char *wxMozillaBrowserNameStr;

/**
 * wxWindows Mozilla browser component
 */
class wxMozillaBrowser: public wxWindow
{
private:
	DECLARE_DYNAMIC_CLASS(wxMozillaBrowser)

protected: 
    static int gNumInstances;

	//Mozilla events
	void OnLocationChange();
	void OnStatusChange();
	void OnProgressChange();
	void OnRightClick();

    bool m_needParent;
    bool m_acceptsFocus;
	wxString m_status;
	bool m_isEditable;
	bool m_isBusy;
public:

	wxMozillaBrowser();
	wxMozillaBrowser(wxWindow *parent, wxWindowID id,
		const wxPoint &pos = wxDefaultPosition,
		const wxSize &size = wxDefaultSize,
		long style = 0,
        	const wxString &name = wxMozillaBrowserNameStr);
	//{
	//	Create(parent, id, pos, size, style, name);
	//}
	virtual ~wxMozillaBrowser();

	bool Create(wxWindow *parent, wxWindowID id,
		const wxPoint &pos = wxDefaultPosition,
		const wxSize &size = wxDefaultSize,
		long style = 0,
	       	const wxString &name = wxMozillaBrowserNameStr);

	virtual bool LoadURL(const wxString &location);
	wxString GetURL();

	bool SavePage(const wxString &filename);
	bool IsBusy();
	void SetProfilePath(const wxString &path);
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
	
	/* Not Yet Implemented - or at least not working! */
	void MakeEditable(bool enable=TRUE);
	bool IsEditable();
	void EditCommand(const wxString &cmdId, const wxString &value = "");

	void InsertHTML(const wxString &html);

	bool OpenStream(const wxString &location, const wxString &type);
	bool AppendToStream(const wxString &data);
	bool CloseStream();
	void OnSize(wxSizeEvent &event);
	void OnActivate(wxActivateEvent &event);
	void OnIdle(wxIdleEvent &event);
    #ifdef __WXMAC__
        void OnPaint(wxPaintEvent &event);
        void OnMove(wxMoveEvent &event);
        void OnLeftDown(wxMouseEvent &event);
    #endif
	wxString GetLinkMessage();
	wxString GetJSStatus();

    bool IsElementInSelection(wxString &element);
    bool SelectElement(wxString &element);
    wxString GetAttribute(wxString &attrName);
    void SetAttribute(wxString &attrName, wxString &attrValue);


	DECLARE_EVENT_TABLE()
//protected:
//	int m_numInstances;
};

class wxMozillaWindow: public wxFrame
{
public:

	wxMozillaWindow(bool showMenu = TRUE, bool showToolbar = TRUE, bool showStatusbar = TRUE);
	wxMozillaBrowser *Mozilla;
};

#endif
