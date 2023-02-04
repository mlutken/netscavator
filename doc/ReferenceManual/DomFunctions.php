<?php

$f = array();
$f["name"] =
// **************************
       "Dom functions";
// **************************

$f["type"]      = "group";
$f["desc"]      = <<<TEXT
Functions used to navigate the dom / linearized dom. These include the workhorses domFind and domFindNext, 
which locate a posistion for example like this: 'domFind ( "DIV, class, MyClass", "equals" );'
TEXT;
$f["functions"]  = array();
$f["seealso"]   = "all-functions, all-function-groups";
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
Search from current position for next that matches a given dom sequence. The function exist in a number of variants,but most often you just need to search for the first position forward that matches like for example:
'domFindNext( "DIV, class, MyClass", "equals" )'. But if you actually wanted to find the third time this sequence appears you could use: 'domFindNext( 3, "DIV, class, MyClass", "equals" )' or even: 'domFindNext( -2, "DIV, class, MyClass", "equals" )' to search for second occurence going backwards.

The dom sequence parameter can be a direct (inline) specified sequence like "DIV, class, MyClass" in which case you also MUST specify the compare function. 
The sequence can also refer to a "named" dom sequence created using domSeqCreate like for example: 
'domSeqCreate("ProductUrlPos", "DIV, href, /products/", "contains" )', and then using like:
'domFindNext( 1, "ProductUrlPos" )'. In case you use a form of domFind which have the sCompareFun parameter it will simply be ignored if a named dom sequence is found and used. 
Finally the sSequence parameter can also refer to a PHP function of that name in which case any sCompareFun parameter is also ignored.

The order in which the 3 approaches are used is: PHP function, named dom sequence, direct specified.
TEXT;
$f["seealso"]       = "domFind, domFindPrev, domFindNextPos, domFindNextParams, string-compare-operators";
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
you also MUST specify the compare function. The sequence can also refer to a "named" dom sequence created using domSeqCreate like for example: 
'domSeqCreate("ProductUrlPos", "DIV, href, /products/", "contains" )', and then using like:
'domFindPrev( "ProductUrlPos", "equals" )' . In this case the sCompareFun parameter will simply be ignored if a named dom sequence is found and used. 
Finally the sSequence parameter can also refer to a PHP function of that name in which case any sCompareFun 
parameter is also ignored.

The order in which the 3 approaches are used is: PHP function, named dom sequence, direct specified.
TEXT;
$f["seealso"]       = "domFind, domFindNext, string-compare-operators";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


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
Search from start (i.e. the start of document or temporay start set by domSetStartPos) for a position that matches a given dom sequence. 
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
$f["seealso"]       = "domFindNext, domFindPos, domFindPrev, string-compare-operators";
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
$f["seealso"]       = "domFind, domFindPrev, domFindNext, string-compare-operators";
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
Search from start (i.e. the start of document or temporay start set by domSetStartPos) for a position that matches a given dom sequence
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
$f["seealso"]       = "domFindNext, domFind, domFindPrev, string-compare-operators";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "domLoopAll";
// ********************
$f["syntax"][]  = <<<TEXT
int domFind ( string sSequence, string sLoopBodyFun );
TEXT;
$f["params"][]    = array ( "string", "sSequence", "Dom sequence. Can be one of: PHP function, named dom sequence, direct specified" );
$f["params"][]    = array ( "string", "sLoopBodyFun", "Loop 'body' function called for each position found." );
$f["params"][]    = array ( "int", "RETURN", "The last valid position found" );

$f["desc"]      = <<<TEXT
Search from start for all positions that matches a given dom sequence and for each it calls the sLoopBodyFun function. 
(ie the start of document or temporay start set by domSetStartPos).

The sequence must by a "named" dom sequence created using domSeqCreate like for example: 
'domSeqCreate("ProductStart", "DIV, href, item", "contains" )', and then using like:
'domLoopAll( "ProductUrlPos", "Crawler_SearchListing_GetProduct" )'. 

Before calling the sLoopBodyFun the domLoopAll sets a temporary start position to the position found and then searches 
forward to the next matching position, which is then set as a stop position. 
This means that within the sLoopBodyFun you will allways start searching from the beginnning of the current section/product 
and you will never "fall through" to the next product thanks to the stop position.

