#define _TRACE_ARGPTR(thp)         (&(thp)->reg.gpr[3])
#define _TRACE_CLOCK_SWAP          (0)
#define _TRACE_SAVE_REGS(t,c)      ((c)->gpr2=(t)->reg.gpr[2],(c)->gpr13=(t)->reg.gpr[13])