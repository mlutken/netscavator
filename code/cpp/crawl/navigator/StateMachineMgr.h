#ifndef _CRAWL_STATE_MACHINE_MGR_H_
#define _CRAWL_STATE_MACHINE_MGR_H_

#include <string>
#include <map>
#include <boost/shared_ptr.hpp>

class ScriptMiner;

namespace crawl {

class DomNavigator;

class StateMachineMgr
{
public:
    // ------------------------
    // --- PUBLIC: Typedefs ---
    // ------------------------

    // ------------------------------------
    // --- Constructor / Init Functions ---
    // ------------------------------------
    StateMachineMgr(const ScriptMiner* pScriptMiner);
    void reset();


    // ---------------------------------
    // --- PUBLIC: Set/Add functions ---
    // ---------------------------------
    void            smAddNew        ( const std::string& sName);
    void            smSetCurrent    ( const std::string& sName );

    // ------------------------------
    // --- PUBLIC: Info functions ---
    // ------------------------------
    boost::shared_ptr<DomNavigator>          smCurrent()             { return m_pCurrentSM;      }
    const boost::shared_ptr<DomNavigator>    smCurrent()     const   { return m_pCurrentSM;      }
    const std::string&                       smCurrentName() const   { return m_sCurrentSMName;  }


private:
    // --- PRIVATE: Typedefs ---
    typedef std::map<std::string, boost::shared_ptr<DomNavigator> >   SMMapT;


    // --- PRIVATE: Members ---
    std::string                         m_sCurrentSMName;
    boost::shared_ptr<DomNavigator>     m_pCurrentSM;
    SMMapT                              m_SMMap;
    const ScriptMiner*                  m_pScriptMiner;

};



} //END namespace crawl

#endif //_CRAWL_STATE_MACHINE_MGR_H_

