/**
 * \file mkasmoff.h
 *
 * This file, along with mkasmoff, is used to generate an assembler
 * include file that contains the offsets of fields and values of
 * manifest constants. The strings in the "COMMENT" macro will appear
 * as comments in the resulting assembler include file. The first
 * parameter of the "VALUE" macro will be the name of the assembler
 * symbolic constant while the second parameter will be its value.
 *
 * Things are done in this roundabout way so that the correct
 * values are generated even if the host system used to compile the
 * kernel is not the same as the target system it's going to run
 * on.
 *
 * \copyright 2007, QNX Software Systems. All Rights Reserved.
 *
 * \license QNX NCEULA 1.01
 *          http://www.qnx.com/legal/licensing/dev_license/eula/nceula1_01.html
 */

/* These extra macros are needed because of ANSI - TODO: clarify */
#define _NAME( pref, line, suff ) pref##line##suff
#define NAME( pref, line, suff ) _NAME( pref, line, suff )

#define COMMENT_SUFFIX	_
#define COMMENT( comm ) char NAME( comment, __LINE__, COMMENT_SUFFIX )[] = comm
#define VALUE( name, val ) unsigned NAME( value, __LINE__, ____##name ) = val
