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

#ifndef _MEMMGR_PROTO_H
#define _MEMMGR_PROTO_H

#include <taskman/pathmgr_object.h>

/* memmgr_init.c */
void memmgr_init(void);
int memmgr_resize(tPathMgrObject * obp, size_t size);
extern const struct object_funcs mem_funcs;

/* memmgr_map.c */
int memmgr_find_object(resmgr_context_t * ctp, tProcess * prp, int fd, mem_map_t * msg,
                       tPathMgrObject ** obpp);
int memmgr_map(resmgr_context_t * ctp, tProcess * prp, mem_map_t * msg);

/* memmgr_ctrl.c */
int memmgr_ctrl(tProcess * prp, mem_ctrl_t * msg);

/* memmgr_info.c */
int memmgr_info(resmgr_context_t * ctp, tProcess * prp, mem_info_t * msg);

/* memmgr_offset.c */
int memmgr_offset(resmgr_context_t * ctp, tProcess * prp, mem_offset_t * msg);

/* memmgr_debug_info.c */
int memmgr_debug_info(resmgr_context_t * ctp, tProcess * prp, mem_debug_info_t * msg);

/* memmgr_fd.c */
void memmgr_fd_init(void);
int memmgr_open_fd(resmgr_context_t * ctp, tProcess *, mem_map_t * msg, tPathMgrObject ** obp);
int memmgr_fd_compact(void);
int memmgr_fd_setname(tPathMgrObject * obp, char *name);

/* memmgr_swap.c */
struct _swap_page_list;
int memmgr_swap(resmgr_context_t * ctp, tProcess * prp, mem_swap_t * msg);
int memmgr_swapout(struct _swap_page_list *list, int n, void *obj);
int memmgr_swapin(struct _swap_page_list *list, int n, void *obj);
int memmgr_swaprem(struct _swap_page_list *list, int n, void *obj);
int memmgr_swap_freemem(pid_t pid, unsigned size, unsigned flags);

/* memmgr_support.c */
int rdecl proc_rlock_adp(tProcess *);
int rdecl proc_wlock_adp(tProcess *);
int rdecl proc_unlock_adp(tProcess *);
int rdecl proc_rlock_promote_adp(tProcess *);
void rdecl proc_lock_owner_mark(tProcess *);
int rdecl proc_lock_owner_check(tProcess *, pid_t, unsigned);

int memmgr_tymem_open(const char *path, int oflags, tPathMgrObject ** obpp, tProcess * prp);
void memmgr_tymem_close(tPathMgrObject * obp);

#endif
