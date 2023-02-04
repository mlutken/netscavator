/*
 * wxMozillaWindow Sample Application
 * Copyright 2001 (c) Jeremiah Cornelius McCarthy. All Rights Reserved.
 */

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include "wx/filesys.h"
#include "wx/fs_inet.h"
#include "wx/fs_zip.h"
#include "wx/fs_mem.h"

#include "wxMozillaBrowser.h"
#include "wxMozillaWindow.h"
#include "wxMozillaProtocolHandler.h"

class wxMozillaDemo: public wxApp
{
public:

	virtual bool OnInit();
};



/**
 * The GuruProtocolHandler is the simplest wrapper around protocols
 * opening guru://uri is equivalent to opening uri
 */
class GuruProtocolHandler : public wxFSProtocolHandler
{
public:
  GuruProtocolHandler(const wxString scheme) : wxFSProtocolHandler(scheme)
  {    
  }
  ~GuruProtocolHandler()
  {
  }
  const wxString NewURI(const wxString spec, const wxString base)
  {
    
    if(base.IsEmpty()||spec.StartsWith(wxT("guru://")))
      return spec;
    wxString mutable_base = base;
    //TODO: replace // with / whenever needed (i.e. not in a :// part)
    const int slash_position = base.Find(wxT('/'), TRUE);
    if(slash_position>7)
      if(!((base[slash_position-1]=='/')&&(base[slash_position-2]==':')))
	mutable_base = base.Mid(0,slash_position);
      else
	mutable_base = base;
    else
      mutable_base = base;

    if (!spec.StartsWith(wxT("/")))
      mutable_base=mutable_base+wxT('/');

    return mutable_base+spec;
  }
  wxProtocolChannel* OpenChannel(const wxString uri)
  {    
    wxString after;
    uri.StartsWith(wxT("guru://"), &after); 
		
    return wxFSProtocolHandler::OpenChannel(after);
  }
  static wxProtocolHandler* Create(const wxString scheme)
  {
	  return new GuruProtocolHandler(scheme);
  }
protected:
  wxFileSystem mFileSystem;
};


bool wxMozillaDemo::OnInit()
{
	wxFileSystem::AddHandler(new wxInternetFSHandler());
	wxFileSystem::AddHandler(new wxZipFSHandler());
	wxFileSystem::AddHandler(new wxMemoryFSHandler());

	wxMozillaWindow *MainWnd;
	MainWnd = new wxMozillaWindow();
	
	
	const wxUId id = {(wxUint32)0x8a2bcf71,(wxUint16)0x3f5b,(wxUint16)0x4559,
		{(wxUint8)0x89, (wxUint8)0x0f,(wxUint8)0xf3,(wxUint8)0xc2,(wxUint8)0xe9,(wxUint8)0x8e,
		(wxUint8)0xa7,(wxUint8)0x01}};
	
	wxRegisterProtocolHandler(wxT("The Guru protocol handler"), wxT("guru"), id, &(GuruProtocolHandler::Create));
		
	MainWnd->Show(TRUE);
	//wxMainWnd *MainWnd;

	//MainWnd = new wxMainWnd();
	//MainWnd->Show(TRUE);

	return TRUE;
};


//wxREGISTER_CUSTOM_PROTOCOL_HANDLER(GuruProtocolHandler, wxT("The Guru Protocol Handler"), wxT("guru"))


IMPLEMENT_APP(wxMozillaDemo)
