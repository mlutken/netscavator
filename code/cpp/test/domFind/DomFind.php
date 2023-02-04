#!/usr/bin/php5 
<?php
require_once "webminer.php";
require_once "DomFind_MainPage.php";


// ----------------------------
// --- Global configuration ---
// ----------------------------

function DomFind_urlSite()			{	return "http://localhost";		}
//function DomFind_urlStart()			{	return "file://home/ml/code/veriquin/code/cpp/test/domFind/domFind.html";	}
function DomFind_urlStart()			{	return "file:///c:/code/crawler/code/cpp/test/domFind/domFind.html";	}
// C:\code\crawler\code\cpp\test\domFind
function DomFind_setRunConfig()			
{
}

// ----------------------
// --- Work functions ---
// ----------------------

function DomFind_beginMining()			
{
	outputDirect 	( "URL_SITE", urlSite()	);
	

}

function DomFind_endMining()			
{	
	printf ( "CALL: DomFind_endMining\n" );	
}



initMining();
addMiner( "DomFind" );
runMiners();


?>

