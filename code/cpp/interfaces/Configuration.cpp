#include "Configuration.h"
#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <boost/lexical_cast.hpp>
#include <boost/filesystem/operations.hpp>
#include <utils/cpaf_string_utils.hpp>
#include <filesystem/cpaf_special_dirs.h>
#include <compression/cpaf_compression_functions.h>
#include <version_info.h>
#include <interfaces_utils.h>
#include <utils/StatusFile.h>


namespace crawl {

using namespace std;
using namespace boost;
namespace po = boost::program_options;

/// A helper function to simplify the main part.
template<class T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
    copy(v.begin(), v.end(), ostream_iterator<T>(cout, " "));
    return os;
}


Configuration::Configuration()
    : m_iContinueCounter    ( 0 )
    , m_sTaskId              ( "" )
{
    m_settings["decimal_point"]     = ".";
    m_settings["thousands_sep"]    = ",";
}



Configuration::~Configuration()
{
}


Configuration::Configuration    ( const Configuration& c    )
    : m_sConfigFile             ( c.m_sConfigFile           )
    , m_settings                ( c.m_settings              )
    , m_phpArgs                 ( c.m_phpArgs               )
    , m_scriptIncludeDirs       ( c.m_scriptIncludeDirs     )
    , m_vm                      ( c.m_vm                    )
    , m_eRunMode                ( c.m_eRunMode              )
    , m_maxPageLoads            ( c.m_maxPageLoads          )
    , m_iContinueCounter        ( c.m_iContinueCounter      )
    , m_sStartStateContinue     ( c.m_sStartStateContinue   )
    , m_bDoContinue             ( c.m_bDoContinue           )
    , m_sUrlStart               ( c.m_sUrlStart             )
    , m_sJobName                ( c.m_sJobName              )
    , m_sTaskId                  ( c.m_sTaskId                )
    , m_urlQueue                ( c.m_urlQueue              )
    , m_pStatusFile             ( c.m_pStatusFile           )
{
}

Configuration&  Configuration::operator= ( const Configuration& c)
{
    m_sConfigFile           = c.m_sConfigFile;
    m_settings              = c.m_settings;
    m_phpArgs               = c.m_phpArgs;
    m_scriptIncludeDirs     = c.m_scriptIncludeDirs;
    m_vm                    = c.m_vm;
    m_eRunMode              = c.m_eRunMode;
    m_maxPageLoads          = c.m_maxPageLoads;
    m_iContinueCounter      = c.m_iContinueCounter;
    m_sStartStateContinue   = c.m_sStartStateContinue;
    m_bDoContinue           = c.m_bDoContinue;
    m_sUrlStart             = c.m_sUrlStart;
    m_sJobName              = c.m_sJobName;
    m_sTaskId               = c.m_sTaskId;
    m_urlQueue              = c.m_urlQueue;
    m_pStatusFile           = c.m_pStatusFile;
    return *this;
}


void Configuration::valueSet  ( const std::string& sName, const std::string& sValue )
{
    m_settings[sName] = sValue;
}

bool Configuration::valueExists ( const std::string& sName ) const
{
    StrStrMapT::const_iterator it = m_settings.find( sName );
    return ( it != m_settings.end() || m_vm.count(sName) );
}


std::string Configuration::valueStrGet ( const std::string& sName ) const
{
    std::string sVal = "";
    const std::string sContinueLookupName = string("root.") + sName;
    std::string sContinueLookupVal = "";
    if ( doContinue() && m_pStatusFile ) sContinueLookupVal = m_pStatusFile->get( sContinueLookupName, string("") );


    StrStrMapT::const_iterator it = m_settings.find( sName );
    if ( it != m_settings.end()         ) sVal = it->second;
    else if ( sContinueLookupVal != ""  ) sVal = sContinueLookupVal;
    else if ( m_vm.count(sName) )   {
        try {
            sVal = m_vm[sName].as<string>();
        }
        catch(...) {
            sVal = "";
        }
        // Try as int
        if ( sVal == "" ) {
            try {
                sVal = std::to_string( m_vm[sName].as<int>() );
            }
            catch(...) {
                sVal = "";
            }
        }
        // Try as float
        if ( sVal == "" ) {
            try {
                sVal = std::to_string( m_vm[sName].as<float>() );
            }
            catch(...) {
                sVal = "";
            }
        }
    }
    else if ( auto default_it = m_defaultSettings.find(sName); default_it != m_defaultSettings.end() ) {
        sVal = default_it->second;
    }

    return sVal;
}

