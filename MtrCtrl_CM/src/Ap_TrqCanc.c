/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Ap_TrqCanc.c
 *     Workspace:  C:/Users/nzt9hv/Documents/Synergy/ccm_wa/ESG_Dev_65/MtrCtrl_CM-nzt9hv/MtrCtrl_CM/autosar
 *     SW-C Type:  Ap_TrqCanc
 *  Generated at:  Tue Apr  7 15:35:41 2015
 *
 *     Generator:  MICROSAR RTE Generator Version 2.17.2
 *       License:  License CBD1010122 valid for CBD1010122 Nexteer  GM MSR_SLP3_BSW_RTE_wGMLAN TexasInstruments TMS570 Texas Instruments
 *
 *   Description:  C-Code implementation template for SW-C <Ap_TrqCanc>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/*
 * Copyright 2015 Nexteer Automotive
 * Nexteer Confidential
 * Version Control:
 * Date Created:      Fri Apr 13 10:09:03 2012
 * %version:          20 %
 * %derived_by:       nzt9hv %
 * %date_modified:    Wed Nov  6 10:32:10 2013 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author    Change Description                                                               SCR #
 * -------   -------  --------  -------------------------------------------------------------------------------  ------
 * 09/20/12  5        OT        Partial implementation of SF99B v004
 * 11/13/12  6        OT        Anomaly 4035 (divide result of atan2f by 2*pi)
 * 11/20/12  8		 Selva 		Checkpoints and memmap statements added	
 * 02/24/13  9        M. Story  anomaly 4342 cogtorq read write
 * 02/24/13  11     Selva       Updated for SF99B -v8 with only changes needed for voltage command integrity check   
 *                              for torque reasonableness	
 * 03/21/13  12     Selva       Updated to version 8 FDD SF99 B	                                                   7711		
 * 06/03/13  13     Selva       Updated to version 9 FDD SF99 B
 * 09/24/13  14       OT        Added sin lookup table function for load reduction
 * 10/21/13  15     Selva       Updated to version FDD v10                                                       10050
 * 10/24/13  16     Selva       Correct the Per instance memory block in Cogging TrqCanc block                   10583
 * 11/06/13  17       Selva      Updated for V11 of     FDD SF99                                                 10740
 * 03/10/15	 18       Selva      Updated for V15 of FDD SF99                                                     12888
 * 04/25/15  19		  Selva      Updated for V16 of FDD SF99                                                     13279
 * 08/19/15	 20       Selva      Updated for V17 of FDD SF99, EA3#A283,EA3#1777  fixed                           EA3#2430
 */
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *
 * AUTOSAR Modelling Object Descriptions
 *
 **********************************************************************************************************************

 Data Types:
 ===========
  NvM_DestPtr
    DataPtr Type to be used by WriteBlock, ReadBlock and RestoreBlockDefaults operations. 	This type is used for all NVRAM blocks


 Component Types:
 ================
  Ap_TrqCanc
    Generates the Current Command and the Voltage Reference for the Current Control

 *********************************************************************************************************************/

#include "Rte_Ap_TrqCanc.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
 
/* MISRA-C:2004 Rule 8.7: This deviation is required to keep the memory map intact.  Rule suppressed by line at each occurrence. */

/* MISRA-C:2004 Rule 10.3: This deviation is required because of Nexteer macro library.  Rule suppressed by line at each occurrence. */

/* MISRA-C:2004 Rule 10.4: This deviation is required because of Nexteer macro library.  Rule suppressed by line at each occurrence. */

/* PRQA S 4533 EOF 
 * MISRA-C:2004 Rule 12.7: This deviation is required because of Nexteer macro library.  Rule suppressed by file level. */


/* MISRA-C:2004 Rule 19.1: This deviation is required for AUTOSAR memory map requirements.  Rule suppressed by line at each occurrence. */

/* MISRA-C:2004 Rule 21.1: Deviation is allowed till decision is made about fixing the warnings in Nexteer Libraries.  Rule suppressed by line at each occurrence. */

 
#include "Ap_TrqCanc_Cfg.h"
#include "CalConstants.h"
#include "fixmath.h"
#include "interpolation.h"
#include "filters.h"
#include <math.h>
#include <float.h>
#include "MtrCtrl_Cfg.h"  
#define MTRCTRL
#include "Ap_MtrCtrl.h"

typedef struct
{
	sint16 CoggingMX_MtrNm_s2p13 ;
	sint16 CoggingMY_MtrNm_s2p13;

} CoggingM_MtrNm_Str ;


#define D_MINCOGRANGE_NM_S2P13                 (FPM_InitFixedPoint_m(-0.1,s2p13_T))
#define D_MAXCOGRANGE_NM_S2P13				   (FPM_InitFixedPoint_m(0.1,s2p13_T))
#define D_MINCOGRANGE_NM_S5P10                 (FPM_InitFixedPoint_m(-0.1,s5p10_T))
#define D_MAXCOGRANGE_NM_S5P10				   (FPM_InitFixedPoint_m(0.1,s5p10_T))
#define D_MINTRQRANGE_NM_F32                    (-0.5F)
#define D_MAXTRQRANGE_NM_F32				     (0.5F)
#define D_SQRT3OVR2_ULS_F32					    0.866025403784F
#define D_6HARMONICNO_F32						6.0F
#define D_12HARMONICNO_F32						12.0F
#define D_COGGINGTBLRES_F32						81.48733F
#define D_MAXTBLVALUE_CNT_U16					511U

#define D_30DEGREES_CNT_U16			5461U
#define D_DEG2RAD_ULS_F32				0.0174532925199F
#define	D_SCALERADTOCNTS_ULS_F32	10430.3783505F
#define D_REVWITHROUND_ULS_F32		65536.5F
#define D_ONEHALF_ULS_F32				0.5F
#define D_POSITIVEONE_CNT_S8            ((sint8)1)
#define D_COGTRQ_LOOPLMT			128U 
#define D_DAXRPLTBLSZ_CNT_U8            (TableSize_m(t_MtrCurrDaxRpl_Amp_u9p7))
#define D_QAXRPLTBLSZ_CNT_U8            (TableSize_m(t_MtrCurrQaxRpl_Amp_u9p7))
#define D_NOOFHARMONIC_CNT_U8      3U
#define D_COGTRQRPL_LOOPLMT 		9U


#define TRQCANC_START_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */

STATIC volatile VAR(float32, Ap_TrqCanc_VAR_NOINIT) CoggingTrqCanc_MtrNm_D_f32;  /* PRQA S 3218 */
STATIC volatile VAR(float32, Ap_TrqCanc_VAR_NOINIT) MtrTrq6thMag_MtrNm_D_f32;     /* PRQA S 3218 */
STATIC volatile VAR(float32, Ap_TrqCanc_VAR_NOINIT)	MtrTrq12thMag_MtrNm_D_f32;     /* PRQA S 3218 */
STATIC volatile VAR(float32, Ap_TrqCanc_VAR_NOINIT)	MtrTrq18thMag_MtrNm_D_f32;       /* PRQA S 3218 */
STATIC volatile VAR(float32, Ap_TrqCanc_VAR_NOINIT) MtrTrq18thMagFinal_MtrNm_D_f32;    /* PRQA S 3218 */
STATIC volatile VAR(float32, Ap_TrqCanc_VAR_NOINIT) MtrTrqRip18thPhsFinal_Rad_D_f32;    /* PRQA S 3218 */
STATIC volatile VAR(float32, Ap_TrqCanc_VAR_NOINIT) MtrTrq6thMagFinal_MtrNm_D_f32;       /* PRQA S 3218 */
STATIC volatile VAR(float32, Ap_TrqCanc_VAR_NOINIT) MtrTrqRip6thPhsFinal_Rad_D_f32;       /* PRQA S 3218 */
STATIC volatile VAR(float32, Ap_TrqCanc_VAR_NOINIT) MtrTrq12thMagFinal_MtrNm_D_f32;        /* PRQA S 3218 */
STATIC volatile VAR(float32, Ap_TrqCanc_VAR_NOINIT) MtrTrqRip12thPhsFinal_Rad_D_f32;        /* PRQA S 3218 */
STATIC  volatile VAR(float32, Ap_TrqCanc_VAR_NOINIT) CoggingTrqMtrPosElec_Rev_D_f32;         /* PRQA S 3218 */
STATIC volatile VAR(float32, Ap_TrqCanc_VAR_NOINIT) MtrTrqRip6thPhs_Rad_D_f32; /* PRQA S 3218 */
STATIC volatile VAR(float32, Ap_TrqCanc_VAR_NOINIT)	MtrTrqRip12thPhs_Rad_D_f32;                  /* PRQA S 3218 */
STATIC volatile VAR(float32, Ap_TrqCanc_VAR_NOINIT)	MtrTrqRip18thPhs_Rad_D_f32; /* PRQA S 3218 */
STATIC volatile VAR(float32, Ap_TrqCanc_VAR_NOINIT)	TrqCanc_MtrTrqRpl_MtrNm_D_f32;  /* PRQA S 3218 */
STATIC VAR(float32, Ap_TrqCanc_VAR_NOINIT) MtrTrqRpl6Mag_MtrNm_M_f32[2];
STATIC VAR(float32, Ap_TrqCanc_VAR_NOINIT) MtrTrqRpl12Mag_MtrNm_M_f32[2];
STATIC VAR(float32, Ap_TrqCanc_VAR_NOINIT) MtrTrq6Ph_Rad_M_f32[2];
STATIC VAR(float32, Ap_TrqCanc_VAR_NOINIT) MtrTrq12Ph_Rad_M_f32[2];
STATIC VAR(float32, Ap_TrqCanc_VAR_NOINIT) MtrTrqRpl18Mag_MtrNm_M_f32[2];
STATIC VAR(float32, Ap_TrqCanc_VAR_NOINIT) MtrTrq18Ph_Rad_M_f32[2];
STATIC VAR(float32, Ap_TrqCanc_VAR_NOINIT) TrqCanc_IqtoTrqMulti_VpRadpS_M_f32[2];
#define TRQCANC_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */

#define TRQCANC_START_SEC_VAR_CLEARED_16
#include "MemMap.h"  /* PRQA S 5087 */
STATIC volatile VAR(uint16, Ap_TrqCanc_VAR_NOINIT) CogginTrqCancIndex_Cnt_D_u16; /* PRQA S 3218 */
VAR(uint16, AUTOMATIC)  SlowDataAccessBufIndex_Cnt_M_u16;
STATIC  VAR(sint16, Ap_TrqCanc_VAR_NOINIT)  TrqCanc_MtrTrqRpl6X_MtrNm_M_s2p13[D_DAXRPLTBLSZ_CNT_U8][D_QAXRPLTBLSZ_CNT_U8] ; 
STATIC  VAR(sint16, Ap_TrqCanc_VAR_NOINIT)  TrqCanc_MtrTrqRpl6Y_MtrNm_M_s2p13[D_DAXRPLTBLSZ_CNT_U8][D_QAXRPLTBLSZ_CNT_U8] ;
STATIC  VAR(sint16, Ap_TrqCanc_VAR_NOINIT)  TrqCanc_MtrTrqRpl12X_MtrNm_M_s2p13[D_DAXRPLTBLSZ_CNT_U8][D_QAXRPLTBLSZ_CNT_U8] ;
STATIC  VAR(sint16, Ap_TrqCanc_VAR_NOINIT)  TrqCanc_MtrTrqRpl12Y_MtrNm_M_s2p13[D_DAXRPLTBLSZ_CNT_U8][D_QAXRPLTBLSZ_CNT_U8];
STATIC  VAR(sint16, Ap_TrqCanc_VAR_NOINIT)  TrqCanc_MtrTrqRpl18X_MtrNm_M_s2p13[D_DAXRPLTBLSZ_CNT_U8][D_QAXRPLTBLSZ_CNT_U8] ;
STATIC  VAR(sint16, Ap_TrqCanc_VAR_NOINIT)  TrqCanc_MtrTrqRpl18Y_MtrNm_M_s2p13[D_DAXRPLTBLSZ_CNT_U8][D_QAXRPLTBLSZ_CNT_U8];
#define TRQCANC_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h" /* PRQA S 5087 */

#define TRQCANC_START_SEC_CONST_16
#include "MemMap.h"  /* PRQA S 5087 */
STATIC CONST(uint16, AUTOMATIC) t_SinTbl_Cnt_u16[513] =                													 /* PRQA S 3218 */
	  { 0u,    201u,  402u,  603u,  804u,  1005u, 1206u, 1407u, 1608u, 1809u, 2010u, 2211u, 2412u, 2613u, 2814u, 3015u,
		3216u, 3416u, 3617u, 3818u, 4019u, 4219u, 4420u, 4621u, 4821u, 5022u, 5222u, 5422u, 5623u, 5823u, 6023u, 6223u,
		6424u, 6624u, 6824u, 7024u, 7223u, 7423u, 7623u, 7823u, 8022u, 8222u, 8421u, 8620u, 8820u, 9019u, 9218u, 9417u,
		9616u, 9815u, 10014u,10212u,10411u,10609u,10808u,11006u,11204u,11402u,11600u,11798u,11996u,12193u,12391u,12588u,
		12785u,12982u,13179u,13376u,13573u,13770u,13966u,14163u,14359u,14555u,14751u,14947u,15142u,15338u,15533u,15729u,
		15924u,16119u,16313u,16508u,16703u,16897u,17091u,17285u,17479u,17673u,17866u,18060u,18253u,18446u,18639u,18831u,
		19024u,19216u,19408u,19600u,19792u,19984u,20175u,20366u,20557u,20748u,20939u,21129u,21319u,21509u,21699u,21889u,
		22078u,22267u,22456u,22645u,22834u,23022u,23210u,23398u,23586u,23773u,23960u,24147u,24334u,24521u,24707u,24893u,
		25079u,25265u,25450u,25635u,25820u,26005u,26189u,26374u,26557u,26741u,26925u,27108u,27291u,27473u,27656u,27838u,
		28020u,28201u,28383u,28564u,28745u,28925u,29106u,29286u,29465u,29645u,29824u,30003u,30181u,30360u,30538u,30716u,
		30893u,31070u,31247u,31424u,31600u,31776u,31952u,32127u,32302u,32477u,32651u,32826u,32999u,33173u,33346u,33519u,
		33692u,33864u,34036u,34208u,34379u,34550u,34721u,34891u,35061u,35231u,35400u,35569u,35738u,35906u,36074u,36242u,
		36409u,36576u,36743u,36909u,37075u,37241u,37406u,37571u,37736u,37900u,38064u,38227u,38390u,38553u,38715u,38877u,
		39039u,39200u,39361u,39522u,39682u,39842u,40001u,40161u,40319u,40478u,40635u,40793u,40950u,41107u,41263u,41419u,
		41575u,41730u,41885u,42039u,42194u,42347u,42500u,42653u,42806u,42958u,43109u,43261u,43411u,43562u,43712u,43861u,
		44011u,44159u,44308u,44456u,44603u,44750u,44897u,45043u,45189u,45334u,45479u,45624u,45768u,45912u,46055u,46198u,
		46340u,46482u,46624u,46765u,46905u,47046u,47185u,47325u,47464u,47602u,47740u,47877u,48014u,48151u,48287u,48423u,
		48558u,48693u,48827u,48961u,49095u,49228u,49360u,49492u,49624u,49755u,49885u,50016u,50145u,50274u,50403u,50531u,
		50659u,50787u,50913u,51040u,51166u,51291u,51416u,51540u,51664u,51788u,51911u,52033u,52155u,52277u,52398u,52518u,
		52638u,52758u,52877u,52995u,53113u,53231u,53348u,53464u,53580u,53696u,53811u,53925u,54039u,54153u,54266u,54378u,
		54490u,54602u,54713u,54823u,54933u,55042u,55151u,55260u,55367u,55475u,55582u,55688u,55794u,55899u,56003u,56108u,
		56211u,56314u,56417u,56519u,56620u,56721u,56822u,56922u,57021u,57120u,57218u,57316u,57413u,57510u,57606u,57702u,
		57797u,57891u,57985u,58079u,58171u,58264u,58356u,58447u,58537u,58628u,58717u,58806u,58895u,58983u,59070u,59157u,
		59243u,59329u,59414u,59498u,59582u,59666u,59749u,59831u,59913u,59994u,60075u,60155u,60234u,60313u,60391u,60469u,
		60546u,60623u,60699u,60775u,60850u,60924u,60998u,61071u,61144u,61216u,61287u,61358u,61429u,61498u,61567u,61636u,
		61704u,61772u,61838u,61905u,61970u,62035u,62100u,62164u,62227u,62290u,62352u,62414u,62475u,62535u,62595u,62654u,
		62713u,62771u,62829u,62886u,62942u,62998u,63053u,63107u,63161u,63214u,63267u,63319u,63371u,63422u,63472u,63522u,
		63571u,63620u,63668u,63715u,63762u,63808u,63853u,63898u,63943u,63986u,64030u,64072u,64114u,64155u,64196u,64236u,
		64276u,64315u,64353u,64391u,64428u,64464u,64500u,64535u,64570u,64604u,64638u,64671u,64703u,64734u,64765u,64796u,
		64826u,64855u,64883u,64911u,64939u,64966u,64992u,65017u,65042u,65066u,65090u,65113u,65136u,65158u,65179u,65199u,
		65219u,65239u,65258u,65276u,65293u,65310u,65327u,65342u,65357u,65372u,65386u,65399u,65412u,65424u,65435u,65446u,
		65456u,65466u,65475u,65483u,65491u,65498u,65504u,65510u,65515u,65520u,65524u,65527u,65530u,65532u,65534u,65535u,
		65535u };
#define TRQCANC_STOP_SEC_CONST_16
#include "MemMap.h"  /* PRQA S 5087 */


