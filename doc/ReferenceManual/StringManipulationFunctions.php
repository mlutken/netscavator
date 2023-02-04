<?php
// --- Common function properties ---
$f_common = array();
$f_common["type"]      = "function";
$f_common["group"]     = "String manipulation functions";
$f_common["params"][]  = array ( "string", "sInput", "Original/source string for manipulation. Note that this string is not changed. The function returns a copy of this string with the applied changes." );

$f_common_i = $f_common;
$f_common_i["note"][]   = "Currently the case insensitive functions are only working properly for english letters a-z,A-Z. This will be corrected in a future release.";



$f = array();
$f["name"] =
// ******************************
       "String manipulation functions";
// ******************************

$f["type"]      = "group";
$f["desc"]      = <<<TEXT
A collection of functions that manipulate strings like: eraseAll_fn, toUpper_fn, etc.
These are normal callable PHP functions. Use same names without "_fn" and in quotes
when using as modifiers in outputValue, outputValueFind, valueModify, valueGet,
valueCompare, nodeCompare, nodeValueParent, nodeValuePos.
TEXT;
$f["seealso"]   = "string-manipulation-operators, all-functions, all-function-groups";
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "trimDefault_fn";
// ********************
$f["syntax"][]  = <<<TEXT
string trimDefault_fn ( string sInput );
TEXT;
$f["params"][]    = array ( "string", "RETURN", "The trimmed/modified string." );

$f["desc"]      = <<<TEXT
Performs default trimming of a string.  
Modifications performed:
(1) Replace all newlines and HTML non-breakable-spaces with spaces.
(2) Collapsing consecutive spaces to one.
(3) Remove whitespace at the ends. Same as trimEnds_fn

Its operator counterpart "trimDefault" is called from every output function as the last thing, even if you specified 
another manipulator, like "replaceAll" the "trimDefault" will still be applied after. You can prevent this by using a manipulator 
that has "raw" in its name like the manipulator "raw" or for example a custom PHP function called rawMyManipulator. 
TEXT;

$f["seealso"]       = "trimDefault, trimEnds_fn";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "raw_fn";
// ********************
$f["syntax"][]  = <<<TEXT
string raw_fn ( string sInput );
TEXT;
$f["params"][]    = array ( "string", "RETURN", "The raw unmodified string." );

$f["desc"]      = <<<TEXT
Output string as is, witout any processing. This function is only usefull when used in its operator 
version "raw" in for example 'outputValue("product_name", "raw");'. This causes the normal applied trimDefault 
to be bypassed. 
TEXT;

$f["seealso"]       = "trimDefault_fn, trimDefault, raw";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "toUpper_fn";
// ********************
$f["syntax"][]  = <<<TEXT
string toUpper_fn ( string sInput );
TEXT;
$f["params"][]    = array ( "string", "RETURN", "The string with all letters in uppercase/capital." );

$f["desc"]      = <<<TEXT
Uppercase all characters in string.
TEXT;

$f["note"][]        = "Currently this function is only working properly for english letters a-z,A-Z. This will be corrected in a future release.";
$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;

$f = $f_common;
$f["name"] =
// ********************
       "toLower_fn";
// ********************
$f["syntax"][]  = <<<TEXT
string toLower_fn ( string sInput );
TEXT;
$f["params"][]    = array ( "string", "RETURN", "The string with all letters in lowercase." );

$f["desc"]      = <<<TEXT
Lowercase all characters in string.
TEXT;

$f["note"][]        = "Currently this function is only working properly for english letters a-z,A-Z. This will be corrected in a future release.";
$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;

$f = $f_common;
$f["name"] =
// ********************
       "trimEnds_fn";
// ********************
$f["syntax"][]  = <<<TEXT
string trimEnds_fn ( string sInput );
TEXT;
$f["params"][]    = array ( "string", "RETURN", "The trimmed/modified string." );

$f["desc"]      = <<<TEXT
Removes spaces and tabs at both ends of the string.
TEXT;

