[bits 32]
VGA_MEMORY equ 0xb8000
COLOR equ 0x0f

print32:
    pusha
    mov ecx,VGA_MEMORY
    mov ah,COLOR
.loop:
    cmp [ebx],byte 0x0
    je .end
    mov al,[ebx]
    mov [ecx],eax
    inc ebx
    add ecx,2
    jmp .loop
.end:
    popa
    ret

clear_screen:
    pusha
    mov edi,VGA_MEMORY
    mov ebx,0
clear_screen_loop:
    cmp ebx,0x7a0
    je clear_screen_end
    mov eax,0x0
    mov [edi+ebx],eax
    inc ebx
    jmp clear_screen_loop
clear_screen_end:
    popa
    ret
printhex32:
    pusha
    mov ebp,esp
    sub esp,0x9
    mov ebx,0
    mov esi,esp
.loop:
    cmp ebx,8
    je .end
    mov eax,edx
    and eax,0xf0000000
    shr eax,28
    add al,0x30
    cmp al,0x39
    jle .step2
    add al,7
.step2:    
    mov [esi+ebx],byte al
    rol edx,4
    inc ebx
    jmp .loop
.end:
    mov [esi+0x8],byte 0x00
    mov ebx,esp
    call print32
    mov esp,ebp
    popa
    ret
