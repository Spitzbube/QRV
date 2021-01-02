/*
 * \file ucontext.h
 *
 * Machine context structures/functions
 *
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
 *
 */

#ifndef _UCONTEXT_H_INCLUDED
#define _UCONTEXT_H_INCLUDED

#include <sys/platform.h>
#include <arch/context.h>
#include <signal.h>

#if defined(__SIGSET_T)
typedef __SIGSET_T sigset_t;
#undef __SIGSET_T
#endif

#if defined(__STACK_T)
typedef __STACK_T stack_t;
#undef __STACK_T
#endif

#if defined(__UCONTEXT_T)
typedef __UCONTEXT_T ucontext_t;
#undef __UCONTEXT_T
#endif

struct __ucontext_t {
    struct __ucontext_t *uc_link;
    sigset_t uc_sigmask;
    stack_t uc_stack;
    mcontext_t uc_mcontext;
};

__BEGIN_DECLS

#if 0
int	getcontext(ucontext_t *);
int	setcontext(const ucontext_t *);
void	makecontext(ucontext_t *, void (*)(), int, ...);
int	swapcontext(ucontext_t *, const ucontext_t *);
#endif

__END_DECLS
#endif
