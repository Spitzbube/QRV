/*
 * Copyright 2013, QNX Software Systems.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"). You
 * may not reproduce, modify or distribute this software except in
 * compliance with the License. You may obtain a copy of the License
 * at: http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTIES OF ANY KIND, either express or implied.
 *
 * This file may contain contributions from others, either as
 * contributors under the License or as licensors under other terms.
 * Please review this entire file for other proprietary rights or license
 * notices, as well as the QNX Development Suite License Guide at
 * http://licensing.qnx.com/license-guide/ for other information.
 */

#include <kernel/startup.h>

#define STARTUP_DEBUG_LEVEL 4

extern void init_qtime(void);
extern void init_clocks(void);
extern void display_clocks(char *);

/* 5+ cycles per loop */
#define delay(x) {volatile unsigned _delay = x; while (_delay--); }
/* ~2 cycles per loop at 720MHz, x in 1/720us units (720MHz clock) */
#define delay_cy(x) {unsigned _delay = ((x+1)>>1); while (_delay--) asm volatile (""); }

const struct debug_device debug_devices[] = {
    { "8250",
	{
	    "0x44E09000^2.0.48000000.16",    // UART0, use the baud rate set by boot loader
        },
        init_riscv_ser,
        put_riscv_ser,
	{
	    &display_char_8250,
	    &poll_key_8250,
	    &break_detect_8250,
	}
    },
};

/*
 * main()
 *  Startup program executing out of RAM
 *
 * 1. It gathers information about the system and places it in a structure
 *    called the system page. The kernel references this structure to
 *    determine everything it needs to know about the system. This structure
 *    is also available to user programs (read only if protection is on)
 *    via _syspage->.
 *
 * 2. It (optionally) turns on the MMU and starts the next program
 *    in the image file system.
 */
int main(int argc, char **argv, char **envv)
{
    int opt;

    while ((opt = getopt(argc, argv, COMMON_OPTIONS_STRING "d")) != -1) {
        switch (opt) {
        case 'd':
            /* Enable WDT */
            //wdt_enable();
            break;
        default:
            handle_common_option(opt);
            break;
        }
    }

    /*
     * Initialize debugging output.
     * kprintf will not work before this point.
     */
    select_debug(debug_devices, sizeof(debug_devices));

    /*
     * Initialize clocks
     */
    init_clocks();

    init_raminfo();

    /*
     * Set CPU frequency
     */
    if (cpu_freq == 0) {
        cpu_freq = detect_frequency_using_power();
    }

    /*
     * Remove RAM used by modules in the image
     */
    alloc_ram(shdr->ram_paddr, shdr->ram_size, 1);

    if (shdr->flags1 & STARTUP_HDR_FLAGS1_VIRTUAL) {
        init_mmu();
    }

    init_intrinfo();

    init_qtime();

    init_cacheattr();

    init_cpuinfo();

    init_hwinfo();

    if (debug_flag > STARTUP_DEBUG_LEVEL) {
        display_clocks("-------after init_clocks-------\n");
        display_PLLs();
    }

    add_typed_string(_CS_MACHINE, "RISC-V virt");

    /*
     * Load bootstrap executables in the image file system and Initialise
     * various syspage pointers. This must be the _last_ initialisation done
     * before transferring control to the next program.
     */
    init_system_private();

    /*
     * This is handy for debugging a new version of the startup program.
     * Commenting this line out will save a great deal of code.
     */
    print_syspage();

    return 0;
}
