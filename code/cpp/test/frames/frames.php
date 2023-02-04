#!/usr/bin/php5 
<?php
require_once "webminer.php";
require_once "frames_MainPage.php";


// ----------------------------
// --- Global configuration ---
// ----------------------------

function frames_urlSite()			{	return "http://localhost";		}
function frames_urlStart()			{	return "file://home/ml/code/veriquin/code/cpp/test/frames/frames.html";	}

function frames_setRunConfig()			
{
}

// ----------------------
// --- Work functions ---
// ----------------------

function frames_beginMining()			
{
	outputDirect 	( "URL_SITE", urlSite()	);
	

}

function frames_endMining()			
{	
	printf ( "CALL: frames_endMining\n" );	
}



initMining();
addMiner( "frames" );
runMiners();


?>

