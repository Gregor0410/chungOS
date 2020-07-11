#ifndef ALLOCATOR_H
#define ALLOCATOR_H
#include "../kernel.h"
void page_fault_handler(registers_t r);
void *index_to_addr(uint32_t pd_index,uint32_t pt_index,uint32_t p_index);
void *get_phys_addr(void* address);
#endif