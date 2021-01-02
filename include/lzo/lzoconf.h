/**
 * \file lzoconf.h
 *
 * Configuration for the LZO real-time data compression library.
 *
 * \copyright (C) 1999 Markus Franz Xaver Johannes Oberhumer
 *                     <markus.oberhumer@jk.uni-linz.ac.at>
 *
 * \license GNU GPL 2.0
 */

#ifndef __LZOCONF_H
#define __LZOCONF_H

#define LZO_VERSION             0x1060
#define LZO_VERSION_STRING      "1.06"
#define LZO_VERSION_DATE        "Nov 29 1999"

#include <limits.h>

#ifdef __cplusplus
extern "C" {
#endif


/***********************************************************************
// LZO requires a conforming <limits.h>
************************************************************************/

#if !defined(CHAR_BIT) || (CHAR_BIT != 8)
#  error "invalid CHAR_BIT"
#endif
#if !defined(UCHAR_MAX) || !defined(UINT_MAX) || !defined(ULONG_MAX)
#  error "check your compiler installation"
#endif
#if (USHRT_MAX < 1 ) || (UINT_MAX < 1) || (ULONG_MAX < 1)
#  error "your limits.h macros are broken"
#endif

/* workaround a cpp bug under hpux 10.20 */
#define LZO_0xffffffffL     4294967295ul


/***********************************************************************
// integral and pointer types
************************************************************************/

/* Integral types with 32 bits or more */
typedef uint32_t      lzo_uint32;
typedef int32_t       lzo_int32;
typedef unsigned int  lzo_uint;
typedef int           lzo_int;

/* no typedef here because of const-pointer issues */
#define lzo_byte     unsigned char
#define lzo_bytep    unsigned char *
#define lzo_charp    char *
#define lzo_voidp    void *
#define lzo_shortp   short *
#define lzo_ushortp  unsigned short *
#define lzo_uint32p  lzo_uint32 *
#define lzo_int32p   lzo_int32 *
#define lzo_uintp    lzo_uint *
#define lzo_intp     lzo_int *
#define lzo_voidpp   lzo_voidp *
#define lzo_bytepp   lzo_bytep *

typedef int lzo_bool;

#ifndef lzo_sizeof_dict_t
#  define lzo_sizeof_dict_t     sizeof(lzo_bytep)
#endif


/***********************************************************************
// function types
************************************************************************/

typedef int
( *lzo_compress_t)   ( const lzo_byte *src, lzo_uint  src_len,
                                        lzo_byte *dst, lzo_uint *dst_len,
                                        lzo_voidp wrkmem );

typedef int
( *lzo_decompress_t) ( const lzo_byte *src, lzo_uint  src_len,
                                        lzo_byte *dst, lzo_uint *dst_len,
                                        lzo_voidp wrkmem );

typedef int
( *lzo_optimize_t)   (       lzo_byte *src, lzo_uint  src_len,
                                        lzo_byte *dst, lzo_uint *dst_len,
                                        lzo_voidp wrkmem );

typedef int
( *lzo_compress_dict_t)(const lzo_byte *src, lzo_uint  src_len,
                                        lzo_byte *dst, lzo_uint *dst_len,
                                        lzo_voidp wrkmem,
                                  const lzo_byte *dict, lzo_uint dict_len );

typedef int
( *lzo_decompress_dict_t)(const lzo_byte *src, lzo_uint  src_len,
                                        lzo_byte *dst, lzo_uint *dst_len,
                                        lzo_voidp wrkmem,
                                  const lzo_byte *dict, lzo_uint dict_len );


/* a progress indicator callback function */
typedef void ( *lzo_progress_callback_t) (lzo_uint, lzo_uint);


/***********************************************************************
// error codes and prototypes
************************************************************************/

/* Error codes for the compression/decompression functions. Negative
 * values are errors, positive values will be used for special but
 * normal events.
 */
#define LZO_E_OK                    0
#define LZO_E_ERROR                 (-1)
#define LZO_E_OUT_OF_MEMORY         (-2)    /* not used right now */
#define LZO_E_NOT_COMPRESSIBLE      (-3)    /* not used right now */
#define LZO_E_INPUT_OVERRUN         (-4)
#define LZO_E_OUTPUT_OVERRUN        (-5)
#define LZO_E_LOOKBEHIND_OVERRUN    (-6)
#define LZO_E_EOF_NOT_FOUND         (-7)
#define LZO_E_INPUT_NOT_CONSUMED    (-8)


/* lzo_init() should be the first function you call.
 * Check the return code !
 *
 * lzo_init() is a macro to allow checking that the library and the
 * compiler's view of various types are consistent.
 */
#define lzo_init() __lzo_init2(LZO_VERSION,(int)sizeof(short),(int)sizeof(int),\
    (int)sizeof(long),(int)sizeof(lzo_uint32),(int)sizeof(lzo_uint),\
    (int)lzo_sizeof_dict_t,(int)sizeof(char *),(int)sizeof(lzo_voidp),\
    (int)sizeof(lzo_compress_t))
