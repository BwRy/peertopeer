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

int
authenticate (const list_t *lst)
{  
  char *buff = xstrdup (pass);
  int len = strlen (buff);

  /* Handshake */
  gc_cipher_encrypt_inline (lst->cipher, len, buff);
  if (send (lst->sock, buff, len, 0) < 0)
    return -1;
  if (recv (lst->sock, buff, len, 0) < 0)
    return -1;
  gc_cipher_decrypt_inline (lst->cipher, len, buff);

  if (strcmp (buff, pass))
    return -1;
  else
    return 0;
}
