/******************************************************************************
*
* Copyright (C) 2017-2020 Xilinx, Inc.  All rights reserved.
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
* FITNESS FOR A PRTNICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
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
* @file xilpdi.h
*
* This is the header file which contains definitions for the PDI.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date        Changes
* ----- ---- -------- -------------------------------------------------------
* 1.00  kc   12/21/2017 Initial release
*
* </pre>
*
* @note
*
******************************************************************************/

#ifndef XILPDI_H
#define XILPDI_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#include "xil_types.h"
#include "xstatus.h"
#include "xil_printf.h"

/************************** Constant Definitions *****************************/
#define XIH_MIN_PRTNS			(1U)
#define XIH_MAX_PRTNS			(32U)

/* Boot header address in PRAM copied by ROM*/
#define XIH_BH_PRAM_ADDR		(0xF201E000U)

#define XIH_AC_PRAM_OFFSET		(0xF70)
/* Boot header SMAP bus width length */
#define XIH_BH_SMAP_BUS_WIDTH_LEN	(16U)

/* Boot header Attr fields */
#define XIH_BH_IMG_ATTRB_BH_AUTH_MASK	(0xC000U)
#define XIH_BH_IMG_ATTRB_SHA2_MASK	(0x3000U)

/* Boot Header PMC FW Rsvd Fields */
#define XIH_BH_MH_START_OFST		(0xC4U)
#define XIH_BH_MH_LEN_OFST		(0xC8U)
#define XIH_BH_MH_AC_START_OFST		(0xCCU)

/* Boot header PUF fields */
#define XIH_BH_PUF_HD_OFFSET		(0x918U)
#define XIH_BH_PUF_CHASH_OFFSET		(0xF18U)
#define XIH_BH_PUF_AUX_OFFSET		(0xF1CU)

/* Defines for length of the headers */
#define XIH_BH_LEN			(0x128U)
#define XIH_FIELD_LEN			(4U)
#define XIH_PFW_LEN_FIELD_LEN		(4U)
#define XIH_IHT_LEN			(128U)
#define XIH_IH_LEN			(64U)
#define XIH_PH_LEN			(128U)
#define XIH_PRTN_WORD_LEN		(0x4U)
#define XIH_PRTN_ALIGN_LEN		(64U)

/* Img header table field offsets */
#define XIH_IHT_VERSION_OFST		(0x0U)
#define XIH_IHT_NO_OF_IMGS_OFST		(0x4U)
#define XIH_IHT_IH_ADDR_OFST		(0x8U)
#define XIH_IHT_NO_OF_PRTNS_OFST	(0xCU)
#define XIH_IHT_PH_ADDR_OFST		(0x10U)
#define XIH_IHT_SBD_ADDR_OFST		(0x14U)
#define XIH_IHT_IDCODE			(0x18U)
#define XIH_IHT_ATTR			(0x1CU)
#define XIH_IHT_CHECKSUM_OFST		(0x3CU)

/* Image Header fields */
#define XIH_IH_PH_OFST			(0x0U)
#define XIH_IH_NO_OF_PRTNS_OFST		(0x4U)
#define XIH_IH_NEXT_IH_OFST		(0x8U)
#define XIH_IH_ATTR_OFST		(0xCU)
#define XIH_IH_NAME_OFST		(0x10U)
#define XIH_IH_CHECKSUM_OFST		(0x3CU)

/* Prtn Hdr Fields */
#define XIH_PH_ENC_DATAWORD_LEN			(0x0U)
#define XIH_PH_UNENC_DATAWORD_LEN		(0x4U)
#define XIH_PH_TOTAL_DATAWORD_LEN		(0x8U)
#define XIH_PH_NEXT_PRTN_OFST			(0xCU)
#define XIH_PH_DSTN_EXECUTION_ADDR	        (0x10U)
#define XIH_PH_DSTN_LOAD_ADDR			(0x18U)
#define XIH_PH_DATA_WORD_OFST			(0x20U)
#define XIH_PH_ATTRB_OFST			(0x24U)
#define XIH_PH_SECTION_COUNT			(0x28U)
#define XIH_PH_CHECKSUM_WORD_OFST		(0x2CU)
#define XIH_PH_RSVD_x30				(0x30U)
#define XIH_PH_AUTHCERTIFICATE_OFST		(0x34U)
#define XIH_PH_RSVD_x38				(0x38U)
#define XIH_PH_CHECKSUM				(0x3CU)

