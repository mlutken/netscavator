<?php
require_once ('cpp_crawl.php');
require_once ('string_utils.php');
require_once ('utils.php');

/**
* \defgroup simplePhpStringFunctions Simple PHP string manipulation
* @{

Simple PHP string manipulation and testing functions.
*/

/** Test if string contains a substring.
\todo Document this!
*/
function contains($haystack, $needle, $case = true)
{
    if ($case)
        return strpos($haystack, $needle, 0) !== false;
    return stripos($haystack, $needle, 0) !== false;
}

function containsAnyOf($haystack, $aNeedles)
{
    $bFoundOne = false;
    foreach ($aNeedles as $needle) {
        $pos = strpos($haystack, $needle);
        if ($pos !== false) {
            $bFoundOne = true;
            break;
        }
    }
    return $bFoundOne;
}

function icontainsAnyOf($haystack, $aNeedles)
{
    $bFoundOne = false;
    foreach ($aNeedles as $needle) {
        $pos = stripos($haystack, $needle);
        if ($pos !== false) {
            $bFoundOne = true;
            break;
        }
    }
    return $bFoundOne;
}


function startsWith($haystack, $needle, $case = true)
{
    if ($case)
        return strpos($haystack, $needle, 0) === 0;

    return stripos($haystack, $needle, 0) === 0;
}

function endsWith($haystack, $needle, $caseSensitive = true)
{
    $expectedPosition = strlen($haystack) - strlen($needle);

    if ($caseSensitive)
        return strrpos($haystack, $needle, 0) === $expectedPosition;

    return strripos($haystack, $needle, 0) === $expectedPosition;
}

function icontains($haystack, $needle)
{
    return stripos($haystack, $needle, 0) !== false;
}

function istartsWith($haystack, $needle)
{
    return stripos($haystack, $needle, 0) === 0;
}

function iendsWith($haystack, $needle)
{
    $expectedPosition = strlen($haystack) - strlen($needle);
    return strripos($haystack, $needle, 0) === $expectedPosition;
}

function replaceLast($search, $replace, $subject)
{
    $pos = strrpos($subject, $search);

    if($pos !== false)
    {
        $subject = substr_replace($subject, $replace, $pos, strlen($search));
    }

    return $subject;
}

function removeLast($search, $subject)
{
    return replaceLast($search, '', $subject);
}

function removeTrailingSlash($path)
{
    if (endsWith($path, "/")) {
        return removeLast("/", $path);
    }
    return $path;
}

/**@}*/

// For generating PHP to MinerCreator output window
global $NL, $TAB, $TAB2, $TAB3, $TAB4;
$NL = "<br>\n";
$TAB = "&nbsp;&nbsp;&nbsp;&nbsp;";
$TAB2 = $TAB . $TAB;
$TAB3 = $TAB . $TAB . $TAB;
$TAB4 = $TAB . $TAB . $TAB . $TAB;


/**
* \defgroup browserScrollFunctions Scrolling the browser
* @{

Functions for scrolling the browser window. Does not work in browser mode 'simple'.
*/


/** Simple Scroll browser all way to the bottom of the page.
    No rebuilding or expecting the page to load data dynamically on scroll.
    For this please use browserScrollDownWait()
*/
function browserScrollToButtom($maxScrolls = 200, $timeOutInMs = 1000)
{
    for ($i = 0; $i < $maxScrolls; $i++) {
        $lastScrollPosY = browserScrollPosYGet();

        browserScroll (0, 10000);
        waitForDomReady($timeOutInMs);
        $currentScrollPosY = browserScrollPosYGet();

        if ($lastScrollPosY == $currentScrollPosY) {
            waitForDomReady($timeOutInMs);
            break;
        }
    }
}

/** Scroll all the way down the current page, and rebuild linear DOM when done.
    After this call the browser will be scrolled to the very end of the page
    , or as far as 1000 pixels x \a $maxScrolls down in case the end of page is not reached.
    After this the linear DOM is rebuilt and ready for further processing.

    Use this function typically on Crawler__SearchResults__mine(). For example like this:

    \code
    function Crawler__SearchResults__mine()
    {
        scrollDown();
        TEMPLATE__SearchResults__mine();
    }
    \endcode

    The above makes sure that in case of a shop using
    scroll-down-to-dynamically-increase-search-results-ajax-style
    ,like for example Google uses on it's image results pages, then
    we still get all results processed.

    @param maxScrolls [in] Maximum number of times to try and scroll down before reaching the end.
    @param timeOutInMs [in] Timeout  in milliseconds for each scroll.
    */
