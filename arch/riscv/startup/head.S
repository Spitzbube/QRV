/**
 * \file head.S
 *
 * First instructions executed in the startup
 *
 * \author Anup Patel <anup.patel@wdc.com>
 * \copyright (c) 2019 Western Digital Corporation or its affiliates.
 *
 * \license SPDX-License-Identifier: BSD-2-Clause
 *
 */

/* Supervisor interrupt enable register */
#define CSR_SIE		0x104

/* Supervisor trap handler base address */
#define CSR_STVEC	0x105

/* Supervisor interrupt pending register */
#define CSR_SIP		0x144

	.section .entry, "ax", %progbits
	.align 3
	.global _start
_start:
	/* Pick one hart to run the main boot sequence */
	la	a3, _hart_lottery
	li	a2, 1
	amoadd.w a3, a2, (a3)
	bnez	a3, _start_hang

	/* Save a0 and a1 */
	la	a3, _boot_a0
	sd	a0, 0(a3)
	la	a3, _boot_a1
	sd	a1, 0(a3)

	/* Zero-out BSS */
	la	a4, _bss_start
	la	a5, _bss_end
_bss_zero:
	sd	zero, (a4)
	add	a4, a4, __SIZEOF_POINTER__
	blt	a4, a5, _bss_zero

_start_warm:
	/* Disable and clear all interrupts */
	csrw	CSR_SIE, zero
	csrw	CSR_SIP, zero

	/* Setup exception vectors */
	la	a3, _start_hang
	csrw	CSR_STVEC, a3

	/* Setup stack */
	la	a3, _kernel_end
	li	a4, 0x2000
	add	sp, a3, a4

	/* Jump to _main() */
	la	a3, _boot_a0
	ld	a0, 0(a3)
	la	a3, _boot_a1
	ld	a1, 0(a3)
	call	_main

	/* We don't expect to reach here hence just hang */
	j	_start_hang

	.section .entry, "ax", %progbits
	.align 3
	.globl _start_hang
_start_hang:
	wfi
	j	_start_hang

	.section .entry, "ax", %progbits
	.align	3
	.global _boot_a0, _boot_a1
_hart_lottery:
	.dword	0
_boot_a0:
	.dword	0
_boot_a1:
	.dword	0
