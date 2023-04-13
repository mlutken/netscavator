<?php
require_once "webminer.php";
require_once "utils.php";

settingSet      ( 'forceClickNextLink', 'false' );                // Set to true if you have no product urls and have to use the url of the search page. Otherwise you wont get next links clicked since the hashIDs will be the same for all pages
settingSet      ( 'scanMode', 'full' );                             // Default scanMode.
settingSet      ( 'saveFallbackDataFromSearchListing', 'true' );    // Default value. Set to false in impl. if you have long searchlistings with many items and are afraid of running out of RAM

settingSet		( 'maxSearchListPages'		, '1000000' );
settingSet		( 'crawlerModeExcludeCSS'	, '1' );

settingSet      ( "item_master", "0" ); 				// True / false script is getting master items
settingSet		( "item_master_reliability", "0");		// Default reliability is 0.

domActionCreate ( "executeSearch__SearchStep__ACTION",  "click" );
domActionCreate ( "nextSearchStep__SearchStep__ACTION", "click" );
domActionCreate ( "clickNext__SearchResults__ACTION",   "click" );

modifierCreate  ( "results_url__SearchResultsCategories__MOD", "ensureAbsoluteUrl");

modifierCreate  ( "item_url__SearchResults__MOD",       "ensureAbsoluteUrl" );
modifierCreate  ( "item_price__SearchResults__MOD",     "trimNumber"  );
modifierCreate  ( "currency_code__SearchResults__MOD",  "toLower" );

modifierCreate  ( "item_url__ItemPage__MOD",            "trimDefault"        );
modifierCreate  ( "item_image_url__ItemPage__MOD",      "ensureAbsoluteUrl" );
modifierCreate  ( "item_price__ItemPage__MOD",          "trimNumber"  );
modifierCreate  ( "description_html__ItemPage__MOD"	,   "getInnerHtmlText__MOD" ); // Alternatives getHtmlText__MOD, getInnerHtmlText__MOD
modifierCreate  ( "breadcrumbs__ItemPage__MOD"	    ,   "getInnerHtmlText__MOD" ); // Alternatives getHtmlText__MOD, getInnerHtmlText__MOD
modifierCreate  ( "currency_code__ItemPage__MOD"	,   "toLower" );

// -------------------------------------------------------------------------
// --- Default dom sequences to find standard elements on a product page ---
// -------------------------------------------------------------------------
// By default we use index_core=products and type_core=product, normally no dom sequences
// Would need to be defined for this.
settingSet      ( "index_core", "products" );
settingSet	( "type_core", "product");

// ----------------------------------
// --- item_title__ItemPage__FIND ---
// ----------------------------------
//domSeqCreate("item_title__ItemPage__FIND#1", "H1, itemprop, name", "equals",  1 | TEXT_NODE);
//domSeqCreate("item_title__ItemPage__FIND#2", "H1", "equals",  1 | TEXT_NODE);
//domSeqCreate("item_title__ItemPage__FIND#3", "H1, *, itemprop, name, content", "equals",  1 );

// ----------------------------------
// --- item_image__ItemPage__FIND ---
// ----------------------------------
//domSeqCreate("item_image_url__ItemPage__FIND#1", "domFindLargestImage" );


// ----------------------------------
// --- item_price__ItemPage__FIND ---
// ----------------------------------
//domSeqCreate("item_price__ItemPage__FIND#1", "itemprop, price, content", "equals",  1 );
//domSeqCreate("item_price__ItemPage__FIND#2", "content, ?, itemprop, price", "equals",  -2 );
//domSeqCreate("item_price__ItemPage__FIND#3", "itemprop, price, *, content", "equals",  1 );
//domSeqCreate("item_price__ItemPage__FIND#4", "itemprop, price", "equals",  1 | TEXT_NODE);


// --- description_html__ItemPage__FIND ---
//domSeqCreate("description_html__ItemPage__FIND#1", "itemprop, description", "equals");

// -----------------------------------
// --- breadcrumbs__ItemPage__FIND ---
// -----------------------------------
/** Tries to find something containing "breadcrumb", but stopping a title position. */
function breadcrumbs__finderFromTitle()
{
    $pos = 0;
    $stop_pos_save = domStopPos();
    $pos_title = domFindPos("item_title__ItemPage__FIND");
    domStopPosSet($pos_title);

    $pos = domFind("breadcrumb", "icontains");
    domStopPosSet($stop_pos_save); // Restore any old dom stop pos
    return $pos;
}

