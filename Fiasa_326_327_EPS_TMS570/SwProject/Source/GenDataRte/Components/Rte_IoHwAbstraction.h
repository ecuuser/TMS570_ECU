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
 *          File:  Components/Rte_IoHwAbstraction.h
 *     Workspace:  C:/Users/mzjphh/Desktop/Fiasa_326_327_05.01.00/Fiasa_326_327_EPS_TMS570/Tools/AsrProject/Config/DCF/EPS.dcf
 *   ECU-Project:  EPS
 *
 *     Generator:  MICROSAR RTE Generator Version 2.19.1
 *       License:  License CBD1010124 valid for CBD1010124 Nexteer  Package: BMW MSR SIP BAC3.0     Micro: TI TMS570 TMS570LS30306  Compiler: Code Composer Studio 4.9.0
 *
 *   Description:  Application header file for SW-C
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_IOHWABSTRACTION_H
# define _RTE_IOHWABSTRACTION_H

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


# define RTE_START_SEC_IOHWABSTRACTION_APPL_CODE
# include "MemMap.h"

/**********************************************************************************************************************
 * Runnable entities
 *********************************************************************************************************************/

FUNC(void, RTE_IOHWABSTRACTION_APPL_CODE) IoHwAb_Dummy(void);

FUNC(Std_ReturnType, RTE_IOHWABSTRACTION_APPL_CODE) IoHwAb_GetEpsEn(P2VAR(IoHwAb_BoolType, AUTOMATIC, RTE_IOHWABSTRACTION_APPL_VAR) signal);

FUNC(Std_ReturnType, RTE_IOHWABSTRACTION_APPL_CODE) IoHwAb_GetFetDrvCntl(P2VAR(IoHwAb_BoolType, AUTOMATIC, RTE_IOHWABSTRACTION_APPL_VAR) signal);

FUNC(Std_ReturnType, RTE_IOHWABSTRACTION_APPL_CODE) IoHwAb_GetFetDrvReset(P2VAR(IoHwAb_BoolType, AUTOMATIC, RTE_IOHWABSTRACTION_APPL_VAR) signal);

FUNC(Std_ReturnType, RTE_IOHWABSTRACTION_APPL_CODE) IoHwAb_GetFetFlt1Data(P2VAR(IoHwAb_BoolType, AUTOMATIC, RTE_IOHWABSTRACTION_APPL_VAR) signal);

FUNC(Std_ReturnType, RTE_IOHWABSTRACTION_APPL_CODE) IoHwAb_GetFetFlt2Clk(P2VAR(IoHwAb_BoolType, AUTOMATIC, RTE_IOHWABSTRACTION_APPL_VAR) signal);

FUNC(Std_ReturnType, RTE_IOHWABSTRACTION_APPL_CODE) IoHwAb_GetOvrVoltFdbk(P2VAR(IoHwAb_BoolType, AUTOMATIC, RTE_IOHWABSTRACTION_APPL_VAR) signal);

FUNC(Std_ReturnType, RTE_IOHWABSTRACTION_APPL_CODE) IoHwAb_GetPwrSwitchEn(P2VAR(IoHwAb_BoolType, AUTOMATIC, RTE_IOHWABSTRACTION_APPL_VAR) signal);

FUNC(Std_ReturnType, RTE_IOHWABSTRACTION_APPL_CODE) IoHwAb_GetSysFault2(P2VAR(IoHwAb_BoolType, AUTOMATIC, RTE_IOHWABSTRACTION_APPL_VAR) signal);

FUNC(Std_ReturnType, RTE_IOHWABSTRACTION_APPL_CODE) IoHwAb_InputOP_GET(P2VAR(IoHwAb_BoolType, AUTOMATIC, RTE_IOHWABSTRACTION_APPL_VAR) signal);

FUNC(Std_ReturnType, RTE_IOHWABSTRACTION_APPL_CODE) IoHwAb_OutputOP_SET(IoHwAb_BoolType signal);

FUNC(Std_ReturnType, RTE_IOHWABSTRACTION_APPL_CODE) IoHwAb_SetFetDrvReset(IoHwAb_BoolType signal);

FUNC(Std_ReturnType, RTE_IOHWABSTRACTION_APPL_CODE) IoHwAb_SetFetFlt2Clk(IoHwAb_BoolType signal);

FUNC(Std_ReturnType, RTE_IOHWABSTRACTION_APPL_CODE) IoHwAb_OutputSetFetFlt2ToOutput(IoHwAb_BoolType signal);

FUNC(Std_ReturnType, RTE_IOHWABSTRACTION_APPL_CODE) IoHwAb_SetSysFault2(IoHwAb_BoolType signal);

FUNC(Std_ReturnType, RTE_IOHWABSTRACTION_APPL_CODE) IoHwAb_SetTODReset(IoHwAb_BoolType signal);

FUNC(Std_ReturnType, RTE_IOHWABSTRACTION_APPL_CODE) IoHwAb_SetWdMonitor(IoHwAb_BoolType signal);

FUNC(Std_ReturnType, RTE_IOHWABSTRACTION_APPL_CODE) IoHwAb_SetWdReset(IoHwAb_BoolType signal);

# define RTE_STOP_SEC_IOHWABSTRACTION_APPL_CODE
# include "MemMap.h"


# ifndef RTE_CORE
/**********************************************************************************************************************
 * Application errors
 *********************************************************************************************************************/

#  define RTE_E_EpsEn_E_NOT_OK (1U)

#  define RTE_E_FetDrvCntl_E_NOT_OK (1U)

#  define RTE_E_FetDrvReset_E_NOT_OK (1U)

#  define RTE_E_FetFlt1Data_E_NOT_OK (1U)

#  define RTE_E_FetFlt2Clk_E_NOT_OK (1U)

#  define RTE_E_IoHwAbPortConfig_E_NOT_OK (1U)

#  define RTE_E_OvrVoltFdbk_E_NOT_OK (1U)

#  define RTE_E_PwrSwitchEn_E_NOT_OK (1U)

#  define RTE_E_SysFault2_E_NOT_OK (1U)

#  define RTE_E_SysFault3_E_NOT_OK (1U)

#  define RTE_E_TODReset_E_NOT_OK (1U)

#  define RTE_E_WdMonitor_E_NOT_OK (1U)

#  define RTE_E_WdReset_E_NOT_OK (1U)
# endif /* !defined(RTE_CORE) */

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */


#endif /* _RTE_IOHWABSTRACTION_H */
