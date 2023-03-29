<?php
require_once "string_utils.php";
require_once "parsing_utils.php";
require_once "CrawlerLog.php";

/** Create domsequences for a number of properties typically listed in a table.
\code
$handlerContext = 'ItemPage';
$preSeq = 'bem-table__title';
$postSeq = '*, bem-table__data-column';
$compareFun = 'icontains';
$postSteps = 1;
$outputNames = [
	'gears_count' => 'Number of gears:',
	'front_axle' => 'Front Axle Type:',
	'cable_routing' => 'Cable Routing:',
	'model_year' => 'Model Year:',
	'frame' => 'Frame:',
	'bike_weight' => 'Bike Weight:',
	'fork_material' => 'Fork Material:',
	'fork' => 'Fork:',
	'steerer' => 'Steerer:',
	'bottle_cage_mounts' => 'Bottle Cage Mounts:',
	'front_derailleur_mount' => 'Front Derailleur Mount:',
	'dropouts' => 'Dropouts:',
	'wheelset' => 'Wheelset:',
	'groupset_brand' => 'Groupset Manufacturer:',
	'brake_levers' => 'Brake Levers/Gear Shifters:',
	'gear_shifters' => 'Brake Levers/Gear Shifters:',
	'front_derailleur' => 'Front Derailleur:',
	'rear_derailleur' => 'Rear Derailleur:',
	'brake_type' => 'Brake Type:',
	'brakes' => 'Brakes:',
	'brake_callipers' => 'Brake Callipers:',
	'chainset_type' => 'Chainset type:',
	'chainset' => 'Chainset:',
	'chainring_size' => 'Chainring Size:',
	'chain' => 'Chain:',
	'bottom_bracket' => 'Bottom Bracket:',
	'cassette' => 'Cassette:',
	'cassette_range' => 'Cassette Range:',
	'handlebars' => 'Handlebars:',
	'bar_tape_grips' => 'Bar Tape/Grips:',
	'stem' => 'Stem:',
	'seat_post' => 'Seat Post:',
	'saddle' => 'Saddle:',
	'tyres' => 'Tyres:',
	'pedals' => 'Pedals:',
	'warranty' => 'Warranty:'
];
propertiesDomSequences($handlerContext, $preSeq, $postSeq, $compareFun, $postSteps, $outputNames);

\endcode
*/
function propertiesDomSequences($handlerContext, $preSeq, $postSeq, $compareFun, $postSteps, $outputNames, $seqVariantNum = 1)
{
	foreach($outputNames as $outputName => $searchFor) {
		$domSeqName = "${outputName}__${handlerContext}__FIND#${seqVariantNum}";
		$domSeq = '';
		if ($preSeq != '')
			$domSeq .= "${preSeq}, ";
		$domSeq .= $searchFor;
		if ($postSeq != '')
			$domSeq .= ", ${postSeq}";

		domSeqCreate($domSeqName, $domSeq, $compareFun, $postSteps);
	}
}

/** Call function if it exists. */
function callFunction($functionName)
{
    if (function_exists($functionName))
        return call_user_func($functionName);
}

function parseCommandLine( $sDefaultVals )
{
	global $argc, $argv;
	cmdDefaultValsSet( $sDefaultVals );
	cmdParseStart ();
	for ( $i = 1; $i < $argc; $i++ ) {
		$sArgument = $argv[$i];
		printf("parseCommandLine arg: '%s'\n", $sArgument );
		cmdParseArg	( $sArgument );
	}
    $logShow = cmdValStrGet("logShow");

	CrawlerLog::I()->loggingCategoriesSet($logShow);
}

function cmdScanModeGet()
{
    static $scanMode = NULL;
    if ( $scanMode == NULL ) {
        $scanMode = cmdValStrGet("scanMode");
        if ($scanMode == '') $scanMode = settingGet( "scanMode");
    }
    if ($scanMode != 'quick') $scanMode = 'full';
    return $scanMode;
}


function strValToBool( $val )
{
    $boolVal = false;
    if ( $val == "yes" || $val == "1" || $val == "true" ) {
        $boolVal = true;
    }

    return $boolVal;
}

