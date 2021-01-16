/**
 * \file sys/_multibytetypes.h
 *
 * Definitions related to multibyte character and string types.
 *
 * \author Yuri Zaporozhets <r_tty@yahoo.co.uk>
 * \license GNU GPL 2.0
 */

#ifndef _SYS_MULTIBYTETYPES_H
#define _SYS_MULTIBYTETYPES_H

#include <stddef.h>

#if !defined(__WCHAR_TYPE__) || !defined(__WINT_TYPE__)
#error __WCHAR_TYPE__ and __WINT_TYPE__ must be defined in stddef.h provided by GCC
#endif

typedef __WCHAR_TYPE__ wchar_t;
typedef __WINT_TYPE__  wint_t;

/* Conversion state information */
typedef struct {
    int __count;
    union {
        wint_t __wch;
        unsigned char __wchb[4];
    } __value;                  // Value so far
} mb_state_t;

typedef mb_state_t _mbstate_t;

/* Iconv descriptor type */
typedef void *iconv_t;

#endif
