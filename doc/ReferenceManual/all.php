NOT USED !!!!!

----------------------
--- Misc functions ---
----------------------

<?php
// --- Common function properties ---
$f_common = array();
$f_common["type"]      = "function";
$f_common["group"]     = "Misc functions";


$f = array();
$f["name"] =
// **************************
       "Misc functions";
// **************************

$f["type"]      = "group";
$f["desc"]      = <<<TEXT
Miscelaneous functions.
TEXT;
$f["seealso"]   = "";
$a[] = $f;

$f = $f_common;
$f["name"] =
// ********************
       "currentMiner";
// ********************
$f["syntax"][]  = <<<TEXT
string currentMiner();
TEXT;
$f["params"][]    = array ( "string", "RETURN", "The name of the current miner." );

$f["desc"]      = <<<TEXT
Get the name of the current miner.
TEXT;

$f["seealso"]       = "currentDataFile";

$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;

$f = $f_common;
$f["name"] =
// ********************
       "currentDataFile";
// ********************
$f["syntax"][]  = <<<TEXT
string currentDataFile();
TEXT;
$f["params"][]    = array ( "string", "RETURN", "The name of the current data (XML) file." );

$f["desc"]      = <<<TEXT
Get the name of the current data file.
TEXT;

$f["seealso"]       = "currentMiner";

$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


?> 


----------------------------------
--- Browser functions ---
----------------------------------


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
browserGoBack. For loading a new page see urlLoad in "URL functions". 
TEXT;
$f["seealso"]   = "urlLoad";
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
$f["params"][]    = array ( "int", "RETURN", "The browser window's width in pixels." );

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


----------------------------
--- Navigation functions ---
----------------------------

<?php
?>


--------------------------------
--- String compare functions ---
--------------------------------

<?php
// --- Common function properties ---
$f_common = array();
$f_common["type"]      = "function";
$f_common["group"]     = "String compare functions";
$f_common["params"][]    = array ( "string", "sInput", "Subject string you want to verify whether it contains, equals, startsWith etc. the sTest string." );
$f_common["params"][]    = array ( "string", "sTest", "The string 'argument' to test for. If eg. function is contains_fn, then we are testing whether sTest is contained within the sInput." );

$f_common_i = $f_common;
$f_common_i["note"][]   = "Currently the case insensitive functions are only working properly for english letters a-z,A-Z. This will be corrected in a future release.";



$f = array();
$f["name"] =
// ******************************
       "String compare functions";
// ******************************

$f["type"]      = "group";
$f["desc"]      = <<<TEXT
A collection of simple functions used to compare two strings in various 
ways. Those functions described here
are regular PHP functions which you use like any other, but each of them 
has a corresponding operator.
The operator has the same name as the regular function name but without 
the '_fn' and is used in domFind,
domFindNext, domSeqCreate, valueCompare, valuesCompare functions. Refer 
to the 'Compare operators' section in this
reference manual.
TEXT;
$f["seealso"]   = "Compare operators";
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "equals_fn";
// ********************
$f["syntax"][]  = <<<TEXT
bool equals_fn ( string sInput, string sTest );
TEXT;
$f["params"][]    = array ( "bool", "RETURN", "True if the two strings are equal." );

$f["desc"]      = <<<TEXT
Compares two strings for equality. This function is mainly here for the 
completeness, since the regular '=='
works in identical way. Also it's here as a consequence of it's 
corresponding operator 'equals', which we
do need for functions like domFindNext, domSeqCreate, valueCompare, 
valuesCompare.
TEXT;

$f["seealso"]       = "iequals_fn, equals";

$f["examples"][]    = <<<TEXT
function MyScript_DoSearch_match()
{
     return equals_fn  ( urlCurrent() , "http://www.somesite.com/search" );
}
TEXT;
$a[] = $f;


$f = $f_common_i;
$f["name"] =
// ********************
       "iequals_fn";
// ********************
$f["syntax"][]  = <<<TEXT
bool iequals_fn ( string sInput, string sTest );
TEXT;
$f["params"][]    = array ( "bool", "RETURN", "True if the two strings are equal regardless of casing." );

$f["desc"]      = <<<TEXT
Case insensitive version of equals_fn.
TEXT;

$f["seealso"]       = "equals_fn, iequals";

$f["examples"][]    = <<<TEXT
\$sInput = "abc";
\$sTest = "aBc";
if ( iequals_fn  ( \$sInput , \$sTest ) ) printf ("Strings '\$sInput' and '\$sTest' ARE 'iequal' \n");
if ( !equals_fn  ( \$sInput , \$sTest ) ) printf ("Strings '\$sInput' and '\$sTest' are NOT 'equal'\n");
// Prints:
// Strings 'abc' and 'aBc' ARE 'iequal'
// Strings 'abc' and 'aBc' are NOT 'equal'
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "contains_fn";
// ********************
$f["syntax"][]  = <<<TEXT
bool contains_fn ( string sInput, string sTest );
TEXT;
$f["params"][]    = array ( "bool", "RETURN", "True if sTest is contained in/is a substring of sInput." );

$f["desc"]      = <<<TEXT
Checks wheter a string is contained within another string. I.e. if a string is a substring of another.
Looks through the sInput string to see if it contains the sTest string.
TEXT;

$f["seealso"]       = "icontains_fn, contains";

$f["examples"][]    = <<<TEXT
function MyScript_SearchListing_match()
{
     return contains_fn  ( urlCurrent() , "/results/" );
}
TEXT;
$a[] = $f;


$f = $f_common_i;
$f["name"] =
// ********************
       "icontains_fn";
// ********************
$f["syntax"][]  = <<<TEXT
bool icontains_fn ( string sInput, string sTest );
TEXT;
$f["params"][]    = array ( "bool", "RETURN", "True if sTest is contained in/is a substring of sInput regardless of casing." );

$f["desc"]      = <<<TEXT
Case insensitive version of contains_fn.
Checks wheter a string is contained within another string. I.e. if a string is a substring of another.
Looks through the sInput string to see if it contains the sTest string.
TEXT;

$f["seealso"]       = "contains_fn, icontains";

$f["examples"][]    = <<<TEXT
$sInput = "aBcDe";
$sTest = "bCd";
printf ( "icontains_fn ( '\$sInput' , '\$sTest' ) = %d\n",  icontains_fn ( \$sInput , \$sTest ) );
printf ( "contains_fn  ( '\$sInput' , '\$sTest' ) = %d\n",  contains_fn  ( \$sInput , \$sTest ) );
// Prints:
// icontains_fn ( 'aBcDe' , 'bCd' ) = 1; // = TRUE
// contains_fn  ( 'aBcDe' , 'bCd' ) = 0; // = FALSE
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "startsWith_fn";
// ********************
$f["syntax"][]  = <<<TEXT
bool startsWith_fn ( string sInput, string sTest );
TEXT;
$f["params"][]    = array ( "bool", "RETURN", "True if sInput starts with sTest." );

$f["desc"]      = <<<TEXT
Checks wheter a string starts with another string. 
TEXT;

$f["seealso"]       = "istartsWith_fn, startsWith";

$f["examples"][]    = <<<TEXT
function MyScript_SearchListing_match()
{
     return startsWith_fn  ( urlCurrent() , "http://www.somesite.com/results/" );
}
TEXT;
$a[] = $f;


$f = $f_common_i;
$f["name"] =
// ********************
       "istartsWith_fn";
// ********************
$f["syntax"][]  = <<<TEXT
bool istartsWith_fn ( string sInput, string sTest );
TEXT;
$f["params"][]    = array ( "bool", "RETURN", "True if sInput starts with sTest regardless of casing." );

$f["desc"]      = <<<TEXT
Case insensitive version of startsWith_fn.
Checks wheter a string starts with another string. 
TEXT;

$f["seealso"]       = "startsWith_fn, istartsWith";

$f["examples"][]    = <<<TEXT
$sInput = "aBcDe";
$sTest = "AbC";
printf ( "istartsWith_fn ( '\$sInput' , '\$sTest' ) = %d\n",  istartsWith_fn ( \$sInput , \$sTest ) );
printf ( "startsWith_fn  ( '\$sInput' , '\$sTest' ) = %d\n",  startsWith_fn  ( \$sInput , \$sTest ) );
// Prints:
// istartsWith_fn ( 'aBcDe' , 'AbC' ) = 1; // = TRUE
// startsWith_fn  ( 'aBcDe' , 'AbC' ) = 0; // = FALSE
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "endsWith_fn";
// ********************
$f["syntax"][]  = <<<TEXT
bool endsWith_fn ( string sInput, string sTest );
TEXT;
$f["params"][]    = array ( "bool", "RETURN", "True if sInput ends with sTest." );

$f["desc"]      = <<<TEXT
Checks wheter a string ends with another string. 
TEXT;

$f["seealso"]       = "iendsWith_fn, endsWith";

$f["examples"][]    = <<<TEXT
function MyScript_DoSearch_match()
{
     return endsWith_fn  ( urlCurrent() , "search.php" );
}
TEXT;
$a[] = $f;


$f = $f_common_i;
$f["name"] =
// ********************
       "iendsWith_fn";
// ********************
$f["syntax"][]  = <<<TEXT
bool iendsWith_fn ( string sInput, string sTest );
TEXT;
$f["params"][]    = array ( "bool", "RETURN", "True if sInput ends with sTest regardless of casing." );

$f["desc"]      = <<<TEXT
Case insensitive version of endsWith_fn.
Checks wheter a string ends with another string. 
TEXT;

$f["seealso"]       = "endsWith_fn, iendsWith";

$f["examples"][]    = <<<TEXT
$sInput = "aBcDe";
$sTest = "CdE";
printf ( "iendsWith_fn ( '\$sInput' , '\$sTest' ) = %d\n",  iendsWith_fn ( \$sInput , \$sTest ) );
printf ( "endsWith_fn  ( '\$sInput' , '\$sTest' ) = %d\n",  endsWith_fn  ( \$sInput , \$sTest ) );
// Prints:
// iendsWith_fn ( 'aBcDe' , 'CdE' ) = 1; // = TRUE
// endsWith_fn  ( 'aBcDe' , 'CdE' ) = 0; // = FALSE
TEXT;
$a[] = $f;

$f = $f_common;
$f["name"] =
// ********************
       "lessThan_fn";
// ********************
$f["syntax"][]  = <<<TEXT
bool lessThan_fn ( string sInput, string sTest );
TEXT;
$f["params"][]    = array ( "bool", "RETURN", "True if sInput is less than sTest." );

$f["desc"]      = <<<TEXT
Lexigraphical comparison of two strings
Checks wheter a string is 'less than' another string. 
TEXT;

$f["seealso"]       = "ilessThan_fn, lessThan";

$f["examples"][]    = <<<TEXT
$sInput = "household";
$sTest1 = "house";
$sTest2 = "houses";
printf ( "lessThan_fn ( '\$sInput' , '\$sTest1' ) = %d\n",  lessThan_fn ( \$sInput , \$sTest1 ) );
printf ( "lessThan_fn ( '\$sInput' , '\$sTest2' ) = %d\n",  lessThan_fn ( \$sInput , \$sTest2 ) );
// Prints:
// lessThan_fn ( 'household' , 'house' )  = 0; // = FALSE
// lessThan_fn ( 'household' , 'houses' ) = 1; // = TRUE
TEXT;
$a[] = $f;


$f = $f_common_i;
$f["name"] =
// ********************
       "ilessThan_fn";
// ********************
$f["syntax"][]  = <<<TEXT
bool ilessThan_fn ( string sInput, string sTest );
TEXT;
$f["params"][]    = array ( "bool", "RETURN", "True if sInput is less than sTest regardless of casing." );

$f["desc"]      = <<<TEXT
Case insensitive version of lessThan_fn.
Checks wheter a string is 'less than' another string. 
TEXT;

$f["seealso"]       = "lessThan_fn, ilessThan";

$f["examples"][]    = <<<TEXT
$sInput = "HouseHold";
$sTest1 = "houSe";
$sTest2 = "houSes";
printf ( "ilessThan_fn ( '\$sInput' , '\$sTest1' ) = %d\n",  ilessThan_fn ( \$sInput , \$sTest1 ) );
printf ( "ilessThan_fn ( '\$sInput' , '\$sTest2' ) = %d\n",  ilessThan_fn ( \$sInput , \$sTest2 ) );
// Prints:
// ilessThan_fn ( 'HouseHold' , 'houSe' )  = 0; // = FALSE
// ilessThan_fn ( 'HouseHold' , 'houSes' ) = 1; // = TRUE
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "greaterThan_fn";
// ********************
$f["syntax"][]  = <<<TEXT
bool greaterThan_fn ( string sInput, string sTest );
TEXT;
$f["params"][]    = array ( "bool", "RETURN", "True if sInput is greater than sTest." );

$f["desc"]      = <<<TEXT
Lexigraphical comparison of two strings
Checks wheter a string is 'greater than' another string. 
TEXT;

$f["seealso"]       = "igreaterThan_fn, greaterThan";

$f["examples"][]    = <<<TEXT
$sInput = "household";
$sTest1 = "house";
$sTest2 = "houses";
printf ( "greaterThan_fn ( '\$sInput' , '\$sTest1' ) = %d\n",  greaterThan_fn ( \$sInput , \$sTest1 ) );
printf ( "greaterThan_fn ( '\$sInput' , '\$sTest2' ) = %d\n",  greaterThan_fn ( \$sInput , \$sTest2 ) );
// Prints:
// greaterThan_fn ( 'household' , 'house' )  = 1; // = TRUE
// greaterThan_fn ( 'household' , 'houses' ) = 0; // = FALSE
TEXT;
$a[] = $f;


$f = $f_common_i;
$f["name"] =
// ********************
       "igreaterThan_fn";
// ********************
$f["syntax"][]  = <<<TEXT
bool igreaterThan_fn ( string sInput, string sTest );
TEXT;
$f["params"][]    = array ( "bool", "RETURN", "True if sInput is greater than sTest regardgreater of casing." );

$f["desc"]      = <<<TEXT
Case insensitive version of greaterThan_fn.
Checks wheter a string is 'greater than' another string. 
TEXT;

$f["seealso"]       = "greaterThan_fn, igreaterThan";

$f["examples"][]    = <<<TEXT
$sInput = "HouseHold";
$sTest1 = "houSe";
$sTest2 = "houSes";
printf ( "igreaterThan_fn ( '\$sInput' , '\$sTest1' ) = %d\n",  igreaterThan_fn ( \$sInput , \$sTest1 ) );
printf ( "igreaterThan_fn ( '\$sInput' , '\$sTest2' ) = %d\n",  igreaterThan_fn ( \$sInput , \$sTest2 ) );
// Prints:
// igreaterThan_fn ( 'HouseHold' , 'houSe' )  = 1; // = TRUE	
// igreaterThan_fn ( 'HouseHold' , 'houSes' ) = 0; // = FALSE
TEXT;
$a[] = $f;

$f = $f_common;
$f["name"] =
// ********************
       "regexSearch_fn";
// ********************
$f["syntax"][]  = <<<TEXT
bool regexSearch_fn ( string sInput, string sTest );
TEXT;
$f["params"][]    = array ( "bool", "RETURN", "True if search for the regular expression sTest is found in sInput." );

$f["desc"]      = <<<TEXT
Regular expression search. Perl style regular expressions are used.
See for example more about regular expressions here:
http://www.aivosto.com/vbtips/regex.html
http://www.codeproject.com/Articles/939/An-Introduction-to-Regular-Expressions
TEXT;

$f["seealso"]       = "regexSearch";

$f["examples"][]    = <<<TEXT
TODO: Create some regular expression examples.
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "valuesCompare";
// ********************
$f["syntax"][]  = <<<TEXT
bool valuesCompare(string sInput, string sTest, string sCompareOperator);
TEXT;
$f["params"][]    = array ( "string", "sCompareOperator", "The compare operator like for example 'contains'." );
$f["params"][]    = array ( "bool", "RETURN", "True if compare operator returns true for the operands sInput and sTest." );

$f["desc"]      = <<<TEXT
Compares two strings using a named operator. 
TEXT;

$f["seealso"]       = "'String compare operators'";

$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;

?>

--------------------------------
--- String compare operators ---
--------------------------------

<? php
// --- Common function properties ---
$f_common = array();
$f_common["type"]      = "operator";
$f_common["group"]     = "String compare operators";
$f_common["params"][]   = array ( "string", "sLhs", "Right hand side of compare operation." );
$f_common["params"][]   = array ( "string", "sTest", "Left hand side of the compare operation." );

