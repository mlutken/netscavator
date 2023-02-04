<?php
require_once "webminer.php";

// ----------------------------
// --- Global configuration ---
// ----------------------------
function Crawler__outputName                   () { return "ExNavigatorDomClickPos"; }
function Crawler__urlSite     () { return "examples.netscavator.com/sites/ExNavigatorDomClickPos/index.php";       }
function Crawler__urlStart    () { return "examples.netscavator.com/sites/ExNavigatorDomClickPos/dosearch.php";    }

function Crawler__beginMining()         
{
    // Define dom sequences for the positions we need
    domSeqCreate  ( "DoSearchBtn__FIND"    , "INPUT, value, Search"    , "equals"          );
    domSeqCreate  ( "ProductStart__FIND"   , "DIV, class, product"     , "equals"          );
    domSeqCreate  ( "ProductName__FIND"    , ""                        , "equals"          );  // Empty means never find => fallback to navigator attribute
    domSeqCreate  ( "ProductPrice__FIND"   , "EUR"                     , "contains"        );
    
    domSeqCreate  ( "DoClickNext__FIND"    , "Next, /A"                , "contains", -2    );
    // (NOTE: we step back so we are sure to be within the A tag when we 'click' on the link.)

    // Dom sequences to find the start of each of the two readio groups
    domSeqCreate  ( "ClothesSelect__FIND"  , "Select clothes type"  , "contains"   );
    domSeqCreate  ( "FabricSelect__FIND"   , "Select fabric type"   , "contains"   );
    
    domSeqCreate  ( "clothesSelectSub__FIND", "clothes_type, value, #1, type, radio", "contains" );
    domSeqCreate  ( "fabricSelectSub__FIND" , "fabric_type, value, #1, type, radio", "contains" );
    
   
    // Navigator
    navDomPosClickCreate("clothesSelect", "clothesSelectSub__FIND" );
    navAttributeNamesCreate ("product_name, sex");
    navOptionAdd ( "Dresses",   "dress"     , ATTR, "Dress,  F"  	);
    navOptionAdd ( "Ties",      "tie"       , ATTR, "Tie,    M"     );
    navOptionAdd ( "Jackets",   "jacket"    , ATTR, "Jacket, MF" 	);
    navDomPosClickCreate("fabricSelect", "fabricSelectSub__FIND" );
    navAttributeNamesCreate ("fabric");
    navOptionAdd ( "Wool"   ,   "wool"      , ATTR, "Wool"          );
    navOptionAdd ( "Cotton" ,   "cotton"    , ATTR, "Cotton"     	);

    // --- Notes on variations to play around with ---
    // ClothesSelectSeq: This sequence is for finding a position from which each subsequent
    //                   dom position search is started from. Since the 'DomPosClick' action 
    //                   in the navigator starts from the position found by ClothesSelectSeq
    //                   each time it executes the 'find the position' using 
    //                   'clothesSelectSubSeq' with '#1' substituted by : 'dress', 'tie', 'jacket'.
    //                   Since the "clothes_type, value, #1, type, radio" seqences are unique
    //                   to the page we don't actually need a starting position close to the 
    //                   radio buttons. Instead we can simply find fx. the top of the page
    //                   as shown in the two lines commented out specifying the seqences
    //                   'ClothesSelectSeq' and 'FabricSelectSeq'.
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
    doActionFind ( 1, "ClothesSelect__FIND",   "clothesSelect" ); // Select clothes radio button according to current navigator state
    doActionFind ( 1, "FabricSelect__FIND",    "fabricSelect"  ); // Select fabric radio button according to current navigator state
    doActionFind ( 1, "DoSearchBtn__FIND",     "click" );         // Click on search button.
    // TIP: Comment out the search button click action and instead click
    //      manually and see how the navigator cycles through the states.
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
            urlLoad ( "examples.netscavator.com/sites/ExNavigatorDomClickPos/dosearch.php" );  // Back to search page
            return true;
        }
        return false;   // No 'next' link, no new page will be loaded. Miner closes down.  
    }
}


?>

