/**
 * \file stdbool.h
 *
 * \brief Definition of the bool type.
 */

#ifndef _STDBOOL_H
#define _STDBOOL_H

#if (__GNUC__ < 8) || (__STDC_VERSION__ < 199901L)
#error C99 and GCC8+ required
#endif

#define bool    _Bool
#define false   0
#define true    1

#endif
