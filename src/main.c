/* Main method definition. */

#include "com.h"

int main (int argc, char *argv[])
{
  if (argc != 2)
    error (1, 1, "Illegal arguments");

  pthread_t thread_con;
  if (pthread_create (&thread_con, NULL, connect_daemon, argv[1]))
    error (1, errno, "pthread_create");

  pthread_t thread_lis;
  if (pthread_create (&thread_lis, NULL, listen_daemon, NULL))
    error (1, errno, "pthread_create");

  for (;;)
    {
      char *in = readline ("message: ");
      if (in == NULL)
	break;
      list_t *p;
      pthread_mutex_lock (&tcp_mut);
      for (p = tcp_rem; p; p = p->nxt)
	send (p->sock, in, strlen (in) + 1, 0);
      pthread_mutex_unlock (&tcp_mut);
      free (in);
    }

  return 0;
}
