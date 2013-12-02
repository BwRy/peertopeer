/* This is a routine to automatically create a fully configured
   socket. */

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

#include "com.h"

int
make_socket (const char *host, const char *service, int isclient)
{
  struct addrinfo hints = { AI_PASSIVE, AF_UNSPEC, SOCK_STREAM, 0 };
  struct addrinfo *res;
  int errcode;
  if ((errcode = getaddrinfo (host, service, &hints, &res)))
     error (1, errno, "Address lookup failed %s", gai_strerror (errcode));

  int sock;

  pthread_cleanup_push (freeaddrinfo, res);

  struct addrinfo *p;
  for (p = res; p != NULL; p = p->ai_next)
    {
      sock = socket (p->ai_family, p->ai_socktype, p->ai_protocol);
      if (sock < 0)
	{
	  error (0, errno, "Failed to create socket");
	  errno = 0;
	  continue;
	}
      if (isclient)
	{
	  if (connect (sock, p->ai_addr, p->ai_addrlen))
	    {
	      error (0, errno, "Connect failed");
	      errno = 0;
	      close (sock);
	      continue;
	    }
	}
      else
	{
	  if (bind (sock, p->ai_addr, p->ai_addrlen))
	    {
	      error (0, errno, "Lookup failed");
	      errno = 0;
	      close (sock);
	      continue;
	    }
	  if (listen (sock, 5))
	    {
	      error (0, errno, "Could not listen for connections");
	      errno = 0;
	      close (sock);
	      continue;
	    }
	}
      break;
    }
  if (p == NULL)
    error (1, 1, "All possibilities failed.");

  pthread_cleanup_pop (1);

  return sock;
}
