<?php
// --- Common function properties ---
$f_common = array();
$f_common["type"]      = "function";
$f_common["group"]     = "Config functions";



$f = array();
$f["name"] =
// **************************
       "Config functions";
// **************************

$f["type"]      = "group";
$f["desc"]      = <<<TEXT
General configuration functions. 
TEXT;
$f["functions"]  = array();
$f["seealso"]   = "all-functions, all-function-groups";
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "configUrlUploadDataSet";
// ********************
$f["syntax"][]  = <<<TEXT
void configUrlUploadDataSet ( string sUrl );
TEXT;
$f["params"][]    = array ( "string", "sUrl", "Server url to which to POST upload the files to using the uploadFileHttpPost function." );

$f["desc"]      = <<<TEXT
Set URL for use by built-in POST function uploadFileHttpPost, which is used by default for uploading to a server. 
Can also be set from the command line using "--upload-url=http//upload.myserver.com".
TEXT;

$f["seealso"]   = "configUrlUploadDataGet, uploadFileHttpPost";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "configUrlUploadDataGet";
// ********************
$f["syntax"][]  = <<<TEXT
string configUrlUploadDataGet ();
TEXT;
$f["params"][]    = array ( "int", "RETURN", "Server Url used by the uploadFileHttpPost function." );

$f["desc"]      = <<<TEXT
Get URL for used by built-in POST function uploadFileHttpPost.
TEXT;

$f["seealso"]   = "configUrlUploadDataSet, uploadFileHttpPost";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "configDisableLoadImages";
// ********************
$f["syntax"][]  = <<<TEXT
void configDisableLoadImages () ;
TEXT;
$f["params"]    = [];

$f["desc"]      = <<<TEXT
Force disable loading of images. 
Can also be set from the command line using "--load-images=no".
TEXT;

$f["seealso"]   = "configForceLoadImages";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "configForceLoadImages";
// ********************
$f["syntax"][]  = <<<TEXT
void configForceLoadImages ();
TEXT;
$f["params"]    = [];

$f["desc"]      = <<<TEXT
Force loading of images. 
Can also be set from the command line using "--load-images=yes".
TEXT;

$f["seealso"]   = "configDisableLoadImages";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "configAddIncludeUrl";
// ********************
$f["syntax"][]  = <<<TEXT
void configAddIncludeUrl ( string sPattern, string sCompareOperator );
TEXT;
$f["params"][]    = array ( "string", "sPattern", "Pattern to use when comparing the url about to be loaded with the compare operator supplied." );
$f["params"][]    = array ( "string", "sCompareOperator", "Compare operator to apply." );

$f["desc"]      = <<<TEXT
Always allow loading URLs matching this pair of (pattern, compare operator). 
You can speed up the crawler by excluding/including URLs that match certain patterns. For example you could disable loading  
any URLs that does not come from the primary site you are crawling using : 
'configAddIncludeUrl ( "somesite.com", "contains" );'.

An URL is considered ok and will be loaded, if it matches any of the (pattern,function) pairs.
<br>
If no INCLUDE patterns is entered (default) then all URLs are cosidered ok to load.
If you have entered both include and exclude URL patterns then first the include patterns are tested 
and only if this test returns true are the exclude patters considered. Again since by default no include 
patterns exists the include test will in this case return true and therefore proceed with testing the 
exclude patterns.

TEXT;

$f["note"]      = "If no INCLUDE patterns is entered (default) then all URLs are cosidered ok to load.";
$f["seealso"]   = "configAddExcludeUrl";
$f["examples"][]    = <<<TEXT
function MyCrawler_doSetup()          
{
    configAddIncludeUrl ( "somesite.com", "contains" ); // Site we are mining
    configAddIncludeUrl ( ".js", "contains" ); // If site gets js files from distrb. network
    ...
}
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "configAddExcludeUrl";
// ********************
$f["syntax"][]  = <<<TEXT
void configAddExcludeUrl ( string sPattern, string sCompareOperator );
TEXT;
$f["params"][]    = array ( "string", "sPattern", "Pattern to use when comparing the url about to be loaded with the compare operator supplied." );
$f["params"][]    = array ( "string", "sCompareOperator", "Compare operator to apply." );

$f["desc"]      = <<<TEXT
Always deny loading URLs matching this pair of (pattern, compare operator). 
You can speed up the crawler by excluding/including URLs that match certain patterns. For example you would often not want to wait for 
the site to load GoogleAnalytics, which you could disable by writing like this: 
'configAddExcludeUrl ( "google-analytics.com", "contains" );'.

