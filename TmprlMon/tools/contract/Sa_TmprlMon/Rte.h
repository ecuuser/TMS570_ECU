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
 *          File:  Rte.h
 *     Workspace:  C:/Sankar/Synergy/Working/TmprlMon-pznywf/TmprlMon/autosar
 *     SW-C Type:  Sa_TmprlMon
 *  Generated at:  Tue Jul  7 09:48:21 2015
 *
 *     Generator:  MICROSAR RTE Generator Version 2.17.2
 *       License:  License CBD1010122 valid for CBD1010122 Nexteer  GM MSR_SLP3_BSW_RTE_wGMLAN TexasInstruments TMS570 Texas Instruments
 *
 *   Description:  Header file containing RTE types (Contract Phase)
 *********************************************************************************************************************/

/* double include prevention */

#ifndef _RTE_H
# define _RTE_H

# define RTE_SW_MAJOR_VERSION (0x02u)
# define RTE_SW_MINOR_VERSION (0x11u)
# define RTE_SW_PATCH_VERSION (0x02u)

# define RTE_VENDOR_ID (0x001Eu)

# define RTE_AR_MAJOR_VERSION (0x02u)
# define RTE_AR_MINOR_VERSION (0x02u)
# define RTE_AR_PATCH_VERSION (0x00u)

# include "Std_Types.h"

/* AUTOSAR 2.1 compatibility */
# if !defined (STATIC) && defined (_STATIC_)
#  define STATIC _STATIC_
# endif

# if !defined (TYPEDEF) && defined (AUTOMATIC)
#  define TYPEDEF AUTOMATIC
# endif

/* Note: application errors are in the range between 1-63
         overlayed error (ORed with application errors) is 64
         structural errors are in the range between 128-256 */

/* common errors */
# define RTE_E_OK               ((Std_ReturnType)  0)
# define RTE_E_INVALID          ((Std_ReturnType)  1)

/* overlayed errors */
# define RTE_E_LOST_DATA        ((Std_ReturnType) 64)
# define RTE_E_MAX_AGE_EXCEEDED ((Std_ReturnType) 64)

/* immediate infrastructure errors */
# define RTE_E_COM_STOPPED      ((Std_ReturnType)128)
# define RTE_E_COMMS_ERROR      ((Std_ReturnType)128)  /* AUTOSAR 2.1 compatibility */
# define RTE_E_TIMEOUT          ((Std_ReturnType)129)
# define RTE_E_LIMIT            ((Std_ReturnType)130)
# define RTE_E_NO_DATA          ((Std_ReturnType)131)
# define RTE_E_TRANSMIT_ACK     ((Std_ReturnType)132)

/* begin Fileversion check */
# ifndef SKIP_MAGIC_NUMBER
#  ifdef RTE_MAGIC_NUMBER
#   if RTE_MAGIC_NUMBER != 1436273839
#    error "The magic number of the generated file <C:/Sankar/Synergy/Working/TmprlMon-pznywf/TmprlMon/tools/contract/Sa_TmprlMon/Rte.h> is different. Please check time and date of the generated RTE files!"
#   endif
#  else
#   define RTE_MAGIC_NUMBER 1436273839
#  endif  /* RTE_MAGIC_NUMBER */
# endif  /* SKIP_MAGIC_NUMBER */
/* end Fileversion check */

#endif /* _RTE_H */