function vectorAppend(&$vector, $append_vec_or_elem)
{
    if (!is_array($vector)) {
        $vector = [];
    }

    if (is_array($append_vec_or_elem)) {
        foreach($append_vec_or_elem as $element) {
            $vector[] = $element;
        }
    }
    else {
        $vector[] = $append_vec_or_elem;
    }
}


/** Get array value safe. Returns value from array of key given or
the default value if not found */
function getArraySafe( $sKeyName, $aArray, $valueIfNotFound='' )
{
	if ( !is_array ($aArray) )						return $valueIfNotFound;
	if ( array_key_exists( $sKeyName, $aArray ) )	return $aArray[$sKeyName];
	else 											return $valueIfNotFound;
}

function helper_TEMPLATE__ItemPage__mine($handlerName)
{
    domNewSearch();
    contextFallbackOutputLoad( urlCurrent() );
    contextBegin     ( 'item' );

    // Set start pos if item_data_start_pos__ItemPage__FIND sequence is defined
	domStartPosSet(domFindPos("item_data_start_pos__${handlerName}__FIND"));
	domStopPosSet(domFindPos("item_data_stop_pos__${handlerName}__FIND"));

    // -----------------------------------
    // --- Check for SKIPPING of title ---
    // -----------------------------------
    $bItemInvalid = false;
    $savePos = domPos();
    if ( domFindNext("SKIP__${handlerName}__FIND") ) {
        outputDirect('SKIP', '"_SKIP_TITLE_' );
        $bItemInvalid = true;
    }
    domPosSet($savePos);
    // --- Test for invalid item ---
    outputValueFindNext ( "item_invalid__${handlerName}__FIND", "item_invalid", "item_invalid__${handlerName}__MOD"  );
    outputDirect        ( 'item_url', urlCurrent(), "item_url__${handlerName}__MOD" );

    $items_mined = itemsMinedInc();

    clog(CrawlerLog::PROGRESS, "ItemPage[%d] urlQueueSize: %d Url: %s\n", $items_mined, urlQueueSize(), urlCurrent() );

    // --- Do rest of output ---
    outputValueFind ( "index_core__${handlerName}__FIND", "index_core", "index_core__${handlerName}__MOD");
    outputValueFind ( "type_core__${handlerName}__FIND", "type_core", "type_core__${handlerName}__MOD");
    outputValueFind ( "item_family__${handlerName}__FIND", "item_family", "item_family__${handlerName}__MOD");
    outputValueFind ( "item_type_text__${handlerName}__FIND", "item_type_text", "item_type_text__${handlerName}__MOD");
    outputValueFind ( "item_subtype_text__${handlerName}__FIND", "item_subtype_text", "item_subtype_text__${handlerName}__MOD");
    // Get all item data requested for product page
    outputValuesFindFromList ($handlerName, "TEMPLATE__${handlerName}__outputNames");

    $outputValuesFunction = outputValueGet( 'item_family' ) . "__${handlerName}__outputNames";
	if (function_exists($outputValuesFunction))
		outputValuesFindFromList ($handlerName, $outputValuesFunction);

    $outputValuesFunction = outputValueGet( 'type_core' ) . "__${handlerName}__outputNames";
	if (function_exists($outputValuesFunction))
		outputValuesFindFromList ($handlerName, $outputValuesFunction);

	outputDirect ( 'crawl_time', infoTimeMiningStartedUtc());
    outputDirect ( 'dbg_navigation_done', "'" . navNavigationDone() . "'" );
    outputDirect ( 'dbg_state', "TEMPLATE__${handlerName}__mine ({$items_mined}): " . navStateString() . "',  OptionIndex: " . navOptionIndexGet("searchStringSelect") );
    contextEnd();
    contextSavedOutputDelete( urlCurrent() );
}


