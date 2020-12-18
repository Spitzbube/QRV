/*
 * $QNXLicenseC:
 * Copyright 2007, QNX Software Systems. All Rights Reserved.
 *
 * You must obtain a written license from and pay applicable license fees to QNX
 * Software Systems before you may reproduce, modify or distribute this software,
 * or any work that includes all or part of this software.   Free development
 * licenses are available for evaluation and non-commercial purposes.  For more
 * information visit http://licensing.qnx.com or email licensing@qnx.com.
 *
 * This file may contain contributions from others.  Please review this entire
 * file for other proprietary rights or license notices, as well as the QNX
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 * $
 */



/*
 *  ppc/970cpu.h
 *
 * Registers specific to the PPC 970
 *

 */

#ifndef __PPC_970CPU_H_INCLUDED
#define __PPC_970CPU_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif


/*
 * SPR registers
 */
#define PPC970_SPR_DABRX		1015
#define PPC970_SPR_HID0			1008
#define PPC970_SPR_HID1			1009
#define PPC970_SPR_HID4			1012
#define PPC970_SPR_HID5			1014
#define PPC970_SPR_SCOMC		276
#define PPC970_SPR_SCOMD		277
#define PPC970_SPR_IMC			799
#define PPC970_SPR_IMC_USER		783
#define PPC970_SPR_TRIG0		976
#define PPC970_SPR_TRIG1		977
#define PPC970_SPR_TRIG2		978
#define PPC970_SPR_VRSAVE		256

/*
 * Exception table vectors
 */
#define PPC970_EXC_MAINTENANCE	(0x1600/sizeof(uint32_t))
#define PPC970_EXC_VPU_ASSIST	(0x1700/sizeof(uint32_t))
#define PPC970_EXC_THERMAL		(0x1800/sizeof(uint32_t))

/*
 * HID0
 */
#define	PPC970_SPR_HID0_ONE_PPC		_ONEBIT64B(0)
#define	PPC970_SPR_HID0_DO_SINGLE	_ONEBIT64B(1)
#define	PPC970_SPR_HID0_ISYNC_SC	_ONEBIT64B(2)
#define	PPC970_SPR_HID0_SER_GP		_ONEBIT64B(3)
#define	PPC970_SPR_HID0_NAP			_ONEBIT64B(9)
#define	PPC970_SPR_HID0_DPM			_ONEBIT64B(11)
#define	PPC970_SPR_HID0_TG			_ONEBIT64B(13)
#define	PPC970_SPR_HID0_HANG_DIS	_ONEBIT64B(14)
#define	PPC970_SPR_HID0_NHR			_ONEBIT64B(15)
#define	PPC970_SPR_HID0_INORDER		_ONEBIT64B(16)
#define	PPC970_SPR_HID0_TB_CTRL		_ONEBIT64B(18)
#define	PPC970_SPR_HID0_EXT_TB_EN	_ONEBIT64B(19)
#define	PPC970_SPR_HID0_CIABR_EN	_ONEBIT64B(22)
#define	PPC970_SPR_HID0_HDICE_EN	_ONEBIT64B(23)
#define	PPC970_SPR_HID0_EN_TERM		_ONEBIT64B(24)
#define	PPC970_SPR_HID0_EN_ATTN		_ONEBIT64B(25)
#define	PPC970_SPR_HID0_EN_MCK		_ONEBIT64B(26)

/*
 * HID1
 */
