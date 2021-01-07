/* ucl_dll.c -- DLL initialization of the UCL library

   This file is part of the UCL real-time data compression library.

   Copyright (C) 1996-2000 Markus Franz Xaver Johannes Oberhumer
 * \license GNU GPL 2.0

   Markus F.X.J. Oberhumer
   <markus.oberhumer@jk.uni-linz.ac.at>
   http://wildsau.idv.uni-linz.ac.at/mfx/ucl.html
 */


#include "ucl_conf.h"


/***********************************************************************
// Windows 16 bit + Watcom C + DLL
************************************************************************/

#if defined(__UCL_WIN16) && defined(__WATCOMC__) && defined(__SW_BD)

/* don't pull in <windows.h> - we don't need it */
#if 0
#include <windows.h>
#endif

#pragma off (unreferenced);
#if 0 && defined(WINVER)
BOOL FAR PASCAL LibMain ( HANDLE hInstance, WORD wDataSegment,
                          WORD wHeapSize, LPSTR lpszCmdLine )
#else
int __far __pascal LibMain ( int a, short b, short c, long d )
#endif
#pragma on (unreferenced);
{
    return 1;
}

#endif



/*
vi:ts=4:et
*/