STATIC FUNC(void, AUTOMATIC )  CoggingTrqTableUpdate( void);
STATIC FUNC(float32, AUTOMATIC) SinLookup( VAR(float32, AUTOMATIC) Theta_Rad_T_f32 );
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
 * SInt16: Integer in interval [-32768...32767] (standard type)
 * SInt8: Integer in interval [-128...127] (standard type)
 * UInt16: Integer in interval [0...65535] (standard type)
 * UInt8: Integer in interval [0...255] (standard type)
 *
 * Enumeration Types:
 * ==================
 * NvM_RequestResultType: Enumeration of integer in interval [0...5] with enumerators
 *   NVM_REQ_OK (0u)
 *   NVM_REQ_NOT_OK (1u)
 *   NVM_REQ_PENDING (2u)
 *   NVM_REQ_INTEGRITY_FAILED (3u)
 *   NVM_REQ_BLOCK_SKIPPED (4u)
 *   NVM_REQ_NV_INVALIDATED (5u)
 *
 * Array Types:
 * ============
 * CoggingCancTrq: Array with 512 element(s) of type UInt16
 * CoggingCancTrqRplComp: Array with 9 element(s) of type UInt16
 * NvM_DestPtr: Array with 65535 element(s) of type UInt8
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
 * Float: D_180OVRPI_ULS_F32 = 57.295779513082
 * Float: D_2MS_SEC_F32 = 0.002
 * Float: D_2PI_ULS_F32 = 6.2831853071796
 * Float: D_ONE_ULS_F32 = 1
 * Float: D_PI_ULS_F32 = 3.1415926535898
 * Float: D_VECUMIN_VOLTS_F32 = 5
 * Float: D_ZERO_ULS_F32 = 0
 * SInt16: D_ZERO_CNT_S16 = 0
 * SInt8: D_ONE_CNT_S8 = 1
 * SInt8: D_ZERO_CNT_S8 = 0
 * UInt16: D_ZERO_CNT_U16 = 0u
 * UInt8: D_QUADRANT1_CNT_U8 = 1u
 * UInt8: D_QUADRANT2_CNT_U8 = 2u
 * UInt8: D_QUADRANT3_CNT_U8 = 3u
 * UInt8: D_QUADRANT4_CNT_U8 = 4u
 * UInt8: D_ZERO_CNT_U8 = 0u
 *
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *
 * APIs which are accessible from all runnable entities of the SW-C
 *
 **********************************************************************************************************************
 * Per-Instance Memory:
 * ====================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   UInt16 *Rte_Pim_CogTrqCal(void)
#else
 *   CoggingCancTrq *Rte_Pim_CogTrqCal(void)
#endif
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   UInt16 *Rte_Pim_CogTrqRplComp(void)
#else
 *   CoggingCancTrqRplComp *Rte_Pim_CogTrqRplComp(void)
#endif
 *
 *********************************************************************************************************************/


#define RTE_START_SEC_AP_TRQCANC_APPL_CODE
#include "MemMap.h" /* PRQA S 5087 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: TrqCanc_Init
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed once after the RTE is started
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Implicit S/R API:
 *   -----------------
 *   Float Rte_IRead_TrqCanc_Init_EstKe_VpRadpS_f32(void)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_TRQCANC_APPL_CODE) TrqCanc_Init(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: TrqCanc_Init
 *********************************************************************************************************************/
     VAR(float32, AUTOMATIC)	 TrqCanc_IqtoTrqMulti_VpRadpS_T_f32;
	 TrqCanc_IqtoTrqMulti_VpRadpS_T_f32 = (D_SQRT3OVR2_ULS_F32 * (Rte_IRead_TrqCanc_Init_EstKe_VpRadpS_f32())); 
     TrqCanc_IqtoTrqMulti_VpRadpS_M_f32[0] =    TrqCanc_IqtoTrqMulti_VpRadpS_T_f32;                        
	 TrqCanc_IqtoTrqMulti_VpRadpS_M_f32[1] =  TrqCanc_IqtoTrqMulti_VpRadpS_M_f32[0];
	(void)CoggingTrqTableUpdate();
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: TrqCanc_Per1
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
 *   Float Rte_IRead_TrqCanc_Per1_EstKe_VpRadpS_f32(void)
 *   Float Rte_IRead_TrqCanc_Per1_EstLd_Henry_f32(void)
 *   Float Rte_IRead_TrqCanc_Per1_EstLq_Henry_f32(void)
 *   Float Rte_IRead_TrqCanc_Per1_MRFMtrVel_MtrRadpS_f32(void)
 *   Float Rte_IRead_TrqCanc_Per1_MtrCurrDaxRef_Amp_f32(void)
 *   Float Rte_IRead_TrqCanc_Per1_MtrCurrQaxRef_Amp_f32(void)
 *   Float Rte_IRead_TrqCanc_Per1_MtrTrqCmdMRFScl_MtrNm_f32(void)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_TRQCANC_APPL_CODE) TrqCanc_Per1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: TrqCanc_Per1
 *********************************************************************************************************************/
VAR(float32, AUTOMATIC) MRFMtrVel_MtrRadpS_T_f32;
VAR(float32, AUTOMATIC)  DaxRef_Amp_T_f32;
VAR(float32, AUTOMATIC)  QaxRef_Amp_T_f32;
VAR(float32, AUTOMATIC) MtrTrqRpl6X_MtrNm_T_f32;
VAR(float32, AUTOMATIC) MtrTrqRpl6Y_MtrNm_T_f32;
VAR(float32, AUTOMATIC) MtrTrqRpl12X_MtrNm_T_f32;
VAR(float32, AUTOMATIC) MtrTrqRpl12Y_MtrNm_T_f32;
VAR(float32, AUTOMATIC) MtrTrqRpl18X_MtrNm_T_f32;
VAR(float32, AUTOMATIC) MtrTrqRpl18Y_MtrNm_T_f32;
VAR(float32, AUTOMATIC) MtrTrq6thMag_MtrNm_T_f32;
VAR(float32, AUTOMATIC) MtrTrq12thMag_MtrNm_T_f32;
VAR(float32, AUTOMATIC) MtrTrq18thMag_MtrNm_T_f32;
VAR(float32, AUTOMATIC) MtrVel6thHarm_MtrRadpS_T_f32;
VAR(float32, AUTOMATIC) MtrVel12thHarm_MtrRadpS_T_f32;
VAR(float32, AUTOMATIC) MtrVel18thHarm_MtrRadpS_T_f32;
VAR(float32, AUTOMATIC)	MtrTrqCancPI6thMagRP_Uls_T_f32;
VAR(float32, AUTOMATIC)	MtrTrqCancPI12thMagRP_Uls_T_f32;
VAR(float32, AUTOMATIC)	MtrTrqCancPI18thMagRP_Uls_T_f32;
VAR(uint16, AUTOMATIC) MtrVel6thHarm_MtrRadpS_T_u16;
VAR(uint16, AUTOMATIC) MtrVel12thHarm_MtrRadpS_T_u16;
VAR(uint16, AUTOMATIC) MtrVel18thHarm_MtrRadpS_T_u16;

VAR(uint16, AUTOMATIC)	MtrTrqCancPI6thMagRP_Uls_T_u6p10;
VAR(uint16, AUTOMATIC)	MtrTrqCancPI6thPhRP_Rev_T_u0p16;
VAR(uint16, AUTOMATIC)	MtrTrqCancPI12thMagRP_Uls_T_u6p10;
VAR(uint16, AUTOMATIC)	MtrTrqCancPI12thPhRP_Rev_T_u0p16;
VAR(float32, AUTOMATIC)	 MtrTrq6thMagInt_MtrNm_T_f32;
VAR(float32, AUTOMATIC)	 MtrTrq12thMagInt_MtrNm_T_f32;
VAR(uint16, AUTOMATIC)	MtrTrqCancPI18thMagRP_Uls_T_u6p10;
VAR(uint16, AUTOMATIC)	MtrTrqCancPI18thPhRP_Rev_T_u0p16;
VAR(float32, AUTOMATIC)	 MtrTrq18thMagInt_MtrNm_T_f32;

