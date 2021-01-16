/**
 * \file nano_alloc.c
 *
 * Basic memory manager for the kernel.
 *
 * \copyright 2007, QNX Software Systems. All Rights Reserved.
 *
 * 64-bit conversion (c) 2021 Yuri Zaporozhets <r_tty@yahoo.co.uk>
 *
 * \license QNX NCEULA 1.01
 *          http://www.qnx.com/legal/licensing/dev_license/eula/nceula1_01.html
 */

#include <unistd.h>
#include "externs.h"
#include "kernel/mempart.h"
#include <sys/mman.h>

static int add_mem(struct asinfo_entry *as, char *name, void *data)
{
    (void) emm_pmem_add(as->start, (as->end - as->start) + 1);
    return 1;
}

void emm_init_mem(int phase)
{
    if (phase == 0) {
        walk_asinfo("sysram", add_mem, NULL);
    }
}
 * This file may contain contributions from others.  Please review this entire
 * file for other proprietary rights or license notices, as well as the QNX
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 * $
 */

static unsigned _dummy_alloc(unsigned size, void **addr)
{
    // Can't get anything more from the system, since it's all been
    // put in the heap.
    return 0;
}

int
emm_mmap(PROCESS * prp, uintptr_t addr, size_t len, int prot, int flags,
         tPathMgrObject * obpe, uint64_t boff, unsigned align, unsigned preload, int fd,
         void **vaddr, size_t *size, part_id_t mpart_id)
{
    unsigned off = (unsigned) boff;

    // NYI: Doesn't handle PROT_NOCACHE
    // Physical can't do guardpages, so remove them from the len
    if (flags & MAP_STACK) {
        if (off >= len) {
            return EINVAL;
        }
        len -= off;
    }
    // Allocate memory
    if (flags & MAP_ANON) {
        len = (len + memmgr.pagesize - 1) & ~(memmgr.pagesize - 1);
        for (;;) {
            *vaddr = _sreallocfunc(0, 0, len, _dummy_alloc);
            if (*vaddr != NULL)
                break;
            if (!purger_invoke(len)) {
                return ENOMEM;
            }
        }
        *size = len;
        return EOK;
    }
    // since physical == virtual, return offset
    if ((flags & (MAP_PHYS | MAP_TYPE)) == (MAP_PHYS | MAP_SHARED)) {
        *vaddr = (void *) CPU_P2V(off);
        *size = len;
        return EOK;
    }

    return EINVAL;
}

int emm_munmap(PROCESS * prp, uintptr_t addr, size_t len, int flags, part_id_t mpart_id)
{
    MemobjDestroyed((void *) _syspage_ptr, CPU_V2P(addr), CPU_V2P(addr) + len - 1, 0, 0);
    _sfree((void *) addr, len);
    return EOK;
}

#define MEM_ALIGNMENT	(sizeof(uint64_t))
int emm_pmem_add(paddr_t start, paddr_t len)
{
    uintptr_t addr;
    uintptr_t end;

    // adjust to make sure addr and size fits within a page
    addr = ((uintptr_t) start + MEM_ALIGNMENT - 1) & ~(MEM_ALIGNMENT - 1);
    end = ((uintptr_t) (start + len) & ~(MEM_ALIGNMENT - 1));

    if ((end > addr) && (end != 0)) {
        _sfree((void *) CPU_P2V(addr), end - addr);
    }
    return EOK;
}

tPathMgrObject *emm_vaddr_to_memobj(PROCESS * prp, void *vaddr, unsigned *offset, int create)
{
    *offset = CPU_V2P(vaddr);
    return (void *) _syspage_ptr;
}
