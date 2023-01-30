/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  Copyright (c) 2006-2010 by Vector Informatik GmbH.                                             All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Rte_Type.h
 *     Workspace:  C:/SynergyEA3/Working/VehDyn/autosar
 *     SW-C Type:  Ap_VehDyn
 *  Generated at:  Wed Dec 16 12:52:35 2015
 *
 *     Generator:  MICROSAR RTE Generator Version 2.17.2
 *       License:  License CBD1010122 valid for CBD1010122 Nexteer  GM MSR_SLP3_BSW_RTE_wGMLAN TexasInstruments TMS570 Texas Instruments
 *
 *   Description:  Header file containing user defined AUTOSAR types and RTE structures (Contract Phase)
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_TYPE_H
# define _RTE_TYPE_H

# include "Rte.h"


/**********************************************************************************************************************
 * Data type definitions
 *********************************************************************************************************************/

# define Rte_TypeDef_Boolean
typedef boolean Boolean;

# define Rte_TypeDef_Float
typedef float32 Float;
# define Float_LowerLimit ((Float)-FLT_MAX)
# define Float_UpperLimit ((Float)FLT_MAX)

# define Rte_TypeDef_UInt16
typedef uint16 UInt16;
# define UInt16_LowerLimit ((UInt16)0u)
# define UInt16_UpperLimit ((UInt16)65535u)

# define Rte_TypeDef_UInt32
typedef uint32 UInt32;
# define UInt32_LowerLimit ((UInt32)0u)
# define UInt32_UpperLimit ((UInt32)4294967295u)

# define Rte_TypeDef_UInt8
typedef uint8 UInt8;
# define UInt8_LowerLimit ((UInt8)0u)
# define UInt8_UpperLimit ((UInt8)255u)

