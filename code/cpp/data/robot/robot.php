<?php
require_once "robot_settings.php";
require_once "CrawlerRobot.php";
require_once "robot_system_utils.php";


if ( $settingUpdateScriptsCmd != "" ) {
	shellExecute ( $settingUpdateScriptsCmd, $settingScriptsBaseDir );
}

for ( $robotNameID = 1; $robotNameID <= $settingNumberOfRobots; $robotNameID++ ) {
	$r = new CrawlerRobot( $settingScriptsBaseDir, $settingRobotsBaseDir, $settingCrawlerBinDir, $settingServerUrl, $robotNameID, $settingPrioQueue );
	$r->run();
	sleep(1);
}





?>

