/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
 /*****************************************************************************
 * Copyright 2014 Nexteer
 * Nexteer Confidential
 *
 * Module File Name  : EPS_DiagSrvcs_ISO.c
 * Module Description: Implementation of CMS Common
 * Project           : CBD
 * Author            : Jared Julien
 *****************************************************************************
 * Version Control:
 * Date Created:      Mon Apr 12 10:20:00 2012
 * %version:          70 %
 * %derived_by:       kzdyfh %
 * %date_modified:    Fri Mar  7 08:40:26 2014 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author    Change Description                                                              SCR #
 * --------  -------  --------  ------------------------------------------------------------------------------  ------
 * 06/06/12  1        KS        Initial Component Release                                                       5606
 * 06/12/12  2        KS        Corrected Manuf Spec Version to 001                                             5606
 * 06/29/12  3        KJS       Corrected anomaly 3464 for service FD02                                         5772
 * 07/05/12  4        KJS       Added service FD1F                                                              5808
 * 07/27/12  5        KJS       Anomaly 3536 correction for serivce F00E                                        5907
 * 07/30/12  6        LWW       Typo correction in serivce F00E                                                 5901
 * 07/31/12  7        LWW       Changed boot software handling                                                  5901
 * 07/31/12  8        KJS       Added offset correction in read services, service req types for F009,           5921
                                and changed NULL to CM_NULL for build variations in FD01.
 * 08/06/12  9        KJS       Added missing temporary variable to service FD14                                5936
 * 09/26/12  10       Jared     Added new service (FD17, FD26, FD27, FD29) for DiagMgr & AvgFricLrn             6396
 * 10/01/12  11       Jared     Updates for Anom 3865 - Added calls to Blackbox data clear in F000 & F001       6408
 * 10/05/12  12       SAH       Updated READ function for EPSInternal_PID_FD12 to use assignment rather than OR 6448
 * 10/18/12  13       Jared     Corrected anom 3645 for NRC compliance with spec v02A                           6401
 * 10/20/12  14       LWW       Name change on hwtrq and vehspd, added absolute value in hwtrq checks           6575
 * 10/23/12  15       Jared     Removed returned value and subsequent NRC translation for FD0D                  6590
 * 10/24/12  16       Jared     Implemented read functions for FD26/27/29 for AvgFricLrn                        6635
 * 10/29/12  17       Jared     Added defeat clear on session change to correct anomaly 3677                    6344
 * 10/30/12  18       JJW       Changed invocation of various Scom serfunction to the standard Macro
 *                              invocation CM_<Scom server function name>
 * 11/01/12  19       JJW       Removed Suspend/Resume interrupt pairs to support mapping Scomm invocations to
 *                              NonTrusted function call interface (the osApi requires interrupts to be enabled)
 * 11/06/12  20       LWW       Added abstraction of DigHwTrq SetScale function                                 6702
 * 11/10/12  21       Jared     Changed FD29 to read/write 2 bytes as u8p8_T                                    6773
 * 11/13/12  22       VK        Anomaly 3976 fix                                                                6817
 * 11/14/12  23       VK        Anomaly 4046 fix                                                                6817
 * 11/26/12  24       Jared     Anomaly 4094 fix                                                                6883
 * 12/06/12  24.1.1   KJS       Added subtraction of write index to all RIDs                                    6941
 * 01/14/13  25       LN        Added F003 and FDA7                                                             6916
 * 01/15/13  26       LN        Updates to PIDs FD0C and FD12                                                   6916
 * 01/24/13  27       Jared     Remove duplicate EEPROM writes from FD16 and FDA5                               7148
 * 01/25/13  28       Jared     Brought in F0FF from PSR458 source                                              7190
 * 02/06/13  29       JJW       MtrPos EOL data handling change to support MtrPos FDD06B_004.1 interface        7293
 * 02/15/13  30       LN        Added functionality for LTLVehSpdFltCtr and IgnCtr reset bits in PID F000       7352
 * 02/22/13  31       LN        Updates tp PIDs F000, F003, FD03, and FDA7                                      7447
 *                              Updated NRCTranslate function                                                   7448
 * 02/22/13  32       LN        Corrected PID F003 and FD03 to allow data not to be overwritten.                7448
 * 03/11/13  33       Jared     Update to spec 04A and generation tool 2.0                                      7225
 * 03/18/13  34       Jared     Update to add MainHandler function and complete overhaul of CMS function        7628
 * 03/21/13  35       KJS       Corrected anomaly 4680 for MEC=0 NRCs for 0x22 services                         7690
 * 04/01/13  36       Jared     Moved MEC/IgnCntr WriteBlock call to periodic function                          7750
 * 04/12/13  37       Jared     Fixed FD11 byte alignment                                                       7852
 * 04/14/13  38       Jared     Anomaly fix 4591 - F008 / F009 sequence NRC                                     4569
 * 04/16/13  39       Jared     Range limit checks for FDB5 and FDB6                                            7136
 * 04/18/13  40       Jared     Fixed conditional statements around F00F function to allow compile on Ford      7931
 * 04/26/13  41       Jared     Fixed anomaly 4858 - cogging table length/alignment issues                      8080
 * 04/30/13  42       Jared     Updated F0FF to use fixed length with padded "don't care" bytes                 8171
 * 05/01/13  43       VK        Anomaly 4950 correction                                                         8202
 * 06/06/13  44       VK        Anomaly 5051 correction                                                         8552
 * 06/14/13  45       Jared     Updated to spec revision 05C                                                    8585
 * 07/12/13  46       Jared     Anomaly fixes for NRC codes and updates to MainHandler checks                   9033
 * 07/16/13  47       Jared     Anomaly fix for FD29/FDB5/FDB6 NRC 0x31 -> 0xFD (Anom 5257)                     9069
 * 07/29/13  48       Jared     Updated FD07 to pass 8 bit values to/from polarity component for A5125          8789
 * 07/31/13  49       Jared     Updated F00F scaling for A5166 to scale velocity by factor of 10                9291
 * 08/29/13  50       Jared     Changed stop length structure element name for shared use with NvM block num    9996
 * 09/19/13  51       Jared     Updated to support config tool v3.x and added FD30 & FD31 for spec 06A          9610
 * 09/27/13  52       LWW       Updated per integration issues of 06A version                                   10272
 * 09/30/13  53       LWW       Made FDB4 Configurable                                                          10272
 * 10/15/13  54       VK        A5799: Corrections for go to position service                                   10414
 *                              A5800: fix (Corrections to F00F service)                                        10415
 * 10/16/13  55       Jared     Update to spec rev 06B:                                                         10467
 *                                  - Changed F009 to type 2
 *                                  - Updated #ifdef to #if for service inclusion/exclusion
 *                                  - Added FDB7 for cogging torque 5
 *                                  - Removed all references to ISOVarTbl, swapped with CM_ references
 * 11/21/13  56       Jared     A5790 - corrected conversion of FD20 battery voltage to allow full range        10896
 * 11/27/13  57       Jared     A5919 - vehicle speed updates for FD02 specific to ModIdx w/ periodic clear     10859
 * 01/15/14  58       LK        Added DID FD28 for TCFlashTraceabilityID and updated PID F006 for return value  11189
 * 01/18/14  59       KJS       Corrected anomaly 6236                                                          11232
 * 01/29/14  60       LK        Updated to CMS Rev 07A                                                          11298
 * 01/30/14  61       LK        A6005 - Replaced cal CM_k_SComTrqPosPol_Cnt_s08 with k_CMSGotoPosPol_Cnt_s08    11277
 * 02/25/14  62       VK        A6390 - Corrections to RID F000                                                 11494
 * 02/28/14  63       Jared     Updates to FDAF to support changes to BlkBox data type for Param1/2             11531
 * 03/04/14  64       VK        Undo changes made to A6390                                                      11494
 * 03/07/14  65       Jared     Corrected missing ReturnDataIdx for service FDAF after previous change          11578
 * 08/04/14  66       VS        Updated the service DID FD30 as writeable                                       11278
 * 08/26/14  67       Jared     A6686: Remain in manufacturing mode when MEC initially reached zero             12314
 *                              A6621: Manual torque command not resetting after Nexteer session has expired    12366
 * 08/29/14  68       KJS       A6427: Corrected anomaly to prevent ECU resets						            12406
 * 10/10/14  69		  SB		Implement FD21 in CMS_Common													12511
 * 11/12/14  70       JWJ       Corrected CMS version number                                                    12664
 */
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
#include "EPS_DiagSrvcs_CommonData.h"
#include "EPS_DiagSrvcs_SrvcLUTbl.h"

#include "EPS_DiagSrvcs_ISO.Interface.h"
#include "EPS_DiagSrvcs_ISO.h"

#include "EPS_DiagSrvcs_XCP.Interface.h"
#include "EPS_DiagSrvcs_XCP.h"
#include "SystemTime.h"
#include "tiotp_regs.h"

#include <string.h> /* provide memset() and memcpy() definitions */

/* PRQA S 4394 EOF
 * MISRA-C: 2004 Rule 10.3: This deviation is required for a composite expression of 'essentially unsigned' typ */

/* PRQA S 4395 EOF
 * MISRA-C: 2004 Rule 10.4: This deviation is required for a composite expression of 'essentially float' typ */

/* PRQA S 303 EOF
 * MISRA-C: 2004 Rule 11.3: This deviation is required for register access.  The rule is suppressed for the entire file */

/* PRQA S 3673 EOF
 * MISRA-C: 2004 Rule 16.7: This deviation is required because of the use of a standardized service function structure. */


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of include and declaration area >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

#define EPSDIAGSRVC_START_SEC_CONST_8
#include "MemMap.h" /* PRQA S 5087 */
/* Version tracking. TODO: Use AUTOSAR Tracking when placed into a component */
STATIC CONST(uint8, EPSDIAGSRVC_VAR) CM_ManufSpecVersion_ASCII_u08[] = {0x30U, 0x37U, 0x42U}; /* PRQA S 3218 */ 
#define EPSDIAGSRVC_STOP_SEC_CONST_8
#include "MemMap.h" /* PRQA S 5087 */


/* Global variables */
#define EPSDIAGSRVC_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */
VAR(ManufModeType, EPSDIAGSRVC_VAR) NxtrMEC_Uls_G_enum;
#if (D_EPSDIAGSRVRIDF00F_CNT_ENUM == D_DIAGSRVC_ENABLED)
STATIC VAR(F00FSTATE_Enum, EPSDIAGSRVC_VAR) GenPosTrajRoutineStatus_Cnt_M_enum;
STATIC VAR(CM_Rte_ModeType_StaMd_Mode, EPSDIAGSRVC_VAR) F00FSystemState_Uls_M_enum;
#endif
#define EPSDIAGSRVC_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */


#define EPSDIAGSRVC_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h" /* PRQA S 5087 */
VAR(boolean, EPSDIAGSRVC_VAR) MfgDiagInhibit_Uls_G_lgc;
STATIC VAR(boolean, EPSDIAGSRVC_VAR) EpsDiagSrvc_WriteMecBlock_Cnt_M_lgc;
STATIC VAR(boolean, EPSDIAGSRVC_VAR) EpsDiagSrvc_WriteICBlock_Cnt_M_lgc;
STATIC VAR(boolean, EPSDIAGSRVC_VAR) EpsDiagSrvc_CurOffsetRunning_Cnt_M_lgc;
#if (D_EPSDIAGSRVRIDF00F_CNT_ENUM == D_DIAGSRVC_ENABLED)
STATIC VAR(boolean, EPSDIAGSRVC_VAR) EpsDiagSrvc_HandsONStart_Cnt_M_lgc;
STATIC VAR(boolean, EPSDIAGSRVC_VAR) EpsDiagSrvc_HandsONAbort_Cnt_M_lgc;
STATIC VAR(boolean, EPSDIAGSRVC_VAR) EpsDiagSrvc_AbsPosTrajReq_Cnt_M_lgc;
STATIC VAR(boolean, EPSDIAGSRVC_VAR) EpsDiagSrvc_MonitorSystemState_Cnt_M_lgc;
#endif
#define EPSDIAGSRVC_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h" /* PRQA S 5087 */


#define EPSDIAGSRVC_START_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(uint32, EPSDIAGSRVC_VAR) EpsDiagSrvc_DefeatClrOnSessionChange_Cnt_M_u32;
STATIC VAR(uint32, EPSDIAGSRVC_VAR) EpsDiagSrvc_DiagSrvDftBuffer_Uls_M_u32;
#if (D_EPSDIAGSRVRIDF00F_CNT_ENUM == D_DIAGSRVC_ENABLED)
STATIC VAR(float32, EPSDIAGSRVC_VAR) EpsDiagSrvc_PosTrajTrgtHWPos_HwDeg_M_f32;
STATIC VAR(float32, EPSDIAGSRVC_VAR) EpsDiagSrvc_TrgtHwVel_DegpS_M_f32; /* PRQA S 3218 */
STATIC VAR(float32, EPSDIAGSRVC_VAR) EpsDiagSrvc_TrgtHwAccel_DegpSSqrd_M_f32; /* PRQA S 3218 */
STATIC VAR(uint32, EPSDIAGSRVC_VAR) EpsDiagSrvc_PosTrajHoldTime_Cnt_M_u32;
STATIC VAR(float32, EPSDIAGSRVC_VAR) EpsDiagSrvc_CurrentHwPos_HwDeg_M_f32;
STATIC VAR(uint32, EPSDIAGSRVC_VAR) EpsDiagSrvc_HandsONStartTime_Cnt_M_u32;
STATIC VAR(uint32, EPSDIAGSRVC_VAR) EpsDiagSrvc_HandsONAbortTime_Cnt_M_u32;
STATIC VAR(uint32, EPSDIAGSRVC_VAR) EpsDiagSrvc_SystemStateStartTime_Cnt_M_u32;
#endif
#define EPSDIAGSRVC_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */


#define EPSDIAGSRVC_START_SEC_VAR_CLEARED_16
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(uint16, EPSDIAGSRVC_VAR) EpsDiagSrvc_VehSpdOverride_Kph_M_u16p0;
VAR(uint16, NVM_APPL_DATA) Nvm_IgnCntr_Cnt_u16;
#define EPSDIAGSRVC_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h" /* PRQA S 5087 */


#define EPSDIAGSRVC_START_SEC_VAR_CLEARED_8
#include "MemMap.h" /* PRQA S 5087 */
VAR(uint8, NVM_APPL_DATA) Nvm_NMEC_Cnt_u8;
VAR(uint8, NVM_APPL_DATA) Nvm_EcuSrlNum_Cnt_u8[4];
VAR(uint8, NVM_APPL_DATA) Nvm_EpsSrlNum_Cnt_u8[4];
VAR(uint8, NVM_APPL_DATA) Nvm_EcuHwPn_Cnt_u8[12];
VAR(uint8, NVM_APPL_DATA) Nvm_NxtrManfScrpd_Cnt_u8[64];
#define EPSDIAGSRVC_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h" /* PRQA S 5087 */




/***********************************************************************************************************************
 *  --- GENERAL FUNCTION START ---
 *
 *  The following functions are used by the system and within services but are not explicitly services themselves.
 *
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:     EPS_DiagSessionChangeIndicator()
 *
 *  Description:       Called when Diagnostic Session Change
 *
 *  Inputs:            None
 *
 *  Outputs:           None
 *
 *
 **********************************************************************************************************************/
FUNC(void, EPSDIAGSRVC_CODE) EPS_DiagSessionChangeIndicator(
	CONST(uint8,EPSDIAGSRVC_VAR) SesCtrlTypeOld,
	CONST(uint8,EPSDIAGSRVC_VAR) SesCtrlTypeNew)
{
	if ((NEXTEER_SESSION == SesCtrlTypeOld) && (NEXTEER_SESSION != SesCtrlTypeNew))
	{

		/* This only applies if service FD0D is active. */
		#if (D_EPSDIAGSRVIOCFD0D_CNT_ENUM == D_DIAGSRVC_ENABLED)
			/* Return Ctrl to ECU */
			CM_MtrTrqLmt_SCom_ManualTrqCmd(FALSE, 0.0F);
		#endif

		/* This only applies if service FD11 is active. */
		#if (D_EPSDIAGSRVIOCFD11_CNT_ENUM == D_DIAGSRVC_ENABLED)
			/* Enable Assist Table and Clear Gain */
			CM_DFTASSTTBL_CNT_LGC = FALSE;
			CM_DWNLDASSTGAIN_ULS_F32 = 1.0F;
		#endif

		/* Clear defeat bits set in EpsDiagSrvc_DefeatClrOnSessionChange_Cnt_M_u32 */
		CM_SrlComSvcDft_Cnt_b32 &= ~EpsDiagSrvc_DefeatClrOnSessionChange_Cnt_M_u32;
		EpsDiagSrvc_DefeatClrOnSessionChange_Cnt_M_u32 = 0U;

		/* Defeats get cleared, so F008 should be denied until defeats are reset */
		EpsDiagSrvc_CurOffsetRunning_Cnt_M_lgc = FALSE;
	}

	return;
}

/***********************************************************************************************************************
 *
 *  Function Name:     EPSDiagSrvcs_Task
 *
 *  Description:       Called every 10ms.
 *
 *  Inputs:            None
 *
 *  Outputs:           None
 *
 **********************************************************************************************************************/
FUNC(void, EPSDIAGSRVC_CODE) EPSDiagSrvcs_Task(void)
{
    #if (D_EPSDIAGSRVRIDF00F_CNT_ENUM == D_DIAGSRVC_ENABLED)
        VAR(uint32, AUTOMATIC) ElapsedTime_Cnt_T_u32;
    #endif

    /* NvM WriteBlock Checks - Moved from Init function to speed startup */
    if (EpsDiagSrvc_WriteMecBlock_Cnt_M_lgc == TRUE)
    {
        (void)NvM_WriteBlock(NVM_BLOCK_CMS_NXTRMEC, NULL_PTR);
        EpsDiagSrvc_WriteMecBlock_Cnt_M_lgc = FALSE;
    }
    if (EpsDiagSrvc_WriteICBlock_Cnt_M_lgc == TRUE)
    {
        (void)NvM_WriteBlock(NVM_BLOCK_CMS_IGNCNTR, NULL_PTR);
        EpsDiagSrvc_WriteICBlock_Cnt_M_lgc = FALSE;
    }

    #if (D_EPSDIAGSRVRIDF00F_CNT_ENUM == D_DIAGSRVC_ENABLED)

        if (GenPosTrajRoutineStatus_Cnt_M_enum != F00F_ACTIVE)
        {
            (void)HandsOnDetection(F00F_DEFAULT);
        }

        if (EpsDiagSrvc_MonitorSystemState_Cnt_M_lgc == TRUE)
        {
            DtrmnElapsedTime_mS_u32(EpsDiagSrvc_SystemStateStartTime_Cnt_M_u32, &ElapsedTime_Cnt_T_u32);
            if (ElapsedTime_Cnt_T_u32 > 10U)
            {
                F00FSystemState_Uls_M_enum = CM_SystemState_Cnt_enum;
            }
        }

        if (GenPosTrajRoutineStatus_Cnt_M_enum == F00F_ACTIVE)
        {   /* Check conditions to move from ACTIVE/START to STOP state */

            EpsDiagSrvc_CurrentHwPos_HwDeg_M_f32 = Abs_f32_m(EpsDiagSrvc_PosTrajTrgtHWPos_HwDeg_M_f32 - CM_SrlComHwPos_HwDeg_f32);

            if (EpsDiagSrvc_CurrentHwPos_HwDeg_M_f32 < k_NxtrSrvcPosTrajThres_HwDeg_f32)
            {
                DtrmnElapsedTime_mS_u32(EpsDiagSrvc_PosTrajHoldTime_Cnt_M_u32, &ElapsedTime_Cnt_T_u32);
                if (ElapsedTime_Cnt_T_u32 > k_NxtrSrvcPosTrajHoldTime_mS_u16)
                {
                    GenPosTrajRoutineStatus_Cnt_M_enum = F00F_SUCCESS;
                    CDD_GenPosTrajEnableFlag_Cnt_G_lgc = FALSE;
                    EpsDiagSrvc_MonitorSystemState_Cnt_M_lgc = FALSE;
                }
            }
            else
            {
                GetSystemTime_mS_u32(&EpsDiagSrvc_PosTrajHoldTime_Cnt_M_u32);
            }

            if (GenPosTrajRoutineStatus_Cnt_M_enum == F00F_ACTIVE)
            {
                /* Check Deactivation Conditions */
                (void)HandsOnDetection(GenPosTrajRoutineStatus_Cnt_M_enum);
                GenPosTrajRoutineStatus_Cnt_M_enum = F00FCheckConditions(FALSE);

                if (GenPosTrajRoutineStatus_Cnt_M_enum != F00F_ACTIVE)
                {
                    CDD_GenPosTrajEnableFlag_Cnt_G_lgc = FALSE;
                }
            }
        }
    #endif

	#if (D_EPSDIAGSRVPIDFD02_CNT_ENUM == D_DIAGSRVC_ENABLED)
		/* If Mod Idx defeat bit is set and vehicle speed increases above zero, clear the defeat */
		/* This condition was added to resolve A5919 */
		if (((CM_SrlComSvcDft_Cnt_b32 & D_SVCDFTMODIDX_CNT_B32) == D_SVCDFTMODIDX_CNT_B32) &&
			(CM_VehicleSpeed_Kph_f32 > 0.0f))
		{
			CM_SrlComSvcDft_Cnt_b32 &= (~(D_SVCDFTMODIDX_CNT_B32));
		}
	#endif
}

/***********************************************************************************************************************
 *
 *  Function Name:     EPS_DiagSrvcs_Init
 *
 *  Description:       Initialization routine for all variables and diagnostic
 *                      services for common manufacturing.
 *
 *  Inputs:            None
 *
 *  Outputs:           None
 *
 **********************************************************************************************************************/
FUNC(void, EPSDIAGSRVC_CODE) EPS_DiagSrvcs_Init(void)
{
    EpsDiagSrvc_WriteMecBlock_Cnt_M_lgc = FALSE;
    EpsDiagSrvc_WriteICBlock_Cnt_M_lgc = FALSE;

    /* Read/Update MEC */
    NxtrMEC_Init();

    /* Start with no inhibiting of diagnostics for manufacturing */
    MfgDiagInhibit_Uls_G_lgc = FALSE;

    /* By default, don't clear any defeat bits on session change */
    EpsDiagSrvc_DefeatClrOnSessionChange_Cnt_M_u32 = 0U;

    if ((CM_SrlComSvcDft_Cnt_b32 & D_UPPERNIBBLEMASK_CNT_U32) != D_SVCDFTMULTIGNMASK_CNT_B32)
    {
        /* Multi Ign Disabled */
        EpsDiagSrvc_DiagSrvDftBuffer_Uls_M_u32 = 0uL;   /* Clears out the buffer for NvM writes */
        CM_SrlComSvcDft_Cnt_b32 = 0uL;      /* NvM RAM variable used by CDD_Interface */
    }
    else
    {
        /* Multi Ign Enabled */
        /* Update the buffer so both the NvM RAM variable and buffer match */
        EpsDiagSrvc_DiagSrvDftBuffer_Uls_M_u32 = CM_SrlComSvcDft_Cnt_b32;
    }

    /* Increment ignition counter */
    if (Nvm_IgnCntr_Cnt_u16 < D_MAXIGNCNT_CNT_U16)
    {
        Nvm_IgnCntr_Cnt_u16 = Nvm_IgnCntr_Cnt_u16 + 1U;
        EpsDiagSrvc_WriteICBlock_Cnt_M_lgc = TRUE;
    }

    #if (D_EPSDIAGSRVRIDF00F_CNT_ENUM == D_DIAGSRVC_ENABLED)
        GenPosTrajRoutineStatus_Cnt_M_enum = F00F_DEFAULT;
        CDD_GenPosTrajEnableFlag_Cnt_G_lgc = FALSE;
        EpsDiagSrvc_AbsPosTrajReq_Cnt_M_lgc = FALSE;
        EpsDiagSrvc_PosTrajTrgtHWPos_HwDeg_M_f32 = 0.0f;
        EpsDiagSrvc_CurrentHwPos_HwDeg_M_f32 = 0.0f;
        GetSystemTime_mS_u32(&EpsDiagSrvc_PosTrajHoldTime_Cnt_M_u32);

        EpsDiagSrvc_HandsONStart_Cnt_M_lgc = FALSE;
        EpsDiagSrvc_HandsONAbort_Cnt_M_lgc = FALSE;
        GetSystemTime_mS_u32(&EpsDiagSrvc_HandsONStartTime_Cnt_M_u32);
        GetSystemTime_mS_u32(&EpsDiagSrvc_HandsONAbortTime_Cnt_M_u32);
    #endif

    return;
}

/***********************************************************************************************************************
 *
 *  Function Name:     NxtrMEC_Init
 *
 *  Description:       Initialization routine for the Nexteer MEC.
 *
 *  Inputs:            None
 *
 *  Outputs:           None
 *
 **********************************************************************************************************************/
FUNC(void, EPSDIAGSRVC_CODE) NxtrMEC_Init(void)
{
	VAR(uint8, EPSDIAGSRVC_VAR) NxtrMEC_Cnt_u8;

	NxtrMEC_Cnt_u8 = Nvm_NMEC_Cnt_u8;

	switch (NxtrMEC_Cnt_u8)
	{
		case D_NXTRMEC_ENGMODE_CNT_U8:  /* Production mode or Engineering mode, do nothing */
			NxtrMEC_Uls_G_enum = EngineeringMode;
		break;
		case D_NXTRMEC_PRODMODE_CNT_U8:
			NxtrMEC_Uls_G_enum = ProductionMode;
		break;
		default:
			NxtrMEC_Cnt_u8--;
			if (NxtrMEC_Cnt_u8 == D_NXTRMEC_PRODMODE_CNT_U8)
			{
				NxtrMEC_Uls_G_enum = ProductionMode;
			}
			else
			{
				NxtrMEC_Uls_G_enum = ManufacturingMode;
			}
			EpsDiagSrvc_WriteMecBlock_Cnt_M_lgc = TRUE;
		break;
	}

	/* Update MEC Counter */
	Nvm_NMEC_Cnt_u8 = NxtrMEC_Cnt_u8;

	return;
}

/***********************************************************************************************************************
 *
 *  Function Name:     DiagSrvcs_MainHandler
 *
 *  Description:       Main entry point for all Nexteer common manufacturing services
 *
 *  Inputs:            ServiceId_Cnt_T_u16    : ID number of the service to be called
 *                     SubType_Cnt_T_u08      : Varies based upon service type:
 *                                                - Type 11: Reset type
 *                                                - Type 22: 22
 *                                                - Type 2E: 2E
 *                                                - Type 2F: 00 (return control) or 03 (short term adjust)
 *                                                - Type 31: 01 (start), 02 (stop), or 03 (request status)
 *                     DataBuffer_Uls_T_u08   : Buffer containing request/response data
 *                     RequestLen_Cnt_T_u16   : Length of data from request currently in DataBuffer
 *                     RespLen_Cnt_T_u16      : Pointer to hold length of response data in DataBuffer after return
 *
 *  Outputs:            CmdResp_Cnt_T_u08     : Response code in NRC or D_EPSNRCNOERROR_CNT_U08 on no error
 *
 **********************************************************************************************************************/
