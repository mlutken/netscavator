#ifndef SCRIPTCRAWL_H
#define SCRIPTCRAWL_H

#include <string>
#include <vector>
#include <QKeyEvent>
#include <QtTest/QtTest>
#include <QtTest/QTestEventList>

#include <cpaf_libs/utils/cpaf_string_utils.hpp>
#include <dom_constants.h>
#include <DomNodeIF.h>
#include <ScriptMinerIF.h>
#include <parser/LinksGetter.h>
#include <parser/DomSeq.h>


/*! \xxfile scriptcrawl.h
 *
 * Core crawler functions exported from C++.
 * 
 * sdfg sd 
 * sdg sd
 * g sdg sdg 
 * hsg
 * 
 */



void*                       testPhpArrayGet ();
std::vector<int>            testArrayGet    ();
std::vector<std::string>    testArrayStrGet    ();

double              average         (std::vector<int> v);
std::vector<double> half            (const std::vector<double>& v);
void                halve_in_place  (std::vector<double>& v);

static const std::string DefaultCompareFun("contains");


// --- String compare functions ---
using crawl::string_compare::equals_fn;
using crawl::string_compare::iequals_fn;
using crawl::string_compare::contains_fn;
using crawl::string_compare::icontains_fn;
using crawl::string_compare::startsWith_fn;
using crawl::string_compare::istartsWith_fn;
using crawl::string_compare::endsWith_fn;
using crawl::string_compare::iendsWith_fn;
using crawl::string_compare::lessThan_fn;
using crawl::string_compare::ilessThan_fn;
using crawl::string_compare::greaterThan_fn;
using crawl::string_compare::igreaterThan_fn;
using crawl::string_compare::regexSearch_fn;


static const bool bTrimBlanksPreset = true;


/* ----------------------
   --- Init functions ---
   ---------------------- */
void            dbgCurrentMinerSetPointer       (const std::string& sMinerPointer);
void            dbgIntParam                     (int i);
void            currentMinerSetPointer          (const std::string& sMinerPointer);
void            currentMinerSetRaw              (void* pMiner);
void 			initMining                      ();
void 			addMiner                        (std::string sMinerName);
void 			runMiners                       ();
void            scriptHtmlEntitiesReplaceAdd    (const std::string& lookFor, const std::string& replaceWith);
void            scriptHtmlEntitiesReplaceClear  ();


// -------------------------------
// --- Info/settings functions ---
// -------------------------------
std::string     outputName                          ();

/*----------------------
--- Misc functions ---
----------------------*/
////void 			useLocale			( const std::string& sLocale )	;
std::string     pageSource                          ();
std::string		currentMiner                        ();
std::string		currentDataFile                     ();
void            triggerPageLoaded                   ();
void            triggerPageLoadedWait               (int timeoutInMs = 3000);
void            waitSleep                           (int timeInMs);
void            waitForDomReady                     (int timeoutInMs = 30000);
void            waitForJavascriptDone               ();
void            clearCookies                        ();
int             configDelayPageLoadedTime           ();
void            configDelayPageLoadedTimeSet        (int milliseconds);
int             networkActivityCounter              ();


