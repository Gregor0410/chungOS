C_SOURCES = $(wildcard stdio/*.c string/*.c stdlib/*.c)
HEADERS = $(wildcard include/*.h) 
# Nice syntax for file extension replacement
OBJ = ${C_SOURCES:.c=.o}
PROJECT_DIR = $(shell pwd)/../..
# Change this if your cross-compiler is somewhere else
CC = i686-elf-gcc --sysroot=${PROJECT_DIR}/src/sysroot -isystem=/usr/include
GDB = i686-elf-gdb
AR = i686-elf-ar
# -g: Use debugging symbols in gcc
CFLAGS = -g

# First rule is run by default
all: lib/libk.a
	cp -r include ../sysroot/usr/
	cp lib/libk.a ../sysroot/usr/lib/libk.a

lib/libk.a: ${OBJ}
	${AR} rcs $@ $^

# Generic rules for wildcards
# To make an object, always compile from its .c
%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -O1 -std=gnu99 -Wall -Wextra -ffreestanding -c $< -o $@

%.o: %.asm
	nasm -felf32 $< -o $@
