<?php
require_once "webminer.php";

// ----------------------------
// --- Global configuration ---
// ----------------------------
function Crawler__outputName           () {   return "ExSimpleDataMining";       }

function Crawler__urlSite () {   return "examples.netscavator.com/sites/ExSimpleDataMining";   }


// --------------------------------
// --- Search listing functions ---
// --------------------------------
function Crawler__SearchListing__match()          
{   
    return true;    // When we only mine a single page simply say that any page is the correct one.
}

function Crawler__SearchListing__mine()           
{
    domNewSearch();     //Reset current dom position to first node

    // --- product_name ---
    domFindNext ( 1, "color:green", "contains" );
    domStep(1);                     // Goto actual name which is next position
    outputValue("product_name");
    
    // --- product_price ---
    domFindNext( 1, "EUR", "contains");
    outputValue("product_price");
}


function Crawler__SearchListing__navigate()           
{   
    return false;   
}

?>

