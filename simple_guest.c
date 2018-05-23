// SPDX-License-Identifier: GPL-2.0

int _cmain(unsigned long dram_start, unsigned long uart_addr)
{
	volatile char *uart = (void *)uart_addr;

	*uart = 'C';

	return 0;
}
