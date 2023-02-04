#pragma once

#include <memory>
#include <mutex>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <Crawler.h>
#include <ScriptMinerIF.h>
#include <DomNodeIF.h>
#include <LinearDomIF.h>
#include <MinerWorkerIF.h>
#include <applicationutils/CrawlerCommandQueue.h>
#include <navigator/SiteMapGetter.h>
#include <parser/LookForWordDomFinder.h>

namespace crawl {
    class StateMachineMgr;
    class WebBrowserIF;
    class StatusFile;
    class MinerWorker;
    class LookForWordMgr;
}


class ScriptMiner : public QObject, public crawl::Crawler {
Q_OBJECT
public:
    // ------------------------
    // --- PUBLIC: Typedefs ---
    // ------------------------
    typedef std::vector<std::string>						FunctionsVecT;
    typedef std::set<std::string>							FunctionsSetT;

    // ----------------------------------
    // --- PUBLIC: Static member vars ---
    // ----------------------------------
    static const std::string        DefaultCompareFun;
    static const std::string        DefaultModifierFun;
    static const int                postMatchStepsZero = 0;

    // ------------------------------------
    // --- Contructors / Init Functions ---
    // ------------------------------------

    ScriptMiner(boost::shared_ptr<crawl::WebBrowserIF> pBrowser
                   , const::std::string& sBaseOutputName
                   , crawl::Url const& siteUrl
                   , const crawl::DataWriterIF::DataWriterVecT& dataWriters
                   , boost::shared_ptr<crawl::ScriptingClassIF> pScriptClass
                   , boost::shared_ptr<crawl::Configuration> pConfig
                   );
    ~ScriptMiner() override;
    void                assignWebBrowser    ( boost::shared_ptr<crawl::WebBrowserIF> pMozBrowser );
    void                init                ();
    void                clearForReloadScript() override;

    void                connectSignals      ();
    void                disconnectSignals   ();

    void                assignScriptingClass    ( boost::shared_ptr<crawl::ScriptingClassIF> pScriptClass );
    bool				scriptFunctionExists    ( const std::string&  sFunName ) const;

    // --- Assign commans/work to miner worker ---
    //     These functions will send a signal to the miner worker, so you don't
    //     have to worry about different threads when using these
    void                startUpPhpWorker();
    void                loadMinerScriptWorker(const QString& phpMinerScript, const QString& scriptAbsPath);
    void                runSetupFunctionsWorker();
    void                beginMiningWorker(bool restart);
    void                endMiningWorker();
    void                matchStepWorker();
    void                mineStepWorker();
    void                navigateStepWorker();
    void                doOnPageLoadedWorker();
    void                runPhpSnippetWorker(const QString& phpCode);

signals:
    void                startUpPhpSignal();
    void                loadMinerScriptSignal(const QString& phpMinerScript, const QString& scriptAbsPath);
    void                runSetupFunctionsSignal();
    void                beginMiningSignal(bool restart);
    void                endMiningSignal();
    void                matchStepSignal();
    void                mineStepSignal();
    void                navigateStepSignal();
    void                doOnPageLoadedSignal(); // When mining we want to do all 3 steps in one go from the script thread
    void                runPhpSnippetSignal(const QString& phpCode);

    void                crawlerCommandsExecutedSignal();
    void                pageLoadedSignal();

    void                emptyCrawlerCommandQueueSignal();

public slots:
    void                emptyCrawlerCommandQueueSlot();

private slots:
    void                workDoneSlot (crawl::MinerWorkerIF::TaskDone done);

private:
    // -------------------------------------
    // --- Start mining helper functions ---
    // -------------------------------------
    void                setUrlStartAndUrlSite       ();
    void				readConfig                  ();
    void                setOutputName           ();
    void				startMiningInitVars         ();
    void                outputBeginMiningRecord     ();
    void                resetVarsBeforeFirstPageLoad ();
    void                doDownloadSitemaps          ();
    void                downloadSitemapsWait        (int timeoutInMs = 10*60*1000);
    void                sitemapsDownloaded          (crawl::SiteMapGetter* smg);
    void                callSetupBeginMiningPhpFunctions();

public:
    // -----------------------------------------
    // --- Start/end mining helper functions ---
    // -----------------------------------------
    void                runSetupFunctions       ();
    void				startMining             (bool restart) override;
    void				endMining               (int iMiningDoneStatus) override;
    void 				signalMiningDone        () override;
    bool				onClose                 () override;

    std::string         creationHandlerContextName() const;
    // --------------------------------------
    // --- Program flow control functions ---
    // --------------------------------------
    void                match               ();
    void				mine                ();
    bool				navigate            ();
    bool				nextPage            () override;
    std::string         handlerContextName  () const override  { return m_sHandlerContextName; }

//	bool				miningDone	() const { return m_bMiningDone;	}

    // -------------------------------
    // --- Info/settings functions ---
    // -------------------------------
    std::string         minerName		() const;
    std::string         outputName		() const override;
    std::string			dataFileName	() const;

    const std::string&	currentLoadingUri() const {return m_sCurrentLoadingUrl; }

//    bool				keepActive          ();
//    void				checkLoadUriTimeout	();

    boost::shared_ptr<crawl::StateMachineMgr>
    stateMachineMgr()               {   return m_pStateMachineMgr;  }
    const boost::shared_ptr<crawl::StateMachineMgr>
    stateMachineMgr() const         {   return m_pStateMachineMgr;  }

    // ---------------------------------
    // --- PRIVATE: Helper functions ---
    // ---------------------------------
//private:
    void addScriptFunctions     ();
    void addFunction            ( std::string const& sFunctionName );

public:
    // ----------------------
    // --- Misc functions ---
    // ----------------------
    std::string     pageSource              () const override;
    std::string     currentMiner            () const override;
    std::string     currentDataFile         () const override;
    void            triggerPageLoaded       () override;
    void            triggerPageLoadedWait   (int timeoutInMs = timeoutInMsReload) override;
    void            waitSleep               (int timeInMs) override;
    bool            waitForDomReady         (int timeoutInMs = 120000) override;
    void            waitForFilesDownloaded  (int timeoutInMs = 10*60*1000) override;
    void            waitForJavascriptDone   () override;
    void            clearCookies            () override;
    int             networkActivityCounter  () const override;


    /*
    -------------------------
    --- Browser functions ---
    ------------------------- */
    void            browserScroll       ( int x, int y );
    int             browserScrollPosXGet() const;
    int             browserScrollPosYGet() const;
    void			browserHide			();
    void			browserShow			();
    void			browserSetSize		(int x, int y);
    int				browserGetSizeX		() const;
    int				browserGetSizeY		() const;
    bool			browserGoBack		();
    virtual void    browserKeyEvent     (int eventType, int key, int modifiers) override;
    virtual void    browserMouseEvent   (int eventType, float xpos, float ypos, int button, int buttons, int modifiers) override;
    virtual void    browserFocusActivate() override;
    virtual void    browserFocusDeactivate() override;