function browserScrollDownWait($maxScrolls = 100, $timeOutInMs = 1000)
{
    for ($i = 0; $i < $maxScrolls; $i++) {
        $lastActivityCounter = networkActivityCounter();
        $lastScrollPosY = browserScrollPosYGet();

        browserScroll ( 0, 1000);
        waitForDomReady($timeOutInMs);
        $currentActivityCounter = networkActivityCounter();
        $currentScrollPosY = browserScrollPosYGet();

        if ($lastScrollPosY == $currentScrollPosY) {
            waitForDomReady($timeOutInMs);
            domRebuildWait();
            break;
        }
    }
}

/** Repeatedly find and click the "get more" / "load more" button and finally wait
to rebuild the entire dom. Use normally like this in your script:
\code
function Crawler__SearchResults__mine()
{
	domSeqCreate ("getMoreBtnFind", "BUTTON, class, product-list__button", "contains", 0);
	clickGetMoreScrollDownWait("getMoreBtnFind", 200);

	return TEMPLATE__SearchResults__mine();
}
\endcode

@todo Fix spelling error in this function name!

 */
function clickGetMoreScrollDownWait($clickMoreBtnFindSeq, $maxIterations = 200,  $rebuildDomForEachClick = true, $timeOutInMs = 30000)
{
	echo "clickGetMoreScrollDownWait";
    for ($i = 0; $i < $maxIterations; $i++) {
        $lastScrollPosY = browserScrollPosYGet();


		if (!domFind($clickMoreBtnFindSeq) ) {
			break;
		}
        nodeClickWait($timeOutInMs);
        if ($rebuildDomForEachClick) {
            domRebuildWait();
		}
		browserScrollToButtom();
        $currentScrollPosY = browserScrollPosYGet();
        if ($lastScrollPosY == $currentScrollPosY) {
            waitForDomReady($timeOutInMs);
            break;
        }
    }
	domRebuildWait();
}

/**@}*/

/** Execute all actions in list given.
Actions are executed using: doActionFind ();
You must supply a handler context and given for example a call like this:
	doActionsFindFromList('selectType, executeSearch', 'SearchStep');

We will get the following actitions executed like this:
	doActionFind ( "selectType__SearchStep__FIND", "selectType__SearchStep__ACTION" );
	doActionFind ( "executeSearch__SearchStep__FIND", "executeSearch__SearchStep__ACTION" );

NOTE: The above example that the action 'executeSearch' is often 'hardcoded' as part of the template's
TEMPLATE__SearchStep__navigate() like for example in the 'standard_project_item_template.tpl.php'.
\param $handlerContext [string] Handler context name like 'SearchStep' or 'SearchListing' ... etc.
\param $actions [mixed] list of action names given as an array or a comma separated string or as a function
                name which MUST return a comma separated string.
*/
function doActionsFindFromList($handlerContext, $actions)
{
    $actionsArray = array();
    if (is_array($actions)) $actionsArray = $actions;
    else if (function_exists($actions)) {
        $actionsString = call_user_func($actions);
        $actionsArray = explodeTrim(',', $actionsString);
    }
    else if (is_string($actions)) {
        $actionsArray = explodeTrim(',', $actions);
    }
    foreach($actionsArray as $action) {
        $action = $action . '__' . $handlerContext;
        doActionFind ( "{$action}__FIND", "{$action}__ACTION" );
    }
}

function outputValuesFindFromList($handlerContext, $outputNames)
{
    $outputNamesArray = array();
    if (is_array($outputNames)) $outputNamesArray = $outputNames;
    else if (function_exists($outputNames)) {
        $outputNamesString = call_user_func($outputNames);
        $outputNamesArray = explodeTrim(',', $outputNamesString);
    }
    else if (is_string($outputNames)) {
        $outputNamesArray = explodeTrim(',', $outputNames);
    }
    foreach($outputNamesArray as $outputName) {
        $prefix = "{$outputName}__{$handlerContext}";
        outputValueFind ( "{$prefix}__FIND", $outputName, "{$prefix}__MOD" );
    }
}


// ---
function domLoopAllNext($domSeq, $loopFunction)
{
    if ( !function_exists($loopFunction) ) return 0;

    $lastPos = 0;
    while ( domFindNext ( 1, $domSeq ) ) {
        domPointerPush();
        $lastPos = domPos();
        domStartPosSet( domPos() );
        $iStopPos = domFindNextPos( 1, $domSeq );
        domStopPosSet( $iStopPos );
        call_user_func($loopFunction);
        domStartPosClear();
        domStopPosClear();
        domPointerPop();
    }
    return $lastPos;
}

