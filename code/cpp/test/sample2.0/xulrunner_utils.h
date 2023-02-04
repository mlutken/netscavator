#include <stdio.h>
#include <string>

class nsFrameLoader;    // Hack to avoid compiler error in nsIFrameLoader.h

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
#include <nsCOMPtr.h>
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
#include <nsIURI.h>
#include <nsIAppShell.h>
#include <nsIXULBrowserWindow.h>
#include <nsIDOMDocumentView.h>


/** Convert a Mozilla UTF16 string (nsEmbedString) to a std::string in UTF8 */
inline std::string
toStdStringUTF8 (const nsString& aString )      ///< Mozilla UTF16 string to convert
{
    return NS_ConvertUTF16toUTF8(aString).get();
}

inline std::string
toStdStringUTF8 (const nsAString& aString )      ///< Mozilla UTF16 string to convert
{
    return NS_ConvertUTF16toUTF8(aString).get();
}


/** Convert a std::string in UTF8 to Mozilla UTF16 string */
inline nsString
toAStringUTF16 (const std::string& sString )        ///< UTF8 std::string to convert
{
    return NS_ConvertUTF8toUTF16( sString.c_str() );
}


template <typename NS_IF_TO, typename NS_COM_PTR_FROM >
nsCOMPtr<NS_IF_TO>
inline getIF( NS_COM_PTR_FROM pType )
{
    nsCOMPtr<NS_IF_TO> pIF(0);

    nsCOMPtr<NS_IF_TO> pIF1(do_QueryInterface( pType ));

    if ( pIF1.get() ) {
        pIF = pIF1;
    }
    else {
        nsCOMPtr<nsIInterfaceRequestor> pIFReq(do_QueryInterface( pType ));
        nsCOMPtr<NS_IF_TO> pIF2(do_QueryInterface( pIFReq ));
        if ( pIF2.get() ) {
            pIF = pIF2;
        }
    }
    return pIF;
}


template <typename NS_IF_TO, typename NS_COM_PTR_FROM >
nsCOMPtr<NS_IF_TO>
inline tryGetIF( NS_COM_PTR_FROM pType, const std::string sToType = "" )
{
    printf("tryGetIF (%s) ... ", sToType.c_str() );
    nsCOMPtr<NS_IF_TO> pIF(0);

    nsCOMPtr<NS_IF_TO> pIF1(do_QueryInterface( pType ));

    if ( pIF1.get() ) {
        pIF = pIF1;
    }
    else {
        nsCOMPtr<nsIInterfaceRequestor> pIFReq(do_QueryInterface( pType ));
        nsCOMPtr<NS_IF_TO> pIF2(do_QueryInterface( pIFReq ));
        if ( pIF2.get() ) {
            pIF = pIF2;
        }
    }

    if ( !pIF.get() ) {   printf ( " ERROR " );   }
    printf(" pointer : '%p\n", pIF.get() );
    return pIF;
}

template <typename NS_COM_PTR_FROM>
inline void tryGetInterfaces( NS_COM_PTR_FROM pType, const std::string sTypeName = "" )
{
    printf("tryGetInterfaces from '%s'\n", sTypeName.c_str() );
    tryGetIF<nsIWebNavigation>(pType, "nsIWebNavigation");
    tryGetIF<nsIWebBrowser>(pType, "nsIWebBrowser");
    tryGetIF<nsIDocShell>(pType, "nsIDocShell");
    tryGetIF<nsIDocShellTreeItem>(pType, "nsIDocShellTreeItem");
    tryGetIF<nsIWebBrowserChrome>(pType, "nsIWebBrowserChrome");
    tryGetIF<nsIXULWindow>(pType, "nsIXULWindow");
    tryGetIF<nsIDOMWindowInternal>( pType, "nsIDOMWindowInternal" );
    tryGetIF<nsIAppShell>( pType, "nsIAppShell" );
    tryGetIF<nsIXULBrowserWindow>( pType, "nsIXULBrowserWindow" );

}

