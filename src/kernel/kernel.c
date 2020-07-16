#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "../drivers/keyboard.h"
#include <stdio.h>
#include "kernel_globals.h"
#include "kernel.h"
#include "timer.h"
#include "bin/bin.h"
#include "interrupts/interrupts.h"

void kernel_main(){
    stdin.writeable=false;
    stdin.readable=false;
    set_cursor(0);
    clear_screen();
    initialize_gdt();
    unmap_identity();
    initialize_idt();
    register_handlers();
    refresh_bitmap();
    init_timer();
    timer_countdown(0);
    keyboard_init();
    uint32_t *x = malloc(4);
    void *y = malloc(16);
    void *y2 = malloc(16);
    uint32_t *z = malloc(4);
    *x = 0xcafebabe;
    *z=0xdeadbeef;
    hexdump(_kernel_end,20);
    printf("\n");
    free(y);
    free(y2);
    uint32_t *a = malloc(4);
    *a=0xcafebeef;
    printf("%x, %x, %x\n",_kernel_end,*x,x);
    hexdump(_kernel_end,20);
    printf("\n");
    while(1){
        char* buf = malloc(8);
        hexdump(_kernel_end,20);
        gets(buf);
    }
    while(1){
        asm("hlt");
    }
}

void unmap_identity(){
    int *boot_page_ptr = &kernel_page_directory[0];
    *boot_page_ptr = 0;
    asm("mov %cr3,%eax\n" "mov %eax,%cr3");
}