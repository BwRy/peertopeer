/* Create list_t entry for tcp_rem. */

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

#define len (mpz_sizeinbase (prime, 8))

list_t *
entry (char *host, int sock, int flags)
{
  list_t *p = xmalloc (sizeof *p);
  p->host = xstrdup (host);

#if HAVE_LIBSSL
  p->ssl = flags & 1 ? SSL_new (client) : SSL_new (server);
  SSL_set_fd (p->ssl, sock);
#else
  p->sock = sock;
  gc_cipher_open (GC_AES256, GC_STREAM, &p->cipher);
  mpz_t my_num;
  mpz_init (my_num);

  char *key = xcalloc (len, sizeof *key);

  pthread_cleanup_push (free, key);
  gc_random (key, len);

  mpz_import (my_num, len, 1, 1, 1, 0, key);

  mpz_t sent;
  mpz_init_set (sent, base);
  mpz_powm (sent, sent, my_num, prime);

  char *buff = xcalloc (len, sizeof *buff);

  pthread_cleanup_push (free, buff);
  mpz_export (buff, NULL, 1, 1, 1, 0, sent);
  
  if (send (sock, buff, len, 0) < 0)
    error (1, errno, "Failed to perform handshake");

  if (recv (sock, buff, len, 0) < 0)
    error (1, errno, "Failed to perform handshake");

  mpz_import (sent, len, 1, 1, 1, 0, buff);
  pthread_cleanup_pop (1);
  
  mpz_powm (sent, sent, my_num, prime);
  mpz_export (key, NULL, 1, 1, 1, 0, sent); 
 
  gc_cipher_setkey (p->cipher, len, key);
  pthread_cleanup_pop (1);
#endif /* HAVE_LIBSSL */

  return p;
}