function domLoopAll($domSeq, $loopFunction)
{
    domNewSearch();
    return domLoopAllNext($domSeq, $loopFunction);
}

function domFindAllPositions( $domSeq )
{
    $posSave = domPos();
    $a = array();
    domNewSearch();
    while ( domFindNext( $domSeq) ) {
        $a[] = domPos();
    }
    domPosSet( $posSave );
    return $a;
}


/** Loops all child nodes of the domNode (if) found, using the domSeq supplied, calling the loop function for each child.
DOM start and stop positions are set to the current (child) position and the next, so
that one can use domFind(); inside the loopFunction and be sure that searches are confined
within these two positions.
\return The loopFunction can optinally return a value, and values from all calls to loopFunction
are returned as an array from this function.*/
function loopAllChildren($domSeq, $loopFunction, $iSearchDir = NEAREST_AUTO)
{
    if (domFind($domSeq)) {
        $positions = nodeChildren($iSearchDir);
        return loopAllPositions($positions, $loopFunction);
    }
    return array();
}


/** Loops all child nodes of the current domNode, calling the loop function for each.
DOM start and stop positions are set to the current (child) position and the next, so
that one can use domFind(); inside the loopFunction and be sure that searches are confined
within these two positions.
\return The loopFunction can optinally return a value, and values from all calls to loopFunction
are returned as an array from this function.*/
function nodeLoopAllChildren($domSeq, $loopFunction, $iSearchDir = NEAREST_AUTO)
{
    $positions = nodeChildren($iSearchDir);
    return loopAllPositions($positions, $loopFunction);
}

/** Loops all child nodes of the domNode at postion, calling the loop function for each.
DOM start and stop positions are set to the current (child) position and the next, so
that one can use domFind(); inside the loopFunction and be sure that searches are confined
within these two positions.
\return The loopFunction can optinally return a value, and values from all calls to loopFunction
are returned as an array from this function.*/
function posLoopAllChildren($domPos, $loopFunction)
{
    $positions = posChildren($domPos);
    return loopAllPositions($positions, $loopFunction);
}

/** Loops all positions in array given, calling the loop function for each.
DOM start and stop positions are set to the current position and the next, so
that one can use domFind(); inside the loopFunction and be sure that searches are confined
within these two positions.
\return The loopFunction can optinally return a value, and values from all calls to loopFunction
are returned as an array from this function.*/
function loopAllPositions($positions, $loopFunction)
{
    if ( !function_exists($loopFunction) ) {
        print "WARNING: function '$loopFunction' not found!";
        return 0;
    }
    $results = array();
    $posSave = domPos();

    $lastPos = 0;
    $SIZE = count($positions);
    for ( $n = 0 ; $n < $SIZE ; $n++ ) {
        $pos = $positions[$n];
        domPosSet($pos);
        domStartPosSet($pos);
        if ($n+1 < $SIZE) {
            domStopPosSet($positions[$n+1]);
        }
        $results[] = call_user_func($loopFunction);
        domStartPosClear();
        domStopPosClear();
    }
    domPosSet($posSave);
    return $results;
}


/** Check to see if the URL passed starts with either http:// or https:// .
    If not we prepend the siteUrl()

    TODO: Do we need to handle spaces in URLS ? See:
            modifierCreate  ( "item_image_url__ItemPage__MOD", "replaceAll", " ", "%20" );	// Image URLs sometimes have spaces .. tsk tsk ..
    */
function ensureAbsoluteUrl($url)
{
    if ( startsWith($url, 'https://') || startsWith($url, 'http://') ) {
        return $url;
    }

    // Remove any starting '/' from the $url and any ending '/' from the siteUrl
    // To ensure we do not get a double '//' in the final URL.
    if (startsWith($url, '/')) {
        $url = substr($url, 1);
    }
    $url_site = urlSite();
    if (endsWith($url_site, '/')) {
        $url_site = substr($url_site, 0, -1);
    }

    return $url_site . '/' . $url;
}

global $g_startTags, $g_endTags, $g_allAllowedTags;

$g_startTags = array(  'STRONG', 'B', 'I', 'U', 'EM', 'TD', 'TR', 'OL',
						'UL', 'LI', 'H1', 'H2', 'H3', 'H4');

$g_endTags = array(  'P', '/P', 'BR' , 'BR/', '/STRONG', '/B', '/I', '/U',
					'/EM', '/TD', '/TR', '/OL', '/UL', '/LI', '/H1',
					'/H2', '/H3', '/H4');

