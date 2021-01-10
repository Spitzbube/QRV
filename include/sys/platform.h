/**
 * \file sys/platform.h
 *
 *  The only symbols made visible by this header are
 *  OS/compiler reserved symbols.
 *
 * \license
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
 */

#ifndef __PLATFORM_H_INCLUDED
#define __PLATFORM_H_INCLUDED

#include <arch/platform.h>
#include <sys/gcc_lp64.h>

#if !defined(__LINT)
#define __LINT(__expr)
#endif

#if !defined(__FLEXARY)
#define __FLEXARY(__type, __name) __type __name[1]
#endif

#if __INT_BITS__==16 && __LONG_BITS__==32 && __PTR_BITS__==32
#define __LP32__ 1
#define __LP32 1
#define _LP32 1
#elif __INT_BITS__==32 && __LONG_BITS__==32 && __PTR_BITS__==32
#define __ILP32__ 1
#define __ILP32 1
#define _ILP32 1
#elif __INT_BITS__==32 && __LONG_BITS__==32 && __PTR_BITS__==64
#define __LLP64__ 1
#define __LLP64 1
#define _LLP64 1
#elif __INT_BITS__==64 && __LONG_BITS__==64 && __PTR_BITS__==64
#define __ILP64__ 1
#define __ILP64 1
#define _ILP64 1
#elif __INT_BITS__==32 && __LONG_BITS__==64 && __PTR_BITS__==64
#define __LP64__ 1
#define __LP64 1
#define _LP64 1
#else
#error Uncommon model for int, long, pointer sizes
#endif

/*
 * PPC numbers its bits backwards from the rest of the known universe
 * (except for the 370, of course :-).
 */
#define _BITFIELD64B(__start_bit,__value)	((_Uint64t)(__value) << (63-(__start_bit)))
#define _BITFIELD32B(__start_bit,__value)	((__value) << (31-(__start_bit)))
#define _BITFIELD16B(__start_bit,__value)	((__value) << (15-(__start_bit)))
#define _BITFIELD8B(__start_bit,__value)	((__value) << ( 7-(__start_bit)))

#define _BITFIELD64L(__start_bit,__value)	((_Uint64t)(__value) << (__start_bit))
#define _BITFIELD32L(__start_bit,__value)	((__value) << (__start_bit))
#define _BITFIELD16L(__start_bit,__value)	((__value) << (__start_bit))
#define _BITFIELD8L(__start_bit,__value)	((__value) << (__start_bit))

#define	_ONEBIT64B(__start_bit)				_BITFIELD64B(__start_bit,1)
#define	_ONEBIT32B(__start_bit)				_BITFIELD32B(__start_bit,1)
#define	_ONEBIT16B(__start_bit)				_BITFIELD16B(__start_bit,1)
#define	_ONEBIT8B(__start_bit)				_BITFIELD8B(__start_bit,1)

#define	_ONEBIT64L(__start_bit)				_BITFIELD64L(__start_bit,1)
#define	_ONEBIT32L(__start_bit)				_BITFIELD32L(__start_bit,1)
#define	_ONEBIT16L(__start_bit)				_BITFIELD16L(__start_bit,1)
#define	_ONEBIT8L(__start_bit)				_BITFIELD8L(__start_bit,1)

#undef __EXT_ANSIC_199012	/* Additional ANSI C bindings */
#undef __EXT_ANSIC_199409	/* Ansi C Amendment 1 bindings */
#undef __EXT_ANSIC_199901	/* Ansi C99 bindings */
#undef __EXT_MATH_199001	/* IEEE 754-1985(R1990) IEEE std for Binary Floating-Point Arithmetic */
#undef __EXT_POSIX1_198808	/* Posix 1003.1 */
#undef __EXT_POSIX1_199009	/* Posix 1003.1 */
#undef __EXT_POSIX1_199309	/* Posix 1003.1b, XOPEN_RT */
#undef __EXT_POSIX1_199506	/* Posix 1003.1c, XOPEN_RTT */
#undef __EXT_POSIX1_200112	/* Posix 1003.1-2001 */
#undef __EXT_POSIX2		/* Posix 1003.2 */
#undef __EXT_QNX		/* QNX extentions */
#undef __EXT_XOPEN_EX		/* XOPEN extentions */
#undef __EXT_UNIX_MISC		/* UNIX definitions not defined by XOPEN */
#undef __EXT_UNIX_HIST		/* incompatible historic unix definitions */
#undef __EXT_BSD		/* BSD extensions */

