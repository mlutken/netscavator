#include <iostream>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <cpaf_file_directory_functions.h>
#include <cpaf_string_utils.hpp>
#include <utils/StringFinder.h>


using namespace std;
using namespace cpaf::filesystem;
using namespace crawl;
namespace po = boost::program_options;
namespace fs = boost::filesystem;
namespace ba = boost::algorithm;

boost::program_options::variables_map   g_vm;

filepaths_t g_allScripts;

// /home/ml1/code/crawler/doc/examples/code
// /home/ml/code/miners/scripts/airplay
bool parseCommandLine ( int argc, char* argv[] )
{

    try {

        // Declare a group of options that will be allowed only on command line
        po::options_description basic("Basic options");
        basic.add_options()
            ("version,v",   "print version string")
            ("help,h",      "produce help message")
            ("dir,d",       po::value<string>()->default_value(""), "Scripts directory")  // /home/ml/code/miners/scripts/airplay
            ;


        po::options_description cmdline_options;
        cmdline_options.add(basic);


        po::store(po::command_line_parser(argc, argv).options(cmdline_options).run(), g_vm);
        po::notify(g_vm);


        if (g_vm.count("help")) {
            cout << cmdline_options << "\n";
            return false;
        }

        cout << "Script directory: " << g_vm["dir"].as<string>() << endl;
        if (!boost::filesystem::exists(g_vm["dir"].as<string>())) {
            cout << "Directory not found. Exit!" << endl;

        }

        g_allScripts = files_list_recursive(g_vm["dir"].as<string>(), true, "*.php", -1);


    }
    catch(std::exception& e)
    {
        cout << "Error: Unknown arguments given:" << endl;
        cout << e.what() << "\n";
        return false;
    }
    return true;
}

bool isCrawlerScript( fs::path p )
{
    string s = read_file(p);
    bool isCrawlerScript = false;
    string leafName = p.leaf().string();

    if ( boost::algorithm::contains(leafName, ".tpl.wizzard.php")) return false;

    if ( boost::algorithm::contains(s, "\"webminer.php\"")) isCrawlerScript = true;
    if ( boost::algorithm::contains(s, "\"Airplay1.tpl.php\"")) isCrawlerScript = true;
    if ( boost::algorithm::contains(s, "Script_minerName")) isCrawlerScript = true;
    if ( boost::algorithm::contains(s, "TEMPLATE__")) isCrawlerScript = true;
    if ( boost::algorithm::contains(s, "Crawler__")) isCrawlerScript = true;
    if ( boost::algorithm::contains(s, "_DoSearch_match")) isCrawlerScript = true;
    if ( boost::algorithm::ends_with(leafName, ".tpl.php")) isCrawlerScript = true;
    if ( leafName == "AirplayTemplateUtils.php" ) isCrawlerScript = true;

    return isCrawlerScript;
}


filepaths_t filterPaths( const filepaths_t& scripts)
{
    filepaths_t allScripts;
    for ( const fs::path& p : scripts) {
        if (isCrawlerScript(p)) {
            allScripts.push_back( p.string() );
        }
    }
    return allScripts;
}

string getScriptName(const std::string& fileContents)
{
    if (!boost::algorithm::contains(fileContents, "Script_minerName")) return "";
    StringFinder sf(fileContents);
    sf.findBeginNext("Script_minerName");
    sf.findBeginNext("\"");
    sf.findEndNext("\"");
    return sf.currentValue();
}


string minerNameRemove(const std::string& fileContents, const std::string& scriptName)
{
    if (scriptName == "") return fileContents;
    if (boost::algorithm::contains(fileContents, "Crawler__")) return fileContents;
    string s = boost::algorithm::replace_all_copy(fileContents, scriptName + "_", "Crawler_" );
    boost::algorithm::replace_all(s, "Script_minerName", "Crawler_outputName" );
    return s;
}

