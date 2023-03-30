#pragma once

#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <dom_constants.h>
#include <DomNodeIF.h>
#include <QObject>
#include <QString>


namespace crawl {
    class StateMachineMgr;
    class ScriptingClassIF;
    class DomSeq;
    class Configuration;
    class LinearDomIF;
    class WebBrowserIF;
    class DomSearchMgr;
    class LinearDomSearch;
    class UrlQueue;

class ScriptMinerIF : public boost::enable_shared_from_this<ScriptMinerIF> {
public:
    // ------------------------
    // --- PUBLIC: Typedefs ---
    // ------------------------

    static constexpr int timeoutInMsDefault = 30000;
    static constexpr int timeoutInMsReload = 3000;

    // ------------------------------------
    // --- Contructors / Init Functions ---
    // ------------------------------------

    ScriptMinerIF();
    ScriptMinerIF  ( boost::shared_ptr<ScriptingClassIF> pScriptClass, boost::shared_ptr<Configuration> pConfig );
    virtual ~ScriptMinerIF  ();

    void    scriptingClassSet               (boost::shared_ptr<ScriptingClassIF> pScriptClass);
    void    configurationSet                (boost::shared_ptr<Configuration> pConfig);
    void    scriptHtmlEntitiesReplaceAdd    (const std::string& lookFor, const std::string& replaceWith);
    void    scriptHtmlEntitiesReplaceClear  ();

    // --------------------
    // --- PUBLIC: Info ---
    // --------------------
    boost::shared_ptr<ScriptingClassIF>         scriptingClass();
    const boost::shared_ptr<ScriptingClassIF>   scriptingClass() const;

    const boost::shared_ptr<Configuration>      config() const;
    boost::shared_ptr<Configuration>            config();

    bool                                        runModeCreator () const;

    virtual boost::shared_ptr<crawl::WebBrowserIF>          webBrowser() = 0;
    virtual const boost::shared_ptr<crawl::WebBrowserIF>    webBrowser() const = 0;

    virtual boost::shared_ptr<LinearDomIF>                  linearDom() = 0;
    virtual const boost::shared_ptr<LinearDomIF>            linearDom() const = 0;

    virtual boost::shared_ptr<LinearDomSearch>              linearDomSearch () = 0;
    virtual const boost::shared_ptr<LinearDomSearch>        linearDomSearch() const	= 0;

    virtual boost::shared_ptr<DomSearchMgr>                 domSearchMgr() = 0;
    virtual const boost::shared_ptr<DomSearchMgr>           domSearchMgr() const = 0;
    virtual const UrlQueue&                                 urlQueue() const = 0;
    virtual UrlQueue&                                       urlQueue() = 0;

    virtual bool				scriptFunctionExists    ( const std::string&  sFunName ) const = 0;

    virtual void				clearForReloadScript() = 0;
    virtual void				startMining         ( bool restart ) = 0;
    virtual void				endMining           ( int iMiningDoneStatus ) = 0;
    virtual void 				signalMiningDone    ( ) = 0;
    virtual bool				onClose             ( ) = 0;

    // --------------------------------------
    // --- Program flow control functions ---
    // --------------------------------------
    virtual void                match			() = 0;
    virtual void				mine			() = 0;
    virtual bool				navigate		() = 0;
    virtual bool				nextPage		() = 0;
    virtual std::string         handlerContextName  () const = 0;

    // -------------------------------
    // --- Info/settings functions ---
    // -------------------------------
    virtual std::string         minerName		() const  = 0;
    virtual std::string         outputName		() const = 0;
    //virtual void                minerName		( const std::string& sMinerName )       { m_sMinerName = sMinerName = 0;    }
    virtual std::string			dataFileName	() const = 0;
    //virtual void				baseOutputName	(const std::string& sBaseOutputName ) { m_sBaseOutputName = sBaseOutputName = 0;	}

    //virtual const std::string&	currentLoadingUri() const {return m_sCurrentLoadingUri = 0; }


    //virtual boost::shared_ptr<crawl::StateMachineMgr>           stateMachineMgr() = 0;
    //virtual const boost::shared_ptr<crawl::StateMachineMgr>     stateMachineMgr() const = 0;

public:
    // ----------------------
    // --- Misc functions ---
    // ----------------------
    virtual std::string     pageSource                          () const = 0;
    virtual std::string     currentMiner                        () const = 0;
    virtual std::string     currentDataFile                     () const = 0;
    virtual void            triggerPageLoaded                   () = 0;
    virtual void            triggerPageLoadedWait               (int timeoutInMs = timeoutInMsReload) = 0;
    virtual void            waitSleep                           (int timeInMs) = 0;
    virtual bool            waitForDomReady                     (int timeoutInMs = timeoutInMsDefault) = 0;
    virtual void            waitForFilesDownloaded              (int timeoutInMs = 10*60*1000) = 0;
    virtual void            waitForJavascriptDone               () = 0;
    virtual void            clearCookies                        () = 0;
    virtual int             networkActivityCounter              () const = 0;

    /*
    -------------------------
    --- Browser functions ---
    ------------------------- */
    virtual void        browserScroll       ( int xScroll, int yScroll ) = 0;
    virtual int         browserScrollPosXGet() const = 0;
    virtual int         browserScrollPosYGet() const = 0;
    virtual void		browserHide			() = 0;
    virtual void		browserShow			() = 0;
    virtual void		browserSetSize		(int x, int y) = 0;
    virtual int			browserGetSizeX		() const = 0;
    virtual int			browserGetSizeY		() const = 0;
    virtual bool		browserGoBack		() = 0;
    virtual void        browserKeyEvent     (int eventType, int key, int modifiers) = 0;
    virtual void        browserMouseEvent   (int eventType, float xpos, float ypos, int button, int buttons, int modifiers) = 0;
    virtual void        browserFocusActivate() = 0;
    virtual void        browserFocusDeactivate() = 0;

    /*------------------------------------------
    --- String operators/compare functions ---
    ------------------------------------------*/
    virtual bool 		valuesCompare		( const std::string& sInput, const std::string& sTest, const std::string& sCompareFun ) = 0;
    /*
    -------------------------
    --- Sitemap functions ---
    -------------------------*/
    virtual void                        siteMapUrlsSet          (const std::vector<std::string> &siteMapUrls) = 0;
    virtual std::vector<std::string>    siteMapUrls             () const = 0;
    virtual void                        siteMapUrlAppend        (const std::string &siteMapUrl) = 0;
    virtual std::vector<std::string>    siteMapLocationUrls     () const = 0;
    virtual void                        siteMapLocationsInclude	(const std::string& urlPattern, const std::string& compareFun = "contains" ) = 0;
    virtual void                        siteMapLocationsExclude	(const std::string& urlPattern, const std::string& compareFun = "contains" ) = 0;

    /*
    ----------------------------------
    --- Navigation (nav) functions ---
    ---------------------------------- */
    virtual void        navActiveNavigatorSet   ( const std::string& sNavigatorName ) = 0;
    virtual std::string navActiveNavigatorGet   () = 0;
    virtual void        navJavascriptExecuteCreate ( const std::string& sNavActionName ) = 0;
    virtual void        navUrlLoadCreate        ( const std::string& sNavActionName, const std::string& sBaseUrl ) = 0;
    virtual void        navInputOptionsCreate   ( const std::string& sNavActionName ) = 0;
    virtual void        navDropDownSelectCreate ( const std::string& sNavActionName ) = 0;
    virtual void        navDomPosClickCreate    ( const std::string& sNavActionName, const std::string& sFindNextDomPosSequence ) = 0;
    virtual void        navDomClickNextCreate   ( const std::string& sNavActionName, const std::string& sFindNextDomPosSequence) = 0;
    virtual void        navAutoInputCreate      ( const std::string& sNavActionName, const std::string& sCharsList, int iMinLength, int iMaxLength ) = 0;

    virtual void        navAttributeNamesCreate ( const std::string& sAttrNames, const std::string& sDelimiter = "," ) = 0;

    // --- PUBLIC: Runtime settings functions ---
    virtual void        navCurrentStateIndicesSet ( const std::string& sState ) = 0;
    virtual std::string navCurrentStateIndicesGet () const = 0;
    virtual void        navCurrentStateSet      ( const std::string& sState, const std::string& sDelimiter ) = 0;
    virtual void        navCurrentStateSet      ( const std::string& sState ) = 0;
    virtual void        navEndStateSet          ( const std::string& sState, const std::string& sDelimiter ) = 0;
    virtual void        navEndStateSet          ( const std::string& sState ) = 0;

    // --- PUBLIC: Add Options functions ---
    virtual void        navOptionResourceAdd    ( const std::string& sResourcePath, const std::string& sScriptFilterFunction,  bool bForceDownload  ) = 0;
    virtual void        navOptionAdd            ( int iCount, const std::string& sValue, const std::string& sSearchFor  ) = 0;
    virtual void        navOptionAdd            ( int iCount, const std::string& sValue ) = 0;
    virtual void        navOptionAdd            ( const std::string& sValue, const std::string& sSearchFor ) = 0;
    virtual void        navOptionAdd            ( const std::string& sValue ) = 0;
    virtual void        navOptionAdd            ( int iCount ) = 0;

