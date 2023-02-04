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
$f["seealso"]   = "all-functions, all-function-groups";
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