VAR(sint16, AUTOMATIC) DaxRef_Amp_T_s8p7;
VAR(sint16, AUTOMATIC) QaxRef_Amp_T_s8p7;
VAR(sint16, AUTOMATIC) MtrTrqRpl6X_MtrNm_T_s2p13;
VAR(sint16, AUTOMATIC) MtrTrqRpl6Y_MtrNm_T_s2p13;
VAR(sint16, AUTOMATIC) MtrTrqRpl12X_MtrNm_T_s2p13;
VAR(sint16, AUTOMATIC) MtrTrqRpl12Y_MtrNm_T_s2p13;
VAR(sint16, AUTOMATIC) MtrTrqRpl18X_MtrNm_T_s2p13;
VAR(sint16, AUTOMATIC) MtrTrqRpl18Y_MtrNm_T_s2p13;
VAR(float32, AUTOMATIC) MtrTrqRip6thPhsTemp_Rad_T_f32;
VAR(float32, AUTOMATIC) MtrTrqRip12thPhsTemp_Rad_T_f32;
VAR(float32, AUTOMATIC) MtrTrqRip18thPhsTemp_Rad_T_f32;
VAR(float32, AUTOMATIC) MtrTrqCancPI6thPhRPTemp_Rev_T_f32;
VAR(float32, AUTOMATIC) MtrTrqCancPI12thPhRPTemp_Rev_T_f32;
VAR(float32, AUTOMATIC) MtrTrqCancPI18thPhRPTemp_Rev_T_f32;
VAR(float32, AUTOMATIC) MtrTrqCancPI6thPhRPTemp_Rad_T_f32;
VAR(float32, AUTOMATIC) MtrTrqCancPI12thPhRPTemp_Rad_T_f32;
VAR(float32, AUTOMATIC) MtrTrqCancPI18thPhRPTemp_Rad_T_f32;
VAR(float32, AUTOMATIC) MtrTrqRip6thPhs_Rad_T_f32;
VAR(float32, AUTOMATIC) MtrTrqRip12thPhs_Rad_T_f32;
VAR(float32, AUTOMATIC) MtrTrqRip18thPhs_Rad_T_f32;
VAR(uint16, AUTOMATIC) WriteAccessBufIndex_Cnt_T_u16;
VAR(float32,AUTOMATIC) 	EstLd_Henry_T_f32      ;
VAR(float32,AUTOMATIC) 	EstLq_Henry_T_f32      ;
VAR(float32,AUTOMATIC) 	MtrTrqCmdMRFScl_MtrNm_T_f32;
VAR(float32,AUTOMATIC) 	IqtoTrqMulti_VpRadpS_T_f32;
VAR(sint16, AUTOMATIC) MtrTrqCmdMRFScl_MtrNm_T_s4p11;
VAR(float32,AUTOMATIC) EstKe_VpRadpS_T_f32;

	/* Configurable Start of Runnable Checkpoint */
		Rte_Call_TrqCanc_Per1_CP0_CheckpointReached();
	/* Read the inputs*/	
	
	
	WriteAccessBufIndex_Cnt_T_u16 = (FastDataAccessBufIndex_Cnt_M_u16&1u)^1u;
	MRFMtrVel_MtrRadpS_T_f32=Rte_IRead_TrqCanc_Per1_MRFMtrVel_MtrRadpS_f32();
	DaxRef_Amp_T_f32=Rte_IRead_TrqCanc_Per1_MtrCurrDaxRef_Amp_f32();
	QaxRef_Amp_T_f32 =Rte_IRead_TrqCanc_Per1_MtrCurrQaxRef_Amp_f32();
	EstLq_Henry_T_f32=Rte_IRead_TrqCanc_Per1_EstLq_Henry_f32();
	MtrTrqCmdMRFScl_MtrNm_T_f32 =Rte_IRead_TrqCanc_Per1_MtrTrqCmdMRFScl_MtrNm_f32();
	EstLd_Henry_T_f32=Rte_IRead_TrqCanc_Per1_EstLd_Henry_f32();
	EstKe_VpRadpS_T_f32 = Rte_IRead_TrqCanc_Per1_EstKe_VpRadpS_f32();
 /*****  Torque ripple compensation table Start*****/
	MtrVel6thHarm_MtrRadpS_T_f32=MRFMtrVel_MtrRadpS_T_f32*k_Harmonic6thElec_Uls_f32*(k_NoofPoles_Uls_f32 * D_ONEHALF_ULS_F32);
	MtrVel12thHarm_MtrRadpS_T_f32=MRFMtrVel_MtrRadpS_T_f32*k_Harmonic12thElec_Uls_f32*(k_NoofPoles_Uls_f32 * D_ONEHALF_ULS_F32);
	MtrVel18thHarm_MtrRadpS_T_f32=MRFMtrVel_MtrRadpS_T_f32*k_Harmonic18thElec_Uls_f32*(k_NoofPoles_Uls_f32 * D_ONEHALF_ULS_F32);	 
	
	
	MtrVel6thHarm_MtrRadpS_T_u16  = FPM_FloatToFixed_m((Abs_f32_m(MtrVel6thHarm_MtrRadpS_T_f32)), u16p0_T);    /* PRQA S 4395 */
	MtrVel12thHarm_MtrRadpS_T_u16 =FPM_FloatToFixed_m((Abs_f32_m(MtrVel12thHarm_MtrRadpS_T_f32)), u16p0_T);    /* PRQA S 4395 */
	MtrVel18thHarm_MtrRadpS_T_u16 =FPM_FloatToFixed_m((Abs_f32_m(MtrVel18thHarm_MtrRadpS_T_f32)), u16p0_T);	   /* PRQA S 4395 */
	
	DaxRef_Amp_T_s8p7=FPM_FloatToFixed_m(DaxRef_Amp_T_f32,s8p7_T);      /* PRQA S 4395 */
	QaxRef_Amp_T_s8p7=FPM_FloatToFixed_m(QaxRef_Amp_T_f32,s8p7_T);     /* PRQA S 4395 */
	MtrTrqCmdMRFScl_MtrNm_T_s4p11= FPM_FloatToFixed_m(MtrTrqCmdMRFScl_MtrNm_T_f32,s4p11_T);  /* PRQA S 4395 */
	
	
	
	/* 6thMag_TrqRipple */
	MtrTrqRpl6X_MtrNm_T_s2p13 = BilinearXYM_s16_u16Xs16YM_Cnt(
		Abs_s16_m(DaxRef_Amp_T_s8p7),                       /* PRQA S 4393 */
		Abs_s16_m(QaxRef_Amp_T_s8p7),                        /* PRQA S 4393 */
		t_MtrCurrDaxRpl_Amp_u9p7,
		TableSize_m(t_MtrCurrDaxRpl_Amp_u9p7),   
		t_MtrCurrQaxRpl_Amp_u9p7,
		TrqCanc_MtrTrqRpl6X_MtrNm_M_s2p13[0],
		TableSize_m(t_MtrCurrQaxRpl_Amp_u9p7));
	
	/* 6thPhase_TrqRipple */
	MtrTrqRpl6Y_MtrNm_T_s2p13 = BilinearXYM_s16_u16Xs16YM_Cnt(
		Abs_s16_m(DaxRef_Amp_T_s8p7),                           /* PRQA S 4393 */
		Abs_s16_m(QaxRef_Amp_T_s8p7),                             /* PRQA S 4393 */
		t_MtrCurrDaxRpl_Amp_u9p7,
		TableSize_m(t_MtrCurrDaxRpl_Amp_u9p7),
		t_MtrCurrQaxRpl_Amp_u9p7,
		TrqCanc_MtrTrqRpl6Y_MtrNm_M_s2p13[0],
		TableSize_m(t_MtrCurrQaxRpl_Amp_u9p7));
	
	/* 12thMag_TrqRipple */
	MtrTrqRpl12X_MtrNm_T_s2p13 = BilinearXYM_s16_u16Xs16YM_Cnt(
		Abs_s16_m(DaxRef_Amp_T_s8p7),                                  /* PRQA S 4393 */
		Abs_s16_m(QaxRef_Amp_T_s8p7),                                 /* PRQA S 4393 */
		t_MtrCurrDaxRpl_Amp_u9p7,
		TableSize_m(t_MtrCurrDaxRpl_Amp_u9p7),
		t_MtrCurrQaxRpl_Amp_u9p7,
		TrqCanc_MtrTrqRpl12X_MtrNm_M_s2p13[0],
		TableSize_m(t_MtrCurrQaxRpl_Amp_u9p7));
	
	/* 12thPhase_TrqRipple */
	MtrTrqRpl12Y_MtrNm_T_s2p13 = BilinearXYM_s16_u16Xs16YM_Cnt(
		Abs_s16_m(DaxRef_Amp_T_s8p7),                               /* PRQA S 4393 */
		Abs_s16_m(QaxRef_Amp_T_s8p7),                               /* PRQA S 4393 */
		t_MtrCurrDaxRpl_Amp_u9p7,
		TableSize_m(t_MtrCurrDaxRpl_Amp_u9p7),
		t_MtrCurrQaxRpl_Amp_u9p7,
		TrqCanc_MtrTrqRpl12Y_MtrNm_M_s2p13[0],
		TableSize_m(t_MtrCurrQaxRpl_Amp_u9p7));
	
