#ifndef _CRAWL_DOM_ACTION_MGR_H_
#define _CRAWL_DOM_ACTION_MGR_H_

#include <map>
#include <string>
#include <boost/shared_ptr.hpp>


namespace crawl {


/** 
XXX Brief description XXX.
XXX Detailed description here ... XXX
\author Veriquin */
class DomActionMgr 
{
public:


	// ----------------
	// --- Typedefs ---
	// ----------------
	struct Action {
		std::string		sAction;
		std::string		sParam1;
		std::string		sParam2;
		int				iSearchDir;
		Action ( const std::string& sAct, const std::string&sP1, const std::string& sP2, int iDir ) 
			:	sAction(sAct), sParam1(sP1), sParam2(sP2), iSearchDir(iDir) 
			{}
	};

	// ------------------------------------
	// --- Constructor / Init Functions ---
	// ------------------------------------
    DomActionMgr();
    void clear();

	// ----------------------------
	// --- Inline Get Functions ---
	// ----------------------------
	
	// ----------------------------------
	// --- Convenience Info Functions ---
	// ----------------------------------
	
	// ---------------------------
	// --- DomAction functions ---
	// ---------------------------
	void						domActionAdd		(	const std::string& sName, const std::string& sAction, const std::string& sParam1, 
														const std::string& sParam2, int iSearchDir );
	boost::shared_ptr<Action>	domActionGet		(	const std::string& sName ) const;
	
	// ----------------------
	// --- Misc Functions ---
	// ----------------------
	
	// -----------------------
	// --- Debug Functions ---
	// -----------------------


private:
	
	typedef	std::map<std::string, boost::shared_ptr<Action> >		MapT;
    // -------------------------
    // --- Private Functions ---
    // -------------------------
    // -------------------
    // --- Member Data ---
    // -------------------
	MapT					m_actions;
};


} // END namespace crawl

#endif //_CRAWL_DOM_ACTION_MGR_H_

