/**
 * \file board.c
 *
 * Board initialization, occurs right after the assembly code in head.S
 *
 * \author Yuri Zaporozhets <r_tty@yahoo.co.uk>
 *
 * \license SPDX-License-Identifier: BSD-2-Clause
 */

#include <kernel/startup.h>
#include <sbi.h>
#include <sys/fdt.h>

#define INCPTR(_ptr, _by) _ptr = TOPTR((char *)(_ptr) + (_by))

extern uint64_t _boot_a0, _boot_a1;
extern char *boot_command_line;

void *fdt_addr;

static unsigned num_cpus_detected;

/* This header is usually filled in by a program like mkifs.
 * For simplicity, we put it here for now.
 */
static struct startup_header s = {
    .signature  = 0x00FF7EEB,
    .version    = 1,
    .flags1     = STARTUP_HDR_FLAGS1_VIRTUAL,
    .header_size = sizeof(struct startup_header),
    .machine    = EM_RISCV,
    .startup_vaddr = 0,
    .paddr_bias = 0,
    .image_paddr = 0,
    .ram_paddr  = 0,
    .ram_size   = MEG(8),   // TODO
    .startup_size = MEG(1), // TODO
    .stored_size = MEG(1),  // TODO
    .imagefs_paddr = 0,
    .imagefs_size = 0,
    .preboot_size = 0,
};

struct startup_header *shdr = &s;

void rvq_putc_ser_dbg(int c) { sbi_ecall_console_putc(c); };

#define _BE(x) ENDIAN_RET32(x)

#define FDT_ALIGN(x, a)		(((x) + (a) - 1) & ~((a) - 1))
#define FDT_TAGALIGN(x)		(FDT_ALIGN((x), FDT_TAGSIZE))

//#define CONFIG_FDT_DEBUG

#ifdef CONFIG_FDT_DEBUG
#define TRACETAG(x...) ({ for (int i=0; i < indent_lvl; i++) kprintf(" "); kprintf(x); })
#else
#define TRACETAG(x...)
#endif

/**
 * \brief Handle a given node.
 */
static void handle_node(const char *name)
{
#define NODE_MATCH(_n) if (strncmp(name, _n, strlen(_n)) == 0)
    NODE_MATCH("cpu@") {
        num_cpus_detected++;
    }
}

/**
 * \brief Handle a property in the given node.
 */
static void handle_property(const char *node, const char *prop, void *data, const int datalen)
{
#define NODE_PROP_MATCH(_n, _p) if (strcmp(node, _n) == 0 && strcmp(prop, _p) == 0)
    NODE_PROP_MATCH("chosen", "bootargs") {
        boot_command_line = data;
        pr_debug("boot command line: %s\n", boot_command_line);
    } else

    NODE_PROP_MATCH("cpus", "timebase-frequency") {
        if (datalen == sizeof(uint32_t)) {
            cpu_freq = _BE(*((uint32_t *)data));
            pr_debug("CPU frequency: %d\n", cpu_freq);
        }
    } else

    if (strncmp(node, "memory@", 7) == 0 && strcmp(prop, "reg") == 0) {
        /* Proceed through all base/len pairs */
        for (unsigned i = 0; i < datalen / (2*sizeof(uint64_t)); i++) {
            uint64_t *ptr = data;
            uint64_t regbase = ENDIAN_RET64(ptr[0]);
            uint64_t regsize = ENDIAN_RET64(ptr[1]);

            /*ramblocks[i].base = regbase;
            ramblocks[i].size = regsize;*/
            // TODO
            shdr->ram_paddr = regbase;
            pr_debug("RAM at %x, size %x\n", regbase, regsize);
        }
    }
}


/**
 * \brief Parse the FTD and initialize all required variables.
 */
static void parse_ftd(void)
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
            handle_node(curr_node);
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
            handle_property(curr_node, values+offset, len ? prop->data : NULL, len);

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
            finished = 1;
            break;

          default:
            crash("Unknown tag %d in FTD\n");
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

    /* Check the signature. If device tree is not there, we cannot continue */
    if (_BE(fdt->magic) != FDT_MAGIC) {
        crash("FDT not detected, cannot continue.\n");
    }

    pr_debug("Devicetree version %d\n", _BE(fdt->version));
    parse_ftd();
}

/**
 * \brief Return the number of CPUs in the system.
 */
unsigned board_smp_num_cpu(void)
{
    return num_cpus_detected;
}
