/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Ap_EtDmpFw.c
 *     Workspace:  C:/Synergy_projects/EtDmpFw-lz4p8n/EtDmpFw/autosar/Ap_EtDmpFw.dcf
 *     SW-C Type:  Ap_EtDmpFw
 *  Generated at:  Thu May 16 14:24:28 2013
 *
 *     Generator:  MICROSAR RTE Generator Version 2.19.1
 *       License:  License CBD1010124 valid for CBD1010124 Nexteer  Package: BMW MSR SIP BAC3.0     Micro: TI TMS570 TMS570LS30306  Compiler: Code Composer Studio 4.9.0
 *
 *   Description:  C-Code implementation template for SW-C <Ap_EtDmpFw>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/* Version Control:
 * Date Created:      Fri Dec  2 16:41:06 2011
 * %version:          5 %
 * %derived_by:       lz4p8n %
 * %date_modified:    Thu May 16 12:52:50 2013 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 08/29/2012   1		NRAR			Component creation.
 * 09/16/2012   2		BWL				Added watchdog checkpoints												6223
 * 01/29/2013	3		Selva			Addition of a Fault Injection Point (at the Assist_EOTDamping input)    7187
 * 05/16/2013   5       SP				Updated to SF-27 v003													7820
 */


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

#include "Rte_Ap_EtDmpFw.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
 
#include "CalConstants.h"
#include "fixmath.h"
#include "fpmtype.h"
#include "GlobalMacro.h"
#include "interpolation.h"
#include "Ap_EtDmpFw_Cfg.h"

#define D_INACTIVEREGION_ULS_U08			0U
#define D_ACTIVEREGION_ULS_U08				1U
#define D_FIREWALLLDISABLED_ULS_U08			2U

#define ETDMPFW_START_SEC_VAR_CLEARED_32
#include "MemMap.h"
STATIC volatile VAR(float32, AP_ETDMPFW_VAR) EOTDmpFWActvLtd_MtrNm_D_f32;
STATIC volatile VAR(float32, AP_ETDMPFW_VAR) EOTDmpFWInActvLtd_MtrNm_D_f32;
STATIC volatile VAR(float32, AP_ETDMPFW_VAR) UprBndActive_MtrNm_D_f32;
STATIC volatile VAR(float32, AP_ETDMPFW_VAR) LwrBndActive_MtrNm_D_f32;
#define ETDMPFW_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */

#define ETDMPFW_START_SEC_VAR_CLEARED_08
#include "MemMap.h" /* PRQA S 5087 */
STATIC volatile VAR(uint8, AP_ETDMPFW_VAR) EOTDmpFWMode_Cnt_M_u08;
#define ETDMPFW_STOP_SEC_VAR_CLEARED_08
#include "MemMap.h" /* PRQA S 5087 */

#define ETDMPFW_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h" /* PRQA S 5087 */
STATIC volatile VAR(boolean, AP_ETDMPFW_VAR) EOTDmpFWActvRegion_Cnt_D_lgc;
STATIC volatile VAR(boolean, AP_ETDMPFW_VAR) EOTDmpFWHWAuth_Cnt_D_lgc;
#define ETDMPFW_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h" /* PRQA S 5087 */

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
 * Float: Real in interval [-FLT_MAX...FLT_MAX] with single precision (standard type)
 * SInt16: Integer in interval [-32768...32767] (standard type)
 *
 * Enumeration Types:
 * ==================
 * FltInjectionLocType: Enumeration of integer in interval [0...255] with enumerators
 *   FLTINJ_ASSIST (1U)
 *   FLTINJ_RETURN (2U)
 *   FLTINJ_DAMPING (3U)
 *   FLTINJ_ASSTSUMNLMT (4U)
 *   FLTINJ_AVGFRICLRN (7U)
 *   FLTINJ_VECU_BATTERYVOLTAGE (8U)
 *   FLTINJ_HYSTCOMP (12U)
 *   FLTINJ_INERTIACOMP (14U)
 *   FLTINJ_EOTDAMPING_ETDMPFW (27U)
 *   FLTINJ_STABILITYCOMP (29U)
 *   FLTINJ_TRQBASEDINRTCOMP (30U)
 *   FLTINJ_SRLCOMVEHSPD_SGNLCOND (33U)
 *   FLTINJ_ASSTFIREWALL (34U)
 *   FLTINJ_ASSTEOTGAIN_LMTCOD (38U)
 *   FLTINJ_DDASTFACTRQST_DRVDYNCTRL (150U)
 *   FLTINJ_DDDMPFACTRQST_DRVDYNCTRL (151U)
 *   FLTINJ_DDRTNFACTRQST_DRVDYNCTRL (152U)
 *   FLTINJ_OUTPUTRAMPMULT_LMTCOD (153U)
 *   FLTINJ_ASSTEOTLIMIT_LMTCOD (154U)
 * ManufModeType: Enumeration of integer in interval [0...2] with enumerators
 *   ProductionMode (0U)
 *   ManufacturingMode (1U)
 *   EngineeringMode (2U)
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
 * Float: D_2MS_SEC_F32 = 0.002F
 * Float: D_MTRTRQCMDHILMT_MTRNM_F32 = 8.8F
 * Float: D_MTRTRQCMDLOLMT_MTRNM_F32 = -8.8F
 * Float: D_ZERO_ULS_F32 = 0.0F
 * SInt16: D_NEGONE_CNT_S16 = -1
 *
 *********************************************************************************************************************/


