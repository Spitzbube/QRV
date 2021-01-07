/*
/* lutil.h -- utilities

   This file is part of the UCL real-time data compression library.

   Copyright (C) 1996-2000 Markus Franz Xaver Johannes Oberhumer
 * \license GNU GPL 2.0

   Markus F.X.J. Oberhumer
   markus.oberhumer@jk.uni-linz.ac.at
 */


#include <stdio.h>
#include <stddef.h>
#if !defined(NO_STDLIB_H)
#  include <stdlib.h>
#endif
#include <string.h>
#include <ctype.h>
#if defined(HAVE_UNISTD_H) || defined(__DJGPP__) || defined(__EMX__)
#  include <unistd.h>
#elif defined(__CYGWIN__) || defined(__CYGWIN32__) || defined(__MINGW32__)
#  include <unistd.h>
#endif
#if defined(HAVE_STAT)
#  include <sys/types.h>
#  include <sys/stat.h>
#endif

#include <ucl/uclconf.h>
#include <ucl/uclutil.h>


/* some systems have a xmalloc in their C library... */
#undef xmalloc
#undef xfree
#undef xread
#undef xwrite
#undef xputc
#undef xgetc
#undef xread32
#undef xwrite32
#define xmalloc         my_xmalloc
#define xfree           my_xfree


#define HEAP_ALLOC(var,size) \
    long __UCL_MMODEL var [ ((size) + (sizeof(long) - 1)) / sizeof(long) ]


/*
vi:ts=4:et
*/

