/*
 * wxWindows Mozilla Browser Component
 * 
 * Developers:
 *  Jeremiah Cornelius McCarthy <jeremiah@whoop-ass.ca>
 *  Kevin Ollivier <kevino@tulane.edu>
 *  Dave Fancella <david.fancella@attbi.com>
 */

// Note: this is private header, to be included only by wxMozilla 
//       implementation!

#include "nsICommandManager.h"
#include "nsIEditingSession.h"
//GONE:#include "nsIDOMEventReceiver.h"
#include "nsIWebBrowserFocus.h"
#include "nsIHTMLEditor.h"
#include "nsIEditor.h"
#include "nsIDOMElement.h"
#include "nsIEditorSpellCheck.h"
#ifdef __WXMAC__
#include "nsIEventSink.h"
#endif 

struct wxMozillaBrowserInterface
{
    nsCOMPtr<nsIBaseWindow> mBaseWindow;
	nsCOMPtr<nsIWebBrowser> mWebBrowser;
	nsCOMPtr<nsIWebNavigation> mWebNav;
	nsCOMPtr<nsICommandManager> mCommandManager; //for editing, NYI
	nsCOMPtr<nsIEditingSession> mEditingSession;
    nsCOMPtr<nsIDOMElement> mSelectedElement;
// // 	nsCOMPtr <nsIEventQueue> eventQueue;
// // 	nsCOMPtr<nsIDOMEventReceiver> mEventReceiver;
	nsCOMPtr<nsIEditorSpellCheck> mSpellChecker;
#ifdef __WXMAC__
    nsCOMPtr<nsIEventSink> mEventSink;
#endif
};

