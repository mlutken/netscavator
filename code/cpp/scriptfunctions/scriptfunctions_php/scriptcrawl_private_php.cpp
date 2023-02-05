////#include <hacks/wx_h_include_hack.h>
//TODO: Not needeed anymore since we don't use wx!? #include <hacks/wx_h_php_undef_hack.h>
#include <zend.h>
#include <zend_interfaces.h>
#include <zend_API.h>
#include <php.h>
#include <SAPI.h>

#include <boost/filesystem/fstream.hpp>
#include <boost/algorithm/string.hpp>
#include <cpaf_libs/utils/cpaf_string_utils.hpp>


////#include "../scriptcrawl_private.h"
#include "PhpScriptingClass.h"


//#ifdef ZTS
//    void*** tsrm_ls;
//#endif


// ---------------------------------------
// --- ScriptingClass create functions ---
// ---------------------------------------

boost::shared_ptr<crawl::ScriptingClassIF>
createPhpScriptingClass()
{
    return boost::shared_ptr<crawl::ScriptingClassIF>( new PhpScriptingClass );
}

crawl::ScriptingClassIF*
createPhpScriptingClassRaw()
{
    return new PhpScriptingClass;
}


// --------------------------------------------
// --- Helper templates to get return value ---
// --------------------------------------------

template <typename RET_TYPE>
RET_TYPE	getPhpRetVal 	( zval*	pRetval )
{
}

template <>
long	getPhpRetVal<long> 	( zval*	pRetval )
{
    long iRetVal = 0;
    if ( Z_TYPE_P(pRetval) == IS_LONG 	) 	iRetVal = static_cast<long>(Z_LVAL_P(pRetval));
    if ( Z_TYPE_P(pRetval) == IS_DOUBLE ) 	iRetVal = static_cast<long>(Z_DVAL_P(pRetval));
    return iRetVal;
}


template <>
bool	getPhpRetVal<bool> 	( zval*	pRetval )
{
    bool bRetVal = false;
    if      ( Z_TYPE_P(pRetval) == IS_FALSE ) 	bRetVal = static_cast<bool>(false);
    else if ( Z_TYPE_P(pRetval) == IS_TRUE 	) 	bRetVal = static_cast<bool>(true);
    else if ( Z_TYPE_P(pRetval) == IS_LONG 	) 	bRetVal = static_cast<bool>(Z_LVAL_P(pRetval));
    else if ( Z_TYPE_P(pRetval) == IS_DOUBLE ) 	bRetVal = static_cast<bool>(Z_DVAL_P(pRetval));
    else if ( (Z_TYPE_P(pRetval) == IS_STRING) && pRetval->value.str) {
        std::string sRetVal = Z_STRVAL_P(pRetval);
        if ( sRetVal != "" && sRetVal != "0" && sRetVal != "false" )	bRetVal = true;
    }
    return bRetVal;
}


template <>
double	getPhpRetVal<double> 	( zval*	pRetval )
{
    double fRetVal = 0.0;
    if ( Z_TYPE_P(pRetval) == IS_LONG 	) 	fRetVal = static_cast<double>(Z_LVAL_P(pRetval));
    if ( Z_TYPE_P(pRetval) == IS_DOUBLE ) 	fRetVal = static_cast<double>(Z_DVAL_P(pRetval));
    return fRetVal;
}


template <>
std::string	getPhpRetVal<std::string> 	( zval*	pRetval )
{
    std::string 	sRetVal	= "";
    if ( (Z_TYPE_P(pRetval) == IS_STRING) && pRetval->value.str) {	sRetVal = Z_STRVAL_P(pRetval);	}
    return sRetVal;
}


template <>
boost::any	getPhpRetVal<boost::any> 	( zval*	pRetval )
{
    boost::any anyRetVal;
    if      ( Z_TYPE_P(pRetval) == IS_FALSE ) 	anyRetVal = static_cast<bool>(false);
    else if ( Z_TYPE_P(pRetval) == IS_TRUE 	) 	anyRetVal = static_cast<bool>(true);
    else if ( Z_TYPE_P(pRetval) == IS_LONG 	) 	anyRetVal = static_cast<long>(Z_LVAL_P(pRetval));
    else if ( Z_TYPE_P(pRetval) == IS_DOUBLE ) 	anyRetVal = static_cast<double>(Z_DVAL_P(pRetval));
    else if ( (Z_TYPE_P(pRetval) == IS_STRING) && pRetval->value.str ) {
        std::string sRetVal = Z_STRVAL_P(pRetval);
        anyRetVal = sRetVal;
    }
    return anyRetVal;
}



