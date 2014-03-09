# Makefile for JamesM's kernel tutorials.
# The C and C++ rules are already setup by default.
# The only one that needs changing is the assembler 
# rule, as we use nasm instead of GNU as.

SOURCES=boot.o main.o monitor.o common.o descriptor_tables.o key.o isr.o interrupt.o gdt.o timer.o
CFLAGS=-nostdlib -nostdinc -fno-builtin -fno-stack-protector -I include/
LDFLAGS=-Tlink.ld
ASFLAGS=-felf

all: $(SOURCES) link

v:
	make all
	sh grub.sh
q:
	make all
	qemu --kernel kernel.bin
g:
	sh g.sh
clean:
	-rm *.o kernel

link:
	ld $(LDFLAGS) -o iso/boot/kernel.bin $(SOURCES)
	ld $(LDFLAGS) -o kernel.bin $(SOURCES)
	rm *.o
	

.s.o:
	nasm $(ASFLAGS) $<
