

#include <stdio.h>

// int main()
// {
// 	printf("DDDDDDDDD\n");
// }

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <gtk/gtk.h>
#include "xpcom-config.h"
#include "nsXPCOMGlue.h"
#include "nsDebug.h"
#include "nsCOMPtr.h"
#include "nsIBaseWindow.h"
#include "nsILocalFile.h"
#include "nsIWebBrowser.h"
#include "nsIWebNavigation.h"
#include "nsEmbedCID.h"
#include "nsEmbedString.h"
#include "nsXULAppAPI.h"
#include "nsComponentManagerUtils.h"
#include "nsIDocShellTreeItem.h"
#include "nsISupportsUtils.h"

//#include "MyEmbedWindow.h"

#include "Init.h"
#include "MiroBrowserEmbed.h"


// XRE_InitEmbeddingType XRE_InitEmbedding;
// XRE_TermEmbeddingType XRE_TermEmbedding;

//BeginReading

static gboolean delete_event( GtkWidget *widget, GdkEvent *event,
gpointer data ) {
		gtk_main_quit();
		return FALSE;

}

int main(int argc, char** argv) {
	printf("Simple Mozilla Gtk+  embedding example Mapzter.\n");
	
	nsresult rv;
	GtkWidget* window;
//	GtkWindow* pMainWin;
	nsCOMPtr<nsIBaseWindow> baseWindow;
	nsCOMPtr<nsIWebBrowser> webBrowser;
	nsCOMPtr<nsIWebNavigation> webNavigation;

	gtk_init (&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
//	pMainWin = gtk_widget_get_parent_window (window) ;
//	gtk_window_set_default_size (window, 400, 600);
	gtk_widget_show(window);


	init_xulrunner();
	webBrowser = do_CreateInstance(NS_WEBBROWSER_CONTRACTID, &rv);
	if (NS_FAILED(rv)) printf("Error: do_CreateInstance webBrowser\n");


	MiroBrowserEmbed* pChrome = new MiroBrowserEmbed();
	//pChrome->AddRef();
	pChrome->init(window, 0, 0, 1024, 800 );

/*	printf("ML: BEFORE: SetContainerWindow\n ");
    webBrowser->SetContainerWindow(static_cast<nsIWebBrowserChrome*>(pChrome));
    nsCOMPtr<nsIDocShellTreeItem> dsti = do_QueryInterface(webBrowser);
    dsti->SetItemType(nsIDocShellTreeItem::typeContentWrapper);
	printf("ML: AFTER: SetContainerWindow\n ");

	baseWindow = do_QueryInterface(webBrowser);
	rv = baseWindow->InitWindow(window, 0, 0, 0, 1024, 800);
	if (NS_FAILED(rv)) printf("Error: InitWindow\n");

	rv = baseWindow->Create();
	if (NS_FAILED(rv)) 	printf("Error: Create\n");

	rv =baseWindow->SetVisibility(PR_TRUE);
	if (NS_FAILED(rv)) 	printf("Error: SetVisibility\n");

	rv =baseWindow->SetEnabled(PR_TRUE);
	if (NS_FAILED(rv)) 	printf("Error: SetEnabled\n");
	
	webNavigation = do_QueryInterface(webBrowser);
	rv = webNavigation->LoadURI(NS_ConvertASCIItoUTF16("http://www.dr.dk").get(),nsIWebNavigation::LOAD_FLAGS_NONE, 0, 0, 0);
	if (NS_FAILED(rv)) 	printf("Error: LoadURI\n");*/
	
	g_signal_connect(G_OBJECT(window), "delete_event",G_CALLBACK(delete_event), 0);
	gtk_main();

//	pChrome->Release(); // Segfaults ...
	delete pChrome;
	shutdown_xulrunner();

	printf("exit...\n");
	

//	XRE_TermEmbedding();
//	XPCOMGlueShutdown();
	return 0;
}

#if 0

int main(int argc, char** argv) {
	printf("Simple Mozilla Gtk+  embedding example Mapzter.\n");
	
	GtkWidget *window;
	nsCOMPtr<nsIBaseWindow> baseWindow;
	nsCOMPtr<nsIWebBrowser> webBrowser;
	nsCOMPtr<nsILocalFile> libxul;
	nsCOMPtr<nsIWebNavigation> webNavigation;
	nsDynamicFunctionLoad nsFuncs[] = {
			{"XRE_InitEmbedding", (NSFuncPtr*)&XRE_InitEmbedding},
			{"XRE_TermEmbedding", (NSFuncPtr*)&XRE_TermEmbedding},
			{0, 0}
	}; 
	nsresult rv;
	gtk_init (&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_show(window);
	
	
	//rv = XPCOMGlueStartup("/home/ml/code/temp/mozilla/dist/bin/libxpcom.so");
	rv = XPCOMGlueStartup( XULRUNNER_SDK_MAIN_LIB  "libxpcom.so" );
	if (NS_FAILED(rv))	printf("Error: XPCOMGlueStartup\n");
	
	rv = XPCOMGlueLoadXULFunctions(nsFuncs);
	if (NS_FAILED(rv)) 	printf("Error: XPCOMGlueLoadXULFunctions\n");
	
	rv = NS_NewNativeLocalFile(nsEmbedCString( XULRUNNER_SDK_MAIN_LIB ), PR_FALSE, getter_AddRefs(libxul));
	
	if (NS_FAILED(rv))	printf("Error: NS_NewNativeLocalFile\n");
	
	rv = XRE_InitEmbedding(libxul, 0, 0, 0, 0);
	if (NS_FAILED(rv)) printf("Error: XRE_InitEmbedding\n");

	webBrowser = do_CreateInstance(NS_WEBBROWSER_CONTRACTID, &rv);
	if (NS_FAILED(rv)) printf("Error: do_CreateInstance webBrowser\n");
	
	baseWindow = do_QueryInterface(webBrowser);
	rv = baseWindow->InitWindow(window, 0, 0, 0, 1024, 800);
	if (NS_FAILED(rv)) printf("Error: InitWindow\n");

	rv = baseWindow->Create();
	if (NS_FAILED(rv)) 	printf("Error: Create\n");
	
	rv =baseWindow->SetVisibility(PR_TRUE);
	if (NS_FAILED(rv)) 	printf("Error: SetVisibility\n");
	
	webNavigation = do_QueryInterface(webBrowser);
	rv = webNavigation->LoadURI(NS_ConvertASCIItoUTF16("http://www.home.dk").get(),nsIWebNavigation::LOAD_FLAGS_NONE, 0, 0, 0);
	if (NS_FAILED(rv)) 	printf("Error: LoadURI\n");
	
	g_signal_connect(G_OBJECT(window), "delete_event",G_CALLBACK(delete_event), 0);
	gtk_main();
	printf("exit...\n");
	XRE_TermEmbedding();
	XPCOMGlueShutdown();
	return 0;
}

#endif








//  static_cast<nsISupports*>(static_cast<__unambiguousBase>(__expr))

// 	nsCOMPtr<nsISupports> pChrome = NS_ISUPPORTS_CAST(nsISupports, new MiroBrowserEmbed());
// 	nsCOMPtr<MiroBrowserEmbed> pChrome = new MiroBrowserEmbed();
// 	nsCOMPtr<nsISupports> pChrome = new MiroBrowserEmbed();
// 	nsCOMPtr<nsISupports> pChrome ( static_cast<MiroBrowserEmbed*>(static_cast<nsISupports*>( new MiroBrowserEmbed())) );
