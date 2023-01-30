/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Ap_EOTActuatorMng.c
 *     Workspace:  C:/_swb/CBD/EOTActuatorMng-cz7lt6/EOTActuatorMng/autosar
 *     SW-C Type:  Ap_EOTActuatorMng
 *  Generated at:  Thu May 28 12:53:52 2015
 *
 *     Generator:  MICROSAR RTE Generator Version 2.17.2
 *       License:  License CBD1010122 valid for CBD1010122 Nexteer  GM MSR_SLP3_BSW_RTE_wGMLAN TexasInstruments TMS570 Texas Instruments
 *
 *   Description:  C-Code implementation template for SW-C <Ap_EOTActuatorMng>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/* Version Control:
 * Date Created:      Fri Dec  2 16:41:06 2011
 * %version:          19 %
 * %derived_by:       cz7lt6 %
 * %date_modified:    Fri Jan 24 08:27:05 2014 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 *           1                  Component creation.
 * 12/06/11  2          KJS     Initial release of the component based design.                                  4072
 * 12/12/11  3          JJW     Chnaged units of k_EOTStateHwTrqLPFKn_Uls_u16 to Cnt
 * 12/14/11  4          KJS     Corrected AssistEOTLimit limit macro call with incorrect variable.
 * 03/17/12  5          M. Story Anomaly 3003 and 3039
 * 03/19/12  6          LWW     Changed incorrect table index constant to TableSize macro
 * 03/22/12  7          M. Story Updated to changes in FDD
 * 05/10/12  8          M. Story Changed t_TrqTblY_Uls_u16p0 to t_TrqTblY_Uls_u1p15 anomaly 3146
 * 05/10/12  9          M. Story Changed t_TrqTblY_Uls_u1p15 to t_TrqTblY_Uls_u2p14 anomaly 3146
 * 05/23/12  10         LWW     Updates for anomaly 3330 correctionn
 * 08/14/12  11         BWL     Update to FDD v006. Added defeat service.
 * 09/16/12  12         BWL     Added watchdog checkpoints.                                                     6221
 * 09/25/12  13         Selva   Added memmap checkpoints.                                                       6221
 * 10/22/12  14         Srikanth Changes in "End Of Travel Impact(Original)" for anomaly 3938                   6588
 * 01/18/13  15         KJS     Anomaly 4269 changes, cleared up MISRA violations                               7106
 * 04/24/13  16         JJW     Increased resolution of t2_EOTPosDepDmpTblY_ and t2_EOTExPosDepDmpTblY
 * 07/25/13  17         KMC     Anomaly 5251 change -- correct ramping of EOTImpactPos_HwDeg_M_f32 so it        9136
 *                              can't become negative.
 * 01/25/13  18         Selva   Updated to v8 and v9 of the SF18                                                11204
 * 05/27/15  19         KJS     Updated to v10 of SF18, anomaly 7605 correction                                 13389
 */
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

#include "Rte_Ap_EOTActuatorMng.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
#include "fpmtype.h"
#include "GlobalMacro.h"
#include "CalConstants.h"
#include "filters.h"
#include "fixmath.h"
#include "interpolation.h"
#include "Ap_EOTActuatorMng_Cfg.h"
 
#define D_HWPOSAUTHHILMT_ULS_F32    (1.0F)
#define D_ONE_ULS_U16               ((uint16)1U)
#define D_MINUSONE_ULS_S16          ((sint16)-1)
#define D_MINUSONE_ULS_F32          (-1.0F)
#define D_2MSLPFKN5HZ_CNT_U16       ((uint16)3991U)

#define D_SESSTATE_PRI1_ULS_U16     ((uint16)0x01U)
#define D_SESSTATE_PRI2_ULS_U16     ((uint16)0x02U)
#define D_SESSTATE_PRI3_ULS_U16     ((uint16)0x04U)
#define D_SESSTATE_PRI4_ULS_U16     ((uint16)0x08U)

#define D_EOTDAMPHILMT_MTRNM_F32    (8.8F)
#define D_EOTDAMPLOLMT_MTRNM_F32    (-8.8F)

#define D_EOTGAINHILMT_ULS_F32      (1.0F)
#define D_EOTGAINLOLMT_ULS_F32      (0.0F)

#define D_EOTHILMT_MTRNM_F32        (8.8F)
#define D_EOTLOLMT_MTRNM_F32        (0.0F)

enum sesState {
    SES_DISABLED    = 0u,
    SES_NORMAL      = 1u,
    SES_ENTERING    = 2u,
    SES_EXITING     = 3u
};

typedef enum sesState sesState_T;


STATIC FUNC(boolean, AUTOMATIC) EOTDetermination( VAR(boolean, AUTOMATIC) CwFound_Cnt_T_lgc, VAR(boolean, AUTOMATIC) CcwFound_Cnt_T_lgc);

STATIC FUNC(float32, AUTOMATIC) EOTOrigImpact( VAR(float32, AUTOMATIC) CwEOT_HwDeg_T_f32, VAR(float32, AUTOMATIC) CcwEOT_HwDeg_T_f32,
                                               VAR(float32, AUTOMATIC) HandWheelAuth_Uls_T_f32, VAR(float32, AUTOMATIC) MotorVel_MtrRadpS_T_f32,
                                               VAR(float32, AUTOMATIC) HandWheelPos_HwDeg_T_f32, VAR(float32, AUTOMATIC) VehicleSpeed_Kph_T_f32);

STATIC FUNC(float32, AUTOMATIC) SES_DetLmtPos( VAR(float32, AUTOMATIC) CwEOT_HwDeg_T_f32, VAR(float32, AUTOMATIC) CcwEOT_HwDeg_T_f32, VAR(float32, AUTOMATIC) HandWheelPos_HwDeg_T_f32 );

STATIC FUNC(float32, AUTOMATIC) SES_CalcExitGain( VAR(float32, AUTOMATIC) HandWheelPos_HwDeg_T_f32, VAR(float32, AUTOMATIC) HwTorque_HwNm_T_f32,
                                                  VAR(float32, AUTOMATIC) PrevEOTGain_Uls_T_f32, CONSTP2VAR(float32, AUTOMATIC, AUTOMATIC) FiltHwTrqPtr_HwNm_T_f32);
                                                    
STATIC FUNC(void, AUTOMATIC) SES_StateCtrl( VAR(float32, AUTOMATIC) FiltHwTrq_HwNm_T_f32, VAR(float32, AUTOMATIC) LimitPosition_HwDeg_T_f32,
                                            VAR(float32, AUTOMATIC) HandWheelPos_HwDeg_T_f32, VAR(float32, AUTOMATIC) HandWheelAuth_Uls_T_f32,
                                            VAR(float32, AUTOMATIC) VehicleSpeed_Kph_T_f32, VAR(boolean, AUTOMATIC) EOTDet_Cnt_T_lgc,
                                            VAR(boolean, AUTOMATIC) EOTDisable_Cnt_T_lgc);

STATIC FUNC(float32, AUTOMATIC) SES_CalcEnterGain( VAR(float32, AUTOMATIC) HandWheelPos_HwDeg_T_f32, VAR(float32, AUTOMATIC) LimitPosition_HwDeg_T_f32, VAR(float32, AUTOMATIC) VehicleSpeed_Kph_T_f32);
        
STATIC FUNC(float32, AUTOMATIC) SES_CalcEOTGain( VAR(float32, AUTOMATIC) EOTEnterGain_Uls_T_f32, VAR(float32, AUTOMATIC) EOTExitGain_Uls_T_f32);