$f_common_i = $f_common;
$f_common_i["note"][]   = "Currently the case insensitive functions are only working properly for english letters a-z,A-Z. This will be corrected in a future release.";




$f = array();
$f["name"] =
// ******************************
       "String compare operators";
// ******************************

$f["type"]      = "group";
$f["desc"]      = <<<TEXT
A collection of simple operators used to compare two strings in various 
ways. The operator has the same name as the regular function name but without 
the '_fn' and is used in domFind,
domFindNext, domSeqCreate, valueCompare, valuesCompare functions like this:
domFind( "class, myClass", "equals" );
reference manual.
TEXT;
$f["seealso"]   = "String compare functions";
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "equals";
// ********************
$f["syntax"][]  = <<<TEXT
"equals"
TEXT;
$f["params"][]    = array ( "bool", "RETURN", "True if the two strings are equal." );

$f["desc"]      = <<<TEXT
Compares two strings for equality. 
TEXT;

$f["seealso"]       = "iequals, equals_fn";

$f["examples"][]    = <<<TEXT
domFind( "class, myClass", "equals" );
TEXT;
$a[] = $f;


$f = $f_common_i;
$f["name"] =
// ********************
       "iequals";
// ********************
$f["syntax"][]  = <<<TEXT
"iequals"
TEXT;
$f["params"][]    = array ( "bool", "RETURN", "True if the two strings are equal regardless of casing." );

$f["desc"]      = <<<TEXT
Case insensitive version of equals operator.
TEXT;

$f["seealso"]       = "equals, iequals_fn";

$f["examples"][]    = <<<TEXT
domFind( "class, myClass", "iequals" );
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "contains";
// ********************
$f["syntax"][]  = <<<TEXT
"contains"
TEXT;
$f["params"][]    = array ( "bool", "RETURN", "True if sTest is contained in/is a substring of sInput." );

$f["desc"]      = <<<TEXT
Checks wheter a string is contained within another string. I.e. if a string is a substring of another.
Looks through the sInput string to see if it contains the sTest string.
TEXT;

$f["seealso"]       = "icontains, contains_fn";

$f["examples"][]    = <<<TEXT
domSeqCreate( "ProductPricePos" "USD", "contains" );
TEXT;
$a[] = $f;


$f = $f_common_i;
$f["name"] =
// ********************
       "icontains";
// ********************
$f["syntax"][]  = <<<TEXT
"icontains"
TEXT;
$f["params"][]    = array ( "bool", "RETURN", "True if sTest is contained in/is a substring of sInput regardless of casing." );

$f["desc"]      = <<<TEXT
Case insensitive version of contains operator.
Checks wheter a string is contained within another string. I.e. if a string is a substring of another.
Looks through the sInput string to see if it contains the sTest string.
TEXT;

$f["seealso"]       = "contains, icontains_fn";

$f["examples"][]    = <<<TEXT
domSeqCreate( "ProductPricePos" "USD", "icontains" );
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "startsWith";
// ********************
$f["syntax"][]  = <<<TEXT
"startsWith"
TEXT;
$f["params"][]    = array ( "bool", "RETURN", "True if sInput starts with sTest." );

$f["desc"]      = <<<TEXT
Checks wheter a string starts with another string. 
TEXT;

$f["seealso"]       = "istartsWith, startsWith_fn";

$f["examples"][]    = <<<TEXT
domSeqCreate( "ProductPricePos" "USD", "startsWith" );
TEXT;
$a[] = $f;


$f = $f_common_i;
$f["name"] =
// ********************
       "istartsWith";
// ********************
$f["syntax"][]  = <<<TEXT
"istartsWith"
TEXT;
$f["params"][]    = array ( "bool", "RETURN", "True if sInput starts with sTest regardless of casing." );

$f["desc"]      = <<<TEXT
Case insensitive version of startsWith operator.
Checks wheter a string starts with another string. 
TEXT;

$f["seealso"]       = "startsWith, istartsWith_fn";

$f["examples"][]    = <<<TEXT
domSeqCreate( "ProductPricePos" "USD", "istartsWith" );
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "endsWith";
// ********************
$f["syntax"][]  = <<<TEXT
"endsWith"
TEXT;
$f["params"][]    = array ( "bool", "RETURN", "True if sInput ends with sTest." );

$f["desc"]      = <<<TEXT
Checks wheter a string ends with another string. 
TEXT;

$f["seealso"]       = "iendsWith, endsWith_fn";

$f["examples"][]    = <<<TEXT
domSeqCreate( "ProductPricePos" "USD", "endsWith" );
TEXT;
$a[] = $f;


$f = $f_common_i;
$f["name"] =
// ********************
       "iendsWith";
// ********************
$f["syntax"][]  = <<<TEXT
"iendsWith"
TEXT;
$f["params"][]    = array ( "bool", "RETURN", "True if sInput ends with sTest regardless of casing." );

$f["desc"]      = <<<TEXT
Case insensitive version of endsWith operator.
Checks wheter a string ends with another string. 
TEXT;

$f["seealso"]       = "endsWith, iendsWith_fn";

$f["examples"][]    = <<<TEXT
domSeqCreate( "ProductPricePos" "USD", "iendsWith" );
TEXT;
$a[] = $f;

$f = $f_common;
$f["name"] =
// ********************
       "lessThan";
// ********************
$f["syntax"][]  = <<<TEXT
"lessThan"
TEXT;
$f["params"][]    = array ( "bool", "RETURN", "True if sInput is less than sTest." );

$f["desc"]      = <<<TEXT
Lexigraphical comparison of two strings
Checks wheter a string is 'less than' another string. 
TEXT;

$f["seealso"]       = "ilessThan, lessThan_fn";

$f["examples"][]    = <<<TEXT
TODO: Examples for lessThan operator
TEXT;
$a[] = $f;


$f = $f_common_i;
$f["name"] =
// ********************
       "ilessThan";
// ********************
$f["syntax"][]  = <<<TEXT
"ilessThan"
TEXT;
$f["params"][]    = array ( "bool", "RETURN", "True if sInput is less than sTest regardless of casing." );

$f["desc"]      = <<<TEXT
Case insensitive version of lessThan operator.
Checks wheter a string is 'less than' another string. 
TEXT;

$f["seealso"]       = "lessThan, ilessThan_fn";

$f["examples"][]    = <<<TEXT
TODO: Examples for ilessThan operator
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "greaterThan";
// ********************
$f["syntax"][]  = <<<TEXT
"greaterThan"
TEXT;
$f["params"][]    = array ( "bool", "RETURN", "True if sInput is greater than sTest." );

$f["desc"]      = <<<TEXT
Lexigraphical comparison of two strings
Checks wheter a string is 'greater than' another string. 
TEXT;

$f["seealso"]       = "igreaterThan, greaterThan_fn";

$f["examples"][]    = <<<TEXT
TODO: Examples for greaterThan operator
TEXT;
$a[] = $f;


$f = $f_common_i;
$f["name"] =
// ********************
       "igreaterThan";
// ********************
$f["syntax"][]  = <<<TEXT
"igreaterThan"
TEXT;
$f["params"][]    = array ( "bool", "RETURN", "True if sInput is greater than sTest regardgreater of casing." );

$f["desc"]      = <<<TEXT
Case insensitive version of greaterThan operator.
Checks wheter a string is 'greater than' another string. 
TEXT;

$f["seealso"]       = "greaterThan_fn, igreaterThan";

$f["examples"][]    = <<<TEXT
TODO: Examples for igreaterThan operator
TEXT;
$a[] = $f;

$f = $f_common;
$f["name"] =
// ********************
       "regexSearch";
// ********************
$f["syntax"][]  = <<<TEXT
"regexSearch"
TEXT;
$f["params"][]    = array ( "bool", "RETURN", "True if search for the regular expression sTest is found in sInput." );

$f["desc"]      = <<<TEXT
Regular expression search. Perl style regular expressions are used.
See for example more about regular expressions here:
http://www.aivosto.com/vbtips/regex.html
http://www.codeproject.com/Articles/939/An-Introduction-to-Regular-Expressions
TEXT;

$f["seealso"]       = "regexSearch_fn";

$f["examples"][]    = <<<TEXT
TODO: Create some regular expression examples for the operator regexSearch.
TEXT;
$a[] = $f;

?>


-------------------------------------
--- String manipulation functions ---
-------------------------------------
<?php
?>


-------------------------------------
--- String manipulation operators ---
-------------------------------------
<?php
?>




---------------------
--- URL functions ---
---------------------
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
$f["seealso"]   = "urlLoad";
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

---------------------
--- Dom functions ---
---------------------

<?php

$f = array();
$f["name"] =
// **************************
       "Dom functions";
// **************************

$f["type"]      = "group";
$f["desc"]      = <<<TEXT
Functions used to navigate the dom / linearized dom. These include the workhorses domFind and domFindNext, 
which locate a posistion for example like this: domFind ( "DIV, class, MyClass", "equals" );
 
TEXT;
$f["seealso"]   = "";
$a[] = $f;

$f = array();
$f["name"] =
// ********************
       "DomNodeTypes";
// ********************
$f["type"]      = "enum";
$f["group"]     = "Dom functions";

$f["values"][]	= array ( "ELEMENT_NODE", "Key element node like DIV, INPUT, HTML, BODY ... Always in capital letters." );
$f["values"][]	= array ( "ATTRIBUTE_NODE", "An actual attribute name. Like 'class' in <DIV class=MyClass ... >" );
$f["values"][]	= array ( "TEXT_NODE", "Text node" );
//$f["values"][]	= array ( "CDATA_SECTION_NODE", "" );
//$f["values"][]	= array ( "ENTITY_REFERENCE_NODE", "" );
//$f["values"][]	= array ( "ENTITY_NODE", "" );
//$f["values"][]	= array ( "PROCESSING_INSTRUCTION_NODE", "" );
//$f["values"][]	= array ( "COMMENT_NODE", "" );
//$f["values"][]	= array ( "DOCUMENT_NODE", "" );
//$f["values"][]	= array ( "DOCUMENT_TYPE_NODE", "" );
//$f["values"][]	= array ( "DOCUMENT_FRAGMENT_NODE", "" );
//$f["values"][]	= array ( "NOTATION_NODE", "" );
$f["values"][]	= array ( "ATTRIBUTE_VALUE_NODE", "The value of an attribute. Like 'MyClass' in <DIV class=MyClass ... >" );
$f["values"][]	= array ( "ALL_NODE_TYPES", "Constant that combines all node types. This is the default we search for." );

$f["desc"]      = <<<TEXT
Dom node types used to restrict searching in the dom to only certain types of nodes, like e.g. TEXT_NODE. 
If you only want to search trough attribute nodes nodes you could do 'domFind( 1, "id, class", "equals", ATTRIBUTE_NODE )'.
You can combine more types using bitwise or operator "|" lie this:
'domFind( 1, "class, MyClass", "equals", ATTRIBUTE_NODE | ATTRIBUTE_VALUE_NODE)'
TEXT;
$f["seealso"]       = "domFind, domFindNext, domFindPrev, domStep";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


// --- Common function properties ---
$f_common = array();
$f_common["type"]      = "function";
$f_common["group"]     = "Dom functions";


$f = $f_common;
$f["name"] =
// ********************
       "domNewSearch";
// ********************
$f["syntax"][]  = <<<TEXT
void domNewSearch();
TEXT;

$f["desc"]      = <<<TEXT
Reset the dom pointer to the top of the page ready for a new search. 
This function is not needed that often since a domFind will do this automatically. 
It most usefull if you for some reason wants to call domFindNext multiple times like 
when iterating thruogh a number of positions on the same page like when locating items 
in a search listing.
TEXT;

$f["seealso"]       = "domFindNext";

$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "domFindParentPos";
// ********************
$f["syntax"][]  = <<<TEXT
int domFindParentPos ( int iLevelsUp = 1 );
TEXT;
$f["params"][]    = array ( "int", "iLevelsUp", "Number of levels to go 'upwards' in the dom tree." );
$f["params"][]    = array ( "int", "RETURN", "Dom position of the parent dom element." );

$f["desc"]      = <<<TEXT
Get position of parent element of current without changing the current position. Given a dom tree like:
'<BODY><DIV><INPUT class=MyClass ></INPUT></DIV></BODY>'. If we are currently at the INPUT element then 
domFindParentPos(1) will return the position of the DIV and domFindParentPos(2) will return the position of BODY.

TODO: Check up on how it works if current position is not an element node but an attribute or attibute value. 
TEXT;
$f["seealso"]       = "domFindParent";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "domFindParent";
// ********************
$f["syntax"][]  = <<<TEXT
int domFindParent ( int iLevelsUp = 1 );
TEXT;
$f["params"][]    = array ( "int", "iLevelsUp", "Number of levels to go 'upwards' in the dom tree." );
$f["params"][]    = array ( "int", "RETURN", "Dom position of the parent dom element." );

$f["desc"]      = <<<TEXT
Go to position of parent element of current. Given a dom tree like:
'<BODY><DIV><INPUT class=MyClass ></INPUT></DIV></BODY>'. If we are currently at the INPUT element then 
domFindParentPos(1) will go to the position of the DIV and domFindParentPos(2) will go to the position of BODY.

TODO: Check up on how it works if current position is not an element node but an attribute or attibute value. 
TEXT;
$f["seealso"]       = "domFindParentPos";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "domFindNext";
// ********************
$f["syntax"][]  = <<<TEXT
int domFindNext ( int iCount, string sSequence, string sCompareFun, int iNodeTypes );
int domFindNext ( int iCount, string sSequence, string sCompareFun );
int domFindNext ( int iCount, string sSequence, int iNodeTypes );
int domFindNext ( int iCount, string sSequence );
int domFindNext ( string sSequence, string sCompareFun );
TEXT;
$f["params"][]    = array ( "int", "iCount", "Stop 1st, 2nd, 3rd ... position that matches the sequence. Can be negative to search backwards." );
$f["params"][]    = array ( "string", "sSequence", "Dom sequence. Can be one of: PHP function, named dom sequence, direct specified" );
$f["params"][]    = array ( "string", "sCompareFun", "Compare operator to use like contains, equals endsWith" );
$f["params"][]    = array ( "int", "iNodeTypes", "Only consider node types matching set. See DomNodeTypes." );
$f["params"][]    = array ( "int", "RETURN", "The new position, that we have moved to in the dom or zero if not found." );

$f["desc"]      = <<<TEXT
Search from current position for next that matches a given dom sequence. The function exist in a number of variants, 
but most often you just need to search for the first position forward that matches like for example:
'domFindNext( "DIV, class, MyClass", "equals" )'. But if you actually wanted to find the third time this sequence appears 
you could use: 'domFindNext( 3, "DIV, class, MyClass", "equals" )' or even: 'domFindNext( -2, "DIV, class, MyClass", "equals" )' 
to search for second occurence going backwards.

The dom sequence parameter can be a direct (inline) specified sequence like "DIV, class, MyClass" in which case 
you also MUST specify the compare function. 
The sequence can also refer to a "named" dom sequence created using domSeqCreate like for example: 
'domSeqCreate("ProductUrlPos", "DIV, href, /products/", "contains" )', and then using like:
'domFindNext( 1, "ProductUrlPos" )'. In case you use a form of domFind which have the sCompareFun parameter 
it will simply be ignored if a named dom sequence is found and used. 
Finally the sSequence parameter can also refer to a PHP function of that name in which case any sCompareFun 
parameter is also ignored.

The order in which the 3 approaches are used is: PHP function, named dom sequence, direct specified.
TEXT;
$f["seealso"]       = "domFind, domFindPrev, domFindNextPos, domFindNextParams, 'String compare operators'";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "domFindPrev";
// ********************
$f["syntax"][]  = <<<TEXT
int domFindPrev ( string sSequence, string sCompareFun );
TEXT;
$f["params"][]    = array ( "string", "sSequence", "Dom sequence. Can be one of: PHP function, named dom sequence, direct specified" );
$f["params"][]    = array ( "string", "sCompareFun", "Compare operator to use like contains, equals endsWith" );
$f["params"][]    = array ( "int", "RETURN", "The new position, that we have moved to in the dom or zero if not found." );

$f["desc"]      = <<<TEXT
Search from current position for first match backwards for given dom sequence. 

