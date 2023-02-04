<?php
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
$f["seealso"]   = "string-compare-functions, all-functions, all-function-groups";
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
