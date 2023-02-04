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
<pre>
contextBegin("product");
outputDirect("type", "Pants" );
outputDirect("brand", "Lewis" );
contextEnd();
</pre>
Will give an XML like:
<code>
&lt;product&gt;<br />
    &lt;type&gt;Pants&lt;/type&gt;<br />
    &lt;brand&gt;Lewis&lt;/brand&gt;<br />
&lt;/product&gt;
</code>

Since contextBegin works like pushing onto a stack it is easy to create a context 
within another context. Just rememeber to call contextEnd for every contextBegin.
TEXT;
$f["note"][]   = "";
$f["seealso"]  = "all-functions, all-function-groups";
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
