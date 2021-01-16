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
 * Prototypes that are private to the kernel itself.
 */

int kdecl ker_bad(tThread * act, struct kerargs_null *kap);
int kdecl ker_nop(tThread * act, struct kerargs_null *kap);
int kdecl ker_sys_cpupage_get(tThread * act, struct kerargs_sys_cpupage_get *kap);
int kdecl ker_sys_cpupage_set(tThread * act, struct kerargs_sys_cpupage_set *kap);
int kdecl ker_channel_create(tThread * act, struct kerargs_channel_create *kap);
int kdecl ker_channel_destroy(tThread * act, struct kerargs_channel_destroy *kap);
int kdecl ker_channel_connect_attrs(tThread * act, struct kerargs_channel_connect_attr *kap);

int kdecl ker_connect_attach(tThread * act, struct kerargs_connect_attach *kap);
int kdecl ker_connect_detach(tThread * act, struct kerargs_connect_detach *kap);
int kdecl ker_connect_client_info(tThread * act, struct kerargs_connect_client_info *kap);
int kdecl ker_connect_server_info(tThread * act, struct kerargs_connect_server_info *kap);
int kdecl ker_connect_flags(tThread * act, struct kerargs_connect_flags *kap);

int kdecl ker_msg_sendv(tThread * act, struct kerargs_msg_sendv *kap);
int kdecl ker_msg_receivev(tThread * act, struct kerargs_msg_receivev *kap);
int kdecl ker_msg_replyv(tThread * act, struct kerargs_msg_replyv *kap);
int kdecl ker_msg_sendpulse(tThread * act, struct kerargs_msg_sendpulse *kap);
int kdecl ker_msg_error(tThread * act, struct kerargs_msg_error *kap);
int kdecl ker_msg_readv(tThread * act, struct kerargs_msg_readv *kap);
int kdecl ker_msg_readwritev(tThread * act, struct kerargs_msg_readwritev *kap);
int kdecl ker_msg_readiov(tThread * act, struct kerargs_msg_readiov *kap);
int kdecl ker_msg_writev(tThread * act, struct kerargs_msg_writev *kap);
int kdecl ker_msg_info(tThread * act, struct kerargs_msg_info *kap);
int kdecl ker_msg_deliver_event(tThread * act, struct kerargs_msg_deliver_event *kap);
int kdecl ker_msg_verify_event(tThread * act, struct kerargs_msg_verify_event *kap);
int kdecl ker_msg_keydata(tThread * act, struct kerargs_msg_keydata *kap);
int kdecl ker_msg_current(tThread * act, struct kerargs_msg_current *kap);

int do_ker_signal_kill(tThread * act, struct kerargs_signal_kill *kap);
int kdecl ker_signal_kill(tThread * act, struct kerargs_signal_kill *kap);
int kdecl ker_signal_return(tThread * act, struct kerargs_signal_return *kap);
int kdecl ker_signal_action(tThread * act, struct kerargs_signal_action *kap);
int kdecl ker_signal_procmask(tThread * act, struct kerargs_signal_procmask *kap);
int kdecl ker_signal_suspend(tThread * act, struct kerargs_signal_suspend *kap);
int kdecl ker_signal_waitinfo(tThread * act, struct kerargs_signal_wait *kap);
int kdecl ker_signal_fault(tThread * act, struct kerargs_signal_fault *kap);

int kdecl ker_thread_create(tThread * act, struct kerargs_thread_create *kap);
int kdecl ker_thread_destroy(tThread * act, struct kerargs_thread_destroy *kap);
int kdecl ker_thread_destroyall(tThread * act, struct kerargs_null *kap);
int kdecl ker_thread_detach(tThread * act, struct kerargs_thread_detach *kap);
int kdecl ker_thread_join(tThread * act, struct kerargs_thread_join *kap);
int kdecl ker_thread_cancel(tThread * act, struct kerargs_thread_cancel *kap);
int kdecl ker_thread_ctl(tThread * act, struct kerargs_thread_ctl *kap);
int kerop_thread_ctl(tThread * act, tThread * op, struct kerargs_thread_ctl *kap);

