/**
 * \file sys/_pthreadtypes.h
 *
 * Some basic types and definitions for POSIX threads.
 *
 * \copyright 2009, QNX Software Systems. All Rights Reserved.
 *
 * \license QNX NCEULA 1.01
 *          http://www.qnx.com/legal/licensing/dev_license/eula/nceula1_01.html
 */

#ifndef _SYS_PTHREADTYPES_H
#define _SYS_PTHREADTYPES_H

#include <sys/_synctypes.h>
#include <sys/_schedtypes.h>

typedef int32_t pthread_t;
typedef int32_t pthread_key_t;

typedef sync_t          pthread_mutex_t;
typedef sync_attr_t     pthread_mutexattr_t;
typedef sync_t          pthread_cond_t;
typedef sync_attr_t     pthread_condattr_t;

/*
 * Structure for pthread_once()
 */
typedef struct _pthread_once {
    int         once;
    sync_t      mutex;
} pthread_once_t;

/*
 * Thread creation attributes.
 */
typedef struct _thread_attr {
    int         flags;
    size_t      stacksize;
    void        *stackaddr;
    void        (*exitfunc)(void *status);
    int         policy;
    sched_param_t sched_param;
    unsigned    guardsize;
    unsigned    prealloc;
    int         spare[2];
} pthread_attr_t;

#endif
