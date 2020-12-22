/**
 * \brief Initialize architecture-specific parts of syspage.
 *
 * \license Apache 2.0 (http://www.apache.org/licenses/LICENSE-2.0)
 *
 * \copyright (c) 2008 QNX Software Systems.
 */

#include <kernel/startup.h>

void cpu_init_syspage_memory()
{
    set_syspage_section(&lsp.cpu.riscv_cpu, sizeof(*lsp.cpu.riscv_cpu.p));
}

struct syspage_entry *cpu_alloc_syspage_memory(paddr_t *cpupagep, paddr_t *syspagep,
                                               unsigned spsize)
{
    struct syspage_entry *sp = lsp.syspage.p;
    struct system_private_entry *private;
    unsigned size;
    unsigned cpsize;
    paddr32_t syspage_paddr;
    unsigned spacing;

#define	SP_OFFSET(field)	PTR_DIFF(lsp.cpu.field.p, sp)
#define	INIT_ENTRY(_cpu, _field) \
		sp->_cpu._field.entry_size = lsp.cpu._cpu##_##_field.size; \
		sp->_cpu._field.entry_off  = SP_OFFSET(_cpu##_##_field)

    spsize = ROUND(spsize, sizeof(uint64_t));
    if ((paddr_bits == 32) && sp->num_cpu == 1) {
        spacing = sizeof(struct cpupage_entry);
    } else {
        /*
         * WARNING: we assume SMP processor has physical cache.
         *          We allocate the cpupages in contiguous memory so that
         *          the kernel's cpypageptr[] pointers point at virtually
         *          contiguous mappings into the physical pages.
         *          The user _cpupage_ptr is a different virtual address
         *          where the same virtual address on each cpu maps the
         *          different physical address for that cpu's cpupage.
         */
        spacing = __PAGESIZE;
        spsize = ROUND(spsize, __PAGESIZE);
    }
    cpsize = sp->num_cpu * spacing;

    /*
     * Allocate the system page (and cpupage entries) and save it away.
     * The system page must be 4K aligned in a virtual system
     */
    size = spsize + cpsize;

    syspage_paddr = alloc_ram(NULL_PADDR, size, lsp.system_private.p->pagesize);
    if (syspage_paddr == NULL_PADDR32) {
        crash("could not allocate 0x%l bytes for syspage/cpupage\n", size);
    }

    private = lsp.system_private.p;

    //TODO: add
    private->kern_syspageptr = riscv_map(~0L, ((paddr_t) syspage_paddr), size, RISCV_MAP_SYSPAGE);
    private->kern_cpupageptr = private->kern_syspageptr + spsize;

    if (paddr_bits != 32) {
        // For LPAE, we don't have an option for kern-rw/user-ro mapping
        // So we'll create a separate user-ro/kern-ro mapping for syspage
        private->user_syspageptr =  riscv_map(~0L, ((paddr_t) syspage_paddr), size, RISCV_MAP_SYSPAGE_RO);
    } else {
        private->user_syspageptr = private->kern_syspageptr;
    }

    int i;
    paddr32_t cpupaddr = syspage_paddr + spsize;
    int cpu_map_flag;

    if (paddr_bits != 32) {
        cpu_map_flag = RISCV_MAP_SYSPAGE_RO;
    } else {
        cpu_map_flag = RISCV_MAP_SYSPAGE;
    }

    /*
     * We have mapped the trap vector page using a per-cpu page table
     */
    private->user_cpupageptr = TOPTR(trap_vectors + __PAGESIZE);

    for (i = 0; i < sp->num_cpu; i++, cpupaddr += spacing) {
        riscv_map_cpu(i, (uintptr_t) private->user_cpupageptr, (paddr_t) cpupaddr, cpu_map_flag);
    }

    /*
     * Map the page directory pages so the memmgr can keep all the cpus'
     * page table mappings consistent.
     */
    //TODO

    private->cpupage_spacing = spacing;

    *syspagep = syspage_paddr;
    *cpupagep = syspage_paddr + spsize;

    sp->riscv.startup_base = startup_base;
    sp->riscv.startup_size = startup_size;

    INIT_ENTRY(riscv, cpu);

    return ((void *) syspage_paddr);
}

/*
 * Run startup with MMU disabled.
 */
void cpu_write_syspage_memory(paddr_t sysp_paddr, unsigned sysp_size)
{

}

