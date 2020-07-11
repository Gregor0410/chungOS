C_SOURCES = $(wildcard src/kernel/*.c src/kernel/bin/*.c src/drivers/*.c src/libc/*/*.c src/kernel/interrupts/*.c src/kernel/allocator/*.c)
ASM_SOURCES = $(wildcard src/kernel/*.asm src/kernel/interrupts/*.asm)
DIRS = $(wildcard src/kernel src/boot)
HEADERS = $(wildcard src/kernel/*.h src/kernel/bin/*.h src/drivers/*.h src/libc/*/*.c) 
# Nice syntax for file extension replacement
OBJ = ${C_SOURCES:.c=.o}
ASM_OBJ = ${ASM_SOURCES:.asm=.o}
# Change this if your cross-compiler is somewhere else
CC = /usr/local/i386elfgcc/bin/i386-elf-gcc
GDB = /usr/local/i386elfgcc/bin/i386-elf-gdb
# -g: Use debugging symbols in gcc
CFLAGS = -g

# First rule is run by default
dist/os.iso: dist/kernel.elf
		cp $< iso/boot/kernel.elf
	    xorriso -report_about HINT -abort_on WARNING -as mkisofs -quiet -boot-info-table -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -input-charset utf-8 -o $@ iso
		#genisoimage -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -A os -input-charset utf8 -quiet -boot-info-table -o os.iso iso
# '--oformat binary' deletes all symbols as a collateral, so we don't need
# to 'strip' them manually on this case
dist/kernel.elf: ${ASM_OBJ} ${OBJ}
	/usr/local/i386elfgcc/bin/i386-elf-ld -T src/link.ld  $^ -o $@

run: os-image.bin
	qemu-system-i386 -fda os-image.bin
flash:
	cp dist/kernel.elf /mnt/e/boot/kernel.elf
# Open the connection to qemu and load our kernel-object file with symbols
debug: os-image.bin kernel.elf
	qemu-system-i386 -s -fda os-image.bin &
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

# Generic rules for wildcards
# To make an object, always compile from its .c
%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -O1 -std=gnu99 -Wall -Wextra -ffreestanding -c $< -o $@

%.o: %.asm
	nasm -felf32 $< -o $@

%.bin: %.asm
	nasm $< -f bin -o $@
