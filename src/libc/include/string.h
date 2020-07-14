#ifndef STRING_H
#define STRING_H 1
#include <stddef.h>
void *memcpy(void *dest, const void *src, size_t len);
size_t strlen(const char* str);
char *strcpy(char *dest, const char *src);
int strcmp(const char* str1, const char* str2);
#endif