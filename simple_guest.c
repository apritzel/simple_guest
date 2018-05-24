// SPDX-License-Identifier: GPL-2.0

#include <stdio.h>

int cmain(unsigned long fdt_addr, unsigned long par2, unsigned long par3,
	  unsigned long load_addr)
{
	unsigned long el;

	uart_init((void *)fdt_addr);

	puts("Running in EL");
	__asm__ volatile ("mrs %0, CurrentEL\n" : "=r" (el));
	puthexln(el >> 2);

	puts("FDT address: 0x");
	puthexln(fdt_addr);

	puts("load address: 0x");
	puthexln(load_addr);

	return 0;
}
