/*
 * Copyright 2007, QNX Software Systems. All Rights Reserved.
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

#include <sys/mman.h>
#include <unistd.h>
#include "externs.h"

void smm_aspace(PROCESS * actprp, PROCESS ** pactprp)
{
    *pactprp = actprp;
}

void smm_configure(char *cfg)
{
}

int smm_debuginfo(PROCESS * prp, struct _mem_debug_info *msg)
{
    return ENOSYS;
}

int smm_dup(PROCESS * pprp, PROCESS * prp)
{
    return ENOSYS;
}

int smm_fault(struct fault_info *info)
{
    return MAKE_SIGCODE(SIGSEGV, SEGV_MAPERR, FLTPAGE);
}

int smm_madvise(PROCESS * prp, uintptr_t addr, size_t len, int flags)
{
    return EOK;
}

size_t
smm_mapinfo(PROCESS * prp, uintptr_t vaddr, struct _procfs_map_info *mip,
            struct _procfs_debug_info *mdp, size_t dbginfo_pathlen, OBJECT ** obpp, int *fdp,
            size_t *contigp)
{
    return 0;
}

int
smm_map_xfer(PROCESS * actprp, PROCESS * prp, IOV ** piov, int *pparts, int *poff, IOV * niov,
             int *pnparts, unsigned flags)
{
    IOV *iov;
    int parts, bytes, off;

    iov = *piov;
    parts = *pparts;
    off = *poff;

    while (off >= GETIOVLEN(iov)) {
        off -= GETIOVLEN(iov);
        if (--parts == 0) {
            *pnparts = 0;
            *pparts = 0;
            return 0;
        }
        ++iov;
    }

    *pnparts = parts;
    bytes = 0;
    SETIOV(niov, (uintptr_t) GETIOVBASE(iov) + off, GETIOVLEN(iov) - off);
    bytes += GETIOVLEN(niov);
    parts--;
    iov++;
    niov++;
    for (; parts; parts--) {
        bytes += GETIOVLEN(iov);
        *niov++ = *iov++;
    }

    *pparts = 0;

    return bytes;
}

int smm_mcreate(PROCESS * prp)
{
    return EOK;
}

void smm_mdestroy(PROCESS * prp)
{
}

int smm_memobj_phys(OBJECT * obp, paddr_t pa)
{
    return ENOSYS;
}

int smm_mlock(PROCESS * prp, uintptr_t addr, size_t len, int flags)
{
    return EOK;
}

int smm_mprotect(PROCESS * prp, uintptr_t addr, size_t len, int prot)
{
    return ENOSYS;
}

int smm_msync(PROCESS * prp, uintptr_t addr, size_t len, int flags)
{
    return ENOSYS;
}

int smm_munlock(PROCESS * prp, uintptr_t addr, size_t len, int flags)
{
    return EOK;
}

int smm_resize(OBJECT * obp, size_t size)
{
    return ENOSYS;
}

int smm_swapper(PROCESS * prp, unsigned *offset, size_t len, int action)
{
    return ENOSYS;
}

unsigned
smm_vaddrinfo(PROCESS * prp, uintptr_t vaddr, paddr_t * paddrp, size_t *lenp, unsigned flags)
{
    if (CPU_VADDR_IN_RANGE(vaddr)) {
        *paddrp = CPU_V2P(vaddr);
        if (lenp != NULL)
            *lenp = (paddr_t) 0 - *paddrp;
        return PROT_READ | PROT_WRITE | PROT_EXEC;
    }
    return PROT_NONE;
}

int smm_validate(PROCESS * prp, uintptr_t addr, size_t len, int flags)
{
    return EOK;
}
