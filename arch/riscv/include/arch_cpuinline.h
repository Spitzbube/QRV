#ifndef _RISCV_CPUINLINE_H
#define _RISCV_CPUINLINE_H

#define __cpu_membarrier() ({ __asm__ __volatile__ ("nop" : : : "memory"); })

#endif
