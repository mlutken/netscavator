#ifndef _WEBBROWSE_DEFAULT_CHROME_EMBED_H_
#define _WEBBROWSE_DEFAULT_CHROME_EMBED_H_

#if WEBBROWSE_ENABLE_GTK
#	include <gtk/gtk.h>
#endif //#if WEBBROWSE_ENABLE_GTK

#if WEBBROWSE_ENABLE_WX
#	include <wx/wx.h>
#endif //#if WEBBROWSE_ENABLE_WX

#include <boost/shared_ptr.hpp>
#include <nsCOMPtr.h>
#include <nsIWebBrowserChrome.h>
#include <nsIEmbeddingSiteWindow.h>
#include <nsIWebBrowser.h>
#include <nsIInterfaceRequestor.h>
#include <nsIWebBrowserChromeFocus.h>
#include <nsIBaseWindow.h>
#include <nsIContextMenuListener.h>
#include <nsIHttpChannel.h>
#include <mozwebbrowser/MozDomNode.h>
#include <WebBrowserIF.h>

class SignalsManager;

typedef void ( *focusCallback ) ( PRBool forward, void* data );

class DefaultChromeEmbed   : 
			public nsIWebBrowserChrome,
			public nsIWebBrowserChromeFocus,
			public nsIEmbeddingSiteWindow,
			public nsIInterfaceRequestor,
			public nsIContextMenuListener

{
public:
//	DefaultChromeEmbed();
    DefaultChromeEmbed( crawl::WebBrowserIF* pWebBrowser, nsCOMPtr<nsIWebBrowser> pIWebBrowser, boost::shared_ptr<SignalsManager> pSignalsManager);
	virtual ~DefaultChromeEmbed();

	NS_DECL_ISUPPORTS
	NS_DECL_NSIWEBBROWSERCHROME
	NS_DECL_NSIEMBEDDINGSITEWINDOW
	NS_DECL_NSIINTERFACEREQUESTOR
	NS_DECL_NSIWEBBROWSERCHROMEFOCUS
	NS_DECL_NSICONTEXTMENULISTENER


	nsresult 					loadURI ( const char* uri );
	nsresult 					resize ( int x, int y, int width, int height );
	nsresult 					focus();
	void 						setFocusCallback ( focusCallback callback, void* data );
	void 						destroy();
	
	void						signalsManagerSet (boost::shared_ptr<SignalsManager> pSignalsManager) { m_pSignalsManager = pSignalsManager; }
		
	nsCOMPtr<nsIWebBrowser> 	getIWebBrowser() 	{	return m_pIWebBrowser;	}
	nsCOMPtr<nsIBaseWindow> 	getIBaseWindow() 	{	return m_pIBaseWindow;	}

protected:
    crawl::WebBrowserIF*                    m_pWebBrowserRawPtr;
    nsCOMPtr<nsIWebBrowser>                 m_pIWebBrowser;
    nsCOMPtr<nsIBaseWindow>                 m_pIBaseWindow;
    nativeWindow                            m_NativeWindow;
    boost::shared_ptr<SignalsManager>       m_pSignalsManager;

    focusCallback                           mFocusCallback;
    void*                                   mFocusCallbackData;
    PRUint32                                mChromeFlags;
    PRBool                                  mContinueModalLoop;

public:

#if WEBBROWSE_ENABLE_GTK
	nsresult 					initNativeWindow ( GtkWidget* parentWindow, int x, int y, int width, int height );
#endif //#if WEBBROWSE_ENABLE_GTK
#if WEBBROWSE_ENABLE_WX
	nsresult 					initNativeWindow ( wxWindow* parentWindow, int x, int y, int width, int height );
#endif //#if WEBBROWSE_ENABLE_WX

};

/* Couple of utility functions, since the XPCOM Macros don't seem to work from
 * Cython.
 */
void addref ( DefaultChromeEmbed* browser );
void release ( DefaultChromeEmbed* browser );

#endif // _WEBBROWSE_DEFAULT_CHROME_EMBED_H_ 
