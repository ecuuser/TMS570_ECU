/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Ap_StOpCtrl.c
 *     Workspace:  C:/Documents and Settings/nzt9hv/My Documents/Synergy/ccm_wa/ESG_Dev_65/StOpCtrl-nzt9hv/StOpCtrl/autosar
 *     SW-C Type:  Ap_StOpCtrl
 *  Generated at:  Sun Sep 23 16:39:55 2012
 *
 *     Generator:  MICROSAR RTE Generator Version 2.17.2
 *       License:  License CBD1010122 valid for CBD1010122 Nexteer  GM MSR_SLP3_BSW_RTE_wGMLAN TexasInstruments TMS570 Texas Instruments
 *
 *   Description:  C-Code implementation template for SW-C <Ap_StOpCtrl>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/* Version Control:
 * Date Created:      Tue Mar 15 17:16:01 2011
 * %version:          21 %
 * %derived_by:       nzt9hv %
 * %date_modified:    Sun Sep 23 16:20:25 2012 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 01/12/11  3        JJW       New generation of Davinci template
 * 01/13/11  4        JJW       Initial ramping queue implementation
 * 01/14/11  5        JJW       Corrected IRV buffered write of AttenFactor
 *                               Added F2 ramp actions
 * 01/14/11  6        JJW       Corrected Operate request logic
 * 02/28/11  8        LWW       Added F1Flag check in Per2
 * 03/26/11  9       JJW       System Framework Update
 * 03/26/11  10      JJW       Remove F1 Fault Flag, implement Cancel Ramp Request Server Runnable
 * 04/11/11  11      LWW       Updated for states and modes design changes
 * 04/11/11  12      LWW       Changed ramping calculation order for A_2265
 * 06/01/11  13      JJW       Template update to provide SrlComSvcDft access for ramp defeat
 * 01/05/12  14      NRAR      Updated as per FDD SF05, Ver OO1c
 * 01/06/12  15      NRAR      D_MAXRAMP_XPMS_F32 Value is changed
 * 01/12/12  16      NRAR      DiagStsF1Active variable name is updated to standard form DiagStsDiagRmpActive
 * 08/11/12  20      BWL       Anom #3272 PrevTargetRampMult is the last target, and PrevOutputRampMult is the last output.
 * 09/23/12  21      Selva      Checkpoints added and mempmap macros corrected		                          6247
 */
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

#include "Rte_Ap_StOpCtrl.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
#include "GlobalMacro.h"
#include <float.h>
#include "Ap_StOpCtrl_Cfg.h"


#define D_TWO_MS_U32          2U
#define D_MAXRAMP_XPMS_F32    0.5F




/* TODO: define the Ramp State structure globally when the Ramp library is defined */
typedef struct RampState{
	uint32   StartTime_mS_u32;
	uint32   Duration_mS_u32;
	float32  StartVal_Uls_f32;
	float32  EndVal_Uls_f32;
}RampState_T;

#define STOPCTRL_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"
STATIC VAR(RampState_T,  STOPCTRL_VAR_NOINIT) RampState_M_Str;
#define STOPCTRL_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"



#define STOPCTRL_START_SEC_VAR_NOINIT_32
#include "MemMap.h"
STATIC VAR(float32,  STOPCTRL_VAR_NOINIT) PrevTargetRampMult_Uls_M_f32;
STATIC VAR(float32,  STOPCTRL_VAR_NOINIT) PrevOutputRampMult_Uls_M_f32;
STATIC VAR(float32,  STOPCTRL_VAR_NOINIT) PrevRate_XpmS_M_f32;
#define STOPCTRL_STOP_SEC_VAR_NOINIT_32
#include "MemMap.h"


