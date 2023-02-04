<?php
require_once "webminer.php";

// ----------------------------
// --- Global configuration ---
// ----------------------------
function Crawler__outputName           () {   return "ExFallBackValues";       }
function Crawler__urlSite   () {   return "examples.netscavator.com/sites/ExFallBackValues/";       }
function Crawler__urlStart  () {   return "examples.netscavator.com/sites/ExFallBackValues/dosearch.php";    }

function Crawler__beginMining()         
{
    // --- Dom sequences for the DoSearch (DS) page ---
    domSeqCreate  ( "DoSearchBtn__DoSearch__FIND"    , "INPUT, value, Search"        , "equals"          );
    domSeqCreate  ( "ClothesSelect__DoSearch__FIND"  , "SELECT, name, clothes_type"  , "equals"          );
    domSeqCreate  ( "FabricSelect__DoSearch__FIND"   , "SELECT, name, fabric_type"   , "equals"          );

    // --- Dom sequences for the SearchListing (SL) page ---
    domSeqCreate  ( "ProductStart__SearchListing__FIND"   , "DIV, class, product"         , "equals"          );
    domSeqCreate  ( "ProductUrl__SearchListing__FIND"     , "A, href, productPage.php"    , "contains"        );
    domSeqCreate  ( "ProductName__SearchListing__FIND"    , ""                            , "equals"          );  
    domSeqCreate  ( "ProductPrice__SearchListing__FIND"   , "EUR"                         , "contains"        );
    domSeqCreate  ( "DoClickNext__SearchListing__FIND"    , "Next, /A"                    , "contains", -2    );

    // --- Dom sequences for the ProductPage (PP) page ---
//     domSeqCreate  ( "ProductName__ProductPage__FIND"    , "TD, Type:, /TD, TD"           , "contains", 1   );  // Fallback since not defined/found
//     domSeqCreate  ( "ProductPrice__ProductPage__FIND"   , "TD, Price:, /TD, TD"          , "contains", 1   );  // Fallback since not defined/found
    domSeqCreate  ( "ProductColor__ProductPage__FIND"   , "TD, Color:, /TD, TD"          , "contains", 1   );  
    domSeqCreate  ( "ProductFabric__ProductPage__FIND"  , "TD, Fabric, /TD, TD"          , "contains", 1   );  
    domSeqCreate  ( "ProductBrand__ProductPage__FIND"   , "TD, Brand:, /TD, TD"          , "contains", 1   );  
    domSeqCreate  ( "ProductId__ProductPage__FIND"      , "TD, Product ID:, /TD, TD"     , "contains", 1   );  
//    domSeqCreate  ( "ProductSex__ProductPage__FIND"     , ""                             , "contains"  );  // Fallback since not defined/found
    
    
    // Navigator
    navDropDownSelectCreate("clothesSelect");
    navAttributeNamesCreate ("product_name, sex");
    navOptionAdd ( 1,  "dresses"        , ATTR, "Dress,  F"  );
    navOptionAdd ( 2,  "ties"           , ATTR, "Tie,    M"  );
    navOptionAdd ( 3,  "jackets"        , ATTR, "Jacket, MF" );
    navDropDownSelectCreate("fabricSelect");
    navAttributeNamesCreate ("fabric");
    navOptionAdd ( 1,  "wool"           , ATTR, "Wool"       );
    navOptionAdd ( 2,  "cotton"         , ATTR, "Cotton"     );
}


// ------------------------------------
// --- DoSearch (DS) page functions ---
// ------------------------------------
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
    doActionFind ( 1, "ClothesSelect__DoSearch__FIND",   "clothesSelect" ); // Select clothes drop down according to current navigator state
    doActionFind ( 1, "FabricSelect__DoSearch__FIND",    "fabricSelect"  ); // Select fabric drop down according to current navigator state
    doActionFind ( 1, "DoSearchBtn__DoSearch__FIND",     "click" );         // Click on search button.
    return true;  // Return 'true' since the navigation results in loading of a new page.
}


// -------------------------------------
// --- Search listing (SL) functions ---
// -------------------------------------
function Crawler__SearchListing__match()          
{   
    return contains_fn( urlCurrent() , "searchlisting" );  // Handle any page with 'searchlisting' in the URL.
}

function Crawler__SearchListing__mine()            
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
    // Get product details from search listing page
    configOutputWriteToFile(false); // Don't write to output, since we write on the product page
    contextBegin("product");
    outputValueFindNext( 1, "ProductUrl__SearchListing__FIND", "product_url", "prepend", "http://examples.netscavator.com/sites/ExFallBackValues/");
    outputValueFindNext( 1, "ProductName__SearchListing__FIND", "product_name", "eraseAll", ":" );
    outputValueFindNext( 1, "ProductPrice__SearchListing__FIND", "product_price", "trimNumber" );
    outputValueFindNext( 1, "", "sex" );   // Get value from Navigator attribute by fallback on fail to find dom pos
    outputDirect ( "fabric" , navAttributeGet("fabric") );  // Gettting the attribute value directly  
    outputDirect ( "currency_name" , "EUR" );  
    outputDirect ( "navigator_state", navStateString() );   // Write the navigator state for demo/debug

    urlQueueAppendUnique( outputValueGet('product_url') );  // Add product page URL to url-queue
    contextOutputSaveAs ( outputValueGet('product_url') );  // Save output using ID product_url
    contextEnd();
    configOutputWriteToFile(true); // Enable writing to file again
}

function Crawler__SearchListing__navigate()           
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
            urlLoad ( "examples.netscavator.com/sites/ExFallBackValues/dosearch.php" );  // Back to search page
            return true;
        }
        return false;   // No 'next' link, no new page will be loaded. Miner closes down.  
    }
}


// ----------------------------------
// --- ProductPage (PP) functions ---
// ----------------------------------
function Crawler__ProductPage__match()          
{   
    return contains_fn( urlCurrent() , "productPage.php" );  // Handle any page with 'productPage.php' in the URL.
}

function Crawler__ProductPage__mine()            
{
    contextFallbackOutputLoad( urlCurrent() );  // Load fallback values written on the search listing page
    domNewSearch();
    // Get more product details from produc page page
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


function Crawler__ProductPage__navigate()           
{   
    if ( urlQueueSize() > 0 ) {
        return false;   // Process next ProductPage in queue
    }
    else {
        if ( !navNavigationDone() ) {
            navNextState(); // Go to next state in navigator
            urlLoad ( "examples.netscavator.com/sites/ExFallBackValues/dosearch.php" );  // Back to search page
            return true;
        }
    }
    return false;
}

?>

