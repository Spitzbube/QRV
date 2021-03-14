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




#include <time.h>
#include <errno.h>
#include <inttypes.h>
#include <limits.h>

clock_t clock(void) {
	uint64_t						t;
	uint64_t						res;

	if(ClockTime_r(CLOCK_PROCESS_CPUTIME_ID, 0, &t) != EOK) {
		return (clock_t)-1;
	}

	res = t / ((uint64_t)1000000000 / CLOCKS_PER_SEC);

	if(res > (clock_t)ULONGLONG_MAX) {
		// Not representable
		return (clock_t)-1;
	}
	return res;
}
