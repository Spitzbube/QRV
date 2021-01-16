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

#ifndef _KERNEL_OBJECTS_H
#define _KERNEL_OBJECTS_H

#ifndef _LARGEFILE64_SOURCE
#define _LARGEFILE64_SOURCE 1
#endif

#include <sys/resource.h>
#include <sys/types.h>
#include <sys/fault.h>
#include <sys/kdebug.h>
#include <sys/debug.h>
#include "kernel/memclass.h"
#include "kernel/mempart.h"
#include "kernel/macros.h"
#include <kernel/posix_types.h>


/******************************************************************************
 * Forward declarations of structure types.
 *****************************************************************************/
typedef struct session_entry tSession;
typedef struct dispatch_entry tDispatch;
typedef struct thread_entry tThread;
typedef struct thread_entry tVthread;   // Same as tThread, but smaller
typedef struct pulse_entry tPulse;
typedef struct syncevent_entry tSyncEvent;
typedef struct sync_entry tSync;
typedef struct interrupt_entry tInterrupt;
typedef struct intrevent_entry tIntrEvent;
typedef struct interrupt_level tIntrLevel;
typedef struct breakpt_entry tBreakpoint;

/* Path manager types */
typedef struct node_entry tNode;
typedef union path_mgr_obj tPathMgrObject;

/* KerArgs union */
typedef union kerargs tKerArgs;

/*
 * This will define the size of a short message. It should
 * be at least 16 bytes as this is aways available in the
 * thread args union.
 */
#ifndef _SHORT_MSG_LEN
#define _SHORT_MSG_LEN			256
#endif
/*
 * This defines the number of incoming send and reply IOV cached by the message
 * pass code. This should be the same size as the SHORT_MSG_LEN buffer.
 */

#ifndef _NUM_CACHED_SEND_IOV
#define _NUM_CACHED_SEND_IOV	(_SHORT_MSG_LEN/(sizeof(iov_t)))
#endif

#ifndef _NUM_CACHED_REPLY_IOV
#define _NUM_CACHED_REPLY_IOV	(_SHORT_MSG_LEN/(sizeof(iov_t)))
#endif

/*
 * kerproc_lock_t
 * this type is used to provide a synchronization mechansim between procnto
 * and the kernel
*/
typedef struct kerproc_lock_s {
    pthread_mutex_t mutex;
    intrspin_t spin;
    // FIX ME - experimental. If keeping, combine into a single int
    int rd_cnt;
    int wr_cnt;
} kerproc_lock_t;

typedef struct proc_create_attr_s {
    part_list_t *mpart_list;    // memory partition list
    part_list_t *spart_list;    // scheduler partition list
} proc_create_attr_t;

/*
 * Types (used by tPulse, tThread, tVthread, tConnection, tChannel)
 */
enum {
    TYPE_THREAD,
    TYPE_PULSE,
    TYPE_SIGNAL,
    TYPE_VTHREAD,
    TYPE_CONNECTION,
    TYPE_CHANNEL,
    TYPE_VPULSE,
    TYPE_SYNCEVENT,
    TYPE_TYPE_MASK = 0x0f,
    TYPE_FLAG_FIRST = 0x10
};

#define TYPE_MASK(t)	((t) & TYPE_TYPE_MASK)

typedef struct sighandler_entry {
    void (*handler)(int);
    unsigned flags;
    sigset_t sig_blocked;
} tSigHandler;

#define HANDLERS_PER_SIGTABLE	4
typedef struct sigtable_entry {
    struct sigtable_entry *next;
    uint32_t sig_base;
    tSigHandler handlers[HANDLERS_PER_SIGTABLE];
} tSigTable;


typedef struct vector_entry {
    uint16_t nentries;
    uint16_t nfree;
    void *free;
    void **vector;
} tVector;

/*
 * A list node and list header for use with the LINK3_* macros.
 */
typedef struct link3_node {
    struct link3_node *next, **prev;
} LINK3_NODE;

typedef struct link3_hdr {
    LINK3_NODE *head, *tail;
} LINK3_HDR;

