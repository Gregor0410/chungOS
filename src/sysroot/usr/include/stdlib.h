#pragma once
typedef struct header{
    bool free : 1;
    size_t size : 31;
    struct header *next;
}header_t;
void* malloc(size_t size);
void free(void *ptr);
void *brk;