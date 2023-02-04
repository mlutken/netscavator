#include "url_string_functions.h"

#include <iostream> // Debug only 

#include <boost/assign/list_of.hpp> 
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>



namespace crawl { 

// --------------------------------------------------------------------------
// --- Parse Helper Functions (not in header since only used within here) ---
// --------------------------------------------------------------------------

/** Return true if string can only represent the beginning of a path.
In case false is returned the string could still represent a path, but then it 
depends on the context (ie. within the whole URL. */
bool is_definitely_a_path( const std::string& s, std::string::size_type iCurPos  )
{
	using namespace std;
	if ( (s.size() - iCurPos  >= 2) && s[iCurPos] == '.' && s[iCurPos+1] == '.'	)	return true;	// ..
	if ( (s.size() - iCurPos  >= 2) && s[iCurPos] == '.' && s[iCurPos+1] == '/'	)	return true;	// ./
	if ( (s.size() - iCurPos  >= 1) && s[iCurPos] == '/'						)	return true;	// /
	return false;	
}

/** Return true if string can only represent the beginning of a hash string. */
bool is_hash( const std::string& s, std::string::size_type iCurPos )
{
	if ( (s.size() - iCurPos >= 1) && s[iCurPos] == '#'	)	return true;
	return false;	
}

/** Return true if string can only represent the beginning of a prameters string. */
bool is_parameters( const std::string& s, std::string::size_type	iCurPos )
{
	if ( (s.size() - iCurPos >= 1) && s[iCurPos] == '?'	)	return true;
	return false;	
}

// ----------------------
// --- Info Functions ---
// ----------------------

/** Test if protocol is valid */
bool is_valid_protocol ( const std::string& sProtocol )
{
	if ( g_valid_protocols.find( sProtocol ) == g_valid_protocols.end() )	return false;
	else																	return true;
}


// -----------------------
// --- Parse Functions ---
// -----------------------


/** Parse for and return the protocol part of an URL string. 
Assumes that \a iCurPos is allready advanced to beginning of possible protocol substring. 
\see crawl::Url::G_validProtocols
return String containing a valid protocol like 'http://' or an empty string if no valid protocol was found.*/ 
std::string parse_protocol(
	const std::string&		sUrl,		///< [in]    String representation of URL to search for protocol in.
	std::string::size_type&	iCurPos		///< [inout] Current string pos. Searches from here and modifies to last position in protocol if possible else  else unchanged.
) 
{
	using namespace std;
    using boost::format;
////    if ( boost::istarts_with( sUrl, "mailto:") )									return "";
    
    if ( is_parameters( sUrl, iCurPos ) || is_definitely_a_path( sUrl, iCurPos ) )	return ""; 
	if ( iCurPos == string::npos )													return "";
	string sProtocol("");

	string::size_type i = sUrl.find(':', iCurPos);		// Find char from position iCurPos in string
	if ( i != string::npos && ( i +2 < sUrl.size()) ) { 
		sProtocol = sUrl.substr(iCurPos, i - iCurPos );
//		sProtocol = sUrl.substr(iCurPos, i - iCurPos + 3);
		if ( !is_valid_protocol(sProtocol) ) sProtocol = "";
		iCurPos = i + 2; // Advance to last position in protocol.
	}
	return sProtocol;
}

/** Search/parse for and return the site part of an URL string. Assumes that \a iCurPos 
is allready advanced past a possible protocol and at the beginning of the site substring. 
Ofcourse if you know the URL string to {not{ contain any protocol then iCurPos can be initialized 
to 0 before calling this function.
return String containing a valid site like 'www.tv2.dk' or an empty string if no valid site was found.*/ 
std::string parse_domain(
	const std::string&		sUrl,		///< [in]    String representation of URL to search for site in.
	std::string::size_type&	iCurPos		///< [inout] Current string pos. Searches from here and modifies to plast osition in site if possible else unchanged.
) 
{
	using namespace std;
    using boost::format;
    
    if ( is_hash( sUrl, iCurPos ) )													return ""; 
    if ( is_parameters( sUrl, iCurPos ) || is_definitely_a_path( sUrl, iCurPos ) )	return ""; 
	if ( iCurPos == string::npos )													return "";
	string sDomain("");

	// Assume that if we find a '/' then it's the start of the path part of the URL
	// Then we just set the substring from iCurPos up the char before the '/' as the site.
    string::size_type i = sUrl.find('/', iCurPos);		// Find char from position iCurPos in string
    if ( i == string::npos ) i = sUrl.find('#', iCurPos);
	if ( i == string::npos ) i = sUrl.find('?', iCurPos);

    string::size_type iDot = sUrl.find('.', iCurPos);	// Find dot '.' int he string
    if ( iDot == string::npos || iDot > i ) return "";  // Only a valid domain if it contains a dot and that dot comes before the domain part ends

	if ( i != string::npos ) { 
		sDomain = sUrl.substr(iCurPos, i - iCurPos);
		iCurPos = i -1;									// Advance to last position in protocol.
	}
	else {	// End of string reached. We assume whole string from iCurPos to end is the site.
		sDomain = sUrl.substr(iCurPos);
		iCurPos = sUrl.size() -1; // Advance to last position in protocol.
	}
	return sDomain;
}

/** Search/parse for and return the path part of an URL string. Assumes that \a iCurPos 
is allready advanced past a possible site and at the beginning of the path substring. 
Ofcourse if you know the URL string to {not{ contain any site then iCurPos can be initialized 
to 0 before calling this function.
return String containing a valid path like '/subdir/somefile.html', '/index.html' or an empty string if no valid path was found.*/ 
std::string parse_path(
	const std::string&		sUrl,		///< [in]    String representation of URL to search for path in.
	std::string::size_type&	iCurPos		///< [inout] Current string pos. Searches from here and modifies to last position in path if possible else unchanged.
) 
{
	using namespace std;
    using boost::format;
    
    if ( is_hash( sUrl, iCurPos ) )			return ""; 
    if ( is_parameters( sUrl, iCurPos ) )	return ""; 
	if ( iCurPos == string::npos )			return "";
	string sPath("");

	// Assume that if we find a '?' then it's the start of the parameters part of the URL
	// Then we just set the substring from iCurPos up the char before the '?' as the path.
	string::size_type i = sUrl.find('?', iCurPos);		// Find char from position iCurPos in string
	if ( i == string::npos ) i = sUrl.find('#', iCurPos);
	
	if ( i != string::npos ) { 
		sPath = sUrl.substr(iCurPos, i - iCurPos);
		iCurPos = i -1; // Advance to last position in site.
	}
	else {	// End of string reached. We assume whole string from iCurPos to end is the path.
		sPath = sUrl.substr(iCurPos);
		iCurPos = sUrl.size() -1;						// Advance to last position in path.
	}
	return sPath;
}


/** Search/parse for and return the subdir part of an URL string. Assumes that \a iCurPos
is allready advanced past a possible site and at the beginning of the path substring.
Ofcourse if you know the URL string to {not{ contain any site then iCurPos can be initialized
to 0 before calling this function.
return String containing a valid subdir like '/subdir/', '/' or an empty string if no valid path was found.*/
std::string parse_subdir(
    const std::string&		sUrl,		///< [in]    String representation of URL to search for subdir   in.
    std::string::size_type&	iCurPos		///< [inout] Current string pos. Searches from here and modifies to last position in path if possible else unchanged.
)
{
    using namespace std;
    using boost::format;

    if ( is_hash( sUrl, iCurPos ) )			return "";
    if ( is_parameters( sUrl, iCurPos ) )	return "";
    if ( iCurPos == string::npos )			return "";
    string sSubDir("");

    // Assume that if we find a '?' then it's the start of the parameters part of the URL
    // Then we just set the substring from iCurPos up the char before the '?' as the subdir.
//    string::size_type i = sUrl.find('?', iCurPos);		// Find char from position iCurPos in string
    string::size_type i = sUrl.rfind( '/' );		// Find char from position iCurPos in string


 //   if ( i == string::npos ) i = sUrl.find('#', iCurPos);

    if ( i != string::npos ) {
        sSubDir = sUrl.substr(iCurPos, i - iCurPos+1);
        iCurPos = i; // Advance to first position in leaf/rest.
    }
    else {	// End of string reached. We assume no explicit subdir, so we manually set it to '/'.
        sSubDir = "/";
        iCurPos = sUrl.size() -1;						// Advance to last position in url.
//        sSubDir = sUrl.substr(iCurPos);
//        iCurPos = sUrl.size() -1;						// Advance to last position in url.
    }
    return sSubDir;
}


/** */
std::string parse_leaf(
    const std::string&		sUrl,		///< [in]    String representation of URL to search for leaf part in.
    std::string::size_type&	iCurPos		///< [inout] Current string pos. Searches from here and modifies to last position in parameters if possible else unchanged.
)
{
    using namespace std;
    string sLeaf = sUrl.substr(iCurPos);
    iCurPos = sUrl.size() -1;						// Advance to last position in url.
    return sLeaf;
}


/** Search/parse for and return the parameters part of an URL string. Assumes that \a iCurPos 
is allready advanced past a possible path and at the beginning of the parameters substring. 
Ofcourse if you know the URL string to {not{ contain any path then iCurPos can be initialized 
to 0 before calling this function.
return String containing a valid parameters like '/subdir/somefile.html', '/index.html' or an empty string if no valid parameters was found.*/ 
std::string parse_parameters(
	const std::string&		sUrl,		///< [in]    String representation of URL to search for parameters in.
	std::string::size_type&	iCurPos		///< [inout] Current string pos. Searches from here and modifies to last position in parameters if possible else unchanged.
) 
{
	using namespace std;
    using boost::format;
    if ( is_hash( sUrl, iCurPos ) )			return ""; 
    if ( !is_parameters( sUrl, iCurPos ) )	return ""; 
	if ( iCurPos == string::npos ) 			return "";
	string sParameters("");

		
	string::size_type i = sUrl.find('#', iCurPos);		// Find char from position iCurPos in string
	if ( i != string::npos ) { 
		sParameters = sUrl.substr(iCurPos, i - iCurPos);
		iCurPos = i -1; // Advance to last position in site.
	}
	else {	// End of string reached. We assume whole string from iCurPos to end is the path.
		sParameters = sUrl.substr(iCurPos);
		iCurPos = sUrl.size() -1;						// Advance to last position in path.
	}

	return sParameters;
}

/** Search/parse for and return the hash part of an URL string. Assumes that \a iCurPos 
is allready advanced past a possible path/parameters and at the beginning of the hash substring. 

return String containing hash part of URL*/ 
std::string parse_hash(
	const std::string&		sUrl,		///< [in]    String representation of URL to search for parameters in.
	std::string::size_type&	iCurPos		///< [inout] Current string pos. Searches from here and modifies to last position in hash if possible else unchanged.
) 
{
	using namespace std;
    using boost::format;
	
	if ( iCurPos == string::npos ) return "";
	string sHash("");

	// We assume whole string from iCurPos to end is the hash.
	if ( is_hash( sUrl, iCurPos ) ) {
		sHash = sUrl.substr(iCurPos);
		iCurPos = sUrl.size() -1;		// Advance to last position in hash.
	}
	
	return sHash;
}


/** Split domain string into components. */
void split_domain ( 
	const std::string& sDomain,		///< [in] Full site string like eg 'www.tv2.dk' to split. 
	string_vec_t& domainVec			///< [out] Vector of strings containing the different parts 
)
{
	domainVec.clear();
	if ( sDomain.empty() ) return;
	using namespace std;
	string s;
	string_vec_t reverseVec;
	boost::split( reverseVec, sDomain, boost::algorithm::is_any_of(".") ); 
	
	string_vec_t::const_reverse_iterator it = reverseVec.rbegin();
	if ( (reverseVec.size() >= 2)  ) {
		s = *(it+1) + '.' + (*it); // Combine the two last parts of sitename to eg. co.uk and check against G_TwoComponentTopDomains
		if ( g_two_component_top_domains.find( s ) != g_two_component_top_domains.end() ) {
			domainVec.push_back(s);
			it = it + 2;
		}
	}

	for ( ; it != reverseVec.rend() ; ++it )	domainVec.push_back(*it);
}

/** Split parameter string into components. */
void split_parameters (	
	const std::string& sParameters,		///< [in] 
	parameter_vec_t& paramVec				///< [out]
)
{
	using namespace std;
	if ( sParameters.empty() )	return;
	paramVec.clear();
	parameter_pair p("", "");
	string* pNameOrVal = &(p.sName);
	string::const_iterator it = sParameters.begin();
	if ( *it == '?' ) ++it;		// Skip initial '?' if present
	for ( ; it != sParameters.end(); ++it ) {
		if ( *it == '&' ) {
			paramVec.push_back(p);
			p.sName		= ""; 
			p.sValue	= "";
			pNameOrVal = &(p.sName);;
		}
		else if ( *it == '=' ) {
			pNameOrVal = &(p.sValue);
		}
		else {
			pNameOrVal->push_back(*it);
		}
	}
	paramVec.push_back(p);
}

/** Advance \a iCurPos to next part of an URL string if possible. 
Assumes that \a iCurPos is allready advanced to end of latest parsed Url part.
In case the \a sLatestParsedPart is empty the \a iCurPos is {not{ advanced.
\return True if the iCurPos is has not reached end of the string.*/ 
bool parse_advance(
	const std::string&		sUrl,				///< [in]    String representation of URL to search for protocol in.
	const std::string&		sLatestParsedPart,	///< [in]    Latest parsed part of URL. Eg. 'http://' if the latest was the protocol. Or empty string if latest parse was unsuccesfull.
	std::string::size_type&	iCurPos				///< [inout] Current string pos. find_protocol searches from here and modifies to last position in protocol if possible else  else unchanged.
) 
{
	if ( sLatestParsedPart.empty() ) {
		return iCurPos < sUrl.size() ;	// Don't advance if last parsed part is empty
	}
	if ( iCurPos +1 < sUrl.size() )  {
		++iCurPos;
		return true;
	}
	return false;
}



} // END namespace crawl

