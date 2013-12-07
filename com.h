/* Main header file. */

/* Copyright (C) 2013 Kieran Colford

   This program is free software: you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation, either version 3 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see
   <http://www.gnu.org/licenses/>.

   The copyright holder can be contacted at <colfordk@gmail.com>. */

#ifndef COM_H
#define COM_H

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <errno.h>
#include <error.h>

#include <pthread.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <argp.h>
#include <readline/readline.h>
#include "getpass.h"
#include "gc.h"

#define FATAL_ERRORS 1
#define TCP_PORT "3488"
#define AUTH_MESSAGE "Hello, World!  How are you today?"

typedef struct _mylist
{
  char *host;
  int sock;
  pthread_t thread;
  struct _mylist *nxt;
} list_t;

#ifdef __cplusplus
extern "C" {
#endif
#if 0
}
#endif

extern pthread_mutex_t tcp_mut;
extern list_t *tcp_rem;
extern gc_cipher_handle global_crypt;

extern int authenticate (const list_t *entry);
extern int make_socket (const char *, const char *, int);
extern void cleanup_sock (int *);

extern list_t *entry (char *, int);
extern void add_entry (const list_t *);
extern void delete_entry (const list_t *);

extern void *listen_daemon (void *);
extern void *connect_daemon (void *);
extern void *relay_daemon (void *);

extern int main (int, char **);

#if 0
{
#endif
#ifdef __cplusplus
}
#endif

#endif
