
#if WEBBROWSE_ENABLE_WX
#	include <hacks/wx_h_include_hack.h>
#endif //#if WEBBROWSE_ENABLE_GTK

#include <iostream>
#include <boost/algorithm/string.hpp>

#include <nsILocalFile.h>
#include <nsXPCOMGlue.h>
#include <nsXULAppAPI.h>
#include <nsIBaseWindow.h>
#include <nsIDocShellTreeItem.h>
#include <nsIWidget.h>
#include <nsIWebNavigation.h>
#include <cpaf_session.h>
#include "webbrowse_embedding_utils.h"

#include <utils/mozilla_strings.h>

#define FF4 1

#ifdef FF4
	XRE_InitEmbedding2Type	XRE_InitEmbedding2;
	XRE_TermEmbeddingType	XRE_TermEmbedding;
#else
	XRE_InitEmbeddingType XRE_InitEmbedding;
	XRE_TermEmbeddingType XRE_TermEmbedding;
#endif

/** Initialize XulRunner. */
nsresult
initXulrunner()
{
	namespace fs = boost::filesystem;
	return initXulrunner( fs::path( XULRUNNER_SDK_MAIN_LIB ) );
}


/** Initialize XulRunner using designated path. */
nsresult initXulrunner(
	std::string const&  sXulPath,	///< [in] Path to XulRunner directory
	std::string const& sEnvVar		///< [in] Enviroment var to check
)
{
	namespace fs = boost::filesystem;
	return initXulrunner( fs::path(sXulPath), sEnvVar );
}

/** Initialize XulRunner using designated path. */
nsresult initXulrunner(
	boost::filesystem::path xulPath,	///< [in] Path to XulRunner directory
	std::string const& sEnvVar			///< [in] Enviroment var to check
)
{
	printf ("xulPath: %s\n", xulPath.string().c_str() );
	namespace fs = boost::filesystem;
	if ( xulPath.empty() && !sEnvVar.empty() ) {
		std::string sXulPath = cpaf::system::get_env( sEnvVar );
		printf( "sEnvVar: %s, sXulPath: %s", sEnvVar.c_str(), sXulPath.c_str() );
	}
	if ( xulPath.empty() ) xulPath = fs::path(XULRUNNER_SDK_MAIN_LIB);

	nsresult rv;
#ifdef FF4
	nsCOMPtr<nsILocalFile> libxul;
	nsDynamicFunctionLoad nsFuncs[] = {
		{"XRE_InitEmbedding2", (NSFuncPtr*)&XRE_InitEmbedding2},
		{"XRE_TermEmbedding", (NSFuncPtr*)&XRE_TermEmbedding},
		{0, 0}
	};
#else
	nsCOMPtr<nsILocalFile> libxul;
	nsDynamicFunctionLoad nsFuncs[] = {
		{"XRE_InitEmbedding", (NSFuncPtr*)&XRE_InitEmbedding},
		{"XRE_TermEmbedding", (NSFuncPtr*)&XRE_TermEmbedding},
		{0, 0}
	};
#endif

	fs::path xpComPath;
#ifdef _WINDOWS
	xpComPath = xulPath / fs::path("xpcom.dll");
#else
	xpComPath = xulPath / fs::path("libxpcom.so");
#endif
	printf( "INFO: XUL_RUNNER_PATH: %s\n", xpComPath.string().c_str() );
    rv = XPCOMGlueStartup( xpComPath.string().c_str() );
	//native_file_string()
	if (NS_FAILED(rv))
		printf( "Error: XPCOMGlueStartup\n" );

	rv = XPCOMGlueLoadXULFunctions(nsFuncs);
	if (NS_FAILED(rv)) {
		printf( "Error: XPCOMGlueLoadXULFunctions\n" );
	}
#ifdef _WINDOWS
	std::string sXulPath = xulPath.string();
    boost::algorithm::replace_all( sXulPath, std::string("/"), std::string("\\") );
    rv = NS_NewNativeLocalFile(nsCString( sXulPath.c_str() ), PR_FALSE, getter_AddRefs(libxul));
#else
    rv = NS_NewNativeLocalFile(nsCString( xulPath.native().c_str() ), PR_FALSE, getter_AddRefs(libxul));
#endif
	if (NS_FAILED(rv)) {
		printf( "Error: NS_NewNativeLocalFile: '%s'\n", xulPath.string().c_str());
	}

#ifdef FF4
	rv = XRE_InitEmbedding2( libxul, 0, 0 );
#else
	rv = XRE_InitEmbedding(libxul, 0, 0, 0, 0);
#endif

	if (NS_FAILED(rv)) {
		printf( "Error: XRE_InitEmbedding\n");
	}
    return NS_OK;
}



