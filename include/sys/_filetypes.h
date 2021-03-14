/**
 * \file sys/_filetypes.h
 *
 * Definitions of types related to file handling (devices, inodes, etc).
 *
 * \author Yuri Zaporozhets <r_tty@yahoo.co.uk>
 * \license GNU GPL 2.0
 */

#ifndef _SYS_FILETYPES_H
#define _SYS_FILETYPES_H

#include <stdint-gcc.h>

typedef uint32_t dev_t;
typedef uint64_t ino_t;
typedef uint64_t ino64_t;
typedef uint32_t mode_t;

typedef int nl_item;
typedef unsigned nlink_t;

/* Block counts */
typedef uint64_t blkcnt_t;
typedef uint64_t blkcnt64_t;
typedef uint64_t blksize_t;
typedef uint64_t fsblkcnt_t;
typedef uint64_t fsblkcnt64_t;
typedef uint64_t fsfilcnt_t;
typedef uint64_t fsfilcnt64_t;

#endif
