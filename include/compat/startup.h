/*
 * In the comments the following letters designate who uses the info
 *
 *   I  - used by the legacy bootloader (QNX IPL)
 *   S  - used by the startup program
 *   IS - used by both the QNX IPL and the startup program
 */
struct legacy_startup_header {
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
