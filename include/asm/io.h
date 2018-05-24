// SPDX-License-Identifier: GPL-2.0
#ifndef IO_H__
#define IO_H__

#include <stdint.h>

#define dmb()		asm volatile ("" : : : "memory")

#define readb_relaxed(a)	(*(volatile uint8_t *)(uintptr_t)(a))
#define writeb_relaxed(v, a)	((*(volatile uint8_t *)(uintptr_t)(a)) = (v))
#define readh_relaxed(a)	(*(volatile uint16_t *)(uintptr_t)(a))
#define writeh_relaxed(v, a)	((*((volatile uint16_t *)(uintptr_t)(a))) = (v))
#define readl_relaxed(a)	(*(volatile uint32_t *)(uintptr_t)(a))
#define writel_relaxed(v, a)	((*((volatile uint32_t *)(uintptr_t)(a))) = (v))

#define readb(a)	({uint8_t __v = readb_relaxed(a); dmb(); __v;})
#define readh(a)	({uint16_t __v = readh_relaxed(a); dmb(); __v;})
#define readl(a)	({uint32_t __v = readl_relaxed(a); dmb(); __v;})
#define writeb(v, a)	({dmb(); writeb_relaxed((v), (a));})
#define writeh(v, a)	({dmb(); writeh_relaxed((v), (a));})
#define writel(v, a)	({dmb(); writel_relaxed((v), (a));})

#endif
