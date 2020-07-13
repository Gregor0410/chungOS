#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "../libc/string/string.h"
#include "../drivers/keyboard.h"
#include "../libc/stdio/stdio.h"
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
    printf("%x\n",_kernel_end);
    while(1){
        char buf[80];
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