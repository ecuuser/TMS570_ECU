/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Ap_ApXcp.c
 *     Workspace:  C:/_swb/BMW/BMW_UKL_MCV_EPS_TMS570-UKL_F45/Xcp/autosar/Ap_ApXcp.dcf
 *     SW-C Type:  Ap_ApXcp
 *  Generated at:  Mon Oct 28 11:23:36 2013
 *
 *     Generator:  MICROSAR RTE Generator Version 2.19.1
 *       License:  License CBD1010124 valid for CBD1010124 Nexteer  Package: BMW MSR SIP BAC3.0     Micro: TI TMS570 TMS570LS30306  Compiler: Code Composer Studio 4.9.0
 *
 *   Description:  C-Code implementation template for SW-C <Ap_ApXcp>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/* Version Control:
 * Date Created:      Thu Dec  6 16:25:02 2012
 * %version:          11 %
 * %derived_by:       cz7lt6 %
 * %date_modified:    Thu Jan  9 14:46:34 2014 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 12/06/12  1        LWW       Initial Component Version
 * 01/02/13  2        JJW       Added 1ms DAQ
 * 01/14/13  3        JJW       Name change to provide uniqueness wihtin the namespace with the AUTOSAR Xcp module 
 * 07/09/13  4        JJW       Remove XcpEvent Rte runnables from this static file, they are to be generated based on
 *		 						the integration roject configuration.
 *								Added ApplXcpCheckDAQAcess() callback to support XcpProf versions greater than 1.27.xx
 * 07/11/13	 5		  KJS		Added support for phase 1 of tune-on-the-fly.
 * 07/25/13	 6		  LWW		Made External EEPROM and Tune on the Fly configurable to be on or off
 * 08/29/13	 7		  LWW		Added callout function to support XCP PID handling
 * 10/28/13	 8		  KJS		Added support for segment 16 and segments yet to be defined. Also updated #defs 
 *								for TOTF configuration options.
 * 11/04/13	 9		  KJS		Corrected coding error in Per1 for Segment16.
 * 11/12/13	 10		  LWW		Anomaly 6014 correction
 * 01/09/14	 11		  KJS		Anomaly 6186 correction
 */
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

#include "Rte_Ap_ApXcp.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
#define APXCP_C
#include "Ap_ApXcp.h"
#include "Mcu.h"
#include "SystemTime.h"
#include "EPS_DiagSrvcs_SrvcLUTbl.h"
#include "EPS_DiagSrvcs_XCP.Interface.h"
#include "EPS_DiagSrvcs_XCP.h"

#if (STD_ON == BC_XCP_EXTEEPACCESS)
	#include "Eep_30_At25128.h"
#endif

/* Local Embedded Constants */
#define D_LOWRANGEIDX_CNT_U8            0x0U
#define D_HIGHRANGEIDX_CNT_U8           0x1U

/* MTA Extension Code "enumeration" */
#define D_MTAEXTRAM_CNT_U8				0x00U
#define D_MTAEXTFLASH_CNT_U8			0x01U
#define D_MTAEXTEEPROM_CNT_U8			0x02U
#define D_MTAEXTNONE_CNT_U8				0x7FU
#define D_MTAEXTAPPSWITCHMSK_CNT_U8		0x80U

/* XCP Data Request "enumeration" */
#define D_XCPEEPROMREAD_CNT_U8			0x00U
#define D_XCPEEPROMWRITE_CNT_U8			0x01U
#define D_XCPNONE_CNT_U8				0xFFU

#if (STD_ON == BC_XCP_EXTEEPACCESS)
	/* Data Types */
	typedef struct XcpNvmReq {
		uint32 EeAddr_Cnt_u32;
		uint8 * pRamAddr_Cnt_u08;
		uint8 Size_Byte_u08;
		uint8 MemType_Cnt_u08;
	} XcpNvmReq_T;


	typedef struct XcpNvmReqState {
		boolean ReqPosted_Cnt_lgc;
		uint8 Outcome_Cnt_u08;
	} XcpNvmReqState_T;
#endif

/* XCP Tune on the fly */
#if (STD_ON == BC_XCP_TUNEONFLY)
	#define XCP_RespLen_m(x) 		xcp.CrmLen = x
	#define XCP_RespCmd_m(x)		CRM_CMD = x
	#define XCP_ErrCode_m(x)		CRM_ERR = x
	#define XCP_CAL_CMD_OK			0u /* From the tech ref, the error check looks for the return value to be 0, no error */
	#define D_MAX_SEGMENT_CNT_U8 	kXcpMaxSegment
	#define D_MAX_PAGES_CNT_U8		kXcpMaxPages

	typedef enum
	{
		XCP_CAL_ECU_ACCESS 		= CAL_ECU,
		XCP_CAL_XCP_ACCESS 		= CAL_XCP,
		XCP_CAL_XCP_ECU_ACCESS 	= (CAL_XCP | CAL_ECU),
		XCP_CAL_ALL_ACCESS 		= CAL_ALL /* Not supported by driver, but placed in to match spec */
	} XcpCalAccessModeType;

	typedef enum
	{
		XCP_FLASH_PAGE = 0u,
		XCP_RAM_PAGE = 1u
	} XcpPageTypes;

	typedef enum
	{
		XCP_PERS_SEG 				= 0u,
		XCP_SETS_SEG 				= 1u,
		XCP_COMMON_SEG 				= 2u,
		XCP_SETANDPER_SEG 			= 3u,
		XCP_SETANDPERANDCOMMON_SEG 	= 4u, /* 5 to 15 are reserved for Nexteer use */
		XCP_CUSTDEFMEMBLK 			= 16u
	} XcpSegTypes;

	typedef struct XcpCalIndexDetails{
		uint8	FlashIndex_Cnt_u8;
		uint32	RAMStartAddr_Cnt_u32;
		sint32	AddrOffset_Cnt_s32;
		uint32	Length_Cnt_u32;
	} XcpCalIndexDetails_T;

	typedef struct XcpCalPageDetails{
		uint8	PageAccess_Cnt_T_u8;
	} XcpCalPageDetails_T;


	typedef struct XcpCalStatus {
		uint8					XcpCalStrVer_Cnt_u8;
		XcpCalIndexDetails_T 	Data[BC_XCP_MAXPERCOPY_CNT_U8];
		uint8					ValidDataPts_Cnt_u8;
		uint16					ActiveTunSet_Cnt_16;
		uint16					ActiveTunPers_Cnt_16;
		uint8 					ActiveCalSegment_Cnt_u8;
		XcpCalPageDetails_T		Page[D_MAX_PAGES_CNT_U8];
		boolean 				CopyComplete_Cnt_lgc;
	} XcpCalStatus_T;

	typedef union {
		TUNING_P_Str 	Pers[BC_XCP_MAXPERCOPY_CNT_U8];
		TUNING_Y_Str 	Sets[BC_XCP_MAXSETCOPY_CNT_U8];
		uint32		 	Common[5]; /* Just to test */
		#if(BC_XCP_SEG16ENABLE == STD_ON)
			uint8		Seg16CustBlck[BC_XCP_TOTFRAMSIZE_CNT_U32];
		#endif
	} XcpCalStr_T;

	#define APXCP_START_SEC_VAR_INIT_UNSPECIFIED
	#include "MemMap.h"
		VAR(XcpCalStr_T, AP_APXCP_VAR) XcpCalStr;
		STATIC VAR(uint16, AP_APXCP_VAR) ActiveTuningSet_Cnt_M_u16;
		STATIC VAR(uint16, AP_APXCP_VAR) ActiveTuningPers_Cnt_M_u16;
	#define APXCP_STOP_SEC_VAR_INIT_UNSPECIFIED
	#include "MemMap.h"

	#define APXCP_START_SEC_VAR_CLEARED_UNSPECIFIED
	#include "MemMap.h"
		STATIC VAR(XcpCalStatus_T, AP_APXCP_VAR) XcpCalStatus_Cnt_M_str;
	#define APXCP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#include "MemMap.h"

	STATIC FUNC(void, AUTOMATIC) XcpSetError(VAR(uint8, AUTOMATIC) ErrCode);
	STATIC FUNC(uint8, AUTOMATIC) CreateXcpCalSession( VAR(uint8, AUTOMATIC) Segment_Cnt_T_u8);

	/* TODO: See if just including a header file can be done instead of manual extern */
	#if (BC_XCP_PERSINDEXLOOKUP == STD_ON)
		extern FUNC(void, AUTOMATIC) GetPersIndexes(VAR(uint8, AUTOMATIC) NumOfPers_Cnt_T_u8, P2VAR(uint8, AUTOMATIC, AUTOMATIC) data);
	#endif
	#if (BC_XCP_SETINDEXLOOKUP == STD_ON)
		extern FUNC(void, AUTOMATIC) GetSetIndexes(VAR(uint8, AUTOMATIC) NumOfPers_Cnt_T_u8, P2VAR(uint8, AUTOMATIC, AUTOMATIC) data);
	#endif
