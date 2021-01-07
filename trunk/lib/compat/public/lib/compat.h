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
** definitions for cross platform dependencies
*/

#ifndef __COMPAT_H__
#define __COMPAT_H__

#if defined(__QNXNTO__)

#include <stdlib.h>
#include <sys/types.h>
#include <stdint.h>

/*
 * unix.h
 */
#ifndef MAXPATHLEN
#define MAXPATHLEN      _POSIX_PATH_MAX
#endif

#if !defined(max)
 #define max(a,b)  (((a) > (b)) ? (a) : (b))
#endif
#if !defined(min) && !defined(__cplusplus)
 #define min(a,b)  (((a) < (b)) ? (a) : (b))
#endif

#define NORMAL_OPEN_PERMS   0666
#define EXECTUTE_OPEN_PERMS 0777
#define FIXUP_FILE_MODE

#define NULL_DEVICE_NAME    "/dev/null"

#define QSSL_ROOT( n )          (n)
#define QSSL_ROOT_PATHLIST( n )     (n)
#define FN_CMP( n1, n2 )        strcmp( n1, n2 )
#define IS_EXE_NAME( n1, n2 )   (strcmp( n1, n2 )==0)

#define PATHSEP_STR         ":"
#define PATHSEP_CHR         ':'
#define DIRSEP_STR 			"/"
#define DIRSEP_CHAR			'/'

#define IS_DIRSEP( c )          ( (c) == '/' )
#define IS_ABSPATH( n )         ( (n)[0] == '/' )
#define HAS_PATH( n )           (strchr( n, '/' ) != 0)
#define FIRST_DIRSEP( n )		strchr( n, '/' )
#define LAST_DIRSEP( n )			strrchr( n, '/' )

#define SKIP_DRIVE(n)           (n)

#define MAKE_BINARY_FD( fd )
#define MAKE_BINARY_FP( fp )

extern char    *openbsd_dirname(char *path);
extern size_t  strlcpy( char *dst, const char *src, size_t siz );
extern void    strmode( mode_t mode, char *p );

#elif defined(__LINUX__)
#include <stddef.h>
#include <sys/types.h>
#include <stdint.h>
typedef unsigned long   ulong_t;

#if !defined(max)
 #define max(a,b)  (((a) > (b)) ? (a) : (b))
#endif
#if !defined(min) && !defined(__cplusplus)
 #define min(a,b)  (((a) < (b)) ? (a) : (b))
#endif

#define NORMAL_OPEN_PERMS 	0666
#define EXECTUTE_OPEN_PERMS 0777
#define FIXUP_FILE_MODE

#define NULL_DEVICE_NAME	"/dev/null"

#define QSSL_ROOT( n )			(n)
#define QSSL_ROOT_PATHLIST( n )		(n)
#define FN_CMP( n1, n2 )		strcmp( n1, n2 )
#define IS_EXE_NAME( n1, n2 )	(strcmp( n1, n2 )==0)

#define PATHSEP_STR			":"
#define PATHSEP_CHR			':'
#define DIRSEP_STR 			"/"
#define DIRSEP_CHAR			'/'

#define IS_DIRSEP( c )			( (c) == '/' )
#define IS_ABSPATH( n )			( (n)[0] == '/' )
#define HAS_PATH( n )			(strchr( n, '/' ) != 0)
#define FIRST_DIRSEP( n )			strchr( n, '/' )
#define LAST_DIRSEP( n )			strrchr( n, '/' )
#define SKIP_DRIVE(n)			(n)

#define MAKE_BINARY_FD( fd )
#define MAKE_BINARY_FP( fp )

#define O_BINARY (0)
#define EOK 0
#define stricmp 	strcasecmp
#define strnicmp 	strncasecmp

#define eaccess		access

extern char *_fullpath( char *buffer, const char *path, size_t size);
extern char *pathfind(__const char *__path, __const char *__name, __const char *__mode);
extern int  memicmp( const void *__s1, const void *__s2, size_t __n );
extern char     *itoa( int __value, char *__buf, int __radix );
extern char     *ltoa( long int __value, char *__buf, int __radix );
extern char     *ultoa( unsigned long int __value, char *__buf, int __radix );
extern char     *utoa( unsigned int __value, char *__buf, int __radix );
extern char     *lltoa( int64_t __value, char *__buf, int __radix );
extern char     *ulltoa( u_int64_t __value, char *__buf, int __radix );
extern void     strmode( mode_t mode, char *p );
extern size_t   strlcpy( char *dst, const char *src, size_t siz );
extern off_t    tell( int __fildes );