    /*------------------------------------------
    --- String operators/compare functions ---
    ------------------------------------------*/
    bool 			valuesCompare		( const std::string& sInput, const std::string& sTest, const std::string& sCompareFun );

    /*
    -------------------------
    --- Sitemap functions ---
    -------------------------*/
    std::vector<std::string>    siteMapUrls             () const override;
    void                        siteMapUrlsSet          (const std::vector<std::string>& siteMapUrls) override;
    void                        siteMapUrlAppend        (const std::string &siteMapUrl) override;
    std::vector<std::string>    siteMapLocationUrls     () const override;
    void                        siteMapLocationsInclude	(const std::string& urlPattern, const std::string& compareFun = DefaultCompareFun ) override;
    void                        siteMapLocationsExclude	(const std::string& urlPattern, const std::string& compareFun = DefaultCompareFun ) override;

    /*
    ----------------------------------
    --- Navigation (nav) functions ---
    ---------------------------------- */
    void        navActiveNavigatorSet   ( const std::string& sNavigatorName );
    std::string navActiveNavigatorGet   ();
    void        navJavascriptExecuteCreate ( const std::string& sNavActionName );
    void        navUrlLoadCreate        ( const std::string& sNavActionName, const std::string& sBaseUrl );
    void        navInputOptionsCreate   ( const std::string& sNavActionName );
    void        navDropDownSelectCreate ( const std::string& sNavActionName );
    void        navDomPosClickCreate    ( const std::string& sNavActionName, const std::string& sFindNextDomPosSequence );
    void        navDomClickNextCreate   ( const std::string& sNavActionName, const std::string& sFindNextDomPosSequence);
    void        navAutoInputCreate      ( const std::string& sNavActionName, const std::string& sCharsList, int iMinLength, int iMaxLength );

    void        navAttributeNamesCreate ( const std::string& sAttrNames, const std::string& sDelimiter = "," );

    // --- PUBLIC: Runtime settings functions ---
    void        navCurrentStateIndicesSet ( const std::string& sState );
    std::string navCurrentStateIndicesGet () const;
    void        navCurrentStateSet      ( const std::string& sState, const std::string& sDelimiter );
    void        navCurrentStateSet      ( const std::string& sState );
    void        navEndStateSet          ( const std::string& sState, const std::string& sDelimiter );
    void        navEndStateSet          ( const std::string& sState );

    // --- PUBLIC: Add Options functions ---
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

    // --- PUBLIC: Runtime functions ---
    std::string navDomTextValueGet      ( const std::string& sNavActionName ) const;
    std::string navDomValueGet          ( const std::string& sNavActionName ) const;
    std::string navValueGet             ( const std::string& sNavActionName ) ;
    std::string navSearchForGet         ( const std::string& sNavActionName ) ;
    int         navCountGet             ( const std::string& sNavActionName ) ;
    int         navOptionIndexGet       ( const std::string& sNavActionName ) ;
    int         navStateIndexGet        ();
    int         navNumStatesGet         () const;
    int         navLastStateIndexGet    () const;

    std::string navAttributeGet         ( const std::string& sNavActionName, const std::string& sAttrName ) ;
    std::string navAttributeGet         ( const std::string& sAttrName ) const;
    bool        navNextState            ();
    bool        navDoActionClickAll     ( const std::string& sNavActionName ) ;
    bool        navDoAction             ( const std::string& sNavActionName ) ;
    std::string navStateString          () const;
    void        navStart                ();
    void        navReset                ();
    bool        navNavigationDone       () const;
    void        navAutoInputIncreaseLength ( bool bDoIncreaseLength );

    /*
    ----------------------------------------------
    --- String modifier/manipulation functions ---
    ---------------------------------------------- */
    std::string		trimDefault_fn 		( const std::string& sInput 	) const;
    std::string		raw_fn				( const std::string& sInput		) const;
    std::string		toUpper_fn			( const std::string& sInput		) const;
    std::string		toLower_fn			( const std::string& sInput		) const;
    std::string		trimEnds_fn			( const std::string& sInput		) const;
    std::string		trimLeft_fn			( const std::string& sInput		) const;
    std::string		trimRight_fn		( const std::string& sInput		) const;
    std::string		trimYear_fn			( const std::string& sInput 	) const;

    std::string		trimInteger_fn		( const std::string& sInput		) const;
    std::string		trimNumber_fn		( const std::string& sInput		) const;


    std::string 	trimCharsEnds_fn	( const std::string& sInput, const std::string& sCharsToTrim ) const;
    std::string 	trimCharsLeft_fn	( const std::string& sInput, const std::string& sCharsToTrim ) const;
    std::string 	trimCharsRight_fn	( const std::string& sInput, const std::string& sCharsToTrim ) const;
    std::string 	trimRegex_fn		( const std::string& sInput, const std::string& sRegex ) const;
    std::string 	itrimRegex_fn		( const std::string& sInput, const std::string& sRegex ) const;
    std::string		append_fn			( const std::string& sInput, const std::string& sString	) const;
    std::string		prepend_fn			( const std::string& sInput, const std::string& sString	) const;
    std::string		eraseFirst_fn		( const std::string& sInput, const std::string& sSearchFor	) const;
    std::string		ieraseFirst_fn		( const std::string& sInput, const std::string& sSearchFor	) const;
    std::string		eraseLast_fn		( const std::string& sInput, const std::string& sSearchFor	) const;
    std::string		ieraseLast_fn		( const std::string& sInput, const std::string& sSearchFor	) const;
    std::string		eraseAll_fn			( const std::string& sInput, const std::string& sSearchFor	) const;
    std::string		ieraseAll_fn		( const std::string& sInput, const std::string& sSearchFor	) const;
    std::string		eraseRegex_fn		( const std::string& sInput, const std::string& sSearchFor	) const;
    std::string		eraseAllRegex_fn	( const std::string& sInput, const std::string& sSearchFor	) const;

