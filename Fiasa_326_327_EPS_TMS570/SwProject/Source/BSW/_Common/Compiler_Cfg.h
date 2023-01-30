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
 *         File:  _Compiler_Cfg.h
 *    Component:  -
 *       Module:  -
 *    Generator:  -
 *
 *  Description:  This File is a template for the Compiler_Cfg.h
 *                This file has to be extended with the memory and pointer classes for all BSW modules
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
 *  01.01.01  2008-12-17  Ht                    Improve list of components  (Tp_AsrTpCan,Tp_AsrTpFr,DrvMcu,DrvIcu added)
 *  01.01.02  2009-04-27  Ht                    support OEM specific _compiler_cfg.inc file, improve list of components 
 *                                              (Cp_XcpOnCanAsr, Il_AsrIpduM, If_VxFblDcm, If_VxFblVpm_Volvo_ab, DrvFls added)
 *  01.01.03  2009-04-24  Msr                   Renamed J1939_AsrBase as TpJ1939_AsrBase
 *  01.01.04  2009-06-03  Ht                    Improve list of components (Adc, Dio, Gpt, Pwm, Spi, Wdg, Fls, Port, Fim)
 *  01.02.00  2009-08-01  Ht                    Improve list of components (Fee_30_Inst2, Can, ...Sub)
 *                                              Support filtering for RTE
 *  01.02.01  2009-09-02  Lo                    add external Flash driver support
 *  01.02.02  2009-09-21  Lo                    add DrvFls_Mcs12xFslftm01ExtVx
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
 *  01.03.02  2010-02-15  Ht                   support SysService_SswRcs_Daimler, SysService_Tls, Tp_Http, 
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
 *  01.05.04  2010-11-16  Ht                    add SysService_Exi, DrvTrans_Int6400EthAsr, Cdd_AsrCdd_Fiat, Diag_AsrDem_Fiat,
 *  01.05.05  2010-12-17  Ht                    add SysService_AsrSchM, DrvEep_XXStubAsr, DrvIcu_Tms570Tinhet01ExtVx
 *                                                  DrvWd_XTle4278gEAsr, DrvWd_XXStubAsr
 *  01.05.06  2011-02-17  Ht                    add DrvEed, SysService_AsrBswM
 *  01.05.07  2011-03-04  Ht                    add DrvTrans_Tja1055CandioAsr
 *                                              rename CanTrcv_30_Tja1040dio to CanTrcv_30_Tja1040
 *                                              add SysService_XmlEngine
 *  01.06.00  2011-03-04  Ht                    support ASR4.0
 *                                              add Ccl_Asr4ComM, Ccl_Asr4SmCan, Nm_Asr4NmIf, Nm_AsrNmDirOsek
 *  01.06.01  2011-04-15  Ht                    add Diag_AsrDcm_<OEM>
 *  01.06.02  2011-06-17  Ht                    correct Diag_AsrDcm_<OEM>
 *                                              add Monitoring_AsrDlt and Monitoring_GenericMeasurement
 *  01.06.03  2011-09-01  Ht                    add DrvTrans_Tja1145CanSpiAsr, DrvTrans_E52013CanspiAsr, DrvFls_XXStubAsr,
 *                                              If_AsrIfFeeV85xNec05Sub, If_AsrIfFeeV85xNec06Sub, If_AsrIfFeeV85xNec07Sub
 *                                              SysService_AsrWdMTttechSub and If_AsrIfWdTttechSub
 *  01.06.04  2011-10-20  Ht                    ESCAN00054334: add If_AsrIfFeeTiSub
 *                                              ESCAN00054719: add Cdd_AsrCdd
 *  01.06.05  2011-12-09  Ht                    add Tp_IpV4, Tp_IpV6
 *  01.06.06  2011-12-14  Ht                    add Monitoring_RuntimeMeasurement
 *  01.06.07  2012-01-03  Ht                    add DrvI2c, SysService_Asr4BswM
 *  01.06.08  2012-01-31  Ht                    add DrvTrans_Ar7000EthAsr, DrvTrans_GenericEthmiiAsr
 *  01.06.09  2012-03-06  Ht                    add If_AsrIfFeeMb9df126Fuji01Sub, 
 *                                              Infineon_Tc1767Inf01Sub, Infineon_Tc178xInf01Sub, Infineon_Tc1797Inf01Sub, Infineon_Tc1797Inf02Sub
 *  01.06.10  2012-03-13  Ht                    add Gw_AsrPduRCfg5, Il_AsrComCfg5, Il_AsrIpduMCfg5, Cdd_AsrCddCfg5,
 *                                              Tp_Asr4TpCan, Diag_Asr4Dcm, Diag_Asr4Dem
 *  01.06.11  2012-03-20  Ht                    add Cp_AsrCcp, Cp_XcpOnTcpIpAsr
 *  01.07.00  2012-07-26  Ht                    add Nm_Asr4NmCan, Nm_Asr4NmFr, Infineon_Xc2000Inf01Sub, Ccl_Asr4ComMCfg5, SysService_Asr4BswMCfg5, SysService_Asr4EcuM, SysService_AsrRamTst,
 *                                                  Ccl_Asr4SmLin
 *                                              add define REGSPACE - add support for ASR specification 4.0 R3
 *  01.07.01  2012-10-23  Seu                   add SysService_XmlSecurity
 *  01.07.02  2013-12-16  Seu                   MISRA compliance: usage of character "'" removed, typos corrected
 *********************************************************************************************************************/
