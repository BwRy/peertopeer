/* This daemon perfoms the initial connection to a network. */

#include "com.h"

void *
connect_daemon (void *arg)
{
  char *host = arg;

  struct addrinfo hints = { 0, AF_UNSPEC, SOCK_STREAM, 0 };
  struct addrinfo *res;
  int errcode;
  if ((errcode = getaddrinfo (arg, TCP_PORT, &hints, &res)))
    error (1, errno, "Address lookup failed %s", gai_strerror (errcode));
  
  int sock;

  pthread_cleanup_push (freeaddrinfo, res);

  struct addrinfo *p;
  for (p = res; p; p = p->ai_next)
    {
      sock = socket (p->ai_family, p->ai_socktype, p->ai_protocol);
      if (sock < 0)
	{
	  error (0, errno, "Failed to create socket");
	  errno = 0;
	  continue;
	}
      if (connect (sock, p->ai_addr, p->ai_addrlen))
	{
	  error (0, errno, "First lookup failed");
	  errno = 0;
	  close (sock);
	  continue;
	}
      break;
    }
  if (p == NULL)
    error (1, 1, "All possibilities failed.");

  host = strdup (p->ai_canonname);

  pthread_cleanup_pop (1);

  return relay_daemon (entry (host, sock));
}