#define RTE_START_SEC_AP_ETDMPFW_APPL_CODE
#include "MemMap.h" /* PRQA S 5087 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: EtDmpFw_Per1
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
 *   Float Rte_IRead_EtDmpFw_Per1_AssistEOTDamping_MtrNm_f32(void)
 *   Float Rte_IRead_EtDmpFw_Per1_CRFMtrVel_MtrRadpS_f32(void)
 *   Boolean Rte_IRead_EtDmpFw_Per1_EOTDisable_Cnt_lgc(void)
 *   Float Rte_IRead_EtDmpFw_Per1_HandwheelAuthority_Uls_f32(void)
 *   Float Rte_IRead_EtDmpFw_Per1_HandwheelPosition_HwDeg_f32(void)
 *   ManufModeType Rte_IRead_EtDmpFw_Per1_MEC_Counter_Cnt_enum(void)
 *   Float Rte_IRead_EtDmpFw_Per1_Vehicle_Speed_Kph_f32(void)
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_EtDmpFw_Per1_EOTDampingLtd_MtrNm_f32(Float data)
 *   Float *Rte_IWriteRef_EtDmpFw_Per1_EOTDampingLtd_MtrNm_f32(void)
 *
 * Client/Server Interfaces:
 * =========================
 *   Server Invocation:
 *   ------------------
 *   Std_ReturnType Rte_Call_FaultInjection_SCom_FltInjection(Float *SignalPath_Uls_f32, FltInjectionLocType LocationKey_Cnt_enum)
 *     Synchronous Server Invocation. Timeout: None
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_ETDMPFW_APPL_CODE) EtDmpFw_Per1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: EtDmpFw_Per1
 *********************************************************************************************************************/
VAR(float32, AUTOMATIC) AsstEOTDamping_MtrNm_T_f32;
VAR(float32, AUTOMATIC) HandwheelPosition_HwDeg_T_f32;
VAR(float32, AUTOMATIC) HandwheelAuthority_Uls_T_f32;
VAR(float32, AUTOMATIC) CRFMtrVel_MtrRadpS_T_f32;
VAR(float32, AUTOMATIC) EOTDamping_MtrNm_T_f32;
VAR(uint16, AUTOMATIC) EOTDmpFWX0_HwDeg_T_u12p4;
VAR(float32, AUTOMATIC) EOTDmpFWX0_HwDeg_T_f32;
VAR(sint16, AUTOMATIC) CRFMtrVel_MtrRadpS_T_s11p4;
VAR(float32, AUTOMATIC) LimitedEOTDamping_MtrNm_T_f32;
VAR(float32, AUTOMATIC) LwrBndActive_MtrNm_T_f32;
VAR(sint16, AUTOMATIC) LwrBndActive_MtrNm_T_s7p8;
VAR(float32, AUTOMATIC) UprBndActive_MtrNm_T_f32;
VAR(sint16, AUTOMATIC) UprBndActive_MtrNm_T_s7p8;
VAR(boolean, AUTOMATIC) EOTDmpFWActvRegion_Cnt_T_lgc;
VAR(boolean, AUTOMATIC) EOTDmpFWHWAuth_Cnt_T_lgc;
VAR(float32, AUTOMATIC) EOTDmpFWActLtd_MtrNm_T_f32;
VAR(float32, AUTOMATIC) EOTDmpFWInActLtd_MtrNm_T_f32;
VAR(uint16,  AUTOMATIC) VehicleSpeed_Kph_T_u9p7;
VAR(float32, AUTOMATIC) VehicleSpeed_Kph_T_f32;

