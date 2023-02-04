<?php
require_once "ExTemplateProductPage.tpl.php";

// ----------------------------
// --- Global configuration ---
// ----------------------------

function Crawler__outputName                () { return "ExTemplateProductPage";       }
function Crawler__urlSite   () { return "examples.netscavator.com/sites/ExTemplateProductPage/";       }
function Crawler__urlStart  () { return "examples.netscavator.com/sites/ExTemplateProductPage/dosearch.php";    }

function Crawler__beginMining()         
{
    settingSet    ( "DoSearchUrl", "examples.netscavator.com/sites/ExTemplateProductPage/dosearch.php" ); 

    // --- Dom sequences for the DoSearch (DS) page ---
    domSeqCreate  ( "DoSearchBtn__DoSearch__FIND"    , "INPUT, value, Search"        , "equals"          );
    domSeqCreate  ( "ClothesSelect__DoSearch__FIND"  , "SELECT, name, clothes_type"  , "equals"          );
    domSeqCreate  ( "FabricSelect__DoSearch__FIND"   , "SELECT, name, fabric_type"   , "equals"          );

    // --- Dom sequences for the SearchListing (SL) page ---
    domSeqCreate  ( "ProductStart__SearchListing__FIND"   , "DIV, class, product"         , "equals"          );
    domSeqCreate  ( "ProductUrl__SearchListing__FIND"     , "A, href, productPage.php"    , "contains"        );
    domSeqCreate  ( "DoClickNext__SearchListing__FIND"    , "Next, /A"                    , "contains", -2    );

    // --- Dom sequences for the ProductPage (PP) page ---
    domSeqCreate  ( "ProductName__ProductPage__FIND"    , "TD, Type:, /TD, TD"           , "contains", 1   );  
    domSeqCreate  ( "ProductPrice__ProductPage__FIND"   , "TD, Price:, /TD, TD"          , "contains", 1   );  
    domSeqCreate  ( "ProductColor__ProductPage__FIND"   , "TD, Color:, /TD, TD"          , "contains", 1   );  
    domSeqCreate  ( "ProductFabric__ProductPage__FIND"  , "TD, Fabric, /TD, TD"          , "contains", 1   );  
    domSeqCreate  ( "ProductBrand__ProductPage__FIND"   , "TD, Brand:, /TD, TD"          , "contains", 1   );  
    domSeqCreate  ( "ProductId__ProductPage__FIND"      , "TD, Product ID:, /TD, TD"     , "contains", 1   );  
    domSeqCreate  ( "ProductSex__ProductPage__FIND"     , ""                             , "contains"  );  
    
    // Navigator
    navDropDownSelectCreate("clothesSelect");
    navAttributeNamesCreate ("product_name, sex");
    navOptionAdd ( 1,  "dresses"        , ATTR, "Dress,  F"  );
    navOptionAdd ( 2,  "ties"           , ATTR, "Tie,    M"  );
    navOptionAdd ( 3,  "jackets"        , ATTR, "Jacket, MF" );
    navDropDownSelectCreate("fabricSelect");
    navAttributeNamesCreate ("fabric");
    navOptionAdd ( 1,  "wool"           , ATTR, "Wool"       );
    navOptionAdd ( 2,  "cotton"         , ATTR, "Cotton"     );
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

function Crawler__ProductPage__match()          
{   
    return contains_fn( urlCurrent() , "productPage.php" );  // Handle any page with 'productPage.php' in the URL.
}


?>