/* IHT attributes */
#define XIH_IHT_ATTR_PUFHD_MASK		(0xC000U)
#define XIH_IHT_ATTR_PUFHD_SHIFT		(14U)
#define XIH_IHT_ATTR_DPA_CM_MASK		(0x3000U)
#define XIH_IHT_ATTR_BYPS_MASK				(0x1U) /**< IDCODE checks bypass */

#define XIH_IHT_EXT_IDCODE_MASK			(0x3FU)

/* Secondary Boot Device (SBD) in IHT Attributes */
#define XIH_IHT_ATTR_SBD_MASK	        (0xFC0U)
#define XIH_IHT_ATTR_SBD_SHIFT			(0x6U)
#define XIH_IHT_ATTR_SBD_SAME	        (0x0U)
#define XIH_IHT_ATTR_SBD_QSPI32	        (0x1U)
#define XIH_IHT_ATTR_SBD_QSPI24	        (0x2U)
#define XIH_IHT_ATTR_SBD_SD_0			(0x4U)
#define XIH_IHT_ATTR_SBD_SD_1			(0x5U)
#define XIH_IHT_ATTR_SBD_SD_LS          (0x6U)
#define XIH_IHT_ATTR_SBD_EMMC	        (0x7U)
#define XIH_IHT_ATTR_SBD_USB			(0x8U)
#define XIH_IHT_ATTR_SBD_PCIE	        (0xAU)
#define XIH_IHT_ATTR_SBD_OSPI			(0xCU)
#define XIH_IHT_ATTR_SBD_SMAP			(0xDU)
#define XIH_IHT_ATTR_SBD_SBI			(0xEU)
#define XIH_IHT_ATTR_SBD_SD_0_RAW		(0xFU)
#define XIH_IHT_ATTR_SBD_SD_1_RAW		(0x10U)
#define XIH_IHT_ATTR_SBD_SD_LS_RAW		(0x11U)
#define XIH_IHT_ATTR_SBD_EMMC_RAW		(0x12U)
#define XIH_IHT_ATTR_SBD_EMMC_0			(0x13U)
#define XIH_IHT_ATTR_SBD_EMMC_0_RAW		(0x14U)

/* Prtn Attribute fields */
#define XIH_PH_ATTRB_DPA_CM_EN_MASK		(0x18000000U)
#define XIH_PH_ATTRB_PRTN_TYPE_MASK		(0x7000000U)
#define XIH_PH_ATTRB_HIVEC_MASK			(0x800000U)
#define XIH_PH_ATTRB_CHUNKSIZE_MASK		(0x700000U)
#define XIH_PH_ATTRB_ENDIAN_MASK		(0x40000U)
#define XIH_PH_ATTRB_PRTN_OWNER_MASK	(0x30000U)
#define XIH_PH_ATTRB_PUFHD_MASK			(0xC000U)
#define XIH_PH_ATTRB_CHECKSUM_MASK		(0x3000U)
#define XIH_PH_ATTRB_DSTN_CPU_MASK		(0x0F00U)
#define XIH_PH_ATTRB_A72_EXEC_ST_MASK	(0x0008U)
#define XIH_PH_ATTRB_TARGET_EL_MASK		(0x0006U)
#define XIH_PH_ATTRB_TZ_SECURE_MASK		(0x0001U)

#define XIH_PH_ATTRB_PUFHD_SHIFT		(14U)

