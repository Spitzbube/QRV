#if VM_USER_SPACE_BOUNDRY < VM_KERN_SPACE_BOUNDRY
    // kernel/ProcNto is in high memory
#define WITHIN_BOUNDRY(first, last, boundry) ((first) <= (boundry) && (last) <= (boundry))
#else
    // kernel/ProcNto is in low memory
#define WITHIN_BOUNDRY(first, last, boundry) ((first) >= (boundry) && (last) >= (boundry))
#endif
