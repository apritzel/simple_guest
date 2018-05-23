SH=/bin/sh

all: simple_guest.bin

%.o: %.c
	${CROSS_COMPILE}gcc -O -c -o $@ $^

%.o: %.S
	${CROSS_COMPILE}as -o $@ $^

simple_guest.bin: start.o simple_guest.o
	${CROSS_COMPILE}ld -o simple_guest.elf $^
	${CROSS_COMPILE}objcopy -O binary simple_guest.elf $@

.PHONY: clean distclean run

run: simple_guest.bin
	qemu-system-aarch64 -M virt -cpu cortex-a57 -nographic -kernel $^

clean:
	rm -f *.o

distclean: clean
	rm -f simple_guest.elf simple_guest.bin