/*
-------------------------
--- Browser functions ---
------------------------- */
/* Key constants for user key events */
const int KEY_ESCAPE        = Qt::Key_Escape;
const int KEY_TAB           = Qt::Key_Tab;
const int KEY_BACKTAB       = Qt::Key_Backtab;
const int KEY_BACKSPACE     = Qt::Key_Backspace;
const int KEY_RETURN        = Qt::Key_Return;
const int KEY_ENTER         = Qt::Key_Enter;
const int KEY_INSERT        = Qt::Key_Insert;
const int KEY_DELETE        = Qt::Key_Delete;
const int KEY_PAUSE         = Qt::Key_Pause;
const int KEY_PRINT         = Qt::Key_Print;
const int KEY_SYSREQ        = Qt::Key_SysReq;
const int KEY_CLEAR         = Qt::Key_Clear;
const int KEY_HOME          = Qt::Key_Home;
const int KEY_END           = Qt::Key_End;
const int KEY_LEFT          = Qt::Key_Left;
const int KEY_UP            = Qt::Key_Up;
const int KEY_RIGHT         = Qt::Key_Right;
const int KEY_DOWN          = Qt::Key_Down;
const int KEY_PAGEUP        = Qt::Key_PageUp;
const int KEY_PAGEDOWN      = Qt::Key_PageDown;
const int KEY_SHIFT         = Qt::Key_Shift;
const int KEY_CONTROL       = Qt::Key_Control;
const int KEY_META          = Qt::Key_Meta;
const int KEY_ALT           = Qt::Key_Alt;
const int KEY_CAPSLOCK      = Qt::Key_CapsLock;
const int KEY_NUMLOCK       = Qt::Key_NumLock;
const int KEY_SCROLLLOCK    = Qt::Key_ScrollLock;
const int KEY_F1            = Qt::Key_F1;
const int KEY_F2            = Qt::Key_F2;
const int KEY_F3            = Qt::Key_F3;
const int KEY_F4            = Qt::Key_F4;
const int KEY_F5            = Qt::Key_F5;
const int KEY_F6            = Qt::Key_F6;
const int KEY_F7            = Qt::Key_F7;
const int KEY_F8            = Qt::Key_F8;
const int KEY_F9            = Qt::Key_F9;
const int KEY_F10           = Qt::Key_F10;
const int KEY_F11           = Qt::Key_F11;
const int KEY_F12           = Qt::Key_F12;
const int KEY_F13           = Qt::Key_F13;
const int KEY_F14           = Qt::Key_F14;
const int KEY_F15           = Qt::Key_F15;
const int KEY_F16           = Qt::Key_F16;
const int KEY_F17           = Qt::Key_F17;
const int KEY_F18           = Qt::Key_F18;
const int KEY_F19           = Qt::Key_F19;
const int KEY_F20           = Qt::Key_F20;
const int KEY_F21           = Qt::Key_F21;
const int KEY_F22           = Qt::Key_F22;
const int KEY_F23           = Qt::Key_F23;
const int KEY_F24           = Qt::Key_F24;
const int KEY_F25           = Qt::Key_F25;
const int KEY_F26           = Qt::Key_F26;
const int KEY_F27           = Qt::Key_F27;
const int KEY_F28           = Qt::Key_F28;
const int KEY_F29           = Qt::Key_F29;
const int KEY_F30           = Qt::Key_F30;
const int KEY_F31           = Qt::Key_F31;
const int KEY_F32           = Qt::Key_F32;
const int KEY_F33           = Qt::Key_F33;
const int KEY_F34           = Qt::Key_F34;
const int KEY_F35           = Qt::Key_F35;
const int KEY_SUPER_L       = Qt::Key_Super_L;
const int KEY_SUPER_R       = Qt::Key_Super_R;
const int KEY_MENU          = Qt::Key_Menu;
const int KEY_HYPER_L       = Qt::Key_Hyper_L;
const int KEY_HYPER_R       = Qt::Key_Hyper_R;
const int KEY_HELP          = Qt::Key_Help;
const int KEY_DIRECTION_L   = Qt::Key_Direction_L;
const int KEY_DIRECTION_R   = Qt::Key_Direction_R;
const int KEY_SPACE         = Qt::Key_Space;
const int KEY_ANY           = Qt::Key_Any;
const int KEY_EXCLAM        = Qt::Key_Exclam;
const int KEY_QUOTEDBL      = Qt::Key_QuoteDbl;
const int KEY_NUMBERSIGN    = Qt::Key_NumberSign;
const int KEY_DOLLAR        = Qt::Key_Dollar;
const int KEY_PERCENT       = Qt::Key_Percent;
const int KEY_AMPERSAND     = Qt::Key_Ampersand;
const int KEY_APOSTROPHE    = Qt::Key_Apostrophe;
const int KEY_PARENLEFT     = Qt::Key_ParenLeft;
const int KEY_PARENRIGHT    = Qt::Key_ParenRight;
const int KEY_ASTERISK      = Qt::Key_Asterisk;
const int KEY_PLUS          = Qt::Key_Plus;
const int KEY_COMMA         = Qt::Key_Comma;
const int KEY_MINUS         = Qt::Key_Minus;
const int KEY_PERIOD        = Qt::Key_Period;
const int KEY_SLASH         = Qt::Key_Slash;
const int KEY_0             = Qt::Key_0;
const int KEY_1             = Qt::Key_1;
const int KEY_2             = Qt::Key_2;
const int KEY_3             = Qt::Key_3;
const int KEY_4             = Qt::Key_4;
const int KEY_5             = Qt::Key_5;
const int KEY_6             = Qt::Key_6;
const int KEY_7             = Qt::Key_7;
const int KEY_8             = Qt::Key_8;
const int KEY_9             = Qt::Key_9;
const int KEY_COLON         = Qt::Key_Colon;
const int KEY_SEMICOLON     = Qt::Key_Semicolon;
const int KEY_LESS          = Qt::Key_Less;
const int KEY_EQUAL         = Qt::Key_Equal;
const int KEY_GREATER       = Qt::Key_Greater;
const int KEY_QUESTION      = Qt::Key_Question;
const int KEY_AT            = Qt::Key_At;
const int KEY_A             = Qt::Key_A;
const int KEY_B             = Qt::Key_B;
const int KEY_C             = Qt::Key_C;
const int KEY_D             = Qt::Key_D;
const int KEY_E             = Qt::Key_E;
const int KEY_F             = Qt::Key_F;
const int KEY_G             = Qt::Key_G;
const int KEY_H             = Qt::Key_H;
const int KEY_I             = Qt::Key_I;
const int KEY_J             = Qt::Key_J;
const int KEY_K             = Qt::Key_K;
const int KEY_L             = Qt::Key_L;
const int KEY_M             = Qt::Key_M;
const int KEY_N             = Qt::Key_N;
const int KEY_O             = Qt::Key_O;
const int KEY_P             = Qt::Key_P;
const int KEY_Q             = Qt::Key_Q;
const int KEY_R             = Qt::Key_R;
const int KEY_S             = Qt::Key_S;
const int KEY_T             = Qt::Key_T;
const int KEY_U             = Qt::Key_U;
const int KEY_V             = Qt::Key_V;
const int KEY_W             = Qt::Key_W;
const int KEY_X             = Qt::Key_X;
const int KEY_Y             = Qt::Key_Y;
const int KEY_Z             = Qt::Key_Z;
const int KEY_BRACKETLEFT   = Qt::Key_BracketLeft;
const int KEY_BACKSLASH     = Qt::Key_Backslash;
const int KEY_BRACKETRIGHT  = Qt::Key_BracketRight;
const int KEY_ASCIICIRCUM   = Qt::Key_AsciiCircum;
const int KEY_UNDERSCORE    = Qt::Key_Underscore;
const int KEY_QUOTELEFT     = Qt::Key_QuoteLeft;
const int KEY_BRACELEFT     = Qt::Key_BraceLeft;
const int KEY_BAR           = Qt::Key_Bar;
const int KEY_BRACERIGHT    = Qt::Key_BraceRight;
const int KEY_ASCIITILDE    = Qt::Key_AsciiTilde;


/* --- Key modifier constants for user events --- */
const int NO_MODIFIER = Qt::NoModifier;
const int SHIFT_MODIFIER = Qt::ShiftModifier;
const int CONTROL_MODIFIER = Qt::ControlModifier;
const int ALT_MODIFIER = Qt::AltModifier;
const int META_MODIFIER = Qt::MetaModifier;
const int KEYPAD_MODIFIER = Qt::KeypadModifier;
const int GROUP_SWITCH_MODIFIER = Qt::GroupSwitchModifier;

/* --- Key event types for user key events --- */
const int KEY_DOWN_EVENT = QTest::KeyAction::Press;
const int KEY_UP_EVENT = QTest::KeyAction::Release;
const int KEY_CLICK_EVENT = QTest::KeyAction::Click;

/* --- Mouse buttons for user mouse events --- */
const int NO_BUTTON = Qt::NoButton;
const int LEFT_BUTTON = Qt::LeftButton;
const int RIGHT_BUTTON = Qt::RightButton;
const int MID_BUTTON = Qt::MiddleButton;
//const int MID_BUTTON = Qt::MidButton;

/* --- Mouse event types for user mouse events --- */
const int MOUSE_DOWN_EVENT = QEvent::MouseButtonPress;
const int MOUSE_UP_EVENT = QEvent::MouseButtonRelease;
const int MOUSE_DBLCLICK_EVENT = QEvent::MouseButtonDblClick;
const int MOUSE_MOVE_EVENT = QEvent::MouseMove;
const int MOUSE_CLICK_EVENT = crawl::MOUSE_CLICK_EVENT;

void            browserScroll       ( int x, int y );
int             browserScrollPosXGet();
int             browserScrollPosYGet();
void			browserHide			()								;
void			browserShow			()								;
void			browserSetSize		(int x, int y)					;
int				browserGetSizeX		()								;
int				browserGetSizeY		()								;
bool			browserGoBack		()								;
void            browserKeyEvent     (int eventType, int key, int modifiers);
void            browserMouseEvent   (int eventType, float xpos, float ypos, int button, int buttons, int modifiers);
void            browserFocusActivate();
void            browserFocusDeactivate();

/*------------------------------------------
--- String operators/compare functions ---
------------------------------------------*/
bool 			valuesCompare		( const std::string& sInput, const std::string& sTest, const std::string& sCompareFun );

/*
-------------------------
--- Sitemap functions ---
-------------------------*/
std::vector<std::string>    allSitemaps();

