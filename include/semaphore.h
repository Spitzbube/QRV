/**
 * \file semaphore.h
 *
  * Semaphore definitions.
  *
 * \copyright (C) 2002-2020 Free Software Foundation, Inc.
 * \license GNU LGPL 2.1
 * \note This file is part of the GNU C Library.
 *
 */

#ifndef _SEMAPHORE_H
#define _SEMAPHORE_H

#include <sys/platform.h>
#include <sys/types.h>

typedef sync_t sem_t;

__BEGIN_DECLS

#define SEM_FAILED      ((sem_t *)-1)
extern sem_t *sem_open(const char *__name, int __oflag, ...);
extern int sem_close(sem_t * __sem);
extern int sem_destroy(sem_t * __sem);
extern int sem_getvalue(sem_t * __sem, int *__value);
extern int sem_init(sem_t * __sem, int __pshared, unsigned __value);
extern int sem_post(sem_t * __sem);
extern int sem_trywait(sem_t * __sem);
extern int sem_unlink(const char *__name);
extern int sem_wait(sem_t * __sem);
extern int sem_timedwait(sem_t * __sem, const struct timespec *__abs_timeout);

__END_DECLS

#endif
