CC=/opt/riscv/bin/riscv32-unknown-elf-gcc
CFLAGS=-O3 -Wall -Wpedantic -Werror -std=gnu11

all: main.S

main.S: main.c Makefile
	$(CC) $(CFLAGS) -S -fverbose-asm main.c -o main.S


