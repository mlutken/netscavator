#!/usr/bin/php5 
<?php
#include("example.php");
#include("myswig.php");
#include("myclass.php");
require "myclass.php";
#dl("example.so");

class SomeClass {
    static function say_hello()
    {
        echo "Hello ccccccccc!\n";
    }
}

//$classname = "SomeClass";
$classname = new SomeClass();


function test_function()
{
	echo "We are in the test function!\n";
	return 'hello';
}

#$vec = new Vector();
$v = new Vector();
$v->x = 2;
$v->y = 3;
$v->z = 4;
echo $v->magnitude2(), "\n";
callCallback( "test_function" );

//callMemberCallback( $classname, "say_hello" );
//callMemberCallback( $classname, "test_function" );

//my_call_user_method ( array($classname, 'say_hello') );
//call_user_method ( array($classname, 'say_hello') );
//test_function();
#echo my_mod(25,7);
#echo Swig_fact(4), "\n";
#echo Swig_div(25,7);

?>

