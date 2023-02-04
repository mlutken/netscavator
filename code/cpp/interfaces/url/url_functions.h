#ifndef _URL_FUNCTIONS_H_
#define _URL_FUNCTIONS_H_

#include <string>
#include <boost/shared_ptr.hpp>

#include "Url.h"


namespace boost { namespace process {
class child;
}} // end boost and process namespaces

namespace crawl {  

typedef boost::shared_ptr<std::string>	str_ptr_t;


/** unit Url_functions.h
Free functions for downloading, testing and URL manipulation.
XXX Detailed description here ... XXX
\author Veriquin */

#ifdef USE_CURL
str_ptr_t				download_url		( const Url& Url );
#endif

//str_ptr_t				download_Url2		( const Url& Url );
// str_ptr_t				download_url_wget	( const Url& Url );
// int						download_url_wget	( std::string const& Url, std::string& sData );
// int						download_Url		( const std::string& sUrl, bool	bQuiet, std::string& sDest );
// int						download_Url		( const std::string& sUrl, bool bQuiet, const boost::filesystem::path filePath );
// bool					linkValid			( const std::string& sUrl );
// boost::process::child	open_Url			( const Url& Url);
// boost::process::child	open_Url			( const Url& Url);

// inline 
// int		download_Url(	const Url& Url, 
// 						bool	bQuiet, 
// 						std::string& sDest )
// {
// 	return download_Url ( Url.string(), bQuiet, sDest );
// }


} // END namespace crawl


#endif // _URL_FUNCTIONS_H_