int kdecl ker_interrupt_attach(tThread * act, struct kerargs_interrupt_attach *kap);
int kdecl ker_interrupt_detach_func(tThread * act, struct kerargs_interrupt_detach_func *kap);
int kdecl ker_interrupt_detach(tThread * act, struct kerargs_interrupt_detach *kap);
int kdecl ker_interrupt_wait(tThread * act, struct kerargs_interrupt_wait *kap);
int kdecl ker_interrupt_mask(tThread * act, struct kerargs_interrupt_mask *kap);
int kdecl ker_interrupt_unmask(tThread * act, struct kerargs_interrupt_unmask *kap);

int kdecl ker_sched_get(tThread * act, struct kerargs_sched_get *kap);
int kdecl ker_sched_set(tThread * act, struct kerargs_sched_set *kap);
int kdecl ker_sched_yield(tThread * act, struct kerargs_null *kap);
int kdecl ker_sched_info(tThread * act, struct kerargs_sched_info *kap);

int kdecl ker_clock_time(tThread * act, struct kerargs_clock_time *kap);
int kdecl ker_clock_adjust(tThread * act, struct kerargs_clock_adjust *kap);
int kdecl ker_clock_period(tThread * act, struct kerargs_clock_period *kap);
int kdecl ker_clock_id(tThread * act, struct kerargs_clock_id *kap);

int kdecl ker_timer_create(tThread * act, struct kerargs_timer_create *kap);
int kdecl ker_timer_destroy(tThread * act, struct kerargs_timer_destroy *kap);
int kdecl ker_timer_settime(tThread * act, struct kerargs_timer_settime *kap);
int kdecl ker_timer_info(tThread * act, struct kerargs_timer_info *kap);
int kdecl ker_timer_alarm(tThread * act, struct kerargs_timer_alarm *kap);
int kdecl ker_timer_timeout(tThread * act, struct kerargs_timer_timeout *kap);

int kdecl ker_sync_create(tThread * act, struct kerargs_sync_create *kap);
int kdecl ker_sync_destroy(tThread * act, struct kerargs_sync_destroy *kap);
int kdecl ker_sync_mutex_lock(tThread * act, struct kerargs_sync_mutex_lock *kap);
int kdecl ker_sync_mutex_unlock(tThread * act, struct kerargs_sync_mutex_unlock *kap);
int kdecl ker_sync_mutex_revive(tThread * act, struct kerargs_sync_mutex_revive *kap);
int kdecl ker_sync_ctl(tThread * act, struct kerargs_sync_ctl *kap);
int kdecl ker_sync_condvar_wait(tThread * act, struct kerargs_sync_condvar_wait *kap);
int kdecl ker_sync_condvar_signal(tThread * act, struct kerargs_sync_condvar_signal *kap);
int kdecl ker_sync_sem_wait(tThread * act, struct kerargs_sync_sem_wait *kap);
int kdecl ker_sync_sem_post(tThread * act, struct kerargs_sync_sem_post *kap);

int kdecl ker_net_cred(tThread * act, struct kerargs_net_cred *kap);
int kdecl ker_net_vtid(tThread * act, struct kerargs_net_vtid *kap);
int kdecl ker_net_unblock(tThread * act, struct kerargs_net_unblock *kap);
int kdecl ker_net_infoscoid(tThread * act, struct kerargs_net_infoscoid *kap);
int kdecl ker_net_signal_kill(tThread * act, struct kerargs_net_signal_kill *kap);

int kdecl ker_mt_ctl(tThread * act, struct kerargs_mt_ctl *kap);

int kdecl ker_trace_event(tThread * act, struct kerargs_trace_event *kap);

int kdecl ker_ring0(tThread * act, struct kerargs_ring0 *kap);

