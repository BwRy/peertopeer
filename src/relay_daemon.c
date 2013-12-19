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

void *
relay_daemon (void *arg)
{
  list_t *me = arg;
  me->thread = pthread_self ();
  add_entry (me);
  pthread_cleanup_push (delete_entry, me);

  if (authenticate (me))
    pthread_exit (0);

  for (;;)
    {
      char *buffer = xmalloc (1000); 
      ssize_t seen = recv_data (me, buffer, sizeof buffer);
      if (seen <= 0)
	break;

      struct broadcast_arg *broad = xmalloc (sizeof *broad);
      broad->from = me;
      broad->data = buffer;
      broad->len = seen;
      pthread_t thread;
      pthread_create (&thread, NULL, broadcast, broad);

      printf ("%s: %s\n", me->host, buffer);
    }

  pthread_cleanup_pop (1);
  return NULL;
}
