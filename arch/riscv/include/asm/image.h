/* SPDX-License-Identifier: GPL-2.0 */

#ifndef _RISCV_ASM_IMAGE_H
#define _RISCV_ASM_IMAGE_H

#define RISCV_IMAGE_MAGIC	"RISCV\0\0\0"
#define RISCV_IMAGE_MAGIC2	"RSC\x05"

#define RISCV_IMAGE_FLAG_LE		0

#define RISCV_HEADER_VERSION_MAJOR 0
#define RISCV_HEADER_VERSION_MINOR 2

#define RISCV_HEADER_VERSION (RISCV_HEADER_VERSION_MAJOR << 16 | RISCV_HEADER_VERSION_MINOR)

#ifndef __ASSEMBLY__
/**
 * struct riscv_image_header - riscv kernel image header
 * @code0:		Executable code
 * @code1:		Executable code
 * @text_offset:	Image load offset (little endian)
 * @image_size:		Effective Image size (little endian)
 * @flags:		kernel flags (little endian)
 * @version:		version
 * @res1:		reserved
 * @res2:		reserved
 * @magic:		Magic number (RISC-V specific; deprecated)
 * @magic2:		Magic number 2 (to match the ARM64 'magic' field pos)
 * @res3:		reserved (will be used for PE COFF offset)
 *
 * The intention is for this header format to be shared between multiple
 * architectures to avoid a proliferation of image header formats.
 */

struct riscv_image_header {
	uint32_t code0;
	uint32_t code1;
	uint64_t text_offset;
	uint64_t image_size;
	uint64_t flags;
	uint32_t version;
	uint32_t res1;
	uint64_t res2;
	uint64_t magic;
	uint32_t magic2;
	uint32_t res3;
};
#endif /* __ASSEMBLY__ */

#endif
