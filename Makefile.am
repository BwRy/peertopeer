SUBDIRS = lib
ACLOCAL_AMFLAGS = -I m4
EXTRA_DIST = m4/gnulib-cache.m4

AM_CPPFLAGS = -Ilib
AM_CFLAGS = -pthread

pkglib_LTLIBRARIES = libcom.la
libcom_la_LDFLAGS = $(GETADDRINFO) $(HOSTENT_LIB) $(INET_NTOP_LIB) $(LIBSOCKET) $(LTLIBINTL) $(LTLIBREADLINE) $(SERVENT_LIB)
libcom_la_SOURCES = 				\
src/add_entry.c					\
src/cleanup_sock.c				\
src/connect_daemon.c				\
src/delete_entry.c				\
src/entry.c					\
src/listen_daemon.c				\
src/make_socket.c 				\
src/relay_daemon.c				\
src/static.c

include_HEADERS = com.h

bin_PROGRAMS = com
com_SOURCES = src/main.c
com_LDADD = libcom.la lib/libgnu.la
