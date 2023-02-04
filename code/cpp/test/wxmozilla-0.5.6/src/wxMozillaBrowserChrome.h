#ifndef __WX_MOZILLA_CHROME_H__
#define __WX_MOZILLA_CHROME_H__
/*
 * wxMozillaBrowserChrome
 * Copyright 2001 (c) Jeremiah Cornelius McCarthy. All Rights Reserved.
 */

#include "wxMozilla.h"
#include "wxMozillaBrowser.h"
#include "nsIWebBrowserChromeFocus.h"
#include "nsICommandParams.h"
//#include "mozilla-config.h"
#include "nsIWebNavigation.h"
//#include "nsISHistoryListener.h"
#include "nsStringAPI.h"
#include "nsCOMPtr.h"
//GONE:#include "nsIEventQueueService.h"
#include "nsIPref.h"
#include "nsISupports.h"
#include "nsIBaseWindow.h"
#include "nsIWebBrowser.h"
#include "nsIWebBrowserPersist.h"
#include "nsIWebBrowserChrome.h"
#include "nsIEmbeddingSiteWindow.h"
#include "nsEmbedAPI.h"
#include "nsIWindowCreator.h"
#include "nsIWindowWatcher.h"
#include "nsCWebBrowser.h"
#include "nsIWebProgressListener.h"
#include "nsIContextMenuListener2.h"
#include "nsIInterfaceRequestor.h"
#include "nsIWebBrowserSetup.h"
#include "nsIDocShellTreeItem.h"
#include "nsIWebBrowserChromeFocus.h"
#include "nsIInterfaceRequestor.h"
#include "nsIInterfaceRequestorUtils.h"
//#include "nsReadableUtils.h"
//#include "nsIWeakReference.h"
#include "nsWeakReference.h"
#include "nsIWeakReferenceUtils.h"
#include "nsIDOMMouseListener.h"
#include "nsIDOMKeyListener.h"
#include "nsIURIContentListener.h"


// forward declarations


/**
 * Mozilla chrome manager
 */
class wxMozillaBrowserChrome:
			public nsISupportsWeakReference,
			public nsIWebBrowserChrome,
			public nsIWebBrowserChromeFocus,
			public nsIWebProgressListener,
			public nsIEmbeddingSiteWindow,
			public nsIInterfaceRequestor,
			public nsIContextMenuListener2,
			public nsIWindowCreator,
			public nsIDOMMouseListener,
			public nsIDOMKeyListener,
			public nsIURIContentListener
{

	public:
		NS_DECL_ISUPPORTS
		NS_DECL_NSISUPPORTSWEAKREFERENCE
		NS_DECL_NSIWEBBROWSERCHROME
		NS_DECL_NSIWEBBROWSERCHROMEFOCUS
		NS_DECL_NSIWEBPROGRESSLISTENER
		NS_DECL_NSIINTERFACEREQUESTOR
		NS_DECL_NSIEMBEDDINGSITEWINDOW
		NS_DECL_NSICONTEXTMENULISTENER2
		NS_DECL_NSIWINDOWCREATOR
		NS_DECL_NSIURICONTENTLISTENER

		//nsIDOMMouseListener
		NS_IMETHOD MouseDown ( nsIDOMEvent* aDOMEvent );
		NS_IMETHOD MouseUp ( nsIDOMEvent* aDOMEvent );
		NS_IMETHOD MouseClick ( nsIDOMEvent* aDOMEvent );
		NS_IMETHOD MouseDblClick ( nsIDOMEvent* aDOMEvent );
		NS_IMETHOD MouseOver ( nsIDOMEvent* aDOMEvent );
		NS_IMETHOD MouseOut ( nsIDOMEvent* aDOMEvent );
		NS_IMETHOD HandleEvent ( nsIDOMEvent *event );

		// nsIDOMKeyListener
		NS_IMETHOD KeyDown ( nsIDOMEvent* aDOMEvent );
		NS_IMETHOD KeyUp ( nsIDOMEvent* aDOMEvent );
		NS_IMETHOD KeyPress ( nsIDOMEvent* aDOMEvent );

		wxMozillaBrowserChrome ( class wxMozillaBrowser *moz );
		virtual ~wxMozillaBrowserChrome();
		void CreateBrowser();

	protected:
		class wxMozillaBrowser *mMoz;
		void * siteWindow;
		bool m_mouseInWindow;
};

#endif
