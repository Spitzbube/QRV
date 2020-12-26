/**
 * \file board.c
 *
 * Board initialization, occurs right after the assembly code in head.S
 *
 * \author Anup Patel <anup.patel@wdc.com>
 * \copyright (c) 2019 Western Digital Corporation or its affiliates.
 *
 * \license SPDX-License-Identifier: BSD-2-Clause
 */

#include <kernel/startup.h>
#include <sbi.h>
#include <sys/fdt.h>

#define SBI_FDT_ADDR 0x82200000

void *fdt_addr;

void rvq_putc_ser_dbg(int c) { sbi_ecall_console_putc(c); };

#define _BE(x) ENDIAN_RET32(x)

/**
 * \brief Early board initialization.
 * \note Register our putchar routine here.
 *       Remove after the select_debug mechanism is ready.
 */
void board_init(void)
{
    set_print_char(rvq_putc_ser_dbg);
    for (int i = 0; i < 79; i++)
        sbi_ecall_console_putc('=');
    sbi_ecall_console_puts("\n\n");

    fdt_addr = (void *)SBI_FDT_ADDR;
    const struct fdt_header *fdt = fdt_addr;

    /* Check the signature. If device tree is not there, we cannot continue */
    if (_BE(fdt->magic) != FDT_MAGIC) {
        crash("FDT not detected, cannot continue.\n");
    }

    pr_debug("Devicetree version %d\n", _BE(fdt->version));
}
