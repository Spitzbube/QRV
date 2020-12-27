/**
 *  \file riscv/platform.h
 *
 *  \note Platform definitions for RISC-V.
 */

#ifndef _RISCV_PLATFORM_H
#define _RISCV_PLATFORM_H

#define __LITTLEENDIAN__
#define __RISCV__
#define _FILE_OFFSET_BITS 64
#define _PADDR_BITS       64

#define __JMPBUFSIZE 32
typedef unsigned __jmpbufalign;

int cpuid(void);

#define packedstruct struct __attribute__((packed))

#endif