function helper_TEMPLATE__DefaultHandler__navigate($handlerName)
{
    // If we have pages in the queue, then return false to allow
    // underlying C++ code to start emptying the queue by loading the productPages URLs.
    if ( urlQueueSize() > 0 ) {
        clog(CrawlerLog::DEBUG, "urlQueueSize: %d, {$handlerName}: nextState Get URL from queue.\n", urlQueueSize() );
        return false;
    }

    // Unless we are at navigators last state, we return to the DoSearchPage
    if ( !navNavigationDone() ) {
        navNextState();
        clog(CrawlerLog::PROGRESS, "{$handlerName}: Next State: '%s'\n", navStateString() );
        urlLoad( settingGet("DoSearchUrl") );
        return true;
    }
    else {
        clog(CrawlerLog::PROGRESS, "{$handlerName}: Navigation done!!! state: '%s',  '%d'\n", navStateString(), navNavigationDone() );
        return false;
    }
}

/**
Validate an email address.
Provide email address (raw input)
Returns true if the email address has the email
address format and the domain exists.
\see http://www.linuxjournal.com/article/9585
\see http://www.sslug.dk/emailarkiv/netvaerk/2006_09/msg00006.html */
function validEmail( $email )
{
	$isValid = true;
	$atIndex = strrpos($email, "@");
	if (is_bool($atIndex) && !$atIndex)
	{
		$isValid = false;
	}
	else
	{
		$domain = substr($email, $atIndex+1);
		$local = substr($email, 0, $atIndex);
		$localLen = strlen($local);
		$domainLen = strlen($domain);
		if ($localLen < 1 || $localLen > 64)
		{
			// local part length exceeded
			$isValid = false;
		}
		else if ($domainLen < 1 || $domainLen > 255)
		{
			// domain part length exceeded
			$isValid = false;
		}
		else if ($local[0] == '.' || $local[$localLen-1] == '.')
		{
			// local part starts or ends with '.'
			$isValid = false;
		}
		else if (preg_match('/\\.\\./', $local))
		{
			// local part has two consecutive dots
			$isValid = false;
		}
		else if (!preg_match('/^[A-Za-z0-9\\-\\.]+$/', $domain))
		{
			// character not valid in domain part
			$isValid = false;
		}
		else if (preg_match('/\\.\\./', $domain))
		{
			// domain part has two consecutive dots
			$isValid = false;
		}
		else if	(!preg_match('/^(\\\\.|[A-Za-z0-9!#%&`_=\\/$\'*+?^{}|~.-])+$/', str_replace("\\\\","",$local)))
		{
			// character not valid in local part unless
			// local part is quoted
			if (!preg_match('/^"(\\\\"|[^"])+"$/',
				str_replace("\\\\","",$local)))
			{
			$isValid = false;
			}
		}
		if ($isValid && !(checkdnsrr($domain,"MX") || checkdnsrr($domain,"A")))
		{
			// domain not found in DNS
			$isValid = false;
		}
	}
	return $isValid;
}


function getCustomHtmlText( $aTagsToPreserve = Array("BR") )
{
	$aTagsToIgnore = Array("B", "I", "STRONG" );
	// Skip any initial <br> (breaks)
	////print_r ( $aTagsToPreserve );
	for ( $i = 0; $i < 10; $i++ ) {
		$bBreak = true;
		if ( nodeValue(trimEnds) ==	"BR" || nodeValue(trimEnds) == '' )	$bBreak = false;
		if ( $bBreak )	break;
		domStep	( 1	)	;
	}

	// Read description including <br> (breaks)
	$s = "";
	for ( $i = 0; $i < 100; $i++ ) {
		$bBreak = true;
		////printf("nodeValue(): '" . nodeValue() . "'\n");
		if ( nodeType()  ==	TEXT_NODE 	) {
			//printf("XXXXXXXXXXXXXXXx\n");
			$bBreak = false;
			$s .= nodeValue();
		}
		if ( array_search ( nodeValue(), $aTagsToPreserve ) !== false ) {
			$bBreak = false;
			if ( array_search ( nodeValue(), $aTagsToIgnore ) === false ) {
				$s .= "<". nodeValue() . ">";
			}
		}
		//printf("bBreak: '$bBreak'\n");

		if ( $bBreak )	break;
		domStep	( 1	)	;
	}
	return $s;
}


// ------------------------------
// --- Debug Helper Functions ---
// ------------------------------

