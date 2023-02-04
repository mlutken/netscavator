#include <xulrunner_utils.h>

#include "CSpecialThing.h"

#include <stdio.h>
#include <string>

//#include <nsIFrameLoader.h>
#include <nsStringAPI.h>
#include <nsIServiceManager.h>
#include <nsIWindowMediator.h>
#include <nsISimpleEnumerator.h>
#include <nsIDOMWindowInternal.h>
#include <nsIXULWindow.h>
#include <nsIDocShell.h>
#include <nsIInterfaceRequestor.h>
#include <nsIDOMWindow.h>
#include <nsIDOMWindow2.h>
#include <nsIDOMLocation.h>
#include <nsServiceManagerUtils.h>
#include <nsIDOMDocument.h>
#include <nsIDOMWindowCollection.h>
#include <nsIDOMDocumentType.h>
#include <nsIWebBrowser.h>
#include <nsIWebBrowserChrome.h>
#include <nsIDOMDOMImplementation.h>
#include <nsIDOMNode.h>
#include <nsIDOMDocumentType.h>
#include <nsIDOMHTMLDocument.h>
#include <nsIDOMHTMLElement.h>
#include <nsIDOMElement.h>
#include <nsIWebNavigation.h>
#include <nsIDocShellTreeItem.h>
#include <nsIPresShell.h>
#include <nsIURI.h>
#include <nsIInterfaceRequestorUtils.h>
#include <nsIDOMAbstractView.h>
#include <nsIBaseWindow.h>
#include <nsIDocShellTreeOwner.h>
#include <nsIDOMEventListener.h>

////#include <nsFrame.h>
////#include <nsPIDOMWindow.h>
////#include <mozilla/dom/Element.h> // Yields warnings

#include <nsIBrowserDOMWindow.h>
#include <nsIDOMXULElement.h>
#include <nsIDOMDocumentView.h>
//#include <nsIDocument.h>          // Yields warnings
#include <nsIDOMEventTarget.h>
#include <nsIDOMEvent.h>


#include <nsIXULBrowserWindow.h>

// --- ---
//#include <mozbrowser/DefaultHttpActivityObserver.h>

using namespace std;



NS_IMPL_ISUPPORTS1(CSpecialThing, ISpecialThing)

CSpecialThing::CSpecialThing()
    : m_bInitialized(false)
    , m_pDomWinBrowser(0)
    , m_pDomWinHtml(0)
    , m_pIHttpActivityObserver(0)
{
    mName.Assign( NS_LITERAL_STRING("Default Name") );
    //addHttpActivityObserver(nsCOMPtr<nsIHttpActivityObserver>(0), true);

}

CSpecialThing::~CSpecialThing()
{
    /* destructor code */
}

/* attribute AString name; */
NS_IMETHODIMP CSpecialThing::GetName(nsAString & aName)
{
    aName.Assign(mName);
    return NS_OK;
}
NS_IMETHODIMP CSpecialThing::SetName(const nsAString & aName)
{
    nsString es (aName);
    mName.Assign(aName);
    return NS_OK;
}







NS_IMETHODIMP CSpecialThing::Init(const nsAString & xulWindow, const nsAString & browserId)
{
    if ( m_bInitialized ) return NS_OK;
    printf("CSpecialThing::Init('%s','%s')\n", toStdStringUTF8(xulWindow).c_str(), toStdStringUTF8(browserId).c_str());
    nsCOMPtr<nsIDOMWindowInternal> pWinInt = getDOMWindowInternalByHref( toStdStringUTF8(xulWindow) );

    //nsCOMPtr<nsIDOMWindow> pDomWinBrowser;
    m_pDomWinHtml  = getDomWindowById( pWinInt, toStdStringUTF8(browserId) );
    m_pDomWinHtml->GetParent( getter_AddRefs(m_pDomWinBrowser) );

    // --- Add events ---
    nsCOMPtr<nsIDOMEventTarget> pDomEventTargetWinHtml(do_QueryInterface(m_pDomWinHtml));
    nsCOMPtr<nsIDOMEventTarget> pDomEventTargetBrowser(do_QueryInterface(m_pDomWinBrowser));
    pDomEventTargetBrowser->AddEventListener(NS_LITERAL_STRING("DOMContentLoaded"), this, PR_FALSE);
    pDomEventTargetBrowser->AddEventListener(NS_LITERAL_STRING("resize"), this, PR_FALSE);
    pDomEventTargetWinHtml->AddEventListener(NS_LITERAL_STRING("unload"), this, PR_FALSE);

    m_bInitialized = true;
    return NS_OK;
}



