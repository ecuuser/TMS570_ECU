/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2007 - 2013 by Vector Informatik GmbH.                                           All rights reserved.
 *
 *                Please note, that this file contains example configuration used by the 
 *                MICROSAR BSW. This code may influence the behaviour of the MICROSAR BSW
 *                in principle. Therefore, great care must be taken to verify
 *                the correctness of the implementation.
 *
 *                The contents of the originally delivered files are only examples respectively
 *                implementation proposals. With regard to the fact that these functions
 *                are meant for demonstration purposes only, the liability of Vector Informatik
 *                shall be expressly excluded in cases of ordinary negligence, 
 *                to the extent admissible by law or statute.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  _MemMap.h
 *    Component:  -
 *       Module:  -
 *    Generator:  -
 *
 *  Description:  This File is a template for the MemMap.h
 *                This file has to be extended with the memory section defines for all BSW modules
 *                which where used.
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  MISRA VIOLATIONS
 *  -------------------------------------------------------------------------------------------------------------------
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Joachim Kalmbach              Jk            Vector Informatik GmbH
 *  Heike Honert                  Ht            Vector Informatik GmbH
 *  Eugen Stripling               Seu           Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2007-08-01  Jk                    Initial creation
 *  01.01.00  2007-12-14  Jk                    Component specific defines filtering added
 *  01.01.02  2008-11-04  Jk                    Component specific defines filtering added
 *  01.01.03  2008-12-17  Ht                    Improve list of components  (Tp_AsrTpCan,Tp_AsrTpFr,DrvMcu,DrvIcu added)
 *  01.01.04  2009-04-27  Ht                    improve list of components  (Cp_XcpOnCanAsr, Il_AsrIpduM, If_VxFblDcm,
 *                                              If_VxFblVpm_Volvo_ab, DrvFls added)
 *  01.01.05  2009-04-24  Msr                   Renamed J1939_AsrBase as TpJ1939_AsrBase
 *  01.01.06  2009-06-03  Ht                    Improve list of components (Adc, Dio, Gpt, Pwm, Spi, Wdg, Fls, Port, Fim)
 *  01.02.00  2009-08-01  Ht                    Improve list of components (Fee_30_Inst2, Can, ...Sub)
 *                                              Support filtering for RTE
 *  01.02.01  2009-08-18  HH                    replaced C++ comment by C comment
 *  01.02.02  2009-09-02  Lo                    add external Flash driver support
 *  01.02.03  2009-09-12  Lo                    add DrvFls_Mcs12xFslftm01ExtVx
 *                        Ht                    Improve list of components (CanTrcv_30_Tja1040dio,
 *                                                Eth, EthTrcv, EthIf, SoAd, TcpIp, EthSM)
 *  01.03.00  2009-10-30  Ht                    support R8: change EthTrcv to EthTrcv_30_Canoeemu
 *                                              support EthTrcv_30_Dp83848
 *                                              change CanTrcv_30_Xdio to CanTrcv_30___Your_Trcv__
 *                                              change CanTrcv_30_Tja1040dio to CanTrcv_30_Tja1041
 *                                              change name FrTrcv to FrTrcv_30_Tja1080dio
 *                        Lo                    add Cp_AsrXcp
 *                        Ht                    add Cp_XcpOnFrAsr
 *  01.03.01  2010-01-13  Ht                    support SysService_AsrCal
 *  01.03.02  2010-02-15  Ht                    support SysService_SswRcs_Daimler, SysService_Tls, Tp_Http, 
 *                                                      SysService_Dns, SysService_Json, DrvTrans_GenericLindioAsr
 *                        Lo                    add Diag_AsrDem for all OEMs
 *                                              rename internal variables and filter methods
 *  01.04.00  2010-03-04  Ht                    change name FrTrcv_30_Tja1080dio to FrTrcv_30_Tja1080
 *  01.04.01  2010-03-10  Ht                    support DrvTrans_GenericFrAsr, DrvTrans_As8223FrspiAsr, DrvEep and If_AsrIfEa
 *  01.04.02  2010-04-07  Lo                    change IfFee to real components and add If_AsrIfWdV85xNec01Sub
 *  01.04.03  2010-06-11  Ht                    add CanTrcv_30_Tja1043
 *                        Lo                    add Il_AsrIpduMEbBmwSub
 *  01.04.04  2010-08-24  Ht                    add CanTrcv_30_Tle62512G, DrvEep_XAt25128EAsr, Tp_AsrTpFrEbBmwSub
 *  01.05.00  2010-08-24  Ht                    support R10:
 *                                              change LinTrcv_30_Tle7259dio to LinTrcv_30_Tle7259
 *  01.05.01  2010-10-14  Ht                    add VStdLib, SysService_SswScc, SysService_IpBase, SysService_Crypto
 *  01.05.02  2010-10-20  Ht                    support comments for Package Merge Tool
 *  01.05.03  2010-11-03  Ht                    add SysService_E2eLibTttechSub, SysService_E2ePwTttechSub
 *  01.05.04  2010-11-16  Ht                    add SysService_Exi, DrvTrans_Int6400EthAsr, Cdd_AsrCdd_Fiat, Diag_AsrDem_Fiat
 *  01.05.05  2010-12-17  Ht                    add SysService_AsrSchM, DrvEep_XXStubAsr, DrvIcu_Tms570Tinhet01ExtVx
 *                                                  DrvWd_XTle4278gEAsr, DrvWd_XXStubAsr
 *  01.05.06  2011-02-17  Ht                    add DrvEed, SysService_AsrBswM
 *  01.05.07  2011-03-04  Ht                    add DrvTrans_Tja1055CandioAsr
 *                                              rename CanTrcv_30_Tja1040dio to CanTrcv_30_Tja1040
 *                                              add SysService_XmlEngine
 *  01.06.00  2011-03-15  Ht                    support ASR4.0
 *                                              add Ccl_Asr4ComM, Ccl_Asr4SmCan, Nm_Asr4NmIf, Nm_AsrNmDirOsek
 *  01.06.01  2011-04-15  Ht                    add Diag_AsrDcm_<OEM>
 *  01.06.02  2011-06-17  Ht                    correct Diag_AsrDcm_<OEM>
 *                                              add Monitoring_AsrDlt and Monitoring_GenericMeasurement
 *  01.06.03  2011-09-20  Ht                    add DrvTrans_Tja1145CanSpiAsr, DrvTrans_E52013CanspiAsr, DrvFls_XXStubAsr,
 *                                              If_AsrIfFeeV85xNec05Sub, If_AsrIfFeeV85xNec06Sub, If_AsrIfFeeV85xNec07Sub
 *                                              SysService_AsrWdMTttechSub and If_AsrIfWdTttechSub
 *  01.06.04  2011-11-22  Ht                    add If_AsrIfFeeTiSub, 
 *                                              ESCAN00054718: add Cdd_AsrCdd
 *  01.06.05  2011-12-09  Ht                    add Tp_IpV4, Tp_IpV6
 *  01.06.06  2011-12-14  Ht                    add Monitoring_RuntimeMeasurement
 *  01.06.07  2012-01-03  Ht                    add DrvI2c, SysService_Asr4BswM
 *  01.06.08  2012-01-31  Ht                    add DrvTrans_Ar7000EthAsr, DrvTrans_GenericEthmiiAsr
 *  01.06.09  2012-03-06  Ht                    add If_AsrIfFeeMb9df126Fuji01Sub, 
 *                                              Infineon_Tc1767Inf01Sub, Infineon_Tc178xInf01Sub, Infineon_Tc1797Inf01Sub, Infineon_Tc1797Inf02Sub
 *  01.06.10  2012-03-13  Ht                    add Gw_AsrPduRCfg5, Il_AsrComCfg5, Il_AsrIpduMCfg5, Cdd_AsrCddCfg5,
 *                                              Tp_Asr4TpCan, Diag_Asr4Dcm, Diag_Asr4Dem
 *  01.06.11  2012-03-20  Ht                    add Cp_AsrCcp, Cp_XcpOnTcpIpAsr
 *  01.07.00  2012-07-26  Ht                    ESCAN00059365: [AUTOSAR4, compiler warning]: Wrong define name in #undef statement causes re-definition warning
 *                                              add Nm_Asr4NmCan, Nm_Asr4NmFr, Infineon_Xc2000Inf01Sub, Ccl_Asr4ComMCfg5, SysService_Asr4BswMCfg5, SysService_Asr4EcuM, SysService_AsrRamTst,
 *                                                  Ccl_Asr4SmLin 
 *            2012-09-04  Ht                    add support for ASR specification 4.0 R3
 *  01.07.01  2012-10-23  Seu                   add SysService_XmlSecurity
 *  01.07.02  2013-01-10  Seu                   MISRA deviation comments added
 *  01.08.00  2013-03-01  Seu    ESCAN00065501  AR4-325: Add support for Post-build RAM memory section
 *            2013-04-12  Seu    ESCAN00066614  Add the deviation for violation of MISRA rule 19.6
 *  01.09.00  2013-12-10  Seu    ESCAN00072537  Add *_NOCACHE_* memory sections for variables
 *            2013-12-16  Seu                   MISRA compliance: usage of character "'" removed, typos corrected
 *********************************************************************************************************************
 * Nexteer Change Log
**********************************************************************************************************************/
/* Version Control:
 * Date Created:      Wed Jul 11 11:30:00 2013
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author    Change Description                                                               SCR #
 * --------  -------  --------  ------------------------------------------------------------------------------  -------
 * 07/16/15    4      PS       Updated to Fiasa SIP (CBD1300649)										   	    CR#13482
 * 12/01/15    10     PS       Implemented software according to SCIR 5A and DSR 6A	 						    EA3#4681, EA3#4686
 * 01/05/16    11     OT       Integrated VehDyn v7.1								 						    EA3#5438
 * 03/16/16    12     PS       Implemented according to SCIR 8A and DSR 7A	 						    		EA3#6773, EA3#6775	
 */
/* PRQA S 0841 MEMMAP_0841_TAG */ /* MD_MSR_19.6 */

/**********************************************************************************************************************
*  INCLUDES
**********************************************************************************************************************/

/**********************************************************************************************************************
*  GLOBAL CONSTANT MACROS
**********************************************************************************************************************/

 /* PRQA S 0883 1 */ /* MD_MemMap_19.15 */
#undef MEMMAP_VENDOR_ID /* PRQA S 0841 */ /* MD_MSR_19.6 */

#define MEMMAP_VENDOR_ID        (30u)

/* AUTOSAR Software Specification Version Information */

# undef MEMMAP_AR_MAJOR_VERSION /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_AR_MINOR_VERSION /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_AR_PATCH_VERSION /* PRQA S 0841 */ /* MD_MSR_19.6 */

/* AUTOSAR Document version 1.1.0 part of release 3.0.1 */
# define MEMMAP_AR_MAJOR_VERSION       (1u)
# define MEMMAP_AR_MINOR_VERSION       (1u)
# define MEMMAP_AR_PATCH_VERSION       (0u)

/* compatiblity to older versions */
# undef MEM_AR_MAJOR_VERSION /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEM_AR_MINOR_VERSION /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEM_AR_PATCH_VERSION /* PRQA S 0841 */ /* MD_MSR_19.6 */

# define MEM_AR_MAJOR_VERSION          MEMMAP_AR_MAJOR_VERSION
# define MEM_AR_MINOR_VERSION          MEMMAP_AR_MINOR_VERSION
# define MEM_AR_PATCH_VERSION          MEMMAP_AR_PATCH_VERSION


# undef MEMMAP_SW_MAJOR_VERSION /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_SW_MINOR_VERSION /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_SW_PATCH_VERSION /* PRQA S 0841 */ /* MD_MSR_19.6 */

# define MEMMAP_SW_MAJOR_VERSION     (1u)
# define MEMMAP_SW_MINOR_VERSION     (9u)
# define MEMMAP_SW_PATCH_VERSION     (0u)

/* compatiblity to older versions */
# undef MEM_SW_MAJOR_VERSION /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEM_SW_MINOR_VERSION /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEM_SW_PATCH_VERSION /* PRQA S 0841 */ /* MD_MSR_19.6 */

# define MEM_SW_MAJOR_VERSION        MEMMAP_SW_MAJOR_VERSION 
# define MEM_SW_MINOR_VERSION        MEMMAP_SW_MINOR_VERSION 
# define MEM_SW_PATCH_VERSION        MEMMAP_SW_PATCH_VERSION 

#define MEMMAP_ERROR

/* Package Merger: Start Section MemMapModuleList */

/* Include these prior to Rte_MemMap, because that file includes Os_MemMap */

#include "Wdg_MemMap.h"
#include "WdgM_MemMap.h"

/* include Rte MemMap because the Rte sections are configuration dependent*/
#include "Rte_MemMap.h"


/**********************************************************************************************************************
*  AbsHwPos START
**********************************************************************************************************************/

#ifdef ABSHWPOS_START_SEC_VAR_CLEARED_32
	#undef ABSHWPOS_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_10
#endif
#ifdef ABSHWPOS_STOP_SEC_VAR_CLEARED_32
	#undef ABSHWPOS_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

#ifdef ABSHWPOS_START_SEC_VAR_CLEARED_16
	#undef ABSHWPOS_START_SEC_VAR_CLEARED_16
	#define START_SEC_VAR_ZERO_INIT_16BIT_10
#endif
#ifdef ABSHWPOS_STOP_SEC_VAR_CLEARED_16
	#undef ABSHWPOS_STOP_SEC_VAR_CLEARED_16
	#define STOP_SEC_VAR
#endif

#ifdef ABSHWPOS_START_SEC_VAR_CLEARED_8
	#undef ABSHWPOS_START_SEC_VAR_CLEARED_8
	#define START_SEC_VAR_ZERO_INIT_8BIT_10
#endif
#ifdef ABSHWPOS_STOP_SEC_VAR_CLEARED_8
	#undef ABSHWPOS_STOP_SEC_VAR_CLEARED_8
	#define STOP_SEC_VAR
#endif

#ifdef ABSHWPOS_START_SEC_VAR_CLEARED_BOOLEAN
	#undef ABSHWPOS_START_SEC_VAR_CLEARED_BOOLEAN
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_10
#endif
#ifdef ABSHWPOS_STOP_SEC_VAR_CLEARED_BOOLEAN
	#undef ABSHWPOS_STOP_SEC_VAR_CLEARED_BOOLEAN
	#define STOP_SEC_VAR
#endif

#ifdef ABSHWPOS_START_SEC_VAR_CLEARED_UNSPECIFIED
	#undef ABSHWPOS_START_SEC_VAR_CLEARED_UNSPECIFIED
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_10
#endif
#ifdef ABSHWPOS_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#undef ABSHWPOS_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  AbsHwPos END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  ActivePull START
**********************************************************************************************************************/

#ifdef ACTIVEPULL_START_SEC_VAR_SAVED_ZONEH_32
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_9:noinit:typeH:ActivePull")
	#undef ACTIVEPULL_START_SEC_VAR_SAVED_ZONEH_32
	#undef MEMMAP_ERROR
#endif
#ifdef ACTIVEPULL_STOP_SEC_VAR_SAVED_ZONEH_32
	#undef ACTIVEPULL_STOP_SEC_VAR_SAVED_ZONEH_32
	#define STOP_SEC_VAR
#endif

#ifdef ACTIVEPULL_START_SEC_VAR_CLEARED_32
	#undef ACTIVEPULL_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_9
#endif
#ifdef ACTIVEPULL_STOP_SEC_VAR_CLEARED_32
	#undef ACTIVEPULL_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

#ifdef ACTIVEPULL_START_SEC_VAR_CLEARED_16
	#undef ACTIVEPULL_START_SEC_VAR_CLEARED_16
	#define START_SEC_VAR_ZERO_INIT_16BIT_9
#endif
#ifdef ACTIVEPULL_STOP_SEC_VAR_CLEARED_16
	#undef ACTIVEPULL_STOP_SEC_VAR_CLEARED_16
	#define STOP_SEC_VAR
#endif

#ifdef ACTIVEPULL_START_SEC_VAR_CLEARED_BOOLEAN
	#undef ACTIVEPULL_START_SEC_VAR_CLEARED_BOOLEAN
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_9
#endif
#ifdef ACTIVEPULL_STOP_SEC_VAR_CLEARED_BOOLEAN
	#undef ACTIVEPULL_STOP_SEC_VAR_CLEARED_BOOLEAN
	#define STOP_SEC_VAR
#endif

#ifdef ACTIVEPULL_START_SEC_VAR_CLEARED_UNSPECIFIED
	#undef ACTIVEPULL_START_SEC_VAR_CLEARED_UNSPECIFIED
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_9
#endif
#ifdef ACTIVEPULL_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#undef ACTIVEPULL_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  ActivePull END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  Adc START
**********************************************************************************************************************/

#ifdef ADC_START_SEC_CODE
	#undef ADC_START_SEC_CODE
	#define START_SEC_CODE
#endif
#ifdef ADC_STOP_SEC_CODE
	#undef ADC_STOP_SEC_CODE
	#define STOP_SEC_CODE
#endif

#ifdef ADC2_START_SEC_CODE
	#undef ADC2_START_SEC_CODE
	#define START_SEC_CODE
#endif
#ifdef ADC2_STOP_SEC_CODE
	#undef ADC2_STOP_SEC_CODE
	#define STOP_SEC_CODE
#endif

#ifdef ADC_START_SEC_CONST_32
	#undef ADC_START_SEC_CONST_32
	#define START_SEC_CONST_32BIT
#endif
#ifdef ADC_STOP_SEC_CONST_32
	#undef ADC_STOP_SEC_CONST_32
	#define STOP_SEC_CONST
#endif

#ifdef ADC2_START_SEC_CONST_32
	#undef ADC2_START_SEC_CONST_32
	#define START_SEC_CONST_32BIT
#endif
#ifdef ADC2_STOP_SEC_CONST_32
	#undef ADC2_STOP_SEC_CONST_32
	#define STOP_SEC_CONST
#endif

/**********************************************************************************************************************
*  Adc END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  ApXcp START
**********************************************************************************************************************/

#ifdef APXCP_START_SEC_VAR_NOINIT_8
	#undef APXCP_START_SEC_VAR_NOINIT_8
	#define START_SEC_VAR_NOINIT_8BIT_9
#endif
#ifdef APXCP_STOP_SEC_VAR_NOINIT_8
	#undef APXCP_STOP_SEC_VAR_NOINIT_8
	#define STOP_SEC_VAR
#endif

#ifdef APXCP_START_SEC_VAR_NOINIT_32
	#undef APXCP_START_SEC_VAR_NOINIT_32
	#define START_SEC_VAR_NOINIT_32BIT_9
#endif
#ifdef APXCP_STOP_SEC_VAR_NOINIT_32
	#undef APXCP_STOP_SEC_VAR_NOINIT_32
	#define STOP_SEC_VAR
#endif

#ifdef APXCP_START_SEC_VAR_INIT_UNSPECIFIED
	#undef APXCP_START_SEC_VAR_INIT_UNSPECIFIED
	#define START_SEC_VAR_INIT_UNSPECIFIED_9
#endif
#ifdef APXCP_STOP_SEC_VAR_INIT_UNSPECIFIED
	#undef APXCP_STOP_SEC_VAR_INIT_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

#ifdef APXCP_START_SEC_VAR_CLEARED_UNSPECIFIED
	#undef APXCP_START_SEC_VAR_CLEARED_UNSPECIFIED
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_9
#endif
#ifdef APXCP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#undef APXCP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

#ifdef APXCP_START_SEC_VAR_CLEARED_8
	#undef APXCP_START_SEC_VAR_CLEARED_8
	#define START_SEC_VAR_ZERO_INIT_8BIT_9
#endif
#ifdef APXCP_STOP_SEC_VAR_CLEARED_8
	#undef APXCP_STOP_SEC_VAR_CLEARED_8
	#define STOP_SEC_VAR
#endif

#ifdef APXCP_START_SEC_VAR_CLEARED_BOOLEAN
	#undef APXCP_START_SEC_VAR_CLEARED_BOOLEAN
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_9
#endif
#ifdef APXCP_STOP_SEC_VAR_CLEARED_BOOLEAN
	#undef APXCP_STOP_SEC_VAR_CLEARED_BOOLEAN
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  ApXcp END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  Assist START
**********************************************************************************************************************/

#ifdef ASSIST_START_SEC_VAR_CLEARED_16
	#undef ASSIST_START_SEC_VAR_CLEARED_16
	#define START_SEC_VAR_ZERO_INIT_16BIT_10
#endif
#ifdef ASSIST_STOP_SEC_VAR_CLEARED_16
	#undef ASSIST_STOP_SEC_VAR_CLEARED_16
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  Assist END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  AssistFirewall START
**********************************************************************************************************************/

#ifdef ASSISTFIREWALL_START_SEC_VAR_CLEARED_16
	#undef ASSISTFIREWALL_START_SEC_VAR_CLEARED_16
	#define START_SEC_VAR_ZERO_INIT_16BIT_10
#endif
#ifdef ASSISTFIREWALL_STOP_SEC_VAR_CLEARED_16
	#undef ASSISTFIREWALL_STOP_SEC_VAR_CLEARED_16
	#define STOP_SEC_VAR
#endif

#ifdef ASSISTFIREWALL_START_SEC_VAR_CLEARED_32
	#undef ASSISTFIREWALL_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_10
#endif
#ifdef ASSISTFIREWALL_STOP_SEC_VAR_CLEARED_32
	#undef ASSISTFIREWALL_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

#ifdef ASSISTFIREWALL_START_SEC_VAR_CLEARED_UNSPECIFIED
	#undef ASSISTFIREWALL_START_SEC_VAR_CLEARED_UNSPECIFIED
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_10
#endif
#ifdef ASSISTFIREWALL_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#undef ASSISTFIREWALL_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

#ifdef ASSISTFIREWALL_START_SEC_VAR_CLEARED_BOOLEAN
	#undef ASSISTFIREWALL_START_SEC_VAR_CLEARED_BOOLEAN
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_10
#endif
#ifdef ASSISTFIREWALL_STOP_SEC_VAR_CLEARED_BOOLEAN
	#undef ASSISTFIREWALL_STOP_SEC_VAR_CLEARED_BOOLEAN
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  AssistFirewall END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  AstLmt START
*********************************************************************************************************************/

#ifdef ASTLMT_START_SEC_VAR_CLEARED_32
	#undef ASTLMT_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_10
#endif
#ifdef ASTLMT_STOP_SEC_VAR_CLEARED_32
	#undef ASTLMT_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

#ifdef ASTLMT_START_SEC_VAR_CLEARED_BOOLEAN
	#undef ASTLMT_START_SEC_VAR_CLEARED_BOOLEAN
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_10
#endif
#ifdef ASTLMT_STOP_SEC_VAR_CLEARED_BOOLEAN
	#undef ASTLMT_STOP_SEC_VAR_CLEARED_BOOLEAN
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  AstLmt END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  Atan2_NxtrLib START
**********************************************************************************************************************/

#ifdef ATAN2_START_SEC_VAR_INIT_32
	#undef ATAN2_START_SEC_VAR_INIT_32
	#define START_SEC_VAR_INIT_32BIT_10
#endif
#ifdef ATAN2_STOP_SEC_VAR_INIT_32
	#undef ATAN2_STOP_SEC_VAR_INIT_32
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  Atan2_NxtrLib END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  AvgFricLrn START
**********************************************************************************************************************/

#ifdef AVGFRICLRN_START_SEC_VAR_CLEARED_32
	#undef AVGFRICLRN_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_16BIT_9
#endif
#ifdef AVGFRICLRN_STOP_SEC_VAR_CLEARED_32
	#undef AVGFRICLRN_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

#ifdef AVGFRICLRN_START_SEC_VAR_CLEARED_BOOLEAN
	#undef AVGFRICLRN_START_SEC_VAR_CLEARED_BOOLEAN
	#define START_SEC_VAR_ZERO_INIT_8BIT_9
#endif
#ifdef AVGFRICLRN_STOP_SEC_VAR_CLEARED_BOOLEAN
	#undef AVGFRICLRN_STOP_SEC_VAR_CLEARED_BOOLEAN
	#define STOP_SEC_VAR
#endif

#ifdef AVGFRICLRN_START_SEC_VAR_CLEARED_UNSPECIFIED
	#undef AVGFRICLRN_START_SEC_VAR_CLEARED_UNSPECIFIED
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_9
#endif
#ifdef AVGFRICLRN_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#undef AVGFRICLRN_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  AvgFricLrn END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  BatteryVoltage START
*********************************************************************************************************************/

#ifdef BATTERYVOLTAGE_START_SEC_VAR_CLEARED_32
	#undef BATTERYVOLTAGE_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_10
#endif
#ifdef BATTERYVOLTAGE_STOP_SEC_VAR_CLEARED_32
	#undef BATTERYVOLTAGE_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

#ifdef BATTERYVOLTAGE_START_SEC_VAR_CLEARED_16
	#undef BATTERYVOLTAGE_START_SEC_VAR_CLEARED_16
	#define START_SEC_VAR_ZERO_INIT_16BIT_10
#endif
#ifdef BATTERYVOLTAGE_STOP_SEC_VAR_CLEARED_16
	#undef BATTERYVOLTAGE_STOP_SEC_VAR_CLEARED_16
	#define STOP_SEC_VAR
#endif

#ifdef BATTERYVOLTAGE_START_SEC_VAR_CLEARED_BOOLEAN
	#undef BATTERYVOLTAGE_START_SEC_VAR_CLEARED_BOOLEAN
	#define START_SEC_VAR_ZERO_INIT_8BIT_10
#endif
#ifdef BATTERYVOLTAGE_STOP_SEC_VAR_CLEARED_BOOLEAN
	#undef BATTERYVOLTAGE_STOP_SEC_VAR_CLEARED_BOOLEAN
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  BatteryVoltage END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  BkCpPc START
**********************************************************************************************************************/

#ifdef BKCPPC_START_SEC_VAR_CLEARED_16
	#undef BKCPPC_START_SEC_VAR_CLEARED_16
	#define START_SEC_VAR_ZERO_INIT_16BIT_9
#endif
#ifdef BKCPPC_STOP_SEC_VAR_CLEARED_16
	#undef BKCPPC_STOP_SEC_VAR_CLEARED_16
	#define STOP_SEC_VAR
#endif

#ifdef BKCPPC_START_SEC_VAR_CLEARED_32
	#undef BKCPPC_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_9
#endif
#ifdef BKCPPC_STOP_SEC_VAR_CLEARED_32
	#undef BKCPPC_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

#ifdef BKCPPC_START_SEC_VAR_CLEARED_UNSPECIFIED
	#undef BKCPPC_START_SEC_VAR_CLEARED_UNSPECIFIED
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_9
#endif
#ifdef BKCPPC_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#undef BKCPPC_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  BkCpPc END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  BVDiag START
**********************************************************************************************************************/

#ifdef BVDIAG_START_SEC_VAR_CLEARED_32
	#undef BVDIAG_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_9
#endif
#ifdef BVDIAG_STOP_SEC_VAR_CLEARED_32
	#undef BVDIAG_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  BVDiag END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  CalConstants START
**********************************************************************************************************************/

#ifdef CALCONSTANTS_START_SEC_VAR_NOINIT_UNSPECIFIED
	#undef CALCONSTANTS_START_SEC_VAR_NOINIT_UNSPECIFIED
	#define START_SEC_VAR_NOINIT_32BIT_10
#endif
#ifdef CALCONSTANTS_STOP_SEC_VAR_NOINIT_UNSPECIFIED
	#undef CALCONSTANTS_STOP_SEC_VAR_NOINIT_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  CalConstants END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  CDDData START
**********************************************************************************************************************/

#ifdef CDDDATA9_START_SEC_VAR_CLEARED_8
	#undef CDDDATA9_START_SEC_VAR_CLEARED_8
	#define START_SEC_VAR_ZERO_INIT_8BIT_9
#endif
#ifdef CDDDATA9_STOP_SEC_VAR_CLEARED_8
	#undef CDDDATA9_STOP_SEC_VAR_CLEARED_8
	#define STOP_SEC_VAR
#endif

#ifdef CDDDATA9_START_SEC_VAR_CLEARED_32
	#undef CDDDATA9_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_9
#endif
#ifdef CDDDATA9_STOP_SEC_VAR_CLEARED_32
	#undef CDDDATA9_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

#ifdef CDDDATA9_START_SEC_VAR_CLEARED_UNSPECIFIED
	#undef CDDDATA9_START_SEC_VAR_CLEARED_UNSPECIFIED
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_9
#endif
#ifdef CDDDATA9_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#undef CDDDATA9_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#define STOP_SEC_VAR
#endif


#ifdef CDDDATA10_START_SEC_VAR_CLEARED_8
	#undef CDDDATA10_START_SEC_VAR_CLEARED_8
	#define START_SEC_VAR_ZERO_INIT_8BIT_10
#endif
#ifdef CDDDATA10_STOP_SEC_VAR_CLEARED_8
	#undef CDDDATA10_STOP_SEC_VAR_CLEARED_8
	#define STOP_SEC_VAR
#endif

#ifdef CDDDATA10_START_SEC_VAR_CLEARED_16
	#undef CDDDATA10_START_SEC_VAR_CLEARED_16
	#define START_SEC_VAR_ZERO_INIT_16BIT_10
#endif
#ifdef CDDDATA10_STOP_SEC_VAR_CLEARED_16
	#undef CDDDATA10_STOP_SEC_VAR_CLEARED_16
	#define STOP_SEC_VAR
#endif

#ifdef CDDDATA10_START_SEC_VAR_CLEARED_32
	#undef CDDDATA10_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_10
#endif
#ifdef CDDDATA10_STOP_SEC_VAR_CLEARED_32
	#undef CDDDATA10_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

#ifdef CDDDATA10_START_SEC_VAR_CLEARED_UNSPECIFIED
	#undef CDDDATA10_START_SEC_VAR_CLEARED_UNSPECIFIED
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_10
#endif
#ifdef CDDDATA10_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#undef CDDDATA10_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  CDDData END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  CDDInterface START
**********************************************************************************************************************/

#ifdef CDDINTERFACE_START_SEC_VAR_NOINIT_32
	#undef CDDINTERFACE_START_SEC_VAR_NOINIT_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_10
#endif
#ifdef CDDINTERFACE_STOP_SEC_VAR_NOINIT_32
	#undef CDDINTERFACE_STOP_SEC_VAR_NOINIT_32
	#define STOP_SEC_VAR
#endif

#ifdef CDDINTERFACE_START_SEC_VAR_CLEARED_8
	#undef CDDINTERFACE_START_SEC_VAR_CLEARED_8
	#define START_SEC_VAR_ZERO_INIT_8BIT_10
#endif
#ifdef CDDINTERFACE_STOP_SEC_VAR_CLEARED_8
	#undef CDDINTERFACE_STOP_SEC_VAR_CLEARED_8
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  CDDInterface END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  CmMtrCurr START
**********************************************************************************************************************/

#ifdef CMMTRCURR_START_SEC_VAR_CLEARED_16
	#undef CMMTRCURR_START_SEC_VAR_CLEARED_16
	#define START_SEC_VAR_ZERO_INIT_16BIT_10
#endif
#ifdef CMMTRCURR_STOP_SEC_VAR_CLEARED_16
	#undef CMMTRCURR_STOP_SEC_VAR_CLEARED_16
	#define STOP_SEC_VAR
#endif

#ifdef CMMTRCURR_START_SEC_VAR_CLEARED_32
	#undef CMMTRCURR_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_10
#endif
#ifdef CMMTRCURR_STOP_SEC_VAR_CLEARED_32
	#undef CMMTRCURR_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

#ifdef CMMTRCURR_START_SEC_VAR_CLEARED_BOOLEAN
	#undef CMMTRCURR_START_SEC_VAR_CLEARED_BOOLEAN
	#define START_SEC_VAR_ZERO_INIT_8BIT_10
#endif
#ifdef CMMTRCURR_STOP_SEC_VAR_CLEARED_BOOLEAN
	#undef CMMTRCURR_STOP_SEC_VAR_CLEARED_BOOLEAN
	#define STOP_SEC_VAR
#endif

#ifdef CMMTRCURR_START_SEC_VAR_CLEARED_UNSPECIFIED
	#undef CMMTRCURR_START_SEC_VAR_CLEARED_UNSPECIFIED
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_10
#endif
#ifdef CMMTRCURR_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#undef CMMTRCURR_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  CmMtrCurr END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  CMS_Common START
**********************************************************************************************************************/

#ifdef EPSDIAGSRVC_START_SEC_CONST_8
	#undef EPSDIAGSRVC_START_SEC_CONST_8
	#define START_SEC_CONST_8BIT
#endif
#ifdef EPSDIAGSRVC_STOP_SEC_CONST_8
	#undef EPSDIAGSRVC_STOP_SEC_CONST_8
	#define STOP_SEC_VAR
#endif

#ifdef EPSDIAGSRVC_START_SEC_VAR_CLEARED_UNSPECIFIED
	#undef EPSDIAGSRVC_START_SEC_VAR_CLEARED_UNSPECIFIED
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_9
#endif
#ifdef EPSDIAGSRVC_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#undef EPSDIAGSRVC_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

#ifdef EPSDIAGSRVC_START_SEC_VAR_CLEARED_BOOLEAN
	#undef EPSDIAGSRVC_START_SEC_VAR_CLEARED_BOOLEAN
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_9
#endif
#ifdef EPSDIAGSRVC_STOP_SEC_VAR_CLEARED_BOOLEAN
	#undef EPSDIAGSRVC_STOP_SEC_VAR_CLEARED_BOOLEAN
	#define STOP_SEC_VAR
#endif

#ifdef EPSDIAGSRVC_START_SEC_VAR_CLEARED_32
	#undef EPSDIAGSRVC_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_9
#endif
#ifdef EPSDIAGSRVC_STOP_SEC_VAR_CLEARED_32
	#undef EPSDIAGSRVC_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

#ifdef EPSDIAGSRVC_START_SEC_VAR_CLEARED_16
	#undef EPSDIAGSRVC_START_SEC_VAR_CLEARED_16
	#define START_SEC_VAR_ZERO_INIT_16BIT_9
