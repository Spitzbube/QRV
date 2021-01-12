/**
 * \file assert.h
 *
 * Implementation of assert() macro
 *
 * \copyright (c) 2019 Free Software Foundation, Inc.
 * \license GNU LGPL 2.1
 * \note This file is part of the GNU C Library.
 *
 * ISO C99 Standard: 7.2. Diagnostics: <assert.h>
 */

#undef assert

#ifdef NDEBUG
#define assert(x) ((void)0)
#else

#define assert(__expr) ((__expr) ? (void) 0 : __assert_fail(#__expr, __FILE__, __LINE__, __func__))

__BEGIN_DECLS
extern void __assert_fail(const char *__expr, const char *__file, unsigned __line,
                          const char *__func);
__END_DECLS

#endif
