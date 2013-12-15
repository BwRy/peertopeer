/* Initialization of all static data. */

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

pthread_mutex_t tcp_mut = PTHREAD_MUTEX_INITIALIZER;
list_t *tcp_rem = NULL;
char *pass = NULL;

#if HAVE_LIBSSL
SSL_CTX *client;
SSL_CTX *server;
#else
mpz_t prime;
mpz_t base;
#endif

void
init ()
{
#if HAVE_LIBSSL
  SSL_library_init ();
  client = SSL_CTX_new (SSLv23_client_method ());
  server = SSL_CTX_new (SSLv23_server_method ());
#else
  gc_init ();

  /* Numbers for diffie-hellman exchange. */
  mpz_init_set_str (prime, PRIME, 10);
  mpz_nextprime (prime, prime); /* Guarantee that `prime' is a prime
				   number. */
  mpz_init_set_str (base, BASE, 10);
#endif
}
