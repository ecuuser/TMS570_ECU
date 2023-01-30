/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2009 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  IoHwAb.h
 *    Component:  EcuAb_AsrIoHwAb
 *       Module:  IoHwAb
 *    Generator:  -
 *
 *  Description:  The IO Hardware Abstraction provides the transitions of signals from the MCAL layer to the upper
 *                layers through the Rte.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Christian Marchl              Chm           Vector Informatik GmbH
 *  Christoph Ederer              Cer           Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  1.01.01   2007-11-26  Chm     ESCAN00023309 Changed line endings to CRLF
 *  1.02.00   2008-05-07  Cer     5006330       Created BSWMD, reworked transformation to use ECU-C file as input,
 *                                              multiple operations in one user defined port possible now, DCM
 *                                              interface added
 *  1.02.01   2009-03-18  Cer     ESCAN00033090 Rework of the memory mapping
 *  1.03.00   2009-09-18  Cer     -             Added symbolic constants for signal states
 *********************************************************************************************************************/

#if (!defined IOHWAB_H)
#define IOHWAB_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/*---- Version identification  ---*/
#define IOHWAB_VENDOR_ID              (30u) /* Vector Informatik */
#define IOHWAB_MODULE_ID              (254u)

/* ##V_CFG_MANAGEMENT ##CQProject : EcuAb_AsrIoHwAb CQComponent : Implementation */
#define ECUAB_ASRIOHWAB_VERSION          0x0103u
#define ECUAB_ASRIOHWAB_RELEASE_VERSION  0x00u

#define IOHWAB_AR_MAJOR_VERSION       (2u)
#define IOHWAB_AR_MINOR_VERSION       (0u)
#define IOHWAB_AR_PATCH_VERSION       (0u)

#define IOHWAB_SW_MAJOR_VERSION       (ECUAB_ASRIOHWAB_VERSION >> 8)
#define IOHWAB_SW_MINOR_VERSION       (ECUAB_ASRIOHWAB_VERSION & 0x00FF)
#define IOHWAB_SW_PATCH_VERSION       ECUAB_ASRIOHWAB_RELEASE_VERSION

/* ----------Error Codes in Development-Mode------------------------------- */
#define IOHWAB_E_NULL_POINTER           (0x10u)

/* ----------IoHwAb Service Identification--------------------------------- */
#define IOHWAB_SID_INIT                       (0x01u)
#define IOHWAB_SID_GET_VERSION_INFO           (0x10u)
#define IOHWAB_SID_OPT_GET                    (0x20u)
#define IOHWAB_SID_OPT_SET                    (0x21u)
#define IOHWAB_SID_OPT_DIAG                   (0x22u)
#define IOHWAB_SID_OPT_DCM_READ               (0x2Au)
#define IOHWAB_SID_OPT_GET_USER_DEFINED       (0x30u)
#define IOHWAB_SID_OPT_SET_USER_DEFINED       (0x31u)
#define IOHWAB_SID_OPT_DIAG_USER_DEFINED      (0x32u)
#define IOHWAB_SID_OPT_DCM_READ_USER_DEFINED  (0x3Au)

/* ----------IoHwAb Signal States------------------------------------------ */
#define IOHWAB_CHL_UNLOCK                     (0x00u)
#define IOHWAB_CHL_LOCK                       (0x01u)

/* ---- API CFG Includes -------------------------------------------------- */
/* include of configuration public part */
#include "Std_Types.h"
#include "IoHwAb_Cfg.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define IOHWAB_START_SEC_CODE
#include "MemMap.h"

FUNC(void, IOHWAB_CODE) IoHwAb_GetVersionInfo
  (
      P2VAR(Std_VersionInfoType, AUTOMATIC, IOHWAB_APPL_DATA) versioninfo
  );

FUNC(void, IOHWAB_CODE) IoHwAb_Init(void);

#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

#endif
/**********************************************************************************************************************
 *  END OF FILE: IoHwAb.h
 *********************************************************************************************************************/

