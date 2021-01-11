/*
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Berkeley Software Design, Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)cdefs.h	8.7 (Berkeley) 1/21/94
 */

#ifndef __CDEFS_H_INCLUDED
#define __CDEFS_H_INCLUDED

/* Try to keep host system's version from coming in */
#ifndef _SYS_CDEFS_H_INCLUDED
  #define	_SYS_CDEFS_H_INCLUDED
#endif

#define _HAS_NAMESPACE	1	/* 1 for C++ names in std */
#define _STD_USING	1	/* exports C names in global */

#if defined (__cplusplus) || defined(__CPLUSPLUS__)
 #define _XSTD				::std::
 #define _X_STD_BEGIN		namespace std {
 #define _X_STD_END			}
_X_STD_BEGIN
_X_STD_END

 #if _ALT_NS > 0
  #define _STD				::_Dinkum_std::
  #define _STD_BEGIN		namespace _Dinkum_std {
  #define _STD_END			}
  #if _ALT_NS == 1		/* define C library in global namespace */
   #define _CSTD			::
   #define _C_STD_BEGIN
   #define _C_STD_END
  #else	/* define both C and C++ in namespace _Dinkum_std */
   #define _CSTD			::_Dinkum_std::
   #define _C_STD_BEGIN		namespace _Dinkum_std {
   #define _C_STD_END		}
  #endif /* _ALT_NS */
_STD_BEGIN
_STD_END
_X_STD_BEGIN
	using namespace _Dinkum_std;
_X_STD_END
 #else
  #define _STD				::std::
  #define _STD_BEGIN		namespace std {
  #define _STD_END			}
  #if defined(_STD_USING)
   #define _CSTD			::std::
   #define _C_STD_BEGIN		namespace std {
   #define _C_STD_END	}
  #else /* _STD_USING */
   #define _CSTD			::
   #define _C_STD_BEGIN
   #define _C_STD_END
  #endif
 #endif

 #if defined(_STD_USING)
  #undef _GLOBAL_USING		/* c* in std namespace, *.h imports to global */
 #endif

 #define _C_LIB_DECL		extern "C" {	/* C has extern "C" linkage */
 #define _END_C_LIB_DECL	}
 #define _EXTERN_C			extern "C" {
 #define _END_EXTERN_C		}

#else /* __cplusplus */

 #undef _STD_USING

 #define _STD
 #define _STD_BEGIN
 #define _STD_END

 #define _XSTD
 #define _X_STD_BEGIN
 #define _X_STD_END

 #define _CSTD
 #define _C_STD_BEGIN
 #define _C_STD_END

 #define _C_LIB_DECL
 #define _END_C_LIB_DECL
 #define _EXTERN_C
 #define _END_EXTERN_C
#endif /* __cplusplus */

#ifndef __BEGIN_DECLS
	#define	__BEGIN_DECLS	_C_LIB_DECL
#endif
#ifndef __END_DECLS
	#define	__END_DECLS	_END_C_LIB_DECL
#endif

#ifndef _NO_RETURN
#define _NO_RETURN(__fun)	void __fun
#endif

/*
 * The __CONCAT macro is used to concatenate parts of symbol names, e.g.
 * with "#define OLD(foo) __CONCAT(old,foo)", OLD(foo) produces oldfoo.
 * The __CONCAT macro is a bit tricky -- make sure you don't put spaces
 * in between its arguments.  __CONCAT can also concatenate double-quoted
 * strings produced by the __STRING macro, but this only works with ANSI C.
 */
#if defined(__STDC__) || defined(__cplusplus) || defined(__CPLUSPLUS__)
#undef __P
#define	__P(protos)	protos		/* full-blown ANSI C */
#define	__CONCAT(x,y)	x ## y
#define	__STRING(x)		#x

#define	__const		const		/* define reserved names to standard */
#define	__signed	signed
#define	__volatile	volatile

#if defined(__cplusplus)
#define	__inline	inline		/* convert to C++ keyword */
#else
#if !defined(__GNUC__) && !defined(__INTEL_COMPILER)
#define	__inline			/* delete GCC keyword */
#endif /* !__GNUC__ && !__INTEL_COMPILER */
#endif /* !__cplusplus */

#if __STDC_VERSION__ >= 199901L
#define __restrict	restrict
#endif

#else	/* !(__STDC__ || __cplusplus) */

#define	__P(protos)	()		/* traditional C preprocessor */
#define	__CONCAT(x,y)	x/**/y
#define	__STRING(x)	"x"

#endif	/* !(__STDC__ || __cplusplus) */

#define __WEAK_ALIAS(__alias, __tgt)			\
	__asm(".weak " #__alias);			\
	__asm(".equ "  #__alias ", " #__tgt)

/* Delete pseudo-keywords wherever they are not available or needed. */
#ifndef __dead
#define __dead
#define __pure

#endif

#endif /* !__CDEFS_H_ */