STATIC FUNC(float32, AUTOMATIC) SES_FiltEOTGain( VAR(float32, AUTOMATIC) EOTGain_Uls_T_f32);

STATIC FUNC(float32, AUTOMATIC) SES_CalcEOTDamp( VAR(float32, AUTOMATIC) CwEOT_HwDeg_T_f32, VAR(float32, AUTOMATIC) CcwEOT_HwDeg_T_f32,
                                                 VAR(float32, AUTOMATIC) VehicleSpeed_Kph_T_f32, VAR(float32, AUTOMATIC) HandWheelPos_HwDeg_T_f32,
                                                 VAR(float32, AUTOMATIC) MotorVel_MtrRadpS_T_f32);

STATIC CONST(uint16, AUTOMATIC) t_TrqTblY_Uls_u2p14[2] = {FPM_InitFixedPoint_m(0.0, u2p14_T), FPM_InitFixedPoint_m(1.0, u2p14_T)};

#define EOTACTUATORMNG_START_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */
/* Module variables */ 
STATIC VAR(float32, AUTOMATIC) EOTActuatorMng_EOTImpactPos_HwDeg_M_f32;
STATIC VAR(float32, AUTOMATIC) EOTActuatorMng_PrevEOTGain_Uls_M_f32; 
STATIC VAR(sint32, AUTOMATIC) EOTActuatorMng_FiltHWTrqSV_HwNm_M_s7p24;
STATIC VAR(uint32, AUTOMATIC) EOTActuatorMng_FiltEOTGainSV_HwNm_M_u1p31;
STATIC VAR(float32, AUTOMATIC) EOTActuatorMng_Damping_MtrNm_M_f32;
STATIC VAR(float32, AUTOMATIC) EOTActuatorMng_OutputRampMultLtd_M_f32;

/* Display variables */
STATIC volatile VAR(float32, AUTOMATIC) EOTActuatorMng_EOTImpact_HwDeg_D_f32;
STATIC volatile VAR(float32, AUTOMATIC) EOTActuatorMng_LimitPosition_HwDeg_D_f32;
STATIC volatile VAR(float32, AUTOMATIC) EOTActuatorMng_EOTEnterGain_Uls_D_f32;
STATIC volatile VAR(float32, AUTOMATIC) EOTActuatorMng_EOTExitgain_Uls_D_f32;
STATIC volatile VAR(float32, AUTOMATIC) EOTActuatorMng_EOTGain_Uls_D_f32;
STATIC volatile VAR(float32, AUTOMATIC) EOTActuatorMng_FiltEOTGain_Uls_D_f32;
STATIC volatile VAR(float32, AUTOMATIC) EOTActuatorMng_EOTDamping_MtrNm_D_f32;
#define EOTACTUATORMNG_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */

#define EOTACTUATORMNG_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h" /* PRQA S 5087 */
STATIC volatile VAR(boolean, AUTOMATIC) EOTActuatorMng_EOTDet_Cnt_D_lgc;
#define EOTACTUATORMNG_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h" /* PRQA S 5087 */

