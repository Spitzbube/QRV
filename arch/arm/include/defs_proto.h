EXT unsigned mmu_domain[PROCESSORS_MAX];
EXT void (*mmu_abort)(CPU_REGISTERS *);
EXT uint64_t last_cycles;
#if defined(VARIANT_v6) && !defined(VARIANT_smp)
/*
 * We need to clear the ARMv6 exclusive monitor on context switches:
 * - on SMP (ARMv6K architectures) we can use clrex.
 * - on non-ARMv6K, we need to perform a dummy strex, so we provide
 *   dummy_strex as a safe location to perform the store.
 */
EXT unsigned dummy_strex;
