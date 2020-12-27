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




#ifdef DEFN
#define EXT
#else
#define EXT extern
#endif

EXT list_head_t _dl_all_objects;
#ifdef DEFN
EXT pthread_mutex_t _dl_list_mutex = PTHREAD_MUTEX_INITIALIZER;
#else
EXT pthread_mutex_t _dl_list_mutex;
#endif

/* __SRCVERSION("externs.h $Rev: 153052 $"); */