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
 *          File:  Rte_Sa_TmprlMon2.h
 *     Workspace:  C:/Sankar/Synergy/Working/TmprlMon-pznywf/TmprlMon/autosar
 *     SW-C Type:  Sa_TmprlMon2
 *  Generated at:  Tue Jul  7 09:48:34 2015
 *
 *     Generator:  MICROSAR RTE Generator Version 2.17.2
 *       License:  License CBD1010122 valid for CBD1010122 Nexteer  GM MSR_SLP3_BSW_RTE_wGMLAN TexasInstruments TMS570 Texas Instruments
 *
 *   Description:  Application header file for SW-C <Sa_TmprlMon2> (Contract Phase)
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_SA_TMPRLMON2_H
# define _RTE_SA_TMPRLMON2_H

# ifdef RTE_APPLICATION_HEADER_FILE
#  error Multiple application header files included.
# endif
# define RTE_APPLICATION_HEADER_FILE

# ifdef __cplusplus
extern "C"
{
# endif /* __cplusplus */

/* include files */

# include "Rte_Type.h"

typedef P2CONST(struct Rte_CDS_Sa_TmprlMon2, TYPEDEF, RTE_CONST) Rte_Instance;


# define RTE_START_SEC_CODE
# include "MemMap.h"

/**********************************************************************************************************************
 * API prototypes
 *********************************************************************************************************************/
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Sa_TmprlMon2_WdMonitor_OP_SET(IoHwAb_BoolType signal);

# define RTE_STOP_SEC_CODE
# include "MemMap.h"



/**********************************************************************************************************************
 * Rte_Call_<p>_<o> (C/S invocation)
 *********************************************************************************************************************/
# define Rte_Call_WdMonitor_OP_SET Rte_Call_Sa_TmprlMon2_WdMonitor_OP_SET




# define RTE_START_SEC_SA_TMPRLMON2_APPL_CODE
# include "MemMap.h"


/**********************************************************************************************************************
 *
 * Runnable Entity Name: TmprlMon2_Per1
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 2ms
 *
 **********************************************************************************************************************
 *
 * Client/Server Interfaces:
 * =========================
 *   Server Invocation:
 *   ------------------
 *   Std_ReturnType Rte_Call_WdMonitor_OP_SET(IoHwAb_BoolType signal)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_WdMonitor_E_NOT_OK
 *
 *********************************************************************************************************************/

FUNC(void, RTE_SA_TMPRLMON2_APPL_CODE) TmprlMon2_Per1(void);

# define RTE_STOP_SEC_SA_TMPRLMON2_APPL_CODE
# include "MemMap.h"


/**********************************************************************************************************************
 * Application errors
 *********************************************************************************************************************/

# define RTE_E_WdMonitor_E_NOT_OK (1u)

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */

/* begin Fileversion check */
# ifndef SKIP_MAGIC_NUMBER
#  ifdef RTE_MAGIC_NUMBER
#   if RTE_MAGIC_NUMBER != 1436270757
#    error "The magic number of the generated file <C:/Sankar/Synergy/Working/TmprlMon-pznywf/TmprlMon/tools/contract/Sa_TmprlMon2/Rte_Sa_TmprlMon2.h> is different. Please check time and date of the generated RTE files!"
#   endif
#  else
#   define RTE_MAGIC_NUMBER 1436270757
#  endif  /* RTE_MAGIC_NUMBER */
# endif  /* SKIP_MAGIC_NUMBER */
/* end Fileversion check */

#endif /* _RTE_SA_TMPRLMON2_H */