// --------------------------------------
// --- Call script function functions ---
// --------------------------------------


#define CALL_PHP_FUN_BEGIN													\
    bool                bOk = true;                                         \
    zval* 				pFunctionName;										\
    zval*				pRetval;											\
    TSRMLS_FETCH();															\
    ZVAL_STRING			( pFunctionName, (char*)sFunName.c_str() 	);
                                                                                                                        \

#define CALL_PHP_FUN_END                                                                            \
    if ( true == bOk ) {                                                                            \
      zval_ptr_dtor(&pRetval);                                                                      \
    } else {                                                                                        \
        printf("ERROR: FIXMENM Function call from C++ to php function '%s' failed\n", sFunName.c_str() );   \
    }                                                                                               \
    zval_ptr_dtor(&pFunctionName);



// ------------------------------------------------------------------------
// --- Helper templates to call PHP functions with different parameters ---
// ------------------------------------------------------------------------

template <typename RETTYPE>
RETTYPE callScriptFunction (
    std::string const& sFunName 	///< Name of (global/free) function to be called
)
{
    bool bOk = false;
    constexpr int params_count = 1;

    zval fn_name;
    ZVAL_STRINGL(&fn_name, sFunName.c_str(), sFunName.length());
    zval return_value;
    if ( call_user_function( CG(function_table ), NULL, &fn_name, &return_value, 0, NULL) != SUCCESS ) {
        bOk = true;
    }

    RETTYPE retval = getPhpRetVal<RETTYPE>( &return_value );
    return retval;
}



/** Call RETTYPE - (string) script function.
\return Returns the return value from the scriptfunction as a RETTYPE. */
template <typename RETTYPE>
RETTYPE callScriptFunction (
    std::string const& sFunName, 	///< Name of (global/free) function to be called
    std::string const& sParam 		///< Parameter to call with
)
{
    bool bOk = false;
    constexpr int params_count = 1;
    zval params[params_count];
    ZVAL_STRINGL(&params[0], sParam.c_str(), sParam.length());

    zval fn_name;
    ZVAL_STRINGL(&fn_name, sFunName.c_str(), sFunName.length());
    zval return_value;
    if ( call_user_function( CG(function_table ), NULL, &fn_name, &return_value, params_count, params) != SUCCESS ) {
        bOk = true;
    }

    RETTYPE retval = getPhpRetVal<RETTYPE>( &return_value );
    return retval;
}


/** Call RETTYPE - (string,string) script function.
\return Returns the return value from the scriptfunction as a string. */
template <typename RETTYPE>
RETTYPE	callScriptFunction (
     const std::string& sFunName
    ,const std::string& sParam1
    ,const std::string& sParam2
)
{
    bool bOk = false;
    constexpr int params_count = 2;
    zval params[params_count];
    ZVAL_STRINGL(&params[0], sParam1.c_str(), sParam1.length());
    ZVAL_STRINGL(&params[1], sParam2.c_str(), sParam2.length());

    zval fn_name;
    ZVAL_STRINGL(&fn_name, sFunName.c_str(), sFunName.length());
    zval return_value;
    if ( call_user_function( CG(function_table ), NULL, &fn_name, &return_value, params_count, params) != SUCCESS ) {
        bOk = true;
    }

    RETTYPE retval = getPhpRetVal<RETTYPE>( &return_value );
    return retval;
}


/** Call RETTYPE - (string,string,string) script function.
\return Returns the return value from the scriptfunction as a string. */
template <typename RETTYPE>
RETTYPE	callScriptFunction	(
    const std::string& sFunName,
    const std::string& sParam1,
    const std::string& sParam2,
    const std::string& sParam3
)
{
    bool bOk = false;
    constexpr int params_count = 3;
    zval params[params_count];
    ZVAL_STRINGL(&params[0], sParam1.c_str(), sParam1.length());
    ZVAL_STRINGL(&params[1], sParam2.c_str(), sParam2.length());
    ZVAL_STRINGL(&params[2], sParam3.c_str(), sParam3.length());

    zval fn_name;
    ZVAL_STRINGL(&fn_name, sFunName.c_str(), sFunName.length());
    zval return_value;
    if ( call_user_function( CG(function_table ), NULL, &fn_name, &return_value, params_count, params) != SUCCESS ) {
        bOk = true;
    }

    RETTYPE retval = getPhpRetVal<RETTYPE>( &return_value );
    return retval;
}




