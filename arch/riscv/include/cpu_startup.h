/*
 * $QNXLicenseC:
 * Copyright 2008, QNX Software Systems.
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

#ifndef _RISCV_CPU_STARTUP_H
#define _RISCV_CPU_STARTUP_H

#include <inline.h>

#define KERCALL_SEQUENCE(name)	uint32_t name[] = {			\
			0xef000000,		/* swi (syscall no. in ip)	*/	\
			0xe7ffffef		/* undefined instruction	*/	\
}

#define CPU_SYSPAGE_TYPE	SYSPAGE_ARM

struct cpu_local_syspage {
	SYSPAGE_SECTION(arm_boxinfo);
	SYSPAGE_SECTION(arm_cpu);
};

#define BOOTSTRAPS_RUN_ONE_TO_ONE	0

#if (_PADDR_BITS-0) != 64
#define CPU_COMMON_OPTIONS_STRING	"w:"
#else
// We use -x to enable LPAE in the 64-bit kernel variant
#define CPU_COMMON_OPTIONS_STRING	"w:x"
#endif

extern void		board_cpu_startup(void);
extern void		board_cpu_startnext(void);

extern unsigned		trap_vectors;
extern unsigned		mmu_cr_set;
extern unsigned		mmu_cr_clr;
extern int		cycles_per_loop;
extern paddr32_t	startup_base;
extern unsigned		startup_size;


#endif