#ifndef COMPILER_CFG_H
#define COMPILER_CFG_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
/* Package Merger: Start Section CompilerCfgIncludes */



/* Package Merger: Stop Section CompilerCfgIncludes */

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

#define AUTOSAR_COMSTACKDATA

#define MSR_REGSPACE  REGSPACE

/* Configurable memory class for pointers to registers (e.g. static volatile CONSTP2VAR(uint16, PWM_CONST, REGSPACE)). */
#define REGSPACE


/* due to compatibility to ASR 2.1 */
#define _STATIC_   STATIC
#define _INLINE_   INLINE

/* Package Merger: Start Section CompilerCfgModuleList */

#define V_SUPPRESS_EXTENDED_VERSION_CHECK

#if defined ( V_ENABLE_USE_DUMMY_STATEMENT )
#  define V_USE_DUMMY_STATEMENT STD_ON
#else
#  define V_USE_DUMMY_STATEMENT STD_OFF
#endif


/* include Rte Compiler_Cfg because the Rte sections are configuration dependent*/
#include "Rte_Compiler_Cfg.h"


/**********************************************************************************************************************
 *  Adc START
 *********************************************************************************************************************/
#define ADC_CODE
#define ADC_CONST
#define ADC_PBCFG
#define ADC_APPL_DATA
#define ADC_VAR
/**********************************************************************************************************************
 *  Adc END
 *********************************************************************************************************************/


#define DIO_CONST
#define DIO_CODE
#define DIO_APPL_DATA
#define DIO_VAR


#define EEP_30_AT25128_CODE
#define EEP_30_AT25128_APPL_CODE
#define EEP_30_AT25128_PBCFG
#define EEP_30_AT25128_CONST
#define EEP_30_AT25128_VAR
#define EEP_30_AT25128_VAR_NOINIT
#define EEP_30_AT25128_APPL_DATA


#define GPT_CODE
#define GPT_DATA
#define GPT_CONST
#define GPT_APPL_DATA
#define GPT_APPL_CODE
#define GPT_PBCFG


/**********************************************************************************************************************
 * MCU START
 *********************************************************************************************************************/

#define MCU_APPL_DATA
#define MCU_CODE
#define MCU_DATA
#define MCU_PBCFG
#define MCU_RAM_COPY
#define MCU_ROM_COPY
#define MICROSAR_NEAR

/**********************************************************************************************************************
 *  MCU END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  PORT START 
 *********************************************************************************************************************/
 
#define PORT_CODE
#define PORT_PBCODE
#define PORT_VAR
#define PORT_APPL_DATA
#define PORT_PBCFG

/**********************************************************************************************************************
 *  PORT END 
 *********************************************************************************************************************/


#define PWM_CODE
#define PWM_VAR
#define PWM_APPL_DATA
#define PWM_PBCFG


/**********************************************************************************************************************
 *  EcuAb_AsrIoHwAb START
 *********************************************************************************************************************/

#define IOHWAB_CODE
#define IOHWAB_VAR
#define IOHWAB_APPL_DATA
#define IOHWAB_APPL_CODE
#define IOHWAB_CONST

/**********************************************************************************************************************
 *  EcuAb_AsrIoHwAb END
 *********************************************************************************************************************/


#define MEMIF_CODE
#define MEMIF_CONST
#define MEMIF_APPL_DATA


/**********************************************************************************************************************
 *  If_AsrIfWd START
 *********************************************************************************************************************/

#define WDGIF_CODE
#define WDGIF_VAR
#define WDGIF_CONST
#define WDGIF_APPL_DATA

/**********************************************************************************************************************
 *  If_AsrIfWd END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  NvM START 
 *********************************************************************************************************************/

#define NVM_APPL_DATA
#define NVM_APPL_CODE
#define NVM_APPL_CONST

