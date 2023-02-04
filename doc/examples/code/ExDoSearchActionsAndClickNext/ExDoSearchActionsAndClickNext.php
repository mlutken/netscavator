<?php
require_once "webminer.php";

// ----------------------------
// --- Global configuration ---
// ----------------------------
function Crawler__outputName                       () {   return "ExDoSearchActionsAndClickNext";       }

function Crawler__urlSite  () {   return "examples.netscavator.com/sites/ExDoSearchActionsAndClickNext/index.php";       }
function Crawler__urlStart () {   return "examples.netscavator.com/sites/ExDoSearchActionsAndClickNext/dosearch.php";    }

function Crawler__beginMining()         
{
    // Define dom sequences for the positions we need
    domSeqCreate  ( "DoSearchType__FIND"   , "INPUT, name, producttype", "equals"          );
    domSeqCreate  ( "DoSearchBtn__FIND"    , "INPUT, value, Search"    , "equals"          );
    domSeqCreate  ( "ProductStart__FIND"   , "DIV, class, product"     , "equals"          );
    domSeqCreate  ( "ProductName__FIND"    , "color:green"             , "contains", 1     );
    domSeqCreate  ( "ProductPrice__FIND"   , "EUR"                     , "contains"        );
    
    domSeqCreate  ( "DoClickNext__FIND"    , "Next, /A"                , "contains", -2    );
    // (NOTE: we step back so we are sure to be within the A tag when we 'click' on the link.)
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
    doActionFind ( 1, "DoSearchType__FIND", "inputValue", "all" ); // Type 'all' (action = 'inputValue') in producttype field.
    doActionFind ( 1, "DoSearchBtn__FIND", "click" );              // Click on search button.
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
    printf("SearchListing_mine\n");
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
    outputValueFindNext( 1, "ProductName__FIND", "product_name", "eraseAll", ":" );
    outputValueFindNext( 1, "ProductPrice__FIND", "product_price", "trimNumber" );
    outputDirect ( "currency_name" , "EUR" );  
    contextEnd();
}

function Crawler__SearchListing__navigate()           
{   
    if ( domFind ( 1, "DoClickNext__FIND" ) ) {
        nodeClick();
        return true;    // if we find a 'next' link then a new page will be loaded
    }
    else {
        return false;   // No 'next' link, no new page will be loaded. Miner closes down.  
    }
}

?>

