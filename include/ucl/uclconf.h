/* uclconf.h -- configuration for the UCL real-time data compression library

   This file is part of the UCL real-time data compression library.

   Copyright (C) 1996-2000 Markus Franz Xaver Johannes Oberhumer

   Markus F.X.J. Oberhumer
   <markus.oberhumer@jk.uni-linz.ac.at>
   http://wildsau.idv.uni-linz.ac.at/mfx/ucl.html
 */


#ifndef __UCLCONF_H
#define __UCLCONF_H

#define UCL_VERSION             0x009100L
#define UCL_VERSION_STRING      "0.91"
#define UCL_VERSION_DATE        "Apr 19 2000"

/* internal Autoconf configuration file - only used when building UCL */
#if defined(UCL_HAVE_CONFIG_H)
#  include <config.h>
#endif
#include <limits.h>

#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************************
// integral and pointer types
************************************************************************/

typedef uint32_t      ucl_uint32;
typedef int32_t       ucl_int32;
typedef unsigned int       ucl_uint;
typedef int                ucl_int;

/* no typedef here because of const-pointer issues */
#define ucl_byte                unsigned char 
#define ucl_bytep               unsigned char  *
#define ucl_charp               char  *
#define ucl_voidp               void  *
#define ucl_shortp              short  *
#define ucl_ushortp             unsigned short  *
#define ucl_uint32p             ucl_uint32  *
#define ucl_int32p              ucl_int32  *
#define ucl_uintp               ucl_uint  *
#define ucl_intp                ucl_int  *
#define ucl_voidpp              ucl_voidp  *
#define ucl_bytepp              ucl_bytep  *

typedef int ucl_bool;

#ifndef ucl_sizeof_dict_t
#  define ucl_sizeof_dict_t     sizeof(ucl_bytep)
#endif


/***********************************************************************
// function types
************************************************************************/

typedef int
( *ucl_compress_t)   ( const ucl_byte *src, ucl_uint  src_len,
                                        ucl_byte *dst, ucl_uint *dst_len,
                                        ucl_voidp wrkmem );

typedef int
( *ucl_decompress_t) ( const ucl_byte *src, ucl_uint  src_len,
                                        ucl_byte *dst, ucl_uint *dst_len,
                                        ucl_voidp wrkmem );

typedef int
( *ucl_optimize_t)   (       ucl_byte *src, ucl_uint  src_len,
                                        ucl_byte *dst, ucl_uint *dst_len,
                                        ucl_voidp wrkmem );

typedef int
( *ucl_compress_dict_t)(const ucl_byte *src, ucl_uint  src_len,
                                        ucl_byte *dst, ucl_uint *dst_len,
                                        ucl_voidp wrkmem,
                                  const ucl_byte *dict, ucl_uint dict_len );

typedef int
( *ucl_decompress_dict_t)(const ucl_byte *src, ucl_uint  src_len,
                                        ucl_byte *dst, ucl_uint *dst_len,
                                        ucl_voidp wrkmem,
                                  const ucl_byte *dict, ucl_uint dict_len );


/* a progress indicator callback function */
typedef struct
{
    void ( *callback) (ucl_uint, ucl_uint, int, ucl_voidp user);
    ucl_voidp user;
}
ucl_progress_callback_t;
#define ucl_progress_callback_p ucl_progress_callback_t  *


/***********************************************************************
// error codes and prototypes
************************************************************************/

/* Error codes for the compression/decompression functions. Negative
 * values are errors, positive values will be used for special but
 * normal events.
 */
#define UCL_E_OK                    0
#define UCL_E_ERROR                 (-1)
#define UCL_E_INVALID_ARGUMENT      (-2)
#define UCL_E_OUT_OF_MEMORY         (-3)
/* compression errors */
#define UCL_E_NOT_COMPRESSIBLE      (-101)
/* decompression errors */
#define UCL_E_INPUT_OVERRUN         (-201)
#define UCL_E_OUTPUT_OVERRUN        (-202)
#define UCL_E_LOOKBEHIND_OVERRUN    (-203)
#define UCL_E_EOF_NOT_FOUND         (-204)
#define UCL_E_INPUT_NOT_CONSUMED    (-205)
#define UCL_E_OVERLAP_OVERRUN       (-206)


/* ucl_init() should be the first function you call.
 * Check the return code !
 *
 * ucl_init() is a macro to allow checking that the library and the
 * compiler's view of various types are consistent.
 */
#define ucl_init() __ucl_init2(UCL_VERSION,(int)sizeof(short),(int)sizeof(int),\
    (int)sizeof(long),(int)sizeof(ucl_uint32),(int)sizeof(ucl_uint),\
    (int)ucl_sizeof_dict_t,(int)sizeof(char *),(int)sizeof(ucl_voidp),\
    (int)sizeof(ucl_compress_t))
extern (int) __ucl_init2(unsigned,int,int,int,int,int,int,int,int,int);

/* version functions (useful for shared libraries) */
extern unsigned ucl_version(void);
extern const char * ucl_version_string(void);
extern const char * ucl_version_date(void);
extern const ucl_charp _ucl_version_string(void);
extern const ucl_charp _ucl_version_date(void);

/* string functions */
extern int ucl_memcmp(const ucl_voidp _s1, const ucl_voidp _s2, ucl_uint _len);
extern ucl_voidp ucl_memcpy(ucl_voidp _dest, const ucl_voidp _src, ucl_uint _len);
extern ucl_voidp ucl_memmove(ucl_voidp _dest, const ucl_voidp _src, ucl_uint _len);
extern ucl_voidp ucl_memset(ucl_voidp _s, int _c, ucl_uint _len);

/* checksum functions */
extern (ucl_uint32)
ucl_adler32(ucl_uint32 _adler, const ucl_byte *_buf, ucl_uint _len);
extern (ucl_uint32)
ucl_crc32(ucl_uint32 _c, const ucl_byte *_buf, ucl_uint _len);

/* memory allocation functions */
extern ucl_voidp ucl_alloc(ucl_uint _nelems, ucl_uint _size);
extern ucl_voidp ucl_malloc(ucl_uint _size);
extern void ucl_free(ucl_voidp _ptr);

typedef ucl_voidp ( *ucl_alloc_hook_t) (ucl_uint, ucl_uint);
typedef void ( *ucl_free_hook_t) (ucl_voidp);

extern ucl_alloc_hook_t ucl_alloc_hook;
extern ucl_free_hook_t ucl_free_hook;

/* misc. */
extern ucl_bool ucl_assert(int _expr);
extern int _ucl_config_check(void);
typedef union { ucl_bytep p; ucl_uint u; } __ucl_pu_u;
typedef union { ucl_bytep p; ucl_uint32 u32; } __ucl_pu32_u;

/* align a char pointer on a boundary that is a multiple of `size' */
extern unsigned __ucl_align_gap(const ucl_voidp _ptr, ucl_uint _size);
#define UCL_PTR_ALIGN_UP(_ptr,_size) \
    ((_ptr) + (ucl_uint) __ucl_align_gap((const ucl_voidp)(_ptr),(ucl_uint)(_size)))


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* already included */
