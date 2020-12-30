/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2019 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Anup Patel <anup.patel@wdc.com>
 */

OUTPUT_ARCH(riscv)
ENTRY(_start)

SECTIONS
{
	/* . = 0xffffffe000000000; */
	. = 0x80200000;
	/*. = ALIGN(0x1000);*/

	PROVIDE(_start = .);

	. = ALIGN(0x1000); /* Need this to create proper sections */

	/* Beginning of the code section */

	.text :
	{
		PROVIDE(_text_start = .);
		*(.entry)
		*(.text)
		. = ALIGN(0x1000);
		_trampoline = .;
		*(.trampoline)
		. = ALIGN(0x1000);
		ASSERT(. - _trampoline == 0x1000, "error: trampoline larger than one page");
		PROVIDE(_text_end = .);
	}

	. = ALIGN(0x1000); /* Ensure next section is page aligned */

	/* End of the code sections */

	/* Beginning of the read-only data sections */

	. = ALIGN(0x1000); /* Ensure next section is page aligned */

	.rodata :
	{
		PROVIDE(_rodata_start = .);
		*(.srodata)
		*(.rodata .rodata.*)
		. = ALIGN(8);
		PROVIDE(_rodata_end = .);
	}

	/* End of the read-only data sections */

	/* Beginning of the read-write data sections */

	. = ALIGN(0x1000); /* Ensure next section is page aligned */

	.data :
	{
		PROVIDE(_data_start = .);
		*(.sdata)
		*(.data)
		*(.data.*)
		*(.readmostly.data)
		*(*.data)
		. = ALIGN(8);

		PROVIDE(_data_end = .);
	}

	. = ALIGN(0x1000); /* Ensure next section is page aligned */

	.bss :
	{
		PROVIDE(_bss_start = .);
		*(.sbss)
		*(.sbss.*)
		*(.bss)
		*(.bss.*)
		. = ALIGN(8);
		PROVIDE(_bss_end = .);
	}

	/* End of the read-write data sections */

	. = ALIGN(0x1000); /* Need this to create proper sections */

	PROVIDE(_end = .);
}
