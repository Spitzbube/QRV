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

/*
 *  sys/syspage.h
 *
 */

#ifndef __SYSPAGE_H_INCLUDED
#define __SYSPAGE_H_INCLUDED

#include <sys/qrv_core.h>

__BEGIN_DECLS
#if defined(__CLOCKADJUST)
struct _clockadjust __CLOCKADJUST;
#undef __CLOCKADJUST
#endif

struct _thread_local_storage;
struct _process_local_storage;
struct syspage_entry;
struct tracebuf;

#if defined(__SLIB_DATA_INDIRECT) && !defined(_syspage_ptr) && !defined(__SLIB)
struct syspage_entry *__get_syspage_ptr(void);
#define _syspage_ptr (__get_syspage_ptr())
#else
extern struct syspage_entry *_syspage_ptr;
#endif

typedef struct {
    _Uint16t entry_off;
    _Uint16t entry_size;
} syspage_entry_info;

/*
 * Include CPU specific definition for network queries.
 */
#include <arch/syspage.h>

/*
 * The CPUPAGE_ENTRY structure and the INDEXES must be matched.
 */
struct cpupage_entry {
    struct _thread_local_storage *tls;
    struct _process_local_storage *pls;
    struct syspage_entry *syspage;
    unsigned long cpu;
    unsigned long state;
    unsigned long spare[8];
};

enum {
    CPUPAGE_ADDR = -1,          /* R */
    CPUPAGE_TLS = 0,            /* R */
    CPUPAGE_PLS,                /* RW */
    CPUPAGE_SYSPAGE,            /* R */
    CPUPAGE_CPU,                /* R */
    CPUPAGE_STATE,              /* R */
    CPUPAGE_MAX
};

/*
 *  Architecture independent system page definitions
 */

/*
 * System page types
 */
enum {
    SYSPAGE_X86,
    SYSPAGE_PPC,
    SYSPAGE_MIPS,
    SYSPAGE_SPARE,
    SYSPAGE_ARM,
    SYSPAGE_SH,
    SYSPAGE_RISCV
};

#define QTIME_FLAG_TIMER_ON_CPU0	1u
#define QTIME_FLAG_CHECK_STABLE		2u
#define QTIME_FLAG_TICKLESS		4u
#define QTIME_FLAG_GLOBAL_CLOCKCYCLES	8u /* clockcycles is synchronized between all processors */

typedef struct qtime_entry {
    _Uint64t cycles_per_sec;    /* for ClockCycles */
    _Uint64t volatile nsec_tod_adjust;
    _Uint64t volatile nsec;
    unsigned long nsec_inc;
    unsigned long boot_time;    /* UTC seconds when machine booted */

    struct _clockadjust adjust;
    unsigned long timer_rate;   /* times 10^timer_scale */
    long timer_scale;
    unsigned long timer_load;
    long intr;
    unsigned long epoch;
    unsigned long flags;
    unsigned int rr_interval_mul;
    unsigned long spare0;
    _Uint64t volatile nsec_stable;
    unsigned long spare[4];
} tQtime;

struct intrspin;

typedef enum {
    DEBUG_WATCHDOG_STOP = 0,
    DEBUG_WATCHDOG_CONTINUE,
    DEBUG_WATCHDOG_FEED
} debug_watchdog_cmd;

#define AS_NULL_OFF		((_Uint16t)-1)

/* Address space flags */
#define AS_ATTR_READABLE	0x0001
#define AS_ATTR_WRITABLE	0x0002
#define AS_ATTR_CACHABLE	0x0004
#define AS_ATTR_VISIBLE		0x0008
#define AS_ATTR_KIDS		0x0010
#define AS_ATTR_CONTINUED	0x0020

#define AS_PRIORITY_DEFAULT	100

struct asinfo_entry {
    _Uint64t start;
    _Uint64t end;
    _Uint16t owner;
    _Uint16t name;
    _Uint16t attr;
    _Uint16t priority;
    int (*alloc_checker)(struct syspage_entry * __sp,
                         _Uint64t * __base, _Uint64t * __len, size_t __size, size_t __align);
    _Uint32t spare;
};