VAR(boolean, AUTOMATIC) EOTDisable_Cnt_T_lgc;
VAR(ManufModeType, AUTOMATIC) MECCounter_Cnt_T_enum;
	
/* Configurable Start of Runnable Checkpoint */
Rte_Call_EtDmpFw_Per1_CP0_CheckpointReached();

/*Store to local inputs */
AsstEOTDamping_MtrNm_T_f32 = Rte_IRead_EtDmpFw_Per1_AssistEOTDamping_MtrNm_f32();
HandwheelPosition_HwDeg_T_f32 = Rte_IRead_EtDmpFw_Per1_HandwheelPosition_HwDeg_f32();
HandwheelAuthority_Uls_T_f32 = Rte_IRead_EtDmpFw_Per1_HandwheelAuthority_Uls_f32();
CRFMtrVel_MtrRadpS_T_f32 = Rte_IRead_EtDmpFw_Per1_CRFMtrVel_MtrRadpS_f32();

VehicleSpeed_Kph_T_f32 = Rte_IRead_EtDmpFw_Per1_Vehicle_Speed_Kph_f32();
VehicleSpeed_Kph_T_u9p7 = FPM_FloatToFixed_m(VehicleSpeed_Kph_T_f32, u9p7_T);

EOTDisable_Cnt_T_lgc = Rte_IRead_EtDmpFw_Per1_EOTDisable_Cnt_lgc();
MECCounter_Cnt_T_enum = Rte_IRead_EtDmpFw_Per1_MEC_Counter_Cnt_enum();

/*** Fault Injection Point ***/
#if(STD_ON == BC_ETDMPFW_FAULTINJECTIONPOINT)
(void) Rte_Call_FaultInjection_SCom_FltInjection(&AsstEOTDamping_MtrNm_T_f32,FLTINJ_EOTDAMPING_ETDMPFW);
#endif


CRFMtrVel_MtrRadpS_T_s11p4 = FPM_FloatToFixed_m(CRFMtrVel_MtrRadpS_T_f32, s11p4_T);
/*** EOT Damp calculation ***/
EOTDamping_MtrNm_T_f32 = AsstEOTDamping_MtrNm_T_f32;
/*** Max EOT Active range Calculation ***/
EOTDmpFWX0_HwDeg_T_u12p4 = k_MinRackTrvl_HwDeg_u12p4 - t2_EOTPosDepDmpTblX_HwDeg_u12p4[0][0];
EOTDmpFWX0_HwDeg_T_f32 = FPM_FixedToFloat_m(EOTDmpFWX0_HwDeg_T_u12p4, u12p4_T);

/***Determine Boundaries ***/
/* ActvCalculation */

UprBndActive_MtrNm_T_s7p8 = BilinearXYM_s16_s16Xs16YM_Cnt(VehicleSpeed_Kph_T_u9p7,
															CRFMtrVel_MtrRadpS_T_s11p4,
															t_EOTDmpFWVehSpd_Kph_u9p7,
															TableSize_m(t_EOTDmpFWVehSpd_Kph_u9p7),
															t_EOTDmpFWActiveBoundX_MtrRadpS_s11p4,
															t2_EOTDmpFWActiveBoundY_MtrNm_s7p8[0],
															TableSize_m(t_EOTDmpFWActiveBoundX_MtrRadpS_s11p4));

UprBndActive_MtrNm_T_f32 = FPM_FixedToFloat_m(UprBndActive_MtrNm_T_s7p8, s7p8_T);

LwrBndActive_MtrNm_T_s7p8 = BilinearXYM_s16_s16Xs16YM_Cnt(VehicleSpeed_Kph_T_u9p7,
															(D_NEGONE_CNT_S16 * CRFMtrVel_MtrRadpS_T_s11p4),
															t_EOTDmpFWVehSpd_Kph_u9p7,
															TableSize_m(t_EOTDmpFWVehSpd_Kph_u9p7),
															t_EOTDmpFWActiveBoundX_MtrRadpS_s11p4,
															t2_EOTDmpFWActiveBoundY_MtrNm_s7p8[0],
															TableSize_m(t_EOTDmpFWActiveBoundX_MtrRadpS_s11p4));