#endif

#if (STD_ON == BC_XCP_EXTEEPACCESS)
	#define APXCP_START_SEC_VAR_CLEARED_8
	#include "MemMap.h"
		STATIC VAR(uint8, AP_APXCP_VAR) NvmHandlerBuffer_Cnt_M_u08[D_XCP_TL_MAXCTO];
	#define APXCP_STOP_SEC_VAR_CLEARED_8
	#include "MemMap.h"

	#define APXCP_START_SEC_VAR_CLEARED_UNSPECIFIED
	#include "MemMap.h"
		STATIC VAR(XcpNvmReq_T, AP_APXCP_VAR) NvmRequest_Cnt_M_Str;
		STATIC VAR(XcpNvmReqState_T, AP_APXCP_VAR) NvmReqState_Cnt_M_Str;
	#define APXCP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#include "MemMap.h"

	#define APXCP_START_SEC_VAR_CLEARED_BOOLEAN
	#include "MemMap.h"
		STATIC VAR(boolean, AP_APXCP_VAR) NvmHandlerBusy_Cnt_M_lgc;
	#define APXCP_STOP_SEC_VAR_CLEARED_BOOLEAN
	#include "MemMap.h"

	STATIC FUNC(void, AP_APXCP_CODE) EERead(void);
	STATIC FUNC(void, AP_APXCP_CODE) EEWrite(void);
#endif

#define APXCP_START_SEC_VAR_NOINIT_8
#include "MemMap.h"
	STATIC VAR(uint8, AP_APXCP_VAR) MtaExt_Cnt_M_u08;
	STATIC VAR(uint8, AP_APXCP_VAR) Size_Cnt_M_u08;
#define APXCP_STOP_SEC_VAR_NOINIT_8
#include "MemMap.h"

#define APXCP_START_SEC_VAR_NOINIT_32
#include "MemMap.h"
	STATIC P2VAR(uint8, AP_APXCP_VAR, AUTOMATIC) WritePtr_Cnt_M_u08;
	STATIC P2VAR(uint8, AP_APXCP_VAR, AUTOMATIC) ReadPtr_Cnt_M_u08;
#define APXCP_STOP_SEC_VAR_NOINIT_32
#include "MemMap.h"

/* This constant can be changed to TRUE post-build to Defeat XCP memory check */
volatile CONST(boolean, AUTOMATIC) EnableTestMode_Cnt_lgc = FALSE;

/* Local Functions */
STATIC FUNC(uint8, AP_APXCP_CODE) CheckXcpAccess( const uint8* address, uint16 size );
STATIC FUNC(uint8, AUTOMATIC) GetFcnIdx(uint8 AppIdx_Cnt_T_u08);
STATIC FUNC(uint8, AUTOMATIC) GetAppIdx(uint8 Application_Cnt_T_u08);


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of include and declaration area >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *
 * Used AUTOSAR Data Types
 *
 **********************************************************************************************************************
 *
 * Primitive Types:
 * ================
 * UInt16: Integer in interval [0...65535] (standard type)
 * UInt32: Integer in interval [0...4294967295] (standard type)
 *
 * Enumeration Types:
 * ==================
 * TuningSessionAddrPtrEnum: Enumeration of integer in interval [0...255] with enumerators
 *   TUN_SESSION_PTR_PERS (0U)
 *   TUN_SESSION_PTR_SETS (1U)
 *   TUN_SESSION_PTR_COMMON (2U)
 *   TUN_SESSION_PTR_SETANDPER (3U)
 *   TUN_SESSION_PTR_SETANDPERANDCOMMON (4U)
 *   TUN_SESSION_PTR_CUSTSEG (16U)
 *   TUN_SESSION_PTR_DISABLED (255U)
 *
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *
 * Defined Constants
 *
 **********************************************************************************************************************
 *
 * Primitive Type Constants:
 * =========================
 * UInt16: D_ZERO_CNT_U16 = 0U
 * UInt32: D_ZERO_CNT_U32 = 0U
 *
 *********************************************************************************************************************/


#define RTE_START_SEC_AP_APXCP_APPL_CODE
#include "MemMap.h"

/**********************************************************************************************************************
 *
 * Runnable Entity Name: ApXcp_Per1
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 10ms
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Implicit S/R API:
 *   -----------------
 *   UInt16 Rte_IRead_ApXcp_Per1_ActiveTunPers_Cnt_u16(void)
 *   UInt16 Rte_IRead_ApXcp_Per1_ActiveTunSet_Cnt_u16(void)
 *   UInt16 Rte_IRead_ApXcp_Per1_DesiredTunPers_Cnt_u16(void)
 *   UInt16 Rte_IRead_ApXcp_Per1_DesiredTunSet_Cnt_u16(void)
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_ApXcp_Per1_ActiveTunOvrPtrAddr_Cnt_u32(UInt32 data)
 *   UInt32 *Rte_IWriteRef_ApXcp_Per1_ActiveTunOvrPtrAddr_Cnt_u32(void)
 *   void Rte_IWrite_ApXcp_Per1_TuningSessionActPtr_Cnt_u8(TuningSessionAddrPtrEnum data)
 *   TuningSessionAddrPtrEnum *Rte_IWriteRef_ApXcp_Per1_TuningSessionActPtr_Cnt_u8(void)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_APXCP_APPL_CODE) ApXcp_Per1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: ApXcp_Per1
 *********************************************************************************************************************/
	#if (STD_ON == BC_XCP_TUNEONFLY)
		VAR(uint16, AUTOMATIC) DesiredTunPers_Cnt_T_u16;
		VAR(uint16, AUTOMATIC) DesiredTunSet_Cnt_T_u16;
		VAR(uint8, AUTOMATIC) i;
	#endif

	VAR(uint32, AUTOMATIC) TunSessionAddrPtr_Cnt_T_u32 = 0u;
	VAR(TuningSessionAddrPtrEnum, AUTOMATIC) TuningSessionActPtr_Cnt_T_u8 = TUN_SESSION_PTR_DISABLED;

	#if (STD_ON == BC_XCP_EXTEEPACCESS)
		/* NvM XCP Management */
		switch(NvmRequest_Cnt_M_Str.MemType_Cnt_u08)
		{
		
			case D_XCPEEPROMREAD_CNT_U8:
				EERead();
			break;
			case D_XCPEEPROMWRITE_CNT_U8:
				EEWrite();
			break;
			default:
				/* Do nothing */
			break;
		}
	#endif

	#if (STD_ON == BC_XCP_TUNEONFLY)
		/* Tuning Session Management */

		ActiveTuningPers_Cnt_M_u16 = Rte_IRead_ApXcp_Per1_ActiveTunPers_Cnt_u16();
		ActiveTuningSet_Cnt_M_u16 = Rte_IRead_ApXcp_Per1_ActiveTunSet_Cnt_u16();
		DesiredTunPers_Cnt_T_u16 = Rte_IRead_ApXcp_Per1_DesiredTunPers_Cnt_u16();
		DesiredTunSet_Cnt_T_u16 = Rte_IRead_ApXcp_Per1_DesiredTunSet_Cnt_u16();

		if( ((XcpCalStatus_Cnt_M_str.Page[XCP_RAM_PAGE].PageAccess_Cnt_T_u8 & XCP_CAL_ECU_ACCESS) != 0U) &&
			(XcpCalStatus_Cnt_M_str.CopyComplete_Cnt_lgc == TRUE))
		{
			/* ECU should access RAM page if it is the correct set/pers combo */
			for (i = 0U; i < XcpCalStatus_Cnt_M_str.ValidDataPts_Cnt_u8; i++)
			{
				switch(XcpCalStatus_Cnt_M_str.ActiveCalSegment_Cnt_u8)
				{
					case XCP_PERS_SEG:
						if( (XcpCalStatus_Cnt_M_str.ActiveTunSet_Cnt_16 == ActiveTuningSet_Cnt_M_u16) &&
							(XcpCalStatus_Cnt_M_str.Data[i].FlashIndex_Cnt_u8 == DesiredTunPers_Cnt_T_u16) )
						{
							/* Match was found with what was copied in RAM */
							TuningSessionActPtr_Cnt_T_u8 = TUN_SESSION_PTR_PERS;
							TunSessionAddrPtr_Cnt_T_u32 = XcpCalStatus_Cnt_M_str.Data[i].RAMStartAddr_Cnt_u32;
							break;
						}
					break;
					case XCP_SETS_SEG:
						if( XcpCalStatus_Cnt_M_str.Data[i].FlashIndex_Cnt_u8 == DesiredTunSet_Cnt_T_u16)
						{
							/* Match was found with what was copied in RAM */
							TuningSessionActPtr_Cnt_T_u8 = TUN_SESSION_PTR_SETS;
							TunSessionAddrPtr_Cnt_T_u32 = XcpCalStatus_Cnt_M_str.Data[i].RAMStartAddr_Cnt_u32;
							break;
						}
					break;
					case XCP_CUSTDEFMEMBLK:
						TuningSessionActPtr_Cnt_T_u8 = TUN_SESSION_PTR_CUSTSEG;
						TunSessionAddrPtr_Cnt_T_u32 = XcpCalStatus_Cnt_M_str.Data[i].RAMStartAddr_Cnt_u32;
					break;
					case XCP_COMMON_SEG:
					case XCP_SETANDPER_SEG:
					case XCP_SETANDPERANDCOMMON_SEG:
					default:
						/* TODO: Complete when Common group is defined. Set the active pointer to disabled until
						 * this section can be completed. Afterwhich it can be set to TUN_SESSION_PTR_COMMON */

						/* Default case should always disable and revert to flash */
						TuningSessionActPtr_Cnt_T_u8 = TUN_SESSION_PTR_DISABLED;
					break;
				}
			}
		}
		else
		{
			TuningSessionActPtr_Cnt_T_u8 = TUN_SESSION_PTR_DISABLED;
		}
	#endif

	/* Update outputs */
	Rte_IWrite_ApXcp_Per1_ActiveTunOvrPtrAddr_Cnt_u32(TunSessionAddrPtr_Cnt_T_u32);
	Rte_IWrite_ApXcp_Per1_TuningSessionActPtr_Cnt_u8(TuningSessionActPtr_Cnt_T_u8);

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

