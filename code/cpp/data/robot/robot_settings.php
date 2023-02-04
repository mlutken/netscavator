<?php

// --- User settings (User might want to change at least th two first) ---
$settingNumberOfRobots		= 1;
$settingServerUrl 			= "http://filesupload.airplaymusic.dk.localhost";
$settingCrawlerCmdParams 	= "--show-output=yes --delete-after-upload=yes";
$settingKillTimeOutSeconds 	= 30;
$settingRobotsBaseDir 		= "/home/ml/robots";
$settingMaxContinues 		= 10;
$settingWaitNewJobSeconds 	= 5;
$settingPrioQueue 			= 2;
$settingUpdateScriptsCmd	= "svn up";

// --- Automatic settings (probably no reason to change) ---
//$settingScriptsBaseDir		= "/home/ml/code/crawler";
$settingScriptsBaseDir		= "/home/ml/code/miners";

//$settingCrawlerBinDir		= "/home/ml/code/miners/webminer/bin";
//$settingCrawlerCmdName 		= "run_crawler";

$settingCrawlerBinDir		= "/home/ml/code/crawler/code/cpp/build_cbs/qtclin_debug_static/crawler";
$settingCrawlerCmdName 		= "crawler";

?>