    std::string 	trimBetween_fn      ( const std::string& sInput, const std::string& sBegin, 		const std::string& sEnd ) const;
    std::string     trimBetweenCount_fn (const std::string& sInput, const std::string& sBegin, const std::string& sEnd, const std::string& sCount ) const override;
    std::string     trimBetweenCount_fn (const std::string& sInput, const std::string& sBegin, const std::string& sEnd, int iCount ) const override;
    std::string 	trimIntegerCustom_fn( const std::string& sInput, const std::string& iBase, 			const std::string& sThousandsSep) const;
    std::string 	trimNumberCustom_fn	( const std::string& sInput, const std::string& sDecimalPoint, 	const std::string& sThousandsSep) const;
    std::string		replaceFirst_fn		( const std::string& sInput, const std::string& sSearchFor,		const std::string& sReplaceWith	) const;
    std::string		ireplaceFirst_fn	( const std::string& sInput, const std::string& sSearchFor,		const std::string& sReplaceWith	) const;
    std::string		replaceLast_fn		( const std::string& sInput, const std::string& sSearchFor,		const std::string& sReplaceWith	) const;
    std::string		ireplaceLast_fn		( const std::string& sInput, const std::string& sSearchFor,		const std::string& sReplaceWith	) const;
    std::string		replaceAll_fn		( const std::string& sInput, const std::string& sSearchFor,		const std::string& sReplaceWith	) const;
    std::string		ireplaceAll_fn		( const std::string& sInput, const std::string& sSearchFor,		const std::string& sReplaceWith	) const;
    std::string		replaceRegex_fn		( const std::string& sInput, const std::string& sSearchFor,		const std::string& sReplaceWith	) const;
    std::string		replaceAllRegex_fn	( const std::string& sInput, const std::string& sSearchFor,		const std::string& sReplaceWith	) const;

    std::string		eraseNth_fn			( const std::string& sInput, const std::string& sSearchFor,	int iNth 	) const;
    std::string		ieraseNth_fn		( const std::string& sInput, const std::string& sSearchFor,	int iNth 	) const;

    std::string		replaceNth_fn		( const std::string& sInput, const std::string& sSearchFor,	const std::string& sReplaceWith, int iNth	) const;
    std::string		ireplaceNth_fn		( const std::string& sInput, const std::string& sSearchFor,	const std::string& sReplaceWith, int iNth	) const;

    std::string		eraseNth_fn         ( const std::string& sInput, const std::string& sSearchFor,     const std::string& sNth 	) const;
    std::string		ieraseNth_fn        ( const std::string& sInput, const std::string& sSearchFor,     const std::string& sNth 	) const;
    std::string		replaceNth_fn       ( const std::string& sInput, const std::string& sSearchFor,	const std::string& sReplaceWith ,const std::string& sNth	) const;
    std::string		ireplaceNth_fn      ( const std::string& sInput, const std::string& sSearchFor,	const std::string& sReplaceWith, const std::string& sNth	) const;


    /*
    ---------------------
    --- URL functions ---
    --------------------- */
    std::string		urlSite();
    std::string		urlCurrent();
    bool			urlLoad		( const std::string sUrl	);
    bool			urlLoadWait	( const std::string sUrl, int timeoutInMs = 30000);

    /*
    ---------------------
    --- DOM functions ---
    --------------------- */
    void        domRebuildWait          ( int timeoutInMs = 30000 ) override;
    void		domNewSearch			();
    std::vector<int> domFindAll         (   const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps );
    std::vector<int> domFindAll         (   const std::string& sSequence, int iPostMatchSteps );
    std::vector<int> domFindAll         (   const std::string& sSequence );
    int			domFindParentPos		( 	int iLevelsUp = 1 );
    int			domFindParent			( 	int iLevelsUp = 1 );

    int         domFindCallPhpFunHelper	(const std::string& sSequence , std::string& sPhpFunRetValOut);
    int			domSeqFindNextParams	( 	int iCount, const crawl::DomSeq& seq, const std::string& sArgs, int iNodeTypes );

    int			domFindNextImpl			(int iCount, std::string& sPhpFunRetVal, const std::string& sSequence,
                                            const std::string& sArgs, const std::string& sCompareFun,
                                            int iPostMatchSteps, int iNodeTypes);
    int			domFindNext				(   int iCount, const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps, int iNodeTypes );
    int			domFindNext				(   int iCount, const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps );
    int			domFindNext				( 	int iCount, const std::string& sSequence, const std::string& sCompareFun );
    int			domFindNext				( 	int iCount, const std::string& sSequence, int iPostMatchSteps );
    int			domFindNext				( 	int iCount, const std::string& sSequence );
    int			domFindNext				(   const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps, int iNodeTypes );
    int			domFindNext				(   const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps );
    int			domFindNext				( 	const std::string& sSequence, const std::string& sCompareFun );
    int			domFindNext				( 	const std::string& sSequence, int iPostMatchSteps );
    int			domFindNext				( 	const std::string& sSequence );
    int			domFindPrev				( 	const std::string& sSequence, const std::string& sCompareFun );
    int			domSeqFindNextParams       ( 	int iCount, const std::string& sSequence, const std::string& sArgs );


    int			domFind					( 	int iCount, const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps, int iNodeTypes );
    int			domFind					( 	int iCount, const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps );
    int			domFind					( 	int iCount, const std::string& sSequence, const std::string& sCompareFun );
    int			domFind					( 	int iCount, const std::string& sSequence, int iPostMatchSteps );
    int			domFind					( 	int iCount, const std::string& sSequence );
    int			domFind					(   const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps, int iNodeTypes );
    int			domFind					(   const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps );
    int			domFind					( 	const std::string& sSequence, const std::string& sCompareFun );
    int			domFind					( 	const std::string& sSequence, int iPostMatchSteps );
    int			domFind					( 	const std::string& sSequence );

    int			domFindPos              ( 	int iCount, const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps, int iNodeTypes );
    int			domFindPos              ( 	int iCount, const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps );
    int			domFindPos              ( 	int iCount, const std::string& sSequence, const std::string& sCompareFun );
    int			domFindPos              ( 	int iCount, const std::string& sSequence, int iPostMatchSteps );
    int			domFindPos              ( 	int iCount, const std::string& sSequence );
    int			domFindPos              (   const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps, int iNodeTypes );
    int			domFindPos              (   const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps );
    int			domFindPos              ( 	const std::string& sSequence, const std::string& sCompareFun );
    int			domFindPos              ( 	const std::string& sSequence, int iPostMatchSteps );
    int			domFindPos              ( 	const std::string& sSequence );


