/**
 * \file sys/_synctypes.h
 *
 * Synchronization structures (sync_t and sync_attr_t).
 *
 * \copyright 2009, QNX Software Systems. All Rights Reserved.
 *
 * \license QNX NCEULA 1.01
 *          http://www.qnx.com/legal/licensing/dev_license/eula/nceula1_01.html
 */

#ifndef _SYS_SYNCTYPES_H
#define _SYS_SYNCTYPES_H

/*
 * owner
 *  -1       Static initalized mutex which is auto created on SyncWait
 *  -2       Destroyed mutex
 *  -3       Named semaphore (the count is used as an fd)
 */
typedef struct _sync {
    long          count;        /* Count for recursive mutexes and semaphores */
    unsigned long owner;        /* Thread id (valid for mutex only) */
} sync_t;

typedef struct _sync_attr {
    int protocol;
    int flags;
    int prioceiling;            /* Not implemented yet */
    int clockid;                /* Condvars only */
    int reserved[4];
} sync_attr_t;

#endif
