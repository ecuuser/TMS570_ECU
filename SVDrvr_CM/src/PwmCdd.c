/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : PwmCdd.c
* Module Description: Non-AUTOSAR PWM driver required to perform EPS motor
*                      control PWM profiles.
* Product           : Gen II Plus - EA3.0
* Author            : Jeremy Warmbier
*****************************************************************************/

/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Thu Dec 16 13:41:03 2010
* %version:          3 %
* %derived_by:       nzt9hv %
* %date_modified:    Tue Jan 21 16:39:33 2014 % 
******************************************************************************

*CHANGE HISTORY:
*
* Date      Rev      Author          Change Description               SCR #
*                                     (MDD Rev & Date)
*-------   -------  --------  -----------------------------------   ----------
*12/16/10   1.0     JJW        Initial Creation                     N/A
*12/21/10   2.0     LWW        Fixed array indexing errors
*12/21/10   3.0     LWW        Fixed typo
*12/23/10   4.0     LWW        Added polarity implementation
*01/13/11   5.0     LWW        Removed Gate Drive Fault boolean
*01/24/11   6.0     LWW        Changed ADC sample offsets to calibrations
*02/01/11   7.0     LWW        Changes to support phase reasonableness
*03/24/11   8.0     JJW        Clk Freq Updates for 80MHz VCLK
*04/15/11   9.0     JJW        Clk Freq Updates for 65MHz VCLK
*10/13/11   11.0    LWW        Clk Freq Updates for 80MHz VCLK
*12/13/11   11.1.1  JJW        Phase Adv x8 resolution increase
*01/30/12   13      LWW        Header name change for Nhet component
*02/27/12   14      RR		  PhaseAdvance and Polarity Changes for Current Mode
*03/07/12   15      RR         DutyCycle B and C Output for Cm_MtrCurr Offset
*07/27/12   16      JJW        Removed FET fault mitigation processing
*							  Changed direct Nhet program structure access to 
*							  abstracted API to support HTU use integration
*07/31/12   17      JJW        Removed FET fault mitigation remanent from 
*								DeadTimeComp_u16p0().
*10/24/12	19	   Selva	   Component split to match requirement FDD 15C 
*12/06/12   18.1.1      JJW        Corrected CDD_MtrPosElec_Rev_G_u0p16 access indexer
							  Removed support for analog phase reasonableness
*02/05/13   18.1.2      JJW        Added configurable access to CorrectedMtrPos and 
								CDD_Read_CommOffset_Cnt_u16.  Change made to provide
								abstraction of buffering mechanisim.
*02/13/13   20      Selva     Merged the changes of 18.1.2 to 19 and changed names depandent on NHET to common CDD name
*04/19/13   21      Selva     Changed the Buffer index of CDD_ModIdxFinal_Uls_G_u16p16 from "CDD_AppDataFwdPthAccessBfr_Cnt_G_u16" to "CDD_CDDDataAccessBfr_Cnt_G_u16"
*08/30/13   22      OT        Moved PWM frequency define into config header
**** Refer the component SVDrvr for the past revisions. ****
*11/01/13   1     Selva     Split the PwmCdd.C from SVDrvr. Removed the Dead time compensation.  CR10668
*21/01/14   2		LK		Replaced d_PWMFreqBase_Hz_u16Added with k_PWMBaseFrequency_Hz_u16
									 d_PwmPrdMax_Cnt_u16 with PwmCdd_PWMPrdMax_Cnt_M_u16  and   
									 d_PwmPrdMin_Cnt_u16 with PwmCdd_PWMPrdMin_Cnt_M_u16		
									 d_PwmPrdRange_Cnt_u16 with PwmCdd_PWMPrdRange_Cnt_M_u16
							removed  d_PwmPrdInitVal_Cnt_u16 which is not used.			         CR11012
*08/11/15   3     Selva     Replaced CDD_ModIdxFinal_Uls_G_u16p16 with 	ModIdxFinal_Uls_T_u16p16 for 83,3hz noise   EA3#2631					
******************************************************************************/

#include "Std_Types.h"
#include "PwmCdd.h"
#include "PwmCdd_Cfg.h"
#include "CDD_Data.h"
#include "CalConstants.h"
#include "fixmath.h"
#include "GlobalMacro.h"
#include "CDD_Func.h"

/*************************/
/* Variable Definitions  */
/*************************/
#define PWMCDD_START_SEC_VAR_CLEARED_16
#include "MemMap.h"  /* PRQA S 5087 */

STATIC VAR(uint16, PWMCDD_VAR_NOINIT) CDD_SeedPWMDither_Cnt_M_u16;
STATIC VAR(uint16, PWMCDD_VAR_NOINIT) CDD_DitherFlt1SV_Cnt_M_u16;
STATIC VAR(uint16, PWMCDD_VAR_NOINIT) CDD_DitherFlt2SV_Cnt_M_u16;
STATIC VAR(uint16, PWMCDD_VAR_NOINIT) CDD_PhaseOffset_Rev_M_u0p16[3];
STATIC VAR(uint16, PWMCDD_VAR_NOINIT) PrevDCPhsAComp_Cnt_M_u16p0;
STATIC VAR(uint16, PWMCDD_VAR_NOINIT) PrevDCPhsBComp_Cnt_M_u16p0;
STATIC VAR(uint16, PWMCDD_VAR_NOINIT) PrevDCPhsCComp_Cnt_M_u16p0;
STATIC VAR(uint16, PWMCDD_VAR_NOINIT) DCPhsAComp_Cnt_M_u16p0;
STATIC VAR(uint16, PWMCDD_VAR_NOINIT) DCPhsBComp_Cnt_M_u16p0;
STATIC VAR(uint16, PWMCDD_VAR_NOINIT) DCPhsCComp_Cnt_M_u16p0;
STATIC VAR(uint16, PWMCDD_VAR_NOINIT) PrevPWMPeriod_Cnt_M_u16;
STATIC VAR(uint16, PWMCDD_VAR_NOINIT) PWMPeriod_Cnt_M_u16;
STATIC VAR(uint16, PWMCDD_VAR_NOINIT) PwmCdd_PWMPrdMax_Cnt_M_u16;
STATIC VAR(uint16, PWMCDD_VAR_NOINIT) PwmCdd_PWMPrdMin_Cnt_M_u16;
STATIC VAR(uint16, PWMCDD_VAR_NOINIT) PwmCdd_PWMPrdRange_Cnt_M_u16;

