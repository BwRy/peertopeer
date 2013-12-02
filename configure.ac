#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([com], [0.1], [colfordk@gmail.com])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([no-dist-gzip dist-xz gnu])
AM_SILENT_RULES([yes])
AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_HEADERS([config.h])

AC_USE_SYSTEM_EXTENSIONS

AC_SUBST([CFLAGS], [-ggdb3])

# Checks for programs.
AC_PROG_CC
gl_EARLY
gl_INIT

# Checks for libraries.
AC_SEARCH_LIBS([readline], [readline edit])

# Checks for header files.
AC_CHECK_HEADERS([OS.h fcntl.h libintl.h limits.h netdb.h stddef.h stdint.h stdlib.h string.h sys/param.h sys/socket.h unistd.h wchar.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_UID_T
AC_TYPE_INT32_T
AC_FUNC_OBSTACK
AC_TYPE_OFF_T
AC_C_RESTRICT
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T

# Checks for library functions.
AC_FUNC_ALLOCA
AC_FUNC_ERROR_AT_LINE
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_FUNC_STRERROR_R
AC_CHECK_FUNCS([getpagesize memset socket strdup strerror])

AC_CHECK_FUNC([getaddrinfo],, [AC_MSG_ERROR([The required function getaddrinfo is not available on your system.  Install the most recent version of glibc to get it.])])

AC_CONFIG_FILES([Makefile
                 lib/Makefile])
AC_OUTPUT
