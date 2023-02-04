#include <stdio.h>
#include <iostream>
#include <string>
#include <boost/algorithm/string.hpp>
#include <cpaf_string_utils.hpp>

/** Parse thru string trying to find something that can parse as a double.
itFirst is set to rest of string. */
bool parse_find_double(
    double& fDouble, 							///< [out] Result (double)
    std::string::const_iterator& itFirst,
    std::string::const_iterator itLast, 		///< [in] String to convert/parse to double
    const std::string& sDecimalPoint,
    const std::string& sThousandsSep
)
{
    fDouble = 0;
    if ( itFirst == itLast ) {
        return false;
    }
    struct lconv * lc;
    lc=localeconv();
    std::string sDecimalPointSystem = lc->decimal_point;


    bool bFound = true;
    std::string sStr(itFirst, itLast);
    boost::replace_all( sStr, sThousandsSep, "" );
    boost::replace_all( sStr, sDecimalPoint, sDecimalPointSystem );

    const char* szIt 	= sStr.c_str();
    const char* szStart = sStr.c_str();
    const char* szEnd 	= sStr.c_str() + sStr.length();
    char* stopStr = NULL;

    while ( fDouble == 0 && ( szIt < szEnd ) ) {
        fDouble = strtod( szIt++, &stopStr );
    }
    if ( fDouble == 0 && (*(--szIt) != '0' ) )	bFound = false;
    int iLen = 	stopStr - szStart;
    itFirst = itFirst + iLen;
    return bFound;
}


/** Parse thru string trying to find something that can parse as a double. */
bool parse_find_double(
    double& fDouble, 							///< [out] Result (double)
    const std::string sInput,
    const std::string& sDecimalPoint,
    const std::string& sThousandsSep
)
{
    std::string::const_iterator it = sInput.begin();
    return parse_find_double( fDouble, it , sInput.end(), sDecimalPoint, sThousandsSep );
}



void test_NumberParse(int argc, char** argv)
{
    printf("test_NumberParse\n");
    const char* loc = setlocale( LC_ALL, NULL);
    printf("loc: %s\n", loc);

    struct lconv * lc;
    lc=localeconv();
    std::string sDecimalPointSystem = lc->decimal_point;
    printf ("Local decimal_point: %s\n",lc->decimal_point);
    printf ("Local thousands_sep: %s\n",lc->thousands_sep);
    printf ("ML: Local sDecimalPointSystem: %s\n",sDecimalPointSystem.c_str());

    std::string sInput = "12.34";
    double fVal;
    bool bFound = parse_find_double( fVal, sInput, ".", ",");
    printf("ML: trimToFloat: '%f'\n", fVal );


}


