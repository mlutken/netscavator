
// For compilers that support precompilation, includes "wx/wx.h".
#include "wx_command_line.h"
#include <boost/algorithm/string.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <wx/stdpaths.h>
#include <Configuration.h>

static const wxCmdLineEntryDesc g_cmdLineDescRobot [] =
{
    { wxCMD_LINE_NONE }
};

static const wxCmdLineEntryDesc g_cmdLineDescEmpty [] =
{
    { wxCMD_LINE_NONE }
};


void wxGetCommandLineParams(
         int argcIn
        , wxChar** argvIn
        , int& argcOut
        , char* argvOut[]
        )
{
    using namespace boost;
    using namespace std;

    for ( int i = 0; i < argcIn; ++i ){
        wxString sWx( argvIn[i] );
        string s = sWx.mb_str(wxConvUTF8).data();
        strcpy(argvOut[i], s.c_str() );
    }
    argcOut = argcIn;
}



void onInitCmdLineRobot(wxCmdLineParser& parser)
{
    parser.SetCmdLine(wxT(""));
    parser.SetDesc (g_cmdLineDescEmpty);
    //must refuse '/' as parameter starter or cannot use "/path" style paths
    parser.SetSwitchChars (wxT("-"));
}

bool onCmdLineParsedRobot(
        boost::shared_ptr<crawl::Configuration> /*pConfig*/
        , wxCmdLineParser& /*parser*/
        , wxChar** /*argv*/
        , int /*argc*/ )
{
    return true;
}
