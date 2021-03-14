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
 *  trace.h     Trace data structures and definitions
 *
 */

#ifndef __TRACE_H_INCLUDED
#define __TRACE_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#ifndef __STATES_H_INCLUDED
#include <sys/states.h>
#endif

#include <sys/spinlock.h>

/* TraceEvent() - modes */
#define QRV_TRACE_ADDALLCLASSES     ((0x00000001<<28)|1)
#define QRV_TRACE_DELALLCLASSES     ((0x00000001<<28)|2)
#define QRV_TRACE_ADDCLASS          ((0x00000002<<28)|3)
#define QRV_TRACE_DELCLASS          ((0x00000002<<28)|4)
#define QRV_TRACE_ADDEVENT          ((0x00000003<<28)|5)
#define QRV_TRACE_DELEVENT          ((0x00000003<<28)|6)
#define QRV_TRACE_ADDEVENTHANDLER   ((0x00000005<<28)|7)
#define QRV_TRACE_DELEVENTHANDLER   ((0x00000003<<28)|8)
#define QRV_TRACE_INSERTEVENT       ((0x00000005<<28)|9)
#define QRV_TRACE_START             ((0x00000001<<28)|10)
#define QRV_TRACE_STOP              ((0x00000001<<28)|11)
#define QRV_TRACE_ALLOCBUFFER       ((0x00000003<<28)|12)
#define QRV_TRACE_DEALLOCBUFFER     ((0x00000001<<28)|13)
#define QRV_TRACE_FLUSHBUFFER       ((0x00000001<<28)|14)
#define QRV_TRACE_QUERYEVENTS       ((0x00000001<<28)|15)
#define QRV_TRACE_SETALLCLASSESFAST ((0x00000001<<28)|16)
#define QRV_TRACE_SETALLCLASSESWIDE ((0x00000001<<28)|17)
#define QRV_TRACE_SETCLASSFAST      ((0x00000002<<28)|18)
#define QRV_TRACE_SETCLASSWIDE      ((0x00000002<<28)|19)
#define QRV_TRACE_SETEVENTFAST      ((0x00000003<<28)|20)
#define QRV_TRACE_SETEVENTWIDE      ((0x00000003<<28)|21)
#define QRV_TRACE_SETCLASSPID       ((0x00000003<<28)|22)
#define QRV_TRACE_SETCLASSTID       ((0x00000004<<28)|23)
#define QRV_TRACE_SETEVENTPID       ((0x00000004<<28)|24)
#define QRV_TRACE_SETEVENTTID       ((0x00000005<<28)|25)
#define QRV_TRACE_CLRCLASSPID       ((0x00000002<<28)|26)
#define QRV_TRACE_CLRCLASSTID       ((0x00000002<<28)|27)
#define QRV_TRACE_CLREVENTPID       ((0x00000003<<28)|28)
#define QRV_TRACE_CLREVENTTID       ((0x00000003<<28)|29)
#define QRV_TRACE_INSERTSUSEREVENT  ((0x00000004<<28)|30)
#define QRV_TRACE_INSERTCUSEREVENT  ((0x00000004<<28)|31)
#define QRV_TRACE_INSERTUSRSTREVENT ((0x00000003<<28)|32)
#define QRV_TRACE_STARTNOSTATE      ((0x00000001<<28)|33)
#define QRV_TRACE_SETRINGMODE       ((0x00000001<<28)|34)
#define QRV_TRACE_SETLINEARMODE     ((0x00000001<<28)|35)
#define QRV_TRACE_ADDCLASSEVHANDLER ((0x00000004<<28)|36)
#define QRV_TRACE_DELCLASSEVHANDLER ((0x00000002<<28)|37)
#define QRV_TRACE_SKIPBUFFER        ((0x00000001<<28)|38)
#define QRV_TRACE_OVERWRITEBUFFER   ((0x00000001<<28)|39)
#define QRV_TRACE_QUERYVERSION      ((0x00000001<<28)|40)
#define QRV_TRACE_QUERYSUPPORT      ((0x00000001<<28)|41)
#define QRV_TRACE_INSERTSCLASSEVENT ((0x00000005<<28)|42)
#define QRV_TRACE_INSERTCCLASSEVENT ((0x00000005<<28)|43)

