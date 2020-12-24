/**
 * \brief Implementation of init_system_private().
 *
 * \license Apache 2.0 (http://www.apache.org/licenses/LICENSE-2.0)
 *
 * \copyright (c) 2008 QNX Software Systems.
 */

#include <kernel/startup.h>

/**
 * \brief TODO
 */
void init_system_private()
{
    struct system_private_entry *private =
        set_syspage_section(&lsp.system_private, sizeof(*lsp.system_private.p));

    /* Set the hostname if it hasn't been set yet */
    if (find_typed_string(_CS_HOSTNAME) < 0) {
        add_typed_string(_CS_HOSTNAME, "localhost");
    }

    /* Record startup location */
    unsigned mem = as_find(AS_NULL_OFF, "memory", NULL);
    as_add(shdr->ram_paddr, shdr->ram_paddr + shdr->startup_size - 1, AS_ATTR_RAM, "startup", mem);

    /* Reserved RAM for processes in the image file system */
    paddr_t start_paddr = shdr->ram_paddr + shdr->startup_size;
    as_add(start_paddr, shdr->ram_paddr + shdr->ram_size - 1, AS_ATTR_RAM, "bootram", mem);

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