function dbgPrintNavigatorStates($iMaxStatesToPrint)
{
    printf("dbgPrintNavigatorStates()\n");
    navStart();
    $i = 0;
    while ( ! navNavigationDone() ) {
        printf( "State: %d, %s, '%d'\n", $i, navStateString(), navNavigationDone() );
        navNextState();

        if ( $i++ > $iMaxStatesToPrint ) {
            printf("INFO: Reached maximum number of states to print!\n");
            break;
        }
    }
    printf( "End  : %d, %s, '%d'\n", $i, navStateString(), navNavigationDone() );

    navStart(); // Reset navigator to start state, just in case it's going to be used in the real script afte this
}


// *********************
// *** PID functions ***
// *********************


// function getpidinfo($pid, $ps_opt="aux")
// {
// 	$ps=shell_exec("ps ".$ps_opt."p ".$pid);
// 	printf("ps:" . $ps );
// 	$ps=explode("\n", $ps);
//
// 	if(count($ps)<2){
// 		trigger_error("PID ".$pid." doesn't exists", E_USER_WARNING);
// 		return false;
// 	}
//
// 	foreach($ps as $key=>$val){
// 		$ps[$key]=explode(" ", ereg_replace(" +", " ", trim($ps[$key])));
// 	}
//
// 	foreach($ps[0] as $key=>$val){
// 		$pidinfo[$val] = $ps[1][$key];
// 		unset($ps[1][$key]);
// 	}
//
// 	if(is_array($ps[1])){
// 		$pidinfo[$val].=" ".implode(" ", $ps[1]);
// 	}
// 	return $pidinfo;
// }

function kill_process( $pid, $force = 9 )
{
	if ( PHP_OS == "Windows" ) {
		print "posix_kill  ( $pid, $force ) NOT Implemented\n";
	}
	else if ( PHP_OS == "Linux" ) {
		return posix_kill  ( $pid, $force );
	}
}

// **********************
// *** Time functions ***
// **********************

/** Read a timestamp from a file. Assumes file are open and readable.
\return The unix-style time as an integer.
\sa http://dk.php.net/manual/en/function.strtotime.php */
function readTimeStamp( $hFile ) ///< Handle to open readable file
{
	rewind($hFile);						// Read from beginning
	$sFormattedRead = fread( $hFile, 100 );
	$a = explode ( "\n", $sFormattedRead );
	$a[0] = strtotime($a[0]);
	return $a;
}

/** Write a timestamp from a file. Assumes file are open and readable.
The timestamp is written in ISO 8601 format.
\return The timestamp actually written ( the a unix-style time as an integer).
\sa http://dk.php.net/manual/en/function.date.php
\sa http://dk.php.net/manual/en/function.time.php */
function writeTimeStamp( $hFile ) ///< Handle to open writable file
{
	rewind($hFile);								// Write from beginning
	$pid = getmypid();							// PID
	$iTimeStampWrite = time();					// Current time measured in the number of seconds since the Unix Epoch (January 1 1970 00:00:00 GMT).
	$sDateWrite = date("c", $iTimeStampWrite );	// "c" formats as ISO 8601 date, see http://dk.php.net/manual/en/function.date.php
	fwrite( $hFile, $sDateWrite );
	fwrite( $hFile, "\n$pid" );
	return $iTimeStampWrite;
}


function okToRunProgram ( $lockFilePath, $iMaxRunTimeInSeconds )
{
	$bOkToRun = true;
	if ( file_exists($lockFilePath) ) {
		$bOkToRun = false;
		$hFile = fopen( $lockFilePath, "r");
		$a = readTimeStamp( $hFile );
		$iTimeStampRead = $a[0];
		$pid = $a[1];
		printf("iTimeStampRead: " . date("c", $iTimeStampRead ) . "\n");
		if ( time() - $iTimeStampRead > $iMaxRunTimeInSeconds )	{
			printf ("OK to run since the old instance ($pid) is hanging or exited without cleaning semaphore\n");
			kill_process($pid);
			sleep(5);
			// Too long time expired since the (apparently) running instance
			// wrote to the timestamp file, that we assume it's hanging or has exited
			// without removing the semaphore file.
			// We delete the file, kill the process and allow this instance to start.
			$bOkToRun = true;
			fclose ( $hFile);
			unlink( $lockFilePath );	// Delete the file on disk.
			if ( file_exists($lockFilePath) ) {
				// This should not happen unless this dir has gotten wrong owner
				logErr("Could not delete semaphore lock file: '$lockFilePath'", __file__);
				print( "Error: Could not delete semaphore lock file: '$lockFilePath'\n");
			}
			$hFile = fopen( "$lockFilePath.KILLED", "w");	// We want to write time process was killed to a file
			writeTimeStamp($hFile);
			fclose($hFile);
			##exit(1);
		}
		else {
			fclose ( $hFile);
		}
	}
	if ( $bOkToRun ) {
		$hFile = fopen( $lockFilePath, "w+");	// We want to write AND read in the file, thus the '+'-sign
		writeTimeStamp($hFile);
		fclose ( $hFile);
	}
	return $bOkToRun;
}

