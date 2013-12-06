/* Delete an entry from the global tcp_rem table. */

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

#include <stdlib.h>
#include <string.h>

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