#define PWMCDD_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"  /* PRQA S 5087 */



/*************************/
/* Constants             */
/*************************/

#define d_HalfPrec16_Cnt_u16            32768UL
#define d_Scaler1_Cnt_u16               1U 
#define d_Scaler16_Cnt_u16              16U 
#define d_SeedInitial_Cnt_u16           10U 
#define d_SeedMultiplier_Cnt_u16        57U  
#define d_SeedOffset_Cnt_u16            1U
#define d_FilterKdBits_Cnt_U16			5U 
#define d_MaxModIdx_Uls_u0p16           (FPM_InitFixedPoint_m(0.9999847412109375, u0p16_T))
#define d_MinModIdx_Uls_u0p16           (FPM_InitFixedPoint_m(0.0, u0p16_T))
#define d_120Deg_Rev_u0p16			(FPM_InitFixedPoint_m(0.3333333333, u0p16_T))
#define d_0Deg_Rev_u0p16				(FPM_InitFixedPoint_m(0.0, u0p16_T))
#define d_30Deg_Rev_u0p16				(FPM_InitFixedPoint_m(0.0833333333, u0p16_T))
#define d_60Deg_Rev_u0p16				(FPM_InitFixedPoint_m(0.1666666666, u0p16_T))
#define d_240Deg_Rev_u0p16			(FPM_InitFixedPoint_m(0.6666666666, u0p16_T))
#define d_180Deg_Rev_u0p16			(FPM_InitFixedPoint_m(0.5, u0p16_T))
#define d_PhaseAOffsetNrm_Rev_u0p16	d_0Deg_Rev_u0p16
#define d_PhaseBOffsetNrm_Rev_u0p16	((uint16)(d_PhaseAOffsetNrm_Rev_u0p16 - d_120Deg_Rev_u0p16))
#define d_PhaseCOffsetNrm_Rev_u0p16	(d_PhaseAOffsetNrm_Rev_u0p16 + d_120Deg_Rev_u0p16)
#define d_PhaseAOffsetInv_Rev_u0p16	d_60Deg_Rev_u0p16
#define d_PhaseBOffsetInv_Rev_u0p16	(d_PhaseAOffsetInv_Rev_u0p16 + d_120Deg_Rev_u0p16)
#define d_PhaseCOffsetInv_Rev_u0p16	((uint16)(d_PhaseAOffsetInv_Rev_u0p16 - d_120Deg_Rev_u0p16))
#define d_RevpCnt_Uls_u0p32			699051UL		/* (FPM_InitFixedPoint_m(1/d_PACntspRev_Uls_u16p0, u0p32_T)) */
#define d_PACntspRev_Uls_u16p0		6144U
#define d_SinePhsToGndTblSize_Cnt_u16   2049U
#define d_MSBMask_Cnt_u16               0x8000U
#define D_POSITIVEONE_CNT_S8            1

#define D_PHSAIDX_CNT_U16  0U    
#define D_PHSBIDX_CNT_U16  1U
#define D_PHSCIDX_CNT_U16  2U


