#ifndef _INTERFACES_UTILS_H_
#define _INTERFACES_UTILS_H_


#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <interfaces_types.h>

namespace crawl {
    class DomNodeIF;

    typedef std::vector<std::string>     StrVecT;

    std::string     nodeTypeToString    ( boost::shared_ptr<DomNodeIF> const& pNode );
    std::string     trimBlanksCopy      ( const std::string& sInput );
    std::string     toString            ( RunModeE eRunMode );
    RunModeE        toRunMode           ( const std::string& sRunMode );
    bool            stringToBool        ( const std::string& sValue );

    void            createScriptParams  ( const std::string& sScriptPath, const StrVecT& params,  int& argcOut, char* argvOut[] );
    void            createScriptParams  ( const std::string& sScriptPath, const std::string& params,  int& argcOut, char* argvOut[] );


} // END namespace crawl


#endif //_INTERFACES_UTILS_H_

