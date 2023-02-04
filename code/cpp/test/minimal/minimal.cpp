/////////////////////////////////////////////////////////////////////////////
// Name:        minimal.cpp
// Purpose:     Minimal wxWidgets sample
// Author:      Julian Smart 
// Modified by:
// Created:     04/01/98
// RCS-ID:      $Id: minimal.cpp 43915 2006-12-11 09:33:34Z CE $
// Copyright:   (c) Julian Smart
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// ============================================================================
// declarations
// ============================================================================

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

// ----------------------------------------------------------------------------
// resources
// ----------------------------------------------------------------------------

// the application icon (under Windows and OS/2 it is in resources and even
// though we could still include the XPM here it would be unused)
#if !defined(__WXMSW__) && !defined(__WXPM__)
#include "sample.xpm"
#endif

#include <iostream>
#include "Init.h"
#include "MiroBrowserEmbed.h"

#if USE_WX

// ----------------------------------------------------------------------------
// private classes
// ----------------------------------------------------------------------------

// Define a new application type, each program should derive a class from wxApp
class MyApp : public wxApp
{
public:
	// override base class virtuals
	// ----------------------------

	// this one is called on application startup and is a good place for the app
	// initialization (doing it here and not in the ctor allows to have an error
	// return: if OnInit() returns false, the application terminates)
	virtual bool OnInit();
	MyApp();
	~MyApp();
		
	MiroBrowserEmbed* 	m_pChrome;

};

// Define a new frame type: this is going to be our main frame
class MyFrame : public wxFrame
{
	public:
		// ctor(s)
		MyFrame ( const wxString& title, MiroBrowserEmbed* 	pChrome );

		// event handlers (these functions should _not_ be virtual)
		void OnQuit 	( wxCommandEvent& event );
		void OnAbout 	( wxCommandEvent& event );
		void OnSize		( wxSizeEvent &event	);
	    void OnPaint	( wxPaintEvent& WXUNUSED(evt)	);

	private:
		MiroBrowserEmbed* 	m_pChrome;
		// any class wishing to process wxWidgets events must use this macro
		DECLARE_EVENT_TABLE()
};

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

// IDs for the controls and the menu commands
enum
{
	// menu items
	Minimal_Quit = wxID_EXIT,

	// it is important for the id corresponding to the "About" command to have
	// this standard value as otherwise it won't be handled properly under Mac
	// (where it is special and put into the "Apple" menu)
	Minimal_About = wxID_ABOUT
};

// ----------------------------------------------------------------------------
// event tables and other macros for wxWidgets
// ----------------------------------------------------------------------------

// the event tables connect the wxWidgets events with the functions (event
// handlers) which process them. It can be also done at run-time, but for the
// simple menu events like this the static method is much simpler.
BEGIN_EVENT_TABLE ( MyFrame, wxFrame )
	EVT_MENU ( Minimal_Quit,  MyFrame::OnQuit )
	EVT_MENU ( Minimal_About, MyFrame::OnAbout )
    EVT_PAINT( MyFrame::OnPaint		)
	EVT_SIZE ( MyFrame::OnSize )
END_EVENT_TABLE()

#endif //#if USE_WX

static gboolean delete_event( GtkWidget *widget, GdkEvent *event,
gpointer data ) {
		gtk_main_quit();
		return FALSE;

}