std::vector<std::string>    siteMapUrls                 ();
void                        siteMapUrlsSet              (const std::vector<std::string> &siteMapUrls);
void                        siteMapUrlAppend            (const std::string &siteMapUrl);
std::vector<std::string>    siteMapLocationUrls         ();
void                        siteMapLocationsInclude     (const std::string& urlPattern, const std::string& compareFun = DefaultCompareFun );
void                        siteMapLocationsExclude     (const std::string& urlPattern, const std::string& compareFun = DefaultCompareFun );


/*
--------------------------------
--- Navigation (nav) functions ---
----------------------------------*/
const int   ATTR 					= 1;
void        navActiveNavigatorSet   ( const std::string& sNavigatorName );
std::string navActiveNavigatorGet   ();
void        navJavascriptExecuteCreate ( const std::string& sNavActionName );
void        navUrlLoadCreate        ( const std::string& sNavActionName, const std::string& sBaseUrl = "" );
void        navInputOptionsCreate   ( const std::string& sNavActionName );
void        navDropDownSelectCreate ( const std::string& sNavActionName );
void        navDomPosClickCreate    ( const std::string& sNavActionName, const std::string& sFindNextDomPosSequence );
void        navDomClickNextCreate   ( const std::string& sNavActionName, const std::string& sFindNextDomPosSequence );
void        navAutoInputCreate      ( const std::string& sNavActionName, const std::string& sCharsList, int iMinLength, int iMaxLength );

void        navAttributeNamesCreate ( const std::string& sAttrNames, const std::string& sDelimiter = "," );

void        navCurrentStateIndicesSet ( const std::string& sState );
std::string navCurrentStateIndicesGet ();
void        navCurrentStateSet      ( const std::string& sState, const std::string& sDelimiter );
void        navCurrentStateSet      ( const std::string& sState );
void        navBeginStateSet        ( const std::string& sState, const std::string& sDelimiter );
void        navBeginStateSet        ( const std::string& sState );
void        navEndStateSet          ( const std::string& sState, const std::string& sDelimiter );
void        navEndStateSet          ( const std::string& sState );

void        navOptionResourceAdd    ( const std::string& sResourcePath, const std::string& sScriptFilterFunction,  bool bForceDownload  );
void        navOptionAdd            ( int iCount, const std::string& sValue, const std::string& sSearchFor  );
void        navOptionAdd            ( int iCount, const std::string& sValue );
void        navOptionAdd            ( const std::string& sValue, const std::string& sSearchFor );
void        navOptionAdd            ( const std::string& sValue );
void        navOptionAdd            ( int iCount );

void        navOptionAdd            ( int iCount, const std::string& sValue, const std::string& sSearchFor,
                                      int attrStart, const std::string& sAttributes, const std::string& sDelimiter = "," );
void        navOptionAdd            ( int iCount, const std::string& sValue,
                                      int attrStart, const std::string& sAttributes, const std::string& sDelimiter = "," );
void        navOptionAdd            ( const std::string& sValue, const std::string& sSearchFor,
                                      int attrStart, const std::string& sAttributes, const std::string& sDelimiter = "," );
void        navOptionAdd            ( const std::string& sValue,
                                      int attrStart, const std::string& sAttributes, const std::string& sDelimiter = "," );
void        navOptionAdd            ( int iCount, int attrStart, const std::string& sAttributes, const std::string& sDelimiter = "," );

std::string navDomTextValueGet      ( const std::string& sNavActionName ) ;
std::string navDomValueGet          ( const std::string& sNavActionName ) ;
std::string navValueGet             ( const std::string& sNavActionName ) ;
std::string navSearchForGet         ( const std::string& sNavActionName ) ;
int         navCountGet             ( const std::string& sNavActionName ) ;
int         navOptionIndexGet       ( const std::string& sNavActionName ) ;
int         navStateIndexGet        () ;
int         navNumStatesGet         ();
int         navLastStateIndexGet    ();


std::string navAttributeGet         ( const std::string& sNavActionName, const std::string& sAttrName ) ;
std::string navAttributeGet         ( const std::string& sAttrName );
bool        navNextState            ();
bool        navDoAction             ( const std::string& sNavActionName ) ;
bool        navDoActionClickAll     ( const std::string& sNavActionName ) ;
std::string navStateString          ();
void        navStart                ();
void        navReset                ();
bool        navNavigationDone       ();
void        navAutoInputIncreaseLength ( bool bDoIncreaseLength );


/*
----------------------------------------------
--- String modifier/manipulation functions ---
---------------------------------------------- */
std::string		trimDefault_fn 		( const std::string& sInput 	);
std::string		raw_fn				( const std::string& sInput		);
std::string		toUpper_fn			( const std::string& sInput		);
std::string		toLower_fn			( const std::string& sInput		);
std::string		trimEnds_fn			( const std::string& sInput		);
std::string		trimLeft_fn			( const std::string& sInput		);
std::string		trimRight_fn		( const std::string& sInput		);
std::string		trimYear_fn			( const std::string& sInput 	);

std::string		trimInteger_fn		( const std::string& sInput		);
std::string		trimNumber_fn		( const std::string& sInput		);


std::string 	trimCharsEnds_fn	( const std::string& sInput, const std::string& sCharsToTrim );
std::string 	trimCharsLeft_fn	( const std::string& sInput, const std::string& sCharsToTrim );
std::string 	trimCharsRight_fn	( const std::string& sInput, const std::string& sCharsToTrim );
std::string 	trimRegex_fn		( const std::string& sInput, const std::string& sRegex );
std::string 	itrimRegex_fn		( const std::string& sInput, const std::string& sRegex );
std::string		append_fn			( const std::string& sInput, const std::string& sString	);
std::string		prepend_fn			( const std::string& sInput, const std::string& sString	);
std::string		eraseFirst_fn		( const std::string& sInput, const std::string& sSearchFor	);
std::string		ieraseFirst_fn		( const std::string& sInput, const std::string& sSearchFor	);
std::string		eraseLast_fn		( const std::string& sInput, const std::string& sSearchFor	);
std::string		ieraseLast_fn		( const std::string& sInput, const std::string& sSearchFor	);
std::string		eraseAll_fn			( const std::string& sInput, const std::string& sSearchFor	);
std::string		ieraseAll_fn		( const std::string& sInput, const std::string& sSearchFor	);
std::string		eraseRegex_fn		( const std::string& sInput, const std::string& sSearchFor	);
std::string		eraseAllRegex_fn	( const std::string& sInput, const std::string& sSearchFor	);

