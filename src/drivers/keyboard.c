#include "../kernel/interrupts/interrupts.h"
#include "ports.h"
char* scancodes[] = {
    "NULL","ESC",
    "1","2","3","4","5","6","7","8","9","0","-","=","BACKSPACE",
    "TAB","q","w","e","r","t","y","u","i","o","p","[","]","ENTER","LEFT CTRL",
    "a","s","d","f","g","h","j","k","l",";","'","`",
    "LEFT SHIFT","\\","z","x","c","v","b","n","m",",",".","/","RIGHT SHIFT"
};
void keyboard_handler(registers_t r){
    int keycode = port_read_byte(0x60);
    if(keycode<sizeof(scancodes)/sizeof(char*)){
        printf("Key: %s\n",scancodes[keycode]);
    }
}
void keyboard_init(){
    register_handler(33,keyboard_handler);
}