/*
 * Copyright (c) 1995-1999 by P.J. Plauger. All rights reserved.
 * Consult your license regarding permissions and restrictions.
 */

/* Customize DINKUM libraries */
#if defined(__LITTLEENDIAN__)
#define _D0		3               /* 0: big endian, 3: little endian floating-point */
#elif defined(__BIGENDIAN__)
#define _D0		0               /* 0: big endian, 3: little endian floating-point */
#else
#error ENDIAN Not defined for system
#endif
#if __LONGDOUBLE_BITS__ == 64
#define _DLONG	0               /* 0: 64, 1: 80, 2: 128 long double bits */
#define _LBIAS	0x3fe           /* 64 long double bits */
#define _LOFF	4               /* 64 long double bits */
#elif __LONGDOUBLE_BITS__ == 80
#define _DLONG	1               /* 0: 64, 1: 80, 2: 128 long double bits */
#define _LBIAS	0x3ffe          /* 80/128 long double bits */
#define _LOFF	15              /* 80/128 long double bits */
#elif __LONGDOUBLE_BITS__ == 128
#define _DLONG	2               /* 0: 64, 1: 80, 2: 128 long double bits */
#define _LBIAS	0x3ffe          /* 80/128 long double bits */
#define _LOFF	15              /* 80/128 long double bits */
#error __LONGDOUBLE_BITS__ not a supported size
#endif

        /* FLOATING-POINT PROPERTIES */
#define _DBIAS	0x3fe           /* IEEE format double and float */
#define _DOFF	4
#define _FBIAS	0x7e
#define _FOFF	7
#define _FRND	1

        /* integer properties */
#define _BITS_BYTE	8
#define _C2		1           /* 0 if not 2's complement */
#if defined(__CHAR_SIGNED__)
#define _CSIGN		1           /* 0 if char is not signed */
#elif defined(__CHAR_UNSIGNED__)
#define _CSIGN		0           /* 0 if char is not signed */
#endif
#define _MBMAX		8           /* MB_LEN_MAX */

#define _MAX_EXP_DIG	8       /* for parsing numerics */
#define _MAX_INT_DIG	32
#define _MAX_SIG_DIG	48
