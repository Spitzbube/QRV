/**
 * \file sys/_schedtypes.h
 *
 * Definition of sched_param_t.
 *
 * \copyright 2009, QNX Software Systems. All Rights Reserved.
 *
 * \license QNX NCEULA 1.01
 *          http://www.qnx.com/legal/licensing/dev_license/eula/nceula1_01.html
 */

#ifndef _SYS_SCHEDTYPES_H
#define _SYS_SCHEDTYPES_H

typedef struct sched_param {
    int32_t sched_priority;
    int32_t sched_curpriority;
    union {
        /* Make sure it occupies at least 32 bytes */
        int32_t _reserved[8];
        struct {
            int32_t ss_low_priority;
            int32_t ss_max_repl;
            struct timespec ss_repl_period;
            struct timespec ss_init_budget;
        };
    };
} sched_param_t;

#endif