$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;

$f = $f_common;
$f["name"] =
// ********************
       "trimLeft_fn";
// ********************
$f["syntax"][]  = <<<TEXT
string trimLeft_fn ( string sInput );
TEXT;
$f["params"][]    = array ( "string", "RETURN", "The trimmed/modified string." );

$f["desc"]      = <<<TEXT
Removes spaces and tabs from left part (start) of the string.
TEXT;

$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;

$f = $f_common;
$f["name"] =
// ********************
       "trimRight_fn";
// ********************
$f["syntax"][]  = <<<TEXT
string trimRight_fn ( string sInput );
TEXT;
$f["params"][]    = array ( "string", "RETURN", "The trimmed/modified string." );

$f["desc"]      = <<<TEXT
Removes spaces and tabs from right part (end) of the string.
TEXT;

$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;

$f = $f_common;
$f["name"] =
// ********************
       "trimYear_fn";
// ********************
$f["syntax"][]  = <<<TEXT
string trimYear_fn ( string sInput );
TEXT;
$f["params"][]    = array ( "string", "RETURN", "A string containing a year (4 digits) or an empty string." );

$f["desc"]      = <<<TEXT
Searches the input string for the first occurence that could represent a year. A year is any 4 digits in a row. The year 
is returned as a string containing the 4 digits.
TEXT;

$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;

$f = $f_common;
$f["name"] =
// ********************
       "trimInteger_fn";
// ********************
$f["syntax"][]  = <<<TEXT
string trimInteger_fn ( string sInput );
TEXT;
$f["params"][]    = array ( "string", "RETURN", "A string containing the first integer found in the input." );

$f["desc"]      = <<<TEXT
Searches the input string for the first occurence that could represent an integer. An integer is any non fractional number found 
in the string like for eaxample 123 or 12, but not 12.34 or 123.56. By default the function uses english locale meaning that 
dot "." is used as decimal point/separator and "," is used as thousands separator. To change this behaviour use the configuration 
functions configParseDecimalPointSet, configParseThousandsSepSet.
TEXT;

$f["seealso"]       = "configParseDecimalPointSet, configParseThousandsSepSet, trimIntegerCustom_fn, trimNumber_fn";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;

$f = $f_common;
$f["name"] =
// ********************
       "trimNumber_fn";
// ********************
$f["syntax"][]  = <<<TEXT
string trimNumber_fn ( string sInput );
TEXT;
$f["params"][]    = array ( "string", "RETURN", "A string containing the first number found in the input." );

$f["desc"]      = <<<TEXT
Searches the input string for the first occurence that could represent a number. A number is for eaxample 123.12 or 12.1, 
and also non fractional/integer numbers like 7 and 678. By default the function uses english locale meaning that "," 
is used as thousands separator. To change this behaviour use the configuration function configParseThousandsSepSet.
TEXT;

$f["seealso"]       = "configParseThousandsSepSet, trimNumberCustom_fn, trimInteger_fn";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "trimCharsEnds_fn";
// ********************
$f["syntax"][]  = <<<TEXT
string  trimCharsEnds_fn  ( string sInput, string sCharsToTrim );
TEXT;
$f["params"][]  = array ( "string", "sCharsToTrim", "String containing all chars you want to \"trim\" away. For example \"tBf\" for trimming t, B and f " );
$f["params"][]  = array ( "string", "RETURN", "The string with specified chars removed." );

$f["desc"]      = <<<TEXT
Removes specified chars from both ends of the input string.
TEXT;

$f["note"][]        = "Currently this function is only working properly for english letters a-z,A-Z. This will be corrected in a future release.";
$f["seealso"]       = "trimCharsLeft_fn, trimCharsRight_fn";
$f["examples"][]    = <<<TEXT
\$trimmed = trimCharsEnds_fn("abcdeff", "af");
print("trimmed: '\$trimmed'\\n"); // Outputs: timmed: 'bcde'
TEXT;
$a[] = $f;
    