    int			domFindNextPos			( 	int iCount, const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps, int iNodeTypes );
    int			domFindNextPos			( 	int iCount, const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps );
    int			domFindNextPos			( 	int iCount, const std::string& sSequence, const std::string& sCompareFun );
    int			domFindNextPos			( 	int iCount, const std::string& sSequence, int iPostMatchSteps );
    int			domFindNextPos			( 	int iCount, const std::string& sSequence );
    int			domFindNextPos			(   const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps, int iNodeTypes );
    int			domFindNextPos			(   const std::string& sSequence, const std::string& sCompareFun, int iPostMatchSteps );
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
    int			domStep					(  	int iCount, int iNodeTypes = crawl::DomNodeTypes::ALL_NODE_TYPES )																					;
    bool		domAtEnd				()																																	;
    void		domRangePushElement		( int iElementPos ) override;
    void		domRangePush			( int iStartPos, int iStopPos ) override;
    void		domRangePop             () override;
    void		domPointerPush			()																																	;
    int			domPointerPop			()																																	;
    int 		domSize					() 																																	;
    int 		domEndPos				() 																																	;
    int 		domPos                  () 																																	;
    int			domPosSet				( int iNewPos )																														;
    int			domStartPosSet			( int iStartPos )																													;
    int			domStartPos             ()																														;
    void		domStartPosClear		()																																	;
    int			domStopPosSet			( int iStopPos )																													;
    int			domStopPos              ()																														;
    void		domStopPosClear			()																																	;
    void		domSetAtEnd             ()																																	;
    int			domContinuePos          () override;
    int			domThisElementPos       () override;
    int			domThisElementPos       ( int pos ) override;
    int			domOwnerPos             ( int iLevelsUp = 1 ) override;
    int			domPosToOwner			( int iLevelsUp = 1 ) override;
    int			domParentPos            ( int iLevelsUp = 1 ) override;
    int			domPosToParent			( int iLevelsUp = 1 ) override;

    /*
    -------------------------------------
    --- DOM Sequence create functions ---
    ------------------------------------- */
    void		domSeqCreate			( 	int iCount, const std::string& sName, const std::string& sSequence,
                                            const std::string& sCompareFun, int iPostMatchSteps, int iNodeTypes, const std::string& sCommaChar ) override;
    void		domSeqCreate			( 	int iCount, const std::string& sName, const std::string& sSequence, const std::string& sCompareFun,
                                            int iPostMatchSteps, int iNodeTypes ) override;
    void		domSeqCreate			( 	int iCount, const std::string& sName, const std::string& sSequence, const std::string& sCompareFun,
                                            int iPostMatchSteps  ) override;
    void		domSeqCreate			( 	int iCount, const std::string& sName, const std::string& sSequence, const std::string& sCompareFun ) override;
    void		domSeqCreate			( 	int iCount, const std::string& sName, const std::string& sSequence, int iPostMatchSteps ) override;
    void		domSeqCreate			( 	int iCount, const std::string& sName, const std::string& sSequence ) override;

    void		domSeqCreate			( 	const std::string& sName, const std::string& sSequence, const std::string& sCompareFun,
                                            int iPostMatchSteps, int iNodeTypes, const std::string& sCommaChar ) override;
    void		domSeqCreate			( 	const std::string& sName, const std::string& sSequence, const std::string& sCompareFun,
                                            int iPostMatchSteps, int iNodeTypes  ) override;
    void		domSeqCreate			( 	const std::string& sName, const std::string& sSequence, const std::string& sCompareFun,
                                            int iPostMatchSteps  ) override;
    void		domSeqCreate			( 	const std::string& sName, const std::string& sSequence, const std::string& sCompareFun ) override;
    void		domSeqCreate			( 	const std::string& sName, const std::string& sSequence, int iPostMatchSteps ) override;
    void		domSeqCreate			( 	const std::string& sName, const std::string& sSequence ) override;

    bool		domSeqExists			( 	const std::string& sName ) const override;

    /*
    -----------------------------------
    --- LookForWord (lfw) functions ---
    ----------------------------------- */
    void		lfwMatchWholeWordsOnlySet(bool matchWholeWordsOnly) override;
    void        lfwClear                () override;
    void        lfwClear                (const std::string& contextName) override;
    void        lfwClear                (const std::string& contextName, const std::string& referenceName) override;
    void        lfwAddWord              (const std::string& contextName, const std::string& referenceName,
                                         const std::string& word, const std::string& compareFun, int nodeTypes) override;
    void		lfwRemoveWord           (const std::string& contextName, const std::string& referenceName,
                                         const std::string& word) override;
    void        lfwGetDataFunctionSet   (const std::string& contextName, const std::string& getDataFunction) override;
    void		lfwGetDataFallbackFunctionSet (const std::string& contextName, const std::string& getDataFallbackFunction) override;
    int         lfwDomFindNext          (const std::string& referenceName) override;
    std::string lfwOutputValueFindNext  (const std::string& referenceName) override;
    std::string lfwPreSequence          (const std::string& contextName) override;
    void        lfwPreSequenceSet       (const std::string& contextName, const std::string& lfwPreSequence) override;
    std::string lfwPostSequence         (const std::string& contextName) override;
    void        lfwPostSequenceSet      (const std::string& contextName, const std::string& lfwPostSequence) override;

    std::string lfwStartPosDomSeq       (const std::string& contextName) const override;
    void        lfwStartPosDomSeqSet    (const std::string& contextName, const std::string& lfwStartPosDomSeq) override;
    std::string lfwStopPosDomSeq        (const std::string& contextName) const override;
    void        lfwStopPosDomSeqSet     (const std::string& contextName, const std::string& lfwStopPosDomSeq) override;

    /*
    ----------------------------------
    --- Element children functions ---
    ---------------------------------  */
    std::vector<int> nodeChildren       ( int iSearchDir = crawl::NEAREST_AUTO ) override;
    std::vector<int> nodeChildren       ( const std::string& tagName, int iSearchDir = crawl::NEAREST_AUTO ) override;
    std::vector<int> nodeChildrenRecur  ( const std::string& tagName, int iSearchDir = crawl::NEAREST_AUTO ) override;
    int              nodeEndElementPos  ( int iSearchDir = crawl::NEAREST_AUTO )override;

    std::vector<int> posChildren        ( int iDomPos) override;
    std::vector<int> posChildren        ( const std::string& tagName, int iDomPos) override;
    std::vector<int> posChildrenRecur   ( const std::string& tagName, int iDomPos) override;
    int              posEndElementPos   ( int iDomPos ) override;

    /*
    ------------------------------------
    --- Current (dom) node functions ---
    ------------------------------------ */
//    boost::shared_ptr<crawl::DomNodeIF> helperGetNearestElement     ( int iSearchDir, std::string sElemType = "" );
    crawl::LinearDomIF::const_iterator  helperGetNearestLinearIter  ( int iSearchDir, std::string sElemType = "" );

