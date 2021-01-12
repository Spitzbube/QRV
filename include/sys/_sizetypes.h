/**
 * \file sys/_sizetypes.h
 *
 * Definitions of size types, based on gcc-provided macros.
 *
 * \license GNU GPL 2.0
 */

#ifndef _SYS_SIZETYPES_T
#define _SYS_SIZETYPES_T

#include <stddef.h>

#ifndef __SIZE_TYPE__
#error __SIZE_TYPE__ must be defined in stddef.h provided by GCC
#endif

typedef __SIZE_TYPE__ size_t;
/* Define ssize_t based on size_t by flipping "signed" and "unsigned" */
#define unsigned signed
typedef __SIZE_TYPE__ ssize_t;
#undef unsigned

#endif
