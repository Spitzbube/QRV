/**
 * \brief Various debugging routines.
 *
 * \license Apache 2.0 (http://www.apache.org/licenses/LICENSE-2.0)
 *
 * \copyright (c) 2009 QNX Software Systems.
 */

#include <kernel/startup.h>

extern void print_syspage_enable(const char *name);
extern void print_syspage_sections(void);

void print_syspage(void)
{
    int opt;

    if (debug_flag > 1) {
        /* We enable things here so that this code doesn't get
         * hauled in unless the user calls print_syspage(). */
        optind = 0;
        while ((opt = getopt(_argc, _argv, "S:")) != -1) {
            if (opt == 'S') {
                print_syspage_enable(optarg);
            }
        }
        print_syspage_sections();
    }
}
