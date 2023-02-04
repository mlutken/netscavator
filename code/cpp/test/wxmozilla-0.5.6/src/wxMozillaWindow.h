#ifndef __WX_MOZILLA_WINDOW_H__
#define __WX_MOZILLA_WINDOW_H__
/*
 * wxMozilla
 *
 * Developers:
 *  Jeremiah Cornelius McCarthy <jeremiah@whoop-ass.ca>
 *  Kevin Ollivier <kevino@tulane.edu>
 *  Dave Fancella <david.fancella@attbi.com>
 */

#include "wx/wx.h"
#include "wx/frame.h"
#include "wx/filedlg.h"
#include "wx/image.h"
#include "wx/fdrepdlg.h"
#include "wx/clipbrd.h"
#include "wxMozillaBrowser.h"
#include "wxMozillaEvents.h"

class wxMozillaWindow: public wxFrame
{
private:
	DECLARE_DYNAMIC_CLASS(wxMozillaWindow)
	//wxBoxSizer *VBox;
	//wxBoxSizer *HBox;
	bool hasMenu;
	bool hasToolbar;
	bool hasStatusbar;
	wxMozillaBrowser *MozWnd2;
	wxStaticText *lblAddress;
	wxButton *GoButton;
	wxButton *BackButton;
	wxButton *NextButton;
	wxButton *StopButton;
	wxButton *RefreshButton;
#if wxUSE_FINDREPLDLG
	wxFindReplaceDialog *findDlg;
	wxFindReplaceData *settings;
#endif

	wxTextCtrl *txtURL;
	//store the event so that you can use its data 
	//when someone clicks on the popup menu.
	wxString eventURL;
	wxString eventImage;
	wxString eventBgImage;
	wxToolBar *toolbar;
	wxStatusBar *statusBar;
	wxMenuBar* appMenuBar;
	wxMenu* fileMenu;
	wxMenu* editMenu;
	wxMenu* viewMenu;
	wxMenu* toolMenu;
	//wxMenuItem* stopItem;
	//wxMenuItem* saveItem;
	//wxMenuItem* refreshItem;

	//wxArtProvider *imageList;
	void NewWindow(wxCommandEvent &myEvent);
	void OpenNewWindow(wxCommandEvent &myEvent);
	void Quit(wxCommandEvent &myEvent);
	void ViewSource(wxCommandEvent &myEvent);
	void GoClicked(wxCommandEvent &myEvent);
	void BackClicked(wxCommandEvent &myEvent);
	void NextClicked(wxCommandEvent &myEvent);
	void StopLoading(wxCommandEvent &myEvent);
	void RefreshPage(wxCommandEvent &myEvent);
	void SaveClicked(wxCommandEvent &myEvent);
	void Undo(wxCommandEvent &myEvent);
	void MakeEditable(wxCommandEvent &myEvent);
	void BoldClicked(wxCommandEvent &myEvent);
	void DoCopy(wxCommandEvent &myEvent);
	void SelectAll(wxCommandEvent &myEvent);
	void SelectNone(wxCommandEvent &myEvent);
#if wxUSE_FINDREPLDLG
	void ShowFindDlg(wxCommandEvent &myEvent);
	void DoFind(wxFindDialogEvent &myEvent);
#endif
	void OnMozillaRightClick(wxMozillaRightClickEvent &event);
	//void OnMozillaMouseEvent(wxMozillaMouseEvent &myEvent);
	void OnMouseDown(wxMouseEvent &myEvent);
	void UpdateURL(wxMozillaLinkChangedEvent &myEvent);
	void BeforeLoad(wxMozillaBeforeLoadEvent &myEvent);
	void UpdateStatus(wxMozillaStatusChangedEvent &myEvent); //determine the state of back and next buttons
	void UpdateState(wxMozillaStateChangedEvent &myEvent);
	void OnLoadComplete(wxMozillaLoadCompleteEvent &myEvent);
	void OnLinkProperties(wxCommandEvent &myEvent);
    void OnEditLink(wxCommandEvent &myEvent);
	//void SpellCheck(wxCommandEvent &myEvent);
    DECLARE_EVENT_TABLE()

public:

	wxMozillaWindow(bool showMenu = TRUE, bool showToolbar = TRUE, bool showStatusbar = TRUE, bool popupWindow = FALSE);
	wxMozillaBrowser *Mozilla;
};
#endif