LZO_EXTERN(int) __lzo_init2(unsigned,int,int,int,int,int,int,int,int,int);

/* version functions (useful for shared libraries) */
LZO_EXTERN(unsigned) lzo_version(void);
LZO_EXTERN(const char *) lzo_version_string(void);
LZO_EXTERN(const char *) lzo_version_date(void);
LZO_EXTERN(const lzo_charp) _lzo_version_string(void);
LZO_EXTERN(const lzo_charp) _lzo_version_date(void);

/* string functions */
LZO_EXTERN(int)
lzo_memcmp(const lzo_voidp _s1, const lzo_voidp _s2, lzo_uint _len);
LZO_EXTERN(lzo_voidp)
lzo_memcpy(lzo_voidp _dest, const lzo_voidp _src, lzo_uint _len);
LZO_EXTERN(lzo_voidp)
lzo_memmove(lzo_voidp _dest, const lzo_voidp _src, lzo_uint _len);
LZO_EXTERN(lzo_voidp)
lzo_memset(lzo_voidp _s, int _c, lzo_uint _len);

/* checksum functions */
LZO_EXTERN(lzo_uint32)
lzo_adler32(lzo_uint32 _adler, const lzo_byte *_buf, lzo_uint _len);
LZO_EXTERN(lzo_uint32)
lzo_crc32(lzo_uint32 _c, const lzo_byte *_buf, lzo_uint _len);

/* memory allocation functions */
LZO_EXTERN(lzo_bytep) lzo_alloc(lzo_uint _nelems, lzo_uint _size);
LZO_EXTERN(lzo_bytep) lzo_malloc(lzo_uint _size);
LZO_EXTERN(void) lzo_free(lzo_voidp _ptr);

extern lzo_bytep ( *lzo_alloc_hook) (lzo_uint,lzo_uint);
extern void ( *lzo_free_hook) (lzo_voidp);

/* misc. */
LZO_EXTERN(lzo_bool) lzo_assert(int _expr);
LZO_EXTERN(int) _lzo_config_check(void);
typedef union { lzo_bytep p; lzo_uint u; } __lzo_pu_u;
typedef union { lzo_bytep p; lzo_uint32 u32; } __lzo_pu32_u;

/* align a char pointer on a boundary that is a multiple of `size' */
LZO_EXTERN(unsigned) __lzo_align_gap(const lzo_voidp _ptr, lzo_uint _size);
#define LZO_PTR_ALIGN_UP(_ptr,_size) \
    ((_ptr) + (lzo_uint) __lzo_align_gap((const lzo_voidp)(_ptr),(lzo_uint)(_size)))

/* deprecated - only for backward compatibility */
#define LZO_ALIGN(_ptr,_size) LZO_PTR_ALIGN_UP(_ptr,_size)


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* already included */

