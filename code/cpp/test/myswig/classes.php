#!/usr/bin/php5 
<?php
require "myphp_module.php";


printf ( "Hello php5\n");

$v = new Vector(2,2,1);
echo $v->len2(), "\n";

// $pV = getVecPtr(4,5,6);
// print $pV->len2();

// $v = getVec(4,5,6);
// print $v->len2();

?>