# define Rte_TypeDef_NTCNumber
typedef uint16 NTCNumber;
# define NTCNumber_LowerLimit ((NTCNumber)0u)
# define NTCNumber_UpperLimit ((NTCNumber)511u)
# if (defined RTE_CONST_NTC_Num_FlashWrapperLgcFlt) || (defined NTC_Num_FlashWrapperLgcFlt)
#  if (!defined RTE_CONST_NTC_Num_FlashWrapperLgcFlt) || (RTE_CONST_NTC_Num_FlashWrapperLgcFlt != 1u)
#   error "Enumeration constant <NTC_Num_FlashWrapperLgcFlt> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_FlashWrapperLgcFlt (1u)
#  define NTC_Num_FlashWrapperLgcFlt ((NTCNumber)1u)
# endif
# if (defined RTE_CONST_NTC_Num_FlashECCCorr) || (defined NTC_Num_FlashECCCorr)
#  if (!defined RTE_CONST_NTC_Num_FlashECCCorr) || (RTE_CONST_NTC_Num_FlashECCCorr != 2u)
#   error "Enumeration constant <NTC_Num_FlashECCCorr> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_FlashECCCorr (2u)
#  define NTC_Num_FlashECCCorr ((NTCNumber)2u)
# endif
# if (defined RTE_CONST_NTC_Num_FlashECCMemFlt) || (defined NTC_Num_FlashECCMemFlt)
#  if (!defined RTE_CONST_NTC_Num_FlashECCMemFlt) || (RTE_CONST_NTC_Num_FlashECCMemFlt != 3u)
#   error "Enumeration constant <NTC_Num_FlashECCMemFlt> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_FlashECCMemFlt (3u)
#  define NTC_Num_FlashECCMemFlt ((NTCNumber)3u)
# endif
# if (defined RTE_CONST_NTC_Num_FlashCRCMemFault) || (defined NTC_Num_FlashCRCMemFault)
#  if (!defined RTE_CONST_NTC_Num_FlashCRCMemFault) || (RTE_CONST_NTC_Num_FlashCRCMemFault != 4u)
#   error "Enumeration constant <NTC_Num_FlashCRCMemFault> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_FlashCRCMemFault (4u)
#  define NTC_Num_FlashCRCMemFault ((NTCNumber)4u)
# endif
# if (defined RTE_CONST_NTC_Num_NvMBlkDftActA) || (defined NTC_Num_NvMBlkDftActA)
#  if (!defined RTE_CONST_NTC_Num_NvMBlkDftActA) || (RTE_CONST_NTC_Num_NvMBlkDftActA != 6u)
#   error "Enumeration constant <NTC_Num_NvMBlkDftActA> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_NvMBlkDftActA (6u)
#  define NTC_Num_NvMBlkDftActA ((NTCNumber)6u)
# endif
# if (defined RTE_CONST_NTC_Num_NvMBlkDftActB) || (defined NTC_Num_NvMBlkDftActB)
#  if (!defined RTE_CONST_NTC_Num_NvMBlkDftActB) || (RTE_CONST_NTC_Num_NvMBlkDftActB != 7u)
#   error "Enumeration constant <NTC_Num_NvMBlkDftActB> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_NvMBlkDftActB (7u)
#  define NTC_Num_NvMBlkDftActB ((NTCNumber)7u)
# endif
# if (defined RTE_CONST_NTC_Num_NvMBlkDftActC) || (defined NTC_Num_NvMBlkDftActC)
#  if (!defined RTE_CONST_NTC_Num_NvMBlkDftActC) || (RTE_CONST_NTC_Num_NvMBlkDftActC != 8u)
#   error "Enumeration constant <NTC_Num_NvMBlkDftActC> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_NvMBlkDftActC (8u)
#  define NTC_Num_NvMBlkDftActC ((NTCNumber)8u)
# endif
# if (defined RTE_CONST_NTC_Num_CurrentSensorCalOutOfRange) || (defined NTC_Num_CurrentSensorCalOutOfRange)
#  if (!defined RTE_CONST_NTC_Num_CurrentSensorCalOutOfRange) || (RTE_CONST_NTC_Num_CurrentSensorCalOutOfRange != 9u)
#   error "Enumeration constant <NTC_Num_CurrentSensorCalOutOfRange> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_CurrentSensorCalOutOfRange (9u)
#  define NTC_Num_CurrentSensorCalOutOfRange ((NTCNumber)9u)
# endif
# if (defined RTE_CONST_NTC_Num_EEPROMDiag) || (defined NTC_Num_EEPROMDiag)
#  if (!defined RTE_CONST_NTC_Num_EEPROMDiag) || (RTE_CONST_NTC_Num_EEPROMDiag != 10u)
#   error "Enumeration constant <NTC_Num_EEPROMDiag> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_EEPROMDiag (10u)
#  define NTC_Num_EEPROMDiag ((NTCNumber)10u)
# endif
# if (defined RTE_CONST_NTC_Num_EEPROMDiagMtrStr) || (defined NTC_Num_EEPROMDiagMtrStr)
#  if (!defined RTE_CONST_NTC_Num_EEPROMDiagMtrStr) || (RTE_CONST_NTC_Num_EEPROMDiagMtrStr != 11u)
#   error "Enumeration constant <NTC_Num_EEPROMDiagMtrStr> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_EEPROMDiagMtrStr (11u)
#  define NTC_Num_EEPROMDiagMtrStr ((NTCNumber)11u)
# endif
# if (defined RTE_CONST_NTC_Num_PriSnsrTrqStorFlt) || (defined NTC_Num_PriSnsrTrqStorFlt)
#  if (!defined RTE_CONST_NTC_Num_PriSnsrTrqStorFlt) || (RTE_CONST_NTC_Num_PriSnsrTrqStorFlt != 12u)
#   error "Enumeration constant <NTC_Num_PriSnsrTrqStorFlt> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_PriSnsrTrqStorFlt (12u)
#  define NTC_Num_PriSnsrTrqStorFlt ((NTCNumber)12u)
# endif
# if (defined RTE_CONST_NTC_Num_EEPROMDiagPosTrimStr) || (defined NTC_Num_EEPROMDiagPosTrimStr)
#  if (!defined RTE_CONST_NTC_Num_EEPROMDiagPosTrimStr) || (RTE_CONST_NTC_Num_EEPROMDiagPosTrimStr != 13u)
#   error "Enumeration constant <NTC_Num_EEPROMDiagPosTrimStr> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_EEPROMDiagPosTrimStr (13u)
#  define NTC_Num_EEPROMDiagPosTrimStr ((NTCNumber)13u)
# endif
# if (defined RTE_CONST_NTC_Num_SecSnsrTrqStorFlt) || (defined NTC_Num_SecSnsrTrqStorFlt)
#  if (!defined RTE_CONST_NTC_Num_SecSnsrTrqStorFlt) || (RTE_CONST_NTC_Num_SecSnsrTrqStorFlt != 14u)
#   error "Enumeration constant <NTC_Num_SecSnsrTrqStorFlt> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_SecSnsrTrqStorFlt (14u)
#  define NTC_Num_SecSnsrTrqStorFlt ((NTCNumber)14u)
# endif
# if (defined RTE_CONST_NTC_Num_EEPROMDiagPolarityStr) || (defined NTC_Num_EEPROMDiagPolarityStr)
#  if (!defined RTE_CONST_NTC_Num_EEPROMDiagPolarityStr) || (RTE_CONST_NTC_Num_EEPROMDiagPolarityStr != 15u)
#   error "Enumeration constant <NTC_Num_EEPROMDiagPolarityStr> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_EEPROMDiagPolarityStr (15u)
#  define NTC_Num_EEPROMDiagPolarityStr ((NTCNumber)15u)
# endif
# if (defined RTE_CONST_NTC_Num_RAMDiag_GeneralFlt) || (defined NTC_Num_RAMDiag_GeneralFlt)
#  if (!defined RTE_CONST_NTC_Num_RAMDiag_GeneralFlt) || (RTE_CONST_NTC_Num_RAMDiag_GeneralFlt != 16u)
#   error "Enumeration constant <NTC_Num_RAMDiag_GeneralFlt> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_RAMDiag_GeneralFlt (16u)
#  define NTC_Num_RAMDiag_GeneralFlt ((NTCNumber)16u)
# endif
# if (defined RTE_CONST_NTC_Num_RAMDiag_WrprLgcFlt) || (defined NTC_Num_RAMDiag_WrprLgcFlt)
#  if (!defined RTE_CONST_NTC_Num_RAMDiag_WrprLgcFlt) || (RTE_CONST_NTC_Num_RAMDiag_WrprLgcFlt != 17u)
#   error "Enumeration constant <NTC_Num_RAMDiag_WrprLgcFlt> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_RAMDiag_WrprLgcFlt (17u)
#  define NTC_Num_RAMDiag_WrprLgcFlt ((NTCNumber)17u)
# endif
# if (defined RTE_CONST_NTC_Num_RAMDiag_ECCCorrIndFlt) || (defined NTC_Num_RAMDiag_ECCCorrIndFlt)
#  if (!defined RTE_CONST_NTC_Num_RAMDiag_ECCCorrIndFlt) || (RTE_CONST_NTC_Num_RAMDiag_ECCCorrIndFlt != 18u)
#   error "Enumeration constant <NTC_Num_RAMDiag_ECCCorrIndFlt> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_RAMDiag_ECCCorrIndFlt (18u)
#  define NTC_Num_RAMDiag_ECCCorrIndFlt ((NTCNumber)18u)
# endif
# if (defined RTE_CONST_NTC_Num_RAMDiag_ECCMemFlt) || (defined NTC_Num_RAMDiag_ECCMemFlt)
#  if (!defined RTE_CONST_NTC_Num_RAMDiag_ECCMemFlt) || (RTE_CONST_NTC_Num_RAMDiag_ECCMemFlt != 19u)
#   error "Enumeration constant <NTC_Num_RAMDiag_ECCMemFlt> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_RAMDiag_ECCMemFlt (19u)
#  define NTC_Num_RAMDiag_ECCMemFlt ((NTCNumber)19u)
# endif
# if (defined RTE_CONST_NTC_Num_RAMDiag_CRCMemFlt) || (defined NTC_Num_RAMDiag_CRCMemFlt)
#  if (!defined RTE_CONST_NTC_Num_RAMDiag_CRCMemFlt) || (RTE_CONST_NTC_Num_RAMDiag_CRCMemFlt != 20u)
#   error "Enumeration constant <NTC_Num_RAMDiag_CRCMemFlt> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_RAMDiag_CRCMemFlt (20u)
#  define NTC_Num_RAMDiag_CRCMemFlt ((NTCNumber)20u)
# endif
# if (defined RTE_CONST_NTC_Num_RAMDiag_VIMRamFlt) || (defined NTC_Num_RAMDiag_VIMRamFlt)
#  if (!defined RTE_CONST_NTC_Num_RAMDiag_VIMRamFlt) || (RTE_CONST_NTC_Num_RAMDiag_VIMRamFlt != 23u)
#   error "Enumeration constant <NTC_Num_RAMDiag_VIMRamFlt> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_RAMDiag_VIMRamFlt (23u)
#  define NTC_Num_RAMDiag_VIMRamFlt ((NTCNumber)23u)
# endif
# if (defined RTE_CONST_NTC_Num_RAMDiag_NHET1RamFlt) || (defined NTC_Num_RAMDiag_NHET1RamFlt)
#  if (!defined RTE_CONST_NTC_Num_RAMDiag_NHET1RamFlt) || (RTE_CONST_NTC_Num_RAMDiag_NHET1RamFlt != 24u)
#   error "Enumeration constant <NTC_Num_RAMDiag_NHET1RamFlt> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_RAMDiag_NHET1RamFlt (24u)
#  define NTC_Num_RAMDiag_NHET1RamFlt ((NTCNumber)24u)
# endif
# if (defined RTE_CONST_NTC_Num_RAMDiag_NHET2RamFlt) || (defined NTC_Num_RAMDiag_NHET2RamFlt)
#  if (!defined RTE_CONST_NTC_Num_RAMDiag_NHET2RamFlt) || (RTE_CONST_NTC_Num_RAMDiag_NHET2RamFlt != 25u)
#   error "Enumeration constant <NTC_Num_RAMDiag_NHET2RamFlt> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_RAMDiag_NHET2RamFlt (25u)
#  define NTC_Num_RAMDiag_NHET2RamFlt ((NTCNumber)25u)
# endif
# if (defined RTE_CONST_NTC_Num_RAMDiag_ADC1RamFlt) || (defined NTC_Num_RAMDiag_ADC1RamFlt)
#  if (!defined RTE_CONST_NTC_Num_RAMDiag_ADC1RamFlt) || (RTE_CONST_NTC_Num_RAMDiag_ADC1RamFlt != 26u)
#   error "Enumeration constant <NTC_Num_RAMDiag_ADC1RamFlt> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_RAMDiag_ADC1RamFlt (26u)
#  define NTC_Num_RAMDiag_ADC1RamFlt ((NTCNumber)26u)
# endif
# if (defined RTE_CONST_NTC_Num_RAMDiag_DCANRamFault) || (defined NTC_Num_RAMDiag_DCANRamFault)
#  if (!defined RTE_CONST_NTC_Num_RAMDiag_DCANRamFault) || (RTE_CONST_NTC_Num_RAMDiag_DCANRamFault != 27u)
#   error "Enumeration constant <NTC_Num_RAMDiag_DCANRamFault> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_RAMDiag_DCANRamFault (27u)
#  define NTC_Num_RAMDiag_DCANRamFault ((NTCNumber)27u)
# endif
# if (defined RTE_CONST_NTC_Num_RAMDiag_ADC2RamFlt) || (defined NTC_Num_RAMDiag_ADC2RamFlt)
#  if (!defined RTE_CONST_NTC_Num_RAMDiag_ADC2RamFlt) || (RTE_CONST_NTC_Num_RAMDiag_ADC2RamFlt != 28u)
#   error "Enumeration constant <NTC_Num_RAMDiag_ADC2RamFlt> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_RAMDiag_ADC2RamFlt (28u)
#  define NTC_Num_RAMDiag_ADC2RamFlt ((NTCNumber)28u)
# endif
# if (defined RTE_CONST_NTC_Num_RAMDiag_HETTU1RamFlt) || (defined NTC_Num_RAMDiag_HETTU1RamFlt)
#  if (!defined RTE_CONST_NTC_Num_RAMDiag_HETTU1RamFlt) || (RTE_CONST_NTC_Num_RAMDiag_HETTU1RamFlt != 29u)
#   error "Enumeration constant <NTC_Num_RAMDiag_HETTU1RamFlt> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_RAMDiag_HETTU1RamFlt (29u)
#  define NTC_Num_RAMDiag_HETTU1RamFlt ((NTCNumber)29u)
# endif
# if (defined RTE_CONST_NTC_Num_RAMDiag_HETTU2RamFlt) || (defined NTC_Num_RAMDiag_HETTU2RamFlt)
#  if (!defined RTE_CONST_NTC_Num_RAMDiag_HETTU2RamFlt) || (RTE_CONST_NTC_Num_RAMDiag_HETTU2RamFlt != 30u)
#   error "Enumeration constant <NTC_Num_RAMDiag_HETTU2RamFlt> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_RAMDiag_HETTU2RamFlt (30u)
#  define NTC_Num_RAMDiag_HETTU2RamFlt ((NTCNumber)30u)
# endif
# if (defined RTE_CONST_NTC_Num_CPU_RegVer) || (defined NTC_Num_CPU_RegVer)
#  if (!defined RTE_CONST_NTC_Num_CPU_RegVer) || (RTE_CONST_NTC_Num_CPU_RegVer != 32u)
#   error "Enumeration constant <NTC_Num_CPU_RegVer> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_CPU_RegVer (32u)
#  define NTC_Num_CPU_RegVer ((NTCNumber)32u)
# endif
# if (defined RTE_CONST_NTC_Num_CPU_CoreInitFlt) || (defined NTC_Num_CPU_CoreInitFlt)
#  if (!defined RTE_CONST_NTC_Num_CPU_CoreInitFlt) || (RTE_CONST_NTC_Num_CPU_CoreInitFlt != 33u)
#   error "Enumeration constant <NTC_Num_CPU_CoreInitFlt> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_CPU_CoreInitFlt (33u)
#  define NTC_Num_CPU_CoreInitFlt ((NTCNumber)33u)
# endif
# if (defined RTE_CONST_NTC_Num_CPU_CoreRunTimeFlt) || (defined NTC_Num_CPU_CoreRunTimeFlt)
#  if (!defined RTE_CONST_NTC_Num_CPU_CoreRunTimeFlt) || (RTE_CONST_NTC_Num_CPU_CoreRunTimeFlt != 34u)
#   error "Enumeration constant <NTC_Num_CPU_CoreRunTimeFlt> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_CPU_CoreRunTimeFlt (34u)
#  define NTC_Num_CPU_CoreRunTimeFlt ((NTCNumber)34u)
# endif
# if (defined RTE_CONST_NTC_Num_CPU_ClockMon) || (defined NTC_Num_CPU_ClockMon)
#  if (!defined RTE_CONST_NTC_Num_CPU_ClockMon) || (RTE_CONST_NTC_Num_CPU_ClockMon != 35u)
#   error "Enumeration constant <NTC_Num_CPU_ClockMon> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_CPU_ClockMon (35u)
#  define NTC_Num_CPU_ClockMon ((NTCNumber)35u)
# endif
# if (defined RTE_CONST_NTC_Num_CPU_eFuseFlt) || (defined NTC_Num_CPU_eFuseFlt)
#  if (!defined RTE_CONST_NTC_Num_CPU_eFuseFlt) || (RTE_CONST_NTC_Num_CPU_eFuseFlt != 36u)
#   error "Enumeration constant <NTC_Num_CPU_eFuseFlt> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_CPU_eFuseFlt (36u)
#  define NTC_Num_CPU_eFuseFlt ((NTCNumber)36u)
# endif
# if (defined RTE_CONST_NTC_Num_CPU_MPUViolation) || (defined NTC_Num_CPU_MPUViolation)
#  if (!defined RTE_CONST_NTC_Num_CPU_MPUViolation) || (RTE_CONST_NTC_Num_CPU_MPUViolation != 37u)
#   error "Enumeration constant <NTC_Num_CPU_MPUViolation> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_CPU_MPUViolation (37u)
#  define NTC_Num_CPU_MPUViolation ((NTCNumber)37u)
# endif
# if (defined RTE_CONST_NTC_Num_CPU_FactPrcsErr) || (defined NTC_Num_CPU_FactPrcsErr)
#  if (!defined RTE_CONST_NTC_Num_CPU_FactPrcsErr) || (RTE_CONST_NTC_Num_CPU_FactPrcsErr != 40u)
#   error "Enumeration constant <NTC_Num_CPU_FactPrcsErr> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_CPU_FactPrcsErr (40u)
#  define NTC_Num_CPU_FactPrcsErr ((NTCNumber)40u)
# endif
# if (defined RTE_CONST_NTC_Num_PropExeDiag_InitDiag) || (defined NTC_Num_PropExeDiag_InitDiag)
#  if (!defined RTE_CONST_NTC_Num_PropExeDiag_InitDiag) || (RTE_CONST_NTC_Num_PropExeDiag_InitDiag != 41u)
#   error "Enumeration constant <NTC_Num_PropExeDiag_InitDiag> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_PropExeDiag_InitDiag (41u)
#  define NTC_Num_PropExeDiag_InitDiag ((NTCNumber)41u)
# endif
# if (defined RTE_CONST_NTC_Num_PrgFlwDeadlnFlt) || (defined NTC_Num_PrgFlwDeadlnFlt)
#  if (!defined RTE_CONST_NTC_Num_PrgFlwDeadlnFlt) || (RTE_CONST_NTC_Num_PrgFlwDeadlnFlt != 42u)
#   error "Enumeration constant <NTC_Num_PrgFlwDeadlnFlt> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_PrgFlwDeadlnFlt (42u)
#  define NTC_Num_PrgFlwDeadlnFlt ((NTCNumber)42u)
# endif
# if (defined RTE_CONST_NTC_Num_PropExeDiag_RunTimeDiag) || (defined NTC_Num_PropExeDiag_RunTimeDiag)
#  if (!defined RTE_CONST_NTC_Num_PropExeDiag_RunTimeDiag) || (RTE_CONST_NTC_Num_PropExeDiag_RunTimeDiag != 43u)
#   error "Enumeration constant <NTC_Num_PropExeDiag_RunTimeDiag> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_PropExeDiag_RunTimeDiag (43u)
#  define NTC_Num_PropExeDiag_RunTimeDiag ((NTCNumber)43u)
# endif
# if (defined RTE_CONST_NTC_Num_PropExeDiag_COPTimeout) || (defined NTC_Num_PropExeDiag_COPTimeout)
#  if (!defined RTE_CONST_NTC_Num_PropExeDiag_COPTimeout) || (RTE_CONST_NTC_Num_PropExeDiag_COPTimeout != 44u)
#   error "Enumeration constant <NTC_Num_PropExeDiag_COPTimeout> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_PropExeDiag_COPTimeout (44u)
#  define NTC_Num_PropExeDiag_COPTimeout ((NTCNumber)44u)
# endif
# if (defined RTE_CONST_NTC_Num_PropExeDiag_PrefetchAbort) || (defined NTC_Num_PropExeDiag_PrefetchAbort)
#  if (!defined RTE_CONST_NTC_Num_PropExeDiag_PrefetchAbort) || (RTE_CONST_NTC_Num_PropExeDiag_PrefetchAbort != 48u)
#   error "Enumeration constant <NTC_Num_PropExeDiag_PrefetchAbort> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_PropExeDiag_PrefetchAbort (48u)
#  define NTC_Num_PropExeDiag_PrefetchAbort ((NTCNumber)48u)
# endif
# if (defined RTE_CONST_NTC_Num_PropExeDiag_DataAbort) || (defined NTC_Num_PropExeDiag_DataAbort)
#  if (!defined RTE_CONST_NTC_Num_PropExeDiag_DataAbort) || (RTE_CONST_NTC_Num_PropExeDiag_DataAbort != 49u)
#   error "Enumeration constant <NTC_Num_PropExeDiag_DataAbort> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_PropExeDiag_DataAbort (49u)
#  define NTC_Num_PropExeDiag_DataAbort ((NTCNumber)49u)
# endif
# if (defined RTE_CONST_NTC_Num_PerDiag_ADC1Flt) || (defined NTC_Num_PerDiag_ADC1Flt)
#  if (!defined RTE_CONST_NTC_Num_PerDiag_ADC1Flt) || (RTE_CONST_NTC_Num_PerDiag_ADC1Flt != 50u)
#   error "Enumeration constant <NTC_Num_PerDiag_ADC1Flt> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_PerDiag_ADC1Flt (50u)
#  define NTC_Num_PerDiag_ADC1Flt ((NTCNumber)50u)
# endif
# if (defined RTE_CONST_NTC_Num_PerDiag_ADC2Flt) || (defined NTC_Num_PerDiag_ADC2Flt)
#  if (!defined RTE_CONST_NTC_Num_PerDiag_ADC2Flt) || (RTE_CONST_NTC_Num_PerDiag_ADC2Flt != 51u)
#   error "Enumeration constant <NTC_Num_PerDiag_ADC2Flt> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_PerDiag_ADC2Flt (51u)
#  define NTC_Num_PerDiag_ADC2Flt ((NTCNumber)51u)
# endif
# if (defined RTE_CONST_NTC_Num_PerDiag_ADCCrossChkFlt) || (defined NTC_Num_PerDiag_ADCCrossChkFlt)
#  if (!defined RTE_CONST_NTC_Num_PerDiag_ADCCrossChkFlt) || (RTE_CONST_NTC_Num_PerDiag_ADCCrossChkFlt != 52u)
#   error "Enumeration constant <NTC_Num_PerDiag_ADCCrossChkFlt> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_PerDiag_ADCCrossChkFlt (52u)
#  define NTC_Num_PerDiag_ADCCrossChkFlt ((NTCNumber)52u)
# endif
# if (defined RTE_CONST_NTC_Num_PerDiag_IllegalAccess) || (defined NTC_Num_PerDiag_IllegalAccess)
#  if (!defined RTE_CONST_NTC_Num_PerDiag_IllegalAccess) || (RTE_CONST_NTC_Num_PerDiag_IllegalAccess != 53u)
#   error "Enumeration constant <NTC_Num_PerDiag_IllegalAccess> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_PerDiag_IllegalAccess (53u)
#  define NTC_Num_PerDiag_IllegalAccess ((NTCNumber)53u)
# endif
# if (defined RTE_CONST_NTC_Num_PerDiag_DMAFlt) || (defined NTC_Num_PerDiag_DMAFlt)
#  if (!defined RTE_CONST_NTC_Num_PerDiag_DMAFlt) || (RTE_CONST_NTC_Num_PerDiag_DMAFlt != 54u)
#   error "Enumeration constant <NTC_Num_PerDiag_DMAFlt> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_PerDiag_DMAFlt (54u)
#  define NTC_Num_PerDiag_DMAFlt ((NTCNumber)54u)
# endif
# if (defined RTE_CONST_NTC_Num_PeripheralStartupFlt) || (defined NTC_Num_PeripheralStartupFlt)
#  if (!defined RTE_CONST_NTC_Num_PeripheralStartupFlt) || (RTE_CONST_NTC_Num_PeripheralStartupFlt != 55u)
#   error "Enumeration constant <NTC_Num_PeripheralStartupFlt> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_PeripheralStartupFlt (55u)
#  define NTC_Num_PeripheralStartupFlt ((NTCNumber)55u)
# endif
# if (defined RTE_CONST_NTC_Num_PerDiag_CPUWarning) || (defined NTC_Num_PerDiag_CPUWarning)
#  if (!defined RTE_CONST_NTC_Num_PerDiag_CPUWarning) || (RTE_CONST_NTC_Num_PerDiag_CPUWarning != 63u)
#   error "Enumeration constant <NTC_Num_PerDiag_CPUWarning> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_PerDiag_CPUWarning (63u)
#  define NTC_Num_PerDiag_CPUWarning ((NTCNumber)63u)
# endif
# if (defined RTE_CONST_NTC_Num_TmpMonFunc) || (defined NTC_Num_TmpMonFunc)
#  if (!defined RTE_CONST_NTC_Num_TmpMonFunc) || (RTE_CONST_NTC_Num_TmpMonFunc != 64u)
#   error "Enumeration constant <NTC_Num_TmpMonFunc> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_TmpMonFunc (64u)
#  define NTC_Num_TmpMonFunc ((NTCNumber)64u)
# endif
# if (defined RTE_CONST_NTC_Num_TmpMonRunTimeFlt) || (defined NTC_Num_TmpMonRunTimeFlt)
#  if (!defined RTE_CONST_NTC_Num_TmpMonRunTimeFlt) || (RTE_CONST_NTC_Num_TmpMonRunTimeFlt != 65u)
#   error "Enumeration constant <NTC_Num_TmpMonRunTimeFlt> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_TmpMonRunTimeFlt (65u)
#  define NTC_Num_TmpMonRunTimeFlt ((NTCNumber)65u)
# endif
# if (defined RTE_CONST_NTC_Num_PowerRelayInitFlt) || (defined NTC_Num_PowerRelayInitFlt)
#  if (!defined RTE_CONST_NTC_Num_PowerRelayInitFlt) || (RTE_CONST_NTC_Num_PowerRelayInitFlt != 66u)
#   error "Enumeration constant <NTC_Num_PowerRelayInitFlt> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_PowerRelayInitFlt (66u)
#  define NTC_Num_PowerRelayInitFlt ((NTCNumber)66u)
# endif
# if (defined RTE_CONST_NTC_Num_PrechargeFailure) || (defined NTC_Num_PrechargeFailure)
#  if (!defined RTE_CONST_NTC_Num_PrechargeFailure) || (RTE_CONST_NTC_Num_PrechargeFailure != 67u)
#   error "Enumeration constant <NTC_Num_PrechargeFailure> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_PrechargeFailure (67u)
#  define NTC_Num_PrechargeFailure ((NTCNumber)67u)
# endif
# if (defined RTE_CONST_NTC_Num_PowerRelayRunFlt) || (defined NTC_Num_PowerRelayRunFlt)
#  if (!defined RTE_CONST_NTC_Num_PowerRelayRunFlt) || (RTE_CONST_NTC_Num_PowerRelayRunFlt != 68u)
#   error "Enumeration constant <NTC_Num_PowerRelayRunFlt> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_PowerRelayRunFlt (68u)
#  define NTC_Num_PowerRelayRunFlt ((NTCNumber)68u)
# endif
# if (defined RTE_CONST_NTC_Num_Thermistor) || (defined NTC_Num_Thermistor)
#  if (!defined RTE_CONST_NTC_Num_Thermistor) || (RTE_CONST_NTC_Num_Thermistor != 69u)
#   error "Enumeration constant <NTC_Num_Thermistor> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_Thermistor (69u)
#  define NTC_Num_Thermistor ((NTCNumber)69u)
# endif
# if (defined RTE_CONST_NTC_Num_RefSupplyVltg) || (defined NTC_Num_RefSupplyVltg)
#  if (!defined RTE_CONST_NTC_Num_RefSupplyVltg) || (RTE_CONST_NTC_Num_RefSupplyVltg != 70u)
#   error "Enumeration constant <NTC_Num_RefSupplyVltg> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_RefSupplyVltg (70u)
#  define NTC_Num_RefSupplyVltg ((NTCNumber)70u)
# endif
# if (defined RTE_CONST_NTC_Num_TrcvrInterfaceFlt) || (defined NTC_Num_TrcvrInterfaceFlt)
#  if (!defined RTE_CONST_NTC_Num_TrcvrInterfaceFlt) || (RTE_CONST_NTC_Num_TrcvrInterfaceFlt != 71u)
#   error "Enumeration constant <NTC_Num_TrcvrInterfaceFlt> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_TrcvrInterfaceFlt (71u)
#  define NTC_Num_TrcvrInterfaceFlt ((NTCNumber)71u)
# endif
# if (defined RTE_CONST_NTC_Num_CPUSupplyOvervoltage) || (defined NTC_Num_CPUSupplyOvervoltage)
#  if (!defined RTE_CONST_NTC_Num_CPUSupplyOvervoltage) || (RTE_CONST_NTC_Num_CPUSupplyOvervoltage != 72u)
#   error "Enumeration constant <NTC_Num_CPUSupplyOvervoltage> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_CPUSupplyOvervoltage (72u)
#  define NTC_Num_CPUSupplyOvervoltage ((NTCNumber)72u)
# endif
# if (defined RTE_CONST_NTC_Num_BattVltgMeasdCorrlnFlt) || (defined NTC_Num_BattVltgMeasdCorrlnFlt)
#  if (!defined RTE_CONST_NTC_Num_BattVltgMeasdCorrlnFlt) || (RTE_CONST_NTC_Num_BattVltgMeasdCorrlnFlt != 73u)
#   error "Enumeration constant <NTC_Num_BattVltgMeasdCorrlnFlt> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_BattVltgMeasdCorrlnFlt (73u)
#  define NTC_Num_BattVltgMeasdCorrlnFlt ((NTCNumber)73u)
# endif
# if (defined RTE_CONST_NTC_Num_IvtrPwrDiscnctFailr) || (defined NTC_Num_IvtrPwrDiscnctFailr)
#  if (!defined RTE_CONST_NTC_Num_IvtrPwrDiscnctFailr) || (RTE_CONST_NTC_Num_IvtrPwrDiscnctFailr != 74u)
#   error "Enumeration constant <NTC_Num_IvtrPwrDiscnctFailr> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_IvtrPwrDiscnctFailr (74u)
#  define NTC_Num_IvtrPwrDiscnctFailr ((NTCNumber)74u)
# endif
# if (defined RTE_CONST_NTC_Num_PowerRelayInit2Flt) || (defined NTC_Num_PowerRelayInit2Flt)
#  if (!defined RTE_CONST_NTC_Num_PowerRelayInit2Flt) || (RTE_CONST_NTC_Num_PowerRelayInit2Flt != 75u)
#   error "Enumeration constant <NTC_Num_PowerRelayInit2Flt> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_PowerRelayInit2Flt (75u)
#  define NTC_Num_PowerRelayInit2Flt ((NTCNumber)75u)
# endif
# if (defined RTE_CONST_NTC_Num_GateDrvFltInProcess) || (defined NTC_Num_GateDrvFltInProcess)
#  if (!defined RTE_CONST_NTC_Num_GateDrvFltInProcess) || (RTE_CONST_NTC_Num_GateDrvFltInProcess != 76u)
#   error "Enumeration constant <NTC_Num_GateDrvFltInProcess> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_GateDrvFltInProcess (76u)
#  define NTC_Num_GateDrvFltInProcess ((NTCNumber)76u)
# endif
# if (defined RTE_CONST_NTC_Num_GateDrvFlt) || (defined NTC_Num_GateDrvFlt)
#  if (!defined RTE_CONST_NTC_Num_GateDrvFlt) || (RTE_CONST_NTC_Num_GateDrvFlt != 77u)
#   error "Enumeration constant <NTC_Num_GateDrvFlt> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_GateDrvFlt (77u)
#  define NTC_Num_GateDrvFlt ((NTCNumber)77u)
# endif
# if (defined RTE_CONST_NTC_Num_OnStateSingleFET) || (defined NTC_Num_OnStateSingleFET)
#  if (!defined RTE_CONST_NTC_Num_OnStateSingleFET) || (RTE_CONST_NTC_Num_OnStateSingleFET != 78u)
#   error "Enumeration constant <NTC_Num_OnStateSingleFET> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_OnStateSingleFET (78u)
#  define NTC_Num_OnStateSingleFET ((NTCNumber)78u)
# endif
# if (defined RTE_CONST_NTC_Num_OnStateMultiFET) || (defined NTC_Num_OnStateMultiFET)
#  if (!defined RTE_CONST_NTC_Num_OnStateMultiFET) || (RTE_CONST_NTC_Num_OnStateMultiFET != 79u)
#   error "Enumeration constant <NTC_Num_OnStateMultiFET> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_OnStateMultiFET (79u)
#  define NTC_Num_OnStateMultiFET ((NTCNumber)79u)
# endif
# if (defined RTE_CONST_NTC_Num_PhaseVoltageVerf) || (defined NTC_Num_PhaseVoltageVerf)
#  if (!defined RTE_CONST_NTC_Num_PhaseVoltageVerf) || (RTE_CONST_NTC_Num_PhaseVoltageVerf != 80u)
#   error "Enumeration constant <NTC_Num_PhaseVoltageVerf> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_PhaseVoltageVerf (80u)
#  define NTC_Num_PhaseVoltageVerf ((NTCNumber)80u)
# endif
# if (defined RTE_CONST_NTC_Num_PhaseDscnt) || (defined NTC_Num_PhaseDscnt)
#  if (!defined RTE_CONST_NTC_Num_PhaseDscnt) || (RTE_CONST_NTC_Num_PhaseDscnt != 81u)
#   error "Enumeration constant <NTC_Num_PhaseDscnt> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_PhaseDscnt (81u)
#  define NTC_Num_PhaseDscnt ((NTCNumber)81u)
# endif
# if (defined RTE_CONST_NTC_Num_DigPhaseVoltageVerf) || (defined NTC_Num_DigPhaseVoltageVerf)
#  if (!defined RTE_CONST_NTC_Num_DigPhaseVoltageVerf) || (RTE_CONST_NTC_Num_DigPhaseVoltageVerf != 82u)
#   error "Enumeration constant <NTC_Num_DigPhaseVoltageVerf> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DigPhaseVoltageVerf (82u)
#  define NTC_Num_DigPhaseVoltageVerf ((NTCNumber)82u)
# endif
# if (defined RTE_CONST_NTC_Num_PhaseDscntFailedDisable) || (defined NTC_Num_PhaseDscntFailedDisable)
#  if (!defined RTE_CONST_NTC_Num_PhaseDscntFailedDisable) || (RTE_CONST_NTC_Num_PhaseDscntFailedDisable != 83u)
#   error "Enumeration constant <NTC_Num_PhaseDscntFailedDisable> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_PhaseDscntFailedDisable (83u)
#  define NTC_Num_PhaseDscntFailedDisable ((NTCNumber)83u)
# endif
# if (defined RTE_CONST_NTC_Num_CurrentMeas1) || (defined NTC_Num_CurrentMeas1)
#  if (!defined RTE_CONST_NTC_Num_CurrentMeas1) || (RTE_CONST_NTC_Num_CurrentMeas1 != 84u)
#   error "Enumeration constant <NTC_Num_CurrentMeas1> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_CurrentMeas1 (84u)
#  define NTC_Num_CurrentMeas1 ((NTCNumber)84u)
# endif
# if (defined RTE_CONST_NTC_Num_CurrentMeas2) || (defined NTC_Num_CurrentMeas2)
#  if (!defined RTE_CONST_NTC_Num_CurrentMeas2) || (RTE_CONST_NTC_Num_CurrentMeas2 != 85u)
#   error "Enumeration constant <NTC_Num_CurrentMeas2> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_CurrentMeas2 (85u)
#  define NTC_Num_CurrentMeas2 ((NTCNumber)85u)
# endif
# if (defined RTE_CONST_NTC_Num_CurrentMeasCrossChk) || (defined NTC_Num_CurrentMeasCrossChk)
#  if (!defined RTE_CONST_NTC_Num_CurrentMeasCrossChk) || (RTE_CONST_NTC_Num_CurrentMeasCrossChk != 86u)
#   error "Enumeration constant <NTC_Num_CurrentMeasCrossChk> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_CurrentMeasCrossChk (86u)
#  define NTC_Num_CurrentMeasCrossChk ((NTCNumber)86u)
# endif
# if (defined RTE_CONST_NTC_Num_PDSupplyOverVoltage) || (defined NTC_Num_PDSupplyOverVoltage)
#  if (!defined RTE_CONST_NTC_Num_PDSupplyOverVoltage) || (RTE_CONST_NTC_Num_PDSupplyOverVoltage != 87u)
#   error "Enumeration constant <NTC_Num_PDSupplyOverVoltage> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_PDSupplyOverVoltage (87u)
#  define NTC_Num_PDSupplyOverVoltage ((NTCNumber)87u)
# endif
# if (defined RTE_CONST_NTC_Num_ChargePumpUnderVoltage) || (defined NTC_Num_ChargePumpUnderVoltage)
#  if (!defined RTE_CONST_NTC_Num_ChargePumpUnderVoltage) || (RTE_CONST_NTC_Num_ChargePumpUnderVoltage != 88u)
#   error "Enumeration constant <NTC_Num_ChargePumpUnderVoltage> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_ChargePumpUnderVoltage (88u)
#  define NTC_Num_ChargePumpUnderVoltage ((NTCNumber)88u)
# endif
# if (defined RTE_CONST_NTC_Num_Inv2GateDrvFltInProcess) || (defined NTC_Num_Inv2GateDrvFltInProcess)
#  if (!defined RTE_CONST_NTC_Num_Inv2GateDrvFltInProcess) || (RTE_CONST_NTC_Num_Inv2GateDrvFltInProcess != 92u)
#   error "Enumeration constant <NTC_Num_Inv2GateDrvFltInProcess> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_Inv2GateDrvFltInProcess (92u)
#  define NTC_Num_Inv2GateDrvFltInProcess ((NTCNumber)92u)
# endif
# if (defined RTE_CONST_NTC_Num_Inv2GateDrvFlt) || (defined NTC_Num_Inv2GateDrvFlt)
#  if (!defined RTE_CONST_NTC_Num_Inv2GateDrvFlt) || (RTE_CONST_NTC_Num_Inv2GateDrvFlt != 93u)
#   error "Enumeration constant <NTC_Num_Inv2GateDrvFlt> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_Inv2GateDrvFlt (93u)
#  define NTC_Num_Inv2GateDrvFlt ((NTCNumber)93u)
# endif
# if (defined RTE_CONST_NTC_Num_Inv2OnStateSingleFET) || (defined NTC_Num_Inv2OnStateSingleFET)
#  if (!defined RTE_CONST_NTC_Num_Inv2OnStateSingleFET) || (RTE_CONST_NTC_Num_Inv2OnStateSingleFET != 94u)
#   error "Enumeration constant <NTC_Num_Inv2OnStateSingleFET> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_Inv2OnStateSingleFET (94u)
#  define NTC_Num_Inv2OnStateSingleFET ((NTCNumber)94u)
# endif
# if (defined RTE_CONST_NTC_Num_HwTrqSensor) || (defined NTC_Num_HwTrqSensor)
#  if (!defined RTE_CONST_NTC_Num_HwTrqSensor) || (RTE_CONST_NTC_Num_HwTrqSensor != 96u)
#   error "Enumeration constant <NTC_Num_HwTrqSensor> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_HwTrqSensor (96u)
#  define NTC_Num_HwTrqSensor ((NTCNumber)96u)
# endif
# if (defined RTE_CONST_NTC_Num_AnaVsDigHwTrq) || (defined NTC_Num_AnaVsDigHwTrq)
#  if (!defined RTE_CONST_NTC_Num_AnaVsDigHwTrq) || (RTE_CONST_NTC_Num_AnaVsDigHwTrq != 97u)
#   error "Enumeration constant <NTC_Num_AnaVsDigHwTrq> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_AnaVsDigHwTrq (97u)
#  define NTC_Num_AnaVsDigHwTrq ((NTCNumber)97u)
# endif
# if (defined RTE_CONST_NTC_Num_TrqSensorRecoveryFlt) || (defined NTC_Num_TrqSensorRecoveryFlt)
#  if (!defined RTE_CONST_NTC_Num_TrqSensorRecoveryFlt) || (RTE_CONST_NTC_Num_TrqSensorRecoveryFlt != 98u)
#   error "Enumeration constant <NTC_Num_TrqSensorRecoveryFlt> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_TrqSensorRecoveryFlt (98u)
#  define NTC_Num_TrqSensorRecoveryFlt ((NTCNumber)98u)
# endif
# if (defined RTE_CONST_NTC_Num_TrqSensorScaleInvalid) || (defined NTC_Num_TrqSensorScaleInvalid)
#  if (!defined RTE_CONST_NTC_Num_TrqSensorScaleInvalid) || (RTE_CONST_NTC_Num_TrqSensorScaleInvalid != 100u)
#   error "Enumeration constant <NTC_Num_TrqSensorScaleInvalid> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_TrqSensorScaleInvalid (100u)
#  define NTC_Num_TrqSensorScaleInvalid ((NTCNumber)100u)
# endif
# if (defined RTE_CONST_NTC_Num_T1vsT2) || (defined NTC_Num_T1vsT2)
#  if (!defined RTE_CONST_NTC_Num_T1vsT2) || (RTE_CONST_NTC_Num_T1vsT2 != 101u)
#   error "Enumeration constant <NTC_Num_T1vsT2> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_T1vsT2 (101u)
#  define NTC_Num_T1vsT2 ((NTCNumber)101u)
# endif
# if (defined RTE_CONST_NTC_Num_T1OutofRange) || (defined NTC_Num_T1OutofRange)
#  if (!defined RTE_CONST_NTC_Num_T1OutofRange) || (RTE_CONST_NTC_Num_T1OutofRange != 102u)
#   error "Enumeration constant <NTC_Num_T1OutofRange> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_T1OutofRange (102u)
#  define NTC_Num_T1OutofRange ((NTCNumber)102u)
# endif
# if (defined RTE_CONST_NTC_Num_T2OutofRange) || (defined NTC_Num_T2OutofRange)
#  if (!defined RTE_CONST_NTC_Num_T2OutofRange) || (RTE_CONST_NTC_Num_T2OutofRange != 103u)
#   error "Enumeration constant <NTC_Num_T2OutofRange> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_T2OutofRange (103u)
#  define NTC_Num_T2OutofRange ((NTCNumber)103u)
# endif
# if (defined RTE_CONST_NTC_Num_DigT1vsT2) || (defined NTC_Num_DigT1vsT2)
#  if (!defined RTE_CONST_NTC_Num_DigT1vsT2) || (RTE_CONST_NTC_Num_DigT1vsT2 != 104u)
#   error "Enumeration constant <NTC_Num_DigT1vsT2> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DigT1vsT2 (104u)
#  define NTC_Num_DigT1vsT2 ((NTCNumber)104u)
# endif
# if (defined RTE_CONST_NTC_Num_DigT1OutofRange) || (defined NTC_Num_DigT1OutofRange)
#  if (!defined RTE_CONST_NTC_Num_DigT1OutofRange) || (RTE_CONST_NTC_Num_DigT1OutofRange != 105u)
#   error "Enumeration constant <NTC_Num_DigT1OutofRange> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DigT1OutofRange (105u)
#  define NTC_Num_DigT1OutofRange ((NTCNumber)105u)
# endif
# if (defined RTE_CONST_NTC_Num_DigT2OutofRange) || (defined NTC_Num_DigT2OutofRange)
#  if (!defined RTE_CONST_NTC_Num_DigT2OutofRange) || (RTE_CONST_NTC_Num_DigT2OutofRange != 106u)
#   error "Enumeration constant <NTC_Num_DigT2OutofRange> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DigT2OutofRange (106u)
#  define NTC_Num_DigT2OutofRange ((NTCNumber)106u)
# endif
# if (defined RTE_CONST_NTC_Num_RedT1vsT2) || (defined NTC_Num_RedT1vsT2)
#  if (!defined RTE_CONST_NTC_Num_RedT1vsT2) || (RTE_CONST_NTC_Num_RedT1vsT2 != 107u)
#   error "Enumeration constant <NTC_Num_RedT1vsT2> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_RedT1vsT2 (107u)
#  define NTC_Num_RedT1vsT2 ((NTCNumber)107u)
# endif
# if (defined RTE_CONST_NTC_Num_HWACrossChecks) || (defined NTC_Num_HWACrossChecks)
#  if (!defined RTE_CONST_NTC_Num_HWACrossChecks) || (RTE_CONST_NTC_Num_HWACrossChecks != 108u)
#   error "Enumeration constant <NTC_Num_HWACrossChecks> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_HWACrossChecks (108u)
#  define NTC_Num_HWACrossChecks ((NTCNumber)108u)
# endif
# if (defined RTE_CONST_NTC_Num_HWASnsrCommFault) || (defined NTC_Num_HWASnsrCommFault)
#  if (!defined RTE_CONST_NTC_Num_HWASnsrCommFault) || (RTE_CONST_NTC_Num_HWASnsrCommFault != 109u)
#   error "Enumeration constant <NTC_Num_HWASnsrCommFault> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_HWASnsrCommFault (109u)
#  define NTC_Num_HWASnsrCommFault ((NTCNumber)109u)
# endif
# if (defined RTE_CONST_NTC_Num_HWASensorRel) || (defined NTC_Num_HWASensorRel)
#  if (!defined RTE_CONST_NTC_Num_HWASensorRel) || (RTE_CONST_NTC_Num_HWASensorRel != 110u)
#   error "Enumeration constant <NTC_Num_HWASensorRel> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_HWASensorRel (110u)
#  define NTC_Num_HWASensorRel ((NTCNumber)110u)
# endif
# if (defined RTE_CONST_NTC_Num_HWASensorAbs) || (defined NTC_Num_HWASensorAbs)
#  if (!defined RTE_CONST_NTC_Num_HWASensorAbs) || (RTE_CONST_NTC_Num_HWASensorAbs != 111u)
#   error "Enumeration constant <NTC_Num_HWASensorAbs> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_HWASensorAbs (111u)
#  define NTC_Num_HWASensorAbs ((NTCNumber)111u)
# endif
# if (defined RTE_CONST_NTC_Num_PriMSB_SinCosCorr) || (defined NTC_Num_PriMSB_SinCosCorr)
#  if (!defined RTE_CONST_NTC_Num_PriMSB_SinCosCorr) || (RTE_CONST_NTC_Num_PriMSB_SinCosCorr != 112u)
#   error "Enumeration constant <NTC_Num_PriMSB_SinCosCorr> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_PriMSB_SinCosCorr (112u)
#  define NTC_Num_PriMSB_SinCosCorr ((NTCNumber)112u)
# endif
# if (defined RTE_CONST_NTC_Num_SecMSB_SinCosCorr) || (defined NTC_Num_SecMSB_SinCosCorr)
#  if (!defined RTE_CONST_NTC_Num_SecMSB_SinCosCorr) || (RTE_CONST_NTC_Num_SecMSB_SinCosCorr != 113u)
#   error "Enumeration constant <NTC_Num_SecMSB_SinCosCorr> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_SecMSB_SinCosCorr (113u)
#  define NTC_Num_SecMSB_SinCosCorr ((NTCNumber)113u)
# endif
# if (defined RTE_CONST_NTC_Num_PriVsSec_SinCosCorr) || (defined NTC_Num_PriVsSec_SinCosCorr)
#  if (!defined RTE_CONST_NTC_Num_PriVsSec_SinCosCorr) || (RTE_CONST_NTC_Num_PriVsSec_SinCosCorr != 114u)
#   error "Enumeration constant <NTC_Num_PriVsSec_SinCosCorr> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_PriVsSec_SinCosCorr (114u)
#  define NTC_Num_PriVsSec_SinCosCorr ((NTCNumber)114u)
# endif
# if (defined RTE_CONST_NTC_Num_DigMSBFlt) || (defined NTC_Num_DigMSBFlt)
#  if (!defined RTE_CONST_NTC_Num_DigMSBFlt) || (RTE_CONST_NTC_Num_DigMSBFlt != 115u)
#   error "Enumeration constant <NTC_Num_DigMSBFlt> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DigMSBFlt (115u)
#  define NTC_Num_DigMSBFlt ((NTCNumber)115u)
# endif
# if (defined RTE_CONST_NTC_Num_MtrVelFlt) || (defined NTC_Num_MtrVelFlt)
#  if (!defined RTE_CONST_NTC_Num_MtrVelFlt) || (RTE_CONST_NTC_Num_MtrVelFlt != 116u)
#   error "Enumeration constant <NTC_Num_MtrVelFlt> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_MtrVelFlt (116u)
#  define NTC_Num_MtrVelFlt ((NTCNumber)116u)
# endif
# if (defined RTE_CONST_NTC_Num_HWAtoMtrAngleCorr) || (defined NTC_Num_HWAtoMtrAngleCorr)
#  if (!defined RTE_CONST_NTC_Num_HWAtoMtrAngleCorr) || (RTE_CONST_NTC_Num_HWAtoMtrAngleCorr != 117u)
#   error "Enumeration constant <NTC_Num_HWAtoMtrAngleCorr> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_HWAtoMtrAngleCorr (117u)
#  define NTC_Num_HWAtoMtrAngleCorr ((NTCNumber)117u)
# endif
# if (defined RTE_CONST_NTC_Num_RedPriVsSec_SinCosCorr) || (defined NTC_Num_RedPriVsSec_SinCosCorr)
#  if (!defined RTE_CONST_NTC_Num_RedPriVsSec_SinCosCorr) || (RTE_CONST_NTC_Num_RedPriVsSec_SinCosCorr != 118u)
#   error "Enumeration constant <NTC_Num_RedPriVsSec_SinCosCorr> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_RedPriVsSec_SinCosCorr (118u)
#  define NTC_Num_RedPriVsSec_SinCosCorr ((NTCNumber)118u)
# endif
# if (defined RTE_CONST_NTC_Num_TurnCntr_PosLoss) || (defined NTC_Num_TurnCntr_PosLoss)
#  if (!defined RTE_CONST_NTC_Num_TurnCntr_PosLoss) || (RTE_CONST_NTC_Num_TurnCntr_PosLoss != 128u)
#   error "Enumeration constant <NTC_Num_TurnCntr_PosLoss> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_TurnCntr_PosLoss (128u)
#  define NTC_Num_TurnCntr_PosLoss ((NTCNumber)128u)
# endif
# if (defined RTE_CONST_NTC_Num_TurnCntr_MicroProcFlt) || (defined NTC_Num_TurnCntr_MicroProcFlt)
#  if (!defined RTE_CONST_NTC_Num_TurnCntr_MicroProcFlt) || (RTE_CONST_NTC_Num_TurnCntr_MicroProcFlt != 129u)
#   error "Enumeration constant <NTC_Num_TurnCntr_MicroProcFlt> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_TurnCntr_MicroProcFlt (129u)
#  define NTC_Num_TurnCntr_MicroProcFlt ((NTCNumber)129u)
# endif
# if (defined RTE_CONST_NTC_Num_TurnCntr_SensorPosFlt) || (defined NTC_Num_TurnCntr_SensorPosFlt)
#  if (!defined RTE_CONST_NTC_Num_TurnCntr_SensorPosFlt) || (RTE_CONST_NTC_Num_TurnCntr_SensorPosFlt != 130u)
#   error "Enumeration constant <NTC_Num_TurnCntr_SensorPosFlt> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_TurnCntr_SensorPosFlt (130u)
#  define NTC_Num_TurnCntr_SensorPosFlt ((NTCNumber)130u)
# endif
# if (defined RTE_CONST_NTC_Num_TurnCntr_SpiComFlt) || (defined NTC_Num_TurnCntr_SpiComFlt)
#  if (!defined RTE_CONST_NTC_Num_TurnCntr_SpiComFlt) || (RTE_CONST_NTC_Num_TurnCntr_SpiComFlt != 131u)
#   error "Enumeration constant <NTC_Num_TurnCntr_SpiComFlt> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_TurnCntr_SpiComFlt (131u)
#  define NTC_Num_TurnCntr_SpiComFlt ((NTCNumber)131u)
# endif
# if (defined RTE_CONST_NTC_Num_TurnCntr_HighQuiescCur) || (defined NTC_Num_TurnCntr_HighQuiescCur)
#  if (!defined RTE_CONST_NTC_Num_TurnCntr_HighQuiescCur) || (RTE_CONST_NTC_Num_TurnCntr_HighQuiescCur != 132u)
#   error "Enumeration constant <NTC_Num_TurnCntr_HighQuiescCur> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_TurnCntr_HighQuiescCur (132u)
#  define NTC_Num_TurnCntr_HighQuiescCur ((NTCNumber)132u)
# endif
# if (defined RTE_CONST_NTC_Num_TurnCntr_MainResets) || (defined NTC_Num_TurnCntr_MainResets)
#  if (!defined RTE_CONST_NTC_Num_TurnCntr_MainResets) || (RTE_CONST_NTC_Num_TurnCntr_MainResets != 133u)
#   error "Enumeration constant <NTC_Num_TurnCntr_MainResets> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_TurnCntr_MainResets (133u)
#  define NTC_Num_TurnCntr_MainResets ((NTCNumber)133u)
# endif
# if (defined RTE_CONST_NTC_Num_TurnCntr_PosLossNotSpdDep) || (defined NTC_Num_TurnCntr_PosLossNotSpdDep)
#  if (!defined RTE_CONST_NTC_Num_TurnCntr_PosLossNotSpdDep) || (RTE_CONST_NTC_Num_TurnCntr_PosLossNotSpdDep != 134u)
#   error "Enumeration constant <NTC_Num_TurnCntr_PosLossNotSpdDep> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_TurnCntr_PosLossNotSpdDep (134u)
#  define NTC_Num_TurnCntr_PosLossNotSpdDep ((NTCNumber)134u)
# endif
# if (defined RTE_CONST_NTC_Num_KinematicIntDiag) || (defined NTC_Num_KinematicIntDiag)
#  if (!defined RTE_CONST_NTC_Num_KinematicIntDiag) || (RTE_CONST_NTC_Num_KinematicIntDiag != 144u)
#   error "Enumeration constant <NTC_Num_KinematicIntDiag> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_KinematicIntDiag (144u)
#  define NTC_Num_KinematicIntDiag ((NTCNumber)144u)
# endif
# if (defined RTE_CONST_NTC_Num_HighFriction) || (defined NTC_Num_HighFriction)
#  if (!defined RTE_CONST_NTC_Num_HighFriction) || (RTE_CONST_NTC_Num_HighFriction != 145u)
#   error "Enumeration constant <NTC_Num_HighFriction> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_HighFriction (145u)
#  define NTC_Num_HighFriction ((NTCNumber)145u)
# endif
# if (defined RTE_CONST_NTC_Num_DutyCycleExceeded) || (defined NTC_Num_DutyCycleExceeded)
#  if (!defined RTE_CONST_NTC_Num_DutyCycleExceeded) || (RTE_CONST_NTC_Num_DutyCycleExceeded != 148u)
#   error "Enumeration constant <NTC_Num_DutyCycleExceeded> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DutyCycleExceeded (148u)
#  define NTC_Num_DutyCycleExceeded ((NTCNumber)148u)
# endif
# if (defined RTE_CONST_NTC_Num_AbsTempThermLimit) || (defined NTC_Num_AbsTempThermLimit)
#  if (!defined RTE_CONST_NTC_Num_AbsTempThermLimit) || (RTE_CONST_NTC_Num_AbsTempThermLimit != 149u)
#   error "Enumeration constant <NTC_Num_AbsTempThermLimit> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_AbsTempThermLimit (149u)
#  define NTC_Num_AbsTempThermLimit ((NTCNumber)149u)
# endif
# if (defined RTE_CONST_NTC_Num_LatchActive) || (defined NTC_Num_LatchActive)
#  if (!defined RTE_CONST_NTC_Num_LatchActive) || (RTE_CONST_NTC_Num_LatchActive != 160u)
#   error "Enumeration constant <NTC_Num_LatchActive> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_LatchActive (160u)
#  define NTC_Num_LatchActive ((NTCNumber)160u)
# endif
# if (defined RTE_CONST_NTC_Num_OpTrqVsHwTrq) || (defined NTC_Num_OpTrqVsHwTrq)
#  if (!defined RTE_CONST_NTC_Num_OpTrqVsHwTrq) || (RTE_CONST_NTC_Num_OpTrqVsHwTrq != 168u)
#   error "Enumeration constant <NTC_Num_OpTrqVsHwTrq> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_OpTrqVsHwTrq (168u)
#  define NTC_Num_OpTrqVsHwTrq ((NTCNumber)168u)
# endif
# if (defined RTE_CONST_NTC_Num_CurrentReas) || (defined NTC_Num_CurrentReas)
#  if (!defined RTE_CONST_NTC_Num_CurrentReas) || (RTE_CONST_NTC_Num_CurrentReas != 169u)
#   error "Enumeration constant <NTC_Num_CurrentReas> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_CurrentReas (169u)
#  define NTC_Num_CurrentReas ((NTCNumber)169u)
# endif
# if (defined RTE_CONST_NTC_Num_LoaRpdShutdn) || (defined NTC_Num_LoaRpdShutdn)
#  if (!defined RTE_CONST_NTC_Num_LoaRpdShutdn) || (RTE_CONST_NTC_Num_LoaRpdShutdn != 170u)
#   error "Enumeration constant <NTC_Num_LoaRpdShutdn> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_LoaRpdShutdn (170u)
#  define NTC_Num_LoaRpdShutdn ((NTCNumber)170u)
# endif
# if (defined RTE_CONST_NTC_Num_LoaCtrldShutdn) || (defined NTC_Num_LoaCtrldShutdn)
#  if (!defined RTE_CONST_NTC_Num_LoaCtrldShutdn) || (RTE_CONST_NTC_Num_LoaCtrldShutdn != 171u)
#   error "Enumeration constant <NTC_Num_LoaCtrldShutdn> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_LoaCtrldShutdn (171u)
#  define NTC_Num_LoaCtrldShutdn ((NTCNumber)171u)
# endif
# if (defined RTE_CONST_NTC_Num_LoaMgr_HwTqIdptSigTooLow) || (defined NTC_Num_LoaMgr_HwTqIdptSigTooLow)
#  if (!defined RTE_CONST_NTC_Num_LoaMgr_HwTqIdptSigTooLow) || (RTE_CONST_NTC_Num_LoaMgr_HwTqIdptSigTooLow != 172u)
#   error "Enumeration constant <NTC_Num_LoaMgr_HwTqIdptSigTooLow> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_LoaMgr_HwTqIdptSigTooLow (172u)
#  define NTC_Num_LoaMgr_HwTqIdptSigTooLow ((NTCNumber)172u)
# endif
# if (defined RTE_CONST_NTC_Num_LoaMgr_MotAgIdptSigTooLow) || (defined NTC_Num_LoaMgr_MotAgIdptSigTooLow)
#  if (!defined RTE_CONST_NTC_Num_LoaMgr_MotAgIdptSigTooLow) || (RTE_CONST_NTC_Num_LoaMgr_MotAgIdptSigTooLow != 173u)
#   error "Enumeration constant <NTC_Num_LoaMgr_MotAgIdptSigTooLow> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_LoaMgr_MotAgIdptSigTooLow (173u)
#  define NTC_Num_LoaMgr_MotAgIdptSigTooLow ((NTCNumber)173u)
# endif
# if (defined RTE_CONST_NTC_Num_LoaMgr_MotCurrIdptSigTooLow) || (defined NTC_Num_LoaMgr_MotCurrIdptSigTooLow)
#  if (!defined RTE_CONST_NTC_Num_LoaMgr_MotCurrIdptSigTooLow) || (RTE_CONST_NTC_Num_LoaMgr_MotCurrIdptSigTooLow != 174u)
#   error "Enumeration constant <NTC_Num_LoaMgr_MotCurrIdptSigTooLow> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_LoaMgr_MotCurrIdptSigTooLow (174u)
#  define NTC_Num_LoaMgr_MotCurrIdptSigTooLow ((NTCNumber)174u)
# endif
# if (defined RTE_CONST_NTC_Num_LoaMgr_IvtrIdptSigTooLow) || (defined NTC_Num_LoaMgr_IvtrIdptSigTooLow)
#  if (!defined RTE_CONST_NTC_Num_LoaMgr_IvtrIdptSigTooLow) || (RTE_CONST_NTC_Num_LoaMgr_IvtrIdptSigTooLow != 175u)
#   error "Enumeration constant <NTC_Num_LoaMgr_IvtrIdptSigTooLow> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_LoaMgr_IvtrIdptSigTooLow (175u)
#  define NTC_Num_LoaMgr_IvtrIdptSigTooLow ((NTCNumber)175u)
# endif
# if (defined RTE_CONST_NTC_Num_OpVoltage) || (defined NTC_Num_OpVoltage)
#  if (!defined RTE_CONST_NTC_Num_OpVoltage) || (RTE_CONST_NTC_Num_OpVoltage != 176u)
#   error "Enumeration constant <NTC_Num_OpVoltage> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_OpVoltage (176u)
#  define NTC_Num_OpVoltage ((NTCNumber)176u)
# endif
# if (defined RTE_CONST_NTC_Num_ExVoltageLow) || (defined NTC_Num_ExVoltageLow)
#  if (!defined RTE_CONST_NTC_Num_ExVoltageLow) || (RTE_CONST_NTC_Num_ExVoltageLow != 177u)
#   error "Enumeration constant <NTC_Num_ExVoltageLow> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_ExVoltageLow (177u)
#  define NTC_Num_ExVoltageLow ((NTCNumber)177u)
# endif
# if (defined RTE_CONST_NTC_Num_ReducedAsstLowVoltage) || (defined NTC_Num_ReducedAsstLowVoltage)
#  if (!defined RTE_CONST_NTC_Num_ReducedAsstLowVoltage) || (RTE_CONST_NTC_Num_ReducedAsstLowVoltage != 178u)
#   error "Enumeration constant <NTC_Num_ReducedAsstLowVoltage> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_ReducedAsstLowVoltage (178u)
#  define NTC_Num_ReducedAsstLowVoltage ((NTCNumber)178u)
# endif
# if (defined RTE_CONST_NTC_Num_ExVoltageHigh) || (defined NTC_Num_ExVoltageHigh)
#  if (!defined RTE_CONST_NTC_Num_ExVoltageHigh) || (RTE_CONST_NTC_Num_ExVoltageHigh != 180u)
#   error "Enumeration constant <NTC_Num_ExVoltageHigh> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_ExVoltageHigh (180u)
#  define NTC_Num_ExVoltageHigh ((NTCNumber)180u)
# endif
# if (defined RTE_CONST_NTC_Num_OpVoltageOvrMax) || (defined NTC_Num_OpVoltageOvrMax)
#  if (!defined RTE_CONST_NTC_Num_OpVoltageOvrMax) || (RTE_CONST_NTC_Num_OpVoltageOvrMax != 181u)
#   error "Enumeration constant <NTC_Num_OpVoltageOvrMax> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_OpVoltageOvrMax (181u)
#  define NTC_Num_OpVoltageOvrMax ((NTCNumber)181u)
# endif
# if (defined RTE_CONST_NTC_Num_BattTransOverVolt) || (defined NTC_Num_BattTransOverVolt)
#  if (!defined RTE_CONST_NTC_Num_BattTransOverVolt) || (RTE_CONST_NTC_Num_BattTransOverVolt != 182u)
#   error "Enumeration constant <NTC_Num_BattTransOverVolt> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_BattTransOverVolt (182u)
#  define NTC_Num_BattTransOverVolt ((NTCNumber)182u)
# endif
# if (defined RTE_CONST_NTC_Num_IgnConfDiag) || (defined NTC_Num_IgnConfDiag)
#  if (!defined RTE_CONST_NTC_Num_IgnConfDiag) || (RTE_CONST_NTC_Num_IgnConfDiag != 184u)
#   error "Enumeration constant <NTC_Num_IgnConfDiag> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_IgnConfDiag (184u)
#  define NTC_Num_IgnConfDiag ((NTCNumber)184u)
# endif
# if (defined RTE_CONST_NTC_Num_TurnCntr_LowBattery) || (defined NTC_Num_TurnCntr_LowBattery)
#  if (!defined RTE_CONST_NTC_Num_TurnCntr_LowBattery) || (RTE_CONST_NTC_Num_TurnCntr_LowBattery != 185u)
#   error "Enumeration constant <NTC_Num_TurnCntr_LowBattery> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_TurnCntr_LowBattery (185u)
#  define NTC_Num_TurnCntr_LowBattery ((NTCNumber)185u)
# endif
# if (defined RTE_CONST_NTC_Num_EEPROMCloseFailed) || (defined NTC_Num_EEPROMCloseFailed)
#  if (!defined RTE_CONST_NTC_Num_EEPROMCloseFailed) || (RTE_CONST_NTC_Num_EEPROMCloseFailed != 191u)
#   error "Enumeration constant <NTC_Num_EEPROMCloseFailed> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_EEPROMCloseFailed (191u)
#  define NTC_Num_EEPROMCloseFailed ((NTCNumber)191u)
# endif
# if (defined RTE_CONST_NTC_Num_SigPath1CrossChk) || (defined NTC_Num_SigPath1CrossChk)
#  if (!defined RTE_CONST_NTC_Num_SigPath1CrossChk) || (RTE_CONST_NTC_Num_SigPath1CrossChk != 192u)
#   error "Enumeration constant <NTC_Num_SigPath1CrossChk> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_SigPath1CrossChk (192u)
#  define NTC_Num_SigPath1CrossChk ((NTCNumber)192u)
# endif
# if (defined RTE_CONST_NTC_Num_SigPath2CrossChk) || (defined NTC_Num_SigPath2CrossChk)
#  if (!defined RTE_CONST_NTC_Num_SigPath2CrossChk) || (RTE_CONST_NTC_Num_SigPath2CrossChk != 193u)
#   error "Enumeration constant <NTC_Num_SigPath2CrossChk> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_SigPath2CrossChk (193u)
#  define NTC_Num_SigPath2CrossChk ((NTCNumber)193u)
# endif
# if (defined RTE_CONST_NTC_Num_SigPath3CrossChk) || (defined NTC_Num_SigPath3CrossChk)
#  if (!defined RTE_CONST_NTC_Num_SigPath3CrossChk) || (RTE_CONST_NTC_Num_SigPath3CrossChk != 194u)
#   error "Enumeration constant <NTC_Num_SigPath3CrossChk> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_SigPath3CrossChk (194u)
#  define NTC_Num_SigPath3CrossChk ((NTCNumber)194u)
# endif
# if (defined RTE_CONST_NTC_Num_SigPath4CrossChk) || (defined NTC_Num_SigPath4CrossChk)
#  if (!defined RTE_CONST_NTC_Num_SigPath4CrossChk) || (RTE_CONST_NTC_Num_SigPath4CrossChk != 195u)
#   error "Enumeration constant <NTC_Num_SigPath4CrossChk> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_SigPath4CrossChk (195u)
#  define NTC_Num_SigPath4CrossChk ((NTCNumber)195u)
# endif
# if (defined RTE_CONST_NTC_Num_SigPath5CrossChk) || (defined NTC_Num_SigPath5CrossChk)
#  if (!defined RTE_CONST_NTC_Num_SigPath5CrossChk) || (RTE_CONST_NTC_Num_SigPath5CrossChk != 196u)
#   error "Enumeration constant <NTC_Num_SigPath5CrossChk> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_SigPath5CrossChk (196u)
#  define NTC_Num_SigPath5CrossChk ((NTCNumber)196u)
# endif
# if (defined RTE_CONST_NTC_Num_DampingFWReached) || (defined NTC_Num_DampingFWReached)
#  if (!defined RTE_CONST_NTC_Num_DampingFWReached) || (RTE_CONST_NTC_Num_DampingFWReached != 197u)
#   error "Enumeration constant <NTC_Num_DampingFWReached> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DampingFWReached (197u)
#  define NTC_Num_DampingFWReached ((NTCNumber)197u)
# endif
# if (defined RTE_CONST_NTC_Num_AssistFWReached) || (defined NTC_Num_AssistFWReached)
#  if (!defined RTE_CONST_NTC_Num_AssistFWReached) || (RTE_CONST_NTC_Num_AssistFWReached != 198u)
#   error "Enumeration constant <NTC_Num_AssistFWReached> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_AssistFWReached (198u)
#  define NTC_Num_AssistFWReached ((NTCNumber)198u)
# endif
# if (defined RTE_CONST_NTC_Num_ReturnFWReached) || (defined NTC_Num_ReturnFWReached)
#  if (!defined RTE_CONST_NTC_Num_ReturnFWReached) || (RTE_CONST_NTC_Num_ReturnFWReached != 199u)
#   error "Enumeration constant <NTC_Num_ReturnFWReached> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_ReturnFWReached (199u)
#  define NTC_Num_ReturnFWReached ((NTCNumber)199u)
# endif
# if (defined RTE_CONST_NTC_Num_DampingFWFltMode) || (defined NTC_Num_DampingFWFltMode)
#  if (!defined RTE_CONST_NTC_Num_DampingFWFltMode) || (RTE_CONST_NTC_Num_DampingFWFltMode != 200u)
#   error "Enumeration constant <NTC_Num_DampingFWFltMode> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DampingFWFltMode (200u)
#  define NTC_Num_DampingFWFltMode ((NTCNumber)200u)
# endif
# if (defined RTE_CONST_NTC_Num_AssistFWFltMode) || (defined NTC_Num_AssistFWFltMode)
#  if (!defined RTE_CONST_NTC_Num_AssistFWFltMode) || (RTE_CONST_NTC_Num_AssistFWFltMode != 201u)
#   error "Enumeration constant <NTC_Num_AssistFWFltMode> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_AssistFWFltMode (201u)
#  define NTC_Num_AssistFWFltMode ((NTCNumber)201u)
# endif
# if (defined RTE_CONST_NTC_Num_VBICFltMode) || (defined NTC_Num_VBICFltMode)
#  if (!defined RTE_CONST_NTC_Num_VBICFltMode) || (RTE_CONST_NTC_Num_VBICFltMode != 202u)
#   error "Enumeration constant <NTC_Num_VBICFltMode> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_VBICFltMode (202u)
#  define NTC_Num_VBICFltMode ((NTCNumber)202u)
# endif
# if (defined RTE_CONST_NTC_Num_StaMdsSysC) || (defined NTC_Num_StaMdsSysC)
#  if (!defined RTE_CONST_NTC_Num_StaMdsSysC) || (RTE_CONST_NTC_Num_StaMdsSysC != 203u)
#   error "Enumeration constant <NTC_Num_StaMdsSysC> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_StaMdsSysC (203u)
#  define NTC_Num_StaMdsSysC ((NTCNumber)203u)
# endif
# if (defined RTE_CONST_NTC_NUM_SysFailureForRotVel) || (defined NTC_NUM_SysFailureForRotVel)
#  if (!defined RTE_CONST_NTC_NUM_SysFailureForRotVel) || (RTE_CONST_NTC_NUM_SysFailureForRotVel != 204u)
#   error "Enumeration constant <NTC_NUM_SysFailureForRotVel> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_NUM_SysFailureForRotVel (204u)
#  define NTC_NUM_SysFailureForRotVel ((NTCNumber)204u)
# endif
# if (defined RTE_CONST_NTC_NUM_SysFailForRedntRotVel) || (defined NTC_NUM_SysFailForRedntRotVel)
#  if (!defined RTE_CONST_NTC_NUM_SysFailForRedntRotVel) || (RTE_CONST_NTC_NUM_SysFailForRedntRotVel != 205u)
#   error "Enumeration constant <NTC_NUM_SysFailForRedntRotVel> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_NUM_SysFailForRedntRotVel (205u)
#  define NTC_NUM_SysFailForRedntRotVel ((NTCNumber)205u)
# endif
# if (defined RTE_CONST_NTC_Num_SysFailureForTrqSnsr) || (defined NTC_Num_SysFailureForTrqSnsr)
#  if (!defined RTE_CONST_NTC_Num_SysFailureForTrqSnsr) || (RTE_CONST_NTC_Num_SysFailureForTrqSnsr != 206u)
#   error "Enumeration constant <NTC_Num_SysFailureForTrqSnsr> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_SysFailureForTrqSnsr (206u)
#  define NTC_Num_SysFailureForTrqSnsr ((NTCNumber)206u)
# endif
# if (defined RTE_CONST_NTC_Num_SysFailureForRedTrqSnsr) || (defined NTC_Num_SysFailureForRedTrqSnsr)
#  if (!defined RTE_CONST_NTC_Num_SysFailureForRedTrqSnsr) || (RTE_CONST_NTC_Num_SysFailureForRedTrqSnsr != 207u)
#   error "Enumeration constant <NTC_Num_SysFailureForRedTrqSnsr> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_SysFailureForRedTrqSnsr (207u)
#  define NTC_Num_SysFailureForRedTrqSnsr ((NTCNumber)207u)
# endif
# if (defined RTE_CONST_NTC_NUM_SysFailureForCtrlVolt) || (defined NTC_NUM_SysFailureForCtrlVolt)
#  if (!defined RTE_CONST_NTC_NUM_SysFailureForCtrlVolt) || (RTE_CONST_NTC_NUM_SysFailureForCtrlVolt != 209u)
#   error "Enumeration constant <NTC_NUM_SysFailureForCtrlVolt> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_NUM_SysFailureForCtrlVolt (209u)
#  define NTC_NUM_SysFailureForCtrlVolt ((NTCNumber)209u)
# endif
# if (defined RTE_CONST_NTC_Num_GlblSgnlOvrwrtDet) || (defined NTC_Num_GlblSgnlOvrwrtDet)
#  if (!defined RTE_CONST_NTC_Num_GlblSgnlOvrwrtDet) || (RTE_CONST_NTC_Num_GlblSgnlOvrwrtDet != 223u)
#   error "Enumeration constant <NTC_Num_GlblSgnlOvrwrtDet> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_GlblSgnlOvrwrtDet (223u)
#  define NTC_Num_GlblSgnlOvrwrtDet ((NTCNumber)223u)
# endif
# if (defined RTE_CONST_NTC_Num_VLF_00) || (defined NTC_Num_VLF_00)
#  if (!defined RTE_CONST_NTC_Num_VLF_00) || (RTE_CONST_NTC_Num_VLF_00 != 224u)
#   error "Enumeration constant <NTC_Num_VLF_00> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_VLF_00 (224u)
#  define NTC_Num_VLF_00 ((NTCNumber)224u)
# endif
# if (defined RTE_CONST_NTC_Num_VLF_01) || (defined NTC_Num_VLF_01)
#  if (!defined RTE_CONST_NTC_Num_VLF_01) || (RTE_CONST_NTC_Num_VLF_01 != 225u)
#   error "Enumeration constant <NTC_Num_VLF_01> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_VLF_01 (225u)
#  define NTC_Num_VLF_01 ((NTCNumber)225u)
# endif
# if (defined RTE_CONST_NTC_Num_VLF_02) || (defined NTC_Num_VLF_02)
#  if (!defined RTE_CONST_NTC_Num_VLF_02) || (RTE_CONST_NTC_Num_VLF_02 != 226u)
#   error "Enumeration constant <NTC_Num_VLF_02> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_VLF_02 (226u)
#  define NTC_Num_VLF_02 ((NTCNumber)226u)
# endif
# if (defined RTE_CONST_NTC_Num_VLF_03) || (defined NTC_Num_VLF_03)
#  if (!defined RTE_CONST_NTC_Num_VLF_03) || (RTE_CONST_NTC_Num_VLF_03 != 227u)
#   error "Enumeration constant <NTC_Num_VLF_03> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_VLF_03 (227u)
#  define NTC_Num_VLF_03 ((NTCNumber)227u)
# endif
# if (defined RTE_CONST_NTC_Num_VLF_04) || (defined NTC_Num_VLF_04)
#  if (!defined RTE_CONST_NTC_Num_VLF_04) || (RTE_CONST_NTC_Num_VLF_04 != 228u)
#   error "Enumeration constant <NTC_Num_VLF_04> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_VLF_04 (228u)
#  define NTC_Num_VLF_04 ((NTCNumber)228u)
# endif
# if (defined RTE_CONST_NTC_Num_VLF_05) || (defined NTC_Num_VLF_05)
#  if (!defined RTE_CONST_NTC_Num_VLF_05) || (RTE_CONST_NTC_Num_VLF_05 != 229u)
#   error "Enumeration constant <NTC_Num_VLF_05> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_VLF_05 (229u)
#  define NTC_Num_VLF_05 ((NTCNumber)229u)
# endif
# if (defined RTE_CONST_NTC_Num_VLF_06) || (defined NTC_Num_VLF_06)
#  if (!defined RTE_CONST_NTC_Num_VLF_06) || (RTE_CONST_NTC_Num_VLF_06 != 230u)
#   error "Enumeration constant <NTC_Num_VLF_06> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_VLF_06 (230u)
#  define NTC_Num_VLF_06 ((NTCNumber)230u)
# endif
# if (defined RTE_CONST_NTC_Num_VLF_07) || (defined NTC_Num_VLF_07)
#  if (!defined RTE_CONST_NTC_Num_VLF_07) || (RTE_CONST_NTC_Num_VLF_07 != 231u)
#   error "Enumeration constant <NTC_Num_VLF_07> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_VLF_07 (231u)
#  define NTC_Num_VLF_07 ((NTCNumber)231u)
# endif
# if (defined RTE_CONST_NTC_Num_VLF_08) || (defined NTC_Num_VLF_08)
#  if (!defined RTE_CONST_NTC_Num_VLF_08) || (RTE_CONST_NTC_Num_VLF_08 != 232u)
#   error "Enumeration constant <NTC_Num_VLF_08> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_VLF_08 (232u)
#  define NTC_Num_VLF_08 ((NTCNumber)232u)
# endif
# if (defined RTE_CONST_NTC_Num_VLF_09) || (defined NTC_Num_VLF_09)
#  if (!defined RTE_CONST_NTC_Num_VLF_09) || (RTE_CONST_NTC_Num_VLF_09 != 233u)
#   error "Enumeration constant <NTC_Num_VLF_09> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_VLF_09 (233u)
#  define NTC_Num_VLF_09 ((NTCNumber)233u)
# endif
# if (defined RTE_CONST_NTC_Num_VLF_10) || (defined NTC_Num_VLF_10)
#  if (!defined RTE_CONST_NTC_Num_VLF_10) || (RTE_CONST_NTC_Num_VLF_10 != 234u)
#   error "Enumeration constant <NTC_Num_VLF_10> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_VLF_10 (234u)
#  define NTC_Num_VLF_10 ((NTCNumber)234u)
# endif
# if (defined RTE_CONST_NTC_Num_VLF_11) || (defined NTC_Num_VLF_11)
#  if (!defined RTE_CONST_NTC_Num_VLF_11) || (RTE_CONST_NTC_Num_VLF_11 != 235u)
#   error "Enumeration constant <NTC_Num_VLF_11> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_VLF_11 (235u)
#  define NTC_Num_VLF_11 ((NTCNumber)235u)
# endif
# if (defined RTE_CONST_NTC_Num_VLF_12) || (defined NTC_Num_VLF_12)
#  if (!defined RTE_CONST_NTC_Num_VLF_12) || (RTE_CONST_NTC_Num_VLF_12 != 236u)
#   error "Enumeration constant <NTC_Num_VLF_12> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_VLF_12 (236u)
#  define NTC_Num_VLF_12 ((NTCNumber)236u)
# endif
# if (defined RTE_CONST_NTC_Num_VLF_13) || (defined NTC_Num_VLF_13)
#  if (!defined RTE_CONST_NTC_Num_VLF_13) || (RTE_CONST_NTC_Num_VLF_13 != 237u)
#   error "Enumeration constant <NTC_Num_VLF_13> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_VLF_13 (237u)
#  define NTC_Num_VLF_13 ((NTCNumber)237u)
# endif
# if (defined RTE_CONST_NTC_Num_VLF_14) || (defined NTC_Num_VLF_14)
#  if (!defined RTE_CONST_NTC_Num_VLF_14) || (RTE_CONST_NTC_Num_VLF_14 != 238u)
#   error "Enumeration constant <NTC_Num_VLF_14> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_VLF_14 (238u)
#  define NTC_Num_VLF_14 ((NTCNumber)238u)
# endif
# if (defined RTE_CONST_NTC_Num_VLF_15) || (defined NTC_Num_VLF_15)
#  if (!defined RTE_CONST_NTC_Num_VLF_15) || (RTE_CONST_NTC_Num_VLF_15 != 239u)
#   error "Enumeration constant <NTC_Num_VLF_15> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_VLF_15 (239u)
#  define NTC_Num_VLF_15 ((NTCNumber)239u)
# endif
# if (defined RTE_CONST_NTC_Num_VLF_16) || (defined NTC_Num_VLF_16)
#  if (!defined RTE_CONST_NTC_Num_VLF_16) || (RTE_CONST_NTC_Num_VLF_16 != 240u)
#   error "Enumeration constant <NTC_Num_VLF_16> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_VLF_16 (240u)
#  define NTC_Num_VLF_16 ((NTCNumber)240u)
# endif
# if (defined RTE_CONST_NTC_Num_VLF_17) || (defined NTC_Num_VLF_17)
#  if (!defined RTE_CONST_NTC_Num_VLF_17) || (RTE_CONST_NTC_Num_VLF_17 != 241u)
#   error "Enumeration constant <NTC_Num_VLF_17> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_VLF_17 (241u)
#  define NTC_Num_VLF_17 ((NTCNumber)241u)
# endif
# if (defined RTE_CONST_NTC_Num_VLF_18) || (defined NTC_Num_VLF_18)
#  if (!defined RTE_CONST_NTC_Num_VLF_18) || (RTE_CONST_NTC_Num_VLF_18 != 242u)
#   error "Enumeration constant <NTC_Num_VLF_18> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_VLF_18 (242u)
#  define NTC_Num_VLF_18 ((NTCNumber)242u)
# endif
# if (defined RTE_CONST_NTC_Num_VLF_19) || (defined NTC_Num_VLF_19)
#  if (!defined RTE_CONST_NTC_Num_VLF_19) || (RTE_CONST_NTC_Num_VLF_19 != 243u)
#   error "Enumeration constant <NTC_Num_VLF_19> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_VLF_19 (243u)
#  define NTC_Num_VLF_19 ((NTCNumber)243u)
# endif
# if (defined RTE_CONST_NTC_Num_VLF_20) || (defined NTC_Num_VLF_20)
#  if (!defined RTE_CONST_NTC_Num_VLF_20) || (RTE_CONST_NTC_Num_VLF_20 != 244u)
#   error "Enumeration constant <NTC_Num_VLF_20> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_VLF_20 (244u)
#  define NTC_Num_VLF_20 ((NTCNumber)244u)
# endif
# if (defined RTE_CONST_NTC_Num_VLF_21) || (defined NTC_Num_VLF_21)
#  if (!defined RTE_CONST_NTC_Num_VLF_21) || (RTE_CONST_NTC_Num_VLF_21 != 245u)
#   error "Enumeration constant <NTC_Num_VLF_21> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_VLF_21 (245u)
#  define NTC_Num_VLF_21 ((NTCNumber)245u)
# endif
# if (defined RTE_CONST_NTC_Num_VLF_22) || (defined NTC_Num_VLF_22)
#  if (!defined RTE_CONST_NTC_Num_VLF_22) || (RTE_CONST_NTC_Num_VLF_22 != 246u)
#   error "Enumeration constant <NTC_Num_VLF_22> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_VLF_22 (246u)
#  define NTC_Num_VLF_22 ((NTCNumber)246u)
# endif
# if (defined RTE_CONST_NTC_Num_VLF_23) || (defined NTC_Num_VLF_23)
#  if (!defined RTE_CONST_NTC_Num_VLF_23) || (RTE_CONST_NTC_Num_VLF_23 != 247u)
#   error "Enumeration constant <NTC_Num_VLF_23> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_VLF_23 (247u)
#  define NTC_Num_VLF_23 ((NTCNumber)247u)
# endif
# if (defined RTE_CONST_NTC_Num_VLF_24) || (defined NTC_Num_VLF_24)
#  if (!defined RTE_CONST_NTC_Num_VLF_24) || (RTE_CONST_NTC_Num_VLF_24 != 248u)
#   error "Enumeration constant <NTC_Num_VLF_24> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_VLF_24 (248u)
#  define NTC_Num_VLF_24 ((NTCNumber)248u)
# endif
# if (defined RTE_CONST_NTC_Num_VLF_25) || (defined NTC_Num_VLF_25)
#  if (!defined RTE_CONST_NTC_Num_VLF_25) || (RTE_CONST_NTC_Num_VLF_25 != 249u)
#   error "Enumeration constant <NTC_Num_VLF_25> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_VLF_25 (249u)
#  define NTC_Num_VLF_25 ((NTCNumber)249u)
# endif
# if (defined RTE_CONST_NTC_Num_VLF_26) || (defined NTC_Num_VLF_26)
#  if (!defined RTE_CONST_NTC_Num_VLF_26) || (RTE_CONST_NTC_Num_VLF_26 != 250u)
#   error "Enumeration constant <NTC_Num_VLF_26> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_VLF_26 (250u)
#  define NTC_Num_VLF_26 ((NTCNumber)250u)
# endif
# if (defined RTE_CONST_NTC_Num_VLF_27) || (defined NTC_Num_VLF_27)
#  if (!defined RTE_CONST_NTC_Num_VLF_27) || (RTE_CONST_NTC_Num_VLF_27 != 251u)
#   error "Enumeration constant <NTC_Num_VLF_27> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_VLF_27 (251u)
#  define NTC_Num_VLF_27 ((NTCNumber)251u)
# endif
# if (defined RTE_CONST_NTC_Num_VLF_28) || (defined NTC_Num_VLF_28)
#  if (!defined RTE_CONST_NTC_Num_VLF_28) || (RTE_CONST_NTC_Num_VLF_28 != 252u)
#   error "Enumeration constant <NTC_Num_VLF_28> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_VLF_28 (252u)
#  define NTC_Num_VLF_28 ((NTCNumber)252u)
# endif
# if (defined RTE_CONST_NTC_Num_VLF_29) || (defined NTC_Num_VLF_29)
#  if (!defined RTE_CONST_NTC_Num_VLF_29) || (RTE_CONST_NTC_Num_VLF_29 != 253u)
#   error "Enumeration constant <NTC_Num_VLF_29> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_VLF_29 (253u)
#  define NTC_Num_VLF_29 ((NTCNumber)253u)
# endif
# if (defined RTE_CONST_NTC_Num_VLF_30) || (defined NTC_Num_VLF_30)
#  if (!defined RTE_CONST_NTC_Num_VLF_30) || (RTE_CONST_NTC_Num_VLF_30 != 254u)
#   error "Enumeration constant <NTC_Num_VLF_30> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_VLF_30 (254u)
#  define NTC_Num_VLF_30 ((NTCNumber)254u)
# endif
# if (defined RTE_CONST_NTC_Num_VLF_31) || (defined NTC_Num_VLF_31)
#  if (!defined RTE_CONST_NTC_Num_VLF_31) || (RTE_CONST_NTC_Num_VLF_31 != 255u)
#   error "Enumeration constant <NTC_Num_VLF_31> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_VLF_31 (255u)
#  define NTC_Num_VLF_31 ((NTCNumber)255u)
# endif
# if (defined RTE_CONST_NTC_Num_BusOffCh1) || (defined NTC_Num_BusOffCh1)
#  if (!defined RTE_CONST_NTC_Num_BusOffCh1) || (RTE_CONST_NTC_Num_BusOffCh1 != 256u)
#   error "Enumeration constant <NTC_Num_BusOffCh1> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_BusOffCh1 (256u)
#  define NTC_Num_BusOffCh1 ((NTCNumber)256u)
# endif
# if (defined RTE_CONST_NTC_Num_BusOffCh1NodeMute) || (defined NTC_Num_BusOffCh1NodeMute)
#  if (!defined RTE_CONST_NTC_Num_BusOffCh1NodeMute) || (RTE_CONST_NTC_Num_BusOffCh1NodeMute != 257u)
#   error "Enumeration constant <NTC_Num_BusOffCh1NodeMute> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_BusOffCh1NodeMute (257u)
#  define NTC_Num_BusOffCh1NodeMute ((NTCNumber)257u)
# endif
# if (defined RTE_CONST_NTC_Num_Node1AAbsent) || (defined NTC_Num_Node1AAbsent)
#  if (!defined RTE_CONST_NTC_Num_Node1AAbsent) || (RTE_CONST_NTC_Num_Node1AAbsent != 258u)
#   error "Enumeration constant <NTC_Num_Node1AAbsent> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_Node1AAbsent (258u)
#  define NTC_Num_Node1AAbsent ((NTCNumber)258u)
# endif
# if (defined RTE_CONST_NTC_Num_Node1AFaulty) || (defined NTC_Num_Node1AFaulty)
#  if (!defined RTE_CONST_NTC_Num_Node1AFaulty) || (RTE_CONST_NTC_Num_Node1AFaulty != 259u)
#   error "Enumeration constant <NTC_Num_Node1AFaulty> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_Node1AFaulty (259u)
#  define NTC_Num_Node1AFaulty ((NTCNumber)259u)
# endif
# if (defined RTE_CONST_NTC_Num_Node1BAbsent) || (defined NTC_Num_Node1BAbsent)
#  if (!defined RTE_CONST_NTC_Num_Node1BAbsent) || (RTE_CONST_NTC_Num_Node1BAbsent != 260u)
#   error "Enumeration constant <NTC_Num_Node1BAbsent> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_Node1BAbsent (260u)
#  define NTC_Num_Node1BAbsent ((NTCNumber)260u)
# endif
# if (defined RTE_CONST_NTC_Num_Node1BFaulty) || (defined NTC_Num_Node1BFaulty)
#  if (!defined RTE_CONST_NTC_Num_Node1BFaulty) || (RTE_CONST_NTC_Num_Node1BFaulty != 261u)
#   error "Enumeration constant <NTC_Num_Node1BFaulty> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_Node1BFaulty (261u)
#  define NTC_Num_Node1BFaulty ((NTCNumber)261u)
# endif
# if (defined RTE_CONST_NTC_Num_Node1CAbsent) || (defined NTC_Num_Node1CAbsent)
#  if (!defined RTE_CONST_NTC_Num_Node1CAbsent) || (RTE_CONST_NTC_Num_Node1CAbsent != 262u)
#   error "Enumeration constant <NTC_Num_Node1CAbsent> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_Node1CAbsent (262u)
#  define NTC_Num_Node1CAbsent ((NTCNumber)262u)
# endif
# if (defined RTE_CONST_NTC_Num_Node1CFaulty) || (defined NTC_Num_Node1CFaulty)
#  if (!defined RTE_CONST_NTC_Num_Node1CFaulty) || (RTE_CONST_NTC_Num_Node1CFaulty != 263u)
#   error "Enumeration constant <NTC_Num_Node1CFaulty> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_Node1CFaulty (263u)
#  define NTC_Num_Node1CFaulty ((NTCNumber)263u)
# endif
# if (defined RTE_CONST_NTC_Num_Node1DAbsent) || (defined NTC_Num_Node1DAbsent)
#  if (!defined RTE_CONST_NTC_Num_Node1DAbsent) || (RTE_CONST_NTC_Num_Node1DAbsent != 264u)
#   error "Enumeration constant <NTC_Num_Node1DAbsent> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_Node1DAbsent (264u)
#  define NTC_Num_Node1DAbsent ((NTCNumber)264u)
# endif
# if (defined RTE_CONST_NTC_Num_Node1DFaulty) || (defined NTC_Num_Node1DFaulty)
#  if (!defined RTE_CONST_NTC_Num_Node1DFaulty) || (RTE_CONST_NTC_Num_Node1DFaulty != 265u)
#   error "Enumeration constant <NTC_Num_Node1DFaulty> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_Node1DFaulty (265u)
#  define NTC_Num_Node1DFaulty ((NTCNumber)265u)
# endif
# if (defined RTE_CONST_NTC_Num_Node1EAbsent) || (defined NTC_Num_Node1EAbsent)
#  if (!defined RTE_CONST_NTC_Num_Node1EAbsent) || (RTE_CONST_NTC_Num_Node1EAbsent != 266u)
#   error "Enumeration constant <NTC_Num_Node1EAbsent> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_Node1EAbsent (266u)
#  define NTC_Num_Node1EAbsent ((NTCNumber)266u)
# endif
# if (defined RTE_CONST_NTC_Num_Node1EFaulty) || (defined NTC_Num_Node1EFaulty)
#  if (!defined RTE_CONST_NTC_Num_Node1EFaulty) || (RTE_CONST_NTC_Num_Node1EFaulty != 267u)
#   error "Enumeration constant <NTC_Num_Node1EFaulty> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_Node1EFaulty (267u)
#  define NTC_Num_Node1EFaulty ((NTCNumber)267u)
# endif
# if (defined RTE_CONST_NTC_Num_Node1FAbsent) || (defined NTC_Num_Node1FAbsent)
#  if (!defined RTE_CONST_NTC_Num_Node1FAbsent) || (RTE_CONST_NTC_Num_Node1FAbsent != 268u)
#   error "Enumeration constant <NTC_Num_Node1FAbsent> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_Node1FAbsent (268u)
#  define NTC_Num_Node1FAbsent ((NTCNumber)268u)
# endif
# if (defined RTE_CONST_NTC_Num_Node1FFaulty) || (defined NTC_Num_Node1FFaulty)
#  if (!defined RTE_CONST_NTC_Num_Node1FFaulty) || (RTE_CONST_NTC_Num_Node1FFaulty != 269u)
#   error "Enumeration constant <NTC_Num_Node1FFaulty> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_Node1FFaulty (269u)
#  define NTC_Num_Node1FFaulty ((NTCNumber)269u)
# endif
# if (defined RTE_CONST_NTC_Num_Node1GAbsent) || (defined NTC_Num_Node1GAbsent)
#  if (!defined RTE_CONST_NTC_Num_Node1GAbsent) || (RTE_CONST_NTC_Num_Node1GAbsent != 270u)
#   error "Enumeration constant <NTC_Num_Node1GAbsent> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_Node1GAbsent (270u)
#  define NTC_Num_Node1GAbsent ((NTCNumber)270u)
# endif
# if (defined RTE_CONST_NTC_Num_Node1GFaulty) || (defined NTC_Num_Node1GFaulty)
#  if (!defined RTE_CONST_NTC_Num_Node1GFaulty) || (RTE_CONST_NTC_Num_Node1GFaulty != 271u)
#   error "Enumeration constant <NTC_Num_Node1GFaulty> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_Node1GFaulty (271u)
#  define NTC_Num_Node1GFaulty ((NTCNumber)271u)
# endif
# if (defined RTE_CONST_NTC_Num_BusOffCh2) || (defined NTC_Num_BusOffCh2)
#  if (!defined RTE_CONST_NTC_Num_BusOffCh2) || (RTE_CONST_NTC_Num_BusOffCh2 != 272u)
#   error "Enumeration constant <NTC_Num_BusOffCh2> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_BusOffCh2 (272u)
#  define NTC_Num_BusOffCh2 ((NTCNumber)272u)
# endif
# if (defined RTE_CONST_NTC_Num_Node2AAbsent) || (defined NTC_Num_Node2AAbsent)
#  if (!defined RTE_CONST_NTC_Num_Node2AAbsent) || (RTE_CONST_NTC_Num_Node2AAbsent != 273u)
#   error "Enumeration constant <NTC_Num_Node2AAbsent> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_Node2AAbsent (273u)
#  define NTC_Num_Node2AAbsent ((NTCNumber)273u)
# endif
# if (defined RTE_CONST_NTC_Num_Node2AFaulty) || (defined NTC_Num_Node2AFaulty)
#  if (!defined RTE_CONST_NTC_Num_Node2AFaulty) || (RTE_CONST_NTC_Num_Node2AFaulty != 274u)
#   error "Enumeration constant <NTC_Num_Node2AFaulty> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_Node2AFaulty (274u)
#  define NTC_Num_Node2AFaulty ((NTCNumber)274u)
# endif
# if (defined RTE_CONST_NTC_Num_Node2BAbsent) || (defined NTC_Num_Node2BAbsent)
#  if (!defined RTE_CONST_NTC_Num_Node2BAbsent) || (RTE_CONST_NTC_Num_Node2BAbsent != 275u)
#   error "Enumeration constant <NTC_Num_Node2BAbsent> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_Node2BAbsent (275u)
#  define NTC_Num_Node2BAbsent ((NTCNumber)275u)
# endif
# if (defined RTE_CONST_NTC_Num_Node2BFaulty) || (defined NTC_Num_Node2BFaulty)
#  if (!defined RTE_CONST_NTC_Num_Node2BFaulty) || (RTE_CONST_NTC_Num_Node2BFaulty != 276u)
#   error "Enumeration constant <NTC_Num_Node2BFaulty> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_Node2BFaulty (276u)
#  define NTC_Num_Node2BFaulty ((NTCNumber)276u)
# endif
# if (defined RTE_CONST_NTC_Num_Node2CAbsent) || (defined NTC_Num_Node2CAbsent)
#  if (!defined RTE_CONST_NTC_Num_Node2CAbsent) || (RTE_CONST_NTC_Num_Node2CAbsent != 277u)
#   error "Enumeration constant <NTC_Num_Node2CAbsent> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_Node2CAbsent (277u)
#  define NTC_Num_Node2CAbsent ((NTCNumber)277u)
# endif
# if (defined RTE_CONST_NTC_Num_Node2CFaulty) || (defined NTC_Num_Node2CFaulty)
#  if (!defined RTE_CONST_NTC_Num_Node2CFaulty) || (RTE_CONST_NTC_Num_Node2CFaulty != 278u)
#   error "Enumeration constant <NTC_Num_Node2CFaulty> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_Node2CFaulty (278u)
#  define NTC_Num_Node2CFaulty ((NTCNumber)278u)
# endif
# if (defined RTE_CONST_NTC_Num_Node2DAbsent) || (defined NTC_Num_Node2DAbsent)
#  if (!defined RTE_CONST_NTC_Num_Node2DAbsent) || (RTE_CONST_NTC_Num_Node2DAbsent != 279u)
#   error "Enumeration constant <NTC_Num_Node2DAbsent> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_Node2DAbsent (279u)
#  define NTC_Num_Node2DAbsent ((NTCNumber)279u)
# endif
# if (defined RTE_CONST_NTC_Num_Node2DFaulty) || (defined NTC_Num_Node2DFaulty)
#  if (!defined RTE_CONST_NTC_Num_Node2DFaulty) || (RTE_CONST_NTC_Num_Node2DFaulty != 280u)
#   error "Enumeration constant <NTC_Num_Node2DFaulty> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_Node2DFaulty (280u)
#  define NTC_Num_Node2DFaulty ((NTCNumber)280u)
# endif
# if (defined RTE_CONST_NTC_Num_Node2EAbsent) || (defined NTC_Num_Node2EAbsent)
#  if (!defined RTE_CONST_NTC_Num_Node2EAbsent) || (RTE_CONST_NTC_Num_Node2EAbsent != 281u)
#   error "Enumeration constant <NTC_Num_Node2EAbsent> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_Node2EAbsent (281u)
#  define NTC_Num_Node2EAbsent ((NTCNumber)281u)
# endif
# if (defined RTE_CONST_NTC_Num_Node2EFaulty) || (defined NTC_Num_Node2EFaulty)
#  if (!defined RTE_CONST_NTC_Num_Node2EFaulty) || (RTE_CONST_NTC_Num_Node2EFaulty != 282u)
#   error "Enumeration constant <NTC_Num_Node2EFaulty> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_Node2EFaulty (282u)
#  define NTC_Num_Node2EFaulty ((NTCNumber)282u)
# endif
# if (defined RTE_CONST_NTC_Num_Node2FAbsent) || (defined NTC_Num_Node2FAbsent)
#  if (!defined RTE_CONST_NTC_Num_Node2FAbsent) || (RTE_CONST_NTC_Num_Node2FAbsent != 283u)
#   error "Enumeration constant <NTC_Num_Node2FAbsent> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_Node2FAbsent (283u)
#  define NTC_Num_Node2FAbsent ((NTCNumber)283u)
# endif
# if (defined RTE_CONST_NTC_Num_Node2FFaulty) || (defined NTC_Num_Node2FFaulty)
#  if (!defined RTE_CONST_NTC_Num_Node2FFaulty) || (RTE_CONST_NTC_Num_Node2FFaulty != 284u)
#   error "Enumeration constant <NTC_Num_Node2FFaulty> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_Node2FFaulty (284u)
#  define NTC_Num_Node2FFaulty ((NTCNumber)284u)
# endif
# if (defined RTE_CONST_NTC_Num_Node2GAbsent) || (defined NTC_Num_Node2GAbsent)
#  if (!defined RTE_CONST_NTC_Num_Node2GAbsent) || (RTE_CONST_NTC_Num_Node2GAbsent != 285u)
#   error "Enumeration constant <NTC_Num_Node2GAbsent> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_Node2GAbsent (285u)
#  define NTC_Num_Node2GAbsent ((NTCNumber)285u)
# endif
# if (defined RTE_CONST_NTC_Num_Node2GFaulty) || (defined NTC_Num_Node2GFaulty)
#  if (!defined RTE_CONST_NTC_Num_Node2GFaulty) || (RTE_CONST_NTC_Num_Node2GFaulty != 286u)
#   error "Enumeration constant <NTC_Num_Node2GFaulty> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_Node2GFaulty (286u)
#  define NTC_Num_Node2GFaulty ((NTCNumber)286u)
# endif
# if (defined RTE_CONST_NTC_Num_InvalidMsg_M) || (defined NTC_Num_InvalidMsg_M)
#  if (!defined RTE_CONST_NTC_Num_InvalidMsg_M) || (RTE_CONST_NTC_Num_InvalidMsg_M != 288u)
#   error "Enumeration constant <NTC_Num_InvalidMsg_M> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_InvalidMsg_M (288u)
#  define NTC_Num_InvalidMsg_M ((NTCNumber)288u)
# endif
# if (defined RTE_CONST_NTC_Num_MissingMsg_M) || (defined NTC_Num_MissingMsg_M)
#  if (!defined RTE_CONST_NTC_Num_MissingMsg_M) || (RTE_CONST_NTC_Num_MissingMsg_M != 289u)
#   error "Enumeration constant <NTC_Num_MissingMsg_M> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_MissingMsg_M (289u)
#  define NTC_Num_MissingMsg_M ((NTCNumber)289u)
# endif
# if (defined RTE_CONST_NTC_Num_CRCFltMsg_M) || (defined NTC_Num_CRCFltMsg_M)
#  if (!defined RTE_CONST_NTC_Num_CRCFltMsg_M) || (RTE_CONST_NTC_Num_CRCFltMsg_M != 290u)
#   error "Enumeration constant <NTC_Num_CRCFltMsg_M> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_CRCFltMsg_M (290u)
#  define NTC_Num_CRCFltMsg_M ((NTCNumber)290u)
# endif
# if (defined RTE_CONST_NTC_Num_PgrsCntFltMsg_M) || (defined NTC_Num_PgrsCntFltMsg_M)
#  if (!defined RTE_CONST_NTC_Num_PgrsCntFltMsg_M) || (RTE_CONST_NTC_Num_PgrsCntFltMsg_M != 291u)
#   error "Enumeration constant <NTC_Num_PgrsCntFltMsg_M> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_PgrsCntFltMsg_M (291u)
#  define NTC_Num_PgrsCntFltMsg_M ((NTCNumber)291u)
# endif
# if (defined RTE_CONST_NTC_Num_DataRngFltMsg_M) || (defined NTC_Num_DataRngFltMsg_M)
#  if (!defined RTE_CONST_NTC_Num_DataRngFltMsg_M) || (RTE_CONST_NTC_Num_DataRngFltMsg_M != 292u)
#   error "Enumeration constant <NTC_Num_DataRngFltMsg_M> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataRngFltMsg_M (292u)
#  define NTC_Num_DataRngFltMsg_M ((NTCNumber)292u)
# endif
# if (defined RTE_CONST_NTC_Num_DataRateFltMsg_M) || (defined NTC_Num_DataRateFltMsg_M)
#  if (!defined RTE_CONST_NTC_Num_DataRateFltMsg_M) || (RTE_CONST_NTC_Num_DataRateFltMsg_M != 293u)
#   error "Enumeration constant <NTC_Num_DataRateFltMsg_M> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataRateFltMsg_M (293u)
#  define NTC_Num_DataRateFltMsg_M ((NTCNumber)293u)
# endif
# if (defined RTE_CONST_NTC_Num_DataOtherFltMsg_M) || (defined NTC_Num_DataOtherFltMsg_M)
#  if (!defined RTE_CONST_NTC_Num_DataOtherFltMsg_M) || (RTE_CONST_NTC_Num_DataOtherFltMsg_M != 294u)
#   error "Enumeration constant <NTC_Num_DataOtherFltMsg_M> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataOtherFltMsg_M (294u)
#  define NTC_Num_DataOtherFltMsg_M ((NTCNumber)294u)
# endif
# if (defined RTE_CONST_NTC_Num_DataOther2FltMsg_M) || (defined NTC_Num_DataOther2FltMsg_M)
#  if (!defined RTE_CONST_NTC_Num_DataOther2FltMsg_M) || (RTE_CONST_NTC_Num_DataOther2FltMsg_M != 295u)
#   error "Enumeration constant <NTC_Num_DataOther2FltMsg_M> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataOther2FltMsg_M (295u)
#  define NTC_Num_DataOther2FltMsg_M ((NTCNumber)295u)
# endif
# if (defined RTE_CONST_NTC_Num_InvalidMsg_N) || (defined NTC_Num_InvalidMsg_N)
#  if (!defined RTE_CONST_NTC_Num_InvalidMsg_N) || (RTE_CONST_NTC_Num_InvalidMsg_N != 296u)
#   error "Enumeration constant <NTC_Num_InvalidMsg_N> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_InvalidMsg_N (296u)
#  define NTC_Num_InvalidMsg_N ((NTCNumber)296u)
# endif
# if (defined RTE_CONST_NTC_Num_MissingMsg_N) || (defined NTC_Num_MissingMsg_N)
#  if (!defined RTE_CONST_NTC_Num_MissingMsg_N) || (RTE_CONST_NTC_Num_MissingMsg_N != 297u)
#   error "Enumeration constant <NTC_Num_MissingMsg_N> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_MissingMsg_N (297u)
#  define NTC_Num_MissingMsg_N ((NTCNumber)297u)
# endif
# if (defined RTE_CONST_NTC_Num_CRCFltMsg_N) || (defined NTC_Num_CRCFltMsg_N)
#  if (!defined RTE_CONST_NTC_Num_CRCFltMsg_N) || (RTE_CONST_NTC_Num_CRCFltMsg_N != 298u)
#   error "Enumeration constant <NTC_Num_CRCFltMsg_N> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_CRCFltMsg_N (298u)
#  define NTC_Num_CRCFltMsg_N ((NTCNumber)298u)
# endif
# if (defined RTE_CONST_NTC_Num_PgrsCntFltMsg_N) || (defined NTC_Num_PgrsCntFltMsg_N)
#  if (!defined RTE_CONST_NTC_Num_PgrsCntFltMsg_N) || (RTE_CONST_NTC_Num_PgrsCntFltMsg_N != 299u)
#   error "Enumeration constant <NTC_Num_PgrsCntFltMsg_N> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_PgrsCntFltMsg_N (299u)
#  define NTC_Num_PgrsCntFltMsg_N ((NTCNumber)299u)
# endif
# if (defined RTE_CONST_NTC_Num_DataRngFltMsg_N) || (defined NTC_Num_DataRngFltMsg_N)
#  if (!defined RTE_CONST_NTC_Num_DataRngFltMsg_N) || (RTE_CONST_NTC_Num_DataRngFltMsg_N != 300u)
#   error "Enumeration constant <NTC_Num_DataRngFltMsg_N> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataRngFltMsg_N (300u)
#  define NTC_Num_DataRngFltMsg_N ((NTCNumber)300u)
# endif
# if (defined RTE_CONST_NTC_Num_DataRateFltMsg_N) || (defined NTC_Num_DataRateFltMsg_N)
#  if (!defined RTE_CONST_NTC_Num_DataRateFltMsg_N) || (RTE_CONST_NTC_Num_DataRateFltMsg_N != 301u)
#   error "Enumeration constant <NTC_Num_DataRateFltMsg_N> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataRateFltMsg_N (301u)
#  define NTC_Num_DataRateFltMsg_N ((NTCNumber)301u)
# endif
# if (defined RTE_CONST_NTC_Num_DataOtherFltMsg_N) || (defined NTC_Num_DataOtherFltMsg_N)
#  if (!defined RTE_CONST_NTC_Num_DataOtherFltMsg_N) || (RTE_CONST_NTC_Num_DataOtherFltMsg_N != 302u)
#   error "Enumeration constant <NTC_Num_DataOtherFltMsg_N> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataOtherFltMsg_N (302u)
#  define NTC_Num_DataOtherFltMsg_N ((NTCNumber)302u)
# endif
# if (defined RTE_CONST_NTC_Num_DataOtherFlt2Msg_N) || (defined NTC_Num_DataOtherFlt2Msg_N)
#  if (!defined RTE_CONST_NTC_Num_DataOtherFlt2Msg_N) || (RTE_CONST_NTC_Num_DataOtherFlt2Msg_N != 303u)
#   error "Enumeration constant <NTC_Num_DataOtherFlt2Msg_N> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataOtherFlt2Msg_N (303u)
#  define NTC_Num_DataOtherFlt2Msg_N ((NTCNumber)303u)
# endif
# if (defined RTE_CONST_NTC_Num_InvalidMsg_O) || (defined NTC_Num_InvalidMsg_O)
#  if (!defined RTE_CONST_NTC_Num_InvalidMsg_O) || (RTE_CONST_NTC_Num_InvalidMsg_O != 304u)
#   error "Enumeration constant <NTC_Num_InvalidMsg_O> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_InvalidMsg_O (304u)
#  define NTC_Num_InvalidMsg_O ((NTCNumber)304u)
# endif
# if (defined RTE_CONST_NTC_Num_MissingMsg_O) || (defined NTC_Num_MissingMsg_O)
#  if (!defined RTE_CONST_NTC_Num_MissingMsg_O) || (RTE_CONST_NTC_Num_MissingMsg_O != 305u)
#   error "Enumeration constant <NTC_Num_MissingMsg_O> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_MissingMsg_O (305u)
#  define NTC_Num_MissingMsg_O ((NTCNumber)305u)
# endif
# if (defined RTE_CONST_NTC_Num_CRCFltMsg_O) || (defined NTC_Num_CRCFltMsg_O)
#  if (!defined RTE_CONST_NTC_Num_CRCFltMsg_O) || (RTE_CONST_NTC_Num_CRCFltMsg_O != 306u)
#   error "Enumeration constant <NTC_Num_CRCFltMsg_O> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_CRCFltMsg_O (306u)
#  define NTC_Num_CRCFltMsg_O ((NTCNumber)306u)
# endif
# if (defined RTE_CONST_NTC_Num_PgrsCntFltMsg_O) || (defined NTC_Num_PgrsCntFltMsg_O)
#  if (!defined RTE_CONST_NTC_Num_PgrsCntFltMsg_O) || (RTE_CONST_NTC_Num_PgrsCntFltMsg_O != 307u)
#   error "Enumeration constant <NTC_Num_PgrsCntFltMsg_O> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_PgrsCntFltMsg_O (307u)
#  define NTC_Num_PgrsCntFltMsg_O ((NTCNumber)307u)
# endif
# if (defined RTE_CONST_NTC_Num_DataRngFltMsg_O) || (defined NTC_Num_DataRngFltMsg_O)
#  if (!defined RTE_CONST_NTC_Num_DataRngFltMsg_O) || (RTE_CONST_NTC_Num_DataRngFltMsg_O != 308u)
#   error "Enumeration constant <NTC_Num_DataRngFltMsg_O> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataRngFltMsg_O (308u)
#  define NTC_Num_DataRngFltMsg_O ((NTCNumber)308u)
# endif
# if (defined RTE_CONST_NTC_Num_DataRateFltMsg_O) || (defined NTC_Num_DataRateFltMsg_O)
#  if (!defined RTE_CONST_NTC_Num_DataRateFltMsg_O) || (RTE_CONST_NTC_Num_DataRateFltMsg_O != 309u)
#   error "Enumeration constant <NTC_Num_DataRateFltMsg_O> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataRateFltMsg_O (309u)
#  define NTC_Num_DataRateFltMsg_O ((NTCNumber)309u)
# endif
# if (defined RTE_CONST_NTC_Num_DataOtherFltMsg_O) || (defined NTC_Num_DataOtherFltMsg_O)
#  if (!defined RTE_CONST_NTC_Num_DataOtherFltMsg_O) || (RTE_CONST_NTC_Num_DataOtherFltMsg_O != 310u)
#   error "Enumeration constant <NTC_Num_DataOtherFltMsg_O> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataOtherFltMsg_O (310u)
#  define NTC_Num_DataOtherFltMsg_O ((NTCNumber)310u)
# endif
# if (defined RTE_CONST_NTC_Num_InvalidMsg_P) || (defined NTC_Num_InvalidMsg_P)
#  if (!defined RTE_CONST_NTC_Num_InvalidMsg_P) || (RTE_CONST_NTC_Num_InvalidMsg_P != 312u)
#   error "Enumeration constant <NTC_Num_InvalidMsg_P> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_InvalidMsg_P (312u)
#  define NTC_Num_InvalidMsg_P ((NTCNumber)312u)
# endif
# if (defined RTE_CONST_NTC_Num_MissingMsg_P) || (defined NTC_Num_MissingMsg_P)
#  if (!defined RTE_CONST_NTC_Num_MissingMsg_P) || (RTE_CONST_NTC_Num_MissingMsg_P != 313u)
#   error "Enumeration constant <NTC_Num_MissingMsg_P> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_MissingMsg_P (313u)
#  define NTC_Num_MissingMsg_P ((NTCNumber)313u)
# endif
# if (defined RTE_CONST_NTC_Num_CRCFltMsg_P) || (defined NTC_Num_CRCFltMsg_P)
#  if (!defined RTE_CONST_NTC_Num_CRCFltMsg_P) || (RTE_CONST_NTC_Num_CRCFltMsg_P != 314u)
#   error "Enumeration constant <NTC_Num_CRCFltMsg_P> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_CRCFltMsg_P (314u)
#  define NTC_Num_CRCFltMsg_P ((NTCNumber)314u)
# endif
# if (defined RTE_CONST_NTC_Num_PgrsCntFltMsg_P) || (defined NTC_Num_PgrsCntFltMsg_P)
#  if (!defined RTE_CONST_NTC_Num_PgrsCntFltMsg_P) || (RTE_CONST_NTC_Num_PgrsCntFltMsg_P != 315u)
#   error "Enumeration constant <NTC_Num_PgrsCntFltMsg_P> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_PgrsCntFltMsg_P (315u)
#  define NTC_Num_PgrsCntFltMsg_P ((NTCNumber)315u)
# endif
# if (defined RTE_CONST_NTC_Num_DataRngFltMsg_P) || (defined NTC_Num_DataRngFltMsg_P)
#  if (!defined RTE_CONST_NTC_Num_DataRngFltMsg_P) || (RTE_CONST_NTC_Num_DataRngFltMsg_P != 316u)
#   error "Enumeration constant <NTC_Num_DataRngFltMsg_P> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataRngFltMsg_P (316u)
#  define NTC_Num_DataRngFltMsg_P ((NTCNumber)316u)
# endif
# if (defined RTE_CONST_NTC_Num_DataRateFltMsg_P) || (defined NTC_Num_DataRateFltMsg_P)
#  if (!defined RTE_CONST_NTC_Num_DataRateFltMsg_P) || (RTE_CONST_NTC_Num_DataRateFltMsg_P != 317u)
#   error "Enumeration constant <NTC_Num_DataRateFltMsg_P> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataRateFltMsg_P (317u)
#  define NTC_Num_DataRateFltMsg_P ((NTCNumber)317u)
# endif
# if (defined RTE_CONST_NTC_Num_DataOtherFltMsg_P) || (defined NTC_Num_DataOtherFltMsg_P)
#  if (!defined RTE_CONST_NTC_Num_DataOtherFltMsg_P) || (RTE_CONST_NTC_Num_DataOtherFltMsg_P != 318u)
#   error "Enumeration constant <NTC_Num_DataOtherFltMsg_P> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataOtherFltMsg_P (318u)
#  define NTC_Num_DataOtherFltMsg_P ((NTCNumber)318u)
# endif
# if (defined RTE_CONST_NTC_Num_InvalidMsg_Q) || (defined NTC_Num_InvalidMsg_Q)
#  if (!defined RTE_CONST_NTC_Num_InvalidMsg_Q) || (RTE_CONST_NTC_Num_InvalidMsg_Q != 320u)
#   error "Enumeration constant <NTC_Num_InvalidMsg_Q> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_InvalidMsg_Q (320u)
#  define NTC_Num_InvalidMsg_Q ((NTCNumber)320u)
# endif
# if (defined RTE_CONST_NTC_Num_MissingMsg_Q) || (defined NTC_Num_MissingMsg_Q)
#  if (!defined RTE_CONST_NTC_Num_MissingMsg_Q) || (RTE_CONST_NTC_Num_MissingMsg_Q != 321u)
#   error "Enumeration constant <NTC_Num_MissingMsg_Q> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_MissingMsg_Q (321u)
#  define NTC_Num_MissingMsg_Q ((NTCNumber)321u)
# endif
# if (defined RTE_CONST_NTC_Num_CRCFltMsg_Q) || (defined NTC_Num_CRCFltMsg_Q)
#  if (!defined RTE_CONST_NTC_Num_CRCFltMsg_Q) || (RTE_CONST_NTC_Num_CRCFltMsg_Q != 322u)
#   error "Enumeration constant <NTC_Num_CRCFltMsg_Q> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_CRCFltMsg_Q (322u)
#  define NTC_Num_CRCFltMsg_Q ((NTCNumber)322u)
# endif
# if (defined RTE_CONST_NTC_Num_PgrsCntFltMsg_Q) || (defined NTC_Num_PgrsCntFltMsg_Q)
#  if (!defined RTE_CONST_NTC_Num_PgrsCntFltMsg_Q) || (RTE_CONST_NTC_Num_PgrsCntFltMsg_Q != 323u)
#   error "Enumeration constant <NTC_Num_PgrsCntFltMsg_Q> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_PgrsCntFltMsg_Q (323u)
#  define NTC_Num_PgrsCntFltMsg_Q ((NTCNumber)323u)
# endif
# if (defined RTE_CONST_NTC_Num_DataRngFltMsg_Q) || (defined NTC_Num_DataRngFltMsg_Q)
#  if (!defined RTE_CONST_NTC_Num_DataRngFltMsg_Q) || (RTE_CONST_NTC_Num_DataRngFltMsg_Q != 324u)
#   error "Enumeration constant <NTC_Num_DataRngFltMsg_Q> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataRngFltMsg_Q (324u)
#  define NTC_Num_DataRngFltMsg_Q ((NTCNumber)324u)
# endif
# if (defined RTE_CONST_NTC_Num_DataRateFltMsg_Q) || (defined NTC_Num_DataRateFltMsg_Q)
#  if (!defined RTE_CONST_NTC_Num_DataRateFltMsg_Q) || (RTE_CONST_NTC_Num_DataRateFltMsg_Q != 325u)
#   error "Enumeration constant <NTC_Num_DataRateFltMsg_Q> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataRateFltMsg_Q (325u)
#  define NTC_Num_DataRateFltMsg_Q ((NTCNumber)325u)
# endif
# if (defined RTE_CONST_NTC_Num_DataOtherFltMsg_Q) || (defined NTC_Num_DataOtherFltMsg_Q)
#  if (!defined RTE_CONST_NTC_Num_DataOtherFltMsg_Q) || (RTE_CONST_NTC_Num_DataOtherFltMsg_Q != 326u)
#   error "Enumeration constant <NTC_Num_DataOtherFltMsg_Q> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataOtherFltMsg_Q (326u)
#  define NTC_Num_DataOtherFltMsg_Q ((NTCNumber)326u)
# endif
# if (defined RTE_CONST_NTC_Num_InvalidMsg_R) || (defined NTC_Num_InvalidMsg_R)
#  if (!defined RTE_CONST_NTC_Num_InvalidMsg_R) || (RTE_CONST_NTC_Num_InvalidMsg_R != 328u)
#   error "Enumeration constant <NTC_Num_InvalidMsg_R> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_InvalidMsg_R (328u)
#  define NTC_Num_InvalidMsg_R ((NTCNumber)328u)
# endif
# if (defined RTE_CONST_NTC_Num_MissingMsg_R) || (defined NTC_Num_MissingMsg_R)
#  if (!defined RTE_CONST_NTC_Num_MissingMsg_R) || (RTE_CONST_NTC_Num_MissingMsg_R != 329u)
#   error "Enumeration constant <NTC_Num_MissingMsg_R> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_MissingMsg_R (329u)
#  define NTC_Num_MissingMsg_R ((NTCNumber)329u)
# endif
# if (defined RTE_CONST_NTC_Num_CRCFltMsg_R) || (defined NTC_Num_CRCFltMsg_R)
#  if (!defined RTE_CONST_NTC_Num_CRCFltMsg_R) || (RTE_CONST_NTC_Num_CRCFltMsg_R != 330u)
#   error "Enumeration constant <NTC_Num_CRCFltMsg_R> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_CRCFltMsg_R (330u)
#  define NTC_Num_CRCFltMsg_R ((NTCNumber)330u)
# endif
# if (defined RTE_CONST_NTC_Num_PgrsCntFltMsg_R) || (defined NTC_Num_PgrsCntFltMsg_R)
#  if (!defined RTE_CONST_NTC_Num_PgrsCntFltMsg_R) || (RTE_CONST_NTC_Num_PgrsCntFltMsg_R != 331u)
#   error "Enumeration constant <NTC_Num_PgrsCntFltMsg_R> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_PgrsCntFltMsg_R (331u)
#  define NTC_Num_PgrsCntFltMsg_R ((NTCNumber)331u)
# endif
# if (defined RTE_CONST_NTC_Num_DataRngFltMsg_R) || (defined NTC_Num_DataRngFltMsg_R)
#  if (!defined RTE_CONST_NTC_Num_DataRngFltMsg_R) || (RTE_CONST_NTC_Num_DataRngFltMsg_R != 332u)
#   error "Enumeration constant <NTC_Num_DataRngFltMsg_R> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataRngFltMsg_R (332u)
#  define NTC_Num_DataRngFltMsg_R ((NTCNumber)332u)
# endif
# if (defined RTE_CONST_NTC_Num_DataRateFltMsg_R) || (defined NTC_Num_DataRateFltMsg_R)
#  if (!defined RTE_CONST_NTC_Num_DataRateFltMsg_R) || (RTE_CONST_NTC_Num_DataRateFltMsg_R != 333u)
#   error "Enumeration constant <NTC_Num_DataRateFltMsg_R> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataRateFltMsg_R (333u)
#  define NTC_Num_DataRateFltMsg_R ((NTCNumber)333u)
# endif
# if (defined RTE_CONST_NTC_Num_DataOtherFltMsg_R) || (defined NTC_Num_DataOtherFltMsg_R)
#  if (!defined RTE_CONST_NTC_Num_DataOtherFltMsg_R) || (RTE_CONST_NTC_Num_DataOtherFltMsg_R != 334u)
#   error "Enumeration constant <NTC_Num_DataOtherFltMsg_R> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataOtherFltMsg_R (334u)
#  define NTC_Num_DataOtherFltMsg_R ((NTCNumber)334u)
# endif
# if (defined RTE_CONST_NTC_Num_DataOtherFlt2Msg_R) || (defined NTC_Num_DataOtherFlt2Msg_R)
#  if (!defined RTE_CONST_NTC_Num_DataOtherFlt2Msg_R) || (RTE_CONST_NTC_Num_DataOtherFlt2Msg_R != 335u)
#   error "Enumeration constant <NTC_Num_DataOtherFlt2Msg_R> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataOtherFlt2Msg_R (335u)
#  define NTC_Num_DataOtherFlt2Msg_R ((NTCNumber)335u)
# endif
# if (defined RTE_CONST_NTC_Num_InvalidMsg_S) || (defined NTC_Num_InvalidMsg_S)
#  if (!defined RTE_CONST_NTC_Num_InvalidMsg_S) || (RTE_CONST_NTC_Num_InvalidMsg_S != 336u)
#   error "Enumeration constant <NTC_Num_InvalidMsg_S> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_InvalidMsg_S (336u)
#  define NTC_Num_InvalidMsg_S ((NTCNumber)336u)
# endif
# if (defined RTE_CONST_NTC_Num_MissingMsg_S) || (defined NTC_Num_MissingMsg_S)
#  if (!defined RTE_CONST_NTC_Num_MissingMsg_S) || (RTE_CONST_NTC_Num_MissingMsg_S != 337u)
#   error "Enumeration constant <NTC_Num_MissingMsg_S> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_MissingMsg_S (337u)
#  define NTC_Num_MissingMsg_S ((NTCNumber)337u)
# endif
# if (defined RTE_CONST_NTC_Num_CRCFltMsg_S) || (defined NTC_Num_CRCFltMsg_S)
#  if (!defined RTE_CONST_NTC_Num_CRCFltMsg_S) || (RTE_CONST_NTC_Num_CRCFltMsg_S != 338u)
#   error "Enumeration constant <NTC_Num_CRCFltMsg_S> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_CRCFltMsg_S (338u)
#  define NTC_Num_CRCFltMsg_S ((NTCNumber)338u)
# endif
# if (defined RTE_CONST_NTC_Num_PgrsCntFltMsg_S) || (defined NTC_Num_PgrsCntFltMsg_S)
#  if (!defined RTE_CONST_NTC_Num_PgrsCntFltMsg_S) || (RTE_CONST_NTC_Num_PgrsCntFltMsg_S != 339u)
#   error "Enumeration constant <NTC_Num_PgrsCntFltMsg_S> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_PgrsCntFltMsg_S (339u)
#  define NTC_Num_PgrsCntFltMsg_S ((NTCNumber)339u)
# endif
# if (defined RTE_CONST_NTC_Num_DataRngFltMsg_S) || (defined NTC_Num_DataRngFltMsg_S)
#  if (!defined RTE_CONST_NTC_Num_DataRngFltMsg_S) || (RTE_CONST_NTC_Num_DataRngFltMsg_S != 340u)
#   error "Enumeration constant <NTC_Num_DataRngFltMsg_S> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataRngFltMsg_S (340u)
#  define NTC_Num_DataRngFltMsg_S ((NTCNumber)340u)
# endif
# if (defined RTE_CONST_NTC_Num_DataRateFltMsg_S) || (defined NTC_Num_DataRateFltMsg_S)
#  if (!defined RTE_CONST_NTC_Num_DataRateFltMsg_S) || (RTE_CONST_NTC_Num_DataRateFltMsg_S != 341u)
#   error "Enumeration constant <NTC_Num_DataRateFltMsg_S> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataRateFltMsg_S (341u)
#  define NTC_Num_DataRateFltMsg_S ((NTCNumber)341u)
# endif
# if (defined RTE_CONST_NTC_Num_DataOtherFltMsg_S) || (defined NTC_Num_DataOtherFltMsg_S)
#  if (!defined RTE_CONST_NTC_Num_DataOtherFltMsg_S) || (RTE_CONST_NTC_Num_DataOtherFltMsg_S != 342u)
#   error "Enumeration constant <NTC_Num_DataOtherFltMsg_S> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataOtherFltMsg_S (342u)
#  define NTC_Num_DataOtherFltMsg_S ((NTCNumber)342u)
# endif
# if (defined RTE_CONST_NTC_Num_InvalidMsg_T) || (defined NTC_Num_InvalidMsg_T)
#  if (!defined RTE_CONST_NTC_Num_InvalidMsg_T) || (RTE_CONST_NTC_Num_InvalidMsg_T != 344u)
#   error "Enumeration constant <NTC_Num_InvalidMsg_T> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_InvalidMsg_T (344u)
#  define NTC_Num_InvalidMsg_T ((NTCNumber)344u)
# endif
# if (defined RTE_CONST_NTC_Num_MissingMsg_T) || (defined NTC_Num_MissingMsg_T)
#  if (!defined RTE_CONST_NTC_Num_MissingMsg_T) || (RTE_CONST_NTC_Num_MissingMsg_T != 345u)
#   error "Enumeration constant <NTC_Num_MissingMsg_T> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_MissingMsg_T (345u)
#  define NTC_Num_MissingMsg_T ((NTCNumber)345u)
# endif
# if (defined RTE_CONST_NTC_Num_CRCFltMsg_T) || (defined NTC_Num_CRCFltMsg_T)
#  if (!defined RTE_CONST_NTC_Num_CRCFltMsg_T) || (RTE_CONST_NTC_Num_CRCFltMsg_T != 346u)
#   error "Enumeration constant <NTC_Num_CRCFltMsg_T> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_CRCFltMsg_T (346u)
#  define NTC_Num_CRCFltMsg_T ((NTCNumber)346u)
# endif
# if (defined RTE_CONST_NTC_Num_PgrsCntFltMsg_T) || (defined NTC_Num_PgrsCntFltMsg_T)
#  if (!defined RTE_CONST_NTC_Num_PgrsCntFltMsg_T) || (RTE_CONST_NTC_Num_PgrsCntFltMsg_T != 347u)
#   error "Enumeration constant <NTC_Num_PgrsCntFltMsg_T> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_PgrsCntFltMsg_T (347u)
#  define NTC_Num_PgrsCntFltMsg_T ((NTCNumber)347u)
# endif
# if (defined RTE_CONST_NTC_Num_DataRngFltMsg_T) || (defined NTC_Num_DataRngFltMsg_T)
#  if (!defined RTE_CONST_NTC_Num_DataRngFltMsg_T) || (RTE_CONST_NTC_Num_DataRngFltMsg_T != 348u)
#   error "Enumeration constant <NTC_Num_DataRngFltMsg_T> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataRngFltMsg_T (348u)
#  define NTC_Num_DataRngFltMsg_T ((NTCNumber)348u)
# endif
# if (defined RTE_CONST_NTC_Num_DataRateFltMsg_T) || (defined NTC_Num_DataRateFltMsg_T)
#  if (!defined RTE_CONST_NTC_Num_DataRateFltMsg_T) || (RTE_CONST_NTC_Num_DataRateFltMsg_T != 349u)
#   error "Enumeration constant <NTC_Num_DataRateFltMsg_T> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataRateFltMsg_T (349u)
#  define NTC_Num_DataRateFltMsg_T ((NTCNumber)349u)
# endif
# if (defined RTE_CONST_NTC_Num_DataOtherFltMsg_T) || (defined NTC_Num_DataOtherFltMsg_T)
#  if (!defined RTE_CONST_NTC_Num_DataOtherFltMsg_T) || (RTE_CONST_NTC_Num_DataOtherFltMsg_T != 350u)
#   error "Enumeration constant <NTC_Num_DataOtherFltMsg_T> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataOtherFltMsg_T (350u)
#  define NTC_Num_DataOtherFltMsg_T ((NTCNumber)350u)
# endif
# if (defined RTE_CONST_NTC_Num_InvalidMsg_U) || (defined NTC_Num_InvalidMsg_U)
#  if (!defined RTE_CONST_NTC_Num_InvalidMsg_U) || (RTE_CONST_NTC_Num_InvalidMsg_U != 352u)
#   error "Enumeration constant <NTC_Num_InvalidMsg_U> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_InvalidMsg_U (352u)
#  define NTC_Num_InvalidMsg_U ((NTCNumber)352u)
# endif
# if (defined RTE_CONST_NTC_Num_MissingMsg_U) || (defined NTC_Num_MissingMsg_U)
#  if (!defined RTE_CONST_NTC_Num_MissingMsg_U) || (RTE_CONST_NTC_Num_MissingMsg_U != 353u)
#   error "Enumeration constant <NTC_Num_MissingMsg_U> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_MissingMsg_U (353u)
#  define NTC_Num_MissingMsg_U ((NTCNumber)353u)
# endif
# if (defined RTE_CONST_NTC_Num_CRCFltMsg_U) || (defined NTC_Num_CRCFltMsg_U)
#  if (!defined RTE_CONST_NTC_Num_CRCFltMsg_U) || (RTE_CONST_NTC_Num_CRCFltMsg_U != 354u)
#   error "Enumeration constant <NTC_Num_CRCFltMsg_U> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_CRCFltMsg_U (354u)
#  define NTC_Num_CRCFltMsg_U ((NTCNumber)354u)
# endif
# if (defined RTE_CONST_NTC_Num_PgrsCntFltMsg_U) || (defined NTC_Num_PgrsCntFltMsg_U)
#  if (!defined RTE_CONST_NTC_Num_PgrsCntFltMsg_U) || (RTE_CONST_NTC_Num_PgrsCntFltMsg_U != 355u)
#   error "Enumeration constant <NTC_Num_PgrsCntFltMsg_U> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_PgrsCntFltMsg_U (355u)
#  define NTC_Num_PgrsCntFltMsg_U ((NTCNumber)355u)
# endif
# if (defined RTE_CONST_NTC_Num_DataRngFltMsg_U) || (defined NTC_Num_DataRngFltMsg_U)
#  if (!defined RTE_CONST_NTC_Num_DataRngFltMsg_U) || (RTE_CONST_NTC_Num_DataRngFltMsg_U != 356u)
#   error "Enumeration constant <NTC_Num_DataRngFltMsg_U> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataRngFltMsg_U (356u)
#  define NTC_Num_DataRngFltMsg_U ((NTCNumber)356u)
# endif
# if (defined RTE_CONST_NTC_Num_DataRateFltMsg_U) || (defined NTC_Num_DataRateFltMsg_U)
#  if (!defined RTE_CONST_NTC_Num_DataRateFltMsg_U) || (RTE_CONST_NTC_Num_DataRateFltMsg_U != 357u)
#   error "Enumeration constant <NTC_Num_DataRateFltMsg_U> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataRateFltMsg_U (357u)
#  define NTC_Num_DataRateFltMsg_U ((NTCNumber)357u)
# endif
# if (defined RTE_CONST_NTC_Num_DataOtherFltMsg_U) || (defined NTC_Num_DataOtherFltMsg_U)
#  if (!defined RTE_CONST_NTC_Num_DataOtherFltMsg_U) || (RTE_CONST_NTC_Num_DataOtherFltMsg_U != 358u)
#   error "Enumeration constant <NTC_Num_DataOtherFltMsg_U> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataOtherFltMsg_U (358u)
#  define NTC_Num_DataOtherFltMsg_U ((NTCNumber)358u)
# endif
# if (defined RTE_CONST_NTC_Num_InvalidMsg_V) || (defined NTC_Num_InvalidMsg_V)
#  if (!defined RTE_CONST_NTC_Num_InvalidMsg_V) || (RTE_CONST_NTC_Num_InvalidMsg_V != 360u)
#   error "Enumeration constant <NTC_Num_InvalidMsg_V> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_InvalidMsg_V (360u)
#  define NTC_Num_InvalidMsg_V ((NTCNumber)360u)
# endif
# if (defined RTE_CONST_NTC_Num_MissingMsg_V) || (defined NTC_Num_MissingMsg_V)
#  if (!defined RTE_CONST_NTC_Num_MissingMsg_V) || (RTE_CONST_NTC_Num_MissingMsg_V != 361u)
#   error "Enumeration constant <NTC_Num_MissingMsg_V> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_MissingMsg_V (361u)
#  define NTC_Num_MissingMsg_V ((NTCNumber)361u)
# endif
# if (defined RTE_CONST_NTC_Num_CRCFltMsg_V) || (defined NTC_Num_CRCFltMsg_V)
#  if (!defined RTE_CONST_NTC_Num_CRCFltMsg_V) || (RTE_CONST_NTC_Num_CRCFltMsg_V != 362u)
#   error "Enumeration constant <NTC_Num_CRCFltMsg_V> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_CRCFltMsg_V (362u)
#  define NTC_Num_CRCFltMsg_V ((NTCNumber)362u)
# endif
# if (defined RTE_CONST_NTC_Num_PgrsCntFltMsg_V) || (defined NTC_Num_PgrsCntFltMsg_V)
#  if (!defined RTE_CONST_NTC_Num_PgrsCntFltMsg_V) || (RTE_CONST_NTC_Num_PgrsCntFltMsg_V != 363u)
#   error "Enumeration constant <NTC_Num_PgrsCntFltMsg_V> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_PgrsCntFltMsg_V (363u)
#  define NTC_Num_PgrsCntFltMsg_V ((NTCNumber)363u)
# endif
# if (defined RTE_CONST_NTC_Num_DataRngFltMsg_V) || (defined NTC_Num_DataRngFltMsg_V)
#  if (!defined RTE_CONST_NTC_Num_DataRngFltMsg_V) || (RTE_CONST_NTC_Num_DataRngFltMsg_V != 364u)
#   error "Enumeration constant <NTC_Num_DataRngFltMsg_V> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataRngFltMsg_V (364u)
#  define NTC_Num_DataRngFltMsg_V ((NTCNumber)364u)
# endif
# if (defined RTE_CONST_NTC_Num_DataRateFltMsg_V) || (defined NTC_Num_DataRateFltMsg_V)
#  if (!defined RTE_CONST_NTC_Num_DataRateFltMsg_V) || (RTE_CONST_NTC_Num_DataRateFltMsg_V != 365u)
#   error "Enumeration constant <NTC_Num_DataRateFltMsg_V> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataRateFltMsg_V (365u)
#  define NTC_Num_DataRateFltMsg_V ((NTCNumber)365u)
# endif
# if (defined RTE_CONST_NTC_Num_DataOtherFltMsg_V) || (defined NTC_Num_DataOtherFltMsg_V)
#  if (!defined RTE_CONST_NTC_Num_DataOtherFltMsg_V) || (RTE_CONST_NTC_Num_DataOtherFltMsg_V != 366u)
#   error "Enumeration constant <NTC_Num_DataOtherFltMsg_V> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataOtherFltMsg_V (366u)
#  define NTC_Num_DataOtherFltMsg_V ((NTCNumber)366u)
# endif
# if (defined RTE_CONST_NTC_Num_InvalidMsg_W) || (defined NTC_Num_InvalidMsg_W)
#  if (!defined RTE_CONST_NTC_Num_InvalidMsg_W) || (RTE_CONST_NTC_Num_InvalidMsg_W != 368u)
#   error "Enumeration constant <NTC_Num_InvalidMsg_W> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_InvalidMsg_W (368u)
#  define NTC_Num_InvalidMsg_W ((NTCNumber)368u)
# endif
# if (defined RTE_CONST_NTC_Num_MissingMsg_W) || (defined NTC_Num_MissingMsg_W)
#  if (!defined RTE_CONST_NTC_Num_MissingMsg_W) || (RTE_CONST_NTC_Num_MissingMsg_W != 369u)
#   error "Enumeration constant <NTC_Num_MissingMsg_W> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_MissingMsg_W (369u)
#  define NTC_Num_MissingMsg_W ((NTCNumber)369u)
# endif
# if (defined RTE_CONST_NTC_Num_CRCFltMsg_W) || (defined NTC_Num_CRCFltMsg_W)
#  if (!defined RTE_CONST_NTC_Num_CRCFltMsg_W) || (RTE_CONST_NTC_Num_CRCFltMsg_W != 370u)
#   error "Enumeration constant <NTC_Num_CRCFltMsg_W> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_CRCFltMsg_W (370u)
#  define NTC_Num_CRCFltMsg_W ((NTCNumber)370u)
# endif
# if (defined RTE_CONST_NTC_Num_PgrsCntFltMsg_W) || (defined NTC_Num_PgrsCntFltMsg_W)
#  if (!defined RTE_CONST_NTC_Num_PgrsCntFltMsg_W) || (RTE_CONST_NTC_Num_PgrsCntFltMsg_W != 371u)
#   error "Enumeration constant <NTC_Num_PgrsCntFltMsg_W> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_PgrsCntFltMsg_W (371u)
#  define NTC_Num_PgrsCntFltMsg_W ((NTCNumber)371u)
# endif
# if (defined RTE_CONST_NTC_Num_DataRngFltMsg_W) || (defined NTC_Num_DataRngFltMsg_W)
#  if (!defined RTE_CONST_NTC_Num_DataRngFltMsg_W) || (RTE_CONST_NTC_Num_DataRngFltMsg_W != 372u)
#   error "Enumeration constant <NTC_Num_DataRngFltMsg_W> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataRngFltMsg_W (372u)
#  define NTC_Num_DataRngFltMsg_W ((NTCNumber)372u)
# endif
# if (defined RTE_CONST_NTC_Num_DataRateFltMsg_W) || (defined NTC_Num_DataRateFltMsg_W)
#  if (!defined RTE_CONST_NTC_Num_DataRateFltMsg_W) || (RTE_CONST_NTC_Num_DataRateFltMsg_W != 373u)
#   error "Enumeration constant <NTC_Num_DataRateFltMsg_W> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataRateFltMsg_W (373u)
#  define NTC_Num_DataRateFltMsg_W ((NTCNumber)373u)
# endif
# if (defined RTE_CONST_NTC_Num_DataOtherFltMsg_W) || (defined NTC_Num_DataOtherFltMsg_W)
#  if (!defined RTE_CONST_NTC_Num_DataOtherFltMsg_W) || (RTE_CONST_NTC_Num_DataOtherFltMsg_W != 374u)
#   error "Enumeration constant <NTC_Num_DataOtherFltMsg_W> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataOtherFltMsg_W (374u)
#  define NTC_Num_DataOtherFltMsg_W ((NTCNumber)374u)
# endif
# if (defined RTE_CONST_NTC_Num_InvalidMsg_X) || (defined NTC_Num_InvalidMsg_X)
#  if (!defined RTE_CONST_NTC_Num_InvalidMsg_X) || (RTE_CONST_NTC_Num_InvalidMsg_X != 376u)
#   error "Enumeration constant <NTC_Num_InvalidMsg_X> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_InvalidMsg_X (376u)
#  define NTC_Num_InvalidMsg_X ((NTCNumber)376u)
# endif
# if (defined RTE_CONST_NTC_Num_MissingMsg_X) || (defined NTC_Num_MissingMsg_X)
#  if (!defined RTE_CONST_NTC_Num_MissingMsg_X) || (RTE_CONST_NTC_Num_MissingMsg_X != 377u)
#   error "Enumeration constant <NTC_Num_MissingMsg_X> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_MissingMsg_X (377u)
#  define NTC_Num_MissingMsg_X ((NTCNumber)377u)
# endif
# if (defined RTE_CONST_NTC_Num_CRCFltMsg_X) || (defined NTC_Num_CRCFltMsg_X)
#  if (!defined RTE_CONST_NTC_Num_CRCFltMsg_X) || (RTE_CONST_NTC_Num_CRCFltMsg_X != 378u)
#   error "Enumeration constant <NTC_Num_CRCFltMsg_X> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_CRCFltMsg_X (378u)
#  define NTC_Num_CRCFltMsg_X ((NTCNumber)378u)
# endif
# if (defined RTE_CONST_NTC_Num_PgrsCntFltMsg_X) || (defined NTC_Num_PgrsCntFltMsg_X)
#  if (!defined RTE_CONST_NTC_Num_PgrsCntFltMsg_X) || (RTE_CONST_NTC_Num_PgrsCntFltMsg_X != 379u)
#   error "Enumeration constant <NTC_Num_PgrsCntFltMsg_X> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_PgrsCntFltMsg_X (379u)
#  define NTC_Num_PgrsCntFltMsg_X ((NTCNumber)379u)
# endif
# if (defined RTE_CONST_NTC_Num_DataRngFltMsg_X) || (defined NTC_Num_DataRngFltMsg_X)
#  if (!defined RTE_CONST_NTC_Num_DataRngFltMsg_X) || (RTE_CONST_NTC_Num_DataRngFltMsg_X != 380u)
#   error "Enumeration constant <NTC_Num_DataRngFltMsg_X> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataRngFltMsg_X (380u)
#  define NTC_Num_DataRngFltMsg_X ((NTCNumber)380u)
# endif
# if (defined RTE_CONST_NTC_Num_DataRateFltMsg_X) || (defined NTC_Num_DataRateFltMsg_X)
#  if (!defined RTE_CONST_NTC_Num_DataRateFltMsg_X) || (RTE_CONST_NTC_Num_DataRateFltMsg_X != 381u)
#   error "Enumeration constant <NTC_Num_DataRateFltMsg_X> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataRateFltMsg_X (381u)
#  define NTC_Num_DataRateFltMsg_X ((NTCNumber)381u)
# endif
# if (defined RTE_CONST_NTC_Num_DataOtherFltMsg_X) || (defined NTC_Num_DataOtherFltMsg_X)
#  if (!defined RTE_CONST_NTC_Num_DataOtherFltMsg_X) || (RTE_CONST_NTC_Num_DataOtherFltMsg_X != 382u)
#   error "Enumeration constant <NTC_Num_DataOtherFltMsg_X> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataOtherFltMsg_X (382u)
#  define NTC_Num_DataOtherFltMsg_X ((NTCNumber)382u)
# endif
# if (defined RTE_CONST_NTC_Num_InvalidMsg_Y) || (defined NTC_Num_InvalidMsg_Y)
#  if (!defined RTE_CONST_NTC_Num_InvalidMsg_Y) || (RTE_CONST_NTC_Num_InvalidMsg_Y != 384u)
#   error "Enumeration constant <NTC_Num_InvalidMsg_Y> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_InvalidMsg_Y (384u)
#  define NTC_Num_InvalidMsg_Y ((NTCNumber)384u)
# endif
# if (defined RTE_CONST_NTC_Num_MissingMsg_Y) || (defined NTC_Num_MissingMsg_Y)
#  if (!defined RTE_CONST_NTC_Num_MissingMsg_Y) || (RTE_CONST_NTC_Num_MissingMsg_Y != 385u)
#   error "Enumeration constant <NTC_Num_MissingMsg_Y> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_MissingMsg_Y (385u)
#  define NTC_Num_MissingMsg_Y ((NTCNumber)385u)
# endif
# if (defined RTE_CONST_NTC_Num_CRCFltMsg_Y) || (defined NTC_Num_CRCFltMsg_Y)
#  if (!defined RTE_CONST_NTC_Num_CRCFltMsg_Y) || (RTE_CONST_NTC_Num_CRCFltMsg_Y != 386u)
#   error "Enumeration constant <NTC_Num_CRCFltMsg_Y> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_CRCFltMsg_Y (386u)
#  define NTC_Num_CRCFltMsg_Y ((NTCNumber)386u)
# endif
# if (defined RTE_CONST_NTC_Num_PgrsCntFltMsg_Y) || (defined NTC_Num_PgrsCntFltMsg_Y)
#  if (!defined RTE_CONST_NTC_Num_PgrsCntFltMsg_Y) || (RTE_CONST_NTC_Num_PgrsCntFltMsg_Y != 387u)
#   error "Enumeration constant <NTC_Num_PgrsCntFltMsg_Y> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_PgrsCntFltMsg_Y (387u)
#  define NTC_Num_PgrsCntFltMsg_Y ((NTCNumber)387u)
# endif
# if (defined RTE_CONST_NTC_Num_DataRngFltMsg_Y) || (defined NTC_Num_DataRngFltMsg_Y)
#  if (!defined RTE_CONST_NTC_Num_DataRngFltMsg_Y) || (RTE_CONST_NTC_Num_DataRngFltMsg_Y != 388u)
#   error "Enumeration constant <NTC_Num_DataRngFltMsg_Y> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataRngFltMsg_Y (388u)
#  define NTC_Num_DataRngFltMsg_Y ((NTCNumber)388u)
# endif
# if (defined RTE_CONST_NTC_Num_DataRateFltMsg_Y) || (defined NTC_Num_DataRateFltMsg_Y)
#  if (!defined RTE_CONST_NTC_Num_DataRateFltMsg_Y) || (RTE_CONST_NTC_Num_DataRateFltMsg_Y != 389u)
#   error "Enumeration constant <NTC_Num_DataRateFltMsg_Y> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataRateFltMsg_Y (389u)
#  define NTC_Num_DataRateFltMsg_Y ((NTCNumber)389u)
# endif
# if (defined RTE_CONST_NTC_Num_DataOtherFltMsg_Y) || (defined NTC_Num_DataOtherFltMsg_Y)
#  if (!defined RTE_CONST_NTC_Num_DataOtherFltMsg_Y) || (RTE_CONST_NTC_Num_DataOtherFltMsg_Y != 390u)
#   error "Enumeration constant <NTC_Num_DataOtherFltMsg_Y> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataOtherFltMsg_Y (390u)
#  define NTC_Num_DataOtherFltMsg_Y ((NTCNumber)390u)
# endif
# if (defined RTE_CONST_NTC_Num_InvalidMsg_Z) || (defined NTC_Num_InvalidMsg_Z)
#  if (!defined RTE_CONST_NTC_Num_InvalidMsg_Z) || (RTE_CONST_NTC_Num_InvalidMsg_Z != 392u)
#   error "Enumeration constant <NTC_Num_InvalidMsg_Z> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_InvalidMsg_Z (392u)
#  define NTC_Num_InvalidMsg_Z ((NTCNumber)392u)
# endif
# if (defined RTE_CONST_NTC_Num_MissingMsg_Z) || (defined NTC_Num_MissingMsg_Z)
#  if (!defined RTE_CONST_NTC_Num_MissingMsg_Z) || (RTE_CONST_NTC_Num_MissingMsg_Z != 393u)
#   error "Enumeration constant <NTC_Num_MissingMsg_Z> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_MissingMsg_Z (393u)
#  define NTC_Num_MissingMsg_Z ((NTCNumber)393u)
# endif
# if (defined RTE_CONST_NTC_Num_CRCFltMsg_Z) || (defined NTC_Num_CRCFltMsg_Z)
#  if (!defined RTE_CONST_NTC_Num_CRCFltMsg_Z) || (RTE_CONST_NTC_Num_CRCFltMsg_Z != 394u)
#   error "Enumeration constant <NTC_Num_CRCFltMsg_Z> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_CRCFltMsg_Z (394u)
#  define NTC_Num_CRCFltMsg_Z ((NTCNumber)394u)
# endif
# if (defined RTE_CONST_NTC_Num_PgrsCntFltMsg_Z) || (defined NTC_Num_PgrsCntFltMsg_Z)
#  if (!defined RTE_CONST_NTC_Num_PgrsCntFltMsg_Z) || (RTE_CONST_NTC_Num_PgrsCntFltMsg_Z != 395u)
#   error "Enumeration constant <NTC_Num_PgrsCntFltMsg_Z> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_PgrsCntFltMsg_Z (395u)
#  define NTC_Num_PgrsCntFltMsg_Z ((NTCNumber)395u)
# endif
# if (defined RTE_CONST_NTC_Num_DataRngFltMsg_Z) || (defined NTC_Num_DataRngFltMsg_Z)
#  if (!defined RTE_CONST_NTC_Num_DataRngFltMsg_Z) || (RTE_CONST_NTC_Num_DataRngFltMsg_Z != 396u)
#   error "Enumeration constant <NTC_Num_DataRngFltMsg_Z> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataRngFltMsg_Z (396u)
#  define NTC_Num_DataRngFltMsg_Z ((NTCNumber)396u)
# endif
# if (defined RTE_CONST_NTC_Num_DataRateFltMsg_Z) || (defined NTC_Num_DataRateFltMsg_Z)
#  if (!defined RTE_CONST_NTC_Num_DataRateFltMsg_Z) || (RTE_CONST_NTC_Num_DataRateFltMsg_Z != 397u)
#   error "Enumeration constant <NTC_Num_DataRateFltMsg_Z> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataRateFltMsg_Z (397u)
#  define NTC_Num_DataRateFltMsg_Z ((NTCNumber)397u)
# endif
# if (defined RTE_CONST_NTC_Num_DataOtherFltMsg_Z) || (defined NTC_Num_DataOtherFltMsg_Z)
#  if (!defined RTE_CONST_NTC_Num_DataOtherFltMsg_Z) || (RTE_CONST_NTC_Num_DataOtherFltMsg_Z != 398u)
#   error "Enumeration constant <NTC_Num_DataOtherFltMsg_Z> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataOtherFltMsg_Z (398u)
#  define NTC_Num_DataOtherFltMsg_Z ((NTCNumber)398u)
# endif
# if (defined RTE_CONST_NTC_Num_DSTXORActive) || (defined NTC_Num_DSTXORActive)
#  if (!defined RTE_CONST_NTC_Num_DSTXORActive) || (RTE_CONST_NTC_Num_DSTXORActive != 399u)
#   error "Enumeration constant <NTC_Num_DSTXORActive> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DSTXORActive (399u)
#  define NTC_Num_DSTXORActive ((NTCNumber)399u)
# endif
# if (defined RTE_CONST_NTC_Num_InvalidMsg_AA) || (defined NTC_Num_InvalidMsg_AA)
#  if (!defined RTE_CONST_NTC_Num_InvalidMsg_AA) || (RTE_CONST_NTC_Num_InvalidMsg_AA != 400u)
#   error "Enumeration constant <NTC_Num_InvalidMsg_AA> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_InvalidMsg_AA (400u)
#  define NTC_Num_InvalidMsg_AA ((NTCNumber)400u)
# endif
# if (defined RTE_CONST_NTC_Num_MissingMsg_AA) || (defined NTC_Num_MissingMsg_AA)
#  if (!defined RTE_CONST_NTC_Num_MissingMsg_AA) || (RTE_CONST_NTC_Num_MissingMsg_AA != 401u)
#   error "Enumeration constant <NTC_Num_MissingMsg_AA> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_MissingMsg_AA (401u)
#  define NTC_Num_MissingMsg_AA ((NTCNumber)401u)
# endif
# if (defined RTE_CONST_NTC_Num_CRCFltMsg_AA) || (defined NTC_Num_CRCFltMsg_AA)
#  if (!defined RTE_CONST_NTC_Num_CRCFltMsg_AA) || (RTE_CONST_NTC_Num_CRCFltMsg_AA != 402u)
#   error "Enumeration constant <NTC_Num_CRCFltMsg_AA> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_CRCFltMsg_AA (402u)
#  define NTC_Num_CRCFltMsg_AA ((NTCNumber)402u)
# endif
# if (defined RTE_CONST_NTC_Num_PgrsCntFltMsg_AA) || (defined NTC_Num_PgrsCntFltMsg_AA)
#  if (!defined RTE_CONST_NTC_Num_PgrsCntFltMsg_AA) || (RTE_CONST_NTC_Num_PgrsCntFltMsg_AA != 403u)
#   error "Enumeration constant <NTC_Num_PgrsCntFltMsg_AA> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_PgrsCntFltMsg_AA (403u)
#  define NTC_Num_PgrsCntFltMsg_AA ((NTCNumber)403u)
# endif
# if (defined RTE_CONST_NTC_Num_DataRngFltMsg_AA) || (defined NTC_Num_DataRngFltMsg_AA)
#  if (!defined RTE_CONST_NTC_Num_DataRngFltMsg_AA) || (RTE_CONST_NTC_Num_DataRngFltMsg_AA != 404u)
#   error "Enumeration constant <NTC_Num_DataRngFltMsg_AA> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataRngFltMsg_AA (404u)
#  define NTC_Num_DataRngFltMsg_AA ((NTCNumber)404u)
# endif
# if (defined RTE_CONST_NTC_Num_DataRateFltMsg_AA) || (defined NTC_Num_DataRateFltMsg_AA)
#  if (!defined RTE_CONST_NTC_Num_DataRateFltMsg_AA) || (RTE_CONST_NTC_Num_DataRateFltMsg_AA != 405u)
#   error "Enumeration constant <NTC_Num_DataRateFltMsg_AA> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataRateFltMsg_AA (405u)
#  define NTC_Num_DataRateFltMsg_AA ((NTCNumber)405u)
# endif
# if (defined RTE_CONST_NTC_Num_DataOtherFltMsg_AA) || (defined NTC_Num_DataOtherFltMsg_AA)
#  if (!defined RTE_CONST_NTC_Num_DataOtherFltMsg_AA) || (RTE_CONST_NTC_Num_DataOtherFltMsg_AA != 406u)
#   error "Enumeration constant <NTC_Num_DataOtherFltMsg_AA> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataOtherFltMsg_AA (406u)
#  define NTC_Num_DataOtherFltMsg_AA ((NTCNumber)406u)
# endif
# if (defined RTE_CONST_NTC_Num_InvalidMsg_AB) || (defined NTC_Num_InvalidMsg_AB)
#  if (!defined RTE_CONST_NTC_Num_InvalidMsg_AB) || (RTE_CONST_NTC_Num_InvalidMsg_AB != 408u)
#   error "Enumeration constant <NTC_Num_InvalidMsg_AB> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_InvalidMsg_AB (408u)
#  define NTC_Num_InvalidMsg_AB ((NTCNumber)408u)
# endif
# if (defined RTE_CONST_NTC_Num_MissingMsg_AB) || (defined NTC_Num_MissingMsg_AB)
#  if (!defined RTE_CONST_NTC_Num_MissingMsg_AB) || (RTE_CONST_NTC_Num_MissingMsg_AB != 409u)
#   error "Enumeration constant <NTC_Num_MissingMsg_AB> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_MissingMsg_AB (409u)
#  define NTC_Num_MissingMsg_AB ((NTCNumber)409u)
# endif
# if (defined RTE_CONST_NTC_Num_CRCFltMsg_AB) || (defined NTC_Num_CRCFltMsg_AB)
#  if (!defined RTE_CONST_NTC_Num_CRCFltMsg_AB) || (RTE_CONST_NTC_Num_CRCFltMsg_AB != 410u)
#   error "Enumeration constant <NTC_Num_CRCFltMsg_AB> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_CRCFltMsg_AB (410u)
#  define NTC_Num_CRCFltMsg_AB ((NTCNumber)410u)
# endif
# if (defined RTE_CONST_NTC_Num_PgrsCntFltMsg_AB) || (defined NTC_Num_PgrsCntFltMsg_AB)
#  if (!defined RTE_CONST_NTC_Num_PgrsCntFltMsg_AB) || (RTE_CONST_NTC_Num_PgrsCntFltMsg_AB != 411u)
#   error "Enumeration constant <NTC_Num_PgrsCntFltMsg_AB> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_PgrsCntFltMsg_AB (411u)
#  define NTC_Num_PgrsCntFltMsg_AB ((NTCNumber)411u)
# endif
# if (defined RTE_CONST_NTC_Num_DataRngFltMsg_AB) || (defined NTC_Num_DataRngFltMsg_AB)
#  if (!defined RTE_CONST_NTC_Num_DataRngFltMsg_AB) || (RTE_CONST_NTC_Num_DataRngFltMsg_AB != 412u)
#   error "Enumeration constant <NTC_Num_DataRngFltMsg_AB> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataRngFltMsg_AB (412u)
#  define NTC_Num_DataRngFltMsg_AB ((NTCNumber)412u)
# endif
# if (defined RTE_CONST_NTC_Num_DataRateFltMsg_AB) || (defined NTC_Num_DataRateFltMsg_AB)
#  if (!defined RTE_CONST_NTC_Num_DataRateFltMsg_AB) || (RTE_CONST_NTC_Num_DataRateFltMsg_AB != 413u)
#   error "Enumeration constant <NTC_Num_DataRateFltMsg_AB> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataRateFltMsg_AB (413u)
#  define NTC_Num_DataRateFltMsg_AB ((NTCNumber)413u)
# endif
# if (defined RTE_CONST_NTC_Num_DataOtherFltMsg_AB) || (defined NTC_Num_DataOtherFltMsg_AB)
#  if (!defined RTE_CONST_NTC_Num_DataOtherFltMsg_AB) || (RTE_CONST_NTC_Num_DataOtherFltMsg_AB != 414u)
#   error "Enumeration constant <NTC_Num_DataOtherFltMsg_AB> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataOtherFltMsg_AB (414u)
#  define NTC_Num_DataOtherFltMsg_AB ((NTCNumber)414u)
# endif
# if (defined RTE_CONST_NTC_Num_InvalidMsg_AC) || (defined NTC_Num_InvalidMsg_AC)
#  if (!defined RTE_CONST_NTC_Num_InvalidMsg_AC) || (RTE_CONST_NTC_Num_InvalidMsg_AC != 416u)
#   error "Enumeration constant <NTC_Num_InvalidMsg_AC> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_InvalidMsg_AC (416u)
#  define NTC_Num_InvalidMsg_AC ((NTCNumber)416u)
# endif
# if (defined RTE_CONST_NTC_Num_MissingMsg_AC) || (defined NTC_Num_MissingMsg_AC)
#  if (!defined RTE_CONST_NTC_Num_MissingMsg_AC) || (RTE_CONST_NTC_Num_MissingMsg_AC != 417u)
#   error "Enumeration constant <NTC_Num_MissingMsg_AC> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_MissingMsg_AC (417u)
#  define NTC_Num_MissingMsg_AC ((NTCNumber)417u)
# endif
# if (defined RTE_CONST_NTC_Num_CRCFltMsg_AC) || (defined NTC_Num_CRCFltMsg_AC)
#  if (!defined RTE_CONST_NTC_Num_CRCFltMsg_AC) || (RTE_CONST_NTC_Num_CRCFltMsg_AC != 418u)
#   error "Enumeration constant <NTC_Num_CRCFltMsg_AC> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_CRCFltMsg_AC (418u)
#  define NTC_Num_CRCFltMsg_AC ((NTCNumber)418u)
# endif
# if (defined RTE_CONST_NTC_Num_PgrsCntFltMsg_AC) || (defined NTC_Num_PgrsCntFltMsg_AC)
#  if (!defined RTE_CONST_NTC_Num_PgrsCntFltMsg_AC) || (RTE_CONST_NTC_Num_PgrsCntFltMsg_AC != 419u)
#   error "Enumeration constant <NTC_Num_PgrsCntFltMsg_AC> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_PgrsCntFltMsg_AC (419u)
#  define NTC_Num_PgrsCntFltMsg_AC ((NTCNumber)419u)
# endif
# if (defined RTE_CONST_NTC_Num_DataRngFltMsg_AC) || (defined NTC_Num_DataRngFltMsg_AC)
#  if (!defined RTE_CONST_NTC_Num_DataRngFltMsg_AC) || (RTE_CONST_NTC_Num_DataRngFltMsg_AC != 420u)
#   error "Enumeration constant <NTC_Num_DataRngFltMsg_AC> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataRngFltMsg_AC (420u)
#  define NTC_Num_DataRngFltMsg_AC ((NTCNumber)420u)
# endif
# if (defined RTE_CONST_NTC_Num_DataRateFltMsg_AC) || (defined NTC_Num_DataRateFltMsg_AC)
#  if (!defined RTE_CONST_NTC_Num_DataRateFltMsg_AC) || (RTE_CONST_NTC_Num_DataRateFltMsg_AC != 421u)
#   error "Enumeration constant <NTC_Num_DataRateFltMsg_AC> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataRateFltMsg_AC (421u)
#  define NTC_Num_DataRateFltMsg_AC ((NTCNumber)421u)
# endif
# if (defined RTE_CONST_NTC_Num_DataOtherFltMsg_AC) || (defined NTC_Num_DataOtherFltMsg_AC)
#  if (!defined RTE_CONST_NTC_Num_DataOtherFltMsg_AC) || (RTE_CONST_NTC_Num_DataOtherFltMsg_AC != 422u)
#   error "Enumeration constant <NTC_Num_DataOtherFltMsg_AC> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataOtherFltMsg_AC (422u)
#  define NTC_Num_DataOtherFltMsg_AC ((NTCNumber)422u)
# endif
# if (defined RTE_CONST_NTC_Num_InvalidMsg_AD) || (defined NTC_Num_InvalidMsg_AD)
#  if (!defined RTE_CONST_NTC_Num_InvalidMsg_AD) || (RTE_CONST_NTC_Num_InvalidMsg_AD != 424u)
#   error "Enumeration constant <NTC_Num_InvalidMsg_AD> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_InvalidMsg_AD (424u)
#  define NTC_Num_InvalidMsg_AD ((NTCNumber)424u)
# endif
# if (defined RTE_CONST_NTC_Num_MissingMsg_AD) || (defined NTC_Num_MissingMsg_AD)
#  if (!defined RTE_CONST_NTC_Num_MissingMsg_AD) || (RTE_CONST_NTC_Num_MissingMsg_AD != 425u)
#   error "Enumeration constant <NTC_Num_MissingMsg_AD> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_MissingMsg_AD (425u)
#  define NTC_Num_MissingMsg_AD ((NTCNumber)425u)
# endif
# if (defined RTE_CONST_NTC_Num_CRCFltMsg_AD) || (defined NTC_Num_CRCFltMsg_AD)
#  if (!defined RTE_CONST_NTC_Num_CRCFltMsg_AD) || (RTE_CONST_NTC_Num_CRCFltMsg_AD != 426u)
#   error "Enumeration constant <NTC_Num_CRCFltMsg_AD> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_CRCFltMsg_AD (426u)
#  define NTC_Num_CRCFltMsg_AD ((NTCNumber)426u)
# endif
# if (defined RTE_CONST_NTC_Num_PgrsCntFltMsg_AD) || (defined NTC_Num_PgrsCntFltMsg_AD)
#  if (!defined RTE_CONST_NTC_Num_PgrsCntFltMsg_AD) || (RTE_CONST_NTC_Num_PgrsCntFltMsg_AD != 427u)
#   error "Enumeration constant <NTC_Num_PgrsCntFltMsg_AD> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_PgrsCntFltMsg_AD (427u)
#  define NTC_Num_PgrsCntFltMsg_AD ((NTCNumber)427u)
# endif
# if (defined RTE_CONST_NTC_Num_DataRngFltMsg_AD) || (defined NTC_Num_DataRngFltMsg_AD)
#  if (!defined RTE_CONST_NTC_Num_DataRngFltMsg_AD) || (RTE_CONST_NTC_Num_DataRngFltMsg_AD != 428u)
#   error "Enumeration constant <NTC_Num_DataRngFltMsg_AD> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataRngFltMsg_AD (428u)
#  define NTC_Num_DataRngFltMsg_AD ((NTCNumber)428u)
# endif
# if (defined RTE_CONST_NTC_Num_DataRateFltMsg_AD) || (defined NTC_Num_DataRateFltMsg_AD)
#  if (!defined RTE_CONST_NTC_Num_DataRateFltMsg_AD) || (RTE_CONST_NTC_Num_DataRateFltMsg_AD != 429u)
#   error "Enumeration constant <NTC_Num_DataRateFltMsg_AD> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataRateFltMsg_AD (429u)
#  define NTC_Num_DataRateFltMsg_AD ((NTCNumber)429u)
# endif
# if (defined RTE_CONST_NTC_Num_DataOtherFltMsg_AD) || (defined NTC_Num_DataOtherFltMsg_AD)
#  if (!defined RTE_CONST_NTC_Num_DataOtherFltMsg_AD) || (RTE_CONST_NTC_Num_DataOtherFltMsg_AD != 430u)
#   error "Enumeration constant <NTC_Num_DataOtherFltMsg_AD> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataOtherFltMsg_AD (430u)
#  define NTC_Num_DataOtherFltMsg_AD ((NTCNumber)430u)
# endif
# if (defined RTE_CONST_NTC_Num_InvalidMsg_AE) || (defined NTC_Num_InvalidMsg_AE)
#  if (!defined RTE_CONST_NTC_Num_InvalidMsg_AE) || (RTE_CONST_NTC_Num_InvalidMsg_AE != 432u)
#   error "Enumeration constant <NTC_Num_InvalidMsg_AE> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_InvalidMsg_AE (432u)
#  define NTC_Num_InvalidMsg_AE ((NTCNumber)432u)
# endif
# if (defined RTE_CONST_NTC_Num_MissingMsg_AE) || (defined NTC_Num_MissingMsg_AE)
#  if (!defined RTE_CONST_NTC_Num_MissingMsg_AE) || (RTE_CONST_NTC_Num_MissingMsg_AE != 433u)
#   error "Enumeration constant <NTC_Num_MissingMsg_AE> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_MissingMsg_AE (433u)
#  define NTC_Num_MissingMsg_AE ((NTCNumber)433u)
# endif
# if (defined RTE_CONST_NTC_Num_CRCFltMsg_AE) || (defined NTC_Num_CRCFltMsg_AE)
#  if (!defined RTE_CONST_NTC_Num_CRCFltMsg_AE) || (RTE_CONST_NTC_Num_CRCFltMsg_AE != 434u)
#   error "Enumeration constant <NTC_Num_CRCFltMsg_AE> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_CRCFltMsg_AE (434u)
#  define NTC_Num_CRCFltMsg_AE ((NTCNumber)434u)
# endif
# if (defined RTE_CONST_NTC_Num_PgrsCntFltMsg_AE) || (defined NTC_Num_PgrsCntFltMsg_AE)
#  if (!defined RTE_CONST_NTC_Num_PgrsCntFltMsg_AE) || (RTE_CONST_NTC_Num_PgrsCntFltMsg_AE != 435u)
#   error "Enumeration constant <NTC_Num_PgrsCntFltMsg_AE> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_PgrsCntFltMsg_AE (435u)
#  define NTC_Num_PgrsCntFltMsg_AE ((NTCNumber)435u)
# endif
# if (defined RTE_CONST_NTC_Num_DataRngFltMsg_AE) || (defined NTC_Num_DataRngFltMsg_AE)
#  if (!defined RTE_CONST_NTC_Num_DataRngFltMsg_AE) || (RTE_CONST_NTC_Num_DataRngFltMsg_AE != 436u)
#   error "Enumeration constant <NTC_Num_DataRngFltMsg_AE> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataRngFltMsg_AE (436u)
#  define NTC_Num_DataRngFltMsg_AE ((NTCNumber)436u)
# endif
# if (defined RTE_CONST_NTC_Num_DataRateFltMsg_AE) || (defined NTC_Num_DataRateFltMsg_AE)
#  if (!defined RTE_CONST_NTC_Num_DataRateFltMsg_AE) || (RTE_CONST_NTC_Num_DataRateFltMsg_AE != 437u)
#   error "Enumeration constant <NTC_Num_DataRateFltMsg_AE> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataRateFltMsg_AE (437u)
#  define NTC_Num_DataRateFltMsg_AE ((NTCNumber)437u)
# endif
# if (defined RTE_CONST_NTC_Num_DataOtherFltMsg_AE) || (defined NTC_Num_DataOtherFltMsg_AE)
#  if (!defined RTE_CONST_NTC_Num_DataOtherFltMsg_AE) || (RTE_CONST_NTC_Num_DataOtherFltMsg_AE != 438u)
#   error "Enumeration constant <NTC_Num_DataOtherFltMsg_AE> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataOtherFltMsg_AE (438u)
#  define NTC_Num_DataOtherFltMsg_AE ((NTCNumber)438u)
# endif
# if (defined RTE_CONST_NTC_Num_InvalidMsg_AF) || (defined NTC_Num_InvalidMsg_AF)
#  if (!defined RTE_CONST_NTC_Num_InvalidMsg_AF) || (RTE_CONST_NTC_Num_InvalidMsg_AF != 440u)
#   error "Enumeration constant <NTC_Num_InvalidMsg_AF> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_InvalidMsg_AF (440u)
#  define NTC_Num_InvalidMsg_AF ((NTCNumber)440u)
# endif
# if (defined RTE_CONST_NTC_Num_MissingMsg_AF) || (defined NTC_Num_MissingMsg_AF)
#  if (!defined RTE_CONST_NTC_Num_MissingMsg_AF) || (RTE_CONST_NTC_Num_MissingMsg_AF != 441u)
#   error "Enumeration constant <NTC_Num_MissingMsg_AF> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_MissingMsg_AF (441u)
#  define NTC_Num_MissingMsg_AF ((NTCNumber)441u)
# endif
# if (defined RTE_CONST_NTC_Num_CRCFltMsg_AF) || (defined NTC_Num_CRCFltMsg_AF)
#  if (!defined RTE_CONST_NTC_Num_CRCFltMsg_AF) || (RTE_CONST_NTC_Num_CRCFltMsg_AF != 442u)
#   error "Enumeration constant <NTC_Num_CRCFltMsg_AF> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_CRCFltMsg_AF (442u)
#  define NTC_Num_CRCFltMsg_AF ((NTCNumber)442u)
# endif
# if (defined RTE_CONST_NTC_Num_PgrsCntFltMsg_AF) || (defined NTC_Num_PgrsCntFltMsg_AF)
#  if (!defined RTE_CONST_NTC_Num_PgrsCntFltMsg_AF) || (RTE_CONST_NTC_Num_PgrsCntFltMsg_AF != 443u)
#   error "Enumeration constant <NTC_Num_PgrsCntFltMsg_AF> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_PgrsCntFltMsg_AF (443u)
#  define NTC_Num_PgrsCntFltMsg_AF ((NTCNumber)443u)
# endif
# if (defined RTE_CONST_NTC_Num_DataRngFltMsg_AF) || (defined NTC_Num_DataRngFltMsg_AF)
#  if (!defined RTE_CONST_NTC_Num_DataRngFltMsg_AF) || (RTE_CONST_NTC_Num_DataRngFltMsg_AF != 444u)
#   error "Enumeration constant <NTC_Num_DataRngFltMsg_AF> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataRngFltMsg_AF (444u)
#  define NTC_Num_DataRngFltMsg_AF ((NTCNumber)444u)
# endif
# if (defined RTE_CONST_NTC_Num_DataRateFltMsg_AF) || (defined NTC_Num_DataRateFltMsg_AF)
#  if (!defined RTE_CONST_NTC_Num_DataRateFltMsg_AF) || (RTE_CONST_NTC_Num_DataRateFltMsg_AF != 445u)
#   error "Enumeration constant <NTC_Num_DataRateFltMsg_AF> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataRateFltMsg_AF (445u)
#  define NTC_Num_DataRateFltMsg_AF ((NTCNumber)445u)
# endif
# if (defined RTE_CONST_NTC_Num_DataOtherFltMsg_AF) || (defined NTC_Num_DataOtherFltMsg_AF)
#  if (!defined RTE_CONST_NTC_Num_DataOtherFltMsg_AF) || (RTE_CONST_NTC_Num_DataOtherFltMsg_AF != 446u)
#   error "Enumeration constant <NTC_Num_DataOtherFltMsg_AF> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataOtherFltMsg_AF (446u)
#  define NTC_Num_DataOtherFltMsg_AF ((NTCNumber)446u)
# endif
# if (defined RTE_CONST_NTC_Num_InvalidMsg_AG) || (defined NTC_Num_InvalidMsg_AG)
#  if (!defined RTE_CONST_NTC_Num_InvalidMsg_AG) || (RTE_CONST_NTC_Num_InvalidMsg_AG != 448u)
#   error "Enumeration constant <NTC_Num_InvalidMsg_AG> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_InvalidMsg_AG (448u)
#  define NTC_Num_InvalidMsg_AG ((NTCNumber)448u)
# endif
# if (defined RTE_CONST_NTC_Num_MissingMsg_AG) || (defined NTC_Num_MissingMsg_AG)
#  if (!defined RTE_CONST_NTC_Num_MissingMsg_AG) || (RTE_CONST_NTC_Num_MissingMsg_AG != 449u)
#   error "Enumeration constant <NTC_Num_MissingMsg_AG> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_MissingMsg_AG (449u)
#  define NTC_Num_MissingMsg_AG ((NTCNumber)449u)
# endif
# if (defined RTE_CONST_NTC_Num_CRCFltMsg_AG) || (defined NTC_Num_CRCFltMsg_AG)
#  if (!defined RTE_CONST_NTC_Num_CRCFltMsg_AG) || (RTE_CONST_NTC_Num_CRCFltMsg_AG != 450u)
#   error "Enumeration constant <NTC_Num_CRCFltMsg_AG> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_CRCFltMsg_AG (450u)
#  define NTC_Num_CRCFltMsg_AG ((NTCNumber)450u)
# endif
# if (defined RTE_CONST_NTC_Num_PgrsCntFltMsg_AG) || (defined NTC_Num_PgrsCntFltMsg_AG)
#  if (!defined RTE_CONST_NTC_Num_PgrsCntFltMsg_AG) || (RTE_CONST_NTC_Num_PgrsCntFltMsg_AG != 451u)
#   error "Enumeration constant <NTC_Num_PgrsCntFltMsg_AG> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_PgrsCntFltMsg_AG (451u)
#  define NTC_Num_PgrsCntFltMsg_AG ((NTCNumber)451u)
# endif
# if (defined RTE_CONST_NTC_Num_DataRngFltMsg_AG) || (defined NTC_Num_DataRngFltMsg_AG)
#  if (!defined RTE_CONST_NTC_Num_DataRngFltMsg_AG) || (RTE_CONST_NTC_Num_DataRngFltMsg_AG != 452u)
#   error "Enumeration constant <NTC_Num_DataRngFltMsg_AG> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataRngFltMsg_AG (452u)
#  define NTC_Num_DataRngFltMsg_AG ((NTCNumber)452u)
# endif
# if (defined RTE_CONST_NTC_Num_DataRateFltMsg_AG) || (defined NTC_Num_DataRateFltMsg_AG)
#  if (!defined RTE_CONST_NTC_Num_DataRateFltMsg_AG) || (RTE_CONST_NTC_Num_DataRateFltMsg_AG != 453u)
#   error "Enumeration constant <NTC_Num_DataRateFltMsg_AG> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataRateFltMsg_AG (453u)
#  define NTC_Num_DataRateFltMsg_AG ((NTCNumber)453u)
# endif
# if (defined RTE_CONST_NTC_Num_DataOtherFltMsg_AG) || (defined NTC_Num_DataOtherFltMsg_AG)
#  if (!defined RTE_CONST_NTC_Num_DataOtherFltMsg_AG) || (RTE_CONST_NTC_Num_DataOtherFltMsg_AG != 454u)
#   error "Enumeration constant <NTC_Num_DataOtherFltMsg_AG> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataOtherFltMsg_AG (454u)
#  define NTC_Num_DataOtherFltMsg_AG ((NTCNumber)454u)
# endif
# if (defined RTE_CONST_NTC_Num_InvalidMsg_AH) || (defined NTC_Num_InvalidMsg_AH)
#  if (!defined RTE_CONST_NTC_Num_InvalidMsg_AH) || (RTE_CONST_NTC_Num_InvalidMsg_AH != 456u)
#   error "Enumeration constant <NTC_Num_InvalidMsg_AH> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_InvalidMsg_AH (456u)
#  define NTC_Num_InvalidMsg_AH ((NTCNumber)456u)
# endif
# if (defined RTE_CONST_NTC_Num_MissingMsg_AH) || (defined NTC_Num_MissingMsg_AH)
#  if (!defined RTE_CONST_NTC_Num_MissingMsg_AH) || (RTE_CONST_NTC_Num_MissingMsg_AH != 457u)
#   error "Enumeration constant <NTC_Num_MissingMsg_AH> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_MissingMsg_AH (457u)
#  define NTC_Num_MissingMsg_AH ((NTCNumber)457u)
# endif
# if (defined RTE_CONST_NTC_Num_CRCFltMsg_AH) || (defined NTC_Num_CRCFltMsg_AH)
#  if (!defined RTE_CONST_NTC_Num_CRCFltMsg_AH) || (RTE_CONST_NTC_Num_CRCFltMsg_AH != 458u)
#   error "Enumeration constant <NTC_Num_CRCFltMsg_AH> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_CRCFltMsg_AH (458u)
#  define NTC_Num_CRCFltMsg_AH ((NTCNumber)458u)
# endif
# if (defined RTE_CONST_NTC_Num_PgrsCntFltMsg_AH) || (defined NTC_Num_PgrsCntFltMsg_AH)
#  if (!defined RTE_CONST_NTC_Num_PgrsCntFltMsg_AH) || (RTE_CONST_NTC_Num_PgrsCntFltMsg_AH != 459u)
#   error "Enumeration constant <NTC_Num_PgrsCntFltMsg_AH> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_PgrsCntFltMsg_AH (459u)
#  define NTC_Num_PgrsCntFltMsg_AH ((NTCNumber)459u)
# endif
# if (defined RTE_CONST_NTC_Num_DataRngFltMsg_AH) || (defined NTC_Num_DataRngFltMsg_AH)
#  if (!defined RTE_CONST_NTC_Num_DataRngFltMsg_AH) || (RTE_CONST_NTC_Num_DataRngFltMsg_AH != 460u)
#   error "Enumeration constant <NTC_Num_DataRngFltMsg_AH> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataRngFltMsg_AH (460u)
#  define NTC_Num_DataRngFltMsg_AH ((NTCNumber)460u)
# endif
# if (defined RTE_CONST_NTC_Num_DataRateFltMsg_AH) || (defined NTC_Num_DataRateFltMsg_AH)
#  if (!defined RTE_CONST_NTC_Num_DataRateFltMsg_AH) || (RTE_CONST_NTC_Num_DataRateFltMsg_AH != 461u)
#   error "Enumeration constant <NTC_Num_DataRateFltMsg_AH> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataRateFltMsg_AH (461u)
#  define NTC_Num_DataRateFltMsg_AH ((NTCNumber)461u)
# endif
# if (defined RTE_CONST_NTC_Num_DataOtherFltMsg_AH) || (defined NTC_Num_DataOtherFltMsg_AH)
#  if (!defined RTE_CONST_NTC_Num_DataOtherFltMsg_AH) || (RTE_CONST_NTC_Num_DataOtherFltMsg_AH != 462u)
#   error "Enumeration constant <NTC_Num_DataOtherFltMsg_AH> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DataOtherFltMsg_AH (462u)
#  define NTC_Num_DataOtherFltMsg_AH ((NTCNumber)462u)
# endif
# if (defined RTE_CONST_NTC_Num_InvalidMsg_ParkAssistParallel) || (defined NTC_Num_InvalidMsg_ParkAssistParallel)
#  if (!defined RTE_CONST_NTC_Num_InvalidMsg_ParkAssistParallel) || (RTE_CONST_NTC_Num_InvalidMsg_ParkAssistParallel != 464u)
#   error "Enumeration constant <NTC_Num_InvalidMsg_ParkAssistParallel> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_InvalidMsg_ParkAssistParallel (464u)
#  define NTC_Num_InvalidMsg_ParkAssistParallel ((NTCNumber)464u)
# endif
# if (defined RTE_CONST_NTC_Num_FlexrayCommunicationError) || (defined NTC_Num_FlexrayCommunicationError)
#  if (!defined RTE_CONST_NTC_Num_FlexrayCommunicationError) || (RTE_CONST_NTC_Num_FlexrayCommunicationError != 465u)
#   error "Enumeration constant <NTC_Num_FlexrayCommunicationError> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_FlexrayCommunicationError (465u)
#  define NTC_Num_FlexrayCommunicationError ((NTCNumber)465u)
# endif
# if (defined RTE_CONST_NTC_Num_InvalidMsg_AI) || (defined NTC_Num_InvalidMsg_AI)
#  if (!defined RTE_CONST_NTC_Num_InvalidMsg_AI) || (RTE_CONST_NTC_Num_InvalidMsg_AI != 466u)
#   error "Enumeration constant <NTC_Num_InvalidMsg_AI> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_InvalidMsg_AI (466u)
#  define NTC_Num_InvalidMsg_AI ((NTCNumber)466u)
# endif
# if (defined RTE_CONST_NTC_Num_MissingMsg_AI) || (defined NTC_Num_MissingMsg_AI)
#  if (!defined RTE_CONST_NTC_Num_MissingMsg_AI) || (RTE_CONST_NTC_Num_MissingMsg_AI != 467u)
#   error "Enumeration constant <NTC_Num_MissingMsg_AI> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_MissingMsg_AI (467u)
#  define NTC_Num_MissingMsg_AI ((NTCNumber)467u)
# endif
# if (defined RTE_CONST_NTC_Num_InvalidMsg_AJ) || (defined NTC_Num_InvalidMsg_AJ)
#  if (!defined RTE_CONST_NTC_Num_InvalidMsg_AJ) || (RTE_CONST_NTC_Num_InvalidMsg_AJ != 472u)
#   error "Enumeration constant <NTC_Num_InvalidMsg_AJ> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_InvalidMsg_AJ (472u)
#  define NTC_Num_InvalidMsg_AJ ((NTCNumber)472u)
# endif
# if (defined RTE_CONST_NTC_Num_MissingMsg_AJ) || (defined NTC_Num_MissingMsg_AJ)
#  if (!defined RTE_CONST_NTC_Num_MissingMsg_AJ) || (RTE_CONST_NTC_Num_MissingMsg_AJ != 473u)
#   error "Enumeration constant <NTC_Num_MissingMsg_AJ> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_MissingMsg_AJ (473u)
#  define NTC_Num_MissingMsg_AJ ((NTCNumber)473u)
# endif
# if (defined RTE_CONST_NTC_Num_InvalidMsg_AK) || (defined NTC_Num_InvalidMsg_AK)
#  if (!defined RTE_CONST_NTC_Num_InvalidMsg_AK) || (RTE_CONST_NTC_Num_InvalidMsg_AK != 480u)
#   error "Enumeration constant <NTC_Num_InvalidMsg_AK> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_InvalidMsg_AK (480u)
#  define NTC_Num_InvalidMsg_AK ((NTCNumber)480u)
# endif
# if (defined RTE_CONST_NTC_Num_MissingMsg_AK) || (defined NTC_Num_MissingMsg_AK)
#  if (!defined RTE_CONST_NTC_Num_MissingMsg_AK) || (RTE_CONST_NTC_Num_MissingMsg_AK != 481u)
#   error "Enumeration constant <NTC_Num_MissingMsg_AK> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_MissingMsg_AK (481u)
#  define NTC_Num_MissingMsg_AK ((NTCNumber)481u)
# endif
# if (defined RTE_CONST_NTC_Num_MissingMsg_AL) || (defined NTC_Num_MissingMsg_AL)
#  if (!defined RTE_CONST_NTC_Num_MissingMsg_AL) || (RTE_CONST_NTC_Num_MissingMsg_AL != 489u)
#   error "Enumeration constant <NTC_Num_MissingMsg_AL> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_MissingMsg_AL (489u)
#  define NTC_Num_MissingMsg_AL ((NTCNumber)489u)
# endif
# if (defined RTE_CONST_NTC_Num_SysConsistencyVerf) || (defined NTC_Num_SysConsistencyVerf)
#  if (!defined RTE_CONST_NTC_Num_SysConsistencyVerf) || (RTE_CONST_NTC_Num_SysConsistencyVerf != 496u)
#   error "Enumeration constant <NTC_Num_SysConsistencyVerf> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_SysConsistencyVerf (496u)
#  define NTC_Num_SysConsistencyVerf ((NTCNumber)496u)
# endif
# if (defined RTE_CONST_NTC_Num_ConfigMisMatch) || (defined NTC_Num_ConfigMisMatch)
#  if (!defined RTE_CONST_NTC_Num_ConfigMisMatch) || (RTE_CONST_NTC_Num_ConfigMisMatch != 497u)
#   error "Enumeration constant <NTC_Num_ConfigMisMatch> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_ConfigMisMatch (497u)
#  define NTC_Num_ConfigMisMatch ((NTCNumber)497u)
# endif
# if (defined RTE_CONST_NTC_Num_CalNotPrgmd) || (defined NTC_Num_CalNotPrgmd)
#  if (!defined RTE_CONST_NTC_Num_CalNotPrgmd) || (RTE_CONST_NTC_Num_CalNotPrgmd != 498u)
#   error "Enumeration constant <NTC_Num_CalNotPrgmd> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_CalNotPrgmd (498u)
#  define NTC_Num_CalNotPrgmd ((NTCNumber)498u)
# endif
# if (defined RTE_CONST_NTC_Num_TunSetNotPrgmd) || (defined NTC_Num_TunSetNotPrgmd)
#  if (!defined RTE_CONST_NTC_Num_TunSetNotPrgmd) || (RTE_CONST_NTC_Num_TunSetNotPrgmd != 499u)
#   error "Enumeration constant <NTC_Num_TunSetNotPrgmd> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_TunSetNotPrgmd (499u)
#  define NTC_Num_TunSetNotPrgmd ((NTCNumber)499u)
# endif
# if (defined RTE_CONST_NTC_Num_EEPROMtoFeeCpyError) || (defined NTC_Num_EEPROMtoFeeCpyError)
#  if (!defined RTE_CONST_NTC_Num_EEPROMtoFeeCpyError) || (RTE_CONST_NTC_Num_EEPROMtoFeeCpyError != 500u)
#   error "Enumeration constant <NTC_Num_EEPROMtoFeeCpyError> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_EEPROMtoFeeCpyError (500u)
#  define NTC_Num_EEPROMtoFeeCpyError ((NTCNumber)500u)
# endif
# if (defined RTE_CONST_NTC_Num_EOLVehTunNtPerf) || (defined NTC_Num_EOLVehTunNtPerf)
#  if (!defined RTE_CONST_NTC_Num_EOLVehTunNtPerf) || (RTE_CONST_NTC_Num_EOLVehTunNtPerf != 501u)
#   error "Enumeration constant <NTC_Num_EOLVehTunNtPerf> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_EOLVehTunNtPerf (501u)
#  define NTC_Num_EOLVehTunNtPerf ((NTCNumber)501u)
# endif
# if (defined RTE_CONST_NTC_Num_MtrSensorNotTrimmed) || (defined NTC_Num_MtrSensorNotTrimmed)
#  if (!defined RTE_CONST_NTC_Num_MtrSensorNotTrimmed) || (RTE_CONST_NTC_Num_MtrSensorNotTrimmed != 502u)
#   error "Enumeration constant <NTC_Num_MtrSensorNotTrimmed> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_MtrSensorNotTrimmed (502u)
#  define NTC_Num_MtrSensorNotTrimmed ((NTCNumber)502u)
# endif
# if (defined RTE_CONST_NTC_Num_HWASensorNotTrimmed) || (defined NTC_Num_HWASensorNotTrimmed)
#  if (!defined RTE_CONST_NTC_Num_HWASensorNotTrimmed) || (RTE_CONST_NTC_Num_HWASensorNotTrimmed != 504u)
#   error "Enumeration constant <NTC_Num_HWASensorNotTrimmed> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_HWASensorNotTrimmed (504u)
#  define NTC_Num_HWASensorNotTrimmed ((NTCNumber)504u)
# endif
# if (defined RTE_CONST_NTC_Num_HWASensorTrimNoAttempt) || (defined NTC_Num_HWASensorTrimNoAttempt)
#  if (!defined RTE_CONST_NTC_Num_HWASensorTrimNoAttempt) || (RTE_CONST_NTC_Num_HWASensorTrimNoAttempt != 505u)
#   error "Enumeration constant <NTC_Num_HWASensorTrimNoAttempt> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_HWASensorTrimNoAttempt (505u)
#  define NTC_Num_HWASensorTrimNoAttempt ((NTCNumber)505u)
# endif
# if (defined RTE_CONST_NTC_Num_TrqSensorScaleNotSet) || (defined NTC_Num_TrqSensorScaleNotSet)
#  if (!defined RTE_CONST_NTC_Num_TrqSensorScaleNotSet) || (RTE_CONST_NTC_Num_TrqSensorScaleNotSet != 506u)
#   error "Enumeration constant <NTC_Num_TrqSensorScaleNotSet> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_TrqSensorScaleNotSet (506u)
#  define NTC_Num_TrqSensorScaleNotSet ((NTCNumber)506u)
# endif
# if (defined RTE_CONST_NTC_Num_TrqSensorNotTrimmed) || (defined NTC_Num_TrqSensorNotTrimmed)
#  if (!defined RTE_CONST_NTC_Num_TrqSensorNotTrimmed) || (RTE_CONST_NTC_Num_TrqSensorNotTrimmed != 507u)
#   error "Enumeration constant <NTC_Num_TrqSensorNotTrimmed> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_TrqSensorNotTrimmed (507u)
#  define NTC_Num_TrqSensorNotTrimmed ((NTCNumber)507u)
# endif
# if (defined RTE_CONST_NTC_Num_AnaHWDiffTqOfstNotTrmd) || (defined NTC_Num_AnaHWDiffTqOfstNotTrmd)
#  if (!defined RTE_CONST_NTC_Num_AnaHWDiffTqOfstNotTrmd) || (RTE_CONST_NTC_Num_AnaHWDiffTqOfstNotTrmd != 508u)
#   error "Enumeration constant <NTC_Num_AnaHWDiffTqOfstNotTrmd> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_AnaHWDiffTqOfstNotTrmd (508u)
#  define NTC_Num_AnaHWDiffTqOfstNotTrmd ((NTCNumber)508u)
# endif
# if (defined RTE_CONST_NTC_Num_DigTrqSensorScaleNotSet) || (defined NTC_Num_DigTrqSensorScaleNotSet)
#  if (!defined RTE_CONST_NTC_Num_DigTrqSensorScaleNotSet) || (RTE_CONST_NTC_Num_DigTrqSensorScaleNotSet != 509u)
#   error "Enumeration constant <NTC_Num_DigTrqSensorScaleNotSet> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DigTrqSensorScaleNotSet (509u)
#  define NTC_Num_DigTrqSensorScaleNotSet ((NTCNumber)509u)
# endif
# if (defined RTE_CONST_NTC_Num_DigTrqSensorNotTrimmed) || (defined NTC_Num_DigTrqSensorNotTrimmed)
#  if (!defined RTE_CONST_NTC_Num_DigTrqSensorNotTrimmed) || (RTE_CONST_NTC_Num_DigTrqSensorNotTrimmed != 510u)
#   error "Enumeration constant <NTC_Num_DigTrqSensorNotTrimmed> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_DigTrqSensorNotTrimmed (510u)
#  define NTC_Num_DigTrqSensorNotTrimmed ((NTCNumber)510u)
# endif
# if (defined RTE_CONST_NTC_Num_SENTHWDiffTqOfstNotTrmd) || (defined NTC_Num_SENTHWDiffTqOfstNotTrmd)
#  if (!defined RTE_CONST_NTC_Num_SENTHWDiffTqOfstNotTrmd) || (RTE_CONST_NTC_Num_SENTHWDiffTqOfstNotTrmd != 511u)
#   error "Enumeration constant <NTC_Num_SENTHWDiffTqOfstNotTrmd> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_Num_SENTHWDiffTqOfstNotTrmd (511u)
#  define NTC_Num_SENTHWDiffTqOfstNotTrmd ((NTCNumber)511u)
# endif

