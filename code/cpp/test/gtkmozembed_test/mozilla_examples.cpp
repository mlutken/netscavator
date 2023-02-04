

// about:cache

#include <iostream>

// mozilla specific headers
#include "nsIDOMKeyEvent.h"
#include "nsIDOMMouseEvent.h"
#include "nsIDOMUIEvent.h"
#include <nsCOMPtr.h>
#include <nsIDOMWindow.h>
#include <nsIDOMDocument.h>
#include <nsIDOMDOMImplementation.h>
#include <nsXPCOMGlue.h>

#include "nsStringAPI.h"
#include "nsEmbedString.h"
#include "nsIDOMNodeList.h"
#include "nsIDOMElement.h"
#include "nsIDOMNode.h"
#include "nsIDOMNamedNodeMap.h"
#include "nsIServiceManager.h"
#include <nsICacheService.h>
#include <nsICache.h>
#include <nsICacheEntryDescriptor.h>
#include <nsICacheSession.h>
#include <nsIInputStream.h>
#include <nsIScriptGlobalObjectOwner.h>
#include <nsIInterfaceRequestorUtils.h>
#include <nsIScriptContext.h>
#include <nsIScriptGlobalObject.h>
#include <jspubtd.h>
#include <nsIDOMHTMLFormElement.h>
#include <nsIDOMHTMLCollection.h>

#include <string>

void ex_javascript1(nsIWebBrowser*  iWebBrowser )
{
	nsCOMPtr<nsIScriptGlobalObjectOwner> theGlobalObjectOwner(do_GetInterface(iWebBrowser));
	
	if (theGlobalObjectOwner) {
		//JSFunction* jsf;
  		nsIScriptGlobalObject* theGlobalObject = theGlobalObjectOwner->GetScriptGlobalObject();
		nsIScriptContext* theScriptContext =theGlobalObject->GetContext();
        
        printf("ML: ex_javascript1: %p %p\n", theGlobalObject, theScriptContext );
        
		nsIPrincipal *thePrincipal = nsnull;
		PRBool IsUndefined;
		nsString theReturnValue;
		nsresult rv = theScriptContext->EvaluateString( 
//				NS_LITERAL_STRING("marley('http://www.yahoo.fr');"),
				NS_LITERAL_STRING("bob();"),
				nsnull,
				thePrincipal, 
				"", 
				1, 
				JSVERSION_DEFAULT, 
				&theReturnValue,
				&IsUndefined );
	}
}

//  virtual nsresult EvaluateString(const nsAString& aScript,
//                                   void *aScopeObject,
//                                   nsIPrincipal *aPrincipal,
//                                   const char *aURL,
//                                   PRUint32 aLineNo,
//                                   PRUint32 aVersion,
//                                   nsAString *aRetValue,
//                                   PRBool* aIsUndefined) = 0;
// 
//   // Note JS bigotry remains here - 'void *aRetValue' is assumed to be a
//   // jsval.  This must move to JSObject before it can be made agnostic.
//   virtual nsresult EvaluateStringWithValue(const nsAString& aScript,
//                                            void *aScopeObject,
//                                            nsIPrincipal *aPrincipal,
//                                            const char *aURL,
//                                            PRUint32 aLineNo,
//                                            PRUint32 aVersion,
//                                            void* aRetValue,
//                                            PRBool* aIsUndefined) = 0;

static const nsIID kICacheServiceIID = NS_ICACHESERVICE_IID;

