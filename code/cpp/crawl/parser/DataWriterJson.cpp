#include "DataWriterJson.h"
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <utf8.h>
#include <cpaf_libs/utils/cpaf_string_utils.hpp>
#include <Configuration.h>

using namespace std;

namespace crawl {

/*
contextBegin("item");
outputDirect("val", "12");
outputDirect("my_list", "1");
outputDirect("my_list", "2");
outputDirect("my_list", "3");
contextBegin("sub_list");
outputDirect("subval", "12");
outputDirect("subval2", "12");
contextEnd();
outputDirect("val2", "12");
contextEnd();

*/

DataWriterJson::DataWriterJson( const boost::filesystem::path& outputDir, const std::string sBaseOutputName )
    : DataWriterIF          ( sBaseOutputName       )
    , m_outputDir           ( outputDir             )
    , m_bDoEncloseInCDATA   ( false                 )
    , m_os                  ()
    , m_iIndentLevel        ( 0                     )
{
}

DataWriterJson::~DataWriterJson()
{
    if ( m_os.is_open() ) m_os.close();
}


// ---------------------------------
// --- PRIVATE: Helper functions ---
// ---------------------------------
const std::string DataWriterJson::fileName ()
{
    if ( baseOutputName() == "" )   return "";
    boost::filesystem::path p = m_outputDir / (baseOutputName() + ".json");
    return p.string();
}


void DataWriterJson::outputLineToStream(
    std::string sLine
)
{
    ensureOpen();
    if ( !m_os.is_open() )         return;
    if ( !doWriteOutputToFile() )  return;

    outputIndention( m_iIndentLevel );
    m_os << utf8::convenience::replace_invalid_json_copy_cautious(sLine, 0x20) << std::endl;
}


void DataWriterJson::outputIndention(
    int iIndentLevel
)
{
    if ( !doWriteOutputToFile() )   return;
    if ( iIndentLevel < 1	)       return;
    if ( iIndentLevel > 100 )       return;	// Sanity check !!
    while ( iIndentLevel-- ) {
        m_os << "\t"  ;
    }
}

void DataWriterJson::ensureOpen ()
{
    if ( !m_os.is_open() ) {
        if ( doContinueMode() ) {
            long posp;
            m_os.open( fileName().c_str(), ios::in | ios::out );
            m_os.seekg( ios::off_type(0), ios_base::end);
            long posg = m_os.tellg();
            m_os.seekg (posg-2);
            posg = m_os.tellg();
            posp = posg;
            char line[1024];
            m_os.getline (line, 2);
            std::string sLine(line);
            bool endsWithROOT = sLine == "]";
            m_os.close();

            if ( endsWithROOT ) {
                m_os.open( fileName().c_str(), ios::in | ios::out );
                m_os.seekp( ios::off_type(posp), ios_base::beg);

                outputLineToStream("{ \"continue\":" + std::to_string(continueCounter()) + " }," );
                m_os.close();
            }
            else {
                m_os.open( fileName().c_str(), ios::app | ios::out );
                outputLineToStream(",{ \"continue\":" + std::to_string(continueCounter()) + " }," );
                m_os.close();
            }
            m_os.open( fileName().c_str(), ios_base::app  | ios::out );

        }
        else {
            m_os.open( fileName().c_str(), ios_base::trunc  | ios::out );
        }
    }
}


// ------------------------------------
// --- PRIVATE: Writer do_functions ---
// ------------------------------------
void DataWriterJson::do_close ()
{
    if ( m_os.is_open() ) m_os.close();
}


void DataWriterJson::do_restart ()
{
    if ( m_os.is_open() )
        m_os.close();
    m_iIndentLevel = 0;
}


void DataWriterJson::do_configOutputEncloseCDATA  ( bool bDoEncloseInCDATA )
{
    m_bDoEncloseInCDATA = bDoEncloseInCDATA;
}


void DataWriterJson::do_beginMining ()
{
//    if ( !doContinueMode() ) outputLineToStream("[");
//    outputLineToStream("{");
}


void DataWriterJson::do_endMining ()
{
}


void DataWriterJson::do_pushContext ( const std::string& newContext, const std::string& prevContext,
                                      int iIndentLevel, size_t contextCount )
{
    using namespace std;
    m_iIndentLevel = iIndentLevel;
    if (contextCount > 1)
        outputLineToStream(",");
    std::string s = "";

    //bool outputContextLineToStream = false;

    const bool curContextIsList = contextIsList(newContext);
    if (curContextIsList) {
        if (newContext == "ROOT") {
            if (!doContinueMode())
                s += "[";
        }
        else
            s += "\"" + newContext + "\": [";
    }
    else {
        const bool prevContextIsList = contextIsList(prevContext);
        if (prevContextIsList || newContext == "" || newContext == "ROOT") {
            s += "{";
            //outputContextLineToStream = true;
        }
        else {
            s += "\"" + newContext + "\": {";
        }
    }
    outputLineToStream(s);
//    if (outputContextLineToStream) {
//        outputIndention( 1 );   // Add extra indention
//        outputLineToStream("\"context\":\"" + newContext + "\"");
//    }

}


void DataWriterJson::do_popContext ( const std::string& sContext, int indentLevel, size_t /*contextCount*/ )
{
    using namespace std;
    m_iIndentLevel = indentLevel;
    if ( contextIsList(sContext))
        outputLineToStream( "]" ) ;
    else
        outputLineToStream( "}" ) ;
}


void DataWriterJson::do_outputValueDirect(const std::string& fieldName
        , const std::string& sValue
        , int indentLevel, size_t valuesCount)
{
//    cout << "DBG DataWriterJson::do_outputValueDirect: '" << fieldName
//         << "'  indentLevel: " << indentLevel
//         << "'  valuesCount: " << valuesCount
//         << endl;
    string sVal = boost::algorithm::replace_all_copy(sValue, "\"", "\\\"");
    m_iIndentLevel = indentLevel;
    std::string s = valuesCount > 1 ? "," : "";
    s += "\"" + fieldName + "\":" ;
    s += "\"" + sVal + "\"";
    outputLineToStream( s );
}

void DataWriterJson::do_outputList(const string& fieldName, const std::vector<string> &list, int indentLevel, size_t valuesCount)
{
    cout << "DBG DataWriterJson::do_outputList: '" << fieldName
         << "'  indentLevel: " << indentLevel
         << "'  valuesCount: " << valuesCount
         << endl;
    string value = "";
    int i = 0;
    for ( const string& elem : list) {
        string sub_split_char = ",";
        if (boost::algorithm::contains(elem, ";")) sub_split_char = ";";
        cpaf::StringVecT sub_elems = cpaf::splitv_trim(elem, sub_split_char); // We support that a list element can itself contain elements separated by ';' or ',' which we split up here and add to the list.
        for (const string& e : sub_elems ) {
            string val = boost::algorithm::replace_all_copy(e, "\"", "\\\"");
            if (i > 0) value += ",";
            value += "\"" + val + "\"";
            ++i;
        }
    }
    m_iIndentLevel = indentLevel;

    std::string s = valuesCount > 1 ? "," : "";
    s += "\"" + fieldName + "\":" ;

    s += "[" + value + "]";
    outputLineToStream( s );

}


} // END namespace crawl
