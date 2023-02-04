#!/usr/bin/php5 
<?php
require "php_crawl.php";

class SomeClass {
	static function say_hello()
	{
		echo "Hello ccccccccc!\n";
	}
	
	function 	print1() {
		echo "SomeClass::print1\n";
	}
};

class DerivedClass extends SomeClass {
	function 	print2() {
		echo "DerivedClass::print2\n";
	}
}

class DerivedVector extends Vector {
	function 	print3() {
		echo "DerivedVector::print3 len(): ";
		echo $this->len2(), "\n";
	}
	
	function len2() {
		return 55;
	}
}



//$classname = "SomeClass";
$classname = new SomeClass();


function test_function()
{
	echo "We are in the test function!\n";
	return 'hello';
}

function test_callback()
{
	echo "test_callback called!\n";
	return 'hello2';
}

function test_callScriptFunction()
{
	echo "test_callScriptFunction!\n";
	return 'hello3';
}

$v = new Vector(2,2,1);
echo $v->len2(), "\n";
echo $v->len(), "\n";
$v->x = 2;
$v->y = 3;
$v->z = 4;
echo $v->len2(), "\n";
echo $v->len(), "\n";
echo $v->magnitude(), "\n";
callCallback( "test_function" );

$c = new DerivedClass();
$c->print1();
$c->print2();

$vD = new DerivedVector(2,2,1);
#echo $vD->len3(), "\n";
echo $vD->len2(), "\n";
echo $vD->len(), "\n";
$vD->print3();
scripInlineTest();
printf ( "Test std::string return value  foo(): %s\n" , foo() );
bar( "Test std::string input parameter" );
#list_functions();
#list_classes();
runScript( "HomeDk" );

//callMemberCallback( $classname, "say_hello" );
//callMemberCallback( $classname, "test_function" );

//my_call_user_method ( array($classname, 'say_hello') );
//call_user_method ( array($classname, 'say_hello') );
//test_function();
#echo my_mod(25,7);
#echo Swig_fact(4), "\n";
#echo Swig_div(25,7);

?>

