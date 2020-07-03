#ifndef TIMER_H
#define TIMER_H
#include <stdint.h>
#define TIMER_COUNTDOWN 0b00110000 //command to set interrupt on terminal count
#define TIMER_SQUARE_WAVE 0b00110110 //command to set square wave generator
void init_timer();
void timer_countdown(double time);
void timer_square_wave(uint32_t frequency);
#endif