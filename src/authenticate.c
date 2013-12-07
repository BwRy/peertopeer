/* Check to make sure that the other host is really who they say they
   are. */

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

#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>

int
authenticate (const list_t *lst)
{
  char buffer[] = AUTH_MESSAGE;
  gc_cipher_encrypt_inline (global_crypt, sizeof buffer, buffer);
  if (send (lst->sock, buffer, sizeof buffer, 0) < 0)
    return -1;
  ssize_t seen = recv (lst->sock, buffer, sizeof buffer, 0);
  if (seen < 0)
    return -1;
  gc_cipher_decrypt_inline (global_crypt, sizeof buffer, buffer);
  buffer[sizeof buffer - 1] = '\0';
  if (strcmp (buffer, AUTH_MESSAGE) != 0)
    return -1;
  return 0;
}
