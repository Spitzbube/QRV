/**
 * \file init_raminfo.c
 *
 * Initialize raminfo structure in the system page.
 *
 * \author Yuri Zaporozhets <r_tty@yahoo.co.uk>
 *
 * \license SPDX-License-Identifier: GNU GPL 2.0
 */

#include <startup.h>

/**
 * \brief Callback to set memory information.
 */
static void handle_property_meminfo(const char *node, const char *prop, void *data, const int datalen)
{
    if (!strncmp(node, "memory@", 7) && !strcmp(prop, "reg")) {
        /* Proceed through all base/len pairs */
        for (unsigned i = 0; i < datalen / (2*sizeof(uint64_t)); i++) {
            uint64_t *ptr = data;
            uint64_t regbase = ENDIAN_RET64(ptr[0]);
            uint64_t regsize = ENDIAN_RET64(ptr[1]);

            add_ram(regbase, regsize);
            pr_debug("RAM at %#p, size %#p\n", regbase, regsize);
        }
    }
}

/**
 * \brief Initialize RAM.
 */
void init_raminfo(void)
{
    pr_info("%s\n", __func__);

    fdt_handle_node_cb = NULL;
    fdt_handle_property_cb = handle_property_meminfo;
    parse_fdt(false, NULL);
}
