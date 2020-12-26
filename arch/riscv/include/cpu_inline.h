#ifndef _RISCV_CPUINLINE_H
#define _RISCV_CPUINLINE_H

#define __cpu_membarrier() ({ __asm__ __volatile__ ("nop" : : : "memory"); })
#define wfi() do { __asm__ __volatile__("wfi" ::: "memory"); } while (0)

#endif