/* 18thMag_TrqRipple */
	MtrTrqRpl18X_MtrNm_T_s2p13 = BilinearXYM_s16_u16Xs16YM_Cnt(
		Abs_s16_m(DaxRef_Amp_T_s8p7),                                  /* PRQA S 4393 */
		Abs_s16_m(QaxRef_Amp_T_s8p7),                                   /* PRQA S 4393 */
		t_MtrCurrDaxRpl_Amp_u9p7,
		TableSize_m(t_MtrCurrDaxRpl_Amp_u9p7),
		t_MtrCurrQaxRpl_Amp_u9p7,
		TrqCanc_MtrTrqRpl18X_MtrNm_M_s2p13[0],
		TableSize_m(t_MtrCurrQaxRpl_Amp_u9p7));
	
	/* 18thPhase_TrqRipple */
	MtrTrqRpl18Y_MtrNm_T_s2p13 = BilinearXYM_s16_u16Xs16YM_Cnt(
		Abs_s16_m(DaxRef_Amp_T_s8p7),                               /* PRQA S 4393 */
		Abs_s16_m(QaxRef_Amp_T_s8p7),                                /* PRQA S 4393 */
		t_MtrCurrDaxRpl_Amp_u9p7,
		TableSize_m(t_MtrCurrDaxRpl_Amp_u9p7),
		t_MtrCurrQaxRpl_Amp_u9p7,
		TrqCanc_MtrTrqRpl18Y_MtrNm_M_s2p13[0],
		TableSize_m(t_MtrCurrQaxRpl_Amp_u9p7));	
	
	
	MtrTrqRpl6X_MtrNm_T_f32 = FPM_FixedToFloat_m(MtrTrqRpl6X_MtrNm_T_s2p13, s2p13_T);
	MtrTrqRpl6Y_MtrNm_T_f32 = FPM_FixedToFloat_m(MtrTrqRpl6Y_MtrNm_T_s2p13, s2p13_T);
	MtrTrqRpl12X_MtrNm_T_f32 = FPM_FixedToFloat_m(MtrTrqRpl12X_MtrNm_T_s2p13, s2p13_T);
	MtrTrqRpl12Y_MtrNm_T_f32 = FPM_FixedToFloat_m(MtrTrqRpl12Y_MtrNm_T_s2p13, s2p13_T);
	MtrTrqRpl18X_MtrNm_T_f32 = FPM_FixedToFloat_m(MtrTrqRpl18X_MtrNm_T_s2p13, s2p13_T);
	MtrTrqRpl18Y_MtrNm_T_f32 = FPM_FixedToFloat_m(MtrTrqRpl18Y_MtrNm_T_s2p13, s2p13_T);
	
	MtrTrq6thMagInt_MtrNm_T_f32 = sqrtf((MtrTrqRpl6X_MtrNm_T_f32 * MtrTrqRpl6X_MtrNm_T_f32) + (MtrTrqRpl6Y_MtrNm_T_f32 * MtrTrqRpl6Y_MtrNm_T_f32));
	MtrTrq12thMagInt_MtrNm_T_f32 = sqrtf((MtrTrqRpl12X_MtrNm_T_f32 * MtrTrqRpl12X_MtrNm_T_f32) + (MtrTrqRpl12Y_MtrNm_T_f32 * MtrTrqRpl12Y_MtrNm_T_f32));
	MtrTrq18thMagInt_MtrNm_T_f32 = sqrtf((MtrTrqRpl18X_MtrNm_T_f32 * MtrTrqRpl18X_MtrNm_T_f32) + (MtrTrqRpl18Y_MtrNm_T_f32 * MtrTrqRpl18Y_MtrNm_T_f32));
	
	MtrTrqRip6thPhsTemp_Rad_T_f32 = ((float32)Sign_f32_m(QaxRef_Amp_T_f32)) * (atan2f(MtrTrqRpl6Y_MtrNm_T_f32, MtrTrqRpl6X_MtrNm_T_f32));
	MtrTrqRip12thPhsTemp_Rad_T_f32 = ((float32)Sign_f32_m(QaxRef_Amp_T_f32)) * (atan2f(MtrTrqRpl12Y_MtrNm_T_f32, MtrTrqRpl12X_MtrNm_T_f32) );
	MtrTrqRip18thPhsTemp_Rad_T_f32 = ((float32)Sign_f32_m(QaxRef_Amp_T_f32)) * (atan2f(MtrTrqRpl18Y_MtrNm_T_f32, MtrTrqRpl18X_MtrNm_T_f32) );
	
	if(MtrTrqRip6thPhsTemp_Rad_T_f32<D_ZERO_ULS_F32)
	{
		MtrTrqRip6thPhsTemp_Rad_T_f32=MtrTrqRip6thPhsTemp_Rad_T_f32+D_2PI_ULS_F32;
	}
	
	if(MtrTrqRip12thPhsTemp_Rad_T_f32<D_ZERO_ULS_F32)
	{
		MtrTrqRip12thPhsTemp_Rad_T_f32=MtrTrqRip12thPhsTemp_Rad_T_f32+D_2PI_ULS_F32;
	}
	
	if(MtrTrqRip18thPhsTemp_Rad_T_f32<D_ZERO_ULS_F32)
	{
		MtrTrqRip18thPhsTemp_Rad_T_f32=MtrTrqRip18thPhsTemp_Rad_T_f32+D_2PI_ULS_F32;
	}
	
	

	
	MtrTrq6thMag_MtrNm_D_f32=MtrTrq6thMagInt_MtrNm_T_f32;
	MtrTrqRip6thPhs_Rad_D_f32=MtrTrqRip6thPhsTemp_Rad_T_f32;
	MtrTrq12thMag_MtrNm_D_f32=MtrTrq12thMagInt_MtrNm_T_f32;
	MtrTrqRip12thPhs_Rad_D_f32=MtrTrqRip12thPhsTemp_Rad_T_f32;
	MtrTrqRip18thPhs_Rad_D_f32=MtrTrqRip18thPhsTemp_Rad_T_f32;
	MtrTrq18thMag_MtrNm_D_f32=MtrTrq18thMagInt_MtrNm_T_f32;
	/*****  Torque ripple compensation table End *****/
	
	/*****  PI Magnitude and phase response compensation table Start *****/
	
	
	
	MtrTrqCancPI6thMagRP_Uls_T_u6p10	=	BilinearXYM_u16_u16Xu16YM_Cnt(
													MtrVel6thHarm_MtrRadpS_T_u16,
													Abs_s16_m(MtrTrqCmdMRFScl_MtrNm_T_s4p11),                  /* PRQA S 4393 */
													t_MtrVelX_MtrRadpS_T_u16,
													TableSize_m(t_MtrVelX_MtrRadpS_T_u16),
													t_MtrTrqCmdPIY_MtrNm_u5p11,
													t2_MtrTrqCancPIMagRP_Uls_u6p10[0],
													TableSize_m(t_MtrTrqCmdPIY_MtrNm_u5p11));

	MtrTrqCancPI6thPhRP_Rev_T_u0p16	=BilinearXYM_u16_u16Xu16YM_Cnt(
													MtrVel6thHarm_MtrRadpS_T_u16,
													Abs_s16_m(MtrTrqCmdMRFScl_MtrNm_T_s4p11),                     /* PRQA S 4393 */
													t_MtrVelX_MtrRadpS_T_u16,
													TableSize_m(t_MtrVelX_MtrRadpS_T_u16),
													t_MtrTrqCmdPIY_MtrNm_u5p11,
													t2_MtrTrqCancPIPhRP_Rev_u0p16[0],
													TableSize_m(t_MtrTrqCmdPIY_MtrNm_u5p11));


	
	MtrTrqCancPI12thMagRP_Uls_T_u6p10	=BilinearXYM_u16_u16Xu16YM_Cnt(
													MtrVel12thHarm_MtrRadpS_T_u16,
													Abs_s16_m(MtrTrqCmdMRFScl_MtrNm_T_s4p11),                   /* PRQA S 4393 */
													t_MtrVelX_MtrRadpS_T_u16,
													TableSize_m(t_MtrVelX_MtrRadpS_T_u16),
													t_MtrTrqCmdPIY_MtrNm_u5p11,
													t2_MtrTrqCancPIMagRP_Uls_u6p10[0],
													TableSize_m(t_MtrTrqCmdPIY_MtrNm_u5p11));

	MtrTrqCancPI12thPhRP_Rev_T_u0p16	=BilinearXYM_u16_u16Xu16YM_Cnt(
													MtrVel12thHarm_MtrRadpS_T_u16,
													Abs_s16_m(MtrTrqCmdMRFScl_MtrNm_T_s4p11),                   /* PRQA S 4393 */
													t_MtrVelX_MtrRadpS_T_u16,
													TableSize_m(t_MtrVelX_MtrRadpS_T_u16),
													t_MtrTrqCmdPIY_MtrNm_u5p11,
													t2_MtrTrqCancPIPhRP_Rev_u0p16[0],
													TableSize_m(t_MtrTrqCmdPIY_MtrNm_u5p11));
	MtrTrqCancPI18thMagRP_Uls_T_u6p10	=BilinearXYM_u16_u16Xu16YM_Cnt(
													MtrVel18thHarm_MtrRadpS_T_u16,
													Abs_s16_m(MtrTrqCmdMRFScl_MtrNm_T_s4p11),                     /* PRQA S 4393 */
													t_MtrVelX_MtrRadpS_T_u16,
													TableSize_m(t_MtrVelX_MtrRadpS_T_u16),
													t_MtrTrqCmdPIY_MtrNm_u5p11,
													t2_MtrTrqCancPIMagRP_Uls_u6p10[0],
													TableSize_m(t_MtrTrqCmdPIY_MtrNm_u5p11));

	MtrTrqCancPI18thPhRP_Rev_T_u0p16	=BilinearXYM_u16_u16Xu16YM_Cnt(
													MtrVel18thHarm_MtrRadpS_T_u16,
													Abs_s16_m(MtrTrqCmdMRFScl_MtrNm_T_s4p11),                    /* PRQA S 4393 */
													t_MtrVelX_MtrRadpS_T_u16,
													TableSize_m(t_MtrVelX_MtrRadpS_T_u16),
													t_MtrTrqCmdPIY_MtrNm_u5p11,
													t2_MtrTrqCancPIPhRP_Rev_u0p16[0],
													TableSize_m(t_MtrTrqCmdPIY_MtrNm_u5p11));

	MtrTrqCancPI6thMagRP_Uls_T_f32=FPM_FixedToFloat_m(MtrTrqCancPI6thMagRP_Uls_T_u6p10,u6p10_T);
	MtrTrqCancPI12thMagRP_Uls_T_f32=FPM_FixedToFloat_m(MtrTrqCancPI12thMagRP_Uls_T_u6p10,u6p10_T);
	MtrTrqCancPI18thMagRP_Uls_T_f32=FPM_FixedToFloat_m(MtrTrqCancPI18thMagRP_Uls_T_u6p10,u6p10_T);
															   
	MtrTrqCancPI6thPhRPTemp_Rev_T_f32	=FPM_FixedToFloat_m(MtrTrqCancPI6thPhRP_Rev_T_u0p16,u0p16_T);
	MtrTrqCancPI12thPhRPTemp_Rev_T_f32	=FPM_FixedToFloat_m(MtrTrqCancPI12thPhRP_Rev_T_u0p16,u0p16_T);
	MtrTrqCancPI18thPhRPTemp_Rev_T_f32	=FPM_FixedToFloat_m(MtrTrqCancPI18thPhRP_Rev_T_u0p16,u0p16_T);

	MtrTrqCancPI6thPhRPTemp_Rad_T_f32=MtrTrqCancPI6thPhRPTemp_Rev_T_f32*(float32)Sign_f32_m(MRFMtrVel_MtrRadpS_T_f32)* D_2PI_ULS_F32;
	MtrTrqCancPI12thPhRPTemp_Rad_T_f32=MtrTrqCancPI12thPhRPTemp_Rev_T_f32*(float32)Sign_f32_m(MRFMtrVel_MtrRadpS_T_f32)*D_2PI_ULS_F32  ;
	
	MtrTrqCancPI18thPhRPTemp_Rad_T_f32=MtrTrqCancPI18thPhRPTemp_Rev_T_f32*(float32)Sign_f32_m(MRFMtrVel_MtrRadpS_T_f32)*D_2PI_ULS_F32  ;

	if(MtrTrqCancPI6thPhRPTemp_Rad_T_f32<D_ZERO_ULS_F32)
		{
		MtrTrqCancPI6thPhRPTemp_Rad_T_f32=MtrTrqCancPI6thPhRPTemp_Rad_T_f32+D_2PI_ULS_F32;

		}


	if(MtrTrqCancPI12thPhRPTemp_Rad_T_f32<D_ZERO_ULS_F32)
		{
		MtrTrqCancPI12thPhRPTemp_Rad_T_f32=MtrTrqCancPI12thPhRPTemp_Rad_T_f32+D_2PI_ULS_F32;

		}

	if(MtrTrqCancPI18thPhRPTemp_Rad_T_f32<D_ZERO_ULS_F32)
		{
		MtrTrqCancPI18thPhRPTemp_Rad_T_f32=MtrTrqCancPI18thPhRPTemp_Rad_T_f32+D_2PI_ULS_F32;

		}



	MtrTrq6thMag_MtrNm_T_f32=Limit_m((MtrTrqCancPI6thMagRP_Uls_T_f32*MtrTrq6thMagInt_MtrNm_T_f32), D_MINTRQRANGE_NM_F32, D_MAXTRQRANGE_NM_F32);
	MtrTrqRip6thPhs_Rad_T_f32=MtrTrqCancPI6thPhRPTemp_Rad_T_f32 + MtrTrqRip6thPhsTemp_Rad_T_f32;

	
	MtrTrq12thMag_MtrNm_T_f32=Limit_m((MtrTrqCancPI12thMagRP_Uls_T_f32*MtrTrq12thMagInt_MtrNm_T_f32), D_MINTRQRANGE_NM_F32, D_MAXTRQRANGE_NM_F32);
	MtrTrqRip12thPhs_Rad_T_f32= MtrTrqCancPI12thPhRPTemp_Rad_T_f32 + MtrTrqRip12thPhsTemp_Rad_T_f32;

	
	MtrTrq18thMag_MtrNm_T_f32=Limit_m((MtrTrqCancPI18thMagRP_Uls_T_f32*MtrTrq18thMagInt_MtrNm_T_f32), D_MINTRQRANGE_NM_F32, D_MAXTRQRANGE_NM_F32);
	MtrTrqRip18thPhs_Rad_T_f32= MtrTrqCancPI18thPhRPTemp_Rad_T_f32 + MtrTrqRip18thPhsTemp_Rad_T_f32;

	/***** PI Magnitude and phase response compensation table End *****/

	MtrTrq6thMagFinal_MtrNm_D_f32=MtrTrq6thMag_MtrNm_T_f32;
	MtrTrqRip6thPhsFinal_Rad_D_f32=MtrTrqRip6thPhs_Rad_T_f32;
	MtrTrq12thMagFinal_MtrNm_D_f32=MtrTrq12thMag_MtrNm_T_f32;
	MtrTrqRip12thPhsFinal_Rad_D_f32=MtrTrqRip12thPhs_Rad_T_f32;
	MtrTrqRip18thPhsFinal_Rad_D_f32=MtrTrqRip18thPhs_Rad_T_f32;
	MtrTrq18thMagFinal_MtrNm_D_f32=MtrTrq18thMag_MtrNm_T_f32;
	
	/**************** Estimate ke*******************/

	IqtoTrqMulti_VpRadpS_T_f32= (EstKe_VpRadpS_T_f32 * D_SQRT3OVR2_ULS_F32 ) + ((((EstLq_Henry_T_f32-EstLd_Henry_T_f32)/2.0F)* DaxRef_Amp_T_f32) *(k_NoofPoles_Uls_f32*0.75F));

   /************************/
	MtrTrqRpl6Mag_MtrNm_M_f32[WriteAccessBufIndex_Cnt_T_u16] =  MtrTrq6thMag_MtrNm_T_f32;
	MtrTrqRpl12Mag_MtrNm_M_f32[WriteAccessBufIndex_Cnt_T_u16] = MtrTrq12thMag_MtrNm_T_f32;
	MtrTrq6Ph_Rad_M_f32[WriteAccessBufIndex_Cnt_T_u16] =     MtrTrqRip6thPhs_Rad_T_f32;
	MtrTrq12Ph_Rad_M_f32[WriteAccessBufIndex_Cnt_T_u16]  =   MtrTrqRip12thPhs_Rad_T_f32;
	MtrTrqRpl18Mag_MtrNm_M_f32[WriteAccessBufIndex_Cnt_T_u16] =MtrTrq18thMag_MtrNm_T_f32;
	MtrTrq18Ph_Rad_M_f32[WriteAccessBufIndex_Cnt_T_u16] =    MtrTrqRip18thPhs_Rad_T_f32;
	TrqCanc_IqtoTrqMulti_VpRadpS_M_f32[WriteAccessBufIndex_Cnt_T_u16] = IqtoTrqMulti_VpRadpS_T_f32;
	/* Configurable End of Runnable Checkpoint */
	Rte_Call_TrqCanc_Per1_CP1_CheckpointReached();
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: TrqCanc_Scom_ReadCogTrqCal
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadCogTrqCal> of PortPrototype <TrqCanc_Scom>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   void TrqCanc_Scom_ReadCogTrqCal(UInt16 *CogTrqCalPtr, UInt16 ID)
#else
 *   void TrqCanc_Scom_ReadCogTrqCal(CoggingCancTrq *CogTrqCalPtr, UInt16 ID)
