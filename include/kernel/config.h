/*
 * Kernel and startup configuration file.
 */

#define CONFIG_ULTRA_VERBOSE

#define CONFIG_KPRINTF_MAX_LIMIT                256
#define CONFIG_KPRINTF_PAD_HEX_WITH_ZEROS       1
#define CONFIG_KPRINTF_PTR_BOUND_LOW            0x80000000
#define CONFIG_KPRINTF_PTR_BOUND_HIGH           0x8FFFFFFF

#define CONFIG_MAX_BOOTLINE_SIZE                256

#define CONFIG_FDT_DEBUG