/* Prtn Attribute Values */
#define XIH_PH_ATTRB_PRTN_TYPE_RSVD		(0x0000000U)
#define XIH_PH_ATTRB_PRTN_TYPE_ELF		(0x1000000U)
#define XIH_PH_ATTRB_PRTN_TYPE_CDO		(0x2000000U)
#define XIH_PH_ATTRB_PRTN_TYPE_CFI		(0x3000000U)
#define XIH_PH_ATTRB_PRTN_TYPE_RAW		(0x4000000U)
#define XIH_PH_ATTRB_PRTN_TYPE_RAW_ELF		(0x5000000U)
#define XIH_PH_ATTRB_PRTN_TYPE_CFI_GSC		(0x6000000U)
#define XIH_PH_ATTRB_PRTN_TYPE_CFI_GSC_UNMASK	(0x7000000U)

#define XIH_PH_ATTRB_PRTN_OWNER_PMCFW	(0x00000U)
#define XIH_PH_ATTRB_PRTN_OWNER_PLM		(0x00000U)
#define XIH_PH_ATTRB_RSA_SIGNATURE		(0x8000U)
#define XIH_PH_ATTRB_NOCHECKSUM			(0x0000U)
#define XIH_PH_ATTRB_CHECKSUM_MD5		(0x1000U)
#define XIH_PH_ATTRB_HASH_SHA2			(0x2000U)
#define XIH_PH_ATTRB_HASH_SHA3			(0x3000U)

#define XIH_PH_ATTRB_DSTN_CPU_NONE	(u32)(0x0000U)
#define XIH_PH_ATTRB_DSTN_CPU_A72_0	(u32)(0x100U)
#define XIH_PH_ATTRB_DSTN_CPU_A72_1	(u32)(0x200U)
#define XIH_PH_ATTRB_DSTN_CPU_A72_2	(u32)(0x300U)
#define XIH_PH_ATTRB_DSTN_CPU_A72_3	(u32)(0x400U)
#define XIH_PH_ATTRB_DSTN_CPU_R5_0	(u32)(0x500U)
#define XIH_PH_ATTRB_DSTN_CPU_R5_1	(u32)(0x600U)
#define XIH_PH_ATTRB_DSTN_CPU_R5_L	(u32)(0x700U)
#define XIH_PH_ATTRB_DSTN_CPU_PSM	(u32)(0x800U)

#define XIH_PH_ATTRB_ENCRYPTION			(u32)(0x80U)

#define XIH_PH_ATTRB_DSTN_DEVICE_NONE	(u32)(0x0000U)
#define XIH_PH_ATTRB_DSTN_DEVICE_PS		(u32)(0x0010U)
#define XIH_PH_ATTRB_DSTN_DEVICE_PL		(u32)(0x0020U)

#define XIH_PH_ATTRB_A72_EXEC_ST_AA32	(u32)(0x0008U)
#define XIH_PH_ATTRB_A72_EXEC_ST_AA64	(u32)(0x0000U)

#define XIH_INVALID_EXEC_ST	(u32)(0xFFFFU)
/**
 * Below is the bit mapping of fields in the ATF Handoff parameters
 * with that of Prtn header. The number of bits shifted is
 * is based on the difference between these two offsets
 *
 *                   ATFHandoffParams	PrtnHdr         Shift
 *     Parameter     PrtnFlags     PrtnAttrb   difference
 * ----------------------------------------------------------------------
 *	Exec State            0			         3                  3 right
 *	ENDIAN	              1	                 18                 17 right
 *	SECURE                2                  0                  2 left
 *	EL                    3:4                1:2                2 left
 *	CPU_A72               5:6                8:10
 */
#define XIH_ATTRB_A72_EXEC_ST_SHIFT_DIFF    (3U)
#define XIH_ATTRB_ENDIAN_SHIFT_DIFF         (17U)
#define XIH_ATTRB_TR_SECURE_SHIFT_DIFF      (2U)
#define XIH_ATTRB_TARGET_EL_SHIFT_DIFF      (2U)

#define XIH_ATTRB_EL_MASK			(u32)(0x18U)
#define XIH_PRTN_FLAGS_EL_2			(u32)(0x10U)
#define XIH_PRTN_FLAGS_DSTN_CPU_A72_MASK	(u32)(0x60U)
#define XIH_PRTN_FLAGS_DSTN_CPU_A72_0		(u32)(0x00U)
#define XIH_PRTN_FLAGS_DSTN_CPU_A72_1		(u32)(0x20U)
#define XIH_PRTN_FLAGS_DSTN_CPU_A72_2		(u32)(0x40U)
#define XIH_PRTN_FLAGS_DSTN_CPU_A72_3		(u32)(0x60U)