$f = $f_common;
$f["name"] =
// ********************
       "trimCharsLeft_fn";
// ********************
$f["syntax"][]  = <<<TEXT
string  trimCharsLeft_fn  ( string sInput, string sCharsToTrim );
TEXT;
$f["params"][]  = array ( "string", "sCharsToTrim", "String containing all chars you want to \"trim\" away. For example \"tBf\" for trimming t, B and f " );
$f["params"][]  = array ( "string", "RETURN", "The string with specified chars removed." );

$f["desc"]      = <<<TEXT
Removes specified chars from left/front end of the input string.
TEXT;

$f["note"][]        = "Currently this function is only working properly for english letters a-z,A-Z. This will be corrected in a future release.";
$f["seealso"]       = "trimCharsEnds_fn, trimCharsRight_fn";
$f["examples"][]    = <<<TEXT
\$trimmed = trimCharsLeft_fn("abcdeff", "ab");
print("trimmed: '\$trimmed'\\n"); // Outputs: timmed: 'cdeff'
TEXT;
$a[] = $f;
    
$f = $f_common;
$f["name"] =
// ********************
       "trimCharsRight_fn";
// ********************
$f["syntax"][]  = <<<TEXT
string  trimCharsRight_fn  ( string sInput, string sCharsToTrim );
TEXT;
$f["params"][]  = array ( "string", "sCharsToTrim", "String containing all chars you want to \"trim\" away. For example \"tBf\" for trimming t, B and f " );
$f["params"][]  = array ( "string", "RETURN", "The string with specified chars removed." );

$f["desc"]      = <<<TEXT
Removes specified chars from right/back end of the input string.
TEXT;

$f["note"][]        = "Currently this function is only working properly for english letters a-z,A-Z. This will be corrected in a future release.";
$f["seealso"]       = "trimCharsEnds_fn, trimCharsLeft_fn";
$f["examples"][]    = <<<TEXT
\$trimmed = trimCharsRight_fn("abcdeff", "f");
print("trimmed: '\$trimmed'\\n"); // Outputs: timmed: 'abcde'
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "trimRegex_fn";
// ********************
$f["syntax"][]  = <<<TEXT
string trimRegex_fn ( string sInput, string sRegex );
TEXT;
$f["params"][]  = array ( "string", "sRegex", "Regular expression (Perl style). The part that matches gets returned." );
$f["params"][]  = array ( "string", "RETURN", "The matching part of the input when searching using the regular expression." );

$f["desc"]      = <<<TEXT
Returns the sub-string that macthes the regular expression. String is searched using the regular expression and the 
first time it macthes the matching part is returned.
TEXT;

$f["seealso"]       = "itrimRegex_fn, eraseRegex_fn";
$f["examples"][]    = <<<TEXT
// Roll your own trimYear_fn
\$year = trimRegex_fn( "In the year 1989 we saw ...", "\d\d\d\d");
print("year: '\$year'\\n"); // Outputs: year: '1989'
TEXT;
$a[] = $f;


$f = $f_common_i;
$f["name"] =
// ********************
       "itrimRegex_fn";
// ********************
$f["syntax"][]  = <<<TEXT
string itrimRegex_fn ( string sInput, string sRegex );
TEXT;
$f["params"][]  = array ( "string", "sRegex", "Regular expression (Perl style). The part that matches gets returned." );
$f["params"][]  = array ( "string", "RETURN", "The matching part of the input when searching using the regular expression." );

$f["desc"]      = <<<TEXT
Returns the sub-string that macthes the regular expression - ignoring casing. String is searched using the regular expression and the 
first time it macthes the matching part is returned.
TEXT;

