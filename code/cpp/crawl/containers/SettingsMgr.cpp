#include "SettingsMgr.h"
 
 
namespace crawl {


// ------------------------------------
// --- Constructor / Init Functions ---
// ------------------------------------
SettingsMgr::SettingsMgr( ) 
{
}

void SettingsMgr::clear()
{
    m_settings.clear();
}
 

// ------------------------
// --- DomSeq Functions ---
// ------------------------
void SettingsMgr::settingDelete		(
     const std::string& sName			///< [in] Name of setting
)
{
    m_settings.erase(sName);
}


void SettingsMgr::settingSet		(
	 const std::string& sName			///< [in] Name of setting 
	,const std::string& sValue			///< [in] Value of setting
)
{
	m_settings[sName] = boost::shared_ptr<Setting> ( new Setting(sName, sValue) ) ;
}

std::string SettingsMgr::settingGet( const std::string& sName, const std::string& defaultValue ) const
{
	MapT::const_iterator it = m_settings.find( sName );
	if ( it != m_settings.end() )	{
        return it->second->sValue;
	}
	else	{
        return defaultValue;
	}
}

bool SettingsMgr::settingExists( const std::string& sName ) const
{
    MapT::const_iterator it = m_settings.find( sName );
    return ( it != m_settings.end() );
}


} // END namespace crawl