NS_IMETHODIMP CSpecialThing::Add(PRInt32 a, PRInt32 b, PRInt32 *_retval)
{
    printf("CSpecialThing::Add(%d, %d)\n", a, b );
    *_retval = a + b;

   // getBrowserQuestionForForum();
    return NS_OK;


    nsString wsName;
    nsresult rv;
    nsCOMPtr<nsIDOMWindowInternal> pWinInt = getDOMWindowInternalByHref( "chrome://xulcrawler/content/main.xul" );
    PRInt32 iWidth = 0;
    if ( pWinInt.get() )  {
        pWinInt->GetInnerWidth(&iWidth);
        printf("GetInnerWidth: %d\n", iWidth );
    }


    nsCOMPtr<nsIDOMWindow> pDomWinBrowser;
    nsCOMPtr<nsIDOMWindow> pDomWin     = getDomWindowById( pWinInt, "mybrowser1" );
    pDomWin->GetParent( getter_AddRefs(pDomWinBrowser) );
    printf("pDomWin: %p\n", pDomWin.get() );
    printf("pDomWinBrowser: %p\n", pDomWinBrowser.get() );

    // --- Add events ---
    nsCOMPtr<nsIDOMEventTarget> pDomEventTargetBrowserWin(do_QueryInterface(pDomWin));
    nsCOMPtr<nsIDOMEventTarget> pDomEventTargetBrowser(do_QueryInterface(pDomWinBrowser));
    pDomEventTargetBrowser->AddEventListener(NS_LITERAL_STRING("DOMContentLoaded"), this, PR_FALSE);
    pDomEventTargetBrowser->AddEventListener(NS_LITERAL_STRING("resize"), this, PR_FALSE);
    pDomEventTargetBrowserWin->AddEventListener(NS_LITERAL_STRING("unload"), this, PR_FALSE);


    rv = pDomWin->GetName( wsName );
    printf("Name mybrowser1: '%s'\n", toStdStringUTF8(wsName).c_str());


    nsCOMPtr<nsIDOMDocument> pDomDoc = getDocument( pDomWin );
    nsCOMPtr<nsIDOMDocumentType> docType = getDoctype( pDomDoc );


    rv = docType->GetName( wsName );
    printf("docType name: '%s'\n", toStdStringUTF8(wsName).c_str());

    nsCOMPtr<nsIDOMHTMLDocument> pHtmlDoc = getIF<nsIDOMHTMLDocument>(pDomDoc);


    pHtmlDoc->GetTitle( wsName );
    printf("htmldoc name: '%s'\n", toStdStringUTF8(wsName).c_str());

    nsCOMPtr<nsIDOMDocumentView> domDocumentView(do_QueryInterface(pDomDoc));


    nsCOMPtr<nsIDOMAbstractView> domAbstractView = getDefaultView(domDocumentView);

    nsCOMPtr<nsIWebNavigation> webNavigation(do_GetInterface(domAbstractView));
    printf("A webNavigation uri: %s\n", getCurrentURI(webNavigation).c_str() );

//    loadURI( webNavigation, "www.dr.dk" );

    //addHttpActivityObserver(nsCOMPtr<nsIHttpActivityObserver>(0), true);


    return NS_OK;
}

NS_IMETHODIMP CSpecialThing::DbgPrint(const nsAString & str)
{
    printf("%s", toStdStringUTF8(str).c_str() );
    return NS_OK;
}

//-----------------------------------------------------------------------------
// nsIDOMEventListener
//-----------------------------------------------------------------------------

NS_IMETHODIMP
CSpecialThing::HandleEvent(nsIDOMEvent* aEvent)
{
    nsString eventType;
    aEvent->GetType(eventType);

    printf("HandleEvent: '%s'\n", toStdStringUTF8(eventType).c_str() );



    if ( eventType.EqualsLiteral("unload") ) {
    }
    else if ( eventType.EqualsLiteral("DOMContentLoaded") ) {
        // --- Re-add events ---
        nsCOMPtr<nsIDOMEventTarget> pDomEventTargetWinHtml(do_QueryInterface(m_pDomWinHtml));
        pDomEventTargetWinHtml->AddEventListener(NS_LITERAL_STRING("unload"), this, PR_FALSE);
        //printf("Re-add events\n");
    }

    return NS_OK;
}



