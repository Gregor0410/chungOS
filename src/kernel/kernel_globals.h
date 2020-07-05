#ifndef KERNEL_GLOBALS
#define KERNEL_GLOBALS
#include <stdint.h>
#include <stdbool.h>
typedef struct {
    volatile bool writeable;
    volatile bool readable;
    volatile char character;
    char* dest;
}char_stream_t;
char_stream_t stdin;
#endif