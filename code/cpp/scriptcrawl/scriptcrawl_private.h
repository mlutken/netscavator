#ifndef _SCRIPTCRAWL_PRIVATE_H_
#define _SCRIPTCRAWL_PRIVATE_H_


#include <string>
#include <boost/shared_ptr.hpp>

namespace crawl {
    class ScriptMinerIF;
}



void                                    currentMinerSet         ( boost::shared_ptr<crawl::ScriptMinerIF> pMiner );
boost::shared_ptr<crawl::ScriptMinerIF> curMiner();

void            currentMinerNameSet ( const std::string& sName );
std::string     currentMinerName    ();


#endif //_SCRIPTCRAWL_PRIVATE_H_