////////////
void CSpecialThing::addHttpActivityObserver(
    nsCOMPtr<nsIHttpActivityObserver>	pIHttpActivityObserver,
    bool 								bAllowCreateDefault
)
{

    if ( m_pIHttpActivityObserver == NULL ) {
        // Should we disable this listener ?
        if ( !pIHttpActivityObserver && !bAllowCreateDefault ) {
            m_pIHttpActivityObserver = NULL;
            return;
        }
        nsresult rv;



        nsCOMPtr<nsIHttpActivityDistributor> 	pIActivityDistributor 	= do_GetService("@mozilla.org/network/http-activity-distributor;1");
        if ( pIActivityDistributor ) {
            printf("ML: nsIHttpActivityDistributor 1\n");
//            m_pIHttpActivityObserver = new DefaultHttpActivityObserver(0);
//            pIActivityDistributor->AddObserver(m_pIHttpActivityObserver);
        }



    //    // Add listener
    //    m_pIHttpActivityObserver = pIHttpActivityObserver;
    //    if ( !m_pIHttpActivityObserver ) m_pIHttpActivityObserver = new DefaultHttpActivityObserver(*m_pMozBrowser);
    //    // bind the progress listener to the browser object
    //    nsCOMPtr<nsISupportsWeakReference> supportsWeak;
    //    supportsWeak = do_QueryInterface( m_pIWebProgressListener );
    //    nsCOMPtr<nsIWeakReference> weakRef;
    //    supportsWeak->GetWeakReference( getter_AddRefs(weakRef) );
    //    m_pWebBrowser->ifMoz()->AddWebBrowserListener( weakRef, NS_GET_IID(nsIHttpActivityObserver) );

    }

}



void CSpecialThing::getBrowserQuestionForForum()
{
    nsString wsHrefXul      = NS_LITERAL_STRING( "chrome://xulcrawler/content/main.xul" );
    nsString wsIDBrowser    = NS_LITERAL_STRING( "mybrowser1" );

    // --- A lot of variables ---
    nsresult rv;
    nsCOMPtr<nsIDOMWindowInternal>      pWinInt(0);
    nsCOMPtr<nsISimpleEnumerator>       pWinEnumerator;
    nsCOMPtr<nsIDOMLocation>            pDOMLocation;
    nsCOMPtr<nsIDOMWindowCollection>    pDOMWindowCollection;
    nsCOMPtr<nsIDOMWindow>              pDomWin;
    nsCOMPtr<nsIDOMWindow>              pDomWinBrowser;
    nsCOMPtr<nsIDOMDocument>            pDomDoc;


    // -----------------------------
    // --- Get DomWindowInternal ---
    // -----------------------------

    nsCOMPtr<nsIWindowMediator> pWindowMediator(do_GetService(NS_WINDOWMEDIATOR_CONTRACTID));

    nsString sWindowType( NS_LITERAL_STRING("") );
    rv = pWindowMediator->GetEnumerator( sWindowType.get(), getter_AddRefs(pWinEnumerator));


    PRBool bHasMoreElements;
    rv = pWinEnumerator->HasMoreElements( &bHasMoreElements );

    while ( bHasMoreElements ) {
        nsCOMPtr<nsISupports> pSupportsWin;
        rv = pWinEnumerator->GetNext( getter_AddRefs(pSupportsWin) );
        nsCOMPtr<nsIDOMWindowInternal> pWinInternal(do_QueryInterface(pSupportsWin));

        rv = pWinInternal->GetLocation( getter_AddRefs(pDOMLocation) );

        nsString wsHrefTest;
        rv = pDOMLocation->GetHref( wsHrefTest );

        // See if we have the correct (XUL) URI
        if ( wsHrefXul == wsHrefTest  ) pWinInt = pWinInternal;

        rv = pWinEnumerator->HasMoreElements( &bHasMoreElements );
    }

    // --- Get the "mybrowser1" element ---
    pWinInt->GetFrames( getter_AddRefs(pDOMWindowCollection) );
    pDOMWindowCollection->NamedItem( wsIDBrowser, getter_AddRefs(pDomWin) );

    pDomWin->GetParent( getter_AddRefs(pDomWinBrowser) );

    // --- Add events ---
    nsCOMPtr<nsIDOMEventTarget> pDomEventTargetBrowserWin(do_QueryInterface(pDomWin));
    nsCOMPtr<nsIDOMEventTarget> pDomEventTargetBrowser(do_QueryInterface(pDomWinBrowser));
    pDomEventTargetBrowser->AddEventListener(NS_LITERAL_STRING("DOMContentLoaded"), this, PR_FALSE);
    pDomEventTargetBrowser->AddEventListener(NS_LITERAL_STRING("resize"), this, PR_FALSE);
    pDomEventTargetBrowserWin->AddEventListener(NS_LITERAL_STRING("unload"), this, PR_FALSE);

    // ---------------------------------------------------------------
    // --- Bonus example on how to get the current URI of the page ---
    // ---------------------------------------------------------------
    pDomWin->GetDocument( getter_AddRefs(pDomDoc) );
    nsCOMPtr<nsIDOMDocumentView> pDomDocumentView(do_QueryInterface(pDomDoc));
    nsCOMPtr<nsIDOMAbstractView> domAbstractView = getDefaultView(pDomDocumentView);
    nsCOMPtr<nsIWebNavigation> webNavigation(do_GetInterface(domAbstractView));
    printf("B webNavigation uri: %s\n", getCurrentURI(webNavigation).c_str() );
}