#define RTE_STOP_SEC_AP_APXCP_APPL_CODE
#include "MemMap.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of function definition area >>            DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/* GLOBAL FUNCTIONS */
/*****************************************************************************
  * Name:        ApXcp_Init
  * Description: XCP application initialization  
  * Inputs:      None 
  * Outputs:     None
  *
*****************************************************************************/
FUNC(void, XCP_CODE) ApXcp_Init(void)
{
	CopyCalsToRam();
	MtaExt_Cnt_M_u08 = D_MTAEXTNONE_CNT_U8;
#if (STD_ON == BC_XCP_EXTEEPACCESS)
	NvmRequest_Cnt_M_Str.MemType_Cnt_u08 = D_XCPNONE_CNT_U8;
#endif
}

/*****************************************************************************
  * Name:        ApXcpWriteCommon
  * Description: Function that performs the XCP write to memory
  * Inputs:      None 
  * Outputs:     None
  *
*****************************************************************************/
FUNC(void, AP_APXCP_CODE) ApXcpWriteCommon(void)
{
	VAR(uint8, AUTOMATIC) i;

	/* Verify test mode writing is enabled or abandon write */
	if (TRUE == EnableTestMode_Cnt_lgc)
	{
		for (i = 0; i < Size_Cnt_M_u08; i++)
		{
			WritePtr_Cnt_M_u08[i] = ReadPtr_Cnt_M_u08[i];
		}
	}
}

/* LOCAL FUNCTIONS */

/*****************************************************************************
 * Name:        GetFcnIdx
 * Description: Get the non-trusted or trusted function Index
 * Inputs:      None
 * Outputs:     None
 *****************************************************************************/
STATIC FUNC(uint8, AUTOMATIC) GetFcnIdx(uint8 AppIdx_Cnt_T_u08)
{
	return (T_FunctionIndex_Cnt_u08[AppIdx_Cnt_T_u08]);
}

/*****************************************************************************
 * Name:        GetAppIdx
 * Description: Get the application index number
 * Inputs:      None
 * Outputs:     None
 *****************************************************************************/
STATIC FUNC(uint8, AUTOMATIC) GetAppIdx(uint8 Application_Cnt_T_u08)
{
	VAR(uint8, AUTOMATIC) AppIdx_Cnt_T_u08 = 0xFFU;
	VAR(uint8, AUTOMATIC) i;

	for (i=0; i < D_NUMOFOSAPPS_CNT_U8; i++)
	{
		if (T_AppIndex_Cnt_u08[i] == Application_Cnt_T_u08)
		{
			AppIdx_Cnt_T_u08 = i;
		}
	}

	return (AppIdx_Cnt_T_u08);
}

#if (STD_ON == BC_XCP_EXTEEPACCESS)
/*****************************************************************************
 * Name:        EERead
 * Description: Request read from EEPROM and transmit response when complete.
 * Inputs:      None 
 * Outputs:     None
 *****************************************************************************/
STATIC FUNC(void, AP_APXCP_CODE) EERead(void)
{
	VAR(MemIf_StatusType, AUTOMATIC) NvmReqSts_Cnt_T_u08;
	VAR(MemIf_JobResultType, AUTOMATIC) NvmJobRes_Cnt_T_u08;
	P2VAR(uint8, AUTOMATIC, AUTOMATIC) pRspBuf_Cnt_T_u08;
	P2VAR(uint8, AUTOMATIC, AUTOMATIC) pRspData_Cnt_T_u08;
	
	/* setup for a new request if appropriate */
	if(TRUE != NvmHandlerBusy_Cnt_M_lgc)
	{
		NvmHandlerBusy_Cnt_M_lgc = TRUE;
		NvmReqState_Cnt_M_Str.ReqPosted_Cnt_lgc = FALSE;
		NvmReqState_Cnt_M_Str.Outcome_Cnt_u08 = XCP_CMD_PENDING;
	}
	
	/* check driver status to post the request or determine the result */
	NvmReqSts_Cnt_T_u08 = Eep_30_At25128_GetStatus();
	if(MEMIF_IDLE == NvmReqSts_Cnt_T_u08)
	{
		if(FALSE == NvmReqState_Cnt_M_Str.ReqPosted_Cnt_lgc)
		{
			if(E_OK != Eep_30_At25128_Read((Eep_30_At25128_AddressType)NvmRequest_Cnt_M_Str.EeAddr_Cnt_u32,
						&(NvmHandlerBuffer_Cnt_M_u08[0]),
						(Eep_30_At25128_LengthType)NvmRequest_Cnt_M_Str.Size_Byte_u08))
			{
				NvmReqState_Cnt_M_Str.Outcome_Cnt_u08 = CRC_ACCESS_DENIED;
			}
			
			NvmReqState_Cnt_M_Str.ReqPosted_Cnt_lgc = TRUE;
		}
		
		NvmJobRes_Cnt_T_u08 = Eep_30_At25128_GetJobResult();
		if(MEMIF_JOB_PENDING != NvmJobRes_Cnt_T_u08)
		{
			if(MEMIF_JOB_OK == NvmJobRes_Cnt_T_u08)
			{
				NvmReqState_Cnt_M_Str.Outcome_Cnt_u08 = XCP_CMD_OK;
			}
			else
			{
				NvmReqState_Cnt_M_Str.Outcome_Cnt_u08 = CRC_GENERIC;
			}
		}
	}
	
	/* finalize if possible */
	if(XCP_CMD_PENDING != NvmReqState_Cnt_M_Str.Outcome_Cnt_u08)
	{
		pRspBuf_Cnt_T_u08 = NvmRequest_Cnt_M_Str.pRamAddr_Cnt_u08;
		if(XCP_CMD_OK == NvmReqState_Cnt_M_Str.Outcome_Cnt_u08)
		{
			*pRspBuf_Cnt_T_u08 = PID_RES;
			pRspBuf_Cnt_T_u08++;
			pRspData_Cnt_T_u08 = &(NvmHandlerBuffer_Cnt_M_u08[0]);
			
			/* copy data to xcp response buffer */
			while(NvmRequest_Cnt_M_Str.Size_Byte_u08 > 0)
			{
				(*pRspBuf_Cnt_T_u08) = (*pRspData_Cnt_T_u08);
				pRspBuf_Cnt_T_u08++; pRspData_Cnt_T_u08++;
				NvmRequest_Cnt_M_Str.Size_Byte_u08--;
			}
		}
		else /* negative response */
		{
			*pRspBuf_Cnt_T_u08 = PID_ERR;
			pRspBuf_Cnt_T_u08++;
			*pRspBuf_Cnt_T_u08 = NvmReqState_Cnt_M_Str.Outcome_Cnt_u08;
		}
		
		/* transmit the response */
		XcpSendCrm();
		
		/* invalidate the current request and signal handler is not busy */
		NvmRequest_Cnt_M_Str.MemType_Cnt_u08 = D_XCPNONE_CNT_U8;
		NvmHandlerBusy_Cnt_M_lgc = FALSE;
	}
}