std::string 	trimBetween_fn      ( const std::string& sInput, const std::string& sBegin, 		const std::string& sEnd );
std::string 	trimBetweenCount_fn ( const std::string& sInput, const std::string& sBegin, 		const std::string& sEnd, const std::string& sCount );
std::string 	trimBetweenCount_fn ( const std::string& sInput, const std::string& sBegin, 		const std::string& sEnd, int iCount );
std::string 	trimIntegerCustom_fn( const std::string& sInput, const std::string& iBase, 			const std::string& sThousandsSep);
std::string 	trimNumberCustom_fn	( const std::string& sInput, const std::string& sDecimalPoint, 	const std::string& sThousandsSep);
std::string		replaceFirst_fn		( const std::string& sInput, const std::string& sSearchFor,		const std::string& sReplaceWith	);
std::string		ireplaceFirst_fn	( const std::string& sInput, const std::string& sSearchFor,		const std::string& sReplaceWith	);
std::string		replaceLast_fn		( const std::string& sInput, const std::string& sSearchFor,		const std::string& sReplaceWith	);
std::string		ireplaceLast_fn		( const std::string& sInput, const std::string& sSearchFor,		const std::string& sReplaceWith	);
std::string		replaceAll_fn		( const std::string& sInput, const std::string& sSearchFor,		const std::string& sReplaceWith	);
std::string		ireplaceAll_fn		( const std::string& sInput, const std::string& sSearchFor,		const std::string& sReplaceWith	);
std::string		replaceRegex_fn		( const std::string& sInput, const std::string& sSearchFor,		const std::string& sReplaceWith	);
std::string		replaceAllRegex_fn	( const std::string& sInput, const std::string& sSearchFor,		const std::string& sReplaceWith	);

std::string		eraseNth_fn			( const std::string& sInput, const std::string& sSearchFor,	int iNth 	);
std::string		eraseNth_fn         ( const std::string& sInput, const std::string& sSearchFor, const std::string& sNth 	);
std::string		ieraseNth_fn		( const std::string& sInput, const std::string& sSearchFor,	int iNth 	);
std::string		ieraseNth_fn        ( const std::string& sInput, const std::string& sSearchFor, const std::string& sNth 	);

std::string		replaceNth_fn		( const std::string& sInput, const std::string& sSearchFor,	const std::string& sReplaceWith, int iNth	);
std::string		replaceNth_fn       ( const std::string& sInput, const std::string& sSearchFor,	const std::string& sReplaceWith ,const std::string& sNth	);
std::string		ireplaceNth_fn		( const std::string& sInput, const std::string& sSearchFor,	const std::string& sReplaceWith, int iNth	);
std::string		ireplaceNth_fn      ( const std::string& sInput, const std::string& sSearchFor,	const std::string& sReplaceWith, const std::string& sNth	);


/*
---------------------
--- URL functions ---
--------------------- */
std::string		urlSite();
std::string		urlCurrent();
bool			urlLoad		( const std::string sURL	);
bool			urlLoadWait	( const std::string sURL, int timeoutInMs = 30000);



/*
---------------------
--- DOM functions ---
--------------------- */
/* OLD (DOM constants) For backwards compatibility */
const int ELEMENT_NODE 					= crawl::DomNodeTypes::ELEMENT                  ;
const int ATTRIBUTE_NODE 				= crawl::DomNodeTypes::ATTRIBUTE 				;
const int TEXT_NODE 					= crawl::DomNodeTypes::TEXT 					;
const int CDATA_SECTION_NODE 			= crawl::DomNodeTypes::CDATA_SECTION 			;
const int ENTITY_REFERENCE_NODE 		= crawl::DomNodeTypes::ENTITY_REFERENCE 		;
const int ENTITY_NODE 					= crawl::DomNodeTypes::ENTITY 					;
const int PROCESSING_INSTRUCTION_NODE	= crawl::DomNodeTypes::PROCESSING_INSTRUCTION 	;
const int COMMENT_NODE 					= crawl::DomNodeTypes::COMMENT                  ;
const int DOCUMENT_NODE 				= crawl::DomNodeTypes::DOCUMENT 				;
const int DOCUMENT_TYPE_NODE 			= crawl::DomNodeTypes::DOCUMENT_TYPE 			;
const int DOCUMENT_FRAGMENT_NODE 		= crawl::DomNodeTypes::DOCUMENT_FRAGMENT 		;
const int NOTATION_NODE 				= crawl::DomNodeTypes::NOTATION 				;
const int ATTRIBUTE_VALUE_NODE          = crawl::DomNodeTypes::ATTRIBUTE_VALUE          ;

/* --- DOM constants --- */
const int ELEMENT 					= crawl::DomNodeTypes::ELEMENT                  ;
const int ATTRIBUTE 				= crawl::DomNodeTypes::ATTRIBUTE 				;
const int TEXT                      = crawl::DomNodeTypes::TEXT 					;
const int CDATA_SECTION 			= crawl::DomNodeTypes::CDATA_SECTION 			;
const int ENTITY_REFERENCE          = crawl::DomNodeTypes::ENTITY_REFERENCE 		;
const int ENTITY 					= crawl::DomNodeTypes::ENTITY 					;
const int PROCESSING_INSTRUCTION	= crawl::DomNodeTypes::PROCESSING_INSTRUCTION 	;
const int COMMENT 					= crawl::DomNodeTypes::COMMENT                  ;
const int DOCUMENT                  = crawl::DomNodeTypes::DOCUMENT 				;
const int DOCUMENT_TYPE 			= crawl::DomNodeTypes::DOCUMENT_TYPE 			;
const int DOCUMENT_FRAGMENT 		= crawl::DomNodeTypes::DOCUMENT_FRAGMENT 		;
const int NOTATION                  = crawl::DomNodeTypes::NOTATION 				;
// Not in Mozilla/W3C original
const int ATTRIBUTE_VALUE           = crawl::DomNodeTypes::ATTRIBUTE_VALUE          ;
const int ELEMENT_END_TAG           = crawl::DomNodeTypes::ELEMENT_END_TAG          ;
const int ATTRIBUTE_NODES           = crawl::DomNodeTypes::ATTRIBUTE_NODES          ;
const int ELEMENT_TEXT              = crawl::DomNodeTypes::ELEMENT_TEXT             ;
const int ELEMENT_NODES             = crawl::DomNodeTypes::ELEMENT_NODES            ;
const int ALL_NODE_TYPES 			= crawl::DomNodeTypes::ALL_NODE_TYPES 			;
const int REMOVE_NODE_TYPES         = crawl::DomNodeTypes::REMOVE_NODE_TYPES        ;

void        domRebuildWait          ( int timeoutInMs = 30000 );
void		domNewSearch			();
std::vector<int> domFindAll         ( const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps );
std::vector<int> domFindAll         ( const std::string& sSequence, int iPostMatchSteps );
std::vector<int> domFindAll         ( const std::string& sSequence );
void        domContinueSearch		();
int			domFindParentPos		( 	int iLevelsUp = 1 );
int			domFindParent			( 	int iLevelsUp = 1 );

int			domFindNextParams		( 	int iCount, const crawl::DomSeq& seq, const std::string& sArgs, int iNodeTypes );

