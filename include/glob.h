/**
 * \file glob.h
 *
 * Definitions and prototypes for glob() function.
 *
 * \copyright (C) 1991-2020 Free Software Foundation, Inc.
 *
 * \license GNU LGPL 2.1
 * \note This file is part of the GNU C Library.
 */

#ifndef _GLOB_H_INCLUDED
#define _GLOB_H_INCLUDED

#include <sys/cdefs.h>

/* Bits set in the FLAGS argument to glob() */
#define	GLOB_ERR	(1 << 0)    /* Return on read errors */
#define	GLOB_MARK	(1 << 1)    /* Append a slash to each name */
#define	GLOB_NOSORT	(1 << 2)    /* Don't sort the names */
#define	GLOB_DOOFFS	(1 << 3)    /* Insert PGLOB->gl_offs NULLs */
#define	GLOB_NOCHECK	(1 << 4)    /* If nothing matches, return the pattern */
#define	GLOB_APPEND	(1 << 5)    /* Append to results of a previous call */
#define	GLOB_NOESCAPE	(1 << 6)    /* Backslashes don't quote metacharacters */
#define	GLOB_PERIOD	(1 << 7)    /* Leading `.' can be matched by metachars */
#define	__GLOB_FLAGS	(GLOB_ERR|GLOB_MARK|GLOB_NOSORT|GLOB_DOOFFS| \
			 GLOB_NOESCAPE|GLOB_NOCHECK|GLOB_APPEND|     \
			 GLOB_PERIOD|GLOB_ALTDIRFUNC|GLOB_BRACE|     \
			 GLOB_NOMAGIC|GLOB_TILDE|GLOB_QUOTE)
#if defined(__EXT_POSIX2)
#define	GLOB_MAGCHAR	(1 << 8)    /* Set in gl_flags if any metachars seen */
#define GLOB_ALTDIRFUNC	(1 << 9)    /* Use gl_opendir et al functions */
#define GLOB_BRACE	(1 << 10)   /* Expand "{a,b}" to "a" "b" */
#define GLOB_NOMAGIC	(1 << 11)   /* If no magic chars, return the pattern */
#define GLOB_TILDE	(1 << 12)   /* Expand ~user and ~ to home directories */
#endif

#ifdef __EXT_QNX
#define	GLOB_QUOTE	(1 << 15)   /* Quote special chars with \ */
#endif

/* Error returns from glob() */
#define	GLOB_NOSPACE	1       /* Ran out of memory */
#define	GLOB_ABEND	2       /* Read error */
#define	GLOB_NOMATCH	3       /* No matches found */

struct _dir;
struct dirent;
struct stat;
typedef struct {
    size_t gl_pathc;      /* Count of paths matched by the pattern */
    int gl_matchc;        /* Count of paths matching pattern */
    char **gl_pathv;      /* List of matched pathnames */
    size_t gl_offs;       /* Slots to reserve in `gl_pathv' */
    int gl_flags;         /* Set to FLAGS, maybe | GLOB_MAGCHAR */

    /* Copy of errfunc parameter to glob. */
    int (*gl_errfunc)(const char *, int);

    /*
     * Alternate filesystem access methods for glob; replacement
     * versions of closedir(3), readdir(3), opendir(3), stat(2)
     * and lstat(2).
     *
     * Used If GLOB_ALTDIRFUNC flag is set.
     */
    void (*gl_closedir)(void *);
    struct dirent *(*gl_readdir) (void *);
    void *(*gl_opendir)(const char *);
    int (*gl_lstat)(const char *, struct stat *);
    int (*gl_stat)(const char *, struct stat *);
} glob_t;

__BEGIN_DECLS

/*
 * Do glob searching for PATTERN, placing results in PGLOB.
 *  The bits defined above may be set in FLAGS.
 *  If a directory cannot be opened or read and ERRFUNC is not nil,
 *  it is called with the pathname that caused the error, and the
 *  `errno' value from the failing call; if it returns non-zero
 *  `glob' returns GLOB_ABEND; if it returns zero, the error is ignored.
 *  If memory cannot be allocated for PGLOB, GLOB_NOSPACE is returned.
 *  Otherwise, `glob' returns zero.
 */
extern int glob(const char *__pattern, int __flags,
                    int (*__errfunc)(const char *, int), glob_t * __pglob);

/* Free storage allocated in PGLOB by a previous `glob' call.  */
extern void globfree(glob_t * __pglob);

__END_DECLS
#endif
