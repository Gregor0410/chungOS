[org 0x7c00]
jmp 0x0:boot
boot:
	xor ax,ax
	mov ds,ax
	mov es,ax
	mov ss,ax
	mov bp,0x7c00
	mov sp,bp
	mov [DRIVE],dl
	call load_kernel
	call switch32
	jmp $
load_kernel:
	cld
	mov bx,0x1000
	mov dh,1
	mov dl,[DRIVE]
	call disk_load
	ret
%include "./boot/bootprint.asm"
%include "./boot/print32.asm"
%include "./boot/disk.asm"
%include "./boot/gdt.asm"
%include "./boot/switch32.asm"
[bits 32]
ENTRYPOINT:
	call clear_screen
	mov ebx,message32
	call print32
	mov edx, [0x1001]
	call printhex32
	jmp $
message16 db "[ChungOS] booted into 16 bit real mode",0
message32 db "[ChungOS] booted into 32 bit protected mode",0
DRIVE db 0

times 510-($-$$) db 0
dw 0xaa55
db 0x41
dd 0xcafebabe