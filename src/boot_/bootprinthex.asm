printhex:
    pusha
    mov bp,sp
    sub sp,0x5
    mov bx,0
    mov si,sp
loop:
    cmp bx,4
    je printhexend
    mov ax,dx
    and ax,0xf000
    shr ax,12
    add al,0x30
    cmp al,0x39
    jle step2
    add al,7
step2:    
    mov [si+bx],byte al
    rol dx,4
    inc bx
    jmp loop
printhexend:
    mov [si+0x4],byte 0x00
    mov di,sp
    call print
    mov sp,bp
    popa
    ret