FUNC(uint8, EPSDIAGSRVC_CODE) DiagSrvcs_MainHandler(VAR(uint16, EPSDIAGSRVC_VAR) ServiceId_Cnt_T_u16,
                                                         VAR(uint8, EPSDIAGSRVC_VAR) SubType_Cnt_T_u08,
                                                         VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[],
                                                         VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16,
                                                         P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLen_Cnt_T_u16)
{
    VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
    VAR(uint8, EPSDIAGSRVC_VAR) CurrentSession_Cnt_T_u08;
    VAR(uint16, EPSDIAGSRVC_VAR) LUTidx_Uls_T_u16;
    VAR(uint8, EPSDIAGSRVC_VAR) Type_Uls_T_u08;
    VAR(uint16, EPSDIAGSRVC_VAR) Length_Cnt_T_u16;

    /* Get current session */
    CM_GetCurrentDiagnosticMode(&CurrentSession_Cnt_T_u08);

    /* Perform lookup from service table */
    LUTidx_Uls_T_u16 = DiagSrvcs_PIDIdxSearch(ServiceId_Cnt_T_u16);
    Type_Uls_T_u08 = t_DiagSrv_PIDtbl[LUTidx_Uls_T_u16].type;
    Length_Cnt_T_u16 = t_DiagSrv_PIDtbl[LUTidx_Uls_T_u16].length;


    /* -----[ Active Check ]----- */
    /* This will also catch any service that is not defined in the LUT.  The PID Index Search will return index 0
     * (D_PIDTBL_INVLDPID_ULS_U16) which is disabled on all programs.
     */
	if ((t_DiagSrv_PIDtbl[LUTidx_Uls_T_u16].active == TRUE) && (LUTidx_Uls_T_u16 != 0U))
    {
        /* -----[ Nexteer Mode Check ]----- */
        if (NEXTEER_SESSION == CurrentSession_Cnt_T_u08)
        {
            /* -----[ Write Access Check ]----- */
            /* a 0x2E service must have write privileges */
            if ( (Type_Uls_T_u08 == D_PIDTBL_PIDTYPE) &&
                 (SubType_Cnt_T_u08 == D_EPSWRDATABYIDPID_CNT_U16) &&
                 (t_DiagSrv_PIDtbl[LUTidx_Uls_T_u16].access == D_PIDTBL_READONLY) )
            {
                /*** Attempted write of read-only service ***/
                CmdResp_Cnt_T_u08 = D_EPSNRCREQOUTOFRANGE_CNT_U08;
            }
            else
            {
                /* -----[ Length Check ]----- */
                /* 0x11 (RESET) : Length of request data must be 0 - reset type passed in SubFunc parameter
                 * 0x22 (READ)  : Length ignored - no data written on a read
                 * 0x2E (WRITE) : Length of request must match the length in the LUT
                 * 0x2F (IOC)   : SubFunc == 0 -> Length must be 0, else length must match LUT length
                 * 0x31 (RID)   : Length is specific to the SubFunc type
                 */
                if (((Type_Uls_T_u08 == D_PIDTBL_RESETTYPE) && (RequestLen_Cnt_T_u16 == 0U)) ||
                    ((Type_Uls_T_u08 == D_PIDTBL_IOCTYPE) &&
                      ( ((SubType_Cnt_T_u08 == 0U) && (RequestLen_Cnt_T_u16 == 0U)) ||
                        ((SubType_Cnt_T_u08 == 3U) && (RequestLen_Cnt_T_u16 == Length_Cnt_T_u16)) ) ) ||
                    ((Type_Uls_T_u08 == D_PIDTBL_PIDTYPE) &&
                      ((SubType_Cnt_T_u08 == D_EPSRDDATABYIDPID_CNT_U16) ||
                                    ( (SubType_Cnt_T_u08 == D_EPSWRDATABYIDPID_CNT_U16) && (RequestLen_Cnt_T_u16 == Length_Cnt_T_u16)) ) ) ||
                    ((Type_Uls_T_u08 == D_PIDTBL_RIDTYPE) &&
                      ( ((SubType_Cnt_T_u08 == D_EPSRIDSUBSTART_CNT_U08) && (RequestLen_Cnt_T_u16 == Length_Cnt_T_u16)) ||
                        ((SubType_Cnt_T_u08 == D_EPSRIDSUBSTOP_CNT_U08) && (RequestLen_Cnt_T_u16 == t_DiagSrv_PIDtbl[LUTidx_Uls_T_u16].length2.lenStop)) ||
                        ((SubType_Cnt_T_u08 == D_EPSRIDSUBSTATUS_CNT_U08) && (RequestLen_Cnt_T_u16 == t_DiagSrv_PIDtbl[LUTidx_Uls_T_u16].lenStatus)) ) )
                   )
                {
                    /* -----[ Configurable NRC checks ]----- */
                    CmdResp_Cnt_T_u08 = DiagSrvcs_ConfiguredNrcCheck(LUTidx_Uls_T_u16, SubType_Cnt_T_u08);

                    /* If no NRC was set, only then call the function */
                    if (CmdResp_Cnt_T_u08 == D_EPSNRCNOERROR_CNT_U08)
                    {
                        /* Set default response length to 0 - let service overwite */
                        *RespLen_Cnt_T_u16 = 0U;

                        /* Invoke the service function */
                        CmdResp_Cnt_T_u08 = t_DiagSrv_PIDtbl[LUTidx_Uls_T_u16].address.func(SubType_Cnt_T_u08,
                                                                                            DataBuffer_Uls_T_u08,
                                                                                            RequestLen_Cnt_T_u16,
                                                                                            RespLen_Cnt_T_u16);
                    }
                }
                else
                {
                    /*** Invalid length ***/
                    CmdResp_Cnt_T_u08 = D_EPSNRCINVALIDFORMAT_CNT_U08;
                }
            }
        }
        else
        {
            /*** Not in Nexteer Mode ***/
            if (NxtrMEC_Uls_G_enum == ProductionMode)
            {
                /* Switch NRC for production mode - effectively "hiding" our services outside of Nexteer Session.
                 * This value is NRC 0x31 for ISO programs, or NRC 0x11 for GMLAN programs (with the exception of type
                 * 0x22 services which must convert the 0x11 to 0x31 because they are the only type that are supported.
                 */
                CmdResp_Cnt_T_u08 = D_EPSNRCNOTNEXTEERPROD_CNT_U08;
            }
            else
            {
                /* Return 0x7F when NMEC > 0 to tell user is in incorrect session */
                CmdResp_Cnt_T_u08 = D_EPSNRCSERVICENOTSUPPORTEDINACTIVESESSION_CNT_U16;
            }
        }
    }
    else
    {
        /*** Service not in table or not active ***/
        if (MSB(ServiceId_Cnt_T_u16) == D_EPSRESETSRVC_CNT_U16)
        {
            /* NRC for a missing or disabled RESET service (type 0x11) - NRC 0x12 - Not the same as all other service */
            CmdResp_Cnt_T_u08 = D_EPSNRCSUBFUNCNOTSUPP_CNT_U08;
        }
        else
        {
            /* NRC for all other missing or disabled services (0x22, 0x2E, 0x2F, and 0x31) */
            CmdResp_Cnt_T_u08 = D_EPSNRCSERVICEMISSING_CNT_U08;
        }
    }

    /* Map NRC codes frmo reserved range to upper conditions not correct values */
    CmdResp_Cnt_T_u08 = DiagSrvcs_NRCTranslate(CmdResp_Cnt_T_u08);

    return CmdResp_Cnt_T_u08;
}


/***********************************************************************************************************************
 *
 *  Function Name:     DiagSrvcs_PIDIdxSearch
 *
 *  Description:       Checks the lookup table for a valid PID entry. This is
 *                     a binary search on a sorted table. Returns zero
 *                     if no entry is found
 *
 *  Inputs:            PID_Uls_T_u16: User sent PID number
 *
 *  Outputs:           ValidPIDIndex_Uls_T_u16: PID index into the lookup table
 *
 **********************************************************************************************************************/
FUNC(uint16, EPSXCPDIAGSRVCS_CODE) DiagSrvcs_PIDIdxSearch(VAR(uint16, EPSDIAGSRVC_VAR) PID_Uls_T_u16)
{
    /* output */
    VAR(uint16, EPSDIAGSRVC_VAR) ValidPIDIdx_Uls_T_u16;

    /* local */
    VAR(uint16, EPSDIAGSRVC_VAR) Start_Cnt_T_u16;
    VAR(uint16, EPSDIAGSRVC_VAR) End_Cnt_T_u16;
    VAR(uint16, EPSDIAGSRVC_VAR) Middle_Cnt_T_u16;

    /* set search starting point */
    Start_Cnt_T_u16 = D_ZERO_CNT_U16;
    End_Cnt_T_u16 = (TableSize_m(t_DiagSrv_PIDtbl) - D_ONE_CNT_U16);
    Middle_Cnt_T_u16 = (Start_Cnt_T_u16 + End_Cnt_T_u16) >> D_ONE_CNT_U16;
    ValidPIDIdx_Uls_T_u16 = D_PIDTBL_INVLDPID_ULS_U16;

    /* binary search */
    while( (Start_Cnt_T_u16 <= End_Cnt_T_u16) && (t_DiagSrv_PIDtbl[Middle_Cnt_T_u16].PID != PID_Uls_T_u16) )
    {
        if (PID_Uls_T_u16 < t_DiagSrv_PIDtbl[Middle_Cnt_T_u16].PID)
        {
            End_Cnt_T_u16 = Middle_Cnt_T_u16 - D_ONE_CNT_U16;
            Middle_Cnt_T_u16 = (Start_Cnt_T_u16 + End_Cnt_T_u16) >> 1;
        }
        else
        {
            Start_Cnt_T_u16 = Middle_Cnt_T_u16 + D_ONE_CNT_U16;
            Middle_Cnt_T_u16 = (Start_Cnt_T_u16 + End_Cnt_T_u16) >> 1;
        }
    }

    /* Make sure a valid index was found, otherwise return error */
    if(t_DiagSrv_PIDtbl[Middle_Cnt_T_u16].PID == PID_Uls_T_u16)
    {
        ValidPIDIdx_Uls_T_u16 = Middle_Cnt_T_u16;
    }
    else
    {
        ValidPIDIdx_Uls_T_u16 = D_PIDTBL_INVLDPID_ULS_U16;
    }

    return (ValidPIDIdx_Uls_T_u16);
}


/***********************************************************************************************************************
 *
 *  Function Name:     DiagSrvcs_ConfiguredNrcCheck
 *
 *  Description:       Lookup configured checks for the passed service and perform the corresponding checks.  If a test
 *                     fails, the appropriate NRC code is retrned.
 *
 *  Inputs:            LUTidx_Uls_T_u16  : Index of PID in t_DiagSrv_PIDtbl returned from DiagSrvcs_PIDIdxSearch func
 *                     SubType_Cnt_T_u08 : Type of the service being called.
 *
 *  Outputs:           D_EPSNRCNOERROR_CNT_U08 if no error found in checks, otherwise corresponding NRC for the failed
 *                     test
 *
 **********************************************************************************************************************/
FUNC(uint8, EPSDIAGSRVC_CODE) DiagSrvcs_ConfiguredNrcCheck(VAR(uint16, EPSDIAGSRVC_VAR) LUTidx_Uls_T_u16, VAR(uint8, EPSDIAGSRVC_VAR) SubType_Cnt_T_u08)
{
    VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
    VAR(uint16, EPSDIAGSRVC_VAR) Checks_Cnt_T_u16 = t_DiagSrv_PIDtbl[LUTidx_Uls_T_u16].checks;

    /* Skip MEC, VehSpd and HwTrq checks for all type 22 services as reads are always allowed */
    if (SubType_Cnt_T_u08 != D_EPSRDDATABYIDPID_CNT_U16)
    {
        /* MEC Counter check */
        if ((Checks_Cnt_T_u16 & D_EPSCHECKMEC_CNT_U16) != 0U)
        {
            if (NxtrMEC_Uls_G_enum == ProductionMode)
            {
                CmdResp_Cnt_T_u08 = D_EPSNRCMECEQZERO_CNT_U08;
            }
        }

        /* Vehicle Speed Check */
        if ((Checks_Cnt_T_u16 & D_EPSCHECKVEHSPD_CNT_U16) != 0U)
        {
            if ( (CM_VehicleSpeed_Kph_f32 > CM_k_TrimVehSpdLimit_Kph_f32) &&
                 (CM_DiagStsDefVehSpd_Cnt_lgc != D_TRUE_CNT_LGC) )
            {
                CmdResp_Cnt_T_u08 = D_EPSNRCVEHSPDTHRSHOLD_CNT_U08;
            }
        }

        /* Handwheel Velocity Check */
        if ((Checks_Cnt_T_u16 & D_EPSCHECKHWVEL) != 0U)
        {
            if (Abs_f32_m(CM_HwTrq_HwNm_f32) > CM_k_TrimHwTrqLimit_HwNm_f32)
            {
                CmdResp_Cnt_T_u08 = D_EPSNRCHWTRQTHRSHOLD_CNT_U08;
            }
        }
    }

    return CmdResp_Cnt_T_u08;
}


/***********************************************************************************************************************
 *
 *  Function Name:     DiagSrvcs_NRCTranslate
 *
 *  Description:       Translates a NRC returned from developer component
 *                     (which is limited in range) to the corresponding
 *                     Nexteer defined NRC in the CM spec
 *
 *  Inputs:            DeveloperNrc: NRC returned from developer
 *                         SCom function
 *
 *  Outputs:           NxtrNRC: Translated code if match was found,
 *                         else returns the input NRC
 *
 **********************************************************************************************************************/
FUNC(CM_Std_ReturnType, EPSDIAGSRVC_CODE) DiagSrvcs_NRCTranslate(VAR(CM_Std_ReturnType, EPSDIAGSRVC_VAR) DeveloperNrc)
{
    VAR(CM_Std_ReturnType, EPSDIAGSRVC_VAR) NxtrNRC;

    switch(DeveloperNrc)
    {
        case 0x14U:
            NxtrNRC = D_EPSNRCREQUESTDATAOUTOFRANGE_CNT_U08;
            break;
        case 0x15U:
            NxtrNRC = D_EPSNRCVEHSPDTHRSHOLD_CNT_U08;
            break;
        case 0x16U:
            NxtrNRC = D_EPSNRCREQSEQUENCEERR_CNT_U08;
            break;
        case 0x21U:
            NxtrNRC = D_EPSNRCPOSSNSRCONDNOTCORRECT_CNT_U08;
            break;
        /* Removed conversion of 0x22 -> 0xFD as 0x22 is valid NRC - Sorry */
        default:
            /* No match found -> Pass Delveloper NRC code */
            NxtrNRC = DeveloperNrc;
            break;
    }
    return NxtrNRC;
}

/***********************************************************************************************************************
 *
 *  Function Name:     DiagSrvNullFunc()
 *
 *  Description:       Blank function to handle incorrect configurations.
 *                     Function is defined this way to match the pointer.
 *
 *  Inputs:            SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Pointer to buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *  Outputs:           Returns NRC for Request out of Range
 *
 **********************************************************************************************************************/
