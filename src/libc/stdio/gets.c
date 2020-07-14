#include "../../kernel/kernel_globals.h"
#include "../../drivers/vga_text.h"
#include "../include/stdio.h"
char *gets(char *str){
    char read_character=0;
    int i = 0;
    while(read_character!='\n'){
        stdin.writeable = true;
        while(stdin.readable==0){ //wait until a character has been written
            asm("hlt");
        }
        read_character=stdin.character;
        if(read_character==0x8){
            //backspace pressed
            if(i>0){
                //delete previous character if there is one
                set_cursor(get_cursor()-1);
                write_char_at_cursor(' ',0x0f);
                i--;
            }
        }else{
        putchar(read_character);
        str[i]=read_character;
        i++;
        }
        stdin.readable=false;
    }
    str[i-1]=0; //replace the newline character with null terminator.
    return str;
}