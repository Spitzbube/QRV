/**
 * \file sys/_offsettypes.h
 *
 * Definitions of off_t and similar types for offsets.
 *
 * \author Yuri Zaporozhets <r_tty@yahoo.co.uk>
 * \license GNU GPL 2.0
 */

#ifndef _SYS_OFFSETTYPES_H
#define _SYS_OFFSETTYPES_H

#include <stdint-gcc.h>

/*
 * On a 64-bit system with LP64 model the following types are equivalent
 */
typedef long off_t;
typedef off_t _off_t;

typedef long long off64_t;
typedef off64_t _off64_t;

/* File position */
typedef off_t fpos_t;

#endif
