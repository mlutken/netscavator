
#include <iostream> 
#include <boost/format.hpp> 
#include <boost/regex.hpp> 
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/regex.hpp>
#include <boost/static_assert.hpp>
#include <utf8.h>
#include <cpaf_libs/utils/cpaf_stl_utils.h>
#include <cpaf_libs/utils/cpaf_string_utils.hpp>

#include <utils/string_algorithms.h>
#include <utils/string_base.h>
#include <Configuration.h>
#include "StringSearch.h"
#include <DataWriterIF.h>

using namespace std;

namespace crawl { 

class Configuration;


/*

    contextBegin("myitem");
    outputDirect("val1", "1");
    outputDirect("val2", "2");
    outputDirect("my_list", "l1");
    outputDirect("my_list", "l2");
    outputDirect("my_list", "l3");
    contextBegin("sub_list");
    contextBegin("subitem");
    outputDirect("subval11", "s11");
    outputDirect("subval21", "s21");
    contextEnd();
    contextBegin("subitem");
    outputDirect("subval12", "s12");
    outputDirect("subval22", "s22");
    contextEnd();
    contextEnd();
    outputDirect("val3", "3");
    outputDirect("val4", "4");
    outputDirect("my2_list", "ml1");
    outputDirect("my2_list", "ml2");
    outputDirect("my2_list", "ml3");
    contextEnd();

*/

// ------------------------------------
// --- Static member initialization ---
// ------------------------------------

// ------------------------------------
// --- Constructor / Init Functions ---
// ------------------------------------


StringSearch::StringSearch(
            boost::shared_ptr<DataWriterIF> pDataWriter
        ,   boost::shared_ptr<Configuration> pConfig )
        :   m_pConfig(pConfig)
{
    if ( pDataWriter ) m_dataWriters.push_back(pDataWriter);
    reset();
}



StringSearch::StringSearch(
            boost::shared_ptr<DataWriterIF> pDataWriter1
        ,   boost::shared_ptr<DataWriterIF> pDataWriter2
        ,   boost::shared_ptr<Configuration> pConfig )
    :   m_pConfig(pConfig)
{
    if ( pDataWriter1 ) m_dataWriters.push_back(pDataWriter1);
    if ( pDataWriter2 ) m_dataWriters.push_back(pDataWriter2);
    reset();
}

StringSearch::StringSearch(
        const DataWriterVecT& dataWriters
        , boost::shared_ptr<Configuration> pConfig )
    :   m_pConfig(pConfig)
{
    m_dataWriters = dataWriters;
    reset();
}

void StringSearch::assignDataWriters  ( const DataWriterVecT dataWriters )
{
    m_dataWriters = dataWriters;
}


void StringSearch::restart( const std::string sBaseOutputName )
{
    reset();
    dwRestart(sBaseOutputName);
}


void StringSearch::outputNameSet  ( const std::string sBaseOutputName )
{
    for( boost::shared_ptr<DataWriterIF> pDW : m_dataWriters ) {
        pDW->baseOutputNameSet( sBaseOutputName );
    }
}

void StringSearch::doContinueModeSet ( bool bDoContinue, int iContinueCounter )
{
    m_bDoContinueMode = bDoContinue;
    dwDoContinueModeSet( bDoContinue, iContinueCounter );
}



void StringSearch::dataWriterOutputClose ()
{
    for( boost::shared_ptr<DataWriterIF> pDW : m_dataWriters ) {
        pDW->close();
    }
}


void StringSearch::reset ()
{
    configOutputWriteToFile(true);
    m_bDebugOutput              = false;
    m_sSearchIn                 = "";
    m_sCurrentValue             = "";
    m_bDoEncloseInCDATA         = false;
    m_pCurContextVals           = StrStrMapPtrT(new StrStrMapT);
    while ( !m_ContextStack.empty())
        m_ContextStack.pop();

    m_curContextFallbackVals.clear();
    m_bDoContinueMode           = false;
}



// ------------------------
// --- Parser Functions ---
// ------------------------
/** Initiate a new parse. */
void
StringSearch::newSearchString ( 
        std::string const& sSearchIn, 		///< [in] String to search in
        std::string const& sFieldName 		///< [in] Database field name of new value
        )
{
    m_sSearchIn = sSearchIn;
    newSearch( sFieldName );
    resetMarkersBeginEnd();	// Also assigns current value from m_sSearchIn
}


/** Initiate a new parse of the current search string. */
void 
StringSearch::newSearch(
        std::string const& sFieldName 		///< [in] Database field name of new value
        )
{
    resetMarkersToPageTop();
    beginNewValue ( sFieldName );
}

/** Search to see if a given regex can be found on the page.
\return True if the given regex can be found using regex_search. */
bool 
StringSearch::canFindRegex ( 
        std::string const& sRegex
        ) const
{
    using namespace boost;
    using namespace std;
    regex expr( sRegex );
    smatch what;
    bool bMatch = false;
    if(regex_search(m_sSearchIn, what, expr))
    {
        bMatch = true;
    }
    return bMatch;
}

void StringSearch::beginNewValue ( 
        std::string const& sFieldName 		///< [in] Database field name of new value
        )
{
    m_sCurrentFieldName = sFieldName;   // TODO: m_sCurrentFieldName can be removed since it seems not to be used.
}

// ------------------------
// --- Parse Functions ---
// ------------------------

bool StringSearch::parseRegex		(
        int iCount, 				///< [in] Stop at match number.
        const std::string& sRegex,	///< [in] Regular expression.
        EMatchPos postMarkerPos,	///< [in] Use the beginning or end og regex match when assigning
        bool bIgnoreCase,			///< [in] Case insensitive compares ?
        bool bParseTo	)			///< [in] True => Current value are set to string up-to match, False => Current value are set to actual match ( i.e. match[0] )
{
    using namespace boost;

    if ( iCount < 1	)	return false;
    boost::match_flag_type 								flags 			= boost::match_default;
    regex::flag_type									constructFlags 	= regex::perl;

    // Construct regular expression
    if ( bIgnoreCase )	constructFlags |= regex::icase;
    boost::regex 		expression (sRegex, constructFlags);

    // Prepare parse-in string
    m_sParseIn.assign ( m_itSubStrBegin, m_itSubStrEnd );

    std::string::const_iterator							itBegin			= m_sParseIn.begin();
    std::string::const_iterator							itParseInBegin 	= m_sParseIn.begin();
    std::string::const_iterator							itEnd			= m_sParseIn.end();

    while( regex_search( itBegin, itEnd, m_parseMatchResults, expression, flags) )
    {
        // update search position:
        itBegin = m_parseMatchResults[0].second;
        if ( --iCount == 0 ) break;
        // update flags:
        flags |= boost::match_prev_avail;
        flags |= boost::match_not_bob;
    }
    bool bFound = ( iCount == 0 ) && ( itBegin <= itEnd ) ;
    if ( bFound ) {
        // Assign current value in case we found a match
        if ( postMarkerPos == MATCH_FIRST ) itBegin = m_parseMatchResults[0].first;
        else								itBegin = m_parseMatchResults[0].second;

        if ( bParseTo )	m_sCurrentValue.assign( itParseInBegin, itBegin );
        else			m_sCurrentValue = m_parseMatchResults[0];
        m_sParseRest.assign( itBegin, itEnd );

        // Prepare for next call tp parseXX
        m_sSearchIn 	= m_sParseRest;
        m_itSubStrBegin = m_sSearchIn.begin();
        m_itSubStrEnd 	= m_sSearchIn.end();
    }
    return bFound;
}



bool StringSearch::parseToString	( 
        int iCount,
        const std::string& sSubstring,
        EMatchPos postMarkerPos,
        bool bIgnoreCase	)
{
    using namespace boost;
    if ( iCount < 1	)	return false;
    StringRangeConstT itRangeResult( m_itSubStrBegin,	m_itSubStrBegin );	// Initialize result range to empty
    StringRangeConstT itRangeSearch( m_itSubStrBegin,  	m_itSubStrEnd 	);

    StringFindConstIteratorT it;
    if ( bIgnoreCase ) 	it = make_find_iterator( itRangeSearch, first_finder(sSubstring, is_iequal()) ) ;
    else				it = make_find_iterator( itRangeSearch, first_finder(sSubstring, is_equal()) ) ;
    for ( ; it!=StringFindConstIteratorT(); ++it) {
        itRangeResult = *it;
        if ( --iCount == 0 ) break;
    }
    bool bFound = ( iCount == 0 ) && itRangeResult ;			// itRange is convertible to bool. True if a match was found
    if ( bFound ) {
        // Assign current value in case we found a match
        std::string::const_iterator		itPos;
        if ( postMarkerPos == MATCH_FIRST ) itPos = itRangeResult.begin();
        else								itPos = itRangeResult.end();
        m_sCurrentValue.assign( m_itSubStrBegin, itPos );
        m_sParseRest.assign( itPos, m_itSubStrEnd );

        // Prepare for next call to parseXX
        m_sSearchIn 	= m_sParseRest;
        m_itSubStrBegin = m_sSearchIn.begin();
        m_itSubStrEnd 	= m_sSearchIn.end();
    }
    return bFound;		// itRange is convertible to bool. True if a match was found
}


bool StringSearch::parseToEnd	( )
{
    using namespace boost;
    m_sCurrentValue.assign ( m_itSubStrBegin, m_itSubStrEnd );
    m_sParseRest	= "";
    m_sSearchIn 	= "";
    m_itSubStrBegin = m_sSearchIn.begin();
    m_itSubStrEnd 	= m_sSearchIn.end();
    return m_sCurrentValue != "";
}



// ------------------------
// --- Marker Functions ---
// ------------------------


/** */
void StringSearch::resetMarkersToPageTop() const 
{
    m_itSubStrBegin	= m_sSearchIn.begin();
    m_itSubStrEnd	= m_sSearchIn.begin();
}

/** */
void StringSearch::resetMarkersToPageBottom() const 
{
    m_itSubStrBegin	= m_sSearchIn.end();
    m_itSubStrEnd	= m_sSearchIn.end();
}


void
StringSearch::setEndToPageBottom () 	const 
{
    m_itSubStrEnd	= m_sSearchIn.end();
}

// --------------- New --------------

/** */
void StringSearch::resetMarkersBeginEnd() 
{
    m_sCurrentValue	= m_sSearchIn;	// Restore current value.
    m_itSubStrBegin	= m_sSearchIn.begin();
    m_itSubStrEnd	= m_sSearchIn.end();
}



/** */
bool StringSearch::findBeginNext ( 
        int iCount, 						///< [in]
        const std::string& 	sPattern, 		///< [in]
        EMatchPos 			setBeginToPos	///< [in] Update 'Begin' marker to first or last position in match.
        )
{
    using namespace boost;
    if ( iCount < 1	)	return false;
    StringRangeConstT itRangeResult( m_itSubStrBegin,	m_itSubStrBegin );	// Initialize result range to empty
    StringRangeConstT itRangeSearch( m_itSubStrBegin,  	m_itSubStrEnd 	);

    for ( StringFindConstIteratorT It= make_find_iterator( itRangeSearch, first_finder(sPattern, is_equal())); It!=StringFindConstIteratorT(); ++It) {
        itRangeResult = *It;
        if ( --iCount == 0 ) break;
    }
    bool bFound = ( iCount == 0 ) && itRangeResult ;			// itRange is convertible to bool. True if a match was found
    if ( bFound ) {
        // Assign 'begin' in case we found a match
        if ( setBeginToPos == MATCH_FIRST ) m_itSubStrBegin = itRangeResult.begin();
        else								m_itSubStrBegin = itRangeResult.end();
        setValueBeginEnd();										// Assign result to current value
    }
    return bFound;		// itRange is convertible to bool. True if a match was found
}


/** */
bool StringSearch::findEndNext ( 
        int iCount, 						///< [in]
        const std::string& 	sPattern, 		///< [in]
        EMatchPos  			setEndToPos		///< [in] Update 'End' marker to first or last position in match.
        )
{
    using namespace boost;
    if ( iCount < 1	)	return false;
    StringRangeConstT itRangeResult( m_itSubStrBegin,	m_itSubStrBegin );	// Initialize result range to empty
    StringRangeConstT itRangeSearch( m_itSubStrBegin,  	m_itSubStrEnd 	);

    for ( StringFindConstIteratorT It= make_find_iterator( itRangeSearch, first_finder(sPattern, is_equal())); It!=StringFindConstIteratorT(); ++It) {
        itRangeResult = *It;
        if ( --iCount == 0 ) break;
    }
    bool bFound = ( iCount == 0 ) && itRangeResult ;			// itRange is convertible to bool. True if a match was found
    if ( bFound ) {
        // Assign 'end' in case we found a match
        if ( setEndToPos == MATCH_FIRST )	m_itSubStrEnd = itRangeResult.begin();
        else								m_itSubStrEnd = itRangeResult.end();
        setValueBeginEnd();										// Assign result to current value
    }
    return bFound;		// itRange is convertible to bool. True if a match was found
}


/** */
bool StringSearch::ifindBeginNext ( 
        int iCount, 						///< [in]
        const std::string& 	sPattern, 		///< [in]
        EMatchPos 			setBeginToPos	///< [in] Update 'Begin' marker to first or last position in match.
        )
{
    using namespace boost;
    if ( iCount < 1	)	return false;
    StringRangeConstT itRangeResult( m_itSubStrBegin,	m_itSubStrBegin );	// Initialize result range to empty
    StringRangeConstT itRangeSearch( m_itSubStrBegin,  	m_itSubStrEnd 	);

    for ( StringFindConstIteratorT It= make_find_iterator( itRangeSearch, first_finder(sPattern, is_iequal())); It!=StringFindConstIteratorT(); ++It) {
        itRangeResult = *It;
        if ( --iCount == 0 ) break;
    }
    bool bFound = ( iCount == 0 ) && itRangeResult ;			// itRange is convertible to bool. True if a match was found
    if ( bFound ) {
        // Assign 'begin' in case we found a match
        if ( setBeginToPos == MATCH_FIRST ) m_itSubStrBegin = itRangeResult.begin();
        else								m_itSubStrBegin = itRangeResult.end();
        setValueBeginEnd();										// Assign result to current value
    }
    return bFound;		// itRange is convertible to bool. True if a match was found
}


/** */
bool StringSearch::ifindEndNext ( 
        int iCount, 						///< [in]
        const std::string& 	sPattern, 		///< [in]
        EMatchPos  			setEndToPos		///< [in] Update 'End' marker to first or last position in match.
        )
{
    using namespace boost;
    if ( iCount < 1	)	return false;
    StringRangeConstT itRangeResult( m_itSubStrBegin,	m_itSubStrBegin );	// Initialize result range to empty
    StringRangeConstT itRangeSearch( m_itSubStrBegin,  	m_itSubStrEnd 	);

    for ( StringFindConstIteratorT It= make_find_iterator( itRangeSearch, first_finder(sPattern, is_iequal())); It!=StringFindConstIteratorT(); ++It) {
        itRangeResult = *It;
        if ( --iCount == 0 ) break;
    }
    bool bFound = ( iCount == 0 ) && itRangeResult ;			// itRange is convertible to bool. True if a match was found
    if ( bFound ) {
        // Assign 'end' in case we found a match
        if ( setEndToPos == MATCH_FIRST )	m_itSubStrEnd = itRangeResult.begin();
        else								m_itSubStrEnd = itRangeResult.end();
        setValueBeginEnd();										// Assign result to current value
    }
    return bFound;		// itRange is convertible to bool. True if a match was found
}


/** */
bool StringSearch::findRegexBeginNext ( 
        int iCount, 						///< [in]
        const std::string& 	sRegex, 		///< [in]
        EMatchPos 			setBeginToPos	///< [in] Update 'Begin' marker to first or last position in match.
        )
{
    if ( iCount < 1	)	return false;
    boost::regex 										expression (sRegex);
    boost::match_results<std::string::const_iterator> 	what;
    boost::match_flag_type 								flags = boost::match_default;
    while( regex_search( m_itSubStrBegin, m_itSubStrEnd, what, expression, flags) )
    {
        // update search position:
        m_itSubStrBegin = what[0].second;
        if ( --iCount == 0 ) break;
        // update flags:
        flags |= boost::match_prev_avail;
        flags |= boost::match_not_bob;
    }
    //	bool bFound = ( iCount == 0 ) && ( m_itSubStrBegin < m_itSubStrEnd ) ;
    bool bFound = ( iCount == 0 ) && ( m_itSubStrBegin <= m_itSubStrEnd ) ;
    if ( bFound ) {
        // Assign 'begin' in case we found a match
        if ( setBeginToPos == MATCH_FIRST ) m_itSubStrBegin = what[0].first;
        else								m_itSubStrBegin = what[0].second;
        setValueBeginEnd();										// Assign result to current value
    }
    return bFound;
}


/** */
bool StringSearch::findRegexEndNext ( 
        int iCount, 						///< [in]
        const std::string& 	sRegex,	 		///< [in]
        EMatchPos  			setEndToPos		///< [in] Update 'End' marker to first or last position in match.
        )
{
    if ( iCount < 1	)	return false;
    boost::regex 										expression (sRegex);
    boost::match_results<std::string::const_iterator> 	what;
    boost::match_flag_type 								flags = boost::match_default;
    std::string::const_iterator 						itEnd = m_sSearchIn.end();

    m_itSubStrEnd = m_itSubStrBegin;
    while( regex_search( m_itSubStrEnd, itEnd, what, expression, flags) )
    {
        // update search position:
        m_itSubStrEnd = what[0].second;
        if ( --iCount == 0 ) break;
        // update flags:
        flags |= boost::match_prev_avail;
        flags |= boost::match_not_bob;
    }
    //	bool bFound = ( iCount == 0 ) && ( m_itSubStrBegin < m_itSubStrEnd ) ;
    bool bFound = ( iCount == 0 ) && ( m_itSubStrBegin <= m_itSubStrEnd ) ;
    if ( bFound ) {
        // Assign 'end' in case we found a match
        if ( setEndToPos == MATCH_FIRST ) 	m_itSubStrEnd = what[0].first;
        else								m_itSubStrEnd = what[0].second;
        setValueBeginEnd();										// Assign result to current value
    }
    return bFound;
}


// --------------- End New --------------



// --- Marker Move Functions ---
/** */
bool StringSearch::moveBegin( 
        int iNumChars 		///< [in]
        )
{
    if ( (m_itSubStrBegin + iNumChars) < m_sSearchIn.end() ) {
        m_itSubStrBegin += iNumChars;
        setValueBeginEnd();										// Assign result to current value
        return true;
    }
    return false;
}

/** */
bool StringSearch::moveEnd( 
        int iNumChars 		///< [in]
        )
{
    if ( (m_itSubStrEnd + iNumChars) <= m_sSearchIn.end() ) {
        m_itSubStrEnd += iNumChars;
        setValueBeginEnd();										// Assign result to current value
        return true;
    }
    return false;
}


// ------------------------------------------------------------------
// --- Assign to current value string (m_sCurrentValue) Functions ---
// ------------------------------------------------------------------

/** Assign to current value string the string between the begin and end markers using a regular expression.
We use a regular expression to search through the substring current between the begin and end markers
using a regular expression to retrieve the value that is then assigned as curent value string.
\todo Fix: getValueBeginEndRegex */
std::string 
StringSearch::setValueBeginEndRegex( 
        std::string const& sRegex
        )
{
    using namespace boost;
    m_sCurrentValue = "";
    regex expr( sRegex );
    smatch what;

    if ( regex_search( m_itSubStrBegin, m_itSubStrEnd, what, expr ) )  {
        m_sCurrentValue = what[1];
    }
    return m_sCurrentValue;
}



/** Set current value string to specified value. */
void StringSearch::setValue( 
        std::string const& sValue 	///< [in] String value to assign to current value string
        )
{
    m_sSearchIn		= sValue;
    resetMarkersBeginEnd();	// Also assigns current value from m_sSearchIn
}


std::string StringSearch::getParseMatch( 
        int iMatchNumber
        ) const
{
    if ( static_cast<unsigned int>(iMatchNumber) < m_parseMatchResults.size() ) 	return m_parseMatchResults[iMatchNumber];
    else 																			return "";
}

std::string StringSearch::getParseRest() const 
{
    return m_sParseRest ;
}

int StringSearch::getParseMatchCount() const 
{
    return m_parseMatchResults.size() ;
}


/** Assign to current value using a regular expression to search through the whole page. */
std::string StringSearch::setValueRegex( 
        std::string const& sRegex			///< [in] Regular expression to use
        )
{
    using namespace boost;
    m_sCurrentValue = "";
    regex expr( sRegex );
    smatch what;
    if ( regex_search( m_sSearchIn, what, expr) )	m_sCurrentValue = what[1];
    return m_sCurrentValue;
}


// --------------------------------------
// --- Modify Current Value Functions ---
// --------------------------------------

void StringSearch::modifyValue	( 
        boost::shared_ptr<StrModifierAbstraction> pManip,
        const std::string& sParam1,
        const std::string& sParam2,
        const std::string& sParam3,
        const std::string& /*sParam4*/
        )
{
    m_sCurrentValue = pManip->callMeStr ( m_pConfig, m_sCurrentValue, sParam1, sParam2, sParam3 );
}


void StringSearch::modifyValue( 
        const StringCopyManipFun1T& fnManip		///< [in]
        )
{
    m_sCurrentValue = fnManip( m_pConfig, m_sCurrentValue ) ;
}

void StringSearch::modifyValue( 
        const StringCopyManipFun2T& fnManip,	///< [in]
        const std::string& sManipParam			///< [in]
        )
{
    m_sCurrentValue = fnManip( m_pConfig, m_sCurrentValue, sManipParam ) ;
}

void StringSearch::modifyValue( 
        const StringCopyManipFun3T& fnManip,	///< [in]
        const std::string& sManipParam1,		///< [in]
        const std::string& sManipParam2			///< [in]
        )
{
    m_sCurrentValue = fnManip( m_pConfig, m_sCurrentValue, sManipParam1, sManipParam2 ) ;
}

void StringSearch::modifyValue( 
        const StringCopyManipFun4T& fnManip,	///< [in]
        const std::string& sManipParam1,		///< [in]
        const std::string& sManipParam2,		///< [in]
        int                iIntParam			///< [in]
        )
{
    m_sCurrentValue = fnManip( m_pConfig, m_sCurrentValue, sManipParam1, sManipParam2, iIntParam ) ;
}



// ------------------------
// --- Output Functions ---
// ------------------------
void StringSearch::beginMining (const std::string& outputName)
{
    const bool doPushWritersContext = true;
    dwBeginMining(outputName);
    pushContext("ROOT", doPushWritersContext);
}

void StringSearch::endMining ()
{
    while ( !m_ContextStack.empty() )
        popContext();
    dwEndMining();
}

void StringSearch::pushContext (
        const std::string& sContext,
        bool bDoPushWritersContext
        )
{
    string actualContext = sContext;
    m_pCurContextVals = StrStrMapPtrT(new StrStrMapT);
    m_outputLists.clear();

    std::string prevContext = "";
    if (!m_ContextStack.empty()) {
        prevContext = m_ContextStack.top().m_context;
    }
    const bool prevContextIsList = fieldIsList(prevContext);
//    if (prevContextIsList) {
//        actualContext = "";
//    }

    incContextCount();
    const size_t parentContextCount = contextCount(); // Order here is important! Mainly to ensure that function contextCount() returns correct number
    m_ContextStack.push( Context(actualContext) );


    if (bDoPushWritersContext) {
        dwPushContext( actualContext, prevContext, parentContextCount );   // When pushing ROOT node in continue mode we don't want to call push context on the writers
        if (prevContextIsList) { // I.e - If this context is a list item, we also write the original context out as a normal field
            dwOutputValueDirect(sContext, prevContext);
        }
    }
}

void StringSearch::popContext()
{
    std::string contexToPop ( "ERROR_CONTEXT_STACK_EMPTY_popContext()" );
    if ( !m_ContextStack.empty()	) 	{

        // Out put lists first
        for (auto pair: m_outputLists) {
            string listName = pair.first;
            auto list = pair.second;
            (*m_pCurContextVals)[listName] = cpaf::join(list, ",");
            if (m_bDoWriteOutputToFile && !list.empty()) {
                incValuesCount();
                for( boost::shared_ptr<DataWriterIF> pDW : m_dataWriters ) {
                    pDW->outputList(listName, list, indentLevel(), valuesCount());
                }
            }
            if (listName != "")
                m_outputLists[listName].clear();
        }

        contexToPop = m_ContextStack.top().m_context;
        m_ContextStack.pop();   // Order here is important! Mainly to ensure that function contextCount() returns correct number
        const size_t parentContextCount = contextCount();
        dwPopContext( contexToPop, parentContextCount );
    }
}



/** Write specific value to database file. */
void StringSearch::outputValueDirectUnit(
        const std::string& sFieldName, 	///< [in]
        const std::string& sValue		///< [in]

        )
{
    if (fieldIsList(sFieldName)) {
        m_outputLists[sFieldName].push_back(sValue);
    }
    else {
        dwOutputValueDirect( sFieldName, sValue );
    }
}



void StringSearch::configOutputEncloseCDATA( bool bDoEncloseInCDATA )
{
    dwConfigOutputEncloseCDATA( bDoEncloseInCDATA );
}	

void StringSearch::configOutputWriteToFile ( bool bDoWriteOutputToFile )
{
    m_bDoWriteOutputToFile = bDoWriteOutputToFile;
    for( boost::shared_ptr<DataWriterIF> pDW : m_dataWriters ) {
        pDW->doWriteOutputToFileSet(bDoWriteOutputToFile);
    }

}


std::string StringSearch::outputValueGet(
        const std::string& sFieldName, 	///< [in] Name (output name) of value to retrieve
        const std::string sContextName  ///< [in] Optional saved context name to get the value from
        )
{
    StrStrMapPtrT pVals = m_pCurContextVals;
    if ( !sContextName.empty() ) {
        auto it = m_contextOutputVals.find(sContextName);
        if ( it != m_contextOutputVals.end() )
            pVals = it->second;
    }

    if ( pVals ) {
        auto itVals = pVals->find( sFieldName );
        if ( itVals != pVals->end() )
            return itVals->second;
    }
    else {
        printf("ML: StringSearch::outputValueGet pVals == NULL (pointer)\n");
    }
    return "";
}


void StringSearch::contextOutputSaveAs ( const std::string& sContextName )
{
    if ( m_pCurContextVals ) {
        m_contextOutputVals[sContextName] = m_pCurContextVals;
    }
    else {
        printf("ML: StringSearch::contextOutputSaveAs pVals == NULL (pointer)\n");
    }
}

void StringSearch::contextFallbackOutputLoad( const std::string& sContextName )
{
    if ( !sContextName.empty() ) {
        ContextOutputValsT::const_iterator it = m_contextOutputVals.find(sContextName);
        if ( it != m_contextOutputVals.end() ) {
            StrStrMapPtrT pFallbackVals(it->second);
            if ( pFallbackVals ) {
                m_curContextFallbackVals = *(it->second);
            }
            else {
                printf("ML: StringSearch::contextFallbackOutputLoad pFallbackVals == NULL (pointer)\n");
            }
        }
        else m_curContextFallbackVals.clear();
    }
    else m_curContextFallbackVals.clear();
}

void StringSearch::contextFallbackOutputClear()
{
    m_curContextFallbackVals.clear();
}

std::string StringSearch::contextFallbackValueGet( const std::string& sFieldName ) const
{
    return cpaf::map_find(m_curContextFallbackVals, std::string(""), sFieldName);
}

void StringSearch::contextFallbackValueSet (
        const std::string& sFieldName
        , const std::string& sValue )
{
    m_curContextFallbackVals[sFieldName] = sValue;
}

bool StringSearch::contextFallbackValueExists( const std::string& sFieldName ) const
{
    return m_curContextFallbackVals.find(sFieldName) != m_curContextFallbackVals.end();
}

void StringSearch::contextFallbackValueDelete( const std::string& sFieldName )
{
    m_curContextFallbackVals.erase(sFieldName);
}

bool StringSearch::contextSavedOutputExists( const std::string& sContextName ) const
{
    return m_contextOutputVals.find(sContextName) != m_contextOutputVals.end();
}

void StringSearch::contextSavedOutputDelete( const std::string& sContextName )
{
    m_contextOutputVals.erase(sContextName);
}

bool StringSearch::fieldIsList(const std::string &fieldName) const
{
    return boost::algorithm::ends_with(fieldName, m_autoListSuffix);
}

// -------------------------
// --- Private Functions ---
// -------------------------

/** Call beginMining() on all data writers. */
void StringSearch::dwBeginMining(const std::string outputName )
{
    if ( outputName != "" )    dwOutputNameSet(outputName);
    for( boost::shared_ptr<DataWriterIF> pDW : m_dataWriters ) {
        pDW->stringSearchSet(this);
        pDW->beginMining();
    }
}


/** Call baseOutputNameSet() on all data writers. */
void StringSearch::dwOutputNameSet(const std::string outputName )
{
    for( boost::shared_ptr<DataWriterIF> pDW : m_dataWriters ) {
        pDW->baseOutputNameSet( outputName );
    }
}

/** Call doContinueModeSet() on all data writers. */
void StringSearch::dwDoContinueModeSet ( bool bDoContinue, int iContinueCounter )
{
    for( boost::shared_ptr<DataWriterIF> pDW : m_dataWriters ) {
        pDW->doContinueModeSet( bDoContinue, iContinueCounter );
    }
}


/** Call restart() on all data writers. */
void StringSearch::dwRestart( const std::string outputName )
{
    for( boost::shared_ptr<DataWriterIF> pDW : m_dataWriters ) {
        pDW->restart( outputName );
    }
}

void StringSearch::dwConfigOutputEncloseCDATA( bool bDoEncloseInCDATA )
{
    for( boost::shared_ptr<DataWriterIF> pDW : m_dataWriters ) {
        pDW->configOutputEncloseCDATA( bDoEncloseInCDATA );
    }
}


void StringSearch::dwEndMining ()
{
    for( boost::shared_ptr<DataWriterIF> pDW : m_dataWriters ) {
        pDW->endMining();
    }
}

void StringSearch::dwPushContext (
        const std::string& sContext,
        const string& prevContext,
        size_t ctxCount
        )
{
    if ( !m_bDoWriteOutputToFile )  return;

    for( boost::shared_ptr<DataWriterIF> pDW : m_dataWriters ) {
        pDW->pushContext( sContext, prevContext, indentLevel()-1, ctxCount );
    }
}

void StringSearch::dwPopContext (const std::string& sContext, size_t parentContextCount)
{
    for( boost::shared_ptr<DataWriterIF> pDW : m_dataWriters )
        pDW->popContext( sContext, indentLevel(), parentContextCount ); // +1 because we have already popped the context stack
}

void StringSearch::dwOutputValueDirect (
        const std::string& sFieldName
        , const std::string& sValue   )
{
    (*m_pCurContextVals)[sFieldName] = sValue;
    if ( !m_bDoWriteOutputToFile )  return;
    incValuesCount();

    for( boost::shared_ptr<DataWriterIF> pDW : m_dataWriters ) {
        pDW->outputValueDirect( sFieldName, sValue, indentLevel(), valuesCount());
    }
}

size_t StringSearch::valuesCount() const
{
    if (m_ContextStack.empty())
        return 0;
    return m_ContextStack.top().m_valuesCount;
}

void StringSearch::incValuesCount()
{
    if (m_ContextStack.empty())
        return;
    m_ContextStack.top().m_valuesCount++;
}

size_t StringSearch::contextCount() const
{
    if (m_ContextStack.empty())
        return 0;
    return m_ContextStack.top().m_contextCount;
}

void StringSearch::incContextCount()
{
    if (m_ContextStack.empty())
        return;
    m_ContextStack.top().m_contextCount++;
}

size_t StringSearch::indentLevel() const
{
    return m_ContextStack.size();
}


} // END namespace crawl
