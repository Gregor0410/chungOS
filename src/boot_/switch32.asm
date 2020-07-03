[bits 16]
switch32:
    cli
    lgdt [gdt_descriptor]
    mov eax,cr0
    or eax,0x1
    mov cr0,eax
    jmp CODE_SEG:init

[bits 32]
init:
    mov ax,DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp,0x90000
    mov esp,ebp

    call ENTRYPOINT

MSG_PRE_INIT db "About to jump to code segment",0