#define EOTACTUATORMNG_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(sesState_T, AUTOMATIC) EOTActuatorMng_SESState_Uls_M_enum;
#define EOTACTUATORMNG_STOP_SEC_VAR_CLEARED_UNSPECIFIED
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
 * Float: Real in interval ]-FLT_MAX...FLT_MAX[ with single precision (standard type)
 * UInt16: Integer in interval [0...65535] (standard type)
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
 * Float: D_2MS_SEC_F32 = 0.002
 * Float: D_MTRTRQCMDHILMT_MTRNM_F32 = 8.8
 * Float: D_ONE_ULS_F32 = 1
 * Float: D_ZERO_ULS_F32 = 0
 * UInt16: D_ZERO_CNT_U16 = 0u
 *
 *********************************************************************************************************************/


#define RTE_START_SEC_AP_EOTACTUATORMNG_APPL_CODE
#include "MemMap.h"  /* PRQA S 5087 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: EOTActuatorMng_Per1
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
 *   Float Rte_IRead_EOTActuatorMng_Per1_CcwEOT_HwDeg_f32(void)
 *   Boolean Rte_IRead_EOTActuatorMng_Per1_CcwFound_Cnt_lgc(void)
 *   Float Rte_IRead_EOTActuatorMng_Per1_CwEOT_HwDeg_f32(void)
 *   Boolean Rte_IRead_EOTActuatorMng_Per1_CwFound_Cnt_lgc(void)
 *   Boolean Rte_IRead_EOTActuatorMng_Per1_EOTDisable_Cnt_lgc(void)
 *   Float Rte_IRead_EOTActuatorMng_Per1_HandWheelAuth_Uls_f32(void)
 *   Float Rte_IRead_EOTActuatorMng_Per1_HandWheelPos_HwDeg_f32(void)
 *   Float Rte_IRead_EOTActuatorMng_Per1_HwTorque_HwNm_f32(void)
 *   Float Rte_IRead_EOTActuatorMng_Per1_MotorVel_MtrRadpS_f32(void)
 *   Float Rte_IRead_EOTActuatorMng_Per1_OutputRampMultLtd_Uls_f32(void)
 *   Float Rte_IRead_EOTActuatorMng_Per1_PreLimitTorque_MtrNm_f32(void)
 *   Float Rte_IRead_EOTActuatorMng_Per1_VehicleSpeed_Kph_f32(void)
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_EOTActuatorMng_Per1_AssistEOTDamping_MtrNm_f32(Float data)
 *   Float *Rte_IWriteRef_EOTActuatorMng_Per1_AssistEOTDamping_MtrNm_f32(void)
 *   void Rte_IWrite_EOTActuatorMng_Per1_AssistEOTGain_Uls_f32(Float data)
 *   Float *Rte_IWriteRef_EOTActuatorMng_Per1_AssistEOTGain_Uls_f32(void)
 *   void Rte_IWrite_EOTActuatorMng_Per1_AssistEOTLimit_MtrNm_f32(Float data)
 *   Float *Rte_IWriteRef_EOTActuatorMng_Per1_AssistEOTLimit_MtrNm_f32(void)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_EOTACTUATORMNG_APPL_CODE) EOTActuatorMng_Per1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: EOTActuatorMng_Per1
 *********************************************************************************************************************/

    /* Input variables */
    VAR(float32, AUTOMATIC) HwTorque_HwNm_T_f32;
    VAR(float32, AUTOMATIC) CwEOT_HwDeg_T_f32;
    VAR(float32, AUTOMATIC) CcwEOT_HwDeg_T_f32;
    VAR(boolean, AUTOMATIC) CwFound_Cnt_T_lgc;
    VAR(boolean, AUTOMATIC) CcwFound_Cnt_T_lgc;
    VAR(float32, AUTOMATIC) HandWheelPos_HwDeg_T_f32;
    VAR(float32, AUTOMATIC) HandWheelAuth_Uls_T_f32;
    VAR(float32, AUTOMATIC) MotorVel_MtrRadpS_T_f32;
    VAR(float32, AUTOMATIC) VehicleSpeed_Kph_T_f32;
    VAR(boolean, AUTOMATIC) EOTDisable_Cnt_T_lgc;
    
    
    /* Output variables */
    VAR(float32, AUTOMATIC) AssistEOTLimit_MtrNm_T_f32;
    VAR(float32, AUTOMATIC) AssistEOTGain_Uls_T_f32;
    VAR(float32, AUTOMATIC) AssistEOTDamping_MtrNm_T_f32;
    
    /* local variables */
    VAR(boolean, AUTOMATIC) EOTDet_Cnt_T_lgc;
    VAR(float32, AUTOMATIC) LimitPosition_HwDeg_T_f32;
    VAR(float32, AUTOMATIC) FiltHwTrq_HwNm_T_f32;
    VAR(float32, AUTOMATIC) EOTExitGain_Uls_T_f32;
    VAR(float32, AUTOMATIC) EOTEnterGain_Uls_T_f32;
    VAR(float32, AUTOMATIC) EOTGain_Uls_T_f32;
    VAR(float32, AUTOMATIC) FiltEOTGain_Uls_T_f32;
    VAR(float32, AUTOMATIC) EOTDamping_MtrNm_T_f32;
    VAR(boolean, AUTOMATIC) EOTOriginalImpactandSoftEnd_Cnt_T_lgc;
    
    /* Configurable Start of Runnable Checkpoint */
    Rte_Call_EOTActuatorMng_Per1_CP0_CheckpointReached();


    /* Read input values */
    HwTorque_HwNm_T_f32 = Rte_IRead_EOTActuatorMng_Per1_HwTorque_HwNm_f32();
    CwEOT_HwDeg_T_f32 = Rte_IRead_EOTActuatorMng_Per1_CwEOT_HwDeg_f32();
    CcwEOT_HwDeg_T_f32 = Rte_IRead_EOTActuatorMng_Per1_CcwEOT_HwDeg_f32();
    CwFound_Cnt_T_lgc = Rte_IRead_EOTActuatorMng_Per1_CwFound_Cnt_lgc();
    CcwFound_Cnt_T_lgc = Rte_IRead_EOTActuatorMng_Per1_CcwFound_Cnt_lgc();
    HandWheelPos_HwDeg_T_f32 = Rte_IRead_EOTActuatorMng_Per1_HandWheelPos_HwDeg_f32();
    HandWheelAuth_Uls_T_f32 = Rte_IRead_EOTActuatorMng_Per1_HandWheelAuth_Uls_f32(); 
    MotorVel_MtrRadpS_T_f32 = Rte_IRead_EOTActuatorMng_Per1_MotorVel_MtrRadpS_f32();
    VehicleSpeed_Kph_T_f32 = Rte_IRead_EOTActuatorMng_Per1_VehicleSpeed_Kph_f32();
    EOTDisable_Cnt_T_lgc = Rte_IRead_EOTActuatorMng_Per1_EOTDisable_Cnt_lgc();
    EOTActuatorMng_OutputRampMultLtd_M_f32 = Rte_IRead_EOTActuatorMng_Per1_OutputRampMultLtd_Uls_f32();

    EOTDet_Cnt_T_lgc = EOTDetermination(CwFound_Cnt_T_lgc, CcwFound_Cnt_T_lgc);
    
    if ((EOTDet_Cnt_T_lgc == TRUE) && (k_EOTOriginalImpactandSoftEnd_Cnt_lgc==FALSE))
    {
        EOTOriginalImpactandSoftEnd_Cnt_T_lgc= TRUE;
    }
    else
    {
        EOTOriginalImpactandSoftEnd_Cnt_T_lgc= FALSE;
    }

    if((EOTOriginalImpactandSoftEnd_Cnt_T_lgc == TRUE) || (TRUE == EOTDisable_Cnt_T_lgc))
    {
        AssistEOTLimit_MtrNm_T_f32 = D_MTRTRQCMDHILMT_MTRNM_F32;        
    }
    else
    {
        AssistEOTLimit_MtrNm_T_f32 = EOTOrigImpact(CwEOT_HwDeg_T_f32, CcwEOT_HwDeg_T_f32, HandWheelAuth_Uls_T_f32, 
                                                   MotorVel_MtrRadpS_T_f32, HandWheelPos_HwDeg_T_f32, VehicleSpeed_Kph_T_f32);
    }
    
    /* Soft End Stops */
    LimitPosition_HwDeg_T_f32 = SES_DetLmtPos( CwEOT_HwDeg_T_f32, CcwEOT_HwDeg_T_f32, HandWheelPos_HwDeg_T_f32 );
    EOTExitGain_Uls_T_f32 = SES_CalcExitGain( HandWheelPos_HwDeg_T_f32, HwTorque_HwNm_T_f32, EOTActuatorMng_PrevEOTGain_Uls_M_f32, &FiltHwTrq_HwNm_T_f32);
    EOTEnterGain_Uls_T_f32 = SES_CalcEnterGain( HandWheelPos_HwDeg_T_f32, LimitPosition_HwDeg_T_f32, VehicleSpeed_Kph_T_f32);
    EOTGain_Uls_T_f32 = SES_CalcEOTGain(EOTEnterGain_Uls_T_f32, EOTExitGain_Uls_T_f32);
    FiltEOTGain_Uls_T_f32 = SES_FiltEOTGain(EOTGain_Uls_T_f32);
    EOTDamping_MtrNm_T_f32 = SES_CalcEOTDamp(CwEOT_HwDeg_T_f32, CcwEOT_HwDeg_T_f32, VehicleSpeed_Kph_T_f32, HandWheelPos_HwDeg_T_f32, MotorVel_MtrRadpS_T_f32);
    
    if(EOTActuatorMng_SESState_Uls_M_enum == SES_DISABLED)
    {
        AssistEOTDamping_MtrNm_T_f32 = D_ZERO_ULS_F32;
        AssistEOTGain_Uls_T_f32 = D_ONE_ULS_F32;
    }
    else
    {
        AssistEOTDamping_MtrNm_T_f32 = EOTDamping_MtrNm_T_f32;
        AssistEOTGain_Uls_T_f32 = FiltEOTGain_Uls_T_f32;
    }
    
    /* Update EOT state for next run */ 
    SES_StateCtrl( FiltHwTrq_HwNm_T_f32, LimitPosition_HwDeg_T_f32, HandWheelPos_HwDeg_T_f32,
        HandWheelAuth_Uls_T_f32, VehicleSpeed_Kph_T_f32, EOTDet_Cnt_T_lgc, EOTDisable_Cnt_T_lgc);
     
    /* limit output */
    AssistEOTDamping_MtrNm_T_f32 = Limit_m(AssistEOTDamping_MtrNm_T_f32, D_EOTDAMPLOLMT_MTRNM_F32, D_EOTDAMPHILMT_MTRNM_F32);
    AssistEOTGain_Uls_T_f32 = Limit_m(AssistEOTGain_Uls_T_f32, D_EOTGAINLOLMT_ULS_F32, D_EOTGAINHILMT_ULS_F32);
    AssistEOTLimit_MtrNm_T_f32 = Limit_m(AssistEOTLimit_MtrNm_T_f32, D_EOTLOLMT_MTRNM_F32, D_EOTHILMT_MTRNM_F32);
    
    EOTActuatorMng_PrevEOTGain_Uls_M_f32 = AssistEOTGain_Uls_T_f32;
    
    /* Write output values */
    Rte_IWrite_EOTActuatorMng_Per1_AssistEOTDamping_MtrNm_f32(AssistEOTDamping_MtrNm_T_f32);
    Rte_IWrite_EOTActuatorMng_Per1_AssistEOTGain_Uls_f32(AssistEOTGain_Uls_T_f32);
     Rte_IWrite_EOTActuatorMng_Per1_AssistEOTLimit_MtrNm_f32(AssistEOTLimit_MtrNm_T_f32);

    /* Configurable End of Runnable Checkpoint */
    Rte_Call_EOTActuatorMng_Per1_CP1_CheckpointReached();
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define RTE_STOP_SEC_AP_EOTACTUATORMNG_APPL_CODE
#include "MemMap.h"  /* PRQA S 5087 */


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of function definition area >>            DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * Function: EOTDetermination
 * Inputs: boolean CwFound_Cnt_T_lgc, boolean CcwFound_Cnt_T_lgc
 * Outputs: boolean EOTDet_Cnt_T_lgc
 *********************************************************************************************************************/ 
