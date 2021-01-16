/**
 * \file sys/_signaltypes.h
 *
 * Definition of signal structures.
 *
 * \copyright 2009, QNX Software Systems. All Rights Reserved.
 *
 * \license QNX NCEULA 1.01
 *          http://www.qnx.com/legal/licensing/dev_license/eula/nceula1_01.html
 */

#ifndef _SYS_SIGNALTYPES_H
#define _SYS_SIGNALTYPES_H

typedef struct {
    uint32_t bits[2];
} sigset_t;

typedef int sig_atomic_t;

/*
 * TODO
 */
union sigval {
    int sival_int;
    void *sival_ptr;
};

/*
 * Sigevent structure
 */
struct sigevent {
    int sigev_notify;
    union {
        int sigev_signo;
        int sigev_coid;
        int sigev_id;
        void (*sigev_notify_function)(union sigval);
    };

    union sigval sigev_value;
    union {
        struct {
            short sigev_code;
            short sigev_priority;
        };
        pthread_attr_t *sigev_notify_attributes;
    };
};

/*
 * Siginfo structure
 */
typedef struct _siginfo {
    int si_signo;
    int si_code;                /* if SI_NOINFO, only si_signo is valid */
    int si_errno;
    union {
        int __pad[7];
        struct {
            pid_t __pid;
            union {
                struct {
                    uid_t __uid;
                    union sigval __value;
                } __kill;       /* si_code <= 0 SI_FROMUSER */
                struct {
                    clock_t __utime;
                    int __status;   /* CLD_EXITED status, else signo */
                    clock_t __stime;
                } __chld;       /* si_signo=SIGCHLD si_code=CLD_* */
            } __pdata;
        } __proc;
        struct {
            int __fltno;
            void *__fltip;
            void *__addr;
            int __bdslot;
        } __fault;              /* si_signo=SIGSEGV,ILL,FPE,TRAP,BUS */
    };
} siginfo_t;

/*
 * Structure that specifies how to handle a signal
 */
struct sigaction {
    union {
        void (*sa_handler)(int);
        void (*sa_sigaction)(int, siginfo_t *, void *);
    };
    int sa_flags;
    sigset_t sa_mask;
};

#endif
