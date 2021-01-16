/**
 * \file ppc/defs_proto.h
 *
 * Architecture-specific definitions and prototypes.
 */

#ifndef _MIPS_DEFS_PROTO_H
#define _MIPS_DEFS_PROTO_H

EXT void *l1pagetable;
EXT volatile unsigned long *__shadow_imask;
EXT void *sys_kercallptr;

#if defined(VARIANT_smp)
//INIT1() values used while kernel is initializing
EXT uintptr_t ker_stack_bot INIT1(0x80000000);
EXT uintptr_t ker_stack_top INIT1(0xffffffff);
#endif

EXT MIPS_PERFREGS disabled_perfregs;

#endif