    virtual void        navOptionAdd            ( int iCount, const std::string& sValue, const std::string& sSearchFor,
                                                  int attrStart, const std::string& sAttributes, const std::string& sDelimiter = "," ) = 0;
    virtual void        navOptionAdd            ( int iCount, const std::string& sValue,
                                                  int attrStart, const std::string& sAttributes, const std::string& sDelimiter = "," ) = 0;
    virtual void        navOptionAdd            ( const std::string& sValue, const std::string& sSearchFor,
                                                  int attrStart, const std::string& sAttributes, const std::string& sDelimiter = "," ) = 0;
    virtual void        navOptionAdd            ( const std::string& sValue,
                                                  int attrStart, const std::string& sAttributes, const std::string& sDelimiter = "," ) = 0;
    virtual void        navOptionAdd            ( int iCount, int attrStart, const std::string& sAttributes, const std::string& sDelimiter = "," ) = 0;

    // --- PUBLIC: Runtime functions ---
    virtual std::string navDomTextValueGet      ( const std::string& sNavActionName ) const = 0;
    virtual std::string navDomValueGet          ( const std::string& sNavActionName ) const = 0;
    virtual std::string navValueGet             ( const std::string& sNavActionName )  = 0;
    virtual std::string navSearchForGet         ( const std::string& sNavActionName )  = 0;
    virtual int         navCountGet             ( const std::string& sNavActionName )  = 0;
    virtual int         navOptionIndexGet       ( const std::string& sNavActionName )  = 0;
    virtual int         navStateIndexGet        ()  = 0;
    virtual int         navNumStatesGet         () const = 0;
    virtual int         navLastStateIndexGet    () const = 0;

    virtual std::string navAttributeGet         ( const std::string& sNavActionName, const std::string& sAttrName )  = 0;
    virtual std::string navAttributeGet         ( const std::string& sAttrName ) const = 0;
    virtual bool        navNextState            () = 0;
    virtual bool        navDoActionClickAll     ( const std::string& sNavActionName )  = 0;
    virtual bool        navDoAction             ( const std::string& sNavActionName )  = 0;
    virtual std::string navStateString          () const = 0;
    virtual void        navStart                () = 0;
    virtual void        navReset                () = 0;
    virtual bool        navNavigationDone       () const = 0;
    virtual void        navAutoInputIncreaseLength ( bool bDoIncreaseLength ) = 0;

    /*
    ----------------------------------------------
    --- String modifier/manipulation functions ---
    ---------------------------------------------- */
    virtual std::string		trimDefault_fn 		( const std::string& sInput 	) const = 0;
    virtual std::string		raw_fn				( const std::string& sInput		) const = 0;
    virtual std::string		toUpper_fn			( const std::string& sInput		) const = 0;
    virtual std::string		toLower_fn			( const std::string& sInput		) const = 0;
    virtual std::string		trimEnds_fn			( const std::string& sInput		) const = 0;
    virtual std::string		trimLeft_fn			( const std::string& sInput		) const = 0;
    virtual std::string		trimRight_fn		( const std::string& sInput		) const = 0;
    virtual std::string		trimYear_fn			( const std::string& sInput 	) const = 0;

    virtual std::string		trimInteger_fn		( const std::string& sInput		) const = 0;
    virtual std::string		trimNumber_fn		( const std::string& sInput		) const = 0;


    virtual std::string 	trimCharsEnds_fn	( const std::string& sInput, const std::string& sCharsToTrim ) const = 0;
    virtual std::string 	trimCharsLeft_fn	( const std::string& sInput, const std::string& sCharsToTrim ) const = 0;
    virtual std::string 	trimCharsRight_fn	( const std::string& sInput, const std::string& sCharsToTrim ) const = 0;
    virtual std::string 	trimRegex_fn		( const std::string& sInput, const std::string& sRegex ) const = 0;
    virtual std::string 	itrimRegex_fn		( const std::string& sInput, const std::string& sRegex ) const = 0;
    virtual std::string		append_fn			( const std::string& sInput, const std::string& sString	) const = 0;
    virtual std::string		prepend_fn			( const std::string& sInput, const std::string& sString	) const = 0;
    virtual std::string		eraseFirst_fn		( const std::string& sInput, const std::string& sSearchFor	) const = 0;
    virtual std::string		ieraseFirst_fn		( const std::string& sInput, const std::string& sSearchFor	) const = 0;
    virtual std::string		eraseLast_fn		( const std::string& sInput, const std::string& sSearchFor	) const = 0;
    virtual std::string		ieraseLast_fn		( const std::string& sInput, const std::string& sSearchFor	) const = 0;
    virtual std::string		eraseAll_fn			( const std::string& sInput, const std::string& sSearchFor	) const = 0;
    virtual std::string		ieraseAll_fn		( const std::string& sInput, const std::string& sSearchFor	) const = 0;
    virtual std::string		eraseRegex_fn		( const std::string& sInput, const std::string& sSearchFor	) const = 0;
    virtual std::string		eraseAllRegex_fn	( const std::string& sInput, const std::string& sSearchFor	) const = 0;

    virtual std::string 	trimBetween_fn      ( const std::string& sInput, const std::string& sBegin, 		const std::string& sEnd ) const = 0;
    virtual std::string 	trimBetweenCount_fn ( const std::string& sInput, const std::string& sBegin, 		const std::string& sEnd, const std::string& sCount ) const = 0;
    virtual std::string 	trimBetweenCount_fn ( const std::string& sInput, const std::string& sBegin, 		const std::string& sEnd, int iCount ) const = 0;
    virtual std::string 	trimIntegerCustom_fn( const std::string& sInput, const std::string& iBase, 			const std::string& sThousandsSep) const = 0;
    virtual std::string 	trimNumberCustom_fn	( const std::string& sInput, const std::string& sDecimalPoint, 	const std::string& sThousandsSep) const = 0;
    virtual std::string		replaceFirst_fn		( const std::string& sInput, const std::string& sSearchFor,		const std::string& sReplaceWith	) const = 0;
    virtual std::string		ireplaceFirst_fn	( const std::string& sInput, const std::string& sSearchFor,		const std::string& sReplaceWith	) const = 0;
    virtual std::string		replaceLast_fn		( const std::string& sInput, const std::string& sSearchFor,		const std::string& sReplaceWith	) const = 0;
    virtual std::string		ireplaceLast_fn		( const std::string& sInput, const std::string& sSearchFor,		const std::string& sReplaceWith	) const = 0;
    virtual std::string		replaceAll_fn		( const std::string& sInput, const std::string& sSearchFor,		const std::string& sReplaceWith	) const = 0;
    virtual std::string		ireplaceAll_fn		( const std::string& sInput, const std::string& sSearchFor,		const std::string& sReplaceWith	) const = 0;
    virtual std::string		replaceRegex_fn		( const std::string& sInput, const std::string& sSearchFor,		const std::string& sReplaceWith	) const = 0;
    virtual std::string		replaceAllRegex_fn	( const std::string& sInput, const std::string& sSearchFor,		const std::string& sReplaceWith	) const = 0;

    virtual std::string		eraseNth_fn			( const std::string& sInput, const std::string& sSearchFor,	int iNth 	) const = 0;
    virtual std::string		eraseNth_fn         ( const std::string& sInput, const std::string& sSearchFor,     const std::string& sNth 	) const = 0;
    virtual std::string		ieraseNth_fn		( const std::string& sInput, const std::string& sSearchFor,	int iNth 	) const = 0;
    virtual std::string		ieraseNth_fn        ( const std::string& sInput, const std::string& sSearchFor,     const std::string& sNth 	) const = 0;

    virtual std::string		replaceNth_fn		( const std::string& sInput, const std::string& sSearchFor,	const std::string& sReplaceWith, int iNth	) const = 0;
    virtual std::string		replaceNth_fn       ( const std::string& sInput, const std::string& sSearchFor,	const std::string& sReplaceWith ,const std::string& sNth	) const = 0;
    virtual std::string		ireplaceNth_fn		( const std::string& sInput, const std::string& sSearchFor,	const std::string& sReplaceWith, int iNth	) const = 0;
    virtual std::string		ireplaceNth_fn      ( const std::string& sInput, const std::string& sSearchFor,	const std::string& sReplaceWith, const std::string& sNth	) const = 0;

    /*
    ---------------------
    --- URL functions ---
    --------------------- */
    virtual std::string		urlSite             () = 0;
    virtual std::string		urlCurrent          () = 0;
    virtual bool			urlLoad             ( const std::string sURL ) = 0;
    virtual bool			urlLoadWait         ( const std::string sURL, int timeoutInMs = timeoutInMsDefault ) = 0;

    /*
    ---------------------
    --- DOM functions ---
    --------------------- */
    virtual void        domRebuildWait          ( int timeoutInMs = timeoutInMsDefault ) = 0;
    virtual void		domNewSearch			() = 0;
    virtual std::vector<int> domFindAll         ( const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps ) = 0;
    virtual std::vector<int> domFindAll         ( const std::string& sSequence, int iPostMatchSteps ) = 0;
    virtual std::vector<int> domFindAll         ( const std::string& sSequence ) = 0;
    void                domContinueSearch		();
    virtual int			domFindParentPos		( int iLevelsUp = 1 ) = 0;
    virtual int			domFindParent			( int iLevelsUp = 1 ) = 0;

