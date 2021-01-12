/**
 * \file startup.h
 *
 * Definitions and include directives for startup.
 *
 * \license Apache 2.0 (http://www.apache.org/licenses/LICENSE-2.0)
 *
 * \copyright (c) 2014 QNX Software Systems.
 *
 * \note For detailed explanation of various startup scenarios see
 *       Documentation/startup-layout.txt
 */

#ifndef _STARTUP_H
#define _STARTUP_H

#include <stddef.h>
#include <stdarg.h>
#include <string.h>
#include <inttypes.h>
#include <stdbool.h>
#include <gulliver.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/neutrino.h>
#include <sys/syspage.h>
#include <sys/elf.h>

#include <hw/sysinfo.h>

#include <kernel/macros.h>
#include <kernel/config.h>

#include <confname.h>

/* For debugging. Set to empty definition when done */
#ifdef CONFIG_ULTRA_VERBOSE
#define ultra_verbose(x...) pr_debug(x)
#else
#define ultra_verbose(x...)
#endif

#define pr_debug(x...) kprintf(x)
#define pr_info(x...)  kprintf(x)
#define pr_warn(x...)  kprintf("WARNING: "  x)
#define pr_err(x...)   kprintf("ERROR: "    x)
#define pr_alert(x...) kprintf("ALERT: "    x)
#define pr_crit(x...)  kprintf("CRITICAL: " x)

/* Address space attributes */
#define AS_ATTR_NONE    0
#define AS_ATTR_RAM     (AS_ATTR_READABLE|AS_ATTR_WRITABLE|AS_ATTR_CACHABLE)
#define AS_ATTR_ROM     (AS_ATTR_READABLE|AS_ATTR_CACHABLE)
#define AS_ATTR_DEV     (AS_ATTR_READABLE|AS_ATTR_WRITABLE)
#define AS_OVERLAY_IO   0x80000000

/* Page protection bits */
#define PROT_READ       0x00000100  /* pages can be read      */
#define PROT_WRITE      0x00000200  /* pages can be written   */
#define PROT_EXEC       0x00000400  /* pages can be executed  */
#define PROT_NOCACHE    0x00000800  /* pages are not cached   */
#define PROT_USER       0x00001000  /* pages are accessable to user */

enum startup_info_types {
    STARTUP_INFO_SKIP = 0,      /* If size 0 then end of list */
    STARTUP_INFO_MEM,
    STARTUP_INFO_DISK,
    STARTUP_INFO_TIME,
    STARTUP_INFO_BOX,
    STARTUP_INFO_USER = 0x8000  /* User reserved numbers start here */
};

struct startup_info_hdr {
    unsigned short type;
    unsigned short size;
};

struct startup_info_skip {
    struct startup_info_hdr hdr;
};

struct startup_info_mem {
    struct startup_info_hdr hdr;
    uint64_t addr;
    uint64_t size;
};

struct startup_info_time {
    struct startup_info_hdr hdr;
    unsigned long time;
};

struct startup_info_box {
    struct startup_info_hdr hdr;
    unsigned char boxtype;
    unsigned char bustype;
    unsigned char spare[2];
};

struct bootargs_entry {
    uint8_t size_lo;    /* Includes entire structure */
    uint8_t size_hi;
    int8_t  argc, envc;
    paddr_t shdr_addr;
    char    args[];     /* variable length */
};


#if defined(__LITTLEENDIAN__) || defined(__X86__)
#define __SC(ch,pos)		((_Uint64t)(ch)<<((pos)*8))
#else
#define __SC(ch,pos)		((_Uint64t)(ch)<<((7-(pos))*8))
#endif
#define __STACK_SIG (__SC('d',0)+__SC('d',1)+__SC('p',2)+__SC('v',3) \
					+__SC('b',4)+__SC('s',5)+__SC('k',6)+__SC('r',7))

struct startup_trailer {
    unsigned long cksum;        /* Checksum from start of header to start of trailer */
};

/* this ASSERT is intentionally meant to not be conditionally implemented */
#define ASSERT(_c_) \
		do { \
			if (!(_c_)) \
			{ \
				const char *s = strrchr(__FILE__, '/'); \
				crash("%s:%d -- ASSERT(%s) failed!\n", (s != NULL) ? s + 1 : __FILE__, __LINE__, #_c_); \
			} \
		} while(0)

#define SYSPAGE_TYPED_SECTION(type, field)	\
		struct field##_section {			\
			type			*p;				\
			unsigned		size;			\
		}						field

#define SYSPAGE_SECTION(field)	SYSPAGE_TYPED_SECTION(struct field##_entry, field)

#include <arch/cpu_startup.h>

#if !defined(MAKE_1TO1_PTR)
#define MAKE_1TO1_PTR(p)	((void *)((paddr_t)(p) + STARTUP_PADDR_BIAS))
#endif

#ifndef __PAGESIZE
#define __PAGESIZE 4096
#endif

#define NULL_PADDR	(~(paddr_t)0)
#define MAX_PADDR	0x7FFFFFFFFF    /* For 39-bit address space */

unsigned arch_max_paddr_bits(void);

// TODO: review
//#define NULL_PADDR32	(~(paddr32_t)0)
//#define MAX_PADDR32     0xffffffff

#define TRUNC(_x,_a)  ((paddr_t)(_x) & ~(((paddr_t)(_a))-1))
#define ROUND(_x,_a)  TRUNC(((paddr_t)(_x)) + ((paddr_t)(_a)-1), (paddr_t)(_a))

#define TRUNCPG(_x)	TRUNC((_x), __PAGESIZE)
#define ROUNDPG(_x)	ROUND((_x), __PAGESIZE)

#define TOPTR(x)		((void *)(x))

#define PTR_DIFF(a,b)	((uint8_t *)(a) - (uint8_t *)(b))

#define COMMON_OPTIONS_STRING   CPU_COMMON_OPTIONS_STRING "ACD:F:f:I:i:K:M:N:P:R:S:Tvr:j:Z"

struct local_syspage {
    SYSPAGE_SECTION(syspage);
    SYSPAGE_SECTION(system_private);
    SYSPAGE_SECTION(asinfo);
    SYSPAGE_SECTION(hwinfo);
    SYSPAGE_SECTION(cpuinfo);
    SYSPAGE_SECTION(cacheattr);
    SYSPAGE_SECTION(qtime);
    SYSPAGE_SECTION(typed_strings);
    SYSPAGE_SECTION(strings);
    SYSPAGE_SECTION(intrinfo);
    SYSPAGE_SECTION(smp);
    SYSPAGE_SECTION(pminfo);
#ifdef CONFIG_MINIDRIVER
    SYSPAGE_SECTION(mdriver);
#endif
    struct cpu_local_syspage cpu;
};

struct debug_device {
    const char *name;
    const char *defaults[2];
    void (*init)(unsigned channel, const char *name, const char *defaults);
    void (*put)(int c);
};

struct startup_intrinfo {
    uint32_t vector_base;
    uint32_t num_vectors;
    uint32_t cascade_vector;
    uint32_t cpu_intr_base;
    uint16_t cpu_intr_stride;
    uint16_t flags;
};

typedef struct {
    paddr_t base;
    unsigned shift;
} chip_info;

#endif
