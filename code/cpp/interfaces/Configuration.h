#ifndef _CRAWL_CONFIGURATION_H_
#define _CRAWL_CONFIGURATION_H_

#include <string>
#include <map>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <interfaces_types.h>



namespace crawl { 

class StatusFile;

class Configuration
{
public:
	// ----------------
	// --- Typedefs ---
	// ----------------
    typedef std::vector<std::string>      StrVecT;

    Configuration();
    ~Configuration();

    Configuration                           ( const Configuration& c);
    Configuration&  operator=               ( const Configuration& c);

    void            valueSet                ( const std::string& sName, const std::string& sValue );

    bool            valueExists             ( const std::string& sName ) const;
    std::string     valueStrGet             ( const std::string& sName ) const;
    bool            valueBoolGet            ( const std::string& sName ) const;
    int             valueIntGet             ( const std::string& sName ) const;
    float           valueNumGet             ( const std::string& sName ) const;

    void            phpArgAdd               ( const std::string& sArg );
    void            phpArgsClear            ();
    void            scriptIncludeDirsAdd    ( const std::string& sArg );
    void            scriptIncludeDirsClear  ();
    const StrVecT&  phpArgs                 () const { return m_phpArgs; }
    const StrVecT&  scriptIncludeDirs       () const { return m_scriptIncludeDirs; }

    std::string     phpArgsStr              () const;
    std::string     phpArgsSaveStr          () const;
    std::string     scriptIncludeDirsStr    () const;
    std::string     scriptIncludeDirsIniFileStr    ()  const;
    std::string     startStateGet           () const;
    std::string     urlStartGet             () const;
    std::string     jobNameGet              () const;
    std::string     taskIdGet                () const;
    std::string     urlQueueContinueFile    () const;
    const StrVecT&  urlQueue                () const;

    int             continueCounterGet      () const { return m_iContinueCounter;  }
    bool            doContinue              () const { return m_bDoContinue;       }
    RunModeE        runMode                 () const { return m_eRunMode;          }
    bool            runModeCreator          () const { return crawl::runModeCreator(runMode()); }

    boost::uint64_t maxPageLoads            () const { return m_maxPageLoads;      }

    boost::filesystem::path     outputDirGet() const;


	// ------------------------
	// --- Helper functions ---
	// ------------------------
    bool            parseCommandLine        ( const std::string& sAppTypeName, int argc, char* argv[] );
    void            getScriptArgvArgc       ( int& argcOut, char* argvOut[] );
    void            runModeSet              ( const std::string& sRunMode );
    void            readContinueVars        ();
    void            printSettings           () const;
	
	// ---------------------------------------
	// --- Simple set/get inline functions ---
	// ---------------------------------------
	
private:
    typedef std::map<std::string, std::string>      StrStrMapT;

    // --------------------------
    // --- PRIVATE: Functions ---
    // --------------------------
    void					setScriptParams			( const std::vector< std::string >& scriptParams );
    void					setScriptIncludes		( const std::vector< std::string >& scriptParams );
    void					valueSetIfEmpty			( const std::string& sName, const std::string& sValue );
    std::string				defaultConfigPathGet	( const boost::filesystem::path& exedir ) const;
    std::string				defaultPhpIniPathGet	( const boost::filesystem::path& exedir ) const;
    std::string				defaultResourcePathGet	( const boost::filesystem::path& exedir ) const;
    boost::filesystem::path defaultConfigInPathGet	( const boost::filesystem::path& exedir ) const;
    boost::filesystem::path defaultPhpIniInPathGet	( const boost::filesystem::path& exedir ) const;
	boost::filesystem::path standardDataPathGet		( const boost::filesystem::path& exedir ) const;
	boost::filesystem::path standardExtensionPathGet( const boost::filesystem::path& exedir ) const;
	std::string				phpIniPathSeparator		() const;
    void					setExeNames				( const char* argv0 );
    void					fillStandardValues		();
    void					readUrlQueueFile		( const std::string& sFileName );

	void					createDefaultConfigFiles();

	// -------------------
	// --- Member Data ---
	// -------------------
    std::string             m_sConfigFile;
    StrStrMapT              m_settings;
    StrVecT                 m_phpArgs;
    StrVecT                 m_scriptIncludeDirs;
    boost::program_options::variables_map   m_vm;
    RunModeE                m_eRunMode;
    boost::uint64_t         m_maxPageLoads;
    int                     m_iContinueCounter;
    std::string             m_sStartStateContinue;
    bool                    m_bDoContinue;
    std::string             m_sUrlStart;
    std::string             m_sJobName;
    std::string             m_sTaskId;
    StrVecT                 m_urlQueue;
    boost::shared_ptr<StatusFile>   m_pStatusFile;
    mutable boost::filesystem::path m_outputDir;
    const StrStrMapT m_defaultSettings =
    {
        {"page_source_file_name"        , "_page_source.html"},
        {"download_page_source_only"    , "false"},
        {"save_page_source"             , "false"},
        {"replace_std_html_entities"    , "true"}
    };

};




} // END namespace crawl

// -------------------------------------------------
// --- C program argument style helper functions ---
// -------------------------------------------------
char**  allocateArrayOfStrings  ( int arraySize, int stringSize );
void    freeArrayOfStrings      ( char** stringArray, int arraySize );


#endif // _CRAWL_CONFIGURATION_H_