void shutdownXulrunner()
{
//	printf("shutdownXulrunner 1\n");
	XRE_TermEmbedding();
//	printf("shutdownXulrunner 2\n");
	XPCOMGlueShutdown();
//	printf("shutdownXulrunner 3\n");
}

nsresult	getPIDOMWindow (
	nsPIDOMWindow** aPIWin,
	nsCOMPtr<nsIWebBrowser> pIWebBrowser
)
{
	*aPIWin = nsnull;
	// get the content DOM window for that web browser
	nsCOMPtr<nsIDOMWindow> pIDomWindow;
	pIWebBrowser->GetContentDOMWindow ( getter_AddRefs ( pIDomWindow ) );
	if ( !pIDomWindow ) {
		printf("Error: MozBrowser::getPIDOMWindow 'GetContentDOMWindow' failed\n");
		return NS_ERROR_FAILURE;
	}

	// get the private DOM window
	nsCOMPtr<nsPIDOMWindow> pIDomWindowPrivate = do_QueryInterface ( pIDomWindow );
	// and the root window for that DOM window
	*aPIWin = pIDomWindowPrivate->GetPrivateRoot();

	if ( *aPIWin )
	{
		NS_ADDREF ( *aPIWin );
		return NS_OK;
	}
	return NS_ERROR_FAILURE;
}



#if WEBBROWSE_ENABLE_QT
#include <QtGui/QWidget>

