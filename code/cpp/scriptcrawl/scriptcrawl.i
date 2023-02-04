
/* File : scripting.i */
%module scripting

%{
#include "scriptcrawl.h"
#include <string>
#include <vector>
#include <url/UrlGetter.h>
#include <utils/CommandLineParser.h>
#include <utils/string_compare_functions.h>
%}


%include "std_string.i"
%include "typemaps.i"
%include "std_vector.i"

namespace std {
    %template(vectori) vector<int>;
    %template(vectord) vector<double>;
    %template(vectors) vector<std::string>;
}

%typemap(out) std::vector<std::string>
{

   array_init(return_value);

   for(unsigned int i=0;i<$1.size();++i)
       add_next_index_string(return_value,$1[i].c_str(),1);

}

%typemap(out) std::vector<int>
{

   array_init(return_value);

   for(unsigned int i=0;i<$1.size();++i)
       add_next_index_long(return_value,$1[i]);

}

void*                       testPhpArrayGet ();
std::vector<int>            testArrayGet    ();


//std::vector<std::string>    testArrayStrGet    ();
//double              average         (std::vector<int> v);
//std::vector<double> half            (const std::vector<double>& v);
//void                halve_in_place  (std::vector<double>& v);

/*
class UrlGetter {
public:
    UrlGetter ( int iLinkType, const std::string& sUrlsMatch="",  const std::string& sIdCompFun = "equals" );
    ~UrlGetter();
    int				count					();
    bool			getNext					();
    void			resetCurrent			( int iNewCurrent = 0 );
    bool			currentAtEnd			();
    std::string		current					();
    std::string		current_raw				();
    std::string		currentProtocol			();
    std::string		currentPath				();
    std::string		currentParameters		();
    std::string		currentDomain			();
    std::string		currentTopDomain		();
    std::string		currentSecondLevelDomain();
    std::string		currentSubDomains		();
    std::string		currentSiteDomain		();
};
*/


namespace crawl {

    class DomSeq
    {
    public:
        DomSeq	();
        DomSeq	( int iCount, const std::string& sPattern, const std::string& sCompareFun, int iPostMatchSteps, int iNodeTypes, const std::string& sCommaChar );
        void	add	( const std::string& sPattern )	;
        void	add	( const std::string& sPattern, const std::string& sCompareFun );

        int		getSize	() 	const;
    };
}

/* --- Command line parsing --- */

namespace crawl {
    void			cmdDefaultValsSet	( const std::string sDefaults	);
    void			cmdParseStart		();
    bool			cmdParseArg			( const std::string sArgument	);
    std::string		cmdValStrGet		( const std::string sArgName 	);
    double			cmdValNumGet		( const std::string sArgName 	);
    void            cmdValStrForceSet	( const std::string sArgName, const std::string& sVal );
    void            cmdValNumForceSet	( const std::string sArgName, double fVal );
}




/* ----------------------
   --- Init functions ---
   ---------------------- */
void        currentMinerSetPointer          (const std::string& sMinerPointer);
void        currentMinerSetRaw              (void* pMiner);
void 		initMining                      ();
void 		addMiner                        (std::string sMinerName);
void 		runMiners                       ();
void        scriptHtmlEntitiesReplaceAdd    (const std::string& lookFor, const std::string& replaceWith);
void        scriptHtmlEntitiesReplaceClear  ();

// -------------------------------
// --- Info/settings functions ---
// -------------------------------
std::string     outputName                      ();

/*----------------------
--- Misc functions ---
----------------------*/
/*void 			useLocale			( const std::string& sLocale )	; */   /* Empty impl. for now */
std::string pageSource                          ();
std::string	currentMiner                        ();
std::string	currentDataFile                     ();
void        triggerPageLoaded                   ();
void        triggerPageLoadedWait               (int timeoutInMs = 3000);
void        waitSleep                           (int timeInMs);
void        waitForDomReady                     (int timeoutInMs = 30000);
void        waitForJavascriptDone               ();
void        clearCookies                        ();
int         configDelayPageLoadedTime           ();
void        configDelayPageLoadedTimeSet        (int milliseconds);
int         networkActivityCounter              ();

/*
-------------------------
--- Browser functions ---
------------------------- */

/* Key constants for user key events */

%constant int KEY_ESCAPE        ;
%constant int KEY_TAB           ;
%constant int KEY_BACKTAB       ;
%constant int KEY_BACKSPACE     ;
%constant int KEY_RETURN        ;
%constant int KEY_ENTER         ;
%constant int KEY_INSERT        ;
%constant int KEY_DELETE        ;
%constant int KEY_PAUSE         ;
%constant int KEY_PRINT         ;
%constant int KEY_SYSREQ        ;
%constant int KEY_CLEAR         ;
%constant int KEY_HOME          ;
%constant int KEY_END           ;
%constant int KEY_LEFT          ;
%constant int KEY_UP            ;
%constant int KEY_RIGHT         ;
%constant int KEY_DOWN          ;
%constant int KEY_PAGEUP        ;
%constant int KEY_PAGEDOWN      ;
%constant int KEY_SHIFT         ;
%constant int KEY_CONTROL       ;
%constant int KEY_META          ;
%constant int KEY_ALT           ;
%constant int KEY_CAPSLOCK      ;
%constant int KEY_NUMLOCK       ;
%constant int KEY_SCROLLLOCK    ;
%constant int KEY_F1            ;
%constant int KEY_F2            ;
%constant int KEY_F3            ;
%constant int KEY_F4            ;
%constant int KEY_F5            ;
%constant int KEY_F6            ;
%constant int KEY_F7            ;
%constant int KEY_F8            ;
%constant int KEY_F9            ;
%constant int KEY_F10           ;
%constant int KEY_F11           ;
%constant int KEY_F12           ;
%constant int KEY_F13           ;
%constant int KEY_F14           ;
%constant int KEY_F15           ;
%constant int KEY_F16           ;
%constant int KEY_F17           ;
%constant int KEY_F18           ;
%constant int KEY_F19           ;
%constant int KEY_F20           ;
%constant int KEY_F21           ;
%constant int KEY_F22           ;
%constant int KEY_F23           ;
%constant int KEY_F24           ;
%constant int KEY_F25           ;
%constant int KEY_F26           ;
%constant int KEY_F27           ;
%constant int KEY_F28           ;
%constant int KEY_F29           ;
%constant int KEY_F30           ;
%constant int KEY_F31           ;
%constant int KEY_F32           ;
%constant int KEY_F33           ;
%constant int KEY_F34           ;
%constant int KEY_F35           ;
%constant int KEY_SUPER_L       ;
%constant int KEY_SUPER_R       ;
%constant int KEY_MENU          ;
%constant int KEY_HYPER_L       ;
%constant int KEY_HYPER_R       ;
%constant int KEY_HELP          ;
%constant int KEY_DIRECTION_L   ;
%constant int KEY_DIRECTION_R   ;
%constant int KEY_SPACE         ;
%constant int KEY_ANY           ;
%constant int KEY_EXCLAM        ;
%constant int KEY_QUOTEDBL      ;
%constant int KEY_NUMBERSIGN    ;
%constant int KEY_DOLLAR        ;
%constant int KEY_PERCENT       ;
%constant int KEY_AMPERSAND     ;
%constant int KEY_APOSTROPHE    ;
%constant int KEY_PARENLEFT     ;
%constant int KEY_PARENRIGHT    ;
%constant int KEY_ASTERISK      ;
%constant int KEY_PLUS          ;
%constant int KEY_COMMA         ;
%constant int KEY_MINUS         ;
%constant int KEY_PERIOD        ;
%constant int KEY_SLASH         ;
%constant int KEY_0             ;
%constant int KEY_1             ;
%constant int KEY_2             ;
%constant int KEY_3             ;
%constant int KEY_4             ;
%constant int KEY_5             ;
%constant int KEY_6             ;
%constant int KEY_7             ;
%constant int KEY_8             ;
%constant int KEY_9             ;
%constant int KEY_COLON         ;
%constant int KEY_SEMICOLON     ;
%constant int KEY_LESS          ;
%constant int KEY_EQUAL         ;
%constant int KEY_GREATER       ;
%constant int KEY_QUESTION      ;
%constant int KEY_AT            ;
%constant int KEY_A             ;
%constant int KEY_B             ;
%constant int KEY_C             ;
%constant int KEY_D             ;
%constant int KEY_E             ;
%constant int KEY_F             ;
%constant int KEY_G             ;
%constant int KEY_H             ;
%constant int KEY_I             ;
%constant int KEY_J             ;
%constant int KEY_K             ;
%constant int KEY_L             ;
%constant int KEY_M             ;
%constant int KEY_N             ;
%constant int KEY_O             ;
%constant int KEY_P             ;
%constant int KEY_Q             ;
%constant int KEY_R             ;
%constant int KEY_S             ;
%constant int KEY_T             ;
%constant int KEY_U             ;
%constant int KEY_V             ;
%constant int KEY_W             ;
%constant int KEY_X             ;
%constant int KEY_Y             ;
%constant int KEY_Z             ;
%constant int KEY_BRACKETLEFT   ;
%constant int KEY_BACKSLASH     ;
%constant int KEY_BRACKETRIGHT  ;
%constant int KEY_ASCIICIRCUM   ;
%constant int KEY_UNDERSCORE    ;
%constant int KEY_QUOTELEFT     ;
%constant int KEY_BRACELEFT     ;
%constant int KEY_BAR           ;
%constant int KEY_BRACERIGHT    ;
%constant int KEY_ASCIITILDE    ;