int			domFindNext				( 	int iCount, const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps, int iNodeTypes );
int			domFindNext				( 	int iCount, const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps );
int			domFindNext				( 	int iCount, const std::string& sSequence, const std::string& sCompareFun );
int			domFindNext				( 	int iCount, const std::string& sSequence, int iPostMatchSteps );
int			domFindNext				( 	int iCount, const std::string& sSequence );
int			domFindNext				( 	const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps, int iNodeTypes );
int			domFindNext				( 	const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps );
int			domFindNext				( 	const std::string& sSequence, const std::string& sCompareFun );
int			domFindNext				( 	const std::string& sSequence, int iPostMatchSteps );
int			domFindNext				( 	const std::string& sSequence );
int			domFindPrev				( 	const std::string& sSequence, const std::string& sCompareFun );
int			domFindNextParams       ( 	int iCount, const std::string& sSequence, const std::string& sArgs );


int			domFind					( 	int iCount, const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps, int iNodeTypes );
int			domFind					( 	int iCount, const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps );
int			domFind					( 	int iCount, const std::string& sSequence, const std::string& sCompareFun );
int			domFind					( 	int iCount, const std::string& sSequence, int iPostMatchSteps );
int			domFind					( 	int iCount, const std::string& sSequence );
int			domFind					( 	const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps, int iNodeTypes );
int			domFind					( 	const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps );
int			domFind					( 	const std::string& sSequence, const std::string& sCompareFun );
int			domFind					( 	const std::string& sSequence, int iPostMatchSteps );
int			domFind					( 	const std::string& sSequence );

int			domFindPos              ( 	int iCount, const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps, int iNodeTypes );
int			domFindPos              ( 	int iCount, const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps );
int			domFindPos              ( 	int iCount, const std::string& sSequence, const std::string& sCompareFun );
int			domFindPos              ( 	int iCount, const std::string& sSequence, int iPostMatchSteps );
int			domFindPos              ( 	int iCount, const std::string& sSequence );
int			domFindPos              ( 	const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps, int iNodeTypes );
int			domFindPos              ( 	const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps );
int			domFindPos              ( 	const std::string& sSequence, const std::string& sCompareFun );
int			domFindPos              ( 	const std::string& sSequence, int iPostMatchSteps );
int			domFindPos              ( 	const std::string& sSequence );


int			domFindNextPos			( 	int iCount, const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps, int iNodeTypes );
int			domFindNextPos			( 	int iCount, const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps );
int			domFindNextPos			( 	int iCount, const std::string& sSequence, const std::string& sCompareFun );
int			domFindNextPos			( 	int iCount, const std::string& sSequence, int iPostMatchSteps );
int			domFindNextPos			( 	int iCount, const std::string& sSequence );
int			domFindNextPos			( 	const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps, int iNodeTypes );
int			domFindNextPos			( 	const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps );
int			domFindNextPos			( 	const std::string& sSequence, const std::string& sCompareFun );
int			domFindNextPos			( 	const std::string& sSequence, int iPostMatchSteps );
int			domFindNextPos			( 	const std::string& sSequence );
int			domFindPrevPos			( 	const std::string& sSequence, const std::string& sCompareFun );

int			domClickInput			(  	int iCount 	)																													;
int			domClickInputNext		(  	int iCount 	)																													;
int			domSetInput				(  	int iCount,	const std::string& sValue 	)																						;
int			domSetInputNext			(  	int iCount,	const std::string& sValue 	)																						;
int			domSetInput				(  	int iCount,	int iValue 					)																						;
int			domSetInputNext			(  	int iCount,	int iValue 					)																						;
int			domStep					(  	int iCount, int iNodeTypes = ALL_NODE_TYPES )																					;
bool		domAtEnd				()																																	;
void		domRangePushElement		( int iElementPos );
void		domRangePush			( int iStartPos, int iStopPos );
void		domRangePop             ();
void		domPointerPush			()																																	;
int			domPointerPop			()																																	;
int 		domSize					() 																																	;
int 		domEndPos				() 																																	;
int 		domPos                  () 																																	;
int			domPosSet				( int iNewPos )																														;
int			domStartPosSet			( int iStartPos )																													;
int			domStartPos             ()																														;
void		domStartPosClear		( )																																	;
int			domStopPosSet			( int iStopPos )																													;
int			domStopPos              ()																														;
void		domStopPosClear			()																																	;
void		domSetAtEnd             ()																																	;
int			domContinuePos          ();
int			domThisElementPos       ();
int			domThisElementPos       ( int pos );
int			domOwnerPos             ( int iLevelsUp = 1 );
int			domPosToOwner			( int iLevelsUp = 1 );
int			domParentPos            ( int iLevelsUp = 1 );
int			domPosToParent			( int iLevelsUp = 1 );

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
void        lfwGetDataFunctionSet   (const std::string& contextName, const std::string& getDataFunction);
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
int         lfwDomStartPos          ();
void        lfwDomStartPosSet       (int pos);
int         lfwDomStopPos           ();
void        lfwDomStopPosSet        (int pos);

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
// --- Auto search for node constants ---
const int NEAREST_FORWARD	= crawl::NEAREST_FORWARD	;
const int NEAREST_BACKWARD	= crawl::NEAREST_BACKWARD 	;
const int NEAREST_BOTH		= crawl::NEAREST_BOTH		;
const int NEAREST_PARENT	= crawl::NEAREST_PARENT		;
const int NEAREST_AUTO		= crawl::NEAREST_AUTO		;
const int NEAREST_THIS_NODE	= crawl::NEAREST_THIS_NODE	;
const int FWD				=  1	;
const int REV				= -1	;

