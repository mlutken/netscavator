//#include <hacks/wx_h_include_hack.h>
//#include <hacks/wx_h_php_undef_hack.h>

#include <iostream>
#include <locale>
#include <boost/format.hpp>
#include <cpaf_libs/time/cpaf_time.h>
#include <compression/cpaf_compression_functions.h>
#include <net/cpaf_http_convenience.h>
#include <parser/DomSeq.h>
#include <parser/DomActionAbstraction.h>
#include <containers/DomSearchMgr.h>
#include <containers/DomActionMgr.h>
#include <containers/ModifierMgr.h>
#include <navigator/DomNavigator.h>
#include <utils/string_algorithms.h>
#include <utils/string_compare_functions.h>
#include <ScriptMinerIF.h>
#include "scriptcrawl_private.h"
#include "scriptcrawl.h"


namespace fs = boost::filesystem;
using crawl::string_compare::G_StringCompareLookUp;


#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>

void *testPhpArrayGet()
{

    return 0;
}

std::vector<int> testArrayGet()
{
    std::vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    return v;
}

std::vector<std::string> testArrayStrGet()
{
    std::vector<std::string> v;
    v.push_back("11");
    v.push_back("22");
    v.push_back("33");
    return v;
}

double average(std::vector<int> v) {
    return std::accumulate(v.begin(),v.end(),0.0)/v.size();
}

std::vector<double> half(const std::vector<double>& v) {
    std::vector<double> w(v);
    for (unsigned int i=0; i<w.size(); i++)
        w[i] /= 2.0;
    return w;
}

void halve_in_place(std::vector<double>& v) {
    std::transform(v.begin(),v.end(),v.begin(),
                   std::bind2nd(std::divides<double>(),2.0));
}

void currentMinerSetPointer  ( const std::string& sMinerPointer )
{
    long iPtr = atol(sMinerPointer.c_str());
    void* pM = (void*)(iPtr);
    currentMinerSetRaw(pM);
}

void currentMinerSetRaw  ( void* pMiner )
{
    crawl::ScriptMinerIF* pM1 = static_cast<crawl::ScriptMinerIF*>(pMiner);
    boost::shared_ptr<crawl::ScriptMinerIF> pM2 = pM1->shared_from_this();
    currentMinerSet(pM2);
}

void initMining()
{
    printf("initMining\n") ;
    using namespace std;

}

void scriptHtmlEntitiesReplaceAdd(const std::string& lookFor, const std::string& replaceWith)
{
    curMiner()->scriptHtmlEntitiesReplaceAdd(lookFor, replaceWith);
}

void scriptHtmlEntitiesReplaceClear()
{
    curMiner()->scriptHtmlEntitiesReplaceClear();
}

void addMiner( std::string sMinerName )
{
    currentMinerNameSet(sMinerName);
    //G_ScriptGlobals::Instance().m_miners[sMinerName] = boost::shared_ptr<ScriptMiner>();
}

//void runMiners( )
//{
//	char*  szArgv[2] = { "", "" };
//	int iArgc = 1;
//	wxEntry( iArgc, &szArgv[0] );
//}

// -------------------------------
// --- Info/settings functions ---
// -------------------------------

std::string outputName()
{
    return curMiner()->outputName();
}

// ----------------------
// --- Misc functions ---
// ----------------------
std::string pageSource()
{
    return curMiner()->pageSource();
}

std::string
currentMiner()
{
    return currentMinerName();
//    return curMiner()->currentMiner();
}

std::string
currentDataFile()
{
    return curMiner()->currentDataFile();
}

void triggerPageLoaded()
{
    curMiner()->triggerPageLoaded();
}

void triggerPageLoadedWait(int timeoutInMs)
{
    curMiner()->triggerPageLoadedWait(timeoutInMs);
}

void waitSleep(int timeInMs)
{
    curMiner()->waitSleep(timeInMs);
}

void waitForDomReady(int timeoutInMs)
{
    curMiner()->waitForDomReady(timeoutInMs);
}

void waitForJavascriptDone()
{
    curMiner()->waitForJavascriptDone();
}

void clearCookies()
{
    curMiner()->clearCookies();
}

int configDelayPageLoadedTime()
{
    return curMiner()->configDelayPageLoadedTime();
}

void configDelayPageLoadedTimeSet(int milliseconds)
{
    curMiner()->configDelayPageLoadedTimeSet(milliseconds);
}

int networkActivityCounter()
{
    return curMiner()->networkActivityCounter();
}

/*
-------------------------
--- Browser functions ---
------------------------- */
void browserScroll(int x, int y)
{
    curMiner()->browserScroll(x, y);
}

int browserScrollPosXGet()
{
    return curMiner()->browserScrollPosXGet();
}

int browserScrollPosYGet()
{
    return curMiner()->browserScrollPosYGet();
}

void browserHide ()
{
    curMiner()->browserHide();
}

void browserShow ()
{
    curMiner()->browserShow();
}

void browserSetSize	(int x, int y)
{
    curMiner()->browserSetSize(x,y);
}

int browserGetSizeX	()
{
    return curMiner()->browserGetSizeX();
}

int browserGetSizeY	()
{
    return curMiner()->browserGetSizeY();
}

bool
browserGoBack ()
{
    return curMiner()->browserGoBack();
}

void browserKeyEvent(int eventType, int key, int modifiers)
{
    curMiner()->browserKeyEvent(eventType, key, modifiers);
}

void browserMouseEvent(int eventType, float xpos, float ypos, int button, int buttons, int modifiers)
{
    curMiner()->browserMouseEvent(eventType, xpos, ypos, button, buttons, modifiers);
}

void browserFocusActivate()
{
    curMiner()->browserFocusActivate();
}

void browserFocusDeactivate()
{
    curMiner()->browserFocusDeactivate();
}

/*------------------------------------------
--- String operators/compare functions ---
------------------------------------------*/

bool valuesCompare (
      const std::string& sInput
    , const std::string& sTest
    , const std::string& sCompareFun
    )
{
    return curMiner()->valueCompare(sInput, sTest, sCompareFun);
}


/*
-------------------------
--- Sitemap functions ---
-------------------------*/

std::vector<std::string> allSitemaps()
{
    std::vector<std::string> v{"one", "two", "three"};
//    v.push_back("11");
//    v.push_back("22");
//    v.push_back("33");
    return v;
}

void siteMapUrlsSet(const std::vector<std::string>& siteMapUrls)
{
    curMiner()->siteMapUrlsSet(siteMapUrls);
}

void siteMapUrlAppend(const std::string& siteMapUrl)
{
    curMiner()->siteMapUrlAppend(siteMapUrl);
}

std::vector<std::string> siteMapLocationUrls()
{
    return curMiner()->siteMapLocationUrls();
}

std::vector<std::string> siteMapUrls()
{
    return curMiner()->siteMapUrls();
}

void siteMapLocationsInclude(const std::string& urlPattern, const std::string& compareFun)
{
    curMiner()->siteMapLocationsInclude(urlPattern, compareFun);
}

void siteMapLocationsExclude(const std::string& urlPattern, const std::string& compareFun)
{
    curMiner()->siteMapLocationsExclude(urlPattern, compareFun);
}

/*--------------------------------
--- Navigation (nav) functions ---
----------------------------------*/
void navActiveNavigatorSet ( const std::string& sNavigatorName  )
{
     curMiner()->navActiveNavigatorSet(sNavigatorName);
}


std::string navActiveNavigatorGet ()
{
    return  curMiner()->navActiveNavigatorGet();
}

void navJavascriptExecuteCreate (
    const std::string& sNavActionName
    )
{
    curMiner()->navJavascriptExecuteCreate ( sNavActionName );
}


void navUrlLoadCreate (
      const std::string& sNavActionName
    , const std::string& sBaseUrl
    )
{
     curMiner()->navUrlLoadCreate( sNavActionName, sBaseUrl );
}

void navInputOptionsCreate (
      const std::string& sNavActionName
    )
{
     curMiner()->navInputOptionsCreate(sNavActionName );
}


void navDropDownSelectCreate (
    const std::string& sNavActionName
    )
{
     curMiner()->navDropDownSelectCreate(sNavActionName);
}


void navDomPosClickCreate (
      const std::string& sNavActionName
    , const std::string& sFindNextDomPosSequence
    )
{
     curMiner()->navDomPosClickCreate(sNavActionName, sFindNextDomPosSequence );
}

void navDomClickNextCreate(const std::string& sNavActionName, const std::string& sFindNextDomPosSequence)
{
    curMiner()->navDomClickNextCreate(sNavActionName, sFindNextDomPosSequence );
}

void navAutoInputCreate (
      const std::string& sNavActionName
    , const std::string& sCharsList
    , int iMinLength
    , int iMaxLength
    )
{
    curMiner()->navAutoInputCreate(sNavActionName, sCharsList, iMinLength, iMaxLength );
}



void navAttributeNamesCreate (
      const std::string& sAttrNames
    , const std::string& sDelimiter
    )
{
    curMiner()->navAttributeNamesCreate(sAttrNames, sDelimiter );
}

void navCurrentStateIndicesSet ( const std::string& sState )
{
    curMiner()->navCurrentStateIndicesSet ( sState );
}

std::string navCurrentStateIndicesGet ()
{
    return curMiner()->navCurrentStateIndicesGet ();
}

void navCurrentStateSet (
      const std::string& sState
    , const std::string& sDelimiter
    )
{
    curMiner()->navCurrentStateSet( sState, sDelimiter );
}

void navCurrentStateSet (
    const std::string& sState
    )
{
    curMiner()->navCurrentStateSet( sState );
}

void navBeginStateSet (
      const std::string& sState
    , const std::string& sDelimiter
    )
{
    curMiner()->navCurrentStateSet( sState, sDelimiter );
}

void navBeginStateSet (
    const std::string& sState
    )
{
    curMiner()->navCurrentStateSet( sState );
}

void navEndStateSet   (
      const std::string& sState
    , const std::string& sDelimiter
    )
{
    curMiner()->navEndStateSet( sState, sDelimiter );
}

void navEndStateSet   (
    const std::string& sState
    )
{
    curMiner()->navEndStateSet( sState );
}

void navOptionResourceAdd    (
      const std::string& sResourcePath
    , const std::string& sScriptFilterFunction
    ,  bool bForceDownload
    )

{
     curMiner()->navOptionResourceAdd( sResourcePath, sScriptFilterFunction, bForceDownload );
}


void navOptionAdd(
      int iCount
    , const std::string& sValue
    , const std::string& sSearchFor
    )
{
    curMiner()->navOptionAdd(iCount, sValue, sSearchFor);
}


void navOptionAdd (
      int iCount
    , const std::string& sValue
    )
{
    curMiner()->navOptionAdd(iCount,sValue);
}


void navOptionAdd (
      const std::string& sValue
    , const std::string& sSearchFor
    )
{
    curMiner()->navOptionAdd(sValue, sSearchFor);
}


void navOptionAdd (
    const std::string& sValue
    )
{
    curMiner()->navOptionAdd(sValue);
}


void navOptionAdd ( int iCount )
{
    curMiner()->navOptionAdd(iCount);
}


void navOptionAdd(
      int iCount
    , const std::string& sValue
    , const std::string& sSearchFor
    , int attrStart
    , const std::string& sAttributes
    , const std::string& sDelimiter
    )
{
    curMiner()->navOptionAdd(iCount, sValue, sSearchFor, attrStart, sAttributes, sDelimiter);
}


void navOptionAdd (
      int iCount
    , const std::string& sValue
    , int attrStart
    , const std::string& sAttributes
    , const std::string& sDelimiter
    )
{
    curMiner()->navOptionAdd(iCount,sValue, attrStart, sAttributes, sDelimiter);
}


void navOptionAdd (
      const std::string& sValue
    , const std::string& sSearchFor
    , int attrStart
    , const std::string& sAttributes
    , const std::string& sDelimiter
    )
{
    curMiner()->navOptionAdd(sValue, sSearchFor, attrStart, sAttributes, sDelimiter);
}


void navOptionAdd (
    const std::string& sValue
  , int attrStart
  , const std::string& sAttributes
  , const std::string& sDelimiter
    )
{
    curMiner()->navOptionAdd(sValue, attrStart, sAttributes, sDelimiter);
}


void navOptionAdd (
    int iCount
  , int attrStart
  , const std::string& sAttributes
  , const std::string& sDelimiter
        )
{
    curMiner()->navOptionAdd(iCount, attrStart, sAttributes, sDelimiter);
}

std::string navDomTextValueGet(
    const std::string& sNavActionName
  )
{
    return curMiner()->navDomTextValueGet(sNavActionName);
}

std::string navDomValueGet(
    const std::string& sNavActionName
  )
{
    return curMiner()->navDomValueGet(sNavActionName);
}

std::string navValueGet(
    const std::string& sNavActionName
  )
{
    return curMiner()->navValueGet(sNavActionName);
}

std::string navSearchForGet(
    const std::string& sNavActionName
    )
{
    return curMiner()->navSearchForGet(sNavActionName);
}

int navCountGet(
    const std::string& sNavActionName
    )
{
    return curMiner()->navCountGet(sNavActionName);
}

int navOptionIndexGet(
    const std::string& sNavActionName
    )
{
    return curMiner()->navOptionIndexGet(sNavActionName);
}

int navStateIndexGet(
    )
{
    return curMiner()->navStateIndexGet();
}

int navNumStatesGet ()
{
    return curMiner()->navNumStatesGet();
}

int navLastStateIndexGet ()
{
    return curMiner()->navLastStateIndexGet();
}


std::string navAttributeGet (
      const std::string& sNavActionName
    , const std::string& sAttrName
    )
{
    return curMiner()->navAttributeGet(sNavActionName, sAttrName);
}

std::string navAttributeGet (
    const std::string& sAttrName
    )
{
    return curMiner()->navAttributeGet(sAttrName);
}


bool navNextState()
{
    return curMiner()->navNextState();
}

bool navDoAction ( const std::string& sNavActionName )
{
    return curMiner()->navDoAction( sNavActionName );
}

bool navDoActionClickAll ( const std::string& sNavActionName )
{
    return curMiner()->navDoActionClickAll( sNavActionName );
}

std::string navStateString ()
{
    return curMiner()->navStateString();
}

void navStart ()
{
    curMiner()->navStart();
}

void navReset ()
{
    curMiner()->navReset();
}

bool navNavigationDone ()
{
    return curMiner()->navNavigationDone();
}

void navAutoInputIncreaseLength ( bool bDoIncreaseLength )
{
    curMiner()->navAutoInputIncreaseLength( bDoIncreaseLength );
}


/*
----------------------------------------------
--- String modifier/manipulation functions ---
---------------------------------------------- */
/**
* \defgroup stringManipFunctions String modifiers
* @{

String modifier/manipulation functions

All these functions ending in _fn can be used as is in normal
PHP code WITH the _fn and WITHOUT the _fn in a modifierCreate.
For example:
\code
modifierCreate("classification_text__ItemPage__MOD", "trimBetween", "<L1>", "</L1>");
\endcode

*/
std::string trimDefault_fn 	( const std::string& sInput 	)
{
    return curMiner()->trimDefault_fn(sInput);
}

std::string raw_fn				( const std::string& sInput		)
{
    return curMiner()->raw_fn(sInput);
}

std::string toUpper_fn			( const std::string& sInput		)
{
    return curMiner()->toUpper_fn(sInput);
}

std::string toLower_fn			( const std::string& sInput		)
{
    return curMiner()->toLower_fn(sInput);
}

std::string trimEnds_fn			( const std::string& sInput		)
{
    return curMiner()->trimEnds_fn(sInput);
}

std::string trimLeft_fn			( const std::string& sInput		)
{
    return curMiner()->trimLeft_fn(sInput);
}

std::string trimRight_fn		( const std::string& sInput		)
{
    return curMiner()->trimRight_fn(sInput);
}

std::string trimYear_fn			( const std::string& sInput 	)
{
    return curMiner()->trimYear_fn(sInput);
}


std::string trimInteger_fn		( const std::string& sInput		)
{
    return curMiner()->trimInteger_fn(sInput);
}

std::string trimNumber_fn		( const std::string& sInput		)
{
    return curMiner()->trimNumber_fn(sInput);
}

std::string trimCharsEnds_fn	( const std::string& sInput, const std::string& sCharsToTrim )
{
    return curMiner()->trimCharsEnds_fn(sInput, sCharsToTrim);
}

std::string trimCharsLeft_fn	( const std::string& sInput, const std::string& sCharsToTrim )
{
    return curMiner()->trimCharsLeft_fn(sInput, sCharsToTrim);
}

std::string trimCharsRight_fn	( const std::string& sInput, const std::string& sCharsToTrim )
{
    return curMiner()->trimCharsRight_fn(sInput, sCharsToTrim);
}

std::string trimRegex_fn		( const std::string& sInput, const std::string& sRegex )
{
    return curMiner()->trimRegex_fn(sInput, sRegex);
}

std::string itrimRegex_fn		( const std::string& sInput, const std::string& sRegex )
{
    return curMiner()->itrimRegex_fn(sInput, sRegex);
}

std::string append_fn			( const std::string& sInput, const std::string& sString	)
{
    return curMiner()->append_fn(sInput, sString);
}

std::string prepend_fn			( const std::string& sInput, const std::string& sString	)
{
    return curMiner()->prepend_fn(sInput, sString);
}

std::string eraseFirst_fn		( const std::string& sInput, const std::string& sSearchFor	)
{
    return curMiner()->eraseFirst_fn(sInput, sSearchFor);
}

std::string ieraseFirst_fn		( const std::string& sInput, const std::string& sSearchFor	)
{
    return curMiner()->ieraseFirst_fn(sInput, sSearchFor);
}

std::string eraseLast_fn		( const std::string& sInput, const std::string& sSearchFor	)
{
    return curMiner()->eraseLast_fn(sInput, sSearchFor);
}

std::string ieraseLast_fn		( const std::string& sInput, const std::string& sSearchFor	)
{
    return curMiner()->ieraseLast_fn(sInput, sSearchFor);
}

std::string eraseAll_fn			( const std::string& sInput, const std::string& sSearchFor	)
{
    return curMiner()->eraseAll_fn(sInput, sSearchFor);
}

std::string ieraseAll_fn		( const std::string& sInput, const std::string& sSearchFor	)
{
    return curMiner()->ieraseAll_fn(sInput, sSearchFor);
}

std::string eraseRegex_fn		( const std::string& sInput, const std::string& sSearchFor	)
{
    return curMiner()->eraseRegex_fn(sInput, sSearchFor);
}

std::string eraseAllRegex_fn	( const std::string& sInput, const std::string& sSearchFor	)
{
    return curMiner()->eraseAllRegex_fn(sInput, sSearchFor);
}


/** Match slice part of string between two delimiters

Match the begin and end delimiters given and return the middle slice of the
input string between the markers.

### Examples of use

\code
\$str = "This is a string when we want to cut out a piece between some markers";
echo trimBetween($str, "we want", "some"); // PRINTS: ' to cut out a piece between '
echo trimBetween($str, "", "some"); // PRINTS: 'This is a string when we want to cut out a piece between '
echo trimBetween($str, "we want", ""); // PRINTS: ' to cut out a piece between some markers'
\endcode

Here is an example of how to use this as a modifier:
\code
modifierCreate("classification_text__ItemPage__MOD", "trimBetween", "<L1>", "</L1>");
\endcode

\return The value between the begin and end markers. The markers are NOT included. If both are amty or none of the
        delimiters are found the original string is returned.
*/
std::string trimBetween_fn  (
          const std::string& sInput ///< [in] Input string to search in
        , const std::string& sBegin ///< [in] Begin delimiter. If left empty we return from the beginning of the input string
        , const std::string& sEnd   ///< [in] End delimiter. If left empty we return to the end f the input string
        )
{
    return curMiner()->trimBetween_fn(sInput, sBegin, sEnd );
}

std::string trimBetweenCount_fn  ( const std::string& sInput, const std::string& sBegin, const std::string& sEnd, const std::string& sCount )
{
    return curMiner()->trimBetweenCount_fn(sInput, sBegin, sEnd, sCount );
}

std::string trimBetweenCount_fn  ( const std::string& sInput, const std::string& sBegin, const std::string& sEnd, int iCount )
{
    return curMiner()->trimBetweenCount_fn(sInput, sBegin, sEnd, iCount );
}

std::string trimIntegerCustom_fn( const std::string& sInput, const std::string& iBase, const std::string& sThousandsSep)
{
    return curMiner()->trimIntegerCustom_fn(sInput, iBase, sThousandsSep);
}

std::string trimNumberCustom_fn	( const std::string& sInput, const std::string& sDecimalPoint, 	const std::string& sThousandsSep)
{
    return curMiner()->trimNumberCustom_fn(sInput, sDecimalPoint, sThousandsSep);
}

std::string replaceFirst_fn		( const std::string& sInput, const std::string& sSearchFor,		const std::string& sReplaceWith	)
{
    return curMiner()->replaceFirst_fn(sInput, sSearchFor, sReplaceWith);
}

std::string ireplaceFirst_fn	( const std::string& sInput, const std::string& sSearchFor,		const std::string& sReplaceWith	)
{
    return curMiner()->ireplaceFirst_fn(sInput, sSearchFor, sReplaceWith);
}

std::string replaceLast_fn		( const std::string& sInput, const std::string& sSearchFor,		const std::string& sReplaceWith	)
{
    return curMiner()->replaceLast_fn(sInput, sSearchFor, sReplaceWith);
}

std::string ireplaceLast_fn		( const std::string& sInput, const std::string& sSearchFor,		const std::string& sReplaceWith	)
{
    return curMiner()->ireplaceLast_fn(sInput, sSearchFor, sReplaceWith);
}

std::string replaceAll_fn		( const std::string& sInput, const std::string& sSearchFor,		const std::string& sReplaceWith	)
{
    return curMiner()->replaceAll_fn(sInput, sSearchFor, sReplaceWith);
}

std::string ireplaceAll_fn		( const std::string& sInput, const std::string& sSearchFor,		const std::string& sReplaceWith	)
{
    return curMiner()->ireplaceAll_fn(sInput, sSearchFor, sReplaceWith);
}

std::string replaceRegex_fn		( const std::string& sInput, const std::string& sSearchFor,		const std::string& sReplaceWith	)
{
    return curMiner()->replaceRegex_fn(sInput, sSearchFor, sReplaceWith);
}