nsresult
initNativeWindow (
	nsCOMPtr<nsIWebBrowser>			pIWebBrowser,
	nsCOMPtr<nsIWebBrowserChrome>	pIWebBrowserChrome,
	QWidget* 						pNativeContainerWindow,
	int 							iX,
	int 							iY,
	int 							iWidth,
	int 							iHeight
)
{
	nsresult rv;
	int iSizeX, iSizeY;
	iSizeX = pNativeContainerWindow->width();
	iSizeY = pNativeContainerWindow->height();

	printf( "1 widget handle: %d  : w,h: %d, %d\n", (int)pNativeContainerWindow->winId(), iSizeX, iSizeY );

	pIWebBrowser->SetContainerWindow ( pIWebBrowserChrome );
	printf( "2 widget handle: %d  : w,h: %d, %d\n", (int)pNativeContainerWindow->winId(), iSizeX, iSizeY );

	nsCOMPtr<nsIDocShellTreeItem> dsti = do_QueryInterface ( pIWebBrowser );
	printf( "3 widget handle: %d  : w,h: %d, %d\n", (int)pNativeContainerWindow->winId(), iSizeX, iSizeY );
	dsti->SetItemType ( nsIDocShellTreeItem::typeContentWrapper );
	printf( "4 widget handle: %d  : w,h: %d, %d\n", (int)pNativeContainerWindow->winId(), iSizeX, iSizeY );

	nsCOMPtr<nsIBaseWindow> pIBaseWindow = do_QueryInterface ( pIWebBrowser ) ;
#ifdef LINUX
	printf( "5 widget handle: %d  : w,h: %d, %d\n", (int)pNativeContainerWindow->winId(), iSizeX, iSizeY );
	rv = pIBaseWindow->InitWindow ( nsNativeWidget ( pNativeContainerWindow->winId() ), nsnull, 0, 0, iSizeX, iSizeY );
	printf( "6 widget handle: %d  : w,h: %d, %d\n", (int)pNativeContainerWindow->winId(), iSizeX, iSizeY );
#else
	rv = pIBaseWindow->InitWindow ( nsNativeWidget ( pNativeContainerWindow->GetHandle() ), nsnull, 0, 0, iSizeX, iSizeY );
#endif
	if ( NS_FAILED ( rv ) ) 	printf ( "Error: InitWindow QT\n" );
	printf( "7 widget handle: %d  : w,h: %d, %d\n", (int)pNativeContainerWindow->winId(), iSizeX, iSizeY );

	rv = pIBaseWindow->Create();
	printf( "8 widget handle: %d  : w,h: %d, %d\n", (int)pNativeContainerWindow->winId(), iSizeX, iSizeY );
	if ( NS_FAILED ( rv ) ) 	printf ( "Error: Create QT\n" );
	printf( "9 widget handle: %d  : w,h: %d, %d\n", (int)pNativeContainerWindow->winId(), iSizeX, iSizeY );
	rv = pIBaseWindow->SetVisibility ( PR_TRUE );
	printf( "10 widget handle: %d  : w,h: %d, %d\n", (int)pNativeContainerWindow->winId(), iSizeX, iSizeY );
	if ( NS_FAILED ( rv ) ) 	printf ( "Error: SetVisibility QT\n" );
	printf( "11 widget handle: %d  : w,h: %d, %d\n", (int)pNativeContainerWindow->winId(), iSizeX, iSizeY );
	rv =pIBaseWindow->SetPositionAndSize(0, 0, iSizeX, iSizeY, PR_TRUE);
	printf( "12 widget handle: %d  : w,h: %d, %d\n", (int)pNativeContainerWindow->winId(), iSizeX, iSizeY );
	if ( NS_FAILED ( rv ) ) 	printf ( "Error: SetPositionAndSize QT\n" );
	printf( "initNativeWindow QT Done OK\n" );
	return NS_OK;
}


#endif //#if WEBBROWSE_ENABLE_QT


#if WEBBROWSE_ENABLE_WX

nsresult
initNativeWindow (
	nsCOMPtr<nsIWebBrowser>			pIWebBrowser,
	nsCOMPtr<nsIWebBrowserChrome>	pIWebBrowserChrome,
	wxWindow* 						pNativeContainerWindow,
	int 							iX,
	int 							iY,
	int 							iWidth,
	int 							iHeight
)
{
	nsresult rv;
	int iSizeX, iSizeY;
	pNativeContainerWindow->GetSize ( &iSizeX, &iSizeY );


	pIWebBrowser->SetContainerWindow ( pIWebBrowserChrome );

	nsCOMPtr<nsIDocShellTreeItem> dsti = do_QueryInterface ( pIWebBrowser );
	dsti->SetItemType ( nsIDocShellTreeItem::typeContentWrapper );

	nsCOMPtr<nsIBaseWindow> pIBaseWindow = do_QueryInterface ( pIWebBrowser ) ;
#ifdef LINUX
	rv = pIBaseWindow->InitWindow ( nsNativeWidget ( pNativeContainerWindow->m_wxwindow ), nsnull, 0, 0, iSizeX, iSizeY );
#else
	rv = pIBaseWindow->InitWindow ( nsNativeWidget ( pNativeContainerWindow->GetHandle() ), nsnull, 0, 0, iSizeX, iSizeY );
#endif
	if ( NS_FAILED ( rv ) ) 	printf ( "Error: InitWindow\n" );

	rv = pIBaseWindow->Create();
	if ( NS_FAILED ( rv ) ) 	printf ( "Error: Create\n" );
	rv = pIBaseWindow->SetVisibility ( PR_TRUE );
	if ( NS_FAILED ( rv ) ) 	printf ( "Error: SetVisibility\n" );
	rv =pIBaseWindow->SetPositionAndSize(0, 0, iSizeX, iSizeY, PR_TRUE);
	if ( NS_FAILED ( rv ) ) 	printf ( "Error: SetPositionAndSize\n" );
// 	rv = pIBaseWindow->SetEnabled ( PR_TRUE );
// 	if ( NS_FAILED ( rv ) ) 	printf ( "Error: SetEnabled\n" );

// // 	nsCOMPtr<nsIWebNavigation> webNavigation;
// // 	webNavigation = do_QueryInterface ( pIWebBrowser );
// // 	rv = webNavigation->LoadURI ( NS_ConvertASCIItoUTF16 ( "file:///home/ml/code/cpaf/cul/boost/doc/html/index.html" ).get(),nsIWebNavigation::LOAD_FLAGS_NONE, 0, 0, 0 );
// // 	if ( NS_FAILED ( rv ) ) 	printf ( "Error: LoadURI\n" );
	return NS_OK;
}


