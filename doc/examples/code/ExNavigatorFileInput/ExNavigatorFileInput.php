<?php
require_once "webminer.php";

// ----------------------------
// --- Global configuration ---
// ----------------------------
function Crawler__outputName               () { return "ExNavigatorFileInput"; }
function Crawler__urlSite   () { return "examples.netscavator.com/sites/ExNavigatorFileInput/index.php";       }
function Crawler__urlStart  () { return "examples.netscavator.com/sites/ExNavigatorFileInput/dosearch.php";    }

function Crawler__beginMining()         
{
    // Define dom sequences for the positions we need
    domSeqCreate  ( "DoSearchBtn__FIND"    , "INPUT, value, Search"        , "equals"          );
    domSeqCreate  ( "ProductStart__FIND"   , "DIV, class, product"         , "equals"          );
    domSeqCreate  ( "ProductName__FIND"    , "color:green"                 , "contains", 1     );
    domSeqCreate  ( "FabricType__FIND"     , "color:black"                 , "contains", 1     );
    domSeqCreate  ( "ProductPrice__FIND"   , "EUR"                         , "contains"        );
    
    domSeqCreate  ( "DoClickNext__FIND"    , "Next, /A"                    , "contains", -2    );
    // (NOTE: we step back so we are sure to be within the A tag when we 'click' on the link.)

    domSeqCreate  ( "ClothesSelect__FIND"  , "INPUT, name, clothes_type"  , "equals"          );
    
    // Navigator
    navInputOptionsCreate( "clothesSelect" );
    navOptionResourceAdd( "http://examples.netscavator.com/sites/ExNavigatorFileInput/clothes_types.txt", "", true );
    //navOptionResourceAdd( "http://examples.netscavator.com/sites/ExNavigatorFileInput/clothes_types.txt.gz", "", true );
    // NOTE: You need to prepend 'http://' if your resource file is somewhere 'online'. If you don't
    //       the miner assumes the file is on the local filesystem. This will be fixed in a 
    //       future release so that if the path without 'http://' is not found on the local filesystem 
    //       then we try again online with 'http://' prepended.
}

function filterFabricType($val)
{
    $val = eraseAll_fn($val, "(" );
    $val = eraseAll_fn($val, ")" );
    return $val;
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
    doActionFind ( 1, "ClothesSelect__FIND",   "clothesSelect" ); // Select clothes drop down according to current navigator state
    doActionFind ( 1, "DoSearchBtn__FIND",     "click" );         // Click on search button.
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
    outputValueFindNext( 1, "ProductName__FIND", "product_name", "eraseAll", ":" );
    outputValueFindNext( 1, "ProductPrice__FIND", "product_price", "trimNumber" );
    outputValueFindNext( 1, "FabricType__FIND", "fabric", "filterFabricType" );
    outputValueFindNext( 1, "", "sex" );   // Oups: This fails, but see ExNavigatorFileInputFilter example for a solution
    outputDirect ( "currency_name" , "EUR" );  
    outputDirect ( "navigator_state", navStateString() );   // Write the navigator state for demo/debug
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
            urlLoad ( "examples.netscavator.com/sites/ExNavigatorFileInput/dosearch.php" );  // Back to search page
            return true;
        }
        return false;   // No 'next' link, no new page will be loaded. Miner closes down.  
    }
}

?>

