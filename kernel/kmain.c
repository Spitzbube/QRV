/*
 * $QNXLicenseC:
 * Copyright 2007, QNX Software Systems. All Rights Reserved.
 *
 * You must obtain a written license from and pay applicable license fees to QNX
 * Software Systems before you may reproduce, modify or distribute this software,
 * or any work that includes all or part of this software.   Free development
 * licenses are available for evaluation and non-commercial purposes.  For more
 * information visit http://licensing.qnx.com or email licensing@qnx.com.
 *
 * This file may contain contributions from others.  Please review this entire
 * file for other proprietary rights or license notices, as well as the QNX
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 * $
 */

#include "externs.h"
#include "apm.h"
#include <unistd.h>

struct module_entry {
    void (*init)(unsigned, unsigned);
    unsigned prio;
};

void module_init(unsigned pass)
{
    extern struct module_entry module_start[];
    extern struct module_entry module_end[];
    struct module_entry *mod;

    for (mod = module_start; mod < module_end; ++mod) {
        if (mod->init != NULL) {
            mod->init(LIBMOD_VERSION_CHECK, pass);
        }
    }
}

/**
 * \brief TODO
 */
static size_t getmem(char *arg)
{
    size_t size;

    size = strtoul(arg, &arg, 0);
    switch (*arg) {
    case 'k':
    case 'K':
        size *= KILO(1);
        break;
    case 'm':
    case 'M':
        size *= MEG(1);
        break;
    default:
        break;
    }
    return size;
}