//domSeqCreate("breadcrumbs__ItemPage__FIND#1", "itemscope, itemtype, http://schema.org/BreadcrumbList", "equals");
//domSeqCreate("breadcrumbs__ItemPage__FIND#2", "itemscope, #contains:schema.org/BreadcrumbList", "equals");
//domSeqCreate("breadcrumbs__ItemPage__FIND#3", "itemscope, itemtype, #contains:data-vocabulary.org/Breadcrumb", "equals");
//domSeqCreate("breadcrumbs__ItemPage__FIND#4", "itemscope, #contains:data-vocabulary.org/Breadcrumb", "equals");
//domSeqCreate("breadcrumbs__ItemPage__FIND#5", "breadcrumbs__finderFromTitle");


function TEMPLATE__parseCommandLine ( $commandParams )
{
    parseCommandLine ( "doClickNext=1;maxSearchListPages=1000000;dbg=0;logShow=ERROR,PROGRESS;checkHash=0;" . $commandParams );
}

function tplHlp_scanMode()
{
    static $scanMode = NULL;
    if ( $scanMode == NULL ) {
        $scanMode = cmdValStrGet("scanMode");
        if ($scanMode == '') $scanMode = settingGet( "scanMode");
    }
    if ($scanMode != 'quick') $scanMode = 'full';
    return $scanMode;
}

function tplHlp_maxSearchListPagesGet()
{
	$max1 = (int)cmdValNumGet('maxSearchListPages');
	$max2 = (int)settingGet('maxSearchListPages');
	return $max1 < $max2 ? $max1 : $max2;
}

/** Return array of item page handler names.
If a TEMPLATE__itemPageNames() function exists then the result of this function
is used otherwise the default array with a single ['ItemPage'] is returned. */
function tplHlp_itemPageNamesGet()
{
	if (function_exists ('TEMPLATE__itemPageNames()')) {
		return TEMPLATE__itemPageNames();
	}
	return ['ItemPage'];
}


function TEMPLATE__doSetup()
{
    global $g_searchListingItemCounter, $g_productPageItemCounter;
    $g_searchListingItemCounter = 0;
    $g_productPageItemCounter = 0;

    itemsMinedReset();
    // Set some default settings values. Override in local script if needed or in

    // Look for word start and stop sequences
    $itemPageNames = tplHlp_itemPageNamesGet();
    foreach(tplHlp_itemPageNamesGet() as $itemPageName) {
		if (domSeqExists("item_data_lfw_start_pos__${itemPageName}__FIND"))
			lfwStartPosDomSeqSet($itemPageName, "item_data_lfw_start_pos__${itemPageName}__FIND");

		if (domSeqExists("item_data_lfw_stop_pos__${itemPageName}__FIND"))
			lfwStopPosDomSeqSet($itemPageName, "item_data_lfw_stop_pos__${itemPageName}__FIND");
    }


    // --- Debug settings : TODO: Do we need this anymore given the new logging system ? ---
    $dbg = cmdValNumGet("dbg");
    $dbgProgress = cmdValNumGet("dbgProgress");
    configDebugOutputSet ($dbg > 1 );
    configProgressOutputSet($dbgProgress > 0);

    clog(CrawlerLog::DEBUG, "TEMPLATE__doSetup, settingGet ('scanMode'): " .  settingGet ('scanMode'));

    callFunction ("PROJECTTEMPLATE__doSetup");
}


function TEMPLATE__beginMining()
{
    outputHeader();  // Required. Outputs a section with shop name etc.
    $urlQueueSize = urlQueueSize();

    clog(CrawlerLog::PROGRESS, "TEMPLATE__beginMining, urlQueueSize: '$urlQueueSize'\n");
    callFunction ("PROJECTTEMPLATE__beginMining");
}

function TEMPLATE__endMining()
{
    dataPushContext ( "end_mining_common" );
    $items_mined = itemsMinedStr();
    outputDirect ( "items_mined", $items_mined );
    dataPopContext  ();

    printf("TEMPLATE__endMining! Total number of items mined: {$items_mined}\n");
    callFunction ("PROJECTTEMPLATE__endMining");
}


