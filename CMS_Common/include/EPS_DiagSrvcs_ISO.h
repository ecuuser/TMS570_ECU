/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : EPS_DiagSrvcs_ISO.h file
* Module Description: Common Manufacturing Program Interface for XCP and ISO services
* Product           : Gen II Plus - EA3.0
* Author            : Kevin Smith
*
* Notes:
* This file contains configurations for ISO services.
*
*****************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/* Version Control:
 * Date Created:      Mon Apr 12 10:20:00 2012
 * %version:          19 %
 * %derived_by:       gz7pm0 %
 * %date_modified:    Mon Jan 27 16:14:05 2014 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 06/06/12     1       KS      Initial Component Release
 * 09/26/12     2       Jared   Added new service (F005, FD26, FD27, FD29) for DiagMgr & AvgFricLrn
 * 10/18/12     3       Jared   Corrected anom 3645 for NRC compliance with spec v02A                           6401
 * 10/29/12     4       Jared   Added MaxIgnCntr to support move of ignition counter increment                  6344
 * 01/14/13     5       LN      Added Support for Customer Supported services that are IOCs (not PIDs)          6931
 * 01/25/13     6       Jared   Brought in F0FF from PSR485 source                                              7190
 * 03/11/13     7       Jared   Update to spec 04A and generation tool 2.0                                      7225
 * 03/18/13     8       Jared   Updated to support revamp of CMS structure                                      7628
 * 03/21/13     9       KJS     Corrected anomaly 4680 for MEC=0 NRCs for 0x22 services                         7690
 * 04/01/13     10      Jared   MISRA warning cleanup                                                           7750
 * 07/12/13     11      Jared   QAC Cleanup with ConfiguredNRCCheck prototype                                   9033
 * 09/19/13     13      Jared   Added new services and common service definitions (previously in Int. header)   9610
 * 09/27/13     14      LWW     Updated per integration issues of 06A version
 * 10/15/13     15      VK      Added F00F constants from interface header                                      10415
 * 10/15/13     16      Jared   Updated length for hardware description table and added F00F definitions into   10467
 *                              definitions area.  Removed ISOVAR table index definitions.
 * 11/26/13     17      Jared   Added definition for FD02 Mod Index bit 9                                       10859
 * 01/29/14		19		LK		Added definition for FD17														11298
 */
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include area >>		                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
#include "EPS_DiagSrvcs_CommonData.h"
#include "EPS_DiagSrvcs_SrvcLUTbl.h"
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of include area >>   		      		    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
#ifndef EPS_DIAGSRVCS_ISO_H
#define EPS_DIAGSRVCS_ISO_H

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of custom include area >>	                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
#include "EPS_DiagSrvcs_ISO.Interface.h"

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of custom include area >>	                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of custom define area >>   		  	    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

#define D_MAXIGNCNT_CNT_U16     65535U


/* Structure to share float data with serial comm data */
typedef struct EPS_DiagSrv_DataStr {
     union {
    	 float32 FloatData_f32;
    	 uint32  IntData_u32;
     }type;
} EPS_DiagSrv_DataStr;

typedef enum F00F_State {
    F00F_DEFAULT        = 0x00,
    F00F_ACTIVE         = 0x01,
    F00F_SUCCESS        = 0x02,
    F00F_CANCELLED      = 0x03,
    F00F_ERROR          = 0x04,
    F00F_NEXTEERMODE    = 0x0A,
    F00F_VEHSPD         = 0x0B,
    F00F_HANDSON        = 0x0C,
    F00F_OBSTRUCTION    = 0x0D
}F00FSTATE_Enum;

/* service function point type */
typedef uint8 (*DiagFuncRef)(VAR(uint8, EPSDIAGSRVCS_VAR) SubFunc_Cnt_T_u08, P2VAR(uint8, EPSDIAGSRVCS_VAR, EPSDIAGSRVCS_VAR) DataBuffer_Uls_T_u08, VAR(CM_MsgLenType, EPSDIAGSRVCS_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVCS_VAR, EPSDIAGSRVCS_VAR) RespLength_Cnt_T_u16);

/******************************************************************************
 *  --- GENERAL FUNCTION START ---
 *****************************************************************************/