STATIC FUNC(boolean, AUTOMATIC) EOTDetermination( VAR(boolean, AUTOMATIC) CwFound_Cnt_T_lgc, VAR(boolean, AUTOMATIC) CcwFound_Cnt_T_lgc)
{
    VAR(boolean, AUTOMATIC) EOTDet_Cnt_T_lgc;
    
    if ( (CwFound_Cnt_T_lgc & CcwFound_Cnt_T_lgc & k_SoftStopEOTEnable_Cnt_lgc) == TRUE )
    {
        EOTDet_Cnt_T_lgc = TRUE;
    }
    else
    {
        EOTDet_Cnt_T_lgc = FALSE;
    }
    
    /* Update display variable */
    EOTActuatorMng_EOTDet_Cnt_D_lgc = EOTDet_Cnt_T_lgc;
    
    return(EOTDet_Cnt_T_lgc);
}

/**********************************************************************************************************************
 * Function: EOTDetermination
 * Inputs:     float32 CwEOT_HwDeg_T_f32, float32 CcwEOT_HwDeg_T_f32, float32 HandWheelAuth_Uls_T_f32, 
 *             float32 MotorVel_MtrRadpS_T_f32, float32 HandWheelPos_HwDeg_T_f32, float32 VehicleSpeed_Kph_T_f32
 * 
 * Outputs: float32 AssistEOTLimit_MtrNm_T_f32
 *********************************************************************************************************************/
STATIC FUNC(float32, AUTOMATIC) EOTOrigImpact( VAR(float32, AUTOMATIC) CwEOT_HwDeg_T_f32, VAR(float32, AUTOMATIC) CcwEOT_HwDeg_T_f32, 
                                               VAR(float32, AUTOMATIC) HandWheelAuth_Uls_T_f32, VAR(float32, AUTOMATIC) MotorVel_MtrRadpS_T_f32, 
                                               VAR(float32, AUTOMATIC) HandWheelPos_HwDeg_T_f32, VAR(float32, AUTOMATIC) VehicleSpeed_Kph_T_f32)
{
    /* outputs */
    VAR(float32, AUTOMATIC) AssistEOTLimit_MtrNm_T_f32;

    /* local variables  */
    VAR(float32, AUTOMATIC) AbsHandWheelPos_HwDeg_T_f32;
    VAR(float32, AUTOMATIC) AbsMotorVel_MtrRadpS_T_f32; 
    VAR(float32, AUTOMATIC) HwPosDiff_HwDeg_T_f32;
    VAR(uint16, AUTOMATIC) t_SpdIptTblX_HwDeg_T_u12p4[2];
    VAR(sint16, AUTOMATIC) CcwEOT_HwDeg_T_s11p4;
    VAR(uint16, AUTOMATIC) CwEOT_HwDeg_T_u12p4;
    VAR(uint16, AUTOMATIC) SpdIntcpt_MtrRadpS_T_u12p4;
    VAR(uint16, AUTOMATIC) EOTImpactPos_HwDeg_T_u12p4;
    VAR(float32, AUTOMATIC) DeltaAstEOTLmt_MtrRadpS_T_f32;
    
    AbsHandWheelPos_HwDeg_T_f32 = Abs_f32_m(HandWheelPos_HwDeg_T_f32);
    AbsMotorVel_MtrRadpS_T_f32 = Abs_f32_m(MotorVel_MtrRadpS_T_f32);
    
    if(HandWheelAuth_Uls_T_f32 < D_HWPOSAUTHHILMT_ULS_F32)
    {
        EOTActuatorMng_EOTImpactPos_HwDeg_M_f32 = FPM_FixedToFloat_m(k_EOTDefltPosition_HwDeg_u12p4, u12p4_T);
    }
    else 
    {
        HwPosDiff_HwDeg_T_f32 = AbsHandWheelPos_HwDeg_T_f32 - EOTActuatorMng_EOTImpactPos_HwDeg_M_f32;
        if (Abs_f32_m(HwPosDiff_HwDeg_T_f32) > FPM_FixedToFloat_m(k_PosRampStep_HwDeg_u12p4, u12p4_T))
        {
            EOTActuatorMng_EOTImpactPos_HwDeg_M_f32 += ((FPM_FixedToFloat_m(k_PosRampStep_HwDeg_u12p4, u12p4_T) * (float32)Sign_f32_m(HwPosDiff_HwDeg_T_f32)));
        }
        else
        {
            EOTActuatorMng_EOTImpactPos_HwDeg_M_f32 = AbsHandWheelPos_HwDeg_T_f32;
        }
    }    
        
    /* update display variable */
    EOTActuatorMng_EOTImpact_HwDeg_D_f32 = EOTActuatorMng_EOTImpactPos_HwDeg_M_f32;
        
    if( HandWheelPos_HwDeg_T_f32 < D_ZERO_ULS_F32 )
    {
        /* Ccw EOT */
        CcwEOT_HwDeg_T_s11p4 = FPM_FloatToFixed_m(CcwEOT_HwDeg_T_f32, s11p4_T);
        t_SpdIptTblX_HwDeg_T_u12p4[0] = Abs_s16_m(CcwEOT_HwDeg_T_s11p4 + (sint16)t_SpdIptTblXTbl_HwDeg_u12p4[0]);
        t_SpdIptTblX_HwDeg_T_u12p4[1] = Abs_s16_m(CcwEOT_HwDeg_T_s11p4 + (sint16)t_SpdIptTblXTbl_HwDeg_u12p4[1]);
    }
    else
    {
        /* Cw EOT */
        CwEOT_HwDeg_T_u12p4 = FPM_FloatToFixed_m(CwEOT_HwDeg_T_f32, u12p4_T);
        t_SpdIptTblX_HwDeg_T_u12p4[0] = CwEOT_HwDeg_T_u12p4 - t_SpdIptTblXTbl_HwDeg_u12p4[0];
        t_SpdIptTblX_HwDeg_T_u12p4[1] = CwEOT_HwDeg_T_u12p4 - t_SpdIptTblXTbl_HwDeg_u12p4[1];
    }
    
    EOTImpactPos_HwDeg_T_u12p4 = FPM_FloatToFixed_m(EOTActuatorMng_EOTImpactPos_HwDeg_M_f32, u12p4_T);
    SpdIntcpt_MtrRadpS_T_u12p4 = IntplVarXY_u16_u16Xu16Y_Cnt( t_SpdIptTblX_HwDeg_T_u12p4, 
                                                              t_SpdIptTblYTbl_MtrRadpS_u12p4, 
                                                              (uint16)TableSize_m(t_SpdIptTblX_HwDeg_T_u12p4), 
                                                              EOTImpactPos_HwDeg_T_u12p4);
    
    DeltaAstEOTLmt_MtrRadpS_T_f32 = FPM_FixedToFloat_m(SpdIntcpt_MtrRadpS_T_u12p4, u12p4_T) - AbsMotorVel_MtrRadpS_T_f32;    

    if (DeltaAstEOTLmt_MtrRadpS_T_f32 < D_ZERO_ULS_F32)
    {
        AssistEOTLimit_MtrNm_T_f32 = D_ZERO_ULS_F32;
    }
    else
    {
        AssistEOTLimit_MtrNm_T_f32 = DeltaAstEOTLmt_MtrRadpS_T_f32 * FPM_FixedToFloat_m(k_SpdIptScale_MtrNmpRadpS_u4p12, u4p12_T);
    }
    if ( VehicleSpeed_Kph_T_f32 > FPM_FixedToFloat_m(k_EOTImpSpdEn_Kph_u9p7, u9p7_T))
    {
        AssistEOTLimit_MtrNm_T_f32 = D_MTRTRQCMDHILMT_MTRNM_F32;
    }

    return (AssistEOTLimit_MtrNm_T_f32);
}

