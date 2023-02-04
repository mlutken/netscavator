<?php
require_once ( __DIR__ . '/../php_fix_include_path.php' ); 

require_once ('unit_test/MinerRobotUT.php');

// RUN CMD: php unit_test.php

print "Running unit tests ... on:" . hostname() . "\n";
$ut = new MinerRobotUT();

$ut->run();