# define Rte_TypeDef_NvM_RequestResultType
typedef uint8 NvM_RequestResultType;
# define NvM_RequestResultType_LowerLimit ((NvM_RequestResultType)0u)
# define NvM_RequestResultType_UpperLimit ((NvM_RequestResultType)5u)
# if (defined RTE_CONST_NVM_REQ_OK) || (defined NVM_REQ_OK)
#  if (!defined RTE_CONST_NVM_REQ_OK) || (RTE_CONST_NVM_REQ_OK != 0u)
#   error "Enumeration constant <NVM_REQ_OK> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NVM_REQ_OK (0u)
#  define NVM_REQ_OK ((NvM_RequestResultType)0u)
# endif
# if (defined RTE_CONST_NVM_REQ_NOT_OK) || (defined NVM_REQ_NOT_OK)
#  if (!defined RTE_CONST_NVM_REQ_NOT_OK) || (RTE_CONST_NVM_REQ_NOT_OK != 1u)
#   error "Enumeration constant <NVM_REQ_NOT_OK> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NVM_REQ_NOT_OK (1u)
#  define NVM_REQ_NOT_OK ((NvM_RequestResultType)1u)
# endif
# if (defined RTE_CONST_NVM_REQ_PENDING) || (defined NVM_REQ_PENDING)
#  if (!defined RTE_CONST_NVM_REQ_PENDING) || (RTE_CONST_NVM_REQ_PENDING != 2u)
#   error "Enumeration constant <NVM_REQ_PENDING> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NVM_REQ_PENDING (2u)
#  define NVM_REQ_PENDING ((NvM_RequestResultType)2u)
# endif
# if (defined RTE_CONST_NVM_REQ_INTEGRITY_FAILED) || (defined NVM_REQ_INTEGRITY_FAILED)
#  if (!defined RTE_CONST_NVM_REQ_INTEGRITY_FAILED) || (RTE_CONST_NVM_REQ_INTEGRITY_FAILED != 3u)
#   error "Enumeration constant <NVM_REQ_INTEGRITY_FAILED> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NVM_REQ_INTEGRITY_FAILED (3u)
#  define NVM_REQ_INTEGRITY_FAILED ((NvM_RequestResultType)3u)
# endif
# if (defined RTE_CONST_NVM_REQ_BLOCK_SKIPPED) || (defined NVM_REQ_BLOCK_SKIPPED)
#  if (!defined RTE_CONST_NVM_REQ_BLOCK_SKIPPED) || (RTE_CONST_NVM_REQ_BLOCK_SKIPPED != 4u)
#   error "Enumeration constant <NVM_REQ_BLOCK_SKIPPED> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NVM_REQ_BLOCK_SKIPPED (4u)
#  define NVM_REQ_BLOCK_SKIPPED ((NvM_RequestResultType)4u)
# endif
# if (defined RTE_CONST_NVM_REQ_NV_INVALIDATED) || (defined NVM_REQ_NV_INVALIDATED)
#  if (!defined RTE_CONST_NVM_REQ_NV_INVALIDATED) || (RTE_CONST_NVM_REQ_NV_INVALIDATED != 5u)
#   error "Enumeration constant <NVM_REQ_NV_INVALIDATED> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NVM_REQ_NV_INVALIDATED (5u)
#  define NVM_REQ_NV_INVALIDATED ((NvM_RequestResultType)5u)
# endif

