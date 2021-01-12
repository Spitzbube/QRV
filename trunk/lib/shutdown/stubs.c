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


#include <sys/shutdown.h>

/* Stubs which can be overridden in the application using libshutdown */

ProcessClass_t shutdown_classify(ProcessInfo_t const *pip)
{
    return CLASS_UNKNOWN;
}

void shutdown_display(int type,DisplayData_t const *display)
{
}

void shutdown_done(int type)
{
}

void shutdown_error(char const *msg)
{
}

void shutdown_process(void)
{
}

void shutdown_progress(int done,int total)
{
}

int shutdown_prompt(char const *name,pid_t pid)
{
	return(PROMPT_SKIP);
}