/*
 * a list node and list header for use with the LINK4_* macros.
 */
typedef LINK3_NODE LINK4_NODE;

typedef struct link4_hdr {
    LINK4_NODE *head, *tail;
    int count;
} LINK4_HDR;


/*
 * Macro to define the fields needed for the pril routines - done this
 * way so that all the structures that use them always have the same layout
 * at the begining.
 */
#define PRIL_ENTRY_FIELDS \
        union { \
            struct pril_entry *pril; \
            tThread    *thread;       \
            tPulse     *pulse;        \
            tSyncEvent *sev;          \
        } next; \
        union { \
            struct pril_entry *prio_tail; \
            struct pril_entry **pril;     \
            tThread    **thread; \
            tPulse     **pulse;  \
            tSyncEvent **sev;    \
        } prev; \
        uint8_t type; \
        uint8_t priority;

typedef struct pril_entry {
    PRIL_ENTRY_FIELDS
} tPril;

struct pril_update {
    struct pril_update *next;
    struct pril_update *prev;
    tPril *pril;
};

typedef struct {
    tPril *data;
} tPrilHead;


typedef struct credential_entry {
    struct credential_entry *next;
    uint32_t links;
    struct _cred_info info;
} tCredential;

struct mempart_node_s;
typedef struct channel_entry tChannel;
typedef struct mm_aspace tAddress;
typedef struct debug_entry tDebug;
typedef struct process_entry tProcess;
typedef struct limits_entry tLimits;
typedef struct timer_entry tTimer;

typedef struct process_entry {
    tProcess *next;
    pid_t pid;
    uint32_t flags;
    tAddress *memory;
    uintptr_t boundry_addr;
    tVector chancons;            // Channels and non-fd connect vector.
    tVector fdcons;              // Fd connection vector.
    tDebug *debugger;
    struct _process_local_storage *pls;
    volatile uint64_t running_time;
    volatile uint64_t system_time;
    struct proc_mux_lock *lock;
    struct process_entry *parent;
    tVector threads;
    tVector timers;
    pid_t pgrp;
    tCredential *cred;
    tLimits *limits;
    tTimer *alarm;
    sigset_t sig_ignore;
    sigset_t sig_queue;
    tPrilHead sig_pending;
    tSigTable *sig_table;
    void (*sigstub)(void);
    void (*canstub)(void);
    tProcess *child;
    tProcess *sibling;
    tThread *join_queue;
    tSession *session;
    tDispatch *default_dpp;
    uint32_t umask;
    uint32_t num_active_threads;
    uint32_t num_processes;     // # of processes created
    int32_t sigtid_cache;
    tChannel *death_chp;
    tNode *root;
    tNode *cwd;
    siginfo_t siginfo;
    struct wait_entry *wap;
    char *debug_name;
    uintptr_t initial_esp;
    uintptr_t base_addr;
    struct loader_context *lcp;
    struct vfork_info *vfork_info;
    struct procfs_ocb *ocb_list;
    struct kdebug_entry kdebug;
    struct procfs_waiting *debug_waiting;
    tThread *valid_thp;
    struct conf_entry *conf_table;
    struct _rsrc_list_array *rsrc_list;
    tProcess *guardian;
    tVector *events;
    uint64_t start_time;
    uint64_t kids_running_time;
    uint64_t kids_system_time;
    uint64_t max_cpu_time;      // in nano-seconds
    uint32_t seq;
    ulong_t rlimit_vals_soft[RLIM_NLIMITS];
    ulong_t rlimit_vals_hard[RLIM_NLIMITS];
    uint16_t nfds;
    uint8_t terming_priority;
    uint8_t process_priority;
    int querying;
    unsigned pending_interrupts;
    /*
     * The following fields pertain to the memory partitioning module.
     *      'mempart_list' is a list of the associated partitions
     *      'mempartlist_lock' - protects the 'mempart_list'
     * Even if the memory partitioning module is not installed, there will be
     * one proxy 'sys_mempart' entry. No accounting is done as this is not really
     * a partition. When the memory partitioning module is installed, there may
     * be several associated partitions
     */
    kerproc_lock_t mpartlist_lock;
    tVector mpart_list;
    kerproc_lock_t spartlist_lock;
    void *spart_list;
} tProcess;

