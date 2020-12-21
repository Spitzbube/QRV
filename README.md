This is QRV, an adaptation (and later re-implementation) of the famous
QNX Neutrino 6.4 operating system to modern 64-bit hardware, aimed primarily
at keeping the Transparent Distributed Processing in the system.

Key differences from the standard QNX 6.4:

 * re-organized source tree
 * integration of startup into the same source tree
 * (planned) configuration system, same as in Linux
 * getting rid of callouts/callins/patches
 * simplifications in the scheduler, multicore-only
 * Unix filesystem (taken from xv6)
 * disk device driver (devb) for QEMU virtio (taken from xv6)