/* --- Key modifier constants for user events --- */
%constant int NO_MODIFIER;
%constant int SHIFT_MODIFIER;
%constant int CONTROL_MODIFIER;
%constant int ALT_MODIFIER;
%constant int META_MODIFIER;
%constant int KEYPAD_MODIFIER;
%constant int GROUP_SWITCH_MODIFIER;

/* --- Key event types for user key events --- */
%constant int KEY_DOWN_EVENT;
%constant int KEY_UP_EVENT;
%constant int KEY_CLICK_EVENT;


/* --- Mouse buttons for user mouse events --- */
%constant int NO_BUTTON;
%constant int LEFT_BUTTON;
%constant int RIGHT_BUTTON;
%constant int MID_BUTTON;

/* --- Mouse event types for user mouse events --- */
%constant int MOUSE_DOWN_EVENT;
%constant int MOUSE_UP_EVENT;
%constant int MOUSE_DBLCLICK_EVENT;
%constant int MOUSE_MOVE_EVENT;
%constant int MOUSE_CLICK_EVENT;

void            browserScroll           (int x, int y);
int             browserScrollPosXGet    ();
int             browserScrollPosYGet    ();
void			browserHide             ();
void			browserShow             ();
void			browserSetSize          (int x, int y);
int             browserGetSizeX         ();
int             browserGetSizeY         ();
bool			browserGoBack           ();
void            browserKeyEvent         (int eventType, int key, int modifiers);
void            browserMouseEvent       (int eventType, float xpos, float ypos, int button, int buttons, int modifiers);
void            browserFocusActivate    ();
void            browserFocusDeactivate  ();

/*------------------------------------------
--- String operators/compare functions ---
------------------------------------------*/
typedef bool (*CompareStringsFnT)(const std::string&, const std::string&) ;
bool 			valuesCompare		( const std::string& sInput, const std::string& sTest, const std::string& sCompareFun );

/*
-------------------------
--- Sitemap functions ---
-------------------------*/
std::vector<std::string>    allSitemaps();
std::vector<std::string>    siteMapUrls             ();
void                        siteMapUrlsSet          (const std::vector<std::string> &siteMapUrls);
void                        siteMapUrlAppend        (const std::string &siteMapUrl);
std::vector<std::string>    siteMapLocationUrls     ();
void                        siteMapLocationsInclude	(const std::string& urlPattern, const std::string& compareFun = DefaultCompareFun );
void                        siteMapLocationsExclude	(const std::string& urlPattern, const std::string& compareFun = DefaultCompareFun );

/*
--------------------------------
--- Navigation (nav) functions ---
----------------------------------*/
%constant int ATTR;

void            navActiveNavigatorSet   ( const std::string& sNavigatorName );
std::string     navActiveNavigatorGet   ();
void            navJavascriptExecuteCreate ( const std::string& sNavActionName );
void            navUrlLoadCreate        ( const std::string& sNavActionName, const std::string& sBaseUrl = "" );
void            navInputOptionsCreate   ( const std::string& sNavActionName );
void            navDropDownSelectCreate ( const std::string& sNavActionName );
void            navDomPosClickCreate    ( const std::string& sNavActionName, const std::string& sFindNextDomPosSequence );
void            navAutoInputCreate      ( const std::string& sNavActionName, const std::string& sCharsList, int iMinLength, int iMaxLength );

void            navAttributeNamesCreate ( const std::string& sAttrNames, const std::string& sDelimiter = "," );

void            navCurrentStateIndicesSet ( const std::string& sState );
std::string     navCurrentStateIndicesGet ();
void            navCurrentStateSet      ( const std::string& sState, const std::string& sDelimiter );
void            navCurrentStateSet      ( const std::string& sState );
void            navBeginStateSet        ( const std::string& sState, const std::string& sDelimiter );
void            navBeginStateSet        ( const std::string& sState );
void            navEndStateSet          ( const std::string& sState, const std::string& sDelimiter );
void            navEndStateSet          ( const std::string& sState );

void            navOptionResourceAdd    ( const std::string& sResourcePath, const std::string& sScriptFilterFunction,  bool bForceDownload  );
void            navOptionAdd            ( int iCount, const std::string& sValue, const std::string& sSearchFor  );
void            navOptionAdd            ( int iCount, const std::string& sValue );
void            navOptionAdd            ( const std::string& sValue, const std::string& sSearchFor );
void            navOptionAdd            ( const std::string& sValue );
void            navOptionAdd            ( int iCount );

void            navOptionAdd            ( int iCount, const std::string& sValue, const std::string& sSearchFor,
                                          int attrStart, const std::string& sAttributes, const std::string& sDelimiter = "," );
void            navOptionAdd            ( int iCount, const std::string& sValue,
                                          int attrStart, const std::string& sAttributes, const std::string& sDelimiter = "," );
void            navOptionAdd            ( const std::string& sValue, const std::string& sSearchFor,
                                          int attrStart, const std::string& sAttributes, const std::string& sDelimiter = "," );
void            navOptionAdd            ( const std::string& sValue,
                                          int attrStart, const std::string& sAttributes, const std::string& sDelimiter = "," );
void            navOptionAdd            ( int iCount, int attrStart, const std::string& sAttributes, const std::string& sDelimiter = "," );

std::string     navDomTextValueGet      ( const std::string& sNavActionName ) ;
std::string     navDomValueGet          ( const std::string& sNavActionName ) ;
std::string     navValueGet             ( const std::string& sNavActionName ) ;
std::string     navSearchForGet         ( const std::string& sNavActionName ) ;
std::string     navAttributeGet         ( const std::string& sNavActionName, const std::string& sAttrName ) ;
std::string     navAttributeGet         ( const std::string& sAttrName );
int             navCountGet             ( const std::string& sNavActionName ) ;
int             navOptionIndexGet       ( const std::string& sNavActionName ) ;
int             navStateIndexGet        ();
int             navNumStatesGet         ();
int             navLastStateIndexGet    ();

bool            navNextState            ();
bool            navDoAction             ( const std::string& sNavActionName ) ;
bool            navDoActionClickAll     ( const std::string& sNavActionName ) ;
std::string     navStateString          ();
void            navStart                ();
void            navReset                ();
bool            navNavigationDone       ();
void            navAutoInputIncreaseLength ( bool bDoIncreaseLength );


bool 			equals_fn	( const std::string& sInput, 	const std::string& sTest 	)	;
bool 			iequals_fn	( const std::string& sInput, 	const std::string& sTest 	)	;
bool 			contains_fn	( const std::string& sInput, 	const std::string& sTest 	)	;
bool 			icontains_fn	( const std::string& sInput, 	const std::string& sTest 	)	;
bool 			startsWith_fn	( const std::string& sInput, 	const std::string& sTest 	)	;
bool 			istartsWith_fn	( const std::string& sInput, 	const std::string& sTest 	)	;
bool 			endsWith_fn	( const std::string& sInput, 	const std::string& sTest 	)	;
bool 			iendsWith_fn	( const std::string& sInput, 	const std::string& sTest 	)	;
bool 			lessThan_fn	( const std::string& sLhs, 		const std::string& sRhs 	)	;
bool 			ilessThan_fn	( const std::string& sLhs,   	const std::string& sRhs 	)	;
bool 			greaterThan_fn	( const std::string& sLhs, 		const std::string& sRhs 	)	;
bool 			igreaterThan_fn	( const std::string& sLhs,   	const std::string& sRhs 	)	;
bool			regexSearch_fn	( const std::string& sInput, 	const std::string& sRegex 	)	;


/*
-------------------------------------
--- String manipulation functions ---
-------------------------------------*/
/*
NOTE: These are normal callable PHP functions. Use same names without _fn
      when using as modifiers in outputXX() functions, valueModify(), valueGet(),
      valueCompare(), nodeCompare(), nodeValueParent(), nodeValuePos()
*/
/* --- 0 parameters --- */
std::string		trimDefault_fn 		( const std::string& sInput 	);
std::string		raw_fn			( const std::string& sInput	);
std::string		toUpper_fn		( const std::string& sInput	);
std::string		toLower_fn		( const std::string& sInput	);
std::string		trimEnds_fn		( const std::string& sInput	);
std::string		trimLeft_fn		( const std::string& sInput	);
std::string		trimRight_fn		( const std::string& sInput	);
std::string		trimYear_fn		( const std::string& sInput 	);
std::string		trimInteger_fn          ( const std::string& sInput	);
std::string		trimNumber_fn		( const std::string& sInput	);

