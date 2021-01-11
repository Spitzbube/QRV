/**
 * \file lzo1.h
 *
 * Public interface of the LZO1 compression algorithm.
 *
 * This file is part of the LZO real-time data compression library.
 *
 * \copyright (C) 1998-99 Markus Franz Xaver Johannes Oberhumer
 *                        <markus.oberhumer@jk.uni-linz.ac.at>
 *                        http://wildsau.idv.uni-linz.ac.at/mfx/lzo.html
 *
 * \license GNU GPL 2.0
 */


#ifndef __LZO1_H
#define __LZO1_H

#ifndef __LZOCONF_H
#include <lzoconf.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif


/***********************************************************************
//
************************************************************************/

/* Memory required for the wrkmem parameter.
 * When the required size is 0, you can also pass a NULL pointer.
 */

#define LZO1_MEM_COMPRESS       ((lzo_uint32) (8192L * lzo_sizeof_dict_t))
#define LZO1_MEM_DECOMPRESS     (0)


LZO_EXTERN(int)
lzo1_compress           ( const lzo_byte *src, lzo_uint  src_len,
                                lzo_byte *dst, lzo_uint *dst_len,
                                lzo_voidp wrkmem );

LZO_EXTERN(int)
lzo1_decompress         ( const lzo_byte *src, lzo_uint  src_len,
                                lzo_byte *dst, lzo_uint *dst_len,
                                lzo_voidp wrkmem /* NOT USED */ );


/***********************************************************************
// better compression ratio at the cost of more memory and time
************************************************************************/

#define LZO1_99_MEM_COMPRESS    ((lzo_uint32) (65536L * lzo_sizeof_dict_t))

#if !defined(LZO_99_UNSUPPORTED)
LZO_EXTERN(int)
lzo1_99_compress        ( const lzo_byte *src, lzo_uint  src_len,
                                lzo_byte *dst, lzo_uint *dst_len,
                                lzo_voidp wrkmem );
#endif



#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* already included */

