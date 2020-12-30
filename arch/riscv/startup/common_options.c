/**
 * \brief Handle common command-line options.
 *
 * \license Apache 2.0 (http://www.apache.org/licenses/LICENSE-2.0)
 *
 * \copyright (c) 2008 QNX Software Systems.
 */

#include <startup.h>

static char *debug_opt[2];

static void get_freq(unsigned long *fp)
{
    unsigned long freq;
    char *end;

    freq = strtoul(optarg, &end, 10);
    if (optarg != end) {
        switch (*end) {
        case 'm':
        case 'M':
            freq *= 1000;
            /* fall through */
        case 'k':
        case 'K':
            freq *= 1000;
            /* fall through */
        case 'h':
        case 'H':
            ++end;
            break;
        default:
            if (freq < 1000)
                freq *= 1000000;
            break;
        }
        *fp = freq;
        optarg = end;
    }
    if (*optarg == ',')
        ++optarg;
}

void handle_common_option(int opt)
{
    unsigned num;
    char *cp;

    if (!cpu_handle_common_option(opt)) {
        switch (opt) {
        case 'D':
            /* kprintf output channel */
            debug_opt[0] = optarg;
            break;
        case 'f':
            /* CPU and timer frequency */
            get_freq(&cpu_freq);
            get_freq(&timer_freq);
            break;
        case 'K':
            /* kdebug remote debug protocol channel */
            debug_opt[1] = optarg;
            break;
        case 'N':
            add_typed_string(_CS_HOSTNAME, optarg);
            break;
        case 'R':
            reserved_size = getsize(optarg, &cp);
            if (*cp == ',') {
                reserved_align = getsize(cp + 1, &cp);
            }
            break;
        case 'S':
            // This gets handled later so that debug code isn't brought in all the time
            break;
        case 'P':
            num = strtoul(optarg, &optarg, 10);
            if (num > 0)
                max_cpus = num;
            break;
        case 'v':
            debug_flag++;
            break;
        case 'F':
        case 'A':
        case 'M':
        case 'r':
        case 'j':
        case 'Z':
            // All handled later, see init_system_private...
            break;
        }
    }
}

/**
 * \brief Set debug device.
 * \note TODO
 */
void set_debug(unsigned channel, const struct debug_device *dev, const char *options)
{
    dev->init(channel, options, dev->defaults[channel]);

    if (channel == 0)
        set_print_char(dev->put);
}

/**
 * \brief Select debug device and channel.
 */
static void select_one(const struct debug_device *dev, unsigned size, unsigned channel)
{
    unsigned len;
    const struct debug_device *selected;
    const struct debug_device *end;
    char *arg;

    end = (void *) ((uint8_t *) dev + size);
    arg = debug_opt[channel];
    if (arg == NULL) {
        for (;;) {
            if (dev >= end)
                return;
            if (dev->defaults[channel] != NULL)
                break;
            ++dev;
        }
        set_debug(channel, dev, "");
        return;
    }
    selected = NULL;
    for (;;) {
        const char *defaults;

        if (dev >= end)
            break;
        defaults = dev->defaults[channel];
        if (defaults != NULL) {
            char ch;

            len = strlen(dev->name);
            ch = arg[len];
            if ((memcmp(arg, dev->name, len) == 0)
                && (ch == ' ' || ch == '\t' || ch == '\0' || ch == '.')) {
                selected = dev;
                arg += len;
                if (*arg == '.')
                    ++arg;
                break;
            }
            if ((selected == NULL) && (defaults[0] != '\0')) {
                // If we don't match any of the names, the first device
                // in the list with actual options is the default device.
                selected = dev;
            }
        }
        ++dev;
    }
    if (selected != NULL)
        set_debug(channel, selected, arg);
}

void select_debug(const struct debug_device *dev, unsigned size)
{
    select_one(dev, size, 0);
    if (debug_opt[1] != NULL)
        select_one(dev, size, 1);
}
