/**
 * \file startup_proto.h
 *
 * Startup function prototypes.
 *
 * \license Apache 2.0 (http://www.apache.org/licenses/LICENSE-2.0)
 *
 * \copyright (c) 2014 QNX Software Systems.
 */

#ifndef _STARTUP_PROTO_H
#define _STARTUP_PROTO_H

/* This function is usually called very first, at the start of _main() */
void board_init(void);

/* Debugging I/O routines available for many systems */
void init_8250(unsigned, const char *, const char *);
void put_8250(int);

/* This is handy for a null debug device */
void dummy_print_char(int);

/* If set_print_char() is called early, many interesting early messages
 * will be seen on the console.
 */
void set_print_char(void (*)(int));
void (*get_print_char(void))(int);

void set_debug(unsigned channel, const struct debug_device *dev, const char *options);
void select_debug(const struct debug_device *dev, unsigned size);

/*
 * These are board specific routines that need to be implemented. There may
 * be more syspage sections that need to be implemented for a particular CPU.
 * Check the appropriate cpu_startup.h. There may be default implementations
 * of these routines in the startup library that* will work for a particular
 * board, or set of boards.
 */
void init_raminfo(void);
void init_intrinfo(void);
void init_qtime(void);
void init_cacheattr(void);
void init_cpuinfo(void);
void init_hwinfo(void);
void init_asinfo(unsigned mem);
void init_nanospin(void);

/* Only needed for SMP systems */
void init_smp(void);
unsigned board_smp_num_cpu(void);
void board_smp_init(struct smp_entry *, unsigned num_cpus);
int board_smp_start(unsigned cpu, void (*start)(void));
unsigned board_smp_adjust_num(unsigned);
extern void (*smp_spin_vaddr)(void);

/* Only needed on systems with an MMU */
void init_mmu(void);

/*
 * These are CPU specific routines that are implemented by the startup library.
 * Users shouldn't have to call these directly.
 */
void cpu_startup(void);
void cpu_one_startup(int __cpu);
void cpu_init_syspage_memory(void);
struct syspage_entry *cpu_alloc_syspage_memory(paddr_t *, paddr_t *, unsigned);
void cpu_write_syspage_memory(paddr_t sys_paddr, unsigned sysp_size);
void cpu_startnext(uintptr_t eip, unsigned cpu);
void elf_map(uintptr_t vaddr, paddr_t paddr, size_t size, int flags);
paddr_t elf_vaddr_to_paddr(uintptr_t vaddr);
uintptr_t load_elf32(paddr_t addr);
void startnext(void);

/*
 * These are CPU/board independent routines that can be used 'as is'.
 */
void init_system_private(void);

#if 0
void load_ifs(paddr_t);
struct pminfo_entry *init_pminfo(unsigned managed_size);

void copy_memory(paddr_t dst, paddr_t src, size_t len);

unsigned calc_cksum(const void *start, unsigned nbytes);
#endif

paddr_t strtopaddr(const char *nptr, char **endptr, int base);

/*
 * FDT routines
 */
void parse_fdt(const bool verbose, size_t *fdt_size);

/*
 * Hardware access routines.
 */
void chip_access(paddr_t base, unsigned reg_shift, unsigned mem_mapped, unsigned size);
unsigned chip_read8(unsigned off);
void chip_write8(unsigned off, unsigned val);
void chip_write16(unsigned off, unsigned val);
void chip_write32(unsigned off, unsigned val);
unsigned chip_read16(unsigned off);
unsigned chip_read32(unsigned off);
uint64_t chip_read64(unsigned off);
void chip_write64(unsigned off, uint64_t val);
void chip_done(void);

unsigned long timer_ns2tick(unsigned long ns);
unsigned long timer_tick2ns(unsigned long ticks);
unsigned long calc_time_t(const struct tm *tm);
unsigned bcd2bin(unsigned a);
unsigned long rtc_time(void);
unsigned long rtc_time_none(void);

void invert_timer_freq(struct qtime_entry *qtime, unsigned freq);
struct qtime_entry *alloc_qtime(void);
struct tm *_gmtime(const time_t * timer, struct tm *tmbuf);

/* Memory management */
void *ws_alloc(size_t);
void add_sysram(void);
void avoid_ram(paddr_t, size_t size);
void add_ram(paddr_t start, uint64_t size);
void watch_add_ram(void (*)(paddr_t, paddr_t));
paddr_t alloc_ram(paddr_t addr, paddr_t size, unsigned align);
paddr_t find_top_ram(paddr_t size);
paddr_t find_top_ram_aligned(paddr_t size, unsigned align, unsigned pagesize);
paddr_t find_ram_in_range(paddr_t range_start, paddr_t range_end, size_t size,
                          unsigned align, unsigned colour, unsigned mask);