function TEMPLATE__getStatus()
{
    //$s = "myvar=myval";
    $s = "";
    $s .= callFunction ("PROJECTTEMPLATE__getStatus");
    return $s;
}

// ------------------------------------------
// --- Default template __match functions ---
// ------------------------------------------
function TEMPLATE__SearchStep__match()
{
//     printf("FIXMENM TEMPLATE__SearchStep__match()");
    return removeTrailingSlash(urlCurrent()) == removeTrailingSlash(settingGet("DoSearchUrl"));
}

function TEMPLATE__SearchResultsCategories__match()
{
//     printf("FIXMENM TEMPLATE__SearchResultsCategories__match()");
    return  domFind("match__SearchResultsCategories__FIND") ||
            domFind("itemStart__SearchResultsCategories__FIND");
}

function TEMPLATE__SearchResults__match()
{
//     printf("FIXMENM TEMPLATE__SearchResults__match()");
    return  domFind("match__SearchResults__FIND") ||
            domFind("urlsContainer__SearchResults__FIND") ||
            domFind("itemStart__SearchResults__FIND");
}

function TEMPLATE__ItemPage__match()
{
    return  domFindPos("match__ItemPage__FIND") ||
            (
                domFindPos("item_price__ItemPage__FIND") &&
                domFindPos("item_title__ItemPage__FIND") &&
                domFindPos("description_html__ItemPage__FIND")
            )
            ;
}

function TEMPLATE__DefaultHandler__match()
{
    return true;
}



// ----------------------------
// --- _Search_ functions ---
// ----------------------------
function TEMPLATE__SearchStep__mine() {}


function TEMPLATE__SearchStep__navigate()
{
    global $g_iSearchListPageCounter, $g_iNumberOfItemsFound, $g_curPageHashID;
    $g_curPageHashID = '';
    $g_iSearchListPageCounter   = 0;
    $g_iNumberOfItemsFound      = -1;   // -1 means we don't know how many items we found. Lots of sites does not display this information on their searchlisting pages

    clog(CrawlerLog::PROGRESS, "TEMPLATE__SearchStep__navigate");
	doActionsFindFromList('SearchStep', 'TEMPLATE__SearchStep__actions');
    doActionFind ( "executeSearch__SearchStep__FIND", "executeSearch__SearchStep__ACTION" );       // Main 'execute search' action

    // If we have pages in the queue from example an initial sitemap, then return false to allow
    // underlying C++ code to start emptying the queue by loading the productPages URLs.
    if (urlQueueSize() > 0) {
        clog(CrawlerLog::PROGRESS, "urlQueueSize: %d, SearchStep: nextState Get URL from queue.\n", urlQueueSize() );
        return false;
    }


    if (navNumStatesGet() > 0) {
        return true;    // Expect navigator to execute a pageload
    }
    else {
        return false;   // No navigator => exit
    }
}


// -----------------------------------
// --- __SearchResults__ functions ---
// -----------------------------------
function TEMPLATE__SearchResults__addUrl()
{
	if (domFind("url__SearchResults__FIND")) {
		$url = valueGet("ensureAbsoluteUrl");
		urlQueueAppendUnique($url);
        clog(CrawlerLog::PROGRESS, "TEMPLATE__SearchResults__addUrl: $url\n");
	}
}