extern FUNC(void, EPSDIAGSRVCS_CODE) EPS_DiagSessionChangeIndicator(CONST(uint8,EPSDIAGSRVCS_VAR) SesCtrlTypeOld, CONST(uint8,EPSDIAGSRVCS_VAR) SesCtrlTypeNew);
extern FUNC(void, EPSDIAGSRVCS_CODE) EPSDiagSrvcs_Task(void);
extern FUNC(void, EPSDIAGSRVCS_CODE) EPS_DiagSrvcs_Init(void);
extern FUNC(uint8, EPSDIAGSRVCS_CODE) DiagSrvcs_MainHandler(VAR(uint16, EPSDIAGSRVCS_VAR) ServiceId_Cnt_T_u16, VAR(uint8, EPSDIAGSRVCS_VAR) SubType_Cnt_T_u08, P2VAR(uint8, EPSDIAGSRVCS_VAR, EPSDIAGSRVCS_VAR) DataBuffer_Uls_T_u08, VAR(CM_MsgLenType, EPSDIAGSRVCS_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVCS_VAR, EPSDIAGSRVCS_VAR) RespLen_Cnt_T_u16);
FUNC(uint16, EPSXCPDIAGSRVCS_CODE) DiagSrvcs_PIDIdxSearch(VAR(uint16, EPSDIAGSRVCS_VAR) PID_Uls_T_u16);
FUNC(uint8, EPSDIAGSRVCS_CODE) DiagSrvcs_ConfiguredNrcCheck(VAR(uint16, EPSDIAGSRVCS_VAR) LUTidx_Uls_T_u16, VAR(uint8, EPSDIAGSRVCS_VAR) SubType_Cnt_T_u08);
FUNC(CM_Std_ReturnType, EPSDIAGSRVCS_CODE) DiagSrvcs_NRCTranslate(VAR(CM_Std_ReturnType, EPSDIAGSRVCS_VAR) DeveloperNrc);
extern FUNC(void, EPSDIAGSRVCS_CODE) NxtrMEC_Init(void);
extern FUNC(uint8, EPSDIAGSRVCS_CODE) DiagSrvNullFunc (VAR(uint8, EPSDIAGSRVCS_VAR) SubFunc_Cnt_T_u08, P2VAR(uint8, EPSDIAGSRVCS_VAR, EPSDIAGSRVCS_VAR) DataBuffer_Uls_T_u08, VAR(CM_MsgLenType, EPSDIAGSRVCS_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVCS_VAR, EPSDIAGSRVCS_VAR) RespLength_Cnt_T_u16);
STATIC FUNC(boolean, EPSDIAGSRVCS_CODE) HandsOnDetection(F00FSTATE_Enum RoutineStatus_Cnt_T_enum);
STATIC FUNC(F00FSTATE_Enum, CDC_USER_CODE) F00FCheckConditions (boolean CheckHwPosAuth);
FUNC(void, EPSDIAGSRVCS_CODE) ProcessF0FF(P2VAR(uint8, AUTOMATIC, AUTOMATIC) t_SrvcData_Cnt_T_u08, VAR(uint16, AUTOMATIC) RequestDataIdx_Cnt_T_u16);
/******************************************************************************
 *  --- GENERAL FUNCTION END ---
 *****************************************************************************/

/* -----[ Common Definitions ]--------------------------------------------------------------------------------------- */

#if (D_EPSDIAGSRVRIDF000_CNT_ENUM == D_DIAGSRVC_ENABLED)
	/* Control Byte 0 */
	#define D_F000NMEC_CNT_U32							0x000001U
	#define D_F000IGNCNTR_CNT_U32						0x000002U
	#define D_F000LTLVEHSPDCNTR_CNT_U32					0x000004U
	#define D_F000STOREDLASTPOSINVALD_CNT_U32			0x000008U
	#define D_F000TACHGAIN_CNT_U32						0x000010U
	#define D_F000SNSRLESSSTOREDLASTPOSINVALID_CNT_U32	0x000020U
	#define D_F000LEARNEDEOT_CNT_U32					0x000040U
	#define D_F000ACTIVEPULLCOMP_CNT_U32				0x000080U

	/* Control Byte 1 */
	#define D_F000NXTRDTCTBL_CNT_U32					0x000100U
	#define D_F000NXTRDTCBLACKBOX_CNT_U32				0x000200U
	#define D_F000CUSTDTCTBL_CNT_U32					0x000400U
	#define D_F000FRICTIONDETECTPARAM_CNT_U32			0x000800U
	#define D_F000WIRPARAM_CNT_U32						0x001000U
	#define D_F000INITLRNDTBLS_CNT_U32					0x002000U
	#define D_F000TRANSOVDATA_CNT_U32					0x004000U
	/* #define D_F000UNUSED1-8_CNT_U32					0x008000U */

	/* Control Byte 2 */
	/* #define D_F000UNUSED2-1_CNT_U32					0x010000U */
	/* #define D_F000UNUSED2-2_CNT_U32					0x020000U */
	/* #define D_F000UNUSED2-3_CNT_U32					0x040000U */
	/* #define D_F000UNUSED2-4_CNT_U32					0x080000U */
	/* #define D_F000UNUSED2-5_CNT_U32					0x100000U */
	/* #define D_F000UNUSED2-6_CNT_U32					0x200000U */
	/* #define D_F000UNUSED2-7_CNT_U32					0x400000U */
	/* #define D_F000UNUSED2-8_CNT_U32					0x800000U */