STATIC CONST(uint16, AUTOMATIC) t_S_SinePhsToGndTbl_Cnt_u0p16[d_SinePhsToGndTblSize_Cnt_u16] = 
{
	56755U, 56788U, 56822U, 56855U, 56889U, 56922U, 56955U, 56988U, 57021U, 57054U, 57087U, 57120U, 57153U, 57186U, 57218U, 57251U,
	57284U, 57316U, 57349U, 57381U, 57413U, 57446U, 57478U, 57510U, 57542U, 57574U, 57606U, 57638U, 57670U, 57702U, 57733U, 57765U,
	57797U, 57828U, 57860U, 57891U, 57923U, 57954U, 57985U, 58016U, 58048U, 58079U, 58110U, 58141U, 58171U, 58202U, 58233U, 58264U,
	58294U, 58325U, 58356U, 58386U, 58416U, 58447U, 58477U, 58507U, 58537U, 58568U, 58598U, 58628U, 58657U, 58687U, 58717U, 58747U,
	58777U, 58806U, 58836U, 58865U, 58895U, 58924U, 58953U, 58983U, 59012U, 59041U, 59070U, 59099U, 59128U, 59157U, 59186U, 59214U,
	59243U, 59272U, 59300U, 59329U, 59357U, 59385U, 59414U, 59442U, 59470U, 59498U, 59526U, 59554U, 59582U, 59610U, 59638U, 59666U,
	59693U, 59721U, 59749U, 59776U, 59804U, 59831U, 59858U, 59886U, 59913U, 59940U, 59967U, 59994U, 60021U, 60048U, 60075U, 60101U,
	60128U, 60155U, 60181U, 60208U, 60234U, 60260U, 60287U, 60313U, 60339U, 60365U, 60391U, 60417U, 60443U, 60469U, 60495U, 60521U,
	60546U, 60572U, 60598U, 60623U, 60649U, 60674U, 60699U, 60724U, 60750U, 60775U, 60800U, 60825U, 60850U, 60874U, 60899U, 60924U,
	60949U, 60973U, 60998U, 61022U, 61047U, 61071U, 61095U, 61120U, 61144U, 61168U, 61192U, 61216U, 61240U, 61263U, 61287U, 61311U,
	61335U, 61358U, 61382U, 61405U, 61429U, 61452U, 61475U, 61498U, 61521U, 61544U, 61567U, 61590U, 61613U, 61636U, 61659U, 61681U,
	61704U, 61727U, 61749U, 61772U, 61794U, 61816U, 61838U, 61861U, 61883U, 61905U, 61927U, 61949U, 61970U, 61992U, 62014U, 62035U,
	62057U, 62079U, 62100U, 62121U, 62143U, 62164U, 62185U, 62206U, 62227U, 62248U, 62269U, 62290U, 62311U, 62332U, 62352U, 62373U,
	62393U, 62414U, 62434U, 62455U, 62475U, 62495U, 62515U, 62535U, 62555U, 62575U, 62595U, 62615U, 62635U, 62654U, 62674U, 62694U,
	62713U, 62733U, 62752U, 62771U, 62790U, 62810U, 62829U, 62848U, 62867U, 62886U, 62904U, 62923U, 62942U, 62960U, 62979U, 62998U,
	63016U, 63034U, 63053U, 63071U, 63089U, 63107U, 63125U, 63143U, 63161U, 63179U, 63197U, 63214U, 63232U, 63250U, 63267U, 63285U,
	63302U, 63319U, 63337U, 63354U, 63371U, 63388U, 63405U, 63422U, 63439U, 63455U, 63472U, 63489U, 63505U, 63522U, 63538U, 63555U,
	63571U, 63587U, 63603U, 63620U, 63636U, 63652U, 63668U, 63683U, 63699U, 63715U, 63731U, 63746U, 63762U, 63777U, 63792U, 63808U,
	63823U, 63838U, 63853U, 63868U, 63883U, 63898U, 63913U, 63928U, 63943U, 63957U, 63972U, 63986U, 64001U, 64015U, 64030U, 64044U,
	64058U, 64072U, 64086U, 64100U, 64114U, 64128U, 64142U, 64155U, 64169U, 64183U, 64196U, 64210U, 64223U, 64236U, 64249U, 64263U,
	64276U, 64289U, 64302U, 64315U, 64328U, 64340U, 64353U, 64366U, 64378U, 64391U, 64403U, 64416U, 64428U, 64440U, 64452U, 64464U,
	64476U, 64488U, 64500U, 64512U, 64524U, 64535U, 64547U, 64559U, 64570U, 64582U, 64593U, 64604U, 64615U, 64627U, 64638U, 64649U,
	64660U, 64671U, 64681U, 64692U, 64703U, 64713U, 64724U, 64734U, 64745U, 64755U, 64765U, 64776U, 64786U, 64796U, 64806U, 64816U,
	64826U, 64835U, 64845U, 64855U, 64864U, 64874U, 64883U, 64893U, 64902U, 64911U, 64921U, 64930U, 64939U, 64948U, 64957U, 64966U,
	64974U, 64983U, 64992U, 65000U, 65009U, 65017U, 65026U, 65034U, 65042U, 65050U, 65058U, 65066U, 65074U, 65082U, 65090U, 65098U,
	65106U, 65113U, 65121U, 65128U, 65136U, 65143U, 65150U, 65158U, 65165U, 65172U, 65179U, 65186U, 65193U, 65199U, 65206U, 65213U,
	65219U, 65226U, 65232U, 65239U, 65245U, 65251U, 65258U, 65264U, 65270U, 65276U, 65282U, 65288U, 65293U, 65299U, 65305U, 65310U,
	65316U, 65321U, 65327U, 65332U, 65337U, 65342U, 65347U, 65352U, 65357U, 65362U, 65367U, 65372U, 65377U, 65381U, 65386U, 65390U,
	65395U, 65399U, 65403U, 65408U, 65412U, 65416U, 65420U, 65424U, 65428U, 65431U, 65435U, 65439U, 65442U, 65446U, 65449U, 65453U,
	65456U, 65459U, 65463U, 65466U, 65469U, 65472U, 65475U, 65477U, 65480U, 65483U, 65486U, 65488U, 65491U, 65493U, 65495U, 65498U,
	65500U, 65502U, 65504U, 65506U, 65508U, 65510U, 65512U, 65514U, 65515U, 65517U, 65518U, 65520U, 65521U, 65523U, 65524U, 65525U,
	65526U, 65527U, 65528U, 65529U, 65530U, 65531U, 65532U, 65532U, 65533U, 65533U, 65534U, 65534U, 65534U, 65535U, 65535U, 65535U,
	65535U, 65535U, 65535U, 65535U, 65534U, 65534U, 65534U, 65533U, 65533U, 65532U, 65532U, 65531U, 65530U, 65529U, 65528U, 65527U,
	65526U, 65525U, 65524U, 65523U, 65521U, 65520U, 65518U, 65517U, 65515U, 65514U, 65512U, 65510U, 65508U, 65506U, 65504U, 65502U,
	65500U, 65498U, 65495U, 65493U, 65491U, 65488U, 65486U, 65483U, 65480U, 65477U, 65475U, 65472U, 65469U, 65466U, 65463U, 65459U,
	65456U, 65453U, 65449U, 65446U, 65442U, 65439U, 65435U, 65431U, 65428U, 65424U, 65420U, 65416U, 65412U, 65408U, 65403U, 65399U,
	65395U, 65390U, 65386U, 65381U, 65377U, 65372U, 65367U, 65362U, 65357U, 65352U, 65347U, 65342U, 65337U, 65332U, 65327U, 65321U,
	65316U, 65310U, 65305U, 65299U, 65293U, 65288U, 65282U, 65276U, 65270U, 65264U, 65258U, 65251U, 65245U, 65239U, 65232U, 65226U,
	65219U, 65213U, 65206U, 65199U, 65193U, 65186U, 65179U, 65172U, 65165U, 65158U, 65150U, 65143U, 65136U, 65128U, 65121U, 65113U,
	65106U, 65098U, 65090U, 65082U, 65074U, 65066U, 65058U, 65050U, 65042U, 65034U, 65026U, 65017U, 65009U, 65000U, 64992U, 64983U,
	64974U, 64966U, 64957U, 64948U, 64939U, 64930U, 64921U, 64911U, 64902U, 64893U, 64883U, 64874U, 64864U, 64855U, 64845U, 64835U,
	64826U, 64816U, 64806U, 64796U, 64786U, 64776U, 64765U, 64755U, 64745U, 64734U, 64724U, 64713U, 64703U, 64692U, 64681U, 64671U,
	64660U, 64649U, 64638U, 64627U, 64615U, 64604U, 64593U, 64582U, 64570U, 64559U, 64547U, 64535U, 64524U, 64512U, 64500U, 64488U,
	64476U, 64464U, 64452U, 64440U, 64428U, 64416U, 64403U, 64391U, 64378U, 64366U, 64353U, 64340U, 64328U, 64315U, 64302U, 64289U,
	64276U, 64263U, 64249U, 64236U, 64223U, 64210U, 64196U, 64183U, 64169U, 64155U, 64142U, 64128U, 64114U, 64100U, 64086U, 64072U,
	64058U, 64044U, 64030U, 64015U, 64001U, 63986U, 63972U, 63957U, 63943U, 63928U, 63913U, 63898U, 63883U, 63868U, 63853U, 63838U,
	63823U, 63808U, 63792U, 63777U, 63762U, 63746U, 63731U, 63715U, 63699U, 63683U, 63668U, 63652U, 63636U, 63620U, 63603U, 63587U,
	63571U, 63555U, 63538U, 63522U, 63505U, 63489U, 63472U, 63455U, 63439U, 63422U, 63405U, 63388U, 63371U, 63354U, 63337U, 63319U,
	63302U, 63285U, 63267U, 63250U, 63232U, 63214U, 63197U, 63179U, 63161U, 63143U, 63125U, 63107U, 63089U, 63071U, 63053U, 63034U,
	63016U, 62998U, 62979U, 62960U, 62942U, 62923U, 62904U, 62886U, 62867U, 62848U, 62829U, 62810U, 62790U, 62771U, 62752U, 62733U,
	62713U, 62694U, 62674U, 62654U, 62635U, 62615U, 62595U, 62575U, 62555U, 62535U, 62515U, 62495U, 62475U, 62455U, 62434U, 62414U,
	62393U, 62373U, 62352U, 62332U, 62311U, 62290U, 62269U, 62248U, 62227U, 62206U, 62185U, 62164U, 62143U, 62121U, 62100U, 62079U,
	62057U, 62035U, 62014U, 61992U, 61970U, 61949U, 61927U, 61905U, 61883U, 61861U, 61838U, 61816U, 61794U, 61772U, 61749U, 61727U,
	61704U, 61681U, 61659U, 61636U, 61613U, 61590U, 61567U, 61544U, 61521U, 61498U, 61475U, 61452U, 61429U, 61405U, 61382U, 61358U,
	61335U, 61311U, 61287U, 61263U, 61240U, 61216U, 61192U, 61168U, 61144U, 61120U, 61095U, 61071U, 61047U, 61022U, 60998U, 60973U,
	60949U, 60924U, 60899U, 60874U, 60850U, 60825U, 60800U, 60775U, 60750U, 60724U, 60699U, 60674U, 60649U, 60623U, 60598U, 60572U,
	60546U, 60521U, 60495U, 60469U, 60443U, 60417U, 60391U, 60365U, 60339U, 60313U, 60287U, 60260U, 60234U, 60208U, 60181U, 60155U,
	60128U, 60101U, 60075U, 60048U, 60021U, 59994U, 59967U, 59940U, 59913U, 59886U, 59858U, 59831U, 59804U, 59776U, 59749U, 59721U,
	59693U, 59666U, 59638U, 59610U, 59582U, 59554U, 59526U, 59498U, 59470U, 59442U, 59414U, 59385U, 59357U, 59329U, 59300U, 59272U,
	59243U, 59214U, 59186U, 59157U, 59128U, 59099U, 59070U, 59041U, 59012U, 58983U, 58953U, 58924U, 58895U, 58865U, 58836U, 58806U,
	58777U, 58747U, 58717U, 58687U, 58657U, 58628U, 58598U, 58568U, 58537U, 58507U, 58477U, 58447U, 58416U, 58386U, 58356U, 58325U,
	58294U, 58264U, 58233U, 58202U, 58171U, 58141U, 58110U, 58079U, 58048U, 58016U, 57985U, 57954U, 57923U, 57891U, 57860U, 57828U,
	57797U, 57765U, 57733U, 57702U, 57670U, 57638U, 57606U, 57574U, 57542U, 57510U, 57478U, 57446U, 57413U, 57381U, 57349U, 57316U,
	57284U, 57251U, 57218U, 57186U, 57153U, 57120U, 57087U, 57054U, 57021U, 56988U, 56955U, 56922U, 56889U, 56855U, 56822U, 56788U,
	56755U, 56721U, 56688U, 56654U, 56620U, 56587U, 56553U, 56519U, 56485U, 56451U, 56417U, 56383U, 56349U, 56314U, 56280U, 56246U,
	56211U, 56177U, 56142U, 56108U, 56073U, 56038U, 56003U, 55969U, 55934U, 55899U, 55864U, 55829U, 55794U, 55758U, 55723U, 55688U,
	55652U, 55617U, 55582U, 55546U, 55510U, 55475U, 55439U, 55403U, 55367U, 55332U, 55296U, 55260U, 55224U, 55187U, 55151U, 55115U,
	55079U, 55042U, 55006U, 54970U, 54933U, 54896U, 54860U, 54823U, 54786U, 54750U, 54713U, 54676U, 54639U, 54602U, 54565U, 54528U,
	54490U, 54453U, 54416U, 54378U, 54341U, 54303U, 54266U, 54228U, 54191U, 54153U, 54115U, 54077U, 54039U, 54002U, 53964U, 53925U,
	53887U, 53849U, 53811U, 53773U, 53734U, 53696U, 53657U, 53619U, 53580U, 53542U, 53503U, 53464U, 53426U, 53387U, 53348U, 53309U,
	53270U, 53231U, 53192U, 53153U, 53113U, 53074U, 53035U, 52995U, 52956U, 52916U, 52877U, 52837U, 52797U, 52758U, 52718U, 52678U,
	52638U, 52598U, 52558U, 52518U, 52478U, 52438U, 52398U, 52357U, 52317U, 52277U, 52236U, 52196U, 52155U, 52115U, 52074U, 52033U,
	51992U, 51952U, 51911U, 51870U, 51829U, 51788U, 51747U, 51705U, 51664U, 51623U, 51582U, 51540U, 51499U, 51457U, 51416U, 51374U,
	51333U, 51291U, 51249U, 51207U, 51166U, 51124U, 51082U, 51040U, 50998U, 50956U, 50913U, 50871U, 50829U, 50787U, 50744U, 50702U,
	50659U, 50617U, 50574U, 50531U, 50489U, 50446U, 50403U, 50360U, 50317U, 50274U, 50231U, 50188U, 50145U, 50102U, 50059U, 50016U,
	49972U, 49929U, 49885U, 49842U, 49798U, 49755U, 49711U, 49667U, 49624U, 49580U, 49536U, 49492U, 49448U, 49404U, 49360U, 49316U,
	49272U, 49228U, 49183U, 49139U, 49095U, 49050U, 49006U, 48961U, 48917U, 48872U, 48827U, 48783U, 48738U, 48693U, 48648U, 48603U,
	48558U, 48513U, 48468U, 48423U, 48378U, 48333U, 48287U, 48242U, 48197U, 48151U, 48106U, 48060U, 48014U, 47969U, 47923U, 47877U,
	47832U, 47786U, 47740U, 47694U, 47648U, 47602U, 47556U, 47510U, 47464U, 47417U, 47371U, 47325U, 47278U, 47232U, 47185U, 47139U,
	47092U, 47046U, 46999U, 46952U, 46905U, 46859U, 46812U, 46765U, 46718U, 46671U, 46624U, 46577U, 46529U, 46482U, 46435U, 46388U,
	46340U, 46293U, 46245U, 46198U, 46150U, 46103U, 46055U, 46007U, 45960U, 45912U, 45864U, 45816U, 45768U, 45720U, 45672U, 45624U,
	45576U, 45528U, 45479U, 45431U, 45383U, 45334U, 45286U, 45238U, 45189U, 45140U, 45092U, 45043U, 44995U, 44946U, 44897U, 44848U,
	44799U, 44750U, 44701U, 44652U, 44603U, 44554U, 44505U, 44456U, 44406U, 44357U, 44308U, 44258U, 44209U, 44159U, 44110U, 44060U,
	44011U, 43961U, 43911U, 43861U, 43812U, 43762U, 43712U, 43662U, 43612U, 43562U, 43512U, 43462U, 43411U, 43361U, 43311U, 43261U,
	43210U, 43160U, 43109U, 43059U, 43008U, 42958U, 42907U, 42856U, 42806U, 42755U, 42704U, 42653U, 42602U, 42551U, 42500U, 42449U,
	42398U, 42347U, 42296U, 42245U, 42194U, 42142U, 42091U, 42039U, 41988U, 41937U, 41885U, 41833U, 41782U, 41730U, 41678U, 41627U,
	41575U, 41523U, 41471U, 41419U, 41367U, 41315U, 41263U, 41211U, 41159U, 41107U, 41055U, 41002U, 40950U, 40898U, 40845U, 40793U,
	40741U, 40688U, 40635U, 40583U, 40530U, 40478U, 40425U, 40372U, 40319U, 40266U, 40213U, 40161U, 40108U, 40055U, 40001U, 39948U,
	39895U, 39842U, 39789U, 39735U, 39682U, 39629U, 39575U, 39522U, 39468U, 39415U, 39361U, 39308U, 39254U, 39200U, 39147U, 39093U,
	39039U, 38985U, 38931U, 38877U, 38824U, 38769U, 38715U, 38661U, 38607U, 38553U, 38499U, 38445U, 38390U, 38336U, 38282U, 38227U,
	38173U, 38118U, 38064U, 38009U, 37954U, 37900U, 37845U, 37790U, 37736U, 37681U, 37626U, 37571U, 37516U, 37461U, 37406U, 37351U,
	37296U, 37241U, 37186U, 37130U, 37075U, 37020U, 36965U, 36909U, 36854U, 36798U, 36743U, 36687U, 36632U, 36576U, 36521U, 36465U,
	36409U, 36354U, 36298U, 36242U, 36186U, 36130U, 36074U, 36018U, 35962U, 35906U, 35850U, 35794U, 35738U, 35682U, 35625U, 35569U,
	35513U, 35457U, 35400U, 35344U, 35287U, 35231U, 35174U, 35118U, 35061U, 35004U, 34948U, 34891U, 34834U, 34778U, 34721U, 34664U,
	34607U, 34550U, 34493U, 34436U, 34379U, 34322U, 34265U, 34208U, 34150U, 34093U, 34036U, 33979U, 33921U, 33864U, 33807U, 33749U,
	33692U, 33634U, 33577U, 33519U, 33462U, 33404U, 33346U, 33288U, 33231U, 33173U, 33115U, 33057U, 32999U, 32941U, 32884U, 32826U,
	32768U, 32709U, 32651U, 32593U, 32535U, 32477U, 32419U, 32360U, 32302U, 32244U, 32185U, 32127U, 32069U, 32010U, 31952U, 31893U,
	31835U, 31776U, 31717U, 31659U, 31600U, 31541U, 31482U, 31424U, 31365U, 31306U, 31247U, 31188U, 31129U, 31070U, 31011U, 30952U,
	30893U, 30834U, 30775U, 30716U, 30656U, 30597U, 30538U, 30478U, 30419U, 30360U, 30300U, 30241U, 30181U, 30122U, 30062U, 30003U,
	29943U, 29884U, 29824U, 29764U, 29704U, 29645U, 29585U, 29525U, 29465U, 29405U, 29345U, 29286U, 29226U, 29166U, 29106U, 29045U,
	28985U, 28925U, 28865U, 28805U, 28745U, 28684U, 28624U, 28564U, 28504U, 28443U, 28383U, 28322U, 28262U, 28201U, 28141U, 28080U,
	28020U, 27959U, 27899U, 27838U, 27777U, 27717U, 27656U, 27595U, 27534U, 27473U, 27413U, 27352U, 27291U, 27230U, 27169U, 27108U,
	27047U, 26986U, 26925U, 26863U, 26802U, 26741U, 26680U, 26619U, 26557U, 26496U, 26435U, 26374U, 26312U, 26251U, 26189U, 26128U,
	26066U, 26005U, 25943U, 25882U, 25820U, 25759U, 25697U, 25635U, 25574U, 25512U, 25450U, 25388U, 25327U, 25265U, 25203U, 25141U,
	25079U, 25017U, 24955U, 24893U, 24831U, 24769U, 24707U, 24645U, 24583U, 24521U, 24459U, 24396U, 24334U, 24272U, 24210U, 24147U,
	24085U, 24023U, 23960U, 23898U, 23836U, 23773U, 23711U, 23648U, 23586U, 23523U, 23461U, 23398U, 23335U, 23273U, 23210U, 23147U,
	23085U, 23022U, 22959U, 22896U, 22834U, 22771U, 22708U, 22645U, 22582U, 22519U, 22456U, 22393U, 22330U, 22267U, 22204U, 22141U,
	22078U, 22015U, 21952U, 21889U, 21825U, 21762U, 21699U, 21636U, 21573U, 21509U, 21446U, 21383U, 21319U, 21256U, 21192U, 21129U,
	21066U, 21002U, 20939U, 20875U, 20812U, 20748U, 20684U, 20621U, 20557U, 20493U, 20430U, 20366U, 20302U, 20239U, 20175U, 20111U,
	20047U, 19984U, 19920U, 19856U, 19792U, 19728U, 19664U, 19600U, 19536U, 19472U, 19408U, 19344U, 19280U, 19216U, 19152U, 19088U,
	19024U, 18960U, 18895U, 18831U, 18767U, 18703U, 18639U, 18574U, 18510U, 18446U, 18381U, 18317U, 18253U, 18188U, 18124U, 18060U,
	17995U, 17931U, 17866U, 17802U, 17737U, 17673U, 17608U, 17544U, 17479U, 17414U, 17350U, 17285U, 17221U, 17156U, 17091U, 17026U,
	16962U, 16897U, 16832U, 16767U, 16703U, 16638U, 16573U, 16508U, 16443U, 16378U, 16313U, 16249U, 16184U, 16119U, 16054U, 15989U,
	15924U, 15859U, 15794U, 15729U, 15664U, 15598U, 15533U, 15468U, 15403U, 15338U, 15273U, 15208U, 15142U, 15077U, 15012U, 14947U,
	14881U, 14816U, 14751U, 14686U, 14620U, 14555U, 14490U, 14424U, 14359U, 14293U, 14228U, 14163U, 14097U, 14032U, 13966U, 13901U,
	13835U, 13770U, 13704U, 13639U, 13573U, 13507U, 13442U, 13376U, 13311U, 13245U, 13179U, 13114U, 13048U, 12982U, 12917U, 12851U,
	12785U, 12720U, 12654U, 12588U, 12522U, 12456U, 12391U, 12325U, 12259U, 12193U, 12127U, 12061U, 11996U, 11930U, 11864U, 11798U,
	11732U, 11666U, 11600U, 11534U, 11468U, 11402U, 11336U, 11270U, 11204U, 11138U, 11072U, 11006U, 10940U, 10874U, 10808U, 10741U,
	10675U, 10609U, 10543U, 10477U, 10411U, 10345U, 10278U, 10212U, 10146U, 10080U, 10014U,  9947U,  9881U,  9815U,  9749U,  9682U,
	 9616U,  9550U,  9483U,  9417U,  9351U,  9284U,  9218U,  9152U,  9085U,  9019U,  8953U,  8886U,  8820U,  8753U,  8687U,  8620U,
	 8554U,  8488U,  8421U,  8355U,  8288U,  8222U,  8155U,  8089U,  8022U,  7956U,  7889U,  7823U,  7756U,  7690U,  7623U,  7556U,
	 7490U,  7423U,  7357U,  7290U,  7223U,  7157U,  7090U,  7024U,  6957U,  6890U,  6824U,  6757U,  6690U,  6624U,  6557U,  6490U,
	 6424U,  6357U,  6290U,  6223U,  6157U,  6090U,  6023U,  5957U,  5890U,  5823U,  5756U,  5689U,  5623U,  5556U,  5489U,  5422U,
	 5356U,  5289U,  5222U,  5155U,  5088U,  5022U,  4955U,  4888U,  4821U,  4754U,  4687U,  4621U,  4554U,  4487U,  4420U,  4353U,
	 4286U,  4219U,  4152U,  4086U,  4019U,  3952U,  3885U,  3818U,  3751U,  3684U,  3617U,  3550U,  3483U,  3416U,  3350U,  3283U,
	 3216U,  3149U,  3082U,  3015U,  2948U,  2881U,  2814U,  2747U,  2680U,  2613U,  2546U,  2479U,  2412U,  2345U,  2278U,  2211U,
	 2144U,  2077U,  2010U,  1943U,  1876U,  1809U,  1742U,  1675U,  1608U,  1541U,  1474U,  1407U,  1340U,  1273U,  1206U,  1139U,
	 1072U,  1005U,   938U,   871U,   804U,   737U,   670U,   603U,   536U,   469U,   402U,   335U,   268U,   201U,   134U,    67U,
	    0U
};
	
	
/* local functions */
STATIC FUNC(uint16, PWMCDD_CODE) PwmPeriodDither_u16(void);
STATIC FUNC(uint16, PWMCDD_CODE) ModIndxPhase_u0p16(uint16 PhaseIndex_Rev_T_u0p16);