/*****************************************************************************
 * Name:        EEWrite
 * Description: Request write to EEPROM and transmit response when complete.
 * Inputs:      None 
 * Outputs:     None
 *****************************************************************************/
STATIC FUNC(void, AP_APXCP_CODE) EEWrite(void)
{
	VAR(MemIf_StatusType, AUTOMATIC) NvmReqSts_Cnt_T_u08;
	VAR(MemIf_JobResultType, AUTOMATIC) NvmJobRes_Cnt_T_u08;
		
	/* setup for a new request if appropriate */
	if(TRUE != NvmHandlerBusy_Cnt_M_lgc)
	{
		NvmHandlerBusy_Cnt_M_lgc = TRUE;
		NvmReqState_Cnt_M_Str.ReqPosted_Cnt_lgc = FALSE;
		NvmReqState_Cnt_M_Str.Outcome_Cnt_u08 = XCP_CMD_PENDING;
	}
	
	/* check driver status and post the request if possible */
	NvmReqSts_Cnt_T_u08 = Eep_30_At25128_GetStatus();
	if(MEMIF_IDLE == NvmReqSts_Cnt_T_u08)
	{
		if(FALSE == NvmReqState_Cnt_M_Str.ReqPosted_Cnt_lgc)
		{
			if(E_OK != Eep_30_At25128_Write((Eep_30_At25128_AddressType)NvmRequest_Cnt_M_Str.EeAddr_Cnt_u32,
						&(NvmHandlerBuffer_Cnt_M_u08[0]),
						(Eep_30_At25128_LengthType)NvmRequest_Cnt_M_Str.Size_Byte_u08))
			{
				NvmReqState_Cnt_M_Str.Outcome_Cnt_u08 = CRC_ACCESS_DENIED;
			}
			
			NvmReqState_Cnt_M_Str.ReqPosted_Cnt_lgc = TRUE;
		}
		
		NvmJobRes_Cnt_T_u08 = Eep_30_At25128_GetJobResult();
		if(MEMIF_JOB_PENDING != NvmJobRes_Cnt_T_u08)
		{
			if(MEMIF_JOB_OK == NvmJobRes_Cnt_T_u08)
			{
				NvmReqState_Cnt_M_Str.Outcome_Cnt_u08 = XCP_CMD_OK;
			}
			else
			{
				NvmReqState_Cnt_M_Str.Outcome_Cnt_u08 = CRC_GENERIC;
			}
		}
	}
	
	/* finalize if possible */
	if(XCP_CMD_PENDING != NvmReqState_Cnt_M_Str.Outcome_Cnt_u08)
	{
		/* transmit the response */
		XcpSendCrm();
		
		/* invalidate the current request and signal handler is not busy */
		NvmRequest_Cnt_M_Str.MemType_Cnt_u08 = D_XCPNONE_CNT_U8;
		NvmHandlerBusy_Cnt_M_lgc = FALSE;
	}
}
#endif
/*****************************************************************************
 * Name:        CheckXcpAccess
 * Description: Determine whether a request with these parameters is valid. 
 * Inputs:      Target address and the length of target data.
 * Outputs:     Whether the request would be valid
 *****************************************************************************/
STATIC FUNC(uint8, AP_APXCP_CODE) CheckXcpAccess( const uint8* address, uint16 size )
{
	VAR(uint8, AUTOMATIC) Outcome_Cnt_T_u08;
	VAR(uint8, AUTOMATIC) i;

	Outcome_Cnt_T_u08 = XCP_CMD_DENIED;

	if (size == 0U)
	{
		/* Keep Denied Status */
	}
	else if ((EnableTestMode_Cnt_lgc == TRUE) && (NxtrMEC_Uls_G_enum == EngineeringMode))
	{
		/* Bypass all memory checks */
		switch(MtaExt_Cnt_M_u08)
		{
			case D_MTAEXTRAM_CNT_U8:
		#if (STD_ON == BC_XCP_EXTEEPACCESS)
			case D_MTAEXTEEPROM_CNT_U8:
		#endif
			case 0xFF:
				Outcome_Cnt_T_u08 = XCP_CMD_OK;
			break;
		#if (STD_OFF == BC_XCP_EXTEEPACCESS)
			case D_MTAEXTEEPROM_CNT_U8:
			/* Leave access denied if External EEP Access is turned off */
			break;
		#endif
			default:
				/* If using extension to switch to application, check that the application is valid */
				if (MtaExt_Cnt_M_u08 >= D_MTAEXTAPPSWITCHMSK_CNT_U8)
				{
					if (GetAppIdx(MtaExt_Cnt_M_u08 - D_MTAEXTAPPSWITCHMSK_CNT_U8) != 0xFF)
					{
						Outcome_Cnt_T_u08 = XCP_CMD_OK;
					}
				}
			break;
		}
	}
	else
	{
		switch(MtaExt_Cnt_M_u08)
		{
			case D_MTAEXTRAM_CNT_U8:
			case D_MTAEXTFLASH_CNT_U8:
				/* Check for address in valid memory regions */
				for (i = 0; i < D_NUMOFVLDMEMRGNS_CNT_U08; i++)
				{
					if (((uint32)address >= T_AllowedMemRegion_Cnt_u32[i][D_LOWRANGEIDX_CNT_U8]) &&
						(((uint32)address + (uint32)size - 1) <= T_AllowedMemRegion_Cnt_u32[i][D_HIGHRANGEIDX_CNT_U8]))
					{
						Outcome_Cnt_T_u08 = XCP_CMD_OK;
					}
				}
			break;
			case D_MTAEXTEEPROM_CNT_U8:
			#if (STD_ON == BC_XCP_EXTEEPACCESS) /* Leave access denied if External EEP Access is turned off */
				if (FALSE == NvmHandlerBusy_Cnt_M_lgc)
				{
					/* Check for address in valid memory regions */
					for (i = 0; i < D_NUMOFVLDEEMEMRGNS_CNT_U08; i++)
					{
						if (((uint32)address >= T_AllowedEEMemRegion_Cnt_u32[i][D_LOWRANGEIDX_CNT_U8]) &&
							(((uint32)address + (uint32)size - 1) <= T_AllowedEEMemRegion_Cnt_u32[i][D_HIGHRANGEIDX_CNT_U8]))
						{
							Outcome_Cnt_T_u08 = XCP_CMD_OK;
						}
					}
				}
			#endif
			break;
			case 0xFF:
				Outcome_Cnt_T_u08 = XCP_CMD_OK;
			break;
			default:
				/* Keep Denied Status - All other memory extensions are not supported in this mode */
			break;
		}
	}

	return(Outcome_Cnt_T_u08);
}

/* CALLOUT FUNCTIONS */
/* *********** CALLBACK: ApplXcpGetPointer ************************************** */
FUNC(uint8*, XCP_CODE) ApplXcpGetPointer( uint8 addr_ext, uint32 addr )
{
	MtaExt_Cnt_M_u08 = addr_ext; 
	
	return((uint8*)addr);
}

