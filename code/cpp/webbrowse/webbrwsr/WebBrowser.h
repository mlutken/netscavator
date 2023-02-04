#ifndef _WEBBROWSE_WEB_BROWSER_H_
#define _WEBBROWSE_WEB_BROWSER_H_

#include <boost/signal.hpp>


#include <nsCOMPtr.h>
#include <nsIWebBrowser.h>
#include <nsIWebNavigation.h>

#include <dom/DOMWindow.h>
#include <utils/mozilla_if_macros.h>
#include <utils/mozilla_utils.h>


class WebBrowser;
typedef boost::shared_ptr<WebBrowser>		WebBrowserPtr;			///< Pointer to a WebBrowser

class WebBrowser : public Supports {
	MOZ_CONSTRUCT(WebBrowser,Supports);
public: 
  /**
     * Registers a listener of the type specified by the iid to receive
     * callbacks. The browser stores a weak reference to the listener
     * to avoid any circular dependencies.
     * Typically this method will be called to register an object
     * to receive <CODE>nsIWebProgressListener</CODE> or 
     * <CODE>nsISHistoryListener</CODE> notifications in which case the
     * the IID is that of the interface.
     *
     * @param aListener The listener to be added.
     * @param aIID      The IID of the interface that will be called
     *                  on the listener as appropriate.
     * @return          <CODE>NS_OK</CODE> for successful registration;
     *                  <CODE>NS_ERROR_INVALID_ARG</CODE> if aIID is not
     *                  supposed to be registered using this method;
     *                  <CODE>NS_ERROR_FAILURE</CODE> either aListener did not
     *                  expose the interface specified by the IID, or some
     *                  other internal error occurred.
     *
     * @see removeWebBrowserListener
     * @see nsIWeakReference
     * @see nsIWebProgressListener
     * @see nsISHistoryListener
     *
     * @return <CODE>NS_OK</CODE>, listener was successfully added;
     *         <CODE>NS_ERROR_INVALID_ARG</CODE>, one of the arguments was
     *         invalid or the object did not implement the interface
     *         specified by the IID.
     */
  /* void addWebBrowserListener (in nsIWeakReference aListener, in nsIIDRef aIID); */
  //NS_SCRIPTABLE NS_IMETHOD AddWebBrowserListener(nsIWeakReference *aListener, const nsIID & aIID) = 0;

  /**
     * Removes a previously registered listener.
     *
     * @param aListener The listener to be removed.
     * @param aIID      The IID of the interface on the listener that will
     *                  no longer be called.
     *
     * @return <CODE>NS_OK</CODE>, listener was successfully removed;
     *         <CODE>NS_ERROR_INVALID_ARG</CODE> arguments was invalid or
     *         the object did not implement the interface specified by the IID.
     *
     * @see addWebBrowserListener
     * @see nsIWeakReference
     */
  /* void removeWebBrowserListener (in nsIWeakReference aListener, in nsIIDRef aIID); */
  //NS_SCRIPTABLE NS_IMETHOD RemoveWebBrowserListener(nsIWeakReference *aListener, const nsIID & aIID) = 0;

  /**
     * The chrome object associated with the browser instance. The embedder
     * must create one chrome object for <I>each</I> browser object
     * that is instantiated. The embedder must associate the two by setting
     * this property to point to the chrome object before creating the browser
     * window via the browser's <CODE>nsIBaseWindow</CODE> interface. 
     *
     * The chrome object must also implement <CODE>nsIEmbeddingSiteWindow</CODE>.
     *
     * The chrome may optionally implement <CODE>nsIInterfaceRequestor</CODE>,
     * <CODE>nsIWebBrowserChromeFocus</CODE>,
     * <CODE>nsIContextMenuListener</CODE> and
     * <CODE>nsITooltipListener</CODE> to receive additional notifications
     * from the browser object.
     *
     * The chrome object may optionally implement <CODE>nsIWebProgressListener</CODE> 
     * instead of explicitly calling <CODE>addWebBrowserListener</CODE> and
     * <CODE>removeWebBrowserListener</CODE> to register a progress listener
     * object. If the implementation does this, it must also implement
     * <CODE>nsIWeakReference</CODE>.
     * 
     * @note The implementation should not refcount the supplied chrome
     *       object; it should assume that a non <CODE>nsnull</CODE> value is
     *       always valid. The embedder must explicitly set this value back
     *       to nsnull if the chrome object is destroyed before the browser
     *       object.
     *
     * @see nsIBaseWindow
     * @see nsIWebBrowserChrome
     * @see nsIEmbeddingSiteWindow
     * @see nsIInterfaceRequestor
     * @see nsIWebBrowserChromeFocus
     * @see nsIContextMenuListener
     * @see nsITooltipListener
     * @see nsIWeakReference
     * @see nsIWebProgressListener
     */
  /* attribute nsIWebBrowserChrome containerWindow; */
  //NS_SCRIPTABLE NS_IMETHOD GetContainerWindow(nsIWebBrowserChrome * *aContainerWindow) = 0;
  //NS_SCRIPTABLE NS_IMETHOD SetContainerWindow(nsIWebBrowserChrome * aContainerWindow) = 0;

  /**
     * URI content listener parent. The embedder may set this property to
     * their own implementation if they intend to override or prevent
     * how certain kinds of content are loaded.
     *
     * @note If this attribute is set to an object that implements
     *       nsISupportsWeakReference, the implementation should get the
     *       nsIWeakReference and hold that.  Otherwise, the implementation
     *       should not refcount this interface; it should assume that a non
     *       null value is always valid.  In that case, the embedder should
     *       explicitly set this value back to null if the parent content
     *       listener is destroyed before the browser object.
     *
     * @see nsIURIContentListener
     */
  /* attribute nsIURIContentListener parentURIContentListener; */
  //NS_SCRIPTABLE NS_IMETHOD GetParentURIContentListener(nsIURIContentListener * *aParentURIContentListener) = 0;
  //NS_SCRIPTABLE NS_IMETHOD SetParentURIContentListener(nsIURIContentListener * aParentURIContentListener) = 0;

	/** The top-level DOM window. The embedder may walk the entire
		DOM starting from this value.
		\see nsIDOMWindow */
	boost::shared_ptr<DOMWindow>	contentDOMWindow () 
	{
		nsCOMPtr<nsIDOMWindow> pIDomWindow;
		ifMoz()->GetContentDOMWindow ( getter_AddRefs ( pIDomWindow ) );
		return boost::shared_ptr<DOMWindow>(new DOMWindow(pIDomWindow));				
	}
		
	// ------------------------------------------------
	// --- Methods beyond W3C/Mozilla specification ---	
	// ------------------------------------------------
private:
	

};

boost::shared_ptr<WebBrowser>	createWebBrowser();


#endif //_WEBBROWSE_WEB_BROWSER_H_