function TEMPLATE__SearchResults__mine()
{
    clog(CrawlerLog::PROGRESS, "TEMPLATE__SearchResults__mine()\n");
    global $g_curPageHashID, $g_prevPageHashID;   // used to detect end of searchlistings in case the last page has a next button, but does not load a new page, but just the last again. CdonDk has this problem

    // Check for a quick SearchResults where we simply add URLs to the queue
    if (domFind("urlsContainer__SearchResults__FIND")) {
        clog(CrawlerLog::PROGRESS, "urlsContainer__SearchResults__FIND: Only add urls from SearchResults.\n");
       	$urlQueueSizeBefore = urlQueueSize();
    	loopAllChildren('urlsContainer__SearchResults__FIND', 'TEMPLATE__SearchResults__addUrl');

       	$urlsAddedCount = urlQueueSize() - $urlQueueSizeBefore;
        clog(CrawlerLog::PROGRESS, "urlsContainer__SearchResults__FIND: Added {$urlsAddedCount} URLs.\n");

        return;
    }


    $g_prevPageHashID = $g_curPageHashID;
    $g_curPageHashID = "";

    $positions = array();

    $logDomFindType = '';
    $savePos = domPos();
    if (domFind("itemsAllContainer__SearchResults__FIND")) {
        $logDomFindType = 'itemsAllContainer__SearchResults__FIND';
        $positions = nodeChildren();
    }
    else {
        if (domSeqExists("itemStart__SearchResults__FIND")) {
            $logDomFindType = 'itemStart__SearchResults__FIND';
            $positions = domFindAll("itemStart__SearchResults__FIND");
        }
        else {
            domNewSearch();
            while (domFindNext("item_url__SearchResults__FIND")) {
                $url = valueGet("item_url__SearchResults__MOD");
                urlQueueAppendUnique($url);
            }
        }
    }
    domPosSet($savePos);
    if ( tplHlp_scanMode() == "full" )
        configOutputWriteToFile(false);
    loopAllPositions($positions, 'TEMPLATE__SearchResults__getItem');
    configOutputWriteToFile(true);
    $g_curPageHashID = md5($g_curPageHashID);

    clog(CrawlerLog::PROGRESS, "urlQueueSize: %d, TEMPLATE__SearchResults__mine(), ${logDomFindType}\n", urlQueueSize() );
}

function TEMPLATE__SearchResults__getItem()
{
    global $g_curPageHashID;

    contextBegin( "item" );

    // -----------------------------------
    // --- Check for SKIPPING of title ---
    // -----------------------------------
    $bItemInvalid = false;
    $savePos = domPos();
    if ( domFind("SKIP__SearchResults__FIND") ) {
        outputDirect("SKIP", "_SKIP_TITLE_" );
        $bItemInvalid = true;
    }
    domPosSet($savePos);
    outputValueFind ( "item_invalid__SearchResults__FIND", "item_invalid", "item_invalid__SearchResults__MOD"  );

    if ( $bItemInvalid || outputValueGet( 'item_invalid' ) == "1" ) {
        contextEnd();
        return;
    }

    outputValueFind ( "item_type__SearchResults__FIND", "item_type", "item_type__SearchResults__MOD");

    // Get all item data requested for a search results (listing) page
    outputValuesFindFromList ('SearchResults', 'TEMPLATE__SearchResults__outputNames');
    outputValuesFindFromList ('SearchResults', 'TEMPLATE__SearchResults__attributeNames');

	$outputValuesFunction = outputValueGet( 'item_family' ) . '__SearchResults__outputNames';
    if (function_exists($outputValuesFunction)) {
		outputValuesFindFromList ('SearchResults', $outputValuesFunction);
    }

	$outputValuesFunction = outputValueGet( 'item_type' ) . '__SearchResults__outputNames';
    if (function_exists($outputValuesFunction)) {
		outputValuesFindFromList ('SearchResults', $outputValuesFunction);
    }

    // Find item_url and add to URL queue in case we doing 'full' scan!
    outputValueFind ( "item_url__SearchResults__FIND", "item_url", "item_url__SearchResults__MOD");
	$url = outputValueGet('item_url') ;
	$g_curPageHashID .= $url;

    if (tplHlp_scanMode() == 'quick') {
        $items_mined = itemsMinedInc();
		outputDirect ( 'dbg_state', "SearchResults__({$items_mined}): '" . navStateString() . "',  OptionIndex: " . navOptionIndexGet("searchStringSelect") );
		outputDirect ( 'dbg_navigation_done', "'" . navNavigationDone() . "'" );
	}
    else { // 'full'
        urlQueueAppendUnique  ( $url );
		clog(CrawlerLog::DEBUG, "TEMPLATE__SearchResults__mine(), urlQueueAppendUnique: '{$url}'\n");
        if ( settingGet("saveFallbackDataFromSearchListing") == "true" ) {
            contextOutputSaveAs ( outputValueGet('item_url') );
        }
    }
    contextEnd();
}