paddr_t find_ram(size_t size, unsigned align, unsigned colour, unsigned mask);
paddr_t calloc_ram(size_t size, unsigned align);
void reserve_ram(unsigned size, unsigned align, unsigned pagesize);
int is_addr_in_ram(paddr_t start, size_t size);

/* Command-line option handling */
int getopt(int argc, char **argv, char *opts);
int cpu_handle_common_option(int opt);
void handle_common_option(int opt);
paddr_t getsize(char *, char **);

/* Printing */
void kprintf(const char *fmt, ...);
void ksprintf(char *buff, const char *fmt, ...);
void crash(const char *fmt, ...);

void print_syspage(void);

char *ultoa_end(unsigned long int v, char *d, int radix);

/* Syspage routines */
void init_syspage_memory(void *, unsigned max_size);
void *grow_syspage_section(void *, unsigned size);
void *set_syspage_section(void *, unsigned size);
void reloc_syspage_memory(void *, unsigned max_size);
void alloc_syspage_memory(void);
void write_syspage_memory(void);

const void *find_startup_info(const void *start, unsigned type);
int find_typed_string(int type_index);
int del_typed_string(int type_index);
unsigned add_typed_string(int type_index, const char *name);
unsigned add_string(const char *name);

struct intrinfo_entry *add_interrupt(const struct startup_intrinfo *);
void add_interrupt_array(const struct startup_intrinfo *intrs, unsigned size);
int interrupt_valid(int intr);