int			nodeType				()																																	;
bool		nodeClickLoadHref		( int iSearchDir = NEAREST_AUTO );
bool		nodeClick				( int iSearchDir = NEAREST_AUTO )																			;
bool		userClick				( int iSearchDir = NEAREST_AUTO );
bool        userMouseEvent          ( int eventType, int button, int buttons, int modifiers, int iSearchDir = NEAREST_AUTO );
bool		nodeClickWait			( int timeoutInMs = 30000, int iSearchDir = NEAREST_AUTO )																			;
bool		nodeMouseEvent			( const std::string& sEvent );
bool		nodeMouseEvent			( const std::string& sEvent, int iSearchDir );
bool		nodeMouseEvent			( const std::string& sEvent, int iButton, int iSearchDir );
bool		nodeJavaScriptEvaluate	( const std::string& sJavaScript, int iSearchDir = NEAREST_AUTO );
bool 		inputSet 				( const std::string& sValue, int iSearchDir = NEAREST_AUTO )																		;
bool 		inputSet 				( int 				 iValue, int iSearchDir = NEAREST_AUTO )																		;
std::string innerHtml               ( int iSearchDir = NEAREST_AUTO );
bool 		innerHtmlSet 			( const std::string& sValue, int iSearchDir = NEAREST_AUTO );
std::string innerText               ( int iSearchDir = NEAREST_AUTO );
bool 		innerTextSet 			( const std::string& sValue, int iSearchDir = NEAREST_AUTO );
bool 		inputValue 				( const std::string& sValue, int iSearchDir = NEAREST_AUTO )																		;
bool 		inputValue 				( int 				 iValue, int iSearchDir = NEAREST_AUTO )																		;
bool		formSubmit				( int iSearchDir = NEAREST_AUTO )																									;
bool		formReset				( int iSearchDir = NEAREST_AUTO )																									;
int			selectLength			( int iSearchDir = NEAREST_AUTO )																									;
int			selectSelectedIndex		( int iSearchDir = NEAREST_AUTO )																									;
std::string	selectSelectedText		( int iSearchDir = NEAREST_AUTO );
std::string	selectSelectedValue		( int iSearchDir = NEAREST_AUTO );
int 		selectSelectedDomPos 	( int iSearchDir = NEAREST_AUTO )																									;
bool		selectSelect			( int iIndex, int iSearchDir = NEAREST_AUTO )																						;
bool		selectIndex             ( int iIndex, int iSearchDir = NEAREST_AUTO )																						;
bool		selectIndexWait         ( int iIndex, int timeoutInMs = 30000, int iSearchDir = NEAREST_AUTO );
bool		selectOption			( int iSearchDir = crawl::NEAREST_AUTO )																									;
bool		selectOptionWait		( int timeoutInMs = 30000, int iSearchDir = crawl::NEAREST_AUTO );
int         selectIndexOfOption		( int iSearchDir = crawl::NEAREST_AUTO );
bool		doActionSimple			( const std::string& sAction, const std::string& sParam1, const std::string& sParam2, int iSearchDir );
bool		doAction				( const std::string& sAction, const std::string& sParam1, const std::string& sParam2, int iSearchDir );
bool		doAction				( const std::string& sAction, const std::string& sParam1, const std::string& sParam2 );
bool		doAction				( const std::string& sAction, const std::string& sParam1, int iSearchDir = NEAREST_AUTO );
bool		doAction				( const std::string& sAction, int iSearchDir = NEAREST_AUTO );
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



//int		doActionFindNextParams			(	int iCount, const std::string& sSequence, const std::string& sArgs, const std::string& sAction, const std::string& sParam1,
//										const std::string& sParam2, int iSearchDir );
//int		doActionFindNextParams			(	int iCount, const std::string& sSequence, const std::string& sArgs, const std::string& sAction, const std::string& sParam1,
//										const std::string& sParam2 );
//int		doActionFindNextParams			(	int iCount, const std::string& sSequence, const std::string& sArgs, const std::string& sAction, const std::string& sParam1,
//										int iSearchDir = NEAREST_AUTO );
//int		doActionFindNextParams			(	int iCount, const std::string& sSequence, const std::string& sArgs, const std::string& sAction, int iSearchDir = NEAREST_AUTO );

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

//int		doActionFindParams			(	int iCount, const std::string& sSequence, const std::string& sArgs, const std::string& sAction, const std::string& sParam1,
//										const std::string& sParam2, int iSearchDir );
//int		doActionFindParams			(	int iCount, const std::string& sSequence, const std::string& sArgs, const std::string& sAction, const std::string& sParam1,
//										const std::string& sParam2 );
//int		doActionFindParams			(	int iCount, const std::string& sSequence, const std::string& sArgs, const std::string& sAction, const std::string& sParam1,
//										int iSearchDir = NEAREST_AUTO );
//int		doActionFindParams			(	int iCount, const std::string& sSequence, const std::string& sArgs, const std::string& sAction, int iSearchDir = NEAREST_AUTO );

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
void modifierCreate					(	const std::string& sModifierID, const std::string& sManipFunID, const std::string& sManipParam1,
                                        const std::string& sManipParam2, const std::string& sManipParam3, const std::string& sManipParam4 );
void modifierCreate					(	const std::string& sModifierID, const std::string& sManipFunID, const std::string& sManipParam1,
                                        const std::string& sManipParam2, const std::string& sManipParam3 );
void modifierCreate					(	const std::string& sModifierID, const std::string& sManipFunID, const std::string& sManipParam1,
                                        const std::string& sManipParam2 );
void modifierCreate					(	const std::string& sModifierID, const std::string& sManipFunID, const std::string& sManipParam1 );
void modifierCreate					(	const std::string& sModifierID, const std::string& sManipFunID );


/*
-----------------------------
--- nodeXX misc functions ---
----------------------------- */
int         nodeLevel               ();  // NOT_DOCUMENTED
std::string	nodeXPath               ();


/*
------------------------------
--- nodeValuePos functions ---
------------------------------ */
std::string	nodeValuePos			( int iDomPos, const std::string& sModifierID, const std::string& sManipParam1,
                                      const std::string& sManipParam2, const std::string& sManipParam3,
                                      const std::string& sManipParam4 );
std::string	nodeValuePos			( int iDomPos, const std::string& sModifierID, const std::string& sManipParam1,
                                      const std::string& sManipParam2, const std::string& sManipParam3 );
std::string	nodeValuePos			( int iDomPos, const std::string& sModifierID, const std::string& sManipParam1,
                                      const std::string& sManipParam2 );
std::string	nodeValuePos			( int iDomPos, const std::string& sModifierID, const std::string& sManipParam1 );
std::string	nodeValuePos			( int iDomPos, const std::string& sModifierID );
std::string	nodeValuePos			( int iDomPos );

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

/*
-----------------------
--- Parse functions ---
----------------------- */
const int 	MATCH_FIRST 	= crawl::MATCH_FIRST	;
const int 	MATCH_LAST		= crawl::MATCH_LAST	;
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

/*
------------------------
--- Text functions ---
------------------------ */
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


/*
-----------------------------
--- (URL) queue functions ---
----------------------------- */
const int LINK_TYPE_LOCAL		=	1 << 0;
const int LINK_TYPE_EXTERNAL	=	1 << 1;
const int LINK_TYPE_ALL			=	0x3;

int			urlQueueSize			()	;
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

/*
-----------------------------
--- linksGetter functions ---
----------------------------- */
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
std::string	valueModify				( const std::string& sModifierID, const std::string& sManipParam1, const std::string& sManipParam2,
                                      const std::string& sManipParam3, const std::string& sManipParam4 );
std::string	valueModify				( const std::string& sModifierID, const std::string& sManipParam1, const std::string& sManipParam2,
                                      const std::string& sManipParam3 );
std::string	valueModify				( const std::string& sModifierID, const std::string& sManipParam1, const std::string& sManipParam2 );
std::string	valueModify				( const std::string& sModifierID, const std::string& sManipParam1 );
std::string	valueModify				( const std::string& sModifierID );


/*
------------------------------
--- Data/Context functions ---
------------------------------ */
void		dataPushContext			(	std::string sContext, std::string const& sUnit = "" );
void		dataPushContextAlias	(	const std::string& sContext, const std::string& sContextAlias, const std::string& sUnit = "" );
void		dataPopContext			();

