#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([Com], [0.1], [colfordk@gmail.com],, 
	[https://github.com/kcolford/peertopeer])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])

# Initialize automake with xz compression instead of gzip.
AM_INIT_AUTOMAKE([no-dist-gzip dist-xz])

# We want every extra feature we can find.
AC_USE_SYSTEM_EXTENSIONS

# I like this, it keeps everything clean.
AM_SILENT_RULES([yes])

AC_CONFIG_SRCDIR([com.h])
AC_CONFIG_HEADERS([config.h])

# Libtool!
LT_INIT

# Debuging stuff, it'll be removed later.
CFLAGS="-ggdb3"

# Find the necessary programs and run the gnulib macros.
AC_PROG_CC
gl_EARLY
gl_INIT

# Experimental support for ssl.
AC_ARG_WITH([ssl], 
  [AS_HELP_STRING([--with-ssl], [enable experimental ssl support])], 
  [AC_CHECK_LIB([ssl], [SSL_library_init], , 
    [AC_MSG_ERROR([Openssl library requested but not found.])])],
  [AC_DEFINE([HAVE_LIBSSL], [0])]
)

# We want the GMP for the diffie-hellman key exchange routines.
AC_CHECK_LIB(gmp, __gmpz_init, ,
       [AC_MSG_ERROR([GNU MP not found, see http://gmplib.org/])])

AC_CONFIG_FILES([Makefile
                 lib/Makefile
		 tests/Makefile])
AC_OUTPUT