/*
 * Channel descriptor
 */
typedef struct channel_entry {
    tChannel *next;
    int32_t chid;
    uint32_t flags;             // _NTO_CHF_*
    uint8_t type;
    uint8_t zero[3];
    tProcess *process;
    tPrilHead send_queue;
    tThread *receive_queue;
    tThread *reply_queue;
    mode_t mode;                /* permissions */
} tChannel;

struct channel_async_entry {
    struct channel_entry ch;    /* basic channel_entry */
    struct sigevent event;      /* the event to be sent for notification */
    tProcess *ev_prp;            /* the process who registers the event */
};

struct gblmsg_entry {
    struct gblmsg_entry *next;
    unsigned priority;
    size_t size;
};

typedef struct connect_entry tConnect;
struct channel_gbl_entry {
    struct channel_entry ch;    /* basic channel_entry */
    struct sigevent event;      /* the event to be sent for notification */
    tProcess *ev_prp;            /* the process who registers the event */
    int ev_coid;                /* handle to identify the owner of the event */
    size_t buffer_size;         /* size of kernel buffer */
    unsigned max_num_buffer;    /* maximum number of buffer allowed */
    unsigned num_curr_msg;      /* how many msgs in the channel send queue */
    struct _cred_info cred;     /* credential */
    void *free;                 /* free buffer list */
    struct gblmsg_entry *tail;  /* points to the tail of the queue */
    tConnect *cons;              /* connection list for cleanup when channel is destroyed */
};

typedef struct connect_entry {
    tConnect *next;
    uint16_t scoid;
    int16_t infoscoid;
    uint8_t type;
    uint8_t zero;
    uint16_t flags;             // COF_*
    tProcess *process;
    tChannel *channel;
    uint32_t links;
    union {
        struct {
            uint32_t nd;
            pid_t pid;
            uint32_t chid;
            uint32_t seq;
            tConnect *cop;
            tConnect *next;
        } lcl;
        struct {
            tCredential *cred;
            uint32_t nd;
            pid_t pid;
            pid_t sid;
            uint32_t flags;     // _NTO_CI_*
            uint32_t coid;
        } net;
    } un;
    tThread *restart;            /* restart pointer, used by async messaging */
    struct _asyncmsg_connection_descriptor *cd; /* for async messaging */
    uint32_t sendq_size;
} tConnect;


struct net_entry {
    tProcess *prp;
    tChannel *chp;
};


typedef struct pulse_entry {
    PRIL_ENTRY_FIELDS           // priority is a signal number for TYPE_SIGNAL
    uint8_t spare;
    int8_t code;
    uint32_t value;
    int32_t id;                 // scoid if TYPE_PULSE or src pid if TYPE_SIGNAL
    unsigned count;
} tPulse;

/* Entries for the sporadic scheduling policy */

// Single replenishment object per schedinfo, used in a list
typedef struct _ss_replenish {
    struct _ss_replenish *next; // Next item to replenish
    tThread *thp;               // Thread to replenish
    uint64_t amount;            // Amount to replenish by (nsec)
    uint64_t repl_time;         // When to replenish this item (nsec)
} tSchedReplenish;

/* Incorporated into the schedinfo below
//This information is shared between threads with the same policy
struct _ss_attr {
	struct _ss_attr	*next;
	uint8_t			low_priority;		//Low priority to drop to when empty
	uint8_t			refcount;			//Number of people sharing this attribute
	uint16_t		max_repl;			//Maximum numer of replenishments
	uint64_t		repl_period;		//Period of the replenisment (nsec)
	uint64_t		init_budget;		//Initial budget for the thread (nsec)
};
*/