# define Rte_TypeDef_NxtrDiagMgrStatus
typedef uint8 NxtrDiagMgrStatus;
# define NxtrDiagMgrStatus_LowerLimit ((NxtrDiagMgrStatus)0u)
# define NxtrDiagMgrStatus_UpperLimit ((NxtrDiagMgrStatus)255u)
# if (defined RTE_CONST_NTC_STATUS_PASSED) || (defined NTC_STATUS_PASSED)
#  if (!defined RTE_CONST_NTC_STATUS_PASSED) || (RTE_CONST_NTC_STATUS_PASSED != 0u)
#   error "Enumeration constant <NTC_STATUS_PASSED> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_STATUS_PASSED (0u)
#  define NTC_STATUS_PASSED ((NxtrDiagMgrStatus)0u)
# endif
# if (defined RTE_CONST_NTC_STATUS_FAILED) || (defined NTC_STATUS_FAILED)
#  if (!defined RTE_CONST_NTC_STATUS_FAILED) || (RTE_CONST_NTC_STATUS_FAILED != 1u)
#   error "Enumeration constant <NTC_STATUS_FAILED> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_STATUS_FAILED (1u)
#  define NTC_STATUS_FAILED ((NxtrDiagMgrStatus)1u)
# endif
# if (defined RTE_CONST_NTC_STATUS_PREPASSED) || (defined NTC_STATUS_PREPASSED)
#  if (!defined RTE_CONST_NTC_STATUS_PREPASSED) || (RTE_CONST_NTC_STATUS_PREPASSED != 2u)
#   error "Enumeration constant <NTC_STATUS_PREPASSED> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_STATUS_PREPASSED (2u)
#  define NTC_STATUS_PREPASSED ((NxtrDiagMgrStatus)2u)
# endif
# if (defined RTE_CONST_NTC_STATUS_PREFAILED) || (defined NTC_STATUS_PREFAILED)
#  if (!defined RTE_CONST_NTC_STATUS_PREFAILED) || (RTE_CONST_NTC_STATUS_PREFAILED != 3u)
#   error "Enumeration constant <NTC_STATUS_PREFAILED> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_NTC_STATUS_PREFAILED (3u)
#  define NTC_STATUS_PREFAILED ((NxtrDiagMgrStatus)3u)
# endif

