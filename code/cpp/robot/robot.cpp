
// For compilers that support precompilation, includes "wx/wx.h".
#include <hacks/wx_h_include_hack.h>
#include <hacks/wx_h_php_undef_hack.h>
#include <wx/cmdline.h>

#include <iostream>
#include <string>
#include <boost/bind.hpp>
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
#include <php_embedding/php_embedding_utils.h>
#include <Configuration.h>
#include <Globals.h>
#include <wx_command_line.h>

const int MAX_ARGS = 10;


// -- application --
//typedef boost::function< void ( void ) >	OnMiningDoneFunT;

class MyApp : public wxApp
{
public:
	MyApp();
	~MyApp();
    bool    OnInit();
    int     OnExit();
    void	onMiningDone();
    virtual void OnInitCmdLine(wxCmdLineParser& parser);
    virtual bool OnCmdLineParsed(wxCmdLineParser& parser);
    //Data
private:
 CreatorMainFrameWx*   m_frame;
};


DECLARE_APP(MyApp)
//IMPLEMENT_APP(MyApp)
IMPLEMENT_APP_CONSOLE(MyApp)



        // -- frame --

        using namespace std;

MyApp::MyApp()
    : m_frame(0)
{
}

int MyApp::OnExit()
{
    if (m_frame) m_frame->endMining();
    return 0;
}

void MyApp::onMiningDone()
{
    printf("MyApp::onMiningDone()\n");
    if (m_frame) m_frame->endMining();
    if ( crawl::g()->configuration()->valueStrGet("exit-when-done" ) == "yes" )
    {
        printf("MyApp::exit()\n");
        this->ExitMainLoop();
    }

}

MyApp::~MyApp()
{
    shutdownPhp();
    //shutdownXulrunner();
}


bool MyApp::OnInit()
{
    //testPhpNoMiner();

    // call default behaviour (mandatory)
    if ( !wxApp::OnInit() ) return false;

    boost::shared_ptr<crawl::Configuration> c= crawl::g()->configuration();

    printf("Config url                 : %s\n", c->valueStrGet("url").c_str() );
    printf("Config exe-path            : %s\n", c->valueStrGet("exe-path").c_str() );
    printf("Config exe-dir             : %s\n", c->valueStrGet("exe-dir").c_str() );
    printf("Config exe-name            : %s\n", c->valueStrGet("exe-name").c_str() );
    printf("Config exe-stemname        : %s\n", c->valueStrGet("exe-stemname").c_str() );
    printf("Config cfg-path            : %s\n", c->valueStrGet("cfg-path").c_str() );
    printf("Config xul-dir             : %s\n", c->valueStrGet("xul-dir").c_str() );
    printf("Config run-mode            : %s\n", c->valueStrGet("run-mode").c_str() );
    printf("Config upload-result       : %s\n", c->valueStrGet("upload-result").c_str() );
    printf("Config load-images         : %s\n", c->valueStrGet("load-images").c_str() );
    printf("Config script-path         : %s\n", c->valueStrGet("script-path").c_str() );
    printf("Config script-name         : %s\n", c->valueStrGet("script-name").c_str() );
    printf("Config script-dir          : %s\n", c->valueStrGet("script-dir").c_str() );
    printf("Config php-ini-path        : %s\n", c->valueStrGet("php-ini-path").c_str() );
    printf("Config Script arguments    : %s\n", c->phpArgsStr().c_str() );
    printf("Config Script include dirs : %s\n", c->scriptIncludeDirsStr().c_str() );
    printf("Config exit-when-done      : %s\n", c->valueStrGet("exit-when-done").c_str() );
    printf("Config win-width           : %d\n", c->valueIntGet("win-width") );
    printf("Config win-height          : %d\n", c->valueIntGet("win-height") );

    //crawl::Url url(c->valueStrGet("url"), false, true );

    //printf("Temporary for command line test we exit here!: Url: '%s'\n", url.string().c_str() );
    //exit(1);

//    std::string sXULRUNNER_PATH_CREATOR = cpaf::system::get_env("XULRUNNER_PATH_CREATOR");
//    if ( sXULRUNNER_PATH_CREATOR != "" ) {
//        initXulrunner(sXULRUNNER_PATH_CREATOR, "" );
//    }
//    else {
//        initXulrunner();
//    }


    char** argvPhp;
    int  argcPhp;

    argvPhp = allocateArrayOfStrings(MAX_ARGS, 256);
    c->getScriptArgvArgc( argcPhp, argvPhp );


    startupPhpScript(c->valueStrGet("php-ini-path").c_str(), argcPhp, argvPhp );
    freeArrayOfStrings( argvPhp, MAX_ARGS );
    executePhpString("require_once 'webminer.php';");
    executePhpFile(c->valueStrGet("script-path").c_str());

    initXulrunner(c->valueStrGet("xul-dir"), "CRAWLER_XUL_RUNNER_PATH" );
    wxString windowTitle(c->valueStrGet("script-name").c_str(), wxConvUTF8 );

    m_frame = new CreatorMainFrameWx(
            boost::bind(&MyApp::onMiningDone, this),
            NULL,
            wxID_ANY,
            wxT("Crawler: ") + windowTitle,
            wxDefaultPosition,
            wxSize(c->valueIntGet("win-width"), c->valueIntGet("win-height")));
    SetTopWindow(m_frame);
    m_frame->Show();

    return true;
}


// ./crawler/_test/simple_test.php

void MyApp::OnInitCmdLine(wxCmdLineParser& parser)
{
    onInitCmdLineRobot(parser);
}


bool MyApp::OnCmdLineParsed(wxCmdLineParser& parser)
{
    char** argvOut;
    int  argcOut;

    argvOut = allocateArrayOfStrings(MAX_ARGS, 256);
    wxGetCommandLineParams( argc, argv, argcOut, argvOut );
    if ( !crawl::g()->configuration()->parseCommandLine( "crawler", argcOut, argvOut ) ) {
        exit(0);
    }
    freeArrayOfStrings( argvOut, MAX_ARGS );
    return true;
}
