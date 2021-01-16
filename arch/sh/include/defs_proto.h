/**
 * \file sh/defs_proto.h
 *
 * Architecture-specific definitions and prototypes.
 */

#ifndef _SH_DEFS_PROTO_H
#define _SH_DEFS_PROTO_H

EXT volatile unsigned long *__shadow_imask;
EXT volatile unsigned long *__cpu_imask[PROCESSORS_MAX];

#if defined(VARIANT_smp)
/*
 * These are required to ensure that am_inkernel will return true
 * during early initialisation.
 * They will be assigned to their real values by ker_start().
 */
EXT uintptr_t ker_stack_bot INIT1(0x80000000);
EXT uintptr_t ker_stack_top INIT1(0xffffffff);
#endif

#endif
