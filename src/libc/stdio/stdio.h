#ifndef STDIO_H
#define STDIO_H
void puts(char* string);
void putchar(char c);
int printf(const char* format, ...);
char* hex_to_str(int hex, char* dest);
#endif