bool Configuration::valueBoolGet ( const std::string& sName ) const
{
    return stringToBool ( valueStrGet( sName ) );
}


int Configuration::valueIntGet ( const std::string& sName ) const
{
    int i = 0;
    std::string sVal = valueStrGet( sName );
    if ( sVal != "" )  i = boost::lexical_cast<int>(sVal);
    else if ( m_vm.count(sName) ) i = m_vm[sName].as<int>();
    return i;
}

float Configuration::valueNumGet ( const std::string& sName ) const
{
    float f = 0;
    std::string sVal = valueStrGet( sName );
    if ( sVal != "" )  f = boost::lexical_cast<float>(sVal);
    else if ( m_vm.count(sName) ) f = m_vm[sName].as<float>();
    return f;
}


void Configuration::phpArgAdd   ( const std::string& sArg )
{
    m_phpArgs.push_back(sArg);
}

void Configuration::phpArgsClear   ()
{
    m_phpArgs.clear();
}


void Configuration::scriptIncludeDirsAdd   ( const std::string& sDir )
{
    m_scriptIncludeDirs.push_back(sDir);
}

void Configuration::scriptIncludeDirsClear   ()
{
    m_scriptIncludeDirs.clear();
}

std::string Configuration::phpArgsStr    ()  const
{
    return cpaf::join(m_phpArgs, " ");
}

std::string Configuration::phpArgsSaveStr    ()  const
{
    return cpaf::join(m_phpArgs, ";");
}


std::string Configuration::scriptIncludeDirsStr ()  const
{
    return cpaf::join(m_scriptIncludeDirs, ";");
}

std::string Configuration::scriptIncludeDirsIniFileStr    ()  const
{
#ifdef _WINDOWS
    return cpaf::join(m_scriptIncludeDirs, ";");
#else
    return cpaf::join(m_scriptIncludeDirs, ":");
#endif
}

std::string Configuration::startStateGet ()  const
{
    std::string startState = valueStrGet("start-state");
    if ( doContinue() ) {
        startState = m_sStartStateContinue;
        //printf("Info: Continuing from state indices: '%s'. Current try number: %d\n", startState.c_str(), m_iContinueCounter );
    }
    return startState;
}

std::string Configuration::urlStartGet ()  const
{
//    std::string urlStart = valueStrGet("url");
//    if ( doContinue() )     urlStart = m_sUrlStart;
//    return urlStart;

    if ( doContinue() ) return m_sUrlStart;
    else                return valueStrGet("url");
}

std::string Configuration::jobNameGet ()  const
{
    if ( doContinue() ) return m_sJobName;
    else                return valueStrGet("job-name");
}

std::string Configuration::taskIdGet ()  const
{
    if ( doContinue() ) return m_sTaskId;
    else                return valueStrGet("task-id");
}

std::string Configuration::urlQueueContinueFile() const
{
    using namespace boost::filesystem;
    path p = outputDirGet() / ( valueStrGet("status-file") + ".urlqueue.gz" );
    return p.string();
}

const StrVecT& Configuration::urlQueue ()  const
{
    return m_urlQueue;
}

boost::filesystem::path Configuration::outputDirGet() const
{
    using namespace cpaf::filesystem;
    if (m_outputDir.empty()) {
        boost::filesystem::path p(valueStrGet("output-dir"));
        if (!directory_writeable(p) || valueStrGet("output-dir") == "DEFAULT") {
            m_outputDir = special_dirs::documents() / "Netscavator";
        }
        else if (valueStrGet("output-dir") == ".") {
            m_outputDir = special_dirs::startup_path();
        }
        else {
            m_outputDir = p;
        }
        m_outputDir = boost::filesystem::absolute(m_outputDir);
        boost::filesystem::create_directories(m_outputDir);
    }
    return m_outputDir;
}


// ------------------------
// --- Helper functions ---
// ------------------------