/**********************************************************************************************************************
 * Function: SES_DetLmtPos
 * Inputs:     float32 CwEOT_HwDeg_T_f32, float32 CcwEOT_HwDeg_T_f32, HandWheelPos_HwDeg_T_f32
 * 
 * Outputs: float32 LimitPos_HwDeg_T_f32
 *********************************************************************************************************************/
STATIC FUNC(float32, AUTOMATIC) SES_DetLmtPos(VAR(float32, AUTOMATIC) CwEOT_HwDeg_T_f32, VAR(float32, AUTOMATIC) CcwEOT_HwDeg_T_f32, VAR(float32, AUTOMATIC) HandWheelPos_HwDeg_T_f32 )
{
    /* output variables */
    VAR(float32, AUTOMATIC) LimitPos_HwDeg_T_f32;
    
    /* local variables */
    VAR(sint16, AUTOMATIC) CcwEOT_HwDeg_T_s11p4;
    VAR(uint16, AUTOMATIC) CwEOT_HwDeg_T_u12p4;
    VAR(sint16, AUTOMATIC) NegMaxRackTrvl_HwDeg_T_s11p4;
    VAR(sint16, AUTOMATIC) NegMinRackTrvl_HwDeg_T_s11p4;
    

    if (HandWheelPos_HwDeg_T_f32 < D_ZERO_ULS_F32)
    {
        /* Ccw */
        CcwEOT_HwDeg_T_s11p4 = FPM_FloatToFixed_m(CcwEOT_HwDeg_T_f32, s11p4_T);
        NegMaxRackTrvl_HwDeg_T_s11p4 = (sint16)(D_MINUSONE_ULS_S16 * (sint16)k_MaxRackTrvl_HwDeg_u12p4);
        NegMinRackTrvl_HwDeg_T_s11p4 = (sint16)(D_MINUSONE_ULS_S16 * (sint16)k_MinRackTrvl_HwDeg_u12p4);
        
        if ( (CcwEOT_HwDeg_T_s11p4 < NegMaxRackTrvl_HwDeg_T_s11p4) || (CcwEOT_HwDeg_T_s11p4 > NegMinRackTrvl_HwDeg_T_s11p4) )
        {
            LimitPos_HwDeg_T_f32 = FPM_FixedToFloat_m(NegMinRackTrvl_HwDeg_T_s11p4, s11p4_T);
        }
        else
        {
            LimitPos_HwDeg_T_f32 = CcwEOT_HwDeg_T_f32;
        }
    }
    else
    {
        /* Cw */
        CwEOT_HwDeg_T_u12p4 = FPM_FloatToFixed_m(CwEOT_HwDeg_T_f32, u12p4_T);
        
        if ( (CwEOT_HwDeg_T_u12p4 < k_MinRackTrvl_HwDeg_u12p4) || (CwEOT_HwDeg_T_u12p4 > k_MaxRackTrvl_HwDeg_u12p4) )
        {
            LimitPos_HwDeg_T_f32 = FPM_FixedToFloat_m(k_MinRackTrvl_HwDeg_u12p4, u12p4_T);
        }
        else
        {
            LimitPos_HwDeg_T_f32 = CwEOT_HwDeg_T_f32;
        }        
    }
    
    EOTActuatorMng_LimitPosition_HwDeg_D_f32 = LimitPos_HwDeg_T_f32;

    return(LimitPos_HwDeg_T_f32);
}

/**********************************************************************************************************************
 * Function: SES_CalcExitGain
 * Inputs:     float32 HandWheelPos_HwDeg_T_f32, float32 HwTorque_HwNm_T_f32, float32 PrevEOTGain_Uls_T_f32
 * 
 * Outputs: float32 EOTExitGain_Uls_T_f32
 *********************************************************************************************************************/
STATIC FUNC(float32, AUTOMATIC) SES_CalcExitGain(     VAR(float32, AUTOMATIC) HandWheelPos_HwDeg_T_f32, VAR(float32, AUTOMATIC) HwTorque_HwNm_T_f32, 
                                                    VAR(float32, AUTOMATIC) PrevEOTGain_Uls_T_f32, CONSTP2VAR(float32, AUTOMATIC, AUTOMATIC) FiltHwTrqPtr_HwNm_T_f32)
{
    /* output variables */
    VAR(float32, AUTOMATIC) EOTExitGain_Uls_T_f32;
    
    /* local variables */
    VAR(uint16, AUTOMATIC) AbsHwTorque_HwNm_T_u8p8;
    VAR(sint16, AUTOMATIC) HwTorque_HwNm_T_s7p8;
    VAR(sint16, AUTOMATIC) FiltHwTorque_HwNm_T_s7p8;
    VAR(float32, AUTOMATIC) LUTGain_Uls_T_f32;
    
    
    AbsHwTorque_HwNm_T_u8p8 = FPM_FloatToFixed_m(Abs_f32_m(HwTorque_HwNm_T_f32), u8p8_T);
    HwTorque_HwNm_T_s7p8 = FPM_FloatToFixed_m(HwTorque_HwNm_T_f32, s7p8_T);
    
    if( HandWheelPos_HwDeg_T_f32 < D_ZERO_ULS_F32)
    {
        HwTorque_HwNm_T_s7p8 *= D_MINUSONE_ULS_S16;
    }
    
    EOTActuatorMng_FiltHWTrqSV_HwNm_M_s7p24 = LPF_SvUpdate_s16InFixKTrunc_m( HwTorque_HwNm_T_s7p8, 
                                                                             EOTActuatorMng_FiltHWTrqSV_HwNm_M_s7p24, 
                                                                             k_EOTStateHwTrqLPFKn_Cnt_u16);

    FiltHwTorque_HwNm_T_s7p8 = LPF_OpUpdate_s16InFixKTrunc_m(EOTActuatorMng_FiltHWTrqSV_HwNm_M_s7p24);
    *FiltHwTrqPtr_HwNm_T_f32 = FPM_FixedToFloat_m(FiltHwTorque_HwNm_T_s7p8, s7p8_T);


    LUTGain_Uls_T_f32 = FPM_FixedToFloat_m(IntplVarXY_u16_u16Xu16Y_Cnt( t_TrqTableX_HwNm_u8p8, 
                                                                        t_TrqTblY_Uls_u2p14, 
                                                                        (uint16)TableSize_m(t_TrqTableX_HwNm_u8p8), 
                                                                        AbsHwTorque_HwNm_T_u8p8), u2p14_T);

    EOTExitGain_Uls_T_f32 = Max_m(LUTGain_Uls_T_f32, PrevEOTGain_Uls_T_f32);

    EOTActuatorMng_EOTExitgain_Uls_D_f32 = EOTExitGain_Uls_T_f32;

    return(EOTExitGain_Uls_T_f32);
}

