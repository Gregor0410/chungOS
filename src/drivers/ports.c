#include <stdint.h>

void port_write_byte(uint16_t port ,uint8_t data){
    __asm__("out %%al,%%dx" : :"a" (data),"d" (port));
}

uint8_t port_read_byte(uint16_t port){
    uint8_t result;
    __asm__("in %%dx,%%al":"=a" (result): "d"(port));
    return result;
}

void port_write_word(uint16_t port ,uint8_t data){
    __asm__("out %%ax,%%dx" : :"a" (data),"d" (port));
}

uint16_t port_read_word(uint16_t port){
    uint16_t result;
    __asm__("in %%dx,%%ax":"=a" (result): "d"(port));
    return result;
}