bool Configuration::parseCommandLine ( const std::string& sAppTypeName, int argc, char* argv[] )
{
    string defaultRunMode       = sAppTypeName == "crawler" ? "crawler" : "design" ;
    string defaultExitWhenDone  = sAppTypeName == "crawler" ? "yes" : "no" ;
    setExeNames( argv[0] );

    string sDefaultCfgPath = valueStrGet("default-cfg-path");

    if ( !boost::filesystem::exists(sDefaultCfgPath) ) {
        createDefaultConfigFiles();
        setExeNames( argv[0] );
        sDefaultCfgPath = valueStrGet("default-cfg-path");
    }


    try {

        // Declare a group of options that will be allowed only on command line
        po::options_description basic("Basic options");
        basic.add_options()
            ("version,v",   "print version string")
            ("help,h",      "produce help message")
            ("cfg-path",     po::value<string>(&m_sConfigFile)->default_value(sDefaultCfgPath), "Path to config/ini file.")
            ;

        // Declare a group of options that will be
        // allowed both on command line and in config file
        po::options_description config("Configuration");
        config.add_options()
            ("url,u", po::value<string>()->default_value(""), "Startup URL/File (URI)")
            ("url-queue", po::value<string>()->default_value(""), "File with urls to preload into the url queue. One URL per line. Can be normal text file ot compressed as .gz (must have this extension then).")
            ("xul-dir,x", po::value<string>()->default_value(""), "Xulrunner directory")
            ("browser,b", po::value<string>()->default_value("webkit"), "Browser: simple, webkit, chrome")
            ("viewmode,v", po::value<string>()->default_value("textedit"), "View mode for simple browser: textedit or textbrowser")
            ("run-mode,r", po::value<string>()->default_value(defaultRunMode), "Runmode: normal, crawler, debug, create")
            ("load-images", po::value<string>()->default_value(""), "Load images during crawling. Values: yes/no or empty which leaves the decision to the script or based on the runmode. In 'crawler' we do not load images by default.")
            ("php-ini-path,i", po::value<string>()->default_value(valueStrGet("default-php-ini-path")), "Php ini file path")
            ("script-include-dir,I",   po::value< vector<string> >()->composing(), "PHP additional include dirs")
            ("resource-dir",   po::value<string>()->default_value(valueStrGet("default-resource-dir")), "Resource path")
            ("exit-when-done", po::value<string>()->default_value(defaultExitWhenDone), "Exit program on mining done. Values: 'yes'','no'")
            ("upload-result", po::value<string>()->default_value(""), "Upload to server Values: yes/no or empty which leaves the decision to the script or based on the runmode. In 'crawler' we upload by default.")
            ("upload-handler", po::value<string>()->default_value(""), "Function to call to do the actual upload of XML data to a server. Possible values: '', 'uploadFileHttpPost', 'uploadFileScp'. If this is empty (default) then the script (template) should have set the handler and using settingSet('upload-handler'). Also the script/template is responsible for the parameters needed (settingSet()) for each of the two methods. See the utils.php file in the installed crawler: webminer/bin/data/php/miner_utils/utils.php See doc for the tw functions: 'uploadFileHttpPost', 'uploadFileScp'.")
            ("upload-url", po::value<string>()->default_value(""), "Optional URL that the upload-handler function can read using configStrGet('upload-url') and use.")
            ("delete-after-upload", po::value<string>()->default_value("no"), "Delete XML output file after upload.")
            ("no-net-activity-handling", po::value<string>()->default_value(""), "Action/handler to take/call in case of no network activity. Values:'none', 'reload': Reloads current page,'': Empty (default) calls 'MinerName_NoNetActivityHandler()', or 'TEMPLATE_NoNetActivityHandler()') or does reload if none of the two functions is preset.")
            ("no-net-activity-timeout", po::value<int>()->default_value(60), "Timeout in secs before the no-net-activity-handling is taken. Reload or call custom handler script function.")
            ("show-network-activity", po::value<string>()->default_value("no"), "Debug print network activity to stdout.")
            ("show-output", po::value<string>()->default_value(""), "Should output data be shown in window. When in crawler mode we usually don't want to waste time doing this. But for the creator we mostly want it.")
            ("status-file", po::value<string>()->default_value("Crawler.status"), "File to which current mining status is written. Default is just 'Crawler.status' in current directory. Used by the automated mining tools.")
            ("job-name", po::value<string>()->default_value("SCRIPT-STEMNAME"), "Job Name. Can be used when script is run on robot machine and is renamed to the generic 'Crawler.php'. This name is written to the Crawler.status file. The default value is the php script stemname. Like 'my-php-script' but witout the '.php' extension.")
            ("task-id", po::value<string>()->default_value(""), "Job ID. Can be used when script is run on robot machine. The central job issuing server might want to give each job a unique ID. This ID is written to the Crawler.status file")
            ("output-name", po::value<string>()->default_value(""), "Force overriding TEMPLATE_baseOutputName() or MinerName__baseOutputName(). Mainly used for by automated mining tools for forcing output file to always be named Crawler.xml(.gz) by using --output-name=Crawler")
            ("output-dir", po::value<string>()->default_value("."), "Output directory. Set to 'DEFAULT' to use 'MyDocuments/netscavator' folder ")
            ("dump-linear-dom", po::value<string>()->default_value(""), "Dump linear DOM version of each page")
            ("dump-html-dom", po::value<string>()->default_value(""), "Dump HTML DOM version of each page")
            ("max-pageloads", po::value<int>()->default_value(0), "Maximum number of pages to load before exit. Default 0 means no limit. Mainly used for testing of automated mining tools.")
            ("win-width", po::value<int>()->default_value(1024), "Window default width")
            ("win-height", po::value<int>()->default_value(800), "Window default height")
        ;

        config.add_options()
            ("continue,c", "Continue crawling job. Can be used in case the crawler has stopped or crashed in the middle of a job.")
            ("max-tries,m",po::value<int>()->default_value(30), "Max tries when trying to continue.")
            ("start-state", po::value<string>()->default_value(""), "Start mining (navigator) in state. Can be either states names or state indices. The state/index for each option/'wheel' are comma separated.")
            ("end-state", po::value<string>()->default_value(""), "End mining when (navigator has) reached state. Can be either states names or state indices. The state/index for each option/'wheel' are comma separated.")
        ;

        // Hidden options, will be allowed both on command line and
        // in config file, but will not be shown to the user.
        // Hidden options are those without argument names (unanmed arguments).
        // In this case we use them for the php script to execute along
        // with the command line parameters for this script.
        po::options_description hidden("Hidden options");
        hidden.add_options()
            ("script-params", po::value< vector<string> >(), "PHP script and parameters")
            ;


        po::options_description cmdline_options;
        cmdline_options.add(basic).add(config).add(hidden);

        po::options_description config_file_options;
        config_file_options.add(config).add(hidden);

        po::options_description visible("Allowed options");
        visible.add(basic).add(config);

        po::positional_options_description p;
        p.add("script-params", -1);

        po::store(po::command_line_parser(argc, argv).options(cmdline_options).positional(p).run(), m_vm);
        po::notify(m_vm);

        ifstream ifs(m_sConfigFile.c_str());
        if (!ifs)
        {
            cout << "Warning: Can not open config file: " << m_sConfigFile << "\n";
            return false;
        }
        else
        {
            store(parse_config_file(ifs, config_file_options), m_vm);
            notify(m_vm);
        }

        if (m_vm.count("help")) {
            cout << visible << "\n";
            return false;
        }

        if (m_vm.count("version")) {
            string sAppName  = sAppTypeName == "crawler" ? "Sleipner crawler" : "Sleipner miner creator" ;
            cout << sAppName << ", version " << versionString() << " , Using embedded PHP version " << crawler_php_version_string() <<  "\n";
            return false;
        }

        // PHP miner script and parameters for this
        if (m_vm.count("script-params")) {
            setScriptParams( m_vm["script-params"].as< vector<string> >() );
        }


        if (m_vm.count("script-include-dir")) {
            setScriptIncludes( m_vm["script-include-dir"].as< vector<string> >() );
        }

        if (m_vm.count("url-queue")) {
            readUrlQueueFile( m_vm["url-queue"].as<string >() );
        }

    }
    catch(std::exception& e)
    {
        cout << "Error: Unknown arguments given:" << endl;
        cout << e.what() << "\n";
        return false;
    }
    readContinueVars();
    fillStandardValues();
    return true;
}

