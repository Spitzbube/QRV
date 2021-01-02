
#include <startup.h>

paddr_t page_directory;

/**
 * \brief Initialize the page directory.
 */
static void riscv_init_pgdir()
{
    unsigned num = lsp.syspage.p->num_cpu;
    set_syspage_section(&lsp.cpu.pgdir, sizeof(paddr_t) * num);

    /* Page directory size is one page (512 entries, 8 bytes each) */
    unsigned pd_size = __PAGESIZE;
    page_directory = calloc_ram(pd_size * num, __PAGESIZE);
}

void init_mmu(void)
{
    kprintf("%s called\n", __func__);
    riscv_init_pgdir();
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
    return paddr;
}