// This information must be maintained per thread
typedef struct _ss_schedinfo {
    uint8_t low_priority;
    uint8_t org_priority;       // 0 if not dropped, pre-drop priority otherwise
    uint16_t reserved;
    uint16_t max_repl;          // Maximum number of replenishments
    uint16_t repl_count;        // Number of replenishments performed
    uint64_t repl_period;       // Period of the replenishments (nsec)
    uint64_t init_budget;       // Initial budget for the thread (nsec)
    uint64_t curr_budget;       // Current budget for the thread (nsec)
    uint64_t activation_time;   // When this thread was "activated"
    uint64_t consumed;          // Amount consumed on this run
    struct _ss_replenish replenishment;
} tSchedInfo;

/* End entries for the sporadic scheduling algorithm */

typedef uint8_t int_fl_t;       /* for typecasting in ker_message.c */

typedef struct thread_entry {           // Also used for vthread_entry
    PRIL_ENTRY_FIELDS uint8_t real_priority;
    uint8_t policy;
    uint8_t state;
    uint32_t reserved_word;
    uint32_t runcpu;
    int_fl_t internal_flags;
    uint64_t timestamp_last_block;  /* set to copy of snap_time() anytime this thread blocks.
                                     * not valid if state is STATE_READY or STATE_RUNNING */
    tProcess *aspace_prp;
    volatile uint32_t async_flags;
    tDispatch *dpp;
    uint32_t timeout_flags;
    uint32_t flags;
    uint32_t sched_flags;       /* for aps scheduling */
    int32_t syscall;
    tProcess *process;
    int32_t tid;
    tDispatch *orig_dpp;         /* after being a guest of another aps partition, it's returned here */
    union {
        struct _ss_schedinfo *ss_info;
        uint32_t rr_ticks;
    } schedinfo;
    union {
        struct {                // type = tThread
            struct _thread_local_storage *tls;
            void *stackaddr;
            size_t stacksize;
        } lcl;
        struct {                // type = VTHREAD
            uint32_t srcnd;     // remote view of our node (Overlays thread_local_storage pointer)
            void *reserved;
            int32_t vtid;       // virtual thread id (index in thread_vector)
        } net;
    } un;
    tThread *client;             /* the client that the server thread works on behalf */
    void *blocked_on;
    tThread *restart;
    // The following is used to hold arguments when a thread blocks to make
    // them easy to access in another threads context. Only a very small
    // number of arguments need to be saved.
    union {
        struct {                // Used by send/read/write for general messages
            iov_t *rmsg;          // Must be 1st arg
            int32_t rparts;     // Must be 2nd arg
            uint32_t coid;      // Must be 3rd arg
            uint32_t msglen;    // Must be 4th arg
            uint32_t dstmsglen; // Must be 5th arg
            tThread *server;     /* the thread in server to serve this msg. Must be 6th arg */
            uint32_t srcmsglen;
            iov_t *smsg;
            uint32_t sparts;
            tThread *dthp;       // Dest thread for message restarts
            iov_t siov[_NUM_CACHED_SEND_IOV];
            iov_t riov[_NUM_CACHED_REPLY_IOV];
        } ms;

        struct {                // Used by send for short messages
            iov_t *rmsg;          // Must be 1st arg
            int32_t rparts;     // Must be 2nd arg
            uint32_t coid;      // Must be 3rd arg
            uint32_t msglen;    // Must be 4th arg
            uint32_t dstmsglen; // Must be 5th arg
            tThread *server;     /* the thread in server to serve this msg. Must be 6th arg */
            void *fill[4];
            uint8_t buff[_SHORT_MSG_LEN];
            iov_t riov[_NUM_CACHED_REPLY_IOV];
        } msbuff;

        struct {                // Used by nano_specret for get rcvinfo && short messages
            iov_t *rmsg;          // Must be 1st arg
            int32_t rparts;     // Must be 2nd arg
            struct _msg_info *info;
            tThread *thp;
            tConnect *cop;
            uint32_t value;
            int32_t id;
            int8_t code;
        } ri;

#define _NTO_NOIOV				1UL << (8*sizeof(uint32_t)-1)   // Must agree with sparts/rparts
#if 0
        struct {                // Used by net (must align with ms)
            iov_t *rmsg;        // Must be 1st arg
            int32_t rparts;     // Must be 2nd arg
            uint32_t vtid;
            uint32_t msglen;    // Must be 4th arg
            uint32_t dstmsglen; // Must be 5th arg
            uint32_t srcmsglen; // Must match ms
            iov_t *smsg;
            uint32_t sparts;
            uint32_t offset;
        } netms;
#endif
        struct {                // Used by ker_signal_suspend.
            sigset_t sig_blocked;
        } ss;
        struct {                // Used by ker_signal_wait.
            sigset_t sig_wait;
            siginfo_t *sig_info;
            int32_t value;
            pid_t pid;
            int8_t signo;
            int8_t code;
        } sw;
        struct {                // Used by ker_timer_timeout (nanosleep only)
            struct _itimer left;
            uint64_t *timeptr;
            uint32_t spare;
        } to;
        struct {                // Used by ker_thread_join
            void **statusptr;
            void *status;
        } jo;
        struct {                // Used by to aquire a mutex (*_condvar_wait, *_mutex_lock)
            sync_t *mutex;
            uint32_t saved_timeout_flags;
            uint32_t owner;     /* owner of *mutex */
            tSync *next;         /* next mutex in the thread mutex hold list */
            tSync **prev;        /* owner, next and prev only meaningful when the thread is the first one in a mutex waiting list */
            uint8_t ceiling;    /* for change of mutex prio ceiling */
            unsigned incr;      /* count increment */
        } mu;
        struct {                // Used by async_flags processing in an SMP machine
            uint32_t save_ip;
            uint32_t save_type;
            uint32_t code;
            uint32_t fault_type;
            uint32_t fault_addr;
        } async;
        struct {                // Used to hold stuff during thread creation
            void *arg;
            const struct _thread_attr *attr;
            void (*exitfunc)(void *status);
            const struct _thread_attr *real_attr;
            int not_sigev_thread;
        } wa;

    } args;
    sigset_t sig_blocked;
    tPrilHead sig_pending;
    uint32_t runmask;
    uint32_t default_runmask;
    char *name;
    int32_t key;
    int32_t last_chid;
    void *status;
#define SIZEOF_VTHREAD		offsetof(struct thread_entry, timeout)
// Items below are not needed for type=VTHREAD
    tTimer *timeout;
    tThread *join;
    tSync *mutex_holdlist;       /* list of holding mutexes whose waiting queue is not empty */
    uint64_t start_time;
    FPU_REGISTERS *fpudata;
    volatile unsigned ticker_using;
    volatile uint64_t running_time;
    struct cpu_thread_entry cpu;    // Must be just before 'reg' field.
    CPU_REGISTERS reg;
} tThread;

