/**
 * \file  sys/gcc_lp64.h
 *
 * \brief Definitions for GCC compiler, LP64 model.
 *
 * The only symbols made visible by this header are OS/compiler reserved symbols.
 *
 * \license
 * Copyright 2007, 2008, QNX Software Systems. All Rights Reserved.
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
 */

#ifndef __GCC_LP64_H_INCLUDED
#define __GCC_LP64_H_INCLUDED

#if (__GNUC__ < 8)
#error GNU C compiler is too old (must be at least 8.x)
#endif

#if __has_attribute(__fallthrough__)
# define fallthrough    __attribute__((__fallthrough__))
#else
# define fallthrough    do {} while (0) /* fallthrough */
#endif

#ifndef __PLATFORM_H_INCLUDED
#error __FILE__ should not be included directly.
#endif

#ifdef __CHAR_UNSIGNED__
#undef __CHAR_SIGNED__
#else
#ifndef __CHAR_SIGNED__
#define __CHAR_SIGNED__
#endif
#endif

#ifdef __GNUG__
#undef _NULL
#define _NULL __null
#endif

#if !defined (__cplusplus) && defined(__WCHAR_TYPE__)
#undef __WCHAR_T
#define __WCHAR_T __WCHAR_TYPE__
#endif

#ifdef __WCHAR_MAX__
#undef _WCMAX
#define _WCMAX __WCHAR_MAX__
#endif

#if !defined(__BIGENDIAN__) && !defined(__LITTLEENDIAN__)
#error Endian not defined
#endif

#ifndef _NO_RETURN
#define _NO_RETURN(fun) void fun __attribute__((__noreturn__))
#endif

#ifndef __CDEFS_H_INCLUDED
#include <sys/cdefs.h>
#endif

/* Use LP64 model */
#define __INT_BITS__	32
#define __PTR_BITS__	64
#define __LONG_BITS__	64

#if defined(__X86__)
#define __LONGDOUBLE_BITS__		80
#elif defined(__PPC__) || defined(__MIPS__) || defined(__SH__) || defined(__ARM__) || defined(__SPARC__) || defined(__RISCV__)
#define __LONGDOUBLE_BITS__		64
#else
#error not configured for CPU
#endif

typedef int _GCC_ATTR_ALIGN_64t __attribute__((__mode__(__DI__)));
typedef unsigned int _GCC_ATTR_ALIGN_u64t
    __attribute__((__mode__(__DI__)));
typedef _GCC_ATTR_ALIGN_64t _Int64t __attribute__((__aligned__(8)));
typedef _GCC_ATTR_ALIGN_u64t _Uint64t __attribute__((__aligned__(8)));

typedef unsigned _GCC_ATTR_ALIGN_u32t;
typedef int _GCC_ATTR_ALIGN_32t;
typedef _GCC_ATTR_ALIGN_u32t _Uint32t __attribute__((__aligned__(4)));
typedef _GCC_ATTR_ALIGN_32t _Int32t __attribute__((__aligned__(4)));

typedef int _GCC_ATTR_ALIGN_8t __attribute__((__mode__(__QI__)));
typedef unsigned int _GCC_ATTR_ALIGN_u8t __attribute__((__mode__(__QI__)));
typedef _GCC_ATTR_ALIGN_8t _Int8t __attribute__((__aligned__(1)));
typedef _GCC_ATTR_ALIGN_u8t _Uint8t __attribute__((__aligned__(1)));

typedef int _Intptrt __attribute__((__mode__(__pointer__)));
typedef unsigned int _Uintptrt __attribute__((__mode__(__pointer__)));

typedef int _GCC_ATTR_ALIGN_16t __attribute__((__mode__(__HI__)));
typedef unsigned int _GCC_ATTR_ALIGN_u16t __attribute__((__mode__(__HI__)));
typedef _GCC_ATTR_ALIGN_16t  _Int16t __attribute__((__aligned__(2)));
typedef _GCC_ATTR_ALIGN_u16t _Uint16t __attribute__((__aligned__(2)));

typedef _Uint64t _Uintptrt;
typedef _Int64t _Intptrt;

__extension__ typedef long long _Longlong;
__extension__ typedef unsigned long long _ULonglong;

/*
 * This is to override the gcc local include files to use
 * our definition of the following types
 */
#define _GCC_PTRDIFF_T
#define _GCC_SIZE_T
#define _GCC_WCHAR_T

/*
 * -ansi		defines __STRICT_ANSI__
 * -traditional		undefines __STDC__ and __STDC_VERSION__
 */
#if defined(__STDC__) && !defined(__STRICT_ANSI__)
#define __EXT
#endif

#ifndef __GNUC_VA_LIST
#define __GNUC_VA_LIST
typedef __builtin_va_list __gnuc_va_list;

typedef __gnuc_va_list __NTO_va_list;
#define __NTO_va_start_stdarg(__p1,__p2)  __builtin_va_start(__p1,__p2)
#define __NTO_va_arg(__p1, __p2)          __builtin_va_arg(__p1,__p2)
#define __NTO_va_end(__p1)                __builtin_va_end(__p1)
#define __NTO_va_copy(__d,__s)            __builtin_va_copy(__d,__s)
#endif

#if _FILE_OFFSET_BITS - 0 == 64
#undef __ALIAS64
#define __ALIAS64(n)	__asm(n)
#endif

#endif