    virtual int			domSeqFindNextParams	( int iCount, const crawl::DomSeq& seq, const std::string& sArgs, int iNodeTypes ) = 0;

    virtual int			domFindNextImpl			( int iCount, std::string& sPhpFunRetVal, const std::string& sSequence,
                                                  const std::string& sArgs, const std::string& sCompareFun, int iPostMatchSteps, int iNodeTypes) = 0;
    virtual int			domFindNext				( int iCount, const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps, int iNodeTypes ) = 0;
    virtual int			domFindNext				( int iCount, const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps ) = 0;
    virtual int			domFindNext				( int iCount, const std::string& sSequence, const std::string& sCompareFun ) = 0;
    virtual int			domFindNext				( int iCount, const std::string& sSequence, int iPostMatchSteps ) = 0;
    virtual int			domFindNext				( int iCount, const std::string& sSequence ) = 0;
    virtual int			domFindNext				( const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps, int iNodeTypes ) = 0;
    virtual int			domFindNext				( const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps ) = 0;
    virtual int			domFindNext				( const std::string& sSequence, const std::string& sCompareFun ) = 0;
    virtual int			domFindNext				( const std::string& sSequence, int iPostMatchSteps ) = 0;
    virtual int			domFindNext				( const std::string& sSequence ) = 0;
    virtual int			domFindPrev				( const std::string& sSequence, const std::string& sCompareFun ) = 0;
    virtual int			domSeqFindNextParams    ( int iCount, const std::string& sSequence, const std::string& sArgs ) = 0;


    virtual int			domFind					( int iCount, const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps, int iNodeTypes ) = 0;
    virtual int			domFind					( int iCount, const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps ) = 0;
    virtual int			domFind					( int iCount, const std::string& sSequence, const std::string& sCompareFun ) = 0;
    virtual int			domFind					( int iCount, const std::string& sSequence, int iPostMatchSteps ) = 0;
    virtual int			domFind					( int iCount, const std::string& sSequence ) = 0;
    virtual int			domFind					( const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps, int iNodeTypes ) = 0;
    virtual int			domFind					( const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps ) = 0;
    virtual int			domFind					( const std::string& sSequence, const std::string& sCompareFun ) = 0;
    virtual int			domFind					( const std::string& sSequence, int iPostMatchSteps ) = 0;
    virtual int			domFind					( const std::string& sSequence ) = 0;

    virtual int			domFindPos              ( int iCount, const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps, int iNodeTypes ) = 0;
    virtual int			domFindPos              ( int iCount, const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps ) = 0;
    virtual int			domFindPos              ( int iCount, const std::string& sSequence, const std::string& sCompareFun ) = 0;
    virtual int			domFindPos              ( int iCount, const std::string& sSequence, int iPostMatchSteps ) = 0;
    virtual int			domFindPos              ( int iCount, const std::string& sSequence ) = 0;
    virtual int			domFindPos              ( const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps, int iNodeTypes ) = 0;
    virtual int			domFindPos              ( const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps ) = 0;
    virtual int			domFindPos              ( const std::string& sSequence, const std::string& sCompareFun ) = 0;
    virtual int			domFindPos              ( const std::string& sSequence, int iPostMatchSteps ) = 0;
    virtual int			domFindPos              ( const std::string& sSequence ) = 0;
    std::vector<int>    domFindAllPositions     ( const std::string& sSequence );

    virtual int			domFindNextPos			( int iCount, const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps, int iNodeTypes ) = 0;
    virtual int			domFindNextPos			( int iCount, const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps ) = 0;
    virtual int			domFindNextPos			( int iCount, const std::string& sSequence, const std::string& sCompareFun ) = 0;
    virtual int			domFindNextPos			( int iCount, const std::string& sSequence, int iPostMatchSteps ) = 0;
    virtual int			domFindNextPos			( int iCount, const std::string& sSequence ) = 0;
    virtual int			domFindNextPos			( const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps, int iNodeTypes ) = 0;
    virtual int			domFindNextPos			( const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps ) = 0;
    virtual int			domFindNextPos			( const std::string& sSequence, const std::string& sCompareFun ) = 0;
    virtual int			domFindNextPos			( const std::string& sSequence, int iPostMatchSteps ) = 0;
    virtual int			domFindNextPos			( const std::string& sSequence ) = 0;
    virtual int			domFindPrevPos			( const std::string& sSequence, const std::string& sCompareFun ) = 0;

    virtual int			domClickInput			( int iCount 	) = 0;
    virtual int			domClickInputNext		( int iCount 	) = 0;
    virtual int			domSetInput				( int iCount,	const std::string& sValue 	) = 0;
    virtual int			domSetInputNext			( int iCount,	const std::string& sValue 	) = 0;
    virtual int			domSetInput				( int iCount,	int iValue 					) = 0;
    virtual int			domSetInputNext			( int iCount,	int iValue 					) = 0;
    virtual int			domStep					( int iCount, int iNodeTypes = DomNodeTypes::ALL_NODE_TYPES ) = 0;
    virtual bool		domAtEnd				() = 0;
    virtual void		domRangePushElement		( int iElementPos ) = 0;
    virtual void		domRangePush			( int iStartPos, int iStopPos ) = 0;
    virtual void		domRangePop             () = 0;
    virtual void		domPointerPush			() = 0;
    virtual int			domPointerPop			() = 0;
    virtual int 		domSize					() = 0;
    virtual int 		domEndPos				() = 0;
    virtual int 		domPos                  () = 0;
    virtual int			domPosSet				( int iNewPos ) = 0;
    virtual int			domStartPosSet			( int iStartPos ) = 0;
    virtual int			domStartPos             () = 0;
    virtual void		domStartPosClear		() = 0;
    virtual int			domStopPosSet			( int iStopPos ) = 0;
    virtual int			domStopPos              () = 0;
    virtual void		domStopPosClear			() = 0;
    virtual void		domSetAtEnd             () = 0;
    virtual int			domContinuePos          () = 0;
    virtual int			domThisElementPos       () = 0;
    virtual int			domThisElementPos       ( int pos ) = 0;
    virtual int			domOwnerPos             ( int iLevelsUp = 1 ) = 0;
    virtual int			domPosToOwner			( int iLevelsUp = 1 ) = 0;
    virtual int			domParentPos            ( int iLevelsUp = 1 ) = 0;
    virtual int			domPosToParent			( int iLevelsUp = 1 ) = 0;

    /*
    -------------------------------------
    --- DOM Sequence create functions ---
    ------------------------------------- */
    virtual void		domSeqCreate			( int iCount, const std::string& sName, const std::string& sSequence,
                                                  const std::string& sCompareFun, int iPostMatchSteps, int iNodeTypes, const std::string& sCommaChar ) = 0;
    virtual void		domSeqCreate			( int iCount, const std::string& sName, const std::string& sSequence, const std::string& sCompareFun,
                                                  int iPostMatchSteps, int iNodeTypes  ) = 0;
    virtual void		domSeqCreate			( int iCount, const std::string& sName, const std::string& sSequence, const std::string& sCompareFun,
                                                  int iPostMatchSteps  ) = 0;
    virtual void		domSeqCreate			( int iCount, const std::string& sName, const std::string& sSequence, const std::string& sCompareFun ) = 0;
    virtual void		domSeqCreate			( int iCount, const std::string& sName, const std::string& sSequence, int iPostMatchSteps ) = 0;
    virtual void		domSeqCreate			( int iCount, const std::string& sName, const std::string& sSequence ) = 0;
    virtual void		domSeqCreate			( const std::string& sName, const std::string& sSequence, const std::string& sCompareFun,
                                                  int iPostMatchSteps, int iNodeTypes, const std::string& sCommaChar  ) = 0;
    virtual void		domSeqCreate			( const std::string& sName, const std::string& sSequence, const std::string& sCompareFun,
                                                  int iPostMatchSteps, int iNodeTypes  ) = 0;
    virtual void		domSeqCreate			( const std::string& sName, const std::string& sSequence, const std::string& sCompareFun,
                                                  int iPostMatchSteps  ) = 0;
    virtual void		domSeqCreate			( const std::string& sName, const std::string& sSequence, const std::string& sCompareFun ) = 0;
    virtual void		domSeqCreate			( const std::string& sName, const std::string& sSequence, int iPostMatchSteps ) = 0;
    virtual void		domSeqCreate			( const std::string& sName, const std::string& sSequence ) = 0;

    virtual bool		domSeqExists			( const std::string& sName ) const = 0;


    /*
    -----------------------------------
    --- LookForWord (lfw) functions ---
    ----------------------------------- */

