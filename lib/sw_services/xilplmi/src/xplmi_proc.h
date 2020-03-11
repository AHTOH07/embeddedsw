/******************************************************************************
* Copyright (C) 2019 - 2020 Xilinx, Inc. All rights reserved.
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
******************************************************************************/

/*****************************************************************************/
/**
*
* @file xplmi_proc.h
*
* This file contains declarations for PROC C file in PLM.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date        Changes
* ----- ---- -------- -------------------------------------------------------
* 1.00  kc   02/07/2019 Initial release
* 1.01  ma   02/03/2020 Change Performance measurement functions generic to be
*                       used for logging
*
* </pre>
*
* @note
*
******************************************************************************/

#ifndef XPLMI_PROC_H
#define XPLMI_PROC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "xiomodule.h"
#include "xil_exception.h"
#include "xplmi_gic_interrupts.h"
#include "xplmi_util.h"
#include "xplmi_status.h"

/************************** Constant Definitions *****************************/
#define IOMODULE_DEVICE_ID XPAR_IOMODULE_0_DEVICE_ID
#define MB_IOMODULE_GPO1_PIT1_PRESCALE_SRC_MASK	(0x2U)
#define XPLMI_PIT1_RESET_VALUE		(0xFFFFFFFEU)
#define XPLMI_PIT2_RESET_VALUE		(0xFFFFFFFEU)
#define XPLMI_PIT1			(0U)
#define XPLMI_PIT2			(1U)
#define XPLMI_PIT3			(2U)
#define XPLMI_IOMODULE_PMC_PIT3_IRQ			(0x5)


/**************************** Type Definitions *******************************/
/**
 * PMC IOmodule interrupts
 */
enum {
	XPLMI_IOMODULE_PMC_GIC_IRQ=16U,
	XPLMI_IOMODULE_PPU1_MB_RAM,
	XPLMI_IOMODULE_ERR_IRQ,
	XPLMI_IOMODULE_RESERVED_19,
	XPLMI_IOMODULE_CFRAME_SEU,
	XPLMI_IOMODULE_RESERVED_21,
	XPLMI_IOMODULE_PMC_GPI,
	XPLMI_IOMODULE_PL_IRQ,
	XPLMI_IOMODULE_SSIT_IRQ_2,
	XPLMI_IOMODULE_SSIT_IRQ_1,
	XPLMI_IOMODULE_SSIT_IRQ_0,
	XPLMI_IOMODULE_PWRDN_REQ,
	XPLMI_IOMODULE_PWRUP_REQ,
	XPLMI_IOMODULE_SRST_REQ,
	XPLMI_IOMODULE_ISO_REQ,
	XPLMI_IOMODULE_WAKEUP_REQ,
	XPLMI_IOMODULE_MASK=0xFFU,
};

/**
 * External interrupt mapping
 */
enum {
	XPLMI_CFRAME_SEU = 0U,
	XPLMI_IPI_IRQ,
	XPLMI_SBI_DATA_RDY,
};

/**
 * Performance measurement structure
 */
typedef struct XPlmi_PerfTime {
	u64 tPerfMs;
	u64 tPerfMsFrac;
}XPlmi_PerfTime;

/***************** Macros (Inline Functions) Definitions *********************/
/************************** Function Prototypes ******************************/
void XPlmi_InitPitTimer(u8 Timer, u32 ResetValue);
int XPlmi_StartTimer();
int XPlmi_InitProc();
int XPlmi_InitIOModule();
void XPlmi_IntrHandler(void *CallbackRef);
u64 XPlmi_GetTimerValue(void );
int XPlmi_SetUpInterruptSystem();
void XPlmi_MeasurePerfTime(u64 tCur, XPlmi_PerfTime * tPerfTime);
void XPlmi_PlmIntrEnable(u32 IntrId);
void XPlmi_PlmIntrDisable(u32 IntrId);
void XPlmi_PlmIntrClear(u32 IntrId);
void XPlmi_RegisterHandler(u32 IntrId, Function_t Handler, void * Data);
void XPlmi_PrintRomTime();
void XPlmi_PrintPlmTimeStamp();
void XPlmi_GetPerfTime(u64 tCur, u64 tEnd, XPlmi_PerfTime * tPerfTime);

/* Handler Table Structure */
struct HandlerTable {
	XInterruptHandler Handler;
};

#ifdef __cplusplus
}
#endif

#endif  /* XPLMI_PROC_H */
