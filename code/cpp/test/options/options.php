#!/usr/bin/php5 
<?php
require_once "webminer.php";
require_once "options_MainPage.php";


// ----------------------------
// --- Global configuration ---
// ----------------------------

function options_urlSite()			{	return "http://localhost";		}
function options_urlStart()			{	return "file://home/ml/code/veriquin/code/cpp/test/options/options.html";	}

function options_setRunConfig()			
{
}

// ----------------------
// --- Work functions ---
// ----------------------

function options_beginMining()			
{
	outputDirect 	( "URL_SITE", urlSite()	);
	

}

function options_endMining()			
{	
	printf ( "CALL: options_endMining\n" );	
}



initMining();
addMiner( "options" );
runMiners();


?>

