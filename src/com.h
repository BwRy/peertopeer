/* Main header file. */

#ifndef COM_H
#define COM_H

#include "config.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#include <unistd.h>
#include <pthread.h>
#include <error.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

extern char *readline (const char *);

#define TCP_PORT "3488"

#define strdup(str) strcpy (calloc (strlen (str) + 1, sizeof (char)), (str))

typedef struct _mylist
{
  char *host;
  int sock;
  pthread_t thread;
  struct _mylist *nxt;
} list_t;

extern pthread_mutex_t tcp_mut;
extern list_t *tcp_rem;

extern void cleanup_sock (int *);

extern list_t *entry (char *, int);
extern void add_entry (const list_t *);
extern void delete_entry (const list_t *);

extern void *listen_daemon (void *);
extern void *connect_daemon (void *);
extern void *relay_daemon (void *);

extern int main (int, char **);

#endif
