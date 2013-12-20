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

# Libtool, without the shared libraries.
LT_INIT([disable-shared])

# Debuging stuff, it'll be removed later.
CFLAGS="-ggdb3"

# Find the necessary programs and run the gnulib macros.
AC_PROG_CC
gl_EARLY
gl_INIT

# Experimental support for ssl.
AC_ARG_WITH([ssl], 
  [AS_HELP_STRING([--with-ssl], [enable experimental ssl support])], ,
  [with_ssl="no"])

AC_DEFINE([WITH_SSL], [], [Whether or not we are using SSL.])

if [ x$with_ssl != "xno" ]; then 
  AC_CHECK_LIB([ssl], [SSL_library_init], , 
    [AC_MSG_ERROR([OpenSSL library not found])])
  AC_DEFINE([WITH_SSL], [1])
else 
  AC_DEFINE([WITH_SSL], [0])
fi

# Support for readline.
AC_ARG_WITH([readline], 
[AS_HELP_STRING([--with-readline], [use readline])], 
[case $with_readline in
yes|no) ;;
*) AC_MSG_ERROR([Invalid option]) ;;
esac],
[with_readline=no])

if test "$with_readline" = "yes"; then
   AC_CHECK_LIB([readline], [readline], , [AC_MSG_ERROR([Readline not found.])])
   AC_DEFINE([WITH_READLINE], [1], [Enable use of the readline library.])
fi

# We want the GMP for the diffie-hellman key exchange routines.
AC_CHECK_LIB([gmp], [__gmpz_init], ,
  [AC_MSG_ERROR([GNU MP not found, see http://gmplib.org/])])

AC_CONFIG_FILES([Makefile
                 lib/Makefile
		 tests/Makefile])
AC_OUTPUT
