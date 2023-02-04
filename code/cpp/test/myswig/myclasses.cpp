// ----------------------------------------------------------------------------
// --- BEGIN: Some hacks to make php and wxWidgets work together on Windows ---
// ----------------------------------------------------------------------------
#include <hacks/wx_h_include_hack.h>
#include <hacks/wx_h_php_undef_hack.h>
#include <zend.h>
#include <zend_interfaces.h>
#include <zend_globals_macros.h>
#include <zend_globals.h>
#include <TSRM.h>
#include <zend_API.h>
#include <php.h>
// ----------------------------------------------------------------------------
// --- END: Some hacks to make php and wxWidgets work together on Windows ---
// ----------------------------------------------------------------------------

#include <math.h>
#include <iostream>

#include "myclasses.h"
 
Vector::Vector( double  iX, double iY, double iZ )
	: x(iX), y(iY), z(iZ)
{
	std::cout << "Vector CONSTRUCTOR: " << x << ", " << y << ", " << z << std::endl;
}

Vector::~Vector()
{
	std::cout << "Vector DESTRUCTOR" << std::endl;
}
 
double
Vector::len2() 
{ 
	return x*x + y*y + z*z; 
}

double
Vector::len() 
{ 
	return sqrt(x*x + y*y + z*z); 
}

double
Vector::magnitude() 
{ 
	return sqrt(x*x + y*y + z*z); 
}

// ----------------------
// --- Callback Stuff ---
// ----------------------


void callCallback( const char* szCallBack )
{
	std::cout << "callCallback( " << szCallBack << " )" << std::endl;

	zval* 			function_name;
	zval*			retval;
	
    ALLOC_INIT_ZVAL(function_name);
//	ZVAL_STRING(function_name, (char*)"test_function", 1 );
	ZVAL_STRING(function_name, (char*)szCallBack, 1 );
	
	// int call_user_function_ex( HashTable*, zval**, zval*, zval**, zend_uint, zval***, int, HashTable* );
 	if ( call_user_function_ex( CG(function_table), NULL, function_name, &retval, 0, NULL, 0, NULL ) != SUCCESS )
 	{
 		zend_error(E_ERROR, "Function call from C++ to php callback '%s' failed", szCallBack );
 	}

	zend_printf("X zend_hash_num_elements(): %d \n", zend_hash_num_elements(EG(function_table)) );
	zend_printf("We have '%s' as val\n", Z_STRVAL_P(function_name) );
	zend_printf("retval '%s' \n", Z_STRVAL_P(retval) );
//	zend_printf("We have '%s' as val\n", function_name->value.str.val );
	
//	zval* return_value = *retval;
//	zval_copy_ctor(return_value);
	zval_ptr_dtor(&retval);
    zval_ptr_dtor(&function_name);	
}


void list_functions( )
{
	std::cout << "list_functions() " << std::endl;

	HashPosition 	function_pos;
	zend_function* 	function_find;

	
	std::string sFunName("test_function");
	int iExist = zend_hash_find( EG(function_table), (char*)sFunName.c_str(), sFunName.size() +1, (void**)&function_find );
	zend_printf("X zend_hash_find(""): %d \n", iExist );
	
//	zend_call_method();
	
	
	if ( SUCCESS == zend_hash_find( EG(function_table), (char*)sFunName.c_str(), sFunName.size() +1, (void**)&function_find ) ) {
		zend_printf("function_name: %s \n", function_find->common.function_name );
	}
	zend_hash_internal_pointer_reset_ex( EG(function_table), &function_pos);
	while ( zend_hash_has_more_elements_ex( EG(function_table), &function_pos) == SUCCESS && !EG(exception) ) {
		zend_hash_get_current_data_ex( EG(function_table), (void**)&function_find, &function_pos);
//		zend_hash_get_current_data_ex(SPL_G(autoload_functions), (void **) &alfi, &function_pos);
//		zend_call_method(alfi->obj ? &alfi->obj : NULL, alfi->ce, &alfi->func_ptr, func_name, func_name_len, &retval, 1, class_name, NULL TSRMLS_CC);
		zend_printf("FUN: %s \n", function_find->common.function_name );
		zend_hash_move_forward_ex( EG(function_table), &function_pos);
	}
	
	zend_printf("X zend_hash_num_elements(): %d \n", zend_hash_num_elements(EG(function_table)) );
}


