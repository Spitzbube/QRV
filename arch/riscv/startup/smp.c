/**
 * \brief Implementation of init_system_private().
 *
 * \license Apache 2.0 (http://www.apache.org/licenses/LICENSE-2.0)
 *
 * \copyright (c) 2008 QNX Software Systems.
 */

#include <startup.h>

/* This boolean is set when the entire syspage is ready */
volatile bool syspage_available;

/**
 * \brief TODO
 */
void cpu_startup(void)
{
}

/**
 * \brief Initialize SMP structure in the system page.
 */
void init_smp(void)
{
    unsigned num_cpus;

    if (max_cpus > 1) {
        num_cpus = board_smp_num_cpu();
        if (num_cpus > max_cpus)
            num_cpus = max_cpus;
        lsp.syspage.p->num_cpu = num_cpus;

        if (num_cpus > 1)
            set_syspage_section(&lsp.smp, sizeof(*lsp.smp.p));
    }
}