    virtual void        lfwMatchWholeWordsOnlySet(bool matchWholeWordsOnly) = 0;
    virtual void		lfwClear                () = 0;
    virtual void		lfwClear                (const std::string& contextName) = 0;
    virtual void		lfwClear                (const std::string& contextName, const std::string& referenceName) = 0;
    virtual void		lfwAddWord              (const std::string& contextName, const std::string& referenceName,
                                                 const std::string& word, const std::string& compareFun, int nodeTypes) = 0;
    virtual void		lfwRemoveWord           (const std::string& contextName, const std::string& referenceName,
                                                 const std::string& word) = 0;
    virtual void		lfwGetDataFunctionSet   (const std::string& contextName, const std::string& getDataFunction) = 0;
    virtual void		lfwGetDataFallbackFunctionSet  (const std::string& contextName, const std::string& getDataFallbackFunction) = 0;
    int                 lfwDomFind              (const std::string& referenceName);
    virtual int         lfwDomFindNext          (const std::string& referenceName) = 0;
    std::string         lfwOutputValueFind      (const std::string& referenceName);
    virtual std::string lfwOutputValueFindNext  (const std::string& referenceName) = 0;
    virtual std::string lfwPreSequence          (const std::string& contextName) = 0;
    virtual void        lfwPreSequenceSet       (const std::string& contextName, const std::string& lfwPreSequence) = 0;
    virtual std::string lfwPostSequence         (const std::string& contextName) = 0;
    virtual void        lfwPostSequenceSet      (const std::string& contextName, const std::string& lfwPostSequence) = 0;
    std::vector<int>    lfwDomFindAllPositions  (const std::string& referenceName);
    int                 lfwDomStartPos          () const;
    void                lfwDomStartPosSet       (int pos);
    int                 lfwDomStopPos           () const;
    void                lfwDomStopPosSet        (int pos);

    virtual std::string lfwStartPosDomSeq       (const std::string& contextName) const = 0;
    virtual void        lfwStartPosDomSeqSet    (const std::string& contextName, const std::string& lfwStartPosDomSeq) = 0;
    virtual std::string lfwStopPosDomSeq        (const std::string& contextName) const = 0;
    virtual void        lfwStopPosDomSeqSet     (const std::string& contextName, const std::string& lfwStopPosDomSeq) = 0;

    /*
    ----------------------------------
    --- Element children functions ---
    ---------------------------------  */
    virtual std::vector<int> nodeChildren       ( int iSearchDir = NEAREST_AUTO ) = 0;
    virtual std::vector<int> nodeChildren       ( const std::string& tagName, int iSearchDir = NEAREST_AUTO ) = 0;
    virtual std::vector<int> nodeChildrenRecur  ( const std::string& tagName, int iSearchDir = NEAREST_AUTO ) = 0;
    virtual int              nodeEndElementPos  ( int iSearchDir = NEAREST_AUTO ) = 0;

    virtual std::vector<int> posChildren        ( int iDomPos) = 0;
    virtual std::vector<int> posChildren        ( const std::string& tagName, int iDomPos ) = 0;
    virtual std::vector<int> posChildrenRecur   ( const std::string& tagName, int iDomPos ) = 0;
    virtual int              posEndElementPos   ( int iDomPos ) = 0;


    /*
    ------------------------------------
    --- Current (dom) node functions ---
    ------------------------------------ */
//    virtual boost::shared_ptr<crawl::DomNodeIF> helperGetNearestElement( int iSearchDir, std::string sElemType = "" ) = 0;
    virtual int			nodeType				() = 0;
    virtual bool		nodeClickLoadHref		( int iSearchDir = NEAREST_AUTO )= 0;
    virtual bool		nodeClick				( int iSearchDir = NEAREST_AUTO )= 0;
    virtual bool		userClick				( int iSearchDir = NEAREST_AUTO )= 0;
    virtual bool        userMouseEvent          ( int eventType, int button, int buttons, int modifiers, int iSearchDir = NEAREST_AUTO ) = 0;
    virtual bool		nodeClickWait			( int timeoutInMs = timeoutInMsDefault, int iSearchDir = NEAREST_AUTO ) = 0;
    virtual bool		nodeMouseEvent			( const std::string& sEvent ) = 0;
    virtual bool		nodeMouseEvent			( const std::string& sEvent, int iSearchDir ) = 0;
    virtual bool		nodeMouseEvent			( const std::string& sEvent, int iButton, int iSearchDir ) = 0;
    virtual bool		nodeJavaScriptEvaluate	( const std::string& sJavaScript, int iSearchDir = crawl::NEAREST_AUTO ) = 0;
    virtual bool 		inputSet 				( const std::string& sValue, int iSearchDir = NEAREST_AUTO ) = 0;
    virtual bool 		inputSet 				( int 				 iValue, int iSearchDir = NEAREST_AUTO ) = 0;
    virtual std::string innerHtml               ( int iSearchDir = NEAREST_AUTO ) = 0;
    virtual bool 		innerHtmlSet 			( const std::string& sValue, int iSearchDir = NEAREST_AUTO ) = 0;
    virtual std::string innerText               ( int iSearchDir = NEAREST_AUTO ) = 0;
    virtual bool 		innerTextSet 			( const std::string& sValue, int iSearchDir = NEAREST_AUTO ) = 0;
    virtual bool		formSubmit				( int iSearchDir = NEAREST_AUTO ) = 0;
    virtual bool		formReset				( int iSearchDir = NEAREST_AUTO ) = 0;
    virtual int			selectLength			( int iSearchDir = NEAREST_AUTO ) = 0;
    virtual int			selectSelectedIndex		( int iSearchDir = NEAREST_AUTO ) = 0;
    virtual std::string	selectSelectedText		( int iSearchDir = NEAREST_AUTO ) = 0;
    virtual std::string	selectSelectedValue		( int iSearchDir = NEAREST_AUTO ) = 0;
    virtual int 		selectSelectedDomPos 	( int iSearchDir = NEAREST_AUTO ) = 0;
    virtual bool		selectSelect			( int iIndex, int iSearchDir = NEAREST_AUTO ) = 0;
    virtual bool		selectIndex             ( int iIndex, int iSearchDir = NEAREST_AUTO ) = 0;
    virtual bool		selectIndexWait         ( int iIndex, int timeoutInMs = timeoutInMsDefault, int iSearchDir = NEAREST_AUTO ) = 0;
    virtual bool		selectOption			( int iSearchDir = NEAREST_AUTO ) = 0;
    virtual bool		selectOptionWait		( int timeoutInMs = timeoutInMsDefault, int iSearchDir = NEAREST_AUTO ) = 0;
    virtual int         selectIndexOfOption		( int iSearchDir = crawl::NEAREST_AUTO ) = 0;
    virtual bool		doActionSimple			( const std::string& sAction, const std::string& sParam1, const std::string& sParam2, int iSearchDir ) = 0;
    virtual bool		doAction				( const std::string& sAction, const std::string& sParam1, const std::string& sParam2, int iSearchDir ) = 0;
    virtual bool		doAction				( const std::string& sAction, const std::string& sParam1, const std::string& sParam2 ) = 0;
    virtual bool		doAction				( const std::string& sAction, const std::string& sParam1, int iSearchDir = NEAREST_AUTO ) = 0;
    virtual bool		doAction				( const std::string& sAction, int iSearchDir = NEAREST_AUTO ) = 0;
    virtual float		nodeGeomPosX			( int iSearchDir = NEAREST_AUTO )= 0;
    virtual float		nodeGeomPosY			( int iSearchDir = NEAREST_AUTO )= 0;
    virtual float		nodeGeomWidth			( int iSearchDir = NEAREST_AUTO )= 0;
    virtual float		nodeGeomHeight			( int iSearchDir = NEAREST_AUTO )= 0;

    /*
    --------------------------------------
    --- DOM doActionFindNext functions ---
    -------------------------------------- */
    virtual int     doActionFindNextImpl        ( int iCount, const std::string& sSequence, const std::string& sAction,
                                                  const std::string& sParam1, const std::string& sParam2, int iSearchDir, bool bUpdateDomPos ) = 0;
    virtual int		doActionFindNext			( int iCount, const std::string& sSequence, const std::string& sAction, const std::string& sParam1,
                                                  const std::string& sParam2, int iSearchDir ) = 0;
    virtual int		doActionFindNext			( int iCount, const std::string& sSequence, const std::string& sAction, const std::string& sParam1,
                                                  const std::string& sParam2 ) = 0;
    virtual int		doActionFindNext			( int iCount, const std::string& sSequence, const std::string& sAction, const std::string& sParam1,
                                                  int iSearchDir = NEAREST_AUTO ) = 0;
    virtual int		doActionFindNext			( int iCount, const std::string& sSequence, const std::string& sAction, int iSearchDir = NEAREST_AUTO ) = 0;

    virtual int		doActionFindNext			( const std::string& sSequence, const std::string& sAction, const std::string& sParam1,
                                                  const std::string& sParam2, int iSearchDir ) = 0;
    virtual int		doActionFindNext			( const std::string& sSequence, const std::string& sAction, const std::string& sParam1,
                                                  const std::string& sParam2 ) = 0;
    virtual int		doActionFindNext			( const std::string& sSequence, const std::string& sAction, const std::string& sParam1,
                                                  int iSearchDir = NEAREST_AUTO ) = 0;
    virtual int		doActionFindNext			( const std::string& sSequence, const std::string& sAction, int iSearchDir = NEAREST_AUTO ) = 0;