/****************************************************************************
 *
 *	Function Name:     PwmCdd_Init
 *
 *  Description:       Initialize Internal Variables and the Module Output value
 *
 *  Inputs:            None
 *
 *  Outputs:           None
 *
 *****************************************************************************/
FUNC(void, PWMCDD_CODE) PwmCdd_Init(void)
{
    /* module specific variables */
    CDD_SeedPWMDither_Cnt_M_u16 = d_SeedInitial_Cnt_u16;
	
	PwmCdd_PWMPrdMax_Cnt_M_u16         =   (uint16)((d_PwmFreq_Hz_Cnt_u16/(uint32)(k_PWMBaseFrequency_Hz_u16 - d_PWMFreqDither_Hz_u16)));
	PwmCdd_PWMPrdMin_Cnt_M_u16         =   (uint16)((d_PwmFreq_Hz_Cnt_u16/(uint32)(k_PWMBaseFrequency_Hz_u16 + d_PWMFreqDither_Hz_u16)));
	PwmCdd_PWMPrdRange_Cnt_M_u16       =   (PwmCdd_PWMPrdMax_Cnt_M_u16 - PwmCdd_PWMPrdMin_Cnt_M_u16);	 
}

/*****************************************************************************
 *
 *  Function Name:     PwmCdd_Per1
 *	
 *  Description:       Control PWM Duty Cycle outputs
 *
 *  Inputs:            None
 *
 *  Outputs:           None
 *
 *****************************************************************************/
