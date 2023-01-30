/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : EPS_DiagSrvcs_CommonData.h file
* Module Description: Common data shared between all the files.
* Product           : Gen II Plus - EA3.0
* Author            : Kevin Smith
*
* Notes:
* This file contains configurations that are shared between ISO and XCP services
* and is included in all the files.
*
**********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/* Version Control:
 * Date Created:      Mon Apr 12 10:20:00 2012
 * %version:          5 %
 * %derived_by:       kzdyfh %
 * %date_modified:    Thu Sep 19 12:34:58 2013 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 06/06/12     1       KS      Initial Component Release
 * 03/13/13     2       Jared   Brought in NRCs to house in central location                                    7225
 * 03/16/13     3       Jared   Added service sub type definitions for type 31 services                         7628
 * 07/12/13     4       Jared   QAC cleanup and NRC $7F addition                                                9033
 * 09/19/13     5       Jared   Added ECU Reset definition                                                      9610
 */
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include area >>                        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "Rte_type.h"
#include "NvM.h"
#include "osek.h"
#include "fpmtype.h"
#include "fixmath.h"
#include "GlobalMacro.h"
#include "Compiler.h"
#include "CalConstants.h"
#include "Ap_DfltConfigData.h"
#include "CDD_Data.h"
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of include area >>                          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

#ifndef EPS_DIAGSRVCS_COMMONDATA_H_
#define EPS_DIAGSRVCS_COMMONDATA_H_

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of custom include area >>                 DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of custom include area >>                   DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of custom define area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/* Switches to enable / disable the services */
#define D_DIAGSRVC_ENABLED					STD_ON
#define D_DIAGSRVC_DISABLED					STD_OFF

/* Common defines used in the diagnostic services */
#define D_PID_NOTACTIVE_CNT_U8				0x00
#define D_PID_ACTIVE_CNT_U8					0x01
#define D_PID_READONLY_CNT_U8				0x00
#define D_PID_READWRITE_CNT_U8				0x01
#define D_BIT0MASK_CNT_U16					0x0001U
#define D_BIT1MASK_CNT_U16					0x0002U
#define D_BIT2MASK_CNT_U16					0x0004U
#define D_BIT3MASK_CNT_U16					0x0008U
#define D_BIT4MASK_CNT_U16					0x0010U
#define D_BIT5MASK_CNT_U16					0x0020U
#define D_BIT6MASK_CNT_U16					0x0040U
#define D_BIT7MASK_CNT_U16					0x0080U
#define D_BYTEMASK_ULS_U8					0xFFU
#define D_NIBBLESHIFT_CNT_U16				4U
#define D_BYTESHIFT_CNT_U16					8U
#define D_BYTESHIFT_CNT_U8					8U
#define D_WORDBYTESHIFT_CNT_U16				12U
#define D_WORDSHIFT_CNT_U16					16U
#define D_MSBYTESHIFT_CNT_U16				24U
#define D_LOWERNIBBLEMASK_CNT_U16			0x0FU
#define D_UPPERNIBBLEMASK_CNT_U16			0xF0U
#define D_LOWERSIXBITSMASK_CNT_U16			0x3FU
#define D_LOWERBYTEBITSEVEN_CNT_U16			0x40U
#define d_LOWNIBUPBYTEMASK_CNT_U16			0x0F00U
#define D_UPPNIBUPBYTEMASK_CNT_U16			0xF000U
#define D_LOWERBYTEMASK_CNT_U16				0x00FFU
#define D_UPPERBYTEMASK_CNT_U16				0xFF00U
#define D_LOWERWORDBYTEMASK_CNT_U16			0x0FFFU
#define D_LOWBYTELOWORDMASK_CNT_U32			0x000000FFUL
#define D_LOWERWORDMASK_CNT_U32				0x0000FFFFUL
#define D_UPPERWORDMASK_CNT_U32				0xFFFF0000UL
#define D_UPPERNIBBLEMASK_CNT_U32			0xF0000000UL
#define D_FLOATMASK_CNT_U32					0xFFFFFFFFUL

/* MEC Values */
#define D_NXTRMEC_ENGMODE_CNT_U8			0xFFU
#define D_NXTRMEC_PRODMODE_CNT_U8			0x00U

/* Macros */
#define bytesToWord_m(x,y)					(((uint16)x << D_BYTESHIFT_CNT_U16) | (uint16)y)
#define uint32RightShftuint8_m(x,y)			(uint8)(((uint32)x >> y) & D_BYTEMASK_ULS_U8)
#define uint8LeftShftuint32_m(x,y)			(uint32)(((uint32)x << y) & D_FLOATMASK_CNT_U32)
#define MSB(x)								(uint8)(((uint16)x >> D_BYTESHIFT_CNT_U16) & D_BYTEMASK_ULS_U8)
#define LSB(x)								(uint8)((uint16)x & D_BYTEMASK_ULS_U8)

/* Service Type Definitions */
#define D_EPSRESETSRVC_CNT_U16				0x11U
#define D_EPSRDDATABYIDPID_CNT_U16			0x22U
#define D_EPSWRDATABYIDPID_CNT_U16			0x2EU
#define D_EPSIOCNTRLPID_CNT_U16				0x2FU
#define D_EPSRTNCNTRLPID_CNT_U16			0x31U

/* Type 11 Reset Services */
#define D_EPSRESET_ECURESET					0x60U

/* PID Function Read/Write Specifier */
#define D_SRVCREQTYPEREAD_CNT_U16			0x22U
#define D_SRVCREQTYPEWRITE_CNT_U16			0x2EU

/* Type 31 Service Sub-Function Types */
#define D_EPSRIDSUBSTART_CNT_U08			1U
#define D_EPSRIDSUBSTOP_CNT_U08				2U
#define D_EPSRIDSUBSTATUS_CNT_U08			3U

/* Type 2F Request type */
#define D_EPSIOCRETURNCTRL_CNT_U08			0U
#define D_EPSIOCSHRTTRMADJ_CNT_U08			3U

/* Configurable NRC Check Bit Masks */
#define D_EPSCHECKMEC_CNT_U16				0x0001U
#define D_EPSCHECKVEHSPD_CNT_U16			0x0002U
#define D_EPSCHECKHWVEL						0x0004U

/* Negative Response Codes */
#define D_EPSNRCNOERROR_CNT_U08								0x00U
#define D_EPSNRCSERVICENOTSUPPORTED_CNT_U16					0x11U
#define D_EPSNRCSUBFUNCNOTSUPP_CNT_U08						0x12U
#define D_EPSNRCINVALIDFORMAT_CNT_U08						0x13U
#define D_EPSNRCCONDNOTCORRECT_CNT_U08						0x22U
#define D_EPSNRCREQSEQUENCEERR_CNT_U08						0x24U
#define D_EPSNRCREQOUTOFRANGE_CNT_U08						0x31U
#define D_EPSNRCREQUESTPENDING_CNT_U08						0x78U
#define D_EPSNRCSERVICENOTSUPPORTEDINACTIVESESSION_CNT_U16	0x7FU
#define D_EPSNRCVEHSPDTHRSHOLD_CNT_U08						0x88U
#define D_EPSNRCMECEQZERO_CNT_U08							0xFBU
#define D_EPSNRCPOSSNSRCONDNOTCORRECT_CNT_U08				0xFCU
#define D_EPSNRCREQUESTDATAOUTOFRANGE_CNT_U08				0xFDU
#define D_EPSNRCHWTRQTHRSHOLD_CNT_U08						0xFEU

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of custom define area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
#endif /* EPS_DIAGSRVCS_COMMONDATA_H_ */
