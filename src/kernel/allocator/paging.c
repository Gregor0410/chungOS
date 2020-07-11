#include "allocator.h"
#define index_to_addr(pd_index,pt_index,p_index) ((pd_index <<22)|(pt_index<<12)|p_index) 


void *get_phys_addr(void* virtual_address){
    volatile uint32_t pd_index = ((uint32_t)virtual_address)>>22;
    volatile uint32_t pt_index = ((uint32_t)virtual_address>>12) &0x3ff;
    volatile struct page_directory_entry *pd = (struct page_directory_entry*)index_to_addr(1023,1023,0);
    if((pd[pd_index].flags&1)==0){
        //PDE not present
        return -1;
    }
    volatile struct page_directory_entry *pt = (struct page_directory_entry*)index_to_addr(1023,pd_index,0);
    if((pt[pt_index].flags&1)==0){
        return -1;
    }
    return (pt[pt_index].address_high<<16)|(pt[pt_index].address_low<<8)|((uint32_t)virtual_address&0xfff);
}