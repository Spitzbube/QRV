/**
 * \brief Function to be executed before and after main()
 *
 * \license Apache 2.0 (http://www.apache.org/licenses/LICENSE-2.0)
 *
 * \copyright (c) 2008 QNX Software Systems.
 */

#include <startup.h>
#include <sbi.h>

unsigned paddr_bits;
int debug_flag = 0;
size_t reserved_size;
unsigned reserved_align;
unsigned long cpu_freq;
unsigned long cycles_freq;
unsigned long timer_freq;
chip_info dbg_device[2];
unsigned patch_channel;

char **_argv;
int _argc;
unsigned max_cpus = ~0U;
chip_info timer_chip;
unsigned (*timer_start)(void);
unsigned (*timer_diff)(unsigned start);
struct syspage_entry *_syspage_ptr;
unsigned misc_flags;
bool secure_system = 0;

extern int main(int argc, char **argv, char **envv);
char boot_command_line[CONFIG_MAX_BOOTLINE_SIZE];

static char *argv[64];

#ifdef CONFIG_BOOT_ENV_VARS
static char *envv[64];
#else
static char **envv = NULL;
#endif


/**
 * \brief Initialize argc and argv variables from boot_command_line.
 */
static void setup_cmdline(void)
{
    char *s = boot_command_line;
    int i = 0, argc = 0;

    argc = 0;
    size_t n = strlen(boot_command_line);
    while (i < n && argc < NUM_ELTS(argv)) {
        argv[argc] = s + i;
        /* Skip spaces, stop if zero */
        if (s[i] == 0)
            break;
        while (s[i] != ' ') i++;
        s[i++] = 0;
        ++argc;
    }
    argv[argc] = 0;

#ifdef CONFIG_BOOT_ENV_VARS
    int envc = 0
    for (i = 0; i < boot_args.envc; ++i) {
        if (i < sizeof envv / sizeof *envv - 1)
            envv[envc++] = args;
        while (*args++);
    }
    envv[envc] = 0;
#endif
    _argc = argc;
    _argv = argv;
}

/**
 * \brief _main(), a precursor to main()
 * \note This is the first function run in supervisor mode.
 */
void _main(void)
{
    paddr_bits = arch_max_paddr_bits();

    board_init();

    setup_cmdline();

    cpu_startup();

#define INIT_SYSPAGE_SIZE 0x600
    init_syspage_memory(ws_alloc(INIT_SYSPAGE_SIZE), INIT_SYSPAGE_SIZE);

    main(_argc, _argv, envv);

#ifdef CONFIG_MINIDRIVER
    /*
     * Tell the mini-drivers that the next time they're called, they're
     * going to be in the kernel. Also flip the handler & data pointers
     * to the proper values for that environment.
     */
    mdriver_hook();
#endif

    /*
     * Copy the local version of the system page we've built to the real
     * system page location we allocated in init_system_private().
     */
    write_syspage_memory();

    //
    // Tell the AP's that that the syspage is now present.
    //
    smp_hook_rtn();

    kprintf("next is to call startnext...");
    for(;;);
    //startnext();
}

static void hook_dummy(void)
{
}

void (*smp_hook_rtn)(void) = hook_dummy;
void (*mdriver_check)(void) = hook_dummy;
void (*mdriver_hook)(void) = hook_dummy;


// Replacement for some C library stuff to minimize startup size
int errno;

int *__get_errno_ptr(void)
{
    return &errno;
}


size_t __stackavail(void)
{
    return (size_t) ~0;
}
