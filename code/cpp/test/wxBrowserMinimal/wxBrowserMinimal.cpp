#include <hacks/wx_h_include_hack.h>
#include <hacks/wx_h_php_undef_hack.h>

#include <iostream>
#include <nsComponentManagerUtils.h>
#include <nsEmbedCID.h>
#include <utils/webbrowse_embedding_utils.h>
#include <webbrwsr/DefaultChromeEmbed.h>
#include <webbrwsr/DefaultWxBrowserFrame.h>
#include <MozBrowserGtk.h>
#include <MozBrowserWx.h>
  
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
	
	MozBrowserWx::Ptr				m_pMozBrowserWx;
};


#if WEBBROWSE_ENABLE_GTK
static gboolean delete_event( GtkWidget *widget, GdkEvent *event,
gpointer data ) {
		gtk_main_quit();
		return FALSE;
}
#endif //WEBBROWSE_ENABLE_GTK

// Create a new application object: this macro will allow wxWidgets to create
// the application object during program execution (it's better than using a
// static object for many reasons) and also implements the accessor function
// wxGetApp() which will return the reference of the right type (i.e. MyApp and
// not wxApp)
//IMPLEMENT_APP(MyApp)
#if 1
IMPLEMENT_APP_CONSOLE ( MyApp )
#else
int main(int argc, char** argv){
	nsresult rv;
	GtkWidget* window;
	gtk_init (&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_show(window);

	initXulrunner();
	DefaultChromeEmbed* pChrome = new DefaultChromeEmbed();
	pChrome->initNativeWindow(window, 0, 0, 1280, 800 );

	g_signal_connect(G_OBJECT(window), "delete_event",G_CALLBACK(delete_event), 0);
	gtk_main();

	delete pChrome;
	shutdownXulrunner();
	printf("exit...\n");
}
#endif



// ============================================================================
// implementation
// ============================================================================
// #include "test_events.cpp"

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

// 'Main program' equivalent: the program execution "starts" here
//bool MyApp::OnInit( int argc, char** argv )
bool MyApp::OnInit()
{
	cout << "MyApp::OnInit xxxxxxxxxxxx" << endl;
	if ( !wxApp::OnInit() )		return false;
	m_pMozBrowserWx = MozBrowserWx::Ptr( new MozBrowserWx() );
// 	testEvents_connectSlots ( m_pMozBrowserWx->signalsManager() );
//	m_pMozBrowserWx->loadURI("http://www.boost.org");
//    m_pMozBrowserWx->loadURI("http://yousee.musik.tdconline.dk");
    m_pMozBrowserWx->loadUri("http://airplaymusic.dk.localhost/");

    m_pMozBrowserWx->sizeSet(800, 600);
	
	m_pMozBrowserWx->show(); 
	return true;
}