static void
ex_nsCache()
{
	
//	return ;
	
 	nsresult rv;
	nsCOMPtr<nsIServiceManager> servMan;
	rv = NS_GetServiceManager(getter_AddRefs(servMan));
	if (NS_FAILED(rv)) {
		printf ( "ERROR 1\n" ); return;
	}

	nsCOMPtr<nsICacheService> cacheService;
	rv = servMan->GetServiceByContractID( "@mozilla.org/network/cache-service;1"	, NS_GET_IID(nsICacheService), getter_AddRefs(cacheService));
	if (NS_FAILED(rv)) {
		printf ( "ERROR 2\n" ); return;
	}
	printf("CacheService\n");
	nsCOMPtr<nsICacheSession> cacheSession;
	
	
	nsCacheStoragePolicy storagePolicy = nsICache::STORE_ON_DISK;
	
    const char* sessionName = "HTTP";
    switch (storagePolicy) {
    case nsICache::STORE_IN_MEMORY:
        sessionName = "HTTP-memory-only";
        break;
    case nsICache::STORE_OFFLINE:
        sessionName = "HTTP-offline";
        break;
    default:
        break;
    }
	
	rv = cacheService->CreateSession( sessionName , storagePolicy, nsICache::STREAM_BASED , getter_AddRefs(cacheSession) );
//	rv = cacheService->CreateSession( "webminer", nsICache::STORE_OFFLINE, nsICache::STREAM_BASED , getter_AddRefs(cacheSession) );
	if (NS_FAILED(rv)) {
		printf ( "ERROR 3\n" ); return;
	}
	
	nsCAutoString cacheKey;
//	NS_CStringSetData ( cacheKey, "http://www.doxys.dk/" );
    
    const char* szUrl = "http://www.doxys.dk/doxys_homepage/index.html";
	cacheKey.Append( szUrl );
//	NS_CStringSetData ( cacheKey, "http://www.doxys.dk/doxys_homepage/index.html" );
	
	
	printf ( "cacheKey: %s\n", cacheKey.get() ) ;
	
	nsCOMPtr<nsICacheEntryDescriptor> cacheEntry;
	rv = cacheSession->OpenCacheEntry(cacheKey, nsICache::ACCESS_READ, PR_TRUE, getter_AddRefs(cacheEntry));
	
	printf ( "rv: %d\n", rv );
	
	if (NS_FAILED(rv)) {
		printf ( "ERROR 4: %d\n", rv ); return;
	}
	
	nsCOMPtr<nsIInputStream>	cacheEntryStream;
	rv = cacheEntry->OpenInputStream( 0, getter_AddRefs(cacheEntryStream) );
	if (NS_FAILED(rv)) {
		printf ( "ERROR 5: %d\n", rv ); return;
	}
	
	PRUint32 	iStreamLen;
	PRUint32 	iBytesRead;
	PRBool		bNonBlocking;
	
	rv = cacheEntryStream->Available( &iStreamLen );
	if (NS_FAILED(rv)) {
		printf ( "ERROR 6: %d\n", rv ); return;
	}
	rv = cacheEntryStream->IsNonBlocking( &bNonBlocking );	
	
	printf("iStreamLen: %d   bNonBlocking: %d\n", iStreamLen, bNonBlocking);
	
	char szBuf[iStreamLen+1];
	
	rv = cacheEntryStream->Read( szBuf, iStreamLen, &iBytesRead);
	if (NS_FAILED(rv)) {
		printf ( "ERROR 7: %d\n", rv ); return;
	}
	printf("iBytesRead: %d\n", iBytesRead );
	printf("----------------------------\n");
	printf("%s\n", szBuf );
	printf("----------------------------\n");
}



static void GetStringValue ( nsACString& aValue )
{
	NS_CStringSetData ( aValue, "GetValue" );
}

//char *ToNewCString(nsACString&)

