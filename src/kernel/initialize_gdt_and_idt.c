#include <stdint.h>
#include <stdbool.h>
#include "kernel.h"
#include "bin/bin.h"
#include "../drivers/ports.h"
#include "interrupts/interrupts.h"
void encode_gdt_entry(struct gdt_entry *target, struct gdt_abstract source){
    // Check the limit to make sure that it can be encoded
    if (source.limit > 65536) {
        // Adjust granularity if required
        source.limit = source.limit >> 12;
        target->limit_high_and_flags = 0xC0;
    } else {
        target->limit_high_and_flags = 0x40;
    }
 
    // Encode the limit
    target->limit_low = (source.limit & 0xFF) | ((source.limit >> 8) & 0xFF);
    target->limit_high_and_flags |= (source.limit >> 16) & 0xF;
 
    // Encode the base 
    target->base_low = (source.base & 0xFF) | ((source.base >> 8) & 0xFF);
    target->base_mid = (source.base >> 16) & 0xFF;
    target->base_high = (source.base >> 24) & 0xFF;
 
    // And... Type
    target->access_byte = source.type;
}

void encode_idt_entry(struct idt_entry *target, struct idt_abstract source){
    //set offset
    target->offset_1 = source.offset &0xffff;
    target->offset_2 = (source.offset >> 16)&0xffff;
    //set type
    target->type_attr = source.type;
    target->zero = 0;
    //selector
    target->selector = source.gdt_offset;
}



void initialize_gdt(){
    struct gdt_entry *GDT = GDT_LOCATION;
    struct gdt_abstract null_descriptor = {.base=0x0,.limit=0x0, .type=0x0};
    struct gdt_abstract code_seg = {.base=0x0,.limit=0xffffffff, .type=0x9a};
    struct gdt_abstract data_seg = {.base=0x0,.limit=0xffffffff, .type=0x92};
    struct gdt_abstract tss_seg = {.base=&TSS, .limit=sizeof(TSS), .type=0x89};
    encode_gdt_entry(&GDT[0],null_descriptor);
    encode_gdt_entry(&GDT[1],code_seg);
    encode_gdt_entry(&GDT[2],data_seg);
    encode_gdt_entry(&GDT[3],tss_seg);
    load_gdt(GDT,(4*8)-1);
}