#define NVM_CRC_APPL_DATA

#define NVM_CONFIG_DATA
#define NVM_CONFIG_CONST

#define NVM_FAST_DATA

#define NVM_PRIVATE_CODE
#define NVM_PRIVATE_CONST
#define NVM_PRIVATE_DATA

#define NVM_PUBLIC_CODE
#define NVM_PUBLIC_CONST

/**********************************************************************************************************************
 *  NvM END
 *********************************************************************************************************************/


#define CRC_APPL_DATA
#define CRC_CODE
#define CRC_CONST


/**********************************************************************************************************************
 *  SYSSERVICE_ASRWDM START 
 *********************************************************************************************************************/

#define WDGM_CODE

#define WDGM_VAR
#define WDGM_VAR_NOINIT
#define WDGM_DATA

#define WDGM_APPL_DATA
#define WDGM_APPL_CODE

#define WDGM_GPT_CODE
#define WDGM_CONST
#define WDGM_PBCFG

/**********************************************************************************************************************
 *  SYSSERVICE_ASRWDM END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  COMM START 
 *********************************************************************************************************************/

#define COMM_CODE

#define COMM_CONST

#define COMM_VAR_INIT
#define COMM_VAR_NOINIT
#define COMM_VAR_NOINIT_8BIT
#define COMM_VAR_NOINIT_16BIT
#define COMM_VAR_NOINIT_UNSPECIFIED
#define COMM_VAR_ZERO_INIT

#define COMM_APPL_CODE
#define COMM_APPL_VAR
#define COMM_APPL_VAR_NVRAM

#define COMM_PBCFG


/**********************************************************************************************************************
 *  COMM END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  CanSM START 
 *********************************************************************************************************************/

#define CANSM_CODE
#define CANSM_APPL_CODE

#define CANSM_CONST
#define CANSM_PBCFG

#define CANSM_VAR_INIT
#define CANSM_VAR_NOINIT
#define CANSM_VAR_ZERO_INIT

#define CANSM_APPL_VAR


/**********************************************************************************************************************
 *  CanSM END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  CddFiat START 
 *********************************************************************************************************************/

#define CDDFIAT_CODE
#define CDDFIAT_VAR
#define CDDFIAT_APPL_CODE
#define CDDFIAT_VAR_NOINIT
#define CDDFIAT_CONST
#define CDDFIAT_COM_APPL_DATA

/**********************************************************************************************************************
 *  CddFiat END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  XCP START 
 *********************************************************************************************************************/

#define XCP_CONST
#define XCP_CODE
#define XCP_APPL_DATA
#define XCP_MTA_DATA
#define XCP_DAQ_DATA
#define XCP_VAR_NOINIT


/**********************************************************************************************************************
 *  XCP END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  CANXCP START 
 *********************************************************************************************************************/

#define CANXCP_VAR_NOINIT
#define CANXCP_CONST
#define CANXCP_PBCFG
#define CANXCP_CODE
#define CANXCP_APPL_VAR

/*-------------------------------------------------------------------------------------------------------------------*/
/* CANXCP END                                                                                                        */
/*-------------------------------------------------------------------------------------------------------------------*/



#define DCM_APPL_CONST
#define DCM_APPL_DATA
#define DCM_CONST
#define DCM_CAL_PRM
#define DCM_PBCFG
#define DCM_CODE
#define DCM_APPL_CODE
#define DCM_VAR_NOINIT



/*==== DEM =================================================================*/
#define DEM_CODE                /* code */
#define DEM_VAR                 /* global/static vars; init after every reset */
#define DEM_VAR_NOINIT_FAST     /* global/static vars; using: bitaccess or frequently used or many accesses in code */
#define DEM_VAR_NOINIT          /* global/static vars; not initialized after reset */
#define DEM_CONST               /* global/static constants */
#define DEM_PBCFG               /* global/static constants for PostBuild */
#define DEM_APPL_CODE           /* callback functions used by DEM, implemented outside DEM */
#define DEM_APPL_DATA           /* vars (buffers) outside DEM, passed via API */
#define DEM_APPL_CONST          /* constants outside DEM, passed via API */
/*==========================================================================*/


/* Kernbauer Version: 1.16 Konfiguration: DrvCAN Erzeugungsgangnummer: 595 */


/**********************************************************************************************************************
 *  Can START 
 *********************************************************************************************************************/