std::string replaceAllRegex_fn	( const std::string& sInput, const std::string& sSearchFor,		const std::string& sReplaceWith	)
{
    return curMiner()->replaceAllRegex_fn(sInput, sSearchFor, sReplaceWith);
}

std::string eraseNth_fn	( const std::string& sInput, const std::string& sSearchFor,	int iNth 	)
{
    return curMiner()->eraseNth_fn(sInput, sSearchFor, iNth);
}

std::string ieraseNth_fn		( const std::string& sInput, const std::string& sSearchFor,	int iNth 	)
{
    return curMiner()->ieraseNth_fn(sInput, sSearchFor, iNth);
}


std::string replaceNth_fn	( const std::string& sInput, const std::string& sSearchFor,	const std::string& sReplaceWith, int iNth	)
{
    return curMiner()->replaceNth_fn(sInput, sSearchFor, sReplaceWith, iNth);
}

std::string ireplaceNth_fn		( const std::string& sInput, const std::string& sSearchFor,	const std::string& sReplaceWith, int iNth	)
{
    return curMiner()->ireplaceNth_fn(sInput, sSearchFor, sReplaceWith, iNth);
}

std::string eraseNth_fn	( const std::string& sInput, const std::string& sSearchFor,     const std::string& sNth 	)
{
    return curMiner()->eraseNth_fn(sInput, sSearchFor, sNth);
}

std::string ieraseNth_fn( const std::string& sInput, const std::string& sSearchFor,     const std::string& sNth 	)
{
    return curMiner()->ieraseNth_fn(sInput, sSearchFor, sNth);
}

std::string replaceNth_fn	( const std::string& sInput, const std::string& sSearchFor,	const std::string& sReplaceWith ,const std::string& sNth	)
{
    return curMiner()->replaceNth_fn(sInput, sSearchFor, sReplaceWith, sNth);
}

std::string ireplaceNth_fn	( const std::string& sInput, const std::string& sSearchFor,	const std::string& sReplaceWith, const std::string& sNth	)
{
    return curMiner()->ireplaceNth_fn(sInput, sSearchFor, sReplaceWith, sNth);
}

/**@}*/


/*
---------------------
--- URL functions ---
--------------------- */
std::string
urlSite()
{
    return curMiner()->urlSite();
}

std::string
urlCurrent()
{
    return curMiner()->urlCurrent();
}

/** Load new URL directly into browser.*/
bool
urlLoad (
    const std::string sURL	)	///< [in] URL (as string) to load .
{
    return curMiner()->urlLoad(sURL);
}


/** Load new URL directly into browser, but wait in php script untill page
has loaded and continue executing php from where load was initiated.*/
bool
urlLoadWait (const std::string sURL	, int timeoutInMs)	///< [in] URL (as string) to load .
{
    return curMiner()->urlLoadWait(sURL, timeoutInMs);
}

/*
---------------------
--- DOM functions ---
--------------------- */
/** Rebuild linear DOM. You might need this if crawler script triggers javascript code that causes
 * new elements to be created, that you need to search for and manipulate with.
For example the calendar widget on startour.dk's main page. */
void domRebuildWait ( int timeoutInMs )
{
    curMiner()->domRebuildWait(timeoutInMs);
}

/** Initiate new search of DOM. Current dom node is set to the first node on the page. */
void	domNewSearch()
{
    curMiner()->domNewSearch();
}

std::vector<int> domFindAll(const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps)
{
    return curMiner()->domFindAll(sSequence, sCompareFun, iPostMatchSteps);
}

std::vector<int> domFindAll(const std::string& sSequence, int iPostMatchSteps)
{
    return curMiner()->domFindAll(sSequence, iPostMatchSteps);
}

std::vector<int> domFindAll(const std::string& sSequence)
{
    return curMiner()->domFindAll(sSequence);
}


/** Initiate new search of DOM, continuing from last pos this handler left of.
The stating position for all subsequent searches are set to the saved position
'domGetContinuePos()' where this handler was last time it handled a page.

This way one can continue searching to next matching position every time this particular page
is loaded. Mostly usefull in seachPage scenarios where we repeatedly return to the same page to
initiate a new search. If one needs to click on the next link in a long list of categories, then one can
call this function to set starting dom position to where we left of last time. The next match
when calling for example domFind("movieCatogory__searchStep1__FIND") will then be the link after the last
one you found.
This can also be done using the navigator in an even simpler way using navDomClickNextCreate().

\see navDomClickNextCreate
*/
void domContinueSearch()
{
    curMiner()->domContinueSearch();
}


/**
Find position parent of dom node. You specify the number of levels up (ancestors)
you want from the input node. Current dom position is }not} modified only position is returned.
Like e.g:
\code
parentNode ( 1, pNode );	// Get immediate parent
parentNode ( 2, pNode );	// Get parent node of parent node (grandparent so to speak)
\endcode

\return The dom position of the specified dom node or zero.*/
int domFindParentPos (
    int iLevelsUp 			///< [in] Stop at parent number iLevelsUp (ONLY positive numbers).
)
{
    return curMiner()->domFindParentPos(iLevelsUp);
}


/**
Find parent of dom node. You specify the number of levels up (ancestors)
you want from the input node. Current dom position is modified to found parent if successfull.
Like e.g:
\code
parentNode ( 1, pNode );	// Get immediate parent
parentNode ( 2, pNode );	// Get parent node of parent node (grandparent so to speak)
\endcode

\return The dom position of the specified dom node or zero.*/
int domFindParent(
    int iLevelsUp 			///< [in] Stop at parent number iLevelsUp (ONLY positive numbers).
)
{
    return curMiner()->domFindParent(iLevelsUp);
}


// -----------------------------
// --- domFindNext functions ---
// -----------------------------


/**
Find from current position a node matching the dom sequence.
Dom is searched from the current dom node.
Current dom node is updated so that subsequent calls to domFindNext() will search from
this position. If no node is found the current dom node is NOT changed.
\note The current dom node is set to the }end including direction} of the matching sequence.
\return Updated dom node position or zero if not found. */
int	domFindNextParams(
        int iCount					///< [in] Stop at match number iCount (ONLY positive numbers, i.e forward search ).
      , const crawl::DomSeq& seq	///< [in] Dom sequence to search for
      , const std::string& sArgs	///< [in] Dom sequence arguments - as comma separated string.
      , int iNodeTypes 				///< [in] Restrict to node types. Default is all node types.
    )
{
    return curMiner()->domSeqFindNextParams(iCount, seq, sArgs, iNodeTypes);
}


/**
Find from current position a node matching the dom sequence.
Dom is searched from the current dom node.
Current dom node is updated so that subsequent calls to domFindNext() will search from
this position. If no node is found the current dom node is NOT changed.
\note The current dom node is set to the }end including direction} of the matching sequence.
\return Updated dom node position or zero if not found. */
//int	domFindNext(
//      int iCount						///< [in] Stop at match number iCount (ONLY positive numbers, i.e forward search ).
//    , const crawl::DomSeq& seq		///< [in] Dom sequence to search for
//    , int iNodeTypes 				///< [in] Restrict to node types. Default is all node types.
//	)
//{
//    return curMiner()->domFindNext(iCount, seq, iNodeTypes );
//}


/**
Find next occurrence of dom sequence. If \a sSequence can not be found as a named stored dom sequence
( created using domSeqCreate() ) an unnamed sequence is created and used. The \a sCompareFun is only used
in case a new dom sequence has to be created. In this case it is used as the default compare function
like in domSeqCreate().
In it's most simple form no dom sequence exist with the name \a sSequence and the parameter takes the form
of a simple string which is to be searched from current dom position using the compare function for example
like this:
\code
domFindNext ( 1, "Click to search", "equals", ALL_NODE_TYPES );
\endcode

!Logical OR between more named dom sequences
It's possible to create several similar named dom sequences and have domFind functions choose the first
that matches, i.e. in effect doing logical OR between them. The dom sequences can be created like this:
\code
domSeqCreate('MyDomSeq#1', 'H1, class, titel', equals, 1 );
domSeqCreate('MyDomSeq#1', 'TD, class, tracktitel, A', equals, 1 );
\endcode
The the 'MyDomSeq' is used later like:
\code
domFindNext	( 1, "MyDomSeq?" );
\endcode

!User defined PHP function
If the \a sSequence is the name of a user defined PHP function, then this function is executed instead of the
normal dom search. The dom positen after the execution of this function will then be returned as the new dom
position. This functionality is especially usefull when customizing a crawler template, where construction
a single dom sequence to get to the right dom position as required by the template is not possible/desired.

\return The new dom position or zero in case no match could be found.
 */
int domFindNext (int iCount				///< Stop at iCount occurrence of sequence. Negative values searches backwards. Not applicaple \a sSequence refers to a user defined PHP function
    , const std::string& sSequence		///< Named dom sequence, or string to use as dom sequence. Can also be the name of a user defined PHP function to call to do the actual dom search.
    , const std::string& sCompareFun	///< Default compare function to use in case \a sSequence is used to create a dom sequence in place.
    , int iPostMatchSteps				///< [in] Steps to move forward or backwards (negative) in dom after a match.
    )
{
    return curMiner()->domFindNext(iCount, sSequence, sCompareFun, iPostMatchSteps);
}

int domFindNext(int iCount, const std::string &sSequence, const std::string &sCompareFun, int iPostMatchSteps, int iNodeTypes)
{
    return curMiner()->domFindNext(iCount, sSequence, sCompareFun, iPostMatchSteps, iNodeTypes);
}


int domFindNext (
     int iCount							///< Stop at iCount occurrence of sequence. Negative values searches backwards. Not applicaple \a sSequence refers to a user defined PHP function
    ,const std::string& sSequence		///< Named dom sequence, or string to use as dom sequence. Can also be the name of a user defined PHP function to call to do the actual dom search.
    ,const std::string& sCompareFun		///< Default compare function to use in case \a sSequence is used to create a dom sequence in place.
    )
{
    return curMiner()->domFindNext( iCount, sSequence, sCompareFun );
}


int domFindNext (int iCount				///< Stop at iCount occurrence of sequence. Negative values searches backwards. Not applicaple \a sSequence refers to a user defined PHP function
    , const std::string& sSequence		///< Named dom sequence, or string to use as dom sequence. Can also be the name of a user defined PHP function to call to do the actual dom search.
    , int iPostMatchSteps				///< [in] Steps to move forward or backwards (negative) in dom after a match.
    )
{
    return curMiner()->domFindNext( iCount, sSequence, iPostMatchSteps);
}

int domFindNext (
      int iCount						///< Stop at iCount occurrence of sequence. Negative values searches backwards. Not applicaple \a sSequence refers to a user defined PHP function
    , const std::string& sSequence		///< Named dom sequence, or string to use as dom sequence. Can also be the name of a user defined PHP function to call to do the actual dom search.
    )
{
    return curMiner()->domFindNext( iCount, sSequence );
}

int domFindNext(const std::string &sSequence, const std::string &sCompareFun, int iPostMatchSteps, int iNodeTypes)
{
    return curMiner()->domFindNext( sSequence, sCompareFun, iPostMatchSteps, iNodeTypes);
}

int domFindNext(const std::string &sSequence, const std::string &sCompareFun, int iPostMatchSteps)
{
    return curMiner()->domFindNext( sSequence, sCompareFun, iPostMatchSteps);
}

/** Find next occurrence in forward direction (i.e. search forwards from current position)
of \a sSequence.
\return Updated dom position or zero if not found. */
int domFindNext (
      const std::string& sSequence		///< Named dom sequence, or string to use as dom sequence. Can also be the name of a user defined PHP function to call to do the actual dom search.
    , const std::string& sCompareFun	///< Default compare function to use in case \a sSequence is used to create a dom sequence in place.
    )
{
    return curMiner()->domFindNext( sSequence, sCompareFun);
}

int domFindNext(const std::string& sSequence, int iPostMatchSteps)
{
    return curMiner()->domFindNext( sSequence, iPostMatchSteps );
}

/** Find next occurrence in forward direction (i.e. search forwards from current position)
of \a sSequence.
\return Updated dom position or zero if not found. */
int domFindNext (
      const std::string& sSequence		///< Named dom sequence, or string to use as dom sequence. Can also be the name of a user defined PHP function to call to do the actual dom search.
    )
{
    return curMiner()->domFindNext( sSequence );
}

/** Find previous occurrence (i.e. search backwards from current position) of \a sSequence.
\return Updated dom position or zero if not found. */
int domFindPrev (
      const std::string& sSequence		///< Named dom sequence, or string to use as dom sequence. Can also be the name of a user defined PHP function to call to do the actual dom search.
    , const std::string& sCompareFun	///< Default compare function to use in case \a sSequence is used to create a dom sequence in place.
    )
{
    return curMiner()->domFindPrev( sSequence, sCompareFun);
}

int domFindNextParams (
      int iCount						///< Stop at iCount occurrence of sequence. Negative values searches backwards. Not applicaple \a sSequence refers to a user defined PHP function
    , const std::string& sSequence		///< Named dom sequence, or string to use as dom sequence. Can also be the name of a user defined PHP function to call to do the actual dom search.
    , const std::string& sArgs
    )
{
    return curMiner()->domSeqFindNextParams( iCount, sSequence, sArgs );
}


// -------------------------
// --- domFind functions ---
// -------------------------

int domFind(int iCount, const std::string &sSequence, const std::string &sCompareFun, int iPostMatchSteps, int iNodeTypes)
{
    return curMiner()->domFind( iCount, sSequence, sCompareFun, iPostMatchSteps, iNodeTypes);
}

/**
Find occurrence of dom sequence from start of page/dom. If \a sSequence can not be found as a named stored dom sequence
( created using domSeqCreate() ) an unnamed sequence is created and used. The \a sCompareFun is only used
in case a new dom sequence has to be created. In this case it is used as the default compare function
like in domSeqCreate().
In it's most simple form no dom sequence exist with the name \a sSequence and the parameter takes the form
of a simple string which is to be searched from current dom position using the compare function for example
like this:
\code
domFindNext ( 1, "Click to search", "equals", ALL_NODE_TYPES );
\endcode

!Logical OR between more named dom sequences
It's possible to create several similar named dom sequences and have domFind functions choose the first
that matches, i.e. in effect doing logical OR between them. The dom sequences can be created like this:
\code
domSeqCreate('MyDomSeq#1', 'H1, class, titel', equals, 1 );
domSeqCreate('MyDomSeq#1', 'TD, class, tracktitel, A', equals, 1 );
\endcode
The the 'MyDomSeq' is used later like:
\code
domFindNext	( 1, "MyDomSeq?" );
\endcode

!User defined PHP function
If the \a sSequence is the name of a user defined PHP function, then this function is executed instead of the
normal dom search. The dom positen after the execution of this function will then be returned as the new dom
position. This functionality is especially usefull when customizing a crawler template, where construction
a single dom sequence to get to the right dom position as required by the template is not possible/desired.

\return The new dom position or zero in case no match could be found.
 */
int domFind (
      int iCount						///< Stop at iCount occurrence of sequence. Negative values searches backwards. Not applicaple \a sSequence refers to a user defined PHP function
    , const std::string& sSequence		///< Named dom sequence, or string to use as dom sequence. Can also be the name of a user defined PHP function to call to do the actual dom search.
    , const std::string& sCompareFun	///< Default compare function to use in case \a sSequence is used to create a dom sequence in place.
    , int iPostMatchSteps				///< [in] Steps to move forward or backwards (negative) in dom after a match.
    )
{
    return curMiner()->domFind( iCount, sSequence, sCompareFun, iPostMatchSteps);
}

int domFind (
      int iCount						///< Stop at iCount occurrence of sequence. Negative values searches backwards. Not applicaple \a sSequence refers to a user defined PHP function
    , const std::string& sSequence		///< Named dom sequence, or string to use as dom sequence. Can also be the name of a user defined PHP function to call to do the actual dom search.
    , const std::string& sCompareFun	///< Default compare function to use in case \a sSequence is used to create a dom sequence in place.
    )
{
    return curMiner()->domFind( iCount, sSequence, sCompareFun);
}


int domFind (
      int iCount						///< Stop at iCount occurrence of sequence. Negative values searches backwards. Not applicaple \a sSequence refers to a user defined PHP function
    , const std::string& sSequence		///< Named dom sequence, or string to use as dom sequence. Can also be the name of a user defined PHP function to call to do the actual dom search.
    , int iPostMatchSteps				///< [in] Steps to move forward or backwards (negative) in dom after a match.
    )
{
    return curMiner()->domFind( iCount, sSequence, iPostMatchSteps);
}

int domFind (
      int iCount						///< Stop at iCount occurrence of sequence. Negative values searches backwards. Not applicaple \a sSequence refers to a user defined PHP function
    , const std::string& sSequence		///< Named dom sequence, or string to use as dom sequence. Can also be the name of a user defined PHP function to call to do the actual dom search.
    )
{
    return curMiner()->domFind( iCount, sSequence );
}


int domFind(const std::string &sSequence, const std::string &sCompareFun, int iPostMatchSteps, int iNodeTypes)
{
    return curMiner()->domFind( sSequence, sCompareFun, iPostMatchSteps, iNodeTypes);
}

int domFind(const std::string &sSequence, const std::string &sCompareFun, int iPostMatchSteps)
{
    return curMiner()->domFind( sSequence, sCompareFun, iPostMatchSteps);
}

int domFind (
      const std::string& sSequence		///< Named dom sequence, or string to use as dom sequence. Can also be the name of a user defined PHP function to call to do the actual dom search.
    , const std::string& sCompareFun	///< Default compare function to use in case \a sSequence is used to create a dom sequence in place.
        )
{
    return curMiner()->domFind( sSequence, sCompareFun );
}

int domFind(const std::string& sSequence, int iPostMatchSteps)
{
    return curMiner()->domFind( sSequence, iPostMatchSteps );
}

int domFind (
      const std::string& sSequence		///< Named dom sequence, or string to use as dom sequence. Can also be the name of a user defined PHP function to call to do the actual dom search.
        )
{
    return curMiner()->domFind( sSequence );
}


int domFindPos(int iCount, const std::string &sSequence, const std::string &sCompareFun, int iPostMatchSteps, int iNodeTypes)
{
    return curMiner()->domFindPos( iCount, sSequence, sCompareFun, iPostMatchSteps, iNodeTypes);
}

int domFindPos (
      int iCount						///< Stop at iCount occurrence of sequence. Negative values searches backwards. Not applicaple \a sSequence refers to a user defined PHP function
    , const std::string& sSequence		///< Named dom sequence, or string to use as dom sequence. Can also be the name of a user defined PHP function to call to do the actual dom search.
    , const std::string& sCompareFun	///< Default compare function to use in case \a sSequence is used to create a dom sequence in place.
    , int iPostMatchSteps				///< [in] Steps to move forward or backwards (negative) in dom after a match.
                )
{
    return curMiner()->domFindPos( iCount, sSequence, sCompareFun, iPostMatchSteps);
}

int domFindPos (
     int iCount							///< Stop at iCount occurrence of sequence. Negative values searches backwards. Not applicaple \a sSequence refers to a user defined PHP function
    ,const std::string& sSequence		///< Named dom sequence, or string to use as dom sequence. Can also be the name of a user defined PHP function to call to do the actual dom search.
    ,const std::string& sCompareFun		///< Default compare function to use in case \a sSequence is used to create a dom sequence in place.
    )
{
    return curMiner()->domFindPos(iCount, sSequence, sCompareFun);
}


int domFindPos (int iCount				///< Stop at iCount occurrence of sequence. Negative values searches backwards. Not applicaple \a sSequence refers to a user defined PHP function
    , const std::string& sSequence		///< Named dom sequence, or string to use as dom sequence. Can also be the name of a user defined PHP function to call to do the actual dom search.
    , int iPostMatchSteps				///< [in] Steps to move forward or backwards (negative) in dom after a match.
    )
{
    return curMiner()->domFindPos( iCount, sSequence, iPostMatchSteps );
}

int domFindPos (
     int iCount							///< Stop at iCount occurrence of sequence. Negative values searches backwards. Not applicaple \a sSequence refers to a user defined PHP function
    ,const std::string& sSequence		///< Named dom sequence, or string to use as dom sequence. Can also be the name of a user defined PHP function to call to do the actual dom search.
    )
{
    return curMiner()->domFindPos( iCount, sSequence );
}

int domFindPos(const std::string &sSequence, const std::string &sCompareFun, int iPostMatchSteps, int iNodeTypes)
{
    return curMiner()->domFindPos(sSequence, sCompareFun, iPostMatchSteps, iNodeTypes);
}

int domFindPos(const std::string &sSequence, const std::string &sCompareFun, int iPostMatchSteps)
{
    return curMiner()->domFindPos(sSequence, sCompareFun, iPostMatchSteps);
}

/** Find next occurrence in forward direction (i.e. search forwards from current position)
of \a sSequence.
\return Dom position or zero if not found. */
int domFindPos (
     const std::string& sSequence		///< Named dom sequence, or string to use as dom sequence. Can also be the name of a user defined PHP function to call to do the actual dom search.
    ,const std::string& sCompareFun		///< Default compare function to use in case \a sSequence is used to create a dom sequence in place.
    )
{
    return curMiner()->domFindPos(sSequence, sCompareFun);
}

int domFindPos(const std::string& sSequence, int iPostMatchSteps)
{
    return curMiner()->domFindPos(sSequence, iPostMatchSteps);
}

/** Find next occurrence in forward direction (i.e. search forwards from current position)
of \a sSequence.
\return Dom position or zero if not found. */
int domFindPos (
     const std::string& sSequence		///< Named dom sequence, or string to use as dom sequence. Can also be the name of a user defined PHP function to call to do the actual dom search.
    )
{
    return curMiner()->domFindPos(sSequence);
}

int domFindNextPos(int iCount, const std::string &sSequence, const std::string &sCompareFun, int iPostMatchSteps, int iNodeTypes)
{
    return curMiner()->domFindNextPos( iCount, sSequence, sCompareFun, iPostMatchSteps, iNodeTypes);
}


