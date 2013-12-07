#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([Com], [0.1], [colfordk@gmail.com],, 
	[https://github.com/kcolford/peertopeer])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([no-dist-gzip dist-xz])
AC_USE_SYSTEM_EXTENSIONS
AM_SILENT_RULES([yes])
AC_CONFIG_SRCDIR([com.h])
AC_CONFIG_HEADERS([config.h])
LT_INIT
AC_PROG_CC
gl_EARLY
gl_INIT

CFLAGS="-ggdb3"

AC_CONFIG_FILES([Makefile
                 lib/Makefile])
AC_OUTPUT
