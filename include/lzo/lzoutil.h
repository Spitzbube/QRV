/* lzoutil.h -- utilities for the LZO real-time data compression library

   This file is part of the LZO real-time data compression library.

   Copyright (C) 1999 Markus Franz Xaver Johannes Oberhumer
   Copyright (C) 1998 Markus Franz Xaver Johannes Oberhumer
   If not, write to the Free Software Foundation, Inc.,
   59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

   Markus F.X.J. Oberhumer
   <markus.oberhumer@jk.uni-linz.ac.at>
   http://wildsau.idv.uni-linz.ac.at/mfx/lzo.html
 */


#ifndef __LZOUTIL_H
#define __LZOUTIL_H

#ifndef __LZOCONF_H
#include <lzoconf.h>
#endif

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif


/***********************************************************************
//
************************************************************************/

LZO_EXTERN(lzo_uint)
lzo_fread(FILE *f, lzo_voidp buf, lzo_uint size);
LZO_EXTERN(lzo_uint)
lzo_fwrite(FILE *f, const lzo_voidp buf, lzo_uint size);


#if (LZO_UINT_MAX <= UINT_MAX)
   /* avoid problems with Win32 DLLs */
#  define lzo_fread(f,b,s)      (fread(b,1,s,f))
#  define lzo_fwrite(f,b,s)     (fwrite(b,1,s,f))
#endif


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* already included */

