/* Main method definition. */

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
#include <stdio.h>
#include <errno.h>
#include <error.h>

#include <readline/readline.h>
#include <argp.h>

#include "getpass.h"

static char *tgt = NULL;
static char *prompt = "message: ";
static int use_pass = 0;
static char *pass = NULL;

const char *argp_program_version = PACKAGE_STRING;
const char *argp_program_bug_address = "<" PACKAGE_BUGREPORT ">";

static void
print_version (FILE *stream, struct argp_state *state)
{
  static const char *out[] = {
    PACKAGE_STRING,
    "",
    "Copyright (C) 2013 Kieran Colford",
    "License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>",
    "This is free software: you are free to change and redistribute it.",
    "There is NO WARRANTY, to the extent permitted by law.",
    "",
    "Written by Kieran Colford",
    0
  };
  const char **p = out;
  
  while (*p)
    fprintf (stream, "%s\n", *p++);
}

void(*argp_program_version_hook)(FILE *, struct argp_state *) = print_version;

static const struct argp_option opts[] = {
  { "prompt", 'p', "STRING", 0, "Use STRING as the message " 
    "to prompt the user for input"},
  { "secure", 's', 0, 0, "Use a secure connection" },
  { "password", 1, "PASS", 0, "Use PASS as the password, implies --secure" },
  { 0 }
};

static error_t 
parse (int key, char *arg, struct argp_state *state)
{
  switch (key)
    {
    case 1:
      pass = arg;
    case 's':
      use_pass = 1;
      break;
    case 'p':
      prompt = arg;
      break;
    case ARGP_KEY_ARG:
      if (state->arg_num == 0)
	tgt = arg;
      else
	argp_usage (state);
      break;
    default:
      return ARGP_ERR_UNKNOWN;
    }
  return 0;
}

static const struct argp option = { opts, parse, "[HOST]", "Connect to HOST " 
				    "to establish a peer-to-peer chat " 
				    "network." };

int main (int argc, char *argv[])
{
  gc_init ();
  gc_cipher_open (GC_AES256, GC_STREAM, &global_crypt);

  argp_parse (&option, argc, argv, 0, NULL, NULL);

  if (use_pass && pass == NULL)
    pass = getpass ("Password: ");

  gc_cipher_setkey (global_crypt, strlen (pass), pass);

  pthread_t thread_con;
  if (tgt != NULL)
    if (pthread_create (&thread_con, NULL, connect_daemon, tgt))
      error (1, errno, "pthread_create");

  pthread_t thread_lis;
  if (pthread_create (&thread_lis, NULL, listen_daemon, NULL))
    error (1, errno, "pthread_create");

  for (;;)
    {
      char *in = readline (prompt);
      if (in == NULL)
	{
	  fprintf (stderr, "\n");
	  break;
	}
      size_t len = strlen (in);
      gc_cipher_encrypt_inline (global_crypt, len, in);
      list_t *p;
      pthread_mutex_lock (&tcp_mut);
      for (p = tcp_rem; p != NULL; p = p->nxt)
	{
	  if (send (p->sock, in, len, 0) < 0)
	    {
	      error (FATAL_ERRORS, errno, "Could not send message to host %s",
		     p->host);
	      pthread_cancel (p->thread);
	    }
	}
      pthread_mutex_unlock (&tcp_mut);
      free (in);
    }

  return 0;
}
