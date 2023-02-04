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
    if ( Z_TYPE_P(pRetval) == IS_BOOL 	) 	bRetVal = static_cast<bool>(Z_BVAL_P(pRetval));
    if ( Z_TYPE_P(pRetval) == IS_LONG 	) 	bRetVal = static_cast<bool>(Z_LVAL_P(pRetval));
    if ( Z_TYPE_P(pRetval) == IS_DOUBLE ) 	bRetVal = static_cast<bool>(Z_DVAL_P(pRetval));
    if ( (Z_TYPE_P(pRetval) == IS_STRING) && pRetval->value.str.val ) {
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
    if ( (Z_TYPE_P(pRetval) == IS_STRING) && pRetval->value.str.val ) {	sRetVal = Z_STRVAL_P(pRetval);	}
    return sRetVal;
}


template <>
boost::any	getPhpRetVal<boost::any> 	( zval*	pRetval )
{
    boost::any anyRetVal;
    if ( Z_TYPE_P(pRetval) == IS_BOOL 	) 	anyRetVal = static_cast<bool>(Z_BVAL_P(pRetval));
    if ( Z_TYPE_P(pRetval) == IS_LONG 	) 	anyRetVal = static_cast<long>(Z_LVAL_P(pRetval));
    if ( Z_TYPE_P(pRetval) == IS_DOUBLE ) 	anyRetVal = static_cast<double>(Z_DVAL_P(pRetval));
    if ( (Z_TYPE_P(pRetval) == IS_STRING) && pRetval->value.str.val ) {
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
    ALLOC_INIT_ZVAL		( pFunctionName									);	\
    ZVAL_STRING			( pFunctionName, (char*)sFunName.c_str(), 1 	);
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
    CALL_PHP_FUN_BEGIN
    if ( call_user_function_ex( CG(function_table ), NULL, pFunctionName, &pRetval, 0, NULL, 0, NULL TSRMLS_CC ) != SUCCESS )
    { bOk = false; }

    RETTYPE retval = getPhpRetVal<RETTYPE>( pRetval );

    if ( true == bOk ) {
      zval_ptr_dtor(&pRetval);
    } else {
        printf("ERROR: RETTYPE callScriptFunction() Function call from C++ to php function '%s' failed\n", sFunName.c_str() );
    }
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
    CALL_PHP_FUN_BEGIN
    const int iParamCount = 1;
    zval**				params[iParamCount]; 		// Creates array of parameters with 1 element allocated.
    zval* 				pParamString;

    ALLOC_INIT_ZVAL		( pParamString									);
    ZVAL_STRING			( pParamString, (char*)sParam.c_str(), 1 		);
    params[0] = &pParamString; // Makes pParamString the first parameter to php function we are calling.

    if ( call_user_function_ex( CG(function_table ), NULL, pFunctionName, &pRetval, iParamCount, params, 0, NULL TSRMLS_CC ) != SUCCESS )
    { bOk = false; }

    RETTYPE retval = getPhpRetVal<RETTYPE>( pRetval );

    zval_ptr_dtor(&pParamString);

    if ( true == bOk ) {
      zval_ptr_dtor(&pRetval);
    } else {
        printf("ERROR: RETTYPE callScriptFunction(sParam) Function call from C++ to php function '%s' failed\n", sFunName.c_str() );
    }
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
    CALL_PHP_FUN_BEGIN
    const int iParamCount = 2;
    zval**				params[iParamCount]; 		// Creates array of parameters with 2 elements allocated.
    zval* 				pParamString1;
    zval* 				pParamString2;

    ALLOC_INIT_ZVAL		( pParamString1									);
    ZVAL_STRING			( pParamString1, (char*)sParam1.c_str(), 1 		);
    ALLOC_INIT_ZVAL		( pParamString2									);
    ZVAL_STRING			( pParamString2, (char*)sParam2.c_str(), 1 		);
    params[0] = &pParamString1;
    params[1] = &pParamString2;

    if ( call_user_function_ex( CG(function_table ), NULL, pFunctionName, &pRetval, iParamCount, params, 0, NULL TSRMLS_CC) != SUCCESS )
    { bOk = false; }

    RETTYPE retval = getPhpRetVal<RETTYPE>( pRetval );

    zval_ptr_dtor(&pParamString1);
    zval_ptr_dtor(&pParamString2);
    if ( true == bOk ) {
      zval_ptr_dtor(&pRetval);
    } else {
        printf("ERROR: RETTYPE callScriptFunction(sParam1, sParam2) Function call from C++ to php function '%s' failed\n", sFunName.c_str() );
    }
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
    CALL_PHP_FUN_BEGIN
    const int iParamCount = 3;
    zval**				params[iParamCount]; 		// Creates array of parameters with 3 elements allocated.
    zval* 				pParamString1;
    zval* 				pParamString2;
    zval* 				pParamString3;

    ALLOC_INIT_ZVAL		( pParamString1									);
    ZVAL_STRING			( pParamString1, (char*)sParam1.c_str(), 1 		);
    ALLOC_INIT_ZVAL		( pParamString2									);
    ZVAL_STRING			( pParamString2, (char*)sParam2.c_str(), 1 		);
    ALLOC_INIT_ZVAL		( pParamString3									);
    ZVAL_STRING			( pParamString3, (char*)sParam3.c_str(), 1 		);
    params[0] = &pParamString1;
    params[1] = &pParamString2;
    params[2] = &pParamString3;

    if ( call_user_function_ex( CG(function_table ), NULL, pFunctionName, &pRetval, iParamCount, params, 0, NULL TSRMLS_CC ) != SUCCESS )
    { bOk = false; }

    RETTYPE retval = getPhpRetVal<RETTYPE>( pRetval );

    zval_ptr_dtor(&pParamString1);
    zval_ptr_dtor(&pParamString2);
    zval_ptr_dtor(&pParamString3);
    if ( true == bOk ) {
      zval_ptr_dtor(&pRetval);
    } else {
        printf("ERROR: RETTYPE callScriptFunction(sParam1, sParam2, sParam3) Function call from C++ to php function '%s' failed\n", sFunName.c_str() );
    }
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
    CALL_PHP_FUN_BEGIN
    const int iParamCount = 4;
    zval**				params[iParamCount]; 		// Creates array of parameters with 4 elements allocated.
    zval* 				pParamString1;
    zval* 				pParamString2;
    zval* 				pParamString3;
    zval* 				pParamString4;

    ALLOC_INIT_ZVAL		( pParamString1									);
    ZVAL_STRING			( pParamString1, (char*)sParam1.c_str(), 1 		);
    ALLOC_INIT_ZVAL		( pParamString2									);
    ZVAL_STRING			( pParamString2, (char*)sParam2.c_str(), 1 		);
    ALLOC_INIT_ZVAL		( pParamString3									);
    ZVAL_STRING			( pParamString3, (char*)sParam3.c_str(), 1 		);
    ALLOC_INIT_ZVAL		( pParamString4									);
    ZVAL_STRING			( pParamString4, (char*)sParam4.c_str(), 1 		);
    params[0] = &pParamString1;
    params[1] = &pParamString2;
    params[2] = &pParamString3;
    params[3] = &pParamString4;

    if ( call_user_function_ex( CG(function_table ), NULL, pFunctionName, &pRetval, iParamCount, params, 0, NULL TSRMLS_CC ) != SUCCESS )
    { bOk = false; }

    RETTYPE retval = getPhpRetVal<RETTYPE>( pRetval );

    zval_ptr_dtor(&pParamString1);
    zval_ptr_dtor(&pParamString2);
    zval_ptr_dtor(&pParamString3);
    zval_ptr_dtor(&pParamString4);
    if ( true == bOk ) {
      zval_ptr_dtor(&pRetval);
    } else {
        printf("ERROR: RETTYPE callScriptFunction(sParam1, sParam2, sParam3, sParam4) Function call from C++ to php function '%s' failed\n", sFunName.c_str() );
    }
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
    CALL_PHP_FUN_BEGIN
    if ( call_user_function_ex( CG(function_table ), NULL, pFunctionName, &pRetval, 0, NULL, 0, NULL TSRMLS_CC ) != SUCCESS )		\
    { bOk = false; }

    if ( true == bOk ) {
      zval_ptr_dtor(&pRetval);
    } else {
        printf("ERROR: void callScriptFunction() Function call from C++ to php function '%s' failed\n", sFunName.c_str() );
    }
}


void
phpCallScriptFunction_Void (
    std::string const& sFunName, 	///< Name of (global/free) function to be called
    std::string const& sParam 		///< Parameter to call with
)
{
    CALL_PHP_FUN_BEGIN
    const int iParamCount = 1;
    zval**				params[iParamCount]; 		// Creates array of parameters with 1 element allocated.
    zval* 				pParamString;

    ALLOC_INIT_ZVAL		( pParamString									);
    ZVAL_STRING			( pParamString, (char*)sParam.c_str(), 1 		);
    params[0] = &pParamString; // Makes pParamString the first parameter to php function we are calling.

    if ( call_user_function_ex( CG(function_table ), NULL, pFunctionName, &pRetval, iParamCount, params, 0, NULL TSRMLS_CC ) != SUCCESS )
    { bOk = false; }


    zval_ptr_dtor(&pParamString);
    if ( true == bOk ) {
      zval_ptr_dtor(&pRetval);
    } else {
        printf("ERROR: void callScriptFunction(sParam1) Function call from C++ to php function '%s' failed\n", sFunName.c_str() );
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

