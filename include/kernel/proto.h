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

#include <arch/proto.h>
#include <kernel/memmgr_hooks.h>
#include <kernel/debug.h>

// Kernel prototypes

// Nanokernel calls
void rdecl block(void);
void rdecl unready(tThread * thp, int newstate);
void rdecl stop_threads(tProcess * prp, unsigned flags, unsigned iflags);
void rdecl cont_threads(tProcess * prp, unsigned flags);
int rdecl stop_one_thread(tProcess * prp, int tid, unsigned flags, unsigned iflags);
int rdecl cont_one_thread(tProcess * prp, int tid, unsigned flags);
int rdecl set_runmask(tThread * thp, unsigned runmask);
void *rdecl object_alloc(tProcess * prp, tSoul * soulp);
void *rdecl object_grow(tSoul * soulp);
void rdecl object_free(tProcess * prp, tSoul * soulp, void *ptr);
void rdecl object_compact(tSoul * soulp);
unsigned rdecl object_register_data(tSoul * soulp, size_t size);
#define             object_to_data(o, c) ((void *)((char *)(o) + (c)))
#define             object_from_data(o, c) ((void *)((char *)(o) - (c)))
void *rdecl vector_lookup(tVector * vec, int id);
void *rdecl vector_lookup2(tVector * vec, int id);
void *rdecl vector_search(tVector * vec, unsigned id, unsigned *found);
int rdecl vector_add(tVector * vec, void *object, unsigned index);
void *rdecl vector_rem(tVector * vec, unsigned index);
int rdecl vector_flag(tVector * vec, unsigned index, int flag);
void rdecl vector_free(tVector * vec);
void *nano_query(int type, unsigned index1, int subtype, unsigned index2, unsigned *next,
                 void *objbuf, int objsize);
tThread *get_active(void);
int rdecl force_ready(tThread * thp, int err);
void rdecl signal_clear_thread(tThread * thp, siginfo_t * sip);
void rdecl signal_ignore(tProcess * prp, int signo);
void rdecl signal_ignore_thread(tThread * thp, int signo);
void rdecl signal_block(tThread * thp, sigset_t * sig_blocked);
void specialret_attr specialret(tThread * thp);
void rdecl deliver_fault(tThread * thp, siginfo_t * info);
void rdecl usr_fault(int code_signo, tThread * act, uintptr_t addr);
void rdecl timer_init(void);
tTimer *rdecl timer_alloc(tProcess *);
void rdecl timer_free(tProcess *, tTimer *);
void rdecl timer_period(void);
void rdecl timer_remaining(tTimer * tip, struct _itimer *left);
int rdecl timer_past(int clockid, int flags, uint64_t * firetime);
void rdecl timer_activate(tTimer * tip);
int rdecl timer_deactivate(tTimer * tip);
void rdecl timer_next(uint64_t * nexttime);
void rdecl timer_expiry(tQtime * qtp);
void rdecl timer_pending(tTimer * tip);
void rdecl thread_init(void);
int rdecl thread_create(tThread * act, tProcess * prp, const struct sigevent *evp,
                        unsigned thread_create_flags);
void rdecl thread_destroy(tThread * thp);
void rdecl thread_destroyall(tThread * thp);
void rdecl thread_cancel(tThread * thp);
uint32_t rdecl keygen(iov_t * msg, int32_t parts, uint32_t key1);
void rdecl get_rcvinfo(tThread * thp, int tid, tConnect * cop, struct _msg_info *rep);
void rdecl connect_detach(tConnect * cop, int prio);
void rdecl connect_coid_disconnect(tConnect * cop, tChannel * chp, int priority);
tVthread *rdecl net_send1(int vtid, struct _vtid_info *vtp);
tConnect *rdecl net_send2(tKerArgs * kap, int vtid, tConnect * cop, tThread * thp);
void rdecl snap_time_wakeup(void);
void rdecl snap_time(uint64_t * tsp, int incl_tod);
int rdecl cred_set(tCredential ** pcrp, struct _cred_info *cip);
void rdecl cred_dirty(tProcess * prp);
tLimits *rdecl limits_getset(uid_t uid, unsigned *newmaxes[]);

