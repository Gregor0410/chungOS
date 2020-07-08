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

void main(){
    stdin.writeable=false;
    stdin.readable=false;
    set_cursor(0);
    clear_screen();
    initialize_gdt();
    initialize_idt();
    init_timer();
    timer_countdown(0);
    keyboard_init();
    while(1){
        char buf[80];
        gets(buf);
    }
    while(1){
        asm("hlt");
    }
}