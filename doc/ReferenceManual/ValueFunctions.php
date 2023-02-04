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
$f["seealso"]   = "all-functions, all-function-groups";
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