    int			nodeType				();
    //bool		nodeClick				( bool bLoadHref, int iSearchDir );
    //bool		nodeClick				( int iSearchDir );
    //bool		nodeClick				();
    bool		nodeClickLoadHref		( int iSearchDir = crawl::NEAREST_AUTO );
    bool		nodeClick				( int iSearchDir = crawl::NEAREST_AUTO );
    bool		userClick				( int iSearchDir = crawl::NEAREST_AUTO );
    bool        userMouseEvent          ( int eventType, int button, int buttons, int modifiers, int iSearchDir = crawl::NEAREST_AUTO );
    bool		nodeClickWait			( int timeoutInMs = 30000, int iSearchDir = crawl::NEAREST_AUTO )																			;
    bool		nodeMouseEvent			( const std::string& sEvent )																		;
    bool		nodeMouseEvent			( const std::string& sEvent, int iSearchDir  )																		;
    bool		nodeMouseEvent			( const std::string& sEvent, int iButton, int iSearchDir  )																		;
    bool		nodeJavaScriptEvaluate	( const std::string& sJavaScript, int iSearchDir = crawl::NEAREST_AUTO );
    bool 		inputSet 				( const std::string& sValue, int iSearchDir = crawl::NEAREST_AUTO )																		;
    bool 		inputSet 				( int 				 iValue, int iSearchDir = crawl::NEAREST_AUTO )																		;
    std::string innerHtml              ( int iSearchDir = crawl::NEAREST_AUTO );
    bool 		innerHtmlSet 			( const std::string& sValue, int iSearchDir = crawl::NEAREST_AUTO );
    std::string innerText              ( int iSearchDir = crawl::NEAREST_AUTO);
    bool 		innerTextSet 			( const std::string& sValue, int iSearchDir = crawl::NEAREST_AUTO );
    bool		formSubmit				( int iSearchDir = crawl::NEAREST_AUTO )																									;
    bool		formReset				( int iSearchDir = crawl::NEAREST_AUTO )																									;
    int			selectLength			( int iSearchDir = crawl::NEAREST_AUTO )																									;
    int			selectSelectedIndex		( int iSearchDir = crawl::NEAREST_AUTO )																									;
    std::string	selectSelectedText		( int iSearchDir = crawl::NEAREST_AUTO );
    std::string	selectSelectedValue		( int iSearchDir = crawl::NEAREST_AUTO );
    int 		selectSelectedDomPos 	( int iSearchDir = crawl::NEAREST_AUTO )																									;
    bool		selectSelect			( int iIndex, int iSearchDir = crawl::NEAREST_AUTO )																						;
    bool		selectIndex             ( int iIndex, int iSearchDir = crawl::NEAREST_AUTO )																						;
    bool		selectIndexWait         ( int iIndex, int timeoutInMs = 30000, int iSearchDir = crawl::NEAREST_AUTO ) override;
    bool		selectOption			( int iSearchDir = crawl::NEAREST_AUTO ) override;
    bool		selectOptionWait		( int timeoutInMs = 30000, int iSearchDir = crawl::NEAREST_AUTO ) override;
    int         selectIndexOfOption		( int iSearchDir = crawl::NEAREST_AUTO );
    bool		doActionSimple			( const std::string& sAction, const std::string& sParam1, const std::string& sParam2, int iSearchDir );
    bool		doAction				( const std::string& sAction, const std::string& sParam1, const std::string& sParam2, int iSearchDir );
    bool		doAction				( const std::string& sAction, const std::string& sParam1, const std::string& sParam2 );
    bool		doAction				( const std::string& sAction, const std::string& sParam1, int iSearchDir = crawl::NEAREST_AUTO );
    bool		doAction				( const std::string& sAction, int iSearchDir = crawl::NEAREST_AUTO );
    float		nodeGeomPosX			( int iSearchDir = crawl::NEAREST_AUTO );
    float		nodeGeomPosY			( int iSearchDir = crawl::NEAREST_AUTO );
    float		nodeGeomWidth			( int iSearchDir = crawl::NEAREST_AUTO );
    float		nodeGeomHeight			( int iSearchDir = crawl::NEAREST_AUTO );

    /*
    --------------------------------------
    --- DOM doActionFindNext functions ---
    -------------------------------------- */
    int     doActionFindNextImpl        (   int iCount, const std::string& sSequence, const std::string& sAction,
                                            const std::string& sParam1, const std::string& sParam2, int iSearchDir, bool bUpdateDomPos );
    int		doActionFindNext			(	int iCount, const std::string& sSequence, const std::string& sAction, const std::string& sParam1,
                                            const std::string& sParam2, int iSearchDir );
    int		doActionFindNext			(	int iCount, const std::string& sSequence, const std::string& sAction, const std::string& sParam1,
                                            const std::string& sParam2 );
    int		doActionFindNext			(	int iCount, const std::string& sSequence, const std::string& sAction, const std::string& sParam1,
                                            int iSearchDir = crawl::NEAREST_AUTO );
    int		doActionFindNext			(	int iCount, const std::string& sSequence, const std::string& sAction, int iSearchDir = crawl::NEAREST_AUTO );


    int		doActionFindNext			(	const std::string& sSequence, const std::string& sAction, const std::string& sParam1,
                                            const std::string& sParam2, int iSearchDir );
    int		doActionFindNext			(	const std::string& sSequence, const std::string& sAction, const std::string& sParam1,
                                            const std::string& sParam2 );
    int		doActionFindNext			(	const std::string& sSequence, const std::string& sAction, const std::string& sParam1,
                                            int iSearchDir = crawl::NEAREST_AUTO );
    int		doActionFindNext			(	const std::string& sSequence, const std::string& sAction, int iSearchDir = crawl::NEAREST_AUTO );

    //int		doActionFindNextParams			(	int iCount, const std::string& sSequence, const std::string& sArgs, const std::string& sAction, const std::string& sParam1,
    //										const std::string& sParam2, int iSearchDir );
    //int		doActionFindNextParams			(	int iCount, const std::string& sSequence, const std::string& sArgs, const std::string& sAction, const std::string& sParam1,
    //										const std::string& sParam2 );
    //int		doActionFindNextParams			(	int iCount, const std::string& sSequence, const std::string& sArgs, const std::string& sAction, const std::string& sParam1,
    //										int iSearchDir = crawl::NEAREST_AUTO );
    //int		doActionFindNextParams			(	int iCount, const std::string& sSequence, const std::string& sArgs, const std::string& sAction, int iSearchDir = crawl::NEAREST_AUTO );

    /*
    ----------------------------------
    --- DOM doActionFind functions ---
    ---------------------------------- */
    int		doActionFind				(	int iCount, const std::string& sSequence, const std::string& sAction, const std::string& sParam1,
                                            const std::string& sParam2, int iSearchDir );
    int		doActionFind				(	int iCount, const std::string& sSequence, const std::string& sAction, const std::string& sParam1,
                                            const std::string& sParam2 );
    int		doActionFind				(	int iCount, const std::string& sSequence, const std::string& sAction, const std::string& sParam1,
                                            int iSearchDir = crawl::NEAREST_AUTO );
    int		doActionFind				(	int iCount, const std::string& sSequence, const std::string& sAction, int iSearchDir = crawl::NEAREST_AUTO );