$f["seealso"]       = "trimRegex_fn, eraseRegex_fn";
$f["examples"][]    = <<<TEXT
// Roll your own trimYear_fn
\$year = trimRegex_fn( "In the year 1989 we saw ...", "\d\d\d\d");
print("year: '\$year'\\n"); // Outputs: year: '1989'
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "append_fn";
// ********************
$f["syntax"][]  = <<<TEXT
string append_fn ( string sInput, string sString );
TEXT;
$f["params"][]  = array ( "string", "sString", "String to append." );
$f["params"][]  = array ( "string", "RETURN", "sInput string with sString appended." );

$f["desc"]      = <<<TEXT
Append string to the input string. Same as concatenation operator "." . Only the operator version "append" is 
really usefull, which could typically be used like this: 'outputValue("price_with_currency", "append", " USD" )'. 
This would write the current value to the ouput with the string " USD" appended. In case
TEXT;

$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "prepend_fn";
// ********************
$f["syntax"][]  = <<<TEXT
string prepend_fn ( string sInput, string sString );
TEXT;
$f["params"][]  = array ( "string", "sString", "String to prepend." );
$f["params"][]  = array ( "string", "RETURN", "sInput string with sString prepended." );

$f["desc"]      = <<<TEXT
Prepend string to the input string. Same as concatenation operator "." . Only the operator version "prepend" is 
really usefull, which could typically be used like this: 'outputValue("url_product", "prepend", "http://www.somesite.com/" )'. 
This would write the current value to the ouput with the site URL "http://www.somesite.com/" prepended.
TEXT;

$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "eraseFirst_fn";
// ********************
$f["syntax"][]  = <<<TEXT
string eraseFirst_fn ( string sInput, string sSearchFor );
TEXT;
$f["params"][]  = array ( "string", "sSearchFor", "String to search for." );
$f["params"][]  = array ( "string", "RETURN", "The trimmed/modified string." );

$f["desc"]      = <<<TEXT
Erase first occurence of sSearchFor string in input string.
TEXT;

$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "eraseLast_fn";
// ********************
$f["syntax"][]  = <<<TEXT
string eraseLast_fn ( string sInput, string sSearchFor );
TEXT;
$f["params"][]  = array ( "string", "sSearchFor", "String to search for." );
$f["params"][]  = array ( "string", "RETURN", "The trimmed/modified string." );

$f["desc"]      = <<<TEXT
Erase last occurence of sSearchFor string in input string.
TEXT;

$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "eraseAll_fn";
// ********************
$f["syntax"][]  = <<<TEXT
string eraseAll_fn ( string sInput, string sSearchFor );
TEXT;
$f["params"][]  = array ( "string", "sSearchFor", "String to search for." );
$f["params"][]  = array ( "string", "RETURN", "The trimmed/modified string." );

$f["desc"]      = <<<TEXT
Erase all occurences of sSearchFor string in input string.
TEXT;

$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "eraseRegex_fn";
// ********************
$f["syntax"][]  = <<<TEXT
string eraseRegex_fn ( string sInput, string sSearchForRegex );
TEXT;
$f["params"][]  = array ( "string", "sSearchForRegex", "Regular expression to search for." );
$f["params"][]  = array ( "string", "RETURN", "The trimmed/modified string." );

$f["desc"]      = <<<TEXT
Erase part of input string that matches the regular expression.
TEXT;

$f["seealso"]       = "trimRegex_fn, ieraseRegex_fn";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common_i;
$f["name"] =
// ********************
       "ieraseFirst_fn";
// ********************
$f["syntax"][]  = <<<TEXT
string ieraseFirst_fn ( string sInput, string sSearchFor );
TEXT;
$f["params"][]  = array ( "string", "sSearchFor", "String to search for." );

$f["desc"]      = <<<TEXT
Erase first occurence of sSearchFor string in input string - ignoring casing.
TEXT;

$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common_i;
$f["name"] =
// ********************
       "ieraseLast_fn";
// ********************
$f["syntax"][]  = <<<TEXT
string ieraseLast_fn ( string sInput, string sSearchFor );
TEXT;
$f["params"][]  = array ( "string", "sSearchFor", "String to search for." );
$f["params"][]  = array ( "string", "RETURN", "The trimmed/modified string." );

