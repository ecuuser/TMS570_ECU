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
 *          File:  Rte.h
 *     Workspace:  C:/Users/mzjphh/Desktop/Fiasa_326_327_05.01.00/Fiasa_326_327_EPS_TMS570/Tools/AsrProject/Config/DCF/EPS.dcf
 *   ECU-Project:  EPS
 *
 *     Generator:  MICROSAR RTE Generator Version 2.19.1
 *       License:  License CBD1010124 valid for CBD1010124 Nexteer  Package: BMW MSR SIP BAC3.0     Micro: TI TMS570 TMS570LS30306  Compiler: Code Composer Studio 4.9.0
 *
 *   Description:  Header file containing RTE types
 *********************************************************************************************************************/

/* double include prevention */

#ifndef _RTE_H
# define _RTE_H

# define RTE_SW_MAJOR_VERSION (0x02U)
# define RTE_SW_MINOR_VERSION (0x13U)
# define RTE_SW_PATCH_VERSION (0x01U)

# define RTE_VENDOR_ID (0x001EU)

# define RTE_AR_MAJOR_VERSION (0x02U)
# define RTE_AR_MINOR_VERSION (0x04U)
# define RTE_AR_PATCH_VERSION (0x00U)

# include "Std_Types.h"

# ifdef RTE_ENABLE_USER_DATATYPES
#  include "Rte_UserTypes.h"
# endif

# if !defined (TYPEDEF) && defined (AUTOMATIC)
#  define TYPEDEF AUTOMATIC
# endif

# if !defined (FUNC_P2CONST)
#  define FUNC_P2CONST(rettype, ptrclass, memclass) FUNC(P2CONST(rettype, AUTOMATIC, ptrclass), memclass)
# endif

/* Note: application errors are in the range between 1-63
         overlayed error (ORed with application errors) is 64
         structural errors are in the range between 128-256 */

/* common errors */
# define RTE_E_OK               (0U)
# define RTE_E_INVALID          (1U)

/* overlayed errors */
# define RTE_E_LOST_DATA        (64U)
# define RTE_E_MAX_AGE_EXCEEDED (64U)

/* immediate infrastructure errors */
# define RTE_E_COM_STOPPED      (128U)
# define RTE_E_COMMS_ERROR      (128U)  /* AUTOSAR 2.1 compatibility */
# define RTE_E_TIMEOUT          (129U)
# define RTE_E_LIMIT            (130U)
# define RTE_E_NO_DATA          (131U)
# define RTE_E_TRANSMIT_ACK     (132U)
# define RTE_E_NEVER_RECEIVED   (133U)

/* assertion handling */
# ifdef RTE_ASSERTION_ENABLED

void Rte_FatalError(uint8 error);

/* internal errors */
#  define RTE_E_INTERNAL_ModeArgument          (0x01U)
#  define RTE_E_INTERNAL_TriggerDisableCounter (0x02U)
#  define RTE_E_INTERNAL_TransitionState       (0x03U)

#  define Rte_Assert(x,e) if (!x) {Rte_FatalError(e);}
# else
#  define Rte_Assert(x,e)
# endif


#endif /* _RTE_H */
