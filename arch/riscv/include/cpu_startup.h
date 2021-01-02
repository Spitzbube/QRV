/**
 * \brief CPU specific definitions for startup.
 *
 * \license Apache 2.0 (http://www.apache.org/licenses/LICENSE-2.0)
 *
 * \copyright (c) 2008 QNX Software Systems.
 */

#ifndef _RISCV_CPU_STARTUP_H
#define _RISCV_CPU_STARTUP_H

#define RISCV_MAP_SYSPAGE	0xffffffff	/* Syspage */
#define RISCV_MAP_SYSPAGE_RO	0xfffffffe	/* Syspage/CPUpage read-only */
#define RISCV_MAP_NOEXEC	0x80000000	/* No execute */
#define RISCV_MAP_DEVICE	0x40000000	/* Memory-mapped I/O */
#define RISCV_MAP_STORDER	0x20000000	/* Strongly ordered memory (TODO) */
#define RISCV_MAP_NOCACHE	0x10000000	/* Non-cacheable memory */

#define CPU_SYSPAGE_TYPE SYSPAGE_RISCV

struct cpu_local_syspage {
    SYSPAGE_SECTION(riscv_cpu);
    SYSPAGE_TYPED_SECTION(paddr_t, pgdir);
};

#define BOOTSTRAPS_RUN_ONE_TO_ONE 1

extern uintptr_t riscv_map(uintptr_t va, paddr_t pa, size_t sz, int flags);

extern void board_cpu_startup(void);
extern void board_cpu_startnext(void);

extern int cycles_per_loop;
extern paddr_t startup_base;
extern unsigned startup_size;

#define CPU_COMMON_OPTIONS_STRING ""

#endif