#endif
#ifdef EPSDIAGSRVC_STOP_SEC_VAR_CLEARED_16
	#undef EPSDIAGSRVC_STOP_SEC_VAR_CLEARED_16
	#define STOP_SEC_VAR
#endif

#ifdef EPSDIAGSRVC_START_SEC_VAR_CLEARED_8
	#undef EPSDIAGSRVC_START_SEC_VAR_CLEARED_8
	#define START_SEC_VAR_ZERO_INIT_8BIT_9
#endif
#ifdef EPSDIAGSRVC_STOP_SEC_VAR_CLEARED_8
	#undef EPSDIAGSRVC_STOP_SEC_VAR_CLEARED_8
	#define STOP_SEC_VAR
#endif

#ifdef EPSXCPSRVC_START_SEC_VAR_CLEARED_16
	#undef EPSXCPSRVC_START_SEC_VAR_CLEARED_16
	#define START_SEC_VAR_ZERO_INIT_16BIT_9
#endif
#ifdef EPSXCPSRVC_STOP_SEC_VAR_CLEARED_16
	#undef EPSXCPSRVC_STOP_SEC_VAR_16
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  CMS_Common END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  CtrldDisShtdn START
**********************************************************************************************************************/

#ifdef CTRLDDISSHTDN_START_SEC_VAR_CLEARED_16
	#undef CTRLDDISSHTDN_START_SEC_VAR_CLEARED_16
	#define START_SEC_VAR_ZERO_INIT_16BIT_10
#endif
#ifdef CTRLDDISSHTDN_STOP_SEC_VAR_CLEARED_16
	#undef CTRLDDISSHTDN_STOP_SEC_VAR_CLEARED_16
	#define STOP_SEC_VAR
#endif

#ifdef CTRLDDISSHTDN_START_SEC_VAR_CLEARED_32
	#undef CTRLDDISSHTDN_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_10
#endif
#ifdef CTRLDDISSHTDN_STOP_SEC_VAR_CLEARED_32
	#undef CTRLDDISSHTDN_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  CtrldDisShtdn END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  CtrlTemp START
**********************************************************************************************************************/

#ifdef CTRLTEMP_START_SEC_VAR_CLEARED_32
	#undef CTRLTEMP_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_9
#endif
#ifdef CTRLTEMP_STOP_SEC_VAR_CLEARED_32
	#undef CTRLTEMP_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

#ifdef CTRLTEMP_START_SEC_VAR_CLEARED_16
	#undef CTRLTEMP_START_SEC_VAR_CLEARED_16
	#define START_SEC_VAR_ZERO_INIT_16BIT_9
#endif
#ifdef CTRLTEMP_STOP_SEC_VAR_CLEARED_16
	#undef CTRLTEMP_STOP_SEC_VAR_CLEARED_16
	#define STOP_SEC_VAR
#endif

#ifdef CTRLTEMP_START_SEC_VAR_CLEARED_UNSPECIFIED
	#undef CTRLTEMP_START_SEC_VAR_CLEARED_UNSPECIFIED
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_9
#endif
#ifdef CTRLTEMP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#undef CTRLTEMP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  CtrlTemp END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  CurrCmd START
**********************************************************************************************************************/

#ifdef CURRCMD_START_SEC_VAR_CLEARED_32
	#undef CURRCMD_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_10
#endif
#ifdef CURRCMD_STOP_SEC_VAR_CLEARED_32
	#undef CURRCMD_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

#ifdef CURRCMD_START_SEC_VAR_CLEARED_16
	#undef CURRCMD_START_SEC_VAR_CLEARED_16
	#define START_SEC_VAR_ZERO_INIT_16BIT_10
#endif
#ifdef CURRCMD_STOP_SEC_VAR_CLEARED_16
	#undef CURRCMD_STOP_SEC_VAR_CLEARED_16
	#define STOP_SEC_VAR
#endif

#ifdef CURRCMD_START_SEC_VAR_CLEARED_UNSPECIFIED
	#undef CURRCMD_START_SEC_VAR_CLEARED_UNSPECIFIED
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_10
#endif
#ifdef CURRCMD_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#undef CURRCMD_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#define STOP_SEC_VAR
#endif


/**********************************************************************************************************************
*  CurrCmd END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  CurrParamComp START
**********************************************************************************************************************/

#ifdef CURRPARAMCOMP_START_SEC_VAR_CLEARED_32
	#undef CURRPARAMCOMP_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_10
#endif
#ifdef CURRPARAMCOMP_STOP_SEC_VAR_CLEARED_32
	#undef CURRPARAMCOMP_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  CurrParamComp END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  Damping START
**********************************************************************************************************************/

#ifdef DAMPING_START_SEC_VAR_CLEARED_16
	#undef DAMPING_START_SEC_VAR_CLEARED_16
	#define START_SEC_VAR_ZERO_INIT_16BIT_10
#endif
#ifdef DAMPING_STOP_SEC_VAR_CLEARED_16
	#undef DAMPING_STOP_SEC_VAR_CLEARED_16
	#define STOP_SEC_VAR
#endif

#ifdef DAMPING_START_SEC_VAR_CLEARED_32
	#undef DAMPING_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_10
#endif
#ifdef DAMPING_STOP_SEC_VAR_CLEARED_32
	#undef DAMPING_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

#ifdef DAMPING_START_SEC_VAR_CLEARED_UNSPECIFIED
	#undef DAMPING_START_SEC_VAR_CLEARED_UNSPECIFIED
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_10
#endif
#ifdef DAMPING_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#undef DAMPING_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  Damping END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  DampingFirewall START
**********************************************************************************************************************/

#ifdef DAMPINGFIREWALL_START_SEC_VAR_CLEARED_32
	#undef DAMPINGFIREWALL_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_10
#endif
#ifdef DAMPINGFIREWALL_STOP_SEC_VAR_CLEARED_32
	#undef DAMPINGFIREWALL_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

#ifdef DAMPINGFIREWALL_START_SEC_VAR_CLEARED_16
	#undef DAMPINGFIREWALL_START_SEC_VAR_CLEARED_16
	#define START_SEC_VAR_ZERO_INIT_16BIT_10
#endif
#ifdef DAMPINGFIREWALL_STOP_SEC_VAR_CLEARED_16
	#undef DAMPINGFIREWALL_STOP_SEC_VAR_CLEARED_16
	#define STOP_SEC_VAR
#endif

#ifdef DAMPINGFIREWALL_START_SEC_VAR_CLEARED_UNSPECIFIED
	#undef DAMPINGFIREWALL_START_SEC_VAR_CLEARED_UNSPECIFIED
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_10
#endif
#ifdef DAMPINGFIREWALL_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#undef DAMPINGFIREWALL_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

#ifdef DAMPINGFIREWALL_START_SEC_VAR_CLEARED_BOOLEAN
	#undef DAMPINGFIREWALL_START_SEC_VAR_CLEARED_BOOLEAN
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_10
#endif
#ifdef DAMPINGFIREWALL_STOP_SEC_VAR_CLEARED_BOOLEAN
	#undef DAMPINGFIREWALL_STOP_SEC_VAR_CLEARED_BOOLEAN
	#define STOP_SEC_VAR
#endif
/**********************************************************************************************************************
*  DampingFirewall END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  DfltConfigData START
**********************************************************************************************************************/

#ifdef DFLTCONFIGDATA_START_SEC_VAR_NOINIT_UNSPECIFIED
	#undef DFLTCONFIGDATA_START_SEC_VAR_NOINIT_UNSPECIFIED
	#define START_SEC_VAR_NOINIT_UNSPECIFIED_9
#endif
#ifdef DFLTCONFIGDATA_STOP_SEC_VAR_NOINIT_UNSPECIFIED
	#undef DFLTCONFIGDATA_STOP_SEC_VAR_NOINIT_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  DfltConfigData END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  DiagMgr START
**********************************************************************************************************************/

#ifdef DIAGMGR_START_SEC_VAR_SAVED_ZONEHGS_UNSPECIFIED
	#undef DIAGMGR_START_SEC_VAR_SAVED_ZONEHGS_UNSPECIFIED
	#define START_SEC_VAR_NOINIT_UNSPECIFIED_GLOBALSHARED
#endif
#ifdef DIAGMGR_STOP_SEC_VAR_SAVED_ZONEHGS_UNSPECIFIED
	#undef DIAGMGR_STOP_SEC_VAR_SAVED_ZONEHGS_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

#ifdef DIAGMGR_START_SEC_VAR_CLEARED_BOOLEAN
	#undef DIAGMGR_START_SEC_VAR_CLEARED_BOOLEAN
	#define START_SEC_VAR_ZERO_INIT_8BIT_GLOBALSHARED
#endif
#ifdef DIAGMGR_STOP_SEC_VAR_CLEARED_BOOLEAN
	#undef DIAGMGR_STOP_SEC_VAR_CLEARED_BOOLEAN
	#define STOP_SEC_VAR
#endif

#ifdef DIAGMGR_START_SEC_CONST_UNSPECIFIED
	#undef DIAGMGR_START_SEC_CONST_UNSPECIFIED
	#undef MEMMAP_ERROR
#endif
#ifdef DIAGMGR_STOP_SEC_CONST_UNSPECIFIED
	#undef DIAGMGR_STOP_SEC_CONST_UNSPECIFIED
	#undef MEMMAP_ERROR
#endif

/**********************************************************************************************************************
*  DiagMgr END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  DiagMgr8 START
**********************************************************************************************************************/

#ifdef DIAGMGR8_START_SEC_VAR_CLEARED_8
	#undef DIAGMGR8_START_SEC_VAR_CLEARED_8
	#define START_SEC_VAR_ZERO_INIT_8BIT_8
#endif
#ifdef DIAGMGR8_STOP_SEC_VAR_CLEARED_8
	#undef DIAGMGR8_STOP_SEC_VAR_CLEARED_8
	#define STOP_SEC_VAR
#endif

#ifdef DIAGMGR8_START_SEC_VAR_CLEARED_16
	#undef DIAGMGR8_START_SEC_VAR_CLEARED_16
	#define START_SEC_VAR_ZERO_INIT_16BIT_8
#endif
#ifdef DIAGMGR8_STOP_SEC_VAR_CLEARED_16
	#undef DIAGMGR8_STOP_SEC_VAR_CLEARED_16
	#define STOP_SEC_VAR
#endif

#ifdef DIAGMGR8_START_SEC_VAR_CLEARED_32
	#undef DIAGMGR8_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_8
#endif
#ifdef DIAGMGR8_STOP_SEC_VAR_CLEARED_32
	#undef DIAGMGR8_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

#ifdef DIAGMGR8_START_SEC_VAR_CLEARED_UNSPECIFIED
	#undef DIAGMGR8_START_SEC_VAR_CLEARED_UNSPECIFIED
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_8
#endif
#ifdef DIAGMGR8_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#undef DIAGMGR8_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  DiagMgr8 END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  DiagMgr9 START
**********************************************************************************************************************/

#ifdef DIAGMGR9_START_SEC_VAR_CLEARED_8
	#undef DIAGMGR9_START_SEC_VAR_CLEARED_8
	#define START_SEC_VAR_ZERO_INIT_8BIT_9
#endif
#ifdef DIAGMGR9_STOP_SEC_VAR_CLEARED_8
	#undef DIAGMGR9_STOP_SEC_VAR_CLEARED_8
	#define STOP_SEC_VAR
#endif

#ifdef DIAGMGR9_START_SEC_VAR_CLEARED_16
	#undef DIAGMGR9_START_SEC_VAR_CLEARED_16
	#define START_SEC_VAR_ZERO_INIT_16BIT_9
#endif
#ifdef DIAGMGR9_STOP_SEC_VAR_CLEARED_16
	#undef DIAGMGR9_STOP_SEC_VAR_CLEARED_16
	#define STOP_SEC_VAR
#endif

#ifdef DIAGMGR9_START_SEC_VAR_CLEARED_32
	#undef DIAGMGR9_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_9
#endif
#ifdef DIAGMGR9_STOP_SEC_VAR_CLEARED_32
	#undef DIAGMGR9_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

#ifdef DIAGMGR9_START_SEC_VAR_CLEARED_UNSPECIFIED
	#undef DIAGMGR9_START_SEC_VAR_CLEARED_UNSPECIFIED
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_9
#endif
#ifdef DIAGMGR9_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#undef DIAGMGR9_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  DiagMgr9 END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  DiagMgr10 START
**********************************************************************************************************************/

#ifdef DIAGMGR10_START_SEC_VAR_CLEARED_8
	#undef DIAGMGR10_START_SEC_VAR_CLEARED_8
	#define START_SEC_VAR_ZERO_INIT_8BIT_10
#endif
#ifdef DIAGMGR10_STOP_SEC_VAR_CLEARED_8
	#undef DIAGMGR10_STOP_SEC_VAR_CLEARED_8
	#define STOP_SEC_VAR
#endif

#ifdef DIAGMGR10_START_SEC_VAR_CLEARED_16
	#undef DIAGMGR10_START_SEC_VAR_CLEARED_16
	#define START_SEC_VAR_ZERO_INIT_16BIT_10
#endif
#ifdef DIAGMGR10_STOP_SEC_VAR_CLEARED_16
	#undef DIAGMGR10_STOP_SEC_VAR_CLEARED_16
	#define STOP_SEC_VAR
#endif

#ifdef DIAGMGR10_START_SEC_VAR_CLEARED_32
	#undef DIAGMGR10_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_10
#endif
#ifdef DIAGMGR10_STOP_SEC_VAR_CLEARED_32
	#undef DIAGMGR10_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

#ifdef DIAGMGR10_START_SEC_VAR_CLEARED_UNSPECIFIED
	#undef DIAGMGR10_START_SEC_VAR_CLEARED_UNSPECIFIED
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_10
#endif
#ifdef DIAGMGR10_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#undef DIAGMGR10_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  DiagMgr10 END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  DiagMgrDemIf START
**********************************************************************************************************************/

#ifdef DIAGMGRDEMIF_START_SEC_VAR_16
	#undef DIAGMGRDEMIF_START_SEC_VAR_16
	#define START_SEC_VAR_ZERO_INIT_16BIT_9
#endif
#ifdef DIAGMGRDEMIF_STOP_SEC_VAR_16
	#undef DIAGMGRDEMIF_STOP_SEC_VAR_16
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  DiagMgrDemIf END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  DiagSvc START
**********************************************************************************************************************/

#ifdef DIAGSVC_START_SEC_VAR_CLEARED_32
	#undef DIAGSVC_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_9
#endif
#ifdef DIAGSVC_STOP_SEC_VAR_CLEARED_32
	#undef DIAGSVC_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

#ifdef DIAGSVC_STOP_SEC_VAR_CLEARED_16
	#undef DIAGSVC_STOP_SEC_VAR_CLEARED_16
	#define START_SEC_VAR_ZERO_INIT_16BIT_9
#endif
#ifdef DIAGSVC_STOP_SEC_VAR_CLEARED_16
	#undef DIAGSVC_STOP_SEC_VAR_CLEARED_16
	#define STOP_SEC_VAR
#endif

#ifdef DIAGSVC_START_SEC_VAR_CLEARED_8
	#undef DIAGSVC_START_SEC_VAR_CLEARED_8
	#define START_SEC_VAR_ZERO_INIT_8BIT_9
#endif
#ifdef DIAGSVC_STOP_SEC_VAR_CLEARED_8
	#undef DIAGSVC_STOP_SEC_VAR_CLEARED_8
	#define STOP_SEC_VAR
#endif

#ifdef DIAGSVC_START_SEC_VAR_CLEARED_BOOLEAN
	#undef DIAGSVC_START_SEC_VAR_CLEARED_BOOLEAN
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_9
#endif
#ifdef DIAGSVC_STOP_SEC_VAR_CLEARED_BOOLEAN
	#undef DIAGSVC_STOP_SEC_VAR_CLEARED_BOOLEAN
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  DiagSvc END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  DigColPs START
*********************************************************************************************************************/
#ifdef DIGCOLPS_START_SEC_VAR_CLEARED_UNSPECIFIED
    #undef DIGCOLPS_START_SEC_VAR_CLEARED_UNSPECIFIED
    #define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_10
#endif

#ifdef DIGCOLPS_STOP_SEC_VAR_CLEARED_UNSPECIFIED
    #undef DIGCOLPS_STOP_SEC_VAR_CLEARED_UNSPECIFIED
    #define STOP_SEC_VAR
#endif

#ifdef DIGCOLPS_START_SEC_VAR_CLEARED_BOOLEAN
    #undef DIGCOLPS_START_SEC_VAR_CLEARED_BOOLEAN
    #define START_SEC_VAR_ZERO_INIT_8BIT_10
#endif

#ifdef DIGCOLPS_STOP_SEC_VAR_CLEARED_BOOLEAN
    #undef DIGCOLPS_STOP_SEC_VAR_CLEARED_BOOLEAN
    #define STOP_SEC_VAR
#endif

#ifdef DIGCOLPS_START_SEC_VAR_CLEARED_32
    #undef DIGCOLPS_START_SEC_VAR_CLEARED_32
    #define START_SEC_VAR_ZERO_INIT_32BIT_10
#endif

#ifdef DIGCOLPS_STOP_SEC_VAR_CLEARED_32
    #undef DIGCOLPS_STOP_SEC_VAR_CLEARED_32
    #define STOP_SEC_VAR
#endif

#ifdef DIGCOLPS_START_SEC_VAR_CLEARED_16
    #undef DIGCOLPS_START_SEC_VAR_CLEARED_16
    #define START_SEC_VAR_ZERO_INIT_16BIT_10
#endif

#ifdef DIGCOLPS_STOP_SEC_VAR_CLEARED_16
    #undef DIGCOLPS_STOP_SEC_VAR_CLEARED_16
    #define STOP_SEC_VAR
#endif

#ifdef DIGCOLPS_START_SEC_VAR_CLEARED_8
    #undef DIGCOLPS_START_SEC_VAR_CLEARED_8
    #define START_SEC_VAR_ZERO_INIT_8BIT_10
#endif

#ifdef DIGCOLPS_STOP_SEC_VAR_CLEARED_8
    #undef DIGCOLPS_STOP_SEC_VAR_CLEARED_8
    #define STOP_SEC_VAR
#endif

#ifdef DIGCOLPS_START_SEC_CONST_16
    #undef DIGCOLPS_START_SEC_CONST_16
	#define START_SEC_CONST_16BIT
#endif

#ifdef DIGCOLPS_STOP_SEC_CONST_16
    #undef DIGCOLPS_STOP_SEC_CONST_16
	#define STOP_SEC_CONST
#endif

/**********************************************************************************************************************
 *  DigColPs END
 *********************************************************************************************************************/

/**********************************************************************************************************************
*  DigColPsInt START
*********************************************************************************************************************/

#ifdef DIGCOLPSINT_START_SEC_VAR_CLEARED_UNSPECIFIED
    #undef DIGCOLPSINT_START_SEC_VAR_CLEARED_UNSPECIFIED
    #define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_10
#endif

#ifdef DIGCOLPSINT_STOP_SEC_VAR_CLEARED_UNSPECIFIED
    #undef DIGCOLPSINT_STOP_SEC_VAR_CLEARED_UNSPECIFIED
    #define STOP_SEC_VAR
#endif

#ifdef DIGCOLPSINT_START_SEC_VAR_CLEARED_BOOLEAN
    #undef DIGCOLPSINT_START_SEC_VAR_CLEARED_BOOLEAN
    #define START_SEC_VAR_ZERO_INIT_8BIT_10
#endif

#ifdef DIGCOLPSINT_STOP_SEC_VAR_CLEARED_BOOLEAN
    #undef DIGCOLPSINT_STOP_SEC_VAR_CLEARED_BOOLEAN
    #define STOP_SEC_VAR
#endif

#ifdef DIGCOLPSINT_START_SEC_VAR_CLEARED_32
    #undef DIGCOLPSINT_START_SEC_VAR_CLEARED_32
    #define START_SEC_VAR_ZERO_INIT_32BIT_10
#endif

#ifdef DIGCOLPSINT_STOP_SEC_VAR_CLEARED_32
    #undef DIGCOLPSINT_STOP_SEC_VAR_CLEARED_32
    #define STOP_SEC_VAR
#endif

#ifdef DIGCOLPSINT_START_SEC_VAR_CLEARED_16
    #undef DIGCOLPSINT_START_SEC_VAR_CLEARED_16
    #define START_SEC_VAR_ZERO_INIT_16BIT_10
#endif

#ifdef DIGCOLPSINT_STOP_SEC_VAR_CLEARED_16
    #undef DIGCOLPSINT_STOP_SEC_VAR_CLEARED_16
    #define STOP_SEC_VAR
#endif

#ifdef DIGCOLPSINT_START_SEC_VAR_CLEARED_8
    #undef DIGCOLPSINT_START_SEC_VAR_CLEARED_8
    #define START_SEC_VAR_ZERO_INIT_8BIT_10
#endif

#ifdef DIGCOLPSINT_STOP_SEC_VAR_CLEARED_8
    #undef DIGCOLPSINT_STOP_SEC_VAR_CLEARED_8
    #define STOP_SEC_VAR
#endif

#ifdef DIGCOLPSINT_START_SEC_CONST_8
    #undef DIGCOLPSINT_START_SEC_CONST_8
	#define START_SEC_CONST_8BIT
#endif

#ifdef DIGCOLPSINT_STOP_SEC_CONST_8
	#undef DIGCOLPSINT_STOP_SEC_CONST_8
	#define STOP_SEC_CONST
#endif

/**********************************************************************************************************************
 *  DigColPsInt END
 *********************************************************************************************************************/


/**********************************************************************************************************************
*  I2cNxtr START
*********************************************************************************************************************/

#ifdef I2CNXTR_START_SEC_VAR_CLEARED_UNSPECIFIED
    #undef I2CNXTR_START_SEC_VAR_CLEARED_UNSPECIFIED
    #define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_10
#endif

#ifdef I2CNXTR_STOP_SEC_VAR_CLEARED_UNSPECIFIED
    #undef I2CNXTR_STOP_SEC_VAR_CLEARED_UNSPECIFIED
    #define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
 *  I2cNxtr END
 *********************************************************************************************************************/

/**********************************************************************************************************************
*  DigHwTrqSENT START
**********************************************************************************************************************/

#ifdef DIGHWTRQSENT_START_SEC_VAR_CLEARED_UNSPECIFIED
	#undef DIGHWTRQSENT_START_SEC_VAR_CLEARED_UNSPECIFIED
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_10
#endif
#ifdef DIGHWTRQSENT_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#undef DIGHWTRQSENT_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

#ifdef DIGMSB_START_SEC_VAR_CLEARED_8
	#undef DIGMSB_START_SEC_VAR_CLEARED_8
	#define START_SEC_VAR_ZERO_INIT_8BIT_10
#endif
#ifdef DIGMSB_STOP_SEC_VAR_CLEARED_8
	#undef DIGMSB_STOP_SEC_VAR_CLEARED_8
	#define STOP_SEC_VAR
#endif

#ifdef DIGMSB_START_SEC_VAR_CLEARED_16
	#undef DIGMSB_START_SEC_VAR_CLEARED_16
	#define START_SEC_VAR_ZERO_INIT_16BIT_10
#endif
#ifdef DIGMSB_STOP_SEC_VAR_CLEARED_16
	#undef DIGMSB_STOP_SEC_VAR_CLEARED_16
	#define STOP_SEC_VAR
#endif

#ifdef DIGHWTRQSENT_START_SEC_VAR_CLEARED_32
	#undef DIGHWTRQSENT_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_10
#endif
#ifdef DIGHWTRQSENT_STOP_SEC_VAR_CLEARED_32
	#undef DIGHWTRQSENT_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

#ifdef DIGHWTRQSENT_START_SEC_VAR_SAVED_ZONEH_32
	#undef DIGHWTRQSENT_START_SEC_VAR_SAVED_ZONEH_32
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_10:noinit:typeH:DigHwTrqSENT")
	#undef MEMMAP_ERROR
#endif
#ifdef DIGHWTRQSENT_STOP_SEC_VAR_SAVED_ZONEH_32
	#undef DIGHWTRQSENT_STOP_SEC_VAR_SAVED_ZONEH_32
	#define STOP_SEC_CONST
#endif

/**********************************************************************************************************************
*  DigHwTrqSENT END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  DigMSB START
**********************************************************************************************************************/

#ifdef DIGMSB_START_SEC_VAR_CLEARED_BOOLEAN
	#undef DIGMSB_START_SEC_VAR_CLEARED_BOOLEAN
	#define START_SEC_VAR_ZERO_INIT_8BIT_10
#endif
#ifdef DIGMSB_STOP_SEC_VAR_CLEARED_BOOLEAN
	#undef DIGMSB_STOP_SEC_VAR_CLEARED_BOOLEAN
	#define STOP_SEC_VAR
#endif

#ifdef DIGMSB_START_SEC_VAR_CLEARED_16
	#undef DIGMSB_START_SEC_VAR_CLEARED_16
	#define START_SEC_VAR_ZERO_INIT_16BIT_10
#endif
#ifdef DIGMSB_STOP_SEC_VAR_CLEARED_16
	#undef DIGMSB_STOP_SEC_VAR_CLEARED_16
	#define STOP_SEC_VAR
#endif

#ifdef DIGMSB_START_SEC_VAR_CLEARED_32
	#undef DIGMSB_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_10
#endif
#ifdef DIGMSB_STOP_SEC_VAR_CLEARED_32
	#undef DIGMSB_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

#ifdef DIGMSB_START_SEC_VAR_CLEARED_UNSPECIFIED
	#undef DIGMSB_START_SEC_VAR_CLEARED_UNSPECIFIED
	#define START_SEC_VAR_ZERO_INIT_32BIT_10
#endif
#ifdef DIGMSB_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#undef DIGMSB_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

#ifdef DIGMSB_START_SEC_CONST_8
	#undef DIGMSB_START_SEC_CONST_8
	#define START_SEC_CONST_8BIT
#endif
#ifdef DIGMSB_STOP_SEC_CONST_8
	#undef DIGMSB_STOP_SEC_CONST_8
	#define STOP_SEC_CONST
#endif

/**********************************************************************************************************************
*  DigMSB END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  DigPhsReasDiag START
**********************************************************************************************************************/

#ifdef DIGPHSREASDIAG_START_SEC_VAR_CLEARED_32
	#undef DIGPHSREASDIAG_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_10
#endif
#ifdef DIGPHSREASDIAG_STOP_SEC_VAR_CLEARED_32
	#undef DIGPHSREASDIAG_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

#ifdef DIGPHSREASDIAG_START_SEC_VAR_CLEARED_16
	#undef DIGPHSREASDIAG_START_SEC_VAR_CLEARED_16
	#define START_SEC_VAR_ZERO_INIT_16BIT_10
#endif
#ifdef DIGPHSREASDIAG_STOP_SEC_VAR_CLEARED_16
	#undef DIGPHSREASDIAG_STOP_SEC_VAR_CLEARED_16
	#define STOP_SEC_VAR
#endif

#ifdef DIGPHSREASDIAG_START_SEC_VAR_CLEARED_8
	#undef DIGPHSREASDIAG_START_SEC_VAR_CLEARED_8
	#define START_SEC_VAR_ZERO_INIT_8BIT_10
#endif
#ifdef DIGPHSREASDIAG_STOP_SEC_VAR_CLEARED_8
	#undef DIGPHSREASDIAG_STOP_SEC_VAR_CLEARED_8
	#define STOP_SEC_VAR
#endif

#ifdef DIGPHSREASDIAG_START_SEC_VAR_CLEARED_BOOLEAN
	#undef DIGPHSREASDIAG_START_SEC_VAR_CLEARED_BOOLEAN
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_10
#endif
#ifdef DIGPHSREASDIAG_STOP_SEC_VAR_CLEARED_BOOLEAN
	#undef DIGPHSREASDIAG_STOP_SEC_VAR_CLEARED_BOOLEAN
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  DigPhsReasDiag END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  DMA START
**********************************************************************************************************************/

#ifdef DMA_START_SEC_VAR_CLEARED_UNSPECIFIED
	#undef DMA_START_SEC_VAR_CLEARED_UNSPECIFIED
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_0
#endif
#ifdef DMA_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#undef DMA_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

#ifdef DMA_START_SEC_VAR_CLEARED_BOOLEAN
	#undef DMA_START_SEC_VAR_CLEARED_BOOLEAN
	#define START_SEC_VAR_ZERO_INIT_8BIT_0
#endif
#ifdef DMA_STOP_SEC_VAR_CLEARED_BOOLEAN
	#undef DMA_STOP_SEC_VAR_CLEARED_BOOLEAN
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  DMA END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  ElePwr START
**********************************************************************************************************************/

#ifdef ELEPWR_START_SEC_VAR_CLEARED_32
	#undef ELEPWR_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_9
#endif
#ifdef ELEPWR_STOP_SEC_VAR_CLEARED_32
	#undef ELEPWR_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  ElePwr END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  ePWM START
**********************************************************************************************************************/

#ifdef EPWM_START_SEC_CODE
	#undef EPWM_START_SEC_CODE
	#define START_SEC_CODE
#endif
#ifdef EPWM_STOP_SEC_CODE
	#undef EPWM_STOP_SEC_CODE
	#define STOP_SEC_CODE
#endif

#ifdef EPWM_START_SEC_VAR_CLEARED_16
	#undef EPWM_START_SEC_VAR_CLEARED_16
	#define START_SEC_VAR_ZERO_INIT_16BIT_0
#endif
#ifdef EPWM_STOP_SEC_VAR_CLEARED_16
	#undef EPWM_STOP_SEC_VAR_CLEARED_16
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  ePWM END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  EOTActuatorMng START
**********************************************************************************************************************/

#ifdef EOTACTUATORMNG_START_SEC_VAR_CLEARED_32
	#undef EOTACTUATORMNG_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_10
#endif
#ifdef EOTACTUATORMNG_STOP_SEC_VAR_CLEARED_32
	#undef EOTACTUATORMNG_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

#ifdef EOTACTUATORMNG_START_SEC_VAR_CLEARED_BOOLEAN
	#undef EOTACTUATORMNG_START_SEC_VAR_CLEARED_BOOLEAN
	#define START_SEC_VAR_ZERO_INIT_8BIT_10
#endif
#ifdef EOTACTUATORMNG_STOP_SEC_VAR_CLEARED_BOOLEAN
	#undef EOTACTUATORMNG_STOP_SEC_VAR_CLEARED_BOOLEAN
	#define STOP_SEC_VAR
#endif

#ifdef EOTACTUATORMNG_START_SEC_VAR_CLEARED_UNSPECIFIED
	#undef EOTACTUATORMNG_START_SEC_VAR_CLEARED_UNSPECIFIED
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_10
#endif
#ifdef EOTACTUATORMNG_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#undef EOTACTUATORMNG_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  EOTActuatorMng END
**********************************************************************************************************************/


/**********************************************************************************************************************
*  EtDmpFw START
**********************************************************************************************************************/

#ifdef ETDMPFW_START_SEC_VAR_CLEARED_08
	#undef ETDMPFW_START_SEC_VAR_CLEARED_08
	#define START_SEC_VAR_ZERO_INIT_8BIT_10
#endif
#ifdef ETDMPFW_STOP_SEC_VAR_CLEARED_08
	#undef ETDMPFW_STOP_SEC_VAR_CLEARED_08
	#define STOP_SEC_VAR
#endif

#ifdef ETDMPFW_START_SEC_VAR_CLEARED_32
	#undef ETDMPFW_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_10
#endif
#ifdef ETDMPFW_STOP_SEC_VAR_CLEARED_32
	#undef ETDMPFW_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

#ifdef ETDMPFW_START_SEC_VAR_CLEARED_BOOLEAN
	#undef ETDMPFW_START_SEC_VAR_CLEARED_BOOLEAN
	#define START_SEC_VAR_ZERO_INIT_8BIT_10
#endif
#ifdef ETDMPFW_STOP_SEC_VAR_CLEARED_BOOLEAN
	#undef ETDMPFW_STOP_SEC_VAR_CLEARED_BOOLEAN
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  EtDmpFw END
**********************************************************************************************************************/


/**********************************************************************************************************************
*  FlsTst START
**********************************************************************************************************************/

#ifdef FLSTST_START_SEC_CONST_UNSPECIFIED
	#undef MEMMAP_ERROR
	#undef FLSTST_START_SEC_CONST_UNSPECIFIED
#endif
#ifdef FLSTST_STOP_SEC_CONST_UNSPECIFIED
	#undef MEMMAP_ERROR
	#undef FLSTST_STOP_SEC_CONST_UNSPECIFIED
#endif

#ifdef FLSTST_START_SEC_VAR_UNSPECIFIED
	#undef FLSTST_START_SEC_VAR_UNSPECIFIED
	#define START_SEC_VAR_NOINIT_UNSPECIFIED_0
#endif
#ifdef FLSTST_STOP_SEC_VAR_UNSPECIFIED
	#undef FLSTST_STOP_SEC_VAR_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

#ifdef FLSTST_START_SEC_VAR_16
	#undef FLSTST_START_SEC_VAR_16
	#define START_SEC_VAR_NOINIT_16BIT_0
#endif
#ifdef FLSTST_STOP_SEC_VAR_16
	#undef FLSTST_STOP_SEC_VAR_16
	#define STOP_SEC_VAR
#endif

#ifdef FLSTST_START_SEC_VAR_CLEARED_8
	#undef FLSTST_START_SEC_VAR_CLEARED_8
	#define START_SEC_VAR_ZERO_INIT_8BIT_0
#endif
#ifdef FLSTST_STOP_SEC_VAR_CLEARED_8
	#undef FLSTST_STOP_SEC_VAR_CLEARED_8
	#define STOP_SEC_VAR
#endif

#ifdef FLSTST_START_SEC_VAR_CLEARED_UNSPECIFIED
	#undef FLSTST_START_SEC_VAR_CLEARED_UNSPECIFIED
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_0
#endif
#ifdef FLSTST_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#undef FLSTST_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

#ifdef FLSTST_START_SEC_CODE
	#undef MEMMAP_ERROR
	#undef FLSTST_START_SEC_CODE