// Create a new application object: this macro will allow wxWidgets to create
// the application object during program execution (it's better than using a
// static object for many reasons) and also implements the accessor function
// wxGetApp() which will return the reference of the right type (i.e. MyApp and
// not wxApp)
//IMPLEMENT_APP(MyApp)
#if USE_WX
IMPLEMENT_APP_CONSOLE ( MyApp )
#else
#include <gtk/gtk.h>
int main(int argc, char** argv){
	nsresult rv;
	GtkWidget* window;
	gtk_init (&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_show(window);

	init_xulrunner();
	MiroBrowserEmbed* pChrome = new MiroBrowserEmbed();
	pChrome->init(window, 0, 0, 1280, 800 );

	g_signal_connect(G_OBJECT(window), "delete_event",G_CALLBACK(delete_event), 0);
	gtk_main();

	delete pChrome;
	shutdown_xulrunner();

	printf("exit...\n");
}
#endif




#if USE_WX

// ============================================================================
// implementation
// ============================================================================
using namespace std;

// ----------------------------------------------------------------------------
// the application class
// ----------------------------------------------------------------------------
MyApp::MyApp() 
{	
	m_pChrome = 0;
	init_xulrunner();
	cout << "MyApp" << endl;
}

MyApp::~MyApp() 
{
	if ( m_pChrome ) delete m_pChrome;
	shutdown_xulrunner();
	cout << "~MyApp" << endl;
}

// 'Main program' equivalent: the program execution "starts" here
bool MyApp::OnInit()
{
	// call the base class initialization method, currently it only parses a
	// few common command-line options but it could be do more in the future
	if ( !wxApp::OnInit() )
		return false;


	m_pChrome = new MiroBrowserEmbed();
	// create the main application window
	MyFrame* frame = new MyFrame ( _T ( "Minimal wxWidgets App" ), m_pChrome );

	//pChrome->AddRef();
	m_pChrome->init(frame, 0, 0, 1024, 800 );
	
	// and show it (the frames, unlike simple controls, are not shown when
	// created initially)
	frame->Show ( true );

	// success: wxApp::OnRun() will be called which will enter the main message
	// loop and the application will run. If we returned false here, the
	// application would exit immediately.
	return true;
}

// ----------------------------------------------------------------------------
// main frame
// ----------------------------------------------------------------------------

// frame constructor
MyFrame::MyFrame ( const wxString& title, MiroBrowserEmbed* pChrome  ) 
: 	wxFrame ( NULL, wxID_ANY, title ),
	m_pChrome(pChrome) 	
{
	// set the frame icon
	SetIcon ( wxICON ( sample ) );

#if wxUSE_MENUS
	// create a menu bar
	wxMenu *fileMenu = new wxMenu;

	// the "About" item should be in the help menu
	wxMenu *helpMenu = new wxMenu;
	helpMenu->Append ( Minimal_About, _T ( "&About...\tF1" ), _T ( "Show about dialog" ) );

	fileMenu->Append ( Minimal_Quit, _T ( "E&xit\tAlt-X" ), _T ( "Quit this program" ) );

	// now append the freshly created menu to the menu bar...
	wxMenuBar *menuBar = new wxMenuBar();
	menuBar->Append ( fileMenu, _T ( "&File" ) );
	menuBar->Append ( helpMenu, _T ( "&Help" ) );

	// ... and attach this menu bar to the frame
	SetMenuBar ( menuBar );
#endif // wxUSE_MENUS

#if wxUSE_STATUSBAR
	// create a status bar just for fun (by default with 1 pane only)
	CreateStatusBar ( 2 );
	SetStatusText ( _T ( "Welcome to wxWidgets!" ) );
#endif // wxUSE_STATUSBAR
}




// event handlers


void MyFrame::OnSize ( wxSizeEvent &pEvent )
{
	printf ("MyFrame::OnSize: %p\n", m_pChrome);
	if ( m_pChrome && m_pChrome->mBrowserBaseWindow ) {
		wxRect newRect = this->GetClientRect();
		m_pChrome->mBrowserBaseWindow->SetPositionAndSize ( 
				newRect.GetLeft(), newRect.GetTop(),
		        newRect.GetWidth(), newRect.GetHeight(), 
				PR_FALSE );
	}
}

void MyFrame::OnPaint(wxPaintEvent& WXUNUSED(evt))
{
	printf("MyFrame::OnPaint\n");

}

void MyFrame::OnQuit ( wxCommandEvent& WXUNUSED ( event ) )
{
	// true is to force the frame to close
	Close ( true );
}

void MyFrame::OnAbout ( wxCommandEvent& WXUNUSED ( event ) )
{
	wxMessageBox ( wxString::Format (
	                   _T ( "Welcome to %s!\n" )
	                   _T ( "\n" )
	                   _T ( "This is the minimal wxWidgets sample\n" )
	                   _T ( "running under %s." ),
	                   wxVERSION_STRING,
	                   wxGetOsDescription().c_str()
	               ),
	               _T ( "About wxWidgets minimal sample" ),
	               wxOK | wxICON_INFORMATION,
	               this );
}
#endif //#if USE_WX