    int		doActionFind				(	const std::string& sSequence, const std::string& sAction, const std::string& sParam1,
                                            const std::string& sParam2, int iSearchDir );
    int		doActionFind				(	const std::string& sSequence, const std::string& sAction, const std::string& sParam1,
                                            const std::string& sParam2 );
    int		doActionFind				(	const std::string& sSequence, const std::string& sAction, const std::string& sParam1,
                                            int iSearchDir = crawl::NEAREST_AUTO );
    int		doActionFind				(	const std::string& sSequence, const std::string& sAction, int iSearchDir = crawl::NEAREST_AUTO );


    //int		doActionFindParams			(	int iCount, const std::string& sSequence, const std::string& sArgs, const std::string& sAction, const std::string& sParam1,
    //										const std::string& sParam2, int iSearchDir );
    //int		doActionFindParams			(	int iCount, const std::string& sSequence, const std::string& sArgs, const std::string& sAction, const std::string& sParam1,
    //										const std::string& sParam2 );
    //int		doActionFindParams			(	int iCount, const std::string& sSequence, const std::string& sArgs, const std::string& sAction, const std::string& sParam1,
    //										int iSearchDir = crawl::NEAREST_AUTO );
    //int		doActionFindParams			(	int iCount, const std::string& sSequence, const std::string& sArgs, const std::string& sAction, int iSearchDir = crawl::NEAREST_AUTO );

    /*
    -----------------------------------
    --- DOM Action create functions ---
    ----------------------------------- */
    void		domActionCreate			( 	const std::string& sName, const std::string& sAction, const std::string& sParam1,
                                            const std::string& sParam2, int iSearchDir );
    void		domActionCreate			( 	const std::string& sName, const std::string& sAction, const std::string& sParam1,
                                            const std::string& sParam2 );
    void		domActionCreate			( 	const std::string& sName, const std::string& sAction, const std::string& sParam1,
                                            int iSearchDir = crawl::NEAREST_AUTO );
    void		domActionCreate			( 	const std::string& sName, const std::string& sAction, int iSearchDir = crawl::NEAREST_AUTO );

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
    int         nodeLevel               () override;
    std::string	nodeXPath               () override;

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