/* *********** CALLBACK: ApplXcpGetTimestamp ************************************** */
FUNC(XcpDaqTimestampType, XCP_CODE) ApplXcpGetTimestamp( void )
{
  uint32 time_uS_u32;
  
  GetSystemTime_uS_u32(&time_uS_u32);

  return(time_uS_u32);
}

/* *********** CALLBACK: ApplXcpReset ************************************** */
FUNC(void, XCP_CODE) ApplXcpReset( void )
{
	Mcu_PerformReset();
}

/* *********** CALLBACK: ApplXcpFlashClear ************************************** */
FUNC(uint8, XCP_CODE) ApplXcpFlashClear( uint8* address, uint32 size )
{
	return XCP_CMD_ERROR;
}

/* *********** CALLBACK: ApplXcpFlashProgram ************************************** */
FUNC(uint8, XCP_CODE) ApplXcpFlashProgram( const uint8* data, uint8* address, uint8 size )
{
	return XCP_CMD_ERROR;
}

/* *********** CALLBACK: ApplXcpProgramStart ************************************** */
FUNC(uint8, XCP_CODE) ApplXcpProgramStart( void )
{
	return XCP_CMD_ERROR;
}

/* *********** CALLBACK: ApplXcpCheckReadEEPROM ************************************** */
FUNC(uint8, XCP_CODE) ApplXcpCheckReadAccess( const uint8* address, uint16 size )
{
	return CheckXcpAccess(address, size);
}

/* *********** CALLBACK: ApplXcpCheckReadEEPROM ************************************** */
FUNC(uint8, XCP_CODE) ApplXcpCheckReadEEPROM( uint8* addr, uint8 size, uint8* data )
{
	VAR(uint8, AUTOMATIC) Outcome_Cnt_T_u08 = XCP_CMD_DENIED;
	
	if(D_MTAEXTEEPROM_CNT_U8 == MtaExt_Cnt_M_u08)
	{
		#if (STD_ON == BC_XCP_EXTEEPACCESS)
			/* data points to beginning of transmit data,
				go to begining of entire message */
			data--; 
			
			/* capture the request */
			NvmRequest_Cnt_M_Str.EeAddr_Cnt_u32 = (uint32)addr;
			NvmRequest_Cnt_M_Str.pRamAddr_Cnt_u08 = data;
			NvmRequest_Cnt_M_Str.Size_Byte_u08 = size;
			NvmRequest_Cnt_M_Str.MemType_Cnt_u08 = D_XCPEEPROMREAD_CNT_U8;
			
			/* let the periodic handle the data access */
			Outcome_Cnt_T_u08 = XCP_CMD_PENDING;
		#endif
	}
	
	return(Outcome_Cnt_T_u08);
}

/* *********** CALLBACK: ApplXcpCheckWriteAccess ************************************** */
FUNC(uint8, XCP_CODE) ApplXcpCheckWriteAccess( const uint8* address, uint8 size )
{
	return CheckXcpAccess(address, size);
}

/* *********** CALLBACK: ApplXcpCheckDAQAccess ************************************** */
FUNC(uint8, XCP_CODE) ApplXcpCheckDAQAccess( uint8* address, uint8 size )
{
	return CheckXcpAccess(address, size);
}

/* *********** CALLBACK: ApplXcpCheckWriteEEPROM ************************************** */
FUNC(uint8, XCP_CODE) ApplXcpCheckWriteEEPROM( uint8* addr, uint8 size, const uint8* data )
{
	VAR(uint8, AUTOMATIC) Outcome_Cnt_T_u08 = XCP_CMD_DENIED;
	
	if(D_MTAEXTEEPROM_CNT_U8 == MtaExt_Cnt_M_u08)
	{	
		#if (STD_ON == BC_XCP_EXTEEPACCESS)
			VAR(uint8, AUTOMATIC) index;

			/* copy data to module buffer */
			for(index=0;index<size;index++)
			{ NvmHandlerBuffer_Cnt_M_u08[index] = data[index]; }
			
			/* capture the request */
			NvmRequest_Cnt_M_Str.EeAddr_Cnt_u32 = (uint32)addr;
			NvmRequest_Cnt_M_Str.pRamAddr_Cnt_u08 = &(NvmHandlerBuffer_Cnt_M_u08[0]);
			NvmRequest_Cnt_M_Str.Size_Byte_u08 = size;
			NvmRequest_Cnt_M_Str.MemType_Cnt_u08 = D_XCPEEPROMWRITE_CNT_U8;
			
			/* let the periodic handle the data access */
			Outcome_Cnt_T_u08 = XCP_CMD_PENDING;
		#endif
	}
	
	return(Outcome_Cnt_T_u08);
}

/* *********** CALLBACK: ApplXcpCalibrationRead ************************************** */
FUNC(uint8, XCP_CODE) ApplXcpCalibrationRead( uint8* addr, uint8 size, uint8* data )
{
	VAR(uint8, AUTOMATIC) i;

	#if (STD_ON == BC_XCP_TUNEONFLY)
		VAR(uint8, AUTOMIATC) x;
		VAR(uint32, AUTOMATIC) FlshAddr_Cnt_T_u32;
		VAR(uint8, AUTOMATIC) RamDataIdx_Cnt_T_u8;
		VAR(boolean, AUTOMATIC) XcpCalFound_Cnt_T_lgc;
		VAR(uint32, AUTOMATIC) FlshAccessStart_Cnt_T_u32;

		for (i = 0U; i < size; i++)
		{
			FlshAddr_Cnt_T_u32 = (uint32)&(addr[i]);
			XcpCalFound_Cnt_T_lgc = FALSE;

			/* The check below is for tuning sessions checks. If XCP has RAM page access the requested read should be read
			 * from RAM instead of flash if the value being read is part of the tuning structure that was copied into RAM.
			 * The check will apply an offset if it is found within the range of data that was copied.
			 */
			if((XcpCalStatus_Cnt_M_str.Page[XCP_RAM_PAGE].PageAccess_Cnt_T_u8 & XCP_CAL_XCP_ACCESS) != 0u)
			{
				for(x = 0U; x < XcpCalStatus_Cnt_M_str.ValidDataPts_Cnt_u8; x++)
				{
					FlshAccessStart_Cnt_T_u32 = XcpCalStatus_Cnt_M_str.Data[x].RAMStartAddr_Cnt_u32 - XcpCalStatus_Cnt_M_str.Data[x].AddrOffset_Cnt_s32;
					if( (FlshAddr_Cnt_T_u32 >= FlshAccessStart_Cnt_T_u32) && (FlshAddr_Cnt_T_u32 < (FlshAccessStart_Cnt_T_u32 + XcpCalStatus_Cnt_M_str.Data[x].Length_Cnt_u32)) )
					{
						RamDataIdx_Cnt_T_u8 = x;
						XcpCalFound_Cnt_T_lgc = TRUE;
						break;
					}
				}
			}

			/* Read the data */
			if (XcpCalFound_Cnt_T_lgc == TRUE)
			{
				data[i] = addr[(i + XcpCalStatus_Cnt_M_str.Data[RamDataIdx_Cnt_T_u8].AddrOffset_Cnt_s32)];
			}
			else
			{
				data[i] = addr[i];
			}
		}
	#else
		for (i = 0U; i < size; i++)
		{
			data[i] = addr[i];
		}
	#endif

	return(XCP_CMD_OK);
}

