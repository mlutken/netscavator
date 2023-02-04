#pragma once
#include <locale>
#include <string_view>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/regex.hpp> 
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/regex.hpp>


namespace crawl {
class Configuration;

// -------------------------
// --- Replace functions ---
// -------------------------

std::string replaceAllKeyVal(const std::map<std::string, std::string>& keyValMap, std::string_view subject);

// ------------------------------------
// --- Charset conversion functions ---
// ------------------------------------

/** Convert string to UTF-8
\todo Implement this for real! */
std::string toUtf8(std::string_view str, std::string_view fromCharset);

// ----------------------
// --- Trim functions ---
// ----------------------

std::string		trimDefault_fun 	( const std::string& sInput );

// ----------------------------------------------------
// --- Trim functions taking a config pointer input ---
// ----------------------------------------------------

std::string		trimDefault_fnc 	( const boost::shared_ptr<Configuration> pConfig, const std::string& sInput 	)								;
std::string		raw_fnc				( const boost::shared_ptr<Configuration> pConfig, const std::string& sInput		)								;
std::string		toUpper_fnc			( const boost::shared_ptr<Configuration> pConfig, const std::string& sInput		)								;
std::string		toLower_fnc			( const boost::shared_ptr<Configuration> pConfig, const std::string& sInput		)								;
std::string		trimEnds_fnc		( const boost::shared_ptr<Configuration> pConfig, const std::string& sInput		)								;
std::string		trimLeft_fnc		( const boost::shared_ptr<Configuration> pConfig, const std::string& sInput		)								;
std::string		trimRight_fnc		( const boost::shared_ptr<Configuration> pConfig, const std::string& sInput		)								;
std::string		trimYear_fnc		( const boost::shared_ptr<Configuration> pConfig, const std::string& sInput 	)								;
std::string		trimInteger_fnc		( const boost::shared_ptr<Configuration> pConfig, const std::string& sInput		)								;
std::string		trimNumber_fnc		( const boost::shared_ptr<Configuration> pConfig, const std::string& sInput		)								;

std::string 	trimCharsEnds_fnc	( const boost::shared_ptr<Configuration> pConfig, const std::string& sInput, const std::string& sCharsToTrim )	;
std::string 	trimCharsLeft_fnc	( const boost::shared_ptr<Configuration> pConfig, const std::string& sInput, const std::string& sCharsToTrim ) 	;
std::string 	trimCharsRight_fnc	( const boost::shared_ptr<Configuration> pConfig, const std::string& sInput, const std::string& sCharsToTrim )	;
std::string 	trimRegex_fnc		( const boost::shared_ptr<Configuration> pConfig, const std::string& sInput, const std::string& sRegex )												;
std::string 	itrimRegex_fnc		( const boost::shared_ptr<Configuration> pConfig, const std::string& sInput, const std::string& sRegex )												;
std::string		append_fnc			( const boost::shared_ptr<Configuration> pConfig, const std::string& sInput, const std::string& sString	)	;
std::string		prepend_fnc			( const boost::shared_ptr<Configuration> pConfig, const std::string& sInput, const std::string& sString	)	;
std::string		eraseFirst_fnc		( const boost::shared_ptr<Configuration> pConfig, const std::string& sInput, const std::string& sSearchFor	)	;
std::string		ieraseFirst_fnc		( const boost::shared_ptr<Configuration> pConfig, const std::string& sInput, const std::string& sSearchFor	)	;
std::string		eraseLast_fnc		( const boost::shared_ptr<Configuration> pConfig, const std::string& sInput, const std::string& sSearchFor	)	;
std::string		ieraseLast_fnc		( const boost::shared_ptr<Configuration> pConfig, const std::string& sInput, const std::string& sSearchFor	)	;
std::string		eraseAll_fnc		( const boost::shared_ptr<Configuration> pConfig, const std::string& sInput, const std::string& sSearchFor	)	;
std::string		ieraseAll_fnc		( const boost::shared_ptr<Configuration> pConfig, const std::string& sInput, const std::string& sSearchFor	)	;
std::string		eraseRegex_fnc		( const boost::shared_ptr<Configuration> pConfig, const std::string& sInput, const std::string& sSearchFor	)	;
std::string		eraseAllRegex_fnc	( const boost::shared_ptr<Configuration> pConfig, const std::string& sInput, const std::string& sSearchFor	)	;

std::string 	trimBetween_fnc     ( const boost::shared_ptr<Configuration> pConfig, const std::string& sInput, const std::string& sBegin, 		const std::string& sEnd );
std::string 	trimBetweenCount_fnc( const boost::shared_ptr<Configuration> pConfig, const std::string& sInput, const std::string& sBegin, 		const std::string& sEnd, const std::string& sCount );
std::string 	trimBetweenCountInt_fnc( const boost::shared_ptr<Configuration> pConfig, const std::string& sInput, const std::string& sBegin, 		const std::string& sEnd, int iCount );
std::string 	trimIntegerCustom_fnc( const boost::shared_ptr<Configuration> pConfig, const std::string& sInput, const std::string& iBase, 		const std::string& sThousandsSep);
std::string 	trimNumberCustom_fnc( const boost::shared_ptr<Configuration> pConfig, const std::string& sInput, const std::string& sDecimalPoint, 	const std::string& sThousandsSep);
std::string		replaceFirst_fnc	( const boost::shared_ptr<Configuration> pConfig, const std::string& sInput, const std::string& sSearchFor,		const std::string& sReplaceWith	);
std::string		ireplaceFirst_fnc	( const boost::shared_ptr<Configuration> pConfig, const std::string& sInput, const std::string& sSearchFor,		const std::string& sReplaceWith	);
std::string		replaceLast_fnc		( const boost::shared_ptr<Configuration> pConfig, const std::string& sInput, const std::string& sSearchFor,		const std::string& sReplaceWith	);
std::string		ireplaceLast_fnc	( const boost::shared_ptr<Configuration> pConfig, const std::string& sInput, const std::string& sSearchFor,		const std::string& sReplaceWith	);
std::string		replaceAll_fnc		( const boost::shared_ptr<Configuration> pConfig, const std::string& sInput, const std::string& sSearchFor,		const std::string& sReplaceWith	)	;
std::string		ireplaceAll_fnc		( const boost::shared_ptr<Configuration> pConfig, const std::string& sInput, const std::string& sSearchFor,		const std::string& sReplaceWith	)	;
std::string		replaceRegex_fnc	( const boost::shared_ptr<Configuration> pConfig, const std::string& sInput, const std::string& sSearchFor,		const std::string& sReplaceWith	)	;
std::string		replaceAllRegex_fnc	( const boost::shared_ptr<Configuration> pConfig, const std::string& sInput, const std::string& sSearchFor,		const std::string& sReplaceWith	)	;

std::string		eraseNth_fnc		( const boost::shared_ptr<Configuration> pConfig, const std::string& sInput, const std::string& sSearchFor,	int iNth 	)	;
std::string		ieraseNth_fnc		( const boost::shared_ptr<Configuration> pConfig, const std::string& sInput, const std::string& sSearchFor,	int iNth 	)	;

std::string		replaceNth_fnc		( const boost::shared_ptr<Configuration> pConfig, const std::string& sInput, const std::string& sSearchFor,	const std::string& sReplaceWith, int iNth	)	;
std::string		ireplaceNth_fnc		( const boost::shared_ptr<Configuration> pConfig, const std::string& sInput, const std::string& sSearchFor,	const std::string& sReplaceWith, int iNth	)	;

std::string		eraseNthStrIndex_fnc( const boost::shared_ptr<Configuration> pConfig, const std::string& sInput, const std::string& sSearchFor,     const std::string& sNth 	)	;
std::string		ieraseNthStrIndex_fnc( const boost::shared_ptr<Configuration> pConfig, const std::string& sInput, const std::string& sSearchFor,	const std::string& sNth 	)	;
std::string		replaceNthStrIndex_fnc	( const boost::shared_ptr<Configuration> pConfig, const std::string& sInput, const std::string& sSearchFor,	const std::string& sReplaceWith, const std::string& sNth	)	;
std::string		ireplaceNthStrIndex_fnc	( const boost::shared_ptr<Configuration> pConfig, const std::string& sInput, const std::string& sSearchFor,	const std::string& sReplaceWith, const std::string& sNth	)	;


// --- Helpers ---
std::string		regexParseValue		( const std::string& sInput, const std::string& sRegex,	bool bIgnoreCase );	

std::string		noOpStr				( const std::string& sInput	);
std::string		noOpStrStr			( const std::string& sInput, const std::string& s2	);
std::string		noOpStrStrStr		( const std::string& sInput, const std::string& s2, const std::string& s3	);
std::string		noOpStrStrInt		( const std::string& sInput, const std::string& s2, int i3	);
std::string		noOpStrStrStrInt	( const std::string& sInput, const std::string& s2, const std::string& s3,  int i4	);

/////////////////////////////
// FOLLOWING SHOULD GO OUT //
/////////////////////////////


//std::string
//trimToInteger 	( const std::string& sInput, const std::locale& loc = std::locale() );

std::string
trimToInteger 	( const std::string& sInput, int iBase, const std::string& sThousandsSep );

//std::string
//trimToFloat 	( const std::string&,  const std::locale& loc = std::locale() );

std::string
trimToFloat 	( const std::string& sInput, const std::string& sDecimalPoint, const std::string& sThousandsSep );


} // END namespace crawl

