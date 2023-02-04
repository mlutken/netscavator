<?php
require_once "webminer.php";

// ----------------------------
// --- Global configuration ---
// ----------------------------
function Crawler__outputName             () {  return "ExNavigatorUrlLoad"; }
function Crawler__urlSite   () {  return "examples.netscavator.com/sites/ExNavigatorUrlLoad/index.php";       }
function Crawler__urlStart  () {  return "examples.netscavator.com/sites/ExNavigatorUrlLoad/dosearch.php";    }

function Crawler__beginMining()         
{
    // Define dom sequences for the positions we need
    domSeqCreate  ( "ProductStart__FIND"   , "DIV, class, product" , "equals"          );
    domSeqCreate  ( "ProductName__FIND"    , ""                    , "equals"          );  // Empty means never find => fallback to navigator attribute
    domSeqCreate  ( "ProductPrice__FIND"   , "EUR"                 , "contains"        );
 
    domSeqCreate  ( "DoClickNext__FIND"    , "Next, /A"            , "contains", -2    );
    // (NOTE: we step back so we are sure to be within the A tag when we 'click' on the link.)

    domSeqCreate    ( "alwaysFindMe__FIND", "HTML", "equals" );   // (Always find) HTML tag always present on a page
    

    // Navigator
    navUrlLoadCreate("clothesPageLoader", "examples.netscavator.com/sites/ExNavigatorUrlLoad/searchlisting.php");
    navAttributeNamesCreate ("product_name, sex, fabric");
    navOptionAdd    ( "1"      , "?clothes_type=dress&fabric_type=wool&page=0"     , ATTR, "Dress,     F,  Wool"    );  
    navOptionAdd    ( "2"      , "?clothes_type=dress&fabric_type=cotton&page=0"   , ATTR, "Dress,     F,  Cotton"  );  
    navOptionAdd    ( "3"      , "?clothes_type=tie&fabric_type=wool&page=0"       , ATTR, "Tie,       M,  Wool"    );  
    navOptionAdd    ( "4"      , "?clothes_type=tie&fabric_type=cotton&page=0"     , ATTR, "Tie,       M,  Cotton"  );  
    navOptionAdd    ( "5"      , "?clothes_type=jacket&fabric_type=wool&page=0"    , ATTR, "Jacket,    MF, Wool"    );  
    navOptionAdd    ( "6"      , "?clothes_type=jacket&fabric_type=cotton&page=0"  , ATTR, "Jacket,    MF, Cotton"  );  
}


// -------------------------------
// --- DoSearch page functions ---
// -------------------------------
function Crawler__DoSearch__match()          
{   
    return contains_fn( urlCurrent() , "dosearch.php" );  // Handle do search page.
}

function Crawler__DoSearch__mine()            
{
    // Nothing to mine on the "do search" page
}


function Crawler__DoSearch__navigate()           
{   
    // We only need to do a single action here which is loading the next page.
    // The 'UrlLoader' of the navigator will do this when we fire the named action
    // 'clothesPageLoader'. To keep things consistent we use the doActionFind, which 
    // requires us to actually find something on the page otherwise the associated 
    // action (loading the page directly) is never fired. We have created a dom sequence
    // which simply looks for a 'HTML' tag which should always be present on a page and 
    // thus the 'find' part of doActionFind will return true and the action is fired loading
    // the next page according to the current state of the navigator.
    // if you don't like the named dom sequence 'alwaysFindMeSeq' approach you can also 
    // use one of the two other ways to achive loading shown here, but commented out.
     doActionFind    ( 1, "alwaysFindMe__FIND", "clothesPageLoader"   ); // 'Always find'. The HTML tag will allways be present

    // Alternative ways to fire the action 'clothesPageLoader' in the navigator.
//    doActionFind    ( 1, "HTML", "clothesPageLoader"   ); // 'Always find'. The HTML tag will allways be present
//    navDoAction ( "clothesPageLoader"); // Fire action directly. Possible since UrlLoader needs no dom position

    return true;  // Return 'true' since the navigation results in loading of a new page.
}


// --------------------------------
// --- Search listing functions ---
// --------------------------------
function Crawler__SearchListing__match()          
{   
    return contains_fn( urlCurrent() , "searchlisting" );  // Handle any page with 'searchlisting' in the URL.
}

function Crawler__SearchListing__mine()            
{
    domNewSearch();
    while ( domFindNext ( 1, "ProductStart__FIND" ) ) {
        domPointerPush();
        $iStopPos = domFindNextPos( 1, "ProductStart__FIND" );
        domSetStopPos( $iStopPos );
        GetProduct();
        domClearStopPos();
        domPointerPop();
    }
}

function GetProduct()            
{
    // Get product name and  product price
    contextBegin("product");
    outputValueFindNext( 1, "ProductName__FIND", "product_name", "eraseAll", ":" );// Get value from Navigator attribute by fallback on fail to find dom pos
    outputValueFindNext( 1, "ProductPrice__FIND", "product_price", "trimNumber" );
    outputValueFindNext( 1, "", "sex" );   // Get value from Navigator attribute by fallback on fail to find dom pos
    outputDirect ( "fabric" , navAttributeGet("fabric") );  // Gettting the attribute value directly  
    outputDirect ( "currency_name" , "EUR" );  
    outputDirect ( "navigator_state", navStateString() );   // Write the navigator state for demo/debug
    outputDirect ( "dbg_state_progress", (string)navLastStateIndexGet() . " / " . navStateIndexGet() ); 
    contextEnd();
}

function Crawler__SearchListing__navigate()           
{   
    if ( domFind ( 1, "DoClickNext__FIND" ) ) {
        nodeClick();
        return true;    // if we find a 'next' link then a new page will be loaded
    }
    else {
        if ( !navNavigationDone() ) {
            navNextState(); // Go to next state in navigator
            urlLoad ( "examples.netscavator.com/sites/ExNavigatorUrlLoad/dosearch.php" );  // Back to search page
            return true;
        }
        return false;   // No 'next' link, no new page will be loaded. Miner closes down.  
    }
}

?>

