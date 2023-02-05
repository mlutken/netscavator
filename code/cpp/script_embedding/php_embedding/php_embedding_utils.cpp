#include <string>
#include "php_embedding_utils.h"
#include <stdio.h>
#include <string.h>

#include <sapi/embed/php_embed.h>

#include "php_embedding_callbacks.h"

//https://www.phpinternalsbook.com/php7/extensions_design/zend_extensions.html

using namespace std;
 
#ifdef ZTS
    void*** tsrm_ls;
#endif


// -------------------
// --- C interface ---
// -------------------


//// TODO: Seems to cause crash in release builds
//static void phpVarSet ( const std::string& sName, const std::string& sValue	)
//{
//    zval* type;
//    ALLOC_INIT_ZVAL(type);
//    ZVAL_STRING(type, sValue.c_str(), 1);

//    char szType[2048];
//    strcpy(szType, sName.c_str() );
//    ZEND_SET_SYMBOL (&EG(symbol_table), szType, type );
//}

static int (*original_embed_startup)(struct _sapi_module_struct* sapi_module ) = NULL;
static int (*original_embed_shutdown)(struct _sapi_module_struct* sapi_module ) = NULL;

static bool g_phpRunning = false;

static int embed_startup_callback(struct _sapi_module_struct* sapi_module )
{
    /* Call original startup function first */
    if ( original_embed_startup(sapi_module) == FAILURE ) {
        return FAILURE;
    }
    int retval = SUCCESS;
    /* Calling the original embed_startup actually places us in the ACTIVATE stage
       rather than in the STARTUP stage, but we can still alter mos INI_SYSTEM and
       INI_PERDIR entries anyhow. */
    if ( g_phpEmbedCallbacks::Instance().startUpFun ) {
        retval = g_phpEmbedCallbacks::Instance().startUpFun( sapi_module );
    }
    return retval;
}

static int embed_shutdown_callback(struct _sapi_module_struct* sapi_module )
{
    int retval = SUCCESS;
    if ( g_phpEmbedCallbacks::Instance().shutDownFun ) {
        retval = g_phpEmbedCallbacks::Instance().shutDownFun( sapi_module );
        if (g_phpEmbedCallbacks::Instance().logToStdOut)
            fflush(stdout);
    }

    /* Call original shutdown function  */
    if ( original_embed_shutdown(sapi_module) == FAILURE ) {
        retval = FAILURE;
    }
    return retval;
}

static void embed_flush(void* server_context)
{
    if ( g_phpEmbedCallbacks::Instance().flushFun ) {
        g_phpEmbedCallbacks::Instance().flushFun( server_context );
        if (g_phpEmbedCallbacks::Instance().logToStdOut)
            fflush(stdout);
    }
    else {
		fflush(stdout);
    }
}

static size_t embed_ub_write( const char* str, size_t strLength )
{
    auto consumed = strLength;
    if ( g_phpEmbedCallbacks::Instance().writeFun ) {
        consumed = g_phpEmbedCallbacks::Instance().writeFun( str, strLength );
        if (g_phpEmbedCallbacks::Instance().logToStdOut)
            printf("%s\n", str );
    }
    else {
        printf("%s\n", str );
    }
    return consumed;
}

//static void embed_log_message( char* str )  // php-5.3.8
// char *message, int syslog_type_int
static void embed_log_message( const char* str, int syslog_type_int )  // php-5.4.9
{
    if ( g_phpEmbedCallbacks::Instance().logMsgFun ) {
        g_phpEmbedCallbacks::Instance().logMsgFun( str );
        if (g_phpEmbedCallbacks::Instance().logToStdOut)
            printf("%s\n", str );
    }
    else {
        printf("%s\n", str );
    }
}

	////void (*sapi_error)(int type, const char *error_msg, ...);

static void embed_error_message( int type, const char* error_msg, ... )  // php-5.3.8
{
    printf("ML: embed_error_message : Error[%d] %s", type, error_msg );
	

//    if ( g_phpEmbedCallbacks::Instance().logMsgFun ) {
//        g_phpEmbedCallbacks::Instance().logMsgFun( str );
//    }
//    else {
//        printf("%s", str );
////        fprintf( stderr, "%s\n", str );
//    }
}

