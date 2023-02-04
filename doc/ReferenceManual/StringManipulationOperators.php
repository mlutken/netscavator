<?php
// --- Common function properties ---
$f_common = array();
$f_common["type"]      = "operator";
$f_common["group"]     = "String manipulation operators";
$f_common["params"][]  = array ( "string", "sInput", "Source string for manipulation. Typically operators are used with outputValue, outputValueFind style functions, where the input string is implicit in that it will be the value at the current node in the dom tree. This is why we denote it like this in the syntax {sInput}" );

$f_common_i = $f_common;
$f_common_i["note"][]   = "Currently the case insensitive operators are only working properly for english letters a-z,A-Z. This will be corrected in a future release.";



$f = array();
$f["name"] =
// ******************************
       "String manipulation operators";
// ******************************

$f["type"]      = "group";
$f["desc"]      = <<<TEXT
A collection of operators that manipulate strings like: "eraseAll", "toUpper", etc.
These are normal callable PHP functions. Use same names without quotes and with "_fn" 
appended for the equivalent normal function. 
TEXT;
$f["seealso"]   = "string-manipulation-functions, all-functions, all-function-groups";
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "trimDefault";
// ********************
$f["syntax"][]  = <<<TEXT
"trimDefault", {sInput}
TEXT;
$f["params"][]    = array ( "string", "RETURN", "The trimmed/modified string." );

$f["desc"]      = <<<TEXT
Performs default trimming of a string.  
Modifications performed:
(1) Replace all newlines and HTML non-breakable-spaces with spaces.
(2) Collapsing consecutive spaces to one.
(3) Remove whitespace at the ends. Same as trimEnds

This trim operator is called from every output function as the last thing, even if you specified 
another manipulator, like "replaceAll" the "trimDefault" will still be applied after. You can prevent this by using a manipulator 
that has "raw" in its name like the manipulator raw or for example a custom PHP function called e.g. 'rawMyManipulator'. 
TEXT;

$f["seealso"]       = "trimDefault, trimEnds";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "raw";
// ********************
$f["syntax"][]  = <<<TEXT
"raw", {sInput}
TEXT;
$f["params"][]    = array ( "string", "RETURN", "The raw unmodified string." );

$f["desc"]      = <<<TEXT
Output string as is, witout any processing. For example 'outputValue("product_name", "raw");'. 
This causes the normal applied trimDefault to be bypassed. 
TEXT;

$f["seealso"]       = "trimDefault";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "toUpper";
// ********************
$f["syntax"][]  = <<<TEXT
"toUpper", {sInput}
TEXT;
$f["params"][]    = array ( "string", "RETURN", "The string with all letters in uppercase/capital." );

$f["desc"]      = <<<TEXT
Uppercase all characters in string.
TEXT;

$f["note"][]        = "Currently this function is only working properly for english letters a-z,A-Z. This will be corrected in a future release.";
$f["seealso"]       = "toLower";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;

$f = $f_common;
$f["name"] =
// ********************
       "toLower";
// ********************
$f["syntax"][]  = <<<TEXT
"toLower", {sInput}
TEXT;
$f["params"][]    = array ( "string", "RETURN", "The string with all letters in lowercase." );

$f["desc"]      = <<<TEXT
Lowercase all characters in string.
TEXT;

$f["note"][]        = "Currently this function is only working properly for english letters a-z,A-Z. This will be corrected in a future release.";
$f["seealso"]       = "toUpper";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;

$f = $f_common;
$f["name"] =
// ********************
       "trimEnds";
// ********************
$f["syntax"][]  = <<<TEXT
"trimEnds", {sInput}
TEXT;
$f["params"][]    = array ( "string", "RETURN", "The trimmed/modified string." );

$f["desc"]      = <<<TEXT
Removes spaces and tabs at both ends of the string.
TEXT;

$f["seealso"]       = "trimLeft, trimRight";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;

$f = $f_common;
$f["name"] =
// ********************
       "trimLeft";
// ********************
$f["syntax"][]  = <<<TEXT
"trimLeft", {sInput}
TEXT;
$f["params"][]    = array ( "string", "RETURN", "The trimmed/modified string." );

$f["desc"]      = <<<TEXT
Removes spaces and tabs from left part (start) of the string.
TEXT;

$f["seealso"]       = "trimRight, trimEnds";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;

$f = $f_common;
$f["name"] =
// ********************
       "trimRight";
// ********************
$f["syntax"][]  = <<<TEXT
"trimRight", {sInput}
TEXT;
$f["params"][]    = array ( "string", "RETURN", "The trimmed/modified string." );

$f["desc"]      = <<<TEXT
Removes spaces and tabs from right part (end) of the string.
TEXT;

$f["seealso"]       = "trimLeft, trimEnds";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;

