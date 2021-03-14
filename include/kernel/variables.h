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

#ifndef _KERNEL_VARIABLES_H
#define _KERNEL_VARIABLES_H

#if defined(rdecl) || defined(KERHDR)
#error Not to be mixed with other kernel/ includes
#endif

#include <stddef.h>
#include <inttypes.h>
#include <arch/cpu_def.h>

#include <sys/fault.h>
#include <sys/debug.h>
#include <kernel/macros.h>
#include <sys/kdebug.h>
#include <kernel/debug.h>
#include <kernel/objects.h>
#include <kernel/kerext.h>
#include <kernel/proto.h>
#include <kernel/query.h>
#include "kernel/memclass.h"

extern tSoul process_souls;
extern tVector process_vector;
extern tProcMgr procmgr;
extern tMemMgr memmgr;
extern unsigned num_processors;
extern tProcess *procnto_prp;
extern memclass_id_t sys_memclass_id;   // generic system ram memory class
extern tVector mempart_vector;
extern tVector schedpart_vector;

extern unsigned user_boundry_addr;

extern const long kernel_conf_table[];

extern int ker_verbose;
extern int munmap_flags_default;
extern mode_t procfs_umask;

#endif
