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
  send_data (lst, buff, len);
  memset (buff, 0, len);
  recv_data (lst, buff, len);

  int ret = strcmp (buff, pass) == 0 ? 0 : -1;
  free (buff);
  return ret;
}
