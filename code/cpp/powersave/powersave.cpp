#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

#include <boost/format.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/cstdint.hpp>
#include <utf8.h>

#include "parsing_numbers_test.cpp"

using namespace std;
using namespace boost::lambda;

int main(int argc, char* argv[])
{
    
    return  parsing_numbers_test( argc, argv );
    
    if (argc != 2) {
        cout << "\nUsage: docsample filename\n";
        return 0;
    }
    
    
    const char* test_file_path = argv[1];
    string sTestFilePath = test_file_path;
    // Open the test file (must be UTF-8 encoded)

    ofstream outFile( (sTestFilePath + "out").c_str() );
    ifstream fs8(test_file_path);
    if (!fs8.is_open()) {
    cout << "Could not open " << test_file_path << endl;
    return 0;
    }

    // Read the first line of the file

    unsigned line_count = 1;
    string line;
    if (!getline(fs8, line)) 
        return 0;

    // Look for utf-8 byte-order mark at the beginning

    if (line.size() > 2) {
        if (utf8::is_bom(line.c_str()))
          cout << "There is a byte order mark" 
                  " at the beginning of the file\n";
    }

    // Play with all the lines in the file

    do {
		
		cout << endl;
		string::iterator end_it = utf8::find_invalid(line.begin(), line.end());
		vector<utf8::uint32_t> utf32line;
		utf8::utf8to32(line.begin(), end_it,  back_inserter(utf32line));
        // And back to utf-8;

        string utf8line; 
        utf8::utf32to8(utf32line.begin(), utf32line.end(), back_inserter(utf8line));
        // Confirm that the conversion went OK:
			
		std::cout << "line    :" << line << std::endl;
		for_each(utf32line.begin(), utf32line.end(), std::cout << _1 << ' ');
		cout << endl;
		
		vector<utf8::uint32_t>::iterator it32;
		for ( it32 = utf32line.begin(); it32 != utf32line.end(); ++it32 ) {
			cout << boost::format ("%x " ) % *it32;
		}
		cout << endl;
//		for_each(utf32line.begin(), utf32line.end(), std::cout << boost::format ("A:%X" ) );
		std::cout << "utf8line:" << utf8line << std::endl;
//		for_each(line.begin(), line.end(), std::cout << _1 << ' ');

		for( string::const_iterator it = line.begin(); it != line.end(); ++it){
			boost::uint32_t c = 0xFF & static_cast<boost::uint32_t>(*it);
			std::cout << boost::format ("'%c':'%02X' " ) % (unsigned char)(*it) % c ;
		}
		cout << endl;
		
// 		char* twochars = "\xe6\x97\xa5\xd1\x88";
// 		char* w = twochars;
// 		int cp = next(w, twochars + 6);
		string::iterator it8 = line.begin();
		for( ; it8 != line.end();){
			boost::uint32_t cp = utf8::next( it8, line.end() );
			std::cout << boost::format ("'%X' " ) % cp ;
		}
		
		
		cout << endl;
	//	outFile << utf8::convenience::replace_invalid_xml_copy (utf8line, '?') << endl;
		outFile << utf8::convenience::replace_invalid_xml_copy (utf8line, utf8::CODE_POINT_REPLACE_EMPTY ) << endl;
		
        getline(fs8, line);
        line_count++;
    } while (!fs8.eof());


	char sz_invalid_sequence[] = "a\x1d\x80\xe0\xa0\xc0\xaf\xed\xa0\x80z";
	std::string invalid_sequence ( sz_invalid_sequence );
	std::string replace_invalid_result;
//	utf8::replace_invalid_xml (invalid_sequence.begin(), invalid_sequence.end(), back_inserter(replace_invalid_result), '?');
//	utf8::replace_invalid_xml (invalid_sequence.begin(), invalid_sequence.end(), back_inserter(replace_invalid_result), utf8::CODE_POINT_REPLACE_EMPTY );
	
	//utf8::convenience::replace_invalid_xml ( invalid_sequence, replace_invalid_result, '?' );
	replace_invalid_result = utf8::convenience::replace_invalid_xml_copy ( invalid_sequence, '?' );
//	replace_invalid_result = utf8::convenience::replace_invalid_xml_copy ( invalid_sequence, utf8::CODE_POINT_REPLACE_EMPTY );
	
	cout << "replace_invalid_result: " << replace_invalid_result << endl;

	cout << endl;
	for( string::const_iterator it = replace_invalid_result.begin(); it != replace_invalid_result.end(); ++it){
		boost::uint32_t c = 0xFF & static_cast<boost::uint32_t>(*it);
		std::cout << boost::format ("'%c':'%X' " ) % (unsigned char)(*it) % c ;
	}
	cout << endl;
    return 0;
}


#if 0
#include <iostream>
#include <stdio.h>

#include <boost/format.hpp>

#include <url/url_functions.h>
#include <cpaf_session.h>

int main(int argc, char* argv[])
{
  	using namespace std;
	using namespace crawl;
    using boost::format;
    using boost::io::group;

	std::string sStdOut;
  
//	downloadUrl( Url("http://www.doxys.dk/doxys_homepage/index.html"), sStdOut );
//	cout<<sStdOut<<endl;
 
	for (int i = 0; i < 30; i++) {
		cout << "last_input_time: "<<cpaf::system::last_input_time()<<endl;
		cout << "get_tick_count32: "<<cpaf::system::get_tick_count32()<<endl;
		int iIdleTime = cpaf::system::get_tick_count32() - cpaf::system::last_input_time();
		cout << "iIdleTime: "<<iIdleTime<<endl;
		cpaf::system::sleep(1);
	}



	cout << format("get_tick_count64 = (%x) \n") % cpaf::system::get_tick_count64(); 

//	bool bShutdownSuccess = cpaf::system::reboot(true);
//	cout << "Hello world from Veriquin powersave! bShutdownSuccess: "<<bShutdownSuccess<<endl;

	return 0;
}

#endif