/* Number of entries possible in ATF: 4 cores * 2 (secure, nonsecure) */
#define XILPDI_MAX_ENTRIES_FOR_ATF	8U

/**
 * Errors during XILDPI processing
 */
#define XILPDI_ERR_IHT_CHECKSUM		(0x1U)
#define XILPDI_ERR_NO_OF_PRTNS		(0x2U)
#define XILPDI_ERR_SBD			(0x3U)
#define XILPDI_ERR_ZERO_LENGTH		(0x4U)
#define XILPDI_ERR_TOTAL_LENGTH		(0x5U)
#define XILPDI_ERR_PRTN_TYPE		(0x6U)

#define SMAP_BUS_WIDTH_8_WORD1		(0xDD000000U)
#define SMAP_BUS_WIDTH_16_WORD1		(0x00DD0000U)
#define SMAP_BUS_WIDTH_32_WORD1		(0x000000DDU)
#define SMAP_BUS_WIDTH_LENGTH		(16U)

/**
 * Image Header Attributes
 */
#define XILPDI_IH_ATTRIB_IMAGE_OWNER_SHIFT		(0x3)
#define XILPDI_IH_ATTRIB_IMAGE_OWNER_WIDTH		(0x3U)
#define XILPDI_IH_ATTRIB_IMAGE_OWNER_MASK		(0X00000038U)

#define XILPDI_IH_ATTRIB_COPY_MEMORY_SHIFT		(0x6U)
#define XILPDI_IH_ATTRIB_COPY_MEMORY_WIDTH		(0x1U)
#define XILPDI_IH_ATTRIB_COPY_MEMORY_MASK		(0X00000040U)


#define XILPDI_IH_ATTRIB_DELAY_LOAD_SHIFT		(0x7U)
#define XILPDI_IH_ATTRIB_DELAY_LOAD_WIDTH		(0x1U)
#define XILPDI_IH_ATTRIB_DELAY_LOAD_MASK		(0X00000080U)


#define XILPDI_IH_ATTRIB_DELAY_HANDOFF_SHIFT		(0x8U)
#define XILPDI_IH_ATTRIB_DELAY_HANDOFF_WIDTH		(0x1U)
#define XILPDI_IH_ATTRIB_DELAY_HANDOFF_MASK		(0X00000100U)

#define XILPDI_METAHDR_RD_HDRS_FROM_DEVICE	(u32)(0x0U)
#define XILPDI_METAHDR_RD_HDRS_FROM_MEMBUF	(u32)(0x1U)

/**************************** Type Definitions *******************************/

/**
 * Structure to store the Boot Header PMC FW fields
 */
typedef struct {
	u32 MetaHdrOfst; /**< Offset to the start of meta header */
	u32 FwRsvd[24U]; /**< FW Reserved fields */
} XilPdi_BootHdrFwRsvd;

/**
 * Structure to store the boot header table details.
 * It contains all the information of boot header table in order.
 */
typedef struct {
	u32 SmapBusWidth[4]; /**< SMAP Bus Width */
	u32 WidthDetection; /**< Width Detection 0xAA995566 */
	u32 ImgIden;  /**< Image Identification */
	u32 EncStatus;  /**< Encryption Status */
	u32 DpiSrcOfst;  /**< Source Offset of PMC FW in DPI */
	u32 DpiStartOfst;  /**< PMC FW start offset in RAM */
	u32 DataPrtnLen;  /**< Data Partition Length */
	u32 TotalDataPrtnLen;  /**< Total Data Partition length */
	u32 PmcFwLen;  /**< PMC FW Length */
	u32 TotalPmcFwLen;  /**< Total PMC FW length */
	u32 ImgAttrb;  /**< Image Attributes */
	u32 Kek[8];  /**< Encrypted Key */
	u32 KekIv[3];  /**< Key Iv */
	u32 SecureHdrIv[3];  /**< Secure Header IV */
	u32 PufShutterVal; /**< PUF Shutter Value */
	u32 RomRsvd[20]; /**< ROM Reserved */
	XilPdi_BootHdrFwRsvd BootHdrFwRsvd; /**< FW reserved fields */
} XilPdi_BootHdr __attribute__ ((aligned(16)));