    std::string	posValue			( int iDomPos, const std::string& sModifierID, const std::string& sManipParam1,
                                      const std::string& sManipParam2, const std::string& sManipParam3,
                                      const std::string& sManipParam4 ) override;
    std::string	posValue			( int iDomPos, const std::string& sModifierID, const std::string& sManipParam1,
                                      const std::string& sManipParam2, const std::string& sManipParam3 ) override;
    std::string	posValue			( int iDomPos, const std::string& sModifierID, const std::string& sManipParam1,
                                      const std::string& sManipParam2 ) override;
    std::string	posValue			( int iDomPos, const std::string& sModifierID, const std::string& sManipParam1 ) override;
    std::string	posValue			( int iDomPos, const std::string& sModifierID ) override;
    std::string	posValue			( int iDomPos ) override;

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
                                          const std::string& sManipParam3, const std::string& sManipParam4 ) override;
    std::string	posAttribute			( int iDomPos, const std::string& sAttribute, const std::string& sModifierID,
                                          const std::string& sManipParam1, const std::string& sManipParam2,
                                          const std::string& sManipParam3 ) override;
    std::string	posAttribute			( int iDomPos, const std::string& sAttribute, const std::string& sModifierID,
                                          const std::string& sManipParam1, const std::string& sManipParam2 ) override;
    std::string	posAttribute			( int iDomPos, const std::string& sAttribute, const std::string& sModifierID,
                                          const std::string& sManipParam1 ) override;
    std::string	posAttribute			( int iDomPos, const std::string& sAttribute, const std::string& sModifierID ) override;
    std::string	posAttribute			( int iDomPos, const std::string& sAttribute ) override;

    /*
    ---------------------------------
    --- nodeText functions ---
    --------------------------------- */
    std::string	nodeText			( const std::string& sModifierID, const std::string& sManipParam1,
                                      const std::string& sManipParam2, const std::string& sManipParam3,
                                      const std::string& sManipParam4 );
    std::string	nodeText			( const std::string& sModifierID, const std::string& sManipParam1,
                                      const std::string& sManipParam2, const std::string& sManipParam3 );
    std::string	nodeText			( const std::string& sModifierID, const std::string& sManipParam1,
                                      const std::string& sManipParam2 );
    std::string	nodeText			( const std::string& sModifierID, const std::string& sManipParam1 );
    std::string	nodeText			( const std::string& sModifierID );
    std::string	nodeText			();

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
    bool		parseRegex			(	int iCount, const std::string& sRegex,		int postMarkerPos = crawl::StringSearch::MATCH_FIRST		)												;
    bool		iparseRegex			(	int iCount, const std::string& sRegex,		int postMarkerPos = crawl::StringSearch::MATCH_FIRST		)												;
    bool		parseToRegex		(	int iCount, const std::string& sRegex,		int postMarkerPos = crawl::StringSearch::MATCH_FIRST		)												;
    bool		iparseToRegex		(	int iCount, const std::string& sRegex,		int postMarkerPos = crawl::StringSearch::MATCH_FIRST		)												;
    bool		parseToString		(	int iCount, const std::string& sSubstring,	int postMarkerPos = crawl::StringSearch::MATCH_FIRST		)												;
    bool		iparseToString		(	int iCount, const std::string& sSubstring,	int postMarkerPos = crawl::StringSearch::MATCH_FIRST		)												;
    bool		parseToEnd			()																																	;
    std::string	getParseMatch		( int iMatchNumber )																												;
    std::string	getParseRest		()																																	;
    int			getParseMatchCount	()																																	;

    /*
    ----------------------
    --- Text functions ---
    ---------------------- */
    void		textNewSearch		()																																	;
    bool		findBegin			(	int iCount, const std::string& sSearchFor, 	int setBeginToPos = crawl::StringSearch::MATCH_LAST		)												;
    bool		findEnd				(	int iCount, const std::string& sSearchFor, 	int setBeginToPos = crawl::StringSearch::MATCH_FIRST	)												;
    bool		findBeginNext		(	int iCount, const std::string& sSearchFor, 	int setBeginToPos = crawl::StringSearch::MATCH_LAST 	)												;
    bool		findEndNext			(	int iCount, const std::string& sSearchFor, 	int setBeginToPos = crawl::StringSearch::MATCH_FIRST	)												;
    bool		ifindBegin			(	int iCount, const std::string& sSearchFor, 	int setBeginToPos = crawl::StringSearch::MATCH_LAST		)												;
    bool		ifindEnd			(	int iCount, const std::string& sSearchFor, 	int setBeginToPos = crawl::StringSearch::MATCH_FIRST	)												;
    bool		ifindBeginNext		(	int iCount, const std::string& sSearchFor, 	int setBeginToPos = crawl::StringSearch::MATCH_LAST 	)												;
    bool		ifindEndNext		(	int iCount, const std::string& sSearchFor, 	int setBeginToPos = crawl::StringSearch::MATCH_FIRST	)												;
    bool		findRegexBegin		(	int iCount, const std::string& sRegex,		int setBeginToPos = crawl::StringSearch::MATCH_LAST		)												;
    bool		findRegexEnd		(	int iCount, const std::string& sRegex, 		int setBeginToPos = crawl::StringSearch::MATCH_FIRST	)												;
    bool		findRegexBeginNext	(	int iCount, const std::string& sRegex,		int setBeginToPos = crawl::StringSearch::MATCH_LAST		)												;
    bool		findRegexEndNext	(	int iCount, const std::string& sRegex, 		int setBeginToPos = crawl::StringSearch::MATCH_FIRST	)												;
    bool		stepBegin			(	int iCount	)																													;
    bool		stepEnd				(	int iCount	)																													;

    /*
    -----------------------------
    --- (URL) queue functions ---
    ----------------------------- */
    enum {
          LINK_TYPE_LOCAL       = 1 << 0
        , LINK_TYPE_EXTERNAL    = 1 << 1
        , LINK_TYPE_ALL         = 3
        };

    int			urlQueueSize			()	const;
    int			urlQueueSizeProcessed	()	const;
    bool        urlQueueAlreadyProcessed( const std::string& sUrl ) const;
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
    std::string	outputValueContextGet	( const std::string& sFieldName, const std::string& sContextName ) override;
    std::string	outputValueGet  		( const std::string& sFieldName, const std::string& sModifierID, const std::string& sManipParam1,
                                          const std::string& sManipParam2, const std::string& sManipParam3, const std::string& sManipParam4 ) override;
    std::string	outputValueGet			( const std::string& sFieldName, const std::string& sModifierID, const std::string& sManipParam1,
                                          const std::string& sManipParam2, const std::string& sManipParam3 ) override;
    std::string	outputValueGet			( const std::string& sFieldName, const std::string& sModifierID, const std::string& sManipParam1,
                                          const std::string& sManipParam2 ) override;
    std::string	outputValueGet			( const std::string& sFieldName, const std::string& sModifierID, const std::string& sManipParam1 ) override;
    std::string	outputValueGet			( const std::string& sFieldName, const std::string& sModifierID ) override;
    std::string	outputValueGet			( const std::string& sFieldName) override;

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
    -------------------------
    --- Context functions ---
    ------------------------- */
    void		dataPushContext			(	std::string sContext, std::string const& sUnit = "" );
    void		dataPushContextAlias	(	const std::string& sContext, const std::string& sContextAlias, const std::string& sUnit = "" );
    void		dataPopContext			();

    void		contextBegin                (	std::string sContextName );
    void		contextEnd                  ();

    void        contextOutputSaveAs         ( const std::string& sContextName );
    void        contextFallbackOutputLoad   ( const std::string& sContextName );
    void        contextFallbackOutputClear  ();
    std::string contextFallbackValueGet     ( const std::string& sFieldName ) const;
    void        contextFallbackValueSet     ( const std::string& sFieldName, const std::string& sValue ) ;

    bool        contextFallbackValueExists  ( const std::string& sFieldName ) const;
    void        contextFallbackValueDelete  ( const std::string& sFieldName );
    bool        contextSavedOutputExists    ( const std::string& sContextName ) const;

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

    int         outputValueFindNextImpl (  int iCount, const std::string& sSequence, const std::string& sFieldName
                                           , const std::string& sModifierID, const std::string& sManipParam1
                                           , const std::string& sManipParam2, const std::string& sManipParam3
                                           , const std::string& sManipParam4, bool bUpdateDomPos );
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




    /*
    ----------------------------
    --- Javascript functions ---
    ---------------------------- */
    bool 		javaScriptExecuteRetVal	( const std::string& sScript, std::string& sScriptReturnValue 	);
    bool 		javaScriptExecute		( const std::string& sScript									);
    bool 		javaScriptExecuteWait	( const std::string& sScript, int timeoutInMs = ScriptMinerIF::timeoutInMsDefault) override;

    /*
    -------------------------
    --- Utility functions ---
    ------------------------- */
    int 		curlPostUploadFileSimple( const std::string& sURL, const std::string& sFieldName, const std::string& sFilePath 	) 	;
    bool 		gzCompressFile			( const std::string& sSrcFilePath, const std::string& sDstFilePath ) 						;
    bool 		gzUnCompressFile		( const std::string& sSrcFilePath, const std::string& sDstFilePath )						;


    /*
    --------------------------
    --- Settings functions ---       -------------------------- */
    void		settingDelete           (	const std::string& sName );
    void		settingSet              (	const std::string& sName, const std::string& sValue );
    std::string settingGet              (	const std::string& sName, const std::string& defaultValue = "" ) const override;
    bool        settingExists           (	const std::string& sName ) const;
    bool        hasSetting              (	const std::string& sName ) const;
    bool        settingBoolGet          (   const std::string& sName ) const override;

    /*
    ------------------------
    --- Config functions ---
    ------------------------ */
    void            runModeSet              ( crawl::RunModeE eRunMode );
    crawl::RunModeE	runMode                 () const;
    std::string configValueGet              ( const std::string& sName );
    void		configValueSet              ( const std::string& sName, const std::string& sValue );
    bool        configValueBoolGet          ( const std::string& sName ) const override;
    void		configUrlStartSet           ( crawl::Url const& startingUrl );
    void        configUrlStartSet           ( const std::string& sUrl	);
    void		configUrlUploadDataSet      ( const std::string sUrl 	);
    std::string	configUrlUploadDataGet      () const;

    void		configDisableLoadImages     ();
    void		configForceLoadImages       ();

    void 		configAddIncludeUrl         ( const std::string& sPattern, const std::string& sCompareFun )	;
    void 		configAddExcludeUrl         ( const std::string& sPattern, const std::string& sCompareFun )	;

    void        configUploadData            ( bool bUploadData );
    void		configForceSendXmlData      ();
    void        configAjaxPageLoadDeltaTime (int iMilliSeconds );
    void		configReloadTimeOut         ( int /*iMinutes*/, int /*iSecs */)			{ /*m_iReloadTimeOutMins = iMinutes; m_iReloadTimeOutSecs = iSecs; */}
    void		configKeepActiveInterval    ( int /*iSecs */)						{ /*m_iKeepActiveIntervalSecs = iSecs;*/ }

    void		configProgressOutputSet     ( bool bEnable )																			;
    void		configDebugOutputSet        ( bool bEnable )																			;
    bool		configDebugOutputGet        ()																							;

    void 		configParseDecimalPointSet  ( const std::string& sDecimalPoint );
    void 		configParseThousandsSepSet  ( const std::string& sThousandsSep );
    std::string	configParseDecimalPointGet  () const;
    std::string	configParseThousandsSepGet  () const;
    std::string configGetRunMode            () const;
    void		configOutputEncloseCDATA    ( bool bDoEncloseInCDATA )																	;
    void		configOutputWriteToFile     ( bool bDoWriteOutputToFile )																	;
    void		configLocaleSettingsSet     (const std::string& country_or_currency_code ) override;

    /*
    -----------------------
    --- Debug functions ---
    ----------------------- */
    void        locatedPositionsClear   ()                                                                  override;
    void		domDebugPrint			( const std::string& sFileName="" 								)	override;
    void		nodeDebugPrint			( int iNodesBefore, int iNodesAfter, bool bPrintNodeTypes = false ) override;
    void		nodeDebugPrint			( int iNodesAround=10, bool bPrintNodeTypes = false )               override;
    std::string	nodeValueDebug			( int iNodesBefore, int iNodesAfter, bool bPrintNodeTypes = false ) override;
    std::string	nodeValueDebug			( int iNodesAround=10, bool bPrintNodeTypes = false )               override;


    // --------------------------------------
    // --- PUBLIC: General info functions ---
    // ---------------------------------------
    int                                 infoMiningDoneStatus            () const { return m_iMiningDoneStatus;          }
    const boost::posix_time::ptime& 	infoTimeMiningStarted           () const { return m_tStartUTC;                  }
    const boost::posix_time::ptime&     infoTimeLastPageLoadStarted     () const { return m_timeLastPageLoadStarted;    }
    const boost::posix_time::ptime&     infoTimeLastPageLoadFinished    () const { return m_timeLastPageLoadFinished;   }
    const std::string&					infoCurrentLoadingUrl           () const { return m_sCurrentLoadingUrl;         }
    const std::string&                  infoLatestFullyLoadedUrl        () const { return m_sLatestFullyLoadedUrl;      }
    boost::uint64_t                     infoPageLoadsTotal              () const { return m_iPageLoadsTotal;            }
    int                                 infoLastNetworkError            () const;

    // ----------------------------------
    // --- Non virtual info functions ---
    // ----------------------------------
    crawl::MiningStepE nextMiningStep   () const { return m_nextMiningStepE; }


    void doOnAjaxCompleted();

    void doOnPageLoadedMainThread();

    crawl::MinerWorker* minerWorker() const;
    void minerWorkerSet(crawl::MinerWorker* minerWorker);



    bool getWaitingForDomReady() const;

    bool workerIsExecutingPhp() const;


    boost::uint32_t itemsWritten() const;

