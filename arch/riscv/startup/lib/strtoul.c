/**
 * \brief Minimalist strtoul() implementation.
 *
 * \license Apache 2.0 (http://www.apache.org/licenses/LICENSE-2.0)
 *
 * \copyright (c) 2008 QNX Software Systems.
 */

#include <kernel/startup.h>

/*
 * Provide a simpler versions of macros/functions in comparison to libc.
 */
#define hexstr(p) (p[0] == '0' && (p[1] == 'x' || p[1] == 'X'))

static int radix_value(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;
    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    return 37;
}

paddr_t strtopaddr(const char *nptr, char **endptr, int base)
{
    const char *p;
    const char *startp;
    int digit;
    paddr_t value;

    if (endptr != NULL)
        *endptr = (char *) nptr;
    p = nptr;
    if (base == 0) {
        if (hexstr(p))
            base = 16;
        else if (*p == '0')
            base = 8;
        else
            base = 10;
    }
    if (base == 16) {
        if (hexstr(p))
            p += 2;             /* skip over '0x' */
    }
    startp = p;
    value = 0;
    for (;;) {
        digit = radix_value(*p);
        if (digit >= base)
            break;
        value = value * base + digit;
        ++p;
    }
    if (p == startp)
        p = nptr;
    if (endptr != NULL)
        *endptr = (char *) p;
    return value;
}

unsigned long strtoul(const char *nptr, char **endptr, int base)
{
    // Assuming that sizeof(paddr_t) >= sizeof(unsigned long)
    return strtopaddr(nptr, endptr, base);
}
