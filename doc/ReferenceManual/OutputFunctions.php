<?php

$f = array();
$f["name"] =
// **************************
       "Output functions";
// **************************

$f["type"]      = "group";
   $f["desc"]      = <<<TEXT
Functions for writing data to the output.
TEXT;
$f["note"][]   = "";
$f["seealso"]  = "all-functions, all-function-groups";
$a[] = $f;


// --- Common function properties ---
$f_common = array();
$f_common["type"]      = "function";
$f_common["group"]     = "Output functions";


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


?>
