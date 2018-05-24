SH=/bin/sh

TARGET=qemu

STANDALONE=-fpic -fno-common -fno-builtin -ffreestanding -nostdinc -fno-strict-aliasing -fno-stack-protector -fno-toplevel-reorder -Wstrict-prototypes -Wno-format-nonliteral -Wno-format-security -nostdlib -Iinclude
STANDALONE_ARM=-mstrict-align

all: simple_guest.bin

OBJS=start.o simple_guest.o

%.o: %.c
	${CROSS_COMPILE}gcc -Os ${STANDALONE} ${STANDALONE_ARM} -c -o $@ -Ttext=0 -DTARGET_${TARGET} $^

%.o: %.S
	${CROSS_COMPILE}as -o $@ $^

simple_guest.bin: ${OBJS}
	${CROSS_COMPILE}ld -Ttext=0 -o simple_guest.elf $^
	${CROSS_COMPILE}objcopy -O binary simple_guest.elf $@

.PHONY: clean distclean run

run: simple_guest.bin
	qemu-system-aarch64 -M virt -cpu cortex-a57 -nographic -kernel $^

clean:
	rm -f *.o

distclean: clean
	rm -f simple_guest.elf simple_guest.bin
