/* n2d_ds.c -- implementation of the NRV2D decompression algorithm

   This file is part of the UCL real-time data compression library.

   Copyright (C) 1996-2000 Markus Franz Xaver Johannes Oberhumer
 * \license GNU GPL 2.0

   Markus F.X.J. Oberhumer
   <markus.oberhumer@jk.uni-linz.ac.at>
   http://wildsau.idv.uni-linz.ac.at/mfx/ucl.html
 */


#define SAFE
#define ucl_nrv2d_decompress_8      ucl_nrv2d_decompress_safe_8
#define ucl_nrv2d_decompress_le16   ucl_nrv2d_decompress_safe_le16
#define ucl_nrv2d_decompress_le32   ucl_nrv2d_decompress_safe_le32
#include "n2d_d.c"
#undef SAFE


/*
vi:ts=4:et
*/

