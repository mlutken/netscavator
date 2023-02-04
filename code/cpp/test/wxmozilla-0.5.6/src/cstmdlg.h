#ifndef __WX_CUSTOM_DIALOG_H__
#define __WX_CUSTOM_DIALOG_H__
/*
 * Custom wxWindows dialog
 * Copyright 2004 (c) Kevin Ollivier. All Rights Reserved.
 * 
 * Licence: wxWindows License
 */

/* wxwindow includes */
#include "wx/defs.h"
#include "wx/window.h"
#include "wx/dialog.h"
#include "wx/app.h"
#include "wx/defs.h"
#include "wx/utils.h"
#include "wx/textctrl.h"

//This class allows for up to three buttons and an optional checkbox, to handle
//scenarios like "Save", "Don't Save", "Cancel" dialogs, as well as "Don't show this again"
//type dialogs
//Buttons will match with styles, such as wxYES_NO | wxCANCEL 
extern const wxChar* wxCustomDialogCaptionStr;

class wxCustomDialog: public wxDialog
{
private:
	DECLARE_DYNAMIC_CLASS(wxCustomDialog)
protected:
	wxString m_message;
	wxString m_caption;
	wxCheckBox* m_checkbox;
	long m_dialogStyle;
	wxWindow* m_parent;
	wxButton m_button1;
	wxButton m_button2;
	wxButton m_button3;

public:
	wxCustomDialog() {}
	wxCustomDialog(wxWindow* parent, const wxString& message, const wxString& caption = wxCustomDialogCaptionStr,
		const wxString& btn1Text = _("OK"), const wxString& btn2Text = wxEmptyString, const wxString& btn3Text = wxEmptyString, 
		const wxString& checkText = wxEmptyString, long style = 0, const wxPoint& pos = wxDefaultPosition);

	//returns the button number 1, 2, or 3
	int ShowModal(void);
	bool IsChecked();
	void OnButton1(wxCommandEvent& event);
	void OnButton2(wxCommandEvent& event);
	void OnButton3(wxCommandEvent& event);
	DECLARE_EVENT_TABLE()
};


class wxLoginDialog: public wxDialog
{
private:
	DECLARE_DYNAMIC_CLASS(wxLoginDialog)
protected:
	wxString m_message;
	wxString m_caption;
	wxString m_username;
	wxString m_password;
	wxTextCtrl* usertext;
	wxTextCtrl* passtext;
	wxCheckBox* m_checkbox;
	long m_dialogStyle;

public:
	wxLoginDialog() {}
	wxLoginDialog(wxWindow* parent, const wxString& message, const wxString& caption = wxEmptyString,
		const wxString& initUsername = wxEmptyString, const wxString& initPassword = wxEmptyString, 
		const wxString& checkText = wxEmptyString, long style = wxOK|wxCANCEL, const wxPoint& pos = wxDefaultPosition);
		
	~wxLoginDialog(){}

	//returns the standard button numbers (wxID_YES, wxID_NO, wxID_CANCEL)
	int ShowModal(void);
	wxString GetUsername(){ return m_username; }
	wxString GetPassword(){ return m_password; }
	bool IsChecked();
};

#endif