#endif

#if (D_EPSDIAGSRVRIDF00F_CNT_ENUM == D_DIAGSRVC_ENABLED)
	#define D_RIDF00FTRGTHWPOSLMT_HWDEGS_F32			800.0F
	#define D_RIDF00FTRGTHWVELLOLMT_DEGPS_F32			10.0F
	#define D_RIDF00FTRGTHWVELHILMT_DEGPS_F32			1000.0F
	#define D_RIDF00FTRGTHWVELSCALE_DEGPSPSEC_U16		10U
	#define D_RIDF00FTRGTHWACCELLOLMT_DEGSPSSQRD_F32	10.0F
	#define D_RIDF00FTRGTHWACCELHILMT_DEGSPSSQRD_F32	2000.0F
	#define D_RIDF00FTRGTHWACCELSCALE_DEGPSSQRDPCNT_U16	10U
	#define D_RIDF00FMAXCONF_ULS_F32					1.0F
	#define D_MAXHWPOSITION_HWDEG_F32					1440.11F
#endif

#if (D_EPSDIAGSRVPIDFD02_CNT_ENUM == D_DIAGSRVC_ENABLED)
	/* Defines specific to PID: FD02 */
	#define D_SVCDFTMODIDX_CNT_B32				0x00000200u
	#define D_SVCDFTRXMSGS_CNT_B32				0x08000000u
	#define D_SVCDFTMULTIGNMASK_CNT_B32			0x50000000u
#endif

#if (D_EPSDIAGSRVPIDFD0F_CNT_ENUM == D_DIAGSRVC_ENABLED)
	/* Defines specific to PID: FD0F */
	#include "DataLogistic.h"
	#define D_HARDWAREDESCTBLPIDSIZE_CNT_U16	59U
#endif

#if (D_EPSDIAGSRVPIDFDB0_CNT_ENUM == D_DIAGSRVC_ENABLED)
	/* Defines specific to PID: FDB0 */
	#define D_COGTRQ_LOOPLMT					128U
	#define D_FDB0ARRAYINDEXOFFSET_CNT_U16		0U
#endif

#if (D_EPSDIAGSRVPIDFDB1_CNT_ENUM == D_DIAGSRVC_ENABLED)
	/* Defines specific to PID: FDB1 */
	#define D_FDB1ARRAYINDEXOFFSET_CNT_U16		1U
#endif

#if (D_EPSDIAGSRVPIDFDB2_CNT_ENUM == D_DIAGSRVC_ENABLED)
	/* Defines specific to PID: FDB2 */
	#define D_FDB2ARRAYINDEXOFFSET_CNT_U16		2U
#endif

#if (D_EPSDIAGSRVPIDFDB3_CNT_ENUM == D_DIAGSRVC_ENABLED)
	/* Defines specific to PID: FDB3 */
	#define D_FDB3ARRAYINDEXOFFSET_CNT_U16		3U
#endif

#if (D_EPSDIAGSRVPIDFDB7_CNT_ENUM == D_DIAGSRVC_ENABLED)
	/* Defines specific to PID: FDB7 */
	#define D_FDB7ARRAYINDEXOFFSET_CNT_U16		4U
#endif


/****************************** BEGIN CMS GENERATION - DO NOT CHANGE/REMOVE THIS COMMENT ******************************/