/** Find from current position a node matching the dom sequence.
Dom is searched from the current dom node. Current dom node is NOT updated. Only the
found position is returned.
If \a sSequence can not be found as a named stored dom sequence
( created using domSeqCreate() ) an unnamed sequence is created and used. The \a sCompareFun is only used
in case a new dom sequence has to be created. In this case it is used as the default compare function
like in domSeqCreate().
In it's most simple form no dom sequence exist with the name \a sSequence and the parameter takes the form
of a simple string which is to be searched from current dom position using the compare function for example
like this:
\code
domFindNext ( 1, "Click to search", "equals", ALL_NODE_TYPES );
\endcode

!Logical OR between more named dom sequences
It's possible to create several similar named dom sequences and have domFind functions choose the first
that matches, i.e. in effect doing logical OR between them. The dom sequences can be created like this:
\code
domSeqCreate('MyDomSeq#1', 'H1, class, titel', equals, 1 );
domSeqCreate('MyDomSeq#1', 'TD, class, tracktitel, A', equals, 1 );
\endcode
The the 'MyDomSeq' is used later like:
\code
domFindNext	( 1, "MyDomSeq?" );
\endcode

!User defined PHP function
If the \a sSequence is the name of a user defined PHP function, then this function is executed instead of the
normal dom search. The dom positen after the execution of this function will then be returned as the new dom
position. This functionality is especially usefull when customizing a crawler template, where construction
a single dom sequence to get to the right dom position as required by the template is not possible/desired.

\note The position returned corresponds to the }end including direction} of the matching sequence.
\return Position of found node or zero. */
int domFindNextPos (
      int iCount						///< Stop at iCount occurrence of sequence. Negative values searches backwards. Not applicaple \a sSequence refers to a user defined PHP function
    , const std::string& sSequence		///< Named dom sequence, or string to use as dom sequence. Can also be the name of a user defined PHP function to call to do the actual dom search.
    , const std::string& sCompareFun	///< Default compare function to use in case \a sSequence is used to create a dom sequence in place.
    , int iPostMatchSteps				///< [in] Steps to move forward or backwards (negative) in dom after a match.
                )
{
    return curMiner()->domFindNextPos( iCount, sSequence, sCompareFun, iPostMatchSteps);
}

int domFindNextPos (
     int iCount							///< Stop at iCount occurrence of sequence. Negative values searches backwards. Not applicaple \a sSequence refers to a user defined PHP function
    ,const std::string& sSequence		///< Named dom sequence, or string to use as dom sequence. Can also be the name of a user defined PHP function to call to do the actual dom search.
    ,const std::string& sCompareFun		///< Default compare function to use in case \a sSequence is used to create a dom sequence in place.
    )
{
    return curMiner()->domFindNextPos(iCount, sSequence, sCompareFun);
}


int domFindNextPos (
      int iCount						///< Stop at iCount occurrence of sequence. Negative values searches backwards. Not applicaple \a sSequence refers to a user defined PHP function
    , const std::string& sSequence		///< Named dom sequence, or string to use as dom sequence. Can also be the name of a user defined PHP function to call to do the actual dom search.
    , int iPostMatchSteps				///< [in] Steps to move forward or backwards (negative) in dom after a match.
    )
{
    return curMiner()->domFindNextPos( iCount, sSequence, iPostMatchSteps );
}

int domFindNextPos (
     int iCount							///< Stop at iCount occurrence of sequence. Negative values searches backwards. Not applicaple \a sSequence refers to a user defined PHP function
    ,const std::string& sSequence		///< Named dom sequence, or string to use as dom sequence. Can also be the name of a user defined PHP function to call to do the actual dom search.
    )
{
    return curMiner()->domFindNextPos( iCount, sSequence );
}

int domFindNextPos(const std::string &sSequence, const std::string &sCompareFun, int iPostMatchSteps, int iNodeTypes)
{
    return curMiner()->domFindNextPos(sSequence, sCompareFun, iPostMatchSteps, iNodeTypes);
}

int domFindNextPos(const std::string &sSequence, const std::string &sCompareFun, int iPostMatchSteps)
{
    return curMiner()->domFindNextPos(sSequence, sCompareFun, iPostMatchSteps);
}

/** Find next occurrence in forward direction (i.e. search forwards from current position)
of \a sSequence.
\return Dom position or zero if not found. */
int domFindNextPos (
     const std::string& sSequence		///< Named dom sequence, or string to use as dom sequence. Can also be the name of a user defined PHP function to call to do the actual dom search.
    ,const std::string& sCompareFun		///< Default compare function to use in case \a sSequence is used to create a dom sequence in place.
    )
{
    return curMiner()->domFindNextPos(sSequence, sCompareFun);
}

int domFindNextPos(const std::string& sSequence, int iPostMatchSteps)
{
    return curMiner()->domFindNextPos(sSequence, iPostMatchSteps);
}

/** Find next occurrence in forward direction (i.e. search forwards from current position)
of \a sSequence.
\return Dom position or zero if not found. */
int domFindNextPos (
     const std::string& sSequence		///< Named dom sequence, or string to use as dom sequence. Can also be the name of a user defined PHP function to call to do the actual dom search.
    )
{
    return curMiner()->domFindNextPos(sSequence);
}

/** Find previous occurrence (i.e. search backwards from current position) of \a sSequence.
\return Updated dom position or zero if not found. */
int domFindPrevPos (
     const std::string& sSequence		///< Named dom sequence, or string to use as dom sequence. Can also be the name of a user defined PHP function to call to do the actual dom search.
    ,const std::string& sCompareFun		///< Default compare function to use in case \a sSequence is used to create a dom sequence in place.
    )
{
    return curMiner()->domFindNextPos( sSequence, sCompareFun );
}


/** Find (from start) and 'click' the INPUT node at given position.
Dom is searched from the start, i.e.current dom node is set to the first node on the page.
Current dom node is updated so that subsequent calls to domXXNext() functions will search from
this position.
\return Updated dom node position or zero if not found. */
int	domClickInput( int iCount ) 	///< [in] Stop at match number iCount (ONLY positive numbers, i.e forward search ).
{
    return curMiner()->domClickInput( iCount );
}

/** Find (from current position) and 'click' the INPUT node at given position.
Dom is searched from the current dom node. Current dom node is updated so that subsequent calls to
domXXNext() functions will search from this position.
\return Updated dom node position or zero if not found. */
int	domClickInputNext( int iCount ) 		///< [in] Stop at match number iCount ( use negative numbers for backwards search ).
{
    return curMiner()->domClickInputNext( iCount );
}

/**
\return Updated dom node position or zero if not found. */
int	domSetInput	(
      int iCount							///< [in] Stop at match number iCount ( use negative numbers for backwards search ).
    , const std::string& sValue
    )
{
    return curMiner()->domSetInput( iCount, sValue );
}

/**
\return Updated dom node position or zero if not found. */
int	domSetInputNext	(
      int iCount							///< [in] Stop at match number iCount ( use negative numbers for backwards search ).
    , const std::string& sValue
    )
{
    return curMiner()->domSetInputNext( iCount, sValue );
}

/**
\return Updated dom node position or zero if not found. */
int	domSetInput	(
      int iCount					///< [in] Stop at match number iCount ( use negative numbers for backwards search ).
    , int iValue
    )
{
    return curMiner()->domSetInput( iCount, iValue );
}


/**
\return Updated dom node position or zero if not found. */
int	domSetInputNext	(
      int iCount					///< [in] Stop at match number iCount ( use negative numbers for backwards search ).
    , int iValue 	)
{
    return curMiner()->domSetInputNext( iCount, iValue );
}


/** Step a number of dom nodes forward or backwards from current position.
\return Updated dom node position or zero if not found. */
int	domStep	(
    int iCount, 		///< [in] Stop at match number iCount ( use negative numbers for backwards search ).
    int iNodeTypes )	///< [in] Restrict to node types. Default is all node types.
{
    return curMiner()->domStep( iCount, iNodeTypes );
}

/** Test for end of dom.
Note that the end of the dom means that we are past the last valid node.
\return true if current node is end of dom. */
bool	domAtEnd()
{
    return curMiner()->domAtEnd();
}

void domRangePushElement(int iElementPos)
{
    return curMiner()->domRangePushElement(iElementPos);
}

void domRangePush(int iStartPos, int iStopPos)
{
    return curMiner()->domRangePush(iStartPos, iStopPos);
}

void domRangePop()
{
    return curMiner()->domRangePop();
}

void domPointerPush()
{
    curMiner()->domPointerPush();
}

int	domPointerPop()
{
    return curMiner()->domPointerPop();
}

int domSize()
{
    return curMiner()->domSize();
}

int domEndPos()
{
    return curMiner()->domEndPos();
}

int domPos()
{
    return curMiner()->domPos();
}

int domPosSet( int iNewPos )
{
    return curMiner()->domPosSet( iNewPos );
}

int	domStartPosSet( int iStartPos )
{
    return curMiner()->domStartPosSet( iStartPos );
}

int	domStartPos()
{
    return curMiner()->domStartPos();
}

void domStartPosClear( )
{
    return curMiner()->domStartPosClear();
}

int	domStopPosSet( int iStopPos )
{
    return curMiner()->domStopPosSet( iStopPos );
}

int	domStopPos()
{
    return curMiner()->domStopPos();
}

void domStopPosClear( )
{
    return curMiner()->domStopPosClear();
}

void domSetAtEnd ()
{
    curMiner()->domSetAtEnd();
}

int domContinuePos()
{
    return curMiner()->domContinuePos();
}

int domThisElementPos()
{
    return curMiner()->domThisElementPos();
}

int domThisElementPos(int pos)
{
    return curMiner()->domThisElementPos(pos);
}

int domOwnerPos(int iLevelsUp)
{
    return curMiner()->domOwnerPos(iLevelsUp);
}

int domPosToOwner(int iLevelsUp)
{
    return curMiner()->domPosToOwner(iLevelsUp);
}

int domParentPos(int iLevelsUp)
{
    return curMiner()->domParentPos(iLevelsUp);
}

int domPosToParent(int iLevelsUp)
{
    return curMiner()->domPosToParent(iLevelsUp);
}

/*
-----------------------------------
--- LookForWord (lfw) functions ---
----------------------------------- */
void lfwMatchWholeWordsOnlySet(bool matchWholeWordsOnly)
{
    curMiner()->lfwMatchWholeWordsOnlySet(matchWholeWordsOnly);
}

void lfwClear()
{
    curMiner()->lfwClear();
}

void lfwClear(const std::string& contextName)
{
    curMiner()->lfwClear(contextName);
}

void lfwClear(const std::string& contextName, const std::string& referenceName)
{
    curMiner()->lfwClear(contextName, referenceName);
}

void lfwAddWord(const std::string& contextName, const std::string& referenceName,
                const std::string& word, const std::string& compareFun, int nodeTypes)
{
    curMiner()->lfwAddWord(contextName, referenceName, word, compareFun, nodeTypes);
}

void lfwRemoveWord(const std::string& contextName, const std::string& referenceName, const std::string& word)
{
    curMiner()->lfwRemoveWord(contextName, referenceName, word);
}

void lfwGetDataFunctionSet(const std::string& contextName, const std::string& getDataFunction)
{
    curMiner()->lfwGetDataFunctionSet(contextName, getDataFunction);
}

void lfwGetDataFallbackFunctionSet(const std::string& contextName, const std::string& getDataFallbackFunction)
{
    curMiner()->lfwGetDataFallbackFunctionSet(contextName, getDataFallbackFunction);
}

int lfwDomFind(const std::string& referenceName)
{
    return curMiner()->lfwDomFind(referenceName);
}

std::string lfwOutputValueFind(const std::string& referenceName)
{
    return curMiner()->lfwOutputValueFind(referenceName);
}

int lfwDomFindNext(const std::string& referenceName)
{
    return curMiner()->lfwDomFindNext(referenceName);
}

std::string lfwOutputValueFindNext(const std::string& referenceName)
{
    return curMiner()->lfwOutputValueFindNext(referenceName);
}

std::string lfwPreSequence(const std::string& referenceName)
{
    return curMiner()->lfwPreSequence(referenceName);
}

void lfwPreSequenceSet(const std::string& referenceName, const std::string& lfwPreSequence)
{
    curMiner()->lfwPreSequenceSet(referenceName, lfwPreSequence);
}

std::string lfwPostSequence(const std::string& referenceName)
{
    return curMiner()->lfwPostSequence(referenceName);
}

void lfwPostSequenceSet(const std::string& referenceName, const std::string& lfwPostSequence)
{
    curMiner()->lfwPostSequenceSet(referenceName, lfwPostSequence);
}

std::vector<int> lfwDomFindAllPositions(const std::string& referenceName)
{
    return curMiner()->lfwDomFindAllPositions(referenceName);
}


int lfwDomStartPos()
{
    return curMiner()->lfwDomStartPos();
}

void lfwDomStartPosSet(int pos)
{
    curMiner()->lfwDomStartPosSet(pos);
}

int lfwDomStopPos()
{
    return curMiner()->lfwDomStopPos();
}

void lfwDomStopPosSet(int pos)
{
    curMiner()->lfwDomStopPosSet(pos);
}


std::string lfwStartPosDomSeq(const std::string& contextName)
{
    return curMiner()->lfwStartPosDomSeq(contextName);
}

void lfwStartPosDomSeqSet(const std::string& contextName, const std::string& lfwStartPosDomSeq)
{
    curMiner()->lfwStartPosDomSeqSet(contextName, lfwStartPosDomSeq);
}

std::string lfwStopPosDomSeq(const std::string& contextName)
{
    return curMiner()->lfwStopPosDomSeq(contextName);
}

void lfwStopPosDomSeqSet(const std::string& contextName, const std::string& lfwStopPosDomSeq)
{
    curMiner()->lfwStopPosDomSeqSet(contextName, lfwStopPosDomSeq);
}


// -------------------------------------
// --- DOM Sequence create functions ---
// -------------------------------------
/**
\defgroup domSeqCreateFunctions Create DOM sequences
@{

Functions for creating DOM sequences
*/
void domSeqCreate (int iCount           ///< [in] Stop at match number iCount (use negative numbers for backwards search).
    , const std::string& sName 			///< [in] Unique name to assign the dom sequence.
    , const std::string& sSequence		///< [in] The actual sequence (by default comma separated).
    , const std::string& sCompareFun	///< [in] Name of default compare function to use.
    , int iPostMatchSteps				///< [in] Steps to move forward or backwards (negative) in dom after a match.
    , int iNodeTypes
    , const std::string& sCommaChar		///< [in] Separation char to use (default is comma ',')
    )
{
    curMiner()->domSeqCreate(iCount, sName, sSequence, sCompareFun, iPostMatchSteps, iNodeTypes, sCommaChar );
}

void domSeqCreate(
        int iCount
        , const std::string& sName
        , const std::string& sSequence
        , const std::string& sCompareFun
        , int iPostMatchSteps
        , int iNodeTypes)
{
    curMiner()->domSeqCreate(iCount, sName, sSequence, sCompareFun, iPostMatchSteps, iNodeTypes );
}


void domSeqCreate (
      int iCount                        ///< [in] Stop at match number iCount (use negative numbers for backwards search).
    , const std::string& sName 			///< [in] Unique name to assign the dom sequence.
    , const std::string& sSequence		///< [in] The actual sequence (by default comma separated).
    , const std::string& sCompareFun
    , int iPostMatchSteps
                  )
{
    curMiner()->domSeqCreate(iCount, sName, sSequence, sCompareFun, iPostMatchSteps);
}

void domSeqCreate (
      int iCount                        ///< [in] Stop at match number iCount (use negative numbers for backwards search).
    , const std::string& sName 			///< [in] Unique name to assign the dom sequence.
    , const std::string& sSequence		///< [in] The actual sequence (by default comma separated).
    , const std::string& sCompareFun
    )
{
    curMiner()->domSeqCreate(iCount, sName, sSequence, sCompareFun);
}


void domSeqCreate (
      int iCount                        ///< [in] Stop at match number iCount (use negative numbers for backwards search).
    , const std::string& sName 			///< [in] Unique name to assign the dom sequence.
    , const std::string& sSequence		///< [in] The actual sequence (by default comma separated).
    , int iPostMatchSteps
                  )
{
    curMiner()->domSeqCreate(iCount, sName, sSequence, iPostMatchSteps);
}

void domSeqCreate (
      int iCount                        ///< [in] Stop at match number iCount (use negative numbers for backwards search).
    , const std::string& sName 			///< [in] Unique name to assign the dom sequence.
    , const std::string& sSequence		///< [in] The actual sequence (by default comma separated).
                  )
{
    curMiner()->domSeqCreate(iCount, sName, sSequence);
}

void domSeqCreate (const std::string& sName 			///< [in] Unique name to assign the dom sequence.
    , const std::string& sSequence		///< [in] The actual sequence (by default comma separated).
    , const std::string& sCompareFun	///< [in] Name of default compare function to use.
    , int iPostMatchSteps				///< [in] Steps to move forward or backwards (negative) in dom after a match.
    , int iNodeTypes
    , const std::string& sCommaChar		///< [in] Separation char to use (default is comma ',')
    )
{
    curMiner()->domSeqCreate(sName, sSequence, sCompareFun, iPostMatchSteps, iNodeTypes, sCommaChar );
}

void domSeqCreate(
        const std::string& sName
        , const std::string& sSequence
        , const std::string& sCompareFun
        , int iPostMatchSteps
        , int iNodeTypes)
{
    curMiner()->domSeqCreate(sName, sSequence, sCompareFun, iPostMatchSteps, iNodeTypes);
}

void domSeqCreate (
     const std::string& sName
    ,const std::string& sSequence
    ,const std::string& sCompareFun
    ,int iPostMatchSteps
                  )
{
    curMiner()->domSeqCreate(sName, sSequence, sCompareFun, iPostMatchSteps);
}

void domSeqCreate (
     const std::string& sName
    ,const std::string& sSequence
    ,const std::string& sCompareFun
    )
{
    curMiner()->domSeqCreate(sName, sSequence, sCompareFun);
}


void domSeqCreate (
     const std::string& sName
    ,const std::string& sSequence
    ,int iPostMatchSteps
                  )
{
    curMiner()->domSeqCreate(sName, sSequence, iPostMatchSteps);
}

void domSeqCreate (
     const std::string& sName
    ,const std::string& sSequence
                  )
{
    curMiner()->domSeqCreate(sName, sSequence);
}

bool domSeqExists (
     const std::string& sName
                  )
{
    return curMiner()->domSeqExists(sName);
}
/**@}*/

/*
----------------------------------
--- Element children functions ---
---------------------------------  */

std::vector<int> nodeChildren(int iSearchDir)
{
    return curMiner()->nodeChildren(iSearchDir);
}

std::vector<int> nodeChildren(const std::string& tagName, int iSearchDir)
{
    return curMiner()->nodeChildren(tagName, iSearchDir);
}

std::vector<int> nodeChildrenRecur(const std::string& tagName, int iSearchDir)
{
    return curMiner()->nodeChildrenRecur(tagName, iSearchDir);
}

int nodeEndElementPos(int iSearchDir)
{
    return curMiner()->nodeEndElementPos(iSearchDir);
}


std::vector<int> posChildElements(int iDomPos)
{
    return curMiner()->posChildren(iDomPos);
}

std::vector<int> posChildren(const std::string& tagName, int iDomPos)
{
    return curMiner()->posChildren(tagName, iDomPos);

}

std::vector<int> posChildrenRecur(const std::string& tagName, int iDomPos)
{
    return curMiner()->posChildrenRecur(tagName, iDomPos);
}

int posEndElementPos(int iDomPos)
{
    return curMiner()->posEndElementPos(iDomPos);
}

// --------------------------------------
// --- Implementation: Node functions ---
// --------------------------------------

/** Get type of the current node. */
int	nodeType ()
{
    return curMiner()->nodeType();
}

/** Perform 'click' on the current dom node. In case node is an A href load the URL directly.
\return true if click was successfull. */
bool nodeClickLoadHref	(
      int iSearchDir
    )
{
    return curMiner()->nodeClickLoadHref( iSearchDir );
}


/** Perform 'click' on the current dom node.
\return true if click was successfull. */
bool nodeClick	(
      int iSearchDir
    )
{
    return curMiner()->nodeClick( iSearchDir );
}

bool userClick(int iSearchDir)
{
    return curMiner()->userClick(iSearchDir);
}

bool userMouseEvent(int eventType, int button, int buttons, int modifiers, int iSearchDir)
{
    return curMiner()->userMouseEvent(eventType, button, buttons, modifiers, iSearchDir);
}


/** Perform 'click' on the current dom node.
\return true if click was successfull. */
bool nodeClickWait	(int timeoutInMs , int iSearchDir)
{
    return curMiner()->nodeClickWait(timeoutInMs, iSearchDir);
}


bool nodeMouseEvent	(
    const std::string& sEvent
    )
{
    return curMiner()->nodeMouseEvent( sEvent );
}

/** Send mouse event the current dom node.
!Events:
-focus
-blur
-select
-change
-click
-dblclick
-mousedown
-mouseup
-mouseover
-mousemove
-mouseout
-keypress
-keydown
-keyup

\return true if successfull. */
bool nodeMouseEvent	(
    const std::string& sEvent,
    int iSearchDir
    )
{
    return curMiner()->nodeMouseEvent( sEvent, iSearchDir );
}

bool nodeMouseEvent	(
      const std::string& sEvent
    , int iButton
    , int iSearchDir
    )
{
    return curMiner()->nodeMouseEvent( sEvent, iButton, iSearchDir );
}

bool nodeJavaScriptEvaluate	( const std::string& sJavaScript, int iSearchDir )
{
    return curMiner()->nodeJavaScriptEvaluate( sJavaScript, iSearchDir );
}

bool inputSet (
      const std::string& sValue
    , int iSearchDir
    )
{
    return curMiner()->inputSet( sValue, iSearchDir );
}

bool inputSet (
      int iValue
    , int iSearchDir
    )
{
    return curMiner()->inputSet(iValue, iSearchDir );
}

std::string innerHtml(int iSearchDir)
{
    return curMiner()->innerHtml(iSearchDir);
}

bool innerHtmlSet(const std::string &sValue, int iSearchDir)
{
    return curMiner()->innerHtmlSet(sValue, iSearchDir);
}

std::string innerText(int iSearchDir)
{
    return curMiner()->innerText(iSearchDir);
}

bool innerTextSet(const std::string &sValue, int iSearchDir)
{
    return curMiner()->innerTextSet(sValue, iSearchDir);
}

bool inputValue (
      const std::string& sValue
    , int iSearchDir
    )
{
    return curMiner()->inputSet( sValue, iSearchDir );
}

bool inputValue (
      int iValue
    , int iSearchDir
    )
{
    return curMiner()->inputSet(iValue, iSearchDir );
}