FUNC(uint8, EPSDIAGSRVC_CODE) DiagSrvNullFunc (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
{
    return D_EPSNRCREQOUTOFRANGE_CNT_U08;
}


/***********************************************************************************************************************
 *
 *  --- Additional Service Helper Functions ---
 *
 **********************************************************************************************************************/

/***********************************************************************************************************************
*
*   Function Name:     HandsOnDetection
*
*   Description:       Check for torque input from Handwheel
*
*   Inputs:            RoutineStatus_Cnt_T_enum - Status of the routine
*
*   Outputs:           HandsOnDetected_Cnt_T_lgc
***********************************************************************************************************************/
#if (D_EPSDIAGSRVRIDF00F_CNT_ENUM == D_DIAGSRVC_ENABLED)
STATIC FUNC(boolean, EPSDIAGSRVC_CODE) HandsOnDetection(F00FSTATE_Enum RoutineStatus_Cnt_T_enum)
{
    VAR(boolean, AUTOMATIC) HandsOnDetected_Cnt_T_lgc;
    VAR(uint32, AUTOMATIC) ElapsedTime_Cnt_T_u32;

    if (RoutineStatus_Cnt_T_enum == F00F_ACTIVE)
    {   /* Hands ON Abort Deactivation Conditions */
        HandsOnDetected_Cnt_T_lgc = FALSE;

        if ( (Abs_f32_m(CM_HwTrq_HwNm_f32)) >= k_F00FHandsOnThres_HwNm_f32 )
        {
            DtrmnElapsedTime_mS_u32(EpsDiagSrvc_HandsONAbortTime_Cnt_M_u32, &ElapsedTime_Cnt_T_u32);

            if (ElapsedTime_Cnt_T_u32 > k_NxtrSrvcHandsOnTime_mS_u16)
            {
                HandsOnDetected_Cnt_T_lgc = TRUE;
            }
        }
        else
        {
            GetSystemTime_mS_u32(&EpsDiagSrvc_HandsONAbortTime_Cnt_M_u32);
        }

        EpsDiagSrvc_HandsONAbort_Cnt_M_lgc = HandsOnDetected_Cnt_T_lgc;

    }
    else
    {   /* Hands OFF Start Activation Conditions */
        HandsOnDetected_Cnt_T_lgc = TRUE;

        if ( Abs_f32_m(CM_HwTrq_HwNm_f32) < k_F00FHandsOnThres_HwNm_f32 )
        {
            DtrmnElapsedTime_mS_u32(EpsDiagSrvc_HandsONStartTime_Cnt_M_u32, &ElapsedTime_Cnt_T_u32);

            if (ElapsedTime_Cnt_T_u32 > k_NxtrSrvcHandsOnTime_mS_u16)
            {
                HandsOnDetected_Cnt_T_lgc = FALSE;
            }
        }
        else
        {
            GetSystemTime_mS_u32(&EpsDiagSrvc_HandsONStartTime_Cnt_M_u32);
        }

        EpsDiagSrvc_HandsONStart_Cnt_M_lgc = HandsOnDetected_Cnt_T_lgc;
    }

    return(HandsOnDetected_Cnt_T_lgc);
}
#endif

/***********************************************************************************************************************
*   Function Name:  F00FCheckConditions
*
*   Description:    Updates the routine status based on the start/stop conditions
*
*   Inputs:         CheckHwPosAuth - Status of HwPosAuthority Check
*
*   Outputs:        RoutineStatus_Cnt_T_Enum
***********************************************************************************************************************/
#if (D_EPSDIAGSRVRIDF00F_CNT_ENUM == D_DIAGSRVC_ENABLED)
STATIC FUNC(F00FSTATE_Enum, EPSDIAGSRVC_CODE) F00FCheckConditions (boolean CheckHwPosAuth)
{
    VAR(boolean, AUTOMATIC) HwPosCkFailed_Cnt_T_lgc = FALSE;
    VAR(F00FSTATE_Enum, AUTOMATIC) RoutineStatus_Cnt_T_Enum;
    VAR(boolean, AUTOMATIC) HandsOnDetected_Cnt_T_lgc;
    VAR(uint8, AUTOMATIC) CurrentSession_Cnt_T_u08;

    (void)CM_GetCurrentDiagnosticMode(&CurrentSession_Cnt_T_u08);

    if (GenPosTrajRoutineStatus_Cnt_M_enum == F00F_ACTIVE)
    {
        HandsOnDetected_Cnt_T_lgc = EpsDiagSrvc_HandsONAbort_Cnt_M_lgc;
        EpsDiagSrvc_MonitorSystemState_Cnt_M_lgc = TRUE;
        GetSystemTime_mS_u32(&EpsDiagSrvc_SystemStateStartTime_Cnt_M_u32);
    }
    else
    {   /* Initialize routine start parameters */
        HandsOnDetected_Cnt_T_lgc = EpsDiagSrvc_HandsONStart_Cnt_M_lgc;
        F00FSystemState_Uls_M_enum = CM_SystemState_Cnt_enum;
    }

    if ((TRUE == CheckHwPosAuth) && (CM_HandwheelAuthority_Uls_f32 < D_RIDF00FMAXCONF_ULS_F32))
    {
        HwPosCkFailed_Cnt_T_lgc = TRUE;
    }

    /* Update Routine Status based on EPS conditions */
    if (F00FSystemState_Uls_M_enum != CM_RTE_MODE_StaMd_Mode_OPERATE)
    {
        RoutineStatus_Cnt_T_Enum = F00F_ERROR;
    }
    else if (CurrentSession_Cnt_T_u08 != NEXTEER_SESSION)
    {
        RoutineStatus_Cnt_T_Enum = F00F_NEXTEERMODE;
    }
    else if ((CM_VehicleSpeed_Kph_f32 >= CM_k_TrimVehSpdLimit_Kph_f32) || (CM_VehSpdValid_Cnt_lgc == FALSE))
    {
        RoutineStatus_Cnt_T_Enum = F00F_VEHSPD;
    }
    else if (HandsOnDetected_Cnt_T_lgc == TRUE)
    {
        RoutineStatus_Cnt_T_Enum = F00F_HANDSON;
    }
    else if (TRUE == HwPosCkFailed_Cnt_T_lgc)
    {
        RoutineStatus_Cnt_T_Enum = F00F_DEFAULT;
    }
    else
    {
        RoutineStatus_Cnt_T_Enum = F00F_ACTIVE;
    }

    if (RoutineStatus_Cnt_T_Enum != F00F_ACTIVE)
    {
        EpsDiagSrvc_MonitorSystemState_Cnt_M_lgc = FALSE;
    }

    return(RoutineStatus_Cnt_T_Enum);
}
#endif

/***********************************************************************************************************************
 *
 *  Function Name:     ProcessF0FF()
 *
 *  Description:       Function to handle processing of DID F0FF.
 *
 *  Inputs:            t_SrvcData_Cnt_T_u08 - Data buffer passed to F0FF
 *                     RequestDataIdx_Cnt_T_u16 - Index position into t_SrvcData_Cnt_T_u08
 *
 *  Outputs:           CmdResp_Cnt_T_u08
 *
 **********************************************************************************************************************/
/* TODO: All global variables and functions should be abstracted (i.e. CM_xxxx), headers should be included to avoid implicit function definitions */
#if (D_EPSDIAGSRVRIDF0FF_CNT_ENUM == D_DIAGSRVC_ENABLED)
FUNC(void, EPSDIAGSRVC_CODE) ProcessF0FF(VAR(uint8, AUTOMATIC) t_SrvcData_Cnt_T_u08[], VAR(uint16, AUTOMATIC) RequestDataIdx_Cnt_T_u16)
{
    VAR(uint32, AUTOMATIC) TicksToExpire_Cnt_T_u32;
    VAR(uint16, AUTOMATIC) TicksToDelay_Cnt_T_u16;
    VAR(uint16, AUTOMATIC) CycleTime_Cnt_T_u16;
    VAR(uint8, AUTOMATIC) AlarmID_Cnt_T_u08;

    /* Check is redundant but done here on "Trusted" side of the function */
    if (TRUE == CM_EnableTestMode_Cnt_lgc)
    {
        if (0x01U == t_SrvcData_Cnt_T_u08[RequestDataIdx_Cnt_T_u16])
        {
            RequestDataIdx_Cnt_T_u16++;
            CM_CancelAlarm((uint16)t_SrvcData_Cnt_T_u08[RequestDataIdx_Cnt_T_u16]);
        }
        else if (0x02U == t_SrvcData_Cnt_T_u08[RequestDataIdx_Cnt_T_u16])
        {
            RequestDataIdx_Cnt_T_u16++;
            (void)CM_WdgM_CheckpointReached((uint16)t_SrvcData_Cnt_T_u08[RequestDataIdx_Cnt_T_u16], (uint16)t_SrvcData_Cnt_T_u08[RequestDataIdx_Cnt_T_u16 + 1U]);
        }
        else if (0x03U == t_SrvcData_Cnt_T_u08[RequestDataIdx_Cnt_T_u16])
        {
            RequestDataIdx_Cnt_T_u16++;
            AlarmID_Cnt_T_u08 = t_SrvcData_Cnt_T_u08[RequestDataIdx_Cnt_T_u16];
            RequestDataIdx_Cnt_T_u16++;
            TicksToDelay_Cnt_T_u16 = bytesToWord_m(t_SrvcData_Cnt_T_u08[RequestDataIdx_Cnt_T_u16], t_SrvcData_Cnt_T_u08[RequestDataIdx_Cnt_T_u16 + 1U]);
            RequestDataIdx_Cnt_T_u16 += 2U;
            CycleTime_Cnt_T_u16 = bytesToWord_m(t_SrvcData_Cnt_T_u08[RequestDataIdx_Cnt_T_u16], t_SrvcData_Cnt_T_u08[RequestDataIdx_Cnt_T_u16 + 1U]);

            CM_DisableSysTickInterrupt();
            CM_GetAlarm((uint16)AlarmID_Cnt_T_u08, (TickRefType)&TicksToExpire_Cnt_T_u32);
            CM_CancelAlarm((uint16)AlarmID_Cnt_T_u08);
            CM_SetRelAlarm((uint16)AlarmID_Cnt_T_u08, (TicksToExpire_Cnt_T_u32 + TicksToDelay_Cnt_T_u16), (uint32)CycleTime_Cnt_T_u16);
            CM_EnableSysTickInterrupt();
        }
        else
        {
            /* Do Nothing */
        }
    }
}
#endif /* (D_EPSDIAGSRVRIDF0FF_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *
 *  --- Common Manufacturing Service Functions ---
 *
 **********************************************************************************************************************/
/****************************** BEGIN CMS GENERATION - DO NOT CHANGE/REMOVE THIS COMMENT ******************************/


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_RESET_1160
 *
 *    RESET ID:        0x1160
 *
 *    Configured NRCs: N/A
 *
 *    Description:     Nexteer ECU Reset
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVRESET1160_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_RESET_1160 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;

        switch(SubFunc_Cnt_T_u08)
        {
            case D_EPSRESET_ECURESET:
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = D_EPSRESET_ECURESET;
                ReturnDataIdx_Cnt_T_u16++;
                /* Call the EcuReset */
                CM_StaMd_SCom_EcuReset();
            break;
            default:
                CmdResp_Cnt_T_u08 = D_EPSNRCREQOUTOFRANGE_CNT_U08;
            break;
        }

        *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVRESET1160_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_RID_F000
 *
 *    RID ID:          0xF000
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB),
 *                     Vehicle Speed Too High (0x88),
 *                     Handwheel Torque Too High (0xFE)
 *
 *    Description:     Manufacturing Variable Reset
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVRIDF000_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_RID_F000 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(uint32, EPSDIAGSRVC_VAR) TempData_Cnt_T_u32;
        VAR(CM_Rte_ModeType_StaMd_Mode, EPSDIAGSRVC_VAR) SystemState_Uls_T_enum;

        switch (SubFunc_Cnt_T_u08)
        {
            case D_EPSRIDSUBSTART_CNT_U08:
                /* Read in Data */
                TempData_Cnt_T_u32 = uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16++], D_ZERO_CNT_U16);
                TempData_Cnt_T_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16++], D_BYTESHIFT_CNT_U8);
                TempData_Cnt_T_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16++], D_WORDSHIFT_CNT_U16);

                /* Get System State */
                SystemState_Uls_T_enum = CM_SystemState_Cnt_enum;

                /* -----[ Check for specific NRC conditions ]----- */
                #ifdef D_F000FRICTIONDETECTPARAM_CNT_LGC
                    if ((TempData_Cnt_T_u32 & D_F000FRICTIONDETECTPARAM_CNT_U32) != 0U)
                    {
                        if (SystemState_Uls_T_enum != CM_RTE_MODE_StaMd_Mode_OPERATE)
                        {
                            CmdResp_Cnt_T_u08 = D_EPSNRCCONDNOTCORRECT_CNT_U08;
                        }
                    }
                #endif
                #ifdef D_F000INITLRNDTBLS_CNT_LGC
                    if ((TempData_Cnt_T_u32 & D_F000INITLRNDTBLS_CNT_U32) != 0U)
                    {
                        if (SystemState_Uls_T_enum != CM_RTE_MODE_StaMd_Mode_OPERATE)
                        {
                            CmdResp_Cnt_T_u08 = D_EPSNRCCONDNOTCORRECT_CNT_U08;
                        }
                    }
                #endif

                /* -----[ Take action only if NRC check passed ]----- */
                if (CmdResp_Cnt_T_u08 == D_EPSNRCNOERROR_CNT_U08)
                {
                    #ifdef D_F000NMEC_CNT_LGC
                        if ((TempData_Cnt_T_u32 & D_F000NMEC_CNT_U32) != 0U)
                        {
                            /* Set MEC to zero, update system enum, and write to EEPROM */
                            Nvm_NMEC_Cnt_u8 = D_ZERO_CNT_U8;
                            NxtrMEC_Uls_G_enum = ProductionMode;
                            (void)NvM_WriteBlock(NVM_BLOCK_CMS_NXTRMEC, NULL_PTR);
                        }
                    #endif
                    #ifdef D_F000IGNCNTR_CNT_LGC
                        if ((TempData_Cnt_T_u32 & D_F000IGNCNTR_CNT_U32) != 0U)
                        {
                            Nvm_IgnCntr_Cnt_u16 = D_ZERO_CNT_U16;
                            (void)NvM_WriteBlock(NVM_BLOCK_CMS_IGNCNTR, NULL_PTR);
                        }
                    #endif
                    #ifdef D_F000LTLVEHSPDCNTR_CNT_LGC
                        if ((TempData_Cnt_T_u32 & D_F000LTLVEHSPDCNTR_CNT_U32) != 0U)
                        {
                            CM_LTLVehSpdCntr_Scom_ResetToZero();
                        }
                    #endif
                    #ifdef D_F000STOREDLASTPOSINVALD_CNT_LGC
                        if ((TempData_Cnt_T_u32 & D_F000STOREDLASTPOSINVALD_CNT_U32) != 0U)
                        {
                            CM_Reset_SLP_SCom_SetSLPToInvld();
                        }
                    #endif
                    #ifdef D_F000TACHGAIN_CNT_LGC
                        if ((TempData_Cnt_T_u32 & D_F000TACHGAIN_CNT_U32) != 0U)
                        {
                            /* TODO: Define services, not currently supported */
                        }
                    #endif
                    #ifdef D_F000SNSRLESSSTOREDLASTPOSINVALID_CNT_LGC
                        if ((TempData_Cnt_T_u32 & D_F000SNSRLESSSTOREDLASTPOSINVALID_CNT_U32) != 0U)
                        {
                            /* TODO: Define services, not currently supported */
                        }
                    #endif
                    #ifdef D_F000LEARNEDEOT_CNT_LGC
                        if ((TempData_Cnt_T_u32 & D_F000LEARNEDEOT_CNT_U32) != 0U)
                        {
                            CM_Reset_LrnEOT_Scom_ResetEOT();
                        }
                    #endif
                    #ifdef D_F000ACTIVEPULLCOMP_CNT_LGC
                        if ((TempData_Cnt_T_u32 & D_F000ACTIVEPULLCOMP_CNT_U32) != 0U)
                        {
                            CM_Reset_ActivePull_SCom_SetLTComp(D_ZERO_ULS_F32);
                        }
                    #endif
                    #ifdef D_F000NXTRDTCTBL_CNT_LGC
                        if ((TempData_Cnt_T_u32 & D_F000NXTRDTCTBL_CNT_U32) != 0U)
                        {
                            CM_Reset_ClearNTCs_SComm();
                        }
                    #endif
                    #ifdef D_F000NXTRDTCBLACKBOX_CNT_LGC
                        if ((TempData_Cnt_T_u32 & D_F000NXTRDTCBLACKBOX_CNT_U32) != 0U)
                        {
                            CM_DiagMgr_SCom_ClearBlackBox();
                        }
                    #endif
                    #ifdef D_F000CUSTDTCTBL_CNT_LGC
                        if ((TempData_Cnt_T_u32 & D_F000CUSTDTCTBL_CNT_U32) != 0U)
                        {
                            (void)CM_Reset_ClearCustDTCs_SComm(D_ALLDTC_MASK_CNT_U32, DEM_DTC_KIND_ALL_DTCS, DEM_DTC_ORIGIN_PRIMARY_MEMORY);
                        }
                    #endif
                    #ifdef D_F000FRICTIONDETECTPARAM_CNT_LGC
                        if ((TempData_Cnt_T_u32 & D_F000FRICTIONDETECTPARAM_CNT_U32) != 0U)
                        {
                            CM_AvgFricLrn_SCom_ResetToZero();
                        }
                    #endif
                    #ifdef D_F000WIRPARAM_CNT_LGC
                        if ((TempData_Cnt_T_u32 & D_F000WIRPARAM_CNT_U32) != 0U)
                        {
                            /* TODO: Define services, not currently supported */
                        }
                    #endif
                    #ifdef D_F000INITLRNDTBLS_CNT_LGC
                        if ((TempData_Cnt_T_u32 & D_F000INITLRNDTBLS_CNT_U32) != 0U)
                        {
                            CM_AvgFricLrn_SCom_InitLearnedTables();
                        }
                    #endif
                    #ifdef D_F000TRANSOVDATA_CNT_LGC
                        if ((TempData_Cnt_T_u32 & D_F000TRANSOVDATA_CNT_U32) != 0U)
                        {
                            CM_BatteryVoltage_SCom_ClearTransOvData();
                        }
                    #endif
                }
                else
                {
                    /* CmdResp_Cnt_T_u08 already set above */
                }
            break;
            default:
                /* Requested sub-function not supported */
                CmdResp_Cnt_T_u08 = D_EPSNRCSUBFUNCNOTSUPP_CNT_U08;
            break;
        }

        *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVRIDF000_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_RID_F001
 *
 *    RID ID:          0xF001
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB)
 *
 *    Description:     Clear Diagnostic Trouble Codes (NTC/CTC)
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVRIDF001_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_RID_F001 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(uint8, EPSDIAGSRVC_VAR) ControlParam1_Cnt_T_u8 = DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16];
        VAR(uint8, EPSDIAGSRVC_VAR) ControlParam2_Cnt_T_u8 = DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16+1U)];

        switch (SubFunc_Cnt_T_u08)
        {
            case D_EPSRIDSUBSTART_CNT_U08:
                if (D_ZERO_CNT_U8 != (ControlParam1_Cnt_T_u8 & D_LOWERNIBBLEMASK_CNT_U16))
                {
                    /* Clear internal NTC stack */
                    CM_ClearNTCs_SComm();
                }
                if (D_ZERO_CNT_U8 != (ControlParam1_Cnt_T_u8 & D_UPPERNIBBLEMASK_CNT_U16))
                {
                    /* Clear Black Box Data */
                    CM_DiagMgr_SCom_ClearBlackBox();
                }
                if (D_ONE_CNT_U8 == ControlParam2_Cnt_T_u8)
                {
                    /* Clear customer DTC stack */
                    /* TODO: Look into a proper way for the application to clear DTCs on the customer stack. This API may not be the best method */
                    CM_ClearCustDTCs_SComm(D_ALLDTC_MASK_CNT_U32, DEM_DTC_KIND_ALL_DTCS, DEM_DTC_ORIGIN_PRIMARY_MEMORY);
                }
            break;
            default:
                /* Requested sub-function not supported */
                CmdResp_Cnt_T_u08 = D_EPSNRCSUBFUNCNOTSUPP_CNT_U08;
            break;
        }

        *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVRIDF001_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_RID_F002
 *
 *    RID ID:          0xF002
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB),
 *                     Vehicle Speed Too High (0x88)
 *
 *    Description:     Torque Sensor End of Line Calibration
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVRIDF002_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_RID_F002 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(uint8, EPSDIAGSRVC_VAR) ControlParam_Cnt_T_u8 = DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16];

        switch (SubFunc_Cnt_T_u08)
        {
            case D_EPSRIDSUBSTART_CNT_U08:
                switch(ControlParam_Cnt_T_u8)
                {
                    case 1U:
                        /* Clear trim */
                        CmdResp_Cnt_T_u08 = CM_HwTrq_SCom_ClrHwTrqTrim();
                    break;
                    case 2U:
                        /* Clear Scale */
                        CmdResp_Cnt_T_u08 = CM_HwTrq_SCom_ClrHwTrqScale();
                    break;
                    case 3U:
                        /* Set Trim */
                        CmdResp_Cnt_T_u08 = CM_HwTrq_SCom_SetHwTrqTrim();
                    break;
                    default:
                        CmdResp_Cnt_T_u08 = D_EPSNRCREQOUTOFRANGE_CNT_U08;
                    break;
                }
            break;
            default:
                /* Requested sub-function not supported */
                CmdResp_Cnt_T_u08 = D_EPSNRCSUBFUNCNOTSUPP_CNT_U08;
            break;
        }

        *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVRIDF002_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_RID_F003
 *
 *    RID ID:          0xF003
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB),
 *                     Vehicle Speed Too High (0x88),
 *                     Handwheel Torque Too High (0xFE)
 *
 *    Description:     Position Sensor End of Line Calibration
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVRIDF003_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_RID_F003 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(uint8, EPSDIAGSRVC_VAR) ControlParam_Cnt_T_u8 = DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16];

        switch (SubFunc_Cnt_T_u08)
        {
            case D_EPSRIDSUBSTART_CNT_U08:
                switch(ControlParam_Cnt_T_u8)
                {
                    case 1U:
                        /* Clear Trim */
                        #ifdef D_F003CLRTRIMNORET_CNT_LGC
                            CM_HwPos_SCom_ClrHwPosTrim();
                        #else
                            CmdResp_Cnt_T_u08 = CM_HwPos_SCom_ClrHwPosTrim();
                        #endif
                    break;
                    case 3U:
                        /* Set Trim */
                        CmdResp_Cnt_T_u08 = CM_HwPos_SCom_SetHwPosTrim();
                        #ifdef D_F003ENABLERELPOSTRIM_CNT_LGC
                            if(CmdResp_Cnt_T_u08 == D_EPSNRCNOERROR_CNT_U08)
                            {
                                CM_AbsHwPos_SCom_SetZeroRev();
                            }
                        #endif
                    break;

                    case 5U:
                        /* Manufacturing Learn Trim */
						#ifndef D_F003DISABLELRNTRIM_CNT_LGC
							CmdResp_Cnt_T_u08 = (uint8)CM_HwPos_SCom_LrnHwPosTrim();
							#ifdef D_F003ENABLERELPOSTRIM_CNT_LGC
								if(CmdResp_Cnt_T_u08 == D_EPSNRCNOERROR_CNT_U08)
								{
									CM_AbsHwPos_SCom_SetZeroRev();
								}
							#endif
						#else
							CmdResp_Cnt_T_u08 = D_EPSNRCPOSSNSRCONDNOTCORRECT_CNT_U08;
						#endif
                    break;

                    default:
                        CmdResp_Cnt_T_u08 = D_EPSNRCREQOUTOFRANGE_CNT_U08;
                    break;
                }
            break;
            default:
                /* Requested sub-function not supported */
                CmdResp_Cnt_T_u08 = D_EPSNRCSUBFUNCNOTSUPP_CNT_U08;
            break;
        }

        *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        return CmdResp_Cnt_T_u08;

    }