/**
 * Structure to store the image header table details.
 * It contains all the information of image header table in order.
 */
typedef struct {
	u32 Version; /**< PDI version used  */
	u32 NoOfImgs; /**< No of images present  */
	u32 ImgHdrAddr; /**< Address to start of 1st Image header*/
	u32 NoOfPrtns; /**< No of partitions present  */
	u32 PrtnHdrAddr; /**< Address to start of 1st partition header*/
	u32 SBDAddr; /**< Secondary Boot device address */
	u32 Idcode; /**< Device ID Code */
	u32 Attr; /**< Attributes */
	u32 Rsrvd[4];
	u32 TotalHdrLen; /**< Total size of Meta header AC + encryption overload */
	u32 IvMetaHdr[3]; /**< Iv for decrypting SH of meta header */
	u32 EncKeySrc; /**< Encryption key source for decrypting SH of headers */
	u32 ExtIdCode;  /**< Extended ID Code */
	u32 AcOffset; /**< AC offset of Meta header */
	u32 KekIv[3]; /**< Kek IV for meta header decryption */
	u32 Rsvd[9U]; /**< Reserved */
	u32 Checksum; /**< Checksum of the image header table */
} XilPdi_ImgHdrTable __attribute__ ((aligned(16)));

/**
 * Structure to store the Image header details.
 * It contains all the information of Image header in order.
 */
typedef struct {
	u32 FirstPrtnHdr; /**< First partition header in the image */
	u32 NoOfPrtns; /**< Number of partitions in the image */
	u32 EncRevokeID; /**< Revocation ID of meta header */
	u32 ImgAttr; /**< Image Attributes */
	u32 ImgName[4]; /**< Image Name */
	u32 ImgID; /**< Image ID */
	u32 Rsvd[6]; /**< Reserved */
	u32 Checksum; /**< checksum of the image header */
} XilPdi_ImgHdr __attribute__ ((aligned(16)));

/**
 * Structure to store the partition header details.
 * It contains all the information of partition header in order.
 */
typedef struct {
	u32 EncDataWordLen; /**< Enc word length of partition*/
	u32 UnEncDataWordLen; /**< unencrypted word length */
	u32 TotalDataWordLen;
		/**< Total word length including the authentication
			certificate if any*/
	u32 NextPrtnOfst; /**< Addr of the next partition header*/
	u64 DstnExecutionAddr; /**< Execution address */
	u64 DstnLoadAddr; /**< Load address in DDR/TCM */
	u32 DataWordOfst; /**< */
	u32 PrtnAttrb; /**< partition attributes */
	u32 SectionCount; /**< section count */
	u32 ChecksumWordOfst; /**< address to checksum when enabled */
	u32 PrtnId; /**< Partition ID */
	u32 AuthCertificateOfst;
		/**< address to the authentication certificate when enabled */
	u32 PrtnIv[3]; /**< IV of the partition's SH */
	u32 EncStatus; /**< Encryption Status/Key Selection */
	u32 KekIv[3]; /**< KEK IV for partition decryption */
	u32 EncRevokeID; /**< Revocation ID of partition for encrypted partition */
	u32 Reserved[9U]; /**< Reserved */
	u32 Checksum; /**< checksum of the partition header */
} XilPdi_PrtnHdr __attribute__ ((aligned(16)));

/**
 * Structure of the image header which contains
 * information of image header table and
 * partition headers.
 */
