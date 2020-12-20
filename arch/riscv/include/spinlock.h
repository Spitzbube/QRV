#ifndef _RISCV_SPINLOCK_H
#define _RISCV_SPINLOCK_H

// Mutual exclusion lock.
struct spinlock {
    unsigned locked;            // Is the lock held?

    // For debugging:
    char *name;                 // Name of lock.
    struct cpu *cpu;            // The cpu holding the lock.
};

void  acquire(struct spinlock*);
int   holding(struct spinlock*);
void  initlock(struct spinlock*, char*);
void  release(struct spinlock*);
void  push_off(void);
void  pop_off(void);

#endif
