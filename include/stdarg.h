/**
 * \file stdarg.h
 *
 * Variable argument macros definitions for use with variable argument lists.
 *
 * \copyright (c) 2019 Free Software Foundation, Inc.
 * \note This file is part of GNU C Library.
 * \license GNU LGPL 2.1
 */

#ifndef _STDARG_H
#define _STDARG_H

typedef __builtin_va_list va_list;
#define va_start(__p1,__p2)  __builtin_va_start(__p1,__p2)
#define va_arg(__p1, __p2)   __builtin_va_arg(__p1,__p2)
#define va_end(__p1)         __builtin_va_end(__p1)
#define va_copy(__d,__s)     __builtin_va_copy(__d,__s)

#endif