The function works equivalent to the follwing:
'
function domLoopAllNext(\$domSeq, \$loopFunction)
{
    domNewSearch();
	\$lastPos = 0;
    while ( domFindNext ( 1, \$domSeq ) ) {
        domPointerPush();
		\$lastPos = domGetPos();
        domSetStartPos( domGetPos() );
        \$iStopPos = domFindNextPos( 1, \$domSeq );
        domSetStopPos( \$iStopPos );
        call_user_func(\$loopFunction);
        domClearStartPos();
        domClearStopPos();
        domPointerPop();
    }
    return \$lastPos;
}
'

TEXT;
$f["seealso"]       = "domLoopAllNext, domSeqCreate";
$f["examples"][]    = <<<TEXT
function Crawler_SearchListing_mine()            
{
	domLoopAll("ProductStartSeq", "Loop_SearchListing_GetProduct" );
}

function Loop_SearchListing_GetProduct()            
{
   // Get product name and  product price
    contextBegin("product");
    outputValueFind( 1, "ProductNameSeq", "product_name", "eraseAll", ":" ); // Get value from Navigator attribute by fallback on fail to find dom pos
    outputValueFind( 1, "ProductPriceSeq", "product_price", "trimNumber" );
    outputValueFind( 1, "", "sex" );   // Get value from Navigator attribute by fallback on fail to find dom pos
    outputDirect ( "fabric" , navAttributeGet("fabric") );  // Gettting the attribute value directly  
    outputDirect ( "currency_name" , "EUR" );  
    outputDirect ( "navigator_state", navStateString() );   // Write the navigator state for demo/debug
    outputDirect ( "nav_state_indices", navCurrentStateIndicesGet() );   // Write the navigator state indices for demo/debug
    outputDirect ( "dbg_state_progress", (string)navLastStateIndexGet() . " / " . navStateIndexGet() ); 
    contextEnd();
}
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "domLoopAllNext";
// ********************
$f["syntax"][]  = <<<TEXT
int domLoopAllNext ( string sSequence, string sLoopBodyFun );
TEXT;
$f["params"][]    = array ( "string", "sSequence", "Dom sequence. Can be one of: PHP function, named dom sequence, direct specified" );
$f["params"][]    = array ( "string", "sLoopBodyFun", "Loop 'body' function called for each position found." );
$f["params"][]    = array ( "int", "RETURN", "The last valid position found" );

$f["desc"]      = <<<TEXT
Search current dom position for all positions that matches a given dom sequence and for each it calls the sLoopBodyFun function.
It is the "Next" version of domLoopAll.

The sequence must by a "named" dom sequence created using domSeqCreate like for example: 
'domSeqCreate("ProductStart", "DIV, href, item", "contains" )', and then using like:
'domLoopAll( "ProductUrlPos", "Crawler_SearchListing_GetProduct" )'. 

Before calling the sLoopBodyFun the domLoopAll sets a temporary start position to the position found and then searches 
forward to the next matching position, which is then set as a stop position. 
This means that within the sLoopBodyFun you will allways start searching from the beginnning of the current section/product 
and you will never "fall through" to the next product thanks to the stop position.

The function works equivalent to the follwing:
'
function domLoopAllNext(\$domSeq, \$loopFunction)
{
	\$lastPos = 0;
    while ( domFindNext ( 1, \$domSeq ) ) {
        domPointerPush();
		\$lastPos = domGetPos();
        domSetStartPos( domGetPos() );
        \$iStopPos = domFindNextPos( 1, \$domSeq );
        domSetStopPos( \$iStopPos );
        call_user_func(\$loopFunction);
        domClearStartPos();
        domClearStopPos();
        domPointerPop();
    }
    return \$lastPos;
}
'

TEXT;
$f["seealso"]       = "domLoopAll, domSeqCreate";
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
void domSeqCreate ( string sName, string sSequence, string sCompareFun, int iPostMatchSteps, string sCommaChar  );
void domSeqCreate ( string sName, string sSequence, string sCompareFun, int iPostMatchSteps  );
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
