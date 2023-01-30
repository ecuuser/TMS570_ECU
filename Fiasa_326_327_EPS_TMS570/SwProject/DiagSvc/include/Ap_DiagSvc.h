/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : Ap_DfltConfigData.h
* Module Description:
* Product           : Gen II Plus - EA3.0
* Author            : Pradeep Srinivasa
*****************************************************************************/
/* Version Control:
 * Date Created:      Thu Jun 20 10:00:00 2013
 * %version:          4 %
 * %derived_by:       mzjphh %
 * %date_modified:    Tue Sep 24 11:27:18 2013 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date       Rev     Author   Change Description                                                               SCR #
 * --------   ------  -------  ------------------------------------------------------------------------------  -------
 * 03/16/16    1      PS       Initial Version		  														   EA3#6773, EA3#6775
 * 04/01/16    2      PS       Added D_EPSNRCVEHSPDINVALID_CNT_U08 for RID 0x0200						       EA3#7178
 * 08/01/16    3      PS       Updated RID 0x0200 to fix anomaly EA3#9955					 				   EA3#9969
 * 10/06/16    4      NS	   Added ProxiConfigurationGetErrorStatus declaration							   EA3#11533
 */

#ifndef RTE_AP_DIAGSVC_H
#define RTE_AP_DIAGSVC_H

#include "CalConstants.h"
#include "GlobalMacro.h"
#include "Dcm.h"
#include "Dem.h"
#include "Dem_Cbk.h"
#include "Dem_Lcfg.h"
#include "Mcu.h"
#include "NtWrap.h"
#include "Ap_DfltConfigData.h"
#define NVM_SKIP_API_DECLARATIONS STD_ON
#include "EPS_DiagSrvcs_SrvcLUTbl.h"
#include "Cd_NvMProxy.h"


#define D_ASCIIFILLER_CNT_U08			0x20u
#define D_DATAFILLER_CNT_U08			0x00u
#define D_STEERINGANGLESENSOR_CNT_F32	0.0625f
#define D_DRIVERTORQUE_CNT_F32			0.125f
#define D_BATTERYVOLTAGE_CNT_F32		0.1f
#define D_ECUTEMPERATURE_CNT_F32 		0.01f
#define D_ECULIFETIMESECS_CNT_F32 		15u
#define CRC_POLYNOMIAL_16				0x1021u
#define D_IOCONTROLTIMEOUT_MS_U16		30000U
#define D_EPSNRCVEHSPDINVALID_CNT_U08	0x89U

/* Note - change this value according to the NvMP_Rte_Sa_DigColPs_DigColPsEOL location in NvM Proxy */
#define D_NVMPXYDIGCOLPSBLK_CNT_U08		15U

/* PROXI Msg definitions */
#define PROXIMSG_CRC_LENGTH				5u
#define PROXIMSG_CONFIGCODE_LENGTH		11u
#define PROXIMSG_PRODCUTION_MONTH		23u
#define PROXIMSG_PRODCUTION_DATA		24u
#define PROXIMSG_VEHICLE_CONFIG			104u
#define PROXIMSG_ENGINE_TYPE			65u
#define PROXIMSG_SUSPENSION_CONFIG		88u
#define PROXIMSG_CAR_CONFIGURATION_1	57u
#define PROXIMSG_CAR_CONFIGURATION_6	62u
#define PROXIMSG_CAR_CONFIGURATION_12	69u
#define PROXIMSG_CAR_CONFIGURATION_15	104u
#define PROXIMSG_INFO_CONFIGURATION_3	112u

extern VAR(Dem_NvStatusDataType, DEM_APPL_DATA) Dem_Cfg_NvEventStatusData; /* PRQA S 0850 */ /* MD_MSR_19.8 */
extern VAR(uint16, NVM_APPL_DATA) Nvm_IgnCntr_Cnt_u16;
extern VAR(Dcm_255Byte_Type, RTE_VAR_DEFAULT_RTE_Ap_9_PIM_GROUP) Rte_DiagSvc_ProxiConfigurationData;
extern VAR(uint8, AP_DIAGSVC_VAR) DiagSvc_ProxiCheckData_Cnt_u08[11];

STATIC FUNC(uint16,RTE_AP_DIAGSVC_APPL_CODE) PROXICRC_CCIT16(P2VAR(uint8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 length);
STATIC FUNC(uint8,	RTE_AP_DIAGSVC_APPL_CODE) Reverse_8bit(uint8 value);
STATIC FUNC(void, 	RTE_AP_DIAGSVC_APPL_CODE) UpdateProxiErrorStatus(uint8 Errorcode, uint8 Byte , uint8 BitInfoMask);
FUNC(void,  RTE_AP_DIAGSVC_APPL_CODE) UpdateFirstDTCDetect();
STATIC FUNC(void, RTE_AP_DIAGSVC_APPL_CODE) ClearFirstDTCDetect();
FUNC(void,  RTE_AP_DIAGSVC_APPL_CODE) DiagSvc_DspPostClearDiagInfo(Dcm_ConfirmationStatusType status);
STATIC FUNC(void,	RTE_AP_DIAGSVC_APPL_CODE) ResetIOCtrlTimer(P2VAR(uint32, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) IOControlTimer_mS_T_u32);
extern FUNC(void, DCM_CODE) Dcm_DspPostClearDiagInfo(Dcm_ConfirmationStatusType status);
extern void Appl_WaitNvMReady(const uint16 blockNumber, const boolean fastMode);
FUNC(NvM_RequestResultType, RTE_AP_DIAGSVC_APPL_CODE) DiagSvc_ProxiConfigurationGetErrorStatus(void);

#endif /* RTE_AP_DIAGSVC_H */
