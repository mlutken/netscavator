/*
 * wxMozillaWindow Modal Window Browser
 *
 * 
 * Developers:
 *  Jeremiah Cornelius McCarthy <jeremiah@whoop-ass.ca>
 *  Kevin Ollivier <kevino@tulane.edu>
 *  Dave Fancella <david.fancella@attbi.com>
 */
#include "wx/wxprec.h"
#include "wx/bmpbuttn.h"
#include "wxMozillaWindow.h"
#include "helpers.h"

#include "../icons/back24.xpm"
#include "../icons/back24_d.xpm"
#include "../icons/forward24.xpm"
#include "../icons/forward24_d.xpm"
#include "../icons/refresh24.xpm"
#include "../icons/refresh24_d.xpm"
#include "../icons/stop24.xpm"
#include "../icons/stop24_d.xpm"

enum {
    ID_MOZCTL = wxID_HIGHEST + 1,
		ID_GO = wxID_HIGHEST + 2,
		ID_ADDRESS = wxID_HIGHEST + 3,
		ID_BACK = wxID_HIGHEST + 4,
		ID_NEXT = wxID_HIGHEST + 5,
		ID_SAVE = wxID_HIGHEST + 6,
		ID_STOP = wxID_HIGHEST + 7,
		ID_REFRESH = wxID_HIGHEST + 8,
		ID_BOLD = wxID_HIGHEST + 9,
		ID_EDITABLE = wxID_HIGHEST + 10,
		ID_COPY = wxID_HIGHEST + 11,
		ID_SELECT_ALL = wxID_HIGHEST + 12,
		ID_SELECT_NONE = wxID_HIGHEST + 13,
		ID_FIND = wxID_HIGHEST + 14,
		ID_NEW_WINDOW = wxID_HIGHEST + 15,
		ID_OPEN = wxID_HIGHEST + 16,
		ID_QUIT = wxID_HIGHEST + 17,
		ID_OPEN_NEW_WINDOW = wxID_HIGHEST + 18,
		ID_SAVE_LINK = wxID_HIGHEST + 19,
		ID_SAVE_IMAGE = wxID_HIGHEST + 20,
		ID_VIEW_SOURCE = wxID_HIGHEST + 21,
		ID_UNDO = wxID_HIGHEST + 22,
        ID_VIEW_LINK = wxID_HIGHEST + 23,
        ID_EDIT_LINK = wxID_HIGHEST + 24
};

IMPLEMENT_DYNAMIC_CLASS(wxMozillaWindow, wxFrame)

BEGIN_EVENT_TABLE(wxMozillaWindow, wxFrame)
	EVT_BUTTON(ID_GO, wxMozillaWindow::GoClicked)
	EVT_TOOL(ID_BACK, wxMozillaWindow::BackClicked)
	EVT_TOOL(ID_NEXT, wxMozillaWindow::NextClicked)
	EVT_TOOL(ID_STOP, wxMozillaWindow::StopLoading)
	EVT_TOOL(ID_REFRESH, wxMozillaWindow::RefreshPage)
	EVT_MENU(ID_NEW_WINDOW, wxMozillaWindow::NewWindow)
	EVT_MENU(ID_OPEN_NEW_WINDOW, wxMozillaWindow::OpenNewWindow)
	EVT_MENU(ID_QUIT, wxMozillaWindow::Quit)
	EVT_MENU(ID_VIEW_SOURCE, wxMozillaWindow::ViewSource)
	EVT_MENU(ID_STOP, wxMozillaWindow::StopLoading)
	EVT_MENU(ID_REFRESH, wxMozillaWindow::RefreshPage)
	EVT_MENU(wxID_SAVE, wxMozillaWindow::SaveClicked)
	EVT_MENU(ID_SELECT_ALL, wxMozillaWindow::SelectAll)
	EVT_MENU(ID_SELECT_NONE, wxMozillaWindow::SelectNone)
	EVT_MENU(ID_FIND, wxMozillaWindow::ShowFindDlg)
	//EVT_MENU(ID_SPELLCHECK, wxMozillaWindow::SpellCheck)
#if wxUSE_FINDREPLDLG
	EVT_FIND(-1, wxMozillaWindow::DoFind)
	EVT_FIND_NEXT(-1, wxMozillaWindow::DoFind)
	EVT_FIND_CLOSE(-1, wxMozillaWindow::DoFind)