#endif
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(void, RTE_AP_TRQCANC_APPL_CODE) TrqCanc_Scom_ReadCogTrqCal(P2VAR(UInt16, AUTOMATIC, RTE_AP_TRQCANC_APPL_VAR) CogTrqCalPtr, UInt16 ID)
#else
FUNC(void, RTE_AP_TRQCANC_APPL_CODE) TrqCanc_Scom_ReadCogTrqCal(P2VAR(CoggingCancTrq, AUTOMATIC, RTE_AP_TRQCANC_APPL_VAR) CogTrqCalPtr, UInt16 ID)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: TrqCanc_Scom_ReadCogTrqCal
 *********************************************************************************************************************/
	VAR(uint16, AUTOMATIC) i;
	if (ID <=3U)
		{
			for(i=0U; i<D_COGTRQ_LOOPLMT; i++)
				{
				(*CogTrqCalPtr)[i] = (*(Rte_Pim_CogTrqCal()))[i+(ID*D_COGTRQ_LOOPLMT)];
				}
		}
	else
		{
			for(i=0U;i<D_COGTRQRPL_LOOPLMT;i++)
					{
				(*CogTrqCalPtr)[i] = (*(Rte_Pim_CogTrqRplComp()))[i];
					}

		}




/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: TrqCanc_Scom_SetCogTrqCal
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <SetCogTrqCal> of PortPrototype <TrqCanc_Scom>
 *
 **********************************************************************************************************************
 *
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType Rte_Call_EOLCogTrqCanc_WriteBlock(const UInt8 *DstPtr)
#else
 *   Std_ReturnType Rte_Call_EOLCogTrqCanc_WriteBlock(const NvM_DestPtr *DstPtr)
#endif
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NvM_AC3_SRBS_Srv_E_NOT_OK
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType Rte_Call_EOLCogTrqRplComp_WriteBlock(const UInt8 *DstPtr)
#else
 *   Std_ReturnType Rte_Call_EOLCogTrqRplComp_WriteBlock(const NvM_DestPtr *DstPtr)
