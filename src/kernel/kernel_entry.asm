global _loader                          ; Make entry point visible to linker.
global boot_page_directory
extern kernel_main                            ; _main is defined elsewhere
 
; setting up the Multiboot header - see GRUB docs for details
MODULEALIGN equ  1<<0             ; align loaded modules on page boundaries
MEMINFO     equ  1<<1             ; provide memory map
FLAGS       equ  MODULEALIGN | MEMINFO  ; this is the Multiboot 'flag' field
MAGIC       equ    0x1BADB002     ; 'magic number' lets bootloader find the header
CHECKSUM    equ -(MAGIC + FLAGS)  ; checksum required
 
; This is the virtual base address of kernel space. It must be used to convert virtual
; addresses into physical addresses until paging is enabled. Note that this is not
; the virtual address where the kernel image itself is loaded -- just the amount that must
; be subtracted from a virtual address to get a physical address.
KERNEL_VIRTUAL_BASE equ 0xC0000000                  ; 3GB
KERNEL_PAGE_NUMBER equ (KERNEL_VIRTUAL_BASE >> 22)  ; Page directory index of kernel's 4MB PTE.
 
 
section .data
align 0x1000
boot_page_directory:
    times 0x1000 db 0
boot_page_table1:
	times 0x1000 db 0
 
section .text
align 4
MultiBootHeader:
    dd MAGIC
    dd FLAGS
    dd CHECKSUM
 
; reserve initial kernel stack space -- that's 16k.
STACKSIZE equ 0x4000
 
; setting up entry point for linker
loader equ (_loader - 0xC0000000)
global loader
 
_loader:
    ; set up page directory with identity map and kernel higher half map
    mov ecx, (boot_page_directory - KERNEL_VIRTUAL_BASE)
	mov cr3, ecx                                        ; Load Page Directory Base Register.
	mov eax,(boot_page_table1- KERNEL_VIRTUAL_BASE)
	or eax,0x3
	mov [ecx],eax
	add ecx,(KERNEL_PAGE_NUMBER*4)
	mov [ecx],eax
	mov ecx,(boot_page_directory - KERNEL_VIRTUAL_BASE) ; map last PDE to the page directory
	mov eax,ecx
	add ecx,(1023*4) 
	or eax,0x3
	mov [ecx],eax
	;set up the page table
	mov ecx, 1024
	mov edi,(boot_page_table1- KERNEL_VIRTUAL_BASE)
	mov esi, 0
	.loop:
		mov eax,esi
		or eax,0x3
		mov [edi],eax
		add esi, 0x1000
		add edi,4
		dec ecx
		cmp ecx,0
		jne .loop
    
	mov eax,cr3
	mov cr3,eax
    mov ecx, cr0
    or ecx, 0x80000000                          ; Set PG bit in CR0 to enable paging.
    mov cr0, ecx
 
    ; Start fetching instructions in kernel space.
    ; Since eip at this point holds the physical address of this command (approximately 0x00100000)
    ; we need to do a long jump to the correct virtual address of StartInHigherHalf which is
    ; approximately 0xC0100000.
    lea ecx, [StartInHigherHalf]
    jmp ecx                                                     ; NOTE: Must be absolute jump!
 
StartInHigherHalf:
    mov esp, stack+STACKSIZE           ; set up the stack
    push eax                           ; pass Multiboot magic number
 
    ; pass Multiboot info structure -- WARNING: This is a physical address and may not be
    ; in the first 4MB!
    push ebx
 
    call  kernel_main                  ; call kernel proper
    hlt                          ; halt machine should kernel return
 
 
section .bss
align 32
stack:
    resb STACKSIZE      ; reserve 16k stack on a uint64_t boundary