FUNC(void, PWMCDD_CODE) PwmCdd_Per1(void)
{
VAR(uint16, AUTOMATIC)    PhaseAdvFinal_Rev_T_u0p16;
VAR(uint16, AUTOMATIC)    Phase_Rev_T_u0p16;
VAR(uint16, AUTOMATIC)    CorrectedMtrPos_Rev_T_u0p16;
VAR(uint16, AUTOMATIC)    CommOffset_Cnt_T_u16;

VAR(uint16, AUTOMATIC)    PhaseIndex_Rev_T_u0p16;

VAR(uint16, AUTOMATIC)    ModIdxPhs_Cnt_T_u0p16[3];

VAR(uint16, AUTOMATIC)    PWMPeriod_Cnt_T_u16;
VAR(uint16, AUTOMATIC)    DCPhsComp_Cnt_T_u16p0[3];


VAR(uint16, AUTOMATIC) i;



	/* Update Phase Reasonableness Data (Purposly at beginning of function to syncronize A/D read with calculations) */
	CDD_PWMDutyCycleASum_Cnt_G_u32[CDD_CDDDataAccessBfr_Cnt_G_u16] += PrevDCPhsAComp_Cnt_M_u16p0;
	CDD_PWMDutyCycleBSum_Cnt_G_u32[CDD_CDDDataAccessBfr_Cnt_G_u16] += PrevDCPhsBComp_Cnt_M_u16p0;
	CDD_PWMDutyCycleCSum_Cnt_G_u32[CDD_CDDDataAccessBfr_Cnt_G_u16] += PrevDCPhsCComp_Cnt_M_u16p0;
	CDD_PWMPeriodSum_Cnt_G_u32[CDD_CDDDataAccessBfr_Cnt_G_u16] += PrevPWMPeriod_Cnt_M_u16;
	
	
	PrevDCPhsAComp_Cnt_M_u16p0 = DCPhsAComp_Cnt_M_u16p0;
	PrevDCPhsBComp_Cnt_M_u16p0 = DCPhsBComp_Cnt_M_u16p0;
	PrevDCPhsCComp_Cnt_M_u16p0 = DCPhsCComp_Cnt_M_u16p0;
	PrevPWMPeriod_Cnt_M_u16 = PWMPeriod_Cnt_M_u16;



	/* Provide configurable read interface for input port which can be optionally dual buffered to ensure data consistency */
	CDD_Read_PhaseAdvanceFinal_Rev_u0p16(&PhaseAdvFinal_Rev_T_u0p16);
	CDD_Read_CorrectedMtrPos_Rev_u0p16(&CorrectedMtrPos_Rev_T_u0p16);
	CDD_Read_CommOffset_Cnt_u16(&CommOffset_Cnt_T_u16);

    PWMPeriod_Cnt_T_u16 = PwmPeriodDither_u16();
    PWMPeriod_Cnt_T_u16 = (uint16)Limit_m(PWMPeriod_Cnt_T_u16, PwmCdd_PWMPrdMin_Cnt_M_u16, PwmCdd_PWMPrdMax_Cnt_M_u16);


	
/* Loop used to consolidate common processing, compiler optimize for speed setting is expected to  */
/*  perform loop unrolling in the compiled software.                                               */
for(i = D_PHSAIDX_CNT_U16; i <= D_PHSCIDX_CNT_U16; i++)
{
	Phase_Rev_T_u0p16 = CorrectedMtrPos_Rev_T_u0p16 + CDD_PhaseOffset_Rev_M_u0p16[i];
	PhaseIndex_Rev_T_u0p16 = Phase_Rev_T_u0p16 + PhaseAdvFinal_Rev_T_u0p16;
	ModIdxPhs_Cnt_T_u0p16[i] = ModIndxPhase_u0p16(PhaseIndex_Rev_T_u0p16);
                                      
    DCPhsComp_Cnt_T_u16p0[i] =  (uint16) ((((uint32)ModIdxPhs_Cnt_T_u0p16[i] * (uint32)PWMPeriod_Cnt_T_u16) 
                               + (uint32)d_HalfPrec16_Cnt_u16)>>d_Scaler16_Cnt_u16);
                                                                                                                               
    DCPhsComp_Cnt_T_u16p0[i] += CommOffset_Cnt_T_u16;                                        
    DCPhsComp_Cnt_T_u16p0[i] = Min_m(DCPhsComp_Cnt_T_u16p0[i], PWMPeriod_Cnt_T_u16);
}

if (TRUE == CDD_PwmDisable_Cnt_G_lgc[CDD_AppDataFbkPthAccessBfr_Cnt_G_u16])
{
	
    DCPhsComp_Cnt_T_u16p0[D_PHSAIDX_CNT_U16] = 0U;
    DCPhsComp_Cnt_T_u16p0[D_PHSBIDX_CNT_U16] = 0U;
    DCPhsComp_Cnt_T_u16p0[D_PHSCIDX_CNT_U16] = 0U;
}
else
{
 
}
	/* Copy the Phase variables to NHET interface*/

	CDD_DCPhsComp_Cnt_G_u16[D_PHSAIDX_CNT_U16] = DCPhsComp_Cnt_T_u16p0[D_PHSAIDX_CNT_U16];
	CDD_DCPhsComp_Cnt_G_u16[D_PHSBIDX_CNT_U16] = DCPhsComp_Cnt_T_u16p0[D_PHSBIDX_CNT_U16];
	CDD_DCPhsComp_Cnt_G_u16[D_PHSCIDX_CNT_U16] = DCPhsComp_Cnt_T_u16p0[D_PHSCIDX_CNT_U16];


	CDD_PWMPeriod_Cnt_G_u16 =	PWMPeriod_Cnt_T_u16;
	
	DCPhsAComp_Cnt_M_u16p0 = DCPhsComp_Cnt_T_u16p0[D_PHSAIDX_CNT_U16];
	DCPhsBComp_Cnt_M_u16p0 = DCPhsComp_Cnt_T_u16p0[D_PHSBIDX_CNT_U16];
	DCPhsCComp_Cnt_M_u16p0 = DCPhsComp_Cnt_T_u16p0[D_PHSCIDX_CNT_U16];
	PWMPeriod_Cnt_M_u16 = PWMPeriod_Cnt_T_u16;
	
	/* Provide configurable write interface for optional BSW output ports */
	CDD_Write_DCPhsBComp_Cnt_u16p0( DCPhsBComp_Cnt_M_u16p0 );
	CDD_Write_DCPhsCComp_Cnt_u16p0( DCPhsCComp_Cnt_M_u16p0 );

} 