// memory object allocator calls
void *malloc(size_t size);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *data, size_t size);
void free(void *data);
void *_smalloc(size_t size);
void *_scalloc(size_t size);
void *_srealloc(void *data, size_t old_size, size_t new_size);
void *_sreallocfunc(void *data, size_t old_size, size_t new_size,
                    size_t (*alloc)(size_t size, void **addr));
void _sfree(void *data, size_t size);
void _kfree(void *data);                      // does a __Ring0() first
void _ksfree(void *data, size_t size);        // does a __Ring0() first
void *_ksmalloc(size_t size);                 // does a __Ring0() first
void *sbrk(int increment);
int purger_register(int (*purge)(size_t), unsigned prio);
int purger_invoke(size_t amount);

void shutdown(unsigned sigcode, const CPU_REGISTERS * reg);
int kprintf(const char *fmt, ...);
int kdprintf(const char *fmt, ...);
int ksprintf(char *buffer, const char *fmt, ...);
int ksnprintf(char *buffer, size_t len, const char *fmt, ...);
int kvsnprintf(char *buf, size_t buflen, const char *fmt, va_list ap);
void dbug_display(const char *buffer, int len);
void scrn_display(const char *buffer, int len);
int scrn_poll_key(void);
void strscrn_display(const char *buffer);
void module_init(unsigned pass);

tProcess *rdecl lookup_pid(pid_t pid);
tConnect *rdecl lookup_connect(int coid);
tConnect *rdecl lookup_rcvid(tKerArgs * kap, int rcvid, tThread ** thpp);
tLimits *rdecl lookup_limits(uid_t uid);
tSync *rdecl sync_create(tProcess * bill_prp, sync_t * sync, unsigned flags);
int rdecl sync_destroy(tProcess * prp, sync_t * sync);
tSync *rdecl sync_lookup(sync_t * sync, unsigned create);
void rdecl sync_wakeup(tSync * syp, int all);

tPulse *rdecl pulse_add(tProcess * prp, tPrilHead * queue, int priority, int code, int value, int id);
tPulse *rdecl pulse_replace(tProcess * prp, tPrilHead * queue, int priority, int code, int value,
                           int id);
int rdecl pulse_deliver(tChannel * chp, int priority, int code, int value, int id,
                        unsigned pulse_flags);
void rdecl pulse_remove(tProcess * prp, tPrilHead * queue, tPulse * pup);

void rdecl remove_unblock(tThread * thp, tConnect * cop, int rcvid);

tSigHandler *get_signal_handler(tProcess * prp, int signo, int create);

int rdecl signal_kill_thread(tProcess * prp, tThread * thp, int signo, int code, int value, pid_t pid,
                             unsigned signal_flags);
int rdecl signal_kill_process(tProcess * prp, int signo, int code, int value, pid_t pid,
                              unsigned signal_flags);
int rdecl signal_kill_group(tThread * killer, pid_t pgrp, int signo, int code, int value, pid_t pid,
                            unsigned signal_flags);

/* Add support for sporatic cleanup */
void rdecl sched_ss_cleanup(tThread * thp);
int rdecl sched_ss_adjust(void);
void rdecl sched_ss_update(tThread * thp, tSchedInfo * ssinfo, tSchedReplenish * ssrepl, int drop);
void rdecl sched_ss_block(tThread * thp, int preempted);
void rdecl sched_ss_queue(tThread * thp);

int rdecl sched_thread(tThread * thp, int policy, struct sched_param *param);

void rdecl timeout_start(tThread * thp);
void rdecl timeout_stop(tThread * thp);

int rdecl sigevent_exe(const struct sigevent *evp, tThread * thp, int verify);
int rdecl sigevent_proc(const struct sigevent *evp);
void intrevent_init(unsigned);
void intrevent_preemption(unsigned);
int intrevent_add_attr intrevent_add(const struct sigevent *evp, tThread * thp, tInterrupt * isr);
int event_add(struct sigevent *evp, tThread * thp);
void intrevent_drain_attr intrevent_drain(void);
void intrevent_flush(void);

int viov_to_piov(tProcess * prp, iov_t * piop, int pparts, iov_t * viop, int vparts, int offset);
void set_intr_mask(int intnum, int set);

