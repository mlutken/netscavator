#ifndef _CRAWL_MODIFIER_MGR_H_
#define _CRAWL_MODIFIER_MGR_H_

#include <map>
#include <string>
#include <boost/shared_ptr.hpp>

namespace crawl {
class Configuration;


/** 
XXX Brief description XXX.
XXX Detailed description here ... XXX
\author Veriquin */
class ModifierMgr 
{
public:


	// ----------------
	// --- Typedefs ---
	// ----------------
	struct Modifier {
		std::string		sManipFunID;	///< ID of one of the built-in string modifier/manipulation functions
		std::string		sParam1;
		std::string		sParam2;
		std::string		sParam3;
		std::string		sParam4;
		Modifier ( const std::string& sManipFun, const std::string&sP1, const std::string& sP2, const std::string& sP3, const std::string& sP4 ) 
			:	sManipFunID(sManipFun), sParam1(sP1), sParam2(sP2), sParam3(sP3), sParam4(sP4) 
			{}
	};

	// ------------------------------------
	// --- Constructor / Init Functions ---
	// ------------------------------------
    ModifierMgr();
    void clear();

	// ----------------------------
	// --- Inline Get Functions ---
	// ----------------------------
	
	// ----------------------------------
	// --- Convenience Info Functions ---
	// ----------------------------------
    bool                        modifierExists  ( const std::string& sName ) const;
	// ---------------------------
	// --- Modifier functions ---
	// ---------------------------
	void						modifierAdd		(	const std::string& sName, const std::string& sMainipFunID, const std::string& sParam1, 
													const std::string& sParam2,const std::string& sParam3, const std::string& sParam4 );
	boost::shared_ptr<Modifier>	modifierGet		(	const std::string& sName ) const;
	
	// ----------------------
	// --- Misc Functions ---
	// ----------------------
	
	// -----------------------
	// --- Debug Functions ---
	// -----------------------


private:
	
	typedef	std::map<std::string, boost::shared_ptr<Modifier> >		MapT;
    // -------------------------
    // --- Private Functions ---
    // -------------------------
    // -------------------
    // --- Member Data ---
    // -------------------
	MapT					m_modifiers;
};


} // END namespace crawl

#endif //_CRAWL_MODIFIER_MGR_H_

