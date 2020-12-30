/**
 * \file board.c
 *
 * Board initialization, occurs right after the assembly code in head.S
 *
 * \author Yuri Zaporozhets <r_tty@yahoo.co.uk>
 *
 * \license SPDX-License-Identifier: BSD-2-Clause
 */

#include <startup.h>
#include <sbi.h>
#include <sys/fdt.h>

#define INCPTR(_ptr, _by) _ptr = TOPTR((char *)(_ptr) + (_by))

extern uint64_t _boot_a0, _boot_a1;
extern char boot_command_line[];

void *fdt_addr;
size_t fdt_size;

static unsigned num_cpus_detected;

paddr_t ramdisk_phys_start, ramdisk_phys_end;

void rvq_putc_ser_dbg(int c) { sbi_ecall_console_putc(c); };

#define _BE(x) ENDIAN_RET32(x)

#define FDT_ALIGN(x, a)		(((x) + (a) - 1) & ~((a) - 1))
#define FDT_TAGALIGN(x)		(FDT_ALIGN((x), FDT_TAGSIZE))

#ifdef CONFIG_FDT_DEBUG
#define TRACETAG(x...) if (verbose) { for (int i=0; i < indent_lvl; i++) kprintf(" "); kprintf(x); }
#else
#define TRACETAG(x...)
#endif

/* Callbacks to be called when we parse FDT */
void (*fdt_handle_node_cb)(const char *);
void (*fdt_handle_property_cb)(const char *, const char *, void *, const int);

/**
 * \brief Handle a given node.
 */
static void handle_node_early(const char *name)
{
#define NODE_MATCH(_n) if (strncmp(name, _n, strlen(_n)) == 0)
    NODE_MATCH("cpu@") {
        num_cpus_detected++;
    }
}

#define WORD_AT(x) ENDIAN_RET32(*((uint32_t *)x))
#define DWORD_AT(x) ENDIAN_RET64(*((uint32_t *)x))

/**
 * \brief Callback to set boot command line, initrd addresses and CPU frequency.
 */
static void handle_property_early(const char *node, const char *prop, void *data, const int datalen)
{
#define NODE_PROP_MATCH(_n, _p) if (!strcmp(node, _n) && !strcmp(prop, _p))
    if (!strcmp(node, "chosen")) {
        if (!strcmp(prop, "bootargs")) {
            int n = strlen(data);
            if (n > CONFIG_MAX_BOOTLINE_SIZE)
                crash("Boot command line is too long (%d bytes, maximum %d bytes allowed)\n",
                    n, CONFIG_MAX_BOOTLINE_SIZE);
            strcpy(boot_command_line, data);
            pr_debug("boot command line: %s\n", boot_command_line);
        } else if (!strcmp(prop, "linux,initrd-start")) {
            ramdisk_phys_start = WORD_AT(data);
        } else if (!strcmp(prop, "linux,initrd-end")) {
            ramdisk_phys_end = WORD_AT(data);
        }
    } else

    NODE_PROP_MATCH("cpus", "timebase-frequency") {
        if (datalen == sizeof(uint32_t)) {
            cpu_freq = WORD_AT(data);
            pr_debug("CPU frequency: %d KHz\n", cpu_freq);
        }
    } else

    if (!strncmp(node, "mmode_resv0@", 12) && !strcmp(prop, "reg")) {
        /* Proceed through all base/len pairs */
        for (unsigned i = 0; i < datalen / (2*sizeof(uint64_t)); i++) {
            uint64_t *ptr = data;
            uint64_t regbase = ENDIAN_RET64(ptr[0]);
            uint64_t regsize = ENDIAN_RET64(ptr[1]);

            avoid_ram(regbase, regsize);
            pr_debug("Reserved memory at %#p, size %#p\n", regbase, regsize);
        }
    }
}


/**
 * \brief Parse the FDT and initialize all required variables.
 *
 * \param[in]  verbose   Print the contents of the tree if CONFIG_FDT_DEBUG is set
 * \param[out] fdt_size  Address of variable to record FDT size
 */
