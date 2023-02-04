<?php

// --- Common function properties ---
$f_common = array();
$f_common["type"]      = "function";
$f_common["group"]     = "Javascript functions";


$f = array();
$f["name"] =
// **************************
       "Javascript functions";
// **************************

$f["type"]      = "group";
$f["desc"]      = <<<TEXT
Functions for (optionally creating and) calling javascript functions. 
TEXT;
$f["seealso"]   = "all-functions, all-function-groups";
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "javaScriptExecuteRetVal";
// ********************
$f["syntax"][]  = <<<TEXT
bool javaScriptExecuteRetVal ( string sScript, string sScriptReturnValue );
TEXT;
$f["params"][]    = array ( "string", "sScript", "Script to execute." );
$f["params"][]    = array ( "string", "sScriptReturnValue", "Variable to receive the return value from the javascript." );
$f["params"][]    = array ( "string", "RETURN", "True if javascript was excuted successfully." );

$f["desc"]      = <<<TEXT
Execute a javascript and get the return value.
TEXT;
$f["seealso"]       = "javaScriptExecute";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "javaScriptExecute";
// ********************
$f["syntax"][]  = <<<TEXT
bool javaScriptExecute ( string sScript );
TEXT;
$f["params"][]    = array ( "string", "sScript", "Script to execute." );
$f["params"][]    = array ( "string", "RETURN", "True if javascript was excuted successfully." );

$f["desc"]      = <<<TEXT
Execute a javascript.
TEXT;
$f["seealso"]       = "javaScriptExecuteRetVal";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


?>