#define	PPC970_SPR_HID1_BHT_PM_MASK			_BITFIELD64B(2,0x7)
#define	PPC970_SPR_HID1_BHT_PM_STATIC		_BITFIELD64B(2,0x0)
#define	PPC970_SPR_HID1_BHT_PM_UNUSED1		_BITFIELD64B(2,0x1)
#define	PPC970_SPR_HID1_BHT_PM_GBL_BHT		_BITFIELD64B(2,0x2)
#define	PPC970_SPR_HID1_BHT_PM_GBL_COMPRESS	_BITFIELD64B(2,0x3)
#define	PPC970_SPR_HID1_BHT_PM_LCL_BHT		_BITFIELD64B(2,0x4)
#define	PPC970_SPR_HID1_BHT_PM_UNUSED2		_BITFIELD64B(2,0x5)
#define	PPC970_SPR_HID1_BHT_PM_FULL			_BITFIELD64B(2,0x6)
#define	PPC970_SPR_HID1_BHT_PM_FULL_COMPRESS _BITFIELD64B(2,0x7)
#define	PPC970_SPR_HID1_EN_LS				_ONEBIT64B(3)
#define	PPC970_SPR_HID1_EN_CC				_ONEBIT64B(4)
#define	PPC970_SPR_HID1_EN_IC				_ONEBIT64B(5)
#define	PPC970_SPR_HID1_PF_MODE_MASK		_BITFIELD64B(8,0x3)
#define	PPC970_SPR_HID1_PF_MODE_NONE		_BITFIELD64B(8,0x0)
#define	PPC970_SPR_HID1_PF_MODE_NSA			_BITFIELD64B(8,0x1)
#define	PPC970_SPR_HID1_PF_MODE_NSA_PLUS_1	_BITFIELD64B(8,0x2)
#define	PPC970_SPR_HID1_PF_MODE_DISABLED	_BITFIELD64B(8,0x3)
#define	PPC970_SPR_HID1_EN_ICBI				_ONEBIT64B(9)
#define	PPC970_SPR_HID1_EN_IF_CACH			_ONEBIT64B(10)
#define	PPC970_SPR_HID1_EN_IF_REC			_ONEBIT64B(11)
#define	PPC970_SPR_HID1_EN_ID_REC			_ONEBIT64B(12)
#define	PPC970_SPR_HID1_EN_ER_REC			_ONEBIT64B(13)
#define	PPC970_SPR_HID1_IC_PE				_ONEBIT64B(14)
#define	PPC970_SPR_HID1_ICD0_PE				_ONEBIT64B(15)
#define	PPC970_SPR_HID1_IER_PE				_ONEBIT64B(17)
#define	PPC970_SPR_HID1_EN_SP_ITW			_ONEBIT64B(18)

/*
 * HID4
 */