    /*
    ----------------------------------
    --- DOM doActionFind functions ---
    ---------------------------------- */
    virtual int		doActionFind				( int iCount, const std::string& sSequence, const std::string& sAction, const std::string& sParam1,
                                                  const std::string& sParam2, int iSearchDir ) = 0;
    virtual int		doActionFind				( int iCount, const std::string& sSequence, const std::string& sAction, const std::string& sParam1,
                                                  const std::string& sParam2 ) = 0;
    virtual int		doActionFind				( int iCount, const std::string& sSequence, const std::string& sAction, const std::string& sParam1,
                                                  int iSearchDir = NEAREST_AUTO ) = 0;
    virtual int		doActionFind				( int iCount, const std::string& sSequence, const std::string& sAction, int iSearchDir = NEAREST_AUTO ) = 0;

    virtual int		doActionFind				( const std::string& sSequence, const std::string& sAction, const std::string& sParam1,
                                                  const std::string& sParam2, int iSearchDir ) = 0;
    virtual int		doActionFind				( const std::string& sSequence, const std::string& sAction, const std::string& sParam1,
                                                  const std::string& sParam2 ) = 0;
    virtual int		doActionFind				( const std::string& sSequence, const std::string& sAction, const std::string& sParam1,
                                                  int iSearchDir = NEAREST_AUTO ) = 0;
    virtual int		doActionFind				( const std::string& sSequence, const std::string& sAction, int iSearchDir = NEAREST_AUTO ) = 0;

    /*
    -----------------------------------
    --- DOM Action create functions ---
    ----------------------------------- */
    virtual void		domActionCreate			( 	const std::string& sName, const std::string& sAction, const std::string& sParam1,
                                                    const std::string& sParam2, int iSearchDir ) = 0;
    virtual void		domActionCreate			( 	const std::string& sName, const std::string& sAction, const std::string& sParam1,
                                                    const std::string& sParam2 ) = 0;
    virtual void		domActionCreate			( 	const std::string& sName, const std::string& sAction, const std::string& sParam1,
                                                    int iSearchDir = NEAREST_AUTO ) = 0;
    virtual void		domActionCreate			( 	const std::string& sName, const std::string& sAction, int iSearchDir = NEAREST_AUTO ) = 0;

    /*
    --------------------------------------------------------------------
    --- Modifier create functions (OutputModifier create functions)  ---
    -------------------------------------------------------------------- */
    virtual void modifierCreate					(	const std::string& sModifierID, const std::string& sManipFunID, const std::string& sManipParam1,
                                                    const std::string& sManipParam2, const std::string& sManipParam3, const std::string& sManipParam4 ) = 0;
    virtual void modifierCreate					(	const std::string& sModifierID, const std::string& sManipFunID, const std::string& sManipParam1,
                                                    const std::string& sManipParam2, const std::string& sManipParam3 ) = 0;
    virtual void modifierCreate					(	const std::string& sModifierID, const std::string& sManipFunID, const std::string& sManipParam1,
                                                    const std::string& sManipParam2 ) = 0;
    virtual void modifierCreate					(	const std::string& sModifierID, const std::string& sManipFunID, const std::string& sManipParam1 ) = 0;
    virtual void modifierCreate					(	const std::string& sModifierID, const std::string& sManipFunID ) = 0;

    /*
    -----------------------------
    --- nodeXX misc functions ---
    ----------------------------- */
    virtual int         nodeLevel               () = 0;
    virtual std::string	nodeXPath               () = 0;

    /*
    ------------------------------
    --- nodeValuePos functions ---
    ------------------------------ */
    virtual std::string	nodeValuePos			( int iDomPos, const std::string& sModifierID, const std::string& sManipParam1,
                                                  const std::string& sManipParam2, const std::string& sManipParam3,
                                                  const std::string& sManipParam4 ) = 0;
    virtual std::string	nodeValuePos			( int iDomPos, const std::string& sModifierID, const std::string& sManipParam1,
                                                  const std::string& sManipParam2, const std::string& sManipParam3 ) = 0;
    virtual std::string	nodeValuePos			( int iDomPos, const std::string& sModifierID, const std::string& sManipParam1,
                                                  const std::string& sManipParam2 ) = 0;
    virtual std::string	nodeValuePos			( int iDomPos, const std::string& sModifierID, const std::string& sManipParam1 ) = 0;
    virtual std::string	nodeValuePos			( int iDomPos, const std::string& sModifierID ) = 0;
    virtual std::string	nodeValuePos			( int iDomPos ) = 0;

    /*
    ---------------------------
    --- nodeValue functions ---
    --------------------------- */
    virtual std::string	nodeValue			( const std::string& sModifierID, const std::string& sManipParam1,
                                              const std::string& sManipParam2, const std::string& sManipParam3,
                                              const std::string& sManipParam4 ) = 0;
    virtual std::string	nodeValue			( const std::string& sModifierID, const std::string& sManipParam1,
                                              const std::string& sManipParam2, const std::string& sManipParam3 ) = 0;
    virtual std::string	nodeValue			( const std::string& sModifierID, const std::string& sManipParam1,
                                              const std::string& sManipParam2 ) = 0;
    virtual std::string	nodeValue			( const std::string& sModifierID, const std::string& sManipParam1 ) = 0;
    virtual std::string	nodeValue			( const std::string& sModifierID ) = 0;
    virtual std::string	nodeValue			() = 0;

    virtual std::string	posValue			( int iDomPos, const std::string& sModifierID, const std::string& sManipParam1,
                                              const std::string& sManipParam2, const std::string& sManipParam3,
                                              const std::string& sManipParam4 ) = 0;
    virtual std::string	posValue			( int iDomPos, const std::string& sModifierID, const std::string& sManipParam1,
                                              const std::string& sManipParam2, const std::string& sManipParam3 ) = 0;
    virtual std::string	posValue			( int iDomPos, const std::string& sModifierID, const std::string& sManipParam1,
                                              const std::string& sManipParam2 ) = 0;
    virtual std::string	posValue			( int iDomPos, const std::string& sModifierID, const std::string& sManipParam1 ) = 0;
    virtual std::string	posValue			( int iDomPos, const std::string& sModifierID ) = 0;
    virtual std::string	posValue			( int iDomPos ) = 0;

    /*
    ---------------------------------
    --- nodeValueParent functions ---
    --------------------------------- */
    virtual std::string	nodeValueParent			( int iLevelsUp, const std::string& sModifierID, const std::string& sManipParam1,
                                                  const std::string& sManipParam2, const std::string& sManipParam3,
                                                  const std::string& sManipParam4 ) = 0;
    virtual std::string	nodeValueParent			( int iLevelsUp, const std::string& sModifierID, const std::string& sManipParam1,
                                                  const std::string& sManipParam2, const std::string& sManipParam3 ) = 0;
    virtual std::string	nodeValueParent			( int iLevelsUp, const std::string& sModifierID, const std::string& sManipParam1,
                                                  const std::string& sManipParam2 ) = 0;
    virtual std::string	nodeValueParent			( int iLevelsUp, const std::string& sModifierID, const std::string& sManipParam1 ) = 0;
    virtual std::string	nodeValueParent			( int iLevelsUp, const std::string& sModifierID ) = 0;
    virtual std::string	nodeValueParent			( int iLevelsUp ) = 0;


    /*
    ---------------------------------
    --- nodeAttribute functions ---
    --------------------------------- */
    virtual std::string	nodeAttribute			( const std::string& sAttribute, const std::string& sModifierID, const std::string& sManipParam1,
                                                  const std::string& sManipParam2, const std::string& sManipParam3,
                                                  const std::string& sManipParam4 ) = 0;
    virtual std::string	nodeAttribute			( const std::string& sAttribute, const std::string& sModifierID, const std::string& sManipParam1,
                                                  const std::string& sManipParam2, const std::string& sManipParam3 ) = 0;
    virtual std::string	nodeAttribute			( const std::string& sAttribute, const std::string& sModifierID, const std::string& sManipParam1,
                                                  const std::string& sManipParam2 ) = 0;
    virtual std::string	nodeAttribute			( const std::string& sAttribute, const std::string& sModifierID, const std::string& sManipParam1 ) = 0;
    virtual std::string	nodeAttribute			( const std::string& sAttribute, const std::string& sModifierID ) = 0;
    virtual std::string	nodeAttribute			( const std::string& sAttribute ) = 0;

    virtual std::string	posAttribute			( int iDomPos, const std::string& sAttribute, const std::string& sModifierID,
                                                  const std::string& sManipParam1,const std::string& sManipParam2,
                                                  const std::string& sManipParam3, const std::string& sManipParam4 ) = 0;
    virtual std::string	posAttribute			( int iDomPos, const std::string& sAttribute, const std::string& sModifierID,
                                                  const std::string& sManipParam1, const std::string& sManipParam2,
                                                  const std::string& sManipParam3 ) = 0;
    virtual std::string	posAttribute			( int iDomPos, const std::string& sAttribute, const std::string& sModifierID,
                                                  const std::string& sManipParam1, const std::string& sManipParam2 ) = 0;
    virtual std::string	posAttribute			( int iDomPos, const std::string& sAttribute, const std::string& sModifierID,
                                                  const std::string& sManipParam1 ) = 0;
    virtual std::string	posAttribute			( int iDomPos, const std::string& sAttribute, const std::string& sModifierID ) = 0;
    virtual std::string	posAttribute			( int iDomPos, const std::string& sAttribute ) = 0;