/**********************************************************************************************************************
 * Function: SES_CalcExitGain
 * Inputs:     float32 FiltHwTrq_HwNm_T_f32, float32 LimitPosition_HwDeg_T_f32, float32 HandWheelPos_HwDeg_T_f32,
 *             float32 HandWheelAuth_Uls_T_f32, float32 VehicleSpeed_Kph_T_f32, boolean EOTDet_Cnt_T_lgc,
 *             boolean EOTDisable_Cnt_T_lgc
 * 
 * Outputs: None: updates module variable. 
 *********************************************************************************************************************/
STATIC FUNC(void, AUTOMATIC) SES_StateCtrl( VAR(float32, AUTOMATIC) FiltHwTrq_HwNm_T_f32, VAR(float32, AUTOMATIC) LimitPosition_HwDeg_T_f32,
                                            VAR(float32, AUTOMATIC) HandWheelPos_HwDeg_T_f32, VAR(float32, AUTOMATIC) HandWheelAuth_Uls_T_f32,
                                            VAR(float32, AUTOMATIC) VehicleSpeed_Kph_T_f32, VAR(boolean, AUTOMATIC) EOTDet_Cnt_T_lgc,
                                            VAR(boolean, AUTOMATIC) EOTDisable_Cnt_T_lgc)
{
    VAR(uint16, AUTOMATIC) StatePriVectRes_Uls_T_u16;
    VAR(sesState_T, AUTOMATIC) SESNextState_Uls_T_enum;
    VAR(float32, AUTOMATIC) EOTDeltaTrqThrsh_HwNm_T_f32;
    
    VAR(uint16, AUTOMATIC) idx_Uls_T_u16;
    VAR(uint16, AUTOMATIC) t_EOTEnterGainTmpTblY_HwDeg_T_u12p4[4];
    VAR(uint16, AUTOMATIC) t_EOTPosDepDampTmpTblY_HwDeg_T_u12p4[4];
    VAR(uint16, AUTOMATIC) VehicleSpeed_Kph_T_u9p7;
    VAR(uint16, AUTOMATIC) EOTEnterGainVal_HwDeg_T_u12p4;
    VAR(float32, AUTOMATIC) EOTEnterGainVal_HwDeg_T_f32;
    
    VAR(uint16, AUTOMATIC) EOTPosDepDampVal_HwDeg_T_u12p4;
    VAR(float32, AUTOMATIC) EOTPosDepDampVal_HwDeg_T_f32;

    StatePriVectRes_Uls_T_u16 = D_ZERO_CNT_U16;
    SESNextState_Uls_T_enum = EOTActuatorMng_SESState_Uls_M_enum;
    
    /* Vector Priority 1 */    
    if( (HandWheelAuth_Uls_T_f32 < FPM_FixedToFloat_m(k_EOTDynConf_Uls_u8p8, u8p8_T)) || 
        (VehicleSpeed_Kph_T_f32 >= FPM_FixedToFloat_m(k_EOTImpSpdEn_Kph_u9p7, u9p7_T)) || 
        (EOTDet_Cnt_T_lgc == FALSE) || 
        (EOTDisable_Cnt_T_lgc == TRUE))
    {
        StatePriVectRes_Uls_T_u16 |= D_SESSTATE_PRI1_ULS_U16;
    }
    else
    {
        /* Vector Priority 2 */
        for (idx_Uls_T_u16 = 0u; idx_Uls_T_u16 < 4u; idx_Uls_T_u16++)
        {
            t_EOTEnterGainTmpTblY_HwDeg_T_u12p4[idx_Uls_T_u16] = t2_EOTEnterGainX_HwDeg_u12p4[idx_Uls_T_u16][(uint16)(TableSize_m(t2_EOTEnterGainX_HwDeg_u12p4[0])-1U)];
            t_EOTPosDepDampTmpTblY_HwDeg_T_u12p4[idx_Uls_T_u16] = t2_EOTPosDepDmpTblX_HwDeg_u12p4[idx_Uls_T_u16][0];
        }
        
        VehicleSpeed_Kph_T_u9p7 = FPM_FloatToFixed_m(VehicleSpeed_Kph_T_f32, u9p7_T);
        
        EOTEnterGainVal_HwDeg_T_u12p4 = IntplVarXY_u16_u16Xu16Y_Cnt( t_EOTEnterGainVspd_Kph_u9p7, 
                                                                     t_EOTEnterGainTmpTblY_HwDeg_T_u12p4, 
                                                                     (uint16)TableSize_m(t_EOTEnterGainVspd_Kph_u9p7), 
                                                                     VehicleSpeed_Kph_T_u9p7);
        
        EOTEnterGainVal_HwDeg_T_f32 = FPM_FixedToFloat_m(EOTEnterGainVal_HwDeg_T_u12p4, u12p4_T);
        
        EOTPosDepDampVal_HwDeg_T_u12p4 = IntplVarXY_u16_u16Xu16Y_Cnt( t_EOTEnterGainVspd_Kph_u9p7, 
                                                                      t_EOTPosDepDampTmpTblY_HwDeg_T_u12p4, 
                                                                      (uint16)TableSize_m(t_EOTEnterGainVspd_Kph_u9p7), 
                                                                      VehicleSpeed_Kph_T_u9p7);    
        
        EOTPosDepDampVal_HwDeg_T_f32 = FPM_FixedToFloat_m(EOTPosDepDampVal_HwDeg_T_u12p4, u12p4_T);
        
        
        if( (( EOTActuatorMng_OutputRampMultLtd_M_f32 <= k_EOTActiveRegionBypassMaxThresh_Uls_f32) && (SESNextState_Uls_T_enum == SES_DISABLED)) || 
            (Abs_f32_m(HandWheelPos_HwDeg_T_f32) <= (Abs_f32_m(LimitPosition_HwDeg_T_f32) - Max_m(EOTEnterGainVal_HwDeg_T_f32, EOTPosDepDampVal_HwDeg_T_f32) )) )
        {
            StatePriVectRes_Uls_T_u16 |= D_SESSTATE_PRI2_ULS_U16;
        }
        else
        {
            EOTDeltaTrqThrsh_HwNm_T_f32 = FPM_FixedToFloat_m(k_EOTDeltaTrqThrsh_HwNm_u9p7, u9p7_T);
            
            /* Vector Priority 3 */
            /* The logic check for system state as shown in the FDD model are done in the switch statement below */
            if ( FiltHwTrq_HwNm_T_f32 > EOTDeltaTrqThrsh_HwNm_T_f32 )
            {
                StatePriVectRes_Uls_T_u16 |= D_SESSTATE_PRI3_ULS_U16;
            }
            else
            {
                /* Vector Priority 4 */
                /* The logic check for system state as shown in the FDD model are done in the switch statement below */
                if ( FiltHwTrq_HwNm_T_f32 < (D_MINUSONE_ULS_F32 * EOTDeltaTrqThrsh_HwNm_T_f32) )
                {
                    StatePriVectRes_Uls_T_u16 |= D_SESSTATE_PRI4_ULS_U16;
                }
            }    
        }
    }
    
    switch(StatePriVectRes_Uls_T_u16)
    {
        case D_SESSTATE_PRI1_ULS_U16:
            SESNextState_Uls_T_enum = SES_DISABLED;
            break;
        case D_SESSTATE_PRI2_ULS_U16:
            SESNextState_Uls_T_enum = SES_NORMAL;
            break;
        case D_SESSTATE_PRI3_ULS_U16:
            if(EOTActuatorMng_SESState_Uls_M_enum != SES_DISABLED)
            {
                SESNextState_Uls_T_enum = SES_ENTERING;
            }
            break;
        case D_SESSTATE_PRI4_ULS_U16:
            if(EOTActuatorMng_SESState_Uls_M_enum != SES_DISABLED)
            {
                SESNextState_Uls_T_enum = SES_EXITING;
            }
            break;
        default:
            break;
    }

    /* Update state variable */
    EOTActuatorMng_SESState_Uls_M_enum = SESNextState_Uls_T_enum;

    return;    
}

