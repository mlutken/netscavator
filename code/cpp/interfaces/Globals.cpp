#include "Globals.h"
#include "Configuration.h"
#include <stdio.h>
#include <iostream>


using namespace std;

namespace crawl { 

    Globals::Globals()
        : m_pConfiguration( new Configuration )
        , m_pGuiActionsMgr(0)
    {
    }

    Globals::~Globals()
    {
    }

    void Globals::forceLink()
    {
        printf("\n\nGlobals::forceLink()\n\n");
    }

    // --------------------------------
    // --- Simple set/get functions ---
    // --------------------------------

    void Globals::configurationSet  ( boost::shared_ptr<Configuration> pConfig )
    {
        m_pConfiguration = pConfig;
    }


    void Globals::minerAdd (
            boost::shared_ptr<ScriptMinerIF> pMiner
            ,   const std::string& sName )
    {
        m_miners[sName]     = pMiner;
        m_pCurrentMiner     = pMiner; // TODO: Only temporary that we set current here also !!
        m_sCurrentMinerName = sName;
    }

    void  Globals::minerSetCurrent   ( const std::string& sName  )
    {
        m_pCurrentMiner = m_miners[sName];
        m_sCurrentMinerName = sName;
    }

    boost::shared_ptr<Configuration>
            Globals::configuration () const
    {
        return m_pConfiguration;
    }

    boost::shared_ptr<ScriptMinerIF>
            Globals::currentMiner () const
    {
        return m_pCurrentMiner;
    }

    GuiActionsMgr* Globals::guiActionsMgr () const
    {
        return m_pGuiActionsMgr;
    }

    void Globals::guiActionsMgrSet  ( GuiActionsMgr* pGuiActionsMgr )
    {
        m_pGuiActionsMgr = pGuiActionsMgr;
    }

    GuiGlobals* Globals::gui () const
    {
        return m_pGuiGlobals;
    }

    void Globals::guiSet ( GuiGlobals* pGuiGlobals )
    {
        m_pGuiGlobals = pGuiGlobals;
    }


    std::string Globals::currentMinerName  () const
    {
        return m_sCurrentMinerName;
    }

    void  Globals::logWrite  ( LogLevelE /*logLevel*/, const std::string& msg )
    {
		printf("%s\n", msg.c_str() );
        ////std::cout << msg << std::endl;
    }



} // END namespace crawl





