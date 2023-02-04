#include <iostream>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <cpaf_file_directory_functions.h>
#include <cpaf_string_utils.hpp>
#include <utils/StringFinder.h>
#include <navigator/SiteMapGetter.h>


using namespace std;
using namespace cpaf::filesystem;
using namespace crawl;
namespace po = boost::program_options;
namespace fs = boost::filesystem;
namespace ba = boost::algorithm;

static boost::program_options::variables_map   g_vm;


/*
With: bcbikeshop.dk
We get:

<!DOCTYPE HTML PUBLIC "-//IETF//DTD HTML 2.0//EN">
<html><head>
<title>301 Moved Permanently</title>
</head><body>
<h1>Moved Permanently</h1>
<p>The document has moved <a href="https://bcbikeshop.dk/robots.txt">here</a>.</p>
<hr>
<address>Apache Server at bcbikeshop.dk Port 80</address>
</body></html>


*/

bool parseCommandLine ( int argc, char* argv[] )
{

    try {

        // https://www.veromoda.com
        // www.sitemaps.org, https:/www.sitemaps.org
        // Declare a group of options that will be allowed only on command line
        po::options_description basic("Basic options");
        basic.add_options()
            ("version,v",   "print version string")
            ("help,h",      "produce help message")
            ("site,s",       po::value<string>()->default_value("https://www.veromoda.com"), "Site to parse")
            ;


        po::options_description cmdline_options;
        cmdline_options.add(basic);


        po::store(po::command_line_parser(argc, argv).options(cmdline_options).run(), g_vm);
        po::notify(g_vm);


        if (g_vm.count("help")) {
            cout << cmdline_options << "\n";
            return false;
        }

        cout << "Site: " << g_vm["site"].as<string>() << endl;
    }
    catch(std::exception& e)
    {
        cout << "Error: Unknown arguments given:" << endl;
        cout << e.what() << "\n";
        return false;
    }
    return true;
}

int main(int argc, char *argv[])
{
    parseCommandLine(argc, argv);

    SiteMapGetter sg(g_vm["site"].as<string>());

    cout << "site_maps_getter site: " << "XXX" << endl;

    sg.downloadSiteMap();


    return 0;
}

