/**
 * \brief Implementation of init_system_private().
 *
 * \license Apache 2.0 (http://www.apache.org/licenses/LICENSE-2.0)
 *
 * \copyright (c) 2008 QNX Software Systems.
 */

#include <startup.h>

/**
 * \brief Initialize system_private_entry in the syspage.
 */
void init_system_private()
{
    ultra_verbose("%s\n", __func__);

    struct system_private_entry *private =
        set_syspage_section(&lsp.system_private, sizeof(*lsp.system_private.p));

    /*
     * Set page size. Failing to do so here will result in some very
     * unexpected results, such as ROUND() returning zero value and mem
     * routines silently stop working.
     */
    private->pagesize = __PAGESIZE;

    /* Set the hostname if it hasn't been set yet */
    if (find_typed_string(_CS_HOSTNAME) < 0) {
        add_typed_string(_CS_HOSTNAME, "localhost");
    }

    /* Record kernel location in the syspage */
    unsigned mem = as_find(AS_NULL_OFF, "cpu_addr_space", NULL);
    as_add((paddr_t)_start, (paddr_t)_end, AS_ATTR_RAM, "kernel", mem);

    /* Record FDT location also */
    as_add((paddr_t)fdt_addr, (paddr_t)fdt_addr + fdt_size, AS_ATTR_ROM, "fdt", mem);

    /* Record RAM-disk location, if necessary */
    if (ramdisk_phys_start)
        as_add(ramdisk_phys_start, ramdisk_phys_end, AS_ATTR_ROM, "ramdisk", mem);

    /*
     * If the user wanted to reserve some memory, allocate it now. Get
     * it from the top of available memory so that we we use as little
     * of any one-to-one mapping area as possible.
     */
    if (reserved_size > 0) {
        reserve_ram(reserved_size, reserved_align, private->pagesize);
    }

    /* Start any application processors */
    //smp_hook_rtn(); // TODO

    /* Add system RAM */
    add_sysram();

    /* Allocate the real storage location for the system & cpu pages.
     * We can't call set_syspage_section()/grow_syspage_section() after this.
     */
    alloc_syspage_memory();
}
