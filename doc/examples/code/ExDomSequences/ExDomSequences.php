<?php
require_once "webminer.php";

// ----------------------------
// --- Global configuration ---
// ----------------------------
function Crawler__outputName       () {   return "ExDomSequences";       }

function Crawler__urlSite () {   return "examples.netscavator.com/sites/ExDomSequences";   }

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
    return true;   
}

function Crawler__SearchListing__mine()            
{
    domNewSearch();
    
    // Loop through all products listed, by finding the start of next product
    // and from there find the name and the price
    while ( domFindNext ( 1, "ProductStart__FIND" ) ) {
        contextBegin("product");
        domFindNext ( 1, "ProductName__FIND" );
        outputValue ( "product_name" );
        
        domFindNext ( 1, "ProductPrice__FIND" );
        outputValue ( "product_price" );
        contextEnd();
    }
}

function Crawler__SearchListing__navigate()           
{   
    return false;    
}
