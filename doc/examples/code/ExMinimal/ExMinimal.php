<?php
require_once "webminer.php";

// ----------------------------
// --- Global configuration ---
// ----------------------------

function Crawler__outputName   () {   return "ExMinimal";       }

function Crawler__urlSite  () {   return "examples.netscavator.com/sites/ExMinimal";   }

// ----------------------------------
// --- DoSearch handler functions ---
// ----------------------------------
function Crawler__DoSearch__match()          
{   
    return true;    // When we only mine a single page, simply say that any page matches.
}

function Crawler__DoSearch__mine()           
{
    printf("Crawler__DoSearch__mine()\n");
    outputDirect("item_name", "item_value");
}

function Crawler__DoSearch__navigate()           
{   
    printf("Crawler__DoSearch__navigate()\n");
    return false;    
}

?>

