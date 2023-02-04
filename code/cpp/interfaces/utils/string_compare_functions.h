#ifndef CRAWL_STRING_COMPARE_FUNCTIONS_H
#define CRAWL_STRING_COMPARE_FUNCTIONS_H

#include <locale>
#include <boost/function.hpp>
#include <boost/regex.hpp> 
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/regex.hpp>


namespace crawl {

/// Prototype for comparision of two strings
typedef boost::function< bool ( std::string const&, std::string const& ) >	StringCompareFunT;


namespace string_compare {
typedef std::map<std::string,StringCompareFunT> StringCompFunAliasMapT;
typedef std::map<int,StringCompareFunT> 		StringCompFunHandleMapT;

struct G_StringCompareLookUp {
    static const StringCompFunAliasMapT 	AliasMap;
    static const StringCompFunHandleMapT 	HandleMap;
    static StringCompareFunT 				fromAlias	( const std::string& sFunAlias );
    static StringCompareFunT 				fromHandle	( int iFunHandle );


    enum IntNamesE {
        alwaysMatchE = 1000,
        neverMatchE,
        equalsE,
        iequalsE,
        containsE,
        icontainsE,
        startsWithE,
        istartsWithE,
        endsWithE,
        iendsWithE,
        lessThanE,
        ilessThanE,
        greaterThanE,
        igreaterThanE,
        regexSearchE,
        nequalsE,
        niequalsE,
        ncontainsE,
        nicontainsE,
        nstartsWithE,
        nistartsWithE,
        nendsWithE,
        niendsWithE,
        nlessThanE,
        nilessThanE,
        ngreaterThanE,
        nigreaterThanE,
        nregexSearchE
    };


};


// --------------------------------
// --- String compare functions ---
// --------------------------------

inline bool 
alwaysFalse ( std::string const& , std::string const& )
{	return  false; 												}

inline bool 
alwaysTrue ( std::string const& , std::string const& )
{	return  true; 												}

inline bool alwaysMatch	( 
        const std::string& /*sInput*/,
        const std::string& /*sTest*/ 	)
{
    return true;
}

inline bool neverMatch		( 
        const std::string& /*sInput*/,
        const std::string& /*sTest*/ 	)
{
    return false;
}

/** Compare strings case sensitive. */
inline bool equals	( 
        const std::string& sInput, 		///< [in] Input string
        const std::string& sTest 		///< [in] Test string
        )
{	
    return boost::algorithm::equals( sInput, sTest );
}
inline bool equals_fn	( const std::string& sInput,const std::string& sTest) 
{	return equals( sInput, sTest );	}


/** Compare strings case in-sensitive. */
inline bool iequals	( 
        const std::string& sInput, 		///< [in] Input string
        const std::string& sTest 		///< [in] Test string
        )
{	
    return boost::algorithm::iequals( sInput, sTest );
}
inline bool iequals_fn	( const std::string& sInput,const std::string& sTest) 
{	return iequals( sInput, sTest );	}


/** String contains string case sensitive. */
inline bool contains	( 
        const std::string& sInput, 		///< [in] Input string
        const std::string& sTest 		///< [in] Test string
        )
{	
    return boost::algorithm::contains( sInput, sTest );
}
inline bool contains_fn	( const std::string& sInput, const std::string& sTest )
{	return contains( sInput, sTest );					}


/** String contains string case in-sensitive. */
inline bool icontains	( 
        const std::string& sInput, 		///< [in] Input string
        const std::string& sTest 		///< [in] Test string
        )
{	
    return boost::algorithm::icontains( sInput, sTest );
}
inline bool icontains_fn	( const std::string& sInput, const std::string& sTest )
{	return icontains( sInput, sTest );					}


/** String starts with string case sensitive. */
inline bool startsWith	( 
        const std::string& sInput, 		///< [in] Input string
        const std::string& sTest 		///< [in] Test string
        )
{	
    return boost::algorithm::starts_with( sInput, sTest );
}
inline bool startsWith_fn	( const std::string& sInput, const std::string& sTest )
{	return startsWith( sInput, sTest );				}

/** String starts with string case in-sensitive. */
inline bool istartsWith	( 
        const std::string& sInput, 		///< [in] Input string
        const std::string& sTest 		///< [in] Test string
        )
{	
    return boost::algorithm::istarts_with( sInput, sTest );
}
inline bool istartsWith_fn	( const std::string& sInput, const std::string& sTest )
{	return istartsWith( sInput, sTest );				}


/** String ends with string case sensitive. */
inline bool endsWith	( 
        const std::string& sInput, 		///< [in] Input string
        const std::string& sTest 		///< [in] Test string
        )
{	
    return boost::algorithm::ends_with( sInput, sTest );
}
inline bool endsWith_fn	( const std::string& sInput, const std::string& sTest )
{	return endsWith( sInput, sTest );				}

/** String ends with string case in-sensitive. */
inline bool iendsWith	( 
        const std::string& sInput, 		///< [in] Input string
        const std::string& sTest 		///< [in] Test string
        )
{	
    return boost::algorithm::iends_with( sInput, sTest );
}
inline bool iendsWith_fn	( const std::string& sInput, const std::string& sTest )
{	return iendsWith( sInput, sTest );				}

/** Lexicographical less case sensitive .
\return true if Left hand side is less than right hand side */
inline bool lessThan ( 
        const std::string& sLhs, 	///< [in] Left hand side
        const std::string& sRhs 	///< [in] Right hand side
        )
{	
    return boost::algorithm::lexicographical_compare( sLhs, sRhs );
}
inline bool lessThan_fn ( const std::string& sLhs, const std::string& sRhs )
{	return lessThan( sLhs, sRhs ); }

/** Lexicographical less case in-sensitive .
\return true if Left hand side is less than right hand side  */
inline bool ilessThan ( 
        const std::string& sLhs, 	///< [in] Left hand side
        const std::string& sRhs 	///< [in] Right hand side
        )
{	
    return boost::algorithm::ilexicographical_compare( sLhs, sRhs );
}
inline bool ilessThan_fn ( const std::string& sLhs, const std::string& sRhs )
{	return ilessThan( sLhs, sRhs ); }

/** Lexicographical greater case sensitive .
\return true if Left hand side is greater than right hand side */
inline bool greaterThan ( 
        const std::string& sLhs, 	///< [in] Left hand side
        const std::string& sRhs 	///< [in] Right hand side
        )
{	
    return boost::algorithm::lexicographical_compare( sRhs, sLhs );
}
inline bool greaterThan_fn ( const std::string& sLhs, const std::string& sRhs )
{	return greaterThan( sLhs, sRhs ); }

/** Lexicographical greater case in-sensitive .
\return true if Left hand side is greater than right hand side */
inline bool igreaterThan ( 
        const std::string& sLhs, 	///< [in] Left hand side
        const std::string& sRhs 	///< [in] Right hand side
        )
{	
    return boost::algorithm::ilexicographical_compare( sRhs, sLhs );
}
inline bool igreaterThan_fn ( const std::string& sLhs, const std::string& sRhs )
{	return igreaterThan( sLhs, sRhs ); }

/** Regular expression search.
\return true if the regular expression matches somewhere in the input string. */
inline bool
regexSearch ( 
        const std::string& sInput,	///< [in] Input string
        const std::string& sRegex 	///< [in] Regular expression
        ){
    boost::regex expr( sRegex );
    boost::smatch what;
    return boost::regex_search( sInput, what, expr ) ;
}
inline bool regexSearch_fn	( const std::string& sInput, const std::string& sRegex )
{	return regexSearch( sInput, sRegex );				}

// ----------------------------------------
// --- Negated string compare functions ---
// ----------------------------------------

/** Compare strings case sensitive - negated. */
inline bool nequals	( 
        const std::string& sInput, 		///< [in] Input string
        const std::string& sTest 		///< [in] Test string
        )
{	
    return !boost::algorithm::equals( sInput, sTest );
}


/** Compare strings case in-sensitive - negated. */
inline bool niequals	( 
        const std::string& sInput, 		///< [in] Input string
        const std::string& sTest 		///< [in] Test string
        )
{	
    return !boost::algorithm::iequals( sInput, sTest );
}

/** String contains string case sensitive - negated. */
inline bool ncontains	( 
        const std::string& sInput, 		///< [in] Input string
        const std::string& sTest 		///< [in] Test string
        )
{	
    return !boost::algorithm::contains( sInput, sTest );
}

/** String contains string case in-sensitive - negated. */
inline bool nicontains	( 
        const std::string& sInput, 		///< [in] Input string
        const std::string& sTest 		///< [in] Test string
        )
{	
    return !boost::algorithm::icontains( sInput, sTest );
}


/** String starts with string case sensitive - negated. */
inline bool nstartsWith	( 
        const std::string& sInput, 		///< [in] Input string
        const std::string& sTest 		///< [in] Test string
        )
{	
    return !boost::algorithm::starts_with( sInput, sTest );
}

/** String starts with string case in-sensitive - negated. */
inline bool nistartsWith	( 
        const std::string& sInput, 		///< [in] Input string
        const std::string& sTest 		///< [in] Test string
        )
{	
    return !boost::algorithm::istarts_with( sInput, sTest );
}


/** String ends with string case sensitive - negated. */
inline bool nendsWith	( 
        const std::string& sInput, 		///< [in] Input string
        const std::string& sTest 		///< [in] Test string
        )
{	
    return !boost::algorithm::ends_with( sInput, sTest );
}

/** String ends with string case in-sensitive - negated. */
inline bool niendsWith	( 
        const std::string& sInput, 		///< [in] Input string
        const std::string& sTest 		///< [in] Test string
        )
{	
    return !boost::algorithm::iends_with( sInput, sTest );
}

/** Lexicographical less case sensitive - negated .
\return true if Left hand side is less than right hand side */
inline bool nlessThan ( 
        const std::string& sLhs, 	///< [in] Left hand side
        const std::string& sRhs 	///< [in] Right hand side
        )
{	
    return !boost::algorithm::lexicographical_compare( sLhs, sRhs );
}

/** Lexicographical less case in-sensitive - negated .
\return true if Left hand side is less than right hand side  */
inline bool nilessThan ( 
        const std::string& sLhs, 	///< [in] Left hand side
        const std::string& sRhs 	///< [in] Right hand side
        )
{	
    return !boost::algorithm::ilexicographical_compare( sLhs, sRhs );
}

/** Lexicographical greater case sensitive - negated.
\return true if Left hand side is greater than right hand side */
inline bool ngreaterThan ( 
        const std::string& sLhs, 	///< [in] Left hand side
        const std::string& sRhs 	///< [in] Right hand side
        )
{	
    return !boost::algorithm::lexicographical_compare( sRhs, sLhs );
}

/** Lexicographical greater case in-sensitive - negated .
\return true if Left hand side is greater than right hand side */
inline bool nigreaterThan ( 
        const std::string& sLhs, 	///< [in] Left hand side
        const std::string& sRhs 	///< [in] Right hand side
        )
{	
    return !boost::algorithm::ilexicographical_compare( sRhs, sLhs );
}

/** Regular expression search - negated.
\return true if the regular expression matches somewhere in the input string. */
inline bool
nregexSearch ( 
        const std::string& sInput,	///< [in] Input string
        const std::string& sRegex 	///< [in] Regular expression
        ){
    boost::regex expr( sRegex );
    boost::smatch what;
    return !boost::regex_search( sInput, what, expr ) ;
}


///////////////// 
// // inline bool 
// // regex ( std::string const& sInput, std::string const& sRegex )
// // {	
// // 	boost::regex expr( sRegex ); 
// // 	boost::smatch what;
// // 	return boost::regex_search( sInput, what, expr ) ;
// // }
///////////////// 

} // END namespace string_compare
} // END namespace crawl

#endif //CRAWL_STRING_COMPARE_FUNCTIONS_H

