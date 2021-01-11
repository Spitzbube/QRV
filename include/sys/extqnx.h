/**
 * \file extqnx.h
 *
 * QNX-specific interfaces, not to be found in other Unix variants.
 *
 * \copyright 2009, QNX Software Systems. All Rights Reserved.
 *
 * \license QNX NCEULA 1.01
 *          http://www.qnx.com/legal/licensing/dev_license/eula/nceula1_01.html
 */

#ifndef _EXTQNX_H
#define _EXTQNX_H

/*** select.h ******************/
#ifdef _EXT_QNX_SELECT
struct sigevent;
struct timespec;
union sigval;

/* Deprecated interfaces */
int _select_event(int __maxfd, fd_set *__readfds, fd_set *__writefds,
			fd_set *__exceptfds, const struct timespec *__ts,
			struct sigevent *__event, int (*eventwait)(const struct timespec *__ts,
			union sigval *__value, void *__arg), void *__arg);
int _select_block(const struct timespec *__ts, union sigval *__value, void *__arg);
#endif

#endif