$f["desc"]      = <<<TEXT
Erase last occurence of sSearchFor string in input string - ignoring casing.
TEXT;

$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common_i;
$f["name"] =
// ********************
       "ieraseAll_fn";
// ********************
$f["syntax"][]  = <<<TEXT
string ieraseAll_fn ( string sInput, string sSearchFor );
TEXT;
$f["params"][]  = array ( "string", "sSearchFor", "String to search for." );
$f["params"][]  = array ( "string", "RETURN", "The trimmed/modified string." );

$f["desc"]      = <<<TEXT
Erase all occurences of sSearchFor string in input string - ignoring casing.
TEXT;

$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common_i;
$f["name"] =
// ********************
       "ieraseRegex_fn";
// ********************
$f["syntax"][]  = <<<TEXT
string ieraseRegex_fn ( string sInput, string sSearchFor );
TEXT;
$f["params"][]  = array ( "string", "sSearchFor", "Regular expression to search for." );
$f["params"][]  = array ( "string", "RETURN", "The trimmed/modified string." );

$f["desc"]      = <<<TEXT
Erase part of input string that matches the regular expression - ignoring casing.
TEXT;

$f["seealso"]       = "itrimRegex_fn, eraseRegex_fn";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "trimIntegerCustom_fn";
// ********************
$f["syntax"][]  = <<<TEXT
string trimIntegerCustom_fn( string sInput, string iBase, string sThousandsSep);
TEXT;
$f["params"][]  = array ( "string", "iBase", "Base to use in conversion. Typically \"10\"" );
$f["params"][]  = array ( "string", "sThousandsSep", "Character used as thousands separator." );
$f["params"][]  = array ( "string", "RETURN", "A string containing the first integer found in the input." );

$f["desc"]      = <<<TEXT
Searches the input string for the first occurence that could represent an integer. An integer is any non fractional number found 
in the string like for eaxample 123 or 12, but not 12.34 or 123.56. This custom version of the trimInteger_fn you 
can specify the base, which typically would be 10, but could be for example 2 for parsing a binary number. 
You can also specify which character to use as thousands separator. For example in Denmark the thousands separator is 
"." and not ",".
TEXT;

$f["seealso"]       = "trimNumberCustom_fn, trimInteger_fn";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "trimNumberCustom_fn";
// ********************
$f["syntax"][]  = <<<TEXT
string trimNumberCustom_fn( string sInput, string sDecimalPoint, string sThousandsSep);
TEXT;
$f["params"][]  = array ( "string", "sDecimalPoint", "Character used as decimal point." );
$f["params"][]  = array ( "string", "sThousandsSep", "Character used as thousands separator." );
$f["params"][]    = array ( "string", "RETURN", "A string containing the first number found in the input." );

$f["desc"]      = <<<TEXT
Searches the input string for the first occurence that could represent a number. A number is for eaxample 123.12 or 12.1, 
and also non fractional/integer numbers like 7 and 678. 
This custom version of the trimNumber_fn you can specify both the decimal point and thousands separator characters. 
For example in Denmark those are excactly opposite of english convention meaning that the decimal point is comma "," and 
the thousands separator is the dot ".".
TEXT;

$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;
 

$f = $f_common;
$f["name"] =
// ********************
       "replaceFirst_fn";
// ********************
$f["syntax"][]  = <<<TEXT
string replaceFirst_fn ( string sInput, string sSearchFor, string sReplaceWith );
TEXT;
$f["params"][]  = array ( "string", "sSearchFor", "String to search for" );
$f["params"][]  = array ( "string", "sReplaceWith", "String that should replace the sSearchFor part." );
$f["params"][]  = array ( "string", "RETURN", "The trimmed/modified string." );

$f["desc"]      = <<<TEXT
Replace first occurence of sSearchFor in input with the replace string.
TEXT;