/**********************************************************************************************************************
 * Function: SES_CalcEnterGain
 * Inputs:     float32 HandWheelPos_HwDeg_T_f32, float32 LimitPosition_HwDeg_T_f32, float32 VehicleSpeed_Kph_T_f32,
 * 
 * Outputs: float32 EOTEnterGain_Uls_T_f32 
 *********************************************************************************************************************/
STATIC FUNC(float32, AUTOMATIC) SES_CalcEnterGain( VAR(float32, AUTOMATIC) HandWheelPos_HwDeg_T_f32, VAR(float32, AUTOMATIC) LimitPosition_HwDeg_T_f32, VAR(float32, AUTOMATIC) VehicleSpeed_Kph_T_f32)
{
    /* outputs */
    VAR(float32, AUTOMATIC) EOTEnterGain_Uls_T_f32;
    
    /* locals */
    VAR(float32, AUTOMATIC) AbsHwPos_HwDeg_T_f32;
    VAR(float32, AUTOMATIC) DeltaHwPos_HwDeg_T_f32;
    VAR(uint16, AUTOMATIC) EOTEnterGain_Uls_T_u1p15;
    VAR(uint16, AUTOMATIC) VehSpd_Kph_T_u9p7;
    VAR(uint16, AUTOMATIC) DeltaHwPos_HwDeg_T_u12p4;
    
    if( EOTActuatorMng_SESState_Uls_M_enum != SES_DISABLED)
    {
        AbsHwPos_HwDeg_T_f32 = Abs_f32_m(HandWheelPos_HwDeg_T_f32);
        DeltaHwPos_HwDeg_T_f32 = Abs_f32_m(LimitPosition_HwDeg_T_f32) - AbsHwPos_HwDeg_T_f32;    
        DeltaHwPos_HwDeg_T_f32 = Max_m(DeltaHwPos_HwDeg_T_f32, D_ZERO_ULS_F32);    
        
        VehSpd_Kph_T_u9p7 = FPM_FloatToFixed_m(VehicleSpeed_Kph_T_f32, u9p7_T);
        DeltaHwPos_HwDeg_T_u12p4 = FPM_FloatToFixed_m(DeltaHwPos_HwDeg_T_f32, u12p4_T);
        
        EOTEnterGain_Uls_T_u1p15 = BilinearXMYM_u16_u16XMu16YM_Cnt( VehSpd_Kph_T_u9p7, 
                                                                    DeltaHwPos_HwDeg_T_u12p4, 
                                                                    t_EOTEnterGainVspd_Kph_u9p7, 
                                                                    (uint16)TableSize_m(t_EOTEnterGainVspd_Kph_u9p7), 
                                                                    (P2CONST(uint16, AUTOMATIC, AUTOMATIC))t2_EOTEnterGainX_HwDeg_u12p4, 
                                                                    (P2CONST(uint16, AUTOMATIC, AUTOMATIC))t2_EOTEnterGainY_Uls_u1p15, 
                                                                    (uint16)TableSize_m(t2_EOTEnterGainX_HwDeg_u12p4[0]));
        
        EOTEnterGain_Uls_T_f32 = FPM_FixedToFloat_m(EOTEnterGain_Uls_T_u1p15, u1p15_T);
    }
    else
    {
        EOTEnterGain_Uls_T_f32 = D_ONE_ULS_F32;
    }
    
    EOTActuatorMng_EOTEnterGain_Uls_D_f32 = EOTEnterGain_Uls_T_f32;
    
    return (EOTEnterGain_Uls_T_f32);
}

/**********************************************************************************************************************
 * Function: SES_CalcEOTGain
 * Inputs:     float32 EOTEnterGain_Uls_T_f32, float32 EOTExitGain_Uls_T_f32
 * 
 * Outputs: float32 EOTGain_Uls_T_f32
 *********************************************************************************************************************/
STATIC FUNC(float32, AUTOMATIC) SES_CalcEOTGain( VAR(float32, AUTOMATIC) EOTEnterGain_Uls_T_f32, VAR(float32, AUTOMATIC) EOTExitGain_Uls_T_f32)
{
    /* outputs */
    VAR(float32, AUTOMATC) EOTGain_Uls_T_f32;
    
    /* locals */
    switch(EOTActuatorMng_SESState_Uls_M_enum)
    {
        case SES_DISABLED:
            EOTGain_Uls_T_f32 = D_ONE_ULS_F32;
            break;
        case SES_EXITING:
            EOTGain_Uls_T_f32 = EOTExitGain_Uls_T_f32;
            break;
        default:
            EOTGain_Uls_T_f32 = EOTEnterGain_Uls_T_f32;
            break;
    }
    
    /* Update Display */
    EOTActuatorMng_EOTGain_Uls_D_f32 = EOTGain_Uls_T_f32;
    
    return (EOTGain_Uls_T_f32);    
}

/**********************************************************************************************************************
 * Function: SES_FiltEOTGain
 * Inputs:     float32 EOTGain_Uls_T_f32
 * 
 * Outputs: float32 FiltEOTGain_Uls_T_f32
 *********************************************************************************************************************/
STATIC FUNC(float32, AUTOMATIC) SES_FiltEOTGain( VAR(float32, AUTOMATIC) EOTGain_Uls_T_f32)
{
    /* outputs */
    VAR(float32, AUTOMATIC) FiltEOTGain_Uls_T_f32;
    
    /* locals */ 
    VAR(uint16, AUTOMATIC) LPFKnVal_Cnt_T_u16;
    VAR(uint16, AUTOMATIC) FiltEOTGain_Uls_T_u1p15;
    VAR(uint16, AUTOMATIC) EOTGain_Uls_T_u1p15;
    
    switch(EOTActuatorMng_SESState_Uls_M_enum)
    {
        case SES_DISABLED:
            LPFKnVal_Cnt_T_u16 = D_2MSLPFKN5HZ_CNT_U16;
            break;
        case SES_EXITING:
            LPFKnVal_Cnt_T_u16 = k_EOTExitLPFKn_Cnt_u16;
            break;
        default:
            LPFKnVal_Cnt_T_u16 = k_EOTEnterLPFKn_Cnt_u16;
            break;
    }
    
    EOTGain_Uls_T_u1p15 = FPM_FloatToFixed_m(EOTGain_Uls_T_f32, u1p15_T);
    
    EOTActuatorMng_FiltEOTGainSV_HwNm_M_u1p31 = LPF_SvUpdate_u16InFixKTrunc_m( EOTGain_Uls_T_u1p15, 
                                                                               EOTActuatorMng_FiltEOTGainSV_HwNm_M_u1p31, 
                                                                               LPFKnVal_Cnt_T_u16);
                                                                      
    FiltEOTGain_Uls_T_u1p15 = (uint16)LPF_OpUpdate_u16InFixKTrunc_m(EOTActuatorMng_FiltEOTGainSV_HwNm_M_u1p31);
    FiltEOTGain_Uls_T_f32 = FPM_FixedToFloat_m(FiltEOTGain_Uls_T_u1p15, u1p15_T);

    EOTActuatorMng_FiltEOTGain_Uls_D_f32 = FiltEOTGain_Uls_T_f32;
    
    return(FiltEOTGain_Uls_T_f32);
}

