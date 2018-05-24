/* SPDX-License-Identifier: GPL-2.0 */

.text
.globl _start
_start:

	b	start
	.word	0xbaadf00d

	.quad	0x80000		// load offset
	.quad	0x100		// size
	.quad	9		// 4K pages, LE, no placement restriction
	.quad	0		// reserved
	.quad	0		// reserved
	.quad	0		// reserved
	.word	0x644d5241	// ARM64 kernel magic
	.word	0		// reserved

start:
	adr	x3, stack
	mov	sp, x3
	adr	x3, _start
	bl	cmain

	mov	x0, #0x84000000	// PSCI base function identifier
	orr	w0, w0, #0x8	// PSCI_SYSTEM_OFF
	mrs	x1, CurrentEL
	cmp	w1, #8
	b.eq	1f
	hvc	#0
	b	loop
1:	smc	#0
loop:	wfi
	b	loop

.data
.align 16
stack: .space	1024