function releaseLockFile( $lockFilePath )
{
	unlink ( $lockFilePath );
}

// *****************************
// *** Compression functions ***
// *****************************


/**
\code
uncompress("test.gz","test.php");
\endcode */
function uncompress($srcName, $dstName) {
	$iBlockSize = 8192;
	$fp = fopen($dstName, "w");
	$zp = gzopen($srcName, "r");
	$contents = '';
	while (!gzeof($zp)) {
		$contents = gzread($zp, $iBlockSize);
		fwrite  ( $fp  , $contents );
	}
	fclose($fp);
	gzclose($zp);
}


/// compress("test.php","test.gz");
function compress($srcName, $dstName)
{
	$iBlockSize = 8192;
	$fp = fopen($srcName, "r");
	$zp = gzopen($dstName, "w9");
	$contents = '';
	while (!feof($fp)) {
		$contents = fread($fp, $iBlockSize);
		gzwrite  ( $zp  , $contents );
	}
	fclose($fp);
	gzclose($zp);
}

/** Compress file adding .gz to it's extension. */
function compressFile($srcName)
{
    $dstName = $srcName . '.gz';
    printf("Compressing '{$srcName}' => '{$dstName}'\n");
    return gzCompressFile( $srcName, $dstName);
}


// **************************************
// *** Upload XML data file functions ***
// **************************************

/*
function compressAndPostUploadFile( $sFileName, $bDeleteFile )
{
    $pathParts = pathinfo($sFileName);
    $sExtension = $pathParts['extension'];
    $sFileNameWE = $pathParts['filename'];
    $sFileNameUpload = $sFileNameWE . ".xml.gz";
    if ( $sExtension != "gz" ){
        printf("Compressing '{$sFileName}' => '{$sFileNameUpload}'\n");
        gzCompressFile( $sFileName, $sFileNameUpload );
    }
    $urlUpload = configUrlUploadDataGet();
    printf("sFileNameUpload: $sFileNameUpload\n");
    printf("Url upload: %s\n", $urlUpload );

    curlPostUploadFileSimple( $urlUpload, "uploadedfile", $sFileNameUpload );
    if ( $bDeleteFile ) {
        unlink($sFileName);
        if ( $sExtension != "gz" ){
            unlink($sFileNameUpload);
        }
    }
}
*/

function uploadFileHttpPost()
{
    $sFile = currentDataFile();
    $ok = compressFile($sFile);
    if (!$ok) {
        printf("ERROR: Could not compress file: '$sFile'\n");
        return;
    }

    $sCompressedFile = $sFile . '.gz';
    $deleteFile = strValToBool(configValueGet("delete-after-upload"));

    printf("INFO: uploadFileHttpPost file: %s,  Delete after upload: %s\n", $sFile, $deleteFile);
    $uploadUrl = configUrlUploadDataGet();

    $ok = curlPostUploadFileSimple( $uploadUrl, "uploadedfile", $sCompressedFile );
    if (!$ok) {
        printf("ERROR: Could not (POST) upload file: '$sCompressedFile', Upload URL: '$uploadUrl'\n");
        return;
    }

    if ($deleteFile) {
        if (file_exists($sFile))
            unlink($sFile);
        if (file_exists($sCompressedFile))
            unlink($sCompressedFile);
    }
}


