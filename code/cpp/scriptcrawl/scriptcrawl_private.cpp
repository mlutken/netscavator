
//#include <hacks/wx_h_include_hack.h>
//#include <hacks/wx_h_php_undef_hack.h>

//#include <iostream>
//#include <utils/webbrowse_embedding_utils.h>
//#include <ScriptingClassIF.h>
//#include <MozBrowserWx.h>
//#include <ScriptMiner.h>

//#include <scriptcrawl_private_php.h>

#include <stdio.h>
#include "scriptcrawl_private.h"
#include <loki/Singleton.h>
#include <ScriptMinerIF.h>

namespace b = boost;

// --------------------------------------
// --- ScriptGlobals member functions ---
// --------------------------------------
class ScriptGlobals
{
public:

    ScriptGlobals();
    ~ScriptGlobals();

    void            currentMinerSet     ( boost::shared_ptr<crawl::ScriptMinerIF> pMiner );
    void            currentMinerNameSet ( const std::string& sName );
    std::string     currentMinerName    () const;
    boost::shared_ptr<crawl::ScriptMinerIF>		currentMiner() const
    {
        return m_pCurrentMiner;
    }


private:
    boost::shared_ptr<crawl::ScriptMinerIF>		m_pCurrentMiner;
    std::string                                 m_sCurrentMinerName;

};

typedef Loki::SingletonHolder<ScriptGlobals, Loki::CreateStatic>	G_ScriptGlobals;

ScriptGlobals::ScriptGlobals()
{ }

ScriptGlobals::~ScriptGlobals()
{ }


void ScriptGlobals::currentMinerSet     ( boost::shared_ptr<crawl::ScriptMinerIF> pMiner )
{
    m_pCurrentMiner = pMiner;
}

void ScriptGlobals::currentMinerNameSet ( const std::string& sName )
{
    m_sCurrentMinerName = sName;
}

std::string ScriptGlobals::currentMinerName  () const
{
    return m_sCurrentMinerName;
}

// -----------------


void currentMinerSet ( boost::shared_ptr<crawl::ScriptMinerIF> pMiner )
{
    G_ScriptGlobals::Instance().currentMinerSet(pMiner);
}

boost::shared_ptr<crawl::ScriptMinerIF> curMiner()
{
    return G_ScriptGlobals::Instance().currentMiner();
}

void currentMinerNameSet ( const std::string& sName )
{
    G_ScriptGlobals::Instance().currentMinerNameSet (sName );
}

std::string currentMinerName  ()
{
    return G_ScriptGlobals::Instance().currentMinerName();
}