# define Rte_TypeDef_NvM_DestPtr
typedef UInt8 NvM_DestPtr[65535];

# define Rte_TypeDef_VehDyn_DataType
typedef struct
{
  Float NVMStoredLastPos_HwDeg_f32;
  Boolean NVMStoredLastPosValid_Cnt_lgc;
} VehDyn_DataType;


# ifndef RTE_SUPPRESS_UNUSED_DATATYPES
/**********************************************************************************************************************
 * Unused Data type definitions
 *********************************************************************************************************************/

#  define Rte_TypeDef_Double
typedef float64 Double;
#  define Double_LowerLimit ((Double)-DBL_MAX)
#  define Double_UpperLimit ((Double)DBL_MAX)

#  define Rte_TypeDef_SInt16
typedef sint16 SInt16;
#  define SInt16_LowerLimit ((SInt16)-32768)
#  define SInt16_UpperLimit ((SInt16)32767)

#  define Rte_TypeDef_SInt32
typedef sint32 SInt32;
#  define SInt32_LowerLimit ((SInt32)-2147483648)
#  define SInt32_UpperLimit ((SInt32)2147483647)

#  define Rte_TypeDef_SInt4
typedef sint8 SInt4;
#  define SInt4_LowerLimit ((SInt4)-8)
#  define SInt4_UpperLimit ((SInt4)7)

