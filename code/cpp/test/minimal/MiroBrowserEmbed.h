
/*
 * MiroBrowserEmbed.h
 *
 * Public interface for our embedded xulrunner browser.  MiroBrowserEmbed
 * serves 2 functions.  It provides an XPCOM interface for XULRunner to hook
 * up to.  It also provides a C++ interface that the .pyx file uses to
 * controll the browser and to hook up callbacks to it.
 */

#ifndef __PCF_MIRO_BROWSER_EMBED_H__
#define __PCF_MIRO_BROWSER_EMBED_H__

#include "wx/wx.h"
#include <gtk/gtk.h>
#include "nsCOMPtr.h"
#include "nsIWebBrowserChrome.h"
#include "nsIEmbeddingSiteWindow.h"
#include "nsIWebBrowser.h"
#include "nsIInterfaceRequestor.h"
#include "nsIWebBrowserChromeFocus.h"
#include "nsIBaseWindow.h"

#define USE_WX 1

typedef void ( *focusCallback ) ( PRBool forward, void* data );

class MiroBrowserEmbed   : public nsIWebBrowserChrome,
			public nsIWebBrowserChromeFocus,
			public nsIEmbeddingSiteWindow,
			public nsIInterfaceRequestor

{
public:
	MiroBrowserEmbed();
	virtual ~MiroBrowserEmbed();

	/*
		* Methods from the XPCOM interfaces we implement.  These are proiveded
		* for XULRunner.
		*/

	NS_DECL_ISUPPORTS
	NS_DECL_NSIWEBBROWSERCHROME
	NS_DECL_NSIEMBEDDINGSITEWINDOW
	NS_DECL_NSIINTERFACEREQUESTOR
	NS_DECL_NSIWEBBROWSERCHROMEFOCUS

	/*
		* Methods to interact with the MiroBrowserEmbed from Cython.  These are
		* called by Miro.
		*/

	// Create a WebBrowser object and place it inside parentWindow.  This must
	// be called before any other methods.
	nsresult init ( GtkWidget* parentWindow, int x, int y, int width, int height );
#if USE_WX
	nsresult init ( wxWindow* parentWindow, int x, int y, int width, int height );
#endif //#if USE_WX
	

	// Load a URI into the browser
	nsresult loadURI ( const char* uri );
	// Call when the parent window changes size
	nsresult resize ( int x, int y, int width, int height );
	// Give the browser keyboard focus
	nsresult focus();
	// Set the focus callback.  This will be called when the user tabs through
	// all the elements in the browser and the next Widget should be given
	// focus.
	void SetFocusCallback ( focusCallback callback, void* data );
	// Destroy the broswer
	void destroy();

	nsCOMPtr<nsIWebBrowser> 	mWebBrowser;
	nsCOMPtr<nsIBaseWindow> 	mBrowserBaseWindow;

protected:
	nativeWindow mWindow;
	
	PRUint32     mChromeFlags;
	PRBool       mContinueModalLoop;
	focusCallback mFocusCallback;
	void* mFocusCallbackData;

};

/* Couple of utility functions, since the XPCOM Macros don't seem to work from
 * Cython.
 NOTE: These might not be needed!
 */
void addref ( MiroBrowserEmbed* browser );
void release ( MiroBrowserEmbed* browser );

#endif /* __PCF_MIRO_BROWSER_EMBED_H__ */