void list_classes( )
{
	std::cout << "list_classes() " << std::endl;

	HashPosition 		ce_pos;
	zend_class_entry* 	ce_find;

	
//	std::string sFunName("test_function");
//	int iExist = zend_hash_find( EG(function_table), (char*)sFunName.c_str(), sFunName.size() +1, (void**)&function_find );
//	zend_printf("X zend_hash_find(""): %d \n", iExist );
	
//	zend_call_method();
	
	
//	if ( SUCCESS == zend_hash_find( EG(function_table), (char*)sFunName.c_str(), sFunName.size() +1, (void**)&function_find ) ) {
//		zend_printf("function_name: %s \n", function_find->common.function_name );
//	}
	zend_hash_internal_pointer_reset_ex( CG(class_table), &ce_pos);
	while ( zend_hash_has_more_elements_ex( CG(class_table), &ce_pos) == SUCCESS && !EG(exception) ) {
		zend_hash_get_current_data_ex( CG(class_table), (void**)&ce_find, &ce_pos);
//		zend_hash_get_current_data_ex(SPL_G(autoload_functions), (void **) &alfi, &function_pos);
//		zend_call_method(alfi->obj ? &alfi->obj : NULL, alfi->ce, &alfi->func_ptr, func_name, func_name_len, &retval, 1, class_name, NULL TSRMLS_CC);
		zend_printf("CLASS: %s \n", ce_find->name );
		zend_hash_move_forward_ex( CG(class_table), &ce_pos);
	}
	
//	zend_printf("X zend_hash_num_elements(): %d \n", zend_hash_num_elements(EG(function_table)) );
}


// -----------------------
// --- WxWidgets Stuff ---
// -----------------------

#ifdef USE_WX_EXAMPLE

//#define HAVE_SSIZE_T
#include <wx/wx.h>

// Define a new application type, each program should derive a class from wxApp
class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

// Define a new frame type: this is going to be our main frame
class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title);

    // event handlers (these functions should _not_ be virtual)
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

private:
    DECLARE_EVENT_TABLE()
};

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

enum 
{
    Minimal_Quit = wxID_EXIT,
    Minimal_About = wxID_ABOUT
};


// ----------------------------------------------------------------------------
// event tables and other macros for wxWidgets
// ----------------------------------------------------------------------------

// the event tables connect the wxWidgets events with the functions (event
// handlers) which process them. It can be also done at run-time, but for the
// simple menu events like this the static method is much simpler.
BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(Minimal_Quit,  MyFrame::OnQuit)
    EVT_MENU(Minimal_About, MyFrame::OnAbout)
END_EVENT_TABLE()

// Create a new application object: this macro will allow wxWidgets to create
// the application object during program execution (it's better than using a
// static object for many reasons) and also implements the accessor function
// wxGetApp() which will return the reference of the right type (i.e. MyApp and
// not wxApp)
IMPLEMENT_APP_NO_MAIN(MyApp)
//IMPLEMENT_APP_CONSOLE(MyApp)

// ============================================================================
// implementation
// ============================================================================

// ----------------------------------------------------------------------------
// the application class
// ----------------------------------------------------------------------------

// 'Main program' equivalent: the program execution "starts" here
bool MyApp::OnInit()
{
    // call the base class initialization method, currently it only parses a
    // few common command-line options but it could be do more in the future
    if ( !wxApp::OnInit() )
        return false;

    // create the main application window
    MyFrame *frame = new MyFrame(_T("Minimal wxWidgets App"));

    // and show it (the frames, unlike simple controls, are not shown when
    // created initially)
    frame->Show(true);

    // success: wxApp::OnRun() will be called which will enter the main message
    // loop and the application will run. If we returned false here, the
    // application would exit immediately.
    return true;
}

// ----------------------------------------------------------------------------
// main frame
// ----------------------------------------------------------------------------

// frame constructor
MyFrame::MyFrame(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title)
{

#if wxUSE_MENUS
    // create a menu bar
    wxMenu *fileMenu = new wxMenu;

    // the "About" item should be in the help menu
    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(Minimal_About, _T("&About...\tF1"), _T("Show about dialog"));

    fileMenu->Append(Minimal_Quit, _T("E&xit\tAlt-X"), _T("Quit this program"));

    // now append the freshly created menu to the menu bar...
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, _T("&File"));
    menuBar->Append(helpMenu, _T("&Help"));

    // ... and attach this menu bar to the frame
    SetMenuBar(menuBar);
#endif // wxUSE_MENUS

#if wxUSE_STATUSBAR
    // create a status bar just for fun (by default with 1 pane only)
    CreateStatusBar(2);
    SetStatusText(_T("Welcome to wxWidgets!"));
#endif // wxUSE_STATUSBAR
}


// event handlers

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    // true is to force the frame to close
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
	callCallback ( "test_callback" );
	
	
}

#endif //USE_WX_EXAMPLE

#ifdef USE_WX_EXAMPLE
void startWx()
{
	std::cout << "startWx()" << std::endl;
	char*  szArgv[2] = { "", "" }; 
	
	//wxEntry(argc, argv);
	int iArgc = 1;
	wxEntry( iArgc, &szArgv[0] );
}
#else
void startWx()
{
	std::cout << "To use 'startWx()' please define USE_WX_EXAMPLE in myclasses.h " << std::endl;
}
#endif