#  define Rte_TypeDef_SInt8
typedef sint8 SInt8;
#  define SInt8_LowerLimit ((SInt8)-128)
#  define SInt8_UpperLimit ((SInt8)127)

#  define Rte_TypeDef_UInt4
typedef uint8 UInt4;
#  define UInt4_LowerLimit ((UInt4)0u)
#  define UInt4_UpperLimit ((UInt4)15u)

# endif


/**********************************************************************************************************************
 * Per-Instance Memory User Types
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Definitions for Mode Management
 *********************************************************************************************************************/
typedef uint8 Rte_ModeType_StaMd_Mode;

# define RTE_MODE_StaMd_Mode_DISABLE ((Rte_ModeType_StaMd_Mode)0)
# define RTE_MODE_StaMd_Mode_OFF ((Rte_ModeType_StaMd_Mode)1)
# define RTE_MODE_StaMd_Mode_OPERATE ((Rte_ModeType_StaMd_Mode)2)
# define RTE_MODE_StaMd_Mode_WARMINIT ((Rte_ModeType_StaMd_Mode)3)
# define RTE_TRANSITION_StaMd_Mode ((Rte_ModeType_StaMd_Mode)4)


/**********************************************************************************************************************
 * Constant value definitions
 *********************************************************************************************************************/

