#ifndef PHP_UNITYLZ4_H
#define PHP_UNITYLZ4_H

extern zend_module_entry unitylz4_module_entry;
#define phpext_unitylz4_ptr &unitylz4_module_entry

#define PHP_UNITYLZ4_VERSION "0.1.0"
#define PHP_UNITYLZ4_EXTNAME "unitylz4"

#ifdef PHP_WIN32
#	define PHP_UNITYLZ4_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_UNITYLZ4_API __attribute__ ((visibility("default")))
#else
#	define PHP_UNITYLZ4_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

#define UNITYLZ4_G(v) ZEND_MODULE_GLOBALS_ACCESSOR(unitylz4, v)

#if defined(ZTS) && defined(COMPILE_DL_UNITYLZ4)
ZEND_TSRMLS_CACHE_EXTERN()
#endif

#endif