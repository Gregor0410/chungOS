#include <stdio.h>

void hexdump(int *address,int len){
    int i;
    for(i=0;i<len;i+=4){
        printf("%x: %x %x %x %x\n",address+i,address[i],address[i+1],address[i+2],address[i+3]);
    }
}