function TEMPLATE__SearchResults__navigate()
{
    global $g_iSearchListPageCounter, $g_iNumberOfItemsFound;
    global $g_curPageHashID, $g_prevPageHashID;   // used to detect end of searchlistings in case the last page has a next button, but does not load a new page, but just the last again. CdonDk has this problem

    clog(CrawlerLog::DEBUG, "TEMPLATE__SearchResults__navigate(): SearchListPageCounter: $g_iSearchListPageCounter\n");

    // ---------------------------------------------------------------------
    // --- Do special processing on first page of search listing results ---
    // ---------------------------------------------------------------------
    if ( $g_iSearchListPageCounter == 1 ) {
        if ( domFind( "numberOfItemsFound__SearchResults__FIND" ) ) {
            $g_iNumberOfItemsFound = valueGet ("numberOfItemsFound__SearchResults__MOD");
        }
        clog(CrawlerLog::DEBUG, "TEMPLATE__SearchResults__navigate(): numberOfItemsFound: $g_iNumberOfItemsFound\n");
    }

    // ---------------------------
    // --- Handle 'click next' ---
    // ---------------------------
    $bMorePages = ++$g_iSearchListPageCounter < tplHlp_maxSearchListPagesGet();

	$hashOk = $g_curPageHashID != $g_prevPageHashID;
	clog(CrawlerLog::DEBUG, "SL (nav): Hash ids  (cur)'$g_curPageHashID' == (prev)'$g_prevPageHashID'\n");
	clog(CrawlerLog::DEBUG, "SL (nav): HashOk: '%d',  checkHash: '%d' forceClickNextLink: '%s'\n", $hashOk, cmdValNumGet("checkHash"), settingGet("forceClickNextLink") );
    if ( $bMorePages && cmdValNumGet("doClickNext") ) {

        if ( domFind( "clickNext__SearchResults__FIND" ) ) {
            if ( $g_curPageHashID != $g_prevPageHashID || cmdValNumGet("checkHash") == 0 || settingGet("forceClickNextLink") == 'true' ) {
                $bOk = doAction("clickNext__SearchResults__ACTION");
                clog(CrawlerLog::DEBUG, "TEMPLATE__SearchResults__navigate(): next elem, pos: '%s', %d\n", valueGet(), domPos() );
                clog(CrawlerLog::DEBUG, "TEMPLATE__SearchResults__navigate(): '$bOk',  urlQueueSize: %d\n", urlQueueSize() );
                return true;
            }
            else {
                clog(CrawlerLog::ERROR, "TEMPLATE__SearchResults__navigate(): Forcing nextState since hash ids match. (cur)'$g_curPageHashID' == (prev)'$g_prevPageHashID'\n    Perhaps you forgot to define 'item_url__SearchResults__FIND'\n");
                if ( $g_curPageHashID == "" ) clog(CrawlerLog::ERROR, "TEMPLATE__SearchResults__navigate(): Forcing nextstate empty hashID for page!!!\n    Perhaps you forgot to define 'item_url__SearchResults__FIND'\n");
            }
        }
    }
    clog(CrawlerLog::DEBUG, "TEMPLATE__SearchResults__navigate(): No next link found!\n");


    // -------------------------------------------------------------
    // --- Handle end of search lising (i.e. no more next pages) ---
    // -------------------------------------------------------------

    // If scanMode=='full' and we have pages in the queue, the return false to allow
    // underlying C++ code to start emptying the queue by loading the item pages URLs.
    if ( tplHlp_scanMode() == "full" ) {
        if ( urlQueueSize() > 0 ) {
            clog(CrawlerLog::DEBUG, "Queue length: %d, TEMPLATE__SearchResults__navigate(): nextState Get URL from queue.\n", urlQueueSize());
            return false;
        }
    }

    // Unless we are at navigators last state, we return to the DoSearchPage
    if ( !navNavigationDone() ) {
        urlLoad( settingGet("DoSearchUrl") );
        navNextState();

        clog(CrawlerLog::DEBUG, "TEMPLATE__SearchResults__navigate(): next State: '%s'\n", navStateString() );

        return true;
    }
    else {
        clog(CrawlerLog::PROGRESS, "TEMPLATE__SearchResults__navigate():  Navigation done!!! state: '%s',  '%d'\n", navStateString(), navNavigationDone() );
        return false;
    }
}

// -------------------------------
// --- SearchResultsCategories ---
// -------------------------------

