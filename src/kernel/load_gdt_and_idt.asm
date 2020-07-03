global load_gdt
global load_idt
gdtr:
    dw 0
    dd 0

load_gdt:
    MOV   EAX, [esp + 4]
    MOV   [gdtr + 2], EAX
    MOV   AX, [ESP + 8]
    MOV   [gdtr], AX
    LGDT  [gdtr]
    jmp 0x08:.reload_segments
.reload_segments:
    mov ax,0x10
    mov ds,ax
    mov es,ax
    mov fs,ax
    mov gs,ax
    mov ss,ax
    mov ax,0x18
    ltr ax
    RET

idt_desc:
    dw 0
    dd 0
load_idt:
    mov eax,[esp+0x4]
    mov [idt_desc+2],eax
    mov ax,[esp+0x8]
    mov [idt_desc],ax
    lidt [idt_desc]
    sti
    ret