/** Call RETTYPE - (string,string,string,string) script function.
\return Returns the return value from the scriptfunction as a string. */
template <typename RETTYPE>
RETTYPE	callScriptFunction	(
    const std::string& sFunName,
    const std::string& sParam1,
    const std::string& sParam2,
    const std::string& sParam3,
    const std::string& sParam4
)
{
    bool bOk = false;
    constexpr int params_count = 4;
    zval params[params_count];
    ZVAL_STRINGL(&params[0], sParam1.c_str(), sParam1.length());
    ZVAL_STRINGL(&params[1], sParam2.c_str(), sParam2.length());
    ZVAL_STRINGL(&params[2], sParam3.c_str(), sParam3.length());
    ZVAL_STRINGL(&params[3], sParam4.c_str(), sParam4.length());

    zval fn_name;
    ZVAL_STRINGL(&fn_name, sFunName.c_str(), sFunName.length());
    zval return_value;
    if ( call_user_function( CG(function_table ), NULL, &fn_name, &return_value, params_count, params) != SUCCESS ) {
        bOk = true;
    }

    RETTYPE retval = getPhpRetVal<RETTYPE>( &return_value );
    return retval;
}


// --------------------------------------
// --- Non templated public functions ---
// --------------------------------------

/** Call void - (void) script function. */
void
phpCallScriptFunction_Void (
    std::string const& sFunName 	///< Name of (global/free) function to be called
)
{
    constexpr int params_count = 1;

    zval fn_name;
    ZVAL_STRINGL(&fn_name, sFunName.c_str(), sFunName.length());
    zval return_value;
    if ( call_user_function( CG(function_table ), NULL, &fn_name, &return_value, 0, NULL) != SUCCESS ) {
    }
}


void
phpCallScriptFunction_Void (
    std::string const& sFunName, 	///< Name of (global/free) function to be called
    std::string const& sParam 		///< Parameter to call with
)
{
    constexpr int params_count = 1;
    zval params[params_count];
    ZVAL_STRINGL(&params[0], sParam.c_str(), sParam.length());

    zval fn_name;
    ZVAL_STRINGL(&fn_name, sFunName.c_str(), sFunName.length());
    zval return_value;
    if ( call_user_function( CG(function_table ), NULL, &fn_name, &return_value, params_count, params) != SUCCESS ) {
    }
}


/** Call long - (void) script function.
\return Returns the return value from the scriptfunction as a long. */
long
phpCallScriptFunction_Long (
    std::string const& sFunName 	///< Name of (global/free) function to be called
)
{
    return callScriptFunction<long>( sFunName );
}


/** Call double - (void) script function.
\return Returns the return value from the scriptfunction as a double. */
double
phpCallScriptFunction_Double (
    std::string const& sFunName 	///< Name of (global/free) function to be called
)
{
    return callScriptFunction<double>( sFunName );
}

/** Call double - (string) script function.
\return Returns the return value from the scriptfunction as a double. */
double
phpCallScriptFunction_Double (
    std::string const& sFunName, 	///< Name of (global/free) function to be called
    std::string const& sParam 		///< Parameter to call with
)
{
    return callScriptFunction<double>( sFunName, sParam );
}

/** Call double - (string) script function.
\return Returns the return value from the scriptfunction as a double. */
double
phpCallScriptFunction_Double (
    std::string const& sFunName, 	///< Name of (global/free) function to be called
    std::string const& sParam1, 	///< Parameter1 to call with
    std::string const& sParam2 		///< Parameter2 to call with
)
{
    return callScriptFunction<double>( sFunName, sParam1, sParam2 );
}


/** Call bool - (void) script function.
\return Returns the return value from the scriptfunction as a bool. */
bool
phpCallScriptFunction_Bool (
    std::string const& sFunName 	///< Name of (global/free) function to be called
)
{
    return callScriptFunction<bool>( sFunName );
}


/** Call bool - (string) script function.
\return Returns the return value from the scriptfunction as a bool. */
bool
phpCallScriptFunction_Bool (
     std::string const& sFunName 	///< Name of (global/free) function to be called
    ,const std::string& sParam
)
{
    return callScriptFunction<bool>( sFunName, sParam );
}



/** Call bool - (string,string) script function.
\return Returns the return value from the scriptfunction as a bool. */
bool
phpCallScriptFunction_Bool (
     const std::string& sFunName
    ,const std::string& sParam1
    ,const std::string& sParam2
)
{
    return callScriptFunction<bool>( sFunName, sParam1, sParam2 );
}


