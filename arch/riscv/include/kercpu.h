/*
 * $QNXLicenseC:
 * Copyright 2007, QNX Software Systems. All Rights Reserved.
 *
 * You must obtain a written license from and pay applicable license fees to QNX
 * Software Systems before you may reproduce, modify or distribute this software,
 * or any work that includes all or part of this software.   Free development
 * licenses are available for evaluation and non-commercial purposes.  For more
 * information visit http://licensing.qnx.com or email licensing@qnx.com.
 *
 * This file may contain contributions from others.  Please review this entire
 * file for other proprietary rights or license notices, as well as the QNX
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 * $
 */

#include <stdbool.h>
#include <sys/types.h>
#include <kernel/posix_types.h>
#include <arch/cpu_def.h>

#define xfer_setjmp(_env)			_setjmp(_env)
#define xfer_longjmp(_env, _ret, _regs)		_longjmp(_env, _ret)

/*
 * This makes each argument in a kernel call structure take up 64 bits so
 * that it aligns with the register save area layout.
*/
#define XFILLER( line )		uint32_t	filler##line
#define FILLER( line )		XFILLER( line )

#define KARGSLOT( arg )		arg; FILLER(__LINE__)

#define REGIP(reg)		((reg)->pc)
#define REGSP(reg)		((reg)->gpr[RISCV_REG_SP])
#define SETREGIP(reg,v)		(REGIP(reg) = (uintptr_t)(v))
#define SETREGSP(reg,v)		(REGSP(reg) = (uintptr_t)(v))

#define REGSTATUS(reg)		((reg)->gpr[RISCV_REG_X0])
#define REGTYPE(reg)		((reg)->gpr[RISCV_REG_X0])
#define SETREGSTATUS(reg,v)	(REGSTATUS(reg) = (uintptr_t)(v))
#define SETREGTYPE(reg,v)	(REGTYPE(reg) = (uintptr_t)(v))


#define SETKIP_FUNC(thp,v)	cpu_invoke_func(thp, (uintptr_t)v)

#define KER_ENTRY_SIZE		4	/* size of kernel entry opcode */
#define KERERR_SKIPAHEAD	8	/* increment IP by this much on error */

/*
 * Convert physical address to pointer value and vice-versa when in a
 * physical memory model.
 */
#define PHYS_TO_PTR(phys)		((void *)RISCV_PHYS_TO_KSEG0(phys))
#define PTR_TO_PHYS(ptr)		((uintptr_t)RISCV_KSEG0_TO_PHYS(ptr))


#define rd_probe_1(ptr)	({ __attribute__((unused)) uint32_t dummy = *(const volatile uint32_t *)(ptr); })

#if 0
inline static void rd_probe_num(const void *loc, int num) {
    //ulong_t tmp;
#warning This function is not implemented yet - stop
    for(;;);
}

inline static void wr_probe_1(void *loc) {
    //ulong_t tmp;
#warning This function is not implemented yet - stop
    for(;;);
}

inline static void wr_probe_num(void *loc, int num) {
    //ulong_t tmp;
#warning This function is not implemented yet - stop
    for(;;);
}
#endif

#define HAVE_ACTIVES_STORAGE	1
#define HAVE_KERSTACK_STORAGE	1
#define HAVE_INKERNEL_STORAGE	1

#define INKERNEL_BITS_SHIFT	8

#if defined(VARIANT_smp)

#define am_inkernel am_inkernel
static inline bool am_inkernel(void)
{
    uintptr_t highmem;
    __asm__ ("ld %0, pc; srli %0, %0, 32" : "=r" (highmem));
    return highmem;
}

#define bitset_inkernel(bits)	atomic_set(&inkernel, bits)
#define bitclr_inkernel(bits)	atomic_clr(&inkernel, bits)

#endif /* SMP */

#if !defined(RISCV_CAUSE2SIGMAP_CONST)
#define RISCV_CAUSE2SIGMAP_CONST const
#endif
extern RISCV_CAUSE2SIGMAP_CONST unsigned long __mips_cause2sig_map[];

extern uintptr_t	next_instruction(CPU_REGISTERS *ctx);
