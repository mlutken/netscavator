
#if 1
#include "auidemo.cpp"
#else 

#include <hacks/wx_h_include_hack.h>
#include <hacks/wx_h_php_undef_hack.h>
#include <iostream>
#include <nsComponentManagerUtils.h>
#include <nsEmbedCID.h>
#include <utils/webbrowse_embedding_utils.h>
#include <webbrwsr/DefaultChromeEmbed.h>
#include <webbrwsr/DefaultWxBrowserFrame.h>
#include <MozBrowserWx.h>

#include "TestCreatorBrowserFrame.h"
#include "TestCreatorBrowserControl.h"
  
// ----------------------------------------------------------------------------
// private classes
// ----------------------------------------------------------------------------

// Define a new application type, each program should derive a class from wxApp
class MyApp : public wxApp
{
public:

	// this one is called on application startup and is a good place for the app
	// initialization (doing it here and not in the ctor allows to have an error
	// return: if OnInit() returns false, the application terminates)
	virtual bool OnInit();
	virtual int	 OnExit();
//	virtual bool OnInit( int argc, char** argv );
	MyApp();
	~MyApp();
	wxFrame*				m_pFrame;
	
	MozBrowserWx::Ptr		m_pMozBrowserWx;
};

// -- wxSizeReportCtrl --
// (a utility control that always reports it's client size)

class wxSizeReportCtrl : public wxControl
{
public:

    wxSizeReportCtrl(wxWindow* parent, wxWindowID id = wxID_ANY,
                     const wxPoint& pos = wxDefaultPosition,
                     const wxSize& size = wxDefaultSize )
                     : wxControl(parent, id, pos, size, wxNO_BORDER)
    {
    }

private:

    void OnPaint(wxPaintEvent& WXUNUSED(evt))
    {
        wxPaintDC dc(this);
        wxSize size = GetClientSize();
        wxString s;
        int h, w, height;

        s.Printf(wxT("Size: %d x %d"), size.x, size.y);

        dc.SetFont(*wxNORMAL_FONT);
        dc.GetTextExtent(s, &w, &height);
        height += 3;
        dc.SetBrush(*wxWHITE_BRUSH);
        dc.SetPen(*wxWHITE_PEN);
        dc.DrawRectangle(0, 0, size.x, size.y);
        dc.SetPen(*wxLIGHT_GREY_PEN);
        dc.DrawLine(0, 0, size.x, size.y);
        dc.DrawLine(0, size.y, size.x, 0);
        dc.DrawText(s, (size.x-w)/2, ((size.y-(height*5))/2));

    }

    void OnEraseBackground(wxEraseEvent& WXUNUSED(evt))
    {
        // intentionally empty
    }

    void OnSize(wxSizeEvent& WXUNUSED(evt))
    {
        Refresh();
    }
private:


    DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(wxSizeReportCtrl, wxControl)
    EVT_PAINT(wxSizeReportCtrl::OnPaint)
    EVT_SIZE(wxSizeReportCtrl::OnSize)
    EVT_ERASE_BACKGROUND(wxSizeReportCtrl::OnEraseBackground)
END_EVENT_TABLE()


IMPLEMENT_APP_CONSOLE ( MyApp )



// ============================================================================
// implementation
// ============================================================================
#include "test_events.cpp"

using namespace std;
// ----------------------------------------------------------------------------
// the application class
// ----------------------------------------------------------------------------

MyApp::MyApp() 
{	
	cout << "MyApp" << endl;
	initXulrunner();
}

int MyApp::OnExit()
{
	cout << "MyApp::OnExit" << endl;
	m_pMozBrowserWx.reset();
	return 0;
}

MyApp::~MyApp() 
{
	cout << "~MyApp" << endl;
	shutdownXulrunner();
}

/*
bool MyApp::OnInit()
{
	cout << "MyApp::OnInit: TestCreatorBrowserFrame" << endl;
	if ( !wxApp::OnInit() )		return false;
	TestCreatorBrowserFrame* pBrowserFrame = new TestCreatorBrowserFrame( _T ( "TestCreator" ) );
	
	m_pMozBrowserWx = MozBrowserWx::Ptr( new MozBrowserWx(pBrowserFrame) );
	
	pBrowserFrame->initWebBrowser( m_pMozBrowserWx-> webBrowser()->ifMoz() );
	testEvents_connectSlots ( m_pMozBrowserWx->signalsManager() );
	m_pMozBrowserWx->loadURI("http://www.boost.org");
//	m_pMozBrowserWx->loadURI("file:///home/ml/code/cpaf/cul/boost/doc/html/index.html");
	
	m_pMozBrowserWx->show(); 
	return true;
}
/**/

/**/
bool MyApp::OnInit()
{
	cout << "MyApp::OnInit: TestCreatorBrowserControl" << endl;
	if ( !wxApp::OnInit() )		return false;
	m_pFrame = new wxFrame(NULL, wxID_ANY, _T("Demo") );	
//	wxSizeReportCtrl* pSizeCtrl = new wxSizeReportCtrl( m_pFrame );
	 
	
	
	TestCreatorBrowserControl* pBrowserControl = new TestCreatorBrowserControl( m_pFrame );
	m_pMozBrowserWx = MozBrowserWx::Ptr( new MozBrowserWx(pBrowserControl) );
	
	pBrowserControl->initWebBrowser( m_pMozBrowserWx-> webBrowser()->ifMoz() );
	testEvents_connectSlots ( m_pMozBrowserWx->signalsManager() );
	m_pMozBrowserWx->loadURI("http://www.boost.org");
	//	m_pMozBrowserWx->loadURI("file:///home/ml/code/cpaf/cul/boost/doc/html/index.html");
	//	m_pMozBrowserWx->show(); 
	m_pFrame->Show(true);
	return true;
}
/**/

#endif