static void
ex_nsEmbedString()
{

	printf ( "Examples: nsEmbedString\n " );
	// This next part illustrates the nsEmbedString:
	nsEmbedString foopy;
	foopy.Append ( PRUnichar ( 'f' ) );
	foopy.Append ( PRUnichar ( 'o' ) );
	foopy.Append ( PRUnichar ( 'o' ) );
	foopy.Append ( PRUnichar ( 'p' ) );
	foopy.Append ( PRUnichar ( 'y' ) );

	const PRUnichar* f = foopy.get();
	PRUint32 l = foopy.Length();
	printf ( "%c%c%c%c%c %d\n", char ( f[0] ), char ( f[1] ), char ( f[2] ), char ( f[3] ), char ( f[4] ), l );
	
//	printf ( "foopy: %s\n", f3);

	nsEmbedCString foopy2;
	GetStringValue ( foopy2 );


	//foopy2.AppendLiteral("foopy");
	const char* f2 = foopy2.get();
	PRUint32 l2 = foopy2.Length();

	printf ( "ML: %s %d\n", f2, l2 );
	
	nsEmbedCString myStr;
	NS_CStringSetData ( myStr, "Mozilla strings er noget pis" );
	printf ( "myStr: %s\n", myStr.get() );
	
//	nsEmbedString myStr2;
//	NS_StringSetData ( myStr2, "Mozilla strings er noget pis" );
	//printf ( "myStr: %s\n", myStr.get() );
	
	
	
//	const nsAString& firstFive = Substring(foopy2, 0, 5);
	
	char* szTest = ToNewCString( foopy2 );
	printf ( "szTest: %s\n", szTest );
	NS_Free ( szTest );
	
	

	
}



static void
ex_nsIDOMWindow_Name( nsIDOMWindow* domWindow )
{
	printf ( "Example: nsIDOMWindow Name\n " );
	nsEmbedString sName;
//	nsAutoString sName;
	domWindow->GetName( sName );
	if ( sName.IsEmpty() ) {
		printf("EMPTY\n");
		domWindow->SetName( NS_ConvertASCIItoUTF16("DOM WINDOW NAME") );
	}
	else {
		printf("HAS NAME\n");
		printf("NAME: %s\n", NS_ConvertUTF16toUTF8(sName).get());
		nsCAutoString sCName = NS_LossyConvertUTF16toASCII( sName );	
		char* szName = ToNewCString( sCName );
		printf ( "szName: %s\n", szName );
		NS_Free ( szName );
	}
}


static void 
ex_nsIDOMDocument_Intro ( nsIDOMDocument* domDoc )
{
	nsresult res;
	printf("Get Document \n");
	nsCOMPtr<nsIDOMNodeList> nodelist;
//	res = domDoc->GetElementsByTagName(NS_LITERAL_STRING("*"),getter_AddRefs(nodelist));	// All elements
	res = domDoc->GetElementsByTagName(NS_LITERAL_STRING("a"),getter_AddRefs(nodelist));	// a elements
	
	PRUint32 index;
	PRUint32 length;
 	res = nodelist->GetLength(&length);
 	printf("Get nodelist num[%d] res[%d]\n",length,res);
 	for(index=0;index<length;index++)
 	{
 		nsCOMPtr<nsIDOMNode> node;
		res=nodelist->Item(index,getter_AddRefs(node));
		
		nsEmbedString sNodeName, sNodeValue;
		node->GetNodeName(sNodeName);
		node->GetNodeValue(sNodeValue);
		printf("Node(name, value): ( %s , %s )\n", NS_ConvertUTF16toUTF8(sNodeName).get(), NS_ConvertUTF16toUTF8(sNodeValue).get());
		
// 		PRUint32 iChildIndex;
// 		PRUint32 iChildLength;
// 		nsCOMPtr<nsIDOMNodeList> childNodeList;
// 		res = node->GetChildNodes( getter_AddRefs(childNodeList) );
// 		res = childNodeList->GetLength(&iChildLength);
// 		printf("Get childNodeList num[%d] res[%d]\n", iChildLength, res);
// 		for ( iChildIndex=0 ; iChildIndex < iChildLength; iChildIndex++ )
// 		{
// 			nsCOMPtr<nsIDOMNode> childNode;
// 			res=childNodeList->Item(index,getter_AddRefs(childNode));
// 			nsEmbedString sChildNodeName, sChildNodeValue;
// 			node->GetNodeName(sChildNodeName);
// 			node->GetNodeValue(sChildNodeValue);
// 			printf("ChildNode(name, value): ( %s , %s )\n", NS_ConvertUTF16toUTF8(sChildNodeName).get(), NS_ConvertUTF16toUTF8(sChildNodeValue).get());
// 		}		
		
		PRUint32 iAttribIndex;
		PRUint32 iAttribLength;
		nsCOMPtr<nsIDOMNamedNodeMap> nodeAttribs;
		res = node->GetAttributes( getter_AddRefs(nodeAttribs) );	
		
		nodeAttribs->GetLength ( &iAttribLength ); 
		
		//printf("iAttribLength: %d\n", iAttribLength );
		for ( iAttribIndex=0 ; iAttribIndex < iAttribLength; iAttribIndex++ )
		{
			nsCOMPtr<nsIDOMNode> attribNode;
			res = nodeAttribs->Item( iAttribIndex, getter_AddRefs( attribNode ));
			nsEmbedString s1, s2;
			attribNode->GetNodeName(s1);
			attribNode->GetNodeValue(s2);
			printf("attribNode(name, value): ( %s , %s )\n", NS_ConvertUTF16toUTF8(s1).get(), NS_ConvertUTF16toUTF8(s2).get());
		}		
		
	
		NS_NAMED_LITERAL_STRING(hrefAttr,"href");
		nsEmbedString sHref;
		nsCOMPtr<nsIDOMElement> elt = do_QueryInterface(node);
		res = elt->GetAttribute( hrefAttr, sHref );
		
		//elt->GetAttribute(
		
		nsEmbedString sTagName;
		elt->GetTagName ( sTagName ) ;
//		printf("sTagName: %s\n", NS_ConvertUTF16toUTF8(sTagName).get());
		
		printf("node[%d] %s res[%d]\n", index, NS_ConvertUTF16toUTF8(sHref).get(), res);
//		printf("node[%d] %s\n", index, NS_ConvertUTF16toUTF8(sHref).get() );
 	}

}


