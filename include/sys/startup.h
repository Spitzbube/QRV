/*
 * \file sys/startup.h
 *
 * Startup header definitions
 *
 * \note For detailed explanation of various startup scenarios see
 *       Documentation/startup-layout.txt
 *
 * \license Apache 2.0 (http://www.apache.org/licenses/LICENSE-2.0)
 *
 * \copyright (c) 2008 QNX Software Systems.
 */

#ifndef __STARTUP_H_INCLUDED
#define __STARTUP_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

/*
 * In the comments the following letters designate who uses the info
 *
 *   I  - used by the legacy bootloader (QNX IPL)
 *   S  - used by the startup program
 *   IS - used by both the QNX IPL and the startup program
 */
struct startup_header {
    uint32_t    signature;      /* I  Header sig, see below */
    uint16_t    version;        /* I  Header vers, see below */
    uint8_t     flags1;         /* IS Misc flags, see below */
    uint8_t     flags2;         /*    Reserved */
    uint16_t    header_size;    /* S  sizeof(struct startup_header) */
    uint16_t    machine;        /* IS Machine type from sys/elf.h */
    paddr_t     startup_vaddr;  /* I  Virtual Address to transfer to after IPL is done */
    paddr_t     paddr_bias;     /* S  Value to add to physical address to get a
                                      value to put into a pointer and indirected through */
    paddr_t     image_paddr;    /* IS Physical address of image */
    paddr_t     ram_paddr;      /* IS Physical address of RAM to copy image to (startup_size bytes copied) */
    size_t      ram_size;       /* S  Amount of RAM used by the startup program
                                      and executables contained in the file system */
    uint32_t   startup_size;    /* I  Size of startup (never compressed) */
    uint32_t   stored_size;     /* I  Size of entire image */
    uint32_t   imagefs_paddr;   /* IS Set by IPL to where the imagefs is when startup runs */
    uint32_t   imagefs_size;    /* S  Size of uncompressed imagefs */
    uint16_t   preboot_size;    /* I  Size of loaded before header */
    uint16_t   zero0;           /*    Zeros */
    uint32_t   zero[3];         /*    Zeros */
    uint32_t   info[48];        /* IS Array of startup_info* structures */
};

/* We keep the flags as chars so they are endian neutral */
#define STARTUP_HDR_FLAGS1_VIRTUAL		0x01
#define STARTUP_HDR_FLAGS1_BIGENDIAN		0x02
#define STARTUP_HDR_FLAGS1_COMPRESS_MASK	0x1c
#define STARTUP_HDR_FLAGS1_COMPRESS_SHIFT	0x02
#define STARTUP_HDR_FLAGS1_COMPRESS_NONE	0x00
#define STARTUP_HDR_FLAGS1_COMPRESS_ZLIB	0x04
#define STARTUP_HDR_FLAGS1_COMPRESS_LZO		0x08
#define STARTUP_HDR_FLAGS1_COMPRESS_UCL		0x0c

/* All values are stored in target endian format */
#define STARTUP_HDR_SIGNATURE			0x00ff7eeb
#define STARTUP_HDR_VERSION			1


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

#endif                          /* __STARTUP_H_INCLUDED */