$f = $f_common;
$f["name"] =
// ********************
       "trimYear";
// ********************
$f["syntax"][]  = <<<TEXT
"trimYear", {sInput}
TEXT;
$f["params"][]    = array ( "string", "RETURN", "A string containing a year (4 digits) or an empty string." );

$f["desc"]      = <<<TEXT
Searches the input string for the first occurence that could represent a year. A year is any 4 digits in a row. The year 
is returned as a string containing the 4 digits.
TEXT;

$f["seealso"]       = "trimInteger, trimRegex";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;

$f = $f_common;
$f["name"] =
// ********************
       "trimInteger";
// ********************
$f["syntax"][]  = <<<TEXT
"trimInteger", {sInput}
TEXT;
$f["params"][]    = array ( "string", "RETURN", "A string containing the first integer found in the input." );

$f["desc"]      = <<<TEXT
Searches the input string for the first occurence that could represent an integer. An integer is any non fractional number found 
in the string like for eaxample 123 or 12, but not 12.34 or 123.56. By default the function uses english locale meaning that 
dot "." is used as decimal point/separator and "," is used as thousands separator. To change this behaviour use the configuration 
functions configParseDecimalPointSet, configParseThousandsSepSet.
TEXT;

$f["seealso"]       = "configParseDecimalPointSet, configParseThousandsSepSet, trimIntegerCustom, trimNumber, trimYear";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;

$f = $f_common;
$f["name"] =
// ********************
       "trimNumber";
// ********************
$f["syntax"][]  = <<<TEXT
"trimNumber", {sInput}
TEXT;
$f["params"][]    = array ( "string", "RETURN", "A string containing the first number found in the input." );

$f["desc"]      = <<<TEXT
Searches the input string for the first occurence that could represent a number. A number is for eaxample 123.12 or 12.1, 
and also non fractional/integer numbers like 7 and 678. By default the function uses english locale meaning that "," 
is used as thousands separator. To change this behaviour use the configuration function configParseThousandsSepSet.
TEXT;

$f["seealso"]       = "configParseThousandsSepSet, trimNumberCustom, trimInteger";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "trimCharsEnds";
// ********************
$f["syntax"][]  = <<<TEXT
"trimCharsEnds", {sInput}, sCharsToTrim
TEXT;
$f["params"][]  = array ( "string", "sCharsToTrim", "String containing all chars you want to \"trim\" away. For example \"tBf\" for trimming t, B and f " );
$f["params"][]  = array ( "string", "RETURN", "The string with specified chars removed." );

$f["desc"]      = <<<TEXT
Removes specified chars from both ends of the input string.
TEXT;

$f["note"][]        = "Currently this function is only working properly for english letters a-z,A-Z. This will be corrected in a future release.";
$f["seealso"]       = "trimCharsLeft, trimCharsRight";
$f["examples"][]    = <<<TEXT
// Assume current dom position contains the string: "abcdeff"
outputValue("trim_test", "trimCharsEnds", "af");
// In output file we get => trim_test: bcde
TEXT;
$a[] = $f;
    
$f = $f_common;
$f["name"] =
// ********************
       "trimCharsLeft";
// ********************
$f["syntax"][]  = <<<TEXT
"trimCharsLeft", {sInput}, sCharsToTrim
TEXT;
$f["params"][]  = array ( "string", "sCharsToTrim", "String containing all chars you want to \"trim\" away. For example \"tBf\" for trimming t, B and f " );
$f["params"][]  = array ( "string", "RETURN", "The string with specified chars removed." );

$f["desc"]      = <<<TEXT
Removes specified chars from left/front end of the input string.
TEXT;

$f["note"][]        = "Currently this function is only working properly for english letters a-z,A-Z. This will be corrected in a future release.";
$f["seealso"]       = "trimCharsEnds, trimCharsRight";
$f["examples"][]    = <<<TEXT
// Assume current dom position contains the string: "abcdeff"
outputValue("trim_test", "trimCharsLeft", "ab");
// In output file we get => trim_test: cdeff
TEXT;
$a[] = $f;
    
$f = $f_common;
$f["name"] =
// ********************
       "trimCharsRight";
// ********************
$f["syntax"][]  = <<<TEXT
"trimCharsRight", {sInput}, sCharsToTrim
TEXT;
$f["params"][]  = array ( "string", "sCharsToTrim", "String containing all chars you want to \"trim\" away. For example \"tBf\" for trimming t, B and f " );
$f["params"][]  = array ( "string", "RETURN", "The string with specified chars removed." );

$f["desc"]      = <<<TEXT
Removes specified chars from right/back end of the input string.
TEXT;

