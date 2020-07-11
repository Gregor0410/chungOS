#include "../kernel.h"
#include "../../libc/stdio/stdio.h"
#include "../../drivers/ports.h"
#include "interrupts.h"


void isr_handler(registers_t r){
    handlers[r.int_no](r);
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

void default_handler(registers_t r){
    printf("Int no %x\n",r.int_no);
    printf("Error code: %x\n",r.err_code);
    printf("EIP: %x,CS: %x, DS: %x",r.eip,r.cs,r.ds);
    asm("hlt");
}