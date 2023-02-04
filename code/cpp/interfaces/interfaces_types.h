#pragma once


#include <string>	
#include <map>
namespace crawl {

typedef std::map<std::string,std::string>   AttributesMap;

enum RunModeE { rmNormalE, rmCrawlerE, rmDesignE, rmDebugE };

enum MiningStepE { stepNoneE, stepMatchE, stepMineE, stepNavigateE, stepLoadPageE };

enum LogLevelE {
        logInfoE        =   1 << 0
    ,   logWarningE     =   1 << 1
    ,   logErrorE       =   1 << 2
    ,   logScriptDebugE =   1 << 3
    ,   logCppDebugE    =   1 << 4
};

enum MiningStatusE {
        miningActiveE                   =   0   ///< Crawler running normally
    ,   miningDoneScriptDoneE           =   1   ///< Normal exit when script is done mining
    ,   miningDoneMaxPageLoadsReachedE  =   2   ///< Max number of pageload specified on command line reached
    ,   miningDoneUserExitE             =   3   ///< Force exit by user
    ,   miningDoneCrawlerKilledE        =   4   ///< Crawler was killed by automated mining tools (robot control)
    ,   miningDoneCrawlerCrashedE       =   5   ///< Crawler crashed
    ,   miningDoneUserStopE             =   6   ///< Force stop by user
};

inline bool  runModeCreator    (RunModeE rm) { return rm == rmDesignE || rm == rmDebugE; }


} // END namespace crawl
