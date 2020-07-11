#include <stdint.h>
#include "ports.h"
#include "../libc/string/string.h"
#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_RAM 0xc00b8000
void vga_scroll();
void clear_row();

uint16_t get_cursor(){
    uint16_t cursor;
    port_write_byte(0x3d4, 14); //request high byte of cursor pos
    cursor = port_read_byte(0x3d5)<<8; //read the high byte
    port_write_byte(0x3d4,15); //get low byte
    cursor+=port_read_byte(0x3d5); //read low byte
    return cursor;
}
void set_cursor(uint16_t cursor){
    if(cursor>=VGA_WIDTH*VGA_HEIGHT){
        vga_scroll();
        cursor-=VGA_WIDTH;
    }
    port_write_byte(0x3d4, 14); //request high byte of cursor pos
    port_write_byte(0x3d5,(uint8_t)((cursor>>8)&0xff)); //set high byte
    port_write_byte(0x3d4,15); //get low byte
    port_write_byte(0x3d5,(uint8_t)(cursor&0xff));//set low byte
}

void vga_scroll(){
    uint8_t buf[VGA_HEIGHT*VGA_WIDTH*2];
    memcpy(buf,(void*)VGA_RAM,sizeof buf); //store vram into buffer
    memcpy((void*)VGA_RAM,buf+(VGA_WIDTH*2),(sizeof buf)-(VGA_WIDTH*2)); //write the buffer offset by one line
    set_cursor(get_cursor()-VGA_WIDTH);
    //clear last line
    clear_row(VGA_HEIGHT-1);
}
void write_char_at_cursor(char text,uint8_t color){
    uint8_t *vga = (uint8_t*)VGA_RAM;
    uint16_t cursor = get_cursor();
    uint32_t vga_offset = cursor *2;
    vga[vga_offset] = text;
    vga[vga_offset+1]=color;
}

void write_char_at_location(char text,uint8_t color,uint16_t position){
    uint8_t *vga = (uint8_t*)VGA_RAM;
    uint32_t vga_offset = position *2;
    vga[vga_offset] = text;
    vga[vga_offset+1]=color;
}
void clear_screen(){
    uint16_t i;
    for (i=0;i<VGA_WIDTH*VGA_HEIGHT;i++){
        write_char_at_location(' ',0x0f,i);
    }
}
void clear_row(int row){
    uint16_t i;
    for (i=0;i<VGA_WIDTH;i++){
        write_char_at_location(' ',0x0f,i+(VGA_WIDTH*row));
    }
}