#define PPC970_SPR_HID4_LPES1				_ONEBIT64B(0)
#define PPC970_SPR_HID4_RMLR_1_2_MASK		_BITFIELD64B(2,0x3)
#define PPC970_SPR_HID4_RMLR_1_2_SHIFT		(63-2)
#define PPC970_SPR_HID4_LPID_2_5_MASK		_BITFIELD64B(6,0xf)
#define PPC970_SPR_HID4_LPID_2_5_SHIFT		(63-6)
#define PPC970_SPR_HID4_RMOR_0_15_MASK		_BITFIELD64B(22,0xffff)
#define PPC970_SPR_HID4_RMOR_0_15_SHIFT		(63-22)
#define PPC970_SPR_HID4_RM_CI				_ONEBIT64B(23)
#define PPC970_SPR_HID4_FORCE_AI			_ONEBIT64B(24)
#define PPC970_SPR_HID4_DIS_PREF			_ONEBIT64B(25)
#define PPC970_SPR_HID4_RES_PREF			_ONEBIT64B(26)
#define PPC970_SPR_HID4_EN_SP_DTW			_ONEBIT64B(27)
#define PPC970_SPR_HID4_L1DC_FLSH			_ONEBIT64B(28)
#define PPC970_SPR_HID4_DIS_DERPC_MASK		_BITFIELD64B(30,0x3)
#define PPC970_SPR_HID4_DIS_DERPC_SHIFT		(63-30)
#define PPC970_SPR_HID4_DIS_DERPG			_ONEBIT64B(31)
#define PPC970_SPR_HID4_DIS_DERAT_MASK		_BITFIELD64B(33,0x3)
#define PPC970_SPR_HID4_DIS_DERAT_SHIFT		(63-33)
#define PPC970_SPR_HID4_DIS_DCTPC_MASK		_BITFIELD64B(35,0x3)
#define PPC970_SPR_HID4_DIS_DCTPC_SHIFT		(63-35)
#define PPC970_SPR_HID4_DIS_DCTPG			_ONEBIT64B(36)
#define PPC970_SPR_HID4_DIS_DCSET_MASK		_BITFIELD64B(38,0x3)
#define PPC970_SPR_HID4_DIS_DCSET_SHIFT		(63-38)
#define PPC970_SPR_HID4_DIS_DCPC_MASK		_BITFIELD64B(40,0x3)
#define PPC970_SPR_HID4_DIS_DCPC_SHIFT		(63-40)
#define PPC970_SPR_HID4_DIS_DCPC			_ONEBIT64B(41)
#define PPC970_SPR_HID4_DIS_DCRTPC_MASK		_BITFIELD64B(43,0x3)
#define PPC970_SPR_HID4_DIS_DCRTPC_SHIFT	(63-43)
#define PPC970_SPR_HID4_DIS_TLBPC_MASK		_BITFIELD64B(47,0xf)
#define PPC970_SPR_HID4_DIS_TLBPC_SHIFT		(63-47)
#define PPC970_SPR_HID4_DIS_TLBPG			_ONEBIT64B(48)
#define PPC970_SPR_HID4_DIS_TLBSET_MASK		_BITFIELD64B(52,0xf)
#define PPC970_SPR_HID4_DIS_TLBSET_SHIFT	(63-52)
#define PPC970_SPR_HID4_DIS_SLBPC			_ONEBIT64B(53)
#define PPC970_SPR_HID4_DIS_SLBPG			_ONEBIT64B(54)
#define PPC970_SPR_HID4_MCK_INJ				_ONEBIT64B(55)
#define PPC970_SPR_HID4_DIS_STFWD			_ONEBIT64B(56)
#define PPC970_SPR_HID4_LPES0				_ONEBIT64B(57)
#define PPC970_SPR_HID4_RMLR_0_MASK			_BITFIELD64B(58,0x1)
#define PPC970_SPR_HID4_RMLR_0_SHIFT		(63-58)
#define PPC970_SPR_HID4_DIS_SPLARX			_ONEBIT64B(60)
#define PPC970_SPR_HID4_LG_PG_DIS			_ONEBIT64B(61)
#define PPC970_SPR_HID4_LPID_0_1_MASK		_BITFIELD64B(63,0x3)
#define PPC970_SPR_HID4_LPID_0_1_SHIFT		(63-63)

/*
 * HID5
 */
#define PPC970_SPR_HID5_HRMOR_0_15_MASK		_BITFIELD64B(47,0xffff)
#define PPC970_SPR_HID5_HRMOR_0_15_SHIFT	(63-47)
#define PPC970_SPR_HID5_DC_MCK				_ONEBIT64B(50)
#define PPC970_SPR_HID5_DIS_PWRSAVE			_ONEBIT64B(51)
#define PPC970_SPR_HID5_FORCE_G				_ONEBIT64B(52)
#define PPC970_SPR_HID5_DC_REPL				_ONEBIT64B(53)
#define PPC970_SPR_HID5_HWR_STMS			_ONEBIT64B(54)
#define PPC970_SPR_HID5_DST_NOOP			_ONEBIT64B(55)
#define PPC970_SPR_HID5_DCBZ_SIZE			_ONEBIT64B(56)
#define PPC970_SPR_HID5_DCBZ32_ILL			_ONEBIT64B(57)
#define PPC970_SPR_HID5_TLB_MAP				_ONEBIT64B(58)
#define PPC970_SPR_HID5_LMQ_PORT			_ONEBIT64B(59)
#define PPC970_SPR_HID5_LMQ_SIZE0			_ONEBIT64B(60)
#define PPC970_SPR_HID5_TCH_NOP				_ONEBIT64B(62)
#define PPC970_SPR_HID5_LMQ_SIZE1			_ONEBIT64B(63)


#endif

/* __SRCVERSION("970cpu.h $Rev: 153052 $"); */
