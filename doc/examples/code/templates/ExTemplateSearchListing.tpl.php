<?php
require_once "webminer.php";


function TEMPLATE__DoSearch__navigate()           
{   
    doActionFind ( 1, "ClothesSelect__DoSearch__FIND",   "clothesSelect" ); // Select clothes drop down according to current navigator state
    doActionFind ( 1, "FabricSelect__DoSearch__FIND",    "fabricSelect"  ); // Select fabric drop down according to current navigator state
    doActionFind ( 1, "DoSearchBtn__DoSearch__FIND",     "click" );         // Click on search button.
    return true;  // Return 'true' since the navigation results in loading of a new page.
}


// --------------------------------
// --- Search listing functions ---
// --------------------------------
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
        GetProduct();
        domClearStopPos();
        domPointerPop();
    }
}

function GetProduct()            
{
    // Get product name and  product price
    contextBegin("product");
    outputValueFindNext( 1, "ProductName__SearchListing__FIND", "product_name", "eraseAll", ":" );
    outputValueFindNext( 1, "ProductPrice__SearchListing__FIND", "product_price", "trimNumber" );
    outputValueFindNext( 1, "", "sex" );   // Get value from Navigator attribute by fallback on fail to find dom pos
    outputDirect ( "fabric" , navAttributeGet("fabric") );  // Gettting the attribute value directly  
    outputDirect ( "currency_name" , "EUR" );  
    outputDirect ( "navigator_state", navStateString() );   // Write the navigator state for demo/debug
    outputDirect ( "dbg_state_progress", (string)navNumStatesGet() . " / " . navStateIndexGet() ); 
    contextEnd();
}

function TEMPLATE__SearchListing__navigate()           
{   
    if ( domFind ( 1, "DoClickNext__FIND" ) ) {
        nodeClick();
        return true;    // if we find a 'next' link then a new page will be loaded
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

?>

