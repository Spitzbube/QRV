#include <kernel/startup.h>
#include <platform/qemu_virt.h>

/**
 * Return the number of bits this machine/platform supports.
 */
unsigned arch_max_paddr_bits(void)
{
    return 39;
}