#endif
#ifdef FLSTST_STOP_SEC_CODE
	#undef MEMMAP_ERROR
	#undef FLSTST_STOP_SEC_CODE
#endif

/**********************************************************************************************************************
*  FlsTst END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  FltInjection START
**********************************************************************************************************************/

#ifdef FLTINJECTION_START_SEC_VAR_CLEARED_32
	#undef FLTINJECTION_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_GLOBALSHARED
#endif
#ifdef FLTINJECTION_STOP_SEC_VAR_CLEARED_32
	#undef FLTINJECTION_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

#ifdef FLTINJECTION_START_SEC_VAR_CLEARED_UNSPECIFIED
	#undef FLTINJECTION_START_SEC_VAR_CLEARED_UNSPECIFIED
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_GLOBALSHARED
#endif
#ifdef FLTINJECTION_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#undef FLTINJECTION_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  FltInjection END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  FrqDepDmpnInrtCmp START
**********************************************************************************************************************/

#ifdef FRQDEPDMPNINRTCMP_START_SEC_VAR_CLEARED_32
	#undef FRQDEPDMPNINRTCMP_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_10
#endif
#ifdef FRQDEPDMPNINRTCMP_STOP_SEC_VAR_CLEARED_32
	#undef FRQDEPDMPNINRTCMP_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

#ifdef FRQDEPDMPNINRTCMP_START_SEC_VAR_CLEARED_UNSPECIFIED
	#undef FRQDEPDMPNINRTCMP_START_SEC_VAR_CLEARED_UNSPECIFIED
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_10
#endif
#ifdef FRQDEPDMPNINRTCMP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#undef FRQDEPDMPNINRTCMP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  FrqDepDmpnInrtCmp END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  Gsod START
**********************************************************************************************************************/

#ifdef GSOD_START_SEC_VAR_CLEARED_BOOLEAN
	#undef GSOD_START_SEC_VAR_CLEARED_BOOLEAN
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_10
#endif
#ifdef GSOD_STOP_SEC_VAR_CLEARED_BOOLEAN
	#undef GSOD_STOP_SEC_VAR_CLEARED_BOOLEAN
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  Gsod END
**********************************************************************************************************************/


/**********************************************************************************************************************
*  HighFreqAssist START
**********************************************************************************************************************/

#ifdef HIGHFREQASSIST_START_SEC_VAR_CLEARED_32
	#undef HIGHFREQASSIST_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_10
#endif
#ifdef HIGHFREQASSIST_STOP_SEC_VAR_CLEARED_32
	#undef HIGHFREQASSIST_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

#ifdef HYSTADD_START_SEC_VAR_CLEARED_UNSPECIFIED
	#undef HYSTADD_START_SEC_VAR_CLEARED_UNSPECIFIED
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_10
#endif
#ifdef HYSTADD_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#undef HYSTADD_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  HighFreqAssist END
**********************************************************************************************************************/


/**********************************************************************************************************************
*  HiLoadStall START
**********************************************************************************************************************/

#ifdef HILOADSTALL_START_SEC_VAR_CLEARED_16
	#undef HILOADSTALL_START_SEC_VAR_CLEARED_16
	#define START_SEC_VAR_ZERO_INIT_16BIT_9
#endif
#ifdef HILOADSTALL_STOP_SEC_VAR_CLEARED_16
	#undef HILOADSTALL_STOP_SEC_VAR_CLEARED_16
	#define STOP_SEC_VAR
#endif

#ifdef HILOADSTALL_START_SEC_VAR_CLEARED_32
	#undef HILOADSTALL_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_9
#endif
#ifdef HILOADSTALL_STOP_SEC_VAR_CLEARED_32
	#undef HILOADSTALL_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  HiLoadStall END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  HwPwUp START
**********************************************************************************************************************/

#ifdef HWPWUP_START_SEC_VAR_CLEARED_UNSPECIFIED
	#undef HWPWUP_START_SEC_VAR_CLEARED_UNSPECIFIED
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_10
#endif
#ifdef HWPWUP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#undef HWPWUP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

#ifdef HWPWUP_START_SEC_VAR_CLEARED_BOOLEAN
	#undef HWPWUP_START_SEC_VAR_CLEARED_BOOLEAN
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_10
#endif
#ifdef HWPWUP_STOP_SEC_VAR_CLEARED_BOOLEAN
	#undef HWPWUP_STOP_SEC_VAR_CLEARED_BOOLEAN
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  HwPwUp END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  HystComp START
**********************************************************************************************************************/

#ifdef HYSTCOMP_START_SEC_VAR_CLEARED_16
	#undef HYSTCOMP_START_SEC_VAR_CLEARED_16
	#define START_SEC_VAR_ZERO_INIT_16BIT_10
#endif
#ifdef HYSTCOMP_STOP_SEC_VAR_CLEARED_16
	#undef HYSTCOMP_STOP_SEC_VAR_CLEARED_16
	#define STOP_SEC_VAR
#endif

#ifdef HYSTCOMP_START_SEC_VAR_CLEARED_32
	#undef HYSTCOMP_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_10
#endif
#ifdef HYSTCOMP_STOP_SEC_VAR_CLEARED_32
	#undef HYSTCOMP_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

#ifdef HYSTCOMP_START_SEC_VAR_CLEARED_UNSPECIFIED
	#undef HYSTCOMP_START_SEC_VAR_CLEARED_UNSPECIFIED
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_10
#endif
#ifdef HYSTCOMP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#undef HYSTCOMP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  HystComp END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  IoHwAbstractionUsr START
**********************************************************************************************************************/

#ifdef IOHWABSTRACTIONUSR_START_SEC_VAR_CLEARED_16
	#undef IOHWABSTRACTIONUSR_START_SEC_VAR_CLEARED_16
	#define START_SEC_VAR_ZERO_INIT_16BIT_10
#endif
#ifdef IOHWABSTRACTIONUSR_STOP_SEC_VAR_CLEARED_16
	#undef IOHWABSTRACTIONUSR_STOP_SEC_VAR_CLEARED_16
	#define STOP_SEC_VAR
#endif

#ifdef IOHWABSTRACTIONUSR_START_SEC_VAR_CLEARED_32
	#undef IOHWABSTRACTIONUSR_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_10
#endif
#ifdef IOHWABSTRACTIONUSR_STOP_SEC_VAR_CLEARED_32
	#undef IOHWABSTRACTIONUSR_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  IoHwAbstractionUsr END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  LmtCod START
**********************************************************************************************************************/

#ifdef LMTCOD_START_SEC_VAR_CLEARED_32
	#undef LMTCOD_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_10
#endif
#ifdef LMTCOD_STOP_SEC_VAR_CLEARED_32
	#undef LMTCOD_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  LmtCod END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  LrnEOT START
**********************************************************************************************************************/

#ifdef LRNEOT_START_SEC_VAR_CLEARED_32
	#undef LRNEOT_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_9
#endif
#ifdef LRNEOT_STOP_SEC_VAR_CLEARED_32
	#undef LRNEOT_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

#ifdef LRNEOT_START_SEC_VAR_CLEARED_BOOLEAN
	#undef LRNEOT_START_SEC_VAR_CLEARED_BOOLEAN
	#define START_SEC_VAR_ZERO_INIT_8BIT_9
#endif
#ifdef LRNEOT_STOP_SEC_VAR_CLEARED_BOOLEAN
	#undef LRNEOT_STOP_SEC_VAR_CLEARED_BOOLEAN
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  LrnEOT END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  Metrics START
**********************************************************************************************************************/

#ifdef METRICS_START_SEC_VAR_CLEARED_UNSPECIFIED
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION()
	#undef METRICS_START_SEC_VAR_CLEARED_UNSPECIFIED
	#undef MEMMAP_ERROR
#endif
#ifdef METRICS_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#undef METRICS_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  Metrics END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  MtrCtrlISR START
**********************************************************************************************************************/

#ifdef MTRCTRLIRQ_START_SEC_VAR_CLEARED_16
	#undef MTRCTRLIRQ_START_SEC_VAR_CLEARED_16
	#define START_SEC_VAR_ZERO_INIT_16BIT_0
#endif
#ifdef MTRCTRLIRQ_STOP_SEC_VAR_CLEARED_16
	#undef MTRCTRLIRQ_STOP_SEC_VAR_CLEARED_16
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  MtrCtrlISR END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  MtrDrvDiag START
**********************************************************************************************************************/

#ifdef MTRDRVDIAG_START_SEC_VAR_CLEARED_32
	#undef MTRDRVDIAG_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_10
#endif
#ifdef MTRDRVDIAG_STOP_SEC_VAR_CLEARED_32
	#undef MTRDRVDIAG_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

#ifdef MTRDRVDIAG_START_SEC_VAR_CLEARED_16
	#undef MTRDRVDIAG_START_SEC_VAR_CLEARED_16
	#define START_SEC_VAR_ZERO_INIT_16BIT_10
#endif
#ifdef MTRDRVDIAG_STOP_SEC_VAR_CLEARED_16
	#undef MTRDRVDIAG_STOP_SEC_VAR_CLEARED_16
	#define STOP_SEC_VAR
#endif

#ifdef MTRDRVDIAG_START_SEC_VAR_CLEARED_BOOLEAN
	#undef MTRDRVDIAG_START_SEC_VAR_CLEARED_BOOLEAN
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_10
#endif
#ifdef MTRDRVDIAG_STOP_SEC_VAR_CLEARED_BOOLEAN
	#undef MTRDRVDIAG_STOP_SEC_VAR_CLEARED_BOOLEAN
	#define STOP_SEC_VAR
#endif

#ifdef MTRDRVDIAG_START_SEC_VAR_CLEARED_UNSPECIFIED
	#undef MTRDRVDIAG_START_SEC_VAR_CLEARED_UNSPECIFIED
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_10
#endif
#ifdef MTRDRVDIAG_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#undef MTRDRVDIAG_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  MtrDrvDiag END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  MtrTempEst START
**********************************************************************************************************************/

#ifdef MTRTEMPEST_START_SEC_VAR_CLEARED_32
	#undef MTRTEMPEST_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_9
#endif
#ifdef MTRTEMPEST_STOP_SEC_VAR_CLEARED_32
	#undef MTRTEMPEST_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

#ifdef MTRTEMPEST_START_SEC_VAR_CLEARED_BOOLEAN
	#undef MTRTEMPEST_START_SEC_VAR_CLEARED_BOOLEAN
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_9
#endif
#ifdef MTRTEMPEST_STOP_SEC_VAR_CLEARED_BOOLEAN
	#undef MTRTEMPEST_STOP_SEC_VAR_CLEARED_BOOLEAN
	#define STOP_SEC_VAR
#endif

#ifdef MTRTEMPEST_START_SEC_VAR_CLEARED_UNSPECIFIED
	#undef MTRTEMPEST_START_SEC_VAR_CLEARED_UNSPECIFIED
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_9
#endif
#ifdef MTRTEMPEST_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#undef MTRTEMPEST_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  MtrTempEst END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  MtrVel START
**********************************************************************************************************************/

#ifdef MTRVEL_START_SEC_VAR_CLEARED_32
	#undef MTRVEL_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_10
#endif
#ifdef MTRVEL_STOP_SEC_VAR_CLEARED_32
	#undef MTRVEL_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

#ifdef MTRVEL_START_SEC_VAR_CLEARED_16
	#undef MTRVEL_START_SEC_VAR_CLEARED_16
	#define START_SEC_VAR_ZERO_INIT_16BIT_10
#endif
#ifdef MTRVEL_STOP_SEC_VAR_CLEARED_16
	#undef MTRVEL_STOP_SEC_VAR_CLEARED_16
	#define STOP_SEC_VAR
#endif

#ifdef MTRVEL_START_SEC_VAR_CLEARED_8
	#undef MTRVEL_START_SEC_VAR_CLEARED_8
	#define START_SEC_VAR_ZERO_INIT_8BIT_10
#endif
#ifdef MTRVEL_STOP_SEC_VAR_CLEARED_8
	#undef MTRVEL_STOP_SEC_VAR_CLEARED_8
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  MtrVel END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  MtrVel2 START
**********************************************************************************************************************/

#ifdef MTRVEL2_START_SEC_VAR_CLEARED_32
	#undef MTRVEL2_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_8
#endif
#ifdef MTRVEL2_STOP_SEC_VAR_CLEARED_32
	#undef MTRVEL2_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

#ifdef MTRVEL2_START_SEC_VAR_CLEARED_16
	#undef MTRVEL2_START_SEC_VAR_CLEARED_16
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_8
#endif
#ifdef MTRVEL2_STOP_SEC_VAR_CLEARED_16
	#undef MTRVEL2_STOP_SEC_VAR_CLEARED_16
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  MtrVel2 END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  MtrVel3 START
**********************************************************************************************************************/

#ifdef MTRVEL3_START_SEC_VAR_CLEARED_8
	#undef MTRVEL3_START_SEC_VAR_CLEARED_8
	#define START_SEC_VAR_ZERO_INIT_8BIT_10
#endif
#ifdef MTRVEL3_STOP_SEC_VAR_CLEARED_8
	#undef MTRVEL3_STOP_SEC_VAR_CLEARED_8
	#define STOP_SEC_VAR
#endif

#ifdef MTRVEL3_START_SEC_VAR_CLEARED_16
	#undef MTRVEL3_START_SEC_VAR_CLEARED_16
	#define START_SEC_VAR_ZERO_INIT_16BIT_10
#endif
#ifdef MTRVEL3_STOP_SEC_VAR_CLEARED_16
	#undef MTRVEL3_STOP_SEC_VAR_CLEARED_16
	#define STOP_SEC_VAR
#endif

#ifdef MTRVEL3_START_SEC_VAR_CLEARED_32
	#undef MTRVEL3_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_10
#endif
#ifdef MTRVEL3_STOP_SEC_VAR_CLEARED_32
	#undef MTRVEL3_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  MtrVel3 END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  Nhet START
**********************************************************************************************************************/

#ifdef NHET_START_SEC_CODE
	#undef NHET_START_SEC_CODE
	#define START_SEC_CODE
#endif
#ifdef NHET_STOP_SEC_CODE
	#undef NHET_STOP_SEC_CODE
	#define STOP_SEC_CODE
#endif

#ifdef NHET1_START_SEC_CONST_8
	#undef NHET1_START_SEC_CONST_8
	#define START_SEC_CONST_8BIT
#endif
#ifdef NHET1_STOP_SEC_CONST_8
	#undef NHET1_STOP_SEC_CONST_8
	#define STOP_SEC_CONST
#endif

#ifdef NHET1_START_SEC_VAR_CLEARED_8
	#undef NHET1_START_SEC_VAR_CLEARED_8
	#define START_SEC_VAR_ZERO_INIT_8BIT_10
#endif
#ifdef NHET1_STOP_SEC_VAR_CLEARED_8
	#undef NHET1_STOP_SEC_VAR_CLEARED_8
	#define STOP_SEC_VAR
#endif

#ifdef NHET1_START_SEC_VAR_CLEARED_16
	#undef NHET1_START_SEC_VAR_CLEARED_16
	#define START_SEC_VAR_ZERO_INIT_16BIT_10
#endif
#ifdef NHET1_STOP_SEC_VAR_CLEARED_16
	#undef NHET1_STOP_SEC_VAR_CLEARED_16
	#define STOP_SEC_VAR
#endif

#ifdef NHET1_START_SEC_VAR_CLEARED_32
	#undef NHET1_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_10
#endif
#ifdef NHET1_STOP_SEC_VAR_CLEARED_32
	#undef NHET1_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

#ifdef NHET_START_SEC_VAR_CLEARED_BOOLEAN
	#undef NHET_START_SEC_VAR_CLEARED_BOOLEAN
	#define START_SEC_VAR_ZERO_INIT_8BIT_0
#endif
#ifdef NHET_STOP_SEC_VAR_CLEARED_BOOLEAN
	#undef NHET_STOP_SEC_VAR_CLEARED_BOOLEAN
	#define STOP_SEC_VAR
#endif

#ifdef NHET_START_SEC_VAR_CLEARED_UNSPECIFIED
	#undef NHET_START_SEC_VAR_CLEARED_UNSPECIFIED
	#define START_SEC_VAR_ZERO_INIT_32BIT_0
#endif
#ifdef NHET_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#undef NHET_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  Nhet END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  NtWrap START
**********************************************************************************************************************/

#ifdef NTWRAP_START_SEC_VAR_NOINIT_UNSPECIFIED
	#undef NTWRAP_START_SEC_VAR_NOINIT_UNSPECIFIED
	#define START_SEC_VAR_NOINIT_UNSPECIFIED_GLOBALSHARED
#endif
#ifdef NTWRAP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
	#undef NTWRAP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  NtWrap END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  NvMProxy START
**********************************************************************************************************************/

#ifdef NVMPROXY_START_SEC_CODE
	#undef NVMPROXY_START_SEC_CODE
	#define START_SEC_CODE
#endif
#ifdef NVMPROXY_STOP_SEC_CODE
	#undef NVMPROXY_STOP_SEC_CODE
	#define STOP_SEC_CODE
#endif

#ifdef NVMPROXY_START_SEC_VAR_CLEARED_UNSPECIFIED
	#undef NVMPROXY_START_SEC_VAR_CLEARED_UNSPECIFIED
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_GLOBALSHARED
#endif
#ifdef NVMPROXY_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#undef NVMPROXY_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

#ifdef NVMPROXY_START_SEC_VAR_NOINIT_8
	#undef NVMPROXY_START_SEC_VAR_NOINIT_8
	#define START_SEC_VAR_NOINIT_8BIT_9
#endif
#ifdef NVMPROXY_STOP_SEC_VAR_NOINIT_8
	#undef NVMPROXY_STOP_SEC_VAR_NOINIT_8
	#define STOP_SEC_VAR
#endif

#ifdef NVMPROXY_START_SEC_CONST_UNSPECIFIED
	#undef NVMPROXY_START_SEC_CONST_UNSPECIFIED
	#define START_SEC_CONST_UNSPECIFIED
#endif
#ifdef NVMPROXY_STOP_SEC_CONST_UNSPECIFIED
	#undef NVMPROXY_STOP_SEC_CONST_UNSPECIFIED
	#define STOP_SEC_CONST
#endif

/**********************************************************************************************************************
*  NvMProxy END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  OvrVoltMon START
**********************************************************************************************************************/

#ifdef OVRVOLTMON_START_SEC_VAR_CLEARED_16
	#undef OVRVOLTMON_START_SEC_VAR_CLEARED_16
	#define START_SEC_VAR_ZERO_INIT_16BIT_10
#endif
#ifdef OVRVOLTMON_STOP_SEC_VAR_CLEARED_16
	#undef OVRVOLTMON_STOP_SEC_VAR_CLEARED_16
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  OvrVoltMon END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  PeakCurrEst START
**********************************************************************************************************************/

#ifdef PEAKCURREST_START_SEC_VAR_CLEARED_32
	#undef PEAKCURREST_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_10
#endif
#ifdef PEAKCURREST_STOP_SEC_VAR_CLEARED_32
	#undef PEAKCURREST_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  PeakCurrEst END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  PICurrContrl START
**********************************************************************************************************************/

#ifdef PICURRCNTRL_START_SEC_VAR_CLEARED_32
	#undef PICURRCNTRL_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_10
#endif
#ifdef PICURRCNTRL_STOP_SEC_VAR_CLEARED_32
	#undef PICURRCNTRL_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

#ifdef PICURRCNTRL_START_SEC_VAR_CLEARED_UNSPECIFIED
	#undef PICURRCNTRL_START_SEC_VAR_CLEARED_UNSPECIFIED
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_10
#endif
#ifdef PICURRCNTRL_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#undef PICURRCNTRL_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  PICurrContrl END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  PwmCdd START
**********************************************************************************************************************/

#ifdef PWMCDD_START_SEC_VAR_CLEARED_16
	# undef PWMCDD_START_SEC_VAR_CLEARED_16
	# define START_SEC_VAR_ZERO_INIT_16BIT_10
#endif
#ifdef PWMCDD_STOP_SEC_VAR_CLEARED_16
	# undef PWMCDD_STOP_SEC_VAR_CLEARED_16
	# define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  PwmCdd END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  PwrLmtFuncCr START
**********************************************************************************************************************/

#ifdef PWRLMTFUNCCR_START_SEC_VAR_CLEARED_32
	# undef PWRLMTFUNCCR_START_SEC_VAR_CLEARED_32
	# define START_SEC_VAR_ZERO_INIT_32BIT_10
#endif
#ifdef PWRLMTFUNCCR_STOP_SEC_VAR_CLEARED_32
	# undef PWRLMTFUNCCR_STOP_SEC_VAR_CLEARED_32
	# define STOP_SEC_VAR
#endif

#ifdef PWRLMTFUNCCR_START_SEC_VAR_CLEARED_BOOLEAN
	#undef PWRLMTFUNCCR_START_SEC_VAR_CLEARED_BOOLEAN
	#define START_SEC_VAR_ZERO_INIT_8BIT_10
#endif
#ifdef PWRLMTFUNCCR_STOP_SEC_VAR_CLEARED_BOOLEAN
	#undef PWRLMTFUNCCR_STOP_SEC_VAR_CLEARED_BOOLEAN
	#define STOP_SEC_VAR
#endif

#ifdef PWRLMTFUNCCR_START_SEC_VAR_CLEARED_UNSPECIFIED
	# undef PWRLMTFUNCCR_START_SEC_VAR_CLEARED_UNSPECIFIED
	# define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_10
#endif
#ifdef PWRLMTFUNCCR_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	# undef PWRLMTFUNCCR_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	# define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  PwrLmtFuncCr END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  QuadDet START
**********************************************************************************************************************/

#ifdef QUADDET_START_SEC_VAR_INIT_8
	# undef QUADDET_START_SEC_VAR_INIT_8
	# define START_SEC_VAR_INIT_8BIT_10
#endif
#ifdef QUADDET_STOP_SEC_VAR_INIT_8
	# undef QUADDET_STOP_SEC_VAR_INIT_8
	# define STOP_SEC_VAR
#endif

#ifdef QUADDET_START_SEC_VAR_INIT_32
	# undef QUADDET_START_SEC_VAR_INIT_32
	# define START_SEC_VAR_INIT_32BIT_10
#endif
#ifdef QUADDET_STOP_SEC_VAR_INIT_32
	# undef QUADDET_STOP_SEC_VAR_INIT_32
	# define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  QuadDet END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  ResetCause START
**********************************************************************************************************************/

#ifdef RESETCAUSE_START_SEC_VAR_POWER_ON_CLEARED_8
	#undef RESETCAUSE_START_SEC_VAR_POWER_ON_CLEARED_8
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".resetcause")
	#undef MEMMAP_ERROR
#endif
#ifdef RESETCAUSE_STOP_SEC_VAR_POWER_ON_CLEARED_8
	#undef RESETCAUSE_STOP_SEC_VAR_POWER_ON_CLEARED_8
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  ResetCause END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  Return START
**********************************************************************************************************************/

#ifdef RETURN_START_SEC_VAR_CLEARED_32
	#undef RETURN_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_10
#endif
#ifdef RETURN_STOP_SEC_VAR_CLEARED_32
	#undef RETURN_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

#ifdef RETURN_START_SEC_VAR_CLEARED_16
	#undef RETURN_START_SEC_VAR_CLEARED_16
	#define START_SEC_VAR_ZERO_INIT_16BIT_10
#endif
#ifdef RETURN_STOP_SEC_VAR_CLEARED_16
	#undef RETURN_STOP_SEC_VAR_CLEARED_16
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  Return END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  ReturnFirewall START
**********************************************************************************************************************/

#ifdef RETURNFIREWALL_START_SEC_VAR_CLEARED_32
	#undef RETURNFIREWALL_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_10
#endif
#ifdef RETURNFIREWALL_STOP_SEC_VAR_CLEARED_32
	#undef RETURNFIREWALL_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

#ifdef RETURNFIREWALL_START_SEC_VAR_CLEARED_BOOLEAN
	#undef RETURNFIREWALL_START_SEC_VAR_CLEARED_BOOLEAN
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_10
#endif
#ifdef RETURNFIREWALL_STOP_SEC_VAR_CLEARED_BOOLEAN
	#undef RETURNFIREWALL_STOP_SEC_VAR_CLEARED_BOOLEAN
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  ReturnFirewall END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  ShtdnMech START
**********************************************************************************************************************/

#ifdef SHTDNMECH_START_SEC_VAR_CLEARED_32
	#undef SHTDNMECH_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_10
#endif
#ifdef SHTDNMECH_STOP_SEC_VAR_CLEARED_32
	#undef SHTDNMECH_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

#ifdef SHTDNMECH_START_SEC_VAR_CLEARED_8
	#undef SHTDNMECH_START_SEC_VAR_CLEARED_8
	#define START_SEC_VAR_ZERO_INIT_8BIT_10
#endif
#ifdef SHTDNMECH_STOP_SEC_VAR_CLEARED_8
	#undef SHTDNMECH_STOP_SEC_VAR_CLEARED_8
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  ShtdnMech END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  SignlCondn START
**********************************************************************************************************************/

#ifdef SIGNLCONDN_START_SEC_VAR_NOINIT_32
	#undef SIGNLCONDN_START_SEC_VAR_NOINIT_32
	#define START_SEC_VAR_NOINIT_32BIT_10
#endif
#ifdef SIGNLCONDN_STOP_SEC_VAR_NOINIT_32
	#undef SIGNLCONDN_STOP_SEC_VAR_NOINIT_32
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  SignlCondn END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  SrlComInput START
**********************************************************************************************************************/

#ifdef SRLCOMINPUT_START_SEC_VAR_CLEARED_32
	#undef SRLCOMINPUT_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_9
#endif
#ifdef SRLCOMINPUT_STOP_SEC_VAR_CLEARED_32
	#undef SRLCOMINPUT_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

#ifdef SRLCOMINPUT_START_SEC_VAR_CLEARED_16
	#undef SRLCOMINPUT_START_SEC_VAR_CLEARED_16
	#define START_SEC_VAR_ZERO_INIT_16BIT_9
#endif
#ifdef SRLCOMINPUT_STOP_SEC_VAR_CLEARED_16
	#undef SRLCOMINPUT_STOP_SEC_VAR_CLEARED_16
	#define STOP_SEC_VAR
#endif

#ifdef SRLCOMINPUT_START_SEC_VAR_CLEARED_8
	#undef SRLCOMINPUT_START_SEC_VAR_CLEARED_8
	#define START_SEC_VAR_ZERO_INIT_8BIT_9
#endif
#ifdef SRLCOMINPUT_STOP_SEC_VAR_CLEARED_8
	#undef SRLCOMINPUT_STOP_SEC_VAR_CLEARED_8
	#define STOP_SEC_VAR
#endif

#ifdef SRLCOMINPUT_START_SEC_VAR_CLEARED_BOOLEAN
	#undef SRLCOMINPUT_START_SEC_VAR_CLEARED_BOOLEAN
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_9
#endif
#ifdef SRLCOMINPUT_STOP_SEC_VAR_CLEARED_BOOLEAN
	#undef SRLCOMINPUT_STOP_SEC_VAR_CLEARED_BOOLEAN
	#define STOP_SEC_VAR
#endif

#ifdef SRLCOMINPUT_START_SEC_VAR_CLEARED_UNSPECIFIED
	#undef SRLCOMINPUT_START_SEC_VAR_CLEARED_UNSPECIFIED
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_9
#endif
#ifdef SRLCOMINPUT_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#undef SRLCOMINPUT_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  SrlComInput END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  SrlComOutput START
**********************************************************************************************************************/

#ifdef SRLCOMOUTPUT_START_SEC_VAR_CLEARED_BOOLEAN
	#undef SRLCOMOUTPUT_START_SEC_VAR_CLEARED_BOOLEAN
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_9
#endif
#ifdef SRLCOMOUTPUT_STOP_SEC_VAR_CLEARED_BOOLEAN
	#undef SRLCOMOUTPUT_STOP_SEC_VAR_CLEARED_BOOLEAN
	#define STOP_SEC_VAR
#endif

#ifdef SRLCOMOUTPUT_START_SEC_VAR_CLEARED_8
	#undef SRLCOMOUTPUT_START_SEC_VAR_CLEARED_8
	#define START_SEC_VAR_ZERO_INIT_8BIT_9
#endif
#ifdef SRLCOMOUTPUT_STOP_SEC_VAR_CLEARED_8
	#undef SRLCOMOUTPUT_STOP_SEC_VAR_CLEARED_8
	#define STOP_SEC_VAR
#endif

#ifdef SRLCOMOUTPUT_START_SEC_VAR_CLEARED_16
	#undef SRLCOMOUTPUT_START_SEC_VAR_CLEARED_16
	#define START_SEC_VAR_ZERO_INIT_16BIT_9
#endif
#ifdef SRLCOMOUTPUT_STOP_SEC_VAR_CLEARED_16
	#undef SRLCOMOUTPUT_STOP_SEC_VAR_CLEARED_16
	#define STOP_SEC_VAR
#endif

#ifdef SRLCOMOUTPUT_START_SEC_VAR_CLEARED_32
	#undef SRLCOMOUTPUT_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_9
#endif
#ifdef SRLCOMOUTPUT_STOP_SEC_VAR_CLEARED_32
	#undef SRLCOMOUTPUT_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  SrlComOutput END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  SpiNxt START
**********************************************************************************************************************/

#ifdef SPINXT_START_SEC_VAR_CLEARED_UNSPECIFIED
	#undef SPINXT_START_SEC_VAR_CLEARED_UNSPECIFIED
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_10
#endif
#ifdef SPINXT_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#undef SPINXT_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

#ifdef SPINXT_START_SEC_CODE
	#undef SPINXT_START_SEC_CODE
	#define START_SEC_CODE
#endif
#ifdef SPINXT_STOP_SEC_CODE
	#undef SPINXT_STOP_SEC_CODE
	#define STOP_SEC_CODE
#endif

/**********************************************************************************************************************
*  SpiNxt END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  StabilityComp START
**********************************************************************************************************************/

#ifdef STABILITYCOMP_START_SEC_VAR_CLEARED_32
	#undef STABILITYCOMP_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_10
#endif
#ifdef STABILITYCOMP_STOP_SEC_VAR_CLEARED_32
	#undef STABILITYCOMP_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

#ifdef STABILITYCOMP_START_SEC_VAR_CLEARED_16
	#undef STABILITYCOMP_START_SEC_VAR_CLEARED_16
	#define START_SEC_VAR_ZERO_INIT_16BIT_10
#endif
#ifdef STABILITYCOMP_STOP_SEC_VAR_CLEARED_16
	#undef STABILITYCOMP_STOP_SEC_VAR_CLEARED_16
	#define STOP_SEC_VAR
#endif

#ifdef STABILITYCOMP_START_SEC_VAR_CLEARED_BOOLEAN
	#undef STABILITYCOMP_START_SEC_VAR_CLEARED_BOOLEAN
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_10
#endif
#ifdef STABILITYCOMP_STOP_SEC_VAR_CLEARED_BOOLEAN
	#undef STABILITYCOMP_STOP_SEC_VAR_CLEARED_BOOLEAN
	#define STOP_SEC_VAR
#endif

#ifdef STABILITYCOMP_START_SEC_VAR_CLEARED_UNSPECIFIED
	#undef STABILITYCOMP_START_SEC_VAR_CLEARED_UNSPECIFIED
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_10
#endif
#ifdef STABILITYCOMP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#undef STABILITYCOMP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  StabilityComp END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  StabilityComp2 START
**********************************************************************************************************************/

#ifdef STABILITYCOMP2_START_SEC_VAR_CLEARED_32
	#undef STABILITYCOMP2_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_8
#endif
#ifdef STABILITYCOMP2_STOP_SEC_VAR_CLEARED_32
	#undef STABILITYCOMP2_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

#ifdef STABILITYCOMP2_START_SEC_VAR_CLEARED_UNSPECIFIED
	#undef STABILITYCOMP2_START_SEC_VAR_CLEARED_UNSPECIFIED
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_8
#endif
#ifdef STABILITYCOMP2_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#undef STABILITYCOMP2_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  StabilityComp2 END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  StaMd START
**********************************************************************************************************************/

#ifdef STAMD_START_SEC_CONST_UNSPECIFIED
	#undef STAMD_START_SEC_CONST_UNSPECIFIED
	#undef MEMMAP_ERROR
#endif
#ifdef STAMD_STOP_SEC_CONST_UNSPECIFIED
	#undef STAMD_STOP_SEC_CONST_UNSPECIFIED
	#undef MEMMAP_ERROR
#endif

#ifdef STAMD_START_SEC_VAR_SAVED_ZONEHGS_8
	#undef STAMD_START_SEC_VAR_SAVED_ZONEHGS_8
	#define START_SEC_VAR_ZERO_INIT_8BIT_GLOBALSHARED
#endif
#ifdef STAMD_STOP_SEC_VAR_SAVED_ZONEHGS_8
	#undef STAMD_STOP_SEC_VAR_SAVED_ZONEHGS_8
	#define STOP_SEC_VAR
#endif

#ifdef STAMD_START_SEC_VAR_SAVED_ZONEHGS_32
	#undef STAMD_START_SEC_VAR_SAVED_ZONEHGS_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_GLOBALSHARED
#endif
#ifdef STAMD_STOP_SEC_VAR_SAVED_ZONEHGS_32
	#undef STAMD_STOP_SEC_VAR_SAVED_ZONEHGS_32
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  StaMd END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  StaMd8 START
**********************************************************************************************************************/

#ifdef STAMD8_START_SEC_VAR_INIT_UNSPECIFIED
	#undef STAMD8_START_SEC_VAR_INIT_UNSPECIFIED
	#define START_SEC_VAR_INIT_UNSPECIFIED_8
#endif
#ifdef STAMD8_STOP_SEC_VAR_INIT_UNSPECIFIED
	#undef STAMD8_STOP_SEC_VAR_INIT_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

#ifdef STAMD8_START_SEC_VAR_CLEARED_32
	#undef STAMD8_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_8
#endif
#ifdef STAMD8_STOP_SEC_VAR_CLEARED_32
	#undef STAMD8_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