    /*
    ---------------------------------
    --- nodeText functions ---
    --------------------------------- */
    virtual std::string	nodeText                ( const std::string& sModifierID, const std::string& sManipParam1,
                                                  const std::string& sManipParam2, const std::string& sManipParam3,
                                                  const std::string& sManipParam4 ) = 0;
    virtual std::string	nodeText                ( const std::string& sModifierID, const std::string& sManipParam1,
                                                  const std::string& sManipParam2, const std::string& sManipParam3 ) = 0;
    virtual std::string	nodeText                ( const std::string& sModifierID, const std::string& sManipParam1,
                                                  const std::string& sManipParam2 ) = 0;
    virtual std::string	nodeText                ( const std::string& sModifierID, const std::string& sManipParam1 ) = 0;
    virtual std::string	nodeText                ( const std::string& sModifierID ) = 0;
    virtual std::string	nodeText                () = 0;

    /*
    -----------------------------
    --- nodeCompare functions ---
    ----------------------------- */
    virtual bool		nodeCompare				( const std::string& sPattern, const std::string& sCompareFun, const std::string& sModifierID,
                                                  const std::string& sManipParam1, const std::string& sManipParam2,
                                                  const std::string& sManipParam3, const std::string& sManipParam4 ) = 0;
    virtual bool		nodeCompare				( const std::string& sPattern, const std::string& sCompareFun, const std::string& sModifierID,
                                                  const std::string& sManipParam1, const std::string& sManipParam2,
                                                  const std::string& sManipParam3 ) = 0;
    virtual bool		nodeCompare				( const std::string& sPattern, const std::string& sCompareFun, const std::string& sModifierID,
                                                  const std::string& sManipParam1, const std::string& sManipParam2 ) = 0;
    virtual bool		nodeCompare				( const std::string& sPattern, const std::string& sCompareFun, const std::string& sModifierID,
                                                  const std::string& sManipParam1 ) = 0;
    virtual bool		nodeCompare				( const std::string& sPattern, const std::string& sCompareFun, const std::string& sModifierID ) = 0;
    virtual bool		nodeCompare				( const std::string& sPattern, const std::string& sCompareFun ) = 0;

    /*
    -----------------------
    --- Parse functions ---
    ----------------------- */
    virtual bool		parseRegex			(	int iCount, const std::string& sRegex,		int postMarkerPos = MATCH_FIRST		) = 0;
    virtual bool		iparseRegex			(	int iCount, const std::string& sRegex,		int postMarkerPos = MATCH_FIRST		) = 0;
    virtual bool		parseToRegex		(	int iCount, const std::string& sRegex,		int postMarkerPos = MATCH_FIRST		) = 0;
    virtual bool		iparseToRegex		(	int iCount, const std::string& sRegex,		int postMarkerPos = MATCH_FIRST		) = 0;
    virtual bool		parseToString		(	int iCount, const std::string& sSubstring,	int postMarkerPos = MATCH_FIRST		) = 0;
    virtual bool		iparseToString		(	int iCount, const std::string& sSubstring,	int postMarkerPos = MATCH_FIRST		) = 0;
    virtual bool		parseToEnd			() = 0;
    virtual std::string	getParseMatch		( int iMatchNumber ) = 0;
    virtual std::string	getParseRest		() = 0;
    virtual int			getParseMatchCount	() = 0;

    /*
    ----------------------
    --- Text functions ---
    ---------------------- */
    virtual void		textNewSearch		() = 0;
    virtual bool		findBegin			(	int iCount, const std::string& sSearchFor, 	int setBeginToPos = MATCH_LAST	) = 0;
    virtual bool		findEnd				(	int iCount, const std::string& sSearchFor, 	int setBeginToPos = MATCH_FIRST	) = 0;
    virtual bool		findBeginNext		(	int iCount, const std::string& sSearchFor, 	int setBeginToPos = MATCH_LAST 	) = 0;
    virtual bool		findEndNext			(	int iCount, const std::string& sSearchFor, 	int setBeginToPos = MATCH_FIRST	) = 0;
    virtual bool		ifindBegin			(	int iCount, const std::string& sSearchFor, 	int setBeginToPos = MATCH_LAST	) = 0;
    virtual bool		ifindEnd			(	int iCount, const std::string& sSearchFor, 	int setBeginToPos = MATCH_FIRST	) = 0;
    virtual bool		ifindBeginNext		(	int iCount, const std::string& sSearchFor, 	int setBeginToPos = MATCH_LAST 	) = 0;
    virtual bool		ifindEndNext		(	int iCount, const std::string& sSearchFor, 	int setBeginToPos = MATCH_FIRST	) = 0;
    virtual bool		findRegexBegin		(	int iCount, const std::string& sRegex,		int setBeginToPos = MATCH_LAST	) = 0;
    virtual bool		findRegexEnd		(	int iCount, const std::string& sRegex, 		int setBeginToPos = MATCH_FIRST	) = 0;
    virtual bool		findRegexBeginNext	(	int iCount, const std::string& sRegex,		int setBeginToPos = MATCH_LAST	) = 0;
    virtual bool		findRegexEndNext	(	int iCount, const std::string& sRegex, 		int setBeginToPos = MATCH_FIRST	) = 0;
    virtual bool		stepBegin			(	int iCount	) = 0;
    virtual bool		stepEnd				(	int iCount	) = 0;

    /*
    -----------------------------
    --- (URL) queue functions ---
    ----------------------------- */

    virtual int			urlQueueSize			()	const = 0;
    virtual int			urlQueueSizeProcessed	()	const = 0;
    virtual bool        urlQueueAlreadyProcessed( const std::string& sUrl ) const = 0;
    virtual void		urlQueueClear			()	 = 0;
    virtual std::string	urlQueueFront			()	 = 0;
    virtual void		urlQueueAppend			(	int iLinkType, const std::string& sUrlsMatch ="", const std::string& sCompareFun = "contains" )	 = 0;
    virtual void		urlQueueAppendUnique	(	int iLinkType, const std::string& sUrlsMatch ="", const std::string& sCompareFun = "contains" )	 = 0;
    virtual void		urlQueueAppend			(	const std::string& sUrl		)	 = 0;
    virtual void		urlQueueAppendUnique	(	const std::string& sUrl		)	 = 0;
    virtual void		urlQueuePrepend			(	const std::string& sUrl		)	 = 0;
    virtual void		urlQueuePrependUnique	(	const std::string& sUrl		)	 = 0;

    /*
    -----------------------------
    --- linksGetter functions ---
    ----------------------------- */
    virtual void		linksGetterDebugPrint	() = 0;

    /*
    --------------------------
    --- valueSet functions ---
    -------------------------- */
    virtual void		valueSet				( const std::string& sValue ) = 0;

    /*
    --------------------------
    --- valueGet functions ---
    -------------------------- */
    virtual std::string	valueGet				( const std::string& sModifierID, const std::string& sManipParam1, const std::string& sManipParam2,
                                                  const std::string& sManipParam3, const std::string& sManipParam4 ) = 0;
    virtual std::string	valueGet				( const std::string& sModifierID, const std::string& sManipParam1, const std::string& sManipParam2,
                                                  const std::string& sManipParam3 ) = 0;
    virtual std::string	valueGet				( const std::string& sModifierID, const std::string& sManipParam1, const std::string& sManipParam2 ) = 0;
    virtual std::string	valueGet				( const std::string& sModifierID, const std::string& sManipParam1 ) = 0;
    virtual std::string	valueGet				( const std::string& sModifierID ) = 0;
    virtual std::string	valueGet				() = 0;

    /*
    ------------------------------
    --- valueCompare functions ---
    ------------------------------ */
    virtual bool	valueCompare				( const std::string& sPattern, const std::string& sCompareFun, const std::string& sModifierID,
                                                  const std::string& sManipParam1, const std::string& sManipParam2, const std::string& sManipParam3,
                                                  const std::string& sManipParam4 ) = 0;
    virtual bool	valueCompare				( const std::string& sPattern, const std::string& sCompareFun, const std::string& sModifierID,
                                                  const std::string& sManipParam1, const std::string& sManipParam2, const std::string& sManipParam3 ) = 0;
    virtual bool	valueCompare				( const std::string& sPattern, const std::string& sCompareFun, const std::string& sModifierID,
                                                  const std::string& sManipParam1, const std::string& sManipParam2 ) = 0;
    virtual bool	valueCompare				( const std::string& sPattern, const std::string& sCompareFun, const std::string& sModifierID,
                                                  const std::string& sManipParam1 ) = 0;
    virtual bool	valueCompare				( const std::string& sPattern, const std::string& sCompareFun, const std::string& sModifierID ) = 0;
    virtual bool	valueCompare				( const std::string& sPattern, const std::string& sCompareFun ) = 0;

    /*
    --------------------------------
    --- outputValueGet functions ---
    -------------------------------- */
    virtual std::string	outputValueContextGet	( const std::string& sFieldName, const std::string& sContextName ) = 0;
    virtual std::string	outputValueGet  		( const std::string& sFieldName, const std::string& sModifierID, const std::string& sManipParam1,
                                                  const std::string& sManipParam2, const std::string& sManipParam3, const std::string& sManipParam4 ) = 0;
    virtual std::string	outputValueGet			( const std::string& sFieldName, const std::string& sModifierID, const std::string& sManipParam1,
                                                  const std::string& sManipParam2, const std::string& sManipParam3 ) = 0;
    virtual std::string	outputValueGet			( const std::string& sFieldName, const std::string& sModifierID, const std::string& sManipParam1,
                                                  const std::string& sManipParam2 ) = 0;
    virtual std::string	outputValueGet			( const std::string& sFieldName, const std::string& sModifierID, const std::string& sManipParam1 ) = 0;
    virtual std::string	outputValueGet			( const std::string& sFieldName, const std::string& sModifierID ) = 0;
    virtual std::string	outputValueGet			( const std::string& sFieldName) = 0;