/* TraceEvent() - external classes */
enum {
    QRV_TRACE_EMPTY,
    QRV_TRACE_CONTROL,
    QRV_TRACE_KERCALL,
    QRV_TRACE_KERCALLENTER,
    QRV_TRACE_KERCALLEXIT,
    QRV_TRACE_KERCALLINT,
    QRV_TRACE_INT,
    QRV_TRACE_INTENTER,
    QRV_TRACE_INTEXIT,
    QRV_TRACE_PROCESS,
    QRV_TRACE_THREAD,
    QRV_TRACE_VTHREAD,
    QRV_TRACE_USER,
    QRV_TRACE_SYSTEM,
    QRV_TRACE_COMM,
    QRV_TRACE_INT_HANDLER_ENTER,
    QRV_TRACE_INT_HANDLER_EXIT,
};

/* TraceEvent() - external events */
#define QRV_TRACE_EMPTYEVENT       (0x00000000)

#define QRV_TRACE_CONTROLTIME      (0x00000001<<0)
#define QRV_TRACE_CONTROLBUFFER    (0x00000001<<1)

#define QRV_TRACE_KERCALLFIRST     (0x00000000)
#define QRV_TRACE_KERCALLLAST      (__KER_BAD)

#define QRV_TRACE_INTFIRST         (0x00000000)
#define QRV_TRACE_INTLAST          (0xffffffff)

#define QRV_TRACE_PROCCREATE       (0x00000001<<0)
#define QRV_TRACE_PROCDESTROY      (0x00000001<<1)
#define QRV_TRACE_PROCCREATE_NAME  (0x00000001<<2)
#define QRV_TRACE_PROCDESTROY_NAME (0x00000001<<3)
#define QRV_TRACE_PROCTHREAD_NAME  (0x00000001<<4)

#define QRV_TRACE_THDEAD           (0x00000001<<STATE_DEAD       )
#define QRV_TRACE_THRUNNING        (0x00000001<<STATE_RUNNING    )
#define QRV_TRACE_THREADY          (0x00000001<<STATE_READY      )
#define QRV_TRACE_THSTOPPED        (0x00000001<<STATE_STOPPED    )
#define QRV_TRACE_THSEND           (0x00000001<<STATE_SEND       )
#define QRV_TRACE_THRECEIVE        (0x00000001<<STATE_RECEIVE    )
#define QRV_TRACE_THREPLY          (0x00000001<<STATE_REPLY      )
#define QRV_TRACE_THSTACK          (0x00000001<<STATE_STACK      )
#define QRV_TRACE_THWAITTHREAD     (0x00000001<<STATE_WAITTHREAD )
#define QRV_TRACE_THWAITPAGE       (0x00000001<<STATE_WAITPAGE   )
#define QRV_TRACE_THSIGSUSPEND     (0x00000001<<STATE_SIGSUSPEND )
#define QRV_TRACE_THSIGWAITINFO    (0x00000001<<STATE_SIGWAITINFO)
#define QRV_TRACE_THNANOSLEEP      (0x00000001<<STATE_NANOSLEEP  )
#define QRV_TRACE_THMUTEX          (0x00000001<<STATE_MUTEX      )
#define QRV_TRACE_THCONDVAR        (0x00000001<<STATE_CONDVAR    )
#define QRV_TRACE_THJOIN           (0x00000001<<STATE_JOIN       )
#define QRV_TRACE_THINTR           (0x00000001<<STATE_INTR       )
#define QRV_TRACE_THSEM            (0x00000001<<STATE_SEM        )
#define QRV_TRACE_THWAITCTX        (0x00000001<<STATE_WAITCTX    )
#define QRV_TRACE_THNET_SEND       (0x00000001<<STATE_NET_SEND   )
#define QRV_TRACE_THNET_REPLY      (0x00000001<<STATE_NET_REPLY  )
#define QRV_TRACE_THCREATE         (0x00000001<<_TRACE_THREAD_CREATE )
#define QRV_TRACE_THDESTROY        (0x00000001<<_TRACE_THREAD_DESTROY)