/* Reset Services */
#if (D_EPSDIAGSRVRESET1160_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_RESET_1160 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_RESET_1160	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVRESET1160_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/* Routine I/O Services */
#if (D_EPSDIAGSRVRIDF000_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_RID_F000 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_RID_F000	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVRIDF000_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVRIDF001_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_RID_F001 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_RID_F001	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVRIDF001_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVRIDF002_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_RID_F002 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_RID_F002	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVRIDF002_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVRIDF003_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_RID_F003 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_RID_F003	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVRIDF003_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVRIDF004_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_RID_F004 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_RID_F004	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVRIDF004_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVRIDF005_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_RID_F005 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_RID_F005	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVRIDF005_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVRIDF006_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_RID_F006 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_RID_F006	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVRIDF006_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVRIDF007_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_RID_F007 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_RID_F007	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVRIDF007_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVRIDF008_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_RID_F008 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_RID_F008	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVRIDF008_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVRIDF009_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_RID_F009 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_RID_F009	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVRIDF009_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVRIDF00A_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_RID_F00A (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_RID_F00A	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVRIDF00A_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVRIDF00B_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_RID_F00B (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_RID_F00B	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVRIDF00B_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVRIDF00C_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_RID_F00C (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_RID_F00C	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVRIDF00C_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVRIDF00D_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_RID_F00D (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_RID_F00D	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVRIDF00D_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVRIDF00E_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_RID_F00E (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_RID_F00E	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVRIDF00E_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVRIDF00F_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_RID_F00F (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_RID_F00F	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVRIDF00F_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVRIDF0FF_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_RID_F0FF (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_RID_F0FF	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVRIDF0FF_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/* PID and I/O Control Services */
#if (D_EPSDIAGSRVPIDFD01_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD01 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FD01	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFD01_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFD02_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD02 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FD02	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFD02_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFD03_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD03 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FD03	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFD03_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFD04_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD04 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FD04	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFD04_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFD05_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD05 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FD05	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFD05_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFD06_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD06 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FD06	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFD06_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFD07_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD07 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FD07	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFD07_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFD08_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD08 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FD08	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFD08_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFD09_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD09 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FD09	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFD09_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFD0A_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD0A (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FD0A	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFD0A_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFD0B_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD0B (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FD0B	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFD0B_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFD0C_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD0C (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FD0C	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFD0C_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVIOCFD0D_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_IOC_FD0D (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_IOC_FD0D	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVIOCFD0D_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFD0E_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD0E (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FD0E	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFD0E_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFD0F_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD0F (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FD0F	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFD0F_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFD10_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD10 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FD10	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFD10_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVIOCFD11_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_IOC_FD11 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_IOC_FD11	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVIOCFD11_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFD12_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD12 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FD12	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFD12_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFD13_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD13 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FD13	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFD13_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFD14_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD14 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FD14	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFD14_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFD15_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD15 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FD15	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFD15_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFD16_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD16 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FD16	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFD16_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFD17_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD17 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FD17	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFD17_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFD18_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD18 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FD18	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFD18_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFD19_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD19 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FD19	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFD19_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFD1A_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD1A (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FD1A	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFD1A_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFD1B_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD1B (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FD1B	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFD1B_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFD1C_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD1C (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FD1C	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFD1C_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFD1D_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD1D (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FD1D	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFD1D_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFD1E_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD1E (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FD1E	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFD1E_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFD1F_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD1F (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FD1F	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFD1F_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFD20_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD20 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FD20	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFD20_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFD21_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD21 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FD21	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFD21_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFD22_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD22 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FD22	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFD22_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFD23_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD23 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FD23	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFD23_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFD24_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD24 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FD24	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFD24_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFD25_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD25 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FD25	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFD25_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFD26_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD26 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FD26	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFD26_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFD27_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD27 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FD27	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFD27_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFD28_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD28 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FD28	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFD28_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFD29_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD29 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FD29	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFD29_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFD30_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD30 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FD30	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFD30_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFD31_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD31 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FD31	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFD31_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFD41_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD41 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FD41	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFD41_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFDA0_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FDA0 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FDA0	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFDA0_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFDA1_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FDA1 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FDA1	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFDA1_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFDA2_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FDA2 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FDA2	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFDA2_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFDA3_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FDA3 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FDA3	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFDA3_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFDA4_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FDA4 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FDA4	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFDA4_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFDA5_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FDA5 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FDA5	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFDA5_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFDA7_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FDA7 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FDA7	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFDA7_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFDA8_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FDA8 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FDA8	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFDA8_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFDA9_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FDA9 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FDA9	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFDA9_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFDAC_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FDAC (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FDAC	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFDAC_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFDAD_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FDAD (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FDAD	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFDAD_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFDAE_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FDAE (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FDAE	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFDAE_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFDAF_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FDAF (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FDAF	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFDAF_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFDB0_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FDB0 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FDB0	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFDB0_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFDB1_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FDB1 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FDB1	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFDB1_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFDB2_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FDB2 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FDB2	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFDB2_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFDB3_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FDB3 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FDB3	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFDB3_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFDB4_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FDB4 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FDB4	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFDB4_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFDB5_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FDB5 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FDB5	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFDB5_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFDB6_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FDB6 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FDB6	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFDB6_CNT_ENUM == D_DIAGSRVC_ENABLED) */

#if (D_EPSDIAGSRVPIDFDB7_CNT_ENUM == D_DIAGSRVC_ENABLED)
	extern FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FDB7 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16);
#else
	#define EPSInternal_PID_FDB7	DiagSrvNullFunc
#endif /* (D_EPSDIAGSRVPIDFDB7_CNT_ENUM == D_DIAGSRVC_ENABLED) */

/******************************* END CMS GENERATION - DO NOT CHANGE/REMOVE THIS COMMENT *******************************/

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of custom define area >>	                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

#endif /* EPS_DIAGSRVCS_ISO_H */
