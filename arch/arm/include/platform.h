/*
 * $QNXLicenseC:
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
 * $
 */



/*
 *  arm/platform.h
 *

 */

#ifndef _ARM_PLATFORM_H_INCLUDED
#define _ARM_PLATFORM_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#error arm/platform.h should not be included directly.
#endif

#if defined(__QNXNTO__)

/*
 * jmp_buf saves/restores only the callee-saved registers and return pc
 */
#define __JMPBUFSIZE 	10
typedef unsigned 		__jmpbufalign;

#else
#error Not configured for target
#endif

#endif
