/**
 * \brief System page routines.
 *
 * \license Apache 2.0 (http://www.apache.org/licenses/LICENSE-2.0)
 *
 * \copyright (c) 2008 QNX Software Systems.
 */

#include <startup.h>

static unsigned fixed_size;

paddr_t syspage_paddr;
struct local_syspage lsp;

struct unknown;
typedef SYSPAGE_TYPED_SECTION(struct unknown, __attribute__((__may_alias__)) local_section);

#define SECTION_START	((local_section *)(void *)&lsp)
#define SECTION_END	((local_section *)(void *)(&lsp+1))

/**
 * \brief TODO
 *
 * \note We keep the maximum size we're allowed to grow things in the
 *       lsp.syspage->p.size field - we'll set it to it's proper value
 *       once we're done, that will also disallow any further growing since
 *       it's going to be less than the total_size.
 */
void *grow_syspage_section(void *p, unsigned add)
{
    local_section *sect = p;
    local_section *s2;
    uint8_t *bottom;
    unsigned new_size, max_size, len;
    uint8_t *new;

    //ultra_verbose("%s: %p, add=%d\n", __func__, p, add);

#ifdef CONFIG_MINIDRIVER
    mdriver_check();
#endif
    if (add > 0) {
        add = ROUND(add, sizeof(uint64_t));
        new_size = lsp.syspage.p->total_size + add;
        max_size = lsp.syspage.p->size;
        if (new_size > max_size) {
            crash("Syspage memory request of %d exceeds maximum of %d bytes.\n",
                  new_size, max_size);
        }
        bottom = (uint8_t *) sect->p + sect->size;
        for (s2 = SECTION_START; s2 < SECTION_END; ++s2) {
            if ((s2 != sect) && ((void *) s2->p >= (void *) bottom)) {
                s2->p = (void *) ((uint8_t *) s2->p + add);
            }
        }
        new = bottom + add;
        len = lsp.syspage.p->total_size - PTR_DIFF(bottom, lsp.syspage.p);
        memmove(new, bottom, len);
        memset(bottom, 0, add);
        sect->size += add;
        lsp.syspage.p->total_size = new_size;
    }
    return sect->p;
}

void *set_syspage_section(void *p, unsigned size)
{
    local_section *sect = p;

    size = ROUND(size, sizeof(uint64_t));
    sect->p = (void *) ((uint8_t *) lsp.syspage.p + fixed_size);
    fixed_size += size;
    return grow_syspage_section(p, size);
}

void init_syspage_memory(void *base, unsigned max_size)
{
    local_section *sect;
    unsigned spsize = ROUND(sizeof(*lsp.syspage.p), sizeof(uint64_t));

    pr_debug("%s\n", __func__);

    for (sect = SECTION_START; sect < SECTION_END; ++sect) {
        sect->p = (void *) ((uint8_t *) base + spsize);
        sect->size = 0;
    }
    lsp.syspage.p = base;
    lsp.syspage.size = spsize;
    memset(base, 0, spsize);
    fixed_size = spsize;
    lsp.syspage.p->total_size = spsize;
    lsp.syspage.p->size = max_size;

    grow_syspage_section(&lsp.typed_strings, sizeof(uint32_t));
    grow_syspage_section(&lsp.strings, sizeof(char));
    grow_syspage_section(&lsp.hwinfo, sizeof(struct hwi_prefix));

    lsp.syspage.p->num_cpu = 1;
    cpu_init_syspage_memory();

    hwi_default();
}

void reloc_syspage_memory(void *base, unsigned max_size)
{
    local_section *sect;
    ptrdiff_t diff;

    memmove(base, lsp.syspage.p, lsp.syspage.p->total_size);
    diff = PTR_DIFF(base, lsp.syspage.p);
    //TODO: callout removal
    for (sect = SECTION_START; sect < SECTION_END; ++sect) {
        sect->p = (void *) ((uint8_t *) sect->p + diff);
    }
    lsp.syspage.p->size = max_size;
}

void alloc_syspage_memory(void)
{
    struct syspage_entry *sp;
    paddr_t cpupage_paddr;
    unsigned i;
    struct cpupage_entry cpu;
    unsigned spsize;

    /* Allow for four more asinfo entries in case the syspage allocation(s)
     * splits address range(s).
     */
    spsize = lsp.syspage.p->total_size + 4 * sizeof(struct asinfo_entry);

    _syspage_ptr = cpu_alloc_syspage_memory(&cpupage_paddr, &syspage_paddr, spsize);

    if (debug_flag) {
        kprintf("%s: syspage size:%x _syspage_ptr:%p\n", __func__, spsize, _syspage_ptr);
    }
#define INIT_ENTRY(field) sp->field.entry_size = lsp.field.size; \
                          sp->field.entry_off = PTR_DIFF(lsp.field.p, sp)

    sp = lsp.syspage.p;
    sp->size = sizeof(*lsp.syspage.p);  // disallows further growing
    sp->type = CPU_SYSPAGE_TYPE;

    INIT_ENTRY(system_private);
    INIT_ENTRY(asinfo);
    INIT_ENTRY(hwinfo);
    INIT_ENTRY(cpuinfo);
    INIT_ENTRY(cacheattr);
    INIT_ENTRY(qtime);
    INIT_ENTRY(typed_strings);
    INIT_ENTRY(strings);
    INIT_ENTRY(intrinfo);
    INIT_ENTRY(smp);
    INIT_ENTRY(pminfo);
#ifdef CONFIG_MINIDRIVER
    INIT_ENTRY(mdriver);
#endif

    memset(&cpu, 0, sizeof(cpu));
    cpu.syspage = lsp.system_private.p->user_syspageptr;
    for (i = 0; i < sp->num_cpu; ++i) {
        struct cpuinfo_entry *cp;

        cp = startup_memory_map(sizeof(cpu), cpupage_paddr, PROT_READ | PROT_WRITE);
        cpu.cpu = i;
        memmove(cp, &cpu, sizeof(cpu));
        startup_memory_unmap(cp);
        cpupage_paddr += lsp.system_private.p->cpupage_spacing;
    }
}

void write_syspage_memory()
{
    unsigned total_size = lsp.syspage.p->total_size;

    memmove(_syspage_ptr, lsp.syspage.p, total_size);
    cpu_write_syspage_memory(syspage_paddr, total_size);
}
