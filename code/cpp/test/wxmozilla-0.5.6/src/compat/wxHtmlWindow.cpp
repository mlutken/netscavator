/*
 * wxMozilla wxHtmlWindow Wrapper
 * 
 * Developers:
 *  Jeremiah Cornelius McCarthy <jeremiah@whoop-ass.ca>
 *  Kevin Ollivier <kevino@tulane.edu>
 *  Dave Fancella <david.fancella@attbi.com>
 */    
#ifdef __GNUG__
#pragma implementation "mozillawin.h"
#endif

#include "wxHtmlWindow.h"

#ifdef __BORDLANDC__
#pragma hdrstop
#endif


wxHtmlWindow::wxHtmlWindow()
{
//	_impl = new wxMozillaBrowser();
}

wxHtmlWindow::wxHtmlWindow(
  wxWindow *parent, wxWindowID id = -1,
  const wxPoint& pos = wxDefaultPosition,
  const wxSize& size = wxDefaultSize,
  long style = wxHW_SCROLLBAR_AUTO,
  const wxString& name = wxT("mozillaWindow"))
{
//	_impl = new wxMozillaBrowser();
}


wxHtmlWindow::~wxHtmlWindow() 
{
  delete _impl;
}

bool wxHtmlWindow::Create(
  wxWindow *parent, wxWindowID id = -1,
  const wxPoint& pos = wxDefaultPosition,
  const wxSize& size = wxDefaultSize,
  long style = wxHW_SCROLLBAR_AUTO,
  const wxString& name = wxT("htmlWindow"))
{
  return _impl->Create(parent, id, pos, size, style, name)
}

bool wxHtmlWindow::SetPage(const wxString& source)
{
  return _impl->SetPage(source);
}
    
bool wxHtmlWindow::AppendToPage(const wxString& source)
{
  return _impl->AppendToPage(source);
}

bool wxHtmlWindow::LoadPage(const wxString& location)
{
  return _impl->LoadPage(location);
}

wxString wxHtmlWindow::GetOpenedPage() 
{
  return _impl->GetOpenedPage();
}

wxString wxHtmlWindow::GetOpenedAnchor() 
{
  return _impl->GetOpenedAnchor();
}

wxString wxHtmlWindow::GetOpenedPageTitle()
{
  return _impl->GetOpenedPageTitle();
}

void wxHtmlWindow::SetRelatedFrame(wxFrame* frame, const wxString& format)
{
  return _impl->SetRelatedFrame(frame, format);
}

wxFrame* wxHtmlWindow::GetRelatedFrame()
{
  return _impl->GetRelatedFrame();
}

void wxHtmlWindow::SetRelatedStatusBar(int bar)
{
  _impl->SetRelatedStatusBar(bar);
}

void wxHtmlWindow::SetFonts(wxString normal_face, wxString fixed_face, const int *sizes)
{
}

void wxHtmlWindow::SetBorders(int b) 
{
}

bool wxHtmlWindow::HistoryBack()
{
  return _impl->HistoryBack();
}

bool wxHtmlWindow::HistoryForward()
{
  return _impl->HistoryForward();
}

bool wxHtmlWindow::HistoryCanBack()
{
  return _impl->HistoryCanBack();
}

bool wxHtmlWindow::HistoryCanForward()
{
  return _impl->HistoryCanForward();
}

void wxHtmlWindow::HistoryClear()
{
  _impl->HistoryClear();
}