/* from sys/stat.h */
#define _S_IFNAM    0x5000
#define S_IFNAM     _S_IFNAM

/* from disk.h */
#define _FLOPPY     1
#define _HARD       2
#define _RAMDISK    3
#define _DRIVER_NAME_LEN   12

/*
 *  Info about a QNX drive.
 *
 *  NOTE:  It is possible that cylinders, heads and track_sectors may be 0,
 *          in which case only disk_sectors describes the physical disk size.
 */
struct _disk_entry {
    unsigned long   blk_offset,
                    num_sectors, /* Num sectors in logical drive (partition) */
                    disk_sectors;/* Num sectors on physical disk    */
    unsigned short  cylinders,
                    heads,
                    track_sectors;
    unsigned char   disk_type,
                    disk_drv;           /*  Drive number as known to driver */
    long            reserved[3];
    unsigned char   driver_name[_DRIVER_NAME_LEN];
} __attribute__ ((packed));

/* from diskman.h */
#ifndef PAUSEphrase
 #define PAUSEphrase           "Please type the <Enter> key to continue..."
#endif

/* from confname.h */
#define __EXT_UNIX_MISC
#define _CS_HOSTNAME            2               /* Name of this node within the communications network */
#define _CS_RELEASE             3               /* Current release level of this implementation */
#define _CS_VERSION             4               /* Current version of this release */
#define _CS_MACHINE             5               /* Name of the hardware type on which the system is running */
#define _CS_ARCHITECTURE        6               /* Name of the instructions set architechure */
#define _CS_HW_SERIAL           7               /* A serial number assiciated with the hardware */
#define _CS_HW_PROVIDER         8               /* The name of the hardware manufacturers */
#define _CS_SRPC_DOMAIN         9               /* The secure RPC domain */
#define _CS_SYSNAME             11              /* Name of this implementation of the operating system */

#define __EXT_QNX
#define _CS_LIBPATH             200             /* default path for runtime to find standard shared objects */
#define _CS_DOMAIN              201             /* Domain of this node within the communications network */
#define _CS_RESOLVE             202             /* In memory /etc/resolve.conf */
#define _CS_TIMEZONE            203             /* timezone string (TZ style) */
#define _CS_LOCALE              204             /* locale string */

#elif defined(__QNX__)
#if !defined(max)
#define max(a,b)  (((a) > (b)) ? (a) : (b))
#endif
#if !defined(min) && !defined(__cplusplus)
#define min(a,b)  (((a) < (b)) ? (a) : (b))
#endif

#define NORMAL_OPEN_PERMS   0666
#define EXECTUTE_OPEN_PERMS 0777
#define FIXUP_FILE_MODE

#define NULL_DEVICE_NAME    "/dev/null"

#define NORMAL_OPEN_PERMS   0666
#define EXECTUTE_OPEN_PERMS 0777
#define FIXUP_FILE_MODE

#define NULL_DEVICE_NAME    "/dev/null"

#define QSSL_ROOT( n )          (n)
#define QSSL_ROOT_PATHLIST( n )     (n)
#define FN_CMP( n1, n2 )        strcmp( n1, n2 )
#define IS_EXE_NAME( n1, n2 )   (strcmp( n1, n2 )==0)

#define PATHSEP_STR         ":"
#define PATHSEP_CHR         ':'
#define DIRSEP_STR 			"/"
#define DIRSEP_CHAR			'/'

#define IS_DIRSEP( c )          ( (c) == '/' )
#define IS_ABSPATH( n )         ( (n)[0] == '/' )
#define HAS_PATH( n )           (strchr( n, '/' ) != 0)
#define FIRST_DIRSEP( n )		strchr( n, '/' )
#define LAST_DIRSEP( n )			strrchr( n, '/' )
#define SKIP_DRIVE(n)           (n)

#define MAKE_BINARY_FD( fd )
#define MAKE_BINARY_FP( fp )
#else
    #error lib/compat.h not configured for system
#endif

#endif
