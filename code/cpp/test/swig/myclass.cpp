#include <iostream>

#include <zend.h>
#include <zend_API.h>
#include <php.h>

#include "myclass.h"

Vector::Vector()
{
	std::cout << "Vector CONSTRUCTOR" << std::endl;
}

Vector::~Vector()
{
	std::cout << "Vector DESTRUCTOR" << std::endl;
}

double
Vector::magnitude2() 
{ 
	return x*x + y*y + z*z; 
}

//TSRMSLS_FETCH();

void callCallback( const char* szCallBack )
{
	std::cout << "callCallback( " << szCallBack << " )" << std::endl;

	zval *function_name;
	zval *retval;

	
    ALLOC_INIT_ZVAL(function_name);
//	ZVAL_STRING(function_name, (char*)"test_function", 1 );
	ZVAL_STRING(function_name, (char*)szCallBack, 1 );
	
	
	// int call_user_function_ex( HashTable*, zval**, zval*, zval**, zend_uint, zval***, int, HashTable* );
 	if ( call_user_function_ex( CG(function_table), NULL, function_name, &retval, 0, NULL, 0, NULL ) != SUCCESS )
 	{
 		zend_error(E_ERROR, "Function call from C++ to php callback '%s' failed", szCallBack );
 	}
	
	zend_printf("We have '%s' as val\n", Z_STRVAL_P(function_name) );
	zend_printf("retval '%s' \n", Z_STRVAL_P(retval) );
//	zend_printf("We have '%s' as val\n", function_name->value.str.val );
	
//	zval* return_value = *retval;
//	zval_copy_ctor(return_value);
	zval_ptr_dtor(&retval);
    zval_ptr_dtor(&function_name);	
}


void callMemberCallback( void* pClassObj,  const char* szCallBack )
{
	std::cout << "callMemberCallback( " << pClassObj << " )" << std::endl;
	std::cout << "callMemberCallback( " << szCallBack << " )" << std::endl;

	zval *function_name;
	zval *retval;

	
    ALLOC_INIT_ZVAL(function_name);
//	ZVAL_STRING(function_name, (char*)"test_function", 1 );
	ZVAL_STRING(function_name, (char*)szCallBack, 1 );
	
	
	// int call_user_function_ex( HashTable*, zval**, zval*, zval**, zend_uint, zval***, int, HashTable* );
 	if ( call_user_function_ex( CG(function_table), NULL, function_name, &retval, 0, NULL, 0, NULL ) != SUCCESS )
 	{
 		zend_error(E_ERROR, "Function call from C++ to php callback '%s' failed", szCallBack );
 	}
	
	zend_printf("We have '%s' as val\n", Z_STRVAL_P(function_name) );
	zend_printf("retval '%s' \n", Z_STRVAL_P(retval) );
//	zend_printf("We have '%s' as val\n", function_name->value.str.val );
	
//	zval* return_value = *retval;
//	zval_copy_ctor(return_value);
	zval_ptr_dtor(&retval);
    zval_ptr_dtor(&function_name);	
}



// static
// ZEND_BEGIN_ARG_INFO_EX(arginfo_my_call_user_method, 0, 0, 2)
// 	ZEND_ARG_INFO(0, method_name)
// 	ZEND_ARG_INFO(1, object)
// 	ZEND_ARG_INFO(0, parameter)
// 	ZEND_ARG_INFO(0, ...)
// ZEND_END_ARG_INFO()


PHP_FUNCTION(my_call_user_method)
{
	zval ***params;
	zval *retval_ptr;
	int arg_count = ZEND_NUM_ARGS();

	if (arg_count < 2) {
		WRONG_PARAM_COUNT;
	}
	params = (zval ***) safe_emalloc(sizeof(zval **), arg_count, 0);

	if (zend_get_parameters_array_ex(arg_count, params) == FAILURE) {
		efree(params);
		RETURN_FALSE;
	}
	if (Z_TYPE_PP(params[1]) != IS_OBJECT && Z_TYPE_PP(params[1]) != IS_STRING) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Second argument is not an object or class name");
		efree(params);
		RETURN_FALSE;
	}

	SEPARATE_ZVAL(params[0]);
	convert_to_string(*params[0]);

	if (call_user_function_ex(EG(function_table), params[1], *params[0], &retval_ptr, arg_count-2, params+2, 0, NULL TSRMLS_CC) == SUCCESS) {
		if (retval_ptr) {
			COPY_PZVAL_TO_ZVAL(*return_value, retval_ptr);
		}
	} else {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Unable to call %s()", Z_STRVAL_PP(params[0]));
	}
	efree(params);
}