#endif //#if WEBBROWSE_ENABLE_WX


#if WEBBROWSE_ENABLE_GTK

nsresult
initNativeWindow (
	nsCOMPtr<nsIWebBrowser>			pIWebBrowser,
	nsCOMPtr<nsIWebBrowserChrome>	pIWebBrowserChrome,
	GtkWidget* 						pNativeContainerWindow,
	int 							iX,
	int 							iY,
	int 							iWidth,
	int 							iHeight
)
{
	nsresult rv;
	pIWebBrowser->SetContainerWindow ( pIWebBrowserChrome );

	nsCOMPtr<nsIDocShellTreeItem> dsti = do_QueryInterface ( pIWebBrowser );
	dsti->SetItemType ( nsIDocShellTreeItem::typeContentWrapper );

	nsCOMPtr<nsIBaseWindow> pIBaseWindow = do_QueryInterface ( pIWebBrowser ) ;
#ifdef LINUX
	rv = pIBaseWindow->InitWindow ( nsNativeWidget ( pNativeContainerWindow ), nsnull, iX, iY, iWidth, iHeight );
#else
#error Implement correct here InitWindow
//	rv = pIBaseWindow->InitWindow ( nsNativeWidget ( pNativeContainerWindow->GetHWND() ), nsnull, 0, 0, sizex, sizey );
#endif
	if ( NS_FAILED ( rv ) ) 	printf ( "Error: InitWindow\n" );

	rv = pIBaseWindow->Create();
	if ( NS_FAILED ( rv ) ) 	printf ( "Error: Create\n" );
	rv = pIBaseWindow->SetVisibility ( PR_TRUE );
	if ( NS_FAILED ( rv ) ) 	printf ( "Error: SetVisibility\n" );
	rv =pIBaseWindow->SetPositionAndSize(0, 0, iWidth, iHeight, PR_TRUE);
	if ( NS_FAILED ( rv ) ) 	printf ( "Error: SetPositionAndSize\n" );
// 	rv = pIBaseWindow->SetEnabled ( PR_TRUE );
// 	if ( NS_FAILED ( rv ) ) 	printf ( "Error: SetEnabled\n" );
	nsCOMPtr<nsIWebNavigation> webNavigation;
	webNavigation = do_QueryInterface ( pIWebBrowser );
	rv = webNavigation->LoadURI ( NS_ConvertASCIItoUTF16 ( "http://www.tv2.dk" ).get(),nsIWebNavigation::LOAD_FLAGS_NONE, 0, 0, 0 );
	if ( NS_FAILED ( rv ) ) 	printf ( "Error: LoadURI\n" );
	return NS_OK;
}


#endif //#if WEBBROWSE_ENABLE_GTK

