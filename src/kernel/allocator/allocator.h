#ifndef ALLOCATOR_H
#define ALLOCATOR_H
#define NUM_PAGES 0xfffff
#include <stdbool.h>
#include "../kernel.h"
void page_fault_handler(registers_t r);
void *index_to_addr(uint32_t pd_index,uint32_t pt_index,uint32_t p_index);
void *get_phys_addr(void* address);
bool pde_present(uint32_t pd_index);
bool pte_present(uint32_t pd_index, uint32_t pt_index);
void refresh_bitmap();
void *get_free_page();
uint32_t memory_bitmap[NUM_PAGES/32];
uint32_t prev_pointer;
#endif