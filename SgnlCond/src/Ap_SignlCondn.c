/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Ap_SignlCondn.c
 *     Workspace:  C:/Synergy_projects/SgnlCond-lz4p8n/SgnlCond/autosar/Ap_SignlCondn.dcf
 *     SW-C Type:  Ap_SignlCondn
 *  Generated at:  Thu May 23 11:50:58 2013
 *
 *     Generator:  MICROSAR RTE Generator Version 2.19.1
 *       License:  License CBD1010124 valid for CBD1010124 Nexteer  Package: BMW MSR SIP BAC3.0     Micro: TI TMS570 TMS570LS30306  Compiler: Code Composer Studio 4.9.0
 *
 *   Description:  C-Code implementation template for SW-C <Ap_SignlCondn>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/* Version Control:
 * Date Created:      Mon Nov 29 18:34:17 2011
 * %version:          10 %
 * %date_modified:    Thu May 23 11:37:51 2013 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 05/15/12	 1		  NRAR		Initial Release for this component. 
 * 05/16/12  2        NRAR      RTE_INIT_IMPLICIT_BUFFERS macro deleted
 * 05/23/12  3        NRAR      Autosar typo update
 * 08/23/12  4        NRAR      FaultInjection point added for SrlComVehSpeed signal                            #6017
 * 09/05/12  5        NRAR      FaultInjection function prototype updated
 * 09/25/12  6        Selva      Checkpoints added and mempmap macros corrected		                          6247
 * 05/21/13	 7		  SP		SF 33 v 003 implementation													  8351
 * 04/02/14  8        SB		Anomaly 6343 Limit outputs													  11607
 * 05/09/14  9		  SB		Updated per Design Review													  11607
 * 05/14/14  10		  SB        UTP fixes																	  11935
 */

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

#include "Rte_Ap_SignlCondn.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

#include "CalConstants.h"
#include "GlobalMacro.h"
#include "Ap_SignlCondn_Cfg.h"

#define D_VEHLONACCELGAIN_KPHPS_F32	3.6F
#define D_VEHSPDLOLMT_KPH_F32 0.0F
#define D_VEHSPDHILMT_KPH_F32 511.0F
#define D_VEHLONACCELLOLMT_KPHPS_F32 (-50.0f)
#define D_VEHLONACCELHILMT_KPHPS_F32 50.0F
#define SIGNLCONDN_START_SEC_VAR_NOINIT_32
#include "MemMap.h"
STATIC VAR(float32, AUTOMATIC) SignlCondn_CurrSrlComVehSpd_Kph_M_f32;
STATIC VAR(float32, AUTOMATIC) SignlCondn_CurrSrlComVehLonAccel_KphpS_M_f32;

#define SIGNLCONDN_STOP_SEC_VAR_NOINIT_32
#include "MemMap.h"  /* PRQA S 5087 */
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
 * Float: Real in interval [-FLT_MAX...FLT_MAX] with single precision (standard type)
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
 *   FLTINJ_SRLCOMVEHLONACCEL_SGNLCOND (155U)
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
 * Float: D_2MS_SEC_F32 = 0.002F
 * Float: D_ZERO_ULS_F32 = 0.0F
 *
 *********************************************************************************************************************/


#define RTE_START_SEC_AP_SIGNLCONDN_APPL_CODE
#include "MemMap.h" /* PRQA S 5087 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: SignlCondn_Per1
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
 *   Float Rte_IRead_SignlCondn_Per1_SrlComVehSpeed_Kph_f32(void)
 *   Float Rte_IRead_SignlCondn_Per1_SrlCom_VehicleLonAccel_KphpS_f32(void)
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_SignlCondn_Per1_VehicleSpeed_Kph_f32(Float data)
 *   Float *Rte_IWriteRef_SignlCondn_Per1_VehicleSpeed_Kph_f32(void)
 *   void Rte_IWrite_SignlCondn_Per1_Vehicle_LonAccel_KphpS_f32(Float data)
 *   Float *Rte_IWriteRef_SignlCondn_Per1_Vehicle_LonAccel_KphpS_f32(void)
 *
 * Client/Server Interfaces:
 * =========================
 *   Server Invocation:
 *   ------------------
 *   Std_ReturnType Rte_Call_FaultInjection_SCom_FltInjection(Float *SignalPath_Uls_f32, FltInjectionLocType LocationKey_Cnt_enum)
 *     Synchronous Server Invocation. Timeout: None
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_SIGNLCONDN_APPL_CODE) SignlCondn_Per1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: SignlCondn_Per1
 *********************************************************************************************************************/
