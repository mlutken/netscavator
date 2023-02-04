<?php
// --- Common function properties ---
$f_common = array();
$f_common["type"]      = "function";
$f_common["group"]     = "Browser functions";


$f = array();
$f["name"] =
// **************************
       "Browser functions";
// **************************

$f["type"]      = "group";
$f["desc"]      = <<<TEXT
The browser functions are a collection of simple functions used to do 
very basic things with the Sleipner web browser. For example setting 
the browser window size or navigating to the previous page using
browserGoBack. For loading a new page see urlLoad in url-functions. 
TEXT;
$f["functions"]  = array();
$f["seealso"]   = "urlLoad, all-functions, all-function-groups";
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "browserHide";
// ********************
$f["syntax"][]  = <<<TEXT
void browserHide();
TEXT;
$f["params"]    = null;

$f["desc"]      = <<<TEXT
Hides the browser window so it is not visible on screen. Use browserShow 
to show it again. By default the browser window is visible.
TEXT;

$f["seealso"]       = "browserShow, browserSetSize";

$f["examples"][]    = <<<TEXT
function MyScript_beginMining()
{
     browserHide();  // Default is visible
      ...
}
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "browserShow";
// ********************
$f["syntax"][]  = <<<TEXT
void browserShow();
TEXT;
$f["params"]    = null;

$f["desc"]      = <<<TEXT
Shows the browser window if previously hidden from a browserHide call.
TEXT;

$f["seealso"]       = "browserHide, browserSetSize";

$f["examples"][]    = <<<TEXT
function MyScript_beginMining()
{
     browserShow();  // Default is visible
      ...
}
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "browserSetSize";
// ********************
$f["syntax"][]  = <<<TEXT
void browserSetSize ( int x, int y );
TEXT;
$f["params"][]    = array ( "int", "x", "Width of browser window in pixels." );
$f["params"][]    = array ( "int", "y", "Height of browser window in pixels." );
$f["params"][]    = array ( "void", "RETURN", "" );

$f["desc"]      = <<<TEXT
Sets the width and height of the browser window.
TEXT;

$f["seealso"]       = "browserGetSizeX, browserGetSizeY";

$f["examples"][]    = <<<TEXT
function MyScript_beginMining()
{
     browserSetSize (1000, 500);
     ...
}
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "browserGetSizeX";
// ********************
$f["syntax"][]  = <<<TEXT
int browserGetSizeX ();
TEXT;
$f["params"][]    = array ( "int", "RETURN", "The browser window width in pixels." );

$f["desc"]      = <<<TEXT
Gets the width of the browser window in pixels.
TEXT;

$f["seealso"]       = "browserGetSizeY, browserSetSize";

$f["examples"][]    = <<<TEXT
function MyScript_beginMining()
{
     \$width = browserGetSizeX ();
     ...
}
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "browserGetSizeY";
// ********************
$f["syntax"][]  = <<<TEXT
int browserGetSizeY ();
TEXT;
$f["params"][]    = array ( "int", "RETURN", "The browser window's height in pixels." );

$f["desc"]      = <<<TEXT
Gets the height of the browser window in pixels.
TEXT;

$f["seealso"]       = "browserGetSizeX, browserSetSize";

$f["examples"][]    = <<<TEXT
function MyScript_beginMining()
{
     \$height = browserGetSizeY ();
     ...
}
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "browserGoBack";
// ********************
$f["syntax"][]  = <<<TEXT
bool browserGoBack ();
TEXT;
$f["params"][]    = array ( "bool", "RETURN", "True if the browser was able to navigate one page back." );

$f["desc"]      = <<<TEXT
Navigates back to the previously loaded page.
TEXT;

$f["seealso"]       = "Navigation functions";

$f["examples"][]    = <<<TEXT
function MyScript__ProductPage_navigate()
{
     ...
     browserGoBack();
}
TEXT;
$a[] = $f;

?>