$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "replaceLast_fn";
// ********************
$f["syntax"][]  = <<<TEXT
string replaceLast_fn ( string sInput, string sSearchFor, string sReplaceWith );
TEXT;
$f["params"][]  = array ( "string", "sSearchFor", "String to search for" );
$f["params"][]  = array ( "string", "sReplaceWith", "String that should replace the sSearchFor part." );
$f["params"][]  = array ( "string", "RETURN", "The trimmed/modified string." );

$f["desc"]      = <<<TEXT
Replace last occurence of sSearchFor in input with the replace string.
TEXT;

$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "replaceAll_fn";
// ********************
$f["syntax"][]  = <<<TEXT
string replaceAll_fn ( string sInput, string sSearchFor, string sReplaceWith );
TEXT;
$f["params"][]  = array ( "string", "sSearchFor", "String to search for" );
$f["params"][]  = array ( "string", "sReplaceWith", "String that should replace the sSearchFor part." );
$f["params"][]  = array ( "string", "RETURN", "The trimmed/modified string." );

$f["desc"]      = <<<TEXT
Replace all occurences of sSearchFor in input with the replace string.
TEXT;

$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common_i;
$f["name"] =
// ********************
       "ireplaceFirst_fn";
// ********************
$f["syntax"][]  = <<<TEXT
string ireplaceFirst_fn ( string sInput, string sSearchFor, string sReplaceWith );
TEXT;
$f["params"][]  = array ( "string", "sSearchFor", "String to search for" );
$f["params"][]  = array ( "string", "sReplaceWith", "String that should replace the sSearchFor part." );
$f["params"][]  = array ( "string", "RETURN", "The trimmed/modified string." );

$f["desc"]      = <<<TEXT
Replace first occurence of sSearchFor in input with the replace string - ignoring casing.
TEXT;

$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common_i;
$f["name"] =
// ********************
       "ireplaceLast_fn";
// ********************
$f["syntax"][]  = <<<TEXT
string ireplaceLast_fn ( string sInput, string sSearchFor, string sReplaceWith );
TEXT;
$f["params"][]  = array ( "string", "sSearchFor", "String to search for" );
$f["params"][]  = array ( "string", "sReplaceWith", "String that should replace the sSearchFor part." );
$f["params"][]  = array ( "string", "RETURN", "The trimmed/modified string." );

$f["desc"]      = <<<TEXT
Replace last occurence of sSearchFor in input with the replace string - ignoring casing.
TEXT;

$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common_i;
$f["name"] =
// ********************
       "ireplaceAll_fn";
// ********************
$f["syntax"][]  = <<<TEXT
string ireplaceAll_fn ( string sInput, string sSearchFor, string sReplaceWith );
TEXT;
$f["params"][]  = array ( "string", "sSearchFor", "String to search for" );
$f["params"][]  = array ( "string", "sReplaceWith", "String that should replace the sSearchFor part." );
$f["params"][]  = array ( "string", "RETURN", "The trimmed/modified string." );

$f["desc"]      = <<<TEXT
Replace all occurences of sSearchFor in input with the replace string - ignoring casing.
TEXT;

$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "replaceRegex_fn";
// ********************
$f["syntax"][]  = <<<TEXT
string replaceRegex_fn ( string sInput, string sSearchFor, string sReplaceWith );
TEXT;
$f["params"][]  = array ( "string", "sSearchFor", "Regular expression to search for." );
$f["params"][]  = array ( "string", "sReplaceWith", "String that should replace the sSearchFor part." );
$f["params"][]  = array ( "string", "RETURN", "The trimmed/modified string." );

$f["desc"]      = <<<TEXT
Replace part of input string that matches the regular expression with sReplaceWith.
TEXT;

$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "replaceAllRegex_fn";
// ********************
$f["syntax"][]  = <<<TEXT
string replaceAllRegex_fn ( string sInput, string sSearchFor, string sReplaceWith );
TEXT;
$f["params"][]  = array ( "string", "sSearchFor", "Regular expression to search for." );
$f["params"][]  = array ( "string", "sReplaceWith", "String that should replace the sSearchFor part." );
$f["params"][]  = array ( "string", "RETURN", "The trimmed/modified string." );

