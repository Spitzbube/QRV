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
 *  spawn.h
 *

 */
#ifndef _SPAWN_H_INCLUDED
#define _SPAWN_H_INCLUDED

#ifndef __TYPES_H_INCLUDED
#include <sys/types.h>
#endif

#ifndef _SIGNAL_H_INCLUDED
#include <signal.h>
#endif

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

__BEGIN_DECLS
#ifndef _SCHED_H_INCLUDED
#include <sched.h>
#endif
/*
 * posix_spawnattr_t
*/
typedef _Uintptrt posix_spawnattr_t;
#define POSIX_SPAWNATTR_INITIALIZER		{NULL}

/*
 * posix_spawn_file_actions_t
*/
typedef _Uintptrt posix_spawn_file_actions_t;
#define POSIX_SPAWN_FILE_ACTIONS_INITIALIZER		{NULL}

/* prototypes */
extern int posix_spawnattr_init(posix_spawnattr_t * attrp);
extern int posix_spawnattr_destroy(posix_spawnattr_t * attrp);
extern int posix_spawnattr_getflags(const posix_spawnattr_t * restrict attrp,
                                    short *restrict flags_p);
extern int posix_spawnattr_setflags(posix_spawnattr_t * attrp, short flags);
extern int posix_spawnattr_getsigdefault(const posix_spawnattr_t * restrict attrp,
                                         sigset_t * restrict sigset_p);
extern int posix_spawnattr_setsigdefault(posix_spawnattr_t * restrict attrp,
                                         const sigset_t * restrict sigset_p);
extern int posix_spawnattr_getsigmask(const posix_spawnattr_t * restrict attrp,
                                      sigset_t * restrict sigset_p);
extern int posix_spawnattr_setsigmask(posix_spawnattr_t * restrict attrp,
                                      const sigset_t * restrict sigset_p);
extern int posix_spawnattr_getpgroup(const posix_spawnattr_t * restrict attrp,
                                     pid_t * restrict pid_p);
extern int posix_spawnattr_setpgroup(posix_spawnattr_t * attrp, pid_t pid);
extern int posix_spawnattr_getschedparam(const posix_spawnattr_t * restrict attrp,
                                         struct sched_param *restrict sched_p);
extern int posix_spawnattr_setschedparam(posix_spawnattr_t * restrict attrp,
                                         const struct sched_param *restrict sched_p);
extern int posix_spawnattr_getschedpolicy(const posix_spawnattr_t * restrict attrp,
                                          int *restrict policy_p);
extern int posix_spawnattr_setschedpolicy(posix_spawnattr_t * attrp, int policy);

extern int posix_spawn_file_actions_init(posix_spawn_file_actions_t * fact_p);
extern int posix_spawn_file_actions_destroy(posix_spawn_file_actions_t * fact_p);
extern int posix_spawn_file_actions_addclose(posix_spawn_file_actions_t * fact_p, int fd);
extern int posix_spawn_file_actions_adddup2(posix_spawn_file_actions_t * fact_p, int fd,
                                            int new_fd);
extern int posix_spawn_file_actions_addopen(posix_spawn_file_actions_t * restrict fact_p,
                                            int new_fd, const char *restrict path, int oflags,
                                            mode_t omode);

extern int posix_spawn(pid_t * restrict pid, const char *restrict path,
                       const posix_spawn_file_actions_t * file_actions,
                       const posix_spawnattr_t * restrict __attrp, char *const argv[restrict],
                       char *const envp[restrict]);
extern int posix_spawnp(pid_t * restrict pid, const char *restrict file,
                        const posix_spawn_file_actions_t * file_actions,
                        const posix_spawnattr_t * restrict __attrp, char *const argv[restrict],
                        char *const envp[restrict]);

#define POSIX_SPAWN_SETPGROUP		0x00000001  /* set process group */
#define POSIX_SPAWN_SETSIGMASK		0x00000002  /* set mask to sigmask */
#define POSIX_SPAWN_SETSIGDEF		0x00000004  /* set members of sigdefault to SIG_DFL */
#define POSIX_SPAWN_SETSCHEDULER	0x00000040  /* set members of sigignore to SIG_IGN */
#define POSIX_SPAWN_SETSCHEDPARAM	0x00000400  /* Set the scheduling policy */
#define POSIX_SPAWN_RESETIDS		0x0000

/* QNX extensions */
#if defined(__EXT_QNX)

#include <sys/part.h>

#define POSIX_SPAWN_SETSIGIGN		0x00000008  /* set members of sigignore to SIG_IGN */
#define POSIX_SPAWN_SETMPART		0x00000010  /* associate process with a set of memory partitions */
#define POSIX_SPAWN_SETSPART		0x00000020  /* associate process with a scheduler partition */
#define POSIX_SPAWN_SETND			0x00000100  /* spawn to remote node */
#define POSIX_SPAWN_EXPLICIT_CPU	0x00000800  /* Set the CPU affinity/runmask */
#define POSIX_SPAWN_SETSTACKMAX		0x00001000  /* Set the stack max */
#define POSIX_SPAWN_NOZOMBIE		0x00002000  /* Process will not zombie on death  */
#define POSIX_SPAWN_ALIGN_DEFAULT	0x00000000  /* Use system default settings for alignment */
#define POSIX_SPAWN_ALIGN_FAULT		0x01000000  /* Try to always fault data misalignment references */
#define POSIX_SPAWN_ALIGN_NOFAULT	0x02000000  /* Don't fault on misalignment, and attempt to fix it (may be slow) */


extern int posix_spawnattr_getxflags(const posix_spawnattr_t * restrict attrp,
                                     uint32_t * restrict flags_p);
