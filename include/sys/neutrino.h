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
 *  sys/neutrino.h
 *

 */
#ifndef __NEUTRINO_H_INCLUDED
#define __NEUTRINO_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#ifndef __TYPES_H_INCLUDED
#include <sys/types.h>
#endif

#ifndef _SIGNAL_H_INCLUDED
#include <signal.h>
#endif

#ifndef _TIME_H_INCLUDED
#include <time.h>
#endif

#ifndef _LIMITS_H_INCLUDED
#include <limits.h>
#endif

#ifndef __STORAGE_H_INCLUDED
#include <sys/storage.h>
#endif

#ifndef __STATES_H_INCLUDED
#include <sys/states.h>
#endif

#define _NTO_VERSION	641     /* version number * 100 */

#define SYSMGR_PID		1
#define SYSMGR_CHID		1
#define SYSMGR_COID		_NTO_SIDE_CHANNEL   /* System process connection is always the first side channel */
#define SYSMGR_HANDLE	0

#include <stdint.h>
#include <arch/cpu_def.h>

__BEGIN_DECLS

__END_DECLS
#endif
