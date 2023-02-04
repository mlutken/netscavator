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
the <b>_fn</b> and is used in domFind, domFindNext, domSeqCreate, valueCompare, valuesCompare functions. Refer 
to the string-compare-operators section in this reference manual.
TEXT;
$f["seealso"]   = "compare-operators, all-functions, all-function-groups";
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
completeness, since the regular "==" works in identical way. Also it is here as a consequence of its 
corresponding operator "equals", which we do need for functions like domFindNext, domSeqCreate, valuesCompare.
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
\$sInput = "aBcDe";
\$sTest = "bCd";
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
\$sInput = "aBcDe";
\$sTest = "AbC";
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
\$sInput = "aBcDe";
\$sTest = "CdE";
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
\$sInput = "household";
\$sTest1 = "house";
\$sTest2 = "houses";
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
\$sInput = "HouseHold";
\$sTest1 = "houSe";
\$sTest2 = "houSes";
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
\$sInput = "household";
\$sTest1 = "house";
\$sTest2 = "houses";
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
\$sInput = "HouseHold";
\$sTest1 = "houSe";
\$sTest2 = "houSes";
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
