<?php

// --- Common function properties ---
$f_common = array();
$f_common["type"]      = "function";
$f_common["group"]     = "Settings functions";


$f = array();
$f["name"] =
// **************************
       "Settings functions";
// **************************

$f["type"]      = "group";
$f["desc"]      = <<<TEXT
Functions for setting and getting user defined values. Like global PHP variables, but a setting variable also 
works as the last resort fallback value, when writing output with outputValue, outputValueFind, etc. 
TEXT;
$f["seealso"]   = "all-functions, all-function-groups";
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "settingDelete";
// ********************
$f["syntax"][]  = <<<TEXT
void settingDelete ( string sName );
TEXT;
$f["params"][]    = array ( "string", "sName", "Name of setting to delete." );

$f["desc"]      = <<<TEXT
Delete a setting value.
TEXT;
$f["seealso"]       = "settingSet, settingGet, settingExists";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "settingSet";
// ********************
$f["syntax"][]  = <<<TEXT
void settingSet ( string sName, string sValue );
TEXT;
$f["params"][]    = array ( "string", "sName", "Name of new setting." );
$f["params"][]    = array ( "string", "sValue", "Value to assign." );

$f["desc"]      = <<<TEXT
Delete a setting value.
TEXT;
$f["seealso"]       = "settingDelete, settingGet, settingExists";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "settingGet";
// ********************
$f["syntax"][]  = <<<TEXT
string settingGet ( string sName );
TEXT;
$f["params"][]    = array ( "string", "sName", "Name of setting to get value for." );

$f["desc"]      = <<<TEXT
Get setting value.
TEXT;
$f["seealso"]       = "settingSet, settingDelete, settingExists";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "settingDelete";
// ********************
$f["syntax"][]  = <<<TEXT
bool settingExists ( string sName ) ;
TEXT;
$f["params"][]    = array ( "string", "sName", "Name of setting to delete." );
$f["params"][]    = array ( "bool", "RETURN", "True if setting exists." );

$f["desc"]      = <<<TEXT
Delete a setting value.
TEXT;
$f["seealso"]       = "settingSet, settingGet, settingExists";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;

?>