#ifdef STAMD8_START_SEC_VAR_CLEARED_16
	#undef STAMD8_START_SEC_VAR_CLEARED_16
	#define START_SEC_VAR_ZERO_INIT_16BIT_8
#endif
#ifdef STAMD8_STOP_SEC_VAR_CLEARED_16
	#undef STAMD8_STOP_SEC_VAR_CLEARED_16
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  StaMd8 END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  StaMd9 START
**********************************************************************************************************************/

#ifdef STAMD9_START_SEC_VAR_INIT_UNSPECIFIED
	#undef STAMD9_START_SEC_VAR_INIT_UNSPECIFIED
	#define START_SEC_VAR_INIT_UNSPECIFIED_9
#endif
#ifdef STAMD9_STOP_SEC_VAR_INIT_UNSPECIFIED
	#undef STAMD9_STOP_SEC_VAR_INIT_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

#ifdef STAMD9_START_SEC_VAR_CLEARED_32
	#undef STAMD9_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_9
#endif
#ifdef STAMD9_STOP_SEC_VAR_CLEARED_32
	#undef STAMD9_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

#ifdef STAMD9_START_SEC_VAR_CLEARED_BOOLEAN
	#undef STAMD9_START_SEC_VAR_CLEARED_BOOLEAN
	#define START_SEC_VAR_ZERO_INIT_16BIT_9
#endif
#ifdef STAMD9_STOP_SEC_VAR_CLEARED_BOOLEAN
	#undef STAMD9_STOP_SEC_VAR_CLEARED_BOOLEAN
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  StaMd9 END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  StaMd10 START
**********************************************************************************************************************/

#ifdef STAMD10_START_SEC_VAR_INIT_UNSPECIFIED
	#undef STAMD10_START_SEC_VAR_INIT_UNSPECIFIED
	#define START_SEC_VAR_INIT_UNSPECIFIED_10
#endif
#ifdef STAMD10_STOP_SEC_VAR_INIT_UNSPECIFIED
	#undef STAMD10_STOP_SEC_VAR_INIT_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

#ifdef STAMD10_START_SEC_VAR_CLEARED_32
	#undef STAMD10_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_10
#endif
#ifdef STAMD10_STOP_SEC_VAR_CLEARED_32
	#undef STAMD10_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

#ifdef STAMD10_START_SEC_VAR_CLEARED_8
	#undef STAMD10_START_SEC_VAR_CLEARED_8
	#define START_SEC_VAR_ZERO_INIT_8BIT_10
#endif
#ifdef STAMD10_STOP_SEC_VAR_CLEARED_8
	#undef STAMD10_STOP_SEC_VAR_CLEARED_8
	#define STOP_SEC_VAR
#endif

#ifdef STAMD10_START_SEC_VAR_CLEARED_BOOLEAN
	#undef STAMD10_START_SEC_VAR_CLEARED_BOOLEAN
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_10
#endif
#ifdef STAMD10_STOP_SEC_VAR_CLEARED_BOOLEAN
	#undef STAMD10_STOP_SEC_VAR_CLEARED_BOOLEAN
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  StaMd10 END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  StOpCtrl START
**********************************************************************************************************************/

#ifdef STOPCTRL_START_SEC_VAR_NOINIT_32
	#undef STOPCTRL_START_SEC_VAR_NOINIT_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_10
#endif
#ifdef STOPCTRL_STOP_SEC_VAR_NOINIT_32
	#undef STOPCTRL_STOP_SEC_VAR_NOINIT_32
	#define STOP_SEC_VAR
#endif

#ifdef STOPCTRL_START_SEC_VAR_NOINIT_UNSPECIFIED
	#undef STOPCTRL_START_SEC_VAR_NOINIT_UNSPECIFIED
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_10
#endif
#ifdef STOPCTRL_STOP_SEC_VAR_NOINIT_UNSPECIFIED
	#undef STOPCTRL_STOP_SEC_VAR_NOINIT_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  StOpCtrl END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  Sweep START
**********************************************************************************************************************/

#ifdef SWEEP_START_SEC_VAR_CLEARED_32
	#undef SWEEP_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_GLOBALSHARED
#endif
#ifdef SWEEP_STOP_SEC_VAR_CLEARED_32
	#undef SWEEP_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

#ifdef SWEEP_START_SEC_VAR_CLEARED_16
	#undef SWEEP_START_SEC_VAR_CLEARED_16
	#define START_SEC_VAR_ZERO_INIT_16BIT_GLOBALSHARED
#endif
#ifdef SWEEP_STOP_SEC_VAR_CLEARED_16
	#undef SWEEP_STOP_SEC_VAR_CLEARED_16
	#define STOP_SEC_VAR
#endif

#ifdef SWEEP_START_SEC_VAR_CLEARED_BOOLEAN
	#undef SWEEP_START_SEC_VAR_CLEARED_BOOLEAN
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_GLOBALSHARED
#endif
#ifdef SWEEP_STOP_SEC_VAR_CLEARED_BOOLEAN
	#undef SWEEP_STOP_SEC_VAR_CLEARED_BOOLEAN
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  Sweep END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  ThrmlDutyCycle START
**********************************************************************************************************************/

#ifdef THRMLDUTYCYCLE_START_SEC_VAR_CLEARED_8
	#undef THRMLDUTYCYCLE_START_SEC_VAR_CLEARED_8
	#define START_SEC_VAR_ZERO_INIT_8BIT_9
#endif
#ifdef THRMLDUTYCYCLE_STOP_SEC_VAR_CLEARED_8
	#undef THRMLDUTYCYCLE_STOP_SEC_VAR_CLEARED_8
	#define STOP_SEC_VAR
#endif

#ifdef THRMLDUTYCYCLE_START_SEC_VAR_CLEARED_16
	#undef THRMLDUTYCYCLE_START_SEC_VAR_CLEARED_16
	#define START_SEC_VAR_ZERO_INIT_16BIT_9
#endif
#ifdef THRMLDUTYCYCLE_STOP_SEC_VAR_CLEARED_16
	#undef THRMLDUTYCYCLE_STOP_SEC_VAR_CLEARED_16
	#define STOP_SEC_VAR
#endif

#ifdef THRMLDUTYCYCLE_START_SEC_VAR_CLEARED_32
	#undef THRMLDUTYCYCLE_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_9
#endif
#ifdef THRMLDUTYCYCLE_STOP_SEC_VAR_CLEARED_32
	#undef THRMLDUTYCYCLE_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

#ifdef THRMLDUTYCYCLE_START_SEC_VAR_CLEARED_UNSPECIFIED
	#undef THRMLDUTYCYCLE_START_SEC_VAR_CLEARED_UNSPECIFIED
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_9
#endif
#ifdef THRMLDUTYCYCLE_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#undef THRMLDUTYCYCLE_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

#ifdef THRMLDUTYCYCLE_STARTP_SEC_VAR_CLEARED_BOOLEAN
	#undef THRMLDUTYCYCLE_STARTP_SEC_VAR_CLEARED_BOOLEAN
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_9
#endif
#ifdef THRMLDUTYCYCLE_STOP_SEC_VAR_CLEARED_BOOLEAN
	#undef THRMLDUTYCYCLE_STOP_SEC_VAR_CLEARED_BOOLEAN
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  ThrmlDutyCycle END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  TmprlMon START
**********************************************************************************************************************/

#ifdef TMPRLMON_START_SEC_CONST_UNSPECIFIED
	#undef TMPRLMON_START_SEC_CONST_UNSPECIFIED
	#define START_SEC_CONST_UNSPECIFIED
#endif
#ifdef TMPRLMON_STOP_SEC_CONST_UNSPECIFIED
	#undef TMPRLMON_STOP_SEC_CONST_UNSPECIFIED
	#define STOP_SEC_CONST
#endif

#ifdef TMPRLMON_START_SEC_VAR_CLEARED_8
	#undef TMPRLMON_START_SEC_VAR_CLEARED_8
	#define START_SEC_VAR_ZERO_INIT_8BIT_10
#endif
#ifdef TMPRLMON_STOP_SEC_VAR_CLEARED_8
	#undef TMPRLMON_STOP_SEC_VAR_CLEARED_8
	#define STOP_SEC_VAR
#endif

#ifdef TMPRLMON_START_SEC_VAR_CLEARED_32
	#undef TMPRLMON_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_10
#endif
#ifdef TMPRLMON_STOP_SEC_VAR_CLEARED_32
	#undef TMPRLMON_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

#ifdef TMPRLMON_START_SEC_VAR_CLEARED_16
	#undef TMPRLMON_START_SEC_VAR_CLEARED_16
	#define START_SEC_VAR_ZERO_INIT_16BIT_10
#endif
#ifdef TMPRLMON_STOP_SEC_VAR_CLEARED_16
	#undef TMPRLMON_STOP_SEC_VAR_CLEARED_16
	#define STOP_SEC_VAR
#endif

#ifdef TMPRLMON_START_SEC_VAR_CLEARED_UNSPECIFIED
	#undef TMPRLMON_START_SEC_VAR_CLEARED_UNSPECIFIED
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_10
#endif
#ifdef TMPRLMON_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#undef TMPRLMON_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

#ifdef TMPRLMON_START_SEC_VAR_CLEARED_BOOLEAN
	#undef TMPRLMON_START_SEC_VAR_CLEARED_BOOLEAN
	#define START_SEC_VAR_ZERO_INIT_8BIT_10
#endif
#ifdef TMPRLMON_STOP_SEC_VAR_CLEARED_BOOLEAN
	#undef TMPRLMON_STOP_SEC_VAR_CLEARED_BOOLEAN
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  TmprlMon END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  TrqCanc START
**********************************************************************************************************************/

#ifdef TRQCANC_START_SEC_VAR_CLEARED_16
	#undef TRQCANC_START_SEC_VAR_CLEARED_16
	#define START_SEC_VAR_ZERO_INIT_16BIT_10
#endif
#ifdef TRQCANC_STOP_SEC_VAR_CLEARED_16
	#undef TRQCANC_STOP_SEC_VAR_CLEARED_16
	#define STOP_SEC_VAR
#endif

#ifdef TRQCANC_START_SEC_VAR_CLEARED_32
	#undef TRQCANC_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_10
#endif
#ifdef TRQCANC_STOP_SEC_VAR_CLEARED_32
	#undef TRQCANC_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

#ifdef TRQCANC_START_SEC_CONST_16
	#undef TRQCANC_START_SEC_CONST_16
	#define START_SEC_CONST_16BIT
#endif
#ifdef TRQCANC_STOP_SEC_CONST_16
	#undef TRQCANC_STOP_SEC_CONST_16
	#define STOP_SEC_CONST
#endif

/**********************************************************************************************************************
*  TrqCanc END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  TqRsDg START
**********************************************************************************************************************/

#ifdef TQRSDG_START_SEC_VAR_CLEARED_32
	#undef TQRSDG_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_10
#endif
#ifdef TQRSDG_STOP_SEC_VAR_CLEARED_32
	#undef TQRSDG_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

#ifdef TQRSDG_START_SEC_VAR_CLEARED_16
	#undef TQRSDG_START_SEC_VAR_CLEARED_16
	#define START_SEC_VAR_ZERO_INIT_16BIT_10
#endif
#ifdef TQRSDG_STOP_SEC_VAR_CLEARED_16
	#undef TQRSDG_STOP_SEC_VAR_CLEARED_16
	#define STOP_SEC_VAR
#endif

#ifdef TQRSDG_START_SEC_VAR_NOINIT_UNSPECIFIED
	#undef TQRSDG_START_SEC_VAR_NOINIT_UNSPECIFIED
	#define START_SEC_VAR_NOINIT_UNSPECIFIED_10
#endif
#ifdef TQRSDG_STOP_SEC_VAR_NOINIT_UNSPECIFIED
	#undef TQRSDG_STOP_SEC_VAR_NOINIT_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  TqRsDg END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  TuningSelAuth START
**********************************************************************************************************************/

#ifdef TUNINGSELAUTH_START_SEC_VAR_CLEARED_16
	#undef TUNINGSELAUTH_START_SEC_VAR_CLEARED_16
	#define START_SEC_VAR_ZERO_INIT_16BIT_10
#endif
#ifdef TUNINGSELAUTH_STOP_SEC_VAR_CLEARED_16
	#undef TUNINGSELAUTH_STOP_SEC_VAR_CLEARED_16
	#define STOP_SEC_VAR
#endif

#ifdef TUNINGSELAUTH_START_SEC_VAR_CLEARED_UNSPECIFIED
	#undef TUNINGSELAUTH_START_SEC_VAR_CLEARED_UNSPECIFIED
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_10
#endif
#ifdef TUNINGSELAUTH_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#undef TUNINGSELAUTH_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  TuningSelAuth END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  uDiag START
**********************************************************************************************************************/

#ifdef WDGRESETHANDLER_START_SEC_VAR_POWER_ON_CLEARED_8
	#undef WDGRESETHANDLER_START_SEC_VAR_POWER_ON_CLEARED_8
	#define START_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
#endif
#ifdef WDGRESETHANDLER_STOP_SEC_VAR_POWER_ON_CLEARED_8
	#undef WDGRESETHANDLER_STOP_SEC_VAR_POWER_ON_CLEARED_8
	#define STOP_SEC_VAR
#endif

#ifdef UDIAG_START_SEC_CONST_UNSPECIFIED
	#undef MEMMAP_ERROR
	#undef UDIAG_START_SEC_CONST_UNSPECIFIED
#endif
#ifdef UDIAG_STOP_SEC_CONST_UNSPECIFIED
	#undef MEMMAP_ERROR
	#undef UDIAG_STOP_SEC_CONST_UNSPECIFIED
#endif

#ifdef UDIAG_START_SEC_VAR_CLEARED_BOOLEAN
	#undef UDIAG_START_SEC_VAR_CLEARED_BOOLEAN
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_10
#endif
#ifdef UDIAG_STOP_SEC_VAR_CLEARED_BOOLEAN
	#undef UDIAG_STOP_SEC_VAR_CLEARED_BOOLEAN
	#define STOP_SEC_VAR
#endif

#ifdef UDIAG_START_SEC_VAR_CLEARED_16
	#undef UDIAG_START_SEC_VAR_CLEARED_16
	#define START_SEC_VAR_ZERO_INIT_16BIT_10
#endif
#ifdef UDIAG_STOP_SEC_VAR_CLEARED_16
	#undef UDIAG_STOP_SEC_VAR_CLEARED_16
	#define STOP_SEC_VAR
#endif

#ifdef UDIAG_START_SEC_VAR_CLEARED_UNSPECIFIED
	#undef UDIAG_START_SEC_VAR_CLEARED_UNSPECIFIED
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_10
#endif
#ifdef UDIAG_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#undef UDIAG_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

#ifdef UDIAG_START_SEC_VAR_CLEARED_32
	#undef UDIAG_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_10
#endif
#ifdef UDIAG_STOP_SEC_VAR_CLEARED_32
	#undef UDIAG_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

#ifdef UDIAG_START_SEC_VAR_SAVED_UNSPECIFIED
	#undef UDIAG_START_SEC_VAR_SAVED_UNSPECIFIED
	#define START_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
#endif
#ifdef UDIAG_STOP_SEC_VAR_SAVED_UNSPECIFIED
	#undef UDIAG_STOP_SEC_VAR_SAVED_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

#ifdef STARTUP_START_SEC_VAR_NOINIT_32
	#undef STARTUP_START_SEC_VAR_NOINIT_32
	#define START_SEC_VAR_NOINIT_32BIT_0
#endif
#ifdef STARTUP_STOP_SEC_VAR_NOINIT_32
	#undef STARTUP_STOP_SEC_VAR_NOINIT_32
	#define STOP_SEC_VAR
#endif

#ifdef STARTUP_START_SEC_VAR_NOINIT_UNSPECIFIED
	#undef STARTUP_START_SEC_VAR_NOINIT_UNSPECIFIED
	#define START_SEC_VAR_NOINIT_UNSPECIFIED_0
#endif
#ifdef STARTUP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
	#undef STARTUP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  uDiag END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  VehDyn START
**********************************************************************************************************************/

#ifdef VEHDYN_START_SEC_VAR_CLEARED_32
	#undef VEHDYN_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_10
#endif
#ifdef VEHDYN_STOP_SEC_VAR_CLEARED_32
	#undef VEHDYN_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif

#ifdef VEHDYN_START_SEC_VAR_CLEARED_8
	#undef VEHDYN_START_SEC_VAR_CLEARED_8
	#define START_SEC_VAR_ZERO_INIT_8BIT_10
#endif
#ifdef VEHDYN_STOP_SEC_VAR_CLEARED_8
	#undef VEHDYN_STOP_SEC_VAR_CLEARED_8
	#define STOP_SEC_VAR
#endif


#ifdef VEHDYN_START_SEC_VAR_CLEARED_UNSPECIFIED
	#undef VEHDYN_START_SEC_VAR_CLEARED_UNSPECIFIED
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_10
#endif
#ifdef VEHDYN_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#undef VEHDYN_STOP_SEC_VAR_CLEARED_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

#ifdef VEHDYN_START_SEC_VAR_CLEARED_BOOLEAN
	#undef VEHDYN_START_SEC_VAR_CLEARED_BOOLEAN
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_10
#endif
#ifdef VEHDYN_STOP_SEC_VAR_CLEARED_BOOLEAN
	#undef VEHDYN_STOP_SEC_VAR_CLEARED_BOOLEAN
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  VehDyn END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  VehPwrMd START
**********************************************************************************************************************/

#ifdef VEHPWRMD_START_SEC_VAR_CLEARED_32
	#undef VEHPWRMD_START_SEC_VAR_CLEARED_32
	#define START_SEC_VAR_ZERO_INIT_32BIT_9
#endif
#ifdef VEHPWRMD_STOP_SEC_VAR_CLEARED_32
	#undef VEHPWRMD_STOP_SEC_VAR_CLEARED_32
	#define STOP_SEC_VAR
#endif


#ifdef VEHPWRMD_START_SEC_VAR_CLEARED_16
	#undef VEHPWRMD_START_SEC_VAR_CLEARED_16
	#define START_SEC_VAR_ZERO_INIT_16BIT_9
#endif
#ifdef VEHPWRMD_STOP_SEC_VAR_CLEARED_16
	#undef VEHPWRMD_STOP_SEC_VAR_CLEARED_16
	#define STOP_SEC_VAR
#endif

#ifdef VEHPWRMD_START_SEC_VAR_CLEARED_BOOLEAN
	#undef VEHPWRMD_START_SEC_VAR_CLEARED_BOOLEAN
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_9
#endif
#ifdef VEHPWRMD_STOP_SEC_VAR_CLEARED_BOOLEAN
	#undef VEHPWRMD_STOP_SEC_VAR_CLEARED_BOOLEAN
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  VehPwrMd END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  VehSpdLmt START
**********************************************************************************************************************/

#ifdef VEHSPDLMT_START_SEC_VAR_CLEARED_16
	#undef VEHSPDLMT_START_SEC_VAR_CLEARED_16
	#define START_SEC_VAR_ZERO_INIT_16BIT_9
#endif
#ifdef VEHSPDLMT_STOP_SEC_VAR_CLEARED_16
	#undef VEHSPDLMT_STOP_SEC_VAR_CLEARED_16
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  VehSpdLmt END
**********************************************************************************************************************/


/**********************************************************************************************************************
*  Dio START
**********************************************************************************************************************/

#ifdef DIO_START_SEC_CODE
	#undef DIO_START_SEC_CODE
	#define START_SEC_CODE
#endif
#ifdef DIO_STOP_SEC_CODE
	#undef DIO_STOP_SEC_CODE
	#define STOP_SEC_CODE
#endif

#ifdef DIO_START_SEC_CONST_UNSPECIFIED
	#undef DIO_START_SEC_CONST_UNSPECIFIED
	#define START_SEC_CONST_32BIT
#endif
#ifdef DIO_STOP_SEC_CONST_UNSPECIFIED
	#undef DIO_STOP_SEC_CONST_UNSPECIFIED
	#define STOP_SEC_CONST
#endif

/**********************************************************************************************************************
*  Dio END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  Fee START
**********************************************************************************************************************/

#ifdef FEE_START_SEC_CODE
	#undef FEE_START_SEC_CODE
	#define START_SEC_CODE
	/* open var section for function-level static variables */
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_9
#endif
#ifdef FEE_STOP_SEC_CODE
	#undef FEE_STOP_SEC_CODE
	#define STOP_SEC_CODE
	#define STOP_SEC_VAR
#endif

#ifdef FEE_START_SEC_CONST_UNSPECIFIED
	#undef FEE_START_SEC_CONST_UNSPECIFIED
	#define START_SEC_CONST_UNSPECIFIED
#endif
#ifdef FEE_STOP_SEC_CONST_UNSPECIFIED
	#undef FEE_STOP_SEC_CONST_UNSPECIFIED
	#define STOP_SEC_CONST
#endif

#ifdef FEE_START_SEC_VAR_INIT_UNSPECIFIED
	#undef FEE_START_SEC_VAR_INIT_UNSPECIFIED
	#define START_SEC_VAR_INIT_UNSPECIFIED_9
#endif
#ifdef FEE_STOP_SEC_VAR_INIT_UNSPECIFIED
	#undef FEE_STOP_SEC_VAR_INIT_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  Fee END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  Gpt START
**********************************************************************************************************************/

#ifdef GPT_START_SEC_CODE
	#undef GPT_START_SEC_CODE
	#define START_SEC_CODE
#endif
#ifdef GPT_STOP_SEC_CODE
	#undef GPT_STOP_SEC_CODE
	#define STOP_SEC_CODE
#endif

#ifdef GPT_START_SEC_CODE_ISR
	#undef GPT_START_SEC_CODE_ISR
	#define START_SEC_CODE_ISR
#endif
#ifdef GPT_STOP_SEC_CODE_ISR
	#undef GPT_STOP_SEC_CODE_ISR
	#define STOP_SEC_CODE
#endif

#ifdef GPT_START_SEC_PBCFG_ROOT
	#undef GPT_START_SEC_PBCFG_ROOT
	#define START_SEC_CONST_PBCFG
#endif
#ifdef GPT_STOP_SEC_PBCFG_ROOT
	#undef GPT_STOP_SEC_PBCFG_ROOT
	#define STOP_SEC_CONST
#endif

#ifdef GPT_START_SEC_PBCFG
	#undef GPT_START_SEC_PBCFG
	#define START_SEC_CONST_PBCFG
#endif
#ifdef GPT_STOP_SEC_PBCFG
	#undef GPT_STOP_SEC_PBCFG
	#define STOP_SEC_CONST
#endif

#ifdef GPT_START_SEC_CONST_32BIT
	#undef GPT_START_SEC_CONST_32BIT
	#define START_SEC_CONST_32BIT
#endif
#ifdef GPT_STOP_SEC_CONST_32BIT
	#undef GPT_STOP_SEC_CONST_32BIT
	#define STOP_SEC_CONST
#endif

#ifdef GPT_START_SEC_VAR_32BIT
	#undef GPT_START_SEC_VAR_32BIT
	#define START_SEC_VAR_NOINIT_32BIT_9
#endif
#ifdef GPT_STOP_SEC_VAR_32BIT
	#undef GPT_STOP_SEC_VAR_32BIT
	#define STOP_SEC_VAR
#endif

#ifdef GPT_START_SEC_VAR_INIT_UNSPECIFIED
	#undef GPT_START_SEC_VAR_INIT_UNSPECIFIED
	#define START_SEC_VAR_NOINIT_UNSPECIFIED_9
#endif
#ifdef GPT_STOP_SEC_VAR_INIT_UNSPECIFIED
	#undef GPT_STOP_SEC_VAR_INIT_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

#ifdef GPT_START_SEC_VAR_UNSPECIFIED
	#undef GPT_START_SEC_VAR_UNSPECIFIED
	#define START_SEC_VAR_NOINIT_UNSPECIFIED_9
#endif
#ifdef GPT_STOP_SEC_VAR_UNSPECIFIED
	#undef GPT_STOP_SEC_VAR_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  Gpt END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  Mcu START
**********************************************************************************************************************/

#ifdef MCU_START_SEC_CODE
	#undef MCU_START_SEC_CODE
	#define START_SEC_CODE
#endif
#ifdef MCU_STOP_SEC_CODE
	#undef MCU_STOP_SEC_CODE
	#define STOP_SEC_CODE
#endif

#ifdef MCU_START_SEC_PBCFG
	#undef MCU_START_SEC_PBCFG
	#define START_SEC_CONST_PBCFG
#endif
#ifdef MCU_STOP_SEC_PBCFG
	#undef MCU_STOP_SEC_PBCFG
	#define STOP_SEC_CONST
#endif

#ifdef MCU_START_SEC_PBCFG_ROOT
	#undef MCU_START_SEC_PBCFG_ROOT
	#define START_SEC_CONST_PBCFG
#endif
#ifdef MCU_STOP_SEC_PBCFG_ROOT
	#undef MCU_STOP_SEC_PBCFG_ROOT
	#define STOP_SEC_CONST
#endif

#ifdef MCU_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
	#undef MCU_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_9
#endif
#ifdef MCU_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
	#undef MCU_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  Mcu END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  Port START
**********************************************************************************************************************/

#ifdef PORT_START_SEC_CODE
	#undef PORT_START_SEC_CODE
	#define START_SEC_CODE
#endif
#ifdef PORT_STOP_SEC_CODE
	#undef PORT_STOP_SEC_CODE
	#define STOP_SEC_CODE
#endif

#ifdef PORT_START_SEC_PBCODE
	#undef PORT_START_SEC_PBCODE
	#define START_SEC_CODE
#endif
#ifdef PORT_STOP_SEC_PBCODE
	#undef PORT_STOP_SEC_PBCODE
	#define STOP_SEC_CODE
#endif

#ifdef PORT_START_SEC_PBCFG
	#undef PORT_START_SEC_PBCFG
	#define START_SEC_CONST_PBCFG
#endif
#ifdef PORT_STOP_SEC_PBCFG
	#undef PORT_STOP_SEC_PBCFG
	#define STOP_SEC_CONST
#endif

#ifdef PORT_START_SEC_PBCFG_ROOT
	#undef PORT_START_SEC_PBCFG_ROOT
	#define START_SEC_CONST_PBCFG
#endif
#ifdef PORT_STOP_SEC_PBCFG_ROOT
	#undef PORT_STOP_SEC_PBCFG_ROOT
	#define STOP_SEC_CONST
#endif

#ifdef PORT_START_SEC_VAR_UNSPECIFIED
	#undef PORT_START_SEC_VAR_UNSPECIFIED
	#define START_SEC_VAR_INIT_UNSPECIFIED_9
#endif
#ifdef PORT_STOP_SEC_VAR_UNSPECIFIED
	#undef PORT_STOP_SEC_VAR_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  Port END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  Wdg START
**********************************************************************************************************************/

#ifdef WDG_START_SEC_CODE
	#undef WDG_START_SEC_CODE
	#define START_SEC_CODE
#endif
#ifdef WDG_STOP_SEC_CODE
	#undef WDG_STOP_SEC_CODE
	#define STOP_SEC_CODE
#endif

#ifdef WDG_START_SEC_CONST_8BIT
	#undef WDG_START_SEC_CONST_8BIT
	#define START_SEC_CONST_8BIT
#endif
#ifdef WDG_STOP_SEC_CONST_8BIT
	#undef WDG_STOP_SEC_CONST_8BIT
	#define STOP_SEC_CONST
#endif

#ifdef WDG_START_SEC_CONST_16BIT
	#undef WDG_START_SEC_CONST_16BIT
	#define START_SEC_CONST_16BIT
#endif
#ifdef WDG_STOP_SEC_CONST_16BIT
	#undef WDG_STOP_SEC_CONST_16BIT
	#define STOP_SEC_CONST
#endif

#ifdef WDG_START_SEC_CONST_32BIT
	#undef WDG_START_SEC_CONST_32BIT
	#define START_SEC_CONST_32BIT
#endif
#ifdef WDG_STOP_SEC_CONST_32BIT
	#undef WDG_STOP_SEC_CONST_32BIT
	#define STOP_SEC_CONST
#endif

#ifdef WDG_START_SEC_CONST_UNSPECIFIED
	#undef WDG_START_SEC_CONST_UNSPECIFIED
	#define START_SEC_CONST_UNSPECIFIED
#endif
#ifdef WDG_STOP_SEC_CONST_UNSPECIFIED
	#undef WDG_STOP_SEC_CONST_UNSPECIFIED
	#define STOP_SEC_CONST
#endif

#ifdef WDG_START_SEC_VAR_8BIT
	#undef WDG_START_SEC_VAR_8BIT
	#define START_SEC_VAR_INIT_8BIT_0
#endif
#ifdef WDG_STOP_SEC_VAR_8BIT
	#undef WDG_STOP_SEC_VAR_8BIT
	#define STOP_SEC_VAR
#endif

#ifdef WDG_START_SEC_VAR_16BIT
	#undef WDG_START_SEC_VAR_16BIT
	#define START_SEC_VAR_INIT_16BIT_0
#endif
#ifdef WDG_STOP_SEC_VAR_16BIT
	#undef WDG_STOP_SEC_VAR_16BIT
	#define STOP_SEC_VAR
#endif

#ifdef WDG_START_SEC_VAR_32BIT
	#undef WDG_START_SEC_VAR_32BIT
	#define START_SEC_VAR_INIT_32BIT_0
#endif
#ifdef WDG_STOP_SEC_VAR_32BIT
	#undef WDG_STOP_SEC_VAR_32BIT
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  Wdg END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  IoHwAb START
**********************************************************************************************************************/

#ifdef IOHWAB_START_SEC_CODE
	#undef IOHWAB_START_SEC_CODE
	#define START_SEC_CODE
#endif
#ifdef IOHWAB_STOP_SEC_CODE
	#undef IOHWAB_STOP_SEC_CODE
	#define STOP_SEC_CODE
#endif

#ifdef IOHWAB_START_SEC_CONST_32BIT
	#undef IOHWAB_START_SEC_CONST_32BIT
	#define START_SEC_CONST_32BIT
#endif
#ifdef IOHWAB_STOP_SEC_CONST_32BIT
	#undef IOHWAB_STOP_SEC_CONST_32BIT
	#define STOP_SEC_CONST
#endif

#ifdef IOHWAB_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
	#undef IOHWAB_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_9
#endif
#ifdef IOHWAB_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
	#undef IOHWAB_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  IoHwAb END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  MemIf START
**********************************************************************************************************************/

#ifdef MEMIF_START_SEC_CONST_8BIT
	#undef MEMIF_START_SEC_CONST_8BIT
	#define START_SEC_CONST_8BIT
#endif
#ifdef MEMIF_STOP_SEC_CONST_8BIT
	#undef MEMIF_STOP_SEC_CONST_8BIT
	#define STOP_SEC_CONST
#endif

#ifdef MEMIF_START_SEC_CONST_32BIT
	#undef MEMIF_START_SEC_CONST_32BIT
	#define START_SEC_CONST_32BIT
#endif
#ifdef MEMIF_STOP_SEC_CONST_32BIT
	#undef MEMIF_STOP_SEC_CONST_32BIT
	#define STOP_SEC_CONST
#endif

#ifdef MEMIF_START_SEC_CODE
	#undef MEMIF_START_SEC_CODE
	#define START_SEC_CODE
#endif
#ifdef MEMIF_STOP_SEC_CODE
	#undef MEMIF_STOP_SEC_CODE
	#define STOP_SEC_CODE
#endif

/**********************************************************************************************************************
*  MemIf END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  WdgIf START
**********************************************************************************************************************/

#ifdef WDGIF_START_SEC_CODE
	#undef WDGIF_START_SEC_CODE
	#define START_SEC_CODE
#endif
#ifdef WDGIF_STOP_SEC_CODE
	#undef WDGIF_STOP_SEC_CODE
	#define STOP_SEC_CODE
#endif

#if defined WDGIF_START_SEC_VAR_INIT_8BIT
	#undef WDGIF_START_SEC_VAR_INIT_8BIT
	#define START_SEC_VAR_INIT_8BIT_9
#endif
#ifdef WDGIF_STOP_SEC_VAR_INIT_8BIT
	#undef WDGIF_STOP_SEC_VAR_INIT_8BIT
	#define STOP_SEC_VAR
#endif

#ifdef WDGIF_START_SEC_VAR_INIT_16BIT
	#undef WDGIF_START_SEC_VAR_INIT_16BIT
	#define START_SEC_VAR_INIT_16BIT_9
#endif
#ifdef WDGIF_STOP_SEC_VAR_INIT_16BIT
	#undef WDGIF_STOP_SEC_VAR_INIT_16BIT
	#define STOP_SEC_VAR
#endif

#ifdef WDGIF_START_SEC_VAR_INIT_32BIT
	#undef WDGIF_START_SEC_VAR_INIT_32BIT
	#define START_SEC_VAR_INIT_32BIT_9
#endif
#ifdef WDGIF_STOP_SEC_VAR_INIT_32BIT
	#undef WDGIF_STOP_SEC_VAR_INIT_32BIT
	#define STOP_SEC_VAR
#endif

#ifdef WDGIF_START_SEC_VAR_INIT_UNSPECIFIED
	#undef WDGIF_START_SEC_VAR_INIT_UNSPECIFIED
	#define START_SEC_VAR_INIT_UNSPECIFIED_9
#endif
#ifdef WDGIF_STOP_SEC_VAR_INIT_UNSPECIFIED
	#undef WDGIF_STOP_SEC_VAR_INIT_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

#ifdef WDGIF_START_SEC_VAR_NOINIT_8BIT
	#undef WDGIF_START_SEC_VAR_NOINIT_8BIT
	#define START_SEC_VAR_NOINIT_8BIT_9
#endif
#ifdef WDGIF_STOP_SEC_VAR_NOINIT_8BIT
	#undef WDGIF_STOP_SEC_VAR_NOINIT_8BIT
	#define STOP_SEC_VAR
#endif

#ifdef WDGIF_START_SEC_VAR_NOINIT_16BIT
	#undef WDGIF_START_SEC_VAR_NOINIT_16BIT
	#define START_SEC_VAR_NOINIT_16BIT_9
#endif
#ifdef WDGIF_STOP_SEC_VAR_NOINIT_16BIT
	#undef WDGIF_STOP_SEC_VAR_NOINIT_16BIT
	#define STOP_SEC_VAR
