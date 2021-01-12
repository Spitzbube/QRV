/**
 * \file stddef.h
 *
 * Standard definitions, based on the GNU C library.
 *
 * \license GNU LGPL 2.1
 *
 */

#ifndef _STDDEF_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#if !defined(__cplusplus) || defined(_STD_USING) || defined(_GLOBAL_USING)
#define _STDDEF_H_INCLUDED
#endif

#ifndef _STDDEF_H_DECLARED
#define _STDDEF_H_DECLARED

#ifdef __SIZE_TYPE__
    typedef __SIZE_TYPE__ size_t;
#undef __SIZE_TYPE__
#endif

#ifdef __PTRDIFF_TYPE__
    typedef __PTRDIFF_TYPE__ ptrdiff_t;
#undef __PTRDIFF_TYPE__
#endif

#if defined(__WCHAR_T)
    typedef __WCHAR_T wchar_t;
#undef __WCHAR_T
#endif

#ifndef NULL
#define NULL   _NULL
#endif

#define offsetof(__typ,__id) __builtin_offsetof(__typ,__id)

/*
 * Neither the C nor C++ standards, nor POSIX, specifies wint_t.
 * We assume that stddef.h will define the macro _WINT_T if and only if
 * it provides wint_t, and conversely, that it will avoid providing
 * wint_t if _WINT_T is already defined.  */
#ifndef _WINT_T
#define _WINT_T 1

/*
 * Integral type unchanged by default argument promotions that can
 * hold any value corresponding to members of the extended character
 * set, as well as at least one value that does not correspond to any
 * member of the extended character set.
 */
#ifndef __WINT_TYPE__
# define __WINT_TYPE__ unsigned int
#endif

#endif /* _WINT_T */

typedef __WINT_TYPE__ wint_t;

#endif

#endif
