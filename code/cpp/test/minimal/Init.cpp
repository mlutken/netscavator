#include <stdlib.h>
#include <string>
#include <boost/algorithm/string.hpp>
//#include <boost/cstdtypes.hpp>

#include "nsCOMPtr.h"
#include "nsEmbedString.h"
#include "nsILocalFile.h"
#include "nsXPCOMGlue.h" 
#include "nsXULAppAPI.h"

#include "Init.h"

XRE_InitEmbeddingType XRE_InitEmbedding;
XRE_TermEmbeddingType XRE_TermEmbedding; 

nsresult init_xulrunner(const char* xul_dir, const char* app_dir)
{
    nsresult rv;

//     char xpcom_dll[_MAX_PATH ];
//     if(strlen(xul_dir) >= _MAX_PATH) {
//         return NS_ERROR_FAILURE;
//     }
//     strcpy(xpcom_dll, xul_dir);
//     strncat(xpcom_dll, "\\xpcom.dll", _MAX_PATH - strlen(xpcom_dll));
// 
//     rv = XPCOMGlueStartup(xpcom_dll);
//     if (NS_FAILED(rv)) {
//         printf("GLUE STARTUP FAILED\n");
//         return rv;
//     }

#ifdef _WINDOWS
	rv = XPCOMGlueStartup( XULRUNNER_SDK_MAIN_LIB  "xpcom.dll" );
#else
	rv = XPCOMGlueStartup( XULRUNNER_SDK_MAIN_LIB  "libxpcom.so" );	// Assume Unix system for now
#endif 
	if (NS_FAILED(rv))	printf("Error: XPCOMGlueStartup\n");
    
    const nsDynamicFunctionLoad dynamicSymbols[] = {
        { "XRE_InitEmbedding", (NSFuncPtr*) &XRE_InitEmbedding },
        { "XRE_TermEmbedding", (NSFuncPtr*) &XRE_TermEmbedding },
        { nsnull, nsnull }
    }; 
    XPCOMGlueLoadXULFunctions(dynamicSymbols);

    nsCOMPtr<nsILocalFile> xul_dir_file;
    rv = NS_NewNativeLocalFile(nsEmbedCString(xul_dir), PR_FALSE,
            getter_AddRefs(xul_dir_file));
    NS_ENSURE_SUCCESS(rv, rv);

    nsCOMPtr<nsILocalFile> app_dir_file;
    rv = NS_NewNativeLocalFile(nsEmbedCString(app_dir), PR_FALSE,
                getter_AddRefs(app_dir_file));
    NS_ENSURE_SUCCESS(rv, rv);

    rv = XRE_InitEmbedding(xul_dir_file, app_dir_file, 0, 0, 0);
    NS_ENSURE_SUCCESS(rv, rv);
    printf("Init OK 1\n");
    return NS_OK;
}


nsresult init_xulrunner()
{
	printf("ML: init_xulrunner() XULRUNNER_SDK_MAIN_LIB: %s\n", XULRUNNER_SDK_MAIN_LIB );
    nsresult rv;
	std::string sXulRunnerSdkMainLib( XULRUNNER_SDK_MAIN_LIB );	// For NS_NewNativeLocalFile, XRE_InitEmbedding

	nsCOMPtr<nsILocalFile> libxul;
	nsDynamicFunctionLoad nsFuncs[] = {
			{"XRE_InitEmbedding", (NSFuncPtr*)&XRE_InitEmbedding},
			{"XRE_TermEmbedding", (NSFuncPtr*)&XRE_TermEmbedding},
			{0, 0}
	}; 
	 
#ifdef _WINDOWS
	rv = XPCOMGlueStartup( XULRUNNER_SDK_MAIN_LIB  "xpcom.dll" );
	boost::replace_all(sXulRunnerSdkMainLib, "/", "\\");      // Use backslashes on Windows
#else
	rv = XPCOMGlueStartup( XULRUNNER_SDK_MAIN_LIB  "libxpcom.so" );	// Assume Unix system for now
#endif 
	if (NS_FAILED(rv))	printf("Error: XPCOMGlueStartup\n");
	
	rv = XPCOMGlueLoadXULFunctions(nsFuncs);
	if (NS_FAILED(rv)) 	printf("Error: XPCOMGlueLoadXULFunctions\n");
	
	printf ("XULRUNNER_SDK_MAIN_LIB: " XULRUNNER_SDK_MAIN_LIB "\n");

	
//	rv = NS_NewNativeLocalFile(nsEmbedCString( XULRUNNER_SDK_MAIN_LIB ), PR_FALSE, getter_AddRefs(libxul));
//	rv = NS_NewNativeLocalFile(nsEmbedCString( "C:\\code\\veriquin\\code\\cpp\\3rdparty\\xulrunner\\windows\\xulrunner\\" ), PR_FALSE, getter_AddRefs(libxul));
	rv = NS_NewNativeLocalFile(nsEmbedCString( sXulRunnerSdkMainLib.c_str() ), PR_FALSE, getter_AddRefs(libxul));
	// NOTE: Important with the slashes here !!!!
		
	if (NS_FAILED(rv))	printf("Error: NS_NewNativeLocalFile\n");
	
	rv = XRE_InitEmbedding(libxul, 0, 0, 0, 0);
	if (NS_FAILED(rv)) printf("Error: XRE_InitEmbedding\n");
    printf("Init OK 2\n");
    return NS_OK;
}

	

void shutdown_xulrunner()
{
    XRE_TermEmbedding();
    XPCOMGlueShutdown();
}