# if (defined RTE_CONST_D_FALSE_CNT_LGC) || (defined D_FALSE_CNT_LGC)
#  if (!defined RTE_CONST_D_FALSE_CNT_LGC) || (RTE_CONST_D_FALSE_CNT_LGC != FALSE)
#   error "Constant value <D_FALSE_CNT_LGC> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_D_FALSE_CNT_LGC (FALSE)
#  define D_FALSE_CNT_LGC ((Boolean)FALSE)
# endif

# if (defined RTE_CONST_D_TRUE_CNT_LGC) || (defined D_TRUE_CNT_LGC)
#  if (!defined RTE_CONST_D_TRUE_CNT_LGC) || (RTE_CONST_D_TRUE_CNT_LGC != TRUE)
#   error "Constant value <D_TRUE_CNT_LGC> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_D_TRUE_CNT_LGC (TRUE)
#  define D_TRUE_CNT_LGC ((Boolean)TRUE)
# endif

# if (defined RTE_CONST_D_2MS_SEC_F32) || (defined D_2MS_SEC_F32)
#  if (!defined RTE_CONST_D_2MS_SEC_F32) || (RTE_CONST_D_2MS_SEC_F32 != 0.002)
#   error "Constant value <D_2MS_SEC_F32> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_D_2MS_SEC_F32 (0.002)
#  define D_2MS_SEC_F32 ((Float)0.002)
# endif