/* --- 1 parameters --- */
std::string     trimCharsEnds_fn	( const std::string& sInput, const std::string& sCharsToTrim )	;
std::string     trimCharsLeft_fn	( const std::string& sInput, const std::string& sCharsToTrim ) 	;
std::string     trimCharsRight_fn	( const std::string& sInput, const std::string& sCharsToTrim )	;
std::string     trimRegex_fn		( const std::string& sInput, const std::string& sRegex )												;
std::string     itrimRegex_fn		( const std::string& sInput, const std::string& sRegex )												;
std::string		append_fn		( const std::string& sInput, const std::string& sString	)	;
std::string		prepend_fn		( const std::string& sInput, const std::string& sString	)	;
std::string		eraseFirst_fn		( const std::string& sInput, const std::string& sSearchFor	)	;
std::string		ieraseFirst_fn		( const std::string& sInput, const std::string& sSearchFor	)	;
std::string		eraseLast_fn		( const std::string& sInput, const std::string& sSearchFor	)	;
std::string		ieraseLast_fn		( const std::string& sInput, const std::string& sSearchFor	)	;
std::string		eraseAll_fn		( const std::string& sInput, const std::string& sSearchFor	)	;
std::string		ieraseAll_fn		( const std::string& sInput, const std::string& sSearchFor	)	;
std::string		eraseRegex_fn		( const std::string& sInput, const std::string& sSearchFor	)	;
std::string		eraseAllRegex_fn	( const std::string& sInput, const std::string& sSearchFor	)	;

/* --- 2 parameters --- */
std::string 	trimBetween_fn      ( const std::string& sInput, const std::string& sBegin, 		const std::string& sEnd );
std::string 	trimBetweenCount_fn ( const std::string& sInput, const std::string& sBegin, 		const std::string& sEnd, const std::string& sCount );
std::string 	trimBetweenCount_fn ( const std::string& sInput, const std::string& sBegin, 		const std::string& sEnd, int iCount );
std::string     trimIntegerCustom_fn( const std::string& sInput, const std::string& iBase,          const std::string& sThousandsSep);
std::string     trimNumberCustom_fn	( const std::string& sInput, const std::string& sDecimalPoint, 	const std::string& sThousandsSep);
std::string		replaceFirst_fn		( const std::string& sInput, const std::string& sSearchFor,		const std::string& sReplaceWith	);
std::string		ireplaceFirst_fn	( const std::string& sInput, const std::string& sSearchFor,		const std::string& sReplaceWith	);
std::string		replaceLast_fn		( const std::string& sInput, const std::string& sSearchFor,		const std::string& sReplaceWith	);
std::string		ireplaceLast_fn		( const std::string& sInput, const std::string& sSearchFor,		const std::string& sReplaceWith	);
std::string		replaceAll_fn		( const std::string& sInput, const std::string& sSearchFor,		const std::string& sReplaceWith	)	;
std::string		ireplaceAll_fn		( const std::string& sInput, const std::string& sSearchFor,		const std::string& sReplaceWith	)	;
std::string		replaceRegex_fn		( const std::string& sInput, const std::string& sSearchFor,		const std::string& sReplaceWith	)	;
std::string		replaceAllRegex_fn	( const std::string& sInput, const std::string& sSearchFor,		const std::string& sReplaceWith	)	;

/* --- 2 parameters (last is an integer ) --- */
std::string		eraseNth_fn			( const std::string& sInput, const std::string& sSearchFor,	int iNth 	)	;
std::string		eraseNth_fn         ( const std::string& sInput, const std::string& sSearchFor, const std::string& sNth 	);
std::string		ieraseNth_fn		( const std::string& sInput, const std::string& sSearchFor,	int iNth 	)	;
std::string		ieraseNth_fn        ( const std::string& sInput, const std::string& sSearchFor, const std::string& sNth 	);

/* --- 3 parameters (last is an integer ) --- */
std::string		replaceNth_fn		( const std::string& sInput, const std::string& sSearchFor,	const std::string& sReplaceWith, int iNth	)	;
std::string		replaceNth_fn       ( const std::string& sInput, const std::string& sSearchFor,	const std::string& sReplaceWith ,const std::string& sNth	);
std::string		ireplaceNth_fn		( const std::string& sInput, const std::string& sSearchFor,	const std::string& sReplaceWith, int iNth	)	;
std::string		ireplaceNth_fn      ( const std::string& sInput, const std::string& sSearchFor,	const std::string& sReplaceWith, const std::string& sNth	);


/*---------------------
--- URL functions ---
---------------------*/
std::string		urlSite();
std::string		urlCurrent();
bool			urlLoad		( const std::string sURL	);
bool			urlLoadWait	( const std::string sURL, int timeoutInMs = 30000);


/*
-------------------------------------------------------
--- OLD (DOM constants) For backwards compatibility ---
------------------------------------------------------- */
%constant int ELEMENT_NODE					;
%constant int ATTRIBUTE_NODE 				;
%constant int TEXT_NODE 					;
%constant int CDATA_SECTION_NODE 			;
%constant int ENTITY_REFERENCE_NODE 		;
%constant int ENTITY_NODE 					;
%constant int PROCESSING_INSTRUCTION_NODE	;
%constant int COMMENT_NODE 					;
%constant int DOCUMENT_NODE 				;
%constant int DOCUMENT_TYPE_NODE 			;
%constant int DOCUMENT_FRAGMENT_NODE 		;
%constant int NOTATION_NODE 				;
%constant int ATTRIBUTE_VALUE_NODE 			;

/*
---------------------
--- DOM constants ---
--------------------- */
%constant int ELEMENT					;
%constant int ATTRIBUTE 				;
%constant int TEXT                      ;
%constant int CDATA_SECTION 			;
%constant int ENTITY_REFERENCE          ;
%constant int ENTITY 					;
%constant int PROCESSING_INSTRUCTION	;
%constant int COMMENT 					;
%constant int DOCUMENT                  ;
%constant int DOCUMENT_TYPE 			;
%constant int DOCUMENT_FRAGMENT 		;
%constant int NOTATION                  ;
// Not in Mozilla/W3C original
%constant int ATTRIBUTE_VALUE 			;
%constant int ELEMENT_END_TAG           ;
%constant int ATTRIBUTE_NODES           ;
%constant int ELEMENT_TEXT              ;
%constant int ELEMENT_NODES             ;
%constant int ALL_NODE_TYPES 			;
%constant int REMOVE_NODE_TYPES         ;


/*---------------------
--- DOM functions ---
---------------------*/
void    domRebuildWait          ( int timeoutInMs = 30000 );
void    domNewSearch			();
std::vector<int> domFindAll     ( const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps );
std::vector<int> domFindAll     ( const std::string& sSequence, int iPostMatchSteps );
std::vector<int> domFindAll     ( const std::string& sSequence );
void    domContinueSearch		();
int		domFindParentPos		( 	int iLevelsUp = 1 );
int		domFindParent			( 	int iLevelsUp = 1 );

/*int		domFindNext			( 	int iCount, const crawl::DomSeq& seq, int iNodeTypes );*/

int		domFindNext             ( 	int iCount, const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps, int iNodeTypes );
int		domFindNext             ( 	int iCount, const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps );
int		domFindNext             ( 	int iCount, const std::string& sSequence, const std::string& sCompareFun );
int		domFindNext             ( 	int iCount, const std::string& sSequence, int iPostMatchSteps );
int		domFindNext             ( 	int iCount, const std::string& sSequence );
int		domFindNext             ( 	const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps, int iNodeTypes );
int		domFindNext             ( 	const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps );
int		domFindNext             ( 	const std::string& sSequence, const std::string& sCompareFun );
int		domFindNext             ( 	const std::string& sSequence, int iPostMatchSteps );
int		domFindNext             ( 	const std::string& sSequence );
int		domFindPrev             ( 	const std::string& sSequence, const std::string& sCompareFun );
int		domFindNextParams       ( 	int iCount, const std::string& sSequence, const std::string& sArgs );

int		domFind                 ( 	int iCount, const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps, int iNodeTypes );
int		domFind                 ( 	int iCount, const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps );
int		domFind                 ( 	int iCount, const std::string& sSequence, const std::string& sCompareFun );
int		domFind                 ( 	int iCount, const std::string& sSequence, int iPostMatchSteps );
int		domFind                 ( 	int iCount, const std::string& sSequence );
int		domFind                 ( 	const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps, int iNodeTypes );
int		domFind                 ( 	const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps );
int		domFind                 ( 	const std::string& sSequence, const std::string& sCompareFun );
int		domFind                 ( 	const std::string& sSequence, int iPostMatchSteps );
int		domFind                 ( 	const std::string& sSequence );

