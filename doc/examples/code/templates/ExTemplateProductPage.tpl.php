<?php
require_once "webminer.php";

// ------------------------------------
// --- DoSearch (DS) page functions ---
// ------------------------------------

function TEMPLATE__DoSearch__mine()            
{
}


function TEMPLATE__DoSearch__navigate()           
{   
    doActionFind ( 1, "ClothesSelect__DoSearch__FIND",   "clothesSelect" ); // Select clothes drop down according to current navigator state
    doActionFind ( 1, "FabricSelect__DoSearch__FIND",    "fabricSelect"  ); // Select fabric drop down according to current navigator state
    doActionFind ( 1, "DoSearchBtn__DoSearch__FIND",     "click" );         // Click on search button.
    return true;  // Return 'true' since the navigation results in loading of a new page.
}


// -------------------------------------
// --- Search listing (SL) functions ---
// -------------------------------------
function TEMPLATE__SearchListing__match()          
{   
    return contains_fn( urlCurrent() , "searchlisting" );  // Handle any page with 'searchlisting' in the URL.
}

function TEMPLATE__SearchListing__mine()            
{
    domNewSearch();
    while ( domFindNext ( 1, "ProductStart__SearchListing__FIND" ) ) {
        domPointerPush();
        $iStopPos = domFindNextPos( 1, "ProductStart__SearchListing__FIND" );
        domSetStopPos( $iStopPos );
        GetProduct_SL();
        domClearStopPos();
        domPointerPop();
    }
}

function GetProduct_SL()            
{
    // Since each URL is only relative to the current site we prepend urlSite()
    if ( domFindNext ( 1, "ProductUrl__SearchListing__FIND" ) ) {
        urlQueueAppendUnique( urlSite() . valueGet() );
    }
}

function TEMPLATE__SearchListing__navigate()           
{   
    if ( domFind ( 1, "DoClickNext__SearchListing__FIND" ) ) {
        nodeClick();
        return true;    // if we find a 'next' link then a new page will be loaded
    }
    else if ( urlQueueSize() > 0 ) {
        return false;       // Start to emty the queue
    }
    else {
        if ( !navNavigationDone() ) {
            navNextState(); // Go to next state in navigator
            urlLoad( settingGet("DoSearchUrl") );
            return true;
        }
        return false;   // No 'next' link, no new page will be loaded. Miner closes down.  
    }
}

// ----------------------------------
// --- ProductPage (PP) functions ---
// ----------------------------------

function TEMPLATE__ProductPage__mine()            
{
    domNewSearch();
    // Get product name and  product price
    contextBegin("product");
    outputDirect( "product_url" , urlCurrent() );
    outputValueFindNext( 1, "ProductName__ProductPage__FIND"   , "product_name", "eraseAll", ":" );
    outputValueFindNext( 1, "ProductPrice__ProductPage__FIND"  , "product_price", "trimNumber" );
    outputValueFindNext( 1, "ProductColor__ProductPage__FIND"  , "color"  );
    outputValueFindNext( 1, "ProductFabric__ProductPage__FIND" , "fabric" );  
    outputValueFindNext( 1, "ProductBrand__ProductPage__FIND"  , "brand_name" );  
    outputValueFindNext( 1, "ProductId__ProductPage__FIND"     , "product_id" );  
    outputValueFindNext( 1, "ProductSex__ProductPage__FIND"    , "sex" );   // Get value from Navigator attribute by fallback on fail to find dom pos
    outputDirect ( "currency_name" , "EUR" );  
    outputDirect ( "navigator_state", navStateString() );   // Write the navigator state for demo/debug
    contextEnd();
}


function TEMPLATE__ProductPage__navigate()           
{   
    if ( urlQueueSize() > 0 ) {
        return false;   // Process next ProductPage in queue
    }
    else {
        if ( !navNavigationDone() ) {
            navNextState(); // Go to next state in navigator
            urlLoad( settingGet("DoSearchUrl") );
            return true;
        }
    }
    return false;
}

?>

