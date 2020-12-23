/**
 * \brief Machine mode initialization, called from the assembly code (entry.S)
 *
 * \license MIT (https://opensource.org/licenses/mit-license.php)
 *
 * \copyright (c) 2006-2020 Frans Kaashoek, Robert Morris, Russ Cox,
 *                          Massachusetts Institute of Technology
 */

#include <kernel/startup.h>
#include <platform/qemu_virt.h>
#include <riscv.h>

extern void _main();
void timerinit();

// entry.S needs one stack per CPU.
__attribute__((aligned(16)))
char stack0[4096 * PROCESSORS_MAX];

// a scratch area per CPU for machine-mode timer interrupts.
uint64_t timer_scratch[PROCESSORS_MAX][5];

// assembly code in kernelvec.S for machine-mode timer interrupt.
extern void timervec();

// entry.S jumps here in machine mode on stack0.
void start()
{
    // Set M Previous Privilege mode to Supervisor, for mret.
    unsigned long x = r_mstatus();
    x &= ~MSTATUS_MPP_MASK;
    x |= MSTATUS_MPP_S;
    w_mstatus(x);

    // Set M Exception Program Counter to _main(), for mret.
    // Requires gcc -mcmodel=medany
    w_mepc((uint64_t) _main);

    // Disable paging for now.
    w_satp(0);

    // Delegate all interrupts and exceptions to supervisor mode.
    w_medeleg(0xffff);
    w_mideleg(0xffff);
    w_sie(r_sie() | SIE_SEIE | SIE_STIE | SIE_SSIE);

    // Ask for clock interrupts.
    timerinit();

    // Keep each CPU's hartid in its tp register, for cpuid().
    int id = r_mhartid();
    w_tp(id);

    // Switch to supervisor mode and jump to main().
    asm volatile ("mret");
}

// set up to receive timer interrupts in machine mode,
// which arrive at timervec in kernelvec.S,
// which turns them into software interrupts for
// devintr() in trap.c.
void timerinit()
{
    // each CPU has a separate source of timer interrupts.
    int id = r_mhartid();

    // ask the CLINT for a timer interrupt.
    int interval = 1000000;     // cycles; about 1/10th second in qemu.
    *(uint64_t *) CLINT_MTIMECMP(id) = *(uint64_t *) CLINT_MTIME + interval;

    // prepare information in scratch[] for timervec.
    // scratch[0..2] : space for timervec to save registers.
    // scratch[3] : address of CLINT MTIMECMP register.
    // scratch[4] : desired interval (in cycles) between timer interrupts.
    uint64_t *scratch = &timer_scratch[id][0];
    scratch[3] = CLINT_MTIMECMP(id);
    scratch[4] = interval;
    w_mscratch((uint64_t) scratch);

    // set the machine-mode trap handler.
    w_mtvec((uint64_t) timervec);

    // enable machine-mode interrupts.
    w_mstatus(r_mstatus() | MSTATUS_MIE);

    // enable machine-mode timer interrupts.
    w_mie(r_mie() | MIE_MTIE);
}