#endif
	EVT_MENU(ID_UNDO, wxMozillaWindow::Undo)
	EVT_MENU(ID_EDITABLE, wxMozillaWindow::MakeEditable)
	EVT_MENU(ID_BOLD, wxMozillaWindow::BoldClicked)
	EVT_MENU(ID_COPY, wxMozillaWindow::DoCopy)
    EVT_MENU(ID_VIEW_LINK, wxMozillaWindow::OnLinkProperties)
    EVT_MENU(ID_EDIT_LINK, wxMozillaWindow::OnEditLink)
	EVT_MOZILLA_URL_CHANGED(wxMozillaWindow::UpdateURL)
	EVT_MOZILLA_STATUS_CHANGED(wxMozillaWindow::UpdateStatus)
	EVT_MOZILLA_STATE_CHANGED(wxMozillaWindow::UpdateState)
	EVT_MOZILLA_BEFORE_LOAD(wxMozillaWindow::BeforeLoad)
	EVT_MOZILLA_RIGHT_CLICK(wxMozillaWindow::OnMozillaRightClick)
	EVT_MOZILLA_LOAD_COMPLETE(wxMozillaWindow::OnLoadComplete)
	//EVT_MOZILLA_MOUSE_EVENT(wxMozillaWindow::OnMozillaMouseEvent)
	//EVT_MOUSE_EVENTS(wxMozillaWindow::OnMouseDown)
END_EVENT_TABLE()

wxMozillaWindow::wxMozillaWindow(bool showMenu, bool showToolbar, bool showStatusbar, bool popupWindow)
{
	wxFrame::Create((wxFrame *)NULL, -1, _("wxMozilla"), wxPoint(0, 0), wxSize(800,600));
        //int posx, posy;
	if (showStatusbar){
		hasStatusbar = TRUE;
		statusBar = this->CreateStatusBar();
	}
	else
		hasStatusbar = FALSE;

	if (showMenu){
	hasMenu = TRUE;
	appMenuBar = new wxMenuBar();
	fileMenu = new wxMenu();
	fileMenu->Append(ID_NEW_WINDOW, _("New Window"));
	fileMenu->Append(ID_OPEN, _("Open"));
	fileMenu->Append(wxID_SAVE, _("Save Page"));
	fileMenu->AppendSeparator();
	fileMenu->Append(ID_QUIT, _("Exit"));

	appMenuBar->Append(fileMenu, _("File"));

	editMenu = new wxMenu();
	editMenu->Append(ID_UNDO, _("Undo"));
	editMenu->Append(ID_EDITABLE, _("Make Editable"));
	editMenu->Append(ID_BOLD, _("Bold"));
	editMenu->AppendSeparator();
	editMenu->Append(ID_COPY, _("Copy"));
	editMenu->AppendSeparator();
	editMenu->Append(ID_SELECT_ALL, _("Select All"));
	editMenu->Append(ID_SELECT_NONE, _("Select None"));
#if wxUSE_FINDREPLDLG
	editMenu->Append(ID_FIND, _("Find"));
#endif
	appMenuBar->Append(editMenu, _("Edit"));

	viewMenu = new wxMenu();
	viewMenu->Append(ID_STOP, _("Stop"));
	viewMenu->Append(ID_REFRESH, _("Refresh"));
	viewMenu->AppendSeparator();
	viewMenu->Append(ID_VIEW_SOURCE, _("View Source"));
    viewMenu->Append(ID_VIEW_LINK, _("Link Properties"));
	appMenuBar->Append(viewMenu, _("View"));

	//toolMenu = new wxMenu();
	//toolMenu->Append(ID_SPELLCHECK, _("Check Spelling"));
	//appMenuBar->Append(toolMenu, _("Tool"));

	this->SetMenuBar(appMenuBar);
	}
	else
		hasMenu = FALSE;
	//myClipboard = new wxClipboard();

        //Create a fake toolbar - it's not pretty but works for now
	if (showToolbar){
		hasToolbar = TRUE;

	wxBitmap BackOn = wxBitmap(back24_xpm);
	wxBitmap BackOff = wxBitmap(back24_d_xpm);
	
	wxBitmap NextOn = wxBitmap(forward24_xpm);
	wxBitmap NextOff = wxBitmap(forward24_d_xpm);
	
	wxBitmap RefreshOn = wxBitmap(refresh24_xpm);
	wxBitmap RefreshOff = wxBitmap(refresh24_d_xpm);

	wxBitmap StopOn = wxBitmap(stop24_xpm);
	wxBitmap StopOff = wxBitmap(stop24_d_xpm);

	toolbar = this->CreateToolBar();
	toolbar->SetMargins(6, 2);

	toolbar->AddTool(ID_BACK, _("Back"), BackOn, BackOff);
	//toolbar->AddSeparator();
	toolbar->AddTool(ID_NEXT, _("Next"), NextOn, NextOff);
	//toolbar->AddSeparator();
	toolbar->AddTool(ID_STOP, _("Stop"), StopOn, StopOff);
	//toolbar->AddSeparator();
	toolbar->AddTool(ID_REFRESH, _("Refresh"), RefreshOn, RefreshOff);
	//toolbar->AddSeparator();
	toolbar->SetToolBitmapSize(wxSize(24,24));
	lblAddress = new wxStaticText(toolbar, -1, _("Address:"));
    txtURL = new wxTextCtrl(toolbar, ID_ADDRESS, _T("http://www.mozilla.org"), wxPoint(400,0), wxSize(180,25));	
	GoButton = new wxButton(toolbar, ID_GO, _("Go!")); 
	toolbar->AddControl(lblAddress);
	toolbar->AddControl(txtURL);
	toolbar->AddControl(GoButton);
	toolbar->Realize();
	}
	else
		hasToolbar = FALSE;
/*
	BackButton = new wxButton(this, ID_BACK, _("Back"), wxPoint(30,0));
	BackButton->Enable(FALSE);
	NextButton = new wxButton(this, ID_NEXT, _("Next"), wxPoint(90,0));
	NextButton->Enable(FALSE);
	StopButton = new wxButton(this, ID_STOP, _("Stop"), wxPoint(190,0));
	StopButton->Enable(FALSE);
	RefreshButton = new wxButton(this, ID_REFRESH, _("Refresh"), wxPoint(270,0));
*/
        
	if (popupWindow)
        Mozilla = new wxMozillaBrowser(this, ID_MOZCTL, wxDefaultPosition, wxDefaultSize, wxCLIP_CHILDREN);
    else
		Mozilla = new wxMozillaBrowser(this, ID_MOZCTL, wxDefaultPosition, wxSize(700, 500), wxCLIP_CHILDREN);
        
	Mozilla->Show(TRUE);
	//Mozilla->SetFocus();
        
        wxBoxSizer *mysizer = new wxBoxSizer(wxVERTICAL);
        mysizer->Add(Mozilla, 1, wxALL|wxEXPAND);

        SetAutoLayout(TRUE);
        SetSizerAndFit(mysizer);
        Layout();
}

