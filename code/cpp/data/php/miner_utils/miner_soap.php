<?php

// set_time_limit(6000000);

// ------------------------
// --- Helper functions ---
// ------------------------


// function listDir( $sDir='.', $bRecursive = true, $sNameContains ='' ) {
	
	// $iLen = strlen($sDir);
	// if ( $iLen > 0 && $sDir[$iLen -1] == '/' )	$sDir = substr( $sDir, 0, -1);
	
	// $aFiles = array();
	// if ( is_dir($sDir) ) {
		// $fh = opendir($sDir);
		// while ( ($file = readdir($fh) ) !== false) {
			// # loop through the files, skipping . and .., and recursing if necessary
			// if (strcmp($file, '.')==0 || strcmp($file, '..')==0) continue;
			// $sFilePath = $sDir . '/' . $file;
			// if ( $bRecursive && is_dir($sFilePath) ) {
				// $aFiles = array_merge( $aFiles, listDir($sFilePath) );
			// }
			// else {
				// if ( $sNameContains == '' )									array_push( $aFiles, $sFilePath );
				// else if ( strpos( $sFilePath, $sNameContains ) !== false ) 	array_push( $aFiles, $sFilePath );
			// }
		// }
		// closedir($fh);
	// } 
	// else {
		// # false if the function was called with an invalid non-directory argument
		// $aFiles = false;
	// }
	// return $aFiles;
// }


// function getNextFileNumber( $sPrefix )
// {
// 	$iNum = PHP_INT_MAX;
// 	$aFiles = listDir( '.', false, $sPrefix ) ;
// 	foreach ( $aFiles as $sFile ) {
// 		$aParts = explode ( '_', $sFile );
// 		if ( $aParts[1] < $iNum )	$iNum = $aParts[1];
// 	}
// 	return $iNum != PHP_INT_MAX ? $iNum : 0;
// }


/** 
Get name of next file ready for uploading. The 'raw' splitted files 
are named like this: upload_#_.xml, where '#' denotes an integer 
number. This function return the lowest number of the files available or 
"" (empty string) if no files are present for sending. */
// function nextUploadName( $bFullName = true )
// {
// 	$iNum = getNextFileNumber('upload_');
// 	$sPath = $bFullName ? './' : '';
// 	return $iNum != 0 ? "{$sPath}upload_{$iNum}_.xml" : "";
// }


/** Splits one large XML file with localities into smaller parts(files) named 
'upload_#_.xml, where '#' denotes part numer. */
// function splitXmlFileForProcessing( $sFileToSplit, $iLocalitiesPerFile = 10 )
// {
// 	$bInLocality 		= false;
// 	$iLocalitiesCounter	= 0;
// 	$iFilePartsCounter	= 1;
// 	$sFilePart 			= "upload_{$iFilePartsCounter}_.xml";
// 	$hRead 				= fopen( $sFileToSplit, 'r');
// 	$bInLocality 		= false;
// 	
// 	$hWrite = fopen( $sFilePart, "w" );
// 	fwrite( $hWrite, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<ROOT>\n" );
// 	
// 	while ( !feof($hRead) ) {
// 		$sLine = fgets( $hRead );	// Read next line from the file
// 		
// 		if ( strpos($sLine, '<LOCALITY>' ) !== false ) {
// 			$bInLocality = true;
// 			fwrite( $hWrite, "<LOCALITY>\n" );
// 			continue;
// 		}
// 		if ( strpos($sLine, '</LOCALITY>' ) !== false ) {
//  			fwrite ( $hWrite, "</LOCALITY>\n" );
// 			
// 			$bInLocality = false;
// 			$iLocalitiesCounter++;
// 			if ( $iLocalitiesCounter % $iLocalitiesPerFile == 0 ) {
// 				fwrite ( $hWrite, "</ROOT>\n" );
// 				fclose( $hWrite );
// 				
// 				$iFilePartsCounter++;
// 				$sFilePart = "upload_{$iFilePartsCounter}_.xml";
// 				$hWrite = fopen( $sFilePart, "w" );
// 				fwrite( $hWrite, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<ROOT>\n" );
// 			}
// 			continue;
// 		}
// 		else if ( $bInLocality ) {
// 			fwrite( $hWrite, $sLine );
// 		}
// 	}
// 	fwrite ( $hWrite, "</ROOT>\n" );
// 	fclose( $hWrite );
// }

// function getNextXMLFile()
// {
// 	global $argv;
// 	global $argc;
// 	
// 	$sNextProcessingPart = nextProcessingName(true)	;
// 	if ( $sNextProcessingPart != "" )	return $sNextProcessingPart;
// 	
// 	$sNextForParseFile = nextReadyForParseName(true);
// 	if ( $sNextForParseFile == "" )	return "";				// No more files to parse at this moment
// 	
// 	$iLocationsPerPart = 500;
// 	if ( $argc > 1 )	$iLocationsPerPart = $argv[1]; 
// 	printf ("Splitting part size: %d\n", $iLocationsPerPart );
// 	// Split the next file into process parts, delete the 
// 	// original uploaded file and return first part of the splitted file.
// 	splitXmlFileForProcessing ( $sNextForParseFile, $iLocationsPerPart );	
// 	unlink ( $sNextForParseFile );			
// 	return nextProcessingName(true)	;
// }

/** Deletes any 'old' upload files from a previous run. */
// function deleteUploadFiles()
// {
// 	$aFiles = listDir( '.', false, 'upload_' );
// 	foreach ( $aFiles as $sFile ) {
// 		unlink ($sFile);
// 	} 
// }

/**/
/// Sends one file to the webservice. 
// function uploadOneFile( $sFile )
// {
// 	$client = new soapclient(WEBSERVICEURL);
// 
// 	$sXmlData	= file_get_contents	( $sFile );
// 	$result 	= $client->call		( 'DataLoading', array($sXmlData) );
// 	printf ( "\n\nresult: '%s'\n\n", $result);
// 	if ( $result == "" ) {
// 		printf( "\nERROR sending XML file\n" );
// 	}
// 	unlink ($sFile );
// }




// function WC_sendXmlData()			
// {
// 	printf("WC_sendXmlData\n");
// 	$sFile = currentDataFile();
// 	printf("File: %s\n", $sFile);
//  	uploadFile( $sFile );
// }

// curl -F uploadedfile=@22M.avi http://jordenergiftig.dk.localhost/webservice/upload.php


////WC_sendXmlData();	

