/**
 * \file x86/defs_proto.h
 *
 * Architecture-specific definitions and prototypes.
 */

#ifndef _X86_DEFS_PROTO_H
#define _X86_DEFS_PROTO_H

EXT short unsigned ker_cs INIT1(0x80);
EXT short unsigned ker_ds INIT1(0x27);
EXT short unsigned ker_ss INIT1(0x88);
EXT short unsigned ker2_cs INIT1(0x90);
EXT short unsigned sys_cs INIT1(0x1d);
EXT short unsigned sys_ds INIT1(0x27);
EXT short unsigned sys_ss INIT1(0x99);
EXT short unsigned usr_cs INIT1(0x1f);
EXT short unsigned usr_ds INIT1(0x27);
EXT short unsigned usr_ss INIT1(0x27);
EXT X86_TSS *tss[PROCESSORS_MAX];
EXT short unsigned cpupage_segs[PROCESSORS_MAX];
EXT unsigned realmode_addr;
EXT volatile unsigned *__inkp INIT1(&inkernel); // For debugging
EXT unsigned fault_code;
EXT unsigned startup_cpunum;

EXT X86_PERFREGS disabled_perfregs;

#endif