# if (defined RTE_CONST_D_CCWEOTINIT_HWDEG_F32) || (defined D_CCWEOTINIT_HWDEG_F32)
#  if (!defined RTE_CONST_D_CCWEOTINIT_HWDEG_F32) || (RTE_CONST_D_CCWEOTINIT_HWDEG_F32 != -360)
#   error "Constant value <D_CCWEOTINIT_HWDEG_F32> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_D_CCWEOTINIT_HWDEG_F32 (-360)
#  define D_CCWEOTINIT_HWDEG_F32 ((Float)-360)
# endif

# if (defined RTE_CONST_D_CWEOTINIT_HWDEG_F32) || (defined D_CWEOTINIT_HWDEG_F32)
#  if (!defined RTE_CONST_D_CWEOTINIT_HWDEG_F32) || (RTE_CONST_D_CWEOTINIT_HWDEG_F32 != 360)
#   error "Constant value <D_CWEOTINIT_HWDEG_F32> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_D_CWEOTINIT_HWDEG_F32 (360)
#  define D_CWEOTINIT_HWDEG_F32 ((Float)360)
# endif

# if (defined RTE_CONST_D_ONE_ULS_F32) || (defined D_ONE_ULS_F32)
#  if (!defined RTE_CONST_D_ONE_ULS_F32) || (RTE_CONST_D_ONE_ULS_F32 != 1)
#   error "Constant value <D_ONE_ULS_F32> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_D_ONE_ULS_F32 (1)
#  define D_ONE_ULS_F32 ((Float)1)
# endif

# if (defined RTE_CONST_D_ZERO_ULS_F32) || (defined D_ZERO_ULS_F32)
#  if (!defined RTE_CONST_D_ZERO_ULS_F32) || (RTE_CONST_D_ZERO_ULS_F32 != 0)
#   error "Constant value <D_ZERO_ULS_F32> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_D_ZERO_ULS_F32 (0)
#  define D_ZERO_ULS_F32 ((Float)0)
# endif

# if (defined RTE_CONST_D_FOUR_CNT_U08) || (defined D_FOUR_CNT_U08)
#  if (!defined RTE_CONST_D_FOUR_CNT_U08) || (RTE_CONST_D_FOUR_CNT_U08 != 4u)
#   error "Constant value <D_FOUR_CNT_U08> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_D_FOUR_CNT_U08 (4u)
#  define D_FOUR_CNT_U08 ((UInt8)4u)
# endif

# if (defined RTE_CONST_D_ONE_CNT_U8) || (defined D_ONE_CNT_U8)
#  if (!defined RTE_CONST_D_ONE_CNT_U8) || (RTE_CONST_D_ONE_CNT_U8 != 1u)
#   error "Constant value <D_ONE_CNT_U8> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_D_ONE_CNT_U8 (1u)
#  define D_ONE_CNT_U8 ((UInt8)1u)
# endif

# if (defined RTE_CONST_D_THREE_CNT_U08) || (defined D_THREE_CNT_U08)
#  if (!defined RTE_CONST_D_THREE_CNT_U08) || (RTE_CONST_D_THREE_CNT_U08 != 3u)
#   error "Constant value <D_THREE_CNT_U08> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_D_THREE_CNT_U08 (3u)
#  define D_THREE_CNT_U08 ((UInt8)3u)
# endif

# if (defined RTE_CONST_D_TWO_CNT_U08) || (defined D_TWO_CNT_U08)
#  if (!defined RTE_CONST_D_TWO_CNT_U08) || (RTE_CONST_D_TWO_CNT_U08 != 2u)
#   error "Constant value <D_TWO_CNT_U08> conflicts with another constant."
#  endif
# else
#  define RTE_CONST_D_TWO_CNT_U08 (2u)
#  define D_TWO_CNT_U08 ((UInt8)2u)
# endif



/**********************************************************************************************************************
 * Type definitions for implicit access to S/R communication
 *********************************************************************************************************************/
/* Types for Data Handles section */

typedef struct
{
  Float value;
} Rte_DE_Float;

typedef struct
{
  Boolean value;
} Rte_DE_Boolean;


/**********************************************************************************************************************
 * Component Data Structures and Port Data Structures
 *********************************************************************************************************************/

struct Rte_CDS_Ap_VehDyn
{
  /* Data Handles section */
  P2VAR(Rte_DE_Float, TYPEDEF, RTE_AP_VEHDYN_APPL_VAR) VehDyn_Init1_RelHwPos_HwDeg_f32;
  P2VAR(Rte_DE_Float, TYPEDEF, RTE_AP_VEHDYN_APPL_VAR) VehDyn_Per1_CcwEOT_HwDeg_f32;
  P2VAR(Rte_DE_Float, TYPEDEF, RTE_AP_VEHDYN_APPL_VAR) VehDyn_Per1_CwEOT_HwDeg_f32;
  P2VAR(Rte_DE_Float, TYPEDEF, RTE_AP_VEHDYN_APPL_VAR) VehDyn_Per1_HwTorque_HwNm_f32;
  P2VAR(Rte_DE_Float, TYPEDEF, RTE_AP_VEHDYN_APPL_VAR) VehDyn_Per1_MotorVelCRF_MtrRadpS_f32;
  P2VAR(Rte_DE_Float, TYPEDEF, RTE_AP_VEHDYN_APPL_VAR) VehDyn_Per1_RelHwPos_HwDeg_f32;
  P2VAR(Rte_DE_Float, TYPEDEF, RTE_AP_VEHDYN_APPL_VAR) VehDyn_Per1_SensorlessAuthority_Uls_f32;
  P2VAR(Rte_DE_Float, TYPEDEF, RTE_AP_VEHDYN_APPL_VAR) VehDyn_Per1_SensorlessHwPos_HwDeg_f32;
  P2VAR(Rte_DE_Boolean, TYPEDEF, RTE_AP_VEHDYN_APPL_VAR) VehDyn_Per1_SrlHwAgVld_Cnt_lgc;
  P2VAR(Rte_DE_Float, TYPEDEF, RTE_AP_VEHDYN_APPL_VAR) VehDyn_Per1_SrlHwAg_HwDeg_f32;
  P2VAR(Rte_DE_Float, TYPEDEF, RTE_AP_VEHDYN_APPL_VAR) VehDyn_Per1_TorqueCmdCRF_MtrNm_f32;
  P2VAR(Rte_DE_Boolean, TYPEDEF, RTE_AP_VEHDYN_APPL_VAR) VehDyn_Per1_VehicleSpeedValid_Cnt_lgc;
  P2VAR(Rte_DE_Float, TYPEDEF, RTE_AP_VEHDYN_APPL_VAR) VehDyn_Per1_VehicleSpeed_Kph_f32;
  P2VAR(Rte_DE_Float, TYPEDEF, RTE_AP_VEHDYN_APPL_VAR) VehDyn_Trns1_HandwheelPosition_HwDeg_f32;
  P2VAR(Rte_DE_Float, TYPEDEF, RTE_AP_VEHDYN_APPL_VAR) VehDyn_Trns1_HwAuth_Uls_f32;
  P2VAR(Rte_DE_Float, TYPEDEF, RTE_AP_VEHDYN_APPL_VAR) VehDyn_Trns1_MechMtrPos_Rev_f32;
  /* PIM Handles section */
  P2VAR(VehDyn_DataType, TYPEDEF, RTE_VAR_DEFAULT_RTE_PIM_GROUP) Pim_MotPosReset;
  /* Vendor specific section */
};

# define RTE_START_SEC_CONST_UNSPECIFIED
# include "MemMap.h"

extern CONSTP2CONST(struct Rte_CDS_Ap_VehDyn, RTE_CONST, RTE_CONST) Rte_Inst_Ap_VehDyn;

# define RTE_STOP_SEC_CONST_UNSPECIFIED
# include "MemMap.h"

/* begin Fileversion check */
# ifndef SKIP_MAGIC_NUMBER
#  ifdef RTE_MAGIC_NUMBER
#   if RTE_MAGIC_NUMBER != 1450282354
#    error "The magic number of the generated file <C:/SynergyEA3/Working/VehDyn/tools/contract/Ap_VehDyn/Rte_Type.h> is different. Please check time and date of the generated RTE files!"
#   endif
#  else
#   define RTE_MAGIC_NUMBER 1450282354
#  endif  /* RTE_MAGIC_NUMBER */
# endif  /* SKIP_MAGIC_NUMBER */
/* end Fileversion check */

#endif /* _RTE_TYPE_H */
