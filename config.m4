PHP_ARG_ENABLE(unitylz4, whether to enable unitylz4 support,
Make sure that the comment is aligned:
[  --enable-unitylz4           Enable unitylz4 support])

if test "$PHP_UNITYLZ4" != "no"; then
  PHP_REQUIRE_CXX()
  PHP_SUBST(UNITYLZ4_SHARED_LIBADD)
  PHP_ADD_LIBRARY(stdc++, 1, UNITYLZ4_SHARED_LIBADD)
  PHP_NEW_EXTENSION(unitylz4, unitylz4.cpp lz4util.cpp binaryreader.cpp, $ext_shared)
fi
