#!/usr/bin/php5 
<?php
require_once "webminer.php";
require_once "Events_MainPage.php";


// ----------------------------
// --- Global configuration ---
// ----------------------------

function Events_urlSite()			{	return "http://localhost";		}
function Events_urlStart()			{	return "/home/ml/code/crawler/code/cpp/test/browserevents/events.html";	}
//function Events_urlStart()			{	return "file:///c:/code/crawler/code/cpp/test/browserevents/events.html";	}

function Events_setRunConfig()			
{
}

// ----------------------
// --- Work functions ---
// ----------------------

function Events_beginMining()			
{
    browserSetSize (800, 600);
	outputDirect 	( "URL_SITE", urlSite()	);
	

}

function Events_endMining()			
{	
	printf ( "CALL: Events_endMining\n" );	
}



initMining();
addMiner( "Events" );
runMiners();


?>