private:
    // --------------------------
    // --- PRIVATE: Functions ---
    // --------------------------
    void                updateScriptStatusString();
    void                writeMiningStatusFile   ();
    bool				slotLoadUri				( crawl::WebBrowserIF& webBrowser, const std::string& sUri);
    void				slotPageLoaded			( crawl::WebBrowserIF& webBrowser );
    void				slotContinuousTimer		( );
    void				slotContinuousTimer2	( );
    std::string         manipulateValueHelper   ( const std::string& sValue, bool  bAllowDefaultTrimming
                                                 , const std::string& sModifierID, const std::string& sManipParam1
                                                 , const std::string& sManipParam2, const std::string& sManipParam3
                                                 , const std::string& /* sManipParam4 reserved */);

    crawl::LookForWordMgr* lookForWordMgr(const std::string& contextName) const;
    crawl::LookForWordMgr* currentLookForWordMgr() const;

    std::string scriptStatus() const;
    void scriptStatusSet(const std::string& scriptStatus);
    void waitingForDomReadySet(bool ready);
    boost::filesystem::path     dumpDirGet  () const;

    // ---------------------
    // --- PRIVATE: Data ---
    // ---------------------
    boost::shared_ptr<crawl::StateMachineMgr>       m_pStateMachineMgr;
    std::unique_ptr<crawl::LookForWordDomFinder>    m_lookForWordDomFinder;
    crawl::SiteMapGetter        m_sitemapGetter;
    std::string					m_outputName;
    FunctionsSetT				m_allFunctions;
    FunctionsVecT				m_matchFunctionsCrawler;
    FunctionsVecT               m_matchFunctionsTemplate;
    FunctionsVecT				m_templateBeginMiningFunctions;
    FunctionsVecT				m_crawlerBeginMiningFunctions;
    int                         m_iMiningDoneStatus;
    boost::posix_time::ptime 	m_tStartUTC;
    std::string                 m_sHandlerContextName;
    std::map<std::string,int>   m_handlerContinuePositions; // For each handler we save the dom position when the handler is done. Use domGetContinuePos() or domContinueSearch() for utilizing this.
    std::string                 m_sBeginMiningHandlerContextName;
    crawl::CrawlerCommandQueue  m_crawlerCommandQueue;
    QThread*                    m_minerWorkerThread;
    crawl::MinerWorker*         m_minerWorker;
    mutable std::map<std::string, std::unique_ptr<crawl::LookForWordMgr>> m_lookForWordMgrs;


    // --- Runmode configuration ---
    bool						m_bUploadData;
    // --- Mining configuration ---
    crawl::Url					m_urlStart;

    ConnectionT                 m_connectionNetProgress;
    ConnectionT					m_connectionPageLoaded;
    ConnectionT					m_connectionLoadUri;
    ConnectionT                 m_connectionOnClose;
    ConnectionT					m_connectionContinuousTimer;
    ConnectionT					m_connectionContinuousTimer2;

    boost::posix_time::ptime	m_timeLastPageLoadStarted;
    boost::posix_time::ptime	m_timeLastPageLoadFinished;
    boost::posix_time::ptime	m_timeLastScriptStatusUpdate;
    std::string					m_sCurrentLoadingUrl;
    bool						m_bPageLoadInProgress;
    bool						m_bNewPageLoadInitiated;
    std::string                 m_sLatestFullyLoadedUrl;
    int                         m_iPreviousActivityCount;
    int                         m_iTimeSinceLastNetActivityInSeconds;
    int                         m_iConfigTimeReloadIfNoActivityInSeconds;
    int                         m_iReloadIfNoActivityLevel;
    int                         m_iMiningRunTimeInSeconds;
    boost::uint64_t             m_iPageLoadsTotal = 0;
    boost::uint32_t             m_iItemsWritten;

    boost::posix_time::time_duration    m_configAjaxPageLoadDeltaTime;
    //boost::timed_mutex			m_LoadUrlWaitMutex;

    std::string					m_sConfigUrlUploadData;
    std::string 				m_sDecimalPoint;
    std::string 				m_sThousandsSep;
    crawl::MiningStepE          m_nextMiningStepE;
    volatile bool               m_waitingForDomReady = false;
    volatile bool               m_workerIsExecutingPhp = false;
    std::string                 m_scriptStatus;
    mutable std::mutex          m_scriptStatusMutex;
    bool                        m_showNetworkActivity = false;
};




