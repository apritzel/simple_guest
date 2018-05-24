// SPDX-License-Identifier: GPL-2.0

#ifndef UART_PL011_H__
#define UART_PL011_H__

#include <asm/io.h>

#ifdef TARGET_qemu
#define UART_BASE_ADDR  0x09000000
#endif

#define PL011_DR	0x00
#define PL011_FR	0x18
#define PL011_IBRD	0x24
#define PL011_FBRD	0x28
#define PL011_LCR_H	0x2c
#define PL011_CR	0x30

void uart_init(const void *fdt)
{
	writel(0x70, UART_BASE_ADDR + PL011_LCR_H); // 8n1, enable FIFOs
	writel(0x301, UART_BASE_ADDR + PL011_CR);   // UART, TX, RX enable
}

int putchar(int c)
{
/* Avoid pointless traps on emulated devices */
#ifndef TARGET_qemu
	while (readl(UART_BASE_ADDR + PL011_FR) & 0x20)
		;
#endif

	writel(c, UART_BASE_ADDR + PL011_DR);
}

#endif
