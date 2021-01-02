/**
 * \file entry.S
 *
 * First instructions executed when the kernel starts.
 *
 * \license MIT (https://opensource.org/licenses/mit-license.php)
 *
 * \copyright (c) 2006-2020 Frans Kaashoek, Robert Morris, Russ Cox,
 *                          Massachusetts Institute of Technology
 */

/*
 * We link statically and the first address to execute (_entry) is
 * specified in the linker script. It can be:
 *      0x80000000 for plain QEMU without BIOS/firmware;
 *      0x80200000 for OpenSBI's fw_jump.bin
 */

.section .text

/* Each CPU will start from this point */
.global _entry

_entry:
	/* This instruction decodes to "MZ" ASCII required by UEFI */
	c.li	s4,-13
	j	_entry1

	.balign 8
	/* Image load offset from the start of RAM */
	.dword 0x200000
	.dword __end - __start
	.dword RISCV_IMAGE_FLAG_LE
	.word RISCV_HEADER_VERSION
	.word 0
	.dword 0
	.ascii RISCV_IMAGE_MAGIC
	.balign 4
	.ascii RISCV_IMAGE_MAGIC2
	.word 0

        /*
         * Set up a stack for C (stack0 is declared in start.c,
         * with a 4096-byte stack per CPU)
         * sp = stack0 + (hartid * 4096)
         */
_entry1:
        la      sp, stack0
        li      a0, 1024*4
        csrr    a1, mhartid
        addi    a1, a1, 1
        mul     a0, a0, a1
        add     sp, sp, a0

        // jump to start() in start.c
        call	start
spin:
        j	spin