#if defined(_XOPEN_SOURCE)
	#if _XOPEN_SOURCE-0 == 500
		#if _POSIX_C_SOURCE-0 > 199506
			#error This POSIX_C_SOURCE is unsuported with XOPEN_SOURCE
		#endif
	#elif _XOPEN_SOURCE-0 == 600
		#if _POSIX_C_SOURCE-0 > 200112
			#error This POSIX_C_SOURCE is unsuported with XOPEN_SOURCE
		#endif
	#else
		#error This version of XOPEN_SOURCE is not supported
	#endif
#endif

#if __STDC__-0 > 0 || defined(_QNX_SOURCE) || defined(_POSIX_SOURCE) || defined(_XOPEN_SOURCE) || (_POSIX_C_SOURCE+0 > 0) || defined(__EXT)
#define __EXT_ANSIC_199012
#endif

#if __STDC_VERSION__-0 >= 199409
#define __EXT_ANSIC_199409
#endif

#if __STDC_VERSION__-0 >= 199901
#define __EXT_ANSIC_199901			/* C99 */

#ifndef __STDC_HOSTED__				/* Hosted implementation */
#define __STDC_HOSTED__		1
#endif

#ifndef __STDC_ISO_10646__			/* ISO/IEC 10646 characters for wchar_t */
#define __STDC_ISO_10646__	200009L	/* this matches glibc, previous was 199712L */
#endif

#ifndef __STDC_IEC_559__			/* IEC 60559 floating-point arithmetic */
#define __STDC_IEC_559__	1
#endif

#ifndef __STDC_IEC_559_COMPLEX__	/* IEC 60559 compatible complex arithmetic */
#define __STDC_IEC_559_COMPLEX__	1
#endif

#endif

#if defined(_QNX_SOURCE) || defined(_POSIX_SOURCE) || defined(_XOPEN_SOURCE) || (_POSIX_C_SOURCE+0 > 0) || defined(__EXT)
#define __EXT_POSIX1_198808
#define __EXT_POSIX1_199009
#endif

#if defined(_QNX_SOURCE) || defined(_XOPEN_SOURCE) || (_POSIX_C_SOURCE+0 >= 199309) || (defined(__EXT) && !defined(_POSIX_SOURCE) && (_POSIX_C_SOURCE+0 <= 0))
#define __EXT_POSIX1_199309
#endif

#if defined(_QNX_SOURCE) || defined(_XOPEN_SOURCE) || (_POSIX_C_SOURCE+0 >= 199506) || (defined(__EXT) && !defined(_POSIX_SOURCE) && (_POSIX_C_SOURCE+0 <= 0))
#define __EXT_POSIX1_199506
#endif

#if defined(_QNX_SOURCE) || (_XOPEN_SOURCE+0 >= 600) || (_POSIX_C_SOURCE+0 >= 200112) || (defined(__EXT) && !defined(_POSIX_SOURCE) && (_POSIX_C_SOURCE+0 <= 0) && !defined(_XOPEN_SOURCE))
#define __EXT_POSIX1_200112
#endif

#if defined(_QNX_SOURCE) || defined(_XOPEN_SOURCE) || (_POSIX_C_SOURCE+0 == 2) || (_POSIX_C_SOURCE+0 >= 199506) || (defined(__EXT) && !defined(_POSIX_SOURCE) && (_POSIX_C_SOURCE+0 <= 0))
#define __EXT_POSIX2
#endif

#if defined(_QNX_SOURCE) || \
    (defined(__EXT) && !defined(__NO_EXT_QNX) && !defined(_POSIX_SOURCE) && !defined(_XOPEN_SOURCE) && (_POSIX_C_SOURCE+0 <= 0))
#define __EXT_QNX
#endif

