#ifndef __SMPXCHG_H_INCLUDED
#define __SMPXCHG_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

__BEGIN_DECLS

// TODO: implement
extern unsigned _smp_cmpxchg(volatile unsigned *__dst, unsigned __cmp, unsigned __src);
extern unsigned _smp_xchg(volatile unsigned *__dst, unsigned __src);

// _mux_smp_cmpxchg() is used only for mutexes
extern unsigned _mux_smp_cmpxchg(volatile unsigned *__dst, unsigned __cmp, unsigned __src);

#define __mutex_smp_cmpxchg(d, c, s)	_mux_smp_cmpxchg((d), (c), (s))

__END_DECLS

#endif