#endif
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NvM_AC3_SRBS_Srv_E_NOT_OK
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   void TrqCanc_Scom_SetCogTrqCal(const UInt16 *CogTrqCalPtr, UInt16 ID)
#else
 *   void TrqCanc_Scom_SetCogTrqCal(const CoggingCancTrq *CogTrqCalPtr, UInt16 ID)
#endif
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(void, RTE_AP_TRQCANC_APPL_CODE) TrqCanc_Scom_SetCogTrqCal(P2CONST(UInt16, AUTOMATIC, RTE_AP_TRQCANC_APPL_DATA) CogTrqCalPtr, UInt16 ID)
#else
FUNC(void, RTE_AP_TRQCANC_APPL_CODE) TrqCanc_Scom_SetCogTrqCal(P2CONST(CoggingCancTrq, AUTOMATIC, RTE_AP_TRQCANC_APPL_DATA) CogTrqCalPtr, UInt16 ID)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: TrqCanc_Scom_SetCogTrqCal
 *********************************************************************************************************************/
	VAR(uint16, AUTOMATIC) i;
	if (ID <= 3U)
	{
		for(i=0U;i<D_COGTRQ_LOOPLMT;i++)
		{
		(*(Rte_Pim_CogTrqCal()))[i+(ID*D_COGTRQ_LOOPLMT)]=(*CogTrqCalPtr)[i];
		}
		(void)Rte_Call_EOLCogTrqCanc_WriteBlock(NULL_PTR);
	}
	else
	{
		for(i=0U;i<D_COGTRQRPL_LOOPLMT;i++)
				{
				(*(Rte_Pim_CogTrqRplComp()))[i]=(*CogTrqCalPtr)[i];
				}

		(void)Rte_Call_EOLCogTrqRplComp_WriteBlock(NULL_PTR);
		(void)CoggingTrqTableUpdate( );
	}

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define RTE_STOP_SEC_AP_TRQCANC_APPL_CODE
#include "MemMap.h" /* PRQA S 5087 */


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of function definition area >>            DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/*****************************************************************************
 *
 *  Function Name:     CoggingTrqTableUpdate
 *	
 *  Description:       CoggingTrqTableUpdate
 *
 *  Inputs:           none
 *
 *  Outputs:          none
 *
 *****************************************************************************/
STATIC FUNC(void, AUTOMATIC )  CoggingTrqTableUpdate( void)
{
	VAR(sint16,  AUTOMATIC) CogTrqCalCompX_T_MtrNm_s2p13;
	VAR(sint16,  AUTOMATIC) CogTrqCalCompY_T_MtrNm_s2p13;
	VAR(CoggingM_MtrNm_Str,  AUTOMATIC) CogTrqCalComp_T_Cnt_str[D_NOOFHARMONIC_CNT_U8];
	VAR(uint16,  AUTOMATIC) i,j;
	
	/***CogTrqCalComp_T_Cnt_str 
	CogTrqCalComp_T_Cnt_str[0]=> 6th Harmonic
	CogTrqCalComp_T_Cnt_str[1]=> 12th Harmonic
	CogTrqCalComp_T_Cnt_str[2]=> 18th Harmonic
	The index starts from 512 
	Ignore the values at index 0, 3, 6 
	***/
	for (i=0u ; i < D_NOOFHARMONIC_CNT_U8; i++)
		{

					CogTrqCalCompX_T_MtrNm_s2p13 = FPM_Fix_m((sint16)((*(Rte_Pim_CogTrqRplComp()))[1u+(3u*i) ]),s5p10_T, s2p13_T)	;        /* PRQA S 4393 */  /* PRQA S 4394 */
					CogTrqCalCompX_T_MtrNm_s2p13 = Limit_m(CogTrqCalCompX_T_MtrNm_s2p13,D_MINCOGRANGE_NM_S2P13, D_MAXCOGRANGE_NM_S2P13);
					CogTrqCalComp_T_Cnt_str[i].CoggingMX_MtrNm_s2p13 = CogTrqCalCompX_T_MtrNm_s2p13;
					CogTrqCalCompY_T_MtrNm_s2p13 = FPM_Fix_m((sint16)((*(Rte_Pim_CogTrqRplComp()))[2u + (i*3u)]),s5p10_T, s2p13_T)	;           /* PRQA S 4393 */ /* PRQA S 4394 */
					CogTrqCalCompY_T_MtrNm_s2p13 = Limit_m(CogTrqCalCompY_T_MtrNm_s2p13,D_MINCOGRANGE_NM_S2P13, D_MAXCOGRANGE_NM_S2P13);
					CogTrqCalComp_T_Cnt_str[i].CoggingMY_MtrNm_s2p13 =CogTrqCalCompY_T_MtrNm_s2p13;


		}

		
	for (i=0u;i<D_DAXRPLTBLSZ_CNT_U8;i++)
	{
		for (j=0u; j<D_QAXRPLTBLSZ_CNT_U8;j++)
		{
			TrqCanc_MtrTrqRpl6X_MtrNm_M_s2p13[i][j] =  t2_MtrTrqRpl6X_MtrNm_s2p13[i][j]  +  CogTrqCalComp_T_Cnt_str[0].CoggingMX_MtrNm_s2p13;
			TrqCanc_MtrTrqRpl6Y_MtrNm_M_s2p13[i][j] =  t2_MtrTrqRpl6Y_MtrNm_s2p13[i][j]  +  CogTrqCalComp_T_Cnt_str[0].CoggingMY_MtrNm_s2p13;
			TrqCanc_MtrTrqRpl12X_MtrNm_M_s2p13[i][j] =  t2_MtrTrqRpl12X_MtrNm_s2p13[i][j] + CogTrqCalComp_T_Cnt_str[1].CoggingMX_MtrNm_s2p13;
			TrqCanc_MtrTrqRpl12Y_MtrNm_M_s2p13[i][j] =  t2_MtrTrqRpl12Y_MtrNm_s2p13[i][j] + CogTrqCalComp_T_Cnt_str[1].CoggingMY_MtrNm_s2p13;
			TrqCanc_MtrTrqRpl18X_MtrNm_M_s2p13[i][j] =  t2_MtrTrqRpl18X_MtrNm_s2p13[i][j] + CogTrqCalComp_T_Cnt_str[2].CoggingMX_MtrNm_s2p13;
			TrqCanc_MtrTrqRpl18Y_MtrNm_M_s2p13[i][j] =  t2_MtrTrqRpl18Y_MtrNm_s2p13[i][j] + CogTrqCalComp_T_Cnt_str[2].CoggingMY_MtrNm_s2p13;
		}
	}

}

/*****************************************************************************
 *
 *  Function Name:     SinLookup
 *	
 *  Description:       TrqCanc Sine lookup to improve throughput
 *
 *  Inputs:            Theta_Rad_T_f32  (angle in radians)
 *
 *  Outputs:           Result_Uls_T_f32 (Output sine value- Precision of p8)
 *
 *****************************************************************************/

STATIC FUNC(float32, AUTOMATIC) SinLookup( VAR(float32, AUTOMATIC) Theta_Rad_T_f32 )
{
	VAR(float32, AUTOMATIC) Theta_Rev_T_f32;
	VAR(uint16,  AUTOMATIC) Theta_Cnt_T_u16;
	VAR(boolean, AUTOMATIC) SignFlip_Cnt_T_lgc;
	VAR(float32, AUTOMATIC) Result_Uls_T_f32;
	
	Theta_Rev_T_f32 = Theta_Rad_T_f32 / D_2PI_ULS_F32;
	
	Theta_Rev_T_f32 = Theta_Rev_T_f32 - ((float32)((sint32)Theta_Rev_T_f32)); /* casting used for 'mod 1' functionality */
	
	if( Theta_Rev_T_f32 < 0.0f )
	{
		Theta_Rev_T_f32 += 1.0f;
	}
	
	/* Conditioned: 0 <= Theta <= 1 */
	
	if( Theta_Rev_T_f32 > 0.5f )
	{
		SignFlip_Cnt_T_lgc = TRUE;
		Theta_Rev_T_f32 -= 0.5f;
	}
	else
	{
		SignFlip_Cnt_T_lgc = FALSE;
	}
	
	if( Theta_Rev_T_f32 > 0.25f )
	{
		Theta_Rev_T_f32 = 0.5f - Theta_Rev_T_f32;
	}
	
	/* Conditioned: 0 <= Theta <= 0.25 */
	
	Theta_Cnt_T_u16 = (uint16)(uint32)(float32)(Theta_Rev_T_f32 * 2048.0f);
	
	Result_Uls_T_f32 = ((float32)t_SinTbl_Cnt_u16[Theta_Cnt_T_u16]) / 65535.0f;
	
	if( SignFlip_Cnt_T_lgc == TRUE )
	{
		Result_Uls_T_f32 = -Result_Uls_T_f32;
	}
	
	return Result_Uls_T_f32;
}

/*****************************************************************************
 *
 *  Function Name:     TrqCogCancRefPer1
 *	
 *  Description:       TrqCanc periodic called from Motor control ISR
 *
 *  Inputs:            None
 *
 *  Outputs:           None
 *
 *****************************************************************************/
