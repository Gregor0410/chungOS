#include <stddef.h>
#include <stdbool.h>
#include "../include/stdio.h"
#include "../include/stdlib.h"
#include "../../kernel/kernel.h"
void* brk = _kernel_end;
header_t *head,*tail;
header_t *get_free_block(size_t size);
void merge_free_blocks();
//the size value in the header struct is a 31 wide bitfield, so when doing arithemtic, the value must be shifted left one bit

void* malloc(size_t size){
    size += size&1; //round up to next even number if odd
    header_t *header;
    header=get_free_block(size);
    if(header){
        return (void *)(header+1);
    }
    //increment brk
    header=brk;
    brk=((uint32_t)brk)+size+sizeof(header_t);
    header->free=false;
    header->size=size>>1;
    header->next=0;
    if(!head){
        head=header;
    }
    if(tail){
        tail->next=header;
    }
    tail=header;
    return (void *)(header+1);
}

void free(void *ptr){
    header_t *header = ptr-sizeof(header_t);
    header->free = true;
}


header_t *get_free_block(size_t size){
    header_t* curr = head;
    while(curr){
        if(curr->free){
            merge_free_blocks(curr);
            if((curr->size<<1)>=size){
                if((curr->size<<1)-size >= sizeof(header_t)+4){
                    //insert new header in the extra space if there is room for new block.
                    header_t *new_header = ((uint32_t)curr)+size+sizeof(header_t);
                    new_header->next = curr->next;
                    new_header->size = ((curr->size<<1)-size-sizeof(header_t))>>1;
                    new_header->free = true;
                    curr->next = new_header;
                    curr->size=size>>1;
                }
                curr->free = false;
                return curr;
            }
        }
        curr = curr->next;
    }
    return 0;
}

void merge_free_blocks(header_t *header){
    if(header==tail)return;
    header_t *curr;
    header_t *prev=header;
    for(curr=header->next;curr->next&&curr->free;curr=curr->next){
        header->size+=curr->size+(sizeof(header_t)>>1);
        prev=curr;
    }
    header->next = prev->next;
    if(header->next==0){
        tail=header;
    }
}