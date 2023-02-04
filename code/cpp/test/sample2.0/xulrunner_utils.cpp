#include "xulrunner_utils.h"
#include <nsServiceManagerUtils.h>
//#include <stdio.h>
//#include <string>
//#include <nsStringAPI.h>
//#include <nsIServiceManager.h>
//#include <nsIWindowMediator.h>
//#include <nsISimpleEnumerator.h>
//#include <nsIDOMWindowInternal.h>
//#include <nsIXULWindow.h>
//#include <nsIDocShell.h>
//#include <nsIInterfaceRequestor.h>
//#include <nsIDOMWindow.h>
//#include <nsIDOMLocation.h>
//#include <nsCOMPtr.h>

using namespace std;

// -------------------------------------------
// --- Get primary (Xul) windows functions ---
// -------------------------------------------

nsCOMPtr<nsIDOMWindowInternal>  getDOMWindowInternalByHref ( const nsString& wsHref )
{
    nsCOMPtr<nsIDOMWindowInternal> pWinInternalRetVal(0);
    nsresult rv;
    nsCOMPtr<nsIServiceManager> servMan;
    rv = NS_GetServiceManager(getter_AddRefs(servMan));

    nsCOMPtr<nsIWindowMediator> pWindowMediator(do_GetService(NS_WINDOWMEDIATOR_CONTRACTID));

    nsString sWindowType( NS_LITERAL_STRING("") );
    nsCOMPtr<nsISimpleEnumerator> pWinEnumerator;
    rv = pWindowMediator->GetEnumerator( sWindowType.get(), getter_AddRefs(pWinEnumerator));


    PRBool bHasMoreElements;
    rv = pWinEnumerator->HasMoreElements( &bHasMoreElements );

    while ( bHasMoreElements ) {
        nsCOMPtr<nsISupports> pSupportsWin;
        rv = pWinEnumerator->GetNext( getter_AddRefs(pSupportsWin) );
        nsCOMPtr<nsIDOMWindowInternal> pWinInternal(do_QueryInterface(pSupportsWin));

        nsCOMPtr<nsIDOMLocation> pDOMLocation;
        rv = pWinInternal->GetLocation( getter_AddRefs(pDOMLocation) );

        nsString wsHrefTest;
        rv = pDOMLocation->GetHref( wsHrefTest );

        if ( wsHref == wsHrefTest  ) {
            pWinInternalRetVal = pWinInternal;
        }
        rv = pWinEnumerator->HasMoreElements( &bHasMoreElements );
    }
    return pWinInternalRetVal;
}


nsCOMPtr<nsIDOMWindowInternal>  getDOMWindowInternalByHref ( const std::string& sHref )
{
    return getDOMWindowInternalByHref( toAStringUTF16(sHref) );
}


nsCOMPtr<nsIXULWindow>  getXulWinByHref ( const nsString& wsHref )
{
    std::string sHref = toStdStringUTF8( wsHref );

    nsCOMPtr<nsIXULWindow> pXulWinRetVal(0);
    nsresult rv;
    nsCOMPtr<nsIServiceManager> servMan;
    rv = NS_GetServiceManager(getter_AddRefs(servMan));

    nsCOMPtr<nsIWindowMediator> pWindowMediator(do_GetService(NS_WINDOWMEDIATOR_CONTRACTID));

    nsString sWindowType( NS_LITERAL_STRING("") );
    nsCOMPtr<nsISimpleEnumerator> pWinEnumerator;
    rv = pWindowMediator->GetXULWindowEnumerator( sWindowType.get(), getter_AddRefs(pWinEnumerator));


    PRBool bHasMoreElements;
    rv = pWinEnumerator->HasMoreElements( &bHasMoreElements );

    while ( bHasMoreElements ) {
        nsCOMPtr<nsISupports> pSupportsWin;
        rv = pWinEnumerator->GetNext( getter_AddRefs(pSupportsWin) );
        nsCOMPtr<nsIXULWindow> pXulWin(do_QueryInterface(pSupportsWin));

        std::string sCurUri = getCurrentUri(pXulWin);

        if ( sHref == sCurUri ) {
            pXulWinRetVal = pXulWin;
        }

        rv = pWinEnumerator->HasMoreElements( &bHasMoreElements );
    }

    return pXulWinRetVal;
}


nsCOMPtr<nsIXULWindow>  getXulWinByHref ( const std::string& sHref )
{
    return getXulWinByHref( toAStringUTF16(sHref) );
}

// ---------------------------
// --- XulWindow functions ---
// ---------------------------

std::string getCurrentUri( nsCOMPtr<nsIXULWindow> pXulWin )
{
    nsCOMPtr<nsIDocShell> pDocShell;
    pXulWin->GetDocShell( getter_AddRefs(pDocShell) );
    nsCOMPtr<nsIWebNavigation> pWebNav = tryGetIF<nsIWebNavigation>( pDocShell );
    nsCOMPtr<nsIURI> pCurrentURI;
    pWebNav->GetCurrentURI( getter_AddRefs(pCurrentURI) );

    nsCString ssSpec;
    pCurrentURI->GetSpec( ssSpec );
    return std::string ( ssSpec.get() );
}



// ------------------------------
// --- Get Interfaces helpers ---
// ------------------------------

// --- nsIDOMWindowInternal ---

nsCOMPtr<nsIDOMDocument> getDOMDocument( nsCOMPtr<nsIDOMWindowInternal> pWinInt )
{
    nsCOMPtr<nsIDOMDocument> pIF;
    pWinInt->GetDocument( getter_AddRefs(pIF) );
    return pIF;
}