#define QRV_TRACE_VTHDEAD          (0x00000001<<STATE_DEAD       )
#define QRV_TRACE_VTHRUNNING       (0x00000001<<STATE_RUNNING    )
#define QRV_TRACE_VTHREADY         (0x00000001<<STATE_READY      )
#define QRV_TRACE_VTHSTOPPED       (0x00000001<<STATE_STOPPED    )
#define QRV_TRACE_VTHSEND          (0x00000001<<STATE_SEND       )
#define QRV_TRACE_VTHRECEIVE       (0x00000001<<STATE_RECEIVE    )
#define QRV_TRACE_VTHREPLY         (0x00000001<<STATE_REPLY      )
#define QRV_TRACE_VTHSTACK         (0x00000001<<STATE_STACK      )
#define QRV_TRACE_VTHWAITTHREAD    (0x00000001<<STATE_WAITTHREAD )
#define QRV_TRACE_VTHWAITPAGE      (0x00000001<<STATE_WAITPAGE   )
#define QRV_TRACE_VTHSIGSUSPEND    (0x00000001<<STATE_SIGSUSPEND )
#define QRV_TRACE_VTHSIGWAITINFO   (0x00000001<<STATE_SIGWAITINFO)
#define QRV_TRACE_VTHNANOSLEEP     (0x00000001<<STATE_NANOSLEEP  )
#define QRV_TRACE_VTHMUTEX         (0x00000001<<STATE_MUTEX      )
#define QRV_TRACE_VTHCONDVAR       (0x00000001<<STATE_CONDVAR    )
#define QRV_TRACE_VTHJOIN          (0x00000001<<STATE_JOIN       )
#define QRV_TRACE_VTHINTR          (0x00000001<<STATE_INTR       )
#define QRV_TRACE_VTHSEM           (0x00000001<<STATE_SEM        )
#define QRV_TRACE_VTHWAITCTX       (0x00000001<<STATE_WAITCTX    )
#define QRV_TRACE_VTHNET_SEND      (0x00000001<<STATE_NET_SEND   )
#define QRV_TRACE_VTHNET_REPLY     (0x00000001<<STATE_NET_REPLY  )
#define QRV_TRACE_VTHCREATE        (0x00000001<<_TRACE_THREAD_CREATE )
#define QRV_TRACE_VTHDESTROY       (0x00000001<<_TRACE_THREAD_DESTROY)

#define QRV_TRACE_USERFIRST        (0x00000000)
#define QRV_TRACE_USERLAST         (0x000003ff)

#define QRV_TRACE_SYS_RESERVED     (0x00000001)
#define QRV_TRACE_SYS_PATHMGR      (0x00000002)
#define QRV_TRACE_SYS_APS_NAME		(0x00000003)
#define QRV_TRACE_SYS_APS_BUDGETS  (0x00000004)
#define QRV_TRACE_SYS_APS_BNKR     (0x00000005)    /* when APS scheduler detects bankruptcy */
#define QRV_TRACE_SYS_MMAP      	(0x00000006)
#define QRV_TRACE_SYS_MUNMAP    	(0x00000007)
#define QRV_TRACE_SYS_MAPNAME    	(0x00000008)
#define QRV_TRACE_SYS_ADDRESS      (0x00000009)
#define QRV_TRACE_SYS_FUNC_ENTER   (0x0000000a)
#define QRV_TRACE_SYS_FUNC_EXIT    (0x0000000b)
#define QRV_TRACE_SYS_SLOG    		(0x0000000c)
#define QRV_TRACE_SYS_LAST			QRV_TRACE_SYS_SLOG

#define QRV_TRACE_COMM_SMSG        (0x00000000)
#define QRV_TRACE_COMM_SPULSE      (0x00000001)
#define QRV_TRACE_COMM_RMSG        (0x00000002)
#define QRV_TRACE_COMM_RPULSE      (0x00000003)
#define QRV_TRACE_COMM_SPULSE_EXE  (0x00000004)
#define QRV_TRACE_COMM_SPULSE_DIS  (0x00000005)
#define QRV_TRACE_COMM_SPULSE_DEA  (0x00000006)
#define QRV_TRACE_COMM_SPULSE_UN   (0x00000007)
#define QRV_TRACE_COMM_SPULSE_QUN  (0x00000008)
#define QRV_TRACE_COMM_SIGNAL      (0x00000009)
#define QRV_TRACE_COMM_REPLY       (0x0000000a)
#define QRV_TRACE_COMM_ERROR    	(0x0000000b)
#define QRV_TRACE_COMM_LAST        QRV_TRACE_COMM_ERROR

#define QRV_TRACE_MAX_CLASS		(0x0000001f)
#define QRV_TRACE_MAX_CODES		(0x000003ff)

#define QRV_TRACE_SETEVENT_C(c,cl) (c&=~(0x1f<<10),c|=(cl))
#define QRV_TRACE_GETEVENT_C(c)    ((c)&(0x1f<<10))
#define QRV_TRACE_SETEVENT(c, e)   (c&=~(0x3ff),c|=(e))
#define QRV_TRACE_GETEVENT(c)      ((c)&0x3ff)
#define QRV_TRACE_GETCPU(h)        (((h)&0x3f000000)>>24)

/* Query support flags */
#define QRV_TRACE_NOINSTRSUPP      (0x00000000)
#define QRV_TRACE_SUPPINSTR        (0x00000001<<0)

