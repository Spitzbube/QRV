#if !defined(CPU_PRT_SYSPAGE_RTN)

#include <startup.h>

#define PSP_STARTUP		1
#define PSP_SYSPAGE		lsp.syspage.p
#define PSP_SPRINTF		ksprintf
#define PSP_VERBOSE(lvl)	(debug_flag > (lvl))

#define PSP_NATIVE_ENDIAN16(v)	(v)
#define PSP_NATIVE_ENDIAN32(v)	(v)
#define PSP_NATIVE_ENDIAN64(v)	(v)
#define PSP_NATIVE_ENDIANPTR(v)	(v)

#endif

#include "cpu_print_sysp.ci"
