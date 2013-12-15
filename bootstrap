#!/bin/sh

gnulib-tool					\
    --import					\
    --vc-files                                  \
    --symbolic                                  \
    --with-tests				\
    --libtool					\
    argp					\
    crypto/gc-rijndael				\
    error					\
    getaddrinfo					\
    getpass					\
    readline					\
    xalloc

autoreconf --install --symlink
