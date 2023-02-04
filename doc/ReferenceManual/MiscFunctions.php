<?php

// --- Common function properties ---
$f_common = array();
$f_common["type"]      = "function";
$f_common["group"]     = "Misc functions";


$f = array();
$f["name"] =
// **************************
       "Misc functions";
// **************************

$f["type"]      = "group";
$f["desc"]      = <<<TEXT
Miscelaneous functions.
TEXT;
$f["seealso"]   = "all-functions, all-function-groups";
$a[] = $f;

$f = $f_common;
$f["name"] =
// ********************
       "currentMiner";
// ********************
$f["syntax"][]  = <<<TEXT
string currentMiner();
TEXT;
$f["params"][]    = array ( "string", "RETURN", "The name of the current miner." );

$f["desc"]      = <<<TEXT
Get the name of the current miner.
TEXT;

$f["seealso"]       = "currentDataFile";

$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;

$f = $f_common;
$f["name"] =
// ********************
       "currentDataFile";
// ********************
$f["syntax"][]  = <<<TEXT
string currentDataFile();
TEXT;
$f["params"][]    = array ( "string", "RETURN", "The name of the current data (XML) file." );

$f["desc"]      = <<<TEXT
Get the name of the current data file.
TEXT;

$f["seealso"]       = "currentMiner";

$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "curlPostUploadFileSimple";
// ********************
$f["syntax"][]  = <<<TEXT
int curlPostUploadFileSimple( string sURL, string sFieldName, string sFilePath  )   ;
TEXT;
$f["params"][]    = array ( "string", "sURL", "Web server URL to receive the uploaded file." );
$f["params"][]    = array ( "string", "sFieldName", "Field name of webform that receives the file." );
$f["params"][]    = array ( "string", "sFilePath", "Local path to file to POST upload." );
$f["params"][]    = array ( "int", "RETURN", "0 If upload was succesfull. Se cURL error codes: http://curl.haxx.se/libcurl/c/libcurl-errors.html ." );

$f["desc"]      = <<<TEXT
Upload file using http POST to a webform. See the manual for PHP examples for how to make this form, but it's completely standard.
TEXT;

$f["seealso"]       = "uploadFileHttpPost, currentDataFile";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "uploadFileHttpPost";
// ********************
$f["syntax"][]  = <<<TEXT
uploadFileHttpPost();
TEXT;
//$f["params"][]    = array ( "int", "RETURN", "0 If upload was succesfull. Se cURL error codes: http://curl.haxx.se/libcurl/c/libcurl-errors.html ." );

$f["desc"]      = <<<TEXT
Do a POST upload of the current data file. The field name of the form should be "uploadedfile" and the URL is set using 
configUrlUploadDataSet. See the manual for PHP examples on how to make this form.
TEXT;

$f["seealso"]       = "curlPostUploadFileSimple";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "gzCompressFile";
// ********************
$f["syntax"][]  = <<<TEXT
bool gzCompressFile ( string sSrcFilePath, string sDstFilePath );
TEXT;
$f["params"][]    = array ( "string", "sSrcFilePath", "Path to source (uncompressed) file." );
$f["params"][]    = array ( "string", "sDstFilePath", "Path to destination (compressed) file." );
$f["params"][]    = array ( "bool", "RETURN", "True if compressed successfully." );

$f["desc"]      = <<<TEXT
Compress a file using the zlib (gz) compression.
TEXT;

$f["seealso"]       = "gzUnCompressFile";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;


$f = $f_common;
$f["name"] =
// ********************
       "gzUnCompressFile";
// ********************
$f["syntax"][]  = <<<TEXT
bool gzUnCompressFile ( string sSrcFilePath, string sDstFilePath );
TEXT;
$f["params"][]    = array ( "string", "sSrcFilePath", "Path to source (compressed) file." );
$f["params"][]    = array ( "string", "sDstFilePath", "Path to destination (uncompressed) file." );
$f["params"][]    = array ( "bool", "RETURN", "True if uncompressed successfully." );

$f["desc"]      = <<<TEXT
Uncompress a file using the zlib (gz) uncompression.
TEXT;

$f["seealso"]       = "gzCompressFile";
$f["examples"][]    = <<<TEXT
TEXT;
$a[] = $f;

?> 