The dom sequence parameter can be a direct (inline) specified sequence like "DIV, class, MyClass" in which case 
you also MUST specify the compare function. 
The sequence can also refer to a "named" dom sequence created using domSeqCreate like for example: 
'domSeqCreate("ProductUrlPos", "DIV, href, /products/", "contains" )', and then using like:
'domFindPrev( "ProductUrlPos", "equals" )' . In this case the sCompareFun parameter will simply be ignored 
if a named dom sequence is found and used. 
Finally the sSequence parameter can also refer to a PHP function of that name in which case any sCompareFun 
parameter is also ignored.

The order in which the 3 approaches are used is: PHP function, named dom sequence, direct specified.
TEXT;
$f["seealso"]       = "domFind, domFindNext, 'String compare operators'";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;



---
$f = $f_common;
$f["name"] =
// ********************
       "domFindNextParams";
// ********************
$f["syntax"][]  = <<<TEXT
int domFindNextParams ( int iCount, string sSequence, string sArgs );
TEXT;
$f["params"][]    = array ( "int", "iCount", "Stop 1st, 2nd, 3rd ... position that matches the sequence. Can be negative to search backwards." );
$f["params"][]    = array ( "string", "sSequence", "Dom sequence. Can be one of: PHP function, named dom sequence, direct specified" );
$f["params"][]    = array ( "string", "sArgs", "Comma separated string of arguments" );
$f["params"][]    = array ( "int", "RETURN", "The new position, that we have moved to in the dom or zero if not found." );

$f["desc"]      = <<<TEXT
Search from current position for next that matches a given dom sequence substituting in the given arguments. 
The domFindNextParams form is mainly used by the navigator's navDomPosClickCreate capability. 

TODO: More about parameters and how it's used.

The order in which the 3 approaches are used is: PHP function, named dom sequence, direct specified.
TEXT;
$f["seealso"]       = "domFind, domFindPrev, domFindNext";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "domFind";
// ********************
$f["syntax"][]  = <<<TEXT
int domFind ( int iCount, string sSequence, string sCompareFun, int iNodeTypes );
int domFind ( int iCount, string sSequence, string sCompareFun );
int domFind ( int iCount, string sSequence, int iNodeTypes );
int domFind ( int iCount, string sSequence );
int domFind ( string sSequence, string sCompareFun );
TEXT;
$f["params"][]    = array ( "int", "iCount", "Stop 1st, 2nd, 3rd ... position that matches the sequence. Can be negative to search backwards." );
$f["params"][]    = array ( "string", "sSequence", "Dom sequence. Can be one of: PHP function, named dom sequence, direct specified" );
$f["params"][]    = array ( "string", "sCompareFun", "Compare operator to use like contains, equals endsWith" );
$f["params"][]    = array ( "int", "iNodeTypes", "Only consider node types matching set. See DomNodeTypes." );
$f["params"][]    = array ( "int", "RETURN", "The new position, that we have moved to in the dom or zero if not found." );

$f["desc"]      = <<<TEXT
Search from start (can be changed by setting temp starting pos) for a position that matches a given dom sequence. 
The function exist in a number of variants, but most often you just need to search for the first position forward 
that matches like for example:
'domFind( "DIV, class, MyClass", "equals" )'. But if you actually wanted to find the third time this sequence appears 
you could use: 'domFind( 3, "DIV, class, MyClass", "equals" )'.

The dom sequence parameter can be a direct (inline) specified sequence like "DIV, class, MyClass" in which case 
you also MUST specify the compare function. 
The sequence can also refer to a "named" dom sequence created using domSeqCreate like for example: 
'domSeqCreate("ProductUrlPos", "DIV, href, /products/", "contains" )', and then using like:
'domFind( 1, "ProductUrlPos" )'. In case you use a form of domFind which have the sCompareFun parameter 
it will simply be ignored if a named dom sequence is found and used. 
Finally the sSequence parameter can also refer to a PHP function of that name in which case any sCompareFun 
parameter is also ignored.

The order in which the 3 approaches are used is: PHP function, named dom sequence, direct specified.
TEXT;
$f["seealso"]       = "domFindNext, domFindPos, domFindPrev, 'String compare operators'";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "domFindNextPos";
// ********************
$f["syntax"][]  = <<<TEXT
int domFindNextPos ( int iCount, string sSequence, string sCompareFun, int iNodeTypes );
int domFindNextPos ( int iCount, string sSequence, string sCompareFun );
int domFindNextPos ( int iCount, string sSequence, int iNodeTypes );
int domFindNextPos ( int iCount, string sSequence );
int domFindNextPos ( string sSequence, string sCompareFun );
TEXT;
$f["params"][]    = array ( "int", "iCount", "Stop 1st, 2nd, 3rd ... position that matches the sequence. Can be negative to search backwards." );
$f["params"][]    = array ( "string", "sSequence", "Dom sequence. Can be one of: PHP function, named dom sequence, direct specified" );
$f["params"][]    = array ( "string", "sCompareFun", "Compare operator to use like contains, equals endsWith" );
$f["params"][]    = array ( "int", "iNodeTypes", "Only consider node types matching set. See DomNodeTypes." );
$f["params"][]    = array ( "int", "RETURN", "The new position, that we have moved to in the dom or zero if not found." );

$f["desc"]      = <<<TEXT
Search from current position for next that matches a given dom sequence returning that position without 
changing the current. The function exist in a number of variants, 
but most often you just need to search for the first position forward that matches like for example:
'domFindNextPos( "DIV, class, MyClass", "equals" )'. But if you actually wanted to find the third time this sequence appears 
you could use: 'domFindNextPos( 3, "DIV, class, MyClass", "equals" )' or even: 'domFindNextPos( -2, "DIV, class, MyClass", "equals" )' 
to search for second occurence going backwards.

The dom sequence parameter can be a direct (inline) specified sequence like "DIV, class, MyClass" in which case 
you also MUST specify the compare function. 
The sequence can also refer to a "named" dom sequence created using domSeqCreate like for example: 
'domSeqCreate("ProductUrlPos", "DIV, href, /products/", "contains" )', and then using like:
'domFindNextPos( 1, "ProductUrlPos" )'. In case you use a form of domFind which have the sCompareFun parameter 
it will simply be ignored if a named dom sequence is found and used. 
Finally the sSequence parameter can also refer to a PHP function of that name in which case any sCompareFun 
parameter is also ignored.

The order in which the 3 approaches are used is: PHP function, named dom sequence, direct specified.
TEXT;
$f["seealso"]       = "domFind, domFindPrev, domFindNext, 'String compare operators'";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "domFindPos";
// ********************
$f["syntax"][]  = <<<TEXT
int domFindPos ( int iCount, string sSequence, string sCompareFun, int iNodeTypes );
int domFindPos ( int iCount, string sSequence, string sCompareFun );
int domFindPos ( int iCount, string sSequence, int iNodeTypes );
int domFindPos ( int iCount, string sSequence );
int domFindPos ( string sSequence, string sCompareFun );
TEXT;
$f["params"][]    = array ( "int", "iCount", "Stop 1st, 2nd, 3rd ... position that matches the sequence. Can be negative to search backwards." );
$f["params"][]    = array ( "string", "sSequence", "Dom sequence. Can be one of: PHP function, named dom sequence, direct specified" );
$f["params"][]    = array ( "string", "sCompareFun", "Compare operator to use like contains, equals endsWith" );
$f["params"][]    = array ( "int", "iNodeTypes", "Only consider node types matching set. See DomNodeTypes." );
$f["params"][]    = array ( "int", "RETURN", "The new position, that we have moved to in the dom or zero if not found." );

$f["desc"]      = <<<TEXT
TODO: Not implemented yet, but will be soon.
Search from start (can be changed by setting temp starting pos) for a position that matches a given dom sequence
returning that position without changing the current. 
The function exist in a number of variants, but most often you just need to search for the first position that matches like 
for example:
'domFindPos( "DIV, class, MyClass", "equals" )'. But if you actually wanted to find the third time this sequence appears 
you could use: 'domFindPos( 3, "DIV, class, MyClass", "equals" )'.

The dom sequence parameter can be a direct (inline) specified sequence like "DIV, class, MyClass" in which case 
you also MUST specify the compare function. 
The sequence can also refer to a "named" dom sequence created using domSeqCreate like for example: 
'domSeqCreate("ProductUrlPos", "DIV, href, /products/", "contains" )', and then using like:
'domFindPos( 1, "ProductUrlPos" )'. In case you use a form of domFindPos which have the sCompareFun parameter 
it will simply be ignored if a named dom sequence is found and used. 
Finally the sSequence parameter can also refer to a PHP function of that name in which case any sCompareFun 
parameter is also ignored.

The order in which the 3 approaches are used is: PHP function, named dom sequence, direct specified.
TEXT;
$f["seealso"]       = "domFindNext, domFind, domFindPrev, 'String compare operators'";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "domClickInput";
// ********************
$f["syntax"][]  = <<<TEXT
int domClickInput ( int iCount );
TEXT;
$f["params"][]    = array ( "int", "iCount", "The INPUT element number to click. for example click INPUT number 3: domClickInput(3)" );
$f["params"][]    = array ( "int", "RETURN", "The dom position of the INPUT element that was clicked." );

$f["desc"]      = <<<TEXT
Click at INPUT element number iCount from start. Current dom position is not changed.
TEXT;
$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "domClickInput";
// ********************
$f["syntax"][]  = <<<TEXT
int domClickInputNext ( int iCount );
TEXT;
$f["params"][]    = array ( "int", "iCount", "The INPUT element number to click. for example click INPUT number 3: domClickInput(3)" );
$f["params"][]    = array ( "int", "RETURN", "The dom position of the INPUT element that was clicked." );

$f["desc"]      = <<<TEXT
Click at INPUT element number iCount starting from current dom position. Current dom position is not changed.
TEXT;
$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "domSetInput";
// ********************
$f["syntax"][]  = <<<TEXT
int domSetInput ( int iCount, string sValue );
int domSetInput ( int iCount, int iValue    );
TEXT;
$f["params"][]    = array ( "int", "iCount", "The INPUT element number to set a value for. for example set INPUT number 3, to 'Video': domSetInput(3, 'Video')." );
$f["params"][]    = array ( "string", "sValue", "The value (string) to set." );
$f["params"][]    = array ( "int", "iValue", "The value (integer) to set." );
$f["params"][]    = array ( "int", "RETURN", "The dom position of the INPUT element that was clicked." );

$f["desc"]      = <<<TEXT
Sets INPUT element number iCount from start to value. Current dom position is not changed.
TEXT;
$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "domSetInputNext";
// ********************
$f["syntax"][]  = <<<TEXT
int domSetInputNext ( int iCount, string sValue );
int domSetInputNext ( int iCount, int iValue    );
TEXT;
$f["params"][]    = array ( "int", "iCount", "The INPUT element number to set a value for. for example set INPUT number 3, to 'Video': domSetInput(3, 'Video')." );
$f["params"][]    = array ( "string", "sValue", "The value (string) to set." );
$f["params"][]    = array ( "int", "iValue", "The value (integer) to set." );
$f["params"][]    = array ( "int", "RETURN", "The dom position of the INPUT element that was clicked." );

$f["desc"]      = <<<TEXT
Sets INPUT element number iCount starting from current dom position to value. Current dom position is not changed.
TEXT;
$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "domStep";
// ********************
$f["syntax"][]  = <<<TEXT
int domStep ( int iCount, int iNodeTypes = ALL_NODE_TYPES );
TEXT;
$f["params"][]    = array ( "int", "iCount", "Number of node positions to move. Negative values step backwards." );
$f["params"][]    = array ( "int", "iNodeTypes", "Only consider node types matching set. See DomNodeTypes." );
$f["params"][]    = array ( "int", "RETURN", "The new position in the dom if the move was possible, zero otherwise." );

$f["desc"]      = <<<TEXT
Unconditionally move current position a number of nodes forward or backwards in the linearized dom. Dom position is 
only changed in case the step/move succeded.
TEXT;
$f["seealso"]       = "domAtEnd";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;

$f = $f_common;
$f["name"] =
// ********************
       "domAtEnd";
// ********************
$f["syntax"][]  = <<<TEXT
bool domAtEnd ();
TEXT;
$f["params"][]    = array ( "bool", "RETURN", "True if current position as at the end" );

$f["desc"]      = <<<TEXT
Test if current position is at the end of the linearized dom.
TEXT;
$f["seealso"]       = "domStep, domSetAtEnd";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "domPointerPush";
// ********************
$f["syntax"][]  = <<<TEXT
void domPointerPush ();
TEXT;

$f["desc"]      = <<<TEXT
Push current dom position to a stack for later restoring using domPointerPop.
TEXT;
$f["seealso"]       = "domPointerPop";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "domPointerPop";
// ********************
$f["syntax"][]  = <<<TEXT
int domPointerPop ();
TEXT;

$f["params"][]    = array ( "int", "RETURN", "The restored dom position." );

$f["desc"]      = <<<TEXT
Restore current dom position to one saved from the most recent call to domPointerPush.
TEXT;
$f["seealso"]       = "domPointerPush";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "domSize";
// ********************
$f["syntax"][]  = <<<TEXT
int domSize ();
TEXT;
$f["params"][]    = array ( "int", "RETURN", "Size of the current linearized dom. I.e. number of nodes/positions." );

$f["desc"]      = <<<TEXT
Get size of the current linearized dom. I.e. number of nodes/positions.
TEXT;
$f["seealso"]       = "domEndPos";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "domEndPos";
// ********************
$f["syntax"][]  = <<<TEXT
int domEndPos ();
TEXT;
$f["params"][]    = array ( "int", "RETURN", "First position after the last valid in the linearized dom." );

$f["desc"]      = <<<TEXT
Get first position after the last valid in the linearized dom. So this position is on past the last valid dom position. 
TEXT;
$f["seealso"]       = "domSize";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "domGetPos";
// ********************
$f["syntax"][]  = <<<TEXT
int domGetPos ();
TEXT;
$f["params"][]    = array ( "int", "RETURN", "Current position in the linearized dom." );

$f["desc"]      = <<<TEXT
Get current position in the linearized dom. 
TEXT;
$f["seealso"]       = "domSetPos";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "domSetPos";
// ********************
$f["syntax"][]  = <<<TEXT
int domSetPos ( int iNewPos );
TEXT;
$f["params"][]    = array ( "int", "iNewPos", "The desired new position to use as current." );
$f["params"][]    = array ( "int", "RETURN", "New position in dom if succesfull, otherwise zero." );

$f["desc"]      = <<<TEXT
Set current dom position to specific value.
TEXT;
$f["seealso"]       = "domGetPos";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "domGetStopPos";
// ********************
$f["syntax"][]  = <<<TEXT
int domGetStopPos ();
TEXT;
$f["params"][]    = array ( "int", "RETURN", "Current stop position in the linearized dom if any." );

$f["desc"]      = <<<TEXT
Get current stop position in the linearized dom. 
TEXT;
$f["seealso"]       = "domSetStopPos, domClearStopPos, domSetStartPos";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "domSetStopPos";
// ********************
$f["syntax"][]  = <<<TEXT
int domSetStopPos ( int iStopPos );
TEXT;
$f["params"][]    = array ( "int", "iStopPos", "Value to use as temporary stop/end position." );
$f["params"][]    = array ( "int", "RETURN", "TODO" );

$f["desc"]      = <<<TEXT
Set a temporary stop position which domFind family functions will not search beyond. The stop postion works as 
if the linearized dom  really ends here.
TEXT;
$f["seealso"]       = "domGetStopPos, domClearStopPos, domSetStartPos";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "domClearStopPos";
// ********************
$f["syntax"][]  = <<<TEXT
void domClearStopPos ();
TEXT;

$f["desc"]      = <<<TEXT
Clears any temporary stop position.
TEXT;
$f["seealso"]       = "domSetStopPos, domClearStartPos";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "domGetStartPos";
// ********************
$f["syntax"][]  = <<<TEXT
int domGetStartPos ();
TEXT;
$f["params"][]    = array ( "int", "RETURN", "Current start position in the linearized dom if any." );

$f["desc"]      = <<<TEXT
TODO: Not implemented yet, but will be soon.
Get current start position in the linearized dom. 
TEXT;
$f["seealso"]       = "domSetStartPos, domClearStartPos, domSetStopPos";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "domSetStartPos";
// ********************
$f["syntax"][]  = <<<TEXT
int domSetStartPos ( int iStartPos );
TEXT;
$f["params"][]    = array ( "int", "iStartPos", "Value to use as temporary start position." );
$f["params"][]    = array ( "int", "RETURN", "TODO" );

