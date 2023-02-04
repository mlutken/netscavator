#include "PhpScriptingClass.h"

#include <iostream>
#include <stdio.h>
#include <zend.h>
#include <zend_interfaces.h>
#include <zend_API.h>
#include <php.h>
#include <SAPI.h>

#include <php_embedding/php_embedding_utils.h>
#include "scriptcrawl_private_php.h"

using namespace std;

//#ifdef ZTS
//    void*** tsrm_ls;
//#endif

PhpScriptingClass::PhpScriptingClass()
{
////    PhpScriptingClass::readScriptFunctions(); // FIXME, TODO, If no problems for a while then remove this uncommented call to readScriptFunctions()
}

PhpScriptingClass::~PhpScriptingClass()
{

}

void PhpScriptingClass::readScriptFunctions()
{
    clearFunctions();
    HashPosition 	function_pos;
    zend_function* 	function_find;
    TSRMLS_FETCH();
    zend_hash_internal_pointer_reset_ex( EG(function_table), &function_pos  );
    while ( zend_hash_has_more_elements_ex( EG(function_table), &function_pos) == SUCCESS && !EG(exception) ) {
        zend_hash_get_current_data_ex( EG(function_table), (void**)&function_find, &function_pos);
        std::string sFunName = function_find->common.function_name;

        addFunction( sFunName );
        zend_hash_move_forward_ex( EG(function_table), &function_pos);
    }

}


// --------------------------------------
// --- Call script function functions ---
// --------------------------------------
bool PhpScriptingClass::scriptFunctionExists  ( const std::string& sFunName 	) const
{
    return phpFunctionExists(sFunName);
}

void PhpScriptingClass::callScriptFunction_Void 	( const std::string& sFunName 	) const
{
    phpCallScriptFunction_Void( sFunName );
}

void PhpScriptingClass::callScriptFunction_Void ( const std::string& sFunName, const std::string& sParam ) const
{
    phpCallScriptFunction_Void( sFunName, sParam );
}


long PhpScriptingClass::callScriptFunction_Long		( const std::string& sFunName 	) const
{
    return phpCallScriptFunction_Long( sFunName );
}


double PhpScriptingClass::callScriptFunction_Double	( const std::string& sFunName 	) const
{
    return phpCallScriptFunction_Double	( sFunName 	);
}

double PhpScriptingClass::callScriptFunction_Double	( const std::string& sFunName, const std::string& sParam ) const
{
    return phpCallScriptFunction_Double	( sFunName, sParam );
}

double PhpScriptingClass::callScriptFunction_Double	( const std::string& sFunName, const std::string& sParam1, const std::string& sParam2  	) const
{
    return phpCallScriptFunction_Double ( sFunName, sParam1, sParam2  );
}


bool PhpScriptingClass::callScriptFunction_Bool ( const std::string& sFunName ) const
{
    return phpCallScriptFunction_Bool ( sFunName ) ;
}

bool PhpScriptingClass::callScriptFunction_Bool	( const std::string& sFunName, const std::string& sParam ) const
{
    return phpCallScriptFunction_Bool ( sFunName, sParam );
}

bool PhpScriptingClass::callScriptFunction_Bool	( const std::string& sFunName, const std::string& sParam1, const std::string& sParam2 ) const
{
    return phpCallScriptFunction_Bool	( sFunName, sParam1, sParam2 );
}

bool PhpScriptingClass::callScriptFunction_Bool	( const std::string& sFunName, const std::string& sParam1, const std::string& sParam2, const std::string& sParam3 ) const
{
    return phpCallScriptFunction_Bool	( sFunName, sParam1, sParam2,sParam3 );
}

bool PhpScriptingClass::callScriptFunction_Bool	( const std::string& sFunName, const std::string& sParam1, const std::string& sParam2, const std::string& sParam3, const std::string& sParam4 ) const
{
    return phpCallScriptFunction_Bool	( sFunName, sParam1, sParam2, sParam3, sParam4 );
}


std::string PhpScriptingClass::callScriptFunction_String ( const std::string& sFunName 	) const
{
    return phpCallScriptFunction_String ( sFunName 	) ;
}

std::string PhpScriptingClass::callScriptFunction_String ( const std::string& sFunName, const std::string& sParam ) const
{
    return phpCallScriptFunction_String ( sFunName, sParam );
}

std::string PhpScriptingClass::callScriptFunction_String ( const std::string& sFunName, const std::string& sParam1, const std::string& sParam2 ) const
{
    return phpCallScriptFunction_String ( sFunName, sParam1, sParam2 );
}

std::string PhpScriptingClass::callScriptFunction_String ( const std::string& sFunName, const std::string& sParam1, const std::string& sParam2, const std::string& sParam3 ) const
{
    return phpCallScriptFunction_String (sFunName, sParam1, sParam2, sParam3 );
}

std::string PhpScriptingClass::callScriptFunction_String ( const std::string& sFunName, const std::string& sParam1, const std::string& sParam2, const std::string& sParam3, const std::string& sParam4 ) const
{
    return phpCallScriptFunction_String (  sFunName,  sParam1,  sParam2, sParam3, sParam4 );
}

boost::any	PhpScriptingClass::callScriptFunction_Any  ( const std::string& sFunName 	) const
{
    return phpCallScriptFunction_Any ( sFunName 	) ;
}


// -----------------------------------
// --- Set/get variables functions ---
// -----------------------------------
void PhpScriptingClass::varSet ( const std::string& sName, const std::string& sValue	) const
{
//    zval* type;
//    ALLOC_INIT_ZVAL(type);
//    ZVAL_STRING(type, "Embedded2", 1);

//    char szType[2048];
//    strcpy(szType, "type" );
//    ZEND_SET_SYMBOL (&EG(symbol_table), szType, type );

}

std::string PhpScriptingClass::varGet_String ( const std::string& sName ) const
{
	return "";
}

