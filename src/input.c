/* This routine returns a malloc'd line of input from stdin with a
   prompt. */

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

char *
input (const char *prompt)
{
#if WITH_READLINE
  return readline (prompt);
#else
  fprintf (stderr, "%s", prompt);
  fflush (stderr);
  char *out = NULL;
  size_t alloc = 0, len = 0;
  char c;
  while ((c = getchar ()) != EOF)
    {	
      if (len == alloc)
	out = x2realloc (out, &alloc);
      if (c == '\n')
	{
	  out[len++] = 0;
	  break;
	}
      else
	out[len++] = c;
    }
  return out;
#endif /* WITH_READLINE */
}
