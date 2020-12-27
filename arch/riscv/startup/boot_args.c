/**
 * Temporary boot_args, until we make an image consisting of kernel+ramdisk
 */

#include <kernel/startup.h>
#include <platform/qemu_virt.h>

static struct startup_header s = {
    .signature  = 0x00FF7EEB,
    .version    = 1,
    .flags1     = STARTUP_HDR_FLAGS1_VIRTUAL,
    .header_size = sizeof(struct startup_header),
    .machine    = EM_RISCV,
    .startup_vaddr = 0,
    .paddr_bias = 0,
    .image_paddr = 0,
    .ram_paddr  = KERNBASE,
    .ram_size   = MEG(8),   // TODO
    .startup_size = MEG(1), // TODO
    .stored_size = MEG(1),  // TODO
    .imagefs_paddr = 0,
    .imagefs_size = 0,
    .preboot_size = 0,
};

struct startup_header *shdr = &s;