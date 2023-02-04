<?php
require_once "webminer.php";

// ----------------------------
// --- Global configuration ---
// ----------------------------
function Crawler__outputName           () {   return "Utf8Test";       }

function Crawler__urlSite () {   return "http://www.bilka.dk/elektronik/film_og_musik/cd/Blues?so=relevans&ps=48&pa=1";   }
function Crawler__urlStart () {   return "http://www.bilka.dk/elektronik/film_og_musik/cd/dansktop/lilholt-lars-stilheden-bag-stoejen--0602537110001(purchase_movie_cd)";   }



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

