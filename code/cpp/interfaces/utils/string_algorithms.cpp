
#include <iostream>
#include <cmath>
#include <boost/assign/list_of.hpp> 

#include "string_algorithms.h"
#include <cpaf_libs/utils/cpaf_string_utils.hpp>
#include <Configuration.h>
#include <utils/StringFinder.h>

namespace crawl {

/** @todo: boost::algorithm not quite working with string_view
 * @todo Slow when dealing with large number of replacements
*/
std::string replaceAllKeyVal(const std::map<std::string,std::string>& keyValMap, std::string_view subject)
{
    if (keyValMap.empty()) {
        return std::string(subject);
    }

    std::string s = std::string(subject);
    for (const auto& [key, val] : keyValMap) {
        boost::algorithm::replace_all(s, key, val);
    }
    return s;
}


std::string toUtf8(std::string_view str, std::string_view fromCharset)
{
    if (fromCharset == "utf-8") {
        return std::string(str);
    }
    // TODO: Handle other charsets. Can probably use Qt for this!

    return std::string(str);
}

/** Parses the string using the regex expression.
Returns the matched string
\note Ignore case currently only works for ASCII chars. */
std::string regexParseValue		(
    const std::string& sInput,	///< [in] Input string to parse.
    const std::string& sRegex,	///< [in] Regular expression.
    bool bIgnoreCase 			///< [in] Case insensitive compares ?
    )
{
    using namespace boost;
    boost::match_results<std::string::const_iterator> 	matchResults;
    std::string sMatch = "";

    boost::match_flag_type 								flags 			= boost::match_default;
    regex::flag_type									constructFlags 	= regex::perl;

    if ( bIgnoreCase )	constructFlags |= regex::icase;
    boost::regex 		expression (sRegex, constructFlags);

    if ( regex_search( sInput, matchResults, expression, flags) )
    {
        sMatch = matchResults[0];
    }
    return sMatch;
}

// ----------------------
// --- Trim functions ---
// ----------------------

std::string
trimDefault_fun (
    const std::string& sInput           ///< [in] Input string to trim.
)
{
    using namespace boost::algorithm;

    // First replace all '&nbsp;' with normal white spaces. Note UTF8 &nbsp; == \302\240 !!
    std::string sTrim =  replace_all_copy( sInput, std::string("\302\240"), std::string(" ") );
    replace_all( sTrim, std::string("\n"), std::string(" ") );
    trim ( sTrim );
    // Primitive (slow) algorithm to clean up spaces so that no more than one space in-a-row so to speak.
    while ( contains ( sTrim, std::string("  ") )  ) {
        replace_all( sTrim, std::string("  "), std::string(" ") );	// Replace two spaces with one space.
    }
    return sTrim;
}


// ----------------------------------------------------
// --- Trim functions taking a config pointer input ---
// ----------------------------------------------------


std::string
trimDefault_fnc (
        const boost::shared_ptr<Configuration> /*pConfig*/
    ,   const std::string& sInput           ///< [in] Input string to trim.
)
{
    return trimDefault_fun(sInput);
}


/** Output string as is, witout any processing.
\return Exact copy of input string . */
std::string raw_fnc	(
        const boost::shared_ptr<Configuration> /*pConfig*/
    ,   const std::string& sInput           ///< [in] Input string to trim.
)
{
    return sInput;
}


////////////////////////

/** Convert string to uppercase.
\return Upcased version of input string. */
std::string toUpper_fnc(
        const boost::shared_ptr<Configuration> /*pConfig*/
    ,   const std::string& sInput           ///< [in] Input string to trim.
)
{
    return boost::algorithm::to_upper_copy ( sInput ); }

/** Convert string to lowercase.
\return Lowercased version of input string. */
std::string toLower_fnc(
        const boost::shared_ptr<Configuration> /*pConfig*/
    ,   const std::string& sInput           ///< [in] Input string to trim.
)
{
    return boost::algorithm::to_lower_copy ( sInput );
}

/** Trim spaces from both ends of string.
\return Trimmed version of input string, i.e. spaces removed from both ends. */
std::string trimEnds_fnc	(
        const boost::shared_ptr<Configuration> pConfig
    ,   const std::string& sInput           ///< [in] Input string to trim.
)
{
    using namespace boost::algorithm;
    std::string sTrim = trimLeft_fnc ( pConfig, sInput );
    return trimRight_fnc ( pConfig, sTrim );
}

/** Trim spaces from left end of string.
\return Trimmed-left version of input string, i.e. spaces removed from left end. */
std::string trimLeft_fnc	(
        const boost::shared_ptr<Configuration> /*pConfig*/
    ,   const std::string& sInput           ///< [in] Input string to trim.
)
{
    using namespace boost::algorithm;

    std::string sTrim = sInput;
    bool bDone = false;
    while ( !bDone ) {
        trim_left ( sTrim );
        bDone = true;
        while ( starts_with ( sTrim, std::string("\302\240") ) ) {
            bDone = false;
            erase_first( sTrim, std::string("\302\240") );
        }
    }
    return sTrim;
}

/** Parses the string looking for anything matching a year (i.e. 4 digits in a row) */
std::string trimYear_fnc (
        const boost::shared_ptr<Configuration> /*pConfig*/
    ,   const std::string& sInput           ///< [in] Input string to trim.
)
{
    return regexParseValue ( sInput, std::string("\\d\\d\\d\\d"), false );
}


/** Primitive trimming of string to an integer.
\return Integer i.e. only integer numbers with all other characters removed. */
std::string trimInteger_fnc	(
        const boost::shared_ptr<Configuration> pConfig
    ,   const std::string& sInput)			///< [in] Original string to trim.
{
    std::string sThousandsSep = ",";
    if ( pConfig ) sThousandsSep = pConfig->valueStrGet("thousands_sep");
    return crawl::trimToInteger(sInput, 10, sThousandsSep );
}


/** Parsing of string to a float/double
\return Float */
std::string trimNumber_fnc	(
        const boost::shared_ptr<Configuration> pConfig
    ,   const std::string& sInput	)			///< [in] Original string to trim.
{
    std::string sDecimalPoint = ".";
    std::string sThousandsSep = ",";
    if ( pConfig ) {
        sDecimalPoint = pConfig->valueStrGet("decimal_point");
        sThousandsSep = pConfig->valueStrGet("thousands_sep");
    }
    std::string num = crawl::trimToFloat( sInput, sDecimalPoint, sThousandsSep );
    return num;
}


/** Trim spaces from right end of string.
\return Trimmed-right version of input string, i.e. spaces removed from right end. */
std::string trimRight_fnc	(
        const boost::shared_ptr<Configuration> /*pConfig*/
    ,   const std::string& sInput           ///< [in] Input string to trim.
)
{
    using namespace boost::algorithm;

    std::string sTrim = sInput;
    bool bDone = false;
    while ( !bDone ) {
        trim_right ( sTrim );
        bDone = true;
        while ( ends_with ( sTrim, std::string("\302\240") ) ) {
            bDone = false;
            erase_last( sTrim, std::string("\302\240") );
        }
    }
    return sTrim;
}


/** Remove chars from beginning and end of string.
\return Trimmed version of input string, i.e. spaces removed from both ends. */
std::string trimCharsEnds_fnc	(
        const boost::shared_ptr<Configuration> /*pConfig*/
    ,   const std::string& sInput 			///< [in] Original string.
    ,   const std::string& sCharsToTrim		///< String containing all chars you want to 'trim' away
    )
{
    return boost::trim_copy_if( sInput, boost::is_any_of( sCharsToTrim ) );
}


/** Remove chars from beginning of string.
\return Trimmed version of input string, i.e. spaces removed from beginning. */
std::string trimCharsLeft_fnc	(
        const boost::shared_ptr<Configuration> /*pConfig*/
    ,   const std::string& sInput 			///< [in] Original string.
    ,   const std::string& sCharsToTrim		///< String containing all chars you want to 'trim' away
)
{
    return boost::trim_left_copy_if( sInput, boost::is_any_of( sCharsToTrim ) );
}

/** Remove chars from end of string.
\return Trimmed version of input string, i.e. spaces removed from end. */
std::string trimCharsRight_fnc (
        const boost::shared_ptr<Configuration> /*pConfig*/
    ,   const std::string& sInput 			///< [in] Original string.
    ,   const std::string& sCharsToTrim		///< String containing all chars you want to 'trim' away
)
{
    return boost::trim_right_copy_if( sInput, boost::is_any_of( sCharsToTrim ) );
}


/** Trim */
std::string trimBetween_fnc  (
          const boost::shared_ptr<Configuration> /*pConfig*/
        , const std::string& sInput                 ///< [in] Original string.
        , const std::string& sBegin                 ///< [in] Begin delimiter - leave empty to use begining of input string
        , const std::string& sEnd                   ///< [in] End delimiter - leave empty to use end of input string
        )
{
    StringFinder sf(sInput);
    sf.findBetween( sBegin, sEnd );
    return sf.currentValueRaw();    // When used in crawler normally trimDefault wil be called. But in case user wants raw we return this as default from here.
}

std::string trimBetweenCount_fnc  (
          const boost::shared_ptr<Configuration> /*pConfig*/
        , const std::string& sInput                 ///< [in] Original string.
        , const std::string& sBegin                 ///< [in] Begin delimiter - leave empty to use begining of input string
        , const std::string& sEnd                   ///< [in] End delimiter - leave empty to use end of input string
        , const std::string& sCount                 ///< [in] Stop at count number of matches.
        )
{
    const int iCount =  static_cast<int>(cpaf::parse_long(sCount));
    StringFinder sf(sInput);
    sf.findBetween( iCount, sBegin, sEnd );
    return sf.currentValueRaw();    // When used in crawler normally trimDefault wil be called. But in case user wants raw we return this as default from here.
}

std::string trimBetweenCountInt_fnc  (
          const boost::shared_ptr<Configuration> /*pConfig*/
        , const std::string& sInput                 ///< [in] Original string.
        , const std::string& sBegin                 ///< [in] Begin delimiter - leave empty to use begining of input string
        , const std::string& sEnd                   ///< [in] End delimiter - leave empty to use end of input string
        , int iCount                                ///< [in] Stop at count number of matches.
        )
{
    StringFinder sf(sInput);
    sf.findBetween( iCount, sBegin, sEnd );
    return sf.currentValueRaw();    // When used in crawler normally trimDefault wil be called. But in case user wants raw we return this as default from here.
}

/** Primitive trimming of string to an integer.
\return Integer i.e. only integer numbers with all other characters removed. */
std::string trimIntegerCustom_fnc	(
        const boost::shared_ptr<Configuration> /*pConfig*/
    ,   const std::string& sInput			///< [in] Original string to trim.
    ,   const std::string& iBase			///< [in] Number representing base. Normally 10 for decimal
    ,   const std::string& sThousandsSep
)
{
    int iNumBase =  static_cast<int>(cpaf::parse_long( iBase ) );
    return crawl::trimToInteger(sInput, iNumBase, sThousandsSep );
}

/** Parsing of string to a float/double
\return Float */
std::string trimNumberCustom_fnc	(
        const boost::shared_ptr<Configuration> /*pConfig*/
    ,   const std::string& sInput			///< [in] Original string to trim.
    ,   const std::string& sDecimalPoint
    ,   const std::string& sThousandsSep
    )
{
    return crawl::trimToFloat(sInput, sDecimalPoint, sThousandsSep );
}


/** Parses the string using the regex expression.
Returns the matched string */
std::string trimRegex_fnc	(
        const boost::shared_ptr<Configuration> /*pConfig*/
    ,   const std::string& sInput 			///< [in] Original string.
    ,   const std::string& sRegex
    )
{
    return crawl::regexParseValue ( sInput, sRegex, false );
}


/** Parses the string using the regex expression (ignoring case).
Returns the matched string
\note Ignore case currently only works for ASCII chars. */
std::string itrimRegex_fnc	(
        const boost::shared_ptr<Configuration> /*pConfig*/
    ,   const std::string& sInput 	///< [in] Original string.
    ,   const std::string& sRegex	///< [in] Regular expression.
    )
{
    return regexParseValue( sInput, sRegex, true );
}


/** Append string to another.
\return Concatenation of the two strings: sInput + sString. */
std::string	append_fnc (
        const boost::shared_ptr<Configuration> /*pConfig*/
    ,   const std::string& sInput 		///< [in] Original string.
    ,   const std::string& sString		///< [in] String to append to original string.
)
{
    return sInput + sString;
}

/** Prepend string with another.
\return Concatenation of the two strings: sString + sInput . */
std::string	prepend_fnc (
        const boost::shared_ptr<Configuration> /*pConfig*/
    ,   const std::string& sInput 		///< [in] Original string.
    ,   const std::string& sString		///< [in] String to append to original string.
)
{
    return sString + sInput;
}


// - replaceFirst / eraseFirst functions ---
/** Replace first occurence of substring with a new string.
\return The original string with first occurence of \p sSearchFor replaced with \p sReplaceWith. */
std::string	replaceFirst_fnc (
        const boost::shared_ptr<Configuration> /*pConfig*/
    ,   const std::string& sInput 			///< [in] Original string.
    ,   const std::string& sSearchFor		///< [in] Substring to search for in original string.
    ,   const std::string& sReplaceWith		///< [in] String to insert into original string first matching place.
)
{
    return boost::algorithm::replace_first_copy( sInput, sSearchFor, sReplaceWith);
}


/** Replace first occurence of substring with a new string - ignore case .
\return The original string with first occurence of \p sSearchFor replaced with \p sReplaceWith. */
std::string	ireplaceFirst_fnc (
        const boost::shared_ptr<Configuration> /*pConfig*/
    ,   const std::string& sInput 			///< [in] Original string.
    ,   const std::string& sSearchFor		///< [in] Substring to search for in original string.
    ,   const std::string& sReplaceWith		///< [in] String to insert into original string first matching place.
)
{
    return boost::algorithm::ireplace_first_copy( sInput, sSearchFor, sReplaceWith );
}

/** Erase first occurence of substring with a new string.
\return The original string with first occurence of \p sSearchFor erased. */
std::string	eraseFirst_fnc (
        const boost::shared_ptr<Configuration> /*pConfig*/
    ,   const std::string& sInput 			///< [in] Original string.
    ,   const std::string& sSearchFor 		///< [in] Substring to search for in original string.
)
{
    return boost::algorithm::erase_first_copy( sInput, sSearchFor );
}

/** Erase first occurence of substring with a new string - ignore case.
\return The original string with first occurence of \p sSearchFor erased. */
std::string	ieraseFirst_fnc (
        const boost::shared_ptr<Configuration> /*pConfig*/
    ,   const std::string& sInput 			///< [in] Original string.
    ,   const std::string& sSearchFor 		///< [in] Substring to search for in original string.
)
{
    return boost::algorithm::ierase_first_copy( sInput, sSearchFor );
}


// - replaceLast / eraseLast functions ---
/** Replace last occurence of substring with a new string.
\return The original string with last occurence of \p sSearchFor replaced with \p sReplaceWith. */
std::string	replaceLast_fnc (
        const boost::shared_ptr<Configuration> /*pConfig*/
    ,   const std::string& sInput 			///< [in] Original string.
    ,   const std::string& sSearchFor		///< [in] Substring to search for in original string.
    ,   const std::string& sReplaceWith		///< [in] String to insert into original string last matching place.
    )
{
    return boost::algorithm::replace_last_copy( sInput, sSearchFor, sReplaceWith);
}


/** Replace last occurence of substring with a new string - ignore case .
\return The original string with last occurence of \p sSearchFor replaced with \p sReplaceWith. */
std::string	ireplaceLast_fnc (
        const boost::shared_ptr<Configuration> /*pConfig*/
    ,   const std::string& sInput 			///< [in] Original string.
    ,   const std::string& sSearchFor		///< [in] Substring to search for in original string.
    ,   const std::string& sReplaceWith		///< [in] String to insert into original string last matching place.
)
{
    return boost::algorithm::ireplace_last_copy( sInput, sSearchFor, sReplaceWith );
}

/** Erase last occurence of substring with a new string.
\return The original string with last occurence of \p sSearchFor erased. */
std::string	eraseLast_fnc (
        const boost::shared_ptr<Configuration> /*pConfig*/
    ,   const std::string& sInput 			///< [in] Original string.
    ,   const std::string& sSearchFor 		///< [in] Substring to search for in original string.
    )
{
    return boost::algorithm::erase_last_copy( sInput, sSearchFor );
}

/** Erase last occurence of substring with a new string - ignore case.
\return The original string with last occurence of \p sSearchFor erased. */
std::string	ieraseLast_fnc (
        const boost::shared_ptr<Configuration> /*pConfig*/
    ,   const std::string& sInput 			///< [in] Original string.
    ,   const std::string& sSearchFor 		///< [in] Substring to search for in original string.
)
{
    return boost::algorithm::ierase_last_copy( sInput, sSearchFor );
}

// ------------------------------------
// --- Erase/replace n-th functions ---
// ------------------------------------

/** Replace the nth occurence of substring with a new string.
\return The original string with the nth occurence of \p sSearchFor replaced with \p sReplaceWith. */
std::string	replaceNth_fnc (
        const boost::shared_ptr<Configuration> /*pConfig*/
    ,   const std::string& sInput 			///< [in] Original string.
    ,   const std::string& sSearchFor		///< [in] Substring to search for in original string.
    ,   const std::string& sReplaceWith     ///< [in] String to insert into original string at nth matching place.
    ,   int                iNth				///< [in] An index of the match to be replaced. The index is 0-based. For negative N, matches are counted from the end of string.
    )
{
    return boost::algorithm::replace_nth_copy( sInput, sSearchFor, iNth, sReplaceWith);
}

/** Replace the nth occurence of substring with a new string - ignore case.
\return The original string with the nth occurence of \p sSearchFor replaced with \p sReplaceWith. */
std::string	ireplaceNth_fnc (
        const boost::shared_ptr<Configuration> /*pConfig*/
    ,   const std::string& sInput 			///< [in] Original string.
    ,   const std::string& sSearchFor		///< [in] Substring to search for in original string.
    ,   const std::string& sReplaceWith     ///< [in] String to insert into original string at nth matching place.
    ,   int                iNth				///< [in] An index of the match to be replaced. The index is 0-based. For negative N, matches are counted from the end of string.
    )
{
    return boost::algorithm::ireplace_nth_copy( sInput, sSearchFor, iNth, sReplaceWith );
}

/** Erase the nth occurence of substring with a new string.
\return The original string with the nth occurence of \p sSearchFor erased. */
std::string	eraseNth_fnc (
        const boost::shared_ptr<Configuration> /*pConfig*/
    ,   const std::string& sInput 			///< [in] Original string.
    ,   const std::string& sSearchFor		///< [in] Substring to search for in original string.
    ,   int                iNth 			///< [in] An index of the match to be erased. The index is 0-based. For negative N, matches are counted from the end of string.
)
{
    return boost::algorithm::erase_nth_copy( sInput, sSearchFor, iNth );
}

/** Erase the nth occurence of substring with a new string - ignore case.
\return The original string with the nth occurence of \p sSearchFor erased. */
std::string	ieraseNth_fnc (
        const boost::shared_ptr<Configuration> /*pConfig*/
    ,   const std::string& sInput 			///< [in] Original string.
    ,   const std::string& sSearchFor		///< [in] Substring to search for in original string.
    ,   int                iNth 			///< [in] An index of the match to be erased. The index is 0-based. For negative N, matches are counted from the end of string.
)
{
    return boost::algorithm::ierase_nth_copy( sInput, sSearchFor, iNth );
}


// -----------------------------------
// --- Erase/replace all functions ---
// -----------------------------------

// - replaceAll / eraseAll functions ---
/** Replace all occurences of substring with a new string.
\return The original string with all occurences of \p sSearchFor replaced with \p sReplaceWith. */
std::string	replaceAll_fnc (
        const boost::shared_ptr<Configuration> /*pConfig*/
    ,   const std::string& sInput 			///< [in] Original string.
    ,   const std::string& sSearchFor		///< [in] Substring to search for in original string.
    ,   const std::string& sReplaceWith		///< [in] String to insert into original string all matching places.
)
{
    return boost::algorithm::replace_all_copy( sInput, sSearchFor, sReplaceWith);
}


/** Replace all occurences of substring with a new string - ignore case.
\return The original string with all occurences of \p sSearchFor replaced with \p sReplaceWith. */
std::string	ireplaceAll_fnc (
        const boost::shared_ptr<Configuration> /*pConfig*/
    ,   const std::string& sInput 			///< [in] Original string.
    ,   const std::string& sSearchFor		///< [in] Substring to search for in original string.
    ,   const std::string& sReplaceWith		///< [in] String to insert into original string all matching places.
    )
{
    return boost::algorithm::ireplace_all_copy( sInput, sSearchFor, sReplaceWith );
}

/** Erase all occurences of substring with a new string.
\return The original string with all occurences of \p sSearchFor erased. */
std::string	eraseAll_fnc (
        const boost::shared_ptr<Configuration> /*pConfig*/
    ,   const std::string& sInput 			///< [in] Original string.
    ,   const std::string& sSearchFor 		///< [in] Substring to search for in original string.
)
{
    return boost::algorithm::erase_all_copy( sInput, sSearchFor );
}

/** Erase all occurences of substring with a new string - ignore case.
\return The original string with all occurences of \p sSearchFor erased. */
std::string	ieraseAll_fnc (
        const boost::shared_ptr<Configuration> /*pConfig*/
    ,   const std::string& sInput 			///< [in] Original string.
    ,   const std::string& sSearchFor 		///< [in] Substring to search for in original string.
)
{
    return boost::algorithm::ierase_all_copy( sInput, sSearchFor );
}

// - Regex functions ---
/** Search for a substring matching given regular expression and substitute with specified string.
\return The original string with \p sRegex match replaced with \p sReplaceWith. */
std::string	replaceRegex_fnc (
        const boost::shared_ptr<Configuration> /*pConfig*/
    ,   const std::string& sInput 			///< [in] Original string.
    ,   const std::string& sRegex			///< [in] Regular expression.
    ,   const std::string& sReplaceWith		///< [in] String to insert into original string where the regex matched.
)
{
    return boost::algorithm::replace_regex_copy( sInput, boost::regex(sRegex), sReplaceWith);
}

/** Replace all substrings, matching given regex, with the specified string.
\return The original string with all 'occurences' of \p sRegex replaced with \p sReplaceWith. */
std::string	replaceAllRegex_fnc (
        const boost::shared_ptr<Configuration> /*pConfig*/
    ,   const std::string& sInput 			///< [in] Original string.
    ,   const std::string& sRegex			///< [in] Regular expression.
    ,   const std::string& sReplaceWith		///< [in] String to insert into original string where the regex matched.
)
{
    return boost::algorithm::replace_all_regex_copy( sInput, boost::regex(sRegex), sReplaceWith);
}


/** Search for a substring matching given regular expression and erase.
\return The original string with \p sRegex match erased. */
std::string	eraseRegex_fnc (
        const boost::shared_ptr<Configuration> /*pConfig*/
    ,   const std::string& sInput 			///< [in] Original string.
    ,   const std::string& sRegex 			///< [in] Regular expression.
)
{
    return boost::algorithm::erase_regex_copy( sInput, boost::regex(sRegex) );
}

/** Erase all substrings, matching given regex.
\return The original string with all 'occurences' of \p sRegex erased. */
std::string	eraseAllRegex_fnc (
        const boost::shared_ptr<Configuration> /*pConfig*/
    ,   const std::string& sInput 			///< [in] Original string.
    ,   const std::string& sRegex 			///< [in] Regular expression.
)
{
    return boost::algorithm::erase_all_regex_copy( sInput, boost::regex(sRegex) );
}

// -----------------------------------------------------------------------------------
// --- Erase/replace n-th functions taking the n-th as a string arg and not an int ---
// -----------------------------------------------------------------------------------

/** Erase the nth occurence of substring with a new string.
The sNth parameter should contain a string which can be parsed to yield an integer.
\return The original string with the nth occurence of \p sSearchFor erased. */
std::string	eraseNthStrIndex_fnc (
        const boost::shared_ptr<Configuration> pConfig
    ,   const std::string& sInput 			///< [in] Original string.
    ,   const std::string& sSearchFor		///< [in] Substring to search for in original string.
    ,   const std::string& sNth				///< [in] An index of the match to be replaced. The index is 0-based. For negative N, matches are counted from the end of string.
    )
{
    std::string sThousandsSep = ",";
    if ( pConfig ) {
        sThousandsSep = pConfig->valueStrGet("thousands_sep");
    }
    int iNth  =  static_cast<int>( cpaf::parse_long( sNth, sThousandsSep, 10 )) -1;
    return boost::algorithm::erase_nth_copy( sInput, sSearchFor, iNth );
}

/** Erase the nth occurence of substring with a new string - ignore case.
The sNth parameter should contain a string which can be parsed to yield an integer.
\return The original string with the nth occurence of \p sSearchFor erased. */
std::string	ieraseNthStrIndex_fnc (
        const boost::shared_ptr<Configuration> pConfig
    ,   const std::string& sInput 			///< [in] Original string.
    ,   const std::string& sSearchFor		///< [in] Substring to search for in original string.
    ,   const std::string& sNth				///< [in] An index of the match to be replaced. The index is 0-based. For negative N, matches are counted from the end of string.
    )
{
    std::string sThousandsSep = ",";
    if ( pConfig ) {
        sThousandsSep = pConfig->valueStrGet("thousands_sep");
    }
    int iNth  =  static_cast<int>( cpaf::parse_long( sNth, sThousandsSep, 10)) -1;
    return boost::algorithm::ierase_nth_copy( sInput, sSearchFor, iNth );
}


/** Replace the nth occurence of substring with a new string.
The sNth parameter should contain a string which can be parsed to yield an integer.
\return The original string with the nth occurence of \p sSearchFor replaced with \p sReplaceWith. */
std::string	replaceNthStrIndex_fnc (
        const boost::shared_ptr<Configuration> pConfig
    ,   const std::string& sInput 			///< [in] Original string.
    ,   const std::string& sSearchFor		///< [in] Substring to search for in original string.
    ,   const std::string& sReplaceWith     ///< [in] String to insert into original string at nth matching place.
    ,   const std::string& sNth				///< [in] An index of the match to be replaced. The index is 0-based. For negative N, matches are counted from the end of string.
    )
{
    std::string sThousandsSep = ",";
    if ( pConfig ) {
        sThousandsSep = pConfig->valueStrGet("thousands_sep");
    }
    int iNth  =  static_cast<int>( cpaf::parse_long( sNth, sThousandsSep, 10)) -1;
    return boost::algorithm::replace_nth_copy( sInput, sSearchFor, iNth, sReplaceWith);
}

/** Replace the nth occurence of substring with a new string - ignore case.
The sNth parameter should contain a string which can be parsed to yield an integer.
\return The original string with the nth occurence of \p sSearchFor replaced with \p sReplaceWith. */
std::string	ireplaceNthStrIndex_fnc (
        const boost::shared_ptr<Configuration> pConfig
    ,   const std::string& sInput 			///< [in] Original string.
    ,   const std::string& sSearchFor		///< [in] Substring to search for in original string.
    ,   const std::string& sReplaceWith     ///< [in] String to insert into original string at nth matching place.
    ,   const std::string& sNth				///< [in] An index of the match to be replaced. The index is 0-based. For negative N, matches are counted from the end of string.
    )
{
    std::string sThousandsSep = ",";
    if ( pConfig ) {
        sThousandsSep = pConfig->valueStrGet("thousands_sep");
    }
    int iNth  =  static_cast<int>( cpaf::parse_long( sNth, sThousandsSep, 10)) -1;
    return boost::algorithm::ireplace_nth_copy( sInput, sSearchFor, iNth, sReplaceWith );
}

// --------------------------------------------------------------------------------------------------
// --- Default no-operation manip functions for use if lookup fails (default functions to return ) --
// --------------------------------------------------------------------------------------------------
std::string	noOpStr			( const std::string& sInput )
{
	return sInput;
}

std::string	noOpStrStr		( const std::string& sInput, const std::string& /*s2*/	)
{
	return sInput;
}

std::string	noOpStrStrStr	( const std::string& sInput, const std::string& /*s2*/, const std::string& /*s3*/	)
{
	return sInput;
}

std::string	noOpStrStrInt	( const std::string& sInput, const std::string& /*s2*/, int /*i3*/	)
{
	return sInput;
}

std::string	noOpStrStrStrInt( const std::string& sInput, const std::string& /*s2*/, const std::string& /*s3*/, int /*i4*/	)
{
	return sInput;
}

std::string
trimToInteger ( 
	const std::string& sInput, 
	int iBase,
	const std::string& sThousandsSep
)
{
    long iVal;
    bool bFound = cpaf::parse_find_long( iVal, sInput, iBase, sThousandsSep );
    if ( !bFound ) iVal = 0;
    return cpaf::to_string_c_locale( iVal );
}

std::string
trimToFloat (const std::string& sInput, const std::string& sDecimalPoint, const std::string& sThousandsSep)
{
    constexpr double default_value = 0;
	double fVal; 
    const bool bFound = cpaf::parse_find_double(fVal, sInput, default_value, sDecimalPoint, sThousandsSep);
    if (!bFound || std::isnan(fVal)) fVal = default_value;
    return cpaf::to_string_c_locale(fVal);
}

} // END namespace crawl