#endif

#ifdef WDGIF_START_SEC_VAR_NOINIT_32BIT
	#undef WDGIF_START_SEC_VAR_NOINIT_32BIT
	#define START_SEC_VAR_NOINIT_32BIT_9
#endif
#ifdef WDGIF_STOP_SEC_VAR_NOINIT_32BIT
	#undef WDGIF_STOP_SEC_VAR_NOINIT_32BIT
	#define STOP_SEC_VAR
#endif

#ifdef WDGIF_START_SEC_VAR_NOINIT_UNSPECIFIED
	#undef WDGIF_START_SEC_VAR_NOINIT_UNSPECIFIED
	#define START_SEC_VAR_NOINIT_UNSPECIFIED_9
#endif
#ifdef WDGIF_STOP_SEC_VAR_NOINIT_UNSPECIFIED
	#undef WDGIF_STOP_SEC_VAR_NOINIT_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

#ifdef WDGIF_START_SEC_VAR_ZERO_INIT_8BIT
	#undef WDGIF_START_SEC_VAR_ZERO_INIT_8BIT
	#define START_SEC_VAR_ZERO_INIT_8BIT_9
#endif
#ifdef WDGIF_STOP_SEC_VAR_ZERO_INIT_8BIT
	#undef WDGIF_STOP_SEC_VAR_ZERO_INIT_8BIT
	#define STOP_SEC_VAR
#endif

#ifdef WDGIF_START_SEC_VAR_ZERO_INIT_16BIT
	#undef WDGIF_START_SEC_VAR_ZERO_INIT_16BIT
	#define START_SEC_VAR_ZERO_INIT_16BIT_9
#endif
#ifdef WDGIF_STOP_SEC_VAR_ZERO_INIT_16BIT
	#undef WDGIF_STOP_SEC_VAR_ZERO_INIT_16BIT
	#define STOP_SEC_VAR
#endif

#ifdef WDGIF_START_SEC_VAR_ZERO_INIT_32BIT
	#undef WDGIF_START_SEC_VAR_ZERO_INIT_32BIT
	#define START_SEC_VAR_ZERO_INIT_32BIT_9
#endif
#ifdef WDGIF_STOP_SEC_VAR_ZERO_INIT_32BIT
	#undef WDGIF_STOP_SEC_VAR_ZERO_INIT_32BIT
	#define STOP_SEC_VAR
#endif

#ifdef WDGIF_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
	#undef WDGIF_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_9
#endif
#ifdef WDGIF_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
	#undef WDGIF_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

#ifdef WDGIF_START_SEC_CONST_8BIT
	#undef WDGIF_START_SEC_CONST_8BIT
	#define START_SEC_CONST_8BIT
#endif
#ifdef WDGIF_STOP_SEC_CONST_8BIT
	#undef WDGIF_STOP_SEC_CONST_8BIT
	#define STOP_SEC_CONST
#endif

#ifdef WDGIF_START_SEC_CONST_16BIT
	#undef WDGIF_START_SEC_CONST_16BIT
	#define START_SEC_CONST_16BIT
#endif
#ifdef WDGIF_STOP_SEC_CONST_16BIT
	#undef WDGIF_STOP_SEC_CONST_16BIT
	#define STOP_SEC_CONST
#endif

#ifdef WDGIF_START_SEC_CONST_32BIT
	#undef WDGIF_START_SEC_CONST_32BIT
	#define START_SEC_CONST_32BIT
#endif
#ifdef WDGIF_STOP_SEC_CONST_32BIT
	#undef WDGIF_STOP_SEC_CONST_32BIT
	#define STOP_SEC_CONST
#endif

#ifdef WDGIF_START_SEC_CONST_UNSPECIFIED
	#undef WDGIF_START_SEC_CONST_UNSPECIFIED
	#define START_SEC_CONST_UNSPECIFIED
#endif
#ifdef WDGIF_STOP_SEC_CONST_UNSPECIFIED
	#undef WDGIF_STOP_SEC_CONST_UNSPECIFIED
	#define STOP_SEC_CONST
#endif

/**********************************************************************************************************************
*  WdgIf END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  NvM START
**********************************************************************************************************************/

#ifdef NVM_START_SEC_CODE
	#undef NVM_START_SEC_CODE
	#define START_SEC_CODE
#endif
#ifdef NVM_STOP_SEC_CODE
	#undef NVM_STOP_SEC_CODE
	#define STOP_SEC_CODE
#endif

#ifdef NVM_START_SEC_CONST_8BIT
	#undef NVM_START_SEC_CONST_8BIT
	#define START_SEC_CONST_8BIT
#endif
#ifdef NVM_STOP_SEC_CONST_8BIT
	#undef NVM_STOP_SEC_CONST_8BIT
	#define STOP_SEC_CONST
#endif

#ifdef NVM_START_SEC_CONST_16BIT
	#undef NVM_START_SEC_CONST_16BIT
	#define START_SEC_CONST_16BIT
#endif
#ifdef NVM_STOP_SEC_CONST_16BIT
	#undef NVM_STOP_SEC_CONST_16BIT
	#define STOP_SEC_CONST
#endif

#ifdef NVM_START_SEC_CONST_UNSPECIFIED
	#undef NVM_START_SEC_CONST_UNSPECIFIED
	#define START_SEC_CONST_UNSPECIFIED
#endif
#ifdef NVM_STOP_SEC_CONST_UNSPECIFIED
	#undef NVM_STOP_SEC_CONST_UNSPECIFIED
	#define STOP_SEC_CONST
#endif

#ifdef NVM_START_SEC_CONST_DESCRIPTOR_TABLE
	#undef NVM_START_SEC_CONST_DESCRIPTOR_TABLE
	#define START_SEC_CONST_UNSPECIFIED
#endif
#ifdef NVM_STOP_SEC_CONST_DESCRIPTOR_TABLE
	#undef NVM_STOP_SEC_CONST_DESCRIPTOR_TABLE
	#define STOP_SEC_CONST
#endif

#ifdef NVM_START_SEC_VAR_NOINIT_8BIT
	#undef NVM_START_SEC_VAR_NOINIT_8BIT
	#define START_SEC_VAR_NOINIT_8BIT_9
#endif
#ifdef NVM_STOP_SEC_VAR_NOINIT_8BIT
	#undef NVM_STOP_SEC_VAR_NOINIT_8BIT
	#define STOP_SEC_VAR
#endif

#ifdef NVM_START_SEC_VAR_NOINIT_UNSPECIFIED
	#undef NVM_START_SEC_VAR_NOINIT_UNSPECIFIED
	#define START_SEC_VAR_NOINIT_UNSPECIFIED_9
#endif
#ifdef NVM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
	#undef NVM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

#ifdef NVM_START_SEC_VAR_UNSPECIFIED
	#undef NVM_START_SEC_VAR_UNSPECIFIED
	#define START_SEC_VAR_NOINIT_UNSPECIFIED_9
#endif
#ifdef NVM_STOP_SEC_VAR_UNSPECIFIED
	#undef NVM_STOP_SEC_VAR_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

#ifdef NVM_START_SEC_VAR_FAST_8BIT
	#undef NVM_START_SEC_VAR_FAST_8BIT
	#define START_SEC_VAR_FAST_NOINIT_8BIT_9
#endif
#ifdef NVM_STOP_SEC_VAR_FAST_8BIT
	#undef NVM_STOP_SEC_VAR_FAST_8BIT
	#define STOP_SEC_VAR
#endif

#ifdef NVM_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
	#undef NVM_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_9
#endif
#ifdef NVM_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
	#undef NVM_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
*  NvM END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  Crc START
**********************************************************************************************************************/

#ifdef CRC_START_SEC_CODE
	#undef CRC_START_SEC_CODE
	#define START_SEC_CODE
#endif
#ifdef CRC_STOP_SEC_CODE
	#undef CRC_STOP_SEC_CODE
	#define STOP_SEC_CODE
#endif

#ifdef CRC_START_SEC_CONST_8BIT
	#undef CRC_START_SEC_CONST_8BIT
	#define START_SEC_CONST_8BIT
#endif
#ifdef CRC_STOP_SEC_CONST_8BIT
	#undef CRC_STOP_SEC_CONST_8BIT
	#define STOP_SEC_CONST
#endif

#ifdef CRC_START_SEC_CONST_16BIT
	#undef CRC_START_SEC_CONST_16BIT
	#define START_SEC_CONST_16BIT
#endif
#ifdef CRC_STOP_SEC_CONST_16BIT
	#undef CRC_STOP_SEC_CONST_16BIT
	#define STOP_SEC_CONST
#endif

#ifdef CRC_START_SEC_CONST_32BIT
	#undef CRC_START_SEC_CONST_32BIT
	#define START_SEC_CONST_32BIT
#endif
#ifdef CRC_STOP_SEC_CONST_32BIT
	#undef CRC_STOP_SEC_CONST_32BIT
	#define STOP_SEC_CONST
#endif

/**********************************************************************************************************************
*  Crc END
**********************************************************************************************************************/

/**********************************************************************************************************************
*  WdgM START
**********************************************************************************************************************/

#if defined WDGM_START_SEC_CODE
	#undef WDGM_START_SEC_CODE
	#define START_SEC_CODE
#endif
#ifdef WDGM_STOP_SEC_CODE
	#undef WDGM_STOP_SEC_CODE
	#define STOP_SEC_CODE
#endif

#if defined WDGM_START_SEC_VAR_INIT_8BIT
	#undef WDGM_START_SEC_VAR_INIT_8BIT
	#define START_SEC_VAR_INIT_8BIT_0
#endif
#ifdef WDGM_STOP_SEC_VAR_INIT_8BIT
	#undef WDGM_STOP_SEC_VAR_INIT_8BIT
	#define STOP_SEC_VAR
#endif

#ifdef WDGM_START_SEC_VAR_INIT_16BIT
	#undef WDGM_START_SEC_VAR_INIT_16BIT
	#define START_SEC_VAR_INIT_16BIT_0
#endif
#ifdef WDGM_STOP_SEC_VAR_INIT_16BIT
	#undef WDGM_STOP_SEC_VAR_INIT_16BIT
	#define STOP_SEC_VAR
#endif

#ifdef WDGM_START_SEC_VAR_INIT_32BIT
	#undef WDGM_START_SEC_VAR_INIT_32BIT
	#define START_SEC_VAR_INIT_32BIT_0
#endif
#ifdef WDGM_STOP_SEC_VAR_INIT_32BIT
	#undef WDGM_STOP_SEC_VAR_INIT_32BIT
	#define STOP_SEC_VAR
#endif

#ifdef WDGM_START_SEC_VAR_INIT_UNSPECIFIED
	#undef WDGM_START_SEC_VAR_INIT_UNSPECIFIED
	#undef MEMMAP_ERROR
#endif

#ifdef WDGM_STOP_SEC_VAR_INIT_UNSPECIFIED
	#undef WDGM_STOP_SEC_VAR_INIT_UNSPECIFIED
	#undef MEMMAP_ERROR
#endif

#ifdef WDGM_GLOBAL_START_SEC_VAR_INIT_32BIT
	#undef WDGM_GLOBAL_START_SEC_VAR_INIT_32BIT
	#undef MEMMAP_ERROR
#endif
#ifdef WDGM_GLOBAL_STOP_SEC_VAR_INIT_32BIT
	#undef WDGM_GLOBAL_STOP_SEC_VAR_INIT_32BIT
	#undef MEMMAP_ERROR
#endif

#ifdef WDGM_GLOBAL_SHARED_START_SEC_VAR_INIT_32BIT
	#undef WDGM_GLOBAL_SHARED_START_SEC_VAR_INIT_32BIT
	#undef MEMMAP_ERROR
#endif
#ifdef WDGM_GLOBAL_SHARED_STOP_SEC_VAR_INIT_32BIT
	#undef WDGM_GLOBAL_SHARED_STOP_SEC_VAR_INIT_32BIT
	#undef MEMMAP_ERROR
#endif

#ifdef WDGM_START_SEC_VAR_NOINIT_8BIT
	#undef WDGM_START_SEC_VAR_NOINIT_8BIT
	#define START_SEC_VAR_NOINIT_8BIT_0
#endif
#ifdef WDGM_STOP_SEC_VAR_NOINIT_8BIT
	#undef WDGM_STOP_SEC_VAR_NOINIT_8BIT
	#define STOP_SEC_VAR
#endif

#ifdef WDGM_START_SEC_VAR_NOINIT_16BIT
	#undef WDGM_START_SEC_VAR_NOINIT_16BIT
	#define START_SEC_VAR_NOINIT_16BIT_0
#endif
#ifdef WDGM_STOP_SEC_VAR_NOINIT_16BIT
	#undef WDGM_STOP_SEC_VAR_NOINIT_16BIT
	#define STOP_SEC_VAR
#endif

#ifdef WDGM_START_SEC_VAR_NOINIT_32BIT
	#undef WDGM_START_SEC_VAR_NOINIT_32BIT
	#define START_SEC_VAR_NOINIT_32BIT_0
#endif
#ifdef WDGM_STOP_SEC_VAR_NOINIT_32BIT
	#undef WDGM_STOP_SEC_VAR_NOINIT_32BIT
	#define STOP_SEC_VAR
#endif

#ifdef WDGM_START_SEC_VAR_NOINIT_UNSPECIFIED
	#undef WDGM_START_SEC_VAR_NOINIT_UNSPECIFIED
	#define START_SEC_VAR_NOINIT_UNSPECIFIED_0
#endif
#ifdef WDGM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
	#undef WDGM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

#ifdef WDGM_GLOBAL_START_SEC_VAR_NOINIT_32BIT
	#undef WDGM_GLOBAL_START_SEC_VAR_NOINIT_32BIT
	#undef MEMMAP_ERROR
#endif
#ifdef WDGM_GLOBAL_STOP_SEC_VAR_NOINIT_32BIT
	#undef WDGM_GLOBAL_STOP_SEC_VAR_NOINIT_32BIT
	#undef MEMMAP_ERROR
#endif

#ifdef WDGM_GLOBAL_SHARED_START_SEC_VAR_NOINIT_32BIT
	#undef WDGM_GLOBAL_SHARED_START_SEC_VAR_NOINIT_32BIT
	#undef MEMMAP_ERROR
#endif
#ifdef WDGM_GLOBAL_SHARED_STOP_SEC_VAR_NOINIT_32BIT
	#undef WDGM_GLOBAL_SHARED_STOP_SEC_VAR_NOINIT_32BIT
	#undef MEMMAP_ERROR
#endif

#ifdef WDGM_GLOBAL_SHARED_START_SEC_VAR_NOINIT_UNSPECIFIED
	#undef WDGM_GLOBAL_SHARED_START_SEC_VAR_NOINIT_UNSPECIFIED
	#undef MEMMAP_ERROR
#endif
#ifdef WDGM_GLOBAL_SHARED_STOP_SEC_VAR_NOINIT_UNSPECIFIED
	#undef WDGM_GLOBAL_SHARED_STOP_SEC_VAR_NOINIT_UNSPECIFIED
	#undef MEMMAP_ERROR
#endif

#ifdef WDGM_START_SEC_VAR_ZERO_INIT_8BIT
	#undef WDGM_START_SEC_VAR_ZERO_INIT_8BIT
	#define START_SEC_VAR_ZERO_INIT_8BIT_0
#endif
#ifdef WDGM_STOP_SEC_VAR_ZERO_INIT_8BIT
	#undef WDGM_STOP_SEC_VAR_ZERO_INIT_8BIT
	#define STOP_SEC_VAR
#endif

#ifdef WDGM_START_SEC_VAR_ZERO_INIT_16BIT
	#undef WDGM_START_SEC_VAR_ZERO_INIT_16BIT
	#define START_SEC_VAR_ZERO_INIT_16BIT_0
#endif
#ifdef WDGM_STOP_SEC_VAR_ZERO_INIT_16BIT
	#undef WDGM_STOP_SEC_VAR_ZERO_INIT_16BIT
	#define STOP_SEC_VAR
#endif

#ifdef WDGM_START_SEC_VAR_ZERO_INIT_32BIT
	#undef WDGM_START_SEC_VAR_ZERO_INIT_32BIT
	#define START_SEC_VAR_ZERO_INIT_32BIT_0
#endif
#ifdef WDGM_STOP_SEC_VAR_ZERO_INIT_32BIT
	#undef WDGM_STOP_SEC_VAR_ZERO_INIT_32BIT
	#define STOP_SEC_VAR
#endif

#ifdef WDGM_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
	#undef WDGM_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
	#define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_0
#endif
#ifdef WDGM_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
	#undef WDGM_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
	#define STOP_SEC_VAR
#endif

#ifdef WDGM_GLOBAL_START_SEC_VAR_ZERO_INIT_32BIT
	#undef WDGM_GLOBAL_START_SEC_VAR_ZERO_INIT_32BIT
	#undef MEMMAP_ERROR
#endif
#ifdef WDGM_GLOBAL_STOP_SEC_VAR_ZERO_INIT_32BIT
	#undef WDGM_GLOBAL_STOP_SEC_VAR_ZERO_INIT_32BIT
	#undef MEMMAP_ERROR
#endif

#ifdef WDGM_GLOBAL_START_SEC_VAR_32BIT
	#undef WDGM_GLOBAL_START_SEC_VAR_32BIT
	#undef MEMMAP_ERROR
#endif
#ifdef WDGM_GLOBAL_STOP_SEC_VAR_32BIT
	#undef WDGM_GLOBAL_STOP_SEC_VAR_32BIT
	#undef MEMMAP_ERROR
#endif

#ifdef WDGM_GLOBAL_START_SEC_VAR_BOOLEAN
	#undef WDGM_GLOBAL_START_SEC_VAR_BOOLEAN
	#undef MEMMAP_ERROR
#endif
#ifdef WDGM_GLOBAL_STOP_SEC_VAR_BOOLEAN
	#undef WDGM_GLOBAL_STOP_SEC_VAR_BOOLEAN
	#undef MEMMAP_ERROR
#endif

#ifdef WDGM_GLOBAL_START_SEC_VAR_NOINIT_UNSPECIFIED
	#undef WDGM_GLOBAL_START_SEC_VAR_NOINIT_UNSPECIFIED
	#undef MEMMAP_ERROR
#endif
#ifdef WDGM_GLOBAL_STOP_SEC_VAR_NOINIT_UNSPECIFIED
	#undef WDGM_GLOBAL_STOP_SEC_VAR_NOINIT_UNSPECIFIED
	#undef MEMMAP_ERROR
#endif

#ifdef WDGM_GLOBAL_SHARED_START_SEC_VAR_ZERO_INIT_32BIT
	#undef WDGM_GLOBAL_SHARED_START_SEC_VAR_ZERO_INIT_32BIT
	#undef MEMMAP_ERROR
#endif
#ifdef WDGM_GLOBAL_SHARED_STOP_SEC_VAR_ZERO_INIT_32BIT
	#undef WDGM_GLOBAL_SHARED_STOP_SEC_VAR_ZERO_INIT_32BIT
	#undef MEMMAP_ERROR
#endif

#ifdef WDGM_SE0_START_SEC_VAR_NOINIT_UNSPECIFIED
	#undef WDGM_SE0_START_SEC_VAR_NOINIT_UNSPECIFIED
	#undef MEMMAP_ERROR
#endif
#ifdef WDGM_SE0_STOP_SEC_VAR_NOINIT_UNSPECIFIED
	#undef WDGM_SE0_STOP_SEC_VAR_NOINIT_UNSPECIFIED
	#undef MEMMAP_ERROR
#endif

#ifdef WDGM_START_SEC_CONST_8BIT
	#undef WDGM_START_SEC_CONST_8BIT
	#define START_SEC_CONST_8BIT
#endif
#ifdef WDGM_STOP_SEC_CONST_8BIT
	#undef WDGM_STOP_SEC_CONST_8BIT
	#define STOP_SEC_CONST
#endif

#ifdef WDGM_START_SEC_CONST_16BIT
	#undef WDGM_START_SEC_CONST_16BIT
	#define START_SEC_CONST_16BIT
#endif
#ifdef WDGM_STOP_SEC_CONST_16BIT
	#undef WDGM_STOP_SEC_CONST_16BIT
	#define STOP_SEC_CONST
#endif

#ifdef WDGM_START_SEC_CONST_32BIT
	#undef WDGM_START_SEC_CONST_32BIT
	#define START_SEC_CONST_32BIT
#endif
#ifdef WDGM_STOP_SEC_CONST_32BIT
	#undef WDGM_STOP_SEC_CONST_32BIT
	#define STOP_SEC_CONST
#endif

#ifdef WDGM_START_SEC_CONST_UNSPECIFIED
	#undef WDGM_START_SEC_CONST_UNSPECIFIED
	#define START_SEC_CONST_UNSPECIFIED
#endif
#ifdef WDGM_STOP_SEC_CONST_UNSPECIFIED
	#undef WDGM_STOP_SEC_CONST_UNSPECIFIED
	#define STOP_SEC_CONST
#endif

/**********************************************************************************************************************
*  WdgM END
**********************************************************************************************************************/

/**********************************************************************************************************************
 *  COMM START 
 *********************************************************************************************************************/

/*******  CODE sections **********************************************************************************************/

#ifdef COMM_START_SEC_CODE
  #undef COMM_START_SEC_CODE
  #define START_SEC_CODE                            /* mapped to default code section */
#endif
#ifdef COMM_STOP_SEC_CODE
  #undef COMM_STOP_SEC_CODE
  #define STOP_SEC_CODE                             /* default code stop section */
#endif

#ifdef COMM_START_SEC_APPL_CODE
  #undef COMM_START_SEC_APPL_CODE
  #define START_SEC_CODE                            /* mapped to default code section */
#endif
#ifdef COMM_STOP_SEC_APPL_CODE
  #undef COMM_STOP_SEC_APPL_CODE
  #define STOP_SEC_CODE                             /* default code stop section */
#endif

/*******  CONST sections  ********************************************************************************************/

/* CONST sections */

#ifdef COMM_START_SEC_CONST_8BIT
# undef COMM_START_SEC_CONST_8BIT
# define START_SEC_CONST_8BIT                       /* mapped to default const 8bit section */
#endif
#ifdef COMM_STOP_SEC_CONST_8BIT
# undef COMM_STOP_SEC_CONST_8BIT
# define STOP_SEC_CONST                             /* default const stop section */
#endif

#ifdef COMM_START_SEC_CONST_16BIT
# undef COMM_START_SEC_CONST_16BIT
# define START_SEC_CONST_16BIT
#endif
#ifdef COMM_STOP_SEC_CONST_16BIT
# undef COMM_STOP_SEC_CONST_16BIT
# define STOP_SEC_CONST
#endif

#ifdef COMM_START_SEC_CONST_32BIT
# undef COMM_START_SEC_CONST_32BIT
# define START_SEC_CONST_32BIT
#endif
#ifdef COMM_STOP_SEC_CONST_32BIT
# undef COMM_STOP_SEC_CONST_32BIT
# define STOP_SEC_CONST
#endif

#ifdef COMM_START_SEC_CONST_UNSPECIFIED
# undef COMM_START_SEC_CONST_UNSPECIFIED
# define START_SEC_CONST_UNSPECIFIED
#endif
#ifdef COMM_STOP_SEC_CONST_UNSPECIFIED
# undef COMM_STOP_SEC_CONST_UNSPECIFIED
# define STOP_SEC_CONST
#endif


/*******  VAR sections  **********************************************************************************************/

/* VAR NOINIT sections */

#ifdef COMM_START_SEC_VAR_NOINIT_8BIT
# undef COMM_START_SEC_VAR_NOINIT_8BIT
# define START_SEC_VAR_NOINIT_8BIT_9
#endif
#ifdef COMM_STOP_SEC_VAR_NOINIT_8BIT
# undef COMM_STOP_SEC_VAR_NOINIT_8BIT
# define STOP_SEC_VAR
#endif

#ifdef COMM_START_SEC_VAR_NOINIT_16BIT
# undef COMM_START_SEC_VAR_NOINIT_16BIT
# define START_SEC_VAR_NOINIT_16BIT_9
#endif
#ifdef COMM_STOP_SEC_VAR_NOINIT_16BIT
# undef COMM_STOP_SEC_VAR_NOINIT_16BIT
# define STOP_SEC_VAR
#endif

#ifdef COMM_START_SEC_VAR_NOINIT_32BIT
# undef COMM_START_SEC_VAR_NOINIT_32BIT
# define START_SEC_VAR_NOINIT_32BIT_9
#endif
#ifdef COMM_STOP_SEC_VAR_NOINIT_32BIT
# undef COMM_STOP_SEC_VAR_NOINIT_32BIT
# define STOP_SEC_VAR
#endif

#ifdef COMM_START_SEC_VAR_NOINIT_UNSPECIFIED
# undef COMM_START_SEC_VAR_NOINIT_UNSPECIFIED
# define START_SEC_VAR_NOINIT_UNSPECIFIED_9
#endif
#ifdef COMM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# undef COMM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# define STOP_SEC_VAR
#endif


/* VAR ZERO INIT sections */

#ifdef COMM_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
# undef COMM_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
# define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_9
#endif
#ifdef COMM_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
# undef COMM_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
# define STOP_SEC_VAR
#endif

/* VAR NVRAM sections */

#ifdef COMM_START_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
# undef COMM_START_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
# define START_SEC_VAR_FAST_NOINIT_UNSPECIFIED_9
#endif
#ifdef COMM_STOP_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
# undef COMM_STOP_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
# define STOP_SEC_VAR
#endif

/* Postbuild CFG CONST sections */

/* Root pointer to postbuild data */
#ifdef COMM_START_SEC_PBCFG_ROOT
# undef COMM_START_SEC_PBCFG_ROOT
# define START_SEC_CONST_PBCFG
#endif
#ifdef COMM_STOP_SEC_PBCFG_ROOT
# undef COMM_STOP_SEC_PBCFG_ROOT
# define STOP_SEC_CONST
#endif
/**********************************************************************************************************************
 *  COMM END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  CanSM START 
 *********************************************************************************************************************/

/*******  CODE sections **********************************************************************************************/

#ifdef CANSM_START_SEC_CODE
# undef CANSM_START_SEC_CODE
# define START_SEC_CODE                                               /* mapped to default code section */
#endif

#ifdef CANSM_STOP_SEC_CODE
# undef CANSM_STOP_SEC_CODE
# define STOP_SEC_CODE                                                /* default code stop section */
#endif

#ifdef CANSM_START_SEC_APPL_CODE
# undef CANSM_START_SEC_APPL_CODE
# define START_SEC_CODE                                               /* mapped to default code section */
#endif

#ifdef CANSM_STOP_SEC_APPL_CODE
# undef CANSM_STOP_SEC_APPL_CODE
# define STOP_SEC_CODE                                                /* default code stop section */
#endif

/*******  CONST sections  ********************************************************************************************/

/* CONST sections */

#ifdef CANSM_START_SEC_CONST_8BIT
# undef CANSM_START_SEC_CONST_8BIT
# define START_SEC_CONST_8BIT
#endif

#ifdef CANSM_STOP_SEC_CONST_8BIT
# undef CANSM_STOP_SEC_CONST_8BIT
# define STOP_SEC_CONST                                               /* default const stop section */
#endif

#ifdef CANSM_START_SEC_CONST_16BIT
# undef CANSM_START_SEC_CONST_16BIT
# define START_SEC_CONST_16BIT
#endif

#ifdef CANSM_STOP_SEC_CONST_16BIT
# undef CANSM_STOP_SEC_CONST_16BIT
# define STOP_SEC_CONST                                               /* default const stop section */
#endif

#ifdef CANSM_START_SEC_CONST_32BIT
# undef CANSM_START_SEC_CONST_32BIT
# define START_SEC_CONST_32BIT
#endif

#ifdef CANSM_STOP_SEC_CONST_32BIT
# undef CANSM_STOP_SEC_CONST_32BIT
# define STOP_SEC_CONST
#endif

/* FAST CONST sections */

/* Postbuild CFG CONST sections */

/* Root pointer to postbuild data */
#ifdef CANSM_START_SEC_PBCFG_ROOT
# undef CANSM_START_SEC_PBCFG_ROOT
# define START_SEC_CONST_PBCFG
#endif
#ifdef CANSM_STOP_SEC_PBCFG_ROOT
# undef CANSM_STOP_SEC_PBCFG_ROOT
# define STOP_SEC_CONST
#endif

/* Root table for postbuild data */

#ifdef CANSM_START_SEC_PBCFG
# undef CANSM_START_SEC_PBCFG
# define START_SEC_CONST_PBCFG
#endif
#ifdef CANSM_STOP_SEC_PBCFG
# undef CANSM_STOP_SEC_PBCFG
# define STOP_SEC_CONST
#endif


/*******  VAR sections  **********************************************************************************************/

/* VAR INIT sections */

#ifdef CANSM_START_SEC_VAR_INIT_8BIT
# undef CANSM_START_SEC_VAR_INIT_8BIT
# define START_SEC_VAR_INIT_8BIT_9
#endif

#ifdef CANSM_STOP_SEC_VAR_INIT_8BIT
# undef CANSM_STOP_SEC_VAR_INIT_8BIT
# define STOP_SEC_VAR
#endif

/* VAR NOINIT sections */

#ifdef CANSM_START_SEC_VAR_NOINIT_8BIT
# undef CANSM_START_SEC_VAR_NOINIT_8BIT
# define START_SEC_VAR_NOINIT_8BIT_9
#endif

#ifdef CANSM_STOP_SEC_VAR_NOINIT_8BIT
# undef CANSM_STOP_SEC_VAR_NOINIT_8BIT
# define STOP_SEC_VAR
#endif

#ifdef CANSM_START_SEC_VAR_NOINIT_UNSPECIFIED
# undef CANSM_START_SEC_VAR_NOINIT_UNSPECIFIED
# define START_SEC_VAR_NOINIT_UNSPECIFIED_9
#endif

#ifdef CANSM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# undef CANSM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# define STOP_SEC_VAR
#endif

/* VAR ZERO INIT sections */

#ifdef CANSM_START_SEC_VAR_ZERO_INIT_8BIT
# undef CANSM_START_SEC_VAR_ZERO_INIT_8BIT
# define START_SEC_VAR_ZERO_INIT_8BIT_9
#endif

#ifdef CANSM_STOP_SEC_VAR_ZERO_INIT_8BIT
# undef CANSM_STOP_SEC_VAR_ZERO_INIT_8BIT
# define STOP_SEC_VAR
#endif

/* VAR FAST INIT sections */


/* VAR FAST NOINIT sections */


/* VAR FAST ZERO INIT sections */


/**********************************************************************************************************************
 *  CanSM END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  CddFiat START 
 *********************************************************************************************************************/

/*******  VAR sections  ********************************************************************************************/

#ifdef CDDFIAT_START_SEC_VAR_NOINIT_8BIT
    #undef CDDFIAT_START_SEC_VAR_NOINIT_8BIT
    #define START_SEC_VAR_NOINIT_8BIT_9
#endif

#ifdef CDDFIAT_STOP_SEC_VAR_NOINIT_8BIT
    #undef CDDFIAT_STOP_SEC_VAR_NOINIT_8BIT
    #define STOP_SEC_VAR
#endif

#ifdef CDDFIAT_START_SEC_VAR_INIT_UNSPECIFIED
    #undef CDDFIAT_START_SEC_VAR_INIT_UNSPECIFIED
    #define START_SEC_VAR_INIT_UNSPECIFIED_9
#endif

#ifdef CDDFIAT_STOP_SEC_VAR_INIT_UNSPECIFIED
    #undef CDDFIAT_STOP_SEC_VAR_INIT_UNSPECIFIED
    #define STOP_SEC_VAR
#endif
#ifdef CDDFIAT_START_SEC_VAR_NOINIT_UNSPECIFIED
    #undef CDDFIAT_START_SEC_VAR_NOINIT_UNSPECIFIED
    #define START_SEC_VAR_NOINIT_UNSPECIFIED_9
#endif
#ifdef CDDFIAT_STOP_SEC_VAR_NOINIT_UNSPECIFIED
    #undef CDDFIAT_STOP_SEC_VAR_NOINIT_UNSPECIFIED
    #define STOP_SEC_VAR
#endif

/*******  CONST sections  ********************************************************************************************/

#ifdef CDDFIAT_START_SEC_CONST_8BIT
    #undef CDDFIAT_START_SEC_CONST_8BIT
    #define START_SEC_CONST_8BIT
#endif

#ifdef CDDFIAT_STOP_SEC_CONST_8BIT
    #undef CDDFIAT_STOP_SEC_CONST_8BIT
    #define STOP_SEC_CONST
#endif

/*******  CODE sections  ********************************************************************************************/

#ifdef CDDFIAT_START_SEC_CODE
    #undef CDDFIAT_START_SEC_CODE
    #define START_SEC_CODE
#endif

#ifdef CDDFIAT_STOP_SEC_CODE
    #undef CDDFIAT_STOP_SEC_CODE
    #define STOP_SEC_CODE
#endif

/**********************************************************************************************************************
 *  CddFiat END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  XCP START 
 *********************************************************************************************************************/

/*******  CODE sections **********************************************************************************************/

#ifdef XCP_START_SEC_CODE 
    #undef XCP_START_SEC_CODE 
    #define START_SEC_CODE
#endif

#ifdef XCP_STOP_SEC_CODE 
    #undef XCP_STOP_SEC_CODE 
    #define STOP_SEC_CODE
#endif


/*******  CONST sections  ********************************************************************************************/

/* CONST sections */

#ifdef XCP_START_SEC_CONST_UNSPECIFIED
    #undef XCP_START_SEC_CONST_UNSPECIFIED
    #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef XCP_STOP_SEC_CONST_UNSPECIFIED
    #undef XCP_STOP_SEC_CONST_UNSPECIFIED
    #define STOP_SEC_CONST
#endif

#ifdef XCP_START_SEC_CONST_16BIT 
    #undef XCP_START_SEC_CONST_16BIT 
    #define START_SEC_CONST_16BIT
#endif

#ifdef XCP_STOP_SEC_CONST_16BIT 
    #undef XCP_STOP_SEC_CONST_16BIT 
    #define STOP_SEC_CONST
