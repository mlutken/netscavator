#include "ModifierMgr.h"
#include <iostream>
#include <Configuration.h>


using namespace std;
namespace crawl {

// ------------------------------------
// --- Static member initialization ---
// ------------------------------------


// ------------------------------------
// --- Constructor / Init Functions ---
// ------------------------------------
ModifierMgr::ModifierMgr( ) 
{
}

void ModifierMgr::clear()
{
    m_modifiers.clear();
}

// ----------------------------------
// --- Convenience Info Functions ---
// ----------------------------------
bool ModifierMgr::modifierExists( const std::string& sName ) const
{
    MapT::const_iterator it = m_modifiers.find( sName );
    return it != m_modifiers.end();
}

// ------------------------
// --- DomSeq Functions ---
// ------------------------
void ModifierMgr::modifierAdd		(	
	 const std::string& sName			///< [in] Name of modifier to add 
	,const std::string& sMainipFunID	///< [in] ID of built-in string modifier/manipulation function. E.g. 'append', 'replaceAll', ...
	,const std::string& sParam1			///< [in] Parameter 1 of modifier
	,const std::string& sParam2			///< [in] Parameter 2 of modifier
	,const std::string& sParam3			///< [in] Parameter 2 of modifier
	,const std::string& sParam4			///< [in] Parameter 2 of modifier
)
{
	m_modifiers[sName] = boost::shared_ptr<Modifier> ( new Modifier(sMainipFunID, sParam1, sParam2, sParam3, sParam4) ) ;
}

boost::shared_ptr<ModifierMgr::Modifier> ModifierMgr::modifierGet( const std::string& sName ) const
{
    MapT::const_iterator it = m_modifiers.find( sName );
	if ( it != m_modifiers.end() )	{
        auto mod = it->second;
        return mod;
	}
	else	{
		return boost::shared_ptr<Modifier>();
	}
}

// -----------------------
// --- Debug Functions ---
// -----------------------


// -------------------------
// --- Private Functions ---
// -------------------------


// ----------------------
// --- Free Functions ---
// ----------------------



} // END namespace crawl