void startupPhp( const char* szPhpIniPath )
{
    const char* szPhpIniPathConst = PHP_HARDCODED_INI_FILE_PATH;
    char  szPhpIniPathUse[2048];
    strcpy( szPhpIniPathUse, szPhpIniPath );
    if ( strcmp(szPhpIniPath, "" ) == 0 ) strcpy( szPhpIniPathUse, szPhpIniPathConst );

    char  szArgs[2][2048];

    strcpy( szArgs[0], "php_cli_test2" );
    strcpy( szArgs[1], "" );
    
    int ac = 1;
    char* av[2] =
    { szArgs[0], szArgs[1] };
    php_embed_module.php_ini_path_override = szPhpIniPathUse;

    if ( original_embed_startup == NULL )  original_embed_startup = php_embed_module.startup;  /*Save original startup */
    php_embed_module.startup = embed_startup_callback;
    if ( original_embed_shutdown == NULL )  original_embed_shutdown = php_embed_module.shutdown;  /*Save original shutdown */
    php_embed_module.shutdown= embed_shutdown_callback;

    php_embed_module.flush			= embed_flush;
    php_embed_module.ub_write		= embed_ub_write;
    php_embed_module.log_message	= embed_log_message;
    php_embed_module.sapi_error		= embed_error_message;
//    php_embed_init( ac, av PTSRMLS_CC );
    php_embed_init( ac, av);
    g_phpRunning = true;
}


void startupPhpScript (
          const char* szPhpIniPath
        , int argc, char* argv[]
        )
{
    const char* szPhpIniPathConst = PHP_HARDCODED_INI_FILE_PATH;
    char  szPhpIniPathUse[2048];
    strcpy( szPhpIniPathUse, szPhpIniPath );
    if ( strcmp(szPhpIniPath, "" ) == 0 ) strcpy( szPhpIniPathUse, szPhpIniPathConst );

    php_embed_module.php_ini_path_override = szPhpIniPathUse;

    if ( original_embed_startup == NULL )  original_embed_startup = php_embed_module.startup;  /*Save original startup */
    php_embed_module.startup = embed_startup_callback;
    if ( original_embed_shutdown == NULL )  original_embed_shutdown = php_embed_module.shutdown;  /*Save original shutdown */
    php_embed_module.shutdown= embed_shutdown_callback;

    php_embed_module.flush			= embed_flush;
    php_embed_module.ub_write		= embed_ub_write;
    php_embed_module.log_message	= embed_log_message;
    php_embed_module.sapi_error		= embed_error_message;
//    php_embed_init( argc, argv PTSRMLS_CC );
    php_embed_init( argc, argv);
    g_phpRunning = true;
}


void shutdownPhp()
{
    if ( true == g_phpRunning ) {
        php_embed_shutdown();
    }
    g_phpRunning = false;
}
 
void executePhpFile ( const char* szFileName )
{
    char szFile[512];
    strcpy(szFile, szFileName );
    executePhpFileCharPtr(szFile);
}


void executePhpString ( const char* szPhpCode )
{
    zend_first_try {
        char* szCode;
        spprintf( &szCode, 0, "%s", szPhpCode );
        zend_eval_string( szCode, NULL, szCode );
        efree ( szCode );
    } zend_end_try();
}

void setMinerPointerRaw ( void* pMiner )
{
    char szCode[256];
    sprintf(szCode, "currentMinerSetPointer('%ld');", (long)pMiner );
    executePhpString(szCode);
}

void iniFileAddIncludePath ( const char* szIncludePath )
{
    const char* szCurrentIncludePath = zend_ini_string( "include_path", sizeof("include_path"), 1 );
    char szNewIncludePath[4096];
    strcpy(szNewIncludePath, szCurrentIncludePath);
#ifdef _WINDOWS
    strcat(szNewIncludePath, ";");
#else
    strcat(szNewIncludePath, ":");
#endif
    strcat(szNewIncludePath, szIncludePath );
//    ZEND_API int zend_alter_ini_entry(zend_string *name, zend_string *new_value, int modify_type, int stage);

//    zend_string const_include_path;
//    zval include_path;
    zend_string* const_include_path = zend_string_init("include_path", strlen("include_path"), 0);
    zend_string* include_path = zend_string_init(szIncludePath, strlen(szIncludePath), 0);
//    ZVAL_STRING(&const_include_path, "include_path");
//    ZVAL_STRING(&include_path, szIncludePath);

    zend_alter_ini_entry( const_include_path, include_path, PHP_INI_SYSTEM, PHP_INI_STAGE_ACTIVATE );
//    zend_alter_ini_entry( "include_path", sizeof("include_path")
//                          , szNewIncludePath, strlen(szNewIncludePath)
//                          , PHP_INI_SYSTEM, PHP_INI_STAGE_ACTIVATE );
}