#endif

#ifdef XCP_START_SEC_CONST_8BIT 
    #undef XCP_START_SEC_CONST_8BIT 
    #define START_SEC_CONST_8BIT
#endif

#ifdef XCP_STOP_SEC_CONST_8BIT 
    #undef XCP_STOP_SEC_CONST_8BIT 
    #define STOP_SEC_CONST
#endif


/*******  VAR sections  **********************************************************************************************/

/* VAR INIT sections */

#ifdef XCP_START_SEC_VAR_NOINIT_UNSPECIFIED 
    #undef XCP_START_SEC_VAR_NOINIT_UNSPECIFIED 
    #define START_SEC_VAR_NOINIT_UNSPECIFIED_9
#endif

#ifdef XCP_STOP_SEC_VAR_NOINIT_UNSPECIFIED 
    #undef XCP_STOP_SEC_VAR_NOINIT_UNSPECIFIED 
    #define STOP_SEC_VAR
#endif

#ifdef XCP_START_SEC_VAR_NOINIT_8BIT 
    #undef XCP_START_SEC_VAR_NOINIT_8BIT 
    #define START_SEC_VAR_NOINIT_8BIT_9
#endif

#ifdef XCP_STOP_SEC_VAR_NOINIT_8BIT 
    #undef XCP_STOP_SEC_VAR_NOINIT_8BIT 
    #define STOP_SEC_VAR
#endif


/**********************************************************************************************************************
 *  XCP END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  CANXCP START 
 *********************************************************************************************************************/

/*******  CODE sections **********************************************************************************************/

#ifdef CANXCP_START_SEC_CODE
  #undef CANXCP_START_SEC_CODE
  #define START_SEC_CODE                            /* mapped to default code section */
#endif

#ifdef CANXCP_STOP_SEC_CODE
  #undef CANXCP_STOP_SEC_CODE
  #define STOP_SEC_CODE                             /* default code stop section */
#endif


/*******  CONST sections  ********************************************************************************************/

/* CONST sections */

#ifdef CANXCP_START_SEC_CONST_8BIT
  #undef CANXCP_START_SEC_CONST_8BIT
  #define START_SEC_CONST_8BIT                      /* mapped to const 8 bit section */
#endif

#ifdef CANXCP_STOP_SEC_CONST_8BIT
  #undef CANXCP_STOP_SEC_CONST_8BIT
  #define STOP_SEC_CONST                            /* default const stop section */
#endif

#ifdef CANXCP_START_SEC_CONST_UNSPECIFIED
  #undef CANXCP_START_SEC_CONST_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED               /* mapped to const unspecified bit section */
#endif

#ifdef CANXCP_STOP_SEC_CONST_UNSPECIFIED
  #undef CANXCP_STOP_SEC_CONST_UNSPECIFIED
  #define STOP_SEC_CONST                            /* default const stop section */
#endif


/* Post build config unspecified */

#ifdef CANXCP_START_SEC_PBCFG_ROOT
  #undef CANXCP_START_SEC_PBCFG_ROOT
  #define START_SEC_CONST_PBCFG                     /* mapped to const unspecified section */
#endif

#ifdef CANXCP_STOP_SEC_PBCFG_ROOT
  #undef CANXCP_STOP_SEC_PBCFG_ROOT
  #define STOP_SEC_CONST                            /* default const stop section */
#endif


#ifdef CANXCP_START_SEC_PBCFG
  #undef CANXCP_START_SEC_PBCFG
  #define START_SEC_CONST_PBCFG                     /* mapped to const unspecified section */
#endif

#ifdef CANXCP_STOP_SEC_PBCFG
  #undef CANXCP_STOP_SEC_PBCFG
  #define STOP_SEC_CONST                            /* default const stop section */
#endif


/*******  VAR sections  **********************************************************************************************/

/* VAR INIT sections */

#ifdef CANXCP_START_SEC_VAR_NOINIT_8BIT
  #undef CANXCP_START_SEC_VAR_NOINIT_8BIT
  #define START_SEC_VAR_NOINIT_8BIT_9                 /* mapped to uninitialized RAM 8bit section */
#endif

#ifdef CANXCP_STOP_SEC_VAR_NOINIT_8BIT
  #undef CANXCP_STOP_SEC_VAR_NOINIT_8BIT
  #define STOP_SEC_VAR                              /* default RAM stop section */
#endif


/* Var noinit unspecified */
#ifdef CANXCP_START_SEC_VAR_NOINIT_UNSPECIFIED
  #undef CANXCP_START_SEC_VAR_NOINIT_UNSPECIFIED
  #define START_SEC_VAR_NOINIT_UNSPECIFIED_9          /* mapped to uninitialized RAM unspecified section */
#endif

#ifdef CANXCP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
  #undef CANXCP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
  #define STOP_SEC_VAR                              /* default RAM stop section */
#endif


/**********************************************************************************************************************
 *  CANXCP END
 *********************************************************************************************************************/

/* ==== Start sections mapping ==== */
#ifdef DCM_START_SEC_CONST_8BIT
# undef DCM_START_SEC_CONST_8BIT
# define START_SEC_CONST_8BIT                                        /*mapped to default const section */
#endif

#ifdef DCM_START_SEC_CONST_16BIT
# undef DCM_START_SEC_CONST_16BIT
# define START_SEC_CONST_16BIT                                       /*mapped to default const section */
#endif

#ifdef DCM_START_SEC_CONST_32BIT
# undef DCM_START_SEC_CONST_32BIT
# define START_SEC_CONST_32BIT                                       /*mapped to default const section */
#endif

#ifdef DCM_START_SEC_CONST_UNSPECIFIED
# undef DCM_START_SEC_CONST_UNSPECIFIED
# define START_SEC_CONST_UNSPECIFIED                                 /*mapped to default const section */
#endif

#ifdef DCM_START_SEC_CALIB_8BIT
# undef DCM_START_SEC_CALIB_8BIT
# define START_SEC_CONST_8BIT                                        /*mapped to default CALIB section */
#endif

#ifdef DCM_START_SEC_CALIB_16BIT
# undef DCM_START_SEC_CALIB_16BIT
# define START_SEC_CONST_16BIT                                       /*mapped to default CALIB section */
#endif

#ifdef DCM_START_SEC_CALIB_32BIT
# undef DCM_START_SEC_CALIB_32BIT
# define START_SEC_CONST_32BIT                                       /*mapped to default CALIB section */
#endif

#ifdef DCM_START_SEC_CALIB_UNSPECIFIED
# undef DCM_START_SEC_CALIB_UNSPECIFIED
# define START_SEC_CONST_UNSPECIFIED                                 /*mapped to default CALIB section */
#endif

#ifdef DCM_START_SEC_VAR_NOINIT_8BIT
# undef DCM_START_SEC_VAR_NOINIT_8BIT
# define START_SEC_VAR_NOINIT_8BIT_9                                   /*mapped to default var section*/
#endif

#ifdef DCM_START_SEC_VAR_NOINIT_16BIT
# undef DCM_START_SEC_VAR_NOINIT_16BIT
# define START_SEC_VAR_NOINIT_16BIT_9                                  /*mapped to default var section*/
#endif

#ifdef DCM_START_SEC_VAR_NOINIT_32BIT
# undef DCM_START_SEC_VAR_NOINIT_32BIT
# define START_SEC_VAR_NOINIT_32BIT_9                                  /*mapped to default var section*/
#endif

#ifdef DCM_START_SEC_VAR_NOINIT_UNSPECIFIED
# undef DCM_START_SEC_VAR_NOINIT_UNSPECIFIED
# define START_SEC_VAR_NOINIT_UNSPECIFIED_9                            /*mapped to default var section*/
#endif

#ifdef DCM_START_SEC_CODE
# undef DCM_START_SEC_CODE
# define START_SEC_CODE                                              /*mapped to default code section*/
#endif

#ifdef DCM_APPL_START_SEC_CODE
# undef DCM_APPL_START_SEC_CODE
# define START_SEC_CODE                                              /*default appl code section*/
#endif

/* ==== Stop sections mapping ==== */

#ifdef DCM_STOP_SEC_CONST_8BIT
# undef DCM_STOP_SEC_CONST_8BIT
# define STOP_SEC_CONST                                              /*default const section */
#endif

#ifdef DCM_STOP_SEC_CONST_16BIT
# undef DCM_STOP_SEC_CONST_16BIT
# define STOP_SEC_CONST                                              /*default const section */
#endif

#ifdef DCM_STOP_SEC_CONST_32BIT
# undef DCM_STOP_SEC_CONST_32BIT
# define STOP_SEC_CONST                                              /*default const section */
#endif

#ifdef DCM_STOP_SEC_CONST_UNSPECIFIED
# undef DCM_STOP_SEC_CONST_UNSPECIFIED
# define STOP_SEC_CONST                                              /*default const section */
#endif

#ifdef DCM_STOP_SEC_CALIB_8BIT
# undef DCM_STOP_SEC_CALIB_8BIT
# define STOP_SEC_CONST                                              /*default CALIB section */
#endif

#ifdef DCM_STOP_SEC_CALIB_16BIT
# undef DCM_STOP_SEC_CALIB_16BIT
# define STOP_SEC_CONST                                              /*default CALIB section */
#endif

#ifdef DCM_STOP_SEC_CALIB_32BIT
# undef DCM_STOP_SEC_CALIB_32BIT
# define STOP_SEC_CONST                                              /*default CALIB section */
#endif

#ifdef DCM_STOP_SEC_CALIB_UNSPECIFIED
# undef DCM_STOP_SEC_CALIB_UNSPECIFIED
# define STOP_SEC_CONST                                              /*default CALIB section */
#endif

#ifdef DCM_STOP_SEC_VAR_NOINIT_8BIT
# undef DCM_STOP_SEC_VAR_NOINIT_8BIT
# define STOP_SEC_VAR                                                /*default var section*/
#endif

#ifdef DCM_STOP_SEC_VAR_NOINIT_16BIT
# undef DCM_STOP_SEC_VAR_NOINIT_16BIT
# define STOP_SEC_VAR                                                /*default var section*/
#endif

#ifdef DCM_STOP_SEC_VAR_NOINIT_32BIT
# undef DCM_STOP_SEC_VAR_NOINIT_32BIT
# define STOP_SEC_VAR                                                /*default var section*/
#endif

#ifdef DCM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# undef DCM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# define STOP_SEC_VAR                                                /*default var section*/
#endif

#ifdef DCM_STOP_SEC_CODE
# undef DCM_STOP_SEC_CODE
# define STOP_SEC_CODE                                               /*default code section*/
#endif

#ifdef DCM_APPL_STOP_SEC_CODE
# undef DCM_APPL_STOP_SEC_CODE
# define STOP_SEC_CODE                                               /*default appl code section*/
#endif

/** DEM ***************************************************************************/
/*---------------------START-MODULE-SPECIFIC-START-SECTIONS-----------------------*/
                                                              /* code section */
#if defined (DEM_START_SEC_CODE)
    #undef DEM_START_SEC_CODE
    #define START_SEC_CODE
#endif
                                                              /* application code section */
#if defined (DEM_APPL_START_SEC_CODE)
    #undef DEM_APPL_START_SEC_CODE
    #define START_SEC_CODE
#endif
                                                              /* vars initialized by startup code */
#if defined (DEM_START_SEC_VAR_8BIT)
    #undef DEM_START_SEC_VAR_8BIT
    #define START_SEC_VAR_INIT_8BIT_9
#endif
#if defined (DEM_START_SEC_VAR_32BIT)
    #undef DEM_START_SEC_VAR_32BIT
    #define START_SEC_VAR_INIT_32BIT_9
#endif
                                                              /* never initialized vars with high number of accesses */
#if defined (DEM_START_SEC_VAR_FAST_8BIT)
    #undef DEM_START_SEC_VAR_FAST_8BIT
    #define START_SEC_VAR_FAST_NOINIT_8BIT_9
#endif
#if defined (DEM_START_SEC_VAR_FAST_16BIT)
    #undef DEM_START_SEC_VAR_FAST_16BIT
    #define START_SEC_VAR_FAST_NOINIT_16BIT_9
#endif
#if defined (DEM_START_SEC_VAR_FAST_32BIT)
    #undef DEM_START_SEC_VAR_FAST_32BIT
    #define START_SEC_VAR_FAST_NOINIT_32BIT_9
#endif
                                                              /* never initialized vars */
#if defined (DEM_START_SEC_VAR_NOINIT_8BIT)
    #undef DEM_START_SEC_VAR_NOINIT_8BIT
    #define START_SEC_VAR_NOINIT_8BIT_9
#endif
#if defined (DEM_START_SEC_VAR_NOINIT_16BIT)
    #undef DEM_START_SEC_VAR_NOINIT_16BIT
    #define START_SEC_VAR_NOINIT_16BIT_9
#endif
#if defined (DEM_START_SEC_VAR_NOINIT_UNSPECIFIED)
    #undef DEM_START_SEC_VAR_NOINIT_UNSPECIFIED
    #define START_SEC_VAR_NOINIT_UNSPECIFIED_9
#endif
                                                              /* vars saved in non volatile memory */
#if defined (DEM_START_SEC_VAR_SAVED_ZONE0_UNSPECIFIED)
    #undef DEM_START_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
    #define START_SEC_VAR_FAST_NOINIT_UNSPECIFIED_9
#endif
                                                              /* global or static constants */
#if defined (DEM_START_SEC_CONST_8BIT)
    #undef DEM_START_SEC_CONST_8BIT
    #define START_SEC_CONST_8BIT
#endif
#if defined (DEM_START_SEC_CONST_32BIT)
    #undef DEM_START_SEC_CONST_32BIT
    #define START_SEC_CONST_32BIT
#endif
#if defined (DEM_START_SEC_CONST_UNSPECIFIED)
    #undef DEM_START_SEC_CONST_UNSPECIFIED
    #define START_SEC_CONST_UNSPECIFIED
#endif
                                                              /* global or static constants (linktime) */
#if defined (DEM_START_SEC_CONST_LCFG)
    #undef DEM_START_SEC_CONST_LCFG
    #define START_SEC_CONST_UNSPECIFIED
#endif
                                                              /* global or static constants (postbuild) */
#if defined (DEM_START_SEC_PBCONST_ROOT)
    #undef DEM_START_SEC_PBCONST_ROOT
    #define START_SEC_CONST_PBCFG
#endif
#if defined (DEM_START_SEC_PBCONST)
    #undef DEM_START_SEC_PBCONST
    #define START_SEC_CONST_PBCFG
#endif
/*---------------------STOP-MODULE-SPECIFIC-START-SECTIONS------------------------*/

/*---------------------START-MODULE-SPECIFIC-STOP-SECTIONS------------------------*/

#if defined (DEM_STOP_SEC_CODE)
    #undef DEM_STOP_SEC_CODE
    #define STOP_SEC_CODE
#endif
                                                             
#if defined (DEM_APPL_STOP_SEC_CODE)
    #undef DEM_APPL_STOP_SEC_CODE
    #define STOP_SEC_CODE
#endif

#if defined (DEM_STOP_SEC_VAR_8BIT)
    #undef DEM_STOP_SEC_VAR_8BIT
    #define STOP_SEC_VAR
#endif
#if defined (DEM_STOP_SEC_VAR_32BIT)
    #undef DEM_STOP_SEC_VAR_32BIT
    #define STOP_SEC_VAR
#endif


#if defined (DEM_STOP_SEC_VAR_FAST_8BIT)
    #undef DEM_STOP_SEC_VAR_FAST_8BIT
    #define STOP_SEC_VAR
#endif
#if defined (DEM_STOP_SEC_VAR_FAST_16BIT)
    #undef DEM_STOP_SEC_VAR_FAST_16BIT
    #define STOP_SEC_VAR
#endif
#if defined (DEM_STOP_SEC_VAR_FAST_32BIT)
    #undef DEM_STOP_SEC_VAR_FAST_32BIT
    #define STOP_SEC_VAR
#endif

#if defined (DEM_STOP_SEC_VAR_NOINIT_8BIT)
    #undef DEM_STOP_SEC_VAR_NOINIT_8BIT
    #define STOP_SEC_VAR
#endif
#if defined (DEM_STOP_SEC_VAR_NOINIT_16BIT)
    #undef DEM_STOP_SEC_VAR_NOINIT_16BIT
    #define STOP_SEC_VAR
#endif
#if defined (DEM_STOP_SEC_VAR_NOINIT_UNSPECIFIED)
    #undef DEM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
    #define STOP_SEC_VAR
#endif

#if defined (DEM_STOP_SEC_VAR_SAVED_ZONE0_UNSPECIFIED)
    #undef DEM_STOP_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
    #define STOP_SEC_VAR
#endif

#if defined (DEM_STOP_SEC_CONST_8BIT)
    #undef DEM_STOP_SEC_CONST_8BIT
    #define STOP_SEC_CONST
#endif
#if defined (DEM_STOP_SEC_CONST_32BIT)
    #undef DEM_STOP_SEC_CONST_32BIT
    #define STOP_SEC_CONST
#endif
#if defined (DEM_STOP_SEC_CONST_UNSPECIFIED)
    #undef DEM_STOP_SEC_CONST_UNSPECIFIED
    #define STOP_SEC_CONST
#endif

#if defined (DEM_STOP_SEC_CONST_LCFG)
    #undef DEM_STOP_SEC_CONST_LCFG
    #define STOP_SEC_CONST
#endif

#if defined (DEM_STOP_SEC_PBCONST_ROOT)
    #undef DEM_STOP_SEC_PBCONST_ROOT
    #define STOP_SEC_CONST
#endif
#if defined (DEM_STOP_SEC_PBCONST)
    #undef DEM_STOP_SEC_PBCONST
    #define STOP_SEC_CONST
#endif
/*---------------------STOP-MODULE-SPECIFIC-STOP-SECTIONS------------------------*/
/** End of DEM *******************************************************************/


/* Kernbauer Version: 1.16 Konfiguration: DrvCAN Erzeugungsgangnummer: 595 */


/**********************************************************************************************************************
 *  Can START 
 *********************************************************************************************************************/

#if defined (CAN_REMAP_PB_SECTIONS)
/* for none PB variants the code will be mapped to standard sections, so the generated and static code can ignore the variant handling */
# if defined (CAN_START_SEC_PBCFG)
#  undef CAN_START_SEC_PBCFG                /* PRQA S 0841 */ /* MD_MSR_19.6 */
#  define CAN_START_SEC_CONST_UNSPECIFIED
# endif
# if defined (CAN_STOP_SEC_PBCFG)
#  undef CAN_STOP_SEC_PBCFG                 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#  define CAN_STOP_SEC_CONST_UNSPECIFIED
# endif

# if defined (CAN_START_SEC_VAR_PBCFG)
#  undef CAN_START_SEC_VAR_PBCFG            /* PRQA S 0841 */ /* MD_MSR_19.6 */
#  define CAN_START_SEC_VAR_NOINIT_UNSPECIFIED_9
# endif
# if defined (CAN_STOP_SEC_VAR_PBCFG)
#  undef CAN_STOP_SEC_VAR_PBCFG             /* PRQA S 0841 */ /* MD_MSR_19.6 */
#  define CAN_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# endif
#endif

/*******  CODE sections **********************************************************************************************/

#ifdef CAN_START_SEC_CODE                             /* CAN code */ /* PRQA S 0883 */ /* Appears only while testing */
# undef CAN_START_SEC_CODE                              /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CODE                               /* mapped to default code section */
#endif
#ifdef CAN_STOP_SEC_CODE
# undef CAN_STOP_SEC_CODE                               /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CODE
#endif

#ifdef CAN_START_SEC_STATIC_CODE                      /* CAN static code */
# undef CAN_START_SEC_STATIC_CODE                       /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CODE                               /* mapped to default code section */
#endif
#ifdef CAN_STOP_SEC_STATIC_CODE
# undef CAN_STOP_SEC_STATIC_CODE                        /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CODE
#endif

#ifdef CAN_START_SEC_CODE_APPL                        /* Appl code (generic precopy)*/
# undef CAN_START_SEC_CODE_APPL                         /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CODE                               /* mapped to default code section */
#endif
#ifdef CAN_STOP_SEC_CODE_APPL
# undef CAN_STOP_SEC_CODE_APPL                          /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CODE
#endif

/*******  CONST sections  ********************************************************************************************/

/* CONST sections */

#ifdef CAN_START_SEC_CONST_8BIT                       /* Const 8bit */
# undef CAN_START_SEC_CONST_8BIT                        /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_8BIT                         /* mapped to default const 8bit section */
#endif
#ifdef CAN_STOP_SEC_CONST_8BIT
# undef CAN_STOP_SEC_CONST_8BIT                         /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST
#endif

#ifdef CAN_START_SEC_CONST_16BIT                      /* Const 16bit */
# undef CAN_START_SEC_CONST_16BIT                       /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_16BIT                        /* mapped to default const 16bit section */
#endif
#ifdef CAN_STOP_SEC_CONST_16BIT
# undef CAN_STOP_SEC_CONST_16BIT                        /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST
#endif

#ifdef CAN_START_SEC_CONST_32BIT                      /* Const 32bit */
# undef CAN_START_SEC_CONST_32BIT                       /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_32BIT                        /* mapped to default const 32bit section */
#endif
#ifdef CAN_STOP_SEC_CONST_32BIT
# undef CAN_STOP_SEC_CONST_32BIT                        /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST
#endif

#ifdef CAN_START_SEC_CONST_UNSPECIFIED                /* Const unspecified */
# undef CAN_START_SEC_CONST_UNSPECIFIED                 /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_UNSPECIFIED                  /* mapped to default const unspec section */
#endif
#ifdef CAN_STOP_SEC_CONST_UNSPECIFIED
# undef CAN_STOP_SEC_CONST_UNSPECIFIED                  /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST
#endif

/* FAST CONST sections */
/* unused */

/* Postbuild CFG CONST sections */

/* Root table for postbuild data (not relevant for CFG5 AutoSar4.0.3) */
#ifdef CAN_START_SEC_PBCFG_ROOT                       /* Generated Postbuild Root Table */
# undef CAN_START_SEC_PBCFG_ROOT                        /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_PBCFG                        /* mapped to default const postbuild section */
#endif
#ifdef CAN_STOP_SEC_PBCFG_ROOT
# undef CAN_STOP_SEC_PBCFG_ROOT                         /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST
#endif

#ifdef CAN_START_SEC_PBCFG                            /* Generated Postbuild */
# undef CAN_START_SEC_PBCFG                             /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_PBCFG                        /* mapped to default const postbuild section */
#endif
#ifdef CAN_STOP_SEC_PBCFG
# undef CAN_STOP_SEC_PBCFG                              /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST
#endif


/*******  VAR sections  **********************************************************************************************/

/* VAR INIT sections */

#ifdef CAN_START_SEC_VAR_INIT_UNSPECIFIED             /* init RAM*/
# undef CAN_START_SEC_VAR_INIT_UNSPECIFIED              /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_INIT_UNSPECIFIED_9               /* mapped to default init var section */
#endif
#ifdef CAN_STOP_SEC_VAR_INIT_UNSPECIFIED
# undef CAN_STOP_SEC_VAR_INIT_UNSPECIFIED               /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif


/* VAR NOINIT sections */

#ifdef CAN_START_SEC_VAR_NOINIT_UNSPECIFIED           /* uninit RAM*/
# undef CAN_START_SEC_VAR_NOINIT_UNSPECIFIED            /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_NOINIT_UNSPECIFIED_9             /* mapped to default uninit var section */
#endif
#ifdef CAN_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# undef CAN_STOP_SEC_VAR_NOINIT_UNSPECIFIED             /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif


/* VAR PBCFG sections */

#ifdef CAN_START_SEC_VAR_PBCFG           /* Generated Postbuild RAM*/
# undef CAN_START_SEC_VAR_PBCFG            /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_PBCFG             /* mapped to default uninit var section */
#endif
#ifdef CAN_STOP_SEC_VAR_PBCFG
# undef CAN_STOP_SEC_VAR_PBCFG             /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

/* VAR ZERO INIT sections */
/* unused */


/* VAR FAST INIT sections */
/* unused */


/* VAR FAST NOINIT sections */
/* unused */

/* VAR FAST ZERO INIT sections */
/* unused */



/**********************************************************************************************************************
 *  Can END
 *********************************************************************************************************************/

#if defined (CANTRCV_30___YOUR_TRCV___START_SEC_CONST_32BIT) /* PRQA S 0883 */ /* Appears only while testing */
#  undef CANTRCV_30___YOUR_TRCV___START_SEC_CONST_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#  define START_SEC_CONST_32BIT             /* mapped to default 32-bit const section */
#endif

#if defined (CANTRCV_30___YOUR_TRCV___START_SEC_CONST_UNSPECIFIED)
#  undef CANTRCV_30___YOUR_TRCV___START_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#  define START_SEC_CONST_UNSPECIFIED      /* unspecified section */
#endif

#if defined (CANTRCV_30___YOUR_TRCV___START_SEC_PBCFG_ROOT) 
#  undef CANTRCV_30___YOUR_TRCV___START_SEC_PBCFG_ROOT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#  define START_SEC_CONST_PBCFG     /* pb section */

#endif

#if defined (CANTRCV_30___YOUR_TRCV___START_SEC_PBCFG)
#  undef CANTRCV_30___YOUR_TRCV___START_SEC_PBCFG /* PRQA S 0841 */ /* MD_MSR_19.6 */
#  define START_SEC_CONST_PBCFG      /* pb section */

#endif

#if defined (CANTRCV_30___YOUR_TRCV___START_SEC_VAR_NOINIT_8BIT)
#  undef CANTRCV_30___YOUR_TRCV___START_SEC_VAR_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#  define START_SEC_VAR_NOINIT_8BIT_9        /* mapped to default 8-bit uninit var section */
#endif


#if defined (CANTRCV_30___YOUR_TRCV___START_SEC_VAR_NOINIT_UNSPECIFIED)
#  undef CANTRCV_30___YOUR_TRCV___START_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#  define START_SEC_VAR_NOINIT_UNSPECIFIED_9                /* mapped to default var section */
#endif


#if defined (CANTRCV_30___YOUR_TRCV___START_SEC_CODE)
#  undef CANTRCV_30___YOUR_TRCV___START_SEC_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#  define START_SEC_CODE                   /* mapped to default code section */
#endif

#if defined (CANTRCV_30___YOUR_TRCV___STOP_SEC_CONST_32BIT)
#  undef CANTRCV_30___YOUR_TRCV___STOP_SEC_CONST_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#  define STOP_SEC_CONST                  /* mapped to default const stop section */
#endif


#if defined (CANTRCV_30___YOUR_TRCV___STOP_SEC_CONST_UNSPECIFIED)
#  undef CANTRCV_30___YOUR_TRCV___STOP_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#  define STOP_SEC_CONST                  /* mapped to default const stop section */
#endif

#if defined (CANTRCV_30___YOUR_TRCV___STOP_SEC_VAR_NOINIT_8BIT)
#  undef CANTRCV_30___YOUR_TRCV___STOP_SEC_VAR_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#  define STOP_SEC_VAR                    /* mapped to default uninit var stop section */
#endif

#if defined (CANTRCV_30___YOUR_TRCV___STOP_SEC_VAR_NOINIT_UNSPECIFIED)
#  undef CANTRCV_30___YOUR_TRCV___STOP_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#  define STOP_SEC_VAR                   /* mapped to default code section */
#endif

#if defined (CANTRCV_30___YOUR_TRCV___STOP_SEC_CODE)
#  undef CANTRCV_30___YOUR_TRCV___STOP_SEC_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
#  define STOP_SEC_CODE                    /* mapped to default code stop section */
#endif

#if defined (CANTRCV_30___YOUR_TRCV___STOP_SEC_PBCFG_ROOT)
#  undef CANTRCV_30___YOUR_TRCV___STOP_SEC_PBCFG_ROOT /* PRQA S 0841 */ /* MD_MSR_19.6 */
#  define STOP_SEC_CONST                  /* mapped to default const stop section */
#endif


#if defined (CANTRCV_30___YOUR_TRCV___STOP_SEC_PBCFG)
#  undef CANTRCV_30___YOUR_TRCV___STOP_SEC_PBCFG /* PRQA S 0841 */ /* MD_MSR_19.6 */
#  define STOP_SEC_CONST                  /* mapped to default const stop section */
#endif

/**********************************************************************************************************************
 *  PDUR START 
 *********************************************************************************************************************/

/*******  CODE sections **********************************************************************************************/

#ifdef PDUR_START_SEC_CODE
# undef PDUR_START_SEC_CODE
# define START_SEC_CODE
#endif
#ifdef PDUR_STOP_SEC_CODE
# undef PDUR_STOP_SEC_CODE
# define STOP_SEC_CODE
#endif


/*******  CONST sections  ********************************************************************************************/

/* CONST sections */

#ifdef PDUR_START_SEC_CONST_8BIT
# undef PDUR_START_SEC_CONST_8BIT
# define START_SEC_CONST_8BIT
#endif
#ifdef PDUR_STOP_SEC_CONST_8BIT
# undef PDUR_STOP_SEC_CONST_8BIT
# define STOP_SEC_CONST
#endif

#ifdef PDUR_START_SEC_CONST_16BIT
# undef PDUR_START_SEC_CONST_16BIT
# define START_SEC_CONST_16BIT
#endif
#ifdef PDUR_STOP_SEC_CONST_16BIT
# undef PDUR_STOP_SEC_CONST_16BIT
# define STOP_SEC_CONST
#endif

#ifdef PDUR_START_SEC_CONST_32BIT
# undef PDUR_START_SEC_CONST_32BIT
# define START_SEC_CONST_32BIT
#endif
#ifdef PDUR_STOP_SEC_CONST_32BIT
# undef PDUR_STOP_SEC_CONST_32BIT
# define STOP_SEC_CONST
#endif

#ifdef PDUR_START_SEC_CONST_UNSPECIFIED
# undef PDUR_START_SEC_CONST_UNSPECIFIED
# define START_SEC_CONST_UNSPECIFIED
#endif
#ifdef PDUR_STOP_SEC_CONST_UNSPECIFIED
# undef PDUR_STOP_SEC_CONST_UNSPECIFIED
# define STOP_SEC_CONST
#endif


/* FAST CONST sections */



/* Postbuild CFG CONST sections */

/* Root table for postbuild data */
#ifdef PDUR_START_SEC_PBCFG
# undef PDUR_START_SEC_PBCFG
# define START_SEC_CONST_PBCFG
#endif
#ifdef PDUR_STOP_SEC_PBCFG
# undef PDUR_STOP_SEC_PBCFG
# define STOP_SEC_CONST
#endif

#ifdef PDUR_START_SEC_PBCFG_ROOT
# undef PDUR_START_SEC_PBCFG_ROOT
# define START_SEC_CONST_PBCFG
#endif
#ifdef PDUR_STOP_SEC_PBCFG_ROOT
# undef PDUR_STOP_SEC_PBCFG_ROOT
# define STOP_SEC_CONST
#endif


/*******  VAR sections  **********************************************************************************************/

/* VAR INIT sections */

#ifdef PDUR_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
# undef PDUR_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
# define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_9
#endif
#ifdef PDUR_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
# undef PDUR_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
# define STOP_SEC_VAR
#endif


/* VAR NOINIT sections */

#ifdef PDUR_START_SEC_VAR_NOINIT_BOOLEAN
# undef PDUR_START_SEC_VAR_NOINIT_BOOLEAN
# define START_SEC_VAR_NOINIT_8BIT_9
#endif
#ifdef PDUR_STOP_SEC_VAR_NOINIT_BOOLEAN
# undef PDUR_STOP_SEC_VAR_NOINIT_BOOLEAN
# define STOP_SEC_VAR
#endif

#ifdef PDUR_START_SEC_VAR_NOINIT_8BIT
# undef PDUR_START_SEC_VAR_NOINIT_8BIT
# define START_SEC_VAR_NOINIT_8BIT_9
#endif
#ifdef PDUR_STOP_SEC_VAR_NOINIT_8BIT
# undef PDUR_STOP_SEC_VAR_NOINIT_8BIT
# define STOP_SEC_VAR
#endif

#ifdef PDUR_START_SEC_VAR_NOINIT_UNSPECIFIED
# undef PDUR_START_SEC_VAR_NOINIT_UNSPECIFIED
# define START_SEC_VAR_NOINIT_UNSPECIFIED_9
#endif
#ifdef PDUR_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# undef PDUR_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# define STOP_SEC_VAR
#endif


/* VAR ZERO INIT sections */



/* VAR FAST INIT sections */



/* VAR FAST NOINIT sections */


/* VAR FAST ZERO INIT sections */



/**********************************************************************************************************************
 *  PDUR END
 *********************************************************************************************************************/

/*-------------------------------------------------------------------------------------------------------------------*/
/* CANIF                                                                                                             */
/*-------------------------------------------------------------------------------------------------------------------*/

/* Code */

#ifdef CANIF_START_SEC_CODE
# undef CANIF_START_SEC_CODE                       /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CODE                            /* mapped to default code section */
#endif

#ifdef CANIF_STOP_SEC_CODE
# undef CANIF_STOP_SEC_CODE                        /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CODE                             /* default code stop section */
#endif


#ifdef CANIF_START_SEC_APPL_CODE
# undef CANIF_START_SEC_APPL_CODE                  /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CODE                            /* mapped to default code section */
#endif

#ifdef CANIF_STOP_SEC_APPL_CODE
# undef CANIF_STOP_SEC_APPL_CODE                   /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CODE                             /* default code stop section */
#endif




/* Const 8bit */

#ifdef CANIF_START_SEC_CONST_8BIT
# undef CANIF_START_SEC_CONST_8BIT                 /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_8BIT                      /* mapped to const 8 bit section */
#endif

#ifdef CANIF_STOP_SEC_CONST_8BIT
# undef CANIF_STOP_SEC_CONST_8BIT                  /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST                            /* default const stop section */
#endif

/* Const 32bit */

#ifdef CANIF_START_SEC_CONST_32BIT
# undef CANIF_START_SEC_CONST_32BIT                 /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_32BIT                      /* mapped to const 32 bit section */
#endif