void Configuration::getScriptArgvArgc ( int& argcOut, char* argvOut[] )
{
    if ( valueStrGet("script-path") != "" ) {
        strcpy( argvOut[0], valueStrGet("script-path").c_str() );
    }
    else strcpy( argvOut[0], "DEFAULT_SCRIPT.php");

    for ( size_t i = 0; i < m_phpArgs.size(); ++i ){
        strcpy(argvOut[i+1], m_phpArgs[i].c_str() );
    }
    argcOut = static_cast<int>(m_phpArgs.size()) + 1;
}


void  Configuration::runModeSet ( const std::string& sRunMode )
{
    valueSet("run-mode", sRunMode );
    m_eRunMode = toRunMode(valueStrGet("run-mode"));
}


void Configuration::readContinueVars()
{
    m_sStartStateContinue   = "";
    m_iContinueCounter      = 0;
    m_bDoContinue           = false;

    if (m_vm.count("continue")) {
        m_pStatusFile = boost::shared_ptr<StatusFile> ( new StatusFile( outputDirGet(), valueStrGet("status-file"), nullptr ) );
        if ( m_pStatusFile->readFile () ) {
            const int continueCounter = m_pStatusFile->get("root.continue_counter", 0 );
            const int miningDone = m_pStatusFile->get("root.mining_done", 1);
            const int maxTries = valueIntGet("max-tries");
            if (maxTries <= continueCounter) {
                printf("Error: Exeeded max number of continue retries! Starting new mining!\nCurrent try number/max: %d/%d\n", continueCounter, maxTries);
                return;
            }
            if (miningDone == 1) {
                printf("Info: Not continuing since last mining completed sucessfully. Starting new mining!\nPrevious run continue count: %d.\n", continueCounter);
                return;
            }
            printf("Info: miningDone: '%d'\n", miningDone );

            m_iContinueCounter = continueCounter +1;
            m_sStartStateContinue = m_pStatusFile->get("root.nav_current_state_indices", std::string("") );
            m_sUrlStart = m_pStatusFile->get("root.latest_loaded_url", std::string("") );
            m_sJobName = m_pStatusFile->get("root.job_name", std::string("") );
            m_sTaskId = m_pStatusFile->get("root.task_id", std::string("") );

            // Read script-path, script-params and script include dirs from status file
            string sScriptCmdLine = m_pStatusFile->get("root.script_path"   , string("") );
            sScriptCmdLine += ";" + m_pStatusFile->get("root.script_params" , string("") );
            string sScriptIncludes = m_pStatusFile->get("root.script_include_dirs" , string("") );
            setScriptParams     ( cpaf::splitv(sScriptCmdLine , ";" ) );
            setScriptIncludes   ( cpaf::splitv(sScriptIncludes, ";" ) );

            readUrlQueueFile( urlQueueContinueFile() );

            m_bDoContinue = true;
            printf("Info: Continuing from state indices: '%s'. Current try number/max: %d/%d\n", m_sStartStateContinue.c_str(), m_iContinueCounter, maxTries );
        }
        else {
            printf("Info: Not continuing since no previous mining files found. Starting new mining!\n");
        }
    }
}