/** Call bool - (string,string,string) script function.
\return Returns the return value from the scriptfunction as a bool. */
bool
phpCallScriptFunction_Bool (
     const std::string& sFunName
    ,const std::string& sParam1
    ,const std::string& sParam2
    ,const std::string& sParam3
)
{
    return callScriptFunction<bool>( sFunName, sParam1, sParam2, sParam3 );
}


bool
phpCallScriptFunction_Bool (
     const std::string& sFunName
    ,const std::string& sParam1
    ,const std::string& sParam2
    ,const std::string& sParam3
    ,const std::string& sParam4
)
{
    return callScriptFunction<bool>( sFunName, sParam1, sParam2, sParam3, sParam4 );
}


/** Call string - (void) script function.
!Syntax
|| int call_user_function_ex( HashTable*, zval**, zval*, zval**, zend_uint, zval***, int, HashTable* );
\see http://www.phpfreaks.com/forums/index.php?action=printpage;topic=10272.0
\return Returns the return value from the scriptfunction as a string. */
std::string
phpCallScriptFunction_String (
    std::string const& sFunName 	///< Name of (global/free) function to be called
)
{
    return callScriptFunction<std::string>( sFunName );
}



/** Call string - (string) script function.
\return Returns the return value from the scriptfunction as a string. */
std::string
phpCallScriptFunction_String	(
     const std::string& sFunName
    ,const std::string& sParam
)
{
    return callScriptFunction<std::string>( sFunName, sParam );
}


/** Call string - (string,string) script function.
\return Returns the return value from the scriptfunction as a string. */
std::string
phpCallScriptFunction_String	(
     const std::string& sFunName
    ,const std::string& sParam1
    ,const std::string& sParam2
)
{
    return callScriptFunction<std::string>( sFunName, sParam1, sParam2 );
}


/** Call string - (string,string,string) script function.
\return Returns the return value from the scriptfunction as a string. */
std::string
phpCallScriptFunction_String	(
    const std::string& sFunName,
    const std::string& sParam1,
    const std::string& sParam2,
    const std::string& sParam3
)
{
    return callScriptFunction<std::string>( sFunName, sParam1, sParam2, sParam3 );
}




/** Call string - (string,string,string,string) script function.
\return Returns the return value from the scriptfunction as a string. */
std::string
phpCallScriptFunction_String	(
    const std::string& sFunName,
    const std::string& sParam1,
    const std::string& sParam2,
    const std::string& sParam3,
    const std::string& sParam4
)
{
    return callScriptFunction<std::string>( sFunName, sParam1, sParam2, sParam3, sParam4 );
}


/** Call boost::any - (void) script function.
!Syntax
|| int call_user_function_ex( HashTable*, zval**, zval*, zval**, zend_uint, zval***, int, HashTable* );
\see http://www.phpfreaks.com/forums/index.php?action=printpage;topic=10272.0
\return Returns the return value from the scriptfunction as a boost::any. */
boost::any
phpCallScriptFunction_Any (
    std::string const& sFunName 	///< Name of (global/free) function to be called
)
{
    return callScriptFunction<boost::any>( sFunName );
}


void phpVarSet ( const std::string& sName, const std::string& sValue	)
{
//    zval* type;
//    ALLOC_INIT_ZVAL(type);
//    ZVAL_STRING(type, sValue.c_str(), 1)

//    char szType[2048];
//    strcpy(szType, sName.c_str() );
//    ZEND_SET_SYMBOL (&EG(symbol_table), szType, type )
}




std::string
getXulRunnerPathFromPhpIni ()
{
    namespace fs = boost::filesystem;
    fs::path xulPath("");
    if ( !sapi_module.php_ini_path_override ) return xulPath.string();

    fs::path iniPath( sapi_module.php_ini_path_override );
    iniPath /= "php.ini";
    printf( "INFO: php.ini path: %s\n", iniPath.string().c_str() );
    std::string sLine;
    fs::ifstream iniFile ( iniPath );
    if ( iniFile.is_open() )
    {
        while (! iniFile.eof() )
        {
            getline (iniFile,sLine);
            if ( boost::algorithm::contains( sLine, "xul_runner_path" ) ) {
                cpaf::StringVecT vec = cpaf::splitv( sLine, "=" );
                std::string sPath = boost::algorithm::trim_copy( vec[1] ) ;
                boost::algorithm::erase_all ( sPath, "\"" );
                xulPath = fs::path( boost::algorithm::trim_copy(sPath) );

            }
        }
        iniFile.close();
    }
    return xulPath.string();
}

