/**
 * \file riscv/defs_proto.h
 *
 * Architecture-specific definitions and prototypes.
 */

#ifndef _RISCV_DEFS_PROTO_H
#define _RISCV_DEFS_PROTO_H

EXT unsigned mmu_domain[PROCESSORS_MAX];
EXT void (*mmu_abort)(CPU_REGISTERS *);
EXT uint64_t last_cycles;

#endif