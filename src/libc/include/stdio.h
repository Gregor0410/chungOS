#ifndef STDIO_H
#define STDIO_H 1
void puts(char* string);
char *gets(char* str);
void putchar(char c);
int printf(const char* format, ...);
char* hex_to_str(int hex, char* dest);
#endif