/* This is the abstraction layer for sending data accross a connect_t
   structure. */

/* Copyright (C) 2013 Kieran Colford

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at
your option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

The copyright holder can be contacted at <colfordk@gmail.com>. */

#include "com.h"

ssize_t 
recv_data (connect_t *conn, void *buf, size_t len)
{
#if HAVE_LIBSSL
  return SSL_read (conn->ssl, buf, len);
#else
  ssize_t ret = recv (conn->sock, buf, len, 0);
  gc_cipher_decrypt_inline (conn->cipher, len, buf);
  return ret;
#endif
}
