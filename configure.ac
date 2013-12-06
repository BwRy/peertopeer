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

AC_CONFIG_SRCDIR([com.h])
AC_CONFIG_HEADERS([config.h])

# This is just debugging stuff, I'll get rid of it later.
CFLAGS="-ggdb3"

# Checks for programs.
AC_PROG_CC
gl_EARLY
gl_INIT

AC_CONFIG_FILES([Makefile
                 lib/Makefile])
AC_OUTPUT
