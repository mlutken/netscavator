#include "DomActionMgr.h"
 
 
namespace crawl {

// ------------------------------------
// --- Static member initialization ---
// ------------------------------------


// ------------------------------------
// --- Constructor / Init Functions ---
// ------------------------------------
DomActionMgr::DomActionMgr( ) 
{
}

void DomActionMgr::clear()
{
    m_actions.clear();
}


// ------------------------
// --- DomSeq Functions ---
// ------------------------
void DomActionMgr::domActionAdd		(	
	 const std::string& sName		///< [in] Name of the named action we are creating (e.g. 'MyClickNextBtnAction' )
	,const std::string& sAction		///< [in] (String) ID of action to perform
	,const std::string& sParam1		///< [in] Parameter 1 to action, if applicable, can be set to empty string if not needed.
	,const std::string& sParam2		///< [in] Parameter 2 to action, if applicable, can be set to empty string if not needed.
	,int iSearchDir					///< [in] "Direction" to search for the node: NEAREST_FORWARD, NEAREST_BACKWARD, NEAREST_BOTH, NEAREST_PARENT , NEAREST_AUTO, NEAREST_THIS_NODE
)
{
	m_actions[sName] = boost::shared_ptr<Action> ( new Action(sAction, sParam1, sParam2, iSearchDir ) ) ;
}

boost::shared_ptr<DomActionMgr::Action> DomActionMgr::domActionGet( const std::string& sName ) const
{
	MapT::const_iterator it = m_actions.find( sName );
	if ( it != m_actions.end() )	{
		return it->second;
	}
	else	{
		return boost::shared_ptr<Action>();
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


