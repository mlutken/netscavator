
#ifndef _MY_EMBED_PRIVATE_H_
#define _MY_EMBED_PRIVATE_H_

#include "nsCOMPtr.h"
#include "nsStringAPI.h"
#include "nsIWebNavigation.h"
#include "nsISHistory.h"
// for our one function that gets the EmbedPrivate via the chrome
// object.
#include "nsIWebBrowserChrome.h"
#include "nsIAppShell.h"
#include "nsPIDOMEventTarget.h"
#include "nsVoidArray.h"
// app component registration
#include "nsIGenericFactory.h"
#include "nsIComponentRegistrar.h"

#include "mingtkmozembedprivate.h"

class EmbedProgress;
class EmbedWindow;
class EmbedContentListener;
class EmbedEventListener;

class nsPIDOMWindow;
class nsIDirectoryServiceProvider;

class EmbedPrivate {

 public:

  EmbedPrivate();
  ~EmbedPrivate();

//  nsresult    Init            (MinGtkMozEmbed *aOwningWidget);
  nsresult    Realize         (PRBool *aAlreadRealized);
  void        Unrealize       (void);
  void        Show            (void);
  void        Hide            (void);
  void        Resize          (PRUint32 aWidth, PRUint32 aHeight);
  void        Destroy         (void);
  void        SetURI          (const char *aURI);
  void        LoadCurrentURI  (void);
  void        Reload          (PRUint32 reloadFlags);

  void        SetChromeMask   (PRUint32 chromeMask);
  void        ApplyChromeMask ();

  static void PushStartup     (void);
  static void PopStartup      (void);
  static void SetPath         (const char *aPath);
  static void SetCompPath     (const char *aPath);
  static void SetAppComponents (const nsModuleComponentInfo* aComps,
                                int aNumComponents);
  static void SetProfilePath  (const char *aDir, const char *aName);
  static void SetDirectoryServiceProvider (nsIDirectoryServiceProvider * appFileLocProvider);

  nsresult OpenStream         (const char *aBaseURI, const char *aContentType);
  nsresult AppendToStream     (const PRUint8 *aData, PRUint32 aLen);
  nsresult CloseStream        (void);

  // This function will find the specific EmbedPrivate object for a
  // given nsIWebBrowserChrome.
  static EmbedPrivate *FindPrivateForBrowser(nsIWebBrowserChrome *aBrowser);

  // This is an upcall that will come from the progress listener
  // whenever there is a content state change.  We need this so we can
  // attach event listeners.
  void        ContentStateChange    (void);

  // This is an upcall from the progress listener when content is
  // finished loading.  We have this so that if it's chrome content
  // that we can size to content properly and show ourselves if
  // visibility is set.
  void        ContentFinishedLoading(void);

  // these are when the widget itself gets focus in and focus out
  // events
  void        ChildFocusIn (void);
  void        ChildFocusOut(void);


  MinGtkMozEmbed                   *mOwningWidget;

  // all of the objects that we own
  EmbedWindow                   *mWindow;
  nsCOMPtr<nsISupports>          mWindowGuard;
  EmbedProgress                 *mProgress;
  nsCOMPtr<nsISupports>          mProgressGuard;
  EmbedContentListener          *mContentListener;
  nsCOMPtr<nsISupports>          mContentListenerGuard;
  EmbedEventListener            *mEventListener;
  nsCOMPtr<nsISupports>          mEventListenerGuard;

  nsCOMPtr<nsIWebNavigation>     mNavigation;
  nsCOMPtr<nsISHistory>          mSessionHistory;

  // our event receiver
  nsCOMPtr<nsPIDOMEventTarget>   mEventTarget;

  // the currently loaded uri
  nsCString                      mURI;

  // the number of widgets that have been created
  static PRUint32                sWidgetCount;
  // the path to the GRE
  static char                   *sPath;
  // the path to components
  static char                   *sCompPath;
  // the list of application-specific components to register
  static const nsModuleComponentInfo  *sAppComps;
  static int                     sNumAppComps;
  // the appshell we have created
  static nsIAppShell            *sAppShell;
  // the list of all open windows
  static nsVoidArray            *sWindowList;
  // what is our profile path?
  static nsILocalFile           *sProfileDir;
  static nsISupports            *sProfileLock;

  static nsIDirectoryServiceProvider * sAppFileLocProvider;

  // chrome mask
  PRUint32                       mChromeMask;
  // is this a chrome window?
  PRBool                         mIsChrome;
  // has the chrome finished loading?
  PRBool                         mChromeLoaded;
  // saved window ID for reparenting later
  GtkWidget                     *mMozWindowWidget;
  // has someone called Destroy() on us?
  PRBool                         mIsDestroyed;

 private:

  // is the chrome listener attached yet?
  PRBool                         mListenersAttached;

  void GetListener    (void);
  void AttachListeners(void);
  void DetachListeners(void);

  // this will get the PIDOMWindow for this widget
  nsresult        GetPIDOMWindow   (nsPIDOMWindow **aPIWin);
  
  static nsresult RegisterAppComponents();

  // offscreen window methods and the offscreen widget
  static void       EnsureOffscreenWindow(void);
  static void       DestroyOffscreenWindow(void);
  static GtkWidget *sOffscreenWindow;
  static GtkWidget *sOffscreenFixed;
 
};



#endif //_MY_EMBED_PRIVATE_H_