$f["desc"]      = <<<TEXT
TODO: Not implemented yet, but will be soon.
Set a temporary start position from which domFind family functions will beging thier search. The start postion works as 
if the linearized dom really started here.
TEXT;
$f["seealso"]       = "domGetStartPos, domClearStartPos, domSetStopPos";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "domClearStartPos";
// ********************
$f["syntax"][]  = <<<TEXT
void domClearStartPos ();
TEXT;

$f["desc"]      = <<<TEXT
TODO: Not implemented yet, but will be soon.
Clears any temporary start position.
TEXT;
$f["seealso"]       = "domSetStartPos, domClearStartPos";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "domSetAtEnd";
// ********************
$f["syntax"][]  = <<<TEXT
void  domSetAtEnd ();
TEXT;

$f["desc"]      = <<<TEXT
Set current position to end, which means one position after last valid one. Used if you want to search backwards 
for a position startting from the end of the linearized dom.
TEXT;
$f["seealso"]       = "domAtEnd";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "domSeqCreate";
// ********************
$f["syntax"][]  = <<<TEXT
void domSeqCreate ( string sName, string sSequence, string sCompareFun,
                    int iPostMatchSteps, string sCommaChar  );
void domSeqCreate ( string sName, string sSequence, string sCompareFun,
                    int iPostMatchSteps  );
void domSeqCreate ( string sName, string sSequence, string sCompareFun );
void domSeqCreate ( string sName, string sSequence, int iPostMatchSteps );
void domSeqCreate ( string sName, string sSequence );
TEXT;
$f["params"][]    = array ( "string", "sName", "Name to assign for this dom sequence." );
$f["params"][]    = array ( "string", "sSequence", "Comma separated dom sequence to match. Like for eaxmple: 'DIV, class, MyClass'." );
$f["params"][]    = array ( "string", "sCompareFun", "(Default) compare operator to use for all nodes in the sequence." );
$f["params"][]    = array ( "string", "iPostMatchSteps", "Number of steps to move current position after matching the sequence when using domFind family functions." );
$f["params"][]    = array ( "string", "sCommaChar", "Alternative character to use as delimter instead of the deafult comma ','. Rarely needed." );

$f["desc"]      = <<<TEXT
Create a named dom sequence.
TEXT;
$f["seealso"]       = "domFind, domFindNext, outputValueFind, outputValueFindNext, doActionFind, doActionFindNext";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;

?>



------------------------------
--- Node actions ---
------------------------------

<?php

$f = array();
$f["name"] =
// **************************
       "Node actions";
// **************************

$f["type"]      = "group";
$f["desc"]      = <<<TEXT
Actions on current node like nodeClick() and other related action functions. These functions (except for nodeType) 
work on an ELEMENT node like DIV, A, INPUT, FORM etc. You can still call then even if the current dom position 
is another type of node like typically an attribute or attribute value. The functions here will 
automatically search for the most likely ELEMENT node and use that as target for your action but keeping 
the current dom position.

So for example if you have at dom snippet like this: 
'
<FORM action="form_action.asp" method="get">
   First name: <INPUT name="fname" type="text" /><br />
   <INPUT type="submit" value="Submit" />
 </FORM>
'
And want to set the first name field to "John" we could do a 'domFind( "INPUT, name, fname", "equals")', which 
would leave the current position at "fname" and then we call 'inputSet( "John" )'. The current position, the "fname" 
attribute value does not as such support the inputSet function, but it's "parent" INPUT element does and the 
inputSet function will find and use this. After calling 'inputSet( "John" )' the current dom position will still 
be at the "fname" attribute value. 

These functions all have a last last parameter called iSearchDir which by default is NEAREST_AUTO, that tries to find 
the most likely node the user wants to use for the action. If this is not working you can force it to search for 
the element node using a different strategy like for eaxmple 'inputSet( "John", NEAREST_PARENT )', see DomSearchDirModes. 
TEXT;
$f["note"][]   = "Dom element nodes like DIV, A, INPUT, FORM, BODY .. will always be in capital letters within the crawler and minercreator.";
$f["seealso"]   = "";
$a[] = $f;

$f = array();
$f["name"] =
// ********************
       "DomSearchDirModes";
// ********************
$f["type"]      = "enum";
$f["group"]     = "Node actions";

$f["values"][]	= array ( "NEAREST_FORWARD", "Search for the nearest node backwards that can be used as target for the action." );
$f["values"][]	= array ( "NEAREST_BACKWARD", "Search for the nearest node forwards that can be used as target for the action." );
$f["values"][]	= array ( "NEAREST_BOTH", "Search for the nearest node in both directions that can be used as target for the action." );
$f["values"][]	= array ( "NEAREST_PARENT", "Search for a parent node that can be used as target for the action." );
$f["values"][]	= array ( "NEAREST_AUTO", "Try to find the most likely ELEMENT node that the user wants the action applied to." );
$f["values"][]	= array ( "NEAREST_THIS_NODE", "Force to use node at current position. Make sure it's an ELEMENT node for example by using the iPostmatchSteps parameter in domFind and domSeqCreate." );
//$f["values"][]	= array ( "FWD", "TODO: What is this used for?" );
//$f["values"][]	= array ( "REV", "TODO: What is this used for?" );

$f["desc"]      = <<<TEXT
When using one of the 'Node actions' you sometimes need to supply extra information so that the action gets 
applied to the correct ELEMENT node. Most often you would not supply an extra parameter to for example nodeClick because 
the default form is equivalent to: 'nodeClick(NEAREST_AUTO)'. If for some reason you know the ELEMENT node you need to 
click is an A tag immediately following your current dom positon you could do: 'nodeClick(NEAREST_FORWARD)'. 
See more explanation in the section about 'Node actions'
TEXT;
$f["seealso"]       = "'Node actions'";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;



// --- Common function properties ---
$f_common = array();
$f_common["type"]      = "function";
$f_common["group"]     = "Node actions";


$f = $f_common;
$f["name"] =
// ********************
       "nodeType";
// ********************
$f["syntax"][]  = <<<TEXT
int nodeType();
TEXT;
$f["params"][]    = array ( "int", "RETURN", "Node type of current node, see DomNodeTypes." );

$f["desc"]      = <<<TEXT
Get the type of the current dom node. This function is actually not an action, but it is related to this group of function 
since it operates on the current node.
TEXT;

$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "nodeClick";
// ********************
$f["syntax"][]  = <<<TEXT
bool nodeClick ( int iSearchDir = NEAREST_AUTO, bool bLoadHref = true );
TEXT;
$f["params"][]    = array ( "int", "iSearchDir", "Specify how to search for the ELEMENT node to apply the action. See DomSearchDirModes and 'Node actions'." );
$f["params"][]    = array ( "bool", "bLoadHref", "Allow the nodeClick function to directly load the href value of an A element if present." );
$f["params"][]    = array ( "bool", "RETURN", "True if a node could be found and the action applied." );

$f["desc"]      = <<<TEXT
Perform a mouse "click" operation on the "current node". Often you will perform this click on a A ELEMENT 
in which case you will get the href=link-to-some-page URL loaded. If for some reason you don't want this
, might be the case if javascript modifies the url and load page directly, you can set the last 
parameter to false. 
Most often you would simply call this function like this: 'nodeClick();' and leave the parameters to their 
default values.
TEXT;
$f["seealso"]       = "doAction";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;



$f = $f_common;
$f["name"] =
// ********************
       "nodeMouseEvent";
// ********************
$f["syntax"][]  = <<<TEXT
bool nodeMouseEvent ( string sEvent, int iButton, int iSearchDir );
bool nodeMouseEvent ( string sEvent, int iSearchDir);
bool nodeMouseEvent ( string sEvent  );
TEXT;
$f["params"][]    = array ( "string", "sEvent", "W3C event name. TODO: Add list of events supported." );
$f["params"][]    = array ( "int", "iButton", "Specify mouse button: 0=>left, 1=>right, 2=>middle" );
$f["params"][]    = array ( "int", "iSearchDir", "Specify how to search for the ELEMENT node to apply the action. See DomSearchDirModes and 'Node actions'." );
$f["params"][]    = array ( "bool", "RETURN", "True if a node could be found and the action applied." );

$f["desc"]      = <<<TEXT
Send mouse event to "current node". 
TODO: Add list of events supported. 
TEXT;
$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "inputSet";
// ********************
$f["syntax"][]  = <<<TEXT
bool inputSet ( string sValue, int iSearchDir = NEAREST_AUTO );
bool inputSet ( int    iValue, int iSearchDir = NEAREST_AUTO );
TEXT;
$f["params"][]    = array ( "string", "sValue", "String value to set." );
$f["params"][]    = array ( "int", "iValue", "Integer value to set" );
$f["params"][]    = array ( "int", "iSearchDir", "Specify how to search for the ELEMENT node to apply the action. See DomSearchDirModes and 'Node actions'." );
$f["params"][]    = array ( "bool", "RETURN", "True if a node could be found and the action applied." );

$f["desc"]      = <<<TEXT
Set INPUT element to a value using current node as starting point or current node in case it is an INPUT. 
TEXT;
$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "formSubmit";
// ********************
$f["syntax"][]  = <<<TEXT
bool formSubmit ( int iSearchDir = NEAREST_AUTO );
TEXT;
$f["params"][]    = array ( "int", "iSearchDir", "Specify how to search for the ELEMENT node to apply the action. See DomSearchDirModes and 'Node actions'." );
$f["params"][]    = array ( "bool", "RETURN", "True if a node could be found and the action applied." );

$f["desc"]      = <<<TEXT
Perform submit on FORM element using current node as starting point or current node in case it is a FORM. 
TEXT;
$f["seealso"]       = "formReset";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "formReset";
// ********************
$f["syntax"][]  = <<<TEXT
bool formReset ( int iSearchDir = NEAREST_AUTO );
TEXT;
$f["params"][]    = array ( "int", "iSearchDir", "Specify how to search for the ELEMENT node to apply the action. See DomSearchDirModes and 'Node actions'." );
$f["params"][]    = array ( "bool", "RETURN", "True if a node could be found and the action applied." );

$f["desc"]      = <<<TEXT
Perform reset on FORM element using current node as starting point or current node in case it is a FORM. 
TEXT;
$f["seealso"]       = "formSubmit";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "selectLength";
// ********************
$f["syntax"][]  = <<<TEXT
int selectLength ( int iSearchDir = NEAREST_AUTO );
TEXT;
$f["params"][]    = array ( "int", "iSearchDir", "Specify how to search for the ELEMENT node to apply the action. See DomSearchDirModes and 'Node actions'." );
$f["params"][]    = array ( "int", "RETURN", "Lenght of SELECT element." );

$f["desc"]      = <<<TEXT
Get number of options in a SELECT element using current node as starting point or current node in case it is a SELECT. 
TEXT;
$f["seealso"]       = "selectIndex, selectSelectedIndex";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "selectSelectedIndex";
// ********************
$f["syntax"][]  = <<<TEXT
int selectSelectedIndex ( int iSearchDir = NEAREST_AUTO );
TEXT;
$f["params"][]    = array ( "int", "iSearchDir", "Specify how to search for the ELEMENT node to apply the action. See DomSearchDirModes and 'Node actions'." );
$f["params"][]    = array ( "int", "RETURN", "Index of currenly selected option." );

$f["desc"]      = <<<TEXT
Get index of current selected option in a SELECT element using current node as starting point or current node in case it is a SELECT. 
TEXT;
$f["seealso"]       = "selectSelectedDomPos, selectLength";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "selectSelectedDomPos";
// ********************
$f["syntax"][]  = <<<TEXT
int selectSelectedDomPos ( int iSearchDir = NEAREST_AUTO );
TEXT;
$f["params"][]    = array ( "int", "iSearchDir", "Specify how to search for the ELEMENT node to apply the action. See DomSearchDirModes and 'Node actions'." );
$f["params"][]    = array ( "int", "RETURN", "Dom position of currently selected option." );

$f["desc"]      = <<<TEXT
Get dom position of current selected OPTION node in a SELECT element using current node as starting point or current node in case it is a SELECT. 
TEXT;
$f["seealso"]       = "selectSelectedIndex, selectLength";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "selectIndex";
// ********************
$f["syntax"][]  = <<<TEXT
bool selectIndex ( int iIndex, int iSearchDir = NEAREST_AUTO );
TEXT;
$f["params"][]    = array ( "int", "iIndex", "Index of option to select." );
$f["params"][]    = array ( "int", "iSearchDir", "Specify how to search for the ELEMENT node to apply the action. See DomSearchDirModes and 'Node actions'." );
$f["params"][]    = array ( "bool", "RETURN", "True if a node could be found and the action applied." );

$f["desc"]      = <<<TEXT
Select option in a SELECT element using current node as starting point or current node in case it is a SELECT. 
TEXT;
$f["seealso"]       = "selectOption, selectSelectedIndex, selectLength";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "selectOption";
// ********************
$f["syntax"][]  = <<<TEXT
bool selectOption ( int iSearchDir = NEAREST_AUTO );
TEXT;
$f["params"][]    = array ( "int", "iSearchDir", "Specify how to search for the ELEMENT node to apply the action. See DomSearchDirModes and 'Node actions'." );
$f["params"][]    = array ( "bool", "RETURN", "True if a node could be found and the action applied." );

$f["desc"]      = <<<TEXT
Select OPTION in a SELECT element using current node as starting point or current node in case it is an OPTION. 
TEXT;
$f["seealso"]       = "selectIndex, selectSelectedIndex, selectLength";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "doAction";
// ********************
$f["syntax"][]  = <<<TEXT
bool doAction ( string sAction, string sParam1, string sParam2, int iSearchDir );
bool doAction ( string sAction, string sParam1, string sParam2 );
bool doAction ( string sAction, string sParam1, int iSearchDir = NEAREST_AUTO );
bool doAction ( string sAction, int iSearchDir = NEAREST_AUTO );
TEXT;
$f["params"][]    = array ( "string", "sAction", "Action to perform. Can be a built-in: click formSubmit inputSet ..., a named action: domActionCreate, or a PHP function." );
$f["params"][]    = array ( "string", "sParam1", "Optional parameter 1 for the action if needed." );
$f["params"][]    = array ( "string", "sParam2", "Optional parameter 2 for the action if needed." );
$f["params"][]    = array ( "int", "iSearchDir", "Specify how to search for the ELEMENT node to apply the action. See DomSearchDirModes and 'Node actions'." );
$f["params"][]    = array ( "bool", "RETURN", "True if a node could be found and the action applied." );

$f["desc"]      = <<<TEXT
Execute named action like "click", "inputSet" etc. The action can also refer to a named action created using 
domActionCreate or to a user defined PHP function.
TEXT;
$f["seealso"]       = "domActionCreate, doActionFind, doActionFindNext";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "doActionFindNext";
// ********************
$f["syntax"][]  = <<<TEXT
bool doActionFindNext ( int iCount, string sSequence, string sAction, string sParam1, string sParam2, int iSearchDir );
bool doActionFindNext ( int iCount, string sSequence, string sAction, string sParam1, string sParam2 );
bool doActionFindNext ( int iCount, string sSequence, string sAction, string sParam1, int iSearchDir = NEAREST_AUTO );
bool doActionFindNext ( int iCount, string sSequence, string sAction, int iSearchDir = NEAREST_AUTO );
TEXT;
$f["params"][]    = array ( "int", "iCount", "Stop 1st, 2nd, 3rd ... position that matches the sequence. Can be negative to search backwards." );
$f["params"][]    = array ( "string", "sSequence", "Dom sequence. Can be one of: PHP function, named dom sequence, direct specified" );
$f["params"][]    = array ( "string", "sAction", "Action to perform. Can be a built-in: click formSubmit inputSet ..., a named action: domActionCreate, or a PHP function." );
$f["params"][]    = array ( "string", "sParam1", "Optional parameter 1 for the action if needed." );
$f["params"][]    = array ( "string", "sParam2", "Optional parameter 2 for the action if needed." );
$f["params"][]    = array ( "int", "iSearchDir", "Specify how to search for the ELEMENT node to apply the action. See DomSearchDirModes and 'Node actions'." );
$f["params"][]    = array ( "bool", "RETURN", "True if a node could be found and the action applied." );