void test_int_c(){
    printf("Interrupt\n");
}
void initialize_idt(){
    struct idt_entry *IDT = IDT_LOCATION;
    encode_idt_entry(&IDT[0],(struct idt_abstract){.offset=&isr0,.type=0x8e,.gdt_offset=0x08});
    encode_idt_entry(&IDT[1],(struct idt_abstract){.offset=&isr1,.type=0x8e,.gdt_offset=0x08});
    encode_idt_entry(&IDT[2],(struct idt_abstract){.offset=&isr2,.type=0x8e,.gdt_offset=0x08});
    encode_idt_entry(&IDT[3],(struct idt_abstract){.offset=&isr3,.type=0x8e,.gdt_offset=0x08});
    encode_idt_entry(&IDT[4],(struct idt_abstract){.offset=&isr4,.type=0x8e,.gdt_offset=0x08});
    encode_idt_entry(&IDT[5],(struct idt_abstract){.offset=&isr5,.type=0x8e,.gdt_offset=0x08});
    encode_idt_entry(&IDT[6],(struct idt_abstract){.offset=&isr6,.type=0x8e,.gdt_offset=0x08});
    encode_idt_entry(&IDT[7],(struct idt_abstract){.offset=&isr7,.type=0x8e,.gdt_offset=0x08});
    encode_idt_entry(&IDT[8],(struct idt_abstract){.offset=&isr8,.type=0x8e,.gdt_offset=0x08});
    encode_idt_entry(&IDT[9],(struct idt_abstract){.offset=&isr9,.type=0x8e,.gdt_offset=0x08});
    encode_idt_entry(&IDT[10],(struct idt_abstract){.offset=&isr10,.type=0x8e,.gdt_offset=0x08});
    encode_idt_entry(&IDT[11],(struct idt_abstract){.offset=&isr11,.type=0x8e,.gdt_offset=0x08});
    encode_idt_entry(&IDT[12],(struct idt_abstract){.offset=&isr12,.type=0x8e,.gdt_offset=0x08});
    encode_idt_entry(&IDT[13],(struct idt_abstract){.offset=&isr13,.type=0x8e,.gdt_offset=0x08});
    encode_idt_entry(&IDT[14],(struct idt_abstract){.offset=&isr14,.type=0x8e,.gdt_offset=0x08});
    encode_idt_entry(&IDT[15],(struct idt_abstract){.offset=&isr15,.type=0x8e,.gdt_offset=0x08});
    encode_idt_entry(&IDT[16],(struct idt_abstract){.offset=&isr16,.type=0x8e,.gdt_offset=0x08});
    encode_idt_entry(&IDT[17],(struct idt_abstract){.offset=&isr17,.type=0x8e,.gdt_offset=0x08});
    encode_idt_entry(&IDT[18],(struct idt_abstract){.offset=&isr18,.type=0x8e,.gdt_offset=0x08});
    encode_idt_entry(&IDT[19],(struct idt_abstract){.offset=&isr19,.type=0x8e,.gdt_offset=0x08});
    encode_idt_entry(&IDT[20],(struct idt_abstract){.offset=&isr20,.type=0x8e,.gdt_offset=0x08});
    encode_idt_entry(&IDT[21],(struct idt_abstract){.offset=&isr21,.type=0x8e,.gdt_offset=0x08});
    encode_idt_entry(&IDT[22],(struct idt_abstract){.offset=&isr22,.type=0x8e,.gdt_offset=0x08});
    encode_idt_entry(&IDT[23],(struct idt_abstract){.offset=&isr23,.type=0x8e,.gdt_offset=0x08});
    encode_idt_entry(&IDT[24],(struct idt_abstract){.offset=&isr24,.type=0x8e,.gdt_offset=0x08});
    encode_idt_entry(&IDT[25],(struct idt_abstract){.offset=&isr25,.type=0x8e,.gdt_offset=0x08});
    encode_idt_entry(&IDT[26],(struct idt_abstract){.offset=&isr26,.type=0x8e,.gdt_offset=0x08});
    encode_idt_entry(&IDT[27],(struct idt_abstract){.offset=&isr27,.type=0x8e,.gdt_offset=0x08});
    encode_idt_entry(&IDT[28],(struct idt_abstract){.offset=&isr28,.type=0x8e,.gdt_offset=0x08});
    encode_idt_entry(&IDT[29],(struct idt_abstract){.offset=&isr29,.type=0x8e,.gdt_offset=0x08});
    encode_idt_entry(&IDT[30],(struct idt_abstract){.offset=&isr30,.type=0x8e,.gdt_offset=0x08});
    encode_idt_entry(&IDT[31],(struct idt_abstract){.offset=&isr31,.type=0x8e,.gdt_offset=0x08});

    //remap PIC
    port_write_byte(0x20, 0x11);
    port_write_byte(0xA0, 0x11);
    port_write_byte(0x21, 0x20);
    port_write_byte(0xA1, 0x28);
    port_write_byte(0x21, 0x04);
    port_write_byte(0xA1, 0x02);
    port_write_byte(0x21, 0x01);
    port_write_byte(0xA1, 0x01);
    port_write_byte(0x21, 0x0);
    port_write_byte(0xA1, 0x0);

    encode_idt_entry(&IDT[32],(struct idt_abstract){.offset=&irq0,.type=0x8e,.gdt_offset=0x08});
    encode_idt_entry(&IDT[33],(struct idt_abstract){.offset=&irq1,.type=0x8e,.gdt_offset=0x08});
    encode_idt_entry(&IDT[34],(struct idt_abstract){.offset=&irq2,.type=0x8e,.gdt_offset=0x08});
    encode_idt_entry(&IDT[35],(struct idt_abstract){.offset=&irq3,.type=0x8e,.gdt_offset=0x08});
    encode_idt_entry(&IDT[36],(struct idt_abstract){.offset=&irq4,.type=0x8e,.gdt_offset=0x08});
    encode_idt_entry(&IDT[37],(struct idt_abstract){.offset=&irq5,.type=0x8e,.gdt_offset=0x08});
    encode_idt_entry(&IDT[38],(struct idt_abstract){.offset=&irq6,.type=0x8e,.gdt_offset=0x08});
    encode_idt_entry(&IDT[39],(struct idt_abstract){.offset=&irq7,.type=0x8e,.gdt_offset=0x08});
    encode_idt_entry(&IDT[40],(struct idt_abstract){.offset=&irq8,.type=0x8e,.gdt_offset=0x08});
    encode_idt_entry(&IDT[41],(struct idt_abstract){.offset=&irq9,.type=0x8e,.gdt_offset=0x08});
    encode_idt_entry(&IDT[42],(struct idt_abstract){.offset=&irq10,.type=0x8e,.gdt_offset=0x08});
    encode_idt_entry(&IDT[43],(struct idt_abstract){.offset=&irq11,.type=0x8e,.gdt_offset=0x08});
    encode_idt_entry(&IDT[44],(struct idt_abstract){.offset=&irq12,.type=0x8e,.gdt_offset=0x08});
    encode_idt_entry(&IDT[45],(struct idt_abstract){.offset=&irq13,.type=0x8e,.gdt_offset=0x08});
    encode_idt_entry(&IDT[46],(struct idt_abstract){.offset=&irq14,.type=0x8e,.gdt_offset=0x08});
    encode_idt_entry(&IDT[47],(struct idt_abstract){.offset=&irq15,.type=0x8e,.gdt_offset=0x08});
    load_idt(IDT,(NO_INTERRUPTS*8)-1);
}