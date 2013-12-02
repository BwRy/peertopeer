/* Initialization of all static data. */

#include "com.h"

pthread_mutex_t tcp_mut = PTHREAD_MUTEX_INITIALIZER;
list_t *tcp_rem = NULL;

list_t *
entry (char *host, int sock)
{
  list_t *p = malloc (sizeof *p);
  p->host = host;
  p->sock = sock;
  return p;
}

void
add_entry (const list_t *lst)
{
  list_t *p = malloc (sizeof *p);
  *p = *lst;
  pthread_mutex_lock (&tcp_mut);
  p->nxt = tcp_rem;
  tcp_rem = p;
  pthread_mutex_unlock (&tcp_mut);
}

void
delete_entry(const list_t *lst)
{
  pthread_mutex_lock (&tcp_mut);
  list_t head;
  head.nxt = tcp_rem;
  list_t *p = &head;
  while (strcmp (lst->host, p->nxt->host))
    p = p->nxt;
  list_t *tmp = p->nxt;
  p->nxt = p->nxt->nxt;
  pthread_mutex_unlock (&tcp_mut);
  free (tmp);
}
