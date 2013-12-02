/* This contains the cleanup routine to be called when a socket is no
   longer needed. */

#include "com.h"

void
cleanup_sock (int *sock)
{
  shutdown (*sock, SHUT_RDWR);
}