$f["desc"]      = <<<TEXT
Call domFindNext on a sequence and execute a named action like "click", "inputSet" etc. The action can also 
refer to a named action created using domActionCreate or to a user defined PHP function.
TEXT;
$f["seealso"]       = "domActionCreate, doAction, doActionFind";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "doActionFind";
// ********************
$f["syntax"][]  = <<<TEXT
bool doActionFind ( int iCount, string sSequence, string sAction, string sParam1, string sParam2, int iSearchDir );
bool doActionFind ( int iCount, string sSequence, string sAction, string sParam1, string sParam2 );
bool doActionFind ( int iCount, string sSequence, string sAction, string sParam1, int iSearchDir = NEAREST_AUTO );
bool doActionFind ( int iCount, string sSequence, string sAction, int iSearchDir = NEAREST_AUTO );
TEXT;
$f["params"][]    = array ( "int", "iCount", "Stop 1st, 2nd, 3rd ... position that matches the sequence. Can be negative to search backwards." );
$f["params"][]    = array ( "string", "sSequence", "Dom sequence. Can be one of: PHP function, named dom sequence, direct specified" );
$f["params"][]    = array ( "string", "sAction", "Action to perform. Can be a built-in: click formSubmit inputSet ..., a named action: domActionCreate, or a PHP function." );
$f["params"][]    = array ( "string", "sParam1", "Optional parameter 1 for the action if needed." );
$f["params"][]    = array ( "string", "sParam2", "Optional parameter 2 for the action if needed." );
$f["params"][]    = array ( "int", "iSearchDir", "Specify how to search for the ELEMENT node to apply the action. See DomSearchDirModes and 'Node actions'." );
$f["params"][]    = array ( "bool", "RETURN", "True if a node could be found and the action applied." );

$f["desc"]      = <<<TEXT
Call domFind on a sequence and execute a named action like "click", "inputSet" etc. The action can also 
refer to a named action created using domActionCreate or to a user defined PHP function.
TEXT;
$f["seealso"]       = "domActionCreate,doAction, doActionFindNext";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "domActionCreate";
// ********************
$f["syntax"][]  = <<<TEXT
bool domActionCreate ( string sName, string sAction, string sParam1, string sParam2, int iSearchDir );
bool domActionCreate ( string sName, string sAction, string sParam1, string sParam2 );
bool domActionCreate ( string sName, string sAction, string sParam1, int iSearchDir = NEAREST_AUTO );
bool domActionCreate ( string sName, string sAction, int iSearchDir = NEAREST_AUTO );
TEXT;
$f["params"][]    = array ( "string", "sName", "Name to use for this action." );
$f["params"][]    = array ( "string", "sAction", "Action to perform. Can be a built-in: click formSubmit inputSet ... or a PHP function." );
$f["params"][]    = array ( "string", "sParam1", "Optional parameter 1 for the action if needed." );
$f["params"][]    = array ( "string", "sParam2", "Optional parameter 2 for the action if needed." );
$f["params"][]    = array ( "int", "iSearchDir", "Specify how to search for the ELEMENT node to apply the action. See DomSearchDirModes and 'Node actions'." );
$f["params"][]    = array ( "bool", "RETURN", "True if a node could be found and the action applied." );

$f["desc"]      = <<<TEXT
Created a named action that can be referred to later. Usefull when dealing with crawler templates. 
The action can be either one of the built-in like "click", "inputSet" etc. or a user defined PHP function.
TEXT;
$f["seealso"]       = "doAction, doActionFind, doActionFindNext";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;

?>


------------------------------
--- Value functions ---
------------------------------

<?php

$f = array();
$f["name"] =
// **************************
       "Value functions";
// **************************

$f["type"]      = "group";
$f["desc"]      = <<<TEXT
Functions for getting the the current value, current node value or the node value of a specified 
dom position. The value can optionally be filtered through modifiers/manipulators like, trimEnds, eraseAll, 
prepend, append, etc.
TEXT;
$f["note"][]   = "";
$f["seealso"]   = "";
$a[] = $f;


// --- Common function properties ---
$f_common = array();
$f_common["type"]      = "function";
$f_common["group"]     = "Value functions";


$f = $f_common;
$f["name"] =
// ********************
       "modifierCreate";
// ********************
$f["syntax"][]  = <<<TEXT
void modifierCreate  ( string sModifierID, string sManipFunID, string sManipParam1,
                       string sManipParam2, string sManipParam3, string sManipParam4 );
void modifierCreate  ( string sModifierID, string sManipFunID, string sManipParam1,
                       string sManipParam2, string sManipParam3 );
void modifierCreate  ( string sModifierID, string sManipFunID, string sManipParam1,
                       string sManipParam2 );
void modifierCreate  ( string sModifierID, string sManipFunID, string sManipParam1 );
void modifierCreate  ( string sModifierID, string sManipFunID );
TEXT;
$f["params"][]    = array ( "string", "sModifierID", "Name to use for this modifier." );
$f["params"][]    = array ( "string", "sManipFunID", "String manipulation to perform. Can be a built-in: trim, prepend eraseAll ... or a PHP function." );
$f["params"][]    = array ( "string", "sManipParam1", "Optional parameter 1 for the manipulation function if needed." );
$f["params"][]    = array ( "string", "sManipParam2", "Optional parameter 2 for the manipulation function if needed." );
$f["params"][]    = array ( "string", "sManipParam3", "Optional parameter 3 for the manipulation function if needed." );
$f["params"][]    = array ( "string", "sManipParam4", "Optional parameter 4 for the manipulation function if needed." );

$f["desc"]      = <<<TEXT
Create named modifier/manipulator that can be referred to later.
TEXT;

$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "valueSet";
// ********************
$f["syntax"][]  = <<<TEXT
void valueSet ( string sValue );
TEXT;
$f["params"][]    = array ( "string", "sValue", "New value to assign to current value." );

$f["desc"]      = <<<TEXT
Force "current value" to specific value.
TEXT;

$f["seealso"]       = "valueGet, nodeValue";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "valueGet";
// ********************
$f["syntax"][]  = <<<TEXT
string valueGet ( string sModifierID, string sManipParam1, string sManipParam2,
                  string sManipParam3, string sManipParam4 );
string valueGet ( string sModifierID,string sManipParam1, string sManipParam2,
                string sManipParam3 );
string valueGet ( string sModifierID,string sManipParam1, string sManipParam2 );
string valueGet ( string sModifierID,string sManipParam1 );
string valueGet ( string sModifierID );
string valueGet ();
TEXT;
$f["params"][]    = array ( "string", "sModifierID", "String manipulation to perform. Can be a built-in: trim, prepend eraseAll ..., A named modifier created with modifierCreate or a PHP function." );
$f["params"][]    = array ( "string", "sManipParam1", "Optional parameter 1 for the manipulation function if needed." );
$f["params"][]    = array ( "string", "sManipParam2", "Optional parameter 2 for the manipulation function if needed." );
$f["params"][]    = array ( "string", "sManipParam3", "Optional parameter 3 for the manipulation function if needed." );
$f["params"][]    = array ( "string", "sManipParam4", "Optional parameter 4 for the manipulation function if needed." );

$f["desc"]      = <<<TEXT
Get current value optionally filtered through a manipulator function. Note that the current value is not always identical to 
nodeValue, since it can be modified using a number of methods like e.g. : valueSet, valueModify or most of the 'Text functions' 
TEXT;
$f["seealso"]       = "valueSet, nodeValue";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "valueCompare";
// ********************
$f["syntax"][]  = <<<TEXT
bool valueCompare ( string sPattern, string sCompareFun, string sModifierID,
                    string sManipParam1, string sManipParam2, string sManipParam3,
                    string sManipParam4 );
bool valueCompare ( string sPattern, string sCompareFun, string sModifierID,
                    string sManipParam1, string sManipParam2, string sManipParam3 );
bool valueCompare ( string sPattern, string sCompareFun, string sModifierID,
                    string sManipParam1, string sManipParam2 );
bool valueCompare ( string sPattern, string sCompareFun, string sModifierID,
                    string sManipParam1 );
bool valueCompare ( string sPattern, string sCompareFun, string sModifierID );
bool valueCompare ( string sPattern, string sCompareFun );
TEXT;
$f["params"][]    = array ( "string", "sPattern", "Pattern to use with compare function/operator." );
$f["params"][]    = array ( "string", "sCompareFun", "Compare function/operator to use. For example: contains, endsWith, ...'" );
$f["params"][]    = array ( "string", "sModifierID", "String manipulation to perform. Can be a built-in: trim, prepend eraseAll ..., A named modifier created with modifierCreate or a PHP function." );
$f["params"][]    = array ( "string", "sManipParam1", "Optional parameter 1 for the manipulation function if needed." );
$f["params"][]    = array ( "string", "sManipParam2", "Optional parameter 2 for the manipulation function if needed." );
$f["params"][]    = array ( "string", "sManipParam3", "Optional parameter 3 for the manipulation function if needed." );
$f["params"][]    = array ( "string", "sManipParam4", "Optional parameter 4 for the manipulation function if needed." );

$f["desc"]      = <<<TEXT
Compare current value using a compare function optionally filtering current value through a manipulator function. Note that the current value is not always identical to 
nodeValue, since it can be modified using a number of methods like e.g. : valueSet, valueModify or most of the 'Text functions' 
TEXT;
$f["seealso"]       = "valueGet, nodeValue";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "valueModify";
// ********************
$f["syntax"][]  = <<<TEXT
string valueModify ( string sModifierID, string sManipParam1, string sManipParam2,
                     string sManipParam3, string sManipParam4 );
string valueModify ( string sModifierID,string sManipParam1, string sManipParam2,
                     string sManipParam3 );
string valueModify ( string sModifierID,string sManipParam1, string sManipParam2 );
string valueModify ( string sModifierID,string sManipParam1 );
string valueModify ( string sModifierID );
TEXT;
$f["params"][]    = array ( "string", "sModifierID", "String manipulation to perform. Can be a built-in: trim, prepend eraseAll ..., A named modifier created with modifierCreate or a PHP function." );
$f["params"][]    = array ( "string", "sManipParam1", "Optional parameter 1 for the manipulation function if needed." );
$f["params"][]    = array ( "string", "sManipParam2", "Optional parameter 2 for the manipulation function if needed." );
$f["params"][]    = array ( "string", "sManipParam3", "Optional parameter 3 for the manipulation function if needed." );
$f["params"][]    = array ( "string", "sManipParam4", "Optional parameter 4 for the manipulation function if needed." );

$f["desc"]      = <<<TEXT
Modify current value through a manipulator function.  
TEXT;
$f["seealso"]       = "valueSet, valueGet, nodeValue";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "nodeValuePos";
// ********************
$f["syntax"][]  = <<<TEXT
string    nodeValuePos ( int iDomPos, string sModifierID, string sManipParam1,
                         string sManipParam2, string sManipParam3,
                         string sManipParam4 );
string    nodeValuePos ( int iDomPos, string sModifierID, string sManipParam1,
                         string sManipParam2, string sManipParam3 );
string    nodeValuePos ( int iDomPos, string sModifierID, string sManipParam1,
                         string sManipParam2 );
string    nodeValuePos ( int iDomPos, string sModifierID, string sManipParam1 );
string    nodeValuePos ( int iDomPos, string sModifierID );
string    nodeValuePos ( int iDomPos );
TEXT;
$f["params"][]    = array ( "int", "iDomPos", "Dom position of node to get value from." );
$f["params"][]    = array ( "string", "sModifierID", "String manipulation to perform. Can be a built-in: trim, prepend eraseAll ..., A named modifier created with modifierCreate or a PHP function." );
$f["params"][]    = array ( "string", "sManipParam1", "Optional parameter 1 for the manipulation function if needed." );
$f["params"][]    = array ( "string", "sManipParam2", "Optional parameter 2 for the manipulation function if needed." );
$f["params"][]    = array ( "string", "sManipParam3", "Optional parameter 3 for the manipulation function if needed." );
$f["params"][]    = array ( "string", "sManipParam4", "Optional parameter 4 for the manipulation function if needed." );

$f["desc"]      = <<<TEXT
Get node value of specified dom position optionally filtered through a manipulator function. 
TEXT;
$f["seealso"]       = "valueSet, nodeValue";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "nodeValue";
// ********************
$f["syntax"][]  = <<<TEXT
string nodeValue        ( string sModifierID, string sManipParam1,
                          string sManipParam2, string sManipParam3,
                          string sManipParam4 );
string nodeValue        ( string sModifierID,string sManipParam1,
                          string sManipParam2, string sManipParam3 );
string nodeValue        ( string sModifierID, string sManipParam1,
                          string sManipParam2 );
string nodeValue        ( string sModifierID, string sManipParam1 );
string nodeValue        ( string sModifierID );
string nodeValue        ();
TEXT;
$f["params"][]    = array ( "string", "sModifierID", "String manipulation to perform. Can be a built-in: trim, prepend eraseAll ..., A named modifier created with modifierCreate or a PHP function." );
$f["params"][]    = array ( "string", "sManipParam1", "Optional parameter 1 for the manipulation function if needed." );
$f["params"][]    = array ( "string", "sManipParam2", "Optional parameter 2 for the manipulation function if needed." );
$f["params"][]    = array ( "string", "sManipParam3", "Optional parameter 3 for the manipulation function if needed." );
$f["params"][]    = array ( "string", "sManipParam4", "Optional parameter 4 for the manipulation function if needed." );

$f["desc"]      = <<<TEXT
Get node value current dom position optionally filtered through a manipulator function. 
TEXT;
$f["seealso"]       = "valueSet, nodeValue";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "nodeValueParent";
// ********************
$f["syntax"][]  = <<<TEXT
string nodeValueParent     	( int iLevelsUp, string sModifierID, string sManipParam1, 
								 string sManipParam2, string sManipParam3,string sManipParam4 );
string nodeValueParent    	( int iLevelsUp, string sModifierID, string sManipParam1,
                              string sManipParam2,string sManipParam3 );
string nodeValueParent      ( int iLevelsUp, string sModifierID, string sManipParam1,
                              string sManipParam2 );
string nodeValueParent      ( int iLevelsUp, string sModifierID, string sManipParam1 );
string nodeValueParent      ( int iLevelsUp, string sModifierID );
string nodeValueParent      ( int iLevelsUp );
TEXT;
$f["params"][]    = array ( "int", "iLevelsUp", "Number of parent levels up from here." );
$f["params"][]    = array ( "string", "sModifierID", "String manipulation to perform. Can be a built-in: trim, prepend eraseAll ..., A named modifier created with modifierCreate or a PHP function." );
$f["params"][]    = array ( "string", "sManipParam1", "Optional parameter 1 for the manipulation function if needed." );
$f["params"][]    = array ( "string", "sManipParam2", "Optional parameter 2 for the manipulation function if needed." );
$f["params"][]    = array ( "string", "sManipParam3", "Optional parameter 3 for the manipulation function if needed." );
$f["params"][]    = array ( "string", "sManipParam4", "Optional parameter 4 for the manipulation function if needed." );

$f["desc"]      = <<<TEXT
Get node value of specified parent level of current position optionally filtered through a manipulator function. 
TEXT;
$f["seealso"]       = "valueSet, nodeValue";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "nodeCompare";
// ********************
$f["syntax"][]  = <<<TEXT
bool nodeCompare ( string sPattern, string sCompareFun, string sModifierID,
                   string sManipParam1, string sManipParam2, string sManipParam3,
                   string sManipParam4 );
bool nodeCompare ( string sPattern, string sCompareFun, string sModifierID,
                   string sManipParam1, string sManipParam2, string sManipParam3 );
bool nodeCompare ( string sPattern, string sCompareFun, string sModifierID,
                   string sManipParam1, string sManipParam2 );
bool nodeCompare ( string sPattern, string sCompareFun, string sModifierID,
                   string sManipParam1 );
bool nodeCompare ( string sPattern, string sCompareFun, string sModifierID );
bool nodeCompare ( string sPattern, string sCompareFun );
TEXT;
$f["params"][]    = array ( "string", "sPattern", "Pattern to use with compare function/operator." );
$f["params"][]    = array ( "string", "sCompareFun", "Compare function/operator to use. For example: contains, endsWith, ...'" );
$f["params"][]    = array ( "string", "sModifierID", "String manipulation to perform. Can be a built-in: trim, prepend eraseAll ..., A named modifier created with modifierCreate or a PHP function." );
$f["params"][]    = array ( "string", "sManipParam1", "Optional parameter 1 for the manipulation function if needed." );
$f["params"][]    = array ( "string", "sManipParam2", "Optional parameter 2 for the manipulation function if needed." );
$f["params"][]    = array ( "string", "sManipParam3", "Optional parameter 3 for the manipulation function if needed." );
$f["params"][]    = array ( "string", "sManipParam4", "Optional parameter 4 for the manipulation function if needed." );

