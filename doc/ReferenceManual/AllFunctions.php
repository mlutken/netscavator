<?php

$f = array();
$f["name"] =
// **************************
       "All functions";
// **************************

$f["type"]      = "overview";
$f["desc"]      = <<<TEXT
List of all functions in alphabetical order. See also functions by group all-function-groups!
TEXT;
$f["functions"]  = array();
$f["seealso"]  = "all-function-groups";
$a[] = $f;


$f = array();
$f["name"] =
// **************************
       "All function groups";
// **************************

$f["type"]      = "overview";
$f["desc"]      = <<<TEXT
List of all functions by group. See also all functions in alphabetical order all-functions.
TEXT;
$f["functions"]  = array();
$f["seealso"]  = "all-functions";
$a[] = $f;



?>
