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
 *  sys/sem.h    UNIX98 IPC Semaphore facility
 *

 */
#ifndef _SEM_H_INCLUDED
#define _SEM_H_INCLUDED

#ifndef _IPC_H_INCLUDED
#include <sys/ipc.h>
#endif

#ifdef __EXT_XOPEN_EX

struct sem {
    unsigned short int semval;
    unsigned short int sempadding;
    pid_t sempid;
    unsigned short int semncnt;
    unsigned short int semzcnt;
};

struct semid_ds {
    struct ipc_perm sem_perm;
    struct sem *sem_base;
    unsigned short int sem_nsems;
    unsigned short int sempadding;
    time_t sem_otime;
    long sem_pad1;
    time_t sem_ctime;
    long sem_pad2;
    long sem_pad3[4];
};

struct sembuf {
    unsigned short int sem_num;
    short int sem_op;
    short int sem_flg;
};

/*
 * Semaphore operation flags
 */
#define SEM_UNDO		010000

/*
 * semctl() command definitions
 */
#define GETNCNT			3
#define GETPID			4
#define GETVAL			5
#define GETALL			6
#define GETZCNT			7
#define SETVAL			8
#define SETALL			9

__BEGIN_DECLS
#if 0
/*
 * UNIX98 Prototypes not currently supported.
 */
extern int semctl(int __semid, int __semnum, int __cmd, ...);
extern int semget(key_t __key, int __nsems, int __semflg);
extern int semop(int __semid, struct sembuf *__sops, size_t __nsops);
#endif

__END_DECLS
#endif
#endif