void rdecl kererr(tThread * thp, int err);
void rdecl kerunerr(tThread * thp);
int rdecl kerisroot(tThread * thp);
int rdecl kerisusr(tThread * thp, tProcess * dst);
int rdecl keriskill(tThread * thp, tProcess * dst, int signo);
int rdecl kerschedok(tThread * thp, int policy, const struct sched_param *param);
int kercall_attach(unsigned callnum, int kdecl(*func) ());
void ker_start(void);
void sync_mutex_lock(tThread * act, sync_t * sync, int flags);
void sync_mutex_unlock(tThread * act, sync_t * sync, unsigned incr);
void mutex_holdlist_add(tThread *, SYNC *);
void mutex_holdlist_rem(SYNC *);
int mutex_set_prioceiling(SYNC * syp, unsigned ceiling, unsigned *ceiling_old);
void rdecl thread_specret(tThread * thp);
void rdecl signal_specret(tThread * thp);

void heap_init(size_t);
int crit_sfree(void *p, size_t size);

const struct sigevent *clock_handler(void *, int id);
void clock_ticker(void);
void fpu_init(void);
struct sigevent *fpu_exception();
struct sigevent *fpu_switch();
int rdecl begin_fp_emulation(tThread * act);
uintptr_t rdecl fpu_emulation_prep(CPU_REGISTERS *, tThread * act, int size);

void init_cpu(void);
void init_traps(void);
void init_objects(void);
void init_memmgr(void);
void init_smp(void);
DISPATCH *init_scheduler_default();

void rdecl clock_resolution(unsigned long nsec);
void clock_start(unsigned long nsec);

void idle(void);

void _smpstart(void);

void rdecl interrupt_init(void);
int rdecl interrupt_attach(int intr, const struct sigevent *(*handler) (void *area, int id),
                           void *area, int flags);
void rdecl interrupt_detach(int intr, const struct sigevent *(*handler) (void *area, int id));
void rdecl interrupt_detach_entry(tProcess * prp, int index);
int rdecl interrupt_mask(int intr, INTERRUPT * itp);
int rdecl interrupt_unmask(int intr, INTERRUPT * itp);
int rdecl interrupt_mask_vector(unsigned vector, int id);
int rdecl interrupt_unmask_vector(unsigned vector, int id);
int rdecl get_interrupt_level(tThread * act, unsigned vector);

unsigned (xferiov_pos) (CPU_REGISTERS * regs);
int (xferiov) (tThread * sthp, IOV * dst, IOV * src, int dparts, int sparts, int doff, int soff);

int (xfermsg) (tThread * dthp, tThread * sthp, int doff, int soff);
int (xferpulse) (tThread * dthp, IOV * dst, int parts, uint32_t code, uint32_t value, int32_t scoid);
int (xferlen) (tThread * thp, IOV * iov, int parts);
int (xfer_memcpy) (void *dst, const void *src, size_t len);
int (xfer_cpy_diov) (tThread * thpd, IOV * dst, uint8_t * saddr, int dparts, unsigned slen);
int (xfer_memchk) (uintptr_t bound, const IOV * iov, size_t iov_len);
void xfer_restart(tThread * thp, CPU_REGISTERS * regs);
void xfer_async_restart(tThread * thp, CPU_REGISTERS * regs);

void __ker_exit(void);
int __pagefault_handler(int faultcode, void *faultaddr, tThread * thp);
struct sigevent *reboot_handler();

void kernel_main(int argc, char *argv[], char *environ[]);

