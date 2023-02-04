#include "NavigateStateBase.h"
#include <stdio.h>
#include <boost/algorithm/string.hpp>

#include <utils/cpaf_string_utils.hpp>
#include <net/cpaf_http_convenience.h>
#include <filesystem/cpaf_special_dirs.h>
#include <compression/cpaf_compression_functions.h>
#include <utils/string_algorithms.h>
#include <ScriptingClassIF.h>
#include <ScriptMiner.h>

/*
 TODO:
 Clear up use of option, "option name", "option value".
 We want all State classes to use :
 "option" => "option name": Should be used purely as name and only as value if no value is designated
 "option value": This is the one that always should be used for input,javascript, etc.
 "index": Used in DropDownSelectState

 */


namespace crawl {
using namespace boost;
using namespace std;
using namespace cpaf::filesystem;
using namespace cpaf::compression;
namespace fs = boost::filesystem;

// ------------------------------------
// --- Static member initialization ---
// ------------------------------------
const int NavigateStateBase::InvalidOptionIndexE        = -1;
const int NavigateStateBase::FirstOptionIndexE          =  0;
const int NavigateStateBase::UseDefaultCountParameter   = -1000000;


// ------------------------------------
// --- Constructor / Init Functions ---
// ------------------------------------
NavigateStateBase::NavigateStateBase()
    : m_iCurrentOptionIndex(FirstOptionIndexE)
    , m_iEndOptionIndex(FirstOptionIndexE)
    , m_sCurrentOption("")
    , m_sCurrentDomTextValue("")
    , m_sCurrentDomValue("")
    , m_iAddOptionPosCounter(NavigateStateBase::FirstOptionIndexE)
    , m_sCurrentOptionAdd("")
////    , m_sBeginOption("")
    , m_sEndOption("")
    , m_bAutoInputDoIncreaseLength(false)
    , m_bAllMoreSignificantStatesAtEnd(false)
    , m_sUrlResource()
    , m_fileResource()
    , m_eResourceType(resNoneE)
    , m_eResourceFileType(resFileTxtE)
    , m_pScriptMiner(0)
{

}

NavigateStateBase::~NavigateStateBase()
{
}


// -------------------------------
// --- PUBLIC: State functions ---
// -------------------------------

boost::int64_t	NavigateStateBase::nextOption	()
{
    do_nextOption();
    return do_currentOptionIndexGet();
}

int NavigateStateBase::optionToIndex ( const std::string& sOption ) const
{
    return hlp_optionToIndex ( sOption );
}

void NavigateStateBase::start()
{
    ////printf( "ML: lastOptionIndex: '%d'\n", static_cast<int>(lastOptionIndex()) );
    do_start();
}

// ------------------------------
// --- PUBLIC: Info functions ---
// ------------------------------
boost::int64_t NavigateStateBase::beginOptionIndex () const
{
    return firstOptionIndex();
//    int index = optionToIndex( beginOption() );
//    if ( index == InvalidOptionIndexE ) return firstOptionIndex();
//    else return index;
}

boost::int64_t NavigateStateBase::endOptionIndex () const
{
    return do_endOptionIndexGet();
//    int index = optionToIndex( endOption() );
//    if ( index == InvalidOptionIndexE ) return lastOptionIndex();
//    else return index;
}

boost::int64_t NavigateStateBase::numOptions () const
{
//    return endOptionIndex() - beginOptionIndex() +1;
    return endOptionIndex() - firstOptionIndex() +1;
}

bool NavigateStateBase::isOption ( const std::string& sOption ) const
{
    const int index = optionToIndex ( sOption );
    return InvalidOptionIndexE != index;
}


void NavigateStateBase::currentDomTextValue ( const std::string& sDomTextVal )
{
    m_sCurrentDomTextValue = sDomTextVal;
}

const std::string& NavigateStateBase::currentDomTextValue() const
{
    return m_sCurrentDomTextValue;
}


void NavigateStateBase::currentDomValue ( const std::string& sDomVal )
{
    m_sCurrentDomValue = sDomVal;
}

const std::string& NavigateStateBase::currentDomValue() const
{
    return m_sCurrentDomValue;
}


std::string NavigateStateBase::currentOption () const
{
    return hlp_getCurrentOption();
}

void NavigateStateBase::currentOptionSet ( const std::string& sOption )
{
    int index = optionToIndex(sOption);
    if ( InvalidOptionIndexE == index ) {
        index = cpaf::to_int_default(sOption , InvalidOptionIndexE );
    }
    if ( InvalidOptionIndexE != index ) currentOptionIndexSet( index );
}

std::string NavigateStateBase::currentSearchFor () const
{
    return do_indexToSearchVal( do_currentOptionIndexGet() );
}

int NavigateStateBase::currentCount() const
{
    return do_indexToCount( do_currentOptionIndexGet() );
}

boost::int64_t	NavigateStateBase::currentOptionIndex	() const
{
    return do_currentOptionIndexGet();
}

void NavigateStateBase::currentOptionIndexSet( boost::int64_t iIndex )
{
    do_currentOptionIndexSet( iIndex ) ;
}


// -----------------------------------
// --- PUBLIC: Set state functions ---
// -----------------------------------
void NavigateStateBase::optionAdd (
        int iCount
      , const std::string& sValue
      , const std::string& sSearchFor
    )
{
    std::string sOptionVal = do_optionAdd( iCount, sValue, sSearchFor );
    hlp_insertInOptionToIndex( m_iAddOptionPosCounter, sOptionVal );
    ++m_iAddOptionPosCounter;
    m_sCurrentOptionAdd = sOptionVal;
    endOptionIndexSet( lastOptionIndex() ); // Update default endOptionIndex to new last index
}


//void NavigateStateBase::beginOptionSet ( const std::string& sOption )
//{
//    m_sBeginOption = sOption;
//}


void NavigateStateBase::endOptionSet   ( const std::string& sOption )
{
    int index = optionToIndex(sOption);
    if ( InvalidOptionIndexE == index ) {
        index = cpaf::to_int_default(sOption , InvalidOptionIndexE );
    }
    if ( InvalidOptionIndexE != index ) {
        endOptionIndexSet( index );
        m_sEndOption = sOption;
    }

//    const int index = optionToIndex( sOption );
//    if ( index != InvalidOptionIndexE ) {
//        endOptionIndexSet( index );
//        m_sEndOption = sOption;
//    }
}

// ----------------------------------
// --- PUBLIC: Property functions ---
// ----------------------------------

void NavigateStateBase::attributeSet(
      const std::string& sOption
    , const std::string& sAttributeName
    , const std::string& sAttributeValue
    )
{
    m_attributeMap[sOption][sAttributeName] = sAttributeValue;
}

std::string	NavigateStateBase::attributeGet( const std::string& sOption, const std::string& sAttributeName )
{
    AttributeMapT::const_iterator itOption = m_attributeMap.find(sOption);
    if ( itOption != m_attributeMap.end() ) {
        StrStrMapT::const_iterator itAttrName = itOption->second.find(sAttributeName);
        if ( itAttrName != itOption->second.end() ) {
            return itAttrName->second;
        }
    }
    return "";
}

std::string	NavigateStateBase::attributeGet ( const std::string& sAttributeName )
{
    return attributeGet( currentOption(), sAttributeName );
}

void NavigateStateBase::attributeNamesCreate(const std::vector<string>& attributeNames)
{
    m_attributeNames = attributeNames;
}

void NavigateStateBase::attributesAdd(const std::vector<string>& attributeValues)
{
    const auto valuesSize = attributeValues.size();
    const auto namesSize = m_attributeNames.size();
    for ( size_t n = 0; n < valuesSize && n < namesSize; ++n) {
        attributeSet(m_sCurrentOptionAdd, m_attributeNames[n], attributeValues[n] );
    }
}

NavigateStateBase::StrVecT NavigateStateBase::attributeNames() const
{
    return m_attributeNames;
}

void NavigateStateBase::setAttributeNames(const StrVecT &attributeNames)
{
    m_attributeNames = attributeNames;
}

// ----------------------------------
// --- PUBLIC: Resource functions ---
// ----------------------------------

void NavigateStateBase::optionResourceAdd   (
      const std::string& sResourcePath
    , const std::string& sScriptFilterFunction
    , bool bForceDownload
    )
{
    setResourceFile( sResourcePath);
    downloadRemoteResource  ( bForceDownload );

    std::string sFilterFun = "";;
    if ( m_pScriptMiner &&  m_pScriptMiner->scriptingClass()->scriptFunctionExists(sScriptFilterFunction) ) {
        sFilterFun = sScriptFilterFunction;
    }
    readResources (sFilterFun);
}



void NavigateStateBase::setResourceFile(
      const std::string& sUrlOrFilePath
    )
{
    m_eResourceType = resLocalE;
    m_sUrlResource = "";
    string sResPath = sUrlOrFilePath;
    if ( algorithm::contains( sUrlOrFilePath, "http://" ) ) {
        m_eResourceType = resHttpE;
        m_sUrlResource = sUrlOrFilePath;
        algorithm::erase_first(sResPath, "http:/");
    }

    if ( resLocalE == m_eResourceType ) {
        fs::path p(sUrlOrFilePath);
        if ( p.root_directory() == "" ) {
//            m_fileResource = (special_dirs::startup / p).normalize();
            m_fileResource = p.normalize();
        }
        else {
            m_fileResource = p;
        }
    }
    else {
        m_fileResource = fs::path(sResPath).leaf();
//        m_fileResource = special_dirs::startup / fs::path(sResPath).leaf();
    }

    m_eResourceFileType = algorithm::contains(sUrlOrFilePath, ".gz" ) ? resFileGzE : resFileTxtE;
}


void NavigateStateBase::downloadRemoteResource  ( bool bForceDownload )
{
    using namespace cpaf::net;
    if ( resHttpE == resourceType() ) {
        bool bDoDownLoad = !fs::exists( fileResource() ) || bForceDownload;
        if( bDoDownLoad ) {
            curl_http_download_file  ( urlResource(), fileResourceStr() );
        }
    }
}


void NavigateStateBase::openLocalFile ()
{
    if ( resFileTxtE == resourceFileType() ) {
        m_resTxtFileHandle = fopen( fileResourceStr().c_str(), "r" );
    }
    else if ( resFileGzE == resourceFileType() ) {
        m_resGzFileHandle = gz_open( fileResourceStr().c_str(), "r" );
    }
}

void NavigateStateBase::closeLocalFile()
{
    if ( resFileTxtE == resourceFileType() ) {
        fclose(m_resTxtFileHandle);
    }
    else if ( resFileGzE == resourceFileType() ) {
        gz_close(m_resGzFileHandle);
    }

}

bool NavigateStateBase::eofLocalFile () const
{
    bool bEof = true;
    if ( resFileTxtE == resourceFileType() ) {
        bEof = feof(m_resTxtFileHandle);
    }
    else if ( resFileGzE == resourceFileType() ) {
        bEof = gz_eof(m_resGzFileHandle);
    }
    return bEof;
}

std::string NavigateStateBase::readLineFromLocalFile () const
{
    const int LINE_LEN = 8096;
    std::string sLine;
    if ( resFileTxtE == resourceFileType() ) {
        char line[LINE_LEN];
        char* retVal = fgets( line, LINE_LEN, m_resTxtFileHandle );
        if ( retVal != NULL ) {
            sLine = line;
        }
    }
    else if ( resFileGzE == resourceFileType() ) {
        gz_gets( m_resGzFileHandle, sLine, LINE_LEN );
    }
    algorithm::erase_last(sLine, "\n");
    return sLine;
}


// -------------------------------------
// --- PUBLIC: Option data functions ---
// -------------------------------------
const NavigateStateBase::OptionT* NavigateStateBase::getOptionData  ( boost::int64_t iOptionIndex ) const
{
    const size_t iIndex = static_cast<size_t>(iOptionIndex);
    if ( iIndex < m_options.size() ) {
        return &m_options[iIndex];
    }
    return 0;
}

const NavigateStateBase::OptionT* NavigateStateBase::getOptionData  () const
{
    return getOptionData( currentOptionIndex() );
}


// --------------------------------------------------
// --- PRIVATE: Abstract interface (do) functions ---
// --------------------------------------------------
void NavigateStateBase::do_currentOptionIndexSet( boost::int64_t iIndex )
{
    m_iCurrentOptionIndex = iIndex;
}


boost::int64_t NavigateStateBase::do_currentOptionIndexGet() const
{
    return m_iCurrentOptionIndex;
}

boost::int64_t NavigateStateBase::do_endOptionIndexGet  () const
{
    return m_iEndOptionIndex;
}

void NavigateStateBase::do_endOptionIndexSet ( boost::int64_t iIndex )
{
    m_iEndOptionIndex = iIndex;
}


boost::int64_t NavigateStateBase::do_lastOptionIndexGet ()  const
{
    return static_cast<int64_t>(m_options.size()) -1;
}

/** Get option value for given index */
std::string	NavigateStateBase::do_indexToOption ( boost::int64_t iOptionIndex ) const
{
    const size_t optionIndex = static_cast<size_t>(iOptionIndex);
    if ( optionIndex < m_options.size() )  return m_options[optionIndex].sValue;
    else                                   return "";
}

/** Get search value for given index */
std::string	NavigateStateBase::do_indexToSearchVal ( boost::int64_t iOptionIndex	) const
{
    const size_t optionIndex = static_cast<size_t>(iOptionIndex);
    if ( optionIndex < m_options.size() )  return m_options[optionIndex].sSearchFor;
    else                                   return "";
}

/** Get count value for given index */
int	NavigateStateBase::do_indexToCount ( boost::int64_t iOptionIndex	) const
{
    const size_t optionIndex = static_cast<size_t>(iOptionIndex);
    if ( optionIndex < m_options.size() )  return m_options[optionIndex].iCount;
    else                                    return 0;
}

void NavigateStateBase::do_nextOption()
{
    boost::int64_t endIndex = lastOptionIndex();
    if ( allMoreSignificantStatesAtEnd() ) endIndex = endOptionIndex();
    if ( m_iCurrentOptionIndex >= endIndex ) m_iCurrentOptionIndex = firstOptionIndex();
    else ++m_iCurrentOptionIndex;
}

std::string  NavigateStateBase::do_optionAdd (
          int iCount
        , const std::string& sValue
        , const std::string& sSearchFor
        )
{
    std::string value = sValue;
    std::string searchFor = sSearchFor;
    if ( iCount == NavigateStateBase::UseDefaultCountParameter )  iCount = 1;
    if ( value == "" )      value = std::to_string( iCount );
    if ( searchFor == "" )  searchFor = value;

    m_options.push_back(OptionT(iCount, value, searchFor));
    return value;
}

void NavigateStateBase::do_start()
{
    //m_iCurrentOptionIndex = beginOptionIndex();
    m_iCurrentOptionIndex = FirstOptionIndexE;
}

void NavigateStateBase::do_addResourceLine ( const std::string& /*sLine*/ )
{
}

// ---------------------------------
// --- PRIVATE: Helper functions ---
// ---------------------------------

std::string NavigateStateBase::hlp_getCurrentOption() const
{
    return do_indexToOption( do_currentOptionIndexGet() );
}


/** Lookup index for option based on the option value. */
boost::int64_t NavigateStateBase::hlp_optionToIndex (
    const std::string& sOption
 ) const
{
    boost::int64_t iOptionIndex = InvalidOptionIndexE;
    OptionToIndexMapT::const_iterator it = m_optionToIndexMap.find(sOption);
    if ( it != m_optionToIndexMap.end() )  iOptionIndex = it->second;
    return iOptionIndex;
}


void NavigateStateBase::hlp_insertInOptionToIndex (
        boost::int64_t iOptionIndex
    ,   const std::string& sOption
    )
{
    m_optionToIndexMap[sOption] = iOptionIndex;
}

bool NavigateStateBase::hlp_atEndOption () const
{
    bool atEnd  = allMoreSignificantStatesAtEnd() && currentOptionIndex() >= endOptionIndex();
    bool atLast = currentOptionIndex() >= lastOptionIndex();
    return atEnd || atLast;
}

// -----------------------------------
// --- PRIVATE: Resource functions ---
// -----------------------------------
void NavigateStateBase::readResources  ( const std::string& sScriptFilterFunction )
{
    if ( fs::exists( fileResource() ) ) {
        openLocalFile();
        if ( sScriptFilterFunction == "" ) {
            while ( !eofLocalFile() ) {
                std::string sLine = readLineFromLocalFile();
                sLine = trimDefault_fun(sLine);
                ////printf("NavigateStateBase::readResources: '%s'\n", sLine.c_str() );
                do_addResourceLine( sLine );
            }
        }
        else {
            while ( !eofLocalFile() ) {
                std::string sLine = readLineFromLocalFile();
                sLine = m_pScriptMiner->scriptingClass()->callScriptFunction_String(sScriptFilterFunction, sLine);
                if ( sLine != "" ) do_addResourceLine( sLine );
            }
        }
        closeLocalFile();
    }
    else {
        printf("ERR: Navigator could not find resource file: '%s'\n", fileResource().string().c_str() );
    }
}



} // END namespace crawl