#endif /* (D_EPSDIAGSRVRIDF003_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_RID_F004
 *
 *    RID ID:          0xF004
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB),
 *                     Vehicle Speed Too High (0x88),
 *                     Handwheel Torque Too High (0xFE)
 *
 *    Description:     Torque Sensor End of Line Calibration - Digital
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVRIDF004_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_RID_F004 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(uint8, EPSDIAGSRVC_VAR) ControlParam_Cnt_T_u8 = DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16];

        switch (SubFunc_Cnt_T_u08)
        {
            case D_EPSRIDSUBSTART_CNT_U08:
                switch(ControlParam_Cnt_T_u8)
                {
                    case 1U:
                        /* Clear trim */
                        CmdResp_Cnt_T_u08 = CM_DigHwTrq_SCom_ClrHwTrqTrim();
                    break;
                    case 2U:
                        /* Clear Scale */
                        #ifdef D_SENTBASEDSENSOR_CNT_LGC
                            CmdResp_Cnt_T_u08 = D_EPSNRCCONDNOTCORRECT_CNT_U08;
                        #else
                            CmdResp_Cnt_T_u08 = CM_DigHwTrq_SCom_ClrHwTrqScale();
                        #endif
                    break;
                    case 3U:
                        /* Set Trim */
                        CmdResp_Cnt_T_u08 = CM_DigHwTrq_SCom_SetHwTrqTrim();
                    break;
                    default:
                        CmdResp_Cnt_T_u08 = D_EPSNRCREQOUTOFRANGE_CNT_U08;
                    break;
                }
            break;
            default:
                /* Requested sub-function not supported */
                CmdResp_Cnt_T_u08 = D_EPSNRCSUBFUNCNOTSUPP_CNT_U08;
            break;
        }

        *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVRIDF004_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_RID_F005
 *
 *    RID ID:          0xF005
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB)
 *
 *    Description:     DTC Status By Number
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVRIDF005_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_RID_F005 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(NTCNumber, AUTOMATIC) NTC_Cnt_T_enum;
        VAR(uint8, AUTOMATIC) Param_Ptr_T_u08;
        VAR(uint8, AUTOMATIC) Status_Ptr_T_u08;
        VAR(uint8, AUTOMATIC) AgingCounter_Ptr_T_u08;

        switch (SubFunc_Cnt_T_u08)
        {
            case D_EPSRIDSUBSTART_CNT_U08:
                NTC_Cnt_T_enum = bytesToWord_m( DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16],
                                                DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16 + 1U]);

                CM_DiagMgr_SCom_GetNTCInfo( NTC_Cnt_T_enum, &Param_Ptr_T_u08, &Status_Ptr_T_u08, &AgingCounter_Ptr_T_u08 );

                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = Status_Ptr_T_u08;
                ReturnDataIdx_Cnt_T_u16++;
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = Param_Ptr_T_u08;
                ReturnDataIdx_Cnt_T_u16++;
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = AgingCounter_Ptr_T_u08;
                ReturnDataIdx_Cnt_T_u16++;
            break;
            default:
                /* Requested sub-function not supported */
                CmdResp_Cnt_T_u08 = D_EPSNRCSUBFUNCNOTSUPP_CNT_U08;
            break;
        }

        *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVRIDF005_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_RID_F006
 *
 *    RID ID:          0xF006
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB)
 *
 *    Description:     Turns Counter Flash Programming
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVRIDF006_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_RID_F006 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;

        VAR(boolean, EPSDIAGSRVC_VAR) pTcFlashActive_Cnt_T_lgc;
        VAR(uint16, EPSDIAGSRVC_VAR) ptrTcDataCntr_Cnt_T_u16;
        VAR(CM_TcFlshPrgMode_T, EPSDIAGSRVC_VAR) ptrTcPrgState_Uls_T_enum;

        switch (SubFunc_Cnt_T_u08)
        {
            case D_EPSRIDSUBSTART_CNT_U08:
                /* Start Routine */
                CmdResp_Cnt_T_u08 = CM_TcFlshPrg_Scom_StartPrg();
            break;
            case D_EPSRIDSUBSTATUS_CNT_U08:
                /* Request Status */
                CM_TcFlshPrg_Scom_FlshPrgStatus(&pTcFlashActive_Cnt_T_lgc, &ptrTcDataCntr_Cnt_T_u16, &ptrTcPrgState_Uls_T_enum);

                /* Flash Active */
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = pTcFlashActive_Cnt_T_lgc;
                ReturnDataIdx_Cnt_T_u16++;

                /* Data Counter */
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(ptrTcDataCntr_Cnt_T_u16);
                ReturnDataIdx_Cnt_T_u16++;
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(ptrTcDataCntr_Cnt_T_u16);
                ReturnDataIdx_Cnt_T_u16++;

                /* Program State */
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = (uint8)ptrTcPrgState_Uls_T_enum;
                ReturnDataIdx_Cnt_T_u16++;
            break;
            default:
                /* Requested sub-function not supported */
                CmdResp_Cnt_T_u08 = D_EPSNRCSUBFUNCNOTSUPP_CNT_U08;
            break;
        }

        *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVRIDF006_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_RID_F007
 *
 *    RID ID:          0xF007
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB)
 *
 *    Description:     Turns Counter Position EOL Calibration
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVRIDF007_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_RID_F007 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(uint8, EPSDIAGSRVC_VAR) ControlParam_Cnt_T_u8 = DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16];

        switch (SubFunc_Cnt_T_u08)
        {
            case D_EPSRIDSUBSTART_CNT_U08:
                switch(ControlParam_Cnt_T_u8)
                {
                    case 1U:
                        /* Clear Position */
                        #ifdef CM_AbsHwPos_Scom_ClearCenterPosition
                            CM_AbsHwPos_Scom_ClearCenterPosition();
                        #endif
                        #ifdef CM_AbsHwPos_Scom_ClearRacktoVehCntrOffset
                            CM_AbsHwPos_Scom_ClearRacktoVehCntrOffset();
                        #endif
                        #ifdef CM_LrnEOT_Scom_ResetEOT
                            CM_LrnEOT_Scom_ResetEOT();
                        #endif
                        #ifdef CM_LrnEOT_Scom_ResetRckCntrPrf
                            CM_LrnEOT_Scom_ResetRckCntrPrf();
                        #endif
                        #ifdef CM_TurnsCounter_SCom_ResetTC
                            CM_TurnsCounter_SCom_ResetTC();
                        #endif
                    break;
                    case 3U:
                        /* Set Position */
                        #ifdef CM_AbsHwPos_Scom_SetCenterPosition
                            CM_AbsHwPos_Scom_SetCenterPosition(D_ZERO_ULS_F32);
                        #endif
                    break;
                    default:
                        CmdResp_Cnt_T_u08 = D_EPSNRCREQOUTOFRANGE_CNT_U08;
                    break;
                }
            break;
            default:
                /* Requested sub-function not supported */
                CmdResp_Cnt_T_u08 = D_EPSNRCSUBFUNCNOTSUPP_CNT_U08;
            break;
        }

        *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVRIDF007_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_RID_F008
 *
 *    RID ID:          0xF008
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB),
 *                     Vehicle Speed Too High (0x88)
 *
 *    Description:     Current Mode - Current Gain Calc
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVRIDF008_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_RID_F008 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;

        switch (SubFunc_Cnt_T_u08)
        {
            case D_EPSRIDSUBSTART_CNT_U08:
                if (EpsDiagSrvc_CurOffsetRunning_Cnt_M_lgc == TRUE)
                {
                    CmdResp_Cnt_T_u08 = (uint8)CM_CmMtrCurr_SCom_CalGain();
                }
                else
                {
                    /* Request Sequence Error - F009 must be started first */
                    CmdResp_Cnt_T_u08 = D_EPSNRCREQSEQUENCEERR_CNT_U08;
                }
            break;
            default:
                /* Requested sub-function not supported */
                CmdResp_Cnt_T_u08 = D_EPSNRCSUBFUNCNOTSUPP_CNT_U08;
            break;
        }

        *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVRIDF008_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_RID_F009
 *
 *    RID ID:          0xF009
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB),
 *                     Vehicle Speed Too High (0x88)
 *
 *    Description:     Current Mode - Current Offset Calc
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVRIDF009_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_RID_F009 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(MtrCurrOffProcessFlag, AUTOMATIC) MtrcurrOffResult;

        switch (SubFunc_Cnt_T_u08)
        {
            case D_EPSRIDSUBSTART_CNT_U08:
                CmdResp_Cnt_T_u08 = (uint8)CM_CmMtrCurr_SCom_CalOffset();
                if(CmdResp_Cnt_T_u08 == D_EPSNRCNOERROR_CNT_U08)
                {
                    /* Set defeat bits: Defeat Eng On, Ramp Disabled, and ModIndex = 0 */
                    CM_SrlComSvcDft_Cnt_b32 |= D_RIDF009SVCDFTBITSSET_CNT_U16;

                    /* Set clear var to clear defeat bits on session change out of Nexteer session */
                    EpsDiagSrvc_DefeatClrOnSessionChange_Cnt_M_u32 |= D_RIDF009SVCDFTBITSSET_CNT_U16;

                    /* Set the variable to indicate the service is running so that F008 may be run */
                    EpsDiagSrvc_CurOffsetRunning_Cnt_M_lgc = TRUE;
                }
            break;
            case D_EPSRIDSUBSTOP_CNT_U08:
                /* Clear defeat bits: Defeat Eng On, Ramp Disabled, and ModIndex = 0 */
                CM_SrlComSvcDft_Cnt_b32 &= D_RIDF009SVCDFTBITSCLR_CNT_U16;

                /* Just cleared the defeat bits, no need to do it again on session change */
                EpsDiagSrvc_DefeatClrOnSessionChange_Cnt_M_u32 &= D_RIDF009SVCDFTBITSCLR_CNT_U16;

                /* Stop F008 for being run */
                EpsDiagSrvc_CurOffsetRunning_Cnt_M_lgc = FALSE;
            break;
            case D_EPSRIDSUBSTATUS_CNT_U08:
                CM_CmMtrCurr_SCom_MtrCurrOffReadStatus(&MtrcurrOffResult);
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = (uint8)MtrcurrOffResult;
                ReturnDataIdx_Cnt_T_u16++;
            break;
            default:
                /* Requested sub-function not supported */
                CmdResp_Cnt_T_u08 = D_EPSNRCSUBFUNCNOTSUPP_CNT_U08;
            break;
        }

        *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVRIDF009_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_RID_F00A
 *
 *    RID ID:          0xF00A
 *
 *    Configured NRCs: N/A
 *
 *    Description:     Write RAM to EEPROM Service
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVRIDF00A_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_RID_F00A (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;

        switch (SubFunc_Cnt_T_u08)
        {
            case D_EPSRIDSUBSTART_CNT_U08:
                /* TODO: Define this service - currently TBD in Spec 05A */
                CmdResp_Cnt_T_u08 = D_EPSNRCREQOUTOFRANGE_CNT_U08;
            break;
            default:
                /* Requested sub-function not supported */
                CmdResp_Cnt_T_u08 = D_EPSNRCSUBFUNCNOTSUPP_CNT_U08;
            break;
        }

        *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVRIDF00A_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_RID_F00B
 *
 *    RID ID:          0xF00B
 *
 *    Configured NRCs: N/A
 *
 *    Description:     Unused
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVRIDF00B_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_RID_F00B (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;

        switch (SubFunc_Cnt_T_u08)
        {
            case D_EPSRIDSUBSTART_CNT_U08:
                /* Unused - Return 0x31 */
                CmdResp_Cnt_T_u08 = D_EPSNRCREQOUTOFRANGE_CNT_U08;
            break;
            default:
                /* Requested sub-function not supported */
                CmdResp_Cnt_T_u08 = D_EPSNRCSUBFUNCNOTSUPP_CNT_U08;
            break;
        }

        *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVRIDF00B_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_RID_F00C
 *
 *    RID ID:          0xF00C
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB)
 *
 *    Description:     Clear Turns Counter EOL Calibrations
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVRIDF00C_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_RID_F00C (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(uint8, EPSDIAGSRVC_VAR) ControlParam_Cnt_T_u8 = DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16];

        switch (SubFunc_Cnt_T_u08)
        {
            case D_EPSRIDSUBSTART_CNT_U08:
                switch(ControlParam_Cnt_T_u8)
                {
                    case 1U:
                        /* Clear Trim Values */
                        CM_TcEOLCals_Scom_ClearTcEOLCals();
                    break;
                    default:
                        CmdResp_Cnt_T_u08 = D_EPSNRCREQOUTOFRANGE_CNT_U08;
                    break;
                }
            break;
            default:
                /* Requested sub-function not supported */
                CmdResp_Cnt_T_u08 = D_EPSNRCSUBFUNCNOTSUPP_CNT_U08;
            break;
        }

        *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVRIDF00C_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_RID_F00D
 *
 *    RID ID:          0xF00D
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB)
 *
 *    Description:     Voltage Mode - Calculate Current Gain
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVRIDF00D_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_RID_F00D (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(uint8, EPSDIAGSRVC_VAR) ControlParam_Cnt_T_u8 = DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16];

        switch (SubFunc_Cnt_T_u08)
        {
            case D_EPSRIDSUBSTART_CNT_U08:
                switch(ControlParam_Cnt_T_u8)
                {
                    case 3U:
                        /* Set Gain */
                        CmdResp_Cnt_T_u08 = CM_MtrCurr_SCom_CalGain();
                    break;
                    default:
                        CmdResp_Cnt_T_u08 = D_EPSNRCREQOUTOFRANGE_CNT_U08;
                    break;
                }
            break;
            default:
                /* Requested sub-function not supported */
                CmdResp_Cnt_T_u08 = D_EPSNRCSUBFUNCNOTSUPP_CNT_U08;
            break;
        }

        *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVRIDF00D_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_RID_F00E
 *
 *    RID ID:          0xF00E
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB)
 *
 *    Description:     Voltage Mode - Set Current Offset
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVRIDF00E_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_RID_F00E (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(uint8, EPSDIAGSRVC_VAR) ControlParam_Cnt_T_u8 = DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16];

        switch (SubFunc_Cnt_T_u08)
        {
            case D_EPSRIDSUBSTART_CNT_U08:
                switch(ControlParam_Cnt_T_u8)
                {
                    case 3U:
                        /* Set Offset */
                        CM_MtrCurr_SCom_CalOffset();

                        /* Set defeat bits: Defeat Eng On, Ramp Disabled, and ModIndex = 0 */
                        CM_SrlComSvcDft_Cnt_b32 |= D_RIDF00ESVCDFTBITSSET_CNT_U16;
                        /* Set clear var to clear defeat bits on session change out of Nexteer session */
                        EpsDiagSrvc_DefeatClrOnSessionChange_Cnt_M_u32 |= D_RIDF00ESVCDFTBITSSET_CNT_U16;
                    break;
                    default:
                        CmdResp_Cnt_T_u08 = D_EPSNRCREQOUTOFRANGE_CNT_U08;
                    break;
                }
            break;
            default:
                /* Requested sub-function not supported */
                CmdResp_Cnt_T_u08 = D_EPSNRCSUBFUNCNOTSUPP_CNT_U08;
            break;
        }

        *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVRIDF00E_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_RID_F00F
 *
 *    RID ID:          0xF00F
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB)
 *
 *    Description:     Neteer Goto Position
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVRIDF00F_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_RID_F00F (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;

        VAR(sint16, AUTOMATIC) TrgtHwPos_HwDeg_T_s15p0;
        VAR(float32, AUTOMATIC) TrgtHwPos_HwDeg_T_f32;
        VAR(uint16, AUTOMATIC) TrgtHwVel_Cnt_T_u16p0;
        VAR(uint16, AUTOMATIC) TrgtHwVel_DegpS_T_u16p0;
        VAR(float32, AUTOMATIC) TrgtHwVel_DegpS_T_f32;
        VAR(uint16, AUTOMATIC) TrgtHwAccel_Cnt_T_u16p0;
        VAR(uint16, AUTOMATIC) TrgtHwAccel_DegpSSqrd_T_u16p0;
        VAR(float32, AUTOMATIC) TrgtHwAccel_DegpSSqrd_T_f32;

        switch(SubFunc_Cnt_T_u08)
        {
            case D_EPSRIDSUBSTART_CNT_U08:
                /* Start Routine */
                if ((DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16 + 4U] == 0x01U) ||
                    (DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16 + 4U] == 0x00U))
                {
                    if (GenPosTrajRoutineStatus_Cnt_M_enum != F00F_ACTIVE)
                    {

                        TrgtHwPos_HwDeg_T_s15p0 = (sint16)(bytesToWord_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16 + 1U]));
                        TrgtHwVel_Cnt_T_u16p0 = (uint16)DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16 + 2U];
                        TrgtHwAccel_Cnt_T_u16p0 = (uint16)DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16 + 3U];
                        EpsDiagSrvc_AbsPosTrajReq_Cnt_M_lgc = (boolean)(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16 + 4U]);
                        GenPosTrajRoutineStatus_Cnt_M_enum = F00FCheckConditions(EpsDiagSrvc_AbsPosTrajReq_Cnt_M_lgc);

                        if (F00F_ACTIVE == GenPosTrajRoutineStatus_Cnt_M_enum)
                        {
                            TrgtHwPos_HwDeg_T_f32 = FPM_FixedToFloat_m(TrgtHwPos_HwDeg_T_s15p0, s15p0_T) * (float32)k_CMSGotoPosPol_Cnt_s08;
                            EpsDiagSrvc_PosTrajTrgtHWPos_HwDeg_M_f32 = Limit_m(TrgtHwPos_HwDeg_T_f32, -D_RIDF00FTRGTHWPOSLMT_HWDEGS_F32, D_RIDF00FTRGTHWPOSLMT_HWDEGS_F32);

                            if ((DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16 + 4U]) == 0U) /* If the service requested is relative */
                            {
                                EpsDiagSrvc_PosTrajTrgtHWPos_HwDeg_M_f32 = Limit_m((CM_Rte_AbsHwPos_SrlComHwPos_HwDeg_f32 + TrgtHwPos_HwDeg_T_f32), -D_MAXHWPOSITION_HWDEG_F32, D_MAXHWPOSITION_HWDEG_F32);
                            }

                            TrgtHwVel_DegpS_T_u16p0 = TrgtHwVel_Cnt_T_u16p0 * D_RIDF00FTRGTHWVELSCALE_DEGPSPSEC_U16;
                            TrgtHwVel_DegpS_T_f32 = FPM_FixedToFloat_m(TrgtHwVel_DegpS_T_u16p0, u16p0_T);
                            EpsDiagSrvc_TrgtHwVel_DegpS_M_f32 = Limit_m(TrgtHwVel_DegpS_T_f32, D_RIDF00FTRGTHWVELLOLMT_DEGPS_F32, D_RIDF00FTRGTHWVELHILMT_DEGPS_F32);

                            TrgtHwAccel_DegpSSqrd_T_u16p0 = TrgtHwAccel_Cnt_T_u16p0 * D_RIDF00FTRGTHWACCELSCALE_DEGPSSQRDPCNT_U16;
                            TrgtHwAccel_DegpSSqrd_T_f32 = FPM_FixedToFloat_m(TrgtHwAccel_DegpSSqrd_T_u16p0, u16p0_T);
                            EpsDiagSrvc_TrgtHwAccel_DegpSSqrd_M_f32 = Limit_m(TrgtHwAccel_DegpSSqrd_T_f32, D_RIDF00FTRGTHWACCELLOLMT_DEGSPSSQRD_F32, D_RIDF00FTRGTHWACCELHILMT_DEGSPSSQRD_F32);

                            CDD_GenPosTrajEnableFlag_Cnt_G_lgc = TRUE;
                            GetSystemTime_mS_u32(&EpsDiagSrvc_HandsONAbortTime_Cnt_M_u32);
                            CM_GenPosTraj_SCom_SetInputParam(EpsDiagSrvc_PosTrajTrgtHWPos_HwDeg_M_f32, EpsDiagSrvc_TrgtHwVel_DegpS_M_f32, EpsDiagSrvc_TrgtHwAccel_DegpSSqrd_M_f32);
                        }
                        else
                        {
                            /* Conditions not correct to start */
                            /* Send request status command (03) to determine specific reason */
                            CmdResp_Cnt_T_u08 = D_EPSNRCCONDNOTCORRECT_CNT_U08;
                        }
                    }
                    else
                    {
                        /* Request sequence error */
                        CmdResp_Cnt_T_u08 = D_EPSNRCREQSEQUENCEERR_CNT_U08;
                    }

                }
                else
                {
                    /* Request data out of range */
                    CmdResp_Cnt_T_u08 = D_EPSNRCREQOUTOFRANGE_CNT_U08;
                }

            break;
            case D_EPSRIDSUBSTOP_CNT_U08:
                /* Stop Routine */
                if (GenPosTrajRoutineStatus_Cnt_M_enum == F00F_ACTIVE)
                {
                    CDD_GenPosTrajEnableFlag_Cnt_G_lgc = FALSE;
                    GenPosTrajRoutineStatus_Cnt_M_enum = F00F_CANCELLED;
                    EpsDiagSrvc_MonitorSystemState_Cnt_M_lgc = FALSE;
                }
                else
                {
                    /* Request sequence error */
                    CmdResp_Cnt_T_u08 = D_EPSNRCREQSEQUENCEERR_CNT_U08;
                }
            break;
            case D_EPSRIDSUBSTATUS_CNT_U08:
                /* Request Status */
                if (GenPosTrajRoutineStatus_Cnt_M_enum != F00F_DEFAULT)
                {
                    DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = (uint8)GenPosTrajRoutineStatus_Cnt_M_enum;
                    ReturnDataIdx_Cnt_T_u16++;
                }
                else
                {
                    /* Request sequence error */
                    CmdResp_Cnt_T_u08 = D_EPSNRCREQSEQUENCEERR_CNT_U08;
                }
            break;
            default:
                /* Sub-function not supported */
                CmdResp_Cnt_T_u08 = D_EPSNRCSUBFUNCNOTSUPP_CNT_U08;
            break;

        }

        *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVRIDF00F_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_RID_F0FF
 *
 *    RID ID:          0xF0FF
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB)
 *
 *    Description:     MPU/Program Flow Test
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVRIDF0FF_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_RID_F0FF (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;

        switch (SubFunc_Cnt_T_u08)
        {
            case D_EPSRIDSUBSTART_CNT_U08:
                if (TRUE != CM_EnableTestMode_Cnt_lgc)
                {
                    CmdResp_Cnt_T_u08 = D_EPSNRCCONDNOTCORRECT_CNT_U08;
                }
                else if (   (DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16] > 3U) ||
                            (DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16] < 1U))
                {
                    CmdResp_Cnt_T_u08 = D_EPSNRCREQOUTOFRANGE_CNT_U08;
                }
                else
                {
                    /* Trusted Function Call */
                    CM_ProcessF0FF(DataBuffer_Uls_T_u08, RequestDataIdx_Cnt_T_u16);
                }
            break;
            default:
                /* Requested sub-function not supported */
                CmdResp_Cnt_T_u08 = D_EPSNRCSUBFUNCNOTSUPP_CNT_U08;
            break;
        }

        *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVRIDF0FF_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FD01
 *
 *    PID ID:          0xFD01
 *
 *    Configured NRCs: N/A
 *
 *    Description:     Internal Software Identifier
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFD01_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD01 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
		/* PRQA S 310 85
		* MISRA-C: 2004 Rule 11.4: This deviation is required*/


        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(uint16, EPSDIAGSRVC_VAR) DataSize_Cnt_T_u16;
        VAR(uint8, EPSDIAGSRVC_VAR) TempByte_Cnt_T_u8;
        VAR(uint16, EPSDIAGSRVC_VAR) i;

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
            CmdResp_Cnt_T_u08 = D_EPSNRCREQOUTOFRANGE_CNT_U08;
        }
        else
        {
            /* Read Service */
            /* SW Release */
            DataSize_Cnt_T_u16 = sizeof(CM_SwRelNum_Cnt_u08)/sizeof(uint8);
            for (i = 0U; i < DataSize_Cnt_T_u16; i++)
            {
                TempByte_Cnt_T_u8 = CM_SwRelNum_Cnt_u08[i];
                if ( TempByte_Cnt_T_u8 != (uint8)CM_NULL )
                {
                    DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = TempByte_Cnt_T_u8;
                    ReturnDataIdx_Cnt_T_u16++;
                }
                else
                {
                    /* Break loop */
                    break;
                }
            }

            /* Add delimiter in */
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = (uint8)',';
            ReturnDataIdx_Cnt_T_u16++;

            /* Cal Release */
            DataSize_Cnt_T_u16 = sizeof(CM_CalRelNum_Cnt_u08)/sizeof(uint8);
            for (i = 0U; i < DataSize_Cnt_T_u16; i++)
            {
                TempByte_Cnt_T_u8 = CM_CalRelNum_Cnt_u08[i];
                if ( TempByte_Cnt_T_u8 != (uint8)CM_NULL )
                {
                    DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = TempByte_Cnt_T_u8;
                    ReturnDataIdx_Cnt_T_u16++;
                }
                else
                {
                    /* Break loop */
                    break;
                }
            }

            /* Add delimiter in */
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = (uint8)',';
            ReturnDataIdx_Cnt_T_u16++;

            /* Bootloader Part Number */
            #ifdef CM_BootRelNum_Cnt_u08
                DataSize_Cnt_T_u16 = 50U;
                for (i = 0U; i < DataSize_Cnt_T_u16; i++)
                {
                    TempByte_Cnt_T_u8 = ((uint8 *)&CM_BootRelNum_Cnt_u08)[i]; /* PRQA S 311 */
                    if ( TempByte_Cnt_T_u8 != (uint8)CM_NULL )
                    {
                        DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = TempByte_Cnt_T_u8;
                        ReturnDataIdx_Cnt_T_u16++;
                    }
                    else
                    {
                        /* Break loop */
                        break;
                    }
                }
            #endif

            /* Null termination */
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = (uint8)CM_NULL;
            ReturnDataIdx_Cnt_T_u16++;

            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFD01_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FD02
 *
 *    PID ID:          0xFD02
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB)
 *
 *    Description:     Serial Communication Service Active (Defeats)
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFD02_CNT_ENUM == D_DIAGSRVC_ENABLED)
	FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD02 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
	{
		/* PRQA S 310 80
		* MISRA-C: 2004 Rule 11.4: This deviation is required*/

		/* Local Vars */
		VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
		VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestDataIdx_Cnt_T_u16 = 0U;
		VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
		VAR(uint32, EPSDIAGSRVC_VAR) Diagtemp_Cnt_T_u32;

		if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
		{
			/* Write Service */
			Diagtemp_Cnt_T_u32 = uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_MSBYTESHIFT_CNT_U16);
			Diagtemp_Cnt_T_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16 + 1u)], D_WORDSHIFT_CNT_U16);
			Diagtemp_Cnt_T_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16 + 2u)], D_BYTESHIFT_CNT_U16);
			Diagtemp_Cnt_T_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16 + 3u)], 0u);

			if (((Diagtemp_Cnt_T_u32 & D_SVCDFTMODIDX_CNT_B32) == D_SVCDFTMODIDX_CNT_B32) &&
				(CM_VehicleSpeed_Kph_f32 > 0.0f))
			{
				CmdResp_Cnt_T_u08 = D_EPSNRCVEHSPDTHRSHOLD_CNT_U08;
			}
			else
			{
				EpsDiagSrvc_DefeatClrOnSessionChange_Cnt_M_u32 = 0U;

				/* Update the defeat variable */
				CM_SrlComSvcDft_Cnt_b32 = Diagtemp_Cnt_T_u32;

				if (D_SVCDFTRXMSGS_CNT_B32 == (CM_SrlComSvcDft_Cnt_b32 & D_SVCDFTRXMSGS_CNT_B32))
				{
					/* TODO: complete definition of vehicle speed override for d_SvcDftRxCANMsgs_Cnt_b32 */
					EpsDiagSrvc_VehSpdOverride_Kph_M_u16p0 = FPM_FloatToFixed_m(CM_VehicleSpeed_Kph_f32, u16p0_T);
				}

				/* Check for multiple ign cycle storage */

				if((CM_SrlComSvcDft_Cnt_b32 & D_UPPERNIBBLEMASK_CNT_U32) != D_SVCDFTMULTIGNMASK_CNT_B32)
				{
					/* Defeats are not stored, zero out buffer and write the block to zero */
					EpsDiagSrvc_DiagSrvDftBuffer_Uls_M_u32 = 0uL;

					/* Use the buffered data instead of the NvM RAM block to void write conflicts */
					(void)NvM_WriteBlock(NVM_BLOCK_EPSDEFEATS, (P2CONST(uint8, AUTOMATIC, AUTOMATIC))&EpsDiagSrvc_DiagSrvDftBuffer_Uls_M_u32);
				}
				else
				{
					/* Defeats are to be stored over ign cycles, update the buffer with the passed data and write the block */
					EpsDiagSrvc_DiagSrvDftBuffer_Uls_M_u32 = CM_SrlComSvcDft_Cnt_b32;
					(void)NvM_WriteBlock(NVM_BLOCK_EPSDEFEATS, (P2CONST(uint8, AUTOMATIC, AUTOMATIC))&EpsDiagSrvc_DiagSrvDftBuffer_Uls_M_u32);
				}
			}
		}
		else
		{
			/* Read Service */
			Diagtemp_Cnt_T_u32 = CM_SrlComSvcDft_Cnt_b32;
			DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(Diagtemp_Cnt_T_u32, D_MSBYTESHIFT_CNT_U16);
			ReturnDataIdx_Cnt_T_u16++;
			DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(Diagtemp_Cnt_T_u32, D_WORDSHIFT_CNT_U16);
			ReturnDataIdx_Cnt_T_u16++;
			DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(Diagtemp_Cnt_T_u32, D_BYTESHIFT_CNT_U16);
			ReturnDataIdx_Cnt_T_u16++;
			DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(Diagtemp_Cnt_T_u32, 0u);
			ReturnDataIdx_Cnt_T_u16++;
			*RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
		}

		return CmdResp_Cnt_T_u08;
	}
