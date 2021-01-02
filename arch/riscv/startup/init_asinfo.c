/**
 * \file init_asinfo.c
 *
 * Add machine-specific asinfo syspage entries in cpu_addr_space.
 *
 * \author Yuri Zaporozhets <r_tty@yahoo.co.uk>
 *
 * \license SPDX-License-Identifier: GNU GPL 2.0
 */

#include <startup.h>
#include <platform/qemu_virt.h>

/**
 * \brief Add such entries as I/O to the cpu_addr_space
 *
 * \todo Make platform-independent
 */
void init_asinfo(unsigned mem)
{
    ultra_verbose("%s: mem=%0#x\n", __func__, mem);

    as_add(0, CLINT-1, AS_ATTR_NONE, "bootrom", mem);
    as_add(CLINT, KERNBASE-1, AS_ATTR_DEV, "io", mem);
}