void Configuration::printSettings() const
{
    printf("Netscavator version        : %s\n", versionString().c_str() );
    printf("Config url                 : %s\n", urlStartGet().c_str() );
    printf("Config exe-path            : %s\n", valueStrGet("exe-path").c_str() );
    printf("Config exe-dir             : %s\n", valueStrGet("exe-dir").c_str() );
    printf("Config exe-name            : %s\n", valueStrGet("exe-name").c_str() );
    printf("Config exe-stemname        : %s\n", valueStrGet("exe-stemname").c_str() );
    printf("Config cfg-path            : %s\n", valueStrGet("cfg-path").c_str() );
    printf("Config resource-dir        : %s\n", valueStrGet("resource-dir").c_str() );
    printf("Config default-resource-dir: %s\n", valueStrGet("default-resource-dir").c_str() );
    printf("Config browser             : %s\n", valueStrGet("browser").c_str() );
    printf("Config viewmode (simple)   : %s\n", valueStrGet("viewmode").c_str() );
    printf("Config run-mode            : %s\n", valueStrGet("run-mode").c_str() );
    printf("Config upload-result       : %s\n", valueStrGet("upload-result").c_str() );
    printf("Config load-images         : %s\n", valueStrGet("load-images").c_str() );
    printf("Config script-path         : %s\n", valueStrGet("script-path").c_str() );
    printf("Config script-name         : %s\n", valueStrGet("script-name").c_str() );
    printf("Config script-dir          : %s\n", valueStrGet("script-dir").c_str() );
    printf("Config php-ini-path        : %s\n", valueStrGet("php-ini-path").c_str() );
    printf("Config Script arguments    : %s\n", phpArgsStr().c_str() );
    printf("Config Script include dirs : %s\n", scriptIncludeDirsIniFileStr().c_str() );
    printf("Config exit-when-done      : %s\n", valueStrGet("exit-when-done").c_str() );
    printf("Config show-output         : %s\n", valueStrGet("show-output").c_str() );
    printf("Config status-file         : %s\n", valueStrGet("status-file").c_str() );
    printf("Config task-id             : %s\n", valueStrGet("task-id").c_str() );
    printf("Config output-name         : %s\n", valueStrGet("output-name").c_str() );
    printf("Config output-dir          : %s\n", outputDirGet().c_str() );
    printf("Config dump-linear-dom     : %s\n", valueStrGet("dump-linear-dom").c_str() );
    printf("Config dump-html-dom       : %s\n", valueStrGet("dump-html-dom").c_str() );
    printf("Config max-pageloads       : %s\n", valueStrGet("max-pageloads").c_str() );
    printf("Config continue requested  : %d\n", m_vm.count("continue") ? 1 : 0 );
    printf("Config max-tries (continue): %d\n", valueIntGet("max-tries") );
    printf("Current continue counter   : %d\n", continueCounterGet() );

    printf("Config no-net-activity-timeout : %d\n", valueIntGet("no-net-activity-timeout") );
    printf("Config no-net-activity-handling: %s\n", valueStrGet("no-net-activity-handling").c_str() );
}