bool formSubmit (
    int iSearchDir )
{
    return curMiner()->formSubmit(iSearchDir);
}


bool formReset (
    int iSearchDir )
{
    return curMiner()->formReset(iSearchDir);
}



/** Get lenght of 'current' SELECT element. Current 'nearest' element is assumed to
be a SELECT or an OPTION element.
\note The SELECT element does not have to be exactly at current dom position. First we see
      if nearest ELEMENT_NODE is a SELECT element. If not we check if the nearest element is
      an OPTION element and if so we use it's parent as the SELECT element. If both these fail
      we search for nearest ELEMENT_NODE that is a SELECT element.
*/
int selectLength (
    int iSearchDir )
{
    return curMiner()->selectLength(iSearchDir);
}

/** Get index of currenly selected option. Current 'nearest' element is assumed to
be a SELECT or an OPTION element.
\note The SELECT element does not have to be exactly at current dom position. First we see
      if nearest ELEMENT_NODE is a SELECT element. If not we check if the nearest element is
      an OPTION element and if so we use it's parent as the SELECT element. If both these fail
      we search for nearest ELEMENT_NODE that is a SELECT element.
*/
int selectSelectedIndex (
    int iSearchDir
 )
{
    return curMiner()->selectSelectedIndex(iSearchDir);
}

/** Get text of currenly selected option. Current 'nearest' element is assumed to
be a SELECT or an OPTION element.
\note The SELECT element does not have to be exactly at current dom position. First we see
      if nearest ELEMENT_NODE is a SELECT element. If not we check if the nearest element is
      an OPTION element and if so we use it's parent as the SELECT element. If both these fail
      we search for nearest ELEMENT_NODE that is a SELECT element.
*/
std::string selectSelectedText (
    int iSearchDir
 )
{
    return curMiner()->selectSelectedText(iSearchDir);
}

/** Get value of currenly selected option. Current 'nearest' element is assumed to
be a SELECT or an OPTION element.
\note The SELECT element does not have to be exactly at current dom position. First we see
      if nearest ELEMENT_NODE is a SELECT element. If not we check if the nearest element is
      an OPTION element and if so we use it's parent as the SELECT element. If both these fail
      we search for nearest ELEMENT_NODE that is a SELECT element.
*/
std::string selectSelectedValue (
    int iSearchDir
 )
{
    return curMiner()->selectSelectedValue(iSearchDir);
}

/** Get dom position of currenly selected option. Current 'nearest' element is assumed to
be a SELECT or an OPTION element.
\note The SELECT element does not have to be exactly at current dom position. First we see
      if nearest ELEMENT_NODE is a SELECT element. If not we check if the nearest element is
      an OPTION element and if so we use it's parent as the SELECT element. If both these fail
      we search for nearest ELEMENT_NODE that is a SELECT element.
*/
int selectSelectedDomPos (
    int iSearchDir )
{
    return curMiner()->selectSelectedDomPos(iSearchDir);
}

/** \deprecated Use New name 'selectIndex' instead. */
bool selectSelect (
    int iIndex,
    int iSearchDir )
{
    return curMiner()->selectSelect( iIndex, iSearchDir );
}

bool selectIndex (
    int iIndex,
    int iSearchDir )
{
    return curMiner()->selectIndex(iIndex, iSearchDir );
}

bool selectIndexWait (int iIndex,
    int timeoutInMs,
    int iSearchDir)
{
    return curMiner()->selectIndexWait(iIndex, timeoutInMs, iSearchDir );
}

bool selectOption (
    int iSearchDir
    )
{
    return curMiner()->selectOption(iSearchDir);
}

bool selectOptionWait(int timeoutInMs, int iSearchDir)
{
    return curMiner()->selectOptionWait(timeoutInMs, iSearchDir);
}

int selectIndexOfOption (
    int iSearchDir
    )
{
    return curMiner()->selectIndexOfOption(iSearchDir);
}

/**
Do dom simple action like 'nodeClick', 'inputValue' etc using current dom node as starting point.
\sa doAction
\remark This is primarely intended as a helper function, since it's functionality is completely
covered by the general doAction() function(s).
\return true if operation was successfull
*/
bool doActionSimple (
     const std::string& sAction		///< [in] name of named action to lookup, ID of action to perform or the name of a PHP function to execute
    ,const std::string& sParam1		///< [in] Parameter 1 to action, if applicable, can be set to empty string if not needed.
    ,const std::string& sParam2		///< [in] Parameter 2 to action, if applicable, can be set to empty string if not needed.
    ,int iSearchDir					///< [in] "Direction" to search for the node: NEAREST_FORWARD, NEAREST_BACKWARD, NEAREST_BOTH, NEAREST_PARENT , NEAREST_AUTO, NEAREST_THIS_NODE
    )
{
    return curMiner()->doActionSimple(sAction, sParam1, sParam2, iSearchDir);
}

/**
Do dom action like 'click', 'inputValue' etc using current dom node as starting point.
The dom action (\a sAction) could also refer to a 'named' dom action created using createDomAction(). In this case
the parameters \a sParam1, \a sParam2, \a iSearchDir will all be ignored since they are embedded in the
reference to the named dom action.

!User defined PHP function
If the \a sAction is the name of a user defined PHP function, then this function is executed instead of the
normal action lookup/execution. This functionality is especially usefull when customizing a crawler template,
where the named dom action to use needs to be more complex than what a single simple action like 'click'
can do.

\remark This function is a a uniform (crawler template friendly) way to do the usual nodeClick(), inputSet(), ... etc.
actions.
\sa createDomAction
\return true if operation was successfull
*/
bool doAction (
     const std::string& sAction		///< [in] name of named action to lookup, ID of action to perform or the name of a PHP function to execute
    ,const std::string& sParam1		///< [in] Parameter 1 to action, if applicable, can be set to empty string if not needed.
    ,const std::string& sParam2		///< [in] Parameter 2 to action, if applicable, can be set to empty string if not needed.
    ,int iSearchDir					///< [in] "Direction" to search for the node: NEAREST_FORWARD, NEAREST_BACKWARD, NEAREST_BOTH, NEAREST_PARENT , NEAREST_AUTO, NEAREST_THIS_NODE
    )
{
    return curMiner()->doAction( sAction, sParam1, sParam2, iSearchDir);
}

/**
Do dom action like 'click', 'inputValue' etc using current dom node as starting point.
The dom action (\a sAction) could also refer to a 'named' dom action created using createDomAction(). In this case
the parameters \a sParam1, \a sParam2 will be ignored since they are embedded in the
reference to the named dom action.

This version (overload) of the function does not take the 'iSearchDir' parameter. The function will allways
work as if that parameter is set to 'NEAREST_AUTO'.

!User defined PHP function
If the \a sAction is the name of a user defined PHP function, then this function is executed instead of the
normal action lookup/execution. This functionality is especially usefull when customizing a crawler template,
where the named dom action to use needs to be more complex than what a single simple action like 'click'
can do.

\remark This function is a a uniform (crawler template friendly) way to do the usual nodeClick(), inputSet(), ... etc.
actions.
\sa createDomAction
\return true if operation was successfull
*/
bool doAction (
     const std::string& sAction		///< [in] name of named action to lookup, ID of action to perform or the name of a PHP function to execute
    ,const std::string& sParam1		///< [in] Parameter 1 to action, if applicable, can be set to empty string if not needed.
    ,const std::string& sParam2		///< [in] Parameter 2 to action, if applicable, can be set to empty string if not needed.
    )
{
    return curMiner()->doAction( sAction, sParam1, sParam2 );
}


/**
Do dom action like 'click', 'inputValue' etc using current dom node as starting point.
The dom action (\a sAction) could also refer to a 'named' dom action created using createDomAction(). In this case
the parameters \a sParam1, \a iSearchDir will be ignored since they are embedded in the
reference to the named dom action.

In case the action simply refers to a built-in simple action like 'click' the default search direction
is: 'NEAREST_AUTO'.

!User defined PHP function
If the \a sAction is the name of a user defined PHP function, then this function is executed instead of the
normal action lookup/execution. This functionality is especially usefull when customizing a crawler template,
where the named dom action to use needs to be more complex than what a single simple action like 'click'
can do.

\remark This function is a a uniform (crawler template friendly) way to do the usual nodeClick(), inputSet(), ... etc.
actions.
\sa createDomAction
\return true if operation was successfull
*/
bool doAction (
     const std::string& sAction		///< [in] name of named action to lookup, ID of action to perform or the name of a PHP function to execute
    ,const std::string& sParam1		///< [in] Parameter 1 to action, if applicable, can be set to empty string if not needed.
    ,int iSearchDir					///< [in] "Direction" to search for the node: NEAREST_FORWARD, NEAREST_BACKWARD, NEAREST_BOTH, NEAREST_PARENT , NEAREST_AUTO, NEAREST_THIS_NODE
    )
{
    return curMiner()->doAction( sAction, sParam1, iSearchDir);
}


/**
Do dom action like 'click', 'inputValue' etc using current dom node as starting point.
The dom action (\a sAction) could also refer to a 'named' dom action created using createDomAction(). In this case
the parameter \a iSearchDir will be ignored since it's are embedded in the reference to the named dom action.

In case the action simply refers to a built-in simple action like 'click' the default search direction
is: 'NEAREST_AUTO'.

!User defined PHP function
If the \a sAction is the name of a user defined PHP function, then this function is executed instead of the
normal action lookup/execution. This functionality is especially usefull when customizing a crawler template,
where the named dom action to use needs to be more complex than what a single simple action like 'click'
can do.

\remark This function is a a uniform (crawler template friendly) way to do the usual nodeClick(), inputSet(), ... etc.
actions.
\sa createDomAction
\return true if operation was successfull
*/
bool doAction (
     const std::string& sAction		///< [in] name of named action to lookup, ID of action to perform or the name of a PHP function to execute
    ,int iSearchDir					///< [in] "Direction" to search for the node: NEAREST_FORWARD, NEAREST_BACKWARD, NEAREST_BOTH, NEAREST_PARENT , NEAREST_AUTO, NEAREST_THIS_NODE
    )
{
    return curMiner()->doAction( sAction, iSearchDir);
}

/** */
float nodeGeomPosX(int iSearchDir)
{
    return curMiner()->nodeGeomPosX(iSearchDir);
}

/** */
float nodeGeomPosY(int iSearchDir)
{
    return curMiner()->nodeGeomPosY(iSearchDir);
}

/** */
float nodeGeomWidth(int iSearchDir)
{
    return curMiner()->nodeGeomWidth(iSearchDir);
}

/** */
float nodeGeomHeight(int iSearchDir)
{
    return curMiner()->nodeGeomHeight(iSearchDir);
}

/*
----------------------------------------
--- DOM doActionFind(Next) functions ---
---------------------------------------- */
/// TODO: Should go out, since it's a helper and should not be called from scripts
int	doActionFindNextImpl(
     int iCount 								///< [in] Stop at match number iCount (use negative numbers for backwards search).
    ,const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sAction					///< [in] name of named action to lookup, ID of action to perform or the name of a PHP function to execute
    ,const std::string& sParam1					///< [in] Parameter 1 to action, if applicable, can be set to empty string if not needed.
    ,const std::string& sParam2					///< [in] Parameter 2 to action, if applicable, can be set to empty string if not needed.
    ,int iSearchDir								///< [in] "Direction" to search for the node: NEAREST_FORWARD, NEAREST_BACKWARD, NEAREST_BOTH, NEAREST_PARENT , NEAREST_AUTO, NEAREST_THIS_NODE
    ,bool bUpdateDomPos							///< [in] Do update dom position to found position.
    )
{
    return curMiner()->doActionFindNextImpl( iCount, sSequence, sAction, sParam1, sParam2, iSearchDir, bUpdateDomPos );
}

/*
--------------------------------------
--- DOM doActionFindNext functions ---
-------------------------------------- */

int		doActionFindNext(
     int iCount 								///< [in] Stop at match number iCount (use negative numbers for backwards search).
    ,const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sAction					///< [in] name of named action to lookup, ID of action to perform or the name of a PHP function to execute
    ,const std::string& sParam1					///< [in] Parameter 1 to action, if applicable, can be set to empty string if not needed.
    ,const std::string& sParam2					///< [in] Parameter 2 to action, if applicable, can be set to empty string if not needed.
    ,int iSearchDir								///< [in] "Direction" to search for the node: NEAREST_FORWARD, NEAREST_BACKWARD, NEAREST_BOTH, NEAREST_PARENT , NEAREST_AUTO, NEAREST_THIS_NODE
    )
{
    return curMiner()->doActionFindNext( iCount, sSequence, sAction, sParam1, sParam2, iSearchDir);
}

int		doActionFindNext (
     int iCount 								///< [in] Stop at match number iCount (use negative numbers for backwards search).
    ,const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sAction					///< [in] name of named action to lookup, ID of action to perform or the name of a PHP function to execute
    ,const std::string& sParam1					///< [in] Parameter 1 to action, if applicable, can be set to empty string if not needed.
    ,const std::string& sParam2					///< [in] Parameter 2 to action, if applicable, can be set to empty string if not needed.
    )
{
    return curMiner()->doActionFindNext(iCount, sSequence, sAction, sParam1, sParam2 );
}

int		doActionFindNext (
     int iCount 								///< [in] Stop at match number iCount (use negative numbers for backwards search).
    ,const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sAction					///< [in] name of named action to lookup, ID of action to perform or the name of a PHP function to execute
    ,const std::string& sParam1					///< [in] Parameter 1 to action, if applicable, can be set to empty string if not needed.
    ,int iSearchDir								///< [in] "Direction" to search for the node: NEAREST_FORWARD, NEAREST_BACKWARD, NEAREST_BOTH, NEAREST_PARENT , NEAREST_AUTO, NEAREST_THIS_NODE
    )
{
    return curMiner()->doActionFindNext( iCount, sSequence, sAction, sParam1, iSearchDir);
}

int		doActionFindNext (
     int iCount 								///< [in] Stop at match number iCount (use negative numbers for backwards search).
    ,const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sAction					///< [in] name of named action to lookup, ID of action to perform or the name of a PHP function to execute
    ,int iSearchDir								///< [in] "Direction" to search for the node: NEAREST_FORWARD, NEAREST_BACKWARD, NEAREST_BOTH, NEAREST_PARENT , NEAREST_AUTO, NEAREST_THIS_NODE
    )
{
    return curMiner()->doActionFindNext( iCount, sSequence, sAction, iSearchDir);
}


int		doActionFindNext(
     const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sAction					///< [in] name of named action to lookup, ID of action to perform or the name of a PHP function to execute
    ,const std::string& sParam1					///< [in] Parameter 1 to action, if applicable, can be set to empty string if not needed.
    ,const std::string& sParam2					///< [in] Parameter 2 to action, if applicable, can be set to empty string if not needed.
    ,int iSearchDir								///< [in] "Direction" to search for the node: NEAREST_FORWARD, NEAREST_BACKWARD, NEAREST_BOTH, NEAREST_PARENT , NEAREST_AUTO, NEAREST_THIS_NODE
    )
{
    return curMiner()->doActionFindNext( sSequence, sAction, sParam1, sParam2, iSearchDir);
}

int		doActionFindNext (
     const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sAction					///< [in] name of named action to lookup, ID of action to perform or the name of a PHP function to execute
    ,const std::string& sParam1					///< [in] Parameter 1 to action, if applicable, can be set to empty string if not needed.
    ,const std::string& sParam2					///< [in] Parameter 2 to action, if applicable, can be set to empty string if not needed.
    )
{
    return curMiner()->doActionFindNext( sSequence, sAction, sParam1, sParam2 );
}

int		doActionFindNext (
     const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sAction					///< [in] name of named action to lookup, ID of action to perform or the name of a PHP function to execute
    ,const std::string& sParam1					///< [in] Parameter 1 to action, if applicable, can be set to empty string if not needed.
    ,int iSearchDir								///< [in] "Direction" to search for the node: NEAREST_FORWARD, NEAREST_BACKWARD, NEAREST_BOTH, NEAREST_PARENT , NEAREST_AUTO, NEAREST_THIS_NODE
    )
{
    return curMiner()->doActionFindNext( sSequence, sAction, sParam1, iSearchDir);
}

int		doActionFindNext (
     const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sAction					///< [in] name of named action to lookup, ID of action to perform or the name of a PHP function to execute
    ,int iSearchDir								///< [in] "Direction" to search for the node: NEAREST_FORWARD, NEAREST_BACKWARD, NEAREST_BOTH, NEAREST_PARENT , NEAREST_AUTO, NEAREST_THIS_NODE
    )
{
    return curMiner()->doActionFindNext( sSequence, sAction, iSearchDir);
}


/*
----------------------------------
--- DOM doActionFind functions ---
---------------------------------- */
int		doActionFind(
     int iCount 								///< [in] Stop at match number iCount (use negative numbers for backwards search).
    ,const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sAction					///< [in] name of named action to lookup, ID of action to perform or the name of a PHP function to execute
    ,const std::string& sParam1					///< [in] Parameter 1 to action, if applicable, can be set to empty string if not needed.
    ,const std::string& sParam2					///< [in] Parameter 2 to action, if applicable, can be set to empty string if not needed.
    ,int iSearchDir								///< [in] "Direction" to search for the node: NEAREST_FORWARD, NEAREST_BACKWARD, NEAREST_BOTH, NEAREST_PARENT , NEAREST_AUTO, NEAREST_THIS_NODE
    )
{
    return curMiner()->doActionFind( iCount, sSequence, sAction, sParam1, sParam2, iSearchDir );
}

int		doActionFind(
     int iCount 								///< [in] Stop at match number iCount (use negative numbers for backwards search).
    ,const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sAction					///< [in] name of named action to lookup, ID of action to perform or the name of a PHP function to execute
    ,const std::string& sParam1					///< [in] Parameter 1 to action, if applicable, can be set to empty string if not needed.
    ,const std::string& sParam2					///< [in] Parameter 2 to action, if applicable, can be set to empty string if not needed.
    )
{
    return curMiner()->doActionFind( iCount, sSequence, sAction, sParam1, sParam2 );
}

int		doActionFind(
     int iCount 								///< [in] Stop at match number iCount (use negative numbers for backwards search).
    ,const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sAction					///< [in] name of named action to lookup, ID of action to perform or the name of a PHP function to execute
    ,const std::string& sParam1					///< [in] Parameter 1 to action, if applicable, can be set to empty string if not needed.
    ,int iSearchDir								///< [in] "Direction" to search for the node: NEAREST_FORWARD, NEAREST_BACKWARD, NEAREST_BOTH, NEAREST_PARENT , NEAREST_AUTO, NEAREST_THIS_NODE
    )
{
    return curMiner()->doActionFind( iCount, sSequence, sAction, sParam1, iSearchDir);
}

int		doActionFind(
     int iCount 								///< [in] Stop at match number iCount (use negative numbers for backwards search).
    ,const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sAction					///< [in] name of named action to lookup, ID of action to perform or the name of a PHP function to execute
    ,int iSearchDir								///< [in] "Direction" to search for the node: NEAREST_FORWARD, NEAREST_BACKWARD, NEAREST_BOTH, NEAREST_PARENT , NEAREST_AUTO, NEAREST_THIS_NODE
    )
{
    return curMiner()->doActionFind( iCount, sSequence, sAction, iSearchDir );
}


int		doActionFind(
     const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sAction					///< [in] name of named action to lookup, ID of action to perform or the name of a PHP function to execute
    ,const std::string& sParam1					///< [in] Parameter 1 to action, if applicable, can be set to empty string if not needed.
    ,const std::string& sParam2					///< [in] Parameter 2 to action, if applicable, can be set to empty string if not needed.
    ,int iSearchDir								///< [in] "Direction" to search for the node: NEAREST_FORWARD, NEAREST_BACKWARD, NEAREST_BOTH, NEAREST_PARENT , NEAREST_AUTO, NEAREST_THIS_NODE
    )
{
    return curMiner()->doActionFind( sSequence, sAction, sParam1, sParam2, iSearchDir );
}

int		doActionFind(
     const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sAction					///< [in] name of named action to lookup, ID of action to perform or the name of a PHP function to execute
    ,const std::string& sParam1					///< [in] Parameter 1 to action, if applicable, can be set to empty string if not needed.
    ,const std::string& sParam2					///< [in] Parameter 2 to action, if applicable, can be set to empty string if not needed.
    )
{
    return curMiner()->doActionFind( sSequence, sAction, sParam1, sParam2 );
}

int		doActionFind(
     const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sAction					///< [in] name of named action to lookup, ID of action to perform or the name of a PHP function to execute
    ,const std::string& sParam1					///< [in] Parameter 1 to action, if applicable, can be set to empty string if not needed.
    ,int iSearchDir								///< [in] "Direction" to search for the node: NEAREST_FORWARD, NEAREST_BACKWARD, NEAREST_BOTH, NEAREST_PARENT , NEAREST_AUTO, NEAREST_THIS_NODE
    )
{
    return curMiner()->doActionFind( sSequence, sAction, sParam1, iSearchDir);
}

int		doActionFind(
     const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sAction					///< [in] name of named action to lookup, ID of action to perform or the name of a PHP function to execute
    ,int iSearchDir								///< [in] "Direction" to search for the node: NEAREST_FORWARD, NEAREST_BACKWARD, NEAREST_BOTH, NEAREST_PARENT , NEAREST_AUTO, NEAREST_THIS_NODE
    )
{
    return curMiner()->doActionFind( sSequence, sAction, iSearchDir );
}


/*
-----------------------------------
--- DOM Action create functions ---
----------------------------------- */

/** Create a named dom action.
The \a sAction should be one of the built in actions which are:
\include ./_doc/domactiontable.inc
\sa doAction functions */
void domActionCreate (
     const std::string& sName		///< [in] Name of the named action we are creating (e.g. 'MyClickNextBtnAction' )
    ,const std::string& sAction		///< [in] (String) ID of action to perform
    ,const std::string& sParam1		///< [in] Parameter 1 to action, if applicable, can be set to empty string if not needed.
    ,const std::string& sParam2		///< [in] Parameter 2 to action, if applicable, can be set to empty string if not needed.
    ,int iSearchDir					///< [in] "Direction" to search for the node: NEAREST_FORWARD, NEAREST_BACKWARD, NEAREST_BOTH, NEAREST_PARENT , NEAREST_AUTO, NEAREST_THIS_NODE
    )
{
    curMiner()->domActionCreate(sName, sAction, sParam1, sParam2, iSearchDir);
}

