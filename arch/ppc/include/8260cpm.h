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
 *  ppc/8260cmp.h
 *
 * Registers specific to the CMP of Motorola PPC 8xx chip
 *

 */

#ifndef __PPC_8260CMP_H_INCLUDED
#define __PPC_8260CMP_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

/*
*** CPM Command Register
*/
#define	PPC8260CPM_CPCR_RST					_ONEBIT32B(0)
#define	PPC8260CPM_CPCR_FLG					_ONEBIT32B(15)
/* PAGE */
#define	PPC8260CPM_CPCR_PAGE_FCC1			_BITFIELD32B(5, 0x04)
#define	PPC8260CPM_CPCR_PAGE_FCC2			_BITFIELD32B(5, 0x05)
#define	PPC8260CPM_CPCR_PAGE_FCC3			_BITFIELD32B(5, 0x06)
#define	PPC8260CPM_CPCR_PAGE_SCC1			_BITFIELD32B(5, 0x00)
#define	PPC8260CPM_CPCR_PAGE_SCC2			_BITFIELD32B(5, 0x01)
#define	PPC8260CPM_CPCR_PAGE_SCC3			_BITFIELD32B(5, 0x02)
#define	PPC8260CPM_CPCR_PAGE_SCC4			_BITFIELD32B(5, 0x03)
#define	PPC8260CPM_CPCR_PAGE_SMC1			_BITFIELD32B(5, 0x07)
#define	PPC8260CPM_CPCR_PAGE_SMC2			_BITFIELD32B(5, 0x08)
#define	PPC8260CPM_CPCR_PAGE_RAND			_BITFIELD32B(5, 0x0a)
#define	PPC8260CPM_CPCR_PAGE_SPI 			_BITFIELD32B(5, 0x09)
#define	PPC8260CPM_CPCR_PAGE_I2C 			_BITFIELD32B(5, 0x0a)
#define	PPC8260CPM_CPCR_PAGE_TIMER			_BITFIELD32B(5, 0x0a)
#define	PPC8260CPM_CPCR_PAGE_MCC1			_BITFIELD32B(5, 0x07)
#define	PPC8260CPM_CPCR_PAGE_MCC2			_BITFIELD32B(5, 0x08)
#define	PPC8260CPM_CPCR_PAGE_IDMA1			_BITFIELD32B(5, 0x07)
#define	PPC8260CPM_CPCR_PAGE_IDMA2			_BITFIELD32B(5, 0x08)
#define	PPC8260CPM_CPCR_PAGE_IDMA3			_BITFIELD32B(5, 0x09)
/* SBC: subblock code */
#define	PPC8260CPM_CPCR_SBC_FCC1			_BITFIELD32B(10, 0x10)
#define	PPC8260CPM_CPCR_SBC_FCC2			_BITFIELD32B(10, 0x11)
#define	PPC8260CPM_CPCR_SBC_FCC3			_BITFIELD32B(10, 0x12)
#define	PPC8260CPM_CPCR_SBC_SCC1			_BITFIELD32B(10, 0x04)
#define	PPC8260CPM_CPCR_SBC_SCC2			_BITFIELD32B(10, 0x05)
#define	PPC8260CPM_CPCR_SBC_SCC3			_BITFIELD32B(10, 0x06)
#define	PPC8260CPM_CPCR_SBC_SCC4			_BITFIELD32B(10, 0x07)
#define	PPC8260CPM_CPCR_SBC_SMC1			_BITFIELD32B(10, 0x08)
#define	PPC8260CPM_CPCR_SBC_SMC2			_BITFIELD32B(10, 0x09)
#define	PPC8260CPM_CPCR_SBC_RAND			_BITFIELD32B(10, 0x0e)
#define	PPC8260CPM_CPCR_SBC_SPI 			_BITFIELD32B(10, 0x0a)
#define	PPC8260CPM_CPCR_SBC_I2C 			_BITFIELD32B(10, 0x0b)
#define	PPC8260CPM_CPCR_SBC_TIMER			_BITFIELD32B(10, 0x0f)
#define	PPC8260CPM_CPCR_SBC_MCC1			_BITFIELD32B(10, 0x1c)
#define	PPC8260CPM_CPCR_SBC_MCC2			_BITFIELD32B(10, 0x1d)
#define	PPC8260CPM_CPCR_SBC_IDMA1			_BITFIELD32B(10, 0x14)
#define	PPC8260CPM_CPCR_SBC_IDMA2			_BITFIELD32B(10, 0x15)
#define	PPC8260CPM_CPCR_SBC_IDMA3			_BITFIELD32B(10, 0x16)
#define	PPC8260CPM_CPCR_SBC_IDMA4			_BITFIELD32B(10, 0x17)
#define	PPC8260CPM_CPCR_SBC_IDMA4			_BITFIELD32B(10, 0x17)
/* MCN */
#define PPC8260CPM_CPCR_MCN_HDLC			_BITFIELD32B(25, 0x0)
#define PPC8260CPM_CPCR_MCN_ATM				_BITFIELD32B(25, 0xa)
#define PPC8260CPM_CPCR_MCN_ETH				_BITFIELD32B(25, 0xc)
#define PPC8260CPM_CPCR_MCN_TRN				_BITFIELD32B(25, 0xf)
/* OPCODE */
#define	PPC8260CPM_CPCR_INITRXTX			_BITFIELD32B(31, 0x0)
#define	PPC8260CPM_CPCR_INITRX				_BITFIELD32B(31, 0x1)
#define	PPC8260CPM_CPCR_INITTX				_BITFIELD32B(31, 0x2)
#define	PPC8260CPM_CPCR_ENTERHUNT			_BITFIELD32B(31, 0x3)
#define	PPC8260CPM_CPCR_STOPTX				_BITFIELD32B(31, 0x4)
#define	PPC8260CPM_CPCR_STOPTXGRACE			_BITFIELD32B(31, 0x5)
#define	PPC8260CPM_CPCR_RESTARTTX			_BITFIELD32B(31, 0x6)
#define	PPC8260CPM_CPCR_CLOSERXBD			_BITFIELD32B(31, 0x7)
#define	PPC8260CPM_CPCR_GADDR				_BITFIELD32B(31, 0x8)
#define	PPC8260CPM_CPCR_SETTIMER			_BITFIELD32B(31, 0x8)
#define	PPC8260CPM_CPCR_GCITIMEOUT			_BITFIELD32B(31, 0x9)
#define	PPC8260CPM_CPCR_STARTDMA			_BITFIELD32B(31, 0x9)
#define	PPC8260CPM_CPCR_MCCSTOPRX			_BITFIELD32B(31, 0x9)
#define	PPC8260CPM_CPCR_RESETBCS			_BITFIELD32B(31, 0xa)
#define	PPC8260CPM_CPCR_ATMTXCOM			_BITFIELD32B(31, 0xa)
#define	PPC8260CPM_CPCR_GCIABORT			_BITFIELD32B(31, 0xa)
#define	PPC8260CPM_CPCR_STOPIDMA			_BITFIELD32B(31, 0xb)
#define	PPC8260CPM_CPCR_RANDOMNUM			_BITFIELD32B(31, 0xc)

/*
 *** CPM Multiplexing
 */
/* CMXSMR */
#define	PPC8260CPM_CMXSMR_SMC1				_ONEBIT8B(0)
#define	PPC8260CPM_CMXSMR_SMC1CS_M			_BITFIELD8B(3, 0x3)
#define	PPC8260CPM_CMXSMR_SMC1CS_BRG1		_BITFIELD8B(3, 0x0)
#define	PPC8260CPM_CMXSMR_SMC1CS_BRG7		_BITFIELD8B(3, 0x1)
#define	PPC8260CPM_CMXSMR_SMC1CS_CLK7		_BITFIELD8B(3, 0x2)
#define	PPC8260CPM_CMXSMR_SMC1CS_CLK9		_BITFIELD8B(3, 0x3)
#define	PPC8260CPM_CMXSMR_SMC2				_ONEBIT8B(4)
#define	PPC8260CPM_CMXSMR_SMC2CS_M			_BITFIELD8B(7, 0x3)
#define	PPC8260CPM_CMXSMR_SMC2CS_BRG2		_BITFIELD8B(7, 0x0)
#define	PPC8260CPM_CMXSMR_SMC2CS_BRG8		_BITFIELD8B(7, 0x1)
#define	PPC8260CPM_CMXSMR_SMC2CS_CLK19		_BITFIELD8B(7, 0x2)
#define	PPC8260CPM_CMXSMR_SMC2CS_CLK20		_BITFIELD8B(7, 0x3)