VAR(float32, AUTOMATIC) SrlComVehSpd_Kph_T_f32;
VAR(float32, AUTOMATIC) SrlComVehLonAccel_KphpS_T_f32;
VAR(float32, AUTOMATIC) CurrSrlComVehSpd_Kph_T_f32;
VAR(float32, AUTOMATIC) CurrSrlComVehLonAccel_KphpS_T_f32;

/* Configurable Start of Runnable Checkpoint */
Rte_Call_SignlCondn_Per1_CP0_CheckpointReached();

/* Vehicle_Speed */
SrlComVehSpd_Kph_T_f32 = Rte_IRead_SignlCondn_Per1_SrlComVehSpeed_Kph_f32();

#if (STD_ON == BC_SIGNLCONDN_FAULTINJECTIONPOINT)
Rte_Call_FaultInjection_SCom_FltInjection(&SrlComVehSpd_Kph_T_f32, FLTINJ_SRLCOMVEHSPD_SGNLCOND);
#endif

CurrSrlComVehSpd_Kph_T_f32  = Limit_m(SrlComVehSpd_Kph_T_f32, (SignlCondn_CurrSrlComVehSpd_Kph_M_f32 - (k_VehSpdSlewRate_KphpSec_f32*D_2MS_SEC_F32)), (SignlCondn_CurrSrlComVehSpd_Kph_M_f32 + (k_VehSpdSlewRate_KphpSec_f32*D_2MS_SEC_F32)));
SignlCondn_CurrSrlComVehSpd_Kph_M_f32 = Limit_m(CurrSrlComVehSpd_Kph_T_f32, D_VEHSPDLOLMT_KPH_F32, D_VEHSPDHILMT_KPH_F32);

Rte_IWrite_SignlCondn_Per1_VehicleSpeed_Kph_f32(SignlCondn_CurrSrlComVehSpd_Kph_M_f32);

/* Vehicle_LonAccel */
SrlComVehLonAccel_KphpS_T_f32 = Rte_IRead_SignlCondn_Per1_SrlCom_VehicleLonAccel_KphpS_f32();

#if (STD_ON == BC_SIGNLCONDN_FAULTINJECTIONPOINT)
Rte_Call_FaultInjection_SCom_FltInjection(&SrlComVehLonAccel_KphpS_T_f32, FLTINJ_SRLCOMVEHLONACCEL_SGNLCOND);
#endif

SrlComVehLonAccel_KphpS_T_f32 = SrlComVehLonAccel_KphpS_T_f32 * D_VEHLONACCELGAIN_KPHPS_F32;
CurrSrlComVehLonAccel_KphpS_T_f32  = Limit_m(SrlComVehLonAccel_KphpS_T_f32, (SignlCondn_CurrSrlComVehLonAccel_KphpS_M_f32 -(k_VehAccelSlewRate_KphpSecSq_f32*D_2MS_SEC_F32 )), (SignlCondn_CurrSrlComVehLonAccel_KphpS_M_f32 +(k_VehAccelSlewRate_KphpSecSq_f32*D_2MS_SEC_F32 )));
SignlCondn_CurrSrlComVehLonAccel_KphpS_M_f32 = Limit_m(CurrSrlComVehLonAccel_KphpS_T_f32, D_VEHLONACCELLOLMT_KPHPS_F32, D_VEHLONACCELHILMT_KPHPS_F32);

Rte_IWrite_SignlCondn_Per1_Vehicle_LonAccel_KphpS_f32(SignlCondn_CurrSrlComVehLonAccel_KphpS_M_f32);

/* Configurable End of Runnable Checkpoint */
 Rte_Call_SignlCondn_Per1_CP1_CheckpointReached();

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define RTE_STOP_SEC_AP_SIGNLCONDN_APPL_CODE
#include "MemMap.h"  /* PRQA S 5087 */


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
