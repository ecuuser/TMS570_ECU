/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2008 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  MemIf.h
 *    Component:  If_AsrIfMem
 *       Module:  MemIf
 *    Generator:  -
 *
 *  Description:  The Memory Abstraction Interface provides uniform access to services of underlying
 *                Memory Hardware abstraction (MemHwA) modules, i.e. EEPROM Abstraction (EA) and
 *                Flash EEPROM Emulation (FEE). The appropriate MemHwA module is selected by a device index.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Tobias Schmid                 Tsd           Vector Informatik GmbH
 *  Roland Suess                  Rsu           Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.02.00  -           Tsd     -             first production release
 *  02.00.00  2008-04-09  Tsd     -             update for AUTOSAR Release 3.0
 *  02.00.01  2008-05-13  Tsd     -             Introduced SIP-Check
 *  02.01.00  2008-09-15  Rsu     -             Supporting 2 Fee instances in NvM
 *  02.01.01  2009-10-20  Tsd     ESCAN00037330 Corrected Fee/Ea calls in macro API in MemIf_Cfg.h
 *  02.01.02  2011-03-16  Du      ESCAN00042276  Only changes in MemIF_Types.h, but SW Patch Version is incremented
 *********************************************************************************************************************/

/*---- Protection against multiple inclusion ------------------------------*/
#if !defined _MEMIF_H_
#define _MEMIF_H_

/*---- Include Header Files ---------------------------*/
#include "MemIf_Types.h"
#include "MemIf_Cfg.h"


/*---- Version identification ---------------*/
/* ##V_CFG_MANAGEMENT ##CQProject : If_AsrIfMem CQComponent : Implementation */
/* Version - BCD coded version number - Main- and Sub-Version - Release-Version */
#define IF_ASRIFMEM_VERSION          (0x0201u)
#define IF_ASRIFMEM_RELEASE_VERSION  (0x02u)

#define MEMIF_MODULE_ID         (22U)
#define MEMIF_VENDOR_ID         (30U)

#define MEMIF_AR_MAJOR_VERSION  ( 1u)
#define MEMIF_AR_MINOR_VERSION  ( 2u)
#define MEMIF_AR_PATCH_VERSION  ( 0u)

#define MEMIF_SW_MAJOR_VERSION  (IF_ASRIFMEM_VERSION >> 8)
#define MEMIF_SW_MINOR_VERSION  (IF_ASRIFMEM_VERSION & 0x00FFu)
#define MEMIF_SW_PATCH_VERSION  (IF_ASRIFMEM_RELEASE_VERSION)

/*---- Perform version checking ------------*/
#if    (  (MEMIF_TYPES_MAJOR_VERSION != (1U)) \
       || (MEMIF_TYPES_MINOR_VERSION != (2U)) )
  #error "Version numbers of MemIf.h and MemIf_Types.h are inconsistent!"
#endif

/*---- Perform check of the defined number of devices ------------*/

#if ( MEMIF_NUMBER_OF_DEVICES == 0 )
  #error "No Eeprom Devices defined!"
#endif

/*---- API Defines ---------------------------------------------------------*/

#define MEMIF_BROADCAST_ID (0xFFu) /* MemIf036, the identifier is not specified */

/*---------MEMIF Service Identification-------------------------------------*/
#define MEMIF_SID_SETMODE         (0x01U)
#define MEMIF_SID_READ            (0x02U)
#define MEMIF_SID_WRITE           (0x03U)
#define MEMIF_SID_CANCEL          (0x04U)
#define MEMIF_SID_GET_STATUS      (0x05U)
#define MEMIF_SID_GET_JOB_RESULT  (0x06U)
#define MEMIF_SID_INVALIDATE      (0x07U)
#define MEMIF_SID_VERSION_INFO    (0x08u)
#define MEMIF_SID_ERASE           (0x09u)

/*---- API Macros ----------------------------------------------------------*/

/*---- API Type definitions ------------------------------------------------*/

/*---- API Structures ------------------------------------------------------*/

/*---- API Variables -------------------------------------------------------*/

/*---- API Functions -------------------------------------------------------*/

#define MEMIF_START_SEC_CODE
#include "MemMap.h"

FUNC(void, MEMIF_CODE)             MemIf_SetMode(MemIf_ModeType  Mode);
FUNC(MemIf_StatusType, MEMIF_CODE) MemIf_GetStatus( uint8 DeviceIndex );


/* Following functios will only be provided, if Development mode is activated */
#if(STD_ON == MEMIF_CFG_USE_FCT_API)

    FUNC(Std_ReturnType, MEMIF_CODE) MemIf_Read(uint8   DeviceIndex,
                                                      uint16   BlockNumber,
                                                      uint16   BlockOffset,
                                           MemIf_DataPtr_pu8   DataBufferPtr,
                                                      uint16   Length);

    FUNC(Std_ReturnType, MEMIF_CODE) MemIf_Write
                                  (
                                                       uint8   DeviceIndex,
                                                      uint16   BlockNumber,
                                           MemIf_DataPtr_pu8   DataBufferPtr);

    FUNC(Std_ReturnType, MEMIF_CODE) MemIf_EraseImmediateBlock
                                  (
                                                       uint8   DeviceIndex,
                                                      uint16   BlockNumber
                                  );

    FUNC(Std_ReturnType, MEMIF_CODE) MemIf_InvalidateBlock
                                  (
                                                       uint8   DeviceIndex,
                                                      uint16   BlockNumber
                                  );

    FUNC(void, MEMIF_CODE) MemIf_Cancel( uint8 DeviceIndex );
    FUNC(MemIf_JobResultType, MEMIF_CODE) MemIf_GetJobResult( uint8 DeviceIndex );

#endif /* MEMIF_CFG_USE_FCT_API */


#if (STD_ON == MEMIF_VERSION_INFO_API)
    FUNC(void, MEMIF_CODE) MemIf_GetVersionInfo
            (
                P2VAR(Std_VersionInfoType, AUTOMATIC, MEMIF_APPL_DATA) VersionInfoPtr
            );
#endif


#define MEMIF_STOP_SEC_CODE
#include "MemMap.h"

/*--------------------------------------------------------------------------*/


#endif /* _MEMIF_H_ */
/*---- End of File ---------------------------------------------------------*/