/* *********** CALLBACK: ApplXcpCalibrationWrite ************************************** */
FUNC(uint8, XCP_CODE) ApplXcpCalibrationWrite( uint8* addr, uint8 size, const uint8* data )
{
	VAR(uint8, AUTOMATIC) Outcome_Cnt_T_u08;
	VAR(uint8, AUTOMATIC) AppIdx_Cnt_T_u08;
	VAR(uint8, AUTOMATIC) FcnIdx_Cnt_T_u08;
	VAR(uint8, AUTOMATIC) i;

	#if (STD_ON == BC_XCP_TUNEONFLY)
		VAR(uint8, AUTOMIATC) x;
		VAR(uint32, AUTOMATIC) FlshAddr_Cnt_T_u32;
		VAR(uint8, AUTOMATIC) RamDataIdx_Cnt_T_u8;
		VAR(boolean, AUTOMATIC) XcpCalFound_Cnt_T_lgc;
		VAR(uint32, AUTOMATIC) FlshAccessStart_Cnt_T_u32;
	#endif

	WritePtr_Cnt_M_u08 = addr;
	ReadPtr_Cnt_M_u08 = (uint8*)data;
	Size_Cnt_M_u08 = size;

	if (D_MTAEXTAPPSWITCHMSK_CNT_U8 ==(D_MTAEXTAPPSWITCHMSK_CNT_U8 & MtaExt_Cnt_M_u08))
	{
		AppIdx_Cnt_T_u08 = GetAppIdx(MtaExt_Cnt_M_u08 - D_MTAEXTAPPSWITCHMSK_CNT_U8);

		if ((AppIdx_Cnt_T_u08 != 0xFF) && (EnableTestMode_Cnt_lgc == TRUE) && (NxtrMEC_Uls_G_enum == EngineeringMode))
		{
			FcnIdx_Cnt_T_u08 = GetFcnIdx(AppIdx_Cnt_T_u08);

			if (AppIdx_Cnt_T_u08 == GetApplicationID())
			{
				/* No application switch needed, directly copy memory */
				for (i = 0; i < Size_Cnt_M_u08; i++)
				{
					WritePtr_Cnt_M_u08[i] = ReadPtr_Cnt_M_u08[i];
				}
			}
			else if (TRUE == oskApplIsTrusted[AppIdx_Cnt_T_u08])
			{
				(void)CallTrustedFunction(FcnIdx_Cnt_T_u08, NULL_PTR);
			}
			else
			{
				(void)CallNonTrustedFunction(FcnIdx_Cnt_T_u08, NULL_PTR);
			}

			Outcome_Cnt_T_u08 = XCP_CMD_OK;
		}
		else
		{
			Outcome_Cnt_T_u08 = XCP_CMD_DENIED;
		}
	}
	else
	{
		/* No application switch needed, directly copy memory */

		#if (STD_ON == BC_XCP_TUNEONFLY)
			/* TODO: For phase one of tuning session it is assumed that the XCP write is on the same application
			 * as the RAM buffer. This may not be the case for all programs and should be addressed in future
			 * phases the design should be modified to be configured for various applications. */

			for (i = 0; i < Size_Cnt_M_u08; i++)
			{
				FlshAddr_Cnt_T_u32 = (uint32)&(WritePtr_Cnt_M_u08[i]);
				XcpCalFound_Cnt_T_lgc = FALSE;

				/* The check below is for tuning sessions checks. If XCP has RAM page access the requested read should be read
				 * from RAM instead of flash if the value being read is part of the tuning structure that was copied into RAM.
				 * The check will apply an offset if it is found within the range of data that was copied.
				 */
				if((XcpCalStatus_Cnt_M_str.Page[XCP_RAM_PAGE].PageAccess_Cnt_T_u8 & XCP_CAL_XCP_ACCESS) != 0u)
				{
					for(x = 0U; x < XcpCalStatus_Cnt_M_str.ValidDataPts_Cnt_u8; x++)
					{
						FlshAccessStart_Cnt_T_u32 = XcpCalStatus_Cnt_M_str.Data[x].RAMStartAddr_Cnt_u32 - XcpCalStatus_Cnt_M_str.Data[x].AddrOffset_Cnt_s32;
						if( (FlshAddr_Cnt_T_u32 >= FlshAccessStart_Cnt_T_u32) && (FlshAddr_Cnt_T_u32 < (FlshAccessStart_Cnt_T_u32 + XcpCalStatus_Cnt_M_str.Data[x].Length_Cnt_u32)) )
						{
							RamDataIdx_Cnt_T_u8 = x;
							XcpCalFound_Cnt_T_lgc = TRUE;
							break;
						}
					}
				}

				/* Write the data */
				if(XcpCalFound_Cnt_T_lgc == TRUE)
				{
					WritePtr_Cnt_M_u08[(i + XcpCalStatus_Cnt_M_str.Data[RamDataIdx_Cnt_T_u8].AddrOffset_Cnt_s32)] = ReadPtr_Cnt_M_u08[i];
				}
				else
				{
					WritePtr_Cnt_M_u08[i] = ReadPtr_Cnt_M_u08[i];
				}
			}

			/* Call Function to update XCP PID in case this write is for a multi-frame XCP PID */
			ProcessXCPPID(Size_Cnt_M_u08);
		#else
			for (i = 0; i < Size_Cnt_M_u08; i++)
			{
				WritePtr_Cnt_M_u08[i] = ReadPtr_Cnt_M_u08[i];
			}

			/* Call Function to update XCP PID in case this write is for a multi-frame XCP PID */
			ProcessXCPPID(Size_Cnt_M_u08);

		#endif

		Outcome_Cnt_T_u08 = XCP_CMD_OK;
	}

	return(Outcome_Cnt_T_u08);
}

#if (STD_ON == BC_XCP_TUNEONFLY)


/***********************************************************************************************************************
 *    Function Name:   ApplXcpGetCalPage
 *
 *    Description:     This command returns the logical number for the calibration data page that is currently
 * 					   activated for the specified access mode and data segment
 *
 *    Inputs:          segment   : Logical data segment number
 *                     mode		 : Access mode
 *
 *    Outputs:         ActivePage_Cnt_T_u8 : Logical data page pointer
 *
 **********************************************************************************************************************/
FUNC (uint8, XCP_CODE) ApplXcpGetCalPage ( VAR(uint8, AUTOMATIC) segment, VAR(uint8, AUTOMATIC) mode )
{
	VAR(uint8, AUTOMATIC) ReturnValue_Cnt_T_u8 = 0u;
	VAR(boolean, AUTOMATIC) ErrorStatus_Cnt_T_lgc;
	VAR(uint8, AUTOMATIC) i;

	/* Verify the mode is valid */
	if ( (mode & (uint8)XCP_CAL_XCP_ECU_ACCESS) != 0 )
	{
		/* Verify Segment_Cnt_T_u8 is within range */
		if(segment < D_MAX_SEGMENT_CNT_U8)
		{
			for (i = 0U; i < D_MAX_PAGES_CNT_U8; i++)
			{
				if( (mode & XcpCalStatus_Cnt_M_str.Page[i].PageAccess_Cnt_T_u8) != 0u)
				{
					ReturnValue_Cnt_T_u8 = XcpCalStatus_Cnt_M_str.Page[i].PageAccess_Cnt_T_u8;
					ErrorStatus_Cnt_T_lgc = FALSE;
				}
				else
				{
					/* Return mode not valid, since it is not used on this page */
					ErrorStatus_Cnt_T_lgc = TRUE;
					ReturnValue_Cnt_T_u8 = CRC_PAGE_MODE_NOT_VALID;
				}
			}
		}
		else
		{
			/* Return Segment_Cnt_T_u8 out of range */
			ErrorStatus_Cnt_T_lgc = TRUE;
			ReturnValue_Cnt_T_u8 = CRC_SEGMENT_NOT_VALID;
		}
	}
	else
	{
		/* Return AccessMode_Cnt_T_u8 out of range */
		ErrorStatus_Cnt_T_lgc = TRUE;
		ReturnValue_Cnt_T_u8 = CRC_PAGE_MODE_NOT_VALID;
	}

	if(ErrorStatus_Cnt_T_lgc == TRUE)
	{
		XcpSetError(ReturnValue_Cnt_T_u8);
	}

	return ReturnValue_Cnt_T_u8;
}


/***********************************************************************************************************************
 *    Function Name:   ApplXcpSetCalPage
 *
 *    Description:     This command returns the logical number for the calibration data page that is currently
 * 					   activated for the specified access mode and data segment
 *
 *    Inputs:          mode		 : Access mode
 *    				   segment   : Logical data segment number
 *					   page		 : Logical data page number
 *
 *    Outputs:         ActivePage_Cnt_T_u8 : Logical data page pointer
 *
 **********************************************************************************************************************/
