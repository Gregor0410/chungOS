#include "../kernel/interrupts/interrupts.h"
#include "../kernel/kernel_globals.h"
#include "ports.h"
#include <stdbool.h>
#include "keyboard.h"
#define DATA_PORT 0x60
#define COMMAND_PORT 0x64

char* scancode_table[] ={ //scancode set 1
    "null",
    "escape", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=", "backspace",
    "tab", "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "[", "]", "enter", "left control",
    "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`",
    "left shift", "#", "Z", "X", "C", "V", "B", "N", "M",",", ".", "/", "right shift",
    "*", "left alt", "space", "CapsLock",
    "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "NumberLock", "ScrollLock",
    "7", "8", "9", "-", "4", "5", "6", "+", "1", "2", "3", "0", ".", "null", "null", "\\",
    "F11", "F12"
};
uint8_t keycodes[] = { //lookup table to convert from scancode set 1 to keycode
    //bits 4-0 =column bits 5-7=row 
    0,
    0,33,34,35,36,37,38,39,40,41,42,43,44,45,
    64,65,66,67,68,69,70,71,72,73,74,75,76,77,160,
    97,98,99,100,101,102,103,104,105,106,107,32,
    128,108,130,131,132,133,134,135,136,137,138,139,140,
    51,162,163,96,
    1,2,3,4,5,6,7,8,9,10,49,14,
    81,82,83,52,109,110,111,84,142,143,144,171,172,0,0,129,11,12
};

char* keycode_table[] = { //lookup table to convert from keycode to key name
    "ESC","F1","F2","F3","F4","F5","F6","F7","F8","F9","F10","F11","F12","Print Screen","Scroll Lock","Pause Break","Stop","Back","Play","Next","","","","","","","","","","","","",
    "`","1","2","3","4","5","6","7","8","9","0","-","=","Backspace","Insert","Home","Page Up","Num Lock","/","*","-","","","","","","","","","","","",
    "Tab","q","w","e","r","t","y","u","i","o","p","[","]","Enter","Delete","End","Page Down","7","8","9","+","","","","","","","","","","","",
    "Caps Lock","a","s","d","f","g","h","j","k","l",";","'","#","4","5","6","","","","","","","","","","","","","","","","",
    "Left Shift","\\","z","x","c","v","b","n","m",",",".","/","Right Shift","Up","1","2","3","Enter","","","","","","","","","","","","","","",
    "Left Control","Left GUI","Left Alt"," ","Alt Gr","Right GUI","Context Menu","Right Control","Left","Down","Right","0","."
};
char keycode_char_table[]= {//lookup table to convert from keycode to char
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    '`','1','2','3','4','5','6','7','8','9','0','-','=',8,0,0,0,0,'/','*','-',0,0,0,0,0,0,0,0,0,0,0,
    0,'q','w','e','r','t','y','u','i','o','p','[',']','\n',0,0,0,'7','8','9','+',0,0,0,0,0,0,0,0,0,0,0,
    0,'a','s','d','f','g','h','j','k','l',';','\'','#','4','5','6',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,'\\','z','x','c','v','b','n','m',',','.','/',0,0,'1','2','3','\n',0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,' ',0,0,0,0,0,0,0,'0','.'
};
char keycode_char_table_shift[]= {//lookup table to convert from keycode to char when holding shift
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    '¬','!','"','£','$','%','^','&','*','(',')','_','+',0,0,0,0,0,'/','*','-',0,0,0,0,0,0,0,0,0,0,0,
    0,'Q','W','E','R','T','Y','U','I','O','P','{','}',0,0,0,0,'7','8','9','+',0,0,0,0,0,0,0,0,0,0,0,
    0,'A','S','D','F','G','H','J','K','L',':','@','~','4','5','6',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,'|','Z','X','C','V','B','N','M','<','>','?',0,0,'1','2','3',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,'0','.'
};

bool pressed_keys[256];
bool extended = false; //set to true when code 0xE0 is sent

void keyboard_handler(registers_t r){
    int scancode = port_read_byte(0x60);
    if(scancode<0x80){
        if(extended){
            //printf("Extended Scancode: %x\nKeycode: %x\nKey: %s\n",scancode,keycodes[scancode],scancode_table[scancode]);
            extended=false;
        }else{
            uint8_t keycode = keycodes[scancode];
            pressed_keys[keycode] = true;
            if(pressed_keys[K_LEFT_SHIFT]||pressed_keys[K_RIGHT_SHIFT]){
                char c = keycode_char_table_shift[keycode];
                if(c!=0){
                    //If character is writable
                    write_stdin(c);
                }
            }else{
                char c = keycode_char_table[keycode];
                if(c!=0){
                    //If character is writable
                    write_stdin(c);
                }
            }
        }
    }else if(scancode==0xE0){
        extended=true;
    }else{
        //key up
        if(!extended){
            uint8_t keycode = keycodes[scancode-0x80];
            pressed_keys[keycode]=false;
        }
        extended=false;
    }
}

void write_stdin(char c){
    if(stdin.writeable){
        stdin.character = c;
        stdin.readable = true;
        stdin.writeable = false;
    }
}

uint8_t keyboard_send_command(uint8_t command){
    asm("cli"); //avoid the interrupt handler eating the data
    while((port_read_byte(COMMAND_PORT)&0b10)>0);
    port_write_byte(DATA_PORT,command);
    while((port_read_byte(COMMAND_PORT)&0b1)==0);
    uint8_t response = port_read_byte(DATA_PORT);
    asm("sti"); //enable interrupts my final message
    return response;
}

uint8_t keyboard_send_data_command(uint8_t command, uint8_t data){
    asm("cli"); //avoid the interrupt handler eating the data
    while((port_read_byte(COMMAND_PORT)&0b10)>0);
    port_write_byte(DATA_PORT,command);
    while((port_read_byte(COMMAND_PORT)&0b10)>0);
    port_write_byte(DATA_PORT,data);
    while((port_read_byte(COMMAND_PORT)&0b1)==0);
    uint8_t response = port_read_byte(DATA_PORT);
    asm("sti"); //enable interrupts my final message
    return response;
}

void keyboard_init(){
    register_handler(33,keyboard_handler);
}