#define CAN_CODE                                   /* CAN modules code qualifier               */ /* PRQA S 0883 */ /* Appears only while testing */
#define CAN_STATIC_CODE                            /* CAN local code qualifier                 */
#define CAN_CONST                                  /* constant memory                          */
#define CAN_CONST_PBCFG                            /* postbuild generated constant/flash       */
#define CAN_VAR_NOINIT                             /* none initialized variables               */
#define CAN_VAR_INIT                               /* initialized variables                    */
#define CAN_VAR_PBCFG                              /* postbuild generated variables/dynamic RAM (CFG5 only) */
#define CAN_INT_CTRL                               /* access to Interrupt controller registers */
#define CAN_REG_CANCELL                            /* CAN cell register qualifier              */
#define CAN_RX_TX_DATA        CAN_REG_CANCELL      /* pointer width >= CAN_REG_CANCELL  / CAN rx/tx data / RAM or SFR    (rx data pointer for Indication and PreCopy functions to higher layers / tx data pointers / sdu  from application)   */
#define CAN_APPL_CODE                              /* Application code qualifier               */
#define CAN_APPL_CONST                             /* Application constant memory              */
#define CAN_APPL_VAR                               /* Application variables                    */

/**********************************************************************************************************************
 *  Can END
 *********************************************************************************************************************/
#define CAN_PBCFG  CAN_CONST_PBCFG                 /* used for compatibility (used by upper layer EcuM) */



#define CANTRCV_30___YOUR_TRCV___CONST /* PRQA S 0883 */ /* Appears only while testing */
#define CANTRCV_30___YOUR_TRCV___VAR
#define CANTRCV_30___YOUR_TRCV___VAR_NOINIT
#define CANTRCV_30___YOUR_TRCV___APPL_VAR
#define CANTRCV_30___YOUR_TRCV___CODE
#define CANTRCV_30___YOUR_TRCV___APPL_CODE
#define CANTRCV_30___YOUR_TRCV___PBCFG



/**********************************************************************************************************************
 *  PDUR START 
 *********************************************************************************************************************/

# define PDUR_CODE
# define PDUR_VAR_NOINIT
# define PDUR_VAR_ZERO_INIT
# define PDUR_VAR
# define PDUR_CONST
# define PDUR_PBCFG
# define PDUR_APPL_DATA
# define PDUR_APPL_CODE
# define PDUR_IPDUM_DATA
# define PDUR_MOST_DATA
# define PDUR_PBCFG_ROOT		PDUR_PBCFG

/**********************************************************************************************************************
 *  PDUR END
 *********************************************************************************************************************/


/*-------------------------------------------------------------------------------------------------------------------*/
/* CANIF                                                                                                             */
/*-------------------------------------------------------------------------------------------------------------------*/


#define CANIF_VAR_NOINIT
#define CANIF_VAR_ZERO_INIT
#define CANIF_VAR_INIT


#define CANIF_CONST
#define CANIF_PBCFG
#define CANIF_PBCFG_ROOT

#define CANIF_CODE


#define CANIF_APPL_CODE
#define CANIF_APPL_VAR
#define CANIF_APPL_PBCFG


/*-------------------------------------------------------------------------------------------------------------------*/

/* Has to be kept in default section -> Default access */
#define CANIF_VAR_STACK


/* VAR section of higher layers (TP / NM / PduR / CanSM / EcuM) automatically mapped to APPL_VAR */
#define CANIF_APPL_STATE_VAR   CANIF_APPL_VAR
#define CANIF_APPL_MSG_VAR     CANIF_APPL_VAR

/* VAR section of lower layers (CAN Driver / Transceiver Driver) automatically mapped to APPL_VAR */
#define CANIF_CBK_VAR          CANIF_APPL_VAR

/* #define CANIF_CBK_TRCV_VAR     CANIF_CBK_VAR    not used yet */
#define CANIF_CBK_DRV_VAR      CANIF_CBK_VAR

/* Code sections - DO NOT MODIFY */
#define CANIF_CBK_TRCV_CODE     CANIF_APPL_CODE
#define CANIF_APPL_STATE_CODE   CANIF_APPL_CODE
#define CANIF_APPL_MSG_CODE     CANIF_APPL_CODE


/* Upper layer data pointer */
#define CANIF_UL_STANDARD_VAR    CANIF_APPL_VAR
#define CANIF_UL_ADVANCED_VAR    CANIF_APPL_VAR
#define CANIF_UL_OSEKNM_VAR      CANIF_APPL_VAR

/*-------------------------------------------------------------------------------------------------------------------*/
/* CANIF                                                                                                             */
/*-------------------------------------------------------------------------------------------------------------------*/




/**********************************************************************************************************************
 *  Com START 
 *********************************************************************************************************************/

