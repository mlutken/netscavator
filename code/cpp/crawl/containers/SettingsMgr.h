#ifndef _CRAWL_SETTINGS_MGR_H_
#define _CRAWL_SETTINGS_MGR_H_

#include <map>
#include <string>
#include <boost/shared_ptr.hpp>


namespace crawl {


/** 
XXX Brief description XXX.
XXX Detailed description here ... XXX
\author Veriquin */
class SettingsMgr 
{
public:


	// ----------------
	// --- Typedefs ---
	// ----------------
	struct Setting {
		std::string		sName;
		std::string		sValue;
		Setting ( const std::string& sNme, const std::string& sVal ) 
			:	sName(sNme), sValue(sVal) 
			{}
	};

	// ------------------------------------
	// --- Constructor / Init Functions ---
	// ------------------------------------
    SettingsMgr();
    void clear();


	// ---------------------------
	// --- Settings functions ---
	// ---------------------------
    void						settingDelete	(	const std::string& sName );
    void						settingSet		(	const std::string& sName, const std::string& sValue );
    std::string                 settingGet		( const std::string& sName, const std::string& defaultValue = "") const;
    bool                        settingExists	(	const std::string& sName ) const;


private:
	
	typedef	std::map<std::string, boost::shared_ptr<Setting> >		MapT;

    // --- Member Data ---
	MapT					m_settings;
};


} // END namespace crawl

#endif //_CRAWL_SETTINGS_MGR_H_

