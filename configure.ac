#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([com], [0.1], [colfordk@gmail.com])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])

# Start up automake.  xz has a better compression ratio than gzip so
# we use it instead.
AM_INIT_AUTOMAKE([no-dist-gzip dist-xz])
AC_USE_SYSTEM_EXTENSIONS
LT_INIT

# A minor novelty
AM_SILENT_RULES([yes])

AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_HEADERS([config.h])

# This is just debugging stuff, I'll get rid of it later.
CFLAGS="-ggdb3"

# Checks for programs.
AC_PROG_CXX
AC_PROG_AWK
AC_PROG_CC
gl_EARLY
gl_INIT
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_RANLIB
AC_PROG_MKDIR_P
AC_PROG_YACC

# Checks for libraries.
AC_SEARCH_LIBS([readline], [readline gnu])

# Checks for header files.
AC_FUNC_ALLOCA
AC_CHECK_HEADERS([OS.h argz.h arpa/inet.h fcntl.h float.h inttypes.h langinfo.h libintl.h limits.h locale.h malloc.h netdb.h netinet/in.h stddef.h stdint.h stdio_ext.h stdlib.h string.h sys/param.h sys/socket.h unistd.h wchar.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_UID_T
AC_C_INLINE
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_FUNC_OBSTACK
AC_TYPE_OFF_T
AC_C_RESTRICT
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT8_T
AC_CHECK_TYPES([ptrdiff_t])

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_FUNC_MALLOC
AC_FUNC_MBRTOWC
AC_FUNC_MMAP
AC_FUNC_REALLOC
AC_FUNC_STRERROR_R
AC_CHECK_FUNCS([__argz_count __argz_next __argz_stringify getcwd getdelim gethostbyname getpagesize localeconv mblen mbrlen memchr mempcpy memset munmap nl_langinfo setlocale socket stpcpy strcasecmp strchr strcspn strdup strerror strstr strtoul])

AC_CONFIG_FILES([Makefile
                 lib/Makefile])
AC_OUTPUT
