#ifndef _CRAWL_GLOBALS_H_
#define _CRAWL_GLOBALS_H_

#include <string>
#include <map>
#include <deque>
#include <memory>
#include <boost/shared_ptr.hpp>	

#include <loki/Singleton.h>
#include "interfaces_types.h"


class GuiActionsMgr;
class GuiGlobals;

namespace crawl { 

class Configuration;
class ScriptMinerIF;


class Globals
{
public:
	// ----------------
	// --- Typedefs ---
	// ----------------
    typedef std::deque< std::pair< std::string, std::string> >     RecentProjectsDequeT;

    Globals();
    ~Globals();

	

	// ------------------------
	// --- Helper functions ---
	// ------------------------
    void                                forceLink();
	
	// ---------------------------------------
	// --- Simple set/get inline functions ---
	// ---------------------------------------
    void                                configurationSet    ( boost::shared_ptr<Configuration> pConfig  );
    void                                minerAdd            ( boost::shared_ptr<ScriptMinerIF> pMiner, const std::string& sName  );
    void                                minerSetCurrent     ( const std::string& sName  );
    boost::shared_ptr<Configuration>    configuration       () const;
    boost::shared_ptr<ScriptMinerIF>    currentMiner        () const;
    GuiActionsMgr*                      guiActionsMgr       () const;
    void                                guiActionsMgrSet    ( GuiActionsMgr* pGuiActionsMgr );
    GuiGlobals*                         gui                 () const;
    void                                guiSet              ( GuiGlobals* pGuiGlobals );
    std::string                         currentMinerName    () const;
    void                                logWrite            ( LogLevelE logLevel, const std::string& msg );
    const RecentProjectsDequeT&         recentProjects      () const    { return m_recentProjects; }
    RecentProjectsDequeT&               recentProjects      ()          { return m_recentProjects; }

private:
    typedef std::map<std::string, boost::shared_ptr<ScriptMinerIF> > MinerMapT;
    // ----------------------------
    // --- PRIVATE: Member Data ---
    // ----------------------------
    boost::shared_ptr<Configuration>    m_pConfiguration;
    boost::shared_ptr<ScriptMinerIF>    m_pCurrentMiner;
    GuiActionsMgr*                      m_pGuiActionsMgr;
    GuiGlobals*                         m_pGuiGlobals;
    std::string                         m_sCurrentMinerName;
    MinerMapT                           m_miners;
    RecentProjectsDequeT                m_recentProjects;


};

typedef Loki::SingletonHolder<Globals, Loki::CreateUsingNew>	G;
//typedef Loki::SingletonHolder<Globals, Loki::CreateStatic>	G;

inline Globals* g()
{
    return &G::Instance();
}


//inline boost::shared_ptr<ScriptMinerIF> currentMiner()
//{
//    return G::Instance().currentMiner();
//}

inline boost::shared_ptr<Configuration> globalConfig()
{
    return G::Instance().configuration();
}


} // END namespace crawl


#endif // _CRAWL_GLOBALS_H_



