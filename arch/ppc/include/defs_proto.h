/**
 * \file ppc/defs_proto.h
 *
 * Architecture-specific definitions and prototypes.
 */

#ifndef _PPC_DEFS_PROTO_H
#define _PPC_DEFS_PROTO_H

EXT unsigned ppc_ienable_bits INIT1(PPC_MSR_EE);
EXT union ppc_alt_regs *actives_alt[PROCESSORS_MAX];
EXT void (*tlb_flush_all)(void);
// The size field is filled in at runtime.
EXT tSoul alt_souls INITSOUL(0, 0, 2, 0, 16);

#if defined(VARIANT_booke)
EXT unsigned ppcbke_tlb_select;
#endif

EXT PPC_PERFREGS disabled_perfregs;

#endif
