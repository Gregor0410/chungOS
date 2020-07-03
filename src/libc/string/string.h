#ifndef STRING_H
#define STRING_H
#include <stddef.h>
void *memcpy(void *dest, const void *src, size_t len);
size_t strlen(const char* str);
char *strcpy(char *dest, const char *src);
#endif