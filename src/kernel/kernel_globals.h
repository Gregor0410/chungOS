#ifndef KERNEL_GLOBALS
#define KERNEL_GLOBALS
#include <stdint.h>
#include <stdbool.h>
struct stdin {
    bool readable;
    char character;
};
#endif