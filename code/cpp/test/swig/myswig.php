<?php

/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.35
 * 
 * This file is not intended to be easily readable and contains a number of 
 * coding conventions designed to improve portability and efficiency. Do not make
 * changes to this file unless you know what you are doing--modify the SWIG 
 * interface file instead. 
 * ----------------------------------------------------------------------------- */

// Try to load our extension if it's not already loaded.
if (!extension_loaded("myswig")) {
  if (strtolower(substr(PHP_OS, 0, 3)) === 'win') {
    if (!dl('php_myswig.dll')) return;
  } else {
    // PHP_SHLIB_SUFFIX is available as of PHP 4.3.0, for older PHP assume 'so'.
    // It gives 'dylib' on MacOS X which is for libraries, modules are 'so'.
    if (PHP_SHLIB_SUFFIX === 'PHP_SHLIB_SUFFIX' || PHP_SHLIB_SUFFIX === 'dylib') {
      if (!dl('myswig.so')) return;
    } else {
      if (!dl('myswig.'.PHP_SHLIB_SUFFIX)) return;
    }
  }
}



abstract class myswig {
	static function Swig_variable_set($Swig_variable) {
		Swig_variable_set($Swig_variable);
	}

	static function Swig_variable_get() {
		return Swig_variable_get();
	}

	static function Swig_fact($arg1) {
		return Swig_fact($arg1);
	}

	static function Swig_div($n,$m) {
		return Swig_div($n,$m);
	}
}

/* PHP Proxy Classes */

?>