extern int posix_spawnattr_setxflags(posix_spawnattr_t * attrp, uint32_t flags);
extern int posix_spawnattr_addpartition(posix_spawnattr_t * restrict attrp,
                                        const char *partition_path, part_dcmd_flags_t flags);
extern int posix_spawnattr_addpartid(posix_spawnattr_t * restrict attrp, part_id_t part_id,
                                     part_dcmd_flags_t flags);
#define posix_spawnattr_addmempartid(__attrp__, __part_id__, __flags__)		posix_spawnattr_addpartid((_attrp__), (__part_id__), (__flags__))
#define posix_spawnattr_addschedpartid(__attrp__, __part_id__, __flags__)	posix_spawnattr_addpartid((_attrp__), (__part_id__), (__flags__))
extern int posix_spawnattr_getpartid(const posix_spawnattr_t * restrict attrp, int *num,
                                     partlist_info_t plist_info[]);
extern int posix_spawnattr_getrunmask(const posix_spawnattr_t * restrict attrp,
                                      uint32_t * restrict runmask_p);
extern int posix_spawnattr_setrunmask(posix_spawnattr_t * attrp, uint32_t runmask);
extern int posix_spawnattr_getsigignore(const posix_spawnattr_t * restrict attrp,
                                        sigset_t * restrict sigset_p);
extern int posix_spawnattr_setsigignore(posix_spawnattr_t * restrict attrp,
                                        const sigset_t * restrict sigset_p);
extern int posix_spawnattr_getstackmax(const posix_spawnattr_t * restrict attrp,
                                       uint32_t * restrict size_p);
extern int posix_spawnattr_setstackmax(posix_spawnattr_t * attrp, uint32_t size);
extern int posix_spawnattr_getnode(const posix_spawnattr_t * restrict attrp,
                                   uint32_t * restrict node_p);
extern int posix_spawnattr_setnode(posix_spawnattr_t * attrp, uint32_t node);


typedef struct inheritance {
    unsigned long flags;
    pid_t pgroup;               /* SPAWN_SETGROUP must be set in flags */
    sigset_t sigmask;           /* SPAWN_SETSIGMASK must be set in flags */
    sigset_t sigdefault;        /* SPAWN_SETSIGDEF must be set in flags */
    sigset_t sigignore;         /* SPAWN_SETSIGIGN must be set in flags */
    unsigned long stack_max;    /* SPAWN_SETSTACKMAX must be set in flags */
#if __INT_BITS__ != 32
    long policy;                /* SPAWN_EXPLICIT_SCHED must be set in flags */
#else
    int policy;                 /* SPAWN_EXPLICIT_SCHED must be set in flags */
#endif
    _Uint32t nd;                /* SPAWN_SETND must be set in flags */
    _Uint32t runmask;           /* SPAWN_EXPLICIT_CPU must be set in flags */
    struct sched_param param;   /* SPAWN_EXPLICIT_SCHED must be set in flags */
} spawn_inheritance_type;

#define SPAWN_SETGROUP			POSIX_SPAWN_SETPGROUP
#define SPAWN_SETSIGMASK		POSIX_SPAWN_SETSIGMASK
#define SPAWN_SETSIGDEF			POSIX_SPAWN_SETSIGDEF
#define SPAWN_SETSIGIGN			POSIX_SPAWN_SETSIGIGN
#define SPAWN_SETMEMPART		POSIX_SPAWN_SETMPART
#define SPAWN_SETSCHEDPART		POSIX_SPAWN_SETSPART
#define SPAWN_TCSETPGROUP		0x00000080  /* Start a new terminal group */
#define SPAWN_SETND				POSIX_SPAWN_SETND
#define SPAWN_SETSID			0x00000200  /* Make new process a session leader */
#define SPAWN_EXPLICIT_SCHED	POSIX_SPAWN_SETSCHEDPARAM
#define SPAWN_EXPLICIT_CPU		POSIX_SPAWN_EXPLICIT_CPU
#define SPAWN_SETSTACKMAX		POSIX_SPAWN_SETSTACKMAX
#define SPAWN_NOZOMBIE			POSIX_SPAWN_NOZOMBIE
#define SPAWN_DEBUG				0x00004000  /* Debug process */
#define SPAWN_HOLD				0x00008000  /* Hold a process for Debug */
#define SPAWN_EXEC				0x00010000  /* Cause the spawn to act like exec() */
#define SPAWN_SEARCH_PATH		0x00020000  /* Search envar PATH for executable */
#define SPAWN_CHECK_SCRIPT		0x00040000  /* Allow starting a shell passing file as script */
#define SPAWN_ALIGN_DEFAULT		POSIX_SPAWN_ALIGN_DEFAULT
#define SPAWN_ALIGN_FAULT		POSIX_SPAWN_ALIGN_FAULT
#define SPAWN_ALIGN_NOFAULT		POSIX_SPAWN_ALIGN_NOFAULT
#define SPAWN_ALIGN_MASK		0x03000000  /* Mask for align fault states below */
#define SPAWN_PADDR64_SAFE		0x04000000  /* Memory physically located >4G is allowed */

#define SPAWN_FDCLOSED			(-1)
#define SPAWN_FDOPEN			(-2)
#define SPAWN_NEWPGROUP			0

extern pid_t spawn(const char *__path, int __fd_count, const int __fd_map[],
                   const struct inheritance *__inherit, char *const __argv[], char *const __envp[]);
extern pid_t spawnp(const char *__file, int __fd_count, const int __fd_map[],
                    const struct inheritance *__inherit, char *const __argv[],
                    char *const __envp[]);

#endif                          /* defined(__EXT_QNX) */


__END_DECLS
#endif