$f["desc"]      = <<<TEXT
Compare current node value using a compare function optionally filtering current value through a manipulator function. Note that the current value is not always identical to 
nodeValue, since it can be modified using a number of methods like e.g. : valueSet, valueModify or most of the 'Text functions' 
TEXT;
$f["seealso"]       = "valueCompare, valueGet, nodeValue";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;
?>

-----------------------
--- Parse functions ---
-----------------------

<?php

$f = array();
$f["name"] =
// **************************
       "Parse functions";
// **************************

$f["type"]      = "group";
$f["desc"]      = <<<TEXT
Functions for primitive parsing of the current value. For most of theese functions the general 
idea is that we want to pinpoint a part of the current value string by moving a begin and end 
marker to sort of "narrow-in" the wanted part. 
For example if we want to find the year part of a current value string like this: 
"was founded 1987 in Kansas" the idea is that we want to move 
the begin marker to rigt before the year and the end marker to right after:

Using actual findBegin, findEnd function you have:
- 'findBegin(1, "founded" )' gives: " 1987 in Kansas".  
- 'findEnd(1, "in" )' gives: " 1987 " 
This current value will by default will be trimmed to "1987" if you use 
for example outputValue("year") or valueGet().


TEXT;
$f["note"][]   = "";
$f["seealso"]   = "";
$a[] = $f;


$f = array();
$f["name"] =
// ********************
       "TextMatchPositions";
// ********************
$f["type"]      = "enum";
$f["group"]     = "Parse functions";

$f["values"][]	= array ( "MATCH_FIRST", "Set position after a match to the first character in the match." );
$f["values"][]	= array ( "MATCH_LAST", "Set position after a match to the last character in the match." );

$f["desc"]      = <<<TEXT
TEXT;
$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


// --- Common function properties ---
$f_common = array();
$f_common["type"]      = "function";
$f_common["group"]     = "Parse functions";


$f = $f_common;
$f["name"] =
// ********************
       "parseRegex";
// ********************
$f["syntax"][]  = <<<TEXT
bool parseRegex ( int iCount, string sRegex,
                  int postMarkerPos = MATCH_FIRST );
TEXT;
$f["params"][]    = array ( "int", "iCount", "Stop 1st, 2nd, 3rd ... position that matches the sequence. Can be negative to search backwards." );
$f["params"][]    = array ( "string", "sRegex", "Regular expression string." );
$f["params"][]    = array ( "enum", "postMarkerPos", "Specify if position in current value string should be before the first character in match or at last position in match. See: TextMatchPositions." );
$f["params"][]    = array ( "bool", "RETURN", "True if found." );

$f["desc"]      = <<<TEXT
Set current value to the matching part of regular expression. For example you could parse for a year using :
'parseRegex(1, "\d\d\d\d")'. If we assume current node value is "was founded 1987 in Kansas", the current 
value would after the parseRegex be "1987".
value to
TEXT;

$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "iparseRegex";
// ********************
$f["syntax"][]  = <<<TEXT
bool iparseRegex ( int iCount, string sRegex,
                   int postMarkerPos = MATCH_FIRST );
TEXT;
$f["params"][]    = array ( "int", "iCount", "Stop 1st, 2nd, 3rd ... position that matches the sequence. Can be negative to search backwards." );
$f["params"][]    = array ( "string", "sRegex", "Regular expression string." );
$f["params"][]    = array ( "enum", "postMarkerPos", "Specify if position in current value string should be before the first character in match or at last position in match. See: TextMatchPositions." );
$f["params"][]    = array ( "bool", "RETURN", "True if found." );

$f["desc"]      = <<<TEXT
Set current value to the matching part of regular expression, ignoring casing. For example you could parse for a year using :
'parseRegex(1, "\d\d\d\d")'. If we assume current node value is "was founded 1987 in Kansas", the current 
value would after the parseRegex be "1987".
value to
TEXT;

$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "parseToRegex";
// ********************
$f["syntax"][]  = <<<TEXT
bool parseToRegex ( int iCount, string sRegex,
                    int postMarkerPos = MATCH_FIRST );
TEXT;
$f["params"][]    = array ( "int", "iCount", "Stop 1st, 2nd, 3rd ... position that matches the sequence. Can be negative to search backwards." );
$f["params"][]    = array ( "string", "sRegex", "Regular expression string." );
$f["params"][]    = array ( "enum", "postMarkerPos", "Specify if position in current value string should be before the first character in match or at last position in match. See: TextMatchPositions." );
$f["params"][]    = array ( "bool", "RETURN", "True if found." );

$f["desc"]      = <<<TEXT
Set current value to the first part of the string until the the part that matches the regular expression. 
For example you have a current value of : "was founded 1987 in Kansas".
Then 'parseToRegex(1, "\d\d\d\d", MATCH_FIRST)' gives "was founded " 
and 'parseToRegex(1, "\d\d\d\d", MATCH_LAST)' gives "was founded 1887".  
TEXT;

$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "iparseToRegex";
// ********************
$f["syntax"][]  = <<<TEXT
bool iparseToRegex ( int iCount, string sRegex,
                     int postMarkerPos = MATCH_FIRST );
TEXT;
$f["params"][]    = array ( "int", "iCount", "Stop 1st, 2nd, 3rd ... position that matches the sequence. Can be negative to search backwards." );
$f["params"][]    = array ( "string", "sRegex", "Regular expression string." );
$f["params"][]    = array ( "enum", "postMarkerPos", "Specify if position in current value string should be before the first character in match or at last position in match. See: TextMatchPositions." );
$f["params"][]    = array ( "bool", "RETURN", "True if found." );

$f["desc"]      = <<<TEXT
Set current value to the first part of the string until the the part that matches the 
regular expression, ignoring casing. 
For example you have a current value of : "was founded 1987 in Kansas".
Then 'parseToRegex(1, "\d\d\d\d", MATCH_FIRST)' gives "was founded " 
and 'parseToRegex(1, "\d\d\d\d", MATCH_LAST)' gives "was founded 1887".  
TEXT;

$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "parseToString";
// ********************
$f["syntax"][]  = <<<TEXT
bool parseToString ( int iCount, string sSubstring,
                     int postMarkerPos = MATCH_FIRST );
TEXT;
$f["params"][]    = array ( "int", "iCount", "Stop 1st, 2nd, 3rd ... position that matches the sequence. Can be negative to search backwards." );
$f["params"][]    = array ( "string", "sSubstring", "Substring to search for." );
$f["params"][]    = array ( "enum", "postMarkerPos", "Specify if position in current value string should be before the first character in match or at last position in match. See: TextMatchPositions." );
$f["params"][]    = array ( "bool", "RETURN", "True if found." );

$f["desc"]      = <<<TEXT
Set current value to the first part of the string until the the part that matches the substring. 
For example you have a current value of : "was founded 1987 in Kansas".
Then 'parseToString(1, "in", MATCH_FIRST)' gives "was founded 1987 " 
and 'parseToString(1, "in", MATCH_LAST)' gives "was founded 1987 in ".  
TEXT;

$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "iparseToString";
// ********************
$f["syntax"][]  = <<<TEXT
bool iparseToString ( int iCount, string sSubstring,
                      int postMarkerPos = MATCH_FIRST );
TEXT;
$f["params"][]    = array ( "int", "iCount", "Stop 1st, 2nd, 3rd ... position that matches the sequence. Can be negative to search backwards." );
$f["params"][]    = array ( "string", "sSubstring", "Substring to search for." );
$f["params"][]    = array ( "enum", "postMarkerPos", "Specify if position in current value string should be before the first character in match or at last position in match. See: TextMatchPositions." );
$f["params"][]    = array ( "bool", "RETURN", "True if found." );

$f["desc"]      = <<<TEXT
Set current value to the first part of the string until the the part that matches the substring, 
ignoring casing.  
For example you have a current value of : "was founded 1987 in Kansas".
Then 'parseToString(1, "in", MATCH_FIRST)' gives "was founded 1987 " 
and 'parseToString(1, "in", MATCH_LAST)' gives "was founded 1987 in ".  
TEXT;

$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "parseToEnd";
// ********************
$f["syntax"][]  = <<<TEXT
bool parseToEnd ();
TEXT;
$f["params"][]    = array ( "bool", "RETURN", "True." );

$f["desc"]      = <<<TEXT
Parse to end of string.
TODO: More explanation of when this function is usefull.
TEXT;
$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "getParseMatch";
// ********************
$f["syntax"][]  = <<<TEXT
string getParseMatch ( int iMatchNumber );
TEXT;
$f["params"][]    = array ( "int", "iMatchNumber", "Captured parse match index number to get. " );
$f["params"][]    = array ( "string", "RETURN", "The captured string from the parse match." );

$f["desc"]      = <<<TEXT
Get captured parse match.
TEXT;
$f["seealso"]       = "getParseMatchCount";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "getParseRest";
// ********************
$f["syntax"][]  = <<<TEXT
string getParseRest ();
TEXT;
$f["params"][]    = array ( "string", "RETURN", "Rest of string following the match." );

$f["desc"]      = <<<TEXT
Get rest of the string following a succesfull regular expression match.
TEXT;
$f["seealso"]       = "getParseMatch";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "getParseMatchCount";
// ********************
$f["syntax"][]  = <<<TEXT
int getParseMatchCount ();
TEXT;
$f["params"][]    = array ( "int", "RETURN", "Number of captured matches." );

$f["desc"]      = <<<TEXT
Get number of captured matches.
TEXT;
$f["seealso"]       = "getParseMatch";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "textNewSearch";
// ********************
$f["syntax"][]  = <<<TEXT
void textNewSearch ();
TEXT;

$f["desc"]      = <<<TEXT
Reset begin and en markers to begin and end of the current value string. This is done automatically 
after any domFind, valueSet, valueModify functions so you should only need call it when you need to do 
multiple rounds of parsing on the same value.
TEXT;
$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "findBegin";
// ********************
$f["syntax"][]  = <<<TEXT
bool findBegin ( int iCount, string sSubstring
               , int postMarkerPos = MATCH_LAST );                    
TEXT;
$f["params"][]    = array ( "int", "iCount", "Stop 1st, 2nd, 3rd ... position that matches the sequence. Can be negative to search backwards." );
$f["params"][]    = array ( "string", "sSubstring", "Substring to search for." );
$f["params"][]    = array ( "enum", "postMarkerPos", "Specify if position in current value string should be before the first character in match or at last position in match. See: TextMatchPositions." );
$f["params"][]    = array ( "bool", "RETURN", "True if found." );

$f["desc"]      = <<<TEXT
Move begin marker to the substring starting from beginning of current value string.  
For example you have a current value of : "was founded 1987 in Kansas".
Then 'findBegin(1, "founded", MATCH_FIRST)' gives "founded 1987 in Kansas" 
and 'findBegin(1, "founded", MATCH_LAST)' gives " 1987 in Kansas".  
If you follow the MATCH_LAST version with a: 'findEnd(1, "in", MATCH_FIRST)' you will 
now have a current value of " 1987 ", which by default will be trimmed to "1987" if you use 
for example outputValue("year") or valueGet().
TEXT;

$f["seealso"]       = "findEnd";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "ifindBegin";
// ********************
$f["syntax"][]  = <<<TEXT
bool ifindBegin ( int iCount, string sSubstring
                , int postMarkerPos = MATCH_LAST );                    
TEXT;
$f["params"][]    = array ( "int", "iCount", "Stop 1st, 2nd, 3rd ... position that matches the sequence. Can be negative to search backwards." );
$f["params"][]    = array ( "string", "sSubstring", "Substring to search for." );
$f["params"][]    = array ( "enum", "postMarkerPos", "Specify if position in current value string should be before the first character in match or at last position in match. See: TextMatchPositions." );
$f["params"][]    = array ( "bool", "RETURN", "True if found." );

$f["desc"]      = <<<TEXT
Move begin marker to the substring starting from beginning of current value string, ignoring casing.  
For example you have a current value of : "was Founded 1987 in Kansas".
Then 'ifindBegin(1, "founded", MATCH_FIRST)' gives "founded 1987 in Kansas" 
and 'ifindBegin(1, "founded", MATCH_LAST)' gives " 1987 in Kansas".  
If you follow the MATCH_LAST version with a: 'ifindEnd(1, "in", MATCH_FIRST)' you will 
now have a current value of " 1987 ", which by default will be trimmed to "1987" if you use 
for example outputValue("year") or valueGet().
TEXT;

$f["seealso"]       = "ifindEnd";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "findEnd";
// ********************
$f["syntax"][]  = <<<TEXT
bool findEnd ( int iCount, string sSubstring
             , int postMarkerPos = MATCH_FIRST );                    
TEXT;
$f["params"][]    = array ( "int", "iCount", "Stop 1st, 2nd, 3rd ... position that matches the sequence. Can be negative to search backwards." );
$f["params"][]    = array ( "string", "sSubstring", "Substring to search for." );
$f["params"][]    = array ( "enum", "postMarkerPos", "Specify if position in current value string should be before the first character in match or at last position in match. See: TextMatchPositions." );
$f["params"][]    = array ( "bool", "RETURN", "True if found." );

$f["desc"]      = <<<TEXT
Move end marker to the substring starting from current begin marker 
or beginning of current value string if begin marker has not been moved.  
For example you have a current value of : "was founded 1987 in Kansas".
Then 'findBegin(1, "founded", MATCH_FIRST)' gives "founded 1987 in Kansas" 
and 'findBegin(1, "founded", MATCH_LAST)' gives " 1987 in Kansas".  
If you follow the MATCH_LAST version with a: 'findEnd(1, "in", MATCH_FIRST)' you will 
now have a current value of " 1987 ", which by default will be trimmed to "1987" if you use 
for example outputValue("year") or valueGet().
TEXT;

$f["seealso"]       = "findBegin";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "ifindEnd";
// ********************
$f["syntax"][]  = <<<TEXT
bool ifindEnd ( int iCount, string sSubstring
              , int postMarkerPos = MATCH_FIRST );                    
TEXT;
$f["params"][]    = array ( "int", "iCount", "Stop 1st, 2nd, 3rd ... position that matches the sequence. Can be negative to search backwards." );
$f["params"][]    = array ( "string", "sSubstring", "Substring to search for." );
$f["params"][]    = array ( "enum", "postMarkerPos", "Specify if position in current value string should be before the first character in match or at last position in match. See: TextMatchPositions." );
$f["params"][]    = array ( "bool", "RETURN", "True if found." );

$f["desc"]      = <<<TEXT
Move end marker to the substring starting from current begin marker 
or beginning of current value string if begin marker has not been moved, ignoring casing.  
For example you have a current value of : "was founded 1987 in Kansas".
Then 'findBegin(1, "founded", MATCH_FIRST)' gives "founded 1987 in Kansas" 
and 'findBegin(1, "founded", MATCH_LAST)' gives " 1987 in Kansas".  
If you follow the MATCH_LAST version with a: 'findEnd(1, "in", MATCH_FIRST)' you will 
now have a current value of " 1987 ", which by default will be trimmed to "1987" if you use 
for example outputValue("year") or valueGet().
TEXT;

$f["seealso"]       = "ifindBegin";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "findBeginNext";
// ********************
$f["syntax"][]  = <<<TEXT
bool findBeginNext ( int iCount, string sSubstring
                   , int postMarkerPos = MATCH_LAST );                    
TEXT;
$f["params"][]    = array ( "int", "iCount", "Stop 1st, 2nd, 3rd ... position that matches the sequence. Can be negative to search backwards." );
$f["params"][]    = array ( "string", "sSubstring", "Substring to search for." );
$f["params"][]    = array ( "enum", "postMarkerPos", "Specify if position in current value string should be before the first character in match or at last position in match. See: TextMatchPositions." );
$f["params"][]    = array ( "bool", "RETURN", "True if found." );

$f["desc"]      = <<<TEXT
Move begin marker to the substring starting from current begin position in current value string.  
TEXT;

$f["seealso"]       = "findBegin";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "ifindBeginNext";
// ********************
$f["syntax"][]  = <<<TEXT
bool ifindBeginNext ( int iCount, string sSubstring
                    , int postMarkerPos = MATCH_LAST );                    
TEXT;
$f["params"][]    = array ( "int", "iCount", "Stop 1st, 2nd, 3rd ... position that matches the sequence. Can be negative to search backwards." );
$f["params"][]    = array ( "string", "sSubstring", "Substring to search for." );
$f["params"][]    = array ( "enum", "postMarkerPos", "Specify if position in current value string should be before the first character in match or at last position in match. See: TextMatchPositions." );
$f["params"][]    = array ( "bool", "RETURN", "True if found." );