void parse_fdt(const bool verbose, size_t *fdt_size)
{
    const struct fdt_header *fdt = fdt_addr;
    struct fdt_node_header *node = TOPTR((uintptr_t)fdt + _BE(fdt->off_dt_struct));
    const char *values = TOPTR((uintptr_t)fdt + _BE(fdt->off_dt_strings));
    char *curr_node;
    int indent_lvl = 0;
    bool finished;

    do {
        uint32_t tag = _BE(node->tag);

        switch (tag) {
          case FDT_NOP:
            INCPTR(node, FDT_TAGSIZE);
            break;

          case FDT_BEGIN_NODE:
            curr_node = node->name;
            TRACETAG("NODE: %s\n", curr_node);
            if (fdt_handle_node_cb)
                fdt_handle_node_cb(curr_node);
            /* Take the trailing zero into account */
            INCPTR(node, FDT_TAGSIZE + strlen(node->name) + 1);
            node = TOPTR(FDT_TAGALIGN((uintptr_t)node));
            if (_BE(node->tag) == FDT_END) {
                crash("Invalid tag %d in FDT\n", tag);
            }
            indent_lvl += 2;
            break;

          case FDT_PROP: {
            struct fdt_property *prop = TOPTR(node);
            unsigned len = _BE(prop->len);
            unsigned offset = _BE(prop->nameoff);

            TRACETAG("PROP: name=%s, string=%s, len=%d\n", values+offset, prop->data, len);
            if (fdt_handle_property_cb)
                fdt_handle_property_cb(curr_node, values+offset, len ? prop->data : NULL, len);

            INCPTR(node, sizeof (*prop));
            INCPTR(node, len);
            node = TOPTR(FDT_TAGALIGN((uintptr_t)node));
            break;
          }

          case FDT_END_NODE:
            TRACETAG("(END NODE)\n");
            INCPTR(node, FDT_TAGSIZE);
            if (_BE(node->tag) == FDT_PROP) {
                crash("\nInvalid tag %d in FDT\n", tag);
            }
            indent_lvl -= 2;
            break;

          case FDT_END:
            TRACETAG("(END FDT)\n");
            if (fdt_size)
                *fdt_size = ROUND(PTR_DIFF(&node->tag, fdt), __PAGESIZE);
            finished = 1;
            break;

          default:
            crash("Unknown tag %d in FDT @ %#p\n", tag, &node->tag);
            break;
        }
    } while (!finished);
}

/**
 * \brief Early board initialization.
 * \note Register our putchar routine here.
 *       Remove after the select_debug mechanism is ready.
 */
void board_init(void)
{
    set_print_char(rvq_putc_ser_dbg);
    for (int i = 0; i < 79; i++)
        sbi_ecall_console_putc('=');
    sbi_ecall_console_puts("\n\n");

    fdt_addr = (void *)_boot_a1;
    const struct fdt_header *fdt = fdt_addr;

    pr_debug("Boot hart %d, FDT @ %#P\n", _boot_a0, fdt_addr);

    /* Avoid using kernel memory */
    avoid_ram((paddr_t)_start, _end - _start);

    /* Check the signature. If device tree is not there, we cannot continue */
    if (_BE(fdt->magic) != FDT_MAGIC) {
        crash("FDT not detected, cannot continue.\n");
    }

    pr_debug("Devicetree version %d\n", _BE(fdt->version));

    fdt_handle_node_cb = handle_node_early;
    fdt_handle_property_cb = handle_property_early;
    parse_fdt(false, &fdt_size);

    pr_debug("FDT size: %d bytes\n", fdt_size);

    if (ramdisk_phys_start && ramdisk_phys_end)
        pr_debug("RAM-disk at %p - %p\n", ramdisk_phys_start, ramdisk_phys_end);

    /*
     * Claim RAM used by the FDT
     */
    avoid_ram((paddr_t)fdt_addr, fdt_size);
}

/**
 * \brief Return the number of CPUs in the system.
 */
unsigned board_smp_num_cpu(void)
{
    return num_cpus_detected;
}
