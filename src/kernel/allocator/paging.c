#include "allocator.h"
#include <stdbool.h>
#define index_to_addr(pd_index,pt_index,p_index) ((pd_index <<22)|(pt_index<<12)|p_index) 

void refresh_bitmap(){
    //iterates through virtual memory and sets the corresponding bits of the mapped physical addresses in the bitmap
    prev_pointer=0;
    for(uint32_t page=0;page<=0xfffff;page++){
        uint32_t phys_addr = (uint32_t)get_phys_addr(page*0x1000);
        if(phys_addr!=-1){
            //virtual address is mapped
            //set the corresponding bit
            uint32_t phys_page = ((phys_addr>>12)&0xfff);
            memory_bitmap[phys_page/32] |= 1<<(phys_page%32);
        }
    }
}

void *get_free_page(){
    for(uint32_t i=prev_pointer;i<NUM_PAGES;i++){
        if(((memory_bitmap[i/32])&(1<<(i%32)))<1){
            //page is free
            prev_pointer=i-1;
            return (void *)(i<<12);
        }
    }
    return (void *)-1;
}


bool pde_present(uint32_t pd_index){
    struct page_directory_entry *pd = (struct page_directory_entry*)index_to_addr(1023,1023,0);
    return (pd[pd_index].flags&1);
}
bool pte_present(uint32_t pd_index, uint32_t pt_index){
    struct page_directory_entry *pd = (struct page_directory_entry*)index_to_addr(1023,1023,0);
    if((pd[pd_index].flags&1)==0){
        //PDE not present
        return false;
    }
    struct page_directory_entry *pt = (struct page_directory_entry*)index_to_addr(1023,pd_index,0);
    return (pt[pt_index].flags&1);
}

void *get_phys_addr(void* virtual_address){
    uint32_t pd_index = ((uint32_t)virtual_address)>>22;
    uint32_t pt_index = ((uint32_t)virtual_address>>12) &0x3ff;
    struct page_directory_entry *pd = (struct page_directory_entry*)index_to_addr(1023,1023,0);
    if((pd[pd_index].flags&1)==0){
        //PDE not present
        return -1;
    }
    struct page_directory_entry *pt = (struct page_directory_entry*)index_to_addr(1023,pd_index,0);
    if((pt[pt_index].flags&1)==0){
        //PTE not present
        return -1;
    }
    return (pt[pt_index].address_high<<16)|(pt[pt_index].address_low<<8)|((uint32_t)virtual_address&0xfff);
}