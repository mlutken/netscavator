<?php

$f = array();
$f["name"] =
// **************************
       "Node actions";
// **************************
$f["parse_name"] = "NodeActions";

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
$f["seealso"]   = "all-functions, all-function-groups";
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
bool nodeClick ( int iSearchDir = NEAREST_AUTO );
TEXT;
$f["params"][]    = array ( "int", "iSearchDir", "Specify how to search for the ELEMENT node to apply the action. See DomSearchDirModes and 'Node actions'." );
$f["params"][]    = array ( "bool", "RETURN", "True if a node could be found and the action applied." );

$f["desc"]      = <<<TEXT
Perform a mouse "click" operation on the "current node". If for some reason this does not work you could 
try calling nodeClickLoadHref, which in case current node is a A href, will try to load this URL directly. 

TEXT;
$f["seealso"]       = "nodeClickLoadHref, doAction";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "nodeClickLoadHref";
// ********************
$f["syntax"][]  = <<<TEXT
bool nodeClickLoadHref ( int iSearchDir = NEAREST_AUTO );
TEXT;
$f["params"][]    = array ( "int", "iSearchDir", "Specify how to search for the ELEMENT node to apply the action. See DomSearchDirModes and 'Node actions'." );
$f["params"][]    = array ( "bool", "RETURN", "True if a node could be found and the action applied." );

$f["desc"]      = <<<TEXT
Perform a mouse "click" operation on the "current node". Often you will perform this click on a A ELEMENT 
in which case you will get the href=link-to-some-page URL loaded directly. Normally you should only use this function 
in case the default nodeClick does not work in your specific case. 
TEXT;
$f["seealso"]       = "nodeClick";
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
       "nodeJavaScriptEvaluate";
// ********************
$f["syntax"][]  = <<<TEXT
bool nodeJavaScriptEvaluate ( string sJavaScript, int iSearchDir);
bool nodeJavaScriptEvaluate ( string sJavaScript  );
TEXT;
$f["params"][]    = array ( "string", "sJavaScript", "Javascript string to evaluate at current element." );
$f["params"][]    = array ( "int", "iSearchDir", "Specify how to search for the ELEMENT node to apply the action. See DomSearchDirModes and 'Node actions'." );
$f["params"][]    = array ( "bool", "RETURN", "True if a node could be found and the javascript evaluated." );

$f["desc"]      = <<<TEXT
Evaluate javascript with current element as 'this'. 
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