$f["note"][]        = "Currently this function is only working properly for english letters a-z,A-Z. This will be corrected in a future release.";
$f["seealso"]       = "trimCharsEnds, trimCharsLeft";
$f["examples"][]    = <<<TEXT
// Assume current dom position contains the string: "abcdeff"
outputValue("trim_test", "trimCharsRight", "f");
// In output file we get => trim_test: abcde
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "trimRegex";
// ********************
$f["syntax"][]  = <<<TEXT
"trimRegex", {sInput}, sRegex
TEXT;
$f["params"][]  = array ( "string", "sRegex", "Regular expression (Perl style). The part that matches gets returned." );
$f["params"][]  = array ( "string", "RETURN", "The matching part of the input when searching using the regular expression." );

$f["desc"]      = <<<TEXT
Returns the sub-string that macthes the regular expression. String is searched using the regular expression and the 
first time it macthes the matching part is returned.
TEXT;

$f["seealso"]       = "itrimRegex, eraseRegex";
$f["examples"][]    = <<<TEXT
// Roll your own trimYear
// Assume current dom position contains the string: "In the year 1989 we saw ..."
outputValue("year", "trimRegex", "\d\d\d\d");
// In output file we get => year: 1989
TEXT;
$a[] = $f;


$f = $f_common_i;
$f["name"] =
// ********************
       "itrimRegex";
// ********************
$f["syntax"][]  = <<<TEXT
"itrimRegex", {sInput}, sRegex
TEXT;
$f["params"][]  = array ( "string", "sRegex", "Regular expression (Perl style). The part that matches gets returned." );
$f["params"][]  = array ( "string", "RETURN", "The matching part of the input when searching using the regular expression." );

$f["desc"]      = <<<TEXT
Returns the sub-string that macthes the regular expression - ignoring casing. String is searched using the regular expression and the 
first time it macthes the matching part is returned.
TEXT;

$f["seealso"]       = "trimRegex, eraseRegex";
$f["examples"][]    = <<<TEXT
// Roll your own trimYear
// Assume current dom position contains the string: "In the year 1989 we saw ..."
outputValue("year", "trimRegex", "\d\d\d\d");
// In output file we get => year: 1989
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "append";
// ********************
$f["syntax"][]  = <<<TEXT
"append", {sInput}, sString
TEXT;
$f["params"][]  = array ( "string", "sString", "String to append." );
$f["params"][]  = array ( "string", "RETURN", "sInput string with sString appended." );

$f["desc"]      = <<<TEXT
Append string to the input string. Same as concatenation operator ".". 
Typically used like this: 'outputValue("price_with_currency", "append", " USD" )'. 
This would write the current value to the ouput with the string " USD" appended. 
TEXT;

$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "prepend";
// ********************
$f["syntax"][]  = <<<TEXT
"prepend", {sInput}, sString
TEXT;
$f["params"][]  = array ( "string", "sString", "String to prepend." );
$f["params"][]  = array ( "string", "RETURN", "sInput string with sString prepended." );

$f["desc"]      = <<<TEXT
Prepend string to the input string. Same as concatenation operator ".". 
Typically be used like this: 'outputValue("url_product", "prepend", "http://www.somesite.com/" )'. 
This would write the current value to the ouput with the site URL "http://www.somesite.com/" prepended.
TEXT;

$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "eraseFirst";
// ********************
$f["syntax"][]  = <<<TEXT
"eraseFirst", {sInput}, sSearchFor
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
       "eraseLast";
// ********************
$f["syntax"][]  = <<<TEXT
"eraseLast", {sInput}, sSearchFor
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
       "eraseAll";
// ********************
$f["syntax"][]  = <<<TEXT
"eraseAll", {sInput}, sSearchFor
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
       "eraseRegex";
// ********************
$f["syntax"][]  = <<<TEXT
"eraseRegex", {sInput}, sSearchForRegex
TEXT;
$f["params"][]  = array ( "string", "sSearchForRegex", "Regular expression to search for." );
$f["params"][]  = array ( "string", "RETURN", "The trimmed/modified string." );

$f["desc"]      = <<<TEXT
Erase part of input string that matches the regular expression.
TEXT;

$f["seealso"]       = "trimRegex, ieraseRegex";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common_i;
$f["name"] =
// ********************
       "ieraseFirst";
// ********************
$f["syntax"][]  = <<<TEXT
"ieraseFirst", {sInput}, sSearchFor
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
       "ieraseLast";
// ********************
$f["syntax"][]  = <<<TEXT
"ieraseLast", {sInput}, sSearchFor
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
       "ieraseAll";
// ********************
$f["syntax"][]  = <<<TEXT
"ieraseAll", {sInput}, sSearchFor
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
       "ieraseRegex";