/* feature index parameters */
enum {
    QRV_TRACE_FIPID,
    QRV_TRACE_FITID,
    QRV_TRACE_FI_NUM
};

/* feature parameter masks */
#define QRV_TRACE_FMEMPTY          (0x00000000)
#define QRV_TRACE_FMPID            (1<<QRV_TRACE_FIPID)
#define QRV_TRACE_FMTID            (1<<QRV_TRACE_FITID)

#define _TRACE_MAX_EVENT_NUM        (0x00000400)

enum _TRACE_THREAD_STATE {      /* Two add. thread-states */
    _TRACE_THREAD_CREATE = STATE_MAX,
    _TRACE_THREAD_DESTROY,
    _TRACE_MAX_TH_STATE_NUM
};

typedef _Uint32t __traceentry;

typedef struct traceevent {
    __traceentry header;        /* CPU, event, format */
    __traceentry data[3];       /* event data         */
} traceevent_t;

/* tracefile header keywords */
#define _TRACE_MAX_HEADER_LEN       (512)
#define _TRACE_HEADER_PREFIX        "TRACE_"
#define _TRACE_HEADER_POSTFIX       "::"

#define _TRACE_HEADER_KEYWORDS() \
	_TRACE_MK_HK(HEADER_BEGIN),  \
	_TRACE_MK_HK(FILE_NAME),     \
	_TRACE_MK_HK(DATE),          \
	_TRACE_MK_HK(VER_MAJOR),     \
	_TRACE_MK_HK(VER_MINOR),     \
	_TRACE_MK_HK(LITTLE_ENDIAN), \
	_TRACE_MK_HK(BIG_ENDIAN),    \
	_TRACE_MK_HK(MIDDLE_ENDIAN), \
	_TRACE_MK_HK(ENCODING),      \
	_TRACE_MK_HK(BOOT_DATE),     \
	_TRACE_MK_HK(CYCLES_PER_SEC),\
	_TRACE_MK_HK(CPU_NUM),       \
	_TRACE_MK_HK(SYSNAME),       \
	_TRACE_MK_HK(NODENAME),      \
	_TRACE_MK_HK(SYS_RELEASE),   \
	_TRACE_MK_HK(SYS_VERSION),   \
	_TRACE_MK_HK(MACHINE),       \
	_TRACE_MK_HK(SYSPAGE_LEN),   \
	_TRACE_MK_HK(HEADER_END)

/* buffer/sequence extraction macros */
#define _TRACE_GET_BUFFNUM(b)       (b>>13)
#define _TRACE_GET_BUFFSEQ(b)       (b&0x000007FF)

#define _TRACE_GET_FLAG(c)          ((c)&0x0fffffff)
#define _TRACE_GET_COUNT(c)         (((c)>>28)&0x7)
#define _TRACE_FLAGS_RING           (0x00010000)
#define _TRACE_FLAGS_WRITING        (0x00020000)
#define _TRACE_FLAGS_WRITTING       _TRACE_FLAGS_WRITING
#define _TRACE_FLAGS_FLUSH          (0x00040000)

#define _TRACE_MAX_KER_CALL_NUM     (128)
#define _TRACE_MAX_INT_NUM          (256)
#define _TRACE_MAX_COMM_NUM         (QRV_TRACE_COMM_LAST+1)
#define _TRACE_MAX_SYSTEM_NUM       (QRV_TRACE_SYS_LAST+1)
#define _TRACE_MAX_USER_NUM       	(QRV_TRACE_USERLAST+1)

/* event data filled by an event handler */
typedef struct {
    __traceentry header;        /* same as traceevent header       */
    _Uint32t *data_array;       /* initialized by the user         */
    _Uint32t el_num;            /* number of elements returned     */
    void *area;                 /* user data                       */
    _Uint32t feature_mask;      /* bits indicate valid features    */
    _Uint32t feature[QRV_TRACE_FI_NUM];    /* feature array - additional data */
} event_data_t;

/* S-simple, C-comb., CC-comb.-cont, B-begin, E-end */
#define _TRACE_STRUCT_S             (0x00000000)
#define _TRACE_STRUCT_CB            (0x00000001<<30)
#define _TRACE_STRUCT_CC            (0x00000002<<30)
#define _TRACE_STRUCT_CE            (0x00000003<<30)
#define _TRACE_GET_STRUCT(c)        ((c)&(0x3<<30))