int		domFindPos              ( 	int iCount, const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps, int iNodeTypes );
int		domFindPos              ( 	int iCount, const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps );
int		domFindPos              ( 	int iCount, const std::string& sSequence, const std::string& sCompareFun );
int		domFindPos              ( 	int iCount, const std::string& sSequence, int iPostMatchSteps );
int		domFindPos              ( 	int iCount, const std::string& sSequence );
int		domFindPos              ( 	const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps, int iNodeTypes );
int		domFindPos              ( 	const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps );
int		domFindPos              ( 	const std::string& sSequence, const std::string& sCompareFun );
int		domFindPos              ( 	const std::string& sSequence, int iPostMatchSteps );
int		domFindPos              ( 	const std::string& sSequence );

int		domFindNextPos			( 	int iCount, const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps, int iNodeTypes );
int		domFindNextPos			( 	int iCount, const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps );
int		domFindNextPos			( 	int iCount, const std::string& sSequence, const std::string& sCompareFun );
int		domFindNextPos			( 	int iCount, const std::string& sSequence, int iPostMatchSteps );
int		domFindNextPos			( 	int iCount, const std::string& sSequence );
int		domFindNextPos			( 	const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps, int iNodeTypes );
int		domFindNextPos			( 	const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps );
int		domFindNextPos			( 	const std::string& sSequence, const std::string& sCompareFun );
int		domFindNextPos			( 	const std::string& sSequence, int iPostMatchSteps );
int		domFindNextPos			( 	const std::string& sSequence );
int		domFindPrevPos			( 	const std::string& sSequence, const std::string& sCompareFun );


int		domClickInput			(  	int iCount 	)																													;
int		domClickInputNext		(  	int iCount 	)																													;
int		domSetInput             (  	int iCount,	const std::string& sValue 	)																						;
int		domSetInputNext			(  	int iCount,	const std::string& sValue 	)																						;
int		domSetInput             (  	int iCount,	int iValue 					)																						;
int		domSetInputNext			(  	int iCount,	int iValue 					)																						;
int		domStep                 (  	int iCount, int iNodeTypes = ALL_NODE_TYPES )																					;
bool    domAtEnd                ()																																	;
void	domRangePushElement		( int iElementPos );
void	domRangePush			( int iStartPos, int iStopPos );
void	domRangePop             ();
void	domPointerPush			()																																	;
int		domPointerPop           ()																																	;
int 	domSize                 () 																																	;
int 	domEndPos               () 																																	;
int 	domPos                  () 																																	;
int		domPosSet				( int iNewPos )																														;
int		domStartPosSet			( int iStartPos )																													;
int		domStartPos  			()																														;
void	domStartPosClear		( )																																	;
int		domStopPosSet			( int iStopPos )																													;
int		domStopPos              ()																														;
void	domStopPosClear			()																																	;
void    domSetAtEnd             ();
int		domContinuePos          ();
int		domThisElementPos       ();
int		domThisElementPos       ( int pos );
int		domOwnerPos             ( int iLevelsUp = 1 );
int		domPosToOwner			( int iLevelsUp = 1 );
int		domParentPos            ( int iLevelsUp = 1 );
int		domPosToParent			( int iLevelsUp = 1 );

/*
-----------------------------------
--- LookForWord (lfw) functions ---
----------------------------------- */
void		lfwMatchWholeWordsOnlySet(bool matchWholeWordsOnly);
void        lfwClear                ();
void        lfwClear                (const std::string& contextName);
void        lfwClear                (const std::string& contextName, const std::string& referenceName);
void        lfwAddWord              (const std::string& contextName, const std::string& referenceName,
                                     const std::string& word, const std::string& compareFun, int nodeTypes);
void		lfwRemoveWord           (const std::string& contextName, const std::string& referenceName,
                                     const std::string& word);
void        lfwGetDataFunctionSet   (const std::string& contextName, const std::string& getDataFallbackFunction);
void		lfwGetDataFallbackFunctionSet (const std::string& contextName, const std::string& getDataFallbackFunction);
int         lfwDomFind              (const std::string& referenceName);
int         lfwDomFindNext          (const std::string& referenceName);
std::string lfwOutputValueFind      (const std::string& referenceName);
std::string lfwOutputValueFindNext  (const std::string& referenceName);
std::string lfwPreSequence          (const std::string& referenceName);
void        lfwPreSequenceSet       (const std::string& referenceName, const std::string& lfwPreSequence);
std::string lfwPostSequence         (const std::string& referenceName);
void        lfwPostSequenceSet      (const std::string& referenceName, const std::string& lfwPostSequence);
std::vector<int>   lfwDomFindAllPositions  (const std::string& referenceName);
//int         lfwDomStartPos          ();
//void        lfwDomStartPosSet       (int pos);
//int         lfwDomStopPos           ();
//void        lfwDomStopPosSet        (int pos);

std::string lfwStartPosDomSeq       (const std::string& contextName);
void        lfwStartPosDomSeqSet    (const std::string& contextName, const std::string& lfwStartPosDomSeq);
std::string lfwStopPosDomSeq        (const std::string& contextName);
void        lfwStopPosDomSeqSet     (const std::string& contextName, const std::string& lfwStopPosDomSeq);

/*
-------------------------------------
--- DOM Sequence create functions ---
------------------------------------- */
void		domSeqCreate			( 	int iCount, const std::string& sName, const std::string& sSequence,
                                        const std::string& sCompareFun, int iPostMatchSteps, int iNodeTypes, const std::string& sCommaChar  );
void		domSeqCreate			( 	int iCount, const std::string& sName, const std::string& sSequence,
                                        const std::string& sCompareFun, int iPostMatchSteps, int iNodeTypes  );
void		domSeqCreate			( 	int iCount, const std::string& sName, const std::string& sSequence,
                                        const std::string& sCompareFun, int iPostMatchSteps  );
void		domSeqCreate			( 	int iCount, const std::string& sName, const std::string& sSequence, const std::string& sCompareFun );
void		domSeqCreate			( 	int iCount, const std::string& sName, const std::string& sSequence, int iPostMatchSteps );
void		domSeqCreate			( 	int iCount, const std::string& sName, const std::string& sSequence );
void		domSeqCreate			( 	const std::string& sName, const std::string& sSequence, const std::string& sCompareFun,
                                        int iPostMatchSteps, int iNodeTypes, const std::string& sCommaChar  );
void		domSeqCreate			( 	const std::string& sName, const std::string& sSequence, const std::string& sCompareFun,
                                        int iPostMatchSteps, int iNodeTypes  );
void		domSeqCreate			( 	const std::string& sName, const std::string& sSequence, const std::string& sCompareFun,
                                        int iPostMatchSteps  );
void		domSeqCreate			( 	const std::string& sName, const std::string& sSequence, const std::string& sCompareFun );
void		domSeqCreate			( 	const std::string& sName, const std::string& sSequence, int iPostMatchSteps );
void		domSeqCreate			( 	const std::string& sName, const std::string& sSequence );

bool 		domSeqExists 			( 	const std::string& sName );


/*
----------------------------------
--- Element children functions ---
---------------------------------  */

std::vector<int> nodeChildren       ( int iSearchDir = crawl::NEAREST_AUTO );
std::vector<int> nodeChildren       ( const std::string& tagName, int iSearchDir = crawl::NEAREST_AUTO );
std::vector<int> nodeChildrenRecur  ( const std::string& tagName, int iSearchDir = crawl::NEAREST_AUTO );
int              nodeEndElementPos  ( int iSearchDir = crawl::NEAREST_AUTO );

std::vector<int> posChildElements   ( int iDomPos);
std::vector<int> posChildren        ( const std::string& tagName, int iDomPos );
std::vector<int> posChildrenRecur   ( const std::string& tagName, int iDomPos );
int              posEndElementPos   ( int iDomPos );


/*
------------------------------------
--- Current (dom) node functions ---
------------------------------------ */
%constant int NEAREST_FORWARD	;
%constant int NEAREST_BACKWARD	;
%constant int NEAREST_BOTH		;
%constant int NEAREST_PARENT	;
%constant int NEAREST_AUTO		;
%constant int NEAREST_THIS_NODE	;
%constant int FWD	;
%constant int REV	;