/*****************************************************************************
 *  Name:           PwmPeriodDither_u16
 *
 *  Description:    Gererates the next PWM Period
 *
 *  Inputs:         None
 *  Outputs:        PWM Period
 *****************************************************************************/
STATIC FUNC(uint16, PWMCDD_CODE)  PwmPeriodDither_u16(void)
{
VAR(uint16, AUTOMATIC)  PWMPeriodFiltInp_Cnt_T_u16;
VAR(uint16, AUTOMATIC)  PWMPeriod_Cnt_T_u16;

    CDD_SeedPWMDither_Cnt_M_u16 = (CDD_SeedPWMDither_Cnt_M_u16
                                    * d_SeedMultiplier_Cnt_u16)
                                    + d_SeedOffset_Cnt_u16;
    
    PWMPeriodFiltInp_Cnt_T_u16 = (uint16)(((uint32)((CDD_SeedPWMDither_Cnt_M_u16
                               * PwmCdd_PWMPrdRange_Cnt_M_u16))>>d_Scaler16_Cnt_u16));
    
	CDD_DitherFlt1SV_Cnt_M_u16 += (PWMPeriodFiltInp_Cnt_T_u16 - 
						           (CDD_DitherFlt1SV_Cnt_M_u16 >> 
                                         d_FilterKdBits_Cnt_U16))
                                 * k_DitherLPFKn_Cnt_u16;
								
    CDD_DitherFlt2SV_Cnt_M_u16 += ((CDD_DitherFlt1SV_Cnt_M_u16 >> 
                                          d_FilterKdBits_Cnt_U16) - 
						            (CDD_DitherFlt2SV_Cnt_M_u16 >>
                                          d_FilterKdBits_Cnt_U16))
                                 * k_DitherLPFKn_Cnt_u16;

    PWMPeriod_Cnt_T_u16  = (uint16)(((uint32)(CDD_DitherFlt2SV_Cnt_M_u16 >> 
                                          d_FilterKdBits_Cnt_U16)) + 
                                          PwmCdd_PWMPrdMin_Cnt_M_u16);

    return(PWMPeriod_Cnt_T_u16);

}