/*
void wxMozillaWindow::SpellCheck(wxCommandEvent &myEvent){
	Mozilla->StartSpellCheck();
	wxMessageBox(Mozilla->GetNextMisspelledWord());
	Mozilla->StopSpellChecker();
}
*/

void wxMozillaWindow::NewWindow(wxCommandEvent &myEvent)
{
	wxMozillaWindow *newWin = new wxMozillaWindow();
	newWin->Show(TRUE);
}

void wxMozillaWindow::Quit(wxCommandEvent &myEvent)
{
	Destroy();
}

void wxMozillaWindow::ViewSource(wxCommandEvent &myEvent)
{
	wxMozillaWindow *newWin = new wxMozillaWindow(FALSE, FALSE, FALSE);
	newWin->Mozilla->LoadURL(wxString(_T("view-source:")) + txtURL->GetValue());
	newWin->Show(TRUE);
}

void wxMozillaWindow::StopLoading(wxCommandEvent &myEvent)
{
	Mozilla->Stop();
}

void wxMozillaWindow::RefreshPage(wxCommandEvent &myEvent)
{
	Mozilla->Reload();
}

void wxMozillaWindow::GoClicked(wxCommandEvent &myEvent)
{
	Mozilla->LoadURL(txtURL->GetValue());
	//CheckStates();
};

void wxMozillaWindow::BackClicked(wxCommandEvent &myEvent)
{
	if (Mozilla->CanGoBack())
		Mozilla->GoBack();
		//CheckStates();
};

void wxMozillaWindow::NextClicked(wxCommandEvent &myEvent)
{
	if (Mozilla->CanGoForward())
		Mozilla->GoForward();
		//CheckStates();
};

