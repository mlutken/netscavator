#ifndef _WEBBROWSE_EMBEDDING_UTILS_H_
#define _WEBBROWSE_EMBEDDING_UTILS_H_

#include <boost/filesystem/path.hpp>
#include <nscore.h>
#include <nsCOMPtr.h>
#include <nsIWebBrowser.h>
#include <nsIWebBrowserChrome.h>
#include <nsPIDOMWindow.h>

nsresult 	initXulrunner();
nsresult 	initXulrunner( std::string const& sXulPath, std::string const& sEnvVar = "" );
nsresult 	initXulrunner( boost::filesystem::path xulPath, std::string const& sEnvVar = ""  );
void 		shutdownXulrunner();
nsresult	getPIDOMWindow ( nsPIDOMWindow** aPIWin, nsCOMPtr<nsIWebBrowser> pIWebBrowser  );




#if WEBBROWSE_ENABLE_QT
class QWidget;
nsresult
initNativeWindow (	nsCOMPtr<nsIWebBrowser>	pIWebBrowser,
					nsCOMPtr<nsIWebBrowserChrome> pIWebBrowserChrome,
					QWidget* pNativeContainerWindow, 
					int iX, int iY, int iWidth, int iHeight );

#endif //#if WEBBROWSE_ENABLE_QT


#if WEBBROWSE_ENABLE_WX
class wxWindow;
nsresult
initNativeWindow (	nsCOMPtr<nsIWebBrowser>	pIWebBrowser,
					nsCOMPtr<nsIWebBrowserChrome> pIWebBrowserChrome,
					wxWindow* pNativeContainerWindow, 
					int iX, int iY, int iWidth, int iHeight );

#endif //#if WEBBROWSE_ENABLE_WX

#if WEBBROWSE_ENABLE_GTK
#include <gtk/gtk.h>

nsresult
initNativeWindow (	nsCOMPtr<nsIWebBrowser>	pIWebBrowser,
					nsCOMPtr<nsIWebBrowserChrome> pIWebBrowserChrome,
					GtkWidget* pNativeContainerWindow, 
					int iX, int iY, int iWidth, int iHeight );

#endif //#if WEBBROWSE_ENABLE_GTK

#endif //_WEBBROWSE_EMBEDDING_UTILS_H_

