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

void
delete_entry(list_t *lst)
{
  pthread_mutex_lock (&tcp_mut);
  list_t head;
  head.nxt = tcp_rem;
  list_t *p = &head;
  while (p->nxt != lst)
    p = p->nxt;
  p->nxt = lst->nxt;
  pthread_mutex_unlock (&tcp_mut);

  free (lst->host);
#if HAVE_LIBSSL
  SSL_shutdown (lst->ssl);
#else
  shutdown (lst->sock, SHUT_RDWR);
  gc_cipher_close (lst->cipher);
#endif
  pthread_cancel (lst->thread);
  free (lst);
}