void wxMozillaWindow::SaveClicked(wxCommandEvent &myEvent)
{
	wxFileDialog mydialog(this, _("Save file as..."), wxEmptyString,Mozilla->GetTitle(),_T("HTML Files (htm,html)|*.htm,*.html"), wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
	if (mydialog.ShowModal() == wxID_OK)
	{
		Mozilla->SavePage(mydialog.GetPath());
	}
	mydialog.Destroy();
}

void wxMozillaWindow::OpenNewWindow(wxCommandEvent &myEvent)
{
	if(eventURL){
		wxMozillaWindow *myWin = new wxMozillaWindow();
		myWin->Mozilla->LoadURL(eventURL);
		myWin->Show(TRUE);
	}

}

void wxMozillaWindow::OnMozillaRightClick(wxMozillaRightClickEvent &myEvent)
{
	//lastEvent = myEvent;
	wxMenu *myMenu = new wxMenu();
	if (!myEvent.GetLink().empty()){
		myMenu->Append(ID_OPEN_NEW_WINDOW, _("Open in New Window"));
        if (Mozilla->IsEditable())
            myMenu->Append(ID_EDIT_LINK, _("Edit Link Properites"));
		eventURL = myEvent.GetLink();
	}
	if (!myEvent.GetImageSrc().empty()){
		eventImage = myEvent.GetImageSrc();
        myMenu->Append(ID_VIEW_LINK, _("Image Properties"));
	}
	wxPoint myPoint = myEvent.GetPosition();
	PopupMenu(myMenu, myPoint);
}

void wxMozillaWindow::OnLoadComplete(wxMozillaLoadCompleteEvent &myEvent){
        printf("Handling OnLoadComplete...\n");
	if (hasStatusbar)
		statusBar->SetStatusText(wxEmptyString);
}

void wxMozillaWindow::Undo(wxCommandEvent &myEvent)
{
	Mozilla->EditCommand(_T("cmd_undo"));
}

void wxMozillaWindow::MakeEditable(wxCommandEvent &myEvent)
{
	Mozilla->MakeEditable(TRUE);
	//Mozilla->Reload();
}

void wxMozillaWindow::BeforeLoad(wxMozillaBeforeLoadEvent &myEvent){
	//doesn't seem to work... even though GetURL() does return http://cnn.com...
	if (myEvent.GetURL().Find(_T("microsoft.com/windows/ie")) != -1)
	{
		//what I really would like to do is myEvent.Cancel()
		//when OnStartURIOpen is called...
		wxMessageDialog mydialog(this, _T("Are you really, really sure you want to visit this site?!"), _T("What do you need to go here for?"), wxYES | wxNO);
		if (mydialog.ShowModal() == wxID_NO)
			Mozilla->Stop();
	}
}

void wxMozillaWindow::BoldClicked(wxCommandEvent &myEvent)
{
	Mozilla->EditCommand(_T("cmd_bold"));
}

#if wxUSE_FINDREPLDLG
void wxMozillaWindow::ShowFindDlg(wxCommandEvent &myEvent)
{

	if (findDlg)
	{
		delete findDlg;
		findDlg = NULL;
	}
	settings = new wxFindReplaceData(wxFR_DOWN|wxFR_WHOLEWORD);
	findDlg = new wxFindReplaceDialog(this, settings, _("Find Text"));
	findDlg->Show(TRUE);
        
}


void wxMozillaWindow::DoFind(wxFindDialogEvent &myEvent)
{
    wxEventType type = myEvent.GetEventType();
	bool result = FALSE; 

	bool matchCase = FALSE;
	bool matchWholeWord = FALSE;
	bool searchBackwards = FALSE;

    if ( type == wxEVT_COMMAND_FIND)
	{
		int flags = myEvent.GetFlags();
		if (flags & wxFR_MATCHCASE)
			matchCase = TRUE;

		if (flags & wxFR_WHOLEWORD)
			matchWholeWord = TRUE;
		
		if (flags & wxFR_DOWN)
			searchBackwards = FALSE;
		else
			searchBackwards = TRUE;
			
		result = Mozilla->Find(myEvent.GetFindString(), matchCase, matchWholeWord, TRUE, searchBackwards);
	}
	else if (type == wxEVT_COMMAND_FIND_NEXT)
	{
		int flags = myEvent.GetFlags();
		if (flags & wxFR_MATCHCASE)
			matchCase = TRUE;

		if (flags & wxFR_WHOLEWORD)
			matchWholeWord = TRUE;
		
		if (flags & wxFR_DOWN)
			searchBackwards = FALSE;
		else
			searchBackwards = TRUE;

		result = Mozilla->Find(myEvent.GetFindString(), matchCase, matchWholeWord, TRUE, searchBackwards);
	}
	else if (type == wxEVT_COMMAND_FIND_CLOSE)
	{
		findDlg->Destroy();
		findDlg = NULL;
		settings = NULL;
	}

	if (!result)
		wxMessageDialog(this, _("The text could not be found."), _("Text Not Found")).ShowModal();
}
#endif //wxUSE_FINDREPLDLG

void wxMozillaWindow::DoCopy(wxCommandEvent &myEvent)
{
	Mozilla->Copy();
  //if (myClipboard->Open())
  //{
    //right now we automatically assume the selection is part of the mozilla contorl
	  //for testing purposes
   // myClipboard->SetData( new wxTextDataObject(Mozilla->GetSelection()) );
   // myClipboard->Close();
  //}
}

void wxMozillaWindow::SelectAll(wxCommandEvent &myEvent)
{
	Mozilla->SelectAll();
}

void wxMozillaWindow::SelectNone(wxCommandEvent &myEvent)
{
	Mozilla->SelectNone();
}
void wxMozillaWindow::UpdateURL(wxMozillaLinkChangedEvent &myEvent)
{
	if (hasToolbar){
	toolbar->EnableTool(ID_BACK, myEvent.CanGoBack());
	toolbar->EnableTool(ID_NEXT, myEvent.CanGoForward());
	txtURL->SetValue(myEvent.GetNewURL());
	}
}

void wxMozillaWindow::UpdateStatus(wxMozillaStatusChangedEvent &myEvent)
{
	if (hasToolbar)
		//toolbar->FindControl(ID_STOP)->Enable(myEvent.isBusy);
		toolbar->EnableTool(ID_STOP, myEvent.IsBusy());
	if (hasStatusbar)
		statusBar->SetStatusText(myEvent.GetStatusText());
	SetTitle(wxString(_T("wxMozilla - ")) + Mozilla->GetTitle());

}

void wxMozillaWindow::UpdateState(wxMozillaStateChangedEvent &myEvent){

	if (hasStatusbar){
		if (myEvent.GetState() & wxMOZILLA_STATE_START)
		{
			statusBar->SetStatusText(wxString(_T("Loading ")) + myEvent.GetURL() + wxString(_T("...")));
		}
		else if (myEvent.GetState() & wxMOZILLA_STATE_NEGOTIATING)
		{
			statusBar->SetStatusText(_T("Contacting server..."));
		}
		else if (myEvent.GetState() & wxMOZILLA_STATE_REDIRECTING)
		{
			statusBar->SetStatusText(wxString(_T("Redirecting from ")) + myEvent.GetURL() + wxString(_T("...")));
		}
		else if (myEvent.GetState() & wxMOZILLA_STATE_TRANSFERRING)
		{
			statusBar->SetStatusText(wxString(_T("Loading ")) + myEvent.GetURL() + wxString(_T("...")));
		}
		//stop scenario is handled by OnLoadComplete 
	}

}
void wxMozillaWindow::OnLinkProperties(wxCommandEvent &myEvent){
    //usually you pass tag name, but for A tags href is passed to avoid confusion with bookmarks within page
    wxString attrName = _T("src");
    //if (Mozilla->IsElementInSelection(attrName)){
        wxString myLink;
	wxString mytag = _T("img");
        myLink = Mozilla->GetElementAttribute(mytag,attrName);
        wxMessageBox(myLink);
     //}
}

void wxMozillaWindow::OnEditLink(wxCommandEvent &myEvent){
    //usually you pass tag name, but for A tags href is passed to avoid confusion with bookmarks within page
    wxString attrName = _T("href");
    //if (Mozilla->IsElementInSelection(attrName)){
        wxString myLink;
	wxString mytag = _T("href"); //tag expects href to differentiate from bookmarks
        myLink = Mozilla->GetElementAttribute(mytag, attrName);
        wxTextEntryDialog *myDialog;
        myDialog = new wxTextEntryDialog(this, wxEmptyString, _("Edit Link Properties"), myLink);
        if (myDialog->ShowModal() == wxID_OK)
        {
            myLink = myDialog->GetValue();
            Mozilla->SetElementAttribute(attrName, myLink);
        }
        myDialog->Destroy();
    //}
}