// ********************
$f["syntax"][]  = <<<TEXT
"ieraseRegex", {sInput}, sSearchFor
TEXT;
$f["params"][]  = array ( "string", "sSearchFor", "Regular expression to search for." );
$f["params"][]  = array ( "string", "RETURN", "The trimmed/modified string." );

$f["desc"]      = <<<TEXT
Erase part of input string that matches the regular expression - ignoring casing.
TEXT;

$f["seealso"]       = "itrimRegex, eraseRegex";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "trimIntegerCustom";
// ********************
$f["syntax"][]  = <<<TEXT
"trimIntegerCustom", {sInput}, iBase, sThousandsSep
TEXT;
$f["params"][]  = array ( "string", "iBase", "Base to use in conversion. Typically \"10\"" );
$f["params"][]  = array ( "string", "sThousandsSep", "Character used as thousands separator." );
$f["params"][]  = array ( "string", "RETURN", "A string containing the first integer found in the input." );

$f["desc"]      = <<<TEXT
Searches the input string for the first occurence that could represent an integer. An integer is any non fractional number found 
in the string like for eaxample 123 or 12, but not 12.34 or 123.56. This custom version of the trimInteger you 
can specify the base, which typically would be 10, but could be for example 2 for parsing a binary number. 
You can also specify which character to use as thousands separator. For example in Denmark the thousands separator is 
"." and not ",".
TEXT;

$f["seealso"]       = "trimNumberCustom, trimInteger";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "trimNumberCustom";
// ********************
$f["syntax"][]  = <<<TEXT
"trimNumberCustom", {sInput}, sDecimalPoint, sThousandsSep
TEXT;
$f["params"][]  = array ( "string", "sDecimalPoint", "Character used as decimal point." );
$f["params"][]  = array ( "string", "sThousandsSep", "Character used as thousands separator." );
$f["params"][]    = array ( "string", "RETURN", "A string containing the first number found in the input." );

$f["desc"]      = <<<TEXT
Searches the input string for the first occurence that could represent a number. A number is for eaxample 123.12 or 12.1, 
and also non fractional/integer numbers like 7 and 678. 
This custom version of the trimNumber you can specify both the decimal point and thousands separator characters. 
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
       "replaceFirst";
// ********************
$f["syntax"][]  = <<<TEXT
"replaceFirst", {sInput}, sSearchFor, sReplaceWith
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
       "replaceLast";
// ********************
$f["syntax"][]  = <<<TEXT
"replaceLast", {sInput}, sSearchFor, sReplaceWith
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
       "replaceAll";
// ********************
$f["syntax"][]  = <<<TEXT
"replaceAll", {sInput}, sSearchFor, sReplaceWith
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
       "ireplaceFirst";
// ********************
$f["syntax"][]  = <<<TEXT
"ireplaceFirst", {sInput}, sSearchFor, sReplaceWith
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
       "ireplaceLast";
// ********************
$f["syntax"][]  = <<<TEXT
"ireplaceLast", {sInput}, sSearchFor, sReplaceWith
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
       "ireplaceAll";
// ********************
$f["syntax"][]  = <<<TEXT
"ireplaceAll", {sInput}, sSearchFor, sReplaceWith
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
       "replaceRegex";
// ********************
$f["syntax"][]  = <<<TEXT
"replaceRegex", {sInput}, sSearchFor, sReplaceWith
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
       "replaceAllRegex";
// ********************
$f["syntax"][]  = <<<TEXT
"replaceAllRegex", {sInput}, sSearchFor, sReplaceWith
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
       "eraseNth";
// ********************
$f["syntax"][]  = <<<TEXT
"eraseNth", {sInput}, sSearchFor, sNth
TEXT;
$f["params"][]  = array ( "string", "sSearchFor", "Regular expression to search for." );
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
       "ieraseNth";
// ********************
$f["syntax"][]  = <<<TEXT
"ieraseNth", {sInput}, sSearchFor, sNth
TEXT;
$f["params"][]  = array ( "string", "sSearchFor", "Regular expression to search for." );
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
       "replaceNth";
// ********************
$f["syntax"][]  = <<<TEXT
"replaceNth", {sInput}, sSearchFor, sReplaceWith, sNth
TEXT;
$f["params"][]  = array ( "string", "sSearchFor", "Regular expression to search for." );
$f["params"][]  = array ( "string", "sReplaceWith", "String that should replace the sSearchFor part." );
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
       "ireplaceNth";
// ********************
$f["syntax"][]  = <<<TEXT
"ireplaceNth", {sInput}, sSearchFor, sReplaceWith, sNth
TEXT;
$f["params"][]  = array ( "string", "sSearchFor", "Regular expression to search for." );
$f["params"][]  = array ( "string", "sReplaceWith", "String that should replace the sSearchFor part." );
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
