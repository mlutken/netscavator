/*
 * Custom wxWindows dialog
 * Copyright 2004 (c) Kevin Ollivier. All Rights Reserved.
 * 
 * Licence: wxWindows License
 */
#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

//#include "wx/dialog.h"
//#include "wx/checkbox.h"
//#include "wx/button.h"
//#include "wx/sizer.h"
#include "cstmdlg.h"

const int ID_BUTTON1 = 1121;
const int ID_BUTTON2 = 1122;
const int ID_BUTTON3 = 1123;

IMPLEMENT_DYNAMIC_CLASS(wxLoginDialog, wxDialog)
IMPLEMENT_DYNAMIC_CLASS(wxCustomDialog, wxDialog)

BEGIN_EVENT_TABLE(wxCustomDialog, wxDialog)
    EVT_BUTTON(ID_BUTTON1, wxCustomDialog::OnButton1)
    EVT_BUTTON(ID_BUTTON2, wxCustomDialog::OnButton2)
    EVT_BUTTON(ID_BUTTON3, wxCustomDialog::OnButton3)
END_EVENT_TABLE()

wxCustomDialog::wxCustomDialog(wxWindow* parent, const wxString& message, const wxString& caption, 
		const wxString& btn1Text, const wxString& btn2Text, const wxString& btn3Text, 
		const wxString& checkText, long style, const wxPoint& pos)
{

	m_message = message;
	m_caption = caption;
	m_dialogStyle = style;

	//create the dialog window
	if (!wxDialog::Create(parent, wxID_ANY, caption, pos, wxDefaultSize, wxDEFAULT_DIALOG_STYLE)){
		return;
	}

	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(CreateTextSizer(message), 0, wxALL, 6);
	//create the controls
	//wxStaticText* messageText = new wxStaticText(this, wxID_ANY, message);
	
	if (checkText != wxEmptyString)
	{
		m_checkbox = new wxCheckBox(this, wxID_ANY, checkText);
		//mainSizer->Add(m_checkbox, 0, wxEXPAND | wxALL, 4);
	}

	//button1 at least should always appear
	wxButton* button1 = new wxButton(this, ID_BUTTON1, btn1Text); 
	wxButton* button2 = NULL;
	wxButton* button3 = NULL;

	if (btn2Text != wxEmptyString)
		button2 = new wxButton(this, ID_BUTTON2, btn2Text); 

	if (btn3Text != wxEmptyString)
		button3 = new wxButton(this, ID_BUTTON3, btn3Text); 

	if (checkText != wxEmptyString)
		mainSizer->Add(m_checkbox, 0, wxALL, 4);

	wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
	//buttonSizer->Add(1, 1, 1, wxEXPAND | wxALL, 4); //empty space for the dialog
	buttonSizer->Add(button1, 0, wxALL, 4);
	if (button2)
		buttonSizer->Add(button2, 0, wxALL, 4);

	if (button3)
		buttonSizer->Add(button3, 0, wxALL, 4);

	mainSizer->Add(buttonSizer, 0, wxALIGN_CENTRE, 4);
	SetSizerAndFit(mainSizer);
	Layout();
}

void wxCustomDialog::OnButton1(wxCommandEvent& WXUNUSED(event))
{
	EndModal(ID_BUTTON1);
}

void wxCustomDialog::OnButton2(wxCommandEvent& WXUNUSED(event))
{
	EndModal(ID_BUTTON2);
}

void wxCustomDialog::OnButton3(wxCommandEvent& WXUNUSED(event))
{
	EndModal(ID_BUTTON3);
}

int wxCustomDialog::ShowModal()
{
	int result;
	result = wxDialog::ShowModal();
	if (result == ID_BUTTON1)
		return 1;
	else if (result == ID_BUTTON2)
		return 2;
	else if (result == ID_BUTTON3)
		return 3;
	else
		return 0;
}

bool wxCustomDialog::IsChecked()
{
	if (m_checkbox)
		return m_checkbox->IsChecked();
	else
		return FALSE;
}

wxLoginDialog::wxLoginDialog(wxWindow* parent, const wxString& message, const wxString& caption,
		const wxString& initUsername, const wxString& initPassword, const wxString& checkText,
		long style, const wxPoint& pos)
{
		//create the dialog window
	if (!wxDialog::Create(parent, wxID_ANY, caption, pos, wxDefaultSize, wxDEFAULT_DIALOG_STYLE)){
		return;
	}

	wxStaticText* mymessage = new wxStaticText(this, wxID_ANY, message);
	wxStaticText* userlabel = new wxStaticText(this, wxID_ANY, _("Username"));
	usertext = new wxTextCtrl(this, wxID_ANY, initUsername);
	wxStaticText* passlabel = new wxStaticText(this, wxID_ANY, _("Password"));
	passtext = new wxTextCtrl(this, wxID_ANY, initPassword, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);

	m_username = initUsername;
	m_password = initPassword;

	wxButton* okButton = new wxButton(this, wxID_OK, _("OK"));
	wxButton* cancelButton = new wxButton(this, wxID_CANCEL, _("Cancel"));

	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(mymessage, 0, wxALL, 10);
	
	mainSizer->Add(userlabel, 0, wxLEFT, 4);
	mainSizer->Add(usertext, 1, wxEXPAND | wxALL, 4);
	mainSizer->Add(passlabel, 0, wxLEFT, 4);
	mainSizer->Add(passtext, 1, wxEXPAND | wxALL, 4);

	if (checkText != wxEmptyString)
	{
		m_checkbox = new wxCheckBox(this, wxID_ANY, checkText);
		mainSizer->Add(m_checkbox, 0, wxEXPAND | wxALL, 4);
	}

	wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
	buttonSizer->Add(1, 1, 1, wxEXPAND | wxALL, 4); //empty space for the dialog
	buttonSizer->Add(okButton, 0, wxALL, 4);
	buttonSizer->Add(cancelButton, 0, wxALL, 4);

	mainSizer->Add(buttonSizer, 0, wxEXPAND);
	SetSizerAndFit(mainSizer);
	Layout();
}

int wxLoginDialog::ShowModal()
{
	int result;
	result = wxDialog::ShowModal();
	m_username = usertext->GetValue();
	m_password = passtext->GetValue();
	return result;
}

bool wxLoginDialog::IsChecked()
{
	if (m_checkbox)
		return m_checkbox->IsChecked();
	else
		return FALSE;
}
