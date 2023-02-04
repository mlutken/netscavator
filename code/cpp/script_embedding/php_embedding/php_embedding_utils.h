#ifndef _PHP_EMBEDDING_UTILS_H_
#define _PHP_EMBEDDING_UTILS_H_

// -------------------
// --- C interface ---
// -------------------

extern "C" {

void startupPhp                 ( const char* szPhpIniPath );
void startupPhpScript           ( const char* szPhpIniPath, int argc, char* argv[] );
void shutdownPhp                ();
void executePhpFile             ( const char* szFileName  );
void executePhpString           ( const char* szPhpCode   );
void setMinerPointerRaw         ( void* pMiner );
void iniFileAddIncludePath      ( const char* szIncludePath );
bool phpFunctionExists          ( const char *szFunctionName, int nameLenght );


void executePhpFileCharPtr      ( char* szFileName  );
void executePhpStringCharPtr    ( char* szPhpCode   );
int php_cli_test4               ( int argc, char* argv[] );
void testPhpNoMiner             ();

}


// ---------------------
// --- C++ interface ---
// ---------------------

#include <string>
#include <QString>

bool phpFunctionExists          ( const std::string& sFunctionName );
bool phpFunctionExists          ( const QString& sFunctionName );

#endif // _PHP_EMBEDDING_UTILS_H_