If the URL matches any of the (pattern,function) pairs, then it should not be loaded.

If no INCLUDE patterns is entered (default) then all URLs are cosidered ok to load.
If you have entered both include and exclude URL patterns then first the include patterns are tested 
and only if this test returns true are the exclude patters considered. Again since by default no include 
patterns exists the include test will in this case return true and therefore proceed with testing the 
exclude patterns.

TEXT;

$f["seealso"]   = "configAddIncludeUrl";
$f["examples"][]    = <<<TEXT
function MyCrawler_doSetup()          
{
    configAddExcludeUrl ( "google-analytics.com", "contains" );
    ...
}
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "configUploadData";
// ********************
$f["syntax"][]  = <<<TEXT
void configUploadData ( bool bUploadData );
TEXT;
$f["params"][]    = array ( "bool", "bUploadData", "True to upload - false to not upload." );

$f["desc"]      = <<<TEXT
Set whether to upload data or not when done mining.
Can also be set from the command line using "--upload-result=yes/no".
TEXT;

$f["seealso"]   = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "configParseDecimalPointSet";
// ********************
$f["syntax"][]  = <<<TEXT
void configParseDecimalPointSet( string sDecimalPoint );
TEXT;
$f["params"][]    = array ( "string", "sDecimalPoint", "Character to use as decimal point when parsing numbers. Default is \".\"." );

$f["desc"]      = <<<TEXT
Set character to use as decimal point when parsing numbers.
TEXT;

$f["seealso"]   = "configParseThousandsSepSet, trimInteger, trimNumber";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "configParseThousandsSepSet";
// ********************
$f["syntax"][]  = <<<TEXT
void configParseThousandsSepSet( string sThousandsSep );
TEXT;
$f["params"][]    = array ( "string", "sThousandsSep", "Character to use as thousands separator when parsing integers. Default is \",\"." );

$f["desc"]      = <<<TEXT
Set character to use as thousands separator when parsing integers.
TEXT;

$f["seealso"]   = "configParseDecimalPointSet, trimInteger, trimNumber";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "configOutputEncloseCDATA";
// ********************
$f["syntax"][]  = <<<TEXT
void configOutputEncloseCDATA( bool bDoEncloseInCDATA );
TEXT;
$f["params"][]    = array ( "bool", "bDoEncloseInCDATA", "True to enclose - false disable it again. Default is not set." );

$f["desc"]      = <<<TEXT
Control whether to enclose XML output in CDATA sections. Default is not set. For standard XML parsers a number of special 
charaters will not be handled correctly unless you enclose the output in "![CDATA", "]]" like this:

'
<xml><root>
<buy_at_url><![CDATA[http://brasilatino.shop.wosbee.com/PublishedService?file=page&pageID=9&itemcode=20058]]></buy_at_url>
</root></xml>
'
TEXT;

$f["seealso"]   = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "configOutputWriteToFile";
// ********************
$f["syntax"][]  = <<<TEXT
void configOutputWriteToFile ( bool bDoWriteOutputToFile );
TEXT;
$f["params"][]    = array ( "bool", "bDoWriteOutputToFile", "True to disable - false enable writing again. Default is not set - i.e. output IS written to file." );

$f["desc"]      = <<<TEXT
Control whether to actually write the output to the file (and output window in Creator). Usefull if you pick up information 
from both the SearchListing and the ProductPage and do not want to have the information split in two section in the output. You 
can then disable writing when on the SearchListing page and then save the output from each item using contextOutputSaveAs. 
You just use outputValue and outputValueFind as normal and then for each item you call
'contextOutputSaveAs(url-item-product-page);
contextEnd();
'. 
On the ProductPage you load these "fallback" values back using current URL like this: 
'contextFallbackOutputLoad( urlCurrent() );'

See more in the Fallback example: http://www.netscavator.com/content/example-fallback-values
TEXT;

$f["seealso"]   = "contextOutputSaveAs, ";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "configGetRunMode";
// ********************
$f["syntax"][]  = <<<TEXT
string configGetRunMode ();
TEXT;
$f["params"][]    = array ( "string", "RETURN", "Run mode string as specified on the command line." );

$f["desc"]      = <<<TEXT
Get run mode as specified on the command line. The command line using parameter is used like this:
"--run-mode=normal/crawler/debug/create".
TEXT;

$f["seealso"]   = "";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;

?>
