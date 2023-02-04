#include "DataWriterIF.h"
#include <boost/algorithm/string.hpp>

using namespace std;

namespace crawl {


DataWriterIF::DataWriterIF (
        const std::string& sBaseOutputName
        )
    : m_sBaseOutputName     ( sBaseOutputName   )
    , m_bDoContinueMode     ( false             )
    , m_iContinueCounter    ( 0                 )
    , m_stringSearch        ( 0                 )
{
}

DataWriterIF::~DataWriterIF ()
{
}

void DataWriterIF::doContinueModeSet   ( bool bDoContinue, int iContinueCounter )
{
    m_bDoContinueMode = bDoContinue;
    m_iContinueCounter = iContinueCounter;
}


void DataWriterIF::restart ( const std::string& sBaseOutputName )
{
    if ( sBaseOutputName != "" )    m_sBaseOutputName = sBaseOutputName;
//        m_sBaseOutputName = sBaseOutputName;
    do_restart();
}

void DataWriterIF::endMining()
{
    do_endMining();
}

bool DataWriterIF::contextIsList(const string& fieldName) const
{
    return fieldName == "ROOT" || fieldName == "" || boost::algorithm::ends_with(fieldName, "_list");
//    return boost::algorithm::ends_with(fieldName, "_list");
}

bool DataWriterIF::doWriteOutputToFile() const
{
    return m_doWriteOutputToFile;
}

void DataWriterIF::doWriteOutputToFileSet(bool doWriteOutputToFile)
{
    m_doWriteOutputToFile = doWriteOutputToFile;
}


} // END namespace crawl

