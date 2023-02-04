
#ifndef _MY_EMBEDWINDOW_H_
#define _MY_EMBEDWINDOW_H_



#include "nsIWebBrowserChrome.h"
#include "nsIEmbeddingSiteWindow.h"
#include "nsISupports.h"
#include "nsIWebBrowser.h"
#include "nsIBaseWindow.h"
#include "nsCOMPtr.h"
#include "nsStringAPI.h"

#include <gtk/gtk.h>

//class EmbedPrivate;

class EmbedWindow : public nsIWebBrowserChrome,
			public nsIEmbeddingSiteWindow
{

public:

	EmbedWindow();
	virtual ~EmbedWindow();

	nsresult Init ();
	nsresult CreateWindow ( GtkWidget* pOwningWidget );
	void     ReleaseChildren ( void );

	NS_DECL_ISUPPORTS

	NS_DECL_NSIWEBBROWSERCHROME

	NS_DECL_NSIEMBEDDINGSITEWINDOW

	nsString                 mTitle;

	nsCOMPtr<nsIBaseWindow>  mBaseWindow; // [OWNER]

private:

//  EmbedPrivate            *mOwner;
	nsCOMPtr<nsIWebBrowser>  mWebBrowser; // [OWNER]
};









#endif //_MY_EMBEDWINDOW_H_