int rdecl cpu_debug_sstep(DEBUG * dep, tThread * thp);
int rdecl cpu_debug_brkpt(DEBUG * dep, BREAKPT * bpp);
void rdecl cpu_debug_attach_brkpts(DEBUG * dep);
void rdecl cpu_debug_detach_brkpts(DEBUG * dep);
int rdecl cpu_debug_fault(DEBUG * dep, tThread * thp, siginfo_t * info, unsigned *pflags);
int rdecl cpu_debug_get_altregs(tThread * thp, debug_altreg_t * regs);
int rdecl cpu_debug_set_altregs(tThread * thp, debug_altreg_t * regs);
int rdecl cpu_debug_set_perfregs(tThread * thp, debug_perfreg_t * regs);
int rdecl cpu_debug_get_perfregs(tThread * thp, debug_perfreg_t * regs);

void halt(void);

int rdecl within_syspage(uintptr_t vaddr, unsigned size);

int rdecl synchash_add(tPathMgrObject * obp, unsigned addr, SYNC * syp);
SYNC *rdecl synchash_lookup(tPathMgrObject * obp, unsigned addr);
void rdecl synchash_rem(unsigned addr, tPathMgrObject * obp, unsigned addr1, unsigned addr2, tProcess * prp,
                        void *vaddr);

uint32_t exe_pt_event_h(ehandler_data_t *, uint32_t, pid_t, int, uint32_t, uint32_t);
uint32_t exe_event_h(ehandler_data_t *, uint32_t, uint32_t, uint32_t);
uint32_t exe_pt_event_h_buff(ehandler_data_t *, uint32_t, pid_t, int, void *, uint32_t);
uint32_t exe_event_h_buff(int, ehandler_data_t *, uint32_t, void *, uint32_t);
int trace_event(uint32_t *);
void add_ktrace_int_handler_enter(tIntrLevel *, INTERRUPT *);
void add_ktrace_int_handler_exit(tIntrLevel *, const struct sigevent *);
void add_ktrace_int_enter(tIntrLevel *);
void add_ktrace_int_exit(tIntrLevel *);
void time_em(uint32_t, uint32_t);
int trace_flushbuffer(void);
void destroy_eh(tProcess *);
void add_trace_string(uint32_t header, const char *fmt, ...);
void add_trace_d1_string(uint32_t header, uint32_t d_1, const char *fmt, ...);
void add_trace_d2_string(uint32_t header, uint32_t d_1, uint32_t d_2, const char *fmt, ...);
int add_trace_event(unsigned code, unsigned data_0, unsigned data_1, unsigned data_2);
void add_trace_buffer(uint32_t header, uint32_t * b_p, unsigned len);
void add_trace_iovs(uint32_t header, IOV * iovs, unsigned iovlen);
void add_ktrace_event(unsigned event, tThread * thp);
void th_em_st(tThread * thp, uint32_t s, int cpu);
void th_em_cd(tThread * thp, uint32_t s, uint32_t c);
void th_em_name(tThread * thp);
void vth_em_cd(tThread * vthp, uint32_t s, uint32_t c);
void vth_em_st(tThread * vthp, uint32_t s);
void pr_em_create(tProcess * prp, pid_t pid);
void pr_em_destroy(tProcess * prp, pid_t pid);
void pr_em_create_name(tProcess * prp);
void pr_em_destroy_name(tProcess * prp);
void comm_em(tThread * thp, tConnect * cop, uint32_t id, uint32_t ev);
void comm_exe_em(tConnect * cop, uint32_t id, uint32_t ev);
void comm_em_signal(tThread * thp, siginfo_t * s_i);
void trace_emit_th_state(tThread * thp, int state);
void trace_emit_sys_aps_name(uint32_t id, char *name);
void trace_emit_sys_aps_budgets(uint32_t id, uint32_t percent, uint32_t critical);
void trace_emit_sys_aps_bankruptcy(uint32_t id, pid_t pid, int32_t tid);
void trace_emit_address(tThread * thp, unsigned vaddr);

void waitpage_status_get(tThread * thp, debug_thread_t * dtp);


uint64_t get_nsec_since_block(tThread * thp);    //in nano_debug.c

