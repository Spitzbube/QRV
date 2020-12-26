/**
 *  \file riscv/platform.h
 *
 *  \note Platform definitions for RISC-V.
 */

#ifndef _RISCV_PLATFORM_H
#define _RISCV_PLATFORM_H

#ifndef __PLATFORM_H_INCLUDED
#error riscv/platform.h should not be included directly.
#endif

#define __JMPBUFSIZE 32
typedef unsigned __jmpbufalign;

int cpuid(void);

#define packedstruct struct __attribute__((packed))

#endif
