<?php
// To set include_path for use with all aphp files include this in you top level php file like this:
// require_once ( __DIR__ . '/../php_fix_include_path.php' ); 
// 
// or whatever the relative path to this file might be.
// Alternatively you can make sure to add the directory this file is located in to you include_path 
// in php.ini

// --- DEBUG: Set error reporting in browser ---
error_reporting(E_ALL);
ini_set('display_errors', 'on');

// --- Timezone UTC ---
date_default_timezone_set('UTC');

set_include_path( __DIR__ . PATH_SEPARATOR . get_include_path());

$g_phpRootDir = __DIR__;

function phpRootDir()
{
    global $g_phpRootDir;
    return $g_phpRootDir;
}

echo "PHP_INCLUDE_PATH: " . get_include_path() . "\n";