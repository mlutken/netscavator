#!/usr/bin/php5 
<?php
require_once "webminer.php";
require_once "minerplayground_MainPage.php";


// ----------------------------
// --- Global configuration ---
// ----------------------------

function MinerPlayGround_urlSite()			{	return "http://localhost";		}
function MinerPlayGround_urlStart()			{	return "file:///home/ml/code/crawler/code/cpp/test/minerplayground/index_minerplayground.html";	}
//function MinerPlayGround_urlStart()			{	return "file:///c:/code/crawler/code/cpp/test/minerplayground/index_minerplayground.html";	}
// C:\code\crawler\code\cpp\test\domFind
function MinerPlayGround_setRunConfig()			
{
}

// ----------------------
// --- Work functions ---
// ----------------------

function MinerPlayGround_beginMining()			
{
	outputDirect 	( "URL_SITE", urlSite()	);
	

}

function MinerPlayGround_endMining()			
{	
	printf ( "CALL: MinerPlayGround_endMining\n" );	
}



initMining();
addMiner( "MinerPlayGround" );
runMiners();


?>