$g_allAllowedTags = array_merge($g_startTags, $g_endTags);


/** Continue adding HTML text until specific domposition is reached. */
function getSimpleHtmlToSequence($endHtmlSequence)
{
    domPointerPush();
    $endHtmlPos = domFindNextPos($endHtmlSequence);
    domPointerPop();
    return getSimpleHtmlToPos($endHtmlPos);
}


/** Continue adding HTML text until specific domposition is reached. */
function getSimpleHtmlToPos($endHtmlPos)
{
    global $g_allAllowedTags;
    $text = "";
    $level = nodeLevel();
    domPointerPush();

    $endHtmlPos = (int)$endHtmlPos;
    while (!domAtEnd() && domPos() < $endHtmlPos) {
        if (nodeValue() == "IFRAME") break;
//      printf ("FIXMNM: dompos [%d] [%d]: %s\n<br>" , domPos(), valueGet() );

        if (nodeType() == TEXT_NODE) {
            $text .= valueGet() . ' ';
        }
        else if (in_array(valueGet(), $g_allAllowedTags, true)) {
            $text .= '<' . valueGet() . '>';
        }
        domStep(1);
    }
    domPointerPop();
    return $text;
}



/** Continue adding HTML text as long as it is in fact simple. No other elements in between. */
function getSimpleHtmlText__MOD()
{
	global $g_allAllowedTags;
	$text = "";
	$level = nodeLevel();
	domPointerPush();
	$validSimpleHtml = true;
//	while (!domAtEnd() && nodeLevel() >= $level) {
	while (!domAtEnd() && $validSimpleHtml) {
		if (nodeValue() == "IFRAME") break;
//		printf ("FIXMNM: dompos [%d] [%d]: %s\n<br>" , domPos(), nodeLevel(), valueGet() );

		if (nodeType() == TEXT_NODE) {
			$text .= valueGet();
		}
		else if (in_array(valueGet(), $g_allAllowedTags, true)) {
			$text .= '<' . valueGet() . '>';
		}
		else {
			$validSimpleHtml = false;
		}
		domStep(1);
	}
	domPointerPop();
	return $text;
}


/** If \a $mode = 'strict' we only consider html on lower levels than start node (children only, not siblings).
In the default 'normal' mode we also continue with siblings as long as the elements are valid simple HTML. */
function getHtmlText($unusedValue='', $mode='')
{
    global $g_startTags, $g_endTags;

    if (!$mode || $mode == '')
        $mode = "normal";

    $invalidHtmlCount = 0;
    $text = "";
    $level = nodeLevel();
    domPointerPush();

    $insideAhref = false;
    $moreHtml = true;
    while (!domAtEnd() && $moreHtml) {

        $value = valueGet();
        $nodeLevel = nodeLevel();
        $nodeType = nodeType();
        if ($value == "IFRAME") break;

        if ($value == "A") {
            $insideAhref = true;
        }
        if ($value == "/A") {
            $insideAhref = false;
        }

        if ($insideAhref) {
            $invalidHtmlCount = 0;
            if ($nodeType == TEXT_NODE) {
                $text .= $value . ' ';
            }
        }
        else if ($nodeType == TEXT_NODE) {
            $text .= $value . ' '; // NOTE: An extra space! Make it easier to parse with sematicsParse.
            $invalidHtmlCount = 0;
        }
        else if (in_array($value, $g_startTags, true)) {
            $text .= '<' . $value . '>';
            $invalidHtmlCount = 0;
        }
        else if (in_array($value, $g_endTags, true)) {
            $text .= '<' . $value . '> ';   // NOTE: An extra space! Make it easier to parse with sematicsParser, which can then ignore the HTML formatting part.
            $invalidHtmlCount = 0;
        }
        else {
            $invalidHtmlCount++;
            if ($invalidHtmlCount === 1) {
                $text .= ' ';
            }
        }
        domStep(1);
        $nodeLevel = nodeLevel(); // NOTE: Need to update these now as we have "stepped" forward
        $nodeType = nodeType();

        if ($mode === "strict") {
            $moreHtml = ($nodeLevel > $level) || ($nodeLevel === $level);
            if (($nodeLevel == $level) && (($nodeType == ELEMENT_END_TAG) || ($nodeType == ELEMENT_NODE)) )
                $moreHtml = false;
        }
        else {
            $moreHtml = $nodeLevel >= $level || ($invalidHtmlCount == 0);
        }
//           printf ("FIXMNM: dompos [%d] [%d/$level]: %s, invalidHtmlCount: $invalidHtmlCount, mode: '$mode', moreHtml: '%d', nodeType: '%x'\n<br>"
//             , domPos(), nodeLevel(), valueGet(), $moreHtml, $nodeType);
    }
    domPointerPop();

    $trimmedText = trim($text);
    if ($trimmedText == '') {
        return valueGet();
    }

    return $text;
}


