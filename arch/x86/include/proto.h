/*
 * not much fancy for now; just a little gnu-insanity
 */
#define kdecl
#define rdecl __attribute__((cdecl,regparm(3)))
#define specialret_attr __attribute__((regparm(1)))
#define intrevent_add_attr __attribute__((regparm(3)))
#define intrevent_drain_attr