enum {
    SYNCEVENT_SUBTYPE_EVENT,
    SYNCEVENT_SUBTYPE_PRIORITYCEILING,
    SYNCEVENT_SUBTYPE_CLOCKID
};

typedef struct syncevent_entry {
    PRIL_ENTRY_FIELDS uint8_t subtype;
    uint8_t reserved;
    union {
        int clockid;
        struct {
            tProcess *process;
            uint32_t tid;
            struct sigevent event;
        } ev;
    } un;
} tSyncEvent;

typedef struct sync_entry {
    tSync *next;
    tPathMgrObject *obj;
    uint32_t addr;
    tPrilHead waiting;
} tSync;


typedef struct timer_entry {
    struct timer_link {
        tTimer *next;
        tTimer *prev;
    } link;
    tTimer *pending;
    struct timer_queue *queue;
    tThread *thread;
    uint32_t overruns;
    int16_t unused;
    uint8_t clockid;
    uint8_t flags;
    struct sigevent event;
    struct _itimer itime;
} tTimer;

/*
 * WARNING: it is very important that this structure be kept a power of 2
 *          for performance reasons. You have to change the definition
 *          of LOG2_SIZEOF_INTRLEVEL if this structure changes.
 */
struct interrupt_level {
    struct interrupt_entry *queue;
    struct intrinfo_entry *info;
    signed short cascade_level;
    unsigned short config;
    unsigned short level_base;
    unsigned short mask_count;
#ifndef CONFIG_32BIT
    uint64_t reserved;
    #define LOG2_SIZEOF_INTRLEVEL 5
#else
    #define LOG2_SIZEOF_INTRLEVEL 4
#endif
};