int         nodeType                ()																																	;
bool		nodeClickLoadHref       ( int iSearchDir = NEAREST_AUTO );
bool		nodeClick               ( int iSearchDir = NEAREST_AUTO );
bool		userClick				( int iSearchDir = NEAREST_AUTO );
bool        userMouseEvent          ( int eventType, int button, int buttons, int modifiers, int iSearchDir = NEAREST_AUTO );
bool		nodeClickWait           ( int timeoutInMs = 30000, int iSearchDir = NEAREST_AUTO );
bool		nodeMouseEvent          ( const std::string& sEvent );
bool		nodeMouseEvent          ( const std::string& sEvent, int iSearchDir );
bool		nodeMouseEvent          ( const std::string& sEvent, int iButton, int iSearchDir );
bool		nodeJavaScriptEvaluate	( const std::string& sJavaScript, int iSearchDir = NEAREST_AUTO );
bool 		inputSet                ( const std::string& sValue, int iSearchDir = NEAREST_AUTO )																		;
bool 		inputSet                ( int iValue, int iSearchDir = NEAREST_AUTO )																		;
std::string innerHtml               ( int iSearchDir = NEAREST_AUTO );
bool 		innerHtmlSet 			( const std::string& sValue, int iSearchDir = NEAREST_AUTO );
std::string innerText               ( int iSearchDir = NEAREST_AUTO );
bool 		innerTextSet 			( const std::string& sValue, int iSearchDir = NEAREST_AUTO );
bool 		inputValue              ( const std::string& sValue, int iSearchDir = NEAREST_AUTO )																		;
bool 		inputValue              ( int iValue, int iSearchDir = NEAREST_AUTO )																		;
bool		formSubmit              ( int iSearchDir = NEAREST_AUTO )																									;
bool		formReset               ( int iSearchDir = NEAREST_AUTO )																									;
int         selectLength            ( int iSearchDir = NEAREST_AUTO )																									;
int         selectSelectedIndex     ( int iSearchDir = NEAREST_AUTO )																									;
std::string	selectSelectedText      ( int iSearchDir = NEAREST_AUTO );
std::string	selectSelectedValue     ( int iSearchDir = NEAREST_AUTO );
int 		selectSelectedDomPos    ( int iSearchDir = NEAREST_AUTO )																									;
bool		selectSelect            ( int iIndex, int iSearchDir = NEAREST_AUTO )																						;
bool		selectIndex             ( int iIndex, int iSearchDir = NEAREST_AUTO )																						;
bool		selectIndexWait         ( int iIndex, int timeoutInMs = 30000, int iSearchDir = NEAREST_AUTO );
bool		selectOption            ( int iSearchDir = NEAREST_AUTO )																									;
bool		selectOptionWait		( int timeoutInMs = 30000, int iSearchDir = NEAREST_AUTO );
int         selectIndexOfOption		( int iSearchDir = NEAREST_AUTO );
/* bool		doActionPos		( int iDomPos, const std::string& sAction, const std::string& sParam1, const std::string& sParam2, int iSearchDir = NEAREST_AUTO );*/
bool		doAction                ( const std::string& sAction, const std::string& sParam1, const std::string& sParam2, int iSearchDir );
bool		doAction                ( const std::string& sAction, const std::string& sParam1, const std::string& sParam2 );
bool		doAction                ( const std::string& sAction, const std::string& sParam1, int iSearchDir = NEAREST_AUTO );
bool		doAction                ( const std::string& sAction, int iSearchDir = NEAREST_AUTO );
float		nodeGeomPosX			( int iSearchDir = NEAREST_AUTO );
float		nodeGeomPosY			( int iSearchDir = NEAREST_AUTO );
float		nodeGeomWidth			( int iSearchDir = NEAREST_AUTO );
float		nodeGeomHeight			( int iSearchDir = NEAREST_AUTO );

/*
--------------------------------------
--- DOM doActionFindNext functions ---
-------------------------------------- */
int		doActionFindNext			(	int iCount, const std::string& sSequence, const std::string& sAction, const std::string& sParam1,
                                        const std::string& sParam2, int iSearchDir );
int		doActionFindNext			(	int iCount, const std::string& sSequence, const std::string& sAction, const std::string& sParam1,
                                        const std::string& sParam2 );
int		doActionFindNext			(	int iCount, const std::string& sSequence, const std::string& sAction, const std::string& sParam1,
                                        int iSearchDir = NEAREST_AUTO );
int		doActionFindNext			(	int iCount, const std::string& sSequence, const std::string& sAction, int iSearchDir = NEAREST_AUTO );

int		doActionFindNext			(	const std::string& sSequence, const std::string& sAction, const std::string& sParam1,
                                                                                const std::string& sParam2, int iSearchDir );
int		doActionFindNext			(	const std::string& sSequence, const std::string& sAction, const std::string& sParam1,
                                                                                const std::string& sParam2 );
int		doActionFindNext			(	const std::string& sSequence, const std::string& sAction, const std::string& sParam1,
                                                                                int iSearchDir = NEAREST_AUTO );
int		doActionFindNext			(	const std::string& sSequence, const std::string& sAction, int iSearchDir = NEAREST_AUTO );


/*
----------------------------------
--- DOM doActionFind functions ---
---------------------------------- */
int		doActionFind				(	int iCount, const std::string& sSequence, const std::string& sAction, const std::string& sParam1,
                                        const std::string& sParam2, int iSearchDir );
int		doActionFind				(	int iCount, const std::string& sSequence, const std::string& sAction, const std::string& sParam1,
                                        const std::string& sParam2 );
int		doActionFind				(	int iCount, const std::string& sSequence, const std::string& sAction, const std::string& sParam1,
                                        int iSearchDir = NEAREST_AUTO );
int		doActionFind				(	int iCount, const std::string& sSequence, const std::string& sAction, int iSearchDir = NEAREST_AUTO );

int		doActionFind				(	const std::string& sSequence, const std::string& sAction, const std::string& sParam1,
                                                                                const std::string& sParam2, int iSearchDir );
int		doActionFind				(	const std::string& sSequence, const std::string& sAction, const std::string& sParam1,
                                                                                const std::string& sParam2 );
int		doActionFind				(	const std::string& sSequence, const std::string& sAction, const std::string& sParam1,
                                                                                int iSearchDir = NEAREST_AUTO );
int		doActionFind				(	const std::string& sSequence, const std::string& sAction, int iSearchDir = NEAREST_AUTO );

/*
-----------------------------------
--- DOM Action create functions ---
----------------------------------- */
void		domActionCreate			( 	const std::string& sName, const std::string& sAction, const std::string& sParam1,
                                        const std::string& sParam2, int iSearchDir );
void		domActionCreate			( 	const std::string& sName, const std::string& sAction, const std::string& sParam1,
                                        const std::string& sParam2 );
void		domActionCreate			( 	const std::string& sName, const std::string& sAction, const std::string& sParam1,
                                        int iSearchDir = NEAREST_AUTO );
void		domActionCreate			( 	const std::string& sName, const std::string& sAction, int iSearchDir = NEAREST_AUTO );


/*
--------------------------------------------------------------------
--- Modifier create functions (OutputModifier create functions)  ---
-------------------------------------------------------------------- */
void modifierCreate					(	const std::string& sModifierID, const std::string& sMainipFunID, const std::string& sManipParam1,
                                        const std::string& sManipParam2, const std::string& sManipParam3, const std::string& sManipParam4 );
void modifierCreate					(	const std::string& sModifierID, const std::string& sMainipFunID, const std::string& sManipParam1,
                                        const std::string& sManipParam2, const std::string& sManipParam3 );
void modifierCreate					(	const std::string& sModifierID, const std::string& sMainipFunID, const std::string& sManipParam1,
                                        const std::string& sManipParam2 );
void modifierCreate					(	const std::string& sModifierID, const std::string& sMainipFunID, const std::string& sManipParam1 );
void modifierCreate					(	const std::string& sModifierID, const std::string& sMainipFunID );

/*
-----------------------------
--- nodeXX misc functions ---
----------------------------- */
int         nodeLevel               ();
std::string	nodeXPath               ();

/*
------------------------------
--- nodeValuePos functions ---
------------------------------ */
std::string	nodeValuePos		( int iDomPos, const std::string& sModifierID, const std::string& sManipParam1,
                                  const std::string& sManipParam2, const std::string& sManipParam3,
                                  const std::string& sManipParam4 );
std::string	nodeValuePos		( int iDomPos, const std::string& sModifierID, const std::string& sManipParam1,
                                  const std::string& sManipParam2, const std::string& sManipParam3 );
std::string	nodeValuePos		( int iDomPos, const std::string& sModifierID, const std::string& sManipParam1,
                                  const std::string& sManipParam2 );
std::string	nodeValuePos		( int iDomPos, const std::string& sModifierID, const std::string& sManipParam1 );
std::string	nodeValuePos		( int iDomPos, const std::string& sModifierID );
std::string	nodeValuePos		( int iDomPos );

std::string	posValue			( int iDomPos, const std::string& sModifierID, const std::string& sManipParam1,
                                  const std::string& sManipParam2, const std::string& sManipParam3,
                                  const std::string& sManipParam4 );
std::string	posValue			( int iDomPos, const std::string& sModifierID, const std::string& sManipParam1,
                                  const std::string& sManipParam2, const std::string& sManipParam3 );
std::string	posValue			( int iDomPos, const std::string& sModifierID, const std::string& sManipParam1,
                                  const std::string& sManipParam2 );