string doubleUnderscoreContext(const std::string& fileContents)
{
    if (boost::algorithm::contains(fileContents, "__match")) return fileContents;
    if (boost::algorithm::contains(fileContents, "TEMPLATE__")) return fileContents;
    string s = boost::algorithm::replace_all_copy(fileContents, "Crawler_", "Crawler__" );
    boost::algorithm::replace_all(s, "TEMPLATE_", "TEMPLATE__" );

    boost::algorithm::replace_all(s, "_match(", "__match(" );
    boost::algorithm::replace_all(s, "_match (", "__match(" );
    boost::algorithm::replace_all(s, "_mine(", "__mine(" );
    boost::algorithm::replace_all(s, "_mine (", "__mine(" );
    boost::algorithm::replace_all(s, "_navigate(", "__navigate(" );
    boost::algorithm::replace_all(s, "_navigate (", "__navigate(" );
    boost::algorithm::replace_all(s, "SearchListing_getProduct", "SearchListing__getProduct" );
    boost::algorithm::replace_all(s, "ProductPage_getSong", "ProductPage__getSong" );
    boost::algorithm::replace_all(s, "Loop_SearchListing_GetProduct", "Loop__SearchListing__GetProduct" );

    return s;
}

string contextFixup(const std::string& fileContents)
{
    string s = boost::algorithm::replace_all_copy(fileContents, "DEFAULT_genre_name__MOD", "genre_name__DEFAULT__MOD" );
    boost::algorithm::replace_all(s, "DEFAULT_media_format_name__MOD", "media_format_name__DEFAULT__MOD" );
    boost::algorithm::replace_all(s, "DEFAULT_media_type_name__MOD", "media_type_name__DEFAULT__MOD" );
    boost::algorithm::replace_all(s, "DEFAULT_data_record_type__MOD", "data_record_type__DEFAULT__MOD" );
    boost::algorithm::replace_all(s, "DEFAULT_item_time__MOD", "item_time__DEFAULT__MOD" );
    boost::algorithm::replace_all(s, "DEFAULT_item_year__MOD", "item_year__DEFAULT__MOD" );
    boost::algorithm::replace_all(s, "__MOD__DS", "__DoSearch__MOD" );
    boost::algorithm::replace_all(s, "__MOD__SL", "__SearchListing__MOD" );
    boost::algorithm::replace_all(s, "__MOD__PP", "__ProductPage__MOD" );
    boost::algorithm::replace_all(s, "__MOD__SONG", "__SONG__MOD" );
    boost::algorithm::replace_all(s, "__FIND__DS", "__DoSearch__FIND" );
    boost::algorithm::replace_all(s, "__FIND__SL", "__SearchListing__FIND" );
    boost::algorithm::replace_all(s, "__FIND__PP", "__ProductPage__FIND" );
    boost::algorithm::replace_all(s, "__FIND__SONG", "__SONG__FIND" );
    boost::algorithm::replace_all(s, "_FIND_DS", "__DoSearch__FIND" );
    boost::algorithm::replace_all(s, "_FIND_SL", "__SearchListing__FIND" );
    boost::algorithm::replace_all(s, "_FIND_PP", "__ProductPage__FIND" );
//    boost::algorithm::replace_all(s, "", "" );
//    boost::algorithm::replace_all(s, "", "" );
//    boost::algorithm::replace_all(s, "", "" );
//    boost::algorithm::replace_all(s, "", "" );
//    boost::algorithm::replace_all(s, "", "" );
//    boost::algorithm::replace_all(s, "", "" );




    return s;
}

int main(int argc, char *argv[])
{
    parseCommandLine(argc, argv);

    g_allScripts = filterPaths(g_allScripts);


    cout << "Number of scripts: " << g_allScripts.size() << endl;

    for ( const fs::path& p : g_allScripts) {
        string fileContents = read_file(p);
        string scriptName = getScriptName(fileContents);
//        if ( scriptName == "" ) cout << scriptName << " : " << p.string() << endl;


//        if (p.leaf().string() == "ExTemplateProductPage.tpl.php")
//        if (p.leaf().string() == "ExTemplateProductPage.php")
//        if (p.leaf().string() == "ExNavigatorAndSelects.php")
//        if (p.leaf().string() == "VinylPladenDk.php")
        // if (p.leaf().string() == "Airplay1.tpl.php")
        // if (scriptName == "MartinTestCdonDk")
        {
            cout << scriptName << " : " << p.string() << endl;
            string s = minerNameRemove(fileContents, scriptName);
            s = doubleUnderscoreContext(s);
            s = contextFixup(s);
//            cout << s << endl;
            write_file(p, s);
        }
    }


    return 0;
}