// ------------------------------------
// --- Get executable path function ---
// TODO: Move to cpaf/cpaf_libs/filesystem/cpaf_special_dirs.h
// ------------------------------------
/**
  Returns the full path to the executable. Also works if exe file is run using PATH
  (i.e. not with actual path to executable ).
  \see http://stackoverflow.com/questions/933850/how-to-find-the-location-of-the-executable-in-c
  */
// static boost::filesystem::path exe_path()
// {
// #if defined ( WINDOWS ) || defined ( _WIN32 )
    // char szExePath[PATH_MAX] = {0};
    // GetModuleFileName(NULL, szExePath, sizeof(szExePath));
    // boost::filesystem::path exePath = boost::filesystem::canonical( szExePath );
    // return exePath;
// #endif
// #if defined ( DARWIN )
// #endif
// #if defined ( LINUX )
    // char szExePath[PATH_MAX] = {0};
    // ssize_t iIgnore = readlink("/proc/self/exe", szExePath, sizeof(szExePath));
    // boost::filesystem::path exePath = boost::filesystem::canonical( szExePath );
    // return exePath;
// #endif
// }


// --------------------------
// --- PRIVATE: Functions ---
// --------------------------
void Configuration::setScriptParams     ( const std::vector< std::string >& scriptParams )
{
    boost::filesystem::path p( boost::filesystem::canonical(scriptParams[0]) );
    valueSet("script-path", p.string() );
    valueSet("script-dir", p.parent_path().string() );
    valueSet("script-name", p.filename().string() );
    valueSet("script-stemname", p.stem().string() );

    for ( size_t i = 1; i < scriptParams.size(); ++i ) {
        phpArgAdd(scriptParams[i]);
    }

    //	cout << "PHP script params are: " << scriptParams << "\n";
}