static void 
ex_FormGet ( nsIDOMDocument* domDoc )
{
	nsresult res;
	printf("Form Get exmaple: Use file 'FormGetTest.html' as loaded page. \n");
	nsCOMPtr<nsIDOMNodeList> nodelist;
	res = domDoc->GetElementsByTagName(NS_LITERAL_STRING("*"),getter_AddRefs(nodelist));	// All elements
//	res = domDoc->GetElementsByTagName(NS_LITERAL_STRING("form"),getter_AddRefs(nodelist));	// a elements
	
	PRUint32 index;
	PRUint32 length;
 	res = nodelist->GetLength(&length);
 	printf("Get nodelist num[%d] res[%d]\n",length,res);
 	for(index=0;index<length;index++)
 	{
 		nsCOMPtr<nsIDOMNode> node;
		res=nodelist->Item(index,getter_AddRefs(node));
		
		nsEmbedString sNodeName, sNodeValue;
		node->GetNodeName(sNodeName);
		node->GetNodeValue(sNodeValue);
		printf("Node(name, value): ( %s , %s )\n", NS_ConvertUTF16toUTF8(sNodeName).get(), NS_ConvertUTF16toUTF8(sNodeValue).get());
	
		
		PRUint32 iAttribIndex;
		PRUint32 iAttribLength;
		nsCOMPtr<nsIDOMNamedNodeMap> nodeAttribs;
		res = node->GetAttributes( getter_AddRefs(nodeAttribs) );	
		
		nodeAttribs->GetLength ( &iAttribLength ); 
		
		//printf("iAttribLength: %d\n", iAttribLength );
		for ( iAttribIndex=0 ; iAttribIndex < iAttribLength; iAttribIndex++ )
		{
			nsCOMPtr<nsIDOMNode> attribNode;
			res = nodeAttribs->Item( iAttribIndex, getter_AddRefs( attribNode ));
			nsEmbedString s1, s2;
			attribNode->GetNodeName(s1);
			attribNode->GetNodeValue(s2);
			printf("attribNode(name, value): ( %s , %s )\n", NS_ConvertUTF16toUTF8(s1).get(), NS_ConvertUTF16toUTF8(s2).get());
		}		
		
	
		NS_NAMED_LITERAL_STRING(hrefAttr,"href");
		nsEmbedString sHref;
		nsCOMPtr<nsIDOMElement> elt = do_QueryInterface(node);
		res = elt->GetAttribute( hrefAttr, sHref );
		
		nsCOMPtr<nsIDOMHTMLFormElement> formElem = do_QueryInterface(node);
		if ( formElem ) {
			printf( "IS formElem\n" );
			nsCOMPtr<nsIDOMHTMLCollection>	formElements;
			res = formElem->GetElements( getter_AddRefs(formElements) );
			if (NS_FAILED(res)) {
				printf ( "ERROR: %d\n", res ); return;
			}
			PRUint32 iLenFormElements;
			PRUint32 iFormElementsIndex;
			formElements->GetLength ( &iLenFormElements );
			printf("formElements.Length: %d\n", iLenFormElements );
			for ( iFormElementsIndex=0 ; iFormElementsIndex < iLenFormElements; iFormElementsIndex++ )
			{
				nsCOMPtr<nsIDOMNode> formNode;
				res = formElements->Item( iFormElementsIndex, getter_AddRefs( formNode ));
				if (NS_FAILED(res)) {
					printf ( "ERROR 2: %d\n", res ); return;
				}
				nsEmbedString s1, s2;
				formNode->GetNodeName(s1);
				formNode->GetNodeValue(s2);
				printf("formNode(name, value): ( %s , %s )\n", NS_ConvertUTF16toUTF8(s1).get(), NS_ConvertUTF16toUTF8(s2).get());
				
				PRUint32 iFormNodeAttribIndex;
				PRUint32 iFormNodeAttribLength;
				nsCOMPtr<nsIDOMNamedNodeMap> formNodeAttribs;
				res = formNode->GetAttributes( getter_AddRefs(formNodeAttribs) );	
				formNodeAttribs->GetLength ( &iFormNodeAttribLength ); 
				
				printf("iFormNodeAttribLength: %d\n", iFormNodeAttribLength );
				for ( iFormNodeAttribIndex=0 ; iFormNodeAttribIndex < iFormNodeAttribLength; iFormNodeAttribIndex++ )
				{
					nsCOMPtr<nsIDOMNode> attribFormNode;
					res = formNodeAttribs->Item( iFormNodeAttribIndex, getter_AddRefs( attribFormNode ));
					nsEmbedString s1, s2;
					attribFormNode->GetNodeName(s1);
					attribFormNode->GetNodeValue(s2);
					std::string sNodeName = NS_ConvertUTF16toUTF8(s1).get();
					if ( sNodeName == "value" && (iFormElementsIndex == 0)) {
						printf("SSSSSSSSSS\n");
						attribFormNode->SetNodeValue (NS_ConvertASCIItoUTF16("Martin Lutken"));
					}
					
					printf("attribFormNode(name, value): ( %s , %s )\n", NS_ConvertUTF16toUTF8(s1).get(), NS_ConvertUTF16toUTF8(s2).get());
				}		
			}
			formElem->Submit();
			printf( "END formElem\n\n" );
		
		}
		
		
		//elt->GetAttribute(
		
		nsEmbedString sTagName;
		elt->GetTagName ( sTagName ) ;
//		printf("sTagName: %s\n", NS_ConvertUTF16toUTF8(sTagName).get());
		
		printf("node[%d] %s res[%d]\n", index, NS_ConvertUTF16toUTF8(sHref).get(), res);
//		printf("node[%d] %s\n", index, NS_ConvertUTF16toUTF8(sHref).get() );
 	}

}

