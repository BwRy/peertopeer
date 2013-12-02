/* Main method definition. */

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
	{
	  fprintf (stderr, "\n");
	  break;
	}
      list_t *p;
      pthread_mutex_lock (&tcp_mut);
      for (p = tcp_rem; p != NULL; p = p->nxt)
	{
	  if (send (p->sock, in, strlen (in) + 1, 0) < 0)
	    {
	      error (0, errno, "Could not send message to host %s", p->host);
	      pthread_cancel (p->thread);
	    }
	}
      pthread_mutex_unlock (&tcp_mut);
      free (in);
    }

  return 0;
}