void Configuration::setScriptIncludes   ( const std::vector< std::string >& scriptParams )
{
    for ( size_t i = 0; i < scriptParams.size(); ++i ) {
        scriptIncludeDirsAdd(scriptParams[i]);
    }
    // cout << "Include paths are: " << scriptParams << "\n";
}

void Configuration::valueSetIfEmpty     (
        const std::string& sName
        , const std::string& sValue )
{
    if ( "" == valueStrGet(sName) ) {
        valueSet(sName, sValue );
    }
}

//#if defined ( WINDOWS ) || defined ( _WIN32 )
//#else
//#endif


std::string Configuration::defaultConfigPathGet( const boost::filesystem::path& exedir ) const
{
    string leafName = valueStrGet("exe-stemname") + ".cfg";
    boost::filesystem::path p;
    p = boost::filesystem::path("/etc/") / "netscavator" / leafName;
    if ( boost::filesystem::exists(p) ) {
        return p.string();
    }
    p = cpaf::filesystem::special_dirs::app_data_local() / string(".netscavator") / leafName;
    if ( boost::filesystem::exists(p) ) {
        return p.string();
    }
    p = exedir / leafName;
    return p.string();
}


std::string Configuration::defaultPhpIniPathGet( const boost::filesystem::path& exedir ) const
{
    string leafName =  "php.ini";
    boost::filesystem::path p;
    p = boost::filesystem::path("/etc/netscavator") / leafName;
    if ( boost::filesystem::exists(p) ) {
        return p.string();
    }
    p = cpaf::filesystem::special_dirs::app_data_local() / string(".netscavator") / leafName;
    if ( boost::filesystem::exists(p) ) {
        return p.string();
    }
    p = exedir / leafName;
    return p.string();
}


std::string Configuration::defaultResourceDirGet( const boost::filesystem::path& exedir ) const
{
    string leafName = "data";
    boost::filesystem::path p;
    p = boost::filesystem::path("/usr/share/netscavator/data");
    if ( boost::filesystem::exists(p) ) {
        return p.string();
    }
    p = exedir / "data";
    if ( boost::filesystem::exists(p) ) {
        return p.string();
    }
    p = standardDataPathGet(exedir);

    return p.string();
}

boost::filesystem::path Configuration::defaultConfigInPathGet( const boost::filesystem::path& exedir ) const
{
    boost::filesystem::path p;
    string leafName = valueStrGet("exe-stemname") + ".cfg.in";
    p = standardDataPathGet(exedir) / "config" / leafName ;
    return p;
}

boost::filesystem::path Configuration::defaultPhpIniInPathGet( const boost::filesystem::path& exedir ) const
{
    boost::filesystem::path p;
    string leafName = "php.ini.in";
    p = standardDataPathGet(exedir) / "config" / leafName ;
    return p;
}

boost::filesystem::path Configuration::standardDataPathGet( const boost::filesystem::path& exedir ) const
{
    boost::filesystem::path p;
    p = exedir.parent_path() / "share" / "netscavator" ;
    return p;
}


boost::filesystem::path Configuration::standardExtensionPathGet( const boost::filesystem::path& /*exedir*/ ) const
{
    boost::filesystem::path p;
#if defined ( WINDOWS ) || defined ( _WIN32 )
    p = exedir ;
#endif
#if defined ( LINUX )
    p = exedir ;
#endif
    return p;
}

std::string	Configuration::phpIniPathSeparator		() const
{
#if defined ( WINDOWS ) || defined ( _WIN32 )
    return ";";
#endif
#if defined ( LINUX )
    return ":";
#endif
    return ":";
}

void Configuration::setExeNames ( const char* /*argv0*/ )
{
    using namespace cpaf::filesystem;
    boost::filesystem::path exepath = special_dirs::exe_path();
    boost::filesystem::path exedir = exepath.parent_path();
//    filesystem::path exepath = exe_path();
    valueSet("exe-path", exepath.string() );
    valueSet("exe-dir", exedir.string() );
    valueSet("exe-name", exepath.filename().string() );
    valueSet("exe-stemname", exepath.stem().string() );
    valueSet("config-stemname", "netscavator" );
    valueSet("default-cfg-path", defaultConfigPathGet(exedir) );
    valueSet("default-php-ini-path", defaultPhpIniPathGet(exedir) );
    const string defaultResourceDir = defaultResourceDirGet(exedir);
    valueSet("default-resource-dir", defaultResourceDir );
}