LwrBndActive_MtrNm_T_f32 = FPM_FixedToFloat_m((D_NEGONE_CNT_S16 * LwrBndActive_MtrNm_T_s7p8), s7p8_T);

EOTDmpFWActLtd_MtrNm_T_f32 = Limit_m(EOTDamping_MtrNm_T_f32, LwrBndActive_MtrNm_T_f32, UprBndActive_MtrNm_T_f32);



/*InActv Calculation */
EOTDmpFWInActLtd_MtrNm_T_f32 = Limit_m(EOTDamping_MtrNm_T_f32, -k_EOTDmpFWInactiveLim_MtrNm_f32, k_EOTDmpFWInactiveLim_MtrNm_f32);

/*** Handwheel position inboard check ***/
if(Abs_f32_m(HandwheelPosition_HwDeg_T_f32) >= EOTDmpFWX0_HwDeg_T_f32)
{
	EOTDmpFWActvRegion_Cnt_T_lgc = TRUE;
}
else
{
	EOTDmpFWActvRegion_Cnt_T_lgc = FALSE;
}

/*** HandwheelAuthority calibration check ***/
if(HandwheelAuthority_Uls_T_f32 >=  FPM_FixedToFloat_m(k_EOTDynConf_Uls_u8p8, u8p8_T))
{
	EOTDmpFWHWAuth_Cnt_T_lgc = TRUE;
}
else
{
	EOTDmpFWHWAuth_Cnt_T_lgc = FALSE;
}

/*** Applying saturation limits based on handwheel position and handwheel authority ***/ 

/* Instead of using MEC Counter the enum is being used. enum equals ProductionMode when MEC Counter is 0. */
if((EOTDisable_Cnt_T_lgc != D_FALSE_CNT_LGC) && (MECCounter_Cnt_T_enum != ProductionMode)) 
{
	LimitedEOTDamping_MtrNm_T_f32 = Limit_m(EOTDamping_MtrNm_T_f32,D_MTRTRQCMDLOLMT_MTRNM_F32 , D_MTRTRQCMDHILMT_MTRNM_F32);
	EOTDmpFWMode_Cnt_M_u08 = D_FIREWALLLDISABLED_ULS_U08;
}

else if((TRUE == EOTDmpFWActvRegion_Cnt_T_lgc) && (TRUE == EOTDmpFWHWAuth_Cnt_T_lgc ))
{

	LimitedEOTDamping_MtrNm_T_f32 = Limit_m(EOTDmpFWActLtd_MtrNm_T_f32,D_MTRTRQCMDLOLMT_MTRNM_F32 , D_MTRTRQCMDHILMT_MTRNM_F32);
	EOTDmpFWMode_Cnt_M_u08 = D_ACTIVEREGION_ULS_U08;
}

else
{
	LimitedEOTDamping_MtrNm_T_f32 = Limit_m(EOTDmpFWInActLtd_MtrNm_T_f32,D_MTRTRQCMDLOLMT_MTRNM_F32 , D_MTRTRQCMDHILMT_MTRNM_F32);
	EOTDmpFWMode_Cnt_M_u08 = D_INACTIVEREGION_ULS_U08;
}

/*** Assigning the output to the Display variables ***/
EOTDmpFWActvRegion_Cnt_D_lgc = EOTDmpFWActvRegion_Cnt_T_lgc;
EOTDmpFWHWAuth_Cnt_D_lgc = EOTDmpFWHWAuth_Cnt_T_lgc;
UprBndActive_MtrNm_D_f32 = UprBndActive_MtrNm_T_f32;
LwrBndActive_MtrNm_D_f32 = LwrBndActive_MtrNm_T_f32;
EOTDmpFWActvLtd_MtrNm_D_f32 = EOTDmpFWActLtd_MtrNm_T_f32;
EOTDmpFWInActvLtd_MtrNm_D_f32 = EOTDmpFWInActLtd_MtrNm_T_f32;


/***Writing back the output ***/
Rte_IWrite_EtDmpFw_Per1_EOTDampingLtd_MtrNm_f32(LimitedEOTDamping_MtrNm_T_f32);

/* Configurable Start of Runnable Checkpoint */
Rte_Call_EtDmpFw_Per1_CP1_CheckpointReached();
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define RTE_STOP_SEC_AP_ETDMPFW_APPL_CODE
#include "MemMap.h" /* PRQA S 5087 */


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of function definition area >>            DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of function definition area >>              DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of removed code area >>                   DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of removed code area >>                     DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
