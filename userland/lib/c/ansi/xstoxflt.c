/*
 * $QNXtpLicenseC:
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




Also copyright P.J. Plauger - see bottom of file for details.
*/

/* _Stoxflt function */
#include <ctype.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include "xmath.h"
_STD_BEGIN

#define BASE	16	/* hexadecimal */
#define NDIG	7	/* hexadecimal digits per long element */

#ifdef __QNX__
/* MAXSIG clashes with an unrelated MAXSIG in signal.h.
   So, undefine it. */
#undef MAXSIG
#endif
#define MAXSIG	(5 * NDIG)	/* maximum significant digits to keep */

int _Stoxflt(const char *s0, const char *s, char **endptr, long lo[],
	int maxsig)
	{	/* convert string to array of long plus exponent */
	char buf[MAXSIG + 1];	/* worst case, with room for rounding digit */
	int nsig;	/* number of significant digits seen */
	int seen;	/* any valid field characters seen */
	int word;	/* current long word to fill */

	const char *pd;
	static const char digits[] = "0123456789abcdefABCDEF";
	static const char vals[] =
		{	/* values of hex digits */
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
		10, 11, 12, 13, 14, 15};

	maxsig *= NDIG;	/* convert word count to digit count */
	if (MAXSIG < maxsig)
		maxsig = MAXSIG;	/* protect against bad call */

	lo[0] = 0;	/* power of ten exponent */
	lo[1] = 0;	/* first NDIG-digit word of fraction */

	for (seen = 0; *s == '0'; ++s, seen = 1)
		;	/* strip leading zeros */
	for (nsig = 0; (pd = (char *)memchr(&digits[0], *s, 22)) != 0;
		++s, seen = 1)
#ifdef __QNX__
		/* Allow one digit more than maxsig, and round up later */
		if (nsig <= maxsig)
#else
		if (nsig < maxsig)
#endif
			buf[nsig++] = vals[pd - digits];	/* accumulate a digit */
		else
			++lo[0];	/* too many digits, just scale exponent */

	if (*s == localeconv()->decimal_point[0])
		++s;
	if (nsig == 0)
		for (; *s == '0'; ++s, seen = 1)
			--lo[0];	/* strip zeros after point */
	for (; (pd = (char *)memchr(&digits[0], *s, 22)) != 0; ++s, seen = 1)
		if (nsig <= maxsig)
			{	/* accumulate a fraction digit */
			buf[nsig++] = vals[pd - digits];
			--lo[0];
			}

	if (maxsig < nsig)
		{	/* discard excess digit after rounding up */
		unsigned int ms = maxsig;	/* to quiet warnings */

		if (BASE / 2 <= buf[ms])
			++buf[ms - 1];	/* okay if digit becomes BASE */
		nsig = maxsig;
		++lo[0];
		}
	for (; 0 < nsig && buf[nsig - 1] == '\0'; --nsig)
		++lo[0];	/* discard trailing zeros */
	if (nsig == 0)
		buf[nsig++] = '\0';	/* ensure at least one digit */
	lo[0] <<= 2;	/* change hex exponent to binary exponent */

	if (seen)
		{	/* convert digit sequence to words */
		int bufidx = 0;	/* next digit in buffer */
		int wordidx = NDIG - nsig % NDIG;	/* next digit in word (% NDIG) */

		word = wordidx % NDIG == 0 ? 0 : 1;
		for (; bufidx < nsig; ++wordidx, ++bufidx)
			if (wordidx % NDIG == 0)
				lo[++word] = buf[bufidx];
			else
				lo[word] = lo[word] * BASE + buf[bufidx];

		if (*s == 'p' || *s == 'P')
			{	/* parse exponent */
			const char *ssav = s;
			const char esign = *++s == '+' || *s == '-' ? *s++ : '+';
			int eseen = 0;
			long lexp = 0;

			for (; isdigit((unsigned char)*s); ++s, eseen = 1)
				if (lexp < 100000000)	/* else overflow */
					lexp = lexp * 10 + (unsigned char)*s - '0';
			if (esign == '-')
				lexp = -lexp;
			lo[0] += lexp;
			if (!eseen)
				s = ssav;	/* roll back if incomplete exponent */
			}
		}

	if (!seen)
		word = 0;	/* return zero if bad parse */
	if (endptr)
		*endptr = (char *)(seen ? s : s0);	/* roll back if bad parse */
	return (word);
		}
_STD_END

/*
 * Copyright (c) 1992-2006 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V5.00:1296 */



