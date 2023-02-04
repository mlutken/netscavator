#include "ScriptingClassIF.h"
#include <stdio.h>


namespace crawl {

ScriptingClassIF::ScriptingClassIF()
{

}

ScriptingClassIF::~ScriptingClassIF()
{

}

void ScriptingClassIF::readScriptFunctions ()
{

}

// --------------------------------------
// --- Call script function functions ---
// --------------------------------------
bool ScriptingClassIF::scriptFunctionExists  ( const std::string& /*sFunName*/ 	) const
{
    return false;
}

void ScriptingClassIF::callScriptFunction_Void 	( const std::string& /*sFunName*/ 	) const
{

}

void ScriptingClassIF::callScriptFunction_Void	( const std::string& /*sFunName*/, const std::string& /*sParam*/  	) const
{
}


long ScriptingClassIF::callScriptFunction_Long		( const std::string& /*sFunName*/ 	) const
{
    return 0;
}


double ScriptingClassIF::callScriptFunction_Double	( const std::string& /*sFunName*/ 	) const
{
    return 0;
}

double ScriptingClassIF::callScriptFunction_Double	( const std::string& /*sFunName*/, const std::string& /*sParam*/  	) const
{
    return 0;
}

double ScriptingClassIF::callScriptFunction_Double	( const std::string& /*sFunName*/, const std::string& /*sParam1*/, const std::string& /*sParam2*/  	) const
{
    return 0;
}


bool ScriptingClassIF::callScriptFunction_Bool 	( const std::string& /*sFunName*/ 	) const
{
    return false;
}

bool ScriptingClassIF::callScriptFunction_Bool	( const std::string& /*sFunName*/, const std::string& /*sParam*/ 	) const
{
    return false;
}

bool ScriptingClassIF::callScriptFunction_Bool	( const std::string& /*sFunName*/, const std::string& /*sParam1*/, const std::string& /*sParam2*/  	) const
{
    return false;
}

bool ScriptingClassIF::callScriptFunction_Bool	( const std::string& /*sFunName*/, const std::string& /*sParam1*/, const std::string& /*sParam2*/, const std::string& /*sParam3*/ ) const
{
    return false;
}

bool ScriptingClassIF::callScriptFunction_Bool	( const std::string& /*sFunName*/, const std::string& /*sParam1*/, const std::string& /*sParam2*/, const std::string& /*sParam3*/, const std::string& /*sParam4*/ ) const
{
    return false;
}


std::string ScriptingClassIF::callScriptFunction_String ( const std::string& /*sFunName*/ 	) const
{
    return "";
}

std::string ScriptingClassIF::callScriptFunction_String	( const std::string& /*sFunName*/, const std::string& /*sParam*/ ) const
{
    return "";
}

std::string ScriptingClassIF::callScriptFunction_String	( const std::string& /*sFunName*/, const std::string& /*sParam1*/, const std::string& /*sParam2*/  	) const
{
    return "";
}

std::string ScriptingClassIF::callScriptFunction_String	( const std::string& /*sFunName*/, const std::string& /*sParam1*/, const std::string& /*sParam2*/, const std::string& /*sParam3*/ ) const
{
    return "";
}

std::string ScriptingClassIF::callScriptFunction_String	( const std::string& /*sFunName*/, const std::string& /*sParam1*/, const std::string& /*sParam2*/, const std::string& /*sParam3*/, const std::string& /*sParam4*/ ) const
{
    return "";
}

boost::any	ScriptingClassIF::callScriptFunction_Any      ( const std::string& /*sFunName*/ 	) const
{
    return  boost::any();
}

// -----------------------------------
// --- Set/get variables functions ---
// -----------------------------------
void ScriptingClassIF::varSet ( const std::string& /*sName*/, const std::string& /*sValue*/	) const
{

}

std::string ScriptingClassIF::varGet_String ( const std::string& /*sName*/ ) const
{
    return "";
}

// -----------------------------------
// --- PROTECTED: Helper functions ---
// -----------------------------------

void ScriptingClassIF::addFunction ( std::string const& sFunctionName )
{
    m_allFunctionsVec.push_back( sFunctionName );
    m_allFunctionsSet.insert( sFunctionName );
}


} // END namespace crawl
