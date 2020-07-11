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
    init_timer();
    timer_countdown(0);
    keyboard_init();
<<<<<<< HEAD
    printf("%x\n",*(int*)0xffc00000);
=======
    printf("%x\n",*(int *)&boot_page_directory[1023]);
    printf("Physical address of kernel_main is: %x\n",get_phys_addr(0x00000000));
>>>>>>> Paging
    while(1){
        char buf[80];
        gets(buf);
    }
    while(1){
        asm("hlt");
    }
}

void unmap_identity(){
    int *boot_page_ptr = &boot_page_directory[0];
    *boot_page_ptr = 0;
    asm("mov %cr3,%eax\n" "mov %eax,%cr3");
}