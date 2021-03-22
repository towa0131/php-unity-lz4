#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

extern "C"{
    #include "php.h"
    #include "php_ini.h"
    #include "ext/standard/info.h"
}

#include "php_unitylz4.hpp"
#include "lz4util.hpp"

using namespace std;

static int le_unitylz4;

PHP_FUNCTION (unity_lz4_uncompress) {
    zend_string *result;
    zend_string *data;

    const unsigned char *buffer;
    size_t length;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STR(data)
    ZEND_PARSE_PARAMETERS_END();

    buffer = (unsigned char *) ZSTR_VAL(data);
    length = ZSTR_LEN(data);

    vector<uint8_t> vec;

    for (int i = 0; i < length; i++) {
        vec.push_back(buffer[i]);
    }

    LZ4Decompressor lz4;
    vector<uint8_t> outBuffer = lz4.decompress(vec);

    if (outBuffer.size() == 0) {
        RETURN_NULL();
    }

    char *cstr = (char*)emalloc(outBuffer.size());

    copy(outBuffer.begin(), outBuffer.end(), cstr);

    result = zend_string_init(cstr, outBuffer.size(), 0);
    efree(cstr);

    RETURN_STR(result);
}

PHP_MINIT_FUNCTION(unitylz4) {
    return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(unitylz4) {
    return SUCCESS;
}

PHP_RINIT_FUNCTION(unitylz4) {
#if defined(COMPILE_DL_UNITYLZ4) && defined(ZTS)
    ZEND_TSRMLS_CACHE_UPDATE();
#endif
    return SUCCESS;
}

PHP_RSHUTDOWN_FUNCTION(unitylz4) {
    return SUCCESS;
}

PHP_MINFO_FUNCTION(unitylz4) {
    php_info_print_table_start();
    php_info_print_table_header(2, "unitylz4 support", "enabled");
    php_info_print_table_end();
}

#if PHP_MAJOR_VERSION >= 8
ZEND_BEGIN_ARG_INFO_EX(arginfo_void, 0, 0, 0)
ZEND_END_ARG_INFO()

const zend_function_entry unitylz4_functions[] = {
    PHP_FE(unity_lz4_uncompress, arginfo_void)
    PHP_FE_END
};

#else

const zend_function_entry unitylz4_functions[] = {
    PHP_FE(unity_lz4_uncompress, NULL)
    PHP_FE_END
};

#endif

zend_module_entry unitylz4_module_entry = {
    STANDARD_MODULE_HEADER,
    PHP_UNITYLZ4_EXTNAME,
    unitylz4_functions,
    PHP_MINIT(unitylz4),
    PHP_MSHUTDOWN(unitylz4),
    PHP_RINIT(unitylz4),
    PHP_RSHUTDOWN(unitylz4),
    PHP_MINFO(unitylz4),
    PHP_UNITYLZ4_VERSION,
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_UNITYLZ4
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(unitylz4)
#endif