#if defined(_QNX_SOURCE) || (defined(__EXT) && !defined(_POSIX_SOURCE) && !defined(_XOPEN_SOURCE) && (_POSIX_C_SOURCE+0 <= 0))
#define __EXT_BSD
#endif

#if defined(_QNX_SOURCE) || defined(_XOPEN_SOURCE) || (defined(__EXT) && !defined(_POSIX_SOURCE) && (_POSIX_C_SOURCE+0 <= 0))
#define __EXT_XOPEN_EX
#endif

#if defined(_QNX_SOURCE) || (_XOPEN_SOURCE+0 == 500) || (defined(__EXT) && !defined(_POSIX_SOURCE) && (_POSIX_C_SOURCE+0 <= 0))
#define __EXT_UNIX_MISC
#endif

#if defined(_QNX_SOURCE) || defined(_XOPEN_SOURCE) || (defined(__EXT) && !defined(_POSIX_SOURCE) && (_POSIX_C_SOURCE+0 <= 0))
#define __EXT_MATH_199001
#endif

#if defined(__UNIX_SOURCE)
#define __EXT_UNIX_HIST
#endif

#if !defined(_LARGEFILE64_SOURCE) && (defined(_QNX_SOURCE) || defined(__EXT)) && (!defined(_FILE_OFFSET_BITS) || _FILE_OFFSET_BITS == 32) && !defined(_POSIX_SOURCE) && (_POSIX_C_SOURCE+0 <= 0)
#define _LARGEFILE64_SOURCE 1
#endif

#if __INT_BITS__ == 32
#define _INT32		int
#define _UINT32		unsigned
#else
#define _INT32		_Int32t
#define _UINT32		_Uint32t
#endif

#undef __INTPTR_T
#define __INTPTR_T		_Intptrt

#undef __PTRDIFF_T
#define __PTRDIFF_T		_Intptrt

#define _LLONG_MAX      0x7fffffffffffffffLL
#define _ULLONG_MAX     0xffffffffffffffffULL

#ifdef __WCHAR_T
typedef __WCHAR_T		_Wchart;
#undef __WCHAR_T
#if !defined(__cplusplus)
#define __WCHAR_T		_Wchart
#endif
#endif

#ifdef __WINT_T
#undef __WINT_T
#define __WINT_T		_Wintt
#endif

#ifdef __MBSTATE_T
typedef __MBSTATE_T		_Mbstatet;
#undef __MBSTATE_T
#define __MBSTATE_T		_Mbstatet
#endif

#ifdef __OFF_T
typedef __OFF_T			_Offt;
#undef __OFF_T
#define __OFF_T			_Offt
#endif

#ifdef __OFF64_T
typedef __OFF64_T		_Off64t;
#undef __OFF64_T
#define __OFF64_T		_Off64t
#endif

/* _Fpost must be after _Offt and _Off64t */
#ifdef __FPOS_T
typedef __FPOS_T		_Fpost;
#undef __FPOS_T
#define __FPOS_T		_Fpost
#endif

#ifdef __EXT_QNX	/* Compatible with old headers */
#ifndef __INTEL_COMPILER
typedef _Int8t					_int8;
typedef _Int16t					_int16;
typedef _Int32t					_int32;
typedef _Int64t					_int64;
#endif /* __INTEL_COMPILER */
typedef _Intptrt				_intptr;
typedef _Uint8t					_uint8;
typedef _Uint16t				_uint16;
typedef _Uint32t				_uint32;
typedef _Uint64t				_uint64;
typedef _Uintptrt				_uintptr;
#endif

typedef _Uint64t				_Paddr64t;
typedef _Uint32t				_Paddr32t;
#if _PADDR_BITS - 0 == 64
typedef _Paddr64t				_Paddrt;
#elif !defined(_PADDR_BITS) || _PADDR_BITS - 0 == 32
typedef _Paddr32t				_Paddrt;
#else
#error _PADDR_BITS value is unsupported
#endif

#ifdef __cplusplus
_STD_BEGIN
typedef bool _Bool;
_STD_END
#endif /* __cplusplus */

#endif