/*****************************************************************************
 *  Name:           ModIndxPhase_u0p16
 *
 *  Description:    Calculates ModIndx for each phase
 *
 *  Inputs:         None
 *  Outputs:        None
 *****************************************************************************/
STATIC FUNC(uint16, PWMCDD_CODE)  ModIndxPhase_u0p16(uint16 PhaseIndex_Rev_T_u0p16)
{
	sint16 PhaseIndex_Rev_T_sm1p16;
VAR(uint16, AUTOMATIC) PhaseIndex_Cnt_T_u16;
VAR(uint16, AUTOMATIC) ModIdxPhs_Cnt_T_u0p16;
VAR(uint32, AUTOMATIC) ModIdxFinal_Uls_T_u16p16;
    
	PwmCdd_Read_ModIdxFinal_Uls_u16p16(&ModIdxFinal_Uls_T_u16p16);

	if (PhaseIndex_Rev_T_u0p16 > d_240Deg_Rev_u0p16)
	{
		ModIdxPhs_Cnt_T_u0p16 = 0u;
	}
	else
	{
		PhaseIndex_Rev_T_sm1p16 = (sint16)(PhaseIndex_Rev_T_u0p16 - d_120Deg_Rev_u0p16);
		PhaseIndex_Rev_T_u0p16 = (uint16)Abs_s32_m((sint32)PhaseIndex_Rev_T_sm1p16);
		PhaseIndex_Cnt_T_u16 = (uint16)((((uint32)PhaseIndex_Rev_T_u0p16 * (uint32)d_PACntspRev_Uls_u16p0)+d_HalfPrec16_Cnt_u16)>>d_Scaler16_Cnt_u16);
		
		ModIdxPhs_Cnt_T_u0p16 = 
			(uint16)(((ModIdxFinal_Uls_T_u16p16 * 
			            (uint32)t_S_SinePhsToGndTbl_Cnt_u0p16[PhaseIndex_Cnt_T_u16]) + 
			           d_HalfPrec16_Cnt_u16) >> d_Scaler16_Cnt_u16);
	}

	return(ModIdxPhs_Cnt_T_u0p16);
}

