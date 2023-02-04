#!/usr/bin/php5 
<?php
require "myphp_module.php";
dl("php_zip.dll");
#dl("myphp_module.dll");


printf ( "Hello php5\n");

$v = new Vector(2,2,1);
echo $v->len2(), "\n";

list_functions();
startWx();

?>

