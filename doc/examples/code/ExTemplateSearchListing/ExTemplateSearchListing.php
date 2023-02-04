<?php
require_once "ExTemplateSearchListing.tpl.php";

// ----------------------------
// --- Global configuration ---
// ---------------------------- 
function Crawler__outputName                   () { return "ExTemplateSearchListing";       }
function Crawler__urlSite  	() { return "examples.netscavator.com/sites/ExTemplateSearchListing/index.php";       }
function Crawler__urlStart   () { return "examples.netscavator.com/sites/ExTemplateSearchListing/dosearch.php";    }

function Crawler__beginMining()         
{
    // Required: Set to URL of search page as the TEMPLATE__SearchListing__navigate() function needs it.
    settingSet    ( "DoSearchUrl", "examples.netscavator.com/sites/ExTemplateSearchListing/dosearch.php" ); 
    
    // Define dom sequences for the positions we need
    domSeqCreate  ( "DoSearchBtn__DoSearch__FIND"    , "INPUT, value, Search"    , "equals"       );
    domSeqCreate  ( "ProductStart__SearchListing__FIND"   , "DIV, class, product"     , "equals"       );
    domSeqCreate  ( "ProductName__SearchListing__FIND"    , ""                        , "equals"       );  // Empty => fallback to nav attribute
    domSeqCreate  ( "ProductPrice__SearchListing__FIND"   , "EUR"                     , "contains"     );
    domSeqCreate  ( "DoClickNext__SearchListing__FIND"    , "Next, /A"                , "contains", -2 );
    // (NOTE: we step back so we are sure to be within the A tag when we 'click' on the link.)

    domSeqCreate  ( "ClothesSelect__DoSearch__FIND"  	, "SELECT, name, clothes_type"  , "equals"  );
    domSeqCreate  ( "FabricSelect__DoSearch__FIND"   	, "SELECT, name, fabric_type"   , "equals"  );
     
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
}


// -----------------------
// --- Match functions ---
// -----------------------
function Crawler__DoSearch__match()          
{   
    return contains_fn( urlCurrent() , "dosearch.php" );  // Handle do search page.
}

function Crawler__SearchListing__match()          
{   
    return contains_fn( urlCurrent() , "searchlisting" );  // Handle any page with 'searchlisting' in the URL.
}


?>