int rdecl debug_process(tProcess * prp, debug_process_t * dpp);
int rdecl debug_thread(tProcess * prp, tThread * thp, debug_thread_t * dtp);
int rdecl debug_stop(tProcess * prp);
int rdecl debug_run(tProcess * prp, debug_run_t * drp);
int rdecl debug_break(tProcess * pid, debug_break_t * dbp);
int rdecl debug_break_list(tProcess * pid, debug_breaklist_t * dbp);

void kdebug_init(int (*kdebug_path)(struct kdebug_entry * entry, char *buff, int buffsize));
int kdebug_attach(struct kdebug_entry *entry, int resident);
int kdebug_unlink(struct kdebug_entry *entry);
int kdebug_detach(struct kdebug_entry *entry);
int kdebug_watch_entry(struct kdebug_entry *entry, uintptr_t entry_addr);
unsigned kdebug_enter(tProcess * prp, unsigned sigcode, CPU_REGISTERS * reg);
void kdebug_kdump_private(const struct kdump_private *);

void mdriver_init(void);
void mdriver_check(void);
void mdriver_process_time(void);
int mdriver_intr_attach(int);

void rdecl send_ipi(int cpu, int cmd);
int rdecl get_cpunum(void);
void rdecl smp_flush_tlb(void);

void rdecl crash(const char *file, int line);
struct asinfo_entry;
int walk_asinfo(const char *name, int (*func)(struct asinfo_entry *, char *, void *), void *data);
int (xfer_memprobe) (void *ptr);

#define XSTR(x)	#x
#define STRINGIZE(x) XSTR(x)

#ifdef _lint
#define		crash()	(exit(-1))
#else
#define		crash() (crash)(STRINGIZE(_BASE_FILE_), __LINE__)
#endif

/*
 * STRLCPY(dst, src, len)
 *
 * BSD 'strlcpy()' - google it
 * NOTE however that unlike the BSD version, this macro (currently) does
 * 	not return anything
 *
 * In general ...
 * a more efficient and safer implementation of strncpy() (non debug)
 * - <dst> is guaranteed to be null terminated
 * - copying stops at first '\0' in <src>
 * - debug version will identify truncated strings
 *
*/
#ifndef NDEBUG
#define STR_OVERFLOW(f, line, s, d, l) \
   					 kprintf("%s:%u - strncpy overflow, src truncated to %d bytes\n\tsrc - '%s'\n\tdst  - '%s'\n", \
   					 				(f), (line), (l)-1, (s), (d))
#else
#define STR_OVERFLOW(f, line, s, d, l)
#endif                          /* NDEBUG */

#define STRLCPY(d, s, l) ({ \
		CRASHCHECK((size_t)(l) > 4096); /* what we believe to be a reasonable value */ \
		if(memccpy((d), (s), '\0', (l)) == NULL) { \
			(d)[((l) > 0) ? (l)-1 : (l)] = '\0'; \
			if ( ker_verbose >= 2 ) { \
				STR_OVERFLOW(STRINGIZE(_BASE_FILE_), __LINE__, (s), (d), (l)); \
			} \
		} \
	})

#undef MMF
#define MMF(r, f, p, e)		MMF_PROTO(r, f, p, e)
MM_FUNCS(smm)
//vendor hooks
struct _resmgr_context;
extern void (rdecl * sync_mutex_lock_hook_for_block) (tThread * thp);
extern void (rdecl * clock_handler_hook_for_ts_preemption) (tThread * act, unsigned int reschedl);
extern void (rdecl * sync_destroy_hook) (tProcess * prp, sync_t * sync);
struct kerargs_sync_create;
extern void (rdecl * sync_create_hook) (tProcess * prp);
extern uint64_t(rdecl * clock_handler_hook_enter) (void);
extern void (rdecl * clock_handler_hook_exit) (uint64_t id_hook_context);   /* parm is output of clock_handler_hook_enter */
extern uint64_t(rdecl * intrevent_drain_hook_enter) (void);
extern void (rdecl * intrevent_drain_hook_exit) (uint64_t id_hook_context); /* parm is output of interevent_drain_hook_enter */
extern void (rdecl * timer_expiry_hook_max_timer_fires) (unsigned int nfires);

/* Architecture-dependent prototypes */
int arch_timer_reload(tQtime *);
int arch_timer_load(tQtime *);
