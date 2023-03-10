/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.35
 * 
 * This file is not intended to be easily readable and contains a number of 
 * coding conventions designed to improve portability and efficiency. Do not make
 * changes to this file unless you know what you are doing--modify the SWIG 
 * interface file instead. 
 * ----------------------------------------------------------------------------- */



#ifndef PHP_EXAMPLE_H
#define PHP_EXAMPLE_H

extern zend_module_entry example_module_entry;
#define phpext_example_ptr &example_module_entry

#ifdef PHP_WIN32
# define PHP_EXAMPLE_API __declspec(dllexport)
#else
# define PHP_EXAMPLE_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(example);
PHP_MSHUTDOWN_FUNCTION(example);
PHP_RINIT_FUNCTION(example);
PHP_RSHUTDOWN_FUNCTION(example);
PHP_MINFO_FUNCTION(example);

ZEND_NAMED_FUNCTION(_wrap_My_variable_set);
ZEND_NAMED_FUNCTION(_wrap_My_variable_get);
ZEND_NAMED_FUNCTION(_wrap_fact);
ZEND_NAMED_FUNCTION(_wrap_my_mod);
#endif /* PHP_EXAMPLE_H */
