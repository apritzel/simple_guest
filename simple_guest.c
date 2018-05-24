// SPDX-License-Identifier: GPL-2.0

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

int _cmain(unsigned long dram_start, unsigned long uart_addr)
{
	uart_init();

	puts("load address: 0x");
	puthexln(dram_start);

	return 0;
}