void		contextBegin                (	std::string sContextName );
void		contextEnd                  ();
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
void		outputDirectUnit		( const std::string& sFieldName, const std::string& sValue, const std::string& sUnit,
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
void		outputDirectUnit		( const std::string& sFieldName, const std::string& sValue, const std::string& sUnit );
// ---
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

//----

void		outputValueUnit			( const std::string& sFieldName, const std::string& sUnit, const std::string& sModifierID,
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
void		outputValueUnit			( const std::string& sFieldName, const std::string& sUnit );

//----

void		outputValue				( const std::string& sFieldName, const std::string& sModifierID, const std::string& sManipParam1,
                                      const std::string& sManipParam2, const std::string& sManipParam3, const std::string& sManipParam4 );
void		outputValue				( const std::string& sFieldName, const std::string& sModifierID, const std::string& sManipParam1,
                                      const std::string& sManipParam2, const std::string& sManipParam3 );
void		outputValue				( const std::string& sFieldName, const std::string& sModifierID, const std::string& sManipParam1,
                                      const std::string& sManipParam2 );
void		outputValue				( const std::string& sFieldName, const std::string& sModifierID, const std::string& sManipParam1 );
void		outputValue				( const std::string& sFieldName, const std::string& sModifierID );
void		outputValue				( const std::string& sFieldName );

/*
-------------------------------------
--- outputValueFindNext functions ---
------------------------------------- */

int			outputValueFindNext		( int iCount, const std::string& sSequence,	const std::string& sFieldName, const std::string& sModifierID,
                                      const std::string& sManipParam1, const std::string& sManipParam2, const std::string& sManipParam3,
                                      const std::string& sManipParam4 );
int			outputValueFindNext		( int iCount, const std::string& sSequence,	const std::string& sFieldName, const std::string& sModifierID,
                                      const std::string& sManipParam1, const std::string& sManipParam2, const std::string& sManipParam3	);
int			outputValueFindNext		( int iCount, const std::string& sSequence,	const std::string& sFieldName, const std::string& sModifierID,
                                      const std::string& sManipParam1, const std::string& sManipParam2	);
int			outputValueFindNext		( int iCount, const std::string& sSequence,	const std::string& sFieldName, const std::string& sModifierID,
                                      const std::string& sManipParam1 );
int			outputValueFindNext		( int iCount, const std::string& sSequence,	const std::string& sFieldName, const std::string& sModifierID );
int			outputValueFindNext		( int iCount, const std::string& sSequence,	const std::string& sFieldName );


int			outputValueFindNext		( const std::string& sSequence,	const std::string& sFieldName, const std::string& sModifierID,
                                      const std::string& sManipParam1, const std::string& sManipParam2, const std::string& sManipParam3,
                                      const std::string& sManipParam4 );
int			outputValueFindNext		( const std::string& sSequence,	const std::string& sFieldName, const std::string& sModifierID,
                                      const std::string& sManipParam1, const std::string& sManipParam2, const std::string& sManipParam3	);
int			outputValueFindNext		( const std::string& sSequence,	const std::string& sFieldName, const std::string& sModifierID,
                                      const std::string& sManipParam1, const std::string& sManipParam2	);
int			outputValueFindNext		( const std::string& sSequence,	const std::string& sFieldName, const std::string& sModifierID,
                                      const std::string& sManipParam1 );
int			outputValueFindNext		( const std::string& sSequence,	const std::string& sFieldName, const std::string& sModifierID );
int			outputValueFindNext		( const std::string& sSequence,	const std::string& sFieldName );


//int			outputValueFindNextParams		( int iCount, const std::string& sSequence, const std::string& sArgs,	const std::string& sFieldName, const std::string& sModifierID,
//									  const std::string& sManipParam1, const std::string& sManipParam2, const std::string& sManipParam3,
//									  const std::string& sManipParam4 );
//int			outputValueFindNextParams		( int iCount, const std::string& sSequence, const std::string& sArgs,	const std::string& sFieldName, const std::string& sModifierID,
//									  const std::string& sManipParam1, const std::string& sManipParam2, const std::string& sManipParam3	);
//int			outputValueFindNextParams		( int iCount, const std::string& sSequence, const std::string& sArgs,	const std::string& sFieldName, const std::string& sModifierID,
//									  const std::string& sManipParam1, const std::string& sManipParam2	);
//int			outputValueFindNextParams		( int iCount, const std::string& sSequence, const std::string& sArgs,	const std::string& sFieldName, const std::string& sModifierID,
//									  const std::string& sManipParam1 );
//int			outputValueFindNextParams		( int iCount, const std::string& sSequence, const std::string& sArgs,	const std::string& sFieldName, const std::string& sModifierID );
//int			outputValueFindNextParams		( int iCount, const std::string& sSequence, const std::string& sArgs,	const std::string& sFieldName );

/*
---------------------------------
--- outputValueFind functions ---
--------------------------------- */
int			outputValueFind			( int iCount, const std::string& sSequence,	const std::string& sFieldName, const std::string& sModifierID,
                                      const std::string& sManipParam1, const std::string& sManipParam2, const std::string& sManipParam3,
                                      const std::string& sManipParam4 );
int			outputValueFind			( int iCount, const std::string& sSequence,	const std::string& sFieldName, const std::string& sModifierID,
                                      const std::string& sManipParam1, const std::string& sManipParam2, const std::string& sManipParam3	);
int			outputValueFind			( int iCount, const std::string& sSequence,	const std::string& sFieldName, const std::string& sModifierID,
                                      const std::string& sManipParam1, const std::string& sManipParam2	);
int			outputValueFind			( int iCount, const std::string& sSequence,	const std::string& sFieldName, const std::string& sModifierID,
                                      const std::string& sManipParam1 );
int			outputValueFind			( int iCount, const std::string& sSequence,	const std::string& sFieldName, const std::string& sModifierID );
int			outputValueFind			( int iCount, const std::string& sSequence,	const std::string& sFieldName );


int			outputValueFind			( const std::string& sSequence,	const std::string& sFieldName, const std::string& sModifierID,
                                      const std::string& sManipParam1, const std::string& sManipParam2, const std::string& sManipParam3,
                                      const std::string& sManipParam4 );
int			outputValueFind			( const std::string& sSequence,	const std::string& sFieldName, const std::string& sModifierID,
                                      const std::string& sManipParam1, const std::string& sManipParam2, const std::string& sManipParam3	);
int			outputValueFind			( const std::string& sSequence,	const std::string& sFieldName, const std::string& sModifierID,
                                      const std::string& sManipParam1, const std::string& sManipParam2	);
int			outputValueFind			( const std::string& sSequence,	const std::string& sFieldName, const std::string& sModifierID,
                                      const std::string& sManipParam1 );
int			outputValueFind			( const std::string& sSequence,	const std::string& sFieldName, const std::string& sModifierID );
int			outputValueFind			( const std::string& sSequence,	const std::string& sFieldName );

//int			outputValueFindParams		( int iCount, const std::string& sSequence, const std::string& sArgs,	const std::string& sFieldName, const std::string& sModifierID,
//									  const std::string& sManipParam1, const std::string& sManipParam2, const std::string& sManipParam3,
//									  const std::string& sManipParam4 );
//int			outputValueFindParams		( int iCount, const std::string& sSequence, const std::string& sArgs,	const std::string& sFieldName, const std::string& sModifierID,
//									  const std::string& sManipParam1, const std::string& sManipParam2, const std::string& sManipParam3	);
//int			outputValueFindParams		( int iCount, const std::string& sSequence, const std::string& sArgs,	const std::string& sFieldName, const std::string& sModifierID,
//									  const std::string& sManipParam1, const std::string& sManipParam2	);
//int			outputValueFindParams		( int iCount, const std::string& sSequence, const std::string& sArgs,	const std::string& sFieldName, const std::string& sModifierID,
//									  const std::string& sManipParam1 );
//int			outputValueFindParams		( int iCount, const std::string& sSequence, const std::string& sArgs,	const std::string& sFieldName, const std::string& sModifierID );
//int			outputValueFindParams		( int iCount, const std::string& sSequence, const std::string& sArgs,	const std::string& sFieldName );

/*---------------------
--- State functions ---
-----------------------*/



/*
----------------------------
--- Javascript functions ---
---------------------------- */
bool 		javaScriptExecuteRetVal	( const std::string& sScript, std::string& sScriptReturnValue 	);
bool 		javaScriptExecute		( const std::string& sScript									);
bool 		javaScriptExecuteWait	( const std::string& sScript, int timeoutInMs = crawl::ScriptMinerIF::timeoutInMsDefault);

/*
-------------------------
--- Utility functions ---
------------------------- */
int 		curlPostUploadFileSimple( const std::string& sURL, const std::string& sFieldName, const std::string& sFilePath 	) 	;
bool 		gzCompressFile			( const std::string& sSrcFilePath, const std::string& sDstFilePath ) 						;
bool 		gzUnCompressFile		( const std::string& sSrcFilePath, const std::string& sDstFilePath )						;

/*
--------------------------
--- Settings functions ---
-------------------------- */
void		settingDelete           (	const std::string& sName );
void		settingSet              (	const std::string& sName, const std::string& sValue );
std::string settingGet              (	const std::string& sName, const std::string& defaultValue = "" );
bool        settingExists           (	const std::string& sName );
bool        hasSetting              (	const std::string& sName ) ;
bool        settingBoolGet          (   const std::string& sName );

/*
------------------------
--- Config functions ---
------------------------ */
std::string configValueGet          ( const std::string& sName );
void		configValueSet          ( const std::string& sName, const std::string& sValue );
bool        configValueBoolGet      ( const std::string& sName );
void 		configUrlStart			( const std::string& sUrl	)																;
void 		configUrlUploadDataSet	( const std::string& sUrl	)																;
std::string configUrlUploadDataGet	()																							;
void 		configDisableLoadImages	()																							;
void 		configForceLoadImages	()																							;
void 		configAddIncludeUrl		( const std::string& sPattern, const std::string& sCompareFun )	;
void 		configAddExcludeUrl		( const std::string& sPattern, const std::string& sCompareFun )	;
void        configUploadData        ( bool bUploadData );
void		configForceSendXmlData	();
void        configAjaxPageLoadDeltaTime ( int iMilliSeconds );
void		configReloadTimeOut		( int iMinutes, int iSecs )																	;
void		configKeepActiveInterval( int iSecs )																				;
void		configProgressOutputSet	( bool bEnable )																			;
void		configDebugOutputSet	( bool bEnable )																			;
bool		configDebugOutputGet	()																							;
void 		configParseDecimalPointSet( const std::string& sDecimalPoint  	)													;
void 		configParseThousandsSepSet( const std::string& sThousandsSep 	)													;
void		configOutputEncloseCDATA( bool bDoEncloseInCDATA )																	;
void		configOutputWriteToFile ( bool bDoWriteOutputToFile );
std::string configGetRunMode        ();
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


// --------------------------------------------
// --- INLINE Implementation: DOM functions ---
// --------------------------------------------


// ---------------------------------------------
// --- INLINE Implementation: Node functions ---
// ---------------------------------------------






// ---------------------------------------------------
// --- INLINE Implementation: Javascript functions ---
// ---------------------------------------------------
bool javaScriptExecuteRetVal( const std::string& sScript, std::string& sScriptReturnValue );
bool javaScriptExecute		( const std::string& sScript	);

//// ----------------------------------------------
//// --- INLINE Implementation: Debug functions ---
//// ----------------------------------------------
//inline void domDebugPrint(
//	const std::string& sFileName )		///< [in] Filename to print to. If emty stdout is used.
//{
//    // TODO: Implement again if we need it!
////    if ( sFileName.empty() )	curMiner()->linearDom()->print( std::cout, false );
////    else {
////		std::ofstream file( sFileName.c_str() ) ;
////        curMiner()->linearDom()->print( file, false );
////	}
//}

///// Debug print current node optionally with the nodes surrounding it
//inline void	nodeDebugPrint(
//	int iNodesBefore, 				///< [in] Number of nodes to print before the current node (positive number always)
//	int iNodesAfter, 				///< [in] Number of nodes to print after the current node (positive number always)
//	bool bPrintNodeTypes )			///< [in] Print the node types also
//{	curMiner()->linearDomSearch()->debugPrintCurrentNode( iNodesBefore, iNodesAfter, bPrintNodeTypes);	}

///// Debug print current node optionally with the nodes surrounding it
//inline void	nodeDebugPrint(
//	int iNodesAround, 				///< [in] Number of nodes to print before the current node (positive number always)
//	bool bPrintNodeTypes )			///< [in] Print the node types also
//{	curMiner()->linearDomSearch()->debugPrintCurrentNode( iNodesAround, iNodesAround, bPrintNodeTypes);	}

///// Get debug string of current node optionally with the nodes surrounding it
//inline std::string nodeValueDebug (
//	int iNodesBefore, 				///< [in] Number of nodes to print before the current node (positive number always)
//	int iNodesAfter, 				///< [in] Number of nodes to print after the current node (positive number always)
//	bool bPrintNodeTypes )			///< [in] Print the node types also
//{	return curMiner()->linearDomSearch()->debugGetCurrentNode( iNodesBefore, iNodesAfter, bPrintNodeTypes);	}

///// Get debug string of current node optionally with the nodes surrounding it
//inline std::string nodeValueDebug (
//	int iNodesAround, 				///< [in] Number of nodes to print before the current node (positive number always)
//	bool bPrintNodeTypes )			///< [in] Print the node types also
//{	return curMiner()->linearDomSearch()->debugGetCurrentNode( iNodesAround, iNodesAround, bPrintNodeTypes);	}


#endif //SCRIPTCRAWL_H


