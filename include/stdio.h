// SPDX-License-Identifier: GPL-2.0

#ifndef __STDIO_H__
#define __STDIO_H__

void uart_init(const void *fdt);

int putchar(int c);
int puts(const char *s);

void puthexb(unsigned char val);
void puthex(unsigned long val);
void puthexln(unsigned long val);

#endif