#define HWI_TAG_INFO(type) HWI_TAG_NAME_##type, \
                           sizeof(struct hwi_##type), \
                           HWI_TAG_ALIGN_##type

/* Prototypes for generic hwi routines. Note there are specific bus and device
 * add functions defined in startup/lib/public/sys/hwinfo.h */
void hwi_default(void);
void *hwi_alloc_tag(const char *tagname, unsigned size, unsigned align);
void *hwi_alloc_item(const char *tagname, unsigned size, unsigned align, const char *itemname,
                     unsigned owner);
void *hwi_grow_tag(unsigned offset, unsigned size);

unsigned hwi_add_synonym(unsigned hwi_off, const char *synonym);
unsigned hwi_find_as(paddr_t base, int mmap);

/* Prototypes for adding buses and devices */
unsigned hwibus_add(const char *bus_name, unsigned hwi_off);
unsigned hwidev_add(const char *device_name, unsigned pnp, unsigned bus_hwi_off);

/* Prototypes for adding tags */
void hwitag_add_common(unsigned hwi_off, void *attr);
void hwitag_add_optstr(unsigned hwi_off, const char *string);
void hwitag_add_location(unsigned hwi_off, paddr_t base, paddr_t len, unsigned reg_shift,
                         unsigned addr_space);
void hwitag_add_busattr(unsigned hwi_off, struct hwi_busattr *attr);
void hwitag_add_irq(unsigned hwi_off, unsigned vector);
unsigned hwitag_add_irq_mapping(unsigned hwi_off, unsigned default_irq);
void hwitag_add_specific_irq_mapping(unsigned hwi_off, unsigned offset, unsigned devfunc,
                                     int adjust);
void hwitag_add_irqrange(unsigned hwi_off, unsigned start_vector, unsigned num);
void hwitag_add_inputclk(unsigned hwi_off, unsigned clk, unsigned div);
void hwitag_add_nicaddr(unsigned hwi_off, const _uint8 * addr, unsigned len);
void hwitag_add_nicphyaddr(unsigned hwi_off, const _uint32 addr);
void hwitag_add_regname(unsigned hwi_off, const char *name, unsigned regoffset);

/* Prototypes for setting specific tag values */
int hwitag_set_nicaddr(unsigned hwi_off, unsigned nic_idx, uint8_t * nic_addr);
int hwitag_set_phyaddr(unsigned hwi_off, unsigned phy_idx, uint32_t phy_addr);
int hwitag_set_ivec(unsigned hwi_off, unsigned ivec_idx, uint32_t vector);
int hwitag_set_dma(unsigned hwi_off, unsigned dma_idx, uint32_t chnl);
int hwitag_set_inputclk(unsigned hwi_off, unsigned clksrc_idx, struct hwi_inputclk *clk);
int hwitag_set_busattr(unsigned hwi_off, unsigned busattr_idx, struct hwi_busattr *busattr);
int hwitag_set_ivecrange(unsigned hwi_off, unsigned ivecrange_idx, unsigned start_vector,
                         unsigned num);
int hwitag_set_avail_ivec(unsigned hwi_off, int ivec_idx, uint32_t vector);
int hwitag_set_errata(unsigned hwi_off, unsigned errata_idx, uint32_t errata);

unsigned as_default(void);
unsigned as_add(paddr_t start, paddr_t end, unsigned attr, const char *name, unsigned owner);
unsigned as_add_containing(paddr_t start, paddr_t end, unsigned attr, const char *name,
                           const char *container);
void as_set_priority(unsigned as_off, unsigned priority);
unsigned as_find(unsigned start, ...);
unsigned as_find_containing(unsigned off, paddr_t start, paddr_t end, const char *container);

extern struct local_syspage lsp;

static inline unsigned as_info2off(const struct asinfo_entry *as) {
    return (uintptr_t)as - (uintptr_t)lsp.asinfo.p;
}

static inline struct asinfo_entry *as_off2info(unsigned off) {
    return (struct asinfo_entry *)((uintptr_t)lsp.asinfo.p + off);
}

#ifdef CONFIG_MINIDRIVER
// TODO: revise
extern unsigned mdriver_max;
extern void (*mdriver_check)(void);
extern void (*mdriver_hook)(void);
int mdriver_add(char *name, int intr, int (*handler)(int state, void *data), paddr_t data_paddr,
                unsigned data_size);
ptrdiff_t cpu_mdriver_map(void);
void *cpu_mdriver_prepare(struct mdriver_entry *md);
int mini_data(int state, void *data);
#endif

uintptr_t startup_io_map(unsigned size, paddr_t phys);
void startup_io_unmap(uintptr_t port);
void *startup_memory_map(unsigned size, paddr_t phys, unsigned prot_flags);
void startup_memory_unmap(void *);

#ifdef CONFIG_PCI
/* Generic PCI routines */
uint16_t pci_read_cfg16(uint8_t bus, uint8_t dev_number, uint8_t func_number, uint8_t reg_offset);
uint8_t pci_read_cfg8(uint8_t bus, uint8_t dev_number, uint8_t func_number, uint8_t reg_offset);
void pci_write_cfg16(uint8_t bus, uint8_t dev_number, uint8_t func_number, uint8_t reg_offset,
                     uint16_t value);
void pci_write_cfg8(uint8_t bus, uint8_t dev_number, uint8_t func_number, uint8_t reg_offset,
                    uint8_t value);

/*
 * CPU specific PCI routines. Note that 8 and 16 bit variants are generic and
 * implemented in terms of these 32 bit variants which are architecture
 * specific.
 */
uint32_t pci_read_cfg32(uint8_t bus, uint8_t dev_number, uint8_t func_number, uint8_t reg_offset);
void pci_write_cfg32(uint8_t bus, uint8_t dev_number, uint8_t func_number, uint8_t reg_offset,
                     uint32_t value);
#endif

#ifdef CONFIG_JTAG
void jtag_store_syspage_addr(void);
void jtag_reserve_syspage_addr(paddr_t jtag_syspage_addr);
void jtag_reserve_memory(paddr_t resmem_addr, size_t resmem_size, uint8_t resmem_flag);
#endif

#ifdef CONFIG_ACPI
paddr_t acpi_find_table(unsigned table_name, unsigned *lenp);
void *board_find_acpi_rsdp(void);
#endif

#ifdef CONFIG_COMPRESSION
void uncompress(int type, paddr_t dst, paddr_t src);
void uncompress_zlib(uint8_t *dst, int *dstlen, uint8_t *src, int srclen, uint8_t *win);
void uncompress_lzo(uint8_t *dst, uint8_t *src);
void uncompress_ucl(uint8_t *dst, uint8_t *src);
#endif

void init_ringbuffers(const char *name, paddr_t ringbuffer_addr, size_t ringbuffer_size);

/***********************
 * Variable prototypes *
 ***********************/
extern unsigned paddr_bits;
extern paddr_t syspage_paddr;
extern int debug_flag;
extern chip_info dbg_device[2];
extern chip_info timer_chip;
extern unsigned long cpu_freq, timer_freq;
extern unsigned max_cpus;
extern unsigned reserved_size, reserved_align;
extern int _argc;
extern char **_argv;
extern char *optarg;
extern int optind;
extern unsigned (*timer_start)(void);
extern unsigned (*timer_diff)(unsigned start);
extern void (*smp_hook_rtn)(void);
extern unsigned misc_flags;
extern bool secure_system;

/* Location of initrd */
extern paddr_t ramdisk_phys_start, ramdisk_phys_end;

/* Start and end addresses of our kernel */
extern const uint8_t _start[], _end[];

extern void *fdt_addr;
extern size_t fdt_size;

/* Callbacks to be called when we parse FDT */
extern void (*fdt_handle_node_cb)(const char *);
extern void (*fdt_handle_property_cb)(const char *, const char *, void *, const int);

#endif
