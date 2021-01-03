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
 *  sys/perfregs.h
 *

 */
#ifndef __PERFREGS_H_INCLUDED
#define __PERFREGS_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#ifndef __TYPES_H_INCLUDED
#include <sys/types.h>
#endif

#include <inttypes.h>

#define PERFREGS_ENABLED_FLAG	0x80000000
#define PERFREGS_SAVED_FLAG	0x40000000

#define PERFREGS_CPUID_SHIFT	16
#define PERFREGS_PARTID_SHIFT	0

#define PERFREGS_MAKEID(cpu,part)	((cpu) << PERFREGS_CPUID_SHIFT)|((part) << PERFREGS_PARTID_SHIFT)

#endif
