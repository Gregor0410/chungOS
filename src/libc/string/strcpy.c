#include "../include/string.h"
#include <stddef.h>

char *strcpy (char *dest, const char *src)
{
  return memcpy (dest, src, strlen (src) + 1);
}