void Configuration::fillStandardValues()
{
    boost::filesystem::path exepath ( valueStrGet("exe-path") );

    // Xul Runner directory
    valueSetIfEmpty( "xul-dir", valueStrGet("exe-dir") );
    runModeSet( valueStrGet("run-mode") );
    m_maxPageLoads = static_cast<uint64_t>(valueIntGet("max-pageloads"));
    const string defaultShowOutput    = runMode() == crawl::rmCrawlerE ? "no" : "yes" ;
    valueSetIfEmpty ( "show-output", defaultShowOutput );

    // Use script name as default job-name
    if (valueStrGet("job-name") == "SCRIPT-STEMNAME") {
        valueSet("job-name", valueStrGet("script-stemname"));
    }

//    filesystem::path scriptpath ( valueStrGet("exe-path") );
}

void Configuration::readUrlQueueFile    ( const std::string& sFileName )
{
    boost::filesystem::path file ( sFileName );
    if ( boost::filesystem::exists( file ) ) {
        cpaf::compression::readlines( m_urlQueue, file );
    }
}


void Configuration::createDefaultConfigFiles ()
{
    using namespace cpaf::filesystem;
    boost::filesystem::path exedir = special_dirs::exe_path().parent_path();
    boost::filesystem::path configInPath = defaultConfigInPathGet(exedir);
    boost::filesystem::path phpIniInPath = defaultPhpIniInPathGet(exedir);

    if ( !boost::filesystem::exists( configInPath ) ) {
        std::cerr << "Error default config.in file not found: '" << configInPath << "'. Please re-install.\n";
        exit(1);
    }
    if ( !boost::filesystem::exists( phpIniInPath ) ) {
        std::cerr << "Error default php.ini.in file not found: '" << configInPath << "'. Please re-install.\n";
        exit(1);
    }
    boost::filesystem::path configDirPath = special_dirs::app_data_local() / string(".netscavator");
    boost::filesystem::path configPath = configDirPath / (valueStrGet("exe-stemname") + ".cfg");
    boost::filesystem::path phpIniPath = configDirPath / "php.ini";

    boost::filesystem::create_directories(configDirPath);

    string sFile = read_file(configInPath);
    algorithm::replace_all(sFile, "@PHP_INI_PATH@", phpIniPath.string() );
    write_file(configPath, sFile);


    if ( boost::filesystem::exists(phpIniPath) ) return;

    boost::filesystem::path incPath1 = standardDataPathGet(exedir) / "php" / "miner_utils";
    boost::filesystem::path incPath2 = standardDataPathGet(exedir) / "php" / "miner_templates";

    string sIncPath = incPath1.string() + phpIniPathSeparator() + incPath2.string();

    sFile = read_file(phpIniInPath);
    algorithm::replace_all(sFile, "@WEBMINER_PHP_INCLUDE_PATH@", sIncPath );
    algorithm::replace_all(sFile, "@WEBMINER_PHP_EXTENSION_DIR@", standardExtensionPathGet(exedir).string() );
    algorithm::replace_all(sFile, "@WEBMINER_PHP_EXTENSIONS@", "" );
    write_file(phpIniPath, sFile);
}


} //END namespace crawl;


// -------------------------------------------------
// --- C program argument style helper functions ---
// -------------------------------------------------

char** allocateArrayOfStrings( int arraySize, int stringSize )
{
    const size_t arraySizeU = static_cast<size_t>(arraySize);
    const size_t stringSizeU = static_cast<size_t>(stringSize);
    char** stringArray = reinterpret_cast<char**>(malloc(arraySizeU * sizeof( char* )));
    for( size_t i = 0; i < arraySizeU; i++)
    {
        stringArray[i] = reinterpret_cast<char*>(malloc(stringSizeU * sizeof(char)));
    }
    return stringArray;
}

void freeArrayOfStrings( char** stringArray, int arraySize )
{
    for( int i = 0; i < arraySize; i++) free(stringArray[i]);
    free(stringArray);
}