$f["desc"]      = <<<TEXT
Move begin marker to the substring starting from current begin position in current value string, 
ignoring casing.  
TEXT;

$f["seealso"]       = "ifindBegin";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "findEndNext";
// ********************
$f["syntax"][]  = <<<TEXT
bool findEndNext ( int iCount, string sSubstring
                 , int postMarkerPos = MATCH_FIRST );                    
TEXT;
$f["params"][]    = array ( "int", "iCount", "Stop 1st, 2nd, 3rd ... position that matches the sequence. Can be negative to search backwards." );
$f["params"][]    = array ( "string", "sSubstring", "Substring to search for." );
$f["params"][]    = array ( "enum", "postMarkerPos", "Specify if position in current value string should be before the first character in match or at last position in match. See: TextMatchPositions." );
$f["params"][]    = array ( "bool", "RETURN", "True if found." );

$f["desc"]      = <<<TEXT
Move end marker to the substring starting from current end position in current value string.  
TEXT;

$f["seealso"]       = "findEnd";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "ifindEndNext";
// ********************
$f["syntax"][]  = <<<TEXT
bool ifindEndNext ( int iCount, string sSubstring
                  , int postMarkerPos = MATCH_FIRST );                    
TEXT;
$f["params"][]    = array ( "int", "iCount", "Stop 1st, 2nd, 3rd ... position that matches the sequence. Can be negative to search backwards." );
$f["params"][]    = array ( "string", "sSubstring", "Substring to search for." );
$f["params"][]    = array ( "enum", "postMarkerPos", "Specify if position in current value string should be before the first character in match or at last position in match. See: TextMatchPositions." );
$f["params"][]    = array ( "bool", "RETURN", "True if found." );

$f["desc"]      = <<<TEXT
Move end marker to the substring starting from current end position in current value string, 
ignoring casing.  
TEXT;

$f["seealso"]       = "findEnd";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "findRegexBegin";
// ********************
$f["syntax"][]  = <<<TEXT
bool findRegexBegin ( int iCount, string sRegex
                    , int postMarkerPos = MATCH_LAST );                    
TEXT;
$f["params"][]    = array ( "int", "iCount", "Stop 1st, 2nd, 3rd ... position that matches the sequence. Can be negative to search backwards." );
$f["params"][]    = array ( "string", "sRegex", "Regular expresion to search for." );
$f["params"][]    = array ( "enum", "postMarkerPos", "Specify if position in current value string should be before the first character in match or at last position in match. See: TextMatchPositions." );
$f["params"][]    = array ( "bool", "RETURN", "True if found." );

$f["desc"]      = <<<TEXT
Move begin marker to the regular expression match starting from beginning of current value string.  
TEXT;
$f["seealso"]       = "findBegin";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "ifindRegexBegin";
// ********************
$f["syntax"][]  = <<<TEXT
bool ifindRegexBegin ( int iCount, string sRegex
                     , int postMarkerPos = MATCH_LAST );                    
TEXT;
$f["params"][]    = array ( "int", "iCount", "Stop 1st, 2nd, 3rd ... position that matches the sequence. Can be negative to search backwards." );
$f["params"][]    = array ( "string", "sRegex", "Regular expresion to search for." );
$f["params"][]    = array ( "enum", "postMarkerPos", "Specify if position in current value string should be before the first character in match or at last position in match. See: TextMatchPositions." );
$f["params"][]    = array ( "bool", "RETURN", "True if found." );

$f["desc"]      = <<<TEXT
Move begin marker to the regular expression match starting from beginning of current value string, 
ignoring casing.  
TEXT;
$f["seealso"]       = "findBegin";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "findRegexEnd";
// ********************
$f["syntax"][]  = <<<TEXT
bool findRegexEnd ( int iCount, string sRegex
                  , int postMarkerPos = MATCH_FIRST );                    
TEXT;
$f["params"][]    = array ( "int", "iCount", "Stop 1st, 2nd, 3rd ... position that matches the sequence. Can be negative to search backwards." );
$f["params"][]    = array ( "string", "sRegex", "Regular expresion to search for." );
$f["params"][]    = array ( "enum", "postMarkerPos", "Specify if position in current value string should be before the first character in match or at last position in match. See: TextMatchPositions." );
$f["params"][]    = array ( "bool", "RETURN", "True if found." );

$f["desc"]      = <<<TEXT
Move end marker to the regular expression match starting from current begin marker 
or beginning of current value string if begin marker has not been moved.  
TEXT;
$f["seealso"]       = "findEnd";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "ifindRegexEnd";
// ********************
$f["syntax"][]  = <<<TEXT
bool ifindRegexEnd ( int iCount, string sRegex
                   , int postMarkerPos = MATCH_FIRST );                    
TEXT;
$f["params"][]    = array ( "int", "iCount", "Stop 1st, 2nd, 3rd ... position that matches the sequence. Can be negative to search backwards." );
$f["params"][]    = array ( "string", "sRegex", "Regular expresion to search for." );
$f["params"][]    = array ( "enum", "postMarkerPos", "Specify if position in current value string should be before the first character in match or at last position in match. See: TextMatchPositions." );
$f["params"][]    = array ( "bool", "RETURN", "True if found." );

$f["desc"]      = <<<TEXT
Move end marker to the regular expression match starting from current begin marker 
or beginning of current value string if begin marker has not been moved, ignoring casing.  
TEXT;
$f["seealso"]       = "ifindEnd";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "findRegexBeginNext";
// ********************
$f["syntax"][]  = <<<TEXT
bool findRegexBeginNext ( int iCount, string sRegex
                        , int postMarkerPos = MATCH_LAST );                    
TEXT;
$f["params"][]    = array ( "int", "iCount", "Stop 1st, 2nd, 3rd ... position that matches the sequence. Can be negative to search backwards." );
$f["params"][]    = array ( "string", "sRegex", "Regular expresion to search for." );
$f["params"][]    = array ( "enum", "postMarkerPos", "Specify if position in current value string should be before the first character in match or at last position in match. See: TextMatchPositions." );
$f["params"][]    = array ( "bool", "RETURN", "True if found." );

$f["desc"]      = <<<TEXT
Move begin marker to the regular expression match starting from current begin position 
of current value string.  
TEXT;
$f["seealso"]       = "findBeginNext";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "ifindRegexBeginNext";
// ********************
$f["syntax"][]  = <<<TEXT
bool ifindRegexBeginNext ( int iCount, string sRegex
                         , int postMarkerPos = MATCH_LAST );                    
TEXT;
$f["params"][]    = array ( "int", "iCount", "Stop 1st, 2nd, 3rd ... position that matches the sequence. Can be negative to search backwards." );
$f["params"][]    = array ( "string", "sRegex", "Regular expresion to search for." );
$f["params"][]    = array ( "enum", "postMarkerPos", "Specify if position in current value string should be before the first character in match or at last position in match. See: TextMatchPositions." );
$f["params"][]    = array ( "bool", "RETURN", "True if found." );

$f["desc"]      = <<<TEXT
Move begin marker to the regular expression match starting from current begin position 
of current value string, ignoring casing.  
TEXT;
$f["seealso"]       = "ifindBeginNext";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "findRegexEndNext";
// ********************
$f["syntax"][]  = <<<TEXT
bool findRegexEndNext ( int iCount, string sRegex
                      , int postMarkerPos = MATCH_FIRST );                    
TEXT;
$f["params"][]    = array ( "int", "iCount", "Stop 1st, 2nd, 3rd ... position that matches the sequence. Can be negative to search backwards." );
$f["params"][]    = array ( "string", "sRegex", "Regular expresion to search for." );
$f["params"][]    = array ( "enum", "postMarkerPos", "Specify if position in current value string should be before the first character in match or at last position in match. See: TextMatchPositions." );
$f["params"][]    = array ( "bool", "RETURN", "True if found." );

$f["desc"]      = <<<TEXT
Move end marker to the regular expression match starting from current end position 
of current value string.  
TEXT;
$f["seealso"]       = "findEndNext";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "ifindRegexEndNext";
// ********************
$f["syntax"][]  = <<<TEXT
bool ifindRegexEndNext ( int iCount, string sRegex
                       , int postMarkerPos = MATCH_FIRST );                    
TEXT;
$f["params"][]    = array ( "int", "iCount", "Stop 1st, 2nd, 3rd ... position that matches the sequence. Can be negative to search backwards." );
$f["params"][]    = array ( "string", "sRegex", "Regular expresion to search for." );
$f["params"][]    = array ( "enum", "postMarkerPos", "Specify if position in current value string should be before the first character in match or at last position in match. See: TextMatchPositions." );
$f["params"][]    = array ( "bool", "RETURN", "True if found." );

$f["desc"]      = <<<TEXT
Move end marker to the regular expression match starting from current end position 
of current value string, ignoring casing.  
TEXT;
$f["seealso"]       = "ifindEndNext";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "stepBegin";
// ********************
$f["syntax"][]  = <<<TEXT
bool stepBegin ( int iCount );
TEXT;
$f["params"][]    = array ( "int", "iCount", "Number of chars to move position in current value string. Negative values moves backwards." );
$f["params"][]    = array ( "bool", "RETURN", "True if step was possible." );

$f["desc"]      = <<<TEXT
Move begin marker a number of chars forwards or backwards starting from current begin position of current value string.
TEXT;
$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "stepEnd";
// ********************
$f["syntax"][]  = <<<TEXT
bool stepEnd ( int iCount );
TEXT;
$f["params"][]    = array ( "int", "iCount", "Number of chars to move position in current value string. Negative values moves backwards." );
$f["params"][]    = array ( "bool", "RETURN", "True if step was possible." );

$f["desc"]      = <<<TEXT
Move end marker a number of chars forwards or backwards starting from current end position of current value string.
TEXT;
$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;
?>


-----------------------------
--- URL queue functions ---
-----------------------------
<?php

$f = array();
$f["name"] =
// **************************
       "URL queue functions";
// **************************

$f["type"]      = "group";
$f["desc"]      = <<<TEXT
Functions for appending and quering the global url queue. Most often you just need 
to use urlQueueAppendUnique and urlQueueSize.
TEXT;
$f["note"][]   = "";
$f["seealso"]  = "";
$a[] = $f;


$f = array();
$f["name"] =
// ********************
       "LinkTypes";
// ********************
$f["type"]      = "enum";
$f["group"]     = "URL queue functions";

$f["values"][]	= array ( "LINK_TYPE_LOCAL", "Site local link." );
$f["values"][]	= array ( "LINK_TYPE_EXTERNAL", "link to another site." );
$f["values"][]	= array ( "LINK_TYPE_ALL", "All link types local, external." );

$f["desc"]      = <<<TEXT
URL link types. Can designate local, external or both types.
TEXT;
$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


// --- Common function properties ---
$f_common = array();
$f_common["type"]      = "function";
$f_common["group"]     = "URL queue functions";


$f = $f_common;
$f["name"] =
// ********************
       "urlQueueSize";
// ********************
$f["syntax"][]  = <<<TEXT
int urlQueueSize();
TEXT;
$f["params"][]    = array ( "int", "RETURN", "Size of current url queue." );

$f["desc"]      = <<<TEXT
TEXT;
$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
Get size of current url queue.
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "urlQueueSizeProcessed";
// ********************
$f["syntax"][]  = <<<TEXT
int urlQueueSizeProcessed();
TEXT;
$f["params"][]    = array ( "int", "RETURN", "Size of current processed urls list." );

$f["desc"]      = <<<TEXT
TEXT;
$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
Get size of current processed urls list.
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "urlQueueAlreadyProcessed";
// ********************
$f["syntax"][]  = <<<TEXT
bool urlQueueAlreadyProcessed( string sUrl );
TEXT;
$f["params"][]    = array ( "string", "sUrl", "Url to test" );
$f["params"][]    = array ( "bool", "RETURN", "true if url has already been processed." );

$f["desc"]      = <<<TEXT
Test if a given url has already been processed - i.e. has been taken from the urlQueue and loaded.
TEXT;
$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "urlQueueClear";
// ********************
$f["syntax"][]  = <<<TEXT
void urlQueueClear ();
TEXT;

$f["desc"]      = <<<TEXT
Clears global url queue.
TEXT;
$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "urlQueueFront";
// ********************
$f["syntax"][]  = <<<TEXT
string urlQueueFront ();
TEXT;
$f["params"][]    = array ( "string", "RETURN", "Front element of url queue." );

$f["desc"]      = <<<TEXT
Get front element of global url queue.
TEXT;
$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "urlQueueAppend";
// ********************
$f["syntax"][]  = <<<TEXT
void urlQueueAppend ( string sUrl );
void urlQueueAppend ( int iLinkType, string sTest ="", string sCompareFun = DefaultCompareFun );
TEXT;
$f["params"][]    = array ( "string", "sUrl", "Url to append to end of global queue." );
$f["params"][]    = array ( "enum", "iLinkType", "Linktype to append. See LinkTypes." );
$f["params"][]    = array ( "string", "sTest", "String to use as test when applying sCompareFun to each url." );
$f["params"][]    = array ( "string", "sCompareFun", "Name of compare function/operator to use like e.g. contains, equals, endsWith" );

$f["desc"]      = <<<TEXT
Form 1:
Append specific url to global url queue. 
Form 2:
Append all '<A ... href=SOME-URL ...></A>' urls to global url queue matching the given string and 
using given compare function/operator.

This way of adding urls allows for duplicates in the url queue, see urlQueueAppendUnique.

TEXT;
$f["seealso"]       = "urlQueueAppendUnique";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "urlQueueAppendUnique";
// ********************
$f["syntax"][]  = <<<TEXT
void urlQueueAppendUnique ( string sUrl );
void urlQueueAppendUnique ( int iLinkType, string sTest ="", string sCompareFun = DefaultCompareFun );
TEXT;
$f["params"][]    = array ( "string", "sUrl", "Url to append to end of global queue." );
$f["params"][]    = array ( "enum", "iLinkType", "Linktype to append. See LinkTypes." );
$f["params"][]    = array ( "string", "sTest", "String to use as test when applying sCompareFun to each url." );
$f["params"][]    = array ( "string", "sCompareFun", "Name of compare function/operator to use like e.g. contains, equals, endsWith" );

$f["desc"]      = <<<TEXT
Form 1:
Uniquely append specific url to global url queue..
Form 2:
Uniquely append all '<A ... href=SOME-URL ...></A>' urls to global url queue matching the given string and using 
given compare function/operator. 

Uniquely means only append url if it is not already in the url queue or in the list of 
already processed urls.
TEXT;
$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "urlQueuePrepend";
// ********************
$f["syntax"][]  = <<<TEXT
void urlQueuePrepend ( string sUrl );
TEXT;
$f["params"][]    = array ( "string", "sUrl", "Url to prepend to front of global queue." );

$f["desc"]      = <<<TEXT
Prepend specific url to front of global url queue. This way of adding urls 
allows for duplicates in the url queue, see urlQueuePrependUnique
TEXT;
$f["seealso"]       = "urlQueueAppend, urlQueuePrependUnique";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "urlQueuePrependUnique";
// ********************
$f["syntax"][]  = <<<TEXT
void urlQueuePrependUnique ( string sUrl );
TEXT;
$f["params"][]    = array ( "string", "sUrl", "Url to prepend to front of global queue." );

$f["desc"]      = <<<TEXT
Prepend specific url to front of global url queue. This way of adding urls 
allows for duplicates in the url queue, see urlQueuePrependUnique

Uniquely means only append url if it is not already in the url queue or in the list of 
already processed urls.
TEXT;
$f["seealso"]       = "urlQueueAppend, urlQueuePrepend";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;
?>


-----------------------------
--- Context functions ---
-----------------------------
<?php

$f = array();
$f["name"] =
// **************************
       "Context functions";
// **************************

$f["type"]      = "group";
$f["desc"]      = <<<TEXT
Functions for specifying output contexts, which generally means grouping output 
values together under a common name. In the default XML output using contextPush 
and contextPop is really simple like for example:
'
contextBegin("product");
outputDirect("type", "Pants" );
outputDirect("brand", "Lewis" );
contextEnd();
'
Will give an XML like:
'
<product>
    <type>Pants</type>
    <brand>Lewis</brand>
</product>
'

Since contextBegin works like pushing onto a stack it is easy to create a context 
within another context. Just rememeber to call contextEnd for every contextBegin.
TEXT;
$f["note"][]   = "";
$f["seealso"]  = "";
$a[] = $f;