/* CMXSCR */
#define	PPC8260CPM_CMXSCR_GR1				_ONEBIT32B(0)
#define	PPC8260CPM_CMXSCR_SC1				_ONEBIT32B(1)
#define	PPC8260CPM_CMXSCR_RS1CS_M			_BITFIELD32B(4, 0x7)
#define	PPC8260CPM_CMXSCR_RS1CS(x)			_BITFIELD32B(4, x)
#define	PPC8260CPM_CMXSCR_RS1CS_BRG1		_BITFIELD32B(4, 0)
#define	PPC8260CPM_CMXSCR_RS1CS_BRG2		_BITFIELD32B(4, 1)
#define	PPC8260CPM_CMXSCR_RS1CS_BRG3		_BITFIELD32B(4, 2)
#define	PPC8260CPM_CMXSCR_RS1CS_BRG4		_BITFIELD32B(4, 3)
#define	PPC8260CPM_CMXSCR_RS1CS_CLK11		_BITFIELD32B(4, 4)
#define	PPC8260CPM_CMXSCR_RS1CS_CLK12		_BITFIELD32B(4, 5)
#define	PPC8260CPM_CMXSCR_RS1CS_CLK3		_BITFIELD32B(4, 6)
#define	PPC8260CPM_CMXSCR_RS1CS_CLK4		_BITFIELD32B(4, 7)
#define	PPC8260CPM_CMXSCR_TS1CS_M			_BITFIELD32B(7, 0x7)
#define	PPC8260CPM_CMXSCR_TS1CS(x)			_BITFIELD32B(7, x)
#define	PPC8260CPM_CMXSCR_TS1CS_BRG1		_BITFIELD32B(7, 0)
#define	PPC8260CPM_CMXSCR_TS1CS_BRG2		_BITFIELD32B(7, 1)
#define	PPC8260CPM_CMXSCR_TS1CS_BRG3		_BITFIELD32B(7, 2)
#define	PPC8260CPM_CMXSCR_TS1CS_BRG4		_BITFIELD32B(7, 3)
#define	PPC8260CPM_CMXSCR_TS1CS_CLK11		_BITFIELD32B(7, 4)
#define	PPC8260CPM_CMXSCR_TS1CS_CLK12		_BITFIELD32B(7, 5)
#define	PPC8260CPM_CMXSCR_TS1CS_CLK3		_BITFIELD32B(7, 6)
#define	PPC8260CPM_CMXSCR_TS1CS_CLK4		_BITFIELD32B(7, 7)
#define	PPC8260CPM_CMXSCR_GR2				_ONEBIT32B(8)
#define	PPC8260CPM_CMXSCR_SC2				_ONEBIT32B(9)
#define	PPC8260CPM_CMXSCR_RS2CS_M			_BITFIELD32B(12, 0x7)
#define	PPC8260CPM_CMXSCR_RS2CS(x)			_BITFIELD32B(12, x)
#define	PPC8260CPM_CMXSCR_RS2CS_BRG1		_BITFIELD32B(12, 0)
#define	PPC8260CPM_CMXSCR_RS2CS_BRG2		_BITFIELD32B(12, 1)
#define	PPC8260CPM_CMXSCR_RS2CS_BRG3		_BITFIELD32B(12, 2)
#define	PPC8260CPM_CMXSCR_RS2CS_BRG4		_BITFIELD32B(12, 3)
#define	PPC8260CPM_CMXSCR_RS2CS_CLK11		_BITFIELD32B(12, 4)
#define	PPC8260CPM_CMXSCR_RS2CS_CLK12		_BITFIELD32B(12, 5)
#define	PPC8260CPM_CMXSCR_RS2CS_CLK3		_BITFIELD32B(12, 6)
#define	PPC8260CPM_CMXSCR_RS2CS_CLK4		_BITFIELD32B(12, 7)
#define	PPC8260CPM_CMXSCR_TS2CS_M			_BITFIELD32B(15, 0x7)
#define	PPC8260CPM_CMXSCR_TS2CS(x)			_BITFIELD32B(15, x)
#define	PPC8260CPM_CMXSCR_TS2CS_BRG1		_BITFIELD32B(15, 0)
#define	PPC8260CPM_CMXSCR_TS2CS_BRG2		_BITFIELD32B(15, 1)
#define	PPC8260CPM_CMXSCR_TS2CS_BRG3		_BITFIELD32B(15, 2)
#define	PPC8260CPM_CMXSCR_TS2CS_BRG4		_BITFIELD32B(15, 3)
#define	PPC8260CPM_CMXSCR_TS2CS_CLK11		_BITFIELD32B(15, 4)
#define	PPC8260CPM_CMXSCR_TS2CS_CLK12		_BITFIELD32B(15, 5)
#define	PPC8260CPM_CMXSCR_TS2CS_CLK3		_BITFIELD32B(15, 6)
#define	PPC8260CPM_CMXSCR_TS2CS_CLK4		_BITFIELD32B(15, 7)
#define	PPC8260CPM_CMXSCR_GR3				_ONEBIT32B(16)
#define	PPC8260CPM_CMXSCR_SC3				_ONEBIT32B(17)
#define	PPC8260CPM_CMXSCR_RS3CS_M			_BITFIELD32B(20, 0x7)
#define	PPC8260CPM_CMXSCR_RS3CS(x)			_BITFIELD32B(20, x)
#define	PPC8260CPM_CMXSCR_RS3CS_BRG1		_BITFIELD32B(20, 0)
#define	PPC8260CPM_CMXSCR_RS3CS_BRG2		_BITFIELD32B(20, 1)
#define	PPC8260CPM_CMXSCR_RS3CS_BRG3		_BITFIELD32B(20, 2)
#define	PPC8260CPM_CMXSCR_RS3CS_BRG4		_BITFIELD32B(20, 3)
#define	PPC8260CPM_CMXSCR_RS3CS_CLK5		_BITFIELD32B(20, 4)
#define	PPC8260CPM_CMXSCR_RS3CS_CLK6		_BITFIELD32B(20, 5)
#define	PPC8260CPM_CMXSCR_RS3CS_CLK7		_BITFIELD32B(20, 6)
#define	PPC8260CPM_CMXSCR_RS3CS_CLK8		_BITFIELD32B(20, 7)
#define	PPC8260CPM_CMXSCR_TS3CS_M			_BITFIELD32B(23, 0x7)
#define	PPC8260CPM_CMXSCR_TS3CS(x)			_BITFIELD32B(23, x)
#define	PPC8260CPM_CMXSCR_TS3CS_BRG1		_BITFIELD32B(23, 0)
#define	PPC8260CPM_CMXSCR_TS3CS_BRG2		_BITFIELD32B(23, 1)
#define	PPC8260CPM_CMXSCR_TS3CS_BRG3		_BITFIELD32B(23, 2)
#define	PPC8260CPM_CMXSCR_TS3CS_BRG4		_BITFIELD32B(23, 3)
#define	PPC8260CPM_CMXSCR_TS3CS_CLK5		_BITFIELD32B(23, 4)
#define	PPC8260CPM_CMXSCR_TS3CS_CLK6		_BITFIELD32B(23, 5)
#define	PPC8260CPM_CMXSCR_TS3CS_CLK7		_BITFIELD32B(23, 6)
#define	PPC8260CPM_CMXSCR_TS3CS_CLK8		_BITFIELD32B(23, 7)
#define	PPC8260CPM_CMXSCR_GR4				_ONEBIT32B(24)
#define	PPC8260CPM_CMXSCR_SC4				_ONEBIT32B(25)
#define	PPC8260CPM_CMXSCR_RS4CS_M			_BITFIELD32B(28, 0x7)
#define	PPC8260CPM_CMXSCR_RS4CS(x)			_BITFIELD32B(28, x)
#define	PPC8260CPM_CMXSCR_RS4CS_BRG1		_BITFIELD32B(28, 0)
#define	PPC8260CPM_CMXSCR_RS4CS_BRG2		_BITFIELD32B(28, 1)
#define	PPC8260CPM_CMXSCR_RS4CS_BRG3		_BITFIELD32B(28, 2)
#define	PPC8260CPM_CMXSCR_RS4CS_BRG4		_BITFIELD32B(28, 3)
#define	PPC8260CPM_CMXSCR_RS4CS_CLK5		_BITFIELD32B(28, 4)
#define	PPC8260CPM_CMXSCR_RS4CS_CLK6		_BITFIELD32B(28, 5)
#define	PPC8260CPM_CMXSCR_RS4CS_CLK7		_BITFIELD32B(28, 6)
#define	PPC8260CPM_CMXSCR_RS4CS_CLK8		_BITFIELD32B(28, 7)
#define	PPC8260CPM_CMXSCR_TS4CS_M			_BITFIELD32B(31, 0x7)
#define	PPC8260CPM_CMXSCR_TS4CS(x)			_BITFIELD32B(31, x)
#define	PPC8260CPM_CMXSCR_TS4CS_BRG1		_BITFIELD32B(31, 0)
#define	PPC8260CPM_CMXSCR_TS4CS_BRG2		_BITFIELD32B(31, 1)
#define	PPC8260CPM_CMXSCR_TS4CS_BRG3		_BITFIELD32B(31, 2)
#define	PPC8260CPM_CMXSCR_TS4CS_BRG4		_BITFIELD32B(31, 3)
#define	PPC8260CPM_CMXSCR_TS4CS_CLK5		_BITFIELD32B(31, 4)
#define	PPC8260CPM_CMXSCR_TS4CS_CLK6		_BITFIELD32B(31, 5)
#define	PPC8260CPM_CMXSCR_TS4CS_CLK7		_BITFIELD32B(31, 6)
#define	PPC8260CPM_CMXSCR_TS4CS_CLK8		_BITFIELD32B(31, 7)

/* CMXFCR */
#define	PPC8260CPM_CMXFCR_FC1				_ONEBIT32B(1)
#define	PPC8260CPM_CMXFCR_RF1CS_M			_BITFIELD32B(4, 0x7)
#define	PPC8260CPM_CMXFCR_RF1CS(x)			_BITFIELD32B(4, x)
#define	PPC8260CPM_CMXFCR_RF1CS_BRG5		_BITFIELD32B(4, 0)
#define	PPC8260CPM_CMXFCR_RF1CS_BRG6		_BITFIELD32B(4, 1)
#define	PPC8260CPM_CMXFCR_RF1CS_BRG7		_BITFIELD32B(4, 2)
#define	PPC8260CPM_CMXFCR_RF1CS_BRG8		_BITFIELD32B(4, 3)
#define	PPC8260CPM_CMXFCR_RF1CS_CLK9		_BITFIELD32B(4, 4)
#define	PPC8260CPM_CMXFCR_RF1CS_CLK10		_BITFIELD32B(4, 5)
#define	PPC8260CPM_CMXFCR_RF1CS_CLK11		_BITFIELD32B(4, 6)
#define	PPC8260CPM_CMXFCR_RF1CS_CLK12		_BITFIELD32B(4, 7)
#define	PPC8260CPM_CMXFCR_TF1CS_M			_BITFIELD32B(7, 0x7)
#define	PPC8260CPM_CMXFCR_TF1CS(x)			_BITFIELD32B(7, x)
#define	PPC8260CPM_CMXFCR_TF1CS_BRG5		_BITFIELD32B(7, 0)
#define	PPC8260CPM_CMXFCR_TF1CS_BRG6		_BITFIELD32B(7, 1)
#define	PPC8260CPM_CMXFCR_TF1CS_BRG7		_BITFIELD32B(7, 2)
#define	PPC8260CPM_CMXFCR_TF1CS_BRG8		_BITFIELD32B(7, 3)
#define	PPC8260CPM_CMXFCR_TF1CS_CLK9		_BITFIELD32B(7, 4)
#define	PPC8260CPM_CMXFCR_TF1CS_CLK10		_BITFIELD32B(7, 5)
#define	PPC8260CPM_CMXFCR_TF1CS_CLK11		_BITFIELD32B(7, 6)
#define	PPC8260CPM_CMXFCR_TF1CS_CLK12		_BITFIELD32B(7, 7)
#define	PPC8260CPM_CMXFCR_FC2				_ONEBIT32B(9)
#define	PPC8260CPM_CMXFCR_RF2CS_M			_BITFIELD32B(12, 0x7)
#define	PPC8260CPM_CMXFCR_RF2CS(x)			_BITFIELD32B(12, x)
#define	PPC8260CPM_CMXFCR_RF2CS_BRG5		_BITFIELD32B(12, 0)
#define	PPC8260CPM_CMXFCR_RF2CS_BRG6		_BITFIELD32B(12, 1)
#define	PPC8260CPM_CMXFCR_RF2CS_BRG7		_BITFIELD32B(12, 2)
#define	PPC8260CPM_CMXFCR_RF2CS_BRG8		_BITFIELD32B(12, 3)
#define	PPC8260CPM_CMXFCR_RF2CS_CLK13		_BITFIELD32B(12, 4)
#define	PPC8260CPM_CMXFCR_RF2CS_CLK14		_BITFIELD32B(12, 5)
#define	PPC8260CPM_CMXFCR_RF2CS_CLK15		_BITFIELD32B(12, 6)
#define	PPC8260CPM_CMXFCR_RF2CS_CLK16		_BITFIELD32B(12, 7)
#define	PPC8260CPM_CMXFCR_TF2CS_M			_BITFIELD32B(15, 0x7)
#define	PPC8260CPM_CMXFCR_TF2CS(x)			_BITFIELD32B(15, x)
#define	PPC8260CPM_CMXFCR_TF2CS_BRG5		_BITFIELD32B(15, 0)
#define	PPC8260CPM_CMXFCR_TF2CS_BRG6		_BITFIELD32B(15, 1)
#define	PPC8260CPM_CMXFCR_TF2CS_BRG7		_BITFIELD32B(15, 2)
#define	PPC8260CPM_CMXFCR_TF2CS_BRG8		_BITFIELD32B(15, 3)
#define	PPC8260CPM_CMXFCR_TF2CS_CLK13		_BITFIELD32B(15, 4)
#define	PPC8260CPM_CMXFCR_TF2CS_CLK14		_BITFIELD32B(15, 5)
#define	PPC8260CPM_CMXFCR_TF2CS_CLK15		_BITFIELD32B(15, 6)
#define	PPC8260CPM_CMXFCR_TF2CS_CLK16		_BITFIELD32B(15, 7)
#define	PPC8260CPM_CMXFCR_FC3				_ONEBIT32B(17)
#define	PPC8260CPM_CMXFCR_RF3CS_M			_BITFIELD32B(20, 0x7)
#define	PPC8260CPM_CMXFCR_RF3CS(x)			_BITFIELD32B(20, x)
#define	PPC8260CPM_CMXFCR_RF3CS_BRG5		_BITFIELD32B(20, 0)
#define	PPC8260CPM_CMXFCR_RF3CS_BRG6		_BITFIELD32B(20, 1)
#define	PPC8260CPM_CMXFCR_RF3CS_BRG7		_BITFIELD32B(20, 2)
#define	PPC8260CPM_CMXFCR_RF3CS_BRG8		_BITFIELD32B(20, 3)
#define	PPC8260CPM_CMXFCR_RF3CS_CLK13		_BITFIELD32B(20, 4)
#define	PPC8260CPM_CMXFCR_RF3CS_CLK14		_BITFIELD32B(20, 5)
#define	PPC8260CPM_CMXFCR_RF3CS_CLK15		_BITFIELD32B(20, 6)
#define	PPC8260CPM_CMXFCR_RF3CS_CLK16		_BITFIELD32B(20, 7)
#define	PPC8260CPM_CMXFCR_TF3CS_M			_BITFIELD32B(23, 0x7)
#define	PPC8260CPM_CMXFCR_TF3CS(x)			_BITFIELD32B(23, x)
#define	PPC8260CPM_CMXFCR_TF3CS_BRG5		_BITFIELD32B(23, 0)
#define	PPC8260CPM_CMXFCR_TF3CS_BRG6		_BITFIELD32B(23, 1)
#define	PPC8260CPM_CMXFCR_TF3CS_BRG7		_BITFIELD32B(23, 2)
#define	PPC8260CPM_CMXFCR_TF3CS_BRG8		_BITFIELD32B(23, 3)
#define	PPC8260CPM_CMXFCR_TF3CS_CLK13		_BITFIELD32B(23, 4)
#define	PPC8260CPM_CMXFCR_TF3CS_CLK14		_BITFIELD32B(23, 5)
#define	PPC8260CPM_CMXFCR_TF3CS_CLK15		_BITFIELD32B(23, 6)
#define	PPC8260CPM_CMXFCR_TF3CS_CLK16		_BITFIELD32B(23, 7)

/*
*** Dual port RAM inside CMP
*/

/* Offset from dual port RAM BASE (0 offset from IMMR base)*/
#define	PPC8260CPM_DPRAM_BDC1_S				0x0
#define	PPC8260CPM_DPRAM_BDC1_E				0x07ff
#define	PPC8260CPM_DPRAM_BDC2_S				0x0800
#define	PPC8260CPM_DPRAM_BDC2_E				0x0fff
#define	PPC8260CPM_DPRAM_BDC3_S				0x1000
#define	PPC8260CPM_DPRAM_BDC3_E				0x17ff
#define	PPC8260CPM_DPRAM_BDC4_S				0x1800
#define	PPC8260CPM_DPRAM_BDC4_E				0x1fff
#define	PPC8260CPM_DPRAM_BDC5_S				0x2000
#define	PPC8260CPM_DPRAM_BDC5_E				0x27ff
#define	PPC8260CPM_DPRAM_BDC6_S				0x2800
#define	PPC8260CPM_DPRAM_BDC6_E				0x2fff
#define	PPC8260CPM_DPRAM_BD7_S				0x3000
#define	PPC8260CPM_DPRAM_BD7_E				0x37ff
#define	PPC8260CPM_DPRAM_BD8_S				0x3800
#define	PPC8260CPM_DPRAM_BD8_E				0x3fff
#define	PPC8260CPM_DPRAM_PARA9_S			0x8000
#define	PPC8260CPM_DPRAM_PARA9_E			0x87ff
#define	PPC8260CPM_DPRAM_PARA10_S			0x8800
#define	PPC8260CPM_DPRAM_PARA10_E			0x8fff
#define	PPC8260CPM_DPRAM_FCCDATA11_S		0xb000
#define	PPC8260CPM_DPRAM_FCCDATA11_E		0xb7ff
#define	PPC8260CPM_DPRAM_FCCDATA12_S		0xb800
#define	PPC8260CPM_DPRAM_FCCDATA12_E		0xbfff

/*
 *** Parameter RAM
 */

/* Parameter RAM MAP */
/* Offset from DPRAM_BASE */
#define	PPC8260CPM_DPRAMPARA_SCC1			0x8000
#define	PPC8260CPM_DPRAMPARA_SCC2			0x8100
#define	PPC8260CPM_DPRAMPARA_SCC3			0x8200
#define	PPC8260CPM_DPRAMPARA_SCC4			0x8300
#define	PPC8260CPM_DPRAMPARA_FCC1			0x8400
#define	PPC8260CPM_DPRAMPARA_FCC2			0x8500
#define	PPC8260CPM_DPRAMPARA_FCC3			0x8600
#define	PPC8260CPM_DPRAMPARA_MCC1			0x8700
#define	PPC8260CPM_DPRAMPARA_SMC1_BASE		0x87fc
#define	PPC8260CPM_DPRAMPARA_DMA1_BASE		0x87fe
#define	PPC8260CPM_DPRAMPARA_MCC2			0x8800
#define	PPC8260CPM_DPRAMPARA_SMC2_BASE		0x88fc
#define	PPC8260CPM_DPRAMPARA_DMA2_BASE		0x88fe
#define	PPC8260CPM_DPRAMPARA_SPI_BASE		0x89fc
#define	PPC8260CPM_DPRAMPARA_DMA3_BASE		0x89fe
#define	PPC8260CPM_DPRAMPARA_TIMERS			0x8ae0
#define	PPC8260CPM_DPRAMPARA_REV_NUM		0x8af0
#define	PPC8260CPM_DPRAMPARA_RAND			0x8af8
#define	PPC8260CPM_DPRAMPARA_FC_BASE		0x8afc
#define	PPC8260CPM_DPRAMPARA_DMA4_BASE		0x8afe

/*
 * Parameter RAM MAP for SMC and SCC
 */

/* common for SMC and SCC */
#define	PPC8260CPM_PARARAM_SCCSMC_RBASE		0x0
#define	PPC8260CPM_PARARAM_SCCSMC_TBASE		0x2
#define	PPC8260CPM_PARARAM_SCCSMC_RFCR		0x4
#define	PPC8260CPM_PARARAM_SCCSMC_TFCR		0x5
#define	PPC8260CPM_PARARAM_SCCSMC_MRBLR		0x6
#define	PPC8260CPM_PARARAM_SCCSMC_RSTATE	0x8
#define	PPC8260CPM_PARARAM_SCCSMC_RBPTR		0x10
#define	PPC8260CPM_PARARAM_SCCSMC_TSTATE	0x18
#define	PPC8260CPM_PARARAM_SCCSMC_TBPTR		0x20

/* Parameter RAM MAP for SMC */
/* Offset from specific controller ParaRAM base */
/* SMC common */
#define	PPC8260CPM_PARARAM_SMC_MAXIDL		0x28
#define	PPC8260CPM_PARARAM_SMC_IDLC			0x2a
#define	PPC8260CPM_PARARAM_SMC_BRKLN		0x2c
#define	PPC8260CPM_PARARAM_SMC_BRKEC		0x2e
#define	PPC8260CPM_PARARAM_SMC_BRKCR		0x30
#define	PPC8260CPM_PARARAM_SMC_R_MASK		0x32

/* Parameter RAM MAP for SCC */
/* Offset from specific controller ParaRAM base */
/* SCC common */
#define	PPC8260CPM_PARARAM_SCC_RCRC			0x28
#define	PPC8260CPM_PARARAM_SCC_TCRC			0x2c

/* SCC UART ParaRAM Map */
#define	PPC8260CPM_PARARAM_SCCUART_MAXIDL	0x38
#define	PPC8260CPM_PARARAM_SCCUART_IDLC		0x3a
#define	PPC8260CPM_PARARAM_SCCUART_BRKCR	0x3c
#define	PPC8260CPM_PARARAM_SCCUART_PAREC	0x3e
#define	PPC8260CPM_PARARAM_SCCUART_FRMEC	0x40
#define	PPC8260CPM_PARARAM_SCCUART_NOSEC	0x42
#define	PPC8260CPM_PARARAM_SCCUART_BRKEC 	0x44
#define	PPC8260CPM_PARARAM_SCCUART_BRKLN 	0x46
#define	PPC8260CPM_PARARAM_SCCUART_UADDR1	0x48
#define	PPC8260CPM_PARARAM_SCCUART_UADDR2	0x4a
#define	PPC8260CPM_PARARAM_SCCUART_RTEMP 	0x4c
#define	PPC8260CPM_PARARAM_SCCUART_TOSEQ 	0x4e
#define	PPC8260CPM_PARARAM_SCCUART_CHAR1	0x50
#define	PPC8260CPM_PARARAM_SCCUART_CHAR2	0x52
#define	PPC8260CPM_PARARAM_SCCUART_CHAR3	0x54
#define	PPC8260CPM_PARARAM_SCCUART_CHAR4	0x56
#define	PPC8260CPM_PARARAM_SCCUART_CHAR5	0x58
#define	PPC8260CPM_PARARAM_SCCUART_CHAR6	0x5a
#define	PPC8260CPM_PARARAM_SCCUART_CHAR7	0x5c
#define	PPC8260CPM_PARARAM_SCCUART_CHAR8	0x5e
#define	PPC8260CPM_PARARAM_SCCUART_RCCM    	0x60
#define	PPC8260CPM_PARARAM_SCCUART_RCCR    	0x62
#define	PPC8260CPM_PARARAM_SCCUART_RLBC    	0x64
/* SCC UART control chars */
#define PPC8260CPM_PARARAM_SCCUART_CHAR_E	0x8000
#define PPC8260CPM_PARARAM_SCCUART_CHAR_R	0x4000

/*
 ** Buffer Descriptors
 */

/* Buffer Descriptor size */
#define	PPC8260CPM_BD_SIZE					8
#define	PPC8260CPM_BD_FLG					0
#define	PPC8260CPM_BD_COUNT					2
#define	PPC8260CPM_BD_POINTER				4

/* Buffer Descriptor flags */

/* UART */
/* common for SMC and SCC */
/* Rx */
#define	PPC8260CPM_UART_RXBD_E				_ONEBIT16B(0)
#define	PPC8260CPM_UART_RXBD_W				_ONEBIT16B(2)
#define	PPC8260CPM_UART_RXBD_I				_ONEBIT16B(3)
#define	PPC8260CPM_UART_RXBD_CM				_ONEBIT16B(6)
#define	PPC8260CPM_UART_RXBD_ID				_ONEBIT16B(7)
#define	PPC8260CPM_UART_RXBD_BR				_ONEBIT16B(10)
#define	PPC8260CPM_UART_RXBD_FR				_ONEBIT16B(11)
#define	PPC8260CPM_UART_RXBD_PR				_ONEBIT16B(12)
#define	PPC8260CPM_UART_RXBD_OV				_ONEBIT16B(14)
#define	PPC8260CPM_UART_RXBD_CD				_ONEBIT16B(15)

/* Tx */
#define	PPC8260CPM_UART_TXBD_R				_ONEBIT16B(0)
#define	PPC8260CPM_UART_TXBD_W				_ONEBIT16B(2)
#define	PPC8260CPM_UART_TXBD_I				_ONEBIT16B(3)
#define	PPC8260CPM_UART_TXBD_CM				_ONEBIT16B(6)
#define	PPC8260CPM_UART_TXBD_P				_ONEBIT16B(7)

/* Rx SCC UART BD */
#define	PPC8260CPM_SCCUART_RXBD_A			_ONEBIT16B(5)
#define	PPC8260CPM_SCCUART_RXBD_CM			_ONEBIT16B(6)
#define	PPC8260CPM_SCCUART_RXBD_AM			_ONEBIT16B(8)

/* Tx SCC UART BD*/
#define	PPC8260CPM_SCCUART_TXBD_CR			_ONEBIT16B(4)
#define	PPC8260CPM_SCCUART_TXBD_A			_ONEBIT16B(5)
#define	PPC8260CPM_SCCUART_TXBD_NS			_ONEBIT16B(8)
#define	PPC8260CPM_SCCUART_TXBD_CT			_ONEBIT16B(15)

/*
** Bard Rate Generators (BRG)
*/
#define	PPC8260CPM_BRG_RST 					_ONEBIT32B(14)
#define	PPC8260CPM_BRG_EN 					_ONEBIT32B(15)
#define	PPC8260CPM_BRG_EXTC_M				_BITFIELD32B(17,3)
#define	PPC8260CPM_BRG_EXTC(x)				_BITFIELD32B(17,x)
#define	PPC8260CPM_BRG_ATB 					_ONEBIT32B(18)
#define	PPC8260CPM_BRG_CD(cnt)				_BITFIELD32B(30,cnt)
#define	PPC8260CPM_BRG_DIV16				_ONEBIT32B(31)
#define	PPC8260CPM_BRG_MAXCNT				(1<<12)

/*
*** Serial Management Controllers (SMC)
*/

/* UART Protocal */

/* Mode register SMC UART */
#define	PPC8260CPM_SMCMR_UART_CLENM			_BITFIELD16B(4, 0xf)
#define	PPC8260CPM_SMCMR_UART_CLEN(data,parity,stop) _BITFIELD16B(4, ((data)+(parity)+(stop)))
#define	PPC8260CPM_SMCMR_UART_Sl			_ONEBIT16B(5)
#define	PPC8260CPM_SMCMR_UART_PEN			_ONEBIT16B(6)
#define	PPC8260CPM_SMCMR_UART_PM			_ONEBIT16B(7)
#define	PPC8260CPM_SMCMR_UART_SM_M			_BITFIELD16B(11, 0x3)
#define	PPC8260CPM_SMCMR_UART_SMUART		_BITFIELD16B(11, 0x2)
#define	PPC8260CPM_SMCMR_UART_DM_M			_BITFIELD16B(13, 0x3)
#define	PPC8260CPM_SMCMR_UART_DMNORMAL		_BITFIELD16B(13, 0x0)
#define	PPC8260CPM_SMCMR_UART_DMLOOPBACK	_BITFIELD16B(13, 0x1)
#define	PPC8260CPM_SMCMR_UART_DMECHO		_BITFIELD16B(13, 0x2)
#define	PPC8260CPM_SMCMR_UART_TEN			_ONEBIT16B(14)
#define	PPC8260CPM_SMCMR_UART_REN			_ONEBIT16B(15)

/* Event register SMC UART & Mask register SMC UART */
#define	PPC8260CPM_SMCERMSKR_UART_BRKE		_ONEBIT8B(1)
#define	PPC8260CPM_SMCERMSKR_UART_BRK 		_ONEBIT8B(3)
#define	PPC8260CPM_SMCERMSKR_UART_BSY		_ONEBIT8B(5)
#define	PPC8260CPM_SMCERMSKR_UART_TX  		_ONEBIT8B(6)
#define	PPC8260CPM_SMCERMSKR_UART_RX 		_ONEBIT8B(7)

/*
*** Serial Comunication Controllers (SCC)
*/

/* General SCC MODE Register High */
#define	PPC8260CPM_GSMR_H_GDE				_ONEBIT32B(15)
#define	PPC8260CPM_GSMR_H_TCRC_M			_BITFIELD32B(17, 0x3)
#define	PPC8260CPM_GSMR_H_TCRC16CCITT		_BITFIELD32B(17, 0x0)
#define	PPC8260CPM_GSMR_H_TCRCCRC16			_BITFIELD32B(17, 0x1)
#define	PPC8260CPM_GSMR_H_TCRC32CCITT		_BITFIELD32B(17, 0x2)
#define	PPC8260CPM_GSMR_H_REVD				_ONEBIT32B(18)
#define	PPC8260CPM_GSMR_H_TRX				_ONEBIT32B(19)
#define	PPC8260CPM_GSMR_H_TTX				_ONEBIT32B(20)
#define	PPC8260CPM_GSMR_H_CDP				_ONEBIT32B(21)
#define	PPC8260CPM_GSMR_H_CTSP				_ONEBIT32B(22)
#define	PPC8260CPM_GSMR_H_CDS				_ONEBIT32B(23)
#define	PPC8260CPM_GSMR_H_CTSS				_ONEBIT32B(24)
#define	PPC8260CPM_GSMR_H_TFL				_ONEBIT32B(25)
#define	PPC8260CPM_GSMR_H_RFW				_ONEBIT32B(26)
#define	PPC8260CPM_GSMR_H_TXSY				_ONEBIT32B(27)
#define	PPC8260CPM_GSMR_H_SYNL_M			_BITFIELD32B(29, 0x3)
#define	PPC8260CPM_GSMR_H_SYNL0				_BITFIELD32B(29, 0x0)
#define	PPC8260CPM_GSMR_H_SYNL4				_BITFIELD32B(29, 0x1)
#define	PPC8260CPM_GSMR_H_SYNL8				_BITFIELD32B(29, 0x2)
#define	PPC8260CPM_GSMR_H_SYNL16			_BITFIELD32B(29, 0x3)
#define	PPC8260CPM_GSMR_H_RTSM				_ONEBIT32B(30)
#define	PPC8260CPM_GSMR_H_RSYN				_ONEBIT32B(31)

/* General SCC MODE Register Low */
#define	PPC8260CPM_GSMR_L_EDGE_M			_BITFIELD32B(2, 0x3)
#define	PPC8260CPM_GSMR_L_EDGEBOTH			_BITFIELD32B(2, 0x0)
#define	PPC8260CPM_GSMR_L_EDGEPOS			_BITFIELD32B(2, 0x1)
#define	PPC8260CPM_GSMR_L_EDGENEG			_BITFIELD32B(2, 0x2)
#define	PPC8260CPM_GSMR_L_EDGENO			_BITFIELD32B(2, 0x3)
#define	PPC8260CPM_GSMR_L_TCI				_ONEBIT32B(3)
#define	PPC8260CPM_GSMR_L_TSNC_M			_BITFIELD32B(5, 0x3)
#define	PPC8260CPM_GSMR_L_TSNCINFINITE		_BITFIELD32B(5, 0x0)
#define	PPC8260CPM_GSMR_L_TSNC14 			_BITFIELD32B(5, 0x1)
#define	PPC8260CPM_GSMR_L_TSNC4  			_BITFIELD32B(5, 0x2)
#define	PPC8260CPM_GSMR_L_TSNC3 			_BITFIELD32B(5, 0x3)
#define	PPC8260CPM_GSMR_L_RINV				_ONEBIT32B(6)
#define	PPC8260CPM_GSMR_L_TINV				_ONEBIT32B(7)
#define	PPC8260CPM_GSMR_L_TPL_M				_BITFIELD32B(10, 0x7)
#define	PPC8260CPM_GSMR_L_TPLNO				_BITFIELD32B(10, 0x0)
#define	PPC8260CPM_GSMR_L_TPL8				_BITFIELD32B(10, 0x1)
#define	PPC8260CPM_GSMR_L_TPL16				_BITFIELD32B(10, 0x2)
#define	PPC8260CPM_GSMR_L_TPL32				_BITFIELD32B(10, 0x3)
#define	PPC8260CPM_GSMR_L_TPL48				_BITFIELD32B(10, 0x4)
#define	PPC8260CPM_GSMR_L_TPL64				_BITFIELD32B(10, 0x5)
#define	PPC8260CPM_GSMR_L_TPL128			_BITFIELD32B(10, 0x6)
#define	PPC8260CPM_GSMR_L_TPP_M				_BITFIELD32B(12, 0x3)
#define	PPC8260CPM_GSMR_L_TPP0				_BITFIELD32B(12, 0x0)
#define	PPC8260CPM_GSMR_L_TPP10				_BITFIELD32B(12, 0x1)
#define	PPC8260CPM_GSMR_L_TPP01				_BITFIELD32B(12, 0x2)
#define	PPC8260CPM_GSMR_L_TPP1				_BITFIELD32B(12, 0x3)
#define	PPC8260CPM_GSMR_L_TEND				_ONEBIT32B(13)
#define	PPC8260CPM_GSMR_L_TDCR_M			_BITFIELD32B(15, 0x3)
#define	PPC8260CPM_GSMR_L_TDCR1				_BITFIELD32B(15, 0x0)
#define	PPC8260CPM_GSMR_L_TDCR8				_BITFIELD32B(15, 0x1)
#define	PPC8260CPM_GSMR_L_TDCR16			_BITFIELD32B(15, 0x2)
#define	PPC8260CPM_GSMR_L_TDCR32			_BITFIELD32B(15, 0x3)
#define	PPC8260CPM_GSMR_L_RDCR_M			_BITFIELD32B(17, 0x3)
#define	PPC8260CPM_GSMR_L_RDCR1				_BITFIELD32B(17, 0x0)
#define	PPC8260CPM_GSMR_L_RDCR8				_BITFIELD32B(17, 0x1)
#define	PPC8260CPM_GSMR_L_RDCR16			_BITFIELD32B(17, 0x2)
#define	PPC8260CPM_GSMR_L_RDCR32			_BITFIELD32B(17, 0x3)
#define	PPC8260CPM_GSMR_L_RENC_M			_BITFIELD32B(20, 0x7)
#define	PPC8260CPM_GSMR_L_RENCNRZ			_BITFIELD32B(20, 0x0)
#define	PPC8260CPM_GSMR_L_RENCNRZIM			_BITFIELD32B(20, 0x1)
#define	PPC8260CPM_GSMR_L_RENCFM0			_BITFIELD32B(20, 0x2)
#define	PPC8260CPM_GSMR_L_RENCMANCHESTER	_BITFIELD32B(20, 0x4)
#define	PPC8260CPM_GSMR_L_RENCDMANCHESTER	_BITFIELD32B(20, 0x6)
#define	PPC8260CPM_GSMR_L_TENC_M			_BITFIELD32B(23, 0x7)
#define	PPC8260CPM_GSMR_L_TENCNRZ			_BITFIELD32B(23, 0x0)
#define	PPC8260CPM_GSMR_L_TENCNRZIM			_BITFIELD32B(23, 0x1)
#define	PPC8260CPM_GSMR_L_TENCFM0			_BITFIELD32B(23, 0x2)
#define	PPC8260CPM_GSMR_L_TENCMANCHESTER	_BITFIELD32B(23, 0x4)
#define	PPC8260CPM_GSMR_L_TENCDMANCHESTER	_BITFIELD32B(23, 0x6)
#define	PPC8260CPM_GSMR_L_DIAG_M			_BITFIELD32B(25, 0x3)
#define	PPC8260CPM_GSMR_L_DIAGNORMAL		_BITFIELD32B(25, 0x0)
#define	PPC8260CPM_GSMR_L_DIAGLOOPBACK		_BITFIELD32B(25, 0x1)
#define	PPC8260CPM_GSMR_L_DIAGECHO			_BITFIELD32B(25, 0x2)
#define	PPC8260CPM_GSMR_L_DIAGLOOPBACK_ECHO	_BITFIELD32B(25, 0x3)
#define	PPC8260CPM_GSMR_L_ENR				_ONEBIT32B(26)
#define	PPC8260CPM_GSMR_L_ENT				_ONEBIT32B(27)
#define	PPC8260CPM_GSMR_L_MODE_M			_BITFIELD32B(31, 0xf)
#define	PPC8260CPM_GSMR_L_MODEHDLC			_BITFIELD32B(31, 0x0)
#define	PPC8260CPM_GSMR_L_MODEAPPLETALK		_BITFIELD32B(31, 0x2)
#define	PPC8260CPM_GSMR_L_MODESS7			_BITFIELD32B(31, 0x3)
#define	PPC8260CPM_GSMR_L_MODEUART			_BITFIELD32B(31, 0x4)
#define	PPC8260CPM_GSMR_L_MODEPROFIBUS		_BITFIELD32B(31, 0x5)
#define	PPC8260CPM_GSMR_L_MODEAHDLC			_BITFIELD32B(31, 0x6)
#define	PPC8260CPM_GSMR_L_MODEV14			_BITFIELD32B(31, 0x7)
#define	PPC8260CPM_GSMR_L_MODEBISYNC		_BITFIELD32B(31, 0x8)
#define	PPC8260CPM_GSMR_L_MODEDDCMP			_BITFIELD32B(31, 0x9)
#define	PPC8260CPM_GSMR_L_MODEETHERNETSCC1	_BITFIELD32B(31, 0xc)

/* SCC Data Synchronization Register */
#define	PPC8260CPM_DSR_SYN1M				_BITFIELD16B(15, 0xf)
#define	PPC8260CPM_DSR_SYN2M				_BITFIELD16B(7, 0xf)
#define	PPC8260CPM_DSR_SYN1(n)				_BITFIELD16B(15, (n))
#define	PPC8260CPM_DSR_SYN2(n)				_BITFIELD16B(7, (n))

/* SCC Transmit-on-Demand Register */
#define	PPC8260CPM_TODR_TOD					_ONEBIT16B(0)

/* UART Protocal */
/* Mode register SCC UART */
#define	PPC8260CPM_SCCMR_UART_FLC			_ONEBIT16B(0)
#define	PPC8260CPM_SCCMR_UART_SL			_ONEBIT16B(1)
#define	PPC8260CPM_SCCMR_UART_CL_M			_BITFIELD16B(3,0x3)
#define	PPC8260CPM_SCCMR_UART_CL5			_BITFIELD16B(3,0x0)
#define	PPC8260CPM_SCCMR_UART_CL6			_BITFIELD16B(3,0x1)
#define	PPC8260CPM_SCCMR_UART_CL7			_BITFIELD16B(3,0x2)
#define	PPC8260CPM_SCCMR_UART_CL8			_BITFIELD16B(3,0x3)
#define	PPC8260CPM_SCCMR_UART_UM_M			_BITFIELD16B(5,0x3)
#define	PPC8260CPM_SCCMR_UART_UMNORMAL		_BITFIELD16B(5,0x0)
#define	PPC8260CPM_SCCMR_UART_UMMULTIDROP	_BITFIELD16B(5,0x1)
#define	PPC8260CPM_SCCMR_UART_UMMULTIDROPAU	_BITFIELD16B(5,0x3)
#define	PPC8260CPM_SCCMR_UART_FRZ			_ONEBIT16B(6)
#define	PPC8260CPM_SCCMR_UART_RZS			_ONEBIT16B(7)
#define	PPC8260CPM_SCCMR_UART_SYN			_ONEBIT16B(8)
#define	PPC8260CPM_SCCMR_UART_DRT			_ONEBIT16B(9)
#define	PPC8260CPM_SCCMR_UART_PEN			_ONEBIT16B(11)
#define	PPC8260CPM_SCCMR_UART_RPM_M			_BITFIELD16B(13, 0x3)
#define	PPC8260CPM_SCCMR_UART_RPMODD		_BITFIELD16B(13, 0x0)
#define	PPC8260CPM_SCCMR_UART_RPMLOW		_BITFIELD16B(13, 0x1)
#define	PPC8260CPM_SCCMR_UART_RPMEVEN		_BITFIELD16B(13, 0x2)
#define	PPC8260CPM_SCCMR_UART_RPMHIGH		_BITFIELD16B(13, 0x3)
#define	PPC8260CPM_SCCMR_UART_TPM_M			_BITFIELD16B(15, 0x3)
#define	PPC8260CPM_SCCMR_UART_TPMODD		_BITFIELD16B(15, 0x0)
#define	PPC8260CPM_SCCMR_UART_TPMLOW		_BITFIELD16B(15, 0x1)
#define	PPC8260CPM_SCCMR_UART_TPMEVEN		_BITFIELD16B(15, 0x2)
#define	PPC8260CPM_SCCMR_UART_TPMHIGH		_BITFIELD16B(15, 0x3)

/* Event register SCC UART & Mask register SCC UART */
#define	PPC8260CPM_SCCERMSKR_UART_GLR 		_ONEBIT16B(3)
#define	PPC8260CPM_SCCERMSKR_UART_GLT 		_ONEBIT16B(4)
#define	PPC8260CPM_SCCERMSKR_UART_AB	 	_ONEBIT16B(6)
#define	PPC8260CPM_SCCERMSKR_UART_IDL	 	_ONEBIT16B(7)
#define	PPC8260CPM_SCCERMSKR_UART_GRA	 	_ONEBIT16B(8)
#define	PPC8260CPM_SCCERMSKR_UART_BRKE		_ONEBIT16B(9)
#define	PPC8260CPM_SCCERMSKR_UART_BRKS 		_ONEBIT16B(10)
#define	PPC8260CPM_SCCERMSKR_UART_CCR		_ONEBIT16B(12)
#define	PPC8260CPM_SCCERMSKR_UART_BSY		_ONEBIT16B(13)
#define	PPC8260CPM_SCCERMSKR_UART_TX  		_ONEBIT16B(14)
#define	PPC8260CPM_SCCERMSKR_UART_RX 		_ONEBIT16B(15)

/* Status Register SCC UART */
#define	PPC8260CPM_SCCSR_UART_ID		 	_ONEBIT8B(7)

/* Fractional Stop Bits */
#define	PPC8260CPM_DSR_FSBM					_BITFIELD16B(4, 0xf)
#define	PPC8260CPM_DSR_FSB(n)				_BITFIELD16B(4, (n))

/* Event register FCC Ethernet */
#define PPC8260CPM_FCCERMSKR_ETH			_BITFIELD32B(15,0xff)
#define PPC8260CPM_FCCERMSKR_ETH_GRA		_ONEBIT32B(8)
#define PPC8260CPM_FCCERMSKR_ETH_RXC		_ONEBIT32B(9)
#define PPC8260CPM_FCCERMSKR_ETH_TXC		_ONEBIT32B(10)
#define PPC8260CPM_FCCERMSKR_ETH_TXE		_ONEBIT32B(11)
#define PPC8260CPM_FCCERMSKR_ETH_RXF		_ONEBIT32B(12)
#define PPC8260CPM_FCCERMSKR_ETH_BSY		_ONEBIT32B(13)
#define PPC8260CPM_FCCERMSKR_ETH_TXB		_ONEBIT32B(14)
#define PPC8260CPM_FCCERMSKR_ETH_RXB		_ONEBIT32B(15)

/* General FCC Mode Register */
#define	PPC8260CPM_GFMR_DIAG_M				_BITFIELD32B(1, 0x3)
#define	PPC8260CPM_GFMR_DIAGNORMAL			_BITFIELD32B(1, 0x0)
#define	PPC8260CPM_GFMR_DIAGLOOPBACK		_BITFIELD32B(1, 0x1)
#define	PPC8260CPM_GFMR_DIAGECHO			_BITFIELD32B(1, 0x2)
#define	PPC8260CPM_GFMR_DIAGLOOPBACK_ECHO	_BITFIELD32B(1, 0x3)
#define	PPC8260CPM_GFMR_TCI					_ONEBIT32B(2)
#define	PPC8260CPM_GFMR_TRX					_ONEBIT32B(3)
#define	PPC8260CPM_GFMR_TTX					_ONEBIT32B(4)
#define	PPC8260CPM_GFMR_CDP					_ONEBIT32B(5)
#define	PPC8260CPM_GFMR_CTSP				_ONEBIT32B(6)
#define	PPC8260CPM_GFMR_CDS					_ONEBIT32B(7)
#define	PPC8260CPM_GFMR_CTSS				_ONEBIT32B(8)
#define	PPC8260CPM_GFMR_SYNL_M				_BITFIELD32B(17,0x3)
#define	PPC8260CPM_GFMR_RTSM				_ONEBIT32B(18)
#define	PPC8260CPM_GFMR_RENC_M				_BITFIELD32B(20,0x3)
#define	PPC8260CPM_GFMR_REVD				_ONEBIT32B(21)
#define	PPC8260CPM_GFMR_TENC_M				_BITFIELD32B(23,0x3)
#define	PPC8260CPM_GFMR_TCRC_M				_BITFIELD32B(25,0x3)
#define	PPC8260CPM_GFMR_TCRC_16				_BITFIELD32B(25,0)
#define	PPC8260CPM_GFMR_TCRC_32				_BITFIELD32B(25,0x2)
#define	PPC8260CPM_GFMR_ENR					_ONEBIT32B(26)
#define	PPC8260CPM_GFMR_ENT					_ONEBIT32B(27)
#define	PPC8260CPM_GFMR_MODE_M				_BITFIELD32B(31, 0xf)
#define	PPC8260CPM_GFMR_MODEHDLC			_BITFIELD32B(31, 0x0)
#define	PPC8260CPM_GFMR_MODEATM				_BITFIELD32B(31, 0xa)
#define	PPC8260CPM_GFMR_MODEETHERNET		_BITFIELD32B(31, 0xc)

/* FCC Ethernet Mode Register */
#define PPC8260CPM_FPSMR_HBC				_ONEBIT32B(0);
#define PPC8260CPM_FPSMR_FC					_ONEBIT32B(1);
#define PPC8260CPM_FPSMR_SBT				_ONEBIT32B(2);
#define PPC8260CPM_FPSMR_LPB				_ONEBIT32B(3);
#define PPC8260CPM_FPSMR_LCW				_ONEBIT32B(4);
#define PPC8260CPM_FPSMR_FDE				_ONEBIT32B(5);
#define PPC8260CPM_FPSMR_MON				_ONEBIT32B(6);
#define PPC8260CPM_FPSMR_PRO				_ONEBIT32B(9);
#define PPC8260CPM_FPSMR_FCE				_ONEBIT32B(10);
#define PPC8260CPM_FPSMR_RSH				_ONEBIT32B(11);
#define PPC8260CPM_FPSMR_CAM				_ONEBIT32B(21);
#define PPC8260CPM_FPSMR_BRO				_ONEBIT32B(22);
#define PPC8260CPM_FPSMR_CRC32				_BITFIELD32B(25,0x2)

/* Rx FCC ETH BD */
#define	PPC8260CPM_FCCETH_RXBD_E			_ONEBIT16B(0)
#define	PPC8260CPM_FCCETH_RXBD_W			_ONEBIT16B(2)
#define	PPC8260CPM_FCCETH_RXBD_I			_ONEBIT16B(3)
#define	PPC8260CPM_FCCETH_RXBD_L			_ONEBIT16B(4)
#define	PPC8260CPM_FCCETH_RXBD_F			_ONEBIT16B(5)
#define	PPC8260CPM_FCCETH_RXBD_M			_ONEBIT16B(7)
#define	PPC8260CPM_FCCETH_RXBD_BC			_ONEBIT16B(8)
#define	PPC8260CPM_FCCETH_RXBD_MC			_ONEBIT16B(9)
#define	PPC8260CPM_FCCETH_RXBD_LG			_ONEBIT16B(10)
#define	PPC8260CPM_FCCETH_RXBD_NO			_ONEBIT16B(11)
#define	PPC8260CPM_FCCETH_RXBD_SH			_ONEBIT16B(12)
#define	PPC8260CPM_FCCETH_RXBD_CR			_ONEBIT16B(13)
#define	PPC8260CPM_FCCETH_RXBD_OV			_ONEBIT16B(14)
#define	PPC8260CPM_FCCETH_RXBD_CL			_ONEBIT16B(15)
#define PPC8260CPM_FCCETH_RXBD_ERROR		_BITFIELD16B(15,0x3f)

/* Tx FCC ETH BD*/
#define	PPC8260CPM_FCCETH_TXBD_R			_ONEBIT16B(0)
#define	PPC8260CPM_FCCETH_TXBD_PAD			_ONEBIT16B(1)
#define	PPC8260CPM_FCCETH_TXBD_W			_ONEBIT16B(2)
#define	PPC8260CPM_FCCETH_TXBD_I			_ONEBIT16B(3)
#define	PPC8260CPM_FCCETH_TXBD_L			_ONEBIT16B(4)
#define	PPC8260CPM_FCCETH_TXBD_TC			_ONEBIT16B(5)
#define	PPC8260CPM_FCCETH_TXBD_DEF			_ONEBIT16B(6)
#define	PPC8260CPM_FCCETH_TXBD_HB			_ONEBIT16B(7)
#define	PPC8260CPM_FCCETH_TXBD_LC			_ONEBIT16B(8)
#define	PPC8260CPM_FCCETH_TXBD_RL			_ONEBIT16B(9)
#define	PPC8260CPM_FCCETH_TXBD_RC_M			_BITFIELD16B(13,0xf)
#define	PPC8260CPM_FCCETH_TXBD_UN			_ONEBIT16B(14)
#define	PPC8260CPM_FCCETH_TXBD_CSL			_ONEBIT16B(15)
#define PPC8260CPM_FCCETH_TXBD_ERROR		_BITFIELD16B(15,0xc2)
#define PPC8260CPM_FCCETH_TXBD_ST_M			_BITFIELD16B(15,0x1fff)

/* FCC Transmit-on-Demand Register */
#define	PPC8260CPM_FTODR_TOD				_ONEBIT16B(0)


/*
*** port identifier
*/
typedef enum {
	PPC8260_SMC1,
	PPC8260_SMC2,
	PPC8260_SCC1,
	PPC8260_SCC2,
	PPC8260_SCC3,
	PPC8260_SCC4,
	PPC8260_USB,
	PPC8260_I2C,
	PPC8260_SPI,
	PPC8260_FCC1,
	PPC8260_FCC2,
	PPC8260_FCC3,
	PPC8260_MCC1,
	PPC8260_MCC2
} PPC8260CPM_CH_NUM;

/*
 * QNX default value for shared resources
 */
/* Offset from DPRAM_BASE
 The format of DBT: ptr to current DB (4), data buffer size (2), reserve (2), table
*/
#define	PPC8260CPM_DPRAM_BDT_SMC1			PPC8260CPM_DPRAM_BD7_S
#define	PPC8260CPM_DPRAM_DBUF_SMC1			PPC8260CPM_DPRAM_BDT_SMC1 + 0x100
#define	PPC8260CPM_DPRAM_BDT_SMC2			PPC8260CPM_DPRAM_DBUF_SMC1 + 0x100
#define	PPC8260CPM_DPRAM_DBUF_SMC2			PPC8260CPM_DPRAM_BDT_SMC2 + 0x100
#define	PPC8260CPM_DPRAM_PARA_SMC1			PPC8260CPM_DPRAM_DBUF_SMC2 + 0x100
#define	PPC8260CPM_DPRAM_PARA_SMC2			PPC8260CPM_DPRAM_PARA_SMC1 + 0x100
#define	PPC8260CPM_DPRAM_BDT_SCC1			PPC8260CPM_DPRAM_BD8_S
#define	PPC8260CPM_DPRAM_DBUF_SCC1			PPC8260CPM_DPRAM_BDT_SCC1 + 0x100
#define	PPC8260CPM_DPRAM_BDT_SCC2			PPC8260CPM_DPRAM_DBUF_SCC1 + 0x100
#define	PPC8260CPM_DPRAM_DBUF_SCC2			PPC8260CPM_DPRAM_BDT_SCC2 + 0x100
#define	PPC8260CPM_DPRAM_BDT_SCC3			PPC8260CPM_DPRAM_DBUF_SCC2 + 0x100
#define	PPC8260CPM_DPRAM_DBUF_SCC3			PPC8260CPM_DPRAM_BDT_SCC3 + 0x100
#define	PPC8260CPM_DPRAM_BDT_SCC4			PPC8260CPM_DPRAM_DBUF_SCC3 + 0x100
#define	PPC8260CPM_DPRAM_DBUF_SCC4			PPC8260CPM_DPRAM_BDT_SCC4 + 0x100

/* UART default paras */
#define	PPC8260CPM_UART_DBSIZE_D			16
#define	PPC8260CPM_UART_DBNUM_D				8

#ifdef BUILDENV_iox
#undef PPC8260CPM_UART_DBSIZE_D
/* Buffer size of 1, to allow kdebug to work with 8260 CPM */
#define	PPC8260CPM_UART_DBSIZE_D			1
#endif

#endif

/* __SRCVERSION("8260cpm.h $Rev: 199790 $"); */
