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
#include <sys/neutrino.h>

int timer_getexpstatus(timer_t timerid) {
	struct _timer_info		info;

	if(TimerInfo(0, timerid, _NTO_TIMER_RESET_OVERRUNS, &info) == -1) {
		return -1;
	}
	if((info.flags & _NTO_TI_ACTIVE) || !(info.flags & _NTO_TI_EXPIRED)) {
		errno = EINVAL;
		return -1;
	}
	return 0;
}


