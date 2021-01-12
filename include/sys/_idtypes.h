/**
 * \file sys/_timetypes.h
 *
 * Definitions of ID integer types (like PID, UID, GID).
 *
 * \author Yuri Zaporozhets <r_tty@yahoo.co.uk>
 * \license GNU GPL 2.0
 */

#ifndef _SYS_IDTYPES_T
#define _SYS_IDTYPES_T

#include <stdint-gcc.h>

typedef int32_t id_t;

typedef int32_t pid_t;
typedef int32_t uid_t;
typedef int32_t gid_t;

#endif
