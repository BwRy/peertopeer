/* This is the daemon that relays input from a socket to stdout and to
   all other sockets. */

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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <error.h>

#include <sys/socket.h>

void *
relay_daemon (void *arg)
{
  list_t *me = arg;
  me->thread = pthread_self ();
  pthread_cleanup_push (free, me);
  pthread_cleanup_push (cleanup_sock, &me->sock);
  pthread_cleanup_push (free, me->host);
  add_entry (me);
  pthread_cleanup_push (delete_entry, me->host);

  for (;;)
    {
      char buffer[1000];
      memset (buffer, 0, sizeof buffer);
      ssize_t seen = recv (me->sock, buffer, sizeof buffer, 0);
      if (seen == 0)
	{
	  error (FATAL_ERRORS, 0, "The host %s has disconnected from us", 
		 me->host);
	  break;
	}
      else if (seen < 0)
	error (1, errno, "An error occured when recieving data");
      else
	{
	  printf ("%s: %s\n", me->host, buffer);
	  list_t *p;
	  pthread_mutex_lock (&tcp_mut);
	  for (p = tcp_rem; p; p = p->nxt)
	    {
	      if (p->sock == me->sock)
		continue;
	      if (send (p->sock, buffer, (size_t) seen, 0) < 0)
		error (1, errno, "Failed to relay data to host %s", p->host);
	    }
	}
    }

  pthread_cleanup_pop (1);
  pthread_cleanup_pop (1);
  pthread_cleanup_pop (1);
  pthread_cleanup_pop (1);
  return NULL;
}
