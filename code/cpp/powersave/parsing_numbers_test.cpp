#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

#include <boost/format.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/cstdint.hpp>
#include <boost/algorithm/string.hpp>

#include <cpaf_string_utils.hpp>

namespace cpaf {



} // end namespace


int parsing_numbers_test(int argc, char* argv[])
{
	using namespace cpaf;
//     if (argc != 2) {
//         cout << "\nUsage: docsample filename\n";
//         return 0;
//     } 
    
	std::string sFloat1 = "12.34";
	std::string sFloat2 = "  12.34  ";
	std::string sFloat3 = "  12.34  rs";
	std::string sFloat4 = " 12.34rs ";
	
	double f1 = to_double(sFloat1);
	printf("f1: %f\n", f1 ); 
	double f2 = to_double(sFloat2);
	printf("f2: %f\n", f2 ); 
	double f3 = to_double(sFloat3);
	printf("f3: %f\n", f3 ); 
	double f4 = to_double(sFloat4);
	printf("f4: %f\n", f4 ); 
		
	
	std::string sStr = "3.141592This stopped it";
	const char* str = sStr.c_str();
	char *stopstring;
	double x;
	x = strtod( str, &stopstring );
	printf("string = %s\n", str );
	printf("strtod = %f\n", x );
	printf("   Stopped scan at: %s\n", stopstring );
	int iLen = 	stopstring - str;
	printf("   Len  scan at: %d\n", iLen );
		
// 	std::string::iterator itEndScan = sStr.begin();
	std::string::iterator itEndScan = sStr.begin() + iLen;
		
	std::string sRest( itEndScan, sStr.end() );	
// 	std::string sRest( itEnd, sStr.end() );	
	printf("sRest = %s\n", sRest.c_str() );
		
	
 	std::string::iterator it = sStr.begin();
	std::string::iterator itEnd = sStr.end();
	double f5 =  parse_double(it, itEnd);
	printf("parse_ = %f\n", f5 );
	std::string sRest2( it, sStr.end() );	
	printf("sRest2 = %s\n", sRest2.c_str() );
		
	sStr = "1.237,141592This stopped it";
	double f6 =  parse_double( sStr, ",", "." );
	printf("PARSE_ = %f\n", f6 );
		
	return 0;
}