// --- Common function properties ---
$f_common = array();
$f_common["type"]      = "function";
$f_common["group"]     = "Context functions";


$f = $f_common;
$f["name"] =
// ********************
       "contextBegin";
// ********************
$f["syntax"][]  = <<<TEXT
void contextBegin ( string sContextName );
TEXT;
$f["params"][]    = array ( "string", "sContextName", "Context name to use in output." );

$f["desc"]      = <<<TEXT
Begin new output context section.
TEXT;
$f["seealso"]       = "contextEnd";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "contextEnd";
// ********************
$f["syntax"][]  = <<<TEXT
void contextEnd ();
TEXT;

$f["desc"]      = <<<TEXT
End current context section.
TEXT;
$f["seealso"]       = "contextBegin";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "contextOutputSaveAs";
// ********************
$f["syntax"][]  = <<<TEXT
void contextOutputSaveAs ( string sContextName );
TEXT;
$f["params"][]    = array ( "string", "sContextName", "Save name to use." );

$f["desc"]      = <<<TEXT
Save all values written in current context under given name for later retrieval. 

The saved context values can be loaded again as "fallback" values. Such fallback 
values are used in outputValueFind, outputValueFindNext statements if no dom position 
can be found in which case the fallback value will be written to the output.

This can be usefull for example if you pick up some of the product information on 
the search listing page and the rest on the product page itself. In that case you save 
the current mined values on the search listing page using the deep link to the product 
page as context name. In the product page handler you reload the fallback values using 
the same deep link url. See more about this in the examples involving templates and in 
the manual.
TEXT;
$f["seealso"]       = "contextFallbackOutputLoad, contextSavedOutputDelete, contextSavedOutputExists";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "contextFallbackOutputLoad";
// ********************
$f["syntax"][]  = <<<TEXT
void contextFallbackOutputLoad ( string sContextName );
TEXT;
$f["params"][]    = array ( "string", "sContextName", "Name of saved context to load." );

$f["desc"]      = <<<TEXT
Load a previously saved context as fallback values. The values would have been 
saved using contextOutputSaveAs function.

Fallback values are used in outputValueFind, outputValueFindNext statements 
if no dom position can be found in which case the fallback value will be 
written to the output.

This can be usefull for example if you pick up some of the product information on 
the search listing page and the rest on the product page itself. In that case you save 
the current mined values on the search listing page using the deep link to the product 
page as context name. In the product page handler you reload the fallback values using 
the same deep link url. See more about this in the examples involving templates and in 
the manual.
TEXT;
$f["seealso"]       = "contextOutputSaveAs";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "contextFallbackOutputClear";
// ********************
$f["syntax"][]  = <<<TEXT
void contextFallbackOutputClear();
TEXT;

$f["desc"]      = <<<TEXT
clear current fallback values.
TEXT;
$f["seealso"]       = "contextFallbackOutputLoad, contextOutputSaveAs";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "contextFallbackValueGet";
// ********************
$f["syntax"][]  = <<<TEXT
string contextFallbackValueGet ( string sFieldName );
TEXT;
$f["params"][]    = array ( "string", "sFieldName", "Field name of fallback value to get." );
$f["params"][]    = array ( "string", "RETURN", "Fallback value for field name." );

$f["desc"]      = <<<TEXT
Get specific fallback value.
TEXT;
$f["seealso"]       = "contextFallbackValueSet, contextFallbackOutputLoad, contextOutputSaveAs, outputValueGet";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "contextFallbackValueSet";
// ********************
$f["syntax"][]  = <<<TEXT
void contextFallbackValueSet ( string sFieldName, string sValue ) ;
TEXT;
$f["params"][]    = array ( "string", "sFieldName", "Field name of fallback value to set." );
$f["params"][]    = array ( "string", "sValue", "Value to set." );

$f["desc"]      = <<<TEXT
Set specific fallback value.
TEXT;
$f["seealso"]       = "contextFallbackValueGet, contextFallbackOutputLoad, contextOutputSaveAs,outputValueGet";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "contextFallbackValueExists";
// ********************
$f["syntax"][]  = <<<TEXT
bool contextFallbackValueExists ( string sFieldName );
TEXT;
$f["params"][]    = array ( "string", "sFieldName", "Field name of fallback value to test for." );
$f["params"][]    = array ( "bool", "RETURN", "True if fallback value with given name can be found." );

$f["desc"]      = <<<TEXT
Test for existence of a fallback value.
TEXT;
$f["seealso"]       = "contextFallbackValueGet, contextFallbackValueDelete";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "contextFallbackValueDelete";
// ********************
$f["syntax"][]  = <<<TEXT
void contextFallbackValueDelete ( string sFieldName );
TEXT;
$f["params"][]    = array ( "string", "sFieldName", "Field name of fallback value to delete." );

$f["desc"]      = <<<TEXT
Delete a falback value.
TEXT;
$f["seealso"]       = "contextFallbackValueGet, contextFallbackValueExists";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "contextSavedOutputExists";
// ********************
$f["syntax"][]  = <<<TEXT
bool contextSavedOutputExists ( string sContextName );
TEXT;
$f["params"][]    = array ( "string", "sContextName", "Name of saved context." );
$f["params"][]    = array ( "bool", "RETURN", "True if a saved context with the given name exists." );

$f["desc"]      = <<<TEXT
Test for existance of saved context.
TEXT;
$f["seealso"]       = "contextSavedOutputDelete, contextOutputSaveAs";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "contextSavedOutputDelete";
// ********************
$f["syntax"][]  = <<<TEXT
void contextSavedOutputDelete ( string sContextName );
TEXT;
$f["params"][]    = array ( "string", "sContextName", "Name of saved context to delete." );

$f["desc"]      = <<<TEXT
Delete a saved context.
TEXT;
$f["seealso"]       = "contextSavedOutputExists, contextOutputSaveAs";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;

?>


-----------------------------
---  Output functions ---
-----------------------------
<?php

$f = array();
$f["name"] =
// **************************
       " Output functions";
// **************************

$f["type"]      = "group";
$f["desc"]      = <<<TEXT
Functions for writing data to the output.
TEXT;
$f["note"][]   = "";
$f["seealso"]  = "";
$a[] = $f;


// --- Common function properties ---
$f_common = array();
$f_common["type"]      = "function";
$f_common["group"]     = " Output functions";


$f = $f_common;
$f["name"] =
// ********************
       "outputDirect";
// ********************
$f["syntax"][]  = <<<TEXT
void outputDirect ( string sFieldName, string sValue, string sModifierID,
                    string sManipParam1,string sManipParam2, string sManipParam3,
                    string sManipParam4 );
void outputDirect ( string sFieldName, string sValue, string sModifierID,
                    string sManipParam1, string sManipParam2, string sManipParam3 );
void outputDirect ( string sFieldName, string sValue, string sModifierID,
                    string sManipParam1, string sManipParam2 );
void outputDirect ( string sFieldName, string sValue, string sModifierID,
                    string sManipParam1 );
void outputDirect ( string sFieldName, string sValue, string sModifierID );
void outputDirect ( string sFieldName, string sValue );
TEXT;
$f["params"][]    = array ( "string", "sFieldName", "Field/output name to use for the value." );
$f["params"][]    = array ( "string", "sValue", "Actual value to write." );
$f["params"][]    = array ( "string", "sModifierID", "String manipulation to perform. Can be a built-in: trim, prepend eraseAll ..., A named modifier created with modifierCreate or a PHP function." );
$f["params"][]    = array ( "string", "sManipParam1", "Optional parameter 1 for the manipulation function if needed." );
$f["params"][]    = array ( "string", "sManipParam2", "Optional parameter 2 for the manipulation function if needed." );
$f["params"][]    = array ( "string", "sManipParam3", "Optional parameter 3 for the manipulation function if needed." );
$f["params"][]    = array ( "string", "sManipParam4", "Optional parameter 4 for the manipulation function if needed." );

$f["desc"]      = <<<TEXT
Write specified value to output, optionally filtered through a manipulator function.
TEXT;
$f["seealso"]       = "outputValue, outputValueFind";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "outputValue";
// ********************
$f["syntax"][]  = <<<TEXT
void outputValue ( string sFieldName, string sModifierID,
                   string sManipParam1, string sManipParam2,
                   string sManipParam3, string sManipParam4 );
void outputValue ( string sFieldName, string sModifierID,
                   string sManipParam1, string sManipParam2,
                   string sManipParam3 );
void outputValue ( string sFieldName, string sModifierID,
                   string sManipParam1, string sManipParam2 );
void outputValue ( string sFieldName, string sModifierID,
                   string sManipParam1 );
void outputValue ( string sFieldName, string sModifierID );
void outputValue ( string sFieldName );
TEXT;
$f["params"][]    = array ( "string", "sFieldName", "Field/output name to use for the value." );
$f["params"][]    = array ( "string", "sModifierID", "String manipulation to perform. Can be a built-in: trim, prepend eraseAll ..., A named modifier created with modifierCreate or a PHP function." );
$f["params"][]    = array ( "string", "sManipParam1", "Optional parameter 1 for the manipulation function if needed." );
$f["params"][]    = array ( "string", "sManipParam2", "Optional parameter 2 for the manipulation function if needed." );
$f["params"][]    = array ( "string", "sManipParam3", "Optional parameter 3 for the manipulation function if needed." );
$f["params"][]    = array ( "string", "sManipParam4", "Optional parameter 4 for the manipulation function if needed." );

$f["desc"]      = <<<TEXT
Write current value to output, optionally filtered through a manipulator function.
TEXT;
$f["seealso"]       = "outputDirect, outputValueFind";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "outputValueFindNext";
// ********************
$f["syntax"][]  = <<<TEXT
int outputValueFindNext ( int iCount, string sSequence, 
                          string sFieldName, string sManipFun,
                          string sManipParam1, string sManipParam2,
                          string sManipParam3, string sManipParam4 );
int outputValueFindNext ( int iCount, string sSequence,
                          string sFieldName, string sManipFun,
                          string sManipParam1, string sManipParam2,
                          string sManipParam3 );
int outputValueFindNext ( int iCount, string sSequence,
                          string sFieldName, string sManipFun,
                          string sManipParam1, string sManipParam2 );
int outputValueFindNext ( int iCount, string sSequence,
                          string sFieldName, string sManipFun,
                          string sManipParam1 );
int outputValueFindNext ( int iCount, string sSequence,
                          string sFieldName, string sManipFun );
int outputValueFindNext ( int iCount, string sSequence,
                          string sFieldName );
int outputValueFindNext ( string sSequence, 
                          string sFieldName, string sManipFun,
                          string sManipParam1, string sManipParam2,
                          string sManipParam3, string sManipParam4 );
int outputValueFindNext ( string sSequence,
                          string sFieldName, string sManipFun,
                          string sManipParam1, string sManipParam2,
                          string sManipParam3 );
int outputValueFindNext ( string sSequence,
                          string sFieldName, string sManipFun,
                          string sManipParam1, string sManipParam2 );
int outputValueFindNext ( string sSequence,
                          string sFieldName, string sManipFun,
                          string sManipParam1 );
int outputValueFindNext ( string sSequence,
                          string sFieldName, string sManipFun );
int outputValueFindNext ( string sSequence,
                          string sFieldName );
TEXT;
$f["params"][]    = array ( "int", "iCount", "Stop 1st, 2nd, 3rd ... position that matches the sequence. Can be negative to search backwards." );
$f["params"][]    = array ( "string", "sSequence", "Dom sequence. Can be one of: PHP function, named dom sequence, direct specified" );
$f["params"][]    = array ( "string", "sFieldName", "Field/output name to use for the value." );
$f["params"][]    = array ( "string", "sManipFun", "String manipulation to perform. Can be a built-in: trim, prepend eraseAll ..., A named modifier created with modifierCreate or a PHP function." );
$f["params"][]    = array ( "string", "sManipParam1", "Optional parameter 1 for the manipulation function if needed." );
$f["params"][]    = array ( "string", "sManipParam2", "Optional parameter 2 for the manipulation function if needed." );
$f["params"][]    = array ( "string", "sManipParam3", "Optional parameter 3 for the manipulation function if needed." );
$f["params"][]    = array ( "string", "sManipParam4", "Optional parameter 4 for the manipulation function if needed." );

$f["params"][]    = array ( "", "", "" );
$f["params"][]    = array ( "int", "RETURN", "The dom position where the sequance matched and wrote to the output, or zero if not found. Note the current dom position is never changed." );

$f["desc"]      = <<<TEXT
Finds (from current position) and writes a value to the output, optionally 
filtered through a manipulator function. Performs a domFindNext and only if 
successfull proceeds to call outputValue using the optional manipulator function.
NOTE: the current dom position is never changed.
TEXT;
$f["seealso"]       = "outputValueFind";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "outputValueFind";
// ********************
$f["syntax"][]  = <<<TEXT
int outputValueFind ( int iCount, string sSequence, 
                      string sFieldName, string sManipFun,
                      string sManipParam1, string sManipParam2,
                      string sManipParam3, string sManipParam4 );
int outputValueFind ( int iCount, string sSequence,
                      string sFieldName, string sManipFun,
                      string sManipParam1, string sManipParam2,
                      string sManipParam3 );
int outputValueFind ( int iCount, string sSequence,
                      string sFieldName, string sManipFun,
                      string sManipParam1, string sManipParam2 );
int outputValueFind ( int iCount, string sSequence,
                      string sFieldName, string sManipFun,
                      string sManipParam1 );
int outputValueFind ( int iCount, string sSequence,
                      string sFieldName, string sManipFun );
int outputValueFind ( int iCount, string sSequence,
                      string sFieldName );
int outputValueFind ( string sSequence, 
                      string sFieldName, string sManipFun,
                      string sManipParam1, string sManipParam2,
                      string sManipParam3, string sManipParam4 );
int outputValueFind ( string sSequence,
                      string sFieldName, string sManipFun,
                      string sManipParam1, string sManipParam2,
                      string sManipParam3 );
int outputValueFind ( string sSequence,
                      string sFieldName, string sManipFun,
                      string sManipParam1, string sManipParam2 );
int outputValueFind ( string sSequence,
                      string sFieldName, string sManipFun,
                      string sManipParam1 );
int outputValueFind ( string sSequence,
                      string sFieldName, string sManipFun );
int outputValueFind ( string sSequence,
                      string sFieldName );
					  
TEXT;
$f["params"][]    = array ( "int", "iCount", "Stop 1st, 2nd, 3rd ... position that matches the sequence. Can be negative to search backwards." );
$f["params"][]    = array ( "string", "sSequence", "Dom sequence. Can be one of: PHP function, named dom sequence, direct specified" );
$f["params"][]    = array ( "string", "sFieldName", "Field/output name to use for the value." );
$f["params"][]    = array ( "string", "sManipFun", "String manipulation to perform. Can be a built-in: trim, prepend eraseAll ..., A named modifier created with modifierCreate or a PHP function." );
$f["params"][]    = array ( "string", "sManipParam1", "Optional parameter 1 for the manipulation function if needed." );
$f["params"][]    = array ( "string", "sManipParam2", "Optional parameter 2 for the manipulation function if needed." );
$f["params"][]    = array ( "string", "sManipParam3", "Optional parameter 3 for the manipulation function if needed." );
$f["params"][]    = array ( "string", "sManipParam4", "Optional parameter 4 for the manipulation function if needed." );

$f["desc"]      = <<<TEXT
Finds (from beginning) and writes a value to the output, optionally 
filtered through a manipulator function. Performs a domFind and only if 
successfull proceeds to call outputValue using the optional manipulator function.
NOTE: the current dom position is never changed.
TEXT;
$f["seealso"]       = "outputValueFind";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "";
// ********************
$f["syntax"][]  = <<<TEXT
string outputValueGet ( string sFieldName, string sContextName = "" );
TEXT;
$f["params"][]    = array ( "string", "sFieldName", "Name of field already written to output." );
$f["params"][]    = array ( "string", "sContextName", "Optional context name to look up in. Default is to not specify and then the current context is used." );
$f["params"][]    = array ( "string", "RETURN", "Value of field already written to output." );

$f["desc"]      = <<<TEXT
Get value of field already written to output.
TEXT;
$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;

?>


-------------------------------

<?php
$f = $f_common;
$f["name"] =
// ********************
       "";
// ********************
$f["syntax"][]  = <<<TEXT
TEXT;
$f["params"][]    = array ( "", "", "" );
$f["params"][]    = array ( "", "RETURN", "" );

$f["desc"]      = <<<TEXT
TEXT;
$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;
?>
-------------------------------