FUNC(void, TrqCanc_CODE) TrqCogCancRefPer1(void)
{
		
		VAR(float32, AUTOMATIC) MtrTrqRpl12Mag_MtrNm_T_f32;
		VAR(float32, AUTOMATIC) MtrTrqRpl6Mag_MtrNm_T_f32;
		VAR(float32, AUTOMATIC) MtrTrqRpl18Mag_MtrNm_T_f32;
		VAR(float32, AUTOMATIC) CorrMtrPosElec_Rev_T_f32;
		VAR(float32, AUTOMATIC) CorrMtrPosElec_Rad_T_f32;
		VAR(uint16, AUTOMATIC) CogginTrqCancIndex_T_Cnt_u16;
		VAR(float32, AUTOMATIC) CoggingTrqCanc_MtrNm_T_f32;
		VAR(sint16, AUTOMATIC) CoggingTrqCanc_MtrNm_T_s5p10;
		VAR(float32, AUTOMATIC) CogginIqRef_Amp_T_f32;

		VAR(float32,AUTOMATIC) MtrPosComputDelay_Rad_T_f32;
		VAR(uint16, AUTOMATIC)  MtrPosComputDelay_Rev_T_u0p16;
		VAR(uint16, AUTOMATIC) PosDelayCorrMtrPosElec_Rev_T_u0p16;
		VAR(float32,AUTOMATIC) 	MtrTrq12Ph_Rad_T_f32;
		VAR(float32,AUTOMATIC) 	MtrTrq6Ph_Rad_T_f32;
		VAR(float32,AUTOMATIC) 	MtrTrq18Ph_Rad_T_f32;
		VAR(float32,AUTOMATIC) 	MtrPos6thHarAngle_Rad_T_f32;
		VAR(float32,AUTOMATIC) 	MtrPos12thHarAngle_Rad_T_f32;
		VAR(sint8,AUTOMATIC) 	MtrElecPol_Cnt_T_s8;
		VAR(uint16, AUTOMATIC) 	MtrPosElec_Rev_T_u0p16;
		VAR(uint16, AUTOMATIC) 	DataAccessBfr_Cnt_T_u16;
		VAR(float32,AUTOMATIC) 	MtrPos18thHarAngle_Rad_T_f32;
		VAR(float32, AUTOMATIC) MtrTrqRpl_MtrNm_T_f32;
		VAR(float32, AUTOMATIC) IqtoTrqMulti_VpRadpS_T_f32;
		
		DataAccessBfr_Cnt_T_u16 =FastDataAccessBufIndex_Cnt_M_u16;
		MtrCntrl_Read_MtrElecPol_Cnt_s8(&MtrElecPol_Cnt_T_s8);
		MtrCntrl_Read_MtrPosElec_Rev_u0p16(&MtrPosElec_Rev_T_u0p16);
		/*** read the inputs as global macros ***/
		MtrPosComputDelay_Rad_T_f32=MtrCtrl_MtrPosComputationDelayRpl_Rad_M_f32[DataAccessBfr_Cnt_T_u16];
		MtrTrqRpl6Mag_MtrNm_T_f32 =MtrTrqRpl6Mag_MtrNm_M_f32[DataAccessBfr_Cnt_T_u16] ;
		MtrTrqRpl12Mag_MtrNm_T_f32=MtrTrqRpl12Mag_MtrNm_M_f32[DataAccessBfr_Cnt_T_u16] ;
	    MtrTrq6Ph_Rad_T_f32  =MtrTrq6Ph_Rad_M_f32[DataAccessBfr_Cnt_T_u16] ;
		MtrTrq12Ph_Rad_T_f32 =MtrTrq12Ph_Rad_M_f32[DataAccessBfr_Cnt_T_u16] ;
		MtrTrqRpl18Mag_MtrNm_T_f32=MtrTrqRpl18Mag_MtrNm_M_f32[DataAccessBfr_Cnt_T_u16] ;
	    MtrTrq18Ph_Rad_T_f32  =MtrTrq18Ph_Rad_M_f32[DataAccessBfr_Cnt_T_u16] ;
		IqtoTrqMulti_VpRadpS_T_f32 = TrqCanc_IqtoTrqMulti_VpRadpS_M_f32[DataAccessBfr_Cnt_T_u16] ;

		/***Cogging torque***/
		if (MtrPosComputDelay_Rad_T_f32 < D_ZERO_ULS_F32)
		{
				MtrPosComputDelay_Rev_T_u0p16 = (uint16)(uint32)(float32)((MtrPosComputDelay_Rad_T_f32 * D_SCALERADTOCNTS_ULS_F32) + D_REVWITHROUND_ULS_F32);
		}
		else
		{
				MtrPosComputDelay_Rev_T_u0p16 = (uint16)(uint32)(float32)((MtrPosComputDelay_Rad_T_f32 * D_SCALERADTOCNTS_ULS_F32) + D_ONEHALF_ULS_F32);
		}

		if(MtrElecPol_Cnt_T_s8 == D_ONE_CNT_S8)
			{
				PosDelayCorrMtrPosElec_Rev_T_u0p16=(uint16)((MtrPosElec_Rev_T_u0p16-D_30DEGREES_CNT_U16)+MtrPosComputDelay_Rev_T_u0p16);
			}
			else
			{
				PosDelayCorrMtrPosElec_Rev_T_u0p16=(uint16)((MtrPosElec_Rev_T_u0p16+D_30DEGREES_CNT_U16)+MtrPosComputDelay_Rev_T_u0p16);
			}

			CorrMtrPosElec_Rev_T_f32= FPM_FixedToFloat_m(PosDelayCorrMtrPosElec_Rev_T_u0p16,u0p16_T);

			CoggingTrqMtrPosElec_Rev_D_f32=CorrMtrPosElec_Rev_T_f32;
			
			
			/***** Iq Cogging torque Compenastion function   *****/
			CorrMtrPosElec_Rad_T_f32 =CorrMtrPosElec_Rev_T_f32*D_2PI_ULS_F32;
			CogginTrqCancIndex_T_Cnt_u16=FPM_FloatToFixed_m(((CorrMtrPosElec_Rad_T_f32)*D_COGGINGTBLRES_F32),u16p0_T);    /* PRQA S 4395 */
			
			
			if(CogginTrqCancIndex_T_Cnt_u16>D_MAXTBLVALUE_CNT_U16)
			{
				CogginTrqCancIndex_T_Cnt_u16=D_MAXTBLVALUE_CNT_U16;
			}

			CogginTrqCancIndex_Cnt_D_u16=CogginTrqCancIndex_T_Cnt_u16;

			CoggingTrqCanc_MtrNm_T_s5p10=(sint16)(*Rte_Pim_CogTrqCal())[CogginTrqCancIndex_T_Cnt_u16];
			CoggingTrqCanc_MtrNm_T_s5p10 = Limit_m(CoggingTrqCanc_MtrNm_T_s5p10,D_MINCOGRANGE_NM_S5P10, D_MAXCOGRANGE_NM_S5P10);
			CoggingTrqCanc_MtrNm_T_f32=FPM_FixedToFloat_m(CoggingTrqCanc_MtrNm_T_s5p10,s5p10_T);
			CoggingTrqCanc_MtrNm_D_f32=CoggingTrqCanc_MtrNm_T_f32;
			
			CogginIqRef_Amp_T_f32=(CoggingTrqCanc_MtrNm_T_f32/(IqtoTrqMulti_VpRadpS_T_f32));
			
			/***** Torque Ripple Compensation Effect *****/

			MtrPos6thHarAngle_Rad_T_f32=MtrTrq6Ph_Rad_T_f32 + (k_Harmonic6thElec_Uls_f32*CorrMtrPosElec_Rad_T_f32) ;
			MtrPos12thHarAngle_Rad_T_f32=MtrTrq12Ph_Rad_T_f32 + (k_Harmonic12thElec_Uls_f32*CorrMtrPosElec_Rad_T_f32);
			MtrPos18thHarAngle_Rad_T_f32 = MtrTrq18Ph_Rad_T_f32 + (k_Harmonic18thElec_Uls_f32*CorrMtrPosElec_Rad_T_f32);
				
		
		    MtrTrqRpl_MtrNm_T_f32=((MtrTrqRpl6Mag_MtrNm_T_f32*SinLookup(MtrPos6thHarAngle_Rad_T_f32))+(MtrTrqRpl12Mag_MtrNm_T_f32*SinLookup(MtrPos12thHarAngle_Rad_T_f32))+(MtrTrqRpl18Mag_MtrNm_T_f32*SinLookup(MtrPos18thHarAngle_Rad_T_f32)));
		    TrqCanc_MtrTrqRpl_MtrNm_D_f32= MtrTrqRpl_MtrNm_T_f32;
				
			/* Updating glbal variable buffers*/
			MtrCurrQaxRpl_Amp_M_f32[SlowDataAccessBufIndex_Cnt_M_u16]= (MtrTrqRpl_MtrNm_T_f32/IqtoTrqMulti_VpRadpS_T_f32);
			MtrCurrQaxCog_Amp_M_f32 = CogginIqRef_Amp_T_f32;
		


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
