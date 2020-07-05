#include "../drivers/ports.h"
#include "interrupts/interrupts.h"
#include "timer.h"
#include <stdint.h>
uint32_t overflow_register=0; //used to allow countdowns greater than 0xffff PIT cycles
void timer_handler(registers_t r){
    if(overflow_register==0){
        printf("Timer\n");
    }else {
        //reset count
        port_write_byte(0x40,0xff);
        port_write_byte(0x40,0xff);
        overflow_register--;
    }
}



void init_timer() {
    register_handler(32,timer_handler);
}

void timer_countdown(double time){
    //set timer to interrupt after time nanoseconds
    time *= 0.00119318; //convert from nanoseconds to number of pit oscillations
    uint32_t count = (uint32_t)time;
    if(count >0xffff){
        overflow_register = count/0xffff;
        count = count % 0xffff;
    }
    uint8_t low = (uint8_t)(count&0xff);
    uint8_t high = (uint8_t)((count >>8)&0xff);
    port_write_byte(0x43,TIMER_COUNTDOWN);
    port_write_byte(0x40, low);
    port_write_byte(0x40, high);
}

void timer_square_wave(uint32_t frequency){
    /* Get the PIT value: hardware clock at 1193180 Hz */
    uint32_t divisor = 1193180 / frequency;
    uint8_t low  = (uint8_t)(divisor & 0xFF);
    uint8_t high = (uint8_t)( (divisor >> 8) & 0xFF);
    /* Send the command */
    port_write_byte(0x43, TIMER_SQUARE_WAVE); /* Command port */
    port_write_byte(0x40, low);
    port_write_byte(0x40, high);
}