//CPU specific things
void cpu_syspage_init(void);
void cpu_interrupt_init(unsigned);
void cpu_thread_init(tThread * act, tThread * thp, int align);
void cpu_thread_waaa(tThread * thp);
void cpu_thread_priv(tThread * thp);
void cpu_thread_align_fault(tThread * thp);
void cpu_thread_destroy(tThread * thp);
void cpu_signal_save(SIGSTACK * ssp, tThread * thp);
void cpu_signal_restore(tThread * thp, SIGSTACK * ssp);
void cpu_intr_attach(INTERRUPT * itp, tThread * thp);
void cpu_greg_load(tThread * thp, CPU_REGISTERS * regs);
void cpu_process_init(tThread * thp, uintptr_t pc, uintptr_t sp);
void cpu_reboot(void);
void cpu_start_ap(uintptr_t start);
void cpu_force_thread_destroyall(tThread * thp);
void cpu_force_fpu_save(tThread * thp);
void cpu_invoke_func(tThread *, uintptr_t);
void cpu_mutex_adjust(tThread *);
void cpu_process_startup(tThread * thp, int forking);

//Routines that get called from outside the kernel
int outside_intr_mask(unsigned vector, int id);
int outside_intr_unmask(unsigned vector, int id);
void outside_intr_lock(struct intrspin *);
void outside_intr_unlock(struct intrspin *);
int outside_trace_event(int *);
int outside_kd_request(union kd_request *);
unsigned outside_vaddr_to_paddr(struct kdebug_entry *entry, uintptr_t vaddr, paddr64_t * paddr,
                                paddr64_t * size);
int outside_kdebug_path(struct kdebug_entry *, char *, int);


//Hook routines that the kernel calls
void hook_idle(uint64_t *, struct qtime_entry *, INTERRUPT *);
struct sigevent *hook_trace(void *, INTERRUPT *);

int rdecl net_sendmsg(tThread * act, tConnect * cop, int prio);
int rdecl net_send_pulse(tThread * act, tConnect * cop, int coid, int prio, int code, int value);
int rdecl net_deliver_signal(tThread * act, struct kerargs_signal_kill *kap);

unsigned cpu_perfreg_id(void);
void rdecl cpu_save_perfregs(void *);
void rdecl cpu_restore_perfregs(void *);
void rdecl cpu_free_perfregs(tThread * thp);
void rdecl cpu_debug_init_perfregs(void);
//int  rdecl    cpu_alloc_perfregs(tThread *thp);

int rdecl msgreceive_gbl(tThread * act, CHANNELGBL * chp, void *msg, size_t size,
                         struct _msg_info *info, tConnect * cop, int coid);
int rdecl msgsend_gbl(tThread * act, tConnect * cop, void *msg, size_t size, unsigned priority,
                      int coid);
#ifdef CONFIG_ASYNC_MSG
int rdecl msgsend_async(tThread * act, tConnect * cop);
int rdecl msgreceive_async(tThread * act, CHANNELASYNC * chp, iov_t * iov, unsigned parts);
#endif

int (rcvmsg) (tThread * dthp, tProcess * sprp, void *destp, int destparts, void *srcp, int srcparts);

#undef MMF
#define MMF(r, f, p, e)		MMF_PROTO(r, f, p, e)
MM_FUNCS(emm)

#ifdef DEBUG_PRIL
void *rdecl pril_first(PRIL_HEAD *);
void *rdecl pril_next(void *);
#else
#define pril_first(ph)	((void *)(ph)->data)
#define pril_next(p)	((void *)(p)->next.pril)
#endif

void *rdecl pril_next_prio(void *);
void *rdecl pril_find_insertion(PRIL_HEAD *, unsigned);
void rdecl pril_add(PRIL_HEAD *, void *);
void rdecl pril_rem(PRIL_HEAD *, void *);
void rdecl pril_update_register(PRIL_HEAD *, struct pril_update *);
void rdecl pril_update_unregister(PRIL_HEAD *, struct pril_update *);

