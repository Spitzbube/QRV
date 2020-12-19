/*
 * $QNXLicenseC:
 * Copyright 2007, QNX Software Systems.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"). You
 * may not reproduce, modify or distribute this software except in
 * compliance with the License. You may obtain a copy of the License
 * at: http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTIES OF ANY KIND, either express or implied.
 *
 * This file may contain contributions from others, either as
 * contributors under the License or as licensors under other terms.
 * Please review this entire file for other proprietary rights or license
 * notices, as well as the QNX Development Suite License Guide at
 * http://licensing.qnx.com/license-guide/ for other information.
 * $
 */



/*
 *  riscv/context.h
 *

 */

#ifndef __RISCV_CONTEXT_H_INCLUDED
#define __RISCV_CONTEXT_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

typedef struct riscv_cpu_registers {
    uint64_t	gpr[32];
} RISCV_CPU_REGISTERS;

/*
 * Register names
 */
#define	RISCV_REG_X0		0
#define	RISCV_REG_X1		1
#define	RISCV_REG_X2		2
#define	RISCV_REG_X3		3
#define	RISCV_REG_X4		4
#define	RISCV_REG_X5		5
#define	RISCV_REG_X6		6
#define	RISCV_REG_X7		7
#define	RISCV_REG_X8		8
#define	RISCV_REG_X9		9
#define	RISCV_REG_X10		10
#define	RISCV_REG_X11		11
#define	RISCV_REG_X12		12
#define	RISCV_REG_X13		13
#define	RISCV_REG_X14		14
#define	RISCV_REG_X15		15

#define RISCV_REG_X16		16
#define RISCV_REG_X17		17
#define RISCV_REG_X18		18
#define RISCV_REG_X19		19
#define RISCV_REG_X20		20
#define RISCV_REG_X21		21
#define RISCV_REG_X22		22
#define RISCV_REG_X23		23
#define RISCV_REG_X24		24
#define RISCV_REG_X25		25
#define RISCV_REG_X26		26
#define RISCV_REG_X27		27
#define RISCV_REG_X28		28
#define RISCV_REG_X29		29
#define RISCV_REG_X30		30
#define RISCV_REG_X31		31

/*
 * Register name aliases
 */
#define	RISCV_REG_FP		11
#define	RISCV_REG_IP		12
#define	RISCV_REG_SP		13
#define	RISCV_REG_LR		14
#define	RISCV_REG_PC		15

/*
 * Register manipulation
 */
#define RISCV_GET_REGIP(regs)			((regs)->gpr[RISCV_REG_PC])
#define RISCV_GET_REGSP(regs)			((regs)->gpr[RISCV_REG_SP])
#define RISCV_SET_REGIP(regs,v)		((regs)->gpr[RISCV_REG_PC] = v)
#define RISCV_SET_REGSP(regs,v)		((regs)->gpr[RISCV_REG_SP] = v)

typedef struct riscv_fpu_registers {
    uint64_t	fpr[32];
} RISCV_FPU_REGISTERS;

#endif /* __RISCV_CONTEXT_H_INCLUDED */
