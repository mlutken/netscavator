//#include <MozBrowserWx.h>

//#include <stdio.h>
//#include <boost/filesystem/path.hpp>
//#include <boost/filesystem/operations.hpp>
//#include <boost/thread/mutex.hpp>
//#include <boost/thread/shared_mutex.hpp>
//#include <boost/cstdint.hpp>

//#include "test_DomStateMachine.cpp"
//#include "test_NumberParse.cpp"
//#include "test_FastMap.cpp"
//#include "test_vector_map_unsigned_key.cpp"
//#include "MultipleReaderWriteQueue.cpp"

//#include <string>
//#include <cpaf_http_convenience.h>
//#include <domstate/InputOptionsState.h>

//namespace fs = boost::filesystem;

//int main(int argc, char** argv)
//{
//    using namespace std;
////    using namespace cpaf::net;
////    using namespace crawl;

////    string leafFileName = fs::path( "sdds", fs::native ).string();

////    string line;



////    InputOptionsState ss;
//////    ss.setResourceFile("http://airplaymusic.dk.localhost/INSTALL.txt");
//////    ss.setResourceFile("/home/ml/aaa.txt");
//////    ss.setResourceFile("/home/ml/aaa.txt.gz");
////    ss.setResourceFile( "http://www.airplaymusic.dk/public_files/miners/files/word_artist.txt.gz" );
////    ss.downloadRemoteResource(false);
////    ss.openLocalFile();
////    while ( !ss.eofLocalFile() ) {
////        line = ss.readLineFromLocalFile();
////        printf("L: '%s'\n", line.c_str() );
//////        printf("L: '%s'", line.c_str() );
////    }
////    ss.closeLocalFile();

////    //root_name( )

////    printf ("urlResource: '%s'\n", ss.urlResource().c_str() );
////    printf ("fileResourceStr: '%s'\n", ss.fileResourceStr().c_str() );
//   // curl_http_download_file  ( "http://airplaymusic.dk.localhost/INSTALL.txt", "aaa.txt" );
//   // curl_http_download_file  ( "http://www.airplaymusic.dk/public_files/miners/files/test.txt", "ddd.txt" );
//   // curl_http_download_file  ( "http://www.airplaymusic.dk/public_files/miners/files/word_artist.txt.gz", "word_artist.txt.gz" );


//    //	test_CommandLineParser( argc, argv);
//    //test_DomStateMachine( argc, argv);
//    //test_DomStateMachine1( argc, argv);
//    //test_NumberParse(argc, argv );
////    test_sparse_vector(argc, argv );

// //   ModuloFifo_threadTest1();

//	return 0;
//}



#include <stdio.h>
#include <iostream>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <cpaf_string_utils.hpp>
#include <utils/StringFinder.h>
//#include <shadow.h>

#define ARRAY_SIZE 1000*1000
#define NUM_TEST 100

using namespace std;
using namespace boost;


class Roman
{
public:
    enum ErrorHandlingModeE { eNone, eReturnValue, eException, eCommandLineDebug };

    explicit Roman ( ErrorHandlingModeE eErrorHandlingMode = eReturnValue )
        : m_eErrorHandlingMode ( eErrorHandlingMode)
        , m_sRomanChars("MDCLXVI")
        , m_sLastError("")
    {

    }

    std::string     lastError   () const    {   return m_sLastError; }