struct interrupt_entry {
    tInterrupt *next;
    tThread *thread;
    const struct sigevent *(*handler) (void *area, int id);
    void *area;
    unsigned flags;
    unsigned level;
    unsigned mask_count;
    int id;
    struct cpu_intrsave cpu;
};

struct interrupt_query_entry {
    struct interrupt_entry info;
    pid_t pid;
    int tid;
    unsigned vector;
    struct sigevent event;
};


typedef struct dispatch_entry {
    tDispatch *next;
    tDispatch **prev;
    int id;                     // Dispatch grou id
    unsigned sindex;            // sort index
    unsigned __pad;             // Align ready array on 8 bytes
    void *bumper;               // Must be zero to stop smp_resched()
    LINK3_HDR ready[NUM_PRI];
#if NUM_PRI <= 8
    uint8_t lo;
#elif NUM_PRI <= 8 * 8
    uint8_t hi;
    uint8_t lo[(NUM_PRI + 7) / 8];
#elif NUM_PRI <= 8 * 8 * 8
    uint8_t hi;
    uint8_t mid[(NUM_PRI + (8 * 8 - 1)) / (8 * 8)];
    uint8_t lo[(NUM_PRI + (8 * 8 - 1)) / (8 * 8)][8];
#else
#error NUM_PRI too high
#endif
} tDispatch;


typedef struct session_entry {
    uint32_t links;
    pid_t leader;
    pid_t pgrp;
    int fd;
    unsigned reserved[10];
} tSession;


typedef struct soul_entry {
    void *next;
    int32_t type;               // Type of soul
    uint32_t total;             // Total allocated (free or in use).
    uint32_t used;              // Number in use.
    uint32_t size;              // Size of object in the list.
    uint32_t newmin;            // Current min we need.
    uint32_t min;               // Lowest min allowed.
    uint32_t highwater;
    uint16_t counter;
    uint8_t align;              // Alignement requirement on soul
    uint8_t flags;              // Soul flags
} tSoul;

typedef struct sigstack_entry {
    struct _sighandler_info info;
    sigset_t sig_blocked;
    sync_t *mutex;
    unsigned old_flags;
    uint64_t timeout_time;
    unsigned timeout_flags;
    unsigned mutex_timeout_flags;
    struct sigevent timeout_event;
    unsigned mutex_acquire_incr;
} tSigStack;


typedef struct intrevent_entry {
    struct intrevent_entry *next;
    tThread *thread;
    struct sigevent event;
} tIntrEvent;


typedef struct hash_entry {
    uint32_t mask;
    void **table;
} tHash;

typedef struct limits_entry {
    struct limits_entry *next;
    uint32_t links;
    uint32_t uid;
    uint32_t max[LIMITS_NUM];
    uint32_t cur[LIMITS_NUM];
} tLimits;

struct fault_handlers {
    void (*fault)(tThread * thp, CPU_REGISTERS * regs, unsigned flags);
    void (*restart)(tThread * thp, CPU_REGISTERS * regs);
};

typedef struct breakpt_entry {
    tBreakpoint *next;
    debug_break_t brk;
    unsigned planted;
#ifdef CPU_DEBUG_BRKPT
    struct cpu_debug_brkpt {CPU_DEBUG_BRKPT} cpu;
#endif
} tBreakpoint;

typedef struct debug_entry {
    tProcess *process;
    unsigned flags;
    int what;
    int why;
    sigset_t signals;
    fltset_t faults;
    int tid;                    // current tid
    tBreakpoint *brk;
    tBreakpoint *skip_brk;          // Skip this breakpoint if not null
#ifdef CPU_DEBUG
    struct cpu_debug {CPU_DEBUG} cpu;
#endif
} tDebug;

struct fault_info {
    tProcess *prp;
    uintptr_t vaddr;
    unsigned sigcode;
    struct cpu_fault_info cpu;
};

#endif