#ifdef CANIF_STOP_SEC_CONST_32BIT
# undef CANIF_STOP_SEC_CONST_32BIT                 /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST                            /* default const stop section */
#endif


/* Const unspecified */

#ifdef CANIF_START_SEC_CONST_UNSPECIFIED
# undef CANIF_START_SEC_CONST_UNSPECIFIED          /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_UNSPECIFIED               /* mapped to const unspecified section */
#endif

#ifdef CANIF_STOP_SEC_CONST_UNSPECIFIED
# undef CANIF_STOP_SEC_CONST_UNSPECIFIED           /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST                            /* default const stop section */
#endif


/* Post build config unspecified */

#ifdef CANIF_START_SEC_PBCFG
# undef CANIF_START_SEC_PBCFG                      /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_PBCFG                     /* mapped to const unspecified section */
#endif

#ifdef CANIF_STOP_SEC_PBCFG
# undef CANIF_STOP_SEC_PBCFG                       /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST                            /* default const stop section */
#endif

#ifdef CANIF_START_SEC_PBCFG_ROOT
# undef CANIF_START_SEC_PBCFG_ROOT                 /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_PBCFG                     /* mapped to const unspecified section */
#endif

#ifdef CANIF_STOP_SEC_PBCFG_ROOT
# undef CANIF_STOP_SEC_PBCFG_ROOT                  /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST                            /* default const stop section */
#endif


/* Var noinit unspecified */

#ifdef CANIF_START_SEC_VAR_NOINIT_UNSPECIFIED
# undef CANIF_START_SEC_VAR_NOINIT_UNSPECIFIED     /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_NOINIT_UNSPECIFIED_9          /* mapped to uninitialized RAM unspecified section */
#endif

#ifdef CANIF_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# undef CANIF_STOP_SEC_VAR_NOINIT_UNSPECIFIED      /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR                              /* default RAM stop section */
#endif

/* Var zero init unspecified */
#ifdef CANIF_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
# undef CANIF_START_SEC_VAR_ZERO_INIT_UNSPECIFIED  /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_ZERO_INIT_UNSPECIFIED_9       /* mapped to zero initialized RAM unspecified section */
#endif

#ifdef CANIF_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
# undef CANIF_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED   /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR                              /* default RAM stop section */
#endif


/* Var init unspecified */
#ifdef CANIF_START_SEC_VAR_INIT_UNSPECIFIED
# undef CANIF_START_SEC_VAR_INIT_UNSPECIFIED       /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_INIT_UNSPECIFIED_9            /* mapped to initialized RAM unspecified section */
#endif

#ifdef CANIF_STOP_SEC_VAR_INIT_UNSPECIFIED
# undef CANIF_STOP_SEC_VAR_INIT_UNSPECIFIED        /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR                              /* default RAM stop section */
#endif


/*-------------------------------------------------------------------------------------------------------------------*/
/* CANIF                                                                                                             */
/*-------------------------------------------------------------------------------------------------------------------*/


/**********************************************************************************************************************
 *  Com START 
 *********************************************************************************************************************/

/*******  CODE sections **********************************************************************************************/

#ifdef COM_START_SEC_CODE
# undef COM_START_SEC_CODE
# define START_SEC_CODE
#endif
#ifdef COM_STOP_SEC_CODE
# undef COM_STOP_SEC_CODE
# define STOP_SEC_CODE
#endif
/* COM application callback code section (Rte_Cbk.h)*/
#ifdef COM_START_SEC_APPL_CODE
# undef COM_START_SEC_APPL_CODE
# define START_SEC_CODE
#endif
#ifdef COM_STOP_SEC_APPL_CODE
# undef COM_STOP_SEC_APPL_CODE
# define STOP_SEC_CODE
#endif


/*******  CONST sections  ********************************************************************************************/

/* CONST sections */

#ifdef COM_START_SEC_CONST_32BIT
# undef COM_START_SEC_CONST_32BIT
# define START_SEC_CONST_32BIT
#endif
#ifdef COM_STOP_SEC_CONST_32BIT
# undef COM_STOP_SEC_CONST_32BIT
# define STOP_SEC_CONST
#endif

#ifdef COM_START_SEC_CONST_UNSPECIFIED
# undef COM_START_SEC_CONST_UNSPECIFIED
# define START_SEC_CONST_UNSPECIFIED
#endif
#ifdef COM_STOP_SEC_CONST_UNSPECIFIED
# undef COM_STOP_SEC_CONST_UNSPECIFIED
# define STOP_SEC_CONST
#endif


/* FAST CONST sections */



/* Postbuild CFG CONST sections */

/* Root table for postbuild data */
#ifdef COM_START_SEC_PBCFG_ROOT
# undef COM_START_SEC_PBCFG_ROOT
# define START_SEC_CONST_PBCFG
#endif
#ifdef COM_STOP_SEC_PBCFG_ROOT
# undef COM_STOP_SEC_PBCFG_ROOT
# define STOP_SEC_CONST
#endif

#ifdef COM_START_SEC_PBCFG
# undef COM_START_SEC_PBCFG
# define START_SEC_CONST_PBCFG
#endif
#ifdef COM_STOP_SEC_PBCFG
# undef COM_STOP_SEC_PBCFG
# define STOP_SEC_CONST
#endif


/*******  VAR sections  **********************************************************************************************/

/* VAR INIT sections */

#ifdef COM_START_SEC_VAR_INIT_UNSPECIFIED
# undef COM_START_SEC_VAR_INIT_UNSPECIFIED
# define START_SEC_VAR_INIT_UNSPECIFIED_9
#endif
#ifdef COM_STOP_SEC_VAR_INIT_UNSPECIFIED
# undef COM_STOP_SEC_VAR_INIT_UNSPECIFIED
# define STOP_SEC_VAR
#endif


/* VAR NOINIT sections */

#ifdef COM_START_SEC_VAR_NOINIT_BOOLEAN
# undef COM_START_SEC_VAR_NOINIT_BOOLEAN
# define START_SEC_VAR_NOINIT_8BIT_9
#endif
#ifdef COM_STOP_SEC_VAR_NOINIT_BOOLEAN
# undef COM_STOP_SEC_VAR_NOINIT_BOOLEAN
# define STOP_SEC_VAR
#endif

#ifdef COM_START_SEC_VAR_NOINIT_8BIT
# undef COM_START_SEC_VAR_NOINIT_8BIT
# define START_SEC_VAR_NOINIT_8BIT_9
#endif
#ifdef COM_STOP_SEC_VAR_NOINIT_8BIT
# undef COM_STOP_SEC_VAR_NOINIT_8BIT
# define STOP_SEC_VAR
#endif

#ifdef COM_START_SEC_VAR_NOINIT_16BIT
# undef COM_START_SEC_VAR_NOINIT_16BIT
# define START_SEC_VAR_NOINIT_16BIT_9
#endif
#ifdef COM_STOP_SEC_VAR_NOINIT_16BIT
# undef COM_STOP_SEC_VAR_NOINIT_16BIT
# define STOP_SEC_VAR
#endif

#ifdef COM_START_SEC_VAR_NOINIT_UNSPECIFIED
# undef COM_START_SEC_VAR_NOINIT_UNSPECIFIED
# define START_SEC_VAR_NOINIT_UNSPECIFIED_9
#endif
#ifdef COM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# undef COM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# define STOP_SEC_VAR
#endif


/* VAR ZERO INIT sections */



/* VAR FAST INIT sections */



/* VAR FAST NOINIT sections */


/* VAR FAST ZERO INIT sections */



/**********************************************************************************************************************
 *  Com END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  CANNM START 
 *********************************************************************************************************************/

/*******  CODE sections **********************************************************************************************/

#ifdef CANNM_START_SEC_CODE
    #undef CANNM_START_SEC_CODE
    #define START_SEC_CODE                              /*mapped to default code section*/
#endif
#ifdef CANNM_STOP_SEC_CODE
    #undef CANNM_STOP_SEC_CODE
    #define STOP_SEC_CODE                               /*default code stop section*/
#endif

/*******  CONST sections  ********************************************************************************************/

/* CONST sections */

#ifdef CANNM_START_SEC_CONST_8BIT
    #undef CANNM_START_SEC_CONST_8BIT
    #define START_SEC_CONST_8BIT                        /*mapped to default const section */
#endif
#ifdef CANNM_STOP_SEC_CONST_8BIT
    #undef CANNM_STOP_SEC_CONST_8BIT
    #define STOP_SEC_CONST                              /*default const stop section*/
#endif

#ifdef CANNM_START_SEC_CONST_32BIT
    #undef CANNM_START_SEC_CONST_32BIT
    #define START_SEC_CONST_32BIT                       /*mapped to default const section */
#endif
#ifdef CANNM_STOP_SEC_CONST_32BIT
    #undef CANNM_STOP_SEC_CONST_32BIT
    #define STOP_SEC_CONST                              /*default const stop section*/
#endif

#ifdef CANNM_START_SEC_CONST_UNSPECIFIED
    #undef CANNM_START_SEC_CONST_UNSPECIFIED
    #define START_SEC_CONST_UNSPECIFIED                 /*mapped to default const section */
#endif
#ifdef CANNM_STOP_SEC_CONST_UNSPECIFIED
    #undef CANNM_STOP_SEC_CONST_UNSPECIFIED
    #define STOP_SEC_CONST                              /*default const stop section*/
#endif

/* Postbuild CFG CONST sections */

#ifdef CANNM_START_SEC_PBCFG
    #undef CANNM_START_SEC_PBCFG
    #define START_SEC_CONST_PBCFG                       /*mapped to default postbuild section */
#endif
#ifdef CANNM_STOP_SEC_PBCFG
    #undef CANNM_STOP_SEC_PBCFG
    #define STOP_SEC_CONST                              /*default const stop section*/
#endif

#ifdef CANNM_START_SEC_PBCFG_ROOT
    #undef CANNM_START_SEC_PBCFG_ROOT
    #define START_SEC_CONST_PBCFG                       /*mapped to default postbuild section */
#endif
#ifdef CANNM_STOP_SEC_PBCFG_ROOT
    #undef CANNM_STOP_SEC_PBCFG_ROOT
    #define STOP_SEC_CONST                              /*default const stop section*/
#endif

/*******  VAR sections  **********************************************************************************************/

/* VAR NOINIT sections */

#ifdef CANNM_START_SEC_VAR_NOINIT_8BIT
    #undef CANNM_START_SEC_VAR_NOINIT_8BIT
    #define START_SEC_VAR_NOINIT_8BIT_9                   /* mapped to default var section */
#endif
#ifdef CANNM_STOP_SEC_VAR_NOINIT_8BIT
    #undef CANNM_STOP_SEC_VAR_NOINIT_8BIT
    #define STOP_SEC_VAR                                /*default var stop section*/
#endif

#ifdef CANNM_START_SEC_VAR_NOINIT_UNSPECIFIED
    #undef CANNM_START_SEC_VAR_NOINIT_UNSPECIFIED
    #define START_SEC_VAR_NOINIT_UNSPECIFIED_9            /* mapped to default var section */
#endif
#ifdef CANNM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
    #undef CANNM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
    #define STOP_SEC_VAR                                /*default var stop section*/
#endif

/* VAR FAST NOINIT sections */

#ifdef CANNM_START_SEC_VAR_FAST_NOINIT_8BIT
    #undef CANNM_START_SEC_VAR_FAST_NOINIT_8BIT
    #define START_SEC_VAR_FAST_NOINIT_8BIT_9              /* mapped to default var section */
#endif
#ifdef CANNM_STOP_SEC_VAR_FAST_NOINIT_8BIT
    #undef CANNM_STOP_SEC_VAR_FAST_NOINIT_8BIT
    #define STOP_SEC_VAR                                /*default var stop section*/
#endif

#ifdef CANNM_START_SEC_VAR_FAST_NOINIT_16BIT
    #undef CANNM_START_SEC_VAR_FAST_NOINIT_16BIT
    #define START_SEC_VAR_FAST_NOINIT_16BIT_9             /* mapped to default var section */
#endif
#ifdef CANNM_STOP_SEC_VAR_FAST_NOINIT_16BIT
    #undef CANNM_STOP_SEC_VAR_FAST_NOINIT_16BIT
    #define STOP_SEC_VAR                                /*default var stop section*/
#endif

#ifdef CANNM_START_SEC_VAR_FAST_NOINIT_UNSPECIFIED
    #undef CANNM_START_SEC_VAR_FAST_NOINIT_UNSPECIFIED
    #define START_SEC_VAR_FAST_NOINIT_UNSPECIFIED_9       /* mapped to default var section */
#endif
#ifdef CANNM_STOP_SEC_VAR_FAST_NOINIT_UNSPECIFIED
    #undef CANNM_STOP_SEC_VAR_FAST_NOINIT_UNSPECIFIED
    #define STOP_SEC_VAR                                /*default var stop section*/
#endif

/* VAR FAST ZERO INIT sections */

#ifdef CANNM_START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED
    #undef CANNM_START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED
    #define START_SEC_VAR_FAST_NOINIT_UNSPECIFIED_9      /* mapped to default var section */
#endif
#ifdef CANNM_STOP_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED
    #undef CANNM_STOP_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED
    #define STOP_SEC_VAR                                /*default var stop section*/
#endif

/**********************************************************************************************************************
 *  CANNM END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  NM START 
 *********************************************************************************************************************/

/*******  CODE sections **********************************************************************************************/

#ifdef NM_START_SEC_CODE
# undef NM_START_SEC_CODE                               /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CODE                                 /* mapped to default code section */
#endif
#ifdef NM_STOP_SEC_CODE
# undef NM_STOP_SEC_CODE                                /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CODE                                  /* default code stop section */
#endif

/*******  CONST sections  ********************************************************************************************/

#ifdef NM_START_SEC_CONST_8BIT
# undef NM_START_SEC_CONST_8BIT                         /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_8BIT                           /* mapped to default const section */
#endif
#ifdef NM_STOP_SEC_CONST_8BIT
# undef NM_STOP_SEC_CONST_8BIT                          /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST                                 /* default const stop section */
#endif

#ifdef NM_START_SEC_CONST_32BIT
# undef NM_START_SEC_CONST_32BIT                        /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_32BIT                          /* mapped to default const section */
#endif
#ifdef NM_STOP_SEC_CONST_32BIT
# undef NM_STOP_SEC_CONST_32BIT                         /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST                                 /* default const stop section */
#endif

#ifdef NM_START_SEC_CONST_UNSPECIFIED
# undef NM_START_SEC_CONST_UNSPECIFIED                  /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_UNSPECIFIED                    /* mapped to default const section */
#endif
#ifdef NM_STOP_SEC_CONST_UNSPECIFIED
# undef NM_STOP_SEC_CONST_UNSPECIFIED                   /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST                                 /* default const stop section */
#endif

/*******  VAR sections  **********************************************************************************************/

/* VAR NOINIT sections */

#ifdef NM_START_SEC_VAR_NOINIT_8BIT
# undef NM_START_SEC_VAR_NOINIT_8BIT                    /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_NOINIT_8BIT_9                      /* mapped to default var section */
#endif
#ifdef NM_STOP_SEC_VAR_NOINIT_8BIT
# undef NM_STOP_SEC_VAR_NOINIT_8BIT                     /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR                                   /* default var stop section */
#endif

#ifdef NM_START_SEC_VAR_NOINIT_UNSPECIFIED
# undef NM_START_SEC_VAR_NOINIT_UNSPECIFIED             /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_NOINIT_UNSPECIFIED_9               /* mapped to default var section */
#endif
#ifdef NM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# undef NM_STOP_SEC_VAR_NOINIT_UNSPECIFIED              /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR                                   /* default var stop section */
#endif

/* VAR FAST NOINIT sections */

#ifdef NM_START_SEC_VAR_FAST_NOINIT_8BIT
# undef NM_START_SEC_VAR_FAST_NOINIT_8BIT               /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_FAST_NOINIT_8BIT_9                 /* mapped to default var section */
#endif
#ifdef NM_STOP_SEC_VAR_FAST_NOINIT_8BIT
# undef NM_STOP_SEC_VAR_FAST_NOINIT_8BIT                /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR                                   /* default var stop section */
#endif

#ifdef NM_START_SEC_VAR_FAST_NOINIT_16BIT
# undef NM_START_SEC_VAR_FAST_NOINIT_16BIT              /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_FAST_NOINIT_16BIT_9                /* mapped to default var section */
#endif
#ifdef NM_STOP_SEC_VAR_FAST_NOINIT_16BIT
# undef NM_STOP_SEC_VAR_FAST_NOINIT_16BIT               /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR                                   /* default var stop section */
#endif

#ifdef NM_START_SEC_VAR_FAST_NOINIT_UNSPECIFIED
# undef NM_START_SEC_VAR_FAST_NOINIT_UNSPECIFIED        /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_FAST_NOINIT_UNSPECIFIED_9          /* mapped to default var section */
#endif
#ifdef NM_STOP_SEC_VAR_FAST_NOINIT_UNSPECIFIED
# undef NM_STOP_SEC_VAR_FAST_NOINIT_UNSPECIFIED         /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR                                   /* default var stop section */
#endif

/* VAR FAST ZERO INIT sections */

#ifdef NM_START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED
# undef NM_START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED     /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_FAST_NOINIT_UNSPECIFIED_9       /* mapped to default var section */
#endif
#ifdef NM_STOP_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED
# undef NM_STOP_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED      /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR                                   /* default var stop section */
#endif

/**********************************************************************************************************************
 *  NM END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  BSWM START 
 *********************************************************************************************************************/

/*******  CODE sections **********************************************************************************************/
#ifdef BSWM_START_SEC_CODE
    #undef BSWM_START_SEC_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define START_SEC_CODE    /*mapped to default code section*/
#endif

#ifdef BSWM_STOP_SEC_CODE
    #undef BSWM_STOP_SEC_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define STOP_SEC_CODE     /*default code stop section*/
#endif

#ifdef BSWM_START_SEC_CONST_UNSPECIFIED
    #undef BSWM_START_SEC_CONST_UNSPECIFIED  /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef BSWM_STOP_SEC_CONST_UNSPECIFIED
    #undef BSWM_STOP_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define STOP_SEC_CONST
#endif

#ifdef BSWM_START_SEC_CONST_8BIT
    #undef BSWM_START_SEC_CONST_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define START_SEC_CONST_8BIT                    /*default code stop section*/
#endif

#ifdef BSWM_STOP_SEC_CONST_8BIT
    #undef BSWM_STOP_SEC_CONST_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define STOP_SEC_CONST                   /*default code stop section*/
#endif

#ifdef BSWM_START_SEC_CONST_32BIT
    #undef BSWM_START_SEC_CONST_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define START_SEC_CONST_32BIT     /*default code stop section*/
#endif

#ifdef BSWM_STOP_SEC_CONST_32BIT
    #undef BSWM_STOP_SEC_CONST_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define STOP_SEC_CONST           /*default code stop section*/
#endif

#ifdef BSWM_START_SEC_VAR_NOINIT_8BIT
    #undef BSWM_START_SEC_VAR_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define START_SEC_VAR_NOINIT_8BIT_9     /*mapped to default code section*/
#endif

#ifdef BSWM_STOP_SEC_VAR_NOINIT_8BIT
    #undef BSWM_STOP_SEC_VAR_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define STOP_SEC_VAR                   /*mapped to default code section*/
#endif

#ifdef BSWM_START_SEC_VAR_NOINIT_16BIT
    #undef BSWM_START_SEC_VAR_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define START_SEC_VAR_NOINIT_16BIT_9      /*mapped to default code section*/
#endif

#ifdef BSWM_STOP_SEC_VAR_NOINIT_16BIT
    #undef BSWM_STOP_SEC_VAR_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define STOP_SEC_VAR                   /*mapped to default code section*/
#endif

#ifdef BSWM_START_SEC_VAR_NOINIT_32BIT
  #undef  BSWM_START_SEC_VAR_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define START_SEC_VAR_NOINIT_32BIT_9
#endif

#ifdef BSWM_STOP_SEC_VAR_NOINIT_32BIT
# undef BSWM_STOP_SEC_VAR_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR                  /*default var section*/
#endif

#ifdef BSWM_START_SEC_VAR_NOINIT_UNSPECIFIED
    #undef BSWM_START_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define START_SEC_VAR_NOINIT_UNSPECIFIED_9     /*mapped to default code section*/
#endif

#ifdef BSWM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
    #undef BSWM_STOP_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define STOP_SEC_VAR                        /*mapped to default code section*/
#endif

#ifdef BSWM_START_SEC_VAR_INIT_UNSPECIFIED
    #undef BSWM_START_SEC_VAR_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define START_SEC_VAR_INIT_UNSPECIFIED_9     /*mapped to default code section*/
#endif

#ifdef BSWM_STOP_SEC_VAR_INIT_UNSPECIFIED
    #undef BSWM_STOP_SEC_VAR_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define STOP_SEC_VAR                      /*mapped to default code section*/
#endif


/**********************************************************************************************************************
 *  BSWM END
 *********************************************************************************************************************/

#ifdef DET_START_SEC_CODE
# undef DET_START_SEC_CODE
# define START_SEC_CODE
#endif
#ifdef DET_STOP_SEC_CODE
# undef DET_STOP_SEC_CODE
# define STOP_SEC_CODE
#endif

#ifdef DET_START_SEC_VAR_UNSPECIFIED
# undef DET_START_SEC_VAR_UNSPECIFIED
# define START_SEC_VAR_NOINIT_UNSPECIFIED_9
#endif
#ifdef DET_STOP_SEC_VAR_UNSPECIFIED
# undef DET_STOP_SEC_VAR_UNSPECIFIED
# define STOP_SEC_VAR
#endif



/**********************************************************************************************************************
 *  SYSSERVICE_ASRECUM START 
 *********************************************************************************************************************/

/*******  CODE sections **********************************************************************************************/
#ifdef ECUM_START_SEC_CODE
# undef ECUM_START_SEC_CODE
# define START_SEC_CODE                            /* mapped to default code section */
#endif
#ifdef ECUM_STOP_SEC_CODE
# undef ECUM_STOP_SEC_CODE
# define STOP_SEC_CODE                             /* default code stop section */
#endif

#ifdef ECUM_START_SEC_CODE_SET_BOOT_TARGET
# undef ECUM_START_SEC_CODE_SET_BOOT_TARGET
# define START_SEC_CODE                            /* mapped to default fast code section */
#endif
#ifdef ECUM_STOP_SEC_CODE_SET_BOOT_TARGET
# undef ECUM_STOP_SEC_CODE_SET_BOOT_TARGET
# define STOP_SEC_CODE                             /* default code stop section */
#endif

#ifdef ECUM_START_SEC_CODE_GET_BOOT_TARGET
# undef ECUM_START_SEC_CODE_GET_BOOT_TARGET
# define START_SEC_CODE                            /* mapped to default ISR code section */
#endif
#ifdef ECUM_STOP_SEC_CODE_GET_BOOT_TARGET
# undef ECUM_STOP_SEC_CODE_GET_BOOT_TARGET
# define STOP_SEC_CODE                             /* default code stop section */
#endif

/*******  CONST sections  ********************************************************************************************/

/* CONST sections */

#ifdef ECUM_START_SEC_CONST_8BIT
# undef ECUM_START_SEC_CONST_8BIT
# define START_SEC_CONST_8BIT                       /* mapped to default const 8bit section */
#endif
#ifdef ECUM_STOP_SEC_CONST_8BIT
# undef ECUM_STOP_SEC_CONST_8BIT
# define STOP_SEC_CONST                             /* default const stop section */
#endif

#ifdef ECUM_START_SEC_CONST_UNSPECIFIED
# undef ECUM_START_SEC_CONST_UNSPECIFIED
# define START_SEC_CONST_UNSPECIFIED
#endif
#ifdef ECUM_STOP_SEC_CONST_UNSPECIFIED
# undef ECUM_STOP_SEC_CONST_UNSPECIFIED
# define STOP_SEC_CONST
#endif

/* FAST CONST sections */

/* Postbuild CFG CONST sections */

/* Root table for postbuild data */
#ifdef ECUM_START_SEC_CONST_PBCFG_ROOT
# undef ECUM_START_SEC_CONST_PBCFG_ROOT
# define START_SEC_CONST_PBCFG
#endif
#ifdef ECUM_STOP_SEC_CONST_PBCFG_ROOT
# undef ECUM_STOP_SEC_CONST_PBCFG_ROOT
# define STOP_SEC_CONST
#endif

#ifdef ECUM_START_SEC_CONST_PBCFG
# undef ECUM_START_SEC_CONST_PBCFG
# define START_SEC_CONST_PBCFG
#endif
#ifdef ECUM_STOP_SEC_CONST_PBCFG
# undef ECUM_STOP_SEC_CONST_PBCFG
# define STOP_SEC_CONST
#endif

/*******  VAR sections  **********************************************************************************************/

/* VAR INIT sections */

#ifdef ECUM_START_SEC_VAR_INIT_UNSPECIFIED
# undef ECUM_START_SEC_VAR_INIT_UNSPECIFIED
# define START_SEC_VAR_INIT_UNSPECIFIED_9
#endif
#ifdef ECUM_STOP_SEC_VAR_INIT_UNSPECIFIED
# undef ECUM_STOP_SEC_VAR_INIT_UNSPECIFIED
# define STOP_SEC_VAR
#endif

/* VAR NOINIT sections */

#ifdef ECUM_START_SEC_VAR_NOINIT_8BIT
# undef ECUM_START_SEC_VAR_NOINIT_8BIT
# define START_SEC_VAR_NOINIT_8BIT_9
#endif
#ifdef ECUM_STOP_SEC_VAR_NOINIT_8BIT
# undef ECUM_STOP_SEC_VAR_NOINIT_8BIT
# define STOP_SEC_VAR
#endif

#ifdef ECUM_START_SEC_VAR_NOINIT_16BIT
# undef ECUM_START_SEC_VAR_NOINIT_16BIT
# define START_SEC_VAR_NOINIT_16BIT_9
#endif
#ifdef ECUM_STOP_SEC_VAR_NOINIT_16BIT
# undef ECUM_STOP_SEC_VAR_NOINIT_16BIT
# define STOP_SEC_VAR
#endif

#ifdef ECUM_START_SEC_VAR_NOINIT_UNSPECIFIED
# undef ECUM_START_SEC_VAR_NOINIT_UNSPECIFIED
# define START_SEC_VAR_NOINIT_UNSPECIFIED_9
#endif
#ifdef ECUM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# undef ECUM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# define STOP_SEC_VAR
#endif

/* VAR ZERO INIT sections */

/* VAR FAST INIT sections */

/* VAR FAST NOINIT sections */

/* VAR FAST ZERO INIT sections */


/**********************************************************************************************************************
 *  SYSSERVICE_ASRECUM END
 *********************************************************************************************************************/


/* -------------------- FiM Start Sections -------------------- */

#ifdef FIM_START_SEC_CONST_UNSPECIFIED
# undef FIM_START_SEC_CONST_UNSPECIFIED
# define START_SEC_CONST_UNSPECIFIED                    /*mapped to default const section */
#endif

#ifdef FIM_START_SEC_LCFG
# undef FIM_START_SEC_LCFG
# define START_SEC_CONST_UNSPECIFIED                    /*mapped to default const section */
#endif

#ifdef FIM_START_SEC_VAR_NOINIT_8BIT
# undef FIM_START_SEC_VAR_NOINIT_8BIT
# define START_SEC_VAR_NOINIT_8BIT_9                      /*mapped to default var section*/
#endif

#ifdef FIM_START_SEC_VAR_NOINIT_16BIT
# undef FIM_START_SEC_VAR_NOINIT_16BIT
# define START_SEC_VAR_NOINIT_16BIT_9                      /*mapped to default var section*/
#endif

#ifdef FIM_START_SEC_VAR_NOINIT_UNSPECIFIED
# undef FIM_START_SEC_VAR_NOINIT_UNSPECIFIED
# define START_SEC_VAR_NOINIT_UNSPECIFIED_9               /*mapped to default var section*/
#endif

#ifdef FIM_START_SEC_CODE
# undef FIM_START_SEC_CODE
# define START_SEC_CODE                                 /*mapped to default code section*/
#endif

/* -------------------- FiM Stop Sections -------------------- */

#ifdef FIM_STOP_SEC_CONST_UNSPECIFIED
# undef FIM_STOP_SEC_CONST_UNSPECIFIED 
# define STOP_SEC_CONST                                 /*mapped to default const section */
#endif

#ifdef FIM_STOP_SEC_LCFG
# undef FIM_STOP_SEC_LCFG
# define STOP_SEC_CONST                                 /*mapped to default const section */
#endif

#ifdef FIM_STOP_SEC_VAR_NOINIT_8BIT
# undef FIM_STOP_SEC_VAR_NOINIT_8BIT
# define STOP_SEC_VAR                                   /*mapped to default var section*/
#endif

#ifdef FIM_STOP_SEC_VAR_NOINIT_16BIT
# undef FIM_STOP_SEC_VAR_NOINIT_16BIT
# define STOP_SEC_VAR                                   /*mapped to default var section*/
#endif

#ifdef FIM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# undef FIM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# define STOP_SEC_VAR                                   /*mapped to default var section*/
#endif

#ifdef FIM_STOP_SEC_CODE
# undef FIM_STOP_SEC_CODE
# define STOP_SEC_CODE                                 /*mapped to default code section*/
#endif

/**********************************************************************************************************************
 *  CANTP START 
 *********************************************************************************************************************/

/*******  CODE sections **********************************************************************************************/

#if defined (CANTP_START_SEC_CODE)
   #undef    CANTP_START_SEC_CODE
   #define         START_SEC_CODE
#endif
#if defined (CANTP_STOP_SEC_CODE)
   #undef    CANTP_STOP_SEC_CODE
   #define         STOP_SEC_CODE
#endif



/*******  CONST sections  ********************************************************************************************/

/* CONST sections */

#if defined (CANTP_START_SEC_CONST_UNSPECIFIED)
   #undef    CANTP_START_SEC_CONST_UNSPECIFIED
   #define         START_SEC_CONST_UNSPECIFIED
#endif
#if defined (CANTP_STOP_SEC_CONST_UNSPECIFIED)
   #undef    CANTP_STOP_SEC_CONST_UNSPECIFIED
   #define         STOP_SEC_CONST
#endif

#if defined (CANTP_START_SEC_CONST_16BIT)
   #undef    CANTP_START_SEC_CONST_16BIT
   #define         START_SEC_CONST_16BIT
#endif
#if defined (CANTP_STOP_SEC_CONST_16BIT)
   #undef    CANTP_STOP_SEC_CONST_16BIT
   #define         STOP_SEC_CONST
#endif

#if defined (CANTP_START_SEC_CONST_32BIT)
   #undef    CANTP_START_SEC_CONST_32BIT
   #define         START_SEC_CONST_32BIT
#endif
#if defined (CANTP_STOP_SEC_CONST_32BIT)
   #undef    CANTP_STOP_SEC_CONST_32BIT
   #define         STOP_SEC_CONST
#endif


/* Postbuild sections */

#if defined (CANTP_START_SEC_CONST_PBCFG)
   #undef    CANTP_START_SEC_CONST_PBCFG
   #define         START_SEC_CONST_PBCFG
#endif
#if defined (CANTP_STOP_SEC_CONST_PBCFG)
   #undef    CANTP_STOP_SEC_CONST_PBCFG
   #define         STOP_SEC_CONST
#endif

#if defined (CANTP_START_SEC_CONST_PBCFG_ROOT)
   #undef    CANTP_START_SEC_CONST_PBCFG_ROOT
   #define         START_SEC_CONST_PBCFG
#endif
#if defined (CANTP_STOP_SEC_CONST_PBCFG_ROOT)
   #undef    CANTP_STOP_SEC_CONST_PBCFG_ROOT
   #define         STOP_SEC_CONST
#endif  



/*******  VAR sections  **********************************************************************************************/

/* VAR INIT sections */

#if defined (CANTP_START_SEC_VAR_INIT_UNSPECIFIED)
   #undef    CANTP_START_SEC_VAR_INIT_UNSPECIFIED
   #define         START_SEC_VAR_INIT_UNSPECIFIED_9
#endif
#if defined (CANTP_STOP_SEC_VAR_INIT_UNSPECIFIED)
   #undef    CANTP_STOP_SEC_VAR_INIT_UNSPECIFIED
   #define         STOP_SEC_VAR
#endif


/* VAR NOINIT sections */

#if defined (CANTP_START_SEC_VAR_NOINIT_UNSPECIFIED)
   #undef    CANTP_START_SEC_VAR_NOINIT_UNSPECIFIED
   #define         START_SEC_VAR_NOINIT_UNSPECIFIED_9
#endif
#if defined (CANTP_STOP_SEC_VAR_NOINIT_UNSPECIFIED)
   #undef    CANTP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
   #define         STOP_SEC_VAR
#endif

#if defined (CANTP_START_SEC_VAR_NOINIT_8BIT)
   #undef    CANTP_START_SEC_VAR_NOINIT_8BIT
   #define         START_SEC_VAR_NOINIT_8BIT_9
#endif
#if defined (CANTP_STOP_SEC_VAR_NOINIT_8BIT)
   #undef    CANTP_STOP_SEC_VAR_NOINIT_8BIT
   #define         STOP_SEC_VAR
#endif


/**********************************************************************************************************************
 *  CANTP END
 *********************************************************************************************************************/

/*-------------------------------------------------------------------------------------------------------------------*/
/* VStdLib start MemMap.inc                                                                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

/*---------------------------------- Code ---------------------------------------------------------------------------*/

#ifdef VSTDLIB_START_SEC_CODE                             /* CAN code */
# undef VSTDLIB_START_SEC_CODE                            /* PRQA S 0841 */
# define START_SEC_CODE                                   /* mapped to default code section */
#endif
#ifdef VSTDLIB_STOP_SEC_CODE
# undef VSTDLIB_STOP_SEC_CODE                             /* PRQA S 0841 */
# define STOP_SEC_CODE
#endif

/*---------------------------------- Const --------------------------------------------------------------------------*/

#ifdef VSTDLIB_START_SEC_CONST_UNSPECIFIED               /* CAN code */
# undef VSTDLIB_START_SEC_CONST_UNSPECIFIED              /* PRQA S 0841 */
# define START_SEC_CONST_UNSPECIFIED                     /* mapped to default code section */
#endif
#ifdef VSTDLIB_STOP_SEC_CONST_UNSPECIFIED  
# undef VSTDLIB_STOP_SEC_CONST_UNSPECIFIED               /* PRQA S 0841 */
# define STOP_SEC_CONST
#endif

/*---------------------------------- RAM ----------------------------------------------------------------------------*/

#ifdef VSTDLIB_START_SEC_VAR_NOINIT_UNSPECIFIED          /* CAN code */
# undef VSTDLIB_START_SEC_VAR_NOINIT_UNSPECIFIED         /* PRQA S 0841 */
# define START_SEC_VAR_NOINIT_UNSPECIFIED_9                /* mapped to default code section */
#endif
#ifdef VSTDLIB_STOP_SEC_VAR_NOINIT_UNSPECIFIED  
# undef VSTDLIB_STOP_SEC_VAR_NOINIT_UNSPECIFIED          /* PRQA S 0841 */
# define STOP_SEC_VAR 
#endif

/*-------------------------------------------------------------------------------------------------------------------*/
/* VStdLib end MemMap.inc                                                                                            */
/*-------------------------------------------------------------------------------------------------------------------*/



/* Package Merger: Stop Section MemMapModuleList */


/* ------------------- provide compatibility to former specifications --------- */

#ifdef START_SEC_CONST_8
    #define START_SEC_CONST_8BIT
    #undef START_SEC_CONST_8 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_CONST_16
    #define START_SEC_CONST_16BIT
    #undef START_SEC_CONST_16 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_CONST_32
    #define START_SEC_CONST_32BIT
    #undef START_SEC_CONST_32 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_CONST_FAST_8
    #define START_SEC_CONST_FAST_8BIT
    #undef START_SEC_CONST_FAST_8 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_CONST_FAST_16
    #define START_SEC_CONST_FAST_16BIT
    #undef START_SEC_CONST_FAST_16 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_CONST_FAST_32
    #define START_SEC_CONST_FAST_32BIT
    #undef START_SEC_CONST_FAST_32 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_INIT_8
    #define START_SEC_VAR_INIT_8BIT
    #undef START_SEC_VAR_INIT_8 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_INIT_16
    #define START_SEC_VAR_INIT_16BIT
    #undef START_SEC_VAR_INIT_16 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_INIT_32
    #define START_SEC_VAR_INIT_32BIT
    #undef START_SEC_VAR_INIT_32 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_NO_INIT_8
    #define START_SEC_VAR_NOINIT_8BIT
    #undef START_SEC_VAR_NO_INIT_8 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_NO_INIT_16
    #define START_SEC_VAR_NOINIT_16BIT
    #undef START_SEC_VAR_NO_INIT_16 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_NO_INIT_32
    #define START_SEC_VAR_NOINIT_32BIT
    #undef START_SEC_VAR_NO_INIT_32 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_NO_INIT_UNSPECIFIED
    #define START_SEC_VAR_NOINIT_UNSPECIFIED
    #undef START_SEC_VAR_NO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_CLEARED_8
    #define START_SEC_VAR_ZERO_INIT_8BIT
    #undef START_SEC_VAR_CLEARED_8 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_CLEARED_16
    #define START_SEC_VAR_ZERO_INIT_16BIT
    #undef START_SEC_VAR_CLEARED_16 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_CLEARED_32
    #define START_SEC_VAR_ZERO_INIT_32BIT
    #undef START_SEC_VAR_CLEARED_32 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_CLEARED_UNSPECIFIED
    #define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
    #undef START_SEC_VAR_CLEARED_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_FAST_INIT_8
    #define START_SEC_VAR_FAST_INIT_8BIT
    #undef START_SEC_VAR_FAST_INIT_8 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_FAST_INIT_16
    #define START_SEC_VAR_FAST_INIT_16BIT
    #undef START_SEC_VAR_FAST_INIT_16 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_FAST_INIT_32
    #define START_SEC_VAR_FAST_INIT_32BIT
    #undef START_SEC_VAR_FAST_INIT_32 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_FAST_NO_INIT_8
    #define START_SEC_VAR_FAST_NOINIT_8BIT
    #undef START_SEC_VAR_FAST_NO_INIT_8 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_FAST_NO_INIT_16
    #define START_SEC_VAR_FAST_NOINIT_16BIT
    #undef START_SEC_VAR_FAST_NO_INIT_16 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_FAST_NO_INIT_32
    #define START_SEC_VAR_FAST_NOINIT_32BIT
    #undef START_SEC_VAR_FAST_NO_INIT_32 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_FAST_NO_INIT_UNSPECIFIED
    #define START_SEC_VAR_FAST_NOINIT_UNSPECIFIED
    #undef START_SEC_VAR_FAST_NO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_FAST_CLEARED_8
    #define START_SEC_VAR_FAST_ZERO_INIT_8BIT
    #undef START_SEC_VAR_FAST_CLEARED_8 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_FAST_CLEARED_16
    #define START_SEC_VAR_FAST_ZERO_INIT_16BIT
    #undef START_SEC_VAR_FAST_CLEARED_16 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_FAST_CLEARED_32
    #define START_SEC_VAR_FAST_ZERO_INIT_32BIT
    #undef START_SEC_VAR_FAST_CLEARED_32 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_FAST_CLEARED_UNSPECIFIED
    #define START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED
    #undef START_SEC_VAR_FAST_CLEARED_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_NOCACHE_INIT_8
    #define START_SEC_VAR_NOCACHE_INIT_8BIT
    #undef START_SEC_VAR_NOCACHE_INIT_8 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_NOCACHE_INIT_16
    #define START_SEC_VAR_NOCACHE_INIT_16BIT
    #undef START_SEC_VAR_NOCACHE_INIT_16 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_NOCACHE_INIT_32
    #define START_SEC_VAR_NOCACHE_INIT_32BIT
    #undef START_SEC_VAR_NOCACHE_INIT_32 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_NOCACHE_NO_INIT_8
    #define START_SEC_VAR_NOCACHE_NOINIT_8BIT
    #undef START_SEC_VAR_NOCACHE_NO_INIT_8 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_NOCACHE_NO_INIT_16
    #define START_SEC_VAR_NOCACHE_NOINIT_16BIT
    #undef START_SEC_VAR_NOCACHE_NO_INIT_16 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_NOCACHE_NO_INIT_32
    #define START_SEC_VAR_NOCACHE_NOINIT_32BIT
    #undef START_SEC_VAR_NOCACHE_NO_INIT_32 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_NOCACHE_NO_INIT_UNSPECIFIED
    #define START_SEC_VAR_NOCACHE_NOINIT_UNSPECIFIED
    #undef START_SEC_VAR_NOCACHE_NO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_NOCACHE_CLEARED_8
    #define START_SEC_VAR_NOCACHE_ZERO_INIT_8BIT
    #undef START_SEC_VAR_NOCACHE_CLEARED_8 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_NOCACHE_CLEARED_16
    #define START_SEC_VAR_NOCACHE_ZERO_INIT_16BIT
    #undef START_SEC_VAR_NOCACHE_CLEARED_16 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_NOCACHE_CLEARED_32
    #define START_SEC_VAR_NOCACHE_ZERO_INIT_32BIT
    #undef START_SEC_VAR_NOCACHE_CLEARED_32 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_NOCACHE_CLEARED_UNSPECIFIED
    #define START_SEC_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED
    #undef START_SEC_VAR_NOCACHE_CLEARED_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

/*------------------------------GLOBAL-SECTIONS-----------------------------*/
/* Check code sections */
#if ( (defined CODE_SEC_OPEN)                            && \
     ((defined START_SEC_CODE                          ) || \
      (defined START_SEC_CODE_FAST                     ) || \
      (defined START_SEC_CODE_ISR                      )    \
      ))
    #error "MemMap.h: Close the former code segment before opening a new one."
#endif

/* Check const sections */
#if ( (defined CONST_SEC_OPEN)                           && \
     ((defined START_SEC_CONST_8BIT                    ) || \
      (defined START_SEC_CONST_16BIT                   ) || \
      (defined START_SEC_CONST_32BIT                   ) || \
      (defined START_SEC_CONST_UNSPECIFIED             ) || \
      (defined START_SEC_CONST_FAST_8BIT               ) || \
      (defined START_SEC_CONST_FAST_16BIT              ) || \
      (defined START_SEC_CONST_FAST_32BIT              ) || \
      (defined START_SEC_CONST_FAST_UNSPECIFIED        ) || \
      (defined START_SEC_CONST_PBCFG                   ) || \
      (defined START_SEC_PBCFG_GLOBALROOT              )    \
      ))
    #error "MemMap.h: Close the former const segment before opening a new one."
#endif

/* Check data sections */
#if ( (defined VAR_SEC_OPEN)                             && \
     ((defined START_SEC_VAR_INIT_8BIT                 ) || \
      (defined START_SEC_VAR_INIT_16BIT                ) || \
      (defined START_SEC_VAR_INIT_32BIT                ) || \
      (defined START_SEC_VAR_INIT_UNSPECIFIED          ) || \
      (defined START_SEC_VAR_NOINIT_8BIT               ) || \
      (defined START_SEC_VAR_NOINIT_16BIT              ) || \
      (defined START_SEC_VAR_NOINIT_32BIT              ) || \
      (defined START_SEC_VAR_NOINIT_UNSPECIFIED        ) || \
      (defined START_SEC_VAR_PBCFG                     ) || \
      (defined START_SEC_VAR_ZERO_INIT_8BIT            ) || \
      (defined START_SEC_VAR_ZERO_INIT_16BIT           ) || \
      (defined START_SEC_VAR_ZERO_INIT_32BIT           ) || \
      (defined START_SEC_VAR_ZERO_INIT_UNSPECIFIED     ) || \
      (defined START_SEC_VAR_FAST_INIT_8BIT            ) || \
      (defined START_SEC_VAR_FAST_INIT_16BIT           ) || \
      (defined START_SEC_VAR_FAST_INIT_32BIT           ) || \
      (defined START_SEC_VAR_FAST_INIT_UNSPECIFIED     ) || \
      (defined START_SEC_VAR_FAST_NOINIT_8BIT          ) || \
      (defined START_SEC_VAR_FAST_NOINIT_16BIT         ) || \
      (defined START_SEC_VAR_FAST_NOINIT_32BIT         ) || \
      (defined START_SEC_VAR_FAST_NOINIT_UNSPECIFIED   ) || \
      (defined START_SEC_VAR_FAST_ZERO_INIT_8BIT       ) || \
      (defined START_SEC_VAR_FAST_ZERO_INIT_16BIT      ) || \
      (defined START_SEC_VAR_FAST_ZERO_INIT_32BIT      ) || \
      (defined START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED) || \
      (defined START_SEC_VAR_NOCACHE_INIT_8BIT         ) || \
      (defined START_SEC_VAR_NOCACHE_INIT_16BIT        ) || \
      (defined START_SEC_VAR_NOCACHE_INIT_32BIT        ) || \
      (defined START_SEC_VAR_NOCACHE_INIT_UNSPECIFIED  ) || \
      (defined START_SEC_VAR_NOCACHE_NOINIT_8BIT       ) || \
      (defined START_SEC_VAR_NOCACHE_NOINIT_16BIT      ) || \
      (defined START_SEC_VAR_NOCACHE_NOINIT_32BIT      ) || \
      (defined START_SEC_VAR_NOCACHE_NOINIT_UNSPECIFIED) || \
      (defined START_SEC_VAR_NOCACHE_ZERO_INIT_8BIT    ) || \
      (defined START_SEC_VAR_NOCACHE_ZERO_INIT_16BIT   ) || \
      (defined START_SEC_VAR_NOCACHE_ZERO_INIT_32BIT   ) || \
      (defined START_SEC_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED)    \
      ))
    #error "MemMap.h: Close the former variable segment before opening a new one."
#endif



/*------------------------------GLOBAL-START-SECTIONS------------------------------*/

/* Code section */
#ifdef START_SEC_CODE                          
    #define CODE_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_CODE                           /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_CODE_FAST                     
    #define CODE_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_CODE_FAST                      /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_CODE_ISR                      
    #define CODE_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_CODE_ISR                       /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif




/* Const section */
#ifdef START_SEC_CONST_8BIT                    
    #define CONST_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_CONST_8BIT                     /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_CONST_16BIT                   
    #define CONST_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_CONST_16BIT                    /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_CONST_32BIT                   
    #define CONST_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_CONST_32BIT                    /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_CONST_UNSPECIFIED             
    #define CONST_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_CONST_UNSPECIFIED              /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_CONST_FAST_8BIT               
    #define CONST_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_CONST_FAST_8BIT                /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_CONST_FAST_16BIT              
    #define CONST_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_CONST_FAST_16BIT               /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_CONST_FAST_32BIT              
    #define CONST_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_CONST_FAST_32BIT               /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_CONST_FAST_UNSPECIFIED        
    #define CONST_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_CONST_FAST_UNSPECIFIED         /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_CONST_PBCFG                   
    #define CONST_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_CONST_PBCFG                    /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_PBCFG_GLOBALROOT              
    #define CONST_SEC_OPEN
/* Enter here a #pragma command for opening the specified section */
/*    #pragma */
    #undef START_SEC_PBCFG_GLOBALROOT               /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif




/* Var section */
#ifdef START_SEC_VAR_INIT_8BIT                 
    #define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_0:init")
    #undef START_SEC_VAR_INIT_8BIT                  /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_INIT_16BIT                
    #define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_0:init")
    #undef START_SEC_VAR_INIT_16BIT                 /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_INIT_32BIT                
    #define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_0:init")
    #undef START_SEC_VAR_INIT_32BIT                 /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_INIT_UNSPECIFIED          
    #define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_0:init")
    #undef START_SEC_VAR_INIT_UNSPECIFIED           /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_NOINIT_8BIT               
    #define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_0:noinit")
    #undef START_SEC_VAR_NOINIT_8BIT                /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_NOINIT_16BIT              
    #define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_0:noinit")
    #undef START_SEC_VAR_NOINIT_16BIT               /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_NOINIT_32BIT              
    #define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_0:noinit")
    #undef START_SEC_VAR_NOINIT_32BIT               /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_NOINIT_UNSPECIFIED        
    #define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_0:noinit")
    #undef START_SEC_VAR_NOINIT_UNSPECIFIED         /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_PBCFG                     
    #define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_0:noinit")
    #undef START_SEC_VAR_PBCFG                      /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_ZERO_INIT_8BIT            
    #define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_0:init")
    #undef START_SEC_VAR_ZERO_INIT_8BIT             /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_ZERO_INIT_16BIT           
    #define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_0:init")
    #undef START_SEC_VAR_ZERO_INIT_16BIT            /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_ZERO_INIT_32BIT           
    #define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_0:init")
    #undef START_SEC_VAR_ZERO_INIT_32BIT            /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_ZERO_INIT_UNSPECIFIED     
    #define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_0:init")
    #undef START_SEC_VAR_ZERO_INIT_UNSPECIFIED      /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_FAST_INIT_8BIT            
    #define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_0:init")
    #undef START_SEC_VAR_FAST_INIT_8BIT             /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_FAST_INIT_16BIT           
    #define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_0:init")
    #undef START_SEC_VAR_FAST_INIT_16BIT            /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_FAST_INIT_32BIT           
    #define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_0:init")
    #undef START_SEC_VAR_FAST_INIT_32BIT            /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_FAST_INIT_UNSPECIFIED     
    #define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_0:init")
    #undef START_SEC_VAR_FAST_INIT_UNSPECIFIED      /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_FAST_NOINIT_8BIT          
    #define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_0:noinit")
    #undef START_SEC_VAR_FAST_NOINIT_8BIT           /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_FAST_NOINIT_16BIT         
    #define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_0:noinit")
    #undef START_SEC_VAR_FAST_NOINIT_16BIT          /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_FAST_NOINIT_32BIT         
    #define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_0:noinit")
    #undef START_SEC_VAR_FAST_NOINIT_32BIT          /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_FAST_NOINIT_UNSPECIFIED   
    #define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_0:noinit")
    #undef START_SEC_VAR_FAST_NOINIT_UNSPECIFIED    /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_FAST_ZERO_INIT_8BIT       
    #define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_0:init")
    #undef START_SEC_VAR_FAST_ZERO_INIT_8BIT        /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_FAST_ZERO_INIT_16BIT      
    #define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_0:init")
    #undef START_SEC_VAR_FAST_ZERO_INIT_16BIT       /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_FAST_ZERO_INIT_32BIT      
    #define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_0:init")
    #undef START_SEC_VAR_FAST_ZERO_INIT_32BIT       /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED
    #define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_0:init")
    #undef START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_NOCACHE_INIT_8BIT         
    #define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_0:init")
    #undef START_SEC_VAR_NOCACHE_INIT_8BIT          /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_NOCACHE_INIT_16BIT        
    #define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_0:init")
    #undef START_SEC_VAR_NOCACHE_INIT_16BIT         /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_NOCACHE_INIT_32BIT        
    #define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_0:init")
    #undef START_SEC_VAR_NOCACHE_INIT_32BIT         /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_NOCACHE_INIT_UNSPECIFIED  
    #define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_0:init")
    #undef START_SEC_VAR_NOCACHE_INIT_UNSPECIFIED   /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_NOCACHE_NOINIT_8BIT       
    #define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_0:noinit")
    #undef START_SEC_VAR_NOCACHE_NOINIT_8BIT        /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_NOCACHE_NOINIT_16BIT      
    #define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_0:noinit")
    #undef START_SEC_VAR_NOCACHE_NOINIT_16BIT       /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_NOCACHE_NOINIT_32BIT      
    #define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_0:noinit")
    #undef START_SEC_VAR_NOCACHE_NOINIT_32BIT       /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_NOCACHE_NOINIT_UNSPECIFIED
    #define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_0:noinit")
    #undef START_SEC_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_NOCACHE_ZERO_INIT_8BIT    
    #define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_0:init")
    #undef START_SEC_VAR_NOCACHE_ZERO_INIT_8BIT     /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_NOCACHE_ZERO_INIT_16BIT   
    #define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_0:init")
    #undef START_SEC_VAR_NOCACHE_ZERO_INIT_16BIT    /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_NOCACHE_ZERO_INIT_32BIT   
    #define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_0:init")
    #undef START_SEC_VAR_NOCACHE_ZERO_INIT_32BIT    /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef START_SEC_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED
    #define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_0:init")
    #undef START_SEC_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

#ifdef START_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".noclear")
	#undef START_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
	#undef MEMMAP_ERROR
#endif



/**************** Application 0 ****************/

#ifdef START_SEC_VAR_INIT_8BIT_0
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_0:init")
	#undef START_SEC_VAR_INIT_8BIT_0
	#undef MEMMAP_ERROR
#endif

#ifdef START_SEC_VAR_INIT_16BIT_0
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_0:init")
	#undef START_SEC_VAR_INIT_16BIT_0
	#undef MEMMAP_ERROR
#endif

#ifdef START_SEC_VAR_INIT_32BIT_0
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_0:init")
	#undef START_SEC_VAR_INIT_32BIT_0
	#undef MEMMAP_ERROR
#endif

#ifdef START_SEC_VAR_INIT_UNSPECIFIED_0
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_0:init")
	#undef START_SEC_VAR_INIT_UNSPECIFIED_0
	#undef MEMMAP_ERROR
#endif


#ifdef START_SEC_VAR_NOINIT_8BIT_0
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_0:noinit")
	#undef START_SEC_VAR_NOINIT_8BIT_0
	#undef MEMMAP_ERROR
#endif

#ifdef START_SEC_VAR_NOINIT_16BIT_0
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_0:noinit")
	#undef START_SEC_VAR_NOINIT_16BIT_0
	#undef MEMMAP_ERROR
#endif

#ifdef START_SEC_VAR_NOINIT_32BIT_0
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_0:noinit")
	#undef START_SEC_VAR_NOINIT_32BIT_0
	#undef MEMMAP_ERROR
#endif

#ifdef START_SEC_VAR_NOINIT_UNSPECIFIED_0
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_0:noinit")
	#undef START_SEC_VAR_NOINIT_UNSPECIFIED_0
	#undef MEMMAP_ERROR
#endif


#ifdef START_SEC_VAR_ZERO_INIT_8BIT_0
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_0:init")
	#undef START_SEC_VAR_ZERO_INIT_8BIT_0
	#undef MEMMAP_ERROR
#endif

#ifdef START_SEC_VAR_ZERO_INIT_16BIT_0
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_0:init")
	#undef START_SEC_VAR_ZERO_INIT_16BIT_0
	#undef MEMMAP_ERROR
#endif

#ifdef START_SEC_VAR_ZERO_INIT_32BIT_0
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_0:init")
	#undef START_SEC_VAR_ZERO_INIT_32BIT_0
	#undef MEMMAP_ERROR
#endif

#ifdef START_SEC_VAR_ZERO_INIT_UNSPECIFIED_0
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_0:init")
	#undef START_SEC_VAR_ZERO_INIT_UNSPECIFIED_0
	#undef MEMMAP_ERROR
#endif



/**************** Application 8 ****************/

#ifdef START_SEC_VAR_INIT_8BIT_8
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_8:init")
	#undef START_SEC_VAR_INIT_8BIT_8
	#undef MEMMAP_ERROR
#endif

#ifdef START_SEC_VAR_INIT_16BIT_8
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_8:init")
	#undef START_SEC_VAR_INIT_16BIT_8
	#undef MEMMAP_ERROR
#endif

#ifdef START_SEC_VAR_INIT_32BIT_8
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_8:init")
	#undef START_SEC_VAR_INIT_32BIT_8
	#undef MEMMAP_ERROR
#endif

#ifdef START_SEC_VAR_INIT_UNSPECIFIED_8
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_8:init")
	#undef START_SEC_VAR_INIT_UNSPECIFIED_8
	#undef MEMMAP_ERROR
#endif


#ifdef START_SEC_VAR_NOINIT_8BIT_8
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_8:noinit")
	#undef START_SEC_VAR_NOINIT_8BIT_8
	#undef MEMMAP_ERROR
#endif

#ifdef START_SEC_VAR_NOINIT_16BIT_8
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_8:noinit")
	#undef START_SEC_VAR_NOINIT_16BIT_8
	#undef MEMMAP_ERROR
#endif

#ifdef START_SEC_VAR_NOINIT_32BIT_8
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_8:noinit")
	#undef START_SEC_VAR_NOINIT_32BIT_8
	#undef MEMMAP_ERROR
#endif

#ifdef START_SEC_VAR_NOINIT_UNSPECIFIED_8
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_8:noinit")
	#undef START_SEC_VAR_NOINIT_UNSPECIFIED_8
	#undef MEMMAP_ERROR
#endif


#ifdef START_SEC_VAR_ZERO_INIT_8BIT_8
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_8:init")
	#undef START_SEC_VAR_ZERO_INIT_8BIT_8
	#undef MEMMAP_ERROR
#endif

#ifdef START_SEC_VAR_ZERO_INIT_16BIT_8
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_8:init")
	#undef START_SEC_VAR_ZERO_INIT_16BIT_8
	#undef MEMMAP_ERROR
#endif

#ifdef START_SEC_VAR_ZERO_INIT_32BIT_8
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_8:init")
	#undef START_SEC_VAR_ZERO_INIT_32BIT_8
	#undef MEMMAP_ERROR
#endif

#ifdef START_SEC_VAR_ZERO_INIT_UNSPECIFIED_8
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_8:init")
	#undef START_SEC_VAR_ZERO_INIT_UNSPECIFIED_8
	#undef MEMMAP_ERROR
#endif



/**************** Application 9 ****************/

#ifdef START_SEC_VAR_INIT_8BIT_9
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_9:init")
	#undef START_SEC_VAR_INIT_8BIT_9
	#undef MEMMAP_ERROR
#endif

#ifdef START_SEC_VAR_INIT_16BIT_9
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_9:init")
	#undef START_SEC_VAR_INIT_16BIT_9
	#undef MEMMAP_ERROR
#endif

#ifdef START_SEC_VAR_INIT_32BIT_9
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_9:init")
	#undef START_SEC_VAR_INIT_32BIT_9
	#undef MEMMAP_ERROR
#endif

#ifdef START_SEC_VAR_INIT_UNSPECIFIED_9
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_9:init")
	#undef START_SEC_VAR_INIT_UNSPECIFIED_9
	#undef MEMMAP_ERROR
#endif


#ifdef START_SEC_VAR_NOINIT_8BIT_9
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_9:noinit")
	#undef START_SEC_VAR_NOINIT_8BIT_9
	#undef MEMMAP_ERROR
#endif

#ifdef START_SEC_VAR_NOINIT_16BIT_9
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_9:noinit")
	#undef START_SEC_VAR_NOINIT_16BIT_9
	#undef MEMMAP_ERROR
#endif

#ifdef START_SEC_VAR_NOINIT_32BIT_9
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_9:noinit")
	#undef START_SEC_VAR_NOINIT_32BIT_9
	#undef MEMMAP_ERROR
#endif

#ifdef START_SEC_VAR_NOINIT_UNSPECIFIED_9
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_9:noinit")
	#undef START_SEC_VAR_NOINIT_UNSPECIFIED_9
	#undef MEMMAP_ERROR
#endif


#ifdef START_SEC_VAR_ZERO_INIT_8BIT_9
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_9:init")
	#undef START_SEC_VAR_ZERO_INIT_8BIT_9
	#undef MEMMAP_ERROR
#endif

#ifdef START_SEC_VAR_ZERO_INIT_16BIT_9
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_9:init")
	#undef START_SEC_VAR_ZERO_INIT_16BIT_9
	#undef MEMMAP_ERROR
#endif

#ifdef START_SEC_VAR_ZERO_INIT_32BIT_9
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_9:init")
	#undef START_SEC_VAR_ZERO_INIT_32BIT_9
	#undef MEMMAP_ERROR
#endif

#ifdef START_SEC_VAR_ZERO_INIT_UNSPECIFIED_9
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_9:init")
	#undef START_SEC_VAR_ZERO_INIT_UNSPECIFIED_9
	#undef MEMMAP_ERROR
#endif


#ifdef START_SEC_VAR_FAST_NOINIT_8BIT_9
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_9:noinit")
	#undef START_SEC_VAR_FAST_NOINIT_8BIT_9
	#undef MEMMAP_ERROR
#endif

#ifdef START_SEC_VAR_FAST_NOINIT_16BIT_9
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_9:noinit")
	#undef START_SEC_VAR_FAST_NOINIT_16BIT_9
	#undef MEMMAP_ERROR
#endif

#ifdef START_SEC_VAR_FAST_NOINIT_32BIT_9
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_9:noinit")
	#undef START_SEC_VAR_FAST_NOINIT_32BIT_9
	#undef MEMMAP_ERROR
#endif

#ifdef START_SEC_VAR_FAST_NOINIT_UNSPECIFIED_9
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_9:noinit")
	#undef START_SEC_VAR_FAST_NOINIT_UNSPECIFIED_9
	#undef MEMMAP_ERROR
#endif



/**************** Application 10 ****************/

#ifdef START_SEC_VAR_INIT_8BIT_10
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_10:init")
	#undef START_SEC_VAR_INIT_8BIT_10
	#undef MEMMAP_ERROR
#endif

#ifdef START_SEC_VAR_INIT_16BIT_10
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_10:init")
	#undef START_SEC_VAR_INIT_16BIT_10
	#undef MEMMAP_ERROR
#endif

#ifdef START_SEC_VAR_INIT_32BIT_10
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_10:init")
	#undef START_SEC_VAR_INIT_32BIT_10
	#undef MEMMAP_ERROR
#endif

#ifdef START_SEC_VAR_INIT_UNSPECIFIED_10
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_10:init")
	#undef START_SEC_VAR_INIT_UNSPECIFIED_10
	#undef MEMMAP_ERROR
#endif


#ifdef START_SEC_VAR_NOINIT_8BIT_10
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_10:noinit")
	#undef START_SEC_VAR_NOINIT_8BIT_10
	#undef MEMMAP_ERROR
#endif

#ifdef START_SEC_VAR_NOINIT_16BIT_10
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_10:noinit")
	#undef START_SEC_VAR_NOINIT_16BIT_10
	#undef MEMMAP_ERROR
#endif

#ifdef START_SEC_VAR_NOINIT_32BIT_10
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_10:noinit")
	#undef START_SEC_VAR_NOINIT_32BIT_10
	#undef MEMMAP_ERROR
#endif

#ifdef START_SEC_VAR_NOINIT_UNSPECIFIED_10
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_10:noinit")
	#undef START_SEC_VAR_NOINIT_UNSPECIFIED_10
	#undef MEMMAP_ERROR
#endif


#ifdef START_SEC_VAR_ZERO_INIT_8BIT_10
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_10:init")
	#undef START_SEC_VAR_ZERO_INIT_8BIT_10
	#undef MEMMAP_ERROR
#endif

#ifdef START_SEC_VAR_ZERO_INIT_16BIT_10
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_10:init")
	#undef START_SEC_VAR_ZERO_INIT_16BIT_10
	#undef MEMMAP_ERROR
#endif

#ifdef START_SEC_VAR_ZERO_INIT_32BIT_10
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_10:init")
	#undef START_SEC_VAR_ZERO_INIT_32BIT_10
	#undef MEMMAP_ERROR
#endif

#ifdef START_SEC_VAR_ZERO_INIT_UNSPECIFIED_10
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossDataAp_10:init")
	#undef START_SEC_VAR_ZERO_INIT_UNSPECIFIED_10
	#undef MEMMAP_ERROR
#endif



/**************** Global Shared ****************/

#ifdef START_SEC_VAR_INIT_8BIT_GLOBALSHARED
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossGlobalShared")
	#undef START_SEC_VAR_INIT_8BIT_GLOBALSHARED
	#undef MEMMAP_ERROR
#endif

#ifdef START_SEC_VAR_INIT_16BIT_GLOBALSHARED
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossGlobalShared")
	#undef START_SEC_VAR_INIT_16BIT_GLOBALSHARED
	#undef MEMMAP_ERROR
#endif

#ifdef START_SEC_VAR_INIT_32BIT_GLOBALSHARED
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossGlobalShared")
	#undef START_SEC_VAR_INIT_32BIT_GLOBALSHARED
	#undef MEMMAP_ERROR
#endif

#ifdef START_SEC_VAR_INIT_UNSPECIFIED_GLOBALSHARED
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossGlobalShared")
	#undef START_SEC_VAR_INIT_UNSPECIFIED_GLOBALSHARED
	#undef MEMMAP_ERROR
#endif


#ifdef START_SEC_VAR_NOINIT_8BIT_GLOBALSHARED
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossGlobalShared")
	#undef START_SEC_VAR_NOINIT_8BIT_GLOBALSHARED
	#undef MEMMAP_ERROR
#endif

#ifdef START_SEC_VAR_NOINIT_16BIT_GLOBALSHARED
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossGlobalShared")
	#undef START_SEC_VAR_NOINIT_16BIT_GLOBALSHARED
	#undef MEMMAP_ERROR
#endif

#ifdef START_SEC_VAR_NOINIT_32BIT_GLOBALSHARED
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossGlobalShared")
	#undef START_SEC_VAR_NOINIT_32BIT_GLOBALSHARED
	#undef MEMMAP_ERROR
#endif

#ifdef START_SEC_VAR_NOINIT_UNSPECIFIED_GLOBALSHARED
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossGlobalShared")
	#undef START_SEC_VAR_NOINIT_UNSPECIFIED_GLOBALSHARED
	#undef MEMMAP_ERROR
#endif


#ifdef START_SEC_VAR_ZERO_INIT_8BIT_GLOBALSHARED
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossGlobalShared")
	#undef START_SEC_VAR_ZERO_INIT_8BIT_GLOBALSHARED
	#undef MEMMAP_ERROR
#endif

#ifdef START_SEC_VAR_ZERO_INIT_16BIT_GLOBALSHARED
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossGlobalShared")
	#undef START_SEC_VAR_ZERO_INIT_16BIT_GLOBALSHARED
	#undef MEMMAP_ERROR
#endif

#ifdef START_SEC_VAR_ZERO_INIT_32BIT_GLOBALSHARED
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossGlobalShared")
	#undef START_SEC_VAR_ZERO_INIT_32BIT_GLOBALSHARED
	#undef MEMMAP_ERROR
#endif

#ifdef START_SEC_VAR_ZERO_INIT_UNSPECIFIED_GLOBALSHARED
	#define VAR_SEC_OPEN
	#pragma SET_DATA_SECTION(".ossGlobalShared")
	#undef START_SEC_VAR_ZERO_INIT_UNSPECIFIED_GLOBALSHARED
	#undef MEMMAP_ERROR
#endif



/*------------------------------GENERAL-STOP-SECTIONS-------------------------------*/

/*default segment for Code*/
#ifdef STOP_SEC_CODE
    #undef CODE_SEC_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
	#pragma SET_CODE_SECTION()
    #undef STOP_SEC_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

/*default segment for Constants*/
#ifdef STOP_SEC_CONST_UNSPECIFIED
	#undef CONST_SEC_OPEN
	#pragma SET_DATA_SECTION()
	#undef STOP_SEC_CONST_UNSPECIFIED
	#undef MEMMAP_ERROR
#endif

/*default segment for Constants*/
#ifdef STOP_SEC_CONST
    #undef CONST_SEC_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
	#pragma SET_DATA_SECTION()
    #undef STOP_SEC_CONST /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif

/*default segment for Datas*/
#ifdef STOP_SEC_VAR
    #undef VAR_SEC_OPEN /* PRQA S 0841 */ /* MD_MSR_19.6 */
	#pragma SET_DATA_SECTION()
    #undef STOP_SEC_VAR /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_19.6 */
#endif


#ifdef MEMMAP_ERROR
    #error "MemMap.h, wrong pragma command"
#endif

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  END OF FILE: MemMap.h
 *********************************************************************************************************************/

/* PRQA L:MEMMAP_0841_TAG */

