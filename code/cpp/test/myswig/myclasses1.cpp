// ----------------------------------------------------------------------------
// --- BEGIN: Some hacks to make php and wxWidgets work together on Windows ---
// ----------------------------------------------------------------------------
/* Include this before anything else if you have problems like multiple defined winsock functions.  */
#if (defined _WINDOWS) || (defined WINDOWS) || (defined _WIN32) 
#	include <winsock2.h>
#endif
#include <wx/wx.h>
// --- Wx and php has some clashes on Windows. Seems to be mostly php's fault ---
#if (defined _WINDOWS) || (defined WINDOWS) || (defined _WIN32) 
#	undef M_PI
#	undef _WIN32_WINNT
#endif
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


#include "myclasses1.h"


 
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

// -----------------------
// --- WxWidgets Stuff ---
// -----------------------

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};


class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title);
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
private:
    DECLARE_EVENT_TABLE()
};


enum {   My_Quit = wxID_EXIT,    My_About = wxID_ABOUT };


// the event tables connect the wxWidgets events with the functions (event
// handlers) which process them. It can be also done at run-time, but for the
// simple menu events like this the static method is much simpler.
BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(My_Quit,  MyFrame::OnQuit)
    EVT_MENU(My_About, MyFrame::OnAbout)
END_EVENT_TABLE()





IMPLEMENT_APP_NO_MAIN(MyApp)


bool MyApp::OnInit()
{
    if ( !wxApp::OnInit() )	return false;
    MyFrame *frame = new MyFrame(_T("Minimal wxWidgets App"));
    frame->Show(true);
    return true;
}



MyFrame::MyFrame(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title)
{
    wxMenu *fileMenu = new wxMenu;
    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(My_About, _T("&About...\tF1"), _T("Show about dialog"));
    fileMenu->Append(My_Quit, _T("E&xit\tAlt-X"), _T("Quit this program"));
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, _T("&File"));
    menuBar->Append(helpMenu, _T("&Help"));
    SetMenuBar(menuBar);
    CreateStatusBar(2);
    SetStatusText(_T("Welcome to wxWidgets!"));
}


void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{	Close(true);	}

void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{}



void startWx()
{
	std::cout << "startWx()" << std::endl;
	char*  szArgv[2] = { "", "" }; 
	int iArgc = 1;
	wxEntry( iArgc, &szArgv[0] );
}


//void	startWx()
//{
//	std::cout << "startWx() " << std::endl;
//}

// /FORCE:MULTIPLE