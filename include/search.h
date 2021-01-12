/**
 * \file search.h
 *
 * Declarations for System V style searching functions.
 *
 * \copyright (C) 1995-2020 Free Software Foundation, Inc.
 * \license GNU LGPL 2.1
 * \note This file is part of the GNU C Library.
 *
 */

#ifndef _SEARCH_H
#define _SEARCH_H

#include <sys/platform.h>

typedef struct _entry {
    char *key;
    void *data;
} ENTRY;

typedef enum { FIND, ENTER } ACTION;
typedef enum { preorder, postorder, endorder, leaf } VISIT;

__BEGIN_DECLS extern ENTRY *hsearch(ENTRY __item, ACTION __action);
extern void *lfind(const void *__key, const void *__base, size_t *__num, size_t __width,
                   int (*__compare)(const void *, const void *));
extern void *lsearch(const void *__key, void *__base, size_t *__num, size_t __width,
                     int (*__compare)(const void *, const void *));
extern void *tdelete(const void *__key, void **__rootp,
                     int (*__compar)(const void *, const void *));
extern void *tfind(const void *__key, void *const *__rootp,
                   int (*__compar)(const void *, const void *));
extern void *tsearch(const void *__key, void **__rootp,
                     int (*__compar)(const void *, const void *));
extern int hcreate(_CSTD size_t __nel);
extern void hdestroy(void);

#if defined(__EXT_XOPEN_EX)
extern void insque(void *__element, void *__pred);
extern void remque(void *__element);
#endif
extern void twalk(const void *__root, void (*__action)(const void *, VISIT, int));

__END_DECLS

#endif
