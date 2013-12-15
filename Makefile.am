SUBDIRS = lib tests
ACLOCAL_AMFLAGS = -I m4
EXTRA_DIST = m4/gnulib-cache.m4 $(TESTS)

AM_CPPFLAGS = -I$(srcdir)/lib
AM_CFLAGS = -pthread

pkglib_LTLIBRARIES = libcom.la
libcom_la_LDFLAGS = $(GETADDRINFO) $(HOSTENT_LIB) $(INET_NTOP_LIB) $(LIBSOCKET) $(LTLIBINTL) $(LTLIBREADLINE) $(SERVENT_LIB)
libcom_la_SOURCES = 				\
src/add_entry.c					\
src/authenticate.c 				\
src/cleanup_sock.c				\
src/connect_daemon.c				\
src/delete_entry.c				\
src/entry.c					\
src/init.c					\
src/listen_daemon.c				\
src/make_socket.c 				\
src/relay_daemon.c				

include_HEADERS = com.h

bin_PROGRAMS = com
com_SOURCES = src/main.c
com_LDADD = libcom.la lib/libgnu.la

AM_TESTS_ENVIRONMENT = export PATH=.:$$PATH;
TESTS = tests/help.sh tests/version.sh
