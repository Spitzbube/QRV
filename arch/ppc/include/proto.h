/*
 * use the "kdecl" attribute to avoid having to save/restore extra
 * registers for kcall fucntions
 */
//#define kdecl __attribute__((kdecl)) // Turn on when compilers support
#define kdecl
#define rdecl
#define specialret_attr
#define intrevent_add_attr
#define intrevent_drain_attr
