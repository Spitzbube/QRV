/**
 * \file dlfcn.h
 *
 * User functions for run-time dynamic loading.
 * \copyright POSIX definitions (c) 2019 Free Software Foundation, Inc.
 *            QNX-specific definitions (c) 2007 QNX Software Systems.
 * \license GNU LGPL 2.1
 */

#ifndef _DLFCN_H
#define _DLFCN_H

#define __need_size_t
#include <stddef.h>

#include <sys/platform.h>

/* Structure containing information about object searched using dladdr() */
typedef struct dl_info {
    const char *dli_fname;
    void *dli_fbase;
    const char *dli_sname;
    void *dli_saddr;
} Dl_info;

__BEGIN_DECLS

/* The MODE argument to dlopen() */
#define RTLD_LAZY       0x0001
#define RTLD_NOW        0x0002
#define RTLD_NOLOAD     0x0004
#define RTLD_GLOBAL     0x0100          // Make all symbols in loaded module visible
#define RTLD_LOCAL      0x0200          // TODO: 0 in glibc
#define RTLD_GROUP      0x0400          // Extension (non-standard)
#define RTLD_WORLD      0x0800          // Extension (non-standard)
#define RTLD_NODELETE   0x1000          // Don't delete object when closed

#ifdef __EXT_QNX
#define RTLD_NOSHARE    0x2000          // Extension (non-standard)
#endif

#define RTLD_DEFAULT    ((void *) -2)
#define RTLD_NEXT       ((void *) -3)

extern char *dlerror(void);
extern void *dlopen(const char *__pathname, int __mode);
extern void *dlsym(void *__handle, const char *__name);
#ifdef __EXT_UNIX_MISC
extern int dladdr(void *__addr, Dl_info * __info);
#endif

#ifdef __EXT_QNX
extern int _dladdr(void *__addr, Dl_info * __info);
#endif

extern int dlclose(void *__handle);

__END_DECLS

#endif