STATIC FUNC(float32, RTE_AP_STATEOUTPUTCONTROL_APPL_CODE) RampLib(RampState_T rampState_T_Str);
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
 * Boolean: Boolean (standard type)
 * Float: Real in interval ]-FLT_MAX...FLT_MAX[ with single precision (standard type)
 * UInt16: Integer in interval [0...65535] (standard type)
 * UInt32: Integer in interval [0...4294967295] (standard type)
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
 * Boolean: D_FALSE_CNT_LGC = FALSE
 * Float: D_ZERO_ULS_F32 = 0
 *
 *********************************************************************************************************************/


#define RTE_START_SEC_AP_STOPCTRL_APPL_CODE
#include "MemMap.h"

/**********************************************************************************************************************
 *
 * Runnable Entity Name: StOpCtrl_Per1
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 2ms
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Implicit S/R API:
 *   -----------------
 *   Float Rte_IRead_StOpCtrl_Per1_DiagRampRate_XpmS_f32(void)
 *   Float Rte_IRead_StOpCtrl_Per1_DiagRampValue_Uls_f32(void)
 *   Boolean Rte_IRead_StOpCtrl_Per1_DiagStsDiagRmpActive_Cnt_lgc(void)
 *   Float Rte_IRead_StOpCtrl_Per1_OperRampRate_XpmS_f32(void)
 *   Float Rte_IRead_StOpCtrl_Per1_OperRampValue_Uls_f32(void)
 *   Boolean Rte_IRead_StOpCtrl_Per1_RampSrlComSvcDft_Cnt_lgc(void)
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_StOpCtrl_Per1_OutputRampMult_Uls_f32(Float data)
 *   Float *Rte_IWriteRef_StOpCtrl_Per1_OutputRampMult_Uls_f32(void)
 *   void Rte_IWrite_StOpCtrl_Per1_RampDwnStatusComplete_Cnt_lgc(Boolean data)
 *   Boolean *Rte_IWriteRef_StOpCtrl_Per1_RampDwnStatusComplete_Cnt_lgc(void)
 *
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
 *   Std_ReturnType Rte_Call_SystemTime_DtrmnElapsedTime_mS_u32(UInt32 InitialTime, UInt32 *ElapsedTime)
 *     Synchronous Service Invocation. Timeout: None
 *   Std_ReturnType Rte_Call_SystemTime_GetSystemTime_mS_u32(UInt32 *CurrentTime)
 *     Synchronous Service Invocation. Timeout: None
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_STOPCTRL_APPL_CODE) StOpCtrl_Per1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: StOpCtrl_Per1
 *********************************************************************************************************************/

	VAR(float32, AUTOMATIC)      OperRampRate_XpmS_T_f32;
	VAR(float32, AUTOMATIC)      OperRampValue_Uls_T_f32;
	VAR(float32, AUTOMATIC)      DiagRampValue_Uls_T_f32;
	VAR(float32, AUTOMATIC)      DiagRampRate_XpmS_T_f32;
	VAR(boolean, AUTOMATIC)      DiagStsDiagRmpActive_Cnt_T_lgc;
    VAR(boolean, AUTOMATIC) 	 RampDwnStatusComplete_T_lgc;
    VAR(float32, AUTOMATIC)      rate_T_f32;
    VAR(float32, AUTOMATIC)      target_T_f32;
    VAR(float32, AUTOMATIC)      NewOutputRampMult_T_f32;
    VAR(boolean, AUTOMATIC)      RampSrlComSvcDft_Cnt_T_lgc;
	VAR(float32, AUTOMATIC)      DiffOutputRampMult_T_f32;
	VAR(float32, AUTOMATIC)      DiffRate_T_f32;
    
	/* Configurable Start of Runnable Checkpoint */
	Rte_Call_StOpCtrl_Per1_CP0_CheckpointReached();

	/*Store Inputs to Module local copy*/

	OperRampRate_XpmS_T_f32 = Rte_IRead_StOpCtrl_Per1_OperRampRate_XpmS_f32();
	OperRampValue_Uls_T_f32 =Rte_IRead_StOpCtrl_Per1_OperRampValue_Uls_f32();
	DiagRampValue_Uls_T_f32=Rte_IRead_StOpCtrl_Per1_DiagRampValue_Uls_f32();
	DiagRampRate_XpmS_T_f32=Rte_IRead_StOpCtrl_Per1_DiagRampRate_XpmS_f32();
	DiagStsDiagRmpActive_Cnt_T_lgc= Rte_IRead_StOpCtrl_Per1_DiagStsDiagRmpActive_Cnt_lgc();
	RampSrlComSvcDft_Cnt_T_lgc= Rte_IRead_StOpCtrl_Per1_RampSrlComSvcDft_Cnt_lgc();

	
	if(FALSE == DiagStsDiagRmpActive_Cnt_T_lgc)
	{
		rate_T_f32= OperRampRate_XpmS_T_f32;
		target_T_f32= OperRampValue_Uls_T_f32;
	}
	else
	{
		rate_T_f32=DiagRampRate_XpmS_T_f32;
		target_T_f32= DiagRampValue_Uls_T_f32;
	}

	if (TRUE == RampSrlComSvcDft_Cnt_T_lgc)
	{
		rate_T_f32 = D_MAXRAMP_XPMS_F32;/*which is 1 over here*/
	}

	DiffOutputRampMult_T_f32 = Abs_f32_m(PrevTargetRampMult_Uls_M_f32 - target_T_f32);
	DiffRate_T_f32 = Abs_f32_m(PrevRate_XpmS_M_f32 - rate_T_f32);
	if((DiffOutputRampMult_T_f32 > FLT_EPSILON) || (DiffRate_T_f32  > FLT_EPSILON))
	{
		
		RampState_M_Str.Duration_mS_u32 = (uint32)( Abs_f32_m( PrevOutputRampMult_Uls_M_f32 - target_T_f32)/ rate_T_f32);
		RampState_M_Str.StartVal_Uls_f32 = PrevOutputRampMult_Uls_M_f32;
		RampState_M_Str.EndVal_Uls_f32 = target_T_f32;


		Rte_Call_SystemTime_GetSystemTime_mS_u32(&(RampState_M_Str.StartTime_mS_u32)); 
		/* Subtract 2ms to preload ramp timer (because command is applied in next 2ms loop) */
		RampState_M_Str.StartTime_mS_u32 = RampState_M_Str.StartTime_mS_u32 - D_TWO_MS_U32;
		
	}


NewOutputRampMult_T_f32 = RampLib(RampState_M_Str);

if( NewOutputRampMult_T_f32 < FLT_EPSILON)
{
	RampDwnStatusComplete_T_lgc = TRUE;
	
}
else
{
	RampDwnStatusComplete_T_lgc = FALSE;
}

PrevTargetRampMult_Uls_M_f32 = target_T_f32;
PrevOutputRampMult_Uls_M_f32=NewOutputRampMult_T_f32;
PrevRate_XpmS_M_f32=rate_T_f32;

Rte_IWrite_StOpCtrl_Per1_OutputRampMult_Uls_f32(NewOutputRampMult_T_f32);
Rte_IWrite_StOpCtrl_Per1_RampDwnStatusComplete_Cnt_lgc(RampDwnStatusComplete_T_lgc);

/* Configurable End of Runnable Checkpoint */
Rte_Call_StOpCtrl_Per1_CP1_CheckpointReached();

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define RTE_STOP_SEC_AP_STOPCTRL_APPL_CODE
#include "MemMap.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of function definition area >>            DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
#define RTE_START_SEC_AP_STOPCTRL_APPL_CODE
#include "MemMap.h"
/*TODO: Migrate this function to a common library in the future */
STATIC FUNC(float32, RTE_AP_STATEOUTPUTCONTROL_APPL_CODE) RampLib(RampState_T rampState_T_Str)
{
VAR(uint32, AUTOMATIC)  ElapsedRamp_mS_T_u32;
VAR(float32, AUTOMATIC) Output_Uls_T_f32;
	
Rte_Call_SystemTime_DtrmnElapsedTime_mS_u32(rampState_T_Str.StartTime_mS_u32, &ElapsedRamp_mS_T_u32);

if(ElapsedRamp_mS_T_u32 >= rampState_T_Str.Duration_mS_u32)
{
	Output_Uls_T_f32 = rampState_T_Str.EndVal_Uls_f32;
}
else
{
	Output_Uls_T_f32 =  rampState_T_Str.StartVal_Uls_f32 + 
                    ((rampState_T_Str.EndVal_Uls_f32 - rampState_T_Str.StartVal_Uls_f32) * ((float32)ElapsedRamp_mS_T_u32 / (float32)rampState_T_Str.Duration_mS_u32));
}

return(Output_Uls_T_f32);               

}
#define RTE_STOP_SEC_AP_STOPCTRL_APPL_CODE
#include "MemMap.h"
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of function definition area >>              DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of removed code area >>                   DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of removed code area >>                     DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