/* Module Constant Data */
#define COM_CONST
/* Module Constant Data of the Postbuild Configuration */
#define COM_PBCFG
/* Module Root Constant of the Postbuild Configuration */
#define COM_PBCFG_ROOT   COM_PBCFG


/* Module Implementation */
#define COM_CODE

/* Module Variables which are initialized by the startup code or by the call of Com_InitMemory() */
#define COM_VAR_NOINIT
/* Module Variables which are initialized by call of Com_Init() */
#define COM_VAR_INIT

/* Application Code Implementation (e.g. Callbacks) */
#define COM_APPL_CODE
/* Application Buffer which is located in RAM */
#define COM_APPL_VAR
/* Application Buffer which is located in ROM or RAM */
#define COM_APPL_DATA

/**********************************************************************************************************************
 *  Com END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  CANNM START 
 *********************************************************************************************************************/

#define CANNM_CODE

#define CANNM_CONST
#define CANNM_PBCFG
#define CANNM_PBCFG_ROOT

#define CANNM_VAR_NOINIT
#define CANNM_VAR_NOINIT_FAST
#define CANNM_VAR_ZERO_INIT_FAST
#define CANNM_APPL_VAR

/**********************************************************************************************************************
 *  CANNM END
 *********************************************************************************************************************/
 



/**********************************************************************************************************************
 *  NM START 
 *********************************************************************************************************************/
 
#define NM_CODE

#define NM_CONST

#define NM_VAR_NOINIT
#define NM_VAR_NOINIT_FAST
#define NM_VAR_ZERO_INIT_FAST
#define NM_APPL_VAR

/**********************************************************************************************************************
 *  NM END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  BSWM START 
 *********************************************************************************************************************/

#define BSWM_CODE
#define BSWM_APPL_CODE
#define BSWM_CONST
#define BSWM_PBCFG
#define BSWM_VAR_INIT
#define BSWM_APPL_DATA
#define BSWM_VAR_NOINIT

/**********************************************************************************************************************
 *  BSWM END
 *********************************************************************************************************************/


# define DET_CODE
# define DET_VAR
# define DET_APPL_DATA
# define DET_APPL_CODE




/**********************************************************************************************************************
 *  SYSSERVICE_ASRECUM START 
 *********************************************************************************************************************/
#define ECUM_API_CODE 
#define ECUM_APPL_CONFIG 
#define ECUM_APPL_DATA 
#define ECUM_VAR_BOOT
#define ECUM_CODE
#define ECUM_CODE_BOOT_TARGET 
#define ECUM_CONST 
#define ECUM_PBCFG
#define ECUM_VAR 
#define ECUM_VAR_NOINIT 

/**********************************************************************************************************************
 *  SYSSERVICE_ASRECUM END
 *********************************************************************************************************************/


/* -------------------- FiM Compiler Abstraction -------------------- */
#define FIM_CODE
#define FIM_CONST
#define FIM_PBCFG
#define FIM_VAR_NOINIT
#define FIM_APPL_DATA


/**********************************************************************************************************************
 *  CANTP START
 *********************************************************************************************************************/

#define CANTP_VAR_INIT
#define CANTP_VAR_NOINIT
#define CANTP_CONST
#define CANTP_APPL_CONST
#define CANTP_CODE
#define CANTP_APPL_CODE
#define CANTP_APPL_DATA
#define CANTP_PBCFG

/**********************************************************************************************************************
 *  CANTP END
 *********************************************************************************************************************/


/*-------------------------------------------------------------------------------------------------------------------*/
/* VStdLib start compiler_cfg                                                                                        */
/*-------------------------------------------------------------------------------------------------------------------*/

#define VSTDLIB_CODE                               /* CAN modules code qualifier                                                                            */
#define VSTDLIB_CONST                              /* constant memory                                                                                       */
#define VSTDLIB_VAR_NEAR                           /* near variables: this is the pointer clas for "pOldState" parameter of VStdLL_GlobalInterruptDisable() */
#define VSTDLIB_CONST_FAR                          /* far constant memory: can remain empty if the application is not using FAR data (neither ROM nor RAM)  */
#define VSTDLIB_VAR_FAR                            /* far variables: can remain empty if the application is not using FAR data (neither ROM nor RAM)        */
#define VSTDLIB_VAR_NOINIT

/*-------------------------------------------------------------------------------------------------------------------*/
/* VStdLib end compiler_cfg                                                                                          */
/*-------------------------------------------------------------------------------------------------------------------*/




/* Package Merger: Stop Section CompilerCfgModuleList */

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


#endif  /* COMPILER_CFG_H */

/**********************************************************************************************************************
 *  END OF FILE: Compiler_Cfg.h
 *********************************************************************************************************************/