$f["desc"]      = <<<TEXT
Replace all parts of input string that matches the regular expression with sReplaceWith.
TEXT;

$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "eraseNth_fn";
// ********************
$f["syntax"][]  = <<<TEXT
string eraseNth_fn ( string sInput, string sSearchFor, int iNth     );
string eraseNth_fn ( string sInput, string sSearchFor, string sNth  );
TEXT;
$f["params"][]  = array ( "string", "sSearchFor", "Regular expression to search for." );
$f["params"][]  = array ( "int", "iNth", "Occurence of sSearchFor string to erase." );
$f["params"][]  = array ( "string", "sNth", "Occurence of sSearchFor string to erase. String should represent an integer." );
$f["params"][]  = array ( "string", "RETURN", "The trimmed/modified string." );

$f["desc"]      = <<<TEXT
Erase the Nth occurence of the sSearchFor in the input string.
TEXT;

$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common_i;
$f["name"] =
// ********************
       "ieraseNth_fn";
// ********************
$f["syntax"][]  = <<<TEXT
string ieraseNth_fn ( string sInput, string sSearchFor, int iNth    );
string ieraseNth_fn ( string sInput, string sSearchFor, string sNth );
TEXT;
$f["params"][]  = array ( "string", "sSearchFor", "Regular expression to search for." );
$f["params"][]  = array ( "int", "iNth", "Occurence of sSearchFor string to erase." );
$f["params"][]  = array ( "string", "sNth", "Occurence of sSearchFor string to erase. String should represent an integer." );
$f["params"][]  = array ( "string", "RETURN", "The trimmed/modified string." );

$f["desc"]      = <<<TEXT
Erase the Nth occurence of the sSearchFor in the input string - ignoring casing.
TEXT;

$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "replaceNth_fn";
// ********************
$f["syntax"][]  = <<<TEXT
string replaceNth_fn ( string sInput, string sSearchFor, string sReplaceWith, int iNth    );
string replaceNth_fn ( string sInput, string sSearchFor, string sReplaceWith, string sNth );
TEXT;
$f["params"][]  = array ( "string", "sSearchFor", "Regular expression to search for." );
$f["params"][]  = array ( "string", "sReplaceWith", "String that should replace the sSearchFor part." );
$f["params"][]  = array ( "int", "iNth", "Occurence of sSearchFor string to erase." );
$f["params"][]  = array ( "string", "sNth", "Occurence of sSearchFor string to erase. String should represent an integer." );
$f["params"][]  = array ( "string", "RETURN", "The trimmed/modified string." );

$f["desc"]      = <<<TEXT
Replace the Nth occurence of the sSearchFor in the input string with the sReplaceWith.
TEXT;

$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common_i;
$f["name"] =
// ********************
       "ireplaceNth_fn";
// ********************
$f["syntax"][]  = <<<TEXT
string ireplaceNth_fn ( string sInput, string sSearchFor, string sReplaceWith, int iNth    );
string ireplaceNth_fn ( string sInput, string sSearchFor, string sReplaceWith, string sNth );
TEXT;
$f["params"][]  = array ( "string", "sSearchFor", "Regular expression to search for." );
$f["params"][]  = array ( "string", "sReplaceWith", "String that should replace the sSearchFor part." );
$f["params"][]  = array ( "int", "iNth", "Occurence of sSearchFor string to erase." );
$f["params"][]  = array ( "string", "sNth", "Occurence of sSearchFor string to erase. String should represent an integer." );
$f["params"][]  = array ( "string", "RETURN", "The trimmed/modified string." );

$f["desc"]      = <<<TEXT
Replace the Nth occurence of the sSearchFor in the input string with the sReplaceWith - ignoring casing.
TEXT;

$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


    
?>
