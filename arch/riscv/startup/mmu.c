
#include <kernel/startup.h>

paddr_t startup_base;
unsigned startup_size;

void init_mmu(void)
{
    kprintf("%s called\n", __func__);
}

/*
 * Map [paddr, paddr+size) with RISC-V specific attributes in flags.
 * If vaddr is ~0, we assign the address, otherwise, the mapping
 * will be made at the specified virtual address.
 */
uintptr_t riscv_map(uintptr_t vaddr, paddr_t paddr, size_t size, int flags)
{
    //TODO
    kprintf("%s called\n", __func__);
    return 0;
}
