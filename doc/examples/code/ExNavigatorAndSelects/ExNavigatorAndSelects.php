<?php
require_once "webminer.php";
 
// ----------------------------
// --- Global configuration ---
// ---------------------------- 
function Crawler___outputName() { return "ExNavigatorAndSelects";  }
function Crawler__urlSite   	() { return "examples.netscavator.com/sites/ExNavigatorAndSelects/index.php";       }
function Crawler__urlStart  	() { return "examples.netscavator.com/sites/ExNavigatorAndSelects/dosearch.php";    }


function Crawler__beginMining()         
{
   // Define dom sequences for the positions we need
    domSeqCreate  ( "DoSearchBtn__FIND"    , "INPUT, value, Search"   , "equals"   );
    domSeqCreate  ( "ProductStart__FIND"   , "DIV, class, product"    , "equals"   );
    domSeqCreate  ( "ProductName__FIND"    , ""                       , "equals"   ); // Empty means never find => fallback to navigator attribute   
    domSeqCreate  ( "ProductPrice__FIND"   , "EUR"                    , "contains" );
    
    domSeqCreate  ( "DoClickNext__FIND"    , "Next, /A"                , "contains", -2    );
    // (NOTE: we step back so we are sure to be within the A tag when we 'click' on the link.)

    domSeqCreate  ( "ClothesSelect__FIND"  	, "SELECT, name, clothes_type"  , "equals" 	);
    domSeqCreate  ( "FabricSelect__FIND"   	, "SELECT, name, fabric_type"   	, "equals"     );
        
    
    // Navigator
    navDropDownSelectCreate("clothesSelect");
    navAttributeNamesCreate ("product_name, sex");
    navOptionAdd ( 1,  "dresses"        	, ATTR, "Dress,  F"  	);
    navOptionAdd ( 2,  "ties"           	, ATTR, "Tie,    M"  	);
    navOptionAdd ( 3,  "jackets"        	, ATTR, "Jacket, MF" 	);
    navDropDownSelectCreate("fabricSelect");
    navAttributeNamesCreate ("fabric");
    navOptionAdd ( 1,  "wool"           	, ATTR, "Wool"       	);
    navOptionAdd ( 2,  "cotton"         	, ATTR, "Cotton"     	);
    //dbgPrintNavigatorStates(10); // Comment in to print the states. Parameter is specifying how many states to print at most. 

    // --- Notes on variations to play around with ---
    // ProductNameSeq: If you use the first one (same as example 3) we get the product name from the actual 
    //                 page we are mining which in these pages are with lowercase starting letter.
    //                 If you use the other version ("" - empty-string) the domFindNext part of the 
    //                 outputValueFindNext( 1, "ProductName__FIND", "product_name", "eraseAll", ":" ); will 
    //                 never find the sequence since the string empty-string are not present on the 
    //                 webpage. This results in the outputValue part of the outputValueFindNext function 
    //                 to look elswhere for a value for the 'product_name' which it is trying to write to the 
    //                 output. Since the navigator has an attribute defined called 'product_name' it then 
    //                 uses the current value of that attribute to write to the output. Since this attribute 
    //                 value changes along with the navigator changing states we now get the product names
    //                 with uppercase starting letters as we wrote them in the attributes for each option 
    //                 in the 'clothesSelect' of the navigator. 
    //                 See also in GetProduct() function : outputValueFindNext( 1, "", "sex" );
    //                 
}

function Crawler__DoSearch_beginMining()          
{   
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
    doActionFind ( 1, "FabricSelect__FIND",    "fabricSelect"  ); // Select fabric drop down according to current navigator state
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
	domLoopAll("ProductStart__FIND", "Loop__SearchListing__GetProduct" );
}

function Loop__SearchListing__GetProduct()            
{
   // Get product name and  product price
    contextBegin("product");
    outputValueFind( 1, "ProductName__FIND", "product_name", "eraseAll", ":" ); // Get value from Navigator attribute by fallback on fail to find dom pos
    outputValueFind( 1, "ProductPrice__FIND", "product_price", "trimNumber" );
    outputValueFind( 1, "", "sex" );   // Get value from Navigator attribute by fallback on fail to find dom pos
    outputDirect ( "fabric" , navAttributeGet("fabric") );  // Gettting the attribute value directly  
    outputDirect ( "currency_name" , "EUR" );  
    outputDirect ( "navigator_state", navStateString() );   // Write the navigator state for demo/debug
    outputDirect ( "nav_state_indices", navCurrentStateIndicesGet() );   // Write the navigator state indices for demo/debug
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
            urlLoad ( "examples.netscavator.com/sites/ExNavigatorAndSelects/dosearch.php" );  // Back to search page
            return true;
        }
        return false;   // No 'next' link, no new page will be loaded. Miner closes down.  
    }
}

?>