/*****************************************************************************
 *  Name:           CDDPorts_ApplyMtrElecMechPol
 *
 *  Description:    Applies the offsets needed for MtrElecMech Polarity Setting
 *
 *  Inputs:         None
 *  Outputs:        None
 *****************************************************************************/
FUNC(void, PWMCDD_CODE) CDD_ApplyPWMMtrElecMechPol(sint8 MtrElecMechPol_Cnt_s8)
{
	if (D_POSITIVEONE_CNT_S8 == MtrElecMechPol_Cnt_s8)
	{
		CDD_PhaseOffset_Rev_M_u0p16[D_PHSAIDX_CNT_U16] = d_PhaseAOffsetNrm_Rev_u0p16;
		CDD_PhaseOffset_Rev_M_u0p16[D_PHSBIDX_CNT_U16] = d_PhaseBOffsetNrm_Rev_u0p16;
		CDD_PhaseOffset_Rev_M_u0p16[D_PHSCIDX_CNT_U16] = d_PhaseCOffsetNrm_Rev_u0p16;
	}
	else
	{
		CDD_PhaseOffset_Rev_M_u0p16[D_PHSAIDX_CNT_U16] = d_PhaseAOffsetInv_Rev_u0p16;
		CDD_PhaseOffset_Rev_M_u0p16[D_PHSBIDX_CNT_U16] = d_PhaseBOffsetInv_Rev_u0p16;
		CDD_PhaseOffset_Rev_M_u0p16[D_PHSCIDX_CNT_U16] = d_PhaseCOffsetInv_Rev_u0p16;
	}
}

/*****************************************************************************
 *  Name:           CDDPorts_ClearPhsReasSum
 *
 *  Description:    Clears the sums for the phase reasonableness
 *
 *  Inputs:         None
 *  Outputs:        None
 *****************************************************************************/
FUNC(void, PWMCDD_CODE) CDDPorts_ClearPhsReasSum(uint16 DataAccessBfr_Cnt_T_u16)
{
	CDD_PWMDutyCycleASum_Cnt_G_u32[DataAccessBfr_Cnt_T_u16] = 0U;
	CDD_PWMDutyCycleBSum_Cnt_G_u32[DataAccessBfr_Cnt_T_u16] = 0U;
	CDD_PWMDutyCycleCSum_Cnt_G_u32[DataAccessBfr_Cnt_T_u16] = 0U;
	CDD_PWMPeriodSum_Cnt_G_u32[DataAccessBfr_Cnt_T_u16] = 0U;
}