void kernel_main(int argc, char *argv[], char *env[])
{
    int i;
    ulong_t n;
    char *cp, *mem_config;
    size_t pregrow = KILO(64);

    module_init(0);
    for (i = 0; i < NUM_PROCESSORS; ++i) {
        if ((SYSPAGE_ENTRY(cpuinfo)[i].flags & CPU_FLAG_FPU) == 0) {
            fpuemul |= 2;
        }
    }
    mem_config = "";
    while ((i = getopt(argc, argv, "a:cf:T:F:m:pP:hl:R:M:ve:u:H:")) != -1) {
        switch (i) {
        case 'u':
            procfs_umask = (mode_t)strtoul(optarg, NULL, 0);
            break;
        case 'a':
            switch (optarg[0]) {
            case 'd':
                align_fault = 1;
                break;
            case 'e':
                align_fault = -1;
                break;
            case 's':
                align_fault = 0;
                break;
            default:
                break;
            }
            break;

        case 'c':
            intrs_aps_critical = 0;
            break;

        case 'p':
            nopreempt = 1;
            break;

        case 'h':
            nohalt = 1;
            break;

        case 'f':
            cp = optarg;
            if (*cp == 'e')
                fpuemul |= 1;
            break;
        case 'm':
            mem_config = optarg;
            break;

        case 'l':
            // -l PROCESSES,THREADS,TIMERS,PULSES,SYNCS,CONNECTS,CHANNELS,INTERRUPTS
            for (cp = optarg, i = 0; *cp; ++i) {
                ulong_t lim = strtoul(cp, &cp, 0);
                if (lim && lim < LONG_MAX)
                    limits_max[i] = (long)lim;
                else
                    kprintf("Ignoring limit value %lu\n", lim);
                if (*cp == ',')
                    ++cp;
            }
            break;

        case 'T': {
            ulong_t val = strtoul(optarg, NULL, 0);
            if (val > 1024) {
                pr_warn("ignoring given fd timeout (value %ld is too high)\n", val);
                break;
            }
            if (val == 0) {
                val = 30;
                pr_warn("fd timeout value is 0, setting to default (%d)\n", val);
            }
            fd_close_timeout = (unsigned)val;
            break;
        }

        case 'F': {
            ulong_t val = strtoul(optarg, NULL, 0);
            if (val > INT_MAX || val < 100) {
                pr_warn("given value for max_fds (%d) is too small or too big, setting to default (100)", val);
                val = 100;
            }
            max_fds = (unsigned)val;
            break;
        }

        case 'P': {
            ulong_t val = strtoul(optarg, NULL, 0);
            if (val < 10) {
                pr_warn("priv value %d too low, setting to default (10)\n", val);
                val = 10;
            }
            if (priv_prio > NUM_PRI) {
                pr_warn("priv value %d too high, setting to default (10)\n", val, NUM_PRI);
                val = NUM_PRI;
            }
            priv_prio = (unsigned)val;
            break;
        }

        case 'R':
            /*
             * reserved memory size (guarantee) for the sysram memory class in the
             * system partition. It would have bee nice to make this a memory ('m')
             * option, but currently that mechanism was designed mainly for flags
             * so using the '-R' option since this is consistent with startup.
             * The value specified here will be sanitized and take effect when
             * MEMPART_INIT() is called.
             * This option is only effective if the memory partition module is
             * included in the build otherwise any optional value will be ignored
             */
            {
                sys_mempart_sysram_min_size = getmem(optarg);

                if (ker_verbose) {
                    kprintf("system partition reserved = 0x%x bytes\n",
                            sys_mempart_sysram_min_size);
                }
                break;
            }
        case 'M':
            {
                /*
                 * mempart_flags_t setting for default_mempart_flags.
                 * This option is independent or the partitioning module
                 */
                ulong_t tmp = strtoul(optarg, NULL, 0);

                if ((tmp & (mempart_flags_HEAP_CREATE | mempart_flags_HEAP_SHARE)) == 0) {
                    pr_warn("Illegal -M option to procnto\n"
                            "Must contain mempart_flags_HEAP_CREATE and/or mempart_flags_HEAP_SHARE\n");
                } else {
                    default_mempart_flags = (unsigned)tmp;
                }

                if (ker_verbose) {
                    kprintf("MEMPART options flags = 0x%x\n", default_mempart_flags);
                }
                break;
            }

        case 'v':
            ker_verbose++;
            break;

        case 'e':
            switch (optarg[0]) {
            case 'n':
                SYSPAGE_ENTRY(system_private)->private_flags |= SYSTEM_PRIVATE_FLAG_EALREADY_NEW;
                break;

            case 'o':
            default:
                SYSPAGE_ENTRY(system_private)->private_flags &= ~SYSTEM_PRIVATE_FLAG_EALREADY_NEW;
                break;
            }
            break;

        case 'H':
            pregrow = getmem(optarg);
            if (pregrow < KILO(1))
                pregrow *= KILO(1);
            break;

        default:
            break;
        }
    }

    if (fpuemul) {
        for (i = 0; i < NUM_PROCESSORS; ++i) {
            SYSPAGE_ENTRY(cpuinfo)[i].flags &= ~CPU_FLAG_FPU;
        }
    }

    if (SYSPAGE_ENTRY(system_private)->private_flags & SYSTEM_PRIVATE_FLAG_EALREADY_NEW) {
        __ealready_value = EALREADY_NEW;
    } else {
        __ealready_value = EALREADY_OLD;
    }

    init_memmgr();
    memmgr.configure(mem_config);
    mdriver_check();
    init_traps();
    mdriver_check();
    memmgr.init_mem(0);
    mdriver_check();
    heap_init(pregrow);
    mdriver_check();
    thread_init();
    mdriver_check();
    module_init(1);
    mdriver_check();
    init_objects();
    mdriver_check();
    intrevent_init(0);
    mdriver_check();
    timer_init();
    mdriver_check();
    interrupt_init();
    mdriver_check();
    init_cpu();

    // Remaining arguments are for Proc, save them in malloc'd storage
    argc -= (optind - 1);
    argv += (optind - 1);
    _argv = _smalloc(((unsigned)argc + 1) * sizeof(*argv));
    for (i = 1; i < argc; ++i) {
        _argv[i] = strdup(argv[i]);
    }
    _argv[0] = strdup(argv[1 - optind]);
    _argv[i] = NULL;
    _argc = argc;
    for (n = 0; env[n] != NULL; ++n) {
        //nothing to do
    }
    environ = _smalloc((n + 1) * sizeof(*environ));
    for (i = 0; i < n; ++i) {
        environ[i] = strdup(env[i]);
    }
    environ[i] = NULL;
    optind = -1;

    // This will return through the kernel and idle will be running!

    mdriver_check();
    set_inkernel(0);
    ker_start();
}
