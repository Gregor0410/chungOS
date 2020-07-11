#include "allocator.h"

void page_fault_handler(registers_t r){
    int fault_address;
    asm("mov %%cr2,%%eax":"=a"(fault_address));
    printf("Page fault at address %x\n",fault_address);
    printf("Error code: %x",r.err_code);
    asm("hlt");
}