function TEMPLATE__SearchResultsCategories__mine()
{
    if (domSeqExists("itemStart__SearchResultsCategories__FIND")) {
        $positions = domFindAll("itemStart__SearchResultsCategories__FIND");
        loopAllPositions($positions, 'TEMPLATE__SearchResultsCategories__getItem');
    }
    // If itemStart__SearchResults__FIND is not defined we assume that results_url__SearchResultsCategories__FIND directly finds a URL
    else {
        domNewSearch();
        while (domFindNext("results_url__SearchResultsCategories__FIND")) {
            $url = valueGet("results_url__SearchResultsCategories__MOD");
            urlQueueAppendUnique($url);
        }
    }
    clog(CrawlerLog::PROGRESS, "urlQueueSize: %d,  TEMPLATE__SearchResultsCategories__mine()\n", urlQueueSize() );
}

function TEMPLATE__SearchResultsCategories__getItem()
{
    domFind ( "results_url__SearchResultsCategories__FIND");
	$url = valueGet("results_url__SearchResultsCategories__MOD");
	urlQueueAppendUnique($url);
	clog(CrawlerLog::DEBUG, "TEMPLATE__SearchResultsCategories__getItem() pos:" . domPos() . " urlQueueAppendUnique: '{$url}'\n");
}

function TEMPLATE__SearchResultsCategories__navigate()
{
	return helper_TEMPLATE__DefaultHandler__navigate('TEMPLATE__SearchResultsCategories__navigate');
}

// -------------------------------
// --- _ItemPage_ functions ---
// -------------------------------

function TEMPLATE__ItemPage__beginMining()
{
    clog(CrawlerLog::DEBUG, "TEMPLATE__ItemPage_beginMining\n");
}


function TEMPLATE__ItemPage__mine()
{
	helper_TEMPLATE__ItemPage__mine('ItemPage');
}


function TEMPLATE__ItemPage__navigate()
{
	return helper_TEMPLATE__DefaultHandler__navigate('TEMPLATE__ItemPage__navigate');
}


// ----------------------------------
// --- _DefaultHandler_ functions ---
// ----------------------------------


function TEMPLATE__DefaultHandler__navigate()
{
    clog(CrawlerLog::WARNING, "TEMPLATE__DefaultHandler__navigate: No handler for URL:\n%s\n", urlCurrent() );
    return helper_TEMPLATE__DefaultHandler__navigate('TEMPLATE__DefaultHandler__navigate');
}

// ------------------------
// --- Helper functions ---
// ------------------------

/**
Output miner name, site URL, locale settings and a record with shop information. */
function outputHeader()
{
    // TODO: Remove this, not used I think!
    $shop_url = settingGet ('shop_url');
    if ('' == $shop_url) {
        $shop_url = settingGet('urlSite');
        settingSet('shop_url', $shop_url);
    }
    // end TODO

    contextBegin    ( "begin_mining_common" );
    outputDirect    ( 'project' , settingGet('project') );
    outputDirect    ( "url_site", settingGet('urlSite') );
    outputDirect    ( "output_name", settingGet('outputName')  );
    outputDirect    ( "shop_id", settingGet('shop_id')  );
    outputDirect    ( "DoSearchUrl", settingGet('DoSearchUrl')  );
    outputDirect    ( 'shop_url', $shop_url );  // TODO: Remove this, not used I think!
    outputDirect    ( "use_sitemap", settingGet('use_sitemap')  );

    outputDirect    ( 'country_code' , settingGet('country_code') );
    outputDirect    ( 'language_code' , settingGet('language_code') );
    outputDirect    ( 'currency_code' , settingGet('currency_code') );
    outputDirect    ( 'decimal_point' , settingGet('decimal_point') );
    outputDirect    ( 'thousands_sep' , settingGet('thousands_sep') );
    contextEnd      ();
}



function dateToIso($date, $format, $forceYear = 0, $forceMonth = 0, $forceDay = 0)
{
	$date = trim($date);
	$dateISO = DateTime::createFromFormat($format, $date);
	if ($dateISO === false) {
        return "FIXME -- $date -- 1 createFromFormat failed";
	}
	$year = $dateISO->format("Y");
	$month = $dateISO->format("m");
	$day = $dateISO->format("d");
	if ($forceYear) {
		$dateISO->setDate ( $forceYear,  $month , $day );
	}
	if ($forceMonth) {
		$dateISO->setDate ( $year,  $forceMonth, $day );
	}
	if ($forceDay) {
		$dateISO->setDate ( $year,  $month , $forceDay );
	}
	return $dateISO->format("Y-m-d");
}
