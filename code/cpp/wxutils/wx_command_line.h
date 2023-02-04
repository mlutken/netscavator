#ifndef _WXUTILS_COMMAND_LINE__H_
#define _WXUTILS_COMMAND_LINE__H_

// For compilers that support precompilation, includes "wx/wx.h".
#include <hacks/wx_h_include_hack.h>
#include <hacks/wx_h_php_undef_hack.h>
#include <wx/cmdline.h>
#include <boost/shared_ptr.hpp>
#include <string>

namespace crawl {
    class Configuration;
}


void wxGetCommandLineParams(
        int argcIn
       , wxChar** argvIn
       , int& argcOut
       , char* argvOut[]
        );


void onInitCmdLineRobot     ( wxCmdLineParser& parser );
bool onCmdLineParsedRobot   (  boost::shared_ptr<crawl::Configuration> pConfig
                              , wxCmdLineParser& parser
                              , wxChar** argv
                              , int argc );


#endif // _WXUTILS_COMMAND_LINE__H_