std::string	posValue			( int iDomPos, const std::string& sModifierID, const std::string& sManipParam1 );
std::string	posValue			( int iDomPos, const std::string& sModifierID );
std::string	posValue			( int iDomPos );

/*
---------------------------
--- nodeValue functions ---
--------------------------- */
std::string	nodeValue			( const std::string& sModifierID, const std::string& sManipParam1,
                                  const std::string& sManipParam2, const std::string& sManipParam3,
                                  const std::string& sManipParam4 );
std::string	nodeValue			( const std::string& sModifierID, const std::string& sManipParam1,
                                  const std::string& sManipParam2, const std::string& sManipParam3 );
std::string	nodeValue			( const std::string& sModifierID, const std::string& sManipParam1,
                                  const std::string& sManipParam2 );
std::string	nodeValue			( const std::string& sModifierID, const std::string& sManipParam1 );
std::string	nodeValue			( const std::string& sModifierID );
std::string	nodeValue			();

/*
---------------------------------
--- nodeValueParent functions ---
--------------------------------- */
std::string	nodeValueParent			( int iLevelsUp, const std::string& sModifierID, const std::string& sManipParam1,
                                      const std::string& sManipParam2, const std::string& sManipParam3,
                                      const std::string& sManipParam4 );
std::string	nodeValueParent			( int iLevelsUp, const std::string& sModifierID, const std::string& sManipParam1,
                                      const std::string& sManipParam2, const std::string& sManipParam3 );
std::string	nodeValueParent			( int iLevelsUp, const std::string& sModifierID, const std::string& sManipParam1,
                                      const std::string& sManipParam2 );
std::string	nodeValueParent			( int iLevelsUp, const std::string& sModifierID, const std::string& sManipParam1 );
std::string	nodeValueParent			( int iLevelsUp, const std::string& sModifierID );
std::string	nodeValueParent			( int iLevelsUp );

/*
---------------------------------
--- nodeAttribute functions ---
--------------------------------- */
std::string	nodeAttribute			( const std::string& sAttribute, const std::string& sModifierID, const std::string& sManipParam1,
                                      const std::string& sManipParam2, const std::string& sManipParam3,
                                      const std::string& sManipParam4 );
std::string	nodeAttribute			( const std::string& sAttribute, const std::string& sModifierID, const std::string& sManipParam1,
                                      const std::string& sManipParam2, const std::string& sManipParam3 );
std::string	nodeAttribute			( const std::string& sAttribute, const std::string& sModifierID, const std::string& sManipParam1,
                                      const std::string& sManipParam2 );
std::string	nodeAttribute			( const std::string& sAttribute, const std::string& sModifierID, const std::string& sManipParam1 );
std::string	nodeAttribute			( const std::string& sAttribute, const std::string& sModifierID );
std::string	nodeAttribute			( const std::string& sAttribute );

std::string	posAttribute			( int iDomPos, const std::string& sAttribute, const std::string& sModifierID,
                                      const std::string& sManipParam1,const std::string& sManipParam2,
                                      const std::string& sManipParam3, const std::string& sManipParam4 );
std::string	posAttribute			( int iDomPos, const std::string& sAttribute, const std::string& sModifierID,
                                      const std::string& sManipParam1, const std::string& sManipParam2,
                                      const std::string& sManipParam3 );
std::string	posAttribute			( int iDomPos, const std::string& sAttribute, const std::string& sModifierID,
                                      const std::string& sManipParam1, const std::string& sManipParam2 );
std::string	posAttribute			( int iDomPos, const std::string& sAttribute, const std::string& sModifierID,
                                      const std::string& sManipParam1 );
std::string	posAttribute			( int iDomPos, const std::string& sAttribute, const std::string& sModifierID );
std::string	posAttribute			( int iDomPos, const std::string& sAttribute );


/*
---------------------------------
--- nodeText functions ---
--------------------------------- */
std::string	nodeText                ( const std::string& sModifierID, const std::string& sManipParam1,
                                      const std::string& sManipParam2, const std::string& sManipParam3,
                                      const std::string& sManipParam4 );
std::string	nodeText                ( const std::string& sModifierID, const std::string& sManipParam1,
                                      const std::string& sManipParam2, const std::string& sManipParam3 );
std::string	nodeText                ( const std::string& sModifierID, const std::string& sManipParam1,
                                      const std::string& sManipParam2 );
std::string	nodeText                ( const std::string& sModifierID, const std::string& sManipParam1 );
std::string	nodeText                ( const std::string& sModifierID );
std::string	nodeText                ();


/*
-----------------------------
--- nodeCompare functions ---
----------------------------- */
bool		nodeCompare				( const std::string& sPattern, const std::string& sCompareFun, const std::string& sModifierID,
                                      const std::string& sManipParam1, const std::string& sManipParam2,
                                      const std::string& sManipParam3, const std::string& sManipParam4 );
bool		nodeCompare				( const std::string& sPattern, const std::string& sCompareFun, const std::string& sModifierID,
                                      const std::string& sManipParam1, const std::string& sManipParam2,
                                      const std::string& sManipParam3 );
bool		nodeCompare				( const std::string& sPattern, const std::string& sCompareFun, const std::string& sModifierID,
                                      const std::string& sManipParam1, const std::string& sManipParam2 );
bool		nodeCompare				( const std::string& sPattern, const std::string& sCompareFun, const std::string& sModifierID,
                                      const std::string& sManipParam1 );
bool		nodeCompare				( const std::string& sPattern, const std::string& sCompareFun, const std::string& sModifierID );
bool		nodeCompare				( const std::string& sPattern, const std::string& sCompareFun );

/*-----------------------
--- Parse functions ---
-----------------------*/
%constant int MATCH_FIRST		;
%constant int MATCH_LAST		;
bool		parseRegex			(	int iCount, const std::string& sRegex,		int postMarkerPos = MATCH_FIRST		)												;
bool		iparseRegex			(	int iCount, const std::string& sRegex,		int postMarkerPos = MATCH_FIRST		)												;
bool		parseToRegex		(	int iCount, const std::string& sRegex,		int postMarkerPos = MATCH_FIRST		)												;
bool		iparseToRegex		(	int iCount, const std::string& sRegex,		int postMarkerPos = MATCH_FIRST		)												;
bool		parseToString		(	int iCount, const std::string& sSubstring,	int postMarkerPos = MATCH_FIRST		)												;
bool		iparseToString		(	int iCount, const std::string& sSubstring,	int postMarkerPos = MATCH_FIRST		)												;
bool		parseToEnd			()																																	;
std::string	getParseMatch		( int iMatchNumber )																												;
std::string	getParseRest		()																																	;
int			getParseMatchCount	()																																	;

/*------------------------
--- Text functions ---
------------------------*/
void		textNewSearch		()																																	;
bool		findBegin			(	int iCount, const std::string& sSearchFor, 	int setBeginToPos = MATCH_LAST		)												;
bool		findEnd				(	int iCount, const std::string& sSearchFor, 	int setBeginToPos = MATCH_FIRST		)												;
bool		findBeginNext		(	int iCount, const std::string& sSearchFor, 	int setBeginToPos = MATCH_LAST 		)												;
bool		findEndNext			(	int iCount, const std::string& sSearchFor, 	int setBeginToPos = MATCH_FIRST		)												;
bool		ifindBegin			(	int iCount, const std::string& sSearchFor, 	int setBeginToPos = MATCH_LAST		)												;
bool		ifindEnd			(	int iCount, const std::string& sSearchFor, 	int setBeginToPos = MATCH_FIRST		)												;
bool		ifindBeginNext		(	int iCount, const std::string& sSearchFor, 	int setBeginToPos = MATCH_LAST 		)												;
bool		ifindEndNext		(	int iCount, const std::string& sSearchFor, 	int setBeginToPos = MATCH_FIRST		)												;
bool		findRegexBegin		(	int iCount, const std::string& sRegex,		int setBeginToPos = MATCH_LAST		)												;
bool		findRegexEnd		(	int iCount, const std::string& sRegex, 		int setBeginToPos = MATCH_FIRST		)												;
bool		findRegexBeginNext	(	int iCount, const std::string& sRegex,		int setBeginToPos = MATCH_LAST		)												;
bool		findRegexEndNext	(	int iCount, const std::string& sRegex, 		int setBeginToPos = MATCH_FIRST		)												;
bool		stepBegin			(	int iCount	)																													;
bool		stepEnd				(	int iCount	)																													;


/*-----------------------------
--- (URL) queue functions ---
-----------------------------*/
%constant int LINK_TYPE_LOCAL		;
%constant int LINK_TYPE_EXTERNAL	;
%constant int LINK_TYPE_ALL			;

