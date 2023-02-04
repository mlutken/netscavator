
#include "WebNavigation.h"	

#include <iostream>
#include <boost/algorithm/string.hpp>
#include <boost/process.hpp>

// // #include <xpcom/nsIServiceManager.h>
// // #include <xpcom/nsIInputStream.h>
// // #include <nkcache/nsICacheService.h>
// // #include <nkcache/nsICache.h>
// // #include <nkcache/nsICacheEntryDescriptor.h>
// // #include <nkcache/nsICacheSession.h>

#include <nsIServiceManager.h>
#include <nsIInputStream.h>
#include <nsICacheService.h>
#include <nsICache.h>
#include <nsICacheEntryDescriptor.h>
#include <nsICacheSession.h>

// Example from Tdiy code
//  const char * utf8_html = NULL;
//  NS_CStringGetData(aHtml, &utf8_html);	// Get  nsACString to char*

/*
std::string 	
WebNavigation::currentURIPageSource() const
{
 	nsresult rv;
	nsCOMPtr<nsIServiceManager> servMan;
	rv = NS_GetServiceManager(getter_AddRefs(servMan));
	if (NS_FAILED(rv)) {	printf ( "ERROR 1\n" ); return "";	}

	nsCOMPtr<nsICacheService> cacheService;
	rv = servMan->GetServiceByContractID( "@mozilla.org/network/cache-service;1"	, NS_GET_IID(nsICacheService), getter_AddRefs(cacheService));
	if (NS_FAILED(rv)) {	printf ( "ERROR 2\n" ); return "";	}
	nsCOMPtr<nsICacheSession> cacheSession;
	 
	nsCacheStoragePolicy storagePolicy = nsICache::STORE_ON_DISK;
	//nsCacheStoragePolicy storagePolicy = nsICache::STORE_ANYWHERE;
	
	
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
	if (NS_FAILED(rv)) { printf ( "ERROR 3\n" ); return ""; }
	
//	nsCAutoString cacheKey;
	nsEmbedCString cacheKey;
	
	std::string sURI = currentURIAsString();
//	boost::trim_right_if( sURI, boost::is_any_of( std::string("/") ) );

	cacheKey.Append( sURI.c_str() );
//	printf("SSSSSSSSSS: cacheKey: %s\n", cacheKey.get() );
	
	nsCOMPtr<nsICacheEntryDescriptor> cacheEntry;
	rv = cacheSession->OpenCacheEntry(cacheKey, nsICache::ACCESS_READ, nsICache::BLOCKING, getter_AddRefs(cacheEntry));
	
	
	
	if (NS_FAILED(rv)) { printf ( "ERROR 4: %d\n", rv ); return ""; }
	
	nsCOMPtr<nsIInputStream>	cacheEntryStream;
	rv = cacheEntry->OpenInputStream( 0, getter_AddRefs(cacheEntryStream) );
	
	if (NS_FAILED(rv)) { printf ( "ERROR 5: %d\n", rv ); return ""; }
	
	PRUint32 	iStreamLen;
	PRUint32 	iBytesRead;
	PRBool		bNonBlocking;
	
	rv = cacheEntryStream->Available( &iStreamLen );
	if (NS_FAILED(rv)) { printf ( "ERROR 6: %d\n", rv ); return ""; }
	
	char szBuf[iStreamLen+1];
	cacheEntryStream->IsNonBlocking( &bNonBlocking );	
	
	rv = cacheEntryStream->Read( szBuf, iStreamLen, &iBytesRead);
	if (NS_FAILED(rv)) { printf ( "ERROR 7: %d\n", rv ); return "";	}
	
	//	printf("iBytesRead: %d\n", iBytesRead );
	return std::string(szBuf);
}
*/





/// Simple loadURI overload.
/// \return True if call succeded.
bool WebNavigation::loadURI( const std::string& sURI, boost::uint32_t aLoadFlags ) 
{
	////		std::cout << boost::format ( "WebNavigation::loadURI URL: %1%\n") % sURI;
	////nsresult rv = ifMoz()->LoadURI( NS_ConvertASCIItoUTF16( sURI.c_str() ).get(), aLoadFlags, 0, 0, 0);
	nsresult rv = ifMoz()->LoadURI( NS_ConvertUTF8toUTF16( sURI.c_str() ).get(), aLoadFlags, 0, 0, 0);
    if ( NS_FAILED(rv) )
        return false;
    else
        return true;
}

std::string 	WebNavigation::currentURIAsString() const
{
	nsCString		uriString;
	nsCOMPtr<nsIURI> 	pIURI;
	ifMoz()->GetCurrentURI( getter_AddRefs(pIURI) );
	
////	pIURI->GetAsciiSpec( uriString );
 	pIURI->GetSpec( uriString );
	
	return std::string ( uriString.get() );
}



// std::string 	
// WebNavigation::currentURIPageSourceWget() const
// {
// 	namespace bp = ::boost::process;
// 	std::string sPageData;
// 	bp::command_line cl("wget");
// 	cl.argument( std::string("-q"));
// 	cl.argument( std::string("-T"));
// 	cl.argument( std::string("10"));
// 	cl.argument( std::string("-t"));
// 	cl.argument( std::string("3"));
// 	cl.argument( std::string("-O"));
// 	cl.argument( std::string("-"));
// 	cl.argument( currentURIAsString() );
// 	
// 	bp::launcher l;
// 	l.set_stdout_behavior(bp::redirect_stream);
// 	l.set_merge_out_err(true);
// 	bp::child c = l.start(cl);
// 	
// 	bp::pistream& is = c.get_stdout();
// 	std::string sLine;
// 	while (std::getline(is, sLine)) {
// 		sLine.append("\n");
// 		sPageData.append( sLine );
// 	}
// 	bp::status s = c.wait();
// 
// 	return sPageData;
// }

