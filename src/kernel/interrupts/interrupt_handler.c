#include "../kernel.h"
#include "../../libc/stdio/stdio.h"
#include "../../drivers/ports.h"
#include "interrupts.h"

isr_t handlers[256];

void isr_handler(registers_t r){
    printf("Interrupt no %x, error code %x\n",r.int_no,r.err_code);
    if(r.int_no==0xd){
        printf("EIP: %x\nSS: %x\n",r.eip,r.ss);
        
    }
}
void register_handler(int no,isr_t handler){
    handlers[no] = handler;
}
void irq_handler(registers_t r) {
    /* After every interrupt we need to send an EOI to the PICs
     * or they will not send another interrupt again */
    if (r.int_no >= 40) port_write_byte(0xA0, 0x20); /* slave */
    port_write_byte(0x20, 0x20); /* master */
    handlers[r.int_no](r);
}