int			urlQueueSize			();
int			urlQueueSizeProcessed	();
bool        urlQueueAlreadyProcessed( const std::string& sUrl );
void		urlQueueClear			()	;
std::string	urlQueueFront			()	;
void		urlQueueAppend			(	int iLinkType, const std::string& sUrlsMatch ="", const std::string& sCompareFun = DefaultCompareFun )	;
void		urlQueueAppendUnique	(	int iLinkType, const std::string& sUrlsMatch ="", const std::string& sCompareFun = DefaultCompareFun )	;
void		urlQueueAppend			(	const std::string& sUrl		)	;
void		urlQueueAppendUnique	(	const std::string& sUrl		)	;
void		urlQueuePrepend			(	const std::string& sUrl		)	;
void		urlQueuePrependUnique	(	const std::string& sUrl		)	;

/*-----------------------------
--- linksGetter functions ---
-----------------------------*/
void		linksGetterDebugPrint	();

/*
--------------------------
--- valueSet functions ---
-------------------------- */
void		valueSet				( const std::string& sValue );

/*
--------------------------
--- valueGet functions ---
-------------------------- */
std::string	valueGet				( const std::string& sModifierID, const std::string& sManipParam1, const std::string& sManipParam2,
                                      const std::string& sManipParam3, const std::string& sManipParam4 );
std::string	valueGet				( const std::string& sModifierID, const std::string& sManipParam1, const std::string& sManipParam2,
                                      const std::string& sManipParam3 );
std::string	valueGet				( const std::string& sModifierID, const std::string& sManipParam1, const std::string& sManipParam2 );
std::string	valueGet				( const std::string& sModifierID, const std::string& sManipParam1 );
std::string	valueGet				( const std::string& sModifierID );
std::string	valueGet				();

/*
------------------------------
--- valueCompare functions ---
------------------------------ */
bool	valueCompare				( const std::string& sPattern, const std::string& sCompareFun, const std::string& sModifierID,
                                      const std::string& sManipParam1, const std::string& sManipParam2, const std::string& sManipParam3,
                                      const std::string& sManipParam4 );
bool	valueCompare				( const std::string& sPattern, const std::string& sCompareFun, const std::string& sModifierID,
                                      const std::string& sManipParam1, const std::string& sManipParam2, const std::string& sManipParam3 );
bool	valueCompare				( const std::string& sPattern, const std::string& sCompareFun, const std::string& sModifierID,
                                      const std::string& sManipParam1, const std::string& sManipParam2 );
bool	valueCompare				( const std::string& sPattern, const std::string& sCompareFun, const std::string& sModifierID,
                                      const std::string& sManipParam1 );
bool	valueCompare				( const std::string& sPattern, const std::string& sCompareFun, const std::string& sModifierID );
bool	valueCompare				( const std::string& sPattern, const std::string& sCompareFun );

/*
--------------------------------
--- outputValueGet functions ---
-------------------------------- */
std::string	outputValueContextGet	( const std::string& sFieldName, const std::string& sContextName );
std::string	outputValueGet  		( const std::string& sFieldName, const std::string& sModifierID, const std::string& sManipParam1,
                                      const std::string& sManipParam2, const std::string& sManipParam3, const std::string& sManipParam4 );
std::string	outputValueGet			( const std::string& sFieldName, const std::string& sModifierID, const std::string& sManipParam1,
                                      const std::string& sManipParam2, const std::string& sManipParam3 );
std::string	outputValueGet			( const std::string& sFieldName, const std::string& sModifierID, const std::string& sManipParam1,
                                      const std::string& sManipParam2 );
std::string	outputValueGet			( const std::string& sFieldName, const std::string& sModifierID, const std::string& sManipParam1 );
std::string	outputValueGet			( const std::string& sFieldName, const std::string& sModifierID );
std::string	outputValueGet			( const std::string& sFieldName);

/*
------------------------------
--- Modify value functions ---
------------------------------ */
std::string	valueModify		( const std::string& sModifierID, const std::string& sManipParam1, const std::string& sManipParam2,
                                                          const std::string& sManipParam3, const std::string& sManipParam4 );
std::string	valueModify		( const std::string& sModifierID, const std::string& sManipParam1, const std::string& sManipParam2,
                                                          const std::string& sManipParam3 );
std::string	valueModify		( const std::string& sModifierID, const std::string& sManipParam1, const std::string& sManipParam2 );
std::string	valueModify		( const std::string& sModifierID, const std::string& sManipParam1 );
std::string	valueModify		( const std::string& sModifierID );


/*
-------------------------
--- Context functions ---
------------------------- */
void        dataPushContext		( std::string sContext, std::string const& sUnit = "" );
void        dataPushContextAlias	( const std::string& sContext, const std::string& sContextAlias, const std::string& sUnit = "" );
void        dataPopContext		();

void        contextBegin                ( std::string sContextName );
void        contextEnd                  ();
void        contextOutputSaveAs         ( const std::string& sContextName );
void        contextFallbackOutputLoad   ( const std::string& sContextName );
void        contextFallbackOutputClear  ();
std::string contextFallbackValueGet     ( const std::string& sFieldName );
void        contextFallbackValueSet     ( const std::string& sFieldName, const std::string& sValue ) ;
bool        contextFallbackValueExists  ( const std::string& sFieldName );
void        contextFallbackValueDelete  ( const std::string& sFieldName );
bool        contextSavedOutputExists    ( const std::string& sContextName );
void        contextSavedOutputDelete    ( const std::string& sContextName );

/*
------------------------
--- Output functions ---
------------------------ */
/*void		outputDirectUnit		( const std::string& sFieldName, const std::string& sValue, const std::string& sUnit,
                                                  const std::string& sModifierID, const std::string& sManipParam1, const std::string& sManipParam2,
                                                  const std::string& sManipParam3, const std::string& sManipParam4 );
void		outputDirectUnit		( const std::string& sFieldName, const std::string& sValue, const std::string& sUnit,
                                                  const std::string& sModifierID, const std::string& sManipParam1, const std::string& sManipParam2,
                                                  const std::string& sManipParam3 );
void		outputDirectUnit		( const std::string& sFieldName, const std::string& sValue, const std::string& sUnit,
                                                  const std::string& sModifierID, const std::string& sManipParam1, const std::string& sManipParam2 );
void		outputDirectUnit		( const std::string& sFieldName, const std::string& sValue, const std::string& sUnit,
                                                  const std::string& sModifierID, const std::string& sManipParam1 );
void		outputDirectUnit		( const std::string& sFieldName, const std::string& sValue, const std::string& sUnit,
                                                  const std::string& sModifierID );
void		outputDirectUnit		( const std::string& sFieldName, const std::string& sValue, const std::string& sUnit );*/
/*---*/
void		outputDirect			( const std::string& sFieldName, const std::string& sValue, const std::string& sModifierID,
                                                  const std::string& sManipParam1, const std::string& sManipParam2, const std::string& sManipParam3,
                                                  const std::string& sManipParam4 );
void		outputDirect			( const std::string& sFieldName, const std::string& sValue, const std::string& sModifierID,
                                                  const std::string& sManipParam1, const std::string& sManipParam2, const std::string& sManipParam3 );
void		outputDirect			( const std::string& sFieldName, const std::string& sValue, const std::string& sModifierID,
                                                  const std::string& sManipParam1, const std::string& sManipParam2 );
void		outputDirect			( const std::string& sFieldName, const std::string& sValue, const std::string& sModifierID,
                                                  const std::string& sManipParam1 );
void		outputDirect			( const std::string& sFieldName, const std::string& sValue, const std::string& sModifierID );
void		outputDirect			( const std::string& sFieldName, const std::string& sValue );

/* --- */
/*void		outputValueUnit			( const std::string& sFieldName, const std::string& sUnit, const std::string& sModifierID,
                                                  const std::string& sManipParam1, const std::string& sManipParam2,
                                                  const std::string& sManipParam3, const std::string& sManipParam4 );
void		outputValueUnit			( const std::string& sFieldName, const std::string& sUnit, const std::string& sModifierID,
                                                  const std::string& sManipParam1, const std::string& sManipParam2,
                                                  const std::string& sManipParam3 );
void		outputValueUnit			( const std::string& sFieldName, const std::string& sUnit, const std::string& sModifierID,
                                                  const std::string& sManipParam1, const std::string& sManipParam2 );
void		outputValueUnit			( const std::string& sFieldName, const std::string& sUnit, const std::string& sModifierID,
                                                 const std::string& sManipParam1 );
void		outputValueUnit			( const std::string& sFieldName, const std::string& sUnit, const std::string& sModifierID );
void		outputValueUnit			( const std::string& sFieldName, const std::string& sUnit );*/

/* --- */
void		outputValue			( const std::string& sFieldName, const std::string& sModifierID, const std::string& sManipParam1,
                                                  const std::string& sManipParam2, const std::string& sManipParam3, const std::string& sManipParam4 );
void		outputValue			( const std::string& sFieldName, const std::string& sModifierID, const std::string& sManipParam1,
                                                  const std::string& sManipParam2, const std::string& sManipParam3 );
void		outputValue			( const std::string& sFieldName, const std::string& sModifierID, const std::string& sManipParam1,
                                                 const std::string& sManipParam2 );
