/* This is the abstraction layer for sending data across a connect_t
   structure. */

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

ssize_t 
send_data (list_t *conn, const void *buf, size_t len)
{
#if WITH_SSL
  return SSL_write (conn->ssl, buf, len);
#else
  void *buff = xmemdup (buf, len);
  gc_cipher_encrypt_inline (conn->cipher, len, buff);
  ssize_t ret = send (conn->sock, buff, len, 0);
  free (buff);
  return ret;
#endif
}