/** scp (Secure CoPy) file to a server.
\param $srcFile Path to file to copy.
\param $user User name of user on destination server.
\param $server Server name (eg. myserver.com) to copy to.
\param $remoteDir Full path to destination directory on remote server.
\param $privateKey Path to ssh private key of \a $user .;
*/
function scpCopyFile($srcFile, $user, $server, $remoteDir, $privateKey)
{
    $cmd = "scp -i ${privateKey} ${srcFile} ${user}@${server}:${remoteDir}";
    $output = [];
    $exit_code = 0;
    exec ( $cmd, $output, $exit_code );
    $ok = (int)$exit_code == 0;

    if (!$ok) {
        printf("ERROR: An error occured during scp copy/upload\n", $srcFile);
        printf("ERROR: Command executed:%s\n", $cmd);
        printf("ERROR: Output from command:%s\n", join("\n", $output));
    }
    return $ok;
}

function uploadFileScp()
{
    $sFile = currentDataFile();
    $ok = compressFile($sFile);
    if (!$ok) {
        printf("ERROR: Could not compress file: '$sFile'\n");
        return;
    }

    $sCompressedFile = $sFile . '.gz';
    $deleteFile = strValToBool(configValueGet("delete-after-upload"));

    printf("uploadFileScp file: %s,  Delete after upload: %s\n", $sFile, $deleteFile);

    $user = settingGet('upload_user');
    $server = settingGet('upload_server');
    $remote_upload_dir = settingGet('remote_upload_dir');
    $remoteDir = settingGet('upload_remote_base_dir') . '/normal_upload';
    $privateKey = settingGet('upload_private_key');
    
    $ok = false;
    if ($remote_upload_dir != '') {
        $ok = scpCopyFile($sCompressedFile, $user, $server, $remote_upload_dir, $privateKey);
        if (!$ok) {
            printf("ERROR: Could not (scp) copy file: '$sCompressedFile' to '$remote_upload_dir'\n");
            return;
        }
    }
    
    if ($remoteDir != '') {
        $ok = scpCopyFile($sCompressedFile, $user, $server, $remoteDir, $privateKey);
        if (!$ok) {
            printf("ERROR: Could not (scp) copy file: '$sCompressedFile' to '$remoteDir'\n");
        }
    }

    if ($deleteFile) {
        if (file_exists($sFile))
            unlink($sFile);
        if (file_exists($sCompressedFile))
            unlink($sCompressedFile);
    }
}


function dbgPrintLocaleAndSiteSettings()
{
    echo "urlSite: " . settingGet('urlSite');
    echo "DoSearchUrl: " . settingGet('DoSearchUrl');
    echo "outputName: " . settingGet('outputName');
    echo "shop_id: " . settingGet('shop_id');

    echo "country_code: " . settingGet('country_code');
    echo "language_code: " . settingGet('language_code');
    echo "currency_code: " . settingGet('currency_code');
    echo "decimal_point: " . settingGet('decimal_point');
    echo "thousands_sep: " . settingGet('thousands_sep');
}

/** Upload file using scp. You must set these config values:
: ''


./make_release_static/crawler/crawler /home/ml/code/miners/scripts/cycling/dk/cykelgear.dk.php  --max-pageloads 8  --upload-result yes --upload-handler uploadFileScp
*/


// function uploadFileOLD( $sFileName )
// {
	// $pathParts = pathinfo($sFileName);
	// $sExtension = $pathParts['extension'];
	// $sFileNameWE = $pathParts['filename'];
	// $sFileNameUpload = $sFileNameWE . ".gz";
	// if ( $sExtension != "gz" ){
		// compress( $sFileName, $sFileNameUpload );
	// }
	// printf("sFileNameUpload: $sFileNameUpload\n");
	// printf("Url upload: %s\n", configUrlUploadDataGet() );

	// $ch = curl_init( configUrlUploadDataGet() );
	// curl_setopt($ch, CURLOPT_POSTFIELDS, array('uploadedfile'=>"@$sFileNameUpload"));
	// curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
	// $postResult = curl_exec($ch);
	// curl_close($ch);
	// print "$postResult";
	// if ( $sExtension != "gz" ){
 		// unlink($sFileNameUpload);
	// }
// }
