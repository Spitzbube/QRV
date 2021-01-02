#include <startup.h>
#include <spinlock.h>

#include "task.h"

struct cpu cpus[PROCESSORS_MAX];

// Must be called with interrupts disabled,
// to prevent race with process being moved
// to a different CPU.
int cpuid(void)
{
    int id = r_tp();
    return id;
}

// Return this CPU's cpu struct.
// Interrupts must be disabled.
struct cpu *mycpu(void)
{
    int id = cpuid();
    struct cpu *c = &cpus[id];
    return c;
}

// Return the current struct proc *, or zero if none.
struct proc *myproc(void)
{
    push_off();
    struct cpu *c = mycpu();
    struct proc *p = c->proc;
    pop_off();
    return p;
}
