// SPDX-License-Identifier: GPL-2.0

#include <stdio.h>

#ifdef TARGET_qemu
	#include "uart_pl011.h"
#endif

int puts(const char *s)
{
	while (*s) {
		if (*s == '\n')
			putchar('\r');
		putchar(*s++);
	}

	return 0;
}

void puthexb(unsigned char b)
{
	if ((b >> 4) > 9)
		putchar((b >> 4) + 'a' - 10);
	else
		putchar((b >> 4) + '0');
	if ((b & 0xf) > 9)
		putchar((b & 0xf) + 'a' - 10);
	else
		putchar((b & 0xf) + '0');
}

void puthex(unsigned long val)
{
	int shift, nibble;
	int first = 1;

	for (shift = 60; shift >= 0; shift -= 4) {
		nibble = (val >> shift) & 0xf;

		if (!nibble && first && shift > 0)
			continue;

		first = 0;

		if (nibble > 9)
			putchar(nibble + 'a' - 10);
		else
			putchar(nibble + '0');
	}
}

void puthexln(unsigned long val)
{
	puthex(val);
	putchar('\r');
	putchar('\n');
}
