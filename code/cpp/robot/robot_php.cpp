
// For compilers that support precompilation, includes "wx/wx.h".
#include <hacks/wx_h_include_hack.h>
#include <hacks/wx_h_php_undef_hack.h>
#include <iostream>
#include <string>
#include <cpaf_session.h>
#include <utils/webbrowse_embedding_utils.h>
#include <ScriptMiner.h>
#include <wx/CreatorMainFrameWx.h>
#include "wx/wxprec.h"

#include <parser/LinearDomSearch.h>

#include <control/DomTreeTextCtrl.h>
#include <control/BrowserWindowCtrl.h>
#include <wx/UrlToolBarWx.h>
#include <wx/FindToolBarWx.h>

#error GGGGGGGGGGGGGg

// -- application --

class MyApp : public wxApp
{
public:
	MyApp();
	~MyApp();
	bool OnInit();
	int	 OnExit();
	//Data
};

DECLARE_APP(MyApp)
//IMPLEMENT_APP(MyApp)
IMPLEMENT_APP_CONSOLE(MyApp)



// -- frame --





using namespace std;

bool MyApp::OnInit()
{
    wxFrame* frame = new CreatorMainFrameWx(NULL,
                                 wxID_ANY,
                                 wxT("Miner Creator"),
                                 wxDefaultPosition,
                                 wxSize(800, 600));
    SetTopWindow(frame);
    frame->Show();

    return true;
}

MyApp::MyApp()
{
    std::string sXULRUNNER_PATH_CREATOR = cpaf::system::get_env("XULRUNNER_PATH_CREATOR");
    if ( sXULRUNNER_PATH_CREATOR != "" ) {
        initXulrunner(sXULRUNNER_PATH_CREATOR, "" );
    }
    else {
        initXulrunner();
    }
}

int MyApp::OnExit()
{
	return 0;
}

MyApp::~MyApp()
{
	shutdownXulrunner();
}


