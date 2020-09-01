/******************************************************************************
* Copyright (c) 2020 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/


/*****************************************************************************/
/**
*
* @file xsecure_sss.c
* This file contains functions for SSS switch configurations.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who     Date     Changes
* ----- ------  -------- ------------------------------------------------------
* 1.0   har     03/26/20 Initial release
* 4.2   har     03/26/20 Updated file version to sync with library version
* 4.3	rpo	 	09/01/20 Asserts are not compiled by default for
*						 secure libraries
*
* </pre>
*
******************************************************************************/

/***************************** Include Files *********************************/
#include "xsecure_sss.h"
#include "xsecure_utils.h"

/************************** Constant Definitions *****************************/
/* XSecure_SssLookupTable[Input source][Resource] */
static const u8 XSecure_SssLookupTable
		[XSECURE_SSS_MAX_SRCS][XSECURE_SSS_MAX_SRCS] = {
	/*+----+-----+-----+-----+-----+-----+-----+--------+
	*|DMA0| DMA1| PTPI| AES | SHA | SBI | PZM |Invalid |
	*+----+-----+-----+-----+-----+-----+-----+--------+
	* 0x00 = INVALID value
	*/
	{0x0DU, 0x00U, 0x00U, 0x06U, 0x00U, 0x0BU, 0x03U, 0x00U}, /* DMA0 */
	{0x00U, 0x09U, 0x00U, 0x07U, 0x00U, 0x0EU, 0x04U, 0x00U}, /* DMA1 */
	{0x0DU, 0x0AU, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U}, /* PTPI */
	{0x0EU, 0x05U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U}, /* AES  */
	{0x0CU, 0x07U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U}, /* SHA  */
	{0x05U, 0x0BU, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U}, /* SBI  */
	{0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U}, /* PZI  */
	{0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U}, /* Invalid */
};

/************************** Function Prototypes ******************************/
static u32 XSecure_SssDmaSrc(u16 DmaId, XSecure_SssSrc *Resource);
static u32 XSecure_SssCfg (XSecure_Sss *InstancePtr, XSecure_SssSrc Resource,
			XSecure_SssSrc InputSrc, XSecure_SssSrc OutputSrc);

/************************** Function Definitions *****************************/
/*****************************************************************************/
/**
 * @brief
 * This function initializes the secure stream switch instance.
 *
 * @param	InstancePtr	Instance pointer to the XSecure_Sss.
 *
 *****************************************************************************/
void XSecure_SssInitialize (XSecure_Sss *InstancePtr)
{
	/* Assert validates the input arguments */
	XSecure_AssertVoid(InstancePtr != NULL);

	InstancePtr->Address = XSECURE_SSS_ADDRESS;

}

/*****************************************************************************/
/**
 * @brief
 * This function configures the secure stream switch for AES engine.
 *
 * @param	InstancePtr	Instance pointer to the XSecure_Sss
 * @param	InputSrc	Input DMA to be selected for AES engine.
 * @param	OutputSrc	Output DMA to be selected for AES engine.
 *
 * @return	- XST_SUCCESS - on successful configuration of the switch
 *			- XST_FAILURE - on failure to configure switch
 *
 * @note	InputSrc, OutputSrc are of type XSecure_SssSrc.
 *
 *****************************************************************************/
u32 XSecure_SssAes(XSecure_Sss *InstancePtr,
		XSecure_SssSrc InputSrc, XSecure_SssSrc OutputSrc)
{
	/* Assert validates the input arguments */
	XSecure_AssertNonvoid(InstancePtr != NULL);
	XSecure_AssertNonvoid((InputSrc >= XSECURE_SSS_DMA0) &&
		(InputSrc < XSECURE_SSS_INVALID));
	XSecure_AssertNonvoid((OutputSrc >= XSECURE_SSS_DMA0) &&
		(OutputSrc < XSECURE_SSS_INVALID));

	return XSecure_SssCfg(InstancePtr, XSECURE_SSS_AES,
			InputSrc, OutputSrc);
}

/*****************************************************************************/
/**
 * @brief
 * This function configures the secure stream switch for SHA hardware engine.
 *
 * @param	InstancePtr	Instance pointer to the XSecure_Sss
 * @param	DmaId		Device ID of DMA which is to be used as an
 *				input to the SHA engine.
 *
 * @return	- XST_SUCCESS - on successful configuration of the switch.
 *			- XST_FAILURE - on failure to configure switch
 *
 *****************************************************************************/
u32 XSecure_SssSha(XSecure_Sss *InstancePtr, u16 DmaId)
{
	XSecure_SssSrc InputSrc = XSECURE_SSS_INVALID;
	u32 Status = (u32)XST_FAILURE;

	/* Assert validates the input arguments */
	XSecure_AssertNonvoid(InstancePtr != NULL);
	XSecure_AssertNonvoid((DmaId == 0U) || (DmaId == 1U));

	Status = XSecure_SssDmaSrc(DmaId, &InputSrc);
	if (Status != XST_SUCCESS) {
		goto END;
	}

	Status = XSecure_SssCfg(InstancePtr, XSECURE_SSS_SHA, InputSrc,
			XSECURE_SSS_INVALID);
END:
	return Status;

}

