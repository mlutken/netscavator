<?php
require_once "webminer.php";

// ----------------------------
// --- Global configuration ---
// ----------------------------
function Crawler__outputName           () {   return "ExOutputTrimming";       }

function Crawler__urlSite   () {   return "examples.netscavator.com/sites/ExOutputTrimming";   }

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



function Crawler__SearchListing__mine()            
{
    domNewSearch();
    
    // Loop through all products listed, by finding the start of next product
    // and from there find the name and the price. We save the position right after
    // finding a product start and restores it after mining the product data.
    // That way we are sure we get the start of each product correctly even if 
    // some of the product data related domFindNext() calls does not succeed 
    // in finding the name or the price, which would leave us at the very end of the page!
    // The saving and restoring of the dom position ensures that failing to 
    // find the the name or price of one product does not affect the others.
    // We also added IF's to the domFindNext() calls locating name and price, making  
    // sure that we only output the data if we actually succeeeded in finding it.
    while ( domFindNext ( 1, "ProductStart__FIND" ) ) {
        $savePos = domGetPos(); // Save dom position
        contextBegin("product");
        if ( domFindNext ( 1, "ProductName__FIND" ) ) {
            outputValue ( "product_name", "eraseAll", ":" );
        }

        if ( domFindNext ( 1, "ProductPrice__FIND" ) ) {
            outputValue ( "product_price", "trimNumber" );
        }
        contextEnd();
        domSetPos($savePos);    // Restore position so we are ready to find next product start
    }
}

function Crawler__SearchListing__navigate()           
{   
    return false;   
}

?>

