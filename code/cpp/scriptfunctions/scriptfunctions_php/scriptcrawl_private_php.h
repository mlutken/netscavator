#ifndef _SCRIPTCRAWL_PRIVATE_PHP_H_
#define _SCRIPTCRAWL_PRIVATE_PHP_H_

#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/any.hpp>

namespace crawl {
    class ScriptingClassIF;
}


boost::shared_ptr<crawl::ScriptingClassIF>
createPhpScriptingClass();

crawl::ScriptingClassIF*
createPhpScriptingClassRaw();


// ------------------------------------------
// --- Call PHP script function functions ---
// ------------------------------------------

void						phpCallScriptFunction_Void      ( const std::string& sFunName 	);
void						phpCallScriptFunction_Void      ( const std::string& sFunName, const std::string& sParam  	);

long						phpCallScriptFunction_Long		( const std::string& sFunName 	);

double						phpCallScriptFunction_Double	( const std::string& sFunName 	);
double						phpCallScriptFunction_Double	( const std::string& sFunName, const std::string& sParam  	);
double						phpCallScriptFunction_Double	( const std::string& sFunName, const std::string& sParam1, const std::string& sParam2  	);

bool						phpCallScriptFunction_Bool      ( const std::string& sFunName 	);
bool						phpCallScriptFunction_Bool		( const std::string& sFunName, const std::string& sParam 	);
bool						phpCallScriptFunction_Bool		( const std::string& sFunName, const std::string& sParam1, const std::string& sParam2  	);
bool						phpCallScriptFunction_Bool		( const std::string& sFunName, const std::string& sParam1, const std::string& sParam2, const std::string& sParam3 );
bool						phpCallScriptFunction_Bool		( const std::string& sFunName, const std::string& sParam1, const std::string& sParam2, const std::string& sParam3, const std::string& sParam4 );


std::string					phpCallScriptFunction_String 	( const std::string& sFunName 	);
std::string					phpCallScriptFunction_String	( const std::string& sFunName, const std::string& sParam 	);
std::string					phpCallScriptFunction_String	( const std::string& sFunName, const std::string& sParam1, const std::string& sParam2  	);
std::string					phpCallScriptFunction_String	( const std::string& sFunName, const std::string& sParam1, const std::string& sParam2, const std::string& sParam3 );
std::string					phpCallScriptFunction_String	( const std::string& sFunName, const std::string& sParam1, const std::string& sParam2, const std::string& sParam3, const std::string& sParam4 );

boost::any					phpCallScriptFunction_Any       ( const std::string& sFunName 	);


#endif

