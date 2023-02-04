<?php

$f = array();
$f["name"] =
// **************************
       "URL queue functions";
// **************************

$f["type"]      = "group";
$f["desc"]      = <<<TEXT
Functions for appending and quering the global url queue. Most often you just need 
to use urlQueueAppendUnique and urlQueueSize.
TEXT;
$f["note"][]   = "";
$f["seealso"]  = "all-functions, all-function-groups";
$a[] = $f;


$f = array();
$f["name"] =
// ********************
       "LinkTypes";
// ********************
$f["type"]      = "enum";
$f["group"]     = "URL queue functions";

$f["values"][]	= array ( "LINK_TYPE_LOCAL", "Site local link." );
$f["values"][]	= array ( "LINK_TYPE_EXTERNAL", "link to another site." );
$f["values"][]	= array ( "LINK_TYPE_ALL", "All link types local, external." );

$f["desc"]      = <<<TEXT
URL link types. Can designate local, external or both types.
TEXT;
$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


// --- Common function properties ---
$f_common = array();
$f_common["type"]      = "function";
$f_common["group"]     = "URL queue functions";


$f = $f_common;
$f["name"] =
// ********************
       "urlQueueSize";
// ********************
$f["syntax"][]  = <<<TEXT
int urlQueueSize();
TEXT;
$f["params"][]    = array ( "int", "RETURN", "Size of current url queue." );

$f["desc"]      = <<<TEXT
TEXT;
$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
Get size of current url queue.
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "urlQueueSizeProcessed";
// ********************
$f["syntax"][]  = <<<TEXT
int urlQueueSizeProcessed();
TEXT;
$f["params"][]    = array ( "int", "RETURN", "Size of current processed urls list." );

$f["desc"]      = <<<TEXT
TEXT;
$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
Get size of current processed urls list.
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "urlQueueAlreadyProcessed";
// ********************
$f["syntax"][]  = <<<TEXT
bool urlQueueAlreadyProcessed( string sUrl );
TEXT;
$f["params"][]    = array ( "string", "sUrl", "Url to test" );
$f["params"][]    = array ( "bool", "RETURN", "true if url has already been processed." );

$f["desc"]      = <<<TEXT
Test if a given url has already been processed - i.e. has been taken from the urlQueue and loaded.
TEXT;
$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "urlQueueClear";
// ********************
$f["syntax"][]  = <<<TEXT
void urlQueueClear ();
TEXT;

$f["desc"]      = <<<TEXT
Clears global url queue.
TEXT;
$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "urlQueueFront";
// ********************
$f["syntax"][]  = <<<TEXT
string urlQueueFront ();
TEXT;
$f["params"][]    = array ( "string", "RETURN", "Front element of url queue." );

$f["desc"]      = <<<TEXT
Get front element of global url queue.
TEXT;
$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "urlQueueAppend";
// ********************
$f["syntax"][]  = <<<TEXT
void urlQueueAppend ( string sUrl );
void urlQueueAppend ( int iLinkType, string sTest ="", string sCompareFun = DefaultCompareFun );
TEXT;
$f["params"][]    = array ( "string", "sUrl", "Url to append to end of global queue." );
$f["params"][]    = array ( "enum", "iLinkType", "Linktype to append. See LinkTypes." );
$f["params"][]    = array ( "string", "sTest", "String to use as test when applying sCompareFun to each url." );
$f["params"][]    = array ( "string", "sCompareFun", "Name of compare function/operator to use like e.g. contains, equals, endsWith" );

$f["desc"]      = <<<TEXT
Form 1:
Append specific url to global url queue. 
Form 2:
Append all '<A ... href=SOME-URL ...></A>' urls to global url queue matching the given string and 
using given compare function/operator.

This way of adding urls allows for duplicates in the url queue, see urlQueueAppendUnique.

TEXT;
$f["seealso"]       = "urlQueueAppendUnique";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "urlQueueAppendUnique";
// ********************
$f["syntax"][]  = <<<TEXT
void urlQueueAppendUnique ( string sUrl );
void urlQueueAppendUnique ( int iLinkType, string sTest ="", string sCompareFun = DefaultCompareFun );
TEXT;
$f["params"][]    = array ( "string", "sUrl", "Url to append to end of global queue." );
$f["params"][]    = array ( "enum", "iLinkType", "Linktype to append. See LinkTypes." );
$f["params"][]    = array ( "string", "sTest", "String to use as test when applying sCompareFun to each url." );
$f["params"][]    = array ( "string", "sCompareFun", "Name of compare function/operator to use like e.g. contains, equals, endsWith" );

$f["desc"]      = <<<TEXT
Form 1:
Uniquely append specific url to global url queue..
Form 2:
Uniquely append all '<A ... href=SOME-URL ...></A>' urls to global url queue matching the given string and using 
given compare function/operator. 

Uniquely means only append url if it is not already in the url queue or in the list of 
already processed urls.
TEXT;
$f["seealso"]       = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "urlQueuePrepend";
// ********************
$f["syntax"][]  = <<<TEXT
void urlQueuePrepend ( string sUrl );
TEXT;
$f["params"][]    = array ( "string", "sUrl", "Url to prepend to front of global queue." );

$f["desc"]      = <<<TEXT
Prepend specific url to front of global url queue. This way of adding urls 
allows for duplicates in the url queue, see urlQueuePrependUnique
TEXT;
$f["seealso"]       = "urlQueueAppend, urlQueuePrependUnique";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "urlQueuePrependUnique";
// ********************
$f["syntax"][]  = <<<TEXT
void urlQueuePrependUnique ( string sUrl );
TEXT;
$f["params"][]    = array ( "string", "sUrl", "Url to prepend to front of global queue." );

$f["desc"]      = <<<TEXT
Prepend specific url to front of global url queue. This way of adding urls 
allows for duplicates in the url queue, see urlQueuePrependUnique

Uniquely means only append url if it is not already in the url queue or in the list of 
already processed urls.
TEXT;
$f["seealso"]       = "urlQueueAppend, urlQueuePrepend";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;
?>