FUNC (uint8, XCP_CODE) ApplXcpSetCalPage ( VAR(uint8, AUTOMATIC) segment, VAR(uint8, AUTOMATIC) page, VAR(uint8, AUTOMATIC) mode )
{
	VAR(uint8, AUTOMATIC) RespCmd_Cnt_T_u8 = XCP_CAL_CMD_OK;
	VAR(uint8, AUTOMATIC) i;

	/* Verify copy has been completed before setting the page */
	if ( ((XcpCalStatus_Cnt_M_str.CopyComplete_Cnt_lgc == TRUE) && (page == (uint8)XCP_RAM_PAGE)) ||
		 (page == (uint8)XCP_FLASH_PAGE) )
	{
		/* Verify the mode is valid */
		if( (mode & (uint8)XCP_CAL_XCP_ECU_ACCESS) != 0)
		{
			/* Verify selected segment is valid */
			if(segment == XcpCalStatus_Cnt_M_str.ActiveCalSegment_Cnt_u8)
			{
				/* Verify selected page is valid */
				if(page < D_MAX_PAGES_CNT_U8)
				{
					/* Update calibration page for the selected mode */
					for(i = 0U; i < D_MAX_PAGES_CNT_U8; i++)
					{
						if (page == i)
						{
							/* Update page access */
							XcpCalStatus_Cnt_M_str.Page[i].PageAccess_Cnt_T_u8 = mode;
						}
						else
						{
							/* Clear access bits for all other pages by ANDing the inverse */
							XcpCalStatus_Cnt_M_str.Page[i].PageAccess_Cnt_T_u8 &= ((uint8)(~mode) & XCP_CAL_XCP_ECU_ACCESS);
						}
					}
				}
				else
				{
					/* Return page out of range */
					RespCmd_Cnt_T_u8 = CRC_PAGE_NOT_VALID;
				}
			}
			else
			{
				/* Return segment out of range */
				RespCmd_Cnt_T_u8 = CRC_SEGMENT_NOT_VALID;
			}
		}
		else
		{
			/* Return mode out of range */
			RespCmd_Cnt_T_u8 = CRC_PAGE_MODE_NOT_VALID;
		}
	}
	else
	{
		/* Return access denied until memory transfer has completed */
		RespCmd_Cnt_T_u8 = CRC_ACCESS_DENIED;
	}

	/* Error handling is provided by the XCP driver */
	return RespCmd_Cnt_T_u8;
}

/***********************************************************************************************************************
 *    Function Name:   ApplXcpCopyCalPage
 *
 *    Description:     This command will kick off the tune-on-the-fly session by sending the segment and page numbers
 *    				   to be copied into the RAM section of memory.
 *
 *    Inputs:          srcSeg   : Source segment to copy (must match the destSeg)
 *                     srcPage  : Source page to copy (must be flash page)
 *                     destSeg  : Destination segment to place copied data (must match the srcSeg)
 *                     destPage : Destination page to place copied data (must be RAM page)
 *
 *    Outputs:         ReturnValue_Cnt_T_u8 : Value returned from the copy operation
 *
 **********************************************************************************************************************/
FUNC (uint8, XCP_CODE) ApplXcpCopyCalPage ( VAR(uint8, AUTOMATIC) srcSeg, VAR(uint8, AUTOMATIC) srcPage, VAR(uint8, AUTOMATIC) destSeg, VAR(uint8, AUTOMATIC) destPage )
{
	VAR(uint8, AUTOMATIC) ReturnValue_Cnt_T_u8 = 0u;

	if( (srcSeg == destSeg) && (srcSeg < D_MAX_SEGMENT_CNT_U8) )
	{
		if( (srcPage == XCP_FLASH_PAGE) && (destPage == XCP_RAM_PAGE) )
		{
			/* Send segment and page */

			/* Anomaly 6186 short term correction. If the RAM page access is active for the ECU, then any copy cal
			 * page requests should be denied. This will force the user to set the access for the ECU back to flash
			 * before any data is allowed to be copied. This will prevent any kick backs during the memcpy commands */
			if( ((XcpCalStatus_Cnt_M_str.Page[XCP_RAM_PAGE].PageAccess_Cnt_T_u8) & XCP_CAL_ECU_ACCESS) == XCP_CAL_ECU_ACCESS)
			{
				/* Set error 0x24 saying that the memory is not accessible. */
				XcpSetError(CRC_ACCESS_DENIED);
			}
			else
			{
				/* ECU access is not on the RAM page, allow the request */
				ReturnValue_Cnt_T_u8 = CreateXcpCalSession(destSeg);
			}
		}
		else
		{
			/* Cannot copy with current setup (RAM->Flash), send error */
			XcpSetError(CRC_PAGE_NOT_VALID);
		}
	}
	else
	{
		/* Segments do not match, return invalid error */
		XcpSetError(CRC_SEGMENT_NOT_VALID);
	}

	/* Error handling is done by the XCP driver */
	return ReturnValue_Cnt_T_u8;
}

/***********************************************************************************************************************
 *    Function Name:   CreateXcpCalSession
 *
 *    Description:     Copies the requested data from flash to RAM and updates the session structure.
 *
 *    Inputs:          Segment_Cnt_T_u8   :  Destination segment to place copied data
 *
 *    Outputs:         ReturnValue_Cnt_T_u8 : Value returned from the copy operation
 *
 **********************************************************************************************************************/