/*
NS_IMETHODIMP
SetVideoWindow(nsIDOMXULElement *aVideoWindow)
{
  NS_ENSURE_ARG_POINTER(aVideoWindow);

 // nsAutoMonitor mon(mMonitor);

  // Get the box object representing the actual display area for the video.
  nsCOMPtr<nsIBoxObject> boxObject;
  nsresult rv = aVideoWindow->GetBoxObject(getter_AddRefs(boxObject));
  NS_ENSURE_SUCCESS (rv, rv);

  nsCOMPtr<nsIDOMDocument> domDocument;
  rv = aVideoWindow->GetOwnerDocument(getter_AddRefs(domDocument));
  NS_ENSURE_SUCCESS(rv, rv);

  nsCOMPtr<nsIDOMDocumentView> domDocumentView(do_QueryInterface(domDocument));
  NS_ENSURE_TRUE(domDocumentView, NS_NOINTERFACE);

  nsCOMPtr<nsIDOMAbstractView> domAbstractView;
  rv = domDocumentView->GetDefaultView(getter_AddRefs(domAbstractView));
  NS_ENSURE_SUCCESS(rv, rv);

  nsCOMPtr<nsIWebNavigation> webNavigation(do_GetInterface(domAbstractView));
  nsCOMPtr<nsIDocShellTreeItem> docShellTreeItem(do_QueryInterface(webNavigation));
  NS_ENSURE_TRUE(docShellTreeItem, NS_NOINTERFACE);

  nsCOMPtr<nsIDocShellTreeOwner> docShellTreeOwner;
  rv = docShellTreeItem->GetTreeOwner(getter_AddRefs(docShellTreeOwner));
  NS_ENSURE_SUCCESS(rv, rv);

  nsCOMPtr<nsIBaseWindow> baseWindow = do_QueryInterface(docShellTreeOwner);
  NS_ENSURE_TRUE(baseWindow, NS_NOINTERFACE);

  nsCOMPtr<nsIWidget> widget;
  rv = baseWindow->GetMainWidget(getter_AddRefs(widget));
  NS_ENSURE_SUCCESS(rv, rv);

  // Attach event listeners
  nsCOMPtr<nsIDocument> document(do_QueryInterface(domDocument));
  NS_ENSURE_TRUE(document, NS_NOINTERFACE);

  mDOMWindow = do_QueryInterface(document->GetScriptGlobalObject());
  NS_ENSURE_TRUE(mDOMWindow, NS_NOINTERFACE);

  nsCOMPtr<nsIDOMEventTarget> target(do_QueryInterface(mDOMWindow));
  NS_ENSURE_TRUE(target, NS_NOINTERFACE);
  target->AddEventListener(NS_LITERAL_STRING("resize"), this, PR_FALSE);
  target->AddEventListener(NS_LITERAL_STRING("unload"), this, PR_FALSE);
  target->AddEventListener(NS_LITERAL_STRING("hide"), this, PR_FALSE);

  NS_WARN_IF_FALSE(NS_IsMainThread(), "Wrong Thread!");

  mVideoWindow = aVideoWindow;

  if (mPlatformInterface) {
    rv = mPlatformInterface->SetVideoBox(boxObject, widget);
    NS_ENSURE_SUCCESS(rv, rv);

    rv = mPlatformInterface->SetDocument(domDocument);
    NS_ENSURE_SUCCESS(rv, rv);
  }
  return NS_OK;
}

*/