/** Create a named dom action.
The \a sAction should be one of the built in actions which are:
\include _doc/domactiontable.inc

This version (overload) of the function does not take the 'iSearchDir' parameter. The function will allways
work as if that parameter is set to 'NEAREST_AUTO'.

\sa doAction functions */
void domActionCreate (
     const std::string& sName		///< [in] Name of the named action we are creating (e.g. 'MyClickNextBtnAction' )
    ,const std::string& sAction		///< [in] (String) ID of action to perform
    ,const std::string& sParam1		///< [in] Parameter 1 to action, if applicable, can be set to empty string if not needed.
    ,const std::string& sParam2		///< [in] Parameter 2 to action, if applicable, can be set to empty string if not needed.
    )
{
    curMiner()->domActionCreate( sName, sAction, sParam1, sParam2 );
}

/** Create a named dom action.
The \a sAction should be one of the built in actions which are:
\include _doc/domactiontable.inc

\sa doAction functions */
void domActionCreate (
     const std::string& sName		///< [in] Name of the named action we are creating (e.g. 'MyClickNextBtnAction' )
    ,const std::string& sAction		///< [in] (String) ID of action to perform
    ,const std::string& sParam1		///< [in] Parameter 1 to action, if applicable, can be set to empty string if not needed.
    ,int iSearchDir					///< [in] "Direction" to search for the node: NEAREST_FORWARD, NEAREST_BACKWARD, NEAREST_BOTH, NEAREST_PARENT , NEAREST_AUTO, NEAREST_THIS_NODE
    )
{
    curMiner()->domActionCreate( sName, sAction, sParam1, iSearchDir);
}

/** Create a named dom action.
The \a sAction should be one of the built in actions which are:
\include _doc/domactiontable.inc

\sa doAction functions */
void domActionCreate (
     const std::string& sName		///< [in] Name of the named action we are creating (e.g. 'MyClickNextBtnAction' )
    ,const std::string& sAction		///< [in] (String) ID of action to perform
    ,int iSearchDir					///< [in] "Direction" to search for the node: NEAREST_FORWARD, NEAREST_BACKWARD, NEAREST_BOTH, NEAREST_PARENT , NEAREST_AUTO, NEAREST_THIS_NODE
    )
{
    curMiner()->domActionCreate( sName, sAction, iSearchDir);
}


/*
--------------------------------------------------------------------
--- Modifier create functions (OutputModifier create functions)  ---
-------------------------------------------------------------------- */
void modifierCreate	(
      const std::string& sModifierID						///< [in] Name to use for new modifier.
    , const std::string& sManipFunID						///< [in] ID of built-in string modifier/manipulation function. E.g. 'append', 'replaceAll', ...
    , const std::string& sManipParam1						///< [in] Parameter 1 to modifier function.
    , const std::string& sManipParam2 						///< [in] Parameter 2 to modifier function.
    , const std::string& sManipParam3						///< [in] Parameter 3 to modifier function.
    , const std::string& /* sManipParam4 reserved */		///< [in] Parameter 4 to modifier function.
)
{
    curMiner()->modifierCreate( sModifierID, sManipFunID, sManipParam1, sManipParam2, sManipParam3 );
}

void modifierCreate	(
     const std::string& sModifierID						///< [in] Name to use for new modifier.
    ,const std::string& sManipFunID						///< [in] ID of built-in string modifier/manipulation function. E.g. 'append', 'replaceAll', ...
    ,const std::string& sManipParam1					///< [in] Parameter 1 to modifier function.
    ,const std::string& sManipParam2 					///< [in] Parameter 2 to modifier function.
    ,const std::string& sManipParam3					///< [in] Parameter 3 to modifier function.
)
{
    curMiner()->modifierCreate( sModifierID, sManipFunID, sManipParam1, sManipParam2, sManipParam3 );
}

void modifierCreate	(
     const std::string& sModifierID						///< [in] Name to use for new modifier.
    ,const std::string& sManipFunID						///< [in] ID of built-in string modifier/manipulation function. E.g. 'append', 'replaceAll', ...
    ,const std::string& sManipParam1					///< [in] Parameter 1 to modifier function.
    ,const std::string& sManipParam2 					///< [in] Parameter 2 to modifier function.
)
{
    curMiner()->modifierCreate( sModifierID, sManipFunID, sManipParam1, sManipParam2 );
}

void modifierCreate	(
     const std::string& sModifierID						///< [in] Name to use for new modifier.
    ,const std::string& sManipFunID						///< [in] ID of built-in string modifier/manipulation function. E.g. 'append', 'replaceAll', ...
    ,const std::string& sManipParam1					///< [in] Parameter 1 to modifier function.
)
{
    curMiner()->modifierCreate( sModifierID, sManipFunID, sManipParam1 );
}

void modifierCreate	(
     const std::string& sModifierID						///< [in] Name to use for new modifier.
    ,const std::string& sManipFunID						///< [in] ID of built-in string modifier/manipulation function. E.g. 'append', 'replaceAll', ...
)
{
    curMiner()->modifierCreate( sModifierID, sManipFunID );
}


/*
-----------------------------
--- nodeXX misc functions ---
----------------------------- */
int	nodeLevel ()
{
    return curMiner()->nodeLevel();
}

std::string nodeXPath()
{
    return curMiner()->nodeXPath();
}

/*
------------------------------
--- nodeValuePos functions ---
------------------------------ */
/**
Get the value of the node at given dom position.
The value extracted from the dom position can optionally be filtered through \a sModifierID + parameters.
\return Value of current node possibly filtered through \a sModifierID + parameters.
*/
std::string	nodeValuePos (
     int iDomPos
    ,const std::string& sModifierID								///< [in] String manipulation function/ to apply to value before writing out.
    ,const std::string& sManipParam1							///< [in] Parameter 1 to modifier function.
    ,const std::string& sManipParam2 							///< [in] Parameter 2 to modifier function.
    ,const std::string& sManipParam3							///< [in] Parameter 3 to modifier function.
    ,const std::string& /* sManipParam4 reserved */				///< [in] Parameter 4 to modifier function.
)
{
    return curMiner()->nodeValuePos( iDomPos, sModifierID, sManipParam1, sManipParam2, sManipParam3 );
}

/** Get the value of the node at given dom position.
The value extracted from the dom position can optionally be filtered through \a sModifierID + parameters.
\return Value of current node possibly filtered through \a sModifierID + parameters. */
std::string	nodeValuePos (
     int iDomPos
    ,const std::string& sModifierID									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    ,const std::string& sManipParam1								///< [in] Parameter 1 to modifier function.
    ,const std::string& sManipParam2 								///< [in] Parameter 2 to modifier function.
    ,const std::string& sManipParam3								///< [in] Parameter 3 to modifier function.
)
{
    return curMiner()->nodeValuePos( iDomPos, sModifierID, sManipParam1, sManipParam2, sManipParam3 );
}

/** Get the value of the node at given dom position.
The value extracted from the dom position can optionally be filtered through \a sModifierID + parameters.
\return Value of current node possibly filtered through \a sModifierID + parameters. */
std::string	nodeValuePos (
     int iDomPos
    ,const std::string& sModifierID									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    ,const std::string& sManipParam1								///< [in] Parameter 1 to modifier function.
    ,const std::string& sManipParam2 								///< [in] Parameter 2 to modifier function.
)
{
    return curMiner()->nodeValuePos( iDomPos, sModifierID, sManipParam1, sManipParam2 );
}

/** Get the value of the node at given dom position.
The value extracted from the dom position can optionally be filtered through \a sModifierID + parameter.
\return Value of current node possibly filtered through \a sModifierID + parameter. */
std::string	nodeValuePos (
     int iDomPos
    ,const std::string& sModifierID									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    ,const std::string& sManipParam1								///< [in] Parameter 1 to modifier function.
)
{
    return curMiner()->nodeValuePos( iDomPos, sModifierID, sManipParam1 );
}

/** Get the value of the node at given dom position.
The value extracted from the dom position can optionally be filtered through \a sModifierID + parameters.
\return Value of current node possibly filtered through \a sModifierID + parameters. */
std::string	nodeValuePos (
     int iDomPos
    ,const std::string& sModifierID									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
)
{
    return curMiner()->nodeValuePos( iDomPos, sModifierID );
}

/** Get the value of the node at given dom position.
The value extracted from the dom position is filtered through trimDefault.
\return Value of current node filtered through trimDefault. */
std::string	nodeValuePos (
     int iDomPos
)
{
    return curMiner()->nodeValuePos( iDomPos );
}


std::string posValue(int iDomPos, const std::string &sModifierID, const std::string &sManipParam1,
                     const std::string &sManipParam2, const std::string &sManipParam3,
                     const std::string &sManipParam4)
{
    return curMiner()->posValue( iDomPos, sModifierID, sManipParam1, sManipParam2, sManipParam3, sManipParam4 );
}

std::string posValue(int iDomPos, const std::string &sModifierID, const std::string &sManipParam1,
                     const std::string &sManipParam2, const std::string &sManipParam3)
{
    return curMiner()->posValue( iDomPos, sModifierID, sManipParam1, sManipParam2, sManipParam3);
}

std::string posValue(int iDomPos, const std::string &sModifierID, const std::string &sManipParam1,
                     const std::string &sManipParam2)
{
    return curMiner()->posValue( iDomPos, sModifierID, sManipParam1, sManipParam2);
}

std::string posValue(int iDomPos, const std::string &sModifierID, const std::string &sManipParam1)
{
    return curMiner()->posValue( iDomPos, sModifierID, sManipParam1);
}

std::string posValue(int iDomPos, const std::string &sModifierID)
{
    return curMiner()->posValue( iDomPos, sModifierID );
}

std::string posValue(int iDomPos)
{
    return curMiner()->posValue( iDomPos );
}


/*
---------------------------
--- nodeValue functions ---
--------------------------- */
/** Get the value of the node at current dom position.
The value extracted from current node position can optionally be filtered through \a sModifierID + parameters.
\return Value of current node possibly filtered through \a sModifierID + parameters. */
std::string	nodeValue (
     const std::string& sModifierID									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    ,const std::string& sManipParam1								///< [in] Parameter 1 to modifier function.
    ,const std::string& sManipParam2 								///< [in] Parameter 2 to modifier function.
    ,const std::string& sManipParam3								///< [in] Parameter 3 to modifier function.
    ,const std::string& /* sManipParam4 reserved */					///< [in] Parameter 4 to modifier function.
)
{
    return curMiner()->nodeValue( sModifierID, sManipParam1, sManipParam2, sManipParam3 );
}

/**
Get the value of the node at current dom position.
The value extracted from current node position can optionally be filtered through \a sModifierID + parameters.
\return Value of current node possibly filtered through \a sModifierID + parameters. */
std::string	nodeValue (
     const std::string& sModifierID									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    ,const std::string& sManipParam1								///< [in] Parameter 1 to modifier function.
    ,const std::string& sManipParam2 								///< [in] Parameter 2 to modifier function.
    ,const std::string& sManipParam3								///< [in] Parameter 3 to modifier function.
)
{
    return curMiner()->nodeValue( sModifierID, sManipParam1, sManipParam2, sManipParam3 );
}


/** Get the value of the node at current dom position.
The value extracted from current node position can optionally be filtered through \a sModifierID + parameters.
\return Value of current node possibly filtered through \a sModifierID + parameters. */
std::string	nodeValue (
     const std::string& sModifierID									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    ,const std::string& sManipParam1								///< [in] Parameter 1 to modifier function.
    ,const std::string& sManipParam2 								///< [in] Parameter 2 to modifier function.
)
{
    return curMiner()->nodeValue( sModifierID, sManipParam1, sManipParam2 );
}

/** Get the value of the node at current dom position.
The value extracted from current node position can optionally be filtered through \a sModifierID + parameter.
\return Value of current node possibly filtered through \a sModifierID + parameter. */
std::string	nodeValue (
     const std::string& sModifierID									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    ,const std::string& sManipParam1								///< [in] Parameter 1 to modifier function.
)
{
    return curMiner()->nodeValue( sModifierID, sManipParam1 );
}

/** Get the value of the node at current dom position.
The value extracted from current node position can optionally be filtered through \a sModifierID.
\return Value of current node possibly filtered through \a sModifierID. */
std::string	nodeValue (
     const std::string& sModifierID									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
)
{
    return curMiner()->nodeValue( sModifierID );
}

/** Get the value of the node at current dom position.
The value extracted from current node position filtered through trimDefault.
\return Value of current node filtered through trimDefault. */
std::string	nodeValue (
)
{
    return curMiner()->nodeValue();
}

/*
---------------------------------
--- nodeValueParent functions ---
--------------------------------- */
/** Get the value of the parent node \a iLevelsUp from the current dom position.
The value extracted from parent node position can optionally be filtered through \a sModifierID + parameters.
\return Value of parent node \a iLevelsUp possibly filtered through \a sModifierID + parameters. */
std::string	nodeValueParent (
     int iLevelsUp 													///< [in] Stop at parent number iLevelsUp (ONLY positive numbers).
    ,const std::string& sModifierID									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    ,const std::string& sManipParam1								///< [in] Parameter 1 to modifier function.
    ,const std::string& sManipParam2 								///< [in] Parameter 2 to modifier function.
    ,const std::string& sManipParam3								///< [in] Parameter 3 to modifier function.
    ,const std::string& /* sManipParam4 reserved */					///< [in] Parameter 4 to modifier function.
)
{
    return curMiner()->nodeValueParent( iLevelsUp, sModifierID, sManipParam1, sManipParam2, sManipParam3 );
}

/**
Get the value of the parent node \a iLevelsUp from the current dom position.
The value extracted from parent node position can optionally be filtered through \a sModifierID + parameters.
\return Value of parent node \a iLevelsUp possibly filtered through \a sModifierID + parameters. */
std::string	nodeValueParent (
     int iLevelsUp 													///< [in] Stop at parent number iLevelsUp (ONLY positive numbers).
    ,const std::string& sModifierID									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    ,const std::string& sManipParam1								///< [in] Parameter 1 to modifier function.
    ,const std::string& sManipParam2 								///< [in] Parameter 2 to modifier function.
    ,const std::string& sManipParam3								///< [in] Parameter 3 to modifier function.
)
{
    return curMiner()->nodeValueParent( iLevelsUp, sModifierID, sManipParam1, sManipParam2, sManipParam3 );
}

/** Get the value of the parent node \a iLevelsUp from the current dom position.
The value extracted from parent node position can optionally be filtered through \a sModifierID + parameters.
\return Value of parent node \a iLevelsUp possibly filtered through \a sModifierID + parameters. */
std::string	nodeValueParent (
     int iLevelsUp 													///< [in] Stop at parent number iLevelsUp (ONLY positive numbers).
    ,const std::string& sModifierID									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    ,const std::string& sManipParam1								///< [in] Parameter 1 to modifier function.
    ,const std::string& sManipParam2 								///< [in] Parameter 2 to modifier function.
)
{
    return curMiner()->nodeValueParent( iLevelsUp, sModifierID, sManipParam1, sManipParam2 );
}

/** Get the value of the parent node \a iLevelsUp from the current dom position.
The value extracted from parent node position can optionally be filtered through \a sModifierID + parameter.
\return Value of parent node \a iLevelsUp possibly filtered through \a sModifierID + parameter. */
std::string	nodeValueParent (
     int iLevelsUp 													///< [in] Stop at parent number iLevelsUp (ONLY positive numbers).
    ,const std::string& sModifierID									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    ,const std::string& sManipParam1								///< [in] Parameter 1 to modifier function.
)
{
    return curMiner()->nodeValueParent( iLevelsUp, sModifierID, sManipParam1 );
}

/** Get the value of the parent node \a iLevelsUp from the current dom position.
The value extracted from parent node position can optionally be filtered through \a sModifierID.
\return Value of parent node \a iLevelsUp possibly filtered through \a sModifierID. */
std::string	nodeValueParent (
     int iLevelsUp 													///< [in] Stop at parent number iLevelsUp (ONLY positive numbers).
    ,const std::string& sModifierID									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
)
{
    return curMiner()->nodeValueParent( iLevelsUp, sModifierID );
}

/** Get the value of the parent node \a iLevelsUp from the current dom position.
The value extracted from parent node position is filtered through trimDefault.
\return Value of parent node \a iLevelsUp filtered through trimDefault. */
std::string	nodeValueParent (
     int iLevelsUp 													///< [in] Stop at parent number iLevelsUp (ONLY positive numbers).
)
{
    return curMiner()->nodeValueParent( iLevelsUp );
}



/*
---------------------------------
--- nodeAttribute functions ---
--------------------------------- */
std::string	nodeAttribute (
      const std::string& sAttribute 					///< [in] Attribute name to get the value for.
    , const std::string& sModifierID					///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    , const std::string& sManipParam1					///< [in] Parameter 1 to modifier function.
    , const std::string& sManipParam2 					///< [in] Parameter 2 to modifier function.
    , const std::string& sManipParam3					///< [in] Parameter 3 to modifier function.
    , const std::string& /* sManipParam4 reserved */	///< [in] Parameter 4 to modifier function.
)
{
    return curMiner()->nodeAttribute( sAttribute, sModifierID, sManipParam1, sManipParam2, sManipParam3, "" );
}

std::string	nodeAttribute (
      const std::string& sAttribute 								///< [in] Attribute name to get the value for.
    , const std::string& sModifierID								///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    , const std::string& sManipParam1								///< [in] Parameter 1 to modifier function.
    , const std::string& sManipParam2 								///< [in] Parameter 2 to modifier function.
    , const std::string& sManipParam3								///< [in] Parameter 3 to modifier function.
)
{
    return curMiner()->nodeAttribute( sAttribute, sModifierID, sManipParam1, sManipParam2, sManipParam3 );
}

std::string	nodeAttribute (
      const std::string& sAttribute 								///< [in] Attribute name to get the value for.
    , const std::string& sModifierID								///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    , const std::string& sManipParam1								///< [in] Parameter 1 to modifier function.
    , const std::string& sManipParam2 								///< [in] Parameter 2 to modifier function.
)
{
    return curMiner()->nodeAttribute( sAttribute, sModifierID, sManipParam1, sManipParam2 );
}

std::string	nodeAttribute (
      const std::string& sAttribute 								///< [in] Attribute name to get the value for.
    , const std::string& sModifierID								///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    , const std::string& sManipParam1								///< [in] Parameter 1 to modifier function.
)
{
    return curMiner()->nodeAttribute( sAttribute, sModifierID, sManipParam1 );
}

std::string	nodeAttribute (
      const std::string& sAttribute 								///< [in] Attribute name to get the value for.
    , const std::string& sModifierID								///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
)
{
    return curMiner()->nodeAttribute( sAttribute, sModifierID );
}

std::string	nodeAttribute (
     const std::string& sAttribute 									///< [in] Attribute name to get the value for.
)
{
    return curMiner()->nodeAttribute( sAttribute );
}

std::string posAttribute(int iDomPos, const std::string &sAttribute, const std::string &sModifierID,
                         const std::string &sManipParam1, const std::string &sManipParam2,
                         const std::string &sManipParam3, const std::string &sManipParam4)
{
    return curMiner()->posAttribute( iDomPos, sAttribute, sModifierID, sManipParam1, sManipParam2, sManipParam3, sManipParam4 );
}

std::string posAttribute(int iDomPos, const std::string &sAttribute, const std::string &sModifierID,
                         const std::string &sManipParam1, const std::string &sManipParam2,
                         const std::string &sManipParam3)
{
    return curMiner()->posAttribute( iDomPos, sAttribute, sModifierID, sManipParam1, sManipParam2, sManipParam3 );
}

std::string posAttribute(int iDomPos, const std::string &sAttribute, const std::string &sModifierID,
                         const std::string &sManipParam1, const std::string &sManipParam2)
{
    return curMiner()->posAttribute( iDomPos, sAttribute, sModifierID, sManipParam1, sManipParam2 );
}

std::string posAttribute(int iDomPos, const std::string &sAttribute, const std::string &sModifierID,
                         const std::string &sManipParam1)
{
    return curMiner()->posAttribute( iDomPos, sAttribute, sModifierID, sManipParam1 );
}

std::string posAttribute(int iDomPos, const std::string &sAttribute, const std::string &sModifierID)
{
    return curMiner()->posAttribute( iDomPos, sAttribute, sModifierID );
}

std::string posAttribute(int iDomPos, const std::string &sAttribute)
{
    return curMiner()->posAttribute( iDomPos, sAttribute );
}

/*
---------------------------------
--- nodeText functions ---
--------------------------------- */
std::string	nodeText (
      const std::string& sModifierID								///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    , const std::string& sManipParam1								///< [in] Parameter 1 to modifier function.
    , const std::string& sManipParam2 								///< [in] Parameter 2 to modifier function.
    , const std::string& sManipParam3								///< [in] Parameter 3 to modifier function.
    , const std::string& /* sManipParam4 reserved */					///< [in] Parameter 4 to modifier function.
)
{
    return curMiner()->nodeText( sModifierID, sManipParam1, sManipParam2, sManipParam3, "" );
}

std::string	nodeText (
      const std::string& sModifierID								///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    , const std::string& sManipParam1								///< [in] Parameter 1 to modifier function.
    , const std::string& sManipParam2 								///< [in] Parameter 2 to modifier function.
    , const std::string& sManipParam3								///< [in] Parameter 3 to modifier function.
)
{
    return curMiner()->nodeText( sModifierID, sManipParam1, sManipParam2, sManipParam3 );
}


/** Get the text of the node at current dom position.
The text extracted from current node position can optionally be filtered through \a sModifierID + parameters.
\return curMiner()->Text of current node possibly filtered through \a sModifierID + parameters. */
std::string	nodeText (
      const std::string& sModifierID								///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    , const std::string& sManipParam1								///< [in] Parameter 1 to modifier function.
    , const std::string& sManipParam2 								///< [in] Parameter 2 to modifier function.
)
{
    return curMiner()->nodeText( sModifierID, sManipParam1, sManipParam2 );
}

/** Get the text of the node at current dom position.
The text extracted from current node position can optionally be filtered through \a sModifierID + parameter.
\return curMiner()->Text of current node possibly filtered through \a sModifierID + parameter. */
std::string	nodeText (
      const std::string& sModifierID								///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    , const std::string& sManipParam1								///< [in] Parameter 1 to modifier function.
)
{
    return curMiner()->nodeText( sModifierID, sManipParam1 );
}