STATIC FUNC(uint8, AUTOMATIC) CreateXcpCalSession( VAR(uint8, AUTOMATIC) Segment_Cnt_T_u8)
{
	VAR(uint8, AUTOMATIC) ReturnValue_Cnt_T_u8 = XCP_CAL_CMD_OK;
	VAR(uint8, AUTOMATIC) i;
	VAR(uint8, AUTOMATIC) subIndex_Cnt_T_u8;
	VAR(uint8, AUTOMATIC) IndxLookupVal_Cnt_T_u8[BC_XCP_MAXPERCOPY_CNT_U8];

	#if (BC_XCP_SEG16ENABLE == STD_ON)
		VAR(uint32, AUTOMATIC) Seg16StartAddr_Cnt_T_u32 = (uint32)(&BC_XCP_SEG16LNKSYMB);
		VAR(uint32, AUTOMATIC) Seg16Length_Cnt_T_u32 = (uint32)(&BC_XCP_SEG16LNKSYMBLEN_CNT_U8);
	#endif

	/* Set initial session values */
	XcpCalStatus_Cnt_M_str.CopyComplete_Cnt_lgc = FALSE;
	XcpCalStatus_Cnt_M_str.ActiveCalSegment_Cnt_u8 = Segment_Cnt_T_u8;
	XcpCalStatus_Cnt_M_str.ActiveTunPers_Cnt_16 = ActiveTuningPers_Cnt_M_u16;
	XcpCalStatus_Cnt_M_str.ActiveTunSet_Cnt_16 = ActiveTuningSet_Cnt_M_u16;

	switch(Segment_Cnt_T_u8)
	{
		case XCP_PERS_SEG:
			#if(BC_XCP_SEG0ENABLE == STD_ON)
				#if (BC_XCP_PERSINDEXLOOKUP == STD_ON)
					/* Call function to gather indexes from integration-specific function */
					GetPersIndexes(BC_XCP_MAXPERCOPY_CNT_U8, &IndxLookupVal_Cnt_T_u8[0]);
				#else
					subIndex_Cnt_T_u8 = 0u;
					for (i = 0U; i < BC_XCP_MAXPERCOPY_CNT_U8; i++)
					{
						if(BC_XCP_MAXPERCOPY_CNT_U8 == 1U)
						{
							/* Only copy the active pers */
							IndxLookupVal_Cnt_T_u8[i] = ActiveTuningPers_Cnt_M_u16;
						}
						else
						{
							/* Copy active first, followed by the remainder starting at pers0, skipping the active one */
							if (i == 0u)
							{
								IndxLookupVal_Cnt_T_u8[i] = ActiveTuningPers_Cnt_M_u16;
								if (subIndex_Cnt_T_u8 != ActiveTuningPers_Cnt_M_u16)
								{
									subIndex_Cnt_T_u8 = 0u;
								}
								else
								{
									subIndex_Cnt_T_u8++;
								}
							}
							else
							{
								if (subIndex_Cnt_T_u8 != ActiveTuningPers_Cnt_M_u16)
								{
									IndxLookupVal_Cnt_T_u8[i] = subIndex_Cnt_T_u8;
								}
								/* Match was found, or x was applied in the above statement, in either case, increment */
								subIndex_Cnt_T_u8++;
							}
						}
					}
				#endif

				/* Copy data to RAM */
				XcpCalStatus_Cnt_M_str.ValidDataPts_Cnt_u8 = BC_XCP_MAXPERCOPY_CNT_U8;

				for (i = 0U; i < BC_XCP_MAXPERCOPY_CNT_U8; i++)
				{
					/* Copy data to RAM */
					memcpy((void *)&(XcpCalStr.Pers[i]), (const void *)(T_TunPersSelectionTbl_Ptr_Str[0][IndxLookupVal_Cnt_T_u8[i]]), (uint16)sizeof(XcpCalStr.Pers[i]));

					/* Update session information */
					XcpCalStatus_Cnt_M_str.Data[i].FlashIndex_Cnt_u8 = IndxLookupVal_Cnt_T_u8[i];
					XcpCalStatus_Cnt_M_str.Data[i].Length_Cnt_u32 = (uint32)sizeof(XcpCalStr.Pers[i]);
					XcpCalStatus_Cnt_M_str.Data[i].RAMStartAddr_Cnt_u32 = (uint32)&(XcpCalStr.Pers[i]);
					XcpCalStatus_Cnt_M_str.Data[i].AddrOffset_Cnt_s32 = XcpCalStatus_Cnt_M_str.Data[i].RAMStartAddr_Cnt_u32 - (uint32)(T_TunPersSelectionTbl_Ptr_Str[0][IndxLookupVal_Cnt_T_u8[i]]);
				}
		#else
			ReturnValue_Cnt_T_u8 = CRC_SEGMENT_NOT_VALID;
			XcpCalStatus_Cnt_M_str.CopyComplete_Cnt_lgc = FALSE; /* Ensure this flag is set to false on error */
		#endif
		break;
		case XCP_SETS_SEG:
			#if(BC_XCP_SEG1ENABLE == STD_ON)
				#if (BC_XCP_SETINDEXLOOKUP == STD_ON)
					/* Call function to gather indexes from integration-specific function */
					GetSetIndexes(BC_XCP_MAXSETCOPY_CNT_U8, &IndxLookupVal_Cnt_T_u8);
				#else
					subIndex_Cnt_T_u8 = 0u;
					for (i = 0U; i < BC_XCP_MAXSETCOPY_CNT_U8; i++)
					{
						if(BC_XCP_MAXSETCOPY_CNT_U8 == 1U)
						{
							/* Only copy the active Set */
							IndxLookupVal_Cnt_T_u8[i] = ActiveTuningSet_Cnt_M_u16;
						}
						else
						{
							/* Copy active first, followed by the remainder starting at pers0, skipping the active one */
							if (i == 0u)
							{
								IndxLookupVal_Cnt_T_u8[i] = ActiveTuningSet_Cnt_M_u16;
								if (subIndex_Cnt_T_u8 != ActiveTuningSet_Cnt_M_u16)
								{
									subIndex_Cnt_T_u8 = 0u;
								}
								else
								{
									subIndex_Cnt_T_u8++;
								}
							}
							else
							{
								if (subIndex_Cnt_T_u8 != ActiveTuningPers_Cnt_M_u16)
								{
									IndxLookupVal_Cnt_T_u8[i] = subIndex_Cnt_T_u8;
								}
								/* Match was found, or x was applied in the above statement, in either case, increment */
								subIndex_Cnt_T_u8++;
							}
						}
					}
				#endif

				/* Copy data to RAM */
				XcpCalStatus_Cnt_M_str.ValidDataPts_Cnt_u8 = BC_XCP_MAXSETCOPY_CNT_U8;

				for (i = 0U; i < BC_XCP_MAXSETCOPY_CNT_U8; i++)
				{
					memcpy((void *)&(XcpCalStr.Sets[i]), (const void *)(T_TunSetSelectionTbl_Ptr_Str[IndxLookupVal_Cnt_T_u8[i]]), (uint16)sizeof(XcpCalStr.Sets[i]));

					/* Update session information */
					XcpCalStatus_Cnt_M_str.Data[i].FlashIndex_Cnt_u8 = IndxLookupVal_Cnt_T_u8[i];
					XcpCalStatus_Cnt_M_str.Data[i].Length_Cnt_u32 = (uint32)sizeof(XcpCalStr.Sets[i]);
					XcpCalStatus_Cnt_M_str.Data[i].RAMStartAddr_Cnt_u32 = (uint32)&(XcpCalStr.Sets[i]);
					XcpCalStatus_Cnt_M_str.Data[i].AddrOffset_Cnt_s32 = XcpCalStatus_Cnt_M_str.Data[i].RAMStartAddr_Cnt_u32 - (uint32)(T_TunSetSelectionTbl_Ptr_Str[IndxLookupVal_Cnt_T_u8[i]]);
				}
		#else
			ReturnValue_Cnt_T_u8 = CRC_SEGMENT_NOT_VALID;
			XcpCalStatus_Cnt_M_str.CopyComplete_Cnt_lgc = FALSE; /* Ensure this flag is set to false on error */
		#endif
		break;
		case XCP_CUSTDEFMEMBLK:
			#if(BC_XCP_SEG16ENABLE == STD_ON)
				/* Copy data to RAM */
				XcpCalStatus_Cnt_M_str.ValidDataPts_Cnt_u8 = 1u; /* Hard coded to one, since only one block is being copied */

				for (i = 0U; i < XcpCalStatus_Cnt_M_str.ValidDataPts_Cnt_u8; i++)
				{
					memcpy((void *)&(XcpCalStr.Seg16CustBlck[i]), (const void *)(Seg16StartAddr_Cnt_T_u32), Seg16Length_Cnt_T_u32);

					/* Update session information */
					XcpCalStatus_Cnt_M_str.Data[i].FlashIndex_Cnt_u8 = 0u; /* Hard coded since it is not needed */
					XcpCalStatus_Cnt_M_str.Data[i].Length_Cnt_u32 = (uint32)Seg16Length_Cnt_T_u32;
					XcpCalStatus_Cnt_M_str.Data[i].RAMStartAddr_Cnt_u32 = (uint32)&(XcpCalStr.Seg16CustBlck[i]);
					XcpCalStatus_Cnt_M_str.Data[i].AddrOffset_Cnt_s32 = XcpCalStatus_Cnt_M_str.Data[i].RAMStartAddr_Cnt_u32 - (uint32)(Seg16StartAddr_Cnt_T_u32);
				}
			#else
				ReturnValue_Cnt_T_u8 = CRC_SEGMENT_NOT_VALID;
				XcpCalStatus_Cnt_M_str.CopyComplete_Cnt_lgc = FALSE; /* Ensure this flag is set to false on error */
			#endif
		break;
		case XCP_COMMON_SEG:				/* TODO: Define at a later date, return a negative response */
		case XCP_SETANDPER_SEG:				/* TODO: Define at a later date, return a negative response */
		case XCP_SETANDPERANDCOMMON_SEG:	/* TODO: Define at a later date, return a negative response */
		default:
			/* Return Error Condition */
			ReturnValue_Cnt_T_u8 = CRC_SEGMENT_NOT_VALID;
			XcpCalStatus_Cnt_M_str.CopyComplete_Cnt_lgc = FALSE; /* Ensure this flag is set to false on error */
		break;
	};

	/* Set complete flag if no error */
	if (ReturnValue_Cnt_T_u8 == XCP_CAL_CMD_OK)
	{
		XcpCalStatus_Cnt_M_str.CopyComplete_Cnt_lgc = TRUE;
	}


	return ReturnValue_Cnt_T_u8;
}

/***********************************************************************************************************************
 *    Function Name:   ApplXcpCopyCalPage
 *
 *    Description:     Custom error handler since some of the functions do not return an error based on a limitation
 *    				   of the Vector driver. This function will set the context to an error condition for XCP requests.
 *
 *    Inputs:          ErrCode_Cnt_T_u8 : Destination page to place copied data (must be RAM page)
 *
 *    Outputs:         None
 *
 **********************************************************************************************************************/
STATIC FUNC(void, AUTOMATIC) XcpSetError(VAR(uint8, AUTOMATIC) ErrCode_Cnt_T_u8)
{
	XCP_RespLen_m(2u); 					/* Set error code length */
	XCP_RespCmd_m((uint8)PID_ERR);		/* Set first byte to 0xFE */
	XCP_ErrCode_m(ErrCode_Cnt_T_u8);	/* Set error code in next byte */

	return;
}

#endif
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of function definition area >>              DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of removed code area >>                   DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

 
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of removed code area >>                     DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