void		outputValue			( const std::string& sFieldName, const std::string& sModifierID, const std::string& sManipParam1 );
void		outputValue			( const std::string& sFieldName, const std::string& sModifierID );
void		outputValue			( const std::string& sFieldName );


/*
-------------------------------------
--- outputValueFindNext functions ---
------------------------------------- */

int		outputValueFindNext	( int iCount, const std::string& sSequence,	const std::string& sFieldName, const std::string& sManipFun,
                                          const std::string& sManipParam1, const std::string& sManipParam2, const std::string& sManipParam3,
                                          const std::string& sManipParam4 );
int		outputValueFindNext	( int iCount, const std::string& sSequence,	const std::string& sFieldName, const std::string& sManipFun,
                                          const std::string& sManipParam1, const std::string& sManipParam2, const std::string& sManipParam3	);
int		outputValueFindNext	( int iCount, const std::string& sSequence,	const std::string& sFieldName, const std::string& sManipFun,
                                          const std::string& sManipParam1, const std::string& sManipParam2	);
int		outputValueFindNext	( int iCount, const std::string& sSequence,	const std::string& sFieldName, const std::string& sManipFun,
                                          const std::string& sManipParam1 );
int		outputValueFindNext	( int iCount, const std::string& sSequence,	const std::string& sFieldName, const std::string& sManipFun );
int		outputValueFindNext	( int iCount, const std::string& sSequence,	const std::string& sFieldName );



int		outputValueFindNext	( const std::string& sSequence,	const std::string& sFieldName, const std::string& sManipFun,
                                          const std::string& sManipParam1, const std::string& sManipParam2, const std::string& sManipParam3,
                                          const std::string& sManipParam4 );
int		outputValueFindNext	( const std::string& sSequence,	const std::string& sFieldName, const std::string& sManipFun,
                                          const std::string& sManipParam1, const std::string& sManipParam2, const std::string& sManipParam3	);
int		outputValueFindNext	( const std::string& sSequence,	const std::string& sFieldName, const std::string& sManipFun,
                                          const std::string& sManipParam1, const std::string& sManipParam2	);
int		outputValueFindNext	( const std::string& sSequence,	const std::string& sFieldName, const std::string& sManipFun,
                                          const std::string& sManipParam1 );
int		outputValueFindNext	( const std::string& sSequence,	const std::string& sFieldName, const std::string& sManipFun );
int		outputValueFindNext	( const std::string& sSequence,	const std::string& sFieldName );

/*
---------------------------------
--- outputValueFind functions ---
--------------------------------- */
int		outputValueFind		( int iCount, const std::string& sSequence,	const std::string& sFieldName, const std::string& sManipFun,
                                         const std::string& sManipParam1, const std::string& sManipParam2, const std::string& sManipParam3,
                                         const std::string& sManipParam4 );
int		outputValueFind		( int iCount, const std::string& sSequence,	const std::string& sFieldName, const std::string& sManipFun,
                                          const std::string& sManipParam1, const std::string& sManipParam2, const std::string& sManipParam3	);
int		outputValueFind		( int iCount, const std::string& sSequence,	const std::string& sFieldName, const std::string& sManipFun,
                                          const std::string& sManipParam1, const std::string& sManipParam2	);
int		outputValueFind		( int iCount, const std::string& sSequence,	const std::string& sFieldName, const std::string& sManipFun,
                                          const std::string& sManipParam1 );
int		outputValueFind		( int iCount, const std::string& sSequence,	const std::string& sFieldName, const std::string& sManipFun );
int		outputValueFind		( int iCount, const std::string& sSequence,	const std::string& sFieldName );


int		outputValueFind		( const std::string& sSequence,	const std::string& sFieldName, const std::string& sManipFun,
                                          const std::string& sManipParam1, const std::string& sManipParam2, const std::string& sManipParam3,
                                          const std::string& sManipParam4 );
int		outputValueFind		( const std::string& sSequence,	const std::string& sFieldName, const std::string& sManipFun,
                                          const std::string& sManipParam1, const std::string& sManipParam2, const std::string& sManipParam3	);
int		outputValueFind		( const std::string& sSequence,	const std::string& sFieldName, const std::string& sManipFun,
                                          const std::string& sManipParam1, const std::string& sManipParam2	);
int		outputValueFind		( const std::string& sSequence,	const std::string& sFieldName, const std::string& sManipFun,
                                          const std::string& sManipParam1 );
int		outputValueFind		( const std::string& sSequence,	const std::string& sFieldName, const std::string& sManipFun );
int		outputValueFind		( const std::string& sSequence,	const std::string& sFieldName );

/*----------------------------
--- Javascript functions ---
----------------------------*/
bool 		javaScriptExecuteRetVal	( const std::string& sScript, std::string& sScriptReturnValue 	)							;
bool 		javaScriptExecute       ( const std::string& sScript									)							;
bool 		javaScriptExecuteWait	( const std::string& sScript, int timeoutInMs = 120000);

/*-------------------------
--- Utility functions ---
-------------------------*/
int 		curlPostUploadFileSimple    ( const std::string& sURL, const std::string& sFieldName, const std::string& sFilePath 	) 	;
bool 		gzCompressFile              ( const std::string& sSrcFilePath, const std::string& sDstFilePath ) 						;
bool 		gzUnCompressFile            ( const std::string& sSrcFilePath, const std::string& sDstFilePath )						;

/*
--------------------------
--- Settings functions ---
-------------------------- */
void        settingDelete           (	const std::string& sName );
void        settingSet              (	const std::string& sName, const std::string& sValue );
std::string settingGet              (	const std::string& sName, const std::string& defaultValue = "" );
bool        settingExists           (	const std::string& sName );
bool        hasSetting              (	const std::string& sName );
bool        settingBoolGet          (   const std::string& sName );


/*------------------------
--- Config functions ---
------------------------*/
std::string configValueGet          ( const std::string& sName );
void		configValueSet          ( const std::string& sName, const std::string& sValue );
bool        configValueBoolGet      ( const std::string& sName );
void 		configUrlStart          ( const std::string& sUrl	)																;
void 		configUrlUploadDataSet	( const std::string& sUrl	)																;
std::string configUrlUploadDataGet	()																							;
void 		configDisableLoadImages	()																							;
void 		configForceLoadImages	()																							;
void 		configAddIncludeUrl     ( const std::string& sPattern, const std::string& sCompareFun )	;
void 		configAddExcludeUrl     ( const std::string& sPattern, const std::string& sCompareFun )	;
void		configForceSendXmlData	();
void        configAjaxPageLoadDeltaTime ( int iMilliSeconds );
void		configReloadTimeOut     ( int iMinutes, int iSecs )																	;
void		configKeepActiveInterval( int iSecs )																				;
void		configProgressOutputSet	( bool bEnable )																			;
void		configDebugOutputSet	( bool bEnable )																			;
bool		configDebugOutputGet	()																							;
void 		configParseDecimalPointSet( const std::string& sDecimalPoint  	)													;
void 		configParseThousandsSepSet( const std::string& sThousandsSep 	)													;
void		configOutputEncloseCDATA( bool bDoEncloseInCDATA )																	;
void		configOutputWriteToFile ( bool bDoWriteOutputToFile );
std::string configGetRunMode            ();
void 		configInsertEndTagNodes ( bool bInsertEndTagNodes )																	;
void 		configSkipEmptyNodes 	( bool bSkipEmptyNodes )																	;
void 		configTrimBlanks 		( bool bTrimBlanks )																		;
void		configLocaleSettingsSet ( const std::string& country_or_currency_code );

/*-----------------------
--- Debug functions ---
-----------------------*/
void        locatedPositionsClear   ()                                                                                          ;
void		domDebugPrint			( const std::string& sFileName="" 								)							;
void		nodeDebugPrint			( int iNodesBefore, int iNodesAfter, bool bPrintNodeTypes = false )							;
void		nodeDebugPrint			( int iNodesAround=10, bool bPrintNodeTypes = false )										;
std::string	nodeValueDebug			( int iNodesBefore, int iNodesAfter, bool bPrintNodeTypes = false )							;
std::string	nodeValueDebug			( int iNodesAround=10, bool bPrintNodeTypes = false )										;

void        dbgSimpleTestFunction       ();
void        dbgIntParam                 (int i);
void        dbgCurrentMinerSetPointer   (const std::string& sMinerPointer);

// --------------------------------------
// --- PUBLIC: General info functions ---
// --------------------------------------
//int                                 infoMiningDoneStatus            ();
std::string     infoTimeMiningStartedUtc();
//std::string                         infoTimeLastPageLoadStarted     ();
//std::string                         infoTimeLastPageLoadFinished    ();
//std::string                         infoCurrentLoadingUrl           ();
//std::string                         infoLatestFullyLoadedUrl        ();
int         infoPageLoadsTotal      ();
int         infoLastNetworkError    ();
