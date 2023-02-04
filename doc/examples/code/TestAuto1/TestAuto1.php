<?php
require_once "webminer.php";

// ----------------------------
// --- Global configuration ---
// ----------------------------


function Crawler__outputName    () {   return "TestAuto1";       }
function Crawler__urlSite   () {   return "examples.netscavator.com/sites/TestAuto1/";       }
function Crawler__urlStart  () {   return "examples.netscavator.com/sites/TestAuto1/dosearch.php";    }

function Crawler__beginMining()         
{
//    browserSetSize(100,100);
    // --- Dom sequences for the DoSearch (DS) page ---
    domSeqCreate  ( "DoSearchBtn__DoSearch__FIND"    , "INPUT, value, Search"        , "equals"          );
    domSeqCreate  ( "ClothesSelect__DoSearch__FIND"  , "SELECT, name, clothes_type"  , "equals"          );
    domSeqCreate  ( "FabricSelect__DoSearch__FIND"   , "SELECT, name, fabric_type"   , "equals"          );

    // --- Dom sequences for the SearchListing (SL) page ---
    domSeqCreate  ( "ProductStart__SearchListing__FIND"   , "DIV, class, product"         , "equals"          );
    domSeqCreate  ( "ProductUrl__SearchListing__FIND"     , "A, href, productPage.php"    , "contains"        );
    domSeqCreate  ( "DoClickNext__SearchListing__FIND"    , "Next, /A"                    , "contains", -2    );

    // --- Dom sequences for the ProductPage (PP) page ---
    domSeqCreate  ( "ProductName__ProductPage__FIND"    , "TD, Type:, /TD, TD"           , "contains", 1   );  
    domSeqCreate  ( "ProductPrice__ProductPage__FIND"   , "TD, Price:, /TD, TD"          , "contains", 1   );  
    domSeqCreate  ( "ProductColor__ProductPage__FIND"   , "TD, Color:, /TD, TD"          , "contains", 1   );  
    domSeqCreate  ( "ProductFabric__ProductPage__FIND"  , "TD, Fabric, /TD, TD"          , "contains", 1   );  
    domSeqCreate  ( "ProductBrand__ProductPage__FIND"   , "TD, Brand:, /TD, TD"          , "contains", 1   );  
    domSeqCreate  ( "ProductId__ProductPage__FIND"      , "TD, Product ID:, /TD, TD"     , "contains", 1   );  
    domSeqCreate  ( "ProductSex__ProductPage__FIND"     , ""                             , "contains", 0  );  

    
    
    
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

    navStart(); // Important: Start navigator 

    //dbgPrintNavigatorStates(10); // Comment in to print the states. Parameter is specifying how many states to print at most. 

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


    contextBegin("DoSearch_Test_2");
    domFind( 1, "ClothesSelect__DoSearch__FIND" );
    outputDirect ("dompos" , "" . domGetPos() );
    outputDirect ("selectLength" , "" . selectLength() );
    outputDirect ("selectSelectedIndex" , "" . selectSelectedIndex() );
    outputDirect ("selectSelectedDomPos" , "" . selectSelectedDomPos() );
    
    
    contextEnd();
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
    //printf("trimNumber_fn('  25.45  '): '%s'\n", trimNumber_fn('  25.45  ') );
    // All we need to do here is to put the (full) URL of each element in the urlQueue.
    // Since each URL is only relative to the current site we prepend urlSite()
    if ( domFindNext ( 1, "ProductUrl__SearchListing__FIND" ) ) {
        urlQueueAppendUnique( urlSite() . valueGet() );
        //printf("DBG: urlSite() . valueGet(): %s\n", urlSite() . valueGet()  );
    }
}

function Crawler__SearchListing__navigate()           
{   
    if ( domFind ( 1, "DoClickNext__SearchListing__FIND" ) ) {
        nodeClick();
        //nodeClick(NEAREST_AUTO, false);
        return true;    // if we find a 'next' link then a new page will be loaded
    }
    else if ( urlQueueSize() > 0 ) {
        return false;       // Start to emty the queue
    }
    else {
        if ( !navNavigationDone() ) {
            navNextState(); // Go to next state in navigator
            urlLoad ( "examples.netscavator.com/sites/TestAuto1/dosearch.php" );  // Back to search page
            return true;
        }
        //return true;    // Enable this to prevent miner from closing down after scanning.
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
    domNewSearch();
    // Get product name and  product price
    contextBegin("product");
    
    domPointerPush();
    if ( domFindNext( 1, "ProductName__ProductPage__FIND" ) ) {
        outputDirect ( "PRODUCT_NAME_DOM_POS", "" . domGetPos()   );
        outputDirect ( "PRODUCT_NAME_NODE_VAL", nodeValue()   );
        outputDirect ( "PRODUCT_NAME_PARENT_DOM_POS", "" . domFindParentPos(1)   );
        outputDirect ( "PRODUCT_NAME_PARENT_NODE_VAL", nodeValueParent(1)    );
        outputDirect ( "PRODUCT_NAME_PARENT2_DOM_POS", "" . domFindParentPos(2)   );
        outputDirect ( "PRODUCT_NAME_PARENT2_NODE_VAL", nodeValueParent(2)    );
        outputDirect ( "PRODUCT_NAME_PARENT3_DOM_POS", "" . domFindParentPos(3)   );
        outputDirect ( "PRODUCT_NAME_PARENT3_NODE_VAL", nodeValueParent(3)    );
        outputDirect ( "PRODUCT_NAME_PARENT4_DOM_POS", "" . domFindParentPos(4)   );
        outputDirect ( "PRODUCT_NAME_PARENT4_NODE_VAL", nodeValueParent(4)    );
        outputDirect ( "PRODUCT_NAME_PARENT5_DOM_POS", "" . domFindParentPos(5)   );
        outputDirect ( "PRODUCT_NAME_PARENT5_NODE_VAL", nodeValueParent(5)    );
    }
    domPointerPop();
    // --------------------
    
    
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
            urlLoad ( "examples.netscavator.com/sites/TestAuto1/dosearch.php" );  // Back to search page
            return true;
        }
    }
    return false;
}



// --------------
// --- Do run ---
// --------------

//dbgSimpleTestFunction();
initMining();
addMiner( "TestAuto1" );
runMiners();

?>

