/******************************************************************************
*
* Copyright (C) 2018 - 2020 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*
* 
*
******************************************************************************/
/*****************************************************************************/
/**
*
* @file fpd_apu.h
*
* This file contains FPD APU definitions used by PSM Firmware
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver	Who		Date		Changes
* ---- ---- -------- ------------------------------
* 1.00  rv   07/17/2018 Initial release
*
* </pre>
*
* @note
*
******************************************************************************/

#ifndef XPSMFW_FPD_APU_H_
#define XPSMFW_FPD_APU_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * FPD_APU Base Address
 */
#define FPD_APU_BASEADDR      0XFD5C0000U

/**
 * Register: FPD_APU_PWRCTL
 */
#define FPD_APU_PWRCTL    ( ( FPD_APU_BASEADDR ) + 0X00000090U )

#define FPD_APU_PWRCTL_CLREXMONREQ_SHIFT   17U
#define FPD_APU_PWRCTL_CLREXMONREQ_WIDTH   1U
#define FPD_APU_PWRCTL_CLREXMONREQ_MASK    0X00020000U

#define FPD_APU_PWRCTL_L2FLUSHREQ_SHIFT   16U
#define FPD_APU_PWRCTL_L2FLUSHREQ_WIDTH   1U
#define FPD_APU_PWRCTL_L2FLUSHREQ_MASK    0X00010000U

#define FPD_APU_PWRCTL_CPUPWRDWNREQ_SHIFT   0U
#define FPD_APU_PWRCTL_CPUPWRDWNREQ_WIDTH   2U
#define FPD_APU_PWRCTL_CPUPWRDWNREQ_MASK    0X00000003U

/**
 * Register: FPD_APU_PWRSTAT
 */
#define FPD_APU_PWRSTAT    ( ( FPD_APU_BASEADDR ) + 0X00000094U )

#define FPD_APU_PWRSTAT_CLREXMONACK_SHIFT   17U
#define FPD_APU_PWRSTAT_CLREXMONACK_WIDTH   1U
#define FPD_APU_PWRSTAT_CLREXMONACK_MASK    0X00020000U

#define FPD_APU_PWRSTAT_L2FLUSHDONE_SHIFT   16U
#define FPD_APU_PWRSTAT_L2FLUSHDONE_WIDTH   1U
#define FPD_APU_PWRSTAT_L2FLUSHDONE_MASK    0X00010000U

#define FPD_APU_PWRSTAT_DBGNOPWRDWN_SHIFT   0U
#define FPD_APU_PWRSTAT_DBGNOPWRDWN_WIDTH   2U
#define FPD_APU_PWRSTAT_DBGNOPWRDWN_MASK    0X00000003U

/* APU reset vector address */
#define FPD_APU_RVBARADDR0L		( ( FPD_APU_BASEADDR ) + 0x00000040U )
#define FPD_APU_RVBARADDR0H		( ( FPD_APU_BASEADDR ) + 0x00000044U )
#define FPD_APU_RVBARADDR1L		( ( FPD_APU_BASEADDR ) + 0x00000048U )
#define FPD_APU_RVBARADDR1H		( ( FPD_APU_BASEADDR ) + 0x0000004CU )

#ifdef __cplusplus
}
#endif

#endif /* XPSMFW_FPD_APU_H_ */
