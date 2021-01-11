#ifndef _SYS_LIBC_CFG_H
#define _SYS_LIBC_CFG_H

#if defined(__m68k__) || defined(__mc68000__) || defined(__riscv)
#define _READ_WRITE_RETURN_TYPE _ssize_t
#endif

#define _READ_WRITE_BUFSIZE_TYPE int

#endif