typedef struct {
	XilPdi_BootHdr BootHdr; /**< Boot Header */
	XilPdi_ImgHdrTable ImgHdrTable; /**< Img header table structure */
	XilPdi_ImgHdr ImgHdr[XIH_MAX_PRTNS]; /**< Prtn header */
	XilPdi_PrtnHdr PrtnHdr[XIH_MAX_PRTNS]; /**< Prtn header */
	u32 FlashOfstAddr; /**< Start of DPI start address in Flash */
	XStatus (*DeviceCopy) (u32 SrcAddr, u64 DestAddress, u32 Length, u32 Flags);
		/**< Function pointer for device copy */
	u32 Flag; /**< To read from flash or buffer ,
			   * if 0 - from flash and 1 - from buffer */
	u64 BufferAddr;
	void* (*XMemCpy)(void * DestPtr, const void * SrcPtr, u32 Len);
} XilPdi_MetaHdr __attribute__ ((aligned(16)));

/*
 * Structure corresponding to each partition entry
 */
typedef struct {
	u64 EntryPoint; /**< Entry point */
	u64 PartitionFlags; /**< Attributes of partition */
} XilPdi_PartitionEntry;

/*
 * Structure for handoff parameters to ARM Trusted Firmware (ATF)
 */
typedef struct {
	char8 MagicValue[4U]; /**< 32 bit magic string */
	u32 NumEntries; /**< Number of Entries */
	XilPdi_PartitionEntry Entry[XILPDI_MAX_ENTRIES_FOR_ATF];
		/**< Structure corresponding to each entry */
} XilPdi_ATFHandoffParams __attribute__ ((aligned(16)));

/***************** Macros (Inline Functions) Definitions *********************/
#ifdef XILPDI_DEBUG
#define XilPdi_Printf(...)	xil_printf(__VA_ARGS__)
#else
#define XilPdi_Printf(...)
#endif

/************************** Function Prototypes ******************************/
u32 XilPdi_GetPrtnOwner(const XilPdi_PrtnHdr * PrtnHdr);
u32 XilPdi_GetChecksumType(XilPdi_PrtnHdr * PrtnHdr);
u32 XilPdi_GetDstnCpu(const XilPdi_PrtnHdr * PrtnHdr);
u32 XilPdi_GetPrtnType(const XilPdi_PrtnHdr * PrtnHdr);
u32 XilPdi_GetA72ExecState(const XilPdi_PrtnHdr * PrtnHdr);
u32 XilPdi_GetVecLocation(const XilPdi_PrtnHdr * PrtnHdr);
u32 XilPdi_IsDpaCmEnable(const XilPdi_PrtnHdr * PrtnHdr);
u32 XilPdi_GetSBD(const XilPdi_ImgHdrTable * ImgHdrTbl);
u32 XilPdi_GetCopyToMemory(const XilPdi_ImgHdr *ImgHdr);
u32 XilPdi_GetDelayLoad(const XilPdi_ImgHdr *ImgHdr);
u32 XilPdi_GetDelayHandoff(const XilPdi_ImgHdr *ImgHdr);


XStatus XilPdi_ValidateChecksum(u32 Buffer[], u32 Len);
XStatus XilPdi_ValidatePrtnHdr(XilPdi_PrtnHdr * PrtnHdr);
XStatus XilPdi_ValidateImgHdrTable(XilPdi_ImgHdrTable * ImgHdrTable);
void XilPdi_ReadBootHdr(XilPdi_MetaHdr * ImgHdrPtr);
XStatus XilPdi_ReadImgHdrTbl(XilPdi_MetaHdr * ImgHdrPtr);
XStatus XilPdi_ReadAndVerifyImgHdr(XilPdi_MetaHdr * MetaHdrPtr);
XStatus XilPdi_ReadAndVerifyPrtnHdr(XilPdi_MetaHdr * ImgHdrPtr);
XStatus XilPdi_ReadAlignedData(XilPdi_MetaHdr * MetaHdrPtr, u32 PrtnNum);

u32 XilPdi_IsDpaCmEnableMetaHdr(const XilPdi_ImgHdrTable * IHdrTable);
u32 XilPdi_GetPufHdMetaHdr(const XilPdi_ImgHdrTable * IHdrTable);
u32 XilPdi_GetPufHdPh(const XilPdi_PrtnHdr * PrtnHdr);

#ifdef __cplusplus
}
#endif

#endif /* XILPDI_H */
