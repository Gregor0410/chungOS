#include "stdio.h"
#include <stdint.h>
#include <stdarg.h>
#include "../string/string.h"
#include <stddef.h>

char* hex_to_str(int hex, char* dest){
    char str[] = "0x00000000";
    for(int i=0;i<8;i++){
        char digit = (hex&0xf)+0x30;
        if(digit>0x39){
            //digit is more than hex 9
            digit+=0x7; //add 7 to move into letters
        }
        str[9-i]=digit;
        hex=hex>>4;
    }
    return strcpy(dest,str);
}
char* dec_to_str(int dec,char* dest){
    if(dec==0)return strcpy(dest,"0");
    char str[]="0000000000";
    int i;
    for(i=9;dec>0;i--){
        str[i]=(dec%10)+0x30;
        dec /= 10;
    }
    return strcpy(dest,str+i+1);
}
int print(char* str,size_t len){
    size_t i;
    for (i=0;i<len;i++){
        putchar(str[i]);
    }
    return (int) len;
}

int printf(const char *format, ...){
    va_list parameters;
    va_start(parameters,format);
    int written = 0;
    while(*format != 0){
        if(format[0]=='%'){
            if(format[1]=='s'){
                char* str = va_arg(parameters,char*);
                written+=print(str,strlen(str));
                format+=2; //dont write the format character
            }else if(format[1]=='x'){
                int hex = va_arg(parameters,int);
                char buf[11];
                char* str = hex_to_str(hex,buf);
                written+=print(str,strlen(str));
                format+=2; //dont write the format character
            }else if(format[1]=='d'){
                int dec = va_arg(parameters,int);
                char buf[11];
                char* str = dec_to_str(dec,buf);
                written+=print(str,strlen(str));
                format+=2; //dont write the format character
            }else{
                //count and print the characters until the next % or until end of string
                putchar(*format);
                format++;
                written++;
                int i;
                for(i=0;format[i]!='%'&&format[i]!=0;i++) putchar(format[i]);
                written+=i;
                format+=i;
            }
        }else{
            //count and print the characters until the next % or until end of string
            putchar(*format);
            format++;
            written++;
            int i;
            for(i=0;format[i]!='%'&&format[i]!=0;i++) putchar(format[i]);
            written+=i;
            format+=i;
        }
    }
    return written;
}