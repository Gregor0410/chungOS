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
    set_cursor(0);
    clear_screen();
    initialize_gdt();
    initialize_idt();
    init_timer();
    keyboard_init();
    printf("Timer Initialised\n");
    timer_countdown(1e9);
    while(1){
        asm("hlt");
    }
}