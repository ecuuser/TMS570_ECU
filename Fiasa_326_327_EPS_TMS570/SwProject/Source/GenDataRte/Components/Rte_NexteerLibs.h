/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  Copyright (c) 2006-2011 by Vector Informatik GmbH.                                             All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Components/Rte_NexteerLibs.h
 *     Workspace:  C:/Users/mzjphh/Desktop/Fiasa_326_327_05.01.00/Fiasa_326_327_EPS_TMS570/Tools/AsrProject/Config/DCF/EPS.dcf
 *   ECU-Project:  EPS
 *
 *     Generator:  MICROSAR RTE Generator Version 2.19.1
 *       License:  License CBD1010124 valid for CBD1010124 Nexteer  Package: BMW MSR SIP BAC3.0     Micro: TI TMS570 TMS570LS30306  Compiler: Code Composer Studio 4.9.0
 *
 *   Description:  Application header file for SW-C
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_NEXTEERLIBS_H
# define _RTE_NEXTEERLIBS_H

# ifndef RTE_CORE
#  ifdef RTE_APPLICATION_HEADER_FILE
#   error Multiple application header files included.
#  endif
#  define RTE_APPLICATION_HEADER_FILE
# endif

# ifdef __cplusplus
extern "C"
{
# endif /* __cplusplus */

/* include files */

# include "Rte_Type.h"


/**********************************************************************************************************************
 * Buffers for inter-runnable variables
 *********************************************************************************************************************/

# define RTE_START_SEC_VAR_Ap_10_INIT_UNSPECIFIED
# include "MemMap.h"

extern VAR(UInt32, RTE_VAR_INIT) Rte_Irv_NexteerLibs_Time_mS_u32;

# define RTE_STOP_SEC_VAR_Ap_10_INIT_UNSPECIFIED
# include "MemMap.h"


# define RTE_START_SEC_CODE
# include "MemMap.h"

/**********************************************************************************************************************
 * API prototypes
 *********************************************************************************************************************/

# define RTE_STOP_SEC_CODE
# include "MemMap.h"


# ifndef RTE_CORE

/**********************************************************************************************************************
 * Inter-runnable variables
 *********************************************************************************************************************/

#  define Rte_IrvRead_DtrmnElapsedTime_mS_u16_Time_mS_u32() \
  Rte_Irv_NexteerLibs_Time_mS_u32

#  define Rte_IrvRead_DtrmnElapsedTime_mS_u32_Time_mS_u32() \
  Rte_Irv_NexteerLibs_Time_mS_u32

#  define Rte_IrvRead_GetSystemTime_mS_u32_Time_mS_u32() \
  Rte_Irv_NexteerLibs_Time_mS_u32

#  define Rte_IrvRead_SystemTime_Per1_Time_mS_u32() \
  Rte_Irv_NexteerLibs_Time_mS_u32

#  define Rte_IrvWrite_SystemTime_Per1_Time_mS_u32(data) \
  (Rte_Irv_NexteerLibs_Time_mS_u32 = (data))


# endif /* !defined(RTE_CORE) */


# define RTE_START_SEC_NEXTEERLIBS_APPL_CODE
# include "MemMap.h"

/**********************************************************************************************************************
 * Runnable entities
 *********************************************************************************************************************/

FUNC(void, RTE_NEXTEERLIBS_APPL_CODE) DtrmnElapsedTime_mS_u16(UInt32 InitialTime, P2VAR(UInt16, AUTOMATIC, RTE_NEXTEERLIBS_APPL_VAR) ElapsedTime);

FUNC(void, RTE_NEXTEERLIBS_APPL_CODE) DtrmnElapsedTime_mS_u32(UInt32 InitialTime, P2VAR(UInt32, AUTOMATIC, RTE_NEXTEERLIBS_APPL_VAR) ElapsedTime);

FUNC(void, RTE_NEXTEERLIBS_APPL_CODE) DtrmnElapsedTime_uS_u16(UInt32 InitialTime, P2VAR(UInt16, AUTOMATIC, RTE_NEXTEERLIBS_APPL_VAR) ElapsedTime);

FUNC(void, RTE_NEXTEERLIBS_APPL_CODE) DtrmnElapsedTime_uS_u32(UInt32 InitialTime, P2VAR(UInt32, AUTOMATIC, RTE_NEXTEERLIBS_APPL_VAR) ElapsedTime);

FUNC(void, RTE_NEXTEERLIBS_APPL_CODE) GetSystemTime_mS_u32(P2VAR(UInt32, AUTOMATIC, RTE_NEXTEERLIBS_APPL_VAR) CurrentTime);

FUNC(void, RTE_NEXTEERLIBS_APPL_CODE) GetSystemTime_uS_u32(P2VAR(UInt32, AUTOMATIC, RTE_NEXTEERLIBS_APPL_VAR) CurrentTime);

FUNC(void, RTE_NEXTEERLIBS_APPL_CODE) SystemTime_Per1(void);

# define RTE_STOP_SEC_NEXTEERLIBS_APPL_CODE
# include "MemMap.h"

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */


#endif /* _RTE_NEXTEERLIBS_H */