/*
Creating Components in C++

Components can be created in C++ using the do_CreateInstance function.

nsCOMPtr<nsILocalFile> theFile;
theFile = do_CreateInstance("@mozilla.org/file/local;1");

This function creates a new component with the corresponding contract ID. The magic of nsCOMPtrs will handle QueryInterface for you. There is also a corresponding getService function as well:

nsCOMPtr<nsIRDFService> rdfService;
rdfService = do_GetService("@mozilla.org/rdf/rdf-service;1");

If you are working with Mozilla source code, most components have a macro defined which can be used in place of the corresponding contract ID string. For example, NS_LOCAL_FILE_CONTRACTID may be used instead of "@mozilla.org/file/local;1".

In native code, function names always begin with a capital letter, even if the interface was defined with the name in lowercase. Attributes are retrieved and modified using methods of the form Get<attribute name> and Set<attribute name>. For example, to get an attribute called 'count' use the GetCount method.

The result of a interface's function is returned as the last argument to the function. The returned value of an interface function is an nsresult which is an integer error code. For instance to get a datasource from the RDF service:

nsCOMPtr<nsIRDFDataSource> dsource;
nsresult rv = rdfService->GetDataSource("rdf:bookmarks", getter_AddRefs(dsource));

Although the GetDataSource interface is defined as returning a nsIRDFDataSource, it is returned as the last argument, and an success or error code is returned from the function. Note that some methods don't follow this convention, these are marked with [notxpcom] in the reference. 
*/