struct hwinfo_entry {
    unsigned long data[1];      /* variable sized, see <hw/sysinfo.h> */
};

#define SYSTEM_PRIVATE_FLAG_ABNORMAL_REBOOT     1UL
#define SYSTEM_PRIVATE_FLAG_EALREADY_NEW        2UL

struct system_private_entry {
    struct cpupage_entry *user_cpupageptr;
    struct syspage_entry *user_syspageptr;
    struct cpupage_entry *kern_cpupageptr;
    struct syspage_entry *kern_syspageptr;
    struct kdebug_info   *kdebug_info;
    struct kdebug_callback *kdebug_call;
    void *boot_program[4];
    unsigned long boot_idx;
    unsigned long cpupage_spacing;
    unsigned long private_flags;
    _Uint32t pagesize;
    struct tracebuf *tracebuf;
    _Paddr32t kdump_info;
    _Uint32t spare[3];
    SYSPAGE_KERNEL_ENTRY;
};

/*
 * System independent CPU flags (system dependent grow from bottom up)
 */
#define CPU_FLAG_FPU    (1U <<  31)    /* CPU has floating point support */
#define CPU_FLAG_MMU    (1U <<  30)    /* MMU is active */

struct cpuinfo_entry {
    _Uint32t cpu;
    _Uint32t speed;
    _Uint32t flags;
    _Uint32t spare0;
    _Uint64t idle_history;
    _Uint32t spare1;
    _Uint16t name;
    _Uint8t ins_cache;
    _Uint8t data_cache;
};

#define CACHE_LIST_END		0xff    /* terminate a cache hierarchy list */

/*
 * Cache flags
 */
#define CACHE_FLAG_INSTR	0x0001  /* cache holds instructions */
#define CACHE_FLAG_DATA		0x0002  /* cache holds data */
#define CACHE_FLAG_UNIFIED	0x0003  /* cache holds both ins & data */
#define CACHE_FLAG_SHARED	0x0004  /* cache is shared between multiple CPUs in an SMP system */
#define CACHE_FLAG_SNOOPED	0x0008  /* cache implements a bus snooping protocol */
#define CACHE_FLAG_VIRT_TAG	0x0010  /* cache is virtually tagged */
#define CACHE_FLAG_VIRTUAL	0x0010  /* backwards compatability flag for above */
#define CACHE_FLAG_WRITEBACK	0x0020  /* cache does writeback, not writethru */
#define CACHE_FLAG_CTRL_PHYS	0x0040  /* control function takes 32-bit paddrs */
#define CACHE_FLAG_SUBSET	0x0080  /* this cache obeys the 'subset' property */
#define CACHE_FLAG_NONCOHERENT	0x0100  /* cache is non-coherent on SMP */
#define CACHE_FLAG_NONISA	0x0200  /* cache doesn't obey ISA cache instr */
#define CACHE_FLAG_NOBROADCAST	0x0400  /* cache ops aren't broadcast on bus for SMP */
#define CACHE_FLAG_VIRT_IDX	0x0800  /* cache is virtually indexed */
#define CACHE_FLAG_CTRL_PHYS64	0x1000  /* control function takes 64-bit paddrs */

struct cacheattr_entry {
    _Uint32t next;
    _Uint32t line_size;
    _Uint32t num_lines;
    _Uint32t flags;
    unsigned (*control)(_Paddr32t, unsigned, int, struct cacheattr_entry *, volatile struct syspage_entry *);
    _Uint16t ways;
    _Uint16t spare0[1];
    _Uint32t spare1[2];
};

struct typed_strings_entry {
    char data[4];               /* variable size */
};

struct strings_entry {
    char data[4];               /* variable size */
};

/*
 * System independent interrupt flags
 * (system dependent grow from bottom up).
 */
#define INTR_FLAG_NMI			0x8000U
#define INTR_FLAG_CASCADE_IMPLICIT_EOI	0x4000U
#define INTR_FLAG_CPU_FAULT		0x2000U
#define INTR_FLAG_SMP_BROADCAST_MASK	0x1000U
#define INTR_FLAG_SMP_BROADCAST_UNMASK	0x0800U

/*
 * System independent interrupt code gen flags
 * (system dependent grow from bottom up).
 */
