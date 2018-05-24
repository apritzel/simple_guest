// SPDX-License-Identifier: GPL-2.0

#ifdef TARGET_qemu

#define UART_BASE_ADDR	0x09000000

static int putchar(int c)
{
	volatile unsigned int *uart_tx = (void *)UART_BASE_ADDR;

	*uart_tx = c;
}

static void uart_init(void)
{
	volatile unsigned int *uart_base = (void *)UART_BASE_ADDR;

	uart_base[0x30 / 4] |= 0x101;
}

#endif

static int puts(const char *s)
{
	while (*s) {
		if (*s == '\n')
			putchar('\r');
		putchar(*s++);
	}

	return 0;
}

static void puthexb(unsigned char b)
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

static void puthex(unsigned long val)
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

static void puthexln(unsigned long val)
{
	puthex(val);
	putchar('\r');
	putchar('\n');
}

int cmain(unsigned long fdt_addr, unsigned long par2, unsigned long par3,
	  unsigned long load_addr)
{
	unsigned long el;

	uart_init();

	puts("Running in EL");
	__asm__ volatile ("mrs %0, CurrentEL\n" : "=r" (el));
	puthexln(el >> 2);

	puts("FDT address: 0x");
	puthexln(fdt_addr);

	puts("load address: 0x");
	puthexln(load_addr);

	return 0;
}