static void ex_nsCache1()
{
 	nsresult rv;
	nsCOMPtr<nsIServiceManager> servMan;
	rv = NS_GetServiceManager(getter_AddRefs(servMan));
	if (NS_FAILED(rv)) {
		printf ( "ERROR 1\n" ); return;
	}

	nsCOMPtr<nsICacheService> cacheService;
	rv = servMan->GetServiceByContractID( "@mozilla.org/network/cache-service;1"	, NS_GET_IID(nsICacheService), getter_AddRefs(cacheService));
	if (NS_FAILED(rv)) {
		printf ( "ERROR 2\n" ); return;
	}
	nsCOMPtr<nsICacheSession> cacheSession;
	
	
	nsCacheStoragePolicy storagePolicy = nsICache::STORE_ON_DISK;
	
    const char* sessionName = "HTTP";
    switch (storagePolicy) {
    case nsICache::STORE_IN_MEMORY:
        sessionName = "HTTP-memory-only";
        break;
    case nsICache::STORE_OFFLINE:
        sessionName = "HTTP-offline";
        break;
    default:
        break;
    }
	
	rv = cacheService->CreateSession( sessionName , storagePolicy, nsICache::STREAM_BASED , getter_AddRefs(cacheSession) );
	if (NS_FAILED(rv)) {
		printf ( "ERROR 3\n" ); return;
	}
	
	nsCAutoString cacheKey;
    const char* szUrl = "http://www.doxys.dk/doxys_homepage/index.html";
	cacheKey.Append( szUrl );
	nsCOMPtr<nsICacheEntryDescriptor> cacheEntry;
	
	rv = cacheSession->OpenCacheEntry(cacheKey, nsICache::ACCESS_READ, PR_TRUE, getter_AddRefs(cacheEntry));
	// FAILS HERE with pages like www.google.com 
	if (NS_FAILED(rv)) {
		printf ( "ERROR 4: %d\n", rv ); return;
	}
	
	nsCOMPtr<nsIInputStream>	cacheEntryStream;
	rv = cacheEntry->OpenInputStream( 0, getter_AddRefs(cacheEntryStream) );
	if (NS_FAILED(rv)) {
		printf ( "ERROR 5: %d\n", rv ); return;
	}
	
	PRUint32 	iStreamLen;
	PRUint32 	iBytesRead;
	PRBool		bNonBlocking;
	
	rv = cacheEntryStream->Available( &iStreamLen );
	if (NS_FAILED(rv)) {
		printf ( "ERROR 6: %d\n", rv ); return;
	}
	rv = cacheEntryStream->IsNonBlocking( &bNonBlocking );	
	
	char szBuf[iStreamLen+1];
	rv = cacheEntryStream->Read( szBuf, iStreamLen, &iBytesRead);
	if (NS_FAILED(rv)) {
		printf ( "ERROR 7: %d\n", rv ); return;
	}
	printf("iBytesRead: %d\n", iBytesRead );
	printf("----------------------------\n");
	printf("%s\n", szBuf );
	printf("----------------------------\n");
}

