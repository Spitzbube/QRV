#define _TRACE_ARGPTR(thp)         (&(thp)->reg.regs[MIPS_BAREG(MIPS_REG_A0)])
#define _TRACE_CLOCK_SWAP          (1)
#define _TRACE_SAVE_REGS(t,c)      ((c)->gp=*(uint64_t*)&(t)->reg.regs[MIPS_BAREG(MIPS_REG_GP)])