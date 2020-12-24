/**
 * \brief Implementation of init_system_private().
 *
 * \license Apache 2.0 (http://www.apache.org/licenses/LICENSE-2.0)
 *
 * \copyright (c) 2008 QNX Software Systems.
 */

#include <kernel/startup.h>

/* This boolean is set when the entire syspage is ready */
volatile bool syspage_available;

/**
 * \brief TODO
 */
void cpu_startup(void)
{
    /* For now, proceed only on hart 0. Put other CPUs to infinite spin */
    if (cpuid() != 0) {
        rvq_putc_ser_dbg('A' + cpuid());
        while (!syspage_available) {

        }for(;;) ;
    }
}
