<?php
require_once "webminer.php";

// ----------------------------
// --- Global configuration ---
// ----------------------------
function Crawler__outputName           () {   return "ExTypicalDataMining";       }
function Crawler__urlSite() {   return "examples.netscavator.com/sites/ExTypicalDataMining";   }

function Crawler__beginMining()         
{
    // Define dom sequences for the positions we need
    domSeqCreate  ( "ProductStart__FIND"   , "DIV, class, product" , "equals"      );
    domSeqCreate  ( "ProductName__FIND"    , "color:green"         , "contains", 1 );
    domSeqCreate  ( "ProductPrice__FIND"   , "EUR"                 , "contains"    );
}

// --------------------------------
// --- Search listing functions ---
// --------------------------------
function Crawler__SearchListing__match()          
{   
    return true;  // When we only mine a single page simply say that any page is the correct one.
}

// Completely general/reuseable way of looping through a list of products
function Crawler__SearchListing__mine()            
{
    domNewSearch();
    while ( domFindNext ( 1, "ProductStart__FIND" ) ) {
        $savePos = domGetPos(); // Save dom position
        $iStopPos = domFindNextPos( 1, "ProductStart__FIND" );
        domSetStopPos( $iStopPos ); // Set stop position to start of next product block
        GetProduct();
        domClearStopPos();
        domSetPos($savePos);    // Restore position so we are ready to find next product start
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
    return false;   
}

?>

