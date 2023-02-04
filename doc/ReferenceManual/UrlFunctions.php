<?php
// --- Common function properties ---
$f_common = array();
$f_common["type"]      = "function";
$f_common["group"]     = "URL functions";


$f = array();
$f["name"] =
// **************************
       "URL functions";
// **************************

$f["type"]      = "group";
$f["desc"]      = <<<TEXT
URL related functions. For example urlLoad to load a new page in the browser.
TEXT;
$f["seealso"]   = "urlLoad, all-functions, all-function-groups";
$a[] = $f;

$f = $f_common;
$f["name"] =
// ********************
       "urlSite";
// ********************
$f["syntax"][]  = <<<TEXT
string urlSite();
TEXT;
$f["params"][]    = array ( "string", "RETURN", "The URL of the current site." );

$f["desc"]      = <<<TEXT
Get URL of the current site.
TEXT;

$f["seealso"]       = "urlCurrent";

$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;

$f = $f_common;
$f["name"] =
// ********************
       "urlCurrent";
// ********************
$f["syntax"][]  = <<<TEXT
string urlCurrent();
TEXT;
$f["params"][]    = array ( "string", "RETURN", "The URL of the current browser page." );

$f["desc"]      = <<<TEXT
Get the URL of the current browser page.
TEXT;

$f["seealso"]       = "urlSite";

$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;

$f = $f_common;
$f["name"] =
// ********************
       "urlLoad";
// ********************
$f["syntax"][]  = <<<TEXT
bool urlLoad ( string sURL );
TEXT;
$f["params"][]    = array ( "string", "sURL", "URL to load." );
$f["params"][]    = array ( "string", "RETURN", "True if load could be initiated successfully." );

$f["desc"]      = <<<TEXT
Load new page in browser. The page load is only initiated here as the next line in your script will 
be executed right after this statement. Later you will have a new "page loaded", which again triggers 
the selection of handlers process as usual.
If you really want the script execution to wait at this point until the page is completely loaded use 
urlLoadWait.
TEXT;

$f["seealso"]       = "urlLoadWait";

$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "urlLoadWait";
// ********************
$f["syntax"][]  = <<<TEXT
bool urlLoadWait ( string sURL );
TEXT;
$f["params"][]    = array ( "string", "sURL", "URL to load." );
$f["params"][]    = array ( "string", "RETURN", "True if load could be initiated successfully." );

$f["desc"]      = <<<TEXT
TODO: NOT IMPLEMENTED YET. 
Load new page in browser. The the next line in your script will NOT be executed until the entire page 
is loaded. The normal "page loaded" actions like the selection of handlers and calling _mine and 
_navigate steps are circumvented in this case. 
TEXT;

$f["seealso"]       = "urlLoad";

$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;

?>