#endif /* (D_EPSDIAGSRVPIDFD02_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FD03
 *
 *    PID ID:          0xFD03
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB)
 *
 *    Description:     End of Line Position Sensor
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFD03_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD03 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(CM_HwPosRelCal_DataType, EPSDIAGSRVC_VAR) EOLHwPosPID;
        VAR(uint16, EPSDIAGSRVC_VAR) Diagtemp_Cnt_T_u16;

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
            SuspendAllInterrupts();
            CM_HwPosRel_SCom_ReadHwPosCals(&EOLHwPosPID);
            ResumeAllInterrupts();

            EOLHwPosPID.HwPosRelTrim_HwDeg_s11p4 = (sint16)bytesToWord_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16+1u)]);
            EOLHwPosPID.EOLHwPosTrmPerf_Cnt_u16 = bytesToWord_m(DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16+2u)], DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16+3u)]);

            SuspendAllInterrupts();
            CM_HwPosRel_SCom_SetHwPosCals(&EOLHwPosPID);
            ResumeAllInterrupts();
        }
        else
        {
            /* Read Service */
            SuspendAllInterrupts();
            CM_HwPosRel_SCom_ReadHwPosCals(&EOLHwPosPID);
            ResumeAllInterrupts();

            Diagtemp_Cnt_T_u16 = (uint16)EOLHwPosPID.HwPosRelTrim_HwDeg_s11p4;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(Diagtemp_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(Diagtemp_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;

            Diagtemp_Cnt_T_u16 = EOLHwPosPID.EOLHwPosTrmPerf_Cnt_u16;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(Diagtemp_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(Diagtemp_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;

            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFD03_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FD04
 *
 *    PID ID:          0xFD04
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB)
 *
 *    Description:     End of Line Sine/Cosine Motor Parameters
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFD04_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD04 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(CM_MtrPosCal_DataType, EPSDIAGSRVC_VAR) MtrPosCals_T_str;

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
            /* BEMF Cal */
            MtrPosCals_T_str.BEMFCal_Rev_u0p16 = bytesToWord_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16 + 1u)]);
            RequestDataIdx_Cnt_T_u16 += 2u;

            /* Sin 1 Offset */
            MtrPosCals_T_str.Sin1Offset_Volts_u3p13 = bytesToWord_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16 + 1u)]);
            RequestDataIdx_Cnt_T_u16 += 2u;

            /* Sin 1 Amp */
            MtrPosCals_T_str.Sin1AmpRec_Uls_u3p13 = bytesToWord_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16 + 1u)]);
            RequestDataIdx_Cnt_T_u16 += 2u;

            /* Cos 1 Offset */
            MtrPosCals_T_str.Cos1Offset_Volts_u3p13 = bytesToWord_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16 + 1u)]);
            RequestDataIdx_Cnt_T_u16 += 2u;

            /* Cos 1 Amp */
            MtrPosCals_T_str.Cos1AmpRec_Uls_u3p13 = bytesToWord_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16 + 1u)]);
            RequestDataIdx_Cnt_T_u16 += 2u;

            /* Sin 1 Delta */
            MtrPosCals_T_str.SinDelta1_Uls_s2p13 = (sint16)bytesToWord_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16 + 1u)]);
            RequestDataIdx_Cnt_T_u16 += 2u;

            /* Cos 1 Delta */
            MtrPosCals_T_str.CosDelta1Rec_Uls_u3p13 = bytesToWord_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16 + 1u)]);
            RequestDataIdx_Cnt_T_u16 += 2u;

            /* Programs with updated MtrPos don't use the ***2 parameters.  To make CMS backwards compatible
             * The follow was added so that programs using an older version of MtrPos, still requiring these
             * parameters, may define D_FD04_USEDEPRECATEDPARAMS_CNT_LGC in their interface header to enable
             * the parsing of the information.  Otherwise, the following 12 bytes are skipped.
             */
            #ifdef D_FD04_USEDEPRECATEDPARAMS_CNT_LGC

                /* Sin 2 Offset */
                MtrPosCals_T_str.Sin2Offset_Volts_u3p13 = bytesToWord_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16 + 1u)]);
                RequestDataIdx_Cnt_T_u16 += 2u;

                /* Sin 2 Amp */
                MtrPosCals_T_str.Sin2AmpRec_Uls_u3p13 = bytesToWord_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16 + 1u)]);
                RequestDataIdx_Cnt_T_u16 += 2u;

                /* Cos 2 Offset */
                MtrPosCals_T_str.Cos2Offset_Volts_u3p13 = bytesToWord_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16 + 1u)]);
                RequestDataIdx_Cnt_T_u16 += 2u;

                /* Cos 2 Amp */
                MtrPosCals_T_str.Cos2AmpRec_Uls_u3p13 = bytesToWord_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16 + 1u)]);
                RequestDataIdx_Cnt_T_u16 += 2u;

                /* Sin 2 Delta */
                MtrPosCals_T_str.SinDelta2_Uls_s2p13 = (sint16)bytesToWord_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16 + 1u)]);
                RequestDataIdx_Cnt_T_u16 += 2u;

                /* Cos 2 Delta */
                MtrPosCals_T_str.CosDelta2Rec_Uls_u3p13 = bytesToWord_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16 + 1u)]);
                RequestDataIdx_Cnt_T_u16 += 2u;

            #else

                /* Skip the deprecated Sin 2 Offset, Sin 2 Amp, Cos 2 Offset, Cos 2 Amp, Sin2 Delta, and Cos 2 Delta parameters */
                RequestDataIdx_Cnt_T_u16 += 12u;

            #endif /* D_FD04_USEDEPRECATEDPARAMS_CNT_LGC */

            /* Sin 1 Off Corr */
            MtrPosCals_T_str.Sin1OffCorr_Volts_s2p13 = (sint16)bytesToWord_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16 + 1u)]);
            RequestDataIdx_Cnt_T_u16 += 2u;

            /* Sin 1 Gain Corr */
            MtrPosCals_T_str.Sin1GainCorr_Uls_u1p15 = bytesToWord_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16 + 1u)]);
            RequestDataIdx_Cnt_T_u16 += 2u;

            /* Cos 1 Off Corr */
            MtrPosCals_T_str.Cos1OffCorr_Volts_s2p13 = (sint16)bytesToWord_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16 + 1u)]);
            RequestDataIdx_Cnt_T_u16 += 2u;

            /* Cos 1 Gain Corr */
            MtrPosCals_T_str.Cos1GainCorr_Uls_u1p15 = bytesToWord_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16 + 1u)]);
            RequestDataIdx_Cnt_T_u16 += 2u;

            /* Sin Har Tbl */
            (void)memcpy((void*)MtrPosCals_T_str.SinHarTbl_Cnt_sm6p13, (void*)&(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16]), D_HARTBLSIZE_CNT_U16);
            RequestDataIdx_Cnt_T_u16 += D_HARTBLSIZE_CNT_U16;

            /* Cos Har Tbl */
            (void)memcpy((void*)MtrPosCals_T_str.CosHarTbl_Cnt_sm6p13, (void*)&(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16]), D_HARTBLSIZE_CNT_U16);
            RequestDataIdx_Cnt_T_u16 += D_HARTBLSIZE_CNT_U16;

            CM_MtrPos_SCom_SetEOLMtrCals(&MtrPosCals_T_str);
        }
        else
        {
            /* Read Service */
            CM_MtrPos_SCom_ReadEOLMtrCals(&MtrPosCals_T_str);

            /* BEMF Cal */
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(MtrPosCals_T_str.BEMFCal_Rev_u0p16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(MtrPosCals_T_str.BEMFCal_Rev_u0p16);
            ReturnDataIdx_Cnt_T_u16++;

            /* Sin 1 Offset */
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(MtrPosCals_T_str.Sin1Offset_Volts_u3p13);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(MtrPosCals_T_str.Sin1Offset_Volts_u3p13);
            ReturnDataIdx_Cnt_T_u16++;

            /* Sin 1 Amp */
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(MtrPosCals_T_str.Sin1AmpRec_Uls_u3p13);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(MtrPosCals_T_str.Sin1AmpRec_Uls_u3p13);
            ReturnDataIdx_Cnt_T_u16++;

            /* Cos 1 Offset */
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(MtrPosCals_T_str.Cos1Offset_Volts_u3p13);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(MtrPosCals_T_str.Cos1Offset_Volts_u3p13);
            ReturnDataIdx_Cnt_T_u16++;

            /* Cos 1 Amp */
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(MtrPosCals_T_str.Cos1AmpRec_Uls_u3p13);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(MtrPosCals_T_str.Cos1AmpRec_Uls_u3p13);
            ReturnDataIdx_Cnt_T_u16++;

            /* Sin 1 Delta */
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(MtrPosCals_T_str.SinDelta1_Uls_s2p13);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(MtrPosCals_T_str.SinDelta1_Uls_s2p13);
            ReturnDataIdx_Cnt_T_u16++;

            /* Cos 1 Delta */
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(MtrPosCals_T_str.CosDelta1Rec_Uls_u3p13);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(MtrPosCals_T_str.CosDelta1Rec_Uls_u3p13);
            ReturnDataIdx_Cnt_T_u16++;

            /* Programs with updated MtrPos don't use the ***2 parameters.  To make CMS backwards compatible
             * The follow was added so that programs using an older version of MtrPos, still requiring these
             * parameters, may define D_FD04_USEDEPRECATEDPARAMS_CNT_LGC in their interface header to enable
             * the return of the information.  Otherwise, the following 12 bytes are filled with zeros.
             */
            #ifdef D_FD04_USEDEPRECATEDPARAMS_CNT_LGC

                /* Sin 2 Offset */
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(MtrPosCals_T_str.Sin2Offset_Volts_u3p13);
                ReturnDataIdx_Cnt_T_u16++;
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(MtrPosCals_T_str.Sin2Offset_Volts_u3p13);
                ReturnDataIdx_Cnt_T_u16++;

                /* Sin 2 Amp */
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(MtrPosCals_T_str.Sin2AmpRec_Uls_u3p13);
                ReturnDataIdx_Cnt_T_u16++;
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(MtrPosCals_T_str.Sin2AmpRec_Uls_u3p13);
                ReturnDataIdx_Cnt_T_u16++;

                /* Cos 2 Offset */
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(MtrPosCals_T_str.Cos2Offset_Volts_u3p13);
                ReturnDataIdx_Cnt_T_u16++;
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(MtrPosCals_T_str.Cos2Offset_Volts_u3p13);
                ReturnDataIdx_Cnt_T_u16++;

                /* Cos 2 Amp */
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(MtrPosCals_T_str.Cos2AmpRec_Uls_u3p13);
                ReturnDataIdx_Cnt_T_u16++;
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(MtrPosCals_T_str.Cos2AmpRec_Uls_u3p13);
                ReturnDataIdx_Cnt_T_u16++;

                /* Sin 2 Delta */
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(MtrPosCals_T_str.SinDelta2_Uls_s2p13);
                ReturnDataIdx_Cnt_T_u16++;
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(MtrPosCals_T_str.SinDelta2_Uls_s2p13);
                ReturnDataIdx_Cnt_T_u16++;

                /* Cos 2 Delta */
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(MtrPosCals_T_str.CosDelta2Rec_Uls_u3p13);
                ReturnDataIdx_Cnt_T_u16++;
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(MtrPosCals_T_str.CosDelta2Rec_Uls_u3p13);
                ReturnDataIdx_Cnt_T_u16++;

            #else

                /* Provide 0's for the deprecated Sin 2 Offset, Sin 2 Amp, Cos 2 Offset, Cos 2 Amp, Sin2 Delta, and Cos 2 Delta parameters */
                (void)memset((void*)&(DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16]), 0, 12u);
                ReturnDataIdx_Cnt_T_u16 += 12u;

            #endif /* D_FD04_USEDEPRECATEDPARAMS_CNT_LGC */

            /* Sin 1 Off Corr */
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(MtrPosCals_T_str.Sin1OffCorr_Volts_s2p13);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(MtrPosCals_T_str.Sin1OffCorr_Volts_s2p13);
            ReturnDataIdx_Cnt_T_u16++;

            /* Sin 1 Gain Corr */
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(MtrPosCals_T_str.Sin1GainCorr_Uls_u1p15);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(MtrPosCals_T_str.Sin1GainCorr_Uls_u1p15);
            ReturnDataIdx_Cnt_T_u16++;

            /* Cos 1 Off Corr */
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(MtrPosCals_T_str.Cos1OffCorr_Volts_s2p13);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(MtrPosCals_T_str.Cos1OffCorr_Volts_s2p13);
            ReturnDataIdx_Cnt_T_u16++;

            /* Cos 1 Gain Corr */
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(MtrPosCals_T_str.Cos1GainCorr_Uls_u1p15);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(MtrPosCals_T_str.Cos1GainCorr_Uls_u1p15);
            ReturnDataIdx_Cnt_T_u16++;

            /* Sin Har Tbl */
            (void)memcpy((void*)&(DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16]), (void*)MtrPosCals_T_str.SinHarTbl_Cnt_sm6p13, D_HARTBLSIZE_CNT_U16);
            ReturnDataIdx_Cnt_T_u16+=D_HARTBLSIZE_CNT_U16;

            /* Cos Har Tbl */
            (void)memcpy((void*)&(DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16]), (void*)MtrPosCals_T_str.CosHarTbl_Cnt_sm6p13, D_HARTBLSIZE_CNT_U16);
            ReturnDataIdx_Cnt_T_u16+=D_HARTBLSIZE_CNT_U16;

            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFD04_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FD05
 *
 *    PID ID:          0xFD05
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB)
 *
 *    Description:     End of Line Torque Sensor - Analog
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFD05_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD05 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(CM_HwTrqTrim_Datatype, EPSDIAGSRVC_VAR) HwTrqTrimData;
        VAR(EPS_DiagSrv_DataStr, EPSDIAGSRVC_VAR) TempData;

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
            TempData.type.IntData_u32 = uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_MSBYTESHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            TempData.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_WORDSHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            TempData.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_BYTESHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            TempData.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_ZERO_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;

            HwTrqTrimData.HwTrqTrim_Volts_f32 = TempData.type.FloatData_f32;

            TempData.type.IntData_u32 = uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_MSBYTESHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            TempData.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_WORDSHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            TempData.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_BYTESHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            TempData.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_ZERO_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;

            HwTrqTrimData.T1Trim_Volts_f32 = TempData.type.FloatData_f32;

            TempData.type.IntData_u32 = uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_MSBYTESHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            TempData.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_WORDSHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            TempData.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_BYTESHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            TempData.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_ZERO_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;

            HwTrqTrimData.T2Trim_Volts_f32 = TempData.type.FloatData_f32;

            HwTrqTrimData.HwTrqTrimPerf_Cnt_lgc = (uint8)DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16];
            RequestDataIdx_Cnt_T_u16++;

            CM_HwTrq_SCom_ManualSetHwTrqTrim(&HwTrqTrimData);
        }
        else
        {
            /* Read Service */
            CM_HwTrq_SCom_ReadHwTrqTrim(&HwTrqTrimData);

            TempData.type.FloatData_f32 = HwTrqTrimData.HwTrqTrim_Volts_f32;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_MSBYTESHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_WORDSHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_BYTESHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_ZERO_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;

            TempData.type.FloatData_f32 = HwTrqTrimData.T1Trim_Volts_f32;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_MSBYTESHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_WORDSHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_BYTESHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_ZERO_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;

            TempData.type.FloatData_f32 = HwTrqTrimData.T2Trim_Volts_f32;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_MSBYTESHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_WORDSHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_BYTESHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_ZERO_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;

            /* Torque Performed Status */
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = HwTrqTrimData.HwTrqTrimPerf_Cnt_lgc;
            ReturnDataIdx_Cnt_T_u16++;

            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFD05_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FD06
 *
 *    PID ID:          0xFD06
 *
 *    Configured NRCs: N/A
 *
 *    Description:     End of Line Digital Motor Parameters
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFD06_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD06 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
            /* Write not supported */
            CmdResp_Cnt_T_u08 = D_EPSNRCREQOUTOFRANGE_CNT_U08;
        }
        else
        {
            /* Read Service */
            /* Request Out of Range */
            CmdResp_Cnt_T_u08 = D_EPSNRCREQOUTOFRANGE_CNT_U08;
            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFD06_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FD07
 *
 *    PID ID:          0xFD07
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB)
 *
 *    Description:     End of Line Polarity
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFD07_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD07 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        #ifdef D_FD07_USE8BITPOLARITY_CNT_LGC
            VAR(uint8, EPSDIAGSRVC_VAR) Polarity_Cnt_T_b08;

            if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
            {
                /* Write Service */
                Polarity_Cnt_T_b08 = DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16];

                if ((Polarity_Cnt_T_b08 & 0xC0) != 0U)
                {
                    CmdResp_Cnt_T_u08 = D_EPSNRCREQOUTOFRANGE_CNT_U08;
                }
                else
                {
                    CM_Polarity_SCom_SetPolarity(Polarity_Cnt_T_b08);
                }
            }
            else
            {
                /* Read Service */
                CM_Polarity_SCom_ReadPolarity(&Polarity_Cnt_T_b08);
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = Polarity_Cnt_T_b08;
                ReturnDataIdx_Cnt_T_u16++;

                *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
            }
        #else /* Polarity Component pre ver 007.3 sill uses the 16 bit interface below */
            VAR(uint16, EPSDIAGSRVC_VAR) Diagtemp_Cnt_T_u16;

            if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
            {
                /* Write Service */
                Diagtemp_Cnt_T_u16 = (uint16)DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16];

                CmdResp_Cnt_T_u08 = CM_Polarity_SCom_SetPolarity(Diagtemp_Cnt_T_u16);
            }
            else
            {
                /* Read Service */
                CM_Polarity_SCom_ReadPolarity(&Diagtemp_Cnt_T_u16);
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = (uint8)(Diagtemp_Cnt_T_u16 & D_LOWERSIXBITSMASK_CNT_U16);
                ReturnDataIdx_Cnt_T_u16++;

                *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
            }
        #endif /* D_FD07_USE8BITPOLARITY_CNT_LGC */

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFD07_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FD08
 *
 *    PID ID:          0xFD08
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB),
 *                     Vehicle Speed Too High (0x88)
 *
 *    Description:     End of Line Torque Sensor Scaling - Analog
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFD08_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD08 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(CM_HwTrqScale_Datatype, EPSDIAGSRVC_VAR) HwTrqScaleData;
        VAR(EPS_DiagSrv_DataStr, EPSDIAGSRVC_VAR) TempData;

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
            TempData.type.IntData_u32 = uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_MSBYTESHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            TempData.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_WORDSHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            TempData.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_BYTESHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            TempData.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_ZERO_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;

            /* NOTE: Scale Status flag is passed via the tester but not used in Scom function, and therefore is ignored */
            CmdResp_Cnt_T_u08 = CM_HwTrq_SCom_SetHwTrqScale(TempData.type.FloatData_f32);
        }
        else
        {
            /* Read Service */
            CM_HwTrq_SCom_ReadHwTrqScale(&HwTrqScaleData);

            /* Torque Scale */
            TempData.type.FloatData_f32 = HwTrqScaleData.HwTrqScale_VoltsPerDeg_f32;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_MSBYTESHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_WORDSHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_BYTESHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_ZERO_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;

            /* Torque Scale Status */
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = HwTrqScaleData.HwTrqScalePerf_Cnt_lgc;
            ReturnDataIdx_Cnt_T_u16++;

            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFD08_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FD09
 *
 *    PID ID:          0xFD09
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB),
 *                     Vehicle Speed Too High (0x88),
 *                     Handwheel Torque Too High (0xFE)
 *
 *    Description:     Learned Ke
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFD09_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD09 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(EPS_DiagSrv_DataStr, EPSDIAGSRVC_VAR) LearnedKe_VoltRadpSec_T_f32;

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
            LearnedKe_VoltRadpSec_T_f32.type.IntData_u32 = uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_MSBYTESHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            LearnedKe_VoltRadpSec_T_f32.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_WORDSHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            LearnedKe_VoltRadpSec_T_f32.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_BYTESHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            LearnedKe_VoltRadpSec_T_f32.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_ZERO_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;

            CM_SCom_KeIntgSVParam_Set(LearnedKe_VoltRadpSec_T_f32.type.FloatData_f32);
    }
        else
        {
            /* Read Service */
            CM_SCom_KeIntgSVParam_Get(&LearnedKe_VoltRadpSec_T_f32.type.FloatData_f32);
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(LearnedKe_VoltRadpSec_T_f32.type.IntData_u32, D_MSBYTESHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(LearnedKe_VoltRadpSec_T_f32.type.IntData_u32, D_WORDSHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(LearnedKe_VoltRadpSec_T_f32.type.IntData_u32, D_BYTESHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(LearnedKe_VoltRadpSec_T_f32.type.IntData_u32, D_ZERO_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;

            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFD09_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FD0A
 *
 *    PID ID:          0xFD0A
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB),
 *                     Vehicle Speed Too High (0x88),
 *                     Handwheel Torque Too High (0xFE)
 *
 *    Description:     Learned R
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFD0A_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD0A (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(EPS_DiagSrv_DataStr, EPSDIAGSRVC_VAR) LearnedR_Ohm_T_f32;

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
            LearnedR_Ohm_T_f32.type.IntData_u32 = uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_MSBYTESHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            LearnedR_Ohm_T_f32.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_WORDSHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            LearnedR_Ohm_T_f32.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_BYTESHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            LearnedR_Ohm_T_f32.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_ZERO_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;

            CM_SCom_RIntgSVParam_Set(LearnedR_Ohm_T_f32.type.FloatData_f32);
        }
        else
        {
            /* Read Service */
            CM_SCom_RIntgSVParam_Get(&LearnedR_Ohm_T_f32.type.FloatData_f32);
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(LearnedR_Ohm_T_f32.type.IntData_u32, D_MSBYTESHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(LearnedR_Ohm_T_f32.type.IntData_u32, D_WORDSHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(LearnedR_Ohm_T_f32.type.IntData_u32, D_BYTESHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(LearnedR_Ohm_T_f32.type.IntData_u32, D_ZERO_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;

            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFD0A_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FD0B
 *
 *    PID ID:          0xFD0B
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB)
 *
 *    Description:     EOL Wheel Imbalance Select
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFD0B_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD0B (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
            CM_WIRSel_Cnt_u16 = bytesToWord_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16 + 1u)]);

            (void)NvM_WriteBlock(NVM_BLOCK_NXTRWIRSELECT, NULL_PTR);
        }
        else
        {
            /* Read Service */
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(CM_WIRSel_Cnt_u16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(CM_WIRSel_Cnt_u16);
            ReturnDataIdx_Cnt_T_u16++;

            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFD0B_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FD0C
 *
 *    PID ID:          0xFD0C
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB)
 *
 *    Description:     End of Line Ke, R and L Motor Parameters
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFD0C_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD0C (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(uint16, EPSDIAGSRVC_VAR) Diagtemp_Cnt_T_u16;
        VAR(float32, EPSDIAGSRVC_VAR) Diagtemp_Cnt_T_f32;
        VAR(float32, EPSDIAGSRVC_VAR) Diagtemp2_Cnt_T_f32;
        VAR(float32, EPSDIAGSRVC_VAR) Diagtemp3_Cnt_T_f32;

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
            /* NomKe_VpRadpS_T_f32 */
            Diagtemp_Cnt_T_f32 = FPM_FixedToFloat_m(bytesToWord_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16+1u)]), um1p17_T);

            /* NomRmtr_Ohm_T_f32 */
            Diagtemp2_Cnt_T_f32 = FPM_FixedToFloat_m(bytesToWord_m(DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16+2u)], DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16+3u)]), um1p17_T);

            /* NomL_Henry_f32 */
            Diagtemp3_Cnt_T_f32 = FPM_FixedToFloat_m(bytesToWord_m(DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16+4u)], DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16+5u)]), um10p26_T);

            #ifdef D_PIDFD0CIGNORELPARAM_CNT_LGC
                CM_SCom_EOLNomMtrParam_Set(Diagtemp_Cnt_T_f32, Diagtemp2_Cnt_T_f32);
            #else
                CM_SCom_EOLNomMtrParam_Set(Diagtemp_Cnt_T_f32, Diagtemp3_Cnt_T_f32, Diagtemp2_Cnt_T_f32);
            #endif
        }
        else
        {
            /* Read Service */
            #ifdef D_PIDFD0CIGNORELPARAM_CNT_LGC
                CM_SCom_EOLNomMtrParam_Get(&Diagtemp_Cnt_T_f32, &Diagtemp2_Cnt_T_f32);
                Diagtemp3_Cnt_T_f32 = 0.0F;
            #else
                CM_SCom_EOLNomMtrParam_Get(&Diagtemp_Cnt_T_f32, &Diagtemp3_Cnt_T_f32, &Diagtemp2_Cnt_T_f32);
            #endif

            /* NomKe_VpRadpS_T_f32 */
            Diagtemp_Cnt_T_u16 = FPM_FloatToFixed_m(Diagtemp_Cnt_T_f32, um1p17_T);
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(Diagtemp_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(Diagtemp_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;

            /* NomRmtr_Ohm_T_f32 */
            Diagtemp_Cnt_T_u16 = FPM_FloatToFixed_m(Diagtemp2_Cnt_T_f32, um1p17_T);
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(Diagtemp_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(Diagtemp_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;

            /* NomL_Henry_f32 */
            Diagtemp_Cnt_T_u16 = FPM_FloatToFixed_m(Diagtemp3_Cnt_T_f32, um10p26_T);
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(Diagtemp_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(Diagtemp_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;

            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFD0C_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_IOC_FD0D
 *
 *    IOC ID:          0xFD0D
 *
 *    Configured NRCs: Vehicle Speed Too High (0x88)
 *
 *    Description:     I/O Control: Motor Torque Command
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVIOCFD0D_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_IOC_FD0D (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(uint16, EPSDIAGSRVC_VAR) MtrTrqCmd_MtrNm_T_u16;
        VAR(float32, EPSDIAGSRVC_VAR) MtrTrqCmd_MtrNm_T_f32 = 0.0F;

        /* Check NRC 0x22 - MEC == 0 */
        if((NxtrMEC_Uls_G_enum != ProductionMode))
        {
            switch(SubFunc_Cnt_T_u08)
            {
                case D_EPSIOCSHRTTRMADJ_CNT_U08:
                    MtrTrqCmd_MtrNm_T_u16 = bytesToWord_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16 + 1u)]);
                    MtrTrqCmd_MtrNm_T_f32 = FPM_FixedToFloat_m((sint16)MtrTrqCmd_MtrNm_T_u16, s4p11_T);

                    CM_MtrTrqLmt_SCom_ManualTrqCmd(TRUE, MtrTrqCmd_MtrNm_T_f32);    /* Set Trq Cmd */
                break;
                case D_EPSIOCRETURNCTRL_CNT_U08:
                    CM_MtrTrqLmt_SCom_ManualTrqCmd(FALSE, MtrTrqCmd_MtrNm_T_f32); /* Return Ctrl to ECU */
                break;
                default:
                    /* Request Out of Range */
                    CmdResp_Cnt_T_u08 = D_EPSNRCREQOUTOFRANGE_CNT_U08;
                break;
            }
        }
        else
        {
            /* Returns 0x22: "Conditions not correct", not FB: "MEC equals Zero" -  As per CM Spec v02a */
            CmdResp_Cnt_T_u08 = D_EPSNRCCONDNOTCORRECT_CNT_U08;
        }

        *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVIOCFD0D_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FD0E
 *
 *    PID ID:          0xFD0E
 *
 *    Configured NRCs: N/A
 *
 *    Description:     Motor Stiffness Check
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFD0E_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD0E (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(EPS_DiagSrv_DataStr, EPSDIAGSRVC_VAR) CumMtrPos;
        VAR(EPS_DiagSrv_DataStr, EPSDIAGSRVC_VAR) MtrTrqCmd;

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
            /* No Write Function */
            CmdResp_Cnt_T_u08 = D_EPSNRCREQOUTOFRANGE_CNT_U08;
        }
        else
        {
            /* Read Service */
            SuspendAllInterrupts();
            CumMtrPos.type.FloatData_f32 = CM_CumMtrPos_Deg_f32;
            MtrTrqCmd.type.FloatData_f32 = CM_MtrTrqCmd_MtrNm_f32;
            ResumeAllInterrupts();

            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(CumMtrPos.type.IntData_u32, D_MSBYTESHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(CumMtrPos.type.IntData_u32, D_WORDSHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(CumMtrPos.type.IntData_u32, D_BYTESHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(CumMtrPos.type.IntData_u32, D_ZERO_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;

            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(MtrTrqCmd.type.IntData_u32, D_MSBYTESHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(MtrTrqCmd.type.IntData_u32, D_WORDSHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(MtrTrqCmd.type.IntData_u32, D_BYTESHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(MtrTrqCmd.type.IntData_u32, D_ZERO_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;

            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFD0E_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FD0F
 *
 *    PID ID:          0xFD0F
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB)
 *
 *    Description:     ECU Hardware Description Table
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFD0F_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD0F (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        CONSTP2VAR(uint8, EPSDIAGSRVC_VAR, EPSDIAGSRVC_CONST)Buffer_T_ptr = (uint8*)(void*)(&HwDescData); /* PRQA S 316,311 */
        VAR(uint16, EPSDIAGSRVC_VAR) Index_Cnt_T_u16;

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
            for (Index_Cnt_T_u16 = 0U; Index_Cnt_T_u16 < RequestLen_Cnt_T_u16; Index_Cnt_T_u16++)
            {
                Buffer_T_ptr[Index_Cnt_T_u16] = DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16]; /* PRQA S 0491 */
				/*
				* MISRA-C: 2004 Rule 17.4: These deviations are required for array subscripting applied to an object of pointer type
				*/

                RequestDataIdx_Cnt_T_u16++;
            }

            (void)NvM_WriteBlock(NVM_BLOCK_HWDESCDATA, NULL_PTR);
        }
        else
        {
            /* Read Service */
            for (Index_Cnt_T_u16 = 0U; Index_Cnt_T_u16 < D_HARDWAREDESCTBLPIDSIZE_CNT_U16; Index_Cnt_T_u16++)
            {
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = Buffer_T_ptr[Index_Cnt_T_u16]; /* PRQA S 0491 */
                /*
                * MISRA-C: 2004 Rule 17.4: These deviations are required for array subscripting applied to an object of pointer type
                */
                ReturnDataIdx_Cnt_T_u16++;
            }

            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFD0F_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FD10
 *
 *    PID ID:          0xFD10
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB)
 *
 *    Description:     Nexteer CCP/XCP Transmit and Receive IDs
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFD10_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD10 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(uint32, EPSDIAGSRVC_VAR) TempData_Cnt_T_u32 = 0U;

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
            CmdResp_Cnt_T_u08 = D_EPSNRCREQOUTOFRANGE_CNT_U08;
        }
        else
        {
            /* Read Service */
            /* XCP Master ID */
            TempData_Cnt_T_u32 = (uint32)D_XCP_MASTER_ID_ULS_U32;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData_Cnt_T_u32, D_MSBYTESHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData_Cnt_T_u32, D_WORDSHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData_Cnt_T_u32, D_BYTESHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData_Cnt_T_u32, D_ZERO_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;

            /* XCP Slave ID */
            TempData_Cnt_T_u32 = (uint32)D_XCP_SLAVE_ID_ULS_U32;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData_Cnt_T_u32, D_MSBYTESHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData_Cnt_T_u32, D_WORDSHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData_Cnt_T_u32, D_BYTESHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData_Cnt_T_u32, D_ZERO_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;

            /* Flexray only (default should be set to 0): Cycle Repetition */
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = (uint8)D_XCP_FLEXRAY_CYCLE_REP_ULS_U8;
            ReturnDataIdx_Cnt_T_u16++;

            /* Flexray only (default should be set to 0): Base Cycle */
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = (uint8)D_XCP_FLEXRAY_BASE_CYCLE_ULS_U8;
            ReturnDataIdx_Cnt_T_u16++;

            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFD10_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_IOC_FD11
 *
 *    IOC ID:          0xFD11
 *
 *    Configured NRCs: N/A
 *
 *    Description:     I/O Control: Control Assist Gain
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVIOCFD11_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_IOC_FD11 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(sint16, EPSDIAGSRVC_VAR) AssistGain_Uls_T_s16;

        switch(SubFunc_Cnt_T_u08)
        {
            case D_EPSIOCSHRTTRMADJ_CNT_U08:
                SuspendAllInterrupts();
                CM_DFTASSTTBL_CNT_LGC = TRUE;
                AssistGain_Uls_T_s16 = (sint16)bytesToWord_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16],  DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16 + 1u)]);
                CM_DWNLDASSTGAIN_ULS_F32 = FPM_FixedToFloat_m(AssistGain_Uls_T_s16, s4p11_T);
                ResumeAllInterrupts();
            break;
            case D_EPSIOCRETURNCTRL_CNT_U08:
                /* Enable Assist Table and Clear Gain */
                SuspendAllInterrupts();
                CM_DFTASSTTBL_CNT_LGC = FALSE;
                CM_DWNLDASSTGAIN_ULS_F32 = 1.0F;
                ResumeAllInterrupts();
            break;
            default:
                CmdResp_Cnt_T_u08 = D_EPSNRCREQOUTOFRANGE_CNT_U08;
            break;
        }

        *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVIOCFD11_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FD12
 *
 *    PID ID:          0xFD12
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB)
 *
 *    Description:     Current Mode Offset and Gain
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFD12_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD12 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(EPS_DiagSrv_DataStr, EPSDIAGSRVC_VAR) TempData;
        VAR(CM_PhaseCurrCal_DataType, EPSDIAGSRVC_VAR) CurrentModeMtrCals_Uls_T_str;

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
            TempData.type.IntData_u32 = uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_MSBYTESHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            TempData.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_WORDSHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            TempData.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_BYTESHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            TempData.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_ZERO_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;

            #ifdef D_PIDFD12IGNOREVCALCMD_CNT_LGC
                /* Not supported, data ignored */
            #else
                CurrentModeMtrCals_Uls_T_str.EOLMtrCurrVcalCmd_VoltCnts_f32 = TempData.type.FloatData_f32;
            #endif

            TempData.type.IntData_u32 = uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_MSBYTESHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            TempData.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_WORDSHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            TempData.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_BYTESHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            TempData.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_ZERO_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;

            #ifdef D_PIDFD1216BITDATASTRG_CNT_LGC
                CurrentModeMtrCals_Uls_T_str.EOLMtrCurr1Gain_AmpspVolt_u7p9 = FPM_FloatToFixed_m(TempData.type.FloatData_f32, u7p9_T);
            #else
                CurrentModeMtrCals_Uls_T_str.EOLPhscurr1Gain_AmpspVolt_f32 = TempData.type.FloatData_f32;
            #endif

            TempData.type.IntData_u32 = uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_MSBYTESHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            TempData.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_WORDSHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            TempData.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_BYTESHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            TempData.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_ZERO_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;

            #ifdef D_PIDFD1216BITDATASTRG_CNT_LGC
                CurrentModeMtrCals_Uls_T_str.EOLMtrCurr2Gain_AmpspVolt_u7p9 = FPM_FloatToFixed_m(TempData.type.FloatData_f32, u7p9_T);
            #else
                CurrentModeMtrCals_Uls_T_str.EOLPhscurr2Gain_AmpspVolt_f32 = TempData.type.FloatData_f32;
            #endif

            TempData.type.IntData_u32 = uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_MSBYTESHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            TempData.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_WORDSHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            TempData.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_BYTESHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            TempData.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_ZERO_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;

            #ifdef D_PIDFD1216BITDATASTRG_CNT_LGC
                CurrentModeMtrCals_Uls_T_str.EOLMtrCurr1Offset_Volts_u3p13 = FPM_FloatToFixed_m(TempData.type.FloatData_f32, u3p13_T);
            #else
                CurrentModeMtrCals_Uls_T_str.EOLMtrCurr1OffsetLo_Volts_f32 = TempData.type.FloatData_f32;
            #endif

            TempData.type.IntData_u32 = uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_MSBYTESHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            TempData.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_WORDSHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            TempData.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_BYTESHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            TempData.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_ZERO_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;

            #ifdef D_PIDFD1216BITDATASTRG_CNT_LGC
                CurrentModeMtrCals_Uls_T_str.EOLMtrCurr2Offset_Volts_u3p13 = FPM_FloatToFixed_m(TempData.type.FloatData_f32, u3p13_T);
            #else
                CurrentModeMtrCals_Uls_T_str.EOLMtrCurr2OffsetLo_Volts_f32 = TempData.type.FloatData_f32;
            #endif

            TempData.type.IntData_u32 = uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_MSBYTESHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            TempData.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_WORDSHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            TempData.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_BYTESHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            TempData.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_ZERO_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;

            #ifdef D_PIDFD12IGNOREOFFSETDIFF_CNT_LGC
                /* Not supported, data ignored */
            #else
                CurrentModeMtrCals_Uls_T_str.EOLMtrCurr1OffsetDiff_Volts_f32 = TempData.type.FloatData_f32;
            #endif

            TempData.type.IntData_u32 = uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_MSBYTESHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            TempData.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_WORDSHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            TempData.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_BYTESHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            TempData.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_ZERO_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;

            #ifdef D_PIDFD12IGNOREOFFSETDIFF_CNT_LGC
                /* Not supported, data ignored */
            #else
                CurrentModeMtrCals_Uls_T_str.EOLMtrCurr2OffsetDiff_Volts_f32 = TempData.type.FloatData_f32;
            #endif

            CM_CmMtrCurr_SCom_SetMtrCurrCals(&CurrentModeMtrCals_Uls_T_str);
        }
        else
        {
            /* Read Service */
            CM_CmMtrCurr_SCom_ReadMtrCurrCals(&CurrentModeMtrCals_Uls_T_str);

            #ifdef D_PIDFD12IGNOREVCALCMD_CNT_LGC
                TempData.type.FloatData_f32 = 0.0F;
            #else
                TempData.type.FloatData_f32 = *(float32 *)&CurrentModeMtrCals_Uls_T_str.EOLMtrCurrVcalCmd_VoltCnts_f32;
            #endif
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_MSBYTESHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_WORDSHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_BYTESHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_ZERO_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;

            #ifdef D_PIDFD1216BITDATASTRG_CNT_LGC
                TempData.type.FloatData_f32 = FPM_FixedToFloat_m((*(uint16 *)&CurrentModeMtrCals_Uls_T_str.EOLMtrCurr1Gain_AmpspVolt_u7p9), u7p9_T);
            #else
                TempData.type.FloatData_f32 = *(float32 *)&CurrentModeMtrCals_Uls_T_str.EOLPhscurr1Gain_AmpspVolt_f32;
            #endif
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_MSBYTESHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_WORDSHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_BYTESHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_ZERO_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;

            #ifdef D_PIDFD1216BITDATASTRG_CNT_LGC
                TempData.type.FloatData_f32 = FPM_FixedToFloat_m((*(uint16 *)&CurrentModeMtrCals_Uls_T_str.EOLMtrCurr2Gain_AmpspVolt_u7p9), u7p9_T);
            #else
                TempData.type.FloatData_f32 = *(float32 *)&CurrentModeMtrCals_Uls_T_str.EOLPhscurr2Gain_AmpspVolt_f32;
            #endif
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_MSBYTESHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_WORDSHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_BYTESHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_ZERO_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;

            #ifdef D_PIDFD1216BITDATASTRG_CNT_LGC
                TempData.type.FloatData_f32 = FPM_FixedToFloat_m((*(uint16 *)&CurrentModeMtrCals_Uls_T_str.EOLMtrCurr1Offset_Volts_u3p13), u3p13_T);
            #else
                TempData.type.FloatData_f32 = *(float32 *)&CurrentModeMtrCals_Uls_T_str.EOLMtrCurr1OffsetLo_Volts_f32;
            #endif
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_MSBYTESHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_WORDSHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_BYTESHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_ZERO_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;

            #ifdef D_PIDFD1216BITDATASTRG_CNT_LGC
                TempData.type.FloatData_f32 = FPM_FixedToFloat_m((*(uint16 *)&CurrentModeMtrCals_Uls_T_str.EOLMtrCurr2Offset_Volts_u3p13), u3p13_T);
            #else
                TempData.type.FloatData_f32 = *(float32 *)&CurrentModeMtrCals_Uls_T_str.EOLMtrCurr2OffsetLo_Volts_f32;
            #endif
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_MSBYTESHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_WORDSHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_BYTESHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_ZERO_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;

            #ifdef D_PIDFD12IGNOREOFFSETDIFF_CNT_LGC
                TempData.type.FloatData_f32 = 0.0F;
            #else
                TempData.type.FloatData_f32 = *(float32 *)&CurrentModeMtrCals_Uls_T_str.EOLMtrCurr1OffsetDiff_Volts_f32;
            #endif
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_MSBYTESHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_WORDSHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_BYTESHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_ZERO_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;

            #ifdef D_PIDFD12IGNOREOFFSETDIFF_CNT_LGC
                TempData.type.FloatData_f32 = 0.0F;
            #else
                TempData.type.FloatData_f32 = *(float32 *)&CurrentModeMtrCals_Uls_T_str.EOLMtrCurr2OffsetDiff_Volts_f32;
            #endif
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_MSBYTESHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_WORDSHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_BYTESHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_ZERO_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;

            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFD12_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FD13
 *
 *    PID ID:          0xFD13
 *
 *    Configured NRCs: N/A
 *
 *    Description:     Read Nexteer DTCs
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFD13_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD13 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(uint16, EPSDIAGSRVC_VAR) DTCIndex_Cnt_T_u16;
        VAR(uint8, EPSDIAGSRVC_VAR) NTCParam_Cnt_T_u8;
        VAR(uint8, EPSDIAGSRVC_VAR) Status_Ptr_T_u8;
        VAR(uint8, EPSDIAGSRVC_VAR) AgingCounter_Ptr_T_u8;

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
            /* Write not supported */
            CmdResp_Cnt_T_u08 = D_EPSNRCREQOUTOFRANGE_CNT_U08;
        }
        else
        {
            /* Read Service */
            CM_DiagMgr_SCom_ReadStrgArray();

            for(DTCIndex_Cnt_T_u16 = 0U; DTCIndex_Cnt_T_u16 < CM_DTCMaxStorage_Cnt_u16; DTCIndex_Cnt_T_u16++)
            {
                CM_DiagMgr_SCom_GetNTCInfo( NTCStrgArray_Cnt_str[DTCIndex_Cnt_T_u16].NTC,
                                            &NTCParam_Cnt_T_u8,
                                            &Status_Ptr_T_u8,
                                            &AgingCounter_Ptr_T_u8);

                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(NTCStrgArray_Cnt_str[DTCIndex_Cnt_T_u16].NTC);
                ReturnDataIdx_Cnt_T_u16++;
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(NTCStrgArray_Cnt_str[DTCIndex_Cnt_T_u16].NTC);
                ReturnDataIdx_Cnt_T_u16++;
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = NTCParam_Cnt_T_u8;
                ReturnDataIdx_Cnt_T_u16++;
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = Status_Ptr_T_u8;
                ReturnDataIdx_Cnt_T_u16++;
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = AgingCounter_Ptr_T_u8;
                ReturnDataIdx_Cnt_T_u16++;
            }

            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFD13_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FD14
 *
 *    PID ID:          0xFD14
 *
 *    Configured NRCs: N/A
 *
 *    Description:     Vehicle System State
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFD14_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD14 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(sint16, EPSDIAGSRVC_VAR) SrlComHwPos_HwDeg_T_s11p4;

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
            /* Write not supported */
            CmdResp_Cnt_T_u08 = D_EPSNRCREQOUTOFRANGE_CNT_U08;
        }
        else
        {
            /* Read Service */
            CM_AbsHwPos_SCom_VehicleSystemStatus(&SrlComHwPos_HwDeg_T_s11p4);
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = (uint8)MSB(SrlComHwPos_HwDeg_T_s11p4);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = (uint8)LSB(SrlComHwPos_HwDeg_T_s11p4);
            ReturnDataIdx_Cnt_T_u16++;
            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFD14_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FD15
 *
 *    PID ID:          0xFD15
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB)
 *
 *    Description:     End of Line Torque Sensor - Digital
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFD15_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD15 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(CM_HwTrqTrim_Datatype, EPSDIAGSRVC_VAR) HwTrqTrimInfo_T_str;
        VAR(EPS_DiagSrv_DataStr, EPSDIAGSRVC_VAR) TempData;

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
            TempData.type.IntData_u32 = uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_MSBYTESHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            TempData.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_WORDSHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            TempData.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_BYTESHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            TempData.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_ZERO_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;

            HwTrqTrimInfo_T_str.HwTrqTrim_Volts_f32 = TempData.type.FloatData_f32;

            TempData.type.IntData_u32 = uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_MSBYTESHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            TempData.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_WORDSHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            TempData.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_BYTESHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            TempData.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_ZERO_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;

            HwTrqTrimInfo_T_str.T1Trim_Volts_f32 = TempData.type.FloatData_f32;

            TempData.type.IntData_u32 = uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_MSBYTESHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            TempData.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_WORDSHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            TempData.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_BYTESHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            TempData.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_ZERO_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;

            HwTrqTrimInfo_T_str.T2Trim_Volts_f32 = TempData.type.FloatData_f32;

            HwTrqTrimInfo_T_str.HwTrqTrimPerf_Cnt_lgc = (uint8)DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16];
            RequestDataIdx_Cnt_T_u16++;

            CmdResp_Cnt_T_u08 = CM_DigHwTrq_SCom_ManualSetHwTrqTrim(&HwTrqTrimInfo_T_str);
        }
        else
        {
            /* Read Service */
            CM_DigHwTrq_SCom_ReadHwTrqTrim(&HwTrqTrimInfo_T_str);

            TempData.type.FloatData_f32 = HwTrqTrimInfo_T_str.HwTrqTrim_Volts_f32;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_MSBYTESHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_WORDSHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_BYTESHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_ZERO_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;

            TempData.type.FloatData_f32 = HwTrqTrimInfo_T_str.T1Trim_Volts_f32;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_MSBYTESHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_WORDSHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_BYTESHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_ZERO_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;

            TempData.type.FloatData_f32 = HwTrqTrimInfo_T_str.T2Trim_Volts_f32;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_MSBYTESHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_WORDSHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_BYTESHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_ZERO_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;

            /* Torque Performed Status */
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = HwTrqTrimInfo_T_str.HwTrqTrimPerf_Cnt_lgc;
            ReturnDataIdx_Cnt_T_u16++;

            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFD15_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FD16
 *
 *    PID ID:          0xFD16
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB),
 *                     Vehicle Speed Too High (0x88)
 *
 *    Description:     End of Line Torque Sensor Scaling - Digital
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFD16_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD16 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(CM_HwTrqScale_Datatype, EPSDIAGSRVC_VAR) HwTrqScale_T_str;
        VAR(EPS_DiagSrv_DataStr, EPSDIAGSRVC_VAR) TempData;

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
            TempData.type.IntData_u32 = uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16],D_MSBYTESHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            TempData.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16],D_WORDSHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            TempData.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16],D_BYTESHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            TempData.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16],D_ZERO_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;

            /* NOTE: Scale Status flag is passed by the tester but not used in Scom function, and therefore is ignored */
            CmdResp_Cnt_T_u08 = CM_DigHwTrq_SCom_SetHwTrqScale(TempData.type.FloatData_f32);
        }
        else
        {
            /* Read Service */
            DigHwTrq_SCom_ReadHwTrqScale(&HwTrqScale_T_str);

            TempData.type.FloatData_f32 = HwTrqScale_T_str.HwTrqScale_VoltsPerDeg_f32;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_MSBYTESHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_WORDSHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_BYTESHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData.type.IntData_u32, D_ZERO_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;

            /* Torque Scale Status */
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = HwTrqScale_T_str.HwTrqScalePerf_Cnt_lgc;
            ReturnDataIdx_Cnt_T_u16++;

            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFD16_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FD17
 *
 *    PID ID:          0xFD17
 *
 *    Configured NRCs: N/A
 *
 *    Description:     Flash Memory Size
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFD17_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD17 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
            CmdResp_Cnt_T_u08 = D_EPSNRCREQOUTOFRANGE_CNT_U08;


        }
        else
        {
            /* Read Service */
			DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(tiOTP->PMS,D_BYTESHIFT_CNT_U16);
			ReturnDataIdx_Cnt_T_u16++;
			DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(tiOTP->PMS,D_ZERO_CNT_U16);
			ReturnDataIdx_Cnt_T_u16++;
            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFD17_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FD18
 *
 *    PID ID:          0xFD18
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB)
 *
 *    Description:     EOL Handwheel Position Sensor Select
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFD18_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD18 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
            /* TODO: Implement this function */
            CmdResp_Cnt_T_u08 = D_EPSNRCREQOUTOFRANGE_CNT_U08;
        }
        else
        {
            /* Read Service */
            CmdResp_Cnt_T_u08 = D_EPSNRCREQOUTOFRANGE_CNT_U08;
            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFD18_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FD19
 *
 *    PID ID:          0xFD19
 *
 *    Configured NRCs: N/A
 *
 *    Description:     Nexteer MEC
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFD19_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD19 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
            CM_NxtrMEC_Cnt_G_u8 = DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16];
            (void)NvM_WriteBlock(NVM_BLOCK_CMS_NXTRMEC, NULL_PTR);

            /* Update Enum value */
            switch(CM_NxtrMEC_Cnt_G_u8)
            {
                case D_NXTRMEC_ENGMODE_CNT_U8:
                    NxtrMEC_Uls_G_enum = EngineeringMode;
                break;
                case D_NXTRMEC_PRODMODE_CNT_U8:
                    NxtrMEC_Uls_G_enum = ProductionMode;
                break;
                default:
                    NxtrMEC_Uls_G_enum = ManufacturingMode;
                break;
            }
        }
        else
        {
            /* Read Service */
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = CM_NxtrMEC_Cnt_G_u8;
            ReturnDataIdx_Cnt_T_u16++;
            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFD19_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FD1A
 *
 *    PID ID:          0xFD1A
 *
 *    Configured NRCs: N/A
 *
 *    Description:     System State
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFD1A_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD1A (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(CM_Rte_ModeType_StaMd_Mode, EPSDIAGSRVC_VAR) SystemState_Uls_T_enum;

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
            /* Write not supported */
            CmdResp_Cnt_T_u08 = D_EPSNRCREQOUTOFRANGE_CNT_U08;
        }
        else
        {
            /* Read Service */
            SystemState_Uls_T_enum = CM_SystemState_Cnt_enum;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = (uint8)SystemState_Uls_T_enum;
            ReturnDataIdx_Cnt_T_u16++;
            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFD1A_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FD1B
 *
 *    PID ID:          0xFD1B
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB)
 *
 *    Description:     Manual Vehicle Speed Override
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFD1B_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD1B (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(float32, EPSDIAGSRVC_VAR) VehSpd_Kph_T_Cnt_f32;

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
            /* make sure bit 27 of FD02 is set */
            if(D_SVCDFTRXMSGS_CNT_B32 == (CM_SrlComSvcDft_Cnt_b32 & D_SVCDFTRXMSGS_CNT_B32))
            {
                /* Conditions passed */
                EpsDiagSrvc_VehSpdOverride_Kph_M_u16p0 = DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16];
                VehSpd_Kph_T_Cnt_f32 = FPM_FixedToFloat_m(EpsDiagSrvc_VehSpdOverride_Kph_M_u16p0, u16p0_T);

                CM_ManualVehSpd_SCom(VehSpd_Kph_T_Cnt_f32);
            }
            else
            {
                /* FD02 Bit 27: Serial Communications Input Disable not set */
                CmdResp_Cnt_T_u08 = D_EPSNRCCONDNOTCORRECT_CNT_U08;
            }
        }
        else
        {
            /* Read Service */
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = (uint8)Min_m(EpsDiagSrvc_VehSpdOverride_Kph_M_u16p0, D_LOWERBYTEMASK_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFD1B_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FD1C
 *
 *    PID ID:          0xFD1C
 *
 *    Configured NRCs: N/A
 *
 *    Description:     Manufacturing Services Version
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFD1C_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD1C (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(uint16, EPSDIAGSRVC_VAR) Index_Cnt_T_u16;
        VAR(uint16, EPSDIAGSRVC_VAR) ArraySize_Cnt_T_u16;
        ArraySize_Cnt_T_u16 = (sizeof(CM_ManufSpecVersion_ASCII_u08)/sizeof(uint8));

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
            /* Write Not Supported */
            CmdResp_Cnt_T_u08 = D_EPSNRCREQOUTOFRANGE_CNT_U08;
        }
        else
        {
            /* Read Service */
            for (Index_Cnt_T_u16 = 0U; Index_Cnt_T_u16 < ArraySize_Cnt_T_u16; Index_Cnt_T_u16++)
            {
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = CM_ManufSpecVersion_ASCII_u08[Index_Cnt_T_u16];
                ReturnDataIdx_Cnt_T_u16++;
            }
            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFD1C_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FD1D
 *
 *    PID ID:          0xFD1D
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB)
 *
 *    Description:     EOL Return Range
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFD1D_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD1D (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(float32, EPSDIAGSRVC_VAR) Diagtemp_Cnt_T_f32;
        VAR(sint16, EPSDIAGSRVC_VAR) Diagtemp_Cnt_T_s11p4;
        VAR(sint16, EPSDIAGSRVC_VAR) Diagtemp_Cnt_T_s16;
        VAR(float32, EPSDIAGSRVC_VAR) Diagtemp_Uls_T_f32;

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
            Diagtemp_Cnt_T_s16 = (sint16)(bytesToWord_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16+1U]));
            Diagtemp_Uls_T_f32 = FPM_FixedToFloat_m(Diagtemp_Cnt_T_s16, s11p4_T);
            CM_Return_SCom_SetEOLRtnRange(Diagtemp_Uls_T_f32);
        }
        else
        {
            /* Read Service */
            CM_Return_SCom_GetEOLRtnRange(&Diagtemp_Cnt_T_f32);
            Diagtemp_Cnt_T_s11p4 = FPM_FloatToFixed_m(Diagtemp_Cnt_T_f32, s11p4_T);
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(Diagtemp_Cnt_T_s11p4);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(Diagtemp_Cnt_T_s11p4);
            ReturnDataIdx_Cnt_T_u16++;
            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFD1D_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FD1E
 *
 *    PID ID:          0xFD1E
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB)
 *
 *    Description:     Torque Sensor Diagnostic Defeat
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFD1E_CNT_ENUM == D_DIAGSRVC_ENABLED)
	FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD1E (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
	{
		/* Local Vars */
		VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
		VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestDataIdx_Cnt_T_u16 = 0U;
		VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
		VAR(uint16, EPSDIAGSRVC_VAR) TempData_Cnt_T_u16;

		if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
		{
			/* Write Service */
			if (NxtrMEC_Uls_G_enum != EngineeringMode)
			{
				TempData_Cnt_T_u16 = bytesToWord_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16 +1u)]);
				CM_MfgDiagInhibit_Cnt_lgc = (uint8)((0xA55AU == TempData_Cnt_T_u16)?TRUE:FALSE);
			}
			else
			{
				/* Return NRC 0x22 when in Engineering Mode (MEC == 0xFF) */
				CmdResp_Cnt_T_u08 = D_EPSNRCCONDNOTCORRECT_CNT_U08;
			}
		}
		else
		{
			/* Read Service */
			TempData_Cnt_T_u16 = (TRUE == CM_MfgDiagInhibit_Cnt_lgc) ? 0xA55AU : 0x0000U;
			DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(TempData_Cnt_T_u16);
			ReturnDataIdx_Cnt_T_u16++;
			DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(TempData_Cnt_T_u16);
			ReturnDataIdx_Cnt_T_u16++;
			*RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
		}

		return CmdResp_Cnt_T_u08;
	}