void executePhpFileCharPtr ( char* szFileName )
{
    zend_first_try {
        char* include_script;
        spprintf( &include_script, 0, "include '%s';", szFileName );
        zend_eval_string( include_script, NULL, szFileName );
        efree ( include_script );
    } zend_end_try();
}

void executePhpStringCharPtr ( char* szPhpCode )
{
    zend_first_try {
        char* szCode;
        spprintf( &szCode, 0, "%s", szPhpCode );
        zend_eval_string( szCode, NULL, szPhpCode );
        efree ( szCode );
    } zend_end_try();
}

int php_cli_test4(const char* szPhpIniPath, int argc, char* argv[])
{
    //std::string s1 = "";
    printf("php_cli_test4  XX \n" );
	if ( argc <= 1 ) {
		printf( "Usage: %s FILENAME\n", argv[0] );
		return -1;
	}
	
    startupPhp(szPhpIniPath);
	

    executePhpFile ( argv[1] );
	
    if ( argc > 2 ) {
        executePhpFile ( argv[2] );
    }

    printf("\n");
//    if (g_callFunc) {
//        printf("readScriptFunctions\n");
//        g_callFunc->readScriptFunctions();
//    }
	
//    string scriptFun = "simple_test2_fun";
//    if ( g_callFunc ) {
//        printf("CALL simple_test2_fun\n");
//       // g_callFunc->callScriptFunction_Void(scriptFun);
//    }

//    scriptFun = "simple_test5_fun";
//    if ( g_callFunc && g_callFunc->scriptFunctionExists(scriptFun) ) {
//        printf("CALL simple_test5_fun\n");
//        g_callFunc->callScriptFunction_Void(scriptFun);
//    }

    shutdownPhp();
		
	return 0;
}

void testPhpNoMiner (const char* szPhpIniPath)
{
//    std::cout << "Miner pointer: " << (unsigned long)m_pMiner.get() << " == " << sMinerPointer << std::endl;
//        std::string s = "currentMinerSetPointer('" + sMinerPointer + "');\n";
//    std::string s = "dbgCurrentMinerSetPointer('" + sMinerPointer + "');\n";
//    std::cout << "Set pointer call: " << s << std::endl;

    startupPhp(szPhpIniPath);
    executePhpFile("./crawler/_test/simple_test.php");
    executePhpString("printf (\"GED\\n\");");
    executePhpString("echo \"HEST\\n\";");
    //executePhpString(s);

    shutdownPhp();

}



static void stringCrashTest()
{
    std::string s1 = "";
}

void stringCrashTest2()
{
    stringCrashTest();
}




bool phpFunctionExists(const char *szFunctionName, int nameLenght)
{
    char *name;
    int name_len = nameLenght;
    zend_function *func;
    char *lcname;
    zend_bool retval;


    lcname = zend_str_tolower_dup(szFunctionName, name_len);

    /* Ignore leading "\" */
    name = lcname;
    if (lcname[0] == '\\') {
        name = &lcname[1];
        name_len--;
    }

//    retval = (zend_hash_find(EG(function_table), name, name_len+1, (void **)&func) == SUCCESS);
    zval* fun_name = zend_hash_str_find(EG(function_table), name, name_len+1);
    return fun_name != nullptr;

    efree(lcname);

    /*
     * A bit of a hack, but not a bad one: we see if the handler of the function
     * is actually one that displays "function is disabled" message.
     */
///    if (retval && func->type == ZEND_INTERNAL_FUNCTION &&
///        func->internal_function.handler == zif_display_disabled_function) {
///        retval = 0;
///    }

    ///RETURN_BOOL(retval);
    return retval != 0;
}

// ---------------------
// --- C++ interface ---
// ---------------------

bool phpFunctionExists(const string &sFunctionName)
{
    return phpFunctionExists(sFunctionName.c_str(), sFunctionName.length());
}

bool phpFunctionExists(const QString &sFunctionName)
{
    const QByteArray &name = sFunctionName.toUtf8();
    return phpFunctionExists(name.data(), name.size());
}
