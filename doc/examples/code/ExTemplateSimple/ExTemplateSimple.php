<?php
require_once "ExTemplateSimple.tpl.php";

// ----------------------------
// --- Global configuration ---
// ----------------------------
function Crawler__outputName           () {   return "ExTemplateSimple";       }
function Crawler__urlSite   () {   return "examples.netscavator.com/sites/ExTemplateSimple";   }

function Crawler__beginMining()         
{
    // Define dom sequences for the positions we need
    domSeqCreate  ( "ProductStart__SearchListing__FIND"   	, "DIV, class, product" , "equals"      );
    domSeqCreate  ( "ProductName__SearchListing__FIND"	    , "color:green"         , "contains", 1 );
    domSeqCreate  ( "ProductPrice__SearchListing__FIND"   	, "EUR"                 , "contains"    );
}

// -----------------------
// --- Match functions ---
// -----------------------
function Crawler__SearchListing__match()          
{   
    return true;  // When we only mine a single page simply say that any page is the correct one.
}

?>