/**********************************************************************************************************************
 * Function: SES_CalcEOTDamp
 * Inputs:     float32 CwEOT_HwDeg_T_f32, float32 CcwEOT_HwDeg_T_f32, float32 VehicleSpeed_Kph_T_f32, 
 *             float32 HandWheelPos_HwDeg_T_f32, float32 MotorVel_MtrRadpS_T_f32,
 * 
 * Outputs: float32 EOTDamping_MtrNm_T_f32
 *********************************************************************************************************************/
STATIC FUNC(float32, AUTOMATIC) SES_CalcEOTDamp( VAR(float32, AUTOMATIC) CwEOT_HwDeg_T_f32, VAR(float32, AUTOMATIC) CcwEOT_HwDeg_T_f32,
                                                 VAR(float32, AUTOMATIC) VehicleSpeed_Kph_T_f32, VAR(float32, AUTOMATIC) HandWheelPos_HwDeg_T_f32,
                                                 VAR(float32, AUTOMATIC) MotorVel_MtrRadpS_T_f32)
{
    /* output */
    VAR(float32, AUTOMATIC) EOTDamping_MtrNm_T_f32;
    
    /* local variables */
    VAR(uint16, AUTOMATIC) CwEOT_HwDeg_T_u12p4;
    VAR(sint16, AUTOMATIC) CcwEOT_HwDeg_T_s11p4;
    VAR(uint16, AUTOMATIC) t2_EOTPos_HwDeg_T_u12p4[4][2];
    VAR(uint16, AUTOMATIC) EOTDamping_MtrNmpRadpS_T_u0p16;
    VAR(uint16, AUTOMATIC) VehSpd_Kph_T_u9p7;
    VAR(uint16, AUTOMATIC) index_Uls_T_u16;
    VAR(float32, AUTOMATIC) EOTDamping_MtrNmpRadpS_T_f32;
    VAR(uint16, AUTOMATIC) HandWheelPos_HwDeg_T_u12p4;
    
    if (EOTActuatorMng_SESState_Uls_M_enum == SES_DISABLED)
    {
        EOTDamping_MtrNm_T_f32 = D_ZERO_ULS_F32;
    }
    else
    {
        if(HandWheelPos_HwDeg_T_f32 < D_ZERO_ULS_F32)
        {
            /* ccw */
            CcwEOT_HwDeg_T_s11p4 = FPM_FloatToFixed_m(CcwEOT_HwDeg_T_f32, s11p4_T);
            for(index_Uls_T_u16 = 0u; index_Uls_T_u16 < 4u; index_Uls_T_u16++)
            {
                t2_EOTPos_HwDeg_T_u12p4[index_Uls_T_u16][0] = Abs_s16_m((CcwEOT_HwDeg_T_s11p4 + (sint16)t2_EOTPosDepDmpTblX_HwDeg_u12p4[index_Uls_T_u16][0]));
                t2_EOTPos_HwDeg_T_u12p4[index_Uls_T_u16][1] = Abs_s16_m((CcwEOT_HwDeg_T_s11p4 + (sint16)t2_EOTPosDepDmpTblX_HwDeg_u12p4[index_Uls_T_u16][1]));
            }
        }
        else
        {
            /* cw */
            CwEOT_HwDeg_T_u12p4 = FPM_FloatToFixed_m(CwEOT_HwDeg_T_f32, u12p4_T);
            for(index_Uls_T_u16 = 0u; index_Uls_T_u16 < 4u; index_Uls_T_u16++)
            {
                t2_EOTPos_HwDeg_T_u12p4[index_Uls_T_u16][0] = CwEOT_HwDeg_T_u12p4 - t2_EOTPosDepDmpTblX_HwDeg_u12p4[index_Uls_T_u16][0];
                t2_EOTPos_HwDeg_T_u12p4[index_Uls_T_u16][1] = CwEOT_HwDeg_T_u12p4 - t2_EOTPosDepDmpTblX_HwDeg_u12p4[index_Uls_T_u16][1];
            }
        }
        
        VehSpd_Kph_T_u9p7 = FPM_FloatToFixed_m(VehicleSpeed_Kph_T_f32, u9p7_T);
        HandWheelPos_HwDeg_T_u12p4 = FPM_FloatToFixed_m(Abs_f32_m(HandWheelPos_HwDeg_T_f32), u12p4_T);
        if( EOTActuatorMng_SESState_Uls_M_enum == SES_EXITING )
        {
            EOTDamping_MtrNmpRadpS_T_u0p16 = BilinearXMYM_u16_u16XMu16YM_Cnt( VehSpd_Kph_T_u9p7, 
                                                                              HandWheelPos_HwDeg_T_u12p4, 
                                                                              t_EOTDmpVspd_Kph_u9p7, 
                                                                              (uint16)TableSize_m(t_EOTDmpVspd_Kph_u9p7), 
                                                                              (P2CONST(uint16, AUTOMATIC, AUTOMATIC))t2_EOTPos_HwDeg_T_u12p4, 
                                                                              (P2CONST(uint16, AUTOMATIC, AUTOMATIC))t2_EOTExPosDepDmpTblY_MtrNmpRadps_u0p16,
                                                                              (uint16)TableSize_m(t2_EOTPos_HwDeg_T_u12p4[0]));
        }
        else
        {
            EOTDamping_MtrNmpRadpS_T_u0p16 = BilinearXMYM_u16_u16XMu16YM_Cnt( VehSpd_Kph_T_u9p7, 
                                                                              HandWheelPos_HwDeg_T_u12p4, 
                                                                              t_EOTDmpVspd_Kph_u9p7, 
                                                                              (uint16)TableSize_m(t_EOTDmpVspd_Kph_u9p7), 
                                                                              (P2CONST(uint16, AUTOMATIC, AUTOMATIC))t2_EOTPos_HwDeg_T_u12p4, 
                                                                              (P2CONST(uint16, AUTOMATIC, AUTOMATIC))t2_EOTPosDepDmpTblY_MtrNmpRadpS_u0p16,
                                                                              (uint16)TableSize_m(t2_EOTPos_HwDeg_T_u12p4[0]));
        }
        
        EOTDamping_MtrNmpRadpS_T_f32 = FPM_FixedToFloat_m(EOTDamping_MtrNmpRadpS_T_u0p16, u0p16_T);
        EOTDamping_MtrNm_T_f32 = EOTDamping_MtrNmpRadpS_T_f32 * MotorVel_MtrRadpS_T_f32;
    }
    
    
    EOTDamping_MtrNm_T_f32 = Limit_m(EOTDamping_MtrNm_T_f32, ((D_2MS_SEC_F32 * -k_EOTPosDepDempFinalSlew_MtrNmpS_T_f32)+ EOTActuatorMng_Damping_MtrNm_M_f32), ((D_2MS_SEC_F32 * k_EOTPosDepDempFinalSlew_MtrNmpS_T_f32)+ EOTActuatorMng_Damping_MtrNm_M_f32));
    EOTActuatorMng_Damping_MtrNm_M_f32 = EOTDamping_MtrNm_T_f32;
    
    EOTActuatorMng_EOTDamping_MtrNm_D_f32 = EOTDamping_MtrNm_T_f32;
    return (EOTDamping_MtrNm_T_f32);
}

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of function definition area >>              DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of removed code area >>                   DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of removed code area >>                     DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
