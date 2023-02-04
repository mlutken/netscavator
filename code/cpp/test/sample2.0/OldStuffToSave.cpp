#include <xulrunner_utils.h>

#include "CSpecialThing.h"

#include <stdio.h>
#include <string>

#include <nsIFrameLoader.h>
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

//#include <nsIFrameLoader.h>
#include <nsIBrowserDOMWindow.h>
#include <nsIDOMXULElement.h>
#include <nsIDOMDocumentView.h>
#include <nsIDocument.h>
#include <nsIDOMEventTarget.h>
#include <nsIDOMEvent.h>


#include <nsIXULBrowserWindow.h>

////#include <nsMediaCache.h>

//#include <nsIDocument.h>  // Compiler warnings en-mass


#include <mozbrowser/DefaultHttpActivityObserver.h>

using namespace std;



NS_IMPL_ISUPPORTS1(CSpecialThing, ISpecialThing)

CSpecialThing::CSpecialThing()
    : m_pIHttpActivityObserver(0)
{
    mName.Assign( NS_LITERAL_STRING("Default Name") );
    addHttpActivityObserver(nsCOMPtr<nsIHttpActivityObserver>(0), true);

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

nsCOMPtr<nsIXULWindow> tryGetXulWinFromDomWinInt1( nsCOMPtr<nsIDOMWindowInternal> pWinInt )
{
    nsCOMPtr<nsIInterfaceRequestor> pIFReq(do_QueryInterface( pWinInt ));

    nsCOMPtr<nsIXULWindow> pXulWin( do_QueryInterface( pIFReq ) );
    if ( !pXulWin.get() ) {   printf ( "ERROR tryGetXulWinFromDomWinInt1 2\n" );   }
    return pXulWin;
}


nsCOMPtr<nsIXULWindow> tryGetXulWinFromDomWinInt2( nsCOMPtr<nsIDOMWindowInternal> pWinInt )
{
    nsresult rv;
    nsCOMPtr<nsIDOMWindow> pDomWin;
    rv = pWinInt->GetContent( getter_AddRefs(pDomWin) );

    nsCOMPtr<nsIInterfaceRequestor> pIFReq(do_QueryInterface( pDomWin ));
    if ( !pIFReq.get() ) {   printf ( "ERROR tryGetXulWinFromDomWinInt2 1\n" );   }

    nsCOMPtr<nsIXULWindow> pXulWin( do_QueryInterface( pIFReq ) );

    if ( !pXulWin.get() ) {   printf ( "ERROR tryGetXulWinFromDomWinInt2 2\n" );   }
    return pXulWin;
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



void CSpecialThing::getBrowserSongBirdStyle()
{
    nsCOMPtr<nsIDOMWindow> pDomWin;

    nsCOMPtr<nsIXULWindow> pXulWin = getXulWinByHref( "chrome://xulcrawler/content/main.xul" );
    printf("pXulWin: %p\n", pXulWin.get() );

    std::string sUri = getCurrentUri( pXulWin );

    printf("URI: '%s'\n", sUri.c_str() );

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
    printf("webNavigation uri: %s\n", getCurrentURI(webNavigation).c_str() );
}






NS_IMETHODIMP CSpecialThing::Add(PRInt32 a, PRInt32 b, PRInt32 *_retval)
{
    printf("CSpecialThing::Add(%d, %d)\n", a, b );
    *_retval = a + b;

    getBrowserAnswerFromForum();
    return NS_OK;


    nsString wsName;
    nsresult rv;
    nsCOMPtr<nsIDOMWindowInternal> pWinInt = getDOMWindowInternalByHref( "chrome://xulcrawler/content/main.xul" );
    PRInt32 iWidth = 0;
    if ( pWinInt.get() )  {
        pWinInt->GetInnerWidth(&iWidth);
        printf("GetInnerWidth: %d\n", iWidth );
    }


    nsCOMPtr<nsIDOMWindow> pWin     = getDomWindowById( pWinInt, "mybrowser1" );
    printf("pWin: %p\n", pWin.get() );

//    nsCOMPtr<nsIFrameLoaderOwner>  pFLO = tryGetIF<nsIFrameLoaderOwner>(pDomDoc, "nsIFrameLoaderOwner");



    rv = pWin->GetName( wsName );
    printf("Name mybrowser1: '%s'\n", toStdStringUTF8(wsName).c_str());


    nsCOMPtr<nsIDOMDocument> pDomDoc = getDocument( pWin );
    nsCOMPtr<nsIDOMDocumentType> docType = getDoctype( pDomDoc );


    rv = docType->GetName( wsName );
    printf("docType name: '%s'\n", toStdStringUTF8(wsName).c_str());

    nsCOMPtr<nsIDOMHTMLDocument> pHtmlDoc = getIF<nsIDOMHTMLDocument>(pDomDoc);


    pHtmlDoc->GetTitle( wsName );
    printf("htmldoc name: '%s'\n", toStdStringUTF8(wsName).c_str());

    nsCOMPtr<nsIDOMDocumentView> domDocumentView(do_QueryInterface(pDomDoc));


    nsCOMPtr<nsIDOMAbstractView> domAbstractView = getDefaultView(domDocumentView);

    nsCOMPtr<nsIWebNavigation> webNavigation(do_GetInterface(domAbstractView));
    printf("webNavigation uri: %s\n", getCurrentURI(webNavigation).c_str() );

    //loadURI( webNavigation, "www.dr.dk" );
    nsCOMPtr<nsIDocShellTreeItem> docShellTreeItem(do_QueryInterface(webNavigation));

    nsCOMPtr<nsIDocShellTreeOwner> docShellTreeOwner;
    rv = docShellTreeItem->GetTreeOwner(getter_AddRefs(docShellTreeOwner));

    nsCOMPtr<nsIBaseWindow> baseWindow = do_QueryInterface(docShellTreeOwner);
    printf("baseWindow: %p\n", baseWindow.get() );

//    nsCOMPtr<nsIFrameLoaderOwner>  pB1 = tryGetIF<nsIFrameLoaderOwner>(domAbstractView, "nsIFrameLoaderOwner");
    //nsCOMPtr<nsIFrameLoader>  pB2;
    //pB1->GetFrameLoader( getter_AddRefs(pB2) );

    nsCOMPtr<nsIWidget> widget;
    rv = baseWindow->GetMainWidget(getter_AddRefs(widget));
    printf("widget: %p\n", widget.get() );

    // Attach event listeners
    nsCOMPtr<nsIDocument> document(do_QueryInterface(pDomDoc));
    printf("document: %p\n", document.get() );

    nsCOMPtr<nsIDOMWindow> mDOMWindow = do_QueryInterface(document->GetScriptGlobalObject());
    printf("mDOMWindow: %p\n", mDOMWindow.get() );

    nsCOMPtr<nsIDOMEventTarget> target(do_QueryInterface(mDOMWindow));
    printf("target: %p\n", mDOMWindow.get() );

    target->AddEventListener(NS_LITERAL_STRING("resize"), this, PR_FALSE);
    target->AddEventListener(NS_LITERAL_STRING("unload"), this, PR_FALSE);
    target->AddEventListener(NS_LITERAL_STRING("hide"), this, PR_FALSE);
    target->AddEventListener(NS_LITERAL_STRING("load"), this, PR_FALSE);
    target->AddEventListener(NS_LITERAL_STRING("DOMContentLoaded"), this, PR_FALSE);


/*

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

 */

    addHttpActivityObserver(nsCOMPtr<nsIHttpActivityObserver>(0), true);


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



    if ( eventType.EqualsLiteral("unload") || eventType.EqualsLiteral("hide")) {

//    // Clean up here
//    nsCOMPtr<nsIDOMEventTarget> target(do_QueryInterface(mDOMWindow));
//    NS_ENSURE_TRUE(target, NS_NOINTERFACE);
//    target->RemoveEventListener(NS_LITERAL_STRING("resize"), this, PR_FALSE);
//    target->RemoveEventListener(NS_LITERAL_STRING("unload"), this, PR_FALSE);
//    target->RemoveEventListener(NS_LITERAL_STRING("hide"), this, PR_FALSE);

//    mDOMWindow = nsnull;
//    mVideoWindow = nsnull;

//    if (mPlatformInterface) {
//      // Clear the video box/widget used by the platform-specific code.
//      nsresult rv = mPlatformInterface->SetVideoBox(nsnull, nsnull);
//      NS_ENSURE_SUCCESS(rv, rv);
//    }
    }
//  else if(eventType.EqualsLiteral("resize") &&
//          mPlatformInterface) {
//    mPlatformInterface->ResizeToWindow();
//  }

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
            m_pIHttpActivityObserver = new DefaultHttpActivityObserver(0);
            pIActivityDistributor->AddObserver(m_pIHttpActivityObserver);
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



void CSpecialThing::getBrowserAnswerFromForum()
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

    nsCOMPtr<nsIDOMDocument> doc;
    pWinInt->GetDocument(getter_AddRefs(doc));
    nsCOMPtr<nsIDOMElement> elt;
    doc->GetElementById(NS_LITERAL_STRING("browser1"), getter_AddRefs(elt));
    nsCOMPtr<nsIDOMEventTarget> tgt(do_QueryInterface(elt));
    printf("doc: %p\n", doc.get() );
    printf("elt: %p\n", elt.get() );
    printf("tgt: %p\n", tgt.get() );

//    tgt->AddEventListener(NS_LITERAL_STRING("DOMContentLoaded"), this, PR_TRUE);

}



/*


//    //// if (NS_FAILED(rv)) {   printf ( "ERROR ERROR\n" );   }


//    nsCOMPtr<nsIWebBrowser> pBrowser ( do_QueryInterface(pDomElem) );
//    if ( !pBrowser.get() ) {   printf ( "ERROR 3\n" );   }
//    nsCOMPtr<nsIXULWindow> pXulWin( do_QueryInterface( pWinInt ) );
//    if ( !pXulWin.get() ) {   printf ( "ERROR 13\n" );   }


//    nsCOMPtr<nsIDOMWindow> pDomWin;
//    rv = pWinInt->GetContent( getter_AddRefs(pDomWin) );


//    nsCOMPtr<nsIDOMDocument> pOwnerDoc;
//    pDomElem->GetOwnerDocument( getter_AddRefs(pOwnerDoc) );
//    printf(" pOwnerDoc.get() , pDDoc.get() : %p, %p\n", pOwnerDoc.get(), pDDoc.get() );
//    nsCOMPtr<nsIDOMHTMLDocument> pHtmDoc ( do_QueryInterface(pDomElem) );
//    if ( !pHtmDoc.get() ) {   printf ( "ERROR 11\n" );   }



//    rv = pDomElem->GetNodeName( wsName );
//    if (NS_FAILED(rv)) {   printf ( "ERROR 3\n" );   }
//    printf("XX name: '%s'\n", toStdStringUTF8(wsName).c_str());

    //GetOwnerDocument

////    nsCOMPtr<nsIDOMHTMLDocument> pHtmDoc ( do_QueryInterface(pDomElem) );
////    if ( !pHtmDoc.get() ) {   printf ( "ERROR 4\n" );   }

////    rv = pHtmDoc->GetTitle( wsName );
////    if (NS_FAILED(rv)) {   printf ( "ERROR 5\n" );   }
////    printf("XX htmldoc name: '%s'\n", toStdStringUTF8(wsName).c_str());

////    printf("pDDoc Name : '%s'\n", toStdStringUTF8(wsName).c_str());

//   GetElementById(const nsAString & elementId, nsIDOMElement **_retval NS_OUTPARAM)

   nsCOMPtr<nsIInterfaceRequestor> pIFReq(do_QueryInterface( pHtmlDoc ));
//    if ( !pIFReq.get() ) {   printf ( "ERROR 1\n" );   }

//    nsCOMPtr<nsIXULWindow> pXulWin( do_QueryInterface( pIFReq ) );
//    if ( !pXulWin.get() ) {   printf ( "ERROR 13\n" );   }


//    nsCOMPtr<nsIXULWindow> pXulWin( do_QueryInterface( pWin ) );
//    if ( !pXulWin.get() ) {   printf ( "ERROR 13\n" );   }
//    //        rv = pXulWin->GetDocShell( getter_AddRefs(pDocShell) );
//    //        if (NS_FAILED(rv)) {   printf ( "ERROR 9\n" );   }
//    nsCOMPtr<nsIDocShell> pDocShell( do_QueryInterface( pHtmlDoc ) );
//    if ( !pDocShell.get() ) {   printf ( "ERROR 14\n" );   }

//    nsCOMPtr<nsIWebBrowserChrome>	pIWebBrowserChrome ( do_QueryInterface(pHtmlDoc) );
//    if ( !pIWebBrowserChrome.get() ) {   printf ( "ERROR 15\n" );   }


//    if ( pWinInt.get() )  {
//        nsCOMPtr<nsIXULWindow> pXulWin( do_QueryInterface( pWinInt ) );
//        if ( !pXulWin.get() ) {   printf ( "ERROR 15\n" );   }
//        nsCOMPtr<nsIInterfaceRequestor> pIFReq(do_QueryInterface( pWinInt ));
//        if ( !pIFReq.get() ) {   printf ( "ERROR 16\n" );   }
//        nsCOMPtr<nsIDOMWindow> pDomWin;
//        rv = pIFReq->GetInterface( nsIDOMWindow::GetIID(), getter_AddRefs(pDomWin) );
//        if (NS_FAILED(rv)) {   printf ( "ERROR 17\n" );   }
//        if ( !pDomWin.get() ) {   printf ( "ERROR 18\n" );   }

//        nsCOMPtr<nsIDOMWindow> pDomTop;
//        rv = pDomWin->GetTop( getter_AddRefs(pDomTop) );
//        if (NS_FAILED(rv)) {   printf ( "ERROR 19\n" );   }
//        if ( !pDomTop.get() ) {   printf ( "ERROR 20\n" );   }
//        if ( pDomTop.get() == pDomWin.get() ) {
//            printf("Same same\n");
//        }
//        nsString wsName;
//        rv = pDomWin->GetName( wsName );
//        if (NS_FAILED(rv)) {   printf ( "ERROR 21\n" );   }
//        printf("Name: '%s'\n", toStdStringUTF8(wsName).c_str());

//        nsCOMPtr<nsIDOMDocument> pDomDoc;
//        rv = pDomWin->GetDocument( getter_AddRefs(pDomDoc) );
//        if (NS_FAILED(rv)) {   printf ( "ERROR 22\n" );   }


//        nsString wsNamespaceURI;
//        rv = pDomDoc->GetNamespaceURI( wsNamespaceURI );
//        if (NS_FAILED(rv)) {   printf ( "ERROR 23\n" );   }
//        printf("wsNamespaceURI: '%s'\n", toStdStringUTF8(wsName).c_str());

//        rv = pDomDoc->SetPrefix( NS_LITERAL_STRING("sss") );

//        rv = pDomDoc->GetPrefix( wsName );
//        if (NS_FAILED(rv)) {   printf ( "ERROR 24\n" );   }
//        printf("Name: '%s'\n", toStdStringUTF8(wsName).c_str());


//    }


        nsCOMPtr<nsIXULWindow> pXulWin( do_QueryInterface( pSupportsWin ) );
        if ( !pXulWin.get() ) {   printf ( "ERROR 8\n" );   }
        nsCOMPtr<nsIDocShell> pDocShell;
        rv = pXulWin->GetDocShell( getter_AddRefs(pDocShell) );
        if (NS_FAILED(rv)) {   printf ( "ERROR 9\n" );   }
        if ( !pDocShell.get() ) {   printf ( "ERROR 10\n" );   }

        PRBool bIsActive = PR_FALSE;
        rv = pDocShell->GetIsActive( &bIsActive );
        if (NS_FAILED(rv)) {   printf ( "ERROR 11\n" );   }
        printf("bIsActive: '%d'\n", bIsActive );

        nsCOMPtr<nsIInterfaceRequestor> pIFReq(do_QueryInterface( pDocShell ));
        if ( !pIFReq.get() ) {   printf ( "ERROR 12\n" );   }
        nsCOMPtr<nsIDOMWindow> pDomWin;
        rv = pIFReq->GetInterface( nsIDOMWindow::GetIID(), getter_AddRefs(pDomWin) );
        if (NS_FAILED(rv)) {   printf ( "ERROR 13\n" );   }
        if ( !pDomWin.get() ) {   printf ( "ERROR 14\n" );   }

        nsString wsName;
        rv = pDomWin->GetName( wsName );
        if (NS_FAILED(rv)) {   printf ( "ERROR 15\n" );   }

        string sName = toStdStringUTF8(wsName);
        printf("Name: '%s'\n", sName.c_str() );
        //GetName


//    NS_ConvertUTF16toUTF8 utf8(aName);
//    NS_ConvertUTF16toUTF8 utf8(NS_LITERAL_STRING("Hej hej") );
    nsString es (NS_LITERAL_STRING("Hej hej") );

    NS_ConvertUTF16toUTF8 utf8(es);
    //utf8.Assign("Hej");
//    return toStdStringUTF8( result );
//    std::string s1("gert"); // = utf8.get();
 //   std::string s2( utf8.get() ); // = utf8.get();
//    const char* sz1 =es.get() ; // = utf8.get();
//    const char* sz2 =utf8.get() ; // = utf8.get();
    printf ("SSS: '%s'\n", utf8.get() ); // = utf8.get();

//    printf("GERT: '%s'\n", s1.c_str() );
    //string sName = toStdStringUTF8(aName);



    printf("Trying...\n");
    nsresult rv;
    nsCOMPtr<nsIServiceManager> servMan;
    rv = NS_GetServiceManager(getter_AddRefs(servMan));
    if (NS_FAILED(rv)) {    printf ( "ERROR 1\n" );  }

//    nsCOMPtr<nsIWindowMediator> pWindowMediator;
//    rv = servMan->GetServiceByContractID( "@mozilla.org/appshell/window-mediator;1",  NS_GET_IID(nsIWindowMediator), getter_AddRefs(pWindowMediator));
    nsCOMPtr<nsIWindowMediator> pWindowMediator(do_GetService(NS_WINDOWMEDIATOR_CONTRACTID));


    if (NS_FAILED(rv)) {    printf ( "ERROR 2\n" );   }
//     nsCOMPtr<nsICacheSession> cacheSession;

    nsString sWindowType( NS_LITERAL_STRING("") );
    nsCOMPtr<nsISimpleEnumerator> pWinEnumerator;
    rv = pWindowMediator->GetEnumerator( sWindowType.get(), getter_AddRefs(pWinEnumerator));
//    rv = pWindowMediator->GetXULWindowEnumerator( sWindowType.get(), getter_AddRefs(pWinEnumerator));
    if (NS_FAILED(rv)) {    printf ( "ERROR 3\n" );   }

    PRBool bHasMoreElements;
    rv = pWinEnumerator->HasMoreElements( &bHasMoreElements );
    if (NS_FAILED(rv)) {   bHasMoreElements = PR_FALSE; printf ( "ERROR 4\n" );   }

    while ( bHasMoreElements ) {
        nsCOMPtr<nsISupports> pSupportsWin;

        rv = pWinEnumerator->GetNext( getter_AddRefs(pSupportsWin) );
        nsCOMPtr<nsIDOMWindowInternal> pWinInternal(do_QueryInterface(pSupportsWin));


        if (NS_FAILED(rv)) {   printf ( "ERROR 5\n" );   }
        if ( !pSupportsWin.get() ) {   printf ( "ERROR 6\n" );   }
        printf("pWinInternal.get(): %p\n", pWinInternal.get() );

        PRBool aFullScreen = 11;
        rv = pWinInternal->GetFullScreen( &aFullScreen);
        printf("pWinInternal.aFullScreen(): %d\n", aFullScreen );


        nsCOMPtr<nsIDOMLocation> pDOMLocation;
        rv = pWinInternal->GetLocation( getter_AddRefs(pDOMLocation) );
        if (NS_FAILED(rv)) {   printf ( "ERROR 6.1\n" );   }
        if ( !pDOMLocation.get() ) {   printf ( "ERROR 6.2\n" );   }


        PRInt32 iWidth;
        rv = pWinInternal->GetInnerWidth(&iWidth);
        if (NS_FAILED(rv)) {   printf ( "ERROR 7\n" );   }
        printf("iWidth: %d\n", iWidth );

        nsString wsHref;
        rv = pDOMLocation->GetHref( wsHref );
        if (NS_FAILED(rv)) {   printf ( "ERROR 15\n" );   }

        printf("Href: '%s'\n", toStdStringUTF8(wsHref).c_str() );


//        nsCOMPtr<nsIXULWindow> pXulWin( do_QueryInterface( pSupportsWin ) );
//        if ( !pXulWin.get() ) {   printf ( "ERROR 8\n" );   }
//        nsCOMPtr<nsIDocShell> pDocShell;
//        rv = pXulWin->GetDocShell( getter_AddRefs(pDocShell) );
//        if (NS_FAILED(rv)) {   printf ( "ERROR 9\n" );   }
//        if ( !pDocShell.get() ) {   printf ( "ERROR 10\n" );   }

//        PRBool bIsActive = PR_FALSE;
//        rv = pDocShell->GetIsActive( &bIsActive );
//        if (NS_FAILED(rv)) {   printf ( "ERROR 11\n" );   }
//        printf("bIsActive: '%d'\n", bIsActive );

//        nsCOMPtr<nsIInterfaceRequestor> pIFReq(do_QueryInterface( pDocShell ));
//        if ( !pIFReq.get() ) {   printf ( "ERROR 12\n" );   }
//        nsCOMPtr<nsIDOMWindow> pDomWin;
//        rv = pIFReq->GetInterface( nsIDOMWindow::GetIID(), getter_AddRefs(pDomWin) );
//        if (NS_FAILED(rv)) {   printf ( "ERROR 13\n" );   }
//        if ( !pDomWin.get() ) {   printf ( "ERROR 14\n" );   }

//        nsString wsName;
//        rv = pDomWin->GetName( wsName );
//        if (NS_FAILED(rv)) {   printf ( "ERROR 15\n" );   }

//        string sName = toStdStringUTF8(wsName);
//        printf("Name: '%s'\n", sName.c_str() );
//        //GetName

        printf("sdsd\n");
        //nsIID sd; GetCID, NS_IDOMWINDOW_IID

        rv = pWinEnumerator->HasMoreElements( &bHasMoreElements );
    }

    nsCOMPtr<nsIDOMWindowCollection> pDOMWindowColl;
    rv = pWin->GetFrames( getter_AddRefs(pDOMWindowColl) );
    if (NS_FAILED(rv)) {   printf ( "ERROR 8\n" );   }
    PRUint32 iLength = 333;
    rv = pDOMWindowColl->GetLength( &iLength );
    if (NS_FAILED(rv)) {   printf ( "ERROR 9\n" );   }
    printf("iLength: %d\n", iLength );

    for ( PRUint32 i = 0; i < iLength; ++i ) {
        nsCOMPtr<nsIDOMWindow> pW;
        nsString wsName;
        rv = pDOMWindowColl->Item( i, getter_AddRefs(pW) );
        if (NS_FAILED(rv)) {   printf ( "ERROR 10n" );   }
        rv = pW->GetName( wsName );
        if (NS_FAILED(rv)) {   printf ( "ERROR 11\n" );   }
        printf("Name: '%s'\n", toStdStringUTF8(wsName).c_str());
    }




    /////////////

    nsCOMPtr<nsIDOMWindow> pDomWin;
    rv = pWinInt->GetContent( getter_AddRefs(pDomWin) );

    nsCOMPtr<nsIDOMWindowCollection> pDOMWindowCollection;
    rv = pWinInt->GetFrames( getter_AddRefs(pDOMWindowCollection) );


    nsCOMPtr<nsIDOMWindow> pWin;
    rv =  pDOMWindowCollection->NamedItem( NS_LITERAL_STRING("mybrowser1") , getter_AddRefs(pWin) );
    rv = pWin->GetName( wsName );
    printf("Name mybrowser1: '%s'\n", toStdStringUTF8(wsName).c_str());

    nsCOMPtr<nsIDocShell> pDocShell( do_QueryInterface( pWinInt ) );
    if ( !pDocShell.get() ) {   printf ( "ERROR PIS\n" );   }



    nsCOMPtr<nsIDOMDocument> pDomDoc;
    rv = pWin->GetDocument( getter_AddRefs(pDomDoc) );
    if (NS_FAILED(rv)) {   printf ( "ERROR 8\n" );   }

    nsCOMPtr<nsIDOMDocumentType> docType;
    rv = pDomDoc->GetDoctype( getter_AddRefs(docType) );
    if (NS_FAILED(rv)) {   printf ( "ERROR 9\n" );   }

    rv = docType->GetName( wsName );
    if (NS_FAILED(rv)) {   printf ( "ERROR 10\n" );   }
    printf("docType name: '%s'\n", toStdStringUTF8(wsName).c_str());

    nsCOMPtr<nsIDOMHTMLDocument> pHtmlDoc ( do_QueryInterface(pDomDoc) );
    if ( !pHtmlDoc.get() ) {   printf ( "ERROR 11\n" );   }

    rv = pHtmlDoc->GetTitle( wsName );
    if (NS_FAILED(rv)) {   printf ( "ERROR 12\n" );   }
    printf("htmldoc name: '%s'\n", toStdStringUTF8(wsName).c_str());


    ///////////////////////////////////////////////////////////////////////////
    ///// Before remmoving the Element functions that gives warnings //////////
    ///////////////////////////////////////////////////////////////////////////
    #include <mozilla/dom/Element.h>

    nsString wsName;
    nsresult rv;
    nsCOMPtr<nsIDOMWindowInternal> pWinInt = getDOMWindowInternalByHref( "chrome://xulcrawler/content/main.xul" );
    PRInt32 iWidth = 0;
    if ( pWinInt.get() )  {
        pWinInt->GetInnerWidth(&iWidth);
        printf("GetInnerWidth: %d\n", iWidth );
    }
//    tryGetInterfaces( pWinInt, "pWinInt" );


    nsCOMPtr<nsIXULWindow> pXulWin = getXulWinByHref( "chrome://xulcrawler/content/main.xul" );
    printf("pXulWin: %p\n", pXulWin.get() );

    std::string sUri = getCurrentUri( pXulWin );

    printf("URI: '%s'\n", sUri.c_str() );

    nsCOMPtr<nsIDocShellTreeItem> pDocShellTreeItem;
    nsString wsNam = NS_LITERAL_STRING("mybrowser1");
    rv = pXulWin->GetContentShellById(wsNam.get() , getter_AddRefs(pDocShellTreeItem) );
    if (NS_FAILED(rv)) {   printf ( "ERROR 2\n" );   }
    if ( !pDocShellTreeItem.get() ) {   printf ( "ERROR 3\n" );   }

    nsCOMPtr<nsIDocShell> pDocShell;
    pXulWin->GetDocShell( getter_AddRefs(pDocShell) );

    nsCOMPtr<nsIPresShell> pPresShell;
    pDocShell->GetPresShell( getter_AddRefs(pPresShell) );
    printf("pPresShell: %p\n", pPresShell.get() );
    nsIDocument* pDocument = pPresShell->GetDocument();
    printf("pDocument: %p\n", pDocument );
    nsIURI* pURI = pDocument->GetDocumentURI();
    printf("pURI: %p\n", pURI );

    nsCString ssSpec;
    pURI->GetSpec( ssSpec );
    printf("ssSpec: %s\n", ssSpec.get() );
    //return std::string ( ssSpec.get() );

    mozilla::dom::Element* pElem = pDocument->GetElementById(NS_LITERAL_STRING("mybrowser1") );
//    mozilla::dom::Element* pElem = pDocument->GetElementById(NS_LITERAL_STRING("btn1") );
    printf("pElem: %p\n", pElem );

    printf("pElem->IsHtml: '%d'\n", pElem->IsHTML() );
    printf("pElem->IsXUL: '%d'\n", pElem->IsXUL() );

    nsCOMPtr<nsIDOMXULElement> pDOMXULElement;

////    nsIFrame* pFrame = pElem->GetPrimaryFrame();
////    printf("pFrame: '%p'\n", pFrame );

    //nsCOMPtr<nsIDOMNodeList> pDOMNodeList;
    //pElem->GetChildNodes( getter_AddRefs(pDOMNodeList));

    //printf("GetChildCount: '%d'\n", pElem->GetChildCount() );


    ////already_AddRefed<nsIURI> pRefUri = pElem->GetHrefURI();
    ////printf("pRefUri: '%p'\n", pRefUri.get() );


    nsCOMPtr<nsIWebBrowser> pWebBrowser;
    nsCOMPtr<nsIBrowserDOMWindow> pBrowserDOMWindow;

    //nsIWebBrowser

    ////nsQueryInterface qif(pElem);
    ////qif.operator()(nsIWebBrowser::GetIID(), getter_AddRefs(pWebBrowser) );
    ////printf("pWebBrowser: '%p'\n", pWebBrowser.get() );

    nsCOMPtr<nsIContent> pE(pElem);


    nsCOMPtr<nsIFrameLoaderOwner>  pB1 = tryGetIF<nsIFrameLoaderOwner>(pE, "nsIFrameLoaderOwner");
    nsCOMPtr<nsIFrameLoader>  pB2;
    pB1->GetFrameLoader( getter_AddRefs(pB2) );

    nsCOMPtr<nsIDocShell> pDocShell1;
    pB2->GetDocShell( getter_AddRefs(pDocShell1) );
    printf("pB2: %p\n", pB2.get() );
    printf("pDocShell1: %p\n", pDocShell1.get() );

    nsCOMPtr<nsIWebNavigation> pWebNav = tryGetIF<nsIWebNavigation>( pDocShell1 );
    printf("pWebNav: %p\n", pWebNav.get() );
    printf("URI: '%s'\n", getCurrentURI(pWebNav).c_str() );


    //nsPIDOMWindow* pPIDOMWindow = pDocument->GetWindow ();
   // printf("pPIDOMWindow: %p\n", pPIDOMWindow );

    //    pDocument->GetElementById()


//    rv = pDDoc->GetNodeName( wsName );
//     printf("XX pDDoc name: '%s'\n", toStdStringUTF8(wsName).c_str());

//    nsCOMPtr<nsIDOMDocument> pDDoc = getDOMDocument(pWinInt);
//    nsCOMPtr<nsIDOMElement> pDomElem = getDOMElementById( pDDoc, "mybrowser1" );



    nsCOMPtr<nsIDOMWindow> pDomWin = getContent( pWinInt);
    nsCOMPtr<nsIDOMWindowCollection> pDOMWindowCollection = getFrames( pWinInt );


    nsCOMPtr<nsIDOMWindow> pWin = namedItem( pDOMWindowCollection, "mybrowser1" );

    rv = pWin->GetName( wsName );
    printf("Name mybrowser1: '%s'\n", toStdStringUTF8(wsName).c_str());


    nsCOMPtr<nsIDOMDocument> pDomDoc = getDocument( pWin );
    nsCOMPtr<nsIDOMDocumentType> docType = getDoctype( pDomDoc );

    rv = docType->GetName( wsName );
    printf("docType name: '%s'\n", toStdStringUTF8(wsName).c_str());

    nsCOMPtr<nsIDOMHTMLDocument> pHtmlDoc = getIF<nsIDOMHTMLDocument>(pDomDoc);

    pHtmlDoc->GetTitle( wsName );
    printf("htmldoc name: '%s'\n", toStdStringUTF8(wsName).c_str());

    nsCOMPtr<nsIDOMDocumentView> domDocumentView(do_QueryInterface(pDomDoc));

    nsCOMPtr<nsIDOMAbstractView> domAbstractView = getDefaultView(domDocumentView);

    nsCOMPtr<nsIWebNavigation> webNavigation(do_GetInterface(domAbstractView));
    printf("webNavigation uri: %s\n", getCurrentURI(webNavigation).c_str() );

    //loadURI( webNavigation, "www.dr.dk" );
    nsCOMPtr<nsIDocShellTreeItem> docShellTreeItem(do_QueryInterface(webNavigation));
    nsCOMPtr<nsIDocShellTreeOwner> docShellTreeOwner;
    rv = docShellTreeItem->GetTreeOwner(getter_AddRefs(docShellTreeOwner));
    nsCOMPtr<nsIBaseWindow> baseWindow = do_QueryInterface(docShellTreeOwner);
    printf("baseWindow: %p\n", baseWindow.get() );

/ *

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

 * /



    printf("CSpecialThing::Add(%d, %d)\n", a, b );
    *_retval = a + b;
    return NS_OK;

    ////////////////

    void CSpecialThing::getBrowserQuestionForForum()
    {
        // --- A lot of variables ---
        nsCOMPtr<nsIDOMWindowInternal> pWinInternalRetVal(0);

        nsresult rv;
        nsCOMPtr<nsISimpleEnumerator>       pWinEnumerator;
        nsCOMPtr<nsIXULWindow>              pXulWin;
        nsCOMPtr<nsIDOMWindow>              pDomWin;
        nsCOMPtr<nsIDOMWindowCollection>    pDOMWindowCollection;
        nsCOMPtr<nsIDocShell>               pDocShell;
        nsCOMPtr<nsIURI>                    pURI;

        // ---------------------
        // --- Get XulWindow ---
        // ---------------------

        std::string sHref = "chrome://xulcrawler/content/main.xul";

        nsCOMPtr<nsIWindowMediator> pWindowMediator(do_GetService(NS_WINDOWMEDIATOR_CONTRACTID));

        nsString sWindowType( NS_LITERAL_STRING("") );
        rv = pWindowMediator->GetXULWindowEnumerator( sWindowType.get(), getter_AddRefs(pWinEnumerator));


        PRBool bHasMoreElements;
        rv = pWinEnumerator->HasMoreElements( &bHasMoreElements );


        while ( bHasMoreElements ) {
            nsCOMPtr<nsISupports> pSupportsWin;
            rv = pWinEnumerator->GetNext( getter_AddRefs(pSupportsWin) );
            nsCOMPtr<nsIXULWindow> pXulWnd(do_QueryInterface(pSupportsWin));

            // --- Get the xul window's URI ---
            pXulWnd->GetDocShell( getter_AddRefs(pDocShell) );
            nsCOMPtr<nsIWebNavigation> pWebNav( do_QueryInterface( pDocShell ) );
            pWebNav->GetCurrentURI( getter_AddRefs(pURI) );

            nsCString ssSpec;
            pURI->GetSpec( ssSpec );

            // Check the current URI against the one we are looking for
            if ( sHref == ssSpec.get() ) pXulWin = pXulWnd;
            rv = pWinEnumerator->HasMoreElements( &bHasMoreElements );
        }


        //pWinInt->GetFrames( getter_AddRefs(pDOMWindowCollection) );
        //printf("pDOMWindowCollection: %p\n", pDOMWindowCollection.get() );


        //pDOMWindowCollection->NamedItem( NS_LITERAL_STRING("mybrowser1") , getter_AddRefs(pDomWin) );

    //    nsCOMPtr<nsIDOMWindowCollection> pDOMWindowCollection = getFrames( pWinInt );
    //    nsCOMPtr<nsIDOMWindow> pWin = namedItem( pDOMWindowCollection, sID.c_str() );

    }

 */