nsCOMPtr<nsIDOMWindow> getContent( nsCOMPtr<nsIDOMWindowInternal> pWinInt )
{
    nsCOMPtr<nsIDOMWindow> pDomWin;
    pWinInt->GetContent( getter_AddRefs(pDomWin) );
    return pDomWin;
}

nsCOMPtr<nsIDOMWindowCollection> getFrames( nsCOMPtr<nsIDOMWindowInternal> pWinInt  )
{
    nsCOMPtr<nsIDOMWindowCollection> pDOMWindowCollection;
    pWinInt->GetFrames( getter_AddRefs(pDOMWindowCollection) );
    return pDOMWindowCollection;
}

nsCOMPtr<nsIDOMWindow> getDomWindowById( nsCOMPtr<nsIDOMWindowInternal> pWinInt, const std::string& sID )
{
    nsCOMPtr<nsIDOMWindowCollection> pDOMWindowCollection = getFrames( pWinInt );
    nsCOMPtr<nsIDOMWindow> pWin = namedItem( pDOMWindowCollection, sID.c_str() );
    return pWin;
}
// --- nsIDOMDocument ---

nsCOMPtr<nsIDOMElement> getDOMElementById( nsCOMPtr<nsIDOMDocument> pDomDoc, const std::string sID )
{
    nsCOMPtr<nsIDOMElement> pDomElem;
    nsString wsID = toAStringUTF16( sID );
    pDomDoc->GetElementById( wsID, getter_AddRefs(pDomElem) );
    return pDomElem;
}

nsCOMPtr<nsIDOMDocumentType> getDoctype( nsCOMPtr<nsIDOMDocument> pDomDoc )
{
    nsCOMPtr<nsIDOMDocumentType> docType;
    pDomDoc->GetDoctype( getter_AddRefs(docType) );
    return docType;
}

// --- nsIDOMWindowCollection ---
nsCOMPtr<nsIDOMWindow> namedItem( nsCOMPtr<nsIDOMWindowCollection> pDOMWindowCollection, const std::string sID )
{
    nsCOMPtr<nsIDOMWindow> pWin;
    nsString wsID = toAStringUTF16( sID );
    pDOMWindowCollection->NamedItem( wsID , getter_AddRefs(pWin) );
    return pWin;
}


// --- nsIDOMWindow ---
nsCOMPtr<nsIDOMDocument> getDocument ( nsCOMPtr<nsIDOMWindow> pWin )
{
    nsCOMPtr<nsIDOMDocument> pDomDoc;
    pWin->GetDocument( getter_AddRefs(pDomDoc) );
    return pDomDoc;
}


// --- nsIDOMDocumentView ---
nsCOMPtr<nsIDOMAbstractView> getDefaultView( nsCOMPtr<nsIDOMDocumentView> pDomDocumentView )
{
    nsCOMPtr<nsIDOMAbstractView> domAbstractView;
    pDomDocumentView->GetDefaultView(getter_AddRefs(domAbstractView));
    return domAbstractView;
}


// --------------------------------
// --- Navigation/Uri functions ---
// --------------------------------

std::string getCurrentURI( nsCOMPtr<nsIWebNavigation> pWebNav )
{
    nsresult rv;
    nsCOMPtr<nsIURI> pUri;
    rv = pWebNav->GetCurrentURI( getter_AddRefs(pUri) );
    if (NS_FAILED(rv)) {   printf ( "ERROR getCurrentURI 1\n" );   }
    nsCString ssSpec;
    rv = pUri->GetSpec(ssSpec);
    if (NS_FAILED(rv)) {   printf ( "ERROR getCurrentURI 2\n" );   }
    std::string sSpec(ssSpec.get() );
    return sSpec;
}


bool loadURI( nsCOMPtr<nsIWebNavigation> pWebNav, const std::string& sUri, PRUint32 aLoadFlags )
{
    nsresult rv = pWebNav->LoadURI( NS_ConvertUTF8toUTF16( sUri.c_str() ).get(), aLoadFlags, 0, 0, 0);
    return ( NS_FAILED(rv) ) ? false : true;
}

bool loadURI( nsCOMPtr<nsIWebNavigation> pWebNav, const std::string& sUri )
{
    return loadURI( pWebNav, sUri, 0);
}

/*



//        nsCOMPtr<nsIDocShell> pDocShell;
//        rv = pXulWin->GetDocShell( getter_AddRefs(pDocShell) );
//        if (NS_FAILED(rv)) {   printf ( "ERROR getXulWinByHref 1\n" );   }
//        printf("pDocShell: %p, rv: %d\n", pDocShell.get(), rv);


//        nsCOMPtr<nsIWebNavigation> pWebNav = tryGetIF<nsIWebNavigation>( pDocShell );
//        nsCOMPtr<nsIURI> pCurrentURI;
//        rv = pWebNav->GetCurrentURI( getter_AddRefs(pCurrentURI) );
//        if (NS_FAILED(rv)) {   printf ( "ERROR getXulWinByHref 2\n" );   }
//        printf("pCurrentURI: %p, rv: %d\n", pCurrentURI.get(), rv);

//        nsCString ssSpec;
//        rv = pCurrentURI->GetSpec( ssSpec );
//        if (NS_FAILED(rv)) {   printf ( "ERROR getXulWinByHref 3\n" );   }
//        printf("CurrentURI: '%s'\n", ssSpec.get() );
//        printf("TestURI   : '%s'\n", sHref.c_str() );

//        if ( sHref == ssSpec.get() ) {
//            pXulWinRetVal = pXulWin;
//        }







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


 */
