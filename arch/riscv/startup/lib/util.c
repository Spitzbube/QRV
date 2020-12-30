/**
 * \brief Various utility routines.
 *
 * \license Apache 2.0 (http://www.apache.org/licenses/LICENSE-2.0)
 *
 * \copyright (c) 2008 QNX Software Systems.
 */

#include <startup.h>

/**
 * \brief Convert a string to a number.
 *
 * \note This function, in addition to straight numeric massaging,
 *        accepts suffixes (like 'K' or 'G') to scale the quantity.
 */
paddr_t getsize(char *str, char **dst)
{
    paddr_t v;

    v = strtopaddr(str, &str, 0);

    switch (*str) {
    case 'G':
    case 'g':
        v *= 1024UL;
        fallthrough;
    case 'M':
    case 'm':
        v *= 1024UL;
        fallthrough;
    case 'K':
    case 'k':
        v *= 1024UL;
        ++str;
        break;
    }
    if (dst != NULL)
        *dst = str;
    return v;
}