#define INTR_GENFLAG_LOAD_SYSPAGE	0x8000U
#define INTR_GENFLAG_LOAD_INTRINFO	0x4000U
#define INTR_GENFLAG_LOAD_LEVEL		0x2000U
#define INTR_GENFLAG_LOAD_INTRMASK	0x1000U
#define INTR_GENFLAG_NOGLITCH		0x0800U
#define INTR_GENFLAG_LOAD_CPUNUM	0x0400U
#define INTR_GENFLAG_ID_LOOP		0x0200U

struct __intrgen_data {
    _Uint16t genflags;
    _Uint16t size;
    void (*rtn)(void);
};

#define INTR_CONFIG_FLAG_PREATTACH	0x0001
#define INTR_CONFIG_FLAG_DISALLOWED	0x0002
#define INTR_CONFIG_FLAG_IPI		0x0004

struct intrinfo_entry {
    _Uint32t vector_base;
    _Uint32t num_vectors;
    _Uint32t cascade_vector;
    _Uint32t cpu_intr_base;
    _Uint16t cpu_intr_stride;
    _Uint16t flags;
    struct __intrgen_data id;
    struct __intrgen_data eoi;
    int (*mask)(struct syspage_entry *, int);
    int (*unmask)(struct syspage_entry *, int);
    unsigned (*config)(struct syspage_entry *, struct intrinfo_entry *, int);
    _Uint32t spare[4];
};

struct smp_entry {
    void (*send_ipi)(struct syspage_entry *, unsigned, int, unsigned *);
    void *start_addr;
    _Uint32t pending;
    _Uint32t cpu;
};

struct pminfo_entry {
    _Uint32t wakeup_pending;
    _Uint32t wakeup_condition;
    _Uint32t spare[4];
    _Uint32t managed_storage[1];    /* Variable sized */
};

/*
 * Mini-drivers
 */
enum mdriver_state {
    MDRIVER_INIT,
    MDRIVER_STARTUP,
    MDRIVER_STARTUP_FINI,
    MDRIVER_KERNEL,
    MDRIVER_PROCESS,
    MDRIVER_INTR_ATTACH,
    MDRIVER_STARTUP_PREPARE,
};

struct mdriver_entry {
    _Uint32t intr;
    int (*handler)(int state, void *data);
    void *data;
    _Paddr32t data_paddr;
    _Uint32t data_size;
    _Uint32t name;
    _Uint32t internal;
    _Uint32t spare[1];
};


struct syspage_entry {
    _Uint16t size;              /* size of syspage_entry */
    _Uint16t total_size;        /* size of system page */
    _Uint16t type;
    _Uint16t num_cpu;
    syspage_entry_info system_private;
    syspage_entry_info asinfo;
    syspage_entry_info hwinfo;
    syspage_entry_info cpuinfo;
    syspage_entry_info cacheattr;
    syspage_entry_info qtime;
    syspage_entry_info typed_strings;
    syspage_entry_info strings;
    syspage_entry_info intrinfo;
    syspage_entry_info smp;
    syspage_entry_info pminfo;
    syspage_entry_info mdriver;
    long spare[2];
    ARCH_SYSPAGE_ENTRY;
};

#define _SYSPAGE_ENTRY_SIZE(b, f)	((b)->f.entry_size)
#define SYSPAGE_ENTRY_SIZE(f)		_SYSPAGE_ENTRY_SIZE(_syspage_ptr, f)

#define _SYSPAGE_ENTRY( __base, __field ) \
	((struct __field##_entry *)(void *)((char *)(__base) + (__base)->__field.entry_off))

#define _SYSPAGE_CPU_ENTRY( __base, __cpu, __field ) \
	((struct __cpu##_##__field##_entry *)(void *)((char *)(__base) + (__base)->__cpu.__field.entry_off))

#define SYSPAGE_ENTRY( __field )		_SYSPAGE_ENTRY( _syspage_ptr, __field )
#define SYSPAGE_CPU_ENTRY( __cpu, __field )	_SYSPAGE_CPU_ENTRY( _syspage_ptr, __cpu, __field )

__END_DECLS

#endif
