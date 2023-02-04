#ifndef __WX_MOZILLA_BROWSER_H__
#define __WX_MOZILLA_BROWSER_H__
/*
 * wxWindows Mozilla Component
 * Copyright 2001 (c) Jeremiah Cornelius McCarthy. All Rights Reserved.
 * 
 * Author: Jeremiah Cornelius McCarthy
 * Created: January 24th, 2001
 * Licence: wxWindows License
 */

/* wxwindow includes */
#include "wx/defs.h"
#include "wx/window.h"
#ifdef __WXMAC__
#include <Carbon/Carbon.h>
#endif

// forward declarations
class wxMozillaBrowserChrome;
struct wxMozillaBrowserInterface;
class wxMozillaDialogs;
class nsIHTMLEditor;
class nsIDOMDocument;
class nsIAppShell;

//macros for testing wxMozilla version
#define wxMOZ_MAJOR_VERSION    0
#define wxMOZ_MINOR_VERSION    5
#define wxMOZ_RELEASE_NUMBER   6

/*  check if the current version is at least major.minor.release */
#define wxMOZILLA_CHECK_VERSION(major,minor,release) \
    (wxMOZ_MAJOR_VERSION > (major) || \
    (wxMOZ_MAJOR_VERSION == (major) && wxMOZ_MINOR_VERSION > (minor)) || \
    (wxMOZ_MAJOR_VERSION == (major) && wxMOZ_MINOR_VERSION == (minor) \
     && wxMOZ_RELEASE_NUMBER >= (release)))


//forward declaration of function needed by wxPython
void wxMozillaInitResourceModule();

extern const wxChar *wxMozillaBrowserNameStr;
//static nsIAppShell *gAppShell;
/**
 * wxWindows Mozilla browser component
 */
class wxMozillaBrowser: public wxWindow
{
	friend class wxMozillaDialogs;
	friend class wxMozillaBrowserChrome;
	//private class int instances;

private:
	DECLARE_DYNAMIC_CLASS(wxMozillaBrowser)
#ifdef __WXMAC__
    //WXEVENTHANDLERREF    m_mozillaEventHandler ;
    //static pascal OSStatus wxMozillaEventChainHandler(EventHandlerCallRef handler , EventRef event , void *data);
#endif
protected:
	class wxMozillaBrowserChrome *Chrome;

    wxMozillaBrowserInterface *m_Mozilla;

	static int gNumInstances;

	//Mozilla events
	void OnLocationChange();
	void OnStatusChange();
	void OnRightClick();

    WXWidget m_macControl;
    bool m_needParent;
    bool m_acceptsFocus;
	wxString m_status;
	bool m_isEditable;
	bool m_isBusy;
    wxString m_title;

    // private wxMozilla functions:
    static bool IsEmbeddingInitialized();
    static bool EnsureEmbedding();

    friend class wxMozillaSettings;

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
	
	/* HTML editor functionality */
	void MakeEditable(bool enable=TRUE);
	bool IsEditable();
	void EditCommand(const wxString &cmdId, const wxString &value = wxEmptyString);
    bool GetCommandState(const wxString &command, const wxString &state);
    wxString GetStateAttribute(wxString &command);

	void UpdateBaseURI(); //this is needed because Mozilla's editor screws up the base URI...
	void InsertHTML(const wxString &html);
	void GetHTMLEditor(nsIHTMLEditor** htmlEditor);

	bool OpenStream(const wxString &location, const wxString &type);
	bool AppendToStream(const wxString &data);
	bool CloseStream();

    #ifdef __WXGTK__
    virtual void SetFocus();
    #endif
    
	void OnSize(wxSizeEvent &event);
	void OnActivate(wxActivateEvent &event);
	void OnIdle(wxIdleEvent &event);
    #ifdef __WXMAC__
        virtual void MacRedraw(WXHRGN updatergnr , long time, bool erase);
        virtual void MacEnabledStateChanged() ;
        virtual void MacSuperChangedPosition() ;
        virtual void MacVisibilityChanged() ;
        void OnPaint(wxPaintEvent &event);
        void OnMove(wxMoveEvent &event);
        void OnMouseEvent(wxMouseEvent &event);
        void OnLeftDown(wxMouseEvent &event);
        void OnSetFocus(wxFocusEvent &pEvent);
        void OnKillFocus(wxFocusEvent &pEvent);
        //virtual void wxWindow::MacRedraw( WXHRGN updatergn , long time , bool erase) ;
    #endif
	wxString GetLinkMessage();
	wxString GetJSStatus();

    bool IsElementInSelection(const wxString &element);
    bool SelectElement(const wxString &element);
    wxString GetElementAttribute(const wxString &tagName, const wxString &attrName);
    void SetElementAttribute(const wxString &attrName, const wxString &attrValue);
    bool SetPage(const wxString &data);
    wxString GetPage();

    // override wxWindow's empty implementation:
    void SetTitle(const wxString &title) { m_title = title; }
    wxString GetTitle() const { return m_title; }

	//spell checker
	void StartSpellCheck();
	wxString GetNextMisspelledWord();
	wxString GetSuggestedWord();
	void ReplaceWord(wxString misspelledWord, wxString replacement, bool allOccurrences);
	void StopSpellChecker();

	DECLARE_EVENT_TABLE()
//protected:
//	int m_numInstances;
public:
	/**
		* @author David Teller <Yoric@users.sourceforge.net>
		* Sets the zoom level
		*/
        bool SetZoom(float level);
	/**
	 * @author David Teller <Yoric@users.sourceforge.net>
	 *
	 * Returns a pointer to the current document
   * @warning behaviour is non-specified if the current document is not fully loaded !
   */
        bool GetDOMDocument(nsIDOMDocument** aDocument);

#ifdef __WXMSW__
/**
 * @author Zhang Yue <zhangyue99@tsinghua.org.cn>
 * we need to override wx set focus method here
 */
void wxMozillaBrowser::SetFocus();
#endif


};

#endif
