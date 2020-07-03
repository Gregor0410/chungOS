#include <stdint.h>
#include "../../drivers/vga_text.h"
#include "../../kernel/kernel_globals.h"
void puts(char* string){
    int i;
    uint16_t cursor = get_cursor();
    for(i=0;string[i]!=0x00;i++){  //write string
        if(cursor%VGA_WIDTH==0){
            set_cursor(cursor); //update cursor every time a new line is hit
            cursor=get_cursor(); //get cursor again in case the driver changed it
        }
        if(string[i]=='\n'){
            cursor+=VGA_WIDTH-(cursor%VGA_WIDTH); 
            set_cursor(cursor); //new line
            cursor=get_cursor();//get cursor again in case the driver changed it
        }else{
            write_char_at_location(string[i],0x0f,cursor);
            cursor++;
        }
    }
    cursor+=VGA_WIDTH-(cursor%VGA_WIDTH); 
    set_cursor(cursor); //new line
}
int putchar(char c){
    uint16_t cursor = get_cursor();
    if (c=='\n'){
        cursor += VGA_WIDTH - (cursor%VGA_WIDTH);
        set_cursor(cursor);
        return (int) c;
    }
    write_char_at_location(c,0x0f,cursor);
    cursor++;
    set_cursor(cursor); //increment cursor
    return (int) c;
}