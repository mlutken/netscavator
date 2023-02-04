#!/usr/bin/php
<?php

$a = array();

require_once('MiscFunctions.php');
require_once('BrowserFunctions.php');
require_once('NavigationFunctions.php');
require_once('StringCompareFunctions.php');
require_once('StringCompareOperators.php');
require_once('StringManipulationFunctions.php');
require_once('StringManipulationOperators.php');
require_once('UrlFunctions.php');
require_once('DomFunctions.php');
require_once('NodeActions.php');
require_once('ValueFunctions.php');
require_once('ParseFunctions.php');
require_once('UrlQueueFunctions.php');
require_once('ContextFunctions.php');
require_once('OutputFunctions.php');
require_once('JavascriptFunctions.php');
require_once('SettingsFunctions.php');
require_once('ConfigFunctions.php');
require_once('DebugFunctions.php');
require_once('AllFunctions.php');


require_once('ReferenceManualGeneratorPlainHtml.php');

printf("Reference Manual Generation\n");


$rg = new ReferenceManualGeneratorPlainHtml( $a, "./html/" );
//$rg->dbgPrint();
$rg->writeFiles();
//print_r ( $a );

//$rg->getHtml( $a[5] );
//$rg->dbgPrintJson();

// -------------
// --- GROUP ---
// -------------