/** Get inner and sibling HTML.
We also continue with siblings as long as the elements are valid simple HTML. */
function getHtmlText__MOD()
{
    return getHtmlText('', 'normal');
}


/** Get inner HTML.' We only consider html on lower levels than start node (children only, not siblings).
*/
function getInnerHtmlText__MOD()
{
    return getHtmlText('', 'strict');
}


function innerHtml__MOD()
{
    return innerHtml();
}

/** Find position of the larges image on the page. */
function domFindLargestImage()
{
    domSeqCreate("image__FIND", "IMG", "equals");
    $image_pos = 0;
    $largest_area = 0;
    $positions = domFindAllPositions("image__FIND");
    foreach($positions as $pos) {
        $width = (int)nodeAttributePos($pos, "width", "0");
        $height = (int)nodeAttributePos($pos, "height", "0");
        $area = $width*$height;
        if ($area > $largest_area) {
            $largest_area = $area;
            $image_pos = $pos;
        }
        //printf("pos[$pos] => '%s' [%s, %s]", nodeAttributePos($pos, "src"), $width, $height);
    }
    if ($image_pos) {

        domPosSet($image_pos);
        if (domFindNext("src", "euquals")) {
            domStep(1);
            $image_pos = domPos();
        }
        else {
            $image_pos = 0;
        }
    }
    return $image_pos;
}

// TODO: Move into C++ code
function nodeAttributePos($pos, $attribute_name, $default_val = '' )
{
    domPointerPush();
    domPosSet($pos);
    $attribute_val = nodeAttribute($attribute_name);
    if ($attribute_val == '') {
        $attribute_val = $default_val;
    }
    domPointerPop();
    return $attribute_val;
}

// TODO: Move into C++ code
function nodeEndElement($pos, $attribute_name, $default_val = '' )
{
    domPointerPush();
    domPosSet($pos);
    $attribute_val = nodeAttribute($attribute_name);
    if ($attribute_val == '') {
        $attribute_val = $default_val;
    }
    domPointerPop();
    return $attribute_val;
}


function phpErrorHandler($errno, $errstr, $errfile, $errline)
{
    if (!(error_reporting() & $errno)) {
        // This error code is not included in error_reporting
        return;
    }

    switch ($errno) {
    case E_USER_ERROR:
        echo "<b>ERROR</b> [$errno] $errstr<br />\n";
        echo "  Fatal error on line $errline in file $errfile";
        break;

    case E_USER_WARNING:
        echo "<b>WARNING</b> [$errno] $errstr<br />\n";
        break;

    case E_USER_NOTICE:
        echo "<b>NOTICE</b> [$errno] $errstr<br />\n";
        break;

    default:
        echo "Unknown error type: [$errno] $errstr<br />\n";
        break;
    }

    /* Don't execute PHP internal error handler */
    return true;
}

$old_error_handler = set_error_handler("phpErrorHandler");

// -----------------------------
// --- items_mined functions ---
// -----------------------------

/** Reset number of items_mined. */
function itemsMinedReset()
{
    settingSet("items_mined", "0");
}

/** Increase items_mined counter by 1.
    Return the new value as an integer. */
function itemsMinedInc()
{
    $items_mined = (int)itemsMined() + 1;
    settingSet("items_mined", "{$items_mined}");
    return (int)settingGet("items_mined");
}

/** Get number of items_mined as an integer. */
function itemsMined()
{
    return (int)settingGet("items_mined");
}

/** Get number of items_mined as a string. */
function itemsMinedStr()
{
    return settingGet("items_mined");
}

// ----------------------
// --- Misc functions ---
// ----------------------
function scriptHtmlEntitiesReplaceSet($replaceMap)
{
    scriptHtmlEntitiesReplaceClear();
    foreach ($replaceMap as $lookFor => $replaceWith) {
        scriptHtmlEntitiesReplaceAdd($lookFor, $replaceWith);
    }
}

// ---------------------------
// --- Debugging functions ---
// ---------------------------
function dbgPrintPositions($positions)
{
    foreach($positions as $pos) {
        printf("pos[$pos] => '%s'", nodeValuePos($pos));
    }
}

