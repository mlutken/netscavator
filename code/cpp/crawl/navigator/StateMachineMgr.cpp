#include "StateMachineMgr.h"

#include <navigator/DomNavigator.h>


namespace crawl {



// ------------------------------------
// --- Constructor / Init Functions ---
// ------------------------------------
StateMachineMgr::StateMachineMgr(const ScriptMiner* pScriptMiner)
    : m_sCurrentSMName("Navigator") // Before: 'State'
    , m_pCurrentSM ( new DomNavigator(pScriptMiner) )
    , m_SMMap()
    , m_pScriptMiner(pScriptMiner)
{
    m_SMMap[m_sCurrentSMName] = m_pCurrentSM;
}


void StateMachineMgr::reset()
{
    SMMapT::iterator it    = m_SMMap.begin();
    SMMapT::iterator itEND = m_SMMap.end();
    for ( ; it != itEND; ++it ) {
        it->second->reset();
    }
}


// ---------------------------------
// --- PUBLIC: Set/Add functions ---
// ---------------------------------
void StateMachineMgr::smAddNew (
      const std::string& sName
   )
{
    m_sCurrentSMName = sName;
    m_pCurrentSM = boost::shared_ptr<DomNavigator>( new DomNavigator(m_pScriptMiner) );
    m_SMMap[m_sCurrentSMName] = m_pCurrentSM;
}

void StateMachineMgr::smSetCurrent ( const std::string& sName )
{
    SMMapT::const_iterator it = m_SMMap.find( sName );
    if ( it != m_SMMap.end() ) {
        m_sCurrentSMName    = sName;
        m_pCurrentSM        = it->second;
    }
    else {
        smAddNew(sName);
    }

}


} // END namespace crawl