    /** Convert decimal number to Roman.  */
    std::string toRoman( int iDecimal )
    {
        m_sLastError = "";
        int aRomanValues[] = { 1000, 500, 100, 50, 10, 5, 1, 0, 0 };   // Last zeroes to ease out of bounds handling

        if ( iDecimal < 1 || iDecimal > 3000 )  {
            m_sLastError = "Valid decimal numbers are 1 to 3000";
            handleError();
            return "";
        }

        string sRoman = "";

        for ( size_t i = 0; i < m_sRomanChars.size(); ) {

            int iDecimalBeforeIteration = iDecimal;
            int iCount = iDecimal / aRomanValues[i];
//            printf ("LOOP %lu [%d] : iCount: %d\n", i, aRomanValues[i], iCount );
            // We need to handle 500, 50, 5 a little differently since they cannot be repeated
            if ( i % 2 == 0 ) { // 1000, 100, 10, 1
//                printf("  WHOLES i = 1000, 100, 10, 1: %lu\n", i );
                if ( 0 == iCount ) {
                    // In general we should continue now, but we check for the 'substract' case first
                    int iSubstractDivisor = aRomanValues[i] - aRomanValues[i+2];
                    iCount = iDecimal / iSubstractDivisor; // Here we try dividing by 900, 90, 9
                    if ( 1 == iCount )  {
                        // Handle the 'substract' cases iCount == 1 here always
                        assert( iCount == 1 );
                        assert( i + 2 < m_sRomanChars.size() );
//                        cout << "    WHOLE SUB " << "first " << m_sRomanChars[i+2] << "  second " << m_sRomanChars[i] << endl;
                        sRoman += m_sRomanChars[i+2];
                        sRoman += m_sRomanChars[i];
                        iDecimal = iDecimal - iSubstractDivisor;
                    }
                }
                else {
                    assert( iCount < 4 );
                    for ( int n = 0; n < iCount; n++ )  sRoman += m_sRomanChars[i];
                    iDecimal = iDecimal - aRomanValues[i]*iCount;
                }
            }
            else {  // 500, 50, 5
//                printf("  HALVES i = 500, 50, 5: %lu\n", i );
                if ( 0 == iCount ) {
                    // In general we should continue now, but we check for the 'substract' case first
                    int iSubstractDivisor = aRomanValues[i] - aRomanValues[i+1];
                    iCount = iDecimal / iSubstractDivisor; // Here we try dividing by 400, 40, 4
                    if ( 1 == iCount )  {
                        // Handle the 'substract' cases iCount == 1 here always
                        assert( i + 1 < m_sRomanChars.size() );
                        sRoman += m_sRomanChars[i+1];
                        sRoman += m_sRomanChars[i];
                        iDecimal = iDecimal - iSubstractDivisor;
                    }
                }
                else {
                    assert( iCount == 1 ); // iCount should always be 0 or 1 for the halves
//                    printf ("    XX: %lu [%d] : %s, iCount: %d\n", i, aRomanValues[i], sRoman.c_str(), iCount );
                    sRoman += m_sRomanChars[i];
                    iDecimal = iDecimal - aRomanValues[i];
                }
            }
//            printf ("      sRoman after iteration %lu %s,  rest iDecimal: %d\n", i, sRoman.c_str(), iDecimal );
            if ( iDecimalBeforeIteration == iDecimal ) i++;

        }

        handleError();
        return sRoman;
    }

    /** Convert Roman number to decimal.  */
    int toDecimal( std::string sRoman)
    {
        vector<int> vRoman;
        algorithm::to_upper(sRoman);

        sRoman = "Z" + sRoman + "??";   // To eliminate out of bounds problems/handling
        m_sLastError = "";

        for ( size_t i = 0; i < sRoman.size(); i++ )
        {
            char c = sRoman[i];
            if ( 0 < i && i < sRoman.size() -2 && m_sRomanChars.find(c) == string::npos) {
                m_sLastError = string("Illegal char: ") + c;
            }
            vRoman.push_back( getCharValue(sRoman[i]));
        }

        int val = 0;
        for ( size_t i = 1; i < vRoman.size()-2; i++ )
        {
//            printf("%lu => %s\n", i, (string("") + sRoman[i]).c_str() );
            int iFac = 1;
            int prvVal = vRoman[i-1];
            int curVal = vRoman[i];
            int nxtVal = vRoman[i+1];
            if ( (prvVal + curVal + nxtVal + vRoman[i+2]) == 4*curVal ) m_sLastError = string("4 equal litterals in a row: ") + sRoman[i];
            if ( curVal < nxtVal ) {
                if ( !isSubValue(curVal)    )  m_sLastError = string("Illegal sub value: ") + sRoman[i];
                if ( nxtVal / curVal > 10   )  m_sLastError = string("Substract sequence: ") + sRoman[i] + sRoman[i+1] + " not allowed";
                if ( prvVal < nxtVal        )  m_sLastError = string("Two substract litterals in a row: ")  +  sRoman[i-1] + sRoman[i] + " " + cpaf::to_string(i);
                iFac = -1;
            }
            val += curVal*iFac;
        }
        if ( handleError() && eReturnValue == m_eErrorHandlingMode )    val = 0;

        return val;
    }


private:

    bool    handleError ()
    {
        bool errorDetected = m_sLastError != "";
        if ( errorDetected ) {
            if      ( eCommandLineDebug == m_eErrorHandlingMode )   cout << "Error: " << m_sLastError << endl;
            //else if ( eException        == m_eErrorHandlingMode )   throw m_sLastError;
        }
        return errorDetected;
    }


    /**
    Get value of Roman char.
    "Many ways to Rome": Yes, here we could just as well have used an associative
     container/dictionary as for example a member and looked up the Roman char value. */
    int getCharValue( char c )
    {
        c = toupper(c); // We could omit this since we always input in uppercase as it is now.
        switch ( c )
        {
        case 'I' : return 1;
        case 'V' : return 5;
        case 'X' : return 10;
        case 'L' : return 50;
        case 'C' : return 100;
        case 'D' : return 500;
        case 'M' : return 1000;
        case 'Z' : return 1001; // T avoid false detection of two substract chars in a row for numbers starting with CM...
        default: return 0;
        }
    }

    /** Determine whether a Roman char (ie. its equivalent decimal value) is allowed as
        substraction value , which only I=1, X=10 and C=100 are. */
    bool isSubValue( int val )
    {
        return val == 1 || val == 10 || val == 100;
    }

    // ---------------------
    // --- Private: Data ---
    // ---------------------
    ErrorHandlingModeE  m_eErrorHandlingMode;
    std::string         m_sRomanChars;
    std::string         m_sLastError;
};




int mainRoman(int argc, char** argv)
{

    cout << "Roman <=> Decimal converter. Input a decimal or a roman number and press ENTER. 'exit' to exit program, 'all' to print all." << endl;

    Roman r( Roman::eCommandLineDebug );
    string sRoman;
    cin >> sRoman;
    if ( sRoman == "all" ) {
        for ( int i = 0; i <= 3000; i++ ) {

            string sRoman = r.toRoman(i);
            int iDecimal = r.toDecimal(sRoman);
            assert(i == iDecimal);
            printf ( "%d => %s : control %d\n", i, sRoman.c_str(), iDecimal );
        }
    }
    else {
        int iDecimal = cpaf::to_int(sRoman);
        if ( iDecimal != 0 ) {
            sRoman = r.toRoman( iDecimal );
            cout << "Decimal to Roman: " << iDecimal << " => " << sRoman << endl;
        }
        else {
            iDecimal = r.toDecimal( sRoman );
            cout << "Roman to Decimal: " << sRoman << " => " << iDecimal << endl;
        }
    }
    return 0;
}


using namespace crawl;

int main(int argc, char** argv)
{

    cout << "String finder test" << endl;

    string str1("abc-*-ABC-*-aBc");
    // Find all 'abc' substrings (ignoring the case)
    // Create a find_iterator
    typedef find_iterator<string::iterator> string_find_iterator;
    string_find_iterator itBegin = string_find_iterator();
    string_find_iterator itEnd = string_find_iterator();
    itBegin =  make_find_iterator(str1, first_finder("abc", is_iequal()) );
    for( ;
        itBegin!=string_find_iterator();
        ++itBegin)
    {
        cout << copy_range<std::string>(*itBegin) << endl;
    }

    StringFinder sf("as > Kim Larsen - Midt om natten");

    cout << "1: '" << sf.currentValue() << "'" << endl;
    sf.findBeginNext(">");
    cout << "2: '" << sf.currentValue() << "'" << endl;
    sf.findEndNext(" - ");
    cout << "3: '" << sf.currentValue() << "'" << endl;


    sf.newSearch();
    cout << "4: '" << sf.currentValue() << "'" << endl;
    sf.findBeginNext(" - ");
    cout << "5: '" << sf.currentValue() << "'" << endl;

    cout << "6: '" << sf.findBetween(">", " - ") << "'" << endl;
    cout << "7: '" << sf.findBetween(" - ", "") << "'" << endl;

    return 0;
}
