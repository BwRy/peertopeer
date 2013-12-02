SUBDIRS = lib
ACLOCAL_AMFLAGS = -I m4
EXTRA_DIST = m4/gnulib-cache.m4

AM_CFLAGS = -pthread

bin_PROGRAMS = com
com_SOURCES =					\
src/add_entry.c					\
src/cleanup_sock.c				\
src/com.h					\
src/connect_daemon.c				\
src/delete_entry.c				\
src/entry.c					\
src/listen_daemon.c				\
src/main.c					\
src/make_socket.c 				\
src/relay_daemon.c				\
src/static.c
