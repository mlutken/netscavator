<?php
require_once "webminer.php";


// Completely general way way of looping through a list of products
function TEMPLATE__SearchListing__mine()            
{
    domNewSearch();
    while ( domFindNext ( 1, "ProductStart__SearchListing__FIND" ) ) {
        $savePos = domGetPos(); // Save dom position
        $iStopPos = domFindNextPos( 1, "ProductStart__SearchListing__FIND" );
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
    outputValueFindNext( 1, "ProductName__SearchListing__FIND", "product_name", "eraseAll", ":" );
    outputValueFindNext( 1, "ProductPrice__SearchListing__FIND", "product_price", "trimNumber" );
    outputDirect ( "currency_name" , "EUR" );  
    contextEnd();
}

function TEMPLATE__SearchListing__navigate()           
{   
    return false;   
}

?>

