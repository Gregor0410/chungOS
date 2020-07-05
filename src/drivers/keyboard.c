#include "../kernel/interrupts/interrupts.h"
#include "../kernel/kernel_globals.h"
#include "ports.h"
#include <stdbool.h>
bool shift=false;
bool caps_lock= false;
bool control = false;
char* scancodes[] = {
    "NULL","ESC",
    "1","2","3","4","5","6","7","8","9","0","-","=","BACKSPACE",
    "TAB","q","w","e","r","t","y","u","i","o","p","[","]","ENTER","LEFT CTRL",
    "a","s","d","f","g","h","j","k","l",";","'","`",
    "LEFT SHIFT","\\","z","x","c","v","b","n","m",",",".","/","RIGHT SHIFT",
    "*","LEFT ALT"," "
};
void keyboard_handler(registers_t r){
    int keycode = port_read_byte(0x60);
    if(keycode<sizeof(scancodes)/sizeof(char*)){
        switch (keycode)
        {
        case 1: //ESC
            break;
        case 0xe: //BACKSPACE
            write_stdin(0x8); //write backspace character
            break;
        case 0xf: //TAB
            break;
        case 0x1c: //ENTER
            write_stdin('\n');
            break;
        case 0x2a: //Shift
            shift=true;
            break;
        case 0x36:
            shift=true;
            break;
        default:
            if(shift){
                write_stdin(scancodes[keycode][0]-0x20);
            }else{
                write_stdin(scancodes[keycode][0]);
            }
            break;
        }
    }
    if(keycode>0x80){
        switch(keycode){
            case 0xAA:
                shift=false;
                break;
            case 0xb6:
                shift=false;
                break;
            default:
                break; 
        }
    }
}
void write_stdin(char c){
    if(stdin.writeable){
        stdin.character = c;
        stdin.readable = true;
        stdin.writeable = false;
    }
}
void keyboard_init(){
    register_handler(33,keyboard_handler);
}