/** Get the text of the node at current dom position.
The text extracted from current node position can optionally be filtered through \a sModifierID.
\return curMiner()->Text of current node possibly filtered through \a sModifierID. */
std::string	nodeText (
     const std::string& sModifierID									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
)
{
    return curMiner()->nodeText( sModifierID );
}

/** Get the text of the node at current dom position.
The text extracted from current node position filtered through trimDefault.
\return curMiner()->Text of current node filtered through trimDefault. */
std::string	nodeText (
)
{
    return curMiner()->nodeText();
}


/*
--------------------------------
--- nodeCompare functions ---
-------------------------------- */
/** Compare current node value (node value of current dom position) with a pattern.
The value extracted from current node position can optionally be filtered through \a sModifierID + parameters.
\return Boolean result of applying the compare function to current node value and the chosen pattern. */
bool	nodeCompare	(
     const std::string& sPattern 			///< [in] String pattern to compare against current value
    ,const std::string& sCompareFun			///< [in] Compare function to use.
    ,const std::string& sModifierID			///< [in] String manipulation function used to manipulate current value. Only built-ins supported.
    ,const std::string& sManipParam1		///< [in] Parameter 1 to modifier function.
    ,const std::string& sManipParam2 		///< [in] Parameter 2 to modifier function.
    ,const std::string& sManipParam3		///< [in] Parameter 3 to modifier function.
    ,const std::string& /* sManipParam4 reserved */					///< [in] Parameter 4 to modifier function.
    )
{
    return curMiner()->nodeCompare( sPattern, sCompareFun, sModifierID, sManipParam1, sManipParam2, sManipParam3 );
}


/** Compare current node value (node value of current dom position) with a pattern.
The value extracted from current node position can optionally be filtered through \a sModifierID + parameters.
\return Boolean result of applying the compare function to current node value and the chosen pattern. */
bool	nodeCompare	(
     const std::string& sPattern 			///< [in] String pattern to compare against current value
    ,const std::string& sCompareFun			///< [in] Compare function to use.
    ,const std::string& sModifierID			///< [in] String manipulation function used to manipulate current value. Only built-ins supported.
    ,const std::string& sManipParam1		///< [in] Parameter 1 to modifier function.
    ,const std::string& sManipParam2 		///< [in] Parameter 2 to modifier function.
    ,const std::string& sManipParam3		///< [in] Parameter 3 to modifier function.
    )
{
    return curMiner()->nodeCompare( sPattern, sCompareFun, sModifierID, sManipParam1, sManipParam2, sManipParam3 );
}

/** Compare current node value (node value of current dom position) with a pattern.
The value extracted from current node position can optionally be filtered through \a sModifierID + parameters.
\return Boolean result of applying the compare function to current node value and the chosen pattern. */
bool	nodeCompare	(
     const std::string& sPattern 			///< [in] String pattern to compare against current value
    ,const std::string& sCompareFun			///< [in] Compare function to use.
    ,const std::string& sModifierID			///< [in] String manipulation function used to manipulate current value. Only built-ins supported.
    ,const std::string& sManipParam1		///< [in] Parameter 1 to modifier function.
    ,const std::string& sManipParam2 		///< [in] Parameter 2 to modifier function.
    )
{
    return curMiner()->nodeCompare( sPattern, sCompareFun, sModifierID, sManipParam1, sManipParam2 );
}

/** Compare current node value (node value of current dom position) with a pattern.
The value extracted from current node position can optionally be filtered through \a sModifierID + parameters.
\return Boolean result of applying the compare function to current node value and the chosen pattern. */
bool	nodeCompare	(
     const std::string& sPattern 			///< [in] String pattern to compare against current value
    ,const std::string& sCompareFun			///< [in] Compare function to use.
    ,const std::string& sModifierID			///< [in] String manipulation function used to manipulate current value. Only built-ins supported.
    ,const std::string& sManipParam1		///< [in] Parameter 1 to modifier function.
    )
{
    return curMiner()->nodeCompare( sPattern, sCompareFun, sModifierID, sManipParam1 );
}

/** Compare current node value (node value of current dom position) with a pattern.
The value extracted from current node position can optionally be filtered through \a sModifierID + parameter.
\return Boolean result of applying the compare function to current node value and the chosen pattern. */
bool	nodeCompare	(
     const std::string& sPattern 			///< [in] String pattern to compare against current value
    ,const std::string& sCompareFun			///< [in] Compare function to use.
    ,const std::string& sModifierID			///< [in] String manipulation function used to manipulate current value. Only built-ins supported.
    )
{
    return curMiner()->nodeCompare( sPattern, sCompareFun, sModifierID );
}

/** Compare current node value (node value of current dom position) with a pattern.
The value extracted from current node position is filtered through trimDefault.
\return Boolean result of applying the compare function to current node value and the chosen pattern. */
bool	nodeCompare	(
     const std::string& sPattern 			///< [in] String pattern to compare against current value
    ,const std::string& sCompareFun			///< [in] Compare function to use.
    )
{
    return curMiner()->nodeCompare( sPattern, sCompareFun );
}

/*
-----------------------
--- Parse functions ---
----------------------- */

bool parseRegex (
    int iCount,
    const std::string& sRegex,
    int postMarkerPos )
{
    return curMiner()->parseRegex( iCount, sRegex, postMarkerPos );
}

bool iparseRegex (
    int iCount,
    const std::string& sRegex,
    int postMarkerPos )
{
    return curMiner()->iparseRegex( iCount, sRegex, postMarkerPos );
}

bool parseToRegex (
    int iCount,
    const std::string& sRegex,
    int postMarkerPos )
{
    return curMiner()->parseToRegex( iCount, sRegex, postMarkerPos );
}

bool iparseToRegex (
    int iCount,
    const std::string& sRegex,
    int postMarkerPos )
{
    return curMiner()->iparseToRegex( iCount, sRegex, postMarkerPos );
}

bool parseToString (
    int iCount,
    const std::string& sSubstring,
    int postMarkerPos )
{
    return curMiner()->parseToString( iCount, sSubstring, postMarkerPos );
}

bool iparseToString (
    int iCount,
    const std::string& sSubstring,
    int postMarkerPos )
{
    return curMiner()->iparseToString( iCount, sSubstring, postMarkerPos );
}

bool parseToEnd ()
{
    return curMiner()->parseToEnd();
}

std::string	getParseMatch (
    int iMatchNumber
)
{
    return curMiner()->getParseMatch(iMatchNumber);
}

std::string	getParseRest ()
{
    return curMiner()->getParseRest();
}

int	getParseMatchCount ()
{
    return curMiner()->getParseMatchCount();
}


/*
------------------------
--- Text functions ---
------------------------ */
void textNewSearch	()
{
    curMiner()->textNewSearch();
}

bool findBegin(
    int iCount, 					///< [in] Stop at match number.
    const std::string& sSearchFor,	///< [in] Substring to search for.
    int setBeginToPos 			)	///< [in] Update 'Begin' marker to first or last position in match.
{
    return curMiner()->findBegin( iCount, sSearchFor, setBeginToPos );
}

bool findEnd		(
    int iCount, 					///< [in] Stop at match number.
    const std::string& sSearchFor,	///< [in] Substring to search for.
    int setEndToPos 			)	///< [in] Update 'End' marker to first or last position in match.
{
    return curMiner()->findEnd( iCount, sSearchFor, setEndToPos );
}

bool findBeginNext	(
    int iCount, 					///< [in] Stop at match number.
    const std::string& sSearchFor,	///< [in] Substring to search for.
    int setBeginToPos 			)	///< [in] Update 'Begin' marker to first or last position in match.
{
    return curMiner()->findBeginNext( iCount, sSearchFor, setBeginToPos );
}

bool findEndNext		(
    int iCount, 					///< [in] Stop at match number.
    const std::string& sSearchFor,	///< [in] Substring to search for.
    int setEndToPos 			)	///< [in] Update 'End' marker to first or last position in match.
{
    return curMiner()->findEndNext( iCount, sSearchFor, setEndToPos );
}

bool ifindBegin	(
    int iCount, 					///< [in] Stop at match number.
    const std::string& sSearchFor,	///< [in] Substring to search for.
    int setBeginToPos 			)	///< [in] Update 'Begin' marker to first or last position in match.
{
    return curMiner()->ifindBegin( iCount, sSearchFor, setBeginToPos );
}

bool ifindEnd		(
    int iCount, 					///< [in] Stop at match number.
    const std::string& sSearchFor,	///< [in] Substring to search for.
    int setEndToPos 			)	///< [in] Update 'End' marker to first or last position in match.
{
    return curMiner()->ifindEnd( iCount, sSearchFor, setEndToPos );
}

bool ifindBeginNext	(
    int iCount, 					///< [in] Stop at match number.
    const std::string& sSearchFor,	///< [in] Substring to search for.
    int setBeginToPos 			)	///< [in] Update 'Begin' marker to first or last position in match.
{
    return curMiner()->ifindBeginNext( iCount, sSearchFor, setBeginToPos );
}

bool ifindEndNext		(
    int iCount, 					///< [in] Stop at match number.
    const std::string& sSearchFor,	///< [in] Substring to search for.
    int setEndToPos 			)	///< [in] Update 'End' marker to first or last position in match.
{
    return curMiner()->ifindEndNext( iCount, sSearchFor, setEndToPos );
}


bool findRegexBegin	(
    int iCount, 					///< [in] Stop at match number.
    const std::string& sRegex,		///< [in] Regular expression to use.
    int setBeginToPos 			)	///< [in] Update 'Begin' marker to first or last position in match.
{
    return curMiner()->findRegexBegin( iCount, sRegex, setBeginToPos );
}

bool findRegexEnd		(
    int iCount, 					///< [in] Stop at match number.
    const std::string& sRegex,		///< [in] Regular expression to use.
    int setEndToPos 			)	///< [in] Update 'End' marker to first or last position in match.
{
    return curMiner()->findRegexEnd( iCount, sRegex, setEndToPos );
}

bool findRegexBeginNext	(
    int iCount, 					///< [in] Stop at match number.
    const std::string& sRegex,		///< [in] Regular expression to use.
    int setBeginToPos 			)	///< [in] Update 'Begin' marker to first or last position in match.
{
    return curMiner()->findRegexBeginNext( iCount, sRegex, setBeginToPos );
}

bool findRegexEndNext	(
    int iCount, 					///< [in] Stop at match number.
    const std::string& sRegex,		///< [in] Regular expression to use.
    int setEndToPos 		)		///< [in] Update 'End' marker to first or last position in match.
{
    return curMiner()->findRegexEndNext( iCount, sRegex, setEndToPos );
}


bool stepBegin		(
    int iCount 	)				///< [in] Number of chars to step.
{
    return curMiner()->stepBegin( iCount );
}


bool stepEnd		(
    int iCount 	)				///< [in] Number of chars to step.
{
    return curMiner()->stepEnd( iCount );
}

/*
-----------------------------
--- (URL) queue functions ---
----------------------------- */
/** Get size of urlQueue. */
int urlQueueSize		()
{
    return curMiner()->urlQueueSize();
}

/** Get size of already processed urls. */
int	urlQueueSizeProcessed()
{
    return curMiner()->urlQueueSizeProcessed();
}

/** Test an url to see if it has been processed already */
bool urlQueueAlreadyProcessed( const std::string& sUrl )
{
    return curMiner()->urlQueueAlreadyProcessed(sUrl);
}

/** Clear urlQueue. */
void	urlQueueClear	()
{
    curMiner()->urlQueueClear();
}

/** Get front (URL) of urlQueue. */
std::string urlQueueFront	()
{
    return curMiner()->urlQueueFront();
}

/** Append urls to queue, allow duplicates. */
void	urlQueueAppend (
     int iLinkType 						///< [in] Link type, one of: LINK_TYPE_LOCAL, LINK_TYPE_EXTERNAL, LINK_TYPE_ALL
    ,const std::string& sUrlsMatch 		///< [in] String to match each url against using the compare operator
    ,const std::string& sCompareFun		///< [in] Compare function to use.
)
{
    curMiner()->urlQueueAppend( iLinkType, sUrlsMatch, sCompareFun );
}


/** Append urls to queue, allow no duplicates allowed. */
void	urlQueueAppendUnique (
     int iLinkType 						///< [in] Link type, one of: LINK_TYPE_LOCAL, LINK_TYPE_EXTERNAL, LINK_TYPE_ALL
    ,const std::string& sUrlsMatch 		///< [in] String to match each url against using the compare operator
    ,const std::string& sCompareFun		///< [in] Compare function to use.
)
{
    curMiner()->urlQueueAppendUnique( iLinkType, sUrlsMatch, sCompareFun );
}

void	urlQueueAppend (
    const std::string& sUrl 		///< [in] Urls to append.
)
{
    curMiner()->urlQueueAppend( sUrl );
}

void	urlQueueAppendUnique (
    const std::string& sUrl 		///< [in] Urls to append.
)
{
    curMiner()->urlQueueAppendUnique( sUrl );
}

void	urlQueuePrepend (
    const std::string& sUrl 		///< [in] Urls to prepend.
)
{
    curMiner()->urlQueuePrepend( sUrl );
}

void	urlQueuePrependUnique (
    const std::string& sUrl 		///< [in] Urls to prepend.
)
{
    curMiner()->urlQueuePrependUnique( sUrl );
}


// ----------------------------------------------------
// --- INLINE Implementation: linksGetter functions ---
// ----------------------------------------------------
/** Debug printing of links calculated by the links getter. Use after a call to
urlQueueAppendUnique() or urlQueueAppend(). */
void linksGetterDebugPrint	()
{
    curMiner()->linksGetterDebugPrint();
}



// --------------------------
// --- valueSet functions ---
// --------------------------
void	valueSet (
    const std::string& sValue )

{
    curMiner()->valueSet( sValue );
}

// --------------------------
// --- valueGet functions ---
// --------------------------

/**
Get current value.
The string manipulation function can be the name of one of the built-ins like
'append', 'eraseAll' etc. By default the value is filtered through the trimDefault function
which trims spaces away from both end of the output string value. If you don't want this
trimming you should use 'raw' as your manipulation function, which takes no extra parameters.

!User defined PHP manipulation function
You can also supply a user defined PHP function name as the string manipulation function, which if
found, will take precedence. The function will be called with the value you're writing as first parameter
and any manipulation parameters as the following arguments. If you don't need all the arguments you do
not need to declare them in your PHP funcion as they will just be silently ignored.
You must remeber to return the modified value from your function.

\return Current value filtered though the function specified. */
std::string	valueGet (
     const std::string& sModifierID									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    ,const std::string& sManipParam1								///< [in] Parameter 1 to modifier function.
    ,const std::string& sManipParam2 								///< [in] Parameter 2 to modifier function.
    ,const std::string& sManipParam3								///< [in] Parameter 3 to modifier function.
    ,const std::string& /* sManipParam4 reserved */					///< [in] Parameter 4 to modifier function.
)
{
    return curMiner()->valueGet ( sModifierID, sManipParam1, sManipParam2, sManipParam3 );
}

std::string	valueGet (
     const std::string& sModifierID									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    ,const std::string& sManipParam1								///< [in] Parameter 1 to modifier function.
    ,const std::string& sManipParam2 								///< [in] Parameter 2 to modifier function.
    ,const std::string& sManipParam3								///< [in] Parameter 3 to modifier function.
)
{
    return curMiner()->valueGet ( sModifierID, sManipParam1, sManipParam2, sManipParam3 );
}

std::string	valueGet (
     const std::string& sModifierID									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    ,const std::string& sManipParam1								///< [in] Parameter 1 to modifier function.
    ,const std::string& sManipParam2 								///< [in] Parameter 2 to modifier function.
)
{
    return curMiner()->valueGet ( sModifierID, sManipParam1, sManipParam2 );
}

std::string	valueGet (
     const std::string& sModifierID									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    ,const std::string& sManipParam1								///< [in] Parameter 1 to modifier function.
)
{
    return curMiner()->valueGet ( sModifierID, sManipParam1 );
}

std::string	valueGet (
     const std::string& sModifierID									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
)
{
    return curMiner()->valueGet ( sModifierID );
}

std::string	valueGet ()
{
    return curMiner()->valueGet ();
}


// ------------------------------
// --- valueCompare functions ---
// ------------------------------

/**
\defgroup valueCompareFunctions Compare current value
@{

Compare current value with a pattern. */
bool	valueCompare	(
     const std::string& sPattern 			///< [in] String pattern to compare against current value
    ,const std::string& sCompareFun			///< [in] Compare function to use.
    ,const std::string& sModifierID			///< [in] String manipulation function used to manipulate current value. Only built-ins supported.
    ,const std::string& sManipParam1		///< [in] Parameter 1 to modifier function.
    ,const std::string& sManipParam2 		///< [in] Parameter 2 to modifier function.
    ,const std::string& sManipParam3		///< [in] Parameter 3 to modifier function.
    ,const std::string& /* sManipParam4 reserved */					///< [in] Parameter 4 to modifier function.
    )
{
    return curMiner()->valueCompare( sPattern, sCompareFun, sModifierID, sManipParam1, sManipParam2, sManipParam3 );
}

bool	valueCompare	(
     const std::string& sPattern 			///< [in] String pattern to compare against current value
    ,const std::string& sCompareFun			///< [in] Compare function to use.
    ,const std::string& sModifierID			///< [in] String manipulation function used to manipulate current value. Only built-ins supported.
    ,const std::string& sManipParam1		///< [in] Parameter 1 to modifier function.
    ,const std::string& sManipParam2 		///< [in] Parameter 2 to modifier function.
    ,const std::string& sManipParam3		///< [in] Parameter 3 to modifier function.
    )
{
    return curMiner()->valueCompare( sPattern, sCompareFun, sModifierID, sManipParam1, sManipParam2, sManipParam3 );
}

bool	valueCompare	(
     const std::string& sPattern 			///< [in] String pattern to compare against current value
    ,const std::string& sCompareFun			///< [in] Compare function to use.
    ,const std::string& sModifierID			///< [in] String manipulation function used to manipulate current value. Only built-ins supported.
    ,const std::string& sManipParam1		///< [in] Parameter 1 to modifier function.
    ,const std::string& sManipParam2 		///< [in] Parameter 2 to modifier function.
    )
{
    return curMiner()->valueCompare( sPattern, sCompareFun, sModifierID, sManipParam1, sManipParam2 );
}

bool	valueCompare	(
     const std::string& sPattern 			///< [in] String pattern to compare against current value
    ,const std::string& sCompareFun			///< [in] Compare function to use.
    ,const std::string& sModifierID			///< [in] String manipulation function used to manipulate current value. Only built-ins supported.
    ,const std::string& sManipParam1		///< [in] Parameter 1 to modifier function.
    )
{
    return curMiner()->valueCompare( sPattern, sCompareFun, sModifierID, sManipParam1 );
}

bool	valueCompare	(
     const std::string& sPattern 			///< [in] String pattern to compare against current value
    ,const std::string& sCompareFun			///< [in] Compare function to use.
    ,const std::string& sModifierID			///< [in] String manipulation function used to manipulate current value. Only built-ins supported.
    )
{
    return curMiner()->valueCompare( sPattern, sCompareFun, sModifierID );
}

bool	valueCompare	(
     const std::string& sPattern 			///< [in] String pattern to compare against current value
    ,const std::string& sCompareFun			///< [in] Compare function to use.
    )
{
    return curMiner()->valueCompare( sPattern, sCompareFun );
}

/**@}*/

// --------------------------------
// --- outputValueGet functions ---
// --------------------------------

/**
\defgroup outputValueGetFunctions Get output value
@{

 Get value of previously written output name/field.
*/
std::string	outputValueContextGet	(
     const std::string& sFieldName			///< [in] Name/fieldname of previously written value to retrieve.
    ,const std::string& sContextName		///< [in] XML level context (default is current context)
)
{
    return curMiner()->outputValueContextGet( sFieldName, sContextName );
}

std::string outputValueGet(const std::string& sFieldName, const std::string& sModifierID, const std::string& sManipParam1,
                                        const std::string& sManipParam2, const std::string& sManipParam3, const std::string& /* sManipParam4 reserved */)
{
    return curMiner()->outputValueGet(sFieldName, sModifierID, sManipParam1, sManipParam2, sManipParam3);
}

std::string outputValueGet(const std::string& sFieldName, const std::string& sModifierID, const std::string& sManipParam1,
                                        const std::string& sManipParam2, const std::string& sManipParam3)
{
    return curMiner()->outputValueGet(sFieldName, sModifierID, sManipParam1, sManipParam2, sManipParam3);
}

std::string outputValueGet(const std::string& sFieldName, const std::string& sModifierID, const std::string& sManipParam1,
                                        const std::string& sManipParam2)
{
    return curMiner()->outputValueGet(sFieldName, sModifierID, sManipParam1, sManipParam2);
}

std::string outputValueGet(const std::string& sFieldName, const std::string& sModifierID, const std::string& sManipParam1)
{
    return curMiner()->outputValueGet(sFieldName, sModifierID, sManipParam1);
}

std::string outputValueGet(const std::string& sFieldName, const std::string& sModifierID)
{
    return curMiner()->outputValueGet(sFieldName, sModifierID);
}

std::string outputValueGet(const std::string& sFieldName)
{
    return curMiner()->outputValueGet(sFieldName);
}

/**@}*/

// ------------------------------
// --- Modify value functions ---
// ------------------------------
/**
\defgroup valueModifyFunctions Modify current value
@{

Direct manipulation of current value with.
The string manipulation function can be the name of one of the built-ins like
'append', 'eraseAll' etc.

!User defined PHP manipulation function
You can also supply a user defined PHP function name as the string manipulation function, which if
found, will take precedence. The function will be called with the current value as first parameter
and any manipulation parameters as the following arguments. If you don't need all the arguments you do
not need to declare them in your PHP funcion as they will just be silently ignored.
You should return the manipulated value from your PHP function.

\note No default trimming is made here like in outputXX functions and in valueGet().
\return New value of current value.
*/
std::string		valueModify(
     const std::string& sModifierID									///< [in] String manipulation function used to manipulate current value.
    ,const std::string& sManipParam1								///< [in] Parameter 1 to modifier function.
    ,const std::string& sManipParam2 								///< [in] Parameter 2 to modifier function.
    ,const std::string& sManipParam3								///< [in] Parameter 3 to modifier function.
    ,const std::string& /* sManipParam4 reserved */					///< [in] Parameter 4 to modifier function.
    )
{
    return curMiner()->valueModify( sModifierID, sManipParam1, sManipParam2, sManipParam3 );
}

std::string		valueModify(
     const std::string& sModifierID									///< [in] String manipulation function used to manipulate current value.
    ,const std::string& sManipParam1								///< [in] Parameter 1 to modifier function.
    ,const std::string& sManipParam2 								///< [in] Parameter 2 to modifier function.
    ,const std::string& sManipParam3								///< [in] Parameter 3 to modifier function.
    )
{
    return curMiner()->valueModify( sModifierID, sManipParam1, sManipParam2, sManipParam3 );
}

std::string		valueModify(
     const std::string& sModifierID									///< [in] String manipulation function used to manipulate current value.
    ,const std::string& sManipParam1								///< [in] Parameter 1 to modifier function.
    ,const std::string& sManipParam2 								///< [in] Parameter 2 to modifier function.
    )
{
    return curMiner()->valueModify( sModifierID, sManipParam1, sManipParam2 );
}

std::string		valueModify(
     const std::string& sModifierID									///< [in] String manipulation function used to manipulate current value.
    ,const std::string& sManipParam1								///< [in] Parameter 1 to modifier function.
    )
{
    return curMiner()->valueModify( sModifierID, sManipParam1 );
}

std::string		valueModify(
     const std::string& sModifierID									///< [in] String manipulation function used to manipulate current value.
    )
{
    return curMiner()->valueModify( sModifierID );
}

/**@}*/

// --------------------------------------
// --- NEW outputDirectUnit functions ---
// --------------------------------------

/**
Direct output of value with unit to the output (eg. XML file).
The string manipulation function can be the name of one of the built-ins like
'append', 'eraseAll' etc. By default the value is filtered through the trimDefault function
which trims spaces away from both end of the output string value. If you don't want this
trimming you should use 'raw' as your manipulation function, which takes no extra parameters.

!User defined PHP manipulation function
You can also supply a user defined PHP function name as the string manipulation function, which if
found, will take precedence. The function will be called with the value you're writing as first parameter
and any manipulation parameters as the following arguments. If you don't need all the arguments you do
not need to declare them in your PHP funcion as they will just be silently ignored.

!Return value from user PHP manipulation function.
You have two options:
-# You return the manipulated value, which is then filtered though 'trimDefault' and written to
   the output using the \a sFieldName and \a sUnit. In cas you do not want the 'trimDefault' you have
   to name you user defined function so that the string 'raw' is part of the name somehow.
-# You return an empty string from your user function (or simply omit the return statement) in which
   case nothing is written to the output. You are then asumed to have taken care of this directly in your
   PHP function by calling another output function directly.
*/
void		outputDirectUnit(
     const std::string& sFieldName 									///< [in] Data field name
    ,const std::string& sValue 										///< [in] Value of field
    ,const std::string& sUnit 										///< [in] Unit of field
    ,const std::string& sModifierID									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    ,const std::string& sManipParam1								///< [in] Parameter 1 to modifier function.
    ,const std::string& sManipParam2 								///< [in] Parameter 2 to modifier function.
    ,const std::string& sManipParam3								///< [in] Parameter 3 to modifier function.
    ,const std::string& /* sManipParam4 reserved */					///< [in] Parameter 4 to modifier function.
    )
{
    curMiner()->outputDirectUnit( sFieldName, sValue, sUnit, sModifierID, sManipParam1, sManipParam2, sManipParam3 );
}



void		outputDirectUnit(
    const std::string& sFieldName, 									///< [in] Data field name
    const std::string& sValue, 										///< [in] Value of field
    const std::string& sUnit, 										///< [in] Unit of field
    const std::string& sModifierID,									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    const std::string& sManipParam1,								///< [in] Parameter 1 to modifier function.
    const std::string& sManipParam2, 								///< [in] Parameter 2 to modifier function.
    const std::string& sManipParam3									///< [in] Parameter 3 to modifier function.
    )
{
    curMiner()->outputDirectUnit( sFieldName, sValue, sUnit, sModifierID, sManipParam1, sManipParam2, sManipParam3 );
}

void		outputDirectUnit(
    const std::string& sFieldName, 									///< [in] Data field name
    const std::string& sValue, 										///< [in] Value of field
    const std::string& sUnit, 										///< [in] Unit of field
    const std::string& sModifierID,									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    const std::string& sManipParam1,								///< [in] Parameter 1 to modifier function.
    const std::string& sManipParam2 								///< [in] Parameter 2 to modifier function.
    )
{
    curMiner()->outputDirectUnit( sFieldName, sValue, sUnit, sModifierID, sManipParam1, sManipParam2 );
}

void		outputDirectUnit(
    const std::string& sFieldName, 									///< [in] Data field name
    const std::string& sValue, 										///< [in] Value of field
    const std::string& sUnit, 										///< [in] Unit of field
    const std::string& sModifierID,									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    const std::string& sManipParam1									///< [in] Parameter 1 to modifier function.
    )
{
    curMiner()->outputDirectUnit( sFieldName, sValue, sUnit, sModifierID, sManipParam1 );
}

void		outputDirectUnit(
    const std::string& sFieldName, 									///< [in] Data field name
    const std::string& sValue, 										///< [in] Value of field
    const std::string& sUnit, 										///< [in] Unit of field
    const std::string& sModifierID									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    )
{
    curMiner()->outputDirectUnit( sFieldName, sValue, sUnit, sModifierID );
}

void		outputDirectUnit(
    const std::string& sFieldName, 									///< [in] Data field name
    const std::string& sValue, 										///< [in] Value of field
    const std::string& sUnit 										///< [in] Unit of field
    )
{
    curMiner()->outputDirectUnit( sFieldName, sValue, sUnit );
}


// ----------------------------------
// --- NEW outputDirect functions ---
// ----------------------------------

/**
\defgroup outputDirectFunctions outputDirect functions
@{
Direct output of value to the output (eg. XML file).
The string manipulation function can be the name of one of the built-ins like
'append', 'eraseAll' etc. By default the value is filtered through the trimDefault function
which trims spaces away from both end of the output string value. If you don't want this
trimming you should use 'raw' as your manipulation function, which takes no extra parameters.

!User defined PHP manipulation function
You can also supply a user defined PHP function name as the string manipulation function, which if
found, will take precedence. The function will be called with the value you're writing as first parameter
and any manipulation parameters as the following arguments. If you don't need all the arguments you do
not need to declare them in your PHP funcion as they will just be silently ignored.

!Return value from user PHP manipulation function.
You have two options:
-# You return the manipulated value, which is then filtered though 'trimDefault' and written to
   the output using the \a sFieldName and \a sUnit. In cas you do not want the 'trimDefault' you have
   to name you user defined function so that the string 'raw' is part of the name somehow.
-# You return an empty string from your user function (or simply omit the return statement) in which
   case nothing is written to the output. You are then asumed to have taken care of this directly in your
   PHP function by calling another output function directly.
*/
void		outputDirect(
    const std::string& sFieldName, 									///< [in] Data field name
    const std::string& sValue, 										///< [in] Value of field
    const std::string& sModifierID,									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    const std::string& sManipParam1,								///< [in] Parameter 1 to modifier function.
    const std::string& sManipParam2, 								///< [in] Parameter 2 to modifier function.
    const std::string& sManipParam3,								///< [in] Parameter 3 to modifier function.
    const std::string& /* sManipParam4 reserved */					///< [in] Parameter 4 to modifier function.
    )
{
    curMiner()->outputDirect( sFieldName, sValue, sModifierID, sManipParam1, sManipParam2, sManipParam3 );
}

void		outputDirect(
    const std::string& sFieldName, 									///< [in] Data field name
    const std::string& sValue, 										///< [in] Value of field
    const std::string& sModifierID,									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    const std::string& sManipParam1,								///< [in] Parameter 1 to modifier function.
    const std::string& sManipParam2, 								///< [in] Parameter 2 to modifier function.
    const std::string& sManipParam3									///< [in] Parameter 3 to modifier function.
    )
{
    curMiner()->outputDirect( sFieldName, sValue, sModifierID, sManipParam1, sManipParam2, sManipParam3 );
}

void		outputDirect(
    const std::string& sFieldName, 									///< [in] Data field name
    const std::string& sValue, 										///< [in] Value of field
    const std::string& sModifierID,									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    const std::string& sManipParam1,								///< [in] Parameter 1 to modifier function.
    const std::string& sManipParam2 								///< [in] Parameter 2 to modifier function.
    )
{
    curMiner()->outputDirect( sFieldName, sValue, sModifierID, sManipParam1, sManipParam2 );
}

void		outputDirect(
    const std::string& sFieldName, 									///< [in] Data field name
    const std::string& sValue, 										///< [in] Value of field
    const std::string& sModifierID,									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    const std::string& sManipParam1									///< [in] Parameter 1 to modifier function.
    )
{
    curMiner()->outputDirect( sFieldName, sValue, sModifierID, sManipParam1 );
}

void		outputDirect(
    const std::string& sFieldName, 									///< [in] Data field name
    const std::string& sValue, 										///< [in] Value of field
    const std::string& sModifierID									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    )
{
    curMiner()->outputDirect( sFieldName, sValue, sModifierID );
}

void		outputDirect(
    const std::string& sFieldName, 									///< [in] Data field name
    const std::string& sValue 										///< [in] Value of field
    )
{
    curMiner()->outputDirect( sFieldName, sValue );
}

/**@}*/

// --------------------------------------
// --- NEW outputValueUnit functions ---
// --------------------------------------

/** Output of current value with unit to the output (eg. XML file).
The string manipulation function can be the name of one of the built-ins like
'append', 'eraseAll' etc. By default the value is filtered through the trimDefault function
which trims spaces away from both end of the output string value. If you don't want this
trimming you should use 'raw' as your manipulation function, which takes no extra parameters.

!User defined PHP manipulation function
You can also supply a user defined PHP function name as the string manipulation function, which if
found, will take precedence. The function will be called with the current value you're as first parameter
and any manipulation parameters as the following arguments. If you don't need all the arguments you do
not need to declare them in your PHP funcion, as they will just be silently ignored.

!Return value from user PHP manipulation function.
You have two options:
-# You return the manipulated value, which is then filtered trhough 'trimDefault' and written to
   the output using the \a sFieldName. In case you do not want the 'trimDefault' you have
   to name you user defined function so that the string 'raw' is part of the name somehow.
-# You return an empty string from your user function (or simply omit the return statement) in which
   case nothing is written to the output. You are then asumed to have taken care of this directly in your
   PHP function by calling another output function.
*/
void		outputValueUnit(
    const std::string& sFieldName, 									///< [in] Data field name
    const std::string& sUnit, 										///< [in] Unit of field
    const std::string& sModifierID,									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    const std::string& sManipParam1,								///< [in] Parameter 1 to modifier function.
    const std::string& sManipParam2, 								///< [in] Parameter 2 to modifier function.
    const std::string& sManipParam3,								///< [in] Parameter 3 to modifier function.
    const std::string& /* sManipParam4 reserved */					///< [in] Parameter 4 to modifier function.
    )
{
    curMiner()->outputValueUnit( sFieldName, sUnit, sModifierID, sManipParam1, sManipParam2, sManipParam3 );
}

void		outputValueUnit(
    const std::string& sFieldName, 									///< [in] Data field name
    const std::string& sUnit, 										///< [in] Unit of field
    const std::string& sModifierID,									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    const std::string& sManipParam1,								///< [in] Parameter 1 to modifier function.
    const std::string& sManipParam2, 								///< [in] Parameter 2 to modifier function.
    const std::string& sManipParam3									///< [in] Parameter 3 to modifier function.
    )
{
    curMiner()->outputValueUnit( sFieldName, sUnit, sModifierID, sManipParam1, sManipParam2, sManipParam3 );
}

void		outputValueUnit(
    const std::string& sFieldName, 									///< [in] Data field name
    const std::string& sUnit, 										///< [in] Unit of field
    const std::string& sModifierID,									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    const std::string& sManipParam1,								///< [in] Parameter 1 to modifier function.
    const std::string& sManipParam2 								///< [in] Parameter 2 to modifier function.
    )
{
    curMiner()->outputValueUnit( sFieldName, sUnit, sModifierID, sManipParam1, sManipParam2 );
}

void		outputValueUnit(
    const std::string& sFieldName, 									///< [in] Data field name
    const std::string& sUnit, 										///< [in] Unit of field
    const std::string& sModifierID,									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    const std::string& sManipParam1									///< [in] Parameter 1 to modifier function.
    )
{
    curMiner()->outputValueUnit( sFieldName, sUnit, sModifierID, sManipParam1 );
}

void		outputValueUnit(
    const std::string& sFieldName, 									///< [in] Data field name
    const std::string& sUnit, 										///< [in] Unit of field
    const std::string& sModifierID									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    )
{
    curMiner()->outputValueUnit( sFieldName, sUnit, sModifierID );
}

void		outputValueUnit(
    const std::string& sFieldName, 									///< [in] Data field name
    const std::string& sUnit 										///< [in] Unit of field
    )
{
    curMiner()->outputValueUnit( sFieldName, sUnit );
}


// ---------------------------------
// --- NEW outputValue functions ---
// ---------------------------------

/**
\defgroup outputValueFunctions outputValue functions
@{

Output of current value to the output (eg. XML file).
The string manipulation function can be the name of one of the built-ins like
'append', 'eraseAll' etc. By default the value is filtered through the trimDefault function
which trims spaces away from both end of the output string value. If you don't want this
trimming you should use 'raw' as your manipulation function, which takes no extra parameters.

!User defined PHP manipulation function
You can also supply a user defined PHP function name as the string manipulation function, which if
found, will take precedence. The function will be called with the current value you're as first parameter
and any manipulation parameters as the following arguments. If you don't need all the arguments you do
not need to declare them in your PHP funcion, as they will just be silently ignored.

!Return value from user PHP manipulation function.
You have two options:
-# You return the manipulated value, which is then filtered trhough 'trimDefault' and written to
   the output using the \a sFieldName. In case you do not want the 'trimDefault' you have
   to name you user defined function so that the string 'raw' is part of the name somehow.
-# You return an empty string from your user function (or simply omit the return statement) in which
   case nothing is written to the output. You are then asumed to have taken care of this directly in your
   PHP function by calling another output function.
*/
void		outputValue(
    const std::string& sFieldName, 									///< [in] Data field name
    const std::string& sModifierID,									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    const std::string& sManipParam1,								///< [in] Parameter 1 to modifier function.
    const std::string& sManipParam2, 								///< [in] Parameter 2 to modifier function.
    const std::string& sManipParam3,								///< [in] Parameter 3 to modifier function.
    const std::string& /* sManipParam4 reserved */					///< [in] Parameter 4 to modifier function.
    )
{
    curMiner()->outputValue( sFieldName, sModifierID, sManipParam1, sManipParam2, sManipParam3 );
}


void		outputValue(
    const std::string& sFieldName, 									///< [in] Data field name
    const std::string& sModifierID,									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    const std::string& sManipParam1,								///< [in] Parameter 1 to modifier function.
    const std::string& sManipParam2, 								///< [in] Parameter 2 to modifier function.
    const std::string& sManipParam3									///< [in] Parameter 3 to modifier function.
    )
{
    curMiner()->outputValue( sFieldName, sModifierID, sManipParam1, sManipParam2, sManipParam3 );
}

void		outputValue(
    const std::string& sFieldName, 									///< [in] Data field name
    const std::string& sModifierID,									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    const std::string& sManipParam1,								///< [in] Parameter 1 to modifier function.
    const std::string& sManipParam2 								///< [in] Parameter 2 to modifier function.
    )
{
    curMiner()->outputValue( sFieldName, sModifierID, sManipParam1, sManipParam2 );
}

void		outputValue(
    const std::string& sFieldName, 									///< [in] Data field name
    const std::string& sModifierID,									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    const std::string& sManipParam1									///< [in] Parameter 1 to modifier function.
    )
{
    curMiner()->outputValue( sFieldName, sModifierID, sManipParam1 );
}

void		outputValue(
    const std::string& sFieldName, 									///< [in] Data field name
    const std::string& sModifierID									///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    )
{
    curMiner()->outputValue( sFieldName, sModifierID );
}

void		outputValue(
    const std::string& sFieldName 									///< [in] Data field name
    )
{
    curMiner()->outputValue( sFieldName );
}

/**@}*/


// --- outputValueFindNextImpl ---

// TODO: Should go out, since it's a helper not to be called from scripts
int		outputValueFindNextImpl(
     int iCount 								///< [in] Stop at match number iCount (use negative numbers for backwards search).
    ,const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sFieldName 				///< [in] Data field name
    ,const std::string& sModifierID				///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    ,const std::string& sManipParam1			///< [in] Parameter 1 to function
    ,const std::string& sManipParam2			///< [in] Parameter 2 to function
    ,const std::string& sManipParam3			///< [in] Parameter 3 to function
    ,const std::string& sManipParam4			///< [in] Parameter 4 to function
    ,bool bUpdateDomPos							///< [in] Do update dom position to found position.
    )
{
    return curMiner()->outputValueFindNextImpl( iCount, sSequence, sFieldName, sModifierID, sManipParam1, sManipParam2, sManipParam3, sManipParam4, bUpdateDomPos );
}

/*
-------------------------------------
--- outputValueFindNext functions ---
------------------------------------- */
/**
 * \defgroup outputValueFindFunctions outputValueFind functions
 * @{
 */

int		outputValueFindNext(
     int iCount 								///< [in] Stop at match number iCount (use negative numbers for backwards search).
    ,const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sFieldName 				///< [in] Data field name
    ,const std::string& sModifierID				///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    ,const std::string& sManipParam1			///< [in] Parameter 1 to function
    ,const std::string& sManipParam2			///< [in] Parameter 2 to function
    ,const std::string& sManipParam3			///< [in] Parameter 3 to function
    ,const std::string& sManipParam4			///< [in] Parameter 4 to function
    )
{
    return curMiner()->outputValueFindNext( iCount, sSequence, sFieldName, sModifierID, sManipParam1, sManipParam2, sManipParam3, sManipParam4 );
}

int	outputValueFindNext( int iCount, const std::string& sSequence, const std::string& sFieldName, const std::string& sModifierID,const std::string& sManipParam1			///< [in] Parameter 1 to function
    ,const std::string& sManipParam2			///< [in] Parameter 2 to function
    ,const std::string& sManipParam3			///< [in] Parameter 3 to function
    )
{
    return curMiner()->outputValueFindNext( iCount, sSequence, sFieldName, sModifierID, sManipParam1, sManipParam2, sManipParam3 );
}

int		outputValueFindNext(
     int iCount 								///< [in] Stop at match number iCount (use negative numbers for backwards search).
    ,const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sFieldName 				///< [in] Data field name
    ,const std::string& sModifierID				///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    ,const std::string& sManipParam1			///< [in] Parameter 1 to function
    ,const std::string& sManipParam2			///< [in] Parameter 2 to function
    )
{
    return curMiner()->outputValueFindNext( iCount, sSequence, sFieldName, sModifierID, sManipParam1, sManipParam2 );
}

int		outputValueFindNext(
     int iCount 								///< [in] Stop at match number iCount (use negative numbers for backwards search).
    ,const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sFieldName 				///< [in] Data field name
    ,const std::string& sModifierID				///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    ,const std::string& sManipParam1			///< [in] Parameter 1 to function
    )
{
    return curMiner()->outputValueFindNext( iCount, sSequence, sFieldName, sModifierID, sManipParam1 );
}

int		outputValueFindNext(
     int iCount 								///< [in] Stop at match number iCount (use negative numbers for backwards search).
    ,const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sFieldName 				///< [in] Data field name
    ,const std::string& sModifierID				///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    )
{
    return curMiner()->outputValueFindNext( iCount, sSequence, sFieldName, sModifierID );
}

int		outputValueFindNext(
     int iCount 								///< [in] Stop at match number iCount (use negative numbers for backwards search).
    ,const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sFieldName 				///< [in] Data field name
    )
{
    return curMiner()->outputValueFindNext( iCount, sSequence, sFieldName );
}

int		outputValueFindNext(
     const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sFieldName 				///< [in] Data field name
    ,const std::string& sModifierID				///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    ,const std::string& sManipParam1			///< [in] Parameter 1 to function
    ,const std::string& sManipParam2			///< [in] Parameter 2 to function
    ,const std::string& sManipParam3			///< [in] Parameter 3 to function
    ,const std::string& sManipParam4			///< [in] Parameter 4 to function
    )
{
    return curMiner()->outputValueFindNext( sSequence, sFieldName, sModifierID, sManipParam1, sManipParam2, sManipParam3, sManipParam4 );
}

int		outputValueFindNext(
     const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sFieldName 				///< [in] Data field name
    ,const std::string& sModifierID				///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    ,const std::string& sManipParam1			///< [in] Parameter 1 to function
    ,const std::string& sManipParam2			///< [in] Parameter 2 to function
    ,const std::string& sManipParam3			///< [in] Parameter 3 to function
    )
{
    return curMiner()->outputValueFindNext( sSequence, sFieldName, sModifierID, sManipParam1, sManipParam2, sManipParam3 );
}

int		outputValueFindNext(
     const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sFieldName 				///< [in] Data field name
    ,const std::string& sModifierID				///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    ,const std::string& sManipParam1			///< [in] Parameter 1 to function
    ,const std::string& sManipParam2			///< [in] Parameter 2 to function
    )
{
    return curMiner()->outputValueFindNext( sSequence, sFieldName, sModifierID, sManipParam1, sManipParam2 );
}

int		outputValueFindNext(
     const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sFieldName 				///< [in] Data field name
    ,const std::string& sModifierID				///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    ,const std::string& sManipParam1			///< [in] Parameter 1 to function
    )
{
    return curMiner()->outputValueFindNext( sSequence, sFieldName, sModifierID, sManipParam1 );
}

int		outputValueFindNext(
     const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sFieldName 				///< [in] Data field name
    ,const std::string& sModifierID				///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    )
{
    return curMiner()->outputValueFindNext( sSequence, sFieldName, sModifierID );
}

int		outputValueFindNext(
     const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sFieldName 				///< [in] Data field name
    )
{
    return curMiner()->outputValueFindNext( sSequence, sFieldName );
}



/*
---------------------------------
--- outputValueFind functions ---
--------------------------------- */
/** Combine domFind with outputValue.
 * This function combines a call to domFind with a call to outputValue.
 * The outputValue "part" is only called if the domFind part does not return
 * zero.
 *
 * */
 int		outputValueFind (
     int iCount 								///< [in] Stop at match number iCount (use negative numbers for backwards search). If omitted, as in overloads, positive 1 is used.
    ,const std::string& sSequence				///< [in] Name of dom sequence to find or custom PHP function to call.
    ,const std::string& sFieldName 				///< [in] Data field name
    ,const std::string& sModifierID				///< [in] Built-in modifier function like 'append', 'removeAll', ... A named modifier (created using modifierCreate() ) or a user defined PHP function.
    ,const std::string& sManipParam1			///< [in] Parameter 1 to function
    ,const std::string& sManipParam2			///< [in] Parameter 2 to function
    ,const std::string& sManipParam3			///< [in] Parameter 3 to function
    ,const std::string& sManipParam4			///< [in] Parameter 4 to function
    )
{
    return curMiner()->outputValueFind( iCount, sSequence, sFieldName, sModifierID, sManipParam1, sManipParam2, sManipParam3, sManipParam4 );
}


int	outputValueFind (int iCount, const std::string& sSequence, const std::string& sFieldName, const std::string& sModifierID,
                     const std::string& sManipParam1, const std::string& sManipParam2, const std::string& sManipParam3 )
{
    return curMiner()->outputValueFind( iCount, sSequence, sFieldName, sModifierID, sManipParam1, sManipParam2, sManipParam3);
}

int outputValueFind (int iCount, const std::string& sSequence, const std::string& sFieldName, const std::string& sModifierID,
                     const std::string& sManipParam1, const std::string& sManipParam2)
{
    return curMiner()->outputValueFind( iCount, sSequence, sFieldName, sModifierID, sManipParam1, sManipParam2 );
}

int	outputValueFind (int iCount, const std::string& sSequence, const std::string& sFieldName, const std::string& sModifierID,
                     const std::string& sManipParam1)
{
    return curMiner()->outputValueFind( iCount, sSequence, sFieldName, sModifierID, sManipParam1 );
}

int	outputValueFind (int iCount, const std::string& sSequence, const std::string& sFieldName, const std::string& sModifierID)
{
    return curMiner()->outputValueFind( iCount, sSequence, sFieldName, sModifierID );
}

int	outputValueFind (int iCount, const std::string& sSequence, const std::string& sFieldName)
{
    return curMiner()->outputValueFind( iCount, sSequence, sFieldName );
}

int	outputValueFind (const std::string& sSequence, const std::string& sFieldName, const std::string& sModifierID,
                     const std::string& sManipParam1, const std::string& sManipParam2, const std::string& sManipParam3,const std::string& sManipParam4)
{
    return curMiner()->outputValueFind( sSequence, sFieldName, sModifierID, sManipParam1, sManipParam2, sManipParam3, sManipParam4 );
}

int	outputValueFind (const std::string& sSequence, const std::string& sFieldName, const std::string& sModifierID,
                     const std::string& sManipParam1, const std::string& sManipParam2, const std::string& sManipParam3)
{
    return curMiner()->outputValueFind( sSequence, sFieldName, sModifierID, sManipParam1, sManipParam2, sManipParam3 );
}

int	outputValueFind (const std::string& sSequence, const std::string& sFieldName, const std::string& sModifierID,
                     const std::string& sManipParam1, const std::string& sManipParam2)
{
    return curMiner()->outputValueFind( sSequence, sFieldName, sModifierID, sManipParam1, sManipParam2 );
}

int	outputValueFind ( const std::string& sSequence, const std::string& sFieldName, const std::string& sModifierID, const std::string& sManipParam1)
{
    return curMiner()->outputValueFind( sSequence, sFieldName, sModifierID, sManipParam1 );
}

int	outputValueFind ( const std::string& sSequence ,const std::string& sFieldName ,const std::string& sModifierID)
{
//    static int counter = 0;
//    ++counter;    std::cerr  << "[" << counter << "] FIXMENM outputValueFind(" << sSequence << ", " << sFieldName << ", " << sModifierID << ")\n";
    return curMiner()->outputValueFind( sSequence, sFieldName, sModifierID );
}

int outputValueFind (const std::string& sSequence, const std::string& sFieldName )
{
    return curMiner()->outputValueFind( sSequence, sFieldName );
}

/**@}*/

// -----------------------------------------------
// --- Implementation: Context functions ---
// -----------------------------------------------

/**
 * \defgroup ContextFunctions Context functions
 * @{
 */

void dataPushContext (
    std::string sContext,
    std::string const& sUnit )
{
    curMiner()->dataPushContext( sContext, sUnit );
}

void dataPushContextAlias (
    const std::string& sContext,
    const std::string& sContextAlias,
    const std::string& sUnit )
{
    curMiner()->dataPushContextAlias( sContext, sContextAlias, sUnit );
}

void dataPopContext	()
{
    curMiner()->dataPopContext();
}


void contextBegin(	std::string sContextName )
{
    curMiner()->contextBegin(sContextName);
}

void contextEnd ()
{
    curMiner()->contextEnd();
}

void contextOutputSaveAs ( const std::string& sContextName )
{
    curMiner()->contextOutputSaveAs(sContextName);
}

void contextFallbackOutputLoad( const std::string& sContextName )
{
    curMiner()->contextFallbackOutputLoad(sContextName);
}

void contextFallbackOutputClear()
{
    return curMiner()->contextFallbackOutputClear();
}

std::string contextFallbackValueGet( const std::string& sFieldName )
{
    return curMiner()->contextFallbackValueGet(sFieldName);
}

void contextFallbackValueSet( const std::string& sFieldName, const std::string& sValue )
{
    return curMiner()->contextFallbackValueSet(sFieldName,sValue);
}

bool contextFallbackValueExists( const std::string& sFieldName )
{
    return curMiner()->contextFallbackValueExists(sFieldName);
}

void contextFallbackValueDelete( const std::string& sFieldName )
{
    curMiner()->contextFallbackValueDelete(sFieldName);
}

bool contextSavedOutputExists( const std::string& sContextName )
{
    return curMiner()->contextSavedOutputExists(sContextName);
}

void contextSavedOutputDelete( const std::string& sContextName )
{
    curMiner()->contextSavedOutputDelete(sContextName);
}


//void dataSaveContextOutput   (
//    const std::string& sContextName
//)
//{
//    curMiner()->dataSaveContextOutput( sContextName );
//}

//void dataLoadContextOutput (
//    const std::string& sContextName
//)
//{
//    curMiner()->dataLoadContextOutput( sContextName );
//}

//std::string dataSavedContextOutputGet(
//    const std::string& sFieldName
//    )
//{
//    return curMiner()->dataSavedContextOutputGet( sFieldName );
//}

//void dataSavedContextOutputDelete (
//    const std::string& sFieldName
//    )
//{
//    curMiner()->dataSavedContextOutputDelete( sFieldName );
//}


/**@}*/

// --------------------------------------------
// --- Implementation: Javascript functions ---
// --------------------------------------------
/**
 * \defgroup JavascriptFunctions Javascript functions
 * @{
 */
bool javaScriptExecuteRetVal(
    const std::string& sScript,
    std::string& sScriptReturnValue )
{
    return curMiner()->javaScriptExecuteRetVal( sScript, sScriptReturnValue );
}

bool javaScriptExecute(
    const std::string& sScript )
{
    return curMiner()->javaScriptExecute( sScript );
}

bool javaScriptExecuteWait(const std::string &sScript, int timeoutInMs)
{
    return curMiner()->javaScriptExecuteWait( sScript, timeoutInMs );
}
/**@}*/

// -------------------------
// --- Utility functions ---
// -------------------------
/**
 * \defgroup UtilityFunctions Utility functions
 * @{
 */

int	curlPostUploadFileSimple(
      const std::string& sURL
    , const std::string& sFieldName
    , const std::string& sFilePath
    )
{
    return curMiner()->curlPostUploadFileSimple( sURL, sFieldName, sFilePath );
}


bool gzCompressFile	(
      const std::string& sSrcFilePath
    , const std::string& sDstFilePath
    )
{
    return curMiner()->gzCompressFile( sSrcFilePath, sDstFilePath );
}

bool gzUnCompressFile (
      const std::string& sSrcFilePath
    , const std::string& sDstFilePath
    )
{
    return curMiner()->gzUnCompressFile( sSrcFilePath, sDstFilePath );
}
/**@}*/


/*
--------------------------
--- Settings functions ---
-------------------------- */
/**
 * \defgroup SettingsFunctions Settings functions
 * @{
 *
 * Functions for manipulating the settings map. Mainly a map for the scripts
 * own use. So a way to have "global" variables across different PHP functions in the script.
 * It has mainly one coupling to the undelying crawler ssystem:
 * This is if you set a value for an output value like for example if the script sets the country_code
 * like this in the top of the script:
 * @code
 * settingSet('currency_code','dkk');
 * @endcode
 *
 * Then when the script at a later point does:
 *
 * @code
 * outputValueFind ( "currency_code__ItemPage__FIND", "currency_code", "currency_code__ItemPage__MOD");
 * @endcode
 *
 * Then if there's no dom sequence defined called currency_code__ItemPage__FIND or it does not find anything, then
 * the above lione will still write the "fallback" value "dkk" as currency_code to the output file because it was
 * stored under this name in the settings map/dictionary.
 *
 */

void settingDelete	(
      const std::string& sName
    )
{
    curMiner()->settingDelete( sName );
}

void settingSet	(
      const std::string& sName
    , const std::string& sValue
    )
{
    curMiner()->settingSet( sName, sValue);
}

std::string settingGet (const std::string& sName , const std::string& defaultValue)
{
    return curMiner()->settingGet(sName, defaultValue);
}

bool settingExists ( const std::string& sName )
{
    return curMiner()->settingExists(sName);
}

bool hasSetting ( const std::string& sName )
{
    return curMiner()->hasSetting(sName);
}

bool settingBoolGet ( const std::string& sName )
{
    return curMiner()->settingBoolGet(sName);
}
/**@}*/
// ----------------------------------------
// --- Implementation: Config functions ---
// ----------------------------------------

/**
 * \defgroup ConfigFunctions Config functions
 * @{
 *
 * Functions for controlling configuration of how the crawler runs.
 */

/** Get config value as a string.
 *
 * @param sName [in] Name of configuration value.
*/
std::string configValueGet (const std::string& sName)
{
    return curMiner()->configValueGet(sName);
}

/** Set config value.
 *
 * @param sName [in] Name of configuration value.
 * @param sValue [in] Value to store in the configuration map under the given name.
*/
void configValueSet (const std::string& sName, const std::string& sValue)
{
    curMiner()->configValueSet(sName, sValue);
}

/** Get config value interpreted as a boolean value.
 *
 * @param sName [in] Name of configuration value.
*/
bool configValueBoolGet(const std::string& sName)
{
    return curMiner()->configValueBoolGet(sName);
}

/** Set the URL to load as first page. If this function is not called the siteUrl
will be used as starting URL. */
void configUrlStart (
    const std::string& sUrl	)		///< [in] URL to load first.
{
    curMiner()->configUrlStartSet( sUrl );
}

/** Set the URL to upload XML data to. */
void configUrlUploadDataSet (
    const std::string& sUrl	)		///< [in] URL to upload XML data to.
{
    curMiner()->configUrlUploadDataSet( sUrl );
}

/** Set the URL to upload XML data to. */
std::string configUrlUploadDataGet ()
{
    return curMiner()->configUrlUploadDataGet();
}


/** Disable image loading.
This only really affects non robot/web runmodes which have image load turned on
by default. If for some reason you need to enforce loading of images even in
when run on the miner robot machines (robot/web run modes) the use configForceLoadImages().
@note This only affects Webkit browser mode. As the simple browser only loads the primary page and no images, ajax requests etc.
\sa configForceLoadImages() */
void configDisableLoadImages()
{
    curMiner()->configDisableLoadImages();
}

/** Force image loading.
Force the loading of images in all runmodes.
\note You should have a really good reason for calling this function, like you need to
      take screenshots of the pages visited. It will slow down mining considerably.
@note This only affects Webkit browser mode. As the simple browser only loads the primary page and no images, ajax requests etc.
\sa configDisableLoadImages() */
void configForceLoadImages()
{
    curMiner()->configForceLoadImages();
}


/** Add to list of "secondary" URL page requests that will be allowed.
 *
 * This function along with the configAddExcludeUrl() function can be used to limit the number of extra URL requests
 * for each main page loaded. Like we might want to exclude any URLS from facebook, Google analytics etc.
 *
 * Before each extra request from the main HTML page to load javascript, css files etc. the URL is checked
 * using the combinations of the the pattern/compare-function pairs added using these two functions:
 * configAddIncludeUrl(), configAddExcludeUrl().
 * The URL resource is loaded if not explicitly excluded OR in case one rule excludes it, then if another explicitly
 * includes it - it is still loaded.
 *
 * @note This only affects Webkit browser mode. As the simple browser only loads the primary page and no images, ajax requests etc.
 * @note DO NOT confuse this function with siteMapLocationsInclude()/siteMapLocationsExclude() which is for filtering main page
 * loads URLs from sitemaps.
 *
 * \sa addToExcludeUrls, siteMapLocationsInclude, siteMapLocationsExclude */
void configAddIncludeUrl (
    const std::string& sPattern,    ///< Pattern include by matching against the compare function
    const std::string& sCompareFun  ///< Compare function to use, like "equals", "contains", "beginsWith", etc.
)
{
    curMiner()->configAddIncludeUrl( sPattern, sCompareFun );
}

/** Add to list of "secondary" URL page requests that will be blocked.
 *
 * This function along with the configAddExcludeUrl() function can be used to limit the number of extra URL requests
 * for each main page loaded. Like we might want to exclude any URLS from facebook, Google analytics etc.
 *
 * Before each extra request from the main HTML page to load javascript, css files etc. the URL is checked
 * using the combinations of the the pattern/compare-function pairs added using these two functions:
 * configAddIncludeUrl(), configAddExcludeUrl().
 * The URL resource is loaded if not explicitly excluded OR in case one rule excludes it, then if another explicitly
 * includes it - it is still loaded.
 *
 * @note This only affects Webkit browser mode. As the simple browser only loads the primary page and no images, ajax requests etc.
 * @note DO NOT confuse this function with siteMapLocationsInclude()/siteMapLocationsExclude() which is for filtering main page
 * loads URLs from sitemaps.
 *
 * \sa configAddIncludeUrl, siteMapLocationsInclude, siteMapLocationsExclude */
void configAddExcludeUrl (
    const std::string& sPattern,        ///< Pattern exclude by matching against the compare function
    const std::string& sCompareFun      ///< Compare function to use, like "equals", "contains", "beginsWith", etc.
)
{
    curMiner()->configAddExcludeUrl( sPattern, sCompareFun );
}


/** Control whether sending XML data to server or not.
 *
Force sending the XML data file to the server in all runmodes.
Overrides the '--upload-data=yes/no' command line setting.
Can be used if you need to test sending data during creation of the script.
In 'crawler' runmode the data will allways be sent to the server.
@param bUploadData [in] Upload data or to server or not.
*/
void configUploadData ( bool bUploadData )
{
    curMiner()->configUploadData(bUploadData);
}

/** Force sending XML data to server.
Force sending the XML data file to the server in all runmodes.
Overrides the '--upload-data=yes/no' command line setting.
Can be used if you need to test sending data during creation of the script.
In 'crawler' runmode the data will normally allways be sent to the server. */
void configForceSendXmlData()
{
    curMiner()->configForceSendXmlData();
}


/** Configure timeout for generating simulated page loaded event.
 *
 * When pages load extra data using ajax calls instead of loading a new page, we
 * try to simulate a page loaded event when each "burst" of ajax activity has ceased.
 * The amount of milliseconds to wait before triggering the page loaded event is
 * configured througg this setting.
 *
 * @note This only affects Webkit browser mode. As the simple browser only loads the primary page and no images, ajax requests etc.
 *
 * @param iMilliSeconds [in] Simulate page loaded after the amount of milliseconds passed since last ajax/network activity.
*/
void configAjaxPageLoadDeltaTime(int iMilliSeconds)
{
    curMiner()->configAjaxPageLoadDeltaTime(iMilliSeconds);
}

void configReloadTimeOut ( int iMinutes, int iSecs )
{
    curMiner()->configReloadTimeOut( iMinutes, iSecs );
}

void configKeepActiveInterval ( int iSecs )
{
    curMiner()->configKeepActiveInterval( iSecs );
}

void configProgressOutputSet	( bool bEnable )
{
    curMiner()->configProgressOutputSet( bEnable );
}

void configDebugOutputSet( bool bEnable )
{
    curMiner()->configDebugOutputSet( bEnable );
}

bool configDebugOutputGet()
{
    return curMiner()->configDebugOutputGet();
}

/** Set which character to use a decimal point when parsing numbers.
 *
 * When parsing integers an floating point numbers we need to do it according
 * to whatever locale the site we are crawling uses.
 *
 * @param sDecimalPoint [in] String with char to use as decimal point when parsing numbers. Typically "." or ",".
*/
void configParseDecimalPointSet( const std::string& sDecimalPoint  )
{
    curMiner()->configParseDecimalPointSet( sDecimalPoint );
}

/** Set which character to use as thousands separator when parsing numbers.
 *
 * When parsing integers an floating point numbers we need to do it according
 * to whatever locale the site we are crawling uses.
 *
 * @param sDecimalPoint [in] String with char to use as thousands separator when parsing numbers. Typically "." or ",".
*/
void configParseThousandsSepSet( const std::string& sThousandsSep )
{
    curMiner()->configParseThousandsSepSet( sThousandsSep );
}


void configOutputEncloseCDATA( bool bDoEncloseInCDATA )
{
    curMiner()->configOutputEncloseCDATA( bDoEncloseInCDATA );
}

void configOutputWriteToFile ( bool bDoWriteOutputToFile )
{
    curMiner()->configOutputWriteToFile( bDoWriteOutputToFile );
}

std::string configGetRunMode()
{
    return curMiner()->configGetRunMode();
}

void configInsertEndTagNodes ( bool /*bInsertEndTagNodes*/ )
{
    // TODO: Obsolete. Not to be used anymore !
    ////curMiner()->configInsertEndTagNodes( bInsertEndTagNodes );
}

void configSkipEmptyNodes ( bool /*bSkipEmptyNodes*/ )
{
    // TODO: Obsolete. Not to be used anymore !
    ////curMiner()->configSkipEmptyNodes( bSkipEmptyNodes );
}

void configTrimBlanks ( bool /*bTrimBlanks*/ )
{
    // TODO: Obsolete. Not to be used anymore !
////    curMiner()->configTrimBlanks( bTrimBlanks );
}

void configLocaleSettingsSet(const std::string& country_or_currency_code)
{
    curMiner()->configLocaleSettingsSet(country_or_currency_code);
}

/**@}*/

// -----------------------
// --- Debug functions ---
// -----------------------

// ----------------------------------------------
// --- INLINE Implementation: Debug functions ---
// ----------------------------------------------

/**
 * \defgroup DebugFunctions Debug functions
 * @{
 *
 * General debug functions that print info to files and/or stdout.
 */

void locatedPositionsClear()
{
    curMiner()->locatedPositionsClear();
}

/** Debug print the entire DOM to a file or stdout.
@param sFileName [in] Filename to print to. If empty stdout is used.
*/
void domDebugPrint (const std::string& sFileName)
{
    curMiner()->domDebugPrint( sFileName );
}

/** Debug print current node optionally with the nodes surrounding it

### Overloads

\code
nodeDebugPrint (int iNodesBefore, int iNodesAfter, bool bPrintNodeTypes)
nodeDebugPrint (int iNodesAround, bool bPrintNodeTypes)
\endcode
@param iNodesBefore [in] Number of nodes to print before the current node (positive number always)
@param iNodesAfter [in] Number of nodes to print after the current node (positive number always)
@param iNodesAround [in] Number of nodes to print both before and after ther curent node
@param bPrintNodeTypes [in] Print the node types also
 * */
void nodeDebugPrint (int iNodesBefore, int iNodesAfter, bool bPrintNodeTypes)
{
    curMiner()->nodeDebugPrint( iNodesBefore, iNodesAfter, bPrintNodeTypes);
}

void nodeDebugPrint (int iNodesAround, bool bPrintNodeTypes)
{
    curMiner()->nodeDebugPrint( iNodesAround, iNodesAround, bPrintNodeTypes);
}

/** Get debug string of current node optionally with the nodes surrounding it

### Overloads

\code
nodeValueDebug (int iNodesBefore, int iNodesAfter, bool bPrintNodeTypes)
nodeValueDebug (int iNodesAround, bool bPrintNodeTypes)
\endcode
@param iNodesBefore [in] Number of nodes to print before the current node (positive number always)
@param iNodesAfter [in] Number of nodes to print after the current node (positive number always)
@param iNodesAround [in] Number of nodes to print both before and after ther curent node
@param bPrintNodeTypes [in] Print the node types also
@return String with the debug info
*/
std::string nodeValueDebug (int iNodesBefore, int iNodesAfter, bool bPrintNodeTypes)
{
    return curMiner()->nodeValueDebug( iNodesBefore, iNodesAfter, bPrintNodeTypes);
}

std::string nodeValueDebug (int iNodesAround, bool bPrintNodeTypes)
{
    return curMiner()->nodeValueDebug( iNodesAround, iNodesAround, bPrintNodeTypes);
}

/**@}*/


// --------------------------------------
// --- PUBLIC: General info functions ---
// --------------------------------------

/**
 * \defgroup GeneralInfoFunctions General info functions
 * @{
 *
 * Collection of some general info functions.
 */


/** Get start of mining in UTC formatted "ISO" pretty like this:
 *  2020-02-04 15:29:46.
@return "Pretty" ISO-like formatted (2020-02-04 15:29:46) date/time for mining start in UTC.
*/
std::string infoTimeMiningStartedUtc()
{
    return cpaf::time::format_utc(curMiner()->infoTimeMiningStarted(), cpaf::time::iso_pretty);
}


/** Get totally number of loaded pages.
@return Number of pages loaded in total up to now.
*/
int infoPageLoadsTotal()
{
    return static_cast<int>(curMiner()->infoPageLoadsTotal());
}


/** Get ID of last network error.
@return ID (int) of last network error.
*/
int infoLastNetworkError()
{
    return curMiner()->infoLastNetworkError();
}
/**@}*/
