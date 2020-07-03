print:
    pusha
    mov bx,0
printloop:
    mov al,[di]
    cmp al,byte 0
    je printend
    mov ah,0x0e
    int 0x10
    inc di
    jmp printloop
printend:
    popa
    ret


print_nl:
    pusha
    
    mov ah, 0x0e
    mov al, 0x0a ; newline char
    int 0x10
    mov al, 0x0d ; carriage return
    int 0x10
    popa
    ret