/*****************************************************************************/
/**
 * @brief
 * This function configures secure stream switch to set DMA in loop back mode.
 *
 * @param	InstancePtr	Instance pointer to the XSecure_Sss
 * @param	DmaId		Device ID of DMA.
 *
 * @return	- XST_SUCCESS - on successful configuration of the switch.
 *			- XST_FAILURE - on failure to configure switch
 *
 *****************************************************************************/
u32 XSecure_SssDmaLoopBack(XSecure_Sss *InstancePtr, u16 DmaId)
{
	XSecure_SssSrc Resource = XSECURE_SSS_INVALID;
	u32 Status = (u32)XST_FAILURE;

	/* Assert validates the input arguments */
	XSecure_AssertNonvoid(InstancePtr != NULL);
	XSecure_AssertNonvoid((DmaId == 0U) || (DmaId == 1U));

	Status = XSecure_SssDmaSrc(DmaId, &Resource);
	if (Status != XST_SUCCESS) {
		goto END;
	}

	Status = XSecure_SssCfg(InstancePtr, Resource, Resource,
				XSECURE_SSS_INVALID);
END:
	return Status;
}

/*****************************************************************************/
/**
 * @brief
 * This function sets the DMA source of type XSecure_SssSrc based on the
 * provided DMA device ID.
 *
 * @param	InstancePtr	Instance pointer to the XSecure_Sss
 * @param	DmaId		Device ID of DMA.
 * @param	Resource	DMA source is updated into the pointer.
 *
 * @return
 *			- XST_SUCCESS if DMA ID is correct
 *			- XST_FAILURE on wrong DMA ID
 *
 *****************************************************************************/
static u32 XSecure_SssDmaSrc(u16 DmaId, XSecure_SssSrc *Resource)
{
	u32 Status = (u32)XST_FAILURE;

	/* Assert validates the input arguments */
	XSecure_AssertNonvoid(Resource != NULL);
	XSecure_AssertNonvoid((DmaId == 0U) || (DmaId == 1U));

	if (DmaId == 0U) {
		*Resource = XSECURE_SSS_DMA0;
		Status = (u32)XST_SUCCESS;
	}
	else {
		*Resource = XSECURE_SSS_DMA1;
		Status = (u32)XST_SUCCESS;
	}
	return Status;
}

/*****************************************************************************/
/**
 * @brief
 * This function configures the secure stream switch.
 *
 * @param	InstancePtr	Instance pointer to the XSecure_Sss
 * @param	Resource	Resource for which input and output paths to be
 *				configured.
 * @param	InputSrc	Input source to be selected for the resource.
 * @param	OutputSrc	Output source to be selected for the resource.
 *
 * @return	- XST_SUCCESS - on successful configuration of the switch
 *		    - XST_FAILURE - on unsuccessful configuration of the switch
 *
 * @note	Resource, InputSrc, OutputSrc are of type XSecure_SssSrc.
 *
 *****************************************************************************/
static u32 XSecure_SssCfg (XSecure_Sss *InstancePtr, XSecure_SssSrc Resource,
			XSecure_SssSrc InputSrc, XSecure_SssSrc OutputSrc)
{
	u32 InputSrcCfg = 0x0U;
	u32 OutputSrcCfg = 0x0U;
	volatile u32 InputSrcCfgRedundant = 0x0U;
	volatile u32 OutputSrcCfgRedundant = 0x0U;
	u32 SssCfg = 0x0U;
	u32 Status = (u32)XST_FAILURE;

	/* Assert validates the input arguments */
	XSecure_AssertNonvoid(InstancePtr != NULL);
	XSecure_AssertNonvoid((InputSrc >= XSECURE_SSS_DMA0) &&
		(InputSrc <= XSECURE_SSS_INVALID));
	XSecure_AssertNonvoid((OutputSrc >= XSECURE_SSS_DMA0) &&
		(OutputSrc <= XSECURE_SSS_INVALID));
	XSecure_AssertNonvoid((Resource >= XSECURE_SSS_DMA0) &&
		(Resource <= XSECURE_SSS_INVALID));

	/*
	 * Configure source of the input for given resource
	 * i.e Configure given InputSrc as a input for given Resource
	 */
	InputSrcCfg = (u32) XSecure_SssLookupTable [Resource][InputSrc] <<
		(XSECURE_SSS_CFG_LEN_IN_BITS * (u32)Resource);

	/*
	 * SSS allows configuring only input source for any Resources
	 * connected to it. So to define output source of given Resource,
	 *  configure given Resource as input to source mentioned by OutputSrc
	 */
	OutputSrcCfg = (u32) XSecure_SssLookupTable [OutputSrc][Resource] <<
			(XSECURE_SSS_CFG_LEN_IN_BITS * (u32)OutputSrc);

	/* Recalculating to verify values */
	InputSrcCfgRedundant = (u32) XSecure_SssLookupTable [Resource][InputSrc] <<
                (XSECURE_SSS_CFG_LEN_IN_BITS * (u32)Resource);

	OutputSrcCfgRedundant = (u32) XSecure_SssLookupTable [OutputSrc][Resource] <<
                (XSECURE_SSS_CFG_LEN_IN_BITS * (u32)OutputSrc);

	SssCfg = InputSrcCfg | OutputSrcCfg;

	if ((SssCfg ^ (InputSrcCfgRedundant | OutputSrcCfgRedundant)) == 0U) {
		Status = XSecure_SecureOut32(InstancePtr->Address, SssCfg);
	}

	return Status;
}
