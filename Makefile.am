SUBDIRS = lib
ACLOCAL_AMFLAGS = -I m4
EXTRA_DIST = m4/gnulib-cache.m4

AM_CFLAGS = -pthread

bin_PROGRAMS = com
com_SOURCES = src/com.h src/main.c src/static.c src/relay_daemon.c \
src/listen_daemon.c src/connect_daemon.c src/cleanup_sock.c