/* internal cleasses (C-class) */
#define _TRACE_EMPTY_C              (0x00000000<<10)
#define _TRACE_CONTROL_C            (0x00000001<<10)
#define _TRACE_KER_CALL_C           (0x00000002<<10)
#define _TRACE_INT_C                (0x00000003<<10)
#define _TRACE_PR_TH_C              (0x00000004<<10)
#define _TRACE_SYSTEM_C             (0x00000005<<10)
#define _TRACE_CONTAINER_C          _TRACE_SYSTEM_C //Container class never defined
#define _TRACE_USER_C               (0x00000006<<10)
#define _TRACE_COMM_C               (0x00000007<<10)
#define _TRACE_TOT_CLASS_NUM        (8)

/* pseudo-events since we can't use direct int. num */
#define _TRACE_INT_ENTRY            (1)
#define _TRACE_INT_EXIT             (2)
#define _TRACE_INT_HANDLER_ENTRY    (3)
#define _TRACE_INT_HANDLER_EXIT     (4)

#define _TRACE_CONTROL_TIME         (0x00000001)
#define _TRACE_CONTROL_BUFFER       (0x00000002)

/* thread create/destroy */
#define _TRACE_PR_TH_CREATE_T       (_TRACE_THREAD_CREATE)
#define _TRACE_PR_TH_DESTROY_T      (_TRACE_THREAD_DESTROY)
#define _TRACE_PR_TH_CREATE_VT      (_TRACE_PR_TH_CREATE_T+_TRACE_MAX_TH_STATE_NUM)
#define _TRACE_PR_TH_DESTROY_VT     (_TRACE_PR_TH_DESTROY_T+_TRACE_MAX_TH_STATE_NUM)

/* process create/destroy => (event<64) */
#define _TRACE_PR_TH_CREATE_P       (0x00000001<<6)
#define _TRACE_PR_TH_DESTROY_P      (0x00000002<<6)
#define _TRACE_PR_TH_CREATE_P_NAME  (0x00000003<<6)
#define _TRACE_PR_TH_DESTROY_P_NAME (0x00000004<<6)
/* additional thread information */
#define _TRACE_PR_TH_NAME_T         (0x00000005<<6)

/* size of individual trace buffers */
#define _TRACEBUFSIZE               (16*1024)
#define _TRACEBUFEMPTY              (300)
#define _TRACELEMENTS  ((_TRACEBUFSIZE-sizeof(struct traceheader))/sizeof(struct traceevent))

#if defined(__QNXNTO__)
/* just needed for kernel <=> tracelogger interface */

#ifndef _SYS_TIME_H
#include <sys/time.h>
#endif

#ifndef _STDARG_H_INCLUDED
#include <stdarg.h>
#endif

typedef struct tracebuf {
    struct traceheader {
        struct tracebuf *baseaddr;  /* base address of the trace buffer  */
        struct tracebuf *next;      /* pointer to the next trace buffer  */
        _Uint32t flags;             /* event mask, locking states, ...   */
        _Uint32t num_events;        /* number of events in the buffer    */
        _Uint32t seq_buff_num;      /* buffer number in the sequence     */
        _Uint32t ls13_rb_num;       /* 13 pos left-shifted ring buff num */
        struct intrspin spin;       /* spin lock (assume 32-bit length)  */
        traceevent_t volatile *begin_ptr;   /* begin of the traceevent chain  */
        traceevent_t volatile *tail_ptr;    /* end of the traceevent chain    */
        _Uint32t reserved[31];      /* reserved for future expansions    */
    } h;
    struct traceevent data[_TRACELEMENTS];
} tracebuf_t;

__BEGIN_DECLS extern int trace_vnlogf(int __code, int __max, const char *__fmt, va_list __arglist);
extern int trace_logf(int __code, const char *__fmt, ...) __attribute__((format(__printf__, 2, 3)));
extern int trace_nlogf(int __code, int __max, const char *__fmt, ...)
    __attribute__((format(__printf__, 3, 4)));
extern int trace_logi(int __code, unsigned __d1, unsigned __d2);
extern int trace_logbc(int __class, int __event, const void *__data, size_t __nbytes);
extern int trace_logb(int __code, const void *__buf, size_t __nbytes);
extern int trace_func_enter(void *__this_fn, void *__call_site);
extern int trace_func_exit(void *__this_fn, void *__call_site);

static __inline__ int trace_here(void)
{
    void *pc = __builtin_return_address(0);
    return TraceEvent(QRV_TRACE_INSERTSCLASSEVENT,
                      QRV_TRACE_SYSTEM, QRV_TRACE_SYS_ADDRESS, (uintptr_t)pc, 0);
}

__END_DECLS
#endif
#endif
