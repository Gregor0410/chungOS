#ifndef KERNEL_H
#define KERNEL_H
#include <stdint.h>
struct descriptor{
    uint16_t size;
    uint32_t address; 
}__attribute__((packed));
struct page_directory_entry{
    uint8_t flags;
    uint8_t address_low;
    uint16_t address_high;
};
struct gdt_entry{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_mid;
    uint8_t access_byte;
    uint8_t limit_high_and_flags;
    uint8_t base_high;
}__attribute__((packed));
struct gdt_abstract{
    uint32_t base;
    uint32_t limit;
    uint8_t type; 
};
struct idt_entry{
    uint16_t offset_1;
    uint16_t selector;
    uint8_t zero;
    uint8_t type_attr;
    uint16_t offset_2;
};
struct idt_abstract{
    uint32_t offset;
    uint8_t type;
    uint16_t gdt_offset;
};
struct tss{
    //Task state segment data structure
    uint16_t link;
    uint16_t res;
    uint32_t esp0;
    uint16_t ss0;
    uint16_t res1;
    uint32_t esp1;
    uint16_t ss1;
    uint16_t res2;
    uint32_t esp2;
    uint16_t ss2;
    uint16_t res3;
    uint32_t cr3;
    uint32_t eip;
    uint32_t eflags;
    uint32_t eax;
    uint32_t ecx;
    uint32_t edx;
    uint32_t ebx;
    uint32_t esp;
    uint32_t ebp;
    uint32_t esi;
    uint32_t edi;
    uint16_t es;
    uint16_t res4;
    uint16_t cs;
    uint16_t res5;
    uint16_t ss;
    uint16_t res6;
    uint16_t ds;
    uint16_t res7;
    uint16_t fs;
    uint16_t res8;
    uint16_t gs;
    uint16_t res9;
    uint16_t ldtr;
    uint32_t res10;
    uint16_t iopb_offset;
};
typedef struct{
   uint32_t ds; /* Data segment selector */
   uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; /* Pushed by pusha. */
   uint32_t int_no, err_code; /* Interrupt number and error code (if applicable) */
   uint32_t eip, cs, eflags, useresp, ss; /* Pushed by the processor automatically */
} registers_t;
void initialize_gdt();
void initialize_idt();
void register_handlers();
void load_gdt(struct gdt_entry *GDT,uint16_t size);
void load_idt(struct idt_entry* IDT,uint16_t size);
struct tss TSS;
struct idt_entry IDT[255];
struct gdt_entry GDT[4];
struct descriptor gdt_descriptor;
struct page_directory_entry kernel_page_directory[1024];
extern uint32_t _kernel_start[];
extern uint32_t _kernel_end[];
#endif