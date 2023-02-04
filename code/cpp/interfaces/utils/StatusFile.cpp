#include "StatusFile.h"
#include <fstream>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/convenience.hpp>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <cpaf_session.h>
#include <cpaf_libs/utils/cpaf_string_utils.hpp>
#include <ScriptMinerIF.h>
#include <ScriptingClassIF.h>
#include <Configuration.h>
#include <version_info.h>

using namespace boost;
using namespace boost::date_time;


namespace crawl {
// --------------------------------------------
// --- PUBLIC: Constructors, init functions ---
// --------------------------------------------

StatusFile::StatusFile(
          const boost::filesystem::path& outputDir
        , const std::string& fileName
        , ScriptMinerIF* pMiner
        )
    :   m_fileName  ( (outputDir / fileName).string()  )
    ,   m_pMiner    ( pMiner    )
    ,   m_scriptStatus("")
{
}

StatusFile::~StatusFile ()
{

}


// ------------------------------
// --- PUBLIC: File functions ---
// ------------------------------
void StatusFile::writeFile ()
{
    using boost::property_tree::ptree;

    if ( m_fileName == "" || m_fileName == "no" )   return;
    if ( !m_pMiner )  return;
    ptree pt;
    pt.put("root.process_id", cpaf::system::getProcessID() );
    pt.put("root.script_name", m_pMiner->minerName() );
    pt.put("root.mining_done", m_pMiner->infoMiningDoneStatus() );
    pt.put("root.nav_current_state_indices", m_pMiner->navCurrentStateIndicesGet());
    pt.put("root.nav_current_state_string", m_pMiner->navStateString() );
    pt.put("root.nav_current_state_index", m_pMiner->navStateIndexGet() );
    pt.put("root.nav_num_states", m_pMiner->navNumStatesGet() );
    pt.put("root.nav_last_state_index", m_pMiner->navLastStateIndexGet() );

    pt.put("root.total_pages_loaded", m_pMiner->infoPageLoadsTotal() );

    pt.put("root.mining_started_time_iso", posix_time::to_iso_string(m_pMiner->infoTimeMiningStarted()) );
    pt.put("root.mining_started_time_ext_iso", posix_time::to_iso_extended_string(m_pMiner->infoTimeMiningStarted()) );

    pt.put("root.current_url", m_pMiner->urlCurrent() );
    pt.put("root.latest_loaded_url", m_pMiner->infoLatestFullyLoadedUrl() );
    pt.put("root.latest_loaded_time_iso", posix_time::to_iso_string(m_pMiner->infoTimeLastPageLoadFinished()) );
    pt.put("root.latest_loaded_time_ext_iso", posix_time::to_iso_extended_string(m_pMiner->infoTimeLastPageLoadFinished()) );

    // From config
    pt.put("root.continue_counter"          , m_pMiner->config()->continueCounterGet()                      );
    pt.put("root.job_name"                  , m_pMiner->config()->jobNameGet()                              );
    pt.put("root.task_id"                   , m_pMiner->config()->taskIdGet()                               );
    pt.put("root.script_path"               , m_pMiner->config()->valueStrGet("script-path")                );
    pt.put("root.script_params"             , m_pMiner->config()->phpArgsSaveStr()                          );
    pt.put("root.script_include_dirs"       , m_pMiner->config()->scriptIncludeDirsStr()                    );

    pt.put("root.cfg-path"                  , m_pMiner->config()->valueStrGet("cfg-path")                   );
    pt.put("root.run-mode"                  , m_pMiner->config()->valueStrGet("run-mode")                   );
    pt.put("root.load-images"               , m_pMiner->config()->valueStrGet("load-images")                );
    pt.put("root.php-ini-path"              , m_pMiner->config()->valueStrGet("php-ini-path")               );
    pt.put("root.resource-dir"              , m_pMiner->config()->valueStrGet("resource-dir")               );
    pt.put("root.exit-when-done"            , m_pMiner->config()->valueStrGet("exit-when-done")             );
    pt.put("root.upload-result"             , m_pMiner->config()->valueStrGet("upload-result")              );
    pt.put("root.upload-handler"            , m_pMiner->config()->valueStrGet("upload-handler")             );
    pt.put("root.no-net-activity-handling"  , m_pMiner->config()->valueStrGet("no-net-activity-handling")   );
    pt.put("root.no-net-activity-timeout"   , m_pMiner->config()->valueStrGet("no-net-activity-timeout")    );
    pt.put("root.show-output"               , m_pMiner->config()->valueStrGet("show-output")                );
    pt.put("root.output-name"               , m_pMiner->config()->valueStrGet("output-name")           );
    pt.put("root.max-pageloads"             , m_pMiner->config()->valueStrGet("max-pageloads")              );
    pt.put("root.win-width"                 , m_pMiner->config()->valueStrGet("win-width")                  );
    pt.put("root.win-height"                , m_pMiner->config()->valueStrGet("win-height")                 );
    pt.put("root.end-state"                 , m_pMiner->config()->valueStrGet("end-state")                  );
    pt.put("root.url-queue-size"            , m_pMiner->urlQueueSize ()                                     );
    pt.put("root.crawler-version"           , versionString()                                               );

    std::vector<std::string> keyValPairVec;
    std::vector<std::string> scriptStatusVec;
    cpaf::splitv_trim( scriptStatusVec, m_scriptStatus, ";" );
    for( const std::string& keyVal : scriptStatusVec ) {
        cpaf::splitv_trim( keyValPairVec, keyVal, "=" );
        if ( 2 == keyValPairVec.size() ) {
            pt.put( "root." + keyValPairVec[0], keyValPairVec[1] );
        }
    }
    std::string items_mined = m_pMiner->settingGet("items_mined", "");
    pt.put("root.items_mined", items_mined);

    // Write the property tree to the file.
//    boost::property_tree::xml_writer_settings<char> w('\t', 1);
//    write_xml(m_fileName, pt, std::locale(), w );
    auto settings = boost::property_tree::xml_writer_settings<std::string> ('\t', 1);
    boost::property_tree::write_xml(m_fileName, pt, std::locale(), settings );
}


bool StatusFile::readFile ()
{
    if ( !boost::filesystem::exists(m_fileName) ) return false;
    // Create an empty property tree object

    bool ok = true;
    try {
        read_xml(m_fileName, m_ptree );
    }
    catch ( const property_tree::ptree_error& ) {
        ok = false;
    }

    if ( !ok ) {
        try {
            read_json(m_fileName, m_ptree );
        }
        catch ( const property_tree::ptree_error& ) {
            ok = false;
        }
    }
    return ok;
}

// --------------------------------
// --- PUBLIC: Access functions ---
// --------------------------------


boost::posix_time::ptime StatusFile::get (const std::string& path, const boost::posix_time::ptime& defaultValue ) const
{
    std::string sTime = m_ptree.get<std::string>( path, "" );
    boost::posix_time::ptime t;
    bool getOk = false;
    try {
        t = boost::posix_time::from_iso_string( sTime );
        getOk = true;
    }
    catch (const std::exception& e)
    {
        std::cout << "Exception 1 in StatusFile::get: " << e.what() << std::endl;
    }
    if ( !getOk ) {
        try {
            t = boost::posix_time::time_from_string( sTime );
            getOk = true;
        }
        catch (const std::exception& e)
        {
            std::cout << "Exception 2 in StatusFile::get: " << e.what() << std::endl;
        }

    }

    if ( !getOk ) t = defaultValue;
    return t;
}

std::string StatusFile::scriptStatus() const
{
    return m_scriptStatus;
}

void StatusFile::scriptStatusSet(const std::string& scriptStatus)
{
    m_scriptStatus = scriptStatus;
}

} // END namespace crawl
