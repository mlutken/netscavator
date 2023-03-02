#include <hacks/wx_h_include_hack.h>
#include <hacks/wx_h_php_undef_hack.h>
#include <zend.h>
#include <zend_interfaces.h>
#include <zend_API.h>
#include <php.h>
#include <SAPI.h>

#include <iostream>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/tokenizer.hpp>
#include <cpaf_string_utils.hpp>

#include <openssl/engine.h>
#include <openssl/ssl.h>
#include <cpaf_http_convenience.h>
#include <cpaf_compression_functions.h>
#include <Globals.h>
#include <scriptcrawl_private_php.h>

#include <hacks/wx_h_include_hack.h>
#include <hacks/wx_h_php_undef_hack.h>
#include "scriptcrawl_private.h"

#include <iostream>
#include <loki/Singleton.h>
#include <utils/webbrowse_embedding_utils.h>
#include <ScriptingClassIF.h>
#include <MozBrowserWx.h>
#include <ScriptMiner.h>

#include <scriptcrawl_private_php.h>
#include <scriptcrawl_private.h>


namespace b = boost;
namespace fs = boost::filesystem;

static int forceLink()
{
    ENGINE_load_builtin_engines();
    SSL_load_error_strings();
    SSL_library_init();
    cpaf::net::curlPostUploadFileSimple("","", boost::filesystem::path() );    // TODO: To force linking of the SSL functions

    cpaf::compression::gzCompress( fs::path(), fs::path());
    cpaf::compression::gzUnCompress( fs::path(), fs::path() );

    namespace fs = boost::filesystem;

    fs::path dstFile("dummy" );
    if ( fs::is_directory(dstFile) ) {
    }
    crawl::g()->forceLink();
    boost::shared_ptr<crawl::ScriptingClassIF> pSc = createPhpScriptingClass();
    return 12;
}

static int iForceLink = forceLink();





// -----------------------
// --- WxWidgets Stuff ---
// -----------------------

// Define a new application type, each program should derive a class from wxApp
class ScriptCrawlApp : public wxApp
{
public:
    ScriptCrawlApp();
    ~ScriptCrawlApp();
    virtual bool 	OnInit();
    virtual int  	OnExit();
    bool			isExiting() const {	return m_bIsExiting;	}
private:
    bool			m_bIsExiting;
};



DECLARE_APP(ScriptCrawlApp)


IMPLEMENT_APP_NO_MAIN(ScriptCrawlApp)

ScriptCrawlApp::ScriptCrawlApp()
 : 	wxApp(),
    m_bIsExiting(false)
{
}


ScriptCrawlApp::~ScriptCrawlApp()
{
//    curMiner().reset();	// TODO: Good idea?  m_pCurrentMiner is has a reference too
}



bool ScriptCrawlApp::OnInit()
{
    namespace fs = boost::filesystem;
    using namespace crawl;
    if ( !wxApp::OnInit() )	return false;

    boost::shared_ptr<crawl::ScriptingClassIF> pScriptingClass = createPhpScriptingClass();

    boost::shared_ptr<ScriptMiner> pMiner ;
    std::string sMinerName = currentMinerName();
    std::string sBaseOutputName = sMinerName;

    std::string sFunName = "TEMPLATE_baseOutputName" ;
    if ( pScriptingClass->scriptFunctionExists(sFunName) ) sBaseOutputName = pScriptingClass->callScriptFunction_String ( sFunName, sMinerName ) ;

    sFunName = sMinerName + "_baseOutputName" ;
    if ( pScriptingClass->scriptFunctionExists(sFunName) ) sBaseOutputName = pScriptingClass->callScriptFunction_String ( sFunName ) ;
    printf( "BaseOutputName: %s\n", sBaseOutputName.c_str() );

    boost::shared_ptr<crawl::WebBrowserIF> pBrowser(new MozBrowserWx());
    std::string sUrl = pScriptingClass->callScriptFunction_String ( sMinerName + "_urlSite" );
    boost::shared_ptr<std::ofstream> pOstream( new std::ofstream( (sBaseOutputName + ".xml").c_str() ) );
    pMiner = boost::shared_ptr<ScriptMiner> ( new ScriptMiner( pBrowser, sMinerName, sBaseOutputName, crawl::Url(sUrl), pOstream ) );
    pMiner->assignScriptingClass(pScriptingClass);
    pMiner->baseOutputNameSet(sBaseOutputName);
    currentMinerSet( pMiner );


    SetTopWindow( curMiner()->mozBrowser()->guiWx() );
    curMiner()->beginMining();
    curMiner()->mozBrowser()->show();
    curMiner()->mozBrowser()->refresh();

    return true;
}

int ScriptCrawlApp::OnExit()
{
    if ( m_bIsExiting	)	return 0;
    m_bIsExiting = true;
//    curMiner().reset();	// TODO: Good idea?  m_pCurrentMiner is has a reference too
    //shutdownXulrunner();
    //wxApp::CleanUp();	// TODO: Investigate this a little more !
    return 0;
}

void runMiners( )
{
    char*  szArgv[2] = { "", "" };
    int iArgc = 1;
    wxEntry( iArgc, &szArgv[0] );
}
