<?php
require_once "miner_robot_settings.php";
require_once "MinerRobot.php";

/*
Test run crawler: 
/home/ml/code/crawler/code/cpp/build_cbs/make_release_static/crawler/crawler /home/ml/code/miners/smart.com.php --job-name wallmart.com --task-id myproject_somesite.com_7
/home/ml/code/crawler/code/cpp/build_cbs/make_release_static/crawler/crawler --continue
 */


print "Godda'\n";

if ( $settingUpdateScriptsCmd != "" ) {
	shellExecute ( $settingUpdateScriptsCmd, $settingScriptsBaseDir );
}

for ( $robotNameID = 1; $robotNameID <= $settingNumberOfRobots; $robotNameID++ ) {
	
	//TODO: Not done yet! $robots_base_dir, $robot_name, $kill_timeout_in_seconds, $max_continues, $crawler_exe_path, $server_url
	$r = new MinerRobot( $settingScriptsBaseDir, $settingRobotsBaseDir, $settingCrawlerBinDir, $settingServerUrl, $robotNameID, $settingPrioQueue );
	$r->run();
	sleep(1);
}





?>

