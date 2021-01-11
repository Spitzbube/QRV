/**
 * \file sys/_types.h
 *
 * ANSI C namespace clean utility typedefs
 *
 * \note This file is a part of NewLib C library 3.2.0.
 *
 * This file defines various typedefs needed by the system calls that support
 * the C library.  Basically, they're just the POSIX versions with an '_'
 * prepended.  Targets shall use <machine/_types.h> to define their own
 *  internal types if desired.
 *
 * There are three define patterns used for type definitions.  Lets assume
 * xyz_t is a user type.
 *
 * The internal type definition uses __machine_xyz_t_defined.  It is defined by
 * <machine/_types.h> to disable a default definition in <sys/_types.h>. It
 * must not be used in other files.

 * User type definitions are guarded by __xyz_t_defined in glibc and
 * _XYZ_T_DECLARED in BSD compatible systems.
*/

#ifndef	_SYS__TYPES_H
#define _SYS__TYPES_H

#define __need_size_t
#define __need_wint_t

#include <stddef.h>
#include <machine/_types.h>

typedef __uint64_t __blkcnt_t;
typedef __uint64_t __blksize_t;
typedef __uint64_t __fsblkcnt_t;
typedef __uint64_t __fsfilcnt_t;

typedef long _off_t;

typedef int __pid_t;

typedef unsigned __dev_t;

/* UID and GID */
typedef unsigned __uid_t;
typedef unsigned __gid_t;

typedef __uint32_t __id_t;

/* _INO_T */
typedef unsigned long __ino_t;

typedef __uint32_t __mode_t;
__extension__ typedef long long _off64_t;

typedef _off_t __off_t;
typedef _off64_t __loff_t;
typedef long __key_t;

/*
 * We need fpos_t for the following, but it doesn't have a leading "_",
 * so we use _fpos_t instead.
 */
#ifndef __machine_fpos_t_defined
typedef long _fpos_t;		/* XXX must match off_t in <sys/types.h> */
				/* (and must be `long' for now) */
#endif

#ifdef __LARGE64_FILES
#ifndef __machine_fpos64_t_defined
typedef _off64_t _fpos64_t;
#endif
#endif

/* Defined by GCC provided <stddef.h> */
#undef __size_t

#ifndef __machine_size_t_defined
#ifdef __SIZE_TYPE__
typedef __SIZE_TYPE__ __size_t;
#else
#if defined(__INT_MAX__) && __INT_MAX__ == 2147483647
typedef unsigned int __size_t;
#else
typedef unsigned long __size_t;
#endif
#endif
#endif

#ifndef __machine_ssize_t_defined
#ifdef __SIZE_TYPE__
/* If __SIZE_TYPE__ is defined (gcc) we define ssize_t based on size_t.
   We simply change "unsigned" to "signed" for this single definition
   to make sure ssize_t and size_t only differ by their signedness. */
#define unsigned signed
typedef __SIZE_TYPE__ _ssize_t;
#undef unsigned
#else
#if defined(__INT_MAX__) && __INT_MAX__ == 2147483647
typedef int _ssize_t;
#else
typedef long _ssize_t;
#endif
#endif
#endif

typedef _ssize_t __ssize_t;

#ifndef __machine_mbstate_t_defined
/* Conversion state information.  */
typedef struct
{
  int __count;
  union
  {
    wint_t __wch;
    unsigned char __wchb[4];
  } __value;		/* Value so far.  */
} _mbstate_t;
#endif

#ifndef __machine_iconv_t_defined
/* Iconv descriptor type */
typedef void *_iconv_t;
#endif

#ifndef __machine_clock_t_defined
#define	_CLOCK_T_	unsigned long	/* clock() */
#endif

typedef	_CLOCK_T_	__clock_t;

#if defined(_USE_LONG_TIME_T) || __LONG_MAX__ > 0x7fffffffL
#define	_TIME_T_ long
#else
#define	_TIME_T_ __int_least64_t
#endif
typedef	_TIME_T_	__time_t;

#ifndef __machine_clockid_t_defined
#define	_CLOCKID_T_ 	unsigned long
#endif

typedef	_CLOCKID_T_	__clockid_t;

#define	_TIMER_T_	unsigned long
typedef	_TIMER_T_	__timer_t;

#ifndef __machine_sa_family_t_defined
typedef	__uint8_t	__sa_family_t;
#endif

#ifndef __machine_socklen_t_defined
typedef	__uint32_t	__socklen_t;
#endif

typedef	int		__nl_item;
typedef	unsigned	__nlink_t;
typedef	long		__suseconds_t;	/* microseconds (signed) */
typedef	unsigned long	__useconds_t;	/* microseconds (unsigned) */

/*
 * Must be identical to the __GNUCLIKE_BUILTIN_VAALIST definition in
 * <sys/cdefs.h>.  The <sys/cdefs.h> must not be included here to avoid cyclic
 * header dependencies.
 */
typedef	__builtin_va_list	__va_list;

#endif	/* _SYS__TYPES_H */
