/**
 * \file sys/libc_cfg.h
 *
 * C library configuration file.
 *
 * \license GNU GPL 2.0
 */

#ifndef _SYS_LIBC_CFG_H
#define _SYS_LIBC_CFG_H



#ifdef __riscv
/* Use signed return type for read/write functions */
#define _READ_WRITE_RETURN_TYPE ssize_t
#else
#define _READ_WRITE_RETURN_TYPE size_t
#endif

#define _READ_WRITE_BUFSIZE_TYPE int

#endif