    /*
    ------------------------------
    --- Modify value functions ---
    ------------------------------ */
    virtual std::string	valueModify				( const std::string& sModifierID, const std::string& sManipParam1, const std::string& sManipParam2,
                                                  const std::string& sManipParam3, const std::string& sManipParam4 ) = 0;
    virtual std::string	valueModify				( const std::string& sModifierID, const std::string& sManipParam1, const std::string& sManipParam2,
                                                  const std::string& sManipParam3 ) = 0;
    virtual std::string	valueModify				( const std::string& sModifierID, const std::string& sManipParam1, const std::string& sManipParam2 ) = 0;
    virtual std::string	valueModify				( const std::string& sModifierID, const std::string& sManipParam1 ) = 0;
    virtual std::string	valueModify				( const std::string& sModifierID ) = 0;


    /*
    -------------------------
    --- Context functions ---
    ------------------------- */
    virtual void		dataPushContext			(	std::string sContext, std::string const& sUnit = "" ) = 0;
    virtual void		dataPushContextAlias	(	const std::string& sContext, const std::string& sContextAlias, const std::string& sUnit = "" ) = 0;
    virtual void		dataPopContext			() = 0;

    virtual void		contextBegin                (	std::string sContextName ) = 0;
    virtual void		contextEnd                  () = 0;

    virtual void        contextOutputSaveAs         ( const std::string& sContextName ) = 0;
    virtual void        contextFallbackOutputLoad   ( const std::string& sContextName ) = 0;
    virtual void        contextFallbackOutputClear  () = 0;
    virtual std::string contextFallbackValueGet     ( const std::string& sFieldName ) const = 0;
    virtual void        contextFallbackValueSet     ( const std::string& sFieldName, const std::string& sValue )  = 0;

    virtual bool        contextFallbackValueExists  ( const std::string& sFieldName ) const = 0;
    virtual void        contextFallbackValueDelete  ( const std::string& sFieldName ) = 0;
    virtual bool        contextSavedOutputExists    ( const std::string& sContextName ) const = 0;

    virtual void        contextSavedOutputDelete    ( const std::string& sContextName ) = 0;

    /*
    ------------------------
    --- Output functions ---
    ------------------------ */
    virtual void		outputDirectUnit		( const std::string& sFieldName, const std::string& sValue, const std::string& sUnit,
                                                  const std::string& sModifierID, const std::string& sManipParam1, const std::string& sManipParam2,
                                                  const std::string& sManipParam3, const std::string& sManipParam4 ) = 0;
    virtual void		outputDirectUnit		( const std::string& sFieldName, const std::string& sValue, const std::string& sUnit,
                                                  const std::string& sModifierID, const std::string& sManipParam1, const std::string& sManipParam2,
                                                  const std::string& sManipParam3 ) = 0;
    virtual void		outputDirectUnit		( const std::string& sFieldName, const std::string& sValue, const std::string& sUnit,
                                                  const std::string& sModifierID, const std::string& sManipParam1, const std::string& sManipParam2 ) = 0;
    virtual void		outputDirectUnit		( const std::string& sFieldName, const std::string& sValue, const std::string& sUnit,
                                                  const std::string& sModifierID, const std::string& sManipParam1 ) = 0;
    virtual void		outputDirectUnit		( const std::string& sFieldName, const std::string& sValue, const std::string& sUnit,
                                                  const std::string& sModifierID ) = 0;
    virtual void		outputDirectUnit		( const std::string& sFieldName, const std::string& sValue, const std::string& sUnit ) = 0;
    // ---
    virtual void		outputDirect			( const std::string& sFieldName, const std::string& sValue, const std::string& sModifierID,
                                                  const std::string& sManipParam1, const std::string& sManipParam2, const std::string& sManipParam3,
                                                  const std::string& sManipParam4 ) = 0;
    virtual void		outputDirect			( const std::string& sFieldName, const std::string& sValue, const std::string& sModifierID,
                                                  const std::string& sManipParam1, const std::string& sManipParam2, const std::string& sManipParam3 ) = 0;
    virtual void		outputDirect			( const std::string& sFieldName, const std::string& sValue, const std::string& sModifierID,
                                                  const std::string& sManipParam1, const std::string& sManipParam2 ) = 0;
    virtual void		outputDirect			( const std::string& sFieldName, const std::string& sValue, const std::string& sModifierID,
                                                  const std::string& sManipParam1 ) = 0;
    virtual void		outputDirect			( const std::string& sFieldName, const std::string& sValue, const std::string& sModifierID ) = 0;
    virtual void		outputDirect			( const std::string& sFieldName, const std::string& sValue ) = 0;

    //----

    virtual void		outputValueUnit			( const std::string& sFieldName, const std::string& sUnit, const std::string& sModifierID,
                                                  const std::string& sManipParam1, const std::string& sManipParam2,
                                                  const std::string& sManipParam3, const std::string& sManipParam4 ) = 0;
    virtual void		outputValueUnit			( const std::string& sFieldName, const std::string& sUnit, const std::string& sModifierID,
                                                  const std::string& sManipParam1, const std::string& sManipParam2,
                                                  const std::string& sManipParam3 ) = 0;
    virtual void		outputValueUnit			( const std::string& sFieldName, const std::string& sUnit, const std::string& sModifierID,
                                                  const std::string& sManipParam1, const std::string& sManipParam2 ) = 0;
    virtual void		outputValueUnit			( const std::string& sFieldName, const std::string& sUnit, const std::string& sModifierID,
                                                  const std::string& sManipParam1 ) = 0;
    virtual void		outputValueUnit			( const std::string& sFieldName, const std::string& sUnit, const std::string& sModifierID ) = 0;
    virtual void		outputValueUnit			( const std::string& sFieldName, const std::string& sUnit ) = 0;

    //----

    virtual void		outputValue				( const std::string& sFieldName, const std::string& sModifierID, const std::string& sManipParam1,
                                                  const std::string& sManipParam2, const std::string& sManipParam3, const std::string& sManipParam4 ) = 0;
    virtual void		outputValue				( const std::string& sFieldName, const std::string& sModifierID, const std::string& sManipParam1,
                                                  const std::string& sManipParam2, const std::string& sManipParam3 ) = 0;
    virtual void		outputValue				( const std::string& sFieldName, const std::string& sModifierID, const std::string& sManipParam1,
                                                  const std::string& sManipParam2 ) = 0;
    virtual void		outputValue				( const std::string& sFieldName, const std::string& sModifierID, const std::string& sManipParam1 ) = 0;
    virtual void		outputValue				( const std::string& sFieldName, const std::string& sModifierID ) = 0;
    virtual void		outputValue				( const std::string& sFieldName ) = 0;

    /*
    -------------------------------------
    --- outputValueFindNext functions ---
    ------------------------------------- */

    virtual int         outputValueFindNextImpl (  int iCount, const std::string& sSequence, const std::string& sFieldName
                                                 , const std::string& sModifierID, const std::string& sManipParam1
                                                 , const std::string& sManipParam2, const std::string& sManipParam3
                                                 , const std::string& sManipParam4, bool bUpdateDomPos ) = 0;
    virtual int			outputValueFindNext		( int iCount, const std::string& sSequence,	const std::string& sFieldName, const std::string& sModifierID,
                                                  const std::string& sManipParam1, const std::string& sManipParam2, const std::string& sManipParam3,
                                                  const std::string& sManipParam4 ) = 0;
    virtual int			outputValueFindNext		( int iCount, const std::string& sSequence,	const std::string& sFieldName, const std::string& sModifierID,
                                                  const std::string& sManipParam1, const std::string& sManipParam2, const std::string& sManipParam3	) = 0;
    virtual int			outputValueFindNext		( int iCount, const std::string& sSequence,	const std::string& sFieldName, const std::string& sModifierID,
                                                  const std::string& sManipParam1, const std::string& sManipParam2	) = 0;
    virtual int			outputValueFindNext		( int iCount, const std::string& sSequence,	const std::string& sFieldName, const std::string& sModifierID,
                                                  const std::string& sManipParam1 ) = 0;
    virtual int			outputValueFindNext		( int iCount, const std::string& sSequence,	const std::string& sFieldName, const std::string& sModifierID ) = 0;
    virtual int			outputValueFindNext		( int iCount, const std::string& sSequence,	const std::string& sFieldName ) = 0;
//    virtual int			outputValueFindNext		( int iCount, const std::string& sSequence,	const std::string& sFieldName ) = 0;

