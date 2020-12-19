// Mutual exclusion lock.
struct spinlock {
    unsigned locked;            // Is the lock held?

    // For debugging:
    char *name;                 // Name of lock.
    struct cpu *cpu;            // The cpu holding the lock.
};

static inline void push_off(void) {}
static inline void pop_off(void) {}
