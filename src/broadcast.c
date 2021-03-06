/* This file contains the routine for broadcasting some data to all
   hosts. */

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
broadcast (void *arg)
{
  struct broadcast_arg *me = arg;
  pthread_mutex_lock (&tcp_mut);
  list_t *p;
  for (p = tcp_rem; p; p = p->nxt)
    {
      if (me->from == p)
	continue;
      if (send_data (p, me->data, me->len) <= 0)
	pthread_cancel (p->thread);
    }
  pthread_mutex_unlock (&tcp_mut);
  free (me->data);
  free (me);
  return NULL;
}
