#include "DataWriterXml.h"
#include <boost/algorithm/string.hpp>
#include <utf8.h>
#include <cpaf_libs/utils/cpaf_string_utils.hpp>

using namespace std;

namespace crawl {


DataWriterXml::DataWriterXml( const boost::filesystem::path& outputDir, const std::string sBaseOutputName )
    : DataWriterIF          ( sBaseOutputName       )
    , m_outputDir           ( outputDir             )
    , m_bDoEncloseInCDATA   ( false                 )
    , m_os                  ()
    , m_iIndentLevel        ( 0                     )
    , m_bDoWriteOutputToFile( true                  )
{
}

DataWriterXml::~DataWriterXml()
{
    if ( m_os.is_open() ) m_os.close();
}


// ---------------------------------
// --- PRIVATE: Helper functions ---
// ---------------------------------
const std::string DataWriterXml::fileName ()
{
    if ( baseOutputName() == "" )   return "";
    boost::filesystem::path p = m_outputDir / (baseOutputName() + ".xml");
    return p.string();
}


void DataWriterXml::outputLineToStream(
    std::string sLine
)
{
    ensureOpen();
    if ( !m_os.is_open() )          return;
    if ( !m_bDoWriteOutputToFile )  return;

    outputIndention( m_iIndentLevel );
    m_os << sLine << std::endl;
}


void DataWriterXml::outputIndention(
    int iIndentLevel
)
{
    if ( !m_bDoWriteOutputToFile )  return;
    if ( iIndentLevel < 1	)       return;
    if ( iIndentLevel > 100 )       return;	// Sanity check !!
    while ( iIndentLevel-- ) {
        m_os << "\t"  ;
    }
}

void DataWriterXml::ensureOpen ()
{
    if ( !m_os.is_open() ) {
        if ( doContinueMode() ) {
            long posp;
            m_os.open( fileName().c_str(), ios::in | ios::out );
            m_os.seekg( ios::off_type(0), ios_base::end);
            long posg = m_os.tellg();
            m_os.seekg (posg-8);
            posg = m_os.tellg();
            posp = posg;
            char line[1024];
            m_os.getline (line, 8);
            std::string sLine(line);
            bool endsWithROOT = sLine == "</ROOT>";
            m_os.close();

            if ( endsWithROOT ) {
                m_os.open( fileName().c_str(), ios::in | ios::out );
                m_os.seekp( ios::off_type(posp), ios_base::beg);
                outputLineToStream("<continue>" + std::to_string(continueCounter()) + "</continue>" );
                m_os.close();
            }
            else {
                m_os.open( fileName().c_str(), ios::app | ios::out );
                outputLineToStream("<continue>" + std::to_string(continueCounter()) + "</continue>" );
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
void DataWriterXml::do_close ()
{
    if ( m_os.is_open() )
        m_os.close();
}


void DataWriterXml::do_restart ()
{
    if ( m_os.is_open() )
        m_os.close();
    m_bDoWriteOutputToFile = true;
    m_iIndentLevel = 0;
}


void DataWriterXml::do_configOutputEncloseCDATA  ( bool bDoEncloseInCDATA )
{
    m_bDoEncloseInCDATA = bDoEncloseInCDATA;
}


void DataWriterXml::do_beginMining ()
{
    if ( !doContinueMode() ) {
        m_iIndentLevel = 1;
        outputLineToStream("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
    }
}


void DataWriterXml::do_endMining ()
{
}


void DataWriterXml::do_pushContext (const std::string& context, const string& /*prevContext*/, int iIndentLevel, size_t /*contextCount*/  )
{
    m_iIndentLevel = iIndentLevel;
    outputLineToStream( "<" + context + ">" );
}


void DataWriterXml::do_popContext (const std::string& sContext, int iIndentLevel , size_t /*contextCount*/)
{
    m_iIndentLevel = iIndentLevel;
    outputLineToStream( "</" + sContext + ">" ) ;
}


void DataWriterXml::do_outputValueDirect(const std::string& sFieldName
        , const std::string& sValue
        , int iIndentLevel , size_t /*valuesCount*/)
{
    m_iIndentLevel = iIndentLevel;
    std::string s( "<" + sFieldName + ">" ) ;
    if ( m_bDoEncloseInCDATA ) s += "<![CDATA[";
	
	// TODO: Do we need this replace_invalid_xml ?
	//s += utf8::convenience::replace_invalid_xml_copy( sValue, ' ' );
    s += sValue;
	
    if ( m_bDoEncloseInCDATA ) s += "]]>";
    s +=  "</" + sFieldName + ">" ;
    outputLineToStream( s );
}

void DataWriterXml::do_outputList(const string &fieldName, const std::vector<string> &list, int indentLevel, size_t /*valuesCount*/)
{
    m_iIndentLevel = indentLevel;
    std::string s( "<" + fieldName + ">" ) ;
    if ( m_bDoEncloseInCDATA ) s += "<![CDATA[";

    // TODO: Not really as complete as the json writer version yet!!!
    // TODO: Do we need this replace_invalid_xml ?
    //s += utf8::convenience::replace_invalid_xml_copy( sValue, ' ' );
    string stringList = boost::algorithm::join(list, ",");
    boost::algorithm::replace_all(stringList, ";", ","); // We support that a list element can itself contains elemenst separated by ';' which we split up here and add to the list.

    s += stringList;

    if ( m_bDoEncloseInCDATA )
        s += "]]>";
    s +=  "</" + fieldName + ">" ;
    outputLineToStream( s );

}



} // END namespace crawl

/*
 "Major cleanup in XML output writer and ScriptMiner::startMining functions. Now we only restart in MinerCreator, the crawler simply starts, which means that in this case we only open the output file once. So next step is to enable appending to the output XML file in case we a doing a continue"
  */