// -------------------------------------------
// --- Get primary (Xul) windows functions ---
// -------------------------------------------
nsCOMPtr<nsIDOMWindowInternal>  getDOMWindowInternalByHref  ( const nsString& wsHref );
nsCOMPtr<nsIDOMWindowInternal>  getDOMWindowInternalByHref  ( const std::string& sHref );

nsCOMPtr<nsIXULWindow>          getXulWinByHref             ( const nsString& wsHref );
nsCOMPtr<nsIXULWindow>          getXulWinByHref             ( const std::string& sHref );


// ---------------------------
// --- XulWindow functions ---
// ---------------------------
std::string                     getCurrentUri               ( nsCOMPtr<nsIXULWindow> pXulWin );



// ------------------------------
// --- Get Interfaces helpers ---
// ------------------------------
// --- nsIDOMWindowInternal ---
nsCOMPtr<nsIDOMDocument>            getDOMDocument      ( nsCOMPtr<nsIDOMWindowInternal> pWinInt );
nsCOMPtr<nsIDOMWindow>              getContent          ( nsCOMPtr<nsIDOMWindowInternal> pWinInt );
nsCOMPtr<nsIDOMWindowCollection>    getFrames           ( nsCOMPtr<nsIDOMWindowInternal> pWinInt );
nsCOMPtr<nsIDOMWindow>              getDomWindowById    ( nsCOMPtr<nsIDOMWindowInternal> pWinInt, const std::string& sID );

// --- nsIDOMDocument ---
nsCOMPtr<nsIDOMElement>             getDOMElementById   ( nsCOMPtr<nsIDOMDocument> pDomDoc, const std::string sID );
nsCOMPtr<nsIDOMDocumentType>        getDoctype          ( nsCOMPtr<nsIDOMDocument> pDomDoc );

// --- nsIDOMWindowCollection ---
nsCOMPtr<nsIDOMWindow>              namedItem           ( nsCOMPtr<nsIDOMWindowCollection> pDOMWindowCollection, const std::string sID );

// --- nsIDOMWindow ---
nsCOMPtr<nsIDOMDocument>            getDocument         ( nsCOMPtr<nsIDOMWindow> pWin );

// --- nsIDOMDocumentView ---
nsCOMPtr<nsIDOMAbstractView>        getDefaultView      ( nsCOMPtr<nsIDOMDocumentView> pDomDocumentView );

// --------------------------------
// --- Navigation/Uri functions ---
// --------------------------------
std::string getCurrentURI   ( nsCOMPtr<nsIWebNavigation> pWebNav );
bool        loadURI         ( nsCOMPtr<nsIWebNavigation> pWebNav, const std::string& sUri, PRUint32 aLoadFlags );
bool        loadURI         ( nsCOMPtr<nsIWebNavigation> pWebNav, const std::string& sUri );




//template <typename NS_IF_TO, typename NS_COM_PTR_FROM >
//nsCOMPtr<NS_IF_TO>
//tryGetIFIndirect( NS_COM_PTR_FROM pType, const std::string sToType = "" )
//{
//    printf("tryGetIF (%s) ... ", sToType.c_str() );
//    nsCOMPtr<nsIInterfaceRequestor> pIFReq(do_QueryInterface( pType ));

//    nsCOMPtr<NS_IF_TO> pIF(do_QueryInterface( pIFReq ));
//    if ( !pIF.get() ) {   printf ( " ERROR " );   }

//    printf(" pointer : '%p\n", pIF.get() );
//    return pIF;
//}


//template <typename NS_IF_TO, typename NS_COM_PTR_FROM >
//nsCOMPtr<NS_IF_TO>
//tryGetIFDirect( NS_COM_PTR_FROM pType, const std::string sToType = "" )
//{
//    printf("tryGetIFDirect (%s) ... ", sToType.c_str() );
//    nsCOMPtr<NS_IF_TO> pIF(do_QueryInterface( pType ));
//    if ( !pIF.get() ) {   printf ( " ERROR " );   }

//    printf(" pointer : '%p\n", pIF.get() );
//    return pIF;
//}
