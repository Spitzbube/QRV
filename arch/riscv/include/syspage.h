
#ifndef _RISCV_SYSPAGE_H
#define _RISCV_SYSPAGE_H

#define SYSPAGE_KERNEL_ENTRY struct riscv_kernel_entry kercall
#define ARCH_SYSPAGE_ENTRY   struct riscv_syspage_entry riscv

/*
 * CPU capability/state flags.
 */
#define RISCV_CPU_FLAG_FOO	1	// TODO

struct riscv_cpu_entry {
    _Uint64t (*clock_cycles)(void);
};

struct riscv_syspage_entry {
    _Uint64t    startup_base;
     unsigned   startup_size;
     syspage_entry_info cpu;
};

struct riscv_kernel_entry {
    int foo; // TODO
};

#endif