    virtual int			outputValueFindNext		( const std::string& sSequence,	const std::string& sFieldName, const std::string& sModifierID,
                                                  const std::string& sManipParam1, const std::string& sManipParam2, const std::string& sManipParam3,
                                                  const std::string& sManipParam4 ) = 0;
    virtual int			outputValueFindNext		( const std::string& sSequence,	const std::string& sFieldName, const std::string& sModifierID,
                                                  const std::string& sManipParam1, const std::string& sManipParam2, const std::string& sManipParam3	) = 0;
    virtual int			outputValueFindNext		( const std::string& sSequence,	const std::string& sFieldName, const std::string& sModifierID,
                                                  const std::string& sManipParam1, const std::string& sManipParam2	) = 0;
    virtual int			outputValueFindNext		( const std::string& sSequence,	const std::string& sFieldName, const std::string& sModifierID,
                                                  const std::string& sManipParam1 ) = 0;
    virtual int			outputValueFindNext		( const std::string& sSequence,	const std::string& sFieldName, const std::string& sModifierID ) = 0;
    virtual int			outputValueFindNext		( const std::string& sSequence,	const std::string& sFieldName ) = 0;


    /*
    ---------------------------------
    --- outputValueFind functions ---
    --------------------------------- */
    virtual int			outputValueFind			( int iCount, const std::string& sSequence,	const std::string& sFieldName, const std::string& sModifierID,
                                                  const std::string& sManipParam1, const std::string& sManipParam2, const std::string& sManipParam3,
                                                  const std::string& sManipParam4 ) = 0;
    virtual int			outputValueFind			( int iCount, const std::string& sSequence,	const std::string& sFieldName, const std::string& sModifierID,
                                                  const std::string& sManipParam1, const std::string& sManipParam2, const std::string& sManipParam3	) = 0;
    virtual int			outputValueFind			( int iCount, const std::string& sSequence,	const std::string& sFieldName, const std::string& sModifierID,
                                                  const std::string& sManipParam1, const std::string& sManipParam2	) = 0;
    virtual int			outputValueFind			( int iCount, const std::string& sSequence,	const std::string& sFieldName, const std::string& sModifierID,
                                                  const std::string& sManipParam1 ) = 0;
    virtual int			outputValueFind			( int iCount, const std::string& sSequence,	const std::string& sFieldName, const std::string& sModifierID ) = 0;
    virtual int			outputValueFind			( int iCount, const std::string& sSequence,	const std::string& sFieldName ) = 0;

    virtual int			outputValueFind			( const std::string& sSequence,	const std::string& sFieldName, const std::string& sModifierID,
                                                  const std::string& sManipParam1, const std::string& sManipParam2, const std::string& sManipParam3,
                                                  const std::string& sManipParam4 ) = 0;
    virtual int			outputValueFind			( const std::string& sSequence,	const std::string& sFieldName, const std::string& sModifierID,
                                                  const std::string& sManipParam1, const std::string& sManipParam2, const std::string& sManipParam3	) = 0;
    virtual int			outputValueFind			( const std::string& sSequence,	const std::string& sFieldName, const std::string& sModifierID,
                                                  const std::string& sManipParam1, const std::string& sManipParam2	) = 0;
    virtual int			outputValueFind			( const std::string& sSequence,	const std::string& sFieldName, const std::string& sModifierID,
                                                  const std::string& sManipParam1 ) = 0;
    virtual int			outputValueFind			( const std::string& sSequence,	const std::string& sFieldName, const std::string& sModifierID ) = 0;
    virtual int			outputValueFind			( const std::string& sSequence,	const std::string& sFieldName ) = 0;




    /*
    ----------------------------
    --- Javascript functions ---
    ---------------------------- */
    virtual bool 		javaScriptExecuteRetVal	( const std::string& sScript, std::string& sScriptReturnValue 	) = 0;
    virtual bool 		javaScriptExecute		( const std::string& sScript									) = 0;
    virtual bool 		javaScriptExecuteWait	( const std::string& sScript, int timeoutInMs = timeoutInMsDefault) = 0;

    /*
    -------------------------
    --- Utility functions ---
    ------------------------- */
    virtual int 		curlPostUploadFileSimple( const std::string& sURL, const std::string& sFieldName, const std::string& sFilePath 	) = 0;
    virtual bool 		gzCompressFile			( const std::string& sSrcFilePath, const std::string& sDstFilePath ) = 0;
    virtual bool 		gzUnCompressFile		( const std::string& sSrcFilePath, const std::string& sDstFilePath ) = 0;


    /*
    --------------------------
    --- Settings functions ---
    -------------------------- */
    virtual void		settingDelete           (	const std::string& sName ) = 0;
    virtual void		settingSet              (	const std::string& sName, const std::string& sValue ) = 0;
    virtual std::string settingGet              (	const std::string& sName, const std::string& defaultValue = "" ) const = 0;
    virtual bool        settingExists           (	const std::string& sName ) const = 0;
    virtual bool        hasSetting              (	const std::string& sName ) const = 0;
    virtual bool        settingBoolGet          (   const std::string& sName, bool defaultValue = false ) const = 0;

    /*
    ------------------------
    --- Config functions ---
    ------------------------ */
    virtual void            runModeSet              ( crawl::RunModeE eRunMode ) = 0;
    virtual crawl::RunModeE	runMode                 () const = 0;

    virtual std::string configValueGet              ( const std::string& sName ) = 0;
    virtual void		configValueSet              ( const std::string& sName, const std::string& sValue ) = 0;
    virtual bool        configValueBoolGet          ( const std::string& sName ) const = 0;
    virtual void        configUrlStartSet           ( const std::string& sUrl	) = 0;
    virtual void		configUrlUploadDataSet      ( const std::string sUrl 	) = 0;
    virtual std::string	configUrlUploadDataGet      () const     = 0;

    virtual void		configDisableLoadImages     () = 0;
    virtual void		configForceLoadImages       () = 0;

    virtual void 		configAddIncludeUrl         ( const std::string& sPattern, const std::string& sCompareFun ) = 0;
    virtual void 		configAddExcludeUrl         ( const std::string& sPattern, const std::string& sCompareFun ) = 0;

    virtual void        configUploadData            ( bool bUploadData ) = 0;
    virtual void		configForceSendXmlData      () = 0;
    virtual void        configAjaxPageLoadDeltaTime (int iMilliSeconds ) = 0;
    virtual void		configReloadTimeOut         ( int iMinutes, int iSecs ) = 0;
    virtual void		configKeepActiveInterval    ( int iSecs ) = 0;
    int                 configDelayPageLoadedTime   () const;
    void                configDelayPageLoadedTimeSet(int milliseconds);

    virtual void		configProgressOutputSet     ( bool bEnable ) = 0;
    virtual void		configDebugOutputSet        ( bool bEnable ) = 0;
    virtual bool		configDebugOutputGet        () = 0;

    virtual void 		configParseDecimalPointSet  ( const std::string& sDecimalPoint ) = 0;
    virtual void 		configParseThousandsSepSet  ( const std::string& sThousandsSep ) = 0;
    virtual std::string	configParseDecimalPointGet  () const = 0;
    virtual std::string	configParseThousandsSepGet  () const = 0;
    virtual std::string configGetRunMode            () const = 0;
//    virtual void 		configInsertEndTagNodes     ( bool bInsertEndTagNodes )	= 0;
//    virtual void 		configSkipEmptyNodes        ( bool bSkipEmptyNodes ) = 0;																	;
//    virtual void 		configTrimBlanks            ( bool bTrimBlanks ) = 0;																	;
    virtual void		configOutputEncloseCDATA    ( bool bDoEncloseInCDATA ) = 0;
    virtual void		configOutputWriteToFile     ( bool bDoWriteOutputToFile ) = 0;
    virtual void		configLocaleSettingsSet     ( const std::string& country_or_currency_code ) = 0;

    /*
    -----------------------
    --- Debug functions ---
    ----------------------- */
    virtual void        locatedPositionsClear   () = 0;
    virtual void		domDebugPrint			( const std::string& sFileName="" ) = 0;
    virtual void		nodeDebugPrint			( int iNodesBefore, int iNodesAfter, bool bPrintNodeTypes = false ) = 0;
    virtual void		nodeDebugPrint			( int iNodesAround=10, bool bPrintNodeTypes = false ) = 0;
    virtual std::string	nodeValueDebug			( int iNodesBefore, int iNodesAfter, bool bPrintNodeTypes = false )= 0;
    virtual std::string	nodeValueDebug			( int iNodesAround=10, bool bPrintNodeTypes = false ) = 0;

    // --------------------------------------
    // --- PUBLIC: General info functions ---
    // ---------------------------------------
    virtual int                                 infoMiningDoneStatus            () const = 0;
    virtual const boost::posix_time::ptime& 	infoTimeMiningStarted           () const = 0;
    virtual const boost::posix_time::ptime&     infoTimeLastPageLoadStarted     () const = 0;
    virtual const boost::posix_time::ptime&     infoTimeLastPageLoadFinished    () const = 0;
    virtual const std::string&					infoCurrentLoadingUrl           () const = 0;
    virtual const std::string&                  infoLatestFullyLoadedUrl        () const = 0;
    virtual boost::uint64_t                     infoPageLoadsTotal              () const = 0;
    virtual int                                 infoLastNetworkError            () const = 0;

private:
    boost::shared_ptr<Configuration>        m_pConfig;
    boost::shared_ptr<ScriptingClassIF>     m_pScriptingClassIF;
    int                                     m_lfwDomStartPos;
    int                                     m_lfwDomStopPos;
};

} //END namespace crawl