#endif /* (D_EPSDIAGSRVPIDFD1E_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FD1F
 *
 *    PID ID:          0xFD1F
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB)
 *
 *    Description:     Serial Comm Handwheel Position Defeat
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFD1F_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD1F (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(boolean, EPSDIAGSRVC_VAR) HwPosDft_Cnt_T_lgc = FALSE;


        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
            HwPosDft_Cnt_T_lgc = DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16];
            switch (HwPosDft_Cnt_T_lgc)
            {
                case TRUE:
                case FALSE:
                    CM_AbsHwPosScom_Scom_HwPosSrvSetToZero(HwPosDft_Cnt_T_lgc);
                break;
                default:
                    /* Command outside the range of valid requests */
                    CmdResp_Cnt_T_u08 = D_EPSNRCREQOUTOFRANGE_CNT_U08;
                break;
            }
        }
        else
        {
            /* Read Service */
            CM_AbsHwPosScom_Scom_HwPosSrvRead(&HwPosDft_Cnt_T_lgc);
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = HwPosDft_Cnt_T_lgc;
            ReturnDataIdx_Cnt_T_u16++;
            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFD1F_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FD20
 *
 *    PID ID:          0xFD20
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB)
 *
 *    Description:     Read Transient Overvoltage Data
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFD20_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD20 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(uint16, EPSDIAGSRVC_VAR) OvervoltageCounter_Cnt_T_u16;
        VAR(float32, EPSDIAGSRVC_VAR) MaxBatteryVoltage_Volts_T_f32;
        VAR(uint8, EPSDIAGSRVC_VAR) MaxBatteryVoltage_Volts_T_u5p3;

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
            /* Write not supported */
            CmdResp_Cnt_T_u08 = D_EPSNRCREQOUTOFRANGE_CNT_U08;
        }
        else
        {
            /* Read Service */
            CM_BatteryVoltage_SCom_ReadTransOvData(&OvervoltageCounter_Cnt_T_u16, &MaxBatteryVoltage_Volts_T_f32);

            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(OvervoltageCounter_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(OvervoltageCounter_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;

            MaxBatteryVoltage_Volts_T_u5p3 = (uint8)FPM_FloatToFixed_m(MaxBatteryVoltage_Volts_T_f32, u13p3_T);
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MaxBatteryVoltage_Volts_T_u5p3;
            ReturnDataIdx_Cnt_T_u16++;

            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFD20_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FD21
 *
 *    PID ID:          0xFD21
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB)
 *
 *    Description:     Vehicle Tuning Select
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFD21_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD21 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(uint8, EPSDIAGSRVC_VAR) TuningSet_Cnt_T_u08;

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
        	TuningSet_Cnt_T_u08 = DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16];

           	if(TuningSet_Cnt_T_u08 <= D_TUNINGSETMAXLIM_CNT_U08)
           	{
           		CmdResp_Cnt_T_u08 = CM_VehicleTune_SCom_SetSelect(TuningSet_Cnt_T_u08);
           	}
           	else
           	{
           	  /* Request data out of range */
           		CmdResp_Cnt_T_u08 = D_EPSNRCREQOUTOFRANGE_CNT_U08;
           	}


        }
        else
        {
            /* Read Service */
        	CM_VehicleTune_SCom_GetSelect(&TuningSet_Cnt_T_u08);
        	DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = TuningSet_Cnt_T_u08;
        	ReturnDataIdx_Cnt_T_u16++;

        	*RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFD21_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FD22
 *
 *    PID ID:          0xFD22
 *
 *    Configured NRCs: N/A
 *
 *    Description:     Turns Counter Software Identifiers
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFD22_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD22 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(CM_TcPartNumType, EPSDIAGSRVC_VAR) TcPrgState;
        VAR(uint8, EPSDIAGSRVC_VAR) i;

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
            /* Write not supported */
            CmdResp_Cnt_T_u08 = D_EPSNRCREQOUTOFRANGE_CNT_U08;
        }
        else
        {
            /* Read Service */
            CM_TurnsCounter_Scom_PartNumSvc(&TcPrgState);

            for (i = 0U; i < D_PIDFD22STRLEN_CNT_U08; i++)
            {
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = TcPrgState[i];
                ReturnDataIdx_Cnt_T_u16++;
            }

            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFD22_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FD23
 *
 *    PID ID:          0xFD23
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB)
 *
 *    Description:     Turns Counter Energy Mode
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFD23_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD23 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
            (void)CM_Vsm_Scom_SetOperatingMode((CM_Vsm_OperatingModeType)DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16]);
        }
        else
        {
            /* Read Service */
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = (uint8)CM_Rte_VehCfg_EnergyModeState_Cnt_enum;
            ReturnDataIdx_Cnt_T_u16++;

            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFD23_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FD24
 *
 *    PID ID:          0xFD24
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB)
 *
 *    Description:     Turns Counter EOL Calibrations
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFD24_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD24 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(CM_EOLTurnsCntrCals_Datatype, EPSDIAGSRVC) TcEolCals_Uls_T_Str;

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
            CmdResp_Cnt_T_u08 = CM_TcEOLCals_Scom_SetTcEOLCals(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16],
                                                               DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16 + 1U],
                                                               DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16 + 2U],
                                                               DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16 + 3U],
                                                               DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16 + 4U],
                                                               DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16 + 5U]);
        }
        else
        {
            /* Read Service */
            CM_TcEOLCals_Scom_ReadTcEOLCals(&TcEolCals_Uls_T_Str);

            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = TcEolCals_Uls_T_Str.TcEolSineOffset_Cnt_u08;
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = TcEolCals_Uls_T_Str.TcEolCosineOffset_Cnt_u08;
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = TcEolCals_Uls_T_Str.TcEolSin2CosGain_Cnt_u08;
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = TcEolCals_Uls_T_Str.TcEolSinVsCosMin_Cnt_u08;
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = TcEolCals_Uls_T_Str.TcEolSinVsCosMax_Cnt_u08;
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = TcEolCals_Uls_T_Str.TcEolCalChksm_Cnt_u08;
            ReturnDataIdx_Cnt_T_u16++;

            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFD24_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FD25
 *
 *    PID ID:          0xFD25
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB)
 *
 *    Description:     Motor Torque Scale Factor
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFD25_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD25 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(float32, EPSDIAGSRVC_VAR) Diagtemp_Cnt_T_f32;
        VAR(uint16, EPSDIAGSRVC_VAR) Diagtemp_Cnt_T_u16;

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
            Diagtemp_Cnt_T_u16 = bytesToWord_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16+1U)]);
            Diagtemp_Cnt_T_f32 = FPM_FixedToFloat_m(Diagtemp_Cnt_T_u16, u7p9_T);

            CM_TrqCmdScl_SCom_Set(Diagtemp_Cnt_T_f32);
        }
        else
        {
            /* Read Service */
            CM_TrqCmdScl_SCom_Get(&Diagtemp_Cnt_T_f32);

            Diagtemp_Cnt_T_u16 = FPM_FloatToFixed_m(Diagtemp_Cnt_T_f32, u7p9_T);
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(Diagtemp_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(Diagtemp_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;
            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFD25_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FD26
 *
 *    PID ID:          0xFD26
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB)
 *
 *    Description:     Average Friction Learning Select
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFD26_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD26 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(boolean, AUTOMATIC) EnableFricLearning_Cnt_T_lgc;
        VAR(boolean, AUTOMATIC) EnableOffsetOutput_Cnt_T_lgc;
        VAR(uint8, AUTOMATIC)   OpMode_Uls_T_u08;
        VAR(CM_Rte_ModeType_StaMd_Mode, EPSDIAGSRVC_VAR) SystemState_Uls_T_enum;

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
            /* Get System State */
            SystemState_Uls_T_enum = CM_SystemState_Cnt_enum;

            if (SystemState_Uls_T_enum == CM_RTE_MODE_StaMd_Mode_OPERATE)
            {
                EnableFricLearning_Cnt_T_lgc = DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16];
                EnableOffsetOutput_Cnt_T_lgc = DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16 + 1U];
                OpMode_Uls_T_u08             = DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16 + 2U];

                if ( (EnableFricLearning_Cnt_T_lgc <= 1U) &&
                     (EnableOffsetOutput_Cnt_T_lgc <= 1U) &&
                     (OpMode_Uls_T_u08 <= 4U) )
                {
                    CM_AvgFricLrn_SCom_SetSelect(EnableFricLearning_Cnt_T_lgc, EnableOffsetOutput_Cnt_T_lgc, OpMode_Uls_T_u08);
                }
                else
                {
                    /* Request data out of range */
                    CmdResp_Cnt_T_u08 = D_EPSNRCREQOUTOFRANGE_CNT_U08;
                }
            }
            else
            {
                /* System not in RUN mode */
                CmdResp_Cnt_T_u08 = D_EPSNRCCONDNOTCORRECT_CNT_U08;
            }
        }
        else
        {
            /* Read Service */
            CM_AvgFricLrn_SCom_GetSelect(&EnableFricLearning_Cnt_T_lgc, &EnableOffsetOutput_Cnt_T_lgc, &OpMode_Uls_T_u08);
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = EnableFricLearning_Cnt_T_lgc;
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = EnableOffsetOutput_Cnt_T_lgc;
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = OpMode_Uls_T_u08;
            ReturnDataIdx_Cnt_T_u16++;

            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFD26_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FD27
 *
 *    PID ID:          0xFD27
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB)
 *
 *    Description:     Friction Offset Output Defeat
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFD27_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD27 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(boolean, AUTOMATIC) DefeatFricitionLearning_Cnt_T_lgc;

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
            DefeatFricitionLearning_Cnt_T_lgc = DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16];

            if (DefeatFricitionLearning_Cnt_T_lgc <= 1U)
            {
                CM_AvgFricLrn_SCom_SetOffsetOutputDefeat(DefeatFricitionLearning_Cnt_T_lgc);
            }
            else
            {
                /* Request data out of range */
                CmdResp_Cnt_T_u08 = D_EPSNRCREQOUTOFRANGE_CNT_U08;
            }
        }
        else
        {
            /* Read Service */
            CM_AvgFricLrn_SCom_GetOffsetOutputDefeat(&DefeatFricitionLearning_Cnt_T_lgc);
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = DefeatFricitionLearning_Cnt_T_lgc;
            ReturnDataIdx_Cnt_T_u16++;

            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFD27_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FD28
 *
 *    PID ID:          0xFD28
 *
 *    Configured NRCs: N/A
 *
 *    Description:     Turns Counter Flash Traceability ID
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFD28_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD28 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;

		VAR(CM_TcFlshTraceabilityType, AUTOMATIC) TcFlshTrceabilityData_Uls_T_str;

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */

            /*Write Not Supported */
            CmdResp_Cnt_T_u08 = D_EPSNRCREQOUTOFRANGE_CNT_U08;
        }
        else
        {
            /* Read Service */

			CM_TcFlshPrg_Scom_TcFlashTraceability(&TcFlshTrceabilityData_Uls_T_str);

			DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TcFlshTrceabilityData_Uls_T_str.ExpectedTcPn_Cnt_u32, D_MSBYTESHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TcFlshTrceabilityData_Uls_T_str.ExpectedTcPn_Cnt_u32, D_WORDSHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TcFlshTrceabilityData_Uls_T_str.ExpectedTcPn_Cnt_u32, D_BYTESHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;

            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TcFlshTrceabilityData_Uls_T_str.TcFlashNvm_Uls_str.LastVldTcPnFlashed_Cnt_u32, D_MSBYTESHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TcFlshTrceabilityData_Uls_T_str.TcFlashNvm_Uls_str.LastVldTcPnFlashed_Cnt_u32, D_WORDSHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TcFlshTrceabilityData_Uls_T_str.TcFlashNvm_Uls_str.LastVldTcPnFlashed_Cnt_u32, D_BYTESHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;

			DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(TcFlshTrceabilityData_Uls_T_str.TcFlashNvm_Uls_str.TcFlashComplete_Cnt_u16);
			ReturnDataIdx_Cnt_T_u16++;
			DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(TcFlshTrceabilityData_Uls_T_str.TcFlashNvm_Uls_str.TcFlashComplete_Cnt_u16);
			ReturnDataIdx_Cnt_T_u16++;

			DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(TcFlshTrceabilityData_Uls_T_str.TcFlashNvm_Uls_str.TcFlashCounter_Cnt_u16);
			ReturnDataIdx_Cnt_T_u16++;
			DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(TcFlshTrceabilityData_Uls_T_str.TcFlashNvm_Uls_str.TcFlashCounter_Cnt_u16);
			ReturnDataIdx_Cnt_T_u16++;

			DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(TcFlshTrceabilityData_Uls_T_str.TcFlashNvm_Uls_str.TcFlashIgnCnt_Cnt_u16);
			ReturnDataIdx_Cnt_T_u16++;
			DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(TcFlshTrceabilityData_Uls_T_str.TcFlashNvm_Uls_str.TcFlashIgnCnt_Cnt_u16);
			ReturnDataIdx_Cnt_T_u16++;

			DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = TcFlshTrceabilityData_Uls_T_str.TcFlashStatus_Cnt_u08;
			ReturnDataIdx_Cnt_T_u16++;

            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFD28_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FD29
 *
 *    PID ID:          0xFD29
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB)
 *
 *    Description:     Set EOL Friction Learned
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFD29_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD29 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(uint16, AUTOMATIC)  EOLFric_HwNm_T_u16;
        VAR(float32, AUTOMATIC) EOLFric_HwNm_T_f32;

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
            EOLFric_HwNm_T_u16 = bytesToWord_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16+1u)]);

            /* Data input range check */
            if (EOLFric_HwNm_T_u16 <= 32512U)
            {
                EOLFric_HwNm_T_f32 = FPM_FixedToFloat_m(EOLFric_HwNm_T_u16, u8p8_T);
                CM_AvgFricLrn_SCom_SetEOLFric(EOLFric_HwNm_T_f32);
            }
            else
            {
                /* Request data out of range */
                CmdResp_Cnt_T_u08 = D_EPSNRCREQUESTDATAOUTOFRANGE_CNT_U08;
            }
        }
        else
        {
            /* Read Service */
            CM_AvgFricLrn_SCom_GetEOLFric(&EOLFric_HwNm_T_f32);
            EOLFric_HwNm_T_u16 = FPM_FloatToFixed_m(EOLFric_HwNm_T_f32, u8p8_T);
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(EOLFric_HwNm_T_u16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(EOLFric_HwNm_T_u16);
            ReturnDataIdx_Cnt_T_u16++;

            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFD29_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FD30
 *
 *    PID ID:          0xFD30
 *
 *    Configured NRCs: N/A
 *
 *    Description:     End of Line Torque Trim Value - Digital SENT
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFD30_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD30 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
		VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(EPS_DiagSrv_DataStr, AUTOMATIC) TempData_Cnt_T_str;
		VAR(boolean, AUTOMATIC) TrimPerformed_Cnt_T_lgc;
		VAR(EPS_DiagSrv_DataStr, EPSDIAGSRVC_VAR) TempDataWrite_Cnt_T_str;

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
            TempDataWrite_Cnt_T_str.type.IntData_u32 = uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16],D_MSBYTESHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            TempDataWrite_Cnt_T_str.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16],D_WORDSHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            TempDataWrite_Cnt_T_str.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16],D_BYTESHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            TempDataWrite_Cnt_T_str.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16],D_ZERO_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;

			TrimPerformed_Cnt_T_lgc = DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16];

			/* Data Input Value Check */
			if (TrimPerformed_Cnt_T_lgc == TRUE)
			{
				/* Write Service */
            	CM_DigHwTrqSENT_SCom_WriteTrim(TempDataWrite_Cnt_T_str.type.FloatData_f32);
			}
			else
			{
				/* Request data out of range */
				CmdResp_Cnt_T_u08 = D_EPSNRCREQOUTOFRANGE_CNT_U08;
			}
        }
        else
        {
            /* Read Service */
            CM_DigHwTrqSENT_SCom_ReadTrim(&TempData_Cnt_T_str.type.FloatData_f32, &TrimPerformed_Cnt_T_lgc);

            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData_Cnt_T_str.type.IntData_u32, D_MSBYTESHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData_Cnt_T_str.type.IntData_u32, D_WORDSHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData_Cnt_T_str.type.IntData_u32, D_BYTESHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData_Cnt_T_str.type.IntData_u32, D_ZERO_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;

            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = (uint8)TrimPerformed_Cnt_T_lgc;
            ReturnDataIdx_Cnt_T_u16++;

            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFD30_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FD31
 *
 *    PID ID:          0xFD31
 *
 *    Configured NRCs: N/A
 *
 *    Description:     Torque Sensor Value - Digital SENT
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFD31_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD31 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(EPS_DiagSrv_DataStr, EPSDIAGSRVC_VAR) TempData_Cnt_T_str;

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
            /* Write not supported */
            CmdResp_Cnt_T_u08 = D_EPSNRCREQOUTOFRANGE_CNT_U08;
        }
        else
        {
            /* Read Service */
            /* Handwheel Torque */
            TempData_Cnt_T_str.type.FloatData_f32 = CM_Rte_Sa_DigHwTrqSENT_HwTorque_HwNm_f32;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData_Cnt_T_str.type.IntData_u32, D_MSBYTESHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData_Cnt_T_str.type.IntData_u32, D_WORDSHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData_Cnt_T_str.type.IntData_u32, D_BYTESHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData_Cnt_T_str.type.IntData_u32, D_ZERO_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;

            /* T1 */
            TempData_Cnt_T_str.type.FloatData_f32 = CM_Rte_Cd_Nhet1_DigHwTrqT1_HwNm_f32;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData_Cnt_T_str.type.IntData_u32, D_MSBYTESHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData_Cnt_T_str.type.IntData_u32, D_WORDSHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData_Cnt_T_str.type.IntData_u32, D_BYTESHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData_Cnt_T_str.type.IntData_u32, D_ZERO_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;

            /* T2 */
            TempData_Cnt_T_str.type.FloatData_f32 = CM_Rte_Cd_Nhet1_DigHwTrqT2_HwNm_f32;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData_Cnt_T_str.type.IntData_u32, D_MSBYTESHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData_Cnt_T_str.type.IntData_u32, D_WORDSHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData_Cnt_T_str.type.IntData_u32, D_BYTESHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData_Cnt_T_str.type.IntData_u32, D_ZERO_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;

            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFD31_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FD41
 *
 *    PID ID:          0xFD41
 *
 *    Configured NRCs: N/A
 *
 *    Description:     Torque Sensor 1 and 2 Voltage
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFD41_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FD41 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(uint16, EPSDIAGSRVC_VAR) Diagtemp_Cnt_T_u16;

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
            /* Write not supported */
            CmdResp_Cnt_T_u08 = D_EPSNRCREQOUTOFRANGE_CNT_U08;
        }
        else
        {
            /* Read Service */
            Diagtemp_Cnt_T_u16 = FPM_FloatToFixed_m(CM_Rte_IoHwAbstractionUsr_T1ADC_Volt_f32, u6p10_T);
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(Diagtemp_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(Diagtemp_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;

            Diagtemp_Cnt_T_u16 = FPM_FloatToFixed_m(CM_Rte_IoHwAbstractionUsr_T2ADC_Volt_f32, u6p10_T);
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(Diagtemp_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(Diagtemp_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;

            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFD41_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FDA0
 *
 *    PID ID:          0xFDA0
 *
 *    Configured NRCs: N/A
 *
 *    Description:     Unused
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFDA0_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FDA0 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
            CmdResp_Cnt_T_u08 = D_EPSNRCREQOUTOFRANGE_CNT_U08;
        }
        else
        {
            /* Read Service */
            CmdResp_Cnt_T_u08 = D_EPSNRCREQOUTOFRANGE_CNT_U08;
            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFDA0_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FDA1
 *
 *    PID ID:          0xFDA1
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB)
 *
 *    Description:     ECU Serial Number
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFDA1_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FDA1 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(uint16, EPSDIAGSRVC_VAR) Index_Cnt_T_u16;
        VAR(uint16, EPSDIAGSRVC_VAR) ArraySize_Cnt_T_u16;

        ArraySize_Cnt_T_u16 = (sizeof(CM_ECUSerialNumber)/sizeof(uint8));

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
            for(RequestDataIdx_Cnt_T_u16 = 0U; RequestDataIdx_Cnt_T_u16 < ArraySize_Cnt_T_u16; RequestDataIdx_Cnt_T_u16++)
            {
                CM_ECUSerialNumber[RequestDataIdx_Cnt_T_u16] = DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16];
            }

            (void)NvM_WriteBlock(NVM_BLOCK_CMS_ECUSRLNUM, NULL_PTR);
        }
        else
        {
            /* Read Service */
            for(Index_Cnt_T_u16 = 0U; Index_Cnt_T_u16 < ArraySize_Cnt_T_u16; Index_Cnt_T_u16++)
            {
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = CM_ECUSerialNumber[Index_Cnt_T_u16];
                ReturnDataIdx_Cnt_T_u16++;
            }

            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFDA1_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FDA2
 *
 *    PID ID:          0xFDA2
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB)
 *
 *    Description:     EPS Serial Number
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFDA2_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FDA2 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(uint16, EPSDIAGSRVC_VAR) Index_Cnt_T_u16;
        VAR(uint16, EPSDIAGSRVC_VAR) ArraySize_Cnt_T_u16;

        ArraySize_Cnt_T_u16 = (sizeof(CM_EPSSerialNumber)/sizeof(uint8));

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
            for(RequestDataIdx_Cnt_T_u16 = 0U; RequestDataIdx_Cnt_T_u16 < ArraySize_Cnt_T_u16; RequestDataIdx_Cnt_T_u16++)
            {
                CM_EPSSerialNumber[RequestDataIdx_Cnt_T_u16] = DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16];
            }
            (void)NvM_WriteBlock(NVM_BLOCK_CMS_EPSSRLNUM, NULL_PTR);
        }
        else
        {
            /* Read Service */
            for(Index_Cnt_T_u16 = 0U; Index_Cnt_T_u16 < ArraySize_Cnt_T_u16; Index_Cnt_T_u16++)
            {
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = CM_EPSSerialNumber[Index_Cnt_T_u16];
                ReturnDataIdx_Cnt_T_u16++;
            }

            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFDA2_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FDA3
 *
 *    PID ID:          0xFDA3
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB)
 *
 *    Description:     ECU Hardware Part Number
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFDA3_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FDA3 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(uint16, EPSDIAGSRVC_VAR) Index_Cnt_T_u16;
        VAR(uint16, EPSDIAGSRVC_VAR) ArraySize_Cnt_T_u16;

        ArraySize_Cnt_T_u16 = (sizeof(CM_ECUHardwarePN)/sizeof(uint8));

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
            for(RequestDataIdx_Cnt_T_u16 = 0U; RequestDataIdx_Cnt_T_u16 < ArraySize_Cnt_T_u16; RequestDataIdx_Cnt_T_u16++)
            {
                CM_ECUHardwarePN[RequestDataIdx_Cnt_T_u16] = DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16];
            }

            (void)NvM_WriteBlock(NVM_BLOCK_CMS_ECUHWPN, NULL_PTR);
        }
        else
        {
            /* Read Service */
            for(Index_Cnt_T_u16 = 0U; Index_Cnt_T_u16 < ArraySize_Cnt_T_u16; Index_Cnt_T_u16++)
            {
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = CM_ECUHardwarePN[Index_Cnt_T_u16];
                ReturnDataIdx_Cnt_T_u16++;
            }
            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFDA3_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FDA4
 *
 *    PID ID:          0xFDA4
 *
 *    Configured NRCs: N/A
 *
 *    Description:     OBSOLETE: Ship State Part Number
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFDA4_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FDA4 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
            /* Write not supported */
            CmdResp_Cnt_T_u08 = D_EPSNRCREQOUTOFRANGE_CNT_U08;
        }
        else
        {
            /* Read Service */
            CmdResp_Cnt_T_u08 = D_EPSNRCREQOUTOFRANGE_CNT_U08;
            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFDA4_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FDA5
 *
 *    PID ID:          0xFDA5
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB)
 *
 *    Description:     Shunt Current Offset and Gain
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFDA5_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FDA5 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(CM_ShCurrCal_DataType, EPSDIAGSRVC_VAR) ShCurrCalPID;
        VAR(uint16, EPSDIAGSRVC_VAR) Diagtemp_Cnt_T_u16;

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
            ShCurrCalPID.EOLShcurrOffset_Volts_f32 = FPM_FixedToFloat_m(bytesToWord_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16+1u)]), u3p13_T);
            ShCurrCalPID.EOLShcurrGain_Uls_f32 = FPM_FixedToFloat_m(bytesToWord_m(DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16+2u)], DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16+3u)]), u1p15_T);

            CM_MtrCurr_SCom_SetMtrCurrCals(&ShCurrCalPID);
        }
        else
        {
            /* Read Service */
            CM_MtrCurr_SCom_ReadMtrCurrCals(&ShCurrCalPID);

            Diagtemp_Cnt_T_u16 = FPM_FloatToFixed_m(ShCurrCalPID.EOLShcurrOffset_Volts_f32, u3p13_T);
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(Diagtemp_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(Diagtemp_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;

            Diagtemp_Cnt_T_u16 = FPM_FloatToFixed_m(ShCurrCalPID.EOLShcurrGain_Uls_f32, u1p15_T);
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(Diagtemp_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(Diagtemp_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;
            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFDA5_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FDA7
 *
 *    PID ID:          0xFDA7
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB)
 *
 *    Description:     Non-Contacting Sensor Calibration Set 1
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFDA7_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FDA7 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(CM_HwPosRelCal_DataType, EPSDIAGSRVC_VAR) NcHwPosCalPID;
        VAR(uint16, EPSDIAGSRVC_VAR) Diagtemp_Cnt_T_u16;

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
            SuspendAllInterrupts();
            (void)CM_HwPosRel_SCom_ReadHwPosCals(&NcHwPosCalPID);
            ResumeAllInterrupts();

            /* Conditions passed */
            NcHwPosCalPID.DcShiftTbl_Cnt_u6p10[0] = bytesToWord_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16+1u)]);
            NcHwPosCalPID.DcShiftTbl_Cnt_u6p10[1] = bytesToWord_m(DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16+2u)], DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16+3u)]);


            NcHwPosCalPID.SinHarMagTbl_Cnt_u6p10[0] = bytesToWord_m(DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16+4u)], DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16+5u)]);
            NcHwPosCalPID.SinHarMagTbl_Cnt_u6p10[1] = bytesToWord_m(DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16+6u)], DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16+7u)]);
            NcHwPosCalPID.SinHarMagTbl_Cnt_u6p10[2] = bytesToWord_m(DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16+8u)], DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16+9u)]);

            NcHwPosCalPID.CosHarMagTbl_Cnt_u6p10[0] = bytesToWord_m(DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16+10u)], DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16+11u)]);
            NcHwPosCalPID.CosHarMagTbl_Cnt_u6p10[1] = bytesToWord_m(DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16+12u)], DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16+13u)]);
            NcHwPosCalPID.CosHarMagTbl_Cnt_u6p10[2] = bytesToWord_m(DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16+14u)], DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16+15u)]);


            NcHwPosCalPID.SinHarAngTbl_Cnt_s0p15[0] = (sint16)bytesToWord_m(DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16+16u)], DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16+17u)]);
            NcHwPosCalPID.SinHarAngTbl_Cnt_s0p15[1] = (sint16)bytesToWord_m(DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16+18u)], DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16+19u)]);
            NcHwPosCalPID.SinHarAngTbl_Cnt_s0p15[2] = (sint16)bytesToWord_m(DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16+20u)], DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16+21u)]);

            NcHwPosCalPID.CosHarAngTbl_Cnt_s0p15[0] = (sint16)bytesToWord_m(DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16+22u)], DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16+23u)]);
            NcHwPosCalPID.CosHarAngTbl_Cnt_s0p15[1] = (sint16)bytesToWord_m(DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16+24u)], DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16+25u)]);
            NcHwPosCalPID.CosHarAngTbl_Cnt_s0p15[2] = (sint16)bytesToWord_m(DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16+26u)], DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16+27u)]);


            NcHwPosCalPID.SinDeltaRel_Uls_s0p15 = (sint16)bytesToWord_m(DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16+28u)], DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16+29u)]);
            NcHwPosCalPID.InvCosDeltRel_Uls_s1p14 = (sint16)bytesToWord_m(DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16+30u)], DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16+31u)]);
            NcHwPosCalPID.RelPeakAdj_Uls_u1p15 = bytesToWord_m(DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16+32u)], DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16+33u)]);
            NcHwPosCalPID.EOLRelAbsAlign_HwDeg_s11p4 = (sint16)bytesToWord_m(DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16+34u)], DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16+35u)]);
            NcHwPosCalPID.EOLP1HarMag1_Volt_u6p10 = bytesToWord_m(DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16+36u)], DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16+37u)]);


            SuspendAllInterrupts();
            (void)CM_HwPosRel_SCom_SetHwPosCals(&NcHwPosCalPID);
            ResumeAllInterrupts();
        }
        else
        {
            /* Read Service */
            SuspendAllInterrupts();
            (void)CM_HwPosRel_SCom_ReadHwPosCals(&NcHwPosCalPID);
            ResumeAllInterrupts();

            Diagtemp_Cnt_T_u16 = (uint16)NcHwPosCalPID.DcShiftTbl_Cnt_u6p10[0];
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(Diagtemp_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(Diagtemp_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;

            Diagtemp_Cnt_T_u16 = (uint16)NcHwPosCalPID.DcShiftTbl_Cnt_u6p10[1];
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(Diagtemp_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(Diagtemp_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;

            Diagtemp_Cnt_T_u16 = (uint16)NcHwPosCalPID.SinHarMagTbl_Cnt_u6p10[0];
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(Diagtemp_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(Diagtemp_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;

            Diagtemp_Cnt_T_u16 = (uint16)NcHwPosCalPID.SinHarMagTbl_Cnt_u6p10[1];
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(Diagtemp_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(Diagtemp_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;

            Diagtemp_Cnt_T_u16 = (uint16)NcHwPosCalPID.SinHarMagTbl_Cnt_u6p10[2];
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(Diagtemp_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(Diagtemp_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;

            Diagtemp_Cnt_T_u16 = (uint16)NcHwPosCalPID.CosHarMagTbl_Cnt_u6p10[0];
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(Diagtemp_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(Diagtemp_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;

            Diagtemp_Cnt_T_u16 = (uint16)NcHwPosCalPID.CosHarMagTbl_Cnt_u6p10[1];
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(Diagtemp_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(Diagtemp_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;

            Diagtemp_Cnt_T_u16 = (uint16)NcHwPosCalPID.CosHarMagTbl_Cnt_u6p10[2];
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(Diagtemp_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(Diagtemp_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;

            Diagtemp_Cnt_T_u16 = (uint16)NcHwPosCalPID.SinHarAngTbl_Cnt_s0p15[0];
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(Diagtemp_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(Diagtemp_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;

            Diagtemp_Cnt_T_u16 = (uint16)NcHwPosCalPID.SinHarAngTbl_Cnt_s0p15[1];
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(Diagtemp_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(Diagtemp_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;

            Diagtemp_Cnt_T_u16 = (uint16)NcHwPosCalPID.SinHarAngTbl_Cnt_s0p15[2];
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(Diagtemp_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(Diagtemp_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;

            Diagtemp_Cnt_T_u16 = (uint16)NcHwPosCalPID.CosHarAngTbl_Cnt_s0p15[0];
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(Diagtemp_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(Diagtemp_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;

            Diagtemp_Cnt_T_u16 = (uint16)NcHwPosCalPID.CosHarAngTbl_Cnt_s0p15[1];
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(Diagtemp_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(Diagtemp_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;

            Diagtemp_Cnt_T_u16 = (uint16)NcHwPosCalPID.CosHarAngTbl_Cnt_s0p15[2];
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(Diagtemp_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(Diagtemp_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;

            Diagtemp_Cnt_T_u16 = (uint16)NcHwPosCalPID.SinDeltaRel_Uls_s0p15;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(Diagtemp_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(Diagtemp_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;

            Diagtemp_Cnt_T_u16 = (uint16)NcHwPosCalPID.InvCosDeltRel_Uls_s1p14;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(Diagtemp_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(Diagtemp_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;

            Diagtemp_Cnt_T_u16 = (uint16)NcHwPosCalPID.RelPeakAdj_Uls_u1p15;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(Diagtemp_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(Diagtemp_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;

            Diagtemp_Cnt_T_u16 = (uint16)NcHwPosCalPID.EOLRelAbsAlign_HwDeg_s11p4;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(Diagtemp_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(Diagtemp_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;

            Diagtemp_Cnt_T_u16 = (uint16)NcHwPosCalPID.EOLP1HarMag1_Volt_u6p10;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(Diagtemp_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(Diagtemp_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;

            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFDA7_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FDA8
 *
 *    PID ID:          0xFDA8
 *
 *    Configured NRCs: N/A
 *
 *    Description:     Non-Contacting Sensor Calibration Set 2
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFDA8_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FDA8 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
            /* Write not supported */
            CmdResp_Cnt_T_u08 = D_EPSNRCREQOUTOFRANGE_CNT_U08;
        }
        else
        {
            /* Read Service */
            CmdResp_Cnt_T_u08 = D_EPSNRCREQOUTOFRANGE_CNT_U08;
            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFDA8_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FDA9
 *
 *    PID ID:          0xFDA9
 *
 *    Configured NRCs: N/A
 *
 *    Description:     Non-Contacting Sensor Calibration Set 3
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFDA9_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FDA9 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
            /* Write not supported */
            CmdResp_Cnt_T_u08 = D_EPSNRCREQOUTOFRANGE_CNT_U08;
        }
        else
        {
            /* Read Service */
            CmdResp_Cnt_T_u08 = D_EPSNRCREQOUTOFRANGE_CNT_U08;
            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFDA9_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FDAC
 *
 *    PID ID:          0xFDAC
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB)
 *
 *    Description:     Nexteer Manufacturing Scratchpad
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFDAC_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FDAC (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(uint16, EPSDIAGSRVC_VAR) Index_Cnt_T_u16;
        VAR(uint16, EPSDIAGSRVC_VAR) ArraySize_Cnt_T_u16;

        ArraySize_Cnt_T_u16 = (sizeof(CM_MfgScratchPad_Cnt_G_u8)/sizeof(uint8));

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
            for(RequestDataIdx_Cnt_T_u16 = 0u; RequestDataIdx_Cnt_T_u16 < ArraySize_Cnt_T_u16; RequestDataIdx_Cnt_T_u16++)
            {
                CM_MfgScratchPad_Cnt_G_u8[RequestDataIdx_Cnt_T_u16] = DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16];
            }

            (void)NvM_WriteBlock(NVM_BLOCK_CMS_NXTRMANUFSCRATCHPAD, NULL_PTR);
        }
        else
        {
            /* Read Service */
            for(Index_Cnt_T_u16 = 0u; Index_Cnt_T_u16 < ArraySize_Cnt_T_u16; Index_Cnt_T_u16++)
            {
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = CM_MfgScratchPad_Cnt_G_u8[Index_Cnt_T_u16];
                ReturnDataIdx_Cnt_T_u16++;
            }
            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFDAC_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FDAD
 *
 *    PID ID:          0xFDAD
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB)
 *
 *    Description:     Active Pull Compensation
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFDAD_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FDAD (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;

        VAR(float32, EPSDIAGSRVC_VAR) PCST_HwNm_T_f32;
        VAR(float32, EPSDIAGSRVC_VAR) PCLT_HwNm_T_f32;
        VAR(float32, EPSDIAGSRVC_VAR) PC_MtrNm_T_f32;
        VAR(boolean, EPSDIAGSRVC_VAR) PCEnabled_Cnt_T_lgc;
        VAR(sint16, EPSDIAGSRVC_VAR) TempData_Cnt_T_s16;

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
            /* Write not supported */
            CmdResp_Cnt_T_u08 = D_EPSNRCREQOUTOFRANGE_CNT_U08;
        }
        else
        {
            /* Read Service */
            CM_ActivePull_SCom_ReadParam(&PC_MtrNm_T_f32, &PCST_HwNm_T_f32, &PCLT_HwNm_T_f32, &PCEnabled_Cnt_T_lgc);

            /* Active Pull Comp Val */
            TempData_Cnt_T_s16 = FPM_FloatToFixed_m(PC_MtrNm_T_f32, s8p7_T);
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(TempData_Cnt_T_s16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(TempData_Cnt_T_s16);
            ReturnDataIdx_Cnt_T_u16++;

            /* Short Term Comp Val*/
            TempData_Cnt_T_s16 = FPM_FloatToFixed_m(PCST_HwNm_T_f32, s10p5_T);
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(TempData_Cnt_T_s16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(TempData_Cnt_T_s16);
            ReturnDataIdx_Cnt_T_u16++;

            /* Long Term Comp Vale*/
            TempData_Cnt_T_s16 = FPM_FloatToFixed_m(PCLT_HwNm_T_f32, s10p5_T);
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(TempData_Cnt_T_s16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(TempData_Cnt_T_s16);
            ReturnDataIdx_Cnt_T_u16++;

            /* Pull Comp Enabled */
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = PCEnabled_Cnt_T_lgc;
            ReturnDataIdx_Cnt_T_u16++;

            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFDAD_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FDAE
 *
 *    PID ID:          0xFDAE
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB)
 *
 *    Description:     Ignition Counter
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFDAE_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FDAE (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
            Nvm_IgnCntr_Cnt_u16 = bytesToWord_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16],DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16+1u)]);
            (void)NvM_WriteBlock(NVM_BLOCK_CMS_IGNCNTR, NULL_PTR);
        }
        else
        {
            /* Read Service */
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(Nvm_IgnCntr_Cnt_u16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(Nvm_IgnCntr_Cnt_u16);
            ReturnDataIdx_Cnt_T_u16++;

            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFDAE_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FDAF
 *
 *    PID ID:          0xFDAF
 *
 *    Configured NRCs: N/A
 *
 *    Description:     NTC Snapshot Data
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFDAF_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FDAF (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(uint8, AUTOMATIC) i;

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
            /* Write not supported */
            CmdResp_Cnt_T_u08 = D_EPSNRCREQOUTOFRANGE_CNT_U08;
        }
        else
        {
            /* Read Service */
            for (i = 0U; i < TableSize_m(NTCBlackBoxData_Cnt_str); i++)
            {
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = NTCBlackBoxData_Cnt_str[i].NTC_Cnt_u08;
                ReturnDataIdx_Cnt_T_u16++;
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = NTCBlackBoxData_Cnt_str[i].Param_Cnt_u08;
                ReturnDataIdx_Cnt_T_u16++;
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = NTCBlackBoxData_Cnt_str[i].SystemState_Cnt_u08;
                ReturnDataIdx_Cnt_T_u16++;
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = NTCBlackBoxData_Cnt_str[i].VehSpd_Kph_u8p0;
                ReturnDataIdx_Cnt_T_u16++;
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(NTCBlackBoxData_Cnt_str[i].BlkBoxCfgData1, D_MSBYTESHIFT_CNT_U16);
                ReturnDataIdx_Cnt_T_u16++;
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(NTCBlackBoxData_Cnt_str[i].BlkBoxCfgData1, D_WORDSHIFT_CNT_U16);
                ReturnDataIdx_Cnt_T_u16++;
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(NTCBlackBoxData_Cnt_str[i].BlkBoxCfgData1, D_BYTESHIFT_CNT_U16);
                ReturnDataIdx_Cnt_T_u16++;
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(NTCBlackBoxData_Cnt_str[i].BlkBoxCfgData1, D_ZERO_CNT_U16);
                ReturnDataIdx_Cnt_T_u16++;
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(NTCBlackBoxData_Cnt_str[i].BlkBoxCfgData2, D_MSBYTESHIFT_CNT_U16);
                ReturnDataIdx_Cnt_T_u16++;
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(NTCBlackBoxData_Cnt_str[i].BlkBoxCfgData2, D_WORDSHIFT_CNT_U16);
                ReturnDataIdx_Cnt_T_u16++;
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(NTCBlackBoxData_Cnt_str[i].BlkBoxCfgData2, D_BYTESHIFT_CNT_U16);
                ReturnDataIdx_Cnt_T_u16++;
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(NTCBlackBoxData_Cnt_str[i].BlkBoxCfgData2, D_ZERO_CNT_U16);
                ReturnDataIdx_Cnt_T_u16++;
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(NTCBlackBoxData_Cnt_str[i].BlkBoxCfgData3, D_MSBYTESHIFT_CNT_U16);
                ReturnDataIdx_Cnt_T_u16++;
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(NTCBlackBoxData_Cnt_str[i].BlkBoxCfgData3, D_WORDSHIFT_CNT_U16);
                ReturnDataIdx_Cnt_T_u16++;
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(NTCBlackBoxData_Cnt_str[i].BlkBoxCfgData3, D_BYTESHIFT_CNT_U16);
                ReturnDataIdx_Cnt_T_u16++;
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(NTCBlackBoxData_Cnt_str[i].BlkBoxCfgData3, D_ZERO_CNT_U16);
                ReturnDataIdx_Cnt_T_u16++;
#ifndef D_ENABLEGENERICPARAMS_CNT_LGC
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(NTCBlackBoxData_Cnt_str[i].HwTrq_HwNm_s4p11);
                ReturnDataIdx_Cnt_T_u16++;
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(NTCBlackBoxData_Cnt_str[i].HwTrq_HwNm_s4p11);
                ReturnDataIdx_Cnt_T_u16++;
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(NTCBlackBoxData_Cnt_str[i].MtrTrq_MtrNm_s4p11);
                ReturnDataIdx_Cnt_T_u16++;
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(NTCBlackBoxData_Cnt_str[i].MtrTrq_MtrNm_s4p11);
#else
                /* DiagMgr v001.23 and later uses generic Param1 and Param2 to allow use of signals other than HwTrq
                 * and MtrTrq for programs such as MTO which uses DiffPres and CoilCurCmd */
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(NTCBlackBoxData_Cnt_str[i].Param1_Cnt_s16);
                ReturnDataIdx_Cnt_T_u16++;
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(NTCBlackBoxData_Cnt_str[i].Param1_Cnt_s16);
                ReturnDataIdx_Cnt_T_u16++;
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(NTCBlackBoxData_Cnt_str[i].Param2_Cnt_s16);
                ReturnDataIdx_Cnt_T_u16++;
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(NTCBlackBoxData_Cnt_str[i].Param2_Cnt_s16);
#endif /* D_ENABLEGENERICPARAMS_CNT_LGC */
                ReturnDataIdx_Cnt_T_u16++;
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(NTCBlackBoxData_Cnt_str[i].IgnCtr_Cnt_u16);
                ReturnDataIdx_Cnt_T_u16++;
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(NTCBlackBoxData_Cnt_str[i].IgnCtr_Cnt_u16);
                ReturnDataIdx_Cnt_T_u16++;
            }

            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFDAF_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FDB0
 *
 *    PID ID:          0xFDB0
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB)
 *
 *    Description:     IPM Cogging Table (1 of 5)
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFDB0_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FDB0 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(uint16, EPSDIAGSRVC_VAR) Index_Cnt_T_u16;
        VAR(CM_IPMCoggingCancTrq, EPSDIAGSRVC_VAR) IPMCoggingTrqValues;

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
            for(Index_Cnt_T_u16 = D_ZERO_CNT_U16; Index_Cnt_T_u16 < D_COGTRQ_LOOPLMT; Index_Cnt_T_u16++)
            {
                IPMCoggingTrqValues[Index_Cnt_T_u16] = bytesToWord_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16],
                                                                     DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16 + 1U]);
                RequestDataIdx_Cnt_T_u16 += 2U;
            }
            (void)CM_IPMTrqCanc_Scom_SetCogTrqCal((const CM_IPMCoggingCancTrq*)&IPMCoggingTrqValues, D_FDB0ARRAYINDEXOFFSET_CNT_U16);
        }
        else
        {
            /* Read Service */
            (void)CM_IPMTrqCanc_Scom_ReadCogTrqCal(&IPMCoggingTrqValues, D_FDB0ARRAYINDEXOFFSET_CNT_U16);
            for( Index_Cnt_T_u16 = D_ZERO_CNT_U16; Index_Cnt_T_u16 < D_COGTRQ_LOOPLMT; Index_Cnt_T_u16++)
            {
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(IPMCoggingTrqValues[Index_Cnt_T_u16]);
                ReturnDataIdx_Cnt_T_u16++;
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(IPMCoggingTrqValues[Index_Cnt_T_u16]);
                ReturnDataIdx_Cnt_T_u16++;
            }
            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFDB0_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FDB1
 *
 *    PID ID:          0xFDB1
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB)
 *
 *    Description:     IPM Cogging Table (2 of 5)
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFDB1_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FDB1 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(CM_IPMCoggingCancTrq, EPSDIAGSRVC_VAR) IPMCoggingTrqValues;
        VAR(uint16, EPSDIAGSRVC_VAR) Index_Cnt_T_u16;

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
            for(Index_Cnt_T_u16 = D_ZERO_CNT_U16; Index_Cnt_T_u16 < D_COGTRQ_LOOPLMT; Index_Cnt_T_u16++)
            {
                IPMCoggingTrqValues[Index_Cnt_T_u16] = bytesToWord_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16],
                                                                     DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16 + 1U]);
                RequestDataIdx_Cnt_T_u16 += 2U;
            }
            (void)CM_IPMTrqCanc_Scom_SetCogTrqCal((const CM_IPMCoggingCancTrq*)&IPMCoggingTrqValues, D_FDB1ARRAYINDEXOFFSET_CNT_U16);
        }
        else
        {
            /* Read Service */
            (void)CM_IPMTrqCanc_Scom_ReadCogTrqCal(&IPMCoggingTrqValues, D_FDB1ARRAYINDEXOFFSET_CNT_U16);
            for( Index_Cnt_T_u16 = D_ZERO_CNT_U16; Index_Cnt_T_u16 < D_COGTRQ_LOOPLMT; Index_Cnt_T_u16++)
            {
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(IPMCoggingTrqValues[Index_Cnt_T_u16]);
                ReturnDataIdx_Cnt_T_u16++;
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(IPMCoggingTrqValues[Index_Cnt_T_u16]);
                ReturnDataIdx_Cnt_T_u16++;
            }
            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFDB1_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FDB2
 *
 *    PID ID:          0xFDB2
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB)
 *
 *    Description:     IPM Cogging Table (3 of 5)
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFDB2_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FDB2 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(uint16, EPSDIAGSRVC_VAR) Index_Cnt_T_u16;
        VAR(CM_IPMCoggingCancTrq, EPSDIAGSRVC_VAR) IPMCoggingTrqValues;

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
            for(Index_Cnt_T_u16 = D_ZERO_CNT_U16; Index_Cnt_T_u16 < D_COGTRQ_LOOPLMT; Index_Cnt_T_u16++)
            {
                IPMCoggingTrqValues[Index_Cnt_T_u16] = bytesToWord_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16],
                                                                     DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16 + 1U]);
                RequestDataIdx_Cnt_T_u16 += 2U;
            }
            (void)CM_IPMTrqCanc_Scom_SetCogTrqCal((const CM_IPMCoggingCancTrq*)&IPMCoggingTrqValues, D_FDB2ARRAYINDEXOFFSET_CNT_U16);
        }
        else
        {
            /* Read Service */
            (void)CM_IPMTrqCanc_Scom_ReadCogTrqCal(&IPMCoggingTrqValues, D_FDB2ARRAYINDEXOFFSET_CNT_U16);
            for( Index_Cnt_T_u16 = D_ZERO_CNT_U16; Index_Cnt_T_u16 < D_COGTRQ_LOOPLMT; Index_Cnt_T_u16++)
            {
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(IPMCoggingTrqValues[Index_Cnt_T_u16]);
                ReturnDataIdx_Cnt_T_u16++;
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(IPMCoggingTrqValues[Index_Cnt_T_u16]);
                ReturnDataIdx_Cnt_T_u16++;
            }
            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFDB2_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FDB3
 *
 *    PID ID:          0xFDB3
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB)
 *
 *    Description:     IPM Cogging Table (4 of 5)
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFDB3_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FDB3 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(CM_IPMCoggingCancTrq, EPSDIAGSRVC_VAR) IPMCoggingTrqValues;
        VAR(uint16, EPSDIAGSRVC_VAR) Index_Cnt_T_u16;

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
            for(Index_Cnt_T_u16 = D_ZERO_CNT_U16; Index_Cnt_T_u16 < D_COGTRQ_LOOPLMT; Index_Cnt_T_u16++)
            {
                IPMCoggingTrqValues[Index_Cnt_T_u16] = bytesToWord_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16],
                                                                     DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16 + 1U]);
                RequestDataIdx_Cnt_T_u16 += 2U;
            }
            (void)CM_IPMTrqCanc_Scom_SetCogTrqCal((const CM_IPMCoggingCancTrq*)&IPMCoggingTrqValues, D_FDB3ARRAYINDEXOFFSET_CNT_U16);
        }
        else
        {
            /* Read Service */
            (void)CM_IPMTrqCanc_Scom_ReadCogTrqCal(&IPMCoggingTrqValues, D_FDB3ARRAYINDEXOFFSET_CNT_U16);
            for( Index_Cnt_T_u16 = D_ZERO_CNT_U16; Index_Cnt_T_u16 < D_COGTRQ_LOOPLMT; Index_Cnt_T_u16++)
            {
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(IPMCoggingTrqValues[Index_Cnt_T_u16]);
                ReturnDataIdx_Cnt_T_u16++;
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(IPMCoggingTrqValues[Index_Cnt_T_u16]);
                ReturnDataIdx_Cnt_T_u16++;
            }
            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFDB3_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FDB4
 *
 *    PID ID:          0xFDB4
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB)
 *
 *    Description:     Current Mode Analog Ke, R, Ld, and Lq
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFDB4_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FDB4 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(uint16, EPSDIAGSRVC_VAR) TempData_Cnt_T_u16;
        VAR(float32, EPSDIAGSRVC_VAR) NomKe_VpRadpS_T_f32;
        VAR(float32, EPSDIAGSRVC_VAR) NomRmtr_Ohm_T_f32;
        #ifndef D_RANDKESUPPORTONLY_CNT_LGC
            VAR(float32, EPSDIAGSRVC_VAR) NomLq_Henry_T_f32;
            VAR(float32, EPSDIAGSRVC_VAR) NomLd_Henry_T_f32;
        #endif

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
            TempData_Cnt_T_u16 = bytesToWord_m(DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16 + 0u)], DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16 + 1u)]);
            NomKe_VpRadpS_T_f32 = FPM_FixedToFloat_m(TempData_Cnt_T_u16, um1p17_T);

            TempData_Cnt_T_u16 = bytesToWord_m(DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16 + 2u)], DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16 + 3u)]);
            NomRmtr_Ohm_T_f32 = FPM_FixedToFloat_m(TempData_Cnt_T_u16, um1p17_T);

            #ifdef D_RANDKESUPPORTONLY_CNT_LGC
                CM_SCom_EOLNomMtrParam_Set_FDB4(NomKe_VpRadpS_T_f32, NomRmtr_Ohm_T_f32);
            #else
                TempData_Cnt_T_u16 = bytesToWord_m(DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16 + 4u)], DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16 + 5u)]);
                NomLq_Henry_T_f32 = FPM_FixedToFloat_m(TempData_Cnt_T_u16, um10p26_T);

                TempData_Cnt_T_u16 = bytesToWord_m(DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16 + 6u)], DataBuffer_Uls_T_u08[(RequestDataIdx_Cnt_T_u16 + 7u)]);
                NomLd_Henry_T_f32 = FPM_FixedToFloat_m(TempData_Cnt_T_u16, um10p26_T);

                CM_SCom_EOLNomMtrParam_Set_FDB4(NomKe_VpRadpS_T_f32, NomLq_Henry_T_f32, NomRmtr_Ohm_T_f32, NomLd_Henry_T_f32);
            #endif
        }
        else
        {
            /* Read Service */
            #ifdef D_RANDKESUPPORTONLY_CNT_LGC
                CM_SCom_EOLNomMtrParam_Get_FDB4(&NomKe_VpRadpS_T_f32, &NomRmtr_Ohm_T_f32);
            #else
                CM_SCom_EOLNomMtrParam_Get_FDB4(&NomKe_VpRadpS_T_f32, &NomLq_Henry_T_f32, &NomRmtr_Ohm_T_f32, &NomLd_Henry_T_f32);
            #endif


            TempData_Cnt_T_u16 = FPM_FloatToFixed_m(NomKe_VpRadpS_T_f32, um1p17_T);
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(TempData_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(TempData_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;

            TempData_Cnt_T_u16 = FPM_FloatToFixed_m(NomRmtr_Ohm_T_f32, um1p17_T);
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(TempData_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(TempData_Cnt_T_u16);
            ReturnDataIdx_Cnt_T_u16++;

            #ifdef D_RANDKESUPPORTONLY_CNT_LGC
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = 0U;
                ReturnDataIdx_Cnt_T_u16++;
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = 0U;
                ReturnDataIdx_Cnt_T_u16++;

                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = 0U;
                ReturnDataIdx_Cnt_T_u16++;
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = 0U;
                ReturnDataIdx_Cnt_T_u16++;
            #else
                TempData_Cnt_T_u16 = FPM_FloatToFixed_m(NomLq_Henry_T_f32, um10p26_T);
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(TempData_Cnt_T_u16);
                ReturnDataIdx_Cnt_T_u16++;
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(TempData_Cnt_T_u16);
                ReturnDataIdx_Cnt_T_u16++;

                TempData_Cnt_T_u16 = FPM_FloatToFixed_m(NomLd_Henry_T_f32, um10p26_T);
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(TempData_Cnt_T_u16);
                ReturnDataIdx_Cnt_T_u16++;
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(TempData_Cnt_T_u16);
                ReturnDataIdx_Cnt_T_u16++;
            #endif


            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFDB4_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FDB5
 *
 *    PID ID:          0xFDB5
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB)
 *
 *    Description:     Active Pull Set Short Term Comp
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFDB5_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FDB5 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(EPS_DiagSrv_DataStr, EPSDIAGSRVC_VAR) TempData_Cnt_T_str;
        VAR(float32, EPSDIAGSRVC_VAR) PC_MtrNm_T_f32;
        VAR(float32, EPSDIAGSRVC_VAR) PCST_HwNm_T_f32;
        VAR(float32, EPSDIAGSRVC_VAR) PCLT_HwNm_T_f32;
        VAR(boolean, EPSDIAGSRVC_VAR) PCEnabled_Cnt_T_lgc;

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
            TempData_Cnt_T_str.type.IntData_u32 = uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_MSBYTESHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            TempData_Cnt_T_str.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_WORDSHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            TempData_Cnt_T_str.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_BYTESHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            TempData_Cnt_T_str.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_ZERO_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;

            if ( (TempData_Cnt_T_str.type.FloatData_f32 >= 0.0F) &&
                 (TempData_Cnt_T_str.type.FloatData_f32 <= 4.0F) )
            {
                CM_ActivePull_SCom_SetSTComp(TempData_Cnt_T_str.type.FloatData_f32);
            }
            else
            {
                /* Request data out of range */
                CmdResp_Cnt_T_u08 = D_EPSNRCREQUESTDATAOUTOFRANGE_CNT_U08;
            }
        }
        else
        {
            /* Read Service */
            CM_ActivePull_SCom_ReadParam(&PC_MtrNm_T_f32, &PCST_HwNm_T_f32, &PCLT_HwNm_T_f32, &PCEnabled_Cnt_T_lgc);
            TempData_Cnt_T_str.type.FloatData_f32 = PCST_HwNm_T_f32;

            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData_Cnt_T_str.type.IntData_u32, D_MSBYTESHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData_Cnt_T_str.type.IntData_u32, D_WORDSHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData_Cnt_T_str.type.IntData_u32, D_BYTESHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData_Cnt_T_str.type.IntData_u32, D_ZERO_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;

            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFDB5_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FDB6
 *
 *    PID ID:          0xFDB6
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB)
 *
 *    Description:     Active Pull Set Long Term Comp
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFDB6_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FDB6 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(EPS_DiagSrv_DataStr, EPSDIAGSRVC_VAR) TempData_Cnt_T_str;
        VAR(float32, EPSDIAGSRVC_VAR) PC_MtrNm_T_f32;
        VAR(float32, EPSDIAGSRVC_VAR) PCST_HwNm_T_f32;
        VAR(float32, EPSDIAGSRVC_VAR) PCLT_HwNm_T_f32;
        VAR(boolean, EPSDIAGSRVC_VAR) PCEnabled_Cnt_T_lgc;

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
            TempData_Cnt_T_str.type.IntData_u32 = uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_MSBYTESHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            TempData_Cnt_T_str.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_WORDSHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            TempData_Cnt_T_str.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_BYTESHIFT_CNT_U16);
            RequestDataIdx_Cnt_T_u16++;
            TempData_Cnt_T_str.type.IntData_u32 |= uint8LeftShftuint32_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16], D_ZERO_CNT_U8);
            RequestDataIdx_Cnt_T_u16++;

            if ( (TempData_Cnt_T_str.type.FloatData_f32 >= 0.0F) &&
                 (TempData_Cnt_T_str.type.FloatData_f32 <= 4.0F) )
            {
                CM_ActivePull_SCom_SetLTComp(TempData_Cnt_T_str.type.FloatData_f32);
            }
            else
            {
                /* Request data out of range */
                CmdResp_Cnt_T_u08 = D_EPSNRCREQUESTDATAOUTOFRANGE_CNT_U08;
            }
        }
        else
        {
            /* Read Service */
            CM_ActivePull_SCom_ReadParam(&PC_MtrNm_T_f32, &PCST_HwNm_T_f32, &PCLT_HwNm_T_f32, &PCEnabled_Cnt_T_lgc);
            TempData_Cnt_T_str.type.FloatData_f32 = PCLT_HwNm_T_f32;

            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData_Cnt_T_str.type.IntData_u32, D_MSBYTESHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData_Cnt_T_str.type.IntData_u32, D_WORDSHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData_Cnt_T_str.type.IntData_u32, D_BYTESHIFT_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;
            DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = uint32RightShftuint8_m(TempData_Cnt_T_str.type.IntData_u32, D_ZERO_CNT_U16);
            ReturnDataIdx_Cnt_T_u16++;

            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFDB6_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/***********************************************************************************************************************
 *    Function Name:   EPSInternal_PID_FDB7
 *
 *    PID ID:          0xFDB7
 *
 *    Configured NRCs: MEC Counter Equals Zero (0xFB)
 *
 *    Description:     IPM Cogging Table (5 of 5)
 *
 *    Inputs:          SubFunc_Cnt_T_u08    : Sub-function type - varies based on srvc type - see MainHandler function
 *                     DataBuffer_Uls_T_u08 : Buffer for request/response data
 *                     RequestLen_Cnt_T_u16 : Number of byte of request data in buffer when function is called
 *                     RespLength_Cnt_T_u16 : Variable pointer to hold the number of response bytes in buffer on return
 *
 *    Outputs:         CmdResp_Cnt_T_u08    : D_EPSNRCNOERROR_CNT_U08 if no error or appropriate NRC
 *
 **********************************************************************************************************************/
#if (D_EPSDIAGSRVPIDFDB7_CNT_ENUM == D_DIAGSRVC_ENABLED)
    FUNC(uint8, EPSDIAGSRVC_CODE) EPSInternal_PID_FDB7 (VAR(uint8, EPSDIAGSRVC_VAR) SubFunc_Cnt_T_u08, VAR(uint8, EPSDIAGSRVC_VAR) DataBuffer_Uls_T_u08[], VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestLen_Cnt_T_u16, P2VAR(CM_MsgLenType, EPSDIAGSRVC_VAR, EPSDIAGSRVC_VAR) RespLength_Cnt_T_u16)
    {
        /* Local Vars */
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) ReturnDataIdx_Cnt_T_u16 = 0U;
        VAR(CM_MsgLenType, EPSDIAGSRVC_VAR) RequestDataIdx_Cnt_T_u16 = 0U;
        VAR(uint8, EPSDIAGSRVC_VAR) CmdResp_Cnt_T_u08 = D_EPSNRCNOERROR_CNT_U08;
        VAR(CM_IPMCoggingCancTrq, EPSDIAGSRVC_VAR) IPMCoggingTrqValues;
        VAR(uint16, EPSDIAGSRVC_VAR) Index_Cnt_T_u16;

        if (SubFunc_Cnt_T_u08 == D_SRVCREQTYPEWRITE_CNT_U16)
        {
            /* Write Service */
            for(Index_Cnt_T_u16 = D_ZERO_CNT_U16; Index_Cnt_T_u16 < 9U; Index_Cnt_T_u16++)
            {
                IPMCoggingTrqValues[Index_Cnt_T_u16] = bytesToWord_m(DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16],
                                                                     DataBuffer_Uls_T_u08[RequestDataIdx_Cnt_T_u16 + 1U]);
                RequestDataIdx_Cnt_T_u16 += 2U;
            }
            (void)CM_IPMTrqCanc_Scom_SetCogTrqCal((const CM_IPMCoggingCancTrq*)&IPMCoggingTrqValues, D_FDB7ARRAYINDEXOFFSET_CNT_U16);
        }
        else
        {
            /* Read Service */
            (void)CM_IPMTrqCanc_Scom_ReadCogTrqCal(&IPMCoggingTrqValues, D_FDB7ARRAYINDEXOFFSET_CNT_U16);
            for( Index_Cnt_T_u16 = D_ZERO_CNT_U16; Index_Cnt_T_u16 < 9U; Index_Cnt_T_u16++)
            {
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = MSB(IPMCoggingTrqValues[Index_Cnt_T_u16]);
                ReturnDataIdx_Cnt_T_u16++;
                DataBuffer_Uls_T_u08[ReturnDataIdx_Cnt_T_u16] = LSB(IPMCoggingTrqValues[Index_Cnt_T_u16]);
                ReturnDataIdx_Cnt_T_u16++;
            }
            *RespLength_Cnt_T_u16 = ReturnDataIdx_Cnt_T_u16;
        }

        return CmdResp_Cnt_T_u08;
    }
#endif /* (D_EPSDIAGSRVPIDFDB7_CNT_ENUM == D_DIAGSRVC_ENABLED) */


/******************************* END CMS GENERATION - DO NOT CHANGE/REMOVE THIS COMMENT *******************************/
