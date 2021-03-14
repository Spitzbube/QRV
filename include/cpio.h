/**
 * \file cpio.h
 *
 * Extended cpio format from POSIX.1.
 *
 * \copyright (C) 2019 Free Software Foundation, Inc.
 * \license GNU LGPL 2.1
 * \note This file is part of the GNU C Library.
 */

#ifndef _CPIO_H
#define _CPIO_H

/*
 * A cpio archive consists of a sequence of files.
 * Each file has a 76 byte header,
 * a variable length, NUL terminated filename,
 * and variable length file data.
 * A header for a filename "TRAILER!!!" indicates the end of the archive.
 *
 *
 * All the fields in the header are ISO 646 (approximately ASCII) strings
 * of octal numbers, left padded, not NUL terminated.
 */

typedef struct __attribute__ ((packed)) {
    char magic[6];              // must be "070707"
    char dev[6];
    char ino[6];
    char mode[6];               // see below for value
    char uid[6];
    char gid[6];
    char nlink[6];
    char rdev[6];               // only valid for chr and blk special files
    char mtime[11];
    char namesize[6];            // count includes terminating NUL in pathname
    char filesize[11];           // must be 0 for FIFOs and directories
} tCpioHeader

/* Value for the field c_magic */
#define MAGIC	"070707"

/* Values for c_mode, OR'd together */
#define C_IRUSR		000400
#define C_IWUSR		000200
#define C_IXUSR		000100
#define C_IRGRP		000040
#define C_IWGRP		000020
#define C_IXGRP		000010
#define C_IROTH		000004
#define C_IWOTH		000002
#define C_IXOTH		000001

#define C_ISUID		004000
#define C_ISGID		002000
#define C_ISVTX		001000

#define C_ISBLK		060000
#define C_ISCHR		020000
#define C_ISDIR		040000
#define C_ISFIFO	010000
#define C_ISSOCK	0140000
#define C_ISLNK		0120000
#define C_ISCTG		0110000
#define C_ISREG		0100000

